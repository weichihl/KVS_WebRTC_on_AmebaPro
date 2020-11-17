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
#include "platform_conf.h"

/**
  \brief  Define the boot method
*/
enum boot_type_e {
    BootFromFlash               = 0,
    BootFromUART                = 1,
    BootFromSDMMC               = 2,
    BootFromSDIOD               = 3,
    BootFromSUSB                = 4,

    BootFromTestModeUART        = 5
};

/**
  \brief  Define the debugging port configuration
*/
enum debug_port_cfg_e {
    DbgPorSWD           = 0,
    DbgPorJTagChain     = 1,
    DbgPorJTag          = 2
};

/**
  \brief  Define the pin selection for flash boot
*/
/* make sure:
    BootFlash_DualIOS0 = SpicDualIOPin;
    BootFlash_QuadIOS0 = SpicQuadIOPin;
    BootFlash_OctalIO = SpicOctalIOPin;
    BootFlash_DualIOS1 = 3;
    BootFlash_QuadIOS1 = 4;
*/
enum flas_boot_pin_sel_e {
    BootFlash_DualIOS0  = 0,
    BootFlash_QuadIOS0  = 1,
    BootFlash_OctalIO   = 2,
    BootFlash_DualIOS1  = 3,
    BootFlash_QuadIOS1  = 4
};

/**
  \brief  Define the UART port selection for UART boot
*/
enum uart_boot_port_sel_e {
    BootUART1           = 0,
    BootUART0           = 1,
    BootUART2           = 2
};

/**
  \brief  Define the pin selection for UART boot
*/
enum uart_boot_pin_sel_e {
    BootUART_S0         = 0,
    BootUART_S1         = 1,
    BootUART_S2         = 2,
    BootUART_S3         = 3
};

/**
  \brief  Define the pin selection for SDMMC boot
*/
enum sdmmc_boot_pin_sel_e {
    BootSDMMC_S0        = 0,
    BootSDMMC_S1        = 1
};

/**
  \brief  Define the boot debugging UART port selection
*/
enum boot_dbg_uart_sel_e {
    BootDbgUART0        = 0,
    BootDbgUART1        = 1,
    BootDbgUART2        = 2
};

/**
  \brief  Define the boot debugging message on/off control
*/
enum boot_dbg_msg_ctrl_e {
    BootDbgMsgOn        = 0,
    BootDbgMsgOff       = 1
};

typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t swrm_vol11_sel     : 4;       /*!< [0..3] SWRM voltage selection */
    __IOM uint8_t swrm_std_sel       : 2;       /*!< [4..5] SWRM STD selection */
    __IOM uint8_t swrm_in01          : 2;       /*!< [7..6] SWRM IN <1:0> */
  } bit;
} efuse_swr_cfg1_t, *pefuse_swr_cfg1_t;

typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t boot_sel        : 4;       /*!< [3..0] Boot method selection */
    __IOM uint8_t pin_sel         : 2;       /*!< [5..4] Boot peripheral's pin selection */
    __IOM uint8_t port_rate_sel   : 2;       /*!< [7..6] Boot peripheral's port selection */
  } bit;
} efuse_boot_cfg1_t, *pefuse_boot_cfg1_t;

typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t cfg             : 3;       /*!< [2..0] Boot peripheral configuration */
    __IM  uint8_t : 3;                       /*!< [5..3] Reserved */
    __IOM uint8_t nsk_mode        : 1;       /*!< [6..6] Secure book No-Share-Key mode enable: 0: disable, 1: enable */
    __IOM uint8_t secure_lock     : 1;       /*!< [7..7] Secure book lock: is allow to load un-encrypted image */
  } bit;
} efuse_boot_cfg2_t, *pefuse_boot_cfg2_t;

typedef union {
  __IOM uint8_t byte;
  
  struct {
    __IOM uint8_t port_sel    : 2;           /*!< [1..0] Boot debugging UART port selection */
    __IOM uint8_t pin_sel     : 2;           /*!< [3..2] Boot debugging UART pin selection */
    __IOM uint8_t dbg_en      : 1;           /*!< [4..4] Boot debugging message enable */
    __IM  uint8_t : 3;
  } bit;
} efuse_boot_dbg_port_cfg_t, *pefuse_boot_dbg_port_cfg_t;

/**
  \brief Union type to access super_sec_ef_ctrl (@ 0x50002c80).
*/
typedef union {
  __OM  uint32_t w;                           /*!< (@ 0x50002c80) Super Secure eFuse Control Register                        */
  
  struct {
    __OM  uint32_t sec_super_sec_ef_lock : 1; /*!< [0..0] When this bit is written to '1', this bit can not be
                                                   written to '0'. Beside the high speed platform is reset.
                                                   1: Super secure zone can not be accessed. 0: Super secure
                                                   zone just can be accessed by secure state. (AXI_PORT[1]
                                                   = 0)                                                                      */
  } b;
} super_sec_ef_ctrl_t, *psuper_sec_ef_ctrl_t;

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

#define EFuseSwrmCfgOffset          (0x04)
#define EFuseBootCfg1Offset         (0x18)
#define EFuseBootCfg2Offset         (0x19)
#define EFuseDbgMsgCfgOffset        (0x1A)
#define EFuseAutoLoadRegBase        (0x40000100UL)

// Registers for eFuse auto-load 
#define SwrmCfgReg                  ((efuse_swr_cfg1_t*)(EFuseAutoLoadRegBase + EFuseSwrmCfgOffset))
#define BootCfg1Reg                 ((efuse_boot_cfg1_t*)(EFuseAutoLoadRegBase + EFuseBootCfg1Offset))
#define BootCfg2Reg                 ((efuse_boot_cfg2_t*)(EFuseAutoLoadRegBase + EFuseBootCfg2Offset))
#define BootDbgMsgCfgReg            ((efuse_boot_dbg_port_cfg_t*)(EFuseAutoLoadRegBase + EFuseDbgMsgCfgOffset))
#define SuperSecEFCtrlReg           ((super_sec_ef_ctrl_t*)(0x50002c80))

#define EFusePackageSel             (0x1F8)
#define EFuseClkSel                 (0x1F9)
#define EFuseReguSel                (0x1FA)
#define EFuseReguSel2               (0x1FB)


#ifdef __cplusplus
}
#endif

#endif /* _EFUSE_BOOT_CFG_H */
