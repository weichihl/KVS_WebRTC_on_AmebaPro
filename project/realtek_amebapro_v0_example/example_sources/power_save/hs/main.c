#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include "platform_autoconf.h"
#include "log_service.h"

#include "wifi_conf.h"
#include <lwip_netconf.h>
#include <lwip/sockets.h>
#include <lwip/netif.h>

#include "icc_api.h"
#include "sys_api_ext.h"

#include "hal_power_mode.h"
#include "power_mode_api.h"

extern void console_init(void);

extern struct netif xnetif[NET_IF_NUM];

/**
 * Lunch a thread to send AT command automatically for a long run test
 */
#define LONG_RUN_TEST   (0)

#define ICC_CMD_REQ_DEEPSLEEP                   (0x10)
#define ICC_CMD_REQ_DEEPSLEEP_STIMER_DURATION   (0x11)

#define ICC_CMD_REQ_STANDBY                     (0x20)
#define ICC_CMD_REQ_STANDBY_STIMER_DURATION     (0x21)
#define ICC_CMD_REQ_STANDBY_GPIO_PIN            (0x22)
#define ICC_CMD_REQ_STANDBY_STIMER_WAKE         (0x23)
#define ICC_CMD_REQ_STANDBY_GPIO_WAKE           (0x24)
#define ICC_CMD_REQ_STANDBY_GPIO_SET            (0x25)
#define ICC_CMD_REQ_STANDBY_GPIO13_SET          (0x26)

#define ICC_CMD_REQ_GET_LS_WAKE_REASON          (0x30)
#define ICC_CMD_NOTIFY_LS_WAKE_REASON           (0x31)

static char your_ssid[33]   = "your_ssid";
static char your_pw[33]     = "your_pw";
//static rtw_security_t sec   = RTW_SECURITY_OPEN;
static rtw_security_t sec   = RTW_SECURITY_WPA2_AES_PSK;

static TaskHandle_t wowlan_thread_handle = NULL;

static char server_ip[16] = "192.168.1.100";
static uint16_t server_port = 5566;
static int enable_tcp_keep_alive = 0;
static uint32_t interval_ms = 30000;
static uint32_t resend_ms = 10000;

static int enable_wowlan_pattern = 0;

