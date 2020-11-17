/**************************************************************************//**
 * @file     hal_adc.c
 * @brief    This file implements the entry functions of the ADC HAL ROM functions.
 *
 * @version  V1.00
 * @date     2016-12-03
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

#include "hal_adc.h"
#include "hal_irq.h"
#include "hal_gdma.h"
#include "hal_efuse.h"

#if defined ( __GNUC__ )
#include <limits.h>
#else
#include "__limits.h"
#endif

#if CONFIG_ADC_EN

#if   defined ( __CC_ARM )                                            /* ARM Compiler 4/5 */
extern hal_adc_func_stubs_t Image$$_STUB_ADC$$Base;     // symbol from linker script
#define __rom_stubs_hal_adc Image$$_STUB_ADC$$Base
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)       /* ARM Compiler 6 */
extern hal_adc_func_stubs_t Image$$_STUB_ADC$$Base;     // symbol from linker script
#define __rom_stubs_hal_adc Image$$_STUB_ADC$$Base
#elif defined ( __GNUC__ )
extern hal_adc_func_stubs_t __rom_stubs_hal_adc;     // symbol from linker script
#elif defined ( __ICCARM__ )
extern hal_adc_func_stubs_t __rom_stubs_hal_adc;     // symbol from linker script

#endif

/**
 * @addtogroup ls_hal_adc ADC
 * @{
 */
/** \brief Description of hal_adc_timeout_chk
 *
 *    hal_adc_timeout_chk is used to check if adc operation is timeout.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:    Pointer to ADC control adapter.
 *   \param[in] uint32_t start_cnt:                     Timer start count.
 *   \return uint8_t:                                   Timeout or not.\n
 *                                                      0: not time-out. 1: time-out.
 */
uint8_t hal_adc_timeout_chk (hal_adc_adapter_t *phal_adc_adapter, uint32_t start_cnt)
{
    return __rom_stubs_hal_adc.hal_adc_timeout_chk(phal_adc_adapter, start_cnt);
}

/** \brief Description of hal_adc_sw_cv_trig
 *
 *    hal_adc_sw_cv_trig is used to execute ADC software conversion trigger.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
void hal_adc_sw_cv_trig (hal_adc_adapter_t *phal_adc_adapter)
{
    __rom_stubs_hal_adc.hal_adc_sw_cv_trig(phal_adc_adapter);
}

/** \brief Description of hal_adc_pure_init
 *
 *    hal_adc_pure_init is used to initialize ADC module.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:       Pointer to ADC control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_adc_pure_init (hal_adc_adapter_t *phal_adc_adapter)
{
    return __rom_stubs_hal_adc.hal_adc_pure_init(phal_adc_adapter);
}

/** \brief Description of hal_adc_pure_deinit
 *
 *    hal_adc_deinit is used to deinitialize ADC module.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:       Pointer to ADC control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_adc_pure_deinit (hal_adc_adapter_t *phal_adc_adapter)
{
    return __rom_stubs_hal_adc.hal_adc_pure_deinit(phal_adc_adapter);
}

/** \brief Description of hal_adc_set_in_type
 *
 *    hal_adc_set_in_type is used to set ADC channel input type.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \param[in] uint8_t input_type:                 Input type.
 *   \return hal_status_t:          return HAL_OK when the given parameters is correct.
 *                                  Only ch0~ch5 are capable of two input type (single-end and differential)
 */
hal_status_t hal_adc_set_in_type (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t input_type)
{
    return __rom_stubs_hal_adc.hal_adc_set_in_type(phal_adc_adapter, ch_no, input_type);
}

/** \brief Description of hal_adc_get_in_type
 *
 *    hal_adc_get_in_type is used to read ADC channel input type.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                              ADC channel number.
 *   \return uint8_t:                               channel input type.\n
 *                                                  0: single end, 1: differential.
 */
uint8_t hal_adc_get_in_type (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
    return __rom_stubs_hal_adc.hal_adc_get_in_type(phal_adc_adapter, ch_no);
}

