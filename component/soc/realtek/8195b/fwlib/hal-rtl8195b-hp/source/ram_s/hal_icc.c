/**************************************************************************//**
 * @file     hal_icc.c
 * @brief    This ICC HAL API functions.
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
#include "hal_cache.h"
#include "memory.h"

#if CONFIG_ICC_EN

extern void ICC_IRQHandler_patch (void);
extern void icc_msg_q_ind_handler_patch (hal_icc_adapter_t *icc_adapter, icc_cmd_msg_q_t *icc_cmd);
extern hal_status_t wait_ls_icc_ready (uint32_t wait_us);

/**
 * @addtogroup hs_hal_icc ICC
 * @{
 */

/**
  * @brief The global ICC HAL adapter(management entity).
  */
hal_icc_adapter_t *picc_adp;

/**
 *  @brief To enter a critical code section, mainly it
 *         disable ICC interrupt to prevent race condition.
 *
 *  @param[in]  icc_adapter  The ICC adapter.
 *
 *  @returns    void.
 */
void hal_icc_enter_critical (hal_icc_adapter_t *icc_adapter)
{
    hal_icc_stubs.hal_icc_enter_critical (icc_adapter);
}

/**
 *  @brief To exit a critical code section, it will re-enable the ICC interrupt
 *         only when the exiting critical section is the top level.
 *
 *  @param[in]  icc_adapter  The ICC adapter.
 *
 *  @returns    void.
 */
void hal_icc_exit_critical (hal_icc_adapter_t *icc_adapter)
{
    hal_icc_stubs.hal_icc_exit_critical (icc_adapter);
}

/**
 *  @brief To register an interrupt handler for ICC HAL.
 *
 *  @param[in] handler  The IRQ handle function.
 *
 *  @returns    void.
 */
void hal_icc_reg_irq (irq_handler_t handler)
{
    hal_icc_stubs.hal_icc_reg_irq (handler);
}

/**
 *  @brief Sends an ICC command to the LS platform.
 *
 *  @param[in]  icc_adapter  The ICC adapter.
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
hal_status_t hal_icc_h2l_cmd_send (hal_icc_adapter_t *icc_adapter, uint32_t cmd_word0,
                                   uint32_t cmd_word1, uint32_t timeout_us)
{
    hal_status_t ret;

    ret = wait_ls_icc_ready (timeout_us);
    if (ret != HAL_OK) {
        return ret;
    }

#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_icc_h2l_cmd_send_rtl8195bhp_patch (icc_adapter, cmd_word0, cmd_word1, timeout_us);
#else
    return hal_icc_stubs.hal_icc_h2l_cmd_send (icc_adapter, cmd_word0, cmd_word1, timeout_us);
#endif
}

/**
 *  @brief Setup a message queue between HS platform and LS platform.
 *         The message queue is used to transfer a message type with a block
 *         of data between HS and LS platform.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_type  The queue type to be setup.
 *                      \arg QID_H2L_HQ HS to LS message Hi-queue.
 *                      \arg QID_H2L_LQ HS to LS message Lo-queue.
 *                      \arg QID_L2H_HQ LS to HS message Hi-queue.
 *                      \arg QID_L2H_LQ LS to HS message Lo-queue.
 *  @param[in]  q_start_addr  The mesage queue buffer start address.
 *  @param[in]  q_size  The queue buffer size.
 *
 *  @return     HAL_OK: Message queue setup OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge of the
 *                           message queue setup command from the LS platform.
 */
hal_status_t hal_icc_set_queue (hal_icc_adapter_t *icc_adapter, uint32_t q_type,
                                uint32_t q_start_addr, uint32_t q_size)
{
    return hal_icc_stubs.hal_icc_set_queue (icc_adapter, q_type, q_start_addr, q_size);
}

/**
 *  @brief Setup the HS to LS message Hi-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_start_addr  The mesage queue buffer start address.
 *  @param[in]  q_size  The queue buffer size.
 *
 *  @return     HAL_OK: Message queue setup OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge of the
 *                           message queue setup command from the LS platform.
 */
hal_status_t hal_icc_set_h2l_hq (hal_icc_adapter_t *icc_adapter, uint32_t q_start_addr, uint32_t q_size)
{
    return hal_icc_stubs.hal_icc_set_queue (icc_adapter, QID_H2L_HQ, q_start_addr,  q_size);
}

/**
 *  @brief Setup the HS to LS message Lo-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_start_addr  The mesage queue buffer start address.
 *  @param[in]  q_size  The queue buffer size.
 *
 *  @return     HAL_OK: Message queue setup OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge of the
 *                           message queue setup command from the LS platform.
 */
hal_status_t hal_icc_set_h2l_lq (hal_icc_adapter_t *icc_adapter, uint32_t q_start_addr, uint32_t q_size)
{
    return hal_icc_stubs.hal_icc_set_queue (icc_adapter, QID_H2L_LQ, q_start_addr,  q_size);
}

/**
 *  @brief Setup the LS to HS message Hi-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_start_addr  The mesage queue buffer start address.
 *  @param[in]  q_size  The queue buffer size.
 *
 *  @return     HAL_OK: Message queue setup OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge of the
 *                           message queue setup command from the LS platform.
 */
hal_status_t hal_icc_set_l2h_hq (hal_icc_adapter_t *icc_adapter, uint32_t q_start_addr, uint32_t q_size)
{
    return hal_icc_stubs.hal_icc_set_queue (icc_adapter, QID_L2H_HQ, q_start_addr,  q_size);
}

/**
 *  @brief Setup the LS to HS message Lo-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_start_addr  The mesage queue buffer start address.
 *  @param[in]  q_size  The queue buffer size.
 *
 *  @return     HAL_OK: Message queue setup OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge of the
 *                           message queue setup command from the LS platform.
 */
hal_status_t hal_icc_set_l2h_lq (hal_icc_adapter_t *icc_adapter, uint32_t q_start_addr, uint32_t q_size)
{
    return hal_icc_stubs.hal_icc_set_queue (icc_adapter, QID_L2H_LQ, q_start_addr,  q_size);
}

/**
 *  @brief Reset the specified message queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
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
hal_status_t hal_icc_reset_queue (hal_icc_adapter_t *icc_adapter, uint32_t q_id)
{
    return hal_icc_stubs.hal_icc_reset_queue (icc_adapter, q_id);
}

/**
 *  @brief Hooks a callback function for the interrupt of LS to HS command indication.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pcallback  The callback function.
 *  @param[in]  pdata  The application data will be passed back to the application with
 *                     the call back function.
 *
 *  @returns    void
 */
void hal_icc_l2h_cmd_ind_hook (hal_icc_adapter_t *icc_adapter, icc_cmd_ind pcallback, void *pdata)
{
//    hal_icc_stubs.hal_icc_l2h_cmd_ind_hook (icc_adapter, pcallback, pdata);
    icc_adapter->l2h_cmd_ind = pcallback;
    icc_adapter->l2h_cmd_ind_cb_para = pdata;
}

