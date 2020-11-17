/**************************************************************************//**
 * @file      rtl8195bhp_syson_type.h
 * @brief
 * @version   V1.00
 * @date      2018-2-14 17:3:35
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

#ifndef _RTL8195BHP_SYSON_SYSON_TYPE_H_
#define _RTL8195BHP_SYSON_SYSON_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_SYSON_REG_TYPE

/**
 * @addtogroup hs_hal_syson_reg SYSON Registers.
 * @ingroup hs_hal_syson
 * @{
 */

/**
  \brief Union type to access syson_sys_pwr_ctrl (@ 0x00000000).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000000) System Power Control Register                              */
  
  struct {
    __IOM uint16_t soc_spc_en : 1;            /*!< [0..0] 1:enable HS SOC domain small power cut                             */
    __IOM uint16_t soc_lpc_en : 1;            /*!< [1..1] 1:enable HS SOC domain large power cut                             */
    __IOM uint16_t video_spc_en : 1;          /*!< [2..2] 1:enable video domain small power cut                              */
    __IOM uint16_t video_lpc_en : 1;          /*!< [3..3] 1:enable video domain large power cut                              */
    __IOM uint16_t wlon_spc_en : 1;           /*!< [4..4] 1:enable WLON domain small power cut                               */
    __IOM uint16_t wlon_lpc_en : 1;           /*!< [5..5] 1:enable WLON domain large power cut                               */
  } b;                                        /*!< bit fields for syson_sys_pwr_ctrl */
} syson_sys_pwr_ctrl_t, *psyson_sys_pwr_ctrl_t;

/**
  \brief Union type to access syson_sys_iso_ctrl (@ 0x00000002).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000002) System Isolation Control Register                          */
  
  struct {
    __IOM uint16_t sys_iso_hssoc : 1;         /*!< [0..0] 1: isolation HS SoC to HS ON domain; 0: disable isolation          */
    __IOM uint16_t sys_iso_vdo : 1;           /*!< [1..1] 1: isolation Vedio to HS on domain; 0: disable isolation           */
    __IOM uint16_t sys_iso_wl : 1;            /*!< [2..2] 1: isolation WLON to HS on domain; 0: disable isolation            */
  } b;                                        /*!< bit fields for syson_sys_iso_ctrl */
} syson_sys_iso_ctrl_t, *psyson_sys_iso_ctrl_t;

/**
  \brief Union type to access syson_hs_clk_ctrl (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) HS System Clock Control Register                           */
  
  struct {
    __IOM uint32_t clk_eeldr_clk : 1;         /*!< [0..0] 1: enable EE Loader clock; 0: disable EE loader                    */
    __IM  uint32_t            : 1;
    __IOM uint32_t tm9_clk_en : 1;            /*!< [2..2] 1: enable TM9 clock ; 0: reset                                     */
    __IOM uint32_t platform_clk_en : 1;       /*!< [3..3] 1: enable HS platform clock ;                                      */
    __IOM uint32_t vendor_clk_en : 1;         /*!< [4..4] 1: enable HS Vendor clock ;                                        */
    __IOM uint32_t dram_sce_clk_en : 1;       /*!< [5..5] 1: Enable DDR SCE CLK                                              */
    __IOM uint32_t flash_sce_clk_en : 1;      /*!< [6..6] 1: Enable flash SCE CLK                                            */
  } b;                                        /*!< bit fields for syson_hs_clk_ctrl */
} syson_hs_clk_ctrl_t, *psyson_hs_clk_ctrl_t;

/**
  \brief Union type to access syson_sys_func_en (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) HS System Function Enable Control Register                 */
  
  struct {
    __IOM uint32_t hs_fen_eeldr : 1;          /*!< [0..0] 1: enable EE Loader; 0: disable EE loader                          */
    __IM  uint32_t            : 1;
    __IOM uint32_t tm9_en     : 1;            /*!< [2..2] 1: enable TM9 ; 0: reset                                           */
    __IOM uint32_t platform_en : 1;           /*!< [3..3] 1: enable platform                                                 */
    __IOM uint32_t vendor_en  : 1;            /*!< [4..4] 1: enable vendor                                                   */
    __IOM uint32_t dram_sce_en : 1;           /*!< [5..5] 1: Enable DDR SCE                                                  */
    __IOM uint32_t flash_sce_en : 1;          /*!< [6..6] 1: Enable flash SCE                                                */
    __IM  uint32_t            : 9;
    __IOM uint32_t hs_soc_en  : 1;            /*!< [16..16] 1: enable HS SOC domain                                          */
    __IOM uint32_t hs_video_en : 1;           /*!< [17..17] 1: enable video domain                                           */
  } b;                                        /*!< bit fields for syson_sys_func_en */
} syson_sys_func_en_t, *psyson_sys_func_en_t;

/**
  \brief Union type to access syson_hs_platform_mem_ctrl0 (@ 0x00000010).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000010) HS Platform Memory Control Register 0                      */
  
  struct {
    __IOM uint32_t hs_plat_dram_type_sel : 1; /*!< [0..0] DRAM type: 0: LPDDER, 1: PSRAM                                     */
    __IOM uint32_t hs_plat_dram_sce_path_en : 1;/*!< [1..1] DRAM SCE enable: 0: RXI300->DRAM_CTRL (access through),
                                                   1: RXI300 -> DRAM_SCE -> DRAM_CTRL                                        */
    __IOM uint32_t hs_plat_flash_sce_path_en : 1;/*!< [2..2] FLASH SCE enable: 0: RXI300->FLASH_CTRL (access through),
                                                   1: RXI300 -> FLASH_SCE -> FLASH_CTRL                                      */
  } b;                                        /*!< bit fields for syson_hs_platform_mem_ctrl0 */
} syson_hs_platform_mem_ctrl0_t, *psyson_hs_platform_mem_ctrl0_t;

/**
  \brief Union type to access syson_sys_clk_ctrl1 (@ 0x00000014).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000014) System Clock Control Register1                             */
  
  struct {
    __IOM uint32_t syspll_cksl : 1;           /*!< [0..0] divider PLL clock source selection 0: 300MHz 1: 200Mhz             */
    __IM  uint32_t            : 3;
    __IOM uint32_t syspll_dvsl : 4;           /*!< [7..4] PLL clock divider value selection                                  */
    __IOM uint32_t sys_cksl   : 1;            /*!< [8..8] system clock source selection 1: PLL divider out 0: 4M             */
    __IOM uint32_t sys_dven   : 1;            /*!< [9..9] system clock divider enable 1: multiply 0.5 0: bypass              */
  } b;                                        /*!< bit fields for syson_sys_clk_ctrl1 */
} syson_sys_clk_ctrl1_t, *psyson_sys_clk_ctrl1_t;

/**
  \brief Union type to access syson_sys_boot_ctrl (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) System Boot Control Register                               */
  
  struct {
    __IOM uint32_t skip_ls_img_load : 1;      /*!< [0..0] If this bit is set, the HS boot loader will skip the
                                                   LS image loading. This bit is valid only when ls_rom_rdy=1.
                                                   1: skip to load LS image.                                                 */
    __IOM uint32_t ls_rom_rdy : 1;            /*!< [1..1] Indicate the LS ROM code initial done. 1: LS ROM code
                                                   ready.                                                                    */
    __IOM uint32_t debuger_pin_en : 1;        /*!< [2..2] 1: Enable debuger mux                                              */
    __IOM uint32_t debuger_mode_sel : 2;      /*!< [4..3] 00: SWD; 01: JTAG 10: JTAG chain mode                              */
    __IOM uint32_t debuger_pin_sel : 1;       /*!< [5..5] LS CPU backup the debugger pin configuration here, for
                                                   restoring after resume from WDT or power saving. debuger
                                                   is muxed on 00: GPIOE_0~4 01: GPIOC_2~6                                   */
    __IM  uint32_t            : 7;
    __IOM uint32_t lp_aon_wsts_gpio : 1;      /*!< [13..13] 1: Indicate AON GPIO A13 Wakeup event                                  */
    __IM  uint32_t lp_aon_wsts_systim : 1;    /*!< [14..14] 1: 1: Indicate AON SYSTimer Wakeup event                          */
    __IOM uint32_t lp_aon_wsts_rtc : 1;       /*!< [15..15] 1: Indicate RTC Wakeup event                                    */
    __IOM uint32_t lp_aon_wsts_adp : 1;       /*!< [16..16] 1: Indicate Adapter Wakeup event                                       */
    __IOM uint32_t lp_wsts_systim : 1;        /*!< [17..17] 1: Indocate SYSTimer Wakeup event                                  */
    __IM  uint32_t lp_wsts_gtim : 1;          /*!< [18..18] 1: Indicate GTimer0~7 Wakeup system event                          */
    __IM  uint32_t lp_wsts_swrd_ocp : 1;      /*!< [19..19] 1: Indicate DCORE SWR OCP event                                    */
    __IOM uint32_t lp_wsts_bod : 1;           /*!< [20..20] 1: Indicate BOD Wakeup event                                       */
    __IM  uint32_t lp_wsts_gpio : 1;          /*!< [21..21] 1: Indicate GPIO Wakeup event                                      */
    __IM  uint32_t lp_wsts_pwm : 1;           /*!< [22..22] 1: Indicate PWM Wakeup event                                       */
    __IM  uint32_t lp_wsts_wlan : 1;          /*!< [23..23] 1: Indicate WLAN Wakeup event                                      */
    __IM  uint32_t lp_wsts_uart : 1;          /*!< [24..24] 1: Indicate UART Wakeup event                                    */
    __IM  uint32_t lp_wsts_i2c : 1;           /*!< [25..25] 1: Indicate I2C Wakeup event                                     */
    __IM  uint32_t lp_wsts_adc : 1;           /*!< [26..26] 1: Indicate ADC Wakeup event                                     */
    __IM  uint32_t lp_wsts_comp : 1;          /*!< [27..27] 1: Indicate Comparetor Wakeup event                              */
    __IM  uint32_t lp_wsts_sgpio : 1;         /*!< [28..28] 1: Indicate SGPIO Wakeup event                                   */
    __IM  uint32_t lp_wsts_aon : 1;           /*!< [29..29] 1: Indicate AON Wakeup event (0x128)                             */
    __IM  uint32_t lp_wsts_hs : 1;            /*!< [30..30] 1: Indicate HS Wakeup event                                      */
  } b;                                        /*!< bit fields for syson_sys_boot_ctrl */
} syson_sys_boot_ctrl_t, *psyson_sys_boot_ctrl_t;

/**
  \brief Union type to access syson_hs_pll_isp_ctrl0 (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) ISP PLL Control Register0                                  */
  
  struct {
    __IM  uint32_t            : 3;
    __IOM uint32_t pll_isp_div_sel : 3;       /*!< [5..3] output divider selection. Default=000 000=/1, 100=/4,
                                                   110=/8, 111=/16                                                           */
    __IOM uint32_t pll_isp_ps_en : 1;         /*!< [6..6] phase selector enable                                              */
    __IOM uint32_t pll_isp_div2_en : 1;       /*!< [7..7] output clk div 2 enable                                            */
    __IOM uint32_t pll_isp_clk_en : 1;        /*!< [8..8] output clk enable                                                  */
    __IOM uint32_t pll_isp_fref_edge_sel : 1; /*!< [9..9] 0:fref,1:frefb                                                     */
    __IOM uint32_t pll_isp_c3_set : 2;        /*!< [11..10] Cp selection. Default=5p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_isp_r3_sel : 3;        /*!< [14..12] R3 selection. Default=1k 000: R3=0k, 001: R3=0.5k,
                                                   010: R3=1k, 011: R3=1.5k, 100: R3=2k, 101: R3=2.5k, 110:
                                                   R3=3k, 111: R3=3.5k;                                                      */
    __IOM uint32_t pll_isp_cs_sel : 2;        /*!< [16..15] Cs selection. Default=50p 00: Cs=30p, 01: Cs=40p, 10:
                                                   Cs=50p, 11: Cs=60p                                                        */
    __IOM uint32_t pll_isp_rs_sel : 3;        /*!< [19..17] Rs selection. Default=14k 000: Rs=2k, 001: Rs=4k, 010:
                                                   Rs=6k, 011: Rs=8k, 100: Rs=10k, 101: Rs=12k, 110: Rs=14k,
                                                   111: Rs=16k;                                                              */
    __IOM uint32_t pll_isp_cp_sel : 2;        /*!< [21..20] Cp selection. Default=3p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_isp_ps_sel : 3;        /*!< [24..22] PLL_ISP_PS_SEL                                                   */
    __IOM uint32_t pll_isp_wdg_en : 1;        /*!< [25..25] 0: watch dog on ,1: watch dog off                                */
    __IOM uint32_t pll_isp_cpc_sel : 3;       /*!< [28..26] charge pump current selection . Default=5u CP current
                                                   select : 000: Icp=5uA, 001: Icp=10uA, 010: Icp=15uA, 011:
                                                   Icp=20uA; 100:Icp=25uA, 101: Icp=30uA, 110: Icp=35uA, 111:
                                                   Icp=40uA;                                                                 */
    __IOM uint32_t pll_isp_en : 1;            /*!< [29..29] (need pwl signal) 0->1                                           */
    __IOM uint32_t pll_isp_div_en : 1;        /*!< [30..30] input divider enable (need pwl signal) 0->1                      */
    __IOM uint32_t pll_isp_powcut_en : 1;     /*!< [31..31] erc enable.                                                      */
  } b;                                        /*!< bit fields for syson_hs_pll_isp_ctrl0 */
} syson_hs_pll_isp_ctrl0_t, *psyson_hs_pll_isp_ctrl0_t;

/**
  \brief Union type to access syson_hs_pll_isp_ctrl1 (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) ISP PLL Control Register1                                  */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_isp_divn_sdm : 6;      /*!< [10..5] PLL_ISP_DIVN_SDM                                                  */
    __IOM uint32_t pll_isp_bb_dbg_sel_afe_sdm : 4;/*!< [14..11] PLL_ISP_BB_DBG_SEL_AFE_SDM                                   */
    __IOM uint32_t pll_isp_trig_rreq_en : 1;  /*!< [15..15] freq. step up or step down enable                                */
    __IOM uint32_t pll_isp_step_freq_sel : 4; /*!< [19..16] step size selection for switching freq.                          */
    __IOM uint32_t pll_isp_tbase_freq_sel : 4;/*!< [23..20] for output clk step up or step down                              */
    __IOM uint32_t pll_isp_freq_sel : 4;      /*!< [27..24] output clk selection, Default=400MHz                             */
    __IOM uint32_t pll_isp_xtal_sel : 4;      /*!< [31..28] xtal selection, Default=40MHz 0000: 40MHz, 0001: 25MHz,
                                                   0010: 13MHz, 0011: 19.2MHz 0100: 20MHz, 0101: 26MHz, 0110:
                                                   38.4MHz, 0111: 17.664MHz 1000: 16MHz, 1001: 14.138MHz 1010:
                                                   12MHz, 1011: 52MHz 1100: 48MHz, 1101: 27MHz, 1110: 24MHz,
                                                   1111: none                                                                */
  } b;                                        /*!< bit fields for syson_hs_pll_isp_ctrl1 */
} syson_hs_pll_isp_ctrl1_t, *psyson_hs_pll_isp_ctrl1_t;

/**
  \brief Union type to access syson_hs_pll_isp_ctrl2 (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) ISP PLL Control Register2                                  */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_isp_ssc_en : 1;        /*!< [5..5] ssc enable. Default=0                                              */
    __IOM uint32_t pll_isp_ssc_freq_sel : 13; /*!< [18..6] ssc freq selection                                                */
    __IOM uint32_t pll_isp_ssc_step_sel : 13; /*!< [31..19] ssc step size selection.                                         */
  } b;                                        /*!< bit fields for syson_hs_pll_isp_ctrl2 */
} syson_hs_pll_isp_ctrl2_t, *psyson_hs_pll_isp_ctrl2_t;

/**
  \brief Union type to access syson_hs_pll_isp_ctrl3 (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) ISP PLL Control Register3                                  */
  
  struct {
    __IM  uint32_t            : 15;
    __IOM uint32_t pll_isp_sdm_order_sel : 1; /*!< [15..15] SDM order: 0:2nd order, 1:3rd order                              */
    __IOM uint32_t pll_isp_sdm_fon : 3;       /*!< [18..16] N code, feedback divider number 1 for 1/8                        */
    __IOM uint32_t pll_isp_sdm_fof : 13;      /*!< [31..19] F code, feedback divider number 1for 1/8*1/2^13                  */
  } b;                                        /*!< bit fields for syson_hs_pll_isp_ctrl3 */
} syson_hs_pll_isp_ctrl3_t, *psyson_hs_pll_isp_ctrl3_t;

/**
  \brief Union type to access syson_hs_pll_isps_ctrl0 (@ 0x00000040).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000040) ISPS PLL Control Register0                                 */
  
  struct {
    __IM  uint32_t            : 3;
    __IOM uint32_t pll_isps_div_sel : 3;      /*!< [5..3] output divider selection. Default=000 000=/1, 100=/4,
                                                   110=/8, 111=/16                                                           */
    __IOM uint32_t pll_isps_ps_en : 1;        /*!< [6..6] phase selector enable                                              */
    __IOM uint32_t pll_isps_div2_en : 1;      /*!< [7..7] output clk div 2 enable                                            */
    __IOM uint32_t pll_isps_clk_en : 1;       /*!< [8..8] output clk enable                                                  */
    __IOM uint32_t pll_isps_fref_edge_sel : 1;/*!< [9..9] 0:fref,1:frefb                                                     */
    __IOM uint32_t pll_isps_c3_set : 2;       /*!< [11..10] Cp selection. Default=5p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_isps_r3_sel : 3;       /*!< [14..12] R3 selection. Default=1k 000: R3=0k, 001: R3=0.5k,
                                                   010: R3=1k, 011: R3=1.5k, 100: R3=2k, 101: R3=2.5k, 110:
                                                   R3=3k, 111: R3=3.5k;                                                      */
    __IOM uint32_t pll_isps_cs_sel : 2;       /*!< [16..15] Cs selection. Default=50p 00: Cs=30p, 01: Cs=40p, 10:
                                                   Cs=50p, 11: Cs=60p                                                        */
    __IOM uint32_t pll_isps_rs_sel : 3;       /*!< [19..17] Rs selection. Default=14k 000: Rs=2k, 001: Rs=4k, 010:
                                                   Rs=6k, 011: Rs=8k, 100: Rs=10k, 101: Rs=12k, 110: Rs=14k,
                                                   111: Rs=16k;                                                              */
    __IOM uint32_t pll_isps_cp_sel : 2;       /*!< [21..20] Cp selection. Default=3p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_isps_ps_sel : 3;       /*!< [24..22] PLL_ISPS_PS_SEL                                                  */
    __IOM uint32_t pll_isps_wdg_en : 1;       /*!< [25..25] 0: watch dog on ,1: watch dog off                                */
    __IOM uint32_t pll_isps_cpc_sel : 3;      /*!< [28..26] charge pump current selection . Default=5u CP current
                                                   select : 000: Icp=5uA, 001: Icp=10uA, 010: Icp=15uA, 011:
                                                   Icp=20uA; 100:Icp=25uA, 101: Icp=30uA, 110: Icp=35uA, 111:
                                                   Icp=40uA;                                                                 */
    __IOM uint32_t pll_isps_en : 1;           /*!< [29..29] (need pwl signal) 0->1                                           */
    __IOM uint32_t pll_isps_div_en : 1;       /*!< [30..30] input divider enable (need pwl signal) 0->1                      */
    __IOM uint32_t pll_isps_powcut_en : 1;    /*!< [31..31] erc enable.                                                      */
  } b;                                        /*!< bit fields for syson_hs_pll_isps_ctrl0 */
} syson_hs_pll_isps_ctrl0_t, *psyson_hs_pll_isps_ctrl0_t;

