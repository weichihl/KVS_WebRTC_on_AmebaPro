/**************************************************************************//**
 * @file     hal_gpio.c
 * @brief    This GPIO HAL API functions.
 *
 * @version  V1.00
 * @date     2017-04-26
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
 * @addtogroup hs_hal_gpio GPIO
 * @{
 */


#include "hal_gpio.h"
#include "hal_pinmux.h"

#if CONFIG_GPIO_EN

#if defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE == 1)

/**
  * @brief The table of IO pad pull control registers.
  */
const __IOM uint32_t *pin_pull_ctrl_reg[] = {
    GPIO_PORTB_PULL_CTRL,
    GPIO_PORTC_PULL_CTRL,
    GPIO_PORTD_PULL_CTRL,
    GPIO_PORTE_PULL_CTRL,
    GPIO_PORTF_PULL_CTRL,
    GPIO_PORTG_PULL_CTRL,
    GPIO_PORTH_PULL_CTRL
};

/**
  * @brief The table of schmitt trigger function control registers.
  */
const __IOM uint32_t *pin_schmitt_ctrl_reg[] = {
    GPIO_PORTB_SCHMITT_CTRL,
    GPIO_PORTC_SCHMITT_CTRL,
    GPIO_PORTD_SCHMITT_CTRL,
    GPIO_PORTE_SCHMITT_CTRL,
    GPIO_PORTF_SCHMITT_CTRL,
    GPIO_PORTG_SCHMITT_CTRL,
    GPIO_PORTH_SCHMITT_CTRL
};

/**
 *  @brief Configures the pull type of the given GPIO pin.
 *
 *  @param[in]  pin_name  The GPIO pin.
 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
 *                - bit[4:0]: the pin number of the GPIO port.
 *  @param[in]  pull_type  The pull type:
 *                - 0: No pull.
 *                - 1: Pull high.
 *                - 2: Pull low.
 *                - other value: No pull.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  Configures IO pad pull type OK.
 */
hal_status_t hal_gpio_pull_ctrl (uint32_t pin_name, pin_pull_type_t pull_type)
{
    uint8_t port_idx = PIN_NAME_2_PORT (pin_name);
    uint8_t pin_idx = PIN_NAME_2_PIN (pin_name);
    uint32_t bit_mask;
    uint32_t pull_ctrl;

    volatile uint32_t pull_ctrl_reg;

    if ((port_idx >= PORT_MAX_NUM) || (pin_idx >= MAX_PIN_IN_PORT)) {
        DBG_GPIO_ERR ("hal_gpio_pull_ctrl: Invalid pin, port=%u pin=%u\r\n", port_idx, pin_idx);
        return HAL_ERR_PARA;
    }

    switch (pull_type) {
        case Pin_PullUp:
            pull_ctrl = PullCtrl_PullHigh;
            break;

        case Pin_PullDown:
            pull_ctrl = PullCtrl_PullLow;
            break;

        case Pin_PullNone:
            pull_ctrl = PullCtrl_HighZ;
            break;

        default:
            DBG_GPIO_ERR ("hal_gpio_pull_ctrl: Unknown pull type(%d), set as Pull-None\r\n", pull_type);
            pull_ctrl = PullCtrl_HighZ;
            break;
    }

    pull_ctrl = pull_ctrl << (pin_idx << 1);
    bit_mask = 0x03 << (pin_idx << 1);
    pull_ctrl_reg = *((uint32_t *)(pin_pull_ctrl_reg[port_idx])) & (~bit_mask);
    *((uint32_t *)(pin_pull_ctrl_reg[port_idx])) = pull_ctrl_reg | pull_ctrl;
    return HAL_OK;
}

