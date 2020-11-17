/**************************************************************************//**
 * @file     main.c
 * @brief    main function example.
 * @version  V1.00
 * @date     2016-06-08
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 ******************************************************************************/

//#include "cmsis.h"
//#include "shell.h"
#include "cmsis_os.h"               // CMSIS RTOS header file
#include <math.h>
#include "hal.h"
#include "strproc.h"
#include "memory.h"
#include "icc_api.h"
#include "serial_api.h"
#include "serial_ex_api.h"
//#include "stdlib.h"

#if !(CONFIG_CMSIS_RTX_EN | CONFIG_CMSIS_FREERTOS_EN)
#error "This test code needs the RTOS is enabled!!"
#endif

void icc_test_task (void const *argument);         // thread function

osThreadId tid_icc_test;                             // thread id
osThreadDef (icc_test_task, osPriorityNormal, 1, 1024);      // thread object

#define TEST_MSG_RX_BUF_SIZE    128
#define TEST_MSG_RX_BUF_NUM     2

//#define TEST_MSG_TX_BUF_SIZE    1024

icc_msg_rx_req_t test_rx_req[TEST_MSG_RX_BUF_NUM];


typedef struct icc_cmd_uart_init_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t uart_idx:2;
            uint32_t uart_parity:4;
            uint32_t uart_stop_bits:2;
            uint32_t uart_frame_bits:8;
            uint32_t :8;
            
            uint32_t cmd:8; // command type bit[31:24]: reserved for ICC command type
        } cmd_b;
    };
} icc_cmd_uart_init_t, *picc_cmd_uart_init_t;

typedef struct icc_msg_uart_tx_s{
    union {
        uint32_t msg_w;
        struct {
            icc_msg_qid_t msg_q:8;  // message type bit[7:0]: reserved for message queue ID
            uint32_t uart_idx:8;    // message operland bit[15:8]: uasr application data
            uint32_t msg_type:8;    // message type bit[23:16]: reserved for ICC message type
            uint32_t cmd:8;         // command type bit[31:24]: reserved for HAL, user app shouldn't use this field
        } msg_b;
    };
} icc_msg_uart_tx_t, *picc_msg_uart_tx_t;

typedef struct icc_cmd_uart_tx_done_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t uart_idx:8;
            uint32_t status:16;
            
            uint32_t cmd:8; // command type bit[31:24]: reserved for ICC command type
        } cmd_b;
    };
} icc_cmd_uart_tx_done_t, *picc_cmd_uart_tx_done_t;

typedef struct icc_cmd_uart_rx_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t uart_idx:8;
            uint32_t :16;
            
            uint32_t cmd:8; // command type bit[31:24]: reserved for ICC command type
        } cmd_b;
    };
} icc_cmd_uart_rx_t, *picc_cmd_uart_rx_t;

typedef struct icc_cmd_uart_rx_err_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t uart_idx:8;
            uint32_t status:16;
            
            uint32_t cmd:8; // command type bit[31:24]: reserved for ICC command type
        } cmd_b;
    };
} icc_cmd_uart_rx_err_t, *picc_cmd_uart_rx_err_t;

typedef struct icc_cmd_uart_abort_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t uart_idx:8;
            uint32_t dir:1;
            uint32_t :15;
            
            uint32_t cmd:8; // command type bit[31:24]: reserved for ICC command type
        } cmd_b;
    };
} icc_cmd_uart_abort_t, *picc_cmd_uart_abort_t;

uint8_t uart_idx;

serial_t serial_obj;
volatile uint32_t uart_tx_len;
volatile uint32_t uart_rx_len;

volatile uint8_t tx_done = 0;
volatile uint8_t rx_done = 0;

#define ICC_UART_FRAME_TYPE     0x01

#define ICC_CMD_UART_INIT       0x10
#define ICC_CMD_UART_TX_DONE    0x11
#define ICC_CMD_UART_RX         0x12
#define ICC_CMD_UART_ABORT      0x13
#define ICC_CMD_UART_RX_ERR     0x14

#define ICC_MSG_UART_TX         0x10
#define ICC_MSG_UART_RX_DONE    0x11

