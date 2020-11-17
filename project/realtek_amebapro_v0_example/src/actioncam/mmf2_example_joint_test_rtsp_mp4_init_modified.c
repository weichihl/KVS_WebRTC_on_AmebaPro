 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

/*
 * V1: MP4
 * V2: RTSP
 */

#include "media_framework/example_media_framework.h"
#include <rtstream.h>
#include <rtsvideo.h>
#include <time.h>
#include "isp_api.h"

#define RESERVED_FILE_SIZE  100
#define V_GAP               (2)

static uint8_t processing = 0;
static uint8_t mp4_running = 0;
static uint32_t file_count = 0;
static char sd_filename[64];
static char sd_dirname[32];
static fatfs_sd_params_t fatfs_sd;
static void *osd_sema = NULL;
static int next_year = 0, next_month = 0, next_day = 0;

extern void led_stop_recording(void);

static void get_next_date(int timezone, int *year, int *month, int *day)
{
	struct tm current_tm;
	unsigned int update_tick = 0;
	long update_sec = 0, update_usec = 0, current_sec = 0;
	unsigned int current_tick = xTaskGetTickCount();

	extern void sntp_get_lasttime(long *sec, long *usec, unsigned int *tick);
	sntp_get_lasttime(&update_sec, &update_usec, &update_tick);

	if(update_tick) {
		long tick_diff_sec, tick_diff_ms;

		tick_diff_sec = (current_tick - update_tick) / configTICK_RATE_HZ;
		tick_diff_ms = (current_tick - update_tick) % configTICK_RATE_HZ / portTICK_RATE_MS;
		update_sec += tick_diff_sec;
		update_usec += (tick_diff_ms * 1000);
		current_sec = update_sec + update_usec / 1000000 + timezone * 3600;
	}
	else {
		current_sec = current_tick / configTICK_RATE_HZ;
	}

	current_sec += 86400;

	current_tm = *(localtime((time_t const*)&current_sec));
	current_tm.tm_year += 1900;
	current_tm.tm_mon += 1;

	*year = current_tm.tm_year;
	*month = current_tm.tm_mon;
	*day = current_tm.tm_mday;
}

void refresh_osd_date(void)
{
	int year, month, day;
	get_next_date(8, &year, &month, &day);

	if((next_year != year) || (next_month != month) || (next_day != day)) {
		rts_write_isp_osd_date(1, osd_date_fmt_10, year, month, day);
		next_year = year;
		next_month = month;
		next_day = day;
	}
}

static void ch0_osd_thread(void *param)
{
	int width, height;
	struct rts_video_osd_attr *attr = NULL;
	struct rts_video_osd_block *pblock = NULL;

	// wait for RTC
	extern void sntp_get_lasttime(long *sec, long *usec, unsigned int *tick);
	long sec, usec;
	unsigned int tick;
	while(1) {
		sntp_get_lasttime(&sec, &usec, &tick);

		if(sec)
			break;
		else
			vTaskDelay(100);
	}

	while(isp_stream_get_status(0) == 0)
		vTaskDelay(100);

	if(rts_av_init() == 0) {
		if(rts_query_isp_osd_attr(0, &attr) == 0) {
			extern unsigned char eng_bin[];
			attr->single_font_addr = (unsigned int) eng_bin;
			attr->osd_char_w = 32;
			attr->osd_char_h = 32;
			attr->date_fmt = osd_date_fmt_10;
			attr->date_blkidx = 0;
			attr->date_pos = 0;
			attr->time_fmt = osd_time_fmt_24;
			attr->time_blkidx = 1;
			attr->time_pos = 0;

			width = V1_WIDTH;
			height = V1_HEIGHT;
			// date
			pblock = &attr->blocks[0];
			pblock->rect.left = 10;
			pblock->rect.top = 10;
			pblock->rect.right = 200;
			pblock->rect.bottom = pblock->rect.top + attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 0;
			pblock->bg_color = 0x000000;
			pblock->ch_color = 0xff0000;
			pblock->flick_enable = 0;
			pblock->char_color_alpha = 0;
			// time
			pblock = &attr->blocks[1];
			pblock->rect.left = 10;
			pblock->rect.top = pblock->rect.top + attr->osd_char_h + 4 * V_GAP;
			pblock->rect.right = 200;
			pblock->rect.bottom = pblock->rect.top + attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 0;
			pblock->bg_color = 0x000000;
			pblock->ch_color = 0xff0000;
			pblock->flick_enable = 0;
			pblock->char_color_alpha = 0;

			rts_set_isp_osd_attr(attr);
			rts_release_isp_osd_attr(attr);
		}
		else {
			printf("ERROR: rts_query_isp_osd_attr ch0\n\r");
		}

		rts_av_release();
	}
	else {
		printf("ERROR: rts_av_init\n\r");
	}

	vTaskDelete(NULL);
}

