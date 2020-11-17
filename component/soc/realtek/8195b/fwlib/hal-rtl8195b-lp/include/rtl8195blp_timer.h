/**************************************************************************//**
 * @file     rtl8195blp_timer.h
 * @brief    The HAL related definition and macros for the TIMER device.
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

#ifndef RTL8195BLP_TIMER_H
#define RTL8195BLP_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "rtl8195blp_tg_type.h"
#include "rtl8195blp_tm_type.h"

/**
 * @addtogroup ls_hal_timer TIMER
 * @{
 */

/**
  * \brief Define timer ID
**/
enum  timer_id_e {
    GTimer0           = 0, //!< Gtimer0
    GTimer1           = 1, //!< Gtimer1
    GTimer2           = 2, //!< Gtimer2
    GTimer3           = 3, //!< Gtimer3
    GTimer4           = 4, //!< Gtimer4
    GTimer5           = 5, //!< Gtimer5
    GTimer6           = 6, //!< Gtimer6
    GTimer7           = 7, //!< Gtimer7

    MaxGTimerNum      = 8  //!< MAX Gtimer Number
};
typedef uint8_t timer_id_t;

/**
  * \brief Define  timer counter value match event ID
**/
enum  timer_match_event_e {
    GTimerMatchEvent0     = 0, //!< Gtimer Match Event 0
    GTimerMatchEvent1     = 1, //!< Gtimer Match Event 1
    GTimerMatchEvent2     = 2, //!< Gtimer Match Event 2
    GTimerMatchEvent3     = 3, //!< Gtimer Match Event 3

    MaxGTimerMatchEvent   = 4 //!< MAX Gtimer Match Event
};
typedef uint8_t timer_match_event_t;

/**
  * \brief Define timer interrupt circute clock source
**/
enum  timer_interrupt_clk_e {
    GTimer_PCLK     = 0, //!< APB clock
    GTimer_SCLK     = 1  //!< SCLK: system clock
};
typedef uint8_t timer_interrupt_clk_t;

/**
  * \brief Define timer operation mode, as the timer control.mode register
**/
enum  timer_op_mode_e {
    GTimerMode_Timer    = 0, //!< Timer mode: reload and repeat mode
    GTimerMode_Counter  = 1  //!< Counter mode: one shot mode
};
typedef uint8_t timer_op_mode_t;

/**
  * \brief Define  timer countting mode, as the timer control.cnt_mode register
**/
enum  timer_cnt_mode_e {
    GTimerCountUp    = 0, //!< Up countting
    GTimerCountDown  = 1  //!< Down countting
};
typedef uint8_t timer_cnt_mode_t;

/**
  * \brief Define  timer interrupt trigger events, as the timer ISR register
**/
enum  timer_interrupt_event_e {
    GTimerIntTimeout    = 0x01, //!< Timeout
    GTimerIntME0        = 0x02, //!< Counter matched event 0
    GTimerIntME1        = 0x04, //!<  Counter matched event 1
    GTimerIntME2        = 0x08, //!< Counter matched event 2
    GTimerIntME3        = 0x10  //!< Counter matched event 3
};
typedef uint8_t timer_interrupt_event_t;

/**
  * \brief Define timer interrupt clk source
**/
enum  timer_source_clk_e {
    GTimerSClk_4M       = 0, //!< The timer group source clock index = 4M
    GTimerSClk_2M       = 1, //!< The timer group source clock index = 2M
    GTimerSClk_32K      = 2, //!< The timer group source clock index = 32K
    GTimerSClk_Ex32K    = 3, //!< The timer group source clock index = external 32768
    GTimerSClk_MAXID    = 4  //!< The max timer group source clock index
};
typedef uint8_t timer_source_clk_t;

/**
  * \brief emulation for timer enable control
**/
enum  timer_enable_e {
    GTimer_Disable  = 0,   //!< Enable
    GTimer_Enable   = 1    //!< Disable
};

/**
  * \brief define timer operation method for application
**/
enum  timer_app_mode_e {
    GTimerOneShot      = GTimerMode_Counter, //!< One shot timer
    GTimerPeriodical    = GTimerMode_Timer   //!< Periodical timer
};
typedef uint8_t timer_app_mode_t;