/**
 *  @brief Hooks a callback function for the interrupt of LS to HS message queue is updated.
 *         This callback function will be called when the LS platform fills new data
 *         into the message queue and updates the queue write pointer.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pcallback  The callback function.
 *  @param[in]  pdata  The application data will be passed back to the application with
 *                     the call back function.
 *
 *  @returns    void
 */
void hal_icc_l2h_queue_ind_hook (hal_icc_adapter_t *icc_adapter, icc_q_ind pcallback, void *pdata)
{
//    hal_icc_stubs.hal_icc_l2h_queue_ind_hook (icc_adapter, pcallback, pdata);
    icc_adapter->l2h_msg_q_ind = pcallback;
    icc_adapter->l2h_msg_q_ind_cb_para = pdata;
}

/**
 *  @brief Hooks a callback function for the interrupt of HS to LS message queue is acknowledged.
 *         This callback function will be called when the LS platform reads data from the message
 *         queue and updates the message queue read pointer.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pcallback  The callback function.
 *  @param[in]  pdata  The application data will be passed back to the application with
 *                     the call back function.
 *
 *  @returns    void
 */
void hal_icc_h2l_queue_ack_hook (hal_icc_adapter_t *icc_adapter, icc_q_ack pcallback, void *pdata)
{
//    hal_icc_stubs.hal_icc_h2l_queue_ack_hook (icc_adapter, pcallback, pdata);
    icc_adapter->h2l_msg_q_ack = pcallback;
    icc_adapter->h2l_msg_q_ack_cb_para = pdata;
}

/**
 *  @brief Hooks a OS task yield function. The ICC HAL will call this function during a busy waiting period.
 *         So the OS can schedule a task switching to prevent other tasks be starved.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  task_yield  The OS task yield function. The application is responsible to hoot this function.
 *
 *  @returns    void.
 */
void hal_icc_task_yield_hook (hal_icc_adapter_t *icc_adapter, icc_task_yield task_yield)
{
//    hal_icc_stubs.hal_icc_task_yield_hook (icc_adapter, task_yield);
    icc_adapter->task_yield = task_yield;
}

/**
  \brief   D-Cache Clean by address for ICC HAL
  \details Cleans D-Cache for the given address
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
void icc_dcache_clean_by_addr (uint32_t *addr, int32_t dsize)
{
    SCB_CleanDCache_by_Addr ((uint32_t *)((uint32_t)addr & 0xFFFFFFE0), (dsize + ((uint32_t)addr & 0x1F)));    
}

/**
  \brief   D-Cache Invalidate by address for ICC HAL
  \details Invalidates D-Cache for the given address
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/

void icc_dcache_invalidate_by_addr (uint32_t *addr, int32_t dsize)
{
    SCB_InvalidateDCache_by_Addr ((uint32_t *)((uint32_t)addr & 0xFFFFFFE0), (dsize + ((uint32_t)addr & 0x1F)));
}


/**
 *  @brief Initials the ICC HAL. This function should be called before
 *         any other ICC HAL operation.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @returns    void.
 */
void hal_icc_init (hal_icc_adapter_t *icc_adapter)
{
    picc_adp = icc_adapter;
    hal_icc_stubs.hal_icc_init (icc_adapter);    
    icc_adapter->enter_critical = (icc_enter_critical_t)hal_icc_stubs.hal_icc_enter_critical;
    icc_adapter->exit_critical = (icc_enter_critical_t)hal_icc_stubs.hal_icc_exit_critical;
//    icc_adapter->dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;
    icc_adapter->dcache_clean_by_addr = icc_dcache_clean_by_addr;
//    icc_adapter->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;
    icc_adapter->dcache_invalidate_by_addr = icc_dcache_invalidate_by_addr;
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    icc_adapter->cmd_q_sn = L2H_CMD_TG;
    icc_adapter->cmd_q_handler = (icc_cmd_q_handler_t)_icc_cmd_q_handler_patch;

    hal_icc_reg_irq ((irq_handler_t) ICC_IRQHandler_patch);
    hal_icc_msg_queue_ind_hook (icc_adapter, (icc_msg_q_ind_t)icc_msg_q_ind_handler_patch);    
    
    icc_adapter->h2l_msg_q_ack = _icc_h2l_q_ack_handler_patch;
    icc_adapter->h2l_msg_q_ack_cb_para = icc_adapter;
    icc_adapter->l2h_msg_q_ind = _icc_l2h_q_ind_handler_patch;
    icc_adapter->l2h_msg_q_ind_cb_para = icc_adapter;
    
    icc_cmd_rom_table_patch_init (icc_adapter);
#endif
}

/**
 *  @brief Disables the ICC HAL.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @returns    void.
 */
void hal_icc_deinit (hal_icc_adapter_t *icc_adapter)
{
    hal_icc_stubs.hal_icc_deinit (icc_adapter);
    picc_adp = (hal_icc_adapter_t *)NULL;
}

/**
 *  @brief Pushs(send) a block of data into the HS to LS message queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id_size  The destination queue index and the data size.
 *                           -bit[31:24]: The index of the target message queue.
 *                             -QID_H2L_HQ: HS to LS message Hi-queue.
 *                             -QID_H2L_LQ: HS to LS message Lo-queue.
 *                           -bit[23:0]: data size to push, in byte.
 *  @param[in]  pbuf  The data buffer to be send.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion of
 *                          data to be pushed into message queue.
 *                            -Value 0: no wait.
 *                            -Value 0xFFFFFFFF: wait forever.
 *
 *  @return     HAL_OK: Data push OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The buffer spack is not enough. The LS platform haven't
 *              finish the message read on this queue.
 *  @return     HAL_TIMEOUT: Timeout with didn't get enough queue buffer space to push data.
 */
hal_status_t hal_icc_push_h2lq (hal_icc_adapter_t *icc_adapter, uint32_t q_id_size,
                                uint8_t *pbuf, uint32_t timeout_us)
{
    return hal_icc_stubs.hal_icc_push_h2lq (icc_adapter, q_id_size, pbuf, timeout_us);
}

/**
 *  @brief Pulls(receives) a block of data from the LS to HS message queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The source queue for data to be read from.
 *                    \arg QID_L2H_HQ   LS to HS message Hi-queue.
 *                    \arg QID_L2H_LQ   LS to HS message Lo-queue.
 *  @param[in]  pbuf  The data buffer for the data reading from the message queue.
 *  @param[in]  size  The maximum data length to receive(the buffer size), in byte.
 *
 *  @returns    The actual size of data read from the message queue.
 */
