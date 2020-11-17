/**************************************************************************//**
 * @file     hal_qdec.c
 * @brief    This QDEC HAL API functions.
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

#include "hal_pinmux.h"
#include "hal_qdec.h"
#include "hal.h"

#if CONFIG_QDEC_EN

/**
 * @addtogroup ls_hal_qdec QDEC
 * @{
 */


/**
 *  @brief The QDEC interrupt handler.
 *
 *  @param[in]  hid The handler ID, it should be the QDEC adapter.
 *
 *  @returns void
 */
void hal_qdec_irq_handler (void *hid)
{
    hal_qdec_stubs.hal_qdec_irq_handler (hid);
}

/**
 *  @brief To register a IRQ handler for the QDEC.
 *
 *  @param[in]  handler The interrupt handle function.
 *
 *  @returns void
 */
void hal_qdec_irq_reg (irq_handler_t handler)
{
    hal_qdec_stubs.hal_qdec_irq_reg (handler);
}

/**
 *  @brief To un-register the QDEC IRQ handler.
 *
 *  @returns void
 */
void hal_qdec_unreg (void)
{
    hal_qdec_stubs.hal_qdec_unreg ();
}

/**
 *  @brief Initialize the QDEC hardware and turn on the QDEC
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  source_clk The QDEC peripheral frequency.
 *  @param[in]  pin_sel QDEC pin mux.
 *  @param[in]  app_pin_sel The pin combination is for the user application.
 *                      If the pin is selected, this pin will be initialized.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_init (hal_qdec_adapter_t *pqdec_adp, qdec_source_clk_t source_clk, qdec_pin_sel_t pin_sel, qdec_app_pin_sel_t app_pin_sel)
{
    hal_status_t ret;
    io_pin_t *pin_list;
    u8 qdec_app_pin_sel_table[2] = {0, 3};

    pin_list = (io_pin_t *)&hal_qdec_stubs.pqdec_pin_group[pin_sel * 7 + qdec_app_pin_sel_table[app_pin_sel]];
    ret = hal_pinmux_register (pin_list, PID_QDEC0);
    if (ret == HAL_OK) {
        return hal_qdec_stubs.hal_qdec_init (pqdec_adp, source_clk, pin_sel, app_pin_sel);
    } else {
        return ret;
    }
}

/**
 *  @brief De-initialize of the QDEC hardware and turn off the QDEC.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *
 *  @returns void
 */
void hal_qdec_deinit (hal_qdec_adapter_t *pqdec_adp)
{
    io_pin_t *pin_list;
    u8 qdec_app_pin_sel_table[2] = {0, 3};

    hal_qdec_stubs.hal_qdec_deinit (pqdec_adp);
    pin_list = (io_pin_t *)&hal_qdec_stubs.pqdec_pin_group[pqdec_adp->pin_sel * 7 + qdec_app_pin_sel_table[pqdec_adp->app_pin_sel]];
    hal_pinmux_unregister (pin_list, PID_QDEC0);
}

/**
*  @brief To enter a critical code section, mainly it
*         disable the QDEC interrupt to prevent race condition.
*
*  @returns void
*/
void hal_qdec_enter_critical (void)
{
    hal_qdec_stubs.hal_qdec_enter_critical ();
}

/**
 *  @brief To exit a critical code section, it will re-enable the QDEC interrupt
 *         only when the exiting critical section is the top level.
 *
 *  @returns void
 */
void hal_qdec_exit_critical (void)
{
    hal_qdec_stubs.hal_qdec_exit_critical ();
}

/**
 *  @brief To show the QDEC information.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *
 *  @returns void
 */
void hal_qdec_info (hal_qdec_adapter_t *pqdec_adp)
{
    hal_qdec_stubs.hal_qdec_info (pqdec_adp);
}

/**
 *  @brief Set the common setting of the quadrature decoder
 *
 *  @param[in]  pqdec_adp The qdec adapter.
 *  @param[in]  qdec_init The parameter structure for initializing the QDEC.
 *                      smp_div  - Sampling Clock = source clock/(smp_div+1). Value: 0 ~ 31
 *                      resolution - The position accumulation counter. 0: 1 phase, 1: 2 phases. Only phase A edges are counted.
 *                      pc_maximum - The maximum value of the position counter. Value: 0 ~ 65535.
 *                      rotation_mode - 0: accumulate the rotation number when the index event occurres with direction(+/-), 1: accumulate the rotation number when the position counter occurres overflow(+)/underflow(-).
 *                      filter_enable - 0: disable de-bounce. 1: enable de-bounce.
 *                      filter_time - De-bounce timer configuration, Value: 0 ~ 2047, unit is sclk: 0.5us or 31.25us. The time needs a little bigger than the maximum period of noise.
 *                      index_enable - 0: The index pulse signal detection is disabled. 1: enable.
 *                      index_level - 0: The index input is low. 1: The index input is lhigh.
 *                      index_rst - The index input can reset the position counter. 0: disable, 1: only reset 1st, 2: reset every index.
 *
 *  @returns void
 */