/*! define the number of timer in a timer group */
#define GTIMER_GROUP_TIMER_NUM      8

/*******************************************************************************
 *                 Register Abstraction
  Register contain:
 ******************************************************************************/

/*! define timer interrupt call back function */
typedef void (*timer_callback_t) (void *);

typedef struct hal_timer_group_adapter_s hal_timer_group_adapter_t, *phal_timer_group_adapter_t;

/**
  \brief  The data structure to handle a HW timer, includes the configuration, register base address
          and interrupt call back functions.
*/
typedef struct hal_timer_adapter_s {
    TM0_Type *tmr_ba;      /*!< The timer register base address */
    TG0_Type *tg_ba;      /*!< The timer group register base address */
    hal_timer_group_adapter_t *ptg_adp;   /*!< The timer group adapter for this timer adapter belong to */
    u32 tick_us; /*! the period time of a tick, in us */
    u32 tick_r_ns; /*! the after zero point of period time of a tick, in ns */
    u16 pre_scaler; /*! the pre-scaler value */
    timer_id_t tid;   /*! The timer index */
    timer_app_mode_t reload_mode;    /* timer counter reload mode, one shot or periodical */
    u32 overflow_fired;     /* the timer counter overflow/inderflow hit count */

    timer_callback_t timeout_callback;      /*! User callback function for timeout indication */
    void *to_cb_para;   /*! the argument for user timeout callback function */
    timer_callback_t me_callback[4];      /*! User callback function for counter value match event 0 ~ 3 */
    void *me_cb_para[4];   /*! the argument for user counter match event 0 ~ 3 callback function */
    void (*enter_critical)(void);   /*! the function for entering timer critical state */
    void (*exit_critical)(void);    /*! the function for exit timer critical state */

    u32 reserved[4];      // reserved
} hal_timer_adapter_t, *phal_timer_adapter_t;

/**
  \brief  The data structure to handle a HW timer group, includes the configuration, register base address
          and timer adapters those belong to this timer group.
*/
struct hal_timer_group_adapter_s {
    TG0_Type *tg_ba;      /*!< The timer group register base address */
    hal_timer_adapter_t *timer_adapter[MaxGTimerNum];   /*!< All the timer adapter belong to this timer group */
    timer_source_clk_t  sclk_idx;  /*!< the source clock index. Default 32K (index 0) */
    u8  tmr_in_use; /*!< the indication of timer is allocated by someone, bit 0 ~ 7 map to timer 0 ~ 7 */
    u8  tgid;   /*!< the timer group ID, it should be always 0 for low power domain */
//    u8  tgctrl;   /*!< the timer group control, it's store the setting of the Timer Group Control register */
};

