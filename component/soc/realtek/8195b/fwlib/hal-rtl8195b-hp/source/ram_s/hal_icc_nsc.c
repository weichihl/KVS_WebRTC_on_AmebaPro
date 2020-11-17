/**************************************************************************//**
 * @file     hal_icc_nsc.c
 * @brief    The entry functions of ICC HAL API functions for Non-secure.
 *
 * @version  V1.00
 * @date     2016-11-30
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

#include "hal_icc.h"
#include "hal_icc_nsc.h"
#include "memory.h"

#if CONFIG_ICC_EN && CONFIG_ICC_NSC_EN

#if defined(CONFIG_BUILD_SECURE) && !defined(CONFIG_BUILD_BOOT)

extern hal_icc_adapter_t *picc_adp;

//hal_icc_adapter_t _icc_ns_obj;  // This adapter just for need of testing
icc_ns_adapter_t *pgicc_ns_adp;
#if (ICC_CMD_TBL_SIZE > 0)
icc_user_cmd_entry_t icc_cmd_tbl_nsc[ICC_CMD_TBL_SIZE];
#endif

/**
 * @defgroup hs_hal_icc_nsc_api ICC HAL NSC APIs.
 * @ingroup hs_hal_icc
 * @{
 * @brief ICC HAL NSC (Non-Secure Callable) APIs.
 */

/**
 *  @brief The callback function of the NSC(non-secure callable function) for sends a block
 *         of data to the LS platform via the HS to LS message Hi-queue by the interrupt mode.
 *         This function will call the non-secure callback function for message data sending is done.
 *
 *  @param[in]  arg  The non-secure ICC HAL adapter.
 *  @param[in]  result  The transfered data length.
 *
 *  @returns void.
 */
void icc_ns_send_h2l_hq_done(uint32_t arg, int32_t result)
{
    icc_ns_adapter_t *picc_ns_adp = (icc_ns_adapter_t *)arg;

    if (picc_ns_adp->h2l_hq_wr_done != NULL) {
        ((icc_nscb *)(picc_ns_adp->h2l_hq_wr_done))(picc_ns_adp->h2l_hq_wr_done_cb_arg, result);
    }
}

/**
 *  @brief The callback function of the NSC(non-secure callable function) for sends a block
 *         of data to the LS platform via the HS to LS message Lo-queue by the interrupt mode.
 *         This function will call the non-secure callback function for message data sending is done.
 *
 *  @param[in]  arg  The non-secure ICC HAL adapter.
 *  @param[in]  result  The transfered data length.
 *
 *  @returns void.
 */
void icc_ns_send_h2l_lq_done(uint32_t arg, int32_t result)
{
    icc_ns_adapter_t *picc_ns_adp = (icc_ns_adapter_t *)arg;

    if (picc_ns_adp->h2l_lq_wr_done != NULL) {
        ((icc_nscb *)(picc_ns_adp->h2l_lq_wr_done))(picc_ns_adp->h2l_lq_wr_done_cb_arg, result);
    }
}

/**
 *  @brief The callback function of the NSC(non-secure callable function) for receives a block of data
 *         from the LS to HS message Hi-queue by the interrupt mode.
 *         This function will call the non-secure callback function for the message queue data receiving
 *         is done.
 *
 *  @param[in]  arg  The non-secure ICC HAL adapter.
 *  @param[in]  tred_len  The transfered data length.
 *
 *  @returns void.
 */
void icc_ns_recv_l2h_hq_done(void *arg, uint32_t tred_len)
{
    icc_ns_adapter_t *picc_ns_adp = (icc_ns_adapter_t *)arg;

    if (picc_ns_adp->l2h_hq_rd_done != NULL) {
        ((icc_nscb *)(picc_ns_adp->l2h_hq_rd_done))(picc_ns_adp->l2h_hq_rd_done_cb_arg, tred_len);
    }
}

/**
 *  @brief The callback function of the NSC(non-secure callable function) for receives a block of data
 *         from the LS to HS message Lo-queue by the interrupt mode.
 *         This function will call the non-secure callback function for the message queue data receiving
 *         is done.
 *
 *  @param[in]  arg  The non-secure ICC HAL adapter.
 *  @param[in]  tred_len  The transfered data length.
 *
 *  @returns void.
 */
void icc_ns_recv_l2h_lq_done(void *arg, uint32_t tred_len)
{
    icc_ns_adapter_t *picc_ns_adp = (icc_ns_adapter_t *)arg;

    if (picc_ns_adp->l2h_lq_rd_done != NULL) {
        ((icc_nscb *)(picc_ns_adp->l2h_lq_rd_done))(picc_ns_adp->l2h_lq_rd_done_cb_arg, tred_len);
    }
}

/**
 *  @brief The NSC function to setups the HS to LS message Hi-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  q_start_addr  The mesage queue buffer start address.
 *  @param[in]  q_size  The queue buffer size.
 *
 *  @return     HAL_OK: Message queue setup OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge of the
 *                           message queue setup command from the LS platform.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_set_h2l_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size)
{
    return hal_icc_set_queue (picc_adp, QID_H2L_HQ, q_start_addr,  q_size);
}

/**
 *  @brief The NSC function to setups the HS to LS message Lo-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  q_start_addr  The mesage queue buffer start address.
 *  @param[in]  q_size  The queue buffer size.
 *
 *  @return     HAL_OK: Message queue setup OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge of the
 *                           message queue setup command from the LS platform.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_set_h2l_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size)
{
    return hal_icc_set_queue (picc_adp, QID_H2L_LQ, q_start_addr,  q_size);
}

/**
 *  @brief The NSC function to setups the LS to HS message Hi-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  q_start_addr  The mesage queue buffer start address.
 *  @param[in]  q_size  The queue buffer size.
 *
 *  @return     HAL_OK: Message queue setup OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge of the
 *                           message queue setup command from the LS platform.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_set_l2h_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size)
{
    return hal_icc_set_queue (picc_adp, QID_L2H_HQ, q_start_addr,  q_size);
}

/**
 *  @brief The NSC function to setups the LS to HS message Lo-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  q_start_addr  The mesage queue buffer start address.
 *  @param[in]  q_size  The queue buffer size.
 *
 *  @return     HAL_OK: Message queue setup OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge of the
 *                           message queue setup command from the LS platform.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_set_l2h_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size)
{
    return hal_icc_set_queue (picc_adp, QID_L2H_LQ, q_start_addr,  q_size);
}

/**
 *  @brief The NSC function to reset the specified message queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  q_id  The index of the queue to be reset.
 *                      \arg QID_H2L_HQ HS to LS message Hi-queue.
 *                      \arg QID_H2L_LQ HS to LS message Lo-queue.
 *                      \arg QID_L2H_HQ LS to HS message Hi-queue.
 *                      \arg QID_L2H_LQ LS to HS message Lo-queue.
 *
 *  @return     HAL_OK: Message queue reset OK.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge from the LS platform.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_reset_queue_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_id)
{
    return hal_icc_reset_queue (picc_adp, q_id);
}

/**
 *  @brief The wrapper function for S region to call NS region ICC task wakeup function.
 *
 *  @param[in]  arg  The argument to call the NS ICC task wakeup function.
 *  @return     void.
 */
