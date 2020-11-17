 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "module_isp.h"
#include "module_h264.h"
#include "module_jpeg.h"
#include "module_dual_uvcd.h"

#include "mmf2_link.h"
#include "mmf2_siso.h"
#include "mmf2_simo.h"
#include "mmf2_miso.h"
#include "mmf2_mimo.h"
#include "example_media_dual_uvcd.h"

#include "video_common_api.h"
#include "sensor_service.h"
#include "example_media_dual_uvcd.h"
#include "platform_opts.h"
   
#if UVCD_DUAL

#if defined(H264_JPEG)
mm_context_t* uvcd_ctx       = NULL;
mm_context_t* uvcd_ext_ctx       = NULL;
mm_context_t* isp_ctx        = NULL;
mm_context_t* isp_ext_ctx        = NULL;
mm_context_t* h264_ctx       = NULL;
mm_context_t* jpeg_ctx       = NULL;
mm_siso_t* siso_isp_uvcd     = NULL;
mm_siso_t* siso_isp_h264     = NULL;
//mm_siso_t* siso_h264_uvcd    = NULL;
mm_siso_t* siso_isp_jpeg     = NULL;
mm_siso_t* siso_isp_h264_uvcd  = NULL;
mm_siso_t* siso_isp_jpeg_uvcd  = NULL;
//mm_siso_t* siso_jpeg_uvcd    = NULL;
mm_miso_t* miso_h264_jpeg_uvcd = NULL;


extern struct uvc_format *uvc_format_ptr;

struct uvc_format *uvc_format_local = NULL;;

#define WIDTH  		1920//1920
#define HEIGHT 		1080//1080

#define WIDTH_EXT  		640//1920
#define HEIGHT_EXT 		360//1080

// 30fps, 2Mbps, JPEG quality 9
#define FPS	   		30 
#define BITRATE 	2*1024*1024//1*1024*1024//2*1024*1024
#define JPEG_LEVEL 	9

#define BLOCK_SIZE						1024*10
#define FRAME_SIZE						(WIDTH*HEIGHT/2)
#define BUFFER_SIZE						(FRAME_SIZE*3)

#define FORMAT_NV16 ISP_FORMAT_YUV422_SEMIPLANAR//ISP_FORMAT_YUV422_SEMIPLANAR//ISP_FORMAT_BAYER_PATTERN

isp_params_t isp_params = {
	.width    = WIDTH, 
	.height   = HEIGHT,
	.fps      = FPS,
	.slot_num = 1,
	.buff_num = 3,
	.format   = ISP_FORMAT_YUV420_SEMIPLANAR
};

isp_params_t isp_ext_params = {
	.width    = WIDTH_EXT, 
	.height   = HEIGHT_EXT,
	.fps      = FPS,
	.slot_num = 1,
	.buff_num = 3,
	.format   = ISP_FORMAT_YUV420_SEMIPLANAR
};

h264_params_t h264_params = {
	.width          = WIDTH,
	.height         = HEIGHT,
	.bps            = BITRATE,
	.fps            = FPS,
	.gop            = FPS,
	.rc_mode        = RC_MODE_H264CBR,
	.mem_total_size = BUFFER_SIZE,
	.mem_block_size = BLOCK_SIZE,
	.mem_frame_size = FRAME_SIZE
};

jpeg_params_t jpeg_params = {
	.width          = WIDTH_EXT,
	.height         = HEIGHT_EXT,
	.level          = JPEG_LEVEL,
	.fps            = FPS,
	.mem_total_size = BUFFER_SIZE,
	.mem_block_size = BLOCK_SIZE,
	.mem_frame_size = FRAME_SIZE
};

