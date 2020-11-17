/**************************************************************************//**
 * @file     hal_spic.h
 * @brief    Provide stub functions for RAM code to access SPIC ROM functions.
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

#ifndef _HAL_SPIC_H_
#define _HAL_SPIC_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

extern const hal_spic_func_stubs_t hal_spic_stubs;

/**

        \addtogroup ls_hal_spic_ram_func Flash Controller HAL RAM APIs
        \ingroup ls_hal_spic
        \brief The flash controller HAL APIs. Functions become an interface between API functions and ROM codes.
        @{
*/

/** \brief Description of spic_load_default_setting
 *
 *    spic_load_default_setting is used to load default setting for One IO mode at low speed without calibration.
 *    The calibration includes baud rate, delay line and dummy cycles(associated with path delay).
 *
 *   \param pspic_init_para_t pspic_init_data:      The pointer of struct storing calibation settings.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_load_default_setting(pspic_init_para_t pspic_init_data)
{
    hal_spic_stubs.spic_load_default_setting(pspic_init_data);
}

/** \brief Description of spic_init
 *
 *    spic_init is used to initialize the flash adaptor in low speed platform..
 *    Unlike the spic_init_setting_rtl8195bhp in high speed platform, the flash control relevant registers are not initialized in low speed platform.
 *    The registers setting is directly inherited from high speed platform.
 *    The related information of flash adaptor is assigned in this function for a specific IO mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_init(phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_spic_stubs.spic_init(phal_spic_adaptor);
}

/** \brief Description of spic_enable_seq_read
 *
 *    spic_enable_seq_read is used to enable sequential transfer mode.
 *    The chip select signal does not toggle between two data frames in auto mode, only clock signal stops toggling.
 *    The path delay dummy cycles between two data frames will be calibrated in this function.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_enable_seq_read(phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_spic_stubs.spic_enable_seq_read(phal_spic_adaptor);
}

/** \brief Description of spic_disable_seq_read
 *
 *    spic_disable_seq_read is used to disable sequential transfer in auto mode.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_disable_seq_read(phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_spic_stubs.spic_disable_seq_read(phal_spic_adaptor);
}

/** \brief Description of spic_set_chnl_num
 *
 *    spic_set_chnl_num is used to set channel numbers of command, address and data phases to the control register.
 *    The flash controller should be disabled so that the values can be correctly written.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_set_chnl_num(phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_spic_stubs.spic_set_chnl_num(phal_spic_adaptor);
}

/** \brief Description of spic_set_delay_line
 *
 *    spic_set_delay_line is used to fine-tune data receive timing with digital PHY.
 *    100 levels of delay line can be used.
 *
 *   \param u8 delay_line:      The level of the delay line, can be 0~99.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_set_delay_line(u8 delay_line)
{
    hal_spic_stubs.spic_set_delay_line(delay_line);
}

/** \brief Description of spic_rx_cmd_8io
 *
 *    spic_rx_cmd_8io is used to send commands which return data from flash after command phase and address phase(depends on command) for Adesto 8IO flash.
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
__STATIC_INLINE void spic_rx_cmd_8io(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    hal_spic_stubs.spic_rx_cmd_8io(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_rx_cmd_4io
 *
 *    spic_rx_cmd_4io is used to send commands which return data from flash after command phase and address phase(depends on command) for most of non-8IO flash.
 *    Usually we will use this function when trying to read status registers of flash.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_rx_cmd_4io(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    hal_spic_stubs.spic_rx_cmd_4io(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_rx_cmd
 *
 *    spic_rx_cmd is an entry function to switch between 8IO or non-8IO rx_cmd functions depending on flash types.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_rx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    hal_spic_stubs.spic_rx_cmd(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_tx_cmd_8io
 *
 *    spic_tx_cmd_8io is used to send flash commands which do not return values for Adesto 8IO flash.
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
__STATIC_INLINE void spic_tx_cmd_8io(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    hal_spic_stubs.spic_tx_cmd_8io(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_tx_cmd_4io
 *
 *    spic_tx_cmd_4io is used to send flash commands which do not return values for most of non-8IO flash.
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
__STATIC_INLINE void spic_tx_cmd_4io(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    hal_spic_stubs.spic_tx_cmd_4io(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_tx_cmd
 *
 *    spic_tx_cmd is an entry function to switch between 8IO or non-8IO tx_cmd functions depending on flash types.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_tx_cmd(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    hal_spic_stubs.spic_tx_cmd(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_tx_cmd_8io_no_check
 *
 *    spic_tx_cmd_8io_no_check is used to send flash commands which do not return values for Adesto 8IO flash.
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
__STATIC_INLINE void spic_tx_cmd_8io_no_check(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    hal_spic_stubs.spic_tx_cmd_8io_no_check(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_tx_cmd_4io_no_check
 *
 *    spic_tx_cmd_4io_no_check is used to send flash commands which do not return values for most of non-8IO flash.
 *    These commands could be erase command or set flash registers.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_tx_cmd_4io_no_check(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    hal_spic_stubs.spic_tx_cmd_4io_no_check(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_tx_cmd_no_check
 *
 *    spic_tx_cmd_no_check is an entry function to switch between 8IO or non-8IO tx_cmd_no_check functions depending on flash types.
 *
 *   \param phal_spic_adaptor_t phal_spic_adaptor:      The pointer of the flash controller adaptor.
 *   \param u8 cmd:      The command byte.
 *   \param u8 data_phase_len:      The length of data followed by command phase.
 *   \param u8 *pdata:      The data followed by command phase.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_tx_cmd_no_check(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata)
{
    hal_spic_stubs.spic_tx_cmd_no_check(phal_spic_adaptor, cmd, data_phase_len, pdata);
}

/** \brief Description of spic_wait_ready
 *
 *    spic_wait_ready is used to check if the flash controller is ready.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_wait_ready(SPIC_Type *spic_dev)
{
    hal_spic_stubs.spic_wait_ready(spic_dev);
}

/** \brief Description of spic_flush_fifo
 *
 *    spic_flush_fifo is used to flush FIFO of the flash controller.
 *
 *   \param SPIC_Type *spic_dev:      The pointer of the flash controller register base.
 *
 *   \return void.
 */
__STATIC_INLINE void spic_flush_fifo(SPIC_Type *spic_dev)
{
    hal_spic_stubs.spic_flush_fifo(spic_dev);
}

/** *@} */ /* End of group ls_hal_spic_ram_func */


#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_SPIC_H_"


