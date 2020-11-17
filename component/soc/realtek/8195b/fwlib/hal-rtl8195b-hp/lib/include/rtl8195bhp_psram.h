/**************************************************************************//**
* @file         rtl819bhp_psram.h
* @brief       The fundamental definition for RTL8195B HP PSRAM module.
*
* @version    V1.00
* @date        2017-07-18
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

#ifndef RTL8195BHP_PSRAM_H
#define RTL8195BHP_PSRAM_H


#ifdef  __cplusplus
  extern "C"
  {
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_PSRAM_CTRL_REG_TYPE

/**
 * @addtogroup hs_hal_psram PSRAM
 * @ingroup 8195bh_hal
 * @{
 * @brief The PSRAM HAL module of the HS platform.
 */

#include "rtl8195bhp_psram_ctrl.h"
#include "rtl8195bhp_psram_ctrl_type.h"

/**
  \brief  Define the psram page size.
*/
enum psram_page_size_e {
    Page256     = 0,
    Page512     = 1,
    Page1k      = 2,
    Page2k      = 3,
    Page4k      = 4,
    Page8k      = 5,
    Page16k     = 6,
    Page32k     = 7,
    Page64k     = 8,
};
typedef uint8_t psram_page_size_t;

/**
  \brief  Define the psram bank size.
*/
enum psram_bank_size_e {
    Bank2   = 0,
    Bank4   = 1,
    Bank8   = 2,
};
typedef uint8_t psram_bank_size_t;

/**
  \brief  Define the psram DQ width.
*/
enum psram_dq_width_e {
    Dq16        = 0,
    Dq32        = 1,
};
typedef uint8_t psram_dq_width_t;

/**
  \brief  Define the psram burst length.
*/
enum psram_mode0_bst_len_e {
    BstLen4     = 0,
    BstLenFly   = 1,
    BstLen8     = 2,
    BstLenCont  = 3, //continuous burst
};
typedef uint8_t psram_mode0_bst_len_t;

/**
  \brief  Define the psram burst type.
*/
enum psram_mode0_bst_type_e {
    Sequential  = 0,
    Interleave  = 1,
};
typedef uint8_t psram_mode0_bst_type_t;

/**
  \brief  Define the psram DFI ratio type.
*/
enum psram_dfi_ratio_type_e {
    DfiRatio1   = 0,
    DfiRatio2   = 1,
    Dfiratio4   = 2,
};
typedef uint8_t psram_dfi_ratio_type_t;

/**
  \brief  Define the psram DDR mode.
*/
enum psram_mode0_ddr_mode_e {
    SdrMode     = 0,
    DdrMode     = 1,
};
typedef uint8_t psram_mode0_ddr_mode_t;

/**
  \brief  Define the psram latency mode.
*/
enum psram_mode0_lt_mode_e {
    Variety     = 0,
    Fix         = 1,
};
typedef uint8_t psram_mode0_lt_mode_t;

/**
  \brief  Define the psram latency code.
*/
enum psram_mode0_lt_code_e {
    Lc0     = 0,
    Lc2     = 2,
    Lc3     = 3,
    Lc4     = 4,
    Lc5     = 5,
    Lc6     = 6,
    Lc7     = 7,
};
typedef uint8_t psram_mode0_lt_code_t;

/**
  \brief  Define the psram asynchronous mode.
*/
enum psram_mode0_async_mode_e {
    Sync    = 0,
    Async   = 1,
};
typedef uint8_t psram_mode0_async_mode_t;

/**
  \brief  Define the psram AADMUX mode.
*/
enum psram_aadmux_mode_e {
    Admux   = 0,
    Aadmux  = 1,
};
typedef uint8_t psram_aadmux_mode_t;

/**
  \brief  Define the psram control register.
*/
enum psram_ctrl_reg_e {
    Bcr     = 0,
    Rcr     = 1,
    Didr    = 2,
};
typedef uint8_t psram_ctrl_reg_t;

/**
  \brief  The data structure for psram infomation.
*/
typedef struct psram_info_s {
    psram_page_size_t   page;
    psram_dq_width_t    dq_width;
    uint32_t            aadmux_en;
    uint32_t            cre_en;
    uint32_t            async_clk_en;
    uint32_t            suspend_en;
}psram_info_t, *ppsram_info_t;

