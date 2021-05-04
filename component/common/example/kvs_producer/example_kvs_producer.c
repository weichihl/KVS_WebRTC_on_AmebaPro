#include "platform_opts.h"

#if CONFIG_EXAMPLE_KVS_PRODUCER

#include "example_kvs_producer.h"

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"

#include "wifi_conf.h"

#include "video_common_api.h"
#include "h264_encoder.h"
#include "isp_api.h"
#include "h264_api.h"
#include "mmf2_dbg.h"
#include "sensor.h"

#include "time.h"

#include "kvs_rest_api.h"
#include "mkv_generator.h"
#include "kvs_errors.h"
#include "kvs_port.h"
#include "iot_credential_provider.h"

#define ISP_SW_BUF_NUM      3    // set 2 for 15fps, set 3 for 30fps
#define KVS_QUEUE_DEPTH     ( 20 )

static xQueueHandle kvsProducerVideoQueue;
#if HAS_AUDIO
static xQueueHandle kvsProducerAudioQueue;
#endif

#define ISP_STREAM_ID       0
#define ISP_HW_SLOT         1
#define VIDEO_OUTPUT_BUFFER_SIZE    ( VIDEO_HEIGHT * VIDEO_WIDTH / 10 )

typedef struct isp_s
{
    isp_stream_t* stream;
    
    isp_cfg_t cfg;
    
    isp_buf_t buf_item[ISP_SW_BUF_NUM];
    xQueueHandle output_ready;
    xQueueHandle output_recycle;
} isp_t;

#define FRAGMENT_BEGIN_SIZE           ( 10 )
#define FRAGMENT_END_SIZE             ( 2 )

#define STREAM_STATE_INIT                   (0)
#define STREAM_STATE_LOAD_FRAME             (1)
#define STREAM_STATE_SEND_PACKAGE_HEADER    (2)
#define STREAM_STATE_SEND_MKV_HEADER        (3)
#define STREAM_STATE_SEND_FRAME_DATA        (4)
#define STREAM_STATE_SEND_PACKAGE_ENDING    (5)

typedef struct
{
    char *pDataEndpoint;

    MkvHeader_t mkvHeader;

    uint32_t uFragmentLen;

    uint8_t *pMkvHeader;
    uint32_t uMkvHeaderLen;
    uint32_t uMkvHeaderSize;

    uint8_t trackId;
    uint8_t *pFrameData;
    uint32_t uFrameLen;

    uint8_t pFragmentBegin[ FRAGMENT_BEGIN_SIZE ];
    uint8_t pFragmentEnd[ FRAGMENT_END_SIZE ];
    uint8_t streamState;

    uint8_t isFirstFrame;
    uint8_t isKeyFrame;
    uint64_t frameTimestamp;
    uint64_t lastKeyFrameTimestamp;
} StreamData_t;

typedef struct
{
    uint8_t uTrackId;
    uint64_t uTimestamp;
    void *pData;
    uint32_t uDataSize;
} MediaData_t;

#if HAS_AUDIO
#include "audio_api.h"
#include "module_aac.h"
#include "faac_api.h"

#define AUDIO_DMA_PAGE_NUM 2
#define AUDIO_DMA_PAGE_SIZE ( 2 * 1024 )

#define RX_PAGE_SIZE 	AUDIO_DMA_PAGE_SIZE //64*N bytes, max: 4095. 128, 4032
#define RX_PAGE_NUM 	AUDIO_DMA_PAGE_NUM

static audio_t audio;
static uint8_t dma_rxdata[ RX_PAGE_SIZE * RX_PAGE_NUM ]__attribute__ ((aligned (0x20))); 

#define AUDIO_QUEUE_DEPTH         ( 10 )
static xQueueHandle audioQueue;
#endif

