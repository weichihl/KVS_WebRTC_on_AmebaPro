/**************************************************************************//**
* @file         hal_efuse.h
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



#ifndef _HAL_EFUSE_H_
#define _HAL_EFUSE_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup ls_hal_efuse EFUSE
 * @{
 */
#define EFUSE_CTRL_SETTING          0x50300000

void hal_efuse_set_cell_sel (efuse_size_t efuse_size);
uint32_t hal_efuse_autoload_en (uint8_t enable);
uint32_t hal_efuse_read (uint32_t ctrl_setting,	uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage);
uint32_t hal_efuse_write (uint32_t ctrl_setting, uint16_t	addr, uint8_t data, uint8_t l25out_voltage);
uint32_t hal_efuse_hs_autoload_en (uint8_t enable);
uint32_t hal_efuse_read_logical (uint32_t ctrl_setting,	uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage);
uint32_t hal_efuse_write_logical (uint32_t ctrl_setting, uint16_t addr, uint8_t data, uint8_t l25out_voltage);
void hal_efuse_disable_lp_jtag (void);
void hal_efuse_disable_sec_jtag (void);
void hal_efuse_disable_nonsec_jtag (void);

/** @} */ /* End of group ls_hal_efuse */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_EFUSE_H_"


