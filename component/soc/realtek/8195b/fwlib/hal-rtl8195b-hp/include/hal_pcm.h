/**************************************************************************//**
 * @file     hal_pcm.h
 * @brief    The HAL API implementation for the PCM device.
 * @version  V1.00
 * @date     2016-12-14
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

#ifndef _HAL_PCM_H_
#define _HAL_PCM_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_pcm PCM
 * @ingroup 8195bh_hal
 * @{
 * @brief The PCM HAL module of the HS platform.
 */

/**
  * @brief The stubs functions table to exports PCM HAL functions in ROM.
  */
extern const hal_pcm_func_stubs_t hal_pcm_stubs;

/**
 *  @brief Get the pcm enable value.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *
 *  @returns The enable value.
 */
__STATIC_INLINE
u32 hal_pcm_get_en_ctrl (hal_pcm_adapter_t *ppcm_adapter)
{
    u32 temp;

    temp = (u32)ppcm_adapter->base_addr->pcmcr_b.pcm_en;
    return temp;
}

/**
 *  @brief Get the pcm mode.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *
 *  @returns The linear mode(1) or compender mode(0).
 */
__STATIC_INLINE
u32 hal_pcm_get_linear_mode (hal_pcm_adapter_t *ppcm_adapter)
{
    u32 temp;

    temp = (u32)ppcm_adapter->base_addr->pcmcr_b.linear_mode;
    return temp;
}

/** @} */ /* End of group hs_hal_pcm */

void hal_pcm_irq_handler (void *hid);
void hal_pcm_irq_reg (void);
void hal_pcm_irq_unreg (hal_pcm_adapter_t *ppcm_adapter);
HAL_Status hal_pcm_en (pcm_index_sel_t index_sel, BOOL en);
HAL_Status hal_pcm_clk_ctrl (pcm_index_sel_t index_sel, BOOL en);
HAL_Status hal_pcm_pin_ctrl (pcm_index_sel_t index_sel, pcm_pin_sel_t pin_sel, BOOL en);
HAL_Status hal_pcm_func_ctrl (hal_pcm_adapter_t *ppcm_adapter, BOOL pcm_func_en);
HAL_Status hal_pcm_init (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_deinit (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_set_format (hal_pcm_adapter_t *ppcm_adapter, hal_pcm_format_t *ppcm_format);
void hal_pcm_enter_critical (void);
void hal_pcm_exit_critical (void);
void hal_pcm_en_ctrl (hal_pcm_adapter_t *ppcm_adapter, BOOL pcm_en_ctrl);
HAL_Status hal_pcm_set_ch_time_slot (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_slot_t pcm_slot);
u32 hal_pcm_set_ch_rem_time_slot (u32 pcm_ch_rem, u32 patsrgn, pcm_slot_t pcm_slot);
HAL_Status hal_pcm_set_ch_wb_time_slot (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_slot_t pcm_slot);
HAL_Status hal_pcm_set_ch_wideband_en (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_en_ctrl);
u32 hal_pcm_set_ch_rem_wideband_en (u32 pcm_ch_rem, u32 pachgn_cnr, BOOL pcm_en_ctrl);
HAL_Status hal_pcm_set_ch_ua_law (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_ua_law_t pcm_ua_law);
u32 hal_pcm_set_ch_rem_ua_law (u32 pcm_ch_rem, u32 pachgn_cnr, pcm_ua_law_t pcm_ua_law);
HAL_Status hal_pcm_set_ch_tx_en (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_tx_en);
HAL_Status hal_pcm_reg_ch_tx_en (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_tx_en);
HAL_Status hal_pcm_set_ch_rx_en (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_rx_en);
HAL_Status hal_pcm_reg_ch_rx_en (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_rx_en);
u32 hal_pcm_set_ch_rem_trx_en (u32 pcm_ch_rem, u32 pachgn_cnr, pcm_trx_ctrl_t pcm_trx_ctrl, BOOL pcm_trx_en);
HAL_Status hal_pcm_set_ch_page_size (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 pcm_page_size);
u32 hal_pcm_set_ch_rem_page_size (u32 pcm_ch_rem, u32 pabsizegn, u8 pcm_page_size);
HAL_Status hal_pcm_clr_ch_intr_ctrl (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, paisr_n_t paisr_n);
u32 hal_pcm_clr_ch_rem_intr_ctrl (u32 pcm_ch_rem, u32 paisr_gn, paisr_n_t paisr_n);
HAL_Status hal_pcm_set_ch_intr_ctrl (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, paimr_n_t paimr_n);
u32 hal_pcm_set_ch_rem_intr_ctrl (u32 pcm_ch_rem, u32 paimr_gn, paimr_n_t paimr_n);
u32 *hal_pcm_get_ch_tx_adr_reg (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
HAL_Status hal_pcm_set_ch_tx_adr (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u16 *pcm_tx_adr);
u32 *hal_pcm_get_ch_rx_adr_reg (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
HAL_Status hal_pcm_set_ch_rx_adr (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u16 *pcm_rx_adr);
u8 hal_pcm_get_ch_page_size (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
HAL_Status hal_pcm_get_ch_trx_info (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, hal_pcm_irqinfo_ch_t *pirq_info_ch);
HAL_Status hal_pcm_set_ch_tx_own (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u32 pcm_page0_own, u32 pcm_page1_own);
HAL_Status hal_pcm_set_ch_rx_own (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u32 pcm_page0_own, u32 pcm_page1_own);
HAL_Status hal_pcm_update_sw_ch_tx_idx (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
HAL_Status hal_pcm_update_sw_ch_rx_idx (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
void hal_pcm_clr_all_intr (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_dis_all_intr (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_dis_all_trx (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_dis_all_tx (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_dis_all_rx (hal_pcm_adapter_t *ppcm_adapter);
HAL_Status hal_pcm_ch_read_memory_cache_invalidate (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 page_idx);
HAL_Status hal_pcm_ch_write_memory_cache_clean (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 page_idx);
void hal_pcm_start_trx (hal_pcm_adapter_t *ppcm_adapter);


#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_PCM_H_"

