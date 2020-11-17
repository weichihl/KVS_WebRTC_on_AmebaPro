/**************************************************************************//**
 * @file     hal_cir.c
 * @brief    This CIR HAL API functions.
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

#include "hal_pinmux.h"
#include "hal_cir.h"

#if CONFIG_CIR_EN

extern void hal_syson_cir_rst(void);

/**
 * @addtogroup ls_hal_cir CIR
 * @{
 */

/**
 *  @brief The CIR interrupt handler.
 *
 *  @param[in]  hid The handler ID, it should be the CIR adapter.
 *
 *  @returns void
 */
void hal_cir_irq_handler (void *hid)
{
    hal_cir_adapter_t *pcir_adp = (hal_cir_adapter_t *)hid;
    
    //==========
    if (pcir_adp->cir_isr_req.b.is_monitor == 1) {
        pcir_adp->base_addr->ier_b.ie_rxld_full = 1;
        pcir_adp->base_addr->ier_b.ie_rxld_end = 1;
    } 
    
    if ((pcir_adp->cir_isr_req_ever.b.is_monitor == 1) && (pcir_adp->base_addr->isr_b.is_rxld_end == 1)) {
        pcir_adp->recv_data_ptr = 0;
        pcir_adp->cir_isr_req_ever.w = 0;
        pcir_adp->base_addr->isr_b.is_rxld_end = 1;
    }     
    //==========
    
    hal_cir_stubs.hal_cir_irq_handler (hid);        

    //==============================================
    if ((pcir_adp->cir_isr_req_ever.b.is_monitor == 1) && ((pcir_adp->base_addr->rxdatacnt & 0x1F) != 0x00)) {
        pcir_adp->cir_isr_req_ever.b.is_monitor = 0;
    }     
    //==============================================
     
}

/**
 *  @brief To register a IRQ handler for the CIR.
 *
 *  @param[in]  handler The interrupt handle function.
 *
 *  @returns void
 */
void hal_cir_irq_reg (irq_handler_t handler)
{
    hal_cir_stubs.hal_cir_irq_reg (handler);
}

/**
 *  @brief To un-register the CIR IRQ handler.
 *
 *  @returns void
 */
void hal_cir_irq_unreg (void)
{
    hal_cir_stubs.hal_cir_irq_unreg ();
}

/**
 *  @brief Initialize the CIR hardware and turn on the CIR
 *
 *  @param[in]  pcir_adp The CIR adapter.
 *  @param[in]  pin_sel CIR pin mux.
 *  @param[in]  app_pin_sel The pin combination for the user application.
 *                      If the pin is selected, this pin will be initialized.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_init (hal_cir_adapter_t *pcir_adp, cir_pin_sel_t pin_sel, cir_app_pin_sel_t app_pin_sel)
{
    hal_status_t ret = HAL_OK;
    io_pin_t *pin_list;
    u8 cir_app_pin_sel_table[3] = {0, 2, 4};

    pin_list = (io_pin_t *)&hal_cir_stubs.pcir_pin_group[pin_sel * 7 + cir_app_pin_sel_table[app_pin_sel]];
    ret = hal_pinmux_register (pin_list, PID_CIR0);
    if (ret == HAL_OK) {
        hal_cir_stubs.hal_cir_init (pcir_adp, pin_sel, app_pin_sel);
        hal_cir_irq_reg (hal_cir_irq_handler);
    }

    return ret;
}

/**
 *  @brief De-initialize of the CIR hardware and turn off the CIR.
 *
 *  @param[in]  pcir_adp The CIR adapter.
 *
 *  @returns void
 */
void hal_cir_deinit (hal_cir_adapter_t *pcir_adp)
{
    io_pin_t *pin_list;
    u8 cir_app_pin_sel_table[3] = {0, 2, 4};

    hal_cir_stubs.hal_cir_deinit (pcir_adp);
    pin_list = (io_pin_t *)&hal_cir_stubs.pcir_pin_group[pcir_adp->pin_sel * 7 + cir_app_pin_sel_table[pcir_adp->app_pin_sel]];
    hal_pinmux_unregister (pin_list, PID_CIR0);
}

/**
 *  @brief Reset the CIR and registers.
 *
 *  @returns void
 */
