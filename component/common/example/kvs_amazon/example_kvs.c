#include "FreeRTOS.h"
#include "task.h"
#include <platform/platform_stdlib.h>
#include "basic_types.h"
#include "platform_opts.h"
#include "section_config.h"
#include <lwip_netconf.h>

#if CONFIG_EXAMPLE_KVS

#if CONFIG_FATFS_EN
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>


/* Config for Ameba-Pro */
#if defined(CONFIG_PLATFORM_8195BHP)
#define STACK_SIZE		20*1024
#if FATFS_DISK_SD

#include "sdio_combine.h"
#include "sdio_host.h"
#include <disk_if/inc/sdcard.h>
#include "fatfs_sdcard_api.h"
#endif

#endif // defined(CONFIG_PLATFORM_8195BHP)

/* Config for KVS example */
#include <com/amazonaws/kinesis/video/cproducer/Include.h>
#include "Samples.h"

#define DEFAULT_RETENTION_PERIOD            2 * HUNDREDS_OF_NANOS_IN_AN_HOUR
#define DEFAULT_BUFFER_DURATION             120 * HUNDREDS_OF_NANOS_IN_A_SECOND
#define DEFAULT_CALLBACK_CHAIN_COUNT        5
#define DEFAULT_KEY_FRAME_INTERVAL          45
//#define DEFAULT_FPS_VALUE                   25
#define DEFAULT_STREAM_DURATION             20 * HUNDREDS_OF_NANOS_IN_A_SECOND
#define DEFAULT_STORAGE_SIZE                20 * 1024 * 1024
#define RECORDED_FRAME_AVG_BITRATE_BIT_PS   3800000

#define NUMBER_OF_FRAME_FILES               403

#define FILE_LOGGING_BUFFER_SIZE            (100 * 1024)
#define MAX_NUMBER_OF_LOG_FILES             5
extern PSampleConfiguration gSampleConfiguration;
/* End of KVS config */

////
FRESULT list_files(char *);
FRESULT del_dir(const TCHAR *path, int del_self);  
FATFS 	fs_sd;
FIL     m_file;
#define TEST_BUF_SIZE	(512)
fatfs_sd_params_t fatfs_sd;
////

STATUS readFrameFromDisk(PBYTE pFrame, PUINT32 pSize, PCHAR frameFilePath)
{
    STATUS retStatus = STATUS_SUCCESS;
    UINT64 size = 0;

    if (pSize == NULL) {
        printf("[KVS Master] readFrameFromDisk(): operation returned status code: 0x%08x \n\r", STATUS_NULL_ARG);
        goto CleanUp;
    }

    size = *pSize;

    // Get the size and read into frame
    retStatus = readFile(frameFilePath, TRUE, pFrame, &size);
    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] readFile(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }

CleanUp:

    if (pSize != NULL) {
        *pSize = (UINT32) size;
    }

    return retStatus;
}

#undef ATOMIC_ADD
#include "video_common_api.h"
#include "h264_encoder.h"
#include "isp_api.h"
#include "h264_api.h"

#include "mmf2_dbg.h"
#include "sensor.h"


struct h264_to_sd_card_def_setting {
	uint32_t height;
	uint32_t width;
	H264_RC_MODE rcMode;
	uint32_t bitrate;
	uint32_t fps;
	uint32_t gopLen;
	uint32_t encode_frame_cnt;
	uint32_t output_buffer_size;
	uint8_t isp_stream_id;
	uint32_t isp_hw_slot;
	uint32_t isp_format;
	char fatfs_filename[64];
};

#define ISP_SW_BUF_NUM	4
#define FATFS_BUF_SIZE	(32*1024)

struct h264_to_sd_card_def_setting def_setting = {
	.height = VIDEO_1080P_HEIGHT,
	.width = VIDEO_1080P_WIDTH,
	.rcMode = H264_RC_MODE_CBR,
	.bitrate = 2*1024*1024,
	.fps = 30,
	.gopLen = 120,
	.encode_frame_cnt = 1500,
	.output_buffer_size = VIDEO_1080P_HEIGHT*VIDEO_1080P_WIDTH,
	.isp_stream_id = 0,
	.isp_hw_slot = 2,
	.isp_format = ISP_FORMAT_YUV420_SEMIPLANAR,
	.fatfs_filename = "h264_to_sdcard.h264",
};

