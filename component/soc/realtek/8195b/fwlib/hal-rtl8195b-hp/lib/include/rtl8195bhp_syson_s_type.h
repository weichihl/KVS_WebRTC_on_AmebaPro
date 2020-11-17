/**************************************************************************//**
 * @file      rtl8195bhp_syson_s_type.h
 * @brief
 * @version   V1.00
 * @date      2017-11-1 11:46:19
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

#ifndef _RTL8195BHP_SYSON_SYSON_S_TYPE_H_
#define _RTL8195BHP_SYSON_SYSON_S_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_SYSON_S_REG_TYPE

/**
 * @addtogroup hs_hal_syson_s_reg SYSON_S Registers.
 * @ingroup hs_hal_syson
 * @{
 */

/**
  \brief Union type to access syson_s_sce_exmem_ctrl0 (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) SCE External Memory Control Register0                      */
  
  struct {
    __IOM uint32_t sce_exmem_op_addr : 8;     /*!< [7..0] When you want to read or write data from or to SCE register,
                                                   you need to fill the address to this register at first.
                                                   Uint: 4 bytes Ex: REG_SECURE_CTRL[7:0] = 0x2 represent
                                                   that SCE register is 0x08.                                                */
  } b;                                        /*!< bit fields for syson_s_sce_exmem_ctrl0 */
} syson_s_sce_exmem_ctrl0_t, *psyson_s_sce_exmem_ctrl0_t;

/**
  \brief Union type to access syson_s_sce_exmem_ctrl1 (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) SCE External Memory Control Register1                      */
  
  struct {
    __IOM uint32_t sce_exmem_op_data : 32;    /*!< [31..0] There are two operation in this register. One is reading
                                                   process and the other is writing process. Reading Process:
                                                   read data from SCE register according to REG_SCE_CONFIG[7:0].
                                                   Writing Process: write data to SCE register according to
                                                   REG_SCE_CONFIG[7:0].                                                      */
  } b;                                        /*!< bit fields for syson_s_sce_exmem_ctrl1 */
} syson_s_sce_exmem_ctrl1_t, *psyson_s_sce_exmem_ctrl1_t;

/**
  \brief Union type to access syson_s_sce_flash_ctrl0 (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) SCE Flash Control Register 0                               */
  
  struct {
    __IOM uint32_t sce_flash_op_addr : 8;     /*!< [7..0] When you want to read or write data from or to SCE register,
                                                   you need to fill the address to this register at first.
                                                   Uint: 4 bytes Ex: REG_SECURE_CTRL[7:0] = 0x2 represent
                                                   that SCE register is 0x08.                                                */
  } b;                                        /*!< bit fields for syson_s_sce_flash_ctrl0 */
} syson_s_sce_flash_ctrl0_t, *psyson_s_sce_flash_ctrl0_t;

/**
  \brief Union type to access syson_s_sce_flash_ctrl1 (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) SCE Flash Control Register 1                               */
  
  struct {
    __IOM uint32_t sce_flash_op_data : 32;    /*!< [31..0] There are two operation in this register. One is reading
                                                   process and the other is writing process. Reading Process:
                                                   read data from SCE register according to REG_SCE_CONFIG[7:0].
                                                   Writing Process: write data to SCE register according to
                                                   REG_SCE_CONFIG[7:0].                                                      */
  } b;                                        /*!< bit fields for syson_s_sce_flash_ctrl1 */
} syson_s_sce_flash_ctrl1_t, *psyson_s_sce_flash_ctrl1_t;

/**
  \brief Union type to access syson_s_sec_efuse_ctrl0 (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) SCE eFuse Control Register 0                               */
  
  struct {
    __IOM uint32_t sec_ef_data : 8;           /*!< [7..0] Access Data                                                        */
    __IOM uint32_t sec_ef_addr : 10;          /*!< [17..8] Access Address                                                    */
    __IM  uint32_t            : 13;
    __IOM uint32_t sec_ef_rwflag : 1;         /*!< [31..31] Write 1 for Program; Write 0 for Read Access                     */
  } b;                                        /*!< bit fields for syson_s_sec_efuse_ctrl0 */
} syson_s_sec_efuse_ctrl0_t, *psyson_s_sec_efuse_ctrl0_t;