void hal_cir_reset (void)
{
    hal_syson_cir_rst();
}

/**
*  @brief To enter a critical code section, mainly it
*         disable the CIR interrupt to prevent race condition.
*
*  @returns void
*/
void hal_cir_enter_critical (void)
{
    hal_cir_stubs.hal_cir_enter_critical ();
}

/**
 *  @brief To exit a critical code section, it will re-enable the CIR interrupt
 *         only when the exiting critical section is the top level.
 *
 *  @returns void
 */
void hal_cir_exit_critical (void)
{
    hal_cir_stubs.hal_cir_exit_critical ();
}

/**
 *  @brief According to the carrier frequency, caulate the parameters of the carrier generator.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] carrier_fq The TX carrier frequency.
 *  @param[in] tx_sclkdiv The divisor of the system clock to generate a proper tick time for the CIR carrier generation.
 *      When set tx_sclkdiv is 0, find the suitable value automatically.
 *  @param[in] cari_hl_ratio Set the high and low ratio of the carrier. cari_hl_ratio[7:0]: low, cari_hl_ratio[15:8]: high.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_tx_carrier_init (hal_cir_adapter_t *pcir_adp, u32 carrier_fq, u32 tx_sclkdiv, u16 cari_hl_ratio)
{
    return hal_cir_stubs.hal_cir_tx_carrier_init (pcir_adp, carrier_fq, tx_sclkdiv, cari_hl_ratio);
}

/**
 *  @brief According to the carrier frequency, caulate the parameters of the receiver.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] carrier_fq The RX carrier frequency.
 *  @param[in] rx_sclkdiv The divisor of the system clock to generate a proper clock for the RX input sampling and trigger tick event.
 *      When set rx_sclkdiv is 0, find the suitable value automatically.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_rx_carrier_init (hal_cir_adapter_t *pcir_adp, u32 carrier_fq, u32 rx_sclkdiv)
{
    return hal_cir_stubs.hal_cir_rx_carrier_init (pcir_adp, carrier_fq, rx_sclkdiv);
}

/**
 *  @brief Set the TX symbol parameter.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] psymdesc
 *                      time_us - The symbol period and the unit is us.
 *                      symbol - The symbol is Symbol_01 ~ Symbol_08.
 *                      symtype - If this symbol is the carrier symbol, set this value is Carrier_Tp.
 *                          If need TX signal level is high, set this value is Space_High.
 *                          If need TX signal level is low, set this value is Space_Low.
 *                          If need TX signal level is the carrier, set this value is Carrier_Tp.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_set_tx_symbol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_symdesc_t *psymdesc)
{
    return hal_cir_stubs.hal_cir_set_tx_symbol (pcir_adp, psymdesc);
}

/**
 *  @brief Set the RX symbol parameter.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] psymdesc
 *                      time_us - The symbol period. This unit is us. If this value is 0, this symbol is disabled.
 *                      symbol - The symbol is Symbol_01 ~ Symbol_08.
 *                      symtype - If this symbol is the carrier symbol, set this value is Carrier_Tp.
 *                          If need RX signal level is high, set this value is Space_High.
 *                          If need RX signal level is low, set this value is Space_Low.
 *                          If need RX signal level is the carrier, set this value is Carrier_Tp.
 *                      time_tolerance_us - Decode the tolerance of the symbol period and the unit is us.
 *                      carrier_tolerance_cnt - Decode the tolerance of symbol carrier counts.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_set_rx_symbol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_symdesc_t *psymdesc)
{
    return hal_cir_stubs.hal_cir_set_rx_symbol (pcir_adp, psymdesc);
}

/**
 *  @brief Set the end time after receiving the last symbol.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] time_us The symbol period. This unit is us.
 *
 *  @returns void
 */
void hal_cir_set_rx_timeout (hal_cir_adapter_t *pcir_adp, u16 time_us)
{
    hal_cir_stubs.hal_cir_set_rx_timeout (pcir_adp, time_us);
}

/**
 *  @brief Set CIR TX and RX reset.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] cir_trx CirNon: no effect, CirTx: Tx reset, CirRx: Rx reset, CirTRx: TX and RX reset.
 *
 *  @returns void
 */
void hal_cir_rst (hal_cir_adapter_t *pcir_adp, cir_TRX_t cir_trx)
{
    hal_cir_stubs.hal_cir_rst (pcir_adp, cir_trx);
}

