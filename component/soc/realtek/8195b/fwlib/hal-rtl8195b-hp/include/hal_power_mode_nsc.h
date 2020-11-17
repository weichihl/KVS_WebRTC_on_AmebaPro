/**************************************************************************//**
* @file         hal_power_mode_nsc.h
* @brief       The HAL API implementation for the POWER MODE
*
* @version    V1.00
* @date        2018-06-29
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



#ifndef _HAL_POWER_MODE_NSC_H_
#define _HAL_POWER_MODE_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */

#ifdef  __cplusplus
 extern "C"
 {
#endif

#if defined(CONFIG_BUILD_SECURE)

/**
 * @defgroup hs_hal_power_mode_nsc_api POWER MODE HAL NSC APIs.
 * @ingroup hs_hal_power_mode
 * @{
 */
void NS_ENTRY slp_hs_cg_cmd_handler_nsc (uint32_t cmd, uint32_t op, uint32_t arg);
void NS_ENTRY slp_hs_pd_cmd_handler_nsc (uint32_t cmd, uint32_t op, uint32_t arg);
void NS_ENTRY hal_SleepCG_nsc (u16 Option, u32 SDuration, u8 Clock, u8 GpioOption);
void NS_ENTRY hal_SleepPG_nsc (u16 Option, u32 SDuration, u8 Memsel, u8 GpioOption);
void NS_ENTRY hal_Boost_nsc (u8 Option);
/** @} */ /* End of group hs_hal_power_mode_nsc_api */

#endif // end of "#if defined(CONFIG_BUILD_SECURE)"


#if defined(CONFIG_BUILD_NONSECURE)
void slp_hs_cg_cmd_handler_nsc (uint32_t cmd, uint32_t op, uint32_t arg);
void slp_hs_pd_cmd_handler_nsc (uint32_t cmd, uint32_t op, uint32_t arg);
void hal_SleepCG_nsc (u16 Option, u32 SDuration, u8 Clock, u8 GpioOption);
void hal_SleepPG_nsc (u16 Option, u32 SDuration, u8 Memsel, u8 GpioOption);
void hal_Boost_nsc (u8 Option);

#define slp_hs_cg_cmd_handler       slp_hs_cg_cmd_handler_nsc
#define slp_hs_pd_cmd_handler       slp_hs_pd_cmd_handler_nsc
#define hal_SleepCG                 hal_SleepCG_nsc
#define hal_SleepPG                 hal_SleepPG_nsc
#define hal_Boost                   hal_Boost_nsc
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

#ifdef  __cplusplus
 }
#endif


#endif  // end of "#define _HAL_POWER_MODE_NSC_H_"


