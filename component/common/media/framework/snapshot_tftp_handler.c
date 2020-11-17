 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"
#include <stdint.h>
#include "jpeg_snapshot.h"
#include "snapshot_tftp_handler.h"
#include "video_common_api.h"
#include "tftp/tftp.h"
#include "wifi_conf.h" //for wifi_is_ready_to_transceive

static tftp * tftp_info = NULL;
static char * tftp_host_ip = NULL;
static char * snapshot_file_name = NULL;
VIDEO_BUFFER video_buf;

#define SNAPSHOT_FILE_NAME "SNAPSHOT"
#define TFTP_HOST_PORT  69
#define TFTP_MODE       "octet"

void snapshot_tftp_send_handler(unsigned char *buffer, int *len, unsigned int index)
{
	//static unsigned int total_size = snapshot_ctx->jpeg_ctx->dest_actual_len;
	int remain_len = video_buf.output_size - (512 * (index - 1));
	if(remain_len / 512) {
		//memset(buffer,index,512);
		memcpy(buffer, (void*) (video_buf.output_buffer + 512 * (index - 1)), 512);
		*len = 512;
	}
	else {
		//memset(buffer,index,(total_size%512));
		memcpy(buffer, (void*) (video_buf.output_buffer + 512 * (index - 1)), remain_len % 512);
		*len = (video_buf.output_size % 512);
	}
	//printf("handler = %d size = %d\r\n",total_size,(*len));
}

void snapshot_tftp_init()
{
	printf("snapshot_tftp_init\n\r");
	tftp_host_ip = (char*)malloc(64);
	if (tftp_host_ip==NULL) {
		printf("allocate tftp_host_ip for snapshot fail");
		return;
	}
	memset(tftp_host_ip, 0, 64);
	
	snapshot_file_name = (char*)malloc(64);
	if (snapshot_file_name==NULL) {
		printf("allocate snapshot_file_name for snapshot fail");
		return;
	}
	memset(snapshot_file_name, 0, 64);
	strcpy(snapshot_file_name,SNAPSHOT_FILE_NAME);
	
	tftp_info = (tftp *) malloc(sizeof(tftp));
	if (tftp_info==NULL) {
		printf("allocate tftp_info for snapshot fail");
		return;
	}
	
	memset(tftp_info, 0, sizeof(tftp));
	tftp_info->send_handle = snapshot_tftp_send_handler;
	tftp_info->tftp_file_name = snapshot_file_name;
	printf("send file name = %s\r\n", tftp_info->tftp_file_name);
	tftp_info->tftp_mode = TFTP_MODE;
	tftp_info->tftp_port = TFTP_HOST_PORT;
	tftp_info->tftp_host = tftp_host_ip;
	tftp_info->tftp_op = WRQ;//FOR READ OPERATION
	tftp_info->tftp_retry_num = 5;
	tftp_info->tftp_timeout = 2;//second
	printf("tftp retry time = %d timeout = %d seconds\r\n", tftp_info->tftp_retry_num, tftp_info->tftp_timeout);
}

void snapshot_tftp_upload_thread(void* param)
{
	char tftp_filename[64] = {0};
	static int tftp_count = 0;
	int timeout_ms = 100;
	
	snapshot_tftp_init();
	
	while(1) {
		if (jpeg_snapshot_get_buffer(&video_buf,timeout_ms)) {
			if (tftp_info->tftp_host[0]==0) {
				printf("ERROR: snapshot_tftp host ip not set\n\r");
				continue;
			}
			if(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) == RTW_SUCCESS) {
				jpeg_snapshot_set_processing(1);
				memset(tftp_filename, 0, 64);
				sprintf(tftp_filename, "%s_%d.jpeg", snapshot_file_name, tftp_count++);
				tftp_info->tftp_file_name = tftp_filename;
				printf("File name = %s\r\n", tftp_info->tftp_file_name);
				if(tftp_client_start(tftp_info) == 0)
					printf("Send file successful\r\n");
				else
					printf("Send file fail\r\n");
				jpeg_snapshot_set_processing(0);
			}
			else {
				printf("wifi not connected\r\n");
			}
		}
	}
}
void jpeg_snapshot_create_tftp_thread()
{
	if(xTaskCreate(snapshot_tftp_upload_thread, ((const char*)"snapshot_upload"), 256, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate failed", __FUNCTION__);
}

void jpeg_snapshot_set_tftp_host_ip(char* addr_string) {
	memset(tftp_host_ip,0,64);
	memcpy(tftp_host_ip,addr_string,64);
}

char* jpeg_snapshot_get_tftp_host_ip() {
	return tftp_host_ip;
}

void jpeg_snapshot_set_filename(char* file_name) {
	memset(snapshot_file_name,0,64);
	memcpy(snapshot_file_name,file_name,64);
}

char* jpeg_snapshot_get_filename() {
	return snapshot_file_name;
}
