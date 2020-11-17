/**************************************************************************//**
 * @file      rtl8195bhp_audio_codec_type.h
 * @brief
 * @version   V1.00
 * @date      2017-11-7 16:11:26
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

#ifndef _RTL8195BHP_AUDIO_CODEC_TYPE_H_
#define _RTL8195BHP_AUDIO_CODEC_TYPE_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/// @cond DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_AUDIO_REG_TYPE

/**
 * @addtogroup hs_hal_audio_reg AUDIO_CODEC Registers.
 * @ingroup hs_hal_audio
 * @{
 */

/**
  \brief Union type to access audio_codec_index_00h (@ 0x00000000).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000000) w                                                  */

  struct {
    __IOM uint16_t dac_addack_pow : 1;        /*!< [0..0] AD/DA clock power down control (0: power down, 1: power
                                                   on)                                                                       */
    __IOM uint16_t dac_ckxen  : 1;            /*!< [1..1] DAC chopper clock enable control (0: disable, 1: enable)           */
    __IOM uint16_t dac_ckxsel : 1;            /*!< [2..2] DAC chopper clock selection (0: ckx2/4, 1: ckx2/8)                 */
    __IOM uint16_t dac_l_pow  : 1;            /*!< [3..3] DAC left channel power down control (0: power down, 1:
                                                   power on)                                                                 */
    __IOM uint16_t dac_r_pow  : 1;            /*!< [4..4] DAC right channel power down control (0: power down,
                                                   1: power on)                                                              */
    __IOM uint16_t dpramp_csel : 2;           /*!< [6..5] Depop C size selection (00: 1x, 01: 2x, 10: 3x, 11: 4x)            */
    __IOM uint16_t dpramp_enramp : 1;         /*!< [7..7] DPRAMP enable ramp control (0: disable, 1: enable)                 */
    __IOM uint16_t dpramp_pow : 1;            /*!< [8..8] DPRAMP power down control (0: power down, 1: power on)             */
    __IOM uint16_t dtsdm_ckxen : 1;           /*!< [9..9] ADC integrater 1 OP chopper enable: 0 : disable 1 : enable
                                                   (default)                                                                 */
    __IOM uint16_t dtsdm_pow_l : 1;           /*!< [10..10] Left channel ADC power on control: 0: power down 1:
                                                   power on                                                                  */
    __IOM uint16_t dtsdm_pow_r : 1;           /*!< [11..11] Right channel ADC power on control: 0: power down 1:
                                                   power on                                                                  */
    __IOM uint16_t hpo_cll    : 1;            /*!< [12..12] Headphone left channel capless mode control (0: non-capless,
                                                   1: capless)                                                               */
    __IOM uint16_t hpo_clndpl : 1;            /*!< [13..13] Headphone left channel capless negative depop mode
                                                   control (0: no depop, 1: depop)                                           */
    __IOM uint16_t hpo_clndpr : 1;            /*!< [14..14] Headphone right channel capless negative depop mode
                                                   control (0: no depop, 1: depop)                                           */
    __IOM uint16_t hpo_clpdpl : 1;            /*!< [15..15] Headphone left channel capless positive depop mode
                                                   control (0: no depop, 1: depop)                                           */
  } b;                                        /*!< bit fields for audio_codec_index_00h */
} audio_codec_index_00h_t, *paudio_codec_index_00h_t;

/**
  \brief Union type to access audio_codec_index_01h (@ 0x00000002).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000002) w                                                  */

  struct {
    __IOM uint16_t hpo_clpdpr : 1;            /*!< [0..0] Headphone right channel capless positive depop mode control
                                                   (0: no depop, 1: depop)                                                   */
    __IOM uint16_t hpo_clr    : 1;            /*!< [1..1] Headphone right channel capless mode control (0: non-capless,
                                                   1: capless)                                                               */
    __IOM uint16_t hpo_dprsell : 2;           /*!< [3..2] Headphone left channel depop R size selection (00: 1x,
                                                   01: 2x, 10: 3x, 11: 4x)                                                   */
    __IOM uint16_t hpo_dprselr : 2;           /*!< [5..4] Headphone right channel depop R size selection (00: 1x,
                                                   01: 2x, 10: 3x, 11: 4x)                                                   */
    __IOM uint16_t hpo_enal   : 1;            /*!< [6..6] Headphone left channel enable amplifier control (0: disable,
                                                   1: enable)                                                                */
    __IOM uint16_t hpo_enar   : 1;            /*!< [7..7] Headphone right channel enable amplifier control (0:
                                                   disable, 1: enable)                                                       */
    __IOM uint16_t hpo_endpl  : 1;            /*!< [8..8] Headphone left channel enable depop control (0: disable,
                                                   1: enable)                                                                */
    __IOM uint16_t hpo_endpr  : 1;            /*!< [9..9] Headphone right channel enable depop control (0: disable,
                                                   1: enable)                                                                */
    __IOM uint16_t hpo_l_pow  : 1;            /*!< [10..10] Headphone left channel power down control (0: power
                                                   down, 1: power on)                                                        */
    __IOM uint16_t hpo_mdpl   : 1;            /*!< [11..11] Headphone left channel mute depop mode control (0:
                                                   no depop, 1: depop)                                                       */
    __IOM uint16_t hpo_mdpr   : 1;            /*!< [12..12] Headphone right channel mute depop mode control (0:
                                                   no depop, 1: depop)                                                       */
    __IOM uint16_t hpo_opndpl : 1;            /*!< [13..13] Headphone left channel op negative depop mode control
                                                   (0: no depop, 1: depop)                                                   */
    __IOM uint16_t hpo_opndpr : 1;            /*!< [14..14] Headphone right channel op negative depop mode control
                                                   (0: no depop, 1: depop)                                                   */
    __IOM uint16_t hpo_oppdpl : 1;            /*!< [15..15] Headphone left channel op positive depop mode control
                                                   (0: no depop, 1: depop)                                                   */
  } b;                                        /*!< bit fields for audio_codec_index_01h */
} audio_codec_index_01h_t, *paudio_codec_index_01h_t;

/**
  \brief Union type to access audio_codec_index_02h (@ 0x00000004).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000004) w                                                  */

  struct {
    __IOM uint16_t hpo_ml     : 2;            /*!< [1..0] Headphone left channel mute control (0: un-mute, 1: mute),
                                                   <0>: DAC, <1>: Analog in                                                  */
    __IOM uint16_t hpo_mr     : 2;            /*!< [3..2] Headphone right channel mute control (0: un-mute, 1:
                                                   mute), <0>: DAC, <1>: Analog in                                           */
    __IOM uint16_t hpo_oppdpr : 1;            /*!< [4..4] Headphone right channel op positive depop mode control
                                                   (0: no depop, 1: depop)                                                   */
    __IOM uint16_t hpo_r_pow  : 1;            /*!< [5..5] Headphone right channel power down control (0: power
                                                   down, 1: power on)                                                        */
    __IOM uint16_t hpo_sel    : 1;            /*!< [6..6] Headphone left channel single-end mode control (0: differential,
                                                   1: single-end)                                                            */
    __IOM uint16_t hpo_ser    : 1;            /*!< [7..7] Headphone right channel single-end mode control (0: differential,
                                                   1: single-end)                                                            */
    __IOM uint16_t mbias_pow  : 1;            /*!< [8..8] MBIAS power control 0: power down 1: power on                      */
    __IOM uint16_t micbias_enchx : 1;         /*!< [9..9] MICBIAS enable chopper clock 0:disable 1:enable                    */
    __IOM uint16_t micbias_pow : 1;           /*!< [10..10] MICBIAS power control 0:power down 1:power on                    */
    __IOM uint16_t micbias_vset : 2;          /*!< [12..11] MICBIAS select output voltage level 00:0.9*AVDD 01:0.86*AVDD
                                                   (for AVDD=1.8v) 10:0.75*AVDD 11:reserved                                  */
    __IOM uint16_t micbst_endfl : 1;          /*!< [13..13] MICBST left channel enable differential 0:single to
                                                   differential 1:differential to differential                               */
    __IOM uint16_t micbst_endfr : 1;          /*!< [14..14] MICBST right channel enable differential 0:single to
                                                   differential 1:differential to differential                               */
    __IOM uint16_t vref_pow   : 1;            /*!< [15..15] VREF power control 0: power down 1: power on                     */
  } b;                                        /*!< bit fields for audio_codec_index_02h */
} audio_codec_index_02h_t, *paudio_codec_index_02h_t;

/**
  \brief Union type to access audio_codec_index_03h (@ 0x00000006).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000006) w                                                  */

  struct {
    __IOM uint16_t micbst_gsell : 2;          /*!< [1..0] MICBST left channel gain select 00: 0dB 01:20dB 10:30dB
                                                   11:40dB                                                                   */
    __IOM uint16_t micbst_gselr : 2;          /*!< [3..2] MICBST right channel gain select 00: 0dB 01:20dB 10:30dB
                                                   11:40dB                                                                   */
    __IOM uint16_t micbst_mute_l : 2;         /*!< [5..4] MICBST mute control mute<0>: mic in mute<1>: line in
                                                   0:unmute 1:mute                                                           */
    __IOM uint16_t micbst_mute_r : 2;         /*!< [7..6] MICBST mute control mute<0>: mic in mute<1>: line in
                                                   0:unmute 1:mute                                                           */
    __IOM uint16_t micbst_pow : 2;            /*!< [9..8] MICBST power control pow<0>: right channel pow<1>: left
                                                   channel 0:power down 1:power on                                           */
    __IOM uint16_t vref_vrefsel : 2;          /*!< [11..10] VREF voltage selection 00: 0.52*VDD 01: 0.51*VDD 10:
                                                   0.50*VDD (default) 11: 0.49*VDD                                           */
    __IOM uint16_t hpo_gsell  : 2;            /*!< [13..12] invalid                                                          */
    __IOM uint16_t hpo_gselr  : 2;            /*!< [15..14] invalid                                                          */
  } b;                                        /*!< bit fields for audio_codec_index_03h */
} audio_codec_index_03h_t, *paudio_codec_index_03h_t;

/**
  \brief Union type to access audio_codec_index_04h (@ 0x00000008).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000008) w                                                  */

  struct {
    __IOM uint16_t debug_bus_sel : 2;         /*!< [1..0] no use                                                             */

    __IM  uint16_t            : 6;
    __IOM uint16_t micbias_count : 4;         /*!< [11..8] invalid                                                           */
    __IOM uint16_t micbias_ocsel : 2;         /*!< [13..12] invalid                                                          */
    __IOM uint16_t micbias_powshdt : 1;       /*!< [14..14] invalid                                                          */
  } b;                                        /*!< bit fields for audio_codec_index_04h */
} audio_codec_index_04h_t, *paudio_codec_index_04h_t;

/**
  \brief Union type to access audio_codec_index_0ch (@ 0x00000018).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000018) w                                                  */

  struct {
    __IOM uint16_t sel_bb_ck_depop : 2;       /*!< [1..0] 2'b00: ck_depop=40MHz/1024, 2'b01: ck_depop=40MHz/2048
                                                   2'b10: ck_depop=40MHz/4096, 2'b11: ck_depop=40MHz/8192                    */
    __IM  uint16_t micbias_oc : 1;            /*!< [2..2] invalid                                                            */
    __IOM uint16_t bb_ck_depop_en : 1;        /*!< [3..3] 1'b1: enable ck_depop                                              */
    __IOM uint16_t ckx_micbias_en : 1;        /*!< [4..4] 1'b1: enable ckx_micbias to be 312.5KHz                            */
  } b;                                        /*!< bit fields for audio_codec_index_0ch */
} audio_codec_index_0ch_t, *paudio_codec_index_0ch_t;

/**
  \brief Union type to access audio_codec_index_0fh (@ 0x0000001E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000001E) w                                                  */

  struct {
    __IOM uint16_t sidetone_hpf_en : 1;       /*!< [0..0] sidetone processing enable control 1'b1 : enable sidetone
                                                   HPF processing 1'b0 : disable sidetone HPF processing                     */
    __IOM uint16_t sidetone_hpf_fc_sel : 3;   /*!< [3..1] sidetone HPF cut-off frequency select (-6dB) 3'b000 :
                                                   fc = 120Hz, 3'b001 : fc = 239Hz 3'b010 : fc = 358Hz, 3'b011
                                                   : fc = 477Hz 3'b100 : fc = 597Hz, 3'b101 : fc = 716Hz 3'b110
                                                   : fc = 835Hz, 3'b111 : fc = 955Hz                                         */
    __IOM uint16_t sidetone_vol_sel : 5;      /*!< [8..4] sidetone volume select 5'h00 : -46.5dB, 5'h01 : -45.0dB
                                                   5'h02 : -43.5dB, 5'h03 : -42.0dB 5'h04 : -40.5dB, 5'h05
                                                   : -39.0dB 5'h06 : -37.5dB, 5'h07 : -36.0dB 5'h08 : -34.5dB,
                                                   5'h09 : -33.0dB 5'h0a : -31.5dB, 5'h0b : -30.0dB 5'h0c
                                                   : -28.5dB, 5'h0d : -27.0dB 5'h0e : -25.5dB, 5'h0f : -24.0dB
                                                   5'h10 : -22.5dB, 5'h11 : -21.0dB 5'h12 : -19.5dB, 5'h13
                                                   : -18.0dB 5'h14 : -16.5dB, 5'h15 : -15.0dB 5'h16 : -13.5dB,
                                                   5'h17 : -12.0dB 5'h18 : -10.5dB, 5'h19 : -9.0dB 5'h1a :
                                                   -7.5dB, 5'h1b : -6.0dB 5'h1c : -4.5dB                                     */
    __IOM uint16_t sidetone_boost_sel : 1;    /*!< [9..9] sidetone boost select 1'b1 : +12dB 1'b0 : + 0dB                    */
    __IOM uint16_t i2s_adc_comp : 2;          /*!< [11..10] 2'b00: OFF; 2'b01: u law; 2'b10: A law                           */
    __IOM uint16_t i2s_dac_comp : 2;          /*!< [13..12] 2'b00: OFF; 2'b01: u law; 2'b10: A law                           */
  } b;                                        /*!< bit fields for audio_codec_index_0fh */
} audio_codec_index_0fh_t, *paudio_codec_index_0fh_t;

/**
  \brief Union type to access audio_codec_index_10h (@ 0x00000020).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000020) w                                                  */

  struct {
    __IOM uint16_t en_i2s_mono : 1;           /*!< [0..0] 1'b1: mono; 1'b0: stereo                                           */
    __IOM uint16_t i2s_en_pcm_n_mode : 1;     /*!< [1..1] 3'b000: I2S; 3'b010: Left Justified; 3'b100: PCM mode
                                                   A; 3'b110: PCM mode B; 3'b101: PCM mode A-N; 3'b111: PCM
                                                   mode B-N                                                                  */
    __IOM uint16_t i2s_data_format_sel : 2;   /*!< [3..2] 3'b000: I2S; 3'b010: Left Justified; 3'b100: PCM mode
                                                   A; 3'b110: PCM mode B; 3'b101: PCM mode A-N; 3'b111: PCM
                                                   mode B-N                                                                  */
    __IOM uint16_t i2s_data_len_sel : 2;      /*!< [5..4] 2'b00: 16 bits; 2'b10: 24 bits; 2'b11: 8 bits;                     */
    __IOM uint16_t inv_i2s_sclk : 1;          /*!< [6..6] 1'b1: I2S/PCM bit clock is inverted                                */
    __IOM uint16_t i2s_rst_n_reg : 1;         /*!< [7..7] 1'b1: rst_n to audio digital IP is de-asserted; 1'b0:
                                                   rst_n to audio digital IP is asserted                                     */
    __IOM uint16_t sel_i2s_rx_ch : 2;         /*!< [9..8] 2'b00: L/R; 2'b01: R/L; 2'b10: L/L; 2'b11: R/R @ ADC
                                                   path                                                                      */
    __IOM uint16_t sel_i2s_tx_ch : 2;         /*!< [11..10] 2'b00: L/R; 2'b01: R/L; 2'b10: L/L; 2'b11: R/R @ DAC
                                                   path                                                                      */
    __IOM uint16_t stereo_i2s_self_lpbk_en : 1;/*!< [12..12] 1'b1: internal loopback mode is enabled                         */
  } b;                                        /*!< bit fields for audio_codec_index_10h */
} audio_codec_index_10h_t, *paudio_codec_index_10h_t;

