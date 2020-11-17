/**************************************************************************//**
 * @file     hal_audio.c
 * @brief    This Audio CODEC HAL API functions.
 *
 * @version  V1.00
 * @date     2016-09-19
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

#include "hal_cache.h"
#include "hal_pinmux.h"
#include "hal_audio.h"
#include "hal_gdma.h"
#include "hal.h"

#if CONFIG_AUDIO_EN

extern void hal_syson_audio_porb_ctrl(BOOL en);
extern void hal_syson_audio_dev_ctrl(BOOL en);
extern void hal_syson_audio_ldo_ctrl(BOOL en);
extern void hal_syson_audio_ldo_tune(u8 sel);


/**
 * @addtogroup hs_hal_audio AUDIO
 * @{
 */

/**
 *  @brief Initialize the AUDIO hardware and turn on the AUDIO.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_codec_power Select audio codec LDO power. 0: 1.8V, 1: 2.8V.
 *
 *  @returns void
 */
void hal_audio_init (hal_audio_adapter_t *paudio_adapter, audio_codec_power_t audio_codec_power)
{
    sport_ctrl_3_t sport_ctrl_3;
    sport_ctrl_2_t sport_ctrl_2;
    sport_ctrl_1_t sport_ctrl_1;
    //audio_codec_index_00h_t audio_codec_index_00h;
    audio_codec_index_02h_t audio_codec_index_02h;
    //audio_codec_index_03h_t audio_codec_index_03h;

    paudio_adapter->si_base_addr = (SI_Type *)SI;
    paudio_adapter->sport0_base_addr = (SPORT0_Type *)SPORT0;

    paudio_adapter->tx_data_empty = 0;
    paudio_adapter->rx_data_ready = 0;

    paudio_adapter->dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;
    paudio_adapter->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;

    //Init SI & SPORT clock
    hal_syson_audio_dev_ctrl(ENABLE);

    //Init Audio Porb
    hal_syson_audio_porb_ctrl(ENABLE);

    //Init SI (Serial Interface)
    hal_audio_si_init(paudio_adapter, ENABLE);

    //Init Sport rate
    hal_audio_sport_rate(paudio_adapter, AUDIO_SR_32KHZ);

    //Init Sport ctrl_3
    sport_ctrl_3.w = paudio_adapter->sport0_base_addr->ctrl_3;
    sport_ctrl_3.b.tx_fifo_depth_half_sel = 0;
    sport_ctrl_3.b.rx_fifo_depth_half_sel = 0;
    paudio_adapter->sport0_base_addr->ctrl_3 = sport_ctrl_3.w;

    //Init Sport ctrl_2
    sport_ctrl_2.w = paudio_adapter->sport0_base_addr->ctrl_2;
    sport_ctrl_2.b.mode_40mhz = 1;
    sport_ctrl_2.b.tx_src_lr_swap = DISABLE;
    sport_ctrl_2.b.tx_src_byte_swap = DISABLE;
    sport_ctrl_2.b.rx_snk_lr_swap = DISABLE;
    sport_ctrl_2.b.rx_snk_byte_swap = DISABLE;
    paudio_adapter->sport0_base_addr->ctrl_2 = sport_ctrl_2.w;

    //Init Sport ctrl_1
    sport_ctrl_1.w = paudio_adapter->sport0_base_addr->ctrl_1;
    sport_ctrl_1.b.sp_wclk_inverse = SPORT_LEFT_PHASE;
    sport_ctrl_1.b.sp_data_format_sel = AUDIO_FORMAT_I2S;
    sport_ctrl_1.b.sp_en_i2s_mono = AUDIO_CH_MONO;
    sport_ctrl_1.b.sp_data_len_sel = AUDIO_WL_16;
    sport_ctrl_1.b.sp_inv_i2s_sclk = DISABLE;
    sport_ctrl_1.b.sp_sel_i2s_tx_ch = AUDIO_L_R;
    sport_ctrl_1.b.sp_sel_i2s_rx_ch = AUDIO_L_R;
    sport_ctrl_1.b.tx_lsb_first = DISABLE;
    sport_ctrl_1.b.rx_lsb_first = DISABLE;
    sport_ctrl_1.b.sp_adc_comp = 0;
    sport_ctrl_1.b.sp_dac_comp = 0;
    sport_ctrl_1.b.long_frame_sync = DISABLE;
    sport_ctrl_1.b.sp_loopback = DISABLE; //ENABLE
    sport_ctrl_1.b.sp_i2s_self_lpbk_en = DISABLE;
    paudio_adapter->sport0_base_addr->ctrl_1 = sport_ctrl_1.w;

    //MBIAS POW
    audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);
    audio_codec_index_02h.b.mbias_pow = 1;
    hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);

    //MBIAS Count
    //hal_audio_micbias_count(paudio_adapter, ENABLE);

    //LDO POW
    hal_delay_us(2);
    hal_syson_audio_ldo_tune(audio_codec_power);
    hal_syson_audio_ldo_ctrl(ENABLE);
    
#if 0

    //VREF POW
    hal_delay_us(22);
    audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);
    audio_codec_index_02h.b.vref_pow = 1;
    hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);

    audio_codec_index_03h.w = hal_audio_si_read(paudio_adapter, 0x03);
    audio_codec_index_03h.b.vref_vrefsel = 2;
    hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);

    //BB_CKX2
    hal_delay_us(1);
    audio_codec_index_00h.w = hal_audio_si_read(paudio_adapter, 0x00);
    audio_codec_index_00h.b.dac_ckxen = 1;
    hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);

    //DAC_ADDACK_POW
    hal_delay_us(5);
    audio_codec_index_00h.w = hal_audio_si_read(paudio_adapter, 0x00);
    audio_codec_index_00h.b.dac_addack_pow = 1;
    hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
#endif

}

/**
 *  @brief De-initialize of the AUDIO hardware and turn off the AUDIO.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_audio_deinit (hal_audio_adapter_t *paudio_adapter)
{
    sport_ctrl_2_t sport_ctrl_2;

    sport_ctrl_2.w = paudio_adapter->sport0_base_addr->ctrl_2;
    sport_ctrl_2.b.mode_40mhz = 0;
    paudio_adapter->sport0_base_addr->ctrl_2 = sport_ctrl_2.w;

    //Deinit LDO POW
    hal_syson_audio_ldo_ctrl(DISABLE);

    //Deinit SI (Serial Interface)
    hal_audio_si_init(paudio_adapter, DISABLE);

    //Deinit Audio Porb
    hal_syson_audio_porb_ctrl(DISABLE);

    //Deinit Audio
    hal_syson_audio_dev_ctrl(DISABLE);
}

/**
 *  @brief Control the communication interface of the audio codec for reading or writing the register.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_si_init (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    paudio_adapter->si_base_addr->clk_ctrl_b.reg_dk_en = en;
}

/**
 *  @brief Read the register of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] address  The register address.
 *
 *  @returns The register value.
 */
u16 hal_audio_si_read (hal_audio_adapter_t *paudio_adapter, u8 address)
{
    si_ctrl_t si_ctrl;

    if (paudio_adapter->si_base_addr->ctrl_b.si_read_start == 1) {
        DBG_AUDIO_WARN("hal_audio_si_read: before still in reading \r\n");
    }

    si_ctrl.w = paudio_adapter->si_base_addr->ctrl;
    si_ctrl.b.si_address = address;
    si_ctrl.b.si_read_start = 1;
    paudio_adapter->si_base_addr->ctrl = si_ctrl.w;

    while(1) {
        if (paudio_adapter->si_base_addr->ctrl_b.si_read_start == 0) {
            break;
        }
    }

    return (paudio_adapter->si_base_addr->ctrl_b.si_data);
}

/**
 *  @brief Write the register of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] address  The register address.
 *  @param[in] data  The register value to be written.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_audio_si_write (hal_audio_adapter_t *paudio_adapter, u8 address, u16 data)
{
    si_ctrl_t si_ctrl;
    u16 si_read_data;

    if (paudio_adapter->si_base_addr->ctrl_b.si_wr_start == 1) {
        DBG_AUDIO_WARN("hal_audio_si_write: before still in writing \r\n");
        return HAL_BUSY;
    }

    si_ctrl.w = paudio_adapter->si_base_addr->ctrl;
    si_ctrl.b.si_address = address;
    si_ctrl.b.si_data = data;
    si_ctrl.b.si_wr_start = 1;
    paudio_adapter->si_base_addr->ctrl = si_ctrl.w;

    while(1) {
        if (paudio_adapter->si_base_addr->ctrl_b.si_wr_start == 0) {
            break;
        }
    }

#if 1
    si_read_data = hal_audio_si_read(paudio_adapter, address);
    DBG_AUDIO_INFO("0x%2x: 0x%4x \r\n", address, si_read_data);
#endif

    return HAL_OK;
}

/**
 *  @brief Set the sport rate to communicate the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_sample_rate  Sample rate.
 *
 *  @returns void
 */
void hal_audio_sport_rate (hal_audio_adapter_t *paudio_adapter, audio_sample_rate_t audio_sample_rate)
{
    sport_gen_bclk_t sport_gen_bclk;

    sport_gen_bclk.w = paudio_adapter->sport0_base_addr->gen_bclk;

    switch (audio_sample_rate) {

        case AUDIO_SR_8KHZ:
            sport_gen_bclk.b.mi = 625;
            sport_gen_bclk.b.ni = 8;
            break;

        case AUDIO_SR_16KHZ:
            sport_gen_bclk.b.mi = 625;
            sport_gen_bclk.b.ni = 16;
            break;

        case AUDIO_SR_32KHZ:
            sport_gen_bclk.b.mi = 625;
            sport_gen_bclk.b.ni = 32;
            break;

        case AUDIO_SR_44p1KHZ:
            sport_gen_bclk.b.mi = 411;
            sport_gen_bclk.b.ni = 29;
            break;

        case AUDIO_SR_48KHZ:
            sport_gen_bclk.b.mi = 625;
            sport_gen_bclk.b.ni = 48;
            break;

        case AUDIO_SR_88p2KHZ:
            sport_gen_bclk.b.mi = 411;
            sport_gen_bclk.b.ni = 58;
            break;

        case AUDIO_SR_96KHZ:
            sport_gen_bclk.b.mi = 625;
            sport_gen_bclk.b.ni = 96;
            break;

        default :

            break;

    }

    sport_gen_bclk.b.mi_ni_update = 1;
    paudio_adapter->sport0_base_addr->gen_bclk = sport_gen_bclk.w;

}

/**
 *  @brief Control the swap of tx audio data.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lr_swap_en  Swap the left and right channel data.
 *  @param[in] byte_swap_en  Swap the byte data.
 *
 *  @returns void
 */
void hal_audio_sport_tx_data_swap (hal_audio_adapter_t *paudio_adapter, BOOL lr_swap_en, BOOL byte_swap_en)
{
    sport_ctrl_2_t sport_ctrl_2;

    sport_ctrl_2.w = paudio_adapter->sport0_base_addr->ctrl_2;
    sport_ctrl_2.b.tx_src_lr_swap = lr_swap_en;
    sport_ctrl_2.b.tx_src_byte_swap = byte_swap_en;
    paudio_adapter->sport0_base_addr->ctrl_2 = sport_ctrl_2.w;
}

/**
 *  @brief Control the swap of rx audio data.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lr_swap_en  Swap the left and right channel data.
 *  @param[in] byte_swap_en  Swap the byte data.
 *
 *  @returns void
 */
void hal_audio_sport_rx_data_swap (hal_audio_adapter_t *paudio_adapter, BOOL lr_swap_en, BOOL byte_swap_en)
{
    sport_ctrl_2_t sport_ctrl_2;

    sport_ctrl_2.w = paudio_adapter->sport0_base_addr->ctrl_2;
    sport_ctrl_2.b.rx_snk_lr_swap = lr_swap_en;
    sport_ctrl_2.b.rx_snk_byte_swap = byte_swap_en;
    paudio_adapter->sport0_base_addr->ctrl_2 = sport_ctrl_2.w;
}

/**
 *  @brief Start the tx audio data.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_sport_tx_start_ctrl (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    sport_ctrl_1_t sport_ctrl_1;
    u8 ctrl_1, ctrl_2;

    if (en == 0) {
        ctrl_1 = 1;
        ctrl_2 = 0;
    } else {
        ctrl_1 = 0;
        ctrl_2 = 1;
    }

    sport_ctrl_1.w = paudio_adapter->sport0_base_addr->ctrl_1;
    sport_ctrl_1.b.sp_tx_disable = ctrl_1;
    sport_ctrl_1.b.sp_start_tx = ctrl_2;
    paudio_adapter->sport0_base_addr->ctrl_1 = sport_ctrl_1.w;
}

/**
 *  @brief Get tx start status.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  TX stop.
 *  @return     1:  TX start.
 */
u32 hal_audio_get_sport_tx_start_status (hal_audio_adapter_t *paudio_adapter)
{
    sport_ctrl_1_t sport_ctrl_1;
    u32 temp;

    sport_ctrl_1.w = paudio_adapter->sport0_base_addr->ctrl_1;

    if ((sport_ctrl_1.b.sp_tx_disable == 0x00) && (sport_ctrl_1.b.sp_start_tx == 0x01)) {
        temp = 1;
    } else {
        temp = 0;
    }

    return temp;
}


/**
 *  @brief Start the rx audio data.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_sport_rx_start_ctrl (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    sport_ctrl_1_t sport_ctrl_1;
    u8 ctrl_1, ctrl_2;

    if (en == 0) {
        ctrl_1 = 1;
        ctrl_2 = 0;
    } else {
        ctrl_1 = 0;
        ctrl_2 = 1;
    }

    sport_ctrl_1.w = paudio_adapter->sport0_base_addr->ctrl_1;
    sport_ctrl_1.b.sp_rx_disable = ctrl_1;
    sport_ctrl_1.b.sp_start_rx = ctrl_2;
    paudio_adapter->sport0_base_addr->ctrl_1 = sport_ctrl_1.w;
}

/**
 *  @brief Get rx start status.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  RX stop.
 *  @return     1:  RX start.
 */
u32 hal_audio_get_sport_rx_start_status (hal_audio_adapter_t *paudio_adapter)
{
    sport_ctrl_1_t sport_ctrl_1;
    u32 temp;

    sport_ctrl_1.w = paudio_adapter->sport0_base_addr->ctrl_1;

    if ((sport_ctrl_1.b.sp_rx_disable == 0x00) && (sport_ctrl_1.b.sp_start_rx == 0x01)) {
        temp = 1;
    } else {
        temp = 0;
    }

    return temp;
}

/**
 *  @brief Start the tx and rx audio data.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_sport_trx_start_ctrl (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    sport_ctrl_1_t sport_ctrl_1;
    u8 ctrl_1, ctrl_2;

    if (en == 0) {
        ctrl_1 = 1;
        ctrl_2 = 0;
    } else {
        ctrl_1 = 0;
        ctrl_2 = 1;
    }

    sport_ctrl_1.w = paudio_adapter->sport0_base_addr->ctrl_1;
    sport_ctrl_1.b.sp_tx_disable = ctrl_1;
    sport_ctrl_1.b.sp_start_tx = ctrl_2;
    sport_ctrl_1.b.sp_rx_disable = ctrl_1;
    sport_ctrl_1.b.sp_start_rx = ctrl_2;
    paudio_adapter->sport0_base_addr->ctrl_1 = sport_ctrl_1.w;
}

/**
 *  @brief Clean the error status.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_audio_sport_clean_error (hal_audio_adapter_t *paudio_adapter)
{
    sport_ctrl_2_t sport_ctrl_2;

    sport_ctrl_2.w = paudio_adapter->sport0_base_addr->ctrl_2;
    sport_ctrl_2.b.clear_tx_err_cnt = 1;
    sport_ctrl_2.b.clear_rx_err_cnt = 1;
    paudio_adapter->sport0_base_addr->ctrl_2 = sport_ctrl_2.w;

    sport_ctrl_2.w = paudio_adapter->sport0_base_addr->ctrl_2;
    sport_ctrl_2.b.clear_tx_err_cnt = 0;
    sport_ctrl_2.b.clear_rx_err_cnt = 0;
    paudio_adapter->sport0_base_addr->ctrl_2 = sport_ctrl_2.w;
}

/**
 *  @brief Reset sport module include resetting FIFO and state machine.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_audio_sport_rst (hal_audio_adapter_t *paudio_adapter)
{
    sport_ctrl_1_t sport_ctrl_1;

    sport_ctrl_1.w = paudio_adapter->sport0_base_addr->ctrl_1;
    sport_ctrl_1.b.sp_reset = 1;
    paudio_adapter->sport0_base_addr->ctrl_1 = sport_ctrl_1.w;
    sport_ctrl_1.b.sp_reset = 0;
    paudio_adapter->sport0_base_addr->ctrl_1 = sport_ctrl_1.w;
}

//Audio Codec Digital Part

/**
 *  @brief Set the sample rate of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_sample_rate  Sample rate.
 *
 *  @returns void
 */
