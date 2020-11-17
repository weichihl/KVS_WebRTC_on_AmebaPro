/**************************************************************************//**
 * @file     hal_sys_ctrl.h
 * @brief    The system control functions declaration.
 * @version  v1.00
 * @date     2017/11/21
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
#ifndef HAL_SYS_CTRL_H
#define HAL_SYS_CTRL_H

#include "cmsis.h"

/**
 * @brief  define debug port mode.
 */
enum dbg_port_mode_e {
    SWD_MODE        = 0,    ///< debugger use SWD mode
    JTAG_MODE       = 1,    ///< debugger use JTAG mode
    JTAG_CHAIN_MODE = 2     ///< debugger use JTAG-Chain mode
};
typedef uint8_t     dbg_port_mode_t;


/**
 * @brief  define HS pltform debugger port pin mux selection.
 */
enum hs_dbg_pin_sel_e {
    HS_DBG_PIN_S0     = 0,  ///< use debugger port on pin E0 ~ E4 (JTAG) or E3 ~ E4 (SWD)
    HS_DBG_PIN_S1     = 1   ///< use debugger port on pin C2 ~ C6 (JTAG) or C5 ~ C6 (SWD)
};
typedef uint8_t     hs_dbg_pin_sel_t;

/**
 * @brief  define HS pltform SPIC RX PHY fetch phase setting.
 */
enum hs_spic_phy_fetch_phase_e {
    RX_SCLK_DELAY_LOW = 1,      ///< Delay 0.5 SCLK to fetch data for IO0~IO3 
    RX_SCLK_DELAY_HIGH = 2,     ///< Delay 0.5 SCLK to fetch data for IO4~IO7 
    RX_PHASE_DELAY_LOW = 4,       ///< Delay ~0.5 BUS CLK to adjust phase to fetch data for IO0~IO3 
    RX_PHASE_DELAY_HIGH = 8       ///< Delay ~0.5 BUS CLK to adjust phase to fetch data for IO4~IO7 
};
typedef uint8_t     hs_spic_phy_fetch_phase_t;

/**
 * @brief  define HS pltform SPIC RX PHY delay setting.
 */
enum hs_spic_phy_delay_e {
    RX_DELAY_BUS_CLK_LOW = 1,
    RX_DELAY_BUS_CLK_HIGH = 2
};
typedef uint8_t     hs_spic_phy_delay_t;

/**
 *  @brief SDIO device enable control.
 *  @details Enable or disable the SDIO device function, clock and pins.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.
 *  @return      void
 *
 */
void hal_syson_sdio_dev_ctrl(BOOL en);

/**
 *  @brief Audio porb power enable control.
 *  @details Enable or disable the audio porb.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.
 *  @return      void
 *
 */
void hal_syson_audio_porb_ctrl(BOOL en);

/**
 *  @brief Audio LDO power enable control.
 *  @details Enable or disable the audio porb.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.
 *  @return      void
 *
 */
void hal_syson_audio_ldo_ctrl(BOOL en);

/**
 *  @brief Select audio codec LDO power.
 *  @details Select audio codec LDO power 1.8V or 2.8V.
 *  @param[in]   sel  Select codec LDO power.
 *                 - 0 = LDO power 1.8V.
 *                 - 1 = LDO power 2.8V.
 *  @return      void
 *
 */
void hal_syson_audio_ldo_tune(u8 sel);

/**
 *  @brief Audio codec device enable control.
 *  @details Enable or disable the audio codec device function, clock and pins.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.
 *  @return      void
 *
 */
void hal_syson_audio_dev_ctrl(BOOL en);

/**
 *  @brief I2S 98.304MHz PLL enable control.
 *  @details Enable or disable the I2S PLL.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.
 *  @return      void
 *
 */
void hal_syson_i2s_98m_pll_ctrl(BOOL en);

/**
 *  @brief I2S 45.1584MHz PLL enable control.
 *  @details Enable or disable the I2S PLL.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.
 *  @return      void
 *
 */
void hal_syson_i2s_45m_pll_ctrl(BOOL en);

/**
 *  @brief PCM 24.576MHz PLL enable control.
 *  @details Enable or disable the PCM PLL.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.
 *  @return      void
 *
 */
void hal_syson_pcm_24m_pll_ctrl(BOOL en);

/**
 *  @brief Reset SGPIO IP
 *  @details Reset SGPIO and registers.
 *  @param[in]   sgpio_index  Select the sgpio indexl.
 *  @return      void
 */
void hal_syson_sgpio_rst(uint32_t sgpio_index);


