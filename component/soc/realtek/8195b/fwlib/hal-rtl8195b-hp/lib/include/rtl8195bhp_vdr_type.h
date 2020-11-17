/**************************************************************************//**
 * @file      rtl8195bhp_vdr_type.h
 * @brief
 * @version   V1.00
 * @date      2017-11-1 11:52:15
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

#ifndef _RTL8195BHP_VENDOR_VDR_TYPE_H_
#define _RTL8195BHP_VENDOR_VDR_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_VDR_REG_TYPE

/**
 * @addtogroup hs_hal_vdr_reg VDR Registers.
 * @ingroup hs_hal_vdr
 * @{
 */

/**
  \brief Union type to access vdr_watch_dog_tmr (@ 0x00000000).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000000) Watch Dog Timer Register                                   */
  
  struct {
    __IOM uint32_t vndr_divfactor : 16;       /*!< [15..0] Dividing factor. Watch dog timer is count with 32.768KHz/(divfactor+1)
                                                   Minimum dividing factor is 1.                                             */
    __IOM uint32_t wdt_en     : 1;            /*!< [16..16] Set 1 to enable watch dog timer                                  */
    __IM  uint32_t            : 7;
    __OM  uint32_t wdt_clear  : 1;            /*!< [24..24] Write 1 to clear timer                                           */
    __IOM uint32_t cnt_limit  : 4;            /*!< [28..25] 0: 0x001 1: 0x003 2: 0x007 3: 0x00F 4: 0x01F 5: 0x03F
                                                   6: 0x07F 7: 0x0FF 8: 0x1FF 9: 0x3FF 10: 0x7FF 11~15: 0xFFF                */
    __IM  uint32_t            : 1;
    __IOM uint32_t wdt_mode   : 1;            /*!< [30..30] 1: Reset system, 0: Interrupt CPU                                */
    __IOM uint32_t wdt_to     : 1;            /*!< [31..31] Watch dog timer timeout. 1 cycle pulse                           */
  } b;                                        /*!< bit fields for vdr_watch_dog_tmr */
} vdr_watch_dog_tmr_t, *pvdr_watch_dog_tmr_t;

/**
  \brief Union type to access vdr_low_pri_int_mode (@ 0x00000004).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000004) Low Priority Interrupt Mode Register                       */
  
  struct {
    __IOM uint32_t low_pri_int_mode : 32;     /*!< [31..0] Each bit control corresponding interrupt mode. 1: Rising
                                                   edge trigger 0: High level active                                         */
  } b;                                        /*!< bit fields for vdr_low_pri_int_mode */
} vdr_low_pri_int_mode_t, *pvdr_low_pri_int_mode_t;

/**
  \brief Union type to access vdr_low_pri_int_imr (@ 0x00000008).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000008) Low Priority Interrupt Mask Register                       */
  
  struct {
    __IOM uint32_t low_pri_int_imr : 32;      /*!< [31..0] Each bit enable corresponding interrupt. 1: Enable 0:
                                                   Disable                                                                   */
  } b;                                        /*!< bit fields for vdr_low_pri_int_imr */
} vdr_low_pri_int_imr_t, *pvdr_low_pri_int_imr_t;

/**
  \brief Union type to access vdr_low_pri_int_isr (@ 0x0000000C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000000C) Low Priority Interrupt Status Register                     */
  
  struct {
    __IOM uint32_t wdt_voe    : 1;            /*!< [0..0] watchdog reset event of VOE                                        */
    __IOM uint32_t wdt_wl     : 1;            /*!< [1..1] watchdog reset event of WL                                         */
    __IOM uint32_t bst_ocp    : 1;            /*!< [2..2] indicate BST OCP event interrupt status                            */
    __IOM uint32_t swr_ocp    : 1;            /*!< [3..3] indicate SWR_M OCP event interrupt status                          */
    __IM  uint32_t            : 5;
    __IOM uint32_t rxi_bus    : 1;            /*!< [9..9] rxi bus interrupt status                                           */
    __IM  uint32_t            : 6;
    __IOM uint32_t ddrphy_dpi_int0 : 1;       /*!< [16..16] DDR PHY DPI INT0 Status                                          */
    __IOM uint32_t ddrphy_dpi_int1 : 1;       /*!< [17..17] DDR PHY DPI INT1 Status                                          */
    __IOM uint32_t ddrphy_dpi_int2 : 1;       /*!< [18..18] DDR PHY DPI INT2 Status                                          */
    __IOM uint32_t ddrphy_dpi_int3 : 1;       /*!< [19..19] DDR PHY DPI INT3 Status                                          */
  } b;                                        /*!< bit fields for vdr_low_pri_int_isr */
} vdr_low_pri_int_isr_t, *pvdr_low_pri_int_isr_t;

