/**************************************************************************//**
 * @file      rtl8195blp_cir_type.h
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

#ifndef _RTL8195BLP_CIR_TYPE_H_
#define _RTL8195BLP_CIR_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_CIR_REG_TYPE

/**
 * @addtogroup ls_hal_cir_reg CIR Registers.
 * @ingroup ls_hal_cir
 * @{
 */

/**
  \brief Union type to access cir_ctrl (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) CIR Control Register                                       */

  struct {
    __IOM uint32_t tdiv       : 8;            /*!< [7..0] RX input sampling and trigger tick event. RX input sampling
                                                   clock = SCLK/(TDIV+1). Tick period (sec) = (TDIV+1)/SCLK.                 */
    __IM  uint32_t            : 20;
    __IOM uint32_t txen       : 1;            /*!< [28..28] 1: TX output enable 0: TX output disable                         */
    __IOM uint32_t rxen       : 1;            /*!< [29..29] 1: RX input enable. Can receive the RX event. 0: RX
                                                   input disable. Receive the RX event is invalid.                           */
    __IOM uint32_t txrst      : 1;            /*!< [30..30] 1: reset enabled 0: reset released (normal works)                */
    __IOM uint32_t rxrst      : 1;            /*!< [31..31] 1: reset enabled 0: reset released (normal works)                */
  } b;                                        /*!< bit fields for cir_ctrl */
} cir_ctrl_t, *pcir_ctrl_t;

/**
  \brief Union type to access cir_cgen (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) Carrier Generator Register                                 */

  struct {
    __IOM uint32_t cdiv       : 8;            /*!< [7..0] Carrier tick period (sec) = (CDIV+1)/SCLK.                         */
    __IOM uint32_t cltick     : 5;            /*!< [12..8] The freq. of the carrier clock = SCLK/(((CHTICK+1)+(CLTICK+1))
                                                   x (CDIV+1)).                                                              */
    __IM  uint32_t            : 3;
    __IOM uint32_t chtick     : 5;            /*!< [20..16] The freq. of the carrier clock = SCLK/(((CHTICK+1)+(CLTICK+1))
                                                   x (CDIV+1)).                                                              */
  } b;                                        /*!< bit fields for cir_cgen */
} cir_cgen_t, *pcir_cgen_t;

/**
  \brief Union type to access cir_fsts (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) FIFO Status Register                                       */

  struct {
    __IM  uint32_t rxrdy      : 1;            /*!< [0..0] 1: At least 1 bytes of RX code in the RX FIFO. 0: No
                                                   data in the RX FIFO.                                                      */
    __IM  uint32_t txfull     : 1;            /*!< [1..1] 1: At least 1 bytes of space in the TX FIFO. 0: No space
                                                   in the TX FIFO (TX FIFO is full).                                         */
    __IM  uint32_t tx2emp     : 1;            /*!< [2..2] 1: At least 2 bytes of space in the TX FIFO. 0: one or
                                                   no space in the TX FIFO.                                                  */
  } b;                                        /*!< bit fields for cir_fsts */
} cir_fsts_t, *pcir_fsts_t;

/**
  \brief Union type to access cir_rxrd (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) RX Code Read Register                                      */

  struct {
    __IM  uint32_t rxrd       : 8;            /*!< [7..0] Read this register will get 1 byte of IR RX symbol code
                                                   from the RX FIFO.                                                         */
  } b;                                        /*!< bit fields for cir_rxrd */
} cir_rxrd_t, *pcir_rxrd_t;

/**
  \brief Union type to access cir_txwr (@ 0x00000010).
*/
typedef union {
  __OM  uint32_t w;                           /*!< (@ 0x00000010) TX Code Write Register                                     */

  struct {
    __OM  uint32_t txwr       : 8;            /*!< [7..0] Write this register will put 1 byte of TX IR code to
                                                   the TX FIFO.                                                              */
  } b;                                        /*!< bit fields for cir_txwr */
} cir_txwr_t, *pcir_txwr_t;

/**
  \brief Union type to access cir_irt (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) IR RX Timeout Register                                     */

  struct {
    __IOM uint32_t idto       : 16;           /*!< [15..0] IR RX idle timeout.                                               */
    __IOM uint32_t csto       : 8;            /*!< [23..16] IR RX Carrier clock sense timeout.                               */
  } b;                                        /*!< bit fields for cir_irt */
} cir_irt_t, *pcir_irt_t;

/**
  \brief Union type to access cir_symcfg0 (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) IR RX Symbol Configuration 0 Register                      */

  struct {
    __IOM uint32_t symccc_db  : 12;           /*!< [11..0] This filed define the down bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symccc_ub  : 12;           /*!< [23..12] This filed define the up bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symtyp     : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:
                                                   Space symbol with low level: RX input signal level keeps
                                                   low for a given period. 1: Space symbol with high level:
                                                   RX input signal level keeps high for a given period. 2:
                                                   Carrier symbol: carrier clock continuously present on the
                                                   RX input signal for a given period.                                       */
    __IM  uint32_t            : 5;
    __IOM uint32_t symen      : 1;            /*!< [31..31] To control the enable of this IR symbol. 1: Enable
                                                   0: Disable                                                                */
  } b;                                        /*!< bit fields for cir_symcfg0 */
} cir_symcfg0_t, *pcir_symcfg0_t;

/**
  \brief Union type to access cir_rxsymt0 (@ 0x0000001C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000001C) IR RX Symbol Time 0 Register                               */

  struct {
    __IOM uint32_t symt_db    : 16;           /*!< [15..0] This filed define the down bond of the period of the
                                                   symbol.                                                                   */
    __IOM uint32_t symt_ub    : 16;           /*!< [31..16] This filed define the up bond of the period of the
                                                   symbol.                                                                   */
  } b;                                        /*!< bit fields for cir_rxsymt0 */
} cir_rxsymt0_t, *pcir_rxsymt0_t;