/** \brief Description of hal_adc_set_comp_thld
 *
 *    hal_adc_set_comp_thld is used to set ADC channel comparison threshold.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \param[in] uint16_t thld_high:                 Comparison high threshold.
 *   \param[in] uint16_t thld_low:                  Comparison low threshold.
 *   \return hal_status_t
 */
hal_status_t hal_adc_set_comp_thld (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint16_t thld_high, uint16_t thld_low)
{
    return __rom_stubs_hal_adc.hal_adc_set_comp_thld(phal_adc_adapter, ch_no, thld_high, thld_low);
}

/** \brief Description of hal_adc_set_comp_rule
 *
 *    hal_adc_set_comp_rule is used to set ADC channel comparison control. When this is set to a particular\n
 *    criterion, the related comparison status and interrupt would be triggered.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \param[in] uint8_t comp_rule:                  Comparison rule.
 *   \return hal_status_t
 */
hal_status_t hal_adc_set_comp_rule (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t comp_rule)
{
    return __rom_stubs_hal_adc.hal_adc_set_comp_rule(phal_adc_adapter, ch_no, comp_rule);
}

/** \brief Description of hal_adc_clear_comp_intr_sts
 *
 *    hal_adc_clear_comp_intr_sts is used to clear adc comparison interrupt status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \return void
 */
void hal_adc_clear_comp_intr_sts (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
    __rom_stubs_hal_adc.hal_adc_clear_comp_intr_sts(phal_adc_adapter, ch_no);
}

/** \brief Description of hal_adc_intr_ctrl
 *
 *    hal_adc_intr_ctrl is used to control interrupt enable/disable.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t intr_option:                Interrupt option (source).\n
 *                                              0: cvlist end.          1: cv end.\n
 *                                              2: channel cv end.      3: fifo full.\n
 *                                              4: fifo over.           5: fifo empty.\n
 *                                              6: dat ovw.             7: err.
 *
 *   \param[in] uint8_t intr_enable:                Interrupt enable control.
 *   \return void
 */
void hal_adc_intr_ctrl (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option, uint8_t intr_enable)
{
    __rom_stubs_hal_adc.hal_adc_intr_ctrl(phal_adc_adapter, intr_option, intr_enable);
}

/** \brief Description of hal_adc_clear_intr_sts
 *
 *    hal_adc_clear_intr_sts is used to clear adc interrupt interrupt status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t intr_option:                Interrupt option (source).\n
 *                                              0: cvlist end.          1: cv end.\n
 *                                              2: channel cv end.      3: fifo full.\n
 *                                              4: fifo over.           5: fifo empty.\n
 *                                              6: dat ovw.             7: err.
 *   \return void
 */
void hal_adc_clear_intr_sts (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option)
{
    __rom_stubs_hal_adc.hal_adc_clear_intr_sts(phal_adc_adapter, intr_option);
}

/** \brief Description of hal_adc_set_cvlist
 *
 *    hal_adc_set_cvlist is used to set ADC channel conversion list.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t *cvlist:                    Pointer to a channel conversion list. It should be an array start address.
 *   \param[in] uint8_t cvlist_len:                 Conversion list length.
 *   \return hal_status_t
 */
hal_status_t hal_adc_set_cvlist (hal_adc_adapter_t *phal_adc_adapter, uint8_t *cvlist, uint8_t cvlist_len)
{
    return __rom_stubs_hal_adc.hal_adc_set_cvlist(phal_adc_adapter, cvlist, cvlist_len);
}

/** \brief Description of hal_adc_item_to_ch
 *
 *    hal_adc_item_to_ch is used to transfer a list item to channel number.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t item_no:                    Item number in the hardware list register.
 *   \return uint8_t:                           Channel number of the list item.
 */
