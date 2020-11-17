/**************************************************************************//**
 * @file     icc_api.c
 * @brief    This file implement the ICC(Inter CPU Communication) HAL API.
 * 
 * @version  V1.00
 * @date     2017-06-05
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
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
#include "cmsis.h"
#include "objects.h"
#include "pinmap.h"
#include "hal.h"
#include "icc_api.h"
#include <string.h>

#ifdef CONFIG_ICC_EN

extern void icc_hal_app_init (void);
extern void icc_task_init(void);
extern void icc_task_deinit(void);

extern hal_icc_adapter_t icc_hal_adp;

/// The ICC command indication callback register table size, adjust this size as needed by the user application
// Increases this value if application needs to register more ICC commang handle callback
#define ICC_API_CMD_TBL_SIZE        10      // the size of the ICC command table, user application can add ICC command and its callback to this table

// define ICC message indication callback register table size, adjust this size as needed by the user application
//#define ICC_MSG_TBL_SIZE        10      // the size of the ICC message table, user application can add ICC message and its callback to this table

/// The size of ICC message callback register table
// Increases this value if application needs to register more ICC message handle callback
#define ICC_API_MSG_TBL_SIZE        10
/// The maximum number of ICC message TX request can be pended for message sending
// Increases this value if application needs to issue more TX message request without wait previous TX message transfer is done.
#define ICC_API_MSG_TX_REQ_NUM      8
/// The number of RX requests is pending for ICC message receiving on LQ
//#define ICC_API_MSG_LQRX_REQ_NUM        2
/// The size, in byte, of the ICC message data receiving buffer with the RX Req of LQ. An ICC message data size cannot over this size
//#define ICC_API_MSG_LQRX_REQ_BUF_SIZE     1024

icc_user_cmd_entry_t icc_api_cmd_tbl[ICC_API_CMD_TBL_SIZE];

icc_msg_entry_t icc_api_msg_table[ICC_API_MSG_TBL_SIZE];
icc_msg_tx_req_t icc_api_msg_txreq[ICC_API_MSG_TX_REQ_NUM];

/** 
 *  @brief Hooks the OS task yield function. The ICC HAL will call this function during
 *         a busy waiting period. So the OS can schedule a task switching to prevent
 *         other tasks be starved.
 *
 *  @param[in]  task_yield  The OS task yield function.
 *
 *  @returns    void.
 */ 
__STATIC_INLINE void icc_api_hook_task_yield (void *task_yield)
{
    // Secure region function cannot call secure-region task-yield
    if (task_yield != NULL) {
        icc_hal_adp.task_yield = (icc_task_yield)task_yield;
    } else {
        icc_hal_adp.task_yield = (icc_task_yield)NULL;
    }
}

/** 
 *  @brief Initials the ICC (Inter CPU Communication) object. 
 *
 *  @param[in]  icc_obj  The ICC object.
 *
 *  @returns    void.
 */
void icc_init (void)
{
    uint32_t i;
    
    icc_hal_app_init();

    hal_icc_set_cmd_tbl(&icc_hal_adp, &(icc_api_cmd_tbl[0]), ICC_API_CMD_TBL_SIZE);
    if (icc_hal_adp.msg_regtbl_sz == 0) {
        icc_hal_adp.pmsg_regtbl = icc_api_msg_table;
        icc_hal_adp.msg_regtbl_sz = ICC_API_MSG_TBL_SIZE;
    }

    for (i=0; i<ICC_API_MSG_TX_REQ_NUM; i++) {
        hal_icc_tx_req_pool_fill(&icc_hal_adp, &icc_api_msg_txreq[i]);
    }

    icc_task_init();    
}

/** 
 *  @brief Submits a message RX request with RX data buffer to the ICC HAL. The RX requests 
 *         are used to receive messages from HS platform. 
 *  @param[in]  rx_req  The message RX request will to be added to the message RX request pending queue.
 *  @param[in]  pbuf  The data buffer for ICC message data receiving.
 *  @param[in]  size  The size, in byte, of the data buffer.
 *
 *  @return     void.
 */
void icc_msg_rx_req_submit (icc_msg_rx_req_t *rx_req, uint8_t *pbuf, uint32_t size)
{
    hal_status_t ret;
    
    rx_req->q_id = ICC_LQ;
    rx_req->msg_buf = pbuf;
    rx_req->buf_size = size;
    
    ret = hal_icc_msg_rx_req_submit (&icc_hal_adp, rx_req);
    if (ret != HAL_OK) {
        DBG_ICC_ERR ("RX Req submit error(%d)\r\n", ret);
    }
}


/** 
 *  @brief To disable the ICC object.
 *
 *  @param[in]  icc_obj  The ICC object.
 *
 *  @returns void.
 */
void icc_deinit (void)
{
    // TODO: disable ICC task
    icc_task_deinit();
}