void hal_qdec_set_parameter (hal_qdec_adapter_t *pqdec_adp, hal_qdec_init_t *qdec_init)
{
    hal_qdec_stubs.hal_qdec_set_parameter (pqdec_adp, qdec_init);
    hal_delay_us(150);
}

/**
 *  @brief Reset the quadrature decoder
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *
 *  @returns void
 */
void hal_qdec_reset (hal_qdec_adapter_t *pqdec_adp)
{
    hal_qdec_stubs.hal_qdec_reset (pqdec_adp);
    hal_delay_us(150);
}

/**
 *  @brief This function can close the auto detection of initial phase. Need to set the initial values of phase A and Phase B.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  ini_phase The manual initial phase state of the quadrature decoder.
 *                      -00: Phase state of (A,B) is (0,0).
 *                      -01: Phase state of (A,B) is (0,1).
 *                      -10: Phase state of (A,B) is (1,0).
 *                      -11: Phase state of (A,B) is (1,1).
 *  @param[in]  qdec_en_ctrl 0: Auto load, 1: Enable manual set.
 *
 *  @returns void
 */
void hal_qdec_set_init_phase_value (hal_qdec_adapter_t *pqdec_adp, qdec_phase_t ini_phase, BOOL qdec_en_ctrl)
{
    hal_qdec_stubs.hal_qdec_set_init_phase_value (pqdec_adp, ini_phase, qdec_en_ctrl);
    hal_delay_us(150);
}

/**
 *  @brief This function will close the auto detection of index. Need to set the detected condition of phase A and Phase B when the index pluse happens.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  detect_phase The manual initial phase state of the quadrature decoder.
 *                      -00: Phase state of (A,B) is (0,0).
 *                      -01: Phase state of (A,B) is (0,1).
 *                      -10: Phase state of (A,B) is (1,0).
 *                      -11: Phase state of (A,B) is (1,1).
 *  @param[in]  qdec_en_ctrl 0: Auto load, 1: Enable manual set.
 *
 *  @returns void
 */
void hal_qdec_set_index_detect_phase (hal_qdec_adapter_t *pqdec_adp, qdec_phase_t detect_phase, BOOL qdec_en_ctrl)
{
    hal_qdec_stubs.hal_qdec_set_index_detect_phase (pqdec_adp, detect_phase, qdec_en_ctrl);
    hal_delay_us(150);
}

/**
 *  @brief Set the priority of the interrupt event, and check this priority is valid.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  cb_priority Set the priority of interrupt, and this value is not the same. 0 is the highest priority. Value: 0 ~ 15.
 *  @param[in]  irq_shift The intterupt event number.
 *
 *  @return     HAL_ERR_PARA:  Setting priority is invalid.
 *  @return     HAL_OK:  Setting is OK.
 */
HAL_Status hal_qdec_cb_priority_check (hal_qdec_adapter_t *pqdec_adp, u32 cb_priority, qdec_irq_shift_t irq_shift)
{
    return hal_qdec_stubs.hal_qdec_cb_priority_check (pqdec_adp, cb_priority, irq_shift);
}

/**
 *  @brief Register the callback function and argument of the interrupt event.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  callback The callback function.
 *  @param[in]  arg The callback argument.
 *  @param[in]  irq_shift TThe intterupt event number.
 *
 *  @returns void
 */
void hal_qdec_reg_cb (hal_qdec_adapter_t *pqdec_adp, qdec_irq_user_cb_t callback, void *arg, qdec_irq_shift_t irq_shift)
{
    hal_qdec_stubs.hal_qdec_reg_cb (pqdec_adp, callback, arg, irq_shift);
}

/**
 *  @brief Cancel the callback function and argument of the interrupt event.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  irq_shift The intterupt event number.
 *
 *  @returns void
 */