void print_PS_help(void) {
    printf("PS=[deepsleep|standby|sleeppg|wowlan|ls_wake_reason|tcp_keep_alive|wowlan_pattern],[options]\r\n");
#if 1
    printf("\r\n");
    printf("PS=deepsleep\r\n");
    printf("\tdeepsleep for default 1 minute\r\n");
    printf("PS=deepsleep,stimer=10\r\n");
    printf("\tdeepsleep for 10 seconds\r\n");
    printf("PS=deepsleep,gpio\r\n");
    printf("\tdeepsleep and configure GPIOA_13 as wakeup source\r\n");

    printf("\r\n");
    printf("PS=standby\r\n");
    printf("\tstandby for default 1 minute\r\n");
    printf("PS=standby,stimer=10\r\n");
    printf("\tstandby for 10 seconds\r\n");
    printf("PS=standby,gpio=2\r\n");
    printf("\tstandby and configure GPIOA_2 as wakeup source\r\n");
    printf("PS=standby,stimer=10,stimer_wake=5\r\n");
    printf("\tstandby for 10 seconds, and repeat it for 5 times then wake HS\r\n");
    printf("\t(i.e. LS is wake every 10s for 5 times, HS is wake from LS after 10s * 5 = 50s\r\n");
    printf("PS=standby,gpio=2,gpio_wake=5\r\n");
    printf("\tstandby and configure GPIOA_2 as wakeup source, and wake HS after GPIOA_2 is trigger for 5 times\r\n");
    printf("\t(i.e. LS is wake when GPIOA_2 is triggered, HS is wake when GPIOA_2 is triggered for 5 times\r\n");
    printf("PS=standby,wowlan,stimer=10,gpio=2\r\n");
    printf("\tconfigure stimer and gpio as wakeup source, and these setting only works in wake on wlan mode\r\n");
    
    printf("PS=standby,gpio13_setting=1,gpio_setting=0x155562,gpio=13\r\n");
    printf("\tconfigure gpio as wakeup source, and do gpio pull ctrl\r\n");

    printf("\r\n");
    printf("PS=wowlan\r\n");
    printf("\tInit wlan and connect to AP with hardcode ssid & pw, and then enter wake on wlan mode\r\n");
    printf("PS=wowlan,your_ssid\r\n");
    printf("\tInit wlan and connect to AP with \"your_ssid\" in open mode, and then enter wake on wlan mode\r\n");
    printf("PS=wowlan,your_ssid,your_pw\r\n");
    printf("\tInit wlan and connect to AP with \"your_ssid\" and \"your_pw\" in WPA2 AES mode, and then enter wake on wlan mode\r\n");

    printf("\r\n");
    printf("PS=ls_wake_reason\r\n");
    printf("\tGet LS wake reason\r\n");

    printf("\r\n");
    printf("PS=tcp_keep_alive\r\n");
    printf("\tEnable TCP KEEP ALIVE with hardcode server IP & PORT. This setting only works in wake on wlan mode\r\n");
    printf("PS=tcp_keep_alive,192.168.1.100,5566\r\n");
    printf("\tEnable TCP KEEP ALIVE with server IP 192.168.1.100 and port 5566. This setting only works in wake on wlan mode\r\n");

    printf("\r\n");
    printf("PS=wowlan_pattern\r\n");
    printf("\tEnable user defined wake up pattern. This settting only works in wake on wlan mode\r\n");
#endif
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

int keepalive_offload_test(void)
{
	int socket_fd;
    int ret = 0;

	if((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		printf("ERROR: socket\n");
	}
	else {
		struct sockaddr_in server_addr;
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = inet_addr(server_ip);	// IP of a TCP server
		server_addr.sin_port = htons(server_port);

		if(connect(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) == 0) {
            printf("\r\nconnected to %s:%d\r\n", server_ip, server_port);
			uint8_t data[] = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a};
//TCP Keep alive test			
#if 0
			for(int i=0; i<5; i++)
			{  
				send(socket_fd, data, 10, 0);
				vTaskDelay(2000);
			}
#endif			
			wifi_set_tcp_keep_alive_offload(socket_fd, data, sizeof(data), interval_ms, resend_ms, 1);
			//should not send any IP packet after set_keep_send()
		}
		else {
			printf("ERROR: connect %s:%d\r\n", server_ip, server_port);
            ret = -1;
		}
	}
    return ret;
}

void set_icmp_ping_pattern(wowlan_pattern_t *pattern)
{
	memset(pattern, 0, sizeof(wowlan_pattern_t));

    char buf[32], mac[6];
    const char ip_protocol[2] = {0x08, 0x00}; // IP {08,00} ARP {08,06}
    const char ip_ver[1] = {0x45};
    const uint8_t icmp_protocol[1] = {0x01};
    const uint8_t *ip = LwIP_GetIP(&xnetif[0]);
    const uint8_t unicast_mask[6] = {0x3f, 0x70, 0x80, 0xc0, 0x03, 0x00};

    wifi_get_mac_address(buf);
    sscanf(buf, "%02x:%02x:%02x:%02x:%02x:%02x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
    memcpy(pattern->eth_da, mac, 6);
    memcpy(pattern->eth_proto_type, ip_protocol, 2);
    memcpy(pattern->header_len, ip_ver, 1);
    memcpy(pattern->ip_proto, icmp_protocol, 1);
    memcpy(pattern->ip_da, ip, 4);
    memcpy(pattern->mask, unicast_mask, 6);
}

void set_tcp_not_connected_pattern(wowlan_pattern_t *pattern)
{
    // This pattern make STA can be wake from TCP SYN packet
	memset(pattern, 0, sizeof(wowlan_pattern_t));

    char buf[32];
	char mac[6];
	char ip_protocol[2] = {0x08, 0x00}; // IP {08,00} ARP {08,06}
	char ip_ver[1] = {0x45};
	char tcp_protocol[1] = {0x06}; // 0x06 for tcp
    char tcp_port[2] = {0x00, 0x50}; // port 80
	uint8_t * ip = LwIP_GetIP(&xnetif[0]);
	const uint8_t uc_mask[6] = {0x3f, 0x70, 0x80, 0xc0, 0x33, 0x00};

	wifi_get_mac_address(buf);
	sscanf(buf, "%02x:%02x:%02x:%02x:%02x:%02x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
	memcpy(pattern->eth_da, mac, 6);
	memcpy(pattern->eth_proto_type, ip_protocol, 2);
	memcpy(pattern->header_len, ip_ver, 1);
	memcpy(pattern->ip_proto, tcp_protocol, 1);
	memcpy(pattern->ip_da, ip, 4);
    memcpy(pattern->dest_port, tcp_port, 2);
	memcpy(pattern->mask, uc_mask, 6);
}

void set_tcp_connected_pattern(wowlan_pattern_t *pattern)
{
    // This pattern make STA can be wake from a connected TCP socket
	memset(pattern, 0, sizeof(wowlan_pattern_t));

    char buf[32];
	char mac[6];
	char ip_protocol[2] = {0x08, 0x00}; // IP {08,00} ARP {08,06}
	char ip_ver[1] = {0x45};
	char tcp_protocol[1] = {0x06}; // 0x06 for tcp
    char tcp_port[2] = {(server_port >> 8) & 0xFF, server_port & 0xFF};
    char flag2[1] = {0x18}; // PSH + ACK
	uint8_t * ip = LwIP_GetIP(&xnetif[0]);
	const uint8_t data_mask[6] = {0x3f, 0x70, 0x80, 0xc0, 0x0F, 0x80};

	wifi_get_mac_address(buf);
	sscanf(buf, "%02x:%02x:%02x:%02x:%02x:%02x", &mac[0], &mac[1], &mac[2], &mac[3], &mac[4], &mac[5]);
	memcpy(pattern->eth_da, mac, 6);
	memcpy(pattern->eth_proto_type, ip_protocol, 2);
	memcpy(pattern->header_len, ip_ver, 1);
	memcpy(pattern->ip_proto, tcp_protocol, 1);
	memcpy(pattern->ip_da, ip, 4);
    memcpy(pattern->src_port, tcp_port, 2);
    memcpy(pattern->flag2, flag2, 1);
	memcpy(pattern->mask, data_mask, 6);
        
        //payload
        uint8_t data[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};
        uint8_t payload_mask[9] = {0xc0, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0};
        memcpy(pattern->payload, data, 10);
	memcpy(pattern->payload_mask, payload_mask, 9);  
}

void wowlan_thread(void *param)
{
    int ret;
    int cnt = 0;

    vTaskDelay(1000);

    while(1) {
        while (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS) {
            vTaskDelay(1000);
            if (wifi_connect( your_ssid, sec, your_pw, strlen(your_ssid), strlen(your_pw), 0, NULL ) == 0) {
                LwIP_DHCP(0, DHCP_START);
            }
        }

        vTaskDelay(2000);

        if (enable_tcp_keep_alive) {
            while (keepalive_offload_test() != 0) {
                vTaskDelay(4000);
            }
            wowlan_pattern_t data_pattern;
            set_tcp_connected_pattern(&data_pattern);
            wifi_wowlan_set_pattern(data_pattern);
        }

        if (enable_wowlan_pattern) {
            wowlan_pattern_t test_pattern;
            set_tcp_not_connected_pattern(&test_pattern);
            wifi_wowlan_set_pattern(test_pattern);
        }	

#if 0
        wowlan_pattern_t ping_pattern;
        set_icmp_ping_pattern(&ping_pattern);
        wifi_wowlan_set_pattern(ping_pattern);
#endif
	
	 wifi_set_dhcp_offload();
	 
	 //wifi_wowlan_set_arp_rsp_keep_alive(1);
	
	 while (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS) {
            vTaskDelay(1000);
        }

        if (rtl8195b_suspend(0) == 0) {
            if (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) == RTW_SUCCESS && wifi_is_connected_to_ap() == 0) {
	  
                uint16_t wakeup_event = BIT6; // default BIT6 for DSTBY_WLAN
                icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY, .cmd_b.para0 = wakeup_event };
                icc_cmd_send (cmd.cmd_w, 0, 1000 * 1000, NULL); // timeout 1s

                while(1) vTaskDelay(1000);
            }
	    else
	    {	        
	        {
		    icc_user_cmd_t cmd = { 
			    .cmd_b.cmd = ICC_CMD_REQ_STANDBY_GPIO_PIN, 
			    .cmd_b.para0 = 13 
		    };
		    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us
		}
		
		uint16_t wakeup_event = BIT2; // default BIT2 for GPIO
                icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY, .cmd_b.para0 = wakeup_event };
                icc_cmd_send (cmd.cmd_w, 0, 1000 * 1000, NULL); // timeout 1s
	      	printf("wifi not connected! DSTBY_GPIO\r\n");		
	    }
        }
	else
	{
	    printf("rtl8195b_suspend fail\r\n");
	}
    }
}