typedef struct isp_s{
	isp_stream_t* stream;
	
	isp_cfg_t cfg;
	
	isp_buf_t buf_item[ISP_SW_BUF_NUM];
	xQueueHandle output_ready;
	xQueueHandle output_recycle;//!< the return buffer.
}isp_t;

/**
 * the callback of isp engine.
*/
void isp_frame_cb(void* p)
{
	BaseType_t xTaskWokenByReceive = pdFALSE;//!< true, a task is waiting for the available item of this queue.
	BaseType_t xHigherPriorityTaskWoken;//!< 
	
	isp_t* ctx = (isp_t*)p;
	isp_info_t* info = &ctx->stream->info;
	isp_cfg_t *cfg = &ctx->cfg;
	isp_buf_t buf;
	isp_buf_t queue_item;
	
	int is_output_ready = 0;
	
	u32 timestamp = xTaskGetTickCountFromISR();
	
	if(info->isp_overflow_flag == 0){
		/** get the available buffer. */
		is_output_ready = xQueueReceiveFromISR(ctx->output_recycle, &buf, &xTaskWokenByReceive) == pdTRUE;
	}else{
		/** this should be take care. */
		info->isp_overflow_flag = 0;
		ISP_DBG_ERROR("isp overflow = %d\r\n",cfg->isp_id);
	}
	
	if(is_output_ready){
		/** flush the isp to the available buffer. */
		isp_handle_buffer(ctx->stream, &buf, MODE_EXCHANGE);
		/** send it to the routine of h264 engine. */
		xQueueSendFromISR(ctx->output_ready, &buf, &xHigherPriorityTaskWoken);	
	}else{
		/** drop this frame buffer if there is no available buffer. */
		isp_handle_buffer(ctx->stream, NULL, MODE_SKIP);
	}
	if( xHigherPriorityTaskWoken || xTaskWokenByReceive)
		taskYIELD ();
}

