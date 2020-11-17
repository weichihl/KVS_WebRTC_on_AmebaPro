 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#include <stdint.h>
#include "avcodec.h"

#include "memory_encoder.h"
#include "mmf2_module.h"
#include "module_aac.h"
#include "mmf2_dbg.h"

#include "psych.h"
#include "faac.h"
#include "faac_api.h"

//------------------------------------------------------------------------------


int aac_handle(void* p, void* input, void* output)
{
	aac_ctx_t *ctx = (aac_ctx_t*)p;
	mm_queue_item_t* input_item = (mm_queue_item_t*)input;
	mm_queue_item_t* output_item = (mm_queue_item_t*)output;
	
	//int samples_read, frame_size;
	int frame_size = 0;
        
        if(ctx->stop == 1){
          printf("stop\r\n");
          return 0;
        }
	
	output_item->timestamp = input_item->timestamp;
	// set timestamp to 1st sample (cache head)
	output_item->timestamp -= 1000 * (ctx->cache_idx/2) / ctx->params.sample_rate;
	
	/*
	if (ctx->params.bit_length==8)
		samples_read = input_item->size;
	else if (ctx->params.bit_length==16)
		samples_read = input_item->size/2;
	*/
	
	memcpy(ctx->cache + ctx->cache_idx, (void*)input_item->data_addr, input_item->size);
	ctx->cache_idx += input_item->size;
	
	if(ctx->cache_idx >= ctx->params.samples_input*2){
		frame_size = aac_encode_run(ctx->faac_enc, (void*)ctx->cache, ctx->params.samples_input, (unsigned char *)output_item->data_addr, ctx->params.max_bytes_output);
		ctx->cache_idx -= ctx->params.samples_input*2;
		if(ctx->cache_idx > 0)
			memmove(ctx->cache, ctx->cache + ctx->params.samples_input*2, ctx->cache_idx);
	}
	
	output_item->size = frame_size;
	output_item->type = AV_CODEC_ID_MP4A_LATM;
	output_item->index = 0;
	return frame_size;
}

int aac_control(void *p, int cmd, int arg)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;
	
	switch(cmd){
	case CMD_AAC_SET_PARAMS:
		memcpy(&ctx->params, ((aac_params_t*)arg), sizeof(aac_params_t));
		break;
	case CMD_AAC_GET_PARAMS:
		memcpy(((aac_params_t*)arg), &ctx->params, sizeof(aac_params_t));
		break;
	case CMD_AAC_SAMPLERATE:
		ctx->params.sample_rate = arg;
		break;
	case CMD_AAC_CHANNEL:
		ctx->params.channel = arg;
		break;
	case CMD_AAC_BITLENGTH:
		ctx->params.bit_length = arg;
		break;
	case CMD_AAC_MEMORY_SIZE:
		ctx->params.mem_total_size = arg;
		break;
	case CMD_AAC_BLOCK_SIZE:
		ctx->params.mem_block_size = arg;
		break;
	case CMD_AAC_MAX_FRAME_SIZE:
		ctx->params.mem_frame_size = arg;
		break;
	case CMD_AAC_INIT_MEM_POOL:
		ctx->mem_pool = memory_init(ctx->params.mem_total_size, ctx->params.mem_block_size);
		if(ctx->mem_pool == NULL){
			mm_printf("Can't allocate AAC buffer\r\n");
			while(1);
		}
		break;
        case CMD_AAC_STOP:
                ctx->stop = 1;
                break;
        case CMD_AAC_RESET:
                aac_encode_close(&ctx->faac_enc);
                if(ctx->cache){
                  free(ctx->cache);
                }
                ctx->cache_idx = 0;
                printf("aac reset\r\n");
	case CMD_AAC_APPLY:
                ctx->stop = 0;
		aac_encode_init(&ctx->faac_enc, ctx->params.bit_length, ctx->params.output_format, ctx->params.sample_rate, ctx->params.channel, ctx->params.mpeg_version, &ctx->params.samples_input, &ctx->params.max_bytes_output);
		ctx->cache =  (uint8_t *)malloc(ctx->params.samples_input * 2 + 1500);	// 1500 max audio page size
		if(!ctx->cache){
			mm_printf("Output memory\n\r");
			while(1);
			// TODO add handing code
		}
		break;
	}
	
	return 0;
}

void* aac_destroy(void* p)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;
	
	if(ctx && ctx->mem_pool) memory_deinit(ctx->mem_pool);
	if(ctx)free(ctx);
	
	return NULL;
}

void* aac_create(void* parent)
{
	aac_ctx_t *ctx = malloc(sizeof(aac_ctx_t));
	if(!ctx) return NULL;
	memset(ctx, 0, sizeof(aac_ctx_t));
	ctx->parent = parent;
	
	return ctx;
}

void* aac_new_item(void *p)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;
	
	return memory_alloc(ctx->mem_pool, ctx->params.mem_frame_size);
}

void* aac_del_item(void *p, void *d)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;
	
	memory_free(ctx->mem_pool, d);
	return NULL;
}

void* aac_rsz_item(void *p, void *d, int len)
{
	aac_ctx_t *ctx = (aac_ctx_t *)p;
	return memory_realloc(ctx->mem_pool, d, len);
}

mm_module_t aac_module = {
	.create = aac_create,
	.destroy = aac_destroy,
	.control = aac_control,
	.handle = aac_handle,
	
	.new_item = aac_new_item,
	.del_item = aac_del_item,
	.rsz_item = aac_rsz_item,
	
	.output_type = MM_TYPE_ASINK,
	.module_type = MM_TYPE_ADSP,
	.name = "AAC"
};
