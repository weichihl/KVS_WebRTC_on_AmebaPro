 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdlib.h>
#include "mmf2_module.h"
#include "module_aad.h"

#include "aacdec.h"

//------------------------------------------------------------------------------

void aad_rtp_raw_parser(void* p, void* input, int len)
{
	
	aad_ctx_t *ctx = (aad_ctx_t*)p;
	
	// parse input data to data cache, skip 4 bytes
	memcpy( ctx->data_cache + ctx->data_cache_len , (void*)((uint32_t)input + 4), len - 4 );
	ctx->data_cache_len += len - 4;	
}

void aad_bypass_parser(void* p, void* input, int len)
{
	aad_ctx_t *ctx = (aad_ctx_t*)p;
	
	memcpy( ctx->data_cache + ctx->data_cache_len , input, len );
	ctx->data_cache_len += len;	
}

void aad_ts_parser(void* p, void* input, int len)
{
	mm_printf("Not support TS parser\n\r");
	while(1);
}

int aad_handle(void* p, void* input, void* output)
{
    aad_ctx_t *ctx = (aad_ctx_t*)p;
	mm_queue_item_t* input_item = (mm_queue_item_t*)input;
	mm_queue_item_t* output_item = (mm_queue_item_t*)output;
	
	AACFrameInfo frameInfo;
	uint8_t *inbuf, *inbuf_backup;
	int bytesLeft, bytesLeft_backup;
	int ret = 0;
	
	if(input_item->size == 0)	return -1;
	
	if (ctx->data_cache_len + input_item->size >= ctx->data_cache_size) {
		// This should never happened
		mm_printf("aac data cache overflow %d %d\r\n", ctx->data_cache_len, input_item->size);
		while(1);
	}	
	
	ctx->parser((void*)ctx, (void*)input_item->data_addr, input_item->size);
	
	inbuf = ctx->data_cache;
	bytesLeft = ctx->data_cache_len;
	
	frameInfo.outputSamps = 0;
	while (ret == 0 && bytesLeft > 1024) {
		inbuf_backup = inbuf;
		bytesLeft_backup = bytesLeft;

		ret = AACDecode(ctx->aad, &inbuf, &bytesLeft, (void *)ctx->decode_buf);
		if (ret == 0) {
			AACGetLastFrameInfo(ctx->aad, &frameInfo);

			// TODO: it might need resample if use different sample rate & channel number
			memcpy((void*)output_item->data_addr, ctx->decode_buf, frameInfo.outputSamps * 2);
		} else {
			if (ret == ERR_AAC_INDATA_UNDERFLOW) {
				inbuf = inbuf_backup;
				bytesLeft = bytesLeft_backup;
			} else {
				mm_printf("decode err:%d\r\n", ret);
			}
			break;
		}
	}

	if (bytesLeft > 0) {
		memmove(ctx->data_cache, ctx->data_cache + ctx->data_cache_len - bytesLeft, bytesLeft);
		ctx->data_cache_len = bytesLeft;
	} else {
		ctx->data_cache_len = 0;
	}	
	
	output_item->size = frameInfo.outputSamps * 2;
	output_item->timestamp = input_item->timestamp;
	output_item->index = 0;
	output_item->type = 0;
  
        return output_item->size;
}

int aad_control(void *p, int cmd, int arg)
{
	aad_ctx_t *ctx = (aad_ctx_t *)p;
	
	switch(cmd){
	case CMD_AAD_SET_PARAMS:
		memcpy(&ctx->params, ((aad_params_t*)arg), sizeof(aad_params_t));
		break;
	case CMD_AAD_GET_PARAMS:
		memcpy(((aad_params_t*)arg), &ctx->params, sizeof(aad_params_t));
		break;
	case CMD_AAD_SAMPLERATE:
		ctx->params.sample_rate = arg;
		break;
	case CMD_AAD_CHANNEL:
		ctx->params.channel = arg;
		break;
	case CMD_AAD_STREAM_TYPE:
		ctx->params.type = arg;
		break;
        case CMD_AAD_RESET:
                AACDeInitDecoder(ctx->aad);
                ctx->aad = AACInitDecoder();
                ctx->data_cache_len = 0;
	case CMD_AAD_APPLY:
		if(ctx->params.type == TYPE_RTP_RAW){
			AACFrameInfo frameInfo;
			frameInfo.nChans = ctx->params.channel;
			frameInfo.sampRateCore = ctx->params.sample_rate;
			frameInfo.profile = 1; // 1 for LC
			AACSetRawBlockParams(ctx->aad, 0, &frameInfo);	
			ctx->parser = aad_rtp_raw_parser;
		}else if(ctx->params.type == TYPE_TS)
			ctx->parser = aad_ts_parser;
		else
			ctx->parser = aad_bypass_parser;
		break;	
	}
	
    return 0;
}

void* aad_destroy(void* p)
{
	aad_ctx_t *ctx = (aad_ctx_t *)p;
	
	if(ctx && ctx->aad) AACDeInitDecoder(ctx->aad);
	
	if(ctx && ctx->decode_buf) free(ctx->decode_buf);
	if(ctx && ctx->data_cache)	free(ctx->data_cache);
    if(ctx)free(ctx);
        
    return NULL;
}

void* aad_create(void* parent)
{
    aad_ctx_t* ctx = (aad_ctx_t *)malloc(sizeof(aad_ctx_t));
    if(!ctx) return NULL;
    ctx->parent = parent;
	
	// no need check return value because of AACInitDecoder implement
	ctx->aad = AACInitDecoder();
	
	ctx->data_cache_size = 4096;
	ctx->data_cache = malloc(ctx->data_cache_size);
	if(!ctx->data_cache)
		goto aad_create_fail;
	// AAC_MAX_NCHANS (2) AAC_MAX_NSAMPS (1024) defined in aacdec.h 
	ctx->decode_buf = malloc(AAC_MAX_NCHANS * AAC_MAX_NSAMPS * sizeof(int16_t));
	if(!ctx->decode_buf)
		goto aad_create_fail;
	
	ctx->data_cache_len = 0;
	return ctx;
	
aad_create_fail:
	aad_destroy((void*)ctx);
	return NULL;
}

void* aad_new_item(void *p)
{
	//aad_ctx_t *ctx = (aad_ctx_t *)p;
	
    return malloc(AAC_MAX_NCHANS * AAC_MAX_NSAMPS * sizeof(int16_t));
}

void* aad_del_item(void *p, void *d)
{
	//aad_ctx_t *ctx = (aad_ctx_t *)p;

	if(d) free(d);
    return NULL;
}


mm_module_t aad_module = {
    .create = aad_create,
    .destroy = aad_destroy,
    .control = aad_control,
    .handle = aad_handle,
    
    .new_item = aad_new_item,
    .del_item = aad_del_item,
    
    .output_type = MM_TYPE_ASINK|MM_TYPE_ADSP,     
    .module_type = MM_TYPE_ADSP,
	.name = "AAD"
};