void _hal_icc_ns_task_up (void *arg)
{
    if (pgicc_ns_adp->task_up == (icc_task_up_t)NULL) {
        return;
    }
    
    ((icc_ns_task_up_nscb_t *)(cmse_nsfptr_create(pgicc_ns_adp->task_up)))(arg);
}

/**
 *  @brief The NSC function to initials the non-secure ICC HAL.
 *         This function should be called before
 *         any other non-secure ICC HAL operation.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_init_nsc (icc_ns_adapter_t *picc_ns_adp)
{
    // the Secure region ICC must be initialed before call this function
    pgicc_ns_adp = picc_ns_adp;
//    if (picc_adp == NULL) {
//        hal_icc_init (&_icc_ns_obj);
//    }

    if (picc_adp == NULL) {
        DBG_ICC_ERR ("hal_icc_init_nsc: Secure region ICC should be initialed first!\r\n");
    }

    picc_adp->task_up = (icc_task_up_t)_hal_icc_ns_task_up;
}

/**
 *  @brief The NSC function to checks whether the specified message queue is empty or not.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  q_id  The index of the message queue to be checked.
 *                      \arg QID_H2L_HQ HS to LS message Hi-queue.
 *                      \arg QID_H2L_LQ HS to LS message Lo-queue.
 *                      \arg QID_L2H_HQ LS to HS message Hi-queue.
 *                      \arg QID_L2H_LQ LS to HS message Lo-queue.
 *
 *  @return     FALSE: the specified message queue is not empty.
 *  @return     TRUE: the specified message queue is empty.
 */
SECTION_NS_ENTRY_FUNC
BOOL NS_ENTRY hal_icc_is_queue_empty_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_id)
{
    return hal_icc_is_queue_empty (picc_adp, q_id);
}

