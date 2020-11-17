/**************************************************************************//**
 * @file     rtl819bhp_adc.h
 * @brief    The fundamental definition for RTL8195B HP ADC module.
 * @version  V1.00
 * @date     2017-01-15
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

#ifndef _RTL8195BHP_ADC_H_
#define _RTL8195BHP_ADC_H_

#include "rtl8195bhp_adc_type.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_adc ADC
 * @{
 */

#undef ADC_SW_DATA_PATCH
#define ADC_BUSY_PATCH
#undef ADC_LAST_ITEM_PATCH
#undef ADC_DMA_PATCH
#undef ADC_NULL_CHANNEL_PATCH


/*  Macros for adc related constant  */
/// adc total channel number (internal + external)
#define HP_ADC_CH_NO            8
/// adc external channel number (adc4 ~ adc7)
#define HP_ADC_EXCH_NO          4
/// adc dual input channel input number
#define HP_ADC_DUAL_IN_CH       8
/// adc hardware list item number
#define HP_ADC_LIST_LEN         16
/// adc hardware list item number in half
#define HP_ADC_LIST_HALF        8
/// adc IRQ Priority
#define HP_ADC_IRQ_PR           3
/// adc resolution bit number
#define HP_ADC_RESOLUTION       12
/// adc data mask
#define HP_ADC_DATA_MASK        0xFFF
/// adc FIFO length
#define HP_ADC_FIFO_LEN         64
/// adc code max value
#define HP_ADC_CODE_MAX         0xFFF
/// adc rule number
#define HP_ADC_COMP_RULE        4
/// adc default DMA RX des width
#define HP_ADC_DMA_DEFAULT_RX_DES_WIDTH 4
//#define HP_ADC_CHIDX_MASK       0x3C00      /// adc channel index mask
/// adc disable timeout
#define HP_ADC_TIMEOUT_DISABLE  0x0
/// adc endless timeout
#define HP_ADC_TIMEOUT_ENDLESS  0xFFFFFFFF
/// adc input all single-end type
#define HP_ADC_INPUT_ALL_SINGLE 0
/// hp adc calculating scale
#define HP_ADC_CALC_SCLE        1024

/// hp adc constant value
#define HP_ADC_FUSE_VAL         0x37F00000
#define HP_ADC_GAIN_DENO_ADDR   0x100
#define HP_ADC_GAIN_MOLE_ADDR   0x102
#define HP_ADC_OFFSET_DENO_ADDR 0x104
#define HP_ADC_OFFSET_MOLE_ADDR 0x108

#define HP_ADC_ICALI_DAT_NUM    6
#define HP_ADC_ICALI_DAT_MSK    0xFE0FFFFF
#define HP_ADC_ICALI_D8_SEL     0x00000000
#define HP_ADC_ICALI_D8_HIGH    135
#define HP_ADC_ICALI_D8_LOW     104

#define HP_ADC_ICALI_D9_SEL     0x00200000
#define HP_ADC_ICALI_D9_HIGH    240
#define HP_ADC_ICALI_D9_LOW     176

#define HP_ADC_ICALI_D10_SEL    0x00400000
#define HP_ADC_ICALI_D10_HIGH   400
#define HP_ADC_ICALI_D10_LOW    336

#define HP_ADC_ICALI_D11_SEL    0x00600000
#define HP_ADC_ICALI_D11_HIGH   680
#define HP_ADC_ICALI_D11_LOW    552

#define HP_ADC_ICALI_D12_SEL    0x00800000
#define HP_ADC_ICALI_D12_HIGH   1207
#define HP_ADC_ICALI_D12_LOW    955

#define HP_ADC_ICALI_D13_SEL    0x00A00000
#define HP_ADC_ICALI_D13_HIGH   1663
#define HP_ADC_ICALI_D13_LOW    1408

typedef struct adc_icali_dat_s {
    uint32_t    icali_msk;
    uint16_t    icali_high;
    uint16_t    icali_low;
}adc_icali_dat_t, *padc_icali_dat_t;

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
    ADCClockDiv5            =   0x00,               /*!< 0x00: adc clock is divided by 5   */
    ADCClockDiv10           =   0x01,               /*!< 0x01: adc clock is divided by 10    */
    ADCClockDiv16           =   0x02,               /*!< 0x02: adc clock is divided by 16    */
    ADCClockDiv32           =   0x03,               /*!< 0x03: adc clock is divided by 32    */
    ADCClockDiv64           =   0x04,               /*!< 0x03: adc clock is divided by 64    */
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
};