/**
 *  @brief When receive the symbol, this symbol is separated into two symbols.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] psymsprt Set the symbol.
 *                      symbol_in - This symbol is separated.
 *                      symbol_out_first - The first symbol is generated.
 *                      symbol_out_second - The second symbol is generated.
 *  @param[in] group The group of the separated symbol is SymGroup0 or SymGroup1.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_symbol_separate (hal_cir_adapter_t *pcir_adp, hal_cir_symsprt_t *psymsprt, cir_sym_group_t group)
{
    return hal_cir_stubs.hal_cir_symbol_separate (pcir_adp, psymsprt, group);
}

/**
 *  @brief Two symbols are decoded to the bit 0.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] psym_in Set the symbol.
 *                      symbol_in_first - The first symbol.
 *                      symbol_in_second - The second symbol.
 *  @param[in] group The group of the decoded symbol is SymGroup0 or SymGroup1.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_symbol_bit0 (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group)
{
    return hal_cir_stubs.hal_cir_symbol_bit0 (pcir_adp, psym_in, group);
}

/**
 *  @brief Two symbols are decoded to the bit 1.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] psym_in Set the symbol.
 *                      symbol_in_first - The first symbol.
 *                      symbol_in_second - The second symbol.
 *  @param[in] group the group ofThe decoded symbol is SymGroup0 or SymGroup1.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_symbol_bit1 (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group)
{
    return hal_cir_stubs.hal_cir_symbol_bit1 (pcir_adp, psym_in, group);
}

/**
 *  @brief Start to decode symbols according to two symbols [symbol_in_second, symbol_in_first].
 *
 *  @param[in]  pcir_adp The CIR adapter.
 *  @param[in]  psym_in Set the symbol.
 *                      symbol_in_first - The first symbol.
 *                      symbol_in_second - The second symbol.
 *  @param[in]  group The group of the decoded symbol is SymGroup0 ~ SymGroup3.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_symbol_strm (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group)
{
    return hal_cir_stubs.hal_cir_symbol_strm (pcir_adp, psym_in, group);
}

/**
 *  @brief These are the callback function and argument for matching the start symbol of SymGroup0.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] callback The callback function.
 *  @param[in] arg The callback argument.
 *
 *  @returns void
 */
void hal_cir_irq_strm_gp0_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg)
{
    hal_cir_stubs.hal_cir_irq_strm_gp0_cb (pcir_adp, callback, arg);
}

/**
 *  @brief These are the callback function and argument for matching the start symbol of SymGroup1.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] callback The callback function.
 *  @param[in] arg The callback argument.
 *
 *  @returns void
 */
void hal_cir_irq_strm_gp1_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg)
{
    hal_cir_stubs.hal_cir_irq_strm_gp1_cb (pcir_adp, callback, arg);
}

/**
 *  @brief Set the monitor data and the number of monitor counts from the LSB.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] monitor_data The monitor data.
 *  @param[in] monitor_cnt Monitor counts 1~32 from the LSB. 0: inactive
 *  @param[in] en 0: disable, 1: enable.
 *
 *  @returns void
 */
void hal_cir_set_monitor (hal_cir_adapter_t *pcir_adp, u32 monitor_data, u32 monitor_cnt, BOOL en)
{
    hal_cir_stubs.hal_cir_set_monitor (pcir_adp, monitor_data, monitor_cnt, en);
}

/**
 *  @brief These are the callback function and argument  for the monitor.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] callback The callback function.
 *  @param[in] arg The callback argument.
 *
 *  @returns void
 */
void hal_cir_irq_monitor_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg)
{
    hal_cir_stubs.hal_cir_irq_monitor_cb (pcir_adp, callback, arg);
}

/**
 *  @brief When finish to send TX data, eneter this callback function.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] callback The callback function.
 *  @param[in] arg The callback argument.
 *
 *  @returns void
 */
void hal_cir_irq_send_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg)
{
    hal_cir_stubs.hal_cir_irq_send_cb (pcir_adp, callback, arg);
}

/**
 *  @brief Set the RX data pointer and length.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] data The RX data pinter.
 *  @param[in] data_limit Set the limit number of RX data, and the unit is 32 bits.
 *
 *  @returns void
 */
