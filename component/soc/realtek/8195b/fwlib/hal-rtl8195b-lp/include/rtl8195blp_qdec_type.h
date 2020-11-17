/**************************************************************************//**
 * @file      rtl8195blp_qdec_type.h
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

#ifndef _RTL8195BLP_QDEC_TYPE_H_
#define _RTL8195BLP_QDEC_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_QDEC_REG_TYPE

/**
 * @addtogroup ls_hal_qdec_reg QDEC Registers.
 * @ingroup ls_hal_qdec
 * @{
 */

/**
  \brief Union type to access qdec_clksel (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) Clock Configuration Register                               */

  struct {
    __IOM uint32_t dbn_tm     : 11;           /*!< [10..0] De-bounce timer configuration.                                    */

    __IM  uint32_t            : 1;
    __IOM uint32_t smp_div    : 5;            /*!< [16..12] Divider for input signal sampling clock Sampling Clock
                                                   = source-clock/(smp_div+1)                                                */
  } b;                                        /*!< bit fields for qdec_clksel */
} qdec_clksel_t, *pqdec_clksel_t;

/**
  \brief Union type to access qdec_ctrl (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) Control Register                                           */

  struct {
    __IOM uint32_t ini_phase  : 2;            /*!< [1..0] The manual initial phase state of the quadrature decoder:(valid
                                                   only mnu_ini = 1) 00: Phase state of (A, B) is (0, 0) 01:
                                                   Phase state of (A, B) is (0, 1) 10: Phase state of (A,
                                                   B) is (1, 0) 11: Phase state of (A, B) is (1, 1)                          */
    __IOM uint32_t mnu_ini    : 1;            /*!< [2..2] Initial the phase state of the quadrature decoder: 1
                                                   : manual set 0 : auto load                                                */
    __IOM uint32_t pchg_lv    : 2;            /*!< [4..3] Position changed interrupt trigger level. 00: +/- 1 01:
                                                   +/- 2 10: +/- 4 11: reserved                                              */
    __IM  uint32_t            : 7;
    __IOM uint32_t dbn_en     : 1;            /*!< [12..12] Input signal (PHA, PHB & IDX) de-bouncing enable control:
                                                   1 : enable de-bounce 0 : disable de-bounce                                */
    __IOM uint32_t cnt_sc     : 1;            /*!< [13..13] The position accumulation counter to be increased/decreased
                                                   by: 0: 1 phase 1: 2 phases. Only phase A edges are counted.               */
    __IOM uint32_t il_int_en  : 1;            /*!< [14..14] Illegal-state detected interrupt enable control: 1
                                                   : enable interrupt 0 : disable interrupt                                  */
    __IOM uint32_t uf_int_en  : 1;            /*!< [15..15] Position counter value underflow interrupt enable control:
                                                   1 : enable interrupt 0 : disable interrupt                                */
    __IOM uint32_t of_int_en  : 1;            /*!< [16..16] Position counter value overflow interrupt enable control:
                                                   1 : enable interrupt 0 : disable interrupt                                */
    __IOM uint32_t ct_int_en  : 1;            /*!< [17..17] Position counter value changed interrupt enable control:
                                                   1 : enable interrupt 0 : disable interrupt                                */
    __IOM uint32_t dr_int_en  : 1;            /*!< [18..18] Movement direction changed interrupt enable control:
                                                   1 : enable interrupt 0 : disable interrupt                                */
    __IOM uint32_t pc_int_en  : 1;            /*!< [19..19] Position counter comparing interrupt enable control:
                                                   1 : enable interrupt 0 : disable interrupt                                */
    __IOM uint32_t rof_int_en : 1;            /*!< [20..20] Rotation counter overflow interrupt enable control:
                                                   1 : enable interrupt 0 : disable interrupt                                */
    __IOM uint32_t ruf_int_en : 1;            /*!< [21..21] Rotation counter underflow interrupt enable control:
                                                   1 : enable interrupt 0 : disable interrupt                                */
    __IOM uint32_t idx_int_en : 1;            /*!< [22..22] Index pulse signal interrupt enable control: 1 : enable
                                                   interrupt 0 : disable interrupt                                           */
    __IOM uint32_t pce_int_en : 1;            /*!< [23..23] Position counter error interrupt enable control: 1
                                                   : enable interrupt 0 : disable interrupt This interrupt
                                                   will be asserted when the index pulse signal is detected
                                                   but the position counter is not equal to 0.                               */
    __IOM uint32_t rc_int_en  : 1;            /*!< [24..24] Rotation counter comparing interrupt enable control:
                                                   1 : enable interrupt 0 : disable interrupt                                */
    __IM  uint32_t            : 2;
    __IOM uint32_t qall_rst   : 1;            /*!< [27..27] Quadrature decoder all reset: 0 : quadrature decoder
                                                   is not in reset. 1 : write 1 to this bit will reset the
                                                   state machine and all functions                                           */
    __IOM uint32_t rc_mod     : 1;            /*!< [28..28] Rotation counter mode: 0 : the rotation counter is
                                                   used to accumulate the number of index event occurred with
                                                   direction(+/-). The index event is the same condition as
                                                   the index reset according to auto reset or index reset
                                                   setting. 1 : the rotation counter is used to accumulate
                                                   the number of the position counter overflow(+)/underflow(-).              */
    __IOM uint32_t rc_rst     : 1;            /*!< [29..29] Rotation counter reset: 0 : rotation counter is not
                                                   in reset 1 : write 1 to this bit will reset the rotation
                                                   counter to 0 The rotation counter reset only can be performed
                                                   when this quadrature decoder is disabled (axis_en = 0).                   */
    __IOM uint32_t pc_rst     : 1;            /*!< [30..30] Position counter reset: 0 : position counter is not
                                                   in reset (normal active) 1 : write 1 to this bit will reset
                                                   the position counter to 0 The position counter reset only
                                                   can be performed when this quadrature decoder is disabled
                                                   (axis_en = 0).                                                            */
    __IOM uint32_t axis_en    : 1;            /*!< [31..31] Quadrature decoder enable control: 1 : enable 0 : disable
                                                   When the CPU write 0(disable) to this bit, the HW should
                                                   do: 1. source clock is gated 2. Clear all interrupt status                */
  } b;                                        /*!< bit fields for qdec_ctrl */
} qdec_ctrl_t, *pqdec_ctrl_t;

