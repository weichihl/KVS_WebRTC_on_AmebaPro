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
#include "cmsis_os.h"               // CMSIS RTOS header file
#include "icc_api.h"
#include "wait_api.h"
#include "strproc.h"
#include "memory.h"

#if !(CONFIG_CMSIS_RTX_EN | CONFIG_CMSIS_FREERTOS_EN)
#error "This test code needs the RTOS is enabled!!"
#endif

void icc_test_task (void const *argument);         // thread function

osThreadId tid_icc_test;                             // thread id
osThreadDef (icc_test_task, osPriorityNormal, 1, 1024);      // thread object


#define TEST_MSG_RX_BUF_SIZE    1024
#define TEST_MSG_RX_BUF_NUM     2

#define TEST_MSG_TX_BUF_SIZE    128
#define TEST_MSG_NUM            10

icc_msg_rx_req_t test_rx_req[TEST_MSG_RX_BUF_NUM];

//__ALIGNED(32) uint8_t temp_bigbuf[TEST_MSG_BUF_SIZE];
//volatile uint8_t tx_done = 0;
//volatile uint8_t rx_done = 0;

volatile uint8_t msg1_loop_back_done;
volatile uint8_t msg2_loop_back_done;

#define ICC_TEST_CMD1           0x10
#define ICC_TEST_CMD2           0x11
#define ICC_TEST_CMD3           0x12
#define ICC_TEST_CMD4           0x13

#define ICC_TEST_MSG1           0x20
#define ICC_TEST_MSG2           0x21
#define ICC_TEST_MSG3           0x22
#define ICC_TEST_MSG4           0x23

#define ICC_TEST_FRAME_TYPE     0x77

void icc_test_cmd1_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    icc_user_cmd_t icc_cmd;

    icc_cmd.cmd_w = cmd;
    dbg_printf("%s==> cmd_type=0x%x para0=0x%x cmd_op=0x%x arg=0x%x\r\n", __func__,
               icc_cmd.cmd_b.cmd, icc_cmd.cmd_b.para0, op, arg);
}

void icc_test_cmd2_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    icc_user_cmd_t icc_cmd;

    icc_cmd.cmd_w = cmd;
    dbg_printf("%s==> cmd_type=0x%x para0=0x%x cmd_op=0x%x arg=0x%x\r\n", __func__,
               icc_cmd.cmd_b.cmd, icc_cmd.cmd_b.para0, op, arg);
}

void icc_test_cmd3_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    icc_user_cmd_t icc_cmd;

    icc_cmd.cmd_w = cmd;
    dbg_printf("%s==> cmd_type=0x%x para0=0x%x cmd_op=0x%x arg=0x%x\r\n", __func__,
               icc_cmd.cmd_b.cmd, icc_cmd.cmd_b.para0, op, arg);
}

void icc_test_cmd4_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    icc_user_cmd_t icc_cmd;

    icc_cmd.cmd_w = cmd;
    dbg_printf("%s==> cmd_type=0x%x para0=0x%x cmd_op=0x%x arg=0x%x\r\n", __func__,
               icc_cmd.cmd_b.cmd, icc_cmd.cmd_b.para0, op, arg);
}

void icc_msg_tx_done (uint32_t pbuf)
{
    dbg_printf ("%s => arg = 0x%x\r\n", __func__, pbuf);
    free ((void *)pbuf);
}

void icc_test_msg1_handler(uint8_t *pmsg_buf, uint32_t msg_size, uint32_t cb_arg)
{
    uint32_t i;
    uint32_t err_cnt = 0;

    msg1_loop_back_done++;
    dbg_printf("%s=> msg_size=%lu\r\n", __func__, msg_size);

    for (i=0; i<msg_size; i++) {
        if (pmsg_buf[i] != (i & 0xFF)) {
            err_cnt++;
        }
    }

    if (err_cnt == 0) {
        dbg_printf("Msg1 loop back data OK!\r\n");
    } else {
        dbg_printf("Msg1 data Incorrect(err_cnt=%lu)!\r\n", err_cnt);
    }
}

void icc_test_msg2_handler(uint8_t *pmsg_buf, uint32_t msg_size, uint32_t cb_arg)
{
    uint32_t i;
    uint32_t err_cnt = 0;

    msg2_loop_back_done++;
    dbg_printf("%s=> msg_size=%lu\r\n", __func__, msg_size);

    for (i=0; i<msg_size; i++) {
        if (pmsg_buf[i] != (i & 0xFF)) {
            err_cnt++;
        }
    }

    if (err_cnt == 0) {
        dbg_printf("Msg2 loop back data OK!\r\n");
    } else {
        dbg_printf("Msg2 data Incorrect(err_cnt=%lu)!\r\n", err_cnt);
    }
}


