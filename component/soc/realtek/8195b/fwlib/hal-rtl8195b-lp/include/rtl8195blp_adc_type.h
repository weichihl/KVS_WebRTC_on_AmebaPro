/**************************************************************************//**
 * @file      rtl8195blp_adc_type.h
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

#ifndef _RTL8195BLP_ADC_TYPE_H_
#define _RTL8195BLP_ADC_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_ADC_REG_TYPE

/**
 * @addtogroup ls_hal_adc_reg ADC Registers.
 * @ingroup ls_hal_adc
 * @{
 */

/**
  \brief Union type to access adc_conf (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) ADC Configuration Register                                 */

  struct {
    __IOM uint32_t ref_in_sel : 1;            /*!< [0..0] ADC reference voltage input.                                       */
    __IOM uint32_t op_mod     : 3;            /*!< [3..1] ADC operation mode. This field is to control ADC operation
                                                   mode.                                                                     */
    __IOM uint32_t cvlist_len : 4;            /*!< [7..4] ADC conversion list length. This field defines the number
                                                   of items in ADC conversion channel list. 0 is for 1 item
                                                   in list. 1 is for 2 items in list.                                        */
    __IM  uint32_t            : 1;
    __IOM uint32_t en         : 1;            /*!< [9..9] ADC enable control. This bit is to control ADC is enable
                                                   or not.                                                                   */
  } b;                                        /*!< bit fields for adc_conf */
} adc_conf_t, *padc_conf_t;

/**
  \brief Union type to access adc_in_type (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) ADC Input Type Register                                    */

  struct {
    __IOM uint32_t ch0        : 1;            /*!< [0..0] ADC channel 0 input type.                                          */
    __IOM uint32_t ch1        : 1;            /*!< [1..1] ADC channel 1 input type.                                          */
    __IOM uint32_t ch2        : 1;            /*!< [2..2] ADC channel 2 input type.                                          */
    __IOM uint32_t ch3        : 1;            /*!< [3..3] ADC channel 3 input type.                                          */
    __IOM uint32_t ch4        : 1;            /*!< [4..4] ADC channel 4 input type.                                          */
    __IOM uint32_t ch5        : 1;            /*!< [5..5] ADC channel 5 input type.                                          */

    __IM  uint32_t ch6        : 1;            /*!< [6..6] ADC channel 6 input type.                                          */
    __IM  uint32_t ch7        : 1;            /*!< [7..7] ADC channel 7 input type.                                          */
    __IM  uint32_t ch8        : 1;            /*!< [8..8] ADC channel 8 input type.                                          */
    __IM  uint32_t ch9        : 1;            /*!< [9..9] ADC channel 9 input type.                                          */
  } b;                                        /*!< bit fields for adc_in_type */
} adc_in_type_t, *padc_in_type_t;

/**
  \brief Union type to access adc_comp_th_ch0 (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) ADC Channel 0 Comparison Threshold Register                */

  struct {
    __IOM uint32_t th_l       : 10;           /*!< [9..0] ADC channel 0 comparison low threshold.                            */

    __IM  uint32_t            : 6;
    __IOM uint32_t th_h       : 10;           /*!< [25..16] ADC channel 0 comparison high threshold.                         */
  } b;                                        /*!< bit fields for adc_comp_th_ch0 */
} adc_comp_th_ch0_t, *padc_comp_th_ch0_t;

/**
  \brief Union type to access adc_comp_th_ch1 (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) ADC Channel 1 Comparison Threshold Register                */

  struct {
    __IOM uint32_t th_l       : 10;           /*!< [9..0] ADC channel 1 comparison low threshold.                            */

    __IM  uint32_t            : 6;
    __IOM uint32_t th_h       : 10;           /*!< [25..16] ADC channel 1 comparison high threshold.                         */
  } b;                                        /*!< bit fields for adc_comp_th_ch1 */
} adc_comp_th_ch1_t, *padc_comp_th_ch1_t;

/**
  \brief Union type to access adc_comp_th_ch2 (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) ADC Channel 2 Comparison Threshold Register                */

  struct {
    __IOM uint32_t th_l       : 10;           /*!< [9..0] ADC channel 2 comparison low threshold.                            */

    __IM  uint32_t            : 6;
    __IOM uint32_t th_h       : 10;           /*!< [25..16] ADC channel 2 comparison high threshold.                         */
  } b;                                        /*!< bit fields for adc_comp_th_ch2 */
} adc_comp_th_ch2_t, *padc_comp_th_ch2_t;

