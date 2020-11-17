/**************************************************************************//**
 * @file     rtl8195bhp_syson_ctrl.h
 * @brief    Defines macros and data types for the System Power On dommin control.
 * @version  v1.00
 * @date     2017/11/17
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
 * @addtogroup hs_hal_syson SysOn
 * @ingroup 8195bh_hal
 * @{
 * @brief The HAL API for System Control.
 */

#ifndef RTL8195BHP_SYSON_CTRL_H
#define RTL8195BHP_SYSON_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief  Define the PLL clock rate
*/
enum pll_clock_rate_e {
    PLL_CLK_200M        = 200000000,
    PLL_CLK_300M        = 300000000
};
typedef uint32_t pll_clock_rate_t;

/**
  \brief  Define the Sys clock rate
*/
enum sys_clock_rate_e {
    SYS_CLK_2M          = 2000000,
    SYS_CLK_4M          = 4000000,
    SYS_CLK_100M        = 100000000,
    SYS_CLK_150M        = 150000000,
    SYS_CLK_200M        = 200000000,
    SYS_CLK_300M        = 300000000
};
typedef uint32_t sys_clock_rate_t;

/**
  \brief  System PLL clock rate selection.
*/
enum  sys_pll_clock_e {
    SYS_PLL_CLK_300M  = 0,    ///< 300Mhz
    SYS_PLL_CLK_200M  = 1     ///< 200Mhz
};

/**
  \brief  System clock source selection.
*/
enum  sys_clock_source_e {
    SYS_CLK_SRC_ANA  = 0,   ///< Clock source = ANA, 4M
    SYS_CLK_SRC_PLL  = 1    ///< Clock source = PLL, 200M/300M
};

/**
  \brief  System wake event selection.
*/
enum  sys_wake_event_e {
   SYS_WKEV_GTIMER      = 1,    /*! Wake by G-Timer interrupt */
   SYS_WKEV_BOOST_OCP   = 2,    /*! Wake by Boost Over Current Protector */
   SYS_WKEV_SWR_OCP     = 3,    /*! Wake by Switch Regulator Over Current Protector */
   SYS_WKEV_GPIO        = 4,    /*! Wake by GPIO Interrupt */
   SYS_WKEV_PWM         = 5,    /*! Wake by PWM Interrupt */
   SYS_WKEV_WLAN        = 8,    /*! Wake by WLan Interrupt */
   SYS_WKEV_SDIO        = 14,   /*! Wake by SDIO device Interrupt */
   SYS_WKEV_USB         = 16,   /*! Wake by USB device Interrupt */
   SYS_WKEV_UART        = 20,   /*! Wake by UART Interrupt */
   SYS_WKEV_I2C         = 24,   /*! Wake by I2C Interrupt */
   SYS_WKEV_ADC         = 26,   /*! Wake by ADC Interrupt */
   SYS_WKEV_SGPIO       = 28    /*! Wake by SGPIO Interrupt */
};
typedef uint8_t sys_wake_event_t;

enum  ldoio_mode_e {
    LDOIO_BYPASS    = 0,    /*! bypass mode */
    LDOIO_LDO       = 1     /*! LDO mode */
};

/**
  \brief  SysOn IRQ(System Wake Event) handler type.
*/
typedef void (*syson_irq_handler_t)(uint32_t arg);

