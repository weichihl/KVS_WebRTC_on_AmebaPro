/**************************************************************************//**
 * @file      rtl8195bhp_pcm_type.h
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

#ifndef _RTL8195BHP_PCM_TYPE_H_
#define _RTL8195BHP_PCM_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_PCM_REG_TYPE

/**
 * @addtogroup hs_hal_pcm_reg PCM Registers.
 * @ingroup hs_hal_pcm
 * @{
 */

/**
  \brief Union type to access pcm_pcmcr (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) PCM interface Control Register                             */

  struct {
    __IM  uint32_t            : 8;
    __IOM uint32_t slave_sel  : 1;            /*!< [8..8] slave_mode 0: disable 1: enable                                    */
    __IOM uint32_t fsinv      : 1;            /*!< [9..9] pcm interface a frame synchronization invert. 0: pcm0fs
                                                   high active. 1: pcm0fs low active.                                        */
    __IM  uint32_t            : 2;
    __IOM uint32_t pcm_en     : 1;            /*!< [12..12] PCM Enable 0: Disable 1: Enable                                  */
    __IOM uint32_t linear_mode : 1;           /*!< [13..13] linear mode enable 0: enable compender 1: linear mode            */
    __IOM uint32_t loop_back  : 1;            /*!< [14..14] pcm loop back mode enable 0:disable 1:enable                     */

    __IM  uint32_t            : 2;
    __IOM uint32_t endian_swap : 1;           /*!< [17..17] edian swap 0:disable 1:enable                                    */
  } b;                                        /*!< bit fields for pcm_pcmcr */
} pcm_pcmcr_t, *ppcm_pcmcr_t;

/**
  \brief Union type to access pcm_pachcnr03 (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) channel0-3 specific control register                       */

  struct {
    __IOM uint32_t ch3re      : 1;            /*!< [0..0] channel receiver enable. 0: disable 1: enable Reset the
                                                   state by setting 1 to 0                                                   */
    __IOM uint32_t ch3te      : 1;            /*!< [1..1] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch3ua      : 1;            /*!< [2..2] channel u law/ a law select. 0: u law, 1: a law                    */
    __IOM uint32_t ch3band    : 1;            /*!< [3..3] narrow band /wide band select. 0: narrow band 1: wide
                                                   band                                                                      */
    __IM  uint32_t            : 4;
    __IOM uint32_t ch2re      : 1;            /*!< [8..8] channel receiver enable. 0: disable 1: enable Reset the
                                                   state by setting 1 to 0                                                   */
    __IOM uint32_t ch2te      : 1;            /*!< [9..9] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch2ua      : 1;            /*!< [10..10] channel u law/ a law select. 0: u law, 1: a law                  */
    __IOM uint32_t ch2band    : 1;            /*!< [11..11] narrow band /wide band select. 0: narrow band 1: wide
                                                   band                                                                      */
    __IM  uint32_t            : 4;
    __IOM uint32_t ch1re      : 1;            /*!< [16..16] channel receiver enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch1te      : 1;            /*!< [17..17] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch1ua      : 1;            /*!< [18..18] channel u law/ a law select. 0: u law, 1: a law                  */
    __IOM uint32_t ch1band    : 1;            /*!< [19..19] narrow band /wide band select. 0: narrow band 1: wide
                                                   band                                                                      */
    __IM  uint32_t            : 4;
    __IOM uint32_t ch0re      : 1;            /*!< [24..24] channel receiver enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch0te      : 1;            /*!< [25..25] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch0ua      : 1;            /*!< [26..26] channel u law/ a law select. 0: u law, 1: a law                  */
    __IOM uint32_t ch0band    : 1;            /*!< [27..27] narrow band /wide band select. 0: narrow band 1: wide
                                                   band                                                                      */
  } b;                                        /*!< bit fields for pcm_pachcnr03 */
} pcm_pachcnr03_t, *ppcm_pachcnr03_t;

/**
  \brief Union type to access pcm_patsr03 (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) channel0-3 time slot assignment register                   */

  struct {
    __IOM uint32_t ch3tsa     : 5;            /*!< [4..0] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch2tsa     : 5;            /*!< [12..8] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch1tsa     : 5;            /*!< [20..16] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch0tsa     : 5;            /*!< [28..24] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
  } b;                                        /*!< bit fields for pcm_patsr03 */
} pcm_patsr03_t, *ppcm_patsr03_t;

/**
  \brief Union type to access pcm_pabsize03 (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) channel0-3 buffer size register                            */

  struct {
    __IOM uint32_t ch3bsize   : 8;            /*!< [7..0] channel buffer size in unit of 4(n+1) bytes.                       */
    __IOM uint32_t ch2bsize   : 8;            /*!< [15..8] channel buffer size in unit of 4(n+1) bytes.                      */
    __IOM uint32_t ch1bsize   : 8;            /*!< [23..16] channel buffer size in unit of 4(n+1) bytes.                     */
    __IOM uint32_t ch0bsize   : 8;            /*!< [31..24] channel buffer size in unit of 4(n+1) bytes.                     */
  } b;                                        /*!< bit fields for pcm_pabsize03 */
} pcm_pabsize03_t, *ppcm_pabsize03_t;

/**
  \brief Union type to access pcm_ch0atxbsa (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) channel 0 tx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch0atxbsa */
} pcm_ch0atxbsa_t, *ppcm_ch0atxbsa_t;

/**
  \brief Union type to access pcm_ch1atxbsa (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) channel 1 tx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch1atxbsa */
} pcm_ch1atxbsa_t, *ppcm_ch1atxbsa_t;

/**
  \brief Union type to access pcm_ch2atxbsa (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) channel 2 tx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch2atxbsa */
} pcm_ch2atxbsa_t, *ppcm_ch2atxbsa_t;

