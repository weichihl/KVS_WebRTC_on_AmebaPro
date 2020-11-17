/**************************************************************************//**
 * @file     hal_adc.h
 * @brief    The HAL API implementation for the ADC device.
 * @version  V1.00
 * @date     2016-12-14
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

#ifndef _HAL_ADC_H_
#define _HAL_ADC_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif


extern const hal_adc_func_stubs_t hal_adc_stubs;

/**
 * @addtogroup hs_hal_adc ADC
 * @ingroup 8195bh_hal
 * @{
 * @brief The ADC HAL module of the LS platform.
 */


__STATIC_INLINE void hal_adc_set_mod (hal_adc_adapter_t *phal_adc_adapter, uint8_t mod)
{
    phal_adc_adapter->init_dat.reg_base->conf_b.op_mod = mod;
}

/** \brief Description of hal_adc_auto_chsw_ctrl
 *
 *    hal_adc_auto_chsw_ctrl is used to enable/disable auto mode.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t auto_enable:                enable/ disable auto chsw.
 *   \return void
 */
__STATIC_INLINE void hal_adc_auto_chsw_ctrl (hal_adc_adapter_t *phal_adc_adapter, uint8_t auto_enable)
{
    phal_adc_adapter->init_dat.reg_base->auto_chsw_ctrl = auto_enable;
}

/** \brief Description of hal_adc_get_last_item
 *
 *    hal_adc_get_last_item is used to read the last cvlist item number which\n
 *    the last conversion is executed.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \return uint32_t:            item number in cvlist
 */
__STATIC_INLINE uint32_t hal_adc_get_last_item (hal_adc_adapter_t *phal_adc_adapter)
{
    return (uint32_t)phal_adc_adapter->init_dat.reg_base->last_item;
}

/** \brief Description of hal_adc_get_empty_sts
 *
 *    hal_adc_get_empty_sts is used to read adc empty status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint32_t:                              0: not empty; 1: empty
 */
__STATIC_INLINE uint32_t hal_adc_get_empty_sts (hal_adc_adapter_t *phal_adc_adapter)
{
    if (phal_adc_adapter->init_dat.reg_base->sts_b.empty) {
        return (uint32_t)1;
    } else {
        return (uint32_t)0;
    }
}

/** \brief Description of hal_adc_get_fifo_no
 *
 *    hal_adc_get_fifo_no is used to read adc fifo entry number.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint32_t:                              fifo entry number
 */
__STATIC_INLINE uint32_t hal_adc_get_fifo_no (hal_adc_adapter_t *phal_adc_adapter)
{
    return (uint32_t)(phal_adc_adapter->init_dat.reg_base->flr);
}

/** \brief Description of hal_adc_set_full_level
 *
 *    hal_adc_set_full_level is used to set adc fifo full level.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint8_t full_lvl:                       Full level.
 *   \return void
 */
__STATIC_INLINE void hal_adc_set_full_level (hal_adc_adapter_t *phal_adc_adapter, uint8_t full_lvl)
{
    if ((full_lvl == 0) || (full_lvl > HP_ADC_FIFO_LEN)) {
        DBG_ADC_ERR("Given full level is larger than HW supported.");
    }

    phal_adc_adapter->init_dat.reg_base->full_lvl_b.full_lvl = (full_lvl - 1);
}

/** \brief Description of hal_adc_get_full_level
 *
 *    hal_adc_get_full_level is used to get adc fifo full level.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint8_t:       ADC full level.
 */
__STATIC_INLINE uint8_t hal_adc_get_full_level (hal_adc_adapter_t *phal_adc_adapter)
{
    return (uint8_t)(phal_adc_adapter->init_dat.reg_base->full_lvl + 1);
}

/** \brief Description of hal_adc_set_in_tape_all
 *
 *    hal_adc_set_in_tape_all is used to set channel input type register directly.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint32_t in_type_mask:                  Mask to ADC input type register.
 *   \return void
 */
__STATIC_INLINE void hal_adc_set_in_tape_all (hal_adc_adapter_t *phal_adc_adapter, uint32_t in_type_mask)
{
    phal_adc_adapter->init_dat.reg_base->in_type = in_type_mask;
}

/** \brief Description of hal_adc_set_trig_timer
 *
 *    hal_adc_set_trig_timer is used to set timer module number for adc conversion trigger source.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint8_t timer_number:                   Timer number for ADC timer trigger source.
 *   \return void
 */
__STATIC_INLINE void hal_adc_set_trig_timer (hal_adc_adapter_t *phal_adc_adapter, uint8_t timer_number)
{
    phal_adc_adapter->init_dat.trig_timer = timer_number;
    phal_adc_adapter->init_dat.reg_base->trig_timer_sel = timer_number;
}

/** \brief Description of hal_adc_set_cv_intr_ch
 *
 *    hal_adc_set_cv_intr_ch is used to set channel number for channel conversion interrrupt.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                          Channel number.
 *   \return void
 */
__STATIC_INLINE void hal_adc_set_cv_intr_ch (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
    phal_adc_adapter->init_dat.reg_base->it_chno_con = ch_no;
}

/** \brief Description of hal_adc_get_cv_intr_ch
 *
 *    hal_adc_get_cv_intr_ch is used to get channel number for channel conversion interrrupt.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint8_t:                       ADC channel number.
 */