PVOID sendVideoPackets(PVOID args)
{
    STATUS retStatus = STATUS_SUCCESS;
    PSampleConfiguration pSampleConfiguration = (PSampleConfiguration) args;
    RtcEncoderStats encoderStats;
    Frame frame;
    UINT32 fileIndex = 0, frameSize;
    CHAR filePath[MAX_PATH_LEN + 1];
    STATUS status;
    UINT32 i;
    //UINT64 startTime, lastFrameTime, elapsed;
    MEMSET(&encoderStats, 0x00, SIZEOF(RtcEncoderStats));


    int ret;
    isp_init_cfg_t isp_init_cfg;
	isp_t isp_ctx;

    if (pSampleConfiguration == NULL) {
        printf("[KVS Master] sendVideoPackets(): operation returned status code: 0x%08x \n\r", STATUS_NULL_ARG);
        goto CleanUp;
    }

    frame.presentationTs = 0;
    //startTime = GETTIME();
    //lastFrameTime = startTime;
    pSampleConfiguration->pVideoFrameBuffer = (PBYTE) MEMALLOC(32*1024);
    pSampleConfiguration->videoBufferSize = 32*1024;

    if (pSampleConfiguration->pVideoFrameBuffer == NULL) {
        printf("[KVS Master] Video frame Buffer reallocation failed...%s (code %d)\n\r", strerror(errno), errno);
        printf("[KVS Master] realloc(): operation returned status code: 0x%08x \n\r", STATUS_NOT_ENOUGH_MEMORY);
        goto CleanUp;
    }


	printf("[H264] init video related settings\n\r");
	// [4][H264] init video related settings
	/**
	 * setup the hardware of isp/h264
	*/
	memset(&isp_init_cfg, 0, sizeof(isp_init_cfg));
	isp_init_cfg.pin_idx = ISP_PIN_IDX;
	isp_init_cfg.clk = SENSOR_CLK_USE;
	isp_init_cfg.ldc = LDC_STATE;
	isp_init_cfg.fps = SENSOR_FPS;
	isp_init_cfg.isp_fw_location = ISP_FW_LOCATION;
	
	video_subsys_init(&isp_init_cfg);
#if 0
#if CONFIG_LIGHT_SENSOR
	init_sensor_service();
#else
	ir_cut_init(NULL);
	ir_cut_enable(1);
#endif
#endif
	/**
	 * setup the sw module of h264 engine.
	*/
	printf("[H264] create encoder\n\r");
	// [5][H264] create encoder
	struct h264_context* h264_ctx;
	ret = h264_create_encoder(&h264_ctx);
	if (ret != H264_OK) {
		printf("\n\rh264_create_encoder err %d\n\r",ret);
		//goto exit;
	}

	printf("[H264] get & set encoder parameters\n\r");
	// [6][H264] get & set encoder parameters
	struct h264_parameter h264_parm;
	ret = h264_get_parm(h264_ctx, &h264_parm);
	if (ret != H264_OK) {
		printf("\n\rh264_get_parmeter err %d\n\r",ret);
		//goto exit;
	}
	
	h264_parm.height = def_setting.height;
	h264_parm.width = def_setting.width;
	h264_parm.rcMode = def_setting.rcMode;
	h264_parm.bps = def_setting.bitrate;
	h264_parm.ratenum = def_setting.fps;
	h264_parm.gopLen = def_setting.gopLen;
	
	ret = h264_set_parm(h264_ctx, &h264_parm);
	if (ret != H264_OK) {
		printf("\n\rh264_set_parmeter err %d\n\r",ret);
		//goto exit;
	}
	
	printf("[H264] init encoder\n\r");
	// [7][H264] init encoder
	ret = h264_init_encoder(h264_ctx);
	if (ret != H264_OK) {
		printf("\n\rh264_init_encoder_buffer err %d\n\r",ret);
		//goto exit;
	}
	
	// [8][ISP] init ISP
	/**
	 * setup the sw module of isp engine.
	*/
	printf("[ISP] init ISP\n\r");
	memset(&isp_ctx,0,sizeof(isp_ctx));
	isp_ctx.output_ready = xQueueCreate(ISP_SW_BUF_NUM, sizeof(isp_buf_t));
	isp_ctx.output_recycle = xQueueCreate(ISP_SW_BUF_NUM, sizeof(isp_buf_t));
	
	isp_ctx.cfg.isp_id = def_setting.isp_stream_id;
	isp_ctx.cfg.format = def_setting.isp_format;
	isp_ctx.cfg.width = def_setting.width;
	isp_ctx.cfg.height = def_setting.height;
	isp_ctx.cfg.fps = def_setting.fps;
	isp_ctx.cfg.hw_slot_num = def_setting.isp_hw_slot;
	
	isp_ctx.stream = isp_stream_create(&isp_ctx.cfg);
	
	isp_stream_set_complete_callback(isp_ctx.stream, isp_frame_cb, (void*)&isp_ctx);
	
	for (int i=0; i<ISP_SW_BUF_NUM; i++ ) {
		/** sensor is at yuv420 mode. */
		unsigned char *ptr =(unsigned char *) malloc(def_setting.width*def_setting.height*3/2);
		if (ptr==NULL) {
			printf("[ISP] Allocate isp buffer[%d] failed\n\r",i);
			while(1);
		}
		isp_ctx.buf_item[i].slot_id = i;
		isp_ctx.buf_item[i].y_addr = (uint32_t) ptr;
		isp_ctx.buf_item[i].uv_addr = isp_ctx.buf_item[i].y_addr + def_setting.width*def_setting.height;
		/** looks like this isp has ping-pong buffers. */
		if (i<def_setting.isp_hw_slot) {
			// config hw slot
			//printf("\n\rconfig hw slot[%d] y=%x, uv=%x\n\r",i,isp_ctx.buf_item[i].y_addr,isp_ctx.buf_item[i].uv_addr);
			isp_handle_buffer(isp_ctx.stream, &isp_ctx.buf_item[i], MODE_SETUP);
		}
		/** backup buffer. */
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



    while (!ATOMIC_LOAD_BOOL(&pSampleConfiguration->appTerminateFlag)) {
		VIDEO_BUFFER video_buf;
		isp_buf_t isp_buf;
		// [9][ISP] get isp data
		/**
		 * get the isp buffe from the isr of isp engine.
		*/
		if(xQueueReceive(isp_ctx.output_ready, &isp_buf, 10) != pdTRUE) {
			continue;
		}
		
		// [10][H264] encode data
		/** allocate the output buffer of h264 engine. */
		video_buf.output_buffer_size = def_setting.output_buffer_size;
		video_buf.output_buffer = malloc(video_buf.output_buffer_size);
		if (video_buf.output_buffer== NULL) {
			printf("Allocate output buffer fail\n\r");
			continue;
		}
		/** trigger the h264 engine. */
		ret = h264_encode_frame(h264_ctx, &isp_buf, &video_buf);
		if (ret != H264_OK) {
			printf("\n\rh264_encode_frame err %d\n\r",ret);
			if (video_buf.output_buffer != NULL)
				free(video_buf.output_buffer);
			continue;
		}

		// [11][ISP] put back isp buffer
		/** return the isp buffer. */
		xQueueSend(isp_ctx.output_recycle, &isp_buf, 10);

        //fileIndex = fileIndex % NUMBER_OF_H264_FRAME_FILES + 1;
        //snprintf(filePath, MAX_PATH_LEN, "/h264SampleFrames/frame-%04d.h264", fileIndex);

        //retStatus = readFrameFromDisk(NULL, &frameSize, filePath);
        //if (retStatus != STATUS_SUCCESS) {
        //    printf("[KVS Master] readFrameFromDisk(): operation returned status code: 0x%08x \n\r", retStatus);
        //    goto CleanUp;
        //}

        // Re-alloc if needed
        //if (frameSize > pSampleConfiguration->videoBufferSize) {
        //    printf("[KVS Master] Video frame Buffer reallocation failed...overflow\n\r");
        //}

        frame.frameData = video_buf.output_buffer;
        frame.size = video_buf.output_size;
        //UINT64 fileSt = GETTIME();
        //retStatus = readFrameFromDisk(frame.frameData, &frameSize, filePath);
        //UINT64 fileEnd = GETTIME();
        //DLOGD("f: %llu", (fileEnd-fileSt)/HUNDREDS_OF_NANOS_IN_A_MILLISECOND);

        if (retStatus != STATUS_SUCCESS) {
            printf("[KVS Master] readFrameFromDisk(): operation returned status code: 0x%08x \n\r", retStatus);
            goto CleanUp;
        }

        // based on bitrate of samples/h264SampleFrames/frame-*
        encoderStats.width = 640;
        encoderStats.height = 480;
        encoderStats.targetBitrate = 262000;
        frame.presentationTs += SAMPLE_VIDEO_FRAME_DURATION;

        MUTEX_LOCK(pSampleConfiguration->streamingSessionListReadLock);
        for (i = 0; i < pSampleConfiguration->streamingSessionCount; ++i) {
            UINT64 frameSt = GETTIME();
            status = writeFrame(pSampleConfiguration->sampleStreamingSessionList[i]->pVideoRtcRtpTransceiver, &frame);
            UINT64 frameEnd = GETTIME();
            DLOGD("w:%llu", (frameEnd-frameSt)/HUNDREDS_OF_NANOS_IN_A_MILLISECOND);
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
        // Adjust sleep in the case the sleep itself and writeFrame take longer than expected. Since sleep makes sure that the thread
        // will be paused at least until the given amount, we can assume that there's no too early frame scenario.
        // Also, it's very unlikely to have a delay greater than SAMPLE_VIDEO_FRAME_DURATION, so the logic assumes that this is always
        // true for simplicity.
        //elapsed = lastFrameTime - startTime;
        //THREAD_SLEEP(SAMPLE_VIDEO_FRAME_DURATION - elapsed % SAMPLE_VIDEO_FRAME_DURATION);
        //lastFrameTime = GETTIME();
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

char *sample_channel_name = "My_KVS_Signaling_Channel";

void example_kvs_thread(void* param){

	FRESULT res; 

	char path[64];

	printf("=== KVS Example ===\n\r");

	res = fatfs_sd_init();
	if(res < 0){
		printf("fatfs_sd_init fail (%d)\n\r", res);
		goto fail;
	}
	fatfs_sd_get_param(&fatfs_sd);
	
    /** #YC_TBD, */
    vTaskDelay(3000);
    #include <sntp/sntp.h>
    sntp_init();
    vTaskDelay(3000);

    STATUS retStatus = STATUS_SUCCESS;
    UINT32 frameSize;
    PSampleConfiguration pSampleConfiguration = NULL;
    SignalingClientMetrics signalingClientMetrics;
    signalingClientMetrics.version = 0;

    // do trickleIce by default
    printf("[KVS Master] Using trickleICE by default\n\r");
    retStatus =
        createSampleConfiguration(sample_channel_name, SIGNALING_CHANNEL_ROLE_TYPE_MASTER, FALSE, FALSE, &pSampleConfiguration);

    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] createSampleConfiguration(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }
    printf("[KVS Master] Created signaling channel %s\n\r", sample_channel_name);

    if (pSampleConfiguration->enableFileLogging) {
        retStatus = createFileLogger(FILE_LOGGING_BUFFER_SIZE, MAX_NUMBER_OF_LOG_FILES, (PCHAR) FILE_LOGGER_LOG_FILE_DIRECTORY_PATH, TRUE, TRUE, NULL);
        if (retStatus != STATUS_SUCCESS) {
            printf("[KVS Master] createFileLogger(): operation returned status code: 0x%08x \n\r", retStatus);
            pSampleConfiguration->enableFileLogging = FALSE;
        }
    }
    
    // Set the video handlers
    pSampleConfiguration->videoSource = sendVideoPackets;
    pSampleConfiguration->mediaType = SAMPLE_STREAMING_VIDEO_ONLY;
    
    printf("[KVS Master] Finished setting audio and video handlers\n\r");


    snprintf(path, sizeof(path), "%s%s", fatfs_sd.drv, "/h264SampleFrames/frame-0001.h264");
    printf("The video file path: %s \n\r", path);

    retStatus = readFrameFromDisk(NULL, &frameSize, path);
    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] readFrameFromDisk(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }
    printf("[KVS Master] Checked sample video frame availability....available\n\r");
        
    // Initialize KVS WebRTC. This must be done before anything else, and must only be done once.

    retStatus = initKvsWebRtc();
    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] initKvsWebRtc(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }
    printf("[KVS Master] KVS WebRTC initialization completed successfully\n\r");
    
    pSampleConfiguration->signalingClientCallbacks.messageReceivedFn = signalingMessageReceived;

    strcpy(pSampleConfiguration->clientInfo.clientId, SAMPLE_MASTER_CLIENT_ID);

    retStatus = createSignalingClientSync(&pSampleConfiguration->clientInfo, &pSampleConfiguration->channelInfo,
                                            &pSampleConfiguration->signalingClientCallbacks, pSampleConfiguration->pCredentialProvider,
                                            &pSampleConfiguration->signalingClientHandle);
    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] createSignalingClientSync(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }
    printf("[KVS Master] Signaling client created successfully\n\r");

    // Enable the processing of the messages
    retStatus = signalingClientConnectSync(pSampleConfiguration->signalingClientHandle);
    if (retStatus != STATUS_SUCCESS) {
        printf("[KVS Master] signalingClientConnectSync(): operation returned status code: 0x%08x \n\r", retStatus);
        goto CleanUp;
    }
    printf("[KVS Master] Signaling client connection to socket established\n\r");

    gSampleConfiguration = pSampleConfiguration;

    printf("[KVS Master] Channel %s set up done \n\r", sample_channel_name);

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
        if (pSampleConfiguration->videoSenderTid != (UINT64) NULL) {
            // Join the threads
            THREAD_JOIN(pSampleConfiguration->videoSenderTid, NULL);
        }

        if (pSampleConfiguration->audioSenderTid != (UINT64) NULL) {
            // Join the threads
            THREAD_JOIN(pSampleConfiguration->audioSenderTid, NULL);
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
        retStatus = freeSignalingClient(&pSampleConfiguration->signalingClientHandle);
        if (retStatus != STATUS_SUCCESS) {
            printf("[KVS Master] freeSignalingClient(): operation returned status code: 0x%08x", retStatus);
        }

        retStatus = freeSampleConfiguration(&pSampleConfiguration);
        if (retStatus != STATUS_SUCCESS) {
            printf("[KVS Master] freeSampleConfiguration(): operation returned status code: 0x%08x", retStatus);
        }
    }
    printf("[KVS Master] Cleanup done\n\r");

        
//////////////////////////////////////////////
	

fail:
	fatfs_sd_close();

exit:
	vTaskDelete(NULL);
}