uint32_t hal_icc_pull_l2hq (hal_icc_adapter_t *icc_adapter, uint32_t q_id,
                            uint8_t *pbuf, uint32_t size)
{
    return hal_icc_stubs.hal_icc_pull_l2hq (icc_adapter, q_id, pbuf, size);
}

/**
 *  @brief To check whether the specified message queue is empty or not.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of the message queue to be checked.
 *                      \arg QID_H2L_HQ HS to LS message Hi-queue.
 *                      \arg QID_H2L_LQ HS to LS message Lo-queue.
 *                      \arg QID_L2H_HQ LS to HS message Hi-queue.
 *                      \arg QID_L2H_LQ LS to HS message Lo-queue.
 *
 *  @return     FALSE: the specified message queue is not empty.
 *  @return     TRUE: the specified message queue is empty.
 */
BOOL hal_icc_is_queue_empty (hal_icc_adapter_t *icc_adapter, uint32_t q_id)
{
    return hal_icc_stubs.hal_icc_is_queue_empty (icc_adapter, q_id);
}

/**
 *  @brief Gets the free buffer size of the specified message queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of the specified message queue:
 *                      \arg QID_H2L_HQ HS to LS message Hi-queue.
 *                      \arg QID_H2L_LQ HS to LS message Lo-queue.
 *                      \arg QID_L2H_HQ LS to HS message Hi-queue.
 *                      \arg QID_L2H_LQ LS to HS message Lo-queue.
 *
 *  @returns    The free buffer size of the queue.
 */
uint32_t hal_icc_get_queue_free_size (hal_icc_adapter_t *icc_adapter, uint32_t q_id)
{
    return hal_icc_stubs.hal_icc_get_queue_free_size (icc_adapter, q_id);
}

/**
 *  @brief Pushs(send) a block of data into the HS to LS message Hi-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pbuf  The data buffer to be send.
 *  @param[in]  size  The size of the data to be pushed, in byte.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion
 *                          of data to be pushed into message queue.
 *                            -Value 0: no wait.
 *                            -Value 0xFFFFFFFF: wait forever.
 *
 *  @return     HAL_OK: Data push OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The buffer spack is not enough. The LS platform haven't
 *              finish the message read on this queue.
 *  @return     HAL_TIMEOUT: Timeout with didn't get enough queue buffer space to push data.
 */
hal_status_t hal_icc_push_h2l_hq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf,
                                  uint32_t size, uint32_t timeout_us)
{
    return hal_icc_stubs.hal_icc_push_h2lq (icc_adapter, (QID_H2L_HQ << 24) | (size & 0xFFFFFF), pbuf, timeout_us);
}

/**
 *  @brief Pushs(send) a block of data into the HS to LS message Lo-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pbuf  The data buffer to be send.
 *  @param[in]  size  The size of the data to be pushed, in byte.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion
 *                          of data to be pushed into message queue.
 *                            -Value 0: no wait.
 *                            -Value 0xFFFFFFFF: wait forever.
 *
 *  @return     HAL_OK: Data push OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The buffer spack is not enough. The LS platform haven't
 *              finish the message read on this queue.
 *  @return     HAL_TIMEOUT: Timeout with didn't get enough queue buffer space to push data.
 */
hal_status_t hal_icc_push_h2l_lq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf,
                                  uint32_t size, uint32_t timeout_us)
{
    return hal_icc_stubs.hal_icc_push_h2lq (icc_adapter, (QID_H2L_LQ << 24) | (size & 0xFFFFFF), pbuf, timeout_us);
}

/**
 *  @brief Pulls(receives) a block of data from the LS to HS message Hi-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pbuf  The data buffer for the data reading from the message queue.
 *  @param[in]  size  The maximum data length to receive(the buffer size), in byte.
 *
 *  @returns    The actual size of data read from the message queue.
 */
uint32_t hal_icc_pull_l2h_hq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size)
{
    return hal_icc_stubs.hal_icc_pull_l2hq (icc_adapter, QID_L2H_HQ, pbuf, size);
}

/**
 *  @brief Pulls(receives) a block of data from the LS to HS message Lo-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pbuf  The data buffer for the data reading from the message queue.
 *  @param[in]  size  The maximum data length to receive(the buffer size), in byte.
 *
 *  @returns    The actual size of data read from the message queue.
 */
uint32_t hal_icc_pull_l2h_lq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size)
{
    return hal_icc_stubs.hal_icc_pull_l2hq (icc_adapter, QID_L2H_LQ, pbuf, size);
}

/**
 *  @brief To send a block of data to LS via the HS to LS message Hi-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
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
hal_status_t hal_icc_send_h2l_hq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size,
                                  uint32_t timeout_us)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_icc_send_h2l_hq_rtl8195bhp_patch (icc_adapter, pbuf, size, timeout_us);    
#else
    return hal_icc_stubs.hal_icc_send_h2l_hq (icc_adapter, pbuf, size, timeout_us);
#endif
}

/**
 *  @brief To send a block of data to LS via the HS to LS message Lo-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
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
hal_status_t hal_icc_send_h2l_lq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size,
                                  uint32_t timeout_us)
{
    return hal_icc_stubs.hal_icc_send_h2l_lq (icc_adapter, pbuf, size, timeout_us);
}

/**
 *  @brief To send a block of data to LS via the HS to LS message queue by the interrupt mode.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of the message queue to for this sending.
 *                    \arg QID_H2L_HQ   HS to LS message Hi-queue.
 *                    \arg QID_H2L_LQ   HS to LS message Lo-queue.
 *  @param[in]  send_req  The message queue send request which contains the buffer address,
 *                        data length and the callback for queue sending is done.
 *
 *  @return     HAL_OK: Data send OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous data sending not finished yet.
 */
hal_status_t hal_icc_send_h2lq_int (hal_icc_adapter_t *icc_adapter, uint32_t q_id, icc_q_rw_req_t *send_req)
{
    return hal_icc_stubs.hal_icc_send_h2lq_int (icc_adapter, q_id, send_req);
}

/**
 *  @brief Aborts an interrupt mode message queue data sending on a specified message queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of the message queue to be aborted.
 *                    \arg QID_H2L_HQ   HS to LS message Hi-queue.
 *                    \arg QID_H2L_LQ   HS to LS message Lo-queue.
 *
 *  @returns    The length of data has been transfered.
 */
uint32_t hal_icc_send_h2lq_abort (hal_icc_adapter_t *icc_adapter, uint32_t q_id)
{
    return hal_icc_stubs.hal_icc_send_h2lq_abort (icc_adapter, q_id);
}

/**
 *  @brief To send a block of data to the LS platform via the HS to LS message Hi-queue
 *         by the interrupt mode.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  send_req  The message queue send request which contains the buffer address,
 *                        data length and the callback for queue sending is done.
 *
 *  @return     HAL_OK: Data push OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous data sending not finished yet.
 */
