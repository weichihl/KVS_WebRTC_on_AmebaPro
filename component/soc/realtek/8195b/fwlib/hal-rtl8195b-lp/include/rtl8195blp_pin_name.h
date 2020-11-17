/**************************************************************************//**
 * @file     rtl8195bl_pin_name.h
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

#ifndef RTL8195BLP_PIN_NAME_H
#define RTL8195BLP_PIN_NAME_H

#ifdef __cplusplus
extern "C" {
#endif

#define PIN_NAME(port_id, pin_id)           (((port_id) << 5) | (pin_id))
#define PIN_NAME_2_PORT(pin_name)           (((pin_name) >> 5) & 0x07)
#define PIN_NAME_2_PIN(pin_name)            ((pin_name) & 0x1F)

#define MAX_PIN_IN_PORT                     (16)  // the maximum pin number in a port

/*! define Chip IO Port Name */
enum {
    PORT_A         = 0,

    PORT_MAX_NUM   = 1
};

/*! define Chip IO Pin Name */
enum {
    PIN_A0         = PIN_NAME(PORT_A, 0),
    PIN_A1         = PIN_NAME(PORT_A, 1),
    PIN_A2         = PIN_NAME(PORT_A, 2),
    PIN_A3         = PIN_NAME(PORT_A, 3),
    PIN_A4         = PIN_NAME(PORT_A, 4),
    PIN_A5         = PIN_NAME(PORT_A, 5),
    PIN_A6         = PIN_NAME(PORT_A, 6),
    PIN_A7         = PIN_NAME(PORT_A, 7),
    PIN_A8         = PIN_NAME(PORT_A, 8),
    PIN_A9         = PIN_NAME(PORT_A, 9),
    PIN_A10        = PIN_NAME(PORT_A, 10),
    PIN_A11        = PIN_NAME(PORT_A, 11),
    PIN_A12        = PIN_NAME(PORT_A, 12),
    PIN_A13        = PIN_NAME(PORT_A, 13),

    PIN_LIST_END   = 0xFF
};

/*! define Pin mux selection */
enum  _pin_sel_e
{
    PinSel0       = 0,
    PinSel1       = 1,
    PinSel2       = 2,
    PinSel3       = 3
};
typedef uint8_t pin_sel_t;

/**
  \brief  define the structure for IO pin.
 */
typedef struct io_pin_s {
    union {
        uint8_t pin_name;
        struct {
            uint8_t pin:5;              /*!< bit:  4.. 0  the pin index in a port */
            uint8_t port:3;             /*!< bit:  7.. 5 the IO port index */
        } pin_name_b;
    };
} io_pin_t, *pio_pin_t;

#ifdef __cplusplus
}
#endif

#endif /* RTL8195BLP_PIN_NAME_H */


