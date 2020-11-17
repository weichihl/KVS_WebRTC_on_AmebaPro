#include "platform_opts.h"
#include "media_framework/example_media_framework.h"
#include "isp_cmd.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "qr_code_scanner/inc/qr_code_scanner.h"
#include "jpeg_snapshot.h"
#include "wifi_conf.h"
#include <lwip_netconf.h>

static uint8_t scanning = 0;
static uint8_t qrcode_running = 0;

void qrcode_scanner_stop(void)
{
	scanning = 0;
}

uint8_t qrcode_scanner_running(void)
{
	return qrcode_running;
}

static void example_qr_code_scanner_done_event(unsigned char *buf, unsigned int buf_len)
{
	unsigned int index;
	unsigned int count;
	unsigned char ssid_string[33] = {0};		//max: 32
	unsigned int ssid_length = 0;
	unsigned char type_string[7] = {0};			//WEP WPA nopass, max: 6
	rtw_security_t security_type = RTW_SECURITY_OPEN;
	unsigned char password_string[65] = {0};	//max: 64
	unsigned int password_length = 0;
	unsigned char hidden_string[6] = {0};		//true false, max: 5
	unsigned int hidden_type = 0;
	unsigned int error_flag = 0;

	// WIFI:S:SSID;T:<WPA|WEP|nopass>;P:<password>;H:<true|false>;;
	// In SSID and password, special characters ':' ';' and '\' should be escaped with character '\' before.
	if(strncmp(buf, "WIFI:", 5) == 0 && *(buf + buf_len - 1) == ';') {
		printf("%s: WIFI QR code! \r\n", __FUNCTION__);

		index = 5;
		while(index < buf_len - 1) {
			if(strncmp(buf + index, "S:", 2) == 0) {
				index += 2;
				count = 0;

				while(1) {
					if(*(buf + index) == '\\')
					{
						*(ssid_string + count) = *(buf + index + 1);
						index += 2;
					}
					else
					{
						*(ssid_string + count) = *(buf + index);
						index ++;
					}
					count ++;
					if(*(buf + index) == ';')
						break;
				}

				ssid_length = count;

				index ++;
			} else if(strncmp(buf + index, "T:", 2) == 0) {
				index += 2;
				count = 0;

				while(*(buf + index + count) != ';')
					count ++;

				strncpy(type_string, buf + index, count);
				if(strncmp(type_string, "WPA", count) == 0)
					security_type = RTW_SECURITY_WPA2_AES_PSK;
				else if(strncmp(type_string, "WEP", count) == 0)
					security_type = RTW_SECURITY_WEP_PSK;
				else if(strncmp(type_string, "nopass", count) == 0)
					security_type = RTW_SECURITY_OPEN;
				else {
					error_flag = 1;
					printf("%s: type = %s \r\n", __FUNCTION__, type_string);
					break;
				}

				index += count + 1;
			} else if(strncmp(buf + index, "P:", 2) == 0) {
				index += 2;
				count = 0;

				while(1) {
					if(*(buf + index) == '\\')
					{
						*(password_string + count) = *(buf + index + 1);
						index += 2;
					}
					else
					{
						*(password_string + count) = *(buf + index);
						index ++;
					}
					count ++;
					if(*(buf + index) == ';')
						break;
				}

				password_length = count;

				index ++;
			} else if(strncmp(buf + index, "H:", 2) == 0) {
				index += 2;
				count = 0;

				while(*(buf + index + count) != ';')
					count ++;

				strncpy(hidden_string, buf + index, count);
				if(strncmp(hidden_string, "true", count) == 0)
					hidden_type = 1;
				else if(strncmp(hidden_string, "false", count) == 0)
					hidden_type = 0;
				else {
					error_flag = 1;
					printf("%s: hidden = %s \r\n", __FUNCTION__, hidden_string);
					break;
				}

				index += count + 1;
			} else {
				error_flag = 1;
				break;
			}
		}

		if(error_flag)
			printf("%s: Error WIFI QR code! \r\n", __FUNCTION__);
		else {
#if 0
			printf("%s: ssid = %s \r\n", __FUNCTION__, ssid_string);
			printf("%s: ssid_length = %d \r\n", __FUNCTION__, ssid_length);
			printf("%s: type = %s \r\n", __FUNCTION__, type_string);
			printf("%s: security_type = 0x%x \r\n", __FUNCTION__, security_type);
			printf("%s: password = %s \r\n", __FUNCTION__, password_string);
			printf("%s: password_length = %d \r\n", __FUNCTION__, password_length);
			printf("%s: hidden = %s \r\n", __FUNCTION__, hidden_string);
			printf("%s: hidden_type = %d \r\n", __FUNCTION__, hidden_type);
#else
			int ret;

			if(security_type == RTW_SECURITY_OPEN)
				ret = wifi_connect(ssid_string, security_type, NULL, ssid_length, 0, 0, NULL);
			else
				ret = wifi_connect(ssid_string, security_type, password_string, ssid_length, password_length, 0, NULL);

			if(ret == RTW_SUCCESS)
				LwIP_DHCP(0, DHCP_START);
#endif
		}
	} else {
		printf("%s: Not WIFI QR code! \r\n", __FUNCTION__);
		printf("%s: buf = %s \r\n", __FUNCTION__, buf);
	}
}

