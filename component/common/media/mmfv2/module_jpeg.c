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
#include "module_jpeg.h"

#include "jpeg_encoder.h"

//------------------------------------------------------------------------------

int jpeg_handle(void* p, void* input, void* output)
{
    jpeg_ctx_t *ctx = (jpeg_ctx_t*)p;
	struct jpeg_context* hantro = ctx->jpeg_cont;
	uint32_t uv_offset = hantro->jpeg_parm.width*hantro->jpeg_parm.height;
	int ret;
	
	mm_queue_item_t* input_item = (mm_queue_item_t*)input;
	mm_queue_item_t* output_item = (mm_queue_item_t*)output;	
	
	hantro->source_addr = (uint32_t)input_item->data_addr;
	hantro->y_addr = (uint32_t)input_item->data_addr;
	hantro->uv_addr = (uint32_t)input_item->data_addr + uv_offset;

	//mm_printf("y %x, uv %x, dst %x\n\r", input_item->data_addr, input_item->data_addr + uv_offset, output_item->data_addr);

	hantro->dest_addr = (uint32_t)output_item->data_addr;
	hantro->dest_len = hantro->mem_info_value.mem_frame_size;
	
	ret = jpeg_encode(hantro);
	if (hantro->snapshot_cb) {
		hantro->snapshot_cb();
	}
 	
	output_item->type = AV_CODEC_ID_MJPEG;
	output_item->index = 0;
	output_item->size = hantro->dest_actual_len;
	output_item->timestamp = input_item->timestamp;
	output_item->hw_timestamp = input_item->hw_timestamp;
	
	return ret;
}

int jpeg_control(void *p, int cmd, int arg)
{
	jpeg_ctx_t *ctx = (jpeg_ctx_t*)p;
	struct jpeg_context *hantro = ctx->jpeg_cont; 
	
	switch(cmd){	
	case CMD_JPEG_SET_HEIGHT:
		hantro->jpeg_parm.height = arg;
		break;
	case CMD_JPEG_SET_WIDTH:
		hantro->jpeg_parm.width = arg;
		break;
	case CMD_JPEG_LEVEL:
		hantro->jpeg_parm.qLevel = arg;
		break;
	case CMD_JPEG_FPS:
		hantro->jpeg_parm.ratenum = arg;
		break;
	case CMD_JPEG_HEADER_TYPE:
		hantro->jpeg_parm.jpeg_full_header = arg;
		break;
	case CMD_JPEG_MEMORY_SIZE:
		hantro->mem_info_value.mem_total_size = arg;
		break;
	case CMD_JPEG_BLOCK_SIZE:
		hantro->mem_info_value.mem_block_size = arg;
		break;
	case CMD_JPEG_MAX_FRAME_SIZE:
		hantro->mem_info_value.mem_frame_size = arg;
		break;
	case CMD_JPEG_SET_PARAMS:
		{	
		jpeg_params_t *params = (jpeg_params_t*)arg;
		hantro->jpeg_parm.height              = params->height;              
		hantro->jpeg_parm.width               = params->width;               
		hantro->jpeg_parm.qLevel               = params->level;                 
		hantro->jpeg_parm.ratenum             = params->fps;           

		hantro->mem_info_value.mem_total_size = params->mem_total_size;      
		hantro->mem_info_value.mem_block_size = params->mem_block_size;      
		hantro->mem_info_value.mem_frame_size = params->mem_frame_size;
		}
		break;
	case CMD_JPEG_GET_PARAMS:
		{
		jpeg_params_t *params = (jpeg_params_t*)arg;
		params->height         = hantro->jpeg_parm.height;
		params->width          = hantro->jpeg_parm.width;
		params->level          = hantro->jpeg_parm.qLevel;
		params->fps            = hantro->jpeg_parm.ratenum;

		params->mem_total_size = hantro->mem_info_value.mem_total_size;
		params->mem_block_size = hantro->mem_info_value.mem_block_size;
		params->mem_frame_size = hantro->mem_info_value.mem_frame_size;
		}
		break;
	case CMD_JPEG_INIT_MEM_POOL:
		ctx->mem_pool = memory_init(hantro->mem_info_value.mem_total_size, hantro->mem_info_value.mem_block_size);//(4*1024*1024,512); 
		if(ctx->mem_pool == NULL){
			mm_printf("Can't allocate JPEG buffer\r\n");
			while(1);
		}
		break;
        case CMD_JPEG_UPDATE:
		if(!ctx->jpeg_cont){
			rt_printf("JPEG not init, update fail\n\r");
			return -1;
		}
		jpeg_release(ctx->jpeg_cont);
	case CMD_JPEG_APPLY:
		if(!ctx->mem_pool){
			rt_printf("need CMD_JPEG_INIT_MEM_POOL\n\r");
			while(1);
		}
		if(jpeg_initial(hantro, &hantro->jpeg_parm)< 0) {
			rt_printf("hantro_jpegenc_initial fail\n\r");
			while(1);
		}
		break;
	case CMD_SNAPSHOT_CB:
		hantro->snapshot_cb = (void (*)(void))arg;
		break;
	case CMD_JPEG_CHANGE_PARM_CB:
		hantro->change_parm_cb = (void (*)(void*))arg;
		break;
	case CMD_JPEG_GET_ENCODER:
		*(void**)arg = (void*)hantro;
		break;
	}
    return 0;
}