/**
  \brief Union type to access adc_comp_th_ch3 (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) ADC Channel 3 Comparison Threshold Register                */

  struct {
    __IOM uint32_t th_l       : 10;           /*!< [9..0] ADC channel 3 comparison low threshold.                            */

    __IM  uint32_t            : 6;
    __IOM uint32_t th_h       : 10;           /*!< [25..16] ADC channel 3 comparison high threshold.                         */
  } b;                                        /*!< bit fields for adc_comp_th_ch3 */
} adc_comp_th_ch3_t, *padc_comp_th_ch3_t;

/**
  \brief Union type to access adc_comp_th_ch4 (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) ADC Channel 4 Comparison Threshold Register                */

  struct {
    __IOM uint32_t th_l       : 10;           /*!< [9..0] ADC channel 4 comparison low threshold.                            */

    __IM  uint32_t            : 6;
    __IOM uint32_t th_h       : 10;           /*!< [25..16] ADC channel 4 comparison high threshold.                         */
  } b;                                        /*!< bit fields for adc_comp_th_ch4 */
} adc_comp_th_ch4_t, *padc_comp_th_ch4_t;

/**
  \brief Union type to access adc_comp_th_ch5 (@ 0x0000001C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000001C) ADC Channel 5 Comparison Threshold Register                */

  struct {
    __IOM uint32_t th_l       : 10;           /*!< [9..0] ADC channel 5 comparison low threshold.                            */

    __IM  uint32_t            : 6;
    __IOM uint32_t th_h       : 10;           /*!< [25..16] ADC channel 5 comparison high threshold.                         */
  } b;                                        /*!< bit fields for adc_comp_th_ch5 */
} adc_comp_th_ch5_t, *padc_comp_th_ch5_t;

/**
  \brief Union type to access adc_comp_th_ch6 (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) ADC Channel 6 Comparison Threshold Register                */

  struct {
    __IOM uint32_t th_l       : 10;           /*!< [9..0] ADC channel 6 comparison low threshold.                            */

    __IM  uint32_t            : 6;
    __IOM uint32_t th_h       : 10;           /*!< [25..16] ADC channel 6 comparison high threshold.                         */
  } b;                                        /*!< bit fields for adc_comp_th_ch6 */
} adc_comp_th_ch6_t, *padc_comp_th_ch6_t;

/**
  \brief Union type to access adc_comp_th_ch7 (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) ADC Channel 7 Comparison Threshold Register                */

  struct {
    __IOM uint32_t th_l       : 10;           /*!< [9..0] ADC channel 7 comparison low threshold.                            */

    __IM  uint32_t            : 6;
    __IOM uint32_t th_h       : 10;           /*!< [25..16] ADC channel 7 comparison high threshold.                         */
  } b;                                        /*!< bit fields for adc_comp_th_ch7 */
} adc_comp_th_ch7_t, *padc_comp_th_ch7_t;

/**
  \brief Union type to access adc_comp_th_ch8 (@ 0x00000028).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000028) ADC Channel 8 Comparison Threshold Register                */

  struct {
    __IOM uint32_t th_l       : 10;           /*!< [9..0] ADC channel 8 comparison low threshold.                            */

    __IM  uint32_t            : 6;
    __IOM uint32_t th_h       : 10;           /*!< [25..16] ADC channel 8 comparison high threshold.                         */
  } b;                                        /*!< bit fields for adc_comp_th_ch8 */
} adc_comp_th_ch8_t, *padc_comp_th_ch8_t;

/**
  \brief Union type to access adc_comp_th_ch9 (@ 0x0000002C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000002C) ADC Channel 9 Comparison Threshold Register                */

  struct {
    __IOM uint32_t th_l       : 10;           /*!< [9..0] ADC channel 9 comparison low threshold.                            */

    __IM  uint32_t            : 6;
    __IOM uint32_t th_h       : 10;           /*!< [25..16] ADC channel 9 comparison high threshold.                         */
  } b;                                        /*!< bit fields for adc_comp_th_ch9 */
} adc_comp_th_ch9_t, *padc_comp_th_ch9_t;

/**
  \brief Union type to access adc_comp_ctrl (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) ADC Comparison Control Register                            */

  struct {
    __IOM uint32_t ch0        : 2;            /*!< [1..0] This field controls that ADC channel 0 comparison criterion.       */
    __IOM uint32_t ch1        : 2;            /*!< [3..2] This field controls that ADC channel 1 comparison criterion.       */
    __IOM uint32_t ch2        : 2;            /*!< [5..4] This field controls that ADC channel 2 comparison criterion.       */
    __IOM uint32_t ch3        : 2;            /*!< [7..6] This field controls that ADC channel 3 comparison criterion.       */
    __IOM uint32_t ch4        : 2;            /*!< [9..8] This field controls that ADC channel 4 comparison criterion.       */
    __IOM uint32_t ch5        : 2;            /*!< [11..10] This field controls that ADC channel 5 comparison criterion.     */
    __IOM uint32_t ch6        : 2;            /*!< [13..12] This field controls that ADC channel 6 comparison criterion.     */
    __IOM uint32_t ch7        : 2;            /*!< [15..14] This field controls that ADC channel 7 comparison criterion.     */
    __IOM uint32_t ch8        : 2;            /*!< [17..16] This field controls that ADC channel 8 comparison criterion.     */
    __IOM uint32_t ch9        : 2;            /*!< [19..18] This field controls that ADC channel 9 comparison criterion.     */
  } b;                                        /*!< bit fields for adc_comp_ctrl */
} adc_comp_ctrl_t, *padc_comp_ctrl_t;

