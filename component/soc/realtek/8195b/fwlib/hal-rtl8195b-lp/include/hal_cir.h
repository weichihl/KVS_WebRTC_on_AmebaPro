/**************************************************************************//**
 * @file     hal_cir.h
 * @brief    The HAL API implementation for the CIR device.
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

#ifndef _HAL_CIR_H_
#define _HAL_CIR_H_

#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup ls_hal_cir CIR
 * @ingroup 8195bl_hal
 * @{
 * @brief The CIR HAL module of the LS platform.
 */

/**
  * @brief The stubs functions table to exports CIR HAL functions in ROM.
  */
extern const hal_cir_func_stubs_t hal_cir_stubs;

/**
 *  @brief TX output enable/disable.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] tx_out_ctrl 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_tx_en (hal_cir_adapter_t *pcir_adp, BOOL tx_out_ctrl)
{
     pcir_adp->base_addr->ctrl_b.txen = tx_out_ctrl;
}

/**
 *  @brief RX input enable/disable.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] rx_out_ctrl 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_rx_en (hal_cir_adapter_t *pcir_adp, BOOL rx_in_ctrl)
{
     pcir_adp->base_addr->ctrl_b.rxen = rx_in_ctrl;
}

/**
 *  @brief Write the symbol to FIFO .
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] symbol The symbol is Symbol_01 ~ Symbol_08.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_send_tx_symbol (hal_cir_adapter_t *pcir_adp, cir_sym_t symbol)
{
     pcir_adp->base_addr->txwr_b.txwr = symbol;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt for matching the start symbol of SymGroup0.
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] int_en 0: disable, 1:Enable to update cir isr and make the interrupt.
 *  @param[in] imr_en 0: disable, 1:Mask the interrupt and the cir isr still updated.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_strm_gp0_int (hal_cir_adapter_t *pcir_adp, BOOL int_en, BOOL imr_en)
{
    pcir_adp->base_addr->ier_b.ie_rxsym0strm = int_en;
    pcir_adp->base_addr->imr_b.im_rxsym0strm = imr_en;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt for matching the start symbol of SymGroup1.
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] int_en 0: disable, 1:Enable to update cir isr and make the interrupt.
 *  @param[in] imr_en 0: disable, 1:Mask the interrupt and the cir isr still updated.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_strm_gp1_int (hal_cir_adapter_t *pcir_adp, BOOL int_en, BOOL imr_en)
{
    pcir_adp->base_addr->ier_b.ie_rxsym1strm = int_en;
    pcir_adp->base_addr->imr_b.im_rxsym1strm = imr_en;
}

/**
 *  @brief Cir decoder enable/disable.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] en 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_decoder_en (hal_cir_adapter_t *pcir_adp, BOOL en)
{
     pcir_adp->base_addr->rxdcctrl_b.rxdc_en = en;
}

/**
 *  @brief  Close RX FIFO  is enabled/disabled.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] en 0: not close RX FIFO, 1: close RX FIFO.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_rxfifo_close_en (hal_cir_adapter_t *pcir_adp, BOOL en)
{
     pcir_adp->base_addr->rxdcctrl_b.rxfifodis = en;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt for the monitor.
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] int_en 0: disable, 1:Enable to update cir isr and make the interrupt.
 *  @param[in] imr_en 0: disable, 1:Mask the interrupt and the cir isr still updated.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_monitor_int (hal_cir_adapter_t *pcir_adp, BOOL int_en, BOOL imr_en)
{
    pcir_adp->base_addr->isr_b.is_monitor = 1;
    pcir_adp->base_addr->ier_b.ie_monitor = int_en;
    pcir_adp->base_addr->imr_b.im_monitor = imr_en;
}

/**
 *  @brief Get the CIR decoded data.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The decoded data.
 */
__STATIC_INLINE
u32 hal_cir_get_decode_data (hal_cir_adapter_t *pcir_adp)
{
    u32 temp;

    temp = (u32)pcir_adp->base_addr->rxdcdata;
    return temp;
}

/**
 *  @brief When the decoded data are bigger than 32 bits, this the first 32-bit data will are saved in rxdcdata_dp.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The first 32-bit decoded data.
 */
