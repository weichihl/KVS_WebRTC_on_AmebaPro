#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include <example_entry.h>
#include "platform_autoconf.h"
#include <time.h>
#include <osdep_service.h>
#include <wifi_conf.h>
#include <lwip_netconf.h>
#include "gpio_api.h"   // mbed
#include "gpio_irq_api.h"   // mbed
#include <lwip/sockets.h>
#include <flash_api.h>
#include <device_lock.h>
#include "fatfs_sdcard_api.h"
#include "icc_api.h"
#include "app_setting.h"
#include "hal_power_mode.h"
#include "power_mode_api.h"
#include "sys_api_ext.h"


extern gpio_t gpio_amp;
extern gpio_irq_t gpio_btn;
extern gpio_t gpio_led_red;

static gpio_t gpio_sensor_pin;
static u32 last_time = 0;

extern char firebase_topic_name[64];
static flash_t flash;

static int led_switch = 0;

int tcp_topic_status = 0;

#include "gpio_api.h"   // mbed
#include "gpio_irq_api.h"   // mbed

static gpio_t gpio_red;
static gpio_t gpio_blue;

doorbell_ctr_t doorbell_handle;

uint8_t isp_used = 0;
uint8_t sd_used = 0;
uint8_t usb_used = 0;

extern int rtsTimezone;
extern _sema doorbell_handle_sema;
static void battoff_thread(void *param);
extern void doorbell_broadcast_set_packet_callback(void (*callback)(uint8_t *packet, size_t len));
extern void sntp_set_lasttime(long sec, long usec, unsigned int tick);
	
int set_playback_state(void)
{
	doorbell_handle.new_state = STATE_PLAYPACK;
	rtw_up_sema(&doorbell_handle_sema);
	return 0;
}

void icc_cmd_short_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	//rtw_up_sema(&doorbell_led_sema);
	//if(mp4_record_running()) {
		//mp4_record_stop();
	//}
  
        if(qrcode_scanner_running()){
          qrcode_scanner_stop();
        }else{
          	doorbell_handle.new_state = STATE_RING;
		rtw_up_sema(&doorbell_handle_sema);
        }
	       
	printf("\n\r%s\n\r", __FUNCTION__);
	printf("cmd = %x op = %x arg = %x\r\n",cmd,op,arg);
}

void icc_cmd_long_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
        //if(mp4_record_running()) {
		//mp4_record_stop();
	//}

	doorbell_handle.new_state = STATE_QRCODE;
	rtw_up_sema(&doorbell_handle_sema);
	printf("\n\r%s\n\r", __FUNCTION__);
	printf("cmd = %x op = %x arg = %x\r\n",cmd,op,arg);

}

void icc_cmd_pir_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{       
	doorbell_handle.new_state = STATE_ARAM;
	rtw_up_sema(&doorbell_handle_sema);
 
        printf("\n\r%s\n\r", __FUNCTION__);
	printf("cmd = %x op = %x arg = %x\r\n",cmd,op,arg);
}

void icc_cmd_poweron_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	//rtw_up_sema(&doorbell_led_sema);
        //extern _sema firebase_message_sema;
        //rtw_up_sema_from_isr(&firebase_message_sema);
	printf("\n\r%s\n\r", __FUNCTION__);
        
}

void icc_cmd_poweroff_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	printf("\n\r%s\n\r", __FUNCTION__);
}

void icc_cmd_rtc_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	printf("\n\r%s\n\r", __FUNCTION__);
	unsigned int tick = xTaskGetTickCount();

	printf("rtc time: UTC %s\r\n", ctime(&op));

	sntp_set_lasttime((long)op, (long)0, tick);
	rtsTimezone = 8;
}

void print_wake_reason(uint32_t wake_reason) {
    if (wake_reason == 0) {
        printf("no wake reason\r\n");
        return;
    }

    if ( wake_reason & LS_WAKE_EVENT_STIMER )      dbg_printf("wake from STIMER\r\n");
    if ( wake_reason & LS_WAKE_EVENT_GTIMER )      dbg_printf("wake from GTIMER\r\n");
    if ( wake_reason & LS_WAKE_EVENT_GPIO )        dbg_printf("wake from GPIO\r\n");
    if ( wake_reason & LS_WAKE_EVENT_PWM )         dbg_printf("wake from PWM\r\n");
    if ( wake_reason & LS_WAKE_EVENT_WLAN )        dbg_printf("wake from WLAN\r\n");
    if ( wake_reason & LS_WAKE_EVENT_UART )        dbg_printf("wake from UART\r\n");
    if ( wake_reason & LS_WAKE_EVENT_I2C )         dbg_printf("wake from I2C\r\n");
    if ( wake_reason & LS_WAKE_EVENT_ADC )         dbg_printf("wake from ADC\r\n");
    if ( wake_reason & LS_WAKE_EVENT_COMP )        dbg_printf("wake from COMP\r\n");
    if ( wake_reason & LS_WAKE_EVENT_SGPIO )       dbg_printf("wake from SGPIO\r\n");
    if ( wake_reason & LS_WAKE_EVENT_AON_GPIO )    dbg_printf("wake from AON_GPIO\r\n");
    if ( wake_reason & LS_WAKE_EVENT_AON_TIMER )   dbg_printf("wake from AON_TIMER\r\n");
    if ( wake_reason & LS_WAKE_EVENT_AON_RTC )     dbg_printf("wake from AON_RTC\r\n");
    if ( wake_reason & LS_WAKE_EVENT_AON_ADAPTER ) dbg_printf("wake from AON_ADAPTER\r\n");
    if ( wake_reason & LS_WAKE_EVENT_HS )          dbg_printf("wake from LS_WAKE_EVENT_HS\r\n");
}

