/**************************************************************************//**
 * @file      rtl8195bhp_sport_type.h
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

#ifndef _RTL8195BHP_SPORT_TYPE_H_
#define _RTL8195BHP_SPORT_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_AUDIO_REG_TYPE

/**
 * @addtogroup hs_hal_audio_reg SPORT Registers.
 * @ingroup hs_hal_audio
 * @{
 */

/**
  \brief Union type to access sport_tx_fifo_adr (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) SPORT TX FIFO Register                                     */
  
  struct {
    __IOM uint32_t tx_fifo_adr : 32;          /*!< [31..0] TX FIFO address                                                   */
  } b;                                        /*!< bit fields for sport_tx_fifo_adr */
} sport_tx_fifo_adr_t, *psport_tx_fifo_adr_t;

/**
  \brief Union type to access sport_ctrl_1 (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) SPORT Control 1 Register                                   */
  
  struct {
    __IOM uint32_t sp_reset   : 1;            /*!< [0..0] Reset SPORT0 module                                                */
    __IOM uint32_t tx_inv_i2s_sclk : 1;       /*!< [1..1] Inverte sclk for TX                                                */
    __IOM uint32_t rx_inv_i2s_sclk : 1;       /*!< [2..2] Inverte sclk for RX                                                */
    __IOM uint32_t slave_clk_sel : 1;         /*!< [3..3] I2S or PCM slave for CLK path.                                     */
    __IOM uint32_t slave_data_sel : 1;        /*!< [4..4] I2S or PCM slave for DATA path.                                    */
    __IOM uint32_t sp_wclk_inverse : 1;       /*!< [5..5] Inverte I2S/PCM word clock.                                        */
    __IOM uint32_t sp_loopback : 1;           /*!< [6..6] Self loopback mode.                                                */
    __IOM uint32_t dsp_ctl_mode : 1;          /*!< [7..7] Handshaking control.                                               */
    __IOM uint32_t sp_data_format_sel : 3;    /*!< [10..8] Set data format                                                   */
    __IOM uint32_t sp_en_i2s_mono : 1;        /*!< [11..11] Set audio channel                                                */
    __IOM uint32_t sp_data_len_sel : 2;       /*!< [13..12] Set data length                                                  */
    __IOM uint32_t sp_inv_i2s_sclk : 1;       /*!< [14..14] Inverte I2S/PCM bit clock.                                       */
    __IOM uint32_t sp_i2s_self_lpbk_en : 1;   /*!< [15..15] Internal loopback mode.                                          */
    __IOM uint32_t sp_tx_disable : 1;         /*!< [16..16] SPORT TX control.                                                */
    __IOM uint32_t sp_start_tx : 1;           /*!< [17..17] Start TX.                                                        */
    __IOM uint32_t sp_adc_comp : 2;           /*!< [19..18] Compander control for ADC .                                      */
    __IOM uint32_t sp_sel_i2s_tx_ch : 2;      /*!< [21..20] Sel TX channel for DAC path.                                     */
    __IOM uint32_t tx_lsb_first : 1;          /*!< [22..22] MSB or LSB control for TX.                                       */
    __IOM uint32_t rx_lsb_first : 1;          /*!< [23..23] MSB or LSB control for RX.                                       */
    __IOM uint32_t sp_rx_disable : 1;         /*!< [24..24] SPORT RX control.                                                */
    __IOM uint32_t sp_start_rx : 1;           /*!< [25..25] Start RX.                                                        */
    __IOM uint32_t sp_dac_comp : 2;           /*!< [27..26] Compander control for DAC .                                      */
    __IOM uint32_t sp_sel_i2s_rx_ch : 2;      /*!< [29..28] Select RX channel for ADC path.                                  */
    __IOM uint32_t mclk_sel   : 1;            /*!< [30..30] Select MCLK output                                               */
    __IOM uint32_t long_frame_sync : 1;       /*!< [31..31] Frame sync mode                                                  */
  } b;                                        /*!< bit fields for sport_ctrl_1 */
} sport_ctrl_1_t, *psport_ctrl_1_t;

