/**************************************************************************//**
* @file         rtl819bhp_dram.h
* @brief       The fundamental definition for RTL8195B HP DRAM module.
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

#ifndef RTL8195BHP_DRAM_H
#define RTL8195BHP_DRAM_H

#ifdef  __cplusplus
  extern "C"
  {
#endif

#include "cmsis.h"

#include "rtl8195bhp_dpi.h"
#include "rtl8195bhp_dpi_type.h"

#define DRAM_CAL_EN  0

/// 20MHz reference clock of LPDDR PLL
#define DDRPLL_reference_clock_20 20
/// 24MHz reference clock of LPDDR PLL
#define DDRPLL_reference_clock_24 24
/// 25MHz reference clock of LPDDR PLL
#define DDRPLL_reference_clock_25 25
/// 26MHz reference clock of LPDDR PLL
#define DDRPLL_reference_clock_26 26
/// 27MHz reference clock of LPDDR PLL
#define DDRPLL_reference_clock_27 27
/// 40MHz reference clock of LPDDR PLL
#define DDRPLL_reference_clock_40 40

/**
  \brief  Define the xtal selection.
*/
enum xtal_rate_e {
    xtal_40M    = 0,
    xtal_25M    = 1,
    xtal_20M    = 4,
    xtal_26M    = 5,
    xtal_27M    = 13,
    xtal_24M    = 14,
};
typedef uint8_t xtal_rate_t;

#if DRAM_CAL_EN
uint8_t dram_access_test(void);
void dram_calibration_dck_map(void);
void dram_calibration_dqs_map(void);
void dram_calibration_dq_map(void);
void dram_calibration_dqs_en(void);
void dram_calibration_rxdelaytap_map(void);
void dram_calibration_txdelaytap_map(void);
void dram_calibration_rxfifo_map(void);
void dram_calibration_rxodt_map(void);
#endif //#if DRAM_CAL_EN

void dram_init_clk_frequency(uint32_t dram_period_ps);
void dram_set_oesync_ck(int32_t mck_ck);
void dram_set_oesync_dqs(int32_t mck_dqs);
void dram_set_oesync_dq(int32_t mck_dq);
void dram_set_wrlvl_dqs(int32_t pi_dqs);
void dram_set_wrlvl_dq(int32_t pi_dq);
void dram_set_wrlvl(int32_t pi_dqs, int32_t pi_dq);
void dram_odt_alwayson(void);




#ifdef  __cplusplus
}
#endif


#endif //#ifndef RTL8195BHP_DRAM_H


