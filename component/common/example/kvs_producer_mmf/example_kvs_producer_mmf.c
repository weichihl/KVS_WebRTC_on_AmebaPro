 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "platform_opts.h"
#if CONFIG_EXAMPLE_KVS_PRODUCER_MMF

#include "example_kvs_producer_mmf.h"
#include "../media_framework/example_media_framework.h"
#include "module_kvs_producer.h"
#include "../kvs_producer/sample_config.h"

mm_context_t* kvs_producer_v1_ctx       = NULL;
mm_siso_t* siso_h264_kvs_v1             = NULL;
mm_miso_t* miso_h264_aac_kvs_v1_a1      = NULL;

/*
 * !!!! Please set your AWS key, KVS_STREAM_NAME, AWS_KVS_REGION, ENABLE_AUDIO_TRACK and ENABLE_IOT_CREDENTIAL in sample_config.h !!!!
*/

/* set the video parameter here, it will overwrite the setting in sample_config.h */
#define PRODUCER_MMF_VIDEO_WIDTH      1920
#define PRODUCER_MMF_VIDEO_HEIGHT     1080
#define PRODUCER_MMF_VIDEO_BPS        1*1024*1024
#define PRODUCER_MMF_VIDEO_FPS        30

isp_params_t kvs_isp_params = {
    .width    = PRODUCER_MMF_VIDEO_WIDTH, 
    .height   = PRODUCER_MMF_VIDEO_HEIGHT,
    .fps      = PRODUCER_MMF_VIDEO_FPS,
    .slot_num = V1_HW_SLOT,
    .buff_num = V1_SW_SLOT,
    .format   = ISP_FORMAT_YUV420_SEMIPLANAR
};

h264_params_t kvs_h264_params = {
    .width          = PRODUCER_MMF_VIDEO_WIDTH,
    .height         = PRODUCER_MMF_VIDEO_HEIGHT,
    .bps            = PRODUCER_MMF_VIDEO_BPS,
    .fps            = PRODUCER_MMF_VIDEO_FPS,
    .gop            = PRODUCER_MMF_VIDEO_FPS,
    .rc_mode        = V1_H264_RCMODE,
    .rotation       = 0,
    .mem_total_size = V1_BUFFER_SIZE,
    .mem_block_size = V1_BLOCK_SIZE,
    .mem_frame_size = V1_FRAME_SIZE,
    .input_type     = ISP_FORMAT_YUV420_SEMIPLANAR
};

#if ENABLE_AUDIO_TRACK
aac_params_t kvs_aac_params = {
    .sample_rate = AUDIO_SAMPLING_RATE,
    .channel = AUDIO_CHANNEL_NUMBER,
    .bit_length = FAAC_INPUT_16BIT,
    .output_format = 0,   //Bitstream output format (0 = Raw; 1 = ADTS)
    .mpeg_version = MPEG4,
    .mem_total_size = 10*1024,
    .mem_block_size = 128,
    .mem_frame_size = 1024
};
#endif

