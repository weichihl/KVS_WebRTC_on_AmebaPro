/**************************************************************************//**
 * @file     hal_pcm.c
 * @brief    This PCM HAL API functions.
 *
 * @version  V1.00
 * @date     2016-09-19
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

#include "hal_cache.h"
#include "hal_pinmux.h"
#include "hal_pcm.h"
#include "hal.h"

#if CONFIG_PCM_EN

extern void hal_syson_pcm_24m_pll_ctrl(BOOL en);

/**
 * @addtogroup hs_hal_pcm PCM
 * @{
 */

/**
 *  @brief The PCM interrupt handler. It process all interrupt events.
 *
 *  @param[in]  hid The handler ID, it should be the PCM adapter.
 *
 *  @returns void
 */
void hal_pcm_irq_handler (void *hid)
{
    hal_pcm_stubs.hal_pcm_irq_handler (hid);
}

/**
 *  @brief To register a IRQ handler for PCM.
 *
 *  @returns void
 */
void hal_pcm_irq_reg (void)
{
    hal_pcm_stubs.hal_pcm_irq_reg ();
}

/**
 *  @brief To un-register the PCM IRQ handler.
 *
 *  @param[in]  ppcm_adapter The PCM adapter.
 *
 *  @returns void
 */
void hal_pcm_irq_unreg (hal_pcm_adapter_t *ppcm_adapter)
{
    hal_pcm_stubs.hal_pcm_irq_unreg (ppcm_adapter);
}

/**
 *  @brief To enable or disable PCM for the platform.
 *
 *  @param[in] index_sel The PCM index. It can be 0 or 1.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_en (pcm_index_sel_t index_sel, BOOL en)
{
    return hal_pcm_stubs.hal_pcm_en (index_sel, en);
}

/**
 *  @brief To enable/disable the bus clock for PCM.
 *
 *  @param[in] index_sel The PCM index. It can be 0 or 1.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_clk_ctrl (pcm_index_sel_t index_sel, BOOL en)
{
    return hal_pcm_stubs.hal_pcm_clk_ctrl (index_sel, en);
}

/**
 *  @brief PCM pin mux selection.
 *
 *  @param[in] index_sel The PCM index. It can be 0 or 1.
 *  @param[in] pin_sel The pin mux selection.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_pin_ctrl (pcm_index_sel_t index_sel, pcm_pin_sel_t pin_sel, BOOL en)
{
    return hal_pcm_stubs.hal_pcm_pin_ctrl (index_sel, pin_sel, en);
}

/**
 *  @brief Control the PCM bus and hardware clock.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_func_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_func_ctrl (hal_pcm_adapter_t *ppcm_adapter, BOOL pcm_func_en)
{
    return hal_pcm_stubs.hal_pcm_func_ctrl (ppcm_adapter, pcm_func_en);
}

/**
 *  @brief Initialize the PCM hardware and turn on the PCM.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_init (hal_pcm_adapter_t *ppcm_adapter)
{
    hal_status_t ret;
    io_pin_t *pin_list;

    pin_list = (io_pin_t *)&hal_pcm_stubs.ppcm_pin[(ppcm_adapter->pcm_index * 10) + (ppcm_adapter->pin_sel * 5)];
    ret = hal_pinmux_register (pin_list, (PID_PCM0 + ppcm_adapter->pcm_index));
    if (ret == HAL_OK) {

        hal_syson_pcm_24m_pll_ctrl(ENABLE);
        ppcm_adapter->dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;
        ppcm_adapter->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;

        return hal_pcm_stubs.hal_pcm_init (ppcm_adapter);
    } else {
        return ret;
    }
}

/**
 *  @brief De-initialize of the PCM hardware and turn off the PCM.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
void hal_pcm_deinit (hal_pcm_adapter_t *ppcm_adapter)
{
    uint32_t pcm_index = ppcm_adapter->pcm_index;
    uint32_t pin_sel = ppcm_adapter->pin_sel;
    io_pin_t *pin_list;

    hal_pcm_stubs.hal_pcm_deinit (ppcm_adapter);
    pin_list = (io_pin_t *)&hal_pcm_stubs.ppcm_pin[(pcm_index * 10) + (pin_sel * 5)];
    hal_pinmux_unregister (pin_list, (PID_PCM0 + pcm_index));
    hal_syson_pcm_24m_pll_ctrl(DISABLE);
}

/**
 *  @brief Set the PCM format parameter.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] ppcm_format The PCM format parameter.
 *                      pcm_slave - Master or Slave mode.
 *                      pcm_linear_mode - Set linear or compender mode. when choose the compender mode, need to set a-law or u-law.
 *                      pcm_loop_back - Set the loopback mode.
 *                      pcm_endian_swap - Set the endian swap.
 *                      pcm_fs_inv - Set the frame sync is the high or low active.
 *
 *  @returns void
 */
