#include <platform_opts.h>
#include "FreeRTOS.h"
#include "task.h"
#include "lwip/netdb.h"
#include <platform/platform_stdlib.h>
#include <lwip_netconf.h>
#include <osdep_service.h>
#include "app_setting.h"
#include <wifi_conf.h>
#include "doorbell_demo.h"
#include <flash_api.h>
#include <device_lock.h>

#define USE_HTTPS    1
#if USE_HTTPS
#include <httpc/httpc.h>
#endif

extern doorbell_ctr_t doorbell_handle;
extern struct netif xnetif[];

#define THREAD_STACK_SIZE 4096
#if USE_HTTPS
#define HOST_NAME "fcm.googleapis.com"
#define HOST_PORT 443
#else
#define HOST_NAME "fcm.googleapis.com"
#define HOST_PORT 80
#endif

//#define SERVER_KEY  "AAAAKf39G0Y:APA91bG8aqSbYCcd1YsshtJn4-Y1jgig1meP1VfVc59kFL86TN8Ix_83my8qY1XHER4AU-I9eB7rdJpvjjXDPZuwDHC3kOCyD_uX8lf7IRjgPCIe1GxbjbpTMjRl6tAsCkqaM1M0V4L1"
//#define ACCESS_TOKEN "eEY32tC2GUQ:APA91bFKvquSvYQ9Jhlfvr3TQO2_V5oAGUUqHdyywHdKeHBYVF5ZrUh3GDOJ6HN81gx23Dfto6ZmZVfg5nJ1Rofsitsg2f-s3dpPbZe562wt2iBVqAvKUi-wdoZeqt8GdiBFX-qLFX2E"
//#define SERVER_KEY "AAAArZzHFDA:APA91bFNbx1_DR3Ep6xULX1AtKBKNFmUr4Ah936dvzgSNeFwWw41vLbBWHypFghuGKtLEZbK9QamFxHc0VEXEpltj9kH2LSMU07GWiD-QyySF2pJ2CZMktBPnDZPDzO6qWgv0FaCW87s"
//#define SERVER_KEY "AAAAC5YzWE4:APA91bGHq6kuxZhL3uysXymX-wGeyt1KuXP3XV0VTlNlfiXu2b2NLViaWfVZ4f12wns0sVqxVmxxN0EY4dsIqSmHPayhOR18SU_69w517L80ipkNHDx9P9iSln13T4cZN6yQuNjXip7Iv-7pcXbcNHgn4yE6xpgNQw"
//#define SERVER_KEY "AIzaSyD5TD9zUiRYWsJeAwkSgyPD2TGTaJVW3NE"
#define SERVER_KEY "AIzaSyD5TD9zUiRYWsJeAwkSgyPD2TGTaJVW3NE"
//#define SERVER_KEY "AIzaSyCOrerfsoOd0WICKpt88YpEftRGGR2pfuw"

//#define SERVER_KEY "AIzaSyA03N7Y4iaZ4gTHXvoJbZQimNv7I0MRCoE"
// IS_LOCAL : 1:local   2:internet   3:local+internet
char const* payload_fmt = "{" \
	" \"to\": \"/topics/%s\"," \
/*	"\"to\": \"" ACCESS_TOKEN "\"," \ */
	"\"priority\" : \"high\"," \
    "\"data\": {" \
    "\"MAC\": \"%02X:%02X:%02X:%02X:%02X:%02X\"," \
    "\"IS_LOCAL\": \"3\"," \
    "\"LOCAL_IP\": \"%d.%d.%d.%d\"," \
    "\"LOCAL_PORT\": \"554\"," \
    "\"RELAY_IP\": \"52.198.104.214\"," \
    "\"RELAY_PORT\": \"5000\"," \
    "\"NAME\": \"Doorbell_%02X%02X%02X\" " \
    "} }\n" ;

char firebase_topic_name[64] = {0};

struct firebase_topic {
	uint32_t topic_name_len;
	uint8_t  topic_name[64];
};

static flash_t flash;

