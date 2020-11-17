/**************************************************************************//**
 * @file     hal_audio.h
 * @brief    The HAL API implementation for the Audio CODEC device.
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

#ifndef _HAL_AUDIO_H_
#define _HAL_AUDIO_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_audio AUDIO
 * @ingroup 8195bh_hal
 * @{
 * @brief The AUDIO HAL module of the HS platform.
 */

#include "cmsis.h"
#include "rtl8195bhp_si_type.h"
#include "rtl8195bhp_sport_type.h"
#include "rtl8195bhp_audio_codec_type.h"

/**
  \brief Audio Sample Rate.
*/
enum  audio_sample_rate_e {
    AUDIO_SR_8KHZ       =   0x07,
    AUDIO_SR_16KHZ      =   0x05,
	AUDIO_SR_32KHZ	    = 	0x03,
    AUDIO_SR_44p1KHZ    =   0x08,
	AUDIO_SR_48KHZ	    =	0x00,
    AUDIO_SR_88p2KHZ	=	0x09,
    AUDIO_SR_96KHZ	    =	0x01
};
typedef uint8_t audio_sample_rate_t;

/**
  \brief Sport WS Swap.
*/
enum  sport_ws_swap_e {
    SPORT_LEFT_PHASE    =   0x0,
    SPORT_RIGHT_PHASE   =   0x1
};
typedef uint8_t sport_ws_swap_t;

/**
  \brief Audio Format.
*/
enum  audio_format_e {
    AUDIO_FORMAT_I2S          =   0x0,
    AUDIO_FORMAT_LEFT_JUST    =   0x1,
    AUDIO_FORMAT_PCM_MODE_A   =   0x2,
    AUDIO_FORMAT_PCM_MODE_B   =   0x3
};
typedef uint8_t audio_format_t;

/**
  \brief Audio Channel number.
*/
enum  audio_ch_num_e {
    AUDIO_CH_STEREO   =   0x0,
    AUDIO_CH_MONO     =   0x1
};
typedef uint8_t audio_ch_num_t;

/**
  \brief Audio Word Length.
*/
enum  audio_word_len_e {
	AUDIO_WL_16 = 0x0,
    AUDIO_WL_24 = 0x2,
    AUDIO_WL_8  = 0x3
};
typedef uint8_t audio_word_len_t;

/**
  \brief Audio Channel Select.
*/
enum  audio_sel_ch_e {
	AUDIO_L_R = 0x0,
    AUDIO_R_L = 0x1,
    AUDIO_L_L = 0x2,
    AUDIO_R_R = 0x3
};
typedef uint8_t audio_sel_ch_t;

/**
  \brief Audio MIC Mixer Select.
*/
enum  audio_mic_mixer_e {
	AUDIO_A_MIC_M = 0x0,
    AUDIO_D_MIC_M = 0x1
};
typedef uint8_t audio_mic_mixer_t;

/**
  \brief Audio HPF Coefficient.
*/
enum  audio_hpf_coef_e {
	AUDIO_HPF_FS_8K_16K     = 0x0,  /*!< fc = (20~2000Hz), or (40~4000Hz) */
    AUDIO_HPF_FS_32K        = 0x1,  /*!< fc = (40~3278Hz) */
	AUDIO_HPF_FS_48K_44p1K  = 0x2,  /*!< fc = (30~2168Hz) or (28~1992Hz) */
    AUDIO_HPF_FS_96K_88p2K  = 0x3   /*!< fc = (30~2034Hz) or (28~1869Hz) */
};
typedef uint8_t audio_hpf_coef_t;

/**
  \brief Audio DMIC Input Clock Select.
*/
enum  audio_dmic_input_clk_e {
	AUDIO_DMIC_5M       = 0x0,
    AUDIO_DMIC_2p5M     = 0x1,  /*!< default */
    AUDIO_DMIC_1p25M    = 0x2,
    AUDIO_DMIC_625K     = 0x3,
    AUDIO_DMIC_312p5K   = 0x4
};
typedef uint8_t audio_dmic_input_clk_t;

/**
  \brief Audio Zero Detection Function Select.
*/
enum  audio_zdet_e {
	AUDIO_IMME_CHAN             = 0x0,
    AUDIO_DETE_AND_IMME_CHAN    = 0x1,
    AUDIO_DETE_AND_INC_DEC_CHAN = 0x2,  /*!< default */
    AUDIO_UN_CHAN               = 0x3
};
typedef uint8_t audio_zdet_t;

/**
  \brief Audio Zero Detection Time Out Select for ADC.
*/
enum  audio_adc_zdet_tout_e {
	AUDIO_ADC_16384_SAMPLES = 0x0,
    AUDIO_ADC_32768_SAMPLES = 0x1,  /*!< default */
    AUDIO_ADC_65536_SAMPLES = 0x2,
    AUDIO_ADC_64_SAMPLES    = 0x3
};
typedef uint8_t audio_adc_zdet_tout_t;

/**
  \brief Audio Zero Detection Time Out Select for DAC.
*/
enum  audio_dac_zdet_tout_e {
	AUDIO_DAC_16384_SAMPLES = 0x0,  /*!< default */
    AUDIO_DAC_32768_SAMPLES = 0x1,
    AUDIO_DAC_65536_SAMPLES = 0x2,
    AUDIO_DAC_256_SAMPLES   = 0x3
};
typedef uint8_t audio_dac_zdet_tout_t;

