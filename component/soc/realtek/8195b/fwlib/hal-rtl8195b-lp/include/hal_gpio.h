/**************************************************************************//**
 * @file     hal_gpio.h
 * @brief    The HAL API implementation for the GPIO.
 * @version  V1.00
 * @date     2016-12-22
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

#ifndef _HAL_GPIO_H_
#define _HAL_GPIO_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

#if (CHIP_VER == CHIP_A_CUT) && (defined(CONFIG_BUILD_RAM))
hal_status_t hal_gpio_schmitt_ctrl_rtl8195blp_patch (uint32_t pin_name, BOOLEAN ctrl, uint8_t v_h3l1);
#elif (CHIP_VER == CHIP_B_CUT) && (defined(CONFIG_BUILD_RAM))
hal_status_t hal_gpio_drive_ctrl_rtl8195blp_patch (uint32_t pin_name, uint8_t drv);
#endif

/**
 * @addtogroup ls_hal_gpio GPIO
 * @ingroup 8195bl_hal
 * @{
 * @brief The GPIO HAL module of the LS platform.
 */

extern const hal_gpio_func_stubs_t hal_gpio_stubs;

/**
 *  @brief To register an interrupt handler for all GPIO interrupt pins and enable
 *         the GPIO interrupt.
 *
 *  @param[in]  irq_handler  The GPIO interrupt handler.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_reg_irq (irq_handler_t irq_handler)
{
    hal_gpio_stubs.hal_gpio_reg_irq (irq_handler);
}

/**
 *  @brief To set the GPIO interrupt IRQ priority.
 *
 *  @param[in]  priority  The IRQ priority.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_set_irq_priority (uint32_t priority)
{
    NVIC_SetPriority(GPIO_IRQn, priority);
}

/**
 *  @brief Initials the GPIO group common resource.
 *           - Enable the GPIO hardware function.
 *           - Register the interrupt handler.
 *           - Initial the GPIO group adapter.
 *
 *  @param[in] pgpio_comm_adp  The GPIO group adapter. For all GPIO pins common
 *             resource handling.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_comm_init (phal_gpio_comm_adapter_t pgpio_comm_adp)
{
    hal_gpio_stubs.hal_gpio_comm_init (pgpio_comm_adp);
}

/**
 *  @brief To de-initial the GPIO common resource.
 *           - Disable the GPIO hardware function.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_comm_deinit (void)
{
    hal_gpio_stubs.hal_gpio_comm_deinit ();
}

/**
 *  @brief To enter a critical section of code, mainly it
 *         disable the GPIO interrupt to prevent any race condition.
 *
 *  @returns void
 */
__STATIC_INLINE void hal_gpio_enter_critical (void)
{
    hal_gpio_stubs.hal_gpio_enter_critical ();
}

/**
 *  @brief To exit a critical code section, it will re-enable the GPIO interrupt
 *         only when the exiting critical section is the top level.
 *
 *  @returns void
 */
__STATIC_INLINE void hal_gpio_exit_critical (void)
{
    hal_gpio_stubs.hal_gpio_exit_critical ();
}

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
__STATIC_INLINE hal_status_t hal_gpio_init (phal_gpio_adapter_t pgpio_adapter, uint32_t pin_name)
{
    return hal_gpio_stubs.hal_gpio_init (pgpio_adapter, pin_name);
}

/**
 *  @brief To de-initial a GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_deinit (phal_gpio_adapter_t pgpio_adapter)
{
    hal_gpio_stubs.hal_gpio_deinit (pgpio_adapter);
}

/**
 *  @brief To set the direction of the specified GPIO pin.
 *
 *  @param pgpio_adapter The GPIO pin adapter.
 *  @param dir The direction (IN or OUT)
 *
 *  @returns void
 */
__STATIC_INLINE void hal_gpio_set_dir (phal_gpio_adapter_t pgpio_adapter, gpio_dir_t dir)
{
    hal_gpio_stubs.hal_gpio_set_dir (pgpio_adapter, dir);
}

/**
 *  @brief Gets current direction of the specified GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns    The GPIO pin direction.
 *                - 0: input.
 *                - 1: output.
 */