void hal_qdec_unreg_cb (hal_qdec_adapter_t *pqdec_adp, qdec_irq_shift_t irq_shift)
{
    hal_qdec_stubs.hal_qdec_unreg_cb (pqdec_adp, irq_shift);
}

/**
 *  @brief Find that the smallest priority number can be used.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *
 *  @returns    The smallest priority number.
 */
u32 hal_qdec_find_unreg_priority (hal_qdec_adapter_t *pqdec_adp)
{
    return hal_qdec_stubs.hal_qdec_find_unreg_priority (pqdec_adp);
}

/**
 *  @brief Register the callback function and argument according to the interrupt event.
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *  @param[in]  irq_shift irq_shift The intterupt event number.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_reg_event_cb (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq, qdec_irq_shift_t irq_shift)
{
    return hal_qdec_stubs.hal_qdec_reg_event_cb (pqdec_adp, pqdec_set_irq, irq_shift);
}

/**
 *  @brief  Control to enable the interrupt and mask the interrupt event for happening the illegal state.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_illegal_state_int (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_illegal_state_int (pqdec_adp, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt event for changing the direction.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_position_direction_change_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp =  hal_qdec_stubs.hal_qdec_set_position_direction_change_init (pqdec_adp, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt event. Set a value changed on the position counter which will trigger the position changed interrupt
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  count_change_value This field set a value changed on the position counter which will trigger the position changed interrupt.
 *                      -00: +/- 1.
 *                      -01: +/- 2.
 *                      -10: +/- 4.
 *                      -11: reserved.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_position_count_change_init (hal_qdec_adapter_t *pqdec_adp, u8 count_change_value, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_position_count_change_init (pqdec_adp, count_change_value, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt when the position counter is equal to the compare value.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  compare_value If the position counter is equal to this value, the corresponding interrupt will be asserted. The value is 0x00~0xFFFF.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_position_compare_init (hal_qdec_adapter_t *pqdec_adp, u16 compare_value, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_position_compare_init (pqdec_adp, compare_value, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt when the position counter value is overflow (Max position counter -> 0x0000).
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_position_overflow_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_position_overflow_init (pqdec_adp, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt when the position counter value is underflow (0x0000 -> Max position counter).
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_position_underflow_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_position_underflow_init (pqdec_adp, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt when the rotation counter is equal to the rotation value.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  compare_value If the rotation counter is equal to this value, the corresponding interrupt will be asserted. The value is 0x00~0xFFF.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_rotation_compare_init (hal_qdec_adapter_t *pqdec_adp, u16 compare_value, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_rotation_compare_init (pqdec_adp, compare_value, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt when the rotation counter value is overflow (Max rotation counter -> 0x0000).
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_rotation_overflow_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_rotation_overflow_init (pqdec_adp, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt when the rotation counter value is underflow (0x0000 -> Max position counter).
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_rotation_underflow_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_rotation_underflow_init (pqdec_adp, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt when detect the index is present.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_index_present_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_index_present_init (pqdec_adp, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt for checking that the position counter is zero at the present of index.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_index_check_init (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_index_check_init (pqdec_adp, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Initial the velocity function. Get the velocity by measuring the counts in a period of time.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  vmuc_mode 0: the counter value uses the absolute value, 1: the counter value does not use the absolute value
 *  @param[in]  vt_div Measuring Clock = source clock /(vt_div+1).
 *
 *  @returns void
 */
void hal_qdec_set_velocity_cnt_init (hal_qdec_adapter_t *pqdec_adp, qdec_vmuc_mode_t vmuc_mode, u8 vt_div)
{
    hal_qdec_stubs.hal_qdec_set_velocity_cnt_init (pqdec_adp, vmuc_mode, vt_div);
    hal_delay_us(150);
}

/**
 *  @brief Set a period of time for measuring the counts
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  time_period The time_period value is 0x00~0xFFFF. Measure time = time_period / (source clock /(smp_div+1)).
 *
 *  @returns void
 */
void hal_qdec_set_velocity_cnt_period (hal_qdec_adapter_t *pqdec_adp, u16 time_period)
{
    hal_qdec_stubs.hal_qdec_set_velocity_cnt_period (pqdec_adp, time_period);
    hal_delay_us(150);
}

/**
 *  @brief Start to measure counts in a period of time.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  qdec_en_ctrl 0: disable measure, 1: enable measure.
 *
 *  @returns void
 */
