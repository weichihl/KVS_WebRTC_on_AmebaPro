/**************************************************************************//**
 * @file     efuse_boot_cfg.h
 * @brief    Define the structure types for boot flow configuration those from eFuse.
 * @version  V1.00
 * @date     2017-04-19
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

#ifndef _EFUSE_BOOT_CFG_H
#define _EFUSE_BOOT_CFG_H

#ifdef __cplusplus
extern "C" {
#endif

/**
  \brief  Define the debugging port configuration
*/
enum debug_port_cfg_e {
    DbgPorSWD           = 0,
    DbgPorJTagChain     = 1
};

/**
  \brief  Define the pin selection for JTag port
*/
enum jtag_pin_sel_e {
    JTag_S0             = 0,
    JTag_S1             = 1
};

/**
  \brief  Define the boot debugging UART port selection
*/
enum boot_dbg_uart_sel_e {
    BootDbgUART1        = 0,
    BootDbgUART0        = 1
};

/**
  \brief  Define the boot debugging message on/off control
*/
enum boot_dbg_msg_ctrl_e {
    BootDbgMsgOn        = 0,
    BootDbgMsgOff       = 1
};

/**
  \brief  Define XTAL input clock selection
*/
enum xtal_sel_e {
    XtalIn40M           = 0,            /*!< 0   XTAL input 40MHz                                                     */
    XtalIn25M           = 1,            /*!< 1   XTAL input 25MHz                                                     */
    XtalIn13M           = 2,            /*!< 2   XTAL input 13MHz                                                     */
    XtalIn192M          = 3,            /*!< 3   XTAL input 19.2MHz                                                   */
    XtalIn20M           = 4,            /*!< 4   XTAL input 20MHz                                                     */
    XtalIn26M           = 5,            /*!< 5   XTAL input 26MHz                                                     */
    XtalIn384M          = 6,            /*!< 6   XTAL input 38.4MHz                                                   */
    XtalIn176M          = 7,            /*!< 7   XTAL input 17.664MHz                                                 */
    XtalIn16M           = 8,            /*!< 8   XTAL input 16MHz                                                     */
    XtalIn141M          = 9,            /*!< 9   XTAL input 14.138MHz                                                 */
    XtalIn12M           = 10,           /*!< 10  XTAL input 12MHz                                                     */
    XtalIn52M           = 11,           /*!< 11  XTAL input 52MHz                                                     */
    XtalIn48M           = 12,           /*!< 12  XTAL input 48MHz                                                     */
    XtalIn27M           = 13,           /*!< 13  XTAL input 27MHz                                                     */
    XtalIn24M           = 14,           /*!< 14  XTAL input 24MHz                                                     */
    XtalInNone          = 15,           /*!< 14  No XTAL input                                                        */
};

typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t ls_jtag_en        : 1;       /*!< [0..0] LS platform JTag function enable, 1:enable */
    __IM  uint8_t : 1;                         /*!< [1..1] Reserved */
    __IOM uint8_t ls_secure_mode_en : 2;       /*!< [3..2] LS secure mode enable, 11: secure, others: non-secure */
    __IOM uint8_t hs_s_jtag_en      : 2;       /*!< [5..4] HS platform secure J-Tag enable, 11: enable, others: disable */
    __IOM uint8_t hs_ns_jtag_en     : 2;       /*!< [7..6] HS platform non-secure J-Tag enable, 11: enable, others: disable */
  } bit;
} efuse_dbg_port_cfg_t, *pefuse_dbg_port_cfg_t;

typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t swr_vol11_sel      : 4;       /*!< [0..3] SWR voltage selection */
    __IOM uint8_t swr_std_sel        : 2;       /*!< [4..5] SWR STD selection */
    __IOM uint8_t swr_fpwm_en        : 1;       /*!< [6..6] Enable SWR force PWM */
    __IOM uint8_t swr_ocp_en         : 1;       /*!< [7..7] Enable SWR OCP */
  } bit;
} efuse_swr_cfg1_t, *pefuse_swr_cfg1_t;


typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t ls_dbger_sel      : 1;       /*!< [0..0] LS debugger selection: 0:SWD, 1:J-TAG Chain */
    __IOM uint8_t hs_dbger_sel      : 1;       /*!< [1..1] HS debugger selection: 0:SWD/J-TAG Chain, 1:J-TAG */
    __IOM uint8_t dbg_port_pin_sel  : 1;       /*!< [2..2] HS J-Tag port pin selection: 0: E0 ~ E4, 1: C2 ~ C6 */
    __IM  uint8_t : 3;                         /*!< [5..3] Reserved */
    __IOM uint8_t dbg_uart_sel      : 1;       /*!< [6..6] debugging UART port selection */
    __IOM uint8_t dbg_msg_ctrl      : 1;       /*!< [7..7] debugging message on/off control */
  } bit;
} efuse_boot_cfg1_t, *pefuse_boot_cfg1_t;

typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t ldo_d_disable     : 1;       /*!< [0..0] LDO_D Disable, 1: Disable LDO_D */
    __IOM uint8_t hs_sys_pll_sel    : 1;       /*!< [1..1] HS platform Sys PLL clock selection, 0: 300M, 1: 200M */
    __IM  uint8_t : 6;                         /*!< [7..1] Reserved */
  } bit;
} efuse_boot_cfg2_t, *pefuse_boot_cfg2_t;

typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t hs_sys_pll_sel     : 1;       /*!< [0..0] HS platform Sys PLL clock selection, 1: 300M, 0: 200M */
    __IOM uint8_t hs_sys_pll_dev_sel : 4;       /*!< [4..1] HS platform Sys PLL clock devider selection */
    __IM  uint8_t                    : 3;       /*!< [7..5] Reserved */
  } bit;
} efuse_clk_cfg1_t, *pefuse_clk_cfg1_t;


typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t ldo_d_mode_sel    : 1;       /*!< [0..0] ldod mode selection 1: LDO */
    __IOM uint8_t boost_en          : 1;       /*!< [1..1] Enable boost */
    __IOM uint8_t chg_en            : 1;       /*!< [2..2] Enable CHG */
    __IM  uint8_t                   : 5;       /*!< [7..3] Reserved */
  } bit;
} efuse_regu_cfg1_t, *pefuse_regu_cfg1_t;

typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t swrm_en           : 1;       /*!< [0..0] SWRM Enable  */
    __IOM uint8_t swrm_mode_en      : 1;       /*!< [1..1] SWRM mode selection */
    __IOM uint8_t ldod_src_mem_en   : 1;       /*!< [2..2] enable ldod as mem power source; 0: enable */
    __IOM uint8_t ldod_src_adj      : 4;       /*!< [6..3] ldod output adj  */
    __IM  uint8_t                   : 1;       /*!< [7..7] Reserved */
  } bit;
} efuse_regu_cfg2_t, *pefuse_regu_cfg2_t;

typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t delay_ctrl        : 1;       /*!< [0..0] boot flow delay control, 0: normal delay, 1: delay x 2  */
    __IM  uint8_t                   : 7;       /*!< [7..1] Reserved */
  } bit;
} efuse_delay_ctrl_t, *pefuse_delay_ctrl_t;

#define EFuseDbgPortCfgOffset       (0x00)
#define EFuseSwrCfg1Offset          (0x04)
#define EFuseBootCfg1Offset         (0x10)
#define EFuseBootCfg2Offset         (0x14)
#define EFuseBootDelayCtrlOffset    (0x1E)
#define EFuseAutoLoadRegBase        (0xA0000220UL)

// Registers for eFuse auto-load 
#define DbgPortCfgReg               ((efuse_dbg_port_cfg_t*)(EFuseAutoLoadRegBase + EFuseDbgPortCfgOffset))
#define BootCfg1Reg                 ((efuse_boot_cfg1_t*)(EFuseAutoLoadRegBase + EFuseBootCfg1Offset))
#define BootCfg2Reg                 ((efuse_boot_cfg2_t*)(EFuseAutoLoadRegBase + EFuseBootCfg2Offset))
#define SWRCfg1Reg                  ((efuse_swr_cfg1_t*)(EFuseAutoLoadRegBase + EFuseSwrCfg1Offset))
#define BootDelayCtrlReg            ((efuse_delay_ctrl_t*)(EFuseAutoLoadRegBase + EFuseBootDelayCtrlOffset))

#define EFusePackageSel             (0x1F8)
#define EFuseClkSel                 (0x1F9)
#define EFuseReguSel                (0x1FA)
#define EFuseReguSel2               (0x1FB)

#ifdef __cplusplus
}
#endif

#endif /* _EFUSE_BOOT_CFG_H */