uint8_t hal_adc_item_to_ch (hal_adc_adapter_t *phal_adc_adapter, uint8_t item_no)
{
    return __rom_stubs_hal_adc.hal_adc_item_to_ch(phal_adc_adapter, item_no);
}

/** \brief Description of hal_adc_load_default
 *
 *    hal_adc_load_default is used to load default value for data structure.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return void
 */
void hal_adc_load_default (hal_adc_adapter_t *phal_adc_adapter)
{
    __rom_stubs_hal_adc.hal_adc_load_default(phal_adc_adapter);
}

/** \brief Description of hal_adc_pin_init
 *
 *    hal_adc_pin_init is used for adc pinmux initialization.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return hal_status_t.
 */
hal_status_t hal_adc_pin_init (hal_adc_adapter_t *phal_adc_adapter)
{
    return __rom_stubs_hal_adc.hal_adc_pin_init(phal_adc_adapter);
}

/** \brief Description of hal_adc_pin_deinit
 *
 *    hal_adc_pin_deinit is used for adc pinmux de-initialization.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return hal_status_t.
 */
hal_status_t hal_adc_pin_deinit (hal_adc_adapter_t *phal_adc_adapter)
{
    return __rom_stubs_hal_adc.hal_adc_pin_deinit(phal_adc_adapter);
}

/** \brief Description of hal_adc_init_rtl819blp
 *
 *    hal_adc_init_rtl819blp is used for adc initialization with power state.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return hal_status_t.
 */
hal_status_t hal_adc_init (hal_adc_adapter_t *phal_adc_adapter)
{
    hal_adc_pll_init();
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_adc_init_rtl8195blp_patch(phal_adc_adapter);
#else
    hal_status_t adc_sts_ret;
    adc_sts_ret = __rom_stubs_hal_adc.hal_adc_init(phal_adc_adapter);
    hal_adc_set_pwr_cut(phal_adc_adapter);
    return adc_sts_ret;
#endif
}

/** \brief Description of hal_adc_unreg_irq
 *
 *    hal_adc_unreg_irq is used to unregister a irq handler

 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return void
 */
void hal_adc_unreg_irq (hal_adc_adapter_t *phal_adc_adapter)
{
    __rom_stubs_hal_adc.hal_adc_unreg_irq (phal_adc_adapter);
}

/** \brief Description of hal_adc_deinit_rtl819blp
 *
 *    hal_adc_deinit_rtl819blp is used for adc de-initialization with power state.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return hal_status_t.
 */
hal_status_t hal_adc_deinit (hal_adc_adapter_t *phal_adc_adapter)
{
    //return __rom_stubs_hal_adc.hal_adc_deinit(phal_adc_adapter);
    
    uint32_t gpio_shdn_bak = HAL_READ32(0xA0000000,0x340);
    hal_status_t retv = HAL_OK;
    retv = __rom_stubs_hal_adc.hal_adc_deinit(phal_adc_adapter);
    HAL_WRITE32(0xA0000000,0x340, gpio_shdn_bak);
    
#if 0
    hal_adc_unreg_irq(phal_adc_adapter);
    if (retv != HAL_OK) {
        return retv;
    }

    retv = __rom_stubs_hal_adc.hal_adc_pin_deinit(phal_adc_adapter);
    if (retv != HAL_OK) {
        return retv;
    }

    /* enable shutdown for digital pins */
    for (adc_ch_cnt = 0; adc_ch_cnt < LP_ADC_EXCH_NO; adc_ch_cnt++) {
        if (phal_adc_adapter->plft_dat.pin_en.w & ((uint32_t)0x01 << adc_ch_cnt)) {
            hal_gpio_shdn_en(adc_ch_cnt);
        }
    }
 
    phal_adc_adapter->status = ADCStatusUninitial;
#endif
    
    return retv;
}

/** \brief Description of hal_adc_single_read
 *
 *    hal_adc_single_read is used for single for particular channel. \n
 *    This function would automatically execute software trigger flow and return the channel data.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adaptor.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \return uint16_t:            ADC sample data.
 */