void isp_frame_cb(void* p)
{
    BaseType_t xTaskWokenByReceive = pdFALSE;
    BaseType_t xHigherPriorityTaskWoken;
    
    isp_t* ctx = (isp_t*)p;
    isp_info_t* info = &ctx->stream->info;
    isp_cfg_t *cfg = &ctx->cfg;
    isp_buf_t buf;
    isp_buf_t queue_item;
    
    int is_output_ready = 0;
    
    u32 timestamp = xTaskGetTickCountFromISR();
    
    if(info->isp_overflow_flag == 0){
        is_output_ready = xQueueReceiveFromISR(ctx->output_recycle, &buf, &xTaskWokenByReceive) == pdTRUE;
    }else{
        info->isp_overflow_flag = 0;
        ISP_DBG_ERROR("isp overflow = %d\r\n",cfg->isp_id);
    }
    
    if(is_output_ready){
        isp_handle_buffer(ctx->stream, &buf, MODE_EXCHANGE);
        xQueueSendFromISR(ctx->output_ready, &buf, &xHigherPriorityTaskWoken);    
    }else{
        isp_handle_buffer(ctx->stream, NULL, MODE_SKIP);
    }
    if( xHigherPriorityTaskWoken || xTaskWokenByReceive )
        taskYIELD ();
}

static void sendVideoFrame( VIDEO_BUFFER *pBuffer )
{
    MediaData_t data;

    data.uTimestamp = getEpochTimestampInMs();
    data.uTrackId = MKV_VIDEO_TRACK_NUMBER;
    data.pData = ( VIDEO_BUFFER * )malloc( sizeof( VIDEO_BUFFER ) );
    if( data.pData == NULL )
    {
        free( pBuffer->output_buffer );
    }
    else
    {
        memcpy( data.pData, pBuffer, sizeof( VIDEO_BUFFER ) );
        data.uDataSize = sizeof( VIDEO_BUFFER );
        xQueueSend( kvsProducerVideoQueue, &data, 0xFFFFFFFF);
    }
}