/**
  \brief Union type to access cir_symcfg1 (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) IR RX Symbol Configuration 1 Register                      */

  struct {
    __IOM uint32_t symccc_db  : 12;           /*!< [11..0] This filed define the down bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symccc_ub  : 12;           /*!< [23..12] This filed define the up bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symtyp     : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:
                                                   Space symbol with low level: RX input signal level keeps
                                                   low for a given period. 1: Space symbol with high level:
                                                   RX input signal level keeps high for a given period. 2:
                                                   Carrier symbol: carrier clock continuously present on the
                                                   RX input signal for a given period.                                       */
    __IM  uint32_t            : 5;
    __IOM uint32_t symen      : 1;            /*!< [31..31] To control the enable of this IR symbol. 1: Enable
                                                   0: Disable                                                                */
  } b;                                        /*!< bit fields for cir_symcfg1 */
} cir_symcfg1_t, *pcir_symcfg1_t;

/**
  \brief Union type to access cir_rxsymt1 (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) IR RX Symbol Time 1 Register                               */

  struct {
    __IOM uint32_t symt_db    : 16;           /*!< [15..0] This filed define the down bond of the period of the
                                                   symbol.                                                                   */
    __IOM uint32_t symt_ub    : 16;           /*!< [31..16] This filed define the up bond of the period of the
                                                   symbol.                                                                   */
  } b;                                        /*!< bit fields for cir_rxsymt1 */
} cir_rxsymt1_t, *pcir_rxsymt1_t;

/**
  \brief Union type to access cir_symcfg2 (@ 0x00000028).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000028) IR RX Symbol Configuration 2 Register                      */

  struct {
    __IOM uint32_t symccc_db  : 12;           /*!< [11..0] This filed define the down bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symccc_ub  : 12;           /*!< [23..12] This filed define the up bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symtyp     : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:
                                                   Space symbol with low level: RX input signal level keeps
                                                   low for a given period. 1: Space symbol with high level:
                                                   RX input signal level keeps high for a given period. 2:
                                                   Carrier symbol: carrier clock continuously present on the
                                                   RX input signal for a given period.                                       */
    __IM  uint32_t            : 5;
    __IOM uint32_t symen      : 1;            /*!< [31..31] To control the enable of this IR symbol. 1: Enable
                                                   0: Disable                                                                */
  } b;                                        /*!< bit fields for cir_symcfg2 */
} cir_symcfg2_t, *pcir_symcfg2_t;

/**
  \brief Union type to access cir_rxsymt2 (@ 0x0000002C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000002C) IR RX Symbol Time 2 Register                               */

  struct {
    __IOM uint32_t symt_db    : 16;           /*!< [15..0] This filed define the down bond of the period of the
                                                   symbol.                                                                   */
    __IOM uint32_t symt_ub    : 16;           /*!< [31..16] This filed define the up bond of the period of the
                                                   symbol.                                                                   */
  } b;                                        /*!< bit fields for cir_rxsymt2 */
} cir_rxsymt2_t, *pcir_rxsymt2_t;

/**
  \brief Union type to access cir_symcfg3 (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) IR RX Symbol Configuration 3 Register                      */

  struct {
    __IOM uint32_t symccc_db  : 12;           /*!< [11..0] This filed define the down bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symccc_ub  : 12;           /*!< [23..12] This filed define the up bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symtyp     : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:
                                                   Space symbol with low level: RX input signal level keeps
                                                   low for a given period. 1: Space symbol with high level:
                                                   RX input signal level keeps high for a given period. 2:
                                                   Carrier symbol: carrier clock continuously present on the
                                                   RX input signal for a given period.                                       */
    __IM  uint32_t            : 5;
    __IOM uint32_t symen      : 1;            /*!< [31..31] To control the enable of this IR symbol. 1: Enable
                                                   0: Disable                                                                */
  } b;                                        /*!< bit fields for cir_symcfg3 */
} cir_symcfg3_t, *pcir_symcfg3_t;

/**
  \brief Union type to access cir_rxsymt3 (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) IR RX Symbol Time 3 Register                               */

  struct {
    __IOM uint32_t symt_db    : 16;           /*!< [15..0] This filed define the down bond of the period of the
                                                   symbol.                                                                   */
    __IOM uint32_t symt_ub    : 16;           /*!< [31..16] This filed define the up bond of the period of the
                                                   symbol.                                                                   */
  } b;                                        /*!< bit fields for cir_rxsymt3 */
} cir_rxsymt3_t, *pcir_rxsymt3_t;

/**
  \brief Union type to access cir_symcfg4 (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) IR RX Symbol Configuration 4 Register                      */

  struct {
    __IOM uint32_t symccc_db  : 12;           /*!< [11..0] This filed define the down bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symccc_ub  : 12;           /*!< [23..12] This filed define the up bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symtyp     : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:
                                                   Space symbol with low level: RX input signal level keeps
                                                   low for a given period. 1: Space symbol with high level:
                                                   RX input signal level keeps high for a given period. 2:
                                                   Carrier symbol: carrier clock continuously present on the
                                                   RX input signal for a given period.                                       */
    __IM  uint32_t            : 5;
    __IOM uint32_t symen      : 1;            /*!< [31..31] To control the enable of this IR symbol. 1: Enable
                                                   0: Disable                                                                */
  } b;                                        /*!< bit fields for cir_symcfg4 */
} cir_symcfg4_t, *pcir_symcfg4_t;

