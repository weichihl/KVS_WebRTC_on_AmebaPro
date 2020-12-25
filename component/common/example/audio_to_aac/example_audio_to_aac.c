#include <platform_opts.h>
#include "platform_stdlib.h"

#if (CONFIG_EXAMPLE_AUDIO_TO_AAC)

#include "cmsis.h"
#include "audio_api.h"
#include "wait_api.h"

#include "module_aac.h"
#include "faac_api.h"
#include "fatfs_sdcard_api.h"

audio_t audio_obj;

#define TX_PAGE_SIZE 2048 //64*N bytes, max: 4032  
#define RX_PAGE_SIZE 2048 //64*N bytes, max: 4032 
#define DMA_PAGE_NUM 2   //Only 2 page 

u8 dma_txdata[TX_PAGE_SIZE*DMA_PAGE_NUM]__attribute__ ((aligned (0x20)));
u8 dma_rxdata[RX_PAGE_SIZE*DMA_PAGE_NUM]__attribute__ ((aligned (0x20)));

xQueueHandle audio_rx_pcm_queue = NULL;

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
    
    if( xQueueSendFromISR(audio_rx_pcm_queue, (void *)pbuf, &xHigherPriorityTaskWoken) != pdTRUE){
      printf("\n\rAudio queue full.\n\r");
    } 
    
    if( xHigherPriorityTaskWoken)
      taskYIELD ();

    audio_set_rx_page(&audio_obj); // submit a new page for receive   
}


void example_audio_to_aac_thread(void* param)
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
    audio_rx_pcm_queue = xQueueCreate(30, TX_PAGE_SIZE);
    xQueueReset(audio_rx_pcm_queue);
    
    //Set AAC encoder parameter
    aac_ctx_t *aac_encoder = (aac_ctx_t *)malloc(sizeof(aac_ctx_t));
    extern aac_params_t aac_params;
    memcpy(&aac_encoder->params, &aac_params, sizeof(aac_params_t));
    
    //Initial AAC encoder 
    aac_encoder->stop = 0;
    aac_encode_init(&aac_encoder->faac_enc, aac_encoder->params.bit_length, aac_encoder->params.output_format, aac_encoder->params.sample_rate, aac_encoder->params.channel, aac_encoder->params.mpeg_version, &aac_encoder->params.samples_input, &aac_encoder->params.max_bytes_output);
    
    //Initial SD card for testing AAC data
    fatfs_sd_init();
    fatfs_sd_create_write_buf(32*1024);
    fatfs_sd_open_file("aac_test.aac");
    int time1 = xTaskGetTickCount();
    int time2;
    
    //Set data buffer
    short buf_16bit[TX_PAGE_SIZE];
    uint8_t buf_8bit[TX_PAGE_SIZE];
    
    //Audio TX and RX Start
    audio_trx_start(&audio_obj);
    printf("\n\rAudio Start.\n\r");

    while (1)
    {
      if(xQueueReceive(audio_rx_pcm_queue, (void*)buf_16bit, 100) == pdTRUE)
      {
        int frame_size = 0;  //int samples_read, frame_size;

        //Encode the data with AAC
        frame_size = aac_encode_run(aac_encoder->faac_enc, (void*)buf_16bit, aac_encoder->params.samples_input, (unsigned char *)buf_8bit, aac_encoder->params.max_bytes_output);

        //buf_8bit contain the encoded data
        
        time2 = xTaskGetTickCount();
        printf("\r\nxTaskGetTickCount: %d\r\n", time2 - time1);
        if ((time2 - time1) <= 10000)
        {
          fatfs_sd_write((char*)buf_8bit, frame_size);
        }
        else
        {
          fatfs_sd_flush_buf();
          fatfs_sd_close_file();
          printf("\r\nFile saving finished.\r\n");
          break;
        }

      }
      else
        continue;
    }
    
    vTaskDelete(NULL);
}


void example_audio_to_aac(void)
{
    if ( xTaskCreate( example_audio_to_aac_thread, "example_audio_to_aac_thread", 2048, ( void * ) NULL, tskIDLE_PRIORITY + 5, NULL) != pdPASS )
        printf("\n\r%s xTaskCreate(example_audio_to_aac_thread) failed", __FUNCTION__);
}

#endif // CONFIG_EXAMPLE_AUDIO_TO_AAC
