/**************************************************************************//**
 * @file      rtl8195bhp_sgpio_type.h
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

#ifndef _RTL8195BHP_SGPIO_TYPE_H_
#define _RTL8195BHP_SGPIO_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_SGPIO_REG_TYPE

/**
 * @addtogroup hs_hal_sgpio_reg SGPIO Registers.
 * @ingroup hs_hal_sgpio
 * @{
 */

/**
  \brief Union type to access sgpio_rxtmr_ctrl (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) RX Timer Control Register                                  */

  struct {
    __IOM uint32_t rxtmr_cen  : 1;            /*!< [0..0] 0: Disabled. The counters are disabled. 1: Enabled. RXTC
                                                   and RXPRTC are enabled.                                                   */
    __IOM uint32_t rxtmr_crst : 1;            /*!< [1..1] RXTC and RXPRTC are synchronously reset on the next positive
                                                   edge of PCLK. The counters remain reset until RXTMR_CEN
                                                   is returned to zero. 0: Disabled. Do nothing. 1: Enabled.                 */
    __IM  uint32_t            : 6;
    __IOM uint32_t rxtmredge_sel : 2;         /*!< [9..8] RXTC will start and RXTMR_CEN will be set according to
                                                   receiving the trigger. 00: Disabled. Do nothing. 01: Receive
                                                   rising edges. 02: Receive falling edges. 03: Receive both
                                                   edges.                                                                    */
  } b;                                        /*!< bit fields for sgpio_rxtmr_ctrl */
} sgpio_rxtmr_ctrl_t, *psgpio_rxtmr_ctrl_t;

/**
  \brief Union type to access sgpio_rxprval (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) RX Maximum Prescale Register                               */

  struct {
    __IOM uint32_t rxprval    : 16;           /*!< [15..0] Maximum value for the RX Prescale Counter                         */
  } b;                                        /*!< bit fields for sgpio_rxprval */
} sgpio_rxprval_t, *psgpio_rxprval_t;

/**
  \brief Union type to access sgpio_rxprtc (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) RX Timer Prescale Register                                 */

  struct {
    __IOM uint32_t rxprtc     : 16;           /*!< [15..0] RX Prescale Counter value.                                        */
  } b;                                        /*!< bit fields for sgpio_rxprtc */
} sgpio_rxprtc_t, *psgpio_rxprtc_t;

/**
  \brief Union type to access sgpio_rxtc (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) RX Timer Counter Register                                  */

  struct {
    __IOM uint32_t rxtc       : 16;           /*!< [15..0] RX Timer Counter value.                                           */
  } b;                                        /*!< bit fields for sgpio_rxtc */
} sgpio_rxtc_t, *psgpio_rxtc_t;