void hal_pcm_set_format (hal_pcm_adapter_t *ppcm_adapter, hal_pcm_format_t *ppcm_format)
{
    hal_pcm_stubs.hal_pcm_set_format (ppcm_adapter, ppcm_format);
}

/**
 *  @brief To enter a critical section of code, mainly it
 *         disable PCM interrupt to prevent race condition.
 *
 *  @returns void
 */
void hal_pcm_enter_critical (void)
{
    hal_pcm_stubs.hal_pcm_enter_critical ();
}

/**
 *  @brief To exit a critical code section, it will re-enable the PCM interrupt
 *         only when the exiting critical section is the top level.
 *
 *  @returns void
 */
void hal_pcm_exit_critical (void)
{
    hal_pcm_stubs.hal_pcm_exit_critical ();
}

/**
 *  @brief Enable or disable the PCM.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_en_ctrl Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_pcm_en_ctrl (hal_pcm_adapter_t *ppcm_adapter, BOOL pcm_en_ctrl)
{
    hal_pcm_stubs.hal_pcm_en_ctrl (ppcm_adapter, pcm_en_ctrl);
}

/**
 *  @brief Set the time slot of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_slot Set the time slot. If configured as 16 bit linear mode, only even number time slot is allowed.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_time_slot (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_slot_t pcm_slot)
{
    return hal_pcm_stubs.hal_pcm_set_ch_time_slot (ppcm_adapter, pcm_ch, pcm_slot);
}

/**
 *  @brief Get the setting value of the channel group about the time slot.
 *
 *  @param[in] pcm_ch_rem The index of the channel group.
 *  @param[in] patsrgn The register value of the channel group.
 *  @param[in] pcm_slot Set the time slot 0~31. If configured as 16 bit linear mode, only even number time slot is allowed.
 *
 *  @returns The setting result.
 */
u32 hal_pcm_set_ch_rem_time_slot (u32 pcm_ch_rem, u32 patsrgn, pcm_slot_t pcm_slot)
{
    return hal_pcm_stubs.hal_pcm_set_ch_rem_time_slot (pcm_ch_rem, patsrgn, pcm_slot);
}

/**
 *  @brief Set the windband time slot of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel. The channel is only valid for CH0~CH7.
 *  @param[in] pcm_slot Set the time slot 0~31. If configured as 16 bit linear mode, only even number time slot is allowed.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_wb_time_slot (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_slot_t pcm_slot)
{
    return hal_pcm_stubs.hal_pcm_set_ch_wb_time_slot (ppcm_adapter, pcm_ch, pcm_slot);
}

/**
 *  @brief Set the windband enablel of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel. The channel is only valid for CH0~CH7.
 *  @param[in] pcm_en_ctrl Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_wideband_en (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_en_ctrl)
{
    return hal_pcm_stubs.hal_pcm_set_ch_wideband_en (ppcm_adapter, pcm_ch, pcm_en_ctrl);
}

/**
 *  @brief Get the setting value of the channel group about the windband enable.
 *
 *  @param[in] pcm_ch_rem The index of the channel group.
 *  @param[in] patsrgn The register value of the channel group.
 *  @param[in] pcm_en_ctrl Enable control: 0 is disable, 1 is enable.
 *
 *  @returns The setting result.
 */