/**
  \brief Union type to access cir_rxsymt4 (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) IR RX Symbol Time 4 Register                               */

  struct {
    __IOM uint32_t symt_db    : 16;           /*!< [15..0] This filed define the down bond of the period of the
                                                   symbol.                                                                   */
    __IOM uint32_t symt_ub    : 16;           /*!< [31..16] This filed define the up bond of the period of the
                                                   symbol.                                                                   */
  } b;                                        /*!< bit fields for cir_rxsymt4 */
} cir_rxsymt4_t, *pcir_rxsymt4_t;

/**
  \brief Union type to access cir_symcfg5 (@ 0x00000040).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000040) IR RX Symbol Configuration 5 Register                      */

  struct {
    __IOM uint32_t symccc_db  : 12;           /*!< [11..0] This filed define the down bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symccc_ub  : 12;           /*!< [23..12] This filed define the up bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symtyp     : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:
                                                   Space symbol with low level: RX input signal level keeps
                                                   low for a given period. 1: Space symbol with high level:
                                                   RX input signal level keeps high for a given period. 2:
                                                   Carrier symbol: carrier clock continuously present on the
                                                   RX input signal for a given period.                                       */
    __IM  uint32_t            : 5;
    __IOM uint32_t symen      : 1;            /*!< [31..31] To control the enable of this IR symbol. 1: Enable
                                                   0: Disable                                                                */
  } b;                                        /*!< bit fields for cir_symcfg5 */
} cir_symcfg5_t, *pcir_symcfg5_t;

/**
  \brief Union type to access cir_rxsymt5 (@ 0x00000044).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000044) IR RX Symbol Time 5 Register                               */

  struct {
    __IOM uint32_t symt_db    : 16;           /*!< [15..0] This filed define the down bond of the period of the
                                                   symbol.                                                                   */
    __IOM uint32_t symt_ub    : 16;           /*!< [31..16] This filed define the up bond of the period of the
                                                   symbol.                                                                   */
  } b;                                        /*!< bit fields for cir_rxsymt5 */
} cir_rxsymt5_t, *pcir_rxsymt5_t;

/**
  \brief Union type to access cir_symcfg6 (@ 0x00000048).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000048) IR RX Symbol Configuration 6 Register                      */

  struct {
    __IOM uint32_t symccc_db  : 12;           /*!< [11..0] This filed define the down bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symccc_ub  : 12;           /*!< [23..12] This filed define the up bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symtyp     : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:
                                                   Space symbol with low level: RX input signal level keeps
                                                   low for a given period. 1: Space symbol with high level:
                                                   RX input signal level keeps high for a given period. 2:
                                                   Carrier symbol: carrier clock continuously present on the
                                                   RX input signal for a given period.                                       */
    __IM  uint32_t            : 5;
    __IOM uint32_t symen      : 1;            /*!< [31..31] To control the enable of this IR symbol. 1: Enable
                                                   0: Disable                                                                */
  } b;                                        /*!< bit fields for cir_symcfg6 */
} cir_symcfg6_t, *pcir_symcfg6_t;

/**
  \brief Union type to access cir_rxsymt6 (@ 0x0000004C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000004C) IR RX Symbol Time 6 Register                               */

  struct {
    __IOM uint32_t symt_db    : 16;           /*!< [15..0] This filed define the down bond of the period of the
                                                   symbol.                                                                   */
    __IOM uint32_t symt_ub    : 16;           /*!< [31..16] This filed define the up bond of the period of the
                                                   symbol.                                                                   */
  } b;                                        /*!< bit fields for cir_rxsymt6 */
} cir_rxsymt6_t, *pcir_rxsymt6_t;

/**
  \brief Union type to access cir_symcfg7 (@ 0x00000050).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000050) IR RX Symbol Configuration 7 Register                      */

  struct {
    __IOM uint32_t symccc_db  : 12;           /*!< [11..0] This filed define the down bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symccc_ub  : 12;           /*!< [23..12] This filed define the up bond of the valid carrier
                                                   clock cycles of the symbol.                                               */
    __IOM uint32_t symtyp     : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:
                                                   Space symbol with low level: RX input signal level keeps
                                                   low for a given period. 1: Space symbol with high level:
                                                   RX input signal level keeps high for a given period. 2:
                                                   Carrier symbol: carrier clock continuously present on the
                                                   RX input signal for a given period.                                       */
    __IM  uint32_t            : 5;
    __IOM uint32_t symen      : 1;            /*!< [31..31] To control the enable of this IR symbol. 1: Enable
                                                   0: Disable                                                                */
  } b;                                        /*!< bit fields for cir_symcfg7 */
} cir_symcfg7_t, *pcir_symcfg7_t;

/**
  \brief Union type to access cir_rxsymt7 (@ 0x00000054).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000054) IR RX Symbol Time 7 Register                               */

  struct {
    __IOM uint32_t symt_db    : 16;           /*!< [15..0] This filed define the down bond of the period of the
                                                   symbol.                                                                   */
    __IOM uint32_t symt_ub    : 16;           /*!< [31..16] This filed define the up bond of the period of the
                                                   symbol.                                                                   */
  } b;                                        /*!< bit fields for cir_rxsymt7 */
} cir_rxsymt7_t, *pcir_rxsymt7_t;

