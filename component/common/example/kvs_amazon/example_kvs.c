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
#define STACK_SIZE		20*1024 //4096
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
    UINT64 startTime, lastFrameTime, elapsed;
    MEMSET(&encoderStats, 0x00, SIZEOF(RtcEncoderStats));

    if (pSampleConfiguration == NULL) {
        printf("[KVS Master] sendVideoPackets(): operation returned status code: 0x%08x \n\r", STATUS_NULL_ARG);
        goto CleanUp;
    }

    frame.presentationTs = 0;
    startTime = GETTIME();
    lastFrameTime = startTime;
    pSampleConfiguration->pVideoFrameBuffer = (PBYTE) MEMALLOC(7*1024);
    pSampleConfiguration->videoBufferSize = 7*1024;

    if (pSampleConfiguration->pVideoFrameBuffer == NULL) {
        printf("[KVS Master] Video frame Buffer reallocation failed...%s (code %d)\n\r", strerror(errno), errno);
        printf("[KVS Master] realloc(): operation returned status code: 0x%08x \n\r", STATUS_NOT_ENOUGH_MEMORY);
        goto CleanUp;
    }

    while (!ATOMIC_LOAD_BOOL(&pSampleConfiguration->appTerminateFlag)) {
        fileIndex = fileIndex % NUMBER_OF_H264_FRAME_FILES + 1;
        snprintf(filePath, MAX_PATH_LEN, "/sdcard/h264SampleFrames/frame-%04d.h264", fileIndex);

        retStatus = readFrameFromDisk(NULL, &frameSize, filePath);
        if (retStatus != STATUS_SUCCESS) {
            printf("[KVS Master] readFrameFromDisk(): operation returned status code: 0x%08x \n\r", retStatus);
            goto CleanUp;
        }

        // Re-alloc if needed
        if (frameSize > pSampleConfiguration->videoBufferSize) {
            printf("[KVS Master] Video frame Buffer reallocation failed...overflow\n\r");
        }

        frame.frameData = pSampleConfiguration->pVideoFrameBuffer;
        frame.size = frameSize;

        retStatus = readFrameFromDisk(frame.frameData, &frameSize, filePath);
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

        // Adjust sleep in the case the sleep itself and writeFrame take longer than expected. Since sleep makes sure that the thread
        // will be paused at least until the given amount, we can assume that there's no too early frame scenario.
        // Also, it's very unlikely to have a delay greater than SAMPLE_VIDEO_FRAME_DURATION, so the logic assumes that this is always
        // true for simplicity.
        elapsed = lastFrameTime - startTime;
        THREAD_SLEEP(SAMPLE_VIDEO_FRAME_DURATION - elapsed % SAMPLE_VIDEO_FRAME_DURATION);
        lastFrameTime = GETTIME();
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

void example_kvs_thread(void* param){

	FRESULT res; 

	char path[64];

	// Delay to wait for IP by DHCP
	vTaskDelay(3000);
	printf("\n\r");
	printf("=== KVS Example sntp_init ===\n\r");
	sntp_init();
	
	// Delay to wait set time
	vTaskDelay(1000);
        
	printf("=== KVS Example ===\n\r");

	res = fatfs_sd_init();
	if(res < 0){
		printf("fatfs_sd_init fail (%d)\n\r", res);
		goto fail;
	}
	fatfs_sd_get_param(&fatfs_sd);


	//printf("\n\r=== Clear files ===\n\r");
	//del_dir(fatfs_sd.drv, 0);
	
	// path of the file
	//snprintf(path, sizeof(path), "%s%s", fatfs_sd.drv, sd_fn);
	
	// list the files
	printf("List files in SD card: %s\n\r", fatfs_sd.drv);
	res = list_files(fatfs_sd.drv);
	if(res){
		printf("list all files in SD card fail (%d)\n\r", res);
	}
	printf("\n\r");
	
	
/////////////////////////////////////////////////////////////////////////////

        //// test some function in esp32 demo
        //// INT32 kvsWebRTCClientMaster(void)
        STATUS retStatus = STATUS_SUCCESS;
        UINT32 frameSize;
        PSampleConfiguration pSampleConfiguration = NULL;
        SignalingClientMetrics signalingClientMetrics;
        signalingClientMetrics.version = 0;
        
#define SAMPLE_CHANNEL_NAME "My_KVS_Signaling_Channel"
        //char *sample_chennel_name = "My_KVS_Signaling_Channel";
        
        // do trickleIce by default
        printf("[KVS Master] Using trickleICE by default\n\r");
        retStatus =
            createSampleConfiguration(SAMPLE_CHANNEL_NAME, SIGNALING_CHANNEL_ROLE_TYPE_MASTER, FALSE, FALSE, &pSampleConfiguration); // TRUE, TRUE
        if (retStatus != STATUS_SUCCESS) {
            printf("[KVS Master] createSampleConfiguration(): operation returned status code: 0x%08x \n\r", retStatus);
            goto CleanUp;
        }
        printf("[KVS Master] Created signaling channel %s\n\r", SAMPLE_CHANNEL_NAME);

        if (pSampleConfiguration->enableFileLogging) {
            retStatus = createFileLogger(FILE_LOGGING_BUFFER_SIZE, MAX_NUMBER_OF_LOG_FILES, (PCHAR) FILE_LOGGER_LOG_FILE_DIRECTORY_PATH, TRUE, TRUE, NULL);
            if (retStatus != STATUS_SUCCESS) {
                printf("[KVS Master] createFileLogger(): operation returned status code: 0x%08x \n\r", retStatus);
                pSampleConfiguration->enableFileLogging = FALSE;
            }
        }
        printf("Create File Logger successfully. \n\r");
        
        // Set the video handlers
        pSampleConfiguration->videoSource = sendVideoPackets;
        pSampleConfiguration->mediaType = SAMPLE_STREAMING_VIDEO_ONLY;
        
        printf("[KVS Master] Finished setting audio and video handlers\n\r");
        
        // Check if the samples are present, #YC_TBD, move to another place, or remove it.
        #if 1
        //retStatus = readFrameFromDisk(NULL, &frameSize, "/sdcard/h264SampleFrames/frame-0001.h264");
        snprintf(path, sizeof(path), "%s%s", fatfs_sd.drv, "/h264SampleFrames/frame-0001.h264");
        printf("The video file path: %s \n\r", path);
        retStatus = readFrameFromDisk(NULL, &frameSize, path);
        if (retStatus != STATUS_SUCCESS) {
            printf("[KVS Master] readFrameFromDisk(): operation returned status code: 0x%08x \n\r", retStatus);
            goto CleanUp;
        }
        printf("[KVS Master] Checked sample video frame availability....available\n\r");
        #endif
     
        
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

        printf("[KVS Master] Channel %s set up done \n\r", "SAMPLE_CHANNEL_NAME");

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

void example_kvs(void)
{
	if(xTaskCreate(example_kvs_thread, ((const char*)"example_kvs_thread"), STACK_SIZE, NULL, tskIDLE_PRIORITY + 2, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_kvs_thread) failed", __FUNCTION__);
}
#endif
#endif /* CONFIG_EXAMPLE_FATFS */
