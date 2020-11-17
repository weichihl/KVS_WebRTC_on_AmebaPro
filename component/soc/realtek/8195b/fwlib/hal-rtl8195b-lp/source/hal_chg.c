/**************************************************************************//**
 * @file     hal_chg.c
 * @brief    This CHG HAL API functions.
 *
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

#include "hal_chg.h"

#if CONFIG_CHG_EN //CONFIG_CHG_EN

#if (CHIP_VER == CHIP_B_CUT) && (defined(CONFIG_BUILD_RAM))
int hal_charger_init_rtl8195blp_patch(hal_chg_adapter_t *pchg_adp, uint32_t cc, uint32_t cv);
void hal_charger_state_rtl8195blp_patch(hal_chg_adapter_t *pchg_adp, u16 tbat_45, u16 tbat_0, u8 temp_adc_ch);
void hal_charger_state_no_adc_rtl8195blp_patch(hal_chg_adapter_t *pchg_adp, u16 cc, u16 cv, hal_adc_adapter_t *padc_adp);
int hal_charger_cccv_cal_rtl8195blp_patch(uint32_t real_cc, uint32_t real_cv, uint32_t tar_cc, uint32_t tar_cv);
#endif

/**
 * @addtogroup ls_hal_chg CHG
 * @{
 */

/**
 *  @brief To Initialize charger cc and cv parameter.
 *
 *  @param[in] pchg_adp The CHG devices adapter.
 *  @param[in] cc is charger Iout Target.
 *  @param[in] cv is charger Vout Target.
 *
 *  @returns     HAL_OK:  Initial succeed.
 *  @returns     HAL_ERR_PARA:  Input arguments are invalid.
 */
int hal_charger_init (hal_chg_adapter_t *pchg_adp, uint32_t cc, uint32_t cv)
{
    return hal_chg_stubs.hal_charger_init (pchg_adp, cc, cv);
}

/**
 *  @brief To Start Charger State Machine.
 *
 *  @param[in] pchg_adp The CHG devices adapter.
 *  @param[in] tbat_45 The Battery temp at 45 degree voltage(mV).
 *  @param[in] tbat_0 The Battery temp at 0 degree voltage(mV).
 *  @param[in] temp_adc_ch The ADC channel of Battery temp..
 *
 *  @returns void
 */
void hal_charger_state (hal_chg_adapter_t *pchg_adp, u16 tbat_45, u16 tbat_0, u8 temp_adc_ch)
{
    #if (CHIP_VER == CHIP_B_CUT) && (defined(CONFIG_BUILD_RAM))
        hal_charger_state_rtl8195blp_patch(pchg_adp, tbat_45, tbat_0, temp_adc_ch);
    #else
        hal_chg_stubs.hal_charger_state (pchg_adp, tbat_45, tbat_0, temp_adc_ch);
    #endif
}

/** 
 *  @brief To Start Charger State Machine without use external ADC.
 *
 *  \param[in] pchg_adp The CHG devices adapter.
 *  \param[in] cc The Constant Current value, Uint:mA.
 *  \param[in] cv The Constant Voltage value, Uint:mV.
 *  \param[in] padc_adp The ADC devices adapter.
 *
 *  \returns void
 */
void hal_charger_state_no_adc (hal_chg_adapter_t *pchg_adp, u16 cc, u16 cv, hal_adc_adapter_t *padc_adp)
{
    #if (CHIP_VER == CHIP_B_CUT) && (defined(CONFIG_BUILD_RAM))
        hal_charger_state_no_adc_rtl8195blp_patch(pchg_adp, cc, cv, padc_adp);
    #else
        hal_chg_stubs.hal_charger_state_no_adc (pchg_adp, cc, cv, padc_adp);
    #endif
}

/** 
 *  \brief To Initialize charger cc and cv parameter.
 *
 *  \param[in] pchg_adp The CHG devices adapter.
 *  \param[in] real_cc The real charger Iout, uint:mA
 *  \param[in] real_cv The real charger Vout, uint:mV
 *  \param[in] tar_cc  The charger Iout Target, uint:mA
 *  \param[in] tar_cv  The charger Vout Target, uint:mV
 *
 *  \returns     HAL_OK:  Write succeed.
 *  \returns     HAL_ERR_PARA:  Write Fail
 */
int hal_charger_cccv_cal(uint32_t real_cc, uint32_t real_cv, uint32_t tar_cc, uint32_t tar_cv)
{
    #if (CHIP_VER == CHIP_B_CUT) && (defined(CONFIG_BUILD_RAM))
        return hal_charger_cccv_cal_rtl8195blp_patch(real_cc, real_cv, tar_cc, tar_cv);
    #else
        return hal_chg_stubs.hal_charger_cccv_cal (real_cc, real_cv, tar_cc, tar_cv);
    #endif
}
/** @} */ /* End of group ls_hal_chg */

#endif  // end of "#if CONFIG_CHG_EN"