void icc_uart_tx_done_callback (void *arg)
{
    icc_cmd_uart_tx_done_t icc_cmd;
    
    dbg_printf ("%s==>\r\n", __FUNCTION__);
    free (arg); // free UART TX buffer

    icc_cmd.cmd_w = 0;
    icc_cmd.cmd_b.cmd = ICC_CMD_UART_TX_DONE;

    icc_cmd_send (icc_cmd.cmd_w, uart_tx_len, 1000000, NULL);
}

void icc_uart_rx_data_to_hs_done (uint32_t cb_arg)
{
    dbg_printf ("%s ==> pbuf = 0x%x\r\n", __FUNCTION__, cb_arg);
    if (cb_arg != 0) {
        free ((void *)cb_arg);
    }
}

void icc_uart_rx_done_callback (void *arg)
{
    int ret;
    uint8_t *pbuf = (uint8_t *)arg;

    dbg_printf ("%s ==> pbuf = 0x%x\r\n", __FUNCTION__, (uint32_t)pbuf);
//    dump_bytes (pbuf, uart_rx_len);

    ret = icc_msg_tx_submit(ICC_MSG_UART_RX_DONE, ICC_UART_FRAME_TYPE, pbuf, uart_rx_len,
                        icc_uart_rx_data_to_hs_done, (uint32_t)pbuf);
    if (ret != 0) {
        dbg_printf("Send ICC Msg with UART RX data failed (%d)\r\n", ret);
    }
}

uint32_t icc_uart_init_cmd_handler (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg)
{
    serial_t *uart_obj = (serial_t *)arg;
    icc_cmd_uart_init_t icc_cmd;
    uint32_t baud_rate;
    PinName tx_pin;
    PinName rx_pin;

    icc_cmd.cmd_w = icc_cmd_word0;
    baud_rate = icc_cmd_word1;
    
    dbg_printf ("ICC_UART_Init_Cmd: Idx=%u FrameBits=%u ", icc_cmd.cmd_b.uart_idx, icc_cmd.cmd_b.uart_frame_bits);
    dbg_printf ("Parity=%u StopBits=%u BaudRate=%lu\r\n", icc_cmd.cmd_b.uart_parity, icc_cmd.cmd_b.uart_stop_bits, baud_rate);

    if (icc_cmd.cmd_b.uart_idx == 0) {
        tx_pin = PA_8;
        rx_pin = PA_7;
        hal_dbg_port_disable(); // since UART0 pin conflict with SWD
    } else {
        tx_pin = PA_1;
        rx_pin = PA_0;
    }
    serial_init (uart_obj, tx_pin, rx_pin);
    serial_format (uart_obj, icc_cmd.cmd_b.uart_frame_bits, icc_cmd.cmd_b.uart_parity, icc_cmd.cmd_b.uart_stop_bits);
    serial_baud (uart_obj, baud_rate);
    serial_set_flow_control (uart_obj, FlowControlNone, 0, 0);
    return 0;
}

uint32_t icc_uart_rx_cmd_handler (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg)
{
    serial_t *uart_obj = (serial_t *)arg;
    icc_cmd_uart_rx_t icc_cmd;
    uint32_t rx_len;
    uint8_t *pbuf;
    int32_t ret;

    icc_cmd.cmd_w = icc_cmd_word0;
    rx_len = icc_cmd_word1;
    dbg_printf("%s==> uart_idx=%u RX_Len=%lu\r\n", __FUNCTION__, icc_cmd.cmd_b.uart_idx, rx_len);

    if (rx_len > 0) {
        pbuf = (uint8_t *)malloc (rx_len);
        if (pbuf != NULL) {
            uart_rx_len = rx_len;
            serial_recv_comp_handler (uart_obj, (void *)icc_uart_rx_done_callback, (uint32_t)pbuf);
            ret = serial_recv_stream_dma (uart_obj, (char *)pbuf, rx_len);
            if (ret != 0) {
                icc_cmd_uart_rx_err_t icc_cmd;
                
                icc_cmd.cmd_w = 0;
                icc_cmd.cmd_b.cmd = ICC_CMD_UART_RX_ERR;
                icc_cmd.cmd_b.status = ret;
                
                icc_cmd_send (icc_cmd.cmd_w, 0, 1000000, NULL);
            }
        } else {
            dbg_printf("%s: malloc for UART RX buf err\r\n", __func__);
        }
    }
    return 0;
}

