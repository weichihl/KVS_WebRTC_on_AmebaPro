/**************************************************************************//**
 * @file     hal_flash_nsc.h
 * @brief    The header file of hal_flash_nsc.c.
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

#ifndef _HAL_FLASH_NSC_H_
#define _HAL_FLASH_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */

#ifdef  __cplusplus
 extern "C"
 {
#endif

#if defined(CONFIG_BUILD_SECURE)
/**

        \addtogroup hs_hal_flash_nsc_api FLASH HAL NSC APIs
        \ingroup hs_hal_flash
        \brief The FLASH HAL NSC (Non-Secure Callable) APIs. Non-secure domain is allowed to access secure functions through NSC APIs.
        @{
*/


void NS_ENTRY hal_flash_read_unique_id_nsc (phal_spic_adaptor_t phal_spic_adaptor, uint8_t *buf, uint8_t len);
hal_status_t NS_ENTRY hal_flash_read_id_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_set_write_enable_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_set_status_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data);
void NS_ENTRY hal_flash_set_status_no_check_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data);
void NS_ENTRY hal_flash_set_status_with_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 addr, u8 data);
void NS_ENTRY hal_flash_set_extended_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 data);
void NS_ENTRY hal_flash_set_write_protect_mode_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 mode);
u8 NS_ENTRY hal_flash_get_status_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd);
u8 NS_ENTRY hal_flash_get_status_with_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 addr);
u8 NS_ENTRY hal_flash_get_extended_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_wait_ready_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_chip_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_64k_block_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
void NS_ENTRY hal_flash_32k_block_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
void NS_ENTRY hal_flash_sector_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
u8 NS_ENTRY hal_flash_query_sector_protect_state_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
void NS_ENTRY hal_flash_protect_sector_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
void NS_ENTRY hal_flash_unprotect_sector_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
void NS_ENTRY hal_flash_global_lock_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_global_unlock_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_set_dummy_cycle_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_set_quad_enable_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_unset_quad_enable_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_enable_qpi_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_enable_opi_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_return_spi_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_return_str_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_enable_opi_dtr_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_disable_dtr_nsc (phal_spic_adaptor_t phal_spic_adaptor);
hal_status_t NS_ENTRY hal_flash_enter_power_down_nsc (phal_spic_adaptor_t phal_spic_adaptor);
hal_status_t NS_ENTRY hal_flash_release_from_power_down_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY hal_flash_stream_read_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data);
void NS_ENTRY hal_flash_stream_write_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data);
void NS_ENTRY hal_flash_burst_read_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data);
void NS_ENTRY hal_flash_burst_write_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data);
void NS_ENTRY hal_flash_page_program_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data);
void NS_ENTRY hal_flash_reset_to_spi_nsc (phal_spic_adaptor_t phal_spic_adaptor);
/** *@} */ /* End of group hs_hal_flash_nsc_api */


#endif // end of "#if defined(CONFIG_BUILD_SECURE)"


#if defined(CONFIG_BUILD_NONSECURE)
void hal_flash_read_unique_id_nsc (phal_spic_adaptor_t phal_spic_adaptor, uint8_t *buf, uint8_t len);
hal_status_t hal_flash_read_id_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_set_write_enable_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_set_status_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data);
void hal_flash_set_status_no_check_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data);
void hal_flash_set_status_with_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 addr, u8 data);
void hal_flash_set_extended_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 data);
void hal_flash_set_write_protect_mode_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 mode);
u8 hal_flash_get_status_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd);
u8 hal_flash_get_status_with_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 addr);
u8 hal_flash_get_extended_addr_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_wait_ready_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_chip_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_64k_block_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
void hal_flash_32k_block_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
void hal_flash_sector_erase_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
u8 hal_flash_query_sector_protect_state_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
void hal_flash_protect_sector_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
void hal_flash_unprotect_sector_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 address);
void hal_flash_global_lock_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_global_unlock_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_set_dummy_cycle_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_set_quad_enable_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_unset_quad_enable_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_enable_qpi_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_enable_opi_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_return_spi_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_return_str_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_enable_opi_dtr_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_disable_dtr_nsc (phal_spic_adaptor_t phal_spic_adaptor);
hal_status_t hal_flash_enter_power_down_nsc (phal_spic_adaptor_t phal_spic_adaptor);
hal_status_t hal_flash_release_from_power_down_nsc (phal_spic_adaptor_t phal_spic_adaptor);
void hal_flash_stream_read_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data);
void hal_flash_stream_write_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data);
void hal_flash_burst_read_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data);
void hal_flash_burst_write_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data);
void hal_flash_page_program_nsc (phal_spic_adaptor_t phal_spic_adaptor, u32 length, u32 addr, u8 *data);
void hal_flash_reset_to_spi_nsc (phal_spic_adaptor_t phal_spic_adaptor);

