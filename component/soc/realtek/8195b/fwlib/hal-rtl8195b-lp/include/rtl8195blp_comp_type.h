/**************************************************************************//**
 * @file      rtl8195blp_comp_type.h
 * @brief
 * @version   V1.00
 * @date      2017-11-1 14:39:57
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

#ifndef _RTL8195BLP_COMP_TYPE_H_
#define _RTL8195BLP_COMP_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_COMP_REG_TYPE

/**
 * @addtogroup ls_hal_comp_reg COMP Registers.
 * @ingroup ls_hal_comp
 * @{
 */

/**
  \brief Union type to access comp_ref_ch0 (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) Comparator Channel 0 Reference Volatage Register           */

  struct {
    __IOM uint32_t ref0       : 8;            /*!< [7..0] This bit controls the comparator channel 0 internal reference
                                                   voltage 0.                                                                */
    __IM  uint32_t            : 8;
    __IOM uint32_t ref1       : 8;            /*!< [23..16] This bit controls the comparator channel 0 internal
                                                   reference voltage 1.                                                      */
  } b;                                        /*!< bit fields for comp_ref_ch0 */
} comp_ref_ch0_t, *pcomp_ref_ch0_t;

/**
  \brief Union type to access comp_ref_ch1 (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) Comparator Channel 1 Reference Volatage Register           */

  struct {
    __IOM uint32_t ref0       : 8;            /*!< [7..0] This bit controls the comparator channel 1 internal reference
                                                   voltage 0.                                                                */
    __IM  uint32_t            : 8;
    __IOM uint32_t ref1       : 8;            /*!< [23..16] This bit controls the comparator channel 1 internal
                                                   reference voltage 1.                                                      */
  } b;                                        /*!< bit fields for comp_ref_ch1 */
} comp_ref_ch1_t, *pcomp_ref_ch1_t;

/**
  \brief Union type to access comp_ref_ch2 (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) Comparator Channel 2 Reference Volatage Register           */

  struct {
    __IOM uint32_t ref0       : 8;            /*!< [7..0] This bit controls the comparator channel 2 internal reference
                                                   voltage 0.                                                                */
    __IM  uint32_t            : 8;
    __IOM uint32_t ref1       : 8;            /*!< [23..16] This bit controls the comparator channel 2 internal
                                                   reference voltage 1.                                                      */
  } b;                                        /*!< bit fields for comp_ref_ch2 */
} comp_ref_ch2_t, *pcomp_ref_ch2_t;

/**
  \brief Union type to access comp_ref_ch3 (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) Comparator Channel 3 Reference Volatage Register           */

  struct {
    __IOM uint32_t ref0       : 8;            /*!< [7..0] This bit controls the comparator channel 3 internal reference
                                                   voltage 0.                                                                */
    __IM  uint32_t            : 8;
    __IOM uint32_t ref1       : 8;            /*!< [23..16] This bit controls the comparator channel 3 internal
                                                   reference voltage 1.                                                      */
  } b;                                        /*!< bit fields for comp_ref_ch3 */
} comp_ref_ch3_t, *pcomp_ref_ch3_t;

