/**************************************************************************//**
 * @file      rtl8195blp_rtc_type.h
 * @brief
 * @version   V1.00
 * @date      2017-11-1 16:37:43
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

#ifndef _RTL8195BLP_RTC_TYPE_H_
#define _RTL8195BLP_RTC_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_RTC_REG_TYPE

/**
 * @addtogroup ls_hal_rtc_reg RTC Registers.
 * @ingroup ls_hal_rtc
 * @{
 */

/**
  \brief Union type to access rtc_cmd (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) REG_AON_LSFIF_CMD                                          */

  struct {
    __IOM uint32_t lsfif_ad   : 16;           /*!< [15..0] BIT_AON_LSFIF_AD[15:8]=8'h00: RTC register base address           */

    __IM  uint32_t            : 8;
    __IOM uint32_t lsfif_we   : 4;            /*!< [27..24] LSF register byte write enable. This field is valid
                                                   during LSF register write transfer, and is ignored during
                                                   LSF register read transfer                                                */
    __IOM uint32_t lsfif_wr   : 1;            /*!< [28..28] LSF register write transfer indicator. 1: LSF register
                                                   write transfer, 0: LSF register read transfer                             */
    __IM  uint32_t            : 2;
    __IOM uint32_t lsfif_poll : 1;            /*!< [31..31] Set this bit to do LSF register read or write transfer
                                                   depend on BIT_AON_LSFIF_WR. When transfer done, this bit
                                                   will be clear by HW                                                       */
  } b;                                        /*!< bit fields for rtc_cmd */
} rtc_cmd_t, *prtc_cmd_t;

/**
  \brief Union type to access rtc_lsfif_rwd (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) REG_AON_LSFIF_RWD                                          */

  struct {
    __IOM uint32_t lsfif_rwd  : 32;           /*!< [31..0] LSF(low speed function) write                                     */
  } b;                                        /*!< bit fields for rtc_lsfif_rwd */
} rtc_lsfif_rwd_t, *prtc_lsfif_rwd_t;

/**
  \brief Union type to access rtc_imr (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) REG_AON_RTC_IMR                                            */

  struct {
    __IOM uint32_t cnt_sec_imr : 1;           /*!< [0..0] Interrupt mask of RTC seconds counter                              */
    __IOM uint32_t cnt_min_imr : 1;           /*!< [1..1] Interrupt mask of RTC minutes counter                              */
    __IOM uint32_t cnt_hrs_imr : 1;           /*!< [2..2] Interrupt mask of RTC hours counter                                */
    __IOM uint32_t cnt_dow_imr : 1;           /*!< [3..3] Interrupt mask of RTC day of week counter                          */
    __IOM uint32_t cnt_dom_imr : 1;           /*!< [4..4] Interrupt mask of RTC day of month counter                         */
    __IOM uint32_t cnt_mth_imr : 1;           /*!< [5..5] Interrupt mask of RTC month counter                                */
    __IOM uint32_t cnt_yrs_imr : 1;           /*!< [6..6] Interrupt mask of RTC years counter                                */
    __IOM uint32_t cnt_doy_imr : 1;           /*!< [7..7] Interrupt mask of RTC day of year counter                          */
    __IOM uint32_t alrm_sec_imr : 1;          /*!< [8..8] Interrupt mask of RTC second alarm                                 */
    __IOM uint32_t alrm_min_imr : 1;          /*!< [9..9] Interrupt mask of RTC minute alarm                                 */
    __IOM uint32_t alrm_hrs_imr : 1;          /*!< [10..10] Interrupt mask of RTC hour alarm                                 */
    __IOM uint32_t alrm_dow_imr : 1;          /*!< [11..11] Interrupt mask of RTC day of week alarm                          */
    __IOM uint32_t alrm_dom_imr : 1;          /*!< [12..12] Interrupt mask of RTC day of month alarm                         */
    __IOM uint32_t alrm_mth_imr : 1;          /*!< [13..13] Interrupt mask of RTC month alarm                                */
    __IOM uint32_t alrm_yrs_imr : 1;          /*!< [14..14] Interrupt mask of RTC year alarm                                 */
    __IOM uint32_t alrm_doy_imr : 1;          /*!< [15..15] Interrupt mask of RTC day of year alarm                          */
    __IOM uint32_t alrm_imr   : 1;            /*!< [16..16] Interrupt mask of RTC alarm                                      */
  } b;                                        /*!< bit fields for rtc_imr */
} rtc_imr_t, *prtc_imr_t;

/**
  \brief Union type to access rtc_isr (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) REG_AON_RTC_ISR                                            */

  struct {
    __IOM uint32_t cnt_sec_isr : 1;           /*!< [0..0] Indicate increment of the second timer                             */
    __IOM uint32_t cnt_min_isr : 1;           /*!< [1..1] Indicate increment of the minute timer                             */
    __IOM uint32_t cnt_hrs_isr : 1;           /*!< [2..2] Indicate increment of the hour timer                               */
    __IOM uint32_t cnt_dow_isr : 1;           /*!< [3..3] Indicate increment of the day-of-week timer                        */
    __IOM uint32_t cnt_dom_isr : 1;           /*!< [4..4] Indicate increment of the day-of-month timer                       */
    __IOM uint32_t cnt_mth_isr : 1;           /*!< [5..5] Indicate increment of the month timer                              */
    __IOM uint32_t cnt_yrs_isr : 1;           /*!< [6..6] Indicate increment of the year timer                               */
    __IOM uint32_t cnt_doy_isr : 1;           /*!< [7..7] Indicate increment of the Day-of-year timer                        */
    __IOM uint32_t alrm_sec_isr : 1;          /*!< [8..8] Indicate Second timer value match ALRM_SEC                         */
    __IOM uint32_t alrm_min_isr : 1;          /*!< [9..9] Indicate Minute timer value match ALRM_MIN                         */
    __IOM uint32_t alrm_hrs_isr : 1;          /*!< [10..10] Indicate Hour timer value match ALRM_HRS                         */
    __IOM uint32_t alrm_dow_isr : 1;          /*!< [11..11] Indicate DOW timer value match ALRM_DOW                          */
    __IOM uint32_t alrm_dom_isr : 1;          /*!< [12..12] Indicate DOM timer value match ALRM_DOM                          */
    __IOM uint32_t alrm_mth_isr : 1;          /*!< [13..13] Indicate MTH timer value match ALRM_MTH                          */
    __IOM uint32_t alrm_yrs_isr : 1;          /*!< [14..14] Indicate Year timer value match ALRM_YRS                         */
    __IOM uint32_t alrm_doy_isr : 1;          /*!< [15..15] Indicate DOY timer value match ALRM_DOY                          */
    __IOM uint32_t alrm_isr   : 1;            /*!< [16..16] Indicate ALL timer value match ALRM value                        */
  } b;                                        /*!< bit fields for rtc_isr */
} rtc_isr_t, *prtc_isr_t;

/** @} */ /* End of group ls_hal_rtc_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_RTC_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BLP_RTC_TYPE_H_

