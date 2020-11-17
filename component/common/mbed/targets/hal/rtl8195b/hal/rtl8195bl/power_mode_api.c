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

gpio_irq_t gpio_irq;

/**
  * @brief The stubs functions table to exports POWER MODE HAL functions in ROM.
  */

//extern const hal_power_mode_func_stubs_t hal_power_mode_stubs;

/** 
 *  @brief The function for ls deep sleep mode.
 *         
 *  @param[in]  Option, To slect AON Timer,GPIO,ADP and RTC.
 *                - bit[3]: the ADP Wake up event.
 *                - bit[2]: the GPIO A13 Rising Wake up event.
 *                - bit[1]: the GPIO A13 Falling Wake up event.
 *                - bit[0]: the AON Timer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value(Max:8300 sec). Uint: us
 *  @param[in]  Memsel, 1: Enable memory, 0: Disable memory.
 *  @param[in]  Clock, 1: 100kHz, 0: 128kHz.
 *
 *  @returns void
 */
void DeepSleep (u8  Option, u64 SDuration, u8 Memsel, u8 Clock)
{
    hal_DeepSleep (Option, SDuration, Memsel, Clock);
}

/** 
 *  @brief The function for ls deep sleep mode.
 *         
 *  @param[in] Option The RTC wake up event.
 *                - bit[3]: Wake up per day.
 *                - bit[2]: Wake up per hour.
 *                - bit[1]: Wake up per minute.
 *                - bit[0]: Wake up per second.
 *  @param[in]  Memsel, 1: Enable memory, 0: Disable memory.
 *
 *  @returns void
 */
void DeepSleep_RTC (u8 Option, u8 Memsel)
{
    hal_DeepSleep_RTC (Option, Memsel);
}

/** 
 *  @brief The function for ls sleep mode.
 *         
 *  @param[in]  Option, To slect AON Timer,GPIO...etc
 *                - bit[4]: the UART Wake up event.
 *                - bit[3]: the PWM Wake up event.
 *                - bit[2]: the GPIO A13 as a Wake up event.
 *                - bit[1]: the GTimer Wake up event. Only active at 128kHz
 *                - bit[0]: the AON Timer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value. Uint: us
 *  @param[in]  Clock, 1: 100kHz, 0: 128kHz.
 *  @param[in]  GpioOption, GPIOA0~A13 as a wake up trigger.
 *
 *  @returns void
 */
void SleepCG (u16 Option, u32 SDuration, u8 Clock, u8 GpioOption)
{
    hal_SleepCG (Option, SDuration, Clock, GpioOption);
}

/** 
 *  @brief The function for ls standby mode.
 *         
 *  @param[in]  Option, To slect AON Timer,GPIO...etc
 *                - bit[4]: the UART Wake up event.
 *                - bit[3]: the PWM Wake up event.
 *                - bit[2]: the GPIO Wake up event.
 *                - bit[1]: the GTimer Wake up event. Not ready
 *                - bit[0]: the AON Timer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value(Max:8300 sec). Uint: us
 *  @param[in]  Memsel, 1: Enable memory, 0: Disable memory.
 *  @param[in]  GpioOption, GPIOA0~A13 as a wake up trigger.
 *
 *  @returns void
 */
void Standby (u16 Option, u64 SDuration, u8 Memsel, u8 GpioOption)
{
    #if 0
    if(Option & SLP_GPIO) {
        if (GpioOption != 13) {
            gpio_irq_init(&gpio_irq, GpioOption, NULL, (uint32_t)&gpio_irq);
            gpio_irq_pull_ctrl(&gpio_irq, PullNone);
            gpio_irq_set(&gpio_irq, IRQ_FALL, 1);
        }
    }
    #endif
    
    #ifdef __GNUC__
        extern int __malloc_av_, __malloc_sbrk_base; 
        *(((uint32_t*)&(__malloc_av_)) + 2)= &__malloc_av_;
        *(uint32_t*)&(__malloc_sbrk_base)= 0xffffffff;
    #endif
  
    hal_Standby (Option, SDuration, Memsel, GpioOption);
}

/** 
 *  @brief The function for hs power on.
 *         
 *  @param[in] none.
 *
 *  @returns void
 */
void HS_Power_On (void)
{
    __disable_irq();
     hs_power_on ();
    __enable_irq();
}

/** 
 *  @brief The function for reading ls gpio wake status.
 *         
 *  @param[in]  none
 *
 *  @returns     0xFFFFFFFF:  The GPIO wake event wasn't trigger.
 *  @returns     Others: ls gpio wake status.
 */
u32 ls_gpio_wake_sts (void)
{
    return hal_ls_gpio_wake_sts();
}

/**
 *  @brief   Set BOD level
 *
 *  @param   bod_lvl: BOD level, max value is 7,
 *                               min value is 0.
 *  @return  void
 *
 */
void BOD_Level_Setting (int bod_lvl)
{     
    sys_set_bod(bod_lvl);
}