void hal_cir_recv (hal_cir_adapter_t *pcir_adp, u32 *data, u32 data_limit)
{
    hal_cir_stubs.hal_cir_recv (pcir_adp, data, data_limit);
}

/**
 *  @brief When finish to get RX data, eneter this callback function.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] callback The callback function.
 *  @param[in] arg The callback argument.
 *
 *  @returns void
 */
void hal_cir_irq_recv_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg)
{
    hal_cir_stubs.hal_cir_irq_recv_cb (pcir_adp, callback, arg);
}

/**
 *  @brief When happen the any CIR interrupt, eneter this callback function.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] callback The callback function.
 *  @param[in] arg The callback argument.
 *
 *  @returns void
 */
void hal_cir_irq_ie_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg)
{
    hal_cir_stubs.hal_cir_irq_ie_cb (pcir_adp, callback, arg);
}

/**
 *  @brief Get the setting symbol type according to the carrier and initial value.
 *
 *  @param[in] carrier The CIR has carrier or not.
 *  @param[in] value The CIR input initial is high or low.
 *
 *  @returns The CIR symbol type
 */
cir_sym_type_t hal_cir_get_carrier_init_level (cir_carrier_t carrier, cir_init_value_t value)
{
    return hal_cir_stubs.hal_cir_get_carrier_init_level (carrier, value);
}

/**
 *  @brief Make the TX initial setting and TX protocol table.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] ptx_protocol_setting Set the TX parameter of the tx protocol frame for CIR API.
 *  @param[in] pcir_tx_protocol Set TX protocol table.
 *
 *  @returns void
 */
void hal_cir_set_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting, hal_cir_tx_protocol_t *pcir_tx_protocol)
{
    hal_cir_stubs.hal_cir_set_tx_protocol (pcir_adp, ptx_protocol_setting, pcir_tx_protocol);
}

/**
 *  @brief Load TX symbol parameters according to the protocol table.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] pcir_tx_protocol Set TX protocol table.
 *  @param[in] symtype_level Set the symbol level of no carrier site.
 *  @param[in] symtype_carrier Set the symbol level of carrier site.
 *
 *  @returns void
 */
void hal_cir_load_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_t *pcir_tx_protocol, cir_sym_type_t symtype_level, cir_sym_type_t symtype_carrier)
{
    hal_cir_stubs.hal_cir_load_tx_protocol (pcir_adp, pcir_tx_protocol, symtype_level, symtype_carrier);
}

/**
 *  @brief Make the RX initial setting and RX protocol table.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] prx_protocol_desc Set the RX parameter of the RX protocol frame for CIR API.
 *  @param[in] pcir_rx_protocol Set RX protocol table.
 *
 *  @returns void
 */
void hal_cir_set_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc, hal_cir_rx_protocol_t *pcir_rx_protocol)
{
    hal_cir_stubs.hal_cir_set_rx_protocol (pcir_adp, prx_protocol_desc, pcir_rx_protocol);
}

/**
 *  @brief Load RX symbol parameters according to the protocol table.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] pcir_rx_protocol Set RX protocol table.
 *  @param[in] symtype_level Set the symbol level of no carrier site.
 *  @param[in] symtype_carrier Set the symbol level of carrier site.
 *
 *  @returns void
 */
void hal_cir_load_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_t *pcir_rx_protocol, cir_sym_type_t symtype_level, cir_sym_type_t symtype_carrier)
{
    hal_cir_stubs.hal_cir_load_rx_protocol (pcir_adp, pcir_rx_protocol, symtype_level, symtype_carrier);
}

/**
 *  @brief Set the RX data pointer and format for CIR API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] data Set the RX data pointer.
 *  @param[in] format Record the format to distinguish the different format in the interrupt.
 *  @param[in] data_32bits_num Set the limit number of RX data, and the unit is 32 bits.
 *
 *  @returns void
 */
void hal_cir_protocol_recv (hal_cir_adapter_t *pcir_adp, u32 *data, u8 format, u32 data_32bits_num)
{
    hal_cir_stubs.hal_cir_protocol_recv (pcir_adp, data, format, data_32bits_num);
}

