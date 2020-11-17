#include <stdio.h>
#include "log_service.h"
#include "platform_opts.h"
#include "cmsis_os.h"
#include <platform/platform_stdlib.h>

#include "freertos_service.h"
#include "osdep_service.h"

#include <stdio.h>
#include <stdlib.h>
#include <rtsisp.h>
#include "rtsosd_cmd.h"
#include "isp_cmd.h"
#include "module_uvcd.h"
#include "isp_api.h"
#include "uvc/inc/usbd_uvc_desc.h"
#include "isp_font.h"
#include "sensor_service.h"

extern struct uvc_format *uvc_format_ptr;

#if CONFIG_EXAMPLE_MEDIA_UVCD
extern struct uvc_dev gUVC_DEVICE;
#endif

void isp_set_flip(int a_dValue);
void isp_get_flip(int *a_pdValue);
void isp_set_brightness(int a_dValue);
void isp_get_brightness(int *a_pdValue);
void isp_set_contrast(int a_dValue);
void isp_get_contrast(int *a_pdValue);
void isp_set_saturation(int a_dValue);
void isp_get_saturation(int *a_pdValue);
void isp_set_sharpness(int a_dValue);
void isp_get_sharpness(int *a_pdValue);
void isp_get_AE_gain(int *a_pdValueAnalogGain, int *a_pdValueDigitalGain, int *a_pdValueISPDigitalGain);

unsigned int isp_str_to_value(const unsigned char *str){
	if(str[0]=='0'&&(str[1]=='x' || str[1]=='X'))
		return strtol((char const*)str,NULL,16);
	else
		return atoi((char const*)str);
}

void fATIS(void *arg)
{
	static int count = 0;
	isp_set_flip(count);
	count++;
	count%=4;
}


void fATI0(void *arg)
{
	//int argc;
	//char *argv[MAX_ARGC] = {0};
	printf("[ATI0]:TODO\n\r");
}

void fATI1(void *arg)
{
	int argc;
	volatile int error_no=0;
	char *argv[MAX_ARGC] = {0};
	int i = 0;
	
	struct isp_cmd_data rcmd;
	memset(&rcmd,0,sizeof(struct isp_cmd_data));
	rcmd.buf = malloc(32);
	
	if(!arg){
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
			"\r\n[ATPW] Usage : ATPW=<mode>");
		error_no = 1;
		goto EXIT;
	}
	
	argc = parse_param(arg, argv);
	if(argc < 7){
		//at_printf("\r\n[ATPW] ERROR : command format error");
		printf("argc = %d\r\n",argc);
		error_no = 1;
		goto EXIT;
	}
	
	rcmd.cmdcode = (isp_str_to_value((unsigned char const*)argv[1])<<8)|isp_str_to_value((unsigned char const*)argv[2]);
	rcmd.index = isp_str_to_value((unsigned char const*)argv[3]);
	rcmd.length = isp_str_to_value((unsigned char const*)argv[4]);
	rcmd.param = isp_str_to_value((unsigned char const*)argv[5]);
	rcmd.addr = isp_str_to_value((unsigned char const*)argv[6]);
	
	if((rcmd.cmdcode&0x80) == 0x00){
		printf("send data len = %d\r\n",rcmd.length);
		for(i=0;i<rcmd.length;i++){
			rcmd.buf[i] = (uint8_t)isp_str_to_value((unsigned char const*)argv[7+i]);
			printf("buf[%d] = 0x%02x\r\n",i,rcmd.buf[i]);
		}
	}
	
	isp_send_cmd(&rcmd);
	
	if(rcmd.cmdcode&0x80){//For read data
		printf("read data len = %d\r\n",rcmd.length);
		for(i=0;i<rcmd.length;i++)
			printf("buf[%d] = 0x%02x\r\n",i,rcmd.buf[i]);
	}
	
	free(rcmd.buf);
	
	return;
