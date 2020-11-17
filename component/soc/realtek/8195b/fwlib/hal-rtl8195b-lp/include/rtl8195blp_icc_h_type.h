/**************************************************************************//**
 * @file      rtl8195blp_icc_h_type.h
 * @brief
 * @version   V1.00
 * @date      2019-7-16 15:50:32
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

#ifndef _RTL8195BLP_ICC_H_TYPE_H_
#define _RTL8195BLP_ICC_H_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_ICC_H_REG_TYPE

/**
 * @addtogroup ls_hal_icc_h_reg ICC_H Registers.
 * @ingroup ls_hal_icc
 * @{
 */

/**
  \brief Union type to access icc_h_hrlw0 (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) HP Read LP Write Register 0                                */
  
  struct {
    __IOM uint32_t hrlw       : 32;           /*!< [31..0] The information maintained by LP CPU. It could be message
                                                   queue information: write pointer Q_L2H or the read pointer
                                                   of Q_H2L.                                                                 */
  } b;                                        /*!< bit fields for icc_h_hrlw0 */
} icc_h_hrlw0_t, *picc_h_hrlw0_t;

/**
  \brief Union type to access icc_h_hrlw1 (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) HP Read LP Write Register 1                                */
  
  struct {
    __IOM uint32_t hrlw       : 32;           /*!< [31..0] The information maintained by LP CPU. It could be message
                                                   queue information: write pointer Q_L2H or the read pointer
                                                   of Q_H2L.                                                                 */
  } b;                                        /*!< bit fields for icc_h_hrlw1 */
} icc_h_hrlw1_t, *picc_h_hrlw1_t;

/**
  \brief Union type to access icc_h_hrlw2 (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) HP Read LP Write Register 2                                */
  
  struct {
    __IOM uint32_t hrlw       : 32;           /*!< [31..0] The information maintained by LP CPU. It could be message
                                                   queue information: write pointer Q_L2H or the read pointer
                                                   of Q_H2L.                                                                 */
  } b;                                        /*!< bit fields for icc_h_hrlw2 */
} icc_h_hrlw2_t, *picc_h_hrlw2_t;

/**
  \brief Union type to access icc_h_hrlw3 (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) HP Read LP Write Register 3                                */
  
  struct {
    __IOM uint32_t hrlw       : 32;           /*!< [31..0] The information maintained by LP CPU. It could be message
                                                   queue information: write pointer Q_L2H or the read pointer
                                                   of Q_H2L.                                                                 */
  } b;                                        /*!< bit fields for icc_h_hrlw3 */
} icc_h_hrlw3_t, *picc_h_hrlw3_t;

/**
  \brief Union type to access icc_h_lptg (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) LP Toggle Register                                         */
  
  struct {
    __IOM uint32_t lptg0      : 1;            /*!< [0..0] It's a 1 bit sequence number for HRLW0 register updating.
                                                   Toggle this bit will assert the corresponding interrupt
                                                   on the HP CPU.                                                            */
    __IOM uint32_t lptg1      : 1;            /*!< [1..1] It's a 1 bit sequence number for HRLW1 register updating.
                                                   Toggle this bit will assert the corresponding interrupt
                                                   on the HP CPU.                                                            */
    __IOM uint32_t lptg2      : 1;            /*!< [2..2] It's a 1 bit sequence number for HRLW2 register updating.
                                                   Toggle this bit will assert the corresponding interrupt
                                                   on the HP CPU.                                                            */
    __IOM uint32_t lptg3      : 1;            /*!< [3..3] It's a 1 bit sequence number for HRLW3 register updating.
                                                   Toggle this bit will assert the corresponding interrupt
                                                   on the HP CPU.                                                            */
    __IM  uint32_t            : 12;
    __IOM uint32_t l2htg0     : 1;            /*!< [16..16] The toggle bit for HLRW0 register updating.                      */
    __IOM uint32_t l2htg1     : 1;            /*!< [17..17] The toggle bit for HLRW1 register updating.                      */
    __IOM uint32_t l2htg2     : 1;            /*!< [18..18] The toggle bit for HLRW2 register updating.                      */
    __IOM uint32_t l2htg3     : 1;            /*!< [19..19] The toggle bit for HLRW3 register updating.                      */
    __IOM uint32_t l2htgs     : 1;            /*!< [20..20] The toggle bit for REG_SEMA register updating.                   */
  } b;                                        /*!< bit fields for icc_h_lptg */
} icc_h_lptg_t, *picc_h_lptg_t;

