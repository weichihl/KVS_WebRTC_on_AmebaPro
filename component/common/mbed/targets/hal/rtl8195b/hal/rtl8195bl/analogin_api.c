/** mbed Microcontroller Library
  ******************************************************************************
  * @file    analogin_api.c
  * @author
  * @version V1.0.0
  * @date    2017-08-01
  * @brief   This file provides mbed API for ADC.
  ******************************************************************************
  * @attention
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2017, Realtek Semiconductor Corporation. All rights reserved.
  ******************************************************************************
  */

#include "objects.h"
#include "PinNames.h"
#include "analogin_api.h"

#include "pinmap.h"
#include "analogin_ex_api.h"
#include "hal_adc.h"
#if (defined(CONFIG_ADC_EN) && (CONFIG_ADC_EN == 1))

extern void *memset(void * dst0, int Val, size_t length);
static uint8_t analogin_init_flag = 0;
static hal_adc_adapter_t analogin_con_adpt;
static hal_gdma_adaptor_t analogin_dma_adpt;
static VOID (*analogin_rxc_cb)(VOID *data);
static uint8_t analogin_ch_list[8] = {0, 1, 2, 3, 4, 5, 6, 7};


static const PinMap PinMap_analogin[] = {
    {PA_0,  RTL_PIN_PERI(PID_ADC0, 0, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {PA_1,  RTL_PIN_PERI(PID_ADC1, 1, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {PA_2,  RTL_PIN_PERI(PID_ADC2, 2, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {PA_3,  RTL_PIN_PERI(PID_ADC3, 3, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {PA_4,  RTL_PIN_PERI(PID_ADC4, 4, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {PA_5,  RTL_PIN_PERI(PID_ADC5, 5, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {PA_6,  RTL_PIN_PERI(PID_ADC6, 6, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {NC,    NC,     0}
};

/**
  * @brief  Analogin internal callbck
  * @param  obj: adc object define in application software.
  * @param  pin: adc PinName according to pinmux spec.
  * @retval none
  */
void analogin_callback_internal(void *data)
{
    hal_adc_set_pwr_cut(&analogin_con_adpt);
    if (analogin_rxc_cb != NULL) {
        analogin_rxc_cb(NULL);
    }
}

/**
  * @brief  Initializes the ADC device, include clock/function/ADC registers.
  * @param  obj: adc object define in application software.
  * @param  pin: adc PinName according to pinmux spec.
  * @retval none
  */
void analogin_init(analogin_t *obj, PinName pin)
{
    uint32_t analogin_peri = (uint32_t)pinmap_peripheral(pin, PinMap_analogin);
    obj->idx = RTL_GET_PERI_IDX(analogin_peri);
    
    if (!analogin_init_flag) {
        memset(&analogin_con_adpt, 0x00, sizeof(analogin_con_adpt));
        hal_adc_load_default(&analogin_con_adpt);
        analogin_con_adpt.init_dat.hw_mode = ADCAutoMod;
        analogin_con_adpt.init_dat.clock_div = ADCClockDiv64;

                
        /* set pin enable flag */
        analogin_con_adpt.plft_dat.pin_en.w |= ((uint32_t)1 << obj->idx);
        if (hal_adc_init(&analogin_con_adpt) != HAL_OK) {
            DBG_ADC_ERR("analogin initialization failed\n");
        } else {
            analogin_init_flag = 1;
            analogin_con_adpt.usr_cb.rxc.cb = analogin_callback_internal;
        }

        hal_adc_set_cvlist(&analogin_con_adpt, &analogin_ch_list[0], 8);
        hal_adc_auto_chsw_ctrl(&analogin_con_adpt, ADCEnable);
        hal_adc_enable(&analogin_con_adpt, ADCEnable);
    } else {
        /* module initialized but pin was NOT */
        if ((analogin_con_adpt.plft_dat.pin_en.w & ((uint32_t)1 << obj->idx)) == 0) {
            analogin_con_adpt.plft_dat.pin_en.w |= ((uint32_t)1 << obj->idx);
            hal_adc_pin_init(&analogin_con_adpt);
        }
    }
    hal_delay_us(200);
}

/**
  * @brief  Deinitializes the ADC device, include clock/function/ADC registers.
  * @param  obj: adc object define in application software.
  * @retval none
  */
void analogin_deinit(analogin_t *obj)
{
    if (analogin_init_flag) {
        analogin_con_adpt.plft_dat.pin_en.w &= (~((uint32_t)1 << obj->idx));
        /* all pin should be turn off therefore module should be turn off, too */
        if (analogin_con_adpt.plft_dat.pin_en.w == 0) {
            hal_adc_deinit(&analogin_con_adpt);
            analogin_init_flag = 0;
        } else {
            hal_adc_pin_deinit(&analogin_con_adpt);
        }
    } else {
        DBG_ADC_ERR("analogin module has been deinited.");
    }
}

/**
  * @brief  Reads data from the specified adc channel fifo.
  * @param  obj: adc object define in application software.
  * @retval : adc channel data(float)
  */
float analogin_read(analogin_t *obj)
{
    uint16_t anain16;
    uint16_t ana_full;
    float retv_ana;

    anain16 = hal_adc_single_read(&analogin_con_adpt, obj->idx);
    ana_full = 0x3FF;

    retv_ana = anain16/ana_full;

    return retv_ana;
}

/**
  * @brief  Reads data from the specified adc channel fifo.
  * @param  obj: adc object define in application software.
  * @retval : 16bit adc channel data(int)
  */
uint16_t analogin_read_u16(analogin_t *obj)
{
    uint16_t anain16;

    anain16 = hal_adc_single_read(&analogin_con_adpt, obj->idx);

    return anain16;
}

/**
  * @brief  Set user callback function
  * @param  obj: adc object define in application software.
  * @param  analogin_cb:  callback type
  * @param  analogin_callback:  callback function
  * @retval : none
  */
void analogin_set_user_callback(analogin_t *obj, AnalogInCallback analogin_cb, void(*analogin_callback)(void *))
{
    switch (analogin_cb) {
        case ANALOGIN_RX_DMA_COMPLETE:
            analogin_rxc_cb = analogin_callback;
            break;
        default:
            break;
    }
}

/**
  * @brief  Clear user callback function
  * @param  obj: adc object define in application software.
  * @param  analogin_cb:  callback type
  * @retval : none
  */
void analogin_clear_user_callback(analogin_t *obj, AnalogInCallback analogin_cb)
{
    switch (analogin_cb) {
        case ANALOGIN_RX_DMA_COMPLETE:
            analogin_con_adpt.usr_cb.rxc.cb = NULL;
            analogin_rxc_cb = NULL;
            break;
        default:
            break;
    }
}

/**
  * @brief  Analog input transfer by DMA
  * @param  obj: adc object define in application software.
  * @param  buf:  data buffer.
  * @param  length:  data length.
  * @retval : 0: success, 1: failed
  */
uint8_t analogin_read_u16_dma (analogin_t * obj, uint16_t *buf, uint16_t length)
{
    uint8_t ana_idx;

    ana_idx = obj->idx;
    hal_adc_set_cvlist (&analogin_con_adpt, &ana_idx, 1);
    hal_adc_dma_init(&analogin_con_adpt, &analogin_dma_adpt);
    if (hal_adc_read_dma(&analogin_con_adpt, length, buf, ADCAutoMod) != HAL_OK) {
        return 1;
    }

    return 0;
}

/**
  * @brief  Analog inpput set up wake criteria
  * @param  obj: adc object define in application software.
  * @param  thld: voltage threshold
  * @param  rule: greater than or less than, 1: greater than, 0: less than
  * @retval : 0: success, 1: failed
  */
uint8_t analogin_set_wake_rule (analogin_t * obj, uint16_t thld, uint8_t greater)
{
    uint8_t ana_idx;
    uint16_t adc_val;
    uint16_t adc_real_val;
    ADC_Type *padc_reg = (ADC_Type *)analogin_con_adpt.init_dat.reg_base;
    ana_idx = obj->idx;
    hal_adc_cali_para_t adc_cali_paras_tmp;

    hal_adc_read_cali_param(LP_ADC_GAIN_DENO_ADDR, (uint8_t*)&adc_cali_paras_tmp.gain_deno, 2);
    hal_adc_read_cali_param(LP_ADC_GAIN_MOLE_ADDR, (uint8_t*)&adc_cali_paras_tmp.gain_mole, 2);
    hal_adc_read_cali_param(LP_ADC_OFFSET_DENO_ADDR, (uint8_t*)&adc_cali_paras_tmp.offset_deno, 4);
    hal_adc_read_cali_param(LP_ADC_OFFSET_MOLE_ADDR, (uint8_t*)&adc_cali_paras_tmp.offset_mole, 2);
    adc_val = hal_adc_calc_real_val(thld, &adc_cali_paras_tmp);
    
    adc_real_val = hal_adc_calc_cali_val(adc_val, &adc_cali_paras_tmp);
    hal_adc_set_comp_thld(&analogin_con_adpt, ana_idx, adc_val, adc_val);
    hal_adc_set_comp_rule(&analogin_con_adpt, ana_idx, greater);
    analogin_con_adpt.init_dat.hw_mode = ADCAutoMod;
    padc_reg->conf_b.op_mod = ADCAutoMod;
    hal_adc_set_cvlist(&analogin_con_adpt, (uint8_t *)&ana_idx, 1);
    hal_adc_intr_ctrl(&analogin_con_adpt, (ADCIntrCompch0+ana_idx), ADCEnable);
    hal_adc_auto_chsw_ctrl(&analogin_con_adpt, ADCEnable);
    __ISB();
    __DSB();
    return 0;
}

#endif //end of #if (defined(CONFIG_ADC_EN) && (CONFIG_ADC_EN == 1))

