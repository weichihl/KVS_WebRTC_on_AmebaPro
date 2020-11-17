 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "example_media_framework.h"

#include "platform_stdlib.h"
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>
#include "sdio_combine.h"
#include "sdio_host.h"
#include <disk_if/inc/sdcard.h>
#include "fatfs_sdcard_api.h"

//It need to enable the reentrant function for Fatfs config setup
/*
Please modify the below setup
#define	_FS_LOCK	6
#define _FS_REENTRANT	1
#define	_USE_LFN	2
*/

int mp4_open_cb(void* m_file,const char* name,char mode)
{
        f_open(m_file,name,mode);
}
int mp4_write_cb(void* m_file,void* buff,unsigned int btw,unsigned int *bw)
{
        f_write(m_file,buff,btw,bw);
}
int mp4_seek_cb(void* m_file,unsigned int ofs)
{
        f_lseek(m_file,ofs);
}
int mp4_close_cb(void *m_file)
{
        f_close(m_file);
}

static int mp4_stop_cb(void *parm)
{
	printf("Record stop\r\n");
}
static int mp4_end_cb(void *parm)
{
	printf("Record end\r\n");
}

mm_context_t* mp4_ctx_v2    = NULL;
mm_mimo_t* mimo_2s_1a1v_mp4  = NULL;

