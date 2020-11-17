#include "FreeRTOS.h"
#include "task.h"
#include "platform/platform_stdlib.h"

#include "sockets.h"
#include "wifi_conf.h" //for wifi_is_ready_to_transceive
#include "wifi_util.h" //for getting wifi mode info
#include "lwip/netif.h" //for LwIP_GetIP

#include "mmf_command.h"

extern struct netif xnetif[NET_IF_NUM];
extern uint8_t* LwIP_GetIP(struct netif *pnetif);

mcmd_t* mcmd_cmd_create(u8 bCmd, u8 bSubCommand, u8 bidx, u8 bLen, u16 wParam, u16 wAddr, u8 *data) {
	mcmd_t *cmd = malloc(sizeof(mcmd_t));
	memset(cmd,0,sizeof(mcmd_t));
	cmd->bCmd = bCmd;
	cmd->bSubCommand= bSubCommand;
	cmd->bidx= bidx;
	cmd->bLen= bLen;
	cmd->wParam= wParam;
	cmd->wAddr= wAddr;
	if(cmd->bLen != 0) {
		cmd->data= malloc(cmd->bLen);
		memcpy(cmd->data,data,cmd->bLen);
	}
	return cmd;
}

void mcmd_queue_service(void *param)
{
	mcmd_context *mcmd_ctx = (mcmd_context *) param;
	mcmd_t *cmd;
	
	while (1)
	{
		if(rtw_down_sema(&mcmd_ctx->cmd_in_sema)) {
			cmd = mcmd_out_cmd_queue(mcmd_ctx);
			// deal with cmd here...
			//if (cmd->bCmd==?)
			//	internal_cmd_handler
			if(mcmd_ctx->cb_custom)
				mcmd_ctx->cb_custom((void*) cmd);
			// free command
			if(cmd->data != NULL) {
				free(cmd->data);
				cmd->data = NULL;
			}
			free(cmd);
			cmd = NULL;
		}
	}
	//vTaskDelete(NULL);
}


void mcmd_socket_service(void *arg);

int mcmd_task_open(mcmd_context *ctx)
{
	if(xTaskCreate(mcmd_queue_service, (char const*)((const signed char*)"mcmd_queue_service"), 1024, (void *)ctx, tskIDLE_PRIORITY + 1,  &ctx->queue_task) != pdPASS) {
		MMF_CMD_ERROR("\r\n mcmd_queue_service: Create Task Error\n");
		return -1;
	}
	
	if(xTaskCreate(mcmd_socket_service, (char const*)((const signed char*)"mcmd_socket_service"), 1024, (void *)ctx, MMF_COMMAND_SERVICE_PRIORITY, &ctx->socket_task) != pdPASS) {
		MMF_CMD_ERROR("\r\n mcmd_socket_service: Create Task Error\n");
		return -1;
	}
	
	return 0;
}

mcmd_context * mcmd_context_init()
{
	mcmd_context *ctx = malloc(sizeof(mcmd_context));
	if(ctx == NULL) {
		MMF_CMD_ERROR("allocate mmf_cmd context failed\n\r");
		return NULL;
	}
	memset(ctx, 0, sizeof(struct mmf_command_context));
	INIT_LIST_HEAD(&ctx->cmd_list);
	rtw_mutex_init(&ctx->list_lock);
	rtw_init_sema(&ctx->cmd_in_sema, 0);
	
	ctx->mcmd_socket = mcmd_socket_create();
	if (!ctx->mcmd_socket) {
		MMF_CMD_ERROR("mcmd_ctx == NULL, command socket is not available\n\r");
		goto error;
	}
/*
	if(xTaskCreate(mcmd_queue_service, ((const signed char*)"mcmd_queue_service"), 1024, (void *)ctx, tskIDLE_PRIORITY + 1,  &ctx->queue_task) != pdPASS) {
		MMF_CMD_ERROR("\r\n mcmd_queue_service: Create Task Error\n");
		goto error;
	}

	//ctx->mcmd_socket->cb_command = (int (*)(void*,void*))cmd_callback;
	if(xTaskCreate(mcmd_socket_service, ((const signed char*)"mcmd_socket_service"), 1024, (void *)ctx, MMF_COMMAND_SERVICE_PRIORITY, &ctx->socket_task) != pdPASS) {
		MMF_CMD_ERROR("\r\n mcmd_socket_service: Create Task Error\n");
		goto error;
	}
*/
	return ctx;
	
error:
	if (ctx) {
		if (ctx->mcmd_socket)
			mcmd_socket_free(ctx->mcmd_socket);	
		mcmd_context_deinit(ctx);
	}
	return NULL;
}