uint16_t hal_adc_single_read (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    hal_adc_cali_para_t adc_cali_paras_tmp;
    uint8_t cali_flag = phal_adc_adapter->use_cali;
    uint16_t adc_dat_tmp;

    hal_adc_read_cali_param(LP_ADC_GAIN_DENO_ADDR, &adc_cali_paras_tmp.gain_deno, 2);
    hal_adc_read_cali_param(LP_ADC_GAIN_MOLE_ADDR, &adc_cali_paras_tmp.gain_mole, 2);
    hal_adc_read_cali_param(LP_ADC_OFFSET_DENO_ADDR, &adc_cali_paras_tmp.offset_deno, 4);
    hal_adc_read_cali_param(LP_ADC_OFFSET_MOLE_ADDR, &adc_cali_paras_tmp.offset_mole, 2);
    DBG_8195BL("gain deno: %08x\n", adc_cali_paras_tmp.gain_deno);
    DBG_8195BL("gain mole: %08x\n", adc_cali_paras_tmp.gain_mole);
    DBG_8195BL("offset deno: %08x\n", adc_cali_paras_tmp.offset_deno);
    DBG_8195BL("offset mole: %08x\n", adc_cali_paras_tmp.offset_mole);

    phal_adc_adapter->use_cali = ADCDisable;
    adc_dat_tmp = __rom_stubs_hal_adc.hal_adc_single_read(phal_adc_adapter, ch_no);
    phal_adc_adapter->use_cali = cali_flag;
    if (phal_adc_adapter->use_cali != 0) {
        adc_dat_tmp = hal_adc_calc_cali_val((uint16_t)adc_dat_tmp, (hal_adc_cali_para_t *)&adc_cali_paras_tmp);
        hal_adc_set_pwr_cut(phal_adc_adapter);
        return (uint16_t)(adc_dat_tmp & LP_ADC_DATA_MASK);
    } else {
        hal_adc_set_pwr_cut(phal_adc_adapter);
        return (uint16_t)(adc_dat_tmp & LP_ADC_DATA_MASK);
    }
#else

    if (phal_adc_adapter->init_dat.hw_mode == ADCAutoMod) {
        hal_adc_cali_para_t adc_cali_paras_tmp;
        uint8_t cali_flag = phal_adc_adapter->use_cali;
        uint16_t adc_dat_tmp;

        hal_adc_read_cali_param(LP_ADC_GAIN_DENO_ADDR, (uint8_t*)&adc_cali_paras_tmp.gain_deno, 2);
        hal_adc_read_cali_param(LP_ADC_GAIN_MOLE_ADDR, (uint8_t*)&adc_cali_paras_tmp.gain_mole, 2);
        hal_adc_read_cali_param(LP_ADC_OFFSET_DENO_ADDR, (uint8_t*)&adc_cali_paras_tmp.offset_deno, 4);
        hal_adc_read_cali_param(LP_ADC_OFFSET_MOLE_ADDR, (uint8_t*)&adc_cali_paras_tmp.offset_mole, 2);

        phal_adc_adapter->use_cali = ADCDisable;
        adc_dat_tmp = __rom_stubs_hal_adc.hal_adc_read_ch_dat(phal_adc_adapter, ch_no, 1);
        phal_adc_adapter->use_cali = cali_flag;
        if (phal_adc_adapter->use_cali != 0) {
            adc_dat_tmp = hal_adc_calc_cali_val((uint16_t)adc_dat_tmp, (hal_adc_cali_para_t *)&adc_cali_paras_tmp);
            return (uint16_t)(adc_dat_tmp & LP_ADC_DATA_MASK);
        } else {
            return (uint16_t)(adc_dat_tmp & LP_ADC_DATA_MASK);
        }
    }else if (phal_adc_adapter->init_dat.hw_mode == ADCSWTrigMod){
        uint16_t adc_ret;
        adc_ret = __rom_stubs_hal_adc.hal_adc_single_read(phal_adc_adapter, ch_no);
        hal_adc_set_pwr_cut(phal_adc_adapter);
        return adc_ret;
    }    
#endif
}