__STATIC_INLINE gpio_dir_t hal_gpio_get_dir (phal_gpio_adapter_t pgpio_adapter)
{
    return hal_gpio_stubs.hal_gpio_get_dir (pgpio_adapter);
}

/**
 *  @brief Sets the output level of the specified GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  io_data  The value to be set to the GPIO pin, 0 or 1.
 *                - 0: the GPIO pin output low level.
 *                - 1: the GPIO pin output high level.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_write (phal_gpio_adapter_t pgpio_adapter, uint32_t io_data)
{
    if (io_data) {
        *(pgpio_adapter->out1_port) = pgpio_adapter->bit_mask;
    } else {
        *(pgpio_adapter->out0_port) = pgpio_adapter->bit_mask;
    }
}

/**
 *  @brief To toggle (0 -> 1 or 1 -> 0) the output level of the specified GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_toggle (phal_gpio_adapter_t pgpio_adapter)
{
    *(pgpio_adapter->outt_port) = pgpio_adapter->bit_mask;
}

/**
 *  @brief To read the input level of the specified GPIO pin.
 *
 *  @param pgpio_adapter The GPIO pin adapter.
 *
 *  @returns The GPIO IN level (0 or 1).
 */
__STATIC_INLINE uint32_t hal_gpio_read (phal_gpio_adapter_t pgpio_adapter)
{
    if (pgpio_adapter->debounce_idx >= GPIO_MAX_DEBOUNCE_PIN) {
        // not using debounce
        return (*((volatile uint32_t *)(pgpio_adapter->in_port)) & pgpio_adapter->bit_mask ? 1 : 0);
    } else {
        return (GPIO->deb_dp_sts & (1 << pgpio_adapter->debounce_idx) ? 1 : 0);
    }
}

/**
 *  @brief Enable the debounce function for the given GPIO pin.
 *         The debounce resource(circuit) is limited, not all GPIO pin
 *         can has debounce function.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  debounce_us  The time filter for the debounce, in micro-second.
 *                           But the time resolution is 31.25us (1/32K) and the
 *                           maximum time is 512 ms.
 *
 *  @return     HAL_NO_RESOURCE:  No debounce resource. (All debounce circuit are allocated).
 *  @return     HAL_ERR_PARA:  Input arguments are invlaid.
 *  @return     HAL_OK:  Debounce function is enabled on this GPIO.
 */
__STATIC_INLINE hal_status_t hal_gpio_debounce_enable (phal_gpio_adapter_t pgpio_adapter, uint32_t debounce_us)
{
    return hal_gpio_stubs.hal_gpio_debounce_enable (pgpio_adapter, debounce_us);
}

/**
 *  @brief Reads the given GPIO pin input level with de-bounced.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns The GPIO pin input level after debouncing.
 *             - 0: the GPIO pin input level is low.
 *             - 1: the GPIO pin input level is high.
 */
__STATIC_INLINE uint32_t hal_gpio_read_debounce (phal_gpio_adapter_t pgpio_adapter)
{
    return (GPIO->deb_dp_sts & (1 << pgpio_adapter->debounce_idx) ? 1 : 0);
}

/**
 *  @brief Disables the debounce function of the given GPIO pin.
 *         The released debounce circuit can be assign to other GPIO pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_debounce_disable (phal_gpio_adapter_t pgpio_adapter)
{
    hal_gpio_stubs.hal_gpio_debounce_disable (pgpio_adapter);
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
__STATIC_INLINE hal_status_t hal_gpio_irq_init (phal_gpio_irq_adapter_t pgpio_irq_adapter, uint32_t pin_name,
                                                gpio_irq_callback_t callback, uint32_t arg)
{
    return hal_gpio_stubs.hal_gpio_irq_init (pgpio_irq_adapter, pin_name, callback, arg);
}

/**
 *  @brief To de-initial and disable a GPIO IRQ pin.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_irq_deinit (phal_gpio_irq_adapter_t pgpio_irq_adapter)
{
    hal_gpio_stubs.hal_gpio_irq_deinit (pgpio_irq_adapter);
}

/**
 *  @brief Configures the interrupt trigger type of a given GPIO IRQ pin.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *  @param[in]  int_type  The interrupt trigger type.
 *                     - 1: Rising edge trigger.
 *                     - 2: Falling edge trigger.
 *                     - 3: Low level trigger.
 *                     - 4: High level trigger.
 *                     - 5: Dual(rising and falling) edge trigger.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_irq_set_trig_type (phal_gpio_irq_adapter_t pgpio_adapter, gpio_int_trig_type_t int_type)
{
    hal_gpio_stubs.hal_gpio_irq_set_trig_type (pgpio_adapter, int_type);
}

/**
 *  @brief Gets current GPIO interrupt trigger type configuration.
 *
 *  @param[in]  pgpio_adapter  The GPIO pin adapter.
 *
 *  @returns    The interrupt trigger type.
 *                - 1: Rising edge trigger.
 *                - 2: Falling edge trigger.
 *                - 3: Low level trigger.
 *                - 4: High level trigger.
 *                - 5: Dual(rising and falling) edge trigger.
 */
