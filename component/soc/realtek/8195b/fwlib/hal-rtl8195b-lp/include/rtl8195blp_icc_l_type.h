/**************************************************************************//**
 * @file      rtl8195blp_icc_l_type.h
 * @brief
 * @version   V1.00
 * @date      2017-11-1 14:39:56
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

#ifndef _RTL8195BLP_ICC_L_TYPE_H_
#define _RTL8195BLP_ICC_L_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_ICC_L_REG_TYPE

/**
 * @addtogroup ls_hal_icc_l_reg ICC_L Registers.
 * @ingroup ls_hal_icc
 * @{
 */

/**
  \brief Union type to access icc_l_hptgie (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) HP Toggle Interrupt Enable Register                        */
  
  struct {
    __IOM uint32_t hptgie0    : 1;            /*!< [0..0] This bit is used to control the enable of the interrupt
                                                   triggered by the HPTG0 toggles. 0/1: Disable / Enable Interrupt           */
    __IOM uint32_t hptgie1    : 1;            /*!< [1..1] This bit is used to control the enable of the interrupt
                                                   triggered by the HPTG1 toggles. 0/1: Disable / Enable Interrupt           */
    __IOM uint32_t hptgie2    : 1;            /*!< [2..2] This bit is used to control the enable of the interrupt
                                                   triggered by the HPTG2 toggles. 0/1: Disable / Enable Interrupt           */
    __IOM uint32_t hptgie3    : 1;            /*!< [3..3] This bit is used to control the enable of the interrupt
                                                   triggered by the HPTG3 toggles. 0/1: Disable / Enable Interrupt           */
    __IOM uint32_t hptgie4    : 1;            /*!< [4..4] This bit is used to control the enable of the interrupt
                                                   triggered by the HPTG4 toggles. 0/1: Disable / Enable Interrupt           */
    __IOM uint32_t hptgie5    : 1;            /*!< [5..5] This bit is used to control the enable of the interrupt
                                                   triggered by the HPTG5 toggles. 0/1: Disable / Enable Interrupt           */
    __IOM uint32_t hptgie6    : 1;            /*!< [6..6] This bit is used to control the enable of the interrupt
                                                   triggered by the HPTG6 toggles. 0/1: Disable / Enable Interrupt           */
    __IOM uint32_t hptgie7    : 1;            /*!< [7..7] This bit is used to control the enable of the interrupt
                                                   triggered by the HPTG7 toggles. 0/1: Disable / Enable Interrupt           */
    __IM  uint32_t            : 8;
    __IOM uint32_t h2ltgie0   : 1;            /*!< [16..16] This bit is used to control the enable of the interrupt
                                                   triggered by the H2LTG0 toggles. 0/1: Disable / Enable
                                                   Interrupt                                                                 */
    __IOM uint32_t h2ltgie1   : 1;            /*!< [17..17] This bit is used to control the enable of the interrupt
                                                   triggered by the H2LTG1 toggles. 0/1: Disable / Enable
                                                   Interrupt                                                                 */
    __IOM uint32_t h2ltgie2   : 1;            /*!< [18..18] This bit is used to control the enable of the interrupt
                                                   triggered by the H2LTG2 toggles. 0/1: Disable / Enable
                                                   Interrupt                                                                 */
    __IOM uint32_t h2ltgie3   : 1;            /*!< [19..19] This bit is used to control the enable of the interrupt
                                                   triggered by the H2LTG3 toggles. 0/1: Disable / Enable
                                                   Interrupt                                                                 */
    __IOM uint32_t h2ltgies   : 1;            /*!< [20..20] This bit is used to control the enable of the interrupt
                                                   triggered by the H2LTGS toggles. 0/1: Disable/Enable Interrupt            */
  } b;                                        /*!< bit fields for icc_l_hptgie */
} icc_l_hptgie_t, *picc_l_hptgie_t;

/**
  \brief Union type to access icc_l_hptgis (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) HP Toggle Interrupt Status Register                        */
  
  struct {
    __IOM uint32_t hptgis0    : 1;            /*!< [0..0] This bit is used to show the interrupt status which is
                                                   triggered by the HPTG0 toggles. This usually means the
                                                   HP CPU has updated the register HWLR0. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t hptgis1    : 1;            /*!< [1..1] This bit is used to show the interrupt status which is
                                                   triggered by the HPTG1 toggles. This usually means the
                                                   HP CPU has updated the register HWLR1. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t hptgis2    : 1;            /*!< [2..2] This bit is used to show the interrupt status which is
                                                   triggered by the HPTG2 toggles. This usually means the
                                                   HP CPU has updated the register HWLR2. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t hptgis3    : 1;            /*!< [3..3] This bit is used to show the interrupt status which is
                                                   triggered by the HPTG3 toggles. This usually means the
                                                   HP CPU has updated the register HWLR3. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t hptgis4    : 1;            /*!< [4..4] This bit is used to show the interrupt status which is
                                                   triggered by the HPTG4 toggles. This usually means the
                                                   HP CPU has updated the register HWLR4. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t hptgis5    : 1;            /*!< [5..5] This bit is used to show the interrupt status which is
                                                   triggered by the HPTG5 toggles. This usually means the
                                                   HP CPU has updated the register HWLR5. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t hptgis6    : 1;            /*!< [6..6] This bit is used to show the interrupt status which is
                                                   triggered by the HPTG6 toggles. This usually means the
                                                   HP CPU has updated the register HWLR6. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t hptgis7    : 1;            /*!< [7..7] This bit is used to show the interrupt status which is
                                                   triggered by the HPTG7 toggles. This usually means the
                                                   HP CPU has updated the register HWLR7. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IM  uint32_t            : 8;
    __IOM uint32_t h2ltgis0   : 1;            /*!< [16..16] This bit is used to show the interrupt status which
                                                   is triggered by the H2LTG0 toggles. This usually means
                                                   the HP CPU has updated the register HLRW0. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t h2ltgis1   : 1;            /*!< [17..17] This bit is used to show the interrupt status which
                                                   is triggered by the H2LTG1 toggles. This usually means
                                                   the HP CPU has updated the register HLRW1. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t h2ltgis2   : 1;            /*!< [18..18] This bit is used to show the interrupt status which
                                                   is triggered by the H2LTG2 toggles. This usually means
                                                   the HP CPU has updated the register HLRW2. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t h2ltgis3   : 1;            /*!< [19..19] This bit is used to show the interrupt status which
                                                   is triggered by the H2LTG3 toggles. This usually means
                                                   the HP CPU has updated the register HLRW3. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
    __IOM uint32_t h2ltgiss   : 1;            /*!< [20..20] This bit is used to show the interrupt status which
                                                   is triggered by the H2LTGS toggles. This usually means
                                                   the HP CPU has updated the register REG_SEMA. 0: No interrupt;
                                                   1: Interrupt is pending. Write 1 to clear.                                */
  } b;                                        /*!< bit fields for icc_l_hptgis */
} icc_l_hptgis_t, *picc_l_hptgis_t;

/** @} */ /* End of group ls_hal_icc_l_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_ICC_L_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BLP_ICC_L_TYPE_H_