void camera_thread(void *param)
{
    int ret;
    VIDEO_BUFFER video_buf;
    u8 start_recording = 0;
    isp_init_cfg_t isp_init_cfg;
    isp_t isp_ctx;

    vTaskDelay( 2000 / portTICK_PERIOD_MS );

    printf("[H264] init video related settings\n\r");
    
    memset(&isp_init_cfg, 0, sizeof(isp_init_cfg));
    isp_init_cfg.pin_idx = ISP_PIN_IDX;
    isp_init_cfg.clk = SENSOR_CLK_USE;
    isp_init_cfg.ldc = LDC_STATE;
    isp_init_cfg.fps = SENSOR_FPS;
    isp_init_cfg.isp_fw_location = ISP_FW_LOCATION;
    
    video_subsys_init(&isp_init_cfg);
#if CONFIG_LIGHT_SENSOR
    init_sensor_service();
#else
    ir_cut_init(NULL);
    ir_cut_enable(1);
#endif
    
    printf("[H264] create encoder\n\r");
    struct h264_context* h264_ctx;
    ret = h264_create_encoder(&h264_ctx);
    if (ret != H264_OK) {
        printf("\n\rh264_create_encoder err %d\n\r",ret);
        goto exit;
    }

    printf("[H264] get & set encoder parameters\n\r");
    struct h264_parameter h264_parm;
    ret = h264_get_parm(h264_ctx, &h264_parm);
    if (ret != H264_OK) {
        printf("\n\rh264_get_parmeter err %d\n\r",ret);
        goto exit;
    }
    
    h264_parm.height = VIDEO_HEIGHT;
    h264_parm.width = VIDEO_WIDTH;
    h264_parm.rcMode = H264_RC_MODE_CBR;
    h264_parm.bps = 1 * 1024 * 1024;
    h264_parm.ratenum = VIDEO_FPS;
    h264_parm.gopLen = 30;
    
    ret = h264_set_parm(h264_ctx, &h264_parm);
    if (ret != H264_OK) {
        printf("\n\rh264_set_parmeter err %d\n\r",ret);
        goto exit;
    }
    
    printf("[H264] init encoder\n\r");
    ret = h264_init_encoder(h264_ctx);
    if (ret != H264_OK) {
        printf("\n\rh264_init_encoder_buffer err %d\n\r",ret);
        goto exit;
    }
    
    printf("[ISP] init ISP\n\r");
    memset(&isp_ctx,0,sizeof(isp_ctx));
    isp_ctx.output_ready = xQueueCreate(ISP_SW_BUF_NUM, sizeof(isp_buf_t));
    isp_ctx.output_recycle = xQueueCreate(ISP_SW_BUF_NUM, sizeof(isp_buf_t));
    
    isp_ctx.cfg.isp_id = ISP_STREAM_ID;
    isp_ctx.cfg.format = ISP_FORMAT_YUV420_SEMIPLANAR;
    isp_ctx.cfg.width = VIDEO_WIDTH;
    isp_ctx.cfg.height = VIDEO_HEIGHT;
    isp_ctx.cfg.fps = VIDEO_FPS;
    isp_ctx.cfg.hw_slot_num = ISP_HW_SLOT;
    
    isp_ctx.stream = isp_stream_create(&isp_ctx.cfg);
    
    isp_stream_set_complete_callback(isp_ctx.stream, isp_frame_cb, (void*)&isp_ctx);
    
    for (int i=0; i<ISP_SW_BUF_NUM; i++ ) {
        unsigned char *ptr =(unsigned char *) malloc( VIDEO_WIDTH * VIDEO_HEIGHT * 3 / 2 );
        if (ptr==NULL) {
            printf("[ISP] Allocate isp buffer[%d] failed\n\r",i);
            while(1);
        }
        isp_ctx.buf_item[i].slot_id = i;
        isp_ctx.buf_item[i].y_addr = (uint32_t) ptr;
        isp_ctx.buf_item[i].uv_addr = isp_ctx.buf_item[i].y_addr + VIDEO_WIDTH * VIDEO_HEIGHT;
        
        if( i < ISP_HW_SLOT ) {
            // config hw slot
            //printf("\n\rconfig hw slot[%d] y=%x, uv=%x\n\r",i,isp_ctx.buf_item[i].y_addr,isp_ctx.buf_item[i].uv_addr);
            isp_handle_buffer(isp_ctx.stream, &isp_ctx.buf_item[i], MODE_SETUP);
        }
        else {
            // extra sw buffer
            //printf("\n\rextra sw buffer[%d] y=%x, uv=%x\n\r",i,isp_ctx.buf_item[i].y_addr,isp_ctx.buf_item[i].uv_addr);
            if(xQueueSend(isp_ctx.output_recycle, &isp_ctx.buf_item[i], 0)!= pdPASS) {
                printf("[ISP] Queue send fail\n\r");
                while(1);
            }
        }
    }
    
    isp_stream_apply(isp_ctx.stream);
    isp_stream_start(isp_ctx.stream);
    
    printf("Start recording\n");
    int enc_cnt = 0;
    while ( 1 )
    {
        // [9][ISP] get isp data
        isp_buf_t isp_buf;
        if(xQueueReceive(isp_ctx.output_ready, &isp_buf, 10) != pdTRUE) {
            continue;
        }
        
        // [10][H264] encode data
        video_buf.output_buffer_size = VIDEO_OUTPUT_BUFFER_SIZE;
        video_buf.output_buffer = malloc( VIDEO_OUTPUT_BUFFER_SIZE );
        if (video_buf.output_buffer== NULL) {
            printf("Allocate output buffer fail\n\r");
            continue;
        }
        ret = h264_encode_frame(h264_ctx, &isp_buf, &video_buf);
        if (ret != H264_OK) {
            printf("\n\rh264_encode_frame err %d\n\r",ret);
            if (video_buf.output_buffer != NULL)
                free(video_buf.output_buffer);
            continue;
        }
        enc_cnt++;
        
        // [11][ISP] put back isp buffer
        xQueueSend(isp_ctx.output_recycle, &isp_buf, 10);
        
        // [12][FATFS] write encoded data into sdcard
        if (start_recording)
        {
            sendVideoFrame( &video_buf );
        }
        else
        {
            if( h264_is_i_frame( video_buf.output_buffer ) )
            {
                start_recording = 1;
                sendVideoFrame( &video_buf );
            }
            else
            {
                if (video_buf.output_buffer != NULL)
                    free(video_buf.output_buffer);
            }
        }
    }
    
exit:
    isp_stream_stop(isp_ctx.stream);
    xQueueReset(isp_ctx.output_ready);
    xQueueReset(isp_ctx.output_recycle);
    for (int i=0; i<ISP_SW_BUF_NUM; i++ ) {
        unsigned char* ptr = (unsigned char*) isp_ctx.buf_item[i].y_addr;
        if (ptr) 
            free(ptr);
    }

    vTaskDelete( NULL );
}

#if HAS_AUDIO
static void audio_rx_complete(uint32_t arg, uint8_t *pbuf)
{
    BaseType_t xHigherPriorityTaskWoken = pdTRUE;

    xQueueSendFromISR( audioQueue, &pbuf, &xHigherPriorityTaskWoken );
}

