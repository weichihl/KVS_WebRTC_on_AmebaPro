 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include "jpeg_snapshot.h"
#include "video_common_api.h"
#include "ff.h"
#include "fatfs_sdcard_api.h"

static char snapshot_file_name[64];
static VIDEO_BUFFER video_buf;
static FIL f;
static fatfs_sd_params_t fatfs_sd;
TaskHandle_t snapshot_sd_thread = NULL;

#define SNAPSHOT_FILE_NAME "SNAPSHOT"

void snapshot_sd_init(void)
{
	printf("snapshot_sd_init\n\r");

	memset(snapshot_file_name, 0, 64);
	strcpy(snapshot_file_name, SNAPSHOT_FILE_NAME);
}

void snapshot_sd_store_thread(void *param)
{
	char sd_filename[64] = {0};
	int sd_count = 0;
	int timeout_ms = 100;
	int res;
	UINT bw = 0;

	snapshot_sd_init();

	while(1) {
		if(jpeg_snapshot_get_buffer(&video_buf, timeout_ms)) {
			jpeg_snapshot_set_processing(1);
			memset(sd_filename, 0, 64);

			if((res = fatfs_sd_get_param(&fatfs_sd)) < 0) {
				fatfs_sd_init();
				res = fatfs_sd_get_param(&fatfs_sd);
			}

			if(res < 0) {
				printf("ERROR: fatfs_sd_get_param\n");
			}
			else {
				strcpy(sd_filename, fatfs_sd.drv);
				sprintf(sd_filename + strlen(sd_filename), "%s_%d.jpeg", snapshot_file_name, sd_count);
				res = f_open(&f, sd_filename, FA_OPEN_ALWAYS | FA_WRITE);

				if(res) {
					printf("ERROR: f_open(%s)\n", sd_filename);
				}
				else {
					f_write(&f, video_buf.output_buffer, video_buf.output_size, (u32*) &bw);
					f_close(&f);
					printf("save file(%s) ok\n", sd_filename);
				}
			}

			sd_count++;
			jpeg_snapshot_set_processing(0);
		}
	}
}

void jpeg_snapshot_create_sd_thread(void)
{
	if(xTaskCreate(snapshot_sd_store_thread, ((const char*)"snapshot_store"), 256, NULL, tskIDLE_PRIORITY + 1, &snapshot_sd_thread) != pdPASS)
		printf("\n\r%s xTaskCreate failed", __FUNCTION__);
}

void jpeg_snapshot_sd_set_filename(char *file_name) {
	memset(snapshot_file_name, 0, 64);
	memcpy(snapshot_file_name, file_name, 64);
}

char* jpeg_snapshot_sd_get_filename(void) {
	return snapshot_file_name;
}
