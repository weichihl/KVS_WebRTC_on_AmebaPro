 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#include <stdint.h>
#include "osdep_service.h"
#include "avcodec.h"
#include "mmf2_module.h"
#include "module_array.h"

//------------------------------------------------------------------------------

uint32_t array_get_aac_frame_size(unsigned char* ptr_start, unsigned char* ptr_end)
{
	if (ptr_start >= ptr_end)
		return 0;
	unsigned char* ptr = ptr_start;
	while(ptr < ptr_end){
		if(ptr[0]==0xff && (ptr[1]>>4)==0x0f)
			break;
		ptr++;
	}
	if(ptr>=ptr_end)	return (ptr_end-ptr_start);
	unsigned char * temp = ptr+3;
	u32 ausize = ((*temp&0x03)<<11)|(*(temp+1)<<3)|((*(temp+2)&0xe0)>>5);
	ptr += ausize;
	if(ptr>=ptr_end)
		return (ptr_end-ptr_start);
	else{
		while(ptr < ptr_end){
			if(ptr[0]==0xff && (ptr[1]>>4)==0x0f)
				return (ptr-ptr_start);
			ptr++;
		}
		return (ptr_end-ptr_start);
	}	
}

uint32_t array_get_h264_frame_size(unsigned char* ptr_start, unsigned char* ptr_end, uint8_t nal_len)
{
	if (ptr_start >= ptr_end)
		return 0;
	
	int skip_flag = 1;
	unsigned char* ptr = ptr_start;
	while ( ptr < ptr_end ) {
		if (ptr[0]==0 && ptr[1]==0) {
			if( (nal_len==4 && ptr[2]==0 && ptr[3]==1)
			   	|| (nal_len==3 && ptr[2]==1)) {
				if((ptr[nal_len]&0x1f)!=0x07 && (ptr[nal_len]&0x1f)!=0x08){	// not SPS or PPS
					if(skip_flag==0){
						return (ptr-ptr_start);
					}else{
						skip_flag = 0;
					}
				}
				else if((ptr[nal_len]&0x1f)==0x08){	// PPS, get next (one more) frame before return
					skip_flag=1;
				}
			}
		}
		ptr++;
	}

	return (ptr_end-ptr_start);
}

void frame_timer_handler(uint32_t hid)
{
	array_ctx_t* ctx = (array_ctx_t*)hid;
	
	if (ctx->stop)
		return;
	
	BaseType_t xTaskWokenByReceive = pdFALSE;
	BaseType_t xHigherPriorityTaskWoken;
	
	uint32_t timestamp = xTaskGetTickCountFromISR();
	
	mm_context_t *mctx = (mm_context_t*)ctx->parent;
	mm_queue_item_t* output_item;
	
	if (ctx->array.data_offset >= ctx->array.data_len) {
		if (ctx->params.mode==ARRAY_MODE_ONCE) {
			ctx->stop = 1;
			ctx->array.data_offset = 0;
			gtimer_stop(&ctx->frame_timer);
			return;
		}
		else {
			ctx->array.data_offset = 0;
		}
	}
	int is_output_ready = xQueueReceiveFromISR(mctx->output_recycle, &output_item, &xTaskWokenByReceive) == pdTRUE;
	if(is_output_ready) {
		int remain_len = ctx->array.data_len - ctx->array.data_offset;
		
		output_item->type = ctx->params.codec_id;
		output_item->timestamp = timestamp;
		output_item->data_addr = ctx->array.data_addr+ctx->array.data_offset;
		if (ctx->params.type == AVMEDIA_TYPE_AUDIO) {
			if (ctx->params.codec_id == AV_CODEC_ID_PCMU || ctx->params.codec_id == AV_CODEC_ID_PCMA) {
				output_item->size = (remain_len > ctx->params.u.a.frame_size)? ctx->params.u.a.frame_size : remain_len;
			}
			else if (ctx->params.codec_id == AV_CODEC_ID_MP4A_LATM) {
				output_item->size = array_get_aac_frame_size((unsigned char*)(ctx->array.data_addr+ctx->array.data_offset), (unsigned char*)(ctx->array.data_addr+ctx->array.data_len));
			}
			else {
				printf("TODO: unhandled codec_id:%d\n\r",ctx->params.codec_id);
				return;
			}
		}
		else if (ctx->params.type == AVMEDIA_TYPE_VIDEO) {
			if (ctx->params.codec_id == AV_CODEC_ID_H264) {
				output_item->size = array_get_h264_frame_size((unsigned char*)(ctx->array.data_addr+ctx->array.data_offset), (unsigned char*)(ctx->array.data_addr+ctx->array.data_len), ctx->params.u.v.h264_nal_size);
			}
			else {
				printf("TODO: unhandled codec_id:%d\n\r",ctx->params.codec_id);
				return;
			}
		}
		xQueueSendFromISR(mctx->output_ready, (void*)&output_item, &xHigherPriorityTaskWoken);
		ctx->array.data_offset += output_item->size;
	}
	if( xHigherPriorityTaskWoken || xTaskWokenByReceive)
		taskYIELD ();
}

