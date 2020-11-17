/**************************************************************************//**
 * @file     hal_timer.c
 * @brief    This TIMER HAL API functions.
 *
 * @version  V1.00
 * @date     2017-07-15
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

#include "hal_timer.h"

#if CONFIG_GTIMER_EN //CONFIG_GTIMER_EN
#define COMPENSATION_TIME 28
/**
 * @addtogroup ls_hal_timer TIMER
 * @{
 */

/**
 *  @brief Reads the count of the system timer. It return the counter register value directly.
 *
 *  @returns    Current tick count of the system time, in us. This count value will be reset to 0
 *              when ever the counter register is overflowed.
 */
uint32_t hal_read_curtime_us (void)
{
    uint32_t i;
    if((CONFIG_TIMER_SCLK_FREQ == 32000) || (CONFIG_TIMER_SCLK_FREQ == 32768)) {
        HAL_WRITE32(0xA0002000,8,0x80);
        for (i=0;i<100000;i++) {
            if ((HAL_READ32(0xA0002000,8) & 0x80) == 0) {
                break;
            } else {
                __NOP();
            }
        }
        return (HAL_READ32(0xA0002000,0xC) <<5);
    } else {
        HAL_WRITE32(0xA0002000,8,0x90);
        for (i=0;i<100000;i++) {
            if ((HAL_READ32(0xA0002000,8) & 0x80) == 0) {
                break;
            } else {
                __NOP();
            }
        }
        return HAL_READ32(0xA0002000,0xC);
    }
    //return hal_gtimer_stubs.hal_read_curtime ();
}

/**
 *  @brief Makes a delay.
 *
 *  @param[in]  time_us  The delay period in micro-second.
 *
 *  @returns    void
 */
void hal_delay_us (uint32_t time_us)
{
    if(time_us > COMPENSATION_TIME){
        time_us = time_us - COMPENSATION_TIME;
    }
    uint32_t start = hal_read_curtime_us();

    while ((hal_read_curtime_us() - start) < time_us);
    //hal_gtimer_stubs.hal_delay_us (time_us);
}

/** @} */ /* End of group ls_hal_timer */

#endif  // end of "#if CONFIG_GTIMER_EN"

