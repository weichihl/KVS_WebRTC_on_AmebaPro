 /**************************************************************************//**
  * @file     rtl8195blp_qdec.h
  * @brief    The HAL related definition and macros for the QDEC device.
  *           Includes Registers and data type definition.
  * @version  V1.00
  * @date     2016-06-14
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

#ifndef _RTL8195BLP_QDEC_H_
#define _RTL8195BLP_QDEC_H_

/** 
 * @addtogroup ls_hal_qdec QDEC
 * @{
 */

#include "basic_types.h"
#include "rtl8195blp_qdec_type.h"

/**
  \brief  Define the QDEC port ID.
*/
enum  qdec_id_e
{
    Qdec_0      = 0,
    MaxQdecNum  = 1
};
typedef uint8_t qdec_id_t;

/**
  \brief QDEC application pin mux selection. 
*/
enum  qdec_app_pin_sel_e
{
    Qdec_Pin_Pha_Phb        =   0x0,
    Qdec_Pin_Pha_Phb_Idx    =   0x1,
    Qdec_Pin_Comb_End       =   0x2
};
typedef uint8_t qdec_app_pin_sel_t;

/**
  \brief QDEC pin mux selection.
*/
enum  qdec_pin_sel_e
{
    Qdec_PinSel_0       = 0,  
    Qdec_PinSel_1       = 1,
    Qdec_PinSel_Max     = 2
};
typedef uint8_t qdec_pin_sel_t;

/*! define qdec phase(A, B) */

/**
  \brief Define QDEC phase.
*/
enum  qdec_phase_e
{
    PhA0_PhB0   = 0,
    PhA0_PhB1   = 1,
    PhA1_PhB0   = 2,
    PhA1_PhB1   = 3    
};
typedef uint8_t qdec_phase_t;

/**
  \brief Define a value changed on the position counter which will trigger the position changed interrupt.
*/
enum  qdec_cnt_chg_e
{
    Pos_Chg1    = 0,
    Pos_Chg2    = 1,
    Pos_Chg4    = 2   
};
typedef uint8_t qdec_cnt_chg_t;

/**
  \brief Define the position accumulation counter to be increased/decreased by 1
*/
enum  qdec_resolution_e
{
    One_Phase   = 0,
    Two_Phase   = 1 
};
typedef uint8_t qdec_resolution_t;

/**
  \brief Define the source of the rotation counter
*/
enum  qdec_rotation_source_e
{
    Index_Event             = 0,
    PC_Over_Or_Under_Flow   = 1 
};
typedef uint8_t qdec_rotation_source_t;

/**
  \brief Define the level of the index input for QDEC
*/
enum  qdec_index_level_e
{
    Input_Low         = 0,
    Input_High        = 1 
};
typedef uint8_t qdec_index_level_t;

/**
  \brief Define the method makes the index reset the position
*/
enum  qdec_index_rst_e
{
    Disable_Rst         = 0,
    Reset_1st_Index     = 1, 
    Reset_Every_Index   = 2
};
typedef uint8_t qdec_index_rst_t;

/**
  \brief Define the changed count of the position is the absolute value or not
*/
enum  qdec_vmuc_mode_e
{
    Absolute_Count      = 0,
    Not_Absolute_Count  = 1 
};
typedef uint8_t qdec_vmuc_mode_t;

/**
  \brief Define the edge event for measuring the time between two edge events
*/
enum  qdec_edge_event_e
{
    Change_1_Edge       = 0,
    Change_2_Edge       = 1, 
    Change_4_Edge       = 2, 
    Change_8_Edge       = 3, 
    Change_16_Edge      = 4,
    Change_32_Edge      = 5, 
    Change_64_Edge      = 6, 
    Change_128_Edge     = 7, 
    Change_256_Edge     = 8, 
    Change_512_Edge     = 9, 
    Change_1024_Edge    = 10, 
    Change_2048_Edge    = 11 
};
typedef uint8_t qdec_edge_event_t;

