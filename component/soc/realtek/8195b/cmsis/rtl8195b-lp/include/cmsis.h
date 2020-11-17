/**************************************************************************//**
 * @file     cmsis.h
 * @brief    The generic CMSIS include file..
 * @version  v1.00
 * @date     2017/11/23
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

#define KM0_APB_BASE              (0xA0000000UL)

#define KM0_SYSON_BASE            (KM0_APB_BASE      + 0x00200UL)

#include "cmsis_compiler.h"
#include "platform_conf.h"
#include "basic_types.h"
#include "section_config.h"
#include "rtl8195blp.h"

#if (defined(ROM_REGION) && (ROM_REGION==1)) || (defined(CONFIG_BUILD_LIB) && (CONFIG_BUILD_LIB==1))
#include "memory.h"
#include "efuse_boot_cfg.h"
// TODO: move ROM & Lib reference header file here
#include "rtl8195blp_aon.h"
#include "rtl8195blp_syson.h"
#include "rtl8195blp_vendor.h"
#endif

#include "hal_api.h"
#include "diag.h"

#include "rtl8195blp_ramstart.h"
#include "rtl8195blp_peri_id.h"
#include "rtl8195blp_pin_name.h"
#include "rtl8195blp_irq.h"
#include "rtl8195blp_syson_ctrl.h"
#include "rtl8195blp_gdma.h"
#include "rtl8195blp_timer.h"
#include "rtl8195blp_lpi.h"
#include "rtl8195blp_misc.h"
#include "rtl8195blp_pinmux.h"
#include "rtl8195blp_uart.h"
#include "rtl8195blp_pwm.h"
#include "rtl8195blp_cir.h"
#include "rtl8195blp_icc.h"
#include "rtl8195blp_qdec.h"
#include "rtl8195blp_gpio.h"
#include "rtl8195blp_flash.h"
#include "rtl8195blp_spic.h"
#include "rtl8195blp_adc.h"
#include "rtl8195blp_comp.h"
#include "rtl8195blp_sgpio.h"
#include "rtl8195blp_i2c.h"
#include "rtl8195blp_efuse.h"
#include "rtl8195blp_rtc.h"
#include "rtl8195blp_chg.h"

#if CONFIG_CMSIS_RTX_EN
#include "cmsis_os.h"               // CMSIS RTOS header file
#endif

#endif
