#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include <example_entry.h>
#include "platform_autoconf.h"

#include <osdep_service.h>
#include <wifi_conf.h>
#include <lwip_netconf.h>
#include "gpio_api.h" 
#include "gpio_irq_api.h" 
#include <lwip/sockets.h>
#include <flash_api.h>
#include <device_lock.h>
#include "doorbell_demo.h"
#include "app_setting.h"
#include "fatfs_sdcard_api.h"
#include <time.h>
#include "hal_power_mode.h"
#include "power_mode_api.h"
#include "sys_api_ext.h"

gpio_t gpio_amp;
gpio_irq_t gpio_btn;
gpio_t gpio_led_red;
gpio_t gpio_led_blue;


extern int sd_ready;
extern char firebase_topic_name[64];
static flash_t flash;
static char sd_filename[32];
static fatfs_sd_params_t fatfs_sd;
extern int rtsTimezone;

extern _sema firebase_message_sema;
extern doorbell_ctr_t doorbell_handle;
extern void icc_task_func(void);
extern void start_firebase_message(void);
extern void mp4_record_stop(void);
extern void send_icc_cmd_poweroff(void);
extern struct tm sntp_gen_system_time(int timezone);
extern _sema firebase_message_sema;
extern void start_doorbell_ring(void);
extern int isp_suspend_func(void *parm);
extern void example_qr_code_scanner_modified(void);
extern int check_doorbell_mmf_status(void);  

struct firebase_topic {
	uint32_t topic_name_len;
	uint8_t  topic_name[64];
};

void amp_gpio_enable(int enable)
{
	gpio_write(&gpio_amp, enable);
}

void led_blue_enable(int enable)
{
        gpio_write(&gpio_led_blue, enable);
}

void led_red_enable(int enable)
{
       gpio_write(&gpio_led_red, enable); 
}

void firebase_topic_thread(void *param)
{
	struct sockaddr_in server_addr;   
	int server_fd = -1;
	struct firebase_topic topic;
	while(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS){
		vTaskDelay(100);
	}

	memset(&topic, 0, sizeof(struct firebase_topic));
        
        device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_stream_read(&flash, FIREBASE_FLASH_ADDR, sizeof(struct firebase_topic), (uint8_t *) &topic);
        device_mutex_unlock(RT_DEV_LOCK_FLASH); 

	if((topic.topic_name_len > 0) && (topic.topic_name_len < sizeof(topic.topic_name))) {
		topic.topic_name[topic.topic_name_len] = 0;
		printf("\r\ntopic name in flash: %s\r\n", topic.topic_name);
		strcpy(firebase_topic_name, topic.topic_name);
	}
	else {
		printf("\r\nno topic name in flash\r\n");
		strcpy(firebase_topic_name, "");
	}

	if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) >= 0) {
		server_addr.sin_family = AF_INET;
		server_addr.sin_port = htons(SERVER_PORT);
		server_addr.sin_addr.s_addr = INADDR_ANY;

		if(bind(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0) {
			printf("bind error\n");
			goto exit;
		}

		if(listen(server_fd, 3) != 0) {
			printf("listen error\n");
			goto exit;
		}

		while(1) {
			struct sockaddr_in client_addr;
			unsigned int client_addr_size = sizeof(client_addr);
			int socket_fd = accept(server_fd, (struct sockaddr *) &client_addr, &client_addr_size);

			if(socket_fd >= 0) {
				char buf[100];
				int read_size = 0;

				if(strlen(firebase_topic_name)) {
					printf("\r\nfirebase topic name: %s\r\n", firebase_topic_name);
					sprintf(buf, "false:%s:;", firebase_topic_name);
					write(socket_fd, buf, strlen(buf));
				}
				else {
					printf("\r\nno firebase topic name\r\n");
					write(socket_fd, "true:;", strlen("true:;"));
				}

				while((read_size = read(socket_fd, buf, sizeof(buf))) > 0) {
					char *end_str = NULL;
	
					buf[read_size] = 0;
					printf("\r\nread: %s\r\n", buf);

					if((end_str = strstr(buf, ":;")) != NULL) {
						if(strstr(buf, "0:") == buf) {
							*end_str = 0;

							if((strlen(&buf[2]) > 0) && (strlen(&buf[2]) < sizeof(topic.topic_name))) {
								memset(&topic, 0, sizeof(struct firebase_topic));
								strcpy(topic.topic_name, &buf[2]);
								topic.topic_name_len = strlen(&buf[2]);
                                                                
                                                                device_mutex_lock(RT_DEV_LOCK_FLASH);
                                                                flash_erase_sector(&flash, FIREBASE_FLASH_ADDR);
                                                                flash_stream_write(&flash, FIREBASE_FLASH_ADDR, sizeof(struct firebase_topic), (uint8_t *) &topic);
                                                                device_mutex_unlock(RT_DEV_LOCK_FLASH);
                                                                

								printf("\r\nupdate topic name in flash: %s\r\n", topic.topic_name);
								strcpy(firebase_topic_name, topic.topic_name);
							}
							else {
								break;
							}
						}
						else if(strstr(buf, "1:") == buf) {
                                                        device_mutex_lock(RT_DEV_LOCK_FLASH);
                                                        flash_erase_sector(&flash, FIREBASE_FLASH_ADDR);
                                                        device_mutex_unlock(RT_DEV_LOCK_FLASH);

							printf("\r\nclear topic name in flash\r\n");
							strcpy(firebase_topic_name, "");
						}
						else {
							break;
						}
					}
					else {
						break;
					}
				}

				close(socket_fd);
			}
		}
	}
	else {
		printf("socket error\n");
		goto exit;
	}

exit:
	if(server_fd >= 0)
		close(server_fd);

	/* Kill init thread after all init tasks done */
	vTaskDelete(NULL);
}

