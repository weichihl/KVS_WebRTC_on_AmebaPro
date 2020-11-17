/**************************************************************************//**
 * @file     hal_flash.h
 * @brief    Provide stub functions for RAM code to access FLASH ROM functions.
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

#ifndef _HAL_FLASH_H_
#define _HAL_FLASH_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

extern const hal_flash_func_stubs_t hal_flash_stubs;

/**

        \addtogroup ls_hal_flash FLASH
        @{
*/

/**

        \addtogroup ls_hal_gdma_flash_func FLASH HAL RAM APIs
        \ingroup ls_hal_flash
        \brief The FLASH HAL APIs. Functions become an interface between API functions and ROM codes.
        @{
*/


/** \brief Description of hal_flash_load_setting
 *
 *    hal_flash_load_setting is used to load flash command pointer and dummy cycle pointer according to flash type.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_load_setting(void *adaptor)
{
    hal_flash_stubs.hal_flash_load_setting(adaptor);
}

/** \brief Description of hal_flash_set_write_enable
 *
 *    hal_flash_set_write_enable is used to send write enable command.
 *    After the command is sent, SPIC checks if the write enable bit is set or not.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_set_write_enable(void *adaptor)
{
    hal_flash_stubs.hal_flash_set_write_enable(adaptor);
}

/** \brief Description of hal_flash_set_status
 *
 *    hal_flash_set_status is used to send write status register command.
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
__STATIC_INLINE void hal_flash_set_status(void *adaptor, u8 cmd, u8 data)
{
    hal_flash_stubs.hal_flash_set_status(adaptor, cmd, data);
}

/** \brief Description of hal_flash_set_status_no_check
 *
 *    hal_flash_set_status_no_check is used to send write status register command.
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
__STATIC_INLINE void hal_flash_set_status_no_check(void *adaptor, u8 cmd, u8 data)
{
    hal_flash_stubs.hal_flash_set_status_no_check(adaptor, cmd, data);
}

/** \brief Description of hal_flash_set_status_with_addr
 *
 *    hal_flash_set_status_with_addr is used to send write status register with address command.
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
__STATIC_INLINE void hal_flash_set_status_with_addr(void *adaptor, u8 cmd, u8 addr, u8 data)
{
    hal_flash_stubs.hal_flash_set_status_with_addr(adaptor, cmd, addr, data);
}

/** \brief Description of hal_flash_set_extended_addr
 *
 *    hal_flash_set_extended_addr is used to send set extended address command.
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
__STATIC_INLINE void hal_flash_set_extended_addr(void *adaptor, u8 data)
{
    hal_flash_stubs.hal_flash_set_extended_addr(adaptor, data);
}

/** \brief Description of hal_flash_get_status
 *
 *    hal_flash_get_status is used to send read status register command.
 *    Each flash may have more than one status registers that can be accessed with different instructions.
 *    Please refer to flash data sheet for more details
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u8 cmd:     The instruction of read status register command.
 *
 *   \return u8: the value of the status register.
 */
__STATIC_INLINE u8 hal_flash_get_status(void *adaptor, u8 cmd)
{
    return hal_flash_stubs.hal_flash_get_status(adaptor, cmd);
}

/** \brief Description of hal_flash_get_status_with_addr
 *
 *    hal_flash_get_status_with_addr is used to send read status register command.
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
__STATIC_INLINE u8 hal_flash_get_status_with_addr(void *adaptor, u8 cmd, u8 addr)
{
    return hal_flash_stubs.hal_flash_get_status_with_addr(adaptor, cmd, addr);
}

/** \brief Description of hal_flash_get_extended_addr
 *
 *    hal_flash_get_extended_addr is used to send read extended address register command.
 *    The value of the extended address register presents the fourth byte of the address phase.
 *    Some flashes cannot support this feature, please refer to flash data sheets.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return u8: the value of the extended addr register.
 */
__STATIC_INLINE u8 hal_flash_get_extended_addr(void *adaptor)
{
    return hal_flash_stubs.hal_flash_get_extended_addr(adaptor);
}