/**
  \brief Union type to access adc_comp_sts (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) ADC Comparison Status Register                             */

  struct {
    __IM  uint32_t ch0        : 2;            /*!< [1..0] This field reflects comparison result of chnnel 0 immediately.     */
    __IM  uint32_t ch1        : 2;            /*!< [3..2] This field reflects comparison result of chnnel 1 immediately.     */
    __IM  uint32_t ch2        : 2;            /*!< [5..4] This field reflects comparison result of chnnel 2 immediately.     */
    __IM  uint32_t ch3        : 2;            /*!< [7..6] This field reflects comparison result of chnnel 3 immediately.     */
    __IM  uint32_t ch4        : 2;            /*!< [9..8] This field reflects comparison result of chnnel 4 immediately.     */
    __IM  uint32_t ch5        : 2;            /*!< [11..10] This field reflects comparison result of chnnel 5 immediately.   */
    __IM  uint32_t ch6        : 2;            /*!< [13..12] This field reflects comparison result of chnnel 6 immediately.   */
    __IM  uint32_t ch7        : 2;            /*!< [15..14] This field reflects comparison result of chnnel 7 immediately.   */
    __IM  uint32_t ch8        : 2;            /*!< [17..16] This field reflects comparison result of chnnel 8 immediately.   */
    __IM  uint32_t ch9        : 2;            /*!< [19..18] This field reflects comparison result of chnnel 9 immediately.   */
  } b;                                        /*!< bit fields for adc_comp_sts */
} adc_comp_sts_t, *padc_comp_sts_t;

/**
  \brief Union type to access adc_chsw_list_0 (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) ADC Channel Swtich List 0 Register                         */

  struct {
    __IOM uint32_t chsw_0     : 4;            /*!< [3..0] This field defines 1st channel in channel switch list.             */
    __IOM uint32_t chsw_1     : 4;            /*!< [7..4] This field defines 2nd channel in channel switch list.             */
    __IOM uint32_t chsw_2     : 4;            /*!< [11..8] This field defines 3rd channel in channel switch list.            */
    __IOM uint32_t chsw_3     : 4;            /*!< [15..12] This field defines 4th channel in channel switch list.           */
    __IOM uint32_t chsw_4     : 4;            /*!< [19..16] This field defines 5th channel in channel switch list.           */
    __IOM uint32_t chsw_5     : 4;            /*!< [23..20] This field defines 6th channel in channel switch list.           */
    __IOM uint32_t chsw_6     : 4;            /*!< [27..24] This field defines 7th channel in channel switch list.           */
    __IOM uint32_t chsw_7     : 4;            /*!< [31..28] This field defines 8th channel in channel switch list.           */
  } b;                                        /*!< bit fields for adc_chsw_list_0 */
} adc_chsw_list_0_t, *padc_chsw_list_0_t;

/**
  \brief Union type to access adc_chsw_list_1 (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) ADC Channel Swtich List 1 Register                         */

  struct {
    __IOM uint32_t chsw_8     : 4;            /*!< [3..0] This field defines 9th channel in channel switch list.             */
    __IOM uint32_t chsw_9     : 4;            /*!< [7..4] This field defines 10th channel in channel switch list.            */
    __IOM uint32_t chsw_10    : 4;            /*!< [11..8] This field defines 11th channel in channel switch list.           */
    __IOM uint32_t chsw_11    : 4;            /*!< [15..12] This field defines 12th channel in channel switch list.          */
    __IOM uint32_t chsw_12    : 4;            /*!< [19..16] This field defines 13th channel in channel switch list.          */
    __IOM uint32_t chsw_13    : 4;            /*!< [23..20] This field defines 14th channel in channel switch list.          */
    __IOM uint32_t chsw_14    : 4;            /*!< [27..24] This field defines 15th channel in channel switch list.          */
    __IOM uint32_t chsw_15    : 4;            /*!< [31..28] This field defines 16th channel in channel switch list.          */
  } b;                                        /*!< bit fields for adc_chsw_list_1 */
} adc_chsw_list_1_t, *padc_chsw_list_1_t;