/**
  \brief Union type to access syson_hs_pll_isps_ctrl1 (@ 0x00000044).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000044) ISPS PLL Control Register1                                 */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_isps_divn_sdm : 6;     /*!< [10..5] PLL_ISPS_DIVN_SDM                                                 */
    __IOM uint32_t pll_isps_bb_dbg_sel_afe_sdm : 4;/*!< [14..11] PLL_ISPS_BB_DBG_SEL_AFE_SDM                                 */
    __IOM uint32_t pll_isps_trig_rreq_en : 1; /*!< [15..15] freq. step up or step down enable                                */
    __IOM uint32_t pll_isps_step_freq_sel : 4;/*!< [19..16] step size selection for switching freq.                          */
    __IOM uint32_t pll_isps_tbase_freq_sel : 4;/*!< [23..20] for output clk step up or step down                             */
    __IOM uint32_t pll_isps_freq_sel : 4;     /*!< [27..24] output clk selection, Default=74.25MHz/37.125MHz 0010:
                                                   74.25MHz/37.125MHz (297MHz/4, 297MHz/8) 0100: 54MHz/27MHz
                                                   (216MHz/4, 216MHz/8) 0110: 24MHz/12MHz (192MHz/8, 192MHz/16)              */
    __IOM uint32_t pll_isps_xtal_sel : 4;     /*!< [31..28] xtal selection, Default=40MHz 0000: 40MHz, 0001: 25MHz,
                                                   0010: 13MHz, 0011: 19.2MHz 0100: 20MHz, 0101: 26MHz, 0110:
                                                   38.4MHz, 0111: 17.664MHz 1000: 16MHz, 1001: 14.138MHz 1010:
                                                   12MHz, 1011: 52MHz 1100: 48MHz, 1101: 27MHz, 1110: 24MHz,
                                                   1111: none                                                                */
  } b;                                        /*!< bit fields for syson_hs_pll_isps_ctrl1 */
} syson_hs_pll_isps_ctrl1_t, *psyson_hs_pll_isps_ctrl1_t;

/**
  \brief Union type to access syson_hs_pll_isps_ctrl2 (@ 0x00000048).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000048) ISPS PLL Control Register2                                 */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_isps_ssc_en : 1;       /*!< [5..5] ssc enable. Default=0                                              */
    __IOM uint32_t pll_isps_ssc_freq_sel : 13;/*!< [18..6] ssc freq selection                                                */
    __IOM uint32_t pll_isps_ssc_step_sel : 13;/*!< [31..19] ssc step size selection.                                         */
  } b;                                        /*!< bit fields for syson_hs_pll_isps_ctrl2 */
} syson_hs_pll_isps_ctrl2_t, *psyson_hs_pll_isps_ctrl2_t;

/**
  \brief Union type to access syson_hs_pll_isps_ctrl3 (@ 0x0000004C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000004C) ISPS PLL Control Register3                                 */
  
  struct {
    __IM  uint32_t            : 15;
    __IOM uint32_t pll_isps_sdm_order_sel : 1;/*!< [15..15] SDM order: 0:2nd order, 1:3rd order                              */
    __IOM uint32_t pll_isps_sdm_fon : 3;      /*!< [18..16] N code, feedback divider number 1 for 1/8                        */
    __IOM uint32_t pll_isps_sdm_fof : 13;     /*!< [31..19] F code, feedback divider number 1for 1/8*1/2^13                  */
  } b;                                        /*!< bit fields for syson_hs_pll_isps_ctrl3 */
} syson_hs_pll_isps_ctrl3_t, *psyson_hs_pll_isps_ctrl3_t;

/**
  \brief Union type to access syson_hs_pll_sys_ctrl0 (@ 0x00000050).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000050) HS PLL Control Register0                                   */
  
  struct {
    __IM  uint32_t            : 3;
    __IOM uint32_t pll_sys_div_sel : 3;       /*!< [5..3] output divider selection. Default=000 000=/1, 100=/4,
                                                   110=/8, 111=/16                                                           */
    __IOM uint32_t pll_sys_ps_en : 1;         /*!< [6..6] phase selector enable                                              */
    __IOM uint32_t pll_sys_div2_en : 1;       /*!< [7..7] output clk div 2 enable                                            */
    __IOM uint32_t pll_sys_clk_en : 1;        /*!< [8..8] output clk enable                                                  */
    __IOM uint32_t pll_sys_fref_edge_sel : 1; /*!< [9..9] 0:fref,1:frefb                                                     */
    __IOM uint32_t pll_sys_c3_set : 2;        /*!< [11..10] Cp selection. Default=5p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_sys_r3_sel : 3;        /*!< [14..12] R3 selection. Default=1k 000: R3=0k, 001: R3=0.5k,
                                                   010: R3=1k, 011: R3=1.5k, 100: R3=2k, 101: R3=2.5k, 110:
                                                   R3=3k, 111: R3=3.5k;                                                      */
    __IOM uint32_t pll_sys_cs_sel : 2;        /*!< [16..15] Cs selection. Default=50p 00: Cs=30p, 01: Cs=40p, 10:
                                                   Cs=50p, 11: Cs=60p                                                        */
    __IOM uint32_t pll_sys_rs_sel : 3;        /*!< [19..17] Rs selection. Default=14k 000: Rs=2k, 001: Rs=4k, 010:
                                                   Rs=6k, 011: Rs=8k, 100: Rs=10k, 101: Rs=12k, 110: Rs=14k,
                                                   111: Rs=16k;                                                              */
    __IOM uint32_t pll_sys_cp_sel : 2;        /*!< [21..20] Cp selection. Default=3p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_sys_ps_sel : 3;        /*!< [24..22] PLL power state selection                                        */
    __IOM uint32_t pll_sys_wdg_en : 1;        /*!< [25..25] 0: watch dog on ,1: watch dog off                                */
    __IOM uint32_t pll_sys_cpc_sel : 3;       /*!< [28..26] charge pump current selection . Default=5u CP current
                                                   select : 000: Icp=5uA, 001: Icp=10uA, 010: Icp=15uA, 011:
                                                   Icp=20uA; 100:Icp=25uA, 101: Icp=30uA, 110: Icp=35uA, 111:
                                                   Icp=40uA;                                                                 */
    __IOM uint32_t pll_sys_en : 1;            /*!< [29..29] (need pwl signal) 0->1                                           */
    __IOM uint32_t pll_sys_div_en : 1;        /*!< [30..30] input divider enable (need pwl signal) 0->1                      */
    __IOM uint32_t pll_sys_powcut_en : 1;     /*!< [31..31] erc enable.                                                      */
  } b;                                        /*!< bit fields for syson_hs_pll_sys_ctrl0 */
} syson_hs_pll_sys_ctrl0_t, *psyson_hs_pll_sys_ctrl0_t;

/**
  \brief Union type to access syson_hs_pll_sys_ctrl1 (@ 0x00000054).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000054) HS PLL Control Register1                                   */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_sys_divn_sdm : 6;      /*!< [10..5] pll_sys_divn_sdm                                                  */
    __IOM uint32_t pll_sys_bb_dbg_sel_afe_sdm : 4;/*!< [14..11] pll_sys_bb_dbg_sel_afe_sdm                                   */
    __IOM uint32_t pll_sys_trig_rreq_en : 1;  /*!< [15..15] freq. step up or step down enable                                */
    __IOM uint32_t pll_sys_step_freq_sel : 4; /*!< [19..16] step size selection for switching freq.                          */
    __IOM uint32_t pll_sys_tbase_freq_sel : 4;/*!< [23..20] for output clk step up or step down                              */
    __IOM uint32_t pll_sys_freq_sel : 4;      /*!< [27..24] output clk selection, Default=300MHz                             */
    __IOM uint32_t pll_sys_xtal_sel : 4;      /*!< [31..28] xtal selection, Default=40MHz 0000: 40MHz, 0001: 25MHz,
                                                   0010: 13MHz, 0011: 19.2MHz 0100: 20MHz, 0101: 26MHz, 0110:
                                                   38.4MHz, 0111: 17.664MHz 1000: 16MHz, 1001: 14.138MHz 1010:
                                                   12MHz, 1011: 52MHz 1100: 48MHz, 1101: 27MHz, 1110: 24MHz,
                                                   1111: none                                                                */
  } b;                                        /*!< bit fields for syson_hs_pll_sys_ctrl1 */
} syson_hs_pll_sys_ctrl1_t, *psyson_hs_pll_sys_ctrl1_t;

/**
  \brief Union type to access syson_hs_pll_sys_ctrl2 (@ 0x00000058).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000058) HS PLL Control Register2                                   */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_sys_ssc_en : 1;        /*!< [5..5] ssc enable. Default=0                                              */
    __IOM uint32_t pll_sys_ssc_freq_sel : 13; /*!< [18..6] ssc freq selection                                                */
    __IOM uint32_t pll_sys_ssc_step_sel : 13; /*!< [31..19] ssc step size selection.                                         */
  } b;                                        /*!< bit fields for syson_hs_pll_sys_ctrl2 */
} syson_hs_pll_sys_ctrl2_t, *psyson_hs_pll_sys_ctrl2_t;

/**
  \brief Union type to access syson_hs_pll_sys_ctrl3 (@ 0x0000005C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000005C) HS PLL Control Register3                                   */
  
  struct {
    __IOM uint32_t pll_sys_200m_div_en : 1;   /*!< [0..0] 1 : enable 200M DIV                                                */
    __IOM uint32_t pll_sys_200m_en : 1;       /*!< [1..1] 1 : enable 200M clk                                                */
    __IM  uint32_t            : 13;
    __IOM uint32_t pll_sys_sdm_order_sel : 1; /*!< [15..15] SDM order: 0:2nd order, 1:3rd order                              */
    __IOM uint32_t pll_sys_sdm_fon : 3;       /*!< [18..16] N code, feedback divider number 1 for 1/8                        */
    __IOM uint32_t pll_sys_sdm_fof : 13;      /*!< [31..19] F code, feedback divider number 1for 1/8*1/2^13                  */
  } b;                                        /*!< bit fields for syson_hs_pll_sys_ctrl3 */
} syson_hs_pll_sys_ctrl3_t, *psyson_hs_pll_sys_ctrl3_t;

/**
  \brief Union type to access syson_hs_pll_enc_ctrl0 (@ 0x00000060).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000060) HS PLL ENC Control Register0                               */
  
  struct {
    __IM  uint32_t            : 3;
    __IOM uint32_t pll_enc_div_sel : 3;       /*!< [5..3] output divider selection. Default=000 000=/1, 100=/4,
                                                   110=/8, 111=/16                                                           */
    __IOM uint32_t pll_enc_ps_en : 1;         /*!< [6..6] phase selector enable                                              */
    __IOM uint32_t pll_enc_div2_en : 1;       /*!< [7..7] output clk div 2 enable                                            */
    __IOM uint32_t pll_enc_clk_en : 1;        /*!< [8..8] output clk enable                                                  */
    __IOM uint32_t pll_enc_fref_edge_sel : 1; /*!< [9..9] 0:fref,1:frefb                                                     */
    __IOM uint32_t pll_enc_c3_set : 2;        /*!< [11..10] Cp selection. Default=5p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_enc_r3_sel : 3;        /*!< [14..12] R3 selection. Default=1k 000: R3=0k, 001: R3=0.5k,
                                                   010: R3=1k, 011: R3=1.5k, 100: R3=2k, 101: R3=2.5k, 110:
                                                   R3=3k, 111: R3=3.5k;                                                      */
    __IOM uint32_t pll_enc_cs_sel : 2;        /*!< [16..15] Cs selection. Default=50p 00: Cs=30p, 01: Cs=40p, 10:
                                                   Cs=50p, 11: Cs=60p                                                        */
    __IOM uint32_t pll_enc_rs_sel : 3;        /*!< [19..17] Rs selection. Default=14k 000: Rs=2k, 001: Rs=4k, 010:
                                                   Rs=6k, 011: Rs=8k, 100: Rs=10k, 101: Rs=12k, 110: Rs=14k,
                                                   111: Rs=16k;                                                              */
    __IOM uint32_t pll_enc_cp_sel : 2;        /*!< [21..20] Cp selection. Default=3p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_enc_ps_sel : 3;        /*!< [24..22] PLL_ENC_PS_SEL                                                   */
    __IOM uint32_t pll_enc_wdg_en : 1;        /*!< [25..25] 0: watch dog on ,1: watch dog off                                */
    __IOM uint32_t pll_enc_cpc_sel : 3;       /*!< [28..26] charge pump current selection . Default=5u CP current
                                                   select : 000: Icp=5uA, 001: Icp=10uA, 010: Icp=15uA, 011:
                                                   Icp=20uA; 100:Icp=25uA, 101: Icp=30uA, 110: Icp=35uA, 111:
                                                   Icp=40uA;                                                                 */
    __IOM uint32_t pll_enc_en : 1;            /*!< [29..29] (need pwl signal) 0->1                                           */
    __IOM uint32_t pll_enc_div_en : 1;        /*!< [30..30] input divider enable (need pwl signal) 0->1                      */
    __IOM uint32_t pll_enc_powcut_en : 1;     /*!< [31..31] enc enable.                                                      */
  } b;                                        /*!< bit fields for syson_hs_pll_enc_ctrl0 */
} syson_hs_pll_enc_ctrl0_t, *psyson_hs_pll_enc_ctrl0_t;

/**
  \brief Union type to access syson_hs_pll_enc_ctrl1 (@ 0x00000064).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000064) HS PLL ENC Control Register1                               */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_enc_divn_sdm : 6;      /*!< [10..5] PLL_ENC_DIVN_SDM                                                  */
    __IOM uint32_t pll_enc_bb_dbg_sel_afe_sdm : 4;/*!< [14..11] PLL_ENC_BB_DBG_SEL_AFE_SDM                                   */
    __IOM uint32_t pll_enc_trig_rreq_en : 1;  /*!< [15..15] freq. step up or step down enable                                */
    __IOM uint32_t pll_enc_step_freq_sel : 4; /*!< [19..16] step size selection for switching freq.                          */
    __IOM uint32_t pll_enc_tbase_freq_sel : 4;/*!< [23..20] for output clk step up or step down                              */
    __IOM uint32_t pll_enc_freq_sel : 4;      /*!< [27..24] output clk selection, Default=240MHz                             */
    __IOM uint32_t pll_enc_xtal_sel : 4;      /*!< [31..28] xtal selection, Default=40MHz 0000: 40MHz, 0001: 25MHz,
                                                   0010: 13MHz, 0011: 19.2MHz 0100: 20MHz, 0101: 26MHz, 0110:
                                                   38.4MHz, 0111: 17.664MHz 1000: 16MHz, 1001: 14.138MHz 1010:
                                                   12MHz, 1011: 52MHz 1100: 48MHz, 1101: 27MHz, 1110: 24MHz,
                                                   1111: none                                                                */
  } b;                                        /*!< bit fields for syson_hs_pll_enc_ctrl1 */
} syson_hs_pll_enc_ctrl1_t, *psyson_hs_pll_enc_ctrl1_t;

/**
  \brief Union type to access syson_hs_pll_enc_ctrl2 (@ 0x00000068).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000068) HS PLL ENC Control Register2                               */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_enc_ssc_en : 1;        /*!< [5..5] ssc enable. Default=0                                              */
    __IOM uint32_t pll_enc_ssc_freq_sel : 13; /*!< [18..6] ssc freq selection                                                */
    __IOM uint32_t pll_enc_ssc_step_sel : 13; /*!< [31..19] ssc step size selection.                                         */
  } b;                                        /*!< bit fields for syson_hs_pll_enc_ctrl2 */
} syson_hs_pll_enc_ctrl2_t, *psyson_hs_pll_enc_ctrl2_t;

/**
  \brief Union type to access syson_hs_pll_enc_ctrl3 (@ 0x0000006C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000006C) HS PLL ENC Control Register3                               */
  
  struct {
    __IM  uint32_t            : 15;
    __IOM uint32_t pll_enc_sdm_order_sel : 1; /*!< [15..15] SDM order: 0:2nd order, 1:3rd order                              */
    __IOM uint32_t pll_enc_sdm_fon : 3;       /*!< [18..16] N code, feedback divider number 1 for 1/8                        */
    __IOM uint32_t pll_enc_sdm_fof : 13;      /*!< [31..19] F code, feedback divider number 1for 1/8*1/2^13                  */
  } b;                                        /*!< bit fields for syson_hs_pll_enc_ctrl3 */
} syson_hs_pll_enc_ctrl3_t, *psyson_hs_pll_enc_ctrl3_t;

/**
  \brief Union type to access syson_hs_pll_peri_ctrl0 (@ 0x00000070).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000070) HS PLL Peripheral Control Register0                        */
  
  struct {
    __IM  uint32_t            : 3;
    __IOM uint32_t pll_peri_div_sel : 3;      /*!< [5..3] output divider selection. Default=000 000=/1, 100=/4,
                                                   110=/8, 111=/16                                                           */
    __IOM uint32_t pll_peri_ps_en : 1;        /*!< [6..6] phase selector enable                                              */
    __IOM uint32_t pll_peri_div2_en : 1;      /*!< [7..7] output clk div 2 enable                                            */
    __IOM uint32_t pll_peri_clk_en : 1;       /*!< [8..8] output clk enable                                                  */
    __IOM uint32_t pll_peri_fref_edge_sel : 1;/*!< [9..9] 0:fref,1:frefb                                                     */
    __IOM uint32_t pll_peri_c3_set : 2;       /*!< [11..10] Cp selection. Default=5p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_peri_r3_sel : 3;       /*!< [14..12] R3 selection. Default=1k 000: R3=0k, 001: R3=0.5k,
                                                   010: R3=1k, 011: R3=1.5k, 100: R3=2k, 101: R3=2.5k, 110:
                                                   R3=3k, 111: R3=3.5k;                                                      */
    __IOM uint32_t pll_peri_cs_sel : 2;       /*!< [16..15] Cs selection. Default=50p 00: Cs=30p, 01: Cs=40p, 10:
                                                   Cs=50p, 11: Cs=60p                                                        */
    __IOM uint32_t pll_peri_rs_sel : 3;       /*!< [19..17] Rs selection. Default=14k 000: Rs=2k, 001: Rs=4k, 010:
                                                   Rs=6k, 011: Rs=8k, 100: Rs=10k, 101: Rs=12k, 110: Rs=14k,
                                                   111: Rs=16k;                                                              */
    __IOM uint32_t pll_peri_cp_sel : 2;       /*!< [21..20] Cp selection. Default=3p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_peris_ps_sel : 3;      /*!< [24..22] pll_peris_ps_sel                                                 */
    __IOM uint32_t pll_peri_wdg_en : 1;       /*!< [25..25] 0: watch dog on ,1: watch dog off                                */
    __IOM uint32_t pll_peri_cpc_sel : 3;      /*!< [28..26] charge pump current selection . Default=5u CP current
                                                   select : 000: Icp=5uA, 001: Icp=10uA, 010: Icp=15uA, 011:
                                                   Icp=20uA; 100:Icp=25uA, 101: Icp=30uA, 110: Icp=35uA, 111:
                                                   Icp=40uA;                                                                 */
    __IOM uint32_t pll_peri_en : 1;           /*!< [29..29] (need pwl signal) 0->1                                           */
    __IOM uint32_t pll_peri_div_en : 1;       /*!< [30..30] input divider enable (need pwl signal) 0->1                      */
    __IOM uint32_t pll_peri_powcut_en : 1;    /*!< [31..31] erc enable.                                                      */
  } b;                                        /*!< bit fields for syson_hs_pll_peri_ctrl0 */
} syson_hs_pll_peri_ctrl0_t, *psyson_hs_pll_peri_ctrl0_t;

/**
  \brief Union type to access syson_hs_pll_peri_ctrl1 (@ 0x00000074).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000074) HS PLL Peripheral Control Register1                        */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_peri_divn_sdm : 6;     /*!< [10..5] pll_peri_divn_sdm                                                 */
    __IOM uint32_t pll_peri_bb_dbg_sel_afe_sdm : 4;/*!< [14..11] pll_peri_bb_dbg_sel_afe_sdm                                 */
    __IOM uint32_t pll_peri_trig_rreq_en : 1; /*!< [15..15] freq. step up or step down enable                                */
    __IOM uint32_t pll_peri_step_freq_sel : 4;/*!< [19..16] step size selection for switching freq.                          */
    __IOM uint32_t pll_peri_tbase_freq_sel : 4;/*!< [23..20] for output clk step up or step down                             */
    __IOM uint32_t pll_peri_freq_sel : 4;     /*!< [27..24] output clk selection, Default=80MHz                              */
    __IOM uint32_t pll_peri_xtal_sel : 4;     /*!< [31..28] xtal selection, Default=40MHz 0000: 40MHz, 0001: 25MHz,
                                                   0010: 13MHz, 0011: 19.2MHz 0100: 20MHz, 0101: 26MHz, 0110:
                                                   38.4MHz, 0111: 17.664MHz 1000: 16MHz, 1001: 14.138MHz 1010:
                                                   12MHz, 1011: 52MHz 1100: 48MHz, 1101: 27MHz, 1110: 24MHz,
                                                   1111: none                                                                */
  } b;                                        /*!< bit fields for syson_hs_pll_peri_ctrl1 */
} syson_hs_pll_peri_ctrl1_t, *psyson_hs_pll_peri_ctrl1_t;

