#include <platform_opts.h>
#if CONFIG_EXAMPLE_MEDIA_UVCH	        

#include "example_usbh_uvc.h"
#include "uvcvideo.h"
#include "uvc_intf.h"
#include "section_config.h"
#include "module_h264.h"

#ifndef UNUSED
#define UNUSED(x) ((void)(x))
#endif

// USBH UVC configurations
// Use EVB as HTTP(s) server to allow HTTP(s) clients to GET UVC image captured from the camera
#define USBH_UVC_APP_HTTPD               0
// Use EVB as HTTP(s) client to PUT UVC image captured from the camera to HTTP(s) server
#define USBH_UVC_APP_HTTPC               1
// Capture UVC images from the camera and save as jpeg files into SD card
#define USBH_UVC_APP_FATFS               2
// Use MMF with UVC as video source and RTSP as sink
#define USBH_UVC_APP_MMF_RTSP            3

#define CONFIG_USBH_UVC_APP              USBH_UVC_APP_MMF_RTSP

// Use EVB as HTTPS client to POST UVC image captured from the camera to HTTPS server
#define CONFIG_USBH_UVC_USE_HTTPS        0

// Check whether the captured image data is valid before futher process
#define CONFIG_USBH_UVC_CHECK_IMAGE_DATA 0

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_HTTPD)
#include "lwip/sockets.h"
#include <httpd/httpd.h>
#if CONFIG_USBH_UVC_USE_HTTPS
#if (HTTPD_USE_TLS == HTTPD_TLS_POLARSSL)
#include <polarssl/certs.h>
#elif (HTTPD_USE_TLS == HTTPD_TLS_MBEDTLS)
#include <mbedtls/certs.h>
#endif
#endif
#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_HTTPC)
#include <httpc/httpc.h>
#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_FATFS)
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>
#include <disk_if/inc/sdcard.h>
#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_MMF_RTSP)
#include "mmf2.h"
#include "mmf2_dbg.h"
#include "module_uvch.h"
#include "module_rtsp2.h"
#endif


#if 0

#define USBH_UVC_BUF_SIZE       (81920*5)
#define USBH_UVC_FORMAT_TYPE    UVC_FORMAT_MJPEG
#define USBH_UVC_WIDTH          1280
#define USBH_UVC_HEIGHT         720
#define USBH_UVC_FRAME_RATE     15

#if (USBH_UVC_FORMAT_TYPE != UVC_FORMAT_MJPEG)
#error "USBH UVC unsupported format, only MJPEG is supported"
#endif

#else


#define USBH_UVC_FORMAT_TYPE    UVC_FORMAT_YUY2
#define USBH_UVC_WIDTH          320
#define USBH_UVC_HEIGHT         320
#define USBH_UVC_BUF_SIZE       (USBH_UVC_WIDTH*USBH_UVC_HEIGHT*2)
#define USBH_UVC_FRAME_RATE     15

#if (USBH_UVC_FORMAT_TYPE != UVC_FORMAT_YUY2)
#error "USBH UVC unsupported format, only YUY2 is supported"
#endif

#endif

#define V1_H264_QUEUE_LEN			70

#define USBH_UVC_JFIF_TAG       0xFF
#define USBH_UVC_JFIF_SOI       0xD8
#define USBH_UVC_JFIF_EOI       0xD9

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_HTTPD)
#define USBH_UVC_HTTPD_TX_SIZE  4000
#if (CONFIG_USBH_UVC_USE_HTTPS == 0)
#define USBH_UVC_HTTPD_SECURE   HTTPD_SECURE_NONE
#define USBH_UVC_HTTPD_PORT     80
#else // (CONFIG_USBH_UVC_USE_HTTPS == 1)
#define USBH_UVC_HTTPD_SECURE   HTTPD_SECURE_TLS
#define USBH_UVC_HTTPD_PORT     443
#endif
#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_HTTPC)
#define USBH_UVC_HTTPC_TX_SIZE  4000
#define USBH_UVC_HTTPC_SERVER   "192.168.1.100"
#if (CONFIG_USBH_UVC_USE_HTTPS == 0)
#define USBH_UVC_HTTPC_SECURE   HTTPC_SECURE_NONE
#define USBH_UVC_HTTPC_PORT     80
#else // (CONFIG_USBH_UVC_USE_HTTPS == 1)
#define USBH_UVC_HTTPC_SECURE   HTTPC_SECURE_TLS
#define USBH_UVC_HTTPC_PORT     443
#endif
#endif

