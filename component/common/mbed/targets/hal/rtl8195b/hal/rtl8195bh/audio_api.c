/**************************************************************************//**
 * @file     audio_api.c
 * @brief    This file implements the AUDIO Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-03
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 ******************************************************************************/
#include "objects.h"
#include "pinmap.h"
#include "audio_api.h"
#include "hal_audio.h"


void audio_init(audio_t *obj, audio_output_mode output_mode, audio_input_mode input_mode, audio_power_sel power_sel)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
    hal_gdma_adaptor_t *paudio_gdma_adp_tx = &obj->audio_gdma_adp_tx;
    hal_gdma_adaptor_t *paudio_gdma_adp_rx = &obj->audio_gdma_adp_rx;

    paudio_adapter->phal_gdma_adaptor_tx = paudio_gdma_adp_tx;
    paudio_adapter->phal_gdma_adaptor_rx = paudio_gdma_adp_rx;

    paudio_adapter->word_len = WL_16BIT;

    hal_audio_init(paudio_adapter, power_sel);

    hal_audio_output_power(paudio_adapter, output_mode);
    
    hal_audio_adc_l_hpf(paudio_adapter, DISABLE);
    hal_audio_adc_r_hpf(paudio_adapter, DISABLE);
    hal_audio_input_power(paudio_adapter, input_mode);    

    hal_audio_ch_num(paudio_adapter, AUDIO_CH_MONO);

    hal_delay_ms(200);
    hal_audio_adc_l_hpf(paudio_adapter, ENABLE);
    hal_audio_adc_r_hpf(paudio_adapter, ENABLE);

    hal_audio_adc_l_2nd_hpf(paudio_adapter, DISABLE, AUDIO_HPF_FS_8K_16K, 0x00);
    hal_audio_adc_r_2nd_hpf(paudio_adapter, DISABLE, AUDIO_HPF_FS_8K_16K, 0x00);
    hal_audio_adc_l_dvol(paudio_adapter, DVOL_ADC_0DB);
    hal_audio_adc_r_dvol(paudio_adapter, DVOL_ADC_0DB);
    hal_audio_adc_l_dmute(paudio_adapter, DISABLE);
    hal_audio_adc_r_dmute(paudio_adapter, DISABLE);

    hal_audio_dac_dither(paudio_adapter, AUDIO_DITHER_DISABLE, AUDIO_DITHER_DISABLE);
    hal_audio_dac_l_dvol(paudio_adapter, DVOL_DAC_0DB);
    hal_audio_dac_r_dvol(paudio_adapter, DVOL_DAC_0DB);
    hal_audio_dac_l_dmute(paudio_adapter, DISABLE);
    hal_audio_dac_r_dmute(paudio_adapter, DISABLE);
    hal_audio_dac_l_zdet(paudio_adapter, AUDIO_DETE_AND_INC_DEC_CHAN, AUDIO_DAC_16384_SAMPLES);
    hal_audio_dac_r_zdet(paudio_adapter, AUDIO_DETE_AND_INC_DEC_CHAN, AUDIO_DAC_16384_SAMPLES);
    hal_audio_alc_mixer(paudio_adapter, DISABLE, DISABLE);
    hal_audio_sidetone_mixer(paudio_adapter, ENABLE, ENABLE);

    hal_audio_digital_rst(paudio_adapter, DISABLE);

}

void audio_deinit(audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
    u32 temp_tx, temp_rx;

    temp_tx = hal_audio_get_sport_tx_start_status(paudio_adapter);
    temp_rx = hal_audio_get_sport_rx_start_status(paudio_adapter);

    if (temp_tx == 0x01) {
        hal_audio_sport_tx_start_ctrl(paudio_adapter, 0);
        hal_gdma_abort(paudio_adapter->phal_gdma_adaptor_tx);
        hal_gdma_chnl_free (paudio_adapter->phal_gdma_adaptor_tx);
    }

    if (temp_rx == 0x01) {
        hal_audio_sport_rx_start_ctrl(paudio_adapter, 0);
        hal_gdma_abort(paudio_adapter->phal_gdma_adaptor_rx);
        hal_gdma_chnl_free (paudio_adapter->phal_gdma_adaptor_rx);
    }
    
    hal_audio_sport_clean_error(paudio_adapter);
    hal_audio_output_power(paudio_adapter, AUDIO_OUTPUT_DISABLE);
    hal_audio_input_power(paudio_adapter, AUDIO_INPUT_DISABLE);
    hal_audio_digital_rst(paudio_adapter, ENABLE);
    hal_audio_deinit(paudio_adapter);
}

