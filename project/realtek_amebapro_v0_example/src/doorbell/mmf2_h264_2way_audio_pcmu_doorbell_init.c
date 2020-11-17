 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "media_framework/example_media_framework.h"
#include "doorbell_demo.h"
#include "app_setting.h"
#include <wifi_conf.h>
   
int sd_ready = 0;   
extern int amp_gpio_enable(int enable);
extern int led_communication_enable(int enable);
extern int led_button_enable(int enable);
extern void send_icc_cmd_poweroff(void);
extern int set_playback_state(void);
 
static uint8_t processing = 0;
static uint8_t mp4_running = 0;
static uint32_t file_count = 0;
static char sd_filename[64];
static char sd_dirname[32];
static fatfs_sd_params_t fatfs_sd;
extern doorbell_ctr_t doorbell_handle;

#define AAC_RECORD 1
#define ENABLE_MP4_RECORD 1 

int isp_suspend_func(void *parm)
{
#if 0  
	if(sd_ready)
	{
	    mm_module_ctrl(isp_v1_ctx, CMD_ISP_STREAM_STOP, 0);
	    siso_stop(siso_isp_h264_v1);
	    mm_module_ctrl(isp_v2_ctx, CMD_ISP_STREAM_STOP, 0);
	    siso_stop(siso_isp_h264_v2);
	    mm_module_close(isp_v1_ctx);
	    mm_module_close(isp_v2_ctx);
	}
	else
	{
#if ENABLE_MP4_RECORD
	    mm_module_ctrl(isp_v2_ctx, CMD_ISP_STREAM_STOP, 0);
	    siso_stop(siso_isp_h264_v2);
	    mm_module_close(isp_v2_ctx);
#else
	    mm_module_ctrl(isp_v1_ctx, CMD_ISP_STREAM_STOP, 0);
	    siso_stop(siso_isp_h264_v1);
	    mm_module_close(isp_v1_ctx);	    
#endif	    
	}
#endif	
	video_subsys_deinit(NULL);
        return 0;
} 

