/**************************************************************************//**
 * @file      rtl8195bhp_si_type.h
 * @brief
 * @version   V1.00
 * @date      2017-11-1 10:11:11
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

#ifndef _RTL8195BHP_SI_TYPE_H_
#define _RTL8195BHP_SI_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_AUDIO_REG_TYPE

/**
 * @addtogroup hs_hal_audio_reg SI Registers.
 * @ingroup hs_hal_audio
 * @{
 */

/**
  \brief Union type to access si_ctrl (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) SI Control Register                                        */
  
  struct {
    __IOM uint32_t si_wr_start : 1;           /*!< [0..0] Si starts to write the register.                                   */
    __IM  uint32_t            : 3;
    __IOM uint32_t si_read_start : 1;         /*!< [4..4] Si starts to read the register.                                    */
    __IM  uint32_t            : 2;
    __IOM uint32_t si_disable : 1;            /*!< [7..7] SI disable control                                                 */
    __IOM uint32_t si_address : 8;            /*!< [15..8] The address of codec                                              */
    __IOM uint32_t si_data    : 16;           /*!< [31..16] si data                                                          */
  } b;                                        /*!< bit fields for si_ctrl */
} si_ctrl_t, *psi_ctrl_t;

/**
  \brief Union type to access si_clk_ctrl (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) SI Clock Control Register                                  */
  
  struct {
    __IOM uint32_t reg_dk_en  : 1;            /*!< [0..0] Gate SI clock                                                      */
  } b;                                        /*!< bit fields for si_clk_ctrl */
} si_clk_ctrl_t, *psi_clk_ctrl_t;

/** @} */ /* End of group hs_hal_audio_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_AUDIO_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_SI_TYPE_H_