void hal_audio_rate (hal_audio_adapter_t *paudio_adapter, audio_sample_rate_t audio_sample_rate)
{
    audio_codec_index_17h_t audio_codec_index_17h;
    audio_codec_index_1bh_t audio_codec_index_1bh;

    audio_codec_index_17h.w = hal_audio_si_read(paudio_adapter, 0x17);
    audio_codec_index_1bh.w = hal_audio_si_read(paudio_adapter, 0x1B);

    audio_codec_index_17h.b.dac_sample_rate = audio_sample_rate;
    audio_codec_index_17h.b.adc_sample_rate = audio_sample_rate;

    if (audio_codec_index_1bh.b.asrc_en == 0) {
        audio_codec_index_17h.b.asrc_fsi_rate_manual = audio_sample_rate;
        audio_codec_index_1bh.b.asrc_256fs_sys_sel = 0;
    } else {
        if ((audio_sample_rate == AUDIO_SR_88p2KHZ) || (audio_sample_rate == AUDIO_SR_96KHZ)) {
            audio_codec_index_17h.b.asrc_fsi_rate_manual = 1;
            audio_codec_index_1bh.b.asrc_256fs_sys_sel = 0;
        } else {
            audio_codec_index_17h.b.asrc_fsi_rate_manual = 0;
            audio_codec_index_1bh.b.asrc_256fs_sys_sel = 1;
        }
    }

    hal_audio_si_write(paudio_adapter, 0x17, audio_codec_index_17h.w);
    hal_audio_si_write(paudio_adapter, 0x1B, audio_codec_index_1bh.w);
}

/**
 *  @brief Set the format of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_format  Select the interface format.
 *
 *  @returns void
 */
void hal_audio_format (hal_audio_adapter_t *paudio_adapter, audio_format_t audio_format)
{
    audio_codec_index_10h_t audio_codec_index_10h;

    audio_codec_index_10h.w = hal_audio_si_read(paudio_adapter, 0x10);
    audio_codec_index_10h.b.i2s_data_format_sel = audio_format;
    hal_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h.w);
}

/**
 *  @brief Set the channel bumber of the audio codec.
 *         Only support MONO.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_ch_num  Select the channel number.
 *
 *  @returns void
 */
void hal_audio_ch_num (hal_audio_adapter_t *paudio_adapter, audio_ch_num_t audio_ch_num)
{
    audio_codec_index_10h_t audio_codec_index_10h;

    audio_codec_index_10h.w = hal_audio_si_read(paudio_adapter, 0x10);
    audio_codec_index_10h.b.en_i2s_mono = audio_ch_num;
    hal_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h.w);
}

/**
 *  @brief Set the data length of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_word_len  The data length.
 *
 *  @returns void
 */
void hal_audio_length (hal_audio_adapter_t *paudio_adapter, audio_word_len_t audio_word_len)
{
    audio_codec_index_10h_t audio_codec_index_10h;

    audio_codec_index_10h.w = hal_audio_si_read(paudio_adapter, 0x10);
    audio_codec_index_10h.b.i2s_data_len_sel = audio_word_len;
    hal_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h.w);
}

/**
 *  @brief Invert the SCK of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sck_inv_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_sck_inv (hal_audio_adapter_t *paudio_adapter, BOOL sck_inv_en)
{
    audio_codec_index_10h_t audio_codec_index_10h;

    audio_codec_index_10h.w = hal_audio_si_read(paudio_adapter, 0x10);
    audio_codec_index_10h.b.inv_i2s_sclk = sck_inv_en;
    hal_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h.w);
}

/**
 *  @brief Control the interface loopback mode of the audio codec. This direction is tx to rx.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sck_inv_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_loopback (hal_audio_adapter_t *paudio_adapter, BOOL loopback_en)
{
    audio_codec_index_10h_t audio_codec_index_10h;

    audio_codec_index_10h.w = hal_audio_si_read(paudio_adapter, 0x10);
    audio_codec_index_10h.b.stereo_i2s_self_lpbk_en = loopback_en;
    hal_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h.w);
}

/**
 *  @brief Control the tx data format of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_sel_ch  Set the relation between the data and channel.
 *                      -00: L/R.
 *                      -01: R/L.
 *                      -10: L/L.
 *                      -11: R/R.
 *
 *  @returns void
 */
void hal_audio_tx_ch (hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch)
{
    audio_codec_index_10h_t audio_codec_index_10h;

    audio_codec_index_10h.w = hal_audio_si_read(paudio_adapter, 0x10);
    audio_codec_index_10h.b.sel_i2s_tx_ch = audio_sel_ch;
    hal_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h.w);
}

/**
 *  @brief Control the rx data format of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_sel_ch  Set the relation between the data and channel.
 *                      -00: L/R.
 *                      -01: R/L.
 *                      -10: L/L.
 *                      -11: R/R.
 *
 *  @returns void
 */
void hal_audio_rx_ch (hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch)
{
    audio_codec_index_10h_t audio_codec_index_10h;

    audio_codec_index_10h.w = hal_audio_si_read(paudio_adapter, 0x10);
    audio_codec_index_10h.b.sel_i2s_rx_ch = audio_sel_ch;
    hal_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h.w);
}

/**
 *  @brief Reset the the digital IP of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_digital_rst (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    audio_codec_index_10h_t audio_codec_index_10h;
    u8 rst_dis_en = 0;

    if (en == 0) {
        rst_dis_en = 1;
    }

    audio_codec_index_10h.w = hal_audio_si_read(paudio_adapter, 0x10);
    audio_codec_index_10h.b.i2s_rst_n_reg = rst_dis_en;
    hal_audio_si_write(paudio_adapter, 0x10, audio_codec_index_10h.w);
}

/**
 *  @brief Control the DAC & ADC loopback. This direction is tx to rx.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] loopback_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_daad_loopback (hal_audio_adapter_t *paudio_adapter, BOOL loopback_en)
{
    audio_codec_index_fbh_t audio_codec_index_fbh;

    audio_codec_index_fbh.w = hal_audio_si_read(paudio_adapter, 0xfb);
    audio_codec_index_fbh.b.daad_lpbk_en = loopback_en;
    hal_audio_si_write(paudio_adapter, 0xfb, audio_codec_index_fbh.w);
}

/**
 *  @brief Control the clock source of the sample rate.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] gen_clk_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_gen_clk (hal_audio_adapter_t *paudio_adapter, BOOL gen_clk_en)
{
    audio_codec_index_1ah_t audio_codec_index_1ah;

    audio_codec_index_1ah.w = hal_audio_si_read(paudio_adapter, 0x1A);

    if (gen_clk_en == 1) {
        audio_codec_index_1ah.b.gen_src_16k128_en = 1;
        audio_codec_index_1ah.b.gen_src_32k128_en = 1;
        audio_codec_index_1ah.b.gen_src_44p1k128_en = 1;
        audio_codec_index_1ah.b.gen_src_48k128_en = 1;
        audio_codec_index_1ah.b.gen_src_8k128_en = 1;
    } else {
        audio_codec_index_1ah.b.gen_src_16k128_en = 0;
        audio_codec_index_1ah.b.gen_src_32k128_en = 0;
        audio_codec_index_1ah.b.gen_src_44p1k128_en = 0;
        audio_codec_index_1ah.b.gen_src_48k128_en = 0;
        audio_codec_index_1ah.b.gen_src_8k128_en = 0;
    }

    hal_audio_si_write(paudio_adapter, 0x1A, audio_codec_index_1ah.w);
}

/**
 *  @brief Control the ASRC of the audio codec.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] asrc_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_asrc (hal_audio_adapter_t *paudio_adapter, BOOL asrc_en)
{
    audio_codec_index_17h_t audio_codec_index_17h;
    audio_codec_index_1ah_t audio_codec_index_1ah;
    audio_codec_index_1bh_t audio_codec_index_1bh;
    u8 sample_rate_flag = 0;

    audio_codec_index_17h.w = hal_audio_si_read(paudio_adapter, 0x17);
    audio_codec_index_1ah.w = hal_audio_si_read(paudio_adapter, 0x1A);
    audio_codec_index_1bh.w = hal_audio_si_read(paudio_adapter, 0x1B);

    audio_codec_index_1bh.b.asrc_en = asrc_en;

    if ((audio_codec_index_17h.b.dac_sample_rate == AUDIO_SR_88p2KHZ) || (audio_codec_index_17h.b.dac_sample_rate == AUDIO_SR_96KHZ)) {
        sample_rate_flag = 1;
    }

    if ((audio_codec_index_17h.b.adc_sample_rate == AUDIO_SR_88p2KHZ) || (audio_codec_index_17h.b.adc_sample_rate == AUDIO_SR_96KHZ)) {
        sample_rate_flag = 1;
    }

    if (audio_codec_index_1bh.b.asrc_en == 1) {
        audio_codec_index_17h.b.asrc_fsi_gating_en = 0;
        audio_codec_index_1ah.b.asrc_ftk_loop_gain_sel = 1;
        audio_codec_index_1bh.b.asrc_ftk_loop_en = 1;
        if (sample_rate_flag == 1) {
            audio_codec_index_17h.b.asrc_fsi_rate_manual = 1;
            audio_codec_index_1bh.b.asrc_256fs_sys_sel = 0;
        } else {
            audio_codec_index_17h.b.asrc_fsi_rate_manual = 0;
            audio_codec_index_1bh.b.asrc_256fs_sys_sel = 1;
        }
    } else {
        audio_codec_index_1bh.b.asrc_256fs_sys_sel = 0;
    }

    hal_audio_si_write(paudio_adapter, 0x17, audio_codec_index_17h.w);
    hal_audio_si_write(paudio_adapter, 0x1A, audio_codec_index_1ah.w);
    hal_audio_si_write(paudio_adapter, 0x1B, audio_codec_index_1bh.w);
}

/**
 *  @brief Control the mute mixer of DAC.
 *         Only support the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dac_l_mute_en  Mute control: 0 is disable, 1 is enable.
 *  @param[in] dac_r_mute_en  Mute control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dac_mixer (hal_audio_adapter_t *paudio_adapter, BOOL dac_l_mute_en, BOOL dac_r_mute_en)
{
    audio_codec_index_fbh_t audio_codec_index_fbh;
    audio_codec_index_fdh_t audio_codec_index_fdh;

    audio_codec_index_fbh.w = hal_audio_si_read(paudio_adapter, 0xfb);
    audio_codec_index_fdh.w = hal_audio_si_read(paudio_adapter, 0xfd);

    audio_codec_index_fbh.b.dac_l_dmix_mute_128fs_da = dac_l_mute_en;
    audio_codec_index_fdh.b.dac_r_dmix_mute_128fs_da = dac_r_mute_en;

    hal_audio_si_write(paudio_adapter, 0xfb, audio_codec_index_fbh.w);
    hal_audio_si_write(paudio_adapter, 0xfd, audio_codec_index_fdh.w);
}

/**
 *  @brief Control the mute mixer of amic.
 *         Only support the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] amic_l_mute_en  Mute control: 0 is disable, 1 is enable.
 *  @param[in] amic_r_mute_en  Mute control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adc_amic_mixer (hal_audio_adapter_t *paudio_adapter, BOOL amic_l_mute_en, BOOL amic_r_mute_en)
{
    audio_codec_index_11h_t audio_codec_index_11h;
    audio_codec_index_14h_t audio_codec_index_14h;

    audio_codec_index_11h.w = hal_audio_si_read(paudio_adapter, 0x11);
    audio_codec_index_14h.w = hal_audio_si_read(paudio_adapter, 0x14);

    audio_codec_index_11h.b.adc_l_ad_mix_mute = amic_l_mute_en;
    audio_codec_index_14h.b.adc_r_ad_mix_mute = amic_r_mute_en;

    hal_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h.w);
    hal_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h.w);
}

/**
 *  @brief Control the mute mixer of dmic.
 *         Only support the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_l_mute_en  Mute control: 0 is disable, 1 is enable.
 *  @param[in] dmic_r_mute_en  Mute control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adc_dmic_mixer (hal_audio_adapter_t *paudio_adapter, BOOL dmic_l_mute_en, BOOL dmic_r_mute_en)
{
    audio_codec_index_11h_t audio_codec_index_11h;
    audio_codec_index_14h_t audio_codec_index_14h;

    audio_codec_index_11h.w = hal_audio_si_read(paudio_adapter, 0x11);
    audio_codec_index_14h.w = hal_audio_si_read(paudio_adapter, 0x14);

    audio_codec_index_11h.b.adc_l_dmic_mix_mute = dmic_l_mute_en;
    audio_codec_index_14h.b.adc_r_dmic_mix_mute = dmic_r_mute_en;

    hal_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h.w);
    hal_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h.w);
}

/**
 *  @brief Control the ALC mixer of DAC.
 *         Only support the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] alc_l_mixer_en  Select the ALC or normal data in the left channel.
 *  @param[in] alc_r_mixer_en  Select the ALC or normal data in the right channel.
 *
 *  @returns void
 */
void hal_audio_alc_mixer (hal_audio_adapter_t *paudio_adapter, BOOL alc_l_mixer_en, BOOL alc_r_mixer_en)
{
    audio_codec_index_fah_t audio_codec_index_fah;
    audio_codec_index_fch_t audio_codec_index_fch;
    u8 temp;

    audio_codec_index_fah.w = hal_audio_si_read(paudio_adapter, 0xfa);
    audio_codec_index_fch.w = hal_audio_si_read(paudio_adapter, 0xfc);

    if (alc_l_mixer_en == 1) {
        temp = 0x00;
    } else {
        temp = 0x01;
    }
    audio_codec_index_fah.b.dac_l_dmix_in_sel = temp;

    if (alc_r_mixer_en == 1) {
        temp = 0x00;
    } else {
        temp = 0x01;
    }
    audio_codec_index_fch.b.dac_r_dmix_in_sel = temp;

    hal_audio_si_write(paudio_adapter, 0xfa, audio_codec_index_fah.w);
    hal_audio_si_write(paudio_adapter, 0xfc, audio_codec_index_fch.w);
}