void mmf2_example_mp4_dual_init(void)
{
	isp_v1_ctx = mm_module_open(&isp_module);
	if(isp_v1_ctx){
		mm_module_ctrl(isp_v1_ctx, CMD_ISP_SET_PARAMS, (int)&isp_v1_params);
		mm_module_ctrl(isp_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_SW_SLOT);
		mm_module_ctrl(isp_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(isp_v1_ctx, CMD_ISP_APPLY, 0);	// start channel 0
	}else{
		rt_printf("ISP open fail\n\r");
		goto mmf2_exmaple_av_mp4_fail;
	}
	
	h264_v1_ctx = mm_module_open(&h264_module);
	if(h264_v1_ctx){
		mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_PARAMS, (int)&h264_v1_params);
		mm_module_ctrl(h264_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_H264_QUEUE_LEN);
		mm_module_ctrl(h264_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(h264_v1_ctx, CMD_H264_INIT_MEM_POOL, 0);
		mm_module_ctrl(h264_v1_ctx, CMD_H264_APPLY, 0);
	}else{
		rt_printf("H264 open fail\n\r");
		goto mmf2_exmaple_av_mp4_fail;
	}	
	
	audio_ctx = mm_module_open(&audio_module);
	if(audio_ctx){
		mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
		mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
	}else{
		rt_printf("AUDIO open fail\n\r");
		goto mmf2_exmaple_av_mp4_fail;
	}
	
	aac_ctx = mm_module_open(&aac_module);
	if(aac_ctx){
		mm_module_ctrl(aac_ctx, CMD_AAC_SET_PARAMS, (int)&aac_params);
		mm_module_ctrl(aac_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(aac_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(aac_ctx, CMD_AAC_INIT_MEM_POOL, 0);
		mm_module_ctrl(aac_ctx, CMD_AAC_APPLY, 0);
	}else{
		rt_printf("AAC open fail\n\r");
		goto mmf2_exmaple_av_mp4_fail;
	}
	
	mp4_ctx = mm_module_open(&mp4_module);
	if(mp4_ctx){
		mm_module_ctrl(mp4_ctx, CMD_MP4_SET_PARAMS, (int)&mp4_v1_params);
		mm_module_ctrl(mp4_ctx, CMD_MP4_START, mp4_v1_params.record_file_num);
		mm_module_ctrl(mp4_ctx, CMD_MP4_SET_STOP_CB,(int)mp4_stop_cb);
		mm_module_ctrl(mp4_ctx, CMD_MP4_SET_END_CB,(int)mp4_end_cb);
		//mm_module_ctrl(mp4_ctx, MM_CMD_SET_QUEUE_LEN, 3);	
		//mm_module_ctrl(mp4_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
	}else{
		rt_printf("MP4 open fail\n\r");
		goto mmf2_exmaple_av_mp4_fail;
	}
	
	mp4_ctx_v2 = mm_module_open(&mp4_module);
	memset(mp4_v2_params.record_file_name,0,sizeof(mp4_v2_params.record_file_name));
	sprintf(mp4_v2_params.record_file_name, "%s","AMEBAPRO_V2");
        mp4_v2_params.mp4_user_callback = 1;//Enable the user callback
	if(mp4_ctx_v2){
		mm_module_ctrl(mp4_ctx_v2, CMD_MP4_SET_PARAMS, (int)&mp4_v2_params);
                mm_module_ctrl(mp4_ctx_v2, CMD_MP4_SET_OPEN_CB,(int)mp4_open_cb);
		mm_module_ctrl(mp4_ctx_v2, CMD_MP4_SET_WRITE_CB,(int)mp4_write_cb);
		mm_module_ctrl(mp4_ctx_v2, CMD_MP4_SET_SEEK_CB,(int)mp4_seek_cb);
		mm_module_ctrl(mp4_ctx_v2, CMD_MP4_SET_CLOSE_CB,(int)mp4_close_cb);
		mm_module_ctrl(mp4_ctx_v2, CMD_MP4_START, mp4_v2_params.record_file_num);
		mm_module_ctrl(mp4_ctx_v2, CMD_MP4_SET_STOP_CB,(int)mp4_stop_cb);
		mm_module_ctrl(mp4_ctx_v2, CMD_MP4_SET_END_CB,(int)mp4_end_cb);
		//mm_module_ctrl(mp4_ctx, MM_CMD_SET_QUEUE_LEN, 3);	
		//mm_module_ctrl(mp4_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
	}else{
		rt_printf("MP4 open fail\n\r");
		goto mmf2_exmaple_av_mp4_fail;
	}
	
	rt_printf("MP4 opened\n\r");
	
	siso_audio_aac = siso_create();
	if(siso_audio_aac){
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_OUTPUT, (uint32_t)aac_ctx, 0);
		siso_start(siso_audio_aac);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_exmaple_av_mp4_fail;
	}
	
	rt_printf("siso_audio_aac started\n\r");
	
	siso_isp_h264_v1 = siso_create();       
	if(siso_isp_h264_v1){
		siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v1_ctx, 0);
		siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_v1_ctx, 0);
		siso_start(siso_isp_h264_v1);
	}else{
		rt_printf("siso2 open fail\n\r");
		goto mmf2_exmaple_av_mp4_fail;
	}
	
	rt_printf("siso_isp_h264_v1 started\n\r");

	mimo_2s_1a1v_mp4 = mimo_create();
	if(mimo_2s_1a1v_mp4){
		mimo_ctrl(mimo_2s_1a1v_mp4, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v1_ctx, 0);
		mimo_ctrl(mimo_2s_1a1v_mp4, MMIC_CMD_ADD_INPUT1, (uint32_t)aac_ctx, 0);
		mimo_ctrl(mimo_2s_1a1v_mp4, MMIC_CMD_ADD_OUTPUT0, (uint32_t)mp4_ctx, MMIC_DEP_INPUT0|MMIC_DEP_INPUT1);
		mimo_ctrl(mimo_2s_1a1v_mp4, MMIC_CMD_ADD_OUTPUT1, (uint32_t)mp4_ctx_v2, MMIC_DEP_INPUT0|MMIC_DEP_INPUT1);
		mimo_start(mimo_2s_1a1v_mp4);
	}else{
		rt_printf("mimo open fail\n\r");
		goto mmf2_exmaple_av_mp4_fail;
	}

	rt_printf("mimo_2s_1a1v_mp4 started\n\r");
	
	return;
mmf2_exmaple_av_mp4_fail:
	
	return;
}