/**
  \brief Define the intterupt event number for QDEC.
*/
enum  qdec_irq_shift_e
{
    Ct_sft      = 0,   
    Of_sft      = 1,   
    Uf_sft      = 2,   
    Il_sft      = 3,   
    Dr_sft      = 4,   
    Pc_sft      = 5,   
    Rof_sft     = 6,   
    Ruf_sft     = 7,   
    Idx_sft     = 8,   
    Pce_sft     = 9,   
    Vccap_sft   = 10,  
    Etcap_sft   = 11,  
    Vlowlmt_sft = 12,
    Vuplmt_sft  = 13, 
    Eterr_sft   = 14,  
    Rc_sft      = 15,
    Max_qdec_sft= 16
};
typedef uint8_t qdec_irq_shift_t;

/**
  \brief Define interrupt clock source type for QDEC.
*/
enum  qdec_irq_source_clk_e
{
    Qdec_Pclk       = 0,    ///< The qdec interrupt source clock = Pclk 
    Qdec_Sclk       = 1,    ///< he qdec interrupt source clock = Sclk 
    QdecClk_MAXID   = 2     ///< The Max index for group source clock source index 
};
typedef uint8_t qdec_irq_source_clk_t;

/**
  \brief Define sclk frequency for QDEC
*/
enum  qdec_source_clk_e
{
    QdecSClk_2M       = 0,    ///< The qdec source clock index = 2M 
    QdecSClk_32K      = 1,    ///< The tqdec source clock index = 32K 
    QdecSClk_MAXID    = 2     ///< The Max index for group source clock source index 
};
typedef uint8_t qdec_source_clk_t;

/**
  \brief  QDEC call back function for the interrupt event
*/
typedef void (*qdec_irq_user_cb_t)(void *);

/**
  \brief Define the common setting of the quadrature decoder
*/
typedef struct hal_qdec_init_s {
    u8                      smp_div;        /*!< Sampling Clock = source clock/(smp_div+1). Value: 0 ~ 31. */ 
    qdec_resolution_t       resolution;     /*!< The position accumulation counter. 0: 1 phase, 1: 2 phases. Only phase A edges are counted. */ 
    u16                     pc_maximum;     /*!< The maximum value of the position counter. Value: 0 ~ 65535. */ 
    qdec_rotation_source_t  rotation_mode;  /*!< 0: accumulate the rotation number when the index event occurres with direction(+/-), 1: accumulate the rotation number when the position counter occurres overflow(+)/underflow(-). */ 
    BOOL                    filter_enable;  /*!< 0: disable de-bounce. 1: enable de-bounce. */  
    u16                     filter_time;    /*!< De-bounce timer configuration, Value: 0 ~ 2047, unit is sclk: 0.5us or 31.25us. The time needs a little bigger than the maximum period of noise. */      
    BOOL                    index_enable;   /*!< 0: The index pulse signal detection is disabled. 1: enable. */        
    qdec_index_level_t      index_level;    /*!< 0: The index input is low. 1: The index input is lhigh. */      
    qdec_index_rst_t        index_rst;      /*!< The index input can reset the position counter. 0: disable, 1: only reset 1st, 2: reset every index. */ 
} hal_qdec_init_t, *phal_qdec_init_t;

/**
  \brief The parameter structure for initializing the interrupt event.   
*/
typedef struct hal_qdec_set_irq_s {
    BOOL int_en;                            /*!< 0: disbale this event interrupt, 1: enable. */       
    BOOL imr_en;                            /*!< 0: disbale mask event interrupt, 1: enable.  */
    BOOL callback_reg_en;                   /*!< 0: don't register this callback function, 1: register this callback function. */
    qdec_irq_user_cb_t callback;            /*!< The callback function. */
    void *arg;                              /*!< The callback argument. */  
} hal_qdec_set_irq_t, *phal_qdec_set_irq_t;

/**
  \brief  The data structure for an QDEC port HAL operations.
*/
typedef struct hal_qdec_adapter_s {
    QDEC_Type *base_addr;                   /*!< The QDEC register base address */
    qdec_pin_sel_t pin_sel;                 /*!< The QDEC pin mux selection */
    qdec_app_pin_sel_t app_pin_sel;         /*!< The QDEC application pin mux selection */
    qdec_source_clk_t sclk_idx;             /*!< Sclk frequency for QDEC */
    hal_qdec_init_t qdec_init_para;         /*!< The common setting of the quadrature decoder */ 
    u8 cb_priority_num[16];                 /*!< Record the interrupt event number */
    qdec_irq_user_cb_t irq_user_cb[16];     /*!< The QDEC call back function for the interrupt event */
    void *user_arg[16];                     /*! < The argument of call back function */
} hal_qdec_adapter_t, *phal_qdec_adapter_t;