static void audio_thread(void *param)
{
    uint8_t *pAudioRxBuffer = NULL;
    uint8_t *pAudioFrame = NULL;
    MediaData_t data;

    vTaskDelay( 2000 / portTICK_PERIOD_MS );

#if 1
    /* AAC initialize */
    faacEncHandle faac_enc;
    int samples_input;
    int max_bytes_output;
    uint8_t *pAacFrame = NULL;

    aac_encode_init(&faac_enc, FAAC_INPUT_16BIT, 0, AUDIO_SAMPLING_RATE, AUDIO_CHANNEL_NUMBER, MPEG4, &samples_input, &max_bytes_output );
#endif

    audioQueue = xQueueCreate( AUDIO_QUEUE_DEPTH, sizeof( uint8_t * ) );
    xQueueReset( audioQueue );

    audio_init( &audio, OUTPUT_SINGLE_EDNED, MIC_DIFFERENTIAL, AUDIO_CODEC_2p8V );
    audio_set_param( &audio, ASR_8KHZ, WL_16BIT );
    audio_mic_analog_gain( &audio, 1, MIC_40DB);

    audio_set_rx_dma_buffer( &audio, dma_rxdata, RX_PAGE_SIZE );
    audio_rx_irq_handler( &audio, audio_rx_complete, NULL );

    audio_rx_start( &audio );

    while( 1 )
    {
        xQueueReceive( audioQueue, &pAudioRxBuffer, portMAX_DELAY );

        pAudioFrame = (uint8_t *)malloc( RX_PAGE_SIZE );
        if( pAudioFrame == NULL )
        {
            printf("%s(): out of memory\r\n");
            continue;
        }

        memcpy( pAudioFrame, pAudioRxBuffer, RX_PAGE_SIZE);
        audio_set_rx_page( &audio );

        data.uTimestamp = getEpochTimestampInMs();
        data.uTrackId = MKV_AUDIO_TRACK_NUMBER;
        data.pData = pAudioFrame;
        data.uDataSize = RX_PAGE_SIZE;

#if 1
        pAacFrame = (uint8_t *)malloc( max_bytes_output );
        if( pAacFrame == NULL )
        {
            printf("%s(): out of memory\r\n");
            continue;
        }
        int xFrameSize = aac_encode_run( faac_enc, pAudioFrame, 1024, pAacFrame, max_bytes_output );
        data.pData = pAacFrame;
        data.uDataSize = xFrameSize;
        free( pAudioFrame );
#endif

        if( !uxQueueSpacesAvailable( kvsProducerAudioQueue ) )
        {
            printf("audio queue is full!\r\n");
            free( data.pData );
        }
        else
        {
            xQueueSend( kvsProducerAudioQueue, &data, 0xFFFFFFFF);
        }
    }
}
#endif

static int loadFrame( StreamData_t *pStreamData )
{
    int32_t retStatus = KVS_STATUS_SUCCEEDED;
    MediaData_t videoData;
    MediaData_t audioData;
    MediaData_t data;
    VIDEO_BUFFER *pVideoBuf;
    uint64_t timestamp = 0;
    uint32_t uFrameLen = 0;

#if HAS_AUDIO
    if( pStreamData->streamState == STREAM_STATE_INIT )
    {
        /* The first frame has to be video, so we flush all audio data. */
        while( xQueueReceive( kvsProducerAudioQueue, &audioData, 0 ) == pdTRUE )
        {
            free( audioData.pData );
        }

        xQueueReceive( kvsProducerVideoQueue, &data, portMAX_DELAY );
    }
    else
    {
        /* Wait both vidoe and audio have data to make sure timestamp consistant */
        xQueuePeek( kvsProducerVideoQueue, &videoData, portMAX_DELAY );
        xQueuePeek( kvsProducerAudioQueue, &audioData, portMAX_DELAY );

        if( videoData.uTimestamp <= audioData.uTimestamp )
        {
            xQueueReceive( kvsProducerVideoQueue, &data, portMAX_DELAY );
        }
        else
        {
            xQueueReceive( kvsProducerAudioQueue, &data, portMAX_DELAY );
        }
    }
#else
    xQueueReceive( kvsProducerVideoQueue, &data, portMAX_DELAY );
#endif

    pStreamData->frameTimestamp = data.uTimestamp;

    if( data.uTrackId == MKV_VIDEO_TRACK_NUMBER )
    {
        pVideoBuf = ( VIDEO_BUFFER * )( data.pData );
        pStreamData->trackId = MKV_VIDEO_TRACK_NUMBER;

        pStreamData->isKeyFrame = ( h264_is_i_frame( pVideoBuf->output_buffer ) ) ? 1 : 0;

        Mkv_convertAnnexBtoAvccInPlace( pVideoBuf->output_buffer, pVideoBuf->output_size, pVideoBuf->output_buffer_size, &uFrameLen );

        pStreamData->pFrameData = pVideoBuf->output_buffer;
        pStreamData->uFrameLen = uFrameLen;

        if( pStreamData->isKeyFrame )
        {
            pStreamData->lastKeyFrameTimestamp = pStreamData->frameTimestamp;
        }
        free( data.pData );

        //printf("v:%llu framesize:%d\r\n", pStreamData->frameTimestamp, pStreamData->uFrameLen);
    }
#if HAS_AUDIO
    else if( data.uTrackId == MKV_AUDIO_TRACK_NUMBER )
    {
        pStreamData->trackId = MKV_AUDIO_TRACK_NUMBER;
        pStreamData->isKeyFrame = 0;
        pStreamData->pFrameData = data.pData;
        pStreamData->uFrameLen = data.uDataSize;

        //printf("a:%llu framesize:%d\r\n", pStreamData->frameTimestamp, pStreamData->uFrameLen);
    }
#endif
    else
    {
    }


    return retStatus;
}

