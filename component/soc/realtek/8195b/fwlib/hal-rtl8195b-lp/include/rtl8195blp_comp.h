/**************************************************************************//**
 * @file     rtl819blp_comp.h
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



#ifndef _RTL8195BLP_COMP_H_
#define _RTL8195BLP_COMP_H_

#include "rtl8195blp_adc_type.h"
#include "rtl8195blp_comp_type.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup ls_hal_comp COMP
 * @{
 */

/*
* @brief Compile option for patch code
*/
//#define COMP_LOCAL_SVD_DECLARATION
#undef COMP_LOCAL_SVD_DECLARATION
#undef COMP_SW_TEMP_PATCH
//#define COMP_INTR_PATCH
#undef COMP_INTR_PATCH

/// lp comparator total channel number
#define LP_COMP_CH_NO           4
/// lp comparator rule mask
#define LP_COMP_RULE_MSK        0x03
/// lp comparator set all comparator rule
#define LP_COMP_RULE_ALLSET     0x07
/// lp comparator reference max value
#define LP_COMP_REF_MAX         31
/// lp comparator rule number
#define LP_COMP_RULE_NO         4
/// lp comparator list length
#define LP_COMP_LIST_LEN        4
/// lp comparator related timer number
#define LP_COMP_TIMER_NO        8
/// lp comparator disable timeout
#define LP_COMP_TIMEOUT_DISABLE 0x0
/// lp comparator endless timeout
#define LP_COMP_TIMEOUT_ENDLESS 0xFFFFFFFF

/** @defgroup comp_reg_access_macro COMP REG ACCESS MACRO
 *  Comparator register access
 *  @{
 */
#define COMP_BASE_REG ((volatile COMP_Type *)(0))
#define HAL_COMP_READ32(base, offset) rtk_le32_to_cpu(*((volatile uint32_t*)(base + offset)))
#define HAL_COMP_WRITE32(base, offset, value) ((*((volatile uint32_t*)(base + offset))) = rtk_cpu_to_le32(value))
/** @} */ // end of COMP REG ACCESS MACRO

/** \brief comparator feature status
*/
enum comp_enable_status_e {
    CompDisable      =   0,                  /*!< 0: for comparator disable state    */
    CompEnable       =   1,                  /*!< 1: for comparator enable state    */
};

/** \brief comparator module state
*/
enum comp_status_e {
    CompStatusUninitial     =   0x00,               /*!< 0x00: comparator uninitial state   */
    CompStatusInitialized   =   0x01,               /*!< 0x01: comparator initialized state   */
    CompStatusIdle          =   0x02,               /*!< 0x02: comparator idle state   */

    CompStatusError         =   0x10,               /*!< 0x10: comparator error state   */
    CompStatusTimeOut       =   0x11,               /*!< 0x11: comparator time-out state   */
};

/** \brief comparator interrupt target
*/
enum comp_interrupt_target_e {
    CompIntrADC     =   0,                  /*!< 0: for comparator to interrupt ADC    */
    CompIntrSys     =   1,                  /*!< 1: for comparator to interrupt system    */
};

/** \brief comparator interrupt target
*/
enum comp_trigger_source_e {
    CompSwTrig     =   0,                   /*!< 0: for comparator software trigger    */
    CompAutoTrig   =   1,                   /*!< 1: for comparator auto trigger    */
    CompTimerTrig  =   2,                   /*!< 2: for comparator timer trigger    */
};

/** \brief comparator user callback adaptor
*/
typedef struct comp_user_callback_adpt_s {
    VOID (*cb)      (VOID *data);                   /*! comparator callback function */
    u32  dat;                                       /*! comparator callback function argument */
}comp_user_callback_adpt_t, *pcomp_user_callback_adpt_t;

/** \brief comparator user callback
*/
typedef struct comp_user_callback_s {
    adc_user_callback_adpt_t  adc_ch_0;             /*! comparator channel 0 interrupt adc callback */
    adc_user_callback_adpt_t  adc_ch_1;             /*! comparator channel 1 interrupt adc callback */
    adc_user_callback_adpt_t  adc_ch_2;             /*! comparator channel 2 interrupt adc callback */
    adc_user_callback_adpt_t  adc_ch_3;             /*! comparator channel 3 interrupt adc callback */
    adc_user_callback_adpt_t  sys_ch_0;             /*! comparator channel 0 interrupt system callback */
    adc_user_callback_adpt_t  sys_ch_1;             /*! comparator channel 1 interrupt system callback */
    adc_user_callback_adpt_t  sys_ch_2;             /*! comparator channel 2 interrupt system callback */
    adc_user_callback_adpt_t  sys_ch_3;             /*! comparator channel 3 interrupt system callback */
}comp_user_callback_t, *pcomp_user_callback_t;

/** \brief comparator initail data structure */
typedef struct comp_init_dat_s {
//    uint8_t     enable;                         /*!< Offset: 0x000   comparator enable state, updated by HAL   */
    uint8_t     trig_timer;                     /*!< Offset: 0x001   comparator conversion trigger timer   */
    uint16_t    rsvd;
    COMP_Type   *reg_base;                      /*!< Offset: 0x004   comparator register base address   */
}comp_init_dat_t, *pcomp_init_dat_t;