/**
 *  @brief Control the sidetone mixer.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sidetone_l_mute_en  Mute control: 0 is disable, 1 is enable.
 *  @param[in] sidetone_r_mute_en  Mute control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_sidetone_mixer (hal_audio_adapter_t *paudio_adapter, BOOL sidetone_l_mute_en, BOOL sidetone_r_mute_en)
{
    audio_codec_index_fbh_t audio_codec_index_fbh;
    audio_codec_index_fdh_t audio_codec_index_fdh;

    audio_codec_index_fbh.w = hal_audio_si_read(paudio_adapter, 0x0fb);
    audio_codec_index_fdh.w = hal_audio_si_read(paudio_adapter, 0x0fd);

    audio_codec_index_fbh.b.dac_l_dmix_mute_128fs_sidetone = sidetone_l_mute_en;
    audio_codec_index_fdh.b.dac_r_dmix_mute_128fs_sidetone = sidetone_r_mute_en;

    hal_audio_si_write(paudio_adapter, 0x0fb, audio_codec_index_fbh.w);
    hal_audio_si_write(paudio_adapter, 0x0fd, audio_codec_index_fdh.w);
}

/**
 *  @brief Control the DAC clock.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dac_l_clk_en  Control the left channel clock: 0 is disable, 1 is enable.
 *  @param[in] dac_r_clk_en  Control the right channel clock: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dac_clk (hal_audio_adapter_t *paudio_adapter, BOOL dac_l_clk_en, BOOL dac_r_clk_en)
{
    audio_codec_index_18h_t audio_codec_index_18h;

    audio_codec_index_18h.w = hal_audio_si_read(paudio_adapter, 0x18);

    audio_codec_index_18h.b.da_l_en = dac_l_clk_en;
    audio_codec_index_18h.b.mod_l_en = dac_l_clk_en;
    audio_codec_index_18h.b.da_r_en = dac_r_clk_en;
    audio_codec_index_18h.b.mod_r_en = dac_r_clk_en;

    if ((dac_l_clk_en == 1) || (dac_r_clk_en == 1)) {
        audio_codec_index_18h.b.da_ana_clk_en = 1;
        audio_codec_index_18h.b.da_fifo_en = 1;
    } else {
        audio_codec_index_18h.b.da_ana_clk_en = 0;
        audio_codec_index_18h.b.da_fifo_en = 0;
    }

    hal_audio_si_write(paudio_adapter, 0x18, audio_codec_index_18h.w);
}

/**
 *  @brief Control the ADC clock.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] adc_l_clk_en  Control the left channel clock: 0 is disable, 1 is enable.
 *  @param[in] adc_r_clk_en  Control the right channel clock: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adc_clk (hal_audio_adapter_t *paudio_adapter, BOOL adc_l_clk_en, BOOL adc_r_clk_en)
{
    audio_codec_index_18h_t audio_codec_index_18h;

    audio_codec_index_18h.w = hal_audio_si_read(paudio_adapter, 0x18);

    audio_codec_index_18h.b.ad_l_en = adc_l_clk_en;
    audio_codec_index_18h.b.ad_ana_l_en = adc_l_clk_en;
    audio_codec_index_18h.b.ad_r_en = adc_r_clk_en;
    audio_codec_index_18h.b.ad_ana_r_en = adc_r_clk_en;

    if ((adc_l_clk_en == 1) || (adc_r_clk_en == 1)) {
        audio_codec_index_18h.b.ad_fifo_en = 1;
        audio_codec_index_18h.b.ad_ana_clk_en = 1;
    } else {
        audio_codec_index_18h.b.ad_fifo_en = 0;
        audio_codec_index_18h.b.ad_ana_clk_en = 0;
    }

    hal_audio_si_write(paudio_adapter, 0x18, audio_codec_index_18h.w);
}

/**
 *  @brief Control the D-MIC clock.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dimc_l_clk_en  Control the left channel clock: 0 is disable, 1 is enable.
 *  @param[in] dimc_r_clk_en  Control the right channel clock: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dmic_clk (hal_audio_adapter_t *paudio_adapter, BOOL dimc_l_clk_en, BOOL dimc_r_clk_en)
{
    audio_codec_index_18h_t audio_codec_index_18h;

    audio_codec_index_18h.w = hal_audio_si_read(paudio_adapter, 0x18);

    audio_codec_index_18h.b.ad_l_en = dimc_l_clk_en;
    audio_codec_index_18h.b.dmic_l_en = dimc_l_clk_en;
    audio_codec_index_18h.b.ad_r_en = dimc_r_clk_en;
    audio_codec_index_18h.b.dmic_r_en = dimc_r_clk_en;

    if ((dimc_l_clk_en == 1) || (dimc_r_clk_en == 1)) {
        audio_codec_index_18h.b.ad_fifo_en = 1;
        audio_codec_index_18h.b.dmic_clk_en = 1;
    } else {
        audio_codec_index_18h.b.ad_fifo_en = 0;
        audio_codec_index_18h.b.dmic_clk_en = 0;
    }

    hal_audio_si_write(paudio_adapter, 0x18, audio_codec_index_18h.w);
}

/**
 *  @brief Control the sidetone clock.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sidetone_clk_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_sidetone_clk (hal_audio_adapter_t *paudio_adapter, BOOL sidetone_clk_en)
{
    audio_codec_index_18h_t audio_codec_index_18h;

    audio_codec_index_18h.w = hal_audio_si_read(paudio_adapter, 0x18);
    audio_codec_index_18h.b.st_en = sidetone_clk_en;
    hal_audio_si_write(paudio_adapter, 0x18, audio_codec_index_18h.w);
}

/**
 *  @brief Select the input clock of D-MIC.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_input_clk  The D-MIC clock.
 *                      -0: 5MHz.
 *                      -1: 2.5MHz.
 *                      -2: 1.25MHz.
 *                      -3: 625KHz.
 *                      -4: 312.5KHz.
 *
 *  @returns void
 */
void hal_audio_dmic_input_clk (hal_audio_adapter_t *paudio_adapter, audio_dmic_input_clk_t dmic_input_clk)
{
    audio_codec_index_17h_t audio_codec_index_17h;

    audio_codec_index_17h.w = hal_audio_si_read(paudio_adapter, 0x17);
    audio_codec_index_17h.b.dmic_clk_sel = dmic_input_clk;
    hal_audio_si_write(paudio_adapter, 0x17, audio_codec_index_17h.w);
}

/**
 *  @brief Control the D-MIC latch.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_l_latch  Control the D-MIC latch of the left channel.
 *  @param[in] dmic_r_latch  Control the D-MIC latch of the right channel.
 *
 *  @returns void
 */
void hal_audio_dmic_latch (hal_audio_adapter_t *paudio_adapter, audio_dmic_latch_t dmic_l_latch, audio_dmic_latch_t dmic_r_latch)
{
    audio_codec_index_11h_t audio_codec_index_11h;
    audio_codec_index_14h_t audio_codec_index_14h;

    audio_codec_index_11h.w = hal_audio_si_read(paudio_adapter, 0x11);
    audio_codec_index_14h.w = hal_audio_si_read(paudio_adapter, 0x14);

    audio_codec_index_11h.b.adc_l_dmic_ri_fa_sel = dmic_l_latch;
    audio_codec_index_14h.b.adc_r_dmic_ri_fa_sel = dmic_r_latch;

    hal_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h.w);
    hal_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h.w);
}

/**
 *  @brief Control the D-MIC gain of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_boost  Set the D-MIC boost.
 *
 *  @returns void
 */
void hal_audio_dmic_l_gain (hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain)
{
    audio_codec_index_12h_t audio_codec_index_12h;

    audio_codec_index_12h.w = hal_audio_si_read(paudio_adapter, 0x12);
    audio_codec_index_12h.b.adc_l_dmic_boost_gain = dmic_gain;
    hal_audio_si_write(paudio_adapter, 0x12, audio_codec_index_12h.w);
}

/**
 *  @brief Control the D-MIC gain of the right channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dmic_boost  Set the D-MIC boost.
 *
 *  @returns void
 */
void hal_audio_dmic_r_gain (hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain)
{
    audio_codec_index_15h_t audio_codec_index_15h;

    audio_codec_index_15h.w = hal_audio_si_read(paudio_adapter, 0x15);
    audio_codec_index_15h.b.adc_r_dmic_boost_gain = dmic_gain;
    hal_audio_si_write(paudio_adapter, 0x15, audio_codec_index_15h.w);
}

/**
 *  @brief Control the D-MIC SRC filter of the left channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lp_1st_en  Control the 1nd LPF: 0 is disable, 1 is enable.
 *  @param[in] lp_2st_en  Control the 2nd LPF: 0 is disable, 1 is enable.
 *  @param[in] src_freq  Set the 1st LPF fc.
 *
 *  @returns void
 */
void hal_audio_dmic_l_src (hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
    audio_codec_index_11h_t audio_codec_index_11h;

    audio_codec_index_11h.w = hal_audio_si_read(paudio_adapter, 0x11);

    audio_codec_index_11h.b.adc_l_dmic_lpf1st_en = lp_1st_en;
    audio_codec_index_11h.b.adc_l_dmic_lpf2nd_en = lp_2st_en;
    audio_codec_index_11h.b.adc_l_dmic_lpf1st_fc_sel = src_freq;

    hal_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h.w);
}

/**
 *  @brief Control the D-MIC SRC filter of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lp_1st_en  Control the 1nd LPF: 0 is disable, 1 is enable.
 *  @param[in] lp_2st_en  Control the 2nd LPF: 0 is disable, 1 is enable.
 *  @param[in] src_freq  Set the 1st LPF fc.
 *
 *  @returns void
 */
void hal_audio_dmic_r_src (hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
    audio_codec_index_14h_t audio_codec_index_14h;

    audio_codec_index_14h.w = hal_audio_si_read(paudio_adapter, 0x14);

    audio_codec_index_14h.b.adc_r_dmic_lpf1st_en = lp_1st_en;
    audio_codec_index_14h.b.adc_r_dmic_lpf2nd_en = lp_2st_en;
    audio_codec_index_14h.b.adc_r_dmic_lpf1st_fc_sel = src_freq;

    hal_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h.w);
}

/**
 *  @brief Control the A-MIC ADC gain of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] amic_gain  Control the boost gain.
 *
 *  @returns void
 */
void hal_audio_amic_l_gain (hal_audio_adapter_t *paudio_adapter, audio_amic_gain_t amic_gain)
{
    audio_codec_index_12h_t audio_codec_index_12h;

    audio_codec_index_12h.w = hal_audio_si_read(paudio_adapter, 0x12);
    audio_codec_index_12h.b.adc_l_ad_comp_gain = amic_gain;
    hal_audio_si_write(paudio_adapter, 0x12, audio_codec_index_12h.w);
}

/**
 *  @brief Control the A-MIC ADC gain of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] amic_gain  Control the boost gain.
 *
 *  @returns void
 */
void hal_audio_amic_r_gain (hal_audio_adapter_t *paudio_adapter, audio_amic_gain_t amic_gain)
{
    audio_codec_index_15h_t audio_codec_index_15h;

    audio_codec_index_15h.w = hal_audio_si_read(paudio_adapter, 0x15);
    audio_codec_index_15h.b.adc_r_ad_comp_gain = amic_gain;
    hal_audio_si_write(paudio_adapter, 0x15, audio_codec_index_15h.w);
}

/**
 *  @brief Control the A-MIC SRC filter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lp_1st_en  Control the 1nd LPF: 0 is disable, 1 is enable.
 *  @param[in] lp_2st_en  Control the 2nd LPF: 0 is disable, 1 is enable.
 *  @param[in] src_freq  Set the 1st LPF fc.
 *
 *  @returns void
 */
void hal_audio_amic_l_src (hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
    audio_codec_index_11h_t audio_codec_index_11h;

    audio_codec_index_11h.w = hal_audio_si_read(paudio_adapter, 0x11);

    audio_codec_index_11h.b.adc_l_ad_lpf1st_en = lp_1st_en;
    audio_codec_index_11h.b.adc_l_ad_lpf2nd_en = lp_2st_en;
    audio_codec_index_11h.b.adc_l_ad_lpf1st_fc_sel = src_freq;

    hal_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h.w);
}

/**
 *  @brief Control the A-MIC SRC filter of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lp_1st_en  Control the 1nd LPF: 0 is disable, 1 is enable.
 *  @param[in] lp_2st_en  Control the 2nd LPF: 0 is disable, 1 is enable.
 *  @param[in] src_freq  Set the 1st LPF fc.
 *
 *  @returns void
 */
void hal_audio_amic_r_src (hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq)
{
    audio_codec_index_14h_t audio_codec_index_14h;

    audio_codec_index_14h.w = hal_audio_si_read(paudio_adapter, 0x14);

    audio_codec_index_14h.b.adc_r_ad_lpf1st_en = lp_1st_en;
    audio_codec_index_14h.b.adc_r_ad_lpf2nd_en = lp_2st_en;
    audio_codec_index_14h.b.adc_r_ad_lpf1st_fc_sel = src_freq;

    hal_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h.w);
}

/**
 *  @brief Control the ADC high pass filter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Control the HPF: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adc_l_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    audio_codec_index_11h_t audio_codec_index_11h;

    audio_codec_index_11h.w = hal_audio_si_read(paudio_adapter, 0x11);
    audio_codec_index_11h.b.adc_l_ad_dchpf_en = en;
    hal_audio_si_write(paudio_adapter, 0x11, audio_codec_index_11h.w);
}

/**
 *  @brief Control the ADC high pass filter of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Control the HPF: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adc_r_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    audio_codec_index_14h_t audio_codec_index_14h;

    audio_codec_index_14h.w = hal_audio_si_read(paudio_adapter, 0x14);
    audio_codec_index_14h.b.adc_r_ad_dchpf_en = en;
    hal_audio_si_write(paudio_adapter, 0x14, audio_codec_index_14h.w);
}


/**
 *  @brief Set the cut-off frequency of the ADC wind filter according to the sample rate and the coefficient.
 *         For the formula of Fc calculation is also shown as: Fc = (Fs * tan-1(a/(2-a))) / pi, FS: sample rate.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] audio_hpf_coef  Select the sample rate.
 *                      -0:  The sample rate is 8k or 16k. a = 2 ^(-6) (1 + n).
 *                      -1:  The sample rate is 32k. a = 2 ^(-7) (1 + n).
 *                      -2:  The sample rate is 48k or 44.1k. a = 2 ^(-8) (1 + n).
 *                      -3:  The sample rate is 96k or 88.2k. a = 2 ^(-9) (1 + n).
 *  @param[in] coef_num  Set the wind filter coefficient " n ".
 *                      -0:  @fs = 8k, or 16k      corresponding     fc = (20~2000Hz), or (40~4000Hz)
 *                      -0:  @fs = 32k               corresponding     fc = (40~3278Hz)
 *                      -0:  @fs = 48k or 44.1k   corresponding     fc = (30~2168Hz) or (28~1992Hz)
 *                      -0:  @fs = 96k or 88.2k   corresponding     fc = (30~2034Hz) or (28~1869Hz)
 *
 *  @returns void
 */
void hal_audio_adc_l_2nd_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_coef_t audio_hpf_coef, u8 coef_num)
{
    audio_codec_index_12h_t audio_codec_index_12h;
    audio_codec_index_13h_t audio_codec_index_13h;

    audio_codec_index_12h.w = hal_audio_si_read(paudio_adapter, 0x12);
    audio_codec_index_13h.w = hal_audio_si_read(paudio_adapter, 0x13);

    audio_codec_index_12h.b.adc_l_adj_hpf_coef_sel= audio_hpf_coef;
    audio_codec_index_13h.b.adc_l_adj_hpf_coef_num = coef_num;
    audio_codec_index_12h.b.adc_l_adj_hpf_2nd_en = en;

    hal_audio_si_write(paudio_adapter, 0x12, audio_codec_index_12h.w);
    hal_audio_si_write(paudio_adapter, 0x13, audio_codec_index_13h.w);
}

/**
 *  @brief Set the cut-off frequency of the ADC wind filter according to the sample rate and the coefficient.
 *         For the formula of Fc calculation is also shown as: Fc = (Fs * tan-1(a/(2-a))) / pi, FS: sample rate, a: the coefficient.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] audio_hpf_coef  Select the sample rate.
 *                      -0:  The sample rate is 8k or 16k.
 *                      -1:  The sample rate is 32k.
 *                      -2:  The sample rate is 48k or 44.1k.
 *                      -3:  The sample rate is 96k or 88.2k.
 *  @param[in] coef_num  Set the wind filter coefficient.
 *                      -0:  @fs = 8k, or 16k      corresponding     fc = (20~2000Hz), or (40~4000Hz)
 *                      -0:  @fs = 32k               corresponding     fc = (40~3278Hz)
 *                      -0:  @fs = 48k or 44.1k   corresponding     fc = (30~2168Hz) or (28~1992Hz)
 *                      -0:  @fs = 96k or 88.2k   corresponding     fc = (30~2034Hz) or (28~1869Hz)
 *
 *  @returns void
 */
void hal_audio_adc_r_2nd_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_coef_t audio_hpf_coef, u8 coef_num)
{
    audio_codec_index_15h_t audio_codec_index_15h;
    audio_codec_index_16h_t audio_codec_index_16h;

    audio_codec_index_15h.w = hal_audio_si_read(paudio_adapter, 0x15);
    audio_codec_index_16h.w = hal_audio_si_read(paudio_adapter, 0x16);

    audio_codec_index_15h.b.adc_r_adj_hpf_coef_sel= audio_hpf_coef;
    audio_codec_index_16h.b.adc_r_adj_hpf_coef_num = coef_num;
    audio_codec_index_15h.b.adc_r_adj_hpf_2nd_en = en;

    hal_audio_si_write(paudio_adapter, 0x15, audio_codec_index_15h.w);
    hal_audio_si_write(paudio_adapter, 0x16, audio_codec_index_16h.w);
}

/**
 *  @brief Control the ADC digital volume of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] step  The digital volume. Every Step is 0.375dB.
 *         The value 0x7F is 30dB.
 *         The value 0x2F is 0dB.
 *         The value 0x00 is -17.625dB.
 *
 *  @returns void
 */
void hal_audio_adc_l_dvol (hal_audio_adapter_t *paudio_adapter, u8 step)
{
    audio_codec_index_13h_t audio_codec_index_13h;

    audio_codec_index_13h.w = hal_audio_si_read(paudio_adapter, 0x13);
    audio_codec_index_13h.b.adc_l_ad_gain = step;

    hal_audio_si_write(paudio_adapter, 0x13, audio_codec_index_13h.w);
}

/**
 *  @brief Control the ADC digital mute of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] mute_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adc_l_dmute (hal_audio_adapter_t *paudio_adapter, BOOL mute_en)
{
    audio_codec_index_12h_t audio_codec_index_12h;

    audio_codec_index_12h.w = hal_audio_si_read(paudio_adapter, 0x12);
    audio_codec_index_12h.b.adc_l_ad_mute = mute_en;

    hal_audio_si_write(paudio_adapter, 0x12, audio_codec_index_12h.w);
}

/**
 *  @brief Control the ADC digital volume of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] step  The digital volume. Every Step is 0.375dB.
 *         The value 0x7F is 30dB.
 *         The value 0x2F is 0dB.
 *         The value 0x00 is -17.625dB.
 *
 *  @returns void
 */
