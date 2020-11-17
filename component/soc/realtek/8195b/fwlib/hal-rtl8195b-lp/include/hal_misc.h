/**************************************************************************//**
 * @file     hal_misc.h
 * @brief    The HAL API implementation for the System Misc.
 * @version  V1.00
 * @date     2016-07-15
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

#ifndef _HAL_MISC_H_
#define _HAL_MISC_H_
#include "cmsis.h"
 
#ifdef  __cplusplus
extern "C"
{
#endif

/** 
 * @addtogroup ls_hal_misc Misc.
 * @{
 */

extern const sys_misc_func_stubs_t sys_misc_stubs;

/** 
 *  @brief Enables the watch dog timer.
 *
 *  @returns    void
 */
void hal_misc_wdt_enable (void);

/** 
 *  @brief Disables the watch dog timer.
 *
 *  @returns    void
 */
void hal_misc_wdt_disable (void);

/** 
 *  @brief Refresh(reload) the watch dog timer counter. 
 *         To prevents the watch dog timer timeout event occurred.
 *
 *  @returns    void
 */
void hal_misc_wdt_refresh (void);

/** 
 *  @brief Initial the HAL Misc. management adapter.
 *
 *  @param[in]  pmisc_adp  The Misc. entity.
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_init (hal_misc_adapter_t *pmisc_adp)
{
    sys_misc_stubs.hal_misc_init (pmisc_adp);
}

/**
 *  @brief Clears the fast boot entry function. 
 *         After doing this the RAM image need to be reload.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_clear_fast_boot (void)
{
    *(sys_misc_stubs.ppRamStartFun) = NULL;
}

/** 
 *  @brief Changes the watch dog timer timeout period.
 *
 *  @param[in]  time_us  The timeout period in micro-second.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_wdt_set_timeout (uint32_t time_us)
{
    sys_misc_stubs.hal_misc_wdt_set_timeout (time_us);
}

/** 
 *  @brief Initials the watch dog timer and setup the timeout period.
 *         The system will be reset by the watch dog timeout event by default.
 *
 *  @param[in]  time_us  The timeout period in micro-second.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_wdt_init (uint32_t time_us)
{
    sys_misc_stubs.hal_misc_wdt_init (time_us);
}

/** 
 *  @brief Registers a handler for the watch dog timeout interrupt.
 *         The WDT timeout interrupt will trigger the NMI interrupt.
 *
 *  @param[in]  handler  The interrupt handler.
 *  @param[in]  arg  The application data will be passed back to the application
 *                   with the callback function.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_wdt_reg_irq (irq_handler_t handler, void *arg)
{
    sys_misc_stubs.hal_misc_wdt_reg_irq (handler, arg);
}

/** 
 *  @brief Registers a handler function for the NMI interrupt which is 
 *         not triggered by the watch dog timer timeout event.
 *
 *  @param[in]  handler  The interrupt handler.
 *  @param[in]  arg  The application data will be passed back to the application
 *                   with the callback function.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_nmi_reg_irq (irq_handler_t handler, void *arg)
{
    sys_misc_stubs.hal_misc_nmi_reg_irq (handler, arg);
}

/** 
 *  @brief To read calibration value of RTC 32K.
 *
 *  @returns The 32k calculation result.
 */
__STATIC_INLINE
u16  hal_misc_rtc_cal_32k (void)
{
    return sys_misc_stubs.hal_misc_rtc_cal_32k ();
}

/** 
 *  @brief To enable wlan SDM Function.
 *
 *  @param[in] bypass_mode: 1: bypass mode, simple /4 path for 128k -> 32K; 
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_misc_sdm_32k_enable (u8 bypass_mode)
{
    sys_misc_stubs.hal_misc_sdm_32k_enable (bypass_mode);
}

/** 
 *  @brief To Read only, HW time loss calculation result.
 *
 *  @returns void
 */
__STATIC_INLINE
u32  hal_misc_read_sdm_32k_time_loss (void)
{
    return sys_misc_stubs.hal_misc_read_sdm_32k_time_loss ();
}

/** 
 *  @brief To set wlan SDM time loss mode Function.
 *
 *  @param[in] time_loss_set, 1:sw set src clk  higher than 128k clk; 0:sw set src clk  lower than 128k clk
 *  @param[in] ttime_loss_reg, set time loss regs
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_misc_set_sdm_32k_time_loss (u8 time_loss_set, u32 time_loss_reg)
{
    sys_misc_stubs.hal_misc_set_sdm_32k_time_loss (time_loss_set, time_loss_reg);
}

/** 
 *  @brief Configures the LS platform 32K clock source.
 *
 *  @param[in]  clk_src  The 32K clock source selection.
 *                         - Ext_Xtal_32K(0): Use the external 32768 Hz Oscillator.
 *                         - Int_Osc_128K(1): Use internal 128K clock source with SDM clock divider.
 *  @param[in]  sdm_bypass The SDM(Sigma-Delta modulation) bypass mode enable flag.
 *                           - 0: The 32K clock is from the SDM adapter output.
 *                           - 1: Bypass the SDM adapter. The 32K clock is derived from 128K clock 
 *                                source devided by 4 directly.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_32k_src_sel (ls_32k_src_t clk_src, uint8_t sdm_bypass)
{
    sys_misc_stubs.hal_misc_32k_src_sel (clk_src, sdm_bypass);
}

/** 
 *  @brief Force triggers a watch dog timer timeout to cause a system reset.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_misc_rst_by_wdt (void)
{
    sys_misc_stubs.hal_misc_rst_by_wdt ();
}

/** 
 *  @brief Invokes a CPU reset. Compares to the system reset, it only reset the
 *         CPU part and the program will be restarted. All other peripheral keeps
 *         their state.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_cpu_rst (void)
{
    sys_misc_stubs.hal_misc_cpu_rst ();
}

/** 
 *  @brief Disables ROM code fast boot. The RAM image need to be reloaded.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_disable_fboot (void)
{
    *(sys_misc_stubs.ppRamStartFun) = (PRAM_FUNCTION_START_TABLE)NULL;
}

/** 
 *  @brief Enables the fast boot.
 *
 *  @param[in]  start_tbl  The start table of the RAM image.
 *                         The ROM boot code will get the RAM entry function from this table.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_enable_fboot (PRAM_FUNCTION_START_TABLE start_tbl)
{
    *(sys_misc_stubs.ppRamStartFun) = start_tbl;
}

/** @} */ /* End of group ls_hal_misc */

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_MISC_H_"