int cmd_deepsleep(int argc, char *argv[])
{
    uint16_t wakeup_event = BIT0; // default BIT0 for DS_STIMER

    if (argc > 2) {
        // user specify the wake up event and parameter
        wakeup_event = 0;
        for (int i=2; i<argc; i++) {
            if(strncmp("stimer", argv[i], sizeof("stimer")-1) == 0)
            {
                char *p = strchr(argv[i], '=');
                if (p != NULL) {
                    uint32_t stimer_duration_in_seconds = atoi(p+1);
                    icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_DEEPSLEEP_STIMER_DURATION, .cmd_b.para0 = stimer_duration_in_seconds };
                    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us
                    wakeup_event |= BIT0; // DS_STIMER
                }
            }
            if (strncmp("gpio", argv[i], sizeof("gpio")-1) == 0)
            {
                wakeup_event |= BIT1; // DS_GPIO
            }
        }
        if (wakeup_event == 0) {
            return -1;
        }
    }

    icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_DEEPSLEEP, .cmd_b.para0 = wakeup_event };
    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us

    return 0;
}

int cmd_standby(int argc, char *argv[])
{
    uint16_t wakeup_event = BIT0;
    int for_wowlan = 0;
    int gpioa_setting = 0;

    if (argc > 2) {
        // user specify the wake up event and parameter
        wakeup_event = 0;
        for (int i=2; i<argc; i++) {
            if(strncmp("stimer", argv[i], sizeof("stimer")-1) == 0)
            {
                char *p = strchr(argv[i], '=');
                if (p != NULL && ((p - argv[i]) == sizeof("stimer") - 1)) {
                    uint32_t stimer_duration_in_seconds = atoi(p+1);
                    icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY_STIMER_DURATION, .cmd_b.para0 = stimer_duration_in_seconds };
                    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us
                    wakeup_event |= BIT0;
                }
            }
            if (strncmp("stimer_wake", argv[i], sizeof("stimer_wake")-1) == 0)
            {
                char *p = strchr(argv[i], '=');
                if (p != NULL) {
                    uint32_t stimer_wake = atoi(p+1);
                    icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY_STIMER_WAKE, .cmd_b.para0 = stimer_wake };
                    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us
                }                
            }
            if (strncmp("gpio13_setting", argv[i], sizeof("gpio13_setting")-1) == 0)
            {
                char *p = strchr(argv[i], '=');
                if (p != NULL && ((p - argv[i]) == sizeof("gpio13_setting") - 1)) {
                    uint32_t gpio13_setting = atoi(p+1);
                    icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY_GPIO13_SET, .cmd_b.para0 = gpio13_setting };
                    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us
		    gpioa_setting = 1;
                }
            }
            if (strncmp("gpio_setting", argv[i], sizeof("gpio_setting")-1) == 0)
            {
                char *p = strchr(argv[i], '=');
                if (p != NULL && ((p - argv[i]) == sizeof("gpio_setting") - 1)) {
                    uint32_t gpio_setting = atoi(p+1);
                    icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY_GPIO_SET, .cmd_b.para0 = gpio_setting };
                    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us
		    gpioa_setting = 1;
                }
            }
            if (strncmp("gpio", argv[i], sizeof("gpio")-1) == 0)
            {
                char *p = strchr(argv[i], '=');
                if (p != NULL && ((p - argv[i]) == sizeof("gpio") - 1)) {
                    uint32_t gpio_A_index = atoi(p+1);
                    icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY_GPIO_PIN, .cmd_b.para0 = gpio_A_index };
                    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us
                    wakeup_event |= BIT2; // DSTBY_GPIO
                }
            }
            if (strncmp("gpio_wake", argv[i], sizeof("gpio_wake")-1) == 0)
            {
                char *p = strchr(argv[i], '=');
                if (p != NULL) {
                    uint32_t gpio_wake = atoi(p+1);
                    icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY_GPIO_WAKE, .cmd_b.para0 = gpio_wake };
                    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us
                }                
            }
            if (strncmp("wowlan", argv[i], sizeof("wowlan")-1) == 0)
            {
                // We just want to send standby parameters to LS. Do not invoke standby now.
                for_wowlan = 1;
            }
        }
        if (for_wowlan) {
            return 0;
        }
        if (wakeup_event == 0) {
            return -1;
        }
    }

    // NOTICE: if we do not configre wlan as wake up source, then we MUST turn if off before standby.
    wifi_off();
    
    if(wakeup_event == 0 && gpioa_setting)
    {
       wakeup_event = BIT0;
       icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY_STIMER_DURATION, .cmd_b.para0 = 60*60 };
       icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us
    }

    icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY, .cmd_b.para0 = wakeup_event }; // BIT0 for DSTBY_STIMER
    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us

    return 0;
}

