 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "module_isp.h"
#include "module_h264.h"
#include "module_jpeg.h"
#include "module_uvcd.h"

#include "mmf2_link.h"
#include "mmf2_siso.h"
#include "mmf2_simo.h"
#include "mmf2_miso.h"
#include "mmf2_mimo.h"
#include "example_media_uvcd.h"

#include "video_common_api.h"
#include "sensor_service.h"
#include "example_media_uvcd.h"
#include "platform_opts.h"
#include "uvc_os_wrap_via_osdep_api.h"
#include "video.h"
   
#if !UVCD_DUAL

//#define DEBUG_OPENCV

#if defined(DEBUG_OPENCV)
#include "module_opencv.h"
// ISP (640x360) -> OPENCV
static mm_context_t* isp_v2_ctx		= NULL;
static mm_context_t* opencv_ctx       	= NULL;
static mm_siso_t* siso_isp_opencv     	= NULL;

#define CV_HW_SLOT 2
#define CV_SW_SLOT 4
static isp_params_t isp_v2_params = {
	.width    = 640, 
	.height   = 360,
	.fps      = 1,
	.slot_num = CV_HW_SLOT,
	.buff_num = CV_SW_SLOT,
	.format   = ISP_FORMAT_YUV420_SEMIPLANAR
};

opencv_params_t opencv_params = {
	.dummy = 0
};

roi_t uvcd_roi_array[16];
int uvcd_roi_count;
#endif

   
#define ENABLE_LDC 1
//------------------------------------------------------------------------------
// Parameter for modules
//------------------------------------------------------------------------------

//STEP 1 ISP->UVCD 2 ISP->H264->UVCD 3 ISP->JPEG->UVCD
mm_context_t* uvcd_ctx       = NULL;
mm_context_t* isp_ctx        = NULL;
mm_context_t* h264_ctx       = NULL;
mm_context_t* jpeg_ctx       = NULL;
mm_siso_t* siso_isp_uvcd     = NULL;
mm_siso_t* siso_isp_h264     = NULL;
mm_siso_t* siso_h264_uvcd    = NULL;
mm_siso_t* siso_isp_jpeg     = NULL;
mm_siso_t* siso_jpeg_uvcd    = NULL;

extern struct uvc_format *uvc_format_ptr;

struct uvc_format *uvc_format_local = NULL;;

#define WIDTH  MAX_W
#define HEIGHT MAX_H

#define BLOCK_SIZE						1024*10
#define FRAME_SIZE						(WIDTH*HEIGHT/2)
#define BUFFER_SIZE						(FRAME_SIZE*3)
#define UVC_STREAM_ID 2

#define FORMAT_NV16 ISP_FORMAT_YUV422_SEMIPLANAR//ISP_FORMAT_YUV422_SEMIPLANAR//ISP_FORMAT_BAYER_PATTERN

#define YUY2_FPS 2
isp_params_t isp_params = {
	.width    = MAX_W, 
	.height   = MAX_H,
	.fps      = YUY2_FPS,
	.slot_num = 2,
	.buff_num = 4,
	.format   = FORMAT_NV16,
	.bayer_type = BAYER_TYPE_BEFORE_BLC
};

h264_params_t h264_params = {
	.width          = MAX_W,
	.height         = MAX_H,
	.bps            = 2*1024*1024,
	.fps            = 30,
	.gop            = 30,
	.rc_mode        = RC_MODE_H264CBR,
	.mem_total_size = BUFFER_SIZE,
	.mem_block_size = BLOCK_SIZE,
	.mem_frame_size = FRAME_SIZE,
	.input_type     = ISP_FORMAT_YUV420_SEMIPLANAR
};

jpeg_params_t jpeg_params = {
	.width          = MAX_W,
	.height         = MAX_H,
	.level          = 5,
	.fps            = 15,
	.mem_total_size = BUFFER_SIZE,
	.mem_block_size = BLOCK_SIZE,
	.mem_frame_size = FRAME_SIZE
};

