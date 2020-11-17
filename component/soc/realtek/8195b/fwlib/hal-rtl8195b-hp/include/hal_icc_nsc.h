/**************************************************************************//**
 * @file     hal_icc_nsc.h
 * @brief    The non-secure callable ICC HAL API implementation.
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

#ifndef _HAL_ICC_NSC_H_
#define _HAL_ICC_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_icc ICC
 * @{
 */

/**
  \brief  The function type of non-secure callback function for ICC HAL.
*/
typedef void __attribute__((cmse_nonsecure_call)) icc_nscb(void *arg, uint32_t tred_len);
/**
  \brief  The function type of non-secure callback function for ICC command indication.
*/
typedef uint32_t __attribute__((cmse_nonsecure_call)) icc_cmd_nscb(uint32_t cmd_word0, uint32_t cmd_word1, uint32_t arg);
/**
  \brief  The function type of non-secure callback function for ICC HAL message queue data indication.
*/
typedef void __attribute__((cmse_nonsecure_call)) icc_msg_q_ind_nscb(uint8_t msg_type, uint8_t msg_op,\
                                                                       uint8_t qid, uint32_t msg_size);
/**
  \brief  The function type of non-secure callback function for ICC user application message queue data indication.
*/
typedef void __attribute__((cmse_nonsecure_call)) icc_user_msg_nscb(uint32_t msg_op, uint32_t msg_size, uint32_t cb_arg);

/**
  \brief  The function type of the NS region ICC task wake up function which be called from S region.
*/
typedef void __attribute__((cmse_nonsecure_call)) icc_ns_task_up_nscb_t(void *arg);
typedef void __attribute__((cmse_nonsecure_call)) icc_ns_task_lock_nscb(void *arg);
typedef void __attribute__((cmse_nonsecure_call)) icc_ns_task_unlock_nscb(void *arg);

/**
  \brief  The function type of the a ICC message TX done NS region callback function which be called from S region.
*/
typedef void __attribute__((cmse_nonsecure_call)) icc_msg_ns_tx_cb_t(uint32_t cb_arg);


/**
  \brief  The type of an entity for an ICC HAL command and its handler on NS region.
*/
typedef struct icc_cmd_ns_entry_s {
    uint8_t cmd;            ///< the ICC command type
    icc_cmd_nscb *callback; ///< the ICC command handler function
    uint32_t cb_arg;        ///< the argument of the ICC command callback function
} icc_user_cmd_ns_entry_t, *picc_user_cmd_ns_entry_t;

/**
  \brief  The type of an entity for a ICC user application command and its handler on NS region.
*/
typedef struct icc_user_msg_ns_entry_s {
    uint8_t msg;                    ///< the ICC message type
    icc_user_msg_nscb *callback;    ///< the ICC command callback function
    uint32_t cb_arg;                ///< the argument of the ICC command callback function
} icc_user_msg_ns_entry_t, *picc_user_msg_ns_entry_t;