u32 hal_pcm_set_ch_rem_wideband_en (u32 pcm_ch_rem, u32 pachgn_cnr, BOOL pcm_en_ctrl)
{
    return hal_pcm_stubs.hal_pcm_set_ch_rem_wideband_en (pcm_ch_rem, pachgn_cnr, pcm_en_ctrl);
}

/**
 *  @brief Set U-law or A-law of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_ua_law Set U-law or A-law, U-law: 0, A-law: 1
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_ua_law (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_ua_law_t pcm_ua_law)
{
    return hal_pcm_stubs.hal_pcm_set_ch_ua_law (ppcm_adapter, pcm_ch, pcm_ua_law);
}

/**
 *  @brief Get the setting value of the channel group about the compender.
 *
 *  @param[in] pcm_ch_rem The index of the channel group.
 *  @param[in] pachgn_cnr The register value of the channel group.
 *  @param[in] pcm_ua_law Set U-law or A-law, U-law: 0, A-law: 1
 *
 *  @returns The setting result.
 */
u32 hal_pcm_set_ch_rem_ua_law (u32 pcm_ch_rem, u32 pachgn_cnr, pcm_ua_law_t pcm_ua_law)
{
    return hal_pcm_stubs.hal_pcm_set_ch_rem_ua_law (pcm_ch_rem, pachgn_cnr, pcm_ua_law);
}

/**
 *  @brief Control the TX enable of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_tx_en TX Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_tx_en (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_tx_en)
{
    return hal_pcm_stubs.hal_pcm_set_ch_tx_en (ppcm_adapter, pcm_ch, pcm_tx_en);
}

/**
 *  @brief Record the TX enable in the PCM adapter.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_tx_en TX Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_reg_ch_tx_en (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_tx_en)
{
    return hal_pcm_stubs.hal_pcm_reg_ch_tx_en (ppcm_adapter, pcm_ch, pcm_tx_en);
}

/**
 *  @brief Control the RX enable of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_rx_en TX Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_rx_en (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_rx_en)
{
    return hal_pcm_stubs.hal_pcm_set_ch_rx_en (ppcm_adapter, pcm_ch, pcm_rx_en);
}

/**
 *  @brief Record the RX enable in the PCM adapter.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_rx_en RX Enable control: 0 is disable, 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_reg_ch_rx_en (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_rx_en)
{
    return hal_pcm_stubs.hal_pcm_reg_ch_rx_en (ppcm_adapter, pcm_ch, pcm_rx_en);
}

/**
 *  @brief Get the setting value of the channel group about the tx and rx enable.
 *
 *  @param[in] pcm_ch_rem The index of the channel group.
 *  @param[in] pachgn_cnr The register value of the channel group.
 *  @param[in] pcm_trx_ctrl RX: 0, TX: 1.
 *  @param[in] pcm_trx_en TRX Enable control: 0 is disable, 1 is enable.
 *
 *  @returns The setting result.
 */
u32 hal_pcm_set_ch_rem_trx_en (u32 pcm_ch_rem, u32 pachgn_cnr, pcm_trx_ctrl_t pcm_trx_ctrl, BOOL pcm_trx_en)
{
    return hal_pcm_stubs.hal_pcm_set_ch_rem_trx_en (pcm_ch_rem, pachgn_cnr, pcm_trx_ctrl, pcm_trx_en);
}

/**
 *  @brief Set the page size of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_page_size Need the even number 2~512, page units: 2 bytes.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_page_size (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 pcm_page_size)
{
    return hal_pcm_stubs.hal_pcm_set_ch_page_size (ppcm_adapter, pcm_ch, pcm_page_size);
}

/**
 *  @brief Get the setting value of the channel group about the page size.
 *
 *  @param[in] pcm_ch_rem The index of the channel group.
 *  @param[in] pabsizegn The register value of the channel group.
 *  @param[in] pcm_page_size Need the even number 2~512, page units: 2 bytes.
 *
 *  @returns The setting result.
 */