/**
  \brief Union type to access cir_rxsymchg (@ 0x00000058).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000058) RX Symbol Change Register                                  */

  struct {
    __IOM uint32_t rxsymcode0 : 4;            /*!< [3..0] The symbol code RXSYMCODE0 is replaced with RXSYM0L_PRDC
                                                   and RXSYM0H_PRDC. When the value is zero, this is inactive.               */
    __IM  uint32_t            : 4;
    __IOM uint32_t rxsym0l_prdc : 4;          /*!< [11..8] This is the low symbol code for replacing RXSYMCODE0.When
                                                   the value is zero, this is inactive.                                      */
    __IOM uint32_t rxsym0h_prdc : 4;          /*!< [15..12] This is the high symbol code for replacing RXSYMCODE0.When
                                                   the value is zero, this is inactive.                                      */
    __IOM uint32_t rxsymcode1 : 4;            /*!< [19..16] The symbol code RXSYMCODE1 is replaced with RXSYM1L_PRDC
                                                   and RXSYM1H_PRDC. When the value is zero, this is inactive.               */
    __IM  uint32_t            : 4;
    __IOM uint32_t rxsym1l_prdc : 4;          /*!< [27..24] This is the low symbol code for replacing RXSYMCODE1.When
                                                   the value is zero, this is inactive.                                      */
    __IOM uint32_t rxsym1h_prdc : 4;          /*!< [31..28] This is the high symbol code for replacing RXSYMCODE1.When
                                                   the value is zero, this is inactive.                                      */
  } b;                                        /*!< bit fields for cir_rxsymchg */
} cir_rxsymchg_t, *pcir_rxsymchg_t;

/**
  \brief Union type to access cir_rxdcctrl (@ 0x0000005C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000005C) RX Decode Control Register                                 */

  struct {
    __IOM uint32_t rxdc_en    : 1;            /*!< [0..0] If RXDC_EN is disable, RX start match is not valid and
                                                   the decode process is inactive. 0: Disable. 1: Enable                     */
    __IOM uint32_t rxfifodis  : 1;            /*!< [1..1] 0: RX FIFO can receive the RX symbol code. 1: RX FIFO
                                                   cannot receive the RX symbol code                                         */
    __IOM uint32_t monitor_en : 1;            /*!< [2..2] Make the monitor match and make MONITOR_EN return to
                                                   0. That monitor the number of bits is MONICNT. 0: Disable.
                                                   1: Enable                                                                 */
    __IM  uint32_t            : 21;
    __IOM uint32_t monicnt    : 5;            /*!< [28..24] When MONITOR_EN is enable, monitor t bits is 0~31:
                                                   monitor 1~32 bit                                                          */
  } b;                                        /*!< bit fields for cir_rxdcctrl */
} cir_rxdcctrl_t, *pcir_rxdcctrl_t;

/**
  \brief Union type to access cir_rxsymdc (@ 0x00000060).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000060) RX Symbol Decode Register                                  */

  struct {
    __IOM uint32_t rxsym0l_bit0 : 4;          /*!< [3..0] If decode symbols match (RXSYM0H_BIT0, RXSYM0L_BIT0),
                                                   RX data will receive bit 0. When RXSYM0L_BIT0 is not zero,
                                                   this match is valid.                                                      */
    __IOM uint32_t rxsym0h_bit0 : 4;          /*!< [7..4] If decode symbols match (RXSYM0H_BIT0, RXSYM0L_BIT0),
                                                   RX data will receive bit 0. When RXSYM0L_BIT0 is not zero,
                                                   this match is valid.                                                      */
    __IOM uint32_t rxsym1l_bit0 : 4;          /*!< [11..8] If decode symbols match (RXSYM1H_BIT0, RXSYM1L_BIT0),
                                                   RX data will receive bit 0. When RXSYM1L_BIT0 is not zero,
                                                   this match is valid.                                                      */
    __IOM uint32_t rxsym1h_bit0 : 4;          /*!< [15..12] If decode symbols match (RXSYM1H_BIT0, RXSYM1L_BIT0),
                                                   RX data will receive bit 0. When RXSYM1L_BIT0 is not zero,
                                                   this match is valid.                                                      */
    __IOM uint32_t rxsym0l_bit1 : 4;          /*!< [19..16] If decode symbols match (RXSYM0H_BIT1, RXSYM0L_BIT1),
                                                   RX data will receive bit 1. When RXSYM0L_BIT1 is not zero,
                                                   this match is valid.                                                      */
    __IOM uint32_t rxsym0h_bit1 : 4;          /*!< [23..20] If decode symbols match (RXSYM0H_BIT1, RXSYM0L_BIT1),
                                                   RX data will receive bit 1. When RXSYM0L_BIT1 is not zero,
                                                   this match is valid.                                                      */
    __IOM uint32_t rxsym1l_bit1 : 4;          /*!< [27..24] If decode symbols match (RXSYM1H_BIT1, RXSYM1L_BIT1),
                                                   RX data will receive bit 1. When RXSYM1L_BIT1 is not zero,
                                                   this match is valid.                                                      */
    __IOM uint32_t rxsym1h_bit1 : 4;          /*!< [31..28] If decode symbols match (RXSYM1H_BIT1, RXSYM1L_BIT1),
                                                   RX data will receive bit 1. When RXSYM1L_BIT1 is not zero,
                                                   this match is valid.                                                      */
  } b;                                        /*!< bit fields for cir_rxsymdc */
} cir_rxsymdc_t, *pcir_rxsymdc_t;

