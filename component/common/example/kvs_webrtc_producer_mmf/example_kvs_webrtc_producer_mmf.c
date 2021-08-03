 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "platform_opts.h"
#if CONFIG_EXAMPLE_KVS_WEBRTC_PRODUCER_MMF

#include "example_kvs_webrtc_producer_mmf.h"
#include "../media_framework/example_media_framework.h"
#include "module_kvs_producer.h"
#include "module_kvs_webrtc.h"

mm_context_t* kvs_webrtc_v1_a1_ctx      = NULL;
mm_context_t* kvs_producer_v1_ctx       = NULL;
mm_mimo_t* mimo_1v_1a_webrtc_producer   = NULL;

void example_kvs_webrtc_producer_mmf_thread(void *param)
{
#if ISP_BOOT_MODE_ENABLE == 0
	common_init();
#endif

    isp_v1_ctx = mm_module_open(&isp_module);
    if(isp_v1_ctx){
        mm_module_ctrl(isp_v1_ctx, CMD_ISP_SET_PARAMS, (int)&isp_v1_params);
        mm_module_ctrl(isp_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_SW_SLOT);
        mm_module_ctrl(isp_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(isp_v1_ctx, CMD_ISP_APPLY, 0);	// start channel 0
    }else{
        rt_printf("ISP open fail\n\r");
        goto example_kvs_webrtc_producer_mmf;
    }

    h264_v1_ctx = mm_module_open(&h264_module);
    if(h264_v1_ctx){
        mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_PARAMS, (int)&h264_v1_params);
        mm_module_ctrl(h264_v1_ctx, CMD_H264_BITRATE, (int)KVS_WEBRTC_BITRATE);
        mm_module_ctrl(h264_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_H264_QUEUE_LEN);
        mm_module_ctrl(h264_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
        mm_module_ctrl(h264_v1_ctx, CMD_H264_INIT_MEM_POOL, 0);
        mm_module_ctrl(h264_v1_ctx, CMD_H264_APPLY, 0);
    }else{
        rt_printf("H264 open fail\n\r");
        goto example_kvs_webrtc_producer_mmf;
    }

    audio_ctx = mm_module_open(&audio_module);
    if(audio_ctx){
        mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
        mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
        mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
    }else{
        rt_printf("AUDIO open fail\n\r");
        goto example_kvs_webrtc_producer_mmf;
    }

    g711e_ctx = mm_module_open(&g711_module);
    if(g711e_ctx){
        mm_module_ctrl(g711e_ctx, CMD_G711_SET_PARAMS, (int)&g711e_params);
        mm_module_ctrl(g711e_ctx, MM_CMD_SET_QUEUE_LEN, 6);
        mm_module_ctrl(g711e_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(g711e_ctx, CMD_G711_APPLY, 0);
    }else{
        rt_printf("G711 open fail\n\r");
        goto example_kvs_webrtc_producer_mmf;
    }	

    kvs_webrtc_v1_a1_ctx = mm_module_open(&kvs_webrtc_module);
    if(kvs_webrtc_v1_a1_ctx){
        mm_module_ctrl(kvs_webrtc_v1_a1_ctx, CMD_KVS_WEBRTC_SET_APPLY, 0);
    }else{
        rt_printf("KVS open fail\n\r");
        goto example_kvs_webrtc_producer_mmf;
    }

    kvs_producer_v1_ctx = mm_module_open(&kvs_producer_module);
    if(kvs_producer_v1_ctx){
        mm_module_ctrl(kvs_producer_v1_ctx, CMD_KVS_PRODUCER_SET_APPLY, 0);
    }else{
        rt_printf("KVS open fail\n\r");
        goto example_kvs_webrtc_producer_mmf;
    }

    siso_audio_g711e = siso_create();
    if(siso_audio_g711e){
        siso_ctrl(siso_audio_g711e, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
        siso_ctrl(siso_audio_g711e, MMIC_CMD_ADD_OUTPUT, (uint32_t)g711e_ctx, 0);
        siso_start(siso_audio_g711e);
    }else{
        rt_printf("siso_audio_g711e open fail\n\r");
        goto example_kvs_webrtc_producer_mmf;
    }

    siso_isp_h264_v1 = siso_create();
    if(siso_isp_h264_v1){
        siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v1_ctx, 0);
        siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_v1_ctx, 0);
        siso_start(siso_isp_h264_v1);
    }else{
        rt_printf("siso_isp_h264_v1 open fail\n\r");
        goto example_kvs_webrtc_producer_mmf;
    }

    mimo_1v_1a_webrtc_producer = mimo_create();
    if(mimo_1v_1a_webrtc_producer){
        mimo_ctrl(mimo_1v_1a_webrtc_producer, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v1_ctx, 0);
        mimo_ctrl(mimo_1v_1a_webrtc_producer, MMIC_CMD_ADD_INPUT1, (uint32_t)g711e_ctx, 0);
        mimo_ctrl(mimo_1v_1a_webrtc_producer, MMIC_CMD_ADD_OUTPUT0, (uint32_t)kvs_webrtc_v1_a1_ctx, MMIC_DEP_INPUT0|MMIC_DEP_INPUT1);
        mimo_ctrl(mimo_1v_1a_webrtc_producer, MMIC_CMD_ADD_OUTPUT1, (uint32_t)kvs_producer_v1_ctx, MMIC_DEP_INPUT0);
        mimo_start(mimo_1v_1a_webrtc_producer);
    }else{
        rt_printf("mimo open fail\n\r");
        goto example_kvs_webrtc_producer_mmf;
    }
    rt_printf("mimo started\n\r");

example_kvs_webrtc_producer_mmf:

    // TODO: exit condition or signal
    while(1){
        vTaskDelay(1000);
    }
}

void example_kvs_webrtc_producer_mmf(void)
{
    /*user can start their own task here*/
    if(xTaskCreate(example_kvs_webrtc_producer_mmf_thread, ((const char*)"example_kvs_webrtc_producer_mmf_thread"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        printf("\r\n example_kvs_webrtc_producer_mmf_thread: Create Task Error\n");
    }
}

#endif /* CONFIG_EXAMPLE_KVS_WEBRTC_PRODUCER_MMF */