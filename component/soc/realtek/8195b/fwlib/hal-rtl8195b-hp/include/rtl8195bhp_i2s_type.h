/**************************************************************************//**
 * @file      rtl8195bhp_i2s_type.h
 * @brief
 * @version   V1.00
 * @date      2017-11-1 10:11:12
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

#ifndef _RTL8195BHP_I2S_TYPE_H_
#define _RTL8195BHP_I2S_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_I2S_REG_TYPE

/**
 * @addtogroup hs_hal_i2s_reg I2S Registers.
 * @ingroup hs_hal_i2s
 * @{
 */

/**
  \brief Union type to access i2s_ctrl (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) I2S Control Register                                       */

  struct {
    __IOM uint32_t iis_en     : 1;            /*!< [0..0] iis_en 0: disable 1: enable                                        */
    __IOM uint32_t tx_act     : 2;            /*!< [2..1] tx_act 00: rx path 01: tx path (internal lbk need enable)
                                                   10: tx_rx path bi-direction audio/voice application (not
                                                   involve 5.1 audio)                                                        */
    __IOM uint32_t audio_mono : 2;            /*!< [4..3] audio_mono 0 (00) : stereo audio 1 (01) : 5.1 audio 2
                                                   (10) : mono                                                               */
    __IOM uint32_t edge_sw    : 1;            /*!< [5..5] Chose to send data at the negative edge or positive edge
                                                   of SCK. 0: negative edge 1: positive edge                                 */
    __IM  uint32_t            : 1;
    __IOM uint32_t loop_back  : 1;            /*!< [7..7] internal testing                                                   */
    __IOM uint32_t format     : 2;            /*!< [9..8] digital interface format 0 (00) : i2s 1 (01) : left justified
                                                   2 (10) : right justified                                                  */
    __IOM uint32_t lr_swap    : 1;            /*!< [10..10] control whether dac appears in right or left phase
                                                   of ws clock 0 : left phase 1 : right phase                                */
    __IOM uint32_t sck_swap   : 1;            /*!< [11..11] invert sck 0: disable 1: enable                                  */
    __IOM uint32_t byte_swap  : 1;            /*!< [12..12] Make the data do the byte switch 0: Disable the switch
                                                   1: Enable the switch                                                      */
    __IM  uint32_t            : 2;
    __IOM uint32_t debug_switch : 2;          /*!< [16..15] switch 32bit debug signal                                        */

    __IM  uint32_t            : 1;
    __IOM uint32_t burst_size : 5;            /*!< [22..18] 1111 : burst16 1011 : burst12 0111 : burst8 0011 :
                                                   burst4                                                                    */
    __IM  uint32_t            : 4;
    __IOM uint32_t mute       : 1;            /*!< [27..27] mute function 0:disable 1:enable                                 */
    __IOM uint32_t slave_mode : 1;            /*!< [28..28] slave_mode 0: disable 1: enable                                  */
    __IOM uint32_t wl         : 2;            /*!< [30..29] word length 0 (00) : 16bits 1 (01) : 24bits 2 (10)
                                                   : 32bits 3 (11) : unused (error)                                          */
    __IOM uint32_t sw_rstn    : 1;            /*!< [31..31] 0 : sw_rstn 1 : no sw reset                                      */
  } b;                                        /*!< bit fields for i2s_ctrl */
} i2s_ctrl_t, *pi2s_ctrl_t;

/**
  \brief Union type to access i2s_page_ptr_tx (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) TX Page pointer Register                                   */

  struct {
    __IM  uint32_t            : 2;
    __IOM uint32_t page_ptr_tx : 30;          /*!< [31..2] tx page pointer. this is a physical address with word-align
                                                   limitation                                                                */
  } b;                                        /*!< bit fields for i2s_page_ptr_tx */
} i2s_page_ptr_tx_t, *pi2s_page_ptr_tx_t;

/**
  \brief Union type to access i2s_page_ptr_rx (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) RX Page pointer Register                                   */

  struct {
    __IM  uint32_t            : 2;
    __IOM uint32_t page_ptr_rx : 30;          /*!< [31..2] rx page pointer. this is a physical address with word-align
                                                   limitation                                                                */
  } b;                                        /*!< bit fields for i2s_page_ptr_rx */
} i2s_page_ptr_rx_t, *pi2s_page_ptr_rx_t;

