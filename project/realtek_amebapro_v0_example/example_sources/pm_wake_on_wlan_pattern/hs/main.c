#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"

#include "platform_autoconf.h"

#include "wifi_conf.h"
#include <lwip_netconf.h>
#include <lwip/sockets.h>
#include <lwip/netif.h>

#include "hal_power_mode.h"
#include "power_mode_api.h"

#define SYSTEM_SUSPEND_FROM_LS (0)

#if SYSTEM_SUSPEND_FROM_LS
#include "icc_api.h"
#define ICC_CMD_REQ_STANDBY (0x10)
#endif

extern void console_init(void);
extern struct netif xnetif[NET_IF_NUM];

/**
 * How to send unicast to device in windows:
 * 1.   Open terminal with admin privilege
 * 2.   Check the arp table
 *          arp -a
 * 3.   If the device ip is not in arp table, then try to add it
 * 3.1  Check the interface idx:
 *          netsh interface ipv4 show interface
 * 3.2  If the idx is 10, device's IP is 192.168.1.123, device's mac is 00-12-34-56-78-90:
 *          netsh -c "interface ipv4" add neighbors 10 192.168.1.123 00-12-34-56-78-90
 * 4.   Check the arp table again, the IP should be a static item
 *
 * If you want to delete this IP from arp table:
 *      arp -d 192.168.1.123
 * 
 */

void set_tcp_pattern(wowlan_pattern_t *pattern)
{

	memset(pattern, 0, sizeof(wowlan_pattern_t));

    char buf[32];
	char mac[6];
	char ip_protocol[2] = {0x08, 0x00}; // IP {08,00} ARP {08,06}
	char ip_ver[1] = {0x45};
	char tcp_protocol[1] = {0x06}; // 0x06 for tcp
    char tcp_port[2] = {0x00, 0x50}; // port 80
	uint8_t * ip = LwIP_GetIP(&xnetif[0]);
	u8 uc_mask[5] = {0x3f, 0x70, 0x80, 0xc0, 0x33};

	// MAC DA
	wifi_get_mac_address(buf);
	sscanf(buf, "%02x:%02x:%02x:%02x:%02x:%02x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
	rtw_memcpy(pattern->eth_da, mac, 6);
	// IP
	rtw_memcpy(pattern->eth_proto_type, ip_protocol, 2);
	// IP ver+len
	rtw_memcpy(pattern->header_len, ip_ver, 1);
	// TCP
	rtw_memcpy(pattern->ip_proto, tcp_protocol, 1);
	// IP DA		
	rtw_memcpy(pattern->ip_da, ip, 4);
    // destination port
    rtw_memcpy(pattern->dest_port, tcp_port, 2);
	// mask
	rtw_memcpy(pattern->mask, uc_mask, 5);	

}


void wowlan_pattern_thread(void *param)
{
    int ret;

    while (1) {
        vTaskDelay(1000);
    	printf("\r\nwait for wifi connection...\r\n");
    	printf("\r\nplease use AT commands (ATW0, ATWC) to make wifi connection\r\n");
        while (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS) {
            vTaskDelay(1000);
        }

		wowlan_pattern_t test_pattern;
		set_tcp_pattern(&test_pattern);
		
		wifi_wowlan_set_pattern(test_pattern);

    	vTaskDelay(4000);

        if (rtl8195b_suspend(0) == 0 && wifi_is_ready_to_transceive(RTW_STA_INTERFACE) == RTW_SUCCESS) {
#if SYSTEM_SUSPEND_FROM_LS
            icc_init ();
            icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY, .cmd_b.para0 = 0 };
            icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // timeout 1000us
#else
            SleepPG(SLP_WLAN, 0, 1, 0);
#endif
        }

        printf("suspend fail\r\n");
        vTaskDelay(1000);
        rtl8195b_resume(0);
    }
}

void main(void)
{
	/* Initialize log uart and at command service */
        console_init();	
#if ISP_BOOT_MODE_ENABLE == 0
	/* pre-processor of application example */
	pre_example_entry();

	/* wlan intialization */
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
	wlan_network();
#endif
#endif
	if(xTaskCreate(wowlan_pattern_thread, ((const char*)"wowlan_pattern_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        printf("\r\n wowlan_pattern_thread: Create Task Error\n");
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