/**
  \brief Union type to access adc_rst_list (@ 0x00000040).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000040) ADC Reset List Register                                    */

  struct {
    __IOM uint32_t rst_list   : 1;            /*!< [0..0] This bit is to reset channel switch list or not.                   */
  } b;                                        /*!< bit fields for adc_rst_list */
} adc_rst_list_t, *padc_rst_list_t;

/**
  \brief Union type to access adc_auto_chsw_ctrl (@ 0x00000044).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000044) ADC Auto Channel Switch Control Register                   */

  struct {
    __IOM uint32_t auto_chsw_en : 1;          /*!< [0..0] This bit controls the automatic channel switch enabled
                                                   or not.                                                                   */
  } b;                                        /*!< bit fields for adc_auto_chsw_ctrl */
} adc_auto_chsw_ctrl_t, *padc_auto_chsw_ctrl_t;

/**
  \brief Union type to access adc_sw_trig (@ 0x00000048).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000048) ADC Software Trigger Register                              */

  struct {
    __IOM uint32_t sw_trig    : 1;            /*!< [0..0] This bit controls the ADC module to do a conersion.                */
  } b;                                        /*!< bit fields for adc_sw_trig */
} adc_sw_trig_t, *padc_sw_trig_t;

/**
  \brief Union type to access adc_last_item (@ 0x0000004C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000004C) ADC Last Item Register                                     */

  struct {
    __IM  uint32_t last_item  : 4;            /*!< [3..0] This field records the last conversion list item that
                                                   a conversion is done for.                                                 */
  } b;                                        /*!< bit fields for adc_last_item */
} adc_last_item_t, *padc_last_item_t;

/**
  \brief Union type to access adc_sts (@ 0x00000050).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000050) ADC Busy_Ready Status Register                             */

  struct {
    __IM  uint32_t busy       : 1;            /*!< [0..0] This bit reflects the ADC is busy or not.                          */
    __IM  uint32_t full       : 1;            /*!< [1..1] This bit reflects the ADC FIFO is full or not.                     */
    __IM  uint32_t empty      : 1;            /*!< [2..2] This bit reflects the ADC FIFO is empty or not.                    */
  } b;                                        /*!< bit fields for adc_sts */
} adc_sts_t, *padc_sts_t;

/**
  \brief Union type to access adc_intr_ctrl (@ 0x00000054).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000054) ADC Interrupt Control Register                             */

  struct {
    __IOM uint32_t it_cvlist_end_en : 1;      /*!< [0..0] This bit controls the interrupt is enbled or not when
                                                   a conversion of the last channel in the list is done.                     */
    __IOM uint32_t it_cv_end_en : 1;          /*!< [1..1] This bit controls the interrupt is enbled or not every
                                                   time a conversion is done.                                                */
    __IOM uint32_t it_chcv_end_en : 1;        /*!< [2..2] This bit controls the interrupt is enbled or not when
                                                   a particular channel conversion is done.                                  */
    __IOM uint32_t it_fifo_full_en : 1;       /*!< [3..3] This bit controls the interrupt is enabled or not when
                                                   a FIFO full state takes place.                                            */
    __IOM uint32_t it_fifo_over_en : 1;       /*!< [4..4] This bit controls the interrupt is enabled or not when
                                                   a FIFO overflow state takes place.                                        */
    __IOM uint32_t it_fifo_empty_en : 1;      /*!< [5..5] This bit controls the interrupt is enabled or not when
                                                   a FIFO empty state takes place.                                           */
    __IOM uint32_t it_dat_ovw_en : 1;         /*!< [6..6] This bit controls the interrupt is enabled or not when
                                                   a data overwritten situation takes place.                                 */
    __IOM uint32_t it_err_en  : 1;            /*!< [7..7] This bit controls the interrupt is enabled or not when
                                                   an error state takes place.                                               */
    __IOM uint32_t it_comp_ch0_en : 1;        /*!< [8..8] This bit controls the interrupt is enabled or not when
                                                   channel 0 comparison criterion matches.                                   */
    __IOM uint32_t it_comp_ch1_en : 1;        /*!< [9..9] This bit controls the interrupt is enabled or not when
                                                   channel 1 comparison criterion matches.                                   */
    __IOM uint32_t it_comp_ch2_en : 1;        /*!< [10..10] This bit controls the interrupt is enabled or not when
                                                   channel 2 comparison criterion matches.                                   */
    __IOM uint32_t it_comp_ch3_en : 1;        /*!< [11..11] This bit controls the interrupt is enabled or not when
                                                   channel 3 comparison criterion matches.                                   */
    __IOM uint32_t it_comp_ch4_en : 1;        /*!< [12..12] This bit controls the interrupt is enabled or not when
                                                   channel 4 comparison criterion matches.                                   */
    __IOM uint32_t it_comp_ch5_en : 1;        /*!< [13..13] This bit controls the interrupt is enabled or not when
                                                   channel 5 comparison criterion matches.                                   */
    __IOM uint32_t it_comp_ch6_en : 1;        /*!< [14..14] This bit controls the interrupt is enabled or not when
                                                   channel 6 comparison criterion matches.                                   */
    __IOM uint32_t it_comp_ch7_en : 1;        /*!< [15..15] This bit controls the interrupt is enabled or not when
                                                   channel 7 comparison criterion matches.                                   */
    __IOM uint32_t it_comp_ch8_en : 1;        /*!< [16..16] This bit controls the interrupt is enabled or not when
                                                   channel 8 comparison criterion matches.                                   */
    __IOM uint32_t it_comp_ch9_en : 1;        /*!< [17..17] This bit controls the interrupt is enabled or not when
                                                   channel 9 comparison criterion matches.                                   */
  } b;                                        /*!< bit fields for adc_intr_ctrl */
} adc_intr_ctrl_t, *padc_intr_ctrl_t;

