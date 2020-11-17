/**************************************************************************//**
 * @file     rtl8195blp_gpio.h
 * @brief    This file defines GPIO HAL macros and data types.
 *
 * @version  V1.00
 * @date     2016-11-15
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

/**
 * @addtogroup ls_hal_gpio GPIO
 * @{
 */

#ifndef RTL8195BLP_GPIO_H
#define RTL8195BLP_GPIO_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rtl8195blp_gpio_type.h"

/**
  \brief  Defines the data type for GPIO pin name, a GPIO pin name is
          from combination of GPIO port and GPIO pin index.
 */
typedef struct gpio_pin_s {
    union {
        uint8_t pin_name;
        struct {
            uint8_t pin:5;              ///< bit:  4.. 0  the pin index in a port
            uint8_t port:3;             ///< bit:  7.. 5 the port index
        } pin_name_b;
    };
} gpio_pin_t, *pgpio_pin_t;

/// Defines the maximum GPIO pin in a port
#define GPIO_MAX_PIN_IDX            16     // the maximum pin number in a port

/// Defines the maximum GPIO interrupt pins. It is the number of the GPIO IRQ pins this platform can support.
#define GPIO_MAX_INT_PIN            4     // 0 ~ 15, one GPIO IP only support 16 configurable interrupt pin
/// Defines the maximum GPIO debounce pins.
/// It is the number of GPIO pin can enable the debounce function simultaneously.
#define GPIO_MAX_DEBOUNCE_PIN       4     // 0 ~ 15, one GPIO IP only support 16 configurable de-bounce pin
/// define the GPIO port number. It's the number of the GPIO port this platform have.
#define GPIO_MAX_PORT_NUM           1      // 0 ~ 3, the port number of the GPIO IP

/**
  \brief  Defines the GPIO port name
 */
enum {
    GPIO_PORT_A         = 0,
    GPIO_PORT_B         = 1,
    GPIO_PORT_C         = 2,
    GPIO_PORT_D         = 3
};

/**
  \brief  Defines GPIO interrupt polarity status
 */
enum {
    GPIO_LevelHigh      = 0,
    GPIO_LevelLow       = 1,
    GPIO_EdgeRising     = 0,
    GPIO_EdgeFalling    = 1,
    GPIO_EdgeDual       = 2
};

/**
  \brief  Defines GPIO interrupt trigger event type.
 */
enum  gpio_int_trigger_type_e {
    GPIO_IntType_None           = 0,
    GPIO_IntType_EdgeRising     = 1,
    GPIO_IntType_EdgeFalling    = 2,
    GPIO_IntType_LevelLow       = 3,
    GPIO_IntType_LevelHigh      = 4,
    GPIO_IntType_EdgeDual       = 5,

    GPIO_IntType_Invalid        = 0x0F
};
typedef uint8_t gpio_int_trig_type_t;

/**
  \brief  Defines GPIO pin direction.
 */
enum  gpio_dir_e {
    GPIO_IN                  = 0,
    GPIO_OUT                 = 1
};
typedef uint8_t gpio_dir_t;

/**
  \brief  Defines GPIO Interrupt clock source.
 */
enum  gpio_int_clk_e {
    GPIO_IntClk_APB      = 0,
    GPIO_IntClk_32K      = 1
};
typedef uint8_t gpio_int_clk_t;

/**
  \brief  Defines IO pad pull control type.
 */
enum pin_pull_ctrl_e {
    PullCtrl_HighZ = 0,
    PullCtrl_PullLow = 1,
    PullCtrl_PullHigh = 2
};

/**
  \brief  Defines IO pad pull type hardware supported.
 */
enum pin_pull_type_e {
    Pin_PullNone  = 0,
    Pin_PullUp    = 1,
    Pin_PullDown  = 2,
    Pin_PullDefault = Pin_PullNone
};
typedef uint8_t pin_pull_type_t;

/**
  \brief  Defines GPIO interrupt call back function type.
 */
typedef void (*gpio_irq_callback_t) (uint32_t int_id, gpio_int_trig_type_t int_type);

/**
  \brief  The data structure for a GPIO pin HAL operation.
*/
typedef struct hal_gpio_pin_adapter_s {
    uint8_t pin_name;               ///< chip pin name to locate the GPIO pin by port & pin index
    uint8_t port_idx;               ///< the GPIO IP port index of the GPIO pin
    uint8_t pin_idx;                ///< the GPIO IP pin index of the GPIO port
    uint8_t debounce_idx;           ///< the index of GPIO debounce function allocated to this GPIO pin, 0 ~ 15
    uint32_t bit_mask;              ///< the bit mask to read/write register

    volatile uint32_t *in_port;     ///< the IN port address
    volatile uint32_t *out0_port;   ///< the OUT port address for write 0
    volatile uint32_t *out1_port;   ///< the OUT port address for write 1
    volatile uint32_t *outt_port;   ///< the OUT port address for toggling
} hal_gpio_adapter_t, *phal_gpio_adapter_t;

