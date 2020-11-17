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
//#include <math.h>
#include "serial_api.h"
#include "strproc.h"
#include "memory.h"
#include "icc_api.h"
#include "utility.h"

void icc_test_task (void const *argument);         // thread function

osThreadId tid_icc_test;                             // thread id
osThreadDef (icc_test_task, osPriorityNormal, 1, 1024);      // thread object


#define TEST_MSG_RX_BUF_SIZE    1024     
#define TEST_MSG_RX_BUF_NUM     2

#define TEST_MSG_TX_BUF_SIZE    128

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


volatile uint8_t loopback_done;

#define ICC_UART_FRAME_TYPE     0x01

#define ICC_CMD_UART_INIT       0x10
#define ICC_CMD_UART_TX_DONE    0x11
#define ICC_CMD_UART_RX         0x12
#define ICC_CMD_UART_ABORT      0x13
#define ICC_CMD_UART_RX_ERR     0x14

#define ICC_MSG_UART_TX         0x10
#define ICC_MSG_UART_RX_DONE    0x11

void icc_uart_tx_done_cmd_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    icc_cmd_uart_tx_done_t icc_cmd;
    uint32_t tx_len;

    icc_cmd.cmd_w = cmd;
    tx_len = op;
    dbg_printf("%s==> status=0x%x tx_len=%lu\r\n", __FUNCTION__, icc_cmd.cmd_b.status, tx_len);
}

void icc_uart_rx_done_msg_handler(uint8_t *pmsg_buf, uint32_t msg_size, uint32_t cb_arg)
{
    uint32_t i;
    uint32_t err_cnt = 0;

    dbg_printf("%s=> msg_size=%lu\r\n", __func__, msg_size);

    // since in interrupt handler, use block mode to read message queue
    if (msg_size > 0) {
        for (i=0; i<msg_size; i++) {
            if (pmsg_buf[i] != (i & 0xFF)) {
                err_cnt++;
            }
        }
        
        if (err_cnt == 0) {
            dbg_printf("UART over ICC loop back data OK!\r\n");
        } else {
            dbg_printf("UART over ICC loop-back data Incorrect(err_cnt=%lu)!\r\n", err_cnt);
            dump_bytes(pmsg_buf, msg_size);
        }
        loopback_done = 1;
    } else {
        dbg_printf ("%s ==> Err\r\n", __FUNCTION__);
    }
    
    /* !!! cannot reference to pmsg_buf after return from this function. If the message data still is needed,
           we should copy them to another buffer */
}

void icc_uart_msg_tx_done (uint32_t pbuf)
{
    dbg_printf ("%s => arg = 0x%x\r\n", __func__, pbuf);
    free ((void *)pbuf);
}

int icc_uart_init_cmd (uint8_t uart_idx, int data_bits, SerialParity parity, int stop_bits, int baudrate)
{
    icc_cmd_uart_init_t icc_cmd;
    uint32_t uart_baud_rate;
    
    dbg_printf ("%s==>\r\n", __FUNCTION__);
    
    icc_cmd.cmd_b.cmd = ICC_CMD_UART_INIT;
    icc_cmd.cmd_b.uart_idx = uart_idx;
    icc_cmd.cmd_b.uart_frame_bits = data_bits;
    icc_cmd.cmd_b.uart_parity = parity;
    icc_cmd.cmd_b.uart_stop_bits = stop_bits;
    uart_baud_rate = baudrate;

    dbg_printf ("UART over ICC test, UART_Init: Idx=%u FrameBits=%u ", icc_cmd.cmd_b.uart_idx, icc_cmd.cmd_b.uart_frame_bits);
    dbg_printf ("Parity=%u StopBits=%u BaudRate=%lu\r\n", icc_cmd.cmd_b.uart_parity, icc_cmd.cmd_b.uart_stop_bits, uart_baud_rate);

    icc_cmd_send (icc_cmd.cmd_w, uart_baud_rate, (uint32_t)1000000, (void *)NULL);
    return 0;
}

int icc_uart_send_cmd (uint8_t *pbuf, uint32_t len)
{
    int ret;
    
    do {
        ret = icc_msg_tx_submit(ICC_MSG_UART_TX, ICC_UART_FRAME_TYPE, pbuf, len,
                            icc_uart_msg_tx_done, (uint32_t)pbuf);
        if (ret != 0) {
            dbg_printf("icc_msg_tx_submit ret=%d\r\n", ret);
        }
    } while (ret != 0);

    return 0;
}

