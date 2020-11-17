/**************************************************************************//**
 * @file     hal_power_mode.h
 * @brief    The HAL API implementation for the POWER MODE device.
 * @version  V1.00
 * @date     2018-06-08
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

#ifndef _HAL_POWER_MODE_H_
#define _HAL_POWER_MODE_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_power_mode POWER MODE
 * @ingroup 8195bh_hal
 * @{
 * @brief The POWER MODE HAL module of the HS platform.
 */

//SLP
#define     SLP_GTIMER    BIT1
#define     SLP_GPIO      BIT2
#define     SLP_PWM       BIT3
#define     SLP_UART      BIT4
#define     SLP_MII   	  BIT5
#define     SLP_WLAN      BIT6
#define     SLP_I2C       BIT7
#define     SLP_ADC       BIT8
#define     SLP_USB       BIT9
#define     SLP_SGPIO     BIT10
#define     SLP_SDIO      BIT11


//DSTBY
#define     DSTBY_GTIMER  BIT1
#define     DSTBY_GPIO    BIT2
#define     DSTBY_WLAN    BIT6

enum clk_idx{
    CLK_128K = 0,
    CLK_100K = 1,
};

void slp_hs_cg_cmd_handler (uint32_t cmd, uint32_t op, uint32_t arg);
void slp_hs_pd_cmd_handler (uint32_t cmd, uint32_t op, uint32_t arg);

/** 
 *  @brief The function for hs sleep clock gated.
 *         
 *  @param[in]  Option, To slect HS Timer, GPIO and PWM...etc
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
void hal_SleepCG (u16 Option, u32 SDuration, u8 Clock, u8 GpioOption);

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
void hal_SleepPG (u16 Option, u32 SDuration, u8 Memsel, u8 GpioOption);

/** 
 *  @brief The function for Boost ON/OFF.
 *         
 *  @param[in]  Option, 1: Enable, 0: Disable
 *
 *  @returns void
 */
void hal_Boost (u8 Option);

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group hs_hal_power_mode */

#endif  // end of "#define _HAL_POWER MODE_H_"