/**
  \brief Union type to access comp_intr_ctrl (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) Comparator Interrupt Control Register                      */

  struct {
    __IOM uint32_t wk_adc_en_0 : 1;           /*!< [0..0] This bit controls whether the comparator channel 0 sends
                                                   wakeup signal or not when the criterion of wk_adc_ctrl_0
                                                   matches.                                                                  */
    __IOM uint32_t wk_adc_ctrl_0 : 2;         /*!< [2..1] This field defines the criterion of when comparator channel
                                                   0 should wake up ADC.                                                     */
    __IOM uint32_t wk_adc_en_1 : 1;           /*!< [3..3] This bit controls whether the comparator channel 1 sends
                                                   wakeup signal or not when the criterion of wk_adc_ctrl_1
                                                   matches.                                                                  */
    __IOM uint32_t wk_adc_ctrl_1 : 2;         /*!< [5..4] This field defines the criterion of when comparator channel
                                                   1 should wake up ADC.                                                     */
    __IOM uint32_t wk_adc_en_2 : 1;           /*!< [6..6] This bit controls whether the comparator channel 2 sends
                                                   wakeup signal or not when the criterion of wk_adc_ctrl_2
                                                   matches.                                                                  */
    __IOM uint32_t wk_adc_ctrl_2 : 2;         /*!< [8..7] This field defines the criterion of when comparator channel
                                                   2 should wake up ADC.                                                     */
    __IOM uint32_t wk_adc_en_3 : 1;           /*!< [9..9] This bit controls whether the comparator channel 3 sends
                                                   wakeup signal or not when the criterion of wk_adc_ctrl_3
                                                   matches.                                                                  */
    __IOM uint32_t wk_adc_ctrl_3 : 2;         /*!< [11..10] This field defines the criterion of when comparator
                                                   channel 3 should wake up ADC.                                             */
    __IM  uint32_t            : 4;
    __IOM uint32_t wk_sys_en_0 : 1;           /*!< [16..16] This bit controls whether the comparator channel 0
                                                   sends interrupt (wake up) signal or not when the criterion
                                                   of wk_sys_ctrl_3 matches.                                                 */
    __IOM uint32_t wk_sys_ctrl_0 : 2;         /*!< [18..17] This bit defines the criterion of when comparator channel
                                                   0 should interrupts (wake up) system.                                     */
    __IOM uint32_t wk_sys_en_1 : 1;           /*!< [19..19] This bit controls whether the comparator channel 1
                                                   sends interrupt (wake up) signal or not when the criterion
                                                   of wk_sys_ctrl_1 matches.                                                 */
    __IOM uint32_t wk_sys_ctrl_1 : 2;         /*!< [21..20] This bit defines the criterion of when comparator channel
                                                   1 should interrupts (wake up) system.                                     */
    __IOM uint32_t wk_sys_en_2 : 1;           /*!< [22..22] This bit controls whether the comparator channel 2
                                                   sends interrupt (wake up) signal or not when the criterion
                                                   of wk_sys_ctrl_2 matches.                                                 */
    __IOM uint32_t wk_sys_ctrl_2 : 2;         /*!< [24..23] This bit defines the criterion of when comparator channel
                                                   2 should interrupts (wake up) system.                                     */
    __IOM uint32_t wk_sys_en_3 : 1;           /*!< [25..25] This bit controls whether the comparator channel 3
                                                   sends interrupt (wake up) signal or not when the criterion
                                                   of wk_sys_ctrl_3 matches.                                                 */
    __IOM uint32_t wk_sys_ctrl_3 : 2;         /*!< [27..26] This bit defines the criterion of when comparator channel
                                                   3 should interrupts (wake up) system.                                     */
  } b;                                        /*!< bit fields for comp_intr_ctrl */
} comp_intr_ctrl_t, *pcomp_intr_ctrl_t;

/**
  \brief Union type to access comp_intr_sts (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) Comparator Interrupt Status Register                       */

  struct {
    __IOM uint32_t wk_adc_sts_0 : 1;          /*!< [0..0] This bit reflects if channle 0 of comparator module sent
                                                   a wake-up signal to ADC or not.                                           */
    __IM  uint32_t            : 2;
    __IOM uint32_t wk_adc_sts_1 : 1;          /*!< [3..3] This bit reflects if channle 1 of comparator module sent
                                                   a wake-up signal to ADC or not.                                           */
    __IM  uint32_t            : 2;
    __IOM uint32_t wk_adc_sts_2 : 1;          /*!< [6..6] This bit reflects if channle 2 of comparator module sent
                                                   a wake-up signal to ADC or not.                                           */
    __IM  uint32_t            : 2;
    __IOM uint32_t wk_adc_sts_3 : 1;          /*!< [9..9] This bit reflects if channle 3 of comparator module sent
                                                   a wake-up signal to ADC or not.                                           */
    __IM  uint32_t            : 6;
    __IOM uint32_t wk_sys_sts_0 : 1;          /*!< [16..16] This bit reflects if channle 0 of comparator module
                                                   sent a interrupt (wake-up) signal to system or not.                       */
    __IM  uint32_t            : 2;
    __IOM uint32_t wk_sys_sts_1 : 1;          /*!< [19..19] This bit reflects if channle 1 of comparator module
                                                   sent a interrupt (wake-up) signal to system or not.                       */
    __IM  uint32_t            : 2;
    __IOM uint32_t wk_sys_sts_2 : 1;          /*!< [22..22] This bit reflects if channle 2 of comparator module
                                                   sent a interrupt (wake-up) signal to system or not.                       */
    __IM  uint32_t            : 2;
    __IOM uint32_t wk_sys_sts_3 : 1;          /*!< [25..25] This bit reflects if channle 3 of comparator module
                                                   sent a interrupt (wake-up) signal to system or not.                       */
  } b;                                        /*!< bit fields for comp_intr_sts */
} comp_intr_sts_t, *pcomp_intr_sts_t;