/**
  \brief Union type to access audio_codec_index_11h (@ 0x00000022).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000022) w                                                  */

  struct {
    __IOM uint16_t adc_l_dmic_ri_fa_sel : 1;  /*!< [0..0] DMIC Data Latching Control: 0: rising latch 1: falling
                                                   latch                                                                     */
    __IM  uint16_t            : 2;
    __IOM uint16_t adc_l_dmic_lpf2nd_en : 1;  /*!< [3..3] DMIC SRC 2nd LPF control: 0: disable 1: enable                     */
    __IOM uint16_t adc_l_dmic_lpf1st_en : 1;  /*!< [4..4] DMIC SRC 1st LPF control: 0: disable 1: enable                     */
    __IOM uint16_t adc_l_dmic_lpf1st_fc_sel : 2;/*!< [6..5] DMIC SRC 1st LPF fc: 00b:31.04khz, 01b:46.92khz, 10b:63.06khz,
                                                   11b:79.45khz                                                              */
    __IM  uint16_t            : 1;
    __IOM uint16_t adc_l_ad_lpf2nd_en : 1;    /*!< [8..8] ADC SRC 2nd LPF control: 0: disable 1: enable                      */
    __IOM uint16_t adc_l_ad_lpf1st_en : 1;    /*!< [9..9] ADC SRC 1st LPF control: 0: disable 1: enable                      */
    __IOM uint16_t adc_l_ad_lpf1st_fc_sel : 2;/*!< [11..10] ADC SRC 1st LPF fc: 00b:31.04khz, 01b:46.92khz, 10b:63.06khz,
                                                   11b:79.45khz                                                              */
    __IOM uint16_t adc_l_ad_mix_mute : 1;     /*!< [12..12] analog ADC input path mute control Left Channel: 0:
                                                   Un-Mute 1: Mute                                                           */
    __IOM uint16_t adc_l_dmic_mix_mute : 1;   /*!< [13..13] DMIC input path mute control Left Channel: 0: Un-Mute
                                                   1: Mute                                                                   */
    __IOM uint16_t adc_l_ad_dchpf_en : 1;     /*!< [14..14] High pass filter enable control (filter DC): 0: disable
                                                   1: enable                                                                 */
  } b;                                        /*!< bit fields for audio_codec_index_11h */
} audio_codec_index_11h_t, *paudio_codec_index_11h_t;

/**
  \brief Union type to access audio_codec_index_12h (@ 0x00000024).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000024) w                                                  */

  struct {
    __IOM uint16_t adc_l_ad_comp_gain : 2;    /*!< [1..0] ADC compensate gain, 0: 0db, 1: 1db, 2: 2db, , 3: 3db,             */
    __IOM uint16_t adc_l_adj_hpf_2nd_en : 1;  /*!< [2..2] Adaptive 2nd High pass filter enable control: 0: disable
                                                   1: enable                                                                 */
    __IOM uint16_t adc_l_adj_hpf_coef_sel : 3;/*!< [5..3] coefficient coarse select, fc range (num==0 ~ num==63):
                                                   3'b000 : fs = 8k, or 16k corresponding fc = (20~2000Hz),
                                                   or (40~4000Hz) 3'b001 : fs = 32k corresponding fc = (40~3278Hz)
                                                   3'b010 : fs = 48k or 44.1k corresponding fc = (30~2168Hz)
                                                   or (28~1992Hz) 3'b011 : fs = 96k or 88.2k corresponding
                                                   fc = (30~2034Hz) or (28~1869Hz)                                           */
    __IOM uint16_t adc_l_dmic_boost_gain : 2; /*!< [7..6] DMIC boost gain control: 00'b : 0dB 01'b: 12dB 10'b :
                                                   24dB 11'b: 36dB                                                           */
    __IOM uint16_t adc_l_ad_mute : 1;         /*!< [8..8] Digital mute from ADC left cheannel digital mixer, 0:un-mute,
                                                   1:mute                                                                    */
    __IOM uint16_t adc_l_ad_zdet_func : 2;    /*!< [10..9] ADC zero detection function select: 2'b00 : immediate
                                                   change 2'b01 : zero detection & immediate change 2'b10
                                                   : zero detection & increase/decrease change 2'b11 : unchange              */
    __IOM uint16_t adc_l_ad_zdet_tout : 2;    /*!< [12..11] ADC zero detection time out select: 2'b00 : 1024*16
                                                   samples 2'b01 : 1024*32 samples 2'b10 : 1024*64 samples
                                                   2'b11 : 64 samples                                                        */
  } b;                                        /*!< bit fields for audio_codec_index_12h */
} audio_codec_index_12h_t, *paudio_codec_index_12h_t;

/**
  \brief Union type to access audio_codec_index_13h (@ 0x00000026).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000026) w                                                  */

  struct {
    __IOM uint16_t adc_l_adj_hpf_coef_num : 6;/*!< [5..0] coefficient fine select (0~63)                                     */
    __IOM uint16_t adc_l_ad_gain : 7;         /*!< [12..6] ADC digital volume -17.625dB~+30dB in 0.375 dB step
                                                   (7'h00:-17.625dB, xxx, 7'h2f:0dB, 7'h30:0.375dB, xxx ,
                                                   7'h7f:30dB)                                                               */
  } b;                                        /*!< bit fields for audio_codec_index_13h */
} audio_codec_index_13h_t, *paudio_codec_index_13h_t;

/**
  \brief Union type to access audio_codec_index_14h (@ 0x00000028).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000028) w                                                  */

  struct {
    __IOM uint16_t adc_r_dmic_ri_fa_sel : 1;  /*!< [0..0] DMIC Data Latching Control: 0: rising latch 1: falling
                                                   latch                                                                     */
    __IM  uint16_t            : 2;
    __IOM uint16_t adc_r_dmic_lpf2nd_en : 1;  /*!< [3..3] DMIC SRC 2nd LPF control: 0: disable 1: enable                     */
    __IOM uint16_t adc_r_dmic_lpf1st_en : 1;  /*!< [4..4] DMIC SRC 1st LPF control: 0: disable 1: enable                     */
    __IOM uint16_t adc_r_dmic_lpf1st_fc_sel : 2;/*!< [6..5] DMIC SRC 1st LPF fc: 00b:31.04khz, 01b:46.92khz, 10b:63.06khz,
                                                   11b:79.45khz                                                              */
    __IM  uint16_t            : 1;
    __IOM uint16_t adc_r_ad_lpf2nd_en : 1;    /*!< [8..8] ADC SRC 2nd LPF control: 0: disable 1: enable                      */
    __IOM uint16_t adc_r_ad_lpf1st_en : 1;    /*!< [9..9] ADC SRC 1st LPF control: 0: disable 1: enable                      */
    __IOM uint16_t adc_r_ad_lpf1st_fc_sel : 2;/*!< [11..10] ADC SRC 1st LPF fc: 00b:31.04khz, 01b:46.92khz, 10b:63.06khz,
                                                   11b:79.45khz                                                              */
    __IOM uint16_t adc_r_ad_mix_mute : 1;     /*!< [12..12] analog ADC input path mute control Left Channel: 0:
                                                   Un-Mute 1: Mute                                                           */
    __IOM uint16_t adc_r_dmic_mix_mute : 1;   /*!< [13..13] DMIC input path mute control Left Channel: 0: Un-Mute
                                                   1: Mute                                                                   */
    __IOM uint16_t adc_r_ad_dchpf_en : 1;     /*!< [14..14] High pass filter enable control (filter DC): 0: disable
                                                   1: enable                                                                 */
  } b;                                        /*!< bit fields for audio_codec_index_14h */
} audio_codec_index_14h_t, *paudio_codec_index_14h_t;

/**
  \brief Union type to access audio_codec_index_15h (@ 0x0000002A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000002A) w                                                  */

  struct {
    __IOM uint16_t adc_r_ad_comp_gain : 2;    /*!< [1..0] ADC compensate gain, 0: 0db, 1: 1db, 2: 2db, , 3: 3db,             */
    __IOM uint16_t adc_r_adj_hpf_2nd_en : 1;  /*!< [2..2] Adaptive 2nd High pass filter enable control: 0: disable
                                                   1: enable                                                                 */
    __IOM uint16_t adc_r_adj_hpf_coef_sel : 3;/*!< [5..3] coefficient coarse select, fc range (num==0 ~ num==63):
                                                   3'b000 : fs = 8k, or 16k corresponding fc = (20~2000Hz),
                                                   or (40~4000Hz) 3'b001 : fs = 32k corresponding fc = (40~3278Hz)
                                                   3'b010 : fs = 48k or 44.1k corresponding fc = (30~2168Hz)
                                                   or (28~1992Hz) 3'b011 : fs = 96k or 88.2k corresponding
                                                   fc = (30~2034Hz) or (28~1869Hz)                                           */
    __IOM uint16_t adc_r_dmic_boost_gain : 2; /*!< [7..6] DMIC boost gain control: 00'b : 0dB 01'b: 12dB 10'b :
                                                   24dB 11'b: 36dB                                                           */
    __IOM uint16_t adc_r_ad_mute : 1;         /*!< [8..8] Digital mute from ADC right cheannel digital mixer, 0:un-mute,
                                                   1:mute                                                                    */
    __IOM uint16_t adc_r_ad_zdet_func : 2;    /*!< [10..9] ADC zero detection function select: 2'b00 : immediate
                                                   change 2'b01 : zero detection & immediate change 2'b10
                                                   : zero detection & increase/decrease change 2'b11 : unchange              */
    __IOM uint16_t adc_r_ad_zdet_tout : 2;    /*!< [12..11] ADC zero detection time out select: 2'b00 : 1024*16
                                                   samples 2'b01 : 1024*32 samples 2'b10 : 1024*64 samples
                                                   2'b11 : 64 samples                                                        */
  } b;                                        /*!< bit fields for audio_codec_index_15h */
} audio_codec_index_15h_t, *paudio_codec_index_15h_t;

/**
  \brief Union type to access audio_codec_index_16h (@ 0x0000002C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000002C) w                                                  */

  struct {
    __IOM uint16_t adc_r_adj_hpf_coef_num : 6;/*!< [5..0] coefficient fine select (0~63)                                     */
    __IOM uint16_t adc_r_ad_gain : 7;         /*!< [12..6] ADC digital volume -17.625dB~+30dB in 0.375 dB step
                                                   (7'h00:-17.625dB, xxx, 7'h2f:0dB, 7'h30:0.375dB, xxx ,
                                                   7'h7f:30dB)                                                               */
  } b;                                        /*!< bit fields for audio_codec_index_16h */
} audio_codec_index_16h_t, *paudio_codec_index_16h_t;

/**
  \brief Union type to access audio_codec_index_17h (@ 0x0000002E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000002E) w                                                  */

  struct {
    __IOM uint16_t dac_sample_rate : 4;       /*!< [3..0] set DAC sample rate: 4'h0: 48K, 4'h1: 96K, 4'h2: reserved,
                                                   4'h3: 32K 4'h4: reserved, 4'h5: 16K, 4'h6: reserved, 4'h7:
                                                   8K 4'h8: 44.1K, 4'h9: 88.2K, 4'hA~4'hF:reserved                           */
    __IOM uint16_t adc_sample_rate : 4;       /*!< [7..4] set ADC sample rate: 4'h0: 48K, 4'h1: 96K, 4'h2: reserved,
                                                   4'h3: 32K 4'h4: reserved, 4'h5: 16K, 4'h6: reserved, 4'h7:
                                                   8K 4'h8: 44.1K, 4'h9: 88.2K, 4'hA~4'hF:reserved                           */
    __IOM uint16_t dmic_clk_sel : 3;          /*!< [10..8] set clock of digital microphone: 3'b000: 5MHz, 3'b001:
                                                   2.5MHz, 3'b010: 1.25MHz, 3'b011: 625kHz, 3'b100: 312.5kHz                 */
    __IOM uint16_t asrc_fsi_rate_manual : 4;  /*!< [14..11] set input sample rate by user: 4'h0: 48K, 4'h1: 96K,
                                                   4'h2: 192K, 4'h3: 32K 4'h4: reserved, 4'h5: 16K, 4'h6:
                                                   reserved, 4'h7: 8K 4'h8: 44.1K, 4'h9: 88.2K, 4'hA: 176.4K,
                                                   4'hB~4'hF: reserved                                                       */
    __IOM uint16_t asrc_fsi_gating_en : 1;    /*!< [15..15] set fsi gating: 1'b0 : disable 1'b1: enable fsi gating           */
  } b;                                        /*!< bit fields for audio_codec_index_17h */
} audio_codec_index_17h_t, *paudio_codec_index_17h_t;

/**
  \brief Union type to access audio_codec_index_18h (@ 0x00000030).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000030) w                                                  */

  struct {
    __IOM uint16_t da_l_en    : 1;            /*!< [0..0] set DAC filter left channel clock: 1'b0 : turn off clock
                                                   and reset 1'b1: turn on clock                                             */
    __IOM uint16_t da_r_en    : 1;            /*!< [1..1] set DAC filter right channel clock: 1'b0 : turn off clock
                                                   and reset 1'b1: turn on clock                                             */
    __IOM uint16_t mod_l_en   : 1;            /*!< [2..2] set DAC modulation left channel clock: 1'b0 : turn off
                                                   clock and reset 1'b1: turn on clock                                       */
    __IOM uint16_t mod_r_en   : 1;            /*!< [3..3] set DAC modulation right channel clock: 1'b0 : turn off
                                                   clock and reset 1'b1: turn on clock                                       */
    __IOM uint16_t da_ana_clk_en : 1;         /*!< [4..4] set DAC analog clock: 1'b0 : turn off clock 1'b1: turn
                                                   on clock                                                                  */
    __IOM uint16_t da_fifo_en : 1;            /*!< [5..5] set DAC fifo clock: 1'b0 : turn off clock and reset 1'b1:
                                                   turn on clock                                                             */
    __IOM uint16_t st_en      : 1;            /*!< [6..6] set sidetone clock: 1'b0 : turn off clock and reset 1'b1:
                                                   turn on clock                                                             */
    __IOM uint16_t ad_l_en    : 1;            /*!< [7..7] set ADC filter left channel clock: 1'b0 : turn off clock
                                                   and reset 1'b1: turn on clock                                             */
    __IOM uint16_t ad_r_en    : 1;            /*!< [8..8] set ADC filter right channel clock: 1'b0 : turn off clock
                                                   and reset 1'b1: turn on clock                                             */
    __IOM uint16_t ad_fifo_en : 1;            /*!< [9..9] set ADC fifo clock: 1'b0 : turn off clock and reset 1'b1:
                                                   turn on clock                                                             */
    __IOM uint16_t ad_ana_clk_en : 1;         /*!< [10..10] set ADC analog clock: 1'b0 : turn off clock 1'b1: turn
                                                   on clock                                                                  */
    __IOM uint16_t ad_ana_l_en : 1;           /*!< [11..11] set ADC filter left channel analog ADC path clock:
                                                   1'b0 : turn off clock and reset 1'b1: turn on clock                       */
    __IOM uint16_t ad_ana_r_en : 1;           /*!< [12..12] set ADC filter right channel analog ADC pathclock:
                                                   1'b0 : turn off clock and reset 1'b1: turn on clock                       */
    __IOM uint16_t dmic_l_en  : 1;            /*!< [13..13] set ADC filter left channel digital MIC path clock:
                                                   1'b0 : turn off clock and reset 1'b1: turn on clock                       */
    __IOM uint16_t dmic_r_en  : 1;            /*!< [14..14] set ADC filter right channel digital MIC pathclock:
                                                   1'b0 : turn off clock and reset 1'b1: turn on clock                       */
    __IOM uint16_t dmic_clk_en : 1;           /*!< [15..15] set digital MIC clock: 1'b0 : turn off clock 1'b1:
                                                   turn on clock                                                             */
  } b;                                        /*!< bit fields for audio_codec_index_18h */
} audio_codec_index_18h_t, *paudio_codec_index_18h_t;

