 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <FreeRTOS.h>
#include <task.h>
#include <queue.h>
#include <semphr.h>

#include <osdep_service.h>
#include "mmf2.h"
#include "mmf2_dbg.h"

#include "module_isp.h"
#include "isp_api.h"
#include "isp_cmd_api.h"
#include "sys_api_ext.h"

#include "isp_boot.h"
#include "sensor.h"

#include "flash_api.h"
#include "device_lock.h"

#define ISP_BOOT_ADDR 0x60000

extern isp_boot_cfg_t isp_boot_cfg_global;
//-----------------------------------------------------------------------------

#define ISP_DEBUG_SHOW 1
void isp_frame_complete_cb(void* p)
{
    BaseType_t xTaskWokenByReceive = pdFALSE;
    BaseType_t xHigherPriorityTaskWoken;
    
    isp_ctx_t* ctx = (isp_ctx_t*)p;
    isp_info_t* info = &ctx->stream->info;
    isp_params_t* params = &ctx->params;
    mm_context_t *mctx = (mm_context_t*)ctx->parent;
    mm_queue_item_t* output_item;

#if ISP_DEBUG_SHOW
    isp_state_t* state = &ctx->state;
#endif    

    int is_output_ready = 0;

    u32 timestamp = xTaskGetTickCountFromISR();
    //rt_printf("isp ddr finish\n\r");

    if(info->isp_overflow_flag == 0){
        is_output_ready = xQueueReceiveFromISR(mctx->output_recycle, &output_item, &xTaskWokenByReceive) == pdTRUE;
    }else{
        info->isp_overflow_flag = 0;
        ISP_DBG_INFO("isp overflow = %d\r\n",params->stream_id);
        //printf("[Z]isp overflow = %d\r\n",params->stream_id);
    }

#if ISP_DEBUG_SHOW
    if(state->timer_2 == 0){
        state->timer_1 = xTaskGetTickCountFromISR();
        state->timer_2 = state->timer_1;
    }else{
        state->timer_2 = xTaskGetTickCountFromISR();
        if((state->timer_2 - state->timer_1)>=1000){
          ISP_DBG_INFO("[%d] isp:%d drop:%d isp_total:%d drop_total:%d",
                       params->stream_id, state->isp_frame, state->drop_frame, state->isp_frame_total, state->drop_frame_total);
          state->timer_2 = 0;
          state->drop_frame = 0;
          state->isp_frame = 0;
        }
    }
#endif

    if(is_output_ready){

        int uv_offset = params->width*params->height;

        isp_buf_t buf;

        buf.y_addr = output_item->data_addr;
        buf.uv_addr = output_item->data_addr+uv_offset;

        isp_handle_buffer(ctx->stream, &buf, MODE_EXCHANGE);
        ctx->hw_slot_item[buf.slot_id]->data_addr = output_item->data_addr;
        // update backup infomation, needed for free resource
        //mm_printf("ex %x <-> %x\n\r", output_item->data_addr, buf.y_addr);

        output_item->data_addr = buf.y_addr;
        output_item->timestamp = timestamp;
        output_item->hw_timestamp = buf.timestamp;
		
		if(params->format == ISP_FORMAT_YUV420_SEMIPLANAR)
			output_item->size =(int) (params->width*params->height*1.5);
		else
			output_item->size = params->width*params->height*2;

        xQueueSendFromISR(mctx->output_ready, (void*)&output_item, &xHigherPriorityTaskWoken);
#if ISP_DEBUG_SHOW
        state->isp_frame++;
        state->isp_frame_total++;
#endif        
    }else{
        isp_handle_buffer(ctx->stream, NULL, MODE_SKIP);
#if ISP_DEBUG_SHOW
        state->drop_frame++;
        state->drop_frame_total++;
#endif        
    }
    if( xHigherPriorityTaskWoken || xTaskWokenByReceive)
        taskYIELD ();
}

#if SENSOR_AUTO_SEL

static void SNR_Clock_Switch(int on)
{
        int value = on;
        isp_set_memory((unsigned char *)&value,SENSOR_CLOCK_SWITCH_REG,1);
        vTaskDelay(10);
}

static void SetGPIOVal(int pin_num,int output)
{
	isp_set_gpio_dir(pin_num,SENSOR_GPIO_OUTPUT);
	isp_set_gpio_value(pin_num,output);
}
static void SensorPowerControl(int on,int delayms)
{
	isp_set_gpio_dir(SENSOR_POWER_ENABLE_PIN,SENSOR_GPIO_OUTPUT);
	isp_set_gpio_value(SENSOR_POWER_ENABLE_PIN,on);
	vTaskDelay(delayms);
}
static void SetGPIODir(int pin_num,int dir)
{
	isp_set_gpio_dir(pin_num,dir);
}