/**
  \brief Union type to access icc_h_sema (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) HW Semaphore Register                                      */
  
  struct {
    __IOM uint32_t sema0_ls_own : 1;          /*!< [0..0] The "Owned by LP" bit of the HW semaphore0.1: the HW
                                                   semaphore0 is owned by LS platform.                                       */
    __IM  uint32_t sema0_hs_own : 1;          /*!< [1..1] The "Owned by HP" bit of the HW semaphore0.1: the HW
                                                   semaphore0 is owned by HP platform.                                       */
    __IOM uint32_t sema1_ls_own : 1;          /*!< [2..2] The "Owned by LP" bit of the HW semaphore1.1: the HW
                                                   semaphore1 is owned by LS platform.                                       */
    __IM  uint32_t sema1_hs_own : 1;          /*!< [3..3] The "Owned by HP" bit of the HW semaphore1.1: the HW
                                                   semaphore1 is owned by HP platform.                                       */
    __IOM uint32_t sema2_ls_own : 1;          /*!< [4..4] The "Owned by LP" bit of the HW semaphore2.1: the HW
                                                   semaphore2 is owned by LS platform.                                       */
    __IM  uint32_t sema2_hs_own : 1;          /*!< [5..5] The "Owned by HP" bit of the HW semaphore2.1: the HW
                                                   semaphore2 is owned by HP platform.                                       */
    __IOM uint32_t sema3_ls_own : 1;          /*!< [6..6] The "Owned by LP" bit of the HW semaphore3.1: the HW
                                                   semaphore3 is owned by LS platform.                                       */
    __IM  uint32_t sema3_hs_own : 1;          /*!< [7..7] The "Owned by HP" bit of the HW semaphore3.1: the HW
                                                   semaphore3 is owned by HP platform.                                       */
    __IOM uint32_t sema4_ls_own : 1;          /*!< [8..8] The "Owned by LP" bit of the HW semaphore4.1: the HW
                                                   semaphore4 is owned by LS platform.                                       */
    __IM  uint32_t sema4_hs_own : 1;          /*!< [9..9] The "Owned by HP" bit of the HW semaphore4.1: the HW
                                                   semaphore4 is owned by HP platform.                                       */
    __IOM uint32_t sema5_ls_own : 1;          /*!< [10..10] The "Owned by LP" bit of the HW semaphore5.1: the HW
                                                   semaphore5 is owned by LS platform.                                       */
    __IM  uint32_t sema5_hs_own : 1;          /*!< [11..11] The "Owned by HP" bit of the HW semaphore5.1: the HW
                                                   semaphore5 is owned by HP platform.                                       */
    __IOM uint32_t sema6_ls_own : 1;          /*!< [12..12] The "Owned by LP" bit of the HW semaphore6.1: the HW
                                                   semaphore6 is owned by LS platform.                                       */
    __IM  uint32_t sema6_hs_own : 1;          /*!< [13..13] The "Owned by HP" bit of the HW semaphore6.1: the HW
                                                   semaphore6 is owned by HP platform.                                       */
    __IOM uint32_t sema7_ls_own : 1;          /*!< [14..14] The "Owned by LP" bit of the HW semaphore7.1: the HW
                                                   semaphore7 is owned by LS platform.                                       */
    __IM  uint32_t sema7_hs_own : 1;          /*!< [15..15] The "Owned by HP" bit of the HW semaphore7.1: the HW
                                                   semaphore7 is owned by HP platform.                                       */
    __IOM uint32_t sema8_ls_own : 1;          /*!< [16..16] The "Owned by LP" bit of the HW semaphore8.1: the HW
                                                   semaphore8 is owned by LS platform.                                       */
    __IM  uint32_t sema8_hs_own : 1;          /*!< [17..17] The "Owned by HP" bit of the HW semaphore8.1: the HW
                                                   semaphore8 is owned by HP platform.                                       */
    __IOM uint32_t sema9_ls_own : 1;          /*!< [18..18] The "Owned by LP" bit of the HW semaphore9.1: the HW
                                                   semaphore9 is owned by LS platform.                                       */
    __IM  uint32_t sema9_hs_own : 1;          /*!< [19..19] The "Owned by HP" bit of the HW semaphore9.1: the HW
                                                   semaphore9 is owned by HP platform.                                       */
    __IOM uint32_t sema10_ls_own : 1;         /*!< [20..20] The "Owned by LP" bit of the HW semaphore10.1: the
                                                   HW semaphore10 is owned by LS platform.                                   */
    __IM  uint32_t sema10_hs_own : 1;         /*!< [21..21] The "Owned by HP" bit of the HW semaphore10.1: the
                                                   HW semaphore10 is owned by HP platform.                                   */
    __IOM uint32_t sema11_ls_own : 1;         /*!< [22..22] The "Owned by LP" bit of the HW semaphore11.1: the
                                                   HW semaphore11 is owned by LS platform.                                   */
    __IM  uint32_t sema11_hs_own : 1;         /*!< [23..23] The "Owned by HP" bit of the HW semaphore11.1: the
                                                   HW semaphore11 is owned by HP platform.                                   */
    __IOM uint32_t sema12_ls_own : 1;         /*!< [24..24] The "Owned by LP" bit of the HW semaphore12.1: the
                                                   HW semaphore12 is owned by LS platform.                                   */
    __IM  uint32_t sema12_hs_own : 1;         /*!< [25..25] The "Owned by HP" bit of the HW semaphore13.1: the
                                                   HW semaphore13 is owned by HP platform.                                   */
    __IOM uint32_t sema13_ls_own : 1;         /*!< [26..26] The "Owned by LP" bit of the HW semaphore13.1: the
                                                   HW semaphore13 is owned by LS platform.                                   */
    __IM  uint32_t sema13_hs_own : 1;         /*!< [27..27] The "Owned by HP" bit of the HW semaphore15.1: the
                                                   HW semaphore16 is owned by HP platform.                                   */
    __IOM uint32_t sema14_ls_own : 1;         /*!< [28..28] The "Owned by LP" bit of the HW semaphore14.1: the
                                                   HW semaphore14 is owned by LS platform.                                   */
    __IM  uint32_t sema14_hs_own : 1;         /*!< [29..29] The "Owned by HP" bit of the HW semaphore14.1: the
                                                   HW semaphore14 is owned by HP platform.                                   */
    __IOM uint32_t sema15_ls_own : 1;         /*!< [30..30] The "Owned by LP" bit of the HW semaphore15.1: the
                                                   HW semaphore15 is owned by LS platform.                                   */
    __IM  uint32_t sema15_hs_own : 1;         /*!< [31..31] The "Owned by HP" bit of the HW semaphore15.1: the
                                                   HW semaphore15 is owned by HP platform.                                   */
  } b;                                        /*!< bit fields for icc_h_sema */
} icc_h_sema_t, *picc_h_sema_t;