/**
  \brief Union type to access sgpio_rxmc (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) Position Counter Register                                  */

  struct {
    __IOM uint32_t rx_mr0i_en : 1;            /*!< [0..0] Generate an interrupt when RXMR0 matches the value in
                                                   the RXTC. 0: Disable 1: Enable                                            */
    __IOM uint32_t rx_mr0rst_en : 1;          /*!< [1..1] Reset RXTC when RXMR0 matches RXTC. 0: Disable 1: Enable           */
    __IOM uint32_t rx_mr0stop_en : 1;         /*!< [2..2] RXTC will stop and RXTMR_CEN will be cleared if RXMR0
                                                   matches RXTC. 0: Disable 1: Enable                                        */
    __IOM uint32_t rx_mr0sclk_en : 1;         /*!< [3..3] Generate a shift clock for RX Data Register when RXMR0
                                                   matches the value in the RXTC. 0: Disable 1: Enable                       */
    __IOM uint32_t rx_mr1i_en : 1;            /*!< [4..4] Generate an interrupt when RXMR1 matches the value in
                                                   the RXTC. 0: Disable 1: Enable                                            */
    __IOM uint32_t rx_mr1rst_en : 1;          /*!< [5..5] Reset RXTC when RXMR1 matches RXTC. 0: Disable 1: Enable           */
    __IOM uint32_t rx_mr1stop_en : 1;         /*!< [6..6] RXTC will stop and RXTMR_CEN will be cleared if RXMR1
                                                   matches RXTC. 0: Disable 1: Enable                                        */
    __IOM uint32_t rx_mr1sclk_en : 1;         /*!< [7..7] Generate a shift clock for RX Data Register when RXMR1
                                                   matches the value in the RXTC. 0: Disable 1: Enable                       */
    __IOM uint32_t rx_mr2i_en : 1;            /*!< [8..8] Generate an interrupt when RXMR2 matches the value in
                                                   the RXTC. 0: Disable 1: Enable                                            */
    __IOM uint32_t rx_mr2rst_en : 1;          /*!< [9..9] Reset RXTC when RXMR2 matches RXTC. 0: Disable 1: Enable           */
    __IOM uint32_t rx_mr2stop_en : 1;         /*!< [10..10] RXTC will stop and RXTMR_CEN will be cleared if RXMR2
                                                   matches RXTC. 0: Disable 1: Enable                                        */
    __IOM uint32_t rx_mr2sclk_en : 1;         /*!< [11..11] Generate a shift clock for RX Data Register when RXMR2
                                                   matches the value in the RXTC. 0: Disable 1: Enable                       */
    __IOM uint32_t rx_mr0mulrst_en : 1;       /*!< [12..12] Reset MULTC when RXMR0 matches RXTC. 0: Disable 1:
                                                   Enable                                                                    */
    __IOM uint32_t rx_mr0mulstop_en : 1;      /*!< [13..13] MULTC will stop and MULTMR_CEN will be cleared if RXMR0
                                                   matches RXTC. 0: Disable 1: Enable                                        */
    __IOM uint32_t rx_posrst_en : 1;          /*!< [14..14] Reset RXTC when each time RXPOSTC reaches 0x0.                   */
    __IOM uint32_t rx_posstop_en : 1;         /*!< [15..15] RXTC will stop and RXTMR_CEN will be cleared when each
                                                   time RXPOSTC reaches 0x0.                                                 */
  } b;                                        /*!< bit fields for sgpio_rxmc */
} sgpio_rxmc_t, *psgpio_rxmc_t;

/**
  \brief Union type to access sgpio_rxmr0 (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) RX Match Register 0                                        */

  struct {
    __IOM uint32_t rxmr0      : 16;           /*!< [15..0] RX timer counter match value.                                     */
  } b;                                        /*!< bit fields for sgpio_rxmr0 */
} sgpio_rxmr0_t, *psgpio_rxmr0_t;

/**
  \brief Union type to access sgpio_rxmr1 (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) RX Match Register 1                                        */

  struct {
    __IOM uint32_t rxmr1      : 16;           /*!< [15..0] RX timer counter match value.                                     */
  } b;                                        /*!< bit fields for sgpio_rxmr1 */
} sgpio_rxmr1_t, *psgpio_rxmr1_t;

/**
  \brief Union type to access sgpio_rxmr2 (@ 0x0000001C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000001C) RX Match Register 2                                        */

  struct {
    __IOM uint32_t rxmr2      : 16;           /*!< [15..0] RX timer counter match value.                                     */
  } b;                                        /*!< bit fields for sgpio_rxmr2 */
} sgpio_rxmr2_t, *psgpio_rxmr2_t;

/**
  \brief Union type to access sgpio_cap_ctrl (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) Capture Control Register                                   */

  struct {
    __IOM uint32_t cap_en     : 1;            /*!< [0..0] CAPR is loaded with the value of RXTC when there is an
                                                   event on the input. 0: Disable 1: Enable.                                 */
    __IOM uint32_t capi_en    : 1;            /*!< [1..1] The capture load event generates an interrupt. 0: Disable
                                                   1: Enable                                                                 */
    __IOM uint32_t capsrc_sel : 1;            /*!< [2..2] Select the capture trigger source. 0: RX input trigger
                                                   event 1: Multiple Counter match event                                     */
    __IOM uint32_t capfe_en   : 1;            /*!< [3..3] Capture on falling edge: a sequence of 1 then 0 causes
                                                   CAPR to be loaded with the contents of RXTC. 0: Disable
                                                   1: Enable                                                                 */
    __IOM uint32_t capre_en   : 1;            /*!< [4..4] Capture on rising edge: a sequence of 0 then 1 causes
                                                   CAPR to be loaded with the contents of RXTC. 0: Disable
                                                   1: Enable                                                                 */
    __IOM uint32_t cap_rxtcrst_en : 1;        /*!< [5..5] Reset RXTC when the capture trigger event happens. 0:
                                                   Disable 1: Enable                                                         */
    __IOM uint32_t cap_rxtcstop_en : 1;       /*!< [6..6] RXTC will stop and RXTMR_CEN will be cleared if the capture
                                                   trigger event happens. 0: Disable 1: Enable                               */
    __IOM uint32_t cap_cmpval_sel : 1;        /*!< [7..7] RXDATA receives value when CAPR is bigger than CAP_CMPVAL.
                                                   0: RXDATA receives 0 1: RXDATA receives 1                                 */
    __IOM uint32_t capvalid_en : 1;           /*!< [8..8] The valid match needs that RXTMR_CEN is enabled. 0: Need
                                                   to enable RXTMR_CEN. 1: Do not need to enable RXTMR_CEN.                  */
    __IM  uint32_t            : 7;
    __IOM uint32_t cap_cmpval : 16;           /*!< [31..16] Compare this value with CAPR                                     */
  } b;                                        /*!< bit fields for sgpio_cap_ctrl */
} sgpio_cap_ctrl_t, *psgpio_cap_ctrl_t;