void icc_test_task (void const *argument)
{
    uint32_t i;
    uint32_t j;
    icc_user_cmd_t cmd;
//    icc_user_msg_t msg;
    uint8_t *pbuf;
    int32_t ret;

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

    // register command callback
    icc_cmd_register(ICC_TEST_CMD1, (icc_user_cmd_callback_t)icc_test_cmd1_handler, ICC_TEST_CMD1);
    icc_cmd_register(ICC_TEST_CMD2, (icc_user_cmd_callback_t)icc_test_cmd2_handler, ICC_TEST_CMD2);
    icc_cmd_register(ICC_TEST_CMD3, (icc_user_cmd_callback_t)icc_test_cmd3_handler, ICC_TEST_CMD3);
    icc_cmd_register(ICC_TEST_CMD4, (icc_user_cmd_callback_t)icc_test_cmd4_handler, ICC_TEST_CMD4);

    // register message callback
    icc_msg_register (ICC_TEST_MSG1, ICC_TEST_FRAME_TYPE, icc_test_msg1_handler, 0);
    icc_msg_register (ICC_TEST_MSG2, ICC_TEST_FRAME_TYPE, icc_test_msg2_handler, 0);

    dbg_printf("Send Test Command1=>\r\n");
    cmd.cmd_b.cmd = ICC_TEST_CMD1;
    cmd.cmd_b.para0 = 0x1111;
    icc_cmd_send (cmd.cmd_w, 0x5A5A5A5A, 1000000, NULL);

    dbg_printf("Send Test Command2=>\r\n");
    cmd.cmd_b.cmd = ICC_TEST_CMD2;
    cmd.cmd_b.para0 = 0x2222;
    icc_cmd_send (cmd.cmd_w, 0x55AA55AA, 1000000, NULL);

    dbg_printf("Send Test Command3=>\r\n");
    cmd.cmd_b.cmd = ICC_TEST_CMD3;
    cmd.cmd_b.para0 = 0x3333;
    icc_cmd_send (cmd.cmd_w, 0xA5A5A5A5, 1000000, NULL);

    dbg_printf("Send Test Command4=>\r\n");
    cmd.cmd_b.cmd = ICC_TEST_CMD4;
    cmd.cmd_b.para0 = 0x4444;
    icc_cmd_send (cmd.cmd_w, 0xAA55AA55, 1000000, NULL);

    wait_ms (100);

    // Test message loop back
    msg1_loop_back_done = 0;
    msg2_loop_back_done = 0;
    dbg_printf("Send Message1 with Data =>\r\n");

    for (j = 0; j < TEST_MSG_NUM; j++) {
        pbuf = malloc (TEST_MSG_TX_BUF_SIZE);
        if (pbuf != NULL) {
            for (i=0; i<TEST_MSG_TX_BUF_SIZE; i++) {
                *(pbuf + i) = i & 0xFF;
            }

            do {
                ret = icc_msg_tx_submit(ICC_TEST_MSG1, ICC_TEST_FRAME_TYPE, pbuf, TEST_MSG_TX_BUF_SIZE,
                                    icc_msg_tx_done, (uint32_t)pbuf);
                if (ret != 0) {
                    dbg_printf("icc_msg_tx_submit ret=%d\r\n", ret);
                }
            } while (ret != 0);
        } else {
            dbg_printf("malloc for Msg1 TX buffer error!\r\n");
        }

        dbg_printf("Send Message2 with Data =>\r\n");

        pbuf = malloc (TEST_MSG_TX_BUF_SIZE);
        if (pbuf != NULL) {
            for (i=0; i<TEST_MSG_TX_BUF_SIZE; i++) {
                *(pbuf + i) = i & 0xFF;
            }

            do {
                ret = icc_msg_tx_submit(ICC_TEST_MSG2, ICC_TEST_FRAME_TYPE, pbuf, TEST_MSG_TX_BUF_SIZE,
                                    icc_msg_tx_done, (uint32_t)pbuf);
                if (ret != 0) {
                    dbg_printf("icc_msg_tx_submit ret=%d\r\n", ret);
                }
            } while (ret != 0);

        } else {
            dbg_printf("malloc for Msg2 TX buffer error!\r\n");
        }
    }

    // wait LS CPU to loop back message 1
    i = 0;
    while (msg1_loop_back_done < TEST_MSG_NUM) {
        wait_ms(1);
        i++;
        if (i > 5000) {
            dbg_printf("Msg1 loop back failed! Didn't get message from LS.\r\n");
            break;
        }
    }

    // wait LS CPU to loop back message 2
    i = 0;
    while (msg2_loop_back_done < TEST_MSG_NUM) {
        wait_ms(1);
        i++;
        if (i > 5000) {
            dbg_printf("Msg2 loop back failed! Didn't get message from LS.\r\n");
            break;
        }
    }

    dbg_printf("Test Done!! <==\r\n");

    while(1);
}



/// default main
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