/** \brief Description of hal_adc_clear_fifo
 *
 *    hal_adc_clear_fifo is used to clear FIFO to the default state.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
void hal_adc_clear_fifo (hal_adc_adapter_t *phal_adc_adapter)
{
    __rom_stubs_hal_adc.hal_adc_clear_fifo(phal_adc_adapter);
}

/** \brief Description of hal_adc_read_ch_dat
 *
 *    hal_adc_read_ch_dat is used to read the channel data directly without any trigger operation.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                          Channel number.
 *   \return uint16_t:                              channel conversion data.\n
 *                                                  If the data is NOT ready or overwritten, a value of 0xFFFF would\n
 *                                                  be returned.
 */
uint16_t hal_adc_read_ch_dat (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t out_raw)
{
    hal_adc_cali_para_t adc_cali_paras_tmp;
    uint8_t cali_flag = phal_adc_adapter->use_cali;
    uint16_t adc_dat_tmp;

    if (phal_adc_adapter->init_dat.hw_mode == ADCAutoMod) {
        hal_adc_read_cali_param(LP_ADC_GAIN_DENO_ADDR, (uint8_t*)&adc_cali_paras_tmp.gain_deno, 2);
        hal_adc_read_cali_param(LP_ADC_GAIN_MOLE_ADDR, (uint8_t*)&adc_cali_paras_tmp.gain_mole, 2);
        hal_adc_read_cali_param(LP_ADC_OFFSET_DENO_ADDR, (uint8_t*)&adc_cali_paras_tmp.offset_deno, 4);
        hal_adc_read_cali_param(LP_ADC_OFFSET_MOLE_ADDR, (uint8_t*)&adc_cali_paras_tmp.offset_mole, 2);

        phal_adc_adapter->use_cali = ADCDisable;
        adc_dat_tmp = __rom_stubs_hal_adc.hal_adc_read_ch_dat(phal_adc_adapter, ch_no, out_raw);
        phal_adc_adapter->use_cali = cali_flag;
        if (phal_adc_adapter->use_cali != 0) {
            adc_dat_tmp = hal_adc_calc_cali_val((uint16_t)adc_dat_tmp, (hal_adc_cali_para_t *)&adc_cali_paras_tmp);
            return (uint16_t)(adc_dat_tmp & LP_ADC_DATA_MASK);
        } else {
            return (uint16_t)(adc_dat_tmp & LP_ADC_DATA_MASK);
        }
    } else {
        DBG_ADC_ERR("Incorrect Operation Mode\n");
        return 0xFFFF;
    }
    
}

/** \brief Description of hal_adc_read_continuous
 *
 *    hal_adc_read_continuous is used to read the channel data continuously according to cvlist and different
 *                                          trigger source.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter
 *   \param[in] uint32_t dat_len:                       ADC conversion data length.
 *   \param[in] uint16_t *dat_buf:                      ADC conversion data pointer.
 *   \param[in] uint8_t trigger_source:                 Inform ADC the trigger source.
 *                                                  0: software, 1: automatic, 2: timer, 3: comparator
 *   \return hal_status_t.
 */
hal_status_t hal_adc_read_continuous (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf,
                                                    uint8_t trigger_source)
{
    return __rom_stubs_hal_adc.hal_adc_read_continuous(phal_adc_adapter, dat_len, dat_buf, trigger_source);
}

/** \brief Description of hal_adc_dma_init
 *
 *    hal_adc_dma_init is to initialize DMA module for adc data collection.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter
 *   \param[in] hal_gdma_chnl_t *pgdma_chnl:            Pointer to GDMA channel control type.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_adc_dma_init (hal_adc_adapter_t *phal_adc_adapter, hal_gdma_adaptor_t *padc_gdma_adaptor)
{
    return __rom_stubs_hal_adc.hal_adc_dma_init(phal_adc_adapter, padc_gdma_adaptor);
}

/** \brief Description of hal_adc_dma_deinit
 *
 *    hal_adc_dma_deinit is to deinitialize DMA module.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adaptor
 *
 *   \return hal_status_t:
 */