/**
  \brief  The data structure of the stubs function for the Timer HAL functions in ROM
*/
typedef struct hal_timer_func_stubs_s {
    phal_timer_group_adapter_t *pptimer_group;
    u32 (*hal_timer_convert_ticks_to_us) (u32 ticks, u8 sclk_idx);
    u32 (*hal_timer_convert_us_to_ticks) (u32 time_us, u8 sclk_idx);
    u64 (*hal_timer_convert_ticks_to_us64)  (u64 ticks, u8 sclk_idx);
    u64 (*hal_timer_convert_us_to_ticks64)  (u64 time_us, u8 sclk_idx);
    void (*hal_timer_irq_handler) (void);
    void (*hal_timer_me_ctrl) (phal_timer_adapter_t ptimer_adp, timer_match_event_t match_ev, u8 enable);
    void (*hal_timer_set_me_counter) (phal_timer_adapter_t ptimer_adp, timer_match_event_t match_ev, u32 counter);
    void (*hal_timer_group_sclk_sel) (hal_timer_group_adapter_t *ptg_adp, u32 sclk_freq);
    void (*hal_timer_group_init) (hal_timer_group_adapter_t *ptg_adp, uint32_t tgid);
    void (*hal_timer_group_deinit) (hal_timer_group_adapter_t *ptg_adp);
    hal_status_t (*hal_timer_bare_init) (phal_timer_adapter_t ptimer_adp, timer_id_t tid);
    void (*hal_timer_deinit) (phal_timer_adapter_t ptimer_adp);
    void (*hal_timer_group_reg_irq) (hal_timer_group_adapter_t *ptg_adp, irq_handler_t irq_handler);
    void (*hal_timer_reg_toirq) (phal_timer_adapter_t ptimer_adp, timer_callback_t callback, void *phid);
    void (*hal_timer_unreg_toirq) (phal_timer_adapter_t ptimer_adp);
    void (*hal_timer_reg_meirq) (phal_timer_adapter_t ptimer_adp, u8 match_ev, timer_callback_t callback, void *phid);
    void (*hal_timer_unreg_meirq) (phal_timer_adapter_t ptimer_adp, u8 match_ev);
    u32 (*hal_timer_set_tick_time) (phal_timer_adapter_t ptimer_adp, u32 tick_ns);
    void (*hal_timer_init_free_run) (phal_timer_adapter_t ptimer_adp, timer_id_t tid, timer_cnt_mode_t cnt_mode, u32 tick_us);
    u32 (*hal_timer_indir_read) (phal_timer_adapter_t ptimer_adp);
    u64 (*hal_timer_read_us) (phal_timer_adapter_t ptimer_adp);
    u64 (*hal_timer_read_us64)(phal_timer_adapter_t ptimer_adp);
    hal_status_t (*hal_timer_init) (phal_timer_adapter_t ptimer_adp, timer_id_t tid);
    u32 (*hal_timer_set_timeout) (phal_timer_adapter_t ptimer_adp, u32 time_us, u32 res_us);
    void (*hal_timer_start) (phal_timer_adapter_t ptimer_adp, timer_app_mode_t reload_mode);
    hal_status_t (*hal_timer_enable_match_event) (phal_timer_adapter_t ptimer_adp, timer_match_event_t match_ev, u32 time_us);
    void (*hal_timer_disable_match_event) (phal_timer_adapter_t ptimer_adp, timer_match_event_t match_ev);
    void (*hal_timer_start_one_shot) (phal_timer_adapter_t ptimer_adp, u32 time_us,
                                       timer_callback_t callback, void *phid);
    void (*hal_timer_start_periodical) (phal_timer_adapter_t ptimer_adp, u32 time_us,
                                        timer_callback_t callback, void *phid);
    timer_id_t (*hal_timer_allocate) (u8 *timer_list);
    timer_id_t (*hal_timer_event_init) (phal_timer_adapter_t ptimer_adp, u32 *ptick_us, timer_id_t *timer_list);
    void (*hal_timer_event_deinit) (timer_id_t tid);

    // hal_misc timer related API
    phal_timer_adapter_t *ppsys_timer;
    u64 (*hal_read_systime) (void);
    u32 (*hal_read_curtime) (void);
    void (*hal_start_systimer) (phal_timer_adapter_t ptimer_adp, uint32_t tmr_id,
                                                timer_cnt_mode_t cnt_md, uint32_t tick_us);
    void (*hal_delay_us) (u32 time_us);

    BOOLEAN (*hal_is_timeout) (u32 start_us, u32 timeout_us);

    uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} hal_timer_func_stubs_t;