/**
  \brief  The type of a non-secure ICC HAL entity for ICC HAL operation.
*/
typedef struct icc_ns_adapter_s {
    icc_nscb *h2l_hq_wr_done;               ///< the call-back for H2L_HQ write done, for interrupt mode write queue
    icc_nscb *h2l_lq_wr_done;               ///< the call-back for H2L_LQ write done, for interrupt mode write queue
    icc_nscb *l2h_hq_rd_done;               ///< the call-back for L2H_HQ read done, for interrupt mode read queue
    icc_nscb *l2h_lq_rd_done;               ///< the call-back for L2H_LQ read done, for interrupt mode read queue
    void *h2l_hq_wr_done_cb_arg;            ///< the argument of the call-back for H2L_HQ write done
    void *h2l_lq_wr_done_cb_arg;            ///< the argument of the call-back for H2L_LQ write done
    void *l2h_hq_rd_done_cb_arg;            ///< the argument of the call-back for L2H_HQ read done
    void *l2h_lq_rd_done_cb_arg;            ///< the argument of the call-back for L2H_LQ read done
    icc_user_cmd_ns_entry_t *phal_cmd_tbl;  ///< the ICC HAL command table
    uint32_t hal_cmd_tbl_size;              ///< the ICC HAL command table size
    icc_user_msg_ns_entry_t *phal_msg_tbl;  ///< the ICC HAL message register table
    uint32_t hal_msg_tbl_size;              ///< the ICC HAL message register table size
    icc_user_cmd_ns_entry_t *pcmd_tbl;      ///< the ICC command table
    uint32_t cmd_tbl_size;                  ///< the ICC command table size
    icc_user_msg_ns_entry_t *pmsg_tbl;      ///< the ICC user message register table
    uint32_t msg_tbl_size;                  ///< the ICC user message register table size

    // B-Cut
    icc_task_yield task_yield;              /*!< the OS task yield function. The ICC HAL will call this function during
                                                a busy waitting, so the OS can do a force task switching to prevent other task
                                                starvation. The user application is responsible to hook this function on. */
    icc_task_up_t task_up;                          ///< the callback function (to wake up the ICC task) to handle IRQ
    void *task_up_arg;                              ///< the argument(or semaphore) of the ICC wake up callback function
    icc_enter_critical_t enter_critical;            ///< the callback function to get the mutext for the ICC HAL protection
    icc_exit_critical_t exit_critical;              ///< the callback function to release the mutext for the ICC HAL protection
    uint8_t mutex_locked;                           ///< mutex level control
     uint8_t msg_regtbl_sz;                          ///< ICC message register table size
    icc_msg_entry_t *pmsg_regtbl;                   ///< the HAL ICC message register table (RAM)
} icc_ns_adapter_t, *picc_ns_adapter_t;

/** @} */ /* End of group hs_hal_icc */

#if defined(CONFIG_BUILD_SECURE)
/**
 * @defgroup hs_hal_icc_nsc_api ICC HAL NSC APIs.
 * @ingroup hs_hal_icc
 * @{
 */

hal_status_t NS_ENTRY hal_icc_set_h2l_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size);
hal_status_t NS_ENTRY hal_icc_set_h2l_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size);
hal_status_t NS_ENTRY hal_icc_set_l2h_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size);
hal_status_t NS_ENTRY hal_icc_set_l2h_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size);
hal_status_t NS_ENTRY hal_icc_reset_queue_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_id);
void NS_ENTRY hal_icc_init_nsc (icc_ns_adapter_t *picc_ns_adp);
BOOL NS_ENTRY hal_icc_is_queue_empty_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_id);
uint32_t NS_ENTRY hal_icc_get_queue_free_size_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_id);
hal_status_t NS_ENTRY hal_icc_send_h2l_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf,
                                               uint32_t size, uint32_t timeout_us);
hal_status_t NS_ENTRY hal_icc_h2l_cmd_send_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t cmd_word0,
                                                uint32_t cmd_word1, uint32_t timeout_us);
hal_status_t NS_ENTRY hal_icc_send_h2l_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf,
                                               uint32_t size, uint32_t timeout_us);
hal_status_t NS_ENTRY hal_icc_send_h2l_hq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *send_req);
hal_status_t NS_ENTRY hal_icc_send_h2l_lq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *send_req);
uint32_t NS_ENTRY hal_icc_send_h2l_hq_abort_nsc (icc_ns_adapter_t *picc_ns_adp);
uint32_t NS_ENTRY hal_icc_send_h2l_lq_abort_nsc (icc_ns_adapter_t *picc_ns_adp);
uint32_t NS_ENTRY hal_icc_recv_l2h_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf,
                                           uint32_t size, uint32_t timeout_us);
uint32_t NS_ENTRY hal_icc_recv_l2h_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf,
                                           uint32_t size, uint32_t timeout_us);
