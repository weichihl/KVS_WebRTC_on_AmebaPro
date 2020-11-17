 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#include <stdint.h>
#include "mmf2_module.h"
#include "module_dual_uvcd.h"
#include "dual_uvc/inc/usbd_uvc_desc.h"
#include "avcodec.h"
//------------------------------------------------------------------------------
#define num 1

#if LIB_UVCD_DUAL

struct uvc_format *uvc_format_ptr = NULL;

static struct usbd_uvc_buffer uvc_payload[num];
static struct usbd_uvc_buffer uvc_payload_ext[num];

static int uvc_init = 0;

unsigned char *ptr_h264 = NULL;
unsigned int ptr_h264_size = 0;
#define H264_STREAM_NUM 1
#define JPEG_STREAM_NUM 0

_mutex uvc_stream_lock;

void dual_uvc_sema_init(void *parm)
{
        rtw_mutex_get(&uvc_stream_lock);
        rtw_mutex_put(&uvc_stream_lock);
        rtw_mutex_init(&uvc_stream_lock);
}

void dual_uvcd_change_format_resolution(void *ctx)
{
        rtw_up_sema_from_isr(&uvc_format_ptr->uvcd_change_sema);
}

void* dual_uvcd_create(void *parent)
{
  	struct uvc_dev *uvc_ctx = get_private_usbd_uvc();
	int i = 0;
	int status = 0;
	if(uvc_init == 1){
		printf("USB INITED");
		return (void*)uvc_ctx; 
	}
	_usb_init();
	status = wait_usb_ready();
	if(status != USB_INIT_OK){
		if(status == USB_NOT_ATTACHED)
			printf("\r\n NO USB device attached\n");
		else
			printf("\r\n USB init fail\n");
		goto exit;
	}
	if(!uvc_ctx)	return NULL;
	
	if(usbd_uvc_init()<0){
		uvc_ctx = NULL;
		printf("usbd uvc init error\r\n");
	}
       
	for(i=0;i<num;i++)
	{
	  uvc_video_put_out_stream_queue(&uvc_payload[i], &uvc_ctx->video[0]);
	  uvc_video_put_out_stream_queue(&uvc_payload_ext[i], &uvc_ctx->video[1]);
	}
	uvc_ctx->change_parm_cb = dual_uvcd_change_format_resolution;
        ////SEMA INIT
        rtw_mutex_init(&uvc_stream_lock);
        ///
	uvc_init = 1;
	return (void*)uvc_ctx; 
exit:
	return NULL;
}

int dual_uvcd_handle(void* p, void* input, void* output)
{
        int ret = 0;
        struct uvc_dev *uvc_ctx = (struct uvc_dev *)p;
		mm_queue_item_t* input_item = (mm_queue_item_t*)input;
        struct usbd_uvc_buffer *payload = NULL;//&rtp_payload;
        int uvc_idx = 0;
   
        if(input_item->type == AV_CODEC_ID_H264){
          uvc_idx = H264_STREAM_NUM;
        }else{
          uvc_idx = JPEG_STREAM_NUM;
        }
        
        //printf("input_item->type  = %d\r\n",input_item->type);

        if((uvc_ctx->common->running == 1 && uvc_idx==JPEG_STREAM_NUM))
		{}
		else if((uvc_ctx->common->running_ext == 1 && uvc_idx==H264_STREAM_NUM))
		{}
		else
			goto end;
       
        do{
			payload = uvc_video_out_stream_queue(&uvc_ctx->video[uvc_idx]);
			if(payload==NULL){
                    printf("NULL\r\n");
                    vTaskDelay(1);
			}
		}while(payload == NULL);
        
        
        payload->mem = (unsigned char*) input_item->data_addr;
        payload->bytesused = input_item->size;
        
        //rtw_mutex_get(&uvc_stream_lock);
		uvc_video_put_in_stream_queue(payload, &uvc_ctx->video[uvc_idx]);
		rtw_down_sema(&uvc_ctx->video[uvc_idx].output_queue_sema);
        //rtw_mutex_put(&uvc_stream_lock);
end:
	return ret;
}

int dual_uvcd_control(void *p, int cmd, int arg)
{
	return 0;
}

void* dual_uvcd_destroy(void* p)
{
	return NULL;
}

mm_module_t dual_uvcd_module = {
    .create = dual_uvcd_create,
    .destroy = dual_uvcd_destroy,
    .control = dual_uvcd_control,
    .handle = dual_uvcd_handle,
    
    .new_item = NULL,
    .del_item = NULL,
    
    .output_type = MM_TYPE_NONE,     // no output
    .module_type = MM_TYPE_VSINK,    // module type is video algorithm
    .name = "DUAL_UVCD"
};

#endif //LIB_UVCD_DUAL