/** 
 *  @brief Registers(add) an ICC command to the user application ICC command table.
 *
 *  @param[in]  cmd  The user application ICC command type to be registered.
 *  @param[in]  callback  The handler function of this user application ICC command type.
 *  @param[in]  cb_arg  The application data will be passed back to the application with the callback function.
 *
 *  @return     void.
 */
void icc_cmd_register(uint8_t cmd, icc_user_cmd_callback_t callback, uint32_t cb_arg)
{
    hal_status_t ret;
    
    ret = hal_icc_cmd_register(&icc_hal_adp, cmd, (icc_user_cmd_handler_t) callback, cb_arg);
    if (ret != HAL_OK) {
        DBG_ICC_ERR ("icc_cmd_register err(%d)\r\n", ret);
    }
}

/** 
 *  @brief Unregisters(remove) an ICC command from the user application ICC command table.
 *
 *  @param[in]  cmd  The ICC command type to be removed from the user application ICC command table.
 *
 *  @returns    void.
 */
void icc_cmd_unregister(uint8_t cmd)
{
    hal_icc_cmd_unregister(&icc_hal_adp, cmd);
}

/** 
 *  @brief Sends an ICC command to the HS platform.
 *
 *  @param[in]  cmd  The ICC command word 0, it contains the command type and the data word0.
 *  @param[in]  cmd_para1  The ICC command parameter(data word1).
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion of
 *                          command sending.
 *                            -Value 0: no wait.
 *                            -Value 0xFFFFFFFF: wait forever.
 *  @param[in]  task_yield  The OS task yield function. The ICC HAL will call this function
 *                          while wait for the command sending is finished.
 *
 *  @return     void.
 */
void icc_cmd_send (uint32_t cmd_w, uint32_t cmd_para1, uint32_t timeout_us, void *task_yield)
{
    hal_status_t ret;
    icc_user_cmd_t cmd;

    cmd.cmd_w = cmd_w;
    icc_api_hook_task_yield(task_yield);

    ret = hal_icc_l2h_cmd_send (&icc_hal_adp, cmd.cmd_w, cmd_para1, timeout_us);

    icc_api_hook_task_yield(NULL);

    if (ret != HAL_OK) {
        DBG_ICC_ERR ("icc_cmd_send err(%d)\r\n", ret);
    }
}

/**
 *  @brief Registers(adds) an ICC user application message to the
 *         ICC user application message table.
 *
 *  @param[in]  msg_type  The ICC message type to be registered.
 *  @param[in]  frame  The frame type(category) of this ICC message.
 *  @param[in]  callback  The ICC message handler function of this new added message type.
 *  @param[in]  cb_arg  The application data will be passed back to the application
 *                      with the callback function.
 *
 *  @return     void.
 */
void icc_msg_register (uint8_t msg_type, uint8_t frame,
                          icc_user_msg_callback_t callback, uint32_t cb_arg)
{
    hal_status_t ret;

    ret = hal_icc_msg_tbl_reg (&icc_hal_adp, msg_type, frame, (icc_msg_rx_cb_t)callback, (uint32_t)cb_arg);

    if (ret != HAL_OK) {
        DBG_ICC_ERR("icc_msg_register err(%d)\r\n", ret);
    }
}

/** 
 *  @brief Un-register(remove) an user application ICC message from the
 *         user application ICC message table.
 *
 *  @param[in]  msg  The user application ICC message type to be removed
 *                   from the user application ICC message table.
 *  @param[in]  frame  The frame type(category) of this ICC message.
 *
 *  @returns    void.
 */
void icc_msg_unregister (uint8_t msg, uint8_t frame)
{
    hal_icc_msg_tbl_unreg (&icc_hal_adp, msg, frame);
}

/** 
 *  @brief Sends a ICC message (with message data) to HS platform.
 *  @param[in]  msg_type  The message type of the ICC message to be send.
 *  @param[in]  frame_type  The frame type(category) of the message type.
 *  @param[in]  q_id  The message queue ID. It assign the message queue to send this message(with its data).
 *  @param[in]  msg_data  The buffer of the message data to be send.
 *  @param[in]  msg_len  The length(in byte) of data in the buffer msg_data to be send.
 *  @param[in]  callback  The call-back function for the message data transfer is done.
 *  @param[in]  callback_arg  The argument of the call-back function.
 *
 *  @return     0: Message send OK. (the TX request adds to the TX pending queue OK).
 *  @return     < 0: Gor error on Message sending.
 */
int32_t icc_msg_tx_submit (uint8_t msg_type, uint8_t frame_type, uint8_t *msg_data, uint16_t msg_len,
                    icc_msg_tx_callback_t callback, uint32_t callback_arg)
{
    hal_status_t ret;
    
    ret = hal_icc_msg_tx (&icc_hal_adp, msg_type, frame_type, ICC_LQ, msg_data, msg_len,
                            (icc_msg_tx_cb_t)callback, callback_arg);
    if (ret != HAL_OK) {
        DBG_ICC_ERR("icc_msg_tx_submit err(%d)\r\n", ret);
    }

    return (0-ret);
}

#endif  // end of "#ifdef CONFIG_ICC_EN"

