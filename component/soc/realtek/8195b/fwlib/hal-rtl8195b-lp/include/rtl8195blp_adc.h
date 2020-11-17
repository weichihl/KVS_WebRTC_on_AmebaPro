/**************************************************************************//**
 * @file     rtl819blp_adc.h
 * @brief    The fundamental definition for RTL8195B LP ADC module.
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

#ifndef _RTL8195BLP_ADC_H_
#define _RTL8195BLP_ADC_H_

#include "rtl8195blp_adc_type.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup ls_hal_adc ADC
 * @{
 */

//#define LOCAL_SVD_DECLARATION
#undef LOCAL_SVD_DECLARATION
//#define ADC_SW_DATA_PATCH
#undef ADC_SW_DATA_PATCH
#define ADC_BUSY_PATCH
//#undef ADC_BUSY_PATCH
//#define ADC_FULL_STS_PATCH
#undef ADC_FULL_STS_PATCH
//#define ADC_LAST_ITEM_PATCH
#undef ADC_LAST_ITEM_PATCH

//#define ADC_DIFF45_PATCH
#undef ADC_DIFF45_PATCH
//#define ADC_RULE_PATCH
#undef ADC_RULE_PATCH

//#define ADC_DMA_PATCH
#undef ADC_DMA_PATCH
//#define ADC_NULL_CHANNEL_PATCH
#undef ADC_NULL_CHANNEL_PATCH


/*  Macros for adc related constant  */
/// lp adc total channel number (internal + external)
#define LP_ADC_CH_NO            10
/// lp adc external channel number
#define LP_ADC_EXCH_NO          7
/// lp adc dual input channel input number
#define LP_ADC_DUAL_IN_CH       5
/// lp adc hardware list item number
#define LP_ADC_LIST_LEN         16
/// lp adc hardware list item number in half
#define LP_ADC_LIST_HALF        8
/// lp adc IRQ Priority
#define LP_ADC_IRQ_PR           3
/// lp adc resolution bit number
#define LP_ADC_RESOLUTION       10
#ifdef ADC_SW_DATA_PATCH
#define LP_ADC_DATA_MASK        0xFC00
#else
/// lp adc data mask
#define LP_ADC_DATA_MASK        0x3FF
#endif
/// lp adc FIFO length
#define LP_ADC_FIFO_LEN         64
/// lp adc code max value
#define LP_ADC_CODE_MAX         0x3FF
#ifdef ADC_RULE_PATCH
/// lp adc rule number
#define LP_ADC_COMP_RULE        3
#else
/// lp adc rule number
#define LP_ADC_COMP_RULE        4
#endif
/// lp adc default DMA RX des width
#define LP_ADC_DMA_DEFAULT_RX_DES_WIDTH 4
/// lp adc channel index mask
#define LP_ADC_CHIDX_MASK       0x3C00
/// lp adc disable timeout
#define LP_ADC_TIMEOUT_DISABLE  0x0
/// lp adc endless timeout
#define LP_ADC_TIMEOUT_ENDLESS  0xFFFFFFFF
/// lp adc input all single-end type
#define LP_ADC_INPUT_ALL_SINGLE 0

/// lp adc calculating scale
#define LP_ADC_CALC_SCLE        1024

/// lp adc constant value
#define LP_ADC_FUSE_VAL         0x50300000

#define LP_ADC_GAIN_DENO_ADDR   0x1D0

#define LP_ADC_GAIN_MOLE_ADDR   0x1D2

#define LP_ADC_OFFSET_DENO_ADDR 0x1D4

#define LP_ADC_OFFSET_MOLE_ADDR 0x1D8


/*  Macros for adc reigster access  */
/** @defgroup adc_reg_access_macro ADC REG ACCESS MACRO
 *  adc register access macro
 *  @{
 */
#define ADC_BASE_REG ((volatile ADC_Type *)(0))
#define HAL_ADC_READ32(base, offset) rtk_le32_to_cpu(*((volatile uint32_t*)(base + offset)))
#define HAL_ADC_WRITE32(base, offset, value) ((*((volatile uint32_t*)(base + offset))) = rtk_cpu_to_le32(value))
#define READ_CLEAR_ADC_REG(base, reg_name)   base->reg_name
/** @} */ // end of ADC REG ACCESS MACRO

