 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#include <stdint.h>
#include "avcodec.h"
#include "mmf2_module.h"
#include "module_h264.h"

#include "h264_encoder.h"

//------------------------------------------------------------------------------

int h264_handle(void* p, void* input, void* output)
{
        h264_ctx_t *ctx = (h264_ctx_t*)p;
	struct h264_context* h264_ctx = ctx->h264_cont;
	uint32_t uv_offset = h264_ctx->h264_parm.width*h264_ctx->h264_parm.height;
	int ret;
	
	mm_queue_item_t* input_item = (mm_queue_item_t*)input;
	mm_queue_item_t* output_item = (mm_queue_item_t*)output;	
	
	h264_ctx->source_addr = (uint32_t)input_item->data_addr;
	h264_ctx->y_addr = (uint32_t)input_item->data_addr;
	h264_ctx->uv_addr = (uint32_t)input_item->data_addr + uv_offset;

	//mm_printf("y %x, uv %x, dst %x\n\r", input_item->data_addr, input_item->data_addr + uv_offset, output_item->data_addr);

	h264_ctx->dest_addr = (uint32_t)output_item->data_addr;
	h264_ctx->dest_len = h264_ctx->mem_info_value.mem_frame_size;
        h264_ctx->isp_timestamp = input_item->timestamp;
        if(h264_ctx->pause)
          return 0;
	//printf("dest_addr= 0x%x len = %d\r\n",h264_ctx->dest_addr,h264_ctx->dest_len);
        if(h264_ctx->dest_addr == 0x00){
            h264_ctx->dest_actual_len = 0x00;
        }else{
            ret = h264_encode(h264_ctx);
            if (h264_ctx->snapshot_encode_cb) {
                  int snapshot_enc_ret = h264_ctx->snapshot_encode_cb(h264_ctx->y_addr,h264_ctx->uv_addr);
            }	
        }
        if(ret == H264_FRAME_SKIP){
          return 0;
        }
	output_item->type = AV_CODEC_ID_H264;
	output_item->index = 0;
	output_item->size = h264_ctx->dest_actual_len;
	output_item->timestamp = input_item->timestamp;
	output_item->hw_timestamp = input_item->hw_timestamp;
	
	return ret;
}