__STATIC_INLINE
u32 hal_cir_get_decode_data_dp (hal_cir_adapter_t *pcir_adp)
{
    u32 temp;

    temp = (u32)pcir_adp->base_addr->rxdcdata_dp;
    return temp;
}

/**
 *  @brief Get FIFO status.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns FIFO status. [0]: RXRDY, [1]: TXFULL, [2]: TX2EMP.
 */
__STATIC_INLINE
u32 hal_cir_txfifo_status (hal_cir_adapter_t *pcir_adp)
{
    u32 temp;

    temp = (u32)pcir_adp->base_addr->fsts;
    return temp;
}

/**
 *  @brief Get the start matching isr status for the group 0.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The start matching status. 0: no interrupt, 1: interrupt is pending.
 */
__STATIC_INLINE
BOOL hal_cir_get_start_match_gp0_status (hal_cir_adapter_t *pcir_adp)
{
    u8 temp;

    temp = (u8)pcir_adp->cir_isr_req_ever.b.is_rxsym0strm;
    return temp;
}

/**
 *  @brief Get the start matching isr status for the group 1.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The start matching status. 0: no interrupt, 1: interrupt is pending.
 */
__STATIC_INLINE
BOOL hal_cir_get_start_match_gp1_status (hal_cir_adapter_t *pcir_adp)
{
    u8 temp;

    temp = (u8)pcir_adp->cir_isr_req_ever.b.is_rxsym1strm;
    return temp;
}

/**
 *  @brief Get the argument of the rx end callback function.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The argument of the rx end callback function.
 */
__STATIC_INLINE
void *hal_cir_get_irq_rx_end_arg_from_adapter (hal_cir_adapter_t *pcir_adp)
{
    void *ptemp;

    ptemp = pcir_adp->rx_protocol_frame.irq_rx_end_arg;
    return ptemp;
}

/**
 *  @brief Get the number of decoded bits.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The number of decoded bits.
 */
__STATIC_INLINE
u32 hal_cir_recv_bit_length (hal_cir_adapter_t *pcir_adp)
{
    u32 temp;

    temp = pcir_adp->base_addr->rxdatacnt;
    return temp;
}

/**
 *  @brief Set the interrupt mask.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_imr (hal_cir_adapter_t *pcir_adp, cir_imr_t cir_imr)
{
    pcir_adp->base_addr->imr = cir_imr.w;
}

/**
 *  @brief Set the interrupt enabling.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_ie (hal_cir_adapter_t *pcir_adp, cir_ier_t cir_ier)
{
    pcir_adp->base_addr->ier = cir_ier.w;
}

/**
 *  @brief Get the interrupt pending status.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The interrupt pending status.
 */
__STATIC_INLINE
u32 hal_cir_get_isr (hal_cir_adapter_t *pcir_adp)
{
    u32 temp;

    temp = pcir_adp->base_addr->isr;
    return temp;
}

/**
 *  @brief Get the RX decode status.
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The RX decode status.
 */
__STATIC_INLINE
cir_rx_status_t hal_cir_get_protocol_rx_status (hal_cir_adapter_t *pcir_adp)
{
    cir_rx_status_t temp;

    temp = (pcir_adp->rx_protocol_frame.cir_format_result);
    return temp;
}

/** @} */ /* End of group ls_hal_cir */


void hal_cir_irq_handler (void *hid);
void hal_cir_irq_reg (irq_handler_t handler);
void hal_cir_irq_unreg (void);