/** \brief adc feature status
*/
enum adc_enable_status_e {
    ADCDisable      =   0,                  /*!< 0: for adc disable state    */
    ADCEnable       =   1,                  /*!< 1: for adc enable state    */
};

/** \brief adc conversion trigger mode
*/
enum adc_trigger_mode_e {
    ADCSWTrigMod    =   0,                  /*!< 0: for adc software trigger mode    */
    ADCAutoMod      =   1,                  /*!< 1: for adc automatic trigger mode    */
    ADCTmTrigMod    =   2,                  /*!< 1: for adc timer trigger mode    */
    ADCCompTrigMod  =   3,                  /*!< 1: for adc comparator trigger mode    */
};

/** \brief adc channel input type
*/
enum adc_input_type_e {
    ADCSingleInput          =   0,          /*!< 0: for adc single end input    */
    ADCDifferentialInput    =   1,          /*!< 1: for adc differentail input    */
};

/** \brief adc module state
*/
enum adc_status_e {
    ADCStatusUninitial      =   0x00,               /*!< 0x00: adc uninitial state   */
    ADCStatusInitialized    =   0x01,               /*!< 0x01: adc initialized state   */
    ADCStatusIdle           =   0x02,               /*!< 0x02: adc idle state   */

    ADCStatusCVReady        =   0x03,               /*!< 0x03: adc conversion ready state   */
    ADCStatusCVing          =   0x04,               /*!< 0x04: adc processing conversion state   */

    ADCStatusError          =   0x10,               /*!< 0x10: adc error state   */
    ADCStatusTimeOut        =   0x11,               /*!< 0x11: adc time-out state   */
};

/** \brief adc module error type
*/
enum adc_err_type_e {
    ADCErrorNone            =   0x00,               /*!< 0x00: adc has no errors    */
    ADCErrorFFOver          =   0x01,               /*!< 0x01: adc has fifo overflow error1    */
    ADCErrorFFUnder         =   0x02,               /*!< 0x02: adc has fifo underflow errors    */
    ADCErrorDatOverWrite    =   0x03,               /*!< 0x03: adc has data over written errors    */
    ADCErrorUnknown         =   0x04,               /*!< 0x04: adc has unknown errors    */

};

/** \brief adc module clock division option
*/
enum adc_clock_div_e {
    ADCClockDiv125          =   0x00,               /*!< 0x00: adc clock is divided by 12.5   */
    ADCClockDiv16           =   0x01,               /*!< 0x01: adc clock is divided by 16    */
    ADCClockDiv32           =   0x02,               /*!< 0x02: adc clock is divided by 32    */
    ADCClockDiv64           =   0x03,               /*!< 0x03: adc clock is divided by 64    */
};

/** \brief adc dma channel status
*/
enum adc_dma_ch_status_e {
    ADCDmaChNone            =   0x00,               /*!< 0x00: adc got no channel    */
    ADCDmaChGot             =   0x01,               /*!< 0x01: adc got a channel    */
    ADCDmaChInitialed       =   0x02,               /*!< 0x02: adc got a channel and initialized it    */
};

/** \brief adc interrupt type
*/
enum adc_interrupt_type_e {
    ADCIntrCVlistEnd        =   0x00,               /*!< 0x00: adc conversion list end interrupt    */
    ADCIntrCVEnd            =   0x01,               /*!< 0x01: adc conversion end interrupt    */
    ADCIntrChCVEnd          =   0x02,               /*!< 0x02: adc particular channel conversion end interrupt    */
    ADCIntrFull             =   0x03,               /*!< 0x03: adc FIFO full interrupt    */
    ADCIntrOver             =   0x04,               /*!< 0x04: adc FIFO overflow interrupt    */
    ADCIntrEmpty            =   0x05,               /*!< 0x05: adc FIFO empty interrupt    */
    ADCIntrDatOvw           =   0x06,               /*!< 0x06: adc data overwritten interrupt    */
    ADCIntrErr              =   0x07,               /*!< 0x07: adc error interrupt    */
    ADCIntrCompch0          =   0x08,               /*!< 0x08: adc channel 0 comparison match interrupt    */
    ADCIntrCompch1          =   0x09,               /*!< 0x09: adc channel 1 comparison match interrupt    */
    ADCIntrCompch2          =   0x0A,               /*!< 0x0A: adc channel 2 comparison match interrupt    */
    ADCIntrCompch3          =   0x0B,               /*!< 0x0B: adc channel 3 comparison match interrupt    */
    ADCIntrCompch4          =   0x0C,               /*!< 0x0C: adc channel 4 comparison match interrupt    */
    ADCIntrCompch5          =   0x0D,               /*!< 0x0D: adc channel 5 comparison match interrupt    */
    ADCIntrCompch6          =   0x0E,               /*!< 0x0E: adc channel 6 comparison match interrupt    */
    ADCIntrCompch7          =   0x0F,               /*!< 0x0F: adc channel 7 comparison match interrupt    */
    ADCIntrCompch8          =   0x10,               /*!< 0x10: adc channel 8 comparison match interrupt    */
    ADCIntrCompch9          =   0x11,               /*!< 0x11: adc channel 9 comparison match interrupt    */
};

