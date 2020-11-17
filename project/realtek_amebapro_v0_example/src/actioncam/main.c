#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include <example_entry.h>
#include "platform_autoconf.h"
#include "hal_cache.h"
#include "icc_api.h"
#include "gpio_api.h"
#include <time.h>
#include "ff.h"
#include "fatfs_sdcard_api.h"
#include <wifi_conf.h>
#include <lwip_netconf.h>
#include "hal_flash_boot.h"
#include "pwmout_api.h"
#include <lwip/sockets.h>
#include <time.h>
#include "media_framework/example_media_framework.h"

extern void console_init(void);

#define AmebaPro_EVB     1
#define ActionCAM_Old    0
#define ActionCAM_New    0
#if AmebaPro_EVB
#define LED_RED_PIN      PH_3
#define LED_GREEN_PIN    PH_2
#define CHARGING_CHECK   0
#elif ActionCAM_Old
#define LED_RED_PIN      PE_7
#define LED_GREEN_PIN    PE_6
#define CHARGE_PIN       PE_2
#define CHARGING_CHECK   0
#elif ActionCAM_New
#define LED_RED_PIN      PC_8
#define LED_GREEN_PIN    PC_9
#define CHARGE_PIN       PC_0
#define CHARGING_CHECK   0
#endif
#define IR_LED_PIN       PG_5

#define IRLED_USE_PWM    0
#define PWM_PERIOD       1718	// 582Hz
#define CONTROL_PORT     8080
#define WATCHDOG_TIMEOUT 10000
#define WATCHDOG_REFRESH 8000

#define ICC_CMD_SHORT    0x10
#define ICC_CMD_LONG     0x11
#define ICC_CMD_POWERON  0x12
#define ICC_CMD_POWEROFF 0x13
#define ICC_CMD_RTC      0x14
#define ICC_CMD_RTC_SET  0x15
#define ICC_CMD_BATTOFF  0x16

#define SNAPSHOT_DIR     "PHOTO"
#define MP4_DIR          "VIDEO"
#define OTA_FILENAME     "ota_is_realtek.bin"

uint8_t isp_used = 0;
uint8_t sd_used = 0;
uint8_t usb_used = 0;

static uint8_t recording = 0;
static uint8_t no_sd_detected = 0;
static uint8_t qrcode_scanning = 0;
static uint8_t wifi_connected = 0;
static uint8_t usb_connected = 0;
static uint8_t is_power_on = 0;
static uint8_t sd_checking = 0;
static uint8_t sd_updating = 0;
static uint8_t snapshot_processing = 0;
static uint8_t md_detecting = 0;
static uint8_t md_recording = 0;
static uint8_t ir_led = 0;
static gpio_t gpio_led_red;
static gpio_t gpio_led_green;
#if CHARGING_CHECK && defined(CHARGE_PIN)
static gpio_t gpio_charge;
#endif
#if !IRLED_USE_PWM
static gpio_t gpio_ir_led;
#else
static pwmout_t pwm_ir_led;
#endif
static void *led_sema = NULL;
static void *sd_sema = NULL;
static void *md_sema = NULL;
static char sd_filename[64];
static fatfs_sd_params_t fatfs_sd;
static FIL f;

static void snapshot_thread(void *param);
static void poweroff_thread(void *param);
static void reboot_thread(void *param);
static void battoff_thread(void *param);
static void watchdog_thread(void *param);
static void control_thread(void *param);
static void osd_thread(void *param);
static void md_thread(void *param);
static void sd_update_thread(void *param);
void led_set_no_sd_detected(uint8_t value);
void md_set_detecting(uint8_t value);
extern void sntp_set_lasttime(long sec, long usec, unsigned int tick);

extern int rtsTimezone;
extern struct netif xnetif[];

void icc_cmd_short_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	printf("\n\r%s\n\r", __FUNCTION__);

	if(md_detecting) {
		printf("ignore due to md_detecting\n\r");
	}
	else if(recording) {
		mp4_to_sd_stop();
		recording = 0;
	}
	else if(qrcode_scanning) {
		qrcode_scanner_stop();
		qrcode_scanning = 0;
	}
	else {
		if(snapshot_processing || no_sd_detected || sd_updating)
			return;

		snapshot_processing = 1;

		// snapshot thread
		if(xTaskCreate(snapshot_thread, ((const char*)"snapshot_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(snapshot_thread) failed", __FUNCTION__);
	}
}

void icc_cmd_long_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	printf("\n\r%s\n\r", __FUNCTION__);

	if(md_detecting) {
		printf("ignore due to md_detecting\n\r");
	}
	else if(recording) {
		mp4_to_sd_stop();
		recording = 0;

		if(op == 1) {
			// qrcode
			qrcode_scanning = 1;
			example_qr_code_scanner_modified();
			rtw_up_sema(&led_sema);
		}
	}
	else if(qrcode_scanning) {
		if(op == 1) {
			qrcode_scanner_stop();
			qrcode_scanning = 0;
		}
	}
	else {
		if(op == 1) {
			// qrcode
			qrcode_scanning = 1;
			example_qr_code_scanner_modified();
			rtw_up_sema(&led_sema);
		}
		else {
			if(no_sd_detected || sd_updating)
				return;

			// recording
			DIR m_dir;
			fatfs_sd_get_param(&fatfs_sd);
			sprintf(sd_filename, "%s%s", fatfs_sd.drv, MP4_DIR);
			if(f_opendir(&m_dir, sd_filename) == 0)
				f_closedir(&m_dir);
			else
				f_mkdir(sd_filename);

			extern struct tm sntp_gen_system_time(int timezone);
			struct tm tm_now = sntp_gen_system_time(rtsTimezone);
			sprintf(sd_filename, "%s/%04d%02d%02d_%02d%02d%02d", MP4_DIR, tm_now.tm_year, tm_now.tm_mon, tm_now.tm_mday, tm_now.tm_hour, tm_now.tm_min, tm_now.tm_sec);

			recording = 1;
			mp4_to_sd_start(sd_filename);
			rtw_up_sema(&led_sema);
		}
	}
}

