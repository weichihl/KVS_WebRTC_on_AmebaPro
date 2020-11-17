/**************************************************************************//**
 * @file     rtl8195bh_pin_name.h
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

#ifndef RTL8195BHP_PIN_NAME_H
#define RTL8195BHP_PIN_NAME_H

#ifdef __cplusplus
extern "C" {
#endif

/// Defines the macro to convert port index and pin index to a pin name
#define PIN_NAME(port_id, pin_id)           (((port_id) << 5) | (pin_id))
/// Defines the macro to get the port index by the given pin name
#define PIN_NAME_2_PORT(pin_name)           (((pin_name) >> 5) & 0x07)
/// Defines the macro to get the pin index by the given pin name
#define PIN_NAME_2_PIN(pin_name)            ((pin_name) & 0x1F)

/// Defines maximum number of pin in a GPIO port
#define MAX_PIN_IN_PORT     16

/**
  \brief  Defines Chip's IO port name.
 */
enum {
    PORT_B         = 0,
    PORT_C         = 1,
    PORT_D         = 2,
    PORT_E         = 3,
    PORT_F         = 4,
    PORT_G         = 5,
    PORT_H         = 6,

    PORT_MAX_NUM   = 7
};

/**
  \brief  Defines Chip's IO pin name.
 */
enum {
    PIN_B0         = PIN_NAME(PORT_B, 0),
    PIN_B1         = PIN_NAME(PORT_B, 1),
    PIN_B2         = PIN_NAME(PORT_B, 2),
    PIN_B3         = PIN_NAME(PORT_B, 3),
    PIN_B4         = PIN_NAME(PORT_B, 4),
    PIN_B5         = PIN_NAME(PORT_B, 5),
    PIN_B6         = PIN_NAME(PORT_B, 6),
    PIN_B7         = PIN_NAME(PORT_B, 7),

    PIN_C0         = PIN_NAME(PORT_C, 0),
    PIN_C1         = PIN_NAME(PORT_C, 1),
    PIN_C2         = PIN_NAME(PORT_C, 2),
    PIN_C3         = PIN_NAME(PORT_C, 3),
    PIN_C4         = PIN_NAME(PORT_C, 4),
    PIN_C5         = PIN_NAME(PORT_C, 5),
    PIN_C6         = PIN_NAME(PORT_C, 6),
    PIN_C7         = PIN_NAME(PORT_C, 7),
    PIN_C8         = PIN_NAME(PORT_C, 8),
    PIN_C9         = PIN_NAME(PORT_C, 9),
    PIN_C10        = PIN_NAME(PORT_C,10),
    PIN_C11        = PIN_NAME(PORT_C,11),

    PIN_D0         = PIN_NAME(PORT_D, 0),
    PIN_D1         = PIN_NAME(PORT_D, 1),
    PIN_D2         = PIN_NAME(PORT_D, 2),
    PIN_D3         = PIN_NAME(PORT_D, 3),
    PIN_D4         = PIN_NAME(PORT_D, 4),
    PIN_D5         = PIN_NAME(PORT_D, 5),
    PIN_D6         = PIN_NAME(PORT_D, 6),
    PIN_D7         = PIN_NAME(PORT_D, 7),
    PIN_D8         = PIN_NAME(PORT_D, 8),
    PIN_D9         = PIN_NAME(PORT_D, 9),
    PIN_D10        = PIN_NAME(PORT_D,10),
    PIN_D11        = PIN_NAME(PORT_D,11),
    PIN_D12        = PIN_NAME(PORT_D,12),
    PIN_D13        = PIN_NAME(PORT_D,13),
    PIN_D14        = PIN_NAME(PORT_D,14),
    PIN_D15        = PIN_NAME(PORT_D,15),

