/******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
******************************************************************************/

#include "platform_opts.h"
#if 1

#include <stdint.h>
//#include "psram_reserve.h"
#include "mmf2_module.h"
#include "module_uvch.h"
#include "usb.h"
#include "uvc_intf.h"
#include "uvcvideo.h"

#define MMF_UVCH_TP_TEST  0
#define Psram_reserve_malloc malloc
#define Psram_reserve_free free

static void mmf_uvch_pump_thread(void *param)
{
    int ret;
	int width=0, height=0;
	int center1=0, center2=0;
    uvc_ctx_t *uvc_ctx = (uvc_ctx_t *)param;
    mm_context_t *mctx = (mm_context_t *)uvc_ctx->parent;
    mm_queue_item_t *output_item;
    struct uvc_buf_context buf;
	width = uvc_ctx->params.width;
	height = uvc_ctx->params.height;
	center1 = width*height/2+width/2;
	center2 = width*height/2+width/2 + width*height;

#if MMF_UVCH_TP_TEST
    static u32 frame_cnt = 0;
    static u32 total_frame_cnt = 0;
    static u32 total_frame_size = 0;
    static u32 start_time;
#endif

    while (1) {
        rtw_down_sema(&uvc_ctx->pump_sema);

        ret = uvc_dqbuf(&buf);

		//printf("Buf len: %d p1:%d p2:%d.\r\n", buf.len, buf.data[center1], buf.data[center2]);
        if (buf.index < 0) {
            printf("\nFail to dequeue UVC buffer\n");
            goto mmf_uvch_pump_thread_qbuf;
        } else if ((uvc_buf_check(&buf) < 0) || (ret < 0)) {
            printf("\nUVC buffer error: %d\n", ret);
            //uvc_stream_off();
            continue;
        }

        if ((mctx == NULL) || (mctx->output_recycle == NULL)) {
            // not ready yet, to avoid hardfault
            goto mmf_uvch_pump_thread_qbuf;
        }
        
#if MMF_UVCH_TP_TEST
        if (total_frame_cnt == 0) {
            start_time = SYSTIMER_TickGet();
            total_frame_size = 0;
            frame_cnt = 0;
        }
        ++total_frame_cnt;
#endif
        
        if (xQueueReceive(mctx->output_recycle, (void *)&output_item, 10) == pdTRUE) {
            output_item->type = uvc_ctx->params.fmt_type;
            output_item->index = buf.index;
            output_item->size = buf.len;
            output_item->timestamp = 0;
            rtw_memcpy((void *)uvc_ctx->frame_buffer, (void *)buf.data, buf.len);
            output_item->data_addr = (uint32_t)uvc_ctx->frame_buffer;
            xQueueSend(mctx->output_ready, (void *)&output_item, 10);
#if MMF_UVCH_TP_TEST
            ++frame_cnt;
            total_frame_size += buf.len;
#endif
        }
        
#if MMF_UVCH_TP_TEST
        if (total_frame_cnt >= 200) {
            u32 duration = SYSTIMER_GetPassTime(start_time);
            u32 mbps = ((total_frame_size * 10) / duration) * 1000 / (1024 * 1024 / 8);
            printf("\nMMF UVCH fps=%d/%d Mbps=%d.%d frame=%dKB\n", (frame_cnt * 1000 + duration/2) / duration, (total_frame_cnt * 1000 + duration/2) / duration, mbps / 10, mbps % 10, total_frame_size / frame_cnt / 1024);
            total_frame_cnt = 0;
        }
#endif

mmf_uvch_pump_thread_qbuf:
        ret = uvc_qbuf(&buf);
        if (ret < 0) {
            printf("\nFail to queue UVC buffer\n");
            goto mmf_uvch_pump_thread_exit;
        }
    }
    
mmf_uvch_pump_thread_exit:
    rtw_thread_exit();
}

