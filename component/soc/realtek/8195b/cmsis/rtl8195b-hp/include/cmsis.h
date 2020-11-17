/**************************************************************************//**
 * @file     cmsis.h
 * @brief    The generic CMSIS include file.
 * @version  V1.00
 * @date     2016-7-20
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

#ifndef MBED_CMSIS_H
#define MBED_CMSIS_H

#define TM9_ITCM_ROM_BASE         (0x00000000UL)
#define TM9_ITCM_RAM_BASE         (0x00010000UL)
#define TM9_ROM_BASE              (0x10000000UL)
#define TM9_DTCM_ROM_BASE         (0x20000000UL)
#define TM9_DTCM_RAM_BASE         (0x20010000UL)
#define TM9_RAM_BASE              (0x20100000UL)

#define TM9_APB_BASE              (0x40000000UL)
#define TM9_SEC_APB_BASE          (0x50000000UL)

#define TM9_SYSON_BASE            (TM9_APB_BASE       + 0x000000UL)
#define TM9_WLAN_BASE             (TM9_APB_BASE       + 0x080000UL)
#define TM9_USB_OTG_BASE          (TM9_APB_BASE       + 0x0C0000UL)
#define TM9_ISP_BASE              (TM9_APB_BASE       + 0x300000UL)     // ISP/MIPI
#define TM9_PSRAMPHY_BASE         (TM9_APB_BASE       + 0x402000UL)     // PSRAM/LPDDR1 Phy. Controller
#define TM9_LPDDRPCAL_BASE        (TM9_APB_BASE       + 0x420000UL)     // LPDDR1 Phy. Calibration
#define TM9_VOE_BASE              (TM9_APB_BASE       + 0x490000UL)     // Video Offload Engine
#define TM9_TFT_BASE              (TM9_APB_BASE       + 0x491000UL)     // TFT Controller
#define TM9_H264_BASE             (TM9_APB_BASE       + 0x500000UL)     // H.264 Encoder
#define TM9_MJPG_BASE             (TM9_APB_BASE       + 0x580000UL)     // MJPG Encoder
#define TM9_PSRAM_BASE            (TM9_APB_BASE       + 0x600000UL)     // PSRAM Controller
#define TM9_LPDDR_BASE            (TM9_APB_BASE       + 0x601000UL)     // LPDDR Controller

#define TM9_PSRAM_MEM_BASE        (0x60000000UL)
#define TM9_LPDDR_MEM_BASE        (0x70000000UL)

#define TM9_IDAU_BASE             (TM9_SEC_APB_BASE   + 0x000000UL)     // Secure Cross-Bar controller (IDAU)

#include "cmsis_compiler.h"
#include "platform_conf.h"
#include "basic_types.h"
#include "rtl8195bhp.h"
#include "section_config.h"
#include "hal_api.h"
#include "diag.h"

#if (defined(ROM_REGION) && (ROM_REGION==1)) || (defined(CONFIG_BUILD_LIB) && (CONFIG_BUILD_LIB==1))
// TODO: move ROM & Lib reference header file here
#include "rtl8195bhp_syson.h"
#include "rtl8195bhp_vendor.h"
#include "rtl8195bhp_vendor_s.h"
#include "rtl8195bhp_crypto.h"
#endif

#include "rtl8195bhp_irq.h"             /* The IRQ priority definition */
#include "rtl8195bhp_syson_ctrl.h"
#include "rtl8195bhp_crypto_ctrl.h"
#include "rtl8195bhp_peri_id.h"
#include "rtl8195bhp_pin_name.h"
#include "rtl8195bhp_cache.h"
#include "rtl8195bhp_gdma.h"
#include "rtl8195bhp_uart.h"
#include "rtl8195bhp_timer.h"
#include "rtl8195bhp_pwm.h"
#include "rtl8195bhp_icc.h"
#include "rtl8195bhp_flash.h"
#include "rtl8195bhp_spic.h"
#include "rtl8195bhp_ssi.h"
#include "rtl8195bhp_gpio.h"
#include "rtl8195bhp_lpi.h"
#include "rtl8195bhp_sce.h"
#include "rtl8195bhp_misc.h"
#include "rtl8195bhp_sdio_host.h"
#include "rtl8195bhp_pinmux.h"
#include "rtl8195bhp_i2s.h"
#include "rtl8195bhp_pcm.h"
#include "rtl8195bhp_sgpio.h"
#include "rtl8195bhp_adc.h"
#include "rtl8195bhp_eth.h"
#include "rtl8195bhp_i2c.h"
#include "rtl8195bhp_efuse.h"
#if CONFIG_USB_OTG_EN
#include "rtl8195bhp_otg.h"
#include "rtl8195bhp_usb.h"
#endif
#if CONFIG_SDIO_DEVICE_EN
#include "rtl8195bhp_sdio_dev.h"
#endif
#if (defined(ROM_REGION) && (ROM_REGION==1)) || (defined(CONFIG_BUILD_LIB) && (CONFIG_BUILD_LIB==1))
//#include "rtl8195bhp_lcdc.h"
#endif
#include <arm_cmse.h>   /* Use CMSE intrinsics */
#if CONFIG_CMSIS_OS_EN
#include "cmsis_os.h"               // CMSIS RTOS header file
#endif

#endif  // end of "#ifndef MBED_CMSIS_H"