/**
  \brief Union type to access pcm_ch3atxbsa (@ 0x0000001C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000001C) channel 3 tx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch3atxbsa */
} pcm_ch3atxbsa_t, *ppcm_ch3atxbsa_t;

/**
  \brief Union type to access pcm_ch0arxbsa (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) channel 0 rx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch0arxbsa */
} pcm_ch0arxbsa_t, *ppcm_ch0arxbsa_t;

/**
  \brief Union type to access pcm_ch1arxbsa (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) channel 1 rx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch1arxbsa */
} pcm_ch1arxbsa_t, *ppcm_ch1arxbsa_t;

/**
  \brief Union type to access pcm_ch2arxbsa (@ 0x00000028).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000028) channel 2 rx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch2arxbsa */
} pcm_ch2arxbsa_t, *ppcm_ch2arxbsa_t;

/**
  \brief Union type to access pcm_ch3arxbsa (@ 0x0000002C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000002C) channel 3 rx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch3arxbsa */
} pcm_ch3arxbsa_t, *ppcm_ch3arxbsa_t;

/**
  \brief Union type to access pcm_paimr03 (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) channel0-3 interrupt mask register                         */

  struct {
    __IOM uint32_t ch3rbp1uaie : 1;           /*!< [0..0] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch3rbp0uaie : 1;           /*!< [1..1] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch3tbp1uaie : 1;           /*!< [2..2] transmit buffer page1 unavailable interrupt enable. 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch3tbp0uaie : 1;           /*!< [3..3] transmit buffer page0 unavailable interrupt enable. 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch3p1rokie : 1;            /*!< [4..4] rx page 1 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch3p0rokie : 1;            /*!< [5..5] rx page 0 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch3p1tokie : 1;            /*!< [6..6] tx page 1 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch3p0tokie : 1;            /*!< [7..7] tx page 0 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch2rbp1uaie : 1;           /*!< [8..8] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch2rbp0uaie : 1;           /*!< [9..9] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch2tbp1uaie : 1;           /*!< [10..10] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch2tbp0uaie : 1;           /*!< [11..11] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch2p1rokie : 1;            /*!< [12..12] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch2p0rokie : 1;            /*!< [13..13] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch2p1tokie : 1;            /*!< [14..14] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch2p0tokie : 1;            /*!< [15..15] tx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch1rbp1uaie : 1;           /*!< [16..16] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch1rbp0uaie : 1;           /*!< [17..17] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch1tbp1uaie : 1;           /*!< [18..18] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch1tbp0uaie : 1;           /*!< [19..19] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch1p1rokie : 1;            /*!< [20..20] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch1p0rokie : 1;            /*!< [21..21] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch1p1tokie : 1;            /*!< [22..22] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch1p0tokie : 1;            /*!< [23..23] tx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch0rbp1uaie : 1;           /*!< [24..24] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch0rbp0uaie : 1;           /*!< [25..25] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch0tbp1uaie : 1;           /*!< [26..26] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch0tbp0uaie : 1;           /*!< [27..27] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch0p1rokie : 1;            /*!< [28..28] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch0p0rokie : 1;            /*!< [29..29] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch0p1tokie : 1;            /*!< [30..30] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch0p0tokie : 1;            /*!< [31..31] tx page 0 ok interrupt enable. 0: disable 1: enable              */
  } b;                                        /*!< bit fields for pcm_paimr03 */
} pcm_paimr03_t, *ppcm_paimr03_t;

/**
  \brief Union type to access pcm_paisr03 (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) channel0-3 interrupt status register                       */

  struct {
    __IOM uint32_t ch3rxp1ua  : 1;            /*!< [0..0] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch3rxp0ua  : 1;            /*!< [1..1] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch3txp1ua  : 1;            /*!< [2..2] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch3txp0ua  : 1;            /*!< [3..3] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch3rxp1ip  : 1;            /*!< [4..4] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch3rxp0ip  : 1;            /*!< [5..5] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch3txp1ip  : 1;            /*!< [6..6] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch3txp0ip  : 1;            /*!< [7..7] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch2rxp1ua  : 1;            /*!< [8..8] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch2rxp0ua  : 1;            /*!< [9..9] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch2txp1ua  : 1;            /*!< [10..10] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch2txp0ua  : 1;            /*!< [11..11] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch2rxp1ip  : 1;            /*!< [12..12] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch2rxp0ip  : 1;            /*!< [13..13] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch2txp1ip  : 1;            /*!< [14..14] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch2txp0ip  : 1;            /*!< [15..15] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch1rxp1ua  : 1;            /*!< [16..16] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch1rxp0ua  : 1;            /*!< [17..17] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch1txp1ua  : 1;            /*!< [18..18] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch1txp0ua  : 1;            /*!< [19..19] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch1rxp1ip  : 1;            /*!< [20..20] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch1rxp0ip  : 1;            /*!< [21..21] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch1txp1ip  : 1;            /*!< [22..22] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch1txp0ip  : 1;            /*!< [23..23] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch0rxp1ua  : 1;            /*!< [24..24] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch0rxp0ua  : 1;            /*!< [25..25] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch0txp1ua  : 1;            /*!< [26..26] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch0txp0ua  : 1;            /*!< [27..27] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch0rxp1p   : 1;            /*!< [28..28] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch0rxp0ip  : 1;            /*!< [29..29] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch0txp1ip  : 1;            /*!< [30..30] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch0txp0ip  : 1;            /*!< [31..31] interrupt pending flag write 1 to clear the interrupt.           */
  } b;                                        /*!< bit fields for pcm_paisr03 */
} pcm_paisr03_t, *ppcm_paisr03_t;

