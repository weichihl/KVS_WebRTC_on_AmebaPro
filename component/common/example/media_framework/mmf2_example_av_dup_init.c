#include "example_media_framework.h"
void mmf2_example_av_dup_init(void)
{
	// ------ Channel 1--------------
	isp_v1_ctx = mm_module_open(&isp_module);
	if(isp_v1_ctx){
		mm_module_ctrl(isp_v1_ctx, CMD_ISP_SET_PARAMS, (int)&isp_v1_params);
		mm_module_ctrl(isp_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_SW_SLOT);
		mm_module_ctrl(isp_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(isp_v1_ctx, CMD_ISP_APPLY, 0);	// start channel 0
	}else{
		rt_printf("ISP open fail\n\r");
		goto mmf2_example_av_dup_init;
	}

	h264_v1_ctx = mm_module_open(&h264_module);
	if(h264_v1_ctx){
		mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_PARAMS, (int)&h264_v1_params);
                //two port
                mm_module_ctrl(h264_v1_ctx, MM_CMD_SET_QUEUE_NUM, 2);
                //port one
                mm_module_ctrl(h264_v1_ctx, MM_CMD_SELECT_QUEUE, 0);
		mm_module_ctrl(h264_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_H264_QUEUE_LEN);
                //port two
                mm_module_ctrl(h264_v1_ctx, MM_CMD_SELECT_QUEUE, 1);
		mm_module_ctrl(h264_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_H264_QUEUE_LEN);
		mm_module_ctrl(h264_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(h264_v1_ctx, CMD_H264_INIT_MEM_POOL, 0);
		mm_module_ctrl(h264_v1_ctx, CMD_H264_APPLY, 0);
	}else{
		rt_printf("H264 open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
	
	
	//--------------Audio --------------
	audio_ctx = mm_module_open(&audio_module);
	if(audio_ctx){
		mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
		mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
	}else{
		rt_printf("audio open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
        
        dup_ctx = mm_module_open(&dup_module);
        if(dup_ctx){
                mm_module_ctrl(dup_ctx, CMD_AUDIO_SET_PARAMS, (int)&dup_params);
                //two port
                mm_module_ctrl(dup_ctx, MM_CMD_SET_QUEUE_NUM, 2);
                //port one
                mm_module_ctrl(dup_ctx, MM_CMD_SELECT_QUEUE, 0);
		mm_module_ctrl(dup_ctx, MM_CMD_SET_QUEUE_LEN, 6);
                //port two
                mm_module_ctrl(dup_ctx, MM_CMD_SELECT_QUEUE, 1);
		mm_module_ctrl(dup_ctx, MM_CMD_SET_QUEUE_LEN, 6);
                
		mm_module_ctrl(dup_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(dup_ctx, CMD_AUDIO_APPLY, 0);
        }else{
                rt_printf("dup open fail\n\r");
		goto mmf2_example_av_dup_init;
        }

	aac_ctx = mm_module_open(&aac_module);
	if(aac_ctx){
		mm_module_ctrl(aac_ctx, CMD_AAC_SET_PARAMS, (int)&aac_params);
		mm_module_ctrl(aac_ctx, MM_CMD_SET_QUEUE_LEN, 16);
		mm_module_ctrl(aac_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(aac_ctx, CMD_AAC_INIT_MEM_POOL, 0);
		mm_module_ctrl(aac_ctx, CMD_AAC_APPLY, 0);
	}else{
		rt_printf("AAC open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
        
        g711e_ctx = mm_module_open(&g711_module);
	if(g711e_ctx){
		mm_module_ctrl(g711e_ctx, CMD_G711_SET_PARAMS, (int)&g711e_params);
		mm_module_ctrl(g711e_ctx, MM_CMD_SET_QUEUE_LEN, 16);
		mm_module_ctrl(g711e_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(g711e_ctx, CMD_G711_APPLY, 0);
	}else{
		rt_printf("G711 open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
	
	//--------------RTSP---------------
	rtsp2_v1_ctx = mm_module_open(&rtsp2_module);
	if(rtsp2_v1_ctx){
		mm_module_ctrl(rtsp2_v1_ctx, CMD_RTSP2_SELECT_STREAM, 0);
		mm_module_ctrl(rtsp2_v1_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_v1_params);
		mm_module_ctrl(rtsp2_v1_ctx, CMD_RTSP2_SET_APPLY, 0);

		mm_module_ctrl(rtsp2_v1_ctx, CMD_RTSP2_SELECT_STREAM, 1);
		mm_module_ctrl(rtsp2_v1_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_a_params);
		mm_module_ctrl(rtsp2_v1_ctx, CMD_RTSP2_SET_APPLY, 0);
		
		mm_module_ctrl(rtsp2_v1_ctx, CMD_RTSP2_SET_STREAMMING, ON);
		//mm_module_ctrl(rtsp2_ctx, MM_CMD_SET_QUEUE_LEN, 3);
		//mm_module_ctrl(rtsp2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
	}else{
		rt_printf("RTSP2 open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
	

	rtsp2_v2_ctx = mm_module_open(&rtsp2_module);
	if(rtsp2_v2_ctx){
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SELECT_STREAM, 0);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_v1_params);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_APPLY, 0);
		
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SELECT_STREAM, 1);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_a_pcmu_params);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_APPLY, 0);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_STREAMMING, ON);
		//mm_module_ctrl(rtsp2_v2_ctx, MM_CMD_SET_QUEUE_LEN, 3);
		//mm_module_ctrl(rtsp2_v2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
	}else{
		rt_printf("RTSP2 open fail\n\r");
		goto mmf2_example_av_dup_init;
	}

	//--------------Link---------------------------
	siso_isp_h264_v1 = siso_create();
	if(siso_isp_h264_v1){
		siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v1_ctx, 0);
		siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_v1_ctx, 0);
		siso_start(siso_isp_h264_v1);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
        
///////////////////////Add       
        siso_audio_dup = siso_create();
	if(siso_audio_dup){
		siso_ctrl(siso_audio_dup, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
		siso_ctrl(siso_audio_dup, MMIC_CMD_ADD_OUTPUT, (uint32_t)dup_ctx, 0);
		siso_start(siso_audio_dup);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
//////////////////////// 

	siso_audio_aac = siso_create();
	if(siso_audio_aac){
		//siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 1);
                siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_INPUT, (uint32_t)dup_ctx, 0);
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_OUTPUT, (uint32_t)aac_ctx, 0);
		siso_start(siso_audio_aac);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
       
        
        siso_audio_g711e = siso_create();
	if(siso_audio_g711e){
		//siso_ctrl(siso_audio_g711e, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
                siso_ctrl(siso_audio_g711e, MMIC_CMD_ADD_INPUT, (uint32_t)dup_ctx, 1);
		siso_ctrl(siso_audio_g711e, MMIC_CMD_ADD_OUTPUT, (uint32_t)g711e_ctx, 0);
		siso_start(siso_audio_g711e);
	}else{
		rt_printf("siso_audio_g711e open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
		
	rt_printf("siso started\n\r");

        miso_h264_aac_rtsp = miso_create();
	if(miso_h264_aac_rtsp){
		miso_ctrl(miso_h264_aac_rtsp, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v1_ctx, 1);
		miso_ctrl(miso_h264_aac_rtsp, MMIC_CMD_ADD_INPUT1, (uint32_t)aac_ctx, 0);
		miso_ctrl(miso_h264_aac_rtsp, MMIC_CMD_ADD_OUTPUT, (uint32_t)rtsp2_v1_ctx, 0);
		miso_start(miso_h264_aac_rtsp);
	}else{
		rt_printf("miso open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
        
        miso_h264_g711_rtsp = miso_create();
	if(miso_h264_g711_rtsp){
		miso_ctrl(miso_h264_g711_rtsp, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v1_ctx, 0);
                miso_ctrl(miso_h264_g711_rtsp, MMIC_CMD_ADD_INPUT1, (uint32_t)g711e_ctx, 0);
		miso_ctrl(miso_h264_g711_rtsp, MMIC_CMD_ADD_OUTPUT, (uint32_t)rtsp2_v2_ctx, 0);
		miso_start(miso_h264_g711_rtsp);
	}else{
		rt_printf("miso open fail\n\r");
		goto mmf2_example_av_dup_init;
	}
        
	return;
mmf2_example_av_dup_init:
	rt_printf("mmf2_example_av_dup_init failed\r\n");
	return;
}