/**
  \brief Audio  Zero Detection Time Out Select for ALC.
*/
enum  audio_alc_zdet_tout_e {
	AUDIO_ALC_12000_SAMPLES = 0x0,
    AUDIO_ALC_24000_SAMPLES = 0x1,  /*!< default */
    AUDIO_ALC_36000_SAMPLES = 0x2,
    AUDIO_ALC_48000_SAMPLES = 0x3
};
typedef uint8_t audio_alc_zdet_tout_t;

/**
  \brief Audio Full Scale Threshold for ALC.
*/
enum  audio_alc_full_scale_e {
	AUDIO_ALC_FULL_n00DB = 0x0, /*!< default */
    AUDIO_ALC_FULL_n0p5DB = 0x1,
    AUDIO_ALC_FULL_n1p0DB = 0x2,
    AUDIO_ALC_FULL_n1p5DB = 0x3
};
typedef uint8_t audio_alc_full_scale_t;

/**
  \brief Audio Bias Voltage Select.
*/
enum  audio_bias_voltage_e {
	AUDIO_BIAS_0p9_AVDD     = 0x0,  /*!< default */
    AUDIO_BIAS_0p86_AVDD    = 0x1,
    AUDIO_BIAS_0p75_AVDD    = 0x2
};
typedef uint8_t audio_bias_voltage_t;

/**
  \brief Audio Mic Gain Select.
*/
enum  audio_mic_gain_e {
	AUDIO_MIC_0DB     = 0x0,    /*!< default */
    AUDIO_MIC_20DB    = 0x1,
    AUDIO_MIC_30DB    = 0x2,
    AUDIO_MIC_40DB    = 0x3
};
typedef uint8_t audio_mic_gain_t;

/**
  \brief Audio Vref Voltage Select.
*/
enum  audio_vref_voltage_e {
	AUDIO_VREF_0p52_VDD = 0x0,
    AUDIO_VREF_0p51_VDD = 0x1,
    AUDIO_VREF_0p50_VDD = 0x2,  /*!< default */
    AUDIO_VREF_0p49_VDD = 0x3
};
typedef uint8_t audio_vref_voltage_t;

/**
  \brief Audio DMIC Latch Select.
*/
enum  audio_dmic_latch_e {
	AUDIO_DIMC_RISING = 0x0,
    AUDIO_DIMC_FALLING = 0x1
};
typedef uint8_t audio_dmic_latch_t;

/**
  \brief Audio DMIC Boost Select.
*/
enum  audio_dmic_gain_e {
	AUDIO_DMIC_BOOST_0DB = 0x0,
    AUDIO_DMIC_BOOST_12DB = 0x1,
	AUDIO_DMIC_BOOST_24DB = 0x2,
    AUDIO_DMIC_BOOST_36DB = 0x3
};
typedef uint8_t audio_dmic_gain_t;

/**
  \brief Audio AMIC Compensate Gain Select.
*/
enum  audio_amic_gain_e {
	AUDIO_AMIC_GAIN_0DB = 0x0,
    AUDIO_AMIC_GAIN_1DB = 0x1,
	AUDIO_AMIC_GAIN_2DB = 0x2,
    AUDIO_AMIC_GAIN_3DB = 0x3
};
typedef uint8_t audio_amic_gain_t;

/**
  \brief Audio Low Pass Filter frequency Select for SRC.
*/
enum  audio_src_freq_e {
	AUDIO_SRC_31p04KHZ = 0x0,
    AUDIO_SRC_46p92KHZ = 0x1,
	AUDIO_SRC_63p06KHZ = 0x2,
    AUDIO_SRC_79p54KHZ = 0x3
};
typedef uint8_t audio_src_freq_t;

/**
  \brief Audio Sidetone Source Select.
*/
enum  audio_sidetone_source_e {
	AUDIO_ST_ADC_L = 0x0,
    AUDIO_ST_ADC_R = 0x1,
    AUDIO_ST_DMIC_L = 0x2,
    AUDIO_ST_DMIC_R = 0x3
};
typedef uint8_t audio_sidetone_source_t;

/**
  \brief Audio Sidetone HPF Cut Off Frequence.
*/
enum  audio_sidetone_hpf_e {
	AUDIO_ST_120HZ = 0x0,
    AUDIO_ST_239HZ = 0x1,
    AUDIO_ST_358HZ = 0x2,
    AUDIO_ST_477HZ = 0x3,
    AUDIO_ST_597HZ = 0x4,
    AUDIO_ST_716HZ = 0x5,
    AUDIO_ST_835HZ = 0x6,
    AUDIO_ST_955HZ = 0x7
};
typedef uint8_t audio_sidetone_hpf_t;

/**
  \brief Audio Sidetone Volume Select .
*/
enum  audio_sidetone_vol_e {
	AUDIO_ST_n46p5DB = 0x0,
    AUDIO_ST_n45DB = 0x1,
    AUDIO_ST_n43p5DB = 0x2,
    AUDIO_ST_n42DB = 0x3,
    AUDIO_ST_n40p5DB = 0x4,
    AUDIO_ST_n39DB = 0x5,
    AUDIO_ST_n37p5DB = 0x6,
    AUDIO_ST_n36DB = 0x7,