/**
  \brief  The data type for SysOn HAL entity manamgment.
*/
typedef struct hal_syson_adapter_s {
    uint32_t sys_wake_event;                /*!< the system wake event */
    syson_irq_handler_t sgpio_handler;      /*!< the SGPIO event callback function */
    uint32_t sgpio_arg;                     /*!< the argument of SGPIO event callback function */
    syson_irq_handler_t adc_handler;        /*!< the ADC event callback function */
    uint32_t adc_arg;                       /*!< the argument of ADC event callback function */
    syson_irq_handler_t i2c_handler;        /*!< the I2C event callback function */
    uint32_t i2c_arg;                       /*!< the argument of I2C event callback function */
    syson_irq_handler_t uart_handler;       /*!< the UART event callback function */
    uint32_t uart_arg;                      /*!< the argument of PWM event callback function */
    syson_irq_handler_t usb_handler;        /*!< the USB wake event callback function */
    uint32_t usb_arg;                       /*!< the argument of USB wake event callback function */
    syson_irq_handler_t sdio_handler;       /*!< the SDIO device wake event callback function */
    uint32_t sdio_arg;                      /*!< the argument of SDIO device wake event callback function */
    syson_irq_handler_t wlan_handler;       /*!< the WLAN event callback function */
    uint32_t wlan_arg;                      /*!< the argument of PWM event callback function */
    syson_irq_handler_t pwm_handler;        /*!< the PWM event callback function */
    uint32_t pwm_arg;                       /*!< the argument of PWM event callback function */
    syson_irq_handler_t gpio_handler;       /*!< the GPIO event callback function */
    uint32_t gpio_arg;                      /*!< the argument of GPIO event callback function */
    syson_irq_handler_t swr_ocp_handler;    /*!< the Switch Regulator OCP event callback function */
    uint32_t swr_ocp_arg;                   /*!< the argument of Switch Regulator OCP event callback function */
    syson_irq_handler_t boost_ocp_handler;  /*!< the Boost OCP event callback function */
    uint32_t boost_ocp_arg;                 /*!< the argument of Boost OCP event callback function */
    syson_irq_handler_t gtimer_handler;     /*!< the G-Timer event callback function */
    uint32_t gtimer_arg;                    /*!< the argument of G-Timer event callback function */
} hal_syson_adapter_t, *phal_syson_adapter_t;

/**
  \brief  The data structure to export the SysOn API functions in ROM.
*/
typedef struct hal_syson_func_stubs_s {
    void (*hal_syson_sys_clk_sel) (uint32_t clk_src, uint32_t clk_sel);
    void (*hal_syson_sys_clk_div) (uint32_t div_en, uint32_t div_sel);
    uint32_t (*hal_syson_query_sys_clk) (void);
    void (*hal_syson_set_sys_clk) (sys_clock_rate_t sys_clk);
    void (*hal_syson_reg_wake_event_handler) (sys_wake_event_t event, syson_irq_handler_t handler, uint32_t arg);
    void (*hal_syson_unreg_wake_event_handler) (sys_wake_event_t event);
    void (*hal_syson_enable_wake_event) (sys_wake_event_t event);
    void (*hal_syson_disable_wake_event) (sys_wake_event_t event);
    void (*hal_syson_reg_irq) (int_vector_t handler);
    void (*hal_syson_init) (hal_syson_adapter_t *psyson_adp);

    uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} hal_syson_func_stubs_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_syson_rom_func
 * @{
 */

void hal_syson_sys_clk_sel_rtl8195bhp (uint32_t clk_src, uint32_t clk_sel);
void hal_syson_sys_clk_div_rtl8195bhp (uint32_t dev_en, uint32_t dev_sel);
uint32_t hal_syson_query_sys_clk_rtl8195bhp (void);
void hal_syson_set_sys_clk_rtl8195bhp (sys_clock_rate_t sys_clk);
void hal_syson_reg_wake_event_handler_rtl8195bhp (sys_wake_event_t event, syson_irq_handler_t handler, uint32_t arg);
void hal_syson_unreg_wake_event_handler_rtl8195bhp (sys_wake_event_t event);
void hal_syson_enable_wake_event_rtl8195bhp (sys_wake_event_t event);
void hal_syson_disable_wake_event_rtl8195bhp (sys_wake_event_t event);
void hal_syson_reg_irq_rtl8195bhp (int_vector_t handler);
void hal_syson_init_rtl8195bhp (hal_syson_adapter_t *psyson_adp);

/** @} */ /* End of group hs_hal_syson_rom_func */

#ifdef __cplusplus
}
#endif

#endif /* RTL8195BHP_SYSON_CTRL_H */

/** @} */ /* End of group hs_hal_syson */

