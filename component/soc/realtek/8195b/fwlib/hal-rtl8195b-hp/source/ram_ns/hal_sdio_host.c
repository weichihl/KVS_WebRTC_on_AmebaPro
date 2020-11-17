/**************************************************************************//**
 * @file    hal_sdio_host.c
 * @brief   The SDIO Host HAL API functions
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
#include "hal_sdio_host.h"
#include "hal_pinmux.h"
#include "hal_cache.h"

#if CONFIG_SDIO_HOST_EN

/** 
 * @addtogroup hs_hal_sdio_host SDIO_HOST
 * @{
 */

extern hal_sdioh_func_stubs_t hal_sdioh_stubs;

u8 sdioh_pin_table_patch[] = {
    PIN_B0, PIN_B1, PIN_B2, PIN_B3, PIN_B4, PIN_B5, PIN_B6, PIN_B7, 0xFF,    // S0
    PIN_B0, PIN_B1, PIN_B2, PIN_B3, PIN_B4, PIN_B5, PIN_F10, PIN_F4, 0xFF,   // S1
    PIN_B0, PIN_B1, PIN_B2, PIN_B3, PIN_B4, PIN_B5, PIN_G0, PIN_G1, 0xFF     // S2
};



void hal_sdioh_pin_ctrl (sdioh_pin_sel_t pin_sel, BOOL en)
{
    hal_sdioh_stubs.hal_sdioh_pin_ctrl(pin_sel, en);
}


void hal_sdioh_irq_reg (irq_handler_t irq_handler)
{
    hal_sdioh_stubs.hal_sdioh_irq_reg(irq_handler);
}


void hal_sdioh_irq_unreg (void)
{
    hal_sdioh_stubs.hal_sdioh_irq_unreg();
}


/** 
 *  @brief To initialize the SDIO host controller.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *  @param[in]  pin_sel The pinmux selection.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdioh_init_host (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_pin_sel_t pin_sel)
{
    hal_status_t ret;
    io_pin_t *pin_list;


    #if (((CHIP_VER == CHIP_A_CUT)||(CHIP_VER == CHIP_B_CUT)||(CHIP_VER == CHIP_C_CUT)) && (defined(CONFIG_BUILD_RAM)))
    pin_list = (io_pin_t*)&sdioh_pin_table_patch[pin_sel*9];
    #else
    pin_list = (io_pin_t*)&hal_sdioh_stubs.sdioh_pin_table[pin_sel*9];
    #endif
    ret = hal_pinmux_register (pin_list, PID_SDIOH);
    if (ret == HAL_OK) {
	#if (((CHIP_VER == CHIP_A_CUT)||(CHIP_VER == CHIP_B_CUT)||(CHIP_VER == CHIP_C_CUT)) && (defined(CONFIG_BUILD_RAM)))
            return hal_sdioh_init_host_rtl8195bhp_patch(psdioh_adapter, pin_sel);
        #else
            return hal_sdioh_stubs.hal_sdioh_init_host(psdioh_adapter, pin_sel);
        #endif
    }
    else {
        return ret;
    }
}


/** 
 *  @brief To initialize the SD memory card.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdioh_init_card (hal_sdio_host_adapter_t *psdioh_adapter)
{
    psdioh_adapter->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;
    psdioh_adapter->dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;
    #if (((CHIP_VER == CHIP_A_CUT)||(CHIP_VER == CHIP_B_CUT)||(CHIP_VER == CHIP_C_CUT)) && (defined(CONFIG_BUILD_RAM)))
        return hal_sdioh_init_card_rtl8195bhp_patch(psdioh_adapter);
    #else
        return hal_sdioh_stubs.hal_sdioh_init_card(psdioh_adapter);
    #endif
}


/** 
 *  @brief To de-initialize the SDIO host controller.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *
 *  @returns    void.
 */
void hal_sdioh_deinit (hal_sdio_host_adapter_t *psdioh_adapter)
{
    u8 pin_sel = psdioh_adapter->pin_mux_sel;
    io_pin_t *pin_list;


    psdioh_adapter->dcache_invalidate_by_addr = NULL;
    psdioh_adapter->dcache_clean_by_addr = NULL;
    #if (((CHIP_VER == CHIP_A_CUT)||(CHIP_VER == CHIP_B_CUT)||(CHIP_VER == CHIP_C_CUT)) && (defined(CONFIG_BUILD_RAM)))
    hal_sdioh_deinit_rtl8195bhp_patch(psdioh_adapter);
    pin_list = (io_pin_t*)&sdioh_pin_table_patch[pin_sel*9];
    #else
    hal_sdioh_stubs.hal_sdioh_deinit(psdioh_adapter);
    pin_list = (io_pin_t*)&hal_sdioh_stubs.sdioh_pin_table[pin_sel*9];
    #endif
    hal_pinmux_unregister (pin_list, PID_SDIOH);
}


/** 
 *  @brief To read data from the SD card.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *  @param[in]  start_addr The start address to begin reading from the card.
 *  @param[in]  blk_cnt The block count.
 *  @param[in]  rbuf_32align The buffer to read data blocks (must be 32-Byte alignment).
 *
 *  @returns    The result.
 */
hal_status_t hal_sdioh_read_data (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u16 blk_cnt, u8 *rbuf_32align)
{
    return hal_sdioh_stubs.hal_sdioh_read_data(psdioh_adapter, start_addr, blk_cnt, rbuf_32align);
}


/** 
 *  @brief To write data to the SD card.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *  @param[in]  start_addr The start address to begin writing to the card.
 *  @param[in]  blk_cnt The block count.
 *  @param[in]  wbuf_32align The buffer to write data blocks (must be 32-Byte alignment).
 *
 *  @returns    The result.
 */
