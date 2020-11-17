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
#include "mp4_muxer.h"
#include "mmf2_module.h"
#include "module_mp4.h"
#include "fatfs_sdcard_api.h"
//------------------------------------------------------------------------------

int mp4_handle(void* p, void* input, void* output)
{
	int ret = 0;
    mp4_ctx_t *ctx = (mp4_ctx_t *)p;
	mm_queue_item_t* input_item = (mm_queue_item_t*)input;
	struct _mp4_context *mp4_muxer = (struct _mp4_context *)ctx->mp4_muxer;
	
	if ( (input_item->type == AV_CODEC_ID_H264) || (input_item->type == AV_CODEC_ID_MP4A_LATM) ) {
		mp4_muxer_handle(mp4_muxer, (uint8_t*)input_item->data_addr, input_item->size, input_item->type,input_item->timestamp);
	}
	return ret;	
}

int mp4_control(void *p, int cmd, int arg)
{
	mp4_ctx_t *ctx = (mp4_ctx_t *)p;
	struct _mp4_context *mp4_muxer = (struct _mp4_context *)ctx->mp4_muxer;
	
	switch(cmd) {
		case CMD_MP4_SET_PARAMS:
			memcpy(&ctx->params, ((mp4_params_t*)arg), sizeof(mp4_params_t));
			mp4_muxer->width = ctx->params.width;
			mp4_muxer->height = ctx->params.height;
			mp4_muxer->frame_rate = ctx->params.fps;
			mp4_muxer->gop = ctx->params.gop;
			
			mp4_muxer->sample_rate = ctx->params.sample_rate;
			mp4_muxer->channel_count = ctx->params.channel;
			
			mp4_muxer->period_time = ctx->params.record_length;
			mp4_muxer->type = ctx->params.record_type;
			mp4_muxer->file_total = ctx->params.record_file_num;
			memset(mp4_muxer->filename,0,sizeof(mp4_muxer->filename));
			strncpy(mp4_muxer->filename,ctx->params.record_file_name,sizeof(mp4_muxer->filename));
			mp4_muxer->fatfs_buf_size = ctx->params.fatfs_buf_size;
                        mp4_muxer->mp4_user_callback = ctx->params.mp4_user_callback;
			break;
		case CMD_MP4_GET_PARAMS:
			memcpy(((mp4_params_t*)arg), &ctx->params, sizeof(mp4_params_t));
			break;
		case CMD_MP4_SET_HEIGHT:
			ctx->params.height = arg;
			mp4_muxer->height = arg;
			break;
		case CMD_MP4_SET_WIDTH:
			ctx->params.width = arg;
			mp4_muxer->width = arg;
			break;
		case CMD_MP4_SET_FPS:
			ctx->params.fps = arg;
			mp4_muxer->frame_rate = arg;
			break;
		case CMD_MP4_SET_GOP:
			ctx->params.gop = arg;
			mp4_muxer->gop = arg;
			break;
		case CMD_MP4_SET_SAMPLERATE:
			ctx->params.sample_rate = arg;
			mp4_muxer->sample_rate = arg;
			break;
		case CMD_MP4_SET_CHANNEL:
			ctx->params.channel = arg;
			mp4_muxer->channel_count = arg;
			break;
		case CMD_MP4_SET_RECORD_LENGTH:
			ctx->params.record_length = arg;
			mp4_muxer->period_time = arg;
			break;
		case CMD_MP4_GET_RECORD_LENGTH:	
			memcpy(((int*)arg), &mp4_muxer->period_time, sizeof(int));
			break;
		case CMD_MP4_SET_RECORD_TYPE:
			ctx->params.record_type = arg;
			mp4_muxer->type = arg;
			break;
		case CMD_MP4_GET_RECORD_TYPE:
			memcpy(((uint32_t*)arg), &mp4_muxer->type, sizeof(uint32_t));
			break;
		case CMD_MP4_SET_RECORD_FILE_NAME:
			memset(ctx->params.record_file_name,0,sizeof(ctx->params.record_file_name));
			strncpy(ctx->params.record_file_name,(char*)arg, sizeof(ctx->params.record_file_name));
			strcpy(mp4_muxer->filename,ctx->params.record_file_name);
			break;
		case CMD_MP4_GET_RECORD_FILE_NAME:
			memset(((char*)arg),0,32);
			memcpy(((char*)arg), &mp4_muxer->filename, sizeof(mp4_muxer->filename));
			break;
		case CMD_MP4_SET_FATFS_BUF_SIZE:
			ctx->params.fatfs_buf_size = arg;
			mp4_muxer->fatfs_buf_size = arg;
			break;
		case CMD_MP4_START:
			mp4_start_record(mp4_muxer, arg);
			break;
		case CMD_MP4_STOP:
			mp4_stop_record(mp4_muxer);
			break;		
		case CMD_MP4_GET_STATUS:
			{
				int *status = (int*)arg;
				*status = mp4_is_recording(mp4_muxer);
			}
			break;
		case CMD_MP4_RESET_FILE_INDEX:
			mp4_muxer->file_name_index = 0;
			break;
                case CMD_MP4_SET_STOP_CB:
                        mp4_muxer->cb_stop = (int (*)(void*))arg;
                        break;
                case CMD_MP4_SET_END_CB:
                        mp4_muxer->cb_end = (int (*)(void*))arg;
                        break;
                case CMD_MP4_LOOP_MODE:
                        mp4_muxer->loop_mode = arg;
                        break;
                case CMD_MP4_SET_ERROR_CB:
                        mp4_muxer->cb_error = (int (*)(void*))arg;
                        break;
                case CMD_MP4_SET_OPEN_CB:
                        mp4_muxer->cb_fopen = (int (*)(void*,const char*,char))arg;//F_OPEN
                        break;
                case CMD_MP4_SET_WRITE_CB:
                        mp4_muxer->cb_fwrite = (int (*)(void*,void*,unsigned int,unsigned int *))arg;//F_WRITE
                        break;
                case CMD_MP4_SET_SEEK_CB:
                        mp4_muxer->cb_fseek = (int (*)(void*,unsigned int))arg;//F_SEEK
                        break;
                case CMD_MP4_SET_CLOSE_CB:
                        mp4_muxer->cb_fclose = (int (*)(void*))arg;//F_CLOSE
                        break;
		default:
			break;
	}
        /*
        int (*cb_fwrite)(void*,void*,unsigned int,unsigned int *);//Start
        int (*cb_fseek)(void*,unsigned int);
        int (*cb_fopen)(void*,const char *,char mode);
        int (*cb_fclose)(void*);
*/
	
    return 0;
}

