/**************************************************************************//**
 * @file     hal_icc_ns.c
 * @brief    This ICC HAL API functions.
 *
 * @version  V1.00
 * @date     2018-03-29
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
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

#include "hal_icc_nsc.h"
#include "memory.h"

#if CONFIG_ICC_EN && defined(CONFIG_BUILD_NONSECURE)

/**
 * @addtogroup hs_hal_icc ICC
 * @{
 */

/** 
 *  @brief Sends a ICC message (with message data) to the peer.
 *  @param[in]  picc_ns_adp  The ICC HAL adapter.
 *  @param[in]  msg_type  The message type of the ICC message to be send.
 *  @param[in]  frame_type  The frame type(category) of the message type.
 *  @param[in]  q_id  The message queue ID. It assign the message queue to send this message(with its data).
 *  @param[in]  msg_data  The buffer of the message data to be send.
 *  @param[in]  msg_len  The length(in byte) of data in the buffer msg_data to be send.
 *  @param[in]  callback  The call-back function for the message data transfer is done.
 *  @param[in]  callback_arg  The argument of the call-back function.
 *
 *  @return     HAL_OK: Message send OK. (the TX request adds to the TX pending queue OK).
 *  @return     HAL_ERR_PARA: Errors on input arguments.
 *  @return     HAL_NO_RESOURCE: No enough of resource (TX request entity) to send this ICC message. Try again latter.
 */
hal_status_t hal_icc_msg_tx (icc_ns_adapter_t *picc_ns_adp, uint8_t msg_type, uint8_t frame_type, uint8_t q_id, 
                                    uint8_t *msg_data, uint16_t msg_len, icc_msg_tx_cb_t callback, uint32_t callback_arg)
{
    icc_msg_tx_req_t tx_req;
    hal_status_t ret;

    if ((msg_data == NULL) && (msg_len > 0)) {
        DBG_ICC_ERR("%s: msg_buf is NULL\r\n", __func__);
        return HAL_ERR_PARA;
    }

    tx_req.msg_type = msg_type;
    tx_req.frame_type = frame_type;
    tx_req.q_id = q_id;
    tx_req.msg_len = msg_len;
    tx_req.msg_data = msg_data;
    tx_req.pnscallback = callback;
    tx_req.nscallback_arg = callback_arg;
    hal_icc_lock(picc_ns_adp);
    ret = hal_icc_msg_tx_req_submit_nsc (picc_ns_adp, &tx_req);
    hal_icc_unlock(picc_ns_adp);

    return ret;
}

/** 
 *  @brief Registers(adds) an ICC user application message to the 
 *         ICC user application message table.
 *
 *  @param[in]  picc_ns_adp  The ICC HAL adapter.
 *  @param[in]  msg  The ICC message type to be registered.
 *  @param[in]  callback  The ICC message handler function of this new added message type.
 *  @param[in]  cb_arg  The application data will be passed back to the application
 *                      with the callback function.
 *
 *  @return     HAL_OK: Message registration OK.
 *  @return     HAL_NOT_READY: The ICC HAL message table buffer did not been initialed yet.
 *  @return     HAL_NO_RESOURCE: No free entry of the table(table is full).
 */
hal_status_t hal_icc_msg_tbl_reg(icc_ns_adapter_t *picc_ns_adp, uint8_t msg, uint8_t frame,
                                        icc_msg_rx_cb_t callback, uint32_t cb_arg)
{
	uint32_t i;
    hal_status_t ret;

    if (picc_ns_adp->pmsg_regtbl == (icc_msg_entry_t *)NULL) {
        return HAL_NOT_READY;
    }

    ret = HAL_NO_RESOURCE;
    hal_icc_lock(picc_ns_adp);
	for (i = 0; i < picc_ns_adp->msg_regtbl_sz; i++) {
		if ((picc_ns_adp->pmsg_regtbl[i].callback != (icc_msg_rx_cb_t)NULL)) {
            continue;
        }
        
		picc_ns_adp->pmsg_regtbl[i].msg = msg;
		picc_ns_adp->pmsg_regtbl[i].frame = frame;
		picc_ns_adp->pmsg_regtbl[i].callback = callback;
		picc_ns_adp->pmsg_regtbl[i].cb_arg = cb_arg;
		ret = HAL_OK;
        break;
	}
    hal_icc_unlock(picc_ns_adp);
    
	return ret;
}