/**
 *  @brief The schmitt trigger on/off control on the given GPIO pin .
 *
 *  @param[in]  pin_name  The GPIO pin.
 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
 *                - bit[4:0]: the pin number of the GPIO port.
 *  @param[in]  ctrl  The on/off control:
 *                      - 0: disable the schmitt trigger.
 *                      - 1: enable the schmitt trigger.
 *  @param[in]  v_h3l1  The GPIO Group Voltage Select:
 *                      - 0: 1.8V.
 *                      - 1: 3V.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  Schmitt trigger enable control setup OK.
 */
hal_status_t hal_gpio_schmitt_ctrl (uint32_t pin_name, BOOLEAN ctrl, uint8_t v_h3l1)
{
    uint8_t port_idx = PIN_NAME_2_PORT (pin_name);
    uint8_t pin_idx = PIN_NAME_2_PIN (pin_name);
    u32 buff;

    if ((port_idx >= PORT_MAX_NUM) || (pin_idx >= MAX_PIN_IN_PORT)) {
        DBG_GPIO_ERR ("hal_gpio_schmitt_ctrl: Invalid pin, port=%u pin=%u\r\n", port_idx, pin_idx);
        return HAL_ERR_PARA;
    }

    if (ctrl) {
        // GPIO Group Voltage Select
        buff = HAL_READ32(0x40000000, 0x28C);
        if (v_h3l1) {
            //SYSON->pad_h3l1 = SYSON->pad_h3l1 |(1 << port_idx);
            buff = buff |(1 << port_idx); // 3V
        } else {
            //SYSON->pad_h3l1 = SYSON->pad_h3l1 &~(1 << port_idx);
            buff = buff &~(1 << port_idx); // 1.8V
        }
        HAL_WRITE32(0x40000000, 0x28C, buff); // Set GPIO PAD H3L1
        // Schmitt trigger ON
        *((uint32_t *)(pin_schmitt_ctrl_reg[port_idx])) |= 1 << pin_idx;
    } else {
        // Schmitt trigger Off
        *((uint32_t *)(pin_schmitt_ctrl_reg[port_idx])) &= ~(1 << pin_idx);
    }
    return HAL_OK;
}


#else   // else of "#if defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE == 1)"

/**
  * @brief The table of all GPIO port data mode input enable registers address.
  */
const uint32_t *pport_in_en_reg[GPIO_MAX_PORT_NUM] = {
    (uint32_t *)&(GPIO->port_a_idm_en),
    (uint32_t *)&(GPIO->port_b_idm_en),
    (uint32_t *)&(GPIO->port_c_idm_en),
    (uint32_t *)&(GPIO->port_d_idm_en)
};

/**
  * @brief The table of all GPIO port data mode output enable registers address.
  */
const uint32_t *pport_out_en_reg[GPIO_MAX_PORT_NUM] = {
    (uint32_t *)&(GPIO->port_a_odm_en),
    (uint32_t *)&(GPIO->port_b_odm_en),
    (uint32_t *)&(GPIO->port_c_odm_en),
    (uint32_t *)&(GPIO->port_d_odm_en)
};

/**
 *  @brief Initials a GPIO pin.
 *           - Defult configure the GPIO pin as a normal input pin (not an interrupt pin).
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  pin_name  The GPIO pin.
 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
 *                - bit[4:0]: the pin number of the GPIO port.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GPIO pin initialization OK.
 */
hal_status_t hal_gpio_init (phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name)
{
    io_pin_t pin_list[2];
    hal_status_t ret;

    pin_list[0].pin_name = pin_name;
    pin_list[1].pin_name = 0xFF;
    ret = hal_pinmux_register((io_pin_t *)&pin_list[0], PID_GPIO);
    if (ret != HAL_OK) {
        return ret;
    }
    return hal_gpio_stubs.hal_gpio_init (pgpio_adapter, pin_name);
}

/**
 *  @brief To de-initial a GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns    void
 */
void hal_gpio_deinit (phal_gpio_adapter_t pgpio_adapter)
{
    io_pin_t pin_list[2];

    pin_list[0].pin_name = pgpio_adapter->pin_name;
    pin_list[1].pin_name = 0xFF;
    hal_pinmux_unregister((io_pin_t *)&pin_list[0], PID_GPIO);
    hal_gpio_stubs.hal_gpio_deinit (pgpio_adapter);
}