/**
  \brief Union type to access vdr_debug_sel (@ 0x0000001C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000001C) Debug Select Register                                      */
  
  struct {
    __IOM uint32_t debug_sel  : 12;           /*!< [11..0] Debug selection                                                   */
  } b;                                        /*!< bit fields for vdr_debug_sel */
} vdr_debug_sel_t, *pvdr_debug_sel_t;

/**
  \brief Union type to access vdr_i2c_dat_swp_ctrl (@ 0x00000020).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000020) I2C Data FIFO Swap Control Register                        */
  
  struct {
    __IOM uint32_t i2c0_tx_swp_en : 1;        /*!< [0..0] TX bit swap enable for I2C0                                        */
    __IOM uint32_t i2c0_rx_swp_en : 1;        /*!< [1..1] RX bit swap enable for I2C0                                        */
    __IM  uint32_t            : 2;
    __IOM uint32_t i2c2_tx_swp_en : 1;        /*!< [4..4] TX bit swap enable for I2C2                                        */
    __IOM uint32_t i2c2_rx_swp_en : 1;        /*!< [5..5] RX bit swap enable for I2C2                                        */
    __IOM uint32_t i2c3_tx_swp_en : 1;        /*!< [6..6] TX bit swap enable for I2C3                                        */
    __IOM uint32_t i2c3_rx_swp_en : 1;        /*!< [7..7] RX bit swap enable for I2C3                                        */
  } b;                                        /*!< bit fields for vdr_i2c_dat_swp_ctrl */
} vdr_i2c_dat_swp_ctrl_t, *pvdr_i2c_dat_swp_ctrl_t;

/**
  \brief Union type to access vdr_i2c_dglch_ctrl (@ 0x00000024).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000024) I2C Deglitch Control Register                              */
  
  struct {
    __IOM uint32_t en         : 1;            /*!< [0..0] I2C deglitch calibrator enable. 1: Enable, 0: Done/Disable         */
    __IM  uint32_t            : 7;
    __IOM uint32_t dat_p_dglch_sts : 1;       /*!< [8..8] SDA positive deglitch filter status. 0: failed, 1:success          */
    __IOM uint32_t dat_n_dglch_sts : 1;       /*!< [9..9] SDA negative deglitch filter status. 0: failed, 1:success          */
    __IOM uint32_t clk_p_dglch_sts : 1;       /*!< [10..10] SCL positive deglitch filter status. 0: failed, 1:success        */
    __IOM uint32_t clk_n_dglch_sts : 1;       /*!< [11..11] SCL negative deglitch filter status. 0: failed, 1:success        */
  } b;                                        /*!< bit fields for vdr_i2c_dglch_ctrl */
} vdr_i2c_dglch_ctrl_t, *pvdr_i2c_dglch_ctrl_t;

/**
  \brief Union type to access vdr_gdma0_isr (@ 0x00000030).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000030) GDMA0 ISR Register                                         */
  
  struct {
    __IM  uint32_t gdma0_ch0_isr : 1;         /*!< [0..0] GDMA 0 ISR for Channel 0                                           */
    __IM  uint32_t gdma0_ch1_isr : 1;         /*!< [1..1] GDMA 0 ISR for Channel 1                                           */
    __IM  uint32_t gdma0_ch2_isr : 1;         /*!< [2..2] GDMA 0 ISR for Channel 2                                           */
    __IM  uint32_t gdma0_ch3_isr : 1;         /*!< [3..3] GDMA 0 ISR for Channel 3                                           */
    __IM  uint32_t gdma0_ch4_isr : 1;         /*!< [4..4] GDMA 0 ISR for Channel 4                                           */
    __IM  uint32_t gdma0_ch5_isr : 1;         /*!< [5..5] GDMA 0 ISR for Channel 5                                           */
  } b;                                        /*!< bit fields for vdr_gdma0_isr */
} vdr_gdma0_isr_t, *pvdr_gdma0_isr_t;

