#include <platform_opts.h>

#if (CONFIG_EXAMPLE_AUDIO_HELIX_AAC)

#include "platform_stdlib.h"
#include "section_config.h"

#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#include "queue.h"

#include "wifi_conf.h"
#include <lwip/sockets.h>
#include <lwip/netdb.h>

#include "audio_api.h"

#include "aacdec.h"

#ifndef SDRAM_BSS_SECTION
#define SDRAM_BSS_SECTION                        
        SECTION(".sdram.bss")
#endif

#define AUDIO_SOURCE_BINARY_ARRAY (1)
#define ADUIO_SOURCE_HTTP_FILE    (0)

#if AUDIO_SOURCE_BINARY_ARRAY
#include "audio_8k_16bit.c"
#endif

#if ADUIO_SOURCE_HTTP_FILE
#define AUDIO_SOURCE_HTTP_FILE_HOST         "192.168.31.15"
#define AUDIO_SOURCE_HTTP_FILE_PORT         (80)
#define AUDIO_SOURCE_HTTP_FILE_NAME         "/audio.aac"
#define BUFFER_SIZE                         (1500)

#define AAC_MAX_FRAME_SIZE (1600)
#define AAC_DATA_CACHE_SIZE ( BUFFER_SIZE + 2 * AAC_MAX_FRAME_SIZE )
SDRAM_BSS_SECTION static uint8_t aac_data_cache[AAC_DATA_CACHE_SIZE];
static uint32_t aac_data_cache_len = 0;
#endif

#if ADUIO_SOURCE_HTTP_FILE
#define AUDIO_PKT_BEGIN (1)
#define AUDIO_PKT_DATA  (2)
#define AUDIO_PKT_END   (3)
typedef struct _audio_pkt_t {
    uint8_t type;
    uint8_t *data;
    uint32_t data_len;
} audio_pkt_t;

#define AUDIO_PKT_QUEUE_LENGTH (50)
static xQueueHandle audio_pkt_queue;
#endif

#define AUDIO_DMA_PAGE_SIZE  2048
#define AUDIO_DMA_PAGE_NUM      4   // Vaild number is 2~4

SDRAM_BSS_SECTION static uint8_t audio_tx_buf[ AUDIO_DMA_PAGE_SIZE * AUDIO_DMA_PAGE_NUM ];
SDRAM_BSS_SECTION static uint8_t audio_rx_buf[ AUDIO_DMA_PAGE_SIZE * AUDIO_DMA_PAGE_NUM ];


static audio_t audio_obj;

#define TX_PAGE_SIZE 2048 //64*N bytes, max: 4032  
#define RX_PAGE_SIZE 2048 //64*N bytes, max: 4032 
#define DMA_PAGE_NUM 2   //Only 2 page 

static u8 dma_txdata[TX_PAGE_SIZE*DMA_PAGE_NUM]__attribute__ ((aligned (0x20))); 
static u8 dma_rxdata[RX_PAGE_SIZE*DMA_PAGE_NUM]__attribute__ ((aligned (0x20))); 

SDRAM_BSS_SECTION static uint8_t decodebuf[ AAC_MAX_NCHANS * AAC_MAX_NSAMPS * sizeof(int16_t) ];

#define AUDIO_TX_PCM_QUEUE_LENGTH (10)
static xQueueHandle audio_tx_pcm_queue = NULL;

static uint32_t audio_tx_pcm_cache_len = 0;
static int16_t audio_tx_pcm_cache[AUDIO_DMA_PAGE_SIZE/2];

static xSemaphoreHandle audio_tx_done_sema = NULL;

static void audio_tx_complete_irq(u32 arg, u8 *pbuf)
{

    audio_t *obj = (audio_t *)arg; 
    u8 *ptx_buf;
    ptx_buf = audio_get_tx_page_adr(obj);
    
    if ( xQueueReceiveFromISR(audio_tx_pcm_queue, ptx_buf, NULL) != pdPASS ) {
        memset(ptx_buf, 0, AUDIO_DMA_PAGE_SIZE);
    }
    
    audio_set_tx_page(obj, ptx_buf);
    xSemaphoreGiveFromISR(audio_tx_done_sema, NULL);
}

static void audio_rx_complete_irq(u32 arg, u8 *pbuf)
{
  
}