/**
  \brief Union type to access icc_h_hlrw0 (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) HP and LP Read/Write Register 0                            */
  
  struct {
    __IOM uint32_t hlrw       : 32;           /*!< [31..0] The information could be writen by LP CPU or HP_CPU.
                                                   It could be used as hardware semaphores. Since both CPU
                                                   can write these registers, the writing side should read
                                                   the register back to check is the writing successful.                     */
  } b;                                        /*!< bit fields for icc_h_hlrw0 */
} icc_h_hlrw0_t, *picc_h_hlrw0_t;

/**
  \brief Union type to access icc_h_hlrw1 (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) HP Read LP Write Register 5                                */
  
  struct {
    __IOM uint32_t hlrw       : 32;           /*!< [31..0] The information could be writen by LP CPU or HP_CPU.
                                                   It could be used as hardware semaphores.                                  */
  } b;                                        /*!< bit fields for icc_h_hlrw1 */
} icc_h_hlrw1_t, *picc_h_hlrw1_t;

/**
  \brief Union type to access icc_h_hlrw2 (@ 0x00000028).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000028) HP Read LP Write Register 6                                */
  
  struct {
    __IOM uint32_t hlrw       : 32;           /*!< [31..0] The information could be writen by LP CPU or HP_CPU.
                                                   It could be used as hardware semaphores.                                  */
  } b;                                        /*!< bit fields for icc_h_hlrw2 */
} icc_h_hlrw2_t, *picc_h_hlrw2_t;

