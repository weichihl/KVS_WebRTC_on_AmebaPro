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

mm_context_t* kvs_producer_v1_ctx  = NULL;
mm_siso_t* siso_h264_kvs_v1        = NULL;

void example_kvs_producer_mmf_thread(void *param)
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
        goto example_kvs_producer_mmf;
    }

    h264_v1_ctx = mm_module_open(&h264_module);
    if(h264_v1_ctx){
        mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_PARAMS, (int)&h264_v1_params);
        mm_module_ctrl(h264_v1_ctx, CMD_H264_BITRATE, (int)(1*1024*1024));
        mm_module_ctrl(h264_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_H264_QUEUE_LEN);
        mm_module_ctrl(h264_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
        mm_module_ctrl(h264_v1_ctx, CMD_H264_INIT_MEM_POOL, 0);
        mm_module_ctrl(h264_v1_ctx, CMD_H264_APPLY, 0);
    }else{
        rt_printf("H264 open fail\n\r");
        goto example_kvs_producer_mmf;
    }
    
    kvs_producer_v1_ctx = mm_module_open(&kvs_producer_module);
    if(kvs_producer_v1_ctx){
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
    
    siso_h264_kvs_v1 = siso_create();
    if(siso_h264_kvs_v1){
        siso_ctrl(siso_h264_kvs_v1, MMIC_CMD_ADD_INPUT, (uint32_t)h264_v1_ctx, 0);
        siso_ctrl(siso_h264_kvs_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)kvs_producer_v1_ctx, 0);
        siso_start(siso_h264_kvs_v1);
    }else{
        rt_printf("siso2 open fail\n\r");
        goto example_kvs_producer_mmf;
    }

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