void example_media_dual_uvcd_init(void)
{       
                uvc_format_ptr = (struct uvc_format *)malloc(sizeof(struct uvc_format));
                memset(uvc_format_ptr, 0, sizeof(struct uvc_format));
                
                uvc_format_local = (struct uvc_format *)malloc(sizeof(struct uvc_format));
                memset(uvc_format_local, 0, sizeof(struct uvc_format));
                
                rtw_init_sema(&uvc_format_ptr->uvcd_change_sema,0);
                
                uvc_format_ptr->format = FORMAT_TYPE_H264;
                uvc_format_ptr->fps = isp_params.fps;
                uvc_format_ptr->height = isp_params.height;
                uvc_format_ptr->width = isp_params.width;
                uvc_format_ptr->isp_format = isp_params.format;
                uvc_format_ptr->ldc = 1;
                
                uvc_format_local->format = FORMAT_TYPE_H264;
                uvc_format_local->fps = isp_params.fps;
                uvc_format_local->height = isp_params.height;
                uvc_format_local->width = isp_params.width;
                uvc_format_local->isp_format = isp_params.format;
                uvc_format_local->ldc = 1;
                
                uvcd_ctx = mm_module_open(&dual_uvcd_module);
              //  struct uvc_dev *uvc_ctx = (struct uvc_dev *)uvcd_ctx->priv;
                
                if(uvcd_ctx){
                        //mm_module_ctrl(uvcd_ctx, CMD_RTSP2_SET_APPLY, 0);
                        //mm_module_ctrl(uvcd_ctx, CMD_RTSP2_SET_STREAMMING, ON);
                }else{
                        rt_printf("uvcd open fail\n\r");
                        goto mmf2_example_uvcd_fail;
                }
                        
                uvcd_ext_ctx = mm_module_open(&dual_uvcd_module);
                
                if(uvcd_ext_ctx){
                                
                }else{
                        rt_printf("uvcd open fail\n\r");
                        goto mmf2_example_uvcd_fail;
                }
		
		//
	
		isp_ctx = mm_module_open(&isp_module);
		if(isp_ctx){
			mm_module_ctrl(isp_ctx, CMD_ISP_SET_PARAMS, (int)&isp_params);
			mm_module_ctrl(isp_ctx, MM_CMD_SET_QUEUE_LEN, isp_params.buff_num);
			mm_module_ctrl(isp_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
			mm_module_ctrl(isp_ctx, CMD_ISP_APPLY, 0);	// start channel 0
		}else{
			rt_printf("ISP open fail\n\r");
			goto mmf2_example_uvcd_fail;
		}
	
		isp_ext_ctx = mm_module_open(&isp_module);
		if(isp_ext_ctx){
			mm_module_ctrl(isp_ext_ctx, CMD_ISP_SET_PARAMS, (int)&isp_ext_params);
			mm_module_ctrl(isp_ext_ctx, MM_CMD_SET_QUEUE_LEN, isp_ext_params.buff_num);
			mm_module_ctrl(isp_ext_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
			mm_module_ctrl(isp_ext_ctx, CMD_ISP_APPLY, 1);	// start channel 0
		}else{
			rt_printf("ISP open fail\n\r");
			goto mmf2_example_uvcd_fail;
		}
  
                h264_ctx = mm_module_open(&h264_module);
		if(h264_ctx){
			mm_module_ctrl(h264_ctx, CMD_H264_SET_PARAMS, (int)&h264_params);
			mm_module_ctrl(h264_ctx, MM_CMD_SET_QUEUE_LEN, 3);
			mm_module_ctrl(h264_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
			mm_module_ctrl(h264_ctx, CMD_H264_INIT_MEM_POOL, 0);
			mm_module_ctrl(h264_ctx, CMD_H264_APPLY, 0);
		}else{
			rt_printf("H264 open fail\n\r");
			goto mmf2_example_uvcd_fail;
		}
        
                jpeg_ctx = mm_module_open(&jpeg_module);
		if(jpeg_ctx){
			mm_module_ctrl(jpeg_ctx, CMD_JPEG_SET_PARAMS, (int)&jpeg_params);
			mm_module_ctrl(jpeg_ctx, MM_CMD_SET_QUEUE_LEN, 3);
			mm_module_ctrl(jpeg_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
			mm_module_ctrl(jpeg_ctx, CMD_JPEG_INIT_MEM_POOL, 0);
			mm_module_ctrl(jpeg_ctx, CMD_JPEG_APPLY, 0);
		}else{
			rt_printf("JPEG open fail\n\r");
			goto mmf2_example_uvcd_fail;
		}

                siso_isp_h264 = siso_create();
                
                if(siso_isp_h264){
                        siso_ctrl(siso_isp_h264, MMIC_CMD_ADD_INPUT, (uint32_t)isp_ctx, 0);
                        siso_ctrl(siso_isp_h264, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_ctx, 0);
                        siso_start(siso_isp_h264);
                }else{
                        rt_printf("siso1 open fail\n\r");
                        goto mmf2_example_uvcd_fail;
                }
                
                siso_isp_jpeg = siso_create();

                if(siso_isp_jpeg){
                        siso_ctrl(siso_isp_jpeg, MMIC_CMD_ADD_INPUT, (uint32_t)isp_ext_ctx, 0);
                        siso_ctrl(siso_isp_jpeg, MMIC_CMD_ADD_OUTPUT, (uint32_t)jpeg_ctx, 0);
                        siso_start(siso_isp_jpeg);
                }else{
                        rt_printf("siso1 open fail\n\r");
                        goto mmf2_example_uvcd_fail;
                }
		
		siso_isp_h264_uvcd = siso_create();
		if(siso_isp_h264_uvcd){
                        siso_ctrl(siso_isp_h264_uvcd, MMIC_CMD_ADD_INPUT, (uint32_t)h264_ctx, 0);
                        siso_ctrl(siso_isp_h264_uvcd, MMIC_CMD_ADD_OUTPUT, (uint32_t)uvcd_ctx, 0);
                        siso_start(siso_isp_h264_uvcd);
		}
		
		siso_isp_jpeg_uvcd = siso_create();
		if(siso_isp_jpeg_uvcd){
                        siso_ctrl(siso_isp_jpeg_uvcd, MMIC_CMD_ADD_INPUT, (uint32_t)jpeg_ctx, 0);
                        siso_ctrl(siso_isp_jpeg_uvcd, MMIC_CMD_ADD_OUTPUT, (uint32_t)uvcd_ext_ctx, 0);
                        siso_start(siso_isp_jpeg_uvcd);
		}
        
        while(1)
                vTaskDelay(1000);

mmf2_example_uvcd_fail:
	
	return;
}

void example_media_dual_uvcd_main(void *param)
{
	example_media_dual_uvcd_init();
	// TODO: exit condition or signal
	while(1)
	{
		vTaskDelay(1000);
	}
	
	//vTaskDelete(NULL);
}

void example_media_dual_uvcd(void)
{
	/*user can start their own task here*/
	if(xTaskCreate(example_media_dual_uvcd_main, ((const char*)"example_media_dual_uvcd_main"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\r\n example_media_two_source_main: Create Task Error\n");
	}
}
#elif defined(H264_NV12)

mm_context_t* uvcd_ctx       = NULL;
mm_context_t* uvcd_ext_ctx       = NULL;
mm_context_t* isp_ctx        = NULL;
mm_context_t* isp_ext_ctx    = NULL;
mm_context_t* h264_ctx       = NULL;
mm_siso_t* siso_isp_uvcd     = NULL;
mm_siso_t* siso_isp_h264     = NULL;
//mm_miso_t* miso_h264_nv12_uvcd = NULL;

//mm_siso_t* siso_isp_uvcd  = NULL;
mm_siso_t* siso_isp_h264_uvcd  = NULL;

extern struct uvc_format *uvc_format_ptr;

struct uvc_format *uvc_format_local = NULL;;

#define WIDTH  		1920
#define HEIGHT 		1080
#define FPS	   		24//20//15//30
#define BITRATE 	2*1024*1024//512*1024

#define WIDTH_EXT  		640
#define HEIGHT_EXT 		360
#define FPS_EXT	   		12//10//15//30

#define BLOCK_SIZE						1024*10
#define FRAME_SIZE						(WIDTH*HEIGHT/2)
#define BUFFER_SIZE						(FRAME_SIZE*3)

#define FORMAT_NV16 ISP_FORMAT_YUV422_SEMIPLANAR//ISP_FORMAT_YUV422_SEMIPLANAR//ISP_FORMAT_BAYER_PATTERN

isp_params_t isp_params = {
	.width    = WIDTH, 
	.height   = HEIGHT,
	.fps      = FPS,
	.slot_num = 1,
	.buff_num = 3,
	.format   = ISP_FORMAT_YUV420_SEMIPLANAR
};

isp_params_t isp_ext_params = {
	.width    = WIDTH_EXT, 
	.height   = HEIGHT_EXT,
	.fps      = FPS_EXT,
	.slot_num = 1,
	.buff_num = 3,
	.format   = ISP_FORMAT_YUV420_SEMIPLANAR
};

h264_params_t h264_params = {
	.width          = WIDTH,
	.height         = HEIGHT,
	.bps            = BITRATE,
	.fps            = FPS,
	.gop            = FPS,
	.rc_mode        = RC_MODE_H264CBR,
	.mem_total_size = BUFFER_SIZE,
	.mem_block_size = BLOCK_SIZE,
	.mem_frame_size = FRAME_SIZE,
	.idrHeader      = 1,
	.profile        = H264_BASE_PROFILE
};

#include "FreeRTOS.h"
#include "task.h"
#include <platform/platform_stdlib.h>
#include "basic_types.h"
#include "platform_opts.h"
#include "usb.h"
#include "dfu/inc/usbd_dfu.h"
///////////////////////////////
#include "isp_cmd.h"
#include "hal_api.h"
#include "rtl8195bhp_isp.h"
#include "hal_isp.h"
#include "isp_cmd_api.h"
#include "isp_api.h"

#include "flash_api.h"
#include "device_lock.h"
#define UVC_MODE 0x00
#define DFU_MODE 0x01
#define USB_DFU_LOCATION 0x600000
#define USB_UVC_LOCATION 0x601000
#define NONE    0X00
#define USB_ERR 0x01
#define ISP_ERR 0x02

void usb_platform_reset(void){
	// reset LS platform
	ls_sys_reset();
	// system software reset
	sys_reset();	
	while(1) osDelay(1000);
}

void usb_dfu_switch_mode(int mode)
{
        flash_t flash;
	unsigned char type[4] = {0};
	if(mode == UVC_MODE){
		type[0]='U';type[1]='V';type[2]='C';
	}else if(mode == DFU_MODE){
		type[0]='D';type[1]='F';type[2]='U';
	}
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_erase_sector(&flash, USB_DFU_LOCATION);
	flash_stream_write(&flash, USB_DFU_LOCATION, sizeof(type), (uint8_t *) type);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
        //ota_platform_reset();
}

void ota_dfu_reset_prepare(void)
{
        printf("switch to uvc mode");
        usb_dfu_switch_mode(UVC_MODE);
}

int usb_dfu_get_mode(void)
{
        flash_t flash;
	unsigned char type[4] = {0};
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_stream_read(&flash, USB_DFU_LOCATION, sizeof(type), (uint8_t *) type);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
        printf("dfu %c %c %c %x %x %x\r\n",type[0],type[1],type[2],type[0],type[1],type[2]);
	if(type[0] == 'D' && type[1] == 'F' && type[2] == 'U')
		return DFU_MODE;
	else
		return UVC_MODE;
}

int usb_uvc_set_status(int mode)
{
        flash_t flash;
	unsigned char status[4] = {0};
	if(mode == USB_ERR){
		status[0]='U';status[1]='S';status[2]='B';
	}else if(mode == ISP_ERR){
		status[0]='I';status[1]='S';status[2]='P';
	}
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_erase_sector(&flash, USB_UVC_LOCATION);
	flash_stream_write(&flash, USB_UVC_LOCATION, sizeof(status), (uint8_t *) status);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
        //ota_platform_reset();
}

int usb_uvc_get_status(void)
{
        flash_t flash;
	unsigned char type[4] = {0};
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_stream_read(&flash, USB_UVC_LOCATION, sizeof(type), (uint8_t *) type);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
        printf("usb_uvc_get_status %c %c %c %x %x %x\r\n",type[0],type[1],type[2],type[0],type[1],type[2]);
	if(type[0] == 'U' && type[1] == 'S' && type[2] == 'B')
		return USB_ERR;
	else if(type[0] == 'I' && type[1] == 'S' && type[2] == 'P')
		return ISP_ERR;
        else
                return NONE; 
}

void dfu_mode_entry(void* param){
	int status = 0;
	_usb_init();
	status = wait_usb_ready();
	if(status != USB_INIT_OK){
		if(status == USB_NOT_ATTACHED)
			printf("\r\n NO USB device attached\n");
		else
			printf("\r\n USB init fail\n");
		goto exit;
	}
	printf("DFU OTA VERSION 0\r\n");
	status = usbd_dfu_init();

	if(status){
		printf("USB DFU driver load fail.\n");
	}else{
		printf("USB MSC driver load done, Available heap [0x%x]\n", xPortGetFreeHeapSize());
	}
exit:
        while(1){
          vTaskDelay(1000);
        }
}
void dual_h264_stop()
{
        mm_module_ctrl(h264_ctx, CMD_H264_PAUSE, 1);
        printf("stop h264\r\n");
}
//We can call the isp stop function to verify whether the monitor task is correct.
void dual_yuv_isp_stop()//Channel 1
{     
      mm_module_ctrl(isp_ext_ctx, CMD_ISP_STREAM_STOP, 1);
}
//We can call the isp stop function to verify whether the monitor task is correct.
void dual_h264_isp_stop()//Channel 0
{
      mm_module_ctrl(isp_ctx, CMD_ISP_STREAM_STOP, 1);
}

void trigger_hardfault(void)//To verify the watchdog reset
{
      void (*fp)(void) = (void (*)(void))(0x00000000);
      fp();
}

#define WATCHDOG_TIMEOUT 10000
#define WATCHDOG_REFRESH 8000

int watch_dog_value = 0;


static void watchdog_thread(void *param)
{
      watchdog_reset_platform(1);
      watchdog_init(WATCHDOG_TIMEOUT);
      watchdog_start();
      while(1) {
                watchdog_refresh();
                vTaskDelay(WATCHDOG_REFRESH);
      }
}

void monitor_uvcd_thread(void *param)
{
      extern void uvc_get_stream_state(int *v0_open, int *v1_open,int *v0_count, int *v1_count);
      int v0_open, v1_open, v0_count, v1_count = 0;
      unsigned int count_0 = 0;
      unsigned int count_1 = 0;
      unsigned int isp_count = 0;
      unsigned int v0_count_temp[4] = {0};
      unsigned int v1_count_temp[4] = {0};
      unsigned int isp0_frame_count[4] = {0};
      unsigned int isp1_frame_count[4] = {0};
      unsigned int isp0_drop_frame_count[4] = {0};
      unsigned int isp1_drop_frame_count[4] = {0};
      int mode = 0;
      
      if(xTaskCreate(watchdog_thread, ((const char*)"watchdog_thread"), 1024, NULL, tskIDLE_PRIORITY + 5, NULL) != pdPASS)
                    printf("\n\r%s xTaskCreate(watchdog_thread) failed", __FUNCTION__);

      printf("usb_uvc_get_status = %d\r\n",usb_uvc_get_status());
      while(1){
        uvc_get_stream_state(&v0_open,&v1_open,&v0_count,&v1_count);
        if(v0_open){
               v0_count_temp[count_0]=v0_count;
               if(v0_count_temp[0] == v0_count_temp[1] && v0_count_temp[0] == v0_count_temp[2] && v0_count_temp[0] == v0_count_temp[3]){
                 printf("No vidoe0 usb data is transferring %x %x %x %x\r\n",v0_count_temp[0],v0_count_temp[1],v0_count_temp[2],v0_count_temp[3]);
                  mode = USB_ERR;
                  if(isp0_frame_count[0] == isp0_frame_count[1] && isp0_frame_count[0] == isp0_frame_count[2] && isp0_frame_count[0] == isp0_frame_count[3])
                  {
                          if(isp0_drop_frame_count[0] == isp0_drop_frame_count[1] && isp0_drop_frame_count[0] == isp0_drop_frame_count[2] && isp0_drop_frame_count[0] == isp0_drop_frame_count[3])
                          {
                                 mode = ISP_ERR; 
                          }

                  }
                  printf("isp0_frame_count is transferring %u %u %u %u\r\n",isp0_frame_count[0],isp0_frame_count[1],isp0_frame_count[2],isp0_frame_count[3]);
                  printf("isp0_drop_frame_count is transferring %u %u %u %u\r\n",isp0_drop_frame_count[0],isp0_drop_frame_count[1],isp0_drop_frame_count[2],isp0_drop_frame_count[3]);
                  vTaskDelay(5000);
                  uvc_get_stream_state(&v0_open,&v1_open,&v0_count,&v1_count);
                  if(v0_count == v0_count_temp[0]){
                      usb_uvc_set_status(mode);
                      usb_platform_reset();
                  }else{
                      printf("v0_count %u v0_count_temp %u\r\n",v0_count,v0_count_temp[0]);
                  }
               }else{
                  //printf("vidoe0 usb data is transferring %x %x %x %x\r\n",v0_count_temp[0],v0_count_temp[1],v0_count_temp[2],v0_count_temp[3]);
               }
               count_0+=1;
               count_0%=4;
        }
        if(v1_open){
               v1_count_temp[count_1]=v1_count;
               if(v1_count_temp[0] == v1_count_temp[1] && v1_count_temp[0] == v1_count_temp[2] && v1_count_temp[0] == v1_count_temp[3]){
                  printf("No vidoe1 usb data is transferring %x %x %x %x\r\n",v1_count_temp[0],v1_count_temp[1],v1_count_temp[2],v1_count_temp[3]);
                  mode = USB_ERR;
                  if(isp1_frame_count[0] == isp1_frame_count[1] && isp1_frame_count[0] == isp1_frame_count[2] && isp1_frame_count[0] == isp1_frame_count[3])
                  {
                          if(isp1_drop_frame_count[0] == isp1_drop_frame_count[1] && isp1_drop_frame_count[0] == isp1_drop_frame_count[2] && isp1_drop_frame_count[0] == isp1_drop_frame_count[3])
                          {
                                 mode = ISP_ERR; 
                          }

                  }
                  printf("isp1_frame_count is transferring %u %u %u %u\r\n",isp1_frame_count[0],isp1_frame_count[1],isp1_frame_count[2],isp1_frame_count[3]);  
                  printf("isp1_drop_frame_count is transferring %u %u %u %u\r\n",isp1_drop_frame_count[0],isp1_drop_frame_count[1],isp1_drop_frame_count[2],isp1_drop_frame_count[3]);
                  //usb_uvc_set_status(mode);
                  //usb_platform_reset();
                  vTaskDelay(5000);
                  uvc_get_stream_state(&v0_open,&v1_open,&v0_count,&v1_count);
                  if(v1_count == v1_count_temp[0]){
                      usb_uvc_set_status(mode);
                      usb_platform_reset();
                  }else{
                      printf("v1_count %u v1_count_temp %u\r\n",v1_count,v1_count_temp[0]);
                  }
               }else{
                  //printf("vidoe1 usb data is transferring %x %x %x %x\r\n",v1_count_temp[0],v1_count_temp[1],v1_count_temp[2],v1_count_temp[3]);
               }
               count_1+=1;
               count_1%=4;
        }
        
        
        vTaskDelay(1000);
        isp_ctx_t* ctx = (isp_ctx_t*)isp_ctx->priv;//For H264
        isp_ctx_t* ctx_ext = (isp_ctx_t*)isp_ext_ctx->priv;
        
        isp0_frame_count[isp_count] = ctx_ext->state.isp_frame_total;
        isp1_frame_count[isp_count] = ctx->state.isp_frame_total;
        
        isp0_drop_frame_count[isp_count] = ctx_ext->state.drop_frame_total;
        isp1_drop_frame_count[isp_count] = ctx->state.drop_frame_total;
#if 0
        printf("isp0_frame_count is transferring %x %x %x %x\r\n",isp0_frame_count[0],isp0_frame_count[1],isp0_frame_count[2],isp0_frame_count[3]);
        printf("isp1_frame_count is transferring %x %x %x %x\r\n",isp1_frame_count[0],isp1_frame_count[1],isp1_frame_count[2],isp1_frame_count[3]);  
        printf("isp0_drop_frame_count is transferring %x %x %x %x\r\n",isp0_drop_frame_count[0],isp0_drop_frame_count[1],isp0_drop_frame_count[2],isp0_drop_frame_count[3]);  
        printf("isp1_drop_frame_count is transferring %x %x %x %x\r\n",isp1_drop_frame_count[0],isp1_drop_frame_count[1],isp1_drop_frame_count[2],isp1_drop_frame_count[3]);  
#endif
        isp_count+=1;
        isp_count%=4;
          
      }
}

void dual_uvcd_monitor_task(void)
{
	/*user can start their own task here*/
	if(xTaskCreate(monitor_uvcd_thread, ((const char*)"monitor_uvcd_thread"), 512, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS) {
		printf("\r\n monitor_uvcd_thread: Create Task Error\n");
	}
}

void example_media_dual_uvcd_init(void)
{       
		uvc_format_ptr = (struct uvc_format *)malloc(sizeof(struct uvc_format));
		memset(uvc_format_ptr, 0, sizeof(struct uvc_format));
		
		uvc_format_local = (struct uvc_format *)malloc(sizeof(struct uvc_format));
		memset(uvc_format_local, 0, sizeof(struct uvc_format));
		
		rtw_init_sema(&uvc_format_ptr->uvcd_change_sema,0);
		
		uvc_format_ptr->format = FORMAT_TYPE_H264;
		uvc_format_ptr->fps = isp_params.fps;
		uvc_format_ptr->height = isp_params.height;
		uvc_format_ptr->width = isp_params.width;
		uvc_format_ptr->isp_format = isp_params.format;
		uvc_format_ptr->ldc = 1;
		
		uvc_format_local->format = FORMAT_TYPE_H264;
		uvc_format_local->fps = isp_params.fps;
		uvc_format_local->height = isp_params.height;
		uvc_format_local->width = isp_params.width;
		uvc_format_local->isp_format = isp_params.format;
		uvc_format_local->ldc = 1;
		
		uvcd_ctx = mm_module_open(&dual_uvcd_module);
	  //  struct uvc_dev *uvc_ctx = (struct uvc_dev *)uvcd_ctx->priv;
		
		if(uvcd_ctx){
				//mm_module_ctrl(uvcd_ctx, CMD_RTSP2_SET_APPLY, 0);
				//mm_module_ctrl(uvcd_ctx, CMD_RTSP2_SET_STREAMMING, ON);
		}else{
				rt_printf("uvcd open fail\n\r");
				goto mmf2_example_uvcd_fail;
		}
				
		uvcd_ext_ctx = mm_module_open(&dual_uvcd_module);
		
		if(uvcd_ext_ctx){
						
		}else{
				rt_printf("uvcd open fail\n\r");
				goto mmf2_example_uvcd_fail;
		}

		//
	
		isp_ctx = mm_module_open(&isp_module);
		if(isp_ctx){
			mm_module_ctrl(isp_ctx, CMD_ISP_SET_PARAMS, (int)&isp_params);
			mm_module_ctrl(isp_ctx, MM_CMD_SET_QUEUE_LEN, isp_params.buff_num);
			mm_module_ctrl(isp_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
			mm_module_ctrl(isp_ctx, CMD_ISP_APPLY, 0);	// start channel 0
		}else{
			rt_printf("ISP open fail\n\r");
			goto mmf2_example_uvcd_fail;
		}
	
		isp_ext_ctx = mm_module_open(&isp_module);
		if(isp_ext_ctx){
			mm_module_ctrl(isp_ext_ctx, CMD_ISP_SET_PARAMS, (int)&isp_ext_params);
			mm_module_ctrl(isp_ext_ctx, MM_CMD_SET_QUEUE_LEN, isp_ext_params.buff_num);
			mm_module_ctrl(isp_ext_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
			mm_module_ctrl(isp_ext_ctx, CMD_ISP_APPLY, 1);	// start channel 0
		}else{
			rt_printf("ISP open fail\n\r");
			goto mmf2_example_uvcd_fail;
		}
  
		h264_ctx = mm_module_open(&h264_module);
		if(h264_ctx){
			mm_module_ctrl(h264_ctx, CMD_H264_SET_PARAMS, (int)&h264_params);
			mm_module_ctrl(h264_ctx, MM_CMD_SET_QUEUE_LEN, 3);
			mm_module_ctrl(h264_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
			mm_module_ctrl(h264_ctx, CMD_H264_INIT_MEM_POOL, 0);
			mm_module_ctrl(h264_ctx, CMD_H264_APPLY, 0);
		}else{
			rt_printf("H264 open fail\n\r");
			goto mmf2_example_uvcd_fail;
		}
        

		siso_isp_h264 = siso_create();
		
		if(siso_isp_h264){
				siso_ctrl(siso_isp_h264, MMIC_CMD_ADD_INPUT, (uint32_t)isp_ctx, 0);
				siso_ctrl(siso_isp_h264, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_ctx, 0);
				siso_start(siso_isp_h264);
		}else{
				rt_printf("siso1 open fail\n\r");
				goto mmf2_example_uvcd_fail;
		}
                
		siso_isp_uvcd = siso_create();

		if(siso_isp_uvcd){
				siso_ctrl(siso_isp_uvcd, MMIC_CMD_ADD_INPUT, (uint32_t)isp_ext_ctx, 0);
				siso_ctrl(siso_isp_uvcd, MMIC_CMD_ADD_OUTPUT, (uint32_t)uvcd_ext_ctx, 0);
				siso_start(siso_isp_uvcd);
		}else{
				rt_printf("siso1 open fail\n\r");
				goto mmf2_example_uvcd_fail;
		}
		
		siso_isp_h264_uvcd = siso_create();
		if(siso_isp_h264_uvcd){
                        siso_ctrl(siso_isp_h264_uvcd, MMIC_CMD_ADD_INPUT, (uint32_t)h264_ctx, 0);
                        siso_ctrl(siso_isp_h264_uvcd, MMIC_CMD_ADD_OUTPUT, (uint32_t)uvcd_ctx, 0);
                        siso_start(siso_isp_h264_uvcd);
		}
                
                dual_uvcd_monitor_task();
                while(1){
                  if(uvc_format_local->state != uvc_format_ptr->state){
                        uvc_format_local->state = uvc_format_ptr->state;
                        printf("uvc stream state = %d\r\n",uvc_format_ptr->state);
                  }
                  vTaskDelay(1000);
                }

mmf2_example_uvcd_fail:
	
	return;
}

void example_media_dual_uvcd_main(void *param)
{
        printf("get dfu mode\r\n");
        //usb_dfu_switch_mode(0);
        //usb_dfu_get_mode();
        if(usb_dfu_get_mode() == UVC_MODE){
            example_media_dual_uvcd_init();
        }else{
            dfu_mode_entry(NULL);
        }
	// TODO: exit condition or signal
	while(1)
	{
		vTaskDelay(1000);
	}
	
	//vTaskDelete(NULL);
}
void example_media_dual_uvcd(void)
{
	/*user can start their own task here*/
	if(xTaskCreate(example_media_dual_uvcd_main, ((const char*)"example_media_dual_uvcd_main"), 512, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS) {
		printf("\r\n example_media_two_source_main: Create Task Error\n");
	}
}
#endif

#endif //UVCD_DUAL