	AUDIO_ST_n34p5DB = 0x8,
    AUDIO_ST_n33DB = 0x9,
    AUDIO_ST_n31p5DB = 0xA,
    AUDIO_ST_n30DB = 0xB,
    AUDIO_ST_n28p5DB = 0xC,
    AUDIO_ST_n27DB = 0xD,
    AUDIO_ST_n25p5DB = 0xE,
    AUDIO_ST_n24DB = 0xF,

    AUDIO_ST_n22p5DB = 0x10,
    AUDIO_ST_n21DB = 0x11,
    AUDIO_ST_n19p5DB = 0x12,
    AUDIO_ST_n18DB = 0x13,
    AUDIO_ST_n16p5DB = 0x14,
    AUDIO_ST_n15DB = 0x15,
    AUDIO_ST_n13p5DB = 0x16,
    AUDIO_ST_n12DB = 0x17,

	AUDIO_ST_n10p5DB = 0x18,
    AUDIO_ST_n9DB = 0x19,
    AUDIO_ST_n7p5DB = 0x1A,
    AUDIO_ST_n60DB = 0x1B,
    AUDIO_ST_n4p5DB = 0x1C,
    AUDIO_ST_n3DB = 0x1D,
    AUDIO_ST_n1p5DB = 0x1E,
    AUDIO_ST_00DB = 0x1F
};
typedef uint8_t audio_sidetone_vol_t;

/**
  \brief Audio Sidetone Boost Select .
*/
enum  audio_sidetone_boost_e {
	AUDIO_ST_BOOST_0DB = 0x0,
    AUDIO_ST_BOOST_12DB = 0x1
};
typedef uint8_t audio_sidetone_boost_t;

/**
  \brief Audio Dither Select.
*/
enum  audio_dac_dither_e {
	AUDIO_DITHER_DISABLE = 0x0,
    AUDIO_DITHER_LSB = 0x1,
    AUDIO_DITHER_LSB_ADD1 = 0x2,    /*!< default */
    AUDIO_DITHER_LSB_ADD2 = 0x3
};
typedef uint8_t audio_dac_dither_t;

/**
  \brief Audio Silence Detection According Wordlength or Level.
*/
enum  audio_silence_detect_e {
    AUDIO_SILE_LEVEL = 0x0,
	AUDIO_SILE_WORDLENGTH = 0x1    /*!< default */
};
typedef uint8_t audio_silence_detect_t;

/**
  \brief Audio Silence Word length.
*/
enum  audio_silence_wordlength_e {
	AUDIO_SILE_16BIT = 0x0,
    AUDIO_SILE_20BIT = 0x1,
    AUDIO_SILE_24BIT = 0x2
};
typedef uint8_t audio_silence_wordlength_t;

/**
  \brief Audio Silence Level.
*/
enum  audio_silence_Level_e {
	AUDIO_SILE_n78DB = 0x0,
    AUDIO_SILE_n84DB = 0x1,
    AUDIO_SILE_n90DB = 0x2,
    AUDIO_SILE_n102DB = 0x3,
    AUDIO_SILE_n108DB = 0x4,
    AUDIO_SILE_n114DB = 0x5,
    AUDIO_SILE_n126DB = 0x6,
    AUDIO_SILE_n132DB = 0x7
};
typedef uint8_t audio_silence_Level_t;

/**
  \brief Audio Silence Debounce.
*/
enum  audio_silence_debounce_e {
    AUDIO_SILE_3840_SAMPLES = 0x0,
    AUDIO_SILE_7680_SAMPLES = 0x1,
    AUDIO_SILE_15360_SAMPLES = 0x2,
    AUDIO_SILE_30720_SAMPLES = 0x3, /*!< default */
    AUDIO_SILE_61440_SAMPLES = 0x4,
    AUDIO_SILE_122880_SAMPLES = 0x5,
    AUDIO_SILE_245760_SAMPLES = 0x6
};
typedef uint8_t audio_silence_debounce_t;

/**
  \brief Audio ALC Sample Rate.
*/
enum  audio_alc_sample_rate_e {
    AUDIO_ALC_SR_48KHZ      =   0x01,
    AUDIO_ALC_SR_96KHZ      =   0x02,
	AUDIO_ALC_SR_192KHZ	    = 	0x03,
    AUDIO_ALC_SR_44p1KHZ    =   0x04,
	AUDIO_ALC_SR_88p2KHZ    =	0x05,
    AUDIO_ALC_SR_176p4KHZ	=	0x06
};
typedef uint8_t audio_alc_sample_rate_t;

/**
  \brief Audio ALC Low Pass Filter Coefficient.
*/
enum  audio_alc_lpf_coef_e {
    AUDIO_COFE_DIV_8     =   0x00,
    AUDIO_COFE_DIV_16    =   0x01,
	AUDIO_COFE_DIV_32    =   0x02,
    AUDIO_COFE_DIV_64    =   0x03,
	AUDIO_COFE_DIV_128   =   0x04,
    AUDIO_COFE_DIV_256   =   0x05,
    AUDIO_COFE_DIV_1024  =   0x06,
    AUDIO_COFE_DIV_2048  =   0x07
};
typedef uint8_t audio_alc_lpf_coef_t;