int h264_control(void *p, int cmd, int arg)
{
	h264_ctx_t *ctx = (h264_ctx_t*)p;
	struct h264_context *h264_ctx = ctx->h264_cont; 
	
	switch(cmd){	
	case CMD_H264_SET_HEIGHT:
		h264_ctx->h264_parm.height = arg;
		break;
	case CMD_H264_SET_WIDTH:
		h264_ctx->h264_parm.width = arg;
		break;
	case CMD_H264_BITRATE:
		h264_ctx->h264_parm.bps = arg;
		h264_ctx->h264_ch_config.bps = arg;
		h264_ctx->h264_ch_config.bps_config = 1;		
		break;
	case CMD_H264_FPS:
		h264_ctx->h264_parm.ratenum = arg;
		break;
        case CMD_H264_PAUSE:
                h264_ctx->pause = arg;
                break;
	case CMD_H264_GOP:
		h264_ctx->h264_parm.gopLen = arg;
		break;
	case CMD_H264_MEMORY_SIZE:
		h264_ctx->mem_info_value.mem_total_size = arg;
		break;
	case CMD_H264_BLOCK_SIZE:
		h264_ctx->mem_info_value.mem_block_size = arg;
		break;
	case CMD_H264_MAX_FRAME_SIZE:
		h264_ctx->mem_info_value.mem_frame_size = arg;
		break;
	case CMD_H264_RCMODE:
		h264_ctx->h264_parm.rcMode = arg;
		break;
	case CMD_H264_FORCE_IFRAME:
                h264_set_force_iframe(h264_ctx);
                //h264_ctx->h264_ch_config.forcei_config = 1;
		break;
        case CMD_H264_SET_ROIPARM:
                {h264_roi_parm_t *roi_param = (h264_roi_parm_t*)arg;
                h264_ctx->h264_parm.roi.enable = roi_param->enable;
                h264_ctx->h264_parm.roi.left = roi_param->left;
                h264_ctx->h264_parm.roi.right = roi_param->right;
                h264_ctx->h264_parm.roi.top = roi_param->top;
                h264_ctx->h264_parm.roi.bottom = roi_param->bottom;
                break;}
        case CMD_H264_SET_ROI:
                h264_set_roi(h264_ctx);
                break;
        case CMD_H264_SET_QPCHROMA_OFFSET:
                h264_ctx->h264_parm.qp_chroma_offset = arg;//The range is -12 to 12
                break;
	case CMD_H264_SET_PARAMS:
		{	
		h264_params_t *params = (h264_params_t*)arg;
		h264_ctx->h264_parm.height              = params->height;              
		h264_ctx->h264_parm.width               = params->width;               
		h264_ctx->h264_parm.bps                 = params->bps;                 
		h264_ctx->h264_parm.ratenum             = params->fps;                 
		h264_ctx->h264_parm.gopLen              = params->gop;                 
		h264_ctx->h264_parm.rcMode              = params->rc_mode;     
		h264_ctx->h264_parm.adaptQpEn 			= params->auto_qp;
		h264_ctx->h264_parm.rcErrorRst 			= params->rst_rcerr;
                h264_ctx->h264_parm.rotation                    = params->rotation;
                h264_ctx->h264_parm.proile                      = params->profile;
                h264_ctx->h264_parm.idrHeader                   = params->idrHeader;
                h264_ctx->h264_parm.inputtype                   = params->input_type;
                h264_ctx->h264_parm.level                       = params->level;
                
		h264_ctx->mem_info_value.mem_total_size = params->mem_total_size;      
		h264_ctx->mem_info_value.mem_block_size = params->mem_block_size;      
		h264_ctx->mem_info_value.mem_frame_size = params->mem_frame_size;
		}
		break;
	case CMD_H264_GET_PARAMS:
		{
		h264_params_t *params = (h264_params_t*)arg;
		params->height         = h264_ctx->h264_parm.height;
		params->width          = h264_ctx->h264_parm.width;
		params->bps            = h264_ctx->h264_parm.bps;
		params->fps            = h264_ctx->h264_parm.ratenum;
		params->gop            = h264_ctx->h264_parm.gopLen;
		params->rc_mode        = h264_ctx->h264_parm.rcMode;

		params->mem_total_size = h264_ctx->mem_info_value.mem_total_size;
		params->mem_block_size = h264_ctx->mem_info_value.mem_block_size;
		params->mem_frame_size = h264_ctx->mem_info_value.mem_frame_size;
		}
		break;			
	case CMD_H264_SET_RCPARAM:
		{
		h264_rc_parm_t *rc_param = (h264_rc_parm_t*)arg;
		h264_ctx->h264_parm.rcMode = rc_param->rcMode;
		h264_ctx->h264_parm.maxQp  = rc_param->maxQp;
		h264_ctx->h264_parm.minIQp = rc_param->minIQp;
		h264_ctx->h264_parm.minQp  = rc_param->minQp;
		h264_ctx->h264_parm.iQp    = rc_param->iQp;
		h264_ctx->h264_parm.pQp    = rc_param->pQp;
		}
		break;
	case CMD_H264_GET_RCPARAM:
		{
		h264_rc_parm_t *rc_param = (h264_rc_parm_t*)arg;
		rc_param->rcMode = h264_ctx->h264_parm.rcMode;
		rc_param->maxQp  = h264_ctx->h264_parm.maxQp;
		rc_param->minIQp = h264_ctx->h264_parm.minIQp;
		rc_param->minQp  = h264_ctx->h264_parm.minQp;
		rc_param->iQp    = h264_ctx->h264_parm.iQp;
		rc_param->pQp    = h264_ctx->h264_parm.pQp;
		}
		break;
	case CMD_H264_SET_RCADVPARAM:
		{
		h264_rc_adv_parm_t *rc_param = (h264_rc_adv_parm_t*)arg;
		h264_ctx->h264_parm.rc_adv_enable = rc_param->rc_adv_enable = 1;
		h264_ctx->h264_parm.maxBps    = rc_param->maxBps;
		h264_ctx->h264_parm.minBps    = rc_param->minBps;
		h264_ctx->h264_parm.intraQpDelta    = rc_param->intraQpDelta;
		h264_ctx->h264_parm.mbQpAdjustment    = rc_param->mbQpAdjustment;
		h264_ctx->h264_parm.mbQpAutoBoost    = rc_param->mbQpAutoBoost;
		}
		break;
	case CMD_H264_GET_RCADVPARAM:
		{
		h264_rc_adv_parm_t *rc_param = (h264_rc_adv_parm_t*)arg;
		rc_param->rc_adv_enable = 1;
		rc_param->maxBps    = h264_ctx->h264_parm.maxBps;
		rc_param->minBps    = h264_ctx->h264_parm.minBps;
		rc_param->intraQpDelta    = h264_ctx->h264_parm.intraQpDelta;
		rc_param->mbQpAdjustment    = h264_ctx->h264_parm.mbQpAdjustment;
		rc_param->mbQpAutoBoost    = h264_ctx->h264_parm.mbQpAutoBoost;
		}
		break;			
	case CMD_H264_INIT_MEM_POOL:
		ctx->mem_pool = memory_init(h264_ctx->mem_info_value.mem_total_size, h264_ctx->mem_info_value.mem_block_size);//(4*1024*1024,512); 
		if(ctx->mem_pool == NULL){
			mm_printf("Can't allocate H264 buffer\r\n");
			while(1);
		}
		break;
	case CMD_H264_UPDATE:
		if(!ctx->h264_cont){
			rt_printf("H264 not init, update fail\n\r");
			return -1;
		}
		h264_release(ctx->h264_cont);
	case CMD_H264_APPLY:
		if(!ctx->mem_pool){
			rt_printf("need CMD_H264_INIT_MEM_POOL\n\r");
			while(1);
		}
		//if(h264_initial(h264_ctx, &h264_ctx->h264_parm)< 0) {
		if(h264_init_encoder(h264_ctx)<0){
			rt_printf("hantro_h264enc_initial fail\n\r");
			while(1);
		}
		break;
	case CMD_SNAPSHOT_ENCODE_CB:
		h264_ctx->snapshot_encode_cb = (int (*)(uint32_t,uint32_t))arg;
		break;
        case CMD_H264_SET_FORCE_DROP_FRAME:
                h264_ctx->h264_parm.force_drop_frame = arg;
                break;
        case CMD_H264_SET_BITRATE:
                h264_set_bitrate(h264_ctx,arg);
                break;
        case CMD_H264_SET_GOPLEN:
                h264_set_goplen(h264_ctx,arg);
                break;
        case CMD_H264_SET_FPS:
                h264_set_fps(h264_ctx,arg);
                break;
        case CMD_H264_SET_RCPARM_UPDATE://It will update the h264_rc_adv_parm_t and h264_rc_parm_t
                h264_set_rate_parm_update(h264_ctx);
                break;
	}
    return 0;
}

