/**************************************************************************//**
* @file         rtl819bhp_lpddr.h
* @brief       The fundamental definition for RTL8195B HP LPDDR module.
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

#ifndef RTL8195BHP_LPDDR_H
#define RTL8195BHP_LPDDR_H


#ifdef  __cplusplus
  extern "C"
  {
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_LPDDR_CTRL_REG_TYPE

/**
 * @addtogroup hs_hal_lpddr LPDDR
 * @ingroup 8195bh_hal
 * @{
 * @brief The LPDDR HAL module of the HS platform.
 */

#include "rtl8195bhp_lpddr_ctrl.h"
#include "rtl8195bhp_lpddr_ctrl_type.h"

/**
  \brief  Define the lpddr dram type.
*/
enum lpddr_dram_type_e {
    NonDdr      = 0,
    Ddr1        = 1,
    Ddr2        = 2,
    Ddr3        = 3,
    Ddr4        = 4,
    DramSdr     = 8,
    Lpddr1      = 9,
};
typedef uint8_t lpddr_dram_type_t;

/**
  \brief  Define the lpddr page size.
*/
enum lpddr_page_size_e {
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
typedef uint8_t lpddr_page_size_t;

/**
  \brief  Define the lpddr bank size.
*/
enum lpddr_bank_size_e {
    Bank2       = 0,
    Bank4       = 1,
    Bank8       = 2,
};
typedef uint8_t lpddr_bank_size_t;

/**
  \brief  Define the lpddr DQ width.
*/
enum lpddr_dq_width_e {
    Dq16        = 0,
    Dq32        = 1,
    HalfDq32    = 2,
};
typedef uint8_t lpddr_dq_width_t;

/**
  \brief  Define the lpddr burst length.
*/
enum lpddr_mode0_bst_len_e {
    BstLen4     = 0,
    BstLenFly   = 1,
    BstLen8     = 2,
};
typedef uint8_t lpddr_mode0_bst_len_t;

/**
  \brief  Define the lpddr burst type.
*/
enum lpddr_mode0_bst_type_e {
    Sequential  = 0,
    Interleave  = 1,
};
typedef uint8_t lpddr_mode0_bst_type_t;

/**
  \brief  Define the lpddr dfi ratio.
*/
enum lpddr_dfi_ratio_type_e {
    DfiRatio1   = 0,
    DfiRatio2   = 1,
    Dfiratio4   = 2,
};
typedef uint8_t lpddr_dfi_ratio_type_t;

/**
  \brief  Define the lpddr partial array self-refresh type.
*/
enum lpddr_pasr_type_e {
    AllBank         = 0,
    HalfArray       = 1,
    QuarterArray    = 2,
    QuarterDsr      = 3,
    OctanDsr        = 4,
    OctanArray      = 5,
    OneSixteenArray = 6,
    OneSixteenDsr   = 7,
};
typedef uint8_t lpddr_pasr_type_t;

/**
  \brief  Define the lpddr drive strength type.
*/
//Drive Strength Type
enum lpddr_ds_type_e {
    Full            = 0,
    Half            = 1,
    Quarter         = 2,
    Octan           = 3,
    ThreeQuarter    = 4,
};
typedef uint8_t lpddr_ds_type_t;

/**
  \brief  The data structure for dram infomation.
*/
typedef struct lpddr_info_s {
    lpddr_dram_type_t   device_type;
    lpddr_page_size_t   page;
    lpddr_bank_size_t   bank;
    lpddr_dq_width_t    dq_width;
} lpddr_info_t, *plpddr_info_t;

/**
  \brief  The data structure for dram mode0 register setting .
*/
typedef struct lpddr_dram_mode_reg_info_s {
    lpddr_mode0_bst_len_t   bst_len;
    lpddr_mode0_bst_type_t  bst_type;
    uint32_t                mode0_cas;
    uint32_t                mode0_wr;
    uint32_t                mode1_dll_en_n;
    uint32_t                mode1_all_lat;
    uint32_t                mode2_cwl;
    uint32_t                dram_par_lat;
    uint32_t                dram_wr_lat;
    uint32_t                dram_rd_lat;
    uint32_t                dram_add_lat;
} lpddr_dram_mode_reg_info_t, *plpddr_dram_mode_reg_info_t;

/**
  \brief  The data structure for dram timing setting .
*/
typedef struct lpddr_timing_info_s {
    uint32_t    trfc_ps;
    uint32_t    trefi_ps;
    uint32_t    wr_max_tck;
    uint32_t    trcd_ps;
    uint32_t    trp_ps;
    uint32_t    tras_ps;
    uint32_t    trrd_ps;
    uint32_t    twr_ps;
    uint32_t    twtr_tck;
    uint32_t    tmrd_tck;
    uint32_t    trtp_tck;
    uint32_t    tccd_tck;
    uint32_t    trc_ps;
    uint32_t    tccd_s_tck;
    uint32_t    twtr_s_tck;
} lpddr_timing_info_t, *plpddr_timing_info_t;

/**
  * @brief The structure to be used to pass the parameters for
  *        lpddr phy and controller setting
  */
typedef struct lpddr_device_info_s {
    lpddr_info_t                *pdev;
    lpddr_dram_mode_reg_info_t  *pmode_reg;
    lpddr_timing_info_t         *ptiming;
    uint32_t                    ddr_period_ps;
    lpddr_dfi_ratio_type_t      dfi_rate;
    lpddr_pasr_type_t           pasr;
    lpddr_ds_type_t             ds;
} lpddr_device_info_t, *plpddr_device_info_t;

//LPDDR Timing
/// LPDDR Clock cycle time (uint: ps)
#define LPDDR_TIMING_TCK        5000   //ps

/// LPDDR AUTO REFRESH to ACTIVE/AUTO REFRESH command period (uint: ps)
#define LPDDR_TIMING_TRFC       72000                   //ps
/// LPDDR Average periodic refresh interval (uint: ps)
#define LPDDR_TIMING_TREFI      7800000                 //ps
/// LPDDR max WRITE recovery time (uint: tck)
#define LPDDR_TIMING_TWRMAXTCK  3                       //tck
/// LPDDR ACTIVE to READ or WRITE delay (uint: ps)
#define LPDDR_TIMING_TRCD       15000                   //ps
/// LPDDR PRECHARGE command period (uint: ps)
#define LPDDR_TIMING_TRP        (3*LPDDR_TIMING_TCK)    //ps
/// LPDDR ACTIVE to PRECHARGE command period (uint: ps)
#define LPDDR_TIMING_TRAS       40000                   //ps
/// LPDDR ACTIVE bank A to ACTIVE bank B delay (uint: ps)
#define LPDDR_TIMING_TRRD       10000                   //ps
/// LPDDR WRITE recovery time (uint: ps)
#define LPDDR_TIMING_TWR        15000                   //ps
/// LPDDR Internal write to Read command delay (uint: tck)
#define LPDDR_TIMING_TWTR       1                       //tck
/// LPDDR MODE REGISTER SET command period (uint: tck)
#define LPDDR_TIMING_TMRD       2                       //tck
#define LPDDR_TIMING_TRTP       0                       //tck
#define LPDDR_TIMING_TCCD       1                       //tck
/// LPDDR ACTIVE to ACTIVE command period (uint: ps)
#define LPDDR_TIMING_TRC        (LPDDR_TIMING_TRAS+LPDDR_TIMING_TRP)    //ps
#define LPDDR_TIMING_TCCDS      0                       //tck
#define LPDDR_TIMING_TWTRS      0                       //tck

/// LPDDR1 register base address
#define LPDDR1_REG_BASE         0x70000000
/// LPDDR1 command SRAM of BSTC function
#define BIST_CMD_BASE           0x40420000
/// LPDDR1 write data SRAM of BSTC function
#define BIST_WD_BASE            0x40421000
/// LPDDR1 mask SRAM of BSTC function
#define BIST_MSK_BASE           0x40423800
/// LPDDR1 read golden data SRAM of BSTC function
#define BIST_RG_BASE            0x4042C000
/// LPDDR1 read data SRAM of BSTC function
#define BIST_RD_BASE            0x40434800

/** @} */ /* End of group hs_hal_lpddr */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_LPDDR_CTRL_REG_TYPE */


#ifdef  __cplusplus
}
#endif


#endif //#ifndef RTL8195BHP_LPDDR_H