/** \brief adc initial data structure */
typedef struct adc_init_dat_s {
    uint8_t     enable;                         /*!< Offset: 0x000   adc enable state, updated by HAL   */
    uint8_t     hw_mode;                        /*!< Offset: 0x001   adc hardware operation mode   */
    uint8_t     cvlist_len;                     /*!< Offset: 0x002   adc conversion list length, 0 for 1 entry,
                                                                     same as hardware. */
    uint8_t     it_chno_cv;                     /*!< Offset: 0x003   adc conversion channel number   */

    uint8_t     ff_tl;                          /*!< Offset: 0x004   adc fifo full threshold   */
    uint8_t     trig_timer;                     /*!< Offset: 0x005   adc conversion trigger timer   */
    uint8_t     clock_div;                      /*!< Offset: 0x006   adc input clock divider   */
    uint8_t     dma_rq_lv;                      /*!< Offset: 0x007   adc dma request level   */

    uint8_t     ref_lvl;                        /*!< Offset: 0x008   adc reference voltage level   */
    uint8_t     use_dly;                        /*!< Offset: 0x009   adc use trig delay   */
    uint16_t    trig_dly;                       /*!< Offset: 0x00a   adc trig delay   */

    ADC_Type    *reg_base;                      /*!< Offset: 0x00c   adc register base address   */
}adc_init_dat_t, *padc_init_dat_t;


/** \brief adc dma information
*/
typedef struct adc_dma_info_s {
    hal_gdma_adaptor_t  *padaptor;                  /*! adc dma adaptor pointer    */
    irq_config_t        irq_config;                 /*! adc dma interrupt handler     */
    uint8_t             ch_sts;                     /*! adc dma channel status (adc local)     */
}adc_dma_info_t,*padc_dma_info_t;

/** \brief adc user callback adaptor
*/
typedef struct adc_user_callback_adpt_s {
    VOID (*cb)      (VOID *data);                   /*! adc callback function */
    uint32_t        dat;                            /*! adc callback function argument */
}adc_user_callback_adpt_t, *padc_user_callback_adpt_t;

/** \brief  lp adc pinmux enable structure.
 */
typedef union {
    uint32_t w;                             /*!< (@ 0x00000000) LP ADC pinmux enable      */

    struct {
        uint32_t adc0 : 1;                  /*!< (@ 0x00000000) ADC0 pinmux enable        */
        uint32_t adc1 : 1;                  /*!< (@ 0x00000001) ADC1 pinmux enable        */
        uint32_t adc2 : 1;                  /*!< (@ 0x00000002) ADC2 pinmux enable        */
        uint32_t adc3 : 1;                  /*!< (@ 0x00000003) ADC3 pinmux enable        */
        uint32_t adc4 : 1;                  /*!< (@ 0x00000004) ADC4 pinmux enable        */
        uint32_t adc5 : 1;                  /*!< (@ 0x00000005) ADC5 pinmux enable        */
        uint32_t adc6 : 1;                  /*!< (@ 0x00000006) ADC6 pinmux enable        */
    } b;
} lp_adc_pin_en_t, *plp_adc_pin_en_t;


/** \brief adc platform related data
*/
typedef struct adc_platform_data_s {
    uint32_t        rx_dma_bound;                   /*! adc low bound to do rx-dma transmission,
                                                        if rx len is more than this bound, rx API
                                                        would change to poll mode transmission.*/
    uint32_t        tr_time_out;                    /*! adc transfer time-out count */
    lp_adc_pin_en_t pin_en;                         /*! adc channel pinmux enable */
}adc_platform_data_t,*padc_platform_data_t;


