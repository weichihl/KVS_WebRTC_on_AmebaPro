/**************************************************************************//**
 * @file     hal_comp.c
 * @brief    This file implements the entry functions of the Comparator HAL ROM functions.
 *
 * @version  V1.00
 * @date     2016-12-01
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


#include "hal_comp.h"

#if CONFIG_COMP_EN

#if   defined ( __CC_ARM )                                            /* ARM Compiler 4/5 */
extern hal_comp_func_stubs_t Image$$_STUB_COMP$$Base;     // symbol from linker script
#define __rom_stubs_hal_comp Image$$_STUB_COMP$$Base
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)       /* ARM Compiler 6 */
extern hal_comp_func_stubs_t Image$$_STUB_COMP$$Base;     // symbol from linker script
#define __rom_stubs_hal_comp Image$$_STUB_COMP$$Base
#elif defined ( __GNUC__ )
extern hal_comp_func_stubs_t __rom_stubs_hal_comp;     // symbol from linker script
#elif defined ( __ICCARM__ )
extern hal_comp_func_stubs_t __rom_stubs_hal_comp;     // symbol from linker script

#endif

/**
 * @addtogroup ls_hal_comp COMP
 * @{
 */

/** \brief Description of hal_comp_timeout_chk
 *
 *    hal_comp_timeout_chk is used to check if comparator operation is timeout.
 *
 *   \param[in] uint32_t start_cnt:                     Timer start count.
 *   \param[in] uint32_t comp_timeout_cnt:              Timer time-out count.
 *   \return uint8_t:                               Timeout or not.
 */
uint8_t hal_comp_timeout_chk (uint32_t start_cnt, uint32_t comp_timeout_cnt)
{
    return __rom_stubs_hal_comp.hal_comp_timeout_chk(start_cnt, comp_timeout_cnt);
}

/** \brief Description of hal_comp_pure_init
 *
 *    hal_comp_pure_init is used to initialize comparator module.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_comp_pure_init (hal_comp_adapter_t *phal_comp_adapter)
{
    return __rom_stubs_hal_comp.hal_comp_pure_init(phal_comp_adapter);
}

/** \brief Description of hal_comp_pure_deinit
 *
 *    hal_comp_pure_deinit is used to deinitialize comparator module.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_comp_pure_deinit (hal_comp_adapter_t *phal_comp_adapter)
{
    return __rom_stubs_hal_comp.hal_comp_pure_deinit(phal_comp_adapter);
}

/** \brief Description of hal_comp_pin_init
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_comp_pin_init (hal_comp_adapter_t *phal_comp_adapter)
{
    return __rom_stubs_hal_comp.hal_comp_pin_init(phal_comp_adapter);
}

/** \brief Description of hal_comp_pin_deinit
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_comp_pin_deinit (hal_comp_adapter_t *phal_comp_adapter)
{
    return __rom_stubs_hal_comp.hal_comp_pin_deinit(phal_comp_adapter);
}

/** \brief Description of hal_comp_init_rtl819blp
 *
 *    hal_comp_init_rtl819blp is used for comparator initialization with pwoer state.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \return hal_status_t.
 */
hal_status_t hal_comp_init (hal_comp_adapter_t *phal_comp_adapter)
{
    return __rom_stubs_hal_comp.hal_comp_init(phal_comp_adapter);
}

/** \brief Description of hal_comp_deinit_rtl819blp
 *
 *    hal_comp_deinit_rtl819blp is used for comparator deinitialization with pwoer state.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adaptor.
 *   \return hal_status_t.
 */
hal_status_t hal_comp_deinit (hal_comp_adapter_t *phal_comp_adapter)
{
    return __rom_stubs_hal_comp.hal_comp_deinit(phal_comp_adapter);
}

/** \brief Description of hal_comp_sw_trig
 *
 *    hal_comp_sw_trig is used to execute comparator software channel switch trigger.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:       Pointer to comparator control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_comp_sw_trig (hal_comp_adapter_t *phal_comp_adapter)
{
    return __rom_stubs_hal_comp.hal_comp_sw_trig(phal_comp_adapter);
}

/** \brief Description of hal_comp_auto_chsw_ctrl
 *
 *    hal_comp_auto_chsw_ctrl is used to enable/disable comparator auto channel switch.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param[in] uint8_t auto_sw_en:                     Auto channel switch enable/disable.
 *   \return hal_status_t
 */
hal_status_t hal_comp_auto_chsw_ctrl (hal_comp_adapter_t *phal_comp_adapter, uint8_t auto_sw_en)
{
    return __rom_stubs_hal_comp.hal_comp_auto_chsw_ctrl(phal_comp_adapter, auto_sw_en);
}

/** \brief Description of hal_comp_set_chsw_list
 *
 *    hal_comp_set_chsw_list is used to set comparator channel switch list.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param[in] uint8_t *chlist:                        Pointer to a channel conversion list. It should be an array start
 *                                                  address.
 *   \param[in] uint8_t list_len:                       Channel list len.
 *   \return hal_status_t
*/
hal_status_t hal_comp_set_chsw_list (hal_comp_adapter_t *phal_comp_adapter, uint8_t *chlist, uint8_t list_len)
{
    return __rom_stubs_hal_comp.hal_comp_set_chsw_list(phal_comp_adapter, chlist, list_len);
}