//int switch_isp_raw = 0; //0 SETUP FINISH 1: YUV420 2: YUV422 3:Bayer
//static int switch_ldc = 0;
DECLARE_UVC_INPUT_HEADER_DESCRIPTOR(1, 4);
extern struct UVC_INPUT_HEADER_DESCRIPTOR(1, 4) uvc_input_header;
extern struct uvc_format_uncompressed uvc_format_yuy2;
extern struct uvc_format_uncompressed uvc_format_nv12;
extern struct uvc_format_uncompressed uvc_format_mjpg;
extern struct uvc_format_uncompressed uvc_format_h264;
//extern void RTKUSER_USB_GET(void* buf);
//extern void RTKUSER_USB_SET(void* buf);
void example_media_uvcd_init(void)
{
	unsigned char index_cnt=1;
#if CONFIG_LIGHT_SENSOR
	init_sensor_service();
#else
	ir_cut_init(NULL);
	ir_cut_enable(1);
#endif
#if UVCD_YUY2
	uvc_format_yuy2.bFormatIndex = index_cnt++;
#endif
#if UVCD_NV12
	uvc_format_nv12.bFormatIndex = index_cnt++;
#endif
#if UVCD_MJPG
	uvc_format_mjpg.bFormatIndex = index_cnt++;
#endif
#if UVCD_H264
	uvc_format_h264.bFormatIndex = index_cnt++;
#endif
	
	uvc_input_header.bLength     = 13+index_cnt-1;
	uvc_input_header.bNumFormats = index_cnt-1;
         //isp_ctx_t* ctx = (isp_ctx_t*)p;
        isp_ctx_t* ctx = NULL;
        
        uvc_format_ptr = (struct uvc_format *)malloc(sizeof(struct uvc_format));
        memset(uvc_format_ptr, 0, sizeof(struct uvc_format));
        
        uvc_format_local = (struct uvc_format *)malloc(sizeof(struct uvc_format));
        memset(uvc_format_local, 0, sizeof(struct uvc_format));
        
        rtw_init_sema(&uvc_format_ptr->uvcd_change_sema,0);
        
        uvc_format_ptr->format = FORMAT_TYPE_YUY2;
        uvc_format_ptr->fps = isp_params.fps;
        uvc_format_ptr->height = isp_params.height;
        uvc_format_ptr->width = isp_params.width;
        uvc_format_ptr->isp_format = FORMAT_NV16;
        uvc_format_ptr->ldc = 1;
        uvc_format_ptr->enable_pu = 0;
        uvc_format_ptr->uvcd_ext_get_cb = NULL;//RTKUSER_USB_GET;
        uvc_format_ptr->uvcd_ext_set_cb = NULL;//RTKUSER_USB_SET;
        
        uvc_format_local->format = FORMAT_TYPE_YUY2;
        uvc_format_local->fps = isp_params.fps;
        uvc_format_local->height = isp_params.height;
        uvc_format_local->width = isp_params.width;
        uvc_format_local->isp_format = FORMAT_NV16;
        uvc_format_local->ldc = 1;
        uvc_format_local->enable_pu = 0;
        uvc_format_local->uvcd_ext_get_cb = NULL;//RTKUSER_USB_GET;
        uvc_format_local->uvcd_ext_set_cb = NULL;//RTKUSER_USB_SET;
		
	uvcd_ctx = mm_module_open(&uvcd_module);
    //  struct uvc_dev *uvc_ctx = (struct uvc_dev *)uvcd_ctx->priv;
        
	if(uvcd_ctx){
		//mm_module_ctrl(uvcd_ctx, CMD_UVCD_CALLBACK_SET, (int)RTKUSER_USB_SET);
		//mm_module_ctrl(uvcd_ctx, CMD_UVCD_CALLBACK_GET, (int)RTKUSER_USB_GET);
	}else{
		rt_printf("uvcd open fail\n\r");
		goto mmf2_example_uvcd_fail;
	}	
        
	isp_ctx = mm_module_open(&isp_module);
	if(isp_ctx){
		mm_module_ctrl(isp_ctx, CMD_ISP_SET_PARAMS, (int)&isp_params);
		mm_module_ctrl(isp_ctx, MM_CMD_SET_QUEUE_LEN, isp_params.buff_num);
		mm_module_ctrl(isp_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		//mm_module_ctrl(isp_ctx, CMD_ISP_APPLY, UVC_STREAM_ID);	// start channel 0
	}else{
		rt_printf("ISP open fail\n\r");
		goto mmf2_example_uvcd_fail;
	}
        
        ctx = (isp_ctx_t*)isp_ctx->priv;
        
#if defined(DEBUG_OPENCV)
	isp_v2_ctx = mm_module_open(&isp_module);
	if(isp_v2_ctx){
		mm_module_ctrl(isp_v2_ctx, CMD_ISP_SET_PARAMS, (int)&isp_v2_params);
		mm_module_ctrl(isp_v2_ctx, MM_CMD_SET_QUEUE_LEN, CV_SW_SLOT);
		mm_module_ctrl(isp_v2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(isp_v2_ctx, CMD_ISP_APPLY, 1);	// start channel 1
	}else{
		rt_printf("ISP open fail\n\r");
		goto mmf2_example_uvcd_fail;
	}
	opencv_ctx = mm_module_open(&opencv_module);
	if(opencv_ctx){
		mm_module_ctrl(opencv_ctx, CMD_OPENCV_SET_PARAMS, (int)&opencv_params);
		mm_module_ctrl(opencv_ctx, CMD_OPENCV_SET_ROI_BUF, (int)uvcd_roi_array);
		mm_module_ctrl(opencv_ctx, CMD_OPENCV_SET_ROI_COUNT, (int)&uvcd_roi_count);
		//mm_module_ctrl(opencv_ctx, MM_CMD_SET_QUEUE_LEN, OV_SW_SLOT);
		//mm_module_ctrl(opencv_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		//mm_module_ctrl(opencv_ctx, CMD_ISP_APPLY, 1);	// start channel 1
	}else{
		rt_printf("ISP open fail\n\r");
		goto mmf2_example_uvcd_fail;
	}	
	
	siso_isp_opencv = siso_create();
	
	if(siso_isp_opencv){
		siso_ctrl(siso_isp_opencv, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v2_ctx, 0);
		siso_ctrl(siso_isp_opencv, MMIC_CMD_ADD_OUTPUT, (uint32_t)opencv_ctx, 0);
		siso_start(siso_isp_opencv);
	}else{
		rt_printf("siso cv open fail\n\r");
		goto mmf2_example_uvcd_fail;
	}
#endif
        
#if UVCD_H264
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
#endif
        
#if UVCD_MJPG
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
#endif
          
        siso_isp_uvcd = siso_create();
	if(siso_isp_uvcd){
		siso_ctrl(siso_isp_uvcd, MMIC_CMD_ADD_INPUT, (uint32_t)isp_ctx, 0);
		siso_ctrl(siso_isp_uvcd, MMIC_CMD_ADD_OUTPUT, (uint32_t)uvcd_ctx, 0);
		siso_start(siso_isp_uvcd);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_example_uvcd_fail;
	}
        

#if UVCD_H264
        siso_isp_h264 = siso_create();
        
        if(siso_isp_h264){
		siso_ctrl(siso_isp_h264, MMIC_CMD_ADD_INPUT, (uint32_t)isp_ctx, 0);
		siso_ctrl(siso_isp_h264, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_ctx, 0);
		//siso_start(siso_isp_h264);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_example_uvcd_fail;
	}
#endif        
        siso_isp_jpeg = siso_create();
        
#if UVCD_MJPG
        if(siso_isp_jpeg){
		siso_ctrl(siso_isp_jpeg, MMIC_CMD_ADD_INPUT, (uint32_t)isp_ctx, 0);
		siso_ctrl(siso_isp_jpeg, MMIC_CMD_ADD_OUTPUT, (uint32_t)jpeg_ctx, 0);
		//siso_start(siso_isp_h264);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_example_uvcd_fail;
	}
#endif
        
#if UVCD_H264
        siso_h264_uvcd = siso_create();
  
        if(siso_h264_uvcd){
		siso_ctrl(siso_h264_uvcd, MMIC_CMD_ADD_INPUT, (uint32_t)h264_ctx, 0);
		siso_ctrl(siso_h264_uvcd, MMIC_CMD_ADD_OUTPUT, (uint32_t)uvcd_ctx, 0);
		//siso_start(siso_h264_uvcd);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_example_uvcd_fail;
	}
#endif
	
#if UVCD_MJPG
        siso_jpeg_uvcd = siso_create();
  
        if(siso_jpeg_uvcd){
		siso_ctrl(siso_jpeg_uvcd, MMIC_CMD_ADD_INPUT, (uint32_t)jpeg_ctx, 0);
		siso_ctrl(siso_jpeg_uvcd, MMIC_CMD_ADD_OUTPUT, (uint32_t)uvcd_ctx, 0);
		//siso_start(siso_h264_uvcd);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_example_uvcd_fail;
	}
#endif

        
        while(1){
                rtw_down_sema(&uvc_format_ptr->uvcd_change_sema);
                printf("f:%d h:%d s:%d w:%d\r\n",uvc_format_ptr->format,uvc_format_ptr->height,uvc_format_ptr->state,uvc_format_ptr->width);
                if((uvc_format_local->format != uvc_format_ptr->format) || (uvc_format_local->width != uvc_format_ptr->width) || (uvc_format_local->height != uvc_format_ptr->height)){
                    printf("change f:%d h:%d s:%d w:%d\r\n",uvc_format_ptr->format,uvc_format_ptr->height,uvc_format_ptr->state,uvc_format_ptr->width);
                    uvc_format_local->state = uvc_format_ptr->state;
                    if(uvc_format_ptr->format == FORMAT_TYPE_YUY2){
                        uvc_format_local->fps = YUY2_FPS;
                        isp_params.format = FORMAT_NV16;
                        isp_params.fps = YUY2_FPS;
                    }else if(uvc_format_ptr->format == FORMAT_TYPE_NV12){
                        uvc_format_local->fps = 15;
                        isp_params.format = ISP_FORMAT_YUV420_SEMIPLANAR;
                        isp_params.fps = 15;
#if UVCD_H264
                    }else if(uvc_format_ptr->format == FORMAT_TYPE_H264){
                        uvc_format_local->format = ISP_FORMAT_YUV420_SEMIPLANAR;
                        uvc_format_local->fps = 30;
                        isp_params.format = ISP_FORMAT_YUV420_SEMIPLANAR;
                        isp_params.fps = 30;
#endif
#if UVCD_MJPG
                    }else if(uvc_format_ptr->format == FORMAT_TYPE_MJPEG){
                        uvc_format_local->format = ISP_FORMAT_YUV420_SEMIPLANAR;
                        uvc_format_local->fps = 15;
                        isp_params.format = ISP_FORMAT_YUV420_SEMIPLANAR;
                        isp_params.fps = 15;
#endif
                    }else if(uvc_format_ptr->format == FORMAT_TYPE_BAYER){
                        uvc_format_local->fps = YUY2_FPS;
                        isp_params.format = ISP_FORMAT_BAYER_PATTERN;
                        isp_params.fps = YUY2_FPS;
                    }
                    
                    uvc_format_local->format = uvc_format_ptr->format;
                    uvc_format_local->width = uvc_format_ptr->width;
                    uvc_format_local->height = uvc_format_ptr->height;
                    uvc_format_local->bayer_type = uvc_format_ptr->bayer_type;
                    isp_params.width = uvc_format_local->width;
                    isp_params.height = uvc_format_local->height;
                    isp_params.bayer_type = uvc_format_local->bayer_type;
                    if((uvc_format_ptr->format == FORMAT_TYPE_YUY2) || (uvc_format_ptr->format == FORMAT_TYPE_NV12) || (uvc_format_ptr->format == FORMAT_TYPE_BAYER)){
                          mm_module_ctrl(isp_ctx, CMD_ISP_STREAM_STOP, 0);
                          
                          siso_pause(siso_isp_uvcd);
#if UVCD_H264
                          siso_pause(siso_isp_h264);
                          siso_pause(siso_h264_uvcd);
#endif
#if UVCD_MJPG
                          siso_pause(siso_isp_jpeg);
                          siso_pause(siso_jpeg_uvcd);
#endif
                          mm_module_ctrl(isp_ctx, CMD_ISP_SET_PARAMS,(int)&isp_params);
                          mm_module_ctrl(isp_ctx, CMD_ISP_UPDATE, UVC_STREAM_ID);
                          siso_resume(siso_isp_uvcd);
                          printf("siso_resume(siso_isp_uvcd)\r\n");
                    }else if(uvc_format_ptr->format == FORMAT_TYPE_H264){
                          mm_module_ctrl(isp_ctx, CMD_ISP_STREAM_STOP, 0);
                          
                          siso_pause(siso_isp_uvcd);
#if UVCD_H264
                          siso_pause(siso_isp_h264);
                          siso_pause(siso_h264_uvcd);
#endif
#if UVCD_MJPG
                          siso_pause(siso_isp_jpeg);
                          siso_pause(siso_jpeg_uvcd);
#endif
                          
                          mm_module_ctrl(isp_ctx, CMD_ISP_SET_PARAMS,(int)&isp_params);
                          mm_module_ctrl(isp_ctx, CMD_ISP_UPDATE, UVC_STREAM_ID);
                          siso_resume(siso_isp_h264);
                          siso_resume(siso_h264_uvcd);
                          printf("siso_resume(siso_isp_h264_uvcd)\r\n");
                    }else if(uvc_format_ptr->format == FORMAT_TYPE_MJPEG){
                          mm_module_ctrl(isp_ctx, CMD_ISP_STREAM_STOP, 0);
                          siso_pause(siso_isp_uvcd);
#if UVCD_H264
                          siso_pause(siso_isp_h264);
                          siso_pause(siso_h264_uvcd);
#endif
#if UVCD_MJPG
                          siso_pause(siso_isp_jpeg);
                          siso_pause(siso_jpeg_uvcd);
#endif
                          mm_module_ctrl(isp_ctx, CMD_ISP_SET_PARAMS,(int)&isp_params);
                          mm_module_ctrl(isp_ctx, CMD_ISP_UPDATE, UVC_STREAM_ID);
#if UVCD_MJPG
                          siso_resume(siso_isp_jpeg);
                          siso_resume(siso_jpeg_uvcd);
#endif
                          printf("siso_resume(siso_isp_jpeg_uvcd)\r\n");
                    }
                }
                if(uvc_format_local->format == FORMAT_TYPE_YUY2 && uvc_format_ptr->format == FORMAT_TYPE_YUY2){
                    if(uvc_format_local->isp_format != uvc_format_ptr->isp_format){
                          uvc_format_local->isp_format = uvc_format_ptr->isp_format;
                          mm_module_ctrl(isp_ctx, CMD_ISP_STREAM_STOP, 0);
                          isp_params.format = uvc_format_local->isp_format;
                          siso_pause(siso_isp_uvcd);
#if UVCD_H264
                          siso_pause(siso_isp_h264);
                          siso_pause(siso_h264_uvcd);
#endif
#if UVCD_MJPG
                          siso_pause(siso_isp_jpeg);
                          siso_pause(siso_jpeg_uvcd);
#endif
                          mm_module_ctrl(isp_ctx, CMD_ISP_SET_PARAMS,(int)&isp_params);
                          mm_module_ctrl(isp_ctx, CMD_ISP_UPDATE, UVC_STREAM_ID);
                          siso_resume(siso_isp_uvcd);
                          printf("siso_resume(siso_isp_uvcd)\r\n");
                    }
                }
                if(uvc_format_local->ldc != uvc_format_ptr->ldc){
#if 0
                    extern void isp_ldc_switch(int id,int format,int width,int height,int enable);
                    uvc_format_local->ldc = uvc_format_ptr->ldc;
                    isp_ldc_switch(0,uvc_format_local->isp_format,uvc_format_local->width,uvc_format_local->height,uvc_format_ptr->ldc);
#else
                    mm_module_ctrl(isp_ctx, CMD_ISP_STREAM_STOP, 0);

                    siso_pause(siso_isp_uvcd);
#if UVCD_H264
                    siso_pause(siso_isp_h264);
                    siso_pause(siso_h264_uvcd);
#endif
#if UVCD_MJPG
                    siso_pause(siso_isp_jpeg);
                    siso_pause(siso_jpeg_uvcd);
#endif

                    isp_stream_apply(ctx->stream);
                    extern void isp_ldc_switch(int id,int format,int width,int height,int enable);
                    uvc_format_local->ldc = uvc_format_ptr->ldc;
#if ENABLE_LDC
                    extern int mcu_init_wait_cmd_done_polling();
                    mcu_init_wait_cmd_done_polling();
                    isp_ldc_switch(0,uvc_format_local->isp_format,uvc_format_local->width,uvc_format_local->height,uvc_format_ptr->ldc);
#endif
                    mm_module_ctrl(isp_ctx,CMD_ISP_STREAM_START,0);
                    if(uvc_format_ptr->format == FORMAT_TYPE_YUY2 || uvc_format_ptr->format == FORMAT_TYPE_NV12){
                        siso_resume(siso_isp_uvcd);
                        printf("siso_resume(siso_isp_uvcd)\r\n");
#if UVCD_H264
                    }else if(uvc_format_ptr->format == FORMAT_TYPE_H264){
                        siso_resume(siso_isp_h264);
                        siso_resume(siso_h264_uvcd);
                        printf("siso_resume(siso_isp_h264_uvcd)\r\n");;
#endif
#if UVCD_MJPG
                    }else if(uvc_format_ptr->format == FORMAT_TYPE_MJPEG){
                        siso_resume(siso_isp_jpeg);
                        siso_resume(siso_jpeg_uvcd);
                        printf("siso_resume(siso_isp_jpeg_uvcd)\r\n");
#endif
                    }else{
                        printf("siso_resume format = %d\r\n",uvc_format_ptr->format);
                    }
#endif
                }
                if(uvc_format_local->state != uvc_format_ptr->state){
                        uvc_format_local->state = uvc_format_ptr->state;
                        if(uvc_format_ptr->state){
                                if((uvc_format_ptr->format == FORMAT_TYPE_YUY2) || (uvc_format_ptr->format == FORMAT_TYPE_NV12) || (uvc_format_ptr->format == FORMAT_TYPE_BAYER)){
                                                                  mm_module_ctrl(isp_ctx, CMD_ISP_SET_PARAMS,(int)&isp_params);
                                          mm_module_ctrl(isp_ctx, CMD_ISP_UPDATE, UVC_STREAM_ID);
                                          siso_resume(siso_isp_uvcd);
                                          printf("power on siso_resume(siso_isp_uvcd)\r\n");
#if UVCD_H264
                                    }else if(uvc_format_ptr->format == FORMAT_TYPE_H264){
                                          mm_module_ctrl(isp_ctx, CMD_ISP_SET_PARAMS,(int)&isp_params);
                                          mm_module_ctrl(isp_ctx, CMD_ISP_UPDATE, UVC_STREAM_ID);
                                          siso_resume(siso_isp_h264);
                                          siso_resume(siso_h264_uvcd);
                                          printf("power on siso_resume(siso_isp_h264_uvcd)\r\n");
#endif
#if UVCD_MJPG
                                    }else if(uvc_format_ptr->format == FORMAT_TYPE_MJPEG){
                                          mm_module_ctrl(isp_ctx, CMD_ISP_SET_PARAMS,(int)&isp_params);
                                          mm_module_ctrl(isp_ctx, CMD_ISP_UPDATE, UVC_STREAM_ID);
                                          siso_resume(siso_isp_jpeg);
                                          siso_resume(siso_jpeg_uvcd);
                                          printf("power on siso_resume(siso_isp_jpeg_uvcd)\r\n");
#endif
                                    }
                        }else{
                                          if((uvc_format_ptr->format == FORMAT_TYPE_YUY2) || (uvc_format_ptr->format == FORMAT_TYPE_NV12) || (uvc_format_ptr->format == FORMAT_TYPE_BAYER)){
                                          mm_module_ctrl(isp_ctx, CMD_ISP_STREAM_STOP, 0);
                                          
                                          siso_pause(siso_isp_uvcd);
#if UVCD_H264
                                          siso_pause(siso_isp_h264);
                                          siso_pause(siso_h264_uvcd);
#endif
#if UVCD_MJPG
                                          siso_pause(siso_isp_jpeg);
                                          siso_pause(siso_jpeg_uvcd);
#endif
                                          printf("power off siso_stop(siso_isp_uvcd)\r\n");
                                    }else if(uvc_format_ptr->format == FORMAT_TYPE_H264){
                                          mm_module_ctrl(isp_ctx, CMD_ISP_STREAM_STOP, 0);
                                          
                                          siso_pause(siso_isp_uvcd);
#if UVCD_H264
                                          siso_pause(siso_isp_h264);
                                          siso_pause(siso_h264_uvcd);
#endif
#if UVCD_MJPG
                                          siso_pause(siso_isp_jpeg);
                                          siso_pause(siso_jpeg_uvcd);
#endif
                                          printf("power off siso_stop(siso_isp_h264_uvcd)\r\n");
                                    }else if(uvc_format_ptr->format == FORMAT_TYPE_MJPEG){
                                          mm_module_ctrl(isp_ctx, CMD_ISP_STREAM_STOP, 0);
                                          siso_pause(siso_isp_uvcd);
#if UVCD_H264
                                          siso_pause(siso_isp_h264);
                                          siso_pause(siso_h264_uvcd);
#endif
#if UVCD_MJPG
                                          siso_pause(siso_isp_jpeg);
                                          siso_pause(siso_jpeg_uvcd);
#endif
                                          printf("power off siso_stop(siso_isp_jpeg_uvcd)\r\n");
                                    }
                                
                        }
                }
        }

mmf2_example_uvcd_fail:
	
	return;
}

void example_media_uvcd_main(void *param)
{
	example_media_uvcd_init();
	// TODO: exit condition or signal
	while(1)
	{
		vTaskDelay(1000);
	}
	
	//vTaskDelete(NULL);
}

void example_media_uvcd(void)
{
	/*user can start their own task here*/
	if(xTaskCreate(example_media_uvcd_main, ((const char*)"example_media_uvcd_main"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\r\n example_media_two_source_main: Create Task Error\n");
	}
}

#endif //UVCD_DUAL