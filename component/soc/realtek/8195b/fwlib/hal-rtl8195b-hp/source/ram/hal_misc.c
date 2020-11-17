/**************************************************************************//**
 * @file     hal_misc.c
 * @brief    This file implements the entry functions of the HAL Misc. ROM functions.
 *
 * @version  V1.00
 * @date     2017-05-24
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

#include "hal_misc.h"
#include "hal_pinmux.h"
#include "hal_gpio.h"

/**
 * @addtogroup hs_hal_misc Misc.
 * @{
 */

/**
  * @brief The data type of SWD pins list.
  */
typedef struct hal_swd_pin_s {
    uint8_t swclk_pin;
    uint8_t swdio_pin;
    uint8_t eol;    // end of list
} hal_swd_pin_t, *phal_swd_pin_t;

/**
  * @brief The data type of SWD pins list.
  */
typedef struct hal_jtag_pin_s {
    uint8_t trst_pin;
    uint8_t tdi_pin;
    uint8_t tdo_pin;
    uint8_t tms_pin;
    uint8_t tclk_pin;
    uint8_t eol;    // end of list
} hal_jtag_pin_t, *phal_jtag_pin_t;

/**
  * @brief Pin mux selection table for SWD pins
  */
const hal_swd_pin_t swd_pins[2] = {
    {PIN_E4, PIN_E3, 0xFF},     ///< S0: pin mux selection 0
    {PIN_C6, PIN_C5, 0xFF}      ///< S1: pin mux selection 1
};

/**
  * @brief Pin mux selection table for JTAG pins
  */
const hal_jtag_pin_t jtag_pins[2] = {
    {PIN_E0, PIN_E1, PIN_E2, PIN_E3, PIN_E4, 0xFF},     ///< S0: pin mux selection 0
    {PIN_C2, PIN_C3, PIN_C4, PIN_C5, PIN_C6, 0xFF}      ///< S1: pin mux selection 1
};

/**
 *  @brief Controls the enable of SWD pins.
 *
 *  @param[in]  pin_sel The pin mux selection, 0 ~ 1.
 *  @param[in]  en  Pin enable control:
 *                    - 0: Disable SWD pins.
 *                    - 1: Enable SWD pins.
 *
 *  @return     HAL_ERR_PARA:  Input pin mux selection is invalid.
 *  @return     HAL_ERR_CONFLICT: pin conflict with other peripheral device.
 *  @return     HAL_OK:  pin control OK.
 */
hal_status_t hal_misc_swd_pin_ctrl (uint8_t pin_sel, BOOL en)
{
    hal_status_t ret;

    if (pin_sel > 1) {
        // invalid pin mux selection
        return HAL_ERR_PARA;
    }

    if (en) {
        ret = hal_pinmux_register((io_pin_t *)&swd_pins[pin_sel], PID_SWD);
        if (ret == HAL_OK) {
            hal_gpio_pull_ctrl(swd_pins[pin_sel].swclk_pin, Pin_PullUp);
            hal_gpio_pull_ctrl(swd_pins[pin_sel].swdio_pin, Pin_PullUp);
//            hal_gpio_schmitt_ctrl (swd_pins[pin_sel].swclk_pin, ON);
//            hal_gpio_schmitt_ctrl (swd_pins[pin_sel].swdio_pin, ON);
        }
    } else {
        ret = hal_pinmux_unregister((io_pin_t *)&swd_pins[pin_sel], PID_SWD);
        if (ret == HAL_OK) {
            hal_gpio_pull_ctrl(swd_pins[pin_sel].swclk_pin, Pin_PullNone);
            hal_gpio_pull_ctrl(swd_pins[pin_sel].swdio_pin, Pin_PullNone);
//            hal_gpio_schmitt_ctrl (swd_pins[pin_sel].swclk_pin, OFF);
        }
    }

    return ret;
}

/**
 *  @brief Controls the enable of JTAG pins.
 *
 *  @param[in]  pin_sel The pin mux selection, 0 ~ 1.
 *  @param[in]  en  Pin enable control:
 *                    - 0: Disable JTAG pins.
 *                    - 1: Enable JTAG pins.
 *
 *  @return     HAL_ERR_PARA:  Input pin mux selection is invalid.
 *  @return     HAL_ERR_CONFLICT: pin conflict with other peripheral device.
 *  @return     HAL_OK:  pin control OK.
 */
hal_status_t hal_misc_jtag_pin_ctrl (uint8_t pin_sel, BOOL en)
{
    hal_status_t ret;

    if (pin_sel > 1) {
        // invalid pin mux selection
        return HAL_ERR_PARA;
    }

    if (en) {
        ret = hal_pinmux_register((io_pin_t *)&jtag_pins[pin_sel], PID_JTAG);
        if (ret == HAL_OK) {
            hal_gpio_pull_ctrl(jtag_pins[pin_sel].tclk_pin, Pin_PullUp);
            hal_gpio_pull_ctrl(jtag_pins[pin_sel].tdi_pin, Pin_PullUp);
            hal_gpio_pull_ctrl(jtag_pins[pin_sel].tdo_pin, Pin_PullUp);
            hal_gpio_pull_ctrl(jtag_pins[pin_sel].tms_pin, Pin_PullUp);
            hal_gpio_pull_ctrl(jtag_pins[pin_sel].trst_pin, Pin_PullUp);
            hal_gpio_schmitt_ctrl (jtag_pins[pin_sel].tclk_pin, ON, 0);
        }
    } else {
        ret = hal_pinmux_unregister((io_pin_t *)&jtag_pins[pin_sel], PID_JTAG);
        if (ret == HAL_OK) {
            hal_gpio_pull_ctrl(jtag_pins[pin_sel].tclk_pin, Pin_PullNone);
            hal_gpio_pull_ctrl(jtag_pins[pin_sel].tdi_pin, Pin_PullNone);
            hal_gpio_pull_ctrl(jtag_pins[pin_sel].tdo_pin, Pin_PullNone);
            hal_gpio_pull_ctrl(jtag_pins[pin_sel].tms_pin, Pin_PullNone);
            hal_gpio_pull_ctrl(jtag_pins[pin_sel].trst_pin, Pin_PullNone);
            hal_gpio_schmitt_ctrl (jtag_pins[pin_sel].tclk_pin, OFF, 0);
        }
    }

    return ret;
}

/** @} */ /* End of group hs_hal_misc */

