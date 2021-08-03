 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/
#include "platform_opts.h"
#if !CONFIG_EXAMPLE_KVS_WEBRTC

/* Headers for example */
#include <com/amazonaws/kinesis/video/cproducer/Include.h>
#include "../../example/kvs_webrtc/example_kvs_webrtc.h"
#include "../../example/kvs_webrtc/Samples.h"
#include "module_kvs_webrtc.h"

#define FILE_LOGGING_BUFFER_SIZE        (100 * 1024)
#define MAX_NUMBER_OF_LOG_FILES         5
extern PSampleConfiguration gSampleConfiguration;

/* Config for Ameba-Pro */
#define STACK_SIZE              20*1024
#define KVS_QUEUE_DEPTH         20

/* Network */
#include <lwip_netconf.h>
#include "wifi_conf.h"
#include <sntp/sntp.h>

/* used to monitor skb resource */
extern int skbbuf_used_num;
extern int skbdata_used_num;
extern int max_local_skb_num;
extern int max_skb_buf_num;

/* Audio/Video */
#include "avcodec.h"
#include "video_common_api.h"
#include "sensor.h"

static xQueueHandle kvsWebrtcVideoQueue;
static xQueueHandle kvsWebrtcAudioQueue;

PVOID sendVideoPackets(PVOID args)
{
    STATUS retStatus = STATUS_SUCCESS;
    PSampleConfiguration pSampleConfiguration = (PSampleConfiguration) args;
    RtcEncoderStats encoderStats;
    Frame frame;
    STATUS status;
    UINT32 i;
    MEMSET(&encoderStats, 0x00, SIZEOF(RtcEncoderStats));

    u8 start_transfer = 0;

    if (pSampleConfiguration == NULL) {
        printf("[KVS Master] sendVideoPackets(): operation returned status code: 0x%08x \n\r", STATUS_NULL_ARG);
        goto CleanUp;
    }

    frame.presentationTs = 0;

    VIDEO_BUFFER video_buf;

    while (!ATOMIC_LOAD_BOOL(&pSampleConfiguration->appTerminateFlag)) 
    {
        if(xQueueReceive( kvsWebrtcVideoQueue, &video_buf, portMAX_DELAY ) != pdTRUE) {
            continue;
        }

        /* Check if the frame is I frame */
        if (!start_transfer) {
            if (h264_is_i_frame(video_buf.output_buffer)) {
                start_transfer = 1;
            }
            else {
                if (video_buf.output_buffer != NULL)
                    free(video_buf.output_buffer);
                continue;
            }
        }

        frame.frameData = video_buf.output_buffer;
        frame.size = video_buf.output_size;
        frame.presentationTs = getEpochTimestampInHundredsOfNanos(NULL);
        //printf("video timestamp = %llu\n\r", frame.presentationTs);

        // based on bitrate of samples/h264SampleFrames/frame-*
        encoderStats.width = KVS_VIDEO_WIDTH;
        encoderStats.height = KVS_VIDEO_HEIGHT;
        encoderStats.targetBitrate = KVS_WEBRTC_BITRATE;

        /* wait for skb resource release */
        if((skbdata_used_num > (max_skb_buf_num - 5)) || (skbbuf_used_num > (max_local_skb_num - 5))){
            if (video_buf.output_buffer != NULL){
                free(video_buf.output_buffer);
            }
            continue; //skip this frame and wait for skb resource release.
        }

        MUTEX_LOCK(pSampleConfiguration->streamingSessionListReadLock);
        for (i = 0; i < pSampleConfiguration->streamingSessionCount; ++i) {
            status = writeFrame(pSampleConfiguration->sampleStreamingSessionList[i]->pVideoRtcRtpTransceiver, &frame);
            encoderStats.encodeTimeMsec = 4; // update encode time to an arbitrary number to demonstrate stats update
            updateEncoderStats(pSampleConfiguration->sampleStreamingSessionList[i]->pVideoRtcRtpTransceiver, &encoderStats);
            if (status != STATUS_SRTP_NOT_READY_YET) {
                if (status != STATUS_SUCCESS) {
#ifdef VERBOSE
                    printf("writeFrame() failed with 0x%08x\n\r", status);
#endif
                }
            }
        }
        MUTEX_UNLOCK(pSampleConfiguration->streamingSessionListReadLock);
        free(video_buf.output_buffer);
    }

CleanUp:

    CHK_LOG_ERR(retStatus);
    return (PVOID)(ULONG_PTR) retStatus;
}

