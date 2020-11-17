/**************************************************************************//**
 * @file      rtl8195bhp_psram_ctrl_type.h
 * @brief
 * @version   V1.00
 * @date      2017-12-8 18:19:4
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

#ifndef _RTL8195BHP_PSRAM_CTRL_TYPE_H_
#define _RTL8195BHP_PSRAM_CTRL_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_PSRAM_CTRL_REG_TYPE

/**
 * @addtogroup hs_hal_psram_ctrl_reg PSRAM_CTRL Registers.
 * @ingroup hs_hal_psram
 * @{
 */

/**
  \brief Union type to access psram_ctrl_ccr (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) Configuration Control Register                             */

  struct {
    __IOM uint32_t init       : 1;            /*!< [0..0] Start to issue PSRAM initialization sequence                       */

    __IM  uint32_t            : 2;
    __IOM uint32_t dpin       : 1;            /*!< [3..3] Start to set PSRAM command function.                               */

    __IM  uint32_t            : 4;
    __IOM uint32_t flush_fifo : 1;            /*!< [8..8] Flush all FIFO in PSRAM_CTRL                                       */
  } b;                                        /*!< bit fields for psram_ctrl_ccr */
} psram_ctrl_ccr_t, *ppsram_ctrl_ccr_t;

/**
  \brief Union type to access psram_ctrl_dcr (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) DRAM Configuration Control Register                        */

  struct {
    __IOM uint32_t dq32       : 1;            /*!< [0..0] Setting the architecture is 2 x 16-Bit PSRAM. It is valid
                                                   to set if the hardware architecture is valid configuration.               */
    __IM  uint32_t            : 1;
    __IOM uint32_t async_mode : 1;            /*!< [2..2] Indicate the PSRAM work at Asynchronous mode or Synchronous
                                                   mode                                                                      */
    __IOM uint32_t ddr_mode   : 1;            /*!< [3..3] Indicate the PSRAM work at DDR mode or SDR mode                    */
    __IOM uint32_t dfi_rate   : 3;            /*!< [6..4] Setting DFI ratio                                                  */
    __IOM uint32_t cre_en     : 1;            /*!< [7..7] Indicate access PSRAM register mode                                */
    __IOM uint32_t clk_en     : 1;            /*!< [8..8] Indicate PSRAM at asynchronous mode clock enable                   */
    __IOM uint32_t suspend_en : 1;            /*!< [9..9] Indicate PSRAM_CTRL support SUSPEND command                        */

    __IM  uint32_t            : 6;
    __IOM uint32_t page_size  : 4;            /*!< [19..16] Indicate the target PSRAM page size                              */
    __IOM uint32_t aadmux     : 1;            /*!< [20..20] Indicate the target PSRAM is AADMUX type or ADMUX or
                                                   normal type                                                               */
  } b;                                        /*!< bit fields for psram_ctrl_dcr */
} psram_ctrl_dcr_t, *ppsram_ctrl_dcr_t;

/**
  \brief Union type to access psram_ctrl_iocr0 (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) I/O Configuration Control Register 0                       */

  struct {
    __IOM uint32_t dfi_cs_wr_dly : 4;         /*!< [3..0] Setting the latency contrast between PHY read data enable
                                                   path latency and PHY command path latency.                                */
    __IOM uint32_t dfi_cs_rd_dly : 4;         /*!< [7..4] Setting the latency contrast between PHY write data path
                                                   latency and PHY command path latency.                                     */
    __IOM uint32_t rd_pipe    : 4;            /*!< [11..8] Setting the extra delay latency of PHY latency for SDR
                                                   mode read data.                                                           */
    __IOM uint32_t tphy_wrdata : 5;           /*!< [16..12] Setting the delay latency from DFI write command to
                                                   DFI write data.                                                           */
    __IM  uint32_t            : 3;
    __IOM uint32_t tphy_rddata_en : 5;        /*!< [24..20] Setting the delay latency from DFI read command to
                                                   dfi_rddata_en signal.                                                     */
    __IOM uint32_t dfi_path_dly : 5;          /*!< [29..25] Setting the delay latency DFI command path latency
                                                   add dfi_psram_wait signal path latency.                                   */
  } b;                                        /*!< bit fields for psram_ctrl_iocr0 */
} psram_ctrl_iocr0_t, *ppsram_ctrl_iocr0_t;

