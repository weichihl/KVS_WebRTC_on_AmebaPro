 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "example_media_framework.h"
void audioloop_reset(int sample_rate)
{
	uint8_t smpl_rate_idx = ASR_16KHZ;
	siso_pause(siso_audio_loop);

	switch(sample_rate){
    	case 8000:  smpl_rate_idx = ASR_8KHZ;     break;
    	case 16000: smpl_rate_idx = ASR_16KHZ;    break;
    	case 32000: smpl_rate_idx = ASR_32KHZ;    break;
    	case 44100: smpl_rate_idx = ASR_44p1KHZ;  break;
    	case 48000: smpl_rate_idx = ASR_48KHZ;    break;
    	case 88200: smpl_rate_idx = ASR_88p2KHZ;  break;
    	case 96000: smpl_rate_idx = ASR_96KHZ;    break;
    	default: break;
	}
	mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_SAMPLERATE, smpl_rate_idx);
	mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_RESET, 0);

	siso_resume(siso_audio_loop);
}
void mmf2_example_audioloop_init(void)
{
	audio_ctx = mm_module_open(&audio_module);
	if(audio_ctx){
		mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
		mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
	}else{
		rt_printf("audio open fail\n\r");
		goto mmf2_exmaple_audioloop_fail;
	}

	
	siso_audio_loop = siso_create();
	if(siso_audio_loop){
		siso_ctrl(siso_audio_loop, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
		siso_ctrl(siso_audio_loop, MMIC_CMD_ADD_OUTPUT, (uint32_t)audio_ctx, 0);
		siso_start(siso_audio_loop);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_exmaple_audioloop_fail;
	}
	
	rt_printf("siso1 started\n\r");


	return;
mmf2_exmaple_audioloop_fail:
	
	return;
}