void audio_set_param(audio_t *obj, audio_sr sample_rate, audio_wl word_length)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    paudio_adapter->word_len = word_length;
    hal_audio_length(paudio_adapter, word_length);
    hal_audio_sport_length(paudio_adapter, word_length);

    if (word_length == WL_24BIT) {
        hal_audio_sport_tx_data_swap(paudio_adapter, 0, 1);
        hal_audio_sport_rx_data_swap(paudio_adapter, 0, 1);
    } else {
        hal_audio_sport_tx_data_swap(paudio_adapter, 0, 0);
        hal_audio_sport_rx_data_swap(paudio_adapter, 0, 0);
    }

    hal_audio_rate(paudio_adapter, sample_rate);
    hal_audio_sport_rate(paudio_adapter, sample_rate);
}

void audio_set_tx_dma_buffer(audio_t *obj, u8 *tx_buf, u32 tx_page_size)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    paudio_adapter->tx_page_index = 0;
    paudio_adapter->tx_page0_adr = (u32)tx_buf;
    paudio_adapter->tx_page1_adr = (u32)tx_buf + tx_page_size;
    paudio_adapter->tx_page_size = tx_page_size;

    if (((tx_page_size & 0x3F) != 0x00) || (tx_page_size > 4032)) {
        DBG_AUDIO_ERR(" 'tx_page_size' needs to be a multiple of 64, and the maximum value is 4032. \r\n");
    }    

    DBG_AUDIO_INFO("tx_buf: 0x%8x \r\n", tx_buf);
    DBG_AUDIO_INFO("tx_page0_adr: 0x%8x \r\n", paudio_adapter->tx_page0_adr);
    DBG_AUDIO_INFO("tx_page1_adr: 0x%8x \r\n", paudio_adapter->tx_page1_adr);

    //hal_audio_tx_dma_init(paudio_adapter, paudio_adapter->word_len, paudio_adapter->tx_page_size, paudio_adapter->tx_page0_adr);
}

void audio_set_rx_dma_buffer(audio_t *obj, u8 *rx_buf, u32 rx_page_size)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    paudio_adapter->rx_page_index = 0;
    paudio_adapter->rx_page0_adr = (u32)rx_buf;
    paudio_adapter->rx_page1_adr = (u32)rx_buf + rx_page_size;
    paudio_adapter->rx_page_size = rx_page_size;

    if (((rx_page_size & 0x3F) != 0x00) || (rx_page_size > 4032)) {
        DBG_AUDIO_ERR(" 'rx_page_size' needs to be a multiple of 64, and the maximum value is 4032. \r\n");
    }  

    DBG_AUDIO_INFO("rx_buf: 0x%8x \r\n", rx_buf);
    DBG_AUDIO_INFO("rx_page0_adr: 0x%8x \r\n", paudio_adapter->rx_page0_adr);
    DBG_AUDIO_INFO("rx_page1_adr: 0x%8x \r\n", paudio_adapter->rx_page1_adr);

    //hal_audio_rx_dma_init(paudio_adapter, paudio_adapter->word_len, paudio_adapter->rx_page_size, paudio_adapter->rx_page0_adr);
}

void audio_tx_irq_handler(audio_t *obj, audio_irq_handler tx_handler, u32 arg)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    paudio_adapter->audio_user_cb.audio_tx_cb = tx_handler;
    paudio_adapter->audio_user_cb.audio_tx_arg = arg;
}

void audio_rx_irq_handler(audio_t *obj, audio_irq_handler rx_handler, u32 arg)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    paudio_adapter->audio_user_cb.audio_rx_cb = rx_handler;
    paudio_adapter->audio_user_cb.audio_rx_arg = arg;
}

u8 *audio_get_tx_page_adr(audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
    u8 *ptxdata_wk;

    ptxdata_wk = paudio_adapter->ptxdata_wk;

    if (ptxdata_wk == NULL) {
        DBG_AUDIO_ERR(" Not update TX address \r\n");
    }

    return ptxdata_wk;
}

void audio_set_tx_page(audio_t *obj, u8 *pbuf)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    paudio_adapter->dcache_clean_by_addr ((uint32_t *)pbuf, (int32_t)paudio_adapter->tx_page_size);

    paudio_adapter->tx_data_empty = 0;
}

void audio_set_rx_page(audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    paudio_adapter->rx_data_ready = 0;
}