/**
 *  @brief The NSC function to gets the free buffer size of the specified message queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  q_id  The index of the specified message queue:
 *                      \arg QID_H2L_HQ HS to LS message Hi-queue.
 *                      \arg QID_H2L_LQ HS to LS message Lo-queue.
 *                      \arg QID_L2H_HQ LS to HS message Hi-queue.
 *                      \arg QID_L2H_LQ LS to HS message Lo-queue.
 *
 *  @returns    The free buffer size of the queue.
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_icc_get_queue_free_size_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_id)
{
    return hal_icc_get_queue_free_size (picc_adp, q_id);
}

/**
 *  @brief The NSC function to sends a block of data to LS via the HS to LS message Hi-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  pbuf  The data buffer to be send.
 *  @param[in]  size  The size of the data to be send, in byte.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion
 *                          of data to be pushed into message queue.
 *                            -value 0: no wait.
 *                            -value 0xFFFFFFFF: wait forever.
 *
 *  @return     HAL_OK: Data push OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous data sending not finished yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get enough queue buffer space to push data.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_send_h2l_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf,
                                               uint32_t size, uint32_t timeout_us)
{
    return hal_icc_send_h2l_hq (picc_adp, pbuf, size, timeout_us);
}

/**
 *  @brief The NSC function to sends an ICC command to the LS platform.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  cmd_word0  The ICC command word 0, it contains the command type and the data word0.
 *  @param[in]  cmd_word1  The ICC command word 1(data word1).
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion of
 *                          command sending.
 *                            -Value 0: no wait.
 *                            -Value 0xFFFFFFFF: wait forever.
 *
 *
 *  @return     HAL_OK: Command sending OK.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge from the LS platform.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_h2l_cmd_send_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t cmd_word0,
                                       uint32_t cmd_word1, uint32_t timeout_us)
{
    return hal_icc_h2l_cmd_send (picc_adp, cmd_word0, cmd_word1, timeout_us);
}

/**
 *  @brief The NSC function to sends a block of data to LS via the HS to LS message Lo-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  pbuf  The data buffer to be send.
 *  @param[in]  size  The size of the data to be send, in byte.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion
 *                          of data to be pushed into message queue.
 *                            -value 0: no wait.
 *                            -value 0xFFFFFFFF: wait forever.
 *
 *  @return     HAL_OK: Data push OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous data sending not finished yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get enough queue buffer space to push data.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_send_h2l_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf, uint32_t size, uint32_t timeout_us)
{
    return hal_icc_send_h2l_lq (picc_adp, pbuf, size, timeout_us);
}

/**
 *  @brief The NSC function to sends a block of data to the LS platform via the HS to LS message Hi-queue
 *         by the interrupt mode.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  send_req  The message queue send request which contains the buffer address,
 *                        data length and the callback for queue sending is done.
 *
 *  @return     HAL_OK: Data push OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous data sending not finished yet.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_send_h2l_hq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *send_req)
{
    icc_q_rw_req_t h2l_hq_req;

    h2l_hq_req.pbuf = send_req->pbuf;
    h2l_hq_req.rw_len = send_req->rw_len;
    h2l_hq_req.callback = (icc_callback_t)icc_ns_send_h2l_hq_done;
    h2l_hq_req.callback_para = (void *)picc_ns_adp;

    picc_ns_adp->h2l_hq_wr_done = (icc_nscb *)cmse_nsfptr_create(send_req->callback);
    picc_ns_adp->h2l_hq_wr_done_cb_arg = send_req->callback_para;
    return hal_icc_send_h2l_hq_int (picc_adp, &h2l_hq_req);
}

/**
 *  @brief The NSC function to sends a block of data to the LS platform via the HS to LS message Lo-queue
 *         by the interrupt mode.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  send_req  The message queue send request which contains the buffer address,
 *                        data length and the callback for queue sending is done.
 *
 *  @return     HAL_OK: Data push OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous data sending not finished yet.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_send_h2l_lq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *send_req)
{
    icc_q_rw_req_t h2l_lq_req;

    h2l_lq_req.pbuf = send_req->pbuf;
    h2l_lq_req.rw_len = send_req->rw_len;
    h2l_lq_req.callback = (icc_callback_t)icc_ns_send_h2l_lq_done;
    h2l_lq_req.callback_para = (void *)picc_ns_adp;

    picc_ns_adp->h2l_lq_wr_done = (icc_nscb *)cmse_nsfptr_create(send_req->callback);
    picc_ns_adp->h2l_lq_wr_done_cb_arg = send_req->callback_para;

    return hal_icc_send_h2l_lq_int (picc_adp, &h2l_lq_req);
}

/**
 *  @brief The NSC function to aborts interrupt mode message data sending on the HS to LS Hi-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *
 *  @returns    The length of data has been transfered.
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_icc_send_h2l_hq_abort_nsc (icc_ns_adapter_t *picc_ns_adp)
{
    return hal_icc_send_h2lq_abort (picc_adp, QID_H2L_HQ);
}

/**
 *  @brief The NSC function to aborts interrupt mode message data sending on the HS to LS Lo-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *
 *  @returns    The length of data has been transfered.
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_icc_send_h2l_lq_abort_nsc (icc_ns_adapter_t *picc_ns_adp)
{
    return hal_icc_send_h2lq_abort (picc_adp, QID_H2L_LQ);
}

/**
 *  @brief The NSC function to receives a block of data from the LS to HS message Hi-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[out]  pbuf  The buffer for the message data receiving.
 *  @param[in]  size  The maximum data size, in byte, to receive.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion of
 *                          data receiving.
 *                            -value 0: no wait.
 *                            -value 0xFFFFFFFF: wait forever.
 *
 *  @return     The actual size of data(in byte) received from the message queue.
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_icc_recv_l2h_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf, uint32_t size, uint32_t timeout_us)
{
    return hal_icc_recv_l2h_hq (picc_adp, pbuf, size, timeout_us);
}

/**
 *  @brief The NSC function to receives a block of data from the LS to HS message Lo-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[out]  pbuf  The buffer for the message data receiving.
 *  @param[in]  size  The maximum data size, in byte, to receive.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion of
 *                          data receiving.
 *                            -value 0: no wait.
 *                            -value 0xFFFFFFFF: wait forever.
 *
 *  @return     The actual size of data(in byte) received from the message queue.
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_icc_recv_l2h_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf, uint32_t size, uint32_t timeout_us)
{
    return hal_icc_recv_l2h_lq (picc_adp, pbuf, size, timeout_us);
}

/**
 *  @brief The NSC function to receives a block of data from the LS to HS message Hi-queue by the interrupt mode.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  rcv_req  The queue receive request which contains the buffer address, data length
 *                       and the callback for the message data receiving is done.
 *
 *  @return     HAL_OK: The message queue data receiving is started with OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous message data receiving not finished yet.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_recv_l2h_hq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *rcv_req)
{
    icc_q_rw_req_t l2h_hq_req;

    l2h_hq_req.pbuf = rcv_req->pbuf;
    l2h_hq_req.rw_len = rcv_req->rw_len;
    l2h_hq_req.callback = icc_ns_recv_l2h_hq_done;
    l2h_hq_req.callback_para = (void *)picc_ns_adp;

    picc_ns_adp->l2h_hq_rd_done = (icc_nscb *)cmse_nsfptr_create(rcv_req->callback);
    picc_ns_adp->l2h_hq_rd_done_cb_arg = rcv_req->callback_para;

    return hal_icc_recv_l2h_hq_int (picc_adp, &l2h_hq_req);
}

/**
 *  @brief The NSC function to receives a block of data from the LS to HS message Lo-queue by the interrupt mode.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  rcv_req  The queue receive request which contains the buffer address, data length
 *                       and the callback for the message data receiving is done.
 *
 *  @return     HAL_OK: The message queue data receiving is started with OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous message data receiving not finished yet.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_recv_l2h_lq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *rcv_req)
{
    icc_q_rw_req_t l2h_lq_req;

    l2h_lq_req.pbuf = rcv_req->pbuf;
    l2h_lq_req.rw_len = rcv_req->rw_len;
    l2h_lq_req.callback = icc_ns_recv_l2h_lq_done;
    l2h_lq_req.callback_para = (void *)picc_ns_adp;

    picc_ns_adp->l2h_lq_rd_done = (icc_nscb *)cmse_nsfptr_create(rcv_req->callback);
    picc_ns_adp->l2h_lq_rd_done_cb_arg = rcv_req->callback_para;

    return hal_icc_recv_l2h_lq_int (picc_adp, &l2h_lq_req);
}

/**
 *  @brief The NSC function to abort an interrupt mode message queue data receiving on the
 *         LS to HS message Hi-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *
 *  @returns    The length of data has been received.
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_icc_recv_l2h_hq_abort_nsc (icc_ns_adapter_t *picc_ns_adp)
{
    return hal_icc_recv_l2h_hq_abort (picc_adp);
}

/**
 *  @brief The NSC function to abort an interrupt mode message queue data receiving on the
 *         LS to HS message Lo-queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *
 *  @returns    The length of data has been received.
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_icc_recv_l2h_lq_abort_nsc (icc_ns_adapter_t *picc_ns_adp)
{
    return hal_icc_recv_l2h_lq_abort (picc_adp);
}

/**
 *  @brief The callback function for non-secure HAL layer ICC command indication.
 *         Since the ICC HAL (in secure region) cannot call non-secure function directly.
 *         So use this function to parse the received ICC command and then call the
 *         corresponding NSCB(non-secure callback) function.
 *
 *  @param[in]  cmd_word0  The word 0 of the received ICC command.
 *  @param[in]  cmd_word1  The word 1 of the received ICC command.
 *  @param[in]  arg  The non-secure ICC HAL adapter.
 *
 *  @returns    Always return 0.
 */
int32_t icc_hal_cmd_ind_nsc_wrapper (uint32_t cmd_word0, uint32_t cmd_word1, uint32_t arg)
{
    icc_ns_adapter_t *picc_ns_adp = (icc_ns_adapter_t *)arg;
    uint32_t i;
    icc_cmd_general_t icc_cmd;

    icc_cmd.word0 = cmd_word0;
    for (i = 0; i < picc_ns_adp->hal_cmd_tbl_size; i++) {
        if (icc_cmd.word0_b.cmd == picc_ns_adp->phal_cmd_tbl[i].cmd) {
            if (picc_ns_adp->phal_cmd_tbl[i].callback != (icc_cmd_nscb *)NULL) {
                ((icc_cmd_nscb *)(picc_ns_adp->phal_cmd_tbl[i].callback))(cmd_word0, cmd_word1, picc_ns_adp->phal_cmd_tbl[i].cb_arg);
            }
            break;
        }
    }

    return 0;
}

