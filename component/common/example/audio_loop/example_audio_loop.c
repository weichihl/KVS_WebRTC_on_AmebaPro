#include <platform_opts.h>
#include "platform_stdlib.h"

#if (CONFIG_EXAMPLE_AUDIO_LOOP)

#include "cmsis.h"
#include "audio_api.h"
#include "wait_api.h"
#include <string.h>

audio_t audio_obj;

#define TX_PAGE_SIZE 128 //64*N bytes, max: 4032  
#define RX_PAGE_SIZE 128 //64*N bytes, max: 4032 
#define DMA_PAGE_NUM 2   //Only 2 page 

u8 dma_txdata[TX_PAGE_SIZE*DMA_PAGE_NUM]__attribute__ ((aligned (0x20))); 
u8 dma_rxdata[RX_PAGE_SIZE*DMA_PAGE_NUM]__attribute__ ((aligned (0x20))); 

void audio_tx_complete_irq(u32 arg, u8 *pbuf)
{
    audio_t *obj = (audio_t *)arg; 
    
    static u32 count=0;
    count++;
    if ((count&1023) == 1023)
    {
        dbg_printf(".\r\n");
    }

    if (audio_get_tx_error_cnt(obj) != 0x00) {
        dbg_printf("tx page error !!! \r\n");
    }        
}

void audio_rx_complete_irq(u32 arg, u8 *pbuf)
{
    audio_t *obj = (audio_t *)arg; 
    u8 *ptx_addre;

    static u32 count=0;
    count++;
    if ((count&1023) == 1023)
    {
        dbg_printf("*\r\n");
    }

    if (audio_get_rx_error_cnt(obj) != 0x00) {
        dbg_printf("rx page error !!! \r\n");
    }

    ptx_addre = audio_get_tx_page_adr(obj);
    memcpy((void*)ptx_addre, (void*)pbuf, TX_PAGE_SIZE);
    audio_set_tx_page(obj, ptx_addre); // loopback
    audio_set_rx_page(obj); // submit a new page for receive   
}


void example_audio_loop_thread(void* param)
{
    //Wait the power is stable 
    wait_ms(300); 
    
    //Audio Init    
    audio_init(&audio_obj, OUTPUT_SINGLE_EDNED, MIC_DIFFERENTIAL, AUDIO_CODEC_2p8V); 
    audio_set_param(&audio_obj, ASR_8KHZ, WL_16BIT);
    
    audio_mic_analog_gain(&audio_obj, ENABLE, MIC_30DB);

    //Init RX dma
    audio_set_rx_dma_buffer(&audio_obj, dma_rxdata, RX_PAGE_SIZE);    
    audio_rx_irq_handler(&audio_obj, (audio_irq_handler)audio_rx_complete_irq, (u32)&audio_obj);

    //Init TX dma
    audio_set_tx_dma_buffer(&audio_obj, dma_txdata, TX_PAGE_SIZE);    
    audio_tx_irq_handler(&audio_obj, (audio_irq_handler)audio_tx_complete_irq, (u32)&audio_obj);

    //Audio TX and RX Start
    audio_trx_start(&audio_obj);
    
	while(1);
    
    vTaskDelete(NULL);
}


void example_audio_loop(void)
{
    if ( xTaskCreate( example_audio_loop_thread, "example_audio_loop_thread", 2048, ( void * ) NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS )
        printf("\n\r%s xTaskCreate(example_audio_loop_thread) failed", __FUNCTION__);
}

#endif // CONFIG_EXAMPLE_AUDIO_LOOP