/**
  \brief Union type to access i2s_page_size_rate (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) Page Size and Sample Rate Register                         */

  struct {
    __IOM uint32_t page_size  : 12;           /*!< [11..0] page size (word unit)                                             */
    __IOM uint32_t page_num   : 2;            /*!< [13..12] page number                                                      */
    __IOM uint32_t sr         : 4;            /*!< [17..14] sample rate 0000: 8khz /7.35k, 0001: 12khz /11.025k
                                                   0010: 16khz /14.7k 0011: 24khz /22.05khz 0100: 32khz /29.4khz
                                                   0101: 48khz /44.1khz 0110: 64khz /58.8khz 0111: 96khz /88.2khz
                                                   1000: 192khz /176.4khz 1001: 384khz others: reserved                      */
    __IOM uint32_t clk_switch : 1;            /*!< [18..18] clk_iis switch 0: clk_iis is 98.304mhz (+-50ppm) 1:
                                                   clk_iis is 45.1584mhz (+-50ppm)                                           */
  } b;                                        /*!< bit fields for i2s_page_size_rate */
} i2s_page_size_rate_t, *pi2s_page_size_rate_t;

/**
  \brief Union type to access i2s_tx_isr_en (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) TX Interrupt Enable Register                               */

  struct {
    __IOM uint32_t p0okie_tx  : 1;            /*!< [0..0] tx page 0 ok interrupt enable 0: disable interrupt 1:
                                                   enable interrupt                                                          */
    __IOM uint32_t p1okie_tx  : 1;            /*!< [1..1] tx page 1 ok interrupt enable 0: disable interrupt 1:
                                                   enable interrupt                                                          */
    __IOM uint32_t p2okie_tx  : 1;            /*!< [2..2] tx page 2 ok interrupt enable 0: disable interrupt 1:
                                                   enable interrupt                                                          */
    __IOM uint32_t p3okie_tx  : 1;            /*!< [3..3] tx page 3 ok interrupt enable 0: disable interrupt 1:
                                                   enable interrupt                                                          */
    __IOM uint32_t page0unava_ie_tx : 1;      /*!< [4..4] tx page 0 unavailable interrupt enable 0: disable interrupt
                                                   1: enable interrupt                                                       */
    __IOM uint32_t page1unava_ie_tx : 1;      /*!< [5..5] tx page 1 unavailable interrupt enable 0: disable interrupt
                                                   1: enable interrupt                                                       */
    __IOM uint32_t page2unava_ie_tx : 1;      /*!< [6..6] tx page 2 unavailable interrupt enable 0: disable interrupt
                                                   1: enable interrupt                                                       */
    __IOM uint32_t page3unava_ie_tx : 1;      /*!< [7..7] tx page 3 unavailable interrupt enable 0: disable interrupt
                                                   1: enable interrupt                                                       */
    __IOM uint32_t fifo_empty_ie_tx : 1;      /*!< [8..8] tx fifo empty interrupt enable 0: disable interrupt 1:
                                                   enable interrupt                                                          */
  } b;                                        /*!< bit fields for i2s_tx_isr_en */
} i2s_tx_isr_en_t, *pi2s_tx_isr_en_t;

/**
  \brief Union type to access i2s_tx_isr_status (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) TX Interrupt Status Register                               */

  struct {
    __IOM uint32_t p0okip_tx  : 1;            /*!< [0..0] tx page 0 ok interrupt pending 0: no interrupt 1: interrupt
                                                   pending, write 1 to clear                                                 */
    __IOM uint32_t p1okip_tx  : 1;            /*!< [1..1] tx page 1 ok interrupt pending 0: no interrupt 1: interrupt
                                                   pending, write 1 to clear                                                 */
    __IOM uint32_t p2okip_tx  : 1;            /*!< [2..2] tx page 2 ok interrupt pending 0: no interrupt 1: interrupt
                                                   pending, write 1 to clear                                                 */
    __IOM uint32_t p3okip_tx  : 1;            /*!< [3..3] tx page 3 ok interrupt pending 0: no interrupt 1: interrupt
                                                   pending, write 1 to clear                                                 */
    __IOM uint32_t page0unava_ip_tx : 1;      /*!< [4..4] tx page 0 unavailable interrupt pending 0: no interrupt
                                                   1: interrupt pending, write 1 to clear                                    */
    __IOM uint32_t page1unava_ip_tx : 1;      /*!< [5..5] tx page 1 unavailable interrupt pending 0: no interrupt
                                                   1: interrupt pending, write 1 to clear                                    */
    __IOM uint32_t page2unava_ip_tx : 1;      /*!< [6..6] tx page 2 unavailable interrupt pending 0: no interrupt
                                                   1: interrupt pending, write 1 to clear                                    */
    __IOM uint32_t page3unava_ip_tx : 1;      /*!< [7..7] tx page 3 unavailable interrupt pending 0: no interrupt
                                                   1: interrupt pending, write 1 to clear                                    */
    __IOM uint32_t fifo_empty_ip_tx : 1;      /*!< [8..8] tx fifo empty interrupt pending 0: no interrupt 1: interrupt
                                                   pending, write 1 to clear                                                 */
  } b;                                        /*!< bit fields for i2s_tx_isr_status */
} i2s_tx_isr_status_t, *pi2s_tx_isr_status_t;