/**
 *  @brief The callback function for non-secure user application ICC command indication.
 *         Since the ICC HAL (in secure region) cannot call non-secure function directly.
 *         So use this function to parse the received ICC command and then call the
 *         corresponding NSCB(non-secure callback) function.
 *
 *  @param[in]  cmd_word0  The word 0 of the received ICC command.
 *  @param[in]  cmd_word1  The word 1 of the received ICC command.
 *  @param[in]  arg  The non-secure ICC HAL adapter.
 *
 *  @returns    Always return 0.
 */
int32_t icc_cmd_ind_nsc_wrapper (uint32_t cmd_word0, uint32_t cmd_word1, uint32_t arg)
{
    icc_ns_adapter_t *picc_ns_adp = (icc_ns_adapter_t *)arg;
    uint32_t i;
    icc_cmd_general_t icc_cmd;

    icc_cmd.word0 = cmd_word0;
    for (i = 0; i < picc_ns_adp->cmd_tbl_size; i++) {
        if (icc_cmd.word0_b.cmd == picc_ns_adp->pcmd_tbl[i].cmd) {
            if (picc_ns_adp->pcmd_tbl[i].callback != (icc_cmd_nscb *)NULL) {
                ((icc_cmd_nscb *)(picc_ns_adp->pcmd_tbl[i].callback))(cmd_word0, cmd_word1, picc_ns_adp->pcmd_tbl[i].cb_arg);
            }
            break;
        }
    }

    return 0;
}

/**
 *  @brief The callback function for non-secure HAL ICC message indication.
 *         Since the ICC HAL (in secure region) cannot call non-secure function directly.
 *         So use this function to parse the received message type and then call the
 *         corresponding NSCB(non-secure callback) function.
 *
 *  @param[in]  msg_op  The received message word.
 *                           -bit[7:0]: The index of the target message queue.
 *                             -QID_L2H_HQ: LS to HS message Hi-queue.
 *                             -QID_L2H_LQ: LS to HS message Lo-queue.
 *                           -bit[15:8]: the message operland(optional).
 *                           -bit[23:16]: the message type.
 *  @param[in]  msg_size  The data length of this message.
 *  @param[in]  cb_arg  The non-secure ICC HAL adapter.
 *
 *  @returns    void.
 */
void icc_hal_msg_ind_nsc_wrapper(uint32_t msg_op, uint32_t msg_size, uint32_t cb_arg)
{
    uint32_t i;
    icc_msg_q_ind_cmd_t icc_msg_q_cmd;
    icc_ns_adapter_t *picc_ns_adp = (icc_ns_adapter_t *)cb_arg;
    uint8_t msg_type;

    icc_msg_q_cmd.cmd_w = msg_op;
    msg_type = icc_msg_q_cmd.cmd_b.msg_type;

    for (i = 0; i < picc_ns_adp->hal_msg_tbl_size; i++) {
        if (msg_type == picc_ns_adp->phal_msg_tbl[i].msg) {
            if (picc_ns_adp->phal_msg_tbl[i].callback != (icc_user_msg_nscb *)NULL) {
                ((icc_user_msg_nscb *)(picc_ns_adp->phal_msg_tbl[i].callback))(msg_op, msg_size, picc_ns_adp->phal_msg_tbl[i].cb_arg);
            }
            break;
        }
    }
}

/**
 *  @brief The callback function for non-secure user application message indication.
 *         Since the ICC HAL (in secure region) cannot call non-secure function directly.
 *         So use this function to parse the received message type and then call the
 *         corresponding NSCB(non-secure callback) function.
 *
 *  @param[in]  msg_op  The received message word.
 *                           -bit[7:0]: The index of the target message queue.
 *                             -QID_L2H_HQ: LS to HS message Hi-queue.
 *                             -QID_L2H_LQ: LS to HS message Lo-queue.
 *                           -bit[15:8]: the message operland(optional).
 *                           -bit[23:16]: the message type.
 *  @param[in]  msg_size  The data length of this message.
 *  @param[in]  cb_arg  The non-secure ICC HAL adapter.
 *
 *  @returns    void.
 */
void icc_msg_ind_nsc_wrapper(uint32_t msg_op, uint32_t msg_size, uint32_t cb_arg)
{
    uint32_t i;
    icc_msg_q_ind_cmd_t icc_msg_q_cmd;
    icc_ns_adapter_t *picc_ns_adp = (icc_ns_adapter_t *)cb_arg;
    uint8_t msg_type;

    icc_msg_q_cmd.cmd_w = msg_op;
    msg_type = icc_msg_q_cmd.cmd_b.msg_type;

    for (i = 0; i < picc_ns_adp->msg_tbl_size; i++) {
        if (msg_type == picc_ns_adp->pmsg_tbl[i].msg) {
            if (picc_ns_adp->pmsg_tbl[i].callback != (icc_user_msg_nscb *)NULL) {
                ((icc_user_msg_nscb *)(picc_ns_adp->pmsg_tbl[i].callback))(msg_op, msg_size, picc_ns_adp->pmsg_tbl[i].cb_arg);
            }
            break;
        }
    }
}