static void *uvch_create(void *parent)
{
    int ret;
    uvc_ctx_t *uvc_ctx;
    uvc_ctx = (uvc_ctx_t *)rtw_zmalloc(sizeof(uvc_ctx_t));
        int status = 0;

    if (uvc_ctx == NULL) {
        return NULL;
    }

    printf("\nInit USB host driver\n");
    ret = USB_INIT_OK;
	_usb_init();

	status = wait_usb_ready();
    if (ret != USB_INIT_OK) {
        printf("\nFail to init USB host driver\n");
        rtw_free(uvc_ctx);
        return NULL;
    }

    printf("\n[uvch_create]Init UVC driver\n");
#if UVC_BUF_DYNAMIC
    ret = uvc_stream_init(4, 60000);
#else
    ret = uvc_stream_init();
#endif

    printf("\n[uvch_create]uvc_stream_init Done\r\n");
    if (ret < 0) {
        printf("\nFail to init UVC driver\n");
        _usb_deinit();
        rtw_free(uvc_ctx);
        return NULL;
    }

    uvc_ctx->ctx = (struct uvc_context *)rtw_zmalloc(sizeof(struct uvc_context));
    if (uvc_ctx->ctx == NULL) {
        printf("\nFail to allocate UVC context\n");
        uvc_stream_free();
        _usb_deinit();
        rtw_free(uvc_ctx);
    printf("\n[uvch_create]Fail uvc_ctx->ctx == NULL\r\n");
        return NULL;
    }

    uvc_ctx->parent = parent;

    rtw_init_sema(&uvc_ctx->pump_sema, 0);
    ret = rtw_create_task(&uvc_ctx->pump_task, "mmf_uvch_pump_thread", MM_UVCH_PUMP_THREAD_STACK_SIZE, MM_UVCH_PUMP_THREAD_PRIORITY, mmf_uvch_pump_thread, (void *)uvc_ctx);
    if (ret != pdPASS) {
        printf("\n%Fail to create MMF USBH UVC pump thread\n");
        rtw_free_sema(&uvc_ctx->pump_sema);
        uvc_stream_free();
        _usb_deinit();
        rtw_free(uvc_ctx);
    printf("\n[uvch_create]Fail ret != pdPASS\r\n");
        return NULL;
    }
    
    return (void *)uvc_ctx;
}

static int uvch_handle(void *p, void *input, void *output)
{
    (void)p;
    (void)input;
    (void)output;
    return 0;
}

static void uvch_frame_timer_handler(uint32_t arg)
{
    uvc_ctx_t *uvc_ctx = (uvc_ctx_t *)arg;
    rtw_up_sema_from_isr(&uvc_ctx->pump_sema);
}