/**
  \brief Union type to access sgpio_capr (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) Capture Register                                           */

  struct {
    __IM  uint32_t capr       : 16;           /*!< [15..0] RX timer counter capture value                                    */
  } b;                                        /*!< bit fields for sgpio_capr */
} sgpio_capr_t, *psgpio_capr_t;

/**
  \brief Union type to access sgpio_multmr_ctrl (@ 0x00000028).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000028) Multiple Timer Control Register                            */

  struct {
    __IOM uint32_t multmr_cen : 1;            /*!< [0..0] 0: Disabled. The counters are disabled. 1: Enabled. MULTC
                                                   and MULPRTC are enabled.                                                  */
    __IOM uint32_t multmr_crst : 1;           /*!< [1..1] The Timer Counter and the Prescale Counter are synchronously
                                                   reset on the next positive edge of PCLK. The counters remain
                                                   reset until MULTMR_CEN is returned to zero. 0: Disabled.
                                                   Do nothing. 1: Enabled.                                                   */
    __IM  uint32_t            : 6;
    __IOM uint32_t mulmode_en : 2;            /*!< [9..8] Counter/Timer Mode This field selects which rising PCLK
                                                   edges can increment MULPRTC or clear MULPRTC and increment
                                                   MULTC. Timer Mode: MULTC is incremented when MULPRTC matches
                                                   MULPRVAL. Before change this mode, need to check that MUTMR_CEN
                                                   is 0. 00: Timer Mode. Incremented every rising PCLK edge.
                                                   01: Counter Mode rising edge. MULTC is incremented on rising
                                                   edges on the input. 02: Counter Mode falling edge. MULTC
                                                   is incremented on falling edges on the input. 03: Counter
                                                   Mode both edge. MULTC is incremented                                      */
  } b;                                        /*!< bit fields for sgpio_multmr_ctrl */
} sgpio_multmr_ctrl_t, *psgpio_multmr_ctrl_t;

/**
  \brief Union type to access sgpio_mulprval (@ 0x0000002C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000002C) Multiple Maximum Prescale Register                         */

  struct {
    __IOM uint32_t mulprval   : 16;           /*!< [15..0] Maximum value for the Multiple Prescale Counter                   */
  } b;                                        /*!< bit fields for sgpio_mulprval */
} sgpio_mulprval_t, *psgpio_mulprval_t;

/**
  \brief Union type to access sgpio_mulprtc (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) Multiple Timer Prescale Register                           */

  struct {
    __IOM uint32_t mulprtc    : 16;           /*!< [15..0] Multiple Prescale Counter value.                                  */
  } b;                                        /*!< bit fields for sgpio_mulprtc */
} sgpio_mulprtc_t, *psgpio_mulprtc_t;

/**
  \brief Union type to access sgpio_multc (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) Multiple Timer Counter Register                            */

  struct {
    __IOM uint32_t multc      : 16;           /*!< [15..0] Multiple Timer Counter value.                                     */
  } b;                                        /*!< bit fields for sgpio_multc */
} sgpio_multc_t, *psgpio_multc_t;