/**
 *  @brief Initials a GPIO IRQ pin.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *  @param[in]  pin_name  The GPIO IRQ pin.
 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
 *                - bit[4:0]: the pin number of the GPIO port.
 *  @param[in]  callback  The GPIO IRQ call back function.
 *  @param[in]  arg  The argument of the GPIO IRQ call back function. It is an application
 *                   priviate data to be passed by the call back function.
 *
 *  @return     HAL_NOT_READY:  The GPIO group adapter does not been initialed yet.
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_NO_RESOURCE: No GPIO IRQ resource (circuit). The GPIO IRQ resource is limited,
 *                               not all GPIO pin can has GPIO IRQ function.
 *  @return     HAL_OK: GPIO IRQ pin initialization OK.
 */
hal_status_t hal_gpio_irq_init (phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
                                gpio_irq_callback_t callback, uint32_t arg)
{
    io_pin_t pin_list[2];
    hal_status_t ret;

    pin_list[0].pin_name = pin_name;
    pin_list[1].pin_name = 0xFF;
    ret = hal_pinmux_register((io_pin_t *)&pin_list[0], PID_GPIO);
    if (ret != HAL_OK) {
        return ret;
    }

    return hal_gpio_stubs.hal_gpio_irq_init (pgpio_irq_adapter, pin_name, callback, arg);
}

/**
 *  @brief To de-initial and disable a GPIO IRQ pin.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *
 *  @returns    void
 */
void hal_gpio_irq_deinit (phal_gpio_irq_adapter_t pgpio_irq_adapter)
{
    io_pin_t pin_list[2];

    pin_list[0].pin_name = pgpio_irq_adapter->pin_name;
    pin_list[1].pin_name = 0xFF;
    hal_pinmux_unregister((io_pin_t *)&pin_list[0], PID_GPIO);
    hal_gpio_stubs.hal_gpio_irq_deinit (pgpio_irq_adapter);
}

/**
 *  @brief Initials a GPIO port. A GPIO port has 32 GPIO pins. However, may not all
 *         GPIO pin will be bound out. Checks the IC package to know what pins are
 *         available on this GPIO port.
 *
 *  @param[in]  pgpio_port_adapter  The GPIO port adapter.
 *  @param[in]  port_idx The GPIO port index.
 *                - 0: Port B
 *                - 1: Port C
 *                - 2: Port D
 *                - 3: Port E
 *                - 4: Port F
 *                - 5: Port G
 *                - 6: Port H
 *  @param[in]  mask  The GPIO pin mask to indicate what pin are included in this port.
 *                    Bit 0 maps to pin 0; bit 1 maps to pin 1; ... etc. The bit value 1
 *                    means the maped pin is included in this GPIO port.
 *  @param[in]  dir  The GPIO port direction, IN or OUT.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GPIO port initialization OK.
 */
hal_status_t hal_gpio_port_init (phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
                                 uint32_t mask, gpio_dir_t dir)
{
    io_pin_t pin_list[MAX_PIN_IN_PORT+1];
    hal_status_t ret;
    gpio_pin_t pin;
    uint32_t i;
    uint32_t j;

    j = 0;
    pin.pin_name_b.port = port_idx;
    for (i=0; i<MAX_PIN_IN_PORT; i++) {
        if (mask & (1 << i)) {
            pin.pin_name_b.pin = i;
            pin_list[j].pin_name = pin.pin_name;
            j++;
        }
    }
    pin_list[j].pin_name = 0xFF;
    ret = hal_pinmux_register((io_pin_t *)&pin_list[0], PID_GPIO);
    if (ret != HAL_OK) {
        return ret;
    }

    return hal_gpio_stubs.hal_gpio_port_init (pgpio_port_adapter, port_idx, mask, dir);
}