static void Delay(int ms)
{
	vTaskDelay(ms);
}
static void uDelay(int u)
{
        hal_delay_us(u);
}

static void usDelay(int u)
{
        hal_delay_us(u);
}

static void WaitTimeOut_Delay(int ms)
{
        vTaskDelay(ms);
}


static void isp_jxf_37_power_on()
{
	SetGPIOVal(SENSOR_POWER_DONE_PIN,SENSOR_PIN_HIGH);
	SetGPIOVal(SENSOR_RESET_PIN,SENSOR_PIN_HIGH); 
	Delay(1);
	SensorPowerControl(SWITCH_ON, EN_DELAYTIME);
	uDelay(1);
	SNR_Clock_Switch(CLOCK_SWITCH_ON);
	Delay(1);
	SetGPIOVal(SENSOR_RESET_PIN,SENSOR_PIN_LOW);
	WaitTimeOut_Delay(12);
	SetGPIOVal(SENSOR_RESET_PIN,SENSOR_PIN_HIGH); 
	Delay(1);
	SetGPIOVal(SENSOR_POWER_DONE_PIN,SENSOR_PIN_LOW);
}
static void isp_gc_1054_power_on()
{
	SetGPIOVal(SENSOR_RESET_PIN,SENSOR_PIN_LOW);
	SetGPIOVal(SENSOR_POWER_DONE_PIN,SENSOR_PIN_HIGH);
	SensorPowerControl(SWITCH_ON,EN_DELAYTIME);
	uDelay(1);
	SNR_Clock_Switch(CLOCK_SWITCH_ON);
	uDelay(1);
	SetGPIOVal(SENSOR_POWER_DONE_PIN,SENSOR_PIN_LOW);
	uDelay(1);
	SetGPIOVal(SENSOR_RESET_PIN,SENSOR_PIN_HIGH);
	WaitTimeOut_Delay(1);
}
static void isp_ps_5270_power_on()
{
	SNR_Clock_Switch(CLOCK_SWITCH_OFF);
	SetGPIOVal(SENSOR_POWER_DONE_PIN,SENSOR_PIN_LOW);
	Delay(1);
	usDelay(100);
	SensorPowerControl(SWITCH_ON,EN_DELAYTIME);
	usDelay(100);
	SetGPIOVal(SENSOR_RESET_PIN,SENSOR_PIN_LOW);
	Delay(10);
	SetGPIOVal(SENSOR_RESET_PIN,SENSOR_PIN_HIGH);
	usDelay(100);
	SNR_Clock_Switch(CLOCK_SWITCH_ON);
	Delay(3);
}
static void isp_gc_2053_power_on()
{
        SetGPIODir(0,1);
        SetGPIODir(1,1);
        SetGPIOVal(1,0);
        SetGPIOVal(0,0);
        SensorPowerControl(SWITCH_ON, EN_DELAYTIME);
        uDelay(1); // unit :100us
        SNR_Clock_Switch(CLOCK_SWITCH_ON);
        uDelay(1);
        SetGPIOVal(1,1);
        uDelay(1);
        SetGPIOVal(0,1);
        WaitTimeOut_Delay(1);
}

static void isp_sc_2232_power_on()
{
	SensorPowerControl(SWITCH_ON,EN_DELAYTIME);
	uDelay(1);
	SNR_Clock_Switch(CLOCK_SWITCH_ON);
	uDelay(1);
	
	SetGPIOVal(SENSOR_POWER_DONE_PIN,SENSOR_PIN_LOW);
	uDelay(1);
        SetGPIOVal(SENSOR_POWER_DONE_PIN,SENSOR_PIN_HIGH);
        
        SetGPIOVal(SENSOR_RESET_PIN,SENSOR_PIN_LOW);
	uDelay(1);
	SetGPIOVal(SENSOR_RESET_PIN,SENSOR_PIN_HIGH);
	
	WaitTimeOut_Delay(1);
}

static void isp_hm_2140_power_on()
{
	printf("function: %s \r\n", __FUNCTION__);
	SetGPIOVal(0,1);
	SNR_Clock_Switch(SWITCH_ON);
	SetGPIOVal(0,0);
	Delay(1);
	SensorPowerControl(SWITCH_ON,EN_DELAYTIME);	
	Delay(1);	
	SetGPIOVal(0,1);
	Delay(1);
}