/**
  \brief Union type to access audio_codec_index_19h (@ 0x00000032).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000032) w                                                  */

  struct {
    __IOM uint16_t asrc_ftk_sdm_ini_15_0 : 16;/*!< [15..0] set initial value of tracked frequency                            */
  } b;                                        /*!< bit fields for audio_codec_index_19h */
} audio_codec_index_19h_t, *paudio_codec_index_19h_t;

/**
  \brief Union type to access audio_codec_index_1ah (@ 0x00000034).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000034) w                                                  */

  struct {
    __IOM uint16_t asrc_ftk_sdm_ini_23_16 : 8;/*!< [7..0] set initial value of tracked frequency                             */
    __IOM uint16_t gen_src_16k128_en : 1;     /*!< [8..8] set 16k*128 clock: 1'b0 : disable 1'b1: enable                     */
    __IOM uint16_t gen_src_32k128_en : 1;     /*!< [9..9] set 32k*128 clock: 1'b0 : disable 1'b1: enable                     */
    __IOM uint16_t gen_src_44p1k128_en : 1;   /*!< [10..10] set 44.1k*128 clock: 1'b0 : disable 1'b1: enable                 */
    __IOM uint16_t gen_src_48k128_en : 1;     /*!< [11..11] set 48k*128 clock: 1'b0 : disable 1'b1: enable                   */
    __IOM uint16_t gen_src_8k128_en : 1;      /*!< [12..12] set 8k*128 clock: 1'b0 : disable 1'b1: enable                    */
    __IOM uint16_t ad_ana_clk_sel : 1;        /*!< [13..13] set clk_ad_ana phase ( reference clk_da_ana): 1'b0
                                                   : inphase 1'b1: inverse phase                                             */
    __IOM uint16_t asrc_ftk_loop_gain_sel : 2;/*!< [15..14] set loop gain: 2'b00 :2^-8 2'b01:2^-14 2'b10:2^-18
                                                   2'b11:2^-20                                                               */
  } b;                                        /*!< bit fields for audio_codec_index_1ah */
} audio_codec_index_1ah_t, *paudio_codec_index_1ah_t;

/**
  \brief Union type to access audio_codec_index_1bh (@ 0x00000036).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000036) w                                                  */

  struct {
    __IOM uint16_t audio_ip_tcon_en : 1;      /*!< [0..0] set audio ip tcon: 1'b0 : disable and reset 1'b1: enable           */
    __IOM uint16_t asrc_ftk_loop_en : 1;      /*!< [1..1] set loop filter enable: 1'b0 : disable 1'b1: enable                */
    __IOM uint16_t asrc_256fs_sys_sel : 2;    /*!< [3..2] set clock of src_tcon: 2'b00: 512*48K, 2'b01: 1024*48K,
                                                   2'b10: 2048*48K, 2'b11: Reserved                                          */
    __IOM uint16_t asrc_en    : 1;            /*!< [4..4] set asynchronous sample rate conversion: 1'b0: disable
                                                   1'b1:enable                                                               */
    __IOM uint16_t sidetone_in_sel : 2;       /*!< [6..5] sideton input selection 2'b00 : from adc_l_lpf 2'b01
                                                   : from adc_r_lpf 2'b10 : from dmic_l_lpf 2'b11 : from dmic_r_lpf          */
  } b;                                        /*!< bit fields for audio_codec_index_1bh */
} audio_codec_index_1bh_t, *paudio_codec_index_1bh_t;

/**
  \brief Union type to access audio_codec_index_1ch (@ 0x00000038).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000038) w                                                  */

  struct {
    __IOM uint16_t alc_atk_mode_rc_ctr : 1;   /*!< [0..0] ALC force slow recovery enable 1'b0: force slow recovery
                                                   1'b1: depend on alc_rc_mode_l and alc_rc_mode_r                           */
    __IOM uint16_t alc_atk_noise_rate : 5;    /*!< [5..1] ALC attack time in noise gate mode ( attack time = (4
                                                   * 2^n) /48k, n = alc_atk_noise_rate[4:0] ) 5'h00: 83us
                                                   5'h01:166us 5'h02:332us ... 5'h12: 21.85 s                                */
    __IOM uint16_t alc_atk_rate : 5;          /*!< [10..6] ALC attack time ( attack time = (4 * 2^n) /48k, n =
                                                   alc_atk_rate[4:0] ) 5'h00: 83us 5'h01:166us 5'h02:332us
                                                   ... 5'h12: 21.85 s                                                        */
    __IOM uint16_t alc_atk_speed_up_rate : 5; /*!< [15..11] ALC attack time for spped up mode ( attack time = (2
                                                   * 2^n) /48k, n = alc_atk_rate[4:0] ) 5'h00: 42us 5'h01:
                                                   83us 5'h02: 166us ... 5'h13: 21.85 s                                      */
  } b;                                        /*!< bit fields for audio_codec_index_1ch */
} audio_codec_index_1ch_t, *paudio_codec_index_1ch_t;

/**
  \brief Union type to access audio_codec_index_1dh (@ 0x0000003A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000003A) w                                                  */

  struct {
    __IOM uint16_t alc_speed_up_en : 1;       /*!< [0..0] alc_spped_up function enable control 1'b0 : disable alc_speed_up
                                                   function 1'b1 : enable alc_speed_up function                              */
    __IOM uint16_t alc_zd_full_ov_en : 1;     /*!< [1..1] enable the controlling of zero-cross by full-scale flag
                                                   1'b0: zero-cross function is controlled by register 1'b1:
                                                   zero-cross function is controlled by full-scale flag                      */
    __IOM uint16_t alc_bk_gain_l : 7;         /*!< [8..2] ALC back boost gain control (0.375dB/step) 7'h00: -35.625
                                                   dB 7'h01: -35.250 dB ..... 7'h5f: 0.000 dB ..... 7'h7f:
                                                   12.000dB                                                                  */
    __IOM uint16_t alc_bk_gain_r : 7;         /*!< [15..9] ALC back boost gain control (0.375dB/step) 7'h00: -35.625
                                                   dB 7'h01: -35.250 dB ..... 7'h5f: 0.000 dB ..... 7'h7f:
                                                   12.000dB                                                                  */
  } b;                                        /*!< bit fields for audio_codec_index_1dh */
} audio_codec_index_1dh_t, *paudio_codec_index_1dh_t;

/**
  \brief Union type to access audio_codec_index_1eh (@ 0x0000003C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000003C) w                                                  */

  struct {
    __IOM uint16_t alc_ctr_en : 1;            /*!< [0..0] ALC function & volumn control 1'b0: function OFF but
                                                   volumn ON 1'b1: function ON and volumn ON                                 */
    __IOM uint16_t alc_drc_en : 1;            /*!< [1..1] DRC enable control 1'b0: deable DRC 1'b1: enable DRC               */
    __IOM uint16_t alc_drc_ratio_sel : 2;     /*!< [3..2] ALC DRC compression ratio select control 2'b00: 1:1 2'b01:
                                                   1:2 2'b10: 1:4 2'b11: 1:8                                                 */
    __IOM uint16_t alc_drc_ratio_sel2 : 2;    /*!< [5..4] ALC DRC compression ratio select control 2'b00: 1:1 2'b01:
                                                   1:2 2'b10: 1:4 2'b11: 1:8                                                 */
    __IOM uint16_t alc_en     : 1;            /*!< [6..6] ALC enable control 1'b0: deable ALC 1'b1: enable ALC               */
    __IOM uint16_t alc_force_fast_rc_ctr : 1; /*!< [7..7] ALC force fast recovery control 1'b0: disable force fast
                                                   recovery 1'b1: enable force fast recovery                                 */
    __IOM uint16_t alc_force_fast_rc_en : 1;  /*!< [8..8] ALC force fast recovery control for special cases ( zero
                                                   data mode) 1'b0: disable force fast recovery for zero data
                                                   mode 1'b1: enable force fast recovery for zero data mode                  */
    __IOM uint16_t alc_ft_boost : 6;          /*!< [14..9] ALC front boost gain control (0.75dB/step) 6'h00: 0
                                                   dB 6'h01: 0.75 dB xxx 6'h27: 29.25 dB                                     */
  } b;                                        /*!< bit fields for audio_codec_index_1eh */
} audio_codec_index_1eh_t, *paudio_codec_index_1eh_t;

/**
  \brief Union type to access audio_codec_index_1fh (@ 0x0000003E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000003E) w                                                  */

  struct {
    __IOM uint16_t alc_lpf_coef_sel : 3;      /*!< [2..0] Coefficient for low pass filter in ALC 3'b000: 2^-3 ;
                                                   3'b001: 2^-4 ; 3'b010: 2^-5 ; 3'b011: 2^-6 ; 3'b100: 2^-7
                                                   ; 3'b101: 2^-8 ; 3'b110: 2^-10 ; 3'b111: 2^-11                            */
    __IOM uint16_t alc_min_range : 3;         /*!< [5..3] Threshold margin control in ALC 3'b000: +-0 dB ; 3'b001:
                                                   +-0.375 dB ; 3'b010: +-0.75 dB 3'b011: +-1.125 dB; 3'b100:
                                                   +-1.5 dB; 3'b101: +-1.875dB 3'b110: +-2.25 dB; 3'b111:
                                                   +-2.625 dB                                                                */
    __IOM uint16_t alc_noise_gain_hd : 1;     /*!< [6..6] ALC hold gain when noise gate mode 1'b0: do not hold
                                                   gain when noise gate mode(depend on noise gate threshold
                                                   to do noise gate's AGC) 1'b1: hold gain when noise gate
                                                   mode                                                                      */
    __IOM uint16_t alc_noise_gate_exp : 4;    /*!< [10..7] ALC noise_gate boost control 4'b0000: 0dB 4'b0001: 3dB
                                                   4'b0010: 6dB .................. 4'b1111: 45dB (3dB/step)                  */
    __IOM uint16_t alc_noise_gate_en : 1;     /*!< [11..11] ALC noise_gate mode control 1'b0: disable noise_gate
                                                   mode 1'b1: enable noise_gate mode                                         */
    __IOM uint16_t alc_noise_gate_drop_en : 1;/*!< [12..12] ALC noise_gate drop mode control 1'b0: disable noise_gate_drop
                                                   mode 1'b1: enable noise_gate_drop mode                                    */
    __IOM uint16_t alc_noise_gate_ratio_sel : 2;/*!< [14..13] ALC DRC expansion ratio select control, when noise
                                                   gate is enabled 2'b00: 1:1 2'b01: 2:1 2'b10: 4:1 2'b11:
                                                   8:1                                                                       */
  } b;                                        /*!< bit fields for audio_codec_index_1fh */
} audio_codec_index_1fh_t, *paudio_codec_index_1fh_t;

/**
  \brief Union type to access audio_codec_index_20h (@ 0x00000040).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000040) w                                                  */

  struct {
    __IOM uint16_t alc_noise_range : 2;       /*!< [1..0] Noise gate threshold margin control in ALC 2'b00: +-0
                                                   dB 2'b01: +-1.5 dB 2'b10: +-3.0 dB 2'b11: +-4.5 dB                        */
    __IOM uint16_t alc_off_gain : 8;          /*!< [9..2] ALC digital volumn gain when alc_ctr_en=1'b0 8'hff: 0
                                                   dB 8'hfe: -0.375 dB 8'hfd: -0.75 dB .....................
                                                   8'h00: -95.625 dB (-0.375dB/step)                                         */
    __IOM uint16_t alc_rate_sel : 3;          /*!< [12..10] ALC rate control for sample rate change 3'b001: 48
                                                   kHz 3'b010: 96 kHz 3'b011: 192 kHz 3'b011: 44.1kHz 3'b100:
                                                   88.2kHz 3'b101: 176.4kHz                                                  */
    __IOM uint16_t alc_rc_fast_en : 1;        /*!< [13..13] ALC force fast recovery control for special cases (window)
                                                   1'b0: disable force fast recovery for special cases 1'b1:
                                                   enable force fast recovery for normal use                                 */
  } b;                                        /*!< bit fields for audio_codec_index_20h */
} audio_codec_index_20h_t, *paudio_codec_index_20h_t;

/**
  \brief Union type to access audio_codec_index_21h (@ 0x00000042).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000042) w                                                  */

  struct {
    __IOM uint16_t alc_rc_fast_rate : 5;      /*!< [4..0] ALC fast recovery time ( recovery time = (4 * 2^n) /48k,
                                                   n = alc_rc_fast_rate[4:0] ) 5'h00: 83us 5'h01:166us 5'h02:332us
                                                   ... 5'h12: 21.85 s                                                        */
    __IOM uint16_t alc_rc_slow_rate : 5;      /*!< [9..5] ALC slow recovery time ( recovery time = (4 * 2^n) /48k,
                                                   n = alc_rc_slow_rate[4:0] ) 5'h00: 83us 5'h01:166us 5'h02:332us
                                                   ... 5'h12: 21.85 s                                                        */
    __IOM uint16_t alc_thmax  : 6;            /*!< [15..10] ALC main-limiter threshold level (at amplitude domain)
                                                   control 6'h00: 0 dB 6'h01: - 0.375dB 6'h02: - 0.750dB ..................
                                                   6'h3f: -23.625dB (-0.375dB/step)                                          */
  } b;                                        /*!< bit fields for audio_codec_index_21h */
} audio_codec_index_21h_t, *paudio_codec_index_21h_t;

/**
  \brief Union type to access audio_codec_index_22h (@ 0x00000044).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000044) w                                                  */

  struct {
    __IOM uint16_t alc_rc_wd_max : 8;         /*!< [7..0] Set upper bound of fast recovery window 8'h01: 5.33 ms
                                                   8'h02: 10.67 ms ................ 8'hff: 1360 ms                           */
    __IOM uint16_t alc_rc_wd_min : 8;         /*!< [15..8] Set lower bound of fast recovery window 8'h01: 2.67
                                                   ms 8'h02: 5.33 ms ................ 8'hff: 680 ms                          */
  } b;                                        /*!< bit fields for audio_codec_index_22h */
} audio_codec_index_22h_t, *paudio_codec_index_22h_t;

/**
  \brief Union type to access audio_codec_index_23h (@ 0x00000046).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000046) w                                                  */

  struct {
    __IOM uint16_t alc_thfull : 2;            /*!< [1..0] ALC full scale threshold level (at amplitude domain)
                                                   control 2'b00: 0 dBFs 2'b01: -0.5 dBFs 2'b10: -1.0 dBFs
                                                   2'b11: -1.5 dBFs                                                          */
    __IOM uint16_t alc_thmax2 : 6;            /*!< [7..2] ALC second-limiter threshold level (at amplitude domain)
                                                   control 6'h00: 0 dB 6'h01: - 0.75dB 6'h02: - 1.5 dB ..................
                                                   6'h3c: -45 dB (-0.75dB/step)                                              */
    __IOM uint16_t alc_thnoise : 5;           /*!< [12..8] AGC noise gate threshold level (at amplitude domain)
                                                   control 5'h00: -24.00dB 5'h01: -25.50dB 5'h02: -27.00dB
                                                   .................. 5'h1f : -70.50dB (-1.5dB/step)                         */
    __IOM uint16_t alc_thzero : 3;            /*!< [15..13] ALC zero-data threshold level (at amplitude domain)
                                                   control 3'b000: -84.0dB 3'b001: -85.5dB 3'b010: -87.0dB
                                                   .................. 3'b111: -94.5dB (-1.5dB/step)                          */
  } b;                                        /*!< bit fields for audio_codec_index_23h */
} audio_codec_index_23h_t, *paudio_codec_index_23h_t;