/**
  \brief Union type to access adc_intr_raw_sts (@ 0x00000058).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000058) ADC Interrupt RAW Status Register                          */

  struct {
    __IM  uint32_t it_cvlist_end : 1;         /*!< [0..0] This bit is the raw status of channel conversion list
                                                   end interrupt.                                                            */
    __IM  uint32_t it_cv_end  : 1;            /*!< [1..1] This bit is the raw status of each conversion end interrupt.       */
    __IM  uint32_t it_chcv_end : 1;           /*!< [2..2] This bit is the raw status of particular channel conversion
                                                   end interrupt.                                                            */
    __IM  uint32_t it_fifo_full : 1;          /*!< [3..3] This bit is the raw status of FIFO full interrupt.                 */
    __IM  uint32_t it_fifo_over : 1;          /*!< [4..4] This bit is the raw status of FIFO overflow interrupt.             */
    __IM  uint32_t it_fifo_empty : 1;         /*!< [5..5] This bit is the raw status of FIFO empty interrupt.                */
    __IM  uint32_t it_dat_ovw : 1;            /*!< [6..6] This bit is the raw status of global data register overwritten
                                                   interrupt.                                                                */
    __IM  uint32_t it_err     : 1;            /*!< [7..7] This bit is the raw status of error interrupt.                     */
    __IM  uint32_t it_comp_ch0 : 1;           /*!< [8..8] This bit is the raw status of channel 0 comparison interrupt.      */
    __IM  uint32_t it_comp_ch1 : 1;           /*!< [9..9] This bit is the raw status of channel 1 comparison interrupt.      */
    __IM  uint32_t it_comp_ch2 : 1;           /*!< [10..10] This bit is the raw status of channel 2 comparison
                                                   interrupt.                                                                */
    __IM  uint32_t it_comp_ch3 : 1;           /*!< [11..11] This bit is the raw status of channel 3 comparison
                                                   interrupt.                                                                */
    __IM  uint32_t it_comp_ch4 : 1;           /*!< [12..12] This bit is the raw status of channel 4 comparison
                                                   interrupt.                                                                */
    __IM  uint32_t it_comp_ch5 : 1;           /*!< [13..13] This bit is the raw status of channel 5 comparison
                                                   interrupt.                                                                */
    __IM  uint32_t it_comp_ch6 : 1;           /*!< [14..14] This bit is the raw status of channel 6 comparison
                                                   interrupt.                                                                */
    __IM  uint32_t it_comp_ch7 : 1;           /*!< [15..15] This bit is the raw status of channel 7 comparison
                                                   interrupt.                                                                */
    __IM  uint32_t it_comp_ch8 : 1;           /*!< [16..16] This bit is the raw status of channel 8 comparison
                                                   interrupt.                                                                */
    __IM  uint32_t it_comp_ch9 : 1;           /*!< [17..17] This bit is the raw status of channel 9 comparison
                                                   interrupt.                                                                */
  } b;                                        /*!< bit fields for adc_intr_raw_sts */
} adc_intr_raw_sts_t, *padc_intr_raw_sts_t;