/** \brief adc initail data structure */
typedef struct adc_init_dat_s {
    uint8_t     enable;                         /*!< Offset: 0x000   adc enable state, updated by HAL   */
    uint8_t     hw_mode;                        /*!< Offset: 0x001   adc hardware operation mode   */
    //u8          cvlist_en;                      /*!< Offset: 0x002   adc conversion list enable for further usage.
    //                                                                 If single read method is prefered for use,
    //                                                                 this should be clear to 0.  */

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
    //hal_gdma_chnl_t     *ch_op;                     /*! adc dma channel option     */
    uint8_t             ch_sts;                     /*! adc dma channel status (adc local)     */
    uint8_t             rsvd0;
    uint16_t            rsvd1;
}adc_dma_info_t,*padc_dma_info_t;

/** \brief adc user callback adaptor
*/
typedef struct adc_user_callback_adpt_s {
    VOID (*cb)      (VOID *data);                   /*! adc callback function */
    uint32_t        dat;                            /*! adc callback function argument */
}adc_user_callback_adpt_t, *padc_user_callback_adpt_t;

/** \brief  hp adc pinmux enable structure.
 */
typedef union {
    uint32_t w;                             /*!< (@ 0x00000000) HP ADC pinmux enable      */

    struct {
        uint32_t adc0 : 1;                  /*!< (@ 0x00000000) ADC0 pinmux enable        */
        uint32_t adc1 : 1;                  /*!< (@ 0x00000001) ADC1 pinmux enable        */
        uint32_t adc2 : 1;                  /*!< (@ 0x00000002) ADC2 pinmux enable        */
        uint32_t adc3 : 1;                  /*!< (@ 0x00000003) ADC3 pinmux enable        */
        uint32_t adc4 : 1;                  /*!< (@ 0x00000004) ADC4 pinmux enable        */
        uint32_t adc5 : 1;                  /*!< (@ 0x00000005) ADC5 pinmux enable        */
        uint32_t adc6 : 1;                  /*!< (@ 0x00000006) ADC6 pinmux enable        */
        uint32_t adc7 : 1;                  /*!< (@ 0x00000006) ADC7 pinmux enable        */
    } b;
} hp_adc_pin_en_t, *php_adc_pin_en_t;


/** \brief adc platform related data
*/
typedef struct adc_platform_data_s {
    uint32_t        rx_dma_bound;                   /*! adc low bound to do rx-dma transmission,
                                                        if rx len is more than this bound, rx API
                                                        would change to poll mode transmission.*/
    uint32_t        tr_time_out;                    /*! adc transmission time-out count */
    hp_adc_pin_en_t pin_en;                         /*! adc channel pinmux enable */
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
    adc_user_callback_adpt_t  err;                  /*! adc error callback */
    adc_user_callback_adpt_t  full;                 /*! adc fifo full callback */
    adc_user_callback_adpt_t  empty;                /*! adc fifo empty callback */
    adc_user_callback_adpt_t  cv_end;               /*! adc conversion end callback */
    adc_user_callback_adpt_t  ch_cv_end;            /*! adc particular channel conversion end callback */
    adc_user_callback_adpt_t  cvlist_end;           /*! adc conversion list end callback */
    adc_user_callback_adpt_t  rxc;                  /*! adc dma receive complete callback */
    adc_user_callback_adpt_t  wake;                 /*! adc wake up callback */
}adc_user_callback_t, *padc_user_callback_t;

/** \brief adc control adaptor
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
    void (*dcache_invalidate_by_addr)(uint32_t *addr, int32_t dsize);   /*! callback function to do the D-cache invalidate  */
    void (*dcache_clean_by_addr) (uint32_t *addr, int32_t dsize);       /*! callback function to do the D-cache clean  */
    void (*dcache_clean_invalidate_by_addr) (uint32_t *addr, int32_t dsize);       /*! callback function to do the D-cache clean
                                                                                       and invalidate */
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
/** \brief Description of hal_adc_chk_chidx_rtl8195bhp
 *
 *    hal_adc_chk_chidx_rtl8195bhp is used to check ADC channel is available or not.
 *
 *   \param[in] uint8_t ch_no:                ADC channel number.
 *   \return hal_status_t
 */