static void isp_imx_307_power_on()
{
	printf("function: %s \r\n", __FUNCTION__);
	SNR_Clock_Switch(SWITCH_OFF);
	SensorPowerControl(SWITCH_OFF,EN_DELAYTIME);
	SetGPIODir(0,1); //aDD
	SetGPIODir(1,1);//ADD
	SensorPowerControl(SWITCH_ON,EN_DELAYTIME);
	uDelay(1);
	SetGPIOVal(0,1);
	SetGPIOVal(1,1);
	SNR_Clock_Switch(SWITCH_ON);
	SetGPIOVal(0,1);
	SetGPIOVal(1,1);
}

static void isp_ov_2740_power_on()
{
	printf("function: %s \r\n", __FUNCTION__);
	SetGPIODir(0,1);
	SetGPIODir(1,1);
	SensorPowerControl(SWITCH_ON,EN_DELAYTIME);
	Delay(1);
	SetGPIOVal(1,1);
	Delay(11);
	SNR_Clock_Switch(SWITCH_ON);
	Delay(2);
	SetGPIOVal(0,1);
}

static void isp_sc_2239_power_on()
{
	printf("function: %s \r\n", __FUNCTION__);
	SetGPIOVal(0,0);
	SetGPIODir(1,1);
	SensorPowerControl(SWITCH_ON,EN_DELAYTIME);
	Delay(5); //t3
	SetGPIOVal(0,1);
	Delay(5); //t4
	SetGPIOVal(1,1);
	Delay(1);//t5
	SNR_Clock_Switch(SWITCH_ON);
}

static void isp_ps_5260_power_on()
{
	printf("function: %s \r\n", __FUNCTION__);
	SNR_Clock_Switch(CLOCK_SWITCH_OFF);
	SetGPIOVal(1,0);
	SensorPowerControl(SWITCH_ON,EN_DELAYTIME);
	usDelay(100);
	SetGPIOVal(0,0);
	usDelay(100);
	SetGPIOVal(0,1);
	usDelay(100);
	SNR_Clock_Switch(SWITCH_ON);
	Delay(1);
}

static void isp_ps_5268_power_on()
{
	printf("function: %s \r\n", __FUNCTION__);
	SetGPIOVal(1,0);
	SensorPowerControl(SWITCH_ON,EN_DELAYTIME);
	usDelay(1);
	SNR_Clock_Switch(SWITCH_ON);
	SetGPIOVal(0,0);
	Delay(5);
	SetGPIOVal(0,1);
	usDelay(100);
}

static void isp_ov_5640_power_on()
{
	printf("function: %s \r\n", __FUNCTION__);
	SetGPIOVal(1,0);
	SensorPowerControl(SWITCH_ON,EN_DELAYTIME);
	usDelay(1);
	SNR_Clock_Switch(SWITCH_ON);
	SetGPIOVal(0,0);
	Delay(100);
	SetGPIOVal(0,1);
	usDelay(100);
}
static int isp_get_sensor_clock(int sensor_id)
{
	int snesor_clock = 0;
	if(sensor_id== SENSOR_OV2735)
	  snesor_clock = ISP_FREQ_24;
	else if(sensor_id ==  SENSOR_SC2232)
	  snesor_clock = ISP_FREQ_27;
	else if(sensor_id ==  SENSOR_HM2140)
	  snesor_clock = ISP_FREQ_24;	
	else if(sensor_id ==  SENSOR_IMX307)
	  snesor_clock = ISP_FREQ_37_125;
	else if(sensor_id ==  SENSOR_SC4236)
	  snesor_clock = ISP_FREQ_27;
	else if(sensor_id ==  SENSOR_GC2053)
	  snesor_clock = ISP_FREQ_27;
	else if(sensor_id ==  SENSOR_OV2740)
	  snesor_clock = ISP_FREQ_24;
	else if(sensor_id ==  SENSOR_GL3004)
	  snesor_clock = ISP_FREQ_24;
	else if(sensor_id ==  SENSOR_JXF37)
	  snesor_clock = ISP_FREQ_24;
	else if(sensor_id ==  SENSOR_SC2232H)
	  snesor_clock = ISP_FREQ_27;
	else if(sensor_id ==  SENSOR_SC2239)
	  snesor_clock = ISP_FREQ_27;
	else if(sensor_id ==  SENSOR_PS5260)
	  snesor_clock = ISP_FREQ_27;
	else if(sensor_id == SENSOR_GC1054)
	  snesor_clock = ISP_FREQ_27;
	else if(sensor_id ==  SENSOR_PS5268)
	  snesor_clock = ISP_FREQ_24;
	else if(sensor_id == SENSOR_PS5270)
	  snesor_clock = ISP_FREQ_27;
	else if(sensor_id ==  SENSOR_OV5640)
	  snesor_clock = ISP_FREQ_24;
	else{
		snesor_clock = -1;
		printf("don't get the sensor id %d\r\n",sensor_id);
	}
	return snesor_clock;
}