void* h264_destroy(void* p)
{
	h264_ctx_t *ctx = (h264_ctx_t*)p;
	
	if(ctx && ctx->mem_pool) memory_deinit(ctx->mem_pool);
	if(ctx && ctx->h264_cont)	{h264_release(ctx->h264_cont); free(ctx->h264_cont); }
    if(ctx) free(ctx);
    return NULL;
}

void* h264_create(void* parent)
{
    h264_ctx_t *ctx = malloc(sizeof(h264_ctx_t));
    if(!ctx) return NULL;
    memset(ctx, 0, sizeof(h264_ctx_t));
    ctx->parent = parent;
	
	ctx->h264_cont = h264_open();
	if(!ctx->h264_cont)
		goto h264_create_fail;
	
    
    return ctx;
h264_create_fail:
	if(ctx)	free(ctx);
	return NULL;
}

void* h264_new_item(void *p)
{
	void* ptr;
	h264_ctx_t *ctx = (h264_ctx_t*)p;
	struct h264_context *h264_cont = ctx->h264_cont; 
	
	ptr = memory_alloc(ctx->mem_pool, h264_cont->mem_info_value.mem_frame_size);
	
	//mm_printf("h264 new item %x\n\r", ptr);
	//if(!ptr)	dump_info(ctx->mem_pool);
    return ptr;
}

void* h264_del_item(void *p, void *d)
{
	h264_ctx_t *ctx = (h264_ctx_t*)p;
	
    if(d) memory_free(ctx->mem_pool, d);
    return NULL;
}

void* h264_rsz_item(void *p, void *d, int len)
{
	h264_ctx_t *ctx = (h264_ctx_t*)p;
	
	//mm_printf("h264 resize item %d\n\r", len);
	return memory_realloc(ctx->mem_pool, d, len);
}

mm_module_t h264_module = {
    .create = h264_create,
    .destroy = h264_destroy,
    .control = h264_control,
    .handle = h264_handle,
    
    .new_item = h264_new_item,
    .del_item = h264_del_item,
    .rsz_item = h264_rsz_item,
    
    .output_type = MM_TYPE_VSINK,    // output for video sink
    .module_type = MM_TYPE_VDSP,     // module type is video algorithm
	.name = "H264"
};