/**
  \brief Union type to access audio_codec_index_24h (@ 0x00000048).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000048) w                                                  */

  struct {
    __IOM uint16_t alc_zdet_func : 2;         /*!< [1..0] Volumn control for ALC zero detection 2'b00: immediatly
                                                   change 2'b01: change directly when zero crossing 2'b10:
                                                   change per step when zero crossing 2'b11: hold original
                                                   gain                                                                      */
    __IOM uint16_t alc_zdet_tout : 2;         /*!< [3..2] Time out for volumn change with ALC zero detection 2'b00:
                                                   12000*SYNC 2'b01: 24000*SYNC 2'b10: 36000*SYNC 2'b11: 48000*SYNC          */
    __IOM uint16_t alc_zero_data_en : 1;      /*!< [4..4] ALC zero_data mode control 1'b0: disable zero_data mode
                                                   1'b1: enable zero_data mode                                               */
    __IOM uint16_t alc_limiter_ratio : 3;     /*!< [7..5] ALC limiter ratio control: 3'b000: 1/4 , 3'b001: 1/8,
                                                   3'b010: 1/16, 3'b011: 1/32, 3'b100: 1/64,3'b101: 1/128,
                                                   3'b110: 1/256, 3'b111: hard limiter                                       */
    __IOM uint16_t alc_zero_data_sel : 1;     /*!< [8..8] ALC zero data mode selection control 1'b0: decide zero
                                                   data mode by root mean square 1'b1: decide zero data mode
                                                   by amplitude detection                                                    */
    __IOM uint16_t alc_zero_data_cnt_th : 2;  /*!< [10..9] Time out for ALC zero data mode with amplitude detetion:
                                                   2'b00: 1024 samples ( 20 msec with 48k sample rate ) 2'b01:
                                                   2048 samples ( 40 msec with 48k sample rate ) 2'b10: 4096
                                                   samples ( 80 msec with 48k sample rate ) 2'b11: 8 samples
                                                   ( 0.17 msec with 48k sample rate , test mode)                             */
    __IOM uint16_t alc_zero_data_lsb_sel : 3; /*!< [13..11] Threshold for ALC zero data mode with amplitude detection
                                                   3'b000: - 78db 3'b001: - 84db 3'b010: - 90db 3'b011: -102db
                                                   3'b100: -108db 3'b101:-114db 3'b110:-126db 3'b111: -132db                 */
    __IOM uint16_t alc_bypass_cd_en : 1;      /*!< [14..14] cross-dection control for alc_bypass function 1'b0:
                                                   alc_bypass function without cross detection 1'b1: alc_bypass
                                                   function with cross detection                                             */
    __IOM uint16_t alc_atk_hold_en : 1;       /*!< [15..15] enable control for attack hold function in ALC 1'b0:
                                                   attack hold function is disable 1'b1: attack hold function
                                                   is enable                                                                 */
  } b;                                        /*!< bit fields for audio_codec_index_24h */
} audio_codec_index_24h_t, *paudio_codec_index_24h_t;

/**
  \brief Union type to access audio_codec_index_25h (@ 0x0000004A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000004A) w                                                  */

  struct {
    __IOM uint16_t alc_limiter_th_15_0 : 16;  /*!< [15..0] ALC limiter threshold control: threshold_in_db = 20*log10(alc_limiter_
                                                   h * 2^-23)                                                                */
  } b;                                        /*!< bit fields for audio_codec_index_25h */
} audio_codec_index_25h_t, *paudio_codec_index_25h_t;

/**
  \brief Union type to access audio_codec_index_26h (@ 0x0000004C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000004C) w                                                  */

  struct {
    __IOM uint16_t alc_limiter_th_23_16 : 8;  /*!< [7..0] ALC limiter threshold control: threshold_in_db = 20*log10(alc_limiter_t
                                                   * 2^-23)                                                                  */
    __IOM uint16_t alc_atk_hold_release_en : 1;/*!< [8..8] enable control for releasing the attck hold when ALC
                                                   is in atk_hold mode 1'b0: atk_hold is not released 1'b1:
                                                   atk_hold will be released                                                 */
    __IOM uint16_t alc_atk_hold_release_th : 2;/*!< [10..9] atk_hold release time control for ALC 2'b00: 5 msec
                                                   ; 2'b01: 400msec ; 2'b10: 1200msec ; 2'b11: 2400msec (@
                                                   fs=48k)                                                                   */
    __IOM uint16_t alc_atk_hold_recov_th : 2; /*!< [12..11] atk_hold recover time control for ALC 2'b00: 5 msec
                                                   ; 2'b01: 400msec ; 2'b10: 1200msec ; 2'b11: 2400msec (@
                                                   fs=48k)                                                                   */
    __IOM uint16_t alc_min_gain_en : 1;       /*!< [13..13] enable control for minimum gain control in ALC 1'b0:
                                                   ALC minimun gain is disable 1'b1: ALC minimun gain is disable             */
  } b;                                        /*!< bit fields for audio_codec_index_26h */
} audio_codec_index_26h_t, *paudio_codec_index_26h_t;

/**
  \brief Union type to access audio_codec_index_27h (@ 0x0000004E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000004E) w                                                  */

  struct {
    __IOM uint16_t alc_min_gain : 8;          /*!< [7..0] min gain for ALC 8'hFF: 0db , 8'hFE: -0.375db , xxx ,
                                                   8'h1: -91.875db , 8'h0: -95.625db                                         */
    __IOM uint16_t da_stereo_mode_en : 1;     /*!< [8..8] enable control for dac filter 1'b0: ALC is mono mode
                                                   1'b1: ALC is stereo mode                                                  */
  } b;                                        /*!< bit fields for audio_codec_index_27h */
} audio_codec_index_27h_t, *paudio_codec_index_27h_t;

/**
  \brief Union type to access audio_codec_index_28h (@ 0x00000050).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000050) w                                                  */

  struct {
    __IM  uint16_t alc_gain_out : 8;          /*!< [7..0] ALC output gain                                                    */
    __IM  uint16_t alc_noise_gate_mode_l : 1; /*!< [8..8] status of noise_gate mode in L channel 1'b0: not noise_gate
                                                   mode 1'b1: noise_gate mode                                                */
    __IM  uint16_t alc_noise_gate_mode_r : 1; /*!< [9..9] status of noise_gate mode in R channel 1'b0: not noise_gate
                                                   mode 1'b1: noise_gate mode                                                */
    __IM  uint16_t alc_op_mode_l : 1;         /*!< [10..10] status of ALC operation mode in L channel 1'b0: recover
                                                   mode 1'b1: attack mode                                                    */
    __IM  uint16_t alc_op_mode_r : 1;         /*!< [11..11] status of ALC operation mode in R channel 1'b0: recover
                                                   mode 1'b1: attack mode                                                    */
    __IM  uint16_t alc_rc_mode_l : 1;         /*!< [12..12] Recovery status of L channel 1'b0: slow recover 1'b1:
                                                   fast recover                                                              */
    __IM  uint16_t alc_rc_mode_r : 1;         /*!< [13..13] Recovery status of R channel 1'b0: slow recover 1'b1:
                                                   fast recover                                                              */
    __IM  uint16_t alc_zero_data_mode_l : 1;  /*!< [14..14] status of zero_data mode in L channel 1'b0: not zero_data
                                                   mode 1'b1: zero_data mode                                                 */
    __IM  uint16_t alc_zero_data_mode_r : 1;  /*!< [15..15] status of zero_data mode in R channel 1'b0: not zero_data
                                                   mode 1'b1: zero_data mode                                                 */
  } b;                                        /*!< bit fields for audio_codec_index_28h */
} audio_codec_index_28h_t, *paudio_codec_index_28h_t;

/**
  \brief Union type to access audio_codec_index_29h (@ 0x00000052).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000052) w                                                  */

  struct {
    __IM  uint16_t alc_bk_rms_hov_l : 1;      /*!< [0..0] status of back-end L channel 1'b0: energy of back-end
                                                   <= alc_thmax 1'b1: energy of back-end > alc_thmax                         */
    __IM  uint16_t alc_bk_rms_hov_r : 1;      /*!< [1..1] status of back-end R channel 1'b0: energy of back-end
                                                   <= alc_thmax 1'b1: energy of back-end > alc_thmax                         */
    __IM  uint16_t alc_bk_rms_lov_l : 1;      /*!< [2..2] status of back-end L channel 1'b0: energy of back-end
                                                   <= alc_thmax - alc_min_range 1'b1: energy of back-end >
                                                   alc_thmax - alc_min_range                                                 */
    __IM  uint16_t alc_bk_rms_lov_r : 1;      /*!< [3..3] status of back-end R channel 1'b0: energy of back-end
                                                   <= alc_thmax - alc_min_range 1'b1: energy of back-end >
                                                   alc_thmax - alc_min_range                                                 */
    __IM  uint16_t alc_force_fast_rc_mode : 1;/*!< [4..4] Status of fast recover in front end 1'b0: slow recover
                                                   mode 1'b1: force fast recover mode                                        */
    __IM  uint16_t alc_thmax_mode_l : 1;      /*!< [5..5] status of noise_gate mode in L channel 1'b0: not thmax_mode
                                                   1'b1: thmax_mode                                                          */
    __IM  uint16_t alc_thmax_mode_r : 1;      /*!< [6..6] status of noise_gate mode in R channel 1'b0: not thmax_mode
                                                   1'b1: thmax_mode                                                          */
    __IM  uint16_t alc_thmax2_mode_l : 1;     /*!< [7..7] status of noise_gate mode in L channel 1'b0: not thmax2_mode
                                                   1'b1: thmax2_mode                                                         */
    __IM  uint16_t alc_thmax2_mode_r : 1;     /*!< [8..8] status of noise_gate mode in R channel 1'b0: not thmax2_mode
                                                   1'b1: thmax2_mode                                                         */
    __IM  uint16_t alc_atk_hold_flag_l : 1;   /*!< [9..9] status of atk_hold mode for L channel in ALC                       */
    __IM  uint16_t alc_atk_hold_flag_r : 1;   /*!< [10..10] status of atk_hold mode for R channel in ALC                     */
    __IM  uint16_t alc_atk_hold_flag : 1;     /*!< [11..11] status of atk_hold mode in ALC                                   */
  } b;                                        /*!< bit fields for audio_codec_index_29h */
} audio_codec_index_29h_t, *paudio_codec_index_29h_t;

/**
  \brief Union type to access audio_codec_index_2ah (@ 0x00000054).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000054) w                                                  */

  struct {
    __IOM uint16_t dac_l_bq_eq_param_update : 1;/*!< [0..0] DAC Lch EQ Write 1 to send parameter update pluse 1'b0:
                                                   Busy (Waiting for cross) 1'b1: Stand-by                                   */
    __IOM uint16_t dac_l_bq_eq_cd_en : 1;     /*!< [1..1] DAC Lch EQ cross detection control 1'b0: Disable (Test
                                                   mode) 1'b1: Enable (Normal mode)                                          */
    __IOM uint16_t dac_l_bq_eq_dither_sel : 2;/*!< [3..2] DAC Lch EQ dither control 2'b00: Normal, 2'b01: LSB 2'b10:
                                                   {LSB+1, LSB}, 2'b11: {LSB+2, LSB+1, LSB}                                  */
    __IM  uint16_t            : 1;
    __IM  uint16_t dac_l_bq_eq_cd_flag : 1;   /*!< [5..5] DAC Lch Biquad filter cross detect status 1'b0: no data
                                                   zero cross 1'b1: data zero cross                                          */
  } b;                                        /*!< bit fields for audio_codec_index_2ah */
} audio_codec_index_2ah_t, *paudio_codec_index_2ah_t;

/**
  \brief Union type to access audio_codec_index_2bh (@ 0x00000056).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000056) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_h0_1_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 1st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_2bh */
} audio_codec_index_2bh_t, *paudio_codec_index_2bh_t;

/**
  \brief Union type to access audio_codec_index_2ch (@ 0x00000058).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000058) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_h0_1_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 1st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_2ch */
} audio_codec_index_2ch_t, *paudio_codec_index_2ch_t;

/**
  \brief Union type to access audio_codec_index_2dh (@ 0x0000005A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000005A) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b1_1_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 1st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_2dh */
} audio_codec_index_2dh_t, *paudio_codec_index_2dh_t;

/**
  \brief Union type to access audio_codec_index_2eh (@ 0x0000005C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000005C) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b1_1_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 1st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_2eh */
} audio_codec_index_2eh_t, *paudio_codec_index_2eh_t;

/**
  \brief Union type to access audio_codec_index_2fh (@ 0x0000005E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000005E) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b2_1_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 1st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_2fh */
} audio_codec_index_2fh_t, *paudio_codec_index_2fh_t;

/**
  \brief Union type to access audio_codec_index_30h (@ 0x00000060).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000060) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b2_1_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 1st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_30h */
} audio_codec_index_30h_t, *paudio_codec_index_30h_t;

/**
  \brief Union type to access audio_codec_index_31h (@ 0x00000062).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000062) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a1_1_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 1st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_31h */
} audio_codec_index_31h_t, *paudio_codec_index_31h_t;

/**
  \brief Union type to access audio_codec_index_32h (@ 0x00000064).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000064) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a1_1_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 1st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_32h */
} audio_codec_index_32h_t, *paudio_codec_index_32h_t;

/**
  \brief Union type to access audio_codec_index_33h (@ 0x00000066).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000066) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a2_1_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 1st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_33h */
} audio_codec_index_33h_t, *paudio_codec_index_33h_t;

/**
  \brief Union type to access audio_codec_index_34h (@ 0x00000068).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000068) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a2_1_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 1st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t dac_l_biquad_en_1 : 1;     /*!< [13..13] DAC Lch 1st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t dac_l_biquad_wclr_1 : 1;   /*!< [14..14] DAC Lch 1st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t dac_l_biquad_status_1 : 1; /*!< [15..15] DAC Lch 1st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_34h */
} audio_codec_index_34h_t, *paudio_codec_index_34h_t;

/**
  \brief Union type to access audio_codec_index_35h (@ 0x0000006A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000006A) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_h0_2_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 2st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_35h */
} audio_codec_index_35h_t, *paudio_codec_index_35h_t;

/**
  \brief Union type to access audio_codec_index_36h (@ 0x0000006C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000006C) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_h0_2_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 2st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_36h */
} audio_codec_index_36h_t, *paudio_codec_index_36h_t;

/**
  \brief Union type to access audio_codec_index_37h (@ 0x0000006E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000006E) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b1_2_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 2st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_37h */
} audio_codec_index_37h_t, *paudio_codec_index_37h_t;

/**
  \brief Union type to access audio_codec_index_38h (@ 0x00000070).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000070) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b1_2_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 2st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_38h */
} audio_codec_index_38h_t, *paudio_codec_index_38h_t;

/**
  \brief Union type to access audio_codec_index_39h (@ 0x00000072).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000072) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b2_2_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 2st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_39h */
} audio_codec_index_39h_t, *paudio_codec_index_39h_t;

/**
  \brief Union type to access audio_codec_index_3ah (@ 0x00000074).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000074) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b2_2_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 2st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_3ah */
} audio_codec_index_3ah_t, *paudio_codec_index_3ah_t;

/**
  \brief Union type to access audio_codec_index_3bh (@ 0x00000076).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000076) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a1_2_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 2st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_3bh */
} audio_codec_index_3bh_t, *paudio_codec_index_3bh_t;

/**
  \brief Union type to access audio_codec_index_3ch (@ 0x00000078).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000078) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a1_2_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 2st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_3ch */
} audio_codec_index_3ch_t, *paudio_codec_index_3ch_t;

/**
  \brief Union type to access audio_codec_index_3dh (@ 0x0000007A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000007A) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a2_2_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 2st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_3dh */
} audio_codec_index_3dh_t, *paudio_codec_index_3dh_t;

/**
  \brief Union type to access audio_codec_index_3eh (@ 0x0000007C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000007C) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a2_2_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 2st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t dac_l_biquad_en_2 : 1;     /*!< [13..13] DAC Lch 2st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t dac_l_biquad_wclr_2 : 1;   /*!< [14..14] DAC Lch 2st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t dac_l_biquad_status_2 : 1; /*!< [15..15] DAC Lch 2st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_3eh */
} audio_codec_index_3eh_t, *paudio_codec_index_3eh_t;

/**
  \brief Union type to access audio_codec_index_3fh (@ 0x0000007E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000007E) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_h0_3_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 3st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_3fh */
} audio_codec_index_3fh_t, *paudio_codec_index_3fh_t;

/**
  \brief Union type to access audio_codec_index_40h (@ 0x00000080).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000080) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_h0_3_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 3st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_40h */
} audio_codec_index_40h_t, *paudio_codec_index_40h_t;