void icc_cmd_poweron_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	printf("\n\r%s\n\r", __FUNCTION__);

	is_power_on = 1;
	gpio_write(&gpio_led_red, 1);

	if(wifi_connected)
		gpio_write(&gpio_led_green, 1);

	SDIO_HOST_Type *psdioh = SDIO_HOST;
	if(psdioh->card_exist_b.sd_exist)
		led_set_no_sd_detected(0);
	else
		led_set_no_sd_detected(1);
}

void icc_cmd_poweroff_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	printf("\n\r%s\n\r", __FUNCTION__);

	// power off thread
	if(xTaskCreate(poweroff_thread, ((const char*)"poweroff_thread"), 1024, NULL, tskIDLE_PRIORITY + 3, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(poweroff_thread) failed", __FUNCTION__);
}

void icc_cmd_rtc_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	printf("\n\r%s\n\r", __FUNCTION__);

	//para0[24]=sec[6]:min[6]:hrs[5]:dow[3]
	//para1[32]=dom[5]:mon[4]:year[12]:doy[9]
	struct tm t = {0};
	icc_user_cmd_t icc_cmd;
	icc_cmd.cmd_w = cmd;
	t.tm_sec = (icc_cmd.cmd_b.para0 & (0x3F << 14)) >> 14;
	t.tm_min = (icc_cmd.cmd_b.para0 & (0x3F << 8)) >> 8;
	t.tm_hour = (icc_cmd.cmd_b.para0 & (0x1F << 3)) >> 3;
	t.tm_wday = icc_cmd.cmd_b.para0 & 0x7;
	t.tm_mday = (op & (0x1F << 25)) >> 25;
	t.tm_mon = (op & (0xF << 21)) >> 21;
	t.tm_year = (op & (0xFFF << 9)) >> 9;
	t.tm_yday = op & 0x1FF;

	time_t seconds = mktime(&t);
	printf("rtc time: UTC %s\r\n", ctime(&seconds));
	sntp_set_lasttime(seconds, 0, xTaskGetTickCount());
	rtsTimezone = 8;
}