void hal_audio_adc_r_dvol (hal_audio_adapter_t *paudio_adapter, u8 step)
{
    audio_codec_index_16h_t audio_codec_index_16h;

    audio_codec_index_16h.w = hal_audio_si_read(paudio_adapter, 0x16);
    audio_codec_index_16h.b.adc_r_ad_gain = step;

    hal_audio_si_write(paudio_adapter, 0x16, audio_codec_index_16h.w);
}

/**
 *  @brief Control the ADC digital mute of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] mute_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_adc_r_dmute (hal_audio_adapter_t *paudio_adapter, BOOL mute_en)
{
    audio_codec_index_15h_t audio_codec_index_15h;

    audio_codec_index_15h.w = hal_audio_si_read(paudio_adapter, 0x15);
    audio_codec_index_15h.b.adc_r_ad_mute = mute_en;

    hal_audio_si_write(paudio_adapter, 0x15, audio_codec_index_15h.w);
}

/**
 *  @brief Control the ADC zero detection function of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] zdet  The detection control.
 *  @param[in] audio_adc_zdet_tout_t  Set the detection timeout.
 *
 *  @returns void
 */
void hal_audio_adc_l_zdet (hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout)
{
    audio_codec_index_12h_t audio_codec_index_12h;

    audio_codec_index_12h.w = hal_audio_si_read(paudio_adapter, 0x12);

    audio_codec_index_12h.b.adc_l_ad_zdet_func = zdet;
    audio_codec_index_12h.b.adc_l_ad_zdet_tout = adc_zdet_tout;

    hal_audio_si_write(paudio_adapter, 0x12, audio_codec_index_12h.w);
}

/**
 *  @brief Control the ADC zero detection function of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] zdet  The detection control.
 *  @param[in] audio_adc_zdet_tout_t  Set the detection timeout.
 *
 *  @returns void
 */
void hal_audio_adc_r_zdet (hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout)
{
    audio_codec_index_15h_t audio_codec_index_15h;

    audio_codec_index_15h.w = hal_audio_si_read(paudio_adapter, 0x15);

    audio_codec_index_15h.b.adc_r_ad_zdet_func = zdet;
    audio_codec_index_15h.b.adc_r_ad_zdet_tout = adc_zdet_tout;

    hal_audio_si_write(paudio_adapter, 0x15, audio_codec_index_15h.w);
}

/**
 *  @brief Control the ADC silence detection function of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] silence_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] detect_sel  The detection control.
 *  @param[in] debounce_time  Set the detection timeout.
 *
 *  @returns void
 */
void hal_audio_adc_l_silence (hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_detect_t detect_sel, audio_silence_debounce_t debounce_time)
{
    audio_codec_index_f8h_t audio_codec_index_f8h;

    audio_codec_index_f8h.w = hal_audio_si_read(paudio_adapter, 0xf8);

    audio_codec_index_f8h.b.adc_l_silence_det_mono_en = silence_en;
    audio_codec_index_f8h.b.adc_l_silence_det_mono_auto_en = detect_sel;
    audio_codec_index_f8h.b.adc_l_silence_mono_debounce_sel = debounce_time;

    hal_audio_si_write(paudio_adapter, 0xf8, audio_codec_index_f8h.w);
}

/**
 *  @brief Control the ADC silence detection parameter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] wordlength  Select the word length.
 *  @param[in] level  Select the detected level.
 *
 *  @returns void
 */
void hal_audio_adc_l_silence_parameter (hal_audio_adapter_t *paudio_adapter, audio_silence_wordlength_t wordlength, audio_silence_Level_t level)
{
    audio_codec_index_f8h_t audio_codec_index_f8h;

    audio_codec_index_f8h.w = hal_audio_si_read(paudio_adapter, 0xf8);

    audio_codec_index_f8h.b.adc_l_silence_mono_data_bit = wordlength;
    audio_codec_index_f8h.b.adc_l_silence_mono_level_sel = level;

    hal_audio_si_write(paudio_adapter, 0xf8, audio_codec_index_f8h.w);
}

/**
 *  @brief Get the ADC silence detection result of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The silence is not detected.
 *  @return     1:  The silence is detected.
 */
u8 hal_audio_adc_l_silence_result (hal_audio_adapter_t *paudio_adapter)
{
    audio_codec_index_f8h_t audio_codec_index_f8h;
    u8 result;

    audio_codec_index_f8h.w = hal_audio_si_read(paudio_adapter, 0xf8);
    result = audio_codec_index_f8h.b.adc_l_silence_det_mono_o;

    return result;
}

/**
 *  @brief Get the ADC silence detection status of the right channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The detection is resting.
 *  @return     1:  The detection is working.
 */
u8 hal_audio_adc_l_silence_status (hal_audio_adapter_t *paudio_adapter)
{
    audio_codec_index_f8h_t audio_codec_index_f8h;
    u8 result;

    audio_codec_index_f8h.w = hal_audio_si_read(paudio_adapter, 0xf8);
    result = audio_codec_index_f8h.b.adc_l_silenece_det_mono_status;

    return result;
}

/**
 *  @brief Control the ADC silence detection function of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] silence_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] detect_sel  The detection control.
 *  @param[in] debounce_time  Set the detection timeout.
 *
 *  @returns void
 */
void hal_audio_adc_r_silence (hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_detect_t detect_sel, audio_silence_debounce_t debounce_time)
{
    audio_codec_index_f9h_t audio_codec_index_f9h;

    audio_codec_index_f9h.w = hal_audio_si_read(paudio_adapter, 0xf9);

    audio_codec_index_f9h.b.adc_r_silence_det_mono_en = silence_en;
    audio_codec_index_f9h.b.adc_r_silence_det_mono_auto_en = detect_sel;
    audio_codec_index_f9h.b.adc_r_silence_mono_debounce_sel = debounce_time;

    hal_audio_si_write(paudio_adapter, 0xf9, audio_codec_index_f9h.w);
}

/**
 *  @brief Control the ADC silence detection parameter of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] wordlength  Select the word length.
 *  @param[in] level  Select the detected level.
 *
 *  @returns void
 */
void hal_audio_adc_r_silence_parameter (hal_audio_adapter_t *paudio_adapter, audio_silence_wordlength_t wordlength, audio_silence_Level_t level)
{
    audio_codec_index_f9h_t audio_codec_index_f9h;

    audio_codec_index_f9h.w = hal_audio_si_read(paudio_adapter, 0xf9);

    audio_codec_index_f9h.b.adc_r_silence_mono_data_bit = wordlength;
    audio_codec_index_f9h.b.adc_r_silence_mono_level_sel = level;

    hal_audio_si_write(paudio_adapter, 0xf9, audio_codec_index_f9h.w);
}

/**
 *  @brief Get the ADC silence detection result of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The silence is not detected.
 *  @return     1:  The silence is detected.
 */
u8 hal_audio_adc_r_silence_result (hal_audio_adapter_t *paudio_adapter)
{
    audio_codec_index_f9h_t audio_codec_index_f9h;
    u8 result;

    audio_codec_index_f9h.w = hal_audio_si_read(paudio_adapter, 0xf9);
    result = audio_codec_index_f9h.b.adc_r_silence_det_mono_o;

    return result;
}

/**
 *  @brief Get the ADC silence detection status of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The detection is resting.
 *  @return     1:  The detection is working.
 */
u8 hal_audio_adc_r_silence_status (hal_audio_adapter_t *paudio_adapter)
{
    audio_codec_index_f9h_t audio_codec_index_f9h;
    u8 result;

    audio_codec_index_f9h.w = hal_audio_si_read(paudio_adapter, 0xf9);
    result = audio_codec_index_f9h.b.adc_r_silenece_det_mono_status;

    return result;
}

/**
 *  @brief Control the DAC dither.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] dac_l_dither Control the dither of the left channel.
 *                      -0: Disable.
 *                      -1: LSB.
 *                      -2: LSB + 1.
 *                      -3: LSB + 2.
 *  @param[in] dac_r_dither Control the dither of the right channel.  This function is not supported.
 *                      -0: Disable.
 *                      -1: LSB.
 *                      -2: LSB + 1.
 *                      -3: LSB + 2.
 *
 *  @returns void
 */
void hal_audio_dac_dither (hal_audio_adapter_t *paudio_adapter, audio_dac_dither_t dac_l_dither, audio_dac_dither_t dac_r_dither)
{
    audio_codec_index_fah_t audio_codec_index_fah;
    audio_codec_index_fch_t audio_codec_index_fch;

    audio_codec_index_fah.w = hal_audio_si_read(paudio_adapter, 0xfa);
    audio_codec_index_fch.w = hal_audio_si_read(paudio_adapter, 0xfc);

    audio_codec_index_fah.b.dac_l_da_dither_sel = dac_l_dither;
    audio_codec_index_fch.b.dac_r_da_dither_sel = dac_r_dither;

    hal_audio_si_write(paudio_adapter, 0xfa, audio_codec_index_fah.w);
    hal_audio_si_write(paudio_adapter, 0xfc, audio_codec_index_fch.w);
}

/**
 *  @brief Control the DAC high pass filter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Control the HPF: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dac_l_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    audio_codec_index_fah_t audio_codec_index_fah;

    audio_codec_index_fah.w = hal_audio_si_read(paudio_adapter, 0xfa);
    audio_codec_index_fah.b.dac_l_dahpf_en = en;
    hal_audio_si_write(paudio_adapter, 0xfa, audio_codec_index_fah.w);
}

/**
 *  @brief Control the DAC high pass filter of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Control the HPF: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dac_r_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    audio_codec_index_fch_t audio_codec_index_fch;

    audio_codec_index_fch.w = hal_audio_si_read(paudio_adapter, 0xfc);
    audio_codec_index_fch.b.dac_r_dahpf_en = en;
    hal_audio_si_write(paudio_adapter, 0xfc, audio_codec_index_fch.w);
}

/**
 *  @brief Control the DAC digital volume of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] step  The digital volume. Every Step is 0.375dB.
 *         The value 0xAF is 0dB.
 *         The value 0x00 is -65.625dB.
 *
 *  @returns void
 */
void hal_audio_dac_l_dvol (hal_audio_adapter_t *paudio_adapter, u8 step)
{
    audio_codec_index_fah_t audio_codec_index_fah;

    audio_codec_index_fah.w = hal_audio_si_read(paudio_adapter, 0xfa);
    audio_codec_index_fah.b.dac_l_da_gain = step;

    hal_audio_si_write(paudio_adapter, 0xfa, audio_codec_index_fah.w);
}

/**
 *  @brief Control the DAC digital mute of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] mute_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dac_l_dmute (hal_audio_adapter_t *paudio_adapter, BOOL mute_en)
{
    audio_codec_index_fbh_t audio_codec_index_fbh;

    audio_codec_index_fbh.w = hal_audio_si_read(paudio_adapter, 0xfb);
    audio_codec_index_fbh.b.dac_l_da_mute = mute_en;

    hal_audio_si_write(paudio_adapter, 0xfb, audio_codec_index_fbh.w);
}

/**
 *  @brief Control the DAC digital volume of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] step  The digital volume. Every Step is 0.375dB.
 *         The value 0xAF is 0dB.
 *         The value 0x00 is -65.625dB.
 *
 *  @returns void
 */
void hal_audio_dac_r_dvol (hal_audio_adapter_t *paudio_adapter, u8 step)
{
    audio_codec_index_fch_t audio_codec_index_fch;

    audio_codec_index_fch.w = hal_audio_si_read(paudio_adapter, 0xfc);
    audio_codec_index_fch.b.dac_r_da_gain = step;

    hal_audio_si_write(paudio_adapter, 0xfc, audio_codec_index_fch.w);
}

/**
 *  @brief Control the DAC digital mute of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] mute_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_dac_r_dmute (hal_audio_adapter_t *paudio_adapter, BOOL mute_en)
{
    audio_codec_index_fdh_t audio_codec_index_fdh;

    audio_codec_index_fdh.w = hal_audio_si_read(paudio_adapter, 0xfd);
    audio_codec_index_fdh.b.dac_r_da_mute = mute_en;

    hal_audio_si_write(paudio_adapter, 0xfd, audio_codec_index_fdh.w);
}

/**
 *  @brief Control the DAC zero detection function of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] zdet  The detection control.
 *  @param[in] audio_adc_zdet_tout_t  Set the detection timeout.
 *
 *  @returns void
 */
void hal_audio_dac_l_zdet (hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_dac_zdet_tout_t adc_zdet_tout)
{
    audio_codec_index_fah_t audio_codec_index_fah;

    audio_codec_index_fah.w = hal_audio_si_read(paudio_adapter, 0xfa);

    audio_codec_index_fah.b.dac_l_da_zdet_func = zdet;
    audio_codec_index_fah.b.dac_l_da_zdet_tout = adc_zdet_tout;

    hal_audio_si_write(paudio_adapter, 0xfa, audio_codec_index_fah.w);
}

/**
 *  @brief Control the DAC zero detection function of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] zdet  The detection control.
 *  @param[in] audio_adc_zdet_tout_t  Set the detection timeout.
 *
 *  @returns void
 */
void hal_audio_dac_r_zdet (hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_dac_zdet_tout_t adc_zdet_tout)
{
    audio_codec_index_fch_t audio_codec_index_fch;

    audio_codec_index_fch.w = hal_audio_si_read(paudio_adapter, 0xfc);

    audio_codec_index_fch.b.dac_r_da_zdet_func = zdet;
    audio_codec_index_fch.b.dac_r_da_zdet_tout = adc_zdet_tout;

    hal_audio_si_write(paudio_adapter, 0xfc, audio_codec_index_fch.w);
}

/**
 *  @brief Control the DAC silence detection function of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] silence_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] detect_sel  The detection control.
 *  @param[in] debounce_time  Set the detection timeout.
 *
 *  @returns void
 */
void hal_audio_dac_l_silence (hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_detect_t detect_sel, audio_silence_debounce_t debounce_time)
{
    audio_codec_index_f6h_t audio_codec_index_f6h;

    audio_codec_index_f6h.w = hal_audio_si_read(paudio_adapter, 0xf6);

    audio_codec_index_f6h.b.dac_l_silence_det_mono_en = silence_en;
    audio_codec_index_f6h.b.dac_l_silence_det_mono_auto_en = detect_sel;
    audio_codec_index_f6h.b.dac_l_silence_mono_debounce_sel = debounce_time;

    hal_audio_si_write(paudio_adapter, 0xf6, audio_codec_index_f6h.w);
}

/**
 *  @brief Control the DAC silence detection parameter of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] wordlength  Select the word length.
 *  @param[in] level  Select the detected level.
 *
 *  @returns void
 */
void hal_audio_dac_l_silence_parameter (hal_audio_adapter_t *paudio_adapter, audio_silence_wordlength_t wordlength, audio_silence_Level_t level)
{
    audio_codec_index_f6h_t audio_codec_index_f6h;

    audio_codec_index_f6h.w = hal_audio_si_read(paudio_adapter, 0xf6);

    audio_codec_index_f6h.b.dac_l_silence_mono_data_bit = wordlength;
    audio_codec_index_f6h.b.dac_l_silence_mono_level_sel = level;

    hal_audio_si_write(paudio_adapter, 0xf6, audio_codec_index_f6h.w);
}

/**
 *  @brief Get the DAC silence detection result of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The silence is not detected.
 *  @return     1:  The silence is detected.
 */
u8 hal_audio_dac_l_silence_result (hal_audio_adapter_t *paudio_adapter)
{
    audio_codec_index_f6h_t audio_codec_index_f6h;
    u8 result;

    audio_codec_index_f6h.w = hal_audio_si_read(paudio_adapter, 0xf6);
    result = audio_codec_index_f6h.b.dac_l_silence_det_mono_o;

    return result;
}

/**
 *  @brief Get the DAC silence detection status of the left channel.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The detection is resting.
 *  @return     1:  The detection is working.
 */
u8 hal_audio_dac_l_silence_status (hal_audio_adapter_t *paudio_adapter)
{
    audio_codec_index_f6h_t audio_codec_index_f6h;
    u8 result;

    audio_codec_index_f6h.w = hal_audio_si_read(paudio_adapter, 0xf6);
    result = audio_codec_index_f6h.b.dac_l_silenece_det_mono_status;

    return result;
}

/**
 *  @brief Control the DAC silence detection function of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] silence_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] detect_sel  The detection control.
 *  @param[in] debounce_time  Set the detection timeout.
 *
 *  @returns void
 */
void hal_audio_dac_r_silence (hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_detect_t detect_sel, audio_silence_debounce_t debounce_time)
{
    audio_codec_index_f7h_t audio_codec_index_f7h;

    audio_codec_index_f7h.w = hal_audio_si_read(paudio_adapter, 0xf7);

    audio_codec_index_f7h.b.dac_r_silence_det_mono_en = silence_en;
    audio_codec_index_f7h.b.dac_r_silence_det_mono_auto_en = detect_sel;
    audio_codec_index_f7h.b.dac_r_silence_mono_debounce_sel = debounce_time;

    hal_audio_si_write(paudio_adapter, 0xf7, audio_codec_index_f7h.w);
}