typedef struct audio_buf_s{
    uint8_t *data_buf;
    uint8_t size;
    uint32_t timestamp;
}audio_buf_t;

PVOID sendAudioPackets(PVOID args)
{
    STATUS retStatus = STATUS_SUCCESS;
    PSampleConfiguration pSampleConfiguration = (PSampleConfiguration) args;
    Frame frame;
    UINT32 i;
    STATUS status;

    if (pSampleConfiguration == NULL) {
        printf("[KVS Master] sendAudioPackets(): operation returned status code: 0x%08x \n", STATUS_NULL_ARG);
        goto CleanUp;
    }

    frame.presentationTs = 0;

    audio_buf_t audio_buf;

    while (!ATOMIC_LOAD_BOOL(&pSampleConfiguration->appTerminateFlag)) 
    {
        if(xQueueReceive( kvsWebrtcAudioQueue, &audio_buf, portMAX_DELAY ) != pdTRUE) {
            continue;
        }

        frame.frameData = audio_buf.data_buf;
        frame.size = audio_buf.size;
        frame.presentationTs = getEpochTimestampInHundredsOfNanos(&audio_buf.timestamp);
        //printf("audio timestamp = %llu\n\r", frame.presentationTs);

        // wait for skb resource release
        if((skbdata_used_num > (max_skb_buf_num - 5)) || (skbbuf_used_num > (max_local_skb_num - 5))){
            if (audio_buf.data_buf != NULL){
                free(audio_buf.data_buf);
            }
            //skip this frame and wait for skb resource release.
            continue;
        }

        MUTEX_LOCK(pSampleConfiguration->streamingSessionListReadLock);
        for (i = 0; i < pSampleConfiguration->streamingSessionCount; ++i) {
            status = writeFrame(pSampleConfiguration->sampleStreamingSessionList[i]->pAudioRtcRtpTransceiver, &frame);
            if (status != STATUS_SRTP_NOT_READY_YET) {
                if (status != STATUS_SUCCESS) {
#ifdef VERBOSE
                    printf("writeFrame() failed with 0x%08x\n", status);
#endif
                }
            }
        }
        MUTEX_UNLOCK(pSampleConfiguration->streamingSessionListReadLock);
        free(audio_buf.data_buf);
    }

CleanUp:

    return (PVOID)(ULONG_PTR) retStatus;
}

UCHAR wifi_ip[16];
UCHAR* ameba_get_ip(void){
    extern struct netif xnetif[NET_IF_NUM];
    UCHAR *ip = LwIP_GetIP(&xnetif[0]);
    memset(wifi_ip, 0, sizeof(wifi_ip)/sizeof(wifi_ip[0]));
    memcpy(wifi_ip, ip, 4);
    return wifi_ip;
}

static int amebapro_platform_init(void)
{
    /* initialize HW crypto, do this if mbedtls using AES hardware crypto */
    platform_set_malloc_free( (void*(*)( size_t ))calloc, vPortFree);

    /* CRYPTO_Init -> Configure mbedtls to use FreeRTOS mutexes -> mbedtls_threading_set_alt(...) */
    CRYPTO_Init();

    while( wifi_is_ready_to_transceive( RTW_STA_INTERFACE ) != RTW_SUCCESS ){
        vTaskDelay( 200 / portTICK_PERIOD_MS );
    }
    printf( "wifi connected\r\n" );

    sntp_init();
    while( getEpochTimestampInHundredsOfNanos(NULL) < 10000000000000000ULL ){
        vTaskDelay( 200 / portTICK_PERIOD_MS );
    }

    return 0;
}

