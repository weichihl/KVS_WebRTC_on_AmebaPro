/**************************************************************************//**
 * @file     rtl8195blp_syson_ctrl.h
 * @brief    Defines macros and data type for the System On domain control.
 * @version  v1.00
 * @date     2017/11/16
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
 * @addtogroup ls_hal_syson SysOn
 * @ingroup 8195bl_hal
 * @{
 * @brief The HAL API for System Control.
 */

#ifndef RTL8195BLP_SYSON_CTRL_H
#define RTL8195BLP_SYSON_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief  System PLL clock rate selection.
*/
enum  sys_pll_clock_e {
    SYS_PLL_CLK_300M  = 0,    /*!< 300Mhz */
    SYS_PLL_CLK_200M  = 1     /*!< 200Mhz */
};

/**
  \brief  System clock source selection.
*/
enum  sys_clock_source_e
{
    SYS_CLK_SRC_ANA  = 0,   /*!< Clock source = ANA, 4M */
    SYS_CLK_SRC_PLL  = 1    /*!< Clock source = PLL, 200M/300M */
};

/**
  \brief  System AON(Power Always On) domain wake events.
*/
enum  aon_wake_event_e {
    AON_WKEV_GPIO      = 0,    /*!< Wake by GPIO interrupt */
    AON_WKEV_TIMER     = 1,    /*!< Wake by AON Timer interrupt */
    AON_WKEV_RTC       = 2,    /*!< Wake by RTC interrupt */
    AON_WKEV_PWR_ADP   = 3     /*!< Wake by Power Adapter */
};

#define SYS_WKEV_AON_MASK       (0x80)

/**
  \brief  System wake events.
*/
enum  sys_wake_event_e {
   SYS_WKEV_GTIMER      = 1,    /*!< Wake by G-Timer interrupt */
   SYS_WKEV_SWR_OCP     = 2,    /*!< Wake by Switch Regulator Over Current Protector */
   SYS_WKEV_BOD         = 3,    /*!< Wake by Brown Out Detector */
   SYS_WKEV_GPIO        = 4,    /*!< Wake by GPIO Interrupt */
   SYS_WKEV_PWM         = 5,    /*!< Wake by PWM Interrupt */
   SYS_WKEV_WLAN        = 8,    /*!< Wake by WLan Interrupt */
   SYS_WKEV_UART        = 20,   /*!< Wake by UART Interrupt */
   SYS_WKEV_I2C         = 24,   /*!< Wake by I2C Interrupt */
   SYS_WKEV_ADC         = 26,   /*!< Wake by ADC Interrupt */
   SYS_WKEV_COMP        = 27,   /*!< Wake by (AD)Comparetor Interrupt */
   SYS_WKEV_SGPIO       = 28,   /*!< Wake by SGPIO Interrupt */
   SYS_WKEV_AON         = 29,   /*!< Wake by AON domain Interrupt */
   SYS_WKEV_HS          = 30,   /*!< Wake by the Interrupt from HS */

   SYS_WKEV_AON_GPIO    = (SYS_WKEV_AON_MASK | AON_WKEV_GPIO),       /*!< Wake by the AON GPIO Interrupt */
   SYS_WKEV_AON_TIMER   = (SYS_WKEV_AON_MASK | AON_WKEV_TIMER),      /*!< Wake by the AON Timer Interrupt */
   SYS_WKEV_AON_RTC     = (SYS_WKEV_AON_MASK | AON_WKEV_RTC),        /*!< Wake by the AON RTC Interrupt */
   SYS_WKEV_AON_PWR_ADP = (SYS_WKEV_AON_MASK | AON_WKEV_PWR_ADP)     /*!< Wake by the AON Power Adapter */
};
typedef uint8_t sys_wake_event_t;

#ifndef _EFUSE_BOOT_CFG_H
typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t hs_sys_pll_sel     : 1;       /*!< [0..0] HS platform Sys PLL clock selection, 1: 300M, 0: 200M */
    __IOM uint8_t hs_sys_pll_dev_sel : 4;       /*!< [4..1] HS platform Sys PLL clock devider selection */
    __IM  uint8_t                    : 3;       /*!< [7..5] Reserved */
  } bit;
} efuse_clk_cfg1_t, *pefuse_clk_cfg1_t;
#endif  // #ifndef _EFUSE_BOOT_CFG_H

/**
  \brief  SysOn IRQ(System Wake Event) handler type.
*/
typedef void (*syson_irq_handler_t)(uint32_t arg);