static int rtsp_suspend_func(void *parm)
{
#if DOORBELL_AMP_ENABLE
        amp_gpio_enable(0);
#endif
        printf("Disable the amp\r\n");
#if ENABLE_MP4_RECORD	
        mm_module_ctrl(isp_v2_ctx, CMD_ISP_STREAM_STOP, 0);
        siso_pause(siso_isp_h264_v2);
	mm_module_ctrl(isp_v2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
	mm_module_ctrl(h264_v2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
#else
        mm_module_ctrl(isp_v1_ctx, CMD_ISP_STREAM_STOP, 0);
        siso_pause(siso_isp_h264_v1);
	mm_module_ctrl(isp_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
	mm_module_ctrl(h264_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
#endif	
        return 0; 
}

static int rtsp_start_func(void *parm)
{
#if DOORBELL_AMP_ENABLE
        amp_gpio_enable(1);
#endif
        printf("Enable the amp\r\n");
#if ENABLE_MP4_RECORD
	mm_module_ctrl(h264_v2_ctx, CMD_H264_UPDATE, 0);
        mm_module_ctrl(isp_v2_ctx, CMD_ISP_UPDATE, 1);
	siso_resume(siso_isp_h264_v2);
#else
        mm_module_ctrl(h264_v1_ctx, CMD_H264_UPDATE, 0);
	mm_module_ctrl(isp_v1_ctx, CMD_ISP_UPDATE, 1);
	siso_resume(siso_isp_h264_v1); 
#endif
	
	
        return 0; 
}

int check_doorbell_mmf_status(void)
{
	if(doorbell_handle.doorbell_state & STATE_MEDIA_READY){
	  	return 1;
	}
	else{
	  	return 0;
	}	  	
}

void start_doorbell_ring(void)
{
	int state = 0;
	int timeout = 0;
	mm_module_ctrl(array_ctx, CMD_ARRAY_GET_STATE, (int)&state);
	if (state) {
		printf("doorbell is ringing\n\r");
	}
	else {
#if DOORBELL_AMP_ENABLE
                amp_gpio_enable(1);
#endif
                led_blue_enable(1);		
		//vTaskDelay(200); 		
		printf("start doorbell_ring\n\r");
		miso_resume(miso_rtp_array_g711d);
		miso_pause(miso_rtp_array_g711d,MM_INPUT0);	// pause audio from rtp
		mm_module_ctrl(array_ctx, CMD_ARRAY_STREAMING, 1);	// doorbell ring
		timeout = 0;
		do {	// wait until doorbell_ring done 
		        timeout++;
			vTaskDelay(100);
			led_blue_enable(1);
			mm_module_ctrl(array_ctx, CMD_ARRAY_GET_STATE, (int)&state);
			if( timeout > 50)
			{
			  	mm_module_ctrl(array_ctx, CMD_ARRAY_STREAMING, 0);
			  	break;
			}
		} while (state==1);
		
		miso_resume(miso_rtp_array_g711d);
		miso_pause(miso_rtp_array_g711d,MM_INPUT1);	// pause array
		//vTaskDelay(800);	
                led_blue_enable(0);
		printf("doorbell_ring done!\n\r");
#if DOORBELL_AMP_ENABLE
                amp_gpio_enable(0);
#endif		
	}
}

static void del_old_file(void)
{
	DIR m_dir;
	FILINFO m_fileinfo;
	char *filename;
	char old_filename[32] = {0};
	char old_filepath[32] = {0};
	WORD filedate = 0, filetime = 0, old_filedate = 0, old_filetime = 0;
#if _USE_LFN
	char fname_lfn[32];
	m_fileinfo.lfname = fname_lfn;
	m_fileinfo.lfsize = sizeof(fname_lfn);
#endif

	if(f_opendir(&m_dir, sd_dirname) == 0) {
		while(1) {
			if((f_readdir(&m_dir, &m_fileinfo) != 0) || m_fileinfo.fname[0] == 0) {
				break;
			}

#if _USE_LFN
			filename = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
			filename = m_fileinfo.fname;
#endif
			if(*filename == '.' || *filename == '..') {
				continue;
			}

			if(!(m_fileinfo.fattrib & AM_DIR)) {
				filedate = m_fileinfo.fdate;
				filetime = m_fileinfo.ftime;

				if(	(strlen(old_filename) == 0) ||
					(filedate < old_filedate) ||
					((filedate == old_filedate) && (filetime < old_filetime))) {

					old_filedate = filedate;
					old_filetime = filetime;
					strcpy(old_filename, filename);
				}
			}
		}

		f_closedir(&m_dir);

		if(strlen(old_filename)) {
			sprintf(old_filepath, "%s/%s", sd_dirname, old_filename);
			printf("del %s\n\r", old_filepath);
			f_unlink(old_filepath);
		}
	}
}

static int mp4_end_cb(void *parm)
{
	if(processing) {
		if(fatfs_get_free_space() < 50)
			del_old_file();

		if(fatfs_get_free_space() < 50) {
			printf("ERROR: free space < 50MB\n\r");
			processing = 0;
			//led_stop_recording();
			return 0;
		}

		file_count ++;
		mp4_v1_params.record_file_num = 1;
		sprintf(mp4_v1_params.record_file_name, "%s_%d", sd_filename, file_count);
		mm_module_ctrl(mp4_ctx, CMD_MP4_SET_PARAMS, (int) &mp4_v1_params);
		mm_module_ctrl(mp4_ctx, CMD_MP4_SET_END_CB,(int) mp4_end_cb);
		mm_module_ctrl(mp4_ctx, CMD_MP4_START, mp4_v1_params.record_file_num);
	}
	else {
		mp4_running = 0;
		//mm_module_ctrl(h264_v2_ctx, CMD_H264_PAUSE, 1);
	}

	return 0;
}

void mp4_record_start(char *filename)
{
	int i;
	
	//mm_module_ctrl(isp_v1_ctx, CMD_ISP_STREAM_START, 0);
	
	for(i = (strlen(filename) - 1); i >= 0; i --) {
		if(filename[i] == '/') {
			fatfs_sd_get_param(&fatfs_sd);
			memset(sd_dirname, 0, sizeof(sd_dirname));
			strcpy(sd_dirname, fatfs_sd.drv);
			memcpy(sd_dirname + strlen(sd_dirname), filename, i);
			break;
		}
	}

	printf("fatfs_get_free_space\r\n");
	if(fatfs_get_free_space() < 50)
		del_old_file();
	
	printf("fatfs_get_free_space2\r\n");
	
	if(fatfs_get_free_space() < 50) {
		printf("ERROR: free space < 50MB\n\r");
		processing = 0;
		//led_stop_recording();
		return;
	}

	file_count = 0;
	mp4_v1_params.record_file_num = 1;
	strcpy(sd_filename, filename);
	sprintf(mp4_v1_params.record_file_name, "%s_%d", sd_filename, file_count);

	//sprintf(mp4_v1_params.record_file_name, "%s", sd_filename);
	mm_module_ctrl(mp4_ctx, CMD_MP4_SET_PARAMS, (int) &mp4_v1_params);
	mm_module_ctrl(mp4_ctx, CMD_MP4_SET_END_CB,(int) mp4_end_cb);
	mm_module_ctrl(mp4_ctx, CMD_MP4_START, mp4_v1_params.record_file_num);
	printf("start mp4 record\n");
	mp4_running = 1;
	processing = 1;
}

void mp4_record_stop(void)
{
	if(processing) {
		processing = 0;
		mp4_running = 0;
		mm_module_ctrl(mp4_ctx, CMD_MP4_STOP, NULL);
		mm_module_ctrl(isp_v2_ctx, CMD_ISP_STREAM_STOP, 0);
	    siso_stop(siso_isp_h264_v2);
	    mm_module_close(isp_v2_ctx);
	}
}

uint8_t mp4_record_running(void)
{
	return mp4_running;
}


extern isp_boot_cfg_t isp_boot_cfg_global; 

void mmf2_h264_2way_audio_pcmu_doorbell_init(void)
{
 	int i = 0;
  	int sdst = 0; 
	
	// ------ Channel 1--------------
	isp_v1_ctx = mm_module_open(&isp_module);
#if ISP_BOOT_MODE_ENABLE	
	isp_v1_params.boot_mode = isp_check_boot_status();
#endif	
	if(isp_v1_ctx){
		mm_module_ctrl(isp_v1_ctx, CMD_ISP_SET_PARAMS, (int)&isp_v1_params);
#if ISP_BOOT_MODE_ENABLE		
		if(isp_v1_params.boot_mode == ISP_FAST_BOOT){
			for(i=0;i<isp_boot_cfg_global.isp_config.hw_slot_num;i++)
				mm_module_ctrl(isp_v1_ctx, CMD_ISP_SET_SELF_BUF, isp_boot_cfg_global.isp_buffer[i]);
			}
#endif		
		mm_module_ctrl(isp_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_SW_SLOT);
		mm_module_ctrl(isp_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(isp_v1_ctx, CMD_ISP_APPLY, 0);	// start channel 0		
		isp_v1_params.boot_mode = ISP_NORMAL_BOOT;	
	}else{
		rt_printf("ISP open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}
	
	rt_printf("isp_v1_ctx\n"); 
	//set WDR
	isp_set_WDR_mode(1);
	isp_set_WDR_level(0x10); 

#if ENABLE_MP4_RECORD	
	if(fatfs_sd_init()<0){
	        sd_ready = 0; 
	}
	else
	{
	        sdst = SD_Status(); 
	        rt_printf("sdst = %d\n\r",sdst);
	  	if(SD_Status() == 0)
		{
			sd_ready = 1;  
		}
		else
		{  
	  		sd_ready = 0;
		}
	}
		    
	if(sd_ready) 
	{	    
	    h264_v1_ctx = mm_module_open(&h264_module);
	    h264_rc_parm_t rc_parm;
	    h264_rc_adv_parm_t rc_adv_param;
	    rc_parm.rcMode = RC_MODE_H264VBR;  
	    rc_parm.minQp = 20;
	    rc_parm.maxQp = 40;
	    rc_parm.minIQp = 20;
	    
	    rc_adv_param.maxBps = h264_v1_params.bps;
	    rc_adv_param.minBps = h264_v1_params.bps*3/4; 
	    rc_adv_param.intraQpDelta = -6; 
	    rc_adv_param.mbQpAdjustment = -1;
	    rc_adv_param.mbQpAutoBoost = 0;
	    
	    //h264_v1_params.gop = h264_v1_params.fps*2;

	    if(h264_v1_ctx){
		    mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_PARAMS, (int)&h264_v1_params); 
		    mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_RCPARAM, (int)&rc_parm);
		    mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_RCADVPARAM, (int)&rc_adv_param);
		    mm_module_ctrl(h264_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_H264_QUEUE_LEN);
		    mm_module_ctrl(h264_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		    mm_module_ctrl(h264_v1_ctx, CMD_H264_INIT_MEM_POOL, 0);
		    mm_module_ctrl(h264_v1_ctx, CMD_H264_APPLY, 0);
	    }else{
		    rt_printf("H264 open fail\n\r");
		    goto mmf2_example_h264_two_way_audio_pcmu_fail;
	    }
	    
	    rt_printf("h264_v1_ctx\n");	
	}
	else	  
	{
	    mm_module_ctrl(isp_v1_ctx, CMD_ISP_STREAM_STOP, 0);
	}
  
         // ------ Channel 2--------------
	rt_printf("isp v2 width = %d height = %d\r\n",isp_v2_params.width,isp_v2_params.height);
	isp_v2_ctx = mm_module_open(&isp_module);
	if(isp_v2_ctx){
		mm_module_ctrl(isp_v2_ctx, CMD_ISP_SET_PARAMS, (int)&isp_v2_params);
		mm_module_ctrl(isp_v2_ctx, MM_CMD_SET_QUEUE_LEN, V2_SW_SLOT);
		mm_module_ctrl(isp_v2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(isp_v2_ctx, CMD_ISP_APPLY, 1);	// start channel 1
	}else{
		rt_printf("ISP open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail; 
	}
		
	h264_v2_ctx = mm_module_open(&h264_module);
	h264_rc_parm_t rc_parm2;
	h264_rc_adv_parm_t rc_adv_param2;
	rc_parm2.rcMode = RC_MODE_H264CBR;
	rc_parm2.minQp = 20;
	rc_parm2.maxQp = 40;
	rc_parm2.minIQp = 20;
	//rc_adv_param2.maxBps = h264_v2_params.bps;
	//rc_adv_param2.minBps = h264_v2_params.bps*3/4;
	rc_adv_param2.intraQpDelta = -6;
	rc_adv_param2.mbQpAdjustment = -1;
	rc_adv_param2.mbQpAutoBoost = 0;
	//h264_v1_params.gop = h264_v1_params.fps*2;
	
	if(h264_v2_ctx){
		mm_module_ctrl(h264_v2_ctx, CMD_H264_SET_PARAMS, (int)&h264_v2_params);
		mm_module_ctrl(h264_v2_ctx, CMD_H264_SET_RCPARAM, (int)&rc_parm2);
		mm_module_ctrl(h264_v2_ctx, CMD_H264_SET_RCADVPARAM, (int)&rc_adv_param2);
		mm_module_ctrl(h264_v2_ctx, MM_CMD_SET_QUEUE_LEN, V2_H264_QUEUE_LEN);
		mm_module_ctrl(h264_v2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(h264_v2_ctx, CMD_H264_INIT_MEM_POOL, 0);
		mm_module_ctrl(h264_v2_ctx, CMD_H264_APPLY, 0); 
	}else{
		rt_printf("H264 open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}
	
	rt_printf("h264_v2_ctx\n");
#else
	    h264_v1_ctx = mm_module_open(&h264_module);
	    h264_rc_parm_t rc_parm;
	    h264_rc_adv_parm_t rc_adv_param;
	    rc_parm.rcMode = RC_MODE_H264CBR;  
	    rc_parm.minQp = 20;
	    rc_parm.maxQp = 40;
	    rc_parm.minIQp = 20;
	    
	    //rc_adv_param.maxBps = h264_v1_params.bps;
	    //rc_adv_param.minBps = h264_v1_params.bps*3/4;
	    rc_adv_param.intraQpDelta = -2;
	    rc_adv_param.mbQpAdjustment = -1;
	    rc_adv_param.mbQpAutoBoost = 0; 
	    
	    //h264_v1_params.gop = h264_v1_params.fps*2;

	    if(h264_v1_ctx){
		    mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_PARAMS, (int)&h264_v1_params); 
		    mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_RCPARAM, (int)&rc_parm);
		    mm_module_ctrl(h264_v1_ctx, CMD_H264_SET_RCADVPARAM, (int)&rc_adv_param);
		    mm_module_ctrl(h264_v1_ctx, MM_CMD_SET_QUEUE_LEN, V1_H264_QUEUE_LEN);
		    mm_module_ctrl(h264_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		    mm_module_ctrl(h264_v1_ctx, CMD_H264_INIT_MEM_POOL, 0);
		    mm_module_ctrl(h264_v1_ctx, CMD_H264_APPLY, 0);
	    }else{
		    rt_printf("H264 open fail\n\r");
		    goto mmf2_example_h264_two_way_audio_pcmu_fail;
	    }
	    
	    rt_printf("h264_v1_ctx\n");		
	
#endif
	    
#ifdef DOORBELL_TARGET_BROAD
	isp_set_flip(FILP_NUM);
#endif	
	
#if CONFIG_LIGHT_SENSOR
	init_sensor_service();
#else
	ir_cut_init(NULL);
	ir_cut_enable(1);
#endif

	//--------------Audio --------------
	audio_ctx = mm_module_open(&audio_module);
	if(audio_ctx){
		mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params); 
		mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
	}else{
		rt_printf("audio open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}
	
	rt_printf("audio_ctx\n");
	
#if AAC_RECORD		
	aac_ctx = mm_module_open(&aac_module);
	if(aac_ctx){
		mm_module_ctrl(aac_ctx, CMD_AAC_SET_PARAMS, (int)&aac_params);
		mm_module_ctrl(aac_ctx, MM_CMD_SET_QUEUE_LEN, 16);
		mm_module_ctrl(aac_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(aac_ctx, CMD_AAC_INIT_MEM_POOL, 0);
		mm_module_ctrl(aac_ctx, CMD_AAC_APPLY, 0);
	}else{
		rt_printf("AAC open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}
	
	rt_printf("aac_ctx\n");
#else
	g711e_ctx = mm_module_open(&g711_module);
	if(g711e_ctx){
		mm_module_ctrl(g711e_ctx, CMD_G711_SET_PARAMS, (int)&g711e_params);
		mm_module_ctrl(g711e_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(g711e_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(g711e_ctx, CMD_G711_APPLY, 0);
	}else{
		rt_printf("G711 open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}	
#endif	
		
	//--------------RTSP---------------

	rtsp2_v2_ctx = mm_module_open(&rtsp2_module);
	if(rtsp2_v2_ctx){
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SELECT_STREAM, 0);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_v2_params);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_APPLY, 0);
		
		//mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_DROP_TIME, 100);		
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SELECT_STREAM, 1);
#if AAC_RECORD
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_a_params);
#else		
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_a_pcmu_params);
#endif		
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_APPLY, 0);
		
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_STOP_CB, (int)rtsp_suspend_func);
                mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_START_CB, (int)rtsp_start_func);
		
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_STREAMMING, ON);
	}else{
		rt_printf("RTSP2 open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}		
	
	rt_printf("rtsp2_v2_ctx\n");

#if ENABLE_MP4_RECORD	
        //--------------MP4---------------	
	if(sd_ready)
	{
	    mp4_ctx = mm_module_open(&mp4_module);
	    if(mp4_ctx){
		    //mm_module_ctrl(mp4_ctx, CMD_MP4_SET_PARAMS, (int)&mp4_v1_params); 
		    //mm_module_ctrl(mp4_ctx, CMD_MP4_START, mp4_v1_params.record_file_num);
	    }else{
		    rt_printf("MP4 open fail\n\r");
		    goto mmf2_example_h264_two_way_audio_pcmu_fail;
	    }
	    
	    rt_printf("mp4_ctx\n");
	    
	    //--------------HTTP File Server---------------
	    httpfs_ctx = mm_module_open(&httpfs_module);
	    if(httpfs_ctx){
		    mm_module_ctrl(httpfs_ctx, CMD_HTTPFS_SET_PARAMS, (int)&httpfs_params);
		    mm_module_ctrl(httpfs_ctx, CMD_HTTPFS_SET_RESPONSE_CB, (int)set_playback_state);
		    mm_module_ctrl(httpfs_ctx, CMD_HTTPFS_APPLY, 0);
	    }else{
		    rt_printf("HTTPFS open fail\n\r");
		    goto mmf2_example_h264_two_way_audio_pcmu_fail;
	    }
	}
	
	//--------------Link---------------------------
	if(sd_ready)
	{
		siso_isp_h264_v1 = siso_create();
		if(siso_isp_h264_v1){
			siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v1_ctx, 0);
			siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_v1_ctx, 0);
			siso_start(siso_isp_h264_v1);
		}else{
			rt_printf("siso_isp_h264_v1 open fail\n\r");
			goto mmf2_example_h264_two_way_audio_pcmu_fail;
		}
	
		rt_printf("siso_isp_h264_v1 started\n\r");
	}

	siso_isp_h264_v2 = siso_create();
	if(siso_isp_h264_v2){
		siso_ctrl(siso_isp_h264_v2, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v2_ctx, 0);
		siso_ctrl(siso_isp_h264_v2, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_v2_ctx, 0);
		siso_start(siso_isp_h264_v2);
	}else{
		rt_printf("siso2 open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}
	
	rt_printf("siso_isp_h264_v2 started\n\r");
	
	rtsp_suspend_func(NULL);
#else
		siso_isp_h264_v1 = siso_create();
		if(siso_isp_h264_v1){
			siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v1_ctx, 0);
			siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_v1_ctx, 0);
			siso_start(siso_isp_h264_v1);
		}else{
			rt_printf("siso_isp_h264_v1 open fail\n\r");
			goto mmf2_example_h264_two_way_audio_pcmu_fail;
		}
	
		rt_printf("siso_isp_h264_v1 started\n\r");
		
		rtsp_suspend_func(NULL);
#endif	

#if AAC_RECORD	
	siso_audio_aac = siso_create();
	if(siso_audio_aac){
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_OUTPUT, (uint32_t)aac_ctx, 0);
		siso_start(siso_audio_aac);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}	
#else
	siso_audio_g711e = siso_create();
	if(siso_audio_g711e){
		siso_ctrl(siso_audio_g711e, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
		siso_ctrl(siso_audio_g711e, MMIC_CMD_ADD_OUTPUT, (uint32_t)g711e_ctx, 0);
		siso_start(siso_audio_g711e);
	}else{
		rt_printf("siso_audio_g711e open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}
	
	rt_printf("siso_audio_g711e started\n\r");	
#endif	

#if ENABLE_MP4_RECORD
	if(sd_ready)
	{
		mimo_2v_1a_rtsp_mp4 = mimo_create();
		if(mimo_2v_1a_rtsp_mp4){
			mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v1_ctx, 0);
			mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_INPUT1, (uint32_t)h264_v2_ctx, 0);
			mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_INPUT2, (uint32_t)aac_ctx, 0);		
			mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_OUTPUT0, (uint32_t)rtsp2_v2_ctx, MMIC_DEP_INPUT1|MMIC_DEP_INPUT2);
			mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_OUTPUT1, (uint32_t)mp4_ctx, MMIC_DEP_INPUT0|MMIC_DEP_INPUT2);
			mimo_start(mimo_2v_1a_rtsp_mp4);
		}else{
			rt_printf("mimo open fail\n\r");
			goto mmf2_example_h264_two_way_audio_pcmu_fail;
		}
		rt_printf("mimo started\n\r");	    
	}
	else	  	  
	{
#if AAC_RECORD	  
    	    miso_h264_aac_rtsp = miso_create();
	    if(miso_h264_aac_rtsp){
		    miso_ctrl(miso_h264_aac_rtsp, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v2_ctx, 0);
		    miso_ctrl(miso_h264_aac_rtsp, MMIC_CMD_ADD_INPUT1, (uint32_t)aac_ctx, 0);		
		    miso_ctrl(miso_h264_aac_rtsp, MMIC_CMD_ADD_OUTPUT0, (uint32_t)rtsp2_v2_ctx, MMIC_DEP_INPUT0|MMIC_DEP_INPUT1);
		    miso_start(miso_h264_aac_rtsp);
	    }else{
		    rt_printf("miso open fail\n\r");
		    goto mmf2_example_h264_two_way_audio_pcmu_fail;
	    }
	    rt_printf("miso started\n\r");
#else
	miso_h264_g711_rtsp = miso_create();
	if(miso_h264_g711_rtsp){
		miso_ctrl(miso_h264_g711_rtsp, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v2_ctx, 0);
		miso_ctrl(miso_h264_g711_rtsp, MMIC_CMD_ADD_INPUT1, (uint32_t)g711e_ctx, 0);
		miso_ctrl(miso_h264_g711_rtsp, MMIC_CMD_ADD_OUTPUT, (uint32_t)rtsp2_v2_ctx, MMIC_DEP_INPUT0|MMIC_DEP_INPUT1);
		miso_start(miso_h264_g711_rtsp);
	}else{
		rt_printf("miso_h264_g711_rtsp fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}
	rt_printf("miso_h264_g711_rtsp started\n\r");	
#endif		    
	}
#else

#if AAC_RECORD	  
    	    miso_h264_aac_rtsp = miso_create();
	    if(miso_h264_aac_rtsp){
		    miso_ctrl(miso_h264_aac_rtsp, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v1_ctx, 0);
		    miso_ctrl(miso_h264_aac_rtsp, MMIC_CMD_ADD_INPUT1, (uint32_t)aac_ctx, 0);		
		    miso_ctrl(miso_h264_aac_rtsp, MMIC_CMD_ADD_OUTPUT0, (uint32_t)rtsp2_v2_ctx, MMIC_DEP_INPUT0|MMIC_DEP_INPUT1);
		    miso_start(miso_h264_aac_rtsp);
	    }else{
		    rt_printf("miso open fail\n\r");
		    goto mmf2_example_h264_two_way_audio_pcmu_fail;
	    }
	    rt_printf("miso started\n\r");
#else
	miso_h264_g711_rtsp = miso_create();
	if(miso_h264_g711_rtsp){
		miso_ctrl(miso_h264_g711_rtsp, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v1_ctx, 0);
		miso_ctrl(miso_h264_g711_rtsp, MMIC_CMD_ADD_INPUT1, (uint32_t)g711e_ctx, 0);
		miso_ctrl(miso_h264_g711_rtsp, MMIC_CMD_ADD_OUTPUT, (uint32_t)rtsp2_v2_ctx, MMIC_DEP_INPUT0|MMIC_DEP_INPUT1);
		miso_start(miso_h264_g711_rtsp);
	}else{
		rt_printf("miso_h264_g711_rtsp fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}
	rt_printf("miso_h264_g711_rtsp started\n\r");	
#endif		
	
#endif
		
	// RTP audio
	
	rtp_ctx = mm_module_open(&rtp_module);
	if(rtp_ctx){
		mm_module_ctrl(rtp_ctx, CMD_RTP_SET_PARAMS, (int)&rtp_g711d_params); 
		mm_module_ctrl(rtp_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(rtp_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(rtp_ctx, CMD_RTP_APPLY, 0);
		mm_module_ctrl(rtp_ctx, CMD_RTP_STREAMING, 1);	// streamming on
	}else{
		rt_printf("RTP open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}

	
	// Audio array input (doorbell)
	array_t array;
	array.data_addr = (uint32_t) doorbell_pcmu_sample;
	array.data_len = (uint32_t) doorbell_pcmu_sample_size;
	array_ctx = mm_module_open(&array_module);
	if(array_ctx){
		mm_module_ctrl(array_ctx, CMD_ARRAY_SET_PARAMS, (int)&doorbell_pcmu_array_params);
		mm_module_ctrl(array_ctx, CMD_ARRAY_SET_ARRAY, (int)&array);
		mm_module_ctrl(array_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(array_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(array_ctx, CMD_ARRAY_APPLY, 0);
		//mm_module_ctrl(array_ctx, CMD_ARRAY_STREAMING, 1);	// streamming on
	}else{
		rt_printf("ARRAY open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}
	
	// G711D
	g711d_ctx = mm_module_open(&g711_module);
	if(g711d_ctx){
		mm_module_ctrl(g711d_ctx, CMD_G711_SET_PARAMS, (int)&g711d_params);
		mm_module_ctrl(g711d_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(g711d_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(g711d_ctx, CMD_G711_APPLY, 0);
	}else{
		rt_printf("G711 open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;  
	}
	
	miso_rtp_array_g711d = miso_create();
	if(miso_rtp_array_g711d){
		miso_ctrl(miso_rtp_array_g711d, MMIC_CMD_ADD_INPUT0, (uint32_t)rtp_ctx, 0);
		miso_ctrl(miso_rtp_array_g711d, MMIC_CMD_ADD_INPUT1, (uint32_t)array_ctx, 0);
		miso_ctrl(miso_rtp_array_g711d, MMIC_CMD_ADD_OUTPUT, (uint32_t)g711d_ctx, 0);
		miso_start(miso_rtp_array_g711d);
	}else{
		rt_printf("miso_rtp_array_g711d open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}

	rt_printf("miso_rtp_array_g711d started\n\r");
	
	siso_g711d_audio = siso_create();
	if(siso_g711d_audio){
		siso_ctrl(siso_g711d_audio, MMIC_CMD_ADD_INPUT, (uint32_t)g711d_ctx, 0);
		siso_ctrl(siso_g711d_audio, MMIC_CMD_ADD_OUTPUT, (uint32_t)audio_ctx, 0);
		siso_start(siso_g711d_audio);
	}else{
		rt_printf("siso_g711d_audio open fail\n\r");
		goto mmf2_example_h264_two_way_audio_pcmu_fail;
	}
	
	rt_printf("siso_g711d_audio started\n\r");
	
	doorbell_handle.doorbell_state |= STATE_MEDIA_READY;
        	
	//printf("Delay 10s and then ring the doorbell\n\r");
	//vTaskDelay(10000);
	//doorbell_ring(); 
	
	return;
mmf2_example_h264_two_way_audio_pcmu_fail:
	
	return;
}