hal_status_t NS_ENTRY hal_icc_recv_l2h_hq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *rcv_req);
hal_status_t NS_ENTRY hal_icc_recv_l2h_lq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *rcv_req);
uint32_t NS_ENTRY hal_icc_recv_l2h_hq_abort_nsc (icc_ns_adapter_t *picc_ns_adp);
uint32_t NS_ENTRY hal_icc_recv_l2h_lq_abort_nsc (icc_ns_adapter_t *picc_ns_adp);
void NS_ENTRY hal_icc_set_hal_cmd_tbl_nsc(icc_ns_adapter_t *picc_ns_adp, icc_user_cmd_ns_entry_t *pcmd_tbl,
                                          uint32_t cmd_tbl_size);
hal_status_t NS_ENTRY hal_icc_hal_cmd_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd,
                                                   icc_user_cmd_handler_t callback, uint32_t cb_arg);
void NS_ENTRY hal_icc_hal_cmd_unregister_all_nsc(icc_ns_adapter_t *picc_ns_adp);
void NS_ENTRY hal_icc_hal_cmd_unregister_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd);
void NS_ENTRY hal_icc_set_cmd_tbl_nsc(icc_ns_adapter_t *picc_ns_adp, icc_user_cmd_ns_entry_t *pcmd_tbl,
                                      uint32_t cmd_tbl_size);
hal_status_t NS_ENTRY hal_icc_cmd_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd,
                                          icc_user_cmd_handler_t callback, uint32_t cb_arg);
void NS_ENTRY hal_icc_cmd_unregister_all_nsc(icc_ns_adapter_t *picc_ns_adp);
void NS_ENTRY hal_icc_cmd_unregister_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd);
hal_status_t NS_ENTRY hal_icc_send_msg_nsc(icc_ns_adapter_t *picc_ns_adp, icc_msg_type_t *picc_msg,
                                           uint32_t timeout_us);
hal_status_t NS_ENTRY hal_icc_send_msg_int_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_type_t *picc_msg,
                                                icc_user_msg_tx_callback_t callback, uint32_t callback_para);
void NS_ENTRY hal_icc_set_hal_msg_tbl_nsc (icc_ns_adapter_t *picc_ns_adp, icc_user_msg_ns_entry_t *pmsg_tbl,
                         uint32_t msg_tbl_size);
hal_status_t NS_ENTRY hal_icc_hal_msg_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t msg,
                                        icc_user_msg_handler_t callback, uint32_t cb_arg);
void NS_ENTRY hal_icc_hal_msg_unregister_all_nsc (icc_ns_adapter_t *picc_ns_adp);
void NS_ENTRY hal_icc_hal_msg_unregister_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t msg);
void NS_ENTRY hal_icc_set_msg_tbl_nsc (icc_ns_adapter_t *picc_ns_adp, icc_user_msg_ns_entry_t *pmsg_tbl,
                                       uint32_t msg_tbl_size);
hal_status_t NS_ENTRY hal_icc_msg_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t msg,
                                        icc_user_msg_handler_t callback, uint32_t cb_arg);
void NS_ENTRY hal_icc_msg_unregister_all_nsc (icc_ns_adapter_t *picc_ns_adp);
void NS_ENTRY hal_icc_msg_unregister_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t msg);
hal_status_t NS_ENTRY hal_icc_ping_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t ping_data, uint32_t timeout_us);
hal_status_t NS_ENTRY hal_icc_get_sema_nsc (icc_ns_adapter_t *picc_ns_adp, icc_sema_id_t sema_id);
hal_status_t NS_ENTRY hal_icc_release_sema_nsc (icc_ns_adapter_t *picc_ns_adp, icc_sema_id_t sema_id);
hal_status_t NS_ENTRY hal_icc_ls_write_reg_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t addr, uint32_t value);
uint32_t NS_ENTRY hal_icc_ls_read_reg_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t addr);
//B-Cut
void NS_ENTRY hal_icc_tx_req_pool_fill_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_tx_req_t *q_req);
hal_status_t NS_ENTRY hal_icc_msg_tx_req_submit_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_tx_req_t *q_req);
void NS_ENTRY hal_icc_msg_tx_req_pending_process_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t q_id);
picc_msg_rx_req_t NS_ENTRY hal_icc_msg_rx_req_done_deq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t q_id);
hal_status_t NS_ENTRY hal_icc_msg_rx_req_submit_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_rx_req_t *q_req);
void NS_ENTRY hal_icc_msg_rx_req_pending_process_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t q_id);
void NS_ENTRY hal_icc_irq_handler_bh_nsc (void);