void fPS(void *arg){
	int argc;
	char *argv[MAX_ARGC] = {0};

    argc = parse_param(arg, argv);

    do {
        if (argc == 1) {
            print_PS_help();
            break;
        }

        if (strcmp(argv[1], "deepsleep") == 0)
        {
            if (cmd_deepsleep(argc, argv) != 0) {
                print_PS_help();
                break;
            }
        }
        else if (strcmp(argv[1], "standby") == 0)
        {
            if (cmd_standby(argc, argv) != 0) {
                print_PS_help();
                break;
            }
        }
        else if (strcmp(argv[1], "ls_wake_reason") == 0)
        {
            icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_GET_LS_WAKE_REASON, .cmd_b.para0 = 0 };
            icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us

            hal_delay_us(1000);
            // update ls wake reason in icc_req_get_ls_wake_reason_handler
        }
        else if (strcmp(argv[1], "sleeppg") == 0)
        {
            if (argc == 2) {
                wifi_off();
                SleepPG(SLP_GTIMER, 20 * 1000 * 1000, 1, 0);
            }
        }
        else if (strcmp(argv[1], "wowlan") == 0)
        {
            if (argc == 3) {
                sprintf(your_ssid, "%s", argv[2]);
                memset(your_pw, 0, sizeof(your_pw));
                sec = RTW_SECURITY_OPEN;
            } else if (argc == 4) {
                sprintf(your_ssid, "%s", argv[2]);
                sprintf(your_pw, "%s", argv[3]);
                sec = RTW_SECURITY_WPA2_AES_PSK;
            }

            if (wowlan_thread_handle == NULL && xTaskCreate(wowlan_thread, ((const char*)"wowlan_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, &wowlan_thread_handle) != pdPASS) {
                printf("\r\n wowlan_thread: Create Task Error\n");
            }
        }
        else if (strcmp(argv[1], "tcp_keep_alive") == 0)
        {
            if (argc >= 4) {
                sprintf(server_ip, "%s", argv[2]);
                server_port = strtoul(argv[3], NULL, 10);
            }
            enable_tcp_keep_alive = 1;
            printf("setup tcp keep alive to %s:%d\r\n", server_ip, server_port);
        }
        else if (strcmp(argv[1], "wowlan_pattern") == 0)
        {
            enable_wowlan_pattern = 1;
            printf("setup wowlan pattern\r\n");
        }
        else
        {
            print_PS_help();
        }
    } while (0);
}

#if LONG_RUN_TEST
extern char log_buf[LOG_SERVICE_BUFLEN];
extern xSemaphoreHandle log_rx_interrupt_sema;
static void long_run_test_thread(void *param) {

    vTaskDelay(1000);
    sprintf(log_buf, "PS=ls_wake_reason");
    xSemaphoreGive(log_rx_interrupt_sema);

    vTaskDelay(1000);
    sprintf(log_buf, "PS=wowlan,%s,%s", your_ssid, your_pw);
    xSemaphoreGive(log_rx_interrupt_sema);

    while(1) vTaskDelay(1000);
}
#endif


log_item_t at_power_save_items[ ] = {
      {"PS", fPS,},
};

void ps_example_init(void)
{
    icc_init ();

    icc_cmd_register(ICC_CMD_NOTIFY_LS_WAKE_REASON, (icc_user_cmd_callback_t)icc_req_get_ls_wake_reason_handler, ICC_CMD_NOTIFY_LS_WAKE_REASON);
}

void main(void)
{

	/* Must have, please do not remove */
    uint8_t wowlan_wake_reason = rtl8195b_wowlan_wake_reason();
    if (wowlan_wake_reason != 0) {
        printf("\r\nwake fom wlan: 0x%02X\r\n", wowlan_wake_reason);
    }

	/* Initialize log uart and at command service */

    console_init();
    
    log_service_add_table(at_power_save_items, sizeof(at_power_save_items)/sizeof(at_power_save_items[0]));

    ps_example_init();

#if ISP_BOOT_MODE_ENABLE == 0
	/* pre-processor of application example */
	pre_example_entry();

	/* wlan intialization */
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
	wlan_network();
#endif
#endif

#if LONG_RUN_TEST
    if(xTaskCreate(long_run_test_thread, ((const char*)"long_run_test_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        printf("\r\n long_run_test_thread: Create Task Error\n");
    }
#endif

	/* Execute application example */
	example_entry();
    
   	/*Enable Schedule, Start Kernel*/
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
	#ifdef PLATFORM_FREERTOS
	vTaskStartScheduler();
	#endif
#else
	RtlConsolTaskRom(NULL);
#endif
}
