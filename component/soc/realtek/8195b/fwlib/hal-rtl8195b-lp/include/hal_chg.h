/**************************************************************************//**
 * @file     hal_chg.h
 * @brief    The HAL API implementation for the CHG device.
 * @version  V1.00
 * @date     2017-07-15
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

#ifndef _HAL_CHG_H_
#define _HAL_CHG_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup ls_hal_chg CHG
 * @ingroup 8195bl_hal
 * @{
 * @brief The CHG HAL module of the LS platform.
 */

/**
  * @brief The stubs functions table to exports CHG HAL functions in ROM.
  */

extern const hal_chg_func_stubs_t hal_chg_stubs;

int hal_charger_init (hal_chg_adapter_t *pchg_adp, uint32_t cc, uint32_t cv);
void hal_charger_state (hal_chg_adapter_t *pchg_adp, u16 tbat_45, u16 tbat_0, u8 temp_adc_ch);
void hal_charger_state_no_adc(hal_chg_adapter_t *pchg_adp, u16 cc, u16 cv, hal_adc_adapter_t *padc_adp);
int hal_charger_cccv_cal(uint32_t real_cc, uint32_t real_cv, uint32_t tar_cc, uint32_t tar_cv);

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group ls_hal_chg */

#endif  // end of "#define _HAL_CHG_H_"