static void example_qr_code_scanner_thread_modified(void *param)
{
	unsigned char *raw_data;
	unsigned int width = 640;
	unsigned int height = 480;
	int x_density = 1;
	int y_density = 1;
	qr_code_scanner_result qr_code_result = QR_CODE_FAIL_UNSPECIFIC_ERROR;
	unsigned char *result_string = NULL;
	unsigned int result_length;

	qrcode_running = 1;

	// stop jpeg snapshot
	extern TaskHandle_t snapshot_sd_thread;
	if(snapshot_sd_thread) {
		vTaskDelete(snapshot_sd_thread);
		snapshot_sd_thread = NULL;
	}
	jpeg_snapshot_isp_deinit();

	result_string = (unsigned char *)malloc(QR_CODE_MAX_RESULT_LENGTH);
	if(result_string == NULL) {
		printf("%s: result_string malloc fail \r\n", __FUNCTION__);
		goto exit;
	}

	if(yuv_snapshot_isp_config(width, height, 10, 2) < 0) {
		printf("%s: yuv_snapshot_isp_config fail \r\n", __FUNCTION__);
	}
	else {
		scanning = 1;

		struct isp_cmd_data cmd_data;
		u8 acTemp[8];
		cmd_data.cmdcode = 0x0301;
		cmd_data.index = 0x01;
		cmd_data.length = 0x02;
		cmd_data.param = 0x00;
		cmd_data.addr = 0x00;
		cmd_data.buf = acTemp;
		// AE: 0x02
		memset(acTemp, 0, sizeof(acTemp));
		cmd_data.buf[0] = 0x02;
		cmd_data.buf[1] = 0x00;
		isp_send_cmd(&cmd_data);
		vTaskDelay(1000);

		while(scanning) {
			qr_code_result = QR_CODE_FAIL_UNSPECIFIC_ERROR;
			memset(result_string, 0, QR_CODE_MAX_RESULT_LENGTH);

			if(yuv_snapshot_isp(&raw_data) < 0)
				printf("%s: get image from camera fail \r\n", __FUNCTION__);
			else
				qr_code_result = qr_code_parsing(raw_data, width, height, x_density, y_density, result_string, &result_length);

			if(qr_code_result == QR_CODE_SUCCESS) {
				printf("%s: qr code scan success \r\n", __FUNCTION__);
				example_qr_code_scanner_done_event(result_string, result_length);
				break;
			}
		}

		// AE: 0x00
		memset(acTemp, 0, sizeof(acTemp));
		cmd_data.buf[0] = 0x00;
		cmd_data.buf[1] = 0x00;
		isp_send_cmd(&cmd_data);

		scanning = 0;
	}

	if(yuv_snapshot_isp_deinit() < 0)
		printf("%s: yuv_snapshot_isp_deinit fail \r\n", __FUNCTION__);

exit:
	if(result_string) {
		free(result_string);
		result_string = NULL;
	}

	led_stop_qrcode_scanning();

	// restart jpeg snapshot
	extern u8* snapshot_buffer;
	jpeg_snapshot_initial(SNAPSHOT_WIDTH, SNAPSHOT_HEIGHT, SNAPSHOT_FPS, SNAPSHOT_LEVEL, (u32)snapshot_buffer, SNAPSHOT_BUFFER_SIZE);
	jpeg_snapshot_isp_config(2);
	jpeg_snapshot_create_sd_thread();

	qrcode_running = 0;

	vTaskDelete(NULL);
}

void example_qr_code_scanner_modified(void)
{
	if(xTaskCreate(example_qr_code_scanner_thread_modified, ((const char *)"example_qr_code_scanner_thread"), 1024, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_qr_code_scanner_thread) failed", __FUNCTION__);
}