HAL_Status hal_cir_init (hal_cir_adapter_t *pcir_adp, cir_pin_sel_t pin_sel, cir_app_pin_sel_t app_pin_sel);
void hal_cir_deinit (hal_cir_adapter_t *pcir_adp);
void hal_cir_reset (void);
void hal_cir_enter_critical (void);
void hal_cir_exit_critical (void);
HAL_Status hal_cir_tx_carrier_init (hal_cir_adapter_t *pcir_adp, u32 carrier_fq, u32 tx_sclkdiv, u16 cari_hl_ratio);
HAL_Status hal_cir_rx_carrier_init (hal_cir_adapter_t *pcir_adp, u32 carrier_fq, u32 rx_sclkdiv);
HAL_Status hal_cir_set_tx_symbol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_symdesc_t *psymdesc);
HAL_Status hal_cir_set_rx_symbol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_symdesc_t *psymdesc);
void hal_cir_set_rx_timeout (hal_cir_adapter_t *pcir_adp, u16 time_us);
void hal_cir_rst (hal_cir_adapter_t *pcir_adp, cir_TRX_t cir_trx);
HAL_Status hal_cir_symbol_separate (hal_cir_adapter_t *pcir_adp, hal_cir_symsprt_t *psymsprt, cir_sym_group_t group);
HAL_Status hal_cir_symbol_bit0 (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group);
HAL_Status hal_cir_symbol_bit1 (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group);
HAL_Status hal_cir_symbol_strm (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group);
void hal_cir_irq_strm_gp0_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
void hal_cir_irq_strm_gp1_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
void hal_cir_set_monitor (hal_cir_adapter_t *pcir_adp, u32 monitor_data, u32 monitor_cnt, BOOL en);
void hal_cir_irq_monitor_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
void hal_cir_irq_send_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
void hal_cir_recv (hal_cir_adapter_t *pcir_adp, u32 *data, u32 data_limit);
void hal_cir_irq_recv_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
void hal_cir_irq_ie_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
cir_sym_type_t hal_cir_get_carrier_init_level (cir_carrier_t carrier, cir_init_value_t value);
void hal_cir_set_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting, hal_cir_tx_protocol_t *pcir_tx_protocol);
void hal_cir_load_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_t *pcir_tx_protocol, cir_sym_type_t symtype_level, cir_sym_type_t symtype_carrier);
void hal_cir_set_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc, hal_cir_rx_protocol_t *pcir_rx_protocol);
void hal_cir_load_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_t *pcir_rx_protocol, cir_sym_type_t symtype_level, cir_sym_type_t symtype_carrier);
void hal_cir_protocol_recv (hal_cir_adapter_t *pcir_adp, u32 *data, u8 format, u32 data_32bits_num);
u32 hal_cir_data_reverse (u32 x);
void hal_cir_set_rx_filter_en (hal_cir_adapter_t *pcir_adp, BOOL en, u8 filter_sym_cnt);
void hal_cir_set_rx_filter_reset (hal_cir_adapter_t *pcir_adp);
HAL_Status hal_cir_set_rx_filter_timeout (hal_cir_adapter_t *pcir_adp, BOOL en, u32 ftime_us);
HAL_Status hal_cir_set_rx_filter_symbol (hal_cir_adapter_t *pcir_adp, cir_sym_t symbol, u8 symb_in_seq);
void hal_cir_irq_filter_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);

//============ Need to init ptx_protocol_frame or prx_protocol_frame ============
void hal_cir_init_output_frame (hal_cir_adapter_t *pcir_adp, cir_sym_type_t symtype_level);
void hal_cir_send_protocol (hal_cir_adapter_t *pcir_adp, u32 *data, u32 length);

//----------------NEC protocol----------------
void hal_cir_set_nec_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
void hal_cir_nec_send (hal_cir_adapter_t *pcir_adp, void *data, cir_nec_tx_format_t format);
void hal_cir_set_nec_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
void hal_cir_rx_nec_pre_irq(void *data);

//----------------Sony Sirc protocol----------------
void hal_cir_set_sony_sirc_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
void hal_cir_sony_sirc_send (hal_cir_adapter_t *pcir_adp, void *data, cir_sony_sirc_format_t format);
void hal_cir_set_sony_sirc_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
void hal_cir_rx_sony_sirc_pre_irq(void *data);

//----------------Philips RC5 protocol----------------
void hal_cir_set_philips_rc5_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
void hal_cir_philips_rc5_send (hal_cir_adapter_t *pcir_adp, hal_cir_philips_rc5_format_t *data);
void hal_cir_set_philips_rc5_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
void hal_cir_rx_philips_rc5_pre_irq(void *data);

//----------------Jvc protocol----------------
void hal_cir_set_jvc_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
void hal_cir_jvc_send (hal_cir_adapter_t *pcir_adp, void *data, cir_jvc_tx_format_t format);
void hal_cir_set_jvc_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
void hal_cir_rx_jvc_pre_irq (void *data);


#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_CIR_H_"