/**
  \brief Union type to access audio_codec_index_41h (@ 0x00000082).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000082) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b1_3_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 3st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_41h */
} audio_codec_index_41h_t, *paudio_codec_index_41h_t;

/**
  \brief Union type to access audio_codec_index_42h (@ 0x00000084).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000084) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b1_3_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 3st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_42h */
} audio_codec_index_42h_t, *paudio_codec_index_42h_t;

/**
  \brief Union type to access audio_codec_index_43h (@ 0x00000086).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000086) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b2_3_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 3st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_43h */
} audio_codec_index_43h_t, *paudio_codec_index_43h_t;

/**
  \brief Union type to access audio_codec_index_44h (@ 0x00000088).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000088) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b2_3_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 3st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_44h */
} audio_codec_index_44h_t, *paudio_codec_index_44h_t;

/**
  \brief Union type to access audio_codec_index_45h (@ 0x0000008A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000008A) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a1_3_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 2st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_45h */
} audio_codec_index_45h_t, *paudio_codec_index_45h_t;

/**
  \brief Union type to access audio_codec_index_46h (@ 0x0000008C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000008C) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a1_3_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 3st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_46h */
} audio_codec_index_46h_t, *paudio_codec_index_46h_t;

/**
  \brief Union type to access audio_codec_index_47h (@ 0x0000008E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000008E) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a2_3_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 3st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_47h */
} audio_codec_index_47h_t, *paudio_codec_index_47h_t;

/**
  \brief Union type to access audio_codec_index_48h (@ 0x00000090).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000090) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a2_3_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 3st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t dac_l_biquad_en_3 : 1;     /*!< [13..13] DAC Lch 3st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t dac_l_biquad_wclr_3 : 1;   /*!< [14..14] DAC Lch 3st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t dac_l_biquad_status_3 : 1; /*!< [15..15] DAC Lch 3st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_48h */
} audio_codec_index_48h_t, *paudio_codec_index_48h_t;

/**
  \brief Union type to access audio_codec_index_49h (@ 0x00000092).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000092) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_h0_4_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 4st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_49h */
} audio_codec_index_49h_t, *paudio_codec_index_49h_t;

/**
  \brief Union type to access audio_codec_index_4ah (@ 0x00000094).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000094) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_h0_4_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 4st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_4ah */
} audio_codec_index_4ah_t, *paudio_codec_index_4ah_t;

/**
  \brief Union type to access audio_codec_index_4bh (@ 0x00000096).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000096) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b1_4_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 4st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_4bh */
} audio_codec_index_4bh_t, *paudio_codec_index_4bh_t;

/**
  \brief Union type to access audio_codec_index_4ch (@ 0x00000098).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000098) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b1_4_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 4st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_4ch */
} audio_codec_index_4ch_t, *paudio_codec_index_4ch_t;

/**
  \brief Union type to access audio_codec_index_4dh (@ 0x0000009A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000009A) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b2_4_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 4st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_4dh */
} audio_codec_index_4dh_t, *paudio_codec_index_4dh_t;

/**
  \brief Union type to access audio_codec_index_4eh (@ 0x0000009C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000009C) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b2_4_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 4st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_4eh */
} audio_codec_index_4eh_t, *paudio_codec_index_4eh_t;

/**
  \brief Union type to access audio_codec_index_4fh (@ 0x0000009E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000009E) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a1_4_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 4st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_4fh */
} audio_codec_index_4fh_t, *paudio_codec_index_4fh_t;

/**
  \brief Union type to access audio_codec_index_50h (@ 0x000000A0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000A0) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a1_4_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 4st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_50h */
} audio_codec_index_50h_t, *paudio_codec_index_50h_t;

/**
  \brief Union type to access audio_codec_index_51h (@ 0x000000A2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000A2) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a2_4_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 4st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_51h */
} audio_codec_index_51h_t, *paudio_codec_index_51h_t;

/**
  \brief Union type to access audio_codec_index_52h (@ 0x000000A4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000A4) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a2_4_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 4st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t dac_l_biquad_en_4 : 1;     /*!< [13..13] DAC Lch 4st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t dac_l_biquad_wclr_4 : 1;   /*!< [14..14] DAC Lch 4st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t dac_l_biquad_status_4 : 1; /*!< [15..15] DAC Lch 4st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_52h */
} audio_codec_index_52h_t, *paudio_codec_index_52h_t;

/**
  \brief Union type to access audio_codec_index_53h (@ 0x000000A6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000A6) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_h0_5_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 5st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_53h */
} audio_codec_index_53h_t, *paudio_codec_index_53h_t;

/**
  \brief Union type to access audio_codec_index_54h (@ 0x000000A8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000A8) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_h0_5_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 5st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_54h */
} audio_codec_index_54h_t, *paudio_codec_index_54h_t;

/**
  \brief Union type to access audio_codec_index_55h (@ 0x000000AA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000AA) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b1_5_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 5st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_55h */
} audio_codec_index_55h_t, *paudio_codec_index_55h_t;

/**
  \brief Union type to access audio_codec_index_56h (@ 0x000000AC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000AC) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b1_5_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 5st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_56h */
} audio_codec_index_56h_t, *paudio_codec_index_56h_t;

/**
  \brief Union type to access audio_codec_index_57h (@ 0x000000AE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000AE) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b2_5_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 5st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_57h */
} audio_codec_index_57h_t, *paudio_codec_index_57h_t;

/**
  \brief Union type to access audio_codec_index_58h (@ 0x000000B0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000B0) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_b2_5_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 5st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_58h */
} audio_codec_index_58h_t, *paudio_codec_index_58h_t;

/**
  \brief Union type to access audio_codec_index_59h (@ 0x000000B2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000B2) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a1_5_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 5st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_59h */
} audio_codec_index_59h_t, *paudio_codec_index_59h_t;

/**
  \brief Union type to access audio_codec_index_5ah (@ 0x000000B4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000B4) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a1_5_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 5st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_5ah */
} audio_codec_index_5ah_t, *paudio_codec_index_5ah_t;

/**
  \brief Union type to access audio_codec_index_5bh (@ 0x000000B6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000B6) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a2_5_bit15to0 : 16;/*!< [15..0] DAC Lch EQ 5st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_5bh */
} audio_codec_index_5bh_t, *paudio_codec_index_5bh_t;

/**
  \brief Union type to access audio_codec_index_5ch (@ 0x000000B8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000B8) w                                                  */

  struct {
    __IOM uint16_t dac_l_biquad_a2_5_bit28to16 : 13;/*!< [12..0] DAC Lch EQ 5st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t dac_l_biquad_en_5 : 1;     /*!< [13..13] DAC Lch 5st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t dac_l_biquad_wclr_5 : 1;   /*!< [14..14] DAC Lch 5st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t dac_l_biquad_status_5 : 1; /*!< [15..15] DAC Lch 5st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_5ch */
} audio_codec_index_5ch_t, *paudio_codec_index_5ch_t;

/**
  \brief Union type to access audio_codec_index_5dh (@ 0x000000BA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000BA) w                                                  */

  struct {
    __IOM uint16_t dac_r_bq_eq_param_update : 1;/*!< [0..0] DAC Rch EQ Write 1 to send parameter update pluse 1'b0:
                                                   Busy (Waiting for cross) 1'b1: Stand-by                                   */
    __IOM uint16_t dac_r_bq_eq_cd_en : 1;     /*!< [1..1] DAC Rch EQ cross detection control 1'b0: Disable (Test
                                                   mode) 1'b1: Enable (Normal mode)                                          */
    __IOM uint16_t dac_r_bq_eq_dither_sel : 2;/*!< [3..2] DAC Rch EQ dither control 2'b00: Normal, 2'b01: LSB 2'b10:
                                                   {LSB+1, LSB}, 2'b11: {LSB+2, LSB+1, LSB}                                  */
    __IM  uint16_t            : 1;
    __IM  uint16_t dac_r_bq_eq_cd_flag : 1;   /*!< [5..5] DAC Rch Biquad filter cross detect status 1'b0: no data
                                                   zero cross 1'b1: data zero cross                                          */
  } b;                                        /*!< bit fields for audio_codec_index_5dh */
} audio_codec_index_5dh_t, *paudio_codec_index_5dh_t;

/**
  \brief Union type to access audio_codec_index_5eh (@ 0x000000BC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000BC) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_h0_1_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 1st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_5eh */
} audio_codec_index_5eh_t, *paudio_codec_index_5eh_t;

/**
  \brief Union type to access audio_codec_index_5fh (@ 0x000000BE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000BE) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_h0_1_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 1st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_5fh */
} audio_codec_index_5fh_t, *paudio_codec_index_5fh_t;

/**
  \brief Union type to access audio_codec_index_60h (@ 0x000000C0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000C0) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b1_1_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 1st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_60h */
} audio_codec_index_60h_t, *paudio_codec_index_60h_t;

/**
  \brief Union type to access audio_codec_index_61h (@ 0x000000C2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000C2) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b1_1_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 1st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_61h */
} audio_codec_index_61h_t, *paudio_codec_index_61h_t;

/**
  \brief Union type to access audio_codec_index_62h (@ 0x000000C4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000C4) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b2_1_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 1st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_62h */
} audio_codec_index_62h_t, *paudio_codec_index_62h_t;

/**
  \brief Union type to access audio_codec_index_63h (@ 0x000000C6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000C6) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b2_1_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 1st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_63h */
} audio_codec_index_63h_t, *paudio_codec_index_63h_t;

/**
  \brief Union type to access audio_codec_index_64h (@ 0x000000C8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000C8) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a1_1_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 1st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_64h */
} audio_codec_index_64h_t, *paudio_codec_index_64h_t;

/**
  \brief Union type to access audio_codec_index_65h (@ 0x000000CA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000CA) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a1_1_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 1st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_65h */
} audio_codec_index_65h_t, *paudio_codec_index_65h_t;

/**
  \brief Union type to access audio_codec_index_66h (@ 0x000000CC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000CC) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a2_1_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 1st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_66h */
} audio_codec_index_66h_t, *paudio_codec_index_66h_t;

/**
  \brief Union type to access audio_codec_index_67h (@ 0x000000CE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000CE) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a2_1_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 1st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t dac_r_biquad_en_1 : 1;     /*!< [13..13] DAC Rch 1st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t dac_r_biquad_wclr_1 : 1;   /*!< [14..14] DAC Rch 1st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t dac_r_biquad_status_1 : 1; /*!< [15..15] DAC Rch 1st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_67h */
} audio_codec_index_67h_t, *paudio_codec_index_67h_t;

/**
  \brief Union type to access audio_codec_index_68h (@ 0x000000D0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000D0) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_h0_2_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 2st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_68h */
} audio_codec_index_68h_t, *paudio_codec_index_68h_t;

/**
  \brief Union type to access audio_codec_index_69h (@ 0x000000D2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000D2) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_h0_2_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 2st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_69h */
} audio_codec_index_69h_t, *paudio_codec_index_69h_t;

/**
  \brief Union type to access audio_codec_index_6ah (@ 0x000000D4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000D4) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b1_2_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 2st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_6ah */
} audio_codec_index_6ah_t, *paudio_codec_index_6ah_t;

/**
  \brief Union type to access audio_codec_index_6bh (@ 0x000000D6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000D6) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b1_2_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 2st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_6bh */
} audio_codec_index_6bh_t, *paudio_codec_index_6bh_t;

/**
  \brief Union type to access audio_codec_index_6ch (@ 0x000000D8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000D8) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b2_2_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 2st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_6ch */
} audio_codec_index_6ch_t, *paudio_codec_index_6ch_t;

/**
  \brief Union type to access audio_codec_index_6dh (@ 0x000000DA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000DA) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b2_2_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 2st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_6dh */
} audio_codec_index_6dh_t, *paudio_codec_index_6dh_t;

/**
  \brief Union type to access audio_codec_index_6eh (@ 0x000000DC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000DC) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a1_2_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 2st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_6eh */
} audio_codec_index_6eh_t, *paudio_codec_index_6eh_t;

/**
  \brief Union type to access audio_codec_index_6fh (@ 0x000000DE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000DE) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a1_2_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 2st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_6fh */
} audio_codec_index_6fh_t, *paudio_codec_index_6fh_t;

/**
  \brief Union type to access audio_codec_index_70h (@ 0x000000E0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000E0) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a2_2_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 2st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_70h */
} audio_codec_index_70h_t, *paudio_codec_index_70h_t;

/**
  \brief Union type to access audio_codec_index_71h (@ 0x000000E2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000E2) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a2_2_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 2st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t dac_r_biquad_en_2 : 1;     /*!< [13..13] DAC Rch 2st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t dac_r_biquad_wclr_2 : 1;   /*!< [14..14] DAC Rch 2st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t dac_r_biquad_status_2 : 1; /*!< [15..15] DAC Rch 2st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_71h */
} audio_codec_index_71h_t, *paudio_codec_index_71h_t;

/**
  \brief Union type to access audio_codec_index_72h (@ 0x000000E4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000E4) index_72Fh                                                 */

  struct {
    __IOM uint16_t dac_r_biquad_h0_3_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 3st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_72h */
} audio_codec_index_72h_t, *paudio_codec_index_72h_t;

/**
  \brief Union type to access audio_codec_index_73h (@ 0x000000E6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000E6) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_h0_3_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 3st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_73h */
} audio_codec_index_73h_t, *paudio_codec_index_73h_t;

/**
  \brief Union type to access audio_codec_index_74h (@ 0x000000E8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000E8) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b1_3_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 3st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_74h */
} audio_codec_index_74h_t, *paudio_codec_index_74h_t;

/**
  \brief Union type to access audio_codec_index_75h (@ 0x000000EA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000EA) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b1_3_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 3st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_75h */
} audio_codec_index_75h_t, *paudio_codec_index_75h_t;

/**
  \brief Union type to access audio_codec_index_76h (@ 0x000000EC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000EC) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b2_3_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 3st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_76h */
} audio_codec_index_76h_t, *paudio_codec_index_76h_t;

/**
  \brief Union type to access audio_codec_index_77h (@ 0x000000EE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000EE) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b2_3_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 3st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_77h */
} audio_codec_index_77h_t, *paudio_codec_index_77h_t;

/**
  \brief Union type to access audio_codec_index_78h (@ 0x000000F0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000F0) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a1_3_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 3st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_78h */
} audio_codec_index_78h_t, *paudio_codec_index_78h_t;

/**
  \brief Union type to access audio_codec_index_79h (@ 0x000000F2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000F2) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a1_3_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 3st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_79h */
} audio_codec_index_79h_t, *paudio_codec_index_79h_t;

/**
  \brief Union type to access audio_codec_index_7ah (@ 0x000000F4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000F4) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a2_3_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 3st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_7ah */
} audio_codec_index_7ah_t, *paudio_codec_index_7ah_t;

/**
  \brief Union type to access audio_codec_index_7bh (@ 0x000000F6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000F6) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a2_3_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 3st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t dac_r_biquad_en_3 : 1;     /*!< [13..13] DAC Rch 3st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t dac_r_biquad_wclr_3 : 1;   /*!< [14..14] DAC Rch 3st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t dac_r_biquad_status_3 : 1; /*!< [15..15] DAC Rch 3st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_7bh */
} audio_codec_index_7bh_t, *paudio_codec_index_7bh_t;

/**
  \brief Union type to access audio_codec_index_7ch (@ 0x000000F8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000F8) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_h0_4_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 4st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_7ch */
} audio_codec_index_7ch_t, *paudio_codec_index_7ch_t;

/**
  \brief Union type to access audio_codec_index_7dh (@ 0x000000FA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000FA) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_h0_4_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 4st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_7dh */
} audio_codec_index_7dh_t, *paudio_codec_index_7dh_t;

/**
  \brief Union type to access audio_codec_index_7eh (@ 0x000000FC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000FC) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b1_4_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 4st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_7eh */
} audio_codec_index_7eh_t, *paudio_codec_index_7eh_t;

/**
  \brief Union type to access audio_codec_index_7fh (@ 0x000000FE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000000FE) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b1_4_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 4st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_7fh */
} audio_codec_index_7fh_t, *paudio_codec_index_7fh_t;