/**
  \brief Audio ALC Limit Ratio.
*/
enum  audio_alc_limit_ratio_e {
    AUDIO_LIM_DIV_4     =   0x00,
    AUDIO_LIM_DIV_8     =   0x01,
	AUDIO_LIM_DIV_16    =   0x02,
    AUDIO_LIM_DIV_32    =   0x03,
	AUDIO_LIM_DIV_64    =   0x04,
    AUDIO_LIM_DIV_128   =   0x05,
    AUDIO_LIM_DIV_256   =   0x06,
    AUDIO_HARD_LIMIT    =   0x07    /*!< default */
};
typedef uint8_t audio_alc_limit_ratio_t;

/**
  \brief Audio ALC Compression Ratio for DRC.
*/
enum  audio_alc_drc_ratio_e {
    AUDIO_DRC_DIV_1 =   0x00,
    AUDIO_DRC_DIV_2 =   0x01, /*!< default */
	AUDIO_DRC_DIV_4 =   0x02,
    AUDIO_DRC_DIV_8 =   0x03
};
typedef uint8_t audio_alc_drc_ratio_t;

/**
  \brief Audio ALC Hold Sample Time for DRC.
*/
enum  audi_alc_drc_hold_e {
    AUDIO_HOLD_240_SAMPLES = 0x0,
    AUDIO_HOLD_19200_SAMPLES = 0x1, /*!< default */
    AUDIO_HOLD_57600_SAMPLES = 0x2,
    AUDIO_HOLD_115200_SAMPLES = 0x3
};
typedef uint8_t audio_alc_drc_hold_t;

/**
  \brief Audio ALC Expansion Ratio for Noise Gate.
*/
enum  audio_alc_noise_gate_ratio_e {
    AUDIO_NOISE_MUL_1 = 0x00,
    AUDIO_NOISE_MUL_2 = 0x01, /*!< default */
	AUDIO_NOISE_MUL_4 = 0x02,
    AUDIO_NOISE_MUL_8 = 0x03
};
typedef uint8_t audio_alc_noise_gate_ratio_t;

/**
  \brief Audio ALC Detection Method for Zero Data.
*/
enum  audio_alc_zero_detect_e {
    AUDIO_ZERO_DETECT_RMS = 0x00,
    AUDIO_ZERO_DETECT_AMP = 0x01 /*!< default */
};
typedef uint8_t audio_alc_zero_detect_t;

/**
  \brief Audio ALC Recovery.
*/
enum  audio_alc_recovery_mode_e {
    AUDIO_FORCE_SLOW = 0x00, /*!< default */
    AUDIO_FORCE_FAST = 0x01
};
typedef uint8_t audio_alc_recovery_mode_t;

/**
  \brief Audio Output Mode.
*/
enum  audio_output_mode_e {
    AUDIO_OUTPUT_DISABLE = 0,
    AUDIO_OUTPUT_SINGLE_EDNED = 1,
    AUDIO_OUTPUT_DIFFERENTIAL = 2,
    AUDIO_OUTPUT_CAPLESS = 3
};
typedef uint8_t audio_output_mode_t;

/**
  \brief Audio Input Mode.
*/
enum  audio_input_mode_e {
    AUDIO_INPUT_DISABLE = 0,
    AUDIO_LINE_IN_MODE = 1,
    AUDIO_MIC_DIFFERENTIAL = 2,
    AUDIO_MIC_SINGLE_EDNED = 3
};
typedef uint8_t audio_input_mode_t;

/**
  \brief Audio Codec Power.
*/
enum  audio_codec_power_e {
    AUDIO_POWER_1p8V = 0,
    AUDIO_POWER_2p8V = 1
};
typedef uint8_t audio_codec_power_t;

/**
  \brief  Audio call back function for the interrupt.
*/
typedef struct hal_audio_user_cb_s{
    VOID (*audio_tx_cb)(u32 arg, u8 *pbuf);
    u32 audio_tx_arg;

    VOID (*audio_rx_cb)(u32 arg, u8 *pbuf);
    u32 audio_rx_arg;
} hal_audio_user_cb_t,*phal_audio_user_cb_t;

typedef struct hal_audio_adapter_s {
    SI_Type *si_base_addr;                      /*!< The SI common register base address */
    SPORT0_Type *sport0_base_addr;              /*!< The SPORT0 common register base address */

    hal_gdma_adaptor_t *phal_gdma_adaptor_tx;   /*!< The TX GDMA adapter */
    hal_gdma_adaptor_t *phal_gdma_adaptor_rx;   /*!< The RX GDMA adapter */

    volatile uint8_t tx_err_cnt;              /*!< TX error counter    */
    volatile uint8_t rx_err_cnt;              /*!< RX error counter    */    

    audio_word_len_t word_len;  /*!< Audio word length */

    u8 tx_data_empty;       /*!< Audio TX data empty flag */
    u8 rx_data_ready;       /*!< Audio RX data ready flag */

    u8 tx_page_index;       /*!< Working TX page index */
    u32 tx_page0_adr;       /*!< TX page0 address */
    u32 tx_page1_adr;       /*!< TX page1 address */
    u32 tx_page_size;       /*!< TX page size */
    u8 *ptxdata_wk;         /*!< Working TX page address */

    u8 rx_page_index;       /*!< Working RX page index */
    u32 rx_page0_adr;       /*!< RX page0 address */
    u32 rx_page1_adr;       /*!< RX page1 address */
    u32 rx_page_size;       /*!< RX page size */
    u8 *prxdata_wk;         /*!< Working RX page address */

    void (*dcache_invalidate_by_addr)(uint32_t *addr, int32_t dsize);   /*! callback function to do the D-cache invalidate  */
    void (*dcache_clean_by_addr) (uint32_t *addr, int32_t dsize);       /*! callback function to do the D-cache clean  */

    hal_audio_user_cb_t audio_user_cb; /*!< User callback function */

    u8 txbf_page_index;     /*!< debug, Working TX page index */
    u32 txbf_page0_adr;     /*!< debug, TX page0 address */
    u32 txbf_page1_adr;     /*!< debug, TX page1 address */
    u8 *ptxdata_bf_wk;      /*!< debug, Working TX page address */

} hal_audio_adapter_t, *phal_audio_adapter_t;

