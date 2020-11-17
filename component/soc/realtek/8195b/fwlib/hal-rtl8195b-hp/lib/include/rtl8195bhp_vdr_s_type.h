/**************************************************************************//**
 * @file      rtl8195bhp_vdr_s_type.h
 * @brief
 * @version   V1.00
 * @date      2017-11-1 11:58:11
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

#ifndef _RTL8195BHP_VENDOR_S_VDR_S_TYPE_H_
#define _RTL8195BHP_VENDOR_S_VDR_S_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_VDR_S_REG_TYPE

/**
 * @addtogroup hs_hal_vdr_s_reg VDR_S Registers.
 * @ingroup hs_hal_vdr
 * @{
 */

/**
  \brief Union type to access vdr_s_gdma0_isr (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) Secure GDMA0 ISR Register                                  */
  
  struct {
    __IM  uint32_t gdma0_ch0_isr : 1;         /*!< [0..0] GDMA 0 ISR for Channel 0                                           */
    __IM  uint32_t gdma0_ch1_isr : 1;         /*!< [1..1] GDMA 0 ISR for Channel 1                                           */
    __IM  uint32_t gdma0_ch2_isr : 1;         /*!< [2..2] GDMA 0 ISR for Channel 2                                           */
    __IM  uint32_t gdma0_ch3_isr : 1;         /*!< [3..3] GDMA 0 ISR for Channel 3                                           */
    __IM  uint32_t gdma0_ch4_isr : 1;         /*!< [4..4] GDMA 0 ISR for Channel 4                                           */
    __IM  uint32_t gdma0_ch5_isr : 1;         /*!< [5..5] GDMA 0 ISR for Channel 5                                           */
  } b;                                        /*!< bit fields for vdr_s_gdma0_isr */
} vdr_s_gdma0_isr_t, *pvdr_s_gdma0_isr_t;

/**
  \brief Union type to access vdr_s_gdma1_isr (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) Secure GDMA1 ISR Register                                  */
  
  struct {
    __IM  uint32_t gdma1_ch0_isr : 1;         /*!< [0..0] GDMA 1 ISR for Channel 0                                           */
    __IM  uint32_t gdma1_ch1_isr : 1;         /*!< [1..1] GDMA 1 ISR for Channel 1                                           */
    __IM  uint32_t gdma1_ch2_isr : 1;         /*!< [2..2] GDMA 1 ISR for Channel 2                                           */
    __IM  uint32_t gdma1_ch3_isr : 1;         /*!< [3..3] GDMA 1 ISR for Channel 3                                           */
    __IM  uint32_t gdma1_ch4_isr : 1;         /*!< [4..4] GDMA 1 ISR for Channel 4                                           */
    __IM  uint32_t gdma1_ch5_isr : 1;         /*!< [5..5] GDMA 1 ISR for Channel 5                                           */
  } b;                                        /*!< bit fields for vdr_s_gdma1_isr */
} vdr_s_gdma1_isr_t, *pvdr_s_gdma1_isr_t;

/**
  \brief Union type to access vdr_s_low_pri_int_mod (@ 0x00000070).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000070) Secure Region Low Priority Interrupt Mode Control
                                                                  Register                                                   */
  
  struct {
    __IOM uint32_t low_pri_int_mode : 32;     /*!< [31..0] Each bit control corresponding interrupt mode. 1: Rising
                                                   edge trigger 0: High level active                                         */
  } b;                                        /*!< bit fields for vdr_s_low_pri_int_mod */
} vdr_s_low_pri_int_mod_t, *pvdr_s_low_pri_int_mod_t;

/**
  \brief Union type to access vdr_s_low_pri_int_imr (@ 0x00000074).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000074) Secure Region Low Priority Interrupt Mask Register         */
  
  struct {
    __IOM uint32_t rxi300_int_imr : 1;        /*!< [0..0] 1: Enable 0: Disable                                               */
  } b;                                        /*!< bit fields for vdr_s_low_pri_int_imr */
} vdr_s_low_pri_int_imr_t, *pvdr_s_low_pri_int_imr_t;

/**
  \brief Union type to access vdr_s_low_pri_int_isr (@ 0x00000078).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000078) Secure Region Low Priority Interrupt Status Register       */
  
  struct {
    __IOM uint32_t rxi300_secure_bus_isr : 1; /*!< [0..0] RXI secure bus interrupt pending status                            */
  } b;                                        /*!< bit fields for vdr_s_low_pri_int_isr */
} vdr_s_low_pri_int_isr_t, *pvdr_s_low_pri_int_isr_t;

/**
  \brief Union type to access vdr_s_sup_sec_ef_ctrl (@ 0x00000080).
*/
typedef union {
  __OM  uint32_t w;                           /*!< (@ 0x00000080) Super Secure eFuse Control Register                        */
  
  struct {
    __OM  uint32_t sec_super_sec_ef_lock : 1; /*!< [0..0] When this bit is written to '1', this bit can not be
                                                   written to 0. Beside the high speed platform is reset.
                                                   1: Super secure zone can not be accessed. 0: Super secure
                                                   zone just can be accessed by secure state. (AXI_PORT[1]
                                                   = 0)                                                                      */
  } b;                                        /*!< bit fields for vdr_s_sup_sec_ef_ctrl */
} vdr_s_sup_sec_ef_ctrl_t, *pvdr_s_sup_sec_ef_ctrl_t;

/** @} */ /* End of group hs_hal_vdr_s_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_VDR_S_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_VENDOR_S_VDR_S_TYPE_H_