/**
  \brief Union type to access vdr_gdma1_isr (@ 0x00000034).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000034) GDMA1 ISR Register                                         */
  
  struct {
    __IM  uint32_t gdma1_ch0_isr : 1;         /*!< [0..0] GDMA 1 ISR for Channel 0                                           */
    __IM  uint32_t gdma1_ch1_isr : 1;         /*!< [1..1] GDMA 1 ISR for Channel 1                                           */
    __IM  uint32_t gdma1_ch2_isr : 1;         /*!< [2..2] GDMA 1 ISR for Channel 2                                           */
    __IM  uint32_t gdma1_ch3_isr : 1;         /*!< [3..3] GDMA 1 ISR for Channel 3                                           */
    __IM  uint32_t gdma1_ch4_isr : 1;         /*!< [4..4] GDMA 1 ISR for Channel 4                                           */
    __IM  uint32_t gdma1_ch5_isr : 1;         /*!< [5..5] GDMA 1 ISR for Channel 5                                           */
  } b;                                        /*!< bit fields for vdr_gdma1_isr */
} vdr_gdma1_isr_t, *pvdr_gdma1_isr_t;

/**
  \brief Union type to access vdr_sgpio_isr (@ 0x00000038).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000038) SGPIO ISR Register                                         */
  
  struct {
    __IM  uint32_t sgpio0_isr : 1;            /*!< [0..0] SGPIO 1 ISR                                                        */
    __IM  uint32_t sgpio1_isr : 1;            /*!< [1..1] SGPIO 0 ISR                                                        */
  } b;                                        /*!< bit fields for vdr_sgpio_isr */
} vdr_sgpio_isr_t, *pvdr_sgpio_isr_t;

/**
  \brief Union type to access vdr_uart_isr (@ 0x0000003C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000003C) UART ISR Register                                          */
  
  struct {
    __IM  uint32_t uart0_isr  : 1;            /*!< [0..0] UART 0 Interrupt pending status                                    */
    __IM  uint32_t uart1_isr  : 1;            /*!< [1..1] UART 1 Interrupt pending status                                    */
    __IM  uint32_t uart2_isr  : 1;            /*!< [2..2] UART 2 Interrupt pending status                                    */
  } b;                                        /*!< bit fields for vdr_uart_isr */
} vdr_uart_isr_t, *pvdr_uart_isr_t;

/**
  \brief Union type to access vdr_i2c_isr (@ 0x00000040).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000040) I2C ISR Register                                           */
  
  struct {
    __IM  uint32_t i2c0_isr   : 1;            /*!< [0..0] I2C0 ISR                                                           */
    __IM  uint32_t            : 1;
    __IM  uint32_t i2c2_isr   : 1;            /*!< [2..2] I2C2 ISR                                                           */
    __IM  uint32_t i2c3_isr   : 1;            /*!< [3..3] I2C3 ISR                                                           */
  } b;                                        /*!< bit fields for vdr_i2c_isr */
} vdr_i2c_isr_t, *pvdr_i2c_isr_t;

/**
  \brief Union type to access vdr_spi_isr (@ 0x00000044).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000044) SPI ISR Register                                           */
  
  struct {
    __IM  uint32_t spi0_isr   : 1;            /*!< [0..0] SPI0 ISR                                                           */
    __IM  uint32_t spi1_isr   : 1;            /*!< [1..1] SPI1 ISR                                                           */
    __IM  uint32_t spi2_isr   : 1;            /*!< [2..2] SPI2 ISR                                                           */
    __IM  uint32_t spi3_isr   : 1;            /*!< [3..3] SPI3 ISR                                                           */
  } b;                                        /*!< bit fields for vdr_spi_isr */
} vdr_spi_isr_t, *pvdr_spi_isr_t;

/**
  \brief Union type to access vdr_i2s_pcm_isr (@ 0x00000048).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000048) I2S ISR Register                                           */
  
  struct {
    __IM  uint32_t i2s0_isr   : 1;            /*!< [0..0] I2S 0 ISR                                                          */
    __IM  uint32_t i2s1_isr   : 1;            /*!< [1..1] I2S 1 ISR                                                          */
    __IM  uint32_t            : 2;
    __IM  uint32_t pcm0_isr   : 1;            /*!< [4..4] PCM 0 ISR                                                          */
    __IM  uint32_t pcm1_isr   : 1;            /*!< [5..5] PCM 1 ISR                                                          */
  } b;                                        /*!< bit fields for vdr_i2s_pcm_isr */
} vdr_i2s_pcm_isr_t, *pvdr_i2s_pcm_isr_t;