/**
  \brief Union type to access syson_hs_pll_peri_ctrl2 (@ 0x00000078).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000078) HS PLL PERI Control Register2                              */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_peri_ssc_en : 1;       /*!< [5..5] ssc enable. Default=0                                              */
    __IOM uint32_t pll_peri_ssc_freq_sel : 13;/*!< [18..6] ssc freq selection                                                */
    __IOM uint32_t pll_peri_ssc_step_sel : 13;/*!< [31..19] ssc step size selection.                                         */
  } b;                                        /*!< bit fields for syson_hs_pll_peri_ctrl2 */
} syson_hs_pll_peri_ctrl2_t, *psyson_hs_pll_peri_ctrl2_t;

/**
  \brief Union type to access syson_hs_pll_peri_ctrl3 (@ 0x0000007C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000007C) HS PLL PERI Control Register3                              */
  
  struct {
    __IM  uint32_t            : 15;
    __IOM uint32_t pll_peri_sdm_order_sel : 1;/*!< [15..15] SDM order: 0:2nd order, 1:3rd order                              */
    __IOM uint32_t pll_peri_sdm_fon : 3;      /*!< [18..16] N code, feedback divider number 1 for 1/8                        */
    __IOM uint32_t pll_peri_sdm_fof : 13;     /*!< [31..19] F code, feedback divider number 1for 1/8*1/2^13                  */
  } b;                                        /*!< bit fields for syson_hs_pll_peri_ctrl3 */
} syson_hs_pll_peri_ctrl3_t, *psyson_hs_pll_peri_ctrl3_t;

/**
  \brief Union type to access syson_hs_pll_i2s_ctrl0 (@ 0x00000080).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000080) HS PLL I2S Control Register0                               */
  
  struct {
    __IM  uint32_t            : 3;
    __IOM uint32_t pll_i2s_div_sel : 3;       /*!< [5..3] output divider selection. Default=000 000=/1, 100=/4,
                                                   110=/8, 111=/16                                                           */
    __IOM uint32_t pll_i2s_ps_en : 1;         /*!< [6..6] phase selector enable                                              */
    __IOM uint32_t pll_i2s_div2_en : 1;       /*!< [7..7] output clk div 2 enable                                            */
    __IOM uint32_t pll_i2s_clk_en : 1;        /*!< [8..8] output clk enable                                                  */
    __IOM uint32_t pll_i2s_fref_edge_sel : 1; /*!< [9..9] 0:fref,1:frefb                                                     */
    __IOM uint32_t pll_i2s_c3_set : 2;        /*!< [11..10] Cp selection. Default=5p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_i2s_r3_sel : 3;        /*!< [14..12] R3 selection. Default=1k 000: R3=0k, 001: R3=0.5k,
                                                   010: R3=1k, 011: R3=1.5k, 100: R3=2k, 101: R3=2.5k, 110:
                                                   R3=3k, 111: R3=3.5k;                                                      */
    __IOM uint32_t pll_i2s_cs_sel : 2;        /*!< [16..15] Cs selection. Default=50p 00: Cs=30p, 01: Cs=40p, 10:
                                                   Cs=50p, 11: Cs=60p                                                        */
    __IOM uint32_t pll_i2s_rs_sel : 3;        /*!< [19..17] Rs selection. Default=14k 000: Rs=2k, 001: Rs=4k, 010:
                                                   Rs=6k, 011: Rs=8k, 100: Rs=10k, 101: Rs=12k, 110: Rs=14k,
                                                   111: Rs=16k;                                                              */
    __IOM uint32_t pll_i2s_cp_sel : 2;        /*!< [21..20] Cp selection. Default=3p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_i2ss_ps_sel : 3;       /*!< [24..22] pll_peris_ps_sel                                                 */
    __IOM uint32_t pll_i2s_wdg_en : 1;        /*!< [25..25] 0: watch dog on ,1: watch dog off                                */
    __IOM uint32_t pll_i2s_cpc_sel : 3;       /*!< [28..26] charge pump current selection . Default=5u CP current
                                                   select : 000: Icp=5uA, 001: Icp=10uA, 010: Icp=15uA, 011:
                                                   Icp=20uA; 100:Icp=25uA, 101: Icp=30uA, 110: Icp=35uA, 111:
                                                   Icp=40uA;                                                                 */
    __IOM uint32_t pll_i2s_en : 1;            /*!< [29..29] (need pwl signal) 0->1                                           */
    __IOM uint32_t pll_i2s_div_en : 1;        /*!< [30..30] input divider enable (need pwl signal) 0->1                      */
    __IOM uint32_t pll_i2s_powcut_en : 1;     /*!< [31..31] erc enable.                                                      */
  } b;                                        /*!< bit fields for syson_hs_pll_i2s_ctrl0 */
} syson_hs_pll_i2s_ctrl0_t, *psyson_hs_pll_i2s_ctrl0_t;

/**
  \brief Union type to access syson_hs_i2s_peri_ctrl1 (@ 0x00000084).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000084) HS PLL I2S Control Register1                               */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_i2s_divn_sdm : 6;      /*!< [10..5] pll_peri_divn_sdm                                                 */
    __IOM uint32_t pll_i2s_bb_dbg_sel_afe_sdm : 4;/*!< [14..11] pll_peri_bb_dbg_sel_afe_sdm                                  */
    __IOM uint32_t pll_i2s_trig_rreq_en : 1;  /*!< [15..15] freq. step up or step down enable                                */
    __IOM uint32_t pll_i2s_step_freq_sel : 4; /*!< [19..16] step size selection for switching freq.                          */
    __IOM uint32_t pll_i2s_tbase_freq_sel : 4;/*!< [23..20] for output clk step up or step down                              */
    __IOM uint32_t pll_i2s_freq_sel : 4;      /*!< [27..24] output clk selection, Default=98.304MHz/24.576MHz                */
    __IOM uint32_t pll_i2s_xtal_sel : 4;      /*!< [31..28] xtal selection, Default=40MHz 0000: 40MHz, 0001: 25MHz,
                                                   0010: 13MHz, 0011: 19.2MHz 0100: 20MHz, 0101: 26MHz, 0110:
                                                   38.4MHz, 0111: 17.664MHz 1000: 16MHz, 1001: 14.138MHz 1010:
                                                   12MHz, 1011: 52MHz 1100: 48MHz, 1101: 27MHz, 1110: 24MHz,
                                                   1111: none                                                                */
  } b;                                        /*!< bit fields for syson_hs_i2s_peri_ctrl1 */
} syson_hs_i2s_peri_ctrl1_t, *psyson_hs_i2s_peri_ctrl1_t;

/**
  \brief Union type to access syson_hs_pll_i2s_ctrl2 (@ 0x00000088).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000088) HS PLL I2S Control Register2                               */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_i2s_ssc_en : 1;        /*!< [5..5] ssc enable. Default=0                                              */
    __IOM uint32_t pll_i2s_ssc_freq_sel : 13; /*!< [18..6] ssc freq selection                                                */
    __IOM uint32_t pll_i2s_ssc_step_sel : 13; /*!< [31..19] ssc step size selection.                                         */
  } b;                                        /*!< bit fields for syson_hs_pll_i2s_ctrl2 */
} syson_hs_pll_i2s_ctrl2_t, *psyson_hs_pll_i2s_ctrl2_t;

/**
  \brief Union type to access syson_hs_pll_i2s_ctrl3 (@ 0x0000008C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000008C) HS PLL I2S Control Register3                               */
  
  struct {
    __IM  uint32_t            : 15;
    __IOM uint32_t pll_i2s_sdm_order_sel : 1; /*!< [15..15] SDM order: 0:2nd order, 1:3rd order                              */
    __IOM uint32_t pll_i2s_sdm_fon : 3;       /*!< [18..16] N code, feedback divider number 1 for 1/8                        */
    __IOM uint32_t pll_i2s_sdm_fof : 13;      /*!< [31..19] F code, feedback divider number 1for 1/8*1/2^13                  */
  } b;                                        /*!< bit fields for syson_hs_pll_i2s_ctrl3 */
} syson_hs_pll_i2s_ctrl3_t, *psyson_hs_pll_i2s_ctrl3_t;

/**
  \brief Union type to access syson_hs_pll_pcm_ctrl0 (@ 0x00000090).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000090) HS PLL PCM Control Register0                               */
  
  struct {
    __IM  uint32_t            : 3;
    __IOM uint32_t pll_pcm_div_sel : 3;       /*!< [5..3] output divider selection. Default=000 000=/1, 100=/4,
                                                   110=/8, 111=/16                                                           */
    __IOM uint32_t pll_pcm_ps_en : 1;         /*!< [6..6] phase selector enable                                              */
    __IOM uint32_t pll_pcm_div2_en : 1;       /*!< [7..7] output clk div 2 enable                                            */
    __IOM uint32_t pll_pcm_clk_en : 1;        /*!< [8..8] output clk enable                                                  */
    __IOM uint32_t pll_pcm_fref_edge_sel : 1; /*!< [9..9] 0:fref,1:frefb                                                     */
    __IOM uint32_t pll_pcm_c3_set : 2;        /*!< [11..10] Cp selection. Default=5p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_pcm_r3_sel : 3;        /*!< [14..12] R3 selection. Default=1k 000: R3=0k, 001: R3=0.5k,
                                                   010: R3=1k, 011: R3=1.5k, 100: R3=2k, 101: R3=2.5k, 110:
                                                   R3=3k, 111: R3=3.5k;                                                      */
    __IOM uint32_t pll_pcm_cs_sel : 2;        /*!< [16..15] Cs selection. Default=50p 00: Cs=30p, 01: Cs=40p, 10:
                                                   Cs=50p, 11: Cs=60p                                                        */
    __IOM uint32_t pll_pcm_rs_sel : 3;        /*!< [19..17] Rs selection. Default=14k 000: Rs=2k, 001: Rs=4k, 010:
                                                   Rs=6k, 011: Rs=8k, 100: Rs=10k, 101: Rs=12k, 110: Rs=14k,
                                                   111: Rs=16k;                                                              */
    __IOM uint32_t pll_pcm_cp_sel : 2;        /*!< [21..20] Cp selection. Default=3p 00: Cp=3p, 01: Cp=4p, 10:
                                                   Cp=5p, 11: Cp=6p                                                          */
    __IOM uint32_t pll_pcms_ps_sel : 3;       /*!< [24..22] pll_peris_ps_sel                                                 */
    __IOM uint32_t pll_pcm_wdg_en : 1;        /*!< [25..25] 0: watch dog on ,1: watch dog off                                */
    __IOM uint32_t pll_pcm_cpc_sel : 3;       /*!< [28..26] charge pump current selection . Default=5u CP current
                                                   select : 000: Icp=5uA, 001: Icp=10uA, 010: Icp=15uA, 011:
                                                   Icp=20uA; 100:Icp=25uA, 101: Icp=30uA, 110: Icp=35uA, 111:
                                                   Icp=40uA;                                                                 */
    __IOM uint32_t pll_pcm_en : 1;            /*!< [29..29] (need pwl signal) 0->1                                           */
    __IOM uint32_t pll_pcm_div_en : 1;        /*!< [30..30] input divider enable (need pwl signal) 0->1                      */
    __IOM uint32_t pll_pcm_powcut_en : 1;     /*!< [31..31] erc enable.                                                      */
  } b;                                        /*!< bit fields for syson_hs_pll_pcm_ctrl0 */
} syson_hs_pll_pcm_ctrl0_t, *psyson_hs_pll_pcm_ctrl0_t;

/**
  \brief Union type to access syson_hs_pll_pcm_ctrl1 (@ 0x00000094).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000094) HS PLL PCM Control Register1                               */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_pcm_divn_sdm : 6;      /*!< [10..5] pll_peri_divn_sdm                                                 */
    __IOM uint32_t pll_pcm_bb_dbg_sel_afe_sdm : 4;/*!< [14..11] pll_peri_bb_dbg_sel_afe_sdm                                  */
    __IOM uint32_t pll_pcm_trig_rreq_en : 1;  /*!< [15..15] freq. step up or step down enable                                */
    __IOM uint32_t pll_pcm_step_freq_sel : 4; /*!< [19..16] step size selection for switching freq.                          */
    __IOM uint32_t pll_pcm_tbase_freq_sel : 4;/*!< [23..20] for output clk step up or step down                              */
    __IOM uint32_t pll_pcm_freq_sel : 4;      /*!< [27..24] output clk selection, Default=45.158MHz                          */
    __IOM uint32_t pll_pcm_xtal_sel : 4;      /*!< [31..28] xtal selection, Default=40MHz 0000: 40MHz, 0001: 25MHz,
                                                   0010: 13MHz, 0011: 19.2MHz 0100: 20MHz, 0101: 26MHz, 0110:
                                                   38.4MHz, 0111: 17.664MHz 1000: 16MHz, 1001: 14.138MHz 1010:
                                                   12MHz, 1011: 52MHz 1100: 48MHz, 1101: 27MHz, 1110: 24MHz,
                                                   1111: none                                                                */
  } b;                                        /*!< bit fields for syson_hs_pll_pcm_ctrl1 */
} syson_hs_pll_pcm_ctrl1_t, *psyson_hs_pll_pcm_ctrl1_t;

/**
  \brief Union type to access syson_hs_pll_pcm_ctrl2 (@ 0x00000098).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000098) HS PLL PCM Control Register2                               */
  
  struct {
    __IM  uint32_t            : 5;
    __IOM uint32_t pll_pcm_ssc_en : 1;        /*!< [5..5] ssc enable. Default=0                                              */
    __IOM uint32_t pll_pcm_ssc_freq_sel : 13; /*!< [18..6] ssc freq selection                                                */
    __IOM uint32_t pll_pcm_ssc_step_sel : 13; /*!< [31..19] ssc step size selection.                                         */
  } b;                                        /*!< bit fields for syson_hs_pll_pcm_ctrl2 */
} syson_hs_pll_pcm_ctrl2_t, *psyson_hs_pll_pcm_ctrl2_t;

/**
  \brief Union type to access syson_hs_pll_pcm_ctrl3 (@ 0x0000009C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000009C) HS PLL PCM Control Register3                               */
  
  struct {
    __IM  uint32_t            : 15;
    __IOM uint32_t pll_pcm_sdm_order_sel : 1; /*!< [15..15] SDM order: 0:2nd order, 1:3rd order                              */
    __IOM uint32_t pll_pcm_sdm_fon : 3;       /*!< [18..16] N code, feedback divider number 1 for 1/8                        */
    __IOM uint32_t pll_pcm_sdm_fof : 13;      /*!< [31..19] F code, feedback divider number 1for 1/8*1/2^13                  */
  } b;                                        /*!< bit fields for syson_hs_pll_pcm_ctrl3 */
} syson_hs_pll_pcm_ctrl3_t, *psyson_hs_pll_pcm_ctrl3_t;

/**
  \brief Union type to access syson_hs_pll_test (@ 0x000000A0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A0) HS PLL Test Register                                       */
  
  struct {
    __IOM uint32_t pll_test_agpio_en : 1;     /*!< [0..0] AGPIO enable                                                       */
    __IOM uint32_t pll_test_agpio_output_en : 1;/*!< [1..1] AGPIO output enable                                              */
    __IOM uint32_t pll_test_agpio_dri_sel : 2;/*!< [3..2] AGPIO driving sel                                                  */
    __IOM uint32_t pll_test_clk_sel : 4;      /*!< [7..4] ckmon clk sel 1111:CK_400M_ISP 1110:READY_400M 1101:CK_ISPS
                                                   1100:READY_ISPS 1011:CK_300M_SYS 1010:READY_300M 1001:CK_240M_ENC
                                                   1000:READY_240M_ENC 0111:CK_80M_PERI 0110:READY_80M_PERI
                                                   0101:CK_98P304M_I2S 0100:CK_24P576M_I2S 0011:READY_I2S
                                                   0010:CK_45P158M_PCM 0001:READY_45P158M_PCM 0000:TL                        */
    __IOM uint32_t pll_test_clk_mon_en : 1;   /*!< [8..8] ckmon enable                                                       */
    __IOM uint32_t xtal_clk_sel : 1;          /*!< [9..9] xtal clk from 0 special route 1 APR                                */
    __IM  uint32_t            : 14;
    __IOM uint32_t pll_isp_rdy : 1;           /*!< [24..24] ISP PLL ready                                                    */
    __IOM uint32_t pll_isps_rdy : 1;          /*!< [25..25] ISPS PLL ready                                                   */
    __IOM uint32_t pll_sys_rdy : 1;           /*!< [26..26] SYS PLL ready                                                    */
    __IOM uint32_t pll_enc_rdy : 1;           /*!< [27..27] Encoder PLL ready                                                */
    __IOM uint32_t pll_peri_rdy : 1;          /*!< [28..28] PERI PLL ready                                                   */
    __IOM uint32_t pll_i2s_rdy : 1;           /*!< [29..29] I2S PLL ready                                                    */
    __IOM uint32_t pll_pcm_rdy : 1;           /*!< [30..30] PCM PLL ready                                                    */
  } b;                                        /*!< bit fields for syson_hs_pll_test */
} syson_hs_pll_test_t, *psyson_hs_pll_test_t;

/**
  \brief Union type to access syson_hs_efuse_ctrl0 (@ 0x000000A4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A4) HS EFuse Control Register0                                 */
  
  struct {
    __IOM uint32_t efuse_autoload_sus : 1;    /*!< [0..0] 1: Autoload successful 0: Autoload fail                            */
    __IOM uint32_t efuse_ldall : 1;           /*!< [1..1] 1: SW enable HWSM to autoload excluding Efuse 0x00~ 0x31           */
    __IOM uint32_t efuse_sys_aldn : 1;        /*!< [2..2] 1: SYS Config autoload done; 0: autoload not ready                 */
    __IOM uint32_t efuse_sdio_aldn : 1;       /*!< [3..3] 1: SDIO Config autoload done; 0: autoload not ready                */
    __IM  uint32_t            : 3;
    __IOM uint32_t hs_efldr_clk_sel : 1;      /*!< [7..7] 1: PLL CLK; 0: 4M                                                  */
    __IOM uint32_t efuse_unlock : 8;          /*!< [15..8] 1: unlock efuse                                                   */
    __IOM uint32_t ldoe25_en  : 1;            /*!< [16..16] Power on LDOE25                                                  */
  } b;                                        /*!< bit fields for syson_hs_efuse_ctrl0 */
} syson_hs_efuse_ctrl0_t, *psyson_hs_efuse_ctrl0_t;

/**
  \brief Union type to access syson_hs_efuse_ctrl1 (@ 0x000000A8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000A8) HS EFuse Control Register1                                 */
  
  struct {
    __IOM uint32_t sys_ef_data : 8;           /*!< [7..0] Access Data                                                        */
    __IOM uint32_t sys_ef_addr : 10;          /*!< [17..8] Access Address                                                    */
    __IOM uint32_t sys_ef_alden : 1;          /*!< [18..18] Autoload Enable                                                  */
    __IOM uint32_t sys_ef_pdwn : 1;           /*!< [19..19] Efuse power down                                                 */
    __IOM uint32_t sys_ef_pgts : 4;           /*!< [23..20] Programming setup time. In the unit of cycle time.(125ns)        */
    __IOM uint32_t sys_ef_rdt : 4;            /*!< [27..24] E-fuse read time: in the unit of cycle time                      */
    __IOM uint32_t sys_ef_pgpd : 3;           /*!< [30..28] E-fuse program time: 000: 5000ns, 001: 5100ns, 010:
                                                   5200ns, 011: 5900ns 100: 6500ns, 101: 7000ns, 110: 7500ns,
                                                   111: 8000ns                                                               */
    __IOM uint32_t sys_ef_rwflag : 1;         /*!< [31..31] Write 1 for Program; Write 0 for Read Access                     */
  } b;                                        /*!< bit fields for syson_hs_efuse_ctrl1 */
} syson_hs_efuse_ctrl1_t, *psyson_hs_efuse_ctrl1_t;

/**
  \brief Union type to access syson_hs_swrm_ctrl0 (@ 0x000000B0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000B0) HS SWRM Control Register0                                  */
  
  struct {
    __IOM uint32_t swrm_sldo_en : 1;          /*!< [0..0] 1: enable SWR SLDO                                                 */
    __IOM uint32_t swrm_m_en  : 1;            /*!< [1..1] 1: enable SWR mode                                                 */
    __IOM uint32_t ldo_m_en   : 1;            /*!< [2..2] 1: enable LDO mode                                                 */
    __IOM uint32_t ldod_enb   : 1;            /*!< [3..3] 1: disable LDO diode                                               */
  } b;                                        /*!< bit fields for syson_hs_swrm_ctrl0 */
} syson_hs_swrm_ctrl0_t, *psyson_hs_swrm_ctrl0_t;