static void kvs_webrtc_thread( void * param )
{
    printf("=== KVS Example ===\n\r");

    // amebapro platform init
    if (amebapro_platform_init() < 0) {
        printf("platform init fail\n\r");
        goto fail;
    }

    STATUS retStatus = STATUS_SUCCESS;
    PSampleConfiguration pSampleConfiguration = NULL;
    SignalingClientMetrics signalingClientMetrics;
    signalingClientMetrics.version = 0;

    // do trickleIce by default
    printf("[KVS Master] Using trickleICE by default\n\r");
    retStatus =
        createSampleConfiguration(KVS_WEBRTC_CHANNEL_NAME, SIGNALING_CHANNEL_ROLE_TYPE_MASTER, TRUE, TRUE, &pSampleConfiguration);

    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] createSampleConfiguration(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }
    printf("[KVS Master] Created signaling channel %s\n\r", KVS_WEBRTC_CHANNEL_NAME);

    if (pSampleConfiguration->enableFileLogging) {
        retStatus = createFileLogger(FILE_LOGGING_BUFFER_SIZE, MAX_NUMBER_OF_LOG_FILES, (PCHAR) FILE_LOGGER_LOG_FILE_DIRECTORY_PATH, TRUE, TRUE, NULL);
        if (retStatus != STATUS_SUCCESS) {
            printf("[KVS Master] createFileLogger(): operation returned status code: 0x%08x \n\r", retStatus);
            pSampleConfiguration->enableFileLogging = FALSE;
        }
    }

    // Set the video handlers
    pSampleConfiguration->videoSource = sendVideoPackets;
    pSampleConfiguration->audioSource = sendAudioPackets;
    pSampleConfiguration->mediaType = SAMPLE_STREAMING_AUDIO_VIDEO;

    printf("[KVS Master] Finished setting audio and video handlers\n\r");

    // Initialize KVS WebRTC. This must be done before anything else, and must only be done once.
    retStatus = initKvsWebRtc();
    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] initKvsWebRtc(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }
    printf("[KVS Master] KVS WebRTC initialization completed successfully\n\r");

    pSampleConfiguration->signalingClientCallbacks.messageReceivedFn = signalingMessageReceived;

    strcpy(pSampleConfiguration->clientInfo.clientId, SAMPLE_MASTER_CLIENT_ID);

    retStatus = signalingClientCreate(&pSampleConfiguration->clientInfo, &pSampleConfiguration->channelInfo,
                                            &pSampleConfiguration->signalingClientCallbacks, pSampleConfiguration->pCredentialProvider,
                                            &pSampleConfiguration->signalingClientHandle);
    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] signalingClientCreate(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }
    printf("[KVS Master] Signaling client created successfully\n\r");

    // Enable the processing of the messages
    retStatus = signalingClientConnect(pSampleConfiguration->signalingClientHandle);
    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] signalingClientConnect(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }
    printf("[KVS Master] Signaling client connection to socket established\n\r");

    gSampleConfiguration = pSampleConfiguration;

    printf("[KVS Master] Channel %s set up done \n\r", KVS_WEBRTC_CHANNEL_NAME);

    // Checking for termination
    retStatus = sessionCleanupWait(pSampleConfiguration);
    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] sessionCleanupWait(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }

    printf("[KVS Master] Streaming session terminated\n\r");


CleanUp:
    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] Terminated with status code 0x%08x", retStatus);
    }

    printf("[KVS Master] Cleaning up....\n\r");
    if (pSampleConfiguration != NULL) {
        // Kick of the termination sequence
        ATOMIC_STORE_BOOL(&pSampleConfiguration->appTerminateFlag, TRUE);

        // Join the threads
        if (pSampleConfiguration->mediaSenderTid != INVALID_TID_VALUE) {
            THREAD_JOIN(pSampleConfiguration->mediaSenderTid, NULL);
        }

        if (pSampleConfiguration->enableFileLogging) {
            freeFileLogger();
        }
        retStatus = signalingClientGetMetrics(pSampleConfiguration->signalingClientHandle, &signalingClientMetrics);
        if (retStatus == STATUS_SUCCESS) {
            logSignalingClientStats(&signalingClientMetrics);
        } else {
            printf("[KVS Master] signalingClientGetMetrics() operation returned status code: 0x%08x", retStatus);
        }
        retStatus = signalingClientFree(&pSampleConfiguration->signalingClientHandle);
        if (retStatus != STATUS_SUCCESS) {
            printf("[KVS Master] freeSignalingClient(): operation returned status code: 0x%08x", retStatus);
        }

        retStatus = freeSampleConfiguration(&pSampleConfiguration);
        if (retStatus != STATUS_SUCCESS) {
            printf("[KVS Master] freeSampleConfiguration(): operation returned status code: 0x%08x", retStatus);
        }
    }
    printf("[KVS Master] Cleanup done\n\r");