void* jpeg_destroy(void* p)
{
	jpeg_ctx_t *ctx = (jpeg_ctx_t*)p;
	
	if(ctx && ctx->mem_pool) memory_deinit(ctx->mem_pool);
	if(ctx && ctx->jpeg_cont)	jpeg_release(ctx->jpeg_cont);
    if(ctx) free(ctx);
    return NULL;
}

void* jpeg_create(void* parent)
{
    jpeg_ctx_t *ctx = malloc(sizeof(jpeg_ctx_t));
    if(!ctx) return NULL;
    memset(ctx, 0, sizeof(jpeg_ctx_t));
    ctx->parent = parent;
	
	ctx->jpeg_cont = jpeg_open();
	if(!ctx->jpeg_cont)
		goto jpeg_create_fail;
	
    
    return ctx;
jpeg_create_fail:
	if(ctx)	free(ctx);
	return NULL;
}

void* jpeg_new_item(void *p)
{
	void* ptr;
	jpeg_ctx_t *ctx = (jpeg_ctx_t*)p;
	struct jpeg_context *hantro = ctx->jpeg_cont; 
	
	ptr = memory_alloc(ctx->mem_pool, hantro->mem_info_value.mem_frame_size);
	
	//mm_printf("jpeg new item %x\n\r", ptr);
	//if(!ptr)	dump_info(ctx->mem_pool);
    return ptr;
}

void* jpeg_del_item(void *p, void *d)
{
	jpeg_ctx_t *ctx = (jpeg_ctx_t*)p;
	
    if(d) memory_free(ctx->mem_pool, d);
    return NULL;
}

void* jpeg_rsz_item(void *p, void *d, int len)
{
	jpeg_ctx_t *ctx = (jpeg_ctx_t*)p;
	
	//mm_printf("jpeg resize item %d\n\r", len);
	return memory_realloc(ctx->mem_pool, d, len);
}

mm_module_t jpeg_module = {
    .create = jpeg_create,
    .destroy = jpeg_destroy,
    .control = jpeg_control,
    .handle = jpeg_handle,
    
    .new_item = jpeg_new_item,
    .del_item = jpeg_del_item,
    .rsz_item = jpeg_rsz_item,
    
    .output_type = MM_TYPE_VSINK,    // output for video sink
    .module_type = MM_TYPE_VDSP,     // module type is video algorithm
	.name = "JPEG"
};