/**
  \brief Union type to access syson_hs_ldoio_ctrl0 (@ 0x000000D4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000D4) HS LDOIO Control Register0                                 */
  
  struct {
    __IOM uint32_t rstb12     : 1;            /*!< [0..0] RSTB12                                                             */
    __IM  uint32_t            : 7;
    __IOM uint32_t ldoio_bypass_en : 1;       /*!< [8..8] Enable Bypass Mode                                                 */
    __IOM uint32_t ldoio_pd   : 1;            /*!< [9..9] Power down                                                         */
    __IOM uint32_t ldoio_rccomp : 1;          /*!< [10..10] Enable RC compensation                                           */
    __IOM uint32_t ldoio_vol_l : 4;           /*!< [14..11] 0000=>1.705V 0001=>1.801V 0010=>1.893V 0011=>1.981V
                                                   0100=>2.071V 0101=>2.165V 0110=>2.251V 0111=>2.344V 1000=>2.445V
                                                   1001=>2.526V 1010=>2.634V 1011=>2.733V 1100=>2.828V 1101=>2.931V
                                                   1110=>3.012V 1111=>3.097V                                                 */
    __IOM uint32_t ldoio_stby0 : 1;           /*!< [15..15] Standby OP tail current                                          */
    __IOM uint32_t ldoio_stby1 : 1;           /*!< [16..16] Standby Power PMOS                                               */
    __IOM uint32_t ldoio_diode_en : 1;        /*!< [17..17] Enable diode soft start                                          */
  } b;                                        /*!< bit fields for syson_hs_ldoio_ctrl0 */
} syson_hs_ldoio_ctrl0_t, *psyson_hs_ldoio_ctrl0_t;

/**
  \brief Union type to access syson_hs_efuse_syscfg0 (@ 0x00000100).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000100) HS eFuse Sys Configure 0 Register                          */
  
  struct {
    __IOM uint32_t efuse_syscfg0 : 32;        /*!< [31..0] Auto loaded eFuse Sys configuration 0                             */
  } b;                                        /*!< bit fields for syson_hs_efuse_syscfg0 */
} syson_hs_efuse_syscfg0_t, *psyson_hs_efuse_syscfg0_t;

/**
  \brief Union type to access syson_hs_efuse_syscfg1 (@ 0x00000104).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000104) HS eFuse Sys Configure 1 Register                          */
  
  struct {
    __IOM uint32_t efuse_syscfg1 : 32;        /*!< [31..0] Auto loaded eFuse Sys configuration 1                             */
  } b;                                        /*!< bit fields for syson_hs_efuse_syscfg1 */
} syson_hs_efuse_syscfg1_t, *psyson_hs_efuse_syscfg1_t;

/**
  \brief Union type to access syson_hs_efuse_syscfg2 (@ 0x00000108).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000108) HS eFuse Sys Configure 2 Register                          */
  
  struct {
    __IOM uint32_t efuse_syscfg2 : 32;        /*!< [31..0] Auto loaded eFuse Sys configuration 2                             */
  } b;                                        /*!< bit fields for syson_hs_efuse_syscfg2 */
} syson_hs_efuse_syscfg2_t, *psyson_hs_efuse_syscfg2_t;

/**
  \brief Union type to access syson_hs_efuse_syscfg3 (@ 0x0000010C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000010C) HS eFuse Sys Configure 3 Register                          */
  
  struct {
    __IOM uint32_t efuse_syscfg3 : 32;        /*!< [31..0] Auto loaded eFuse Sys configuration 3                             */
  } b;                                        /*!< bit fields for syson_hs_efuse_syscfg3 */
} syson_hs_efuse_syscfg3_t, *psyson_hs_efuse_syscfg3_t;

/**
  \brief Union type to access syson_hs_efuse_syscfg4 (@ 0x00000110).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000110) HS eFuse Sys Configure 4 Register                          */
  
  struct {
    __IOM uint32_t efuse_syscfg4 : 32;        /*!< [31..0] Auto loaded eFuse Sys configuration 4                             */
  } b;                                        /*!< bit fields for syson_hs_efuse_syscfg4 */
} syson_hs_efuse_syscfg4_t, *psyson_hs_efuse_syscfg4_t;

/**
  \brief Union type to access syson_hs_efuse_syscfg5 (@ 0x00000114).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000114) HS eFuse Sys Configure 5 Register                          */
  
  struct {
    __IOM uint32_t efuse_syscfg5 : 32;        /*!< [31..0] Auto loaded eFuse Sys configuration 5                             */
  } b;                                        /*!< bit fields for syson_hs_efuse_syscfg5 */
} syson_hs_efuse_syscfg5_t, *psyson_hs_efuse_syscfg5_t;

/**
  \brief Union type to access syson_hs_efuse_syscfg6 (@ 0x00000118).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000118) HS eFuse Sys Configure 6 Register                          */
  
  struct {
    __IOM uint32_t efuse_syscfg6 : 32;        /*!< [31..0] Auto loaded eFuse Sys configuration 6                             */
  } b;                                        /*!< bit fields for syson_hs_efuse_syscfg6 */
} syson_hs_efuse_syscfg6_t, *psyson_hs_efuse_syscfg6_t;

/**
  \brief Union type to access syson_hs_efuse_syscfg7 (@ 0x0000011C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000011C) HS eFuse Sys Configure 7 Register                          */
  
  struct {
    __IOM uint32_t efuse_syscfg7 : 32;        /*!< [31..0] Auto loaded eFuse Sys configuration 7                             */
  } b;                                        /*!< bit fields for syson_hs_efuse_syscfg7 */
} syson_hs_efuse_syscfg7_t, *psyson_hs_efuse_syscfg7_t;

/**
  \brief Union type to access syson_hs_wake_event_msk0 (@ 0x00000120).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000120) HS Wakeup Event Mask Register                              */
  
  struct {
    __IM  uint32_t            : 1;
    __IOM uint32_t wevt_gtim_msk : 1;         /*!< [1..1] 1: enable Gtimer 0~F Wakeup event; 0: disable the event
                                                   to wakeup system                                                          */
    __IOM uint32_t wevt_boost_ocp_msk : 1;    /*!< [2..2] 1: enable boost OCP wakeup event; 0: disable the event
                                                   to wakeup system                                                          */
    __IOM uint32_t wevt_swrm_ocp_msk : 1;     /*!< [3..3] 1: enable SWRM OCP wakeup event; 0: disable the event
                                                   to wakeup system                                                          */
    __IOM uint32_t wevt_gpio_msk : 1;         /*!< [4..4] 1: enable GPIO Wakeup event; 0: disable the event to
                                                   wakeup system                                                             */
    __IOM uint32_t wevt_pwm_msk : 1;          /*!< [5..5] 1: enable PWM Wakeup event; 0: disable the event to wakeup
                                                   system                                                                    */
    __IM  uint32_t            : 2;
    __IOM uint32_t wevt_wlan_msk : 1;         /*!< [8..8] 1: enable WLAN Wakeup event; 0: disable the event to
                                                   wakeup system                                                             */
    __IM  uint32_t            : 5;
    __IOM uint32_t wevt_sdio_msk : 1;         /*!< [14..14] 1: enable SDIO Wakeup event; 0: disable the event to
                                                   wakeup system                                                             */
    __IM  uint32_t            : 1;
    __IOM uint32_t wevt_usb_msk : 1;          /*!< [16..16] 1: enable USB Wakeup event; 0: disable the event to
                                                   wakeup system                                                             */
    __IM  uint32_t            : 3;
    __IOM uint32_t wevt_uart_msk : 1;         /*!< [20..20] 1: enable UART Wakeup event; 0: disable the event to
                                                   wakeup system                                                             */
    __IM  uint32_t            : 1;
    __IOM uint32_t rsvd_wevt_spi_msk : 1;     /*!< [22..22] 1: enable SPI Wakeup event; 0: disable the event to
                                                   wakeup system                                                             */
    __IM  uint32_t            : 1;
    __IOM uint32_t wevt_i2c_msk : 1;          /*!< [24..24] 1: enable I2C Wakeup event; 0: disable the event to
                                                   wakeup system                                                             */
    __IM  uint32_t            : 1;
    __IOM uint32_t wevt_adc_msk : 1;          /*!< [26..26] 1: enable ADC Wakeup event; 0: disable the event to
                                                   wakeup system                                                             */
    __IM  uint32_t            : 1;
    __IOM uint32_t wevt_sgpio_msk : 1;        /*!< [28..28] 1: enable SGPIO Wakeup event; 0: disable the event
                                                   to wakeup system                                                          */
  } b;                                        /*!< bit fields for syson_hs_wake_event_msk0 */
} syson_hs_wake_event_msk0_t, *psyson_hs_wake_event_msk0_t;

/**
  \brief Union type to access syson_hs_wake_event_status0 (@ 0x00000124).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000124) HS Wakeup Event Status Register                            */
  
  struct {
    __IM  uint32_t            : 1;
    __IM  uint32_t wevt_gtim_sts : 1;         /*!< [1..1] 1: Indicate GTimer0~F Wakeup event;                                */
    __IM  uint32_t wevt_boost_ocp_sts : 1;    /*!< [2..2] 1: Indicate BOOST OCP event                                        */
    __IM  uint32_t wevt_swrm_ocp_sts : 1;     /*!< [3..3] 1: Indicate SWRM OCP event                                         */
    __IM  uint32_t wevt_gpio_sts : 1;         /*!< [4..4] 1: Indicate GPIO Wakeup event                                      */
    __IM  uint32_t wevt_pwm_sts : 1;          /*!< [5..5] RSVD for GPIO wakeup event                                         */
    __IM  uint32_t            : 2;
    __IM  uint32_t wevt_wlan_sts : 1;         /*!< [8..8] 1: Indicate WLAN Wakeup event                                      */
    __IM  uint32_t            : 5;
    __IM  uint32_t wevt_sdio_sts : 1;         /*!< [14..14] 1: Indicate SDIO Wakeup event                                    */
    __IM  uint32_t            : 1;
    __IM  uint32_t wevt_usb_sts : 1;          /*!< [16..16] 1:Indicate USB Wakeup event                                      */
    __IM  uint32_t            : 3;
    __IM  uint32_t wevt_uart_sts : 1;         /*!< [20..20] 1: Indicate UART Wakeup event                                    */
    __IM  uint32_t            : 1;
    __IM  uint32_t rsvd_wevt_spi_sts : 1;     /*!< [22..22] 1: Indicate SPI Wakeup event                                     */
    __IM  uint32_t            : 1;
    __IM  uint32_t wevt_i2c_sts : 1;          /*!< [24..24] 1: Indicate I2C Wakeup event                                     */
    __IM  uint32_t            : 1;
    __IM  uint32_t wevt_adc_sts : 1;          /*!< [26..26] 1: Indicate ADC Wakeup event                                     */
    __IM  uint32_t            : 1;
    __IM  uint32_t wevt_sgpio_sts : 1;        /*!< [28..28] 1: Indicate SGPIO Wakeup event                                   */
  } b;                                        /*!< bit fields for syson_hs_wake_event_status0 */
} syson_hs_wake_event_status0_t, *psyson_hs_wake_event_status0_t;

/**
  \brief Union type to access syson_hs_adc_ctrl0 (@ 0x00000150).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000150) HS ADC Control 0                                           */
  
  struct {
    __IOM uint32_t pwr_cut    : 1;            /*!< [0..0] power cut                                                          */
    __IOM uint32_t en         : 1;            /*!< [1..1] en                                                                 */
    __IOM uint32_t ref_en     : 1;            /*!< [2..2] ref_en                                                             */
    __IOM uint32_t cal_en     : 1;            /*!< [3..3] cal_en                                                             */
    __IOM uint32_t vref_en    : 1;            /*!< [4..4] ext_vref_en                                                        */
    __IOM uint32_t ck         : 1;            /*!< [5..5] reg_ck                                                             */
    __IOM uint32_t ckd2       : 1;            /*!< [6..6] reg_ckd2                                                           */
    __IOM uint32_t dly        : 1;            /*!< [7..7] reg_delay                                                          */
    __IOM uint32_t samp       : 1;            /*!< [8..8] reg_samp                                                           */
    __IOM uint32_t revck      : 1;            /*!< [9..9] reg_revck                                                          */
    __IOM uint32_t dout       : 1;            /*!< [10..10] reg_dout                                                         */
    __IOM uint32_t bstca      : 1;            /*!< [11..11] reg_bstca                                                        */
    __IOM uint32_t avg        : 1;            /*!< [12..12] reg_avg                                                          */
    __IOM uint32_t bypass     : 6;            /*!< [18..13] reg_bypass[6:0]                                                  */
    __IOM uint32_t dat_sel    : 5;            /*!< [23..19] reg_data_sel[4:0]                                                */
  } b;                                        /*!< bit fields for syson_hs_adc_ctrl0 */
} syson_hs_adc_ctrl0_t, *psyson_hs_adc_ctrl0_t;

/**
  \brief Union type to access syson_hs_adc_ctrl1 (@ 0x00000154).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000154) HS ADC Control 1                                           */
  
  struct {
    __IOM uint32_t dout0_p    : 2;            /*!< [1..0] reg_dout0_p[1:0]                                                   */
    __IOM uint32_t dout0_n    : 2;            /*!< [3..2] reg_dout0_n[1:0]                                                   */
    __IOM uint32_t dout1_p    : 3;            /*!< [6..4] reg_dout1_p[2:0]                                                   */
    __IOM uint32_t dout1_n    : 3;            /*!< [9..7] reg_dout1_n[2:0]                                                   */
    __IOM uint32_t dout2_p    : 3;            /*!< [12..10] reg_dout2_p[2:0]                                                 */
    __IOM uint32_t dout2_n    : 3;            /*!< [15..13] reg_dout2_n[2:0]                                                 */
    __IOM uint32_t dout3_p    : 4;            /*!< [19..16] reg_dout3_p[3:0]                                                 */
    __IOM uint32_t dout3_n    : 4;            /*!< [23..20] reg_dout3_n[3:0]                                                 */
    __IOM uint32_t dout4_p    : 5;            /*!< [28..24] reg_dout4_p[4:0]                                                 */
    __IOM uint32_t dmy        : 3;            /*!< [31..29] dummy                                                            */
  } b;                                        /*!< bit fields for syson_hs_adc_ctrl1 */
} syson_hs_adc_ctrl1_t, *psyson_hs_adc_ctrl1_t;

/**
  \brief Union type to access syson_hs_adc_ctrl2 (@ 0x00000158).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000158) HS ADC Control 2                                           */
  
  struct {
    __IOM uint32_t dout4_n    : 5;            /*!< [4..0] reg_dout4_n[4:0]                                                   */
    __IOM uint32_t dout5_p    : 5;            /*!< [9..5] reg_dout5_p[4:0]                                                   */
    __IOM uint32_t dout5_n    : 5;            /*!< [14..10] reg_dout5_n[4:0]                                                 */
    __IOM uint32_t dout6_p    : 5;            /*!< [19..15] reg_dout6_p[4:0]                                                 */
    __IOM uint32_t dout6_n    : 5;            /*!< [24..20] reg_dout6_n[4:0]                                                 */
    __IOM uint32_t dout7_p    : 5;            /*!< [29..25] reg_dout7_p[4:0]                                                 */
    __IOM uint32_t dmy        : 2;            /*!< [31..30] dummy                                                            */
  } b;                                        /*!< bit fields for syson_hs_adc_ctrl2 */
} syson_hs_adc_ctrl2_t, *psyson_hs_adc_ctrl2_t;

/**
  \brief Union type to access syson_hs_adc_ctrl3 (@ 0x0000015C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000015C) HS ADC Control 3                                           */
  
  struct {
    __IOM uint32_t dout7_n    : 5;            /*!< [4..0] reg_dout7_n[4:0]                                                   */
    __IOM uint32_t dout8_p    : 5;            /*!< [9..5] reg_dout8_p[4:0]                                                   */
    __IOM uint32_t dout8_n    : 5;            /*!< [14..10] reg_dout8_n[4:0]                                                 */
    __IOM uint32_t dout9_p    : 6;            /*!< [20..15] reg_dout9_p[5:0]                                                 */
    __IOM uint32_t dout9_n    : 6;            /*!< [26..21] reg_dout9_n[5:0]                                                 */
    __IOM uint32_t dmy        : 5;            /*!< [31..27] dummy                                                            */
  } b;                                        /*!< bit fields for syson_hs_adc_ctrl3 */
} syson_hs_adc_ctrl3_t, *psyson_hs_adc_ctrl3_t;

/**
  \brief Union type to access syson_hs_adc_ctrl4 (@ 0x00000160).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000160) HS ADC Control 4                                           */
  
  struct {
    __IOM uint32_t dout10_p   : 6;            /*!< [5..0] reg_dout10_p[5:0]                                                  */
    __IOM uint32_t dout10_n   : 6;            /*!< [11..6] reg_dout10_n[5:0]                                                 */
    __IOM uint32_t dout11_p   : 7;            /*!< [18..12] reg_dout11_p[6:0]                                                */
    __IOM uint32_t dout11_n   : 7;            /*!< [25..19] reg_dout11_n[6:0]                                                */
    __IOM uint32_t dmy        : 6;            /*!< [31..26] dummy                                                            */
  } b;                                        /*!< bit fields for syson_hs_adc_ctrl4 */
} syson_hs_adc_ctrl4_t, *psyson_hs_adc_ctrl4_t;

/**
  \brief Union type to access syson_hs_adc_ctrl5 (@ 0x00000164).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000164) HS ADC Control 5                                           */
  
  struct {
    __IOM uint32_t dout12_p   : 8;            /*!< [7..0] reg_dout12_p[7:0]                                                  */
    __IOM uint32_t dout12_n   : 8;            /*!< [15..8] reg_dout12_n[7:0]                                                 */
    __IOM uint32_t dout13_p   : 8;            /*!< [23..16] reg_dout13_p[7:0]                                                */
    __IOM uint32_t dout13_n   : 8;            /*!< [31..24] reg_dout13_n[7:0]                                                */
  } b;                                        /*!< bit fields for syson_hs_adc_ctrl5 */
} syson_hs_adc_ctrl5_t, *psyson_hs_adc_ctrl5_t;

/**
  \brief Union type to access syson_hs_adc_ctrl6 (@ 0x00000168).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000168) HS ADC Control 6                                           */
  
  struct {
    __IOM uint32_t dout_offp  : 6;            /*!< [5..0] reg_dout_offp[5:0]                                                 */
    __IOM uint32_t dout_offn  : 6;            /*!< [11..6] reg_dout_offn[5:0]                                                */
    __IOM uint32_t dmy        : 20;           /*!< [31..12] dummy                                                            */
  } b;                                        /*!< bit fields for syson_hs_adc_ctrl6 */
} syson_hs_adc_ctrl6_t, *psyson_hs_adc_ctrl6_t;

/**
  \brief Union type to access syson_hs_adc_iso (@ 0x0000016C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000016C) HS AD Power Isolation Control Register                     */
  
  struct {
    __IOM uint32_t peri_pll   : 1;            /*!< [0..0] 1: isolation peri pll and aux AD                                   */
    __IOM uint32_t sys_otr_pll : 1;           /*!< [1..1] 1: isolation syspll and other pll                                  */
  } b;                                        /*!< bit fields for syson_hs_adc_iso */
} syson_hs_adc_iso_t, *psyson_hs_adc_iso_t;