/**
 *  @brief  Control whether the data appear in "right" or "left" phase of WS clock.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sport_ws_swap Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_audio_sport_ws_swap (hal_audio_adapter_t *paudio_adapter, sport_ws_swap_t sport_ws_swap)
{
    paudio_adapter->sport0_base_addr->ctrl_1_b.sp_wclk_inverse = sport_ws_swap;
}

/**
 *  @brief  Conrtol the interface format.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_format Select the interface format.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_audio_sport_format (hal_audio_adapter_t *paudio_adapter, audio_format_t audio_format)
{
    paudio_adapter->sport0_base_addr->ctrl_1_b.sp_data_format_sel = audio_format;
}

/**
 *  @brief  Set the channel nunber.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_ch_num The channel nunber.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_audio_sport_ch_num (hal_audio_adapter_t *paudio_adapter, audio_ch_num_t audio_ch_num)
{
    paudio_adapter->sport0_base_addr->ctrl_1_b.sp_en_i2s_mono = audio_ch_num;
}

/**
 *  @brief  Set the word length.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] audio_word_len The word length.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_audio_sport_length (hal_audio_adapter_t *paudio_adapter, audio_word_len_t audio_word_len)
{
    paudio_adapter->sport0_base_addr->ctrl_1_b.sp_data_len_sel = audio_word_len;
}

/**
 *  @brief  Invert sport SCK.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] sck_inv_en Enable control.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_audio_sport_sck_inv (hal_audio_adapter_t *paudio_adapter, BOOL sck_inv_en)
{
    paudio_adapter->sport0_base_addr->ctrl_1_b.sp_inv_i2s_sclk = sck_inv_en;
}

/**
 *  @brief Control the tx data format of the sport.
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
__STATIC_INLINE
void hal_audio_sport_tx_ch (hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch)
{
    paudio_adapter->sport0_base_addr->ctrl_1_b.sp_sel_i2s_tx_ch = audio_sel_ch;
}

/**
 *  @brief Control the rx data format of the sport.
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
__STATIC_INLINE
void hal_audio_sport_rx_ch (hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch)
{
    paudio_adapter->sport0_base_addr->ctrl_1_b.sp_sel_i2s_rx_ch = audio_sel_ch;
}

/**
 *  @brief Set the tx lsb control.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lsb_first_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_audio_sport_tx_lsb_first (hal_audio_adapter_t *paudio_adapter, BOOL lsb_first_en)
{
    paudio_adapter->sport0_base_addr->ctrl_1_b.tx_lsb_first = lsb_first_en;
}

/**
 *  @brief Set the rx lsb control.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] lsb_first_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_audio_sport_rx_lsb_first (hal_audio_adapter_t *paudio_adapter, BOOL lsb_first_en)
{
    paudio_adapter->sport0_base_addr->ctrl_1_b.rx_lsb_first = lsb_first_en;
}

/**
 *  @brief Set the sport loopback mode.
 *
 *  @param[in] paudio_adapter The AUDIO adapter.
 *  @param[in] loopback_en  Enable control: 0 is disable, 1 is enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_audio_sport_loopback (hal_audio_adapter_t *paudio_adapter, BOOL loopback_en)
{
    paudio_adapter->sport0_base_addr->ctrl_1_b.sp_loopback = loopback_en;
}


/** @} */ /* End of group hs_hal_audio */

void hal_audio_init (hal_audio_adapter_t *paudio_adapter, audio_codec_power_t audio_codec_power);
void hal_audio_deinit (hal_audio_adapter_t *paudio_adapter);

void hal_audio_dma_tx_irq_handle (void *data);
void hal_audio_tx_dma_param(hal_audio_adapter_t *paudio_adapter, audio_word_len_t word_len, u32 page_size, u32 tx_buf);
void hal_audio_tx_dma_init (hal_audio_adapter_t *paudio_adapter, audio_word_len_t word_len, u32 page_size, u32 tx_buf);
void hal_audio_tx_dma_start (hal_audio_adapter_t *paudio_adapter);

void hal_audio_dma_rx_irq_handle (void *data);
void hal_audio_rx_dma_param(hal_audio_adapter_t *paudio_adapter, audio_word_len_t word_len, u32 page_size, u32 rx_buf);
void hal_audio_rx_dma_init (hal_audio_adapter_t *paudio_adapter, audio_word_len_t word_len, u32 page_size, u32 rx_buf);
void hal_audio_rx_dma_start (hal_audio_adapter_t *paudio_adapter);
void hal_audio_micbias_count (hal_audio_adapter_t *paudio_adapter, u32 fun_en);


