/*
 * Realtek Semiconductor Corp.
 *
 * example/example_mask.c
 *
 * Copyright (C) 2016      Ming Qian<ming_qian@realsil.com.cn>
 */
#define OSD_LIB_ENUM_SIZE 1
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
//#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <rtstream.h>
#include <rtsvideo.h>
#include "FreeRTOS.h"
#include "task.h"
#include <rtsisp.h>

extern unsigned char chi_bin[];
extern unsigned char eng_bin[];
extern unsigned char logo_pic_bin[];

#define H_GAP (2)
#define V_GAP (2)

static int g_exit = 0;
struct rts_osd_char_t showchar_ch[6][160];

#if defined(__GNUC__)
#define NS_PER_MS  (1000000)
#define US_PER_MS  (1000)
static int usleep(unsigned int usec)
{
    vTaskDelay((usec + US_PER_MS - 1) / US_PER_MS);
    return 0;
}
#endif

static void Termination(int sign)
{
	g_exit = 1;
}
static int enable_osd(struct rts_video_osd_attr *attr,
		unsigned int eng_addr,
		unsigned int chi_addr,
		unsigned int pic_addr)
{
	int ret;
	int i;

	char *ch_char_str = "苏州上海Realtek08广州007Tel110";

	int ch_len = strlen(ch_char_str);
	struct rts_osd_text_t showtext_ch = {NULL, 0};
	struct rts_osd_char_t showchar_ch[160];
	memset(showchar_ch, 0, sizeof(showchar_ch));

	int j = 0;
	for (i = 0; i < ch_len; ) {

		if (0x0F == ((uint8_t)ch_char_str[i] >> 4)) {
			showchar_ch[j].char_type = char_type_double;
			memcpy(showchar_ch[j++].char_value, &ch_char_str[i], 4);
			i += 4;
		} else if (0x0E == ((uint8_t)ch_char_str[i] >> 4)) {
			showchar_ch[j].char_type = char_type_double;
			memcpy(showchar_ch[j++].char_value, &ch_char_str[i], 3);
			i += 3;
		} else if (0x0C == ((uint8_t)ch_char_str[i] >> 4)) {
			showchar_ch[j].char_type = char_type_double;
			memcpy(showchar_ch[j++].char_value, &ch_char_str[i], 2);
			i += 2;
		} else if (((uint8_t)ch_char_str[i] < 128)) {
			showchar_ch[j].char_type = char_type_single;
			memcpy(showchar_ch[j++].char_value, &ch_char_str[i], 1);
			i++;
		}
	}
	showtext_ch.count = j;
	showtext_ch.content = showchar_ch;
	/*show picture*/
	BITMAP_S bitmap;
	uint8_t *data;

	if (!attr)
		return -1;

	if (attr->number == 0)
		return -1;

	data = (uint8_t*)pic_addr;

	bitmap.pixel_fmt = PIXEL_FORMAT_RGB_1BPP;
	bitmap.u32Width = RTS_MAKE_WORD(data[3], data[4]);
	bitmap.u32Height = RTS_MAKE_WORD(data[5], data[6]);
	bitmap.pData = data + RTS_MAKE_WORD(data[0], data[1]);

	printf("pic file len = %d\n", RTS_MAKE_WORD(data[0], data[1]));
	printf("pic size = %d %d\n", bitmap.u32Width, bitmap.u32Height);
	if (attr->number == 0) {
		/*0 : the first stream*/
		return -1;
	}

	attr->osd_char_w = 32;
	attr->osd_char_h = 32;

	for (i = 0; i < attr->number; i++) {
		struct rts_video_osd_block *pblock = attr->blocks + i;

		switch (i) {
		case 0:
			pblock->rect.left = 10;
			pblock->rect.top = 10;
			pblock->rect.right = pblock->rect.left + bitmap.u32Width;
			pblock->rect.bottom = pblock->rect.top + bitmap.u32Height;
			pblock->bg_enable = 0;
			pblock->bg_color = 0x87cefa;
			pblock->ch_color = 0xff0000;
			pblock->flick_enable = 0;
			pblock->char_color_alpha = 0;
			pblock->pbitmap = &bitmap;

			break;
		case 1:
			pblock->rect.left = 100;
			pblock->rect.top = 350;
			pblock->rect.right = 600;
			pblock->rect.bottom = pblock->rect.top +
				attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 1;
			pblock->bg_color = 0xff0000;
			pblock->flick_enable = 0;
			pblock->ch_color = 0xFFFFFF;
			pblock->char_color_alpha = 8;
			break;
		case 2:
			pblock->rect.left = 200;
			pblock->rect.top = 600;
			pblock->rect.right = 600;
			pblock->rect.bottom = pblock->rect.top +
				attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 1;
			pblock->bg_color = 0x0000ff;
			pblock->ch_color = 0xff00ff;
			pblock->flick_enable = 1;
			pblock->char_color_alpha = 0;
			break;
		case 3:
			pblock->rect.left = 500;
			pblock->rect.top = 100;
			pblock->rect.right = 600;
			pblock->rect.bottom = pblock->rect.top +
				attr->osd_char_h + 2 * V_GAP;
			pblock->bg_enable = 1;
			pblock->bg_color = 0x00ff00;
			pblock->flick_enable = 0;
			pblock->ch_color = 0xFF0000;
			pblock->char_color_alpha = 0;
			pblock->pshowtext = &showtext_ch;
			break;
		default:
			break;
		}
	}
	attr->time_fmt = osd_time_fmt_24;
	attr->time_blkidx = 1;
	attr->time_pos = 0;

	attr->date_fmt = osd_date_fmt_10;
	attr->date_blkidx = 2;
	attr->date_pos = 0;

	attr->single_font_addr = eng_addr;
	attr->double_font_addr = chi_addr;

	/*0 : the first stream*/
	ret = rts_set_isp_osd_attr(attr);


	return ret;
}