/**
  \brief Union type to access syson_hs_sys_cfg0 (@ 0x000001F0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000001F0) HS System Configuration Register 0                         */
  
  struct {
    __IM  uint32_t chip_ver   : 4;            /*!< [3..0] Chip version 0000 : A-cut 0001 : B-cut 0010 : C-cut 0011
                                                   : D-cut                                                                   */
    __IM  uint32_t vendor_id  : 2;            /*!< [5..4] Vendor ID Download FW version ; 00: TSMC , 01: SMIC,
                                                   10: UMC                                                                   */
    __IM  uint32_t            : 1;
    __IM  uint32_t chip_type  : 1;            /*!< [7..7] TestChip ID,1: Test (RLE); 0: MP(RL)                               */
    __IM  uint32_t            : 8;
    __IM  uint32_t xtal_sel   : 4;            /*!< [19..16] Xtal selection                                                   */
    __IM  uint32_t            : 4;
    __IM  uint32_t syscfg_alf_en : 1;         /*!< [24..24] 0: Autoload fail                                                 */
    __IM  uint32_t syscfg_test_mod_en : 1;    /*!< [25..25] 0: normal mode 1: test mode                                      */
    __IM  uint32_t syscfg_trp_spsldo_sel : 1; /*!< [26..26] Trapped Selection for SPS 0: SWR mode; 1: LDO mode               */
    __IM  uint32_t            : 1;
    __IM  uint32_t db_opt0_ext_rstb : 1;      /*!< [28..28] vht_sigb_crc_sel0                                                */
    __IM  uint32_t db_opt1_ext_clk : 1;       /*!< [29..29] db_opt1/ext_clk                                                  */
    __IM  uint32_t chg_li_exist : 1;          /*!< [30..30] 1: CHG or Li battery exist                                       */
    __IM  uint32_t syscfg_bd_pkg_sel : 1;     /*!< [31..31] Trapped PKG_ENG_SEL value 0: normal package; 1: engineering
                                                   mode                                                                      */
  } b;                                        /*!< bit fields for syson_hs_sys_cfg0 */
} syson_hs_sys_cfg0_t, *psyson_hs_sys_cfg0_t;

/**
  \brief Union type to access syson_hs_psram_ctrl (@ 0x00000200).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000200) HS PSRAM Control Register                                  */
  
  struct {
    __IOM uint32_t hs_psram_en : 1;           /*!< [0..0] memory control clock enable                                        */
    __IM  uint32_t            : 3;
    __IOM uint32_t hs_psram_clk_en : 1;       /*!< [4..4] memory control clock enable                                        */
    __IM  uint32_t            : 3;
    __IOM uint32_t hs_psram_speedup : 1;      /*!< [8..8] rxi310_speedup_sim                                                 */
  } b;                                        /*!< bit fields for syson_hs_psram_ctrl */
} syson_hs_psram_ctrl_t, *psyson_hs_psram_ctrl_t;

/**
  \brief Union type to access syson_hs_lpddr1_ctrl (@ 0x00000204).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000204) HS LPDDR1 Control Register                                 */
  
  struct {
    __IOM uint32_t hs_lpddr1_en : 1;          /*!< [0..0] memory control function enable                                     */
    __IM  uint32_t            : 3;
    __IOM uint32_t hs_lpddr1_clk_en : 1;      /*!< [4..4] memory control function enable                                     */
    __IM  uint32_t            : 3;
    __IOM uint32_t hs_lpddr1_speedup : 1;     /*!< [8..8] rxi310_speedup_sim                                                 */
  } b;                                        /*!< bit fields for syson_hs_lpddr1_ctrl */
} syson_hs_lpddr1_ctrl_t, *psyson_hs_lpddr1_ctrl_t;

/**
  \brief Union type to access syson_hs_ddrphy_ctrl (@ 0x00000208).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000208) HS DDR PHY Control Register                                */
  
  struct {
    __IOM uint32_t hs_ddrphy_crt_rst : 1;     /*!< [0..0] CRT active low asynchronous reset                                  */
    __IOM uint32_t hs_ddrphy_dpi_rst : 1;     /*!< [1..1] DPI active low asynchronous reset                                  */
    __IOM uint32_t hs_ddrphy_dpi_fifo_rst : 1;/*!< [2..2] DPI active low asynchronous reset for FIFO debug                   */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_ddrphy_pll_ldo_en : 1;  /*!< [4..4] PLL LDO enable                                                     */
    __IM  uint32_t hs_ddrphy_pll_rdy : 1;     /*!< [5..5] PLL ready                                                          */
    __IOM uint32_t hs_ddrphy_pll_pwn : 1;     /*!< [6..6] 1: power down DDRPHY PLL                                           */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_ddrphy_rbus_clk_en : 1; /*!< [8..8] Rbus interface clock gating control                                */
    __IOM uint32_t hs_ddrphy_crt_clk_en : 1;  /*!< [9..9] CRT control register clock gating control                          */
  } b;                                        /*!< bit fields for syson_hs_ddrphy_ctrl */
} syson_hs_ddrphy_ctrl_t, *psyson_hs_ddrphy_ctrl_t;

/**
  \brief Union type to access syson_hs_share_mem_ctrl (@ 0x0000020C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000020C) HS Share Memory Control Register                           */
  
  struct {
    __IOM uint32_t hs_share_mem_en : 1;       /*!< [0..0] Memory function enable: 0: disable, 1: enable                      */
    __IM  uint32_t            : 3;
    __IOM uint32_t hs_share_mem_clk_en : 1;   /*!< [4..4] Memory clock enable: 0: disable, 1: enable                         */
    __IM  uint32_t            : 3;
    __IOM uint32_t hs_share_mem_mod_sel : 1;  /*!< [8..8] Mode selection: 0: used by platform, 1: used by H264
                                                   encoder                                                                   */
  } b;                                        /*!< bit fields for syson_hs_share_mem_ctrl */
} syson_hs_share_mem_ctrl_t, *psyson_hs_share_mem_ctrl_t;

/**
  \brief Union type to access syson_hs_flash_ctrl (@ 0x00000210).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000210) HS Flash Control Register                                  */
  
  struct {
    __IOM uint32_t hs_flash_en : 1;           /*!< [0..0] 1: Enable FLASH                                                    */
    __IOM uint32_t hs_flash_clk_en : 1;       /*!< [1..1] 1: Enable FLASH CLK                                                */
    __IM  uint32_t            : 2;
    __IM  uint32_t hs_flash_init_ok : 1;      /*!< [4..4] BOOT_finish                                                        */
    __IOM uint32_t hs_flash_speedup : 1;      /*!< [5..5] spic_speed_up                                                      */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_flash_mux_en : 1;       /*!< [8..8] 1: Enable FLASH MUX                                                */
    __IOM uint32_t hs_flash_mode_sel : 1;     /*!< [9..9] 0: QPI Mode; 1: OCT mode (GPIOF_0~10)                              */
    __IOM uint32_t hs_flash_quad_bit_mux_en : 1;/*!< [10..10] QPI mode quad bit mux enable                                   */
    __IOM uint32_t hs_flash_qpi_mux_sel : 1;  /*!< [11..11] 0: GPIOF_0,3,4,7,9,10; 1: GPIOB_0~5                              */
  } b;                                        /*!< bit fields for syson_hs_flash_ctrl */
} syson_hs_flash_ctrl_t, *psyson_hs_flash_ctrl_t;

/**
  \brief Union type to access syson_hs_flash_phy_ctrl0 (@ 0x00000214).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000214) HS Flash PHY Control Register 0                            */
  
  struct {
    __IOM uint32_t hs_flash_phy_en : 1;       /*!< [0..0] Enable rx data, must enable first.                                 */
    __IOM uint32_t hs_flash_phy_output_phase_en : 1;/*!< [1..1] Tx Coase tuning for DTR. Delay 0.5 spic_clk period of
                                                   sclk                                                                      */
    __IOM uint32_t hs_flash_phy_merge_phase_en : 1;/*!< [2..2] Rx tuning for DTR. If upper lane & lower lane data are
                                                   reversed, set this bit to recover. 0: posedge rx data first
                                                   1: negedge rx data first                                                  */
    __IOM uint32_t hs_flash_phy_dqs_en : 1;   /*!< [3..3] Enable DQS to fetch rx data. Enable Rx tuning via DQS
                                                   for offset 218 bit 8 to bit23 and offset 214 bit 16 to
                                                   bit 19                                                                    */
    __IOM uint32_t hs_flash_phy_dqs_ddr_en : 1;/*!< [4..4] Enable DQS to fetch double data rate rx data. Must enable
                                                   before using DTR mode. Enable Rx tuning for offset 218
                                                   bit 8 to bit23 and offset 214 bit 16 to bit 19                            */
    __IOM uint32_t hs_flash_phy_dly_en : 2;   /*!< [6..5] Rx tuning when the deviation of high lane and low lane
                                                   is up to 1 cycle due to the process. 0 : delay lower lane
                                                   a spic_clk period 1 : delay upper lane a spic_clk period                  */
    __IM  uint32_t            : 9;
    __IOM uint32_t hs_flash_phy_fetch_phase : 4;/*!< [19..16] Rx coarse tune. bit 16 : delay 0.5 spic_clk period
                                                   to fetch lower lane data bit 17 : delay 0.5 spic_clk period
                                                   to fetch upper lane data bit 18 : delay 0.5 spic_clk period
                                                   to sync lower lane data to spic bit 19 : delay 0.5 spic_clk
                                                   period to sync upper lane data to spic bit 16 = bit 17,
                                                   bit 18 = bit 19.                                                          */
  } b;                                        /*!< bit fields for syson_hs_flash_phy_ctrl0 */
} syson_hs_flash_phy_ctrl0_t, *psyson_hs_flash_phy_ctrl0_t;

/**
  \brief Union type to access syson_hs_flash_phy_ctrl1 (@ 0x00000218).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000218) HS Flash PHY Control Register 1                            */
  
  struct {
    __IOM uint32_t hs_flash_phy_output_dly_sel : 8;/*!< [7..0] Tx fine tung for DTR. Select delay level of sclk delay
                                                   line                                                                      */
    __IOM uint32_t hs_flash_phy_dqsl_dly_sel : 8;/*!< [15..8] select delay level of DQS on the lower lane. Rx fine
                                                   tune for 4IO and first 4IO of 8IO. If offset 214 bit 3
                                                   is enabled, the delay is based on DQS, otherwise, the delay
                                                   is based on sclk                                                          */
    __IOM uint32_t hs_flash_phy_dqsu_dly_sel : 8;/*!< [23..16] select delay level of DQS on the upper lane. Rx fine
                                                   tune for last 4IO of 8IO. If offset 214 bit 3 is enabled,
                                                   the delay is based on DQS, otherwise, the delay is based
                                                   on sclk                                                                   */
  } b;                                        /*!< bit fields for syson_hs_flash_phy_ctrl1 */
} syson_hs_flash_phy_ctrl1_t, *psyson_hs_flash_phy_ctrl1_t;

/**
  \brief Union type to access syson_hs_platform_ctrl0 (@ 0x00000220).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000220) HS Platform Control Register 0                             */
  
  struct {
    __IOM uint32_t hs_gdma0_en : 1;           /*!< [0..0] 1: Enable GDMA0                                                    */
    __IOM uint32_t hs_gdma0_clk_en : 1;       /*!< [1..1] 1: Enable GDMA0 CLK                                                */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_gdma0_clk_alws_en : 1;  /*!< [4..4] gdma_clk_always_enable                                             */
    __IOM uint32_t hs_gdma0_clk_alws_dis : 1; /*!< [5..5] gdma_clk_always_disable                                            */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_gdma1_en : 1;           /*!< [8..8] 1: Enable GDMA1                                                    */
    __IOM uint32_t hs_gdma1_clk_en : 1;       /*!< [9..9] 1: Enable GDMA1 CLK                                                */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_gdma1_clk_alws_en : 1;  /*!< [12..12] gdma_clk_always_enable                                           */
    __IOM uint32_t hs_gdma1_clk_alws_dis : 1; /*!< [13..13] gdma_clk_always_disable                                          */
    __IM  uint32_t            : 2;
    __IOM uint32_t lxbus_en   : 1;            /*!< [16..16] 1: Enable LX bus                                                 */
    __IOM uint32_t lxbus_clk_en : 1;          /*!< [17..17] 1: Enable LX bus CLK                                             */
    __IM  uint32_t            : 6;
    __IOM uint32_t hs_ipsec_en : 1;           /*!< [24..24] 1: enable security engine IP                                     */
    __IOM uint32_t hs_ipsec_clk_en : 1;       /*!< [25..25] 1: security engine clock enable                                  */
  } b;                                        /*!< bit fields for syson_hs_platform_ctrl0 */
} syson_hs_platform_ctrl0_t, *psyson_hs_platform_ctrl0_t;

/**
  \brief Union type to access syson_hs_debuger_ctrl (@ 0x00000224).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000224) HS Debugger Control Register                               */
  
  struct {
    __IOM uint32_t debuger_pin_en : 1;        /*!< [0..0] 1: Enable debuger mux                                              */
    __IOM uint32_t debuger_mode_sel : 2;      /*!< [2..1] 00: SWD; 01: JTAG 10: JTAG chain mode                              */
    __IOM uint32_t debuger_pin_sel : 1;       /*!< [3..3] debuger is muxed on 0: GPIOE_0~4 1: GPIOC_2~6                      */
  } b;                                        /*!< bit fields for syson_hs_debuger_ctrl */
} syson_hs_debuger_ctrl_t, *psyson_hs_debuger_ctrl_t;

/**
  \brief Union type to access syson_hs_timer_ctrl (@ 0x00000228).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000228) HS G-Timer Control Register                                */
  
  struct {
    __IOM uint32_t hs_tg0_en  : 1;            /*!< [0..0] 1: Enable HS Timer Group0 block                                    */
    __IOM uint32_t hs_tg0_pclk_en : 1;        /*!< [1..1] 1: Enable HS Timer Group0 Pclock                                   */
    __IOM uint32_t hs_tg0_sclk_en : 1;        /*!< [2..2] 1: Enable HS Timer Group0 Sclock                                   */
    __IOM uint32_t hs_tg0_intr_clk_sel : 1;   /*!< [3..3] select TG0 interrupt clock source, 0: APB clock, 1: timer
                                                   counter clock (controlled by BIT_TG0_SCLK_SEL[1:0])                       */
    __IOM uint32_t hs_tg0_src_sel : 2;        /*!< [5..4] 00: 2MHz 01: 20MHz 10: 32KHz_LP 11: rsvd                           */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_tg1_en  : 1;            /*!< [8..8] 1: Enable HS Timer Group1 block                                    */
    __IOM uint32_t hs_tg1_pclk_en : 1;        /*!< [9..9] 1: Enable HS Timer Group1 Pclock                                   */
    __IOM uint32_t hs_tg1_sclk_en : 1;        /*!< [10..10] 1: Enable HS Timer Group1 Sclock                                 */
    __IOM uint32_t hs_tg1_intr_clk_sel : 1;   /*!< [11..11] Select TC1 interrupt clock source, 0: APB clock, 1:
                                                   timer counter clock (controlled by BIT_TG1_SCLK_SEL[1:0])                 */
    __IOM uint32_t hs_tg1_src_sel : 2;        /*!< [13..12] 00: 2MHz 01: 20MHz 10: 32KHz_LP 11: rsvd                         */
  } b;                                        /*!< bit fields for syson_hs_timer_ctrl */
} syson_hs_timer_ctrl_t, *psyson_hs_timer_ctrl_t;

/**
  \brief Union type to access syson_hs_tef_ctrl (@ 0x0000022C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000022C) HS Timer Event Function (PWM) Control Register             */
  
  struct {
    __IOM uint32_t tef_en     : 1;            /*!< [0..0] Timer event function enable control. 1: Enable HS TEF
                                                   block                                                                     */
    __IOM uint32_t tef_pclk_en : 1;           /*!< [1..1] Timer event function P-clock control. 1: Enable HS TEF
                                                   pclock                                                                    */
    __IOM uint32_t tef_sclk_en : 1;           /*!< [2..2] Timer event function S-clock control. 1: Enable HS TEF
                                                   sclock                                                                    */
    __IOM uint32_t tef_int_clk_sel : 1;       /*!< [3..3] Timer event function interrupt clock selection. 0: APB
                                                   CLK; 1: TIMER CLK                                                         */
    __IM  uint32_t            : 4;
    __IOM uint32_t pwm0_pin_en : 1;           /*!< [8..8] enable PWM0 mux                                                    */
    __IOM uint32_t pwm1_pin_en : 1;           /*!< [9..9] enable PWM1 mux                                                    */
    __IOM uint32_t pwm2_pin_en : 1;           /*!< [10..10] enable PWM2 mux                                                  */
    __IOM uint32_t pwm3_pin_en : 1;           /*!< [11..11] enable PWM3 mux                                                  */
    __IOM uint32_t pwm4_pin_en : 1;           /*!< [12..12] enable PWM4 mux                                                  */
    __IOM uint32_t pwm5_pin_en : 1;           /*!< [13..13] enable PWM5 mux                                                  */
    __IOM uint32_t pwm6_pin_en : 1;           /*!< [14..14] enable PWM6 mux                                                  */
    __IOM uint32_t pwm7_pin_en : 1;           /*!< [15..15] enable PWM7 mux                                                  */
    __IOM uint32_t pwm0_pin_sel : 2;          /*!< [17..16] PWM0 is muxed on 00: GPIOE_0 01: GPIOG_2 10: GPIOC_4
                                                   11: GPIOB_0                                                               */
    __IOM uint32_t pwm1_pin_sel : 2;          /*!< [19..18] PWM1 is muxed on 00: GPIOE_1 01: GPIOG_3 10: GPIOC_5
                                                   11: GPIOB_1                                                               */
    __IOM uint32_t pwm2_pin_sel : 2;          /*!< [21..20] PWM2 is muxed on 00: GPIOE_2 01: GPIOG_4 10: GPIOC_6
                                                   11: GPIOB_2                                                               */
    __IOM uint32_t pwm3_pin_sel : 2;          /*!< [23..22] PWM3 is muxed on 00: GPIOE_3 01: GPIOG_5 10: GPIOC_7
                                                   11: GPIOB_3                                                               */
    __IOM uint32_t pwm4_pin_sel : 2;          /*!< [25..24] PWM4 is muxed on 00: GPIOE_4 01: GPIOG_6 10: GPIOC_8
                                                   11: GPIOB_4                                                               */
    __IOM uint32_t pwm5_pin_sel : 2;          /*!< [27..26] PWM5 is muxed on 00: GPIOE_5 01: GPIOG_7 10: GPIOC_9
                                                   11: GPIOB_5                                                               */
    __IOM uint32_t pwm6_pin_sel : 2;          /*!< [29..28] PWM6 is muxed on 00: GPIOE_6 01: GPIOG_8 10: GPIOC_10
                                                   11: GPIOB_6                                                               */
    __IOM uint32_t pwm7_pin_sel : 2;          /*!< [31..30] PWM7 is muxed on 00: GPIOE_7 01: GPIOG_9 10: GPIOC_11
                                                   11: GPIOB_7                                                               */
  } b;                                        /*!< bit fields for syson_hs_tef_ctrl */
} syson_hs_tef_ctrl_t, *psyson_hs_tef_ctrl_t;

/**
  \brief Union type to access syson_hs_adc_ctrl (@ 0x00000230).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000230) HS ADC Control Register                                    */
  
  struct {
    __IOM uint32_t en         : 1;            /*!< [0..0] Enable HS ADC block. 1:Enable, 0:Disable                           */
    __IOM uint32_t pclk_en    : 1;            /*!< [1..1] Enable HS ADC Pclock. 1:Enable, 0:Disable                          */
    __IOM uint32_t sclk_en    : 1;            /*!< [2..2] Enable HS ADC Sclock. 1:Enable, 0:Disable                          */
    __IM  uint32_t            : 1;
    __IOM uint32_t intr_clk_sel : 1;          /*!< [4..4] Interrupt clock select. 0: Pclk; 1: Sclk                           */
    __IOM uint32_t ctrl_msr_sel : 1;          /*!< [5..5] Control MSR select. 0: HW; 1:SW                                    */
    __IM  uint32_t            : 2;
    __IOM uint32_t adc4_mux_en : 1;           /*!< [8..8] Enable HS ADC4 MUX on GPIOH_0. 1:Enable, 0:Disable                 */
    __IOM uint32_t adc5_mux_en : 1;           /*!< [9..9] Enable HS ADC5 MUX on GPIOH_1. 1:Enable, 0:Disable                 */
    __IOM uint32_t adc6_mux_en : 1;           /*!< [10..10] Enable HS ADC6 MUX on GPIOH_2. 1:Enable, 0:Disable               */
    __IOM uint32_t adc7_mux_en : 1;           /*!< [11..11] Enable HS ADC7 MUX on GPIOH_3. 1:Enable, 0:Disable               */
  } b;                                        /*!< bit fields for syson_hs_adc_ctrl */
} syson_hs_adc_ctrl_t, *psyson_hs_adc_ctrl_t;

