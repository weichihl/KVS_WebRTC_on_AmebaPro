#include <stdlib.h>
#include "diag.h"
#include "isp_boot.h"
#include "platform_opts.h"
#include "sensor.h"
#include "isp_api.h"
#if ISP_BOOT_MODE_ENABLE
extern isp_boot_stream_t isp_boot_stream;

#if ISP_BOOT_MODE_ENABLE

#define hal_delay_ms(time_ms) do {hal_delay_us((time_ms)*1000);} while (0)

void SNR_Clock_Switch(int on)
{
        unsigned char value = on;
        isp_boot_set_memory(&value,SENSOR_CLOCK_SWITCH_REG,1);
        hal_delay_ms(10);
}
void SetGPIOVal(int pin_num,int output)
{
	isp_boot_set_gpio_dir(pin_num,SENSOR_GPIO_OUTPUT);
	isp_boot_set_gpio_value(pin_num,output);
}

void SensorPowerControl(int on,int delayms)
{
	isp_boot_set_gpio_dir(SENSOR_POWER_ENABLE_PIN,SENSOR_GPIO_OUTPUT);
	isp_boot_set_gpio_value(SENSOR_POWER_ENABLE_PIN,on);
        hal_delay_ms(delayms);
}

void SetGPIODir(int pin_num,int dir)
{
	isp_boot_set_gpio_dir(pin_num,dir);
}

void Delay(int ms)
{
        hal_delay_ms(ms);
}
void uDelay(int u)
{
        hal_delay_us(u);
}

void usDelay(int u)
{
        hal_delay_us(u);
}

void WaitTimeOut_Delay(int ms)
{
        hal_delay_ms(ms);
}
void isp_jxf_37_power_on()
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

void isp_gc_2053_power_on()
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

void isp_sc_2232_power_on()
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

int isp_get_sensor_clock(int sensor_id)
{
	int snesor_clock = 0;

	if(sensor_id ==  SENSOR_SC2232)
	  snesor_clock = ISP_FREQ_27;
	else if(sensor_id ==  SENSOR_GC2053)
	  snesor_clock = ISP_FREQ_27;
	else if(sensor_id ==  SENSOR_JXF37)
	  snesor_clock = ISP_FREQ_24;
	else{
		snesor_clock = -1;
		rt_printf("don't get the sensor id %d\r\n",sensor_id);
	}
	return snesor_clock;
}

int isp_boot_video_get_clock_pin(int SensorName,int *clock, int *pin){
        *clock = isp_get_sensor_clock(SensorName);
        *pin = ISP_PIN_SEL_S1;//Normal the pin is s1
        if(*clock <0)
          return -1;
        else
          return 0;
}

int isp_boot_video_sensor_check(int SensorName){

	//rt_printf("isp_boot_video_sensor_check\r\n");
	if(SensorName == SENSOR_SC2232){
		
		unsigned char sendor_id[2];
#if ISP_AUTO_SEL_ENABLE
                isp_sc_2232_power_on();
#endif
		sendor_id[0] = isp_boot_i2c_read_byte(0x3107);
		sendor_id[1] = isp_boot_i2c_read_byte(0x3108);
		
		if(sendor_id[0] == 0x22 || sendor_id[1] == 0x32){
			return 0;
		}else{
			rt_printf("it is not SC2232!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	}else if(SensorName == SENSOR_GC2053){
		
		unsigned char sendor_id[2];
#if ISP_AUTO_SEL_ENABLE
                isp_gc_2053_power_on();
#endif

		sendor_id[0] = isp_boot_i2c_read_byte(0xF0);
		sendor_id[1] = isp_boot_i2c_read_byte(0xF1);
		
		if(sendor_id[0] == 0x20 || sendor_id[1] == 0x53){
			return 0;
		}else{
			rt_printf("it is not GC2053!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	
	
	}else if(SensorName == SENSOR_JXF37){
		
		unsigned char sendor_id[2];
                
#if ISP_AUTO_SEL_ENABLE
                isp_jxf_37_power_on();
#endif

		sendor_id[0] = 	isp_boot_i2c_read_byte(0x0A);
		sendor_id[1] = 	isp_boot_i2c_read_byte(0x0B);
		if(sendor_id[0] == 0x0F || sendor_id[1] == 0x37){
			return 0;
		}else{
			rt_printf("it is not JXF37!,please check sensor.h and isp.bin!\n\r");
			return -1;
		}
	

	}
	else{
		rt_printf("Unknown sensor\n\r");
		return -1;
	}          
}

#endif

#define ISP_FW_LOCATION 0x601000
#define FLASH_BASE_ADDRESS 0x98000000
unsigned char sen_boot_id[0x08]={SENSOR_SC2232,SENSOR_JXF37,SENSOR_GC2053,SENSOR_ALL};

int user_setup_isp(void *parm)
{
  isp_boot_set_flip_mode(3);//You can setup the isp operation at here.
}

void user_boot_config_init(void *parm)
{
      if(isp_boot_stream.isp_sensor_auto_sel_flag){
          isp_boot_stream.check_sensor_id = isp_boot_video_sensor_check;
          isp_boot_stream.get_sensor_clock_pin = isp_boot_video_get_clock_pin;
          isp_boot_stream.isp_multi_sensor = SENSOR_DEFAULT;
          int temp = 0;
          unsigned char isp[4]={0};
          
          memcpy(isp,FLASH_BASE_ADDRESS+ISP_FW_LOCATION,sizeof(isp));
          memcpy(isp_boot_stream.sensor_table,sen_boot_id,sizeof(isp_boot_stream.sensor_table));
          //dbg_printf("ISP:%c %c %c %d\r\n",isp[0],isp[1],isp[2],isp[3]);
          if(isp[0] == 'I'&& isp[1] == 'S' && isp[2] == 'P'){
            isp_boot_stream.isp_multi_sensor = isp[3];
          }else{
            isp_boot_stream.isp_multi_sensor = SENSOR_DEFAULT;
          }
          //Sort the priority to the first for isp_nulti_sensor
          for(int i = 0;i<sizeof(isp_boot_stream.sensor_table);i++){//It will pick the sensor default as the first selection item.
            if(isp_boot_stream.sensor_table[i] == isp_boot_stream.isp_multi_sensor && isp_boot_stream.sensor_table[i] != 0xff){
              temp = isp_boot_stream.sensor_table[0];
              isp_boot_stream.sensor_table[0] = isp_boot_stream.sensor_table[i];
              isp_boot_stream.sensor_table[i] = temp;
            }
          }
          
          isp_boot_stream.user_isp_callback = user_setup_isp;
      }
}
#endif