/**
  \brief  The data structure to handle multiple QDEC adapters.
*/
typedef struct hal_qdec_group_adapter_s {
    volatile uint32_t critical_lv;                      /*!< Record QDEC HAL enter critical section level */
    hal_qdec_adapter_t *pqdec_adapter[MaxQdecNum];      /*!< All the QDEC adapters of this platform */
    irq_handler_t irq_fun[MaxQdecNum];                  /*!< The IRQ handler for different QDEC adapters */
} hal_qdec_group_adapter_t, *phal_qdec_group_adapter_t;


/// @cond DOXYGEN_ROM_HAL_API

/** 
 * @addtogroup ls_hal_qdec_rom_func QDEC HAL ROM APIs.
 * @{
 */

void hal_qdec_irq_handler_rtl8195blp (void *hid);
void hal_qdec_irq_reg_rtl8195blp (irq_handler_t handler);
void hal_qdec_unreg_rtl8195blp (void);
HAL_Status hal_qdec_init_rtl8195blp(hal_qdec_adapter_t *pqdec_adp, qdec_source_clk_t source_clk, qdec_pin_sel_t pin_sel, qdec_app_pin_sel_t app_pin_sel);
void hal_qdec_deinit_rtl8195blp (hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_enter_critical_rtl8195blp (void);
void hal_qdec_exit_critical_rtl8195blp (void);
void hal_qdec_info_rtl8195blp(hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_set_parameter_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_init_t *qdec_init);
void hal_qdec_reset_rtl8195blp (hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_set_init_phase_value_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, qdec_phase_t ini_phase, BOOL qdec_en_ctrl);
void hal_qdec_set_index_detect_phase_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, qdec_phase_t detect_phase, BOOL qdec_en_ctrl);
HAL_Status hal_qdec_cb_priority_check_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, u32 cb_priority, qdec_irq_shift_t irq_shift);
void hal_qdec_reg_cb_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, qdec_irq_user_cb_t callback, void *arg, qdec_irq_shift_t irq_shift);
void hal_qdec_unreg_cb_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, qdec_irq_shift_t irq_shift);
u32 hal_qdec_find_unreg_priority_rtl8195blp (hal_qdec_adapter_t *pqdec_adp);
HAL_Status hal_qdec_reg_event_cb_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq, qdec_irq_shift_t irq_shift);
HAL_Status hal_qdec_set_illegal_state_int_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_position_direction_change_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_position_count_change_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, u8 count_change_value, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_position_compare_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, u16 compare_value, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_position_overflow_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_position_underflow_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_rotation_compare_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, u16 compare_value, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_rotation_overflow_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_rotation_underflow_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_index_present_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_index_check_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
void hal_qdec_set_velocity_cnt_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, qdec_vmuc_mode_t vmuc_mode, u8 vt_div);
void hal_qdec_set_velocity_cnt_period_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, u16 time_period);
void hal_qdec_start_velocity_cnt_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, BOOL qdec_en_ctrl);
u32 hal_qdec_time_us_to_cnt_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, float time_us);
float hal_qdec_time_cnt_to_us_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, u16 time_cnt);
HAL_Status hal_qdec_set_velocity_cnt_interrupt_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_velocity_cnt_lowlmt_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, u16 low_limit_cnt, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_velocity_cnt_uplmt_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, u16 up_limit_cnt, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_velocity_time_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, qdec_edge_event_t phase_change, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_velocity_time_err_init_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
void hal_qdec_start_velocity_time_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, BOOL qdec_en_ctrl);
void hal_qdec_position_reset_rtl8195blp (hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_rotation_reset_rtl8195blp (hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_velocity_cnt_reset_rtl8195blp (hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_velocity_time_reset_rtl8195blp (hal_qdec_adapter_t *pqdec_adp);
float hal_qdec_get_velocity_cnt_rpm_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, u32 hw_pulse_per_rev, u16 velocity_cnt);

/** 
 *  @brief Quadrature decoder enable control.
 *         
 *  @param[in] pqdec_adp The qdec adapter.
 *  @param[in] qdec_en_ctrl 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_qdec_set_en_rtl8195blp (hal_qdec_adapter_t *pqdec_adp, BOOL qdec_en_ctrl)
{  
    pqdec_adp->base_addr->ctrl_b.axis_en = qdec_en_ctrl;
}

/** 
 *  @brief  Get the counts in a period of time.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns The capture value of the velocity counter.
 */
__STATIC_INLINE
u16 hal_qdec_get_velocity_cnt_rtl8195blp (hal_qdec_adapter_t *pqdec_adp)
{
    return (pqdec_adp->base_addr->vccap_b.vc_cap);
}

/** 
 *  @brief  Get the measuring time within the specified number of phase changes.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns The capture value of the edge timer.
 */
__STATIC_INLINE
u16 hal_qdec_get_velocity_time_rtl8195blp (hal_qdec_adapter_t *pqdec_adp)
{
    return (pqdec_adp->base_addr->etcap_b.et_cap);
}

/** 
 *  @brief  Get the position counter of QDEC.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns Position counter
 */
__STATIC_INLINE
u16 hal_qdec_get_pc_rtl8195blp (hal_qdec_adapter_t *pqdec_adp)
{
    return (pqdec_adp->base_addr->pc_b.pc);
}

/** 
 *  @brief  Get the rotation counter of QDEC.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns Rotation counter
 */
__STATIC_INLINE
u16 hal_qdec_get_rc_rtl8195blp (hal_qdec_adapter_t *pqdec_adp)
{
    return (pqdec_adp->base_addr->pc_b.rc);
}

/** 
 *  @brief  Get the movement direction of QDEC.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns 0: decrease, 1: increase
 */
__STATIC_INLINE
u8 hal_qdec_get_direction_rtl8195blp (hal_qdec_adapter_t *pqdec_adp)
{
    return (pqdec_adp->base_addr->pc_b.dir);
}

/** 
 *  @brief  Get the phase state of QDEC.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns Current state of (A, B) phase
 */
__STATIC_INLINE
u8 hal_qdec_get_phase_state_rtl8195blp (hal_qdec_adapter_t *pqdec_adp)
{
    return (pqdec_adp->base_addr->pc_b.sta);
}

/** 
 *  @brief  Check that the status of auto load to set initial phase
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns 0: auto load on-going, 1: auto load done
 */
__STATIC_INLINE
u8 hal_qdec_get_init_phase_state_rtl8195blp (hal_qdec_adapter_t *pqdec_adp)
{
    return (pqdec_adp->base_addr->pc_b.als);
}

/** 
 *  @brief  Get the velocity timer value of the down counter by measuring the counts
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns The velocity timer value.
 */
__STATIC_INLINE
u16 hal_qdec_get_velocity_cnt_downcnt_rtl8195blp (hal_qdec_adapter_t *pqdec_adp)
{
    return (pqdec_adp->base_addr->vt_b.vt);
}

/** 
 *  @brief  Get the edge timer value of the up counter by measuring the time
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns The edge timer value.
 */
__STATIC_INLINE
u16 hal_qdec_get_velocity_time_upcnt_rtl8195blp (hal_qdec_adapter_t *pqdec_adp)
{
    return (pqdec_adp->base_addr->et_b.et);
}

/** 
 *  @brief  Get the interrupt status register of the quadrature decoder
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns The interrupt status.
 */
__STATIC_INLINE
u32 hal_qdec_get_isr_rtl8195blp (hal_qdec_adapter_t *pqdec_adp)
{
    return (pqdec_adp->base_addr->isr);
}

/** @} */ /* End of group ls_hal_qdec_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */


/**
  \brief  The data structure of the stubs function for the QDEC HAL functions in ROM
*/
typedef struct hal_qdec_func_stubs_s {
    hal_qdec_group_adapter_t *pqdec_gadapter;
    const uint8_t *pqdec_pin_group;
    void (*hal_qdec_irq_handler) (void *hid);
    void (*hal_qdec_irq_reg) (irq_handler_t handler);
    void (*hal_qdec_unreg) (void);
    HAL_Status (*hal_qdec_init) (hal_qdec_adapter_t *pqdec_adp, qdec_source_clk_t source_clk, qdec_pin_sel_t pin_sel, qdec_app_pin_sel_t app_pin_sel);
    void (*hal_qdec_deinit) (hal_qdec_adapter_t *pqdec_adp);
    void (*hal_qdec_enter_critical) (void);
    void (*hal_qdec_exit_critical) (void);
    void (*hal_qdec_info) (hal_qdec_adapter_t *pqdec_adp);
    void (*hal_qdec_set_parameter) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_init_t *qdec_init);
    void (*hal_qdec_reset) (hal_qdec_adapter_t *pqdec_adp);
    void (*hal_qdec_set_init_phase_value) (hal_qdec_adapter_t *pqdec_adp, qdec_phase_t ini_phase, BOOL qdec_en_ctrl);
    void (*hal_qdec_set_index_detect_phase) (hal_qdec_adapter_t *pqdec_adp, qdec_phase_t detect_phase, BOOL qdec_en_ctrl);
    HAL_Status (*hal_qdec_cb_priority_check) (hal_qdec_adapter_t *pqdec_adp, u32 cb_priority, qdec_irq_shift_t irq_shift);
    void (*hal_qdec_reg_cb) (hal_qdec_adapter_t *pqdec_adp, qdec_irq_user_cb_t callback, void *arg, qdec_irq_shift_t irq_shift);
    void (*hal_qdec_unreg_cb) (hal_qdec_adapter_t *pqdec_adp, qdec_irq_shift_t irq_shift);
    u32 (*hal_qdec_find_unreg_priority) (hal_qdec_adapter_t *pqdec_adp);
    HAL_Status (*hal_qdec_reg_event_cb) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq, qdec_irq_shift_t irq_shift);
    HAL_Status (*hal_qdec_set_illegal_state_int) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_position_direction_change_init) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_position_count_change_init) (hal_qdec_adapter_t *pqdec_adp, u8 count_change_value, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_position_compare_init) (hal_qdec_adapter_t *pqdec_adp, u16 compare_value, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_position_overflow_init) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_position_underflow_init) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_rotation_compare_init) (hal_qdec_adapter_t *pqdec_adp, u16 compare_value, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_rotation_overflow_init) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_rotation_underflow_init) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_index_present_init) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_index_check_init) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
    void (*hal_qdec_set_velocity_cnt_init) (hal_qdec_adapter_t *pqdec_adp, qdec_vmuc_mode_t vmuc_mode, u8 vt_div);
    void (*hal_qdec_set_velocity_cnt_period) (hal_qdec_adapter_t *pqdec_adp, u16 time_period);
    void (*hal_qdec_start_velocity_cnt) (hal_qdec_adapter_t *pqdec_adp, BOOL qdec_en_ctrl);
    u32 (*hal_qdec_time_us_to_cnt) (hal_qdec_adapter_t *pqdec_adp, float time_us);
    float (*hal_qdec_time_cnt_to_us) (hal_qdec_adapter_t *pqdec_adp, u16 time_cnt);
    HAL_Status (*hal_qdec_set_velocity_cnt_interrupt) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_velocity_cnt_lowlmt_init) (hal_qdec_adapter_t *pqdec_adp, u16 low_limit_cnt, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_velocity_cnt_uplmt_init) (hal_qdec_adapter_t *pqdec_adp, u16 up_limit_cnt, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_velocity_time_init) (hal_qdec_adapter_t *pqdec_adp, qdec_edge_event_t phase_change, hal_qdec_set_irq_t *pqdec_set_irq);
    HAL_Status (*hal_qdec_set_velocity_time_err_init) (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
    void (*hal_qdec_start_velocity_time) (hal_qdec_adapter_t *pqdec_adp, BOOL qdec_en_ctrl);
    void (*hal_qdec_position_reset) (hal_qdec_adapter_t *pqdec_adp);
    void (*hal_qdec_rotation_reset) (hal_qdec_adapter_t *pqdec_adp);
    void (*hal_qdec_velocity_cnt_reset) (hal_qdec_adapter_t *pqdec_adp);
    void (*hal_qdec_velocity_time_reset) (hal_qdec_adapter_t *pqdec_adp);
    float (*hal_qdec_get_velocity_cnt_rpm) (hal_qdec_adapter_t *pqdec_adp, u32 hw_pulse_per_rev, u16 velocity_cnt);
    uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} hal_qdec_func_stubs_t;

/** @} */ /* End of group ls_hal_qdec */


#endif  // end of "#define _RTL8195BLP_QDEC_H_"