/**
  \brief Union type to access audio_codec_index_80h (@ 0x00000100).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000100) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b2_4_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 4st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_80h */
} audio_codec_index_80h_t, *paudio_codec_index_80h_t;

/**
  \brief Union type to access audio_codec_index_81h (@ 0x00000102).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000102) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b2_4_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 4st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_81h */
} audio_codec_index_81h_t, *paudio_codec_index_81h_t;

/**
  \brief Union type to access audio_codec_index_82h (@ 0x00000104).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000104) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a1_4_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 4st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_82h */
} audio_codec_index_82h_t, *paudio_codec_index_82h_t;

/**
  \brief Union type to access audio_codec_index_83h (@ 0x00000106).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000106) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a1_4_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 4st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_83h */
} audio_codec_index_83h_t, *paudio_codec_index_83h_t;

/**
  \brief Union type to access audio_codec_index_84h (@ 0x00000108).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000108) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a2_4_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 4st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_84h */
} audio_codec_index_84h_t, *paudio_codec_index_84h_t;

/**
  \brief Union type to access audio_codec_index_85h (@ 0x0000010A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000010A) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a2_4_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 4st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t dac_r_biquad_en_4 : 1;     /*!< [13..13] DAC Rch 4st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t dac_r_biquad_wclr_4 : 1;   /*!< [14..14] DAC Rch 4st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t dac_r_biquad_status_4 : 1; /*!< [15..15] DAC Rch 4st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_85h */
} audio_codec_index_85h_t, *paudio_codec_index_85h_t;

/**
  \brief Union type to access audio_codec_index_86h (@ 0x0000010C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000010C) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_h0_5_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 5st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_86h */
} audio_codec_index_86h_t, *paudio_codec_index_86h_t;

/**
  \brief Union type to access audio_codec_index_87h (@ 0x0000010E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000010E) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_h0_5_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 5st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_87h */
} audio_codec_index_87h_t, *paudio_codec_index_87h_t;

/**
  \brief Union type to access audio_codec_index_88h (@ 0x00000110).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000110) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b1_5_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 5st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_88h */
} audio_codec_index_88h_t, *paudio_codec_index_88h_t;

/**
  \brief Union type to access audio_codec_index_89h (@ 0x00000112).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000112) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b1_5_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 5st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_89h */
} audio_codec_index_89h_t, *paudio_codec_index_89h_t;

/**
  \brief Union type to access audio_codec_index_8ah (@ 0x00000114).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000114) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b2_5_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 5st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_8ah */
} audio_codec_index_8ah_t, *paudio_codec_index_8ah_t;

/**
  \brief Union type to access audio_codec_index_8bh (@ 0x00000116).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000116) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_b2_5_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 5st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_8bh */
} audio_codec_index_8bh_t, *paudio_codec_index_8bh_t;

/**
  \brief Union type to access audio_codec_index_8ch (@ 0x00000118).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000118) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a1_5_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 5st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_8ch */
} audio_codec_index_8ch_t, *paudio_codec_index_8ch_t;

/**
  \brief Union type to access audio_codec_index_8dh (@ 0x0000011A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000011A) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a1_5_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 5st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_8dh */
} audio_codec_index_8dh_t, *paudio_codec_index_8dh_t;

/**
  \brief Union type to access audio_codec_index_8eh (@ 0x0000011C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000011C) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a2_5_bit15to0 : 16;/*!< [15..0] DAC Rch EQ 5st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_8eh */
} audio_codec_index_8eh_t, *paudio_codec_index_8eh_t;

/**
  \brief Union type to access audio_codec_index_8fh (@ 0x0000011E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000011E) w                                                  */

  struct {
    __IOM uint16_t dac_r_biquad_a2_5_bit28to16 : 13;/*!< [12..0] DAC Rch EQ 5st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t dac_r_biquad_en_5 : 1;     /*!< [13..13] DAC Rch 5st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t dac_r_biquad_wclr_5 : 1;   /*!< [14..14] DAC Rch 5st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t dac_r_biquad_status_5 : 1; /*!< [15..15] DAC Rch 5st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_8fh */
} audio_codec_index_8fh_t, *paudio_codec_index_8fh_t;

/**
  \brief Union type to access audio_codec_index_90h (@ 0x00000120).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000120) w                                                  */

  struct {
    __IOM uint16_t adc_l_bq_eq_param_update : 1;/*!< [0..0] ADC Lch EQ Write 1 to send parameter update pluse 1'b0:
                                                   Busy (Waiting for cross) 1'b1: Stand-by                                   */
    __IOM uint16_t adc_l_bq_eq_cd_en : 1;     /*!< [1..1] ADC Lch EQ cross detection control 1'b0: Disable (Test
                                                   mode) 1'b1: Enable (Normal mode)                                          */
    __IOM uint16_t adc_l_bq_eq_dither_sel : 2;/*!< [3..2] ADC Lch EQ dither control 2'b00: Normal, 2'b01: LSB 2'b10:
                                                   {LSB+1, LSB}, 2'b11: {LSB+2, LSB+1, LSB}                                  */
    __IM  uint16_t            : 1;
    __IM  uint16_t adc_l_bq_eq_cd_flag : 1;   /*!< [5..5] ADC Lch Biquad filter cross detect status 1'b0: no data
                                                   zero cross 1'b1: data zero cross                                          */
  } b;                                        /*!< bit fields for audio_codec_index_90h */
} audio_codec_index_90h_t, *paudio_codec_index_90h_t;

/**
  \brief Union type to access audio_codec_index_91h (@ 0x00000122).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000122) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_h0_1_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 1st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_91h */
} audio_codec_index_91h_t, *paudio_codec_index_91h_t;

/**
  \brief Union type to access audio_codec_index_92h (@ 0x00000124).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000124) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_h0_1_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 1st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_92h */
} audio_codec_index_92h_t, *paudio_codec_index_92h_t;

/**
  \brief Union type to access audio_codec_index_93h (@ 0x00000126).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000126) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b1_1_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 1st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_93h */
} audio_codec_index_93h_t, *paudio_codec_index_93h_t;

/**
  \brief Union type to access audio_codec_index_94h (@ 0x00000128).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000128) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b1_1_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 1st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_94h */
} audio_codec_index_94h_t, *paudio_codec_index_94h_t;

/**
  \brief Union type to access audio_codec_index_95h (@ 0x0000012A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000012A) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b2_1_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 1st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_95h */
} audio_codec_index_95h_t, *paudio_codec_index_95h_t;

/**
  \brief Union type to access audio_codec_index_96h (@ 0x0000012C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000012C) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b2_1_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 1st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_96h */
} audio_codec_index_96h_t, *paudio_codec_index_96h_t;

/**
  \brief Union type to access audio_codec_index_97h (@ 0x0000012E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000012E) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a1_1_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 1st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_97h */
} audio_codec_index_97h_t, *paudio_codec_index_97h_t;

/**
  \brief Union type to access audio_codec_index_98h (@ 0x00000130).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000130) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a1_1_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 1st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_98h */
} audio_codec_index_98h_t, *paudio_codec_index_98h_t;

/**
  \brief Union type to access audio_codec_index_99h (@ 0x00000132).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000132) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a2_1_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 1st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_99h */
} audio_codec_index_99h_t, *paudio_codec_index_99h_t;

/**
  \brief Union type to access audio_codec_index_9ah (@ 0x00000134).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000134) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a2_1_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 1st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t adc_l_biquad_en_1 : 1;     /*!< [13..13] ADC Lch 1st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t adc_l_biquad_wclr_1 : 1;   /*!< [14..14] ADC Lch 1st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t adc_l_biquad_status_1 : 1; /*!< [15..15] ADC Lch 1st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_9ah */
} audio_codec_index_9ah_t, *paudio_codec_index_9ah_t;

/**
  \brief Union type to access audio_codec_index_9bh (@ 0x00000136).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000136) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_h0_2_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 2st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_9bh */
} audio_codec_index_9bh_t, *paudio_codec_index_9bh_t;

/**
  \brief Union type to access audio_codec_index_9ch (@ 0x00000138).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000138) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_h0_2_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 2st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_9ch */
} audio_codec_index_9ch_t, *paudio_codec_index_9ch_t;

/**
  \brief Union type to access audio_codec_index_9dh (@ 0x0000013A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000013A) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b1_2_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 2st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_9dh */
} audio_codec_index_9dh_t, *paudio_codec_index_9dh_t;

/**
  \brief Union type to access audio_codec_index_9eh (@ 0x0000013C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000013C) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b1_2_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 2st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_9eh */
} audio_codec_index_9eh_t, *paudio_codec_index_9eh_t;

/**
  \brief Union type to access audio_codec_index_9fh (@ 0x0000013E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000013E) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b2_2_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 2st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_9fh */
} audio_codec_index_9fh_t, *paudio_codec_index_9fh_t;

/**
  \brief Union type to access audio_codec_index_a0h (@ 0x00000140).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000140) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b2_2_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 2st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_a0h */
} audio_codec_index_a0h_t, *paudio_codec_index_a0h_t;

/**
  \brief Union type to access audio_codec_index_a1h (@ 0x00000142).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000142) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a1_2_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 2st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_a1h */
} audio_codec_index_a1h_t, *paudio_codec_index_a1h_t;

/**
  \brief Union type to access audio_codec_index_a2h (@ 0x00000144).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000144) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a1_2_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 2st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_a2h */
} audio_codec_index_a2h_t, *paudio_codec_index_a2h_t;

/**
  \brief Union type to access audio_codec_index_a3h (@ 0x00000146).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000146) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a2_2_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 2st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_a3h */
} audio_codec_index_a3h_t, *paudio_codec_index_a3h_t;

/**
  \brief Union type to access audio_codec_index_a4h (@ 0x00000148).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000148) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a2_2_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 2st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t adc_l_biquad_en_2 : 1;     /*!< [13..13] ADC Lch 2st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t adc_l_biquad_wclr_2 : 1;   /*!< [14..14] ADC Lch 2st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t adc_l_biquad_status_2 : 1; /*!< [15..15] ADC Lch 2st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_a4h */
} audio_codec_index_a4h_t, *paudio_codec_index_a4h_t;

/**
  \brief Union type to access audio_codec_index_a5h (@ 0x0000014A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000014A) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_h0_3_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 3st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_a5h */
} audio_codec_index_a5h_t, *paudio_codec_index_a5h_t;

/**
  \brief Union type to access audio_codec_index_a6h (@ 0x0000014C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000014C) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_h0_3_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 3st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_a6h */
} audio_codec_index_a6h_t, *paudio_codec_index_a6h_t;

/**
  \brief Union type to access audio_codec_index_a7h (@ 0x0000014E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000014E) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b1_3_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 3st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_a7h */
} audio_codec_index_a7h_t, *paudio_codec_index_a7h_t;

/**
  \brief Union type to access audio_codec_index_a8h (@ 0x00000150).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000150) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b1_3_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 3st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_a8h */
} audio_codec_index_a8h_t, *paudio_codec_index_a8h_t;

/**
  \brief Union type to access audio_codec_index_a9h (@ 0x00000152).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000152) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b2_3_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 3st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_a9h */
} audio_codec_index_a9h_t, *paudio_codec_index_a9h_t;

/**
  \brief Union type to access audio_codec_index_aah (@ 0x00000154).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000154) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b2_3_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 3st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_aah */
} audio_codec_index_aah_t, *paudio_codec_index_aah_t;

/**
  \brief Union type to access audio_codec_index_abh (@ 0x00000156).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000156) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a1_3_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 2st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_abh */
} audio_codec_index_abh_t, *paudio_codec_index_abh_t;

/**
  \brief Union type to access audio_codec_index_ach (@ 0x00000158).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000158) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a1_3_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 3st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_ach */
} audio_codec_index_ach_t, *paudio_codec_index_ach_t;

/**
  \brief Union type to access audio_codec_index_adh (@ 0x0000015A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000015A) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a2_3_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 3st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_adh */
} audio_codec_index_adh_t, *paudio_codec_index_adh_t;

/**
  \brief Union type to access audio_codec_index_aeh (@ 0x0000015C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000015C) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a2_3_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 3st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t adc_l_biquad_en_3 : 1;     /*!< [13..13] ADC Lch 3st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t adc_l_biquad_wclr_3 : 1;   /*!< [14..14] ADC Lch 3st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t adc_l_biquad_status_3 : 1; /*!< [15..15] ADC Lch 3st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_aeh */
} audio_codec_index_aeh_t, *paudio_codec_index_aeh_t;

/**
  \brief Union type to access audio_codec_index_afh (@ 0x0000015E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000015E) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_h0_4_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 4st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_afh */
} audio_codec_index_afh_t, *paudio_codec_index_afh_t;

/**
  \brief Union type to access audio_codec_index_b0h (@ 0x00000160).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000160) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_h0_4_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 4st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_b0h */
} audio_codec_index_b0h_t, *paudio_codec_index_b0h_t;

/**
  \brief Union type to access audio_codec_index_b1h (@ 0x00000162).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000162) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b1_4_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 4st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_b1h */
} audio_codec_index_b1h_t, *paudio_codec_index_b1h_t;

/**
  \brief Union type to access audio_codec_index_b2h (@ 0x00000164).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000164) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b1_4_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 4st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_b2h */
} audio_codec_index_b2h_t, *paudio_codec_index_b2h_t;

/**
  \brief Union type to access audio_codec_index_b3h (@ 0x00000166).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000166) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b2_4_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 4st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_b3h */
} audio_codec_index_b3h_t, *paudio_codec_index_b3h_t;

/**
  \brief Union type to access audio_codec_index_b4h (@ 0x00000168).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000168) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b2_4_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 4st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_b4h */
} audio_codec_index_b4h_t, *paudio_codec_index_b4h_t;

/**
  \brief Union type to access audio_codec_index_b5h (@ 0x0000016A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000016A) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a1_4_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 4st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_b5h */
} audio_codec_index_b5h_t, *paudio_codec_index_b5h_t;

/**
  \brief Union type to access audio_codec_index_b6h (@ 0x0000016C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000016C) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a1_4_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 4st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_b6h */
} audio_codec_index_b6h_t, *paudio_codec_index_b6h_t;

/**
  \brief Union type to access audio_codec_index_b7h (@ 0x0000016E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000016E) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a2_4_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 4st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_b7h */
} audio_codec_index_b7h_t, *paudio_codec_index_b7h_t;

/**
  \brief Union type to access audio_codec_index_b8h (@ 0x00000170).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000170) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a2_4_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 4st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t adc_l_biquad_en_4 : 1;     /*!< [13..13] ADC Lch 4st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t adc_l_biquad_wclr_4 : 1;   /*!< [14..14] ADC Lch 4st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t adc_l_biquad_status_4 : 1; /*!< [15..15] ADC Lch 4st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_b8h */
} audio_codec_index_b8h_t, *paudio_codec_index_b8h_t;

/**
  \brief Union type to access audio_codec_index_b9h (@ 0x00000172).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000172) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_h0_5_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 5st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_b9h */
} audio_codec_index_b9h_t, *paudio_codec_index_b9h_t;

/**
  \brief Union type to access audio_codec_index_bah (@ 0x00000174).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000174) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_h0_5_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 5st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_bah */
} audio_codec_index_bah_t, *paudio_codec_index_bah_t;

/**
  \brief Union type to access audio_codec_index_bbh (@ 0x00000176).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000176) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b1_5_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 5st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_bbh */
} audio_codec_index_bbh_t, *paudio_codec_index_bbh_t;

/**
  \brief Union type to access audio_codec_index_bch (@ 0x00000178).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000178) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b1_5_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 5st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_bch */
} audio_codec_index_bch_t, *paudio_codec_index_bch_t;

/**
  \brief Union type to access audio_codec_index_bdh (@ 0x0000017A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000017A) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b2_5_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 5st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_bdh */
} audio_codec_index_bdh_t, *paudio_codec_index_bdh_t;

/**
  \brief Union type to access audio_codec_index_beh (@ 0x0000017C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000017C) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_b2_5_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 5st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_beh */
} audio_codec_index_beh_t, *paudio_codec_index_beh_t;

/**
  \brief Union type to access audio_codec_index_bfh (@ 0x0000017E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000017E) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a1_5_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 5st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_bfh */
} audio_codec_index_bfh_t, *paudio_codec_index_bfh_t;