void start_firebase_topic(void)
{
	  if(xTaskCreate(firebase_topic_thread, ((const char*)"firebase_topic_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(firebase_topic_thread) failed", __FUNCTION__);
}

void thread_isp_flip(void *parm)  
{
	  while(1){  
		if (isp_stream_get_status(0) != 0) {
#if ISP_FLIP_ENABLE
                        isp_set_flip(FILP_NUM);
			printf("set flip\r\n");
#endif
			break;
		}
		vTaskDelay(500);
	  }
	  vTaskDelete(NULL);
}

void isp_flip_thread(void)
{
	  if(xTaskCreate(thread_isp_flip, ((const char*)"thread_isp_flip"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
			printf("\n\r%s xTaskCreate(thread_isp_flip) failed", __FUNCTION__);
}

void thread_doorbell_status_monitor(void *parm)
{
	static int wifi_wait_count = 0;
	static int wifi_flag = 0;
	int i = 0;
	int led_value = 0;
  

#if ISP_BOOT_MODE_ENABLE	
	while(check_doorbell_mmf_status()==0)
	{
		vTaskDelay(1);
	}
  	pre_example_entry();
	
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
	wlan_network();
#endif
#endif 
   
	//LED control
	while(1){
	    //QR code Scan
	    if(qrcode_scanner_running()){
	      while(qrcode_scanner_running()) {
		      led_red_enable(0);
		      vTaskDelay(200);
		      led_red_enable(1);
		      vTaskDelay(200);
	      }
	    }
	    
	    //wifi not connected	    
	    if(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS){
	      doorbell_handle.doorbell_state &= ~ STATE_WIFI_CONNECTED;
	      led_red_enable(led_value);
	      led_blue_enable(~led_value);
	      led_value = ~led_value;
	      wifi_flag = 0;
	    }else{
		  if(wifi_flag == 0)
		  {  
		      doorbell_handle.doorbell_state |= STATE_WIFI_CONNECTED;
		      led_red_enable(0);
		      led_blue_enable(0);
		      wifi_flag = 1;
		      printf("wifi connected\r\n");
		  }
	    }
	    
	    //
	    vTaskDelay(100);
	}
}

void doorbell_status_monitor()
{
          if(xTaskCreate(thread_doorbell_status_monitor, ((const char*)"thread_wifi_monitor"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
                        printf("\n\r%s xTaskCreate(thread_wifi_monitor) failed", __FUNCTION__);
}

void check_doorbell_status()
{
  extern int check_doorbell_mmf_status();
  while(1){
    if(check_doorbell_mmf_status())
      break;
    vTaskDelay(10);
  }
}

_sema doorbell_handle_sema;
extern struct netif xnetif[NET_IF_NUM];

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

void media_contol_thread(void *param)
{		
	int timeoutstatus = 0;
	int qrtime = 0;
	int playbacktime = 0;   
  	// 1V1A RTSP MP4
	// ISP   -> H264 -> RTSP and mp4
	// AUDIO -> AAC  -> RTSP and mp4
	//mmf2_example_av_rtsp_mp4_init();
	
	// H264 and 2way audio (G711, PCMU)
	// ISP   -> H264 -> RTSP (V1)
	// AUDIO -> G711E  -> RTSP
	// RTP   -> G711D  -> AUDIO
	// ARRAY (PCMU) -> G711D -> AUDIO (doorbell)
		
	mmf2_h264_2way_audio_pcmu_doorbell_init();
	
#ifdef DOORBELL_TARGET_BROAD
	//flash write protect prevention
	flash_t         flash;
	u8 status = 0;
	u8 status2 = 0;
	u8 status3 = 0;
	status = flash_get_status(&flash);
	//printf("Status Register Before Setting= %x\n", flash_get_status(&flash));
	if(status != 0 ||  status2 != 0 || status3 != 0)
	{
	        printf("Status Register Before Setting= %x\n", status);
		printf("Status2 Register Before Setting= %x\n", status2);
		printf("Status3 Register Before Setting= %x\n", status3);
		flash_set_status(&flash,0);
		flash_set_status2(&flash,0);
		flash_set_status3(&flash,0);
		flash_reset_status(&flash);
	}
#endif	
        	
	// TODO: exit condition or signal
	while(1)
	{	         
	    if(rtw_down_timeout_sema(&doorbell_handle_sema,SUSPEND_TIME)==0)
	    {
	    	timeoutstatus = 1;  
	    }
	    
	    switch(doorbell_handle.new_state)
	    {
	    case STATE_ARAM:
	        printf("STATE_ARAM\r\n");
	        if(doorbell_handle.doorbell_state & STATE_RECORD || qrcode_scanner_running() || doorbell_handle.doorbell_state & STATE_NONESD){
		    //do something
		   doorbell_handle.new_state = STATE_NORMAL;
		}
		else
		{
		    doorbell_handle.new_state = STATE_NORMAL;
		    if(firebase_message_sema == NULL)
			vTaskDelay(500);
		
		    if(firebase_message_sema != NULL)
		    	rtw_up_sema(&firebase_message_sema);

		    if(sd_ready)
		    {  
			DIR m_dir;
			fatfs_sd_get_param(&fatfs_sd);
			sprintf(sd_filename, "%s%s", fatfs_sd.drv, MP4_DIR);
			if(f_opendir(&m_dir, sd_filename) == 0)
			{
				f_closedir(&m_dir);
			}
			else
			{
				f_mkdir(sd_filename);
			}
			

			struct tm tm_now = sntp_gen_system_time(rtsTimezone);
			sprintf(sd_filename, "%s/%04d%02d%02d_%02d%02d%02d", MP4_DIR, tm_now.tm_year, tm_now.tm_mon, tm_now.tm_mday, tm_now.tm_hour, tm_now.tm_min, tm_now.tm_sec);
			//sprintf(sd_filename, "%s/%s", MP4_DIR, "mp4_record");			
			mp4_record_start(sd_filename);

			doorbell_handle.doorbell_state |= STATE_RECORD;
		    }
		    else
		    {
		        doorbell_handle.doorbell_state |= STATE_NONESD;
		    }
		}
	      break;
	    case STATE_QRCODE:
	      	printf("STATE_QRCODE\r\n");
	      	doorbell_handle.new_state = STATE_NORMAL;  
		example_qr_code_scanner_modified();
	      break;
	    case STATE_RING:
	       printf("STATE_RING\r\n");
	      	doorbell_handle.new_state = STATE_NORMAL;
          	if(firebase_message_sema == NULL)
		    vTaskDelay(500);
		
		if(firebase_message_sema != NULL)
		    rtw_up_sema(&firebase_message_sema);		

		check_doorbell_status(); 

		printf("play doorbell\r\n");
		start_doorbell_ring();
         
	      break;
	    case STATE_PLAYPACK:
	         printf("STATE_PLAYPACK\r\n");
	         doorbell_handle.new_state = STATE_NORMAL;
		 doorbell_handle.doorbell_state |= STATE_PLAYPACK;
		 playbacktime = 0;
	      break;
	    case STATE_NORMAL:
	      printf("STATE_NORMAL\r\n");
	      if(qrcode_scanner_running() && timeoutstatus){
	         qrtime++;
		 timeoutstatus = 0;
		 if(qrtime >= 3){
		 	qrcode_scanner_stop();
			qrtime = 0;
		 }		   
	      }	
	      else if((doorbell_handle.doorbell_state & STATE_PLAYPACK) && timeoutstatus){
		  playbacktime++;
		  timeoutstatus = 0;
		  if(playbacktime >= 3){
		  	doorbell_handle.doorbell_state &= ~STATE_PLAYPACK;
		  	playbacktime = 0;
		  }	
	      }
	      else if(timeoutstatus)
	      {	
		if(doorbell_handle.doorbell_state & STATE_RECORD){
		    mp4_record_stop();
		    vTaskDelay(1000); 
		    doorbell_handle.doorbell_state &= ~STATE_RECORD;
		}
#if DOORBELL_AMP_ENABLE		
		amp_gpio_enable(0);
#endif		
		led_blue_enable(0);
		led_red_enable(0);
		printf("Timeout!!\r\n"); 

#if USE_WOWLAN
		isp_suspend_func(NULL);
	        vTaskDelay(1000);	
#if 1
		wowlan_pattern_t ping_pattern;
		set_icmp_ping_pattern(&ping_pattern);
		wifi_wowlan_set_pattern(ping_pattern);
#endif
		 
		if (rtl8195b_suspend(0) == 0) {
		    if (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) == RTW_SUCCESS && wifi_is_connected_to_ap() == 0) {		
			    send_icc_cmd_poweroff();
		    }
		}		
#else
		if(rltk_wlan_running(0)) 
		      wifi_off();
		
		isp_suspend_func(NULL);
		vTaskDelay(1000);
		send_icc_cmd_poweroff(); 
#endif	
		while(1) vTaskDelay(1000);
		//SleepPG(SLP_GTIMER, 20 * 1000 * 1000, 1, 0);
		//SleepPG(SLP_GPIO, 20 * 1000 * 1000, 1, 10);
	      }
	      break;
	    }
	}
	
	//stop_all_streaming();	
	//close_all_context();
	//vTaskDelete(NULL);
}

void media_control_init()
{
        if(xTaskCreate(media_contol_thread, ((const char*)"mmf_ctr"), 512, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\r\n media_contol_thread: Create Task Error\n");
	}
}

void doorbell_init_function(void *parm)
{
        /* IO initial      */
  	//AMP init
        gpio_init(&gpio_amp, AMP_PIN);    
	gpio_dir(&gpio_amp, PIN_OUTPUT);
	gpio_mode(&gpio_amp, PullNone);
	gpio_write(&gpio_amp, 0);	 
        //LED inital
	gpio_init(&gpio_led_red, BTN_RED); //BUTTON RED
	gpio_dir(&gpio_led_red, PIN_OUTPUT);
	gpio_mode(&gpio_led_red, PullNone);
	gpio_write(&gpio_led_red, 0);

	gpio_init(&gpio_led_blue, BTN_BLUE);//BUTTON BLUE
	gpio_dir(&gpio_led_blue, PIN_OUTPUT);
	gpio_mode(&gpio_led_blue, PullNone);
	gpio_write(&gpio_led_blue, 1);
	
	//video flip
	isp_flip_thread();		
	rtw_init_sema(&doorbell_handle_sema, 0);
	
	//icc handler initial
        icc_task_func(); 
	//start mmf application
	media_control_init(); 
	
	//doorbell moniter
	doorbell_status_monitor();
	
	//firebase start
	start_firebase_message();	
	start_firebase_topic();    
	
#if CONFIG_MEDIA_AMEBACAM_APP_BROADCAST	
	//start doorbell broadcast
	media_doorbell_broadcast();
#endif	
	
#ifdef DOORBELL_TARGET_BROAD
	amp_gpio_enable(1);
#endif	
}