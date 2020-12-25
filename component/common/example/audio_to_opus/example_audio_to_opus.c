#include <platform_opts.h>
#include "platform_stdlib.h"

#if (CONFIG_EXAMPLE_AUDIO_TO_OPUS)

#include "cmsis.h"
#include "audio_api.h"
#include "wait_api.h"
#include <string.h>
#include "opusenc.h"

audio_t audio_obj;

#define TX_PAGE_SIZE 128 //64*N bytes, max: 4032  
#define RX_PAGE_SIZE 128 //64*N bytes, max: 4032 
#define DMA_PAGE_NUM 2   //Only 2 page 

u8 dma_txdata[TX_PAGE_SIZE*DMA_PAGE_NUM]__attribute__ ((aligned (0x20))); 
u8 dma_rxdata[RX_PAGE_SIZE*DMA_PAGE_NUM]__attribute__ ((aligned (0x20)));

//opus parameter
#define SAMPLE_RATE 8000
#define CHANNELS 1
#define APPLICATION OPUS_APPLICATION_AUDIO

xQueueHandle audio_queue;

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

    static u32 count=0;
    count++;
    if ((count&1023) == 1023)
    {
        dbg_printf("*\r\n");
    }

    if (audio_get_rx_error_cnt(obj) != 0x00) {
        dbg_printf("rx page error !!! \r\n");
    }

    BaseType_t xHigherPriorityTaskWoken;
    
    if( xQueueSendFromISR(audio_queue, (void *)pbuf, &xHigherPriorityTaskWoken) != pdTRUE){
      printf("\n\rAudio queue full.\n\r");
    } 
    
    if( xHigherPriorityTaskWoken)
      taskYIELD ();

    audio_set_rx_page(&audio_obj); // submit a new page for receive   
}


void example_audio_to_opus_thread(void* param)
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
    
    //Create a queue to receive the RX buffer from audio_in
    audio_queue = xQueueCreate(6, TX_PAGE_SIZE);
    xQueueReset(audio_queue);
    
    //Audio TX and RX Start
    audio_trx_start(&audio_obj);
    printf("\n\rAudio Start.\n\r");
    
    //Holds the state of the encoder and decoder
    OpusEncoder *encoder;
    OpusDecoder *decoder;
    int err;
    //Create a new encoder state
    encoder = opus_encoder_create(SAMPLE_RATE, CHANNELS, APPLICATION, &err);
    //Create a new decoder state
    decoder = opus_decoder_create(SAMPLE_RATE, CHANNELS, &err);
    
    short buf_16bit[TX_PAGE_SIZE/2];
    unsigned char buf_8bit[TX_PAGE_SIZE/2];
    
    u8 *ptx_addre;
    while (1)
    {
      if(xQueueReceive(audio_queue, (void*)buf_16bit, 6) == pdTRUE)
      {   
        //Encode the data with OPUS encoder
        opus_int32 compressedBytes = opus_encode(encoder, buf_16bit, TX_PAGE_SIZE/2, buf_8bit, TX_PAGE_SIZE/2);
        
        // buf_8bit contain the encoded data
                
        //Decode the data with OPUS decoder
        opus_int32 decompressedBytes = opus_decode(decoder, buf_8bit, compressedBytes, buf_16bit, TX_PAGE_SIZE/2, 0);
        
        ptx_addre = audio_get_tx_page_adr(&audio_obj);
        memcpy((void*)ptx_addre, (void*)buf_16bit, TX_PAGE_SIZE);
        audio_set_tx_page(&audio_obj, ptx_addre); // loopback
      }
      else
       continue;
    }
    
    vTaskDelete(NULL);
}


void example_audio_to_opus(void)
{
    if ( xTaskCreate( example_audio_to_opus_thread, "example_audio_to_opus_thread", 2048, ( void * ) NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS )
        printf("\n\r%s xTaskCreate(example_audio_to_opus_thread) failed", __FUNCTION__);
}

#endif // CONFIG_EXAMPLE_AUDIO_TO_OPUS
