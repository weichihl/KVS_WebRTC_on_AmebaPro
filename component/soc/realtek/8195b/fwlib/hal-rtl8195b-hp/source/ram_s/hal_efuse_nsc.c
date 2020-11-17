/**************************************************************************//**
* @file         hal_efuse_nsc.c
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
#include "hal_efuse_nsc.h"


#if CONFIG_EFUSE_EN && CONFIG_EFUSE_NSC_EN

#if defined(CONFIG_BUILD_SECURE)

/**
 * @defgroup hs_hal_efuse_nsc_api EFUSE HAL NSC APIs.
 * @ingroup hs_hal_efuse
 * @{
 * @brief EFUSE HAL NSC (Non-Secure Callable) APIs.
 */

/**
 *  @brief The NSC function to select hs efuse cell.
 *
 *  @param[in]  efuse_size  efuse size.
 *
 *  @return  void
 */
SECTION_NS_ENTRY_FUNC
void NS_ENTRY hal_efuse_set_cell_sel_nsc (efuse_size_t efuse_size)
{
    hal_efuse_set_cell_sel(efuse_size);
}

/**
 *  @brief The NSC function to enable hs efuse autoload.
 *
 *  @param[in]  enable  enable.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_efuse_autoload_en_nsc(uint8_t enable)
{
    return hal_efuse_autoload_en(enable);
}

/**
 *  @brief The NSC function to read hs efuse.
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  addr                 read address.
 *  @param[in]  pdata               address of read back data.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_efuse_read_nsc (uint32_t ctrl_setting, uint16_t addr, uint8_t *pdata, uint8_t l25out_voltage)
{
    return hal_efuse_read(ctrl_setting, addr, pdata, l25out_voltage);
}

/**
 *  @brief The NSC function to write hs efuse.
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  addr                 write address.
 *  @param[in]  data                 write data.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_efuse_write_nsc (uint32_t ctrl_setting, uint16_t   addr, uint8_t data, uint8_t l25out_voltage)
{
    return hal_efuse_write(ctrl_setting, addr, data, l25out_voltage);
}

/**
 *  @brief The NSC function to enable hci efuse autoload.
 *
 *  @param[in]  enable  enable.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_efuse_hci_autoload_en_nsc(uint8_t enable)
{
    return hal_efuse_hci_autoload_en(enable);
}

/**
 *  @brief The NSC function to get user otp
 *
 *  @param[in]  ctrl_setting       control register setting.
 *  @param[in]  puser_otp         adress of read back user otp.
 *  @param[in]  l25out_voltage  LDOE25 voltage select.
 *
 *  @return  SUCCESS
 *  @return  FAIL
 */
SECTION_NS_ENTRY_FUNC
uint32_t NS_ENTRY hal_user_otp_get_nsc(uint8_t *puser_otp)
{
    return hal_user_otp_get(puser_otp);
}

/** @} */ /* End of group hs_hal_efuse_nsc_api */

#endif // end of "#if defined(CONFIG_BUILD_SECURE)"
#endif  /* end of "#if CONFIG_EFUSE_EN && CONFIG_EFUSE_NSC_EN" */