hal_status_t hal_sdioh_write_data (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u16 blk_cnt, u8 *wbuf_32align)
{
    #if (((CHIP_VER == CHIP_A_CUT)||(CHIP_VER == CHIP_B_CUT)||(CHIP_VER == CHIP_C_CUT)) && (defined(CONFIG_BUILD_RAM)))
    return hal_sdioh_write_data_rtl8195bhp_patch(psdioh_adapter, start_addr, blk_cnt, wbuf_32align);
    #else
    return hal_sdioh_stubs.hal_sdioh_write_data(psdioh_adapter, start_addr, blk_cnt, wbuf_32align);
    #endif
}


/** 
 *  @brief To erase data in the SD card.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *  @param[in]  start_addr The start address to begin erasing.
 *  @param[in]  end_addr The end address to begin erasing.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdioh_erase (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u64 end_addr)
{
    #if ((CHIP_VER == CHIP_A_CUT) && (defined(CONFIG_BUILD_RAM)))
    return hal_sdioh_erase_rtl8195bhp_patch(psdioh_adapter, start_addr, end_addr);
    #else
    return hal_sdioh_stubs.hal_sdioh_erase(psdioh_adapter, start_addr, end_addr);
    #endif
}


/** 
 *  @brief To stop the SD bus transmission.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdioh_stop_transmission (hal_sdio_host_adapter_t *psdioh_adapter)
{
    return hal_sdioh_stubs.hal_sdioh_stop_transmission(psdioh_adapter);
}


/** 
 *  @brief To get the current state of the SD card.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdioh_get_card_status (hal_sdio_host_adapter_t *psdioh_adapter)
{
    return hal_sdioh_stubs.hal_sdioh_get_card_status(psdioh_adapter);
}


/** 
 *  @brief To get the SD status from the SD card.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *  @param[in]  buf_32align The buffer to store the SD status (must be 32-Byte alignment).
 *
 *  @returns    The result.
 */
hal_status_t hal_sdioh_get_sd_status (hal_sdio_host_adapter_t *psdioh_adapter, u8 *buf_32align)
{
    return hal_sdioh_stubs.hal_sdioh_get_sd_status(psdioh_adapter, buf_32align);
}


/** 
 *  @brief To switch the SD bus speed.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *  @param[in]  speed The specified bus speed.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdioh_switch_bus_speed (hal_sdio_host_adapter_t *psdioh_adapter, u8 speed)
{
    #if ((CHIP_VER == CHIP_A_CUT) && (defined(CONFIG_BUILD_RAM)))
        return hal_sdioh_switch_bus_speed_rtl8195bhp_patch(psdioh_adapter, speed);
    #else
        return hal_sdioh_stubs.hal_sdioh_switch_bus_speed(psdioh_adapter, speed);
    #endif
}


/** 
 *  @brief To get the current signaling level.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *
 *  @returns    The signaling level (1: 1.8V, 0: 3.3V).
 */
u8 hal_sdioh_get_curr_signal_level (hal_sdio_host_adapter_t *psdioh_adapter)
{
    return hal_sdioh_stubs.hal_sdioh_get_curr_signal_level(psdioh_adapter);
}


/** 
 *  @brief To get the speed mode supported by the card.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *  @param[in]  value The supported speed mode.
 *
 *  @returns    The result.
 */
hal_status_t hal_sdioh_get_supported_speed (hal_sdio_host_adapter_t *psdioh_adapter, u8 *value)
{
    #if ((CHIP_VER == CHIP_A_CUT) && (defined(CONFIG_BUILD_RAM)))
    return hal_sdioh_get_supported_speed_rtl8195bhp_patch(psdioh_adapter, value);
    #else
    return hal_sdioh_stubs.hal_sdioh_get_supported_speed(psdioh_adapter, value);
    #endif
}


/** 
 *  @brief To hook a callback function for SD card insertion interrupt.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *  @param[in]  pcallback The callback function.
 *  @param[in]  pdata The argument of the callback function.
 *
 *  @returns    void.
 */
void hal_sdioh_card_insert_hook (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_card_detect pcallback, void *pdata)
{
    #if (((CHIP_VER == CHIP_A_CUT)||(CHIP_VER == CHIP_B_CUT)||(CHIP_VER == CHIP_C_CUT)) && (defined(CONFIG_BUILD_RAM)))
    hal_sdioh_card_insert_hook_rtl8195bhp_patch(psdioh_adapter, pcallback, pdata);
    #else
    hal_sdioh_stubs.hal_sdioh_card_insert_hook(psdioh_adapter, pcallback, pdata);
    #endif
}



/** 
 *  @brief To hook a callback function for SD card removal interrupt.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *  @param[in]  pcallback The callback function.
 *  @param[in]  pdata The argument of the callback function.
 *
 *  @returns    void.
 */
void hal_sdioh_card_remove_hook (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_card_detect pcallback, void *pdata)
{
    hal_sdioh_stubs.hal_sdioh_card_remove_hook(psdioh_adapter, pcallback, pdata);
}


/** 
 *  @brief To hook a callback function to make OS do a context-switch while waiting.
 *
 *  @param[in]  psdioh_adapter The SDIO host HAL adapter.
 *  @param[in]  task_yield The callback function.
 *
 *  @returns    void.
 */
void hal_sdioh_task_yield_hook (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_task_yield task_yield)
{
    hal_sdioh_stubs.hal_sdioh_task_yield_hook(psdioh_adapter, task_yield);
}

/** @} */ /* End of group hs_hal_sdio_host */

#endif  // end of "#if CONFIG_SDIO_HOST_EN