/**
  \brief Union type to access comp_intr_raw_sts (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) Comparator Interrupt RAW Status Register                   */

  struct {
    __IM  uint32_t wk_adc_sts_0 : 1;          /*!< [0..0] This bit reflects if channle 0 of comparator module sent
                                                   a wake-up signal to ADC or not.                                           */
    __IM  uint32_t            : 2;
    __IM  uint32_t wk_adc_sts_1 : 1;          /*!< [3..3] This bit reflects if channle 1 of comparator module sent
                                                   a wake-up signal to ADC or not.                                           */
    __IM  uint32_t            : 2;
    __IM  uint32_t wk_adc_sts_2 : 1;          /*!< [6..6] This bit reflects if channle 2 of comparator module sent
                                                   a wake-up signal to ADC or not.                                           */
    __IM  uint32_t            : 2;
    __IM  uint32_t wk_adc_sts_3 : 1;          /*!< [9..9] This bit reflects if channle 3 of comparator module sent
                                                   a wake-up signal to ADC or not.                                           */
    __IM  uint32_t            : 6;
    __IM  uint32_t wk_sys_sts_0 : 1;          /*!< [16..16] This bit reflects if channle 0 of comparator module
                                                   sent a interrupt (wake-up) signal to system or not.                       */
    __IM  uint32_t            : 2;
    __IM  uint32_t wk_sys_sts_1 : 1;          /*!< [19..19] This bit reflects if channle 1 of comparator module
                                                   sent a interrupt (wake-up) signal to system or not.                       */
    __IM  uint32_t            : 2;
    __IM  uint32_t wk_sys_sts_2 : 1;          /*!< [22..22] This bit reflects if channle 2 of comparator module
                                                   sent a interrupt (wake-up) signal to system or not.                       */
    __IM  uint32_t            : 2;
    __IM  uint32_t wk_sys_sts_3 : 1;          /*!< [25..25] This bit reflects if channle 3 of comparator module
                                                   sent a interrupt (wake-up) signal to system or not.                       */
  } b;                                        /*!< bit fields for comp_intr_raw_sts */
} comp_intr_raw_sts_t, *pcomp_intr_raw_sts_t;

/**
  \brief Union type to access comp_chsw_list (@ 0x0000001C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000001C) Comparator Channel Switch List Register                    */

  struct {
    __IOM uint32_t chsw_0     : 4;            /*!< [3..0] These bits defines the 1st channel to do a comparison
                                                   when the start-compare event takes place.                                 */
    __IOM uint32_t chsw_1     : 4;            /*!< [7..4] These bits defines the 2nd channel to do a comparison
                                                   when the start-compare event takes place.                                 */
    __IOM uint32_t chsw_2     : 4;            /*!< [11..8] These bits defines the 3rd channel to do a comparison
                                                   when the start-compare event takes place.                                 */
    __IOM uint32_t chsw_3     : 4;            /*!< [15..12] These bits defines the 4th channel to do a comparison
                                                   when the start-compare event takes place.                                 */
  } b;                                        /*!< bit fields for comp_chsw_list */
} comp_chsw_list_t, *pcomp_chsw_list_t;

/**
  \brief Union type to access comp_last_ch (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) Comparator Last Channel Register                           */

  struct {
    __IOM uint32_t last_ch    : 2;            /*!< [1..0] These bits reflects the last used channel.                         */
  } b;                                        /*!< bit fields for comp_last_ch */
} comp_last_ch_t, *pcomp_last_ch_t;

/**
  \brief Union type to access comp_busy (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) Comparator Busy Status Register                            */

  struct {
    __IM  uint32_t busy       : 1;            /*!< [0..0] This bit reflects the comparator is busy or not.                   */
  } b;                                        /*!< bit fields for comp_busy */
} comp_busy_t, *pcomp_busy_t;