static int initializeMkvHeader( StreamData_t *pStreamData )
{
    int32_t retStatus = KVS_STATUS_SUCCEEDED;
    uint8_t *pVideoCpdData = NULL;
    uint32_t uCpdLen = 0;
    uint32_t uMaxMkvHeaderSize = 0;

    Mkv_generateH264CodecPrivateDataFromAvccNalus( pStreamData->pFrameData, pStreamData->uFrameLen, NULL, &uCpdLen );
    pVideoCpdData = ( uint8_t * ) malloc( uCpdLen );
    Mkv_generateH264CodecPrivateDataFromAvccNalus( pStreamData->pFrameData, pStreamData->uFrameLen, pVideoCpdData, &uCpdLen );

#if HAS_AUDIO
#if 1
    uint8_t pAudioCpdData[ MKV_AAC_CPD_SIZE_BYTE ];
    uint32_t uAudioCpdSize = MKV_AAC_CPD_SIZE_BYTE;
    Mkv_generateAacCodecPrivateData( AAC_LC, AUDIO_SAMPLING_RATE, AUDIO_CHANNEL_NUMBER, pAudioCpdData, MKV_AAC_CPD_SIZE_BYTE );
#else
    uint8_t pAudioCpdData[ MKV_PCM_CPD_SIZE_BYTE ];
    uint32_t uAudioCpdSize = MKV_PCM_CPD_SIZE_BYTE;
    Mkv_generatePcmCodecPrivateData( PCM_FORMAT_CODE_MULAW, AUDIO_SAMPLING_RATE, AUDIO_CHANNEL_NUMBER, pAudioCpdData, MKV_PCM_CPD_SIZE_BYTE );
#endif
#endif

    VideoTrackInfo_t videoTrackInfo =
    {
        .pTrackName = VIDEO_NAME,
        .pCodecName = VIDEO_CODEC_NAME,
        .uWidth = VIDEO_WIDTH,
        .uHeight = VIDEO_HEIGHT,
        .pCodecPrivate = pVideoCpdData,
        .uCodecPrivateLen = uCpdLen
    };

#if HAS_AUDIO
    AudioTrackInfo_t audioTrackInfo =
    {
        .pTrackName = AUDIO_NAME,
        .pCodecName = AUDIO_CODEC_NAME,
        .uFrequency = AUDIO_SAMPLING_RATE,
        .uChannelNumber = AUDIO_CHANNEL_NUMBER,
        .pCodecPrivate = pAudioCpdData,
        .uCodecPrivateLen = uAudioCpdSize
    };
#endif

#if HAS_AUDIO
    Mkv_initializeHeaders( &( pStreamData->mkvHeader ), &videoTrackInfo, &audioTrackInfo );
#else
    Mkv_initializeHeaders( &( pStreamData->mkvHeader ), &videoTrackInfo, NULL );
#endif

    Mkv_getMkvHeader( &( pStreamData->mkvHeader ), 1, 0, MKV_VIDEO_TRACK_NUMBER, NULL, 0, &uMaxMkvHeaderSize );

    pStreamData->pMkvHeader = (uint8_t *) malloc( uMaxMkvHeaderSize );
    pStreamData->uMkvHeaderSize = uMaxMkvHeaderSize;

    pStreamData->isFirstFrame = 1;

    free( pVideoCpdData );

    return retStatus;
}