/**
  \brief Union type to access i2s_rx_isr_en (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) RX Interrupt Enable Register                               */

  struct {
    __IOM uint32_t p0okie_rx  : 1;            /*!< [0..0] rx page 0 ok interrupt enable 0: disable interrupt 1:
                                                   enable interrupt                                                          */
    __IOM uint32_t p1okie_rx  : 1;            /*!< [1..1] rx page 1 ok interrupt enable 0: disable interrupt 1:
                                                   enable interrupt                                                          */
    __IOM uint32_t p2okie_rx  : 1;            /*!< [2..2] rx page 2 ok interrupt enable 0: disable interrupt 1:
                                                   enable interrupt                                                          */
    __IOM uint32_t p3okie_rx  : 1;            /*!< [3..3] rx page 3 ok interrupt enable 0: disable interrupt 1:
                                                   enable interrupt                                                          */
    __IOM uint32_t page0unava_ie_rx : 1;      /*!< [4..4] rx page 0 unavailable interrupt enable 0: disable interrupt
                                                   1: enable interrupt                                                       */
    __IOM uint32_t page1unava_ie_rx : 1;      /*!< [5..5] rx page 1 unavailable interrupt enable 0: disable interrupt
                                                   1: enable interrupt                                                       */
    __IOM uint32_t page2unava_ie_rx : 1;      /*!< [6..6] rx page 2 unavailable interrupt enable 0: disable interrupt
                                                   1: enable interrupt                                                       */
    __IOM uint32_t page3unava_ie_rx : 1;      /*!< [7..7] rx page 3 unavailable interrupt enable 0 : disable interrupt
                                                   1: enable interrupt                                                       */
    __IOM uint32_t fifo_full_ie_rx : 1;       /*!< [8..8] rx fifo full interrupt enable 0: disable interrupt 1:
                                                   enable interrupt                                                          */
  } b;                                        /*!< bit fields for i2s_rx_isr_en */
} i2s_rx_isr_en_t, *pi2s_rx_isr_en_t;

/**
  \brief Union type to access i2s_rx_isr_status (@ 0x0000001C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000001C) RX Interrupt Status Register                               */

  struct {
    __IOM uint32_t p0okip_rx  : 1;            /*!< [0..0] rx page 0 ok interrupt pending 0: no interrupt 1: interrupt
                                                   pending, write 1 to clear                                                 */
    __IOM uint32_t p1okip_rx  : 1;            /*!< [1..1] rx page 1 ok interrupt pending 0: no interrupt 1: interrupt
                                                   pending, write 1 to clear                                                 */
    __IOM uint32_t p2okip_rx  : 1;            /*!< [2..2] rx page 2 ok interrupt pending 0: no interrupt 1: interrupt
                                                   pending, write 1 to clear                                                 */
    __IOM uint32_t p3okip_rx  : 1;            /*!< [3..3] rx page 3 ok interrupt pending 0: no interrupt 1: interrupt
                                                   pending, write 1 to clear                                                 */
    __IOM uint32_t page0unava_ip_rx : 1;      /*!< [4..4] rx page 0 unavailable interrupt pending 0: no interrupt
                                                   1: interrupt pending, write 1 to clear                                    */
    __IOM uint32_t page1unava_ip_rx : 1;      /*!< [5..5] rx page 1 unavailable interrupt pending 0: no interrupt
                                                   1: interrupt pending, write 1 to clear                                    */
    __IOM uint32_t page2unava_ip_rx : 1;      /*!< [6..6] rx page 2 unavailable interrupt pending 0: no interrupt
                                                   1: interrupt pending, write 1 to clear                                    */
    __IOM uint32_t page3unava_ip_rx : 1;      /*!< [7..7] rx page 3 unavailable interrupt pending 0: no interrupt
                                                   1: interrupt pending, write 1 to clear                                    */
    __IOM uint32_t fifo_full_ip_rx : 1;       /*!< [8..8] rx fifo full interrupt pending 0: no interrupt 1: interrupt
                                                   pending, write 1 to clear                                                 */
  } b;                                        /*!< bit fields for i2s_rx_isr_status */
} i2s_rx_isr_status_t, *pi2s_rx_isr_status_t;