#if (CONFIG_USBH_UVC_USE_HTTPS == 0)
#define USBH_UVC_HTTP_TAG       "HTTP"
#else
#define USBH_UVC_HTTP_TAG       "HTTPS"
#endif

#if (CONFIG_USBH_UVC_APP != USBH_UVC_APP_MMF_RTSP)
static _mutex uvc_buf_mutex = NULL;
PSRAM_BSS_SECTION u8 uvc_buf[USBH_UVC_BUF_SIZE];
static int uvc_buf_size = 0;
#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_HTTPC)
static _sema uvc_httpc_save_img_sema = NULL;
static int uvc_httpc_img_file_no = 0;
#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_FATFS)
static _sema uvc_fatfs_save_img_sema = NULL;
static int uvc_fatfs_is_init = 0;
static int uvc_fatfs_img_file_no = 0;
#endif

#if (CONFIG_USBH_UVC_APP != USBH_UVC_APP_MMF_RTSP)

static void uvc_img_prepare(struct uvc_buf_context *buf)
{
    u32 len = 0;
    u32 start = 0;

    if (buf != NULL) {
#if ((CONFIG_USBH_UVC_CHECK_IMAGE_DATA == 1) && (USBH_UVC_FORMAT_TYPE == UVC_FORMAT_MJPEG))
        u8 *ptr = (u8 *)buf->data;
        u32 end = 0;
        u32 i = 0;

        // Check mjpeg image data
        // Normally, the mjpeg image data shall start with SOI and end with EOI
        while (i < buf->len - 1) {
            if ((*ptr == USBH_UVC_JFIF_TAG) && (*(ptr + 1) == USBH_UVC_JFIF_SOI)) { // Check SOI
                start = i;
                ptr += 2;
                i += 2;
            } else if ((*ptr == USBH_UVC_JFIF_TAG) && (*(ptr + 1) == USBH_UVC_JFIF_EOI)) { // Check EOI
                end = i + 1;
                break;
            } else {
                ptr += 1;
                i += 1;
            }
        }

        if (end <= start) {
            printf("\nInvalid uvc data, len=%d, start with %02X %02X\n", buf->len, buf->data[0], buf->data[1]);
            return;
        }

        len = end - start;

        if (len == buf->len) {
            printf("\nCapture uvc data, len=%d\n", len);
        } else {
            printf("\nCapture uvc data, len=%d, start=%d, end=%d\n", len, start, end);
        }

#else
        len = buf->len;
#endif
        rtw_mutex_get(&uvc_buf_mutex);
        rtw_memcpy(uvc_buf, (void *)(buf->data + start), len);
        uvc_buf_size = len;
        rtw_mutex_put(&uvc_buf_mutex);

        if (uvc_buf_size > 0) {
#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_FATFS)
            if (uvc_fatfs_is_init) {
                rtw_up_sema(&uvc_fatfs_save_img_sema);
            }
#endif
#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_HTTPC)
            rtw_up_sema(&uvc_httpc_save_img_sema);
#endif
        }
    }
}

#endif // (CONFIG_USBH_UVC_APP != USBH_UVC_APP_MMF_RTSP)

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_HTTPD)

