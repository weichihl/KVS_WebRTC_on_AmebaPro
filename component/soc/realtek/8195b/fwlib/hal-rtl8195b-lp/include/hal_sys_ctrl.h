/**************************************************************************//**
 * @file     hal_sys_ctrl.h
 * @brief    The system control functions declaration.
 * @version  v1.00
 * @date     2020/03/16
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
    SWD_MODE    = 0,        ///< debugger use SWD mode
    JTAG_MODE   = 1         ///< debugger use JTAG mode
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
 * @brief  define LP pltform wakeup indication status.
 */
typedef struct {
    union {
        uint32_t wk_indication_tbl;
        struct {
            uint32_t gpio_wake_sts : 1;         /*!< [0..0] 1: Indicate GPIO wake(GPIOA_13)                              */
            uint32_t aon_wake_tim0_sts : 1;     /*!< [1..1] 1: Indicate AON timer wake                                   */
            uint32_t rtc_wake_sts : 1;          /*!< [2..2] 1: Indicate RTC wake                                         */
            uint32_t adp_wake_sts : 1;          /*!< [3..3] 1: Indicate Adapter wake                                     */
            uint32_t lp_wsts_systim : 1;        /*!< [4..4] 1: Indocate SYSTimer Wakeup event                            */
            uint32_t lp_wsts_gtim : 1;          /*!< [5..5] 1: Indicate GTimer0~7 Wakeup system event                    */
            uint32_t lp_wsts_swrd_ocp : 1;      /*!< [6..6] 1: Indicate DCORE SWR OCP event                              */
            uint32_t lp_wsts_bod : 1;           /*!< [7..7] 1: Indicate BOD Wakeup event                                 */
            uint32_t lp_wsts_gpio : 1;          /*!< [8..8] 1: Indicate GPIO Wakeup event(Except GPIOA_13, other GPIOs)  */
            uint32_t lp_wsts_pwm : 1;           /*!< [9..9] 1: Indicate PWM Wakeup event                                 */
            uint32_t lp_wsts_wlan : 1;          /*!< [10..10] 1: Indicate WLAN Wakeup event                              */
            uint32_t lp_wsts_uart : 1;          /*!< [11..11] 1: Indicate UART Wakeup event                              */
            uint32_t lp_wsts_i2c : 1;           /*!< [12..12] 1: Indicate I2C Wakeup event                               */
            uint32_t lp_wsts_adc : 1;           /*!< [13..13] 1: Indicate ADC Wakeup event                               */
            uint32_t lp_wsts_comp : 1;          /*!< [14..14] 1: Indicate Comparetor Wakeup event                        */
            uint32_t lp_wsts_sgpio : 1;         /*!< [15..15] 1: Indicate SGPIO Wakeup event                             */
            uint32_t lp_wsts_aon : 1;           /*!< [16..16] 1: Indicate AON Wakeup event (0x128)                       */
            uint32_t lp_wsts_hs : 1;            /*!< [17..17] 1: Indicate HS Wakeup event                                */
        }        wk_indication_tbl_b;
    } ;
} ls_wk_indicat_t;

/**
 *  @brief Store lp wake-up indication reason(Backup using, because gpio init will clean gpio sts).
 *  @return      void
 *
 */
void hal_misc_store_lp_wk_indicat(void);

/**
 *  @brief Get lp wake-up indication reason.
 *  @return      void
 *
 */
uint32_t hal_misc_get_lp_wk_indicat(void);

/**
 *  @brief Select the QDEC sclk
 *
 *  @param[in] source_clk Select sclk.
 *                 - 0 = 2MHz.
 *                 - 1 = 32KHz.
 *  @return      void
 */
void hal_syson_sel_qdec_sclk(u8 sclk_sel);

/**
 *  @brief SGPIO pin control
 *
 *  @param[in] pin_sel Select the pin.
 *                 - 0 = Select0, GPIOA 2~3
 *                 - 1 = Select1, GPIOA 7~8
 *  @param[in]   en  The enable control.
 *  @return      void
 */
void hal_syson_sgpio_pin_ctrl(u8 pin_sel, BOOL en);

/**
 *  @brief Reset SGPIO IP
 *
 *  @return      void
 */
void hal_syson_sgpio_rst(void);

/**
 *  @brief Reset CIR IP
 *
 *  @return      void
 */
void hal_syson_cir_rst(void);

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
 *  @brief Controls the enable of SWD pins.
 *
 *  @param[in]  en  Pin enable control:
 *                    - 0: Disable SWD pins.
 *                    - 1: Enable SWD pins.
 *
 *  @return     void.
 */
void hal_misc_swd_pin_ctrl (BOOL en);

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
 *  @brief Do FLL 2M calibration
 *
 *  @return      int32_t 0: fine-tune OK,
 *                       1: fine-tune failed.
 *
 */
int32_t cali_fll2m_clk_src_ram(void);


void hal_syson_i2c_pwr_ctrl(uint8_t en);

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
 *  @brief GPIO shutdown enable
 *  @param[in]   pin_num pin number of GPIO to be shutdowned
 *  @return      void
 *
 */
void hal_gpio_shdn_en(uint8_t pin_num);

#endif  // end of "#ifndef HAL_SYS_CTRL_H"

