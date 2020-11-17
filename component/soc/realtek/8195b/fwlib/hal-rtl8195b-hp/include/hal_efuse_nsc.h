/**************************************************************************//**
* @file         hal_efuse_nsc.h
* @brief       The HAL API implementation for the EFUSE
*
* @version    V1.00
* @date        2017-02-13
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



#ifndef _HAL_EFUSE_NSC_H_
#define _HAL_EFUSE_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */

#ifdef  __cplusplus
 extern "C"
 {
#endif

#if defined(CONFIG_BUILD_SECURE)

/**
 * @defgroup hs_hal_efuse_nsc_api EFUSE HAL NSC APIs.
 * @ingroup hs_hal_efuse
 * @{
 */
void NS_ENTRY hal_efuse_set_cell_sel_nsc (efuse_size_t efuse_size);
uint32_t NS_ENTRY hal_efuse_autoload_en_nsc(uint8_t enable);
uint32_t NS_ENTRY hal_efuse_read_nsc (uint32_t ctrl_setting, uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage);
uint32_t NS_ENTRY hal_efuse_write_nsc (uint32_t ctrl_setting, uint16_t   addr, uint8_t data, uint8_t l25out_voltage);
uint32_t NS_ENTRY hal_efuse_hci_autoload_en_nsc (uint8_t enable);
uint32_t NS_ENTRY hal_user_otp_get_nsc (uint8_t *puser_otp);
void NS_ENTRY hal_user_otp_set_nsc (uint8_t *puser_otp);

/** @} */ /* End of group hs_hal_efuse_nsc_api */

#endif // end of "#if defined(CONFIG_BUILD_SECURE)"


#if defined(CONFIG_BUILD_NONSECURE)
void hal_efuse_set_cell_sel_nsc (efuse_size_t efuse_size);
uint32_t hal_efuse_autoload_en_nsc (uint8_t enable);
uint32_t hal_efuse_read_nsc (uint32_t ctrl_setting, uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage);
uint32_t hal_efuse_write_nsc (uint32_t ctrl_setting, uint16_t   addr, uint8_t data, uint8_t l25out_voltage);
uint32_t hal_efuse_hci_autoload_en_nsc (uint8_t enable);
uint32_t hal_user_otp_get_nsc (uint8_t *puser_otp);
void hal_user_otp_set_nsc (uint8_t *puser_otp);

#define hal_efuse_set_cell_sel              hal_efuse_set_cell_sel_nsc
#define hal_efuse_autoload_en               hal_efuse_autoload_en_nsc
#define hal_efuse_read                      hal_efuse_read_nsc
#define hal_efuse_write                     hal_efuse_write_nsc
#define hal_efuse_hci_autoload_en           hal_efuse_hci_autoload_en_nsc
#define hal_user_otp_get                    hal_user_otp_get_nsc
#define hal_user_otp_set                    hal_user_otp_set_nsc
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

#ifdef  __cplusplus
 }
#endif


#endif  // end of "#define _HAL_EFUSE_NSC_H_"


