/**************************************************************************//**
* @file         rtl8195blp_efuse.h
* @brief       The fundamental definition for RTL8195B LP Efuse module.
*
* @version    V1.00
* @date        2017-02-15
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



#ifndef RTL8195BLP_EFUSE_H
#define RTL8195BLP_EFUSE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup ls_hal_efuse EFUSE
 * @ingroup 8195bl_hal
 * @{
 * @brief The EFUSE HAL on LS platform.
 */


/**
  \brief  Define the EFUSE size.
*/
enum efuse_size_e {
      Size4KB   = 0x0,
      Size2KB   = 0x1,
      Size1KB   = 0x2,
      Size8KB   = 0x3
};
typedef uint8_t efuse_size_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup ls_hal_efuse_rom_func EFUSE HAL ROM APIs.
 * @ingroup ls_hal_efuse
 * @{
 */


/*  Function declaration   */
void hal_efuse_power_switch_rtl8195blp(uint8_t bwrite, uint8_t	pwr_state, uint8_t l25out_voltage);
void hal_efuse_hs_power_switch_rtl8195blp(uint8_t bwrite, uint8_t	pwr_state, uint8_t l25out_voltage);
void hal_efuse_set_cell_sel_rtl8195blp(efuse_size_t efuse_size);
uint32_t hal_efuse_autoload_en_rtl8195blp(uint8_t enable);
uint32_t hal_efuse_read_rtl8195blp(uint32_t ctrl_setting,	uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage);
uint32_t hal_efuse_write_rtl8195blp(uint32_t ctrl_setting, uint16_t	addr, uint8_t data, uint8_t l25out_voltage);
uint32_t hal_efuse_hs_autoload_en_rtl8195blp(uint8_t enable);
uint32_t hal_efuse_read_logical_rtl8195blp(uint32_t ctrl_setting,	uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage);
uint32_t hal_efuse_write_logical_rtl8195blp(uint32_t ctrl_setting, uint16_t addr, uint8_t data, uint8_t l25out_voltage);

/** @} */ /* End of group ls_hal_efuse_rom_func */

/// @endcond    /* End of cond DOXYGEN_ROM_HAL_API */


/**
  \brief  The data structure of the stubs function for the EFUSE HAL functions in ROM
*/
typedef struct hal_efuse_func_stubs_s {
    void (*hal_efuse_set_cell_sel) (efuse_size_t efuse_size);
    uint32_t (*hal_efuse_autoload_en) (uint8_t enable);
    uint32_t (*hal_efuse_read) (uint32_t ctrl_setting,	uint16_t addr, uint8_t *data, uint8_t l25out_voltage);
    uint32_t (*hal_efuse_write) (uint32_t ctrl_setting, uint16_t	addr, uint8_t data, uint8_t l25out_voltage);
    uint32_t (*hal_efuse_hs_autoload_en) (uint8_t enable);
    uint32_t (*hal_efuse_read_logical)(uint32_t ctrl_setting, uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage);
    uint32_t (*hal_efuse_write_logical)(uint32_t ctrl_setting, uint16_t addr, uint8_t data, uint8_t l25out_voltage);
    uint32_t reserved[10]; // reserved space for next ROM code version function table extending.
}hal_efuse_func_stubs_t;

/** @} */ /* End of group ls_hal_efuse */

#ifdef __cplusplus
}
#endif

#endif /* RTL8195BLP_EFUSE_H */

