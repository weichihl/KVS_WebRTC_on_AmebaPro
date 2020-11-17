/**************************************************************************//**
* @file         hal_psram.h
* @brief       The HAL API implementation for the PSRAM
*
* @version    V1.00
* @date        2017-05-15
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


#ifndef _HAL_PSRAM_H_
#define _HAL_PSRAM_H_

#include "cmsis.h"

#ifdef  __cplusplus
  extern "C"
  {
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_PSRAM_CTRL_REG_TYPE

/**
 * @addtogroup hs_hal_psram PSRAM
 * @{
 */
void dpin_function(uint8_t option);

void hal_psram_cg(void);
void hal_psram_resume_from_cg(void);
void hal_psram_pg(void);
void hal_psram_resume_from_pg(void);
void hal_psram_init (void);

/** @} */ /* End of group hs_hal_psram */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_PSRAM_CTRL_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif //#ifndef _HAL_PSRAM_H_