/**
 *  @brief Enable flash controller IP
 *  @details Enable clock and function of the flash controller.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.ol.
 *  @return      void
 */
void hal_syson_spic_dev_ctrl(BOOL en);

/**
 *  @brief Flash controller PHY control
 *  @details Delay TX or RX clock cycles to ensure data can be read correctly
 *  @param[in]   tx_sclk_dly  Delay 0.5 SCLK when TX data.
 *  @param[in]   rx_fetch_phase  Delay 0.5 SCLK or align clock phase when RX data.
 *  @param[in]   rx_clk_dly  Dealy 1 bus clock when RX data.
 *  @param[in]   rx_merge_phase  Reverse lower lane and upper lane for 8IO DTR.
 *  @return      void
 */
void hal_syson_spic_phy_ctrl(u8 tx_sclk_dly, u8 rx_fetch_phase, u8 rx_clk_dly, u8 rx_merge_phase);


/**
 *  @brief I2C filter enable control.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.
 *  @return      void
 *
 */
void hal_syson_i2c_filter_ctrl(BOOL en);

/**
 *  @brief I2C calibration input enable control.
 *  @param[in]   en  The enable control.
 *                 - 1 = Enable.
 *                 - 0 = Disable.
 *  @return      void
 *
 */
void hal_syson_i2c_cali_in_ctrl(BOOL en);

/**
 *  @brief Handle the notification of the debugger port configuration changed.
 *  @param[in]   icc_cmd_word0  This word0 of the ICC command for debug port configuration change notification.
 *  @param[in]   icc_cmd_word1  This word1 of the ICC command for debug port configuration change notification.
 *  @param[in]   arg  This argument is ignored.
 *
 *  @return      void.
 *
 */
void dbg_port_cfg_noti_handler (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg);

/**
 *  @brief Configures debuger port setting.
 *  @param[in]   ls_dbg_mode  The LS platform debug port mode selection, JTAG or SWD.
 *  @param[in]   hs_dbg_mode  The HS platform debug port mode selection, JTAG or SWD.
 *                 - SWD_MODE  selectes the SWD mode.
 *                 - JTAG_MODE  selects the JTAG mode.
 *  @param[in]  hs_pin_sel  HS debugger port pin mux selection.
 *                  - HS_DBG_PIN_S0    use pin on pin E0 ~ E4(JTAG) or E3 ~ E4(SWD)
 *                  - HS_DBG_PIN_S1    use pin on pin C2 ~ C6(JTAG) or C5 ~ C6(SWD)
 *
 *  @return      HAL_ERR_PARA  One or more input arguments is/are invalid.
 *  @return      HAL_OK  Debugger port configures OK.
 *
 */
hal_status_t hal_dbg_port_cfg (dbg_port_mode_t ls_dbg_mode, dbg_port_mode_t hs_dbg_mode, hs_dbg_pin_sel_t hs_pin_sel);


/**
 *  @brief Disables the debugger(JTAG/SWD) port.
 *
 *  @return      void
 *
 */
void hal_dbg_port_disable(void);

/**
 *  @brief I2C deglitch enable control.
 *
 *  @param[in]   en  The enable control
 *  @returns    void
 */
void hal_i2c_dglch_ctrl (BOOL en);

/**
 *  @brief I2C deglitch enable control check
 *
 *  @returns    void
 */
void hal_i2c_dglch_ctrl_chk (void);

/**
 *  @brief I2C deglitch register read
 *
 *  @returns    uint32_t    deglitch register value.
 */
uint32_t hal_i2c_read_dglch_reg (void);

/**
 *  @brief I2C filter analog control
 *
 *  @param[in]   en  The enable control
 *  @returns    void
 */
void hal_i2c_fltr_ana_ctrl (BOOL en);

/**
 *  @brief ADC Power Preinit
 *  @details ADC Power preinit function.
 *  @param[in]   hal_adc_adapter_t *phal_adc_adapter
 *  @return      hal_status_t
 *
 */
hal_status_t hal_adc_pwr_preinit (hal_adc_adapter_t *phal_adc_adapter);

/**
 *  @brief LP ADC power cut enable
 *  @details LP ADC power cut enable
 *  @param[in]   void
 *  @return      hal_status_t
 *
 */
hal_status_t hal_lp_adc_en_pwr_by_hp(void);

void hal_i2c_iopwr_enable(hal_i2c_adapter_t *phal_i2c_adapter);
#endif  // end of "#ifndef HAL_SYS_CTRL_H"