/**
 *  @brief Control the DAC silence detection parameter of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] wordlength  Select the word length.
 *  @param[in] level  Select the detected level.
 *
 *  @returns void
 */
void hal_audio_dac_r_silence_parameter (hal_audio_adapter_t *paudio_adapter, audio_silence_wordlength_t wordlength, audio_silence_Level_t level)
{
    audio_codec_index_f7h_t audio_codec_index_f7h;

    audio_codec_index_f7h.w = hal_audio_si_read(paudio_adapter, 0xf7);

    audio_codec_index_f7h.b.dac_r_silence_mono_data_bit = wordlength;
    audio_codec_index_f7h.b.dac_r_silence_mono_level_sel = level;

    hal_audio_si_write(paudio_adapter, 0xf7, audio_codec_index_f7h.w);
}

/**
 *  @brief Get the DAC silence detection result of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The silence is not detected.
 *  @return     1:  The silence is detected.
 */
u8 hal_audio_dac_r_silence_result (hal_audio_adapter_t *paudio_adapter)
{
    audio_codec_index_f7h_t audio_codec_index_f7h;
    u8 result;

    audio_codec_index_f7h.w = hal_audio_si_read(paudio_adapter, 0xf7);
    result = audio_codec_index_f7h.b.dac_r_silence_det_mono_o;

    return result;
}

/**
 *  @brief Get the DAC silence detection status of the right channel.
 *         This function is not supported.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @return     0:  The detection is resting.
 *  @return     1:  The detection is working.
 */
u8 hal_audio_dac_r_silence_status (hal_audio_adapter_t *paudio_adapter)
{
    audio_codec_index_f7h_t audio_codec_index_f7h;
    u8 result;

    audio_codec_index_f7h.w = hal_audio_si_read(paudio_adapter, 0xf7);
    result = audio_codec_index_f7h.b.dac_r_silenece_det_mono_status;

    return result;
}

/**
 *  @brief Select the sidetone source.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] source_sel  Select the sidetone source.
 *
 *  @returns void
 */
void hal_audio_sidetone_source (hal_audio_adapter_t *paudio_adapter, audio_sidetone_source_t source_sel)
{
    audio_codec_index_1bh_t audio_codec_index_1bh;

    audio_codec_index_1bh.w = hal_audio_si_read(paudio_adapter, 0x1b);
    audio_codec_index_1bh.b.sidetone_in_sel = source_sel;
    hal_audio_si_write(paudio_adapter, 0x1b, audio_codec_index_1bh.w);
}

/**
 *  @brief Control the sidetone high pass filter.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] hpf_en  Enable Narrow-band 1st HPF : 0 is disable, 1 is enable.
 *  @param[in] sidetone_hpf  Select the sidetone HPF cut-off frequency.
 *
 *  @returns void
 */
void hal_audio_sidetone_hpf (hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf)
{
    audio_codec_index_0fh_t audio_codec_index_0fh;

    audio_codec_index_0fh.w = hal_audio_si_read(paudio_adapter, 0x0f);

    audio_codec_index_0fh.b.sidetone_hpf_en = hpf_en;
    audio_codec_index_0fh.b.sidetone_hpf_fc_sel = sidetone_hpf;

    hal_audio_si_write(paudio_adapter, 0x0f, audio_codec_index_0fh.w);
}

/**
 *  @brief Control the sidetone volume.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sidetone_vol  Select the sidetone volume.
 *  @param[in] sidetone_boost  Select the sidetone boost.
 *
 *  @returns void
 */
void hal_audio_sidetone_vol (hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost)
{
    audio_codec_index_0fh_t audio_codec_index_0fh;

    audio_codec_index_0fh.w = hal_audio_si_read(paudio_adapter, 0x0f);

    audio_codec_index_0fh.b.sidetone_vol_sel = sidetone_vol;
    audio_codec_index_0fh.b.sidetone_boost_sel = sidetone_boost;

    hal_audio_si_write(paudio_adapter, 0x0f, audio_codec_index_0fh.w);
}

/**
 *  @brief Control the ALC function.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] alc_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] alc_stereo_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] sample_rate  Select the ALC sample rate.
 *
 *  @returns void
 */
void hal_audio_alc_ctrl (hal_audio_adapter_t *paudio_adapter, BOOL alc_en, BOOL alc_stereo_en, audio_alc_sample_rate_t sample_rate)
{
    audio_codec_index_1eh_t audio_codec_index_1eh;
    audio_codec_index_20h_t audio_codec_index_20h;
    audio_codec_index_27h_t audio_codec_index_27h;

    audio_codec_index_1eh.w = hal_audio_si_read(paudio_adapter, 0x01e);
    audio_codec_index_20h.w = hal_audio_si_read(paudio_adapter, 0x020);
    audio_codec_index_27h.w = hal_audio_si_read(paudio_adapter, 0x027);

    audio_codec_index_1eh.b.alc_en = alc_en;
    audio_codec_index_20h.b.alc_rate_sel = sample_rate;
    audio_codec_index_27h.b.da_stereo_mode_en = alc_stereo_en;

    hal_audio_si_write(paudio_adapter, 0x01e, audio_codec_index_1eh.w);
    hal_audio_si_write(paudio_adapter, 0x020, audio_codec_index_20h.w);
    hal_audio_si_write(paudio_adapter, 0x027, audio_codec_index_27h.w);
}

/**
 *  @brief Control the ALC boost.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] front_boost_step  Control the front boost gain. Every Step is 0.75dB.
 *         The value 0x27 is 29.25dB.
 *         The value 0x00 is 0dB.
 *  @param[in] back_boost_l_step  Control the back boost gain of the left channel. Every Step is 0.375dB.
 *         The value 0x00 is -35.625dB.
 *         The value 0x5F is 0dB.
 *         The value 0x7F is 12dB.
 *  @param[in] back_boost_r_step  Control the back boost gain of the right channel. Every Step is 0.375dB.
 *         The value 0x00 is -35.625dB.
 *         The value 0x5F is 0dB.
 *         The value 0x7F is 12dB.
 *
 *  @returns void
 */
void hal_audio_alc_boost (hal_audio_adapter_t *paudio_adapter, u8 front_boost_step, u8 back_boost_l_step, u8 back_boost_r_step)
{
    audio_codec_index_1dh_t audio_codec_index_1dh;
    audio_codec_index_1eh_t audio_codec_index_1eh;

    audio_codec_index_1dh.w = hal_audio_si_read(paudio_adapter, 0x01d);
    audio_codec_index_1eh.w = hal_audio_si_read(paudio_adapter, 0x01e);

    audio_codec_index_1dh.b.alc_bk_gain_l = back_boost_l_step;
    audio_codec_index_1dh.b.alc_bk_gain_r = back_boost_r_step;
    audio_codec_index_1eh.b.alc_ft_boost = front_boost_step;

    hal_audio_si_write(paudio_adapter, 0x01d, audio_codec_index_1dh.w);
    hal_audio_si_write(paudio_adapter, 0x01e, audio_codec_index_1eh.w);
}

/**
 *  @brief Set the digital volume when the ALC function is disabled.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] firm_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] firm_gain_step  Control the digital volum. Every Step is -0.375dB.
 *         The value 0xFF is 0dB. (default)
 *         The value 0x00 is -95.625dB.
 *
 *  @returns void
 */
void hal_audio_alc_firm_gain(hal_audio_adapter_t *paudio_adapter, BOOL firm_en, u8 firm_gain_step)
{
    audio_codec_index_1eh_t audio_codec_index_1eh;
    audio_codec_index_20h_t audio_codec_index_20h;
    u8 temp;

    audio_codec_index_1eh.w = hal_audio_si_read(paudio_adapter, 0x01e);
    audio_codec_index_20h.w = hal_audio_si_read(paudio_adapter, 0x020);

    if (firm_en == 1) {
        temp = 0;
    } else {
        temp = 1;
    }
    audio_codec_index_1eh.b.alc_ctr_en = temp;

    audio_codec_index_20h.b.alc_off_gain = firm_gain_step;

    hal_audio_si_write(paudio_adapter, 0x01e, audio_codec_index_1eh.w);
    hal_audio_si_write(paudio_adapter, 0x020, audio_codec_index_20h.w);
}

/**
 *  @brief Control the ALC minimum gain.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] min_gain_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] min_gain_step  Control the gain step. Every Step is -0.375dB.
 *         The value 0xFF is 0dB. (default)
 *         The value 0x00 is -95.625dB.
 *
 *  @returns void
 */
void hal_audio_alc_min_gain(hal_audio_adapter_t *paudio_adapter, BOOL min_gain_en, u8 min_gain_step)
{
    audio_codec_index_26h_t audio_codec_index_26h;
    audio_codec_index_27h_t audio_codec_index_27h;

    audio_codec_index_26h.w = hal_audio_si_read(paudio_adapter, 0x026);
    audio_codec_index_27h.w = hal_audio_si_read(paudio_adapter, 0x027);

    audio_codec_index_26h.b.alc_min_gain_en = min_gain_en;
    audio_codec_index_27h.b.alc_min_gain = min_gain_step;

    hal_audio_si_write(paudio_adapter, 0x026, audio_codec_index_26h.w);
    hal_audio_si_write(paudio_adapter, 0x027, audio_codec_index_27h.w);
}

/**
 *  @brief Set the coefficient for the ALC low pass filter.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lpf_coef  Select the coefficient.
 *
 *  @returns void
 */
void hal_audio_alc_lpf_coef (hal_audio_adapter_t *paudio_adapter, audio_alc_lpf_coef_t lpf_coef)
{
    audio_codec_index_1fh_t audio_codec_index_1fh;

    audio_codec_index_1fh.w = hal_audio_si_read(paudio_adapter, 0x1f);
    audio_codec_index_1fh.b.alc_lpf_coef_sel = lpf_coef;
    hal_audio_si_write(paudio_adapter, 0x1f, audio_codec_index_1fh.w);
}

/**
 *  @brief Control the ALC limiter function.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] limit_ratio  Select the limiter ratio.
 *  @param[in] threshold  Set the threshold.  Threshold_in_db = 20*log10(alc_limiter_th * 2^-23).
 *
 *  @returns void
 */
void hal_audio_alc_limiter_ctrl (hal_audio_adapter_t *paudio_adapter, audio_alc_limit_ratio_t limit_ratio, u32 threshold)
{
    audio_codec_index_24h_t audio_codec_index_24h;
    audio_codec_index_25h_t audio_codec_index_25h;
    audio_codec_index_26h_t audio_codec_index_26h;

    audio_codec_index_24h.w = hal_audio_si_read(paudio_adapter, 0x24);
    audio_codec_index_25h.w = hal_audio_si_read(paudio_adapter, 0x25);
    audio_codec_index_26h.w = hal_audio_si_read(paudio_adapter, 0x26);

    audio_codec_index_24h.b.alc_limiter_ratio = limit_ratio;
    audio_codec_index_25h.b.alc_limiter_th_15_0 = (u16)(threshold & 0x0ffff);
    audio_codec_index_26h.b.alc_limiter_th_23_16 = (u8)((threshold >> 16) & 0x0ff);

    hal_audio_si_write(paudio_adapter, 0x24, audio_codec_index_24h.w);
    hal_audio_si_write(paudio_adapter, 0x25, audio_codec_index_25h.w);
    hal_audio_si_write(paudio_adapter, 0x26, audio_codec_index_26h.w);
}

/**
 *  @brief Control the ALC zero detection function.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] zdet  The detection control.
 *  @param[in] audio_adc_zdet_tout_t  Set the detection timeout.
 *
 *  @returns void
 */
void hal_audio_alc_zdet (hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_alc_zdet_tout_t alc_zdet_tout)
{
    audio_codec_index_24h_t audio_codec_index_24h;

    audio_codec_index_24h.w = hal_audio_si_read(paudio_adapter, 0x24);

    audio_codec_index_24h.b.alc_zdet_func = zdet;
    audio_codec_index_24h.b.alc_zdet_tout = alc_zdet_tout;

    hal_audio_si_write(paudio_adapter, 0x24, audio_codec_index_24h.w);
}

/**
 *  @brief Set the ALC full sacle.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] alc_full_scale Control the full scale threshold level.
 *                      -00: 0 dbFs. (default)
 *                      -01: -0.5 dbFs.
 *                      -10: -1.0 dbFs.
 *                      -11: -1.5 dbFs.
 *
 *  @returns void
 */
void hal_audio_alc_full_scale (hal_audio_adapter_t *paudio_adapter, audio_alc_full_scale_t alc_full_scale)
{
    audio_codec_index_23h_t audio_codec_index_23h;

    audio_codec_index_23h.w = hal_audio_si_read(paudio_adapter, 0x23);
    audio_codec_index_23h.b.alc_thfull = alc_full_scale;
    hal_audio_si_write(paudio_adapter, 0x23, audio_codec_index_23h.w);
}

/**
 *  @brief Control the ALC DRC.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_alc_drc_en (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    audio_codec_index_1eh_t audio_codec_index_1eh;

    audio_codec_index_1eh.w = hal_audio_si_read(paudio_adapter, 0x1e);

    audio_codec_index_1eh.b.alc_drc_en = en;

    hal_audio_si_write(paudio_adapter, 0x1e, audio_codec_index_1eh.w);
}

/**
 *  @brief Control the attack threshold 1 of the ALC DRC.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] threshold_step  Control the ALC main-limiter threshold level. Every Step is -0.375dB.
 *         The value 0x00 is 0dB. (default)
 *         The value 0x3F is -23.65dB.
 *  @param[in] range_step  Control the range step. Every Step is +/-0.375dB.
 *         The value 0x00 is 0dB.
 *         The value 0x02 is +/-0.75dB. (default)
 *         The value 0x07 is +/-2.625dB.
 *
 *  @returns void
 */
void hal_audio_alc_drc_attack_thr1 (hal_audio_adapter_t *paudio_adapter, u8 threshold_step, u8 range_step)
{
    audio_codec_index_1fh_t audio_codec_index_1fh;
    audio_codec_index_21h_t audio_codec_index_21h;

    audio_codec_index_1fh.w = hal_audio_si_read(paudio_adapter, 0x1f);
    audio_codec_index_21h.w = hal_audio_si_read(paudio_adapter, 0x21);

    audio_codec_index_1fh.b.alc_min_range = range_step;
    audio_codec_index_21h.b.alc_thmax = threshold_step;

    hal_audio_si_write(paudio_adapter, 0x1f, audio_codec_index_1fh.w);
    hal_audio_si_write(paudio_adapter, 0x21, audio_codec_index_21h.w);
}

/**
 *  @brief Control the attack threshold 2 of the ALC DRC.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] threshold_step  Control the ALC main-limiter threshold level. Every Step is -0.75dB.
 *         The value 0x00 is 0dB. (default)
 *         The value 0x3C is -45dB.
 *  @param[in] range_step  Control the range step. Every Step is +/-0.375dB.
 *         The value 0x00 is 0dB.
 *         The value 0x02 is +/-0.75dB. (default)
 *         The value 0x7 is +/-2.625dB.
 *
 *  @returns void
 */
void hal_audio_alc_drc_attack_thr2 (hal_audio_adapter_t *paudio_adapter, u8 threshold_step, u8 range_step)
{
    audio_codec_index_1fh_t audio_codec_index_1fh;
    audio_codec_index_23h_t audio_codec_index_23h;

    audio_codec_index_1fh.w = hal_audio_si_read(paudio_adapter, 0x1f);
    audio_codec_index_23h.w = hal_audio_si_read(paudio_adapter, 0x23);

    audio_codec_index_1fh.b.alc_min_range = range_step;
    audio_codec_index_23h.b.alc_thmax2 = threshold_step;

    hal_audio_si_write(paudio_adapter, 0x1f, audio_codec_index_1fh.w);
    hal_audio_si_write(paudio_adapter, 0x23, audio_codec_index_23h.w);
}

/**
 *  @brief Control the attack rate of the ALC DRC.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] speed_rate_en  Speed rate control: 0 is to use the normal rate, 1 is to use the speed rate.
 *  @param[in] normal_rate_time  ALC normal attack time, (4 * 2^n) /48k, n = normal_rate_time.
 *         The value 0x00 is 83us.
 *         The value 0x03 is 666us. (default)
 *         The value 0x12 is 21.85s.
 *  @param[in] speed_rate_time  ALC speed attack time, (2 * 2^n) /48k, n = speed_rate_time.
 *         The value 0x00 is 42us. (default)
 *         The value 0x13 is 21.85s.
 *
 *  @returns void
 */
