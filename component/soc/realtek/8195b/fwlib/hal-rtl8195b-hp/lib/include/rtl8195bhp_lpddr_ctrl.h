/**************************************************************************//**
* @file         rtl819bhp_lpddr_ctrl.h
* @brief       The fundamental definition for RTL8195B HP LPDDR Controller module.
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


#ifndef RTL8195BHP_LPDDR_CTRL_H
#define RTL8195BHP_LPDDR_CTRL_H

#ifdef __cplusplus
extern "C" {
#endif


/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */



/* =========================================================================================================================== */
/* ================                                        LPDDR_CTRL                                         ================ */
/* =========================================================================================================================== */

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_LPDDR_CTRL_REG_TYPE


/**
  * @brief LPDDR Controller (LPDDR_CTRL)
  */

typedef struct {                                /*!< (@ 0x40601000) LPDDR_CTRL Structure                                       */

  union {
    __IOM uint32_t ccr;                         /*!< (@ 0x00000000) Configuration Control Register                             */

    struct {
      __IOM uint32_t init       : 1;            /*!< [0..0] Start to issue DRAM initialization sequence                        */

      __IM  uint32_t            : 1;
      __IOM uint32_t btt        : 1;            /*!< [2..2] Start to run BIST function.                                        */
      __IOM uint32_t dpit       : 1;            /*!< [3..3] Start to set DRAM pins function. According to CMD_DPIN
                                                     register setting to the related DRAM command pins one DRAM
                                                     clock cycle.                                                              */
      __IM  uint32_t            : 4;
      __IOM uint32_t flush_fifo : 1;            /*!< [8..8] Flush all FIFO in RXI310_DRAM_CTRL                                 */

      __IM  uint32_t            : 22;
      __OM  uint32_t cr_update  : 1;            /*!< [31..31] Indicate to update the related control register to
                                                     timing counter register: TPR0, TPR1, TPR2, TPR3 without
                                                     any implementation (DPIT, BTT, INIT).                                     */
    } ccr_b;
  } ;

  union {
    __IOM uint32_t dcr;                         /*!< (@ 0x00000004) DRAM Configuration Control Register                        */

    struct {
      __IOM uint32_t ddr        : 3;            /*!< [2..0] Indicate the target DRAM type                                      */
      __IOM uint32_t sdr        : 1;            /*!< [3..3] Indicate the target DRAM type                                      */
      __IOM uint32_t dq_32      : 1;            /*!< [4..4] Setting the DDR architecture is 2 x 16-Bit DRAM. It is
                                                     valid to set if the hardware architecture is valid configuration.         */
      __IOM uint32_t half_dq    : 1;            /*!< [5..5] Indicate only using 16-bit DRAM on the DQ_32 hardware
                                                     architecture.                                                             */
      __IOM uint32_t hybr_dq    : 1;            /*!< [6..6] Indicate access DRAM DQ_32 hardware architecture in DQx16-bit
                                                     or DQx32-bit according to CR_MISC:HYBR_SIZE .                             */
      __IM  uint32_t            : 1;
      __IOM uint32_t dfi_rate   : 3;            /*!< [10..8] Setting DFI ratio.                                                */

      __IM  uint32_t            : 1;
      __IOM uint32_t rank2      : 1;            /*!< [12..12] Set DRAM RANK2 architecture implement.                           */

      __IM  uint32_t            : 4;
      __IOM uint32_t dbi        : 1;            /*!< [17..17] Setting READ DBI function for DDR4                               */
      __IOM uint32_t par        : 1;            /*!< [18..18] Setting PAR function for DDR4                                    */
      __IOM uint32_t gear_down  : 1;            /*!< [19..19] Setting GEAR_DOWN function for DDR4                              */

      __IM  uint32_t            : 1;
      __IOM uint32_t bg2        : 1;            /*!< [21..21] Support BankGroup2 function for DDR4                             */

      __IM  uint32_t            : 8;
      __IOM uint32_t zqc        : 1;            /*!< [30..30] Issue DRAM ZQCS/ZQCL command after serial Auto-refresh
                                                     command implementation. This function should set with CR_DRR:ZQCL_INV
                                                     and CR_TPR2:ZQCS_INV                                                      */
    } dcr_b;
  } ;

  union {
    __IOM uint32_t iocr;                        /*!< (@ 0x00000008) I/0 Configuration Control Register                         */

    struct {
      __IOM uint32_t odt_2pins  : 1;            /*!< [0..0] Indicate to connect 2 ODT_PINS.                                    */

      __IM  uint32_t            : 1;
      __IOM uint32_t stc_cke    : 1;            /*!< [2..2] Setting DRAM static CKE function. Else DRAM_CTRL supports
                                                     dynamic CKE function.                                                     */
      __IOM uint32_t stc_odt    : 1;            /*!< [3..3] Setting DRAM static ODT function. Else DRAM_CTRL supports
                                                     dynamic ODT function.                                                     */
      __IOM uint32_t two_n_pre_en : 1;          /*!< [4..4] Setting DRAM: command pins = keeps 2t but DRAM:CS keeps
                                                     only 1t*.                                                                 */
      __IOM uint32_t trtw_2t_dis : 1;           /*!< [5..5] Setting DRAM: read -> write command interval time > 2t*            */
      __IOM uint32_t half_cs_n  : 1;            /*!< [6..6] Setting DRAM:CS only keeps half cycle* at LPDDR2/3                 */

      __IM  uint32_t            : 1;
      __IOM uint32_t rd_pipe    : 4;            /*!< [11..8] Setting the extra delay latency of CAS on SDR. If it
                                                     works on SDR, the smallest value is 0.                                    */
      __IOM uint32_t tphy_wrdata : 5;           /*!< [16..12] Setting the delay latency from dfi_wrdata_en signal
                                                     to dfi_wddata. If it works on DDR, the smallest value is
                                                     1.                                                                        */
      __IOM uint32_t tphy_wlat  : 3;            /*!< [19..17] Setting the delay latency from DFI write command to
                                                     dfi_wrdata_en signal. If it works on DDR, the smallest
                                                     value is 0.                                                               */
      __IOM uint32_t tphy_rddata_en : 5;        /*!< [24..20] Setting the delay latency from DFI read command to
                                                     dfi_rddata_en signal. If it works on DDR, the smallest
                                                     value is 1.                                                               */
      __IM  uint32_t            : 5;
      __IOM uint32_t fpga_lp    : 1;            /*!< [30..30] Enable to loopback mode form output DFI ports to input
                                                     DFI ports on FPGA.                                                        */
      __IOM uint32_t fpga_dfi   : 1;            /*!< [31..31] Enable to connect external PHY on FPGA                           */
    } iocr_b;
  } ;

  union {
    __IOM uint32_t csr;                         /*!< (@ 0x0000000C) Controller Status Register                                 */

    struct {
      __IM  uint32_t            : 8;
      __IOM uint32_t mem_idle   : 1;            /*!< [8..8] Disable memory access state                                        */

      __IM  uint32_t            : 1;
      __IOM uint32_t bstc_idle  : 1;            /*!< [10..10] Disable BSTC function state                                      */
    } csr_b;
  } ;

  union {
    __IOM uint32_t drr;                         /*!< (@ 0x00000010) DRAM Refresh Control Register                              */

    struct {
      __IOM uint32_t trfc       : 8;            /*!< [7..0] Refresh to Active or Refresh commands delay cycles                 */
      __IOM uint32_t tref       : 16;           /*!< [23..8] Maximum average Refresh commands delay cycles. tREF[4:0]
                                                     is also used to indicate the early cycles to inform RTK_PHY
                                                     before ZQC command implementation.                                        */
      __IOM uint32_t ref_num    : 4;            /*!< [27..24] Setting the number of Refresh commands to issue in
                                                     between two surrounding Refresh commands                                  */
      __IOM uint32_t ref_dis    : 1;            /*!< [28..28] Disable RXI310_DRAM issues Refresh command to DRAM.              */
      __IOM uint32_t zqcl_inv   : 3;            /*!< [31..29] It is used for indicate ZQCL implementation interval
                                                     time after ZQCS implementation times.                                     */
    } drr_b;
  } ;

  union {
    __IOM uint32_t tpr0;                        /*!< (@ 0x00000014) DRAM Timing Parameter Register 0                           */

    struct {
      __IOM uint32_t trp        : 4;            /*!< [3..0] Precharge command cycles                                           */
      __IOM uint32_t tras       : 5;            /*!< [8..4] Active to Precharge command delay cycles                           */
      __IOM uint32_t twr        : 4;            /*!< [12..9] Write Recovery delay cycles                                       */
      __IOM uint32_t trtp       : 4;            /*!< [16..13] Read to Precharge command delay cycles.                          */
      __IOM uint32_t tcke       : 4;            /*!< [20..17] max(tCKE, tXP) cycles                                            */

      __IM  uint32_t            : 3;
      __IOM uint32_t tzqcs      : 8;            /*!< [31..24] ZQCS command cycles                                              */
    } tpr0_b;
  } ;

  union {
    __IOM uint32_t tpr1;                        /*!< (@ 0x00000018) DRAM Timing Parameter Register 1                           */

    struct {
      __IOM uint32_t trrd       : 4;            /*!< [3..0] Active to Active command delay cycles (in the different
                                                     BANK)                                                                     */
      __IOM uint32_t trc        : 6;            /*!< [9..4] Active to Active or Refresh command delay cycles(in the
                                                     same BANK).                                                               */
      __IOM uint32_t trcd       : 4;            /*!< [13..10] Active to internal Read or Write delay cycles                    */
      __IOM uint32_t tccd       : 3;            /*!< [16..14] CAS# to CAS# command delay cycles                                */
      __IOM uint32_t twtr       : 3;            /*!< [19..17] Delay cycles start of internal Write transaction to
                                                     internal read command                                                     */
      __IOM uint32_t trtw       : 4;            /*!< [23..20] Read to Write command delay cycles.                              */
      __IOM uint32_t tfaw       : 5;            /*!< [28..24] Four active window cycles                                        */
    } tpr1_b;
  } ;

  union {
    __IOM uint32_t tpr2;                        /*!< (@ 0x0000001C) DRAM Timing Parameter Register 2                           */

    struct {
      __IOM uint32_t int_ref_num_or_zqc_inv : 4;/*!< [3..0] Set the number of Refresh command to issue in DRAM(SDR/DDR1/DDR2)
                                                     initialization flow. After DRAM initial flow, it is also
                                                     used for indicate ZQCS implementation interval times after
                                                     serial AUTO_Refresh implementation times.                                 */
      __IOM uint32_t tmrd       : 4;            /*!< [7..4] Mode register operations delay cycles. Setting the maximum
                                                     value between Mode register set command delay cycles and
                                                     Mode Register set command update delay cycles.                            */
      __IOM uint32_t tns        : 4;            /*!< [11..8] If non-dfined CR_INTI_RMBIT configuration. For different
                                                     DRAM initiation flow, it has to wait tNS ns. It can set
                                                     this register. The wait time is 2 (tUS<<7) cycles.                        */
      __IOM uint32_t tus        : 10;           /*!< [21..12] If non-dfined CR_INTI_RMBIT configuration. For different
                                                     DRAM initiation flow, it has to wait tUS ns. It can set
                                                     this register. The wait time is 2 (tUS<<10) cycles.                       */
      __IOM uint32_t rst_tus    : 10;           /*!< [31..22] If non-dfined CR_INTI_RMBIT configuration. For DRAM
                                                     initiation flow, RESET_n signal would be set high until
                                                     2 (RST_tUS<<10) cycles.                                                   */
    } tpr2_b;
  } ;

  union {
    __IOM uint32_t tpr3;                        /*!< (@ 0x00000020) DRAM Timing Parameter Register 3                           */

    struct {
      __IM  uint32_t            : 4;
      __IOM uint32_t dpin_cmd_lat : 3;          /*!< [6..4] Set CS_N pin delay cycles with others command pins.                */

      __IM  uint32_t            : 7;
      __IOM uint32_t tccd_s     : 3;            /*!< [16..14] CAS# to CAS# command delay cycles at different bank
                                                     group in DDR4.                                                            */
      __IOM uint32_t twtr_s     : 3;            /*!< [19..17] Delay cycles start of internal Write transaction to
                                                     internal read command at different bank group in DDR4.                    */
      __IM  uint32_t            : 9;
      __IOM uint32_t tccd_r     : 3;            /*!< [31..29] tCCD delay cycles for different rank DRAM die.                   */
    } tpr3_b;
  } ;
  __IM  uint32_t  RESERVED;

  union {
    __IOM uint32_t cmd_dpin;                    /*!< (@ 0x00000028) Command Data Pin Register                                  */

    struct {
      __IOM uint32_t addr       : 17;           /*!< [16..0] Set the value of ADDR pins                                        */
      __IOM uint32_t ba         : 4;            /*!< [20..17] Set the value of BA pins                                         */
      __IOM uint32_t we_n       : 1;            /*!< [21..21] Set the value of WE_N pin                                        */
      __IOM uint32_t cas_n      : 1;            /*!< [22..22] Set the value of CAS_N pin                                       */
      __IOM uint32_t ras_n      : 1;            /*!< [23..23] Set the value of RAS_N pin                                       */
      __IOM uint32_t cs_n       : 1;            /*!< [24..24] Set the value of CS_N pin                                        */
      __IOM uint32_t act_n      : 1;            /*!< [25..25] Set the value of ACT_N pin in DDR4                               */
      __IOM uint32_t parity     : 1;            /*!< [26..26] Set the value of PARITY pin in DDR4                              */

      __IM  uint32_t            : 4;
      __IOM uint32_t cs_n_1     : 1;            /*!< [31..31] Set the value of CS_1 pin if parameter: CS_BITS>1                */
    } cmd_dpin_b;
  } ;

  union {
    __IOM uint32_t tie_dpin;                    /*!< (@ 0x0000002C) Tied Data Pin Register                                     */

    struct {
      __IOM uint32_t rst_n      : 1;            /*!< [0..0] Set the value of RST_N pin                                         */
      __IOM uint32_t cke        : 1;            /*!< [1..1] Set the value of CKE pin                                           */
      __IOM uint32_t odt        : 1;            /*!< [2..2] Set the value of ODT pin                                           */
      __IOM uint32_t ten        : 1;            /*!< [3..3] ten                                                                */
      __IOM uint32_t alert_n    : 1;            /*!< [4..4] alert_n                                                            */

      __IM  uint32_t            : 24;
      __IOM uint32_t rst_n_1    : 1;            /*!< [29..29] Set the value of RST_N_1 pin if parameter: RST_BITS>1            */
      __IOM uint32_t cke_1      : 1;            /*!< [30..30] Set the value of CKE_1 pin if parameter: CKE_BITS>1              */
      __IOM uint32_t odt_1      : 1;            /*!< [31..31] Set the value of ODT_1 pin if parameter: ODT_BITS>1              */
    } tie_dpin_b;
  } ;

  union {
    __IOM uint32_t mr_info;                     /*!< (@ 0x00000030) Mode Latency Information Register                          */

    struct {
      __IOM uint32_t wr_lat     : 5;            /*!< [4..0] It is indicate DRAM write data latency                             */
      __IOM uint32_t rd_lat     : 5;            /*!< [9..5] It is indicate DRAM read data latency.                             */
      __IOM uint32_t add_lat    : 5;            /*!< [14..10] It is indicate DRAM additive latency.                            */
      __IOM uint32_t tdqsck_max : 3;            /*!< [17..15] It is indicate tDQSCK_MAX cycle value for LPDDR23.               */
    } mr_info_b;
  } ;

  union {
    __IOM uint32_t mr0;                         /*!< (@ 0x00000034) DRAM Mode Register 0                                       */

    struct {
      __IOM uint32_t mr0        : 32;           /*!< [31..0] Setting the value to Mode register MR0 in DRAM initialization
                                                     flow.                                                                     */
    } mr0_b;
  } ;

  union {
    __IOM uint32_t mr1;                         /*!< (@ 0x00000038) DRAM Mode Register 1                                       */

    struct {
      __IOM uint32_t mr1        : 32;           /*!< [31..0] Setting the value to Mode register EMR1 in DRAM initialization
                                                     flow.                                                                     */
    } mr1_b;
  } ;

  union {
    __OM  uint32_t mr2;                         /*!< (@ 0x0000003C) DRAM Mode Register 2                                       */

    struct {
      __OM  uint32_t mr2        : 32;           /*!< [31..0] Setting the value to Mode register EMR2 in DRAM initialization
                                                     flow.                                                                     */
    } mr2_b;
  } ;
  __IM  uint32_t  RESERVED1[36];

  union {
    __IOM uint32_t bcr;                         /*!< (@ 0x000000D0) BSTC Control Register                                      */

    struct {
      __IOM uint32_t stop       : 1;            /*!< [0..0] Disable to run BSTC hardware function                              */
      __IOM uint32_t cmp        : 1;            /*!< [1..1] Enable compare mode. RXI310_DRAM would compare read data
                                                     form DRAM with the expected data in BSTC_RG_SRAM.                         */
      __IOM uint32_t loop       : 1;            /*!< [2..2] Enable loop mode. RXI310_DRAM repeats to implement BSTC
                                                     function for overnight testing                                            */
      __IOM uint32_t dis_msk    : 1;            /*!< [3..3] Disable using BSTC_MSK_SRAM. RXI310_DRAM would write
                                                     full data to DRAM without masking function.                               */
      __IOM uint32_t at_err_stop : 1;           /*!< [4..4] RXI310_DRAM would stop the BSTC function implementation
                                                     if BSTC_RD and BSTC_RG compare error data automatically.
                                                     To enable this function it also must enable the loop mode
                                                     and compare mode (BCR[2:1]).                                              */
      __IOM uint32_t crr        : 1;            /*!< [5..5] Set to clean CR_BER and CR_BST:{ERR_CNT, ERR_FST_TH}
                                                     registers                                                                 */
      __IM  uint32_t            : 2;
      __IOM uint32_t fus_cmd    : 1;            /*!< [8..8] Flush BSTC_CMD_SRAM data                                           */
      __IOM uint32_t fus_wd     : 1;            /*!< [9..9] Flush BSTC_WD_SRAM data                                            */
      __IOM uint32_t fus_rg     : 1;            /*!< [10..10] Flush BSTC_RG_SRAM data                                          */
      __IOM uint32_t fus_rd     : 1;            /*!< [11..11] Flush BSTC_RD_SRAM data.                                         */
      __IOM uint32_t reload_sram : 3;           /*!< [14..12] RELOAD_SRAM[2]: Reload to keep the previous BSTC RG
                                                     SRAM level RELOAD_SRAM[1]: Reload to keep the previous
                                                     BSTC WD SRAM level RELOAD_SRAM[0]: Reload to keep the previous
                                                     BSTC CMD SRAM level                                                       */
      __IM  uint32_t            : 1;
      __IOM uint32_t rd_ex_cnt  : 14;           /*!< [29..16] Set the expected word number of BSTC_RD_SRAM.                    */
    } bcr_b;
  } ;

  union {
    __IOM uint32_t bct;                         /*!< (@ 0x000000D4) BSTC compare loop counter register                         */

    struct {
      __IOM uint32_t loop_cnt   : 16;           /*!< [15..0] If set LOOP_CNT >0 and enable CR_BCR:LOOP, BSTC test
                                                     patterns would be tested in LOOP_CNT times.                               */
    } bct_b;
  } ;

  union {
    __IOM uint32_t bcm;                         /*!< (@ 0x000000D8) BSTC compare bit mask Register                             */

    struct {
      __IOM uint32_t cmp_mbit   : 32;           /*!< [31..0] It is used to mask data bit to compare in auto compare
                                                     function.                                                                 */
    } bcm_b;
  } ;

  union {
    __IOM uint32_t bst;                         /*!< (@ 0x000000DC) BSTC Status Register                                       */

    struct {
      __IOM uint32_t err_fst_th : 14;           /*!< [13..0] Indicate the address of the first error data in the
                                                     BSTC_RD_SRAM. It can clear by CR_BCR:CRR.                                 */
      __IM  uint32_t            : 1;
      __IOM uint32_t rd_in_st   : 1;            /*!< [15..15] Indicate RXI310_DRAM had received read data from DRAM.
                                                     It can clear by BSTC_START function.                                      */
      __IOM uint32_t err_cnt    : 16;           /*!< [31..16] Indicate the entry number of the error read data if
                                                     compare mode is setting. It can clear by CR_BCR:CRR.                      */
    } bst_b;
  } ;

  union {
    __IOM uint32_t bsram0;                      /*!< (@ 0x000000E0) BSTC SRAM Status Register 0                                */

    struct {
      __IOM uint32_t cmd_cnt    : 12;           /*!< [11..0] Indicate the word counts of the data in the command
                                                     SRAM (CMD_SRAM)                                                           */
      __IM  uint32_t            : 4;
      __IOM uint32_t wd_cnt     : 14;           /*!< [29..16] Indicate the word counts of the data in the write data
                                                     SRAM (WD_SRAM)                                                            */
    } bsram0_b;
  } ;

  union {
    __IOM uint32_t bsram1;                      /*!< (@ 0x000000E4) BSTC SRAM Status Register 1                                */

    struct {
      __IOM uint32_t rg_cnt     : 15;           /*!< [14..0] Indicate the word counts of the data in the golden data
                                                     SRAM (RG_SRAM)                                                            */
      __IM  uint32_t            : 1;
      __IOM uint32_t rd_cnt     : 14;           /*!< [29..16] Indicate the word counts of the data in the read data
                                                     (RD_SRAM).                                                                */
    } bsram1_b;
  } ;

  union {
    __IOM uint32_t ber;                         /*!< (@ 0x000000E8) BSTC Error Bit Register                                    */

    struct {
      __IOM uint32_t err_bit    : 32;           /*!< [31..0] Indicate which bit ever had occurred error in auto compare
                                                     function.                                                                 */
    } ber_b;
  } ;
  __IM  uint32_t  RESERVED2[2];

  union {
    __IOM uint32_t pctl_svn_id;                 /*!< (@ 0x000000F4) PCTL Version ID Register                                   */

    struct {
      __IOM uint32_t release_date : 16;         /*!< [15..0] Indicate the IP release date for the particular project           */
      __IOM uint32_t svn_num    : 16;           /*!< [31..16] Indicate the SVN number of the released RTL code                 */
    } pctl_svn_id_b;
  } ;

  union {
    __IOM uint32_t pctl_idr;                    /*!< (@ 0x000000F8) PCTL Identification Register                               */

    struct {
      __IOM uint32_t cr_pctl_def : 16;          /*!< [15..0] If user ties this field at input port tie, it indicates
                                                     user definition. Or it only shows one main support DRAM
                                                     type.                                                                     */
      __IOM uint32_t cr_ver     : 16;           /*!< [31..16] The control register version number                              */
    } pctl_idr_b;
  } ;
  __IM  uint32_t  RESERVED3[74];

  union {
    __IOM uint32_t misc;                        /*!< (@ 0x00000224) Memory Information Setting Control Register                */

    struct {
      __IOM uint32_t page_size  : 4;            /*!< [3..0] Indicate the target DRAM page size (unit: Byte)                    */
      __IOM uint32_t bank_size  : 2;            /*!< [5..4] Indicate the target DRAM bank size                                 */
      __IOM uint32_t bst_size   : 2;            /*!< [7..6] Indicate RXI310_DRAM to issue DRAM Burst size                      */

      __IM  uint32_t            : 2;
      __IOM uint32_t hybr_size  : 2;            /*!< [11..10] Indicate the target DRAM page size (unit: Byte)                  */
    } misc_b;
  } ;
  __IM  uint32_t  RESERVED4[30];

  union {
    __IOM uint32_t ocp_wrap_idr;                /*!< (@ 0x000002A0) OCP_WRAP ID number Register                                */

    struct {
      __IOM uint32_t cr_wrap_def : 16;          /*!< [15..0] Indicate RXI310_DRAM number                                       */
      __IOM uint32_t cr_wrap_idr : 16;          /*!< [31..16] Indicate RXI310_OCP_WRAP ID number.                              */
    } ocp_wrap_idr_b;
  } ;

  union {
    __IOM uint32_t ocp_wrap_version;            /*!< (@ 0x000002A4) OCP_WRAP version numbers                                   */

    struct {
      __IOM uint32_t release_date : 16;         /*!< [15..0] Indicate the IP release date for the particular project           */
      __IOM uint32_t svn_num    : 16;           /*!< [31..16] Indicate the SVN number of the release RTL code                  */
    } ocp_wrap_version_b;
  } ;
} LPDDR_CTRL_Type;                              /*!< Size = 680 (0x2a8)                                                        */

/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_LPDDR_CTRL_REG_TYPE */

/** @} */ /* End of group Device_Peripheral_peripherals */


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

#define LPDDR_CTRL_BASE             0x40601000UL

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */


/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define LPDDR_CTRL                  ((LPDDR_CTRL_Type *)        LPDDR_CTRL_BASE)

/** @} */ /* End of group Device_Peripheral_declaration */


#ifdef __cplusplus
}
#endif

#endif /* RTL8195BHP_LPDDR_CTRL_H */