/**
 *  @brief To de-initial a GPIO port. All pins in this GPIO port will be switched
 *         as input pin.
 *
 *  @param[in]  pgpio_port_adapter The GPIO port adapter.
 *
 *  @returns    void
 */
void hal_gpio_port_deinit (phal_gpio_port_adapter_t pgpio_port_adapter)
{
    io_pin_t pin_list[MAX_PIN_IN_PORT+1];
    gpio_pin_t pin;
    uint32_t i;
    uint32_t j;
    uint32_t mask;
    j = 0;
    pin.pin_name= hal_gpio_ip_pin_to_chip_pin (pgpio_port_adapter->port_idx, pgpio_port_adapter->pin_offset);
    mask = pgpio_port_adapter->pin_mask;
    for (i=0; i<MAX_PIN_IN_PORT; i++) {
        if (mask & (1 << i)) {
            pin.pin_name_b.pin = i;
            pin_list[j].pin_name = pin.pin_name;
            j++;
        }
    }
    pin_list[j].pin_name = 0xFF;
    hal_pinmux_unregister((io_pin_t *)&pin_list[0], PID_GPIO);
    
    //DBG_GPIO_ERR ("mux:%x\r\n",ppinmux_manager->pinmux_reg_log[3]);
    hal_gpio_stubs.hal_gpio_port_deinit (pgpio_port_adapter);
}

/**
 *  @brief To set the direction of the given GPIO port.
 *
 *  @param[in]  pgpio_port_adapter The GPIO port adapter.
 *  @param[in]  dir  The GPIO port direction, IN or OUT.
 *                     -0: input.
 *                     -1: output.
 *
 *  @returns    void
 */
void hal_gpio_port_dir (phal_gpio_port_adapter_t pgpio_port_adapter, gpio_dir_t dir)
{
    uint32_t *port_dir_en;
    uint32_t port_idx;

    if(pgpio_port_adapter == NULL) {
        DBG_GPIO_ERR ("hal_gpio_port_dir: The pgpio_port adapter is not initialize\r\n");
    } else {
        port_idx = pgpio_port_adapter->port_idx;
        // set direction
        if (dir == GPIO_IN) {
            port_dir_en = (uint32_t *)pport_in_en_reg[port_idx];
        
        } else {
            port_dir_en = (uint32_t *)pport_out_en_reg[port_idx];
        }
        
        *port_dir_en = pgpio_port_adapter->pin_mask << pgpio_port_adapter->pin_offset;
    }
}

/**
 *  @brief Coverts an IP pin to a chip pin name.
 *
 *  @param[in]  port_idx The port index of the IP pin.
 *  @param[in]  pin_idx The pin index of the IP pin.
 *
 *  @returns    The converted chip pin name.
 */
uint8_t hal_gpio_ip_pin_to_chip_pin (uint32_t port_idx, uint32_t pin_idx)
{
    uint8_t chip_port;
    uint8_t chip_pin;

    // convert chip pin definition to IP pin definition
    // port B maps to IP Port 0[15: 0]
    // port C maps to IP Port 0[31:16]
    // port D maps to IP Port 1[15: 0]
    // port E maps to IP Port 1[31:16]
    // port F maps to IP Port 2[15: 0]
    // port G maps to IP Port 2[31:16]
    // port H maps to IP Port 3[15: 0]
    // port I maps to IP Port 3[31:16]

    chip_port = port_idx << 1;
    if (pin_idx >= 16) {
        chip_port++;
        chip_pin = pin_idx - 16;
    } else {
        chip_pin = pin_idx;
    }

    return PIN_NAME(chip_port, chip_pin);
}

#endif  // end of else of "#if defined(CONFIG_BUILD_SECURE) && (CONFIG_BUILD_SECURE == 1)"

#endif  // end of "#if CONFIG_GPIO_EN"

/** @} */ /* End of group hs_hal_gpio */

