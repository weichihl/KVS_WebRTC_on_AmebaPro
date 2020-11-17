/**************************************************************************//**
 * @file     hal_icc.h
 * @brief    The HAL API implementation for the ICC device.
 * @version  V1.00
 * @date     2016-11-29
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
 *
 ******************************************************************************/

#ifndef _HAL_ICC_H_
#define _HAL_ICC_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/** 
 * @addtogroup ls_hal_icc ICC
 * @{
 */
__STATIC_INLINE void hal_icc_lock (hal_icc_adapter_t *icc_adapter)
{
    if (icc_adapter->enter_critical != NULL) {
        (icc_adapter->enter_critical)(icc_adapter);
    }
}

__STATIC_INLINE void hal_icc_unlock (hal_icc_adapter_t *icc_adapter)
{
    if (icc_adapter->exit_critical != NULL) {
        (icc_adapter->exit_critical)(icc_adapter);
    }
}

void hal_icc_enter_critical (hal_icc_adapter_t *icc_adapter);
void hal_icc_exit_critical (hal_icc_adapter_t *icc_adapter);
void hal_icc_reg_irq (irq_handler_t handler);
hal_status_t hal_icc_l2h_cmd_send (hal_icc_adapter_t *icc_adapter, uint32_t cmd_word0, 
                                   uint32_t cmd_word1, uint32_t timeout_us);
hal_status_t hal_icc_reset_queue (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
void hal_icc_h2l_cmd_ind_hook (hal_icc_adapter_t *icc_adapter, icc_cmd_ind pcallback, void *pdata);
void hal_icc_h2l_queue_ind_hook (hal_icc_adapter_t *icc_adapter, icc_q_ind pcallback, void *pdata);
void hal_icc_l2h_queue_ack_hook (hal_icc_adapter_t *icc_adapter, icc_q_ack pcallback, void *pdata);
void hal_icc_task_yield_hook (hal_icc_adapter_t *icc_adapter, icc_task_yield task_yield);
void hal_icc_init (hal_icc_adapter_t *icc_adapter);
void hal_icc_deinit (hal_icc_adapter_t *icc_adapter);
hal_status_t hal_icc_push_l2hq (hal_icc_adapter_t *icc_adapter, uint32_t q_id_size, 
                                uint8_t *pbuf, uint32_t timeout_us);
uint32_t hal_icc_pull_h2lq (hal_icc_adapter_t *icc_adapter, uint32_t q_id, 
                            uint8_t *pbuf, uint32_t size);
BOOL hal_icc_is_queue_empty (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
uint32_t hal_icc_get_queue_free_size (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
hal_status_t hal_icc_push_l2h_hq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, 
                                  uint32_t size, uint32_t timeout_us);
hal_status_t hal_icc_push_l2h_lq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, 
                                  uint32_t size, uint32_t timeout_us);
uint32_t hal_icc_pull_h2l_hq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size);
uint32_t hal_icc_pull_h2l_lq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size);
hal_status_t hal_icc_send_l2h_hq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size, 
                                  uint32_t timeout_us);
hal_status_t hal_icc_send_l2h_lq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size, 
                                  uint32_t timeout_us);
hal_status_t hal_icc_send_l2hq_int (hal_icc_adapter_t *icc_adapter, uint32_t q_id, icc_q_rw_req_t *send_req);
uint32_t hal_icc_send_l2hq_abort (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
hal_status_t hal_icc_send_l2h_hq_int (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *send_req);
hal_status_t hal_icc_send_l2h_lq_int (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *send_req);
uint32_t hal_icc_send_l2h_hq_abort (hal_icc_adapter_t *icc_adapter);
uint32_t hal_icc_send_l2h_lq_abort (hal_icc_adapter_t *icc_adapter);
uint32_t hal_icc_recv_h2lq (hal_icc_adapter_t *icc_adapter, uint32_t q_id_size, 
                            uint8_t *pbuf, uint32_t timeout_us);
uint32_t hal_icc_recv_h2l_hq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, 
                              uint32_t size, uint32_t timeout_us);
uint32_t hal_icc_recv_h2l_lq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, 
                              uint32_t size, uint32_t timeout_us);