/**
  \brief Union type to access sgpio_mulmc (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) Multiple Match Control Register                            */

  struct {
    __IOM uint32_t mul_mr0i_en : 1;           /*!< [0..0] Generate an interrupt when BIT_PERI_MULMR0_GP0 or BIT_PERI_MULMR0_GP1
                                                   match the value in the BIT_PERI_MULTC. 0: Disable 1: Enable               */
    __IOM uint32_t mul_mr0rst_en : 1;         /*!< [1..1] Reset BIT_PERI_MULTC when BIT_PERI_MULMR0_GP0 or BIT_PERI_MULMR0_GP1
                                                   match BIT_PERI_MULTC. 0: Disable 1: Enable                                */
    __IOM uint32_t mul_mr0stop_en : 1;        /*!< [2..2] MULTC will stop and MULTMR_CEN will be cleared if MULMR0_GP0
                                                   or MULMR0_GP1 match MULTC. 0: Disable 1: Enable                           */
    __IOM uint32_t mul_mr0sclk_en : 1;        /*!< [3..3] Generate a shift clock for Multiple Data Register when
                                                   MULMR0_GP0 or MULMR0_GP1 match the value in the MULTC.
                                                   0: Disable 1: Enable                                                      */
    __IOM uint32_t mul_mr0rxrst_en : 1;       /*!< [4..4] Reset RXTC when MULMR0_GP0 or MULMR0_GP1 match MULTC.
                                                   0: Disable 1: Enable                                                      */
    __IOM uint32_t mul_mr0rxstop_en : 1;      /*!< [5..5] RXTC will stop and RXTMR_CEN will be cleared if MULMR0_GP0
                                                   or MULMR0_GP1 match MULTC. 0: Disable 1: Enable                           */
    __IOM uint32_t mul_mr0capsrc_en : 1;      /*!< [6..6] Change the capture trigger source. When match MULTC,
                                                   generate the Multiple Counter match event to make that
                                                   CAPR is loaded with the value of RXTC. 0: Disable 1: Enable               */
    __IOM uint32_t mul_mr0mcnt_en : 1;        /*!< [7..7] Let MUL_MCNT counts down when MULMR0_GP0 or MULMR0_GP1
                                                   match the value in the MULTC. 0: Disable 1: Enable                        */
    __IOM uint32_t mul_mcnti_en : 1;          /*!< [8..8] Generate an interrupt when MUL_MCNT reaches zero.                  */
    __IOM uint32_t mul_mcntrst_en : 1;        /*!< [9..9] Reset MULTC when each time MUL_MCNT reaches zero. 0:
                                                   Disable 1: Enable                                                         */
    __IOM uint32_t mul_mcntstop_en : 1;       /*!< [10..10] MULTC will stop and MULTMR_CEN will be cleared if each
                                                   time MUL_MCNT reaches zero. 0: Disable 1: Enable                          */
    __IOM uint32_t mul_fmode_en : 1;          /*!< [11..11] The match value of multiple match control is according
                                                   to multiple match FIFO. This mode only changes match values.
                                                   The match control is the same. 1->0 reset all FIFO logic
                                                   to initial state. 0: Disable 1: Enable                                    */
    __IOM uint32_t mul_dma_en : 1;            /*!< [12..12] Use DMA mode to write the match value of FIFO. Need
                                                   to set FMODE. 0: Disable 1: Enable                                        */
    __IOM uint32_t mul_dma_start : 1;         /*!< [13..13] When set DMA register and complete data prepartion,
                                                   set this bit in order to trigger that mutiple match FIFO
                                                   is loaded with data for the first time. 0: Disabled. Do
                                                   nothing. 1: Trigger DMA. Automatically change from 1 to
                                                   0.                                                                        */
    __IOM uint32_t mul_dma_unfli_en : 1;      /*!< [14..14] Generate an interrupt when multiple match FIFO is underflow
                                                   in the DMA mode. (MUL_DMA_EN = 1)                                         */
  } b;                                        /*!< bit fields for sgpio_mulmc */
} sgpio_mulmc_t, *psgpio_mulmc_t;

/**
  \brief Union type to access sgpio_mulmr01gp0 (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) Multiple Match Register 0 & 1 For Group 0                  */

  struct {
    __IOM uint32_t mulmr0_gp0 : 16;           /*!< [15..0] Multiple timer counter match value when TXDATA[0] is
                                                   0.                                                                        */
    __IOM uint32_t mulmr1_gp0 : 16;           /*!< [31..16] Multiple timer counter match value when TXDATA[0] is
                                                   0.                                                                        */
  } b;                                        /*!< bit fields for sgpio_mulmr01gp0 */
} sgpio_mulmr01gp0_t, *psgpio_mulmr01gp0_t;