void icc_cmd_battoff_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	printf("\n\r%s\n\r", __FUNCTION__);
	printf("adc=0x%x\n\r", op);

	// battery off thread
	if(xTaskCreate(battoff_thread, ((const char*)"battoff_thread"), 1024, NULL, tskIDLE_PRIORITY + 3, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(battoff_thread) failed", __FUNCTION__);
}

void send_icc_cmd_rtc(void)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_RTC;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_rtc_set(uint32_t seconds)
{
	struct tm *t = localtime(&seconds);

	//para0[24]=sec[6]:min[6]:hrs[5]:dow[3]
	//para1[32]=dom[5]:mon[4]:year[12]:doy[9]
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_RTC_SET;
	cmd.cmd_b.para0 =
		(t->tm_sec << 14) |
		(t->tm_min << 8) |
		(t->tm_hour << 3) |
		t->tm_wday;
	uint32_t para1 =
		(t->tm_mday << 25) |
		(t->tm_mon << 21) |
		(t->tm_year << 9) |
		t->tm_yday;

	icc_cmd_send(cmd.cmd_w, para1, 2000000, NULL);
}

void update_rtc_time(uint32_t t)
{
	static uint8_t rtc_updated = 0;

	if(!rtc_updated) {
		rtc_updated = 1;
		sntp_set_lasttime(t, 0, xTaskGetTickCount());
		send_icc_cmd_rtc_set(t);

		if(!qrcode_scanning)
			setup_ch0_osd_attr();
	}
}

// media amebacam broadcast packet callback
static void packet_callback(uint8_t *packet, size_t len)
{
	packet[len] = 0;
	printf("%s\n\r", packet);

	if(memcmp(packet, "AMEBA:DISCOVER:", strlen("AMEBA:DISCOVER:")) == 0) {
		uint32_t t = 0;
		int i;

		for(i = strlen("AMEBA:DISCOVER:"); i < len - 4; i ++)
			t = t * 10 + (packet[i] - '0');

		update_rtc_time(t);
	}

	if(memcmp(packet, "AMEBA:OTA:", strlen("AMEBA:OTA:")) == 0) {
		char name[13];
		uint8_t *mac = LwIP_GetMAC(&xnetif[0]);
		sprintf(name, "Ameba_%02x%02x%02x", mac[3], mac[4], mac[5]);

		if(memcmp(packet + strlen("AMEBA:OTA:"), name, strlen(name)) == 0) {
			char *ip_str = packet + strlen("AMEBA:OTA:") + strlen(name) + 1;
			char *ip_str_end = strstr(ip_str, ":");
			*ip_str_end = 0;
			char *port_str = ip_str_end + 1;
			printf("OTA from %s:%d\n\r", ip_str, atoi(port_str));

			if(qrcode_scanning) {
				qrcode_scanner_stop();
				qrcode_scanning = 0;

				// OTA
				update_ota_local(ip_str, atoi(port_str));
			}
			else {
				printf("ignore OTA if !qrcode_scanning\n\r");
			}
		}
	}
}

// SD callback
void sdh_card_insert_callback(void *pdata)
{
	if(is_power_on && !sd_checking) {
		if(sd_sema)
			rtw_up_sema_from_isr(&sd_sema);
	}
}

void sdh_card_remove_callback(void *pdata)
{
	if(is_power_on && !sd_checking) {
		if(sd_sema)
			rtw_up_sema_from_isr(&sd_sema);
	}
}

// USB UVC driver callback for stream on
void streaming_on_callback(void){
	setup_ch0_osd_attr();
}

// USB MSC driver callback for disconnecting USB
void usbd_msc_suspend(struct usb_composite_dev *cdev)
{
	static uint8_t is_called = 0;

	printf("usb disconnected\n\r");

	if(!is_called)
		is_called = 1;
	else
		return;

	// set target example
	char *target_example = (char *) 0x71fffff0;
	strcpy(target_example, "reboot");
	dcache_clean_by_addr((uint32_t *) target_example, 16);

	// reboot thread
	if(xTaskCreate(reboot_thread, ((const char*)"reboot_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(reboot_thread) failed", __FUNCTION__);
}

// USB blank driver callback for connecting USB
int fun_set_alt_callback(struct usb_function *f, unsigned interface, unsigned alt)
{
	printf("usb connected\n\r");
	usb_connected = 1;

	// set target example
	char *target_example = (char *) 0x71fffff0;
	SDIO_HOST_Type *psdioh = SDIO_HOST;
	if(psdioh->card_exist_b.sd_exist)
		strcpy(target_example, "mass");
	else
		strcpy(target_example, "uvc");
	dcache_clean_by_addr((uint32_t *) target_example, 16);

	// reboot thread
	if(xTaskCreate(reboot_thread, ((const char*)"reboot_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(reboot_thread) failed", __FUNCTION__);
}

static void usbd_blank_thread(void *param)
{
	int status = 0;
	_usb_init();
	status = wait_usb_ready();
	if(status != 0){
		if(status == 2)
			printf("\r\n NO USB device attached\n");
		else
			printf("\r\n USB init fail\n");
		goto exit;
	}
	usbd_blank_init();

exit:
	vTaskDelete(NULL);
}

void led_stop_recording(void)
{
	recording = 0;
}

void led_stop_qrcode_scanning(void)
{
	qrcode_scanning = 0;
}

void led_set_no_sd_detected(uint8_t value)
{
	no_sd_detected = value;

	if(no_sd_detected) {
		if(led_sema)
			rtw_up_sema(&led_sema);
	}
}

void ir_led_enable(void)
{
	if(ir_led == 0) {
#if IRLED_USE_PWM
		// IR LED PWM
		pwmout_init(&pwm_ir_led, IR_LED_PIN);
		pwmout_period_us(&pwm_ir_led, PWM_PERIOD);
		pwmout_pulsewidth_us(&pwm_ir_led, PWM_PERIOD/6);
#else
		gpio_write(&gpio_ir_led, 1);
#endif
		// gray mode
		sensor_external_set_gray_mode(1);

		ir_led = 1;
	}
}

void ir_led_disable(void)
{
	if(ir_led == 1) {
#if IRLED_USE_PWM
		// IR LED PWM
		pwmout_free(&pwm_ir_led);
#else
		gpio_write(&gpio_ir_led, 0);
#endif
		// gray mode
		sensor_external_set_gray_mode(0);

		ir_led = 0;
	}
}

uint8_t get_ir_led(void)
{
	return ir_led;
}

static void led_thread(void *param)
{
	rtw_init_sema(&led_sema, 0);

	while(1) {
		rtw_down_sema(&led_sema);

		if(no_sd_detected) {
			while(no_sd_detected) {
				if(qrcode_scanning) {
					gpio_write(&gpio_led_green, 0);
				}
				else {
					if(wifi_connected)
						gpio_write(&gpio_led_green, 1);
					else
						gpio_write(&gpio_led_green, 0);
				}

				gpio_write(&gpio_led_red, 0);
				vTaskDelay(250);
				gpio_write(&gpio_led_red, 1);
				vTaskDelay(250);

				if(qrcode_scanning) {
					gpio_write(&gpio_led_green, 1);
				}
				else {
					if(wifi_connected)
						gpio_write(&gpio_led_green, 1);
					else
						gpio_write(&gpio_led_green, 0);
				}

				gpio_write(&gpio_led_red, 0);
				vTaskDelay(250);
				gpio_write(&gpio_led_red, 1);
				vTaskDelay(250);
			}
		}
		else {
			if(recording || md_recording) {
				while(recording || md_recording) {
					gpio_write(&gpio_led_red, 0);
					vTaskDelay(500);
					gpio_write(&gpio_led_red, 1);
					vTaskDelay(500);
				}

				gpio_write(&gpio_led_red, 1);
			}

			if(qrcode_scanning) {
				while(qrcode_scanning) {
					gpio_write(&gpio_led_green, 0);
					vTaskDelay(500);
					gpio_write(&gpio_led_green, 1);
					vTaskDelay(500);
				}

				if(wifi_connected)
					gpio_write(&gpio_led_green, 1);
				else
					gpio_write(&gpio_led_green, 0);
			}

			if(sd_updating) {
				while(sd_updating) {
					gpio_write(&gpio_led_red, 0);
					vTaskDelay(100);
					gpio_write(&gpio_led_red, 1);
					vTaskDelay(100);
				}

				gpio_write(&gpio_led_red, 1);
			}
		}
	}
}

static void sd_thread(void *param)
{
	rtw_init_sema(&sd_sema, 0);

	while(1) {
		rtw_down_sema(&sd_sema);
		sd_checking = 1;

		vTaskDelay(50);	// delay to get correct sd voltage

		SDIO_HOST_Type *psdioh = SDIO_HOST;
		if(psdioh->card_exist_b.sd_exist) {
			led_set_no_sd_detected(0);
			SD_DeInit();
			SD_Init();
		}
		else {
			led_set_no_sd_detected(1);
		}

		sd_checking = 0;
	}
}

static void control_thread(void *param)
{
	struct sockaddr_in server_addr;
	int server_fd = -1;

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) >= 0) {
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(CONTROL_PORT);
		server_addr.sin_addr.s_addr = INADDR_ANY;

		if(bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
			printf("ERROR: bind\n\r");
			goto exit;
		}

		if(listen(server_fd, 3) != 0) {
			printf("ERROR: listen\n\r");
			goto exit;
		}

		while(1) {
			struct sockaddr_in client_addr;
			unsigned int client_addr_size = sizeof(client_addr);
			int fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_addr_size);

			if(fd >= 0) {
				unsigned char buf[100];
				int recv_timeout, read_size;

				// recv timeout 10s
				recv_timeout = 10 * 1000;
				if(setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &recv_timeout, sizeof(recv_timeout)) != 0)
					printf("ERROR: setsockopt\n\r");

				if((read_size = read(fd, buf, sizeof(buf))) > 0) {
					buf[read_size] = 0;
					printf("%s\n\r", buf);

					if(memcmp(buf, "AMEBA:OTA:", strlen("AMEBA:OTA:")) == 0) {
						char *ip_str = buf + strlen("AMEBA:OTA:");
						char *ip_str_end = strstr(ip_str, ":");
						*ip_str_end = 0;
						char *port_str = ip_str_end + 1;
						printf("OTA from %s:%d\n\r", ip_str, atoi(port_str));

						if(qrcode_scanning) {
							qrcode_scanner_stop();
							qrcode_scanning = 0;

							// OTA
							update_ota_local(ip_str, atoi(port_str));
						}
						else {
							printf("ignore OTA if !qrcode_scanning\n\r");
						}
					}
					else if(memcmp(buf, "AMEBA:CONTROL:", strlen("AMEBA:CONTROL:")) == 0) {
						char *control_str = buf + strlen("AMEBA:CONTROL:");

						if(memcmp(control_str, "IRLED:1", strlen("IRLED:1")) == 0) {
							printf("IR LED ON\n\r");
							ir_led_enable();
						}
						else if(memcmp(control_str, "IRLED:0", strlen("IRLED:0")) == 0) {
							printf("IR LED OFF\n\r");
							ir_led_disable();
						}
						else if(memcmp(control_str, "MD:1", strlen("MD:1")) == 0) {
							printf("MD enable\n\r");
							md_set_detecting(1);
						}
						else if(memcmp(control_str, "MD:0", strlen("MD:0")) == 0) {
							printf("MD disable\n\r");
							md_set_detecting(0);
						}
					}
				}

				close(fd);
			}
			else {
				printf("ERROR: accept\n\r");
			}
		}
	}
	else {
		printf("ERROR: socket\n\r");
		goto exit;
	}

exit:
	vTaskDelete(NULL);
}

static void osd_thread(void *param)
{
	while(1) {
		vTaskDelay(3600*1000);
		extern struct tm sntp_gen_system_time(int timezone);
		struct tm current_tm = sntp_gen_system_time(8);

		if((current_tm.tm_hour != 0) && (current_tm.tm_hour != 23)) {
			if(!qrcode_scanning)
				refresh_osd_date();
		}
	}
}

void md_set_detecting(uint8_t value)
{
	if(!md_detecting && (value == 1)) {
		if(recording) {
			mp4_to_sd_stop();
			recording = 0;
		}
		else if(qrcode_scanning) {
			qrcode_scanner_stop();
			qrcode_scanning = 0;
		}

		// wait max 5s for mp4 or qrcode
		extern uint8_t mp4_to_sd_running(void);
		extern uint8_t qrcode_scanner_running(void);
		int i;
		for(i = 0; i < 50; i ++) {
			if(!mp4_to_sd_running() && !qrcode_scanner_running())
				break;
			vTaskDelay(100);
		}

		md_detecting = 1;
		extern void setup_md_attr(uint8_t enable);
		setup_md_attr(1);

		if(md_sema)
			rtw_up_sema(&md_sema);
	}
	else if(md_detecting && (value == 0)){
		md_detecting = 0;
		vTaskDelay(200);	// wait for md_thread
		extern void setup_md_attr(uint8_t enable);
		setup_md_attr(0);
	}
}

static void md_thread(void *param)
{
	int count = 0, status = 0;

	rtw_init_sema(&md_sema, 0);

	while(1) {
		rtw_down_sema(&md_sema);

		if(rts_av_init() == 0) {
			while(md_detecting) {
				if((status = rts_check_isp_md_status(0)) == 1)
					printf("motion detected!\n\r");

				if(!md_recording && (status == 1)) {
					if(no_sd_detected || sd_updating)
						continue;

					DIR m_dir;
					fatfs_sd_get_param(&fatfs_sd);
					sprintf(sd_filename, "%s%s", fatfs_sd.drv, MP4_DIR);
					if(f_opendir(&m_dir, sd_filename) == 0)
						f_closedir(&m_dir);
					else
						f_mkdir(sd_filename);

					extern struct tm sntp_gen_system_time(int timezone);
					struct tm tm_now = sntp_gen_system_time(rtsTimezone);
					sprintf(sd_filename, "%s/%04d%02d%02d_%02d%02d%02d", MP4_DIR, tm_now.tm_year, tm_now.tm_mon, tm_now.tm_mday, tm_now.tm_hour, tm_now.tm_min, tm_now.tm_sec);

					md_recording = 1;
					mp4_to_sd_start(sd_filename);
					rtw_up_sema(&led_sema);
					count = 0;
					printf("md_recording start\n\r");
				}
				else if(md_recording) {
					if(status == 0) {
						count ++;

						if(count == 600) {
							mp4_to_sd_stop();
							md_recording = 0;
							printf("md_recording stop\n\r");
						}
					}
					else {
						count = 0;
					}
				}

				vTaskDelay(100);
			}

			if(md_recording) {
				mp4_to_sd_stop();
				md_recording = 0;
				printf("md_recording stop\n\r");
			}

			rts_av_release();
		}
		else {
			printf("ERROR: rts_av_init\n\r");
		}
	}
}

static void sd_update_thread(void *param)
{
	int ret;

	vTaskDelay(3000);

	if(usb_connected)
		goto exit;

	printf("%s\n\r", __FUNCTION__);
	SDIO_HOST_Type *psdioh = SDIO_HOST;
	if(psdioh->card_exist_b.sd_exist) {
		if((ret = fatfs_sd_get_param(&fatfs_sd)) < 0) {
			fatfs_sd_init();
			ret = fatfs_sd_get_param(&fatfs_sd);
		}

		if(ret < 0) {
			printf("ERROR: fatfs_sd_get_param\n");
		}
		else {
			strcpy(sd_filename, fatfs_sd.drv);
			strcat(sd_filename, OTA_FILENAME);
			ret = f_open(&f, sd_filename, FA_READ);

			if(ret) {
				printf("%s not found\n\r", sd_filename);
			}
			else {
				f_close(&f);
				sd_updating = 1;

				if(led_sema)
					rtw_up_sema(&led_sema);

				ret = sdcard_update_ota(OTA_FILENAME);
				sd_updating = 0;

				if(!ret) {
					printf("[%s] Ready to reboot\n\r", __FUNCTION__);
					ota_platform_reset();
				}
			}
		}
	}

exit:
	vTaskDelete(NULL);
}

static void watchdog_thread(void *param)
{
	while(1) {
		watchdog_refresh();
		vTaskDelay(WATCHDOG_REFRESH);
	}
}

#if CHARGING_CHECK && defined(CHARGE_PIN)
static void charge_thread(void *param)
{
	while(1) {
		if(is_power_on) {
			// charging: charge pin low
			if(gpio_read(&gpio_charge) == 0) {
				vTaskDelay(1000);

				if(usb_connected)
					continue;

				// power off thread
				if(xTaskCreate(poweroff_thread, ((const char*)"poweroff_thread"), 1024, NULL, tskIDLE_PRIORITY + 3, NULL) != pdPASS)
					printf("\n\r%s xTaskCreate(poweroff_thread) failed", __FUNCTION__);

				break;
			}
		}

		vTaskDelay(1000);
	}

	vTaskDelete(NULL);
}
#endif

static void snapshot_thread(void *param)
{
	DIR m_dir;

	fatfs_sd_get_param(&fatfs_sd);
	sprintf(sd_filename, "%s%s", fatfs_sd.drv, SNAPSHOT_DIR);

	if(f_opendir(&m_dir, sd_filename) == 0)
		f_closedir(&m_dir);
	else
		f_mkdir(sd_filename);

	extern struct tm sntp_gen_system_time(int timezone);
	struct tm tm_now = sntp_gen_system_time(rtsTimezone);
	sprintf(sd_filename, "%s/%04d%02d%02d_%02d%02d%02d", SNAPSHOT_DIR, tm_now.tm_year, tm_now.tm_mon, tm_now.tm_mday, tm_now.tm_hour, tm_now.tm_min, tm_now.tm_sec);

	gpio_write(&gpio_led_red, 0);
	extern void setup_ch2_osd_attr(void);
	jpeg_snapshot_isp_callback((int) setup_ch2_osd_attr);
	extern void jpeg_snapshot_sd_set_filename(char *file_name);
	jpeg_snapshot_sd_set_filename(sd_filename);
	jpeg_snapshot_isp();
	gpio_write(&gpio_led_red, 1);

	snapshot_processing = 0;
	vTaskDelete(NULL);
}

static void poweroff_thread(void *param)
{
	if(recording) {
		mp4_to_sd_stop();
		recording = 0;
	}
	else if(qrcode_scanning) {
		qrcode_scanner_stop();
		qrcode_scanning = 0;
	}
	else if(md_detecting){
		md_detecting = 0;
		vTaskDelay(200);	// wait for md_thread
		extern void setup_md_attr(uint8_t enable);
		setup_md_attr(0);
	}

	// wait max 5s for mp4 or qrcode
	extern uint8_t mp4_to_sd_running(void);
	extern uint8_t qrcode_scanner_running(void);
	int i;
	for(i = 0; i < 50; i ++) {
		if(!mp4_to_sd_running() && !qrcode_scanner_running())
			break;
		vTaskDelay(100);
	}

	// deinit wlan
	if(rltk_wlan_running(0))
		wifi_off();
	// turn off isp
	if(isp_used) {
		printf("\n\rturn off isp ++\n\r");
		*((uint32_t *)(0x4000020C)) = 0;
		printf("\n\rturn off isp --\n\r");
	}
	// dinit sdcard
	if(sd_used) {
		printf("\n\rSD_DeInit ++\n\r");
		SD_DeInit();
		printf("\n\rSD_DeInit --\n\r");
	}
	// deinit usb
	if(usb_used) {
		printf("\n\rusb_deinit ++\n\r");
		usb_deinit();
		printf("\n\rusb_deinit --\n\r");
	}

	icc_user_cmd_t replied_cmd;
	replied_cmd.cmd_b.cmd = ICC_CMD_POWEROFF;
	replied_cmd.cmd_b.para0 = 0;
	icc_cmd_send(replied_cmd.cmd_w, 0, 2000000, NULL);

	while(1) {
		gpio_write(&gpio_led_red, 0);
		gpio_write(&gpio_led_green, 0);
	}
}

static void reboot_thread(void *param)
{
	vTaskDelay(1000);	// delay for usb init done

	// deinit wlan
	if(rltk_wlan_running(0))
		wifi_off();
	// turn off isp
	if(isp_used) {
		printf("\n\rturn off isp ++\n\r");
		*((uint32_t *)(0x4000020C)) = 0;
		printf("\n\rturn off isp --\n\r");
	}
	// dinit sdcard
	if(sd_used) {
		printf("\n\rSD_DeInit ++\n\r");
		SD_DeInit();
		printf("\n\rSD_DeInit --\n\r");
	}
	// deinit usb
	if(usb_used) {
		printf("\n\rusb_deinit ++\n\r");
		usb_deinit();
		printf("\n\rusb_deinit --\n\r");
	}
	// turn off fast boot
	printf("\n\rturn off fast boot ++\n\r");
	*((uint32_t *)(0x50000828)) = 0;
	printf("\n\rturn off fast boot --\n\r");
	// use wdt reset
	printf("\n\rwdt reset ++\n\r");
	watchdog_stop();
	watchdog_init(100);
	watchdog_start();
	printf("\n\rwdt reset --\n\r");

	while(1) vTaskDelay(1000);
}

static void battoff_thread(void *param)
{
	int i;

	for(i = 0; i < 3; i ++) {
		gpio_write(&gpio_led_red, 0);
		vTaskDelay(250);
		gpio_write(&gpio_led_red, 1);
		vTaskDelay(250);
	}

	// power off thread
	if(xTaskCreate(poweroff_thread, ((const char*)"poweroff_thread"), 1024, NULL, tskIDLE_PRIORITY + 3, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(poweroff_thread) failed", __FUNCTION__);

	vTaskDelete(NULL);
}

typedef int (*wlan_init_done_ptr)(void);
extern wlan_init_done_ptr p_wlan_init_done_callback;
static void _connect_hdl(char* buf, int buf_len, int flags, void* userdata)
{
	wifi_connected = 1;

	if(is_power_on)
		gpio_write(&gpio_led_green, 1);
}
static void _disconnect_hdl(char* buf, int buf_len, int flags, void* userdata)
{
	wifi_connected = 0;
	gpio_write(&gpio_led_green, 0);
}
static void wificonnect_thread(void *param)
{
	// Clear WLAN init done callback to prevent re-enter init sequence at each wlan init
	p_wlan_init_done_callback = NULL;

#if 0
	// sta mode to fixed ap
	char *ssid = "cube";
	char *passwd = "12345678";

	wifi_reg_event_handler(WIFI_EVENT_CONNECT, _connect_hdl, NULL);
	wifi_reg_event_handler(WIFI_EVENT_DISCONNECT, _disconnect_hdl, NULL);

	if(wifi_connect((unsigned char *) ssid, RTW_SECURITY_WPA2_AES_PSK, 
		(unsigned char *) passwd, strlen(ssid), strlen(passwd), 0, NULL) == RTW_SUCCESS) {

		LwIP_DHCP(0, DHCP_START);
	}
#else
	// sta mode with wlan fast connect
	wifi_reg_event_handler(WIFI_EVENT_CONNECT, _connect_hdl, NULL);
	wifi_reg_event_handler(WIFI_EVENT_DISCONNECT, _disconnect_hdl, NULL);
	wlan_init_done_callback();
#endif

	vTaskDelete(NULL);
}
static int _wlan_init_done_callback(void)
{
	// wifi connect thread
	if(xTaskCreate(wificonnect_thread, ((const char*)"wificonnect_thread"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(wificonnect_thread) failed", __FUNCTION__);
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	/* Initialize log uart and at command service */
	console_init();	

	fw_img_export_info_type_t *pfw_image_info = get_fw_img_info_tbl();
	printf("loaded_fw_idx=%d, fw1_valid=%d, fw1_sn=%d, fw2_valid=%d, fw2_sn=%d, \n\r", pfw_image_info->loaded_fw_idx, pfw_image_info->fw1_valid, pfw_image_info->fw1_sn, pfw_image_info->fw2_valid, pfw_image_info->fw2_sn);

	// WatchDog
	watchdog_init(WATCHDOG_TIMEOUT);
	watchdog_start();

#if ISP_BOOT_MODE_ENABLE == 0
	/* pre-processor of application example */
	pre_example_entry();

	/* wlan intialization */
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
//	wlan_network();
#endif
#endif
	/* Execute application example */
//	example_entry();

	// LED GPIO
	gpio_init(&gpio_led_red, LED_RED_PIN);
	gpio_dir(&gpio_led_red, PIN_OUTPUT);
	gpio_mode(&gpio_led_red, PullDown);
	gpio_init(&gpio_led_green, LED_GREEN_PIN);
	gpio_dir(&gpio_led_green, PIN_OUTPUT);
	gpio_mode(&gpio_led_green, PullDown);

#if CHARGING_CHECK && defined(CHARGE_PIN)
	// CHARGE GPIO
	gpio_init(&gpio_charge, CHARGE_PIN);
	gpio_dir(&gpio_charge, PIN_INPUT);
	gpio_mode(&gpio_charge, PullNone);
#endif

#if !IRLED_USE_PWM
	// IR LED GPIO
	gpio_init(&gpio_ir_led, IR_LED_PIN);
	gpio_dir(&gpio_ir_led, PIN_OUTPUT);
	gpio_mode(&gpio_ir_led, PullDown);
#endif
	char *target_example = (char *) 0x71fffff0;
	target_example[15] = 0;
	if(strcmp(target_example, "mass") == 0) {
		memset(target_example, 0, 16);
		dcache_clean_by_addr ((uint32_t *) target_example, 16);

		isp_used = 0;
		sd_used = 1;
		usb_used = 1;
		is_power_on = 1;
		gpio_write(&gpio_led_red, 1);

		// MSC example
		example_mass_storage();

		// ICC
		icc_init();
		icc_cmd_register(ICC_CMD_POWERON, (icc_user_cmd_callback_t) icc_cmd_poweron_handler, NULL);
		icc_cmd_register(ICC_CMD_POWEROFF, (icc_user_cmd_callback_t) icc_cmd_poweroff_handler, NULL);
		icc_cmd_register(ICC_CMD_RTC, (icc_user_cmd_callback_t) icc_cmd_rtc_handler, NULL);
		icc_cmd_register(ICC_CMD_BATTOFF, (icc_user_cmd_callback_t) icc_cmd_battoff_handler, NULL);
		send_icc_cmd_rtc();	// to get rtc if reboot
	}
	else if(strcmp(target_example, "uvc") == 0) {
		memset(target_example, 0, 16);
		dcache_clean_by_addr ((uint32_t *) target_example, 16);

		isp_used = 1;
		sd_used = 0;
		usb_used = 1;
		is_power_on = 1;
		gpio_write(&gpio_led_red, 1);

		// UVC example
		example_media_uvcd();

		// ICC
		icc_init();
		icc_cmd_register(ICC_CMD_POWERON, (icc_user_cmd_callback_t) icc_cmd_poweron_handler, NULL);
		icc_cmd_register(ICC_CMD_POWEROFF, (icc_user_cmd_callback_t) icc_cmd_poweroff_handler, NULL);
		icc_cmd_register(ICC_CMD_RTC, (icc_user_cmd_callback_t) icc_cmd_rtc_handler, NULL);
		icc_cmd_register(ICC_CMD_BATTOFF, (icc_user_cmd_callback_t) icc_cmd_battoff_handler, NULL);
		send_icc_cmd_rtc();	// to get rtc if reboot
	}
	else {
		if(strcmp(target_example, "reboot") == 0) {
			memset(target_example, 0, 16);
			dcache_clean_by_addr ((uint32_t *) target_example, 16);

			is_power_on = 1;
			gpio_write(&gpio_led_red, 1);
		}

		isp_used = 1;
		sd_used = 1;
		usb_used = 1;

		p_wlan_init_done_callback = _wlan_init_done_callback;
		wlan_network();

		// steaming + mp4 + snapshot example
		example_media_framework_modified();

		// amebacam broadcast example
		extern void amebacam_broadcast_set_packet_callback(void (*callback)(uint8_t *packet, size_t len));
		amebacam_broadcast_set_packet_callback(packet_callback);
		media_amebacam_broadcast_modified();

		// USB
		if(xTaskCreate(usbd_blank_thread, ((const char*)"usbd_blank_thread"), 256, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(usbd_blank_thread) failed", __FUNCTION__);

		// ICC
		icc_init();
		icc_cmd_register(ICC_CMD_SHORT, (icc_user_cmd_callback_t) icc_cmd_short_handler, NULL);
		icc_cmd_register(ICC_CMD_LONG, (icc_user_cmd_callback_t) icc_cmd_long_handler, NULL);
		icc_cmd_register(ICC_CMD_POWERON, (icc_user_cmd_callback_t) icc_cmd_poweron_handler, NULL);
		icc_cmd_register(ICC_CMD_POWEROFF, (icc_user_cmd_callback_t) icc_cmd_poweroff_handler, NULL);
		icc_cmd_register(ICC_CMD_RTC, (icc_user_cmd_callback_t) icc_cmd_rtc_handler, NULL);
		icc_cmd_register(ICC_CMD_BATTOFF, (icc_user_cmd_callback_t) icc_cmd_battoff_handler, NULL);
		send_icc_cmd_rtc();	// to get rtc if reboot

		// LED thread
		if(xTaskCreate(led_thread, ((const char*)"led_thread"), 256, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(led_thread) failed", __FUNCTION__);

		// SD thread
		if(xTaskCreate(sd_thread, ((const char*)"sd_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(sd_thread) failed", __FUNCTION__);

		// Control thread
		if(xTaskCreate(control_thread, ((const char*)"control_thread"), 1024, NULL, tskIDLE_PRIORITY + 5, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(control_thread) failed", __FUNCTION__);

		// SD update thread
		if(xTaskCreate(sd_update_thread, ((const char*)"sd_update_thread"), 1024, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(sd_update_thread) failed", __FUNCTION__);

		// MD thread
		if(xTaskCreate(md_thread, ((const char*)"md_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(md_thread) failed", __FUNCTION__);

#if CHARGING_CHECK && defined(CHARGE_PIN)
		// charge thread
		if(xTaskCreate(charge_thread, ((const char*)"charge_thread"), 256, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(charge_thread) failed", __FUNCTION__);
#endif
	}

	// WatchDog thread
	if(xTaskCreate(watchdog_thread, ((const char*)"watchdog_thread"), 1024, NULL, tskIDLE_PRIORITY + 5, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(watchdog_thread) failed", __FUNCTION__);

	if(isp_used) {
		// OSD thread
		if(xTaskCreate(osd_thread, ((const char*)"osd_thread"), 256, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(osd_thread) failed", __FUNCTION__);
	}

	/*Enable Schedule, Start Kernel*/
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
	#ifdef PLATFORM_FREERTOS
	vTaskStartScheduler();
	#endif
#else
	RtlConsolTaskRom(NULL);
#endif
}
