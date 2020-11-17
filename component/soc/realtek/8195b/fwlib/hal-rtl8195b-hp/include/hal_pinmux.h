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

#ifndef _HAL_PINMUX_H_
#define _HAL_PINMUX_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#if !defined(CONFIG_BUILD_NONSECURE)

extern const hal_pin_manag_func_stubs_t hal_pin_manag_stubs;
extern hal_status_t hal_pin_pwrdwn_rtl8195bhp_patch (io_pin_t *pin_list, uint8_t periphl_id);

/**
 *  @brief Initial the pin mux manager.
 *
 *  @param[in]  pinmux_manag  The pin mux manager entity.
 *
 *  @returns    void.
 */
static __inline void hal_pinmux_manager_init (hal_pin_mux_mang_t *pinmux_manag)
{
    pinmux_manag->pin_reg_func = hal_pin_manag_stubs.hal_pin_register;
    pinmux_manag->pin_unreg_func = hal_pin_manag_stubs.hal_pin_unregister;
    pinmux_manag->ioport_pwrup_ctrl_func = hal_pin_manag_stubs.hal_pin_pwrup;
//    pinmux_manag->ioport_pwrdn_ctrl_func = hal_pin_manag_stubs.hal_pin_pwrdwn;
    pinmux_manag->ioport_pwrdn_ctrl_func = hal_pin_pwrdwn_rtl8195bhp_patch;
    hal_pin_manag_stubs.hal_pinmux_manager_init (pinmux_manag);
}

/**
 *  @brief To register a list of IO pin to the "in using" record.
 *
 *  @param[in]  pin_list  The IO pin list. The list is end with a byte value 0xFF.
 *  @param[in]  periphl_id  The ID of the peripheral will use these pins.
 *
 *  @return     HAL_OK:  Pin register OK.
 *  @return     HAL_ERR_CONFLICT:  Pin conflict. At least one of pin in the list
 *              is occupied by other peripheral device.
 */
static __inline hal_status_t hal_pin_register (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pin_register (pin_list, periphl_id);
}

/**
 *  @brief To unregister a list of IO pins from the "in using" record.
 *
 *  @param[in]  pin_list  The IO pin list. The list is end with a byte value 0xFF.
 *  @param[in]  periphl_id  The ID of the peripheral own these pins.
 *
 *  @return     HAL_OK:  Pin unregister OK.
 *  @return     HAL_ERR_PARA:  The peripheral ID doesn't match with the ID on the "in using" record.
 */
static __inline hal_status_t hal_pin_unregister (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pin_unregister (pin_list, periphl_id);
}

/**
 *  @brief To power on (enable) a list of IO pad .
 *
 *  @param[in]  pin_list  The IO pin list. The list is end with a byte value 0xFF.
 *  @param[in]  periphl_id  The ID of the peripheral owns these pins.
 *
 *  @return     HAL_OK:  IO pad power up OK.
 */
static __inline hal_status_t hal_pin_pwrup (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pin_pwrup (pin_list, periphl_id);
}

/**
 *  @brief To power down (disable) a list of IO pad.
 *
 *  @param[in]  pin_list  The IO pin list. The list is end with a byte value 0xFF.
 *  @param[in]  periphl_id  The ID of the peripheral owns these pins.
 *
 *  @return     HAL_OK:  IO pad power down OK.
 */
static __inline hal_status_t hal_pin_pwrdwn (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pin_pwrdwn (pin_list, periphl_id);
}

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
static __inline hal_status_t hal_pinmux_register (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pinmux_register (pin_list, periphl_id);
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
static __inline hal_status_t hal_pinmux_unregister (io_pin_t *pin_list, uint8_t periphl_id)
{
    return hal_pin_manag_stubs.hal_pinmux_unregister (pin_list, periphl_id);
}

#else   // else of "#if !defined(CONFIG_BUILD_NONSECURE)"
// Build for Non-Secure
#if 0
void hal_pinmux_manager_init_nsc (hal_pin_mux_mang_t *pinmux_manag);
hal_status_t hal_pin_register_nsc (io_pin_t *pin_list, uint8_t periphl_id);
hal_status_t hal_pin_unregister_nsc (io_pin_t *pin_list, uint8_t periphl_id);
hal_status_t hal_pin_pwrup_nsc (io_pin_t *pin_list, uint8_t periphl_id);
hal_status_t hal_pin_pwrdwn_nsc (io_pin_t *pin_list, uint8_t periphl_id);
#endif
hal_status_t hal_pinmux_register_nsc (io_pin_t *pin_list, uint8_t periphl_id);
hal_status_t hal_pinmux_unregister_nsc (io_pin_t *pin_list, uint8_t periphl_id);

#if 0
#define hal_pinmux_manager_init         hal_pinmux_manager_init_nsc
#define hal_pin_register                hal_pin_register_nsc
#define hal_pin_unregister              hal_pin_unregister_nsc
#define hal_pin_pwrup                   hal_pin_pwrup_nsc
#define hal_pin_pwrdwn                  hal_pin_pwrdwn_nsc
#endif
#define hal_pinmux_register             hal_pinmux_register_nsc
#define hal_pinmux_unregister           hal_pinmux_unregister_nsc

#endif

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_PINMUX_H_"

