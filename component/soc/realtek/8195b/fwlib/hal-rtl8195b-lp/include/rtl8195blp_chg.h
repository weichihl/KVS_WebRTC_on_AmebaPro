 /**************************************************************************//**
  * @file     rtl8195blp_chg.h
  * @brief    The HAL related definition and macros for the CHG device.
  *           Includes Registers and data type definition.
  * @version  V1.00
  * @date     2017-07-12
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

#ifndef _RTL8195BLP_CHG_H_
#define _RTL8195BLP_CHG_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup ls_hal_chg CHG
 * @{
 */

/**
  * \brief The charger (CHG) Efuse parameter
**/
#define EFuseChgReg0   (0x1E0)  //!< Define EFuseChgReg0 index
#define EFuseChgReg1   (0x1E1)  //!< Define EFuseChgReg1 index
#define EFuseChgReg2   (0x1E2)  //!< Define EFuseChgReg2 index
#define EFuseChgReg3   (0x1E3)  //!< Define EFuseChgReg3 index


/**
  * \brief The charger (CHG) parameter
**/

enum  chg_para_e {
    T_Bat_Max     = 45,     //!< T_Bat_Max, Uint: C
    T_Bat_Normal  = 35,     //!< T_Bat_Normal, Uint: C
    V_Bat_Max     = 4300,   //!< V_Bat_Max, Uint:mV
    V_Bat_Min     = 2600,   //!< V_Bat_Min, Uint:mV
    V_Bat_Normal  = 4000,   //!< V_Bat_Normal, Uint:mV
    V_Bat_Pre     = 3000,   //!< V_Bat_Pre, Uint:mV
    Vbat_Ftune    = 16,     //!< Vbat_Ftune, Uint:10mV
    CV_MAX        = 4200,   //!< CV_MAX, Uint:mV
    CV_MIN        = 3500    //!< CV_MIN, Uint:mV
};
typedef uint16_t chg_para_sel_t;


/**
  * \brief The data structure to record charger (CHG) parameter.
**/

typedef struct hal_chg_adapter_s {
    hal_adc_adapter_t *phal_adc_adapter; //!< The data structure to control the ADC register.
    u16 cc; //!< The cc value
    u16 cv; //!< The cv value
    u16 ichg_ct;    //!< The ichg_ct value
    u16 ichg_ft;    //!< The ichg_ft value
    u16 vbat_ct;    //!< The vbat_ct value
    u16 vbat_ft;    //!< The vbat_ft value
    u16 tbat_0;     //!< The Battery at 0 degree value
    u16 tbat_10;    //!< The Battery at 10 degree value
    u16 tbat_35;    //!< The Battery at 35 degree value
    u16 tbat_45;    //!< The Battery at 45 degree value
    u32 chg_state;  //!< The chg state parameter
    u16 chg_vbat;   //!< The Battery Voltage
    u16 chg_ibat;   //!< The Battery Current
    u16 chg_vadp;   //!< The Adapter Voltage
    u16 chg_tbat;   //!< The Battery Temperature
    u16 i_kp;       //!< The i_kp parameter
    u16 v_kp;       //!< The v_kp parameter
} hal_chg_adapter_t, *phal_chg_adapter_t;


/**
  \brief  The data structure of the stubs function for the CHG HAL functions in ROM
*/
typedef struct hal_chg_func_stubs_s {
    phal_chg_adapter_t *pchg_adp;
    int (*hal_charger_init) (hal_chg_adapter_t *pchg_adp, uint32_t cc, uint32_t cv);
    void (*hal_charger_state) (hal_chg_adapter_t *pchg_adp, u16 tbat_45, u16 tbat_0, u8 temp_adc_ch);
    void (*hal_charger_state_no_adc) (hal_chg_adapter_t *pchg_adp, u16 cc, u16 cv, hal_adc_adapter_t *padc_adp);
    int (*hal_charger_cccv_cal) (uint32_t real_cc, uint32_t real_cv, uint32_t tar_cc, uint32_t tar_cv);
    uint32_t reserved[4];  // reserved space for next ROM code version function table extending.
}hal_chg_func_stubs_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup ls_hal_chg_rom_func CHG HAL ROM APIs.
 * @{
 */
int hal_charger_init_rtl8195blp(hal_chg_adapter_t *pchg_adp, uint32_t cc, uint32_t cv);
void hal_charger_state_rtl8195blp(hal_chg_adapter_t *pchg_adp, u16 tbat_45, u16 tbat_0, u8 temp_adc_ch);
void hal_charger_state_no_adc_rtl8195blp(hal_chg_adapter_t *pchg_adp, u16 cc, u16 cv, hal_adc_adapter_t *padc_adp);
int hal_charger_cccv_cal_rtl8195blp(uint32_t real_cc, uint32_t real_cv, uint32_t tar_cc, uint32_t tar_cv);

/** @} */ /* End of group ls_hal_chg_rom_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group ls_hal_chg */

#endif  // end of "#define _RTL8195BLP_CHG_H_"