/**
  \brief Union type to access qdec_mpc (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) Max Position Counter Register                              */

  struct {
    __IOM uint32_t mpc        : 16;           /*!< [15..0] The maximum value of the position counter.                        */
    __IOM uint32_t pcc        : 16;           /*!< [31..16] The value to be compared with the position counter.              */
  } b;                                        /*!< bit fields for qdec_mpc */
} qdec_mpc_t, *pqdec_mpc_t;

/**
  \brief Union type to access qdec_rc (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) Rotation Compare Register                                  */

  struct {
    __IOM uint32_t rcc        : 12;           /*!< [11..0] The value to be compared with the rotation counter.               */
  } b;                                        /*!< bit fields for qdec_rc */
} qdec_rc_t, *pqdec_rc_t;

/**
  \brief Union type to access qdec_pc (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) Position Counter Register                                  */

  struct {
    __IM  uint32_t pc         : 16;           /*!< [15..0] The position accumulation counter.                                */
    __IM  uint32_t dir        : 1;            /*!< [16..16] The movement direction. 0 : decrease 1 : increase                */
    __IM  uint32_t als        : 1;            /*!< [17..17] The status of auto load to set initial phase 1 : auto
                                                   load done 0 : auto load on-going                                          */
    __IM  uint32_t sta        : 2;            /*!< [19..18] The quadrature decoder phase state.Current state of
                                                   (A, B) phase.                                                             */
    __IM  uint32_t rc         : 12;           /*!< [31..20] The rotation counter.                                            */
  } b;                                        /*!< bit fields for qdec_pc */
} qdec_pc_t, *pqdec_pc_t;