/**
  \brief Union type to access sgpio_mulmr23gp0 (@ 0x00000040).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000040) Multiple Match Register 2 & 3 For Group 0                  */

  struct {
    __IOM uint32_t mulmr2_gp0 : 16;           /*!< [15..0] Multiple timer counter match value when TXDATA[0] is
                                                   0.                                                                        */
    __IOM uint32_t mulmr3_gp0 : 16;           /*!< [31..16] Multiple timer counter match value when TXDATA[0] is
                                                   0.                                                                        */
  } b;                                        /*!< bit fields for sgpio_mulmr23gp0 */
} sgpio_mulmr23gp0_t, *psgpio_mulmr23gp0_t;

/**
  \brief Union type to access sgpio_mulmr01gp1 (@ 0x00000044).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000044) Multiple Match Register 0 & 1 For Group 1                  */

  struct {
    __IOM uint32_t mulmr0_gp1 : 16;           /*!< [15..0] Multiple timer counter match value when TXDATA[0] is
                                                   1.                                                                        */
    __IOM uint32_t mulmr1_gp1 : 16;           /*!< [31..16] Multiple timer counter match value when TXDATA[0] is
                                                   1.                                                                        */
  } b;                                        /*!< bit fields for sgpio_mulmr01gp1 */
} sgpio_mulmr01gp1_t, *psgpio_mulmr01gp1_t;

/**
  \brief Union type to access sgpio_mulmr23gp1 (@ 0x00000048).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000048) Multiple Match Register 2 & 3 For Group 1                  */

  struct {
    __IOM uint32_t mulmr2_gp1 : 16;           /*!< [15..0] Multiple timer counter match value when TXDATA[0] is
                                                   1.                                                                        */
    __IOM uint32_t mulmr3_gp1 : 16;           /*!< [31..16] Multiple timer counter match value when TXDATA[0] is
                                                   1.                                                                        */
  } b;                                        /*!< bit fields for sgpio_mulmr23gp1 */
} sgpio_mulmr23gp1_t, *psgpio_mulmr23gp1_t;

/**
  \brief Union type to access sgpio_mul_mcnt (@ 0x0000004C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000004C) Multiple Match Counter Register                            */

  struct {
    __IOM uint32_t mul_mcnt   : 8;            /*!< [7..0] When MULMR0_GP0 or MULMR0_GP1 match MULTC, MUL_MCNT counts
                                                   down. Counting to zero can stop and reset the multiple
                                                   counter by multiple match control register.                               */
  } b;                                        /*!< bit fields for sgpio_mul_mcnt */
} sgpio_mul_mcnt_t, *psgpio_mul_mcnt_t;

/**
  \brief Union type to access sgpio_mulemr (@ 0x00000050).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000050) External Match Control Register                            */

  struct {
    __IOM uint32_t mulemc1    : 2;            /*!< [1..0] When MULMR1_GP0 or MULMR1_GP1 are equal to MULTC, determines
                                                   the functionality of output. 00: Do nothing. 01: Output
                                                   is low. 10: Output is high. 11: Toggle.                                   */
    __IOM uint32_t mulemc2    : 2;            /*!< [3..2] When MULMR2_GP0 or MULMR2_GP1 are equal to MULTC, determines
                                                   the functionality of output. 00: Do nothing. 01: Output
                                                   is low. 10: Output is high. 11: Toggle.                                   */
    __IOM uint32_t mulemc3    : 2;            /*!< [5..4] When MULMR3_GP0 or MULMR3_GP1 are equal to MULTC, determines
                                                   the functionality of output. 00: Do nothing. 01: Output
                                                   is low. 10: Output is high. 11: Toggle.                                   */
    __IOM uint32_t rxemc0     : 2;            /*!< [7..6] When RXMR0 is equal to RXTC, determines the functionality
                                                   of output. 00: Do nothing. 01: Output is low. 10: Output
                                                   is high. 11: Toggle.                                                      */
    __IOM uint32_t rxemc1     : 2;            /*!< [9..8] When RXMR1 is equal to RXTC, determines the functionality
                                                   of output. 00: Do nothing. 01: Output is low. 10: Output
                                                   is high. 11: Toggle.                                                      */
    __IOM uint32_t rxemc2     : 2;            /*!< [11..10] When RXMR2 is equal to RXTC, determines the functionality
                                                   of output. 00: Do nothing. 01: Output is low. 10: Output
                                                   is high. 11: Toggle.                                                      */
    __IM  uint32_t            : 4;
    __IOM uint32_t biout      : 1;            /*!< [16..16] Send TX to bi-direction open-drain output. When disable
                                                   output, bi-direction open-drain output is high. 0: Disable
                                                   output 1: Enable output                                                   */
  } b;                                        /*!< bit fields for sgpio_mulemr */
} sgpio_mulemr_t, *psgpio_mulemr_t;