/**
  \brief Union type to access vdr_gdma_hsks_ctrl (@ 0x00000060).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000060) GDMA Handshake Control Register                            */
  
  struct {
    __IOM uint32_t hs_gdma_hsks_cfg : 32;     /*!< [31..0] GDMA handshake signal mapping. Some peripherals can
                                                   operate with either GDMA0 or GDMA1. This mapping decides
                                                   DMA handshake signal connection. If Nth bit is 0, the peripheral's
                                                   DMA handshake signal is connected to GDMA0; if Nth bit
                                                   is 1, the peripheral's DMA handshake signal is connected
                                                   to GDMA1. Peripheral and GDMA handshake signal connection
                                                   option is as in below table.                                              */
  } b;                                        /*!< bit fields for vdr_gdma_hsks_ctrl */
} vdr_gdma_hsks_ctrl_t, *pvdr_gdma_hsks_ctrl_t;

/**
  \brief Union type to access vdr_mailbox_out_ctrl (@ 0x00000078).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000078) Mailbox Out Control Register                               */
  
  struct {
    __IOM uint32_t outrdy     : 1;            /*!< [0..0] Out mailbox data ready flag. CPU can only update OutData
                                                   when this bit is 0. After updating OutData, CPU should
                                                   set OutReady to 1. CPU writes 0 has no effect                             */
    __IOM uint32_t out_empty_int_en : 1;      /*!< [1..1] After OutData has been read by remote side (OutReady
                                                   == 0), CPU will receive interrupt if this bit is set to
                                                   1.                                                                        */
    __IM  uint32_t            : 5;
    __IOM uint32_t out_abort  : 1;            /*!< [7..7] Out data abort FW write 1 to this bit will clear OutReady
                                                   This bit is auto-clear.                                                   */
  } b;                                        /*!< bit fields for vdr_mailbox_out_ctrl */
} vdr_mailbox_out_ctrl_t, *pvdr_mailbox_out_ctrl_t;

/**
  \brief Union type to access vdr_pta_i2c_ctrl (@ 0x0000007C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000007C) I2C PTA Control Register                                   */
  
  struct {
    __IOM uint32_t pta_i2c_en : 1;            /*!< [0..0] pta_i2c_en                                                         */
    __IOM uint32_t pta_i2c_unlock : 1;        /*!< [1..1] pta_i2c_unlock                                                     */
    __IOM uint32_t pta_i2c_speed : 2;         /*!< [3..2] pta_i2c_speed                                                      */
    __IOM uint32_t pta_i2c_gnt_fw : 1;        /*!< [4..4] pta_i2c_gnt_fw                                                     */
    __IOM uint32_t pta_i2c_bus_gnt_fw : 3;    /*!< [7..5] pta_i2c_bus_gnt_fw                                                 */
  } b;                                        /*!< bit fields for vdr_pta_i2c_ctrl */
} vdr_pta_i2c_ctrl_t, *pvdr_pta_i2c_ctrl_t;

/**
  \brief Union type to access vdr_wl_pmc_imr (@ 0x00000088).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000088) WLAN PMC IMR Register                                      */
  
  struct {
    __IOM uint32_t bit_inrdy  : 1;            /*!< [0..0] In mailbox data ready status. After CPU read InData,
                                                   it should write 1 to clear this bit.                                      */
    __IOM uint32_t bit_inrdy_int_en : 1;      /*!< [1..1] Enable interrupt of In mailbox data ready                          */
  } b;                                        /*!< bit fields for vdr_wl_pmc_imr */
} vdr_wl_pmc_imr_t, *pvdr_wl_pmc_imr_t;