u32 hal_pcm_set_ch_rem_page_size (u32 pcm_ch_rem, u32 pabsizegn, u8 pcm_page_size)
{
    return hal_pcm_stubs.hal_pcm_set_ch_rem_page_size (pcm_ch_rem, pabsizegn, pcm_page_size);
}

/**
 *  @brief Clean the interrupt status of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] paisr_n The interrupt status.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_clr_ch_intr_ctrl (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, paisr_n_t paisr_n)
{
    return hal_pcm_stubs.hal_pcm_clr_ch_intr_ctrl (ppcm_adapter, pcm_ch, paisr_n);
}

/**
 *  @brief Get the setting value of the channel group about the interrupt status.
 *
 *  @param[in] pcm_ch_rem The index of the channel group.
 *  @param[in] paisr_gn The register value of the channel group.
 *  @param[in] paisr_n The interrupt status.
 *
 *  @returns The setting result.
 */
u32 hal_pcm_clr_ch_rem_intr_ctrl (u32 pcm_ch_rem, u32 paisr_gn, paisr_n_t paisr_n)
{
    return hal_pcm_stubs.hal_pcm_clr_ch_rem_intr_ctrl (pcm_ch_rem, paisr_gn, paisr_n);
}

/**
 *  @brief Enable the interrupt of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] paimr_n The interrupt enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_intr_ctrl (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, paimr_n_t paimr_n)
{
    return hal_pcm_stubs.hal_pcm_set_ch_intr_ctrl (ppcm_adapter, pcm_ch, paimr_n);
}

/**
 *  @brief Get the setting value of the channel group about the interrupt enable.
 *
 *  @param[in] pcm_ch_rem The index of the channel group.
 *  @param[in] paimr_gn The register value of the channel group.
 *  @param[in] paimr_n The interrupt enable.
 *
 *  @returns The setting result.
 */
u32 hal_pcm_set_ch_rem_intr_ctrl (u32 pcm_ch_rem, u32 paimr_gn, paimr_n_t paimr_n)
{
    return hal_pcm_stubs.hal_pcm_set_ch_rem_intr_ctrl (pcm_ch_rem, paimr_gn, paimr_n);
}

/**
 *  @brief Get the tx address of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *
 *  @returns The tx address.
 */
u32 *hal_pcm_get_ch_tx_adr_reg (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch)
{
    return hal_pcm_stubs.hal_pcm_get_ch_tx_adr_reg (ppcm_adapter, pcm_ch);
}

/**
 *  @brief Set the tx address of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_tx_adr The tx address.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_tx_adr (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u16 *pcm_tx_adr)
{
    return hal_pcm_stubs.hal_pcm_set_ch_tx_adr (ppcm_adapter, pcm_ch, pcm_tx_adr);
}

/**
 *  @brief Get the rx address of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *
 *  @returns The rx address.
 */
u32 *hal_pcm_get_ch_rx_adr_reg (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch)
{
    return hal_pcm_stubs.hal_pcm_get_ch_rx_adr_reg (ppcm_adapter, pcm_ch);
}

/**
 *  @brief Set the rx address of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_rx_adr The tx address.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_rx_adr (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u16 *pcm_rx_adr)
{
    return hal_pcm_stubs.hal_pcm_set_ch_rx_adr (ppcm_adapter, pcm_ch, pcm_rx_adr);
}

/**
 *  @brief Get the page size of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *
 *  @returns The page size.
 */
u8 hal_pcm_get_ch_page_size (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch)
{
    return hal_pcm_stubs.hal_pcm_get_ch_page_size (ppcm_adapter, pcm_ch);
}