/**
  \brief Union type to access pcm_pachcnr47 (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) channel4-7 specific control register                       */

  struct {
    __IOM uint32_t ch7re      : 1;            /*!< [0..0] channel receiver enable. 0: disable 1: enable Reset the
                                                   state by setting 1 to 0                                                   */
    __IOM uint32_t ch7te      : 1;            /*!< [1..1] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch7ua      : 1;            /*!< [2..2] channel u law/ a law select. 0: u law, 1: a law                    */
    __IOM uint32_t ch7band    : 1;            /*!< [3..3] narrow band /wide band select. 0: narrow band 1: wide
                                                   band                                                                      */
    __IM  uint32_t            : 4;
    __IOM uint32_t ch6re      : 1;            /*!< [8..8] channel receiver enable. 0: disable 1: enable Reset the
                                                   state by setting 1 to 0                                                   */
    __IOM uint32_t ch6te      : 1;            /*!< [9..9] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch6ua      : 1;            /*!< [10..10] channel u law/ a law select. 0: u law, 1: a law                  */
    __IOM uint32_t ch6band    : 1;            /*!< [11..11] narrow band /wide band select. 0: narrow band 1: wide
                                                   band                                                                      */
    __IM  uint32_t            : 4;
    __IOM uint32_t ch5re      : 1;            /*!< [16..16] channel receiver enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch5te      : 1;            /*!< [17..17] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch5ua      : 1;            /*!< [18..18] channel u law/ a law select. 0: u law, 1: a law                  */
    __IOM uint32_t ch5band    : 1;            /*!< [19..19] narrow band /wide band select. 0: narrow band 1: wide
                                                   band                                                                      */
    __IM  uint32_t            : 4;
    __IOM uint32_t ch4re      : 1;            /*!< [24..24] channel receiver enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch4te      : 1;            /*!< [25..25] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch4ua      : 1;            /*!< [26..26] channel u law/ a law select. 0: u law, 1: a law                  */
    __IOM uint32_t ch4band    : 1;            /*!< [27..27] narrow band /wide band select. 0: narrow band 1: wide
                                                   band                                                                      */
  } b;                                        /*!< bit fields for pcm_pachcnr47 */
} pcm_pachcnr47_t, *ppcm_pachcnr47_t;

/**
  \brief Union type to access pcm_patsr47 (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) channel4-7 time slot assignment register                   */

  struct {
    __IOM uint32_t ch7tsa     : 5;            /*!< [4..0] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch6tsa     : 5;            /*!< [12..8] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch5tsa     : 5;            /*!< [20..16] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch4tsa     : 5;            /*!< [28..24] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
  } b;                                        /*!< bit fields for pcm_patsr47 */
} pcm_patsr47_t, *ppcm_patsr47_t;

/**
  \brief Union type to access pcm_pabsize47 (@ 0x00000040).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000040) channel4-7 buffer size register                            */

  struct {
    __IOM uint32_t ch7bsize   : 8;            /*!< [7..0] channel buffer size in unit of 4(n+1) bytes.                       */
    __IOM uint32_t ch6bsize   : 8;            /*!< [15..8] channel buffer size in unit of 4(n+1) bytes.                      */
    __IOM uint32_t ch5bsize   : 8;            /*!< [23..16] channel buffer size in unit of 4(n+1) bytes.                     */
    __IOM uint32_t ch4bsize   : 8;            /*!< [31..24] channel buffer size in unit of 4(n+1) bytes.                     */
  } b;                                        /*!< bit fields for pcm_pabsize47 */
} pcm_pabsize47_t, *ppcm_pabsize47_t;

/**
  \brief Union type to access pcm_ch4atxbsa (@ 0x00000044).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000044) channel 4 tx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch4atxbsa */
} pcm_ch4atxbsa_t, *ppcm_ch4atxbsa_t;

/**
  \brief Union type to access pcm_ch5atxbsa (@ 0x00000048).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000048) channel 5 tx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch5atxbsa */
} pcm_ch5atxbsa_t, *ppcm_ch5atxbsa_t;

/**
  \brief Union type to access pcm_ch6atxbsa (@ 0x0000004C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000004C) channel 6 tx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch6atxbsa */
} pcm_ch6atxbsa_t, *ppcm_ch6atxbsa_t;

/**
  \brief Union type to access pcm_ch7atxbsa (@ 0x00000050).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000050) channel 7 tx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch7atxbsa */
} pcm_ch7atxbsa_t, *ppcm_ch7atxbsa_t;

/**
  \brief Union type to access pcm_ch4arxbsa (@ 0x00000054).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000054) channel 4 rx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch4arxbsa */
} pcm_ch4arxbsa_t, *ppcm_ch4arxbsa_t;

/**
  \brief Union type to access pcm_ch5arxbsa (@ 0x00000058).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000058) channel 5 rx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch5arxbsa */
} pcm_ch5arxbsa_t, *ppcm_ch5arxbsa_t;

/**
  \brief Union type to access pcm_ch6arxbsa (@ 0x0000005C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000005C) channel 6 rx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch6arxbsa */
} pcm_ch6arxbsa_t, *ppcm_ch6arxbsa_t;

/**
  \brief Union type to access pcm_ch7arxbsa (@ 0x00000060).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000060) channel 7 rx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch7arxbsa */
} pcm_ch7arxbsa_t, *ppcm_ch7arxbsa_t;