/** \brief adc user callback
*/
typedef struct adc_user_callback_s {
    adc_user_callback_adpt_t  ch0_comp;             /*! adc ch0 comparison match callback */
    adc_user_callback_adpt_t  ch1_comp;             /*! adc ch1 comparison match callback */
    adc_user_callback_adpt_t  ch2_comp;             /*! adc ch2 comparison match callback */
    adc_user_callback_adpt_t  ch3_comp;             /*! adc ch3 comparison match callback */
    adc_user_callback_adpt_t  ch4_comp;             /*! adc ch4 comparison match callback */
    adc_user_callback_adpt_t  ch5_comp;             /*! adc ch5 comparison match callback */
    adc_user_callback_adpt_t  ch6_comp;             /*! adc ch6 comparison match callback */
    adc_user_callback_adpt_t  ch7_comp;             /*! adc ch7 comparison match callback */
    adc_user_callback_adpt_t  ch8_comp;             /*! adc ch8 comparison match callback */
    adc_user_callback_adpt_t  ch9_comp;             /*! adc ch9 comparison match callback */
    adc_user_callback_adpt_t  err;                  /*! adc error callback */
    adc_user_callback_adpt_t  full;                 /*! adc fifo full callback */
    adc_user_callback_adpt_t  empty;                /*! adc fifo empty callback */
    adc_user_callback_adpt_t  cv_end;               /*! adc conversion end callback */
    adc_user_callback_adpt_t  ch_cv_end;            /*! adc particular channel conversion end callback */
    adc_user_callback_adpt_t  cvlist_end;           /*! adc conversion list end callback */
    adc_user_callback_adpt_t  rxc;                  /*! adc dma receive complete callback */
    adc_user_callback_adpt_t  wake;                 /*! adc wake up callback */
}adc_user_callback_t, *padc_user_callback_t;

/** \brief adc control adapter
*/
typedef struct hal_adc_adapter_s {
    volatile uint8_t    status;                     /*! adc module status    */
    volatile uint8_t    use_dma;                    /*! adc module uses dma or not  */
    uint8_t             continuous_rd;              /*! adc internal flag for continuous read including DMA read */
    uint8_t             use_cali;                   /*! adc use calibration or not    */
    volatile uint32_t   err_type;                   /*! adc module error type    */
    uint32_t            cv_dat_len;                 /*! adc conversion data len, this is for receving data length, not
                                                        hardware conversion length  */
    uint16_t            *cv_dat_buf;                /*! adc conversion data buffer pointer    */
    adc_init_dat_t      init_dat;                   /*! adc initial data     */
    adc_user_callback_t usr_cb;                     /*! adc user callback     */
    adc_dma_info_t      dma_dat;                    /*! adc dma data   */
    adc_platform_data_t plft_dat;                   /*! adc platform data */
    hal_timer_adapter_t *timer_adpt;                /*! adc trigger timer adapter   */
}hal_adc_adapter_t, *phal_adc_adapter_t;

/** \brief adc calibration parameters
*/
typedef struct hal_adc_cali_para_s {
    int16_t             gain_deno;
    int16_t             gain_mole;
    int32_t             offset_deno;
    int16_t             offset_mole;
    int16_t             rsvd;
}hal_adc_cali_para_t, *phal_adc_cali_para_t;

/**
  \brief Union type to access adc params
*/
typedef union {
  __IOM int32_t w;                            /*!< word                                 */

  struct {
    __IOM int32_t b0 : 8;                    /*!< [7..0] byte0                                       */
    __IOM int32_t b1 : 8;                    /*!< [15..8] byte1                                       */
    __IOM int32_t b2 : 8;                    /*!< [23..16] byte2                                       */
    __IOM int32_t b3 : 8;                    /*!< [31..24] byte3                                       */
  } b;                                        /*!< bit fields for adc_conf */
} adc_w_b_t, *padc_w_b_t;

extern volatile hal_adc_cali_para_t adc_cali_paras;

/*  Inline functions  */
/** \brief Description of hal_adc_chk_chidx_rtl8195blp
 *
 *    hal_adc_chk_chidx_rtl8195blp is used to check ADC channel is available or not.
 *
 *   \param[in] uint8_t ch_no:                ADC channel number.
 *   \return hal_status_t
 */
__STATIC_INLINE hal_status_t hal_adc_chk_chidx_rtl8195blp(uint8_t ch_no)
{
    if (ch_no < LP_ADC_CH_NO) {
        return HAL_OK;
    } else {
        return HAL_ERR_PARA;
    }
}