hal_status_t hal_adc_dma_deinit (hal_adc_adapter_t *phal_adc_adapter)
{
    return __rom_stubs_hal_adc.hal_adc_dma_deinit(phal_adc_adapter);
}

/** \brief Description of hal_adc_read_dma
 *
 *    hal_adc_read_dma is used to read data contiuously by using DMA module.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter
 *   \param[in] uint32_t dat_len:                       ADC conversion data length.
 *   \param[in] uint16_t *dat_buf:                      ADC conversion data pointer.
 *   \param[in] uint8_t trigger_source:                 Inform ADC the trigger source.
 *                                                  1: automatic, 2: timer, 3: comparator,
 *                                                  software trigger is not available when using DMA because
 *                                                  software trigger would occupy CPU resource and application could
 *                                                  not get any performance improvement even using DMA.
 *
 *   \return hal_status_t.
 */
hal_status_t hal_adc_read_dma (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf,
                                                    uint8_t trigger_source)
{
    return __rom_stubs_hal_adc.hal_adc_read_dma(phal_adc_adapter, dat_len, dat_buf, trigger_source);
}

/** \brief Description of hal_adc_reg_irq
 *
 *    hal_adc_reg_irq is used to register a irq handler

 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \param[in] irq_handler_t handler:                IRQ handler function.
 *   \return void
 */
void hal_adc_reg_irq (hal_adc_adapter_t *phal_adc_adapter, irq_handler_t handler)
{
    __rom_stubs_hal_adc.hal_adc_reg_irq (phal_adc_adapter, handler);
}

/** \brief Description of hal_adc_gen_rand_dat32
 *
 *    hal_adc_gen_rand_dat32 is used to read adc channel data contiuously and get a random number.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter
 *   \param[in] uint8_t ch_no:  Channel number
 *   \return uint32_t
 */
uint32_t hal_adc_gen_rand_dat32 (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
        return hal_adc_gen_rand_dat32_rtl8195blp_patch(phal_adc_adapter, ch_no);
#else
        return __rom_stubs_hal_adc.hal_adc_gen_rand_dat32(phal_adc_adapter, ch_no);
#endif
}

/** \brief Description of hal_adc_cal_gain_deno
 *
 *    hal_adc_cal_gain_deno is used to calculate denominator part of adc gain.
 *
 *   \param[in] int16_t ideal code 0
 *   \param[in] int16_t ideal code 1
 *   \return int32_t
 */
int16_t hal_adc_calc_gain_deno (int16_t ideal_co_1, int16_t ideal_co_0)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    return (int16_t)(ideal_co_1 - ideal_co_0);
#else
    return __rom_stubs_hal_adc.hal_adc_calc_gain_deno(ideal_co_1, ideal_co_0);
#endif
}

/** \brief Description of hal_adc_cal_gain_mole
 *
 *    hal_adc_cal_gain_mole is used to calculate molecular part of adc gain.
 *
 *   \param[in] int16_t real code 0
 *   \param[in] int16_t real code 1
 *   \return int32_t
 */
int16_t hal_adc_calc_gain_mole(int16_t real_co_1, int16_t real_co_0)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    return (int16_t)(real_co_1 - real_co_0);
#else
    return __rom_stubs_hal_adc.hal_adc_calc_gain_mole(real_co_1, real_co_0);
#endif
}

/** \brief Description of hal_adc_cal_offet_deno
 *
 *    hal_adc_cal_offet_deno is used to calculate denominator part of adc offset.
 *
 *   \param[in] int16_t ideal code 0
 *   \param[in] int16_t ideal code 1
 *   \param[in] int16_t real code 0
 *   \param[in] int16_t real code 1
 *   \return int32_t
 */