/**
  \brief Union type to access pcm_paimr47 (@ 0x00000064).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000064) channel4-7 interrupt mask register                         */

  struct {
    __IOM uint32_t ch7rbp1uaie : 1;           /*!< [0..0] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch7rbp0uaie : 1;           /*!< [1..1] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch7tbp1uaie : 1;           /*!< [2..2] transmit buffer page1 unavailable interrupt enable. 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch7tbp0uaie : 1;           /*!< [3..3] transmit buffer page0 unavailable interrupt enable. 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch7p1rokie : 1;            /*!< [4..4] rx page 1 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch7p0rokie : 1;            /*!< [5..5] rx page 0 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch7p1tokie : 1;            /*!< [6..6] tx page 1 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch7p0tokie : 1;            /*!< [7..7] tx page 0 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch6rbp1uaie : 1;           /*!< [8..8] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch6rbp0uaie : 1;           /*!< [9..9] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch6tbp1uaie : 1;           /*!< [10..10] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch6tbp0uaie : 1;           /*!< [11..11] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch6p1rokie : 1;            /*!< [12..12] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch6p0rokie : 1;            /*!< [13..13] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch6p1tokie : 1;            /*!< [14..14] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch6p0tokie : 1;            /*!< [15..15] tx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch5rbp1uaie : 1;           /*!< [16..16] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch5rbp0uaie : 1;           /*!< [17..17] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch5tbp1uaie : 1;           /*!< [18..18] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch5tbp0uaie : 1;           /*!< [19..19] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch5p1rokie : 1;            /*!< [20..20] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch5p0rokie : 1;            /*!< [21..21] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch5p1tokie : 1;            /*!< [22..22] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch5p0tokie : 1;            /*!< [23..23] tx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch4rbp1uaie : 1;           /*!< [24..24] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch4rbp0uaie : 1;           /*!< [25..25] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch4tbp1uaie : 1;           /*!< [26..26] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch4tbp0uaie : 1;           /*!< [27..27] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch4p1rokie : 1;            /*!< [28..28] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch4p0rokie : 1;            /*!< [29..29] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch4p1tokie : 1;            /*!< [30..30] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch4p0tokie : 1;            /*!< [31..31] tx page 0 ok interrupt enable. 0: disable 1: enable              */
  } b;                                        /*!< bit fields for pcm_paimr47 */
} pcm_paimr47_t, *ppcm_paimr47_t;

/**
  \brief Union type to access pcm_paisr47 (@ 0x00000068).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000068) channel4-7 interrupt status register                       */

  struct {
    __IOM uint32_t ch7rxp1ua  : 1;            /*!< [0..0] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch7rxp0ua  : 1;            /*!< [1..1] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch7txp1ua  : 1;            /*!< [2..2] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch7txp0ua  : 1;            /*!< [3..3] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch7rxp1ip  : 1;            /*!< [4..4] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch7rxp0ip  : 1;            /*!< [5..5] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch7txp1ip  : 1;            /*!< [6..6] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch7txp0ip  : 1;            /*!< [7..7] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch6rxp1ua  : 1;            /*!< [8..8] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch6rxp0ua  : 1;            /*!< [9..9] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch6txp1ua  : 1;            /*!< [10..10] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch6txp0ua  : 1;            /*!< [11..11] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch6rxp1ip  : 1;            /*!< [12..12] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch6rxp0ip  : 1;            /*!< [13..13] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch6txp1ip  : 1;            /*!< [14..14] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch6txp0ip  : 1;            /*!< [15..15] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch5rxp1ua  : 1;            /*!< [16..16] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch5rxp0ua  : 1;            /*!< [17..17] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch5txp1ua  : 1;            /*!< [18..18] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch5txp0ua  : 1;            /*!< [19..19] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch5rxp1ip  : 1;            /*!< [20..20] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch5rxp0ip  : 1;            /*!< [21..21] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch5txp1ip  : 1;            /*!< [22..22] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch5txp0ip  : 1;            /*!< [23..23] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch4rxp1ua  : 1;            /*!< [24..24] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch4rxp0ua  : 1;            /*!< [25..25] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch4txp1ua  : 1;            /*!< [26..26] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch4txp0ua  : 1;            /*!< [27..27] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch4rxp1p   : 1;            /*!< [28..28] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch4rxp0ip  : 1;            /*!< [29..29] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch4txp1ip  : 1;            /*!< [30..30] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch4txp0ip  : 1;            /*!< [31..31] interrupt pending flag write 1 to clear the interrupt.           */
  } b;                                        /*!< bit fields for pcm_paisr47 */
} pcm_paisr47_t, *ppcm_paisr47_t;

/**
  \brief Union type to access pcm_pachcnr811 (@ 0x0000006C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000006C) channel8-11 specific control register                      */

  struct {
    __IOM uint32_t ch11re     : 1;            /*!< [0..0] channel receiver enable. 0: disable 1: enable Reset the
                                                   state by setting 1 to 0                                                   */
    __IOM uint32_t ch11te     : 1;            /*!< [1..1] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch11ua     : 1;            /*!< [2..2] channel u law/ a law select. 0: u law, 1: a law                    */

    __IM  uint32_t            : 5;
    __IOM uint32_t ch10re     : 1;            /*!< [8..8] channel receiver enable. 0: disable 1: enable Reset the
                                                   state by setting 1 to 0                                                   */
    __IOM uint32_t ch10te     : 1;            /*!< [9..9] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch10ua     : 1;            /*!< [10..10] channel u law/ a law select. 0: u law, 1: a law                  */

    __IM  uint32_t            : 5;
    __IOM uint32_t ch9re      : 1;            /*!< [16..16] channel receiver enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch9te      : 1;            /*!< [17..17] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch9ua      : 1;            /*!< [18..18] channel u law/ a law select. 0: u law, 1: a law                  */

    __IM  uint32_t            : 5;
    __IOM uint32_t ch8re      : 1;            /*!< [24..24] channel receiver enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch8te      : 1;            /*!< [25..25] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch8ua      : 1;            /*!< [26..26] channel u law/ a law select. 0: u law, 1: a law                  */
  } b;                                        /*!< bit fields for pcm_pachcnr811 */
} pcm_pachcnr811_t, *ppcm_pachcnr811_t;

