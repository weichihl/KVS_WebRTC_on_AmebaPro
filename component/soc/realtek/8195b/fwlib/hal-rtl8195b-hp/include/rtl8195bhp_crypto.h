/**************************************************************************//**
 * @file     rtl8195bhp_crypto.h
 * @brief    This file defines crypto type ,device address and declare device module macro variables.
 * @version  1.0
 * @date     11. December 2017
 * @note     Generated by SVDConv V3.3.9 on Thursday, 21.09.2017 17:03:48
 *           from File 'rtl8195bhp_crypto.svd',
 *           last modified on Thursday, 21.09.2017 09:03:15
 *
 *******************************************************************************
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
/** @addtogroup hs_hal_crypto CRYPTO
 *  @ingroup 8195bh_hal
 *  @{
 *  @brief The Crypto HAL. This crypto implements functions for cryptographic,such as
 *         calculating CRC value, authentication, encryption and decryption.
 */

#include "basic_types.h"

#ifndef RTL8195BHP_CRYPTO_H
#define RTL8195BHP_CRYPTO_H

#ifdef __cplusplus
extern "C" {
#endif

/* ================================================================================================================= */
/* ================                            Device Specific Peripheral Section                             ====== */
/* ================================================================================================================= */

/// @cond DOXYGEN_CRYPTO_REG_TYPE

/** @addtogroup device_crypto_reg Crypto Device Type
 *  @ingroup hs_hal_crypto
 *  @{
 */




/* ================================================================================================================= */
/* ================                                          CRYPTO                                           ====== */
/* ================================================================================================================= */


/**
 * @brief Crypto in Secure (CRYPTO)
 */
typedef struct {                                /*!< (@ 0x50070000) CRYPTO Structure */

  union {
    __IOM uint32_t srcdesc_status_reg;          /*!< (@ 0x00000000) Source Descriptor FIFO status Register */

    struct {
      __IM  uint32_t fifo_empty_cnt : 8;        /*!< [7..0] Source Descriptor FIFO empty counter                    */
      __IM  uint32_t swptr      : 8;            /*!< [15..8] Source Descriptor FIFO write pointer                   */
      __IM  uint32_t srptr      : 8;            /*!< [23..16] Source Descriptor FIFO read pointer                   */
      __IOM uint32_t src_fail   : 1;            /*!< [24..24] Source Descriptor fail interrupt                      */

      __IM  uint32_t src_fail_status : 2;       /*!< [26..25] Source Descriptor fail status                         */
      __IOM uint32_t src_fail_m : 1;            /*!< [27..27] Source Descriptor fail interrupt mask                 */

      __IM  uint32_t            : 2;
      __IOM uint32_t pk_up      : 1;            /*!< [30..30] packet base update wptr to engine                     */
      __IOM uint32_t src_rst    : 1;            /*!< [31..31] Source Descriptor reset(only for pk_up=1'b1           */
    } srcdesc_status_reg_b;
  } ;

  union {
    __IOM uint32_t sdfw_reg;                    /*!< (@ 0x00000004) IPSec Source Descriptor first word              */

    struct {
      __IOM uint32_t sdfw       : 32;           /*!< [31..0] IPSec Source Descriptor first word                     */
    } sdfw_reg_b;
  } ;

  union {
    __IOM uint32_t sdsw_reg;                    /*!< (@ 0x00000008) IPSec Source Descriptor second word             */

    struct {
      __IOM uint32_t sdsw       : 32;           /*!< [31..0] IPSec Source Descriptor second word                    */
    } sdsw_reg_b;
  } ;
  __IM  uint32_t  RESERVED;

  union {
    __IOM uint32_t ipscsr_reset_isr_conf_reg;   /*!< (@ 0x00000010) IPSec Command/Status Register,
                                                 *                  for reset / isr poll status
                                                 */

    struct {
      __OM  uint32_t soft_rst   : 1;            /*!< [0..0] Software Reset write 1 to reset                         */
      __IM  uint32_t            : 2;
      __IM  uint32_t dma_busy   : 1;            /*!< [3..3] Ipsec dma busy                                          */
      __IOM uint32_t cmd_ok     : 1;            /*!< [4..4] Command OK interrupt                                    */

      __IM  uint32_t            : 2;
      __IOM uint32_t intr_mode  : 1;            /*!< [7..7] Select ok interrupt mode                                */
      __IM  uint32_t ok_intr_cnt : 8;           /*!< [15..8] OK interrupt counter                                   */
      __IOM uint32_t clear_ok_intr_num : 8;     /*!< [23..16] Clear OK interrupt number                             */

      __IM  uint32_t            : 7;
      __OM  uint32_t ipsec_rst  : 1;            /*!< [31..31] Ipsec engine Reset Write 1 to reset the crypto engine
                                                 *    and DMA engine
                                                 */
    } ipscsr_reset_isr_conf_reg_b;
  } ;

  union {
    __IOM uint32_t ipscsr_int_mask_reg;         /*!< (@ 0x00000014) IPSec Command/Status Register, for interrupt mask */

    struct {
      __IOM uint32_t cmd_ok_m   : 1;            /*!< [0..0] Command OK interrupt Mask 1: Mask Enable 0: Mask Disable */

      __IM  uint32_t            : 2;
      __IOM uint32_t src_err0_m : 1;            /*!< [3..3] Source Descriptor Error 0 Interrupt Mask 1: Mask Enable
                                                 *   0: Mask Disable
                                                 */
      __IOM uint32_t src_err1_m : 1;            /*!< [4..4] Source Descriptor Error 1 Interrupt Mask 1: Mask Enable
                                                 *   0: Mask Disable
                                                 */
      __IOM uint32_t src_err2_m : 1;            /*!< [5..5] Source Descriptor Error 2 Interrupt Mask 1: Mask Enable
                                                 *   0: Mask Disable
                                                 */
      __IOM uint32_t src_err3_m : 1;            /*!< [6..6] Source Descriptor Error 3 Interrupt Mask 1: Mask Enable
                                                 *   0: Mask Disable
                                                 */
      __IOM uint32_t src_err4_m : 1;            /*!< [7..7] Source Descriptor Error 4 Interrupt Mask 1: Mask Enable
                                                 *   0: Mask Disable
                                                 */
      __IOM uint32_t src_err5_m : 1;            /*!< [8..8] Source Descriptor Error 5 Interrupt Mask 1: Mask Enable
                                                 *   0: Mask Disable
                                                 */
      __IOM uint32_t src_err6_m : 1;            /*!< [9..9] Source Descriptor Error 6 Interrupt Mask 1: Mask Enable
                                                 *   0: Mask Disable
                                                 */
      __IOM uint32_t src_err7_m : 1;            /*!< [10..10] Source Descriptor Error 7 Interrupt Mask 1: Mask Enable
                                                 *   0: Mask Disable
                                                 */
      __IOM uint32_t src_err8_m : 1;            /*!< [11..11] Source Descriptor Error 8 Interrupt Mask 1: Mask Enable
                                                 *   0: Mask Disable
                                                 */
      __IOM uint32_t src_err9_m : 1;            /*!< [12..12] Source Descriptor Error 9 Interrupt Mask 1: Mask Enable
                                                 *   0: Mask Disable
                                                 */
      __IOM uint32_t dst_err1_m : 1;            /*!< [13..13] Destination Descriptor Error 1 Interrupt Mask 1: Mask
                                                 *   Enable 0: Mask Disable
                                                 */
      __IOM uint32_t dst_err2_m : 1;            /*!< [14..14] Destination Descriptor Error 2 Interrupt Mask 1: Mask
                                                 *   Enable 0: Mask Disable
                                                 */
      __IOM uint32_t dst_err3_m : 1;            /*!< [15..15] Destination Descriptor Error 3 Interrupt Mask 1: Mask
                                                 *   Enable 0: Mask Disable
                                                 */
      __IOM uint32_t dst_err4_m : 1;            /*!< [16..16] Destination Descriptor Error 4 Interrupt Mask 1: Mask
                                                 *   Enable 0: Mask Disable
                                                 */
      __IOM uint32_t dst_err5_m : 1;            /*!< [17..17] Destination Descriptor Error 5 Interrupt Mask 1: Mask
                                                 *   Enable 0: Mask Disable
                                                 */
      __IOM uint32_t dst_err6_m : 1;            /*!< [18..18] Destination Descriptor Error 6 Interrupt Mask 1: Mask
                                                 *   Enable 0: Mask Disable
                                                 */
    } ipscsr_int_mask_reg_b;
  } ;

  union {
    __IOM uint32_t ipscsr_debug_reg;            /*!< (@ 0x00000018) IPSec Command/Status Register, for debug        */

    struct {
      __IOM uint32_t dma_wait_cycle : 16;       /*!< [15..0] Software Reset                                         */
      __IOM uint32_t arbiter_mode : 1;          /*!< [16..16] dma arbiter mode: 1'b0 : round-robin 1'b1 : detect
                                                 *   fifo wasted level
                                                 */
      __IM  uint32_t            : 3;
      __IOM uint32_t debug_port_sel : 4;        /*!< [23..20] Debug port selection: 4'd0 : engine_dbg,
                                                 *   4'd1 : dma_lexra_dbg, 4'd2 : dma_rx_dbg, 4'd3 : dma_tx_dbg
                                                 */
      __IOM uint32_t engine_clk_en : 1;         /*!< [24..24] Ipsec Engine clock enable                             */

      __IM  uint32_t            : 6;
      __IOM uint32_t debug_wb   : 1;            /*!< [31..31] Debug : write back mode                               */
    } ipscsr_debug_reg_b;
  } ;

  union {
    __IOM uint16_t ipscsr_err_stats_reg;        /*!< (@ 0x0000001C) IPSec Command/Status Register, for error status */

    struct {
      __IOM uint16_t src_err0   : 1;            /*!< [0..0] Source Descriptor Error 0 interrupt First segment descriptor
                                                 *   is not set (FS=0), when descriptor is pointing to the first
                                                 *   segment of the packet. (or) First segment descriptor is
                                                 *   set (FS=1), when descriptor is polling to the first segment
                                                 *   of the packet. Write 1 to clear
                                                 */
      __IOM uint16_t src_err1   : 1;            /*!< [1..1] Source Descriptor Error 1 interrupt Last segment descriptor
                                                 *   is not set (LS=1), when descriptor is pointing to the first
                                                 *   segment of the packet. Write 1 to clear
                                                 */
      __IOM uint16_t src_err2   : 1;            /*!< [2..2] Source Descriptor Error 2 interrupt 1. Source Descriptor
                                                 *   Starting Address error(SDSA[1:0]!=2'd0) 2. memory protection
                                                 *   event Write 1 to clear
                                                 */
      __IOM uint16_t src_err3   : 1;            /*!< [3..3] Source Descriptor Error 3 interrupt Length error :
                                                 *   1. first descriptor & (CL!=3)
                                                 *   2. ((CL=0)&(kl==0)&(il==0)&(pl==0)&(shil==0)
                                                 *   Write 1 to clear
                                                 */
      __IOM uint16_t src_err4   : 1;            /*!< [4..4] Source Descriptor Error 4 interrupt Source Data Buffer
                                                 *   Pointer error(SDDB[1:0]!=2'd0) Write 1 to clear
                                                 */
      __IOM uint16_t src_err5   : 1;            /*!< [5..5] Source Descriptor Error 5 interrupt Data length = a2eo(epl)
                                                 *   + enl + apl = 0 Write 1 to clear
                                                 */
      __IOM uint16_t src_err6   : 1;            /*!< [6..6] Source Descriptor Error 6 interrupt Sum(a2eo)!=header
                                                 *   total length Write 1 to clear
                                                 */
      __IOM uint16_t src_err7   : 1;            /*!< [7..7] Source Descriptor Error 7 interrupt Sum(enl)!=encryption
                                                 *   total length Write 1 to clear
                                                 */
      __IOM uint16_t src_err8   : 1;            /*!< [8..8] Source Descriptor Error 8 interrupt Sum(apl)!=hash padding
                                                 *   total length Write 1 to clear
                                                 */
      __IOM uint16_t src_err9   : 1;            /*!< [9..9] Source Descriptor Error 9 interrupt Sum(enl)!=encryption
                                                 *   padding total length Write 1 to clear
                                                 */
      __IOM uint16_t des_err1   : 1;            /*!< [10..10] Destination Descriptor Error 1 interrupt 1. Destination
                                                 *   Descriptor Starting Address error(DDSA[1:0]!=2'd0) 2. memory
                                                 *   protection error Write 1 to clear
                                                 */
      __IOM uint16_t des_err2   : 1;            /*!< [11..11] Destination Descriptor Error 2 interrupt (ENC=1'b1),
                                                 *   when only active hash engine Write 1 to clear
                                                 */
      __IOM uint16_t des_err3   : 1;            /*!< [12..12] Destination Descriptor Error 2 interrupt (ENC=1'b0),
                                                 *   when only active encryption engine Write 1 to clear
                                                 */
      __IOM uint16_t des_err4   : 1;            /*!< [13..13] Destination Descriptor Error 4 interrupt 1. (enl_sum
                                                 *   > enc_len) 2. (enl==0) & (apl==0) Write 1 to clear
                                                 */
      __IOM uint16_t des_err5   : 1;            /*!< [14..14] Destination Descriptor Error 5 interrupt 1. md5: adl>16
                                                 *   2. sha1: adl>20 3. sha224: adl>28 4. sha256: adl>32 5.
                                                 *   sha384: adl>48 6. sha512: adl>64 Write 1 to clear
                                                 */
      __IOM uint16_t des_err6   : 1;            /*!< [15..15] Destination Descriptor Error 6 interrupt
                                                 *   when set sequential hash 1. md5: adl!=16 2. sha1: adl!=20
                                                 *   3. sha224/256: adl!=32 4. sha384/512: adl!=64 Write 1 to clear
                                                 */
    } ipscsr_err_stats_reg_b;
  } ;
  __IM  uint16_t  RESERVED1;
  __IM  uint32_t  RESERVED2[4];

  union {
    __IOM uint32_t ipscsr_swap_burst_reg;       /*!< (@ 0x00000030) IPSec Command/Status Register, for swap / burst
                                                 *                  numbers
                                                 */

    struct {
      __IOM uint32_t set_swap   : 1;            /*!< [0..0] Byte swap for command setting data 1: Enable 0: Disable */
      __IOM uint32_t key_iv_swap : 1;           /*!< [1..1] Byte swap for key and iv 1: Enable 0: Disable           */
      __IOM uint32_t key_pad_swap : 1;          /*!< [2..2] Byte swap for hmac key 1: Enable 0: Disable             */
      __IOM uint32_t hash_inital_value_swap : 1;/*!< [3..3] Byte swap for sequential hash initial value 1: Enable
                                                 *   0: Disable
                                                 */
      __IOM uint32_t dma_in_little_endian : 1;  /*!< [4..4] Input data is little endian 1: little endian 0: big endian
                                                 */
      __IM  uint32_t            : 3;
      __IOM uint32_t tx_byte_swap : 1;          /*!< [8..8] Byte swap for dma_tx engine input data 1: Enable 0: Disable
                                                 */
      __IOM uint32_t data_out_little_endian : 1;/*!< [9..9] Output data is little endian 1: little endian 0: big
                                                 *   endian
                                                 */
      __IOM uint32_t mac_out_little_endian : 1; /*!< [10..10] Output mac is little endian 1: little endian 0: big
                                                 *   endian
                                                 */
      __IOM uint32_t rx_wd_swap : 1;            /*!< [11..11] Word swap for dma_rx engine input data 1: Enable 0:
                                                 *   Disable
                                                 */
      __IOM uint32_t tx_wd_swap : 1;            /*!< [12..12] Word swap for dma_tx engine input data 1: Enable 0:
                                                 *   Disable
                                                 */
      __IM  uint32_t            : 3;
      __IOM uint32_t dma_burst_length : 6;      /*!< [21..16] dma burst length Max : 32 Min: 1                      */
    } ipscsr_swap_burst_reg_b;
  } ;
  __IM  uint32_t  RESERVED3[51];

  union {
    __OM  uint32_t crc_rst_reg;                 /*!< (@ 0x00000100) crc reset                                       */

    struct {
      __OM  uint32_t rst        : 1;            /*!< [0..0] CRC reset                                               */
    } crc_rst_reg_b;
  } ;

  union {
    __IOM uint32_t crc_op_reg;                  /*!< (@ 0x00000104) crc operation                                   */

    struct {
      __IOM uint32_t crc_iswap  : 3;            /*!< [2..0] swap input data                                         */
      __IOM uint32_t crc_oswap  : 1;            /*!< [3..3] swap output data                                        */
      __IOM uint32_t crc_sel    : 3;            /*!< [6..4] crc sel                                                 */
      __IOM uint32_t crc_dma    : 1;            /*!< [7..7] DMA mode                                                */
      __IOM uint32_t crc_be     : 2;            /*!< [9..8] big endian                                              */

      __IM  uint32_t            : 2;
      __IOM uint32_t crc_last   : 1;            /*!< [12..12] crc last                                              */

      __IM  uint32_t            : 3;
      __IOM uint32_t crc_length : 16;           /*!< [31..16] length                                                */
    } crc_op_reg_b;
  } ;

  union {
    __IOM uint32_t crc_poly_reg;                /*!< (@ 0x00000108) CRC polynomia register                          */

    struct {
      __IOM uint32_t crc_poly   : 32;           /*!< [31..0] crc polynomial coefficients                            */
    } crc_poly_reg_b;
  } ;

  union {
    __IOM uint32_t crc_iv_reg;                  /*!< (@ 0x0000010C) CRC initial value register                      */

    struct {
      __IOM uint32_t crc_init   : 32;           /*!< [31..0] crc init value                                         */
    } crc_iv_reg_b;
  } ;

  union {
    __IOM uint32_t crc_oxor_reg;                /*!< (@ 0x00000110) CRC initial value register                      */

    struct {
      __IOM uint32_t crc_oxor   : 32;           /*!< [31..0] if output xor mode                                     */
    } crc_oxor_reg_b;
  } ;

  union {
    __IOM uint32_t crc_data_reg;                /*!< (@ 0x00000114) CRC data register                               */

    struct {
      __IOM uint32_t crc_data   : 32;           /*!< [31..0] din - Command mode : DMA==1'b0 SDBP - Source Data Buffer
                                                 *   Pointer : DMA==1'b1
                                                 */
    } crc_data_reg_b;
  } ;

  union {
    __IOM uint32_t crc_stat_reg;                /*!< (@ 0x00000118) CRC status register                             */

    struct {
      __IM  uint32_t busy       : 1;            /*!< [0..0] still busy in previous execution                        */
      __IOM  uint32_t crc_ok     : 1;           /*!< [1..1] finish execution                                        */
      __IOM uint32_t crc_intr_mask : 1;         /*!< [2..2] interrupt mask                                          */
      __OM  uint32_t crc_little_endian : 1;     /*!< [3..3] little endian                                           */
    } crc_stat_reg_b;
  } ;

  union {
    __IM  uint32_t crc_result_reg;              /*!< (@ 0x0000011C) CRC result register                             */

    struct {
      __IM  uint32_t crc_out    : 32;           /*!< [31..0] output result                                          */
    } crc_result_reg_b;
  } ;

  union {
    __IM  uint32_t crc_count_reg;               /*!< (@ 0x00000120) CRC count register                              */

    struct {
      __IM  uint32_t crc_cnt    : 16;           /*!< [15..0] count number in bytes                                  */
    } crc_count_reg_b;
  } ;
  __IM  uint32_t  RESERVED4[951];

  union {
    __IOM uint32_t dstdesc_status_reg;          /*!< (@ 0x00001000) destination descriptor status                   */

    struct {
      __IM  uint32_t fifo_empty_cnt : 8;        /*!< [7..0] Destination Descriptor FIFO empty counter               */
      __IM  uint32_t dwptr      : 8;            /*!< [15..8] Destination Descriptor FIFO write pointer              */
      __IM  uint32_t drptr      : 8;            /*!< [23..16] Destination Descriptor FIFO read pointer              */
      __IOM uint32_t dst_fail   : 1;            /*!< [24..24] Destination Descriptor fail interrupt                 */
      __IM  uint32_t dst_fail_status : 2;       /*!< [26..25] Destination Descriptor fail status                    */
      __IOM uint32_t dst_fail_m : 1;            /*!< [27..27] Destination Descriptor fail interrupt mask            */

      __IM  uint32_t            : 3;
      __IOM uint32_t dst_rst    : 1;            /*!< [31..31] Destination Descriptor reset                          */
    } dstdesc_status_reg_b;
  } ;

  union {
    __IOM uint32_t ddfw_reg;                    /*!< (@ 0x00001004) destination descriptor first word               */

    struct {
      __IOM uint32_t ddfw       : 32;           /*!< [31..0] IPSec Destination Descriptor first word                */
    } ddfw_reg_b;
  } ;

  union {
    __IOM uint32_t ddsw_reg;                    /*!< (@ 0x00001008) destination descriptor second word              */

    struct {
      __IOM uint32_t ddsw       : 32;           /*!< [31..0] IPSec Destination Descriptor second word               */
    } ddsw_reg_b;
  } ;

  union {
    __IOM uint32_t desc_pkt_conf_reg;           /*!< (@ 0x0000100C) descriptor packet setting                       */

    struct {
      __IOM uint32_t dbg_sptr   : 8;            /*!< [7..0] Source Descriptor FIFO empty counter                    */
      __IOM uint32_t dbg_dptr   : 8;            /*!< [15..8] Destination Descriptor FIFO write pointer              */
      __IM  uint32_t pk_arbiter : 2;            /*!< [17..16] Packet arbiter 2'd0 : bus1, 2'd1 : bus2, 2'd2 : bus3  */

      __IM  uint32_t            : 6;
      __IOM uint32_t bus1_priority_th : 2;      /*!< [25..24] Bus1 priority threshold                               */
      __IOM uint32_t bus2_priority_th : 2;      /*!< [27..26] Bus2 priority threshold                               */
      __IOM uint32_t bus3_priority_th : 2;      /*!< [29..28] Bus3 priority threshold                               */
      __IOM uint32_t pk_arbiter_mode : 2;       /*!< [31..30] Packet arbiter mode                                   */
    } desc_pkt_conf_reg_b;
  } ;
} CRYPTO_Type;                                  /*!< Size = 4112 (0x1010)                    */

/** @} */ /* End of group device_crypto_reg */

/* ================================================================================================================ */
/* ================                          Device Specific Peripheral Address Map                           ===== */
/* ================================================================================================================ */


/** @addtogroup device_crypto_addr Crypto Base Address
 *  @ingroup hs_hal_crypto
 *  @{
 */

#define CRYPTO_S_BASE                 0x50070000UL
#define CRYPTO_NS_BASE                0x40070000UL

/** @} */ /* End of group device_crypto_addr */


/* ================================================================================================================ */
/* ================                                  Peripheral declaration                                   ===== */
/* ================================================================================================================ */


/** @addtogroup device_crypto_decl Crypto Device Declaration
 *  @ingroup hs_hal_crypto
 *  @{
 */

#define CRYPTO_S_MODULE                         ((CRYPTO_Type *)            CRYPTO_S_BASE)
#define CRYPTO_NS_MODULE                        ((CRYPTO_Type *)            CRYPTO_NS_BASE)

/** @} */ /* End of group device_crypto_decl */

/// @endcond /* End of condition DOXYGEN_CRYPTO_REG_TYPE */

#ifdef __cplusplus
}
#endif

#endif /* RTL8195BHP_CRYPTO_H */

/** @} */ /* End of group hs_hal_crypto */