/**
 *  @brief Change the data from MSB to LSB or LSB to MSB.
 *
 *  @param[in] x Input data.
 *
 *  @returns Output data.
 */
u32 hal_cir_data_reverse (u32 x)
{
    return hal_cir_stubs.hal_cir_data_reverse (x);
}

/**
 *  @brief Set the symbols to monitor.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] en Enable or disable the function.
 *  @param[in] filter_sym_cnt Set the counts for the symbol filter.
 *
 *  @returns void
 */
void hal_cir_set_rx_filter_en (hal_cir_adapter_t *pcir_adp, BOOL en, u8 filter_sym_cnt)
{
    hal_cir_stubs.hal_cir_set_rx_filter_en (pcir_adp, en, filter_sym_cnt);
}

/**
 *  @brief Reset the RX filter.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *
 *  @returns void
 */
void hal_cir_set_rx_filter_reset (hal_cir_adapter_t *pcir_adp)
{
    hal_cir_stubs.hal_cir_set_rx_filter_reset (pcir_adp);
}

/**
 *  @brief Set the waitting time for the next monitor symbol. When timeout event happens, restart to monitor the first symbol.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] en Enable or disable the function.
 *  @param[in] ftime_us Set the time. The unit is us.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_set_rx_filter_timeout (hal_cir_adapter_t *pcir_adp, BOOL en, u32 ftime_us)
{
    return hal_cir_stubs.hal_cir_set_rx_filter_timeout (pcir_adp, en, ftime_us);
}

/**
 *  @brief Set the monitor symbols and the order.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] symbol Set the CIR symbol
 *  @param[in] symb_in_seq Set the monitor order.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_cir_set_rx_filter_symbol (hal_cir_adapter_t *pcir_adp, cir_sym_t symbol, u8 symb_in_seq)
{
    return hal_cir_stubs.hal_cir_set_rx_filter_symbol (pcir_adp, symbol, symb_in_seq);
}

/**
 *  @brief These are the callback function and argument for the filter function.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] callback The callback function.
 *  @param[in] arg The callback argument.
 *
 *  @returns void
 */
void hal_cir_irq_filter_cb (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg)
{
    hal_cir_stubs.hal_cir_irq_filter_cb (pcir_adp, callback, arg);
}

/**
 *  @brief Set the TX initial output.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] symtype_level The CIR symbol type.
 *
 *  @returns void
 */
void hal_cir_init_output_frame (hal_cir_adapter_t *pcir_adp, cir_sym_type_t symtype_level)
{
    hal_cir_stubs.hal_cir_init_output_frame (pcir_adp, symtype_level);
}

/**
 *  @brief Set the TX data pointer and length.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] data The TX data pinter.
 *  @param[in] length The TX data length.
 *
 *  @returns void
 */
void hal_cir_send_protocol (hal_cir_adapter_t *pcir_adp, u32 *data, u32 length)
{
    hal_cir_stubs.hal_cir_send_protocol (pcir_adp, data, length);
}

/**
 *  @brief Make the TX initial setting and protocol table for NEC API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] ptx_protocol_setting Set the TX parameter of the TX protocol frame for CIR API.
 *                      output_init - Set the tx initial level.
 *                      carrier - Set the protocol has the carrier site or not.
 *                      tx_sclkdiv - Set tx sclk to divide.
 *                      irq_tx_end_cb - Set the tx end callback function.
 *                      irq_tx_end_arg - Set the argument of the tx end callback function.
 *
 *  @returns void
 */
void hal_cir_set_nec_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting)
{
    hal_cir_stubs.hal_cir_set_nec_tx_protocol (pcir_adp, ptx_protocol_setting);
}

/**
 *  @brief Set the TX data pointer and format for NEC API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] data Set the TX data pointer.
 *  @param[in] format Set the format.
 *
 *  @returns void
 */
void hal_cir_nec_send (hal_cir_adapter_t *pcir_adp, void *data, cir_nec_tx_format_t format)
{
    hal_cir_stubs.hal_cir_nec_send (pcir_adp, data, format);
}