/**
  \brief Union type to access syson_hs_gpio_ctrl (@ 0x00000234).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000234) HS GPIO Control Register                                   */
  
  struct {
    __IOM uint32_t hs_gpio_en : 1;            /*!< [0..0] 1: Enable HS GPIO block                                            */
    __IOM uint32_t hs_gpio_pclk_en : 1;       /*!< [1..1] 1: Enable HS GPIO Pclock                                           */
    __IOM uint32_t hs_gpio_sclk_en : 1;       /*!< [2..2] 1: Enable HS GPIO Sclock                                           */
    __IOM uint32_t hs_gpio_intr_clk_sel : 1;  /*!< [3..3] 1: APB, 0: debounce clock                                          */
    __IOM uint32_t hs_gpio_db_clk_sel : 1;    /*!< [4..4] 1: HS 32K, 0: LP 32K                                               */
  } b;                                        /*!< bit fields for syson_hs_gpio_ctrl */
} syson_hs_gpio_ctrl_t, *psyson_hs_gpio_ctrl_t;

/**
  \brief Union type to access syson_hs_codec_ctrl (@ 0x00000238).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000238) HS CODEC Control Register                                  */
  
  struct {
    __IOM uint32_t hs_codec_en : 1;           /*!< [0..0] Enable codec IP. 1:Enable, 0:Disable                               */
    __IOM uint32_t hs_codec_pclk_en : 1;      /*!< [1..1] Enable codec Pclock. 1:Enable, 0:Disable                           */
    __IOM uint32_t hs_codec_sclk_en : 1;      /*!< [2..2] Enable codec Sclock. 1:Enable, 0:Disable                           */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_codec_porb : 1;         /*!< [4..4] 0:reset codec                                                      */
    __IM  uint32_t            : 3;
    __IOM uint32_t hs_codec_ldo_en : 1;       /*!< [8..8] LDO power control. 1:Enable, 0:Disable                             */
    __IOM uint32_t hs_codec_ldo_tune : 7;     /*!< [15..9] LDO voltage control. 1:Enable, 0:Disable                          */
  } b;                                        /*!< bit fields for syson_hs_codec_ctrl */
} syson_hs_codec_ctrl_t, *psyson_hs_codec_ctrl_t;

/**
  \brief Union type to access syson_hs_isp_ctrl (@ 0x0000023C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000023C) HS ISP Control Register                                    */
  
  struct {
    __IOM uint32_t hs_isp_en  : 1;            /*!< [0..0] 1. Enable ISP                                                      */
    __IOM uint32_t hs_isp_clk_en : 1;         /*!< [1..1] 1. Enable ISP CLK                                                  */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_isp_i2c_mux_en : 1;     /*!< [4..4] 1. Enable ISP I2C MUX                                              */
    __IOM uint32_t hs_isp_parallel_mux_en : 1;/*!< [5..5] 1. Enable ISP parallel MUX (GPIOD_3~15)                            */
    __IOM uint32_t hs_isp_ctrl_mux_en : 1;    /*!< [6..6] 1. Enable ISP Control MUX                                          */
    __IOM uint32_t hs_isp_ctrl_mux_sel : 1;   /*!< [7..7] ISP Control is muxed on 0: GPIOC_2~7, GPIOD_2 1: GPIOC_2~7,
                                                   GPIOE_13                                                                  */
    __IOM uint32_t hs_encoder_en : 1;         /*!< [8..8] 1: Enable Encoder                                                  */
    __IOM uint32_t hs_encoder_clk_en : 1;     /*!< [9..9] 1: Enable Encoder CLK                                              */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_voe_en  : 1;            /*!< [12..12] 1: Enable VOE                                                    */
    __IOM uint32_t hs_voe_clk_en : 1;         /*!< [13..13] 1: Enable VOE CLK                                                */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_mjpeg_en : 1;           /*!< [16..16] 1: Enable Motion JPEG                                            */
    __IOM uint32_t hs_mjpeg_clk_en : 1;       /*!< [17..17] 1: Enable Motion JPEG CLK                                        */
    __IM  uint32_t            : 2;
    __IOM uint32_t mipi_signal_sw : 1;        /*!< [20..20] 1: enable mipi signal                                            */
    __IM  uint32_t            : 3;
    __IOM uint32_t hs_lcdc_en : 1;            /*!< [24..24] 1: Enable LCDC                                                   */
    __IOM uint32_t hs_lcdc_clk_en : 1;        /*!< [25..25] 1: Enable LCDC CLK                                               */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_lcdc_mux_en : 1;        /*!< [28..28] 1: Enable LCDC MUX                                               */
    __IOM uint32_t hs_lcdc_mode_sel : 1;      /*!< [29..29] 1: MCU (GPIOD_2~9, GPIOE_0~12); 0: RGB (GPIOD_2~9,
                                                   GPIOE_0~11)                                                               */
    __IOM uint32_t hs_rlcdc_en : 1;           /*!< [30..30] 1: Enable reduce pin of LCDC MCU mode : GPIOE_0~12
                                                   RGB mode : GPIOE_0~5, 8~11                                                */
  } b;                                        /*!< bit fields for syson_hs_isp_ctrl */
} syson_hs_isp_ctrl_t, *psyson_hs_isp_ctrl_t;

/**
  \brief Union type to access syson_hs_wl_ctrl (@ 0x00000240).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000240) HS WLAN Control Register                                   */
  
  struct {
    __IOM uint32_t hs_wl_axi_en : 1;          /*!< [0..0] 1: enable WL AXI function                                          */
    __IOM uint32_t hs_wlon_en : 1;            /*!< [1..1] 1: enable WLON and WL macro block                                  */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_wlaxi_clk_en : 1;       /*!< [4..4] 1: enable WL axi clock                                             */
    __IOM uint32_t hs_wlon_clk_en : 1;        /*!< [5..5] 1: enable WL clock                                                 */
    __IOM uint32_t hs_wl_32k_sel : 1;         /*!< [6..6] 0: Xtal, 1: LP_32K                                                 */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_wl_ant0_pin_en : 1;     /*!< [8..8] 1: Enable RFE_Ctrl 0 &1 (GPIOC_8, 9)                               */
    __IOM uint32_t hs_wl_ant1_pin_en : 1;     /*!< [9..9] 1: Enable RFE_Ctrl 2 &3 (GPIOC_10, 11)                             */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_wl_led0_pin_en : 1;     /*!< [12..12] 1: Enable LED0 MUX                                               */
    __IOM uint32_t hs_wl_led0_pin_sel : 2;    /*!< [14..13] LED is muxed on 00: GPIOC_0 01: GPIOC_1 10: GPIOC_8
                                                   11: GPIOC_9                                                               */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_btcoex_pin_en : 1;      /*!< [16..16] 1: Enable BTCOEX Pin                                             */
    __IOM uint32_t hs_btcoex_pin_sel : 2;     /*!< [18..17] BTCOEX is muxed to 00: GPIOH_8~11 01: GPIOC_8~11 10:
                                                   GPIOG_6~9 11: RSVD                                                        */
    __IOM uint32_t hs_btcmd_pin_en : 1;       /*!< [19..19] 1: Enable mailbox pin (GPIOH_12~14)                              */
    __IM  uint32_t            : 4;
    __IOM uint32_t hs_wlafe_pod33 : 1;        /*!< [24..24] 0: power down 33 WLAFE                                           */
    __IOM uint32_t hs_wlafe_pod125 : 1;       /*!< [25..25] 0: power down 125 WLAFE                                          */
  } b;                                        /*!< bit fields for syson_hs_wl_ctrl */
} syson_hs_wl_ctrl_t, *psyson_hs_wl_ctrl_t;

/**
  \brief Union type to access syson_hs_otg_ctrl (@ 0x00000244).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000244) HS OTG Control Register                                    */
  
  struct {
    __IOM uint32_t en         : 1;            /*!< [0..0] 1: enable OTG IP                                                   */
    __IOM uint32_t rst_mux    : 1;            /*!< [1..1] 1: Mask WDOG_RST                                                   */
    __IM  uint32_t            : 2;
    __IOM uint32_t clk_en     : 1;            /*!< [4..4] 1: OTG clock enable                                                */
    __IM  uint32_t            : 11;
    __IOM uint32_t usbd_en    : 1;            /*!< [16..16] 1: USB Digital power cut enable (USB PHY analog 1.2V
                                                   power cut enable)                                                         */
    __IM  uint32_t            : 1;
    __IOM uint32_t hv_en      : 1;            /*!< [18..18] 1: USB PHY analog 3.3V power cut enable                          */
    __IOM uint32_t bg_en      : 1;            /*!< [19..19] 1. Enable bandgap                                                */
    __IOM uint32_t usb_pdn33  : 1;            /*!< [20..20] 1: power down USB (LDOIO power down share it)                    */
    __IOM uint32_t ibx2_usb_en : 1;           /*!< [21..21] 1: Enable IBX to USB                                             */
    __IOM uint32_t ibx2_mipi_en : 1;          /*!< [22..22] 1: Enable IBX to MIPI                                            */
    __IM  uint32_t            : 1;
    __IOM uint32_t iso_usbd_en : 1;           /*!< [24..24] 1: enable usb digital isolation                                  */
    __IOM uint32_t iso_usba_en : 1;           /*!< [25..25] 1: enable usb analogy isolation                                  */
  } b;                                        /*!< bit fields for syson_hs_otg_ctrl */
} syson_hs_otg_ctrl_t, *psyson_hs_otg_ctrl_t;

/**
  \brief Union type to access syson_hs_sdio_ctrl (@ 0x00000248).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000248) HS SDIO Control Register                                   */
  
  struct {
    __IOM uint32_t hs_sdiod_on_en : 1;        /*!< [0..0] 1: enable SDIO device IP ON block                                  */
    __IOM uint32_t hs_sdiod_off_en : 1;       /*!< [1..1] 1: enable SDIO device IP OFF block                                 */
    __IOM uint32_t hs_sdio_dev_clk_en : 1;    /*!< [2..2] 1: enable SDIO DEV clock                                           */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_sdiod_on_rst_mux : 1;   /*!< [4..4] 1: Mask WDOG_RST                                                   */
    __IOM uint32_t hs_sdiod_pin_en : 1;       /*!< [5..5] SDIO Device Mode PINMUX enable (GPIOB_0~5)                         */
    __IOM uint32_t hs_sdiod_int_dis : 1;      /*!< [6..6] 1: disable SD_INT pin                                              */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_sdioh_en : 1;           /*!< [8..8] 1: enable SDIO host IP block                                       */
    __IOM uint32_t hs_sdio_hst_pclk_en : 1;   /*!< [9..9] 1: enable SDIO HST pclock                                          */
    __IOM uint32_t hs_sdio_hst_100m_en : 1;   /*!< [10..10] SDIO 100Mhz clock generator function enable                      */
    __IOM uint32_t hs_sdio_hst_sclk_en : 1;   /*!< [11..11] 1: Enable SDIO host SCLK                                         */
    __IM  uint32_t            : 4;
    __IOM uint32_t hs_sdio_clk1_phsel : 3;    /*!< [18..16] clk100m_vp0 phase shift selection                                */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_sdio_clk2_phsel : 3;    /*!< [22..20] clk100m_vp1 phase shift selection                                */
    __IM  uint32_t            : 1;
    __IM  uint32_t hs_sdio_ck100_rdy : 1;     /*!< [24..24] sdh_clk100m clock ready                                          */
    __IM  uint32_t hs_sdio_ck100_vp0_rdy : 1; /*!< [25..25] sdh_clk100m_vp0 clock ready                                      */
    __IM  uint32_t hs_sdio_ck100_vp1_rdy : 1; /*!< [26..26] sdh_clk100m_vp1 clock ready                                      */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_sdioh_pin_en : 1;       /*!< [28..28] SDIO Host Mode PINMUX enable                                     */
    __IOM uint32_t hs_sdioh_cd_wp_sel : 2;    /*!< [30..29] CMD, CLK, D0~3 on (GPIOB_0~5) CD, WP are muxed on 00:
                                                   GPIOB_6,7 01: GPIOF_10,4 10: GPIOG_0,1 11: RSVD                           */
    __IOM uint32_t sdh2d_lbk_en : 1;          /*!< [31..31] sdh2d loopback enable                                            */
  } b;                                        /*!< bit fields for syson_hs_sdio_ctrl */
} syson_hs_sdio_ctrl_t, *psyson_hs_sdio_ctrl_t;

/**
  \brief Union type to access syson_hs_mii_ctrl (@ 0x0000024C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000024C) HS MII Control Register                                    */
  
  struct {
    __IOM uint32_t hs_mii_en  : 1;            /*!< [0..0] 1: enable MII IP                                                   */
    __IOM uint32_t hs_mii_clk_en : 1;         /*!< [1..1] 1: MII clock enable                                                */
    __IOM uint32_t hs_mii_sclk_gen : 1;       /*!< [2..2] 1: Enable MII 50MHz                                                */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_mii_pin_en : 1;         /*!< [4..4] 1: MII PINMUX enable                                               */
    __IOM uint32_t hs_mii_mod_sel : 1;        /*!< [5..5] 0: MII 1: RMII                                                     */
    __IOM uint32_t hs_mii_mux_sel : 1;        /*!< [6..6] MII is muxed on 0: MII : GPIOB_0~6, GPIOC_10, 11, GPIOE_0~7
                                                   RMII : GPIOB_1~3,5,6, GPIOC_10, 11, GPIOE_0~2, 5~7 1: MII
                                                   : GPIOE_0~13 RMII : GPIOE_0~2, 5, 7~9, 11~13                              */
  } b;                                        /*!< bit fields for syson_hs_mii_ctrl */
} syson_hs_mii_ctrl_t, *psyson_hs_mii_ctrl_t;

/**
  \brief Union type to access syson_hs_uart_ctrl (@ 0x00000260).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000260) HS UART Control Register                                   */
  
  struct {
    __IOM uint32_t hs_uart0_en : 1;           /*!< [0..0] 1: Enable UART0                                                    */
    __IOM uint32_t hs_uart0_bd_en : 1;        /*!< [1..1] 1: Enable UART0 bus domain                                         */
    __IOM uint32_t hs_uart0_pclk_en : 1;      /*!< [2..2] 1: Enable UART0 PCLK                                               */
    __IOM uint32_t hs_uart0_sclk_en : 1;      /*!< [3..3] 1: Enable UART0 SCLK                                               */
    __IOM uint32_t hs_uart0_mux_en : 1;       /*!< [4..4] 1: UART 0 pin (TX and RX) enable                                   */
    __IOM uint32_t hs_uart0_flow_ctrl_en : 1; /*!< [5..5] 1. Enable RTS/CTS                                                  */
    __IOM uint32_t hs_uart0_mux_sel : 2;      /*!< [7..6] UART0 is muxed on 00: GPIOE_4~7 01: GPIOG_6~9 10: GPIOH_0~3
                                                   11: GPIOC_0~3                                                             */
    __IOM uint32_t hs_uart1_en : 1;           /*!< [8..8] 1: Enable UART1                                                    */
    __IOM uint32_t hs_uart1_bd_en : 1;        /*!< [9..9] 1: Enable UART1 bus domain                                         */
    __IOM uint32_t hs_uart1_pclk_en : 1;      /*!< [10..10] 1: Enable UART1 PCLK                                             */
    __IOM uint32_t hs_uart1_sclk_en : 1;      /*!< [11..11] 1: Enable UART1 SCLK                                             */
    __IOM uint32_t hs_uart1_mux_en : 1;       /*!< [12..12] 1: UART 1 pin (TX and RX) enable                                 */
    __IOM uint32_t hs_uart1_flow_ctrl_en : 1; /*!< [13..13] 1. Enable RTS/CTS                                                */
    __IOM uint32_t hs_uart1_mux_sel : 2;      /*!< [15..14] UART1 is muxed on 00: GPIOB_0~3 01: GPIOG_2~5 10: GPIOC_4~7
                                                   11: RSVD                                                                  */
    __IOM uint32_t hs_uart2_en : 1;           /*!< [16..16] 1: Enable UART2                                                  */
    __IOM uint32_t hs_uart2_bd_en : 1;        /*!< [17..17] 1: Enable UART2 bus domain                                       */
    __IOM uint32_t hs_uart2_pclk_en : 1;      /*!< [18..18] 1: Enable UART2 PCLK                                             */
    __IOM uint32_t hs_uart2_sclk_en : 1;      /*!< [19..19] 1: Enable UART2 SCLK                                             */
    __IOM uint32_t hs_uart2_mux_en : 1;       /*!< [20..20] 1: UART 2 pin (TX and RX) enable                                 */
    __IOM uint32_t hs_uart2_flow_ctrl_en : 1; /*!< [21..21] 1. Enable RTS/CTS                                                */
    __IOM uint32_t hs_uart2_mux_sel : 2;      /*!< [23..22] UART2 is muxed on 00: GPIOC_8~11 01: GPIOE_0~3 10:
                                                   GPIOH_4~7 11: RSVD                                                        */
  } b;                                        /*!< bit fields for syson_hs_uart_ctrl */
} syson_hs_uart_ctrl_t, *psyson_hs_uart_ctrl_t;

/**
  \brief Union type to access syson_hs_i2c_ctrl (@ 0x00000264).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000264) HS I2C Control Register                                    */
  
  struct {
    __IOM uint32_t i2c0_en    : 1;            /*!< [0..0] 1: Enable I2C0                                                     */
    __IOM uint32_t i2c0_pclk_en : 1;          /*!< [1..1] 1: Enable I2C0 PCLK                                                */
    __IOM uint32_t i2c0_sclk_en : 1;          /*!< [2..2] 1: Enable I2C0 SCLK                                                */
    __IM  uint32_t            : 1;
    __IOM uint32_t i2c0_mux_en : 1;           /*!< [4..4] 1: Enable I2C0 MUX                                                 */
    __IOM uint32_t i2c0_mux_sel : 2;          /*!< [6..5] I2C0 is muxed on 00: GPIOB_0~1 01: GPIOG_4~5 10: GPIOH_2~3
                                                   11: RSVD                                                                  */
    __IM  uint32_t            : 9;
    __IOM uint32_t i2c2_en    : 1;            /*!< [16..16] 1: Enable I2C2                                                   */
    __IOM uint32_t i2c2_pclk_en : 1;          /*!< [17..17] 1: Enable I2C2 PCLK                                              */
    __IOM uint32_t i2c2_sclk_en : 1;          /*!< [18..18] 1: Enable I2C2 SCLK                                              */
    __IM  uint32_t            : 1;
    __IOM uint32_t i2c2_mux_en : 1;           /*!< [20..20] 1: Enable I2C2 MUX                                               */
    __IOM uint32_t i2c2_mux_sel : 2;          /*!< [22..21] I2C2 is muxed on 00: GPIOB_2~3 01: GPIOG_6~7 10: GPIOE_14~15
                                                   11: RSVD                                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t i2c3_en    : 1;            /*!< [24..24] 1: Enable I2C3                                                   */
    __IOM uint32_t i2c3_pclk_en : 1;          /*!< [25..25] 1: Enable I2C3 PCLK                                              */
    __IOM uint32_t i2c3_sclk_en : 1;          /*!< [26..26] 1: Enable I2C3 SCLK                                              */
    __IM  uint32_t            : 1;
    __IOM uint32_t i2c3_mux_en : 1;           /*!< [28..28] 1: Enable I2C3 MUX                                               */
    __IOM uint32_t i2c3_mux_sel : 2;          /*!< [30..29] I2C3 is muxed on 00: GPIOB_4~5 01: GPIOG_8~9 10: GPIOF_10,
                                                   4 11: RSVD                                                                */
  } b;                                        /*!< bit fields for syson_hs_i2c_ctrl */
} syson_hs_i2c_ctrl_t, *psyson_hs_i2c_ctrl_t;