/** @} */ /* End of group hs_hal_icc_nsc_api */

#endif  // end of "#if defined(CONFIG_BUILD_SECURE)"

#if defined(CONFIG_BUILD_NONSECURE)
__STATIC_INLINE void hal_icc_lock (icc_ns_adapter_t *icc_adapter)
{
    if (icc_adapter->enter_critical != NULL) {
        (icc_adapter->enter_critical)(icc_adapter);
    }
}

__STATIC_INLINE void hal_icc_unlock (icc_ns_adapter_t *icc_adapter)
{
    if (icc_adapter->exit_critical != NULL) {
        (icc_adapter->exit_critical)(icc_adapter);
    }
}

hal_status_t hal_icc_set_h2l_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size);
hal_status_t hal_icc_set_h2l_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size);
hal_status_t hal_icc_set_l2h_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size);
hal_status_t hal_icc_set_l2h_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_start_addr, uint32_t q_size);
hal_status_t hal_icc_reset_queue_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_id);
void hal_icc_init_nsc (icc_ns_adapter_t *picc_ns_adp);
BOOL hal_icc_is_queue_empty_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_id);
uint32_t hal_icc_get_queue_free_size_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t q_id);
hal_status_t hal_icc_h2l_cmd_send_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t cmd_word0,
                                       uint32_t cmd_word1, uint32_t timeout_us);
hal_status_t hal_icc_send_h2l_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf, uint32_t size, uint32_t timeout_us);
hal_status_t hal_icc_send_h2l_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf, uint32_t size, uint32_t timeout_us);
hal_status_t hal_icc_send_h2l_hq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *send_req);
hal_status_t hal_icc_send_h2l_lq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *send_req);
uint32_t hal_icc_send_h2l_hq_abort_nsc (icc_ns_adapter_t *picc_ns_adp);
uint32_t hal_icc_send_h2l_lq_abort_nsc (icc_ns_adapter_t *picc_ns_adp);
uint32_t hal_icc_recv_l2h_hq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf, uint32_t size, uint32_t timeout_us);
uint32_t hal_icc_recv_l2h_lq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t *pbuf, uint32_t size, uint32_t timeout_us);
hal_status_t hal_icc_recv_l2h_hq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *rcv_req);
hal_status_t hal_icc_recv_l2h_lq_int_nsc (icc_ns_adapter_t *picc_ns_adp, volatile icc_q_rw_req_t *rcv_req);
uint32_t hal_icc_recv_l2h_hq_abort_nsc (icc_ns_adapter_t *picc_ns_adp);
uint32_t hal_icc_recv_l2h_lq_abort_nsc (icc_ns_adapter_t *picc_ns_adp);
void hal_icc_set_hal_cmd_tbl_nsc(icc_ns_adapter_t *picc_ns_adp, icc_user_cmd_ns_entry_t *pcmd_tbl,
                                          uint32_t cmd_tbl_size);
hal_status_t hal_icc_hal_cmd_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd,
                                                   icc_user_cmd_handler_t callback, uint32_t cb_arg);
void hal_icc_hal_cmd_unregister_all_nsc(icc_ns_adapter_t *picc_ns_adp);
void hal_icc_hal_cmd_unregister_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd);
void hal_icc_set_cmd_tbl_nsc(icc_ns_adapter_t *picc_ns_adp, icc_user_cmd_ns_entry_t *pcmd_tbl, uint32_t cmd_tbl_size);
hal_status_t hal_icc_cmd_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd,
                                 icc_user_cmd_handler_t callback, uint32_t cb_arg);