/** 
 *  @brief Un-register(remove) an user application ICC message from the
 *         user application ICC message table.
 *
 *  @param[in]  picc_ns_adp  The ICC HAL adapter.
 *  @param[in]  msg  The user application ICC message type to be removed
 *                   from the user application ICC message table.
 *
 *  @returns    void.
 */
void hal_icc_msg_tbl_unreg(icc_ns_adapter_t *picc_ns_adp, uint8_t msg, uint8_t frame)
{
	uint32_t i;

    if (picc_ns_adp->pmsg_regtbl == (icc_msg_entry_t *)NULL) {
        return;
    }

    hal_icc_lock(picc_ns_adp);
	for (i = 0; i < picc_ns_adp->msg_regtbl_sz; i++) {
        if ((msg == picc_ns_adp->pmsg_regtbl[i].msg) &&
            (frame == picc_ns_adp->pmsg_regtbl[i].frame)) {
            memset(&picc_ns_adp->pmsg_regtbl[i], 0, sizeof(icc_msg_entry_t));
            break;
        }
	}
    hal_icc_unlock(picc_ns_adp);
}

/** 
 *  @brief The call back function of a ICC message header receiving. It parses the message type
 *         and call the corresponding handler and then should switch to the RX message data stage.
 *  @param[in]  picc_ns_adp  The ICC HAL adapter.
 *  @param[in]  icc_cmd  The new ICC message indication command.
 *
 *  @return     none.
 */
void icc_msg_rx_ready_handler (icc_ns_adapter_t *picc_ns_adp, uint8_t frame_type, uint8_t msg_type,
                                              uint8_t *pmsg_data, uint32_t msg_len)
{
    uint32_t i;

    if (picc_ns_adp->pmsg_regtbl != (icc_msg_entry_t *)NULL) {
        for (i = 0; i < picc_ns_adp->msg_regtbl_sz; i++) {
            if ((msg_type == picc_ns_adp->pmsg_regtbl[i].msg) && 
                (frame_type == picc_ns_adp->pmsg_regtbl[i].frame)) {
                if (picc_ns_adp->pmsg_regtbl[i].callback != (icc_msg_rx_cb_t)NULL) {
                    (picc_ns_adp->pmsg_regtbl[i].callback)(pmsg_data, msg_len, picc_ns_adp->pmsg_regtbl[i].cb_arg);
                }
                break;
            }
        }
    }
}

/** 
 *  @brief Process all the RX requests in the transfer finished RX requests queue. 
 *         This function should be called from the ICC task main loop.
 *  @param[in]  picc_ns_adp  The ICC HAL adapter.
 *  @param[in]  q_id  The index of the queue.
 *                    - 0: The high-queue for the transfer finished RX requests.
 *                    - 1: The low-queue for the transfer finished RX requests.
 *
 *  @return     The gotton RX request entity. If the queue is empty, it returns NULL.
 */
void hal_icc_msg_rx_req_done_process (icc_ns_adapter_t *picc_ns_adp, uint8_t q_id)
{
    icc_msg_rx_req_t *rx_req;

    do {
        rx_req = hal_icc_msg_rx_req_done_deq_nsc (picc_ns_adp, q_id);
        if (rx_req != NULL) {
            // after call the message callback, suppose we can recycle the RX request
            icc_msg_rx_ready_handler(picc_ns_adp, rx_req->frame_type, rx_req->msg_type, rx_req->msg_buf,
                                                rx_req->tred_len);            
            // recycle the RX request
            hal_icc_msg_rx_req_submit_nsc (picc_ns_adp, rx_req);
        }
    } while (rx_req != NULL);
}

/** @} */ /* End of group hs_hal_icc */

#endif      // end of "#if CONFIG_ICC_EN && defined(CONFIG_BUILD_NONSECURE)"

