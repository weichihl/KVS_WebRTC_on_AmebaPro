/**************************************************************************//**
 * @file     hal_qdec.h
 * @brief    The HAL API implementation for the QDEC device.
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

#ifndef _HAL_QDEC_H_
#define _HAL_QDEC_H_

#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup ls_hal_qdec QDEC
 * @ingroup 8195bl_hal
 * @{
 * @brief The QDEC HAL module of the LS platform.
 */

/**
  * @brief The stubs functions table to exports QDEC HAL functions in ROM.
  */
extern const hal_qdec_func_stubs_t hal_qdec_stubs;

/**
 *  @brief Quadrature decoder enable control.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *  @param[in] qdec_en_ctrl 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_qdec_set_en (hal_qdec_adapter_t *pqdec_adp, BOOL qdec_en_ctrl)
{
    pqdec_adp->base_addr->ctrl_b.axis_en = qdec_en_ctrl;
}

/**
 *  @brief Get quadrature decoder enable control.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
u8 hal_qdec_get_en (hal_qdec_adapter_t *pqdec_adp)
{
    return (u8)(pqdec_adp->base_addr->ctrl_b.axis_en);
}

/**
 *  @brief  Get the counts in a period of time.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns The capture value of the velocity counter.
 */
__STATIC_INLINE
u16 hal_qdec_get_velocity_cnt (hal_qdec_adapter_t *pqdec_adp)
{
    u16 temp;

    temp = (u16)pqdec_adp->base_addr->vccap_b.vc_cap;
    return temp;
}

/**
 *  @brief  Get the measuring time within the specified number of phase changes.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns The capture value of the edge timer.
 */
__STATIC_INLINE
u16 hal_qdec_get_velocity_time (hal_qdec_adapter_t *pqdec_adp)
{
    u16 temp;

    temp = (u16)pqdec_adp->base_addr->etcap_b.et_cap;
    return temp;
}

/**
 *  @brief  Get the position counter of QDEC.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns Position counter
 */
__STATIC_INLINE
u16 hal_qdec_get_pc (hal_qdec_adapter_t *pqdec_adp)
{
    u16 temp;

    temp = (u16)pqdec_adp->base_addr->pc_b.pc;
    return temp;
}

/**
 *  @brief  Get the rotation counter of QDEC.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns Rotation counter
 */
__STATIC_INLINE
u16 hal_qdec_get_rc (hal_qdec_adapter_t *pqdec_adp)
{
    u16 temp;

    temp = (u16)pqdec_adp->base_addr->pc_b.rc;
    return temp;
}

/**
 *  @brief  Get the movement direction of QDEC.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns 0: decrease, 1: increase
 */
__STATIC_INLINE
u8 hal_qdec_get_direction (hal_qdec_adapter_t *pqdec_adp)
{
    u8 temp;

    temp = (u8)pqdec_adp->base_addr->pc_b.dir;
    return temp;
}

/**
 *  @brief  Get the phase state of QDEC.
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns Current state of (A, B) phase
 */
__STATIC_INLINE
u8 hal_qdec_get_phase_state (hal_qdec_adapter_t *pqdec_adp)
{
    u8 temp;

    temp = (u8)pqdec_adp->base_addr->pc_b.sta;
    return temp;
}

/**
 *  @brief  Check that the status of auto load to set initial phase
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns 0: auto load on-going, 1: auto load done
 */
__STATIC_INLINE
u8 hal_qdec_get_init_phase_state (hal_qdec_adapter_t *pqdec_adp)
{
    u8 temp;

    temp = (u8)pqdec_adp->base_addr->pc_b.als;
    return temp;
}

/**
 *  @brief  Get the velocity timer value of the down counter by measuring the counts
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns The velocity timer value.
 */
__STATIC_INLINE
u16 hal_qdec_get_velocity_cnt_downcnt (hal_qdec_adapter_t *pqdec_adp)
{
    u16 temp;

    temp = (u16)pqdec_adp->base_addr->vt_b.vt;
    return temp;
}

/**
 *  @brief  Get the edge timer value of the up counter by measuring the time
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns The edge timer value.
 */
__STATIC_INLINE
u16 hal_qdec_get_velocity_time_upcnt (hal_qdec_adapter_t *pqdec_adp)
{
    u16 temp;

    temp = (u16)pqdec_adp->base_addr->et_b.et;
    return temp;
}