void example_kvs_producer_mmf_thread(void *param)
{
#if ISP_BOOT_MODE_ENABLE == 0
    common_init();
#endif

    isp_v1_ctx = mm_module_open(&isp_module);
    if(isp_v1_ctx){
        mm_module_ctrl(isp_v1_ctx, CMD_ISP_SET_PARAMS, (int)&kvs_isp_params);
        mm_module_ctrl(isp_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_SW_SLOT);
        mm_module_ctrl(isp_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(isp_v1_ctx, CMD_ISP_APPLY, 0);	// start channel 0
    }else{
        rt_printf("ISP open fail\n\r");
        goto example_kvs_producer_mmf;
    }

    h264_v1_ctx = mm_module_open(&h264_module);
    if(h264_v1_ctx){
        mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_PARAMS, (int)&kvs_h264_params);
        mm_module_ctrl(h264_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_H264_QUEUE_LEN);
        mm_module_ctrl(h264_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
        mm_module_ctrl(h264_v1_ctx, CMD_H264_INIT_MEM_POOL, 0);
        mm_module_ctrl(h264_v1_ctx, CMD_H264_APPLY, 0);
    }else{
        rt_printf("H264 open fail\n\r");
        goto example_kvs_producer_mmf;
    }

#if ENABLE_AUDIO_TRACK
    audio_ctx = mm_module_open(&audio_module);
    if(audio_ctx){
        mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
        mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
        mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
    }else{
        rt_printf("AUDIO open fail\n\r");
        goto example_kvs_producer_mmf;
    }
    
    aac_ctx = mm_module_open(&aac_module);
    if(aac_ctx){
        mm_module_ctrl(aac_ctx, CMD_AAC_SET_PARAMS, (int)&kvs_aac_params);
        mm_module_ctrl(aac_ctx, MM_CMD_SET_QUEUE_LEN, 6);
        mm_module_ctrl(aac_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
        mm_module_ctrl(aac_ctx, CMD_AAC_INIT_MEM_POOL, 0);
        mm_module_ctrl(aac_ctx, CMD_AAC_APPLY, 0);
    }else{
        rt_printf("AAC open fail\n\r");
        goto example_kvs_producer_mmf;
    }
    
    siso_audio_aac = siso_create();
    if(siso_audio_aac){
        siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
        siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_OUTPUT, (uint32_t)aac_ctx, 0);
        siso_start(siso_audio_aac);
    }else{
        rt_printf("siso1 open fail\n\r");
        goto example_kvs_producer_mmf;
    }
#endif
    
    kvs_producer_v1_ctx = mm_module_open(&kvs_producer_module);
    if(kvs_producer_v1_ctx){
        mm_module_ctrl(kvs_producer_v1_ctx, CMD_KVS_PRODUCER_SET_VIDEO_HEIGHT, PRODUCER_MMF_VIDEO_HEIGHT);
        mm_module_ctrl(kvs_producer_v1_ctx, CMD_KVS_PRODUCER_SET_VIDEO_WIDTH, PRODUCER_MMF_VIDEO_WIDTH);
        mm_module_ctrl(kvs_producer_v1_ctx, CMD_KVS_PRODUCER_SET_APPLY, 0);
    }else{
        rt_printf("KVS open fail\n\r");
        goto example_kvs_producer_mmf;
    }

    siso_isp_h264_v1 = siso_create();
    if(siso_isp_h264_v1){
        siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v1_ctx, 0);
        siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_v1_ctx, 0);
        siso_start(siso_isp_h264_v1);
    }else{
        rt_printf("siso1 open fail\n\r");
        goto example_kvs_producer_mmf;
    }
    
#if ENABLE_AUDIO_TRACK
    miso_h264_aac_kvs_v1_a1 = miso_create();
    if(miso_h264_aac_kvs_v1_a1){
        miso_ctrl(miso_h264_aac_kvs_v1_a1, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v1_ctx, 0);
        miso_ctrl(miso_h264_aac_kvs_v1_a1, MMIC_CMD_ADD_INPUT1, (uint32_t)aac_ctx, 0);
        miso_ctrl(miso_h264_aac_kvs_v1_a1, MMIC_CMD_ADD_OUTPUT, (uint32_t)kvs_producer_v1_ctx, 0);
        miso_start(miso_h264_aac_kvs_v1_a1);
    }else{
        rt_printf("miso_h264_aac_kvs_v1_a1 open fail\n\r");
        goto example_kvs_producer_mmf;
    }
    rt_printf("miso started\n\r");
#else
    siso_h264_kvs_v1 = siso_create();
    if(siso_h264_kvs_v1){
        siso_ctrl(siso_h264_kvs_v1, MMIC_CMD_ADD_INPUT, (uint32_t)h264_v1_ctx, 0);
        siso_ctrl(siso_h264_kvs_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)kvs_producer_v1_ctx, 0);
        siso_start(siso_h264_kvs_v1);
    }else{
        rt_printf("siso2 open fail\n\r");
        goto example_kvs_producer_mmf;
    }
    rt_printf("siso started\n\r");
#endif

example_kvs_producer_mmf:
	
    // TODO: exit condition or signal
    while(1)
    {
        vTaskDelay(1000);
    }
}

void example_kvs_producer_mmf(void)
{
    /*user can start their own task here*/
    if(xTaskCreate(example_kvs_producer_mmf_thread, ((const char*)"example_kvs_producer_mmf_thread"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        printf("\r\n example_kvs_producer_mmf_thread: Create Task Error\n");
    }
}

#endif /* CONFIG_EXAMPLE_KVS_PRODUCER_MMF */