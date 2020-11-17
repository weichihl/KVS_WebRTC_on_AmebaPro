 /**************************************************************************//**
  * @file     chg_api.c
  * @brief    This file implements the mbed HAL API for CHG function.
  *
  * @version  V1.00
  * @date     2018-06-06
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

#include "objects.h"
#include "hal_chg.h"
#include "chg_api.h"
hal_adc_adapter_t adc_adp;

/**
  * @brief  Initializes the CHG registers with default parameters and run CHG state machine.
  * @param  obj: CHG object define in application software.
  * @param  cc: The Constant Current value, Uint:mA.
  * @param  cv: The Constant Voltage value, Uint:mV.
  * @retval none
  */
void charger_sm(chg_t *obj, u16 cc, u16 cv)
{
    u32 chg_exist =0;
    static u8 adc_int=0;
    if (adc_int == 0) {
        hal_adc_load_default(&adc_adp);
        hal_adc_init(&adc_adp);
        adc_int = 1;
    }
    // Read CHG_EXIST
    chg_exist = (HAL_READ32(0xA0000200, 0x1f0) & 0x40000000); // A00003F0[30]: 1: CHG_EXIST
    hal_charger_state_no_adc(&obj->chg_adapter, cc, cv, &adc_adp);
}