#define hal_flash_read_unique_id                hal_flash_read_unique_id_nsc
#define hal_flash_read_id                       hal_flash_read_id_nsc
#define hal_flash_set_write_enable              hal_flash_set_write_enable_nsc
#define hal_flash_set_status                    hal_flash_set_status_nsc
#define hal_flash_set_status_no_check           hal_flash_set_status_no_check_nsc
#define hal_flash_set_status_with_addr          hal_flash_set_status_with_addr_nsc
#define hal_flash_set_extended_addr             hal_flash_set_extended_addr_nsc
#define hal_flash_set_write_protect_mode        hal_flash_set_write_protect_mode_nsc
#define hal_flash_get_status                    hal_flash_get_status_nsc
#define hal_flash_get_status_with_addr          hal_flash_get_status_with_addr_nsc
#define hal_flash_get_extended_addr             hal_flash_get_extended_addr_nsc
#define hal_flash_wait_ready                    hal_flash_wait_ready_nsc
#define hal_flash_chip_erase                    hal_flash_chip_erase_nsc
#define hal_flash_64k_block_erase               hal_flash_64k_block_erase_nsc
#define hal_flash_32k_block_erase               hal_flash_32k_block_erase_nsc
#define hal_flash_sector_erase                  hal_flash_sector_erase_nsc
#define hal_flash_set_dummy_cycle               hal_flash_set_dummy_cycle_nsc
#define hal_flash_query_sector_protect_state    hal_flash_query_sector_protect_state_nsc
#define hal_flash_protect_sector                hal_flash_protect_sector_nsc
#define hal_flash_unprotect_sector              hal_flash_unprotect_sector_nsc
#define hal_flash_global_lock                   hal_flash_global_lock_nsc
#define hal_flash_global_unlock                 hal_flash_global_unlock_nsc
#define hal_flash_set_quad_enable               hal_flash_set_quad_enable_nsc
#define hal_flash_unset_quad_enable             hal_flash_unset_quad_enable_nsc
#define hal_flash_enable_qpi                    hal_flash_enable_qpi_nsc
#define hal_flash_enable_opi                    hal_flash_enable_opi_nsc
#define hal_flash_return_spi                    hal_flash_return_spi_nsc
#define hal_flash_return_str                    hal_flash_return_str_nsc
#define hal_flash_enable_opi_dtr                hal_flash_enable_opi_dtr_nsc
#define hal_flash_disable_dtr                   hal_flash_disable_dtr_nsc
#define hal_flash_enter_power_down              hal_flash_enter_power_down_nsc
#define hal_flash_release_from_power_down       hal_flash_release_from_power_down_nsc
#define hal_flash_stream_read                   hal_flash_stream_read_nsc
#define hal_flash_stream_write                  hal_flash_stream_write_nsc
#define hal_flash_burst_read                    hal_flash_burst_read_nsc
#define hal_flash_burst_write                   hal_flash_burst_write_nsc
#define hal_flash_page_program                  hal_flash_page_program_nsc
#define hal_flash_reset_to_spi                  hal_flash_reset_to_spi_nsc
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

#ifdef  __cplusplus
 }
#endif


#endif  // end of "#define _HAL_FLASH_NSC_H_"