/**
  \brief Union type to access adc_intr_sts (@ 0x0000005C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000005C) ADC Interrupt Status Register                              */

  struct {
    __IOM uint32_t it_cvlist_end : 1;         /*!< [0..0] This bit is the status of channel conversion list end
                                                   interrupt.                                                                */
    __IOM uint32_t it_cv_end  : 1;            /*!< [1..1] This bit is the status of each conversion end interrupt.           */
    __IOM uint32_t it_chcv_end : 1;           /*!< [2..2] This bit is the status of particular channel conversion
                                                   end interrupt.                                                            */
    __IOM uint32_t it_fifo_full : 1;          /*!< [3..3] This bit is the status of FIFO full interrupt.                     */
    __IOM uint32_t it_fifo_over : 1;          /*!< [4..4] This bit is the status of FIFO overflow interrupt.                 */
    __IOM uint32_t it_fifo_empty : 1;         /*!< [5..5] This bit is the status of FIFO empty interrupt.                    */
    __IOM uint32_t it_dat_ovw : 1;            /*!< [6..6] This bit is the status of global data register overwritten
                                                   interrupt.                                                                */
    __IOM uint32_t it_err     : 1;            /*!< [7..7] This bit is the status of error interrupt.                         */
    __IOM uint32_t it_comp_ch0 : 1;           /*!< [8..8] This bit is the status of channel 0 comparison interrupt.          */
    __IOM uint32_t it_comp_ch1 : 1;           /*!< [9..9] This bit is the status of channel 1 comparison interrupt.          */
    __IOM uint32_t it_comp_ch2 : 1;           /*!< [10..10] This bit is the status of channel 2 comparison interrupt.        */
    __IOM uint32_t it_comp_ch3 : 1;           /*!< [11..11] This bit is the status of channel 3 comparison interrupt.        */
    __IOM uint32_t it_comp_ch4 : 1;           /*!< [12..12] This bit is the status of channel 4 comparison interrupt.        */
    __IOM uint32_t it_comp_ch5 : 1;           /*!< [13..13] This bit is the status of channel 5 comparison interrupt.        */
    __IOM uint32_t it_comp_ch6 : 1;           /*!< [14..14] This bit is the status of channel 6 comparison interrupt.        */
    __IOM uint32_t it_comp_ch7 : 1;           /*!< [15..15] This bit is the status of channel 7 comparison interrupt.        */
    __IOM uint32_t it_comp_ch8 : 1;           /*!< [16..16] This bit is the status of channel 8 comparison interrupt.        */
    __IOM uint32_t it_comp_ch9 : 1;           /*!< [17..17] This bit is the status of channel 9 comparison interrupt.        */
  } b;                                        /*!< bit fields for adc_intr_sts */
} adc_intr_sts_t, *padc_intr_sts_t;

/**
  \brief Union type to access adc_it_chno_con (@ 0x00000060).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000060) ADC Conversion Interrupt Channel Number Configuration
                                                                  Register                                                   */

  struct {
    __IOM uint32_t it_chno_con : 4;           /*!< [3..0] This field defines that ADC module should send interrupt
                                                   signal to system when a conversion which of channel number
                                                   is the same as this field. This register is only valid
                                                   when BIT_ADC_IT_CHCV_END_EN is set.                                       */
  } b;                                        /*!< bit fields for adc_it_chno_con */
} adc_it_chno_con_t, *padc_it_chno_con_t;

/**
  \brief Union type to access adc_full_lvl (@ 0x00000064).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000064) ADC FIFO Full Level Register                               */

  struct {
    __IOM uint32_t full_lvl   : 6;            /*!< [5..0] This field defines the FIFO full entry threshold level
                                                   and it is used for FIFO full interrupt. It should be set
                                                   according to ADC FIFO depth.                                              */
  } b;                                        /*!< bit fields for adc_full_lvl */
} adc_full_lvl_t, *padc_full_lvl_t;

/**
  \brief Union type to access adc_trig_timer_sel (@ 0x00000068).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000068) ADC Trigger Timer Select Register                          */

  struct {
    __IOM uint32_t trig_timer_sel : 3;        /*!< [2..0] This field defines which timer channel would be used
                                                   to make ADC module do a conversion.                                       */
  } b;                                        /*!< bit fields for adc_trig_timer_sel */
} adc_trig_timer_sel_t, *padc_trig_timer_sel_t;

/**
  \brief Union type to access adc_dat_global (@ 0x0000006C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000006C) ADC Global Data Register                                   */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of a conversion
                                                   channel in the list.                                                      */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in BIT_ADC_DATA_GLOBAL takes place.                             */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_glb.                                             */
    __IOM uint32_t ch         : 4;            /*!< [21..18] This field indicates which channel data is in dat_glb            */
  } b;                                        /*!< bit fields for adc_dat_global */
} adc_dat_global_t, *padc_dat_global_t;

/**
  \brief Union type to access adc_dat_ch0 (@ 0x00000070).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000070) ADC Channel 0 Data Register                                */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of channel
                                                   0.                                                                        */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in dat_ch0 takes place.                                         */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_ch0.                                             */
  } b;                                        /*!< bit fields for adc_dat_ch0 */
} adc_dat_ch0_t, *padc_dat_ch0_t;

