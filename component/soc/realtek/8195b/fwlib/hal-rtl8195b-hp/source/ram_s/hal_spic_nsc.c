/**************************************************************************//**
 * @file     hal_spic_nsc.c
 * @brief    Allow flash to be accessed through non-secure callable function in non-secure mode.
 * @version  1.00
 * @date     2017-08-22
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

#include "hal_spic.h"
#include "hal_spic_nsc.h"



#if defined(CONFIG_BUILD_SECURE)

/**

        \addtogroup hs_hal_spic_nsc_api Flash Controller HAL NSC APIs
        \ingroup hs_hal_spic
        \brief The Flash Controller HAL NSC (Non-Secure Callable) APIs. Non-secure domain is allowed to access secure functions through NSC APIs.
        @{
*/


/** \brief Description of Non-secure callable function spic_load_default_setting_nsc
 *
 *    spic_load_default_setting_nsc is used to load default setting for One IO mode at low speed without calibration.
 *    The calibration includes baud rate, delay line and dummy cycles(associated with path delay).
 *
 *   \param pspic_init_para_t pspic_init_data:      The pointer of struct storing calibation settings.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_load_default_setting_nsc(pspic_init_para_t pspic_init_data)
{
    spic_load_default_setting(pspic_init_data);
}

/** \brief Description of Non-secure callable function spic_query_system_clk_nsc
 *
 *    spic_query_system_clk_nsc is used to query current CPU clock.
 *    Different CPU speed will apply different calibration parameters to optimize the flash controller.
 *
 *   \param void.
 *
 *   \return u8: The macro definition of CPU clock.
 */
SECTION_NS_ENTRY_FUNC
u8 NS_ENTRY spic_query_system_clk_nsc(void)
{
    return spic_query_system_clk();
}

/** \brief Description of Non-secure callable function spic_clock_ctrl_nsc
 *
 *    spic_clock_ctrl_nsc is used to enable or disable the flash controller clock and function enable.
 *
 *   \param u8 ctl:      The control parameter.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_clock_ctrl_nsc(u8 ctl)
{
    spic_clock_ctrl(ctl);
}

/** \brief Description of Non-secure callable function spic_pin_ctrl_nsc
 *
 *    spic_pin_ctrl_nsc is used to select and control pinmux of the flash controller.
 *
 *   \param u8 io_pin_sel:      The pinmux selection.
 *   \param u8 ctl:      The control parameter.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_pin_ctrl_nsc(u8 io_pin_sel, u8 ctl)
{
    spic_pin_ctrl(io_pin_sel, ctl);
}

/** \brief Description of Non-secure callable function spic_init_setting_nsc
 *
 *    spic_init_setting_nsc is used to initialize the flash controller.
 *    The function and clock are enbaled at the first. Some parameters and registers are initialized afte that.
 *    Flash controller is set with One IO mode with low speed to ensure it can operate flash correctly without calibration procedure.
 *    If flash ID cannot be identified, a release from deep power down command is executed to wake the flash.
 *    A return to SPI command is executed followed by the release from deep power down command to ensure flash is under SPI mode.
 *    After these commands, a read ID command is issued to identify the flash type.
 *    For Adesto flash type, we should unlock flash so that the flash can be accessed correctly at the end of the functioin.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 spic_bit_mode:      The target IO mode the flash controller is going to operate.
 *
 *   \return hal_status_t.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY spic_init_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode)
{
    return spic_init_setting(phal_spic_adaptor, spic_bit_mode);
}

/** \brief Description of Non-secure callable function spic_load_calibration_setting_nsc
 *
 *    spic_load_calibration_setting_nsc is used to load calibration settings from flash to the adaptor.
 *    Flash controller will try to load available calibration setting so that it does not have to calibrate.
 *    It takes less time to boot up system without flash calibration process.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_load_calibration_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor)
{
    spic_load_calibration_setting(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function spic_store_calibration_setting_nsc
 *
 *    spic_store_calibration_setting_nsc is used to store valid calibration setting to flash after calibration process.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_store_calibration_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor)
{
    spic_store_calibration_setting(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function spic_config_dtr_read_nsc
 *
 *    spic_config_dtr_read_nsc is used to configurate flash controller so that it can read data correctly with DTR mode .
 *    1-4D-4D, 4D-4D-4D, 8D-8D-8D modes access should call this function first.
 *    x-y-z : x is IO mode of command phase, y is IO mode of address phase, z is IO mode of data phase. D stands for DTR mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_config_dtr_read_nsc(phal_spic_adaptor_t phal_spic_adaptor)
{
    spic_config_dtr_read(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function spic_config_auto_mode_nsc
 *
 *    spic_config_auto_mode_nsc is used to configurate auto mode of flash controller.
 *    In the meantime, the flash controller sends commands to switch flash to the target IO mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_config_auto_mode_nsc(phal_spic_adaptor_t phal_spic_adaptor)
{
    spic_config_auto_mode(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function spic_config_user_mode_nsc
 *
 *    spic_config_user_mode_nsc is used to configurate user mode of flash controller.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_config_user_mode_nsc(phal_spic_adaptor_t phal_spic_adaptor)
{
    spic_config_user_mode(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function spic_verify_calibration_para_nsc
 *
 *    spic_verify_calibration_para_nsc is used to verify calibration pattern for calibration procedure.
 *
 *   \param void.
 *
 *   \return BOOL: _TRUE: data is correct, _FALSE: data is wrong.
 */