static int updateFragmetData( StreamData_t *pStreamData )
{
    uint64_t timestamp = 0;
    uint16_t deltaTimestamp = 0;

    if( pStreamData->isKeyFrame )
    {
        timestamp = pStreamData->frameTimestamp;
        deltaTimestamp = 0;
    }
    else
    {
        timestamp = 0;
        deltaTimestamp = ( uint16_t )(pStreamData->frameTimestamp - pStreamData->lastKeyFrameTimestamp);
    }
//printf("%c: t:%llu d:%d k:%d\r\n", pStreamData->trackId == 1 ? 'v' : 'a', timestamp, deltaTimestamp, pStreamData->isKeyFrame);
    /* Update MKV headers */
    Mkv_updateTimestamp( &(pStreamData->mkvHeader), timestamp );
    Mkv_updateDeltaTimestamp( &(pStreamData->mkvHeader), pStreamData->trackId, deltaTimestamp );
    Mkv_updateProperty( &(pStreamData->mkvHeader), pStreamData->trackId, pStreamData->isKeyFrame );
    Mkv_updateFrameSize( &(pStreamData->mkvHeader), pStreamData->trackId, pStreamData->uFrameLen );

    /* Get MKV header */
    Mkv_getMkvHeader( &(pStreamData->mkvHeader), pStreamData->isFirstFrame, pStreamData->isKeyFrame, pStreamData->trackId, pStreamData->pMkvHeader, pStreamData->uMkvHeaderSize, &( pStreamData->uMkvHeaderLen ) );

    /* Update fragment length */
    pStreamData->uFragmentLen = pStreamData->uMkvHeaderLen + pStreamData->uFrameLen;

    /* Update fragment begin */
    snprintf( ( char * )( pStreamData->pFragmentBegin ), FRAGMENT_BEGIN_SIZE, "%08x", pStreamData->uFragmentLen );
    pStreamData->pFragmentBegin[8] = '\r';
    pStreamData->pFragmentBegin[9] = '\n';
}

static int putMediaWantMoreDateCallback( uint8_t ** ppBuffer,
                                         uint32_t *pBufferLen,
                                         uint8_t * customData )
{
    int32_t retStatus = KVS_STATUS_SUCCEEDED;
    StreamData_t *pStreamData = NULL;

    pStreamData = ( StreamData_t * )customData;

    if( pStreamData->streamState == STREAM_STATE_INIT )
    {
        loadFrame( pStreamData );
        initializeMkvHeader( pStreamData );
        pStreamData->streamState = STREAM_STATE_SEND_PACKAGE_HEADER;
    }
    else if ( pStreamData->streamState == STREAM_STATE_LOAD_FRAME )
    {
        loadFrame( pStreamData );
        pStreamData->streamState = STREAM_STATE_SEND_PACKAGE_HEADER;
    }
    if ( pStreamData->streamState == STREAM_STATE_SEND_PACKAGE_HEADER )
    {
        updateFragmetData( pStreamData );
    }

    switch( pStreamData->streamState )
    {
        case STREAM_STATE_SEND_PACKAGE_HEADER:
        {
            *ppBuffer = pStreamData->pFragmentBegin;
            *pBufferLen = FRAGMENT_BEGIN_SIZE;
            pStreamData->streamState = STREAM_STATE_SEND_MKV_HEADER;
            break;
        }
        case STREAM_STATE_SEND_MKV_HEADER:
        {
            *ppBuffer = pStreamData->pMkvHeader;
            *pBufferLen = pStreamData->uMkvHeaderLen;

            pStreamData->streamState = STREAM_STATE_SEND_FRAME_DATA;
            break;
        }
        case STREAM_STATE_SEND_FRAME_DATA:
        {
            *ppBuffer = pStreamData->pFrameData;
            *pBufferLen = pStreamData->uFrameLen;
            pStreamData->streamState = STREAM_STATE_SEND_PACKAGE_ENDING;
            break;
        }
        case STREAM_STATE_SEND_PACKAGE_ENDING:
        {
            *ppBuffer = pStreamData->pFragmentEnd;
            *pBufferLen = FRAGMENT_END_SIZE;

            pStreamData->isFirstFrame = 0;
            free( pStreamData->pFrameData );

            pStreamData->streamState = STREAM_STATE_LOAD_FRAME;
            break;
        }
        default:
        {
            retStatus = KVS_STATUS_REST_UNKNOWN_ERROR;
            break;
        }
    }

    return 0;
}