/**
  \brief Union type to access syson_s_sec_efuse_ctrl1 (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) SCE eFuse Control Register 1                               */
  
  struct {
    __IM  uint32_t            : 1;
    __IOM uint32_t bit_sec_wlan_dis : 1;      /*!< [1..1] When this bit is written to '0', Wlan can access the
                                                   secure memory otherwise, if this bit is written to '1',
                                                   can not access the secure memory.                                         */
    __IOM uint32_t sec_sdio_host_dis : 1;     /*!< [2..2] When this bit is written to '0', SDIO Host can access
                                                   the secure memory otherwise, if this bit is written to
                                                   '1', can not access the secure memory.                                    */
    __IOM uint32_t sec_sdio_device_dis : 1;   /*!< [3..3] When this bit is written to '0', SDIO Device can access
                                                   the secure memory otherwise, if this bit is written to
                                                   '1', can not access the secure memory.                                    */
    __IOM uint32_t sec_mii_dis : 1;           /*!< [4..4] When this bit is written to '0', MII can access the secure
                                                   memory otherwise, if this bit is written to '1', can not
                                                   access the secure memory.                                                 */
    __IOM uint32_t sec_otg_dis : 1;           /*!< [5..5] When this bit is written to '0', OTG can access the secure
                                                   memory otherwise, if this bit is written to '1', can not
                                                   access the secure memory.                                                 */
    __IOM uint32_t sec_pcm_0_dis : 1;         /*!< [6..6] When this bit is written to '0', PCM can access the secure
                                                   memory otherwise, if this bit is written to '1', can not
                                                   access the secure memory.                                                 */
    __IOM uint32_t sec_pcm_1_dis : 1;         /*!< [7..7] When this bit is written to '0', PCM can access the secure
                                                   memory otherwise, if this bit is written to '1', can not
                                                   access the secure memory.                                                 */
    __IOM uint32_t sec_i2s_0_dis : 1;         /*!< [8..8] When this bit is written to '0', I2S can access the secure
                                                   memory otherwise, if this bit is written to '1', can not
                                                   access the secure memory.                                                 */
    __IOM uint32_t sec_i2s_1_dis : 1;         /*!< [9..9] When this bit is written to '0', I2S 1 can access the
                                                   secure memory otherwise, if this bit is written to '1',
                                                   can not access the secure memory.                                         */
    __IOM uint32_t sec_isp_dis : 1;           /*!< [10..10] When this bit is written to '0', ISP can access the
                                                   secure memory otherwise, if this bit is written to '1',
                                                   can not access the secure memory.                                         */
    __IM  uint32_t            : 5;
    __OM  uint32_t sec_ip_config_lock_en : 1; /*!< [16..16] When this bit is written to '1', this bit can not be
                                                   written to 0. Beside the high speed platform is reset.
                                                   1: REG_SYS_SECURE_CTRL[15:1] can not be accessed. 0: REG_SYS_SECURE_CTRL[
                                                   5:1] just can be accessed by secure state.                                */
  } b;                                        /*!< bit fields for syson_s_sec_efuse_ctrl1 */
} syson_s_sec_efuse_ctrl1_t, *psyson_s_sec_efuse_ctrl1_t;

/**
  \brief Union type to access syson_s_sec_clk_ctrl (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) SCE Clock Control Register                                 */
  
  struct {
    __IOM uint32_t flash_sce_clk_en : 1;      /*!< [0..0] 1: Enable flash SCE CLK                                            */
    __IOM uint32_t dram_sce_clk_en : 1;       /*!< [1..1] 1: Enable DDR SCE CLK                                              */
  } b;                                        /*!< bit fields for syson_s_sec_clk_ctrl */
} syson_s_sec_clk_ctrl_t, *psyson_s_sec_clk_ctrl_t;

/**
  \brief Union type to access syson_s_sec_func_ctrl (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) SCE Function Control Register                              */
  
  struct {
    __IOM uint32_t flash_sce_en : 1;          /*!< [0..0] 1: Enable flash SCE                                                */
    __IOM uint32_t dram_sce_en : 1;           /*!< [1..1] 1: Enable DDR SCE                                                  */
  } b;                                        /*!< bit fields for syson_s_sec_func_ctrl */
} syson_s_sec_func_ctrl_t, *psyson_s_sec_func_ctrl_t;

/** @} */ /* End of group hs_hal_syson_s_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_SYSON_S_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_SYSON_SYSON_S_TYPE_H_