/**
 *  @brief Make the RX initial setting and protocol table for NEC API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] prx_protocol_desc Set the RX parameter of the RX protocol frame for CIR API.
 *                      input_init - Set the rx initial level.
 *                      carrier - Set the protocol has the carrier site or not.
 *                      rx_sclkdiv - Set rx sclk to divide.
 *                      symbol_time_tolerance_us - Set the the time tolerance of the rx symbol.
 *                      carrier_tolerance_cnt - Set the the carrier tolerance of the rx symbol.
 *                      check_frame_end_time_us - Set the end time after receiving the last symbol.
 *                      irq_rx_end_cb - Set the rx end callback function.
 *                      irq_rx_end_arg - Set the argument of the rx end callback function.
 *
 *  @returns void
 */
void hal_cir_set_nec_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc)
{
    hal_cir_stubs.hal_cir_set_nec_rx_protocol (pcir_adp, prx_protocol_desc);
}

/**
 *  @brief Process the RX format of the NEC protocol for NEC API.
 *
 *  @param[in] data The CIR adapter.
 *
 *  @returns void
 */
void hal_cir_rx_nec_pre_irq(void *data)
{
    hal_cir_stubs.hal_cir_rx_nec_pre_irq (data);
}

/**
 *  @brief Make the TX initial setting and protocol table for SONY-SIRC API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] ptx_protocol_setting Set the TX parameter of the TX protocol frame for CIR API.
 *                      output_init - Set the tx initial level.
 *                      carrier - Set the protocol has the carrier site or not.
 *                      tx_sclkdiv - Set tx sclk to divide.
 *                      irq_tx_end_cb - Set the tx end callback function.
 *                      irq_tx_end_arg - Set the argument of the tx end callback function.
 *
 *  @returns void
 */
void hal_cir_set_sony_sirc_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting)
{
    hal_cir_stubs.hal_cir_set_sony_sirc_tx_protocol (pcir_adp, ptx_protocol_setting);
}

/**
 *  @brief Set the TX data pointer and format for SONY-SIRC API.
 *
 *  @param[in]  pcir_adp The CIR adapter.
 *  @param[in]  data Set the TX data pointer.
 *  @param[in]  format Set the format.
 *
 *  @returns void
 */
void hal_cir_sony_sirc_send (hal_cir_adapter_t *pcir_adp, void *data, cir_sony_sirc_format_t format)
{
    hal_cir_stubs.hal_cir_sony_sirc_send (pcir_adp, data, format);
}

/**
 *  @brief Make the RX initial setting and protocol table for SONY-SIRC API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] prx_protocol_desc Set the RX parameter of the RX protocol frame for CIR API.
 *                      input_init - Set the rx initial level.
 *                      carrier - Set the protocol has the carrier site or not.
 *                      rx_sclkdiv - Set rx sclk to divide.
 *                      symbol_time_tolerance_us - Set the the time tolerance of the rx symbol.
 *                      carrier_tolerance_cnt - Set the the carrier tolerance of the rx symbol.
 *                      check_frame_end_time_us - Set the end time after receiving the last symbol.
 *                      irq_rx_end_cb - Set the rx end callback function.
 *                      irq_rx_end_arg - Set the argument of the rx end callback function.
 *
 *  @returns void
 */
void hal_cir_set_sony_sirc_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc)
{
    hal_cir_stubs.hal_cir_set_sony_sirc_rx_protocol (pcir_adp, prx_protocol_desc);
}

/**
 *  @brief Process the RX format of the SONY-SIRC protocol for SONY-SIRC API.
 *
 *  @param[in] data The CIR adapter.
 *
 *  @returns void
 */
void hal_cir_rx_sony_sirc_pre_irq(void *data)
{
    hal_cir_stubs.hal_cir_rx_sony_sirc_pre_irq (data);
}

/**
 *  @brief Make the TX initial setting and protocol table for PHILIPS-RC5 API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] ptx_protocol_setting Set the TX parameter of the TX protocol frame for CIR API.
 *                      output_init - Set the tx initial level.
 *                      carrier - Set the protocol has the carrier site or not.
 *                      tx_sclkdiv - Set tx sclk to divide.
 *                      irq_tx_end_cb - Set the tx end callback function.
 *                      irq_tx_end_arg - Set the argument of the tx end callback function.
 *
 *  @returns void
 */
void hal_cir_set_philips_rc5_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting)
{
    hal_cir_stubs.hal_cir_set_philips_rc5_tx_protocol (pcir_adp, ptx_protocol_setting);
}