void mcmd_context_deinit(mcmd_context *ctx)
{
	INIT_LIST_HEAD(&ctx->cmd_list);
	rtw_mutex_free(&ctx->list_lock);
	rtw_free_sema(&ctx->cmd_in_sema);
	mcmd_socket_free(ctx->mcmd_socket);
	if(ctx->queue_task && (xTaskGetCurrentTaskHandle()!=ctx->queue_task))
		vTaskDelete( ctx->queue_task );
	if(ctx->socket_task && (xTaskGetCurrentTaskHandle()!=ctx->socket_task))
		vTaskDelete( ctx->socket_task );
	free(ctx);
	ctx = NULL;
}


void mcmd_in_cmd_queue(mcmd_t *cmd, mcmd_context *ctx)
{
	rtw_mutex_get(&ctx->list_lock);
	list_add_tail(&cmd->list, &ctx->cmd_list);
	rtw_mutex_put(&ctx->list_lock);
	rtw_up_sema(&ctx->cmd_in_sema);
}

mcmd_t *mcmd_out_cmd_queue(mcmd_context *ctx)
{
	mcmd_t *cmd = NULL;
	if(!list_empty(&ctx->cmd_list))
	{ 
		rtw_mutex_get(&ctx->list_lock);
		cmd = list_first_entry(&ctx->cmd_list, mcmd_t, list);
		list_del_init(&cmd->list);
		rtw_mutex_put(&ctx->list_lock);
	}
	return cmd;
}

void mcmd_socket_free(mcmd_socket_t *mcmd_socket)
{
	if (mcmd_socket != NULL) {
		if (mcmd_socket->request != NULL) {
			free(mcmd_socket->request);
			mcmd_socket->request = NULL;
		}
		if (mcmd_socket->response!= NULL) {
			free(mcmd_socket->response);
			mcmd_socket->response = NULL;
		}		
		if (mcmd_socket->remote_ip != NULL) {
			free(mcmd_socket->remote_ip);
			mcmd_socket->remote_ip = NULL;
		}
		free(mcmd_socket);
		mcmd_socket = NULL;
	}
}

mcmd_socket_t *mcmd_socket_create()
{
    mcmd_socket_t *mcmd_socket = malloc(sizeof(mcmd_socket_t));
	if(mcmd_socket == NULL)
	{
		MMF_CMD_ERROR("allocate mcmd_socket failed\n\r");
		goto error;
	}
	memset(mcmd_socket, 0, sizeof(mcmd_socket_t));
	
	mcmd_socket->request= malloc(MMF_COMMAND_BUF_SIZE);
	if(mcmd_socket->request== NULL) {
		MMF_CMD_ERROR("allocate mcmd_socket req_buf failed\n\r");
		goto error;
	}
	
	mcmd_socket->response= malloc(MMF_COMMAND_BUF_SIZE);
	if(mcmd_socket->response== NULL) {
		MMF_CMD_ERROR("allocate mcmd_socket resp_buf failed\n\r");
		goto error;
	}	
	
	mcmd_socket->remote_ip = malloc(4);
	if(mcmd_socket->remote_ip == NULL)
	{
		MMF_CMD_ERROR("allocate mcmd_socket remote ip memory failed\n\r");
		goto error;
	}
	
	return mcmd_socket;
	
error:
	mcmd_socket_free(mcmd_socket);
	return NULL;
}

int mcmd_socket_open(mcmd_socket_t * socket, void* cmd_callback)
{
	socket->cb_command = (int (*)(void*,void*))cmd_callback;
	if(xTaskCreate(mcmd_socket_service, (char const*)((const signed char*)"mcmd_socket_service"), 1024, (void *)socket, MMF_COMMAND_SERVICE_PRIORITY, NULL) != pdPASS) {
		MMF_CMD_ERROR("\r\n mcmd_socket_service: Create Task Error\n");
		goto error;
	}
	return 0;
error:
	mcmd_socket_free(socket);
	return -1;
}