/**
  \brief Union type to access cir_rxsymstrm (@ 0x00000064).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000064) RX Symbol Start Match Register                             */

  struct {
    __IOM uint32_t rxsym0strm_l : 4;          /*!< [3..0] If decode symbols match (RXSYM0STRM_H, RXSYM0STRM_L),
                                                   RX start decoding from this pattern. When (RXSYM0STRM_H,
                                                   RXSYM0STRM_L) is zero, this match is inactive.                            */
    __IOM uint32_t rxsym0strm_h : 4;          /*!< [7..4] If decode symbols match (RXSYM0STRM_H, RXSYM0STRM_L),
                                                   RX start decoding from this pattern. When (RXSYM0STRM_H,
                                                   RXSYM0STRM_L) is zero, this match is inactive.                            */
    __IOM uint32_t rxsym1strm_l : 4;          /*!< [11..8] If decode symbols match (RXSYM1STRM_H, RXSYM1STRM_L),
                                                   RX start decoding from this pattern. When (RXSYM1STRM_H,
                                                   RXSYM1STRM_L) is zero, this match is inactive.                            */
    __IOM uint32_t rxsym1strm_h : 4;          /*!< [15..12] If decode symbols match (RXSYM1STRM_H, RXSYM1STRM_L),
                                                   RX start decoding from this pattern. When (RXSYM1STRM_H,
                                                   RXSYM1STRM_L) is zero, this match is inactive.                            */
    __IOM uint32_t rxsym2strm_l : 4;          /*!< [19..16] If decode symbols match (RXSYM2STRM_H, RXSYM2STRM_L),
                                                   RX start decoding from this pattern. When (RXSYM2STRM_H,
                                                   RXSYM2STRM_L) is zero, this match is inactive.                            */
    __IOM uint32_t rxsym2strm_h : 4;          /*!< [23..20] If decode symbols match (RXSYM2STRM_H, RXSYM2STRM_L),
                                                   RX start decoding from this pattern. When (RXSYM2STRM_H,
                                                   RXSYM2STRM_L) is zero, this match is inactive.                            */
    __IOM uint32_t rxsym3strm_l : 4;          /*!< [27..24] If decode symbols match (RXSYM3STRM_H, RXSYM3STRM_L),
                                                   RX start decoding from this pattern. When (RXSYM3STRM_H,
                                                   RXSYM3STRM_L) is zero, this match is inactive.                            */
    __IOM uint32_t rxsym3strm_h : 4;          /*!< [31..28] If decode symbols match (RXSYM3STRM_H, RXSYM3STRM_L),
                                                   RX start decoding from this pattern. When (RXSYM3STRM_H,
                                                   RXSYM3STRM_L) is zero, this match is inactive.                            */
  } b;                                        /*!< bit fields for cir_rxsymstrm */
} cir_rxsymstrm_t, *pcir_rxsymstrm_t;

/**
  \brief Union type to access cir_rxdatacnt (@ 0x00000068).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000068) RX Data Count Register                                     */

  struct {
    __IM  uint32_t rxdatacnt  : 7;            /*!< [6..0] This register is used to count the decode number.                  */
  } b;                                        /*!< bit fields for cir_rxdatacnt */
} cir_rxdatacnt_t, *pcir_rxdatacnt_t;

/**
  \brief Union type to access cir_rxdcdata (@ 0x0000006C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000006C) RX Decode Data Register                                    */

  struct {
    __IOM uint32_t rxdcdata   : 32;           /*!< [31..0] When RX receives the end symbol or gets 32 bits, RXDCDATA
                                                   is updated. Receive the data from LSB.                                    */
  } b;                                        /*!< bit fields for cir_rxdcdata */
} cir_rxdcdata_t, *pcir_rxdcdata_t;

/**
  \brief Union type to access cir_rxdcdata_dp (@ 0x00000070).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000070) RX Decode Data Duplicate Register                          */

  struct {
    __IOM uint32_t rxdcdata_dp : 32;          /*!< [31..0] If RXDCDATA receives 32 bits, RXDCDATA_DP is loaded
                                                   with RXDCDATA. In the monitor mode, write the monitor data
                                                   in this register.                                                         */
  } b;                                        /*!< bit fields for cir_rxdcdata_dp */
} cir_rxdcdata_dp_t, *pcir_rxdcdata_dp_t;

/**
  \brief Union type to access cir_txsymcfg0 (@ 0x00000074).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000074) IR TX Symbol Configuration 0 Register                      */

  struct {
    __IOM uint32_t symtccc    : 16;           /*!< [15..0] The symbol type is Carrier symbol: defines the carrier
                                                   clock cycles of the symbol The symbol type is Space symbol:
                                                   defines the period of the symbol                                          */
    __IM  uint32_t            : 8;
    __IOM uint32_t txsymtyp   : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:Space
                                                   symbol with low level: TX output signal level keeps low
                                                   for a given period. 1:Space symbol with high level: TX
                                                   output signal level keeps high for a given period. 2:Carrier
                                                   symbol: carrier clock cycles continuously present on the
                                                   TX output signal.                                                         */
  } b;                                        /*!< bit fields for cir_txsymcfg0 */
} cir_txsymcfg0_t, *pcir_txsymcfg0_t;

/**
  \brief Union type to access cir_txsymcfg1 (@ 0x00000078).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000078) IR TX Symbol Configuration 1 Register                      */

  struct {
    __IOM uint32_t symtccc    : 16;           /*!< [15..0] The symbol type is Carrier symbol: defines the carrier
                                                   clock cycles of the symbol The symbol type is Space symbol:
                                                   defines the period of the symbol                                          */
    __IM  uint32_t            : 8;
    __IOM uint32_t txsymtyp   : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:Space
                                                   symbol with low level: TX output signal level keeps low
                                                   for a given period. 1:Space symbol with high level: TX
                                                   output signal level keeps high for a given period. 2:Carrier
                                                   symbol: carrier clock cycles continuously present on the
                                                   TX output signal.                                                         */
  } b;                                        /*!< bit fields for cir_txsymcfg1 */
} cir_txsymcfg1_t, *pcir_txsymcfg1_t;

