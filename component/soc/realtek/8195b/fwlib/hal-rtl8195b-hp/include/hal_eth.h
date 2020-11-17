/**************************************************************************//**
 * @file    hal_eth.h
 * @brief   The HAL API implementation for Ethernet MAC controller
 * @version V1.00
 * @date    2017-07-20
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
#ifndef _HAL_ETH_H_
#define _HAL_ETH_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif
// scottchen
#if ((CHIP_VER <= CHIP_C_CUT) && (defined(CONFIG_BUILD_RAM)))
hal_status_t hal_eth_init_rtl8195bhp_patch (hal_eth_adapter_t *peth_adapter, eth_if_sel_t if_sel, eth_pin_sel_t pin_sel);
void hal_eth_set_link_rtl8195bhp_patch (hal_eth_adapter_t *peth_adapter, s32 speed, s32 duplex);
hal_status_t hal_eth_init_force_spd_rtl8195bhp (hal_eth_adapter_t *peth_adapter, eth_if_sel_t if_sel, eth_pin_sel_t pin_sel);
s32 hal_eth_write_data_rtl8195bhp_patch (hal_eth_adapter_t *peth_adapter, u8 *data, u32 size);
u32 hal_eth_send_pkt_rtl8195bhp_patch (hal_eth_adapter_t *peth_adapter);
u32 hal_eth_receive_pkt_rtl8195bhp_patch (hal_eth_adapter_t *peth_adapter);
u32 hal_eth_read_data_rtl8195bhp_patch (hal_eth_adapter_t *peth_adapter, u8 *data, u32 size);
#endif
// scottchen end

/** 
 * @addtogroup hs_hal_ethernet ETHERNET
 * @{
 * brief The ETHERNET HAL RAM APIs. These APIs is provided for user application to control the Ethernet MAC hardware.
 */

hal_status_t hal_eth_pin_ctrl (eth_pin_sel_t pin_sel, BOOL en);
void hal_eth_set_interface (eth_if_sel_t if_sel);
void hal_eth_irq_handler (void);
void hal_eth_irq_reg (irq_handler_t irq_handler);
void hal_eth_irq_unreg (void);
void hal_eth_set_mac_addr (u8 *addr);
void hal_eth_get_mac_addr (u8 *addr);
void hal_eth_set_desc_num (u8 tx_desc_no, u8 rx_desc_no);
void hal_eth_set_desc_addr (u8 *tx_desc, u8 *rx_desc);
void hal_eth_set_pkt_buf (u8 *tx_pkt_buf, u8 *rx_pkt_buf);
hal_status_t hal_eth_init (eth_if_sel_t if_sel, eth_pin_sel_t pin_sel);
hal_status_t hal_eth_init_force_spd (eth_if_sel_t if_sel, eth_pin_sel_t pin_sel);  // scottchen
void hal_eth_deinit (void);
s32 hal_eth_write_data (u8 *data, u32 size);
u32 hal_eth_send_pkt (void);
u32 hal_eth_receive_pkt (void);
u32 hal_eth_read_data (u8 *data, u32 size);
u32 hal_eth_get_link_status (void);
void hal_eth_set_link (s32 speed, s32 duplex);
void hal_eth_callback_hook (eth_callback_t pcallback);
void hal_eth_task_yield_hook (eth_task_yield task_yield);

/** @} */ /* End of group hs_hal_ethernet */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_ETH_H_"