static void initialize_audio(uint8_t ch_num, int sample_rate)
{
    printf("ch:%d sr:%d\r\n", ch_num, sample_rate);

    uint8_t smpl_rate_idx = ASR_8KHZ;
    uint8_t ch_num_idx = AUDIO_CH_STEREO;

    switch(ch_num){
        case 1: ch_num_idx = AUDIO_CH_MONO;   break;
        case 2: ch_num_idx = AUDIO_CH_STEREO; break;
        default: break;
    }
    switch(sample_rate){
        case 8000:  smpl_rate_idx = AUDIO_SR_8KHZ;     break;
        case 16000: smpl_rate_idx = AUDIO_SR_16KHZ;    break;	
        case 32000: smpl_rate_idx = AUDIO_SR_32KHZ;    break;
        case 44100: smpl_rate_idx = AUDIO_SR_44p1KHZ;  break;
        case 48000: smpl_rate_idx = AUDIO_SR_48KHZ;    break;
        default: break;
    }

    audio_init(&audio_obj, OUTPUT_SINGLE_EDNED, MIC_DIFFERENTIAL, AUDIO_CODEC_2p8V); 
    audio_set_param(&audio_obj, smpl_rate_idx, WL_16BIT);
    printf("sample rate = %d\r\n",smpl_rate_idx);
    
    audio_mic_analog_gain(&audio_obj, ENABLE, MIC_30DB);

    //Init RX dma
    audio_set_rx_dma_buffer(&audio_obj, dma_rxdata, RX_PAGE_SIZE);    
    audio_rx_irq_handler(&audio_obj, (audio_irq_handler)audio_rx_complete_irq, (u32)&audio_obj);

    //Init TX dma
    audio_set_tx_dma_buffer(&audio_obj, dma_txdata, TX_PAGE_SIZE);    
    audio_tx_irq_handler(&audio_obj, (audio_irq_handler)audio_tx_complete_irq, (u32)&audio_obj);

    //Audio TX and RX Start
    audio_trx_start(&audio_obj);
}

static void audio_play_pcm(int16_t *buf, uint32_t len)
{
    for (int i=0; i<len; i++) {
        audio_tx_pcm_cache[audio_tx_pcm_cache_len++] = buf[i];
        if (audio_tx_pcm_cache_len == AUDIO_DMA_PAGE_SIZE/2) {
            xQueueSend(audio_tx_pcm_queue, audio_tx_pcm_cache, portMAX_DELAY);
            audio_tx_pcm_cache_len = 0;
        }
    }
}

#if AUDIO_SOURCE_BINARY_ARRAY
void audio_play_binary_array(uint8_t *srcbuf, uint32_t len) {
    uint8_t *inbuf;
    int bytesLeft;

    int ret;
    HAACDecoder	hAACDecoder;
    AACFrameInfo frameInfo;

    uint8_t first_frame = 1;

    hAACDecoder = AACInitDecoder();

    inbuf = srcbuf;
    bytesLeft = len;//len;
    //printf("bytesLeft = %d\r\n",bytesLeft);
    audio_tx_done_sema = xSemaphoreCreateBinary();

    frameInfo.outputSamps = 0;
    while (1) {
        ret = AACDecode(hAACDecoder, &inbuf, &bytesLeft, (void *)decodebuf);
        if (!ret) {
            AACGetLastFrameInfo(hAACDecoder, &frameInfo);
            if (first_frame) {
                initialize_audio(frameInfo.nChans, frameInfo.sampRateOut);
                first_frame = 0;
                //printf("frameInfo.nChans = %d frameInfo.sampRateOut = %d\r\n",frameInfo.nChans, frameInfo.sampRateOut);
            }
            audio_play_pcm((void *)decodebuf, frameInfo.outputSamps);
        } else {
            printf("error: %d\r\n", ret);
            break;
        }
    }

    printf("decoding finished\r\n");
}
#endif

#if ADUIO_SOURCE_HTTP_FILE
void file_download_thread(void* param)
{
    int n, server_fd = -1;
    struct sockaddr_in server_addr;
    struct hostent *server_host;
    char *buf = NULL;

    audio_pkt_t pkt_data;

    while (wifi_is_ready_to_transceive(RTW_STA_INTERFACE) != RTW_SUCCESS) vTaskDelay(1000);

    do {
        server_fd = socket(AF_INET, SOCK_STREAM, 0);
        if ( server_fd < 0 ) {
            printf("ERROR: socket\r\n");
            break;
        }

        server_host = gethostbyname(AUDIO_SOURCE_HTTP_FILE_HOST);
        server_addr.sin_port = htons(AUDIO_SOURCE_HTTP_FILE_PORT);
        server_addr.sin_family = AF_INET;
        memcpy((void *) &server_addr.sin_addr, (void *) server_host->h_addr, server_host->h_length);
        if ( connect(server_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) != 0 ) {
            printf("ERROR: connect\r\n");
            break;
        }

        setsockopt(server_fd, SOL_SOCKET, SO_RCVTIMEO, &(int){ 5000 }, sizeof(int));

        buf = (char *) malloc (BUFFER_SIZE);
        if (buf == NULL) {
            printf("ERROR: malloc\r\n");
            break;
        }

		sprintf(buf, "GET %s HTTP/1.1\r\nHost: %s\r\n\r\n", AUDIO_SOURCE_HTTP_FILE_NAME, AUDIO_SOURCE_HTTP_FILE_HOST);
		write(server_fd, buf, strlen(buf));

        audio_pkt_t pkt_begin = { .type = AUDIO_PKT_BEGIN, .data = NULL, .data_len = 0 };
        xQueueSend( audio_pkt_queue, ( void * ) &pkt_begin, portMAX_DELAY );

        n = read(server_fd, buf, BUFFER_SIZE);

        while( (n = read(server_fd, buf, BUFFER_SIZE)) > 0 ) {
            pkt_data.type = AUDIO_PKT_DATA;
            pkt_data.data_len = n;
            pkt_data.data = (uint8_t *) malloc (n);
            while ( pkt_data.data == NULL) {
                vTaskDelay(100);
                pkt_data.data = (uint8_t *) malloc (n);
            }
            memcpy( pkt_data.data, buf, n );
            xQueueSend( audio_pkt_queue, ( void * ) &pkt_data, portMAX_DELAY );
        }

        printf("exit download\r\n");
    } while (0);

    if (buf != NULL) free(buf);

	if(server_fd >= 0) close(server_fd);

    audio_pkt_t pkt_end = { .type = AUDIO_PKT_END, .data = NULL, .data_len = 0 };
    xQueueSend( audio_pkt_queue, ( void * ) &pkt_end, portMAX_DELAY );

    vTaskDelete(NULL);
}