__STATIC_INLINE gpio_int_trig_type_t hal_gpio_irq_get_trig_type (phal_gpio_irq_adapter_t pgpio_adapter)
{
    return hal_gpio_stubs.hal_gpio_irq_get_trig_type (pgpio_adapter);
}

/**
 *  @brief Enables the interrupt of the given GPIO IRQ pin.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *
 *  @returns void
 */
__STATIC_INLINE void hal_gpio_irq_enable (phal_gpio_irq_adapter_t pgpio_irq_adapter)
{
    hal_gpio_stubs.hal_gpio_irq_enable (pgpio_irq_adapter);
}

/**
 *  @brief Disables the interrupt of the given GPIO IRQ pin.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_irq_disable (phal_gpio_irq_adapter_t pgpio_irq_adapter)
{
    hal_gpio_stubs.hal_gpio_irq_disable (pgpio_irq_adapter);
}

/**
 *  @brief Enables the debounce function of the given GPIO IRQ pin.
 *         The debounce resource(circuit) is limited, not all GPIO pin
 *         can has debounce function.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *  @param[in]  debounce_us  The time filter for the debounce, in micro-second.
 *                           But the time resolution is 31.25us (1/32K) and the
 *                           maximum time is 512 ms.
 *
 *  @return     HAL_NO_RESOURCE:  No debounce resource. (All debounce circuit are allocated).
 *  @return     HAL_OK:  Debounce function is enabled on this GPIO.
 */
__STATIC_INLINE hal_status_t hal_gpio_irq_debounce_enable (phal_gpio_irq_adapter_t pgpio_irq_adapter,
                                                                    uint32_t debounce_us)
{
    return hal_gpio_stubs.hal_gpio_irq_debounce_enable (pgpio_irq_adapter, debounce_us);
}

/**
 *  @brief To disable the debounce function of the given GPIO IRQ pin.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_irq_debounce_disable (phal_gpio_irq_adapter_t pgpio_irq_adapter)
{
    hal_gpio_stubs.hal_gpio_irq_debounce_disable (pgpio_irq_adapter);
}

/**
 *  @brief Reads the input level of the given GPIO IRQ pin.
 *         If a debounce function is enabled on this GPIO IRQ pin,
 *         then reads the de-bounced input level.
 *
 *  @param[in]  pgpio_irq_adapter  The GPIO IRQ pin adapter.
 *
 *  @returns    The input level(0 or 1) of the GPIO IRQ pin.
 *                - 0: the GPIO IRQ pin input level is low.
 *                - 1: the GPIO IRQ pin input level is high.
 */
__STATIC_INLINE uint32_t hal_gpio_irq_read (phal_gpio_irq_adapter_t pgpio_irq_adapter)
{
    if (pgpio_irq_adapter->debounce_idx >= GPIO_MAX_DEBOUNCE_PIN) {
        // not using debounce
        return (*((volatile uint32_t *)(pgpio_irq_adapter->in_port)) & pgpio_irq_adapter->bit_mask ? 1 : 0);
    } else {
        return (GPIO->deb_dp_sts & (1 << pgpio_irq_adapter->debounce_idx) ? 1 : 0);
    }
}

