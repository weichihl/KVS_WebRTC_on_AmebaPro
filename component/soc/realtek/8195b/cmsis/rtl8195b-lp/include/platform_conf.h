/**************************************************************************//**
 * @file     platform_conf.h
 * @brief    The platform configuration file.
 * @version  V1.00
 * @date     2016-05-17
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 *
 ******************************************************************************/

#ifndef _PLATFORM_CONF_H_
#define _PLATFORM_CONF_H_

/* System configuration */
#define RTL8195BLP                          1
#define CONFIG_CPU_CLK                      (4000000)
#define PLATFORM_CLK                        (2000000)
#define CONFIG_FPGA                         0
#define CONFIG_FPGAV6                       0

#define CHIP_A_CUT                          0
#define CHIP_B_CUT                          1
#define CHIP_C_CUT                          2
#define CHIP_D_CUT                          3

#if CONFIG_FPGA
#define CHIP_VER                            (CHIP_D_CUT)
#else
#define CHIP_VER                            (CHIP_C_CUT)
#endif

/* ROM code version */
#define ROM_VER_MAIN                        (CHIP_VER+1)
#define ROM_VER_SUB                         (0)

/* Peripheral device configuration */
#define CONFIG_PWR_EN                       1   // build power mode source code: 2
#define CONFIG_GTIMER_EN                    1
#define CONFIG_WDG_EN                       1
#define CONFIG_GDMA_EN                      1
#define CONFIG_GPIO_EN                      1
#define CONFIG_UART_EN                      1
#define CONFIG_I2C_EN                       1
#define CONFIG_SOC_PS_EN                    1
#define CONFIG_EFUSE_EN                     1
#define CONFIG_EFUSE_NORMAL                 1
#define CONFIG_SPI_FLASH_EN                 1
#define CONFIG_ADC_EN                       1
#define CONFIG_COMP_EN                      1
#define CONFIG_DAC_EN                       1
#define CONFIG_PWM_EN                       1
#define CONFIG_RTC_EN                       1
#define CONFIG_ICC_EN                       1
#define CONFIG_QDEC_EN                      1
#define CONFIG_CIR_EN                       1
#define CONFIG_SGPIO_EN                     1
#define CONFIG_CHG_EN                       1

#define CONFIG_CMSIS_FREERTOS_EN            0   // is enable FreeRTOS, it should be 0 for LS platform

#define CONFIG_CMSIS_RTX_EN                 1   // is enable RTX RTOS
#define CONFIG_RTX_IN_ROM                   1   // is RTX in ROM ?

#define CONFIG_DEBUG_LOG                    1
#define CONFIG_DEBUG_ERROR                  1
#define CONFIG_DEBUG_WARN                   1
#define CONFIG_DEBUG_INFO                   1

#define CONFIG_LIGHT_PRINTF                 1   // use lighter printf (use smaller stack size)

#define CONFIG_SYS_TIMER_ID                 0   // the G-Timer ID be used as free run system ticker
#if CONFIG_FPGA
#define CONFIG_TIMER_SCLK_FREQ              (2000000)   // GTimer SCLK: 4M / 2M / 32K / Ext.32K
#else
#define CONFIG_TIMER_SCLK_FREQ              (32000)   // GTimer SCLK: 4M / 2M / 32K / Ext.32K
#endif
#if (CONFIG_TIMER_SCLK_FREQ == 32000)
#define CONFIG_SYS_TICK_TIME                (1000000/CONFIG_TIMER_SCLK_FREQ)   // in us
#else
#define CONFIG_SYS_TICK_TIME                (1)   // in us
#endif
#define STDIO_UART_IDX                      (1)       // STDIO UART port index

/* Verifi each IP configuration */
#define CONFIG_VRF_MODE                      0

#define LOAD_FLAH_IMG_EN                    (1)   // is enable to load the image from the flash

#if (CHIP_VER > CHIP_A_CUT)
#define HARD_FAULT_BACK_TRACE               (1)     // is enable the stack back trace for hard fault exception
#else
#define HARD_FAULT_BACK_TRACE               (0)
#endif


#if defined(CONFIG_BUILD_RAM) && (CONFIG_BUILD_RAM == 1)
#define __STACK_SIZE                        (0x0800)    // 2K, main stack memory size
#endif  // end of "#if defined(CONFIG_BUILD_RAM) && (CONFIG_BUILD_RAM == 1)"

#endif  // end of "#define _PLATFORM_CONF_H_"