/**
 *  @brief  Get the interrupt status register of the quadrature decoder
 *
 *  @param[in] pqdec_adp The qdec adapter.
 *
 *  @returns The interrupt status.
 */
__STATIC_INLINE
u32 hal_qdec_get_isr (hal_qdec_adapter_t *pqdec_adp)
{
    u32 temp;

    temp = pqdec_adp->base_addr->isr;
    return temp;
}

/** @} */ /* End of group ls_hal_qdec */


void hal_qdec_irq_handler (void *hid);
void hal_qdec_irq_reg (irq_handler_t handler);
void hal_qdec_unreg (void);
HAL_Status hal_qdec_init (hal_qdec_adapter_t *pqdec_adp, qdec_source_clk_t source_clk, qdec_pin_sel_t pin_sel, qdec_app_pin_sel_t app_pin_sel);
void hal_qdec_deinit (hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_enter_critical (void);
void hal_qdec_exit_critical (void);
void hal_qdec_info (hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_set_parameter (hal_qdec_adapter_t *pqdec_adp, hal_qdec_init_t *qdec_init);
void hal_qdec_reset (hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_set_init_phase_value (hal_qdec_adapter_t *pqdec_adp, qdec_phase_t ini_phase, BOOL qdec_en_ctrl);
void hal_qdec_set_index_detect_phase (hal_qdec_adapter_t *pqdec_adp, qdec_phase_t detect_phase, BOOL qdec_en_ctrl);
HAL_Status hal_qdec_cb_priority_check (hal_qdec_adapter_t *pqdec_adp, u32 cb_priority, qdec_irq_shift_t irq_shift);
void hal_qdec_reg_cb (hal_qdec_adapter_t *pqdec_adp, qdec_irq_user_cb_t callback, void *arg, qdec_irq_shift_t irq_shift);
void hal_qdec_unreg_cb (hal_qdec_adapter_t *pqdec_adp, qdec_irq_shift_t irq_shift);
u32 hal_qdec_find_unreg_priority (hal_qdec_adapter_t *pqdec_adp);
HAL_Status hal_qdec_reg_event_cb (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq, qdec_irq_shift_t irq_shift);
HAL_Status hal_qdec_set_illegal_state_int (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_position_direction_change_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_position_count_change_init (hal_qdec_adapter_t *pqdec_adp, u8 count_change_value, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_position_compare_init (hal_qdec_adapter_t *pqdec_adp, u16 compare_value, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_position_overflow_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_position_underflow_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_rotation_compare_init (hal_qdec_adapter_t *pqdec_adp, u16 compare_value, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_rotation_overflow_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_rotation_underflow_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_index_present_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_index_check_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
void hal_qdec_set_velocity_cnt_init (hal_qdec_adapter_t *pqdec_adp, qdec_vmuc_mode_t vmuc_mode, u8 vt_div);
void hal_qdec_set_velocity_cnt_period (hal_qdec_adapter_t *pqdec_adp, u16 time_period);
void hal_qdec_start_velocity_cnt (hal_qdec_adapter_t *pqdec_adp, BOOL qdec_en_ctrl);
u32 hal_qdec_time_us_to_cnt (hal_qdec_adapter_t *pqdec_adp, float time_us);
float hal_qdec_time_cnt_to_us (hal_qdec_adapter_t *pqdec_adp, u16 time_cnt);
HAL_Status hal_qdec_set_velocity_cnt_interrupt (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_velocity_cnt_lowlmt_init (hal_qdec_adapter_t *pqdec_adp, u16 low_limit_cnt, hal_qdec_set_irq_t *pqdec_set_irq);
HAL_Status hal_qdec_set_velocity_cnt_uplmt_init (hal_qdec_adapter_t *pqdec_adp, u16 up_limit_cnt, hal_qdec_set_irq_t *pqdec_set_irq);
void hal_qdec_position_reset (hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_rotation_reset (hal_qdec_adapter_t *pqdec_adp);
void hal_qdec_velocity_cnt_reset (hal_qdec_adapter_t *pqdec_adp);
float hal_qdec_get_velocity_cnt_rpm (hal_qdec_adapter_t *pqdec_adp, u32 hw_pulse_per_rev, u16 velocity_cnt);



#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_CIR_H_"