int32_t hal_adc_calc_offset_deno(int16_t ideal_co_1, int16_t ideal_co_0, int16_t real_co_1, int16_t real_co_0)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    int32_t offset_deno;

    offset_deno = (ideal_co_0 * real_co_1) - (ideal_co_1 * real_co_0);

    return (int32_t)offset_deno;
#else
    return __rom_stubs_hal_adc.hal_adc_calc_offset_deno(ideal_co_1, ideal_co_0, real_co_1, real_co_0);
#endif
}

/** \brief Description of hal_adc_cal_offset_mole
 *
 *    hal_adc_cal_offset_mole is used to calculate molecular part of adc offset.
 *
 *   \param[in] int16_t real code 0
 *   \param[in] int16_t real code 1
 *   \return int32_t
 */
int16_t hal_adc_calc_offset_mole(int16_t real_co_1, int16_t real_co_0)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    return (int16_t)(real_co_1 - real_co_0);
#else
    return __rom_stubs_hal_adc.hal_adc_calc_offset_mole(real_co_1, real_co_0);
#endif
}

/** \brief Description of hal_adc_calc_cali_val
 *
 *    hal_adc_calc_cali_val is used to calculate calibration value
 *
 *   \param[in] uint16_t adc real value
 *   \param[in] hal_adc_cali_para_t *phal_adc_cali_para
 *   \return int32_t
 */
uint16_t hal_adc_calc_cali_val(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para) 
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    uint16_t ret_cali_val;
    int64_t read_val_scle = adc_read_val * LP_ADC_CALC_SCLE;
    int64_t gain_deno_scle = phal_adc_cali_para->gain_deno;
    int64_t gain_mole_scle = phal_adc_cali_para->gain_mole;
    int64_t offset_deno_scle = (phal_adc_cali_para->offset_deno) * LP_ADC_CALC_SCLE;
    int64_t offset_mole_scle = phal_adc_cali_para->offset_mole;

    if ((phal_adc_cali_para->gain_deno == 0xFFFF) || (phal_adc_cali_para->gain_mole == 0xFFFF) || 
        (phal_adc_cali_para->offset_deno == 0xFFFFFFFF) || (phal_adc_cali_para->offset_mole== 0xFFFF)) {
        DBG_ADC_ERR();
        return (uint16_t)adc_read_val;
    }
    
    DBG_ADC_INFO("read val scaled: %x\n", read_val_scle);
    DBG_ADC_INFO("offset deno scaled: %x\n", offset_deno_scle);
    read_val_scle = (read_val_scle * gain_deno_scle * offset_mole_scle);    
    offset_deno_scle = offset_deno_scle * offset_mole_scle;    
    read_val_scle = read_val_scle + offset_deno_scle;
    read_val_scle = read_val_scle / gain_mole_scle;
    read_val_scle = read_val_scle / offset_mole_scle;
    
    /* save read_val_scle to offset_deno_scle temporarily */
    offset_deno_scle = read_val_scle;
    read_val_scle = read_val_scle / LP_ADC_CALC_SCLE;
    if (offset_deno_scle < 0) {
        offset_deno_scle = offset_deno_scle * (-1);
    }
    
    if ((offset_deno_scle % LP_ADC_CALC_SCLE) > (LP_ADC_CALC_SCLE/2)) {
        DBG_ADC_WARN("final value is inreased/decresed by 1\n");
        if (read_val_scle > 0) {
            read_val_scle++;
        } else {
            read_val_scle--;
        }
    }
    
    ret_cali_val = (uint16_t)read_val_scle;

    if (read_val_scle < 0) {
        ret_cali_val = 0;
        DBG_ADC_WARN("cali value is less than 0.\n");
    } else if (read_val_scle > LP_ADC_CODE_MAX) {
        ret_cali_val = LP_ADC_CODE_MAX;
        DBG_ADC_WARN("cali value is greater than 1023.\n");
    }
    
    return (uint16_t)ret_cali_val;