//Audio SI interface Part
void hal_audio_si_init (hal_audio_adapter_t *paudio_adapter, BOOL en);
u16 hal_audio_si_read (hal_audio_adapter_t *paudio_adapter, u8 address);
HAL_Status hal_audio_si_write (hal_audio_adapter_t *paudio_adapter, u8 address, u16 data);

//Audio Sport interface Part
void hal_audio_sport_rate (hal_audio_adapter_t *paudio_adapter, audio_sample_rate_t audio_sample_rate);
void hal_audio_sport_tx_data_swap (hal_audio_adapter_t *paudio_adapter, BOOL lr_swap_en, BOOL byte_swap_en);
void hal_audio_sport_rx_data_swap (hal_audio_adapter_t *paudio_adapter, BOOL lr_swap_en, BOOL byte_swap_en);
void hal_audio_sport_tx_start_ctrl (hal_audio_adapter_t *paudio_adapter, BOOL en);
u32 hal_audio_get_sport_tx_start_status (hal_audio_adapter_t *paudio_adapter);
void hal_audio_sport_rx_start_ctrl (hal_audio_adapter_t *paudio_adapter, BOOL en);
u32 hal_audio_get_sport_rx_start_status (hal_audio_adapter_t *paudio_adapter);
void hal_audio_sport_trx_start_ctrl (hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_sport_clean_error (hal_audio_adapter_t *paudio_adapter);
void hal_audio_sport_rst (hal_audio_adapter_t *paudio_adapter);


//=== Audio Codec Digital Part ===

// Codec Audio Interface
void hal_audio_rate (hal_audio_adapter_t *paudio_adapter, audio_sample_rate_t audio_sample_rate);
void hal_audio_format (hal_audio_adapter_t *paudio_adapter, audio_format_t audio_format);
void hal_audio_ch_num (hal_audio_adapter_t *paudio_adapter, audio_ch_num_t audio_ch_num);
void hal_audio_length (hal_audio_adapter_t *paudio_adapter, audio_word_len_t audio_word_len);
void hal_audio_sck_inv (hal_audio_adapter_t *paudio_adapter, BOOL sck_inv_en);
void hal_audio_loopback (hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
void hal_audio_tx_ch (hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch);
void hal_audio_rx_ch (hal_audio_adapter_t *paudio_adapter, audio_sel_ch_t audio_sel_ch);

// Others
void hal_audio_digital_rst (hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_daad_loopback (hal_audio_adapter_t *paudio_adapter, BOOL loopback_en);
void hal_audio_gen_clk (hal_audio_adapter_t *paudio_adapter, BOOL gen_clk_en);
void hal_audio_asrc (hal_audio_adapter_t *paudio_adapter, BOOL asrc_en);

// Mixer
void hal_audio_dac_mixer (hal_audio_adapter_t *paudio_adapter, BOOL dac_l_mute_en, BOOL dac_r_mute_en);
void hal_audio_adc_amic_mixer (hal_audio_adapter_t *paudio_adapter, BOOL amic_l_mute_en, BOOL amic_r_mute_en);
void hal_audio_adc_dmic_mixer (hal_audio_adapter_t *paudio_adapter, BOOL dmic_l_mute_en, BOOL dmic_r_mute_en);
void hal_audio_alc_mixer (hal_audio_adapter_t *paudio_adapter, BOOL alc_l_mixer_en, BOOL alc_r_mixer_en);
void hal_audio_sidetone_mixer (hal_audio_adapter_t *paudio_adapter, BOOL sidetone_l_mute_en, BOOL sidetone_r_mute_en);

// Function Clock
void hal_audio_dac_clk (hal_audio_adapter_t *paudio_adapter, BOOL dac_l_clk_en, BOOL dac_r_clk_en);
void hal_audio_adc_clk (hal_audio_adapter_t *paudio_adapter, BOOL adc_l_clk_en, BOOL adc_r_clk_en);
void hal_audio_dmic_clk (hal_audio_adapter_t *paudio_adapter, BOOL dimc_l_clk_en, BOOL dimc_r_clk_en);
void hal_audio_sidetone_clk (hal_audio_adapter_t *paudio_adapter, BOOL sidetone_clk_en);

// DMIC
void hal_audio_dmic_input_clk (hal_audio_adapter_t *paudio_adapter, audio_dmic_input_clk_t dmic_input_clk);
void hal_audio_dmic_latch (hal_audio_adapter_t *paudio_adapter, audio_dmic_latch_t dmic_l_latch, audio_dmic_latch_t dmic_r_latch);
void hal_audio_dmic_l_gain (hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain);
void hal_audio_dmic_r_gain (hal_audio_adapter_t *paudio_adapter, audio_dmic_gain_t dmic_gain);
void hal_audio_dmic_l_src (hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
void hal_audio_dmic_r_src (hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);

// AMIC
void hal_audio_amic_l_gain (hal_audio_adapter_t *paudio_adapter, audio_amic_gain_t amic_gain);
void hal_audio_amic_r_gain (hal_audio_adapter_t *paudio_adapter, audio_amic_gain_t amic_gain);
void hal_audio_amic_l_src (hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);
void hal_audio_amic_r_src (hal_audio_adapter_t *paudio_adapter, BOOL lp_1st_en, BOOL lp_2st_en, audio_src_freq_t src_freq);

// ADC High Pass Filter for Filtering DC
void hal_audio_adc_l_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_adc_r_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en);

// ADC High Pass Filter for Wind Noise Reduction
void hal_audio_adc_l_2nd_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_coef_t audio_hpf_coef, u8 coef_num);
void hal_audio_adc_r_2nd_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en, audio_hpf_coef_t audio_hpf_coef, u8 coef_num);

// ADC Digital Volume Control &  zero detection function select
void hal_audio_adc_l_dvol (hal_audio_adapter_t *paudio_adapter, u8 step);
void hal_audio_adc_l_dmute (hal_audio_adapter_t *paudio_adapter, BOOL mute_en);

void hal_audio_adc_r_dvol (hal_audio_adapter_t *paudio_adapter, u8 step);
void hal_audio_adc_r_dmute (hal_audio_adapter_t *paudio_adapter, BOOL mute_en);

void hal_audio_adc_l_zdet (hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout);
void hal_audio_adc_r_zdet (hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout);

// ADC Silence Detection
void hal_audio_adc_l_silence (hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_detect_t detect_sel, audio_silence_debounce_t debounce_time);
void hal_audio_adc_l_silence_parameter (hal_audio_adapter_t *paudio_adapter, audio_silence_wordlength_t wordlength, audio_silence_Level_t level);
u8 hal_audio_adc_l_silence_result (hal_audio_adapter_t *paudio_adapter);
u8 hal_audio_adc_l_silence_status (hal_audio_adapter_t *paudio_adapter);

void hal_audio_adc_r_silence (hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_detect_t detect_sel, audio_silence_debounce_t debounce_time);
void hal_audio_adc_r_silence_parameter (hal_audio_adapter_t *paudio_adapter, audio_silence_wordlength_t wordlength, audio_silence_Level_t level);
u8 hal_audio_adc_r_silence_result (hal_audio_adapter_t *paudio_adapter);
u8 hal_audio_adc_r_silence_status (hal_audio_adapter_t *paudio_adapter);

// DAC Dither Select
void hal_audio_dac_dither (hal_audio_adapter_t *paudio_adapter, audio_dac_dither_t dac_l_dither, audio_dac_dither_t dac_r_dither);

// DAC High Pass Filter
void hal_audio_dac_l_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_dac_r_hpf (hal_audio_adapter_t *paudio_adapter, BOOL en);

// DAC Digital Volume Control &  zero detection function select
void hal_audio_dac_l_dvol (hal_audio_adapter_t *paudio_adapter, u8 step);
void hal_audio_dac_l_dmute (hal_audio_adapter_t *paudio_adapter, BOOL mute_en);

void hal_audio_dac_r_dvol (hal_audio_adapter_t *paudio_adapter, u8 step);
void hal_audio_dac_r_dmute (hal_audio_adapter_t *paudio_adapter, BOOL mute_en);

void hal_audio_dac_l_zdet (hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout);
void hal_audio_dac_r_zdet (hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_adc_zdet_tout_t adc_zdet_tout);

// DAC Silence Detection
void hal_audio_dac_l_silence (hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_detect_t detect_sel, audio_silence_debounce_t debounce_time);
void hal_audio_dac_l_silence_parameter (hal_audio_adapter_t *paudio_adapter, audio_silence_wordlength_t wordlength, audio_silence_Level_t level);
u8 hal_audio_dac_l_silence_result (hal_audio_adapter_t *paudio_adapter);
u8 hal_audio_dac_l_silence_status (hal_audio_adapter_t *paudio_adapter);

void hal_audio_dac_r_silence (hal_audio_adapter_t *paudio_adapter, BOOL silence_en, audio_silence_detect_t detect_sel, audio_silence_debounce_t debounce_time);
void hal_audio_dac_r_silence_parameter (hal_audio_adapter_t *paudio_adapter, audio_silence_wordlength_t wordlength, audio_silence_Level_t level);
u8 hal_audio_dac_r_silence_result (hal_audio_adapter_t *paudio_adapter);
u8 hal_audio_dac_r_silence_status (hal_audio_adapter_t *paudio_adapter);

// Sidetone
void hal_audio_sidetone_source (hal_audio_adapter_t *paudio_adapter, audio_sidetone_source_t source_sel);
void hal_audio_sidetone_hpf (hal_audio_adapter_t *paudio_adapter, BOOL hpf_en, audio_sidetone_hpf_t sidetone_hpf);
void hal_audio_sidetone_vol (hal_audio_adapter_t *paudio_adapter, audio_sidetone_vol_t sidetone_vol, audio_sidetone_boost_t sidetone_boost);

// ALC function
void hal_audio_alc_ctrl (hal_audio_adapter_t *paudio_adapter, BOOL alc_en, BOOL alc_stereo_en, audio_alc_sample_rate_t sample_rate);
void hal_audio_alc_boost (hal_audio_adapter_t *paudio_adapter, u8 front_boost_step, u8 back_boost_l_step, u8 back_boost_r_step);
void hal_audio_alc_firm_gain(hal_audio_adapter_t *paudio_adapter, BOOL firm_en, u8 firm_gain_step);
void hal_audio_alc_min_gain(hal_audio_adapter_t *paudio_adapter, BOOL min_gain_en, u8 min_gain_step);
void hal_audio_alc_lpf_coef (hal_audio_adapter_t *paudio_adapter, audio_alc_lpf_coef_t lpf_coef);
void hal_audio_alc_limiter_ctrl (hal_audio_adapter_t *paudio_adapter, audio_alc_limit_ratio_t limit_ratio, u32 threshold);
void hal_audio_alc_zdet (hal_audio_adapter_t *paudio_adapter, audio_zdet_t zdet, audio_alc_zdet_tout_t alc_zdet_tout);
void hal_audio_alc_full_scale (hal_audio_adapter_t *paudio_adapter, audio_alc_full_scale_t alc_full_scale);

void hal_audio_alc_drc_en (hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_alc_drc_attack_thr1 (hal_audio_adapter_t *paudio_adapter, u8 threshold_step, u8 range_step);
void hal_audio_alc_drc_attack_thr2 (hal_audio_adapter_t *paudio_adapter, u8 threshold_step, u8 range_step);
void hal_audio_alc_drc_attack_rate (hal_audio_adapter_t *paudio_adapter, BOOL speed_rate_en, u8 normal_rate_time, u8 speed_rate_time);
void hal_audio_alc_drc_attack_ratio1 (hal_audio_adapter_t *paudio_adapter, audio_alc_drc_ratio_t drc_ratio1);
void hal_audio_alc_drc_attack_ratio2 (hal_audio_adapter_t *paudio_adapter, audio_alc_drc_ratio_t drc_ratio2);

void hal_audio_alc_attack_hold (hal_audio_adapter_t *paudio_adapter, BOOL hold_en, audio_alc_drc_hold_t recover_time);
void hal_audio_alc_attack_hold_to_release (hal_audio_adapter_t *paudio_adapter, BOOL release_en, audio_alc_drc_hold_t release_time);

void hal_audio_alc_noise_gate_en (hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_alc_noise_gate_attack_thr (hal_audio_adapter_t *paudio_adapter, u8 threshold_step, u8 range_step);
void hal_audio_alc_noise_gate_attack_rate (hal_audio_adapter_t *paudio_adapter, u8 rate_time);
void hal_audio_alc_noise_gate_attack_drop (hal_audio_adapter_t *paudio_adapter, BOOL en, u8 drop_gain_step);
void hal_audio_alc_noise_gate_attack_hold (hal_audio_adapter_t *paudio_adapter, BOOL hold_gate_en);
void hal_audio_alc_noise_gate_expand_ratio (hal_audio_adapter_t *paudio_adapter, audio_alc_noise_gate_ratio_t expand_ratio);

void hal_audio_alc_zero_data_en (hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_alc_zero_data_thr (hal_audio_adapter_t *paudio_adapter, audio_alc_zero_detect_t detect_sel, u8 rms_threshold_step, u8 amp_threshold_step);
void hal_audio_alc_zero_data_time (hal_audio_adapter_t *paudio_adapter, u8 check_time);

void hal_audio_alc_recovery_ctrl (hal_audio_adapter_t *paudio_adapter, audio_alc_recovery_mode_t recovery_mode, u8 slow_recovery_time, u8 fast_recovery_time);
void hal_audio_alc_recovery_special_mode1 (hal_audio_adapter_t *paudio_adapter, BOOL en, u8 upper_bound, u8 lower_bound);
void hal_audio_alc_recovery_special_mode2 (hal_audio_adapter_t *paudio_adapter, BOOL en);


//=== Audio Codec Analog Part ===
void hal_audio_ad_da_clk_power (hal_audio_adapter_t *paudio_adapter, BOOL en);
void hal_audio_dac_power (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);
void hal_audio_adc_power (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);
void hal_audio_output_power (hal_audio_adapter_t *paudio_adapter, audio_output_mode_t output_mode);
void hal_audio_input_power (hal_audio_adapter_t *paudio_adapter, audio_input_mode_t input_mode);

void hal_audio_hpo_capless_mode (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);
void hal_audio_hpo_capless_depop (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);
void hal_audio_hpo_amplifier (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);
void hal_audio_hpo_depop (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);
void hal_audio_hpo_power (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);
void hal_audio_hpo_mute_depop (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);
void hal_audio_hpo_op_depop (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);
void hal_audio_hpo_mute (hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en, BOOL right_mute_en);
void hal_audio_hpo_differential_mode (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);

void hal_audio_mic_bias (hal_audio_adapter_t *paudio_adapter, BOOL bias_en, audio_bias_voltage_t bias_voltage);
void hal_audio_mic_differential_mode (hal_audio_adapter_t *paudio_adapter, BOOL left_en, BOOL right_en);
void hal_audio_mic_mute (hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en, BOOL right_mute_en);
void hal_audio_line_in_mute (hal_audio_adapter_t *paudio_adapter, BOOL left_mute_en, BOOL right_mute_en);
void hal_audio_mic_boost (hal_audio_adapter_t *paudio_adapter, BOOL left_en, audio_mic_gain_t left_gain, BOOL right_en, audio_mic_gain_t right_gain);

void hal_audio_vref (hal_audio_adapter_t *paudio_adapter, BOOL vref_en, audio_vref_voltage_t vref_voltage);



#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_AUDIO_H_"