    PIN_E0         = PIN_NAME(PORT_E, 0),
    PIN_E1         = PIN_NAME(PORT_E, 1),
    PIN_E2         = PIN_NAME(PORT_E, 2),
    PIN_E3         = PIN_NAME(PORT_E, 3),
    PIN_E4         = PIN_NAME(PORT_E, 4),
    PIN_E5         = PIN_NAME(PORT_E, 5),
    PIN_E6         = PIN_NAME(PORT_E, 6),
    PIN_E7         = PIN_NAME(PORT_E, 7),
    PIN_E8         = PIN_NAME(PORT_E, 8),
    PIN_E9         = PIN_NAME(PORT_E, 9),
    PIN_E10        = PIN_NAME(PORT_E,10),
    PIN_E11        = PIN_NAME(PORT_E,11),
    PIN_E12        = PIN_NAME(PORT_E,12),
    PIN_E13        = PIN_NAME(PORT_E,13),
    PIN_E14        = PIN_NAME(PORT_E,14),
    PIN_E15        = PIN_NAME(PORT_E,15),

    PIN_F0         = PIN_NAME(PORT_F, 0),
    PIN_F1         = PIN_NAME(PORT_F, 1),
    PIN_F2         = PIN_NAME(PORT_F, 2),
    PIN_F3         = PIN_NAME(PORT_F, 3),
    PIN_F4         = PIN_NAME(PORT_F, 4),
    PIN_F5         = PIN_NAME(PORT_F, 5),
    PIN_F6         = PIN_NAME(PORT_F, 6),
    PIN_F7         = PIN_NAME(PORT_F, 7),
    PIN_F8         = PIN_NAME(PORT_F, 8),
    PIN_F9         = PIN_NAME(PORT_F, 9),
    PIN_F10        = PIN_NAME(PORT_F,10),

    PIN_G0         = PIN_NAME(PORT_G, 0),
    PIN_G1         = PIN_NAME(PORT_G, 1),
    PIN_G2         = PIN_NAME(PORT_G, 2),
    PIN_G3         = PIN_NAME(PORT_G, 3),
    PIN_G4         = PIN_NAME(PORT_G, 4),
    PIN_G5         = PIN_NAME(PORT_G, 5),
    PIN_G6         = PIN_NAME(PORT_G, 6),
    PIN_G7         = PIN_NAME(PORT_G, 7),
    PIN_G8         = PIN_NAME(PORT_G, 8),
    PIN_G9         = PIN_NAME(PORT_G, 9),

    PIN_H0         = PIN_NAME(PORT_H, 0),
    PIN_H1         = PIN_NAME(PORT_H, 1),
    PIN_H2         = PIN_NAME(PORT_H, 2),
    PIN_H3         = PIN_NAME(PORT_H, 3),
    PIN_H4         = PIN_NAME(PORT_H, 4),
    PIN_H5         = PIN_NAME(PORT_H, 5),
    PIN_H6         = PIN_NAME(PORT_H, 6),
    PIN_H7         = PIN_NAME(PORT_H, 7),
    PIN_H8         = PIN_NAME(PORT_H, 8),
    PIN_H9         = PIN_NAME(PORT_H, 9),
    PIN_H10        = PIN_NAME(PORT_H,10),
    PIN_H11        = PIN_NAME(PORT_H,11),
    PIN_H12        = PIN_NAME(PORT_H,12),
    PIN_H13        = PIN_NAME(PORT_H,13),
    PIN_H14        = PIN_NAME(PORT_H,14),

    PIN_LIST_END   = 0xFF
};

/**
  \brief  Defines the data type for IO pin.
 */
typedef struct io_pin_s {
    union {
        uint8_t pin_name;
        struct {
            uint8_t pin:5;              ///< bit:  4.. 0  the pin index in a port
            uint8_t port:3;             ///< bit:  7.. 5 the IO port index
        } pin_name_b;
    };
} io_pin_t, *pio_pin_t;

/**
  \brief  Defines the pin mux selection.
 */
enum  _pin_sel_e {
    PinSel0       = 0,
    PinSel1       = 1,
    PinSel2       = 2,
    PinSel3       = 3
};
typedef uint8_t pin_sel_t;

/**
  \brief  Defines the pin of SDIO device.
 */
enum  sdio_pins_e {
    PIN_SDIO_D2     = PIN_B0,
    PIN_SDIO_D3     = PIN_B1,
    PIN_SDIO_CMD    = PIN_B2,
    PIN_SDIO_CLK    = PIN_B3,
    PIN_SDIO_D0     = PIN_B4,
    PIN_SDIO_D1     = PIN_B5,
    PIN_SDIO_INT    = PIN_B6
};


#ifdef __cplusplus
}
#endif

#endif /* RTL8195BHP_PIN_NAME_H */