/**
  \brief Union type to access pcm_patsr811 (@ 0x00000070).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000070) channel8-11 time slot assignment register                  */

  struct {
    __IOM uint32_t ch11tsa    : 5;            /*!< [4..0] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch10tsa    : 5;            /*!< [12..8] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch9tsa     : 5;            /*!< [20..16] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch8tsa     : 5;            /*!< [28..24] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
  } b;                                        /*!< bit fields for pcm_patsr811 */
} pcm_patsr811_t, *ppcm_patsr811_t;

/**
  \brief Union type to access pcm_pabsize811 (@ 0x00000074).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000074) channel8-11 buffer size register                           */

  struct {
    __IOM uint32_t ch11bsize  : 8;            /*!< [7..0] channel buffer size in unit of 4(n+1) bytes.                       */
    __IOM uint32_t ch10bsize  : 8;            /*!< [15..8] channel buffer size in unit of 4(n+1) bytes.                      */
    __IOM uint32_t ch9bsize   : 8;            /*!< [23..16] channel buffer size in unit of 4(n+1) bytes.                     */
    __IOM uint32_t ch8bsize   : 8;            /*!< [31..24] channel buffer size in unit of 4(n+1) bytes.                     */
  } b;                                        /*!< bit fields for pcm_pabsize811 */
} pcm_pabsize811_t, *ppcm_pabsize811_t;

/**
  \brief Union type to access pcm_ch8atxbsa (@ 0x00000078).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000078) channel 8 tx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch8atxbsa */
} pcm_ch8atxbsa_t, *ppcm_ch8atxbsa_t;

/**
  \brief Union type to access pcm_ch9atxbsa (@ 0x0000007C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000007C) channel 9 tx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch9atxbsa */
} pcm_ch9atxbsa_t, *ppcm_ch9atxbsa_t;

/**
  \brief Union type to access pcm_ch10atxbsa (@ 0x00000080).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000080) channel 10 tx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch10atxbsa */
} pcm_ch10atxbsa_t, *ppcm_ch10atxbsa_t;

/**
  \brief Union type to access pcm_ch11atxbsa (@ 0x00000084).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000084) channel 11 tx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch11atxbsa */
} pcm_ch11atxbsa_t, *ppcm_ch11atxbsa_t;

/**
  \brief Union type to access pcm_ch8arxbsa (@ 0x00000088).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000088) channel 8 rx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch8arxbsa */
} pcm_ch8arxbsa_t, *ppcm_ch8arxbsa_t;

/**
  \brief Union type to access pcm_ch9arxbsa (@ 0x0000008C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000008C) channel 9 rx buffer starting address pointer               */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch9arxbsa */
} pcm_ch9arxbsa_t, *ppcm_ch9arxbsa_t;

/**
  \brief Union type to access pcm_ch10arxbsa (@ 0x00000090).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000090) channel 10 rx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch10arxbsa */
} pcm_ch10arxbsa_t, *ppcm_ch10arxbsa_t;

/**
  \brief Union type to access pcm_ch11arxbsa (@ 0x00000094).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000094) channel 11 rx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch11arxbsa */
} pcm_ch11arxbsa_t, *ppcm_ch11arxbsa_t;

/**
  \brief Union type to access pcm_paimr811 (@ 0x00000098).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000098) channel8-11 interrupt mask register                        */

  struct {
    __IOM uint32_t ch11rbp1uaie : 1;          /*!< [0..0] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch11rbp0uaie : 1;          /*!< [1..1] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch11tbp1uaie : 1;          /*!< [2..2] transmit buffer page1 unavailable interrupt enable. 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch11tbp0uaie : 1;          /*!< [3..3] transmit buffer page0 unavailable interrupt enable. 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch11p1rokie : 1;           /*!< [4..4] rx page 1 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch11p0rokie : 1;           /*!< [5..5] rx page 0 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch11p1tokie : 1;           /*!< [6..6] tx page 1 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch11p0tokie : 1;           /*!< [7..7] tx page 0 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch10rbp1uaie : 1;          /*!< [8..8] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch10rbp0uaie : 1;          /*!< [9..9] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch10tbp1uaie : 1;          /*!< [10..10] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch10tbp0uaie : 1;          /*!< [11..11] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch10p1rokie : 1;           /*!< [12..12] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch10p0rokie : 1;           /*!< [13..13] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch10p1tokie : 1;           /*!< [14..14] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch10p0tokie : 1;           /*!< [15..15] tx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch9rbp1uaie : 1;           /*!< [16..16] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch9rbp0uaie : 1;           /*!< [17..17] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch9tbp1uaie : 1;           /*!< [18..18] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch9tbp0uaie : 1;           /*!< [19..19] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch9p1rokie : 1;            /*!< [20..20] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch9p0rokie : 1;            /*!< [21..21] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch9p1tokie : 1;            /*!< [22..22] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch9p0tokie : 1;            /*!< [23..23] tx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch8rbp1uaie : 1;           /*!< [24..24] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch8rbp0uaie : 1;           /*!< [25..25] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch8tbp1uaie : 1;           /*!< [26..26] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch8tbp0uaie : 1;           /*!< [27..27] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch8p1rokie : 1;            /*!< [28..28] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch8p0rokie : 1;            /*!< [29..29] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch8p1tokie : 1;            /*!< [30..30] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch8p0tokie : 1;            /*!< [31..31] tx page 0 ok interrupt enable. 0: disable 1: enable              */
  } b;                                        /*!< bit fields for pcm_paimr811 */
} pcm_paimr811_t, *ppcm_paimr811_t;