/**
  \brief Union type to access syson_hs_spi_ctrl (@ 0x00000268).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000268) SPI System Control Register                                */
  
  struct {
    __IOM uint32_t hs_spi0_en : 1;            /*!< [0..0] 1: Enable SPI0                                                     */
    __IOM uint32_t hs_spi0_clk_en : 1;        /*!< [1..1] 1: Enable SPI0 CLK                                                 */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_spi0_role_sel : 1;      /*!< [3..3] 1: master; 0: slave                                                */
    __IOM uint32_t hs_spi0_mux_en : 1;        /*!< [4..4] 1: Enable SPI0 MUX                                                 */
    __IOM uint32_t hs_spi0_cs_dis : 1;        /*!< [5..5] 1: Disable SPI0 CS                                                 */
    __IOM uint32_t hs_spi0_mux_sel : 2;       /*!< [7..6] SPI0 is muxed on 00: GPIOG_6~9 01: GPIOE_12~15 10: RSVD
                                                   11: RSVD                                                                  */
    __IOM uint32_t hs_spi1_en : 1;            /*!< [8..8] 1: Enable SPI1                                                     */
    __IOM uint32_t hs_spi1_clk_en : 1;        /*!< [9..9] 1: Enable SPI1 CLK                                                 */
    __IM  uint32_t            : 1;
    __IOM uint32_t hs_spi1_role_sel : 1;      /*!< [11..11] 1: master; 0: slave                                              */
    __IOM uint32_t hs_spi1_mux_en : 1;        /*!< [12..12] 1: Enable SPI1 MUX                                               */
    __IOM uint32_t hs_spi1_cs_dis : 1;        /*!< [13..13] 1: Disable SPI1 CS                                               */
    __IOM uint32_t hs_spi1_mux_sel : 2;       /*!< [15..14] SPI1 is muxed on 00: GPIOE_0~3 01: GPIOG_0~3 10: RSVD
                                                   11: RSVD                                                                  */
    __IOM uint32_t hs_spi2_en : 1;            /*!< [16..16] 1: Enable SPI2                                                   */
    __IOM uint32_t hs_spi2_clk_en : 1;        /*!< [17..17] 1: Enable SPI2 CLK                                               */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_spi2_mux_en : 1;        /*!< [20..20] 1: Enable SPI2 MUX                                               */
    __IOM uint32_t hs_spi2_cs_dis : 1;        /*!< [21..21] 1: Disable SPI2 CS                                               */
    __IOM uint32_t hs_spi2_mux_sel : 2;       /*!< [23..22] SPI2 is muxed on 00: GPIOB_0~3 01: GPIOC_0~3 10: RSVD
                                                   11: RSVD                                                                  */
    __IOM uint32_t hs_spi3_en : 1;            /*!< [24..24] 1: Enable SPI3                                                   */
    __IOM uint32_t hs_spi3_clk_en : 1;        /*!< [25..25] 1: Enable SPI3 CLK                                               */
    __IM  uint32_t            : 2;
    __IOM uint32_t hs_spi3_mux_en : 1;        /*!< [28..28] 1: Enable SPI3 MUX                                               */
    __IOM uint32_t hs_spi3_mux_sel : 2;       /*!< [30..29] SPI3 is muxed on 00: GPIOE_4~7 01: GPIOH_0~3 10: RSVD
                                                   11: RSVD                                                                  */
  } b;                                        /*!< bit fields for syson_hs_spi_ctrl */
} syson_hs_spi_ctrl_t, *psyson_hs_spi_ctrl_t;

/**
  \brief Union type to access syson_hs_i2s_ctrl (@ 0x00000270).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000270) HS I2S Control Register                                    */
  
  struct {
    __IOM uint32_t i2s0_en    : 1;            /*!< [0..0] 1: Enable I2S0                                                     */
    __IOM uint32_t i2s0_clk_en : 1;           /*!< [1..1] 1: Enable I2S0 CLK                                                 */
    __IOM uint32_t i2s0_mux_en : 1;           /*!< [2..2] 1: Enable I2S0 MUX                                                 */
    __IOM uint32_t i2s0_mclk_en : 1;          /*!< [3..3] Enable I2S0 Master Clock Output                                    */
    __IOM uint32_t i2s0_rx_en : 1;            /*!< [4..4] 1: Enable I2S0 RX                                                  */
    __IOM uint32_t i2s0_tx51_en : 1;          /*!< [5..5] 1: Enable I2S0 TX51                                                */
    __IOM uint32_t i2s0_mux_sel : 2;          /*!< [7..6] i2S0 is muxed to 00: GPIOE0~6 01: GPIOG0~6 10: RSVD 11:
                                                   RSVD                                                                      */
    __IOM uint32_t i2s1_en    : 1;            /*!< [8..8] 1: Enable I2S1                                                     */
    __IOM uint32_t i2s1_clk_en : 1;           /*!< [9..9] 1: Enable I2S1 CLK                                                 */
    __IOM uint32_t i2s1_mux_en : 1;           /*!< [10..10] 1: Enable I2S1 MUX                                               */
    __IOM uint32_t i2s1_mclk_en : 1;          /*!< [11..11] Enable I2S1 Master Clock Output                                  */
    __IOM uint32_t i2s1_rx_en : 1;            /*!< [12..12] 1: Enable I2S1 RX                                                */
    __IOM uint32_t i2s1_tx51_en : 1;          /*!< [13..13] 1: Enable I2S1 TX51                                              */
    __IOM uint32_t i2s1_mux_sel : 2;          /*!< [15..14] i2S1 is muxed to 00: GPIOB0~6 01: GPIOG5~9 10: RSVD
                                                   11: RSVD                                                                  */
  } b;                                        /*!< bit fields for syson_hs_i2s_ctrl */
} syson_hs_i2s_ctrl_t, *psyson_hs_i2s_ctrl_t;

/**
  \brief Union type to access syson_hs_pcm_ctrl (@ 0x00000274).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000274) HS PCM Control Register                                    */
  
  struct {
    __IOM uint32_t pcm0_en    : 1;            /*!< [0..0] 1: Enable PCM0                                                     */
    __IOM uint32_t pcm0_clk_en : 1;           /*!< [1..1] 1: Enable PCM0 CLK                                                 */
    __IM  uint32_t            : 2;
    __IOM uint32_t pcm0_mux_en : 1;           /*!< [4..4] 1: Enable PCM0 MUX                                                 */
    __IOM uint32_t pcm0_mux_sel : 2;          /*!< [6..5] PCM0 is muxed to 00: GPIOE0~3 01: GPIOG0~3 10: RSVD 11:
                                                   RSVD                                                                      */
    __IM  uint32_t            : 1;
    __IOM uint32_t pcm1_en    : 1;            /*!< [8..8] 1: Enable PCM1                                                     */
    __IOM uint32_t pcm1_clk_en : 1;           /*!< [9..9] 1: Enable PCM1 CLK                                                 */
    __IM  uint32_t            : 2;
    __IOM uint32_t pcm1_mux_en : 1;           /*!< [12..12] 1: Enable PCM1 MUX                                               */
    __IOM uint32_t pcm1_mux_sel : 2;          /*!< [14..13] PCM1 is muxed to 00: GPIOB0~3 01: GPIOG6~9 10: RSVD
                                                   11: RSVD                                                                  */
  } b;                                        /*!< bit fields for syson_hs_pcm_ctrl */
} syson_hs_pcm_ctrl_t, *psyson_hs_pcm_ctrl_t;

/**
  \brief Union type to access syson_hs_sgpio_ctrl (@ 0x00000278).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000278) HS SGPIO Control Register                                  */
  
  struct {
    __IOM uint32_t sgpio0_en  : 1;            /*!< [0..0] 1: Enable SGPIO0                                                   */
    __IOM uint32_t sgpio0_pclk_en : 1;        /*!< [1..1] 1: Enable SGPIO0 PCLK                                              */
    __IOM uint32_t sgpio0_sclk_en : 1;        /*!< [2..2] 1: Enable SGPIO0 SCLK                                              */
    __IM  uint32_t            : 1;
    __IOM uint32_t sgpio0_mux_en : 1;         /*!< [4..4] 1: Enable SGPIO0 MUX                                               */
    __IOM uint32_t sgpio0_mux_sel : 2;        /*!< [6..5] SGPIO0 is muxed to 00: GPIOB4~5 01: GPIOE0~1 10: GPIOE10~11
                                                   11: RSVD                                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t sgpio1_en  : 1;            /*!< [8..8] 1: Enable SGPIO1                                                   */
    __IOM uint32_t sgpio1_pclk_en : 1;        /*!< [9..9] 1: Enable SGPIO1 PCLK                                              */
    __IOM uint32_t sgpio1_sclk_en : 1;        /*!< [10..10] 1: Enable SGPIO1 SCLK                                            */
    __IM  uint32_t            : 1;
    __IOM uint32_t sgpio1_mux_en : 1;         /*!< [12..12] 1: Enable SGPIO1 MUX                                             */
    __IOM uint32_t sgpio1_mux_sel : 2;        /*!< [14..13] SGPIO1 is muxed to 00: GPIOC8~9 01: GPIOE2~3 10: GPIOE12~13
                                                   11: RSVD                                                                  */
    __IM  uint32_t            : 1;
    __IOM uint32_t sgpio2_en  : 1;            /*!< [16..16] 1: Enable SGPIO2                                                 */
    __IOM uint32_t sgpio2_pclk_en : 1;        /*!< [17..17] 1: Enable SGPIO2 PCLK                                            */
    __IOM uint32_t sgpio2_sclk_en : 1;        /*!< [18..18] 1: Enable SGPIO2 SCLK                                            */
    __IM  uint32_t            : 1;
    __IOM uint32_t sgpio2_mux_en : 1;         /*!< [20..20] 1: Enable SGPIO2 MUX                                             */
    __IOM uint32_t sgpio2_mux_sel : 2;        /*!< [22..21] SGPIO2 is muxed to 00: GPIOG8~9 01: GPIOE4~5 10: GPIOE14~15
                                                   11: RSVD                                                                  */
  } b;                                        /*!< bit fields for syson_hs_sgpio_ctrl */
} syson_hs_sgpio_ctrl_t, *psyson_hs_sgpio_ctrl_t;

/**
  \brief Union type to access syson_hs_i2c_rc_fltr_ctrl (@ 0x0000027C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000027C) I2C RC Filter Control Register                             */
  
  struct {
    __IOM uint32_t fltr_en    : 1;            /*!< [0..0] Filter Enable. 1: Enable, 0: Disable                               */
    __IOM uint32_t cal_in_en  : 1;            /*!< [1..1] RC Calibrate Input Enable. 1: Enable, 0: Disable                   */
    __IOM uint32_t ana_en     : 1;            /*!< [2..2] RC Filter Analog Enable. 1: Enable, 0: Disable                     */
  } b;                                        /*!< bit fields for syson_hs_i2c_rc_fltr_ctrl */
} syson_hs_i2c_rc_fltr_ctrl_t, *psyson_hs_i2c_rc_fltr_ctrl_t;

/**
  \brief Union type to access syson_hs_io_pad_pwd (@ 0x00000280).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000280) IO Pad Power Down Control Register                         */
  
  struct {
    __IOM uint32_t gpiob_padpwd : 1;          /*!< [0..0] 1: power down GPIO pad group B                                     */
    __IOM uint32_t gpioc_padpwd : 1;          /*!< [1..1] 1: power down GPIO pad group C                                     */
    __IOM uint32_t gpiod_padpwd : 1;          /*!< [2..2] 1: power down GPIO pad group D                                     */
    __IOM uint32_t gpioe_padpwd : 1;          /*!< [3..3] 1: power down GPIO pad group E                                     */
    __IOM uint32_t gpiof_padpwd : 1;          /*!< [4..4] 1: power down GPIO pad group F                                     */
    __IOM uint32_t gpiog_padpwd : 1;          /*!< [5..5] 1: power down GPIO pad group G                                     */
    __IOM uint32_t gpioh_padpwd : 1;          /*!< [6..6] 1: power down GPIO pad group H                                     */
    __IOM uint32_t gpioijk_padpwd : 1;        /*!< [7..7] 1: power down GPIO pad group IJK                                   */
  } b;                                        /*!< bit fields for syson_hs_io_pad_pwd */
} syson_hs_io_pad_pwd_t, *psyson_hs_io_pad_pwd_t;

/**
  \brief Union type to access syson_hs_io_pad_rstb (@ 0x00000284).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000284) IO Pad Reset Control Register                              */
  
  struct {
    __IOM uint32_t gpioijk_rstb33 : 1;        /*!< [0..0] 0: Reset GPIO pad Group IJK                                        */
  } b;                                        /*!< bit fields for syson_hs_io_pad_rstb */
} syson_hs_io_pad_rstb_t, *psyson_hs_io_pad_rstb_t;

/**
  \brief Union type to access syson_hs_io_pad_shdn (@ 0x00000288).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000288) IO Pad Shutdown Control Register                           */
  
  struct {
    __IOM uint32_t gpiod10_shdn_n : 1;        /*!< [0..0] 0: shutdown GPIOD10 PAD; 1: enable GPIOD10 PAD                     */
    __IOM uint32_t gpiod11_shdn_n : 1;        /*!< [1..1] 0: shutdown GPIOD11 PAD; 1: enable GPIOD11 PAD                     */
    __IOM uint32_t gpiod12_shdn_n : 1;        /*!< [2..2] 0: shutdown GPIOD12 PAD; 1: enable GPIOD12 PAD                     */
    __IOM uint32_t gpiod13_shdn_n : 1;        /*!< [3..3] 0: shutdown GPIOD13 PAD; 1: enable GPIOD13 PAD                     */
    __IOM uint32_t gpiod14_shdn_n : 1;        /*!< [4..4] 0: shutdown GPIOD14 PAD; 1: enable GPIOD14 PAD                     */
    __IOM uint32_t gpiod15_shdn_n : 1;        /*!< [5..5] 0: shutdown GPIOD15 PAD; 1: enable GPIOD15 PAD                     */
    __IM  uint32_t            : 10;
    __IOM uint32_t gpioh0_shdn_n : 1;         /*!< [16..16] 0: shutdown GPIOH0 PAD; 1: enable GPIOH0 PAD                     */
    __IOM uint32_t gpioh1_shdn_n : 1;         /*!< [17..17] 0: shutdown GPIOH1 PAD; 1: enable GPIOH1 PAD                     */
    __IOM uint32_t gpioh2_shdn_n : 1;         /*!< [18..18] 0: shutdown GPIOH2 PAD; 1: enable GPIOH2 PAD                     */
    __IOM uint32_t gpioh3_shdn_n : 1;         /*!< [19..19] 0: shutdown GPIOH3 PAD; 1: enable GPIOH3 PAD                     */
  } b;                                        /*!< bit fields for syson_hs_io_pad_shdn */
} syson_hs_io_pad_shdn_t, *psyson_hs_io_pad_shdn_t;

/**
  \brief Union type to access syson_pad_h3l1 (@ 0x0000028C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000028C) IO Pad H3L1 Register                                       */
  
  struct {
    __IOM uint32_t gpiob_h3l1_sel : 1;        /*!< [0..0] GPIO Group B Voltage Select: 0: 1.8V, 1: 3V                        */
    __IOM uint32_t gpioc_h3l1_sel : 1;        /*!< [1..1] GPIO Group C Voltage Select: 0: 1.8V, 1: 3V                        */
    __IOM uint32_t gpiod_h3l1_sel : 1;        /*!< [2..2] GPIO Group D Voltage Select: 0: 1.8V, 1: 3V                        */
    __IOM uint32_t gpioe_h3l1_sel : 1;        /*!< [3..3] GPIO Group E Voltage Select: 0: 1.8V, 1: 3V                        */
    __IOM uint32_t gpiof_h3l1_sel : 1;        /*!< [4..4] GPIO Group F Voltage Select: 0: 1.8V, 1: 3V                        */
    __IOM uint32_t gpiog_h3l1_sel : 1;        /*!< [5..5] GPIO Group G Voltage Select: 0: 1.8V, 1: 3V                        */
    __IOM uint32_t gpioh_h3l1_sel : 1;        /*!< [6..6] GPIO Group H Voltage Select: 0: 1.8V, 1: 3V                        */
  } b;                                        /*!< bit fields for syson_pad_h3l1 */
} syson_pad_h3l1_t, *psyson_pad_h3l1_t;

/**
  \brief Union type to access syson_pad_drv (@ 0x00000290).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000290) IO Pad Drive Current Control Register                      */
  
  struct {
    __IM  uint32_t            : 1;
    __IOM uint32_t gpioc_drv_sel : 1;         /*!< [1..1] GPIO Group C Driving Select: 0: 8mA, 1: 16mA                       */
    __IOM uint32_t gpiod_drv_sel : 1;         /*!< [2..2] GPIO Group D Driving Select: 0: 8mA, 1: 16mA                       */
    __IOM uint32_t gpioe_drv_sel : 1;         /*!< [3..3] GPIO Group E Driving Select: 0: 8mA, 1: 16mA                       */
    __IOM uint32_t gpiof_drv_sel : 1;         /*!< [4..4] GPIO Group F Driving Select: 0: 8mA, 1: 16mA                       */
    __IOM uint32_t gpiog_drv_sel : 1;         /*!< [5..5] GPIO Group G Driving Select: 0: 8mA, 1: 16mA                       */
    __IOM uint32_t gpioh_drv_sel : 1;         /*!< [6..6] GPIO Group H Driving Select: 0: 8mA, 1: 16mA                       */
    __IM  uint32_t            : 1;
    __IOM uint32_t gpiob_drv_sel : 4;         /*!< [11..8] GPIO Group B Driving Select: VDIO = 1.8 VDIO =3.3 0000:
                                                   1mA 3mA 0001: 2mA 6mA 0011: 4mA 12mA 0101: 6mA 18mA 0111:
                                                   8mA 1101: 10mA 1111: 12mA BIT0=N2E. BIT1 =N3E, BIT2=N4E,
                                                   BIT3=N5E                                                                  */
  } b;                                        /*!< bit fields for syson_pad_drv */
} syson_pad_drv_t, *psyson_pad_drv_t;

/**
  \brief Union type to access syson_hs_gpiob_pull_ctrl (@ 0x000002A0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002A0) GPIOB Pull Control Register                                */
  
  struct {
    __IOM uint32_t gpiob0_pull_ctrl : 2;      /*!< [1..0] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t gpiob1_pull_ctrl : 2;      /*!< [3..2] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t gpiob2_pull_ctrl : 2;      /*!< [5..4] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t gpiob3_pull_ctrl : 2;      /*!< [7..6] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t gpiob4_pull_ctrl : 2;      /*!< [9..8] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t gpiob5_pull_ctrl : 2;      /*!< [11..10] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t gpiob6_pull_ctrl : 2;      /*!< [13..12] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t gpiob7_pull_ctrl : 2;      /*!< [15..14] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
  } b;                                        /*!< bit fields for syson_hs_gpiob_pull_ctrl */
} syson_hs_gpiob_pull_ctrl_t, *psyson_hs_gpiob_pull_ctrl_t;

/**
  \brief Union type to access syson_hs_gpioc_pull_ctrl (@ 0x000002A4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002A4) GPIOC Pull Control Register                                */
  
  struct {
    __IOM uint32_t bit_gpioc0_pull_ctrl : 2;  /*!< [1..0] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioc1_pull_ctrl : 2;  /*!< [3..2] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioc2_pull_ctrl : 2;  /*!< [5..4] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioc3_pull_ctrl : 2;  /*!< [7..6] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioc4_pull_ctrl : 2;  /*!< [9..8] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioc5_pull_ctrl : 2;  /*!< [11..10] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioc6_pull_ctrl : 2;  /*!< [13..12] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioc7_pull_ctrl : 2;  /*!< [15..14] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioc8_pull_ctrl : 2;  /*!< [17..16] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioc9_pull_ctrl : 2;  /*!< [19..18] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioc10_pull_ctrl : 2; /*!< [21..20] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioc11_pull_ctrl : 2; /*!< [23..22] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
  } b;                                        /*!< bit fields for syson_hs_gpioc_pull_ctrl */
} syson_hs_gpioc_pull_ctrl_t, *psyson_hs_gpioc_pull_ctrl_t;

/**
  \brief Union type to access syson_hs_gpiod_pull_ctrl (@ 0x000002A8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002A8) GPIOD Pull Control Register                                */
  
  struct {
    __IOM uint32_t bit_gpiod0_pull_ctrl : 2;  /*!< [1..0] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiod1_pull_ctrl : 2;  /*!< [3..2] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiod2_pull_ctrl : 2;  /*!< [5..4] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiod3_pull_ctrl : 2;  /*!< [7..6] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiod4_pull_ctrl : 2;  /*!< [9..8] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiod5_pull_ctrl : 2;  /*!< [11..10] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiod6_pull_ctrl : 2;  /*!< [13..12] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiod7_pull_ctrl : 2;  /*!< [15..14] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiod8_pull_ctrl : 2;  /*!< [17..16] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiod9_pull_ctrl : 2;  /*!< [19..18] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiod10_pull_ctrl : 2; /*!< [21..20] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiod11_pull_ctrl : 2; /*!< [23..22] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiod12_pull_ctrl : 2; /*!< [25..24] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiod13_pull_ctrl : 2; /*!< [27..26] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiod14_pull_ctrl : 2; /*!< [29..28] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiod15_pull_ctrl : 2; /*!< [31..30] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
  } b;                                        /*!< bit fields for syson_hs_gpiod_pull_ctrl */
} syson_hs_gpiod_pull_ctrl_t, *psyson_hs_gpiod_pull_ctrl_t;

