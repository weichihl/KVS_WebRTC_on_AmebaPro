/**************************************************************************//**
* @file         hal_efuse.c
* @brief       This file implements the entry functions of the Efuse HAL ROM functions.
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



#include "hal_efuse.h"

#if CONFIG_EFUSE_EN
/**
 * @addtogroup hs_hal_efuse EFUSE
 * @{
 */

/**
  * @brief The global EFUSE HAL adapter(management entity).
  */
extern hal_efuse_func_stubs_t hal_efuse_stubs;

/**
 *  @brief To select hs efuse cell
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
 *  @brief To enable hs efuse autoload
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
 *  @brief To read hs efuse
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  addr                 read address.
 *  @param[in]  pdata               address of read back data.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_efuse_read (uint32_t ctrl_setting, uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_efuse_read(ctrl_setting, addr, pdata, l25out_voltage);
}

/**
 *  @brief To write hs efuse
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  addr                 write address.
 *  @param[in]  data                 write data.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_efuse_write (uint32_t ctrl_setting, uint16_t   addr, uint8_t data, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_efuse_write(ctrl_setting, addr, data, l25out_voltage);
}

/**
 *  @brief To enable hci efuse autoload
 *
 *  @param[in]  enable  enable.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_efuse_hci_autoload_en(uint8_t enable)
{
    return hal_efuse_stubs.hal_efuse_hci_autoload_en(enable);
}

/**
 *  @brief To read hs efuse through security register
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  addr                 read address.
 *  @param[in]  pdata               address of read back data.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_sec_efuse_read(uint32_t ctrl_setting,	uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_sec_efuse_read(ctrl_setting, addr, pdata, l25out_voltage);
}

/**
 *  @brief To write hs efuse through security register
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  addr                 write address.
 *  @param[in]  data                 write data.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_sec_efuse_write(uint32_t ctrl_setting, uint16_t   addr, uint8_t data, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_sec_efuse_write(ctrl_setting, addr, data, l25out_voltage);
}

/**
 *  @brief To write super security key
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  psusec_key       address of 32-byte super security key.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_susec_key_write(uint8_t *psusec_key)
{
    return hal_efuse_stubs.hal_susec_key_write(0x37F00000, psusec_key, 7);
}

/**
 *  @brief To get user otp
 *
 *  @param[in]  puser_otp         adress of read back user otp.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_user_otp_get(uint8_t *puser_otp)
{
    return hal_efuse_stubs.hal_user_otp_get(0x37F00000, puser_otp, 7);
}

/**
 *  @brief To get security key
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  psec_key          adress of read back security key.
 *  @param[in]  length              security key length.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_sec_key_get(uint32_t ctrl_setting, uint8_t *psec_key, uint32_t length, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_sec_key_get(ctrl_setting, psec_key, length, l25out_voltage);
}

/**
 *  @brief To get super security key
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  psec_key          adress of read back 32-byte super security key.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_susec_key_get(uint32_t ctrl_setting, uint8_t *psusec_key, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_susec_key_get(ctrl_setting, psusec_key, l25out_voltage);
}

/**
 *  @brief To compare designate offset of super security key
 *
 *  @param[in]  addr                comapre offset of super security key.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_susec_key_comp(uint8_t addr)
{
    return hal_efuse_stubs.hal_susec_key_comp(addr);
}

/**
 *  @brief To compare 32-byte super security key
 *
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_susec_key_comp_all(void)
{
    return hal_efuse_stubs.hal_susec_key_comp_all();
}

/**
 *  @brief To write security key
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  psec_key          address of 32-byte security key.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_sec_key_write(uint8_t *psec_key)
{
    return hal_efuse_stubs.hal_sec_key_write(0x37F00000, psec_key, 7);
}

/**
 *  @brief To write writable security zone
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  offset               write offset.
 *  @param[in]  length              write length.
 *  @param[in]  pcontent           address of write content.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
uint32_t hal_sec_zone_write(uint32_t ctrl_setting, uint8_t offset, uint8_t length, uint8_t *pcontent, uint8_t l25out_voltage)
{
    return hal_efuse_stubs.hal_sec_zone_write(ctrl_setting, offset, length, pcontent, l25out_voltage);
}

/**
 *  @brief To set user otp
 *
 *  @param[in]  puser_otp         adress of user otp value.
 *
 *  @return  void
 */
void hal_user_otp_set(uint8_t *puser_otp)
{
    uint8_t idx = 0;
    uint8_t data_tmp;
    
    for(idx = 0; idx < 32; idx++) {
        hal_efuse_stubs.hal_efuse_read(0x37F00000, (0x110+idx), (&data_tmp), 7);

        if(data_tmp == 0xFF) {
            hal_efuse_stubs.hal_efuse_write(0x37F00000, (0x110+idx), (*(puser_otp+idx)), 7);    
        }
    }
}

/** @} */ /* End of group hs_hal_efuse */


#endif  /* end of "#if CONFIG_EFUSE_EN" */