/**
  \brief Union type to access pcm_paisr811 (@ 0x0000009C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000009C) channel8-11 interrupt status register                      */

  struct {
    __IOM uint32_t ch11rxp1ua : 1;            /*!< [0..0] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch11rxp0ua : 1;            /*!< [1..1] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch11txp1ua : 1;            /*!< [2..2] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch11txp0ua : 1;            /*!< [3..3] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch11rxp1ip : 1;            /*!< [4..4] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch11rxp0ip : 1;            /*!< [5..5] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch11txp1ip : 1;            /*!< [6..6] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch11txp0ip : 1;            /*!< [7..7] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch10rxp1ua : 1;            /*!< [8..8] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch10rxp0ua : 1;            /*!< [9..9] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch10txp1ua : 1;            /*!< [10..10] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch10txp0ua : 1;            /*!< [11..11] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch10rxp1ip : 1;            /*!< [12..12] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch10rxp0ip : 1;            /*!< [13..13] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch10txp1ip : 1;            /*!< [14..14] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch10txp0ip : 1;            /*!< [15..15] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch9rxp1ua  : 1;            /*!< [16..16] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch9rxp0ua  : 1;            /*!< [17..17] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch9txp1ua  : 1;            /*!< [18..18] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch9txp0ua  : 1;            /*!< [19..19] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch9rxp1ip  : 1;            /*!< [20..20] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch9rxp0ip  : 1;            /*!< [21..21] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch9txp1ip  : 1;            /*!< [22..22] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch9txp0ip  : 1;            /*!< [23..23] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch8rxp1ua  : 1;            /*!< [24..24] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch8rxp0ua  : 1;            /*!< [25..25] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch8txp1ua  : 1;            /*!< [26..26] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch8txp0ua  : 1;            /*!< [27..27] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch8rxp1p   : 1;            /*!< [28..28] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch8rxp0ip  : 1;            /*!< [29..29] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch8txp1ip  : 1;            /*!< [30..30] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch8txp0ip  : 1;            /*!< [31..31] interrupt pending flag write 1 to clear the interrupt.           */
  } b;                                        /*!< bit fields for pcm_paisr811 */
} pcm_paisr811_t, *ppcm_paisr811_t;

/**
  \brief Union type to access pcm_pachcnr1215 (@ 0x000000A0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A0) channel12-15 specific control register                     */

  struct {
    __IOM uint32_t ch15re     : 1;            /*!< [0..0] channel receiver enable. 0: disable 1: enable Reset the
                                                   state by setting 1 to 0                                                   */
    __IOM uint32_t ch15te     : 1;            /*!< [1..1] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch15ua     : 1;            /*!< [2..2] channel u law/ a law select. 0: u law, 1: a law                    */

    __IM  uint32_t            : 5;
    __IOM uint32_t ch14re     : 1;            /*!< [8..8] channel receiver enable. 0: disable 1: enable Reset the
                                                   state by setting 1 to 0                                                   */
    __IOM uint32_t ch14te     : 1;            /*!< [9..9] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch14ua     : 1;            /*!< [10..10] channel u law/ a law select. 0: u law, 1: a law                  */

    __IM  uint32_t            : 5;
    __IOM uint32_t ch13re     : 1;            /*!< [16..16] channel receiver enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch13te     : 1;            /*!< [17..17] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch13ua     : 1;            /*!< [18..18] channel u law/ a law select. 0: u law, 1: a law                  */

    __IM  uint32_t            : 5;
    __IOM uint32_t ch12re     : 1;            /*!< [24..24] channel receiver enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch12te     : 1;            /*!< [25..25] channel transmitter enable. 0: disable 1: enable Reset
                                                   the state by setting 1 to 0                                               */
    __IOM uint32_t ch12ua     : 1;            /*!< [26..26] channel u law/ a law select. 0: u law, 1: a law                  */
  } b;                                        /*!< bit fields for pcm_pachcnr1215 */
} pcm_pachcnr1215_t, *ppcm_pachcnr1215_t;

/**
  \brief Union type to access pcm_patsr1215 (@ 0x000000A4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A4) channel12-15 time slot assignment register                 */

  struct {
    __IOM uint32_t ch15tsa    : 5;            /*!< [4..0] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch14tsa    : 5;            /*!< [12..8] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch13tsa    : 5;            /*!< [20..16] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch12tsa    : 5;            /*!< [28..24] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
  } b;                                        /*!< bit fields for pcm_patsr1215 */
} pcm_patsr1215_t, *ppcm_patsr1215_t;

/**
  \brief Union type to access pcm_pabsize1215 (@ 0x000000A8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A8) channel12-15 buffer size register                          */

  struct {
    __IOM uint32_t ch15bsize  : 8;            /*!< [7..0] channel buffer size in unit of 4(n+1) bytes.                       */
    __IOM uint32_t ch14bsize  : 8;            /*!< [15..8] channel buffer size in unit of 4(n+1) bytes.                      */
    __IOM uint32_t ch13bsize  : 8;            /*!< [23..16] channel buffer size in unit of 4(n+1) bytes.                     */
    __IOM uint32_t ch12bsize  : 8;            /*!< [31..24] channel buffer size in unit of 4(n+1) bytes.                     */
  } b;                                        /*!< bit fields for pcm_pabsize1215 */
} pcm_pabsize1215_t, *ppcm_pabsize1215_t;

/**
  \brief Union type to access pcm_ch12atxbsa (@ 0x000000AC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000AC) channel 12 tx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch12atxbsa */
} pcm_ch12atxbsa_t, *ppcm_ch12atxbsa_t;

/**
  \brief Union type to access pcm_ch13atxbsa (@ 0x000000B0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000B0) channel 13 tx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch13atxbsa */
} pcm_ch13atxbsa_t, *ppcm_ch13atxbsa_t;

/**
  \brief Union type to access pcm_ch14atxbsa (@ 0x000000B4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000B4) channel 14 tx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch14atxbsa */
} pcm_ch14atxbsa_t, *ppcm_ch14atxbsa_t;