void icc_req_get_ls_wake_reason_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    icc_user_cmd_t icc_cmd;
    uint32_t wake_reason;

    icc_cmd.cmd_w = cmd;
    wake_reason = icc_cmd.cmd_b.para0;

    print_wake_reason(wake_reason);
}

void send_icc_cmd_poweroff(void)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_POWEROFF;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_rtc(void)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_RTC;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_rtc_set(uint32_t t)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_RTC_SET;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, t, 2000000, NULL);
}

void icc_cmd_battoff_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	printf("\n\r%s\n\r", __FUNCTION__);
	printf("adc=0x%x\n\r", op);

	// battery off thread
	if(xTaskCreate(battoff_thread, ((const char*)"battoff_thread"), 1024, NULL, tskIDLE_PRIORITY + 3, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(battoff_thread) failed", __FUNCTION__);
}

void update_rtc_time(uint32_t t)
{
	static uint8_t rtc_updated = 0;
    unsigned int tick = xTaskGetTickCount();
	if(!rtc_updated) {
		rtc_updated = 1;
		sntp_set_lasttime((long)t, (long)0, tick);
		send_icc_cmd_rtc_set(t);

		//if(!qrcode_scanning)
			//setup_ch0_osd_attr();
	}
}

// media amebacam broadcast packet callback
static void packet_callback(uint8_t *packet, size_t len)
{
	packet[len] = 0;
	printf("%s\n\r", packet);
        printf("packet_callback--------------\n");
	if(memcmp(packet, "AMEBA:DISCOVER:", strlen("AMEBA:DISCOVER:")) == 0) {
		uint32_t t = 0;
		int i;

		for(i = strlen("AMEBA:DISCOVER:"); i < len - 4; i ++)
			t = t * 10 + (packet[i] - '0');
		
                printf("update_rtc_time--------------\n");
		update_rtc_time(t);
	}
#if 0
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
#endif	
}

static void battoff_thread(void *param)
{
	int i;

	//for(i = 0; i < 3; i ++) {
		//gpio_write(&gpio_led_red, 0);
		//vTaskDelay(250);
		//gpio_write(&gpio_led_red, 1);
		//vTaskDelay(250);
	//}

	// power off thread
	//if(xTaskCreate(poweroff_thread, ((const char*)"poweroff_thread"), 1024, NULL, tskIDLE_PRIORITY + 3, NULL) != pdPASS)
		//printf("\n\r%s xTaskCreate(poweroff_thread) failed", __FUNCTION__);

	//todo: send notification
	vTaskDelete(NULL);
}


void icc_thread(void *parm)
{
	doorbell_handle.doorbell_state = STATE_NORMAL;
	doorbell_handle.new_state = STATE_NORMAL;
        icc_init();
	icc_cmd_register(ICC_CMD_SHORT, (icc_user_cmd_callback_t) icc_cmd_short_handler, NULL);
        icc_cmd_register(ICC_CMD_PIR, (icc_user_cmd_callback_t) icc_cmd_pir_handler, NULL);
	icc_cmd_register(ICC_CMD_LONG, (icc_user_cmd_callback_t) icc_cmd_long_handler, NULL);
	icc_cmd_register(ICC_CMD_POWERON, (icc_user_cmd_callback_t) icc_cmd_poweron_handler, NULL);
	icc_cmd_register(ICC_CMD_POWEROFF, (icc_user_cmd_callback_t) icc_cmd_poweroff_handler, NULL);
	icc_cmd_register(ICC_CMD_RTC, (icc_user_cmd_callback_t) icc_cmd_rtc_handler, NULL);
	icc_cmd_register(ICC_CMD_BATTOFF, (icc_user_cmd_callback_t) icc_cmd_battoff_handler, NULL);
	icc_cmd_register(ICC_CMD_NOTIFY_LS_WAKE_REASON, (icc_user_cmd_callback_t)icc_req_get_ls_wake_reason_handler, ICC_CMD_NOTIFY_LS_WAKE_REASON);
	
	// amebacam broadcast example
	doorbell_broadcast_set_packet_callback(packet_callback);

	vTaskDelete(NULL);
}

void icc_task_func(void)
{
	if(xTaskCreate(icc_thread, ((const char*)"icc_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
				  printf("\n\r%s xTaskCreate(icc_thread) failed", __FUNCTION__);
}