char *print_file_info(FILINFO fileinfo, char *fn, char* path)
{
	char info[256];
	char fname[64];
	memset(fname, 0, sizeof(fname));
	snprintf(fname, sizeof(fname), "%s", fn);	
	
	snprintf(info, sizeof(info), 
		"%c%c%c%c%c  %u/%02u/%02u  %02u:%02u  %9llu  %30s  %30s", 
		(fileinfo.fattrib & AM_DIR) ? 'D' : '-',
		(fileinfo.fattrib & AM_RDO) ? 'R' : '-',
		(fileinfo.fattrib & AM_HID) ? 'H' : '-',
		(fileinfo.fattrib & AM_SYS) ? 'S' : '-',
		(fileinfo.fattrib & AM_ARC) ? 'A' : '-',
		(fileinfo.fdate >> 9) + 1980,
		(fileinfo.fdate >> 5) & 15,
		fileinfo.fdate & 31,
		(fileinfo.ftime >> 11),
		(fileinfo.ftime >> 5) & 63,
		fileinfo.fsize,
		fn,
		path);
	printf("%s\n\r", info);
	return info;
}

FRESULT list_files(char* list_path)
{
	DIR m_dir;
	FILINFO m_fileinfo;
	FRESULT res;
	char *filename;
#if _USE_LFN
	char fname_lfn[_MAX_LFN + 1];
	m_fileinfo.lfname = fname_lfn;
	m_fileinfo.lfsize = sizeof(fname_lfn);
#endif
	char cur_path[64];
	//strcpy(cur_path, list_path);

	// open directory
	res = f_opendir(&m_dir, list_path);

	if(res == FR_OK)
	{
		for (;;) {
			strcpy(cur_path, list_path);
			// read directory and store it in file info object
			res = f_readdir(&m_dir, &m_fileinfo);
			if (res != FR_OK || m_fileinfo.fname[0] == 0) {
				break;
			}

#if _USE_LFN
			filename = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
			filename = m_fileinfo.fname;
#endif
			if (*filename == '.' || *filename == '..') 
			{
				continue;
			}

			// check if the object is directory
			if(m_fileinfo.fattrib & AM_DIR)
			{
				sprintf(&cur_path[strlen(list_path)], "/%s", filename);
				print_file_info(m_fileinfo, filename, cur_path);
				res = list_files(cur_path);
				//strcpy(list_path, cur_path);
				if (res != FR_OK) 
				{
					break;
				}
				//list_path[strlen(list_path)] = 0;
			}
			else {
				print_file_info(m_fileinfo, filename, cur_path);
			}

		}
	}

	// close directory
	res = f_closedir(&m_dir);
	if(res){
		printf("close directory fail: %d\n\r", res);
	}
	return res;
}