int icc_uart_recv_cmd (int rx_len)
{
    icc_cmd_uart_rx_t icc_cmd;
    
    dbg_printf ("%s==>\r\n", __FUNCTION__);
    
    icc_cmd.cmd_b.cmd = ICC_CMD_UART_RX;

    dbg_printf ("UART over ICC test, RX data: Len=%lu \r\n", rx_len);

    icc_cmd_send (icc_cmd.cmd_w, rx_len, 1000000, NULL);
    return 0;
}

int icc_uart_tr_abort_cmd (uint8_t dir)
{
    icc_cmd_uart_abort_t icc_cmd;
    
    dbg_printf ("%s==>\r\n", __FUNCTION__);
    
    icc_cmd.cmd_b.cmd = ICC_CMD_UART_ABORT;
    icc_cmd.cmd_b.dir = dir ? 1: 0;
    dbg_printf ("UART over ICC test, Transfer Abort: Dir=%u \r\n", icc_cmd.cmd_b.dir);
    
    icc_cmd_send (icc_cmd.cmd_w, 0, 1000000, NULL);
    return 0;
}

void icc_test_task (void const *argument)
{
    uint32_t i;
//    icc_user_msg_t msg;
    uint8_t *pbuf;

//wait LS ready    
    vTaskDelay(2000);
    
    dbg_printf("icc_test_task==>\r\n");

    icc_init ();

    // Initial the data buffer for message receiving
    for (i=0; i<TEST_MSG_RX_BUF_NUM; i++) {
        pbuf = malloc (TEST_MSG_RX_BUF_SIZE);
        if (pbuf != NULL) {
            icc_msg_rx_req_submit (&test_rx_req[i], pbuf, TEST_MSG_RX_BUF_SIZE);
        } else {
            dbg_printf("malloc for Msg RX buffer error!\r\n");
            break;
        }
    }

    icc_cmd_register (ICC_CMD_UART_TX_DONE, (icc_user_cmd_callback_t)icc_uart_tx_done_cmd_handler, 0);
    icc_msg_register (ICC_MSG_UART_RX_DONE, ICC_UART_FRAME_TYPE, icc_uart_rx_done_msg_handler, 0);

    // initial LS UART via ICC command: UART0(Pin A7, A8)
    icc_uart_init_cmd(0, 8, 0, 1, 9600);
    
    pbuf = malloc (TEST_MSG_TX_BUF_SIZE);
    if (pbuf != NULL) {
        for (i=0; i<TEST_MSG_TX_BUF_SIZE; i++) {
            *(pbuf + i) = i & 0xFF;
        }
        dcache_clean_by_addr((uint32_t *)pbuf, TEST_MSG_TX_BUF_SIZE);

        // Do a LS UART TX-RX loop-back
        loopback_done = 0;
        icc_uart_recv_cmd(TEST_MSG_TX_BUF_SIZE);
        icc_uart_send_cmd(pbuf, TEST_MSG_TX_BUF_SIZE);

        i = 0;
        while (loopback_done == 0) {
            wait_ms(1);
            i++;
            if (i > 5000) {
                dbg_printf("LS UART loop back over ICC test failed!\r\n");
                break;
            }
        }
        
    } else {
        dbg_printf("malloc for Msg1 TX buffer error!\r\n");
    }

    dbg_printf("Test Done!! <==\r\n");
    
    while(1);
}

void main (void)
{
    uint32_t ret;

    DBG_ERR_MSG_ON(_DBG_ICC_);
//    DBG_WARN_MSG_ON(_DBG_ICC_);
//    DBG_INFO_MSG_ON(_DBG_ICC_);
    ret = osKernelInitialize ();                    // initialize CMSIS-RTOS
    if (ret != osOK) {
        dbg_printf ("KernelInitErr(0x%x)\r\n", ret);
        while(1);
    }
    
    // create 'thread' functions that start executing,
    // example: tid_name = osThreadCreate (osThread(name), NULL);
    tid_icc_test = osThreadCreate (osThread(icc_test_task), NULL);
    if (tid_icc_test == 0) {
        dbg_printf ("Create shell task error\r\n");
    }

    ret = osKernelStart ();                         // start thread execution 

    while(1);
}