void hal_audio_alc_drc_attack_rate (hal_audio_adapter_t *paudio_adapter, BOOL speed_rate_en, u8 normal_rate_time, u8 speed_rate_time)
{
    audio_codec_index_1ch_t audio_codec_index_1ch;
    audio_codec_index_1dh_t audio_codec_index_1dh;

    audio_codec_index_1ch.w = hal_audio_si_read(paudio_adapter, 0x1c);
    audio_codec_index_1dh.w = hal_audio_si_read(paudio_adapter, 0x1d);

    audio_codec_index_1ch.b.alc_atk_rate = normal_rate_time;
    audio_codec_index_1ch.b.alc_atk_speed_up_rate = speed_rate_time;
    audio_codec_index_1dh.b.alc_speed_up_en = speed_rate_en;

    hal_audio_si_write(paudio_adapter, 0x1c, audio_codec_index_1ch.w);
    hal_audio_si_write(paudio_adapter, 0x1d, audio_codec_index_1dh.w);
}

/**
 *  @brief Set the ratio 1 by using the attack threshold 1 of the ALC DRC.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] drc_ratio1  Select the ALC DRC compression ratio.
 *                      -00: 1 : 1.
 *                      -01: 1 : 2. (default)
 *                      -10: 1 : 4.
 *                      -11: 1 : 8.
 *
 *  @returns void
 */
void hal_audio_alc_drc_attack_ratio1 (hal_audio_adapter_t *paudio_adapter, audio_alc_drc_ratio_t drc_ratio1)
{
    audio_codec_index_1eh_t audio_codec_index_1eh;

    audio_codec_index_1eh.w = hal_audio_si_read(paudio_adapter, 0x1e);
    audio_codec_index_1eh.b.alc_drc_ratio_sel = drc_ratio1;
    hal_audio_si_write(paudio_adapter, 0x1e, audio_codec_index_1eh.w);
}

/**
 *  @brief Set the ratio 2 by using the attack threshold 2 of the ALC DRC.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] drc_ratio2  Select the ALC DRC compression ratio.
 *                      -00: 1 : 1.
 *                      -01: 1 : 2. (default)
 *                      -10: 1 : 4.
 *                      -11: 1 : 8.
 *
 *  @returns void
 */
void hal_audio_alc_drc_attack_ratio2 (hal_audio_adapter_t *paudio_adapter, audio_alc_drc_ratio_t drc_ratio2)
{
    audio_codec_index_1eh_t audio_codec_index_1eh;

    audio_codec_index_1eh.w = hal_audio_si_read(paudio_adapter, 0x1e);
    audio_codec_index_1eh.b.alc_drc_ratio_sel2 = drc_ratio2;
    hal_audio_si_write(paudio_adapter, 0x1e, audio_codec_index_1eh.w);
}

/**
 *  @brief Control the hold time of the ALC.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] hold_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] recover_time  Control the recover time.
 *                      -00: 5ms, @fs 48k.  240 samples.
 *                      -01: 400ms, @fs 48k. 19200 samples. (default)
 *                      -10: 1200ms, @fs 48k. 57600 samples.
 *                      -11: 2400ms, @fs 48k. 115200 samples.
 *
 *  @returns void
 */
void hal_audio_alc_attack_hold (hal_audio_adapter_t *paudio_adapter, BOOL hold_en, audio_alc_drc_hold_t recover_time)
{
    audio_codec_index_24h_t audio_codec_index_24h;
    audio_codec_index_26h_t audio_codec_index_26h;

    audio_codec_index_24h.w = hal_audio_si_read(paudio_adapter, 0x24);
    audio_codec_index_26h.w = hal_audio_si_read(paudio_adapter, 0x26);

    audio_codec_index_26h.b.alc_atk_hold_recov_th = recover_time;
    audio_codec_index_24h.b.alc_atk_hold_en = hold_en;

    hal_audio_si_write(paudio_adapter, 0x24, audio_codec_index_24h.w);
    hal_audio_si_write(paudio_adapter, 0x26, audio_codec_index_26h.w);
}


/**
 *  @brief Control the hold-release time of the ALC.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] release_en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] release_time  Control the release time.
 *                      -00: 5ms, @fs 48k.  240 samples.
 *                      -01: 400ms, @fs 48k. 19200 samples. (default)
 *                      -10: 1200ms, @fs 48k. 57600 samples.
 *                      -11: 2400ms, @fs 48k. 115200 samples.
 *
 *  @returns void
 */
void hal_audio_alc_attack_hold_to_release (hal_audio_adapter_t *paudio_adapter, BOOL release_en, audio_alc_drc_hold_t release_time)
{
    audio_codec_index_26h_t audio_codec_index_26h;

    audio_codec_index_26h.w = hal_audio_si_read(paudio_adapter, 0x26);

    audio_codec_index_26h.b.alc_atk_hold_release_th = release_time;
    audio_codec_index_26h.b.alc_atk_hold_release_en = release_en;

    hal_audio_si_write(paudio_adapter, 0x26, audio_codec_index_26h.w);
}

/**
 *  @brief Control the noise gate.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_alc_noise_gate_en (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    audio_codec_index_1fh_t audio_codec_index_1fh;

    audio_codec_index_1fh.w = hal_audio_si_read(paudio_adapter, 0x1f);
    audio_codec_index_1fh.b.alc_noise_gate_en = en;
    hal_audio_si_write(paudio_adapter, 0x1f, audio_codec_index_1fh.w);
}

/**
 *  @brief Control the attack threshold of the ALC noise gate.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] threshold_step  Control the AGC noise gate threshold level. Every Step is -1.5dB.
 *         The value 0x00 is-24dB. (default)
 *         The value 0x1F is -70.5dB.
 *  @param[in] range_step  Control the range step. Every Step is +/-1.5dB.
 *         The value 0x00 is 0dB.
 *         The value 0x01 is +/-1.5dB. (default)
 *         The value 0x03 is +/-4.5dB.
 *
 *  @returns void
 */
void hal_audio_alc_noise_gate_attack_thr (hal_audio_adapter_t *paudio_adapter, u8 threshold_step, u8 range_step)
{
    audio_codec_index_20h_t audio_codec_index_20h;
    audio_codec_index_23h_t audio_codec_index_23h;

    audio_codec_index_20h.w = hal_audio_si_read(paudio_adapter, 0x20);
    audio_codec_index_23h.w = hal_audio_si_read(paudio_adapter, 0x23);

    audio_codec_index_20h.b.alc_noise_range = range_step;
    audio_codec_index_23h.b.alc_thnoise = threshold_step;

    hal_audio_si_write(paudio_adapter, 0x20, audio_codec_index_20h.w);
    hal_audio_si_write(paudio_adapter, 0x23, audio_codec_index_23h.w);
}

/**
 *  @brief Control the attack rate of the ALC noise gate.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] rate_time  ALC normal attack time, (4 * 2^n) /48k, n = rate_time.
 *         The value 0x00 is 83us.
 *         The value 0x06 is 5.33ms. (default)
 *         The value 0x12 is 21.85s.
 *
 *  @returns void
 */
void hal_audio_alc_noise_gate_attack_rate (hal_audio_adapter_t *paudio_adapter, u8 rate_time)
{
    audio_codec_index_1ch_t audio_codec_index_1ch;

    audio_codec_index_1ch.w = hal_audio_si_read(paudio_adapter, 0x1c);
    audio_codec_index_1ch.b.alc_atk_noise_rate = rate_time;
    hal_audio_si_write(paudio_adapter, 0x1c, audio_codec_index_1ch.w);
}

/**
 *  @brief Control the attack drop of the ALC noise gate.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *  @param[in] drop_gain_step  ALC noise_gate boost. Every Step is -3dB.
 *         The value 0x00 is 0dB.
 *         The value 0x04 is -12dB. (default)
 *         The value 0x0F is -45dB.
 *
 *  @returns void
 */
void hal_audio_alc_noise_gate_attack_drop (hal_audio_adapter_t *paudio_adapter, BOOL en, u8 drop_gain_step)
{
    audio_codec_index_1fh_t audio_codec_index_1fh;

    audio_codec_index_1fh.w = hal_audio_si_read(paudio_adapter, 0x1f);
    audio_codec_index_1fh.b.alc_noise_gate_drop_en = en;
    audio_codec_index_1fh.b.alc_noise_gate_exp = drop_gain_step;
    hal_audio_si_write(paudio_adapter, 0x1f, audio_codec_index_1fh.w);
}

/**
 *  @brief Control the attack hold of the ALC noise gate.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] hold_gate_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_alc_noise_gate_attack_hold (hal_audio_adapter_t *paudio_adapter, BOOL hold_gate_en)
{
    audio_codec_index_1fh_t audio_codec_index_1fh;

    audio_codec_index_1fh.w = hal_audio_si_read(paudio_adapter, 0x1f);
    audio_codec_index_1fh.b.alc_noise_gain_hd = hold_gate_en;
    hal_audio_si_write(paudio_adapter, 0x1f, audio_codec_index_1fh.w);
}

/**
 *  @brief Control the expand ratio of the ALC noise gate.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] expand_ratio  Select the ALC noise expand ratio.
 *                      -00: 1 : 1.
 *                      -01: 2 : 1. (default)
 *                      -10: 4 : 1.
 *                      -11: 8 : 1.
 *
 *  @returns void
 */
void hal_audio_alc_noise_gate_expand_ratio (hal_audio_adapter_t *paudio_adapter, audio_alc_noise_gate_ratio_t expand_ratio)
{
    audio_codec_index_1fh_t audio_codec_index_1fh;

    audio_codec_index_1fh.w = hal_audio_si_read(paudio_adapter, 0x1f);
    audio_codec_index_1fh.b.alc_noise_gate_ratio_sel = expand_ratio;
    hal_audio_si_write(paudio_adapter, 0x1f, audio_codec_index_1fh.w);
}

/**
 *  @brief Control the zero data of the ALC.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_alc_zero_data_en (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    audio_codec_index_24h_t audio_codec_index_24h;

    audio_codec_index_24h.w = hal_audio_si_read(paudio_adapter, 0x24);
    audio_codec_index_24h.b.alc_zero_data_en = en;
    hal_audio_si_write(paudio_adapter, 0x24, audio_codec_index_24h.w);
}

/**
 *  @brief Control the threshold of the ALC zero data .
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] detect_sel  Select ALC zero data mode.
 *  @param[in] rms_threshold_step  ALC zero-data threshold level. Every Step is -1.5dB.
 *         The value 0x00 is -84dB. (default)
 *         The value 0x07 is -94.5dB.
 *  @param[in] amp_threshold_step  Threshold for ALC zero data mode with amplitude detection.
 *                      -000: -78dB.
 *                      -001: -84dB. (default)
 *                      -010: -90dB.
 *                      -011: -102dB.
 *                      -100: -108dB.
 *                      -101: -114dB.
 *                      -110: -126dB.
 *                      -111: -132dB.
 *
 *  @returns void
 */
void hal_audio_alc_zero_data_thr (hal_audio_adapter_t *paudio_adapter, audio_alc_zero_detect_t detect_sel, u8 rms_threshold_step, u8 amp_threshold_step)
{
    audio_codec_index_23h_t audio_codec_index_23h;
    audio_codec_index_24h_t audio_codec_index_24h;

    audio_codec_index_23h.w = hal_audio_si_read(paudio_adapter, 0x23);
    audio_codec_index_24h.w = hal_audio_si_read(paudio_adapter, 0x24);

    audio_codec_index_23h.b.alc_thzero = rms_threshold_step;
    audio_codec_index_24h.b.alc_zero_data_sel = detect_sel;
    audio_codec_index_24h.b.alc_zero_data_lsb_sel = amp_threshold_step;

    hal_audio_si_write(paudio_adapter, 0x23, audio_codec_index_23h.w);
    hal_audio_si_write(paudio_adapter, 0x24, audio_codec_index_24h.w);
}

/**
 *  @brief Control time out for the amplitude detection of the ALC zero data mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] check_time  Control the check time.
 *                      -00: 20ms, @fs 48k. 1024 samples.
 *                      -01: 40ms, @fs 48k. 2048 samples.
 *                      -10: 80ms, @fs 48k. 4096 samples. (default)
 *                      -11: 0.17ms, @fs 48k. 8 samples.
 *
 *  @returns void
 */
void hal_audio_alc_zero_data_time (hal_audio_adapter_t *paudio_adapter, u8 check_time)
{
    audio_codec_index_24h_t audio_codec_index_24h;

    audio_codec_index_24h.w = hal_audio_si_read(paudio_adapter, 0x24);
    audio_codec_index_24h.b.alc_zero_data_cnt_th = check_time;
    hal_audio_si_write(paudio_adapter, 0x24, audio_codec_index_24h.w);
}

/**
 *  @brief Control the ALC recovery mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] recovery_mode  Control the recovery mode.
 *  @param[in] slow_recovery_time  ALC slow recovery time, (4 * 2^n) /48k, n = slow_recovery_time.
 *         The value 0x00 is 83us. (default)
 *         The value 0x12 is 21.85s.
 *  @param[in] fast_recovery_time  ALC fast recovery time, (4 * 2^n) /48k, n = fast_recovery_time.
 *         The value 0x00 is 83us.
 *         The value 0x04 is 1.328ms. (default)
 *         The value 0x12 is 21.85s.
 *
 *  @returns void
 */
void hal_audio_alc_recovery_ctrl (hal_audio_adapter_t *paudio_adapter, audio_alc_recovery_mode_t recovery_mode, u8 slow_recovery_time, u8 fast_recovery_time)
{
    audio_codec_index_1ch_t audio_codec_index_1ch;
    audio_codec_index_1eh_t audio_codec_index_1eh;
    audio_codec_index_21h_t audio_codec_index_21h;

    audio_codec_index_1ch.w = hal_audio_si_read(paudio_adapter, 0x1c);
    audio_codec_index_1eh.w = hal_audio_si_read(paudio_adapter, 0x1e);
    audio_codec_index_21h.w = hal_audio_si_read(paudio_adapter, 0x21);

    if (recovery_mode == AUDIO_FORCE_SLOW) {
        audio_codec_index_1ch.b.alc_atk_mode_rc_ctr = 0;
        audio_codec_index_1eh.b.alc_force_fast_rc_ctr = 0;
    } else if (recovery_mode == AUDIO_FORCE_FAST) {
        audio_codec_index_1ch.b.alc_atk_mode_rc_ctr = 1;
        audio_codec_index_1eh.b.alc_force_fast_rc_ctr = 1;
    }

    audio_codec_index_21h.b.alc_rc_fast_rate = fast_recovery_time;
    audio_codec_index_21h.b.alc_rc_slow_rate = slow_recovery_time;

    hal_audio_si_write(paudio_adapter, 0x1c, audio_codec_index_1ch.w);
    hal_audio_si_write(paudio_adapter, 0x1e, audio_codec_index_1eh.w);
    hal_audio_si_write(paudio_adapter, 0x21, audio_codec_index_21h.w);
}

/**
 *  @brief Control the ALC force fast recovery by the window mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable the recovery window: 0 is disable, 1 is enable.
 *  @param[in] upper_bound  Set upper bound of fast recovery window. Every Step is 5.33ms.
 *         The value 0x01 is 5.33ms.
 *         The value 0x74 is 618.28ms. (default)
 *         The value 0xFF is 1360ms.
 *  @param[in] lower_bound  Set lower bound of fast recovery window. Every Step is 2.67ms.
 *         The value 0x01 is 2.67ms.
 *         The value 0x18 is 64.08ms. (default)
 *         The value 0xFF is 680ms.
 *
 *  @returns void
 */
void hal_audio_alc_recovery_special_mode1 (hal_audio_adapter_t *paudio_adapter, BOOL en, u8 upper_bound, u8 lower_bound)
{
    audio_codec_index_20h_t audio_codec_index_20h;
    audio_codec_index_22h_t audio_codec_index_22h;

    audio_codec_index_20h.w = hal_audio_si_read(paudio_adapter, 0x20);
    audio_codec_index_22h.w = hal_audio_si_read(paudio_adapter, 0x22);
    audio_codec_index_20h.b.alc_rc_fast_en = en;
    audio_codec_index_22h.b.alc_rc_wd_max = upper_bound;
    audio_codec_index_22h.b.alc_rc_wd_min = lower_bound;
    hal_audio_si_write(paudio_adapter, 0x20, audio_codec_index_20h.w);
    hal_audio_si_write(paudio_adapter, 0x22, audio_codec_index_22h.w);
}