__STATIC_INLINE hal_status_t hal_adc_chk_chidx_rtl8195bhp(uint8_t ch_no)
{
    if (ch_no < HP_ADC_CH_NO) {
        return HAL_OK;
    } else {
        return HAL_ERR_PARA;
    }
}

/** \brief Description of hal_adc_auto_chsw_ctrl_rtl8195bhp
 *
 *    hal_adc_chk_chidx_rtl8195bhp is used to enable/disable auto mode.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t auto_enable:                enable/ disable auto chsw.
 *   \return void
 */
__STATIC_INLINE void hal_adc_auto_chsw_ctrl_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t auto_enable)
{
    phal_adc_adapter->init_dat.reg_base->auto_chsw_ctrl = auto_enable;
}

/** \brief Description of hal_adc_get_last_item_rtl8195bhp
 *
 *    hal_adc_get_last_item_rtl8195bhp is used to read the last cvlist item number which \n
 *    the last conversion is executed.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:    Pointer to ADC control adapter.
 *   \return uint32_t:            item number in cvlist
 */
__STATIC_INLINE uint32_t hal_adc_get_last_item_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter)
{
    return (uint32_t)phal_adc_adapter->init_dat.reg_base->last_item;
}

/** \brief Description of hal_adc_get_empty_sts_rtl8195bhp
 *
 *    hal_adc_get_empty_sts_rtl8195bhp is used to read adc empty status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint32_t:                              0: not full; 1: full
 */
__STATIC_INLINE uint32_t hal_adc_get_empty_sts_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter)
{
    if (phal_adc_adapter->init_dat.reg_base->sts_b.empty) {
        return (uint32_t)1;
    } else {
        return (uint32_t)0;
    }
}

/** \brief Description of hal_adc_reset_list_rtl8195bhp
 *
 *    hal_adc_reset_list_rtl8195bhp is used to reset cvlist to the default state.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
__STATIC_INLINE void hal_adc_reset_list_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter)
{
    phal_adc_adapter->init_dat.reg_base->rst_list = 1;
    phal_adc_adapter->init_dat.reg_base->rst_list = 0;
}

#if 0
/** \brief Description of hal_adc_read_fifo_rtl8195bhp
 *
 *    hal_adc_read_fifo_rtl8195bhp is used to read the fifo register(global) without any trigger operations.
 *
 *   \param hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return uint16_t:                              channel conversion data.
 */
__STATIC_INLINE uint16_t hal_adc_read_fifo_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter)
{
    return (uint16_t)(phal_adc_adapter->init_dat.reg_base->dat_global_b.dat);
}
#endif

/** \brief adc pin definition structure
*/
typedef struct hal_adc_pin_s {
    uint8_t adc_in;
    uint8_t eol;    // end of list
}hal_adc_pin_t, *phal_adc_pin_t;

/*  Function declaration   */
void hal_adc_irq_handler_rtl8195bhp (void);
void hal_adc_dma_irq_handler_rtl8195bhp (void);

uint8_t hal_adc_timeout_chk_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint32_t start_cnt);
void hal_adc_sw_cv_trig_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
void hal_adc_irq_handle_rtl8195bhp (void *data);
void hal_adc_dma_irq_handle_rtl8195bhp (void *data);
hal_status_t hal_adc_pwr_init_rtl8195bh (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pwr_deinit_rtl8195bh (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pure_init_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pure_deinit_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_set_in_type_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t input_type);
uint8_t hal_adc_get_in_type_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
hal_status_t hal_adc_set_comp_thld_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint16_t thld_high, uint16_t thld_low);
hal_status_t hal_adc_set_comp_rule_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t comp_rule);
void hal_adc_clear_comp_intr_sts_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
void hal_adc_intr_ctrl_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option, uint8_t intr_enable);
void hal_adc_clear_intr_sts_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option);
hal_status_t hal_adc_set_cvlist_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t *cvlist, uint8_t cvlist_len);
uint8_t hal_adc_item_to_ch_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t item_no);
void hal_adc_load_default_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
void hal_adc_reg_irq_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, irq_handler_t handler);
void hal_adc_unreg_irq_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_init_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_deinit_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
uint16_t hal_adc_single_read_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
void hal_adc_clear_fifo_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
uint16_t hal_adc_read_ch_dat_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t out_raw);
hal_status_t hal_adc_read_continuous_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf,
                                                    uint8_t trigger_source);