static void uvc_httpd_img_get_cb(struct httpd_conn *conn)
{
    u32 send_offset = 0;
    int left_size;
    int ret;
    
    httpd_conn_dump_header(conn);
    
    // GET img page
    ret = httpd_request_is_method(conn, "GET");
    if (ret) {
        rtw_mutex_get(&uvc_buf_mutex);
        left_size = uvc_buf_size;
        httpd_response_write_header_start(conn, "200 OK", "image/jpeg", uvc_buf_size);
        httpd_response_write_header(conn, "connection", "close");
        httpd_response_write_header_finish(conn);

        while (left_size > 0) {
            if (left_size > USBH_UVC_HTTPD_TX_SIZE) {
                ret = httpd_response_write_data(conn, uvc_buf + send_offset, USBH_UVC_HTTPD_TX_SIZE);
                if (ret < 0) {
                    printf("\nFail to send %s response: %d\n", USBH_UVC_HTTP_TAG, ret);
                    break;
                }

                send_offset += USBH_UVC_HTTPD_TX_SIZE;
                left_size -= USBH_UVC_HTTPD_TX_SIZE;
            } else {
                ret = httpd_response_write_data(conn, uvc_buf + send_offset, left_size);
                if (ret < 0) {
                    printf("\nFail to send %s response: %d\n", USBH_UVC_HTTP_TAG, ret);
                    break;
                }

                printf("\nUVC image sent, %d bytes\n", uvc_buf_size);
                left_size = 0;
            }

            rtw_mdelay_os(1);
        }

        rtw_mutex_put(&uvc_buf_mutex);
    } else {
        httpd_response_method_not_allowed(conn, NULL);
    }

    httpd_conn_close(conn);
}

static int uvc_httpd_start(void)
{
    int ret;
    
#if CONFIG_USBH_UVC_USE_HTTPS
#if (HTTPD_USE_TLS == HTTPD_TLS_POLARSSL)
    ret = httpd_setup_cert(test_srv_crt, test_srv_key, test_ca_crt);
#elif (HTTPD_USE_TLS == HTTPD_TLS_MBEDTLS)
    ret = httpd_setup_cert(mbedtls_test_srv_crt, mbedtls_test_srv_key, mbedtls_test_ca_crt);
#endif
    if (ret != 0) {
        printf("\nFail to setup %s server cert\n", USBH_UVC_HTTP_TAG);
        return ret;
    }

#endif
    httpd_reg_page_callback("/", uvc_httpd_img_get_cb);
    ret = httpd_start(USBH_UVC_HTTPD_PORT, 1, 4096, HTTPD_THREAD_SINGLE, USBH_UVC_HTTPD_SECURE);
    if (ret != 0) {
        printf("\nFail to start %s server: %d\n", USBH_UVC_HTTP_TAG, ret);
        httpd_clear_page_callbacks();
    }

    return ret;
}

#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_HTTPC)

