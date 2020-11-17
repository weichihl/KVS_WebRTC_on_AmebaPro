/**************************************************************************//**
 * @file     hal_syson.h
 * @brief    The HAL API implementation for the SysOn functions.
 * @version  V1.00
 * @date     2017-06-23
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#ifndef _HAL_SYSON_H_
#define _HAL_SYSON_H_
#include "cmsis.h"

/** 
 * @addtogroup ls_hal_syson
 * @{
 */
 
#ifdef  __cplusplus
extern "C"
{
#endif

extern const hal_syson_func_stubs_t hal_syson_stubs;     // symbol from linker script

/** 
 *  @brief Registers an interrupt handler for the SysOn wake up event.
 *
 *  @param[in] event The Wake up event ID.
 *  @param[in] handler The Wake up event handler (callback function).
 *  @param[in] arg The argument of the wake up event handler (callback function).
 *
 *  @returns void
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
 *  @returns void
 */ 
__STATIC_INLINE
void hal_syson_unreg_wake_event_handler (sys_wake_event_t event)
{
    hal_syson_stubs.hal_syson_unreg_wake_event_handler (event);
}

/** 
 *  @brief Enables a SysOn wake up event.
 *
 *  @param[in] event The Wake up event ID.
 *
 *  @returns void
 */ 
__STATIC_INLINE
void hal_syson_enable_wake_event (sys_wake_event_t event)
{
    hal_syson_stubs.hal_syson_enable_wake_event (event);
}

/** 
 *  @brief Disables a SysOn wake up event.
 *
 *  @param[in] event The Wake up event ID.
 *
 *  @return  void
 */ 
__STATIC_INLINE
void hal_syson_disable_wake_event (sys_wake_event_t event)
{
    hal_syson_stubs.hal_syson_disable_wake_event (event);
}

/** 
 *  @brief Registers an interrupt handler for the SysOn function.
 *
 *  @param[in] handler The IRQ handle function.
 *
 *  @return  void
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

/** @} */ /* End of group ls_hal_syson */