EXIT:
	printf("error at command format\r\n");
}
extern void isp_get_sensor_fps(int *a_pdValue);
void fATIQ(void *arg)
{
	volatile int argc;
	volatile int error_no = 0;
	char *argv[MAX_ARGC] = {0};
	int dValue2, dValue = 0;
	int dValueAnalogGain, dValueDigitalGain, dValueISPDigitalGain;
	float fAECGain = 0;
	int dIndex = 0;
	int dWrite = 0;
	int i = 0;
	
	if(!arg){
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
			"\r\n[ATPW] Usage : ATPW=<mode>");
		error_no = 1;
		goto EXIT;
	}
	
	argc = parse_param(arg, argv);
	dIndex = isp_str_to_value((unsigned char const*)argv[1]);
	dWrite = isp_str_to_value((unsigned char const*)argv[2]);
	
	if(dWrite)
	{
		dValue = isp_str_to_value((unsigned char const*)argv[3]);
		if(dIndex==0)
			isp_set_flip(dValue);
		else if(dIndex==1)
			isp_set_brightness(dValue);
		else if(dIndex==2)
			isp_set_saturation(dValue);
		else if(dIndex==3)
			isp_set_sharpness(dValue);
		else if(dIndex==4)
			isp_set_contrast(dValue);
#if CONFIG_EXAMPLE_MEDIA_UVCD
		else if(dIndex==5)
		{
			if(dValue==0)
			{
				uvc_format_ptr->isp_format = ISP_FORMAT_BAYER_PATTERN;
				gUVC_DEVICE.change_parm_cb(uvc_format_ptr);
				printf("ToBayer\r\n");
			}
			else if(dValue==1)
			{
				uvc_format_ptr->isp_format = ISP_FORMAT_YUV422_SEMIPLANAR;
				gUVC_DEVICE.change_parm_cb(uvc_format_ptr);
				printf("ToISPIMG\r\n");
			}
		}
		else if(dIndex==6)
		{
			if(dValue>=0 && dValue<=1)
			{
				uvc_format_ptr->ldc = dValue;
				gUVC_DEVICE.change_parm_cb(uvc_format_ptr);
			}

			printf("LDC: %d\r\n", dValue);
		}
#endif
	}
	else
	{
		if(dIndex==0)
		{
			isp_get_flip(&dValue);
			printf("Flip: %d\r\n", dValue);
		}
		else if(dIndex==1)
		{
			isp_get_brightness(&dValue);
			printf("Brightness: %d\r\n", dValue);
		}
		else if(dIndex==2)
		{
			isp_get_saturation(&dValue);
			printf("Saturation: %d\r\n", dValue);
		}
		else if(dIndex==3)
		{
			isp_get_sharpness(&dValue);
			printf("Sharpness: %d\r\n", dValue);
		}
		else if(dIndex==4)
		{
			isp_get_contrast(&dValue);
			printf("Contrast: %d\r\n", dValue);
		}
		else if(dIndex==7)
		{
			isp_get_AE_gain(&dValueAnalogGain, &dValueDigitalGain, &dValueISPDigitalGain);
			fAECGain = ((float)dValueAnalogGain/256)*((float)dValueDigitalGain/256)*((float)dValueISPDigitalGain/256);
			printf("AEC Gain: %.6f\r\n", fAECGain);
		}
		else if(dIndex==9)
		{
			struct isp_cmd_data rcmd;
			unsigned char acBuf[32];
			float starttime = 0;
			float startframe = 0;
			float endtime = 0;
			float endframe = 0;
			float fexp, diftime, difframe;
			int iexp;
			int iFrameCntPre;
			int iOverflowCnt = 0;
			int iFPS=0;
			
			dValue = isp_str_to_value((unsigned char const*)argv[3]);
			if(dValue==0)
			{
				memset(&rcmd,0,sizeof(struct isp_cmd_data));
				rcmd.buf = acBuf;

				rcmd.cmdcode = 0x81;
				rcmd.index = 0;
				rcmd.length = 1;
				rcmd.param = 0;
				rcmd.addr = 0x8037;
		
				isp_send_cmd(&rcmd);
				starttime = xTaskGetTickCountFromISR();
				startframe = acBuf[0];
				iFrameCntPre = startframe;
				printf("Estimating fps, wait for senconds...\r\n");
				for(i=0; i<120; i++)
				{
					//isp_get_exposure_time(&iexp);
					//fexp = iexp/1000;
					isp_send_cmd(&rcmd);
					if(acBuf[0]<iFrameCntPre)
						iOverflowCnt++;
					//printf("exp: %.2f(ms)  count-time: %3d-%d\r\n", fexp, acBuf[0], xTaskGetTickCountFromISR());
					vTaskDelay(100);
					iFrameCntPre = acBuf[0];
					if(i%10==0)
						printf(".\r\n");
				}
				isp_send_cmd(&rcmd);
				printf("Done.\r\n");
				endtime = xTaskGetTickCountFromISR();
				endframe = acBuf[0];
				diftime = endtime-starttime;
				difframe = endframe-startframe+256*iOverflowCnt;
				printf("FPS: %.3f\r\n", 1000*(difframe)/diftime);
			}
			else if(dValue==1)
			{
				isp_get_sensor_fps(&iFPS);
				printf("FPS: %d\r\n", iFPS);
			}

		}
	}
	
	return;