/**
  \brief Union type to access qdec_isc (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) Index Signal Configuration Register                        */

  struct {
    __IOM uint32_t pos_rst_phb : 1;           /*!< [0..0] To assign the state of the phase_B signal for the accumulation
                                                   position counter reseting. When cnt_sc is 1, this setting
                                                   is invalid. (pos_rst_pha, pos_rst_phb) = (0, 0) : Reset
                                                   when phase_A signal is 0 and phase_B signale is 0 (pos_rst_pha,
                                                   pos_rst_phb) = (0, 1) : Reset when phase_A signal is 0
                                                   and phase_B signale is 1 (pos_rst_pha, pos_rst_phb) = (1,
                                                   1) : Reset when phase_A signal is 1 and phase_B signale
                                                   is 1 (pos_rst_pha, pos_rst_phb) = (1, 0) : Reset when phase_A
                                                   signal is 1 and phase_B signale is 0                                      */
    __IOM uint32_t pos_rst_pha : 1;           /*!< [1..1] To assign the state of the phase_A signal for the accumulation
                                                   counter reseting. When cnt_sc is 1, the reset is only according
                                                   to pos_rst_pha.                                                           */
    __IM  uint32_t            : 1;
    __IOM uint32_t pos_rst_en : 2;            /*!< [4..3] Enable the accumulation position counter to be reset
                                                   by the Index pulse signal with a given phase_A and/or phase_B
                                                   state. 00: Disabled, no position counter reset on the index
                                                   pulse signal 01: Reset the position counter on the 1st
                                                   index pulse signal only. 10: Reset the position counter
                                                   on every index pulse signal. 11: Reserved                                 */
    __IOM uint32_t idx_inv    : 1;            /*!< [5..5] Inverse the index pulse input signal. 0: no inverse 1:
                                                   inverse the index pulse signal input                                      */
    __IOM uint32_t idx_auto_en : 1;           /*!< [6..6] Auto-index mechanism. 0: Disable. 1: Enable. When enable
                                                   this function, ignore the setting pos_rst_pha, and pos_rst_phb.           */
    __IM  uint32_t            : 24;
    __IOM uint32_t idx_en     : 1;            /*!< [31..31] Enable the index pulse detection. 0: Disable. The index
                                                   pulse signal detection is disabled, all index pulse signal
                                                   related configurations should be ignored. 1: Enable.                      */
  } b;                                        /*!< bit fields for qdec_isc */
} qdec_isc_t, *pqdec_isc_t;

/**
  \brief Union type to access qdec_vctrl (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) Velocity Control Register                                  */

  struct {
    __IOM uint32_t vmuc_en    : 1;            /*!< [0..0] The velocity measurement unit of measuring the velocity
                                                   counter enable control: 0: disable 1: enable                              */
    __IOM uint32_t vmut_en    : 1;            /*!< [1..1] The velocity measurement unit of measuring the edge time
                                                   enable control: 0: disable 1: enable                                      */
    __IOM uint32_t vmuc_rst   : 1;            /*!< [2..2] Reset the velocity measurement unit of measuring the
                                                   velocity counter: 0: it is not in reset 1: write 1 to this
                                                   bit will reset this unit. Reset the velocity counter, reset
                                                   the velocity counter capture register, and reload the velocity
                                                   timer.                                                                    */
    __IOM uint32_t vmut_rst   : 1;            /*!< [3..3] Reset the velocity measurement unit of measuring the
                                                   edge time: 0: it is not in reset 1: write 1 to this bit
                                                   will reset this unit. Reset the edge timer to zero, reset
                                                   the edge timer capture register, and the prescale edge
                                                   clk restarts to count.                                                    */
    __IOM uint32_t vccap_int_en : 1;          /*!< [4..4] Velocity counter capture interrupt enable control: 0:
                                                   disable interrupt 1: enable interrupt When the velocity
                                                   timer reaches zero, the velocity counter register and the
                                                   position counter are captured in capture registers.                       */
    __IOM uint32_t etcap_int_en : 1;          /*!< [5..5] Edge timer capture interrupt enable control: 0: disable
                                                   interrupt 1: enable interrupt When generate the edge prescale
                                                   event, the edge timer register is captured in the edge
                                                   timer capture register.                                                   */
    __IOM uint32_t vlowlmt_int_en : 1;        /*!< [6..6] Velocity lower limit interrupt enable control: 0: disable
                                                   interrupt 1: enable interrupt                                             */
    __IOM uint32_t vuplmt_int_en : 1;         /*!< [7..7] Velocity upper limit interrupt enable control: 0: disable
                                                   interrupt 1: enable interrupt                                             */
    __IOM uint32_t eterr_int_en : 1;          /*!< [8..8] Edge Timer error interrupt enable control: 0: disable
                                                   interrupt 1: enable interrupt When the edge timer is overflow,
                                                   this interrupt will be asserted.                                          */
    __IOM uint32_t vmuc_mode  : 1;            /*!< [9..9] The velocity measurement unit of measuring the velocity
                                                   counter mode control: 0: the counter value uses the absolute
                                                   value from the decoder 1: the counter value uses the same
                                                   value of the position counter                                             */
    __IM  uint32_t            : 6;
    __IOM uint32_t vt_div     : 8;            /*!< [23..16] Divider for the velocity timer clock Velocity Timer
                                                   Clock = source-clock/(vt_div+1)                                           */
    __IM  uint32_t            : 4;
    __IOM uint32_t eclk_div   : 4;            /*!< [31..28] Edge clock prescale control: 0000: edge prescale event
                                                   = Eclk / 1; 0001: edge prescale event = Eclk / 2; etc.
                                                   1011: edge prescale event = Eclk / 2048; others reserved                  */
  } b;                                        /*!< bit fields for qdec_vctrl */
} qdec_vctrl_t, *pqdec_vctrl_t;