static int initializeStreamData( StreamData_t *pStreamData )
{
    int32_t retStatus = KVS_STATUS_SUCCEEDED;

    if( pStreamData == NULL )
    {
        retStatus = KVS_STATUS_INVALID_ARG;
    }

    if( retStatus == KVS_STATUS_SUCCEEDED )
    {
        pStreamData->pDataEndpoint = ( char * )malloc( KVS_DATA_ENDPOINT_MAX_SIZE );
        if( pStreamData->pDataEndpoint == NULL )
        {
            retStatus = KVS_STATUS_NOT_ENOUGH_MEMORY;
        }
    }

    if( retStatus == KVS_STATUS_SUCCEEDED )
    {
        pStreamData->uFragmentLen = 0;
        pStreamData->pMkvHeader = NULL;
        pStreamData->uMkvHeaderLen = 0;
        pStreamData->pFrameData = NULL;
        pStreamData->uFrameLen = 0;
        memset(pStreamData->pFragmentBegin, 0, FRAGMENT_BEGIN_SIZE );
        pStreamData->streamState = STREAM_STATE_INIT;
        pStreamData->isFirstFrame = 0;
        pStreamData->isKeyFrame = 0;
        pStreamData->frameTimestamp = 0;
        pStreamData->lastKeyFrameTimestamp = 0;
        pStreamData->pFragmentEnd[0] = '\r';
        pStreamData->pFragmentEnd[1] = '\n';
    }

    return retStatus;
}

extern char log_buf[100];
extern xSemaphoreHandle log_rx_interrupt_sema;
void kvs_producer_thread( void * param )
{
    vTaskDelay( 1000 / portTICK_PERIOD_MS );

#if 0
    sprintf(log_buf, "ATW0=ssid");
    xSemaphoreGive(log_rx_interrupt_sema);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );

    sprintf(log_buf, "ATW1=pw");
    xSemaphoreGive(log_rx_interrupt_sema);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );

    sprintf(log_buf, "ATWC");
    xSemaphoreGive(log_rx_interrupt_sema);
    vTaskDelay( 1000 / portTICK_PERIOD_MS );
#endif

    // initialize HW crypto
    platform_set_malloc_free( (void*(*)( size_t ))calloc, vPortFree);

    while( wifi_is_ready_to_transceive( RTW_STA_INTERFACE ) != RTW_SUCCESS )
    {
        vTaskDelay( 200 / portTICK_PERIOD_MS );
    }
    printf( "wifi connected\r\n" );

    sntp_init();
    while( getEpochTimestampInMs() < 1000000000000ULL )
    {
        vTaskDelay( 200 / portTICK_PERIOD_MS );
    }

    int32_t retStatus = KVS_STATUS_SUCCEEDED;
    StreamData_t *pStreamData = NULL;
    KvsServiceParameter_t serviceParameter;
#if USE_IOT_CERT
    IotCredentialRequest_t req = {
            .pCredentialHost = CREDENTIALS_HOST,
            .pRoleAlias = ROLE_ALIAS,
            .pThingName = THING_NAME,
            .pRootCA = ROOT_CA,
            .pCertificate = CERTIFICATE,
            .pPrivateKey = PRIVATE_KEY
    };
    IotCredentialToken_t token;
#endif

#if USE_IOT_CERT
    retStatus = Iot_getCredential( &req, &token );

    if( retStatus == KVS_STATUS_SUCCEEDED )
    {
        serviceParameter.pAccessKey = token.pAccessKeyId;
        serviceParameter.pSecretKey = token.pSecretAccessKey;
        serviceParameter.pToken = token.pSessionToken;
    }
#else
    serviceParameter.pAccessKey = AWS_ACCESS_KEY;
    serviceParameter.pSecretKey = AWS_SECRET_KEY;
    serviceParameter.pToken = NULL;