/** \brief  lp adc pinmux enable structure.
 */
typedef union {
    uint32_t w;                             /*!< (@ 0x00000000) LP comparator pinmux enable      */

    struct {
        uint32_t comp0 : 1;                 /*!< (@ 0x00000000) comparator0 pinmux enable        */
        uint32_t comp1 : 1;                 /*!< (@ 0x00000001) comparator1 pinmux enable        */
        uint32_t comp2 : 1;                 /*!< (@ 0x00000002) comparator2 pinmux enable        */
        uint32_t comp3 : 1;                 /*!< (@ 0x00000003) comparator3 pinmux enable        */
    } b;
} lp_comp_pin_en_t, *plp_comp_pin_en_t;


/** \brief comparator control adaptor
*/
typedef struct hal_comp_adapter_s {
    volatile uint8_t    status;                     /*! comparator module status    */
    uint8_t             rsvd0;
    uint16_t            rsvd1;
    comp_init_dat_t     init_dat;                   /*! comparator initial data     */
    comp_user_callback_t usr_cb;                    /*! comparator user callback     */
    //irq_config_t        irq_config;                 /*! comparator interrupt handler     */
    hal_timer_adapter_t *timer_adpt;                /*! comparator trigger timer adapter   */
    lp_comp_pin_en_t    pin_en;                     /*! comparator pinmux enable control   */
}hal_comp_adapter_t, *phal_comp_adapter_t;

void hal_comp_irq_handler_rtl8195blp (void);
uint8_t hal_comp_timeout_chk_rtl8195blp (uint32_t start_cnt, uint32_t comp_timeout_cnt);
hal_status_t hal_comp_pure_init_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_pure_deinit_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_pin_init_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_pin_deinit_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter);
void hal_comp_reg_irq_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter, irq_handler_t handler);
void hal_comp_unreg_irq_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_init_rtl819blp (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_deinit_rtl819blp (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_sw_trig_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter);
hal_status_t hal_comp_auto_chsw_ctrl_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter, uint8_t auto_sw_en);
hal_status_t hal_comp_set_chsw_list_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter, uint8_t *chlist, uint8_t list_len);
void hal_comp_set_refv_rtl819blp (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t refv0, uint8_t refv1);
void hal_comp_set_intr_rule_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar, uint8_t intr_rule);
void hal_comp_clear_intr_rule_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel ,uint8_t intr_tar);
uint8_t hal_comp_get_intr_sts_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar);
void hal_comp_clear_intr_sts_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar);
uint8_t hal_comp_get_ana_sts_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel);
void hal_comp_load_default_rtl8195blp (hal_comp_adapter_t *phal_comp_adapter);

/**
  \brief  The data structure of the stubs function for the Comparator HAL functions in ROM
*/
typedef struct hal_comp_func_stubs_s {
    uint8_t (*hal_comp_timeout_chk) (uint32_t start_cnt, uint32_t comp_timeout_cnt);
    hal_status_t (*hal_comp_pure_init) (hal_comp_adapter_t *phal_comp_adapter);
    hal_status_t (*hal_comp_pure_deinit) (hal_comp_adapter_t *phal_comp_adapter);
    hal_status_t (*hal_comp_pin_init) (hal_comp_adapter_t *phal_comp_adapter);
    hal_status_t (*hal_comp_pin_deinit) (hal_comp_adapter_t *phal_comp_adapter);
    void (*hal_comp_reg_irq) (hal_comp_adapter_t *phal_comp_adapter, irq_handler_t handler);
    void (*hal_comp_unreg_irq) (hal_comp_adapter_t *phal_comp_adapter);
    hal_status_t (*hal_comp_init) (hal_comp_adapter_t *phal_comp_adapter);
    hal_status_t (*hal_comp_deinit) (hal_comp_adapter_t *phal_comp_adapter);
    hal_status_t (*hal_comp_sw_trig) (hal_comp_adapter_t *phal_comp_adapter);
    hal_status_t (*hal_comp_auto_chsw_ctrl) (hal_comp_adapter_t *phal_comp_adapter, uint8_t auto_sw_en);
    hal_status_t (*hal_comp_set_chsw_list) (hal_comp_adapter_t *phal_comp_adapter, uint8_t *chlist, uint8_t list_len);
    void (*hal_comp_set_refv) (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t refv0, uint8_t refv1);
    void (*hal_comp_set_intr_rule) (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar, uint8_t intr_rule);
    void (*hal_comp_clear_intr_rule) (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel ,uint8_t intr_tar);
    uint8_t (*hal_comp_get_intr_sts) (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar);
    void (*hal_comp_clear_intr_sts) (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel, uint8_t intr_tar);
    uint8_t (*hal_comp_get_ana_sts) (hal_comp_adapter_t *phal_comp_adapter, uint8_t channel);
    void (*hal_comp_load_default) (hal_comp_adapter_t *phal_comp_adapter);
    void (*hal_comp_irq_handler) (void);
    uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} hal_comp_func_stubs_t;

/** @} */ /* End of group ls_hal_comp */

#ifdef __cplusplus
}
#endif

#endif /* _RTL8195BLP_COMP_H_ */