void audio_play_http_file()
{
    audio_pkt_t pkt;

    uint8_t *inbuf;
    int bytesLeft;

    int ret;
    HAACDecoder	hAACDecoder;
    AACFrameInfo frameInfo;

    uint8_t first_frame = 1;

    hAACDecoder = AACInitDecoder();

    while (1) {
        if (xQueueReceive( audio_pkt_queue, &pkt, portMAX_DELAY ) != pdTRUE) {
            continue;
        }

        if (pkt.type == AUDIO_PKT_BEGIN) {
            vTaskDelay(5000); // wait 5 seconds for buffering
        }

        if (pkt.type == AUDIO_PKT_DATA) {
            if (aac_data_cache_len + pkt.data_len >= AAC_DATA_CACHE_SIZE) {
                printf("aac data cache overflow %d %d\r\n", aac_data_cache_len, pkt.data_len);
                free(pkt.data);
                break;
            }

            memcpy( aac_data_cache + aac_data_cache_len, pkt.data, pkt.data_len );
            aac_data_cache_len += pkt.data_len;
            free(pkt.data);

            inbuf = aac_data_cache;
            bytesLeft = aac_data_cache_len;

            ret = 0;
            while (ret == 0) {
                ret = AACDecode(hAACDecoder, &inbuf, &bytesLeft, (void*)decodebuf);
                if (ret == 0) {
                    AACGetLastFrameInfo(hAACDecoder, &frameInfo);
                    
                    if (first_frame) {
                        initialize_audio(frameInfo.nChans, frameInfo.sampRateOut);
                        first_frame = 0;
                    }
                    audio_play_pcm((void*)decodebuf, frameInfo.outputSamps);
                } else {
                    if (ret != ERR_AAC_INDATA_UNDERFLOW) {
                        printf("ret:%d\r\n", ret);
                    }
                    break;
                }
            }

            if (bytesLeft > 0) {
                memmove(aac_data_cache, aac_data_cache + aac_data_cache_len - bytesLeft, bytesLeft);
                aac_data_cache_len = bytesLeft;
            } else {
                aac_data_cache_len = 0;
            }
        }

        if (pkt.type == AUDIO_PKT_END) {
        }
    }

    vTaskDelete(NULL);
}
#endif

void example_audio_helix_aac_thread(void* param)
{
    audio_tx_pcm_queue = xQueueCreate(AUDIO_TX_PCM_QUEUE_LENGTH, AUDIO_DMA_PAGE_SIZE);

#if AUDIO_SOURCE_BINARY_ARRAY
    audio_play_binary_array(sr8000_aac,sr8000_mono_aac_len);
#endif

#if ADUIO_SOURCE_HTTP_FILE
    audio_pkt_queue = xQueueCreate(AUDIO_PKT_QUEUE_LENGTH, sizeof(audio_pkt_t));
    
    audio_tx_done_sema = xSemaphoreCreateBinary();

    if(xTaskCreate(file_download_thread, ((const char*)"file_download_thread"), 768, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(file_download_thread) failed", __FUNCTION__);

    audio_play_http_file();
#endif

    vTaskDelete(NULL);
}

void example_audio_helix_aac(void)
{
    
    if ( xTaskCreate( example_audio_helix_aac_thread, "example_audio_helix_aac_thread", 1024, ( void * ) NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS )
        printf("\n\r%s xTaskCreate(example_audio_helix_aac_thread) failed", __FUNCTION__);
}

#endif