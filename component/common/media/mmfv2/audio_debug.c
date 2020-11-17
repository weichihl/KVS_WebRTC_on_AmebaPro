#include <audio_debug.h>
#include <cmsis.h>
#include <stdio_port_func.h>
#include <hal_uart.h>

uint8_t* audio_rx_debug_buffer;
uint8_t* audio_tx_debug_buffer;

uint8_t* audio_rx_aec_buffer;

int audio_rx_debug_len;
int audio_tx_debug_len;

int audio_rx_aec_len;

int audio_rx_debug_ena = 0;
int audio_tx_debug_ena = 0;

int audio_rx_aec_ena = 0;

extern hal_uart_adapter_t log_uart;			// from ram_start.c
extern void uart_irq(u32 id,u32 event);		// from rtl_console.c

// stop stdio
void audio_stdio_off(void)
{
	stdio_port_init_s ((void *)&log_uart, (stdio_putc_t)NULL, (stdio_getc_t)NULL);

    stdio_port_init_ns ((void *)&log_uart, (stdio_putc_t)NULL, (stdio_getc_t)NULL);
	//stdio_port_deinit_s();
	//stdio_port_deinit_ns();
}

void audio_stdio_on(void)
{
	stdio_port_init_s ((void *)&log_uart, (stdio_putc_t)hal_uart_stubs.hal_uart_wputc,\
                     (stdio_getc_t)hal_uart_stubs.hal_uart_rgetc);

    stdio_port_init_ns ((void *)&log_uart, (stdio_putc_t)hal_uart_stubs.hal_uart_wputc,\
                     (stdio_getc_t)hal_uart_stubs.hal_uart_rgetc);
}

void audio_console_rx_off(void)
{	
	hal_uart_rxind_hook(&log_uart, NULL, 0, 0);   
}

void audio_console_rx_on(void)
{
	hal_uart_rxind_hook(&log_uart, uart_irq, 0, 0);   
}

void audio_debug_buf_print(uint8_t *buf)
{
	for(int line=0;line<16;line++){
		for(int i=0;i<16;i++){
			printf("%x ", buf[line*16+i]);
		}
		printf("\n");
	}
	printf("\n");
}

// init rx debug buffer
void audio_rx_debug_init(int time)
{
	int new_debug_len = 8000*2*time;
	
	if( (audio_rx_debug_len !=0) && (new_debug_len != audio_rx_debug_len)){
		if(audio_rx_debug_buffer){
			free(audio_rx_debug_buffer);
			audio_rx_debug_buffer = NULL;
	}
		
		if(audio_rx_aec_buffer){
			free(audio_rx_aec_buffer);
			audio_rx_aec_buffer = NULL;
		}
	}
	audio_rx_debug_len = new_debug_len;
	audio_rx_aec_len = new_debug_len;
	audio_rx_debug_buffer = malloc(new_debug_len);	
	audio_rx_aec_buffer = malloc(new_debug_len);
}

// deinit rx debug buffer
void audio_rx_debug_deinit(void)
{
	if(audio_rx_debug_buffer)
		free(audio_rx_debug_buffer);
}

// start rx debug 
void audio_rx_debug_start(int mode)	// mode : 1 (mic), mode : 2 (aec)
{
	if(audio_rx_debug_buffer){
		audio_rx_debug_ena = mode;
		audio_rx_aec_ena = mode;
	}else
		printf("rx debug fail, no memory\n\r");
}

// dump debug data to uart
void audio_rx_debug_dump(void)
{
	audio_stdio_off();
	char *atad_start_word = "_a_t_a_d_";
	vTaskDelay(500);
	hal_uart_send(&log_uart, atad_start_word, strlen(atad_start_word), 1000);
	vTaskDelay(500);
	// RAM to UART
	//hal_uart_send(&log_uart, audio_rx_debug_buffer, audio_rx_debug_len, 5000);

	
	int rx_len = 0;
	#define MAX_UART_DMA_LENGTH	2*1024	
	while(rx_len < audio_rx_debug_len){ 
		int rest_len = audio_rx_debug_len - rx_len;
		int dma_len = rest_len > MAX_UART_DMA_LENGTH? MAX_UART_DMA_LENGTH:rest_len;
		hal_uart_send(&log_uart, &audio_rx_debug_buffer[rx_len], dma_len, 1000);
		//hal_uart_dma_send(&log_uart, &audio_rx_debug_buffer[rx_len], dma_len);
		rx_len += dma_len;
	}	
	
	audio_stdio_on();
}

void audio_rx_aec_dump(void)
{
	audio_stdio_off();
	char *atad_start_word = "_a_t_a_d_";
	vTaskDelay(500);
	hal_uart_send(&log_uart, atad_start_word, strlen(atad_start_word), 1000);
	vTaskDelay(500);
	// RAM to UART
	//hal_uart_send(&log_uart, audio_rx_debug_buffer, audio_rx_debug_len, 5000);

	
	int rx_len = 0;
	#define MAX_UART_DMA_LENGTH	2*1024	
	while(rx_len < audio_rx_aec_len){ 
		int rest_len = audio_rx_aec_len - rx_len;
		int dma_len = rest_len > MAX_UART_DMA_LENGTH? MAX_UART_DMA_LENGTH:rest_len;
		hal_uart_send(&log_uart, &audio_rx_aec_buffer[rx_len], dma_len, 1000);
		//hal_uart_dma_send(&log_uart, &audio_rx_debug_buffer[rx_len], dma_len);
		rx_len += dma_len;
	}	
	
	audio_stdio_on();
}

// init tx debug buffer
void audio_tx_debug_init(int time)
{
	int new_debug_len = 8000*2*time;
	
	if( (audio_tx_debug_len !=0) && (new_debug_len != audio_tx_debug_len)){
		if(audio_tx_debug_buffer)
			free(audio_tx_debug_buffer);
			audio_tx_debug_buffer = NULL;
	}
	audio_tx_debug_len = new_debug_len;
	audio_tx_debug_buffer = malloc(new_debug_len);
}

// deinit tx debug buffer
void audio_tx_debug_deinit(void)
{
	if(audio_tx_debug_buffer)
		free(audio_tx_debug_buffer);
}

// start sending to speaker
void audio_tx_debug_start(void)
{
	if(audio_tx_debug_buffer)
		audio_tx_debug_ena = 1;
	else
		printf("tx debug fail, no memory");
}

// receive data from uart
void audio_tx_debug_get(void)
{
	audio_console_rx_off();
	audio_stdio_off();
	
	int tx_len = 0;
	#define MAX_UART_DMA_LENGTH	2*1024
	// UART to RAM
	while(tx_len < audio_tx_debug_len){ 
		int rest_len = audio_tx_debug_len - tx_len;
		int dma_len = rest_len > MAX_UART_DMA_LENGTH? MAX_UART_DMA_LENGTH:rest_len;
		//hal_uart_dma_recv(&log_uart, &audio_tx_debug_buffer[tx_len], dma_len);
		hal_uart_recv(&log_uart, &audio_tx_debug_buffer[tx_len], dma_len, 1000);
		tx_len += dma_len;
		printf("\r%02d\%", tx_len*100/audio_tx_debug_len);
	}
	printf(" - done\n\r");
	
	audio_stdio_on();	
	audio_console_rx_on();
}