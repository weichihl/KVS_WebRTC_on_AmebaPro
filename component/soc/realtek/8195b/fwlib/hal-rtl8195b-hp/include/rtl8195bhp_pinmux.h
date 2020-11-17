/**************************************************************************//**
 * @file     rtl8195bh_pinmux.h
 * @brief    Define the IC pin name and IO port name
 * @version  V1.00
 * @date     2016-07-20
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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

#ifndef RTL8195BHP_PIN_MUX_H
#define RTL8195BHP_PIN_MUX_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rtl8195bhp_pin_name.h"

typedef hal_status_t (*pin_register_t) (io_pin_t *pin_list, uint8_t periphl_id);
typedef hal_status_t (*pin_unregister_t) (io_pin_t *pin_list, uint8_t periphl_id);
typedef hal_status_t (*pin_validation_t) (io_pin_t *pin_list, uint8_t periphl_id);
typedef hal_status_t (*io_port_pwrup_t) (io_pin_t *pin_list, uint8_t periphl_id);
typedef hal_status_t (*io_port_pwrdn_t) (io_pin_t *pin_list, uint8_t periphl_id);

/**
  \brief  Pin management data structure to handle pin mux conflct, validate, power down management functions.
*/
typedef struct hal_pin_mux_mang_s {
    pin_register_t pin_reg_func;                ///< the callback function for pin register: usage record and conflict checking
    pin_unregister_t pin_unreg_func;            ///< the callback function for pin un-register
    pin_validation_t pin_validat_func;          ///< the callback function for pin validation checking
    io_port_pwrup_t ioport_pwrup_ctrl_func;     ///< the callback function for GPIO pin power up control
    io_port_pwrdn_t ioport_pwrdn_ctrl_func;     ///< the callback function for GPIO pin power down control
    uint16_t pinmux_reg_log[PORT_MAX_NUM];      ///< the bit map to record each pin is in using or not
    uint16_t pinmux_pwr_log[PORT_MAX_NUM];      ///< the bit map to record each pin is powered(enabled) or not
    uint8_t *pinmux_reg_rec;                    ///< the array to record each pin is allocated to which peripheral
} hal_pin_mux_mang_t, *phal_pin_mux_mang_t;

void hal_pinmux_manager_init_rtl8195bhp (hal_pin_mux_mang_t *pinmux_manag);
hal_status_t hal_pin_register_rtl8195bhp (io_pin_t *pin_list, uint8_t periphl_id);
hal_status_t hal_pin_unregister_rtl8195bhp (io_pin_t *pin_list, uint8_t periphl_id);
hal_status_t hal_pin_pwrup_rtl8195bhp (io_pin_t *pin_list, uint8_t periphl_id);
hal_status_t hal_pin_pwrdwn_rtl8195bhp (io_pin_t *pin_list, uint8_t periphl_id);
hal_status_t hal_pinmux_register_rtl8195bhp (io_pin_t *pin_list, uint8_t periphl_id);
hal_status_t hal_pinmux_unregister_rtl8195bhp (io_pin_t *pin_list, uint8_t periphl_id);

/**
  \brief  The data structure of the stubs function for the pin mux management HAL functions in ROM.
*/
typedef struct hal_pin_manag_func_stubs_s {
    phal_pin_mux_mang_t *pppin_manager;
    void (*hal_pinmux_manager_init) (hal_pin_mux_mang_t *pinmux_manag);
    hal_status_t (*hal_pin_register) (io_pin_t *pin_list, uint8_t periphl_id);
    hal_status_t (*hal_pin_unregister) (io_pin_t *pin_list, uint8_t periphl_id);
    hal_status_t (*hal_pin_pwrup) (io_pin_t *pin_list, uint8_t periphl_id);
    hal_status_t (*hal_pin_pwrdwn) (io_pin_t *pin_list, uint8_t periphl_id);
    hal_status_t (*hal_pinmux_register) (io_pin_t *pin_list, uint8_t periphl_id);
    hal_status_t (*hal_pinmux_unregister) (io_pin_t *pin_list, uint8_t periphl_id);

    uint32_t reserved[8];  // reserved space for next ROM code version function table extending.
} hal_pin_manag_func_stubs_t, *phal_pin_manag_func_stubs_t;

#ifdef __cplusplus
}
#endif

#endif /* RTL8195BHP_PIN_MUX_H */