static int uvch_control(void *p, int cmd, int arg)
{
    int ret = 0;
    uvc_ctx_t *uvc_ctx = (uvc_ctx_t *)p;
    struct uvc_context *ctx = uvc_ctx->ctx;

	printf("MMF control- cmd:%d arg:%d.\r\n", cmd, arg);
    switch (cmd) {
        case MM_CMD_UVCH_SET_STREAMING: {
			printf("MM_CMD_UVCH_SET_STREAMING.\r\n");
            if (arg == ON) {
                if (0 == uvc_is_stream_on()) {
                    ret = uvc_stream_on();
                    if (ret == 0) {
                        gtimer_start_periodical(&uvc_ctx->frame_timer, uvc_ctx->frame_timer_period, (void *)uvch_frame_timer_handler,
                            (uint32_t)uvc_ctx);
						printf("MM_CMD_UVCH_SET_STREAMING(Done).\r\n");
                    }
                }
            } else {
                if (1 == uvc_is_stream_on()) {
                    uvc_stream_off();
                    gtimer_stop(&uvc_ctx->frame_timer);
                }
            }

            break;
        }

        case MM_CMD_UVCH_SET_PARAMS: {
            uvc_parameter_t *param = (uvc_parameter_t *)arg;

            if (param->fmt_type == UVC_FORMAT_MJPEG || param->fmt_type == UVC_FORMAT_YUY2) {
                ctx->fmt_type = (uvc_fmt_t)param->fmt_type;
                ctx->width = param->width;
                ctx->height = param->height;
                ctx->frame_rate = param->frame_rate;
                ctx->compression_ratio = param->compression_ratio;
                uvc_ctx->frame_timer_period = 1000000 / param->frame_rate;
                rtw_memcpy((void *)&uvc_ctx->params, (void *)arg, sizeof(uvc_parameter_t));
				printf("MM_CMD_UVCH_SET_PARAMS.\r\n");
				printf("MM_CMD_UVCH_SET_PARAMS fmt_type:%d.\r\n", ctx->fmt_type);
				printf("MM_CMD_UVCH_SET_PARAMS width:%d.\r\n", ctx->width);
				printf("MM_CMD_UVCH_SET_PARAMS height:%d.\r\n", ctx->height);
				printf("MM_CMD_UVCH_SET_PARAMS frame_rate:%d.\r\n", ctx->frame_rate);
				printf("MM_CMD_UVCH_SET_PARAMS compression_ratio:%d.\r\n", ctx->compression_ratio);
            } else {
                ctx->fmt_type = UVC_FORMAT_UNKNOWN;
                printf("\nInvalid UVC format: %d\n", param->fmt_type);
                ret = -EINVAL;
            }

            break;
        }

        case MM_CMD_UVCH_APPLY: {
            u8 *buf;
            uvc_parameter_t *param = &uvc_ctx->params;
        
            if (param->ext_frame_buf) {
                buf = (u8 *)Psram_reserve_malloc(param->frame_buf_size);
            } else {
                buf = (u8 *)rtw_malloc(param->frame_buf_size);
            }

            if (buf != NULL) {
                uvc_ctx->frame_buffer = buf;
                ret = uvc_set_param(ctx->fmt_type, &ctx->width, &ctx->height, &ctx->frame_rate, &ctx->compression_ratio);
                if (ret == 0) {
					printf("MM_CMD_UVCH_APPLY.\r\n");
                    gtimer_init(&uvc_ctx->frame_timer, 2);
                }
            } else {
                printf("\nFail to allocate UVC frame buffer\n");
                ret = -ENOMEM;
            }

            break;
        }

        default: {
            ret = -EINVAL;
            break;
        }
    }

    return ret;
}

static void *uvch_destroy(void *p)
{
    uvc_ctx_t *uvc_ctx = (uvc_ctx_t *)p;
    uvc_stream_free();

    if (uvc_ctx != NULL) {
        uvc_parameter_t *param = &uvc_ctx->params;
        
        if (uvc_ctx->pump_task.task != NULL) {
            rtw_delete_task(&uvc_ctx->pump_task);
        }
        
        if (uvc_ctx->frame_buffer != NULL) {
            if (param->ext_frame_buf) {
                Psram_reserve_free(uvc_ctx->frame_buffer);
            } else {
                rtw_free(uvc_ctx->frame_buffer);
            }
            uvc_ctx->frame_buffer = NULL;
        }

        if (uvc_ctx->ctx != NULL) {
            rtw_free(uvc_ctx->ctx);
            uvc_ctx->ctx = NULL;
        }

        rtw_free_sema(&uvc_ctx->pump_sema);
        rtw_free(uvc_ctx);
    }

    _usb_deinit();
    return (void *)NULL;
}

mm_module_t uvch_module = {
    .create = uvch_create,
    .destroy = uvch_destroy,
    .control = uvch_control,
    .handle = uvch_handle,

    .new_item = NULL,
    .del_item = NULL,

    .output_type = MM_TYPE_VSINK,   // output to rtsp
    .module_type = MM_TYPE_VSRC,    // video source
    .name = "UVCH"
};

#endif
