/**************************************************************************//**
 * @file     hal_icc_app.h
 * @brief    The ICC Application level API definition.
 * @version  V1.00
 * @date     2017-07-13
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

#ifndef _HAL_ICC_APP_H_
#define _HAL_ICC_APP_H_
#include "cmsis.h"
#include "hal_icc_nsc.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @brief  Define the HAL layer ICC commands those are used in the communication between HS platform and LS platform.
 *         The commanf type definition should be the same for both HS and LS.
 */
enum hal_icc_commands {
    HAL_ICC_CMD_DBG_PORT_CFG    = 0xB1,     ///< Notification of the debugger port configuration, LS -> HS
    HAL_ICC_CMD_LS_RDY          = 0xB2,     ///< Notification of LS booting ready, LS -> HS
    HAL_ICC_CMD_LS_RST_REQ      = 0xB3,     ///< Request to LS to do reboot, HS -> LS
    HAL_ICC_CMD_LS_EFUSE_RWB    = 0xB4,     ///< Request to read/write LS eFuse 1 byte, HS -> LS
    HAL_ICC_CMD_LS_EFUSE_RW_RET = 0xB5,     ///< Status of read/write LS eFuse data command, LS -> HS
    HAL_ICC_CMD_LS_SWWDT_INIT   = 0xB6,		///< Request to LS to init HS monitor, HS -> LS
    HAL_ICC_CMD_LS_SWWDT_START	= 0xB7,     ///< Request to LS to start HS monitor, HS -> LS
    HAL_ICC_CMD_LS_SWWDT_REFLESH= 0xB8,     ///< Request to LS to refresh HS monitor, HS -> LS
    HAL_ICC_LP_CG               = 0xC0,     ///< Notification of HS CG, HS -> LS
    HAL_ICC_LP_PD               = 0xC1      ///< Notification of HS PD, HS -> LS
};

/**
 * @brief  Define the ICC Dg port configuration command format.
*/
typedef struct icc_cmd_dbg_port_cfg_s {
    union {
        uint32_t word0;
        struct {
            uint32_t hs_dbg_mode:8;     ///< HS debugger port mode: JTAG(Chain) or SWD
            uint32_t hs_dbg_pin_sel:8;  ///< HS debugger port pin selection: S0(GPIOE 0 ~ 4) or S1(GPIOC 2~ 6)
            uint32_t ls_dbg_mode:8;     ///< LS debugger port mode: JTAG(Chain) or SWD
            uint32_t cmd:8;
        } word0_b;
    };

    union {
        uint32_t word1;
        uint32_t para1;
    };
} icc_cmd_dbg_port_cfg_t, *picc_cmd_dbg_port_cfg_t;

enum icc_ls_efuse_rw_flag {
    ICC_LS_EFUSE_READ   = 0,
    ICC_LS_EFUSE_WRITE  = 1
};

/**
 * @brief  ICC command for LS eFuse data read/write.
*/
typedef struct icc_cmd_ls_efuse_rw_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t byte_cnt:2;    ///< byte count to read/write: 0 ~ 3 = 1 ~ 4
            uint32_t rw_flag:1;     ///< read(0) or write(1)
            uint32_t reserved:5;
            uint32_t addr:16;       ///< efuse address
            uint32_t cmd:8;
        } cmd_b;
    };
} icc_cmd_ls_efuse_rw_t, *picc_cmd_ls_efuse_rw_t;

/**
 * @brief  ICC command for LS eFuse data read/write command result.
*/
typedef struct icc_cmd_ls_efuse_rw_ret_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t byte_cnt:2;    ///< byte count to read/write: 0 ~ 3 = 1 ~ 4
            uint32_t rw_flag:1;     ///< read(0) or write(1)
            uint32_t status:5;      ///< command status
            uint32_t addr:16;       ///< efuse address
            uint32_t cmd:8;
        } cmd_b;
    };
} icc_cmd_ls_efuse_rw_ret_t, *picc_cmd_ls_efuse_rw_ret_t;

#if defined (CONFIG_BUILD_NONSECURE)
extern icc_ns_adapter_t icc_hal_adp;
#else
extern hal_icc_adapter_t icc_hal_adp;
#endif

void icc_hal_app_init (void);
void icc_task_init(void);
hal_status_t icc_happ_ls_write_reg (uint32_t addr, uint32_t value);
uint32_t icc_happ_ls_read_reg (uint32_t addr);
hal_status_t hal_icc_ls_efuse_write (uint16_t addr, uint8_t data);
hal_status_t hal_icc_ls_efuse_read (uint16_t addr, uint8_t *pdata);
#define hal_ls_efuse_write          hal_icc_ls_efuse_write
#define hal_ls_efuse_read           hal_icc_ls_efuse_read

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_ICC_APP_H_"