void hal_qdec_start_velocity_cnt (hal_qdec_adapter_t *pqdec_adp, BOOL qdec_en_ctrl)
{
    hal_qdec_stubs.hal_qdec_start_velocity_cnt (pqdec_adp, qdec_en_ctrl);
    hal_delay_us(150);
}

/**
 *  @brief Change the time unit from us to counts.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  time_us Measure time. This unit is us.
 *
 *  @returns Calculate the result, and the unit is count.
 */
u32 hal_qdec_time_us_to_cnt (hal_qdec_adapter_t *pqdec_adp, float time_us)
{
    return hal_qdec_stubs.hal_qdec_time_us_to_cnt (pqdec_adp, time_us);
}

/**
 *  @brief Change the time unit from counts to us.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  time_cnt Measure time. This unit is count.
 *
 *  @returns Calculate the result, and the unit is us.
 */
float hal_qdec_time_cnt_to_us (hal_qdec_adapter_t *pqdec_adp, u16 time_cnt)
{
    return hal_qdec_stubs.hal_qdec_time_cnt_to_us (pqdec_adp, time_cnt);
}

/**
 *  @brief Control to enable the interrupt and mask the interrupt when the measuring time is timeout.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_velocity_cnt_interrupt (hal_qdec_adapter_t *pqdec_adp, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_velocity_cnt_interrupt (pqdec_adp, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief The measuring counts is less than the low limit. This interrupt will be asserted.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  low_limit_cnt The low limit value is 0x00~0xFFFF.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_velocity_cnt_lowlmt_init (hal_qdec_adapter_t *pqdec_adp, u16 low_limit_cnt, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_velocity_cnt_lowlmt_init (pqdec_adp, low_limit_cnt, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief The measuring counts is bigger than the up limit. This interrupt will be asserted.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  up_limit_cnt The up limit value is 0x00~0xFFFF.
 *  @param[in]  pqdec_set_irq The parameter structure for initializing the interrupt event.
 *                      int_en - 0: disbale this event interrupt, 1: enable.
 *                      imr_en - 0: disbale mask event interrupt, 1: enable.
 *                      callback_reg_en - 0: don't register this callback function, 1: register this callback function.
 *                      callback - The callback function.
 *                      arg - The callback argument.
 *
 *  @return     HAL_ERR_PARA
 *  @return     HAL_OK
 */
HAL_Status hal_qdec_set_velocity_cnt_uplmt_init (hal_qdec_adapter_t *pqdec_adp, u16 up_limit_cnt, hal_qdec_set_irq_t *pqdec_set_irq)
{
    HAL_Status s_temp;

    s_temp = hal_qdec_stubs.hal_qdec_set_velocity_cnt_uplmt_init (pqdec_adp, up_limit_cnt, pqdec_set_irq);
    hal_delay_us(150);

    return s_temp;
}

/**
 *  @brief Reset the position of QDEC.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *
 *  @returns void
 */
void hal_qdec_position_reset (hal_qdec_adapter_t *pqdec_adp)
{
    hal_qdec_stubs.hal_qdec_position_reset (pqdec_adp);
    hal_delay_us(150);
}

/**
 *  @brief Reset the rotation of QDEC.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *
 *  @returns void
 */
void hal_qdec_rotation_reset (hal_qdec_adapter_t *pqdec_adp)
{
    hal_qdec_stubs.hal_qdec_rotation_reset (pqdec_adp);
    hal_delay_us(150);
}

/**
 *  @brief Reset the velocity function of measuring counts.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *
 *  @returns void
 */
void hal_qdec_velocity_cnt_reset (hal_qdec_adapter_t *pqdec_adp)
{
    hal_qdec_stubs.hal_qdec_velocity_cnt_reset (pqdec_adp);
    hal_delay_us(150);
}

/**
 *  @brief Get the revolution per minute.
 *
 *  @param[in]  pqdec_adp The QDEC adapter.
 *  @param[in]  hw_pulse_per_rev The number of pulses per revolution to the quadrature encoder
 *  @param[in]  velocity_cnt Measure counts in a period of time.
 *
 *  @returns The result.
 */
float hal_qdec_get_velocity_cnt_rpm (hal_qdec_adapter_t *pqdec_adp, u32 hw_pulse_per_rev, u16 velocity_cnt)
{
    return hal_qdec_stubs.hal_qdec_get_velocity_cnt_rpm (pqdec_adp, hw_pulse_per_rev, velocity_cnt);
}

/** @} */ /* End of group ls_hal_qdec */

#endif