/**
  \brief Union type to access pcm_ch15atxbsa (@ 0x000000B8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000B8) channel 15 tx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch15atxbsa */
} pcm_ch15atxbsa_t, *ppcm_ch15atxbsa_t;

/**
  \brief Union type to access pcm_ch12arxbsa (@ 0x000000BC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000BC) channel 12 rx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch12arxbsa */
} pcm_ch12arxbsa_t, *ppcm_ch12arxbsa_t;

/**
  \brief Union type to access pcm_ch13arxbsa (@ 0x000000C0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000C0) channel 13 rx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch13arxbsa */
} pcm_ch13arxbsa_t, *ppcm_ch13arxbsa_t;

/**
  \brief Union type to access pcm_ch14arxbsa (@ 0x000000C4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000C4) channel 14 rx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch14arxbsa */
} pcm_ch14arxbsa_t, *ppcm_ch14arxbsa_t;

/**
  \brief Union type to access pcm_ch15arxbsa (@ 0x000000C8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000C8) channel 15 rx buffer starting address pointer              */

  struct {
    __IOM uint32_t p0own      : 1;            /*!< [0..0] page0 own bit 1: page0 owned by pcm controller 0: page0
                                                   owned by cpu                                                              */
    __IOM uint32_t p1own      : 1;            /*!< [1..1] page1 own bit 1: page1 owned by pcm controller 0: page1
                                                   owned by cpu                                                              */
    __IOM uint32_t bufptr     : 30;           /*!< [31..2] physical buffer starting address. the buffer address
                                                   must word aligned.                                                        */
  } b;                                        /*!< bit fields for pcm_ch15arxbsa */
} pcm_ch15arxbsa_t, *ppcm_ch15arxbsa_t;

/**
  \brief Union type to access pcm_paimr1215 (@ 0x000000CC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000CC) channel12-15 interrupt mask register                       */

  struct {
    __IOM uint32_t ch15rbp1uaie : 1;          /*!< [0..0] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch15rbp0uaie : 1;          /*!< [1..1] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch15tbp1uaie : 1;          /*!< [2..2] transmit buffer page1 unavailable interrupt enable. 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch15tbp0uaie : 1;          /*!< [3..3] transmit buffer page0 unavailable interrupt enable. 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch15p1rokie : 1;           /*!< [4..4] rx page 1 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch15p0rokie : 1;           /*!< [5..5] rx page 0 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch15p1tokie : 1;           /*!< [6..6] tx page 1 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch15p0tokie : 1;           /*!< [7..7] tx page 0 ok interrupt enable. 0: disable 1: enable                */
    __IOM uint32_t ch14rbp1uaie : 1;          /*!< [8..8] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch14rbp0uaie : 1;          /*!< [9..9] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch14tbp1uaie : 1;          /*!< [10..10] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch14tbp0uaie : 1;          /*!< [11..11] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch14p1rokie : 1;           /*!< [12..12] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch14p0rokie : 1;           /*!< [13..13] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch14p1tokie : 1;           /*!< [14..14] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch14p0tokie : 1;           /*!< [15..15] tx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch13rbp1uaie : 1;          /*!< [16..16] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch13rbp0uaie : 1;          /*!< [17..17] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch13tbp1uaie : 1;          /*!< [18..18] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch13tbp0uaie : 1;          /*!< [19..19] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch13p1rokie : 1;           /*!< [20..20] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch13p0rokie : 1;           /*!< [21..21] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch13p1tokie : 1;           /*!< [22..22] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch13p0tokie : 1;           /*!< [23..23] tx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch12rbp1uaie : 1;          /*!< [24..24] receive buffer page1 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch12rbp0uaie : 1;          /*!< [25..25] receive buffer page0 unavailable interrupt enable 0:
                                                   disable 1: enable                                                         */
    __IOM uint32_t ch12tbp1uaie : 1;          /*!< [26..26] transmit buffer page1 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch12tbp0uaie : 1;          /*!< [27..27] transmit buffer page0 unavailable interrupt enable.
                                                   0: disable 1: enable                                                      */
    __IOM uint32_t ch12p1rokie : 1;           /*!< [28..28] rx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch12p0rokie : 1;           /*!< [29..29] rx page 0 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch12p1tokie : 1;           /*!< [30..30] tx page 1 ok interrupt enable. 0: disable 1: enable              */
    __IOM uint32_t ch12p0tokie : 1;           /*!< [31..31] tx page 0 ok interrupt enable. 0: disable 1: enable              */
  } b;                                        /*!< bit fields for pcm_paimr1215 */
} pcm_paimr1215_t, *ppcm_paimr1215_t;

/**
  \brief Union type to access pcm_paisr1215 (@ 0x000000D0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000D0) channel12-15 interrupt status register                     */

  struct {
    __IOM uint32_t ch15rxp1ua : 1;            /*!< [0..0] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch15rxp0ua : 1;            /*!< [1..1] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch15txp1ua : 1;            /*!< [2..2] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch15txp0ua : 1;            /*!< [3..3] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch15rxp1ip : 1;            /*!< [4..4] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch15rxp0ip : 1;            /*!< [5..5] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch15txp1ip : 1;            /*!< [6..6] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch15txp0ip : 1;            /*!< [7..7] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch14rxp1ua : 1;            /*!< [8..8] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch14rxp0ua : 1;            /*!< [9..9] interrupt pending flag write 1 to clear the interrupt.             */
    __IOM uint32_t ch14txp1ua : 1;            /*!< [10..10] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch14txp0ua : 1;            /*!< [11..11] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch14rxp1ip : 1;            /*!< [12..12] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch14rxp0ip : 1;            /*!< [13..13] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch14txp1ip : 1;            /*!< [14..14] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch14txp0ip : 1;            /*!< [15..15] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch13rxp1ua : 1;            /*!< [16..16] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch13rxp0ua : 1;            /*!< [17..17] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch13txp1ua : 1;            /*!< [18..18] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch13txp0ua : 1;            /*!< [19..19] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch13rxp1ip : 1;            /*!< [20..20] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch13rxp0ip : 1;            /*!< [21..21] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch13txp1ip : 1;            /*!< [22..22] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch13txp0ip : 1;            /*!< [23..23] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch12rxp1ua : 1;            /*!< [24..24] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch12rxp0ua : 1;            /*!< [25..25] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch12txp1ua : 1;            /*!< [26..26] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch12txp0ua : 1;            /*!< [27..27] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch12rxp1p  : 1;            /*!< [28..28] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch12rxp0ip : 1;            /*!< [29..29] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch12txp1ip : 1;            /*!< [30..30] interrupt pending flag write 1 to clear the interrupt.           */
    __IOM uint32_t ch12txp0ip : 1;            /*!< [31..31] interrupt pending flag write 1 to clear the interrupt.           */
  } b;                                        /*!< bit fields for pcm_paisr1215 */
} pcm_paisr1215_t, *ppcm_paisr1215_t;