hal_status_t hal_icc_send_h2l_hq_int (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *send_req)
{
    return hal_icc_stubs.hal_icc_send_h2lq_int (icc_adapter, QID_H2L_HQ, send_req);
}

/**
 *  @brief To send a block of data to the LS platform via the HS to LS message Lo-queue
 *         by the interrupt mode.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  send_req  The message queue send request which contains the buffer address,
 *                        data length and the callback for queue sending is done.
 *
 *  @return     HAL_OK: Data push OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous data sending not finished yet.
 */
hal_status_t hal_icc_send_h2l_lq_int (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *send_req)
{
    return hal_icc_stubs.hal_icc_send_h2lq_int (icc_adapter, QID_H2L_LQ, send_req);
}

/**
 *  @brief Aborts interrupt mode message data sending on the HS to LS Hi-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @returns    The length of data has been transfered.
 */
uint32_t hal_icc_send_h2l_hq_abort (hal_icc_adapter_t *icc_adapter)
{
    return hal_icc_stubs.hal_icc_send_h2lq_abort (icc_adapter, QID_H2L_HQ);
}

/**
 *  @brief Aborts interrupt mode message data sending on the HS to LS Lo-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @returns    The length of data has been transfered.
 */
uint32_t hal_icc_send_h2l_lq_abort (hal_icc_adapter_t *icc_adapter)
{
    return hal_icc_stubs.hal_icc_send_h2lq_abort (icc_adapter, QID_H2L_LQ);
}

/**
 *  @brief Receives a block of data from the specified LS to HS message queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id_size  The source queue index and the data size.
 *                           -bit[31:24]: The index of the target message queue.
 *                             -QID_L2H_HQ: LS to HS message Hi-queue.
 *                             -QID_L2H_LQ: LS to HS message Lo-queue.
 *                           -bit[23:0]: the maximum data size to receive, in byte.
 *  @param[out]  pbuf  The buffer for the message data receiving.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion of
 *                          data receiving.
 *                            -value 0: no wait.
 *                            -value 0xFFFFFFFF: wait forever.
 *
 *  @return     The actual size of data received from the message queue.
 */
uint32_t hal_icc_recv_l2hq (hal_icc_adapter_t *icc_adapter, uint32_t q_id_size,
                            uint8_t *pbuf, uint32_t timeout_us)
{
    return hal_icc_stubs.hal_icc_recv_l2hq (icc_adapter, q_id_size, pbuf, timeout_us);
}

/**
 *  @brief Receives a block of data from the LS to HS message Hi-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[out]  pbuf  The buffer for the message data receiving.
 *  @param[in]  size  The maximum data size, in byte, to receive.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion of
 *                          data receiving.
 *                            -value 0: no wait.
 *                            -value 0xFFFFFFFF: wait forever.
 *
 *  @return     The actual size of data(in byte) received from the message queue.
 */
uint32_t hal_icc_recv_l2h_hq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf,
                              uint32_t size, uint32_t timeout_us)
{
    return hal_icc_stubs.hal_icc_recv_l2hq (icc_adapter, (QID_L2H_HQ << 24) | (size & 0xFFFFFF) , pbuf, timeout_us);
}

/**
 *  @brief Receives a block of data from the LS to HS message Lo-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[out]  pbuf  The buffer for the message data receiving.
 *  @param[in]  size  The maximum data size, in byte, to receive.
 *  @param[in]  timeout_us  The period, in micro-second, to wait the completion of
 *                          data receiving.
 *                            -value 0: no wait.
 *                            -value 0xFFFFFFFF: wait forever.
 *
 *  @return     The actual size of data(in byte) received from the message queue.
 */
uint32_t hal_icc_recv_l2h_lq (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf,
                              uint32_t size, uint32_t timeout_us)
{
    return hal_icc_stubs.hal_icc_recv_l2hq (icc_adapter, (QID_L2H_LQ << 24) | (size & 0xFFFFFF) , pbuf, timeout_us);
}

/**
 *  @brief Receives a block of data from a specified LS to HS message queue by the interrupt mode.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of the message queue for this receiving.
 *                    \arg QID_L2H_HQ   LS to HS message Hi-queue.
 *                    \arg QID_L2H_LQ   LS to HS message Lo-queue.
 *  @param[in]  rcv_req  The queue receive request which contains the buffer address, data length
 *                       and the callback for the message data receiving is done.
 *
 *  @return     HAL_OK: The message queue data receiving is started with OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous message data receiving not finished yet.
 */
hal_status_t hal_icc_recv_l2hq_int (hal_icc_adapter_t *icc_adapter, uint32_t q_id, icc_q_rw_req_t *rcv_req)
{
    return hal_icc_stubs.hal_icc_recv_l2hq_int (icc_adapter, q_id, rcv_req);
}

/**
 *  @brief Receives a block of data from the LS to HS message Hi-queue by the interrupt mode.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  rcv_req  The queue receive request which contains the buffer address, data length
 *                       and the callback for the message data receiving is done.
 *
 *  @return     HAL_OK: The message queue data receiving is started with OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous message data receiving not finished yet.
 */
hal_status_t hal_icc_recv_l2h_hq_int (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *rcv_req)
{
    return hal_icc_stubs.hal_icc_recv_l2hq_int (icc_adapter, QID_L2H_HQ, rcv_req);
}

/**
 *  @brief Receives a block of data from the LS to HS message Lo-queue by the interrupt mode.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  rcv_req  The queue receive request which contains the buffer address, data length
 *                       and the callback for the message data receiving is done.
 *
 *  @return     HAL_OK: The message queue data receiving is started with OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous message data receiving not finished yet.
 */
hal_status_t hal_icc_recv_l2h_lq_int (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *rcv_req)
{
    return hal_icc_stubs.hal_icc_recv_l2hq_int (icc_adapter, QID_L2H_LQ, rcv_req);
}

/**
 *  @brief Abort an interrupt mode message queue data receiving on the specified message queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of the message queue to be aborted.
 *                    \arg QID_L2H_HQ   LS to HS message Hi-queue.
 *                    \arg QID_L2H_LQ   LS to HS message Lo-queue.
 *
 *  @returns    The length of data has been received.
 */
uint32_t hal_icc_recv_l2hq_abort (hal_icc_adapter_t *icc_adapter, uint32_t q_id)
{
    return hal_icc_stubs.hal_icc_recv_l2hq_abort (icc_adapter, q_id);
}

/**
 *  @brief Abort an interrupt mode message queue data receiving on the LS to HS message Hi-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @returns    The length of data has been received.
 */
uint32_t hal_icc_recv_l2h_hq_abort (hal_icc_adapter_t *icc_adapter)
{
    return hal_icc_stubs.hal_icc_recv_l2hq_abort (icc_adapter, QID_L2H_HQ);
}

/**
 *  @brief Abort an interrupt mode message queue data receiving on the LS to HS message Lo-queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @returns    The length of data has been received.
 */