/**
 *  @brief Control the ALC force fast recovery by the zero data mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_alc_recovery_special_mode2 (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    audio_codec_index_1eh_t audio_codec_index_1eh;

    audio_codec_index_1eh.w = hal_audio_si_read(paudio_adapter, 0x1e);
    audio_codec_index_1eh.b.alc_force_fast_rc_en = en;
    hal_audio_si_write(paudio_adapter, 0x1e, audio_codec_index_1eh.w);
}

//Audio Codec Analog Part

/**
 *  @brief Control the power of the ADC and DAC clock.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
void hal_audio_ad_da_clk_power (hal_audio_adapter_t *paudio_adapter, BOOL en)
{
    audio_codec_index_00h_t audio_codec_index_00h;

    audio_codec_index_00h.w = hal_audio_si_read(paudio_adapter, 0x00);
    audio_codec_index_00h.b.dac_addack_pow = en;
    hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
}

/**
 *  @brief Control the DAC power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_dac_power (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_00h_t audio_codec_index_00h;

    audio_codec_index_00h.w = hal_audio_si_read(paudio_adapter, 0x00);
    audio_codec_index_00h.b.dac_l_pow = left_en;
    audio_codec_index_00h.b.dac_r_pow = right_en;
    hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
}

/**
 *  @brief Control the ADC power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_adc_power (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_00h_t audio_codec_index_00h;

    audio_codec_index_00h.w = hal_audio_si_read(paudio_adapter, 0x00);
    audio_codec_index_00h.b.dtsdm_pow_l = left_en;
    audio_codec_index_00h.b.dtsdm_pow_r = right_en;
    hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
}

/**
 *  @brief Control the output power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_output_mode_t Select the output mode.
 *
 *  @returns void
 */
void hal_audio_output_power (hal_audio_adapter_t *paudio_adapter, audio_output_mode_t output_mode)
{
    audio_codec_index_00h_t audio_codec_index_00h;
    audio_codec_index_01h_t audio_codec_index_01h;
    audio_codec_index_02h_t audio_codec_index_02h;
    //audio_codec_index_03h_t audio_codec_index_03h;
    audio_codec_index_0ch_t audio_codec_index_0ch;
    u16 input_index_00h;
    u16 input_index_02h;

    input_index_00h = hal_audio_si_read(paudio_adapter, 0x00) & 0x0c00;
    input_index_02h = hal_audio_si_read(paudio_adapter, 0x02) & 0x7e00;

    if (output_mode == AUDIO_OUTPUT_SINGLE_EDNED) {

        DBG_AUDIO_INFO(" hal_audio_output_power, AUDIO_OUTPUT_SINGLE_EDNED\r\n");

        //Step0:
        //audio_codec_index_03h.w = 0x08f0;
        //hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);

        //Step1:
        audio_codec_index_00h.w = (0x031b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_01h.w = 0x07fc;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
        audio_codec_index_02h.w = (0x81ea | input_index_02h);
        hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
        audio_codec_index_0ch.w = 0x0010;
        hal_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch.w);

        //Step2:
        audio_codec_index_01h.w = 0x9ffc;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
        audio_codec_index_02h.w = (0x81fa | input_index_02h);
        hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);

        //Step3:
        audio_codec_index_00h.w = (0x039b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_0ch.w = 0x0018;
        hal_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch.w);

        //Step4:
        hal_delay_ms(300);

        //Step5:
        audio_codec_index_00h.w = (0x021b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_01h.w = 0x04fc;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
        audio_codec_index_02h.w = (0x81ea | input_index_02h);
        hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
        audio_codec_index_0ch.w = 0x0010;
        hal_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch.w);

    } else if (output_mode == AUDIO_OUTPUT_DIFFERENTIAL) {

        DBG_AUDIO_INFO(" hal_audio_output_power, AUDIO_OUTPUT_DIFFERENTIAL\r\n");

        //Step0:
        //audio_codec_index_03h.w = 0x08f0;
        //hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);

        //Step1:
        audio_codec_index_00h.w = (0x031b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_01h.w = 0x07fc;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
        audio_codec_index_02h.w = (0x812a | input_index_02h);
        hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
        audio_codec_index_0ch.w = 0x0010;
        hal_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch.w);

        //Step2:
        audio_codec_index_01h.w = 0x9ffc;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
        audio_codec_index_02h.w = (0x813a | input_index_02h);
        hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);

        //Step3:
        audio_codec_index_00h.w = (0x039b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_0ch.w = 0x0018;
        hal_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch.w);

        //Step4:
        hal_delay_ms(50);

        //Step5:
        audio_codec_index_00h.w = (0x031b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_01h.w = 0x67fc;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
        audio_codec_index_02h.w = (0x812a | input_index_02h);
        hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);

        //Step6:
        audio_codec_index_00h.w = (0x039b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);

        //Step7:
        hal_delay_ms(5);

        //Step8:
        audio_codec_index_01h.w = 0x04fc;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);

        //Step9:
        audio_codec_index_00h.w = (0x021b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_0ch.w = 0x0010;
        hal_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch.w);

    } else if (output_mode == AUDIO_OUTPUT_CAPLESS) {

        DBG_AUDIO_INFO(" hal_audio_output_power, AUDIO_OUTPUT_CAPLESS\r\n");

        //Step0:
        //audio_codec_index_03h.w = 0x08f0;
        //hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);

        //Step1:
        audio_codec_index_00h.w = (0x131b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_01h.w = 0x07fe;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
        audio_codec_index_02h.w = (0x81ea | input_index_02h);
        hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
        audio_codec_index_0ch.w = 0x0010;
        hal_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch.w);

        //Step2:
        audio_codec_index_00h.w = (0x731b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);

        //Step3:
        audio_codec_index_00h.w = (0x739b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_0ch.w = 0x0018;
        hal_audio_si_write(paudio_adapter, 0x0c, audio_codec_index_0ch.w);

        //Step4:
        hal_delay_ms(50);

        //Step5:
        audio_codec_index_00h.w = (0x731b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);

        //Step6:
        audio_codec_index_00h.w = (0x931b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_01h.w = 0x1fff;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);

        //Step7:
        audio_codec_index_00h.w = (0x939b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);

        //Step8:
        hal_delay_ms(5);

        //Step9:
        audio_codec_index_01h.w = 0x04fe;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);

        //Step10:
        audio_codec_index_00h.w = (0x121b | input_index_00h);
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);

    } else if (output_mode == AUDIO_OUTPUT_DISABLE) {

        DBG_AUDIO_INFO(" hal_audio_output_power, AUDIO_OUTPUT_DISABLE\r\n");

        audio_codec_index_00h.w = hal_audio_si_read(paudio_adapter, 0x00);
        audio_codec_index_01h.w = hal_audio_si_read(paudio_adapter, 0x01);
        audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);

        audio_codec_index_00h.w = audio_codec_index_00h.w & 0x0FFF;
        hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
        audio_codec_index_01h.w = audio_codec_index_01h.w & 0x0000;
        hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
        audio_codec_index_02h.w = audio_codec_index_02h.w & 0xFF00;
        hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);

        hal_delay_ms(3);
    }

    if (output_mode != AUDIO_OUTPUT_DISABLE) {
        hal_audio_dac_clk(paudio_adapter, ENABLE, ENABLE);
        hal_audio_dac_mixer(paudio_adapter, DISABLE, DISABLE);
    } else {
        hal_audio_dac_clk(paudio_adapter, DISABLE, DISABLE);
        hal_audio_dac_mixer(paudio_adapter, ENABLE, ENABLE);
    }

}

/**
 *  @brief Control the input power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_input_mode_t Select the input mode.
 *
 *  @returns void
 */
void hal_audio_input_power (hal_audio_adapter_t *paudio_adapter, audio_input_mode_t input_mode)
{
    audio_codec_index_02h_t audio_codec_index_02h;
    audio_codec_index_03h_t audio_codec_index_03h;

    if ((input_mode == AUDIO_MIC_DIFFERENTIAL) || (input_mode == AUDIO_MIC_SINGLE_EDNED)) {

        //MICBAS POW
        hal_delay_us(1);
        audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);
        audio_codec_index_02h.b.micbias_enchx = 1;
        audio_codec_index_02h.b.micbias_pow = 1;
        hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);

        //MICBST POW
        hal_delay_us(2);
        audio_codec_index_03h.w = hal_audio_si_read(paudio_adapter, 0x03);
        audio_codec_index_03h.b.micbst_pow = 3;
        hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);

        if (input_mode == AUDIO_MIC_DIFFERENTIAL) {
            DBG_AUDIO_INFO(" hal_audio_input_power, AUDIO_MIC_DIFFERENTIAL\r\n");
            hal_audio_mic_differential_mode(paudio_adapter, ENABLE, ENABLE);
        } else {
            DBG_AUDIO_INFO(" hal_audio_input_power, AUDIO_MIC_SINGLE_EDNED\r\n");
            hal_audio_mic_differential_mode(paudio_adapter, DISABLE, DISABLE);
        }

        hal_audio_adc_power(paudio_adapter, ENABLE, ENABLE);
        hal_audio_mic_boost(paudio_adapter, ENABLE, AUDIO_MIC_0DB, ENABLE, AUDIO_MIC_0DB);
        hal_audio_adc_clk(paudio_adapter, ENABLE, ENABLE);
        hal_audio_adc_amic_mixer(paudio_adapter, DISABLE, DISABLE);

        hal_audio_line_in_mute(paudio_adapter, ENABLE, ENABLE);
        hal_audio_mic_mute(paudio_adapter, DISABLE, DISABLE);

        hal_audio_mic_bias(paudio_adapter, ENABLE, AUDIO_BIAS_0p9_AVDD);
    } else if (input_mode == AUDIO_LINE_IN_MODE) {

        DBG_AUDIO_INFO(" hal_audio_input_power, AUDIO_LINE_IN_MODE\r\n");

        //MICBAS POW
        hal_delay_us(1);
        audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);
        audio_codec_index_02h.b.micbias_enchx = 1;
        audio_codec_index_02h.b.micbias_pow = 0;
        hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);

        //MICBST POW
        hal_delay_us(2);
        audio_codec_index_03h.w = hal_audio_si_read(paudio_adapter, 0x03);
        audio_codec_index_03h.b.micbst_pow = 0;
        hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);

        hal_audio_adc_power(paudio_adapter, ENABLE, ENABLE);
        hal_audio_mic_boost(paudio_adapter, ENABLE, AUDIO_MIC_0DB, ENABLE, AUDIO_MIC_0DB);
        hal_audio_adc_clk(paudio_adapter, ENABLE, ENABLE);
        hal_audio_adc_amic_mixer(paudio_adapter, DISABLE, DISABLE);

        hal_audio_mic_mute(paudio_adapter, ENABLE, ENABLE);
        hal_audio_line_in_mute(paudio_adapter, DISABLE, DISABLE);
    } else if (input_mode == AUDIO_INPUT_DISABLE) {
        DBG_AUDIO_INFO(" hal_audio_input_power, AUDIO_INPUT_DISABLE\r\n");
        hal_audio_mic_mute(paudio_adapter, ENABLE, ENABLE);
        hal_audio_line_in_mute(paudio_adapter, ENABLE, ENABLE);
        hal_audio_adc_amic_mixer(paudio_adapter, ENABLE, ENABLE);
        hal_audio_adc_clk(paudio_adapter, DISABLE, DISABLE);
        hal_audio_mic_boost(paudio_adapter, DISABLE, AUDIO_MIC_0DB, DISABLE, AUDIO_MIC_0DB);
        hal_audio_adc_power(paudio_adapter, DISABLE, DISABLE);
    }

}

/**
 *  @brief Control the capless mode of the headphone.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_hpo_capless_mode (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_00h_t audio_codec_index_00h;
    audio_codec_index_01h_t audio_codec_index_01h;

    audio_codec_index_00h.w = hal_audio_si_read(paudio_adapter, 0x00);
    audio_codec_index_01h.w = hal_audio_si_read(paudio_adapter, 0x01);

    audio_codec_index_00h.b.hpo_cll = left_en;
    audio_codec_index_01h.b.hpo_clr = right_en;

    hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
    hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
}

/**
 *  @brief Control the depop of the headphone in the capless mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is no depop, 1 is depop.
 *  @param[in] right_en The right channel control: 0 is no depop, 1 is depop. This function is not supported.    ed.
 *
 *  @returns void
 */
void hal_audio_hpo_capless_depop (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_00h_t audio_codec_index_00h;
    audio_codec_index_01h_t audio_codec_index_01h;

    audio_codec_index_00h.w = hal_audio_si_read(paudio_adapter, 0x00);
    audio_codec_index_01h.w = hal_audio_si_read(paudio_adapter, 0x01);

    audio_codec_index_00h.b.hpo_clndpl = left_en;
    audio_codec_index_00h.b.hpo_clpdpl = left_en;

    audio_codec_index_00h.b.hpo_clndpr = right_en;
    audio_codec_index_01h.b.hpo_clpdpr = right_en;

    hal_audio_si_write(paudio_adapter, 0x00, audio_codec_index_00h.w);
    hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
}

/**
 *  @brief Control the amplifier of the headphone.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_hpo_amplifier (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_01h_t audio_codec_index_01h;

    audio_codec_index_01h.w = hal_audio_si_read(paudio_adapter, 0x01);
    audio_codec_index_01h.b.hpo_enal = left_en;
    audio_codec_index_01h.b.hpo_enar = right_en;
    hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
}

/**
 *  @brief Control the depop mode of the headphone.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_hpo_depop (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_01h_t audio_codec_index_01h;

    audio_codec_index_01h.w = hal_audio_si_read(paudio_adapter, 0x01);
    audio_codec_index_01h.b.hpo_endpl = left_en;
    audio_codec_index_01h.b.hpo_endpr = right_en;
    hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
}

/**
 *  @brief Control the headphone power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_hpo_power (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_01h_t audio_codec_index_01h;
    audio_codec_index_02h_t audio_codec_index_02h;

    audio_codec_index_01h.w = hal_audio_si_read(paudio_adapter, 0x01);
    audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);
    audio_codec_index_01h.b.hpo_l_pow = left_en;
    audio_codec_index_02h.b.hpo_r_pow = right_en;
    hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
    hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
}

/**
 *  @brief Control the depop of the headphone mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is no depop, 1 is depop.
 *  @param[in] right_en The right channel control: 0 is no depop, 1 is depop. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_hpo_mute_depop (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_01h_t audio_codec_index_01h;

    audio_codec_index_01h.w = hal_audio_si_read(paudio_adapter, 0x01);
    audio_codec_index_01h.b.hpo_mdpl = left_en;
    audio_codec_index_01h.b.hpo_mdpr = right_en;
    hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
}

/**
 *  @brief Control the depop of the headphone op.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is no depop, 1 is depop.
 *  @param[in] right_en The right channel control: 0 is no depop, 1 is depop. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_hpo_op_depop (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_01h_t audio_codec_index_01h;
    audio_codec_index_02h_t audio_codec_index_02h;

    audio_codec_index_01h.w = hal_audio_si_read(paudio_adapter, 0x01);
    audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);

    audio_codec_index_01h.b.hpo_opndpl = left_en;
    audio_codec_index_01h.b.hpo_oppdpl = left_en;

    audio_codec_index_01h.b.hpo_opndpr = right_en;
    audio_codec_index_02h.b.hpo_oppdpr = right_en;

    hal_audio_si_write(paudio_adapter, 0x01, audio_codec_index_01h.w);
    hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
}

/**
 *  @brief Control the headphone mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_mute_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_mute_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_hpo_mute (hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en, BOOL right_mute_en)
{
    audio_codec_index_02h_t audio_codec_index_02h;

    audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);

    if (left_mute_en == 1) {
        audio_codec_index_02h.b.hpo_ml = 0x3;
    } else {
        audio_codec_index_02h.b.hpo_ml = 0x2;
    }

    if (right_mute_en == 1) {
        audio_codec_index_02h.b.hpo_mr = 0x3;
    } else {
        audio_codec_index_02h.b.hpo_mr = 0x2;
    }

    hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
}

/**
 *  @brief Control the headphone differential mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_hpo_differential_mode (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_02h_t audio_codec_index_02h;

    audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);

    if (left_en == 1) {
        audio_codec_index_02h.b.hpo_sel = 0;
    } else {
        audio_codec_index_02h.b.hpo_sel = 1;
    }

    if (right_en == 1) {
        audio_codec_index_02h.b.hpo_ser = 0;
    } else {
        audio_codec_index_02h.b.hpo_ser = 1;
    }

    hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
}

/**
 *  @brief Control the mic bias.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] bias_en Enable control: 0 is disable, 1 is enable.
 *  @param[in] bias_voltage Select the bias voltage.
 *                      -00: 0.9AVDD. (default)
 *                      -01: 0.86AVDD.
 *                      -10: 0.75AVDD.
 *                      -11: reserved.
 *
 *  @returns void
 */
void hal_audio_mic_bias (hal_audio_adapter_t *paudio_adapter, BOOL bias_en, audio_bias_voltage_t bias_voltage)
{
    audio_codec_index_02h_t audio_codec_index_02h;

    audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);

    audio_codec_index_02h.b.micbias_pow = bias_en;
    audio_codec_index_02h.b.micbias_vset = bias_voltage;

    hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
}