/**
 *  @brief The NSC function to initials the ICC HAL command table buffer.
 *         The ICC HAL will look for the command handler in this table when a new ICC command is received.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  pcmd_tbl  The command table buffer.
 *  @param[in]  cmd_tbl_size  The size(number of commands) of this command table.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_set_hal_cmd_tbl_nsc(icc_ns_adapter_t *picc_ns_adp, icc_user_cmd_ns_entry_t *pcmd_tbl,
                                          uint32_t cmd_tbl_size)
{
    picc_ns_adp->phal_cmd_tbl = (icc_user_cmd_ns_entry_t *)pcmd_tbl;
    picc_ns_adp->hal_cmd_tbl_size = cmd_tbl_size;
}

/**
 *  @brief The NSC function to registers(adds) an ICC HAL command to the ICC HAL command table.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  cmd  The ICC command type to be registered.
 *  @param[in]  callback  The ICC command handler function.
 *  @param[in]  cb_arg  The application data will be passed back to the application with the callback function.
 *
 *  @return     HAL_OK: Command registration OK.
 *  @return     HAL_NOT_READY: The ICC HAL command table buffer did not been initialed yet.
 *  @return     HAL_NO_RESOURCE: No free entry of the table(table is full).
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_hal_cmd_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd,
                                                   icc_user_cmd_handler_t callback, uint32_t cb_arg)
{
	uint32_t i;

    if (picc_ns_adp->phal_cmd_tbl == (icc_user_cmd_ns_entry_t *)NULL) {
        return HAL_NOT_READY;
    }

	for (i = 0; i < picc_ns_adp->hal_cmd_tbl_size; i++) {
		if ((picc_ns_adp->phal_cmd_tbl[i].callback != (icc_cmd_nscb *)NULL)) {
            continue;
        }

		picc_ns_adp->phal_cmd_tbl[i].cmd = cmd;
		picc_ns_adp->phal_cmd_tbl[i].callback = (icc_cmd_nscb *)cmse_nsfptr_create(callback);
        picc_ns_adp->phal_cmd_tbl[i].cb_arg = cb_arg;
        return hal_icc_hal_cmd_register(picc_adp, cmd, (icc_user_cmd_handler_t)icc_hal_cmd_ind_nsc_wrapper,
                                        (uint32_t)picc_ns_adp);
	}

    DBG_ICC_ERR ("hal_icc_hal_cmd_register_nsc: ICC NS cmd table is full\r\n");
	return HAL_NO_RESOURCE;
}

/**
 *  @brief The NSC function to resets the ICC HAL command table. After reset the HAL command table is empty.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_hal_cmd_unregister_all_nsc(icc_ns_adapter_t *picc_ns_adp)
{
	uint32_t i;

	for (i = 0; i < picc_ns_adp->hal_cmd_tbl_size; i++) {
        if (picc_ns_adp->phal_cmd_tbl[i].callback != (icc_cmd_nscb *)NULL) {
            hal_icc_hal_cmd_unregister(picc_adp, picc_ns_adp->phal_cmd_tbl[i].cmd);
    		picc_ns_adp->phal_cmd_tbl[i].cmd = 0;
    		picc_ns_adp->phal_cmd_tbl[i].callback = (icc_cmd_nscb *)NULL;
        }
	}
}

/**
 *  @brief The NSC function to un-register(remove) an ICC HAL command from the command table.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  cmd  The ICC HAL command type to be removed from the HAL command table.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_hal_cmd_unregister_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd)
{
	uint32_t i;

	for (i = 0; i < picc_ns_adp->hal_cmd_tbl_size; i++) {
        if (picc_ns_adp->phal_cmd_tbl[i].cmd == cmd) {
            hal_icc_hal_cmd_unregister(picc_adp, picc_ns_adp->phal_cmd_tbl[i].cmd);
    		picc_ns_adp->phal_cmd_tbl[i].cmd = 0;
    		picc_ns_adp->phal_cmd_tbl[i].callback = (icc_cmd_nscb *)NULL;
            break;
        }
	}
}

/**
 *  @brief The NSC function to initials the ICC user application command table buffer.
 *         When a new ICC command is received, the ICC HAL will search the command handler
 *         in the HAL command table first. If the command handler not be found in the
 *         HAL command table then it will search this user application ICC command table.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  pcmd_tbl  The command table buffer.
 *  @param[in]  cmd_tbl_size  The size(number of commands) of this command table.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_set_cmd_tbl_nsc(icc_ns_adapter_t *picc_ns_adp, icc_user_cmd_ns_entry_t *pcmd_tbl, uint32_t cmd_tbl_size)
{
    picc_ns_adp->pcmd_tbl = (icc_user_cmd_ns_entry_t *)pcmd_tbl;
    picc_ns_adp->cmd_tbl_size = cmd_tbl_size;
}

/**
 *  @brief The NSC function to registers(add) an ICC command to the user application ICC command table.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  cmd  The user application ICC command type to be registered.
 *  @param[in]  callback  The handler function of this user application ICC command type.
 *  @param[in]  cb_arg  The application data will be passed back to the application with the callback function.
 *
 *  @return     HAL_OK: Command registration OK.
 *  @return     HAL_NOT_READY: The user application ICC command table buffer did not been initialed yet.
 *  @return     HAL_NO_RESOURCE: No free entry of the table(table is full).
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_cmd_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd, icc_user_cmd_handler_t callback, uint32_t cb_arg)
{
	uint32_t i;

    if (picc_ns_adp->pcmd_tbl == (icc_user_cmd_ns_entry_t *)NULL) {
        return HAL_NOT_READY;
    }

    if (picc_adp->pcmd_tbl == (icc_user_cmd_entry_t *)NULL) {
#if (ICC_CMD_TBL_SIZE > 0)
        hal_icc_set_cmd_tbl(picc_adp, &(icc_cmd_tbl_nsc[0]), ICC_CMD_TBL_SIZE);
#else
        DBG_ICC_ERR ("hal_icc_cmd_register_nsc: S-Region Cmd Reg table is null!!\r\n");
        return HAL_NOT_READY;
#endif
    }

	for (i = 0; i < picc_ns_adp->cmd_tbl_size; i++) {
		if ((picc_ns_adp->pcmd_tbl[i].callback != (icc_cmd_nscb *)NULL)) {
            continue;
        }

		picc_ns_adp->pcmd_tbl[i].cmd = cmd;
		picc_ns_adp->pcmd_tbl[i].callback = (icc_cmd_nscb *)cmse_nsfptr_create(callback);
        picc_ns_adp->pcmd_tbl[i].cb_arg = cb_arg;
        return hal_icc_cmd_register(picc_adp, cmd, (icc_user_cmd_handler_t)icc_cmd_ind_nsc_wrapper, (uint32_t)picc_ns_adp);
	}

    DBG_ICC_ERR ("hal_icc_cmd_register_nsc: ICC NS cmd table is full\r\n");
	return HAL_NO_RESOURCE;
}

/**
 *  @brief The NSC function to resets the user application ICC command table. After the reset
 *         the user application ICC command table is empty.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_cmd_unregister_all_nsc(icc_ns_adapter_t *picc_ns_adp)
{
	uint32_t i;

	for (i = 0; i < picc_ns_adp->cmd_tbl_size; i++) {
        if (picc_ns_adp->pcmd_tbl[i].callback != (icc_cmd_nscb *)NULL) {
            hal_icc_cmd_unregister(picc_adp, picc_ns_adp->pcmd_tbl[i].cmd);
    		picc_ns_adp->pcmd_tbl[i].cmd = 0;
    		picc_ns_adp->pcmd_tbl[i].callback = (icc_cmd_nscb *)NULL;
        }
	}
}

/**
 *  @brief The NSC function to unregisters(remove) an ICC command from the user application ICC command table.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  cmd  The ICC command type to be removed from the user application ICC command table.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_cmd_unregister_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd)
{
	uint32_t i;

	for (i = 0; i < picc_ns_adp->cmd_tbl_size; i++) {
        if (picc_ns_adp->pcmd_tbl[i].cmd == cmd) {
            hal_icc_cmd_unregister(picc_adp, picc_ns_adp->pcmd_tbl[i].cmd);
    		picc_ns_adp->pcmd_tbl[i].cmd = 0;
    		picc_ns_adp->pcmd_tbl[i].callback = (icc_cmd_nscb *)NULL;
            break;
        }
	}
}

/**
 *  @brief The NSC function to sends a user application message with data to the LS platform via a
 *         specified HS to LS message queue.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  picc_msg  The message send request. The request includes the mesage type, queue index,
 *                        the data buffer and the data size for the message sending.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion
 *                          of data to be pushed into message queue.
 *                            -value 0: no wait.
 *                            -value 0xFFFFFFFF: wait forever.
 *
 *  @return     HAL_OK: Message send OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous data sending not finished yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get enough queue buffer space to push data.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_send_msg_nsc(icc_ns_adapter_t *picc_ns_adp, icc_msg_type_t *picc_msg, uint32_t timeout_us)
{
    return hal_icc_send_msg(picc_adp, picc_msg, timeout_us);
}

/**
 *  @brief The NSC function to sends a user application message with data to the LS platform via a
 *         specified HS to LS message queue by the interrupt mode.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  picc_msg  The message send request. The request includes the mesage type, queue index,
 *                        the data buffer and the data size for the message sending.
 *  @param[in]  callback  The call back function for the message data sending is done.
 *  @param[in]  callback_para  The application data will be passed back to the application with the callback function.
 *
 *  @return     HAL_OK: Message sending is started with OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous data sending not finished yet.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_send_msg_int_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_type_t *picc_msg,
                                                icc_user_msg_tx_callback_t callback, uint32_t callback_para)
{
    if (picc_msg->msg_q == ICC_HQ) {
        picc_ns_adp->h2l_hq_wr_done = (icc_nscb *)cmse_nsfptr_create(callback);
        picc_ns_adp->h2l_hq_wr_done_cb_arg = (void *)callback_para;
        return hal_icc_send_msg_int (picc_adp, picc_msg, icc_ns_send_h2l_hq_done, (uint32_t)picc_ns_adp);
    } else {
        picc_ns_adp->h2l_lq_wr_done = (icc_nscb *)cmse_nsfptr_create(callback);
        picc_ns_adp->h2l_lq_wr_done_cb_arg = (void *)callback_para;
        return hal_icc_send_msg_int (picc_adp, picc_msg, icc_ns_send_h2l_lq_done, (uint32_t)picc_ns_adp);
    }
}

/**
 *  @brief The NSC function to initials the ICC HAL message table buffer. The ICC HAL will look for the
 *         message handler in this table when a new ICC message is received.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  pmsg_tbl  The message table buffer.
 *  @param[in]  msg_tbl_size  The size(the maximum number of message) of this message table.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_set_hal_msg_tbl_nsc (icc_ns_adapter_t *picc_ns_adp, icc_user_msg_ns_entry_t *pmsg_tbl,
                         uint32_t msg_tbl_size)
{
    picc_ns_adp->phal_msg_tbl = pmsg_tbl;
    picc_ns_adp->hal_msg_tbl_size = msg_tbl_size;
}

/**
 *  @brief The NSC function to registers(adds) an ICC HAL message to the ICC HAL message table.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  msg  The ICC message type to be registered.
 *  @param[in]  callback  The ICC message handler function.
 *  @param[in]  cb_arg  The application data will be passed back to the application
 *                      with the callback function.
 *
 *  @return     HAL_OK: Message registration OK.
 *  @return     HAL_NOT_READY: The ICC HAL message table buffer did not been initialed yet.
 *  @return     HAL_NO_RESOURCE: No free entry of the table(table is full).
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_hal_msg_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t msg,
                                        icc_user_msg_handler_t callback, uint32_t cb_arg)
{
	uint32_t i;

    if (picc_ns_adp->phal_msg_tbl == (icc_user_msg_ns_entry_t *)NULL) {
        return HAL_NOT_READY;
    }

	for (i = 0; i < picc_ns_adp->hal_msg_tbl_size; i++) {
		if ((picc_ns_adp->phal_msg_tbl[i].callback != (icc_user_msg_nscb *)NULL)) {
            continue;
        }

		picc_ns_adp->phal_msg_tbl[i].msg = msg;
		picc_ns_adp->phal_msg_tbl[i].callback = (icc_user_msg_nscb *)cmse_nsfptr_create(callback);
		picc_ns_adp->phal_msg_tbl[i].cb_arg = cb_arg;
		return hal_icc_hal_msg_register(picc_adp, msg, (icc_user_msg_handler_t)icc_hal_msg_ind_nsc_wrapper,
                                    (uint32_t)picc_ns_adp);
	}
	return HAL_NO_RESOURCE;
}

/**
 *  @brief The NSC function to resets the HAL ICC message table. After the reset
 *         the HAL ICC command table is empty.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_hal_msg_unregister_all_nsc (icc_ns_adapter_t *picc_ns_adp)
{
	uint32_t i;

    if (picc_ns_adp->phal_msg_tbl == (icc_user_msg_ns_entry_t *)NULL) {
        return;
    }

	for (i = 0; i < picc_ns_adp->hal_msg_tbl_size; i++) {
        if (picc_ns_adp->phal_msg_tbl[i].callback != (icc_user_msg_nscb *)NULL) {
            hal_icc_hal_msg_unregister (picc_adp, picc_ns_adp->phal_msg_tbl[i].msg);
        }
		picc_ns_adp->phal_msg_tbl[i].msg = 0;
		picc_ns_adp->phal_msg_tbl[i].callback = (icc_user_msg_nscb *)NULL;
		picc_ns_adp->phal_msg_tbl[i].cb_arg = (uint32_t)0;
	}
}

/**
 *  @brief The NSC function to unregister(remove) an ICC HAL message from the message table.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  msg  The ICC HAL message type to be removed from the HAL message table.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_hal_msg_unregister_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t msg)
{
	uint32_t i;

    if (picc_ns_adp->phal_msg_tbl == (icc_user_msg_ns_entry_t *)NULL) {
        return;
    }

	for (i = 0; i < picc_ns_adp->hal_msg_tbl_size; i++) {
        if (msg == picc_ns_adp->phal_msg_tbl[i].msg) {
    		picc_ns_adp->phal_msg_tbl[i].msg = 0;
    		picc_ns_adp->phal_msg_tbl[i].callback = (icc_user_msg_nscb *)NULL;
            picc_ns_adp->phal_msg_tbl[i].cb_arg = (uint32_t)0;
            hal_icc_hal_msg_unregister (picc_adp, msg);
            break;
        }
	}
}

/**
 *  @brief The NSC function to initials the ICC user application message table buffer.
 *         When a new ICC message is received, the ICC HAL will search the command handler
 *         in the HAL message table first. If the command handler not be found in the
 *         HAL message table then it will search this user application ICC message table.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  pmsg_tbl  The message table buffer.
 *  @param[in]  msg_tbl_size  The size(the maximum number of messages) of this message table.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_set_msg_tbl_nsc (icc_ns_adapter_t *picc_ns_adp, icc_user_msg_ns_entry_t *pmsg_tbl,
                         uint32_t msg_tbl_size)
{
    picc_ns_adp->pmsg_tbl = pmsg_tbl;
    picc_ns_adp->msg_tbl_size = msg_tbl_size;
}

/**
 *  @brief The NSC function to registers(adds) an ICC user application message to the
 *         ICC user application message table.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  msg  The ICC message type to be registered.
 *  @param[in]  callback  The ICC message handler function of this new added message type.
 *  @param[in]  cb_arg  The application data will be passed back to the application
 *                      with the callback function.
 *
 *  @return     HAL_OK: Message registration OK.
 *  @return     HAL_NOT_READY: The ICC HAL message table buffer did not been initialed yet.
 *  @return     HAL_NO_RESOURCE: No free entry of the table(table is full).
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_msg_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t msg,
                                        icc_user_msg_handler_t callback, uint32_t cb_arg)
{
	uint32_t i;

    if (picc_ns_adp->pmsg_tbl == (icc_user_msg_ns_entry_t *)NULL) {
        return HAL_NOT_READY;
    }

	for (i = 0; i < picc_ns_adp->msg_tbl_size; i++) {
		if ((picc_ns_adp->pmsg_tbl[i].callback != (icc_user_msg_nscb *)NULL)) {
            continue;
        }

		picc_ns_adp->pmsg_tbl[i].msg = msg;
		picc_ns_adp->pmsg_tbl[i].callback = (icc_user_msg_nscb *)cmse_nsfptr_create(callback);
		picc_ns_adp->pmsg_tbl[i].cb_arg = cb_arg;
		return hal_icc_msg_register(picc_adp, msg, (icc_user_msg_handler_t)icc_msg_ind_nsc_wrapper,
                                    (uint32_t)picc_ns_adp);
	}
	return HAL_NO_RESOURCE;
}

/**
 *  @brief The NSC function to resets the user application ICC message table. After the reset
 *         the user application  ICC command table is empty.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_msg_unregister_all_nsc (icc_ns_adapter_t *picc_ns_adp)
{
	uint32_t i;

    if (picc_ns_adp->pmsg_tbl == (icc_user_msg_ns_entry_t *)NULL) {
        return;
    }

	for (i = 0; i < picc_ns_adp->msg_tbl_size; i++) {
        if (picc_ns_adp->pmsg_tbl[i].callback != (icc_user_msg_nscb *)NULL) {
            hal_icc_msg_unregister (picc_adp, picc_ns_adp->pmsg_tbl[i].msg);
        }
		picc_ns_adp->pmsg_tbl[i].msg = 0;
		picc_ns_adp->pmsg_tbl[i].callback = (icc_user_msg_nscb *)NULL;
		picc_ns_adp->pmsg_tbl[i].cb_arg = (uint32_t)0;
	}
}

/**
 *  @brief The NSC function to unregister(remove) an user application ICC message from the
 *         user application ICC message table.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  msg  The user application ICC message type to be removed
 *                   from the user application ICC message table.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_msg_unregister_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t msg)
{
	uint32_t i;

    if (picc_ns_adp->pmsg_tbl == (icc_user_msg_ns_entry_t *)NULL) {
        return;
    }

	for (i = 0; i < picc_ns_adp->msg_tbl_size; i++) {
        if (msg == picc_ns_adp->pmsg_tbl[i].msg) {
    		picc_ns_adp->pmsg_tbl[i].msg = 0;
    		picc_ns_adp->pmsg_tbl[i].callback = (icc_user_msg_nscb *)NULL;
            picc_ns_adp->pmsg_tbl[i].cb_arg = (uint32_t)0;
            hal_icc_msg_unregister (picc_adp, msg);
            break;
        }
	}
}

/**
 *  @brief The NSC function to sends a Ping command from HS to LS to check whether the LS ICC HAL
 *         is ready or not.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  ping_data  The data will be send with the ping command.
 *  @param[in]  timeout_us  The time period(in micro-second) for the
 *                          waiting of the response for this Pin command
 *                          from the LS platform.
 *
 *  @return     HAL_OK: Ping command sending OK.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the ping command
 *                           response from the LS platform.
 *  @returns result.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_ping_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t ping_data, uint32_t timeout_us)
{
    return hal_icc_ping (picc_adp, ping_data, timeout_us);
}

/**
 *  @brief The NSC function to gets a specified ICC hardware semaphore.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  sema_id  The index of the ICC hardware semaphore to get.
 *                       The ICC hardware implements 16 hardware semaphore.
 *                       So the valid value of this index is 0 ~ 15.
 *
 *  @return     HAL_OK: Got semaphore with OK.
 *  @return     HAL_ERR_PARA: The semaphore index value is invalid.
 *  @return     HAL_BUSY: The specified semaphore has been gotten.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_get_sema_nsc (icc_ns_adapter_t *picc_ns_adp, icc_sema_id_t sema_id)
{
    return hal_icc_stubs.hal_icc_get_sema (picc_adp, sema_id);
}

/**
 *  @brief The NSC function to frees a specified ICC hardware semaphore.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  sema_id  The index of the ICC hardware semaphore to get.
 *                       The valid value of this index is 0 ~ 15.
 *
 *  @return     HAL_OK: The semaphore is freed with OK.
 *  @return     HAL_ERR_PARA: The semaphore index value is invalid.
 *  @return     HAL_BUSY: The specified semaphore is owned by the LS platform.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_release_sema_nsc (icc_ns_adapter_t *picc_ns_adp, icc_sema_id_t sema_id)
{
    return hal_icc_stubs.hal_icc_release_sema (picc_adp, sema_id);
}

/**
 *  @brief The NSC function to writes a LS platform's register via the ICC command channel.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  addr  The address of the LS platform's register to be wrote.
 *  @param[in]  value  The 32-bits value to be wrote to the LS register.
 *
 *  @return     HAL_OK: LS register write OK.
 *  @return     HAL_BUSY: ICC command channel is busy, the previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge from the LS platform.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_ls_write_reg_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t addr, uint32_t value)
{
    return hal_icc_stubs.hal_icc_ls_write_cmd (picc_adp, addr, &value, 1);
}

/**
 *  @brief The NSC function to reads a LS platform's register via the ICC command channel.
 *
 *  @param[in]  picc_ns_adp  The non-secure ICC HAL adapter.
 *  @param[in]  addr  The address of the LS platform's register to read.
 *
 *  @return     The read register value. If error occurred, the return value will be 0x00.
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_icc_ls_read_reg_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t addr)
{
    uint32_t reg_val;

    reg_val = 0x00;
    hal_icc_stubs.hal_icc_ls_read_cmd (picc_adp, addr, &reg_val, 1);

    return reg_val;
}

// ======== start of new message architecture ========
/** 
 *  @brief To add message queue TX/RX request to the free message queue request pool.
 *  @param[in]  picc_ns_adp  The ICC HAL adapter.
 *  @param[in]  q_req  The message queue request to be added to the free pool.
 *
 *  @return     none.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_tx_req_pool_fill_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_tx_req_t *q_req)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_tx_req_pool_fill_rtl8195bhp_patch (picc_adp, q_req);
#else
    hal_icc_stubs.hal_icc_tx_req_pool_fill (picc_adp, q_req);
#endif
}

/**
 *  @brief The callback function for non-secure user application message indication.
 *         Since the ICC HAL (in secure region) cannot call non-secure function directly.
 *         So use this function to parse the received message type and then call the
 *         corresponding NSCB(non-secure callback) function.
 *
 *  @param[in]  msg_op  The received message word.
 *                           -bit[7:0]: The index of the target message queue.
 *                             -QID_L2H_HQ: LS to HS message Hi-queue.
 *                             -QID_L2H_LQ: LS to HS message Lo-queue.
 *                           -bit[15:8]: the message operland(optional).
 *                           -bit[23:16]: the message type.
 *  @param[in]  msg_size  The data length of this message.
 *  @param[in]  cb_arg  The non-secure ICC HAL adapter.
 *
 *  @returns    void.
 */
void icc_msg_tx_req_done_nsc_wrapper(icc_msg_tx_req_t *ptx_req)
{
    if (ptx_req->pnscallback == NULL) {
        return;
    }
    
    ((icc_msg_ns_tx_cb_t *)(cmse_nsfptr_create(ptx_req->pnscallback)))(ptx_req->nscallback_arg);
}

/** 
 *  @brief Submits a new message TX request to the message TX pending queue.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_req  The message TX request will to be submitted to the message TX pending queue.
 *
 *  @return     HAL_OK: TX request submission OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_msg_tx_req_submit_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_tx_req_t *q_req)
{
    icc_msg_tx_req_t *ptx_req;
    hal_status_t ret;

    ptx_req = hal_icc_tx_req_pool_get(picc_adp);
    if (ptx_req == NULL) {
        DBG_ICC_ERR("%s: no free TX Req\r\n", __func__);
        return HAL_NO_RESOURCE;
    }

    memcpy(ptx_req, q_req, sizeof(icc_msg_tx_req_t));
    ptx_req->callback_arg = (uint32_t)ptx_req;
    ptx_req->pcallback = (icc_msg_tx_cb_t)icc_msg_tx_req_done_nsc_wrapper;
    ret = hal_icc_msg_tx_req_submit (picc_adp, ptx_req);

    return ret;
}

/** 
 *  @brief Process the message TX request those pending in the message TX queue.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of message queue to handle.
 *
 *  @return     void
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_msg_tx_req_pending_process_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t q_id)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_msg_tx_req_pending_process_rtl8195bhp_patch (picc_adp, q_id);
#else
    hal_icc_stubs.hal_icc_msg_tx_req_pending_process (picc_adp, q_id);
#endif
}

/** 
 *  @brief Gets the 1st(head) RX request from the queue of RX request transfer is finished. 
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of the queue.
 *                    - 0: The high-queue for the transfer finished RX requests.
 *                    - 1: The low-queue for the transfer finished RX requests.
 *
 *  @return     The gotton RX request entity. If the queue is empty, it returns NULL.
 */