uint32_t hal_icc_recv_l2h_lq_abort (hal_icc_adapter_t *icc_adapter)
{
    return hal_icc_stubs.hal_icc_recv_l2hq_abort (icc_adapter, QID_L2H_LQ);
}

/**
 *  @brief Gets a specified ICC hardware semaphore.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  sema_id  The index of the ICC hardware semaphore to get.
 *                       The ICC hardware implements 16 hardware semaphore.
 *                       So the valid value of this index is 0 ~ 15.
 *
 *  @return     HAL_OK: Got semaphore with OK.
 *  @return     HAL_ERR_PARA: The semaphore index value is invalid.
 *  @return     HAL_BUSY: The specified semaphore has been gotten.
 */
hal_status_t hal_icc_get_sema (hal_icc_adapter_t *icc_adapter, icc_sema_id_t sema_id)
{
    return hal_icc_stubs.hal_icc_get_sema (icc_adapter, sema_id);
}

/**
 *  @brief Frees a specified ICC hardware semaphore.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  sema_id  The index of the ICC hardware semaphore to get.
 *                       The valid value of this index is 0 ~ 15.
 *
 *  @return     HAL_OK: The semaphore is freed with OK.
 *  @return     HAL_ERR_PARA: The semaphore index value is invalid.
 *  @return     HAL_BUSY: The specified semaphore is owned by the LS platform.
 */
hal_status_t hal_icc_release_sema (hal_icc_adapter_t *icc_adapter, icc_sema_id_t sema_id)
{
    return hal_icc_stubs.hal_icc_release_sema (icc_adapter, sema_id);
}

/**
 *  @brief Writes the LS platform memory or registers via the ICC command channel.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  addr  The address of the LS platform memory(registers) to be wrote.
 *  @param[in]  pdata  The 32-bits aligned data buffer for the LS memory(registers) writing.
 *  @param[in]  len_dw  The length of data to write, in double word(4-bytes).
 *
 *  @return     HAL_OK: LS memory(registers) write OK.
 *  @return     HAL_BUSY: ICC command channel is busy, the previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge from the LS platform.
 */
hal_status_t hal_icc_ls_write_cmd (hal_icc_adapter_t *icc_adapter, uint32_t addr, uint32_t *pdata, uint32_t len_dw)
{
    return hal_icc_stubs.hal_icc_ls_write_cmd (icc_adapter, addr, pdata, len_dw);
}

/**
 *  @brief Reads the LS platform memory or registers via the ICC command channel.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  addr  The address of the LS platform memory(registers) to read.
 *  @param[out]  pbuf  The 32-bits aligned data buffer for the reading of the LS memory(registers).
 *  @param[in]  len_dw  The length of data to read, in double word(4-bytes).
 *
 *  @return     HAL_OK: LS memory(registers) reads OK.
 *  @return     HAL_BUSY: ICC command channel is busy, the previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge from the LS platform.
 */
hal_status_t hal_icc_ls_read_cmd (hal_icc_adapter_t *icc_adapter, uint32_t addr, uint32_t *pbuf, uint32_t len_dw)
{
    return hal_icc_stubs.hal_icc_ls_read_cmd (icc_adapter, addr, pbuf, len_dw);
}

/**
 *  @brief Initials the ICC HAL command table buffer. The ICC HAL will look for the command handler
 *         in this table when a new ICC command is received.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pcmd_tbl  The command table buffer.
 *  @param[in]  cmd_tbl_size  The size(number of commands) of this command table.
 *
 *  @returns    void.
 */
void hal_icc_set_hal_cmd_tbl(hal_icc_adapter_t *icc_adapter, icc_user_cmd_entry_t *pcmd_tbl, uint32_t cmd_tbl_size)
{
    hal_icc_stubs.hal_icc_set_hal_cmd_tbl(icc_adapter, pcmd_tbl, cmd_tbl_size);
}

/**
 *  @brief Initials the ICC user application command table buffer.
 *         When a new ICC command is received, the ICC HAL will search the command handler
 *         in the HAL command table first. If the command handler not be found in the
 *         HAL command table then it will search this user application ICC command table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pcmd_tbl  The command table buffer.
 *  @param[in]  cmd_tbl_size  The size(number of commands) of this command table.
 *
 *  @returns    void.
 */
void hal_icc_set_cmd_tbl(hal_icc_adapter_t *icc_adapter, icc_user_cmd_entry_t *pcmd_tbl, uint32_t cmd_tbl_size)
{
    hal_icc_stubs.hal_icc_set_cmd_tbl(icc_adapter, pcmd_tbl, cmd_tbl_size);
}

/**
 *  @brief Registers(adds) an ICC HAL command to the ICC HAL command table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  cmd  The ICC command type to be registered.
 *  @param[in]  callback  The ICC command handler function.
 *  @param[in]  cb_arg  The application data will be passed back to the application with the callback function.
 *
 *  @return     HAL_OK: Command registration OK.
 *  @return     HAL_NOT_READY: The ICC HAL command table buffer did not been initialed yet.
 *  @return     HAL_NO_RESOURCE: No free entry of the table(table is full).
 */
hal_status_t hal_icc_hal_cmd_register(hal_icc_adapter_t *icc_adapter, uint8_t cmd, icc_user_cmd_handler_t callback,
                                  uint32_t cb_arg)
{
    return hal_icc_stubs.hal_icc_hal_cmd_register(icc_adapter, cmd, callback, cb_arg);
}

/**
 *  @brief Reset the ICC HAL command table. After reset the HAL command table is empty.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @returns    void.
 */
void hal_icc_hal_cmd_unregister_all(hal_icc_adapter_t *icc_adapter)
{
    hal_icc_stubs.hal_icc_hal_cmd_unregister_all(icc_adapter);
}

/**
 *  @brief Un-register(remove) an ICC HAL command from the command table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  cmd  The ICC HAL command type to be removed from the HAL command table.
 *
 *  @returns    void.
 */
void hal_icc_hal_cmd_unregister(hal_icc_adapter_t *icc_adapter, uint8_t cmd)
{
    hal_icc_stubs.hal_icc_hal_cmd_unregister(icc_adapter, cmd);
}

/**
 *  @brief Registers(add) an ICC command to the user application ICC command table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  cmd  The user application ICC command type to be registered.
 *  @param[in]  callback  The handler function of this user application ICC command type.
 *  @param[in]  cb_arg  The application data will be passed back to the application with the callback function.
 *
 *  @return     HAL_OK: Command registration OK.
 *  @return     HAL_NOT_READY: The user application ICC command table buffer did not been initialed yet.
 *  @return     HAL_NO_RESOURCE: No free entry of the table(table is full).
 */