static void uvc_httpc_thread(void *param)
{
    u32 send_offset;
    int left_size;
    int ret;
    char img_file[32];
    struct httpc_conn *conn = NULL;
    
    UNUSED(param);
    
    rtw_mdelay_os(3000); // Wait for network ready

    while (1) {
        rtw_down_sema(&uvc_httpc_save_img_sema);
        conn = httpc_conn_new(USBH_UVC_HTTPC_SECURE, NULL, NULL, NULL);
        if (conn) {
            ret = httpc_conn_connect(conn, USBH_UVC_HTTPC_SERVER, USBH_UVC_HTTPC_PORT, 0);
            if (ret == 0) {
                rtw_mutex_get(&uvc_buf_mutex);
                sprintf(img_file, "/uploads/img%d.jpeg", uvc_httpc_img_file_no);
                // start a header and add Host (added automatically), Content-Type and Content-Length (added by input param)
                httpc_request_write_header_start(conn, "PUT", img_file, NULL, uvc_buf_size);
                // add other header fields if necessary
                httpc_request_write_header(conn, "Connection", "close");
                // finish and send header
                httpc_request_write_header_finish(conn);
                send_offset = 0;
                left_size = uvc_buf_size;

                // send http body
                while (left_size > 0) {
                    if (left_size > USBH_UVC_HTTPC_TX_SIZE) {
                        ret = httpc_request_write_data(conn, uvc_buf + send_offset, USBH_UVC_HTTPC_TX_SIZE);
                        if (ret < 0) {
                            printf("\nFail to send %s request: %d\n", USBH_UVC_HTTP_TAG, ret);
                            break;
                        }

                        send_offset += USBH_UVC_HTTPC_TX_SIZE;
                        left_size -= USBH_UVC_HTTPC_TX_SIZE;
                    } else {
                        ret = httpc_request_write_data(conn, uvc_buf + send_offset, left_size);
                        if (ret < 0) {
                            printf("\nFail to send %s request: %d\n", USBH_UVC_HTTP_TAG, ret);
                            break;
                        }

                        printf("\nUVC image img%d.jpeg sent, %d bytes\n", uvc_httpc_img_file_no, uvc_buf_size);
                        left_size = 0;
                    }

                    rtw_mdelay_os(1);
                }

                rtw_mutex_put(&uvc_buf_mutex);
                // receive response header
                ret = httpc_response_read_header(conn);
                if (ret == 0) {
                    httpc_conn_dump_header(conn);
                    // receive response body
                    ret = httpc_response_is_status(conn, "200 OK");
                    if (ret) {
                        uint8_t buf[1024];
                        int read_size = 0;
                        uint32_t total_size = 0;

                        while (1) {
                            rtw_memset(buf, 0, sizeof(buf));
                            read_size = httpc_response_read_data(conn, buf, sizeof(buf) - 1);
                            if (read_size > 0) {
                                total_size += read_size;
                                printf("\n%s\n", buf);
                            } else {
                                break;
                            }

                            if (conn->response.content_len && (total_size >= conn->response.content_len)) {
                                break;
                            }
                        }
                    }
                }

                uvc_httpc_img_file_no++;
            } else {
                printf("\nFail to connect to %s server\n", USBH_UVC_HTTP_TAG);
            }

            httpc_conn_close(conn);
            httpc_conn_free(conn);
        }
    }

    rtw_thread_exit();
}

static int uvc_httpc_start(void)
{
    int ret = 0;
    struct task_struct task;
    
    rtw_init_sema(&uvc_httpc_save_img_sema, 0);
    
    ret = rtw_create_task(&task, "uvc_httpc_thread", 2048, tskIDLE_PRIORITY + 2, uvc_httpc_thread, NULL);
    if (ret != pdPASS) {
        printf("\n%Fail to create USB host UVC %s client thread\n", USBH_UVC_HTTP_TAG);
        rtw_free_sema(&uvc_httpc_save_img_sema);
        ret = 1;
    } else {
        ret = 0;
    }

    return ret;
}

#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_FATFS)

#include "ff.h"
    FATFS m_fs;
    FIL m_file;