__STATIC_INLINE uint8_t hal_adc_get_cv_intr_ch (hal_adc_adapter_t *phal_adc_adapter)
{
    return (uint8_t)(phal_adc_adapter->init_dat.reg_base->it_chno_con);
}

/** \brief Description of hal_adc_clear_all_intr
 *
 *    hal_adc_clear_all_intr is used to clear all pending interrupt status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
__STATIC_INLINE void hal_adc_clear_all_intr (hal_adc_adapter_t *phal_adc_adapter)
{
    phal_adc_adapter->init_dat.reg_base->intr_sts = 0xFFFFFFFF;
}

/** \brief Description of hal_adc_reset_list
 *
 *    hal_adc_reset_list is used to reset cvlist to the default state.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
__STATIC_INLINE void hal_adc_reset_list (hal_adc_adapter_t *phal_adc_adapter)
{
    phal_adc_adapter->init_dat.reg_base->rst_list = 1;
    phal_adc_adapter->init_dat.reg_base->rst_list = 0;
}

uint32_t hal_adc_calc_cali_val(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para);

/** \brief Description of hal_adc_read_fifo
 *
 *    hal_adc_read_fifo is used to read the fifo register(global) without any trigger operations.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint16_t:                              channel conversion data.
 */
__STATIC_INLINE uint16_t hal_adc_read_fifo (hal_adc_adapter_t *phal_adc_adapter, uint8_t out_raw)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    return (uint16_t)(phal_adc_adapter->init_dat.reg_base->dat_global_b.dat);
#else
    return (uint16_t)(hal_adc_stubs.hal_adc_read_fifo(phal_adc_adapter, out_raw));
#endif
}

__STATIC_INLINE uint32_t hal_adc_read_fifo_w_sts (hal_adc_adapter_t *phal_adc_adapter)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    return (uint32_t)(phal_adc_adapter->init_dat.reg_base->dat_global);
#else
    adc_dat_global_t dat_tmp;
    dat_tmp.w = (phal_adc_adapter->init_dat.reg_base->dat_global);
    
    if (phal_adc_adapter->use_cali) {
        dat_tmp.b.dat = hal_adc_calc_cali_val((uint16_t)(dat_tmp.b.dat), (hal_adc_cali_para_t *)&(hal_adc_stubs.hal_adc_cali_para));
    }

    return (uint32_t)dat_tmp.w;
#endif
}

uint8_t hal_adc_timeout_chk (hal_adc_adapter_t *phal_adc_adapter, uint32_t start_cnt);
void hal_adc_sw_cv_trig (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pure_init (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pure_deinit (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_set_in_type (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t input_type);
uint8_t hal_adc_get_in_type (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
hal_status_t hal_adc_set_comp_thld (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint16_t thld_high, uint16_t thld_low);
hal_status_t hal_adc_set_comp_rule (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t comp_rule);
void hal_adc_clear_comp_intr_sts (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
void hal_adc_intr_ctrl (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option, uint8_t intr_enable);
void hal_adc_clear_intr_sts (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option);
hal_status_t hal_adc_set_cvlist (hal_adc_adapter_t *phal_adc_adapter, uint8_t *cvlist, uint8_t cvlist_len);
uint8_t hal_adc_item_to_ch (hal_adc_adapter_t *phal_adc_adapter, uint8_t item_no);
void hal_adc_load_default (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pin_init (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pin_deinit (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_init (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_deinit (hal_adc_adapter_t *phal_adc_adapter);
uint16_t hal_adc_single_read (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
void hal_adc_clear_fifo (hal_adc_adapter_t *phal_adc_adapter);
uint16_t hal_adc_read_ch_dat (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t out_raw);
hal_status_t hal_adc_read_continuous (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf,
                                                    uint8_t trigger_source);
hal_status_t hal_adc_dma_init (hal_adc_adapter_t *phal_adc_adapter, hal_gdma_adaptor_t *padc_gdma_adaptor);
hal_status_t hal_adc_dma_deinit (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_read_dma (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf, uint8_t trigger_source);

#if (CHIP_VER == CHIP_A_CUT)
hal_status_t hal_adc_pwr_init_rtl8195bhp_patch (hal_adc_adapter_t *phal_adc_adapter);
#endif

int16_t hal_adc_calc_gain_deno(int16_t ideal_co_1, int16_t ideal_co_0);
int16_t hal_adc_calc_gain_mole(int16_t real_co_1, int16_t real_co_0);
int32_t hal_adc_calc_offset_deno(int16_t ideal_co_1, int16_t ideal_co_0, int16_t real_co_1, int16_t real_co_0);
int16_t hal_adc_calc_offset_mole(int16_t real_co_1, int16_t real_co_0);
//uint16_t hal_adc_calc_cali_val(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para);
void hal_adc_read_cali_param(uint16_t addr, uint8_t *param_addr, uint8_t param_len);
void hal_adc_write_cali_param(uint16_t addr, uint8_t *param_addr, uint8_t param_len);
uint16_t hal_adc_single_read_rtl8195bhp_patch (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
/** @} */ /* End of group ls_hal_adc */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_ADC_H_"