/** \brief Description of hal_flash_wait_ready
 *
 *    hal_flash_wait_ready is used to check the BUSY/WIP bit of the status register.
 *    This function polls the BUSY/WIP of the status register until flash returns to ready state.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_wait_ready(void *adaptor)
{
    hal_flash_stubs.hal_flash_wait_ready(adaptor);
}

/** \brief Description of hal_flash_chip_erase
 *
 *    hal_flash_chip_erase is used to send chip erase command.
 *    This function aims to erase whole flash chip.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_chip_erase(void *adaptor)
{
    hal_flash_stubs.hal_flash_chip_erase(adaptor);
}

/** \brief Description of hal_flash_64k_block_erase
 *
 *    hal_flash_64k_block_erase is used to send 64K block erase command.
 *    This function aims to erase 64K byte blocks.
 *    The address is aligned to 64K byte boundaries.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to be erased.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_64k_block_erase(void *adaptor, u32 address)
{
    hal_flash_stubs.hal_flash_64k_block_erase(adaptor, address);
}

/** \brief Description of hal_flash_32k_block_erase
 *
 *    hal_flash_32k_block_erase is used to send 32K block erase command.
 *    This function aims to erase 32K byte blocks.
 *    The address is aligned to 32K byte boundaries.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to be erased.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_32k_block_erase(void *adaptor, u32 address)
{
    hal_flash_stubs.hal_flash_32k_block_erase(adaptor, address);
}

/** \brief Description of hal_flash_sector_erase
 *
 *    hal_flash_sector_erase is used to send sector erase command.
 *    This function aims to erase 4K byte sectors.
 *    The address is aligned to 4K byte boundaries.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to be erased.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_sector_erase(void *adaptor, u32 address)
{
    hal_flash_stubs.hal_flash_sector_erase(adaptor, address);
}

/** \brief Description of hal_flash_query_sector_protect_state
 *
 *    hal_flash_query_sector_protect_state is used to query the sector's write protect status.
 *    This function is only valid for flashes supporting individual block protect or sector protect feature.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to query write protect state.
 *
 *   \return u8: the write protect status.
 */
__STATIC_INLINE u8 hal_flash_query_sector_protect_state(void *adaptor, u32 address)
{
    return hal_flash_stubs.hal_flash_query_sector_protect_state(adaptor, address);
}

/** \brief Description of hal_flash_protect_sector
 *
 *    hal_flash_protect_sector is used to send individual write protect command.
 *    This function is only valid for flashes supporting individual block protect or sector protect feature.
 *    For actual protect regions depending on flash types.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to enable write protect.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_protect_sector(void *adaptor, u32 address)
{
    hal_flash_stubs.hal_flash_protect_sector(adaptor, address);
}

/** \brief Description of hal_flash_unprotect_sector
 *
 *    hal_flash_unprotect_sector is used to send individual write unprotect command.
 *    This function is only valid for flashes supporting individual block protect or sector protect feature.
 *    For actual protect regions depending on flash types.
 *    Please refer to flash data sheets for more details.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 address:      The target address to disable write protect.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_unprotect_sector(void *adaptor, u32 address)
{
    hal_flash_stubs.hal_flash_unprotect_sector(adaptor, address);
}

/** \brief Description of hal_flash_enter_power_down
 *
 *    hal_flash_enter_power_down is used to send deep power down command.
 *    Flash enters deep power down state after this function.
 *    Any access except few commands is ignored by flash.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return hal_status_t.
 */
__STATIC_INLINE hal_status_t hal_flash_enter_power_down(void *adaptor)
{
    return hal_flash_stubs.hal_flash_enter_power_down(adaptor);
}

/** \brief Description of hal_flash_release_from_power_down
 *
 *    hal_flash_release_from_power_down is used to send release from deep power down command.
 *    Flash returns from deep power down state after this function.
 *    It can accept any command normally.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *
 *   \return hal_status_t.
 */
__STATIC_INLINE hal_status_t hal_flash_release_from_power_down(void *adaptor)
{
    return hal_flash_stubs.hal_flash_release_from_power_down(adaptor);
}

/** \brief Description of hal_flash_stream_read
 *
 *    hal_flash_stream_read is used to read sequential data with auto mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting read address in flash.
 *   \param u8 *data:      The destination address in memory to store data.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_stream_read(void *adaptor, u32 length, u32 addr, u8 *data)
{
    hal_flash_stubs.hal_flash_stream_read(adaptor, length, addr, data);
}

/** \brief Description of hal_flash_burst_read
 *
 *    hal_flash_burst_read is used to read sequential data with user mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting read address in flash.
 *   \param u8 *data:      The destination address in memory to store data.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_burst_read(void *adaptor, u32 length, u32 addr, u8 *data)
{
    hal_flash_stubs.hal_flash_burst_read(adaptor, length, addr, data);
}

/** \brief Description of hal_flash_burst_write
 *
 *    hal_flash_burst_write is used to program sequential data with user mode.
 *
 *   \param void *adaptor:      The pointer of the flash adaptor.
 *   \param u32 length:      The transfer length.
 *   \param u32 addr:      The starting program address in flash.
 *   \param u8 *data:      The address of data. Data stored in ram is about to be programmed to the flash.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_flash_burst_write(void *adaptor, u32 length, u32 addr, u8 *data)
{
    hal_flash_stubs.hal_flash_burst_write(adaptor, length, addr, data);
}

/** \brief Description of hal_flash_page_program
 *
 *    hal_flash_page_program is used to divide total transfer length into several pages.
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
__STATIC_INLINE void hal_flash_page_program(void *adaptor, u32 length, u32 addr, u8 *data)
{
    hal_flash_stubs.hal_flash_page_program(adaptor, length, addr, data);
}

/** *@} */ /* End of group ls_hal_flash_ram_func */

/** *@} */ /* End of group ls_hal_flash */


#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_FLASH_H_"