int array_control(void *p, int cmd, int arg)
{
	array_ctx_t* ctx = (array_ctx_t*)p;
	
	switch(cmd){
	case CMD_ARRAY_SET_PARAMS:
		memcpy(&ctx->params, (void*)arg, sizeof(array_params_t));
		break;
	case CMD_ARRAY_GET_PARAMS:
		memcpy((void*)arg, &ctx->params, sizeof(array_params_t));
		break;
	case CMD_ARRAY_SET_ARRAY:
		memcpy(&ctx->array, (void*)arg, sizeof(array_t));
		break;
	case CMD_ARRAY_SET_MODE:
		ctx->params.mode = (uint8_t)arg;
		break;
	case CMD_ARRAY_APPLY:
		if (ctx->params.type == AVMEDIA_TYPE_VIDEO) {
			ctx->frame_timer_period = 1000000/ctx->params.u.v.fps;
		}
		else if (ctx->params.type == AVMEDIA_TYPE_AUDIO) {
			if (ctx->params.codec_id == AV_CODEC_ID_PCMU || ctx->params.codec_id == AV_CODEC_ID_PCMA) {
				ctx->frame_timer_period =(int) (1000000/((float)ctx->params.u.a.samplerate/ctx->params.u.a.frame_size));
			}
			else if (ctx->params.codec_id == AV_CODEC_ID_MP4A_LATM) {
				ctx->frame_timer_period =(int)( 1000000/((float)ctx->params.u.a.samplerate/1024));
			}
		}
		else {
			return -1;
		}	
		
		if (ctx->frame_timer_period==0) {
			printf("Error, frame_timer_period can't be 0\n\r");
			return -1;
		}
		
		gtimer_init(&ctx->frame_timer, 0xff);
		
		break;
	case CMD_ARRAY_GET_STATE:
		*(int*)arg = ((ctx->stop)? 0:1);
		break;
	case CMD_ARRAY_STREAMING:
		if(arg == 1) {	// stream on
			if (ctx->stop) {
				ctx->array.data_offset = 0;
				//printf("ctx->frame_timer_period =%d\n\r",ctx->frame_timer_period);
				gtimer_start_periodical(&ctx->frame_timer, ctx->frame_timer_period, (void*)frame_timer_handler, (uint32_t)ctx);
				ctx->stop = 0;
			}
		}else {			// stream off
			if (!ctx->stop) {
				gtimer_stop(&ctx->frame_timer);
				ctx->stop = 1;
			}
		}
		break;
	}
	return 0;
}

int array_handle(void* ctx, void* input, void* output)
{
	return 0;
}

void* array_destroy(void* p)
{
	array_ctx_t *ctx = (array_ctx_t *)p;
	
	if(ctx->stop==0)
		array_control((void*)ctx, CMD_ARRAY_STREAMING, 0);
	
	if(ctx && ctx->up_sema) rtw_free_sema(&ctx->up_sema);
	if(ctx && ctx->task) vTaskDelete(ctx->task);
	if(ctx)	free(ctx);
	return NULL;
}

void* array_create(void* parent)
{
	array_ctx_t *ctx = malloc(sizeof(array_ctx_t));
	if(!ctx) return NULL;
	memset(ctx, 0, sizeof(array_ctx_t));
	
	ctx->parent = parent;
	
	ctx->stop = 1;
	rtw_init_sema(&ctx->up_sema, 0);
	
	return ctx;

//array_create_fail:
	//array_destroy((void*)ctx);
	//return NULL;
}

void* array_new_item(void *p)
{
	return NULL;
}

void* array_del_item(void *p, void *d)
{
	return NULL;
}

mm_module_t array_module = {
	.create = array_create,
	.destroy = array_destroy,
	.control = array_control,
	.handle = array_handle,
	
	.new_item = array_new_item,
	.del_item = array_del_item,
	
	.output_type = MM_TYPE_ASINK|MM_TYPE_ADSP | MM_TYPE_VSINK|MM_TYPE_VDSP,
	.module_type = MM_TYPE_ASRC|MM_TYPE_VSRC,
	.name = "ARRAY"
};