uint32_t hal_adc_gen_rand_dat32_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
uint32_t hal_adc_exd_mod_control_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t mod_bit, uint8_t enable);
hal_status_t hal_adc_pwr_init_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
hal_status_t hal_adc_pwr_deinit_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);

//hal_status_t hal_adc_dma_init_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
//hal_status_t hal_adc_dma_deinit_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter);
//hal_status_t hal_adc_read_dma_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf, uint8_t trigger_source);

int16_t hal_adc_calc_gain_deno_rtl8195bhp(int16_t ideal_co_1, int16_t ideal_co_0);
int16_t hal_adc_calc_gain_mole_rtl8195bhp(int16_t real_co_1, int16_t real_co_0);
int32_t hal_adc_calc_offset_deno_rtl8195bhp(int16_t ideal_co_1, int16_t ideal_co_0, int16_t real_co_1, int16_t real_co_0);
int16_t hal_adc_calc_offset_mole_rtl8195bhp(int16_t real_co_1, int16_t real_co_0);
uint32_t hal_adc_calc_cali_val_rtl8195bhp(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para);
void hal_adc_read_cali_param_rtl8195bhp(uint16_t addr, uint8_t *param_addr, uint8_t param_len);
void hal_adc_write_cali_param_rtl8195bhp(uint16_t addr, uint8_t *param_addr, uint8_t param_len);

uint16_t hal_adc_read_fifo_rtl8195bhp (hal_adc_adapter_t *phal_adc_adapter, uint8_t out_raw);
/**
  \brief  The data structure of the stubs function for the ADC HAL functions in ROM
*/
typedef struct hal_adc_func_stubs_s {
    hal_adc_pin_t *hal_adc_pin_list;
    uint8_t (*hal_adc_timeout_chk) (hal_adc_adapter_t *phal_adc_adapter, uint32_t start_cnt);
    void (*hal_adc_sw_cv_trig) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_pwr_init) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_pwr_deinit) (hal_adc_adapter_t *phal_adc_adapter);
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
    hal_status_t (*hal_adc_init) (hal_adc_adapter_t *phal_adc_adapter);
    hal_status_t (*hal_adc_deinit) (hal_adc_adapter_t *phal_adc_adapter);
    uint16_t (*hal_adc_single_read) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
    void (*hal_adc_clear_fifo) (hal_adc_adapter_t *phal_adc_adapter);
    uint16_t (*hal_adc_read_ch_dat) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t out_raw);
    hal_status_t (*hal_adc_read_continuous) (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf, uint8_t trigger_source);
    uint32_t (*hal_adc_gen_rand_dat32) (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);
    //hal_status_t (*hal_adc_dma_init) (hal_adc_adapter_t *phal_adc_adapter);
    //hal_status_t (*hal_adc_dma_deinit) (hal_adc_adapter_t *phal_adc_adapter);
    //hal_status_t (*hal_adc_read_dma) (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf, uint8_t trigger_source);
    void (*hal_adc_irq_handler) (void);
    void (*hal_adc_dma_irq_handler) (void);
    uint32_t (*hal_adc_exd_mod_control) (hal_adc_adapter_t *phal_adc_adapter, uint8_t mod_bit, uint8_t enable);
    volatile hal_adc_adapter_t **phal_adc_irq_adpt;
    volatile hal_adc_cali_para_t *hal_adc_cali_para;
    
    int16_t (*hal_adc_calc_gain_deno)(int16_t ideal_co_1, int16_t ideal_co_0);
    int16_t (*hal_adc_calc_gain_mole)(int16_t real_co_1, int16_t real_co_0);
    int32_t (*hal_adc_calc_offset_deno)(int16_t ideal_co_1, int16_t ideal_co_0, int16_t real_co_1, int16_t real_co_0);
    int16_t (*hal_adc_calc_offset_mole)(int16_t real_co_1, int16_t real_co_0);
    uint32_t (*hal_adc_calc_cali_val)(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para);
    void (*hal_adc_read_cali_param)(uint16_t addr, uint8_t *param_addr, uint8_t param_len);    
    void (*hal_adc_write_cali_param)(uint16_t addr, uint8_t *param_addr, uint8_t param_len);
    uint16_t (*hal_adc_read_fifo)(hal_adc_adapter_t *phal_adc_adapter, uint8_t out_raw);
    uint32_t reserved[5];  // reserved space for next ROM code version function table extending.
} hal_adc_func_stubs_t;

/** @} */ /* End of group hs_hal_adc */

#ifdef  __cplusplus
}
#endif

#endif

