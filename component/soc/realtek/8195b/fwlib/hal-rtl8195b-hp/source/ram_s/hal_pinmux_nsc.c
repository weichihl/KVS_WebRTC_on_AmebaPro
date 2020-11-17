/**************************************************************************//**
 * @file     hal_pinmux_nsc.c
 * @brief    The entry functions of Pin Mux HAL API functions for Non-secure.
 *
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
 ******************************************************************************/

#include "hal_pinmux.h"

#if defined(CONFIG_BUILD_SECURE) && !defined(CONFIG_BUILD_BOOT)

#if 0
/**
 *  @brief To initial the pin mux manager.
 *
 *  @param pinmux_manag The pin mux manager entity.
 *
 *  @returns Result
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_pinmux_manager_init_nsc (hal_pin_mux_mang_t *pinmux_manag)
{
    hal_pinmux_manager_init (pinmux_manag);
}

/**
 *  @brief To register an IO pin to in using table.
 *
 *  @param pin The pin to be registered
 *
 *  @returns Result
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_pin_register_nsc (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_register (pin_list, periphl_id);
}

/**
 *  @brief To unregister an IO pin from the using table.
 *
 *  @param pin The pin to be un-registered
 *
 *  @returns None
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_pin_unregister_nsc (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_unregister (pin_list, periphl_id);
}

/**
 *  @brief To power on (enable) a ist of IO pin .
 *
 *  @param pin_list The IO pin list to be powered on
 *
 *  @returns Result
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_pin_pwrup_nsc (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_pwrup (pin_list, periphl_id);
}

/**
 *  @brief To power down (disable) a list of IO pin.
 *
 *  @param pin_list The IO pin list to be powered on
 *
 *  @returns Result
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_pin_pwrdwn_nsc (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_pwrdwn (pin_list, periphl_id);
}
#endif

/**
 *  @brief To register a list of IO pin to the pin mux magagement.
 *         The pin mux management will do the checking of pin conflict and pin valid.
 *         And then power up the IO pad.
 *
 *  @param[in]  pin_list  The IO pin list. The list is end with a byte value 0xFF.
 *  @param[in]  periphl_id  The ID of the peripheral will use these pins.
 *
 *  @return     HAL_OK:  Pin list register OK.
 *  @return     HAL_ERR_CONFLICT:  Pin conflict. At least one of pin in the list
 *              is occupied by other peripheral device.
 *  @return     HAL_ERR_HW: At least one of pin in the pin list is invalid for this IC.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_pinmux_register_nsc (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pinmux_register (pin_list, periphl_id);
}

/**
 *  @brief Unregister a list of IO pins from the pin mux management.
 *         The pin mux management will power down the IO pads.
 *
 *  @param[in]  pin_list  The IO pin list. The list is end with a byte value 0xFF.
 *  @param[in]  periphl_id  The ID of the peripheral own these pins.
 *
 *  @return     HAL_OK:  Pin unregister OK.
 *  @return     HAL_ERR_PARA:  The peripheral doesn't own these pins.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_pinmux_unregister_nsc (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pinmux_unregister (pin_list, periphl_id);
}

#endif // end of "#if defined(CONFIG_BUILD_SECURE)"