SECTION_NS_ENTRY_FUNC
BOOL NS_ENTRY spic_verify_calibration_para_nsc(void)
{
    return spic_verify_calibration_para();
}

/** \brief Description of Non-secure callable function spic_enable_seq_read_nsc
 *
 *    spic_enable_seq_read_nsc is used to enable sequential transfer mode.
 *    The chip select signal does not toggle between two data frames in auto mode, only clock signal stops toggling.
 *    The path delay dummy cycles between two data frames will be calibrated in this function.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_enable_seq_read_nsc(phal_spic_adaptor_t phal_spic_adaptor)
{
    spic_enable_seq_read(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function spic_disable_seq_read_nsc
 *
 *    spic_disable_seq_read_nsc is used to disable sequential transfer in auto mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_disable_seq_read_nsc(phal_spic_adaptor_t phal_spic_adaptor)
{
    spic_disable_seq_read(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function spic_set_chnl_num_nsc
 *
 *    spic_set_chnl_num_nsc is used to set channel numbers of command, address and data phases to the control register.
 *    The flash controller should be disabled so that the values can be correctly written.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_set_chnl_num_nsc(phal_spic_adaptor_t phal_spic_adaptor)
{
    spic_set_chnl_num(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function spic_set_delay_line_nsc
 *
 *    spic_set_delay_line_nsc is used to fine-tune data receive timing with digital PHY.
 *    100 levels of delay line can be used.
 *
 *   \param u8 delay_line:      The level of the delay line, can be 0~99.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_set_delay_line_nsc(u8 delay_line)
{
    spic_set_delay_line(delay_line);
}

/** \brief Description of Non-secure callable function spic_rx_cmd_8io_nsc
 *
 *    spic_rx_cmd_8io_nsc is used to send commands which return data from flash after command phase and address phase(depends on command) for Adesto 8IO flash.
 *    Usually we will use this function when trying to read status registers of flash.
 *    Flash should be under 1-1-1, 4-4-4, 8-8-8, 4D-4D-4D or 8D-8D-8D when it enters this function.
 *    x-y-z : x is IO mode of command phase, y is IO mode of address phase, z is IO mode of data phase. D stands for DTR mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_rx_cmd_8io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    spic_rx_cmd_8io(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of Non-secure callable function spic_rx_cmd_4io_nsc
 *
 *    spic_rx_cmd_4io_nsc is used to send commands which return data from flash after command phase and address phase(depends on command) for most of non-8IO flash.
 *    Usually we will use this function when trying to read status registers of flash.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_rx_cmd_4io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    spic_rx_cmd_4io(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of Non-secure callable function spic_rx_cmd_nsc
 *
 *    spic_rx_cmd_nsc is an entry function to switch between 8IO or non-8IO rx_cmd functions depending on flash types.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_rx_cmd_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    spic_rx_cmd(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of Non-secure callable function spic_tx_cmd_8io_nsc
 *
 *    spic_tx_cmd_8io_nsc is used to send flash commands which do not return values for Adesto 8IO flash.
 *    These commands could be erase command or set flash registers.
 *    Flash should be under 1-1-1, 4-4-4, 8-8-8, 4D-4D-4D or 8D-8D-8D when it enters this function.
 *    x-y-z : x is IO mode of command phase, y is IO mode of address phase, z is IO mode of data phase. D stands for DTR mode.
 *    At the end of the function, the flash status is checked if flash returns to ready state.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_tx_cmd_8io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    spic_tx_cmd_8io(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of Non-secure callable function spic_tx_cmd_4io_nsc
 *
 *    spic_tx_cmd_4io_nsc is used to send flash commands which do not return values for most of non-8IO flash.
 *    These commands could be erase command or set flash registers.
 *    At the end of the function, the flash status is checked if flash returns to ready state.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_tx_cmd_4io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    spic_tx_cmd_4io(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of Non-secure callable function spic_tx_cmd_8io_no_check_nsc
 *
 *    spic_tx_cmd_8io_no_check_nsc is used to send flash commands which do not return values for Adesto 8IO flash.
 *    These commands could be erase command or set flash registers.
 *    Flash should be under 1-1-1, 4-4-4, 8-8-8, 4D-4D-4D or 8D-8D-8D when it enters this function.
 *    x-y-z : x is IO mode of command phase, y is IO mode of address phase, z is IO mode of data phase. D stands for DTR mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_tx_cmd_8io_no_check_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    spic_tx_cmd_8io_no_check(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of Non-secure callable function spic_tx_cmd_4io_no_check_nsc
 *
 *    spic_tx_cmd_4io_no_check_nsc is used to send flash commands which do not return values for most of non-8IO flash.
 *    These commands could be erase command or set flash registers.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_tx_cmd_4io_no_check_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    spic_tx_cmd_4io_no_check(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of Non-secure callable function spic_tx_cmd_no_check_nsc
 *
 *    spic_tx_cmd_no_check_nsc is an entry function to switch between 8IO or non-8IO tx_cmd_no_check functions depending on flash types.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_tx_cmd_no_check_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    spic_tx_cmd_no_check(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of Non-secure callable function spic_tx_cmd_nsc
 *
 *    spic_tx_cmd_nsc is an entry function to switch between 8IO or non-8IO tx_cmd functions depending on flash types.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_tx_cmd_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    spic_tx_cmd(phal_spic_adaptor, cmd, data_phase_len,pdata);
}

/** \brief Description of Non-secure callable function spic_wait_ready_nsc
 *
 *    spic_wait_ready_nsc is used to check if the flash controller is ready.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_wait_ready_nsc(SPIC_Type *spic_dev)
{
    spic_wait_ready(spic_dev);
}

/** \brief Description of Non-secure callable function spic_flush_fifo_nsc
 *
 *    spic_flush_fifo_nsc is used to flush FIFO of the flash controller.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_flush_fifo_nsc(SPIC_Type *spic_dev)
{
    spic_flush_fifo(spic_dev);
}

/** \brief Description of Non-secure callable function spic_pinmux_init_nsc
 *
 *    spic_pinmux_init_nsc is used to select pinmux to operate flash.
 *    The pinmux selection is registered and checked if the relevant pins are occpuied by other devices.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 io_pin_sel:      The pinmux selection.
 *
 *   \return hal_status_t.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY spic_pinmux_init_nsc(phal_spic_adaptor_t phal_spic_adaptor,u8 io_pin_sel)
{
    return spic_pinmux_init(phal_spic_adaptor, io_pin_sel);
}

/** \brief Description of Non-secure callable function spic_init_nsc
 *
 *    spic_init_nsc is used to initialize flash controller setting.
 *    Flash can be accessed freely with API functions after this function.
 *    Flash access path delay is calibrated if no available setting is stored in flash before.
 *    After that, the flash controller initializes user mode and auto mode registers for the current IO mode.
 *    At the end of the function, the sequential transfer mode is also calibrated for future use.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 spic_bit_mode:   The flash IO mode.
 *   \param u8 io_pin_sel:      The pinmux selection.
 *
 *   \return hal_status_t.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY spic_init_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode, u8 io_pin_sel)
{
    return spic_init(phal_spic_adaptor, spic_bit_mode, io_pin_sel);
}

/** \brief Description of Non-secure callable function spic_deinit_nsc
 *
 *    spic_deinit_nsc is used to de-initialize flash controller setting when flash is no longer used.
 *    Pinmux, function enable and clock are disabled in the function.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash adaptor.
 *
 *   \return hal_status_t.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY spic_deinit_nsc(phal_spic_adaptor_t phal_spic_adaptor)
{
    return spic_deinit(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function spic_calibration_nsc
 *
 *    spic_calibration_nsc is used to calibrate the path delay of flash data access path.
 *    It ensures the flash controller can read correct data by inserting few delay.
 *    The level of delays depends on the operating frequency and flash IO mode.
 *    If an optimal available window is found, the setting is stored in flash so that flash controller directly load the setting next time.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash adaptor.
 *
 *   \return BOOL: _TURE: Success, _FALSE: No available window, calibration unsuccessful.
 */