hal_status_t hal_icc_cmd_register(hal_icc_adapter_t *icc_adapter, uint8_t cmd, icc_user_cmd_handler_t callback,
                                  uint32_t cb_arg)
{
    return hal_icc_stubs.hal_icc_cmd_register(icc_adapter, cmd, callback, cb_arg);
}

/**
 *  @brief Resets the user application ICC command table. After the reset
 *         the user application ICC command table is empty.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @returns    void.
 */
void hal_icc_cmd_unregister_all(hal_icc_adapter_t *icc_adapter)
{
    hal_icc_stubs.hal_icc_cmd_unregister_all(icc_adapter);
}

/**
 *  @brief Unregisters(remove) an ICC command from the user application ICC command table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  cmd  The ICC command type to be removed from the user application ICC command table.
 *
 *  @returns    void.
 */
void hal_icc_cmd_unregister(hal_icc_adapter_t *icc_adapter, uint8_t cmd)
{
    hal_icc_stubs.hal_icc_cmd_unregister(icc_adapter, cmd);
}

/**
 *  @brief Sends a user application message with data to the LS platform via a
 *         specified HS to LS message queue.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
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
hal_status_t hal_icc_send_msg(hal_icc_adapter_t *icc_adapter, icc_msg_type_t *picc_msg,
                              uint32_t timeout_us)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_icc_send_msg_rtl8195bhp_patch (icc_adapter, picc_msg, timeout_us);
#else
    return hal_icc_stubs.hal_icc_send_msg(icc_adapter, picc_msg, timeout_us);
#endif
}

/**
 *  @brief Sends a user application message with data to the LS platform via a
 *         specified HS to LS message queue by the interrupt mode.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  picc_msg  The message send request. The request includes the mesage type, queue index,
 *                        the data buffer and the data size for the message sending.
 *  @param[in]  callback  The call back function for the message data sending is done.
 *  @param[in]  callback_para  The application data will be passed back to the application with the callback function.
 *
 *  @return     HAL_OK: Message sending is started with OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_BUSY: The previous data sending not finished yet.
 */
hal_status_t hal_icc_send_msg_int (hal_icc_adapter_t *icc_adapter, icc_msg_type_t *picc_msg,
                                   icc_user_msg_tx_callback_t callback, uint32_t callback_para)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)    
    return hal_icc_send_msg_int_rtl8195bhp_patch (icc_adapter, picc_msg, callback, callback_para);
#else
    return hal_icc_stubs.hal_icc_send_msg_int (icc_adapter, picc_msg, callback, callback_para);
#endif
}

/**
 *  @brief Hooks an user application handler function for message queue indication command.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pcallback  The callback function.
 *
 *  @returns    void
 */
void hal_icc_msg_queue_ind_hook (hal_icc_adapter_t *icc_adapter, icc_msg_q_ind_t pcallback)
{
    hal_icc_stubs.hal_icc_msg_queue_ind_hook (icc_adapter, pcallback);
}

/**
 *  @brief Initials the ICC HAL message table buffer. The ICC HAL will look for the
 *         message handler in this table when a new ICC message is received.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pmsg_tbl  The message table buffer.
 *  @param[in]  msg_tbl_size  The size(the maximum number of message) of this message table.
 *
 *  @returns    void.
 */
void hal_icc_set_hal_msg_tbl (hal_icc_adapter_t *icc_adapter, icc_user_msg_entry_t *pmsg_tbl, uint32_t msg_tbl_size)
{
    hal_icc_stubs.hal_icc_set_hal_msg_tbl (icc_adapter, pmsg_tbl, msg_tbl_size);
}

/**
 *  @brief Registers(adds) an ICC HAL message to the ICC HAL message table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  msg  The ICC message type to be registered.
 *  @param[in]  callback  The ICC message handler function.
 *  @param[in]  cb_arg  The application data will be passed back to the application
 *                      with the callback function.
 *
 *  @return     HAL_OK: Message registration OK.
 *  @return     HAL_NOT_READY: The ICC HAL message table buffer did not been initialed yet.
 *  @return     HAL_NO_RESOURCE: No free entry of the table(table is full).
 */
hal_status_t hal_icc_hal_msg_register (hal_icc_adapter_t *icc_adapter, uint8_t msg,
                             icc_user_msg_handler_t callback, uint32_t cb_arg)
{
    return hal_icc_stubs.hal_icc_hal_msg_register(icc_adapter, msg, callback, cb_arg);
}

/**
 *  @brief Resets the HAL ICC message table. After the reset
 *         the HAL ICC command table is empty.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @returns    void.
 */
void hal_icc_hal_msg_unregister_all (hal_icc_adapter_t *icc_adapter)
{
    hal_icc_stubs.hal_icc_hal_msg_unregister_all (icc_adapter);
}


/**
 *  @brief Un-register(remove) an ICC HAL message from the message table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  msg  The ICC HAL message type to be removed from the HAL message table.
 *
 *  @returns    void.
 */
void hal_icc_hal_msg_unregister (hal_icc_adapter_t *icc_adapter, uint8_t msg)
{
    hal_icc_stubs.hal_icc_hal_msg_unregister (icc_adapter, msg);
}

/**
 *  @brief Initials the ICC user application message table buffer.
 *         When a new ICC message is received, the ICC HAL will search the command handler
 *         in the HAL message table first. If the command handler not be found in the
 *         HAL message table then it will search this user application ICC message table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pmsg_tbl  The message table buffer.
 *  @param[in]  msg_tbl_size  The size(the maximum number of messages) of this message table.
 *
 *  @returns    void.
 */
void hal_icc_set_msg_tbl (hal_icc_adapter_t *icc_adapter, icc_user_msg_entry_t *pmsg_tbl,
                         uint32_t msg_tbl_size)
{
    hal_icc_stubs.hal_icc_set_msg_tbl (icc_adapter, pmsg_tbl, msg_tbl_size);
}

/**
 *  @brief Registers(adds) an ICC user application message to the
 *         ICC user application message table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  msg  The ICC message type to be registered.
 *  @param[in]  callback  The ICC message handler function of this new added message type.
 *  @param[in]  cb_arg  The application data will be passed back to the application
 *                      with the callback function.
 *
 *  @return     HAL_OK: Message registration OK.
 *  @return     HAL_NOT_READY: The ICC HAL message table buffer did not been initialed yet.
 *  @return     HAL_NO_RESOURCE: No free entry of the table(table is full).
 */
hal_status_t hal_icc_msg_register (hal_icc_adapter_t *icc_adapter, uint8_t msg,
                             icc_user_msg_handler_t callback, uint32_t cb_arg)
{
    return hal_icc_stubs.hal_icc_msg_register(icc_adapter, msg, callback, cb_arg);
}

/**
 *  @brief Resets the user application ICC message table. After the reset
 *         the user application  ICC command table is empty.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @returns    void.
 */
void hal_icc_msg_unregister_all (hal_icc_adapter_t *icc_adapter)
{
    hal_icc_stubs.hal_icc_msg_unregister_all (icc_adapter);
}