static void send_firebase_message(void)
{
	int port = HOST_PORT;
	char *host = HOST_NAME;
	struct hostent *server;
	struct sockaddr_in serv_addr;
	int sockfd = -1, bytes;
	char message_buf[1024];
	//char content_buf[1024];
	struct firebase_topic topic;
	
	if(strlen(firebase_topic_name) == 0)
	{
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
	}

	if(strlen(firebase_topic_name) == 0) {
		printf("\n\rIGNORE: no firebase topic\n\r");
		return;
	}
	
#if USE_HTTPS
	struct httpc_conn *conn = NULL;
	printf("httpc_conn_new\r\n");
	conn = httpc_conn_new(HTTPC_SECURE_TLS, NULL, NULL, NULL);
	if(conn)
	{
	        printf("httpc_conn_connect\r\n");
		if(httpc_conn_connect(conn, HOST_NAME, 443, 0) == 0) {
		        /* HTTP POST request */
			//char *post_data = "param1=test_data1&param2=test_data2";
		        u8 *mac = LwIP_GetMAC(&xnetif[0]);
			u8 *ip = LwIP_GetIP(&xnetif[0]);
			memset(message_buf, 0, sizeof(message_buf));
			int content_len = sprintf(message_buf, payload_fmt,
				firebase_topic_name,
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
				ip[0], ip[1], ip[2], ip[3],
				mac[3], mac[4], mac[5]);
			
			content_len = strlen(message_buf)-1;// It is not included the /n at the ned, so we don't need to add it
			
			printf("content_len = %d\r\n",content_len);
			
			//sprintf(content_buf,"application/json\nAuthorization: key=%s\n",SERVER_KEY);
#if 0
			sprintf(message_buf,"POST /fcm/send HTTP/1.1\nContent-Type: application/json\nAuthorization: key=%s\nHost: %s\nContent-Length: %d\n\n",
				SERVER_KEY, HOST_NAME, content_len);
			sprintf(message_buf + strlen(message_buf), payload_fmt,
				firebase_topic_name,
				mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
				ip[0], ip[1], ip[2], ip[3],
				mac[3], mac[4], mac[5],"\n");
#endif
			printf("\r\nRequest:\r\n%s \r\n", message_buf);
			// start a header and add Host (added automatically), Content-Type and Content-Length (added by input param)
			//httpc_conn_setup_user_password(conn, "key", "AIzaSyD5TD9zUiRYWsJeAwkSgyPD2TGTaJVW3NE");
			httpc_request_write_header_start(conn, "POST", "/fcm/send", "application/json", content_len);
			
			// add other header fields if necessary
			httpc_request_write_header(conn, "Authorization", "key=AIzaSyD5TD9zUiRYWsJeAwkSgyPD2TGTaJVW3NE");
			httpc_request_write_header(conn, "Connection", "close");
			// finish and send header
			httpc_request_write_header_finish(conn);
			// send http body
			httpc_request_write_data(conn, (uint8_t*)message_buf, content_len);

			// receive response header
			if(httpc_response_read_header(conn) == 0) {
				httpc_conn_dump_header(conn);

				// receive response body
				if(httpc_response_is_status(conn, "200 OK")) {
					uint8_t buf[2048];
					int read_size = 0, total_size = 0;

					while(1) {
						memset(buf, 0, sizeof(buf));
						read_size = httpc_response_read_data(conn, buf, sizeof(buf) - 1);

						if(read_size > 0) {
							total_size += read_size;
							printf("%s", buf);
						}
						else {
							break;
						}

						if(conn->response.content_len && (total_size >= conn->response.content_len))
							break;
					}
				}
			}
		}
		else {
			printf("\nERROR: httpc_conn_connect\n");
		}

		httpc_conn_close(conn);
		httpc_conn_free(conn);
	}
#else
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0) {
		printf("[ERROR] Create socket failed\n");
		goto exit;
	}

	server = gethostbyname(host);
	if(server == NULL) {
		printf("[ERROR] Get host ip failed\n");
		goto exit;
	}

	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(port);
	memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

	if(connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
		printf("[ERROR] connect failed\n");
		goto exit;
	}

	u8 *mac = LwIP_GetMAC(&xnetif[0]);
	u8 *ip = LwIP_GetIP(&xnetif[0]);
        memset(message_buf, 0, sizeof(message_buf));
	int content_len = sprintf(message_buf, payload_fmt,
		firebase_topic_name,
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
		ip[0], ip[1], ip[2], ip[3],
		mac[3], mac[4], mac[5]);
        
        content_len = strlen(message_buf)-1;// It is not included the /n at the ned, so we don't need to add it
        
        printf("content_len = %d\r\n",content_len);

	sprintf(message_buf,"POST /fcm/send HTTP/1.1\nContent-Type: application/json\nAuthorization: key=%s\nHost: %s\nContent-Length: %d\n\n",
		SERVER_KEY, HOST_NAME, content_len);
	sprintf(message_buf + strlen(message_buf), payload_fmt,
		firebase_topic_name,
		mac[0], mac[1], mac[2], mac[3], mac[4], mac[5],
		ip[0], ip[1], ip[2], ip[3],
		mac[3], mac[4], mac[5],"\n");

	printf("\r\nRequest:\r\n%s \r\n", message_buf);
        
	bytes = write(sockfd, message_buf, strlen(message_buf));
	if(bytes < 0) {
		printf("[ERROR] send packet failed\n");
		goto exit;
	}

	//receive response
	printf("\r\nResponse:\r\n");
	while(1) {
		memset(message_buf, 0, sizeof(message_buf));
		bytes = read(sockfd, message_buf, sizeof(message_buf) - 1);
		if(bytes < 0) {
			printf("[ERROR] receive packet failed\n");
			break;
		}
        if(bytes == 0)
			break;
		if(bytes > 0){
        	printf("%s", message_buf);
                break;
                }
    }

exit:
    if(sockfd != -1) {
		close(sockfd);
	}
#endif    
}

_sema firebase_message_sema = NULL;
static void firebase_message_thread(void *param)
{
	rtw_init_sema(&firebase_message_sema, 0);

	while(1) {
		rtw_down_sema(&firebase_message_sema);
		while(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS){
			 vTaskDelay(100);
		}
                
		send_firebase_message();
	}

	vTaskDelete(NULL);
}

void start_firebase_message(void)
{
	if(xTaskCreate(firebase_message_thread, ((const char*)"firebase_message_thread"), THREAD_STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(firebase_message_thread) failed\n", __FUNCTION__);
	return;
}