void icc_uart_tx_msg_handler(uint8_t *pmsg_buf, uint32_t msg_size, uint32_t arg)
{
    serial_t *uart_obj = (serial_t *)arg;
    uint8_t *pbuf;
    int32_t ret=0;

    dbg_printf ("%s => msg_size=%lu arg=0x%x\r\n", __FUNCTION__, msg_size, arg);

    if (msg_size > 0) {
//        dump_bytes (pmsg_buf, msg_size);
        pbuf = (uint8_t *)malloc(msg_size);
        if (pbuf != NULL) {
            memcpy (pbuf, pmsg_buf, msg_size);
            uart_tx_len = msg_size;
            serial_send_comp_handler (uart_obj, (void *)icc_uart_tx_done_callback, (uint32_t)pbuf);
            ret = serial_send_stream (uart_obj, (char *)pbuf, msg_size);
            if (ret != 0) {
                dbg_printf("%s=> UART TX Err(%d)\r\n", __func__, ret);
            }
        } else {
            dbg_printf ("%s => malloc for UART TX buf err!!\r\n", __FUNCTION__);
            ret = 1;
        }
    }

    if ((msg_size == 0) || (ret != 0)) {
        icc_cmd_uart_tx_done_t icc_cmd;

        icc_cmd.cmd_w = 0;
        icc_cmd.cmd_b.cmd = ICC_CMD_UART_TX_DONE;
        icc_cmd.cmd_b.status = ret;
        
        icc_cmd_send (icc_cmd.cmd_w, 0, 1000000, NULL);
    }
}

 void icc_test_task (void const *argument)
{
    uint32_t i;
    uint8_t *pbuf;
    
    dbg_printf("icc_test_task==>\r\n");

    icc_init ();

    // Initial the data buffer for message receiving
    for (i=0; i<TEST_MSG_RX_BUF_NUM; i++) {
        pbuf = (uint8_t *)malloc (TEST_MSG_RX_BUF_SIZE);
        if (pbuf != NULL) {
            icc_msg_rx_req_submit (&test_rx_req[i], pbuf, TEST_MSG_RX_BUF_SIZE);
        } else {
            dbg_printf("malloc for Msg RX buffer error!\r\n");
            break;
        }
    }

    // register command callback
    icc_cmd_register(ICC_CMD_UART_INIT, (icc_user_cmd_callback_t)icc_uart_init_cmd_handler, (uint32_t)&serial_obj);
    icc_cmd_register(ICC_CMD_UART_RX, (icc_user_cmd_callback_t)icc_uart_rx_cmd_handler, (uint32_t)&serial_obj);

    // register message callback
    icc_msg_register (ICC_MSG_UART_TX, ICC_UART_FRAME_TYPE, icc_uart_tx_msg_handler, (uint32_t)&serial_obj);

    while(1);
}

/// default main
void main (void)
{
    uint32_t ret;

    DBG_ERR_MSG_ON(_DBG_ICC_);
    DBG_WARN_MSG_ON(_DBG_ICC_);
//    DBG_INFO_MSG_ON(_DBG_ICC_);
    
#if CONFIG_CMSIS_RTX_EN | CONFIG_CMSIS_FREERTOS_EN
    ret = osKernelInitialize ();                    // initialize CMSIS-RTOS
    if (ret != osOK) {
        dbg_printf ("KernelInitErr(0x%x)\r\n", ret);
        while(1);
    }
    
    // initialize peripherals here
    
    // create 'thread' functions that start executing,
    // example: tid_name = osThreadCreate (osThread(name), NULL);
    tid_icc_test = osThreadCreate (osThread(icc_test_task), NULL);
    if (tid_icc_test == 0) {
        dbg_printf ("Create shell task error\r\n");
    }

    ret = osKernelStart ();                         // start thread execution 
#else
    icc_test_task ();
#endif    
}