#endif

    serviceParameter.pRegion = AWS_KVS_REGION;
    serviceParameter.pService = AWS_KVS_SERVICE;
    serviceParameter.pHost = AWS_KVS_HOST;
    serviceParameter.pUserAgent = HTTP_AGENT;

    if( retStatus == KVS_STATUS_SUCCEEDED )
    {
        pStreamData = ( StreamData_t * )malloc( sizeof( StreamData_t ) );
        if( pStreamData == NULL )
        {
            printf( "failed to allocate kvs stream data\r\n" );
            retStatus = KVS_STATUS_NOT_ENOUGH_MEMORY;
        }
    }

    if( retStatus == KVS_STATUS_SUCCEEDED )
    {
        retStatus = initializeStreamData( pStreamData );
        if( retStatus != KVS_STATUS_SUCCEEDED )
        {
            printf( "failed to initialize stream data\r\n" );
        }
    }

    if( retStatus == KVS_STATUS_SUCCEEDED )
    {
        printf( "try to describe stream\r\n" );
        retStatus = Kvs_describeStream( &serviceParameter, KVS_STREAM_NAME );
        if( retStatus != KVS_STATUS_SUCCEEDED )
        {
            printf( "failed to describe stream, err(%d)\r\n", retStatus );
#if USE_IOT_CERT
            printf( "If we use IoT certification, then KVS stream has to be created first.\n" );
#else
            printf( "try to create stream\r\n" );
            retStatus = Kvs_createStream( &serviceParameter, DEVICE_NAME, KVS_STREAM_NAME, MEDIA_TYPE, DATA_RETENTION_IN_HOURS);
            if( retStatus == KVS_STATUS_SUCCEEDED )
            {
                printf( "Create stream successfully\r\n" );
            }
            else
            {
                printf( "Failed to create stream, err(%d)\r\n", retStatus );
            }
#endif
        }
    }

    if( retStatus == KVS_STATUS_SUCCEEDED )
    {
        printf( "try to get data endpoint\r\n" );
        retStatus = Kvs_getDataEndpoint( &serviceParameter, KVS_STREAM_NAME, pStreamData->pDataEndpoint, KVS_DATA_ENDPOINT_MAX_SIZE );
        if( retStatus == KVS_STATUS_SUCCEEDED )
        {
            printf( "Data endpoint: %s\r\n", pStreamData->pDataEndpoint );
        }
        else
        {
            printf( "Failed to get data endpoint, err(%d)\r\n", retStatus );
        }
    }

    if( retStatus == KVS_STATUS_SUCCEEDED )
    {
        kvsProducerVideoQueue = xQueueCreate( KVS_QUEUE_DEPTH, sizeof( MediaData_t ) );
        xQueueReset(kvsProducerVideoQueue);

#if HAS_AUDIO
        kvsProducerAudioQueue = xQueueCreate( KVS_QUEUE_DEPTH, sizeof( MediaData_t ) );
        xQueueReset(kvsProducerAudioQueue);
#endif

        if( xTaskCreate( camera_thread, ( ( const char * )"camera_thread" ), 1024, NULL, tskIDLE_PRIORITY + 1, NULL ) != pdPASS )
            printf("\n\r%s xTaskCreate(camera_thread) failed", __FUNCTION__ );

#if HAS_AUDIO
        if( xTaskCreate( audio_thread, ( ( const char * )"audio_thread" ), 1024, NULL, tskIDLE_PRIORITY + 1, NULL ) != pdPASS )
            printf("\n\r%s xTaskCreate(audio_thread) failed", __FUNCTION__ );
#endif
    }

    if( retStatus == KVS_STATUS_SUCCEEDED )
    {
        /* "PUT MEDIA" RESTful API uses different endpoint */
        serviceParameter.pHost = pStreamData->pDataEndpoint;

        printf( "try to put media\r\n" );
        retStatus = Kvs_putMedia( &serviceParameter, KVS_STREAM_NAME, putMediaWantMoreDateCallback, pStreamData );
        if( retStatus == KVS_STATUS_SUCCEEDED )
        {
            printf( "put media success\r\n" );
        }
        else
        {
            printf( "Failed to put media, err(%d)\r\n", retStatus );
        }
    }

    vTaskDelete( NULL );
}

void example_kvs_producer( void )
{
    if( xTaskCreate(kvs_producer_thread, ((const char*)"kvs_producer_thread"), 4096, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
        printf("\n\r%s xTaskCreate(kvs_producer_thread) failed", __FUNCTION__);
}

#endif // #ifdef CONFIG_EXAMPLE_KVS_PRODUCER