/**
  \brief Union type to access pcm_paintmap (@ 0x000000D4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000D4) intmap                                                     */

  struct {
    __IOM uint32_t intmap     : 32;           /*!< [31..0] Not support                                                       */
  } b;                                        /*!< bit fields for pcm_paintmap */
} pcm_paintmap_t, *ppcm_paintmap_t;

/**
  \brief Union type to access pcm_pawtsr03 (@ 0x000000D8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000D8) channel0-3 wideband time slot assignment register          */

  struct {
    __IOM uint32_t ch3wtsa    : 5;            /*!< [4..0] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch2wtsa    : 5;            /*!< [12..8] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch1wtsa    : 5;            /*!< [20..16] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch0wtsa    : 5;            /*!< [28..24] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
  } b;                                        /*!< bit fields for pcm_pawtsr03 */
} pcm_pawtsr03_t, *ppcm_pawtsr03_t;

/**
  \brief Union type to access pcm_pawtsr47 (@ 0x000000DC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000DC) channel4-7 wideband time slot assignment register          */

  struct {
    __IOM uint32_t ch7tsa     : 5;            /*!< [4..0] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch6tsa     : 5;            /*!< [12..8] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch5tsa     : 5;            /*!< [20..16] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
    __IM  uint32_t            : 3;
    __IOM uint32_t ch4tsa     : 5;            /*!< [28..24] pcm interface a time slot assignment for rx/tx fifo.
                                                   Slot0 - slot31 if configured as 16 bit linear mode, only
                                                   even number time slot is allowed                                          */
  } b;                                        /*!< bit fields for pcm_pawtsr47 */
} pcm_pawtsr47_t, *ppcm_pawtsr47_t;

/**
  \brief Union type to access pcm_bufowchk (@ 0x000000E0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000E0) pcm rx buffer data overwrite indicate                      */

  struct {
    __IOM uint32_t ch0overw   : 1;            /*!< [0..0] rx buffer data overwrite indicate. write 1 to clear the
                                                   status.                                                                   */
    __IOM uint32_t ch1overw   : 1;            /*!< [1..1] rx buffer data overwrite indicate. write 1 to clear the
                                                   status.                                                                   */
    __IOM uint32_t ch2overw   : 1;            /*!< [2..2] rx buffer data overwrite indicate. write 1 to clear the
                                                   status.                                                                   */
    __IOM uint32_t ch3overw   : 1;            /*!< [3..3] rx buffer data overwrite indicate. write 1 to clear the
                                                   status.                                                                   */
    __IOM uint32_t ch4overw   : 1;            /*!< [4..4] rx buffer data overwrite indicate. write 1 to clear the
                                                   status.                                                                   */
    __IOM uint32_t ch5overw   : 1;            /*!< [5..5] rx buffer data overwrite indicate. write 1 to clear the
                                                   status.                                                                   */
    __IOM uint32_t ch6overw   : 1;            /*!< [6..6] rx buffer data overwrite indicate. write 1 to clear the
                                                   status.                                                                   */
    __IOM uint32_t ch7overw   : 1;            /*!< [7..7] rx buffer data overwrite indicate. write 1 to clear the
                                                   status.                                                                   */
    __IOM uint32_t ch8overw   : 1;            /*!< [8..8] rx buffer data overwrite indicate. write 1 to clear the
                                                   status.                                                                   */
    __IOM uint32_t ch9overw   : 1;            /*!< [9..9] rx buffer data overwrite indicate. write 1 to clear the
                                                   status.                                                                   */
    __IOM uint32_t ch10overw  : 1;            /*!< [10..10] rx buffer data overwrite indicate. write 1 to clear
                                                   the status.                                                               */
    __IOM uint32_t ch11overw  : 1;            /*!< [11..11] rx buffer data overwrite indicate. write 1 to clear
                                                   the status.                                                               */
    __IOM uint32_t ch12overw  : 1;            /*!< [12..12] rx buffer data overwrite indicate. write 1 to clear
                                                   the status.                                                               */
    __IOM uint32_t ch13overw  : 1;            /*!< [13..13] rx buffer data overwrite indicate. write 1 to clear
                                                   the status.                                                               */
    __IOM uint32_t ch14overw  : 1;            /*!< [14..14] rx buffer data overwrite indicate. write 1 to clear
                                                   the status.                                                               */
    __IOM uint32_t ch15overw  : 1;            /*!< [15..15] rx buffer data overwrite indicate. write 1 to clear
                                                   the status.                                                               */
  } b;                                        /*!< bit fields for pcm_bufowchk */
} pcm_bufowchk_t, *ppcm_bufowchk_t;

/** @} */ /* End of group hs_hal_pcm_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_PCM_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_PCM_TYPE_H_