/**
  \brief Union type to access sgpio_data_ctrl (@ 0x00000054).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000054) Data Control Register                                      */

  struct {
    __IOM uint32_t rxsft_ie   : 1;            /*!< [0..0] Enable generating an interrupt when have a shift clock
                                                   for RX Data Register. 0: Disable 1: Enable                                */
    __IOM uint32_t mulsft_ie  : 1;            /*!< [1..1] Enable generating an interrupt when have a shift clock
                                                   for Multiple Data Register. 0: Disable 1: Enable                          */
    __IOM uint32_t rxload_ie  : 1;            /*!< [2..2] When RXDATA_DP is loaded with RXDATA, generate an interrupt.
                                                   0: Disable 1: Enable                                                      */
    __IOM uint32_t mulload_ie : 1;            /*!< [3..3] When MULDATA_DP is loaded with MULDATA, generate an interrupt.
                                                   0: Disable 1: Enable                                                      */
    __IOM uint32_t rxdatasrc_sel : 1;         /*!< [4..4] Select RXDATA input source. 0: External input 1: Capture
                                                   comparison                                                                */
    __IOM uint32_t pattern_match_mode : 1;    /*!< [5..5] Filter receving data. RXDATA_DP is programmed with the
                                                   pattern to be matched. RXDATA_DP is not loaded with RXDATA.
                                                   0: Do not match data 1: Match dat                                         */
    __IOM uint32_t pattern_match_ie : 1;      /*!< [6..6] When RXDATA_DP is equal to RXDATA & RXDATAMASK, generate
                                                   an interrupt. E.g. when looking for pattern 0x12XX XX34,
                                                   then RXDATA should be set to 0x12XX XX34 and RXDATAMASK
                                                   to 0xFF00 00FF. 0: Disable 1: Enable                                      */
    __IOM uint32_t rxdata_dir : 1;            /*!< [7..7] Select the input direction of the RXDATA 0: Input data
                                                   from MSB 1: Input data from LSB                                           */
    __IOM uint32_t txdata_dir : 1;            /*!< [8..8] Select the output direction of the TXDATA 0: Output data
                                                   from LSB 1: Output data from MSB                                          */
  } b;                                        /*!< bit fields for sgpio_data_ctrl */
} sgpio_data_ctrl_t, *psgpio_data_ctrl_t;

/**
  \brief Union type to access sgpio_rxdata (@ 0x00000058).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000058) RX Data Register                                           */

  struct {
    __IOM uint32_t rxdata     : 32;           /*!< [31..0] The register shifts right at each active shift clock;
                                                   loading RXDATA[31] with data captured from input.                         */
  } b;                                        /*!< bit fields for sgpio_rxdata */
} sgpio_rxdata_t, *psgpio_rxdata_t;

/**
  \brief Union type to access sgpio_rxdata_dp (@ 0x0000005C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000005C) RX Data Duplicate Register                                 */

  struct {
    __IOM uint32_t rxdata_dp  : 32;           /*!< [31..0] When each time RXPOSTC reaches 0x0, RXDATA_DP is loaded
                                                   with RXDATA.                                                              */
  } b;                                        /*!< bit fields for sgpio_rxdata_dp */
} sgpio_rxdata_dp_t, *psgpio_rxdata_dp_t;

/**
  \brief Union type to access sgpio_rxposr (@ 0x00000060).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000060) RX Position Register                                       */

  struct {
    __IOM uint32_t rxpostc    : 5;            /*!< [4..0] When generate a shift clock for RX Data Register, RXPOSTC
                                                   counts down                                                               */
    __IM  uint32_t            : 3;
    __IOM uint32_t rxposrst   : 5;            /*!< [12..8] Reload value for RXPOSTC after RXPOSTC reaches 0x0.               */
  } b;                                        /*!< bit fields for sgpio_rxposr */
} sgpio_rxposr_t, *psgpio_rxposr_t;