#include "sdio_combine.h"
#include "sdio_host.h"
#include <disk_if/inc/sdcard.h>
#include "fatfs_sdcard_api.h"
fatfs_sd_params_t fatfs_sd;
static void uvc_fatfs_thread(void *param)
{
	int drv_num = 0;
    int Fatfs_ok = 1;
    FRESULT res;
    char logical_drv[4];
    char f_num[15];
    char filename[64] = {0};
    char path[64];
    int bw;
    int ret;
    
    UNUSED(param);
    
    // Register disk driver to fatfs
	res = fatfs_sd_init();
	if(res < 0){
		printf("fatfs_sd_init fail (%d)\n", res);
		Fatfs_ok = 0;
		goto fail;
	}
	fatfs_sd_get_param(&fatfs_sd);
	
    // Save image file to disk
    if (Fatfs_ok) {

        rtw_init_sema(&uvc_fatfs_save_img_sema, 0);
        uvc_fatfs_is_init = 1;

        while (uvc_fatfs_is_init) {
            rtw_down_sema(&uvc_fatfs_save_img_sema);
            
            memset(filename, 0, 64);
            sprintf(filename, "img");
            sprintf(f_num, "%d", uvc_fatfs_img_file_no);
            strcat(filename, f_num);
            strcat(filename, ".jpg");
            strcpy(path, logical_drv);
            sprintf(&path[strlen(path)], "%s", filename);
            
            res = f_open(&m_file, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
            if (res) {
                printf("\nFail to open file (%s): %d\n", filename, res);
                continue;
            }

            printf("\nCreate image file: %s\n", filename);

            if ((&m_file)->fsize > 0) {
                res = f_lseek(&m_file, 0);
                if (res) {
                    f_close(&m_file);
                    printf("\nFail to seek file: %d\n", res);
                    goto out;
                }
            }

            rtw_mutex_get(&uvc_buf_mutex);

            do {
                res = f_write(&m_file, uvc_buf, uvc_buf_size, (u32 *)&bw);
                if (res) {
                    f_lseek(&m_file, 0);
                    printf("\nFail to write file: %d\n", res);
                    break;
                }

                printf("\nWrite %d bytes\n", bw);
            } while (bw < uvc_buf_size);

            rtw_mutex_put(&uvc_buf_mutex);
            
            res = f_close(&m_file);
            if (res) {
                printf("\nFail to close file (%s): d\n", filename, res);
            }

            uvc_fatfs_img_file_no++;
        }

out:
        rtw_free_sema(&uvc_fatfs_save_img_sema);
        
        res = f_mount(NULL, logical_drv, 1);
        if (res != FR_OK) {
            printf("\nFail to unmount logical drive: %d\n", res);
        }

        ret = FATFS_UnRegisterDiskDriver(drv_num);
        if (ret) {
            printf("\nFail to unregister disk driver from FATFS: %d\n", ret);
        }
    }

fail:
    rtw_thread_exit();
}

static int uvc_fatfs_start(void)
{
    int ret;
    struct task_struct task;
    
    ret = rtw_create_task(&task, "uvc_fatfs_thread", 1024, tskIDLE_PRIORITY + 2, uvc_fatfs_thread, NULL);
    if (ret != pdPASS) {
        printf("\n%Fail to create USB host UVC fatfs thread\n");
        ret = 1;
    } else {
        ret = 0;
    }

    return ret;
}

#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_MMF_RTSP)


#define BLOCK_SIZE						1024*10
#define FRAME_SIZE						(USBH_UVC_WIDTH*USBH_UVC_HEIGHT/2)
#define BUFFER_SIZE						(FRAME_SIZE*3)
static uvc_parameter_t uvc_params = {
    .fmt_type          = USBH_UVC_FORMAT_TYPE,
    .width             = USBH_UVC_WIDTH,
    .height            = USBH_UVC_HEIGHT,
    .frame_rate        = USBH_UVC_FRAME_RATE,
    .compression_ratio = 0,
    .frame_buf_size    = USBH_UVC_BUF_SIZE,
    .ext_frame_buf     = 1
};
h264_params_t h264_params_ = {
	.width          = USBH_UVC_WIDTH,
	.height         = USBH_UVC_HEIGHT,
	.bps            = 2*1024*1024,
	.fps            = USBH_UVC_FRAME_RATE,
	.gop            = USBH_UVC_FRAME_RATE,
	.rc_mode        = RC_MODE_H264CBR,
	.mem_total_size = BUFFER_SIZE,
	.mem_block_size = BLOCK_SIZE,
	.mem_frame_size = FRAME_SIZE,
	.input_type     = ISP_FORMAT_YUY2_INTERLEAVED
};
//h264_params_t h264_params_ = {
//	.width          = 1280,
//	.height         = 720,
//	.bps            = 2*1024*1024,
//	.fps            = 30,
//	.gop            = 30,
//	.rc_mode        = RC_MODE_H264CBR,
//	.mem_total_size = 1280*720/2 + 5*1024*1024/2,
//	.mem_block_size = 1024*10,
//	.mem_frame_size = 1280*720/2
//};

static rtsp2_params_t rtsp2_params = {
    .type = AVMEDIA_TYPE_VIDEO,
    .u = {
        .v = {
            .codec_id = AV_CODEC_ID_H264,
            .fps      = USBH_UVC_FRAME_RATE,
        }
    }
};

static void example_usbh_uvc_task_ori(void *param)
{
    int ret = 0;
    UNUSED(param);
    mm_context_t *uvch_ctx = NULL;
    mm_context_t *rtsp_ctx = NULL;
    mm_siso_t *uvc_to_rstp_siso = NULL;
    
    rtw_mdelay_os(3000); // Wait for network ready


	
    printf("\nOpen MMF UVCH module\n");
 
    uvch_ctx = mm_module_open(&uvch_module);
    if (uvch_ctx != NULL) {
        mm_module_ctrl(uvch_ctx, MM_CMD_SET_QUEUE_LEN, 1);
        mm_module_ctrl(uvch_ctx, MM_CMD_UVCH_SET_PARAMS, (int)&uvc_params);
        mm_module_ctrl(uvch_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(uvch_ctx, MM_CMD_UVCH_APPLY, 0);
        mm_module_ctrl(uvch_ctx, MM_CMD_UVCH_SET_STREAMING, ON);
    } else {
        printf("\nFail to open MMF UVCH module\n");
        return;
    }

	
	
	
    printf("\nOpen MMF RTSP module\n");
    
    rtsp_ctx = mm_module_open(&rtsp2_module);
    if (rtsp_ctx != NULL) {
        mm_module_ctrl(rtsp_ctx, CMD_RTSP2_SELECT_STREAM, 0);
        mm_module_ctrl(rtsp_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_params);
        mm_module_ctrl(rtsp_ctx, CMD_RTSP2_SET_APPLY, 0);
        mm_module_ctrl(rtsp_ctx, CMD_RTSP2_SET_STREAMMING, ON);
    } else {
        printf("\nFail to open MMF RTSP module\n");
        mm_module_close(uvch_ctx);
        return;
    }

	
	
	
    printf("\nCreate MMF UVCH-RSTP SISO\n");
    
    uvc_to_rstp_siso = siso_create();
    if (uvc_to_rstp_siso != NULL) {
        siso_ctrl(uvc_to_rstp_siso, MMIC_CMD_ADD_INPUT, (uint32_t)uvch_ctx, 0);
        siso_ctrl(uvc_to_rstp_siso, MMIC_CMD_ADD_OUTPUT, (uint32_t)rtsp_ctx, 0);
        ret = siso_start(uvc_to_rstp_siso);

        if (ret < 0) {
            printf("\nFail to start MMF UVCH-RSTP SISO\n");
            mm_module_close(rtsp_ctx);
            mm_module_close(uvch_ctx);
            return;
        }
    } else {
        printf("\nFail to create MMF UVCH-RSTP SISO\n");
        mm_module_close(rtsp_ctx);
        mm_module_close(uvch_ctx);
    }

    printf("\nMMF UVCH-RSTP started\n");
    
    rtw_thread_exit();
}
static void example_usbh_uvc_task(void *param)
{
    int ret = 0;
    UNUSED(param);
    mm_context_t *uvch_ctx = NULL;
    mm_context_t *rtsp_ctx = NULL;
	mm_context_t *h264_ctx = NULL;
    mm_siso_t *uvc_to_rstp_siso = NULL;
    mm_siso_t *siso_uvch_h264_v1 = NULL;
    mm_siso_t *siso_h264_rtsp_v1 = NULL;
    
	hal_video_sys_init_rtl8195bhp();
	hal_enc_hw_init();
	init_h1v6_parm();    

	rtw_mdelay_os(3000); // Wait for network ready
	
    printf("\nOpen MMF UVCH module\n");
    
    uvch_ctx = mm_module_open(&uvch_module);
    if (uvch_ctx != NULL) {
        mm_module_ctrl(uvch_ctx, MM_CMD_SET_QUEUE_LEN, 1);
        mm_module_ctrl(uvch_ctx, MM_CMD_UVCH_SET_PARAMS, (int)&uvc_params);
        mm_module_ctrl(uvch_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_STATIC);
        mm_module_ctrl(uvch_ctx, MM_CMD_UVCH_APPLY, 0);
        mm_module_ctrl(uvch_ctx, MM_CMD_UVCH_SET_STREAMING, ON);
    } else {
		mm_module_close(uvch_ctx);
        printf("\nFail to open MMF UVCH module\n");
        return;
    }

	h264_ctx = mm_module_open(&h264_module);
	if(h264_ctx){
		mm_module_ctrl(h264_ctx, CMD_H264_SET_PARAMS, (int)&h264_params_);
		mm_module_ctrl(h264_ctx, MM_CMD_SET_QUEUE_LEN, V1_H264_QUEUE_LEN);
		mm_module_ctrl(h264_ctx, MM_CMD_INIT_QUEUE_ITEMS, MMQI_FLAG_DYNAMIC);
		mm_module_ctrl(h264_ctx, CMD_H264_INIT_MEM_POOL, 0);
		mm_module_ctrl(h264_ctx, CMD_H264_APPLY, 0);
	}else{
		rt_printf("H264 open fail\n\r");
		return;
	}
	
    printf("\nOpen MMF RTSP module\n");
    
    rtsp_ctx = mm_module_open(&rtsp2_module);
    if (rtsp_ctx != NULL) {
        mm_module_ctrl(rtsp_ctx, CMD_RTSP2_SELECT_STREAM, 0);
        mm_module_ctrl(rtsp_ctx, CMD_RTSP2_SET_PARAMS, (int)&rtsp2_params);
        mm_module_ctrl(rtsp_ctx, CMD_RTSP2_SET_APPLY, 0);
        mm_module_ctrl(rtsp_ctx, CMD_RTSP2_SET_STREAMMING, ON);
    } else {
        printf("\nFail to open MMF RTSP module\n");
        mm_module_close(uvch_ctx);
        return;
    }

#if 1
	siso_uvch_h264_v1 = siso_create();
	if(siso_uvch_h264_v1){
		siso_ctrl(siso_uvch_h264_v1, MMIC_CMD_ADD_INPUT, (uint32_t)uvch_ctx, 0);
		siso_ctrl(siso_uvch_h264_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)h264_ctx, 0);
		siso_start(siso_uvch_h264_v1);
		printf("siso1 open success\n\r");
	}else{
		printf("siso1 open fail\n\r");
		return;
	}

	siso_h264_rtsp_v1 = siso_create();
	if(siso_h264_rtsp_v1){
		siso_ctrl(siso_h264_rtsp_v1, MMIC_CMD_ADD_INPUT, (uint32_t)h264_ctx, 0);
		siso_ctrl(siso_h264_rtsp_v1, MMIC_CMD_ADD_OUTPUT, (uint32_t)rtsp_ctx, 0);
		siso_start(siso_h264_rtsp_v1);
		printf("siso2 open success\n\r");
	}else{
		printf("siso2 open fail\n\r");
		return;
	}
	while(1)
	{
		vTaskDelay(100);
	}
#else
	printf("\nCreate MMF UVCH-RSTP SISO\n");
    
    uvc_to_rstp_siso = siso_create();
    if (uvc_to_rstp_siso != NULL) {
        siso_ctrl(uvc_to_rstp_siso, MMIC_CMD_ADD_INPUT, (uint32_t)uvch_ctx, 0);
        siso_ctrl(uvc_to_rstp_siso, MMIC_CMD_ADD_OUTPUT, (uint32_t)rtsp_ctx, 0);
        ret = siso_start(uvc_to_rstp_siso);

        if (ret < 0) {
            printf("\nFail to start MMF UVCH-RSTP SISO\n");
            mm_module_close(rtsp_ctx);
            mm_module_close(uvch_ctx);
            return;
        }
    } else {
        printf("\nFail to create MMF UVCH-RSTP SISO\n");
        mm_module_close(rtsp_ctx);
        mm_module_close(uvch_ctx);
    }
    rtw_thread_exit();
#endif

}

#else

static void example_usbh_uvc_task(void *param)
{
    int ret = 0;
    struct uvc_buf_context buf;
    struct uvc_context *uvc_ctx;
	int status = 0;
    UNUSED(param);

    printf("\nInit USB host driver\n");
    ret = USB_INIT_OK;
	_usb_init();
	status = wait_usb_ready();
	if(status != USB_INIT_OK){
		if(status == USB_NOT_ATTACHED)
			printf("\r\n NO USB device attached\n");
		else
			printf("\r\n USB init fail\n");
		goto exit;
	}
    if (ret != USB_INIT_OK) {
        printf("\nFail to init USB\n");
        goto exit;
    }
    
    printf("\n[example_usbh_uvc_task]Init UVC driver\n");
#if UVC_BUF_DYNAMIC
    ret = uvc_stream_init(4, 60000);
#else
    ret = uvc_stream_init();
#endif
    if (ret < 0) {
        printf("\nFail to init UVC driver\n");
        goto exit1;
    }
    
    printf("\nSet UVC parameters\n");
    uvc_ctx = (struct uvc_context *)rtw_malloc(sizeof(struct uvc_context));
    if (!uvc_ctx) {
        printf("\nFail to allocate UVC context\n");
        goto exit1;
    }

    uvc_ctx->fmt_type = USBH_UVC_FORMAT_TYPE;
    uvc_ctx->width = USBH_UVC_WIDTH;
    uvc_ctx->height = USBH_UVC_HEIGHT;
    uvc_ctx->frame_rate = USBH_UVC_FRAME_RATE;
    uvc_ctx->compression_ratio = 0;
    ret = uvc_set_param(uvc_ctx->fmt_type, &uvc_ctx->width, &uvc_ctx->height, &uvc_ctx->frame_rate,
            &uvc_ctx->compression_ratio);
    if (ret < 0) {
        printf("\nFail to set UVC parameters: %d\n", ret);
        goto exit2;
    }

    printf("\nTurn on UVC stream\n");
    ret = uvc_stream_on();
    if (ret < 0) {
        printf("\nFail to turn on UVC stream: %d\n", ret);
        goto exit2;
    }

    rtw_mutex_init(&uvc_buf_mutex);
    
#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_HTTPD)
    printf("\nStart %s server\n", USBH_UVC_HTTP_TAG);
    ret = uvc_httpd_start();
    if (ret != 0) {
        printf("\nFail to start %s server: %d\n", USBH_UVC_HTTP_TAG, ret);
        goto exit2;
    }
#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_HTTPC)
    printf("\nStart %s client\n", USBH_UVC_HTTP_TAG);
    ret = uvc_httpc_start();
    if (ret != 0) {
        printf("\nFail to start %s client: %d\n", USBH_UVC_HTTP_TAG, ret);
        goto exit2;
    }
#endif

#if (CONFIG_USBH_UVC_APP == USBH_UVC_APP_FATFS)
    printf("\nStart FATFS service\n");
    ret = uvc_fatfs_start();
    if (ret != 0) {
        printf("\nFail to start fatfs: %d\n", ret);
        goto exit2;
    }
#endif

    printf("\nStart capturing images\n");
    
    while (1) {
        ret = uvc_dqbuf(&buf);
        
        if (buf.index < 0) {
            printf("\nFail to dequeue UVC buffer\n");
            ret = 1;
        } else if ((uvc_buf_check(&buf) < 0) || (ret < 0)) {
            printf("\nUVC buffer error: %d\n", ret);
            uvc_stream_off();
            break;
        }

        if (ret == 0) {
            uvc_img_prepare(&buf);
        }

        ret = uvc_qbuf(&buf);
        if (ret < 0) {
            printf("\nFail to queue UVC buffer\n");
        }

        rtw_mdelay_os(1000);
    }

    printf("\nStop capturing images\n");

exit2:
    rtw_mutex_free(&uvc_buf_mutex);
    uvc_stream_free();
    rtw_free(uvc_ctx);
exit1:
    _usb_deinit();
exit:
    rtw_thread_exit();
}

#endif // (CONFIG_USBH_UVC_APP == USBH_UVC_APP_MMF_RTSP)

void example_usbh_uvc(void)
{
    int ret;
    struct task_struct task;
    
    printf("\nUSB host UVC demo started...\n");
    
    ret = rtw_create_task(&task, "example_usbh_uvc_task", 1024, tskIDLE_PRIORITY + 1, example_usbh_uvc_task, NULL);
    if (ret != pdPASS) {
        printf("\nFail to create USB host UVC thread\n");
    }
}

#endif
