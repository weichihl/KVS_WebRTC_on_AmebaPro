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
#include "platform_opts.h"
#if !CONFIG_EXAMPLE_KVS_WEBRTC

#include "module_kvs_webrtc_audio.h"
#include "avcodec.h"
#include "../../example/kvs_webrtc/example_kvs_webrtc.h"

extern xQueueHandle audio_queue_recv;

void kvs_webrtc_audio_handler(void* p)
{
    kvs_webrtc_audio_ctx_t *ctx = (kvs_webrtc_audio_ctx_t*)p;
    
    unsigned char audio_rev_buf[AUDIO_G711_FRAME_SIZE];

    while (1)
    {
        if(xQueueReceive(audio_queue_recv, audio_rev_buf, 0xFFFFFFFF) != pdTRUE)
            continue;	// should not happen
        
        mm_context_t *mctx = (mm_context_t*)ctx->parent;
        mm_queue_item_t* output_item;
        if(xQueueReceive(mctx->output_recycle, &output_item, 0xFFFFFFFF) == pdTRUE){
            memcpy((void*)output_item->data_addr,(void*)audio_rev_buf, AUDIO_G711_FRAME_SIZE);
            output_item->size = AUDIO_G711_FRAME_SIZE;
            output_item->type = AV_CODEC_ID_PCMU;
            xQueueSend(mctx->output_ready, (void*)&output_item, 0xFFFFFFFF);
        }
    }
}

int kvs_webrtc_audio_control(void *p, int cmd, int arg)
{
    kvs_webrtc_audio_ctx_t *ctx = (kvs_webrtc_audio_ctx_t*)p;

    switch(cmd){

    case CMD_KVS_WEBRTC_SET_APPLY:
        if( xTaskCreate(kvs_webrtc_audio_handler, ((const char*)"kvs_webrtc_audio_handler_thread"), 512, (void*)ctx, tskIDLE_PRIORITY + 1, &ctx->webrtc_audio_handler) != pdPASS){
            printf("\n\r%s xTaskCreate(kvs_webrtc_thread) failed", __FUNCTION__);
        }
        break;
    }
    return 0;
}

void* kvs_webrtc_audio_destroy(void* p)
{
    kvs_webrtc_audio_ctx_t *ctx = (kvs_webrtc_audio_ctx_t*)p;
    if(ctx) free(ctx);
    
    if(ctx->webrtc_audio_handler) vTaskDelete(ctx->webrtc_audio_handler);
    
    return NULL;
}

void* kvs_webrtc_audio_create(void* parent)
{
    kvs_webrtc_audio_ctx_t *ctx = malloc(sizeof(kvs_webrtc_audio_ctx_t));
    if(!ctx) return NULL;
    memset(ctx, 0, sizeof(kvs_webrtc_audio_ctx_t));
    ctx->parent = parent;

    printf("kvs_webrtc_audio_create...\r\n");

    return ctx;
}

int kvs_webrtc_audio_handle(void* ctx, void* input, void* output)
{
    return 0;
}

void* kvs_webrtc_audio_new_item(void *p)
{
	kvs_webrtc_audio_ctx_t *ctx = (kvs_webrtc_audio_ctx_t *)p;
	
    return (void*)malloc(AUDIO_G711_FRAME_SIZE*2);
}

void* kvs_webrtc_audio_del_item(void *p, void *d)
{
	(void)p;
    if(d) free(d);
    return NULL;
}

mm_module_t kvs_webrtc_audio_module = {
    .create = kvs_webrtc_audio_create,
    .destroy = kvs_webrtc_audio_destroy,
    .control = kvs_webrtc_audio_control,
    .handle = kvs_webrtc_audio_handle,
    
    .new_item = kvs_webrtc_audio_new_item,
    .del_item = kvs_webrtc_audio_del_item,

    .output_type = MM_TYPE_ADSP,       // output for audio sink
    .module_type = MM_TYPE_ASRC,      // module type is video algorithm
    .name = "KVS_WebRTC_audio"
};

#endif