/**
  \brief  The data structure for a GPIO IRQ pin HAL operation.
*/
typedef struct hal_gpio_irq_pin_adapter_s {
    uint8_t     pin_name;           ///< chip pin name to locate the GPIO pin by port & pin index
    uint8_t     ip_pin_name;        ///< IP pin name to locate the GPIO pin by port & pin index
    uint8_t     int_idx;            ///< the GPIO interrupt function index, 0 ~ 15
    uint8_t     debounce_idx;       ///< the GPIO debounce function index, 0 ~ 15
    uint8_t     int_type;           ///< the GPIO interrupt trigger type
    uint8_t     resv[3];
    uint32_t    bit_mask;           ///< the bit mask to read register
    volatile uint32_t    *in_port;  ///< the IN port address
    gpio_irq_callback_t irq_callback;   ///< the call-back function of the GPIO IRQ
    uint32_t irq_callback_arg;      ///< the argument of the IRQ call-back function, it's a priviate data will be
                                    ///< pass to the application with the call back function.
    void *pnext;                    ///< point to the next gpio_irq_pin_adapter
} hal_gpio_irq_adapter_t, *phal_gpio_irq_adapter_t;

/**
  \brief  The data structure for a GPIO port HAL operation.
*/
typedef struct hal_gpio_port_adapter_s {
    uint32_t port_idx;              ///< the port index
    uint32_t pin_mask;              ///< the mask of pin to indicate what pin is included
    uint32_t bit_mask;              ///< the bits mask to read/write register
    volatile uint32_t *in_port;     ///< the IN port address
    volatile uint32_t *out0_port;   ///< the OUT port address for write 0
    volatile uint32_t *out1_port;   ///< the OUT port address for write 1
    volatile uint32_t *outt_port;   ///< the OUT port address for toggling
    uint8_t  debounce_en;           ///< is enable debounce for all pins of this port
} hal_gpio_port_adapter_t, *phal_gpio_port_adapter_t;