/**
 *  @brief Un-register(remove) an user application ICC message from the
 *         user application ICC message table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  msg  The user application ICC message type to be removed
 *                   from the user application ICC message table.
 *
 *  @returns    void.
 */
void hal_icc_msg_unregister (hal_icc_adapter_t *icc_adapter, uint8_t msg)
{
    hal_icc_stubs.hal_icc_msg_unregister (icc_adapter, msg);
}

/**
 *  @brief To set the timeout period for ICC command completion waitting.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  cmd_timeout_us  The time period(in micro-second) for the
 *                              waiting of an ICC command sending completion.
 *  @param[in]  ls_read_timeout_us  The time period(in micro-second) for the
 *                                  waiting of an LS register reading command completion.
 *
 *  @returns    void.
 */
void hal_icc_set_timeout(hal_icc_adapter_t *icc_adapter, uint32_t cmd_timeout_us,
                         uint32_t ls_read_timeout_us)
{
    hal_icc_stubs.hal_icc_set_timeout(icc_adapter, cmd_timeout_us, ls_read_timeout_us);
}

/**
 *  @brief Sends a Ping command from HS to LS to check whether the LS ICC HAL
 *         is ready or not.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
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
hal_status_t hal_icc_ping (hal_icc_adapter_t *icc_adapter, uint32_t ping_data, uint32_t timeout_us)
{
    return hal_icc_stubs.hal_icc_ping (icc_adapter, ping_data, timeout_us);
}

#if !defined (CONFIG_BUILD_NONSECURE)
/**
 *  @brief Writes a LS platform's register via the ICC command channel.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  addr  The address of the LS platform's register to be wrote.
 *  @param[in]  value  The 32-bits value to be wrote to the LS register.
 *
 *  @return     HAL_OK: LS register write OK.
 *  @return     HAL_BUSY: ICC command channel is busy, the previous ICC command sending not finish yet.
 *  @return     HAL_TIMEOUT: Timeout with didn't get the acknowledge from the LS platform.
 */
hal_status_t hal_icc_ls_write_reg (hal_icc_adapter_t *icc_adapter, uint32_t addr, uint32_t value)
{
    return hal_icc_stubs.hal_icc_ls_write_cmd (icc_adapter, addr, &value, 1);
}

/**
 *  @brief Reads a LS platform's register via the ICC command channel.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  addr  The address of the LS platform's register to read.
 *
 *  @return     The read register value. If error occurred, the return value will be 0x00.
 */
uint32_t hal_icc_ls_read_reg (hal_icc_adapter_t *icc_adapter, uint32_t addr)
{
    uint32_t reg_val;

    reg_val = 0x00;
    hal_icc_stubs.hal_icc_ls_read_cmd (icc_adapter, addr, &reg_val, 1);

    return reg_val;
}
#endif  // end of "#if !defined (CONFIG_BUILD_NONSECURE)"

/** 
 *  @brief The button half of the ICC IRQ handler. 
 *         It process all ICC interrupt events.
 *
 *  @returns    void.
 */
void hal_icc_irq_handler_bh (void)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_irq_handler_bh_rtl8195bhp_patch ();
#else
    hal_icc_stubs.hal_icc_irq_handler_bh();
#endif
}

/** 
 *  @brief Initial the ICC command queue. Assign the ICC command queue buffer and the queue size.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pbuf  The ICC command queue buffer.
 *  @param[in]  cmd_q_size  The size(number of ICC commands) of the ICC command queue. An ICC command
 *                          uses 2 double words of space.
 *
 *  @return     none.
 */
void hal_icc_init_cmd_q (hal_icc_adapter_t *icc_adapter, uint32_t *pbuf, uint8_t cmd_q_size)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_init_cmd_q_rtl8195bhp_patch (icc_adapter, pbuf, cmd_q_size);
#else
    hal_icc_stubs.hal_icc_init_cmd_q (icc_adapter, pbuf, cmd_q_size);
#endif

}

// ======== start of new message architecture ========

/** 
 *  @brief To add message queue TX/RX request to the free message queue request pool.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_req  The message queue request to be added to the free pool.
 *
 *  @return     none.
 */
void hal_icc_tx_req_pool_fill (hal_icc_adapter_t *icc_adapter, icc_msg_tx_req_t *q_req)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_tx_req_pool_fill_rtl8195bhp_patch (icc_adapter, q_req);
#else
    hal_icc_stubs.hal_icc_tx_req_pool_fill (icc_adapter, q_req);
#endif
}

/** 
 *  @brief To takes out a message queue TX request from the message queue request pool.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *
 *  @return     The gotton message queue TX request entity.
 */
picc_msg_tx_req_t hal_icc_tx_req_pool_get (hal_icc_adapter_t *icc_adapter)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_icc_tx_req_pool_get_rtl8195bhp_patch (icc_adapter);
#else
    return hal_icc_stubs.hal_icc_tx_req_pool_get (icc_adapter);
#endif
}

/** 
 *  @brief Submits a new message TX request to the message TX pending queue.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_req  The message TX request will to be submitted to the message TX pending queue.
 *
 *  @return     HAL_OK: TX request submission OK.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 */
hal_status_t hal_icc_msg_tx_req_submit (hal_icc_adapter_t *icc_adapter, icc_msg_tx_req_t *q_req)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_icc_msg_tx_req_submit_rtl8195bhp_patch (icc_adapter, q_req);
#else
    return hal_icc_stubs.hal_icc_msg_tx_req_submit (icc_adapter, q_req);
#endif
}

/** 
 *  @brief Sends a ICC message (with message data) to the peer.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
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
hal_status_t hal_icc_msg_tx (hal_icc_adapter_t *icc_adapter, uint8_t msg_type, uint8_t frame_type, uint8_t q_id, 
                                    uint8_t *msg_data, uint16_t msg_len, icc_msg_tx_cb_t callback, uint32_t callback_arg)
{
    icc_msg_tx_req_t *ptx_req;
    hal_status_t ret;

    if ((msg_data == NULL) && (msg_len > 0)) {
        DBG_ICC_ERR("%s: msg_buf is NULL\r\n", __func__);
        return HAL_ERR_PARA;
    }

    hal_icc_lock(icc_adapter);
    ptx_req = hal_icc_tx_req_pool_get(icc_adapter);
    hal_icc_unlock(icc_adapter);
    if (ptx_req == NULL) {
        DBG_ICC_ERR("%s: no free TX Req\r\n", __func__);
        return HAL_NO_RESOURCE;
    }

    ptx_req->msg_type = msg_type;
    ptx_req->frame_type = frame_type;
    ptx_req->q_id = q_id;
    ptx_req->msg_len = msg_len;
    ptx_req->msg_data = msg_data;
    ptx_req->pcallback = callback;
    ptx_req->callback_arg = callback_arg;
    hal_icc_lock(icc_adapter);
    ret = hal_icc_msg_tx_req_submit (icc_adapter, ptx_req);
    hal_icc_unlock(icc_adapter);

    return ret;
}

/** 
 *  @brief Process the message TX request those pending in the message TX queue.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of message queue to handle.
 *
 *  @return     void
 */