/**
  \brief Union type to access sport_ctrl_2 (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) SPORT Control 2 Register                                   */
  
  struct {
    __IOM uint32_t frame_sync_offset : 8;     /*!< [7..0] Long frame_syn control                                             */
    __IOM uint32_t debug_bus_sel : 3;         /*!< [10..8] Debug bus control                                                 */
    __IM  uint32_t            : 1;
    __IOM uint32_t clear_tx_err_cnt : 1;      /*!< [12..12] Clear TX error counter                                           */
    __IOM uint32_t clear_rx_err_cnt : 1;      /*!< [13..13] Clear RX error counter                                           */
    __IM  uint32_t            : 2;
    __IOM uint32_t mode_40mhz : 1;            /*!< [16..16] 40MHz mode                                                       */
    __IOM uint32_t mode_128fs : 1;            /*!< [17..17] 128fs mode                                                       */
    __IM  uint32_t            : 2;
    __IOM uint32_t tx_src_byte_swap : 1;      /*!< [20..20] Byte swap for TX                                                 */
    __IOM uint32_t tx_src_lr_swap : 1;        /*!< [21..21] LR swap for TX                                                   */
    __IOM uint32_t rx_snk_byte_swap : 1;      /*!< [22..22] Byte swap for RX                                                 */
    __IOM uint32_t rx_snk_lr_swap : 1;        /*!< [23..23] LR swap for RX                                                   */
    __IOM uint32_t int_enable : 8;            /*!< [31..24] Interrupt Enable                                                 */
  } b;                                        /*!< bit fields for sport_ctrl_2 */
} sport_ctrl_2_t, *psport_ctrl_2_t;

/**
  \brief Union type to access sport_ctrl_3 (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) SPORT Control 3 Register                                   */
  
  struct {
    __IOM uint32_t tx_dsp_clear_int : 1;      /*!< [0..0] Clear tx interrupt                                                 */
    __IOM uint32_t rx_dsp_clear_int : 1;      /*!< [1..1] Clear rx interrupt                                                 */
    __IM  uint32_t            : 2;
    __IOM uint32_t tx_fifo_depth_half_sel : 1;/*!< [4..4] Reduce TX FIFO depth.                                              */
    __IOM uint32_t rx_fifo_depth_half_sel : 1;/*!< [5..5] Reduce RX FIFO depth.                                              */
  } b;                                        /*!< bit fields for sport_ctrl_3 */
} sport_ctrl_3_t, *psport_ctrl_3_t;

/**
  \brief Union type to access sport_rx_fifo_adr (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) SPORT RX FIFO Register                                     */
  
  struct {
    __IOM uint32_t rx_fifo_adr : 32;          /*!< [31..0] RX FIFO address                                                   */
  } b;                                        /*!< bit fields for sport_rx_fifo_adr */
} sport_rx_fifo_adr_t, *psport_rx_fifo_adr_t;

/**
  \brief Union type to access sport_counter_status (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) SPORT Counter Status Register                              */
  
  struct {
    __IM  uint32_t tx0_wcnt_bus : 8;          /*!< [7..0] TX0 FIFO write counter status                                      */
    __IM  uint32_t tx1_wcnt_bus : 8;          /*!< [15..8] TX1 FIFO write counter status                                     */
    __IM  uint32_t rx0_rcnt_bus : 8;          /*!< [23..16] RX0 FIFO read counter status                                     */
    __IM  uint32_t rx1_rcnt_bus : 8;          /*!< [31..24] RX1 FIFO read counter status                                     */
  } b;                                        /*!< bit fields for sport_counter_status */
} sport_counter_status_t, *psport_counter_status_t;

/**
  \brief Union type to access sport_err_counter (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) SPORT Error Counter Register                               */
  
  struct {
    __IM  uint32_t tx_err_cnt : 8;            /*!< [7..0] TX error counter                                                   */
    __IM  uint32_t rx_err_cnt : 8;            /*!< [15..8] RX error counter                                                  */
  } b;                                        /*!< bit fields for sport_err_counter */
} sport_err_counter_t, *psport_err_counter_t;

/**
  \brief Union type to access sport_gen_bclk (@ 0x0000001C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000001C) SPORT Generate BCLK Register                               */
  
  struct {
    __IOM uint32_t mi         : 16;           /*!< [15..0] Set parameter for BCLK                                            */
    __IOM uint32_t ni         : 15;           /*!< [30..16] Set parameter for BCLK                                           */
    __IOM uint32_t mi_ni_update : 1;          /*!< [31..31] Update mi and ni                                                 */
  } b;                                        /*!< bit fields for sport_gen_bclk */
} sport_gen_bclk_t, *psport_gen_bclk_t;

/** @} */ /* End of group hs_hal_audio_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_AUDIO_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_SPORT_TYPE_H_