SECTION_NS_ENTRY_FUNC
BOOL NS_ENTRY spic_calibration_nsc(phal_spic_adaptor_t phal_spic_adaptor, u32 default_dummy_cycle)
{
    return spic_calibration(phal_spic_adaptor, default_dummy_cycle);
}

/** \brief Description of Non-secure callable function spic_store_setting_nsc
 *
 *    spic_store_setting_nsc is used to store flash adaptor setting.
 *    The information is used to recover flash from reset state or system sleep.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash adaptor.
 *   \param phal_spic_restore_setting_t phal_spic_setting:      The pointer of data structure storing recovery information.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_store_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor, phal_spic_restore_setting_t phal_spic_setting)
{
    spic_store_setting(phal_spic_adaptor, phal_spic_setting);
}

/** \brief Description of Non-secure callable function spic_recover_setting_nsc
 *
 *    spic_recover_setting_nsc is used to load flash adaptor setting.
 *    After the syetem wakes up from sleep state or recovers from reset, the flash controller registers are also reseted.
 *    This function re-initialize the flash controller with the information stored before.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash adaptor.
 *   \param phal_spic_restore_setting_t phal_spic_setting:      The pointer of data structure storing recovery information.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY spic_recover_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor, phal_spic_restore_setting_t phal_spic_setting)
{
    spic_recover_setting(phal_spic_adaptor, phal_spic_setting);
}

/** *@} */ /* End of group hs_hal_spic_nsc_api */

#endif