/** \brief Description of hal_comp_set_refv_rtl819blp
 *
 *    hal_comp_set_refv_rtl819blp is used to set comparator reference voltage.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param[in] uint8_t channel:                        Comparator channel number.
 *   \param[in] uint8_t refv0:                          Comparator reference voltage 0 that
 *                                                  would be regarded as lower reference voltage.
 *   \param[in] uint8_t refv1:                          Comparator reference voltage 1 that
 *                                                  would be regarded as higher reference voltage.
 *   \return void
*/
void hal_comp_set_refv (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t refv0, uint8_t refv1)
{
    __rom_stubs_hal_comp.hal_comp_set_refv(phal_comp_adapter, channel, refv0, refv1);
}

/** \brief Description of hal_comp_set_intr_rule
 *
 *    hal_comp_set_intr_rule is used to set comparator interrupt rule which is to interrupt system or \n
 *                                      to wake up ADC by sending trigger pulse internally.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param[in] uint8_t channel:                        Comparator channel number.
 *   \param[in] uint8_t intr_tar:                       Comparator interrupt target. 0: ADC module, 1: system.
 *   \param[in] uint8_t intr_rule:                      Comparator interrupt rule.
 *   \return void
*/
void hal_comp_set_intr_rule (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar, uint8_t intr_rule)
{
    __rom_stubs_hal_comp.hal_comp_set_intr_rule(phal_comp_adapter, channel, intr_tar, intr_rule);
}

/** \brief Description of hal_comp_clear_intr_rule
 *
 *    hal_comp_clear_intr_rule is used to clear comparator interrupt rule (disable.)
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param[in] uint8_t channel:                        Comparator channel number.
 *   \param[in] uint8_t intr_tar:                       Comparator interrupt target. 0: ADC module, 1: system.
 *   \return void
*/
void hal_comp_clear_intr_rule (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel ,uint8_t intr_tar)
{
    __rom_stubs_hal_comp.hal_comp_clear_intr_rule(phal_comp_adapter, channel ,intr_tar);
}

/** \brief Description of hal_comp_get_intr_sts
 *
 *    hal_comp_get_intr_sts is used to get interrupt status of each chaanel according to the interrupt target.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param[in] uint8_t channel:                        Comparator channel number.
 *   \param[in] uint8_t intr_tar:                       Comparator interrupt target. 0: ADC module, 1: system.
 *   \return uint8_t    interrupt status.
*/
uint8_t hal_comp_get_intr_sts (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar)
{
    return __rom_stubs_hal_comp.hal_comp_get_intr_sts(phal_comp_adapter, channel, intr_tar);
}

/** \brief Description of hal_comp_clear_intr_sts
 *
 *    hal_comp_clear_intr_sts is used to clear interrupt status.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param[in] uint8_t channel:                        Comparator channel number.
 *   \param[in] uint8_t intr_tar:                       Comparator interrupt target. 0: ADC module, 1: system.
 *   \return void
*/
void hal_comp_clear_intr_sts (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar)
{
    __rom_stubs_hal_comp.hal_comp_clear_intr_sts(phal_comp_adapter, channel, intr_tar);
}

/** \brief Description of hal_comp_get_ana_sts
 *
 *    hal_comp_get_ana_sts is used to get analog status.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param[in] uint8_t channel:                        Comparator channel number.
 *   \return uint8_t:       Comparator analog output status.
*/
uint8_t hal_comp_get_ana_sts (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel)
{
    return __rom_stubs_hal_comp.hal_comp_get_ana_sts(phal_comp_adapter, channel);
}

/** \brief Description of hal_comp_load_default
 *
 *    hal_comp_load_default is used to load the default value for comparator.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \return void
*/
void hal_comp_load_default (hal_comp_adapter_t *phal_comp_adapter)
{
    __rom_stubs_hal_comp.hal_comp_load_default(phal_comp_adapter);
}

/** \brief Description of hal_comp_reg_irq
 *
 *    hal_comp_reg_irq is used to register a irq handler

 *   \param hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adaptor.
 *   \param irq_handler_t handler:                IRQ handler function.
 *   \return void
 */
void hal_comp_reg_irq (hal_comp_adapter_t *phal_comp_adapter, irq_handler_t handler)
{
    __rom_stubs_hal_comp.hal_comp_reg_irq (phal_comp_adapter, handler);
}

/** \brief Description of hal_comp_unreg_irq
 *
 *    hal_comp_unreg_irq is used to unregister a irq handler

 *   \param hal_comp_adapter_t *phal_comp_adapter:        Pointer to ccmparator control adaptor.
 *   \return void
 */
void hal_comp_unreg_irq (hal_comp_adapter_t *phal_comp_adapter)
{
    __rom_stubs_hal_comp.hal_comp_unreg_irq (phal_comp_adapter);
}


/** @} */ /* End of group ls_hal_comp */

#endif  /* end of "#if CONFIG_COMP_EN" */