/**
  \brief Union type to access sgpio_rxdatamask (@ 0x00000064).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000064) RX Data Mask Register                                      */

  struct {
    __IOM uint32_t rxdatamask : 32;           /*!< [31..0] Mask for pattern match function.                                  */
  } b;                                        /*!< bit fields for sgpio_rxdatamask */
} sgpio_rxdatamask_t, *psgpio_rxdatamask_t;

/**
  \brief Union type to access sgpio_muldata (@ 0x00000068).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000068) Multiple Data Register                                     */

  struct {
    __IOM uint32_t muldata    : 32;           /*!< [31..0] The register shifts right at each active shift clock;
                                                   output is set to MULDATA [0].                                             */
  } b;                                        /*!< bit fields for sgpio_muldata */
} sgpio_muldata_t, *psgpio_muldata_t;

/**
  \brief Union type to access sgpio_muldata_dp (@ 0x0000006C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000006C) Multiple Data Duplicate Register                           */

  struct {
    __IOM uint32_t muldata_dp : 32;           /*!< [31..0] When each time MULPOSTC reaches 0x0, MULDATA_DP is loaded
                                                   with MULDATA.                                                             */
  } b;                                        /*!< bit fields for sgpio_muldata_dp */
} sgpio_muldata_dp_t, *psgpio_muldata_dp_t;

/**
  \brief Union type to access sgpio_mulposr (@ 0x00000070).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000070) Multiple Position Register                                 */

  struct {
    __IOM uint32_t mulpostc   : 5;            /*!< [4..0] When generate a shift clock for Multiple Data Register,
                                                   MULPOSTC counts down.                                                     */
    __IM  uint32_t            : 3;
    __IOM uint32_t mulposrst  : 5;            /*!< [12..8] Reload value for MULPOSTC after MULPOSTC reaches 0x0.             */
  } b;                                        /*!< bit fields for sgpio_mulposr */
} sgpio_mulposr_t, *psgpio_mulposr_t;

/**
  \brief Union type to access sgpio_mulfdata (@ 0x00000074).
*/
typedef union {
  __OM  uint32_t w;                           /*!< (@ 0x00000074) Multiple FIFO Data Register                                */

  struct {
    __OM  uint32_t mulfdata   : 32;           /*!< [31..0] Write the match value (FMR1, FMR0) or (FMR3, FMR2) to
                                                   FIFO.                                                                     */
  } b;                                        /*!< bit fields for sgpio_mulfdata */
} sgpio_mulfdata_t, *psgpio_mulfdata_t;

/**
  \brief Union type to access sgpio_is (@ 0x00000078).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000078) SGPIO Interrupt Status Regwter                            */

  struct {
    __IOM uint32_t rx_mr0i_is : 1;            /*!< [0..0] Interrupt raw status 0: No Interrupt. 1: Interrupt requirement
                                                   met. Clear Interrupts; write 1 to clear.                                  */
    __IOM uint32_t rx_mr1i_is : 1;            /*!< [1..1] Interrupt raw status 0: No Interrupt. 1: Interrupt requirement
                                                   met. Clear Interrupts; write 1 to clear.                                  */
    __IOM uint32_t rx_mr2i_is : 1;            /*!< [2..2] Interrupt raw status 0: No Interrupt. 1: Interrupt requirement
                                                   met. Clear Interrupts; write 1 to clear.                                  */
    __IOM uint32_t mul_mr0i_is : 1;           /*!< [3..3] Interrupt raw status 0: No Interrupt. 1: Interrupt requirement
                                                   met. Clear Interrupts; write 1 to clear.                                  */
    __IOM uint32_t capi_is    : 1;            /*!< [4..4] Interrupt raw status 0: No Interrupt. 1: Interrupt requirement
                                                   met. Clear Interrupts; write 1 to clear.                                  */
    __IOM uint32_t rxsft_is   : 1;            /*!< [5..5] Interrupt raw status 0: No Interrupt. 1: Interrupt requirement
                                                   met. Clear Interrupts; write 1 to clear.                                  */
    __IOM uint32_t mulsft_is  : 1;            /*!< [6..6] Interrupt raw status 0: No Interrupt. 1: Interrupt requirement
                                                   met. Clear Interrupts; write 1 to clear.                                  */
    __IOM uint32_t rxload_is  : 1;            /*!< [7..7] Interrupt raw status 0: No Interrupt. 1: Interrupt requirement
                                                   met. Clear Interrupts; write 1 to clear.                                  */
    __IOM uint32_t mulload_is : 1;            /*!< [8..8] Interrupt raw status 0: No Interrupt. 1: Interrupt requirement
                                                   met. Clear Interrupts; write 1 to clear.                                  */
    __IOM uint32_t pattern_match_is : 1;      /*!< [9..9] Interrupt raw status 0: No Interrupt. 1: Interrupt requirement
                                                   met. Clear Interrupts; write 1 to clear.                                  */
    __IOM uint32_t mulmcnt_is : 1;            /*!< [10..10] Interrupt raw status 0: No Interrupt. 1: Interrupt
                                                   requirement met. Clear Interrupts; write 1 to clear.                      */
    __IOM uint32_t mul_dma_unfl_is : 1;       /*!< [11..11] Interrupt raw status 0: No Interrupt. 1: Interrupt
                                                   requirement met. Clear Interrupts; write 1 to clear.                      */
  } b;                                        /*!< bit fields for sgpio_is */
} sgpio_is_t, *psgpio_is_t;

