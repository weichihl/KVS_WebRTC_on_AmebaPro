
/*
* Broadcast thread for AmebaCam app
*/

#include "FreeRTOS.h"
#include "task.h"
#include "rtsp/rtsp_api.h"
#include "sockets.h"
#include "lwip_netconf.h" //for LwIP_GetIP, LwIP_GetMAC
#include "hal_flash_boot.h"
#if defined(CONFIG_PLATFORM_8195A)
#include "mmf_sink.h"
#endif

extern struct netif xnetif[NET_IF_NUM];
extern u8 AmebaCam_device_name[256];

static void (*packet_callback)(uint8_t *packet, size_t len) = NULL;
void amebacam_broadcast_set_packet_callback(void (*callback)(uint8_t *packet, size_t len))
{
	packet_callback = callback;
}

#if defined(CONFIG_PLATFORM_8195A)
	#if ENABLE_PROXY_SEVER
		msink_context	*rtsp_sink;
	#endif
#endif


static void media_amebacam_broadcast_all(void);

static void amebacam_broadcast_thread_all(void *param)
{
	int socket = -1;
	int broadcast = 1;
	struct sockaddr_in bindAddr;
	uint16_t port = 49154;
	unsigned char packet[32];
        int broadcast_retry_count = 5;
        int i = 0;
        
	printf("example_bcast_thread\r\n");
	// Create socket
	if((socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("ERROR: socket failed\n");
		goto exit;
	}
	
	// Set broadcast socket option
	if(setsockopt(socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0){
		printf("ERROR: setsockopt failed\n");
		goto exit;
	}
	
	// Set the bind address
	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_port = htons(port);
	bindAddr.sin_addr.s_addr = INADDR_ANY;
	if(bind(socket, (struct sockaddr *) &bindAddr, sizeof(bindAddr)) < 0){
		printf("ERROR: bind failed\n");
		goto exit;
	}
	
	
	while(1) {
                int sendLen;
                struct sockaddr to;
                struct sockaddr_in *to_sin = (struct sockaddr_in*) &to;
                to_sin->sin_family = AF_INET;
                to_sin->sin_port = htons(49153);
                to_sin->sin_addr.s_addr = INADDR_BROADCAST;
                sprintf((char*)packet, "wake_up");
                for(i=0;i<broadcast_retry_count;i++){
                  if((sendLen = sendto(socket, packet, strlen(packet), 0, &to, sizeof(struct sockaddr))) < 0)
                                printf("ERROR: sendto broadcast\n");

                  vTaskDelay(2);
                }
                goto exit;
	}

exit:
	printf("broadcast example finish\n");
	close(socket);
	vTaskDelete(NULL);
        return;
}

static void amebacam_broadcast_thread(void *param)
{
#if defined(CONFIG_PLATFORM_8195A)
	#if ENABLE_PROXY_SEVER
		printf("AmebaCam wait sink\n\r");
		while (rtsp_sink==NULL) {
			vTaskDelay(1000);
		}
	#endif
#endif
	while (AmebaCam_device_name[0]=='\0') {
		vTaskDelay(2);
	}
        
        media_amebacam_broadcast_all();
	printf("\n\rAmebaCam Broadcast\r\n");
	
	int socket = -1;
	int broadcast = 1;
	struct sockaddr_in bindAddr;
	uint16_t port = 49152;//server
	uint16_t port2 = 49151;//client
	unsigned char packet[64];
	uint8_t *mac;
	static unsigned char broadcast_to_app[300];
#if defined(CONFIG_PLATFORM_8195A)
	#if ENABLE_PROXY_SEVER	
		struct rtsp_context * rtsp_ctx = rtsp_sink->drv_priv;
		u8 proxy_suffix[256];
		memset(proxy_suffix, 0, 256);
		sprintf(proxy_suffix, "%s_%d",AmebaCam_device_name,rtsp_ctx->id);
	#endif
#endif
	mac = (uint8_t*) LwIP_GetMAC(&xnetif[0]);
	
	// Create socket
	if((socket = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("ERROR: Broadcast thread of AmebaCam failed socket failed\n\r");
		goto err;
	}
	
	// Set broadcast socket option
	if(setsockopt(socket, SOL_SOCKET, SO_BROADCAST, &broadcast, sizeof(broadcast)) < 0){
		printf("ERROR: setsockopt failed\n");
		goto err;
	}
	
	// Set the bind address
	memset(&bindAddr, 0, sizeof(bindAddr));
	bindAddr.sin_family = AF_INET;
	bindAddr.sin_port = htons(port);
	bindAddr.sin_addr.s_addr = INADDR_ANY;
	if(bind(socket, (struct sockaddr *) &bindAddr, sizeof(bindAddr)) < 0){
		printf("ERROR: bind failed\n");
		goto err;
	}
	
	
	while(1) {
		// Receive broadcast
		int packetLen = 0;
		struct sockaddr from;
		struct sockaddr_in *from_sin = (struct sockaddr_in*) &from;
		u32_t fromLen = sizeof(from);
		
		if((packetLen = recvfrom(socket, packet, sizeof(packet), 0, &from, &fromLen)) >= 0) {
			uint8_t *ip = (uint8_t *) &from_sin->sin_addr.s_addr;
			uint16_t from_port = ntohs(from_sin->sin_port);
			printf("Broadcast from AmebaCam App (%d.%d.%d.%d)\n\r",ip[0], ip[1], ip[2], ip[3]);

			if(packet_callback)
				packet_callback(packet, packetLen);
		}
		
		// Send broadcast
		if(packetLen > 0) {
			int sendLen;
			struct sockaddr to;
			struct sockaddr_in *to_sin = (struct sockaddr_in*) &to;
			to_sin->sin_family = AF_INET;
			to_sin->sin_port = htons(port2);
			to_sin->sin_addr.s_addr = from_sin->sin_addr.s_addr;//INADDR_ANY;
#if defined(CONFIG_PLATFORM_8195A)
	#if ENABLE_PROXY_SEVER
			sprintf((char*)broadcast_to_app, "%02x%02x%02x%02x%02x%02x;%d;%s;", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
			rtsp_ctx->proxy_port,proxy_suffix);
	#else
			sprintf((char*)broadcast_to_app, "%02x%02x%02x%02x%02x%02x;0;%s;", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
			AmebaCam_device_name);
	#endif
#else
			extern uint8_t get_ir_led(void);
			fw_img_export_info_type_t *pfw_image_info = get_fw_img_info_tbl();
			char fw_ver[32];
			sprintf(fw_ver, "fw%dsn%d", pfw_image_info->loaded_fw_idx, (pfw_image_info->loaded_fw_idx == 1)?pfw_image_info->fw1_sn:pfw_image_info->fw2_sn);
			sprintf((char*)broadcast_to_app, "%02x%02x%02x%02x%02x%02x;0;%s;720;%s;%d;", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
			AmebaCam_device_name, fw_ver, get_ir_led());
#endif
			sendLen = sendto(socket, broadcast_to_app, strlen((const char*)broadcast_to_app), 0, &to, sizeof(struct sockaddr));
			if( sendLen < 0)
				printf("ERROR: Send Broadcast to AmebaCam App Fail\n\r");
			else
				printf("Broadcast to AmebaCam App: %s\n\r",broadcast_to_app);
				//printf("sendto - %d bytes to broadcast:%d, data: %s\n", sendLen, port2,broadcast_to_app);
		}
	}
	
err:
	printf("ERROR: Broadcast thread of AmebaCam failed\n");
	close(socket);
	
	vTaskDelete(NULL);
}

void media_amebacam_broadcast_modified(void)
{
	/*user can start their own task here*/
	if(xTaskCreate(amebacam_broadcast_thread, ((const char*)"amebacam_broadcast"), 256, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\r\n media_amebacam_broadcast: Create Task Error\n");
	}
}

static void media_amebacam_broadcast_all(void)
{
	/*user can start their own task here*/
	if(xTaskCreate(amebacam_broadcast_thread_all, ((const char*)"amebacam_broadcast_all"), 256, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\r\n media_amebacam_broadcast_all: Create Task Error\n");
	}
}