void audio_tx_start (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    paudio_adapter->tx_page_index = 0;
    paudio_adapter->ptxdata_wk = NULL;

    if (paudio_adapter->dcache_clean_by_addr != NULL) {
        paudio_adapter->dcache_clean_by_addr ((uint32_t *)paudio_adapter->tx_page0_adr, (int32_t)paudio_adapter->tx_page_size);
        paudio_adapter->dcache_clean_by_addr ((uint32_t *)paudio_adapter->tx_page1_adr, (int32_t)paudio_adapter->tx_page_size);
    } else {
        DBG_AUDIO_ERR(" paudio_adapter->dcache_clean_by_addr is null \r\n");
    }

    hal_audio_tx_dma_init(paudio_adapter, paudio_adapter->word_len, paudio_adapter->tx_page_size, paudio_adapter->tx_page0_adr);
    hal_audio_sport_rst(paudio_adapter);
    hal_audio_tx_dma_start(paudio_adapter);
    hal_audio_sport_clean_error(paudio_adapter);
    paudio_adapter->tx_data_empty = 0;
    hal_audio_sport_tx_start_ctrl(paudio_adapter, 1);
}

void audio_rx_start (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_rx_dma_init(paudio_adapter, paudio_adapter->word_len, paudio_adapter->rx_page_size, paudio_adapter->rx_page0_adr);
    hal_audio_sport_rst(paudio_adapter);
    hal_audio_rx_dma_start(paudio_adapter);
    hal_audio_sport_clean_error(paudio_adapter);
    paudio_adapter->rx_page_index = 0;
    hal_audio_sport_rx_start_ctrl(paudio_adapter, 1);
}

void audio_trx_start (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    if (paudio_adapter->dcache_clean_by_addr != NULL) {
        paudio_adapter->dcache_clean_by_addr ((uint32_t *)paudio_adapter->tx_page0_adr, (int32_t)paudio_adapter->tx_page_size);
        paudio_adapter->dcache_clean_by_addr ((uint32_t *)paudio_adapter->tx_page1_adr, (int32_t)paudio_adapter->tx_page_size);
    } else {
        DBG_AUDIO_ERR(" paudio_adapter->dcache_clean_by_addr is null \r\n");
    }

    hal_audio_rx_dma_init(paudio_adapter, paudio_adapter->word_len, paudio_adapter->rx_page_size, paudio_adapter->rx_page0_adr);
    hal_audio_tx_dma_init(paudio_adapter, paudio_adapter->word_len, paudio_adapter->tx_page_size, paudio_adapter->tx_page0_adr);

    hal_audio_sport_rst(paudio_adapter);
    hal_audio_rx_dma_start(paudio_adapter);
    hal_audio_tx_dma_start(paudio_adapter);
    hal_audio_sport_clean_error(paudio_adapter);
    paudio_adapter->tx_data_empty = 0;
    paudio_adapter->rx_page_index = 0;
    hal_audio_sport_trx_start_ctrl(paudio_adapter, 1);
}

void audio_tx_stop (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_sport_tx_start_ctrl(paudio_adapter, 0);
    hal_gdma_abort(paudio_adapter->phal_gdma_adaptor_tx);
    //Free TX GDMA Channel
    hal_gdma_chnl_free (paudio_adapter->phal_gdma_adaptor_tx);
}

void audio_rx_stop (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_sport_rx_start_ctrl(paudio_adapter, 0);
    hal_gdma_abort(paudio_adapter->phal_gdma_adaptor_rx);
    //Free RX GDMA Channel
    hal_gdma_chnl_free (paudio_adapter->phal_gdma_adaptor_rx);
}

void audio_trx_stop (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_sport_trx_start_ctrl(paudio_adapter, 0);

    hal_gdma_abort(paudio_adapter->phal_gdma_adaptor_tx);
    hal_gdma_abort(paudio_adapter->phal_gdma_adaptor_rx);

    //Free TX GDMA Channel
    hal_gdma_chnl_free (paudio_adapter->phal_gdma_adaptor_tx);
    //Free RX GDMA Channel
    hal_gdma_chnl_free (paudio_adapter->phal_gdma_adaptor_rx);

    hal_audio_sport_clean_error(paudio_adapter);
}

u8 audio_get_tx_error_cnt (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    return paudio_adapter->tx_err_cnt;
}

u8 audio_get_rx_error_cnt (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    return paudio_adapter->rx_err_cnt;
}

void audio_clean_error_cnt (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_sport_clean_error(paudio_adapter);
}

void audio_sport_loopback (audio_t *obj, BOOL en)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_sport_loopback(paudio_adapter, en);
}

void audio_mic_analog_mute (audio_t *obj, BOOL en)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_mic_mute(paudio_adapter, en, en);
}