extern u16 _htons(u16 x);
#define WLAN0_NAME "wlan0"
//void mcmd_socket_service(mcmd_socket_t *socket)
void mcmd_socket_service(void *arg)
{
	mcmd_context *mcmd_ctx = (mcmd_context *) arg;
	
	u32 start_time, current_time;
	int mode = 0;
	struct sockaddr_in server_addr, client_addr;
	socklen_t client_addr_len = sizeof(struct sockaddr_in);
	fd_set server_read_fds, client_read_fds;
	struct timeval s_listen_timeout, c_listen_timeout;
	volatile int ok;
	int opt = 1;
	
Redo:
	start_time = rtw_get_current_time();
	wext_get_mode(WLAN0_NAME, &mode);
	//printf("\n\rwlan mode:%d", mode);
	while(1)
	{
		// waiting for sta mode or ap mode ready
		vTaskDelay(1000);
		current_time = rtw_get_current_time();
		if((current_time - start_time) > 60000)
		{
			MMF_CMD_ERROR("\n\rwifi Tx/Rx not ready... mcmd_socket_service stopped");
			return;
		}
		if(rltk_wlan_running(0)>0){
			wext_get_mode(WLAN0_NAME, &mode);
			if(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) >= 0 && (mode == IW_MODE_INFRA)){
				printf("connect successful sta mode\r\n");
				break;
			}
			if(wifi_is_ready_to_transceive(RTW_AP_INTERFACE) >= 0 && (mode == IW_MODE_MASTER)){
				printf("connect successful ap mode\r\n");
				break;
			}
		}
	}
	
	wext_get_mode(WLAN0_NAME, &mode);
	//printf("\n\rwlan mode:%d", mode);
	
	mcmd_ctx->mcmd_socket->server_ip = LwIP_GetIP(&xnetif[0]);
	mcmd_ctx->mcmd_socket->server_port = DEF_MMF_COMMAND_PORT;
	mcmd_ctx->mcmd_socket->server_socket = socket(AF_INET, SOCK_STREAM, 0);
	if(mcmd_ctx->mcmd_socket->server_socket < 0)
	{
		MMF_CMD_ERROR("mmf cmd server socket create failed!\n\r");
		goto error;
	}
	
	if((setsockopt(mcmd_ctx->mcmd_socket->server_socket, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt))) < 0){
		MMF_CMD_ERROR("Error on setting socket option\n\r");
		goto error;
	}
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = *(uint32_t *)(mcmd_ctx->mcmd_socket->server_ip) /* _htonl(INADDR_ANY),socket->server_ip*/;
	server_addr.sin_port = _htons(mcmd_ctx->mcmd_socket->server_port);
	
	if(bind(mcmd_ctx->mcmd_socket->server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0)
	{
		MMF_CMD_ERROR("Cannot bind mmf cmd server socket\n\r");
		goto error;
	}
	listen(mcmd_ctx->mcmd_socket->server_socket, 1);
	printf("mmf cmd socket enabled\n\r");
	printf("[mmf cmd socket] waiting for client to connect \n\r");
	//enter service loop
	while(1)
	{
		FD_ZERO(&server_read_fds);
		s_listen_timeout.tv_sec = 1;
		s_listen_timeout.tv_usec = 0;
		FD_SET(mcmd_ctx->mcmd_socket->server_socket, &server_read_fds);
		if(select(MMF_COMMAND_SELECT_SOCK, &server_read_fds, NULL, NULL, &s_listen_timeout))
		{
			mcmd_ctx->mcmd_socket->client_socket = accept(mcmd_ctx->mcmd_socket->server_socket, (struct sockaddr*)&client_addr, &client_addr_len);
			if(mcmd_ctx->mcmd_socket->client_socket < 0)
			{
				MMF_CMD_ERROR("client_socket error (accept fail)\n\r");
				close(mcmd_ctx->mcmd_socket->client_socket);
				continue;
			}
			
			*(mcmd_ctx->mcmd_socket->remote_ip + 3) = (unsigned char) (client_addr.sin_addr.s_addr >> 24);
			*(mcmd_ctx->mcmd_socket->remote_ip + 2) = (unsigned char) (client_addr.sin_addr.s_addr >> 16);
			*(mcmd_ctx->mcmd_socket->remote_ip + 1) = (unsigned char) (client_addr.sin_addr.s_addr >> 8);
			*(mcmd_ctx->mcmd_socket->remote_ip) = (unsigned char) (client_addr.sin_addr.s_addr );
			
			printf("mmf command server: client socket accepted\n\r");
			while(1)	
			{
				FD_ZERO(&client_read_fds);
				c_listen_timeout.tv_sec = 0;
				c_listen_timeout.tv_usec = 10000;
				FD_SET(mcmd_ctx->mcmd_socket->client_socket, &client_read_fds);
				
				if(select(MMF_COMMAND_SELECT_SOCK, &client_read_fds, NULL, NULL, &c_listen_timeout))
				{
					int len = 0;
					memset(mcmd_ctx->mcmd_socket->request, 0, MMF_COMMAND_BUF_SIZE);
					memset(mcmd_ctx->mcmd_socket->response, 0, MMF_COMMAND_BUF_SIZE);
					len = read(mcmd_ctx->mcmd_socket->client_socket, mcmd_ctx->mcmd_socket->request, MMF_COMMAND_BUF_SIZE);
					
					if (len <=0) {
						printf("mcmd_socket_service: socket closed....\n\r");
						goto out;
					}

					//socket->command = mcmd_parse_cmd(socket->request);
					//mcmd_in_cmd_queue(socket->command,mcmd_ctx);

					if (mcmd_ctx->mcmd_socket->cb_command) {
						printf("read [%d]:[%s]\n\r",strlen((char const*)mcmd_ctx->mcmd_socket->request),mcmd_ctx->mcmd_socket->request);
						len = mcmd_ctx->mcmd_socket->cb_command((void*)mcmd_ctx->mcmd_socket->request,(void*)mcmd_ctx->mcmd_socket->response);
						if (len > MMF_COMMAND_BUF_SIZE)
							len = MMF_COMMAND_BUF_SIZE;
						if (len > 0)
							ok = write(mcmd_ctx->mcmd_socket->client_socket, mcmd_ctx->mcmd_socket->response, len);
					}
					else {
						printf("mcmd_socket_service: no cb_command\n\r");
					}
				}
				
				if(mode == IW_MODE_INFRA){
					if(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) < 0)
						goto out;
				}else if(mode == IW_MODE_MASTER){
					if(wifi_is_ready_to_transceive(RTW_AP_INTERFACE) < 0)
						goto out;
				}else{
					goto out;
				}
			}
out:
			close(mcmd_ctx->mcmd_socket->client_socket);
		}
		
		if(mode == IW_MODE_INFRA) {
			if(wifi_is_ready_to_transceive(RTW_STA_INTERFACE) < 0) {
				MMF_CMD_ERROR("wifi Tx/Rx broke! mmf command server closed\n\r");
				close(mcmd_ctx->mcmd_socket->server_socket);
				printf("mmf command server Reconnect!\n\r");
					goto Redo;
			}
		}else if(mode == IW_MODE_MASTER) {
			if(wifi_is_ready_to_transceive(RTW_AP_INTERFACE) < 0) {
				MMF_CMD_ERROR("wifi Tx/Rx broke! mmf command server closed\n\r");
				close(mcmd_ctx->mcmd_socket->server_socket);
				printf("mmf command server Reconnect!\n\r");
					goto Redo;
			}
		}else{
			goto error;
		}
	}
error:
	close(mcmd_ctx->mcmd_socket->server_socket);
	printf("mmf command socket service stop\n\r");
	vTaskDelete(NULL);
}

mcmd_t* mcmd_parse_cmd(u8 *data)
{
	mcmd_t* cmd = malloc(sizeof(mcmd_t));
	cmd->bCmd = *data;
	cmd->bSubCommand = *(data+1);
	cmd->bidx= *(data+2);
	cmd->bLen= *(data+3);
	cmd->wParam= *(u16 *) (data+4);
	cmd->wAddr= *(u16 *) (data+6);
	cmd->data = malloc(cmd->bLen);
	memcpy(cmd->data, data+8, cmd->bLen);
	
	return cmd;
}