/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup ls_hal_timer_rom_func TIMER HAL ROM APIs.
 * @{
 */

/**
 *  @brief To read timer group interrupt status
 *
 *  @param[in] ptg_adp The timer group adapter.
 *
 *  @returns The interrupt pending status
 */
 __STATIC_INLINE
u8 hal_timer_group_get_ists_rtl8195blp (hal_timer_group_adapter_t *ptg_adp)
{
    return ptg_adp->tg_ba->ists_b.ists;
}

/**
 *  @brief To read timer group interrupt raw status (without mask)
 *
 *  @param[in] ptg_adp The timer group adapter.
 *
 *  @returns The interrupt pending status
 */
__STATIC_INLINE
u8 hal_timer_group_get_rists_rtl8195blp (hal_timer_group_adapter_t *ptg_adp)
{
    return ptg_adp->tg_ba->raw_ists_b.rists;
}

/**
 *  @brief To get the interrupt pending status (with mask).
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The interrupt pending status
 */
__STATIC_INLINE
u8 hal_timer_get_int_pending_rtl8195blp (phal_timer_adapter_t ptimer_adp)
{
    return ptimer_adp->tg_ba->ists_b.ists & (1 << ptimer_adp->tid);
}

/**
 *  @brief To get the interrupt pending status (without mask).
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The interrupt pending status
 */
__STATIC_INLINE
u8 hal_timer_get_rint_pending_rtl8195blp (phal_timer_adapter_t ptimer_adp)
{
    return ptimer_adp->tg_ba->raw_ists_b.rists & (1 << ptimer_adp->tid);
}

/**
 *  @brief To set the reload value for timer operation mode.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] reload The relaod counter value for timer mode.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_reload_rtl8195blp (phal_timer_adapter_t ptimer_adp, u32 reload)
{
    ptimer_adp->tmr_ba->lc = reload;
}

/**
 *  @brief To read the timer counter value
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The timer counter value
 */
__STATIC_INLINE
u32 hal_timer_read_rtl8195blp (phal_timer_adapter_t ptimer_adp)
{
#if 0
    u32 cnt;

    do {
        cnt = ptimer_adp->tmr_ba->tc;
    } while (cnt != ptimer_adp->tmr_ba->tc);

    return cnt;
#endif
    // if the timer clock source is 2M, it's impossible to get same value of 2 reading, since the CPU is slow.
    return (ptimer_adp->tmr_ba->tc);
}

/**
 *  @brief To set the timer counter value
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] tc The timer counter value.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_write_rtl8195blp (phal_timer_adapter_t ptimer_adp, u32 tc)
{
    ptimer_adp->tmr_ba->tc = tc;
}

/**
 *  @brief To write the timer pre-scale counter value
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] psc The pre-scale counter value
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_write_prescal_cnt_rtl8195blp (phal_timer_adapter_t ptimer_adp, u16 psc)
{
    ptimer_adp->tmr_ba->pc_b.pc = psc;
}

/**
 *  @brief To read the timer pre-scale counter value
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The pre-scaler current counter value
 */
__STATIC_INLINE
u16 hal_timer_read_prescal_cnt_rtl8195blp (phal_timer_adapter_t ptimer_adp)
{
    return ptimer_adp->tmr_ba->pc_b.pc;
}

/**
 *  @brief To set the reload value of the timer pre-scaler
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] psc The pre-scaler counter reload value
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_prescal_rtl8195blp (phal_timer_adapter_t ptimer_adp, u16 psrc)
{
//    ptimer_adp->pre_scaler = psrc;
    ptimer_adp->tmr_ba->pr_b.pr = psrc;
}

/**
 *  @brief To enable/start the timer.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_enable_rtl8195blp (phal_timer_adapter_t ptimer_adp)
{
    ptimer_adp->tmr_ba->ctrl_b.en = 1;
}

/**
 *  @brief To disable the timer.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_disable_rtl8195blp (phal_timer_adapter_t ptimer_adp)
{
    ptimer_adp->tmr_ba->ctrl_b.en = 0;
}

/**
 *  @brief To set the interrupt mask.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] imr The interrupt mask setting (0/1).
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_imr_rtl8195blp (phal_timer_adapter_t ptimer_adp, u8 imr)
{
    ptimer_adp->tmr_ba->ctrl_b.imr = imr;
}

/**
 *  @brief To set the timer operation mode: timer (reload) mode or counter (one shot) mode
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] op_mode The timer operation mode.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_opmode_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_op_mode_t op_mode)
{
    ptimer_adp->tmr_ba->ctrl_b.mod = op_mode;
}

/**
 *  @brief To set the timer countting mode. (up counter/ down counter)
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] cnt_mode The countting mode. 0: up countting, 1: down countting
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_set_cntmode_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_cnt_mode_t cnt_mode)
{
    ptimer_adp->tmr_ba->ctrl_b.cnt_mod = cnt_mode;
}

/**
 *  @brief To read the interrupt status.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *
 *  @returns The interrupt status
 */
__STATIC_INLINE
u32 hal_timer_read_isr_rtl8195blp (phal_timer_adapter_t ptimer_adp)
{
    return ptimer_adp->tmr_ba->isr;
}

/**
 *  @brief To clear the interrupt pending status.
 *
 *  @param[in] ptimer_adp The timer adapter.
 *  @param[in] int_ev The pending interrupt to be cleared
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_timer_clear_isr_rtl8195blp (phal_timer_adapter_t ptimer_adp, u32 int_ev)
{
    ptimer_adp->tmr_ba->isr = int_ev;
}

u32 hal_timer_convert_ticks_to_us_rtl8195blp  (u32 ticks, u8 sclk_idx);
u32 hal_timer_convert_us_to_ticks_rtl8195blp  (u32 time_us, u8 sclk_idx);
u64 hal_timer_convert_ticks_to_us64_rtl8195blp  (u64 ticks, u8 sclk_idx);
u64 hal_timer_convert_us_to_ticks64_rtl8195blp  (u64 time_us, u8 sclk_idx);
void hal_timer_me_ctrl_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_match_event_t match_ev, u8 enable);
void hal_timer_set_me_counter_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_match_event_t match_ev, u32 counter);
void hal_timer_group_sclk_sel_rtl8195blp (hal_timer_group_adapter_t *ptg_adp, u32 sclk_freq);
void hal_timer_group_init_rtl8195blp (hal_timer_group_adapter_t *ptg_adp, uint32_t tgid);
void hal_timer_group_deinit_rtl8195blp (hal_timer_group_adapter_t *ptg_adp);
hal_status_t hal_timer_bare_init_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_id_t tid);
void hal_timer_deinit_rtl8195blp (phal_timer_adapter_t ptimer_adp);
void hal_timer_group_reg_irq_rtl8195blp (hal_timer_group_adapter_t *ptg_adp, irq_handler_t irq_handler);
void hal_timer_reg_toirq_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_callback_t callback, void *phid);
void hal_timer_unreg_toirq_rtl8195blp (phal_timer_adapter_t ptimer_adp);
void hal_timer_reg_meirq_rtl8195blp (phal_timer_adapter_t ptimer_adp, u8 match_ev,
                                     timer_callback_t callback, void *phid);
void hal_timer_unreg_meirq_rtl8195blp (phal_timer_adapter_t ptimer_adp, u8 match_ev);
u32 hal_timer_set_tick_time_rtl8195blp (phal_timer_adapter_t ptimer_adp, u32 tick_ns);
void hal_timer_init_free_run_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_id_t tid,
                                         timer_cnt_mode_t cnt_mode, u32 tick_us);
u32 hal_timer_indir_read_rtl8195blp (phal_timer_adapter_t ptimer_adp);
u64 hal_timer_read_us_rtl8195blp (phal_timer_adapter_t ptimer_adp);
u64 hal_timer_read_us64_rtl8195blp (phal_timer_adapter_t ptimer_adp);
hal_status_t hal_timer_init_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_id_t tid);
u32 hal_timer_set_timeout_rtl8195blp (phal_timer_adapter_t ptimer_adp, u32 time_us, u32 res_us);
void hal_timer_start_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_app_mode_t reload_mode);
hal_status_t hal_timer_enable_match_event_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_match_event_t match_ev, u32 time_us);
void hal_timer_disable_match_event_rtl8195blp (phal_timer_adapter_t ptimer_adp, timer_match_event_t match_ev);
void hal_timer_start_one_shot_rtl8195blp (phal_timer_adapter_t ptimer_adp, u32 time_us,
                                          timer_callback_t callback, void *phid);
void hal_timer_start_periodical_rtl8195blp (phal_timer_adapter_t ptimer_adp, u32 time_us,
                                          timer_callback_t callback, void *phid);
timer_id_t hal_timer_allocate_rtl8195blp (u8 *timer_list);

timer_id_t hal_timer_event_init_rtl8195blp (phal_timer_adapter_t ptimer_adp, u32 *ptick_us, timer_id_t *timer_list);

void hal_timer_event_deinit_rtl8195blp (timer_id_t tid);

/** @} */ /* End of group ls_hal_timer_rom_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group ls_hal_timer */

#endif  // end of "#define _RTL8195BLP_TIMER_H_"

