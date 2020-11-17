 /**************************************************************************//**
  * @file     hal_flash_nsc.c
  * @brief    Execute flash commands in non-secure mode through non-secure callable functions.
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
#include "hal_flash.h"
#include "hal_flash_nsc.h"



#if defined(CONFIG_BUILD_SECURE)

/**

        \addtogroup hs_hal_flash_nsc_api FLASH HAL NSC APIs
        \ingroup hs_hal_flash
        \brief The FLASH HAL NSC (Non-Secure Callable) APIs. Non-secure domain is allowed to access secure functions through NSC APIs.
        @{
*/


/** \brief Description of Non-secure callable function hal_flash_read_unique_id_nsc
 *
 *    hal_flash_read_unique_id_nsc is used to read unique ID for the flash.
 *    This function is only valid for Winbond Flash.
 *    The ID is unique for each flash sample even if the part number is the name.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param uint8_t *buf:      The buff to store ID.
 *   \param uint8_t *len:      The lenght of ID.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_read_unique_id_nsc (phal_spic_adaptor_t phal_spic_adaptor, uint8_t *buf, uint8_t len)
{
    hal_flash_read_unique_id(phal_spic_adaptor, buf, len);
}

/** \brief Description of Non-secure callable function hal_flash_read_id_nsc
 *
 *    hal_flash_read_id_nsc is used to read ID for the flash.
 *    Flash with the same part number has the same flash ID.
 *    ID can be used to identify the type of flash.
 *    The ID information is stored in the flash adaptor.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return hal_status_t.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_flash_read_id_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    return hal_flash_read_id(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_set_write_enable_nsc
 *
 *    hal_flash_set_write_enable_nsc is used to send write enable command.
 *    After the command is sent, SPIC checks if the write enable bit is set or not.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_set_write_enable_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_set_write_enable(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_set_status_nsc
 *
 *    hal_flash_set_status_nsc is used to send write status register command.
 *    Write status register command may not be the same for different status registers or different flash types.
 *    Users can input an instruction and a value according to flash data sheet to set the status register.
 *    The function will check if flash is ready after setting the status register.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:      The instruction of write status register command.
 *   \param u8 data:     The value is going to be set in status register.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_set_status_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data)
{
    hal_flash_set_status(phal_spic_adaptor, cmd, data);
}

/** \brief Description of Non-secure callable function hal_flash_set_status_no_check_nsc
 *
 *    hal_flash_set_status_no_check_nsc is used to send write status register command.
 *    Write status register command may not be the same for different status registers or different flash types.
 *    Users can input an instruction and a value according to flash data sheet to set the status register.
 *    The function will NOT check if flash is ready after setting the status register.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:      The instruction of write status register command.
 *   \param u8 data:     The value is going to be set in status register.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_set_status_no_check_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data)
{
    hal_flash_set_status_no_check(phal_spic_adaptor, cmd, data);
}

/** \brief Description of Non-secure callable function hal_flash_set_status_with_addr_nsc
 *
 *    hal_flash_set_status_with_addr_nsc is used to send write status register with address command.
 *    Write status register command may not be the same for different status registers or different flash types.
 *    Some write status commands allow to carry one address byte to identify which status register.
 *    Users can input an instruction, an address and a value according to flash data sheet to set the status register.
 *    The function will check if flash is ready after setting the status register.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:      The instruction of write status register command.
 *   \param u8 addr:     The address of write status register command.
 *   \param u8 data:     The value is going to be set in status register.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_set_status_with_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 addr, u8 data)
{
    hal_flash_set_status_with_addr(phal_spic_adaptor, cmd, addr, data);
}

/** \brief Description of Non-secure callable function hal_flash_set_extended_addr_nsc
 *
 *    hal_flash_set_extended_addr_nsc is used to send set extended address command.
 *    Flash access 128 Mbit region at most with three address bytes.
 *    With this command, the value followed by the command presents the fourth address byte.
 *    Flash accesses beyond 128 Mbit region by setting different value of the fourth address byte to switch among different 128 Mbit bank.
 *    Some flashes cannot support this feature, please refer to flash data sheets.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 data:     The fourth address byte.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_set_extended_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 data)
{
    hal_flash_set_extended_addr(phal_spic_adaptor, data);
}

/** \brief Description of Non-secure callable function hal_flash_set_write_protect_mode_nsc
 *
 *    hal_flash_set_write_protect_mode_nsc is used to send set write protect mode command.
 *    Write protect feature can be either by multiple blocks or by individual block.
 *    Only some of Winbond flashes support this feature.
 *    The block protect control byte is written to one of the status register.
 *    Please refer to flash data sheet for more details
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 mode:     The block protect control parameter.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_set_write_protect_mode_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 mode)
{
    hal_flash_set_write_protect_mode(phal_spic_adaptor, mode);
}

/** \brief Description of Non-secure callable function hal_flash_get_status_nsc
 *
 *    hal_flash_get_status_nsc is used to send read status register command.
 *    Each flash may have more than one status registers that can be accessed with different instructions.
 *    Please refer to flash data sheet for more details
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:     The instruction of read status register command.
 *
 *   \return u8: the value of the status register.
 */
