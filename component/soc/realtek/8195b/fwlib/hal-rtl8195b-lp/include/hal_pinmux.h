/**************************************************************************//**
 * @file     hal_pinmux.h
 * @brief    The HAL API implementation for the pin mux managemment.
 * @version  V1.00
 * @date     2016-12-30
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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

#ifndef _HAL_PINMUX_H_
#define _HAL_PINMUX_H_
#include "cmsis.h"
 
#ifdef  __cplusplus
extern "C"
{
#endif

extern const hal_pin_manag_func_stubs_t hal_pin_manag_stubs;

#if defined(CONFIG_BUILD_RAM) && (CHIP_VER <= CHIP_B_CUT)
/** 
 *  @brief To power down (disable) a list of IO pin.
 *
 *  @param pin_list The IO pin list to be powered on
 *
 *  @returns Result
 */
hal_status_t hal_pin_pwrdwn_patch (io_pin_t *pin_list, uint8_t periphl_id);
#endif

/** 
 *  @brief To initial the pin mux manager.
 *
 *  @param pinmux_manag The pin mux manager entity.
 *
 *  @returns Result
 */ 
static __inline void hal_pinmux_manager_init (hal_pin_mux_mang_t *pinmux_manag)
{
    pinmux_manag->pin_reg_func = hal_pin_manag_stubs.hal_pin_register;
    pinmux_manag->pin_unreg_func = hal_pin_manag_stubs.hal_pin_unregister;
    pinmux_manag->ioport_pwrup_ctrl_func = (io_port_pwrup_t)(hal_pin_manag_stubs.hal_pin_pwrup);
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER <= CHIP_B_CUT)    
    pinmux_manag->ioport_pwrdn_ctrl_func = (io_port_pwrdn_t)hal_pin_pwrdwn_patch;
#else
    pinmux_manag->ioport_pwrdn_ctrl_func = (io_port_pwrdn_t)(hal_pin_manag_stubs.hal_pin_pwrdwn);
#endif
    hal_pin_manag_stubs.hal_pinmux_manager_init (pinmux_manag);
}

/** 
 *  @brief To register an IO pin to in using table.
 *
 *  @param pin The pin to be registered
 *
 *  @returns Result
 */ 
static __inline hal_status_t hal_pin_register (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pin_register (pin_list, periphl_id);
}

/** 
 *  @brief To unregister an IO pin from the using table.
 *
 *  @param pin The pin to be un-registered
 *
 *  @returns None
 */ 
static __inline hal_status_t hal_pin_unregister (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pin_unregister (pin_list, periphl_id);
}

/** 
 *  @brief To power on (enable) a ist of IO pin .
 *
 *  @param pin_list The IO pin list to be powered on
 *
 *  @returns Result
 */ 
static __inline hal_status_t hal_pin_pwrup (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pin_pwrup (pin_list, periphl_id);
}

/** 
 *  @brief To power down (disable) a list of IO pin.
 *
 *  @param pin_list The IO pin list to be powered on
 *
 *  @returns Result
 */ 
static __inline hal_status_t hal_pin_pwrdwn (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pin_pwrdwn (pin_list, periphl_id);
}

/** 
 *  @brief To register an IO pin to in using table.
 *
 *  @param pin The pin to be registered
 *
 *  @returns Result
 */ 
static __inline hal_status_t hal_pinmux_register (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pinmux_register (pin_list, periphl_id);
}

/** 
 *  @brief To unregister an IO pin from the using table.
 *
 *  @param pin The pin to be un-registered
 *
 *  @returns None
 */ 
static __inline hal_status_t hal_pinmux_unregister (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pinmux_unregister (pin_list, periphl_id);
}

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_PINMUX_H_"