/**
  \brief  The data type for SysOn HAL entity manamgment.
*/
typedef struct hal_syson_adapter_s {
    uint32_t sys_wake_event;                    /*!< the system wake event */
    uint32_t aon_wake_event;                    /*!< the AON wake event */
    syson_irq_handler_t gtimer_handler;         /*!< the G-Timer event callback function */
    uint32_t gtimer_arg;                        /*!< the argument of G-Timer event callback function */ 
    syson_irq_handler_t swr_ocp_handler;        /*!< the Switch Regulator OCP event callback function */
    uint32_t swr_ocp_arg;                       /*!< the argument of Switch Regulator OCP event callback function */ 
    syson_irq_handler_t bod_handler;            /*!< the Brown Out Detector event callback function */
    uint32_t bod_arg;                           /*!< the argument of Brown Out Detector event callback function */ 
    syson_irq_handler_t gpio_handler;           /*!< the GPIO event callback function */
    uint32_t gpio_arg;                          /*!< the argument of GPIO event callback function */ 
    syson_irq_handler_t pwm_handler;            /*!< the PWM event callback function */
    uint32_t pwm_arg;                           /*!< the argument of PWM event callback function */ 
    syson_irq_handler_t wlan_handler;           /*!< the WLAN event callback function */
    uint32_t wlan_arg;                          /*!< the argument of PWM event callback function */ 
    syson_irq_handler_t uart_handler;           /*!< the UART event callback function */
    uint32_t uart_arg;                          /*!< the argument of PWM event callback function */ 
    syson_irq_handler_t i2c_handler;            /*!< the I2C event callback function */
    uint32_t i2c_arg;                           /*!< the argument of I2C event callback function */ 
    syson_irq_handler_t adc_handler;            /*!< the ADC event callback function */
    uint32_t adc_arg;                           /*!< the argument of ADC event callback function */ 
    syson_irq_handler_t comp_handler;           /*!< the Comparetor event callback function */
    uint32_t comp_arg;                          /*!< the argument of Comparetor event callback function */ 
    syson_irq_handler_t sgpio_handler;          /*!< the SGPIO event callback function */
    uint32_t sgpio_arg;                         /*!< the argument of SGPIO event callback function */ 
    syson_irq_handler_t aon_handler;            /*!< the AON domain wake event callback function */
    uint32_t aon_arg;                           /*!< the argument of AON domain wake event callback function */ 
    syson_irq_handler_t hs_handler;             /*!< the HS wake event callback function */
    uint32_t hs_arg;                            /*!< the argument of HS wake event callback function */ 
    syson_irq_handler_t aon_gpio_handler;       /*!< the AON domain GPIO event callback function */
    uint32_t aon_gpio_arg;                      /*!< the argument of AON domain GPIO event callback function */ 
    syson_irq_handler_t aon_timer_handler;      /*!< the AON domain Timer event callback function */
    uint32_t aon_timer_arg;                     /*!< the argument of AON domain Timer event callback function */ 
    syson_irq_handler_t aon_rtc_handler;        /*!< the AON domain RTC event callback function */
    uint32_t aon_rtc_arg;                       /*!< the argument of AON domain RTC event callback function */ 
    syson_irq_handler_t aon_padp_handler;       /*!< the AON domain power adapter event callback function */
    uint32_t aon_padp_arg;                      /*!< the argument of AON domain power adapter event callback function */ 

    uint32_t reserved[16];    // reserved for RAM code extension
} hal_syson_adapter_t, *phal_syson_adapter_t;

/**
  \brief  The data structure for the SysOn ROM API functions exporting.
*/
typedef struct hal_syson_func_stubs_s {
    void (*hal_syson_sys_clk_sel) (uint32_t clk_src, efuse_clk_cfg1_t *clk_sel);
    void (*hal_syson_reg_wake_event_handler) (sys_wake_event_t event, syson_irq_handler_t handler, uint32_t arg);
    void (*hal_syson_unreg_wake_event_handler) (sys_wake_event_t event);    
    void (*hal_syson_enable_wake_event) (sys_wake_event_t event);
    void (*hal_syson_disable_wake_event) (sys_wake_event_t event);
    void (*hal_syson_reg_irq) (int_vector_t handler);
    void (*hal_syson_init) (hal_syson_adapter_t *psyson_adp);

    uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} hal_syson_func_stubs_t;

/** 
 * @addtogroup ls_hal_syson_rom_func
 * @{
 */

void hal_syson_sys_clk_sel_rtl8195blp (uint32_t clk_src, efuse_clk_cfg1_t *clk_sel);
void hal_syson_reg_wake_event_handler_rtl8195blp (sys_wake_event_t event, syson_irq_handler_t handler, uint32_t arg);
void hal_syson_unreg_wake_event_handler_rtl8195blp (sys_wake_event_t event);
void hal_syson_enable_wake_event_rtl8195blp (sys_wake_event_t event);
void hal_syson_disable_wake_event_rtl8195blp (sys_wake_event_t event);
void hal_syson_reg_irq_rtl8195blp (int_vector_t handler);
void hal_syson_init_rtl8195blp (hal_syson_adapter_t *psyson_adp);

/** @} */ /* End of group ls_hal_syson_rom_func */

#ifdef __cplusplus
}
#endif

#endif /* RTL8195BLP_SYSON_CTRL_H */


/** @} */ /* End of group ls_hal_syson */