/**
  \brief Union type to access psram_ctrl_csr (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) Controller Status Register                                 */

  struct {
    __IM  uint32_t            : 8;
    __IOM uint32_t mem_idle   : 1;            /*!< [8..8] Disable memory access state                                        */

    __IM  uint32_t            : 8;
    __IOM uint32_t dpin_mode  : 2;            /*!< [18..17] DPIN mode decode                                                 */
  } b;                                        /*!< bit fields for psram_ctrl_csr */
} psram_ctrl_csr_t, *ppsram_ctrl_csr_t;

/**
  \brief Union type to access psram_ctrl_drr (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) DRAM Refresh Control Register                              */

  struct {
    __IOM uint32_t tcph       : 4;            /*!< [3..0] PSRAM CE# pin HIGH cycles between subsequent command               */
    __IOM uint32_t tcem       : 11;           /*!< [14..4] Maximum average Refresh commands delay cycles. Every
                                                   tCEM a Refresh opportunity must be provided                               */
    __IOM uint32_t tpu        : 7;            /*!< [21..15] For PSRAM initiation flow, it has to wait tPU                    */
  } b;                                        /*!< bit fields for psram_ctrl_drr */
} psram_ctrl_drr_t, *ppsram_ctrl_drr_t;

/**
  \brief Union type to access psram_ctrl_tpr0 (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) DRAM Timing Parameter Register 0                           */

  struct {
    __IOM uint32_t trc        : 6;            /*!< [5..0] PSRAM asynchronous Read operation Read cycle time.                 */
    __IOM uint32_t twc        : 6;            /*!< [11..6] PSRAM asynchronous Write operation Write cycle time.              */
    __IOM uint32_t twph       : 3;            /*!< [14..12] PSRAM asynchronous Write operation Write pulse width
                                                   HIGH.                                                                     */
    __IOM uint32_t twp        : 5;            /*!< [19..15] PSRAM asynchronous Write operation Write pulse width.            */
    __IOM uint32_t toe        : 4;            /*!< [23..20] PSPAM asynchronous Read operation output enable to
                                                   valid output                                                              */
  } b;                                        /*!< bit fields for psram_ctrl_tpr0 */
} psram_ctrl_tpr0_t, *ppsram_ctrl_tpr0_t;

/**
  \brief Union type to access psram_ctrl_tpr1 (@ 0x00000018).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000018) DRAM Timing Parameter Register 1                           */

  struct {
    __IOM uint32_t tcvs       : 2;            /*!< [1..0] PSRAM asynchronous operation CE# pin LOW to ADV# pin
                                                   HIGH.                                                                     */
    __IOM uint32_t tavh       : 2;            /*!< [3..2] PSRAM asynchronous operation Address hold from ADV# pin
                                                   HIGH.                                                                     */
    __IOM uint32_t tvp        : 2;            /*!< [5..4] PSRAM asynchronous operation ADV# pin pulse width LOW.             */
    __IOM uint32_t tos        : 2;            /*!< [7..6] PSRAM asynchronous operation OE# pin HIGH setup time
                                                   to ADV# pin LOW.                                                          */
    __IOM uint32_t toh        : 2;            /*!< [9..8] PSRAM asynchronous Read operation OE# pin hold after
                                                   ADV# pin HIGH.                                                            */
  } b;                                        /*!< bit fields for psram_ctrl_tpr1 */
} psram_ctrl_tpr1_t, *ppsram_ctrl_tpr1_t;

/**
  \brief Union type to access psram_ctrl_cmd_dpin (@ 0x00000028).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000028) Command Data Pin Register                                  */

  struct {
    __IOM uint32_t addr       : 24;           /*!< [23..0] If DPIN operate at Write/Read data mode, indicate the
                                                   value of address.                                                         */
  } b;                                        /*!< bit fields for psram_ctrl_cmd_dpin */
} psram_ctrl_cmd_dpin_t, *ppsram_ctrl_cmd_dpin_t;

/**
  \brief Union type to access psram_ctrl_mr_info (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) Mode Latency Information Register                          */

  struct {
    __IOM uint32_t wl         : 5;            /*!< [4..0] Indicate PSRAM write latency counter.                              */
    __IOM uint32_t rl         : 5;            /*!< [9..5] Indicate PSRAM write latency counter.                              */
  } b;                                        /*!< bit fields for psram_ctrl_mr_info */
} psram_ctrl_mr_info_t, *ppsram_ctrl_mr_info_t;