static int disable_osd(struct rts_video_osd_attr *attr)
{
	int i;

	if (!attr)
		return -1;

	for (i = 0; i < attr->number; i++) {
		struct rts_video_osd_block *block = attr->blocks + i;
		block->pbitmap = NULL;
		block->pshowtext = NULL;
		block->bg_enable = 0;
		block->flick_enable = 0;
		block->stroke_enable = 0;
	}
	attr->time_fmt = osd_time_fmt_no;
	attr->date_fmt = osd_date_fmt_no;
	attr->single_font_addr = NULL;
	attr->double_font_addr = NULL;

	rts_set_isp_osd_attr(attr);

	return 0;
}

extern int rtsTimezone;
int example_isp_osd_multi_main(int enable, unsigned int eng_addr, unsigned int chi_addr, unsigned int pic_addr)
{
	int i, ret;
	struct rts_video_osd_attr *attr = NULL;

    signal(SIGINT, Termination);
	signal(SIGTERM, Termination);   
    
	rts_set_log_mask(RTS_LOG_MASK_CONS);

	/*run as:
	 * example 1 eng.bin chi.bin pic.bin
	enable = (int)strtol(argv[1], NULL, 0);
	eng_addr = strtol(argv[2], NULL, 16);
	chi_addr = strtol(argv[3], NULL, 16);
	pic_addr = strtol(argv[4], NULL, 16);
	 * */

	rtsTimezone = 28800;
        ret = rts_av_init();
	if (ret)
		return ret;

	rts_isp_ctrl_set_profile(1920, 1080, 1);
	ret = rts_query_isp_osd_attr(0, &attr);
	if (ret) {
		printf("query osd attr fail, ret = %d\n", ret);
		goto exit;
	}
	printf("attr num = %d\n", attr->number);

	if (enable)
		ret = enable_osd(attr, eng_addr, chi_addr, pic_addr);
	else
		ret = disable_osd(attr);
	if (ret)
		printf("%s osd fail, ret = %d\n",
				enable ? "enable" : "disable", ret);
	    
	while (!g_exit) {
		usleep(1000 * 1000);

		i++;

		if (i % 60 == 0)
			rts_refresh_isp_osd_datetime(attr);
	}
    
    rts_release_isp_osd_attr(attr);
    
exit:
	rts_av_release();

	return ret;
}



static void example_isp_osd_multi_task(void *arg)
{
        example_isp_osd_multi_main(1, (unsigned int)eng_bin, (unsigned int)chi_bin, (unsigned int)logo_pic_bin);
        vTaskDelete(NULL);
}

void example_isp_osd_multi(void *arg)
{
        printf("Text/Logo OSD Test\r\n");

	if(xTaskCreate(example_isp_osd_multi_task, "OSD", 50*1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate failed", __FUNCTION__);
}