/**
  \brief  The data structure for the GPIO Common resource menagement.
*/
typedef struct hal_gpio_comm_adapter_s {
    volatile phal_gpio_irq_adapter_t gpio_irq_list_head; ///< the head of the gpio_irq_pin_adapter list
    volatile phal_gpio_irq_adapter_t gpio_irq_list_tail; ///< the tail of the gpio_irq_pin_adapter list
    volatile uint32_t gpio_irq_using;        ///< the bit map to indicate using status of IRQ functions
    volatile uint32_t gpio_deb_using;        ///< the bit map to indicate using status of debounce functions
    volatile uint32_t critical_lv;           ///< to record GPIO HAL enter critical section level
    union {
        volatile uint32_t errs;
        struct {
            volatile uint32_t irq_err:1;     ///< IRQ handler error
            volatile uint32_t init_err:1;    ///< initial error
        } err_flag;
    };
} hal_gpio_comm_adapter_t, *phal_gpio_comm_adapter_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup ls_hal_gpio_rom_func GPIO HAL ROM APIs.
 * @{
 */


void hal_gpio_reg_irq_rtl8195blp (irq_handler_t irq_handler);
void hal_gpio_set_irq_priority_rtl8195blp (uint32_t priority);
void hal_gpio_comm_init_rtl8195blp (phal_gpio_comm_adapter_t pgpio_comm_adp);
void hal_gpio_comm_deinit_rtl8195blp (void);
void hal_gpio_enter_critical_rtl8195blp (void);
void hal_gpio_exit_critical_rtl8195blp (void);
hal_status_t hal_gpio_init_rtl8195blp (phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
void hal_gpio_deinit_rtl8195blp (phal_gpio_adapter_t pgpio_adapter);
void hal_gpio_set_dir_rtl8195blp (phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir);
gpio_dir_t hal_gpio_get_dir_rtl8195blp (phal_gpio_adapter_t pgpio_adapter);
void hal_gpio_write_rtl8195blp (phal_gpio_adapter_t pgpio_adapter, uint32_t io_data);
void hal_gpio_toggle_rtl8195blp (phal_gpio_adapter_t pgpio_adapter);
uint32_t hal_gpio_read_rtl8195blp (phal_gpio_adapter_t pgpio_adapter);
hal_status_t hal_gpio_debounce_enable_rtl8195blp (phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us);
uint32_t hal_gpio_read_debounce_rtl8195blp (phal_gpio_adapter_t pgpio_adapter);
void hal_gpio_debounce_disable_rtl8195blp (phal_gpio_adapter_t pgpio_adapter);
hal_status_t hal_gpio_irq_init_rtl8195blp (phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
                gpio_irq_callback_t callback, uint32_t arg);
void hal_gpio_irq_deinit_rtl8195blp (phal_gpio_irq_adapter_t pgpio_irq_adapter);
void hal_gpio_irq_set_trig_type_rtl8195blp (phal_gpio_irq_adapter_t pgpio_adapter, gpio_int_trig_type_t int_type);
gpio_int_trig_type_t hal_gpio_irq_get_trig_type_rtl8195blp (phal_gpio_irq_adapter_t pgpio_adapter);
void hal_gpio_irq_enable_rtl8195blp (phal_gpio_irq_adapter_t pgpio_irq_adapter);
void hal_gpio_irq_disable_rtl8195blp (phal_gpio_irq_adapter_t pgpio_irq_adapter);
hal_status_t hal_gpio_irq_debounce_enable_rtl8195blp (phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t debounce_us);
void hal_gpio_irq_debounce_disable_rtl8195blp (phal_gpio_irq_adapter_t pgpio_irq_adapter);
uint32_t hal_gpio_irq_read_rtl8195blp (phal_gpio_irq_adapter_t pgpio_irq_adapter);
hal_status_t hal_gpio_port_init_rtl8195blp (phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
                                    uint32_t mask, gpio_dir_t dir);
void hal_gpio_port_deinit_rtl8195blp (phal_gpio_port_adapter_t pgpio_port_adapter);
void hal_gpio_port_write_rtl8195blp (phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t io_data);
uint32_t hal_gpio_port_read_rtl8195blp (phal_gpio_port_adapter_t pgpio_port_adapter);
hal_status_t hal_gpio_pull_ctrl_rtl8195blp (uint32_t pin_name, pin_pull_type_t pull_type);
hal_status_t hal_gpio_schmitt_ctrl_rtl8195blp (uint32_t pin_name, BOOLEAN ctrl, uint8_t v_h3l1);
hal_status_t hal_gpio_drive_ctrl_rtl8195blp (uint32_t pin_name, uint8_t drv);

/** @} */ /* End of group ls_hal_gpio_rom_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/**
  \brief  The data structure of the stubs functions of the GPIO HAL functions in ROM.
*/
typedef struct hal_gpio_func_stubs_s {
    phal_gpio_comm_adapter_t *ppgpio_comm_adp;
    void (*hal_gpio_reg_irq) (irq_handler_t irq_handler);
    void (*hal_gpio_comm_init) (phal_gpio_comm_adapter_t pgpio_comm_adp);
    void (*hal_gpio_comm_deinit) (void);
    void (*hal_gpio_enter_critical) (void);
    void (*hal_gpio_exit_critical) (void);
    hal_status_t (*hal_gpio_init) (phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name);
    void (*hal_gpio_deinit) (phal_gpio_adapter_t pgpio_adapter);
    void (*hal_gpio_set_dir) (phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir);
    gpio_dir_t (*hal_gpio_get_dir) (phal_gpio_adapter_t pgpio_adapter);
    void (*hal_gpio_write) (phal_gpio_adapter_t pgpio_adapter, uint32_t io_data);
    void (*hal_gpio_toggle) (phal_gpio_adapter_t pgpio_adapter);
    uint32_t (*hal_gpio_read) (phal_gpio_adapter_t pgpio_adapter);
    hal_status_t (*hal_gpio_debounce_enable) (phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us);
    uint32_t (*hal_gpio_read_debounce) (phal_gpio_adapter_t pgpio_adapter);
    void (*hal_gpio_debounce_disable) (phal_gpio_adapter_t pgpio_adapter);
    hal_status_t (*hal_gpio_irq_init) (phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
                                        gpio_irq_callback_t callback, uint32_t arg);
    void (*hal_gpio_irq_deinit) (phal_gpio_irq_adapter_t pgpio_irq_adapter);
    void (*hal_gpio_irq_set_trig_type) (phal_gpio_irq_adapter_t pgpio_adapter, gpio_int_trig_type_t int_type);
    gpio_int_trig_type_t (*hal_gpio_irq_get_trig_type) (phal_gpio_irq_adapter_t pgpio_adapter);
    void (*hal_gpio_irq_enable) (phal_gpio_irq_adapter_t pgpio_irq_adapter);
    void (*hal_gpio_irq_disable) (phal_gpio_irq_adapter_t pgpio_irq_adapter);
    hal_status_t (*hal_gpio_irq_debounce_enable) (phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t debounce_us);
    void (*hal_gpio_irq_debounce_disable) (phal_gpio_irq_adapter_t pgpio_irq_adapter);
    uint32_t (*hal_gpio_irq_read) (phal_gpio_irq_adapter_t pgpio_irq_adapter);
    hal_status_t (*hal_gpio_port_init) (phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
                                        uint32_t mask, gpio_dir_t dir);
    void (*hal_gpio_port_deinit) (phal_gpio_port_adapter_t pgpio_port_adapter);
    void (*hal_gpio_port_write) (phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t io_data);
    uint32_t (*hal_gpio_port_read) (phal_gpio_port_adapter_t pgpio_port_adapter);
    hal_status_t (*hal_gpio_pull_ctrl) (uint32_t pin_name, pin_pull_type_t pull_type);
    hal_status_t (*hal_gpio_schmitt_ctrl) (uint32_t pin_name, BOOLEAN ctrl, uint8_t v_h3l1);
    hal_status_t (*hal_gpio_drive_ctrl) (uint32_t pin_name, uint8_t drv);
    uint32_t reserved[11];  // reserved space for next ROM code version function table extending.
} hal_gpio_func_stubs_t;

#ifdef __cplusplus
}
#endif

#endif /* RTL8195BLP_GPIO_H */


/** @} */ /* End of group ls_hal_gpio */