/**
  \brief Union type to access i2s_tx_page0_own (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) TX Page0 Own Bit Register                                  */

  struct {
    __IM  uint32_t            : 31;
    __IOM uint32_t p0own_tx   : 1;            /*!< [31..31] tx page 0 own bit 0: page 0 owned by cpu 1: page 0
                                                   owned by iis controller                                                   */
  } b;                                        /*!< bit fields for i2s_tx_page0_own */
} i2s_tx_page0_own_t, *pi2s_tx_page0_own_t;

/**
  \brief Union type to access i2s_tx_page1_own (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) TX Page1 Own Bit Register                                  */

  struct {
    __IM  uint32_t            : 31;
    __IOM uint32_t p1own_tx   : 1;            /*!< [31..31] tx page 1 own bit 0: page 1 owned by cpu 1: page 1
                                                   owned by iis controller                                                   */
  } b;                                        /*!< bit fields for i2s_tx_page1_own */
} i2s_tx_page1_own_t, *pi2s_tx_page1_own_t;

/**
  \brief Union type to access i2s_tx_page2_own (@ 0x00000028).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000028) TX Page2 Own Bit Register                                  */

  struct {
    __IM  uint32_t            : 31;
    __IOM uint32_t p2own_tx   : 1;            /*!< [31..31] tx page 2 own bit 0: page 2 owned by cpu 1: page 2
                                                   owned by iis controller                                                   */
  } b;                                        /*!< bit fields for i2s_tx_page2_own */
} i2s_tx_page2_own_t, *pi2s_tx_page2_own_t;

/**
  \brief Union type to access i2s_tx_page3_own (@ 0x0000002C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000002C) TX Page3 Own Bit Register                                  */

  struct {
    __IM  uint32_t            : 31;
    __IOM uint32_t p3own_tx   : 1;            /*!< [31..31] tx page 3 own bit 0: page 3 owned by cpu 1: page 3
                                                   owned by iis controller                                                   */
  } b;                                        /*!< bit fields for i2s_tx_page3_own */
} i2s_tx_page3_own_t, *pi2s_tx_page3_own_t;

/**
  \brief Union type to access i2s_rx_page0_own (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) RX Page0 Own Bit Register                                  */

  struct {
    __IM  uint32_t            : 31;
    __IOM uint32_t p0own_rx   : 1;            /*!< [31..31] rx page 0 own bit 0: page 0 owned by cpu 1: page 0
                                                   owned by iis controller                                                   */
  } b;                                        /*!< bit fields for i2s_rx_page0_own */
} i2s_rx_page0_own_t, *pi2s_rx_page0_own_t;

/**
  \brief Union type to access i2s_rx_page1_own (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) RX Page1 Own Bit Register                                  */

  struct {
    __IM  uint32_t            : 31;
    __IOM uint32_t p1own_rx   : 1;            /*!< [31..31] rx page 1 own bit 0: page 1 owned by cpu 1: page 1
                                                   owned by iis controller                                                   */
  } b;                                        /*!< bit fields for i2s_rx_page1_own */
} i2s_rx_page1_own_t, *pi2s_rx_page1_own_t;

/**
  \brief Union type to access i2s_rx_page2_own (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) RX Page2 Own Bit Register                                  */

  struct {
    __IM  uint32_t            : 31;
    __IOM uint32_t p2own_rx   : 1;            /*!< [31..31] rx page 2 own bit 0: page 2 owned by cpu 1: page 2
                                                   owned by iis controller                                                   */
  } b;                                        /*!< bit fields for i2s_rx_page2_own */
} i2s_rx_page2_own_t, *pi2s_rx_page2_own_t;

/**
  \brief Union type to access i2s_rx_page3_own (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) RX Page3 Own Bit Register                                  */

  struct {
    __IM  uint32_t            : 31;
    __IOM uint32_t p3own_rx   : 1;            /*!< [31..31] rx page 3 own bit 0: page 3 owned by cpu 1: page 3
                                                   owned by iis controller                                                   */
  } b;                                        /*!< bit fields for i2s_rx_page3_own */
} i2s_rx_page3_own_t, *pi2s_rx_page3_own_t;

/**
  \brief Union type to access i2s_version_id (@ 0x00000040).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000040) Version id                                                 */

  struct {
    __IM  uint32_t version_id : 32;           /*!< [31..0] version id                                                        */
  } b;                                        /*!< bit fields for i2s_version_id */
} i2s_version_id_t, *pi2s_version_id_t;

/** @} */ /* End of group hs_hal_i2s_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_I2S_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_I2S_TYPE_H_