/**
  \brief Union type to access qdec_vc (@ 0x0000001C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000001C) Velocity Counter Register                                  */

  struct {
    __IM  uint32_t vc         : 16;           /*!< [15..0] This velocity counter will be increased or decreased
                                                   (depends on the direction) by one for every 1 or 2 (depends
                                                   on cnt_sc) phase state changed.                                           */
  } b;                                        /*!< bit fields for qdec_vc */
} qdec_vc_t, *pqdec_vc_t;

/**
  \brief Union type to access qdec_vccap (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) Velocity Counter Capture Register                          */

  struct {
    __IM  uint32_t vc_cap     : 16;           /*!< [15..0] When the velocity timer reaches zero, the velocity counter
                                                   register is captured in the velocity counter capture register.            */
  } b;                                        /*!< bit fields for qdec_vccap */
} qdec_vccap_t, *pqdec_vccap_t;

/**
  \brief Union type to access qdec_pccap (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) Position Counter Capture Register                          */

  struct {
    __IM  uint32_t pc_cap     : 16;           /*!< [15..0] When the velocity timer reaches zero, the position counter
                                                   register is captured in the position counter capture register.            */
  } b;                                        /*!< bit fields for qdec_pccap */
} qdec_pccap_t, *pqdec_pccap_t;

/**
  \brief Union type to access qdec_vtrld (@ 0x00000028).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000028) Velocity Time Reload Register                              */

  struct {
    __IOM uint32_t vtrld      : 16;           /*!< [15..0] When the velocity timer reaches zero, the velocity timer
                                                   register reloads this value.                                              */
  } b;                                        /*!< bit fields for qdec_vtrld */
} qdec_vtrld_t, *pqdec_vtrld_t;

/**
  \brief Union type to access qdec_vt (@ 0x0000002C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000002C) Velocity Timer Register                                    */

  struct {
    __IM  uint32_t vt         : 16;           /*!< [15..0] This is the velocity timer value of the down counter              */
  } b;                                        /*!< bit fields for qdec_vt */
} qdec_vt_t, *pqdec_vt_t;

/**
  \brief Union type to access qdec_vcomp (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) Velocity Compare Register                                  */

  struct {
    __IOM uint32_t vlowlmt    : 16;           /*!< [15..0] This is the velocity lower limit value                            */
    __IOM uint32_t vuplmt     : 16;           /*!< [31..16] This is the velocity upper limit value                           */
  } b;                                        /*!< bit fields for qdec_vcomp */
} qdec_vcomp_t, *pqdec_vcomp_t;

/**
  \brief Union type to access qdec_et (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) Edge Timer Register                                        */

  struct {
    __IM  uint32_t et         : 16;           /*!< [15..0] This is the edge timer value of the up counter                    */
  } b;                                        /*!< bit fields for qdec_et */
} qdec_et_t, *pqdec_et_t;

/**
  \brief Union type to access qdec_etcap (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) Edge Timer Capture Register                                */

  struct {
    __IM  uint32_t et_cap     : 16;           /*!< [15..0] When happen the edge clock capture event, the edge timer
                                                   register is captured in the edge timer capture register.                  */
  } b;                                        /*!< bit fields for qdec_etcap */
} qdec_etcap_t, *pqdec_etcap_t;