#else
    return __rom_stubs_hal_adc.hal_adc_calc_cali_val(adc_read_val, phal_adc_cali_para);
#endif
}

/** \brief Description of hal_adc_calc_real_val
 *
 *    hal_adc_calc_cali_val is used to calculate real value
 *
 *   \param[in] uint16_t adc ideal value
 *   \param[in] hal_adc_cali_para_t *phal_adc_cali_para
 *   \return int16_t
 */
uint16_t hal_adc_calc_real_val(uint16_t adc_ideal_val, hal_adc_cali_para_t *phal_adc_cali_para) 
{
    uint16_t ret_real_val;
    int64_t ideal_val_scle =  (int64_t)(adc_ideal_val);
    int64_t gain_deno_scle = phal_adc_cali_para->gain_deno;
    int64_t gain_mole_scle = phal_adc_cali_para->gain_mole;
    int64_t offset_deno_scle = (phal_adc_cali_para->offset_deno);
    int64_t offset_mole_scle = phal_adc_cali_para->offset_mole;

    if ((phal_adc_cali_para->gain_deno == 0xFFFF) || (phal_adc_cali_para->gain_mole == 0xFFFF) || 
        (phal_adc_cali_para->offset_deno == 0xFFFFFFFF) || (phal_adc_cali_para->offset_mole== 0xFFFF)) {
        return (uint16_t)adc_ideal_val;
    }

    ideal_val_scle = ideal_val_scle * offset_mole_scle;
    ideal_val_scle = ideal_val_scle - offset_deno_scle;
    ideal_val_scle = (ideal_val_scle * gain_mole_scle);
    ideal_val_scle = ideal_val_scle/gain_deno_scle;
    ret_real_val = ideal_val_scle / offset_mole_scle;

    return ret_real_val;
}

/** \brief Description of hal_adc_read_cali_param
 *
 *    hal_adc_read_cali_param is used to read calibration parameters.
 *
 *   \param[in] uint16_t parameters address
 *   \param[in] uint8_t *return data address
 *   \param[in] uint8_t parameter length
 *   \return void
 */
void hal_adc_read_cali_param(uint16_t addr, uint8_t *param_addr, uint8_t param_len)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    uint8_t rd_cnt;

    for (rd_cnt = 0; rd_cnt < param_len; rd_cnt++) {
        hal_efuse_read(LP_ADC_FUSE_VAL, (addr+rd_cnt), (param_addr+rd_cnt), 7); 
        DBG_ADC_INFO("read param(%x): %x\n", (addr+rd_cnt), *(param_addr+rd_cnt));
    }
#else
    __rom_stubs_hal_adc.hal_adc_read_cali_param(addr, param_addr, param_len);
#endif
}

/** \brief Description of hal_adc_write_cali_param
 *
 *    hal_adc_write_cali_param is used to read calibration parameters.
 *
 *   \param[in] uint16_t parameters address
 *   \param[in] uint8_t *data address
 *   \param[in] uint8_t parameter length
 *   \return void
 */
void hal_adc_write_cali_param(uint16_t addr, uint8_t *param_addr, uint8_t param_len)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    uint8_t rd_cnt;

    for (rd_cnt = 0; rd_cnt < param_len; rd_cnt++) {
        hal_efuse_write(LP_ADC_FUSE_VAL, (addr+rd_cnt), *(param_addr+rd_cnt), 7); 
        DBG_ADC_INFO("write param(%x): %x\n", (addr+rd_cnt), *(param_addr+rd_cnt));
    }
#else
    __rom_stubs_hal_adc.hal_adc_write_cali_param(addr, param_addr, param_len);
#endif
}

/** @} */ /* End of group ls_hal_adc */

#endif  /* end of "#if CONFIG_ADC_EN" */

