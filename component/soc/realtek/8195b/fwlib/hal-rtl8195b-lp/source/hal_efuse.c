/**************************************************************************//**
* @file         hal_efuse.c
* @brief       This file implements the entry functions of the Efuse HAL ROM functions.
*
* @version    V1.00
* @date        2017-02-13
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


#include "hal_efuse.h"

#if CONFIG_EFUSE_EN

/**
 * @addtogroup ls_hal_efuse EFUSE
 * @{
 */


/**
* @brief The stubs functions table to exports EFUSE HAL functions in ROM.
*/
extern hal_efuse_func_stubs_t hal_efuse_stubs;

/**
 *  @brief To select ls efuse cell
 *
 *  @param[in]  efuse_size  efuse size.
 *
 *  @return  void
 */
void hal_efuse_set_cell_sel (efuse_size_t efuse_size)
{
    hal_efuse_stubs.hal_efuse_set_cell_sel(efuse_size);
}

/**
 *  @brief To enable ls efuse autoload
 *
 *  @param[in]  enable  enable.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_efuse_autoload_en(uint8_t enable)
{
    return hal_efuse_stubs.hal_efuse_autoload_en(enable);
}

/**
 *  @brief To read ls efuse
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  addr                 read address.
 *  @param[in]  pdata               address of read back data.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_efuse_read (uint32_t ctrl_setting,	uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_efuse_read(ctrl_setting, addr, pdata, l25out_voltage);
}

/**
 *  @brief To write ls efuse
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  addr                 write address.
 *  @param[in]  data                 write data.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_efuse_write (uint32_t ctrl_setting, uint16_t	addr, uint8_t data, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_efuse_write(ctrl_setting, addr, data, l25out_voltage);
}

/**
 *  @brief To enable hs efuse autoload
 *
 *  @param[in]  enable  enable.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_efuse_hs_autoload_en(uint8_t enable)
{
    return hal_efuse_stubs.hal_efuse_hs_autoload_en(enable);
}

/**
 *  @brief To read logical region of ls efuse
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  addr                 read address.
 *  @param[in]  pdata               address of read back data.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_efuse_read_logical (uint32_t ctrl_setting,	uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_efuse_read_logical(ctrl_setting, addr, pdata, l25out_voltage);
}

/**
 *  @brief To write logical region of ls efuse
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  addr                 write address.
 *  @param[in]  data                 write data.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_efuse_write_logical (uint32_t ctrl_setting, uint16_t addr, uint8_t data, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_efuse_write_logical(ctrl_setting, addr, data, l25out_voltage);
}

/**
 *  @brief To disable LP jtag
 *
 *  @return  void
 */
void hal_efuse_disable_lp_jtag (void)
{
    hal_efuse_stubs.hal_efuse_write(0x50300000, 0x00, 0xFC, 7);
}

/**
 *  @brief To disable HS secure jtag
 *
 *  @return  void
 */
void hal_efuse_disable_sec_jtag (void)
{
    hal_efuse_stubs.hal_efuse_write(0x50300000, 0x00, 0xCF, 7);
}

/**
 *  @brief To disable HS nonsecure jtag
 *
 *  @return  void
 */
void hal_efuse_disable_nonsec_jtag (void)
{
    hal_efuse_stubs.hal_efuse_write(0x50300000, 0x00, 0x3F, 7);
}

/** @} */ /* End of group ls_hal_efuse */


#endif  /* end of "#if CONFIG_EFUSE_EN" */