void setup_ch0_osd_attr(void)
{
	if(xTaskCreate(ch0_osd_thread, "ch0_osd_thread", 8*1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(ch0_osd_thread) failed", __FUNCTION__);
}

static void ch0and1_osd_thread(void *param)
{
	int width, height;
	struct rts_video_osd_attr *attr = NULL;
	struct rts_video_osd_block *pblock = NULL;

	// wait for RTC
	extern void sntp_get_lasttime(long *sec, long *usec, unsigned int *tick);
	long sec, usec;
	unsigned int tick;
	while(1) {
		sntp_get_lasttime(&sec, &usec, &tick);

		if(sec)
			break;
		else
			vTaskDelay(100);
	}

	while(isp_stream_get_status(0) == 0)
		vTaskDelay(100);

	if(rts_av_init() == 0) {
		if(rts_query_isp_osd_attr(0, &attr) == 0) {
			extern unsigned char eng_bin[];
			attr->single_font_addr = (unsigned int) eng_bin;
			attr->osd_char_w = 32;
			attr->osd_char_h = 32;
			attr->date_fmt = osd_date_fmt_10;
			attr->date_blkidx = 0;
			attr->date_pos = 0;
			attr->time_fmt = osd_time_fmt_24;
			attr->time_blkidx = 1;
			attr->time_pos = 0;

			width = V1_WIDTH;
			height = V1_HEIGHT;
			// date
			pblock = &attr->blocks[0];
			pblock->rect.left = 10;
			pblock->rect.top = 10;
			pblock->rect.right = 200;
			pblock->rect.bottom = pblock->rect.top + attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 0;
			pblock->bg_color = 0x000000;
			pblock->ch_color = 0xff0000;
			pblock->flick_enable = 0;
			pblock->char_color_alpha = 0;
			// time
			pblock = &attr->blocks[1];
			pblock->rect.left = 10;
			pblock->rect.top = pblock->rect.top + attr->osd_char_h + 4 * V_GAP;
			pblock->rect.right = 200;
			pblock->rect.bottom = pblock->rect.top + attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 0;
			pblock->bg_color = 0x000000;
			pblock->ch_color = 0xff0000;
			pblock->flick_enable = 0;
			pblock->char_color_alpha = 0;

			rts_set_isp_osd_attr(attr);
			rts_release_isp_osd_attr(attr);
		}
		else {
			printf("ERROR: rts_query_isp_osd_attr ch0\n\r");
		}

		if(rts_query_isp_osd_attr(1, &attr) == 0) {
			extern unsigned char eng_bin[];
			attr->single_font_addr = (unsigned int) eng_bin;
			attr->osd_char_w = 32;
			attr->osd_char_h = 32;
			attr->date_fmt = osd_date_fmt_10;
			attr->date_blkidx = 0;
			attr->date_pos = 0;
			attr->time_fmt = osd_time_fmt_24;
			attr->time_blkidx = 1;
			attr->time_pos = 0;

			width = V2_WIDTH;
			height = V2_HEIGHT;
			// date
			pblock = &attr->blocks[0];
			pblock->rect.left = 10;
			pblock->rect.top = 10;
			pblock->rect.right = 200;
			pblock->rect.bottom = pblock->rect.top + attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 0;
			pblock->bg_color = 0x000000;
			pblock->ch_color = 0xff0000;
			pblock->flick_enable = 0;
			pblock->char_color_alpha = 0;
			// time
			pblock = &attr->blocks[1];
			pblock->rect.left = 10;
			pblock->rect.top = pblock->rect.top + attr->osd_char_h + 4 * V_GAP;
			pblock->rect.right = 200;
			pblock->rect.bottom = pblock->rect.top + attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 0;
			pblock->bg_color = 0x000000;
			pblock->ch_color = 0xff0000;
			pblock->flick_enable = 0;
			pblock->char_color_alpha = 0;

			rts_set_isp_osd_attr(attr);
			rts_release_isp_osd_attr(attr);
		}
		else {
			printf("ERROR: rts_query_isp_osd_attr ch1\n\r");
		}

		rts_av_release();
	}
	else {
		printf("ERROR: rts_av_init\n\r");
	}

	vTaskDelete(NULL);
}

void setup_ch0and1_osd_attr(void)
{
	if(xTaskCreate(ch0and1_osd_thread, "ch0and1_osd_thread", 8*1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(ch0and1_osd_thread) failed", __FUNCTION__);
}

static void ch2_osd_thread(void *param)
{
	int width, height;
	struct rts_video_osd_attr *attr = NULL;
	struct rts_video_osd_block *pblock = NULL;

	if(rts_av_init() == 0) {
		if(rts_query_isp_osd_attr(2, &attr) == 0) {
			extern unsigned char eng_bin[];
			attr->single_font_addr = (unsigned int) eng_bin;
			attr->osd_char_w = 32;
			attr->osd_char_h = 32;
			attr->date_fmt = osd_date_fmt_10;
			attr->date_blkidx = 0;
			attr->date_pos = 0;
			attr->time_fmt = osd_time_fmt_24;
			attr->time_blkidx = 1;
			attr->time_pos = 0;

			width = V3_WIDTH;
			height = V3_HEIGHT;
			// date
			pblock = &attr->blocks[0];
			pblock->rect.left = 10;
			pblock->rect.top = 10;
			pblock->rect.right = 200;
			pblock->rect.bottom = pblock->rect.top + attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 0;
			pblock->bg_color = 0x000000;
			pblock->ch_color = 0xff0000;
			pblock->flick_enable = 0;
			pblock->char_color_alpha = 0;
			// time
			pblock = &attr->blocks[1];
			pblock->rect.left = 10;
			pblock->rect.top = pblock->rect.top + attr->osd_char_h + 4 * V_GAP;
			pblock->rect.right = 200;
			pblock->rect.bottom = pblock->rect.top + attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 0;
			pblock->bg_color = 0x000000;
			pblock->ch_color = 0xff0000;
			pblock->flick_enable = 0;
			pblock->char_color_alpha = 0;

			rts_set_isp_osd_attr(attr);
			rts_release_isp_osd_attr(attr);
		}
		else {
			printf("ERROR: rts_query_isp_osd_attr ch2\n\r");
		}

		rts_av_release();
	}
	else {
		printf("ERROR: rts_av_init\n\r");
	}

	rtw_up_sema(&osd_sema);
	vTaskDelete(NULL);
}

void setup_ch2_osd_attr(void)
{
	int i;

	if(osd_sema == NULL)
		rtw_init_sema(&osd_sema, 0);

	if(xTaskCreate(ch2_osd_thread, "ch2_osd_thread", 8*1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(ch2_osd_thread) failed", __FUNCTION__);

	rtw_down_sema(&osd_sema);
}

void setup_md_attr(uint8_t enable)
{
	int i;
	struct rts_video_md_attr *attr = NULL;

	if(rts_av_init() == 0) {
		if(rts_query_isp_md_attr(&attr, 1920, 1080) == 0) {
			for(i = 0; i < attr->number; i++) {
				struct rts_video_md_block *pblock = attr->blocks + i;

				if(enable) {
					if(pblock->type ==  RTS_ISP_BLK_TYPE_GRID) {
						pblock->area.left = 0;
						pblock->area.top = 0;
						pblock->area.cell.width = 60;
						pblock->area.cell.height = 60;
						pblock->area.rows = 18;
						pblock->area.columns = 32;
						pblock->area.length = (pblock->area.rows * pblock->area.columns + 7) / 8;
						memset(pblock->area.bitmap, 0xff, pblock->area.length);
					}
					else if(pblock->type == RTS_ISP_BLK_TYPE_RECT) {
						pblock->rect.left = 320;
						pblock->rect.top = 240;
						pblock->rect.right = 720;
						pblock->rect.bottom = 540;
					}
					else {
						pblock->enable = 0;
						continue;
					}

					pblock->sensitivity = 90;
					pblock->percentage = 25;
					pblock->frame_interval = 5;

					pblock->enable = 1;
				} else {
					pblock->enable = 0;
				}
			}

			rts_set_isp_md_attr(attr);
			rts_release_isp_md_attr(attr);
		}
		else {
			printf("ERROR: rts_query_isp_md_attr\n\r");
		}

		rts_av_release();
	}
	else {
		printf("ERROR: rts_av_init\n\r");
	}
}

int mmf_h264_suspend(void *arg)
{
	printf("mmf_h264_suspend\r\n");
	mm_module_ctrl(h264_v2_ctx, CMD_H264_PAUSE, 1);
}
int mmf_h264_start(void *arg)
{
	printf("mmf_h264_start\r\n");
	mm_module_ctrl(h264_v2_ctx, CMD_H264_PAUSE, 0);
}

static int del_old_file(void)
{
	int ret = -1;
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
			ret = 0;
		}
	}

	return ret;
}

static int mp4_error_cb(void *parm)
{
	if(processing) {
		processing = 0;
		mp4_running = 0;
		led_stop_recording();
		mm_module_ctrl(h264_v2_ctx, CMD_H264_PAUSE, 1);
	}
	printf("The sdcard is error\r\n");
	//Do your operation
}

static int mp4_end_cb(void *parm)
{
	if(processing) {
		while(fatfs_get_free_space() < RESERVED_FILE_SIZE) {
			if(del_old_file() != 0) {
				printf("ERROR: free space < %d MB\n\r", RESERVED_FILE_SIZE);
				processing = 0;
				led_stop_recording();
				return 0;
			}
		}

		vTaskDelay(100);
		file_count ++;
		mp4_v1_params.record_file_num = 1;
		sprintf(mp4_v1_params.record_file_name, "%s_%d", sd_filename, file_count);
		mm_module_ctrl(mp4_ctx, CMD_MP4_SET_PARAMS, (int) &mp4_v1_params);
		mm_module_ctrl(mp4_ctx, CMD_MP4_SET_END_CB,(int) mp4_end_cb);
		mm_module_ctrl(mp4_ctx, CMD_MP4_SET_ERROR_CB,(int) mp4_error_cb);
		mm_module_ctrl(mp4_ctx, CMD_MP4_START, mp4_v1_params.record_file_num);
	}
	else {
		mp4_running = 0;
		mm_module_ctrl(h264_v1_ctx, CMD_H264_PAUSE, 1);
	}

	return 0;
}

void mp4_to_sd_start(char *filename)
{
	int i;
	
	for(i = (strlen(filename) - 1); i >= 0; i --) {
		if(filename[i] == '/') {
			fatfs_sd_get_param(&fatfs_sd);
			memset(sd_dirname, 0, sizeof(sd_dirname));
			strcpy(sd_dirname, fatfs_sd.drv);
			memcpy(sd_dirname + strlen(sd_dirname), filename, i);
			break;
		}
	}

	while(fatfs_get_free_space() < RESERVED_FILE_SIZE) {
		if(del_old_file() != 0) {
			printf("ERROR: free space < %d MB\n\r", RESERVED_FILE_SIZE);
			processing = 0;
			led_stop_recording();
			return;
		}
	}

	mm_module_ctrl(h264_v1_ctx, CMD_H264_PAUSE, 0);

	file_count = 0;
	mp4_v1_params.record_file_num = 1;
	strcpy(sd_filename, filename);
	sprintf(mp4_v1_params.record_file_name, "%s_%d", sd_filename, file_count);
	mm_module_ctrl(mp4_ctx, CMD_MP4_SET_PARAMS, (int) &mp4_v1_params);
	mm_module_ctrl(mp4_ctx, CMD_MP4_SET_END_CB,(int) mp4_end_cb);
	mm_module_ctrl(mp4_ctx, CMD_MP4_SET_ERROR_CB,(int) mp4_error_cb);
	mm_module_ctrl(mp4_ctx, CMD_MP4_START, mp4_v1_params.record_file_num);
	mp4_running = 1;
	processing = 1;
}

void mp4_to_sd_stop(void)
{
	if(processing) {
		processing = 0;
		mm_module_ctrl(mp4_ctx, CMD_MP4_STOP, NULL);
	}
}

uint8_t mp4_to_sd_running(void)
{
	return mp4_running;
}

void set_sc2232_fps(int fps)
{
	switch (fps)
	{
	//5 FPS
	case 5:
	isp_i2c_write_byte(0x320c,0x33);
	isp_i2c_write_byte(0x320d,0x90);
	break;
	//10 FPS
	case 10:
	isp_i2c_write_byte(0x320c,0x19);
	isp_i2c_write_byte(0x320d,0xC8);
	break;
	//15 FPS
	case 15:
	isp_i2c_write_byte(0x320c,0x11);
	isp_i2c_write_byte(0x320d,0x30);
	break;
	//20 FPS
	case 20:
	isp_i2c_write_byte(0x320c,0x0C);
	isp_i2c_write_byte(0x320d,0xE4);
	break;
	//25 FPS
	case 25:
	isp_i2c_write_byte(0x320c,0x0A);
	isp_i2c_write_byte(0x320d,0x50);
	break;
	//30 FPS
	case 30:
	isp_i2c_write_byte(0x320c,0x08);
	isp_i2c_write_byte(0x320d,0x98);
	break;
	default:
	printf("It don't support the fps = %d\r\n",fps);
	}
}

// set streaming  GP & VBR
void set_qp_vbr(void *parm)
{
	h264_rc_parm_t rc_param;
	rc_param.rcMode = RC_MODE_H264VBR;
	rc_param.minQp = 35;
	rc_param.maxQp = 40;
	//rc_param.minIQp = 50;
	mm_module_ctrl(h264_v2_ctx, CMD_H264_SET_RCPARAM,(int)&rc_param);
}

void mmf2_example_joint_test_rtsp_mp4_init_modified(void)
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
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
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
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	
	
	
	// ------ Channel 2--------------
	isp_v2_ctx = mm_module_open(&isp_module);
	if(isp_v2_ctx){
		mm_module_ctrl(isp_v2_ctx, CMD_ISP_SET_PARAMS, (int)&isp_v2_params);
		mm_module_ctrl(isp_v2_ctx, MM_CMD_SET_QUEUE_LEN, V2_SW_SLOT);
		mm_module_ctrl(isp_v2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(isp_v2_ctx, CMD_ISP_APPLY, 1);	// start channel 1
	}else{
		rt_printf("ISP open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	
	h264_v2_ctx = mm_module_open(&h264_module);
	if(h264_v2_ctx){
		mm_module_ctrl(h264_v2_ctx, CMD_H264_SET_PARAMS, (int)&h264_v2_params);
		mm_module_ctrl(h264_v2_ctx, MM_CMD_SET_QUEUE_LEN, V2_H264_QUEUE_LEN);
		mm_module_ctrl(h264_v2_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(h264_v2_ctx, CMD_H264_INIT_MEM_POOL, 0);
		set_qp_vbr (NULL);
		mm_module_ctrl(h264_v2_ctx, CMD_H264_APPLY, 0);
	}else{
		rt_printf("H264 open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	
	//--------------Audio --------------
#if USING_I2S_MIC
	i2s_ctx = mm_module_open(&i2s_module);
	if(i2s_ctx){
		mm_module_ctrl(i2s_ctx, CMD_I2S_SET_PARAMS, (int)&i2s_params);
		mm_module_ctrl(i2s_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(i2s_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(i2s_ctx, CMD_I2S_APPLY, 0);
	}else{
		rt_printf("i2s open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
#endif
	audio_ctx = mm_module_open(&audio_module);
	if(audio_ctx){
		mm_module_ctrl(audio_ctx, CMD_AUDIO_SET_PARAMS, (int)&audio_params);
		mm_module_ctrl(audio_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(audio_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(audio_ctx, CMD_AUDIO_APPLY, 0);
	}else{
		rt_printf("audio open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
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
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
        
        //--------------MP4---------------
	mp4_ctx = mm_module_open(&mp4_module);
	if(mp4_ctx){
		//mm_module_ctrl(mp4_ctx, CMD_MP4_SET_PARAMS, (int)&mp4_v1_params);
		//mm_module_ctrl(mp4_ctx, CMD_MP4_START, mp4_v1_params.record_file_num);
		//mm_module_ctrl(mp4_ctx, MM_CMD_SET_QUEUE_LEN, 3);
		//mm_module_ctrl(mp4_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
	}else{
		rt_printf("MP4 open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	
	
	//--------------RTSP---------------
	rtsp2_v2_ctx = mm_module_open(&rtsp2_module);
	if(rtsp2_v2_ctx){
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SELECT_STREAM, 0);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_v2_params);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_APPLY, 0);
		
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SELECT_STREAM, 1);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_a_params);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_APPLY, 0);

		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_DROP_TIME, 300);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_STOP_CB, (int)mmf_h264_suspend);
		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_START_CB, (int)mmf_h264_start);

		mm_module_ctrl(rtsp2_v2_ctx, CMD_RTSP2_SET_STREAMMING, ON);
		//mm_module_ctrl(rtsp2_v1_ctx, MM_CMD_SET_QUEUE_LEN, 3);
		//mm_module_ctrl(rtsp2_v1_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
	}else{
		rt_printf("RTSP2 open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	
	//--------------Link---------------------------
	siso_isp_h264_v1 = siso_create();
	if(siso_isp_h264_v1){
		siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v1_ctx, 0);
		siso_ctrl(siso_isp_h264_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_v1_ctx, 0);
		siso_start(siso_isp_h264_v1);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	
	siso_isp_h264_v2 = siso_create();
	if(siso_isp_h264_v2){
		siso_ctrl(siso_isp_h264_v2, MMIC_CMD_ADD_INPUT, (uint32_t)isp_v2_ctx, 0);
		siso_ctrl(siso_isp_h264_v2, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_v2_ctx, 0);
		siso_start(siso_isp_h264_v2);
	}else{
		rt_printf("siso2 open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}	
	
	siso_audio_aac = siso_create();
	if(siso_audio_aac){
#if USING_I2S_MIC
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_INPUT, (uint32_t)i2s_ctx, 0);
#else
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_INPUT, (uint32_t)audio_ctx, 0);
#endif
		siso_ctrl(siso_audio_aac, MMIC_CMD_ADD_OUTPUT, (uint32_t)aac_ctx, 0);
		siso_start(siso_audio_aac);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	
	
	rt_printf("siso started\n\r");
	
	mimo_2v_1a_rtsp_mp4 = mimo_create();
	if(mimo_2v_1a_rtsp_mp4){
		mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_INPUT0, (uint32_t)h264_v1_ctx, 0);
		mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_INPUT1, (uint32_t)h264_v2_ctx, 0);
		mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_INPUT2, (uint32_t)aac_ctx, 0);
		//mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_OUTPUT0, (uint32_t)rtsp2_v1_ctx, MMIC_DEP_INPUT0|MMIC_DEP_INPUT2);
		//mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_OUTPUT1, (uint32_t)mp4_ctx, MMIC_DEP_INPUT1|MMIC_DEP_INPUT2);
                mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_OUTPUT0, (uint32_t)mp4_ctx, MMIC_DEP_INPUT0|MMIC_DEP_INPUT2);
		mimo_ctrl(mimo_2v_1a_rtsp_mp4, MMIC_CMD_ADD_OUTPUT1, (uint32_t)rtsp2_v2_ctx, MMIC_DEP_INPUT1|MMIC_DEP_INPUT2);
		mimo_start(mimo_2v_1a_rtsp_mp4);
	}else{
		rt_printf("mimo open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	rt_printf("mimo started\n\r");
	
	// RTP audio
	
	rtp_ctx = mm_module_open(&rtp_module);
	if(rtp_ctx){
		mm_module_ctrl(rtp_ctx, CMD_RTP_SET_PARAMS, (int)&rtp_aad_params);
		mm_module_ctrl(rtp_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(rtp_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(rtp_ctx, CMD_RTP_APPLY, 0);
		mm_module_ctrl(rtp_ctx, CMD_RTP_STREAMING, 1);	// streamming on
	}else{
		rt_printf("RTP open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	
	aad_ctx = mm_module_open(&aad_module);
	if(aad_ctx){
		mm_module_ctrl(aad_ctx, CMD_AAD_SET_PARAMS, (int)&aad_rtp_params);
		mm_module_ctrl(aad_ctx, MM_CMD_SET_QUEUE_LEN, 6);
		mm_module_ctrl(aad_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
		mm_module_ctrl(aad_ctx, CMD_AAD_APPLY, 0);
	}else{
		rt_printf("AAD open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	
	siso_rtp_aad = siso_create();
	if(siso_rtp_aad){
		siso_ctrl(siso_rtp_aad, MMIC_CMD_ADD_INPUT, (uint32_t)rtp_ctx, 0);
		siso_ctrl(siso_rtp_aad, MMIC_CMD_ADD_OUTPUT, (uint32_t)aad_ctx, 0);
		siso_start(siso_rtp_aad);
	}else{
		rt_printf("siso1 open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}
	
	rt_printf("siso3 started\n\r");
	
	siso_aad_audio = siso_create();
	if(siso_aad_audio){
		siso_ctrl(siso_aad_audio, MMIC_CMD_ADD_INPUT, (uint32_t)aad_ctx, 0);
		siso_ctrl(siso_aad_audio, MMIC_CMD_ADD_OUTPUT, (uint32_t)audio_ctx, 0);
		siso_start(siso_aad_audio);
	}else{
		rt_printf("siso2 open fail\n\r");
		goto mmf2_exmaple_joint_test_rtsp_mp4_fail;
	}

	mm_module_ctrl(h264_v1_ctx, CMD_H264_PAUSE, 1);
	mm_module_ctrl(h264_v2_ctx, CMD_H264_PAUSE, 1);

	return;
mmf2_exmaple_joint_test_rtsp_mp4_fail:
	
	return;

}