/**
  \brief Union type to access syson_hs_gpioe_pull_ctrl (@ 0x000002AC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002AC) GPIOE Pull Control Register                                */
  
  struct {
    __IOM uint32_t bit_gpioe0_pull_ctrl : 2;  /*!< [1..0] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioe1_pull_ctrl : 2;  /*!< [3..2] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioe2_pull_ctrl : 2;  /*!< [5..4] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioe3_pull_ctrl : 2;  /*!< [7..6] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioe4_pull_ctrl : 2;  /*!< [9..8] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioe5_pull_ctrl : 2;  /*!< [11..10] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioe6_pull_ctrl : 2;  /*!< [13..12] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioe7_pull_ctrl : 2;  /*!< [15..14] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioe8_pull_ctrl : 2;  /*!< [17..16] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioe9_pull_ctrl : 2;  /*!< [19..18] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioe10_pull_ctrl : 2; /*!< [21..20] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioe11_pull_ctrl : 2; /*!< [23..22] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioe12_pull_ctrl : 2; /*!< [25..24] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioe13_pull_ctrl : 2; /*!< [27..26] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioe14_pull_ctrl : 2; /*!< [29..28] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioe15_pull_ctrl : 2; /*!< [31..30] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
  } b;                                        /*!< bit fields for syson_hs_gpioe_pull_ctrl */
} syson_hs_gpioe_pull_ctrl_t, *psyson_hs_gpioe_pull_ctrl_t;

/**
  \brief Union type to access syson_hs_gpiof_pull_ctrl (@ 0x000002B0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002B0) GPIOF Pull Control Register                                */
  
  struct {
    __IOM uint32_t bit_gpiof0_pull_ctrl : 2;  /*!< [1..0] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiof1_pull_ctrl : 2;  /*!< [3..2] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiof2_pull_ctrl : 2;  /*!< [5..4] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiof3_pull_ctrl : 2;  /*!< [7..6] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiof4_pull_ctrl : 2;  /*!< [9..8] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiof5_pull_ctrl : 2;  /*!< [11..10] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiof6_pull_ctrl : 2;  /*!< [13..12] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiof7_pull_ctrl : 2;  /*!< [15..14] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiof8_pull_ctrl : 2;  /*!< [17..16] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiof9_pull_ctrl : 2;  /*!< [19..18] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiof10_pull_ctrl : 2; /*!< [21..20] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
  } b;                                        /*!< bit fields for syson_hs_gpiof_pull_ctrl */
} syson_hs_gpiof_pull_ctrl_t, *psyson_hs_gpiof_pull_ctrl_t;

/**
  \brief Union type to access syson_hs_gpiog_pull_ctrl (@ 0x000002B4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002B4) GPIOG Pull Control Register                                */
  
  struct {
    __IOM uint32_t bit_gpiog0_pull_ctrl : 2;  /*!< [1..0] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiog1_pull_ctrl : 2;  /*!< [3..2] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiog2_pull_ctrl : 2;  /*!< [5..4] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiog3_pull_ctrl : 2;  /*!< [7..6] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiog4_pull_ctrl : 2;  /*!< [9..8] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpiog5_pull_ctrl : 2;  /*!< [11..10] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiog6_pull_ctrl : 2;  /*!< [13..12] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiog7_pull_ctrl : 2;  /*!< [15..14] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiog8_pull_ctrl : 2;  /*!< [17..16] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpiog9_pull_ctrl : 2;  /*!< [19..18] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
  } b;                                        /*!< bit fields for syson_hs_gpiog_pull_ctrl */
} syson_hs_gpiog_pull_ctrl_t, *psyson_hs_gpiog_pull_ctrl_t;

/**
  \brief Union type to access syson_hs_gpioh_pull_ctrl (@ 0x000002B8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002B8) GPIOH Pull Control Register                                */
  
  struct {
    __IOM uint32_t bit_gpioh0_pull_ctrl : 2;  /*!< [1..0] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioh1_pull_ctrl : 2;  /*!< [3..2] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioh2_pull_ctrl : 2;  /*!< [5..4] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioh3_pull_ctrl : 2;  /*!< [7..6] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioh4_pull_ctrl : 2;  /*!< [9..8] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull high;
                                                   2b'11: reserved                                                           */
    __IOM uint32_t bit_gpioh5_pull_ctrl : 2;  /*!< [11..10] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioh6_pull_ctrl : 2;  /*!< [13..12] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioh7_pull_ctrl : 2;  /*!< [15..14] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioh8_pull_ctrl : 2;  /*!< [17..16] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioh9_pull_ctrl : 2;  /*!< [19..18] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioh10_pull_ctrl : 2; /*!< [21..20] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioh11_pull_ctrl : 2; /*!< [23..22] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioh12_pull_ctrl : 2; /*!< [25..24] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioh13_pull_ctrl : 2; /*!< [27..26] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
    __IOM uint32_t bit_gpioh14_pull_ctrl : 2; /*!< [29..28] 2b'00: high impedence; 2b'01: pull low; 2b'10: pull
                                                   high; 2b'11: reserved                                                     */
  } b;                                        /*!< bit fields for syson_hs_gpioh_pull_ctrl */
} syson_hs_gpioh_pull_ctrl_t, *psyson_hs_gpioh_pull_ctrl_t;

/**
  \brief Union type to access syson_hs_gpiob_smt_ctrl (@ 0x000002C0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002C0) GPIOB Schmitt Trigger Control Register                     */
  
  struct {
    __IOM uint32_t bit_gpiob0_smt_en : 1;     /*!< [0..0] Enable GPIOB0 schmitt trigger                                      */
    __IOM uint32_t bit_gpiob1_smt_en : 1;     /*!< [1..1] Enable GPIOB1 schmitt trigger                                      */
    __IOM uint32_t bit_gpiob2_smt_en : 1;     /*!< [2..2] Enable GPIOB2 schmitt trigger                                      */
    __IOM uint32_t bit_gpiob3_smt_en : 1;     /*!< [3..3] Enable GPIOB3 schmitt trigger                                      */
    __IOM uint32_t bit_gpiob4_smt_en : 1;     /*!< [4..4] Enable GPIOB4 schmitt trigger                                      */
    __IOM uint32_t bit_gpiob5_smt_en : 1;     /*!< [5..5] Enable GPIOB5 schmitt trigger                                      */
    __IOM uint32_t bit_gpiob6_smt_en : 1;     /*!< [6..6] Enable GPIOB6 schmitt trigger                                      */
    __IOM uint32_t bit_gpiob7_smt_en : 1;     /*!< [7..7] Enable GPIOB7 schmitt trigger                                      */
  } b;                                        /*!< bit fields for syson_hs_gpiob_smt_ctrl */
} syson_hs_gpiob_smt_ctrl_t, *psyson_hs_gpiob_smt_ctrl_t;

/**
  \brief Union type to access syson_hs_gpioc_smt_ctrl (@ 0x000002C4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002C4) GPIOC Schmitt Trigger Control Register                     */
  
  struct {
    __IOM uint32_t bit_gpioc0_smt_en : 1;     /*!< [0..0] Enable GPIOC0 schmitt trigger                                      */
    __IOM uint32_t bit_gpioc1_smt_en : 1;     /*!< [1..1] Enable GPIOC1 schmitt trigger                                      */
    __IOM uint32_t bit_gpioc2_smt_en : 1;     /*!< [2..2] Enable GPIOC2 schmitt trigger                                      */
    __IOM uint32_t bit_gpioc3_smt_en : 1;     /*!< [3..3] Enable GPIOC3 schmitt trigger                                      */
    __IOM uint32_t bit_gpioc4_smt_en : 1;     /*!< [4..4] Enable GPIOC4 schmitt trigger                                      */
    __IOM uint32_t bit_gpioc5_smt_en : 1;     /*!< [5..5] Enable GPIOC5 schmitt trigger                                      */
    __IOM uint32_t bit_gpioc6_smt_en : 1;     /*!< [6..6] Enable GPIOC6 schmitt trigger                                      */
    __IOM uint32_t bit_gpioc7_smt_en : 1;     /*!< [7..7] Enable GPIOC7 schmitt trigger                                      */
    __IOM uint32_t bit_gpioc8_smt_en : 1;     /*!< [8..8] Enable GPIOC8 schmitt trigger                                      */
    __IOM uint32_t bit_gpioc9_smt_en : 1;     /*!< [9..9] Enable GPIOC9 schmitt trigger                                      */
    __IOM uint32_t bit_gpioc10_smt_en : 1;    /*!< [10..10] Enable GPIOC10 schmitt trigger                                   */
    __IOM uint32_t bit_gpioc11_smt_en : 1;    /*!< [11..11] Enable GPIOC11 schmitt trigger                                   */
  } b;                                        /*!< bit fields for syson_hs_gpioc_smt_ctrl */
} syson_hs_gpioc_smt_ctrl_t, *psyson_hs_gpioc_smt_ctrl_t;

/**
  \brief Union type to access syson_hs_gpiod_smt_ctrl (@ 0x000002C8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002C8) GPIOD Schmitt Trigger Control Register                     */
  
  struct {
    __IOM uint32_t bit_gpiod0_smt_en : 1;     /*!< [0..0] Enable GPIOD0 schmitt trigger                                      */
    __IOM uint32_t bit_gpiod1_smt_en : 1;     /*!< [1..1] Enable GPIOD1 schmitt trigger                                      */
    __IOM uint32_t bit_gpiod2_smt_en : 1;     /*!< [2..2] Enable GPIOD2 schmitt trigger                                      */
    __IOM uint32_t bit_gpiod3_smt_en : 1;     /*!< [3..3] Enable GPIOD3 schmitt trigger                                      */
    __IOM uint32_t bit_gpiod4_smt_en : 1;     /*!< [4..4] Enable GPIOD4 schmitt trigger                                      */
    __IOM uint32_t bit_gpiod5_smt_en : 1;     /*!< [5..5] Enable GPIOD5 schmitt trigger                                      */
    __IOM uint32_t bit_gpiod6_smt_en : 1;     /*!< [6..6] Enable GPIOD6 schmitt trigger                                      */
    __IOM uint32_t bit_gpiod7_smt_en : 1;     /*!< [7..7] Enable GPIOD7 schmitt trigger                                      */
    __IOM uint32_t bit_gpiod8_smt_en : 1;     /*!< [8..8] Enable GPIOD8 schmitt trigger                                      */
    __IOM uint32_t bit_gpiod9_smt_en : 1;     /*!< [9..9] Enable GPIOD9 schmitt trigger                                      */
    __IOM uint32_t bit_gpiod10_smt_en : 1;    /*!< [10..10] Enable GPIOD10 schmitt trigger                                   */
    __IOM uint32_t bit_gpiod11_smt_en : 1;    /*!< [11..11] Enable GPIOD11 schmitt trigger                                   */
    __IOM uint32_t bit_gpiod12_smt_en : 1;    /*!< [12..12] Enable GPIOD12 schmitt trigger                                   */
    __IOM uint32_t bit_gpiod13_smt_en : 1;    /*!< [13..13] Enable GPIOD13 schmitt trigger                                   */
    __IOM uint32_t bit_gpiod14_smt_en : 1;    /*!< [14..14] Enable GPIOD14 schmitt trigger                                   */
    __IOM uint32_t bit_gpiod15_smt_en : 1;    /*!< [15..15] Enable GPIOD15 schmitt trigger                                   */
  } b;                                        /*!< bit fields for syson_hs_gpiod_smt_ctrl */
} syson_hs_gpiod_smt_ctrl_t, *psyson_hs_gpiod_smt_ctrl_t;

/**
  \brief Union type to access syson_hs_gpioe_smt_ctrl (@ 0x000002CC).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002CC) GPIOE Schmitt Trigger Control Register                     */
  
  struct {
    __IOM uint32_t bit_gpioe0_smt_en : 1;     /*!< [0..0] Enable GPIOE0 schmitt trigger                                      */
    __IOM uint32_t bit_gpioe1_smt_en : 1;     /*!< [1..1] Enable GPIOE1 schmitt trigger                                      */
    __IOM uint32_t bit_gpioe2_smt_en : 1;     /*!< [2..2] Enable GPIOE2 schmitt trigger                                      */
    __IOM uint32_t bit_gpioe3_smt_en : 1;     /*!< [3..3] Enable GPIOE3 schmitt trigger                                      */
    __IOM uint32_t bit_gpioe4_smt_en : 1;     /*!< [4..4] Enable GPIOE4 schmitt trigger                                      */
    __IOM uint32_t bit_gpioe5_smt_en : 1;     /*!< [5..5] Enable GPIOE5 schmitt trigger                                      */
    __IOM uint32_t bit_gpioe6_smt_en : 1;     /*!< [6..6] Enable GPIOE6 schmitt trigger                                      */
    __IOM uint32_t bit_gpioe7_smt_en : 1;     /*!< [7..7] Enable GPIOE7 schmitt trigger                                      */
    __IOM uint32_t bit_gpioe8_smt_en : 1;     /*!< [8..8] Enable GPIOE8 schmitt trigger                                      */
    __IOM uint32_t bit_gpioe9_smt_en : 1;     /*!< [9..9] Enable GPIOE9 schmitt trigger                                      */
    __IOM uint32_t bit_gpioe10_smt_en : 1;    /*!< [10..10] Enable GPIOE10 schmitt trigger                                   */
    __IOM uint32_t bit_gpioe11_smt_en : 1;    /*!< [11..11] Enable GPIOE11 schmitt trigger                                   */
    __IOM uint32_t bit_gpioe12_smt_en : 1;    /*!< [12..12] Enable GPIOE12 schmitt trigger                                   */
    __IOM uint32_t bit_gpioe13_smt_en : 1;    /*!< [13..13] Enable GPIOE13 schmitt trigger                                   */
    __IOM uint32_t bit_gpioe14_smt_en : 1;    /*!< [14..14] Enable GPIOE14 schmitt trigger                                   */
    __IOM uint32_t bit_gpioe15_smt_en : 1;    /*!< [15..15] Enable GPIOE15 schmitt trigger                                   */
  } b;                                        /*!< bit fields for syson_hs_gpioe_smt_ctrl */
} syson_hs_gpioe_smt_ctrl_t, *psyson_hs_gpioe_smt_ctrl_t;

/**
  \brief Union type to access syson_hs_gpiof_smt_ctrl (@ 0x000002D0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002D0) GPIOF Schmitt Trigger Control Register                     */
  
  struct {
    __IOM uint32_t bit_gpiof0_smt_en : 1;     /*!< [0..0] Enable GPIOF0 schmitt trigger                                      */
    __IOM uint32_t bit_gpiof1_smt_en : 1;     /*!< [1..1] Enable GPIOF1 schmitt trigger                                      */
    __IOM uint32_t bit_gpiof2_smt_en : 1;     /*!< [2..2] Enable GPIOF2 schmitt trigger                                      */
    __IOM uint32_t bit_gpiof3_smt_en : 1;     /*!< [3..3] Enable GPIOF3 schmitt trigger                                      */
    __IOM uint32_t bit_gpiof4_smt_en : 1;     /*!< [4..4] Enable GPIOF4 schmitt trigger                                      */
    __IOM uint32_t bit_gpiof5_smt_en : 1;     /*!< [5..5] Enable GPIOF5 schmitt trigger                                      */
    __IOM uint32_t bit_gpiof6_smt_en : 1;     /*!< [6..6] Enable GPIOF6 schmitt trigger                                      */
    __IOM uint32_t bit_gpiof7_smt_en : 1;     /*!< [7..7] Enable GPIOF7 schmitt trigger                                      */
    __IOM uint32_t bit_gpiof8_smt_en : 1;     /*!< [8..8] Enable GPIOF8 schmitt trigger                                      */
    __IOM uint32_t bit_gpiof9_smt_en : 1;     /*!< [9..9] Enable GPIOF9 schmitt trigger                                      */
    __IOM uint32_t bit_gpiof10_smt_en : 1;    /*!< [10..10] Enable GPIOF10 schmitt trigger                                   */
  } b;                                        /*!< bit fields for syson_hs_gpiof_smt_ctrl */
} syson_hs_gpiof_smt_ctrl_t, *psyson_hs_gpiof_smt_ctrl_t;

/**
  \brief Union type to access syson_hs_gpiog_smt_ctrl (@ 0x000002D4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002D4) GPIOG Schmitt Trigger Control Register                     */
  
  struct {
    __IOM uint32_t bit_gpiog0_smt_en : 1;     /*!< [0..0] Enable GPIOG0 schmitt trigger                                      */
    __IOM uint32_t bit_gpiog1_smt_en : 1;     /*!< [1..1] Enable GPIOG1 schmitt trigger                                      */
    __IOM uint32_t bit_gpiog2_smt_en : 1;     /*!< [2..2] Enable GPIOG2 schmitt trigger                                      */
    __IOM uint32_t bit_gpiog3_smt_en : 1;     /*!< [3..3] Enable GPIOG3 schmitt trigger                                      */
    __IOM uint32_t bit_gpiog4_smt_en : 1;     /*!< [4..4] Enable GPIOG4 schmitt trigger                                      */
    __IOM uint32_t bit_gpiog5_smt_en : 1;     /*!< [5..5] Enable GPIOG5 schmitt trigger                                      */
    __IOM uint32_t bit_gpiog6_smt_en : 1;     /*!< [6..6] Enable GPIOG6 schmitt trigger                                      */
    __IOM uint32_t bit_gpiog7_smt_en : 1;     /*!< [7..7] Enable GPIOG7 schmitt trigger                                      */
    __IOM uint32_t bit_gpiog8_smt_en : 1;     /*!< [8..8] Enable GPIOG8 schmitt trigger                                      */
    __IOM uint32_t bit_gpiog9_smt_en : 1;     /*!< [9..9] Enable GPIOG9 schmitt trigger                                      */
  } b;                                        /*!< bit fields for syson_hs_gpiog_smt_ctrl */
} syson_hs_gpiog_smt_ctrl_t, *psyson_hs_gpiog_smt_ctrl_t;

/**
  \brief Union type to access syson_hs_gpioh_smt_ctrl (@ 0x000002D8).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000002D8) GPIOH Schmitt Trigger Control Register                     */
  
  struct {
    __IOM uint32_t bit_gpioh0_smt_en : 1;     /*!< [0..0] Enable GPIOH0 schmitt trigger                                      */
    __IOM uint32_t bit_gpioh1_smt_en : 1;     /*!< [1..1] Enable GPIOH1 schmitt trigger                                      */
    __IOM uint32_t bit_gpioh2_smt_en : 1;     /*!< [2..2] Enable GPIOH2 schmitt trigger                                      */
    __IOM uint32_t bit_gpioh3_smt_en : 1;     /*!< [3..3] Enable GPIOH3 schmitt trigger                                      */
    __IOM uint32_t bit_gpioh4_smt_en : 1;     /*!< [4..4] Enable GPIOH4 schmitt trigger                                      */
    __IOM uint32_t bit_gpioh5_smt_en : 1;     /*!< [5..5] Enable GPIOH5 schmitt trigger                                      */
    __IOM uint32_t bit_gpioh6_smt_en : 1;     /*!< [6..6] Enable GPIOH6 schmitt trigger                                      */
    __IOM uint32_t bit_gpioh7_smt_en : 1;     /*!< [7..7] Enable GPIOH7 schmitt trigger                                      */
    __IOM uint32_t bit_gpioh8_smt_en : 1;     /*!< [8..8] Enable GPIOH8 schmitt trigger                                      */
    __IOM uint32_t bit_gpioh9_smt_en : 1;     /*!< [9..9] Enable GPIOH9 schmitt trigger                                      */
    __IOM uint32_t bit_gpioh10_smt_en : 1;    /*!< [10..10] Enable GPIOH10 schmitt trigger                                   */
    __IOM uint32_t bit_gpioh11_smt_en : 1;    /*!< [11..11] Enable GPIOH11 schmitt trigger                                   */
    __IOM uint32_t bit_gpioh12_smt_en : 1;    /*!< [12..12] Enable GPIOH12 schmitt trigger                                   */
    __IOM uint32_t bit_gpioh13_smt_en : 1;    /*!< [13..13] Enable GPIOH13 schmitt trigger                                   */
    __IOM uint32_t bit_gpioh14_smt_en : 1;    /*!< [14..14] Enable GPIOH14 schmitt trigger                                   */
  } b;                                        /*!< bit fields for syson_hs_gpioh_smt_ctrl */
} syson_hs_gpioh_smt_ctrl_t, *psyson_hs_gpioh_smt_ctrl_t;

/** @} */ /* End of group hs_hal_syson_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_SYSON_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_SYSON_SYSON_TYPE_H_