SECTION_NS_ENTRY_FUNC
u8 NS_ENTRY hal_flash_get_status_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd)
{
    return hal_flash_get_status(phal_spic_adaptor, cmd);
}

/** \brief Description of Non-secure callable function hal_flash_get_status_with_addr_nsc
 *
 *    hal_flash_get_status_with_addr_nsc is used to send read status register command.
 *    Each flash may have more than one status registers that can be accessed with different instructions.
 *    A address byte followed by the instruction is sent to identify which status register.
 *    Please refer to flash data sheet for more details
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:     The instruction of read status register command.
 *   \param u8 addr:    The address byte of read status register command.
 *
 *   \return u8: the value of the status register.
 */
SECTION_NS_ENTRY_FUNC
u8 NS_ENTRY hal_flash_get_status_with_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 addr)
{
    return hal_flash_get_status_with_addr(phal_spic_adaptor, cmd, addr);
}

/** \brief Description of Non-secure callable function hal_flash_get_extended_addr_nsc
 *
 *    hal_flash_get_extended_addr_nsc is used to send read extended address register command.
 *    The value of the extended address register presents the fourth byte of the address phase.
 *    Some flashes cannot support this feature, please refer to flash data sheets.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return u8: the value of the extended addr register.
 */
SECTION_NS_ENTRY_FUNC
u8 NS_ENTRY hal_flash_get_extended_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    return hal_flash_get_extended_addr(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_wait_ready_nsc
 *
 *    hal_flash_wait_ready_nsc is used to check the BUSY/WIP bit of the status register.
 *    This function polls the BUSY/WIP of the status register until flash returns to ready state.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_wait_ready_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_wait_ready(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_chip_erase_nsc
 *
 *    hal_flash_chip_erase_nsc is used to send chip erase command.
 *    This function aims to erase whole flash chip.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_chip_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_chip_erase(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_64k_block_erase_nsc
 *
 *    hal_flash_64k_block_erase_nsc is used to send 64K block erase command.
 *    This function aims to erase 64K byte blocks.
 *    The address is aligned to 64K byte boundaries.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to be erased.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_64k_block_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address)
{
    hal_flash_64k_block_erase(phal_spic_adaptor, address);
}

/** \brief Description of Non-secure callable function hal_flash_32k_block_erase_nsc
 *
 *    hal_flash_32k_block_erase_nsc is used to send 32K block erase command.
 *    This function aims to erase 32K byte blocks.
 *    The address is aligned to 32K byte boundaries.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to be erased.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_32k_block_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address)
{
    hal_flash_32k_block_erase(phal_spic_adaptor, address);
}

/** \brief Description of Non-secure callable function hal_flash_sector_erase_nsc
 *
 *    hal_flash_sector_erase_nsc is used to send sector erase command.
 *    This function aims to erase 4K byte sectors.
 *    The address is aligned to 4K byte boundaries.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to be erased.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_sector_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address)
{
    hal_flash_sector_erase(phal_spic_adaptor, address);
}

/** \brief Description of Non-secure callable function hal_flash_query_sector_protect_state_nsc
 *
 *    hal_flash_query_sector_protect_state_nsc is used to query the sector's write protect status.
 *    This function is only valid for flashes supporting individual block protect or sector protect feature.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to query write protect state.
 *
 *   \return u8: the write protect status.
 */
SECTION_NS_ENTRY_FUNC
u8 NS_ENTRY hal_flash_query_sector_protect_state_nsc(phal_spic_adaptor_t phal_spic_adaptor, u32 address)
{
    return hal_flash_query_sector_protect_state(phal_spic_adaptor, address);
}

/** \brief Description of Non-secure callable function hal_flash_protect_sector_nsc
 *
 *    hal_flash_protect_sector_nsc is used to send individual write protect command.
 *    This function is only valid for flashes supporting individual block protect or sector protect feature.
 *    For actual protect regions depending on flash types.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to enable write protect.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_protect_sector_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address)
{
    hal_flash_protect_sector(phal_spic_adaptor, address);
}

/** \brief Description of Non-secure callable function hal_flash_unprotect_sector_nsc
 *
 *    hal_flash_unprotect_sector_nsc is used to send individual write unprotect command.
 *    This function is only valid for flashes supporting individual block protect or sector protect feature.
 *    For actual protect regions depending on flash types.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to disable write protect.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_unprotect_sector_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address)
{
    hal_flash_unprotect_sector(phal_spic_adaptor, address);
}

/** \brief Description of Non-secure callable function hal_flash_global_lock_nsc
 *
 *    hal_flash_global_lock_nsc is used to send whole chip write protect command.
 *    This function is only valid some of Winbond flash.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_global_lock_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_global_lock(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_global_unlock_nsc
 *
 *    hal_flash_global_unlock_nsc is used to send whole chip write unprotect command.
 *    This function is only valid some of Winbond flash.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_global_unlock_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_global_unlock(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_set_dummy_cycle_nsc
 *
 *    hal_flash_set_dummy_cycle_nsc is used to configure flash dummy cycle.
 *    Flash allows users to adjust dummy cycles with various operting frequency under multiple IO modes.
 *    Higher speed requires more dummy cycles.
 *    We take into account the SPIC clock source and performance to derive optimal operating frequnecy of flash.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_set_dummy_cycle_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_set_dummy_cycle(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_set_quad_enable_nsc
 *
 *    hal_flash_set_quad_enable_nsc is used to set quad enable bit of flash.
 *    Some flash types require flash to set quad enable bit before switching to Quad IO mode.
 *    Only Winbond and MXIC supports this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_set_quad_enable_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_set_quad_enable(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_unset_quad_enable_nsc
 *
 *    hal_flash_unset_quad_enable_nsc is used to clear quad enable bit of flash.
 *    Quad IO bit should be cleaned before switching to other non-Quad IO mode.
 *    Only Winbond and MXIC supports this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_unset_quad_enable_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_unset_quad_enable(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_enable_qpi_nsc
 *
 *    hal_flash_enable_qpi_nsc is used to switch flash to QPI mode (4-4-4).
 *    Quad enable bit is set before SPIC sends enter QPI mode command.
 *    Only Adesto, Winbond and MXIC supports this function.
 *    Must ensure flash is under SPI mode before CPU enters this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_enable_qpi_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_enable_qpi(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_enable_opi_nsc
 *
 *    hal_flash_enable_opi_nsc is used to switch flash to OPI mode (8-8-8).
 *    Only Adesto supports this function.
 *    Must ensure flash is under SPI mode before CPU enters this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_enable_opi_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_enable_opi(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_return_spi_nsc
 *
 *    hal_flash_return_spi_nsc is used to switch flash back to SPI mode.
 *    Unlike flash_reset_to_spi_rtl8195bhp function recovering flash back to SPI mode from abnormal state,
 *    this funciton is a bridge to switch between different IO mode when flash is under control.
 *    Every IO mode should call this function to switch back to SPI mode before flash enters the other IO mode.
 *    Only Adesto, Winbond and MXIC support this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_return_spi_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_return_spi(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_return_str_nsc
 *
 *    hal_flash_return_str_nsc is used to set SPIC, not flash, to STR mode
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_return_str_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_return_str(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_enable_opi_dtr_nsc
 *
 *    hal_flash_enable_opi_dtr_nsc is used to set flash to OPI DTR mode.
 *    Must ensure flash is under SPI mode before the processor jumps to this function.
 *    Only Adesto flash support this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_enable_opi_dtr_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_enable_opi_dtr(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_disable_dtr_nsc
 *
 *    hal_flash_disable_dtr_nsc is used to set octal flash to STR mode.
 *    This function switch IO mode from 4D-4D-4D, 8D-8D-8D to 4-4-4 and 8-8-8 respectively.
 *    Only Adesto flash support this function.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_disable_dtr_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_disable_dtr(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_enter_power_down_nsc
 *
 *    hal_flash_enter_power_down_nsc is used to send deep power down command.
 *    Flash enters deep power down state after this function.
 *    Any access except few commands is ignored by flash.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return hal_status_t.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_flash_enter_power_down_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    return hal_flash_enter_power_down(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_release_from_power_down_nsc
 *
 *    hal_flash_release_from_power_down_nsc is used to send release from deep power down command.
 *    Flash returns from deep power down state after this function.
 *    It can accept any command normally.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return hal_status_t.
 */
SECTION_NS_ENTRY_FUNC
hal_status_t NS_ENTRY hal_flash_release_from_power_down_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    return hal_flash_release_from_power_down(phal_spic_adaptor);
}

/** \brief Description of Non-secure callable function hal_flash_stream_read_nsc
 *
 *    hal_flash_stream_read_nsc is used to read sequential data with auto mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting read address in flash.
 *   \param u8 *data:      The destination address in memory to store data.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_stream_read_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data)
{
    hal_flash_stream_read(phal_spic_adaptor, length, addr, data);
}

/** \brief Description of Non-secure callable function hal_flash_stream_write_nsc
 *
 *    hal_flash_stream_write_nsc is used to program sequential data with auto mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting program address in flash.
 *   \param u8 *data:      The address of data. Data stored in ram is about to be programmed to the flash.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_stream_write_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data)
{
    hal_flash_stream_write(phal_spic_adaptor, length, addr, data);
}

/** \brief Description of Non-secure callable function hal_flash_burst_read_nsc
 *
 *    hal_flash_burst_read_nsc is used to read sequential data with user mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting read address in flash.
 *   \param u8 *data:      The destination address in memory to store data.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_burst_read_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data)
{
    hal_flash_burst_read(phal_spic_adaptor, length, addr, data);
}

/** \brief Description of Non-secure callable function hal_flash_burst_write_nsc
 *
 *    hal_flash_burst_write_nsc is used to program sequential data with user mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting program address in flash.
 *   \param u8 *data:      The address of data. Data stored in ram is about to be programmed to the flash.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_burst_write_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data)
{
    hal_flash_burst_write(phal_spic_adaptor, length, addr, data);
}

/** \brief Description of Non-secure callable function hal_flash_page_program_nsc
 *
 *    hal_flash_page_program_nsc is used to divide total transfer length into several pages.
 *    Each page program command can program 256 bytes, a page size, at most.
 *    Multiple program commands should be sent if the transfer length is larger than the page size.
 *    Please refer to flash data sheets about page program command for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting program address in flash.
 *   \param u8 *data:      The address of data. Data stored in ram is about to be programmed to the flash.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_page_program_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data)
{
    hal_flash_page_program(phal_spic_adaptor, length, addr, data);
}

/** \brief Description of Non-secure callable function hal_flash_reset_to_spi_nsc
 *
 *    hal_flash_reset_to_spi_nsc is used to reset flash back to SPI mode.
 *    This function is called when SPIC cannot read correct ID.
 *    It would be two scenarios that ID cannot be read.
 *    First, flash may enter unknown state that SPIC cannot access the flash with the correct IO mode.
 *    Second, flash may be in deep power down state so that commands sent by SPIC cannot be recognized.
 *    This function aims to wake up flash and reset it to default SPI mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_flash_reset_to_spi_nsc (phal_spic_adaptor_t phal_spic_adaptor)
{
    hal_flash_reset_to_spi(phal_spic_adaptor);
}

/** *@} */ /* End of group hs_hal_flash_nsc_api */

#endif
