/**************************************************************************//**
 * @file     efuse_api.c
 * @brief    This file implements the EFUSE Mbed HAL API functions.
 * 
 * @version  V1.00
 * @date     2018-05-02
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
#include "hal_efuse.h"
#include "efuse_api.h"

#if CONFIG_EFUSE_EN

int efuse_disable_lp_jtag(void)
{
    hal_efuse_disable_lp_jtag();
    return 0;
}

int efuse_disable_sec_jtag(void)
{
    hal_efuse_disable_sec_jtag();
    return 0;
}

int efuse_disable_nonsec_jtag(void)
{
    hal_efuse_disable_nonsec_jtag();
    return 0;
}

#endif // #if CONFIG_EFUSE_EN 