/**
  \brief Union type to access cir_txsymcfg2 (@ 0x0000007C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000007C) IR TX Symbol Configuration 2 Register                      */

  struct {
    __IOM uint32_t symtccc    : 16;           /*!< [15..0] The symbol type is Carrier symbol: defines the carrier
                                                   clock cycles of the symbol The symbol type is Space symbol:
                                                   defines the period of the symbol                                          */
    __IM  uint32_t            : 8;
    __IOM uint32_t txsymtyp   : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:Space
                                                   symbol with low level: TX output signal level keeps low
                                                   for a given period. 1:Space symbol with high level: TX
                                                   output signal level keeps high for a given period. 2:Carrier
                                                   symbol: carrier clock cycles continuously present on the
                                                   TX output signal.                                                         */
  } b;                                        /*!< bit fields for cir_txsymcfg2 */
} cir_txsymcfg2_t, *pcir_txsymcfg2_t;

/**
  \brief Union type to access cir_txsymcfg3 (@ 0x00000080).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000080) IR TX Symbol Configuration 3 Register                      */

  struct {
    __IOM uint32_t symtccc    : 16;           /*!< [15..0] The symbol type is Carrier symbol: defines the carrier
                                                   clock cycles of the symbol The symbol type is Space symbol:
                                                   defines the period of the symbol                                          */
    __IM  uint32_t            : 8;
    __IOM uint32_t txsymtyp   : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:Space
                                                   symbol with low level: TX output signal level keeps low
                                                   for a given period. 1:Space symbol with high level: TX
                                                   output signal level keeps high for a given period. 2:Carrier
                                                   symbol: carrier clock cycles continuously present on the
                                                   TX output signal.                                                         */
  } b;                                        /*!< bit fields for cir_txsymcfg3 */
} cir_txsymcfg3_t, *pcir_txsymcfg3_t;

/**
  \brief Union type to access cir_txsymcfg4 (@ 0x00000084).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000084) IR TX Symbol Configuration 4 Register                      */

  struct {
    __IOM uint32_t symtccc    : 16;           /*!< [15..0] The symbol type is Carrier symbol: defines the carrier
                                                   clock cycles of the symbol The symbol type is Space symbol:
                                                   defines the period of the symbol                                          */
    __IM  uint32_t            : 8;
    __IOM uint32_t txsymtyp   : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:Space
                                                   symbol with low level: TX output signal level keeps low
                                                   for a given period. 1:Space symbol with high level: TX
                                                   output signal level keeps high for a given period. 2:Carrier
                                                   symbol: carrier clock cycles continuously present on the
                                                   TX output signal.                                                         */
  } b;                                        /*!< bit fields for cir_txsymcfg4 */
} cir_txsymcfg4_t, *pcir_txsymcfg4_t;

/**
  \brief Union type to access cir_txsymcfg5 (@ 0x00000088).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000088) IR TX Symbol Configuration 5 Register                      */

  struct {
    __IOM uint32_t symtccc    : 16;           /*!< [15..0] The symbol type is Carrier symbol: defines the carrier
                                                   clock cycles of the symbol The symbol type is Space symbol:
                                                   defines the period of the symbol                                          */
    __IM  uint32_t            : 8;
    __IOM uint32_t txsymtyp   : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:Space
                                                   symbol with low level: TX output signal level keeps low
                                                   for a given period. 1:Space symbol with high level: TX
                                                   output signal level keeps high for a given period. 2:Carrier
                                                   symbol: carrier clock cycles continuously present on the
                                                   TX output signal.                                                         */
  } b;                                        /*!< bit fields for cir_txsymcfg5 */
} cir_txsymcfg5_t, *pcir_txsymcfg5_t;

/**
  \brief Union type to access cir_txsymcfg6 (@ 0x0000008C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000008C) IR TX Symbol Configuration 6 Register                      */

  struct {
    __IOM uint32_t symtccc    : 16;           /*!< [15..0] The symbol type is Carrier symbol: defines the carrier
                                                   clock cycles of the symbol The symbol type is Space symbol:
                                                   defines the period of the symbol                                          */
    __IM  uint32_t            : 8;
    __IOM uint32_t txsymtyp   : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:Space
                                                   symbol with low level: TX output signal level keeps low
                                                   for a given period. 1:Space symbol with high level: TX
                                                   output signal level keeps high for a given period. 2:Carrier
                                                   symbol: carrier clock cycles continuously present on the
                                                   TX output signal.                                                         */
  } b;                                        /*!< bit fields for cir_txsymcfg6 */
} cir_txsymcfg6_t, *pcir_txsymcfg6_t;

/**
  \brief Union type to access cir_txsymcfg7 (@ 0x00000090).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000090) IR TX Symbol Configuration 7 Register                      */

  struct {
    __IOM uint32_t symtccc    : 16;           /*!< [15..0] The symbol type is Carrier symbol: defines the carrier
                                                   clock cycles of the symbol The symbol type is Space symbol:
                                                   defines the period of the symbol                                          */
    __IM  uint32_t            : 8;
    __IOM uint32_t txsymtyp   : 2;            /*!< [25..24] This field is used to configure the symbol type. 0:Space
                                                   symbol with low level: TX output signal level keeps low
                                                   for a given period. 1:Space symbol with high level: TX
                                                   output signal level keeps high for a given period. 2:Carrier
                                                   symbol: carrier clock cycles continuously present on the
                                                   TX output signal.                                                         */
  } b;                                        /*!< bit fields for cir_txsymcfg7 */
} cir_txsymcfg7_t, *pcir_txsymcfg7_t;

