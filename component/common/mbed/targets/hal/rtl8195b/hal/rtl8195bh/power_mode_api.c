 /**************************************************************************//**
  * @file     power_mode_api.c
  * @brief    This file implements the mbed HAL API for POWER MODE function.
  *
  * @version  V1.00
  * @date     2018-06-25
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

#include "objects.h"
#include "hal_power_mode.h"
#include "power_mode_api.h"
#include "pinmap.h"
#include "gpio_irq_api.h"
#include "gpio_irq_ex_api.h"
#include "hal_power_mode_nsc.h"

gpio_irq_t gpio_irq;

/**
  * @brief The stubs functions table to exports POWER MODE HAL functions in ROM.
  */

/** 
 *  @brief The function for hs clock gated.
 *         
 *  @param[in]  Option, To slect HS Timer, GPIO and PWM..etc
 *                - bit[4]: the UART Wake up event.
 *                - bit[3]: the PWM Wake up event.
 *                - bit[2]: the GPIO Wake up event.
 *                - bit[1]: the GTimer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value. Uint: us
 *  @param[in]  Clock, 1: 100kHz, 0: 128kHz.
 *  @param[in]  GpioOption, Select GPIO pin as a wake up trigger.
 *
 *  @returns void
 */
void SleepCG (u16 Option, u32 SDuration, u8 Clock, u8 GpioOption)
{
    if(Option & SLP_GPIO) {
        gpio_irq_init(&gpio_irq, GpioOption, NULL, (uint32_t)&gpio_irq);
        gpio_irq_pull_ctrl(&gpio_irq, PullNone);
        gpio_irq_set(&gpio_irq, IRQ_FALL, 1);
    }
    hal_SleepCG (Option, SDuration, Clock, GpioOption);
}

/** 
 *  @brief The function for hs power gated.
 *         
 *  @param[in]  Option, To slect HS Timer and GPIO
 *                - bit[2]: the GPIO Wake up event.
 *                - bit[1]: the GTimer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value. Uint: us
 *  @param[in]  Memsel, 1: Enable memory, 0: Disable memory.
 *  @param[in]  GpioOption, Select GPIO pin as a wake up trigger.
 *
 *  @returns void
 */
void SleepPG (u16 Option, u32 SDuration, u8 Memsel, u8 GpioOption)
{
    if(Option & SLP_GPIO) {
        gpio_irq_init(&gpio_irq, GpioOption, NULL, (uint32_t)&gpio_irq);
        gpio_irq_pull_ctrl(&gpio_irq, PullNone);
        gpio_irq_set(&gpio_irq, IRQ_FALL, 1);
    }
    hal_SleepPG (Option, SDuration, Memsel, GpioOption);
}