void* mp4_destroy(void* p)
{
	mp4_ctx_t *ctx = (mp4_ctx_t *)p;
	
	if (ctx) { 
		if (ctx->mp4_muxer){
			mp4_muxer_close(ctx->mp4_muxer);
			free(ctx->mp4_muxer);
		}
		fatfs_sd_close();
		free(ctx);
	}
    return NULL;
}

void* mp4_create(void* parent)
{
    mp4_ctx_t *ctx = malloc(sizeof(mp4_ctx_t));
    if(!ctx) return NULL;
    memset(ctx, 0, sizeof(mp4_ctx_t));
    ctx->parent = parent;
	
	ctx->mp4_muxer = (pmp4_context) malloc(sizeof(mp4_context));
	if(!ctx->mp4_muxer)	goto mp4_create_fail;
    memset(ctx->mp4_muxer, 0, sizeof(mp4_context));
	
	if(fatfs_sd_init()<0){
		goto mp4_create_fail;
	}
	fatfs_sd_get_param(&ctx->fatfs_params);
	set_mp4_fatfs_param(ctx->mp4_muxer, &ctx->fatfs_params);
	
	mp4_muxer_init(ctx->mp4_muxer);

	return ctx;
mp4_create_fail:
	mp4_destroy((void*)ctx);
    return NULL;
}

mm_module_t mp4_module = {
    .create = mp4_create,
    .destroy = mp4_destroy,
    .control = mp4_control,
    .handle = mp4_handle,
    
    .new_item = NULL,
    .del_item = NULL,
    
    .output_type = MM_TYPE_NONE,     // no output
    .module_type = MM_TYPE_AVSINK,    // module type is video algorithm
	.name = "MP4"
};