hal_status_t hal_icc_recv_h2lq_int (hal_icc_adapter_t *icc_adapter, uint32_t q_id, icc_q_rw_req_t *rcv_req);
hal_status_t hal_icc_recv_h2l_hq_int (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *rcv_req);
hal_status_t hal_icc_recv_h2l_lq_int (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *rcv_req);
uint32_t hal_icc_recv_h2lq_abort (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
uint32_t hal_icc_recv_h2l_hq_abort (hal_icc_adapter_t *icc_adapter);
uint32_t hal_icc_recv_h2l_lq_abort (hal_icc_adapter_t *icc_adapter);
void hal_icc_set_hal_cmd_tbl(hal_icc_adapter_t *icc_adapter, icc_user_cmd_entry_t *pcmd_tbl, uint32_t cmd_tbl_size);
void hal_icc_set_cmd_tbl(hal_icc_adapter_t *icc_adapter, icc_user_cmd_entry_t *pcmd_tbl, uint32_t cmd_tbl_size);
hal_status_t hal_icc_hal_cmd_register(hal_icc_adapter_t *icc_adapter, uint8_t cmd,
                             icc_user_cmd_handler_t callback, uint32_t cb_arg);
void hal_icc_hal_cmd_unregister_all(hal_icc_adapter_t *icc_adapter);
void hal_icc_hal_cmd_unregister(hal_icc_adapter_t *icc_adapter, uint8_t cmd);
hal_status_t hal_icc_cmd_register(hal_icc_adapter_t *icc_adapter, uint8_t cmd,
                             icc_user_cmd_handler_t callback, uint32_t cb_arg);
void hal_icc_cmd_unregister_all(hal_icc_adapter_t *icc_adapter);
void hal_icc_cmd_unregister(hal_icc_adapter_t *icc_adapter, uint8_t cmd);
hal_status_t hal_icc_send_msg(hal_icc_adapter_t *icc_adapter, icc_msg_type_t *picc_msg, uint32_t timeout_us);
hal_status_t hal_icc_send_msg_int (hal_icc_adapter_t *icc_adapter, icc_msg_type_t *picc_msg,
                                   icc_user_msg_tx_callback_t callback, uint32_t callback_para);
void hal_icc_msg_queue_ind_hook (hal_icc_adapter_t *icc_adapter, icc_msg_q_ind_t pcallback);
void hal_icc_set_hal_msg_tbl (hal_icc_adapter_t *icc_adapter, icc_user_msg_entry_t *pmsg_tbl, uint32_t msg_tbl_size);
void hal_icc_set_msg_tbl (hal_icc_adapter_t *icc_adapter, icc_user_msg_entry_t *pmsg_tbl, 
                         uint32_t msg_tbl_size);
hal_status_t hal_icc_hal_msg_register (hal_icc_adapter_t *icc_adapter, uint8_t msg,
                             icc_user_msg_handler_t callback, uint32_t cb_arg);
void hal_icc_hal_msg_unregister_all (hal_icc_adapter_t *icc_adapter);
void hal_icc_hal_msg_unregister (hal_icc_adapter_t *icc_adapter, uint8_t msg);
hal_status_t hal_icc_msg_register (hal_icc_adapter_t *icc_adapter, uint8_t msg,
                             icc_user_msg_handler_t callback, uint32_t cb_arg);
void hal_icc_msg_unregister_all (hal_icc_adapter_t *icc_adapter);
void hal_icc_msg_unregister (hal_icc_adapter_t *icc_adapter, uint8_t msg);
void hal_icc_set_timeout(hal_icc_adapter_t *icc_adapter, uint32_t cmd_timeout_us);
hal_status_t hal_icc_ping (hal_icc_adapter_t *icc_adapter, uint32_t ping_data, uint32_t timeout_us);
void hal_icc_irq_handler_bh (void);
void hal_icc_init_cmd_q (hal_icc_adapter_t *icc_adapter, uint32_t *pbuf, uint8_t cmd_q_size);    

void hal_icc_tx_req_pool_fill (hal_icc_adapter_t *icc_adapter, icc_msg_tx_req_t *q_req);
picc_msg_tx_req_t hal_icc_tx_req_pool_get (hal_icc_adapter_t *icc_adapter);
void hal_icc_msg_tx_req_pending_process (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
hal_status_t hal_icc_msg_tx_req_submit (hal_icc_adapter_t *icc_adapter, icc_msg_tx_req_t *q_req);
hal_status_t hal_icc_msg_tx (hal_icc_adapter_t *icc_adapter, uint8_t msg_type, uint8_t frame_type, uint8_t q_id, 
                                    uint8_t *msg_data, uint16_t msg_len, icc_msg_tx_cb_t callback, uint32_t callback_arg);
void hal_icc_msg_rx_req_done_process (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
hal_status_t hal_icc_msg_rx_req_submit (hal_icc_adapter_t *icc_adapter, icc_msg_rx_req_t *q_req);
void hal_icc_msg_rx_req_pending_process (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
void hal_icc_msg_tbl_init (hal_icc_adapter_t *icc_adapter, icc_msg_entry_t *pmsg_tbl, uint8_t tbl_sz);
hal_status_t hal_icc_msg_tbl_reg (hal_icc_adapter_t *icc_adapter, uint8_t msg, uint8_t frame,
                                        icc_msg_rx_cb_t callback, uint32_t cb_arg);
void hal_icc_msg_tbl_unreg (hal_icc_adapter_t *icc_adapter, uint8_t msg, uint8_t frame);

#if defined(CONFIG_BUILD_RAM)
void _icc_l2h_q_ack_handler_patch (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
uint32_t _icc_h2l_q_ind_handler_patch (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
void ICC_IRQHandler_patch (void);
void hal_icc_irq_handler_bh_rtl8195blp_patch (void);
hal_status_t hal_icc_l2h_cmd_send_rtl8195blp_patch  (hal_icc_adapter_t *icc_adapter, uint32_t cmd_word0, 
                                                uint32_t cmd_word1, uint32_t timeout_us);
hal_status_t hal_icc_send_l2h_hq_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf,
                                                                uint32_t size, uint32_t timeout_us);
hal_status_t hal_icc_send_l2hq_int_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, uint32_t q_id,
                                                         icc_q_rw_req_t *send_req);
hal_status_t hal_icc_recv_h2lq_int_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, uint32_t q_id,
                                                                icc_q_rw_req_t *rcv_req);
hal_status_t hal_icc_send_msg_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, icc_msg_type_t *picc_msg,
                                                          uint32_t timeout_us);
hal_status_t hal_icc_send_msg_int_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, icc_msg_type_t *picc_msg,
                                              icc_user_msg_tx_callback_t callback, uint32_t callback_para);
void icc_cmd_rom_table_patch_init (hal_icc_adapter_t *icc_adapter);
void _icc_cmd_q_handler_patch (hal_icc_adapter_t *icc_adapter);
void hal_icc_init_cmd_q_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, uint32_t *pbuf, uint8_t cmd_q_size);
hal_status_t hal_icc_msg_rx_req_submit_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, icc_msg_rx_req_t *q_req);
icc_msg_tx_req_t *hal_icc_msg_tx_req_pending_deq_patch (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
void hal_icc_tx_req_pool_fill_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, icc_msg_tx_req_t *q_req);
picc_msg_tx_req_t hal_icc_tx_req_pool_get_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter);
void hal_icc_msg_tx_req_pending_process_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
hal_status_t hal_icc_msg_tx_req_submit_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, 
                                                                      icc_msg_tx_req_t *q_req);
void icc_msg_rx_ready_handler_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, uint8_t frame_type, uint8_t msg_type,
                                              uint8_t *pmsg_data, uint32_t msg_len);
picc_msg_rx_req_t hal_icc_msg_rx_req_done_deq_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
void hal_icc_msg_rx_req_done_process_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
void hal_icc_msg_rx_req_pending_process_rtl8195blp_patch (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
hal_status_t hal_icc_msg_tbl_reg_rtl8195blp_patch(hal_icc_adapter_t *icc_adapter, uint8_t msg, uint8_t frame,
                                        icc_msg_rx_cb_t callback, uint32_t cb_arg);
void hal_icc_msg_tbl_unreg_rtl8195blp_patch(hal_icc_adapter_t *icc_adapter, uint8_t msg, uint8_t frame);
#endif  // end of "#if defined(CONFIG_BUILD_RAM)"

/** @} */ /* End of group ls_hal_icc */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_ICC_H_"

