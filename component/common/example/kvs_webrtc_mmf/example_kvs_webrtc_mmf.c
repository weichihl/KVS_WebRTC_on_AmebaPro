 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "platform_opts.h"
#if CONFIG_EXAMPLE_KVS_WEBRTC_MMF

#include "../media_framework/example_media_framework.h"
#include "module_kvs_webrtc.h"
#include "module_kvs_webrtc_audio.h"

mm_context_t* kvs_webrtc_v1_a1_ctx      = NULL;
mm_context_t* kvs_webrtc_audio_ctx      = NULL;
mm_miso_t* miso_h264_g711_kvs_v1_a1     = NULL;
mm_siso_t* siso_webrtc_g711d            = NULL;

/*
 * !!!! Please set your AWS key and channel_name in example_kvs_webrtc.h !!!!
*/

/* set the video parameter here, it will overwrite the setting in example_kvs_webrtc.h */
#define WEBRTC_MMF_VIDEO_WIDTH      1280
#define WEBRTC_MMF_VIDEO_HEIGHT     720
#define WEBRTC_MMF_VIDEO_BPS        512*1024
#define WEBRTC_MMF_VIDEO_FPS        30

isp_params_t isp_kvs_webrtc_params = {
	.width    = WEBRTC_MMF_VIDEO_WIDTH, 
	.height   = WEBRTC_MMF_VIDEO_HEIGHT,
	.fps      = WEBRTC_MMF_VIDEO_FPS,
	.slot_num = V1_HW_SLOT,
	.buff_num = V1_SW_SLOT,
	.format   = ISP_FORMAT_YUV420_SEMIPLANAR
};

h264_params_t h264_kvs_webrtc_params = {
	.width          = WEBRTC_MMF_VIDEO_WIDTH,
	.height         = WEBRTC_MMF_VIDEO_HEIGHT,
	.bps            = WEBRTC_MMF_VIDEO_BPS,
	.fps            = WEBRTC_MMF_VIDEO_FPS,
	.gop            = WEBRTC_MMF_VIDEO_FPS,
	.rc_mode        = V1_H264_RCMODE,
    .rotation       = 0,
	.mem_total_size = V1_BUFFER_SIZE,
	.mem_block_size = V1_BLOCK_SIZE,
	.mem_frame_size = V1_FRAME_SIZE,
	.input_type     = ISP_FORMAT_YUV420_SEMIPLANAR
};