/**
  \brief Union type to access audio_codec_index_c0h (@ 0x00000180).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000180) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a1_5_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 5st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_c0h */
} audio_codec_index_c0h_t, *paudio_codec_index_c0h_t;

/**
  \brief Union type to access audio_codec_index_c1h (@ 0x00000182).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000182) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a2_5_bit15to0 : 16;/*!< [15..0] ADC Lch EQ 5st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_c1h */
} audio_codec_index_c1h_t, *paudio_codec_index_c1h_t;

/**
  \brief Union type to access audio_codec_index_c2h (@ 0x00000184).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000184) w                                                  */

  struct {
    __IOM uint16_t adc_l_biquad_a2_5_bit28to16 : 13;/*!< [12..0] ADC Lch EQ 5st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t adc_l_biquad_en_5 : 1;     /*!< [13..13] ADC Lch 5st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t adc_l_biquad_wclr_5 : 1;   /*!< [14..14] ADC Lch 5st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t adc_l_biquad_status_5 : 1; /*!< [15..15] ADC Lch 5st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_c2h */
} audio_codec_index_c2h_t, *paudio_codec_index_c2h_t;

/**
  \brief Union type to access audio_codec_index_c3h (@ 0x00000186).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000186) w                                                  */

  struct {
    __IOM uint16_t adc_r_bq_eq_param_update : 1;/*!< [0..0] ADC Rch EQ Write 1 to send parameter update pluse 1'b0:
                                                   Busy (Waiting for cross) 1'b1: Stand-by                                   */
    __IOM uint16_t adc_r_bq_eq_cd_en : 1;     /*!< [1..1] ADC Rch EQ cross detection control 1'b0: Disable (Test
                                                   mode) 1'b1: Enable (Normal mode)                                          */
    __IOM uint16_t adc_r_bq_eq_dither_sel : 2;/*!< [3..2] ADC Rch EQ dither control 2'b00: Normal, 2'b01: LSB 2'b10:
                                                   {LSB+1, LSB}, 2'b11: {LSB+2, LSB+1, LSB}                                  */
    __IM  uint16_t            : 1;
    __IM  uint16_t adc_r_bq_eq_cd_flag : 1;   /*!< [5..5] ADC Rch Biquad filter cross detect status 1'b0: no data
                                                   zero cross 1'b1: data zero cross                                          */
  } b;                                        /*!< bit fields for audio_codec_index_c3h */
} audio_codec_index_c3h_t, *paudio_codec_index_c3h_t;

/**
  \brief Union type to access audio_codec_index_c4h (@ 0x00000188).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000188) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_h0_1_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 1st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_c4h */
} audio_codec_index_c4h_t, *paudio_codec_index_c4h_t;

/**
  \brief Union type to access audio_codec_index_c5h (@ 0x0000018A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000018A) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_h0_1_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 1st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_c5h */
} audio_codec_index_c5h_t, *paudio_codec_index_c5h_t;

/**
  \brief Union type to access audio_codec_index_c6h (@ 0x0000018C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000018C) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b1_1_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 1st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_c6h */
} audio_codec_index_c6h_t, *paudio_codec_index_c6h_t;

/**
  \brief Union type to access audio_codec_index_c7h (@ 0x0000018E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000018E) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b1_1_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 1st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_c7h */
} audio_codec_index_c7h_t, *paudio_codec_index_c7h_t;

/**
  \brief Union type to access audio_codec_index_c8h (@ 0x00000190).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000190) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b2_1_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 1st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_c8h */
} audio_codec_index_c8h_t, *paudio_codec_index_c8h_t;

/**
  \brief Union type to access audio_codec_index_c9h (@ 0x00000192).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000192) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b2_1_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 1st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_c9h */
} audio_codec_index_c9h_t, *paudio_codec_index_c9h_t;

/**
  \brief Union type to access audio_codec_index_cah (@ 0x00000194).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000194) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a1_1_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 1st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_cah */
} audio_codec_index_cah_t, *paudio_codec_index_cah_t;

/**
  \brief Union type to access audio_codec_index_cbh (@ 0x00000196).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000196) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a1_1_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 1st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_cbh */
} audio_codec_index_cbh_t, *paudio_codec_index_cbh_t;

/**
  \brief Union type to access audio_codec_index_cch (@ 0x00000198).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x00000198) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a2_1_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 1st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_cch */
} audio_codec_index_cch_t, *paudio_codec_index_cch_t;

/**
  \brief Union type to access audio_codec_index_cdh (@ 0x0000019A).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000019A) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a2_1_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 1st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t adc_r_biquad_en_1 : 1;     /*!< [13..13] ADC Rch 1st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t adc_r_biquad_wclr_1 : 1;   /*!< [14..14] ADC Rch 1st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t adc_r_biquad_status_1 : 1; /*!< [15..15] ADC Rch 1st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_cdh */
} audio_codec_index_cdh_t, *paudio_codec_index_cdh_t;

/**
  \brief Union type to access audio_codec_index_ceh (@ 0x0000019C).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000019C) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_h0_2_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 2st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_ceh */
} audio_codec_index_ceh_t, *paudio_codec_index_ceh_t;

/**
  \brief Union type to access audio_codec_index_cfh (@ 0x0000019E).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x0000019E) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_h0_2_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 2st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_cfh */
} audio_codec_index_cfh_t, *paudio_codec_index_cfh_t;

/**
  \brief Union type to access audio_codec_index_d0h (@ 0x000001A0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001A0) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b1_2_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 2st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_d0h */
} audio_codec_index_d0h_t, *paudio_codec_index_d0h_t;

/**
  \brief Union type to access audio_codec_index_d1h (@ 0x000001A2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001A2) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b1_2_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 2st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_d1h */
} audio_codec_index_d1h_t, *paudio_codec_index_d1h_t;

/**
  \brief Union type to access audio_codec_index_d2h (@ 0x000001A4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001A4) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b2_2_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 2st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_d2h */
} audio_codec_index_d2h_t, *paudio_codec_index_d2h_t;

/**
  \brief Union type to access audio_codec_index_d3h (@ 0x000001A6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001A6) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b2_2_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 2st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_d3h */
} audio_codec_index_d3h_t, *paudio_codec_index_d3h_t;

/**
  \brief Union type to access audio_codec_index_d4h (@ 0x000001A8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001A8) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a1_2_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 2st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_d4h */
} audio_codec_index_d4h_t, *paudio_codec_index_d4h_t;

/**
  \brief Union type to access audio_codec_index_d5h (@ 0x000001AA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001AA) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a1_2_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 2st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_d5h */
} audio_codec_index_d5h_t, *paudio_codec_index_d5h_t;

/**
  \brief Union type to access audio_codec_index_d6h (@ 0x000001AC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001AC) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a2_2_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 2st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_d6h */
} audio_codec_index_d6h_t, *paudio_codec_index_d6h_t;

/**
  \brief Union type to access audio_codec_index_d7h (@ 0x000001AE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001AE) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a2_2_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 2st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t adc_r_biquad_en_2 : 1;     /*!< [13..13] ADC Rch 2st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t adc_r_biquad_wclr_2 : 1;   /*!< [14..14] ADC Rch 2st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t adc_r_biquad_status_2 : 1; /*!< [15..15] ADC Rch 2st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_d7h */
} audio_codec_index_d7h_t, *paudio_codec_index_d7h_t;

/**
  \brief Union type to access audio_codec_index_d8h (@ 0x000001B0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001B0) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_h0_3_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 3st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_d8h */
} audio_codec_index_d8h_t, *paudio_codec_index_d8h_t;

/**
  \brief Union type to access audio_codec_index_d9h (@ 0x000001B2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001B2) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_h0_3_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 3st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_d9h */
} audio_codec_index_d9h_t, *paudio_codec_index_d9h_t;

/**
  \brief Union type to access audio_codec_index_dah (@ 0x000001B4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001B4) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b1_3_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 3st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_dah */
} audio_codec_index_dah_t, *paudio_codec_index_dah_t;

/**
  \brief Union type to access audio_codec_index_dbh (@ 0x000001B6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001B6) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b1_3_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 3st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_dbh */
} audio_codec_index_dbh_t, *paudio_codec_index_dbh_t;

/**
  \brief Union type to access audio_codec_index_dch (@ 0x000001B8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001B8) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b2_3_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 3st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_dch */
} audio_codec_index_dch_t, *paudio_codec_index_dch_t;

/**
  \brief Union type to access audio_codec_index_ddh (@ 0x000001BA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001BA) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b2_3_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 3st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_ddh */
} audio_codec_index_ddh_t, *paudio_codec_index_ddh_t;

/**
  \brief Union type to access audio_codec_index_deh (@ 0x000001BC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001BC) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a1_3_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 3st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_deh */
} audio_codec_index_deh_t, *paudio_codec_index_deh_t;

/**
  \brief Union type to access audio_codec_index_dfh (@ 0x000001BE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001BE) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a1_3_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 3st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_dfh */
} audio_codec_index_dfh_t, *paudio_codec_index_dfh_t;

/**
  \brief Union type to access audio_codec_index_e0h (@ 0x000001C0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001C0) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a2_3_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 3st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_e0h */
} audio_codec_index_e0h_t, *paudio_codec_index_e0h_t;

/**
  \brief Union type to access audio_codec_index_e1h (@ 0x000001C2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001C2) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a2_3_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 3st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t adc_r_biquad_en_3 : 1;     /*!< [13..13] ADC Rch 3st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t adc_r_biquad_wclr_3 : 1;   /*!< [14..14] ADC Rch 3st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t adc_r_biquad_status_3 : 1; /*!< [15..15] ADC Rch 3st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_e1h */
} audio_codec_index_e1h_t, *paudio_codec_index_e1h_t;

/**
  \brief Union type to access audio_codec_index_e2h (@ 0x000001C4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001C4) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_h0_4_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 4st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_e2h */
} audio_codec_index_e2h_t, *paudio_codec_index_e2h_t;

/**
  \brief Union type to access audio_codec_index_e3h (@ 0x000001C6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001C6) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_h0_4_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 4st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_e3h */
} audio_codec_index_e3h_t, *paudio_codec_index_e3h_t;

/**
  \brief Union type to access audio_codec_index_e4h (@ 0x000001C8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001C8) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b1_4_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 4st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_e4h */
} audio_codec_index_e4h_t, *paudio_codec_index_e4h_t;

/**
  \brief Union type to access audio_codec_index_e5h (@ 0x000001CA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001CA) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b1_4_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 4st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_e5h */
} audio_codec_index_e5h_t, *paudio_codec_index_e5h_t;

/**
  \brief Union type to access audio_codec_index_e6h (@ 0x000001CC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001CC) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b2_4_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 4st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_e6h */
} audio_codec_index_e6h_t, *paudio_codec_index_e6h_t;

/**
  \brief Union type to access audio_codec_index_e7h (@ 0x000001CE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001CE) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b2_4_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 4st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_e7h */
} audio_codec_index_e7h_t, *paudio_codec_index_e7h_t;

/**
  \brief Union type to access audio_codec_index_e8h (@ 0x000001D0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001D0) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a1_4_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 4st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_e8h */
} audio_codec_index_e8h_t, *paudio_codec_index_e8h_t;

/**
  \brief Union type to access audio_codec_index_e9h (@ 0x000001D2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001D2) index_E9h                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a1_4_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 4st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_e9h */
} audio_codec_index_e9h_t, *paudio_codec_index_e9h_t;

/**
  \brief Union type to access audio_codec_index_eah (@ 0x000001D4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001D4) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a2_4_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 4st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_eah */
} audio_codec_index_eah_t, *paudio_codec_index_eah_t;

/**
  \brief Union type to access audio_codec_index_ebh (@ 0x000001D6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001D6) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a2_4_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 4st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t adc_r_biquad_en_4 : 1;     /*!< [13..13] ADC Rch 4st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t adc_r_biquad_wclr_4 : 1;   /*!< [14..14] ADC Rch 4st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t adc_r_biquad_status_4 : 1; /*!< [15..15] ADC Rch 4st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_ebh */
} audio_codec_index_ebh_t, *paudio_codec_index_ebh_t;

/**
  \brief Union type to access audio_codec_index_ech (@ 0x000001D8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001D8) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_h0_5_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 5st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_ech */
} audio_codec_index_ech_t, *paudio_codec_index_ech_t;

/**
  \brief Union type to access audio_codec_index_edh (@ 0x000001DA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001DA) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_h0_5_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 5st-band coef. h0 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_edh */
} audio_codec_index_edh_t, *paudio_codec_index_edh_t;

/**
  \brief Union type to access audio_codec_index_eeh (@ 0x000001DC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001DC) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b1_5_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 5st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_eeh */
} audio_codec_index_eeh_t, *paudio_codec_index_eeh_t;

/**
  \brief Union type to access audio_codec_index_efh (@ 0x000001DE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001DE) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b1_5_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 5st-band coef. b1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_efh */
} audio_codec_index_efh_t, *paudio_codec_index_efh_t;

/**
  \brief Union type to access audio_codec_index_f0h (@ 0x000001E0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001E0) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b2_5_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 5st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_f0h */
} audio_codec_index_f0h_t, *paudio_codec_index_f0h_t;

/**
  \brief Union type to access audio_codec_index_f1h (@ 0x000001E2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001E2) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_b2_5_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 5st-band coef. b2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_f1h */
} audio_codec_index_f1h_t, *paudio_codec_index_f1h_t;

/**
  \brief Union type to access audio_codec_index_f2h (@ 0x000001E4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001E4) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a1_5_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 5st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_f2h */
} audio_codec_index_f2h_t, *paudio_codec_index_f2h_t;

/**
  \brief Union type to access audio_codec_index_f3h (@ 0x000001E6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001E6) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a1_5_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 5st-band coef. a1 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_f3h */
} audio_codec_index_f3h_t, *paudio_codec_index_f3h_t;

/**
  \brief Union type to access audio_codec_index_f4h (@ 0x000001E8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001E8) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a2_5_bit15to0 : 16;/*!< [15..0] ADC Rch EQ 5st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
  } b;                                        /*!< bit fields for audio_codec_index_f4h */
} audio_codec_index_f4h_t, *paudio_codec_index_f4h_t;

/**
  \brief Union type to access audio_codec_index_f5h (@ 0x000001EA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001EA) w                                                  */

  struct {
    __IOM uint16_t adc_r_biquad_a2_5_bit28to16 : 13;/*!< [12..0] ADC Rch EQ 5st-band coef. a2 2's complement in 4.25
                                                   format, i.e. the range is from -8~7.99.                                   */
    __IOM uint16_t adc_r_biquad_en_5 : 1;     /*!< [13..13] ADC Rch 5st-band EQ biquad control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __OM  uint16_t adc_r_biquad_wclr_5 : 1;   /*!< [14..14] ADC Rch 5st-band Biquad filter write clear 1'b0: Normal
                                                   1'b1: Overflow Write 1 to send clear status pluse                         */
    __IM  uint16_t adc_r_biquad_status_5 : 1; /*!< [15..15] ADC Rch 5st-band Biquad filter status 1'b0: Normal
                                                   1'b1: Overflow                                                            */
  } b;                                        /*!< bit fields for audio_codec_index_f5h */
} audio_codec_index_f5h_t, *paudio_codec_index_f5h_t;