EXIT:
	printf("error at command format\r\n");
}
#include "device.h"
#include "gpio_api.h"   // mbed
#include "ambient_light_sensor.h"
void fATIR(void *arg)
{
	volatile int argc, error_no = 0;
	char *argv[MAX_ARGC] = {0};
	
	struct isp_cmd_data rcmd;
	memset(&rcmd,0,sizeof(struct isp_cmd_data));
	rcmd.buf = malloc(32);
	
	if(!arg){
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
			"\r\n[ATPW] Usage : ATPW=<mode>");
		error_no = 1;
		goto EXIT;
	}

	argc = parse_param(arg, argv);
	int mode = isp_str_to_value((unsigned char*)argv[1]);
	int dValue1 = isp_str_to_value((unsigned char*)argv[2]);
	float fBright = (float)dValue1/100.0f;

	
	// Init LED control pin
	if(mode==1)
	{
		ir_cut_enable(0);
		vTaskDelay(1000);
		ir_cut_enable(1);
		printf("IR Cut On\r\n");
	}
	else if(mode==0)
	{
		ir_cut_enable(1);
		vTaskDelay(1000);
		ir_cut_enable(0);
		printf("IR Cut Off\r\n");
	}
	else if(mode==2)
	{
#if CONFIG_LIGHT_SENSOR
		int lux = ambient_light_sensor_get_lux(0);
		printf("light_sensor: %d \r\n", lux);
#else
		//printf("[LIGHT_SENSOR] Option is not enabled.\r\n", lux);
#endif
	}
	else if(mode==3)
	{
#if CONFIG_LIGHT_SENSOR
		if(dValue1 > 100)
			dValue1 = 100;
		if(dValue1 < 0)
			dValue1 = 0;
		
		float fBright = (float)dValue1/100.0f;
		ir_ctrl_set_brightness(fBright);
		printf("led_brightness: %f \r\n", fBright);
#else
		//printf("[LIGHT_SENSOR] Option is not enabled.\r\n", lux);
#endif
	}
	
	
	return;
EXIT:
	printf("error at command format\r\n");
}

void fATIN(void *arg)
{
#if CONFIG_EXAMPLE_MEDIA_UVCD
	volatile int argc, error_no = 0;
	int dNextDate, dFormat, dYear, dMonth, dDay;
	char *argv[MAX_ARGC] = {0};
	
	struct isp_cmd_data rcmd;
	memset(&rcmd,0,sizeof(struct isp_cmd_data));
	rcmd.buf = malloc(32);
	
	if(!arg){
		AT_DBG_MSG(AT_FLAG_WIFI, AT_DBG_ERROR,
			"\r\n[ATPW] Usage : ATPW=<mode>");
		error_no = 1;
		goto EXIT;
	}

	argc = parse_param(arg, argv);

	dNextDate = isp_str_to_value((unsigned char*)argv[1]);
	dFormat   = isp_str_to_value((unsigned char*)argv[2]);
	dYear     = isp_str_to_value((unsigned char*)argv[3]);
	dMonth    = isp_str_to_value((unsigned char*)argv[4]);
	dDay      = isp_str_to_value((unsigned char*)argv[5]);
	
	rts_write_isp_osd_date(dNextDate, dFormat, dYear, dMonth, dDay);
	
	
	return;
EXIT:
	printf("error at command format\r\n");
#endif
}


void fATIH(void *arg){
	printf("ATI0:DBG\r\n");
	printf("ATI1:GET DEVICE INFORMATION\r\n");
	printf("ATI2:PREVIEW\r\n");
	printf("ATI3:ISP_PROCESS\r\n");
	printf("ATI4:CAMERA\r\n");
	printf("ATI5:RTK EXTENDED CONTROL\r\n");
	printf("ATI6:GET COORDINATE INFO\r\n");
	printf("ATW7:MTD\r\n");
	printf("ATW8:OSD\r\n");
	printf("ATW9:PRIVATE MASK\r\n");
	printf("ATWA:OTHER\r\n");
}