/**
 *  @brief Initials a GPIO port. A GPIO port has 32 GPIO pins. However, may not all
 *         GPIO pin will be bound out. Checks the IC package to know what pins are
 *         available on this GPIO port.
 *
 *  @param[in]  pgpio_port_adapter  The GPIO port adapter.
 *  @param[in]  port_idx The GPIO port index.
 *  @param[in]  mask  The GPIO pin mask to indicate what pin are included in this port.
 *                    Bit 0 maps to pin 0; bit 1 maps to pin 1; ... etc. The bit value 1
 *                    means the maped pin is included in this GPIO port.
 *  @param[in]  dir  The GPIO port direction, IN or OUT.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GPIO port initialization OK.
 */
__STATIC_INLINE hal_status_t hal_gpio_port_init (phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t port_idx,
                                                 uint32_t mask, gpio_dir_t dir)
{
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
__STATIC_INLINE void hal_gpio_port_deinit (phal_gpio_port_adapter_t pgpio_port_adapter)
{
    hal_gpio_stubs.hal_gpio_port_deinit (pgpio_port_adapter);
}

/**
 *  @brief Writes a value to the given GPIO output port.
 *
 *  @param[in]  pgpio_port_adapter  The GPIO port adapter.
 *  @param[in]  io_data  The value to be write to the GPIO port.
 *
 *  @returns    void
 */
__STATIC_INLINE void hal_gpio_port_write (phal_gpio_port_adapter_t pgpio_port_adapter, uint32_t io_data)
{
    // write bits of out 1
    *(pgpio_port_adapter->out1_port) = io_data & pgpio_port_adapter->pin_mask;

    // write bits of out 0
    *(pgpio_port_adapter->out0_port) = (~io_data) & pgpio_port_adapter->pin_mask;
}

/**
 *  @brief Read the GPIO port.
 *
 *  @param[in]  pgpio_port_adapter  The GPIO port adapter.
 *
 *  @returns    The level status of the GPIO port.
 */
__STATIC_INLINE uint32_t hal_gpio_port_read (phal_gpio_port_adapter_t pgpio_port_adapter)
{
    return (*((volatile uint32_t *)(pgpio_port_adapter->in_port)) & pgpio_port_adapter->pin_mask);
}

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
 *  @returns    Always return HAL_OK.
 */
__STATIC_INLINE hal_status_t hal_gpio_pull_ctrl (uint32_t pin_name, pin_pull_type_t pull_type)
{
    return hal_gpio_stubs.hal_gpio_pull_ctrl (pin_name, pull_type);
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
 *  @returns    Always return HAL_OK.
 */
__STATIC_INLINE hal_status_t hal_gpio_schmitt_ctrl (uint32_t pin_name, BOOLEAN ctrl, uint8_t v_h3l1)
{
    #if (CHIP_VER == CHIP_A_CUT) && (defined(CONFIG_BUILD_RAM))
        return hal_gpio_schmitt_ctrl_rtl8195blp_patch (pin_name, ctrl, v_h3l1);
    #else
        return hal_gpio_stubs.hal_gpio_schmitt_ctrl (pin_name, ctrl, v_h3l1);
    #endif
}

/** 
 *  @brief Controls the IO pad drive power current on the given GPIO pin .
 *
 *  @param[in]  pin_name  The GPIO pin.
 *                - bit[7:5]: the GPIO port number. Each port has 32 GPIO pins.
 *                - bit[4:0]: the pin number of the GPIO port.
 *  @param[in]  drv  The I/O pad driving power selection:
 *                  Only for Group B Driving Select:
 *                      - 1.8V: 0: 1mA; 1: 2mA; 3: 4mA; 5: 6mA; 7: 8mA; 13: 10mA; 15: 12mA
 *                      - 3.3V: 0: 3mA; 1: 6mA; 3: 12mA; 5: 18mA
 *                  Others:
 *                   - 0: 8mA
 *                   - 1: 16mA
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  IO pad driving current setup OK.
 */
__STATIC_INLINE hal_status_t hal_gpio_drive_ctrl (uint32_t pin_name, uint8_t drv)
{
        
    #if (CHIP_VER == CHIP_B_CUT) && (defined(CONFIG_BUILD_RAM))
        return hal_gpio_drive_ctrl_rtl8195blp_patch (pin_name, drv);
    #else
        return hal_gpio_stubs.hal_gpio_drive_ctrl (pin_name, drv);
    #endif
}

/** @} */ /* End of group ls_hal_gpio */

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _HAL_GPIO_H_"