/**
  \brief Union type to access vdr_lx_ctrl0 (@ 0x00000090).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000090) Lexra Control Register 0                                   */
  
  struct {
    __IOM uint32_t lx_bus_timeout_en : 1;     /*!< [0..0] 1:Enable                                                           */
    __IOM uint32_t lx_bus_timeout_threshold : 2;/*!< [2..1] 2'b00: 2^15 lexra clock cycles 2'b01: 2^13 lexra clock
                                                   cycles 2'b10: 2^11 lexra clock cycles 2'b11: 2^9 lexra
                                                   clock cycles                                                              */
    __IOM uint32_t lx1_dma_lock_en : 1;       /*!< [3..3] 1'b1: set gnt=0 to lock lexra dma function.                        */
    __IM  uint32_t lx1_dma_lock_done : 1;     /*!< [4..4] 1'b1: lock is done. There is no dma transaction now.               */
    __IOM uint32_t pcm_spdup_en : 1;          /*!< [5..5] PCM speedup enable, only for test mode.                            */
    __IOM uint32_t pcm0_lx_req_en : 1;        /*!< [6..6] 1: Enable                                                          */
    __IOM uint32_t pcm1_lx_req_en : 1;        /*!< [7..7] 1: Enable                                                          */
    __IOM uint32_t lx2_dma_lock_en : 1;       /*!< [8..8] 1'b1: set gnt=0 to lock lexra dma function.                        */
    __IM  uint32_t lx2_dma_lock_done : 1;     /*!< [9..9] 1'b1: lock is done. There is no dma transaction now.               */
    __IM  uint32_t            : 6;
    __IOM uint32_t mii_lx_timeout_en : 1;     /*!< [16..16] 1:Enable                                                         */
    __IOM uint32_t mii_lx_timeout_threshold : 2;/*!< [18..17] 2'b00: 2^15 lexra clock cycles 2'b01: 2^13 lexra clock
                                                   cycles 2'b10: 2^11 lexra clock cycles 2'b11: 2^9 lexra
                                                   clock cycles                                                              */
  } b;                                        /*!< bit fields for vdr_lx_ctrl0 */
} vdr_lx_ctrl0_t, *pvdr_lx_ctrl0_t;

/**
  \brief Union type to access vdr_lx_ctrl1 (@ 0x00000094).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000094) Lexra Control Register 1                                   */
  
  struct {
    __IM  uint32_t r_lx1_to_addr_mst : 32;    /*!< [31..0] The address when lexra master is hanged.                          */
  } b;                                        /*!< bit fields for vdr_lx_ctrl1 */
} vdr_lx_ctrl1_t, *pvdr_lx_ctrl1_t;

/**
  \brief Union type to access vdr_lx_ctrl2 (@ 0x00000098).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x00000098) Lexra Control Register 2                                   */
  
  struct {
    __IM  uint32_t r_lx1_to_addr_slv : 32;    /*!< [31..0] The address when lexra slave is hanged.                           */
  } b;                                        /*!< bit fields for vdr_lx_ctrl2 */
} vdr_lx_ctrl2_t, *pvdr_lx_ctrl2_t;

/**
  \brief Union type to access vdr_reg_lx_ctrl3 (@ 0x0000009C).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x0000009C) Lexra Control Register 3                                   */
  
  struct {
    __IM  uint32_t r_lx2_to_addr_mst : 32;    /*!< [31..0] The address when lexra master is hanged.                          */
  } b;                                        /*!< bit fields for vdr_reg_lx_ctrl3 */
} vdr_reg_lx_ctrl3_t, *pvdr_reg_lx_ctrl3_t;

/**
  \brief Union type to access vdr_mbist_ctrl0 (@ 0x000000B0).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000B0) MBIST Control Register 0                                   */
  
  struct {
    __IOM uint32_t mbist_en   : 1;            /*!< [0..0] Set reset_n of mbist controller                                    */
    __IOM uint32_t mbist_cke  : 1;            /*!< [1..1] Set clock enable of mbist controller                               */
    __IM  uint32_t            : 6;
    __IOM uint32_t mbist_ctrlr_addr : 5;      /*!< [12..8] Set mbist controller address                                      */
  } b;                                        /*!< bit fields for vdr_mbist_ctrl0 */
} vdr_mbist_ctrl0_t, *pvdr_mbist_ctrl0_t;

/**
  \brief Union type to access vdr_mbist_ctrl1 (@ 0x000000B4).
*/
typedef union {
  __IOM uint32_t w;                           /*!< (@ 0x000000B4) MBIST Control Register 1                                   */
  
  struct {
    __IOM uint32_t mbist_ctrlr_data : 32;     /*!< [31..0] Indirectly write to mbist controller with write strobe/Indirectly
                                                   read from mbist controller                                                */
  } b;                                        /*!< bit fields for vdr_mbist_ctrl1 */
} vdr_mbist_ctrl1_t, *pvdr_mbist_ctrl1_t;

/** @} */ /* End of group hs_hal_vdr_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_VDR_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_VENDOR_VDR_TYPE_H_