/**
  \brief Union type to access comp_ch_sts (@ 0x00000028).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000028) Comparator Channel Status Register                         */

  struct {
    __IM  uint32_t ch_sts_0   : 2;            /*!< [1..0] This bit reflects the channel 0 comparison result.                 */
    __IM  uint32_t ch_sts_1   : 2;            /*!< [3..2] This bit reflects the channel 1 comparison result.                 */
    __IM  uint32_t ch_sts_2   : 2;            /*!< [5..4] This bit reflects the channel 2 comparison result.                 */
    __IM  uint32_t ch_sts_3   : 2;            /*!< [7..6] This bit reflects the channel 3 comparison result.                 */
  } b;                                        /*!< bit fields for comp_ch_sts */
} comp_ch_sts_t, *pcomp_ch_sts_t;

/**
  \brief Union type to access comp_auto_shut (@ 0x0000002C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000002C) Comparator Auto Shutdown Register                          */

  struct {
    __IOM uint32_t auto_shut  : 1;            /*!< [0..0] This bit controls the comparator to disable the analog
                                                   module and mux automatically or not after the analog conversion
                                                   is done.                                                                  */
  } b;                                        /*!< bit fields for comp_auto_shut */
} comp_auto_shut_t, *pcomp_auto_shut_t;

/**
  \brief Union type to access comp_wk_timer (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) Comparator Wake Timer Control Reigster                     */

  struct {
    __IOM uint32_t wk_timer   : 1;            /*!< [0..0] This bit controls the external trigger source of general
                                                   timer enabled or not.                                                     */
  } b;                                        /*!< bit fields for comp_wk_timer */
} comp_wk_timer_t, *pcomp_wk_timer_t;

/**
  \brief Union type to access comp_wk_timer_sel (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) Comparator Wake Timer Select Reigster                      */

  struct {
    __IOM uint32_t wk_timer_sel : 2;          /*!< [1..0] This three bits defines which timer channel would be
                                                   used to wake up the comparator.                                           */
  } b;                                        /*!< bit fields for comp_wk_timer_sel */
} comp_wk_timer_sel_t, *pcomp_wk_timer_sel_t;

/**
  \brief Union type to access comp_rst_list (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) Comparator Rest List Register                              */

  struct {
    __IOM uint32_t rst_list   : 1;            /*!< [0..0] This bit controls to reset the channel switch to default
                                                   state or not.                                                             */
  } b;                                        /*!< bit fields for comp_rst_list */
} comp_rst_list_t, *pcomp_rst_list_t;

/**
  \brief Union type to access comp_auto_sw_en (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) Comparator Auto Channel Switch Enable Reigster             */

  struct {
    __IOM uint32_t auto_sw_en : 1;            /*!< [0..0] This bit controls the automatic channel swtich enabled
                                                   or disabled.                                                              */
  } b;                                        /*!< bit fields for comp_auto_sw_en */
} comp_auto_sw_en_t, *pcomp_auto_sw_en_t;

/**
  \brief Union type to access comp_enable (@ 0x00000040).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000040) Comparator Enable Control Register                         */

  struct {
    __IOM uint32_t enable     : 1;            /*!< [0..0] This bit is for comparator enable control.                         */
    __IOM uint32_t trig_en    : 1;            /*!< [1..1] This bit is a mulitple trigger control source. For software
                                                   trigger (when comparator auto channel switch register (offset:
                                                   0x3C) is NOT set and wake timer control is NOT set), this
                                                   bit is used to be a software trigger source. Each time
                                                   this bit is set to 1 from 0, it drives comparator to do
                                                   a channel comparison. For auto trigger, this bit is used
                                                   to drive comparator to start the auto channel switch operation.           */
  } b;                                        /*!< bit fields for comp_enable */
} comp_enable_t, *pcomp_enable_t;

/**
  \brief Union type to access comp_wk_shut_cnt (@ 0x00000044).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000044) Comparator Shutdown Counter Register                       */

  struct {
    __IOM uint32_t wk_shut_cnt : 8;           /*!< [7..0] This eight bits defines how long to disable comparator
                                                   analog module when an external trigger event is sent to
                                                   the comparator. The count must include the comparator response
                                                   time to get a correct compare result.                                     */
  } b;                                        /*!< bit fields for comp_wk_shut_cnt */
} comp_wk_shut_cnt_t, *pcomp_wk_shut_cnt_t;

/** @} */ /* End of group ls_hal_comp_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_COMP_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BLP_COMP_TYPE_H_