extern u32 hal_isp_get_mcu_cmd_status(void);
extern int hal_isp_check_mcu_cmd_status(u32 status);

int atcmd_mcu_init_wait_cmd_done()
{
	unsigned int cmd_status = 0;
	while (1) {
		cmd_status = hal_isp_get_mcu_cmd_status();
		vTaskDelay(1);
		if (!hal_isp_check_mcu_cmd_status(cmd_status)) {
			DBG_ISP_INFO("cmd_done\r\n");
			break;
		}
	}
	return 0;
}

void fATI9(void *arg){
#if 0
	int ret = 0;
	int i = 0;
	u8 tmp[10];
	tmp[0] = 0;
	ret = hal_isp_snr_cmd_w(0xfd, 0x01, tmp, atcmd_mcu_init_wait_cmd_done, atcmd_mcu_init_wait_cmd_done);
	ret = hal_isp_snr_cmd_r(0xfd, 0x01, tmp, atcmd_mcu_init_wait_cmd_done, atcmd_mcu_init_wait_cmd_done);
	printf("0xfd = %x\r\n",tmp[0]);
	if(tmp[0] == 0x00){
		for(i=0;i<0x10;i++){
			ret = hal_isp_snr_cmd_r(i, 0x01, tmp, atcmd_mcu_init_wait_cmd_done, atcmd_mcu_init_wait_cmd_done);
			printf("index = %x value = %x\r\n",i,tmp[0]);
		}
	}
#endif
}


void fATIO(void *arg)
{
#if CONFIG_EXAMPLE_ISP_OSD_MULTI
	printf("Text/Logo OSD Test\r\n");
	if ((isp_stream_get_status(ISP_STREAM_0) | isp_stream_get_status(ISP_STREAM_1) | isp_stream_get_status(ISP_STREAM_2)) != 0) {    
        example_isp_osd_multi();
    } else {
        printf("ISP driver needs to be started\r\n");
    }
#else
	printf("CONFIG_EXAMPLE_ISP_OSD_MULTI=0\r\n");
#endif
}

void fATIM(void *arg)
{
#if CONFIG_EXAMPLE_MASK
	printf("Mask Test\r\n");
	if ((isp_stream_get_status(ISP_STREAM_0) | isp_stream_get_status(ISP_STREAM_1) | isp_stream_get_status(ISP_STREAM_2)) != 0) { 
        example_mask(1, 1280, 720);
    } else {
        printf("ISP driver needs to be started\r\n");
    }    
#else
	printf("CONFIG_EXAMPLE_MASK=0\r\n");
#endif
}

void fATID(void *arg)
{
#if CONFIG_EXAMPLE_MOTION_DETECT
	printf("Motion Detect Test\r\n");
    
	if ((isp_stream_get_status(ISP_STREAM_0) | isp_stream_get_status(ISP_STREAM_1) | isp_stream_get_status(ISP_STREAM_2)) != 0) {
        example_md();
    } else {
        printf("ISP driver needs to be started\r\n");
    }
#else
	printf("CONFIG_EXAMPLE_MOTION_DETECT=0\r\n");
#endif
}

void fATIL(void *arg)
{
        isp_get_lost_frame_info(NULL);
}

log_item_t at_isp_items[ ] = {
	{"ATIS", fATIS,},//isp_config(0,2,4,15,1280,720);
	{"ATI0", fATI0,},
	{"ATI1", fATI1,},
	{"ATIR", fATIR,},
	{"ATIQ", fATIQ,},
	{"ATIH", fATIH,},
	{"ATI9", fATI9,},
	{"ATIO", fATIO,},
	{"ATIM", fATIM,},
	{"ATID", fATID,},
	{"ATIN", fATIN,},
        {"ATIL", fATIL,},//Lost frame info
};

void at_isp_init(void)
{
	//isp_atcmd_initial();
	//printf("isp log service start\r\n");
	log_service_add_table(at_isp_items, sizeof(at_isp_items)/sizeof(at_isp_items[0]));
	printf("isp log service start\r\n");
}

log_module_init(at_isp_init);

