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
#include "platform_stdlib.h"

#if (defined(CONFIG_ADC_EN) && (CONFIG_ADC_EN == 1))

extern void *memset(void * dst0, int Val, size_t length);
static uint8_t analogin_init_flag = 0;
static hal_adc_adapter_t analogin_con_adpt;
static hal_gdma_adaptor_t analogin_dma_adpt;

static const PinMap PinMap_analogin[] = {
    {PH_0,  RTL_PIN_PERI(PID_ADC0, 4, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {PH_1,  RTL_PIN_PERI(PID_ADC1, 5, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {PH_2,  RTL_PIN_PERI(PID_ADC2, 6, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {PH_3,  RTL_PIN_PERI(PID_ADC3, 7, 0), RTL_PIN_FUNC(PID_ADC0, 0)},
    {NC,    NC,     0}
};

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
        analogin_con_adpt.init_dat.use_dly = 1;
        analogin_con_adpt.init_dat.trig_dly = 100;
        analogin_con_adpt.use_cali = 0;
        /* set pin enable flag */
        analogin_con_adpt.plft_dat.pin_en.w |= ((uint32_t)1 << obj->idx);
        if (hal_adc_init(&analogin_con_adpt) != HAL_OK) {
            printf("analogin initialization failed\n");
        } else {
            analogin_init_flag = 1;
            hal_delay_ms(20);
            hal_adc_set_in_tape_all((hal_adc_adapter_t *)&analogin_con_adpt, HP_ADC_INPUT_ALL_SINGLE);
            hal_adc_set_cvlist((hal_adc_adapter_t *)&analogin_con_adpt, (uint8_t *)&analogin_init_flag, 1);
        }
    } else {
        /* module initialized but pin was NOT */
        if ((analogin_con_adpt.plft_dat.pin_en.w & ((uint32_t)1 << obj->idx)) == 0) {
            analogin_con_adpt.plft_dat.pin_en.w |= ((uint32_t)1 << obj->idx);
            hal_adc_pin_init(&analogin_con_adpt);
        }
        
    }
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
        printf("analogin module has been deinited.");
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
            analogin_con_adpt.usr_cb.rxc.cb = analogin_callback;
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

#endif //end of #if (defined(CONFIG_ADC_EN) && (CONFIG_ADC_EN == 1))