void hal_icc_cmd_unregister_all_nsc(icc_ns_adapter_t *picc_ns_adp);
void hal_icc_cmd_unregister_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t cmd);
hal_status_t hal_icc_send_msg_nsc(icc_ns_adapter_t *picc_ns_adp, icc_msg_type_t *picc_msg, uint32_t timeout_us);
hal_status_t hal_icc_send_msg_int_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_type_t *picc_msg,
                                       icc_user_msg_tx_callback_t callback, uint32_t callback_para);
void hal_icc_set_hal_msg_tbl_nsc (icc_ns_adapter_t *picc_ns_adp, icc_user_msg_ns_entry_t *pmsg_tbl,
                         uint32_t msg_tbl_size);
hal_status_t hal_icc_hal_msg_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t msg,
                                        icc_user_msg_handler_t callback, uint32_t cb_arg);
void hal_icc_hal_msg_unregister_all_nsc (icc_ns_adapter_t *picc_ns_adp);
void hal_icc_hal_msg_unregister_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t msg);
void hal_icc_set_msg_tbl_nsc (icc_ns_adapter_t *picc_ns_adp, icc_user_msg_ns_entry_t *pmsg_tbl,
                              uint32_t msg_tbl_size);
hal_status_t hal_icc_msg_register_nsc(icc_ns_adapter_t *picc_ns_adp, uint8_t msg,
                                 icc_user_msg_handler_t callback, uint32_t cb_arg);
void hal_icc_msg_unregister_all_nsc (icc_ns_adapter_t *picc_ns_adp);
void hal_icc_msg_unregister_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t msg);
hal_status_t hal_icc_ping_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t ping_data, uint32_t timeout_us);
hal_status_t hal_icc_get_sema_nsc (icc_ns_adapter_t *picc_ns_adp, icc_sema_id_t sema_id);
hal_status_t hal_icc_release_sema_nsc (icc_ns_adapter_t *picc_ns_adp, icc_sema_id_t sema_id);
hal_status_t hal_icc_ls_write_reg_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t addr, uint32_t value);
uint32_t hal_icc_ls_read_reg_nsc (icc_ns_adapter_t *picc_ns_adp, uint32_t addr);
//B-Cut
void hal_icc_tx_req_pool_fill_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_tx_req_t *q_req);
hal_status_t hal_icc_msg_tx_req_submit_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_tx_req_t *q_req);
void hal_icc_msg_tx_req_pending_process_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t q_id);
picc_msg_rx_req_t hal_icc_msg_rx_req_done_deq_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t q_id);
hal_status_t hal_icc_msg_rx_req_submit_nsc (icc_ns_adapter_t *picc_ns_adp, icc_msg_rx_req_t *q_req);
void hal_icc_msg_rx_req_pending_process_nsc (icc_ns_adapter_t *picc_ns_adp, uint8_t q_id);
void hal_icc_irq_handler_bh_nsc (void);