/**
 *  @brief Control the mic differential mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_mic_differential_mode (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en)
{
    audio_codec_index_02h_t audio_codec_index_02h;

    audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);

    audio_codec_index_02h.b.micbst_endfl = left_en;
    audio_codec_index_02h.b.micbst_endfr = right_en;

    hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
}

/**
 *  @brief Control the mic mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_mute_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_mute_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_mic_mute (hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en, BOOL right_mute_en)
{
    audio_codec_index_03h_t audio_codec_index_03h;

    audio_codec_index_03h.w = hal_audio_si_read(paudio_adapter, 0x03);

    audio_codec_index_03h.b.micbst_mute_l &= 0xfffe;
    audio_codec_index_03h.b.micbst_mute_r &= 0xfffe;

    if (left_mute_en == 1) {
        audio_codec_index_03h.b.micbst_mute_l |= 0x01;
    }

    if (right_mute_en == 1) {
        audio_codec_index_03h.b.micbst_mute_r |= 0x01;
    }

    hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);
}

/**
 *  @brief Control the line-in mute.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_mute_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] right_mute_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *
 *  @returns void
 */
void hal_audio_line_in_mute (hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en, BOOL right_mute_en)
{
    audio_codec_index_03h_t audio_codec_index_03h;

    audio_codec_index_03h.w = hal_audio_si_read(paudio_adapter, 0x03);

    audio_codec_index_03h.b.micbst_mute_l &= 0xfffd;
    audio_codec_index_03h.b.micbst_mute_r &= 0xfffd;

    if (left_mute_en == 1) {
        audio_codec_index_03h.b.micbst_mute_l |= 0x02;
    }

    if (right_mute_en == 1) {
        audio_codec_index_03h.b.micbst_mute_r |= 0x02;
    }

    hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);
}

/**
 *  @brief Control the mic power.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] left_en The left channel control: 0 is disable, 1 is enable.
 *  @param[in] left_gain Select the left channel gain.
 *                      -00: 0dB. (default)
 *                      -01: 20dB.
 *                      -10: 30dB.
 *                      -11: 40dB.
 *  @param[in] right_en The right channel control: 0 is disable, 1 is enable. This function is not supported.
 *  @param[in] right_gain Select the right channel gain. This function is not supported.
 *                      -00: 0dB. (default)
 *                      -01: 20dB.
 *                      -10: 30dB.
 *                      -11: 40dB.
 *
 *  @returns void
 */
void hal_audio_mic_boost (hal_audio_adapter_t *paudio_adapter, BOOL left_en, audio_mic_gain_t left_gain, BOOL right_en, audio_mic_gain_t right_gain)
{
    audio_codec_index_03h_t audio_codec_index_03h;
    u16 micbst_pow_tp;

    audio_codec_index_03h.w = hal_audio_si_read(paudio_adapter, 0x03);

    micbst_pow_tp = (left_en << 1) & 0x02;
    micbst_pow_tp |=  (right_en & 0x01);
    audio_codec_index_03h.b.micbst_pow = micbst_pow_tp;

    audio_codec_index_03h.b.micbst_gsell = left_gain;
    audio_codec_index_03h.b.micbst_gselr = right_gain;

    hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);
}

/**
 *  @brief Control the vref voltage.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] vref_en Enable control: 0 is disable, 1 is enable.
 *  @param[in] vref_voltage Select the bias voltage.
 *                      -00: 0.52VDD.
 *                      -01: 0.51VDD.
 *                      -10: 0.50VDD. (default)
 *                      -11: 0.49VDD.
 *
 *  @returns void
 */
void hal_audio_vref (hal_audio_adapter_t *paudio_adapter, BOOL vref_en, audio_vref_voltage_t vref_voltage)
{
    audio_codec_index_02h_t audio_codec_index_02h;
    audio_codec_index_03h_t audio_codec_index_03h;

    audio_codec_index_02h.w = hal_audio_si_read(paudio_adapter, 0x02);
    audio_codec_index_03h.w = hal_audio_si_read(paudio_adapter, 0x03);

    audio_codec_index_02h.b.vref_pow = vref_en;
    audio_codec_index_03h.b.vref_vrefsel = vref_voltage;

    hal_audio_si_write(paudio_adapter, 0x02, audio_codec_index_02h.w);
    hal_audio_si_write(paudio_adapter, 0x03, audio_codec_index_03h.w);
}

//Audio Codec Data process

/**
 *  @brief The audio tx interrupt handler. It process all interrupt events.
 *
 *  @param[in]  data It should be the AUDIO adapter.
 *
 *  @returns void
 */
void hal_audio_dma_tx_irq_handle (void *data)
{
    hal_audio_adapter_t *paudio_adapter = (hal_audio_adapter_t *) data;

    if(paudio_adapter->tx_page_index == 0x00) {
        paudio_adapter->phal_gdma_adaptor_tx->ch_sar = paudio_adapter->tx_page1_adr;
        paudio_adapter->ptxdata_wk = (u8 *)paudio_adapter->tx_page0_adr;

        paudio_adapter->ptxdata_bf_wk = (u8 *)paudio_adapter->txbf_page0_adr;
        paudio_adapter->txbf_page_index = 0;

    } else {
        paudio_adapter->phal_gdma_adaptor_tx->ch_sar = paudio_adapter->tx_page0_adr;
        paudio_adapter->ptxdata_wk = (u8 *)paudio_adapter->tx_page1_adr;

        paudio_adapter->ptxdata_bf_wk = (u8 *)paudio_adapter->txbf_page1_adr;
        paudio_adapter->txbf_page_index = 1;
    }
    
    paudio_adapter->tx_err_cnt = paudio_adapter->sport0_base_addr->err_counter_b.tx_err_cnt;
    if (paudio_adapter->tx_err_cnt != 0x00) {
        paudio_adapter->sport0_base_addr->ctrl_2_b.clear_tx_err_cnt = 1;
        paudio_adapter->sport0_base_addr->ctrl_2_b.clear_tx_err_cnt = 0;
    }   

    hal_gdma_transfer_start(paudio_adapter->phal_gdma_adaptor_tx, MultiBlkDis);

    if (paudio_adapter->tx_data_empty == 0) {
        paudio_adapter->tx_data_empty = 1;
    } else {
        DBG_AUDIO_WARN("=== TX Warning !!, not process tx data \r\n");
    }

    paudio_adapter->audio_user_cb.audio_tx_cb(paudio_adapter->audio_user_cb.audio_tx_arg, paudio_adapter->ptxdata_wk);

    if(paudio_adapter->tx_page_index == 0x00) {
        paudio_adapter->tx_page_index = 1;
    } else {
        paudio_adapter->tx_page_index = 0;
    }

}

/**
 *  @brief Set the tx DMA parameter of the audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] word_len The audio word length.
 *  @param[in] page_size The data page size.
 *  @param[in] tx_buf The tx data buffer pointer.
 *
 *  @returns void
 */
void hal_audio_tx_dma_param(hal_audio_adapter_t *paudio_adapter, audio_word_len_t word_len, u32 page_size, u32 tx_buf)
{
    hal_gdma_adaptor_t *pgdma_adaptor = paudio_adapter->phal_gdma_adaptor_tx;
    u32 sport_tx_fifo_adr;

    sport_tx_fifo_adr = (u32)paudio_adapter->sport0_base_addr;

    pgdma_adaptor->gdma_ctl.tt_fc = TTFCMemToPeri;
    pgdma_adaptor->gdma_cfg.dest_per = GDMA_HANDSHAKE_CODEC_TX;
    pgdma_adaptor->ch_dar = sport_tx_fifo_adr;
    pgdma_adaptor->gdma_isr_type = (TransferType|ErrType);
    pgdma_adaptor->gdma_ctl.int_en = 1;
    pgdma_adaptor->gdma_ctl.dinc = NoChange;
    pgdma_adaptor->gdma_ctl.sinc = IncType;

    if (word_len != AUDIO_WL_8) {
        pgdma_adaptor->gdma_ctl.src_msize   = MsizeSixTeen;
        pgdma_adaptor->gdma_ctl.src_tr_width = TrWidthFourBytes;
        pgdma_adaptor->gdma_ctl.dest_msize  = MsizeSixTeen;
        pgdma_adaptor->gdma_ctl.dst_tr_width = TrWidthFourBytes;
        pgdma_adaptor->gdma_ctl.block_size = (page_size >> 2); // source unit, make irq
    } else {
        pgdma_adaptor->gdma_ctl.src_msize   = MsizeFour;
        pgdma_adaptor->gdma_ctl.src_tr_width = TrWidthFourBytes;
        pgdma_adaptor->gdma_ctl.dest_msize  = MsizeSixTeen;
        pgdma_adaptor->gdma_ctl.dst_tr_width = TrWidthOneByte;
        pgdma_adaptor->gdma_ctl.block_size = (page_size >> 2); // source unit, make irq
    }
    pgdma_adaptor->ch_sar= tx_buf;
    hal_gdma_handshake_init(pgdma_adaptor, GDMA_HANDSHAKE_CODEC_TX);
    hal_gdma_irq_reg(pgdma_adaptor, hal_audio_dma_tx_irq_handle, paudio_adapter);

}

/**
 *  @brief Initialize the tx DMA of the audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] word_len The audio word length.
 *  @param[in] page_size The data page size.
 *  @param[in] tx_buf The tx data buffer pointer.
 *
 *  @returns void
 */
void hal_audio_tx_dma_init (hal_audio_adapter_t *paudio_adapter, audio_word_len_t word_len, u32 page_size, u32 tx_buf)
{
    hal_gdma_adaptor_t *pgdma_adaptor = paudio_adapter->phal_gdma_adaptor_tx;
    hal_status_t ret;

    //GDMA TX Init
    ret = hal_gdma_chnl_alloc(pgdma_adaptor, MultiBlkDis);    // default no-multiple block support

    if (ret == HAL_OK) {
        hal_audio_tx_dma_param(paudio_adapter, word_len, page_size, tx_buf);
        hal_gdma_chnl_init(pgdma_adaptor);
    } else {
        DBG_AUDIO_WARN(" GDMA channel allocate failed(%d)\r\n", ret);
    }
}

/**
 *  @brief Start the audio tx DMA.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_audio_tx_dma_start (hal_audio_adapter_t *paudio_adapter)
{
    hal_gdma_adaptor_t *pgdma_adaptor = paudio_adapter->phal_gdma_adaptor_tx;

    //GDMA TX Start
    hal_gdma_transfer_start(pgdma_adaptor, MultiBlkDis);
}

/**
 *  @brief The audio rx interrupt handler. It process all interrupt events.
 *
 *  @param[in]  data It should be the AUDIO adapter.
 *
 *  @returns void
 */
void hal_audio_dma_rx_irq_handle (void *data)
{
    hal_audio_adapter_t *paudio_adapter = (hal_audio_adapter_t *) data;

    if(paudio_adapter->rx_page_index == 0x00) {
        paudio_adapter->phal_gdma_adaptor_rx->ch_dar = paudio_adapter->rx_page1_adr;
        paudio_adapter->prxdata_wk = (u8 *)paudio_adapter->rx_page0_adr;
    } else {
        paudio_adapter->phal_gdma_adaptor_rx->ch_dar = paudio_adapter->rx_page0_adr;
        paudio_adapter->prxdata_wk = (u8 *)paudio_adapter->rx_page1_adr;
    }

    paudio_adapter->rx_err_cnt = paudio_adapter->sport0_base_addr->err_counter_b.rx_err_cnt;        
    if (paudio_adapter->rx_err_cnt != 0x00) {
        paudio_adapter->sport0_base_addr->ctrl_2_b.clear_rx_err_cnt = 1;
        paudio_adapter->sport0_base_addr->ctrl_2_b.clear_rx_err_cnt = 0;
    }

    hal_gdma_transfer_start(paudio_adapter->phal_gdma_adaptor_rx, MultiBlkDis);

    if (paudio_adapter->rx_data_ready == 0) {
        paudio_adapter->rx_data_ready = 1;
    } else {
        DBG_AUDIO_WARN("=== RX Warning !!, not process rx data \r\n");
    }

    dcache_invalidate_by_addr((u32 *)paudio_adapter->prxdata_wk, (int32_t)(paudio_adapter->rx_page_size));
    //dcache_invalidate_by_addr_rtl8195bhp((u32*)paudio_adapter->rx_page0_adr, (int32_t)((paudio_adapter->rx_page_size) << 1));

    paudio_adapter->audio_user_cb.audio_rx_cb(paudio_adapter->audio_user_cb.audio_rx_arg, paudio_adapter->prxdata_wk);

    if(paudio_adapter->rx_page_index == 0x00) {
        paudio_adapter->rx_page_index = 1;
    } else {
        paudio_adapter->rx_page_index = 0;
    }

}

/**
 *  @brief Set the rx DMA parameter of the audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] word_len The audio word length.
 *  @param[in] page_size The data page size.
 *  @param[in] rx_buf The tx data buffer pointer.
 *
 *  @returns void
 */
void hal_audio_rx_dma_param(hal_audio_adapter_t *paudio_adapter, audio_word_len_t word_len, u32 page_size, u32 rx_buf)
{
    hal_gdma_adaptor_t *pgdma_adaptor = paudio_adapter->phal_gdma_adaptor_rx;
    u32 sport_rx_fifo_adr;

    sport_rx_fifo_adr = ((u32)paudio_adapter->sport0_base_addr + 0x10);

    pgdma_adaptor->gdma_ctl.tt_fc = TTFCPeriToMem;
    pgdma_adaptor->gdma_cfg.src_per = GDMA_HANDSHAKE_CODEC_RX;
    pgdma_adaptor->ch_dar = rx_buf;
    pgdma_adaptor->gdma_isr_type = (TransferType|ErrType);
    pgdma_adaptor->gdma_ctl.int_en = 1;
    pgdma_adaptor->gdma_ctl.dinc = IncType;
    pgdma_adaptor->gdma_ctl.sinc = NoChange;

    if (word_len != AUDIO_WL_8) {
        pgdma_adaptor->gdma_ctl.src_msize   = MsizeSixTeen;
        pgdma_adaptor->gdma_ctl.src_tr_width = TrWidthFourBytes;
        pgdma_adaptor->gdma_ctl.dest_msize  = MsizeSixTeen;
        pgdma_adaptor->gdma_ctl.dst_tr_width = TrWidthFourBytes;
        pgdma_adaptor->gdma_ctl.block_size =  (page_size >> 2); // source unit, make irq
    } else {
        pgdma_adaptor->gdma_ctl.src_msize   = MsizeSixTeen;
        pgdma_adaptor->gdma_ctl.src_tr_width = TrWidthOneByte;
        pgdma_adaptor->gdma_ctl.dest_msize  = MsizeFour;
        pgdma_adaptor->gdma_ctl.dst_tr_width = TrWidthFourBytes;
        pgdma_adaptor->gdma_ctl.block_size = page_size;         // source unit, make irq
    }
    pgdma_adaptor->ch_sar= sport_rx_fifo_adr;
    hal_gdma_handshake_init(pgdma_adaptor, GDMA_HANDSHAKE_CODEC_RX);
    hal_gdma_irq_reg(pgdma_adaptor, hal_audio_dma_rx_irq_handle, paudio_adapter);

}

/**
 *  @brief Initialize the rx DMA of the audio.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] word_len The audio word length.
 *  @param[in] page_size The data page size.
 *  @param[in] rx_buf The tx data buffer pointer.
 *
 *  @returns void
 */
void hal_audio_rx_dma_init (hal_audio_adapter_t *paudio_adapter, audio_word_len_t word_len, u32 page_size, u32 rx_buf)
{
    hal_gdma_adaptor_t *pgdma_adaptor = paudio_adapter->phal_gdma_adaptor_rx;
    hal_status_t ret;

    //GDMA RX Init
    ret = hal_gdma_chnl_alloc(pgdma_adaptor, MultiBlkDis);    // default no-multiple block support

    if (ret == HAL_OK) {
        hal_audio_rx_dma_param(paudio_adapter, word_len, page_size, rx_buf);
        hal_gdma_chnl_init(pgdma_adaptor);
    } else {
        DBG_AUDIO_WARN(" GDMA channel allocate failed(%d)\r\n", ret);
    }
}

/**
 *  @brief Start the audio rx DMA.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *
 *  @returns void
 */
void hal_audio_rx_dma_start (hal_audio_adapter_t *paudio_adapter)
{
    hal_gdma_adaptor_t *pgdma_adaptor = paudio_adapter->phal_gdma_adaptor_rx;

    //GDMA RX Start
    hal_gdma_transfer_start(pgdma_adaptor, MultiBlkDis);
}

/** @} */ /* End of group hs_hal_audio */

#endif