void audio_line_in_analog_mute (audio_t *obj, BOOL en)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_line_in_mute(paudio_adapter, en, en);
}

void audio_mic_analog_gain (audio_t *obj, BOOL en, audio_mic_gain mic_gain)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_mic_boost(paudio_adapter, en, mic_gain, en, mic_gain);
}

void audio_hpo_amplifier (audio_t *obj, BOOL en)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_hpo_amplifier(paudio_adapter, en, en);
}

void audio_adc_digital_vol (audio_t *obj, u8 step)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    if (step > 0x7F) {
        DBG_AUDIO_ERR(" The adc step exceeds the maximum value 0x7F. \r\n");
    } else {
        hal_audio_adc_l_dvol(paudio_adapter, step);
        hal_audio_adc_r_dvol(paudio_adapter, step);
    }
}

void audio_adc_digital_mute (audio_t *obj, BOOL mute_en)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_adc_l_dmute(paudio_adapter, mute_en);
    hal_audio_adc_r_dmute(paudio_adapter, mute_en);
}

void audio_headphone_analog_mute (audio_t *obj, BOOL en)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_hpo_mute(paudio_adapter, en, en);
}

void audio_dac_digital_vol (audio_t *obj, u8 step)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    if (step > DVOL_DAC_0DB) {
        DBG_AUDIO_ERR(" The dac step exceeds the maximum value 0xAF. \r\n");
    } else {
        hal_audio_dac_l_dvol(paudio_adapter, step);
        hal_audio_dac_r_dvol(paudio_adapter, step);
    }
}

void audio_dac_digital_mute (audio_t *obj, BOOL mute_en)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_dac_l_dmute(paudio_adapter, mute_en);
    hal_audio_dac_r_dmute(paudio_adapter, mute_en);
}

void audio_vref_voltage_ctrl (audio_t *obj, audio_vref_voltage voltage)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_vref(paudio_adapter, ENABLE, voltage);
}

void audio_sidetone_init (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_sidetone_mixer(paudio_adapter, DISABLE, DISABLE);
    hal_audio_sidetone_source(paudio_adapter, AUDIO_ST_ADC_L);
    hal_audio_sidetone_clk(paudio_adapter, ENABLE);
}

void audio_sidetone_deinit (audio_t *obj)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_sidetone_mixer(paudio_adapter, ENABLE, ENABLE);
    hal_audio_sidetone_clk(paudio_adapter, DISABLE);
}

void audio_sidetone_vol (audio_t *obj, audio_sidetone_boost_t sidetone_boost, u8 step)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    if (step > SIDETONE_0DB) {
        DBG_AUDIO_ERR(" The sidetone step exceeds the maximum value 0x1F. \r\n");
    } else {
        hal_audio_sidetone_vol(paudio_adapter, step, sidetone_boost);
    }
}

void audio_sidetone_hpf_ctrl (audio_t *obj, BOOL en, audio_sidetone_hpf sidetone_hpf)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_sidetone_hpf(paudio_adapter, en, sidetone_hpf);
}

void audio_wind_filter (audio_t *obj, BOOL en, audio_sr sample_rate, u8 coef_num)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;
    u8 audio_hpf_coef;

    if ((sample_rate == ASR_8KHZ) || (sample_rate == ASR_16KHZ)) {
        audio_hpf_coef = AUDIO_HPF_FS_8K_16K;
    } else if (sample_rate == ASR_32KHZ) {
        audio_hpf_coef = AUDIO_HPF_FS_32K;
    } else if ((sample_rate == ASR_44p1KHZ) || (sample_rate == ASR_48KHZ)) {
        audio_hpf_coef = AUDIO_HPF_FS_48K_44p1K;
    } else if ((sample_rate == ASR_88p2KHZ) || (sample_rate == ASR_96KHZ)) {
        audio_hpf_coef = AUDIO_HPF_FS_96K_88p2K;
    }

    if (coef_num > 0x3f) {
        DBG_AUDIO_ERR(" The coef_num exceeds the maximum value 0x3F. \r\n");
    } else {
        hal_audio_adc_l_2nd_hpf(paudio_adapter, en, audio_hpf_coef, coef_num);
        hal_audio_adc_r_2nd_hpf(paudio_adapter, en, audio_hpf_coef, coef_num);
    }
}

void audio_mic_bias_ctrl (audio_t *obj, BOOL en, audio_bias_voltage voltage)
{
    hal_audio_adapter_t *paudio_adapter = &obj->audio_adapter;

    hal_audio_mic_bias(paudio_adapter, en, voltage);
}