/**
  \brief Union type to access psram_ctrl_mr0 (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) DRAM Mode Register 0                                       */

  struct {
    __IOM uint32_t mr0        : 32;           /*!< [31..0] Setting the value to PSRAM BCR register in initialization
                                                   flow.                                                                     */
  } b;                                        /*!< bit fields for psram_ctrl_mr0 */
} psram_ctrl_mr0_t, *ppsram_ctrl_mr0_t;

/**
  \brief Union type to access psram_ctrl_mr1 (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) DRAM Mode Register 1                                       */

  struct {
    __IOM uint32_t mr1        : 32;           /*!< [31..0] Setting the value to PSRAM RCR register in initialization
                                                   flow.                                                                     */
  } b;                                        /*!< bit fields for psram_ctrl_mr1 */
} psram_ctrl_mr1_t, *ppsram_ctrl_mr1_t;

/**
  \brief Union type to access psram_ctrl_iocr1 (@ 0x00000050).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000050) I/O Configuration Control Register 1                       */

  struct {
    __IOM uint32_t dfi_cke_wr_dly : 4;        /*!< [3..0] Setting the delay latency from SUSPEND command to dfi_psram_ck_en
                                                   signal during WRITE transaction.                                          */
    __IOM uint32_t dfi_cke_rd_dly : 4;        /*!< [7..4] Setting the delay latency from SUSPEND command to dfi_psram_ck_en
                                                   signal during READ transaction.                                           */
    __IOM uint32_t dfi_cke_cmd_dly : 4;       /*!< [11..8] Setting the delay latency from SUSPEND command to dfi_psram_ck_en
                                                   signal during access PSRAM register.                                      */
  } b;                                        /*!< bit fields for psram_ctrl_iocr1 */
} psram_ctrl_iocr1_t, *ppsram_ctrl_iocr1_t;

/**
  \brief Union type to access psram_ctrl_dpdri (@ 0x00000060).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000060) DPIN data index Register                                   */

  struct {
    __IOM uint32_t dpin_data_index : 4;       /*!< [3..0] Indicate select which DPIN DATA register                           */
  } b;                                        /*!< bit fields for psram_ctrl_dpdri */
} psram_ctrl_dpdri_t, *ppsram_ctrl_dpdri_t;

/**
  \brief Union type to access psram_ctrl_dpdr (@ 0x00000064).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000064) DPIN data Register                                         */

  struct {
    __IOM uint32_t dpin_data  : 32;           /*!< [31..0] Indicate the data which will be written to PSRAM or
                                                   the data read from PSRAM                                                  */
  } b;                                        /*!< bit fields for psram_ctrl_dpdr */
} psram_ctrl_dpdr_t, *ppsram_ctrl_dpdr_t;

/**
  \brief Union type to access psram_ctrl_pctl_svn_id (@ 0x000000F4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000F4) PCTL Version ID Register                                   */

  struct {
    __IOM uint32_t release_date : 16;         /*!< [15..0] Indicate the IP release date for the particular project           */
    __IOM uint32_t svn_num    : 16;           /*!< [31..16] Indicate the SVN number of the released RTL code                 */
  } b;                                        /*!< bit fields for psram_ctrl_pctl_svn_id */
} psram_ctrl_pctl_svn_id_t, *ppsram_ctrl_pctl_svn_id_t;

/**
  \brief Union type to access psram_ctrl_pctl_idr (@ 0x000000F8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000F8) PCTL Identification Register                               */

  struct {
    __IOM uint32_t cr_pctl_def : 16;          /*!< [15..0] If user ties this field at input port tie, it indicates
                                                   user definition. Or it only shows one main support DRAM
                                                   type.                                                                     */
    __IOM uint32_t cr_ver     : 16;           /*!< [31..16] The control register version number                              */
  } b;                                        /*!< bit fields for psram_ctrl_pctl_idr */
} psram_ctrl_pctl_idr_t, *ppsram_ctrl_pctl_idr_t;

/** @} */ /* End of group hs_hal_psram_ctrl_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_PSRAM_CTRL_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_PSRAM_CTRL_TYPE_H_