/**
  \brief Union type to access icc_h_hlrw3 (@ 0x0000002C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000002C) HP Read LP Write Register 7                                */
  
  struct {
    __IOM uint32_t hlrw       : 32;           /*!< [31..0] The information could be writen by LP CPU or HP_CPU.
                                                   It could be used as hardware semaphores.                                  */
  } b;                                        /*!< bit fields for icc_h_hlrw3 */
} icc_h_hlrw3_t, *picc_h_hlrw3_t;

/**
  \brief Union type to access icc_h_hwlr0 (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) HP Write LP Read Register 0                                */
  
  struct {
    __IM  uint32_t hwlr       : 32;           /*!< [31..0] The information maintained by HP CPU. It could be message
                                                   queue information: start address, queue size, write pointer
                                                   Q_H2L or the read pointer of Q_L2H.                                       */
  } b;                                        /*!< bit fields for icc_h_hwlr0 */
} icc_h_hwlr0_t, *picc_h_hwlr0_t;

/**
  \brief Union type to access icc_h_hwlr1 (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) HP Write LP Read Register 1                                */
  
  struct {
    __IM  uint32_t hwlr       : 32;           /*!< [31..0] The information maintained by HP CPU. It could be message
                                                   queue information: start address, queue size, write pointer
                                                   Q_H2L or the read pointer of Q_L2H.                                       */
  } b;                                        /*!< bit fields for icc_h_hwlr1 */
} icc_h_hwlr1_t, *picc_h_hwlr1_t;

/**
  \brief Union type to access icc_h_hwlr2 (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) HP Write LP Read Register 2                                */
  
  struct {
    __IM  uint32_t hwlr       : 32;           /*!< [31..0] The information maintained by HP CPU. It could be message
                                                   queue information: start address, queue size, write pointer
                                                   Q_H2L or the read pointer of Q_L2H.                                       */
  } b;                                        /*!< bit fields for icc_h_hwlr2 */
} icc_h_hwlr2_t, *picc_h_hwlr2_t;

/**
  \brief Union type to access icc_h_hwlr3 (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) HP Write LP Read Register 3                                */
  
  struct {
    __IM  uint32_t hwlr       : 32;           /*!< [31..0] The information maintained by HP CPU. It could be message
                                                   queue information: start address, queue size, write pointer
                                                   Q_H2L or the read pointer of Q_L2H.                                       */
  } b;                                        /*!< bit fields for icc_h_hwlr3 */
} icc_h_hwlr3_t, *picc_h_hwlr3_t;

/**
  \brief Union type to access icc_h_hwlr4 (@ 0x00000040).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000040) HP Write LP Read Register 4                                */
  
  struct {
    __IM  uint32_t hwlr       : 32;           /*!< [31..0] The information maintained by HP CPU. It could be message
                                                   queue information: start address, queue size, write pointer
                                                   Q_H2L or the read pointer of Q_L2H.                                       */
  } b;                                        /*!< bit fields for icc_h_hwlr4 */
} icc_h_hwlr4_t, *picc_h_hwlr4_t;