/**
  \brief Union type to access adc_dat_ch1 (@ 0x00000074).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000074) ADC Channel 1 Data Register                                */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of channel
                                                   1.                                                                        */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in dat_ch1 takes place.                                         */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_ch1.                                             */
  } b;                                        /*!< bit fields for adc_dat_ch1 */
} adc_dat_ch1_t, *padc_dat_ch1_t;

/**
  \brief Union type to access adc_dat_ch2 (@ 0x00000078).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000078) ADC Channel 2 Data Register                                */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of channel
                                                   2.                                                                        */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in dat_ch2 takes place.                                         */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_ch2.                                             */
  } b;                                        /*!< bit fields for adc_dat_ch2 */
} adc_dat_ch2_t, *padc_dat_ch2_t;

/**
  \brief Union type to access adc_dat_ch3 (@ 0x0000007C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000007C) ADC Channel 3 Data Register                                */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of channel
                                                   3.                                                                        */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in dat_ch3 takes place.                                         */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_ch3.                                             */
  } b;                                        /*!< bit fields for adc_dat_ch3 */
} adc_dat_ch3_t, *padc_dat_ch3_t;

/**
  \brief Union type to access adc_dat_ch4 (@ 0x00000080).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000080) ADC Channel 4 Data Register                                */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of channel
                                                   4.                                                                        */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in dat_ch4 takes place.                                         */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_ch4.                                             */
  } b;                                        /*!< bit fields for adc_dat_ch4 */
} adc_dat_ch4_t, *padc_dat_ch4_t;

/**
  \brief Union type to access adc_dat_ch5 (@ 0x00000084).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000084) ADC Channel 5 Data Register                                */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of channel
                                                   5.                                                                        */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in dat_ch5 takes place.                                         */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_ch5.                                             */
  } b;                                        /*!< bit fields for adc_dat_ch5 */
} adc_dat_ch5_t, *padc_dat_ch5_t;

/**
  \brief Union type to access adc_dat_ch6 (@ 0x00000088).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000088) ADC Channel 6 Data Register                                */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of channel
                                                   6.                                                                        */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in dat_ch6 takes place.                                         */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_ch6.                                             */
  } b;                                        /*!< bit fields for adc_dat_ch6 */
} adc_dat_ch6_t, *padc_dat_ch6_t;

/**
  \brief Union type to access adc_dat_ch7 (@ 0x0000008C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000008C) ADC Channel 7 Data Register                                */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of channel
                                                   7.                                                                        */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in dat_ch7 takes place.                                         */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_ch7.                                             */
  } b;                                        /*!< bit fields for adc_dat_ch7 */
} adc_dat_ch7_t, *padc_dat_ch7_t;

/**
  \brief Union type to access adc_dat_ch8 (@ 0x00000090).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000090) ADC Channel 8 Data Register                                */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of channel
                                                   8.                                                                        */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in dat_ch8 takes place.                                         */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_ch8.                                             */
  } b;                                        /*!< bit fields for adc_dat_ch8 */
} adc_dat_ch8_t, *padc_dat_ch8_t;

/**
  \brief Union type to access adc_dat_ch9 (@ 0x00000094).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000094) ADC Channel 9 Data Register                                */

  struct {
    __IOM uint32_t dat        : 10;           /*!< [9..0] This field contains the newest conversion data of channel
                                                   9.                                                                        */
    __IM  uint32_t            : 6;
    __IOM uint32_t ovw        : 1;            /*!< [16..16] This bit indicates that there is a data overwritten
                                                   situation in dat_ch9 takes place.                                         */
    __IOM uint32_t rdy        : 1;            /*!< [17..17] This field indicates that a conversion is done. And
                                                   its data is put into dat_ch9.                                             */
  } b;                                        /*!< bit fields for adc_dat_ch9 */
} adc_dat_ch9_t, *padc_dat_ch9_t;

/**
  \brief Union type to access adc_dma_con (@ 0x00000098).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000098) ADC DMA Control Register                                   */

  struct {
    __IOM uint32_t en         : 1;            /*!< [0..0] This bit controls that DMA function of ADC is enabled
                                                   or not.                                                                   */
    __IM  uint32_t            : 7;
    __IOM uint32_t lvl        : 6;            /*!< [13..8] This field defines the FIFO threshold level that ADC
                                                   module should make a DMA request to DMA module.                           */
  } b;                                        /*!< bit fields for adc_dma_con */
} adc_dma_con_t, *padc_dma_con_t;