/** \brief Description of hal_adc_auto_chsw_ctrl_rtl8195blp
 *
 *    hal_adc_auto_chsw_ctrl_rtl8195blp is used to enable/disable auto mode.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t auto_enable:                enable/ disable auto chsw.
 *   \return void
 */
__STATIC_INLINE void hal_adc_auto_chsw_ctrl_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t auto_enable)
{
    phal_adc_adapter->init_dat.reg_base->auto_chsw_ctrl = auto_enable;
}

/** \brief Description of hal_adc_get_last_item_rtl8195blp
 *
 *    hal_adc_get_last_item_rtl8195blp is used to read the last cvlist item number which \n
 *    the last conversion is executed.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:    Pointer to ADC control adapter.
 *   \return uint32_t:            item number in cvlist
 */
__STATIC_INLINE uint32_t hal_adc_get_last_item_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter)
{
    return (uint32_t)phal_adc_adapter->init_dat.reg_base->last_item;
}

/** \brief Description of hal_adc_get_empty_sts_rtl8195blp
 *
 *    hal_adc_get_empty_sts_rtl8195blp is used to read adc empty status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint32_t:                              0: not full; 1: full
 */
__STATIC_INLINE uint32_t hal_adc_get_empty_sts_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter)
{
//    ADC_Type *padc_reg = padc_init_data->reg_base;

//#ifdef ADC_FULL_STS_PATCH
//    if (padc_reg->intr_raw_sts_b.it_fifo_full == 1) {
//        /* clear full status */
//        padc_reg->intr_sts_b.it_fifo_full = 1;
//        return (uint32_t)1;
//    } else {
//        return (uint32_t)0;
//    }
//#else
    if (phal_adc_adapter->init_dat.reg_base->sts_b.empty) {
        return (uint32_t)1;
    } else {
        return (uint32_t)0;
    }
//#endif
}

/** \brief Description of hal_adc_reset_list_rtl8195blp
 *
 *    hal_adc_reset_list_rtl8195blp is used to reset cvlist to the default state.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
__STATIC_INLINE void hal_adc_reset_list_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter)
{
    phal_adc_adapter->init_dat.reg_base->rst_list = 1;
    phal_adc_adapter->init_dat.reg_base->rst_list = 0;
}

/*  Function declaration   */
void hal_adc_irq_handler_rtl8195blp (void);
void hal_adc_dma_irq_handler_rtl8195blp (void);

uint8_t hal_adc_timeout_chk_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint32_t start_cnt);
void hal_adc_sw_cv_trig_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pure_init_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pure_deinit_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_set_in_type_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t input_type);
uint8_t hal_adc_get_in_type_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
hal_status_t hal_adc_set_comp_thld_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint16_t thld_high, uint16_t thld_low);
hal_status_t hal_adc_set_comp_rule_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t comp_rule);
void hal_adc_clear_comp_intr_sts_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
void hal_adc_intr_ctrl_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option, uint8_t intr_enable);
void hal_adc_clear_intr_sts_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option);
hal_status_t hal_adc_set_cvlist_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t *cvlist, uint8_t cvlist_len);
uint8_t hal_adc_item_to_ch_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t item_no);
void hal_adc_load_default_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
void hal_adc_reg_irq_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, irq_handler_t handler);
void hal_adc_unreg_irq_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pin_init_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pin_deinit_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_init_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_deinit_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
uint16_t hal_adc_single_read_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
void hal_adc_clear_fifo_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
uint16_t hal_adc_read_ch_dat_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t out_raw);
hal_status_t hal_adc_read_continuous_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf, uint8_t trigger_source);
hal_status_t hal_adc_dma_init_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, hal_gdma_adaptor_t *padc_gdma_adaptor);
hal_status_t hal_adc_dma_deinit_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_read_dma_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf, uint8_t trigger_source);
hal_status_t hal_adc_init_rtl8195blp_patch (hal_adc_adapter_t *phal_adc_adapter);
uint32_t hal_adc_gen_rand_dat32_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);