/**
  \brief  The data structure for psram mode0 register setting .
*/
typedef struct psram_mode_reg_info_s {
    psram_mode0_bst_len_t       bst_len;
    psram_mode0_ddr_mode_t      ddr_mode;
    psram_mode0_lt_mode_t       lt_mode;
    psram_mode0_async_mode_t    async_mode;
    psram_mode0_lt_code_t       lt_code;
}psram_mode_reg_info_t, *ppsram_mode_reg_info_t;

/**
  \brief  The data structure for psram timing setting .
*/
typedef struct psram_timing_info_s {
    uint32_t    tpu_ps;
    uint32_t    tcem_ps;
    uint32_t    tcph_ps;
    uint32_t    toe_ps;
    uint32_t    twp_ps;
    uint32_t    twph_ps;
    uint32_t    twc_ps;
    uint32_t    trc_ps;
    uint32_t    toh_ps;
    uint32_t    tos_ps;
    uint32_t    tvp_ps;
    uint32_t    tavh_ps;
    uint32_t    tcvs_ps;
}psram_timing_info_t, *ppsram_timing_info_t;

/**
  * @brief The structure for psram dqss, dqsck information.
  */
typedef struct psram_ddr_mode_dqs_info_s {
    uint32_t    dqss;
    uint32_t    dqsck;
}psram_ddr_mode_dqs_info_t, *ppsram_ddr_mode_dqs_info_t;

/**
  * @brief The structure for psram IOCR register setting
  */
typedef struct psram_iocr_phy_info_s {
    uint32_t    rd_pipe;
    uint32_t    dfi_path_dly;
    uint32_t    tphy_wrdata;
    uint32_t    tphy_rddata_en;
    uint32_t    dfi_cs_wr_dly;
    uint32_t    dfi_cs_rd_dly;
    uint32_t    dfi_cke_wr_dly;
    uint32_t    dfi_cke_rd_dly;
    uint32_t    dfi_cke_cmd_dly;
}psram_iocr_phy_info_t, *ppsram_iocr_phy_info_t;

/**
  * @brief The structure to be used to pass the parameters for
  *        psram phy and controller setting
  */
typedef struct psram_device_info_s {
    psram_info_t                *pdev;
    psram_mode_reg_info_t       *pmode_reg;
    psram_timing_info_t         *ptiming;
    psram_ddr_mode_dqs_info_t   *pdqs;
    psram_iocr_phy_info_t       *piocr_phy;
    uint32_t                    ddr_period_ps;
    psram_dfi_ratio_type_t      dfi_rate;
}psram_device_info_t, *ppsram_device_info_t;


//PSRAM Timing (for 166MHz)
/// PSRAM Clock cycle time (uint: ps)
#define PSRAM_PERIOD_PS     6000                //ps

/// PSRAM CE# high between subsequent async operations time (uint: ps)
#define PSRAM_TIMING_TCPH   (2*PSRAM_PERIOD_PS) //ps

/// PSRAM power up time (uint: ps)
#define PSRAM_TIMING_TPU    150000              //ps
/// PSRAM maximum CE# pulse width time (uint: ps)
#define PSRAM_TIMING_TCEM   1000000             //ps
/// PSRAM output enable to valid output time (uint: ps)
#define PSRAM_TIMING_TOE    20000               //ps
/// PSRAM write pulse width time (uint: ps)
#define PSRAM_TIMING_TWP    45000               //ps
/// PSRAM write pulse width HIGH time (uint: ps)
#define PSRAM_TIMING_TWPH   10000               //ps
#define PSRAM_TIMING_TWC    70000               //ps
#define PSRAM_TIMING_TRC    70000               //ps
#define PSRAM_TIMING_TOH    0                   //ps
#define PSRAM_TIMING_TOS    0                   //ps
/// PSRAM ADV# pulse width LOW time (uint: ps)
#define PSRAM_TIMING_TVP    5000                //ps
/// PSRAM Address hold from ADV# HIGH time (uint: ps)
#define PSRAM_TIMING_TAVH   2000                //ps
/// PSRAM CE# LOW to ADV# HIGH time (uint: ps)
#define PSRAM_TIMING_TCVS   7000                //ps
/// PSRAM CLK rising to DQS rising (uint: clk)
#define PSRAM_TIMING_TDQSS  1                   //clk
/// PSRAM DQS output access time from CLK (uint: clk)
#define PSRAM_TIMING_TDQSCK 0                   //clk


/// PSRAM register base address
#define PSRAM_REG_BASE         0x60000000

/** @} */ /* End of group hs_hal_psram */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_PSRAM_CTRL_REG_TYPE */


#ifdef  __cplusplus
}
#endif


#endif //#ifndef RTL8195BHP_PSRAM_H