fail:

    vTaskDelete(NULL);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////

int kvs_webrtc_handle(void* p, void* input, void* output)
{
    kvs_webrtc_ctx_t *ctx = (kvs_webrtc_ctx_t*)p;

    mm_queue_item_t* input_item = (mm_queue_item_t*)input;

    if (input_item->type == AV_CODEC_ID_H264)
    {
        VIDEO_BUFFER video_buf;
        video_buf.output_buffer_size = KVS_VIDEO_OUTPUT_BUFFER_SIZE;
        video_buf.output_buffer = malloc( KVS_VIDEO_OUTPUT_BUFFER_SIZE );

        video_buf.output_size = input_item->size;
        memcpy(video_buf.output_buffer, (uint8_t*)input_item->data_addr, video_buf.output_size);
        
        if (uxQueueSpacesAvailable(kvsWebrtcVideoQueue) != 0)
            xQueueSend( kvsWebrtcVideoQueue, &video_buf, 0);
        else
            free(video_buf.output_buffer);
    }
    else if (input_item->type == AV_CODEC_ID_PCMU)
    {
        audio_buf_t audio_buf;
        audio_buf.size = input_item->size;

        audio_buf.data_buf =  malloc( audio_buf.size );
        memcpy(audio_buf.data_buf, (uint8_t*)input_item->data_addr, audio_buf.size);

        audio_buf.timestamp = xTaskGetTickCount();

        if (uxQueueSpacesAvailable(kvsWebrtcAudioQueue) != 0)
            xQueueSend( kvsWebrtcAudioQueue, &audio_buf, 0);
        else
            free(audio_buf.data_buf);
    }

    return 0;
}

int kvs_webrtc_control(void *p, int cmd, int arg)
{
    kvs_webrtc_ctx_t *ctx = (kvs_webrtc_ctx_t*)p;

    switch(cmd){

    case CMD_KVS_WEBRTC_SET_APPLY:
        if( xTaskCreate(kvs_webrtc_thread, ((const char*)"kvs_webrtc_thread"), STACK_SIZE, NULL, tskIDLE_PRIORITY + 3, NULL) != pdPASS){
            printf("\n\r%s xTaskCreate(kvs_webrtc_thread) failed", __FUNCTION__);
        }
        break;
    }
    return 0;
}

void* kvs_webrtc_destroy(void* p)
{
    kvs_webrtc_ctx_t *ctx = (kvs_webrtc_ctx_t*)p;
    if(ctx) free(ctx);
    return NULL;
}

void* kvs_webrtc_create(void* parent)
{
    kvs_webrtc_ctx_t *ctx = malloc(sizeof(kvs_webrtc_ctx_t));
    if(!ctx) return NULL;
    memset(ctx, 0, sizeof(kvs_webrtc_ctx_t));
    ctx->parent = parent;

    kvsWebrtcVideoQueue = xQueueCreate( KVS_QUEUE_DEPTH, sizeof( VIDEO_BUFFER ) );
    xQueueReset(kvsWebrtcVideoQueue);

    kvsWebrtcAudioQueue = xQueueCreate( KVS_QUEUE_DEPTH, sizeof( audio_buf_t ) );
    xQueueReset(kvsWebrtcAudioQueue);

    printf("kvs_webrtc_create...\r\n");

    return ctx;
}

mm_module_t kvs_webrtc_module = {
    .create = kvs_webrtc_create,
    .destroy = kvs_webrtc_destroy,
    .control = kvs_webrtc_control,
    .handle = kvs_webrtc_handle,

    .output_type = MM_TYPE_NONE,        // output for video sink
    .module_type = MM_TYPE_AVSINK,      // module type is video algorithm
    .name = "KVS_WebRTC"
};

#endif