FRESULT del_dir(const TCHAR *path, int del_self)  
{  
    FRESULT res;  
    DIR   m_dir;    
    FILINFO m_fileinfo;     
	char *filename;
    char file[_MAX_LFN + 1];  
#if _USE_LFN
		char fname_lfn[_MAX_LFN + 1];
		m_fileinfo.lfname = fname_lfn;
		m_fileinfo.lfsize = sizeof(fname_lfn);
#endif

    res = f_opendir(&m_dir, path);  

	if(res == FR_OK) {
		for (;;) {
			// read directory and store it in file info object
			res = f_readdir(&m_dir, &m_fileinfo);
			if (res != FR_OK || m_fileinfo.fname[0] == 0) {
				break;
			}

#if _USE_LFN
			filename = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
			filename = m_fileinfo.fname;
#endif
			if (*filename == '.' || *filename == '..') 
			{
				continue;
			}

			printf("del: %s\n\r", filename);
			sprintf((char*)file, "%s/%s", path, filename);  

			if (m_fileinfo.fattrib & AM_DIR) {  
            	res = del_dir(file, 1);  
        	}  
        	else { 
            	res = f_unlink(file);  
        	}  	

		}

	}
	
    // close directory
	res = f_closedir(&m_dir);

	// delete self? 
    if(res == FR_OK) {
		if(del_self == 1)
			res = f_unlink(path);  
    }

	return res;  
}  


#include <sntp/sntp.h>

void example_kvs(void)
{
    
    //if(xTaskCreate(example_kvs_thread, ((const char*)"example_kvs_thread"), STACK_SIZE, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
	if(xTaskCreate(example_kvs_thread, ((const char*)"example_kvs_thread"), STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_kvs_thread) failed", __FUNCTION__);
}
#endif
#endif /* CONFIG_EXAMPLE_FATFS */