static int isp_video_get_clock_pin(int SensorName,int *clock, int *pin){
        *clock = isp_get_sensor_clock(SensorName);
        *pin = ISP_PIN_SEL_S1;//Normal the pin is s1
        if(*clock <0)
          return -1;
        else
          return 0;
}
#endif
//-----------------------------------------------------------------------------
int isp_video_sensor_check(int SensorName){

	
	if(SensorName == SENSOR_SC2232){
		
		unsigned char sendor_id[2];
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE            
                isp_sc_2232_power_on();
#endif
		sendor_id[0] = isp_i2c_read_byte(0x3107);
		sendor_id[1] = isp_i2c_read_byte(0x3108);
		
		if(sendor_id[0] == 0x22 && sendor_id[1] == 0x32){
			return 0;
		}else{
			printf("it is not SC2232!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	}else if(SensorName == SENSOR_OV2735){//check 0v2735 register
		
		unsigned char sendor_id[2];
		//---------------change to page 0---------------- 
		isp_i2c_write_byte(0xfd, 0);
		//---------------end of change to page 0---------------- 
		sendor_id[0] = 	isp_i2c_read_byte(0x02);
		sendor_id[1] = 	isp_i2c_read_byte(0x03);
		
		if(sendor_id[0]== 0x27 && sendor_id[1]== 0x35 ){
			return 0;
		}else{
			printf("it is not OV2735!,please check sensor.h and isp.bin\n\r");
			return -1;
		}
	}else if(SensorName == SENSOR_HM2140){//check HM2140 register
		
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE               
	isp_hm_2140_power_on();
#endif
		unsigned char sendor_id[2];

		sendor_id[0] = 	isp_i2c_read_byte(0x0000);
		sendor_id[1] = 	isp_i2c_read_byte(0x0001);
		
		if(sendor_id[0]== 0x21 && sendor_id[1]== 0x40 ){
			return 0;
		}else{
			printf("%x %x, it is not HM2410!,please check sensor.h and isp.bin\n\r", sendor_id[0], sendor_id[1]);
			return -1;
		}
	}else if (SensorName == SENSOR_IMX307){
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE                 
	isp_imx_307_power_on();
#endif	
		unsigned char sendor_id[2];
		
		//sendor_id[0] = 	isp_i2c_read_byte(0x309E);
		//sendor_id[1] = 	isp_i2c_read_byte(0x309F);
		sendor_id[0] = 	isp_i2c_read_byte(0x3004);
		sendor_id[1] = 	isp_i2c_read_byte(0x3008);
		printf("sendor_id[0]=0x%x, sendor_id[1]=0x%x\n\r", sendor_id[0], sendor_id[1]);
		if(sendor_id[0]== 0x10 && sendor_id[1]== 0xA0 ){
			return 0;
		}else{
			return -1;
		}		
	
		
	}else if(SensorName == SENSOR_SC4236){
		
		unsigned char sendor_id[2];

		sendor_id[0] = isp_i2c_read_byte(0x3107);
		sendor_id[1] = isp_i2c_read_byte(0x3108);
		
		if(sendor_id[0] == 0x32 && sendor_id[1] == 0x35){
			return 0;
		}else{
			printf("it is not SC4236!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	
	
	}else if(SensorName == SENSOR_GC2053){
		
		unsigned char sendor_id[2];
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE
                isp_gc_2053_power_on();
#endif

		sendor_id[0] = isp_i2c_read_byte(0xF0);
		sendor_id[1] = isp_i2c_read_byte(0xF1);
		
		if(sendor_id[0] == 0x20 && sendor_id[1] == 0x53){
			return 0;
		}else{
			printf("it is not GC2053!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	
	
	}else if(SensorName == SENSOR_OV2740){
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE 
                isp_ov_2740_power_on();
#endif
		unsigned char sendor_id[2];

		sendor_id[0] = isp_i2c_read_byte(0x300B);
		sendor_id[1] = isp_i2c_read_byte(0x300C);
		
		if(sendor_id[0] == 0x27 && sendor_id[1] == 0x40){
			return 0;
		}else{
			printf("it is not OV2740!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	
	
	}else if(SensorName == SENSOR_JXF37){
		
		unsigned char sendor_id[2];
                
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE
                isp_jxf_37_power_on();
#endif

		sendor_id[0] = 	isp_i2c_read_byte(0x0A);
		sendor_id[1] = 	isp_i2c_read_byte(0x0B);
		if(sendor_id[0] == 0x0F && sendor_id[1] == 0x37){
			return 0;
		}else{
			printf("it is not JXF37!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	

	}else if(SensorName == SENSOR_SC2232H){
		
		unsigned char sendor_id[2];

		sendor_id[0] = isp_i2c_read_byte(0x3107);
		sendor_id[1] = isp_i2c_read_byte(0x3108);
		if(sendor_id[0] == 0xCB && sendor_id[1] == 0x07){
			return 0;
		}else{
			printf("it is not SC2232H!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}

	}
	else if(SensorName == SENSOR_GL3004){
		unsigned char sendor_id[2];

		sendor_id[0] = isp_i2c_read_byte(0x0A50);
		sendor_id[1] = isp_i2c_read_byte(0x0A51);
		if(sendor_id[0] == 0x30 && sendor_id[1] == 0x04){
			printf("Sensor ID Check : Sensor is GL3004!\n\r");
			return 0;
		}else{
			printf("it is not GL3004!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	}
	else if(SensorName == SENSOR_SC2239){
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE
	isp_sc_2239_power_on();
#endif		
		
		unsigned char sendor_id[2];

		sendor_id[0] = isp_i2c_read_byte(0x3107);
		sendor_id[1] = isp_i2c_read_byte(0x3108);
		if(sendor_id[0] == 0xCB && sendor_id[1] == 0x10){
			return 0;
		}else{
			printf("it is not SC2239!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	}
	else if(SensorName == SENSOR_PS5260){
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE
	isp_ps_5260_power_on();
#endif
		unsigned char sendor_id[2];
		isp_i2c_write_byte(0xef, 0x00);
		sendor_id[0] = isp_i2c_read_byte(0x00);
		sendor_id[1] = isp_i2c_read_byte(0x01);
		printf("sendor_id[0]=0x%x, sendor_id[1]=0x%x\n\r", sendor_id[0], sendor_id[1]);
		if(sendor_id[0] == 0x52 && sendor_id[1] == 0x60){
			return 0;
		}else{
			printf("it is not PS5260!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	}
	else if(SensorName == SENSOR_GC1054){
		
		unsigned char sendor_id[2];
                
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE
                isp_gc_1054_power_on();
#endif

		sendor_id[0] = isp_i2c_read_byte(0xF0);
		sendor_id[1] = isp_i2c_read_byte(0xF1);
		printf("sendor_id[0]=0x%x, sendor_id[1]=0x%x\n\r", sendor_id[0], sendor_id[1]);
		
		if(sendor_id[0] == 0x10 && sendor_id[1] == 0x54){
			return 0;
		}else{
			printf("it is not GC1054!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	
	
	}
	else if(SensorName == SENSOR_PS5268){
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE
	isp_ps_5268_power_on();
#endif
		unsigned char sendor_id[2];
		sendor_id[0] = isp_i2c_read_byte(0x0100);
		sendor_id[1] = isp_i2c_read_byte(0x0101);
		if(sendor_id[0] == 0x52 && sendor_id[1] == 0x68){
			printf("[PS5268] sendor_id[0]=0x%x, sendor_id[1]=0x%x\n\r", sendor_id[0], sendor_id[1]);
			return 0;
		}else{
			printf("it is not PS5268!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	}
	else if(SensorName == SENSOR_PS5270){
		unsigned char sendor_id[2];
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE
                isp_ps_5270_power_on();
#endif
		isp_i2c_write_byte(0xef, 0x00);
		sendor_id[0] = isp_i2c_read_byte(0x00);
		sendor_id[1] = isp_i2c_read_byte(0x01);
		printf("sendor_id[0]=0x%x, sendor_id[1]=0x%x\n\r", sendor_id[0], sendor_id[1]);
		if(sendor_id[0] == 0x52 && sendor_id[1] == 0x70){
			return 0;
		}else{
			printf("it is not PS5270!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	}
	else if(SensorName == SENSOR_OV5640){
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE
	isp_ov_5640_power_on();
#endif
		unsigned char sendor_id[2];
		sendor_id[0] = isp_i2c_read_byte(0x300A);
		sendor_id[1] = isp_i2c_read_byte(0x300B);
		printf("sendor_id[0]=0x%x, sendor_id[1]=0x%x\n\r", sendor_id[0], sendor_id[1]);
		if(sendor_id[0] == 0x56 && sendor_id[1] == 0x40){
			return 0;
		}else{
			printf("it is not OV5640!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	}
	else{
		printf("Unknown sensor\n\r");
		return -1;
	}          
}

int isp_control(void *p, int cmd, int arg)
{
    isp_ctx_t* ctx = (isp_ctx_t*)p;    
    isp_cfg_t cfg;
    mm_context_t *mctx = (mm_context_t*)ctx->parent;
    mm_queue_item_t* tmp_item;
	int temp;

    switch(cmd){
    case CMD_ISP_SET_PARAMS:
        memcpy(&ctx->params, (void*)arg, sizeof(isp_params_t));
        break;
    case CMD_ISP_GET_PARAMS:
        memcpy((void*)arg, &ctx->params, sizeof(isp_params_t));
        break;		
	case CMD_ISP_STREAMID:
		ctx->params.stream_id = arg;
		break;
	case CMD_ISP_HW_SLOT:
		ctx->params.slot_num = arg;
		break;
	case CMD_ISP_SW_SLOT:
		ctx->params.buff_num = arg;
		break;
	case CMD_ISP_FPS:
		ctx->params.fps = arg;
		break;
	case CMD_ISP_WIDTH:
		ctx->params.width = arg;
		break;
	case CMD_ISP_HEIGHT:
		ctx->params.height = arg;
		break;
	case CMD_ISP_FORMAT:
		ctx->params.format = arg;
        case CMD_ISP_SET_SELF_BUF:
                ctx->params.self_buf_addr[ctx->params.self_buf_count] = arg;
                ctx->params.self_buf_count++;
		break;
        case CMD_ISP_SET_BOOT_MODE:
                ctx->params.boot_mode = arg;
                break;
	case CMD_ISP_DUMP_STATE:
		rt_printf("drop frame %d, drop frame total %d\n\r", ctx->state.drop_frame, ctx->state.drop_frame_total);
		rt_printf("isp  frame %d, isp  frame total %d\n\r", ctx->state.isp_frame , ctx->state.isp_frame_total );
		break;
	case CMD_ISP_STREAM_START:
		// config hw slot, get resource from module queue
	        if(isp_stream_get_status(ctx->stream->cfg.isp_id) == 1)	// 1: stream on
			return 0;
		for(int i = 0; i < ctx->params.slot_num; i++){
			if(xQueueReceive(mctx->output_recycle, (void*)&tmp_item, 10) == pdTRUE){
				isp_buf_t buf;
				buf.slot_id = i;
				buf.y_addr = tmp_item->data_addr;
				buf.uv_addr = tmp_item->data_addr + ctx->params.width*ctx->params.height;
				if(ctx->params.boot_mode == ISP_NORMAL_BOOT)
                                    isp_handle_buffer(ctx->stream, &buf, MODE_SETUP);
				ctx->hw_slot_item[i] = tmp_item;
			}
		}		
		isp_stream_start(ctx->stream);
		break;
	case CMD_ISP_STREAM_STOP:
	        if(isp_stream_get_status(ctx->stream->cfg.isp_id) == 0)	// 0: stream off
			return 0;
		isp_stream_stop(ctx->stream);
		// release hw slot item
		for(int i = 0; i < ctx->params.slot_num; i++){
			if(ctx->hw_slot_item[i]){
				//rt_printf("hw slot %x data %x\n\r", ctx->hw_slot_item[i], ctx->hw_slot_item[i]->data_addr);
				xQueueSend(mctx->output_recycle, (void*)&ctx->hw_slot_item[i], 10);
			}
		}			
		break;
	case CMD_ISP_UPDATE:
		if(isp_stream_get_status(arg) == 1)	// 1: stream on
			return -1;
		
		if(!ctx->buf_width || !ctx->buf_height){
			rt_printf("buffer not created, cannot update setting\n\r");
			return -1;
		}
		if((ctx->params.width > ctx->buf_width) || (ctx->params.height > ctx->buf_height)){
			rt_printf("new resolution %dx%d is larger than buffer configuration %dx%d\n\r", ctx->params.width, ctx->params.height, ctx->buf_width, ctx->buf_height);
			return -1;
		}
                temp = arg;
		arg = ctx->params.stream_id;	// use old stream id
		ctx->stream = isp_stream_destroy(ctx->stream);
                arg = temp;
        case CMD_ISP_APPLY:
		if(isp_stream_get_status(arg) == 1)	// 1: stream on
			return 0;

		ctx->params.stream_id = arg;

		cfg.isp_id = arg;
		cfg.format = ctx->params.format;
		cfg.width = ctx->params.width;
		cfg.height = ctx->params.height;
		cfg.fps = ctx->params.fps;
		cfg.bayer_type = ctx->params.bayer_type;
		cfg.hw_slot_num = ctx->params.slot_num;
    cfg.boot_mode = ctx->params.boot_mode;
		
		ctx->stream = isp_stream_create(&cfg);
		if(!ctx->stream){
			mctx->state = MM_STAT_ERROR;
			return -1;
		}
		
		isp_stream_set_complete_callback(ctx->stream, isp_frame_complete_cb, (void*)ctx);
		
		// config hw slot, get resource from module queue
		for(int i = 0; i < ctx->params.slot_num; i++){
			if(xQueueReceive(mctx->output_recycle, (void*)&tmp_item, 0) == pdTRUE){
				isp_buf_t buf;
				buf.slot_id = i;
				buf.y_addr = tmp_item->data_addr;
				buf.uv_addr = tmp_item->data_addr + ctx->params.width*ctx->params.height;
				if(ctx->params.boot_mode == ISP_NORMAL_BOOT)
                                    isp_handle_buffer(ctx->stream, &buf, MODE_SETUP);
				ctx->hw_slot_item[i] = tmp_item;
				//rt_printf("setup hw slot %x\n\r", tmp_item->data_addr);
			}else{
				// error case
				mctx->state = MM_STAT_ERROR;
				return -1;
			}
		}		
		
		isp_stream_apply(ctx->stream);
		isp_stream_start(ctx->stream);
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_DISABLE
#if SENSOR_USE == SENSOR_ALL
                int ret = isp_video_sensor_check(SENSOR_DEFAULT);
#else
		int ret = isp_video_sensor_check(SENSOR_USE);
#endif

		if (ret == -1){
			rt_printf("use the wrong sensor in sensor.h define SENSOR_USE!\n\r");
			while(1);
		}
#endif
                break;
    }
    return 0;
}

int isp_handle(void* ctx, void* input, void* output)
{
    return 0;
}

void* isp_destroy(void* p)
{
    isp_ctx_t* ctx = (isp_ctx_t*)p;

    if(ctx && ctx->stream)    ctx->stream=isp_stream_destroy(ctx->stream);

    free(ctx);
    return NULL;
}

#ifndef ISP_FW_LOCATION
#define ISP_FW_LOCATION 0x601000
#endif

#define ISP_USER_LOCATION 0x700000

int isp_get_id(void)
{
	flash_t flash;
	unsigned char type[4] = {0};
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_stream_read(&flash, ISP_FW_LOCATION, sizeof(type), (uint8_t *) type);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
	//printf("ISP %c %c %c %x %x %x\r\n",type[0],type[1],type[2],type[0],type[1],type[2]);
	if(type[0] == 'I' && type[1] == 'S' && type[2] == 'P'){
		return type[3];
	}else{
		return 0xff;
	}
}

int isp_set_sensor(int sensor_id)
{
	flash_t flash;
	int value = 0;
	unsigned char status[4] = {0};
	value = isp_get_id();
	status[0]='I';status[1]='S';status[2]='P';status[3]=sensor_id;
	
	if(value != sensor_id){
		device_mutex_lock(RT_DEV_LOCK_FLASH);
		flash_erase_sector(&flash, ISP_FW_LOCATION);
		flash_stream_write(&flash, ISP_FW_LOCATION, sizeof(status), (uint8_t *) status);
		device_mutex_unlock(RT_DEV_LOCK_FLASH);
                printf("Store the sensor id %d %d\r\n",value,sensor_id);
	}else{
                printf("The sensor id is the same\r\n");
        }
	return 0;
}

int isp_user_callback(void *parm)
{
    //isp_set_flip(3);
	return 0;
}

void* isp_create(void* parent)
{
    int ret;
    isp_init_cfg_t isp_init_cfg;
    isp_ctx_t *ctx = malloc(sizeof(isp_ctx_t));
    if(!ctx) return NULL;
    memset(ctx, 0, sizeof(isp_ctx_t));

    ctx->parent = parent;

    memset(&isp_init_cfg, 0, sizeof(isp_init_cfg));
    isp_init_cfg.pin_idx = ISP_PIN_IDX;
    isp_init_cfg.clk = SENSOR_CLK_USE;
    isp_init_cfg.ldc = LDC_STATE;
    isp_init_cfg.fps = SENSOR_FPS;
    isp_init_cfg.isp_fw_location = ISP_FW_LOCATION;
    isp_init_cfg.isp_fw_space = ISP_FW_SPACE;
    isp_init_cfg.user_isp_callback = isp_user_callback;
#if ISP_FW_SPACE == ISP_FW_USERSPACE
    isp_init_cfg.isp_user_space_addr = SENSOR_FW_USER_ADDR;
    isp_init_cfg.isp_user_space_size = SENSOR_FW_USER_SIZE;
#endif
    
#if SENSOR_USE == SENSOR_ALL
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE
    isp_init_cfg.check_sensor_id = isp_video_sensor_check;
    isp_init_cfg.get_sensor_clock_pin = isp_video_get_clock_pin;
    isp_init_cfg.isp_sensor_auto_sel_flag = SENSOR_AUTO_SEL;
    memcpy(isp_init_cfg.sensor_table,sen_id,sizeof(isp_init_cfg.sensor_table));
    isp_init_cfg.isp_multi_sensor = SENSOR_DEFAULT;
    int temp = 0;
    for(int i = 0;i<sizeof(isp_init_cfg.sensor_table);i++){//It will pick the sensor default as the first selection item.
      if(isp_init_cfg.sensor_table[i] == isp_init_cfg.isp_multi_sensor && isp_init_cfg.sensor_table[i] != 0xff){
        temp = isp_init_cfg.sensor_table[0];
        isp_init_cfg.sensor_table[0] = isp_init_cfg.sensor_table[i];
        isp_init_cfg.sensor_table[i] = temp;
      }
    }
#else
    isp_init_cfg.isp_multi_sensor = SENSOR_DEFAULT;
#endif
#endif
    isp_init_cfg.isp_InitExposureTime = InitExposureTimeAtNormalMode;
    ret = video_subsys_init(&isp_init_cfg);
#if SENSOR_AUTO_SEL == ISP_AUTO_SEL_ENABLE
    if(ret < 0){
      printf("can't get the correct id\r\n");
    }else{
      printf("The sensor is %d clock = %d\r\n",isp_init_cfg.isp_multi_sensor,isp_init_cfg.clk);
    }
    //isp_set_sensor(isp_init_cfg.isp_multi_sensor); //Please stored the sensor id at the last, ot it will affluence the isp.
#endif
    if(ret < 0)
        goto isp_create_fail;

    return ctx;

isp_create_fail:

    if(ctx) free(ctx);
    return NULL;
}

void* isp_new_item(void *p)
{
    isp_ctx_t* ctx = (isp_ctx_t*)p;
    // get parameter 
    isp_params_t* param = &ctx->params;
    // malloc a correct sized memroy
    //mm_printf("new item\n\r");
    ctx->buf_width = param->width;
    ctx->buf_height = param->height;
    static int isp_count = 0;
    unsigned char *ptr = NULL;
    if(ctx->params.self_buf_count){
          ptr = (unsigned char *)ctx->params.self_buf_addr[isp_count];
          isp_count++;
          ctx->params.self_buf_count--;
          if(ctx->params.self_buf_count == 0)
              isp_count = 0;
          return ptr;
    }
    if(param->format == ISP_FORMAT_BAYER_PATTERN || param->format == ISP_FORMAT_YUV422_SEMIPLANAR)
        return malloc((param->width+8)*(param->height+8)*2);
    else
        return malloc((param->width+8)*(param->height+8)*3/2);
    //return malloc(param->width*param->height*3/2);
}

void* isp_del_item(void *p, void *d)
{
    if(d) free(d);
    return NULL;
}

mm_module_t isp_module = {
    .create = isp_create,
    .destroy = isp_destroy,
    .control = isp_control,
    .handle = isp_handle,

    .new_item = isp_new_item,
    .del_item = isp_del_item,
    .rsz_item = NULL,

    .output_type = MM_TYPE_VDSP,    // output for video algorithm
    .module_type = MM_TYPE_VSRC,    // module type is video source
    .name = "ISP"
};