SECTION_NS_ENTRY_FUNC
picc_msg_rx_req_t NS_ENTRY hal_icc_msg_rx_req_done_deq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t q_id)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_icc_msg_rx_req_done_deq_rtl8195bhp_patch (picc_adp, q_id);
#else
    return hal_icc_stubs.hal_icc_msg_rx_req_done_deq (picc_adp, q_id);
#endif
}

/** 
 *  @brief Submits a new message RX request to the ICC HAL. This RX request will be 
 *         added to the RX request pending queue.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_req  The message RX request will to be added to the message RX request pending queue.
 *
 *  @return     HAL_OK: TX request submission OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_icc_msg_rx_req_submit_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_rx_req_t *q_req)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_icc_msg_rx_req_submit_rtl8195bhp_patch (picc_adp, q_req);
#else
    return hal_icc_stubs.hal_icc_msg_rx_req_submit (picc_adp, q_req);
#endif
}

/** 
 *  @brief Processes RX request entity in the RX requests pending queue. 
 *         It will start the ICC message RX state machine if the queue is not empty and the RX state is idle.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of the queue.
 *                    - 0: The high-queue for the pending RX requests.
 *                    - 1: The low-queue for the pending RX requests.
 *
 *  @return     The gotton RX request entity. It return NULL if the queue is empty.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_msg_rx_req_pending_process_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t q_id)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_msg_rx_req_pending_process_rtl8195bh_patch (picc_adp, q_id);
#else
    hal_icc_stubs.hal_icc_msg_rx_req_pending_process (picc_adp, q_id);
#endif
}

/** 
 *  @brief The button half of the ICC IRQ handler. 
 *         It process all ICC interrupt events.
 *
 *  @returns    void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_icc_irq_handler_bh_nsc (void)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_irq_handler_bh_rtl8195bhp_patch ();
#else
    hal_icc_stubs.hal_icc_irq_handler_bh();
#endif
}

/** @} */ /* End of group hs_hal_icc_nsc_api */

#endif // end of "#if defined(CONFIG_BUILD_SECURE)"
#endif  // end of "#if CONFIG_ICC_EN && CONFIG_ICC_NSC_EN"

