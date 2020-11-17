/**************************************************************************//**
 * @file     section_config.c
 * @brief    Defines section name for code text or data for we can locate
 *           them to a specific address.
 *
 * @version  V1.00
 * @date     2020-02-03
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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

#ifndef _SECTION_CONFIG_H_
#define _SECTION_CONFIG_H_

#include "basic_types.h"

#define INFRA_ROM_TEXT_SECTION                  SECTION(".infra.rom.text")

#define START_RAM_FUN_A_SECTION                 SECTION(".start.ram.data.a")
#define START_RAM_DATA_SECTION                  SECTION(".data.start.ram")
#define START_RAM_SIGNATURE_SECTION             SECTION(".start.ram.sign")
#define SECTION_SYS_BSS                         SECTION(".sys.bss")

// Temp buffer for ROM code
#define SECTION_ROM_TEMP_BSS                    SECTION(".rom_temp.bss")

#endif //_SECTION_CONFIG_H_