/**
 *  @brief Set the TX data pointer and format for PHILIPS-RC5 API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] data Set the TX data pointer.
 *
 *  @returns void
 */
void hal_cir_philips_rc5_send (hal_cir_adapter_t *pcir_adp, hal_cir_philips_rc5_format_t *data)
{
    hal_cir_stubs.hal_cir_philips_rc5_send (pcir_adp, data);
}

/**
 *  @brief Make the RX initial setting and protocol table for PHILIPS-RC5 API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] prx_protocol_desc Set the RX parameter of the RX protocol frame for CIR API.
 *                      input_init - Set the rx initial level.
 *                      carrier - Set the protocol has the carrier site or not.
 *                      rx_sclkdiv - Set rx sclk to divide.
 *                      symbol_time_tolerance_us - Set the the time tolerance of the rx symbol.
 *                      carrier_tolerance_cnt - Set the the carrier tolerance of the rx symbol.
 *                      check_frame_end_time_us - Set the end time after receiving the last symbol.
 *                      irq_rx_end_cb - Set the rx end callback function.
 *                      irq_rx_end_arg - Set the argument of the rx end callback function.
 *
 *  @returns void
 */
void hal_cir_set_philips_rc5_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc)
{
    hal_cir_stubs.hal_cir_set_philips_rc5_rx_protocol (pcir_adp, prx_protocol_desc);
}

/**
 *  @brief Process the RX format of the PHILIPS-RC5 protocol for PHILIPS-RC5 API.
 *
 *  @param[in] data The CIR adapter.
 *
 *  @returns void
 */
void hal_cir_rx_philips_rc5_pre_irq(void *data)
{
    hal_cir_stubs.hal_cir_rx_philips_rc5_pre_irq (data);
}

/**
 *  @brief Make the TX initial setting and protocol table for JVC API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] ptx_protocol_setting Set the TX parameter of the TX protocol frame for CIR API.
 *                      output_init - Set the tx initial level.
 *                      carrier - Set the protocol has the carrier site or not.
 *                      tx_sclkdiv - Set tx sclk to divide.
 *                      irq_tx_end_cb - Set the tx end callback function.
 *                      irq_tx_end_arg - Set the argument of the tx end callback function.
 *
 *  @returns void
 */
void hal_cir_set_jvc_tx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting)
{
    hal_cir_stubs.hal_cir_set_jvc_tx_protocol (pcir_adp, ptx_protocol_setting);
}

/**
 *  @brief Set the TX data pointer and format for JVC API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] data Set the TX data pointer.
 *  @param[in] format Set the format.
 *
 *  @returns void
 */
void hal_cir_jvc_send (hal_cir_adapter_t *pcir_adp, void *data, cir_jvc_tx_format_t format)
{
    hal_cir_stubs.hal_cir_jvc_send (pcir_adp, data, format);
}

/**
 *  @brief Make the RX initial setting and protocol table for JVC API.
 *
 *  @param[in] pcir_adp The CIR adapter.
 *  @param[in] prx_protocol_desc Set the RX parameter of the RX protocol frame for CIR API.
 *                      input_init - Set the rx initial level.
 *                      carrier - Set the protocol has the carrier site or not.
 *                      rx_sclkdiv - Set rx sclk to divide.
 *                      symbol_time_tolerance_us - Set the the time tolerance of the rx symbol.
 *                      carrier_tolerance_cnt - Set the the carrier tolerance of the rx symbol.
 *                      check_frame_end_time_us - Set the end time after receiving the last symbol.
 *                      irq_rx_end_cb - Set the rx end callback function.
 *                      irq_rx_end_arg - Set the argument of the rx end callback function.
 *
 *  @returns void
 */
void hal_cir_set_jvc_rx_protocol (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc)
{
    hal_cir_stubs.hal_cir_set_jvc_rx_protocol (pcir_adp, prx_protocol_desc);
}

/**
 *  @brief Process the RX format of the JVC protocol for JVC API.
 *
 *  @param[in] data The CIR adapter.
 *
 *  @returns void
 */
void hal_cir_rx_jvc_pre_irq(void *data)
{
    hal_cir_stubs.hal_cir_rx_jvc_pre_irq (data);
}

/** @} */ /* End of group ls_hal_cir */

#endif