int16_t hal_adc_calc_gain_deno_rtl8195blp(int16_t ideal_co_1, int16_t ideal_co_0);
int16_t hal_adc_calc_gain_mole_rtl8195blp(int16_t real_co_1, int16_t real_co_0);
int32_t hal_adc_calc_offset_deno_rtl8195blp(int16_t ideal_co_1, int16_t ideal_co_0, int16_t real_co_1, int16_t real_co_0);
int16_t hal_adc_calc_offset_mole_rtl8195blp(int16_t real_co_1, int16_t real_co_0);
uint16_t hal_adc_calc_cali_val_rtl8195blp(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para);
void hal_adc_read_cali_param_rtl8195blp(uint16_t addr, uint8_t *param_addr, uint8_t param_len);
void hal_adc_write_cali_param_rtl8195blp(uint16_t addr, uint8_t *param_addr, uint8_t param_len);

uint16_t hal_adc_read_fifo_rtl8195blp (hal_adc_adapter_t *phal_adc_adapter, uint8_t out_raw);

/**
  \brief  The data structure of the stubs function for the ADC HAL functions in ROM
*/
typedef struct hal_adc_func_stubs_s {
    uint8_t (*hal_adc_timeout_chk) (hal_adc_adapter_t *phal_adc_adapter, uint32_t start_cnt);
    void (*hal_adc_sw_cv_trig) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_pure_init) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_pure_deinit) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_set_in_type) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t input_type);
    uint8_t (*hal_adc_get_in_type) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
    hal_status_t (*hal_adc_set_comp_thld) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint16_t thld_high, uint16_t thld_low);
    hal_status_t (*hal_adc_set_comp_rule) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t comp_rule);
    void (*hal_adc_clear_comp_intr_sts) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
    void (*hal_adc_intr_ctrl) (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option, uint8_t intr_enable);
    void (*hal_adc_clear_intr_sts) (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option);
    hal_status_t (*hal_adc_set_cvlist) (hal_adc_adapter_t *phal_adc_adapter, uint8_t *cvlist, uint8_t cvlist_len);
    uint8_t (*hal_adc_item_to_ch) (hal_adc_adapter_t *phal_adc_adapter, uint8_t item_no);
    void (*hal_adc_load_default) (hal_adc_adapter_t *phal_adc_adapter);
    void (*hal_adc_reg_irq) (hal_adc_adapter_t *phal_adc_adapter, irq_handler_t handler);
    void (*hal_adc_unreg_irq) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_pin_init) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_pin_deinit) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_init) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_deinit) (hal_adc_adapter_t *phal_adc_adapter);
    uint16_t (*hal_adc_single_read) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
    void (*hal_adc_clear_fifo) (hal_adc_adapter_t *phal_adc_adapter);
    uint16_t (*hal_adc_read_ch_dat) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t out_raw);
    hal_status_t (*hal_adc_read_continuous) (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf, uint8_t trigger_source);
    hal_status_t (*hal_adc_dma_init) (hal_adc_adapter_t *phal_adc_adapter, hal_gdma_adaptor_t *padc_gdma_adaptor);
    hal_status_t (*hal_adc_dma_deinit) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_read_dma) (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf, uint8_t trigger_source);
    void (*hal_adc_irq_handler) (void);
    void (*hal_adc_dma_irq_handler) (void);
    uint32_t (*hal_adc_gen_rand_dat32) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
    volatile hal_adc_adapter_t **phal_adc_irq_adpt;
    volatile hal_adc_cali_para_t *hal_adc_cali_para;
    
    int16_t (*hal_adc_calc_gain_deno)(int16_t ideal_co_1, int16_t ideal_co_0);
    int16_t (*hal_adc_calc_gain_mole)(int16_t real_co_1, int16_t real_co_0);
    int32_t (*hal_adc_calc_offset_deno)(int16_t ideal_co_1, int16_t ideal_co_0, int16_t real_co_1, int16_t real_co_0);
    int16_t (*hal_adc_calc_offset_mole)(int16_t real_co_1, int16_t real_co_0);
    uint16_t (*hal_adc_calc_cali_val)(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para);
    void (*hal_adc_read_cali_param)(uint16_t addr, uint8_t *param_addr, uint8_t param_len);    
    void (*hal_adc_write_cali_param)(uint16_t addr, uint8_t *param_addr, uint8_t param_len);
    uint16_t (*hal_adc_read_fifo)(hal_adc_adapter_t *phal_adc_adapter, uint8_t out_raw);
    
    uint32_t reserved[5];  // reserved space for next ROM code version function table extending.
} hal_adc_func_stubs_t;

/** @} */ /* End of group ls_hal_adc */

#ifdef  __cplusplus
}
#endif

#endif