/**
  \brief Union type to access qdec_imr (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) Interrupt Mask Register                                    */

  struct {
    __IOM uint32_t ct_int_m   : 1;            /*!< [0..0] Counter value changed interrupt mask: 0: un-mask 1: mask           */
    __IOM uint32_t of_int_m   : 1;            /*!< [1..1] Position counter overflow interrupt mask: 0: un-mask
                                                   1: mask                                                                   */
    __IOM uint32_t uf_int_m   : 1;            /*!< [2..2] Position counter underflow interrupt mask: 0: un-mask
                                                   1: mask                                                                   */
    __IOM uint32_t il_int_m   : 1;            /*!< [3..3] Illegal state interrupt mask: 0: un-mask 1: mask                   */
    __IOM uint32_t dr_int_m   : 1;            /*!< [4..4] Direction changed interrupt mask: 0: un-mask 1: mask               */
    __IOM uint32_t pc_int_m   : 1;            /*!< [5..5] Position counter comparing interrupt mask: 0: un-mask
                                                   1: mask                                                                   */
    __IOM uint32_t rof_int_m  : 1;            /*!< [6..6] Rotation counter overflow interrupt mask: 0: un-mask
                                                   1: mask                                                                   */
    __IOM uint32_t ruf_int_m  : 1;            /*!< [7..7] Rotation counter underflow interrupt mask: 0: un-mask
                                                   1: mask                                                                   */
    __IOM uint32_t idx_int_m  : 1;            /*!< [8..8] Index pulse signal interrupt mask: 0: un-mask 1: mask
                                                   This interrupt will be asserted when the index pulse signal
                                                   present.                                                                  */
    __IOM uint32_t pce_int_m  : 1;            /*!< [9..9] Position counter error interrupt mask: 0: un-mask 1:
                                                   mask                                                                      */
    __IOM uint32_t vccap_int_m : 1;           /*!< [10..10] Velocity counter capture interrupt mask: 0: un-mask
                                                   1: mask                                                                   */
    __IOM uint32_t etcap_int_m : 1;           /*!< [11..11] Edge timer capture interrupt mask: 0: un-mask 1: mask            */
    __IOM uint32_t vlowlmt_int_m : 1;         /*!< [12..12] Velocity lower limit interrupt mask: 0: un-mask 1:
                                                   mask                                                                      */
    __IOM uint32_t vuplmt_int_m : 1;          /*!< [13..13] Velocity upper limit interrupt mask: 0: un-mask 1:
                                                   mask                                                                      */
    __IOM uint32_t eterr_int_m : 1;           /*!< [14..14] Edge Timer error interrupt mask: 0: un-mask 1: mask
                                                   When the edge timer is overflow, this interrupt will be
                                                   asserted.                                                                 */
    __IOM uint32_t rc_int_m   : 1;            /*!< [15..15] Rotation counter comparing interrupt mask: 0: un-mask
                                                   1: mask This interrupt will be asserted when the rotation
                                                   counter is equal to the value of rcc.                                     */
  } b;                                        /*!< bit fields for qdec_imr */
} qdec_imr_t, *pqdec_imr_t;

/**
  \brief Union type to access qdec_isr (@ 0x00000040).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000040) Interrupt Status Register                                  */

  struct {
    __IOM uint32_t ct_int_s   : 1;            /*!< [0..0] 0: no interrupt 1: interrupt pending                               */
    __IOM uint32_t of_int_s   : 1;            /*!< [1..1] 0: no interrupt 1: interrupt pending                               */
    __IOM uint32_t uf_int_s   : 1;            /*!< [2..2] 0: no interrupt 1: interrupt pending                               */
    __IOM uint32_t il_int_s   : 1;            /*!< [3..3] 0: no interrupt 1: interrupt pending                               */
    __IOM uint32_t dr_int_s   : 1;            /*!< [4..4] 0: no interrupt 1: interrupt pending                               */
    __IOM uint32_t pc_int_s   : 1;            /*!< [5..5] 0: no interrupt 1: interrupt pending                               */
    __IOM uint32_t rof_int_s  : 1;            /*!< [6..6] 0: no interrupt 1: interrupt pending                               */
    __IOM uint32_t ruf_int_s  : 1;            /*!< [7..7] 0: no interrupt 1: interrupt pending                               */
    __IOM uint32_t idx_int_s  : 1;            /*!< [8..8] 0: no interrupt 1: interrupt pending                               */
    __IOM uint32_t pce_int_s  : 1;            /*!< [9..9] 0: no interrupt 1: interrupt pending                               */
    __IOM uint32_t vccap_int_s : 1;           /*!< [10..10] 0: no interrupt 1: interrupt pending                             */
    __IOM uint32_t etcap_int_s : 1;           /*!< [11..11] 0: no interrupt 1: interrupt pending                             */
    __IOM uint32_t vlowlmt_int_s : 1;         /*!< [12..12] 0: no interrupt 1: interrupt pending                             */
    __IOM uint32_t vuplmt_int_s : 1;          /*!< [13..13] 0: no interrupt 1: interrupt pending                             */
    __IOM uint32_t eterr_int_s : 1;           /*!< [14..14] 0: no interrupt 1: interrupt pending                             */
    __IOM uint32_t rc_int_s   : 1;            /*!< [15..15] 0: no interrupt 1: interrupt pending                             */
  } b;                                        /*!< bit fields for qdec_isr */
} qdec_isr_t, *pqdec_isr_t;

/** @} */ /* End of group ls_hal_qdec_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_QDEC_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BLP_QDEC_TYPE_H_