/**
  \brief Union type to access icc_h_hwlr5 (@ 0x00000044).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000044) HP Write LP Read Register 5                                */
  
  struct {
    __IM  uint32_t hwlr       : 32;           /*!< [31..0] The information maintained by HP CPU. It could be message
                                                   queue information: start address, queue size, write pointer
                                                   Q_H2L or the read pointer of Q_L2H.                                       */
  } b;                                        /*!< bit fields for icc_h_hwlr5 */
} icc_h_hwlr5_t, *picc_h_hwlr5_t;

/**
  \brief Union type to access icc_h_hwlr6 (@ 0x00000048).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000048) HP Write LP Read Register 6                                */
  
  struct {
    __IM  uint32_t hwlr       : 32;           /*!< [31..0] The information maintained by HP CPU. It could be message
                                                   queue information: start address, queue size, write pointer
                                                   Q_H2L or the read pointer of Q_L2H.                                       */
  } b;                                        /*!< bit fields for icc_h_hwlr6 */
} icc_h_hwlr6_t, *picc_h_hwlr6_t;

/**
  \brief Union type to access icc_h_hwlr7 (@ 0x0000004C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000004C) HP Write LP Read Register 7                                */
  
  struct {
    __IM  uint32_t hwlr       : 32;           /*!< [31..0] The information maintained by HP CPU. It could be message
                                                   queue information: start address, queue size, write pointer
                                                   Q_H2L or the read pointer of Q_L2H.                                       */
  } b;                                        /*!< bit fields for icc_h_hwlr7 */
} icc_h_hwlr7_t, *picc_h_hwlr7_t;

/**
  \brief Union type to access icc_h_hptg (@ 0x00000050).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000050) HP Toggle Register                                         */
  
  struct {
    __IM  uint32_t hptg0      : 1;            /*!< [0..0] It's a 1 bit sequence number for HWLR0 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t hptg1      : 1;            /*!< [1..1] It's a 1 bit sequence number for HWLR1 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t hptg2      : 1;            /*!< [2..2] It's a 1 bit sequence number for HWLR2 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t hptg3      : 1;            /*!< [3..3] It's a 1 bit sequence number for HWLR3 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t hptg4      : 1;            /*!< [4..4] It's a 1 bit sequence number for HWLR4 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t hptg5      : 1;            /*!< [5..5] It's a 1 bit sequence number for HWLR5 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t hptg6      : 1;            /*!< [6..6] It's a 1 bit sequence number for HWLR6 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t hptg7      : 1;            /*!< [7..7] It's a 1 bit sequence number for HWLR7 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t            : 8;
    __IM  uint32_t h2ltg0     : 1;            /*!< [16..16] It's a 1 bit sequence number for HLRW0 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t h2ltg1     : 1;            /*!< [17..17] It's a 1 bit sequence number for HLRW1 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t h2ltg2     : 1;            /*!< [18..18] It's a 1 bit sequence number for HLRW2 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t h2ltg3     : 1;            /*!< [19..19] It's a 1 bit sequence number for HLRW3 register updating.
                                                   Toggle this bit (0 to 1 or 1 to 0) will assert the corresponding
                                                   interrupt on the LP CPU.                                                  */
    __IM  uint32_t h2ltgs     : 1;            /*!< [20..20] This bit is used to control the enable of the interrupt
                                                   triggered by the H2LTGS toggles. 0/1: Disable/Enable Interrupt            */
  } b;                                        /*!< bit fields for icc_h_hptg */
} icc_h_hptg_t, *picc_h_hptg_t;

/** @} */ /* End of group ls_hal_icc_h_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_ICC_H_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BLP_ICC_H_TYPE_H_