/**
  \brief Union type to access audio_codec_index_f6h (@ 0x000001EC).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001EC) w                                                  */

  struct {
    __IOM uint16_t dac_l_silence_det_mono_en : 1;/*!< [0..0] dac_l_silence data detection enable contorl 1'b0: diable
                                                   dac_l_silence data detection 1'b1: enable dac_l_silence
                                                   data detection                                                            */
    __IOM uint16_t dac_l_silence_det_mono_auto_en : 1;/*!< [1..1] dac_l_silence data dete threshold automatically control
                                                   1'b0: dac_l_silence data threshold is determined by dac_l_silence_mono_le
                                                   el_sel 1'b1: dac_l_silence data threshold is determined
                                                   by dac_l_silence_mono_data_bit                                            */
    __IOM uint16_t dac_l_silence_mono_data_bit : 2;/*!< [3..2] dac_l_silence detection input data word length 2'b00:
                                                   16-bits, corresponding to dac_l_silence data threshold=-78db;
                                                   2'b01: 20-bits, corresponding to dac_l_silence data threshold=-102db;
                                                   2'b10: 24-bits, corresponding to dac_l_silence data threshold=-126db;
                                                   2'b11: 24-bits, corresponding to dac_l_silence data threshold=-126db;     */
    __IOM uint16_t dac_l_silence_mono_level_sel : 3;/*!< [6..4] dac_l_silence data detection threshold register control
                                                   3'b000: -78 db ; 3'b001: -84 db ; 3'b010: -90 db ; 3'b011:
                                                   -102db 3'b100: -108db ; 3'b101: -114db ; 3'b110: -126db
                                                   ; 3'b111: -132db                                                          */
    __IOM uint16_t dac_l_silence_mono_debounce_sel : 3;/*!< [9..7] dac_l_silence data detection debounce control 3'b000:
                                                   debounce 80ms at sample rate 48k 3'b001: debounce 160ms
                                                   at sample rate 48k 3'b010: debounce 320ms at sample rate
                                                   48k 3'b011: debounce 640ms at sample rate 48k 3'b100: debounce
                                                   1.28 s at sample rate 48k 3'b101: debounce 2.56 s at sample
                                                   rate 48k 3'b110: debounce 5.12 s at sample rate 48k 3'b111:
                                                   debounce 0.16ms at sample rate 48k (test mode)                            */
    __IM  uint16_t dac_l_silence_det_mono_o : 1;/*!< [10..10] dac_l_silence data status (result of silence detection)
                                                   1'b0: not dac_l_silence data ; 1'b1: dac_l_silence is detected            */
    __IM  uint16_t dac_l_silenece_det_mono_status : 1;/*!< [11..11] ongoing status of dac_l_silence detection 1'b0: dac_l_silence
                                                   detection is resting (clk is gating) 1'b1: dac_l_silence
                                                   detection is working                                                      */
  } b;                                        /*!< bit fields for audio_codec_index_f6h */
} audio_codec_index_f6h_t, *paudio_codec_index_f6h_t;

/**
  \brief Union type to access audio_codec_index_f7h (@ 0x000001EE).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001EE) w                                                  */

  struct {
    __IOM uint16_t dac_r_silence_det_mono_en : 1;/*!< [0..0] dac_r_silence data detection enable contorl 1'b0: diable
                                                   dac_r_silence data detection 1'b1: enable dac_r_silence
                                                   data detection                                                            */
    __IOM uint16_t dac_r_silence_det_mono_auto_en : 1;/*!< [1..1] dac_r_silence data dete threshold automatically control
                                                   1'b0: dac_r_silence data threshold is determined by dac_r_silence_mono_le
                                                   el_sel 1'b1: dac_r_silence data threshold is determined
                                                   by dac_r_silence_mono_data_bit                                            */
    __IOM uint16_t dac_r_silence_mono_data_bit : 2;/*!< [3..2] dac_r_silence detection input data word length 2'b00:
                                                   16-bits, corresponding to dac_r_silence data threshold=-78db;
                                                   2'b01: 20-bits, corresponding to dac_r_silence data threshold=-102db;
                                                   2'b10: 24-bits, corresponding to dac_r_silence data threshold=-126db;
                                                   2'b11: 24-bits, corresponding to dac_r_silence data threshold=-126db;     */
    __IOM uint16_t dac_r_silence_mono_level_sel : 3;/*!< [6..4] dac_r_silence data detection threshold register control
                                                   3'b000: -78 db ; 3'b001: -84 db ; 3'b010: -90 db ; 3'b011:
                                                   -102db 3'b100: -108db ; 3'b101: -114db ; 3'b110: -126db
                                                   ; 3'b111: -132db                                                          */
    __IOM uint16_t dac_r_silence_mono_debounce_sel : 3;/*!< [9..7] dac_r_silence data detection debounce control 3'b000:
                                                   debounce 80ms at sample rate 48k 3'b001: debounce 160ms
                                                   at sample rate 48k 3'b010: debounce 320ms at sample rate
                                                   48k 3'b011: debounce 640ms at sample rate 48k 3'b100: debounce
                                                   1.28 s at sample rate 48k 3'b101: debounce 2.56 s at sample
                                                   rate 48k 3'b110: debounce 5.12 s at sample rate 48k 3'b111:
                                                   debounce 0.16ms at sample rate 48k (test mode)                            */
    __IM  uint16_t dac_r_silence_det_mono_o : 1;/*!< [10..10] dac_r_silence data status (result of silence detection)
                                                   1'b0: not dac_r_silence data ; 1'b1: dac_r_silence is detected            */
    __IM  uint16_t dac_r_silenece_det_mono_status : 1;/*!< [11..11] ongoing status of dac_r_silence detection 1'b0: dac_r_silence
                                                   detection is resting (clk is gating) 1'b1: dac_r_silence
                                                   detection is working                                                      */
  } b;                                        /*!< bit fields for audio_codec_index_f7h */
} audio_codec_index_f7h_t, *paudio_codec_index_f7h_t;

/**
  \brief Union type to access audio_codec_index_f8h (@ 0x000001F0).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001F0) w                                                  */

  struct {
    __IOM uint16_t adc_l_silence_det_mono_en : 1;/*!< [0..0] adc_l_silence data detection enable contorl 1'b0: diable
                                                   adc_l_silence data detection 1'b1: enable adc_l_silence
                                                   data detection                                                            */
    __IOM uint16_t adc_l_silence_det_mono_auto_en : 1;/*!< [1..1] adc_l_silence data dete threshold automatically control
                                                   1'b0: adc_l_silence data threshold is register controlled
                                                   1'b1: adc_l_silence data threshold is automatically controlled            */
    __IOM uint16_t adc_l_silence_mono_data_bit : 2;/*!< [3..2] adc_l_silence detection input data word length 2'b00:
                                                   16-bits ; 2'b01: 20-bits ; 2'b10: 24-bits; 2'b11: 24-bits                 */
    __IOM uint16_t adc_l_silence_mono_level_sel : 3;/*!< [6..4] adc_l_silence data detection threshold register control
                                                   3'b000: -78 db ; 3'b001: -84 db ; 3'b010: -90 db ; 3'b011:
                                                   -102db 3'b100: -108db ; 3'b101: -114db ; 3'b110: -126db
                                                   ; 3'b111: -132db                                                          */
    __IOM uint16_t adc_l_silence_mono_debounce_sel : 3;/*!< [9..7] adc_l_silence data detection debounce control 3'b000:
                                                   debounce 80ms at sample rate 48k 3'b001: debounce 160ms
                                                   at sample rate 48k 3'b010: debounce 320ms at sample rate
                                                   48k 3'b011: debounce 640ms at sample rate 48k 3'b100: debounce
                                                   1.28 s at sample rate 48k 3'b101: debounce 2.56 s at sample
                                                   rate 48k 3'b110: debounce 5.12 s at sample rate 48k 3'b111:
                                                   debounce 0.16ms at sample rate 48k (test mode)                            */
    __IM  uint16_t adc_l_silence_det_mono_o : 1;/*!< [10..10] adc_l_silence data status 1'b0: not adc_l_silence data
                                                   ; 1'b1: adc_l_silence is detected                                         */
    __IM  uint16_t adc_l_silenece_det_mono_status : 1;/*!< [11..11] status of adc_l_silence detection 1'b0: adc_l_silence
                                                   detection is resting (clk is gating) 1'b1: adc_l_silence
                                                   detection is working                                                      */
  } b;                                        /*!< bit fields for audio_codec_index_f8h */
} audio_codec_index_f8h_t, *paudio_codec_index_f8h_t;

/**
  \brief Union type to access audio_codec_index_f9h (@ 0x000001F2).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001F2) w                                                  */

  struct {
    __IOM uint16_t adc_r_silence_det_mono_en : 1;/*!< [0..0] adc_r_silence data detection enable contorl 1'b0: diable
                                                   adc_r_silence data detection 1'b1: enable adc_r_silence
                                                   data detection                                                            */
    __IOM uint16_t adc_r_silence_det_mono_auto_en : 1;/*!< [1..1] adc_r_silence data dete threshold automatically control
                                                   1'b0: adc_r_silence data threshold is register controlled
                                                   1'b1: adc_r_silence data threshold is automatically controlled            */
    __IOM uint16_t adc_r_silence_mono_data_bit : 2;/*!< [3..2] adc_r_silence detection input data word length 2'b00:
                                                   16-bits ; 2'b01: 20-bits ; 2'b10: 24-bits; 2'b11: 24-bits                 */
    __IOM uint16_t adc_r_silence_mono_level_sel : 3;/*!< [6..4] adc_r_silence data detection threshold register control
                                                   3'b000: -78 db ; 3'b001: -84 db ; 3'b010: -90 db ; 3'b011:
                                                   -102db 3'b100: -108db ; 3'b101: -114db ; 3'b110: -126db
                                                   ; 3'b111: -132db                                                          */
    __IOM uint16_t adc_r_silence_mono_debounce_sel : 3;/*!< [9..7] adc_r_silence data detection debounce control 3'b000:
                                                   debounce 80ms at sample rate 48k 3'b001: debounce 160ms
                                                   at sample rate 48k 3'b010: debounce 320ms at sample rate
                                                   48k 3'b011: debounce 640ms at sample rate 48k 3'b100: debounce
                                                   1.28 s at sample rate 48k 3'b101: debounce 2.56 s at sample
                                                   rate 48k 3'b110: debounce 5.12 s at sample rate 48k 3'b111:
                                                   debounce 0.16ms at sample rate 48k (test mode)                            */
    __IM  uint16_t adc_r_silence_det_mono_o : 1;/*!< [10..10] adc_r_silence data status 1'b0: not adc_r_silence data
                                                   ; 1'b1: adc_r_silence is detected                                         */
    __IM  uint16_t adc_r_silenece_det_mono_status : 1;/*!< [11..11] status of adc_r_silence detection 1'b0: adc_r_silence
                                                   detection is resting (clk is gating) 1'b1: adc_r_silence
                                                   detection is working                                                      */
  } b;                                        /*!< bit fields for audio_codec_index_f9h */
} audio_codec_index_f9h_t, *paudio_codec_index_f9h_t;

/**
  \brief Union type to access audio_codec_index_fah (@ 0x000001F4).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001F4) w                                                  */

  struct {
    __IOM uint16_t dac_l_da_gain : 8;         /*!< [7..0] mon DAC Lch dvol gain control (0.375dB/step) 8'hAF: 0dB
                                                   8'h00: -65.625dB                                                          */
    __IOM uint16_t dac_l_dahpf_en : 1;        /*!< [8..8] mon DAC Lch Narrow-band 1st HPF enable control 1'b0:
                                                   Disable 1'b1: Enable                                                      */
    __IOM uint16_t dac_l_da_dither_sel : 2;   /*!< [10..9] mon DAC Lch dither select 2'b00: disable 2'b01: LSB
                                                   2'b10: LSB+1 2'b11: LSB+2                                                 */
    __IOM uint16_t dac_l_da_zdet_func : 2;    /*!< [12..11] mon DAC Lch Zero detection function mode control 2'b00:
                                                   Immediate change 2'b01: Zero detection and immediate change
                                                   2'b10: Zero detection and increase/decrease change 2'b11:
                                                   N/A                                                                       */
    __IOM uint16_t dac_l_da_zdet_tout : 2;    /*!< [14..13] mon DAC Lch Zero detection time out mode control 2'b00:
                                                   1024*16 samples 2'b01: 1024*32 samples 2'b10: 1024*64 samples
                                                   2'b11: 256 samples                                                        */
    __IOM uint16_t dac_l_dmix_in_sel : 1;     /*!< [15..15] mon DAC Lch Upsample filter input select 1'b0: alc
                                                   output 1'b1: mono dac volume output                                       */
  } b;                                        /*!< bit fields for audio_codec_index_fah */
} audio_codec_index_fah_t, *paudio_codec_index_fah_t;

/**
  \brief Union type to access audio_codec_index_fbh (@ 0x000001F6).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001F6) w                                                  */

  struct {
    __IOM uint16_t dac_l_da_mute : 1;         /*!< [0..0] mon DAC Lch dvol mute enable 1'b0: unmute 1'b1: mute               */
    __IOM uint16_t daad_lpbk_en : 1;          /*!< [1..1] Digital DAC & ADC loop back control 1'b0: Disable 1'b1:
                                                   Enable                                                                    */
    __IOM uint16_t dac_l_dmix_mute_128fs_da : 1;/*!< [2..2] mon DAC Lch 128fs-domain mixer da path mute enable 1'b0:
                                                   unmute 1'b1: mute                                                         */
    __IOM uint16_t dac_l_dmix_mute_128fs_sidetone : 1;/*!< [3..3] mon DAC Lch 128fs-domain mixer sidetone path mute enable
                                                   1'b0: unmute 1'b1: mute                                                   */
  } b;                                        /*!< bit fields for audio_codec_index_fbh */
} audio_codec_index_fbh_t, *paudio_codec_index_fbh_t;

/**
  \brief Union type to access audio_codec_index_fch (@ 0x000001F8).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001F8) w                                                  */

  struct {
    __IOM uint16_t dac_r_da_gain : 8;         /*!< [7..0] mon DAC Rch dvol gain control (0.375dB/step) 8'hAF: 0dB
                                                   8'h00: -65.625dB                                                          */
    __IOM uint16_t dac_r_dahpf_en : 1;        /*!< [8..8] mon DAC Rch Narrow-band 1st HPF enable control 1'b0:
                                                   Disable 1'b1: Enable                                                      */
    __IOM uint16_t dac_r_da_dither_sel : 2;   /*!< [10..9] mon DAC Rch dither select 2'b00: disable 2'b01: LSB
                                                   2'b10: LSB+1 2'b11: LSB+2                                                 */
    __IOM uint16_t dac_r_da_zdet_func : 2;    /*!< [12..11] mon DAC Rch Zero detection function mode control 2'b00:
                                                   Immediate change 2'b01: Zero detection and immediate change
                                                   2'b10: Zero detection and increase/decrease change 2'b11:
                                                   N/A                                                                       */
    __IOM uint16_t dac_r_da_zdet_tout : 2;    /*!< [14..13] mon DAC Rch Zero detection time out mode control 2'b00:
                                                   1024*16 samples 2'b01: 1024*32 samples 2'b10: 1024*64 samples
                                                   2'b11: 256 samples                                                        */
    __IOM uint16_t dac_r_dmix_in_sel : 1;     /*!< [15..15] mon DAC Rch Upsample filter input select 1'b0: alc
                                                   output 1'b1: mono dac volume output                                       */
  } b;                                        /*!< bit fields for audio_codec_index_fch */
} audio_codec_index_fch_t, *paudio_codec_index_fch_t;

/**
  \brief Union type to access audio_codec_index_fdh (@ 0x000001FA).
*/
typedef union {
  __IOM uint16_t w;                           /*!< (@ 0x000001FA) w                                                  */

  struct {
    __IOM uint16_t dac_r_da_mute : 1;         /*!< [0..0] mon DAC Rch dvol mute enable 1'b0: unmute 1'b1: mute               */

    __IM  uint16_t            : 1;
    __IOM uint16_t dac_r_dmix_mute_128fs_da : 1;/*!< [2..2] mon DAC Rch 128fs-domain mixer da path mute enable 1'b0:
                                                   unmute 1'b1: mute                                                         */
    __IOM uint16_t dac_r_dmix_mute_128fs_sidetone : 1;/*!< [3..3] mon DAC Rch 128fs-domain mixer sidetone path mute enable
                                                   1'b0: unmute 1'b1: mute                                                   */
  } b;                                        /*!< bit fields for audio_codec_index_fdh */
} audio_codec_index_fdh_t, *paudio_codec_index_fdh_t;

/** @} */ /* End of group hs_hal_audio_reg */
/// @endcond /* End of condition DOXYGEN_GENERAL_REG_TYPE || DOXYGEN_AUDIO_REG_TYPE */


#ifdef  __cplusplus
}
#endif

#endif    // end of #ifndef _RTL8195BHP_AUDIO_CODEC_TYPE_H_