void example_kvs_webrtc_mmf_thread(void *param)
{
#if ISP_BOOT_MODE_ENABLE == 0
	common_init();
#endif

    isp_v1_ctx = mm_module_open(&isp_module);
    if(isp_v1_ctx){
        mm_module_ctrl(isp_v1_ctx, CMD_ISP_SET_PARAMS, (int)&isp_kvs_webrtc_params);
        mm_module_ctrl(isp_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_SW_SLOT);
        mm_module_ctrl(isp_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(isp_v1_ctx, CMD_ISP_APPLY, 0);	// start channel 0
    }else{
        rt_printf("ISP open fail\n\r");
        goto example_kvs_webrtc_mmf;
    }

    h264_v1_ctx = mm_module_open(&h264_module);
    if(h264_v1_ctx){
        mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_PARAMS, (int)&h264_kvs_webrtc_params);
        mm_module_ctrl(h264_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_H264_QUEUE_LEN);
        mm_module_ctrl(h264_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
        mm_module_ctrl(h264_v1_ctx, CMD_H264_INIT_MEM_POOL, 0);
        mm_module_ctrl(h264_v1_ctx, CMD_H264_APPLY, 0);
    }else{
        rt_printf("H264 open fail\n\r");
        goto example_kvs_webrtc_mmf;
    }

    audio_ctx = mm_module_open(&audio_module);
    if(audio_ctx){
        mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
        mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_DAC_GAIN, (int)0x40);
        mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
        mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
    }else{
        rt_printf("AUDIO open fail\n\r");
        goto example_kvs_webrtc_mmf;
    }

    g711e_ctx = mm_module_open(&g711_module);
    if(g711e_ctx){
        mm_module_ctrl(g711e_ctx, CMD_G711_SET_PARAMS, (int)&g711e_params);
        mm_module_ctrl(g711e_ctx, MM_CMD_SET_QUEUE_LEN, 6);
        mm_module_ctrl(g711e_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(g711e_ctx, CMD_G711_APPLY, 0);
    }else{
        rt_printf("G711 open fail\n\r");
        goto example_kvs_webrtc_mmf;
    }

    kvs_webrtc_v1_a1_ctx = mm_module_open(&kvs_webrtc_module);
    if(kvs_webrtc_v1_a1_ctx){
        mm_module_ctrl(kvs_webrtc_v1_a1_ctx, CMD_KVS_WEBRTC_SET_VIDEO_HEIGHT, WEBRTC_MMF_VIDEO_HEIGHT);
        mm_module_ctrl(kvs_webrtc_v1_a1_ctx, CMD_KVS_WEBRTC_SET_VIDEO_WIDTH, WEBRTC_MMF_VIDEO_WIDTH);
        mm_module_ctrl(kvs_webrtc_v1_a1_ctx, CMD_KVS_WEBRTC_SET_VIDEO_BPS, WEBRTC_MMF_VIDEO_BPS);
        mm_module_ctrl(kvs_webrtc_v1_a1_ctx, CMD_KVS_WEBRTC_SET_APPLY, 0);
    }else{
        rt_printf("KVS open fail\n\r");
        goto example_kvs_webrtc_mmf;
    }

#ifdef ENABLE_AUDIO_SENDRECV
    kvs_webrtc_audio_ctx = mm_module_open(&kvs_webrtc_audio_module);
    if(kvs_webrtc_audio_ctx){
        mm_module_ctrl(kvs_webrtc_audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(kvs_webrtc_audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(kvs_webrtc_audio_ctx, CMD_KVS_WEBRTC_SET_APPLY, 0);
    }else{
        rt_printf("kvs_webrtc_audio_ctx open fail\n\r");
        goto example_kvs_webrtc_mmf;
    }

    g711d_ctx = mm_module_open(&g711_module);
	if(g711d_ctx){
		mm_module_ctrl(g711d_ctx, CMD_G711_SET_PARAMS, (int)&g711d_params);
		mm_module_ctrl(g711d_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(g711d_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(g711d_ctx, CMD_G711_APPLY, 0);
	}else{
		rt_printf("G711 open fail\n\r");
		goto example_kvs_webrtc_mmf;
	}
#endif

    siso_audio_g711e = siso_create();
    if(siso_audio_g711e){
        siso_ctrl(siso_audio_g711e, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
        siso_ctrl(siso_audio_g711e, MMIC_CMD_ADD_OUTPUT, (uint32_t)g711e_ctx, 0);
        siso_start(siso_audio_g711e);
    }else{
        rt_printf("siso_audio_g711e open fail\n\r");
        goto example_kvs_webrtc_mmf;
    }

    siso_isp_h264_v1 = siso_create();
    if(siso_isp_h264_v1){
        siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v1_ctx, 0);
        siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_v1_ctx, 0);
        siso_start(siso_isp_h264_v1);
    }else{
        rt_printf("siso_isp_h264_v1 open fail\n\r");
        goto example_kvs_webrtc_mmf;
    }

#ifdef ENABLE_AUDIO_SENDRECV  
    siso_webrtc_g711d = siso_create();
	if(siso_webrtc_g711d){
		siso_ctrl(siso_webrtc_g711d, MMIC_CMD_ADD_INPUT, (uint32_t)kvs_webrtc_audio_ctx, 0);
		siso_ctrl(siso_webrtc_g711d, MMIC_CMD_ADD_OUTPUT, (uint32_t)g711d_ctx, 0);
		siso_start(siso_webrtc_g711d);
	}else{
		rt_printf("siso2 open fail\n\r");
		goto example_kvs_webrtc_mmf;
	}

    siso_g711d_audio = siso_create();
	if(siso_g711d_audio){
		siso_ctrl(siso_g711d_audio, MMIC_CMD_ADD_INPUT, (uint32_t)g711d_ctx, 0);
		siso_ctrl(siso_g711d_audio, MMIC_CMD_ADD_OUTPUT, (uint32_t)audio_ctx, 0);
		siso_start(siso_g711d_audio);
	}else{
		rt_printf("siso3 open fail\n\r");
		goto example_kvs_webrtc_mmf;
	}
#endif

    miso_h264_g711_kvs_v1_a1 = miso_create();
    if(miso_h264_g711_kvs_v1_a1){
        miso_ctrl(miso_h264_g711_kvs_v1_a1, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v1_ctx, 0);
        miso_ctrl(miso_h264_g711_kvs_v1_a1, MMIC_CMD_ADD_INPUT1, (uint32_t)g711e_ctx, 0);
        miso_ctrl(miso_h264_g711_kvs_v1_a1, MMIC_CMD_ADD_OUTPUT, (uint32_t)kvs_webrtc_v1_a1_ctx, 0);
        miso_start(miso_h264_g711_kvs_v1_a1);
    }else{
        rt_printf("miso_h264_g711_kvs_v1_a1 open fail\n\r");
        goto example_kvs_webrtc_mmf;
    }
    rt_printf("miso started\n\r");

example_kvs_webrtc_mmf:
	
    // TODO: exit condition or signal
    while(1){
        vTaskDelay(1000);
    }
}

void example_kvs_webrtc_mmf(void)
{
    /*user can start their own task here*/
    if(xTaskCreate(example_kvs_webrtc_mmf_thread, ((const char*)"example_kvs_webrtc_mmf_thread"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        printf("\r\n example_kvs_webrtc_mmf_thread: Create Task Error\n");
    }
}

#endif /* CONFIG_EXAMPLE_KVS_WEBRTC_MMF */