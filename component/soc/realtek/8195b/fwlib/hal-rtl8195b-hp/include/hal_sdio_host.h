/**************************************************************************//**
 * @file    hal_sdio_host.h
 * @brief   The HAL API implementation for SDIO Host controller
 * @version V1.00
 * @date    2017-07-12
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
#ifndef _HAL_SDIO_HOST_H_
#define _HAL_SDIO_HOST_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#if (((CHIP_VER == CHIP_A_CUT)||(CHIP_VER == CHIP_B_CUT)||(CHIP_VER == CHIP_C_CUT)) && (defined(CONFIG_BUILD_RAM)))
hal_status_t hal_sdioh_init_host_rtl8195bhp_patch (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_pin_sel_t pin_sel);
hal_status_t hal_sdioh_erase_rtl8195bhp_patch (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u64 end_addr);
hal_status_t hal_sdioh_switch_bus_speed_rtl8195bhp_patch (hal_sdio_host_adapter_t *psdioh_adapter, u8 speed);
hal_status_t hal_sdioh_get_supported_speed_rtl8195bhp_patch (hal_sdio_host_adapter_t *psdioh_adapter, u8 *value);
hal_status_t hal_sdioh_init_card_rtl8195bhp_patch (hal_sdio_host_adapter_t *psdioh_adapter);
void hal_sdioh_deinit_rtl8195bhp_patch (hal_sdio_host_adapter_t *psdioh_adapter);
hal_status_t hal_sdioh_write_data_rtl8195bhp_patch (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u16 blk_cnt, u8 *wbuf_32align);
void hal_sdioh_card_insert_hook_rtl8195bhp_patch (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_card_detect pcallback, void *pdata);
#endif

/** 
 * @addtogroup hs_hal_sdio_host SDIO_HOST
 * @{
 * brief The SDIO Host HAL RAM APIs. These APIs is provided for user application to control the SDIO Host hardware.
 */

/// the selection of SDIO host pinmux
#define SDIOH_PIN_SEL       (SdiohPinSel0)



void hal_sdioh_pin_ctrl (sdioh_pin_sel_t pin_sel, BOOL en);
void hal_sdioh_irq_reg (irq_handler_t irq_handler);
void hal_sdioh_irq_unreg (void);
hal_status_t hal_sdioh_init_host (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_pin_sel_t pin_sel);
hal_status_t hal_sdioh_init_card (hal_sdio_host_adapter_t *psdioh_adapter);
void hal_sdioh_deinit (hal_sdio_host_adapter_t *psdioh_adapter);
hal_status_t hal_sdioh_read_data (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u16 blk_cnt, u8 *rbuf_32align);
hal_status_t hal_sdioh_write_data (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u16 blk_cnt, u8 *wbuf_32align);
hal_status_t hal_sdioh_erase (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u64 end_addr);
hal_status_t hal_sdioh_stop_transmission (hal_sdio_host_adapter_t *psdioh_adapter);
hal_status_t hal_sdioh_get_card_status (hal_sdio_host_adapter_t *psdioh_adapter);
hal_status_t hal_sdioh_get_sd_status (hal_sdio_host_adapter_t *psdioh_adapter, u8 *buf_32align);
hal_status_t hal_sdioh_switch_bus_speed (hal_sdio_host_adapter_t *psdioh_adapter, u8 speed);
u8 hal_sdioh_get_curr_signal_level (hal_sdio_host_adapter_t *psdioh_adapter);
hal_status_t hal_sdioh_get_supported_speed (hal_sdio_host_adapter_t *psdioh_adapter, u8 *value);
void hal_sdioh_card_insert_hook (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_card_detect pcallback, void *pdata);
void hal_sdioh_card_remove_hook (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_card_detect pcallback, void *pdata);
void hal_sdioh_task_yield_hook (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_task_yield task_yield);

/** @} */ /* End of group hs_hal_sdio_host */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SDIO_HOST_H_"