/**
 *  @brief Get the trx channel information.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pirq_info_ch Set the variable for getting the information.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_get_ch_trx_info (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, hal_pcm_irqinfo_ch_t *pirq_info_ch)
{
    return hal_pcm_stubs.hal_pcm_get_ch_trx_info (ppcm_adapter, pcm_ch, pirq_info_ch);
}

/**
 *  @brief Set the tx own bit of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_page0_own Set 1 is enable.
 *  @param[in] pcm_page1_own Set 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_tx_own (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u32 pcm_page0_own, u32 pcm_page1_own)
{
    return hal_pcm_stubs.hal_pcm_set_ch_tx_own (ppcm_adapter, pcm_ch, pcm_page0_own, pcm_page1_own);
}

/**
 *  @brief Set the rx own bit of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] pcm_page0_own Set 1 is enable.
 *  @param[in] pcm_page1_own Set 1 is enable.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_set_ch_rx_own (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u32 pcm_page0_own, u32 pcm_page1_own)
{
    return hal_pcm_stubs.hal_pcm_set_ch_rx_own (ppcm_adapter, pcm_ch, pcm_page0_own, pcm_page1_own);
}

/**
 *  @brief Update the tx processing page index of the channel in the table.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_update_sw_ch_tx_idx (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch)
{
    return hal_pcm_stubs.hal_pcm_update_sw_ch_tx_idx (ppcm_adapter, pcm_ch);
}

/**
 *  @brief Update the rx processing page index of the channel in the table.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_update_sw_ch_rx_idx (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch)
{
    return hal_pcm_stubs.hal_pcm_update_sw_ch_rx_idx (ppcm_adapter, pcm_ch);
}

/**
 *  @brief Clean all interrupt status.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *
 *  @returns void
 */
void hal_pcm_clr_all_intr (hal_pcm_adapter_t *ppcm_adapter)
{
    hal_pcm_stubs.hal_pcm_clr_all_intr (ppcm_adapter);
}

/**
 *  @brief Disable all interrupt.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *
 *  @returns void
 */
void hal_pcm_dis_all_intr (hal_pcm_adapter_t *ppcm_adapter)
{
    hal_pcm_stubs.hal_pcm_dis_all_intr (ppcm_adapter);
}

/**
 *  @brief Disable TX and RX of all channels.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *
 *  @returns void
 */
void hal_pcm_dis_all_trx (hal_pcm_adapter_t *ppcm_adapter)
{
    hal_pcm_stubs.hal_pcm_dis_all_trx (ppcm_adapter);
}

/**
 *  @brief Disable TX of all channels.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *
 *  @returns void
 */
void hal_pcm_dis_all_tx (hal_pcm_adapter_t *ppcm_adapter)
{
    hal_pcm_stubs.hal_pcm_dis_all_tx (ppcm_adapter);
}

/**
 *  @brief Disable RX of all channels.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *
 *  @returns void
 */
void hal_pcm_dis_all_rx (hal_pcm_adapter_t *ppcm_adapter)
{
    hal_pcm_stubs.hal_pcm_dis_all_rx (ppcm_adapter);
}

/**
 *  @brief Invalidate the D-Cache of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] page_idx Set the page index.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_pcm_ch_read_memory_cache_invalidate (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 page_idx)
{
    return hal_pcm_stubs.hal_pcm_ch_read_memory_cache_invalidate (ppcm_adapter, pcm_ch, page_idx);
}

/**
 *  @brief Clean the D-Cache of the channel.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *  @param[in] pcm_ch Set the channel, CH0~CH15.
 *  @param[in] page_idx Set the page index.
 *
 *  @returns void
 */
HAL_Status hal_pcm_ch_write_memory_cache_clean (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 page_idx)
{
    return hal_pcm_stubs.hal_pcm_ch_write_memory_cache_clean (ppcm_adapter, pcm_ch, page_idx);
}

/**
 *  @brief Start the tx and rx transmission for all enabled channels.
 *
 *  @param[in] ppcm_adapter The PCM adapter.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
void hal_pcm_start_trx (hal_pcm_adapter_t *ppcm_adapter)
{
   hal_pcm_stubs.hal_pcm_start_trx (ppcm_adapter);
}

/** @} */ /* End of group hs_hal_pcm */

#endif