/**
  \brief Union type to access cir_ier (@ 0x00000094).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000094) Interrupt Enable Register                                  */

  struct {
    __IOM uint32_t ie_rxrdy   : 1;            /*!< [0..0] Enable the interrupt of data ready in the RX FIFO. 1:
                                                   Enable 0: Disable                                                         */
    __IOM uint32_t ie_rxhf    : 1;            /*!< [1..1] Enable the interrupt of the RX FIFO is half full. 1:
                                                   Enable 0: Disable                                                         */
    __IOM uint32_t ie_rxaf    : 1;            /*!< [2..2] Enable the interrupt of the RX FIFO is full. 1: Enable
                                                   0: Disable                                                                */
    __IOM uint32_t ie_rxftr   : 1;            /*!< [3..3] Enable the interrupt of the RX filter pattern matched.
                                                   1: Enable 0: Disable                                                      */
    __IOM uint32_t ie_txemp   : 1;            /*!< [4..4] Enable the interrupt of the TX FIFO is empty. 1: Enable
                                                   0: Disable                                                                */
    __IOM uint32_t ie_tx2emp  : 1;            /*!< [5..5] When the TX FIFO is at least 2 bytes of space, this interrupt
                                                   will be asserted. 1: Enable 0: Disable                                    */
    __IOM uint32_t ie_txhe    : 1;            /*!< [6..6] Enable the interrupt of the TX FIFO is half empty. 1:
                                                   Enable 0: Disable                                                         */
    __IOM uint32_t ie_rxld_end : 1;           /*!< [7..7] RXDCDATA is loaded because RX receives the end symbol.
                                                   Enable this interrupt. 1: Enable 0: Disable                               */
    __IOM uint32_t ie_rxld_full : 1;          /*!< [8..8] RXDCDATA_DP is loaded because RXDCDATA gets 32 bits.
                                                   Enable this interrupt. 1: Enable 0: Disable                               */
    __IOM uint32_t ie_rxsym0strm : 1;         /*!< [9..9] When decode symbols match (RXSYM0STRM_H, RXSYM0STRM_L),
                                                   generate an interrupt. 1: Enable 0: Disable                               */
    __IOM uint32_t ie_rxsym1strm : 1;         /*!< [10..10] When decode symbols match (RXSYM1STRM_H, RXSYM1STRM_L),
                                                   generate an interrupt. 1: Enable 0: Disable                               */
    __IOM uint32_t ie_monitor : 1;            /*!< [11..11] When the monitor value of RXDCDATA_DP is equal to the
                                                   monitor value of RXDCDATA in the RX monitor mode, it can
                                                   generate an interrupt. 1: Enable 0: Disable                               */
  } b;                                        /*!< bit fields for cir_ier */
} cir_ier_t, *pcir_ier_t;

/**
  \brief Union type to access cir_imr (@ 0x00000098).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000098) Interrupt Mask Register                                    */

  struct {
    __IOM uint32_t im_rxrdy   : 1;            /*!< [0..0] 1: Mask the interrupt 0: Un-Mask                                   */
    __IOM uint32_t im_rxhf    : 1;            /*!< [1..1] 1: Mask the interrupt 0: Un-Mask                                   */
    __IOM uint32_t im_rxaf    : 1;            /*!< [2..2] 1: Mask the interrupt 0: Un-Mask                                   */
    __IOM uint32_t im_rxftr   : 1;            /*!< [3..3] 1: Mask the interrupt 0: Un-Mask                                   */
    __IOM uint32_t im_txemp   : 1;            /*!< [4..4] 1: Mask the interrupt 0: Un-Mask                                   */
    __IOM uint32_t im_tx2emp  : 1;            /*!< [5..5] 1: Mask the interrupt 0: Un-Mask                                   */
    __IOM uint32_t im_txhe    : 1;            /*!< [6..6] 1: Mask the interrupt 0: Un-Mask                                   */
    __IOM uint32_t im_rxld_end : 1;           /*!< [7..7] 1: Mask the interrupt 0: Un-Mask                                   */
    __IOM uint32_t im_rxld_full : 1;          /*!< [8..8] 1: Mask the interrupt 0: Un-Mask                                   */
    __IOM uint32_t im_rxsym0strm : 1;         /*!< [9..9] 1: Mask the interrupt 0: Un-Mask                                   */
    __IOM uint32_t im_rxsym1strm : 1;         /*!< [10..10] 1: Mask the interrupt 0: Un-Mask                                 */
    __IOM uint32_t im_monitor : 1;            /*!< [11..11] 1: Mask the interrupt 0: Un-Mask                                 */
  } b;                                        /*!< bit fields for cir_imr */
} cir_imr_t, *pcir_imr_t;