/**
  \brief Union type to access sgpio_gf (@ 0x0000007C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000007C) SGPIO Glitch Filter Register                               */

  struct {
    __IOM uint32_t gf         : 8;            /*!< [7..0] This register can enable or disable digital glitch filtering.
                                                   0: Disable 1: delay 1T clock 2: delay 2T clock etc. 255:
                                                   delay 255T clock                                                          */
  } b;                                        /*!< bit fields for sgpio_gf */
} sgpio_gf_t, *psgpio_gf_t;

/**
  \brief Union type to access sgpio_output (@ 0x00000080).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000080) SGPIO Output Register                                      */

  struct {
    __IOM uint32_t output     : 1;            /*!< [0..0] This bit will act according to MULEMC1~3 and RXEMC0~2
                                                   bits. Drive the state of output by setting this bit. 0:
                                                   Output is low 1: Output is high                                           */
  } b;                                        /*!< bit fields for sgpio_output */
} sgpio_output_t, *psgpio_output_t;

/**
  \brief Union type to access sgpio_im (@ 0x00000084).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000084) SGPIO Interrupt Mask Register                              */

  struct {
    __IOM uint32_t rx_mr0i_im : 1;            /*!< [0..0] interrupt mask: 0: un-mask 1: mask                                 */
    __IOM uint32_t rx_mr1i_im : 1;            /*!< [1..1] interrupt mask: 0: un-mask 1: mask                                 */
    __IOM uint32_t rx_mr2i_im : 1;            /*!< [2..2] interrupt mask: 0: un-mask 1: mask                                 */
    __IOM uint32_t mul_mr0i_im : 1;           /*!< [3..3] interrupt mask: 0: un-mask 1: mask                                 */
    __IOM uint32_t capi_im    : 1;            /*!< [4..4] interrupt mask: 0: un-mask 1: mask                                 */
    __IOM uint32_t rxsft_im   : 1;            /*!< [5..5] interrupt mask: 0: un-mask 1: mask                                 */
    __IOM uint32_t mulsft_im  : 1;            /*!< [6..6] interrupt mask: 0: un-mask 1: mask                                 */
    __IOM uint32_t rxload_im  : 1;            /*!< [7..7] interrupt mask: 0: un-mask 1: mask                                 */
    __IOM uint32_t mulload_im : 1;            /*!< [8..8] interrupt mask: 0: un-mask 1: mask                                 */
    __IOM uint32_t pattern_match_im : 1;      /*!< [9..9] interrupt mask: 0: un-mask 1: mask                                 */
    __IOM uint32_t mulmcnt_im : 1;            /*!< [10..10] interrupt mask: 0: un-mask 1: mask                               */
    __IOM uint32_t mul_dma_unfl_im : 1;       /*!< [11..11] interrupt mask: 0: un-mask 1: mask                               */
  } b;                                        /*!< bit fields for sgpio_im */
} sgpio_im_t, *psgpio_im_t;

/** @} */ /* End of group hs_hal_sgpio_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_SGPIO_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_SGPIO_TYPE_H_

