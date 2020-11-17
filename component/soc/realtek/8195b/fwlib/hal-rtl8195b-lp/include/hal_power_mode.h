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
 * @addtogroup ls_hal_power_mode POWER MODE
 * @ingroup 8195bl_hal
 * @{
 * @brief The POWER MODE HAL module of the LS platform.
 */

//SLP
#define     SLP_STIMER    BIT0
#define     SLP_GTIMER    BIT1
#define     SLP_GPIO      BIT2
#define     SLP_PWM       BIT3
#define     SLP_UART      BIT4
#define     SLP_HSTIMER   BIT5
#define     SLP_WLAN      BIT6
#define     SLP_I2C       BIT7
#define     SLP_ADC       BIT8
#define     SLP_COMP      BIT9
#define     SLP_SGPIO     BIT10
//#define     SLP_WL        BIT3

//DSTBY
#define     DSTBY_STIMER  BIT0
#define     DSTBY_GTIMER  BIT1
#define     DSTBY_GPIO    BIT2
#define     DSTBY_PWM     BIT3
#define     DSTBY_UART    BIT4
#define     DSTBY_HSTIMER BIT5
#define     DSTBY_WLAN    BIT6
#define     DSTBY_I2C     BIT7
#define     DSTBY_ADC     BIT8
#define     DSTBY_COMP    BIT9
#define     DSTBY_SGPIO   BIT10
#define     DSTBY_RTC     BIT11
//#define     DSTBY_NFC     BIT3

//DS wake event
#define DS_STIMER       BIT0
#define DS_GPIO_FALL    BIT1
#define DS_GPIO_RISE    BIT2
#define DS_ADP          BIT3
#define DS_RTC          BIT4

enum clk_idx{
    CLK_128K = 0,
    CLK_100K = 1,
};

void slp_ls_cg_cmd_handler (uint32_t cmd, uint32_t op, uint32_t arg);
void slp_ls_pd_cmd_handler (uint32_t cmd, uint32_t op, uint32_t arg);
VOID hs_power_on (VOID);
VOID hs_power_off_b (VOID);
VOID hs_power_off (VOID);
void hal_sys_reg_irq(uint32_t wake_buff);

/**
  * @brief The stubs functions table to exports POWER MODE HAL functions in ROM.
  */

//extern const hal_chg_func_stubs_t hal_chg_stubs;

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
void hal_DeepSleep (u8  Option, u64 SDuration, u8 Memsel, u8 Clock);

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
void hal_DeepSleep_RTC (u8 Option, u8 Memsel);

/** 
 *  @brief The function for ls sleep mode.
 *         
 *  @param[in]  Option, To slect AON Timer,GPIO...etc
 *                - bit[4]: the UART Wake up event.
 *                - bit[3]: the PWM Wake up event.
 *                - bit[2]: the GPIO as a Wake up event.
 *                - bit[1]: the GTimer Wake up event. Only active at 128kHz
 *                - bit[0]: the AON Timer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value. Uint: us
 *  @param[in]  Clock, 1: 100kHz, 0: 128kHz.
 *  @param[in]  GpioOption, GPIOA0~A13 as a wake up trigger.
 *
 *  @returns void
 */
void hal_SleepCG (u16 Option, u32 SDuration, u8 Clock, u8 GpioOption);

/** 
 *  @brief The function for ls standby mode.
 *         
 *  @param[in]  Option, To slect AON Timer,GPIO...etc
 *                - bit[4]: the UART Wake up event.
 *                - bit[3]: the PWM Wake up event.
 *                - bit[2]: the GPIO as a Wake up event.
 *                - bit[1]: the GTimer Wake up event.
 *                - bit[0]: the AON Timer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value(Max:8300 sec). Uint: us
 *  @param[in]  Memsel, 1: Enable memory, 0: Disable memory.
 *  @param[in]  GpioOption, GPIOA0~A13 as a wake up trigger.
 *
 *  @returns void
 */
void hal_Standby (u16 Option, u64 SDuration, u8 Memsel, u8 GpioOption);

/** 
 *  @brief The function for reading ls gpio wake status.
 *         
 *  @param[in]  none
 *
 *  @returns     0xFFFFFFFF:  The GPIO wake event wasn't trigger.
 *  @returns     Others: ls gpio irq status.
 */
u32 hal_ls_gpio_wake_sts (void);

/**
 *  @brief   Set BOD level
 *
 *  @param   bod_lvl: BOD level, max value is 7,
 *                               min value is 0.
 *  @return  void
 *
 */
void sys_set_bod(int bod_lvl);

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group ls_hal_power_mode */

#endif  // end of "#define _HAL_POWER MODE_H_"
