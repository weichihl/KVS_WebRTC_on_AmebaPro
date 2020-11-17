/**************************************************************************//**
 * @file     hal_syson.h
 * @brief    The HAL API implementation for the system wake up functions.
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

#ifndef _HAL_SYSON_H_
#define _HAL_SYSON_H_
#include "cmsis.h"

/**
 * @addtogroup hs_hal_syson
 * @{
 */

#ifdef  __cplusplus
extern "C"
{
#endif

extern const hal_syson_func_stubs_t hal_syson_stubs;

/**
 *  @brief Configures the clock source of system.
 *
 *  @param[in] clk_src System clock source selection, 0: ANA(4M), 1: PLL(200M/300M)
 *  @param[in] clk_sel System PLL clock freq selection, 0: 200M, 1: 300M
 *
 *  @return  void
 */
__STATIC_INLINE
void hal_syson_sys_clk_sel (uint32_t clk_src, uint32_t clk_sel)
{
    hal_syson_stubs.hal_syson_sys_clk_sel (clk_src, clk_sel);
}

/**
 *  @brief Initials the clock divider of the clock source of system.
 *
 *  @param[in] div_en Clock devider enable.
 *  @param[in] div_sel Clock devider value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_syson_sys_clk_div (uint32_t div_en, uint32_t div_sel)
{
    hal_syson_stubs.hal_syson_sys_clk_div (div_en, div_sel);
}

/**
 *  @brief Gets current CPU clock freq.
 *
 *  @returns The CPU clock frequency.
 */
__STATIC_INLINE
uint32_t hal_syson_query_sys_clk (void)
{
    return hal_syson_stubs.hal_syson_query_sys_clk();
}

/**
 *  @brief Set the System(CPU) clock rate.
 *
 *  @param[in] sys_clk The target system clock rate.
 *
 *  @return  void.
 */
__STATIC_INLINE
void hal_syson_set_sys_clk (sys_clock_rate_t sys_clk)
{
    hal_syson_stubs.hal_syson_set_sys_clk (sys_clk);
}

/**
 *  @brief Registers an interrupt handler for the SysOn wake up event.
 *
 *  @param[in] event The Wake up event ID.
 *  @param[in] handler The Wake up event handler (callback function).
 *  @param[in] arg The argument of the wake up event handler (callback function).
 *
 *  @return  void
 */
__STATIC_INLINE
void hal_syson_reg_wake_event_handler (sys_wake_event_t event, syson_irq_handler_t handler, uint32_t arg)
{
    hal_syson_stubs.hal_syson_reg_wake_event_handler (event, handler, arg);
}

/**
 *  @brief Un-registers an interrupt handler for the SysOn wake up event.
 *
 *  @param[in] event The Wake up event ID.
 *
 *  @return  void
 */
__STATIC_INLINE
void hal_syson_unreg_wake_event_handler (sys_wake_event_t event)
{
    hal_syson_stubs.hal_syson_unreg_wake_event_handler (event);
}

/**
 *  @brief Enables a SysOn wake up event.
 *
 *  @param[in] psyson_adp The SysOn adapter.
 *  @param[in] event The Wake up event ID.
 *
 *  @return  void
 */
__STATIC_INLINE
void hal_syson_enable_wake_event (sys_wake_event_t event)
{
    hal_syson_stubs.hal_syson_enable_wake_event (event);
}

/**
 *  @brief Disables a SysOn wake up event.
 *
 *  @param[in] psyson_adp The SysOn adapter.
 *  @param[in] event The Wake up event ID.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_syson_disable_wake_event (sys_wake_event_t event)
{
    hal_syson_stubs.hal_syson_disable_wake_event (event);
}

/**
 *  @brief Registers an interrupt handler for the SysOn function.
 *
 *  @param[in] psyson_adp The SysOn adapter.
 *  @param[in] handler The IRQ handle function.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_syson_reg_irq (int_vector_t handler)
{
    hal_syson_stubs.hal_syson_reg_irq (handler);
}

/**
 *  @brief Initials the System On domain management entity.
 *
 *  @param[in] psyson_adp The SysOn adapter.
 *
 *  @return  void.
 */
__STATIC_INLINE
void hal_syson_init (hal_syson_adapter_t *psyson_adp)
{
    hal_syson_stubs.hal_syson_init (psyson_adp);
}

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SYSON_H_"

/** @} */ /* End of group hs_hal_syson */