/**
  \brief Union type to access cir_isr (@ 0x0000009C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000009C) Interrupt Status Register                                  */

  struct {
    __IOM uint32_t is_rxrdy   : 1;            /*!< [0..0] 1: interrupt is pending 0: no interrupt Write 1 to this
                                                   bit will clear this interrupt status.                                     */
    __IOM uint32_t is_rxhf    : 1;            /*!< [1..1] 1: interrupt is pending 0: no interrupt Write 1 to this
                                                   bit will clear this interrupt status.                                     */
    __IOM uint32_t is_rxaf    : 1;            /*!< [2..2] 1: interrupt is pending 0: no interrupt Write 1 to this
                                                   bit will clear this interrupt status.                                     */
    __IOM uint32_t is_rxftr   : 1;            /*!< [3..3] 1: interrupt is pending 0: no interrupt Write 1 to this
                                                   bit will clear this interrupt status.                                     */
    __IOM uint32_t is_txemp   : 1;            /*!< [4..4] 1: interrupt is pending 0: no interrupt Write 1 to this
                                                   bit will clear this interrupt status.                                     */
    __IOM uint32_t is_tx2emp  : 1;            /*!< [5..5] 1: interrupt is pending 0: no interrupt Write 1 to this
                                                   bit will clear this interrupt status.                                     */
    __IOM uint32_t is_txhe    : 1;            /*!< [6..6] 1: interrupt is pending 0: no interrupt Write 1 to this
                                                   bit will clear this interrupt status.                                     */
    __IOM uint32_t is_rxld_end : 1;           /*!< [7..7] 1: interrupt is pending 0: no interrupt Write 1 to this
                                                   bit will clear this interrupt status.                                     */
    __IOM uint32_t is_rxld_full : 1;          /*!< [8..8] 1: interrupt is pending 0: no interrupt Write 1 to this
                                                   bit will clear this interrupt status.                                     */
    __IOM uint32_t is_rxsym0strm : 1;         /*!< [9..9] 1: interrupt is pending 0: no interrupt Write 1 to this
                                                   bit will clear this interrupt status.                                     */
    __IOM uint32_t is_rxsym1strm : 1;         /*!< [10..10] 1: interrupt is pending 0: no interrupt Write 1 to
                                                   this bit will clear this interrupt status.                                */
    __IOM uint32_t is_monitor : 1;            /*!< [11..11] 1: interrupt is pending 0: no interrupt Write 1 to
                                                   this bit will clear this interrupt status.                                */
  } b;                                        /*!< bit fields for cir_isr */
} cir_isr_t, *pcir_isr_t;

/**
  \brief Union type to access cir_rfc (@ 0x000000A0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A0) IR RX Filter Control Register                              */

  struct {
    __IOM uint32_t rfsn       : 4;            /*!< [3..0] This field define the number of patterns should be used
                                                   to check the IR RX received symbol codes.                                 */
    __IM  uint32_t            : 4;
    __IOM uint32_t rfto       : 16;           /*!< [23..8] This field defines a timeout value for the waiting of
                                                   a new RX symbol code to be shifted into the IR RX filter.                 */
    __IM  uint32_t            : 5;
    __IOM uint32_t rftoen     : 1;            /*!< [29..29] This bit is used to control the IR RX filter timeout
                                                   function enabling. 0: no timeout (timeout function is disabled).
                                                   1: timeout function is enabled.                                           */
    __IOM uint32_t rfrst      : 1;            /*!< [30..30] This bit is used to reset the IR RX filter. 0: reset
                                                   signal is released, normal works 1: reset the RX filter                   */
    __IOM uint32_t rfen       : 1;            /*!< [31..31] This bit is used to control the IR RX filter function
                                                   enabling. 0: IR RX filter function is disabled 1: IR RX
                                                   filter function is enabled                                                */
  } b;                                        /*!< bit fields for cir_rfc */
} cir_rfc_t, *pcir_rfc_t;

/**
  \brief Union type to access cir_rfpat0 (@ 0x000000A4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A4) IR RX Filter Pattern 0 Register                            */

  struct {
    __IOM uint32_t rfpt0      : 4;            /*!< [3..0] The pattern to compare with the IR RX symbol code                  */
    __IOM uint32_t rfpt1      : 4;            /*!< [7..4] The pattern to compare with the IR RX symbol code                  */
    __IOM uint32_t rfpt2      : 4;            /*!< [11..8] The pattern to compare with the IR RX symbol code                 */
    __IOM uint32_t rfpt3      : 4;            /*!< [15..12] The pattern to compare with the IR RX symbol code                */
    __IOM uint32_t rfpt4      : 4;            /*!< [19..16] The pattern to compare with the IR RX symbol code                */
    __IOM uint32_t rfpt5      : 4;            /*!< [23..20] The pattern to compare with the IR RX symbol code                */
    __IOM uint32_t rfpt6      : 4;            /*!< [27..24] The pattern to compare with the IR RX symbol code                */
    __IOM uint32_t rfpt7      : 4;            /*!< [31..28] The pattern to compare with the IR RX symbol code                */
  } b;                                        /*!< bit fields for cir_rfpat0 */
} cir_rfpat0_t, *pcir_rfpat0_t;

/**
  \brief Union type to access cir_rfpat1 (@ 0x000000A8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A8) IR RX Filter Pattern 0 Register                            */

  struct {
    __IOM uint32_t rfpt8      : 4;            /*!< [3..0] The pattern to compare with the IR RX symbol code                  */
    __IOM uint32_t rfpt9      : 4;            /*!< [7..4] The pattern to compare with the IR RX symbol code                  */
    __IOM uint32_t rfpt10     : 4;            /*!< [11..8] The pattern to compare with the IR RX symbol code                 */
    __IOM uint32_t rfpt11     : 4;            /*!< [15..12] The pattern to compare with the IR RX symbol code                */
    __IOM uint32_t rfpt12     : 4;            /*!< [19..16] The pattern to compare with the IR RX symbol code                */
    __IOM uint32_t rfpt13     : 4;            /*!< [23..20] The pattern to compare with the IR RX symbol code                */
    __IOM uint32_t rfpt14     : 4;            /*!< [27..24] The pattern to compare with the IR RX symbol code                */
    __IOM uint32_t rfpt15     : 4;            /*!< [31..28] The pattern to compare with the IR RX symbol code                */
  } b;                                        /*!< bit fields for cir_rfpat1 */
} cir_rfpat1_t, *pcir_rfpat1_t;

/** @} */ /* End of group ls_hal_cir_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_CIR_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BLP_CIR_TYPE_H_