/**
  \brief Union type to access adc_flr (@ 0x0000009C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000009C) ADC FIFO Level Register                                    */

  struct {
    __IOM uint32_t flr        : 7;            /*!< [6..0] This field records the current ADC FIFO entry number.              */
  } b;                                        /*!< bit fields for adc_flr */
} adc_flr_t, *padc_flr_t;

/**
  \brief Union type to access adc_clr_fifo (@ 0x000000A0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A0) ADC Clear FIFO Register                                    */

  struct {
    __IOM uint32_t clr_fifo   : 1;            /*!< [0..0] This bit is used to clear FIFO contents and makes it
                                                   to the default status.                                                    */
  } b;                                        /*!< bit fields for adc_clr_fifo */
} adc_clr_fifo_t, *padc_clr_fifo_t;

/**
  \brief Union type to access adc_clk_div (@ 0x000000A4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A4) ADC Clock Division Register                                */

  struct {
    __IOM uint32_t clk_div    : 3;            /*!< [2..0] This field defines clock divider level of ADC module.              */
  } b;                                        /*!< bit fields for adc_clk_div */
} adc_clk_div_t, *padc_clk_div_t;

/**
  \brief Union type to access adc_dly_cnt (@ 0x000000A8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A8) ADC Delay Couont Register                                  */

  struct {
    __IOM uint32_t dly_cnt    : 4;            /*!< [3..0] This field defines channel switch delay count.                     */
  } b;                                        /*!< bit fields for adc_dly_cnt */
} adc_dly_cnt_t, *padc_dly_cnt_t;

/**
  \brief Union type to access adc_pwr_ctrl (@ 0x000000AC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000AC) ADC Power Control Register                                 */

  struct {
    __IOM uint32_t pwr_ctrl   : 1;            /*!< [0..0] This field is used to power control.                               */
  } b;                                        /*!< bit fields for adc_pwr_ctrl */
} adc_pwr_ctrl_t, *padc_pwr_ctrl_t;

/**
  \brief Union type to access adc_ana_ctrl (@ 0x000000B0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000B0) ADC Analog Control Register                                */

  struct {
    __IOM uint32_t pwr_cut    : 1;            /*!< [0..0] This field is for analog usage.                                    */
    __IOM uint32_t pwr        : 1;            /*!< [1..1] This field is for analog usage.                                    */
    __IOM uint32_t pwr_ref    : 1;            /*!< [2..2] This field is for analog usage.                                    */
    __IOM uint32_t ck         : 1;            /*!< [3..3] This field is for analog usage.                                    */
    __IOM uint32_t dly        : 1;            /*!< [4..4] This field is for analog usage.                                    */
    __IOM uint32_t vref_sel   : 2;            /*!< [6..5] This field is for analog usage.                                    */
    __IOM uint32_t revckda    : 1;            /*!< [7..7] This field is for analog usage.                                    */
    __IOM uint32_t mpdec      : 2;            /*!< [9..8] This field is for analog usage.                                    */
    __IOM uint32_t meta       : 1;            /*!< [10..10] This field is for analog usage.                                  */
    __IOM uint32_t ch0_sel    : 2;            /*!< [12..11] This field is for analog usage.                                  */
    __IOM uint32_t ch1_sel    : 2;            /*!< [14..13] This field is for analog usage.                                  */
    __IOM uint32_t ch2_sel    : 2;            /*!< [16..15] This field is for analog usage.                                  */
    __IOM uint32_t ch3_sel    : 2;            /*!< [18..17] This field is for analog usage.                                  */
  } b;                                        /*!< bit fields for adc_ana_ctrl */
} adc_ana_ctrl_t, *padc_ana_ctrl_t;

/**
  \brief Union type to access adc_ana_sd (@ 0x000000B4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000B4) ADC Signal Detect Register                                 */

  struct {
    __IOM uint32_t pwr_sd     : 1;            /*!< [0..0] This field is for analog usage.                                    */
    __IOM uint32_t sd_pse_edge : 1;           /*!< [1..1] This field is for analog usage.                                    */
    __IOM uint32_t sel_vrefh  : 5;            /*!< [6..2] This field is for analog usage.                                    */
    __IOM uint32_t sel_vrefl  : 5;            /*!< [11..7] This field is for analog usage.                                   */
    __IOM uint32_t pwr_bg     : 1;            /*!< [12..12] This field is for analog usage.                                  */
    __IOM uint32_t pwr_i      : 1;            /*!< [13..13] This field is for analog usage.                                  */
    __IOM uint32_t pwr_mbias  : 1;            /*!< [14..14] This field is for analog usage.                                  */
  } b;                                        /*!< bit fields for adc_ana_sd */
} adc_ana_sd_t, *padc_ana_sd_t;

/** @} */ /* End of group ls_hal_adc_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_ADC_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BLP_ADC_TYPE_H_