#define hal_icc_set_h2l_hq              hal_icc_set_h2l_hq_nsc
#define hal_icc_set_h2l_lq              hal_icc_set_h2l_lq_nsc
#define hal_icc_set_l2h_hq              hal_icc_set_l2h_hq_nsc
#define hal_icc_set_l2h_lq              hal_icc_set_l2h_lq_nsc
#define hal_icc_reset_queue             hal_icc_reset_queue_nsc
#define hal_icc_init                    hal_icc_init_nsc
#define hal_icc_is_queue_empty          hal_icc_is_queue_empty_nsc
#define hal_icc_get_queue_free_size     hal_icc_get_queue_free_size_nsc
#define hal_icc_h2l_cmd_send            hal_icc_h2l_cmd_send_nsc
#define hal_icc_send_h2l_hq             hal_icc_send_h2l_hq_nsc
#define hal_icc_send_h2l_lq             hal_icc_send_h2l_lq_nsc
#define hal_icc_send_h2l_hq_int         hal_icc_send_h2l_hq_int_nsc
#define hal_icc_send_h2l_lq_int         hal_icc_send_h2l_lq_int_nsc
#define hal_icc_send_h2l_hq_abort       hal_icc_send_h2l_hq_abort_nsc
#define hal_icc_send_h2l_lq_abort       hal_icc_send_h2l_lq_abort_nsc
#define hal_icc_recv_l2h_hq             hal_icc_recv_l2h_hq_nsc
#define hal_icc_recv_l2h_lq             hal_icc_recv_l2h_lq_nsc
#define hal_icc_recv_l2h_hq_int         hal_icc_recv_l2h_hq_int_nsc
#define hal_icc_recv_l2h_lq_int         hal_icc_recv_l2h_lq_int_nsc
#define hal_icc_recv_l2h_hq_abort       hal_icc_recv_l2h_hq_abort_nsc
#define hal_icc_recv_l2h_lq_abort       hal_icc_recv_l2h_lq_abort_nsc
#define hal_icc_set_hal_cmd_tbl         hal_icc_set_hal_cmd_tbl_nsc
#define hal_icc_hal_cmd_register        hal_icc_hal_cmd_register_nsc
#define hal_icc_hal_cmd_unregister_all  hal_icc_hal_cmd_unregister_all_nsc
#define hal_icc_hal_cmd_unregister      hal_icc_hal_cmd_unregister_nsc
#define hal_icc_set_cmd_tbl             hal_icc_set_cmd_tbl_nsc
#define hal_icc_cmd_register            hal_icc_cmd_register_nsc
#define hal_icc_cmd_unregister_all      hal_icc_cmd_unregister_all_nsc
#define hal_icc_cmd_unregister          hal_icc_cmd_unregister_nsc
#define hal_icc_send_msg                hal_icc_send_msg_nsc
#define hal_icc_send_msg_int            hal_icc_send_msg_int_nsc
#define hal_icc_set_hal_msg_tbl         hal_icc_set_hal_msg_tbl_nsc
#define hal_icc_hal_msg_register        hal_icc_hal_msg_register_nsc
#define hal_icc_hal_msg_unregister_all  hal_icc_hal_msg_unregister_all_nsc
#define hal_icc_hal_msg_unregister      hal_icc_hal_msg_unregister_nsc
#define hal_icc_set_msg_tbl             hal_icc_set_msg_tbl_nsc
#define hal_icc_msg_register            hal_icc_msg_register_nsc
#define hal_icc_msg_unregister_all      hal_icc_msg_unregister_all_nsc
#define hal_icc_msg_unregister          hal_icc_msg_unregister_nsc
#define hal_icc_ping                    hal_icc_ping_nsc
#define hal_icc_get_sema                hal_icc_get_sema_nsc
#define hal_icc_release_sema            hal_icc_release_sema_nsc
#define hal_icc_ls_write_reg            hal_icc_ls_write_reg_nsc
#define hal_icc_ls_read_reg             hal_icc_ls_read_reg_nsc

//B-Cut
#define hal_icc_tx_req_pool_fill        hal_icc_tx_req_pool_fill_nsc
#define hal_icc_msg_tx_req_submit       hal_icc_msg_tx_req_submit_nsc
#define hal_icc_msg_tx_req_pending_process  hal_icc_msg_tx_req_pending_process_nsc
#define hal_icc_msg_rx_req_done_deq     hal_icc_msg_rx_req_done_deq_nsc
#define hal_icc_msg_rx_req_submit       hal_icc_msg_rx_req_submit_nsc
#define hal_icc_msg_rx_req_pending_process  hal_icc_msg_rx_req_pending_process_nsc
#define hal_icc_irq_handler_bh          hal_icc_irq_handler_bh_nsc

#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_ICC_NSC_H_"