void hal_icc_msg_tx_req_pending_process (hal_icc_adapter_t *icc_adapter, uint8_t q_id)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_msg_tx_req_pending_process_rtl8195bhp_patch (icc_adapter, q_id);
#else
    hal_icc_stubs.hal_icc_msg_tx_req_pending_process (icc_adapter, q_id);
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
picc_msg_rx_req_t hal_icc_msg_rx_req_done_deq (hal_icc_adapter_t *icc_adapter, uint8_t q_id)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_icc_msg_rx_req_done_deq_rtl8195bhp_patch (icc_adapter, q_id);
#else
    return hal_icc_stubs.hal_icc_msg_rx_req_done_deq (icc_adapter, q_id);
#endif
}

/** 
 *  @brief The call back function of a ICC message header receiving. It parses the message type
 *         and call the corresponding handler and then should switch to the RX message data stage.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  icc_cmd  The new ICC message indication command.
 *
 *  @return     none.
 */
void icc_msg_rx_ready_handler (hal_icc_adapter_t *icc_adapter, uint8_t frame_type, uint8_t msg_type,
                                              uint8_t *pmsg_data, uint32_t msg_len)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    icc_msg_rx_ready_handler_rtl8195bhp_patch (icc_adapter, frame_type, msg_type, pmsg_data, msg_len);
#else
    hal_icc_stubs.icc_msg_rx_ready_handler (icc_adapter, frame_type, msg_type, pmsg_data, msg_len);
#endif
}

/** 
 *  @brief Process all the RX requests in the transfer finished RX requests queue. 
 *         This function should be called from the ICC task main loop.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  q_id  The index of the queue.
 *                    - 0: The high-queue for the transfer finished RX requests.
 *                    - 1: The low-queue for the transfer finished RX requests.
 *
 *  @return     The gotton RX request entity. If the queue is empty, it returns NULL.
 */
void hal_icc_msg_rx_req_done_process (hal_icc_adapter_t *icc_adapter, uint8_t q_id)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_msg_rx_req_done_process_rtl8195bh_patch (icc_adapter, q_id);
#else
    hal_icc_stubs.hal_icc_msg_rx_req_done_process (icc_adapter, q_id);
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
hal_status_t hal_icc_msg_rx_req_submit (hal_icc_adapter_t *icc_adapter, icc_msg_rx_req_t *q_req)
{
    hal_status_t ret;
    uint8_t q_id;
    uint8_t task_up = 0;
    
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    ret = hal_icc_msg_rx_req_submit_rtl8195bhp_patch (icc_adapter, q_req);
#else
    q_id = q_req->q_id;
    if (icc_adapter->rx_q_h[q_id] == NULL) {
        // message queue is empty, this is the 1st message RX request
        task_up = 1;
    }

    ret = hal_icc_stubs.hal_icc_msg_rx_req_submit (icc_adapter, q_req);
    /* workaround for ROM code's bug: didn't wake up the ICC task to process 
       pending RX Req for the 1st RX Req is submitted */
    if ((ret == HAL_OK) && (task_up)) {
        if (icc_adapter->task_up != NULL) {
            (icc_adapter->task_up)(icc_adapter->task_up_arg);        
        }
    }
#endif

    return ret;
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
void hal_icc_msg_rx_req_pending_process (hal_icc_adapter_t *icc_adapter, uint8_t q_id)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_msg_rx_req_pending_process_rtl8195bh_patch (icc_adapter, q_id);
#else
    hal_icc_stubs.hal_icc_msg_rx_req_pending_process (icc_adapter, q_id);
#endif
}

/** 
 *  @brief Initials the table of ICC message receiving call-back functions. The application can register(add) a ICC
 *         message type with a call-back function. The call-back function will be called when its corresponding 
 *         message is received.
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  pmsg_tbl  The ICC message table buffer.
 *  @param[in]  tbl_sz  The size(number of message can be registered) of the ICC message 
 *                      call-back function table.
 *
 *  @return     none.
 */
void hal_icc_msg_tbl_init (hal_icc_adapter_t *icc_adapter, icc_msg_entry_t *pmsg_tbl, uint8_t tbl_sz)
{
    icc_adapter->msg_regtbl_sz = tbl_sz;
    icc_adapter->pmsg_regtbl = pmsg_tbl;
    if ((pmsg_tbl != NULL) && (tbl_sz > 0)) {
        memset (icc_adapter->pmsg_regtbl, 0, sizeof(icc_msg_entry_t)*icc_adapter->msg_regtbl_sz);
    }
}

/** 
 *  @brief Registers(adds) an ICC user application message to the 
 *         ICC user application message table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  msg  The ICC message type to be registered.
 *  @param[in]  frame  The frame type(category) of this ICC message.
 *  @param[in]  callback  The ICC message handler function of this new added message type.
 *  @param[in]  cb_arg  The application data will be passed back to the application
 *                      with the callback function.
 *
 *  @return     HAL_OK: Message registration OK.
 *  @return     HAL_NOT_READY: The ICC HAL message table buffer did not been initialed yet.
 *  @return     HAL_NO_RESOURCE: No free entry of the table(table is full).
 */
hal_status_t hal_icc_msg_tbl_reg (hal_icc_adapter_t *icc_adapter, uint8_t msg, uint8_t frame,
                                        icc_msg_rx_cb_t callback, uint32_t cb_arg)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_icc_msg_tbl_reg_rtl8195bhp_patch (icc_adapter, msg, frame, callback, cb_arg);
#else
    return hal_icc_stubs.hal_icc_msg_tbl_reg (icc_adapter, msg, frame, callback, cb_arg);
#endif

}

/** 
 *  @brief Un-register(remove) an user application ICC message from the
 *         user application ICC message table.
 *
 *  @param[in]  icc_adapter  The ICC HAL adapter.
 *  @param[in]  msg  The user application ICC message type to be removed
 *                   from the user application ICC message table.
 *  @param[in]  frame  The frame type(category) of this ICC message.
 *
 *  @returns    void.
 */
void hal_icc_msg_tbl_unreg (hal_icc_adapter_t *icc_adapter, uint8_t msg, uint8_t frame)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    hal_icc_msg_tbl_unreg_rtl8195bhp_patch (icc_adapter, msg, frame);
#else
    hal_icc_stubs.hal_icc_msg_tbl_unreg (icc_adapter, msg, frame);
#endif
}


/** @} */ /* End of group hs_hal_icc */

#endif  // end of "#if CONFIG_ICC_EN"

