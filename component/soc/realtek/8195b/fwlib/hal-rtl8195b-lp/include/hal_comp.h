/**************************************************************************//**
 * @file     hal_comp.h
 * @brief    The HAL API implementation for the Comparator device.
 * @version  V1.00
 * @date     2016-07-15
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


#ifndef _HAL_COMP_H_
#define _HAL_COMP_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup ls_hal_comp COMP
 * @ingroup 8195bl_hal
 * @{
 * @brief The COMP HAL module of the LS platform.
 */

/** \brief Description of hal_comp_atuo_chsw_mode_ctrl
 *
 *    hal_comp_atuo_chsw_mode_ctrl is used to control automatic channel switch (auto mode)
 *    enabled or disabled.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param[in] uint8_t auto_mode_enable:               Comparator mode is enable or disable.
 *   \return void
 */
__STATIC_INLINE void hal_comp_atuo_chsw_mode_ctrl (hal_comp_adapter_t *phal_comp_adapter, uint8_t auto_mode_enable)
{
    phal_comp_adapter->init_dat.reg_base->auto_sw_en = auto_mode_enable;
}

/** \brief Description of hal_comp_timer_trig_ctrl
 *
 *    hal_comp_timer_trig_ctrl is used to set timer trigger mode is enable or disabled.
 *
 *   \param hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param uint8_t timer_trig_enable:              enable/disable.
 *   \return NA.
 */
__STATIC_INLINE void hal_comp_timer_trig_ctrl (hal_comp_adapter_t *phal_comp_adapter, uint8_t timer_trig_enable)
{
    phal_comp_adapter->init_dat.reg_base->wk_timer = timer_trig_enable;
}

/** \brief Description of hal_comp_set_trig_timer
 *
 *    hal_comp_set_trig_timer is used to set timer module number for comparator trigger source.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control adapter.
 *   \param[in] uint8_t timer_number:                   timer number.
 *   \return void
 */
__STATIC_INLINE void hal_comp_set_trig_timer (hal_comp_adapter_t *phal_comp_adapter, uint8_t timer_number)
{
    phal_comp_adapter->init_dat.reg_base->wk_timer_sel = timer_number;
}

/** \brief Description of hal_comp_reset_list
 *
 *    hal_comp_reset_list is used to reset channel switch list to the default state.
 *
 *   \param[in] hal_comp_adapter_t *phal_comp_adapter:        Pointer to comparator control data.
 *   \return void
*/
__STATIC_INLINE void hal_comp_reset_list (hal_comp_adapter_t *phal_comp_adapter)
{
    phal_comp_adapter->init_dat.reg_base->rst_list = 1;
    phal_comp_adapter->init_dat.reg_base->rst_list = 0;
}

//void hal_comp_irq_handler (hal_comp_adapter_t *phal_comp_adapter);
uint8_t hal_comp_timeout_chk (uint32_t start_cnt, uint32_t comp_timeout_cnt);
hal_status_t hal_comp_pure_init (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_pure_deinit (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_pin_init (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_pin_deinit (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_init (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_deinit (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_sw_trig (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_auto_chsw_ctrl (hal_comp_adapter_t *phal_comp_adapter, uint8_t auto_sw_en);
hal_status_t hal_comp_set_chsw_list (hal_comp_adapter_t *phal_comp_adapter, uint8_t *chlist, uint8_t list_len);
void hal_comp_set_refv (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t refv0, uint8_t refv1);
void hal_comp_set_intr_rule (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar, uint8_t intr_rule);
void hal_comp_clear_intr_rule (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel ,uint8_t intr_tar);
uint8_t hal_comp_get_intr_sts (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar);
void hal_comp_clear_intr_sts (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar);
uint8_t hal_comp_get_ana_sts (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel);
void hal_comp_load_default (hal_comp_adapter_t *phal_comp_adapter);

/** @} */ /* End of group ls_hal_comp */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_TIMER_H_"


