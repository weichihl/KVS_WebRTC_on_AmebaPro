/*----------------------------------------------------------------------------
 *      CMSIS-RTOS  -  RTX
 *----------------------------------------------------------------------------
 *      Name:    RTX_Conf_CM.C
 *      Purpose: Configuration of CMSIS RTX Kernel for Cortex-M
 *      Rev.:    V4.70.1
 *----------------------------------------------------------------------------
 *
 * Copyright (c) 1999-2009 KEIL, 2009-2015 ARM Germany GmbH
 * All rights reserved.
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *  - Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  - Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  - Neither the name of ARM  nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *---------------------------------------------------------------------------*/

#include "cmsis_os.h"


/*----------------------------------------------------------------------------
 *      RTX User configuration part BEGIN
 *---------------------------------------------------------------------------*/

//-------- <<< Use Configuration Wizard in Context Menu >>> -----------------
//
// <h>Thread Configuration
// =======================
//
//   <o>Number of concurrent running user threads <1-250>
//   <i> Defines max. number of user threads that will run at the same time.
//   <i> Default: 6
#ifndef OS_TASKCNT
#if (CONFIG_VRF_MODE) 
 #define OS_TASKCNT     10
#else 
#define OS_TASKCNT     6
#endif
#endif

//   <o>Default Thread stack size [bytes] <64-4096:8><#/4>
//   <i> Defines default stack size for threads with osThreadDef stacksz = 0
//   <i> Default: 256
#ifndef OS_STKSIZE
 #define OS_STKSIZE     256      // this stack size value is in words
#endif

//   <o>Main Thread stack size [bytes] <64-32768:8><#/4>
//   <i> Defines stack size for main thread.
//   <i> Default: 200
#ifndef OS_MAINSTKSIZE
#if (CONFIG_VRF_MODE) 
 #define OS_MAINSTKSIZE 1536      // this stack size value is in words
#else 
 #define OS_MAINSTKSIZE 1024      // this stack size value is in words
#endif
#endif

//   <o>Number of threads with user-provided stack size <0-250>
//   <i> Defines the number of threads with user-provided stack size.
//   <i> Default: 0
#ifndef OS_PRIVCNT
 #define OS_PRIVCNT     1
#endif

//   <o>Total stack size [bytes] for threads with user-provided stack size <0-1048576:8><#/4>
//   <i> Defines the combined stack size for threads with user-provided stack size.
//   <i> Default: 0
#ifndef OS_PRIVSTKSIZE
 #define OS_PRIVSTKSIZE 1024       // this stack size value is in words
#endif

//   <q>Stack overflow checking
//   <i> Enable stack overflow checks at thread switch.
//   <i> Enabling this option increases slightly the execution time of a thread switch.
#ifndef OS_STKCHECK
 #define OS_STKCHECK    1
#endif

//   <q>Stack usage watermark
//   <i> Initialize thread stack with watermark pattern for analyzing stack usage (current/maximum) in System and Thread Viewer.
//   <i> Enabling this option increases significantly the execution time of osThreadCreate.
#ifndef OS_STKINIT
#define OS_STKINIT      0
#endif

//   <o>Processor mode for thread execution
//     <0=> Unprivileged mode
//     <1=> Privileged mode
//   <i> Default: Privileged mode
#ifndef OS_RUNPRIV
 #define OS_RUNPRIV     1
#endif

// </h>

// <h>RTX Kernel Timer Tick Configuration
// ======================================
//   <q> Use Cortex-M SysTick timer as RTX Kernel Timer
//   <i> Cortex-M processors provide in most cases a SysTick timer that can be used as
//   <i> as time-base for RTX.
#ifndef OS_SYSTICK
 #define OS_SYSTICK     1
#endif
//
//   <o>RTOS Kernel Timer input clock frequency [Hz] <1-1000000000>
//   <i> Defines the input frequency of the RTOS Kernel Timer.
//   <i> When the Cortex-M SysTick timer is used, the input clock
//   <i> is on most systems identical with the core clock.
#ifndef OS_CLOCK
 #define OS_CLOCK       4000000
#endif

//   <o>RTX Timer tick interval value [us] <1-1000000>
//   <i> The RTX Timer tick interval value is used to calculate timeout values.
//   <i> When the Cortex-M SysTick timer is enabled, the value also configures the SysTick timer.
//   <i> Default: 1000  (1ms)
#ifndef OS_TICK
 #define OS_TICK        1000
#endif

// </h>

// <h>System Configuration
// =======================
//
// <e>Round-Robin Thread switching
// ===============================
//
// <i> Enables Round-Robin Thread switching.
#ifndef OS_ROBIN
 #define OS_ROBIN       1
#endif

//   <o>Round-Robin Timeout [ticks] <1-1000>
//   <i> Defines how long a thread will execute before a thread switch.
//   <i> Default: 5
#ifndef OS_ROBINTOUT
 #define OS_ROBINTOUT   5
#endif

// </e>

// <e>User Timers
// ==============
//   <i> Enables user Timers
#ifndef OS_TIMERS
 #define OS_TIMERS      1
#endif

//   <o>Timer Thread Priority
//                        <1=> Low
//     <2=> Below Normal  <3=> Normal  <4=> Above Normal
//                        <5=> High
//                        <6=> Realtime (highest)
//   <i> Defines priority for Timer Thread
//   <i> Default: High
#ifndef OS_TIMERPRIO
 #define OS_TIMERPRIO   5
#endif

//   <o>Timer Thread stack size [bytes] <64-4096:8><#/4>
//   <i> Defines stack size for Timer thread.
//   <i> Default: 200
#ifndef OS_TIMERSTKSZ
 #define OS_TIMERSTKSZ  200     // this stack size value is in words
#endif

//   <o>Timer Callback Queue size <1-32>
//   <i> Number of concurrent active timer callback functions.
//   <i> Default: 4
#ifndef OS_TIMERCBQS
 #define OS_TIMERCBQS   8
#endif

// </e>

//   <o>ISR FIFO Queue size<4=>   4 entries  <8=>   8 entries
//                         <12=> 12 entries  <16=> 16 entries
//                         <24=> 24 entries  <32=> 32 entries
//                         <48=> 48 entries  <64=> 64 entries
//                         <96=> 96 entries
//   <i> ISR functions store requests to this buffer,
//   <i> when they are called from the interrupt handler.
//   <i> Default: 16 entries
#ifndef OS_FIFOSZ
 #define OS_FIFOSZ      16
#endif

// </h>

//------------- <<< end of configuration section >>> -----------------------

// Standard library system mutexes
// ===============================
//  Define max. number system mutexes that are used to protect
//  the arm standard runtime library. For microlib they are not used.
#ifndef OS_MUTEXCNT
 #define OS_MUTEXCNT    8
#endif

/*----------------------------------------------------------------------------
 *      RTX User configuration part END
 *---------------------------------------------------------------------------*/

#define OS_TRV          ((uint32_t)(((double)OS_CLOCK*(double)OS_TICK)/1E6)-1)


/*----------------------------------------------------------------------------
 *      Global Functions
 *---------------------------------------------------------------------------*/

/*--------------------------- os_idle_demon ---------------------------------*/

/// \brief The idle demon is running when no other thread is ready to run
extern void os_idle_callback (void);

__attribute__ ((__section__(".rtx.callback.text")))
void os_idle_demon (void) {
    os_idle_callback();
    while(1);
}

#if (OS_SYSTICK == 0)   // Functions for alternative timer as RTX kernel timer

/*--------------------------- os_tick_init ----------------------------------*/

/// \brief Initializes an alternative hardware timer as RTX kernel timer
/// \return                             IRQ number of the alternative hardware timer
int os_tick_init (void) {
  return (-1);  /* Return IRQ number of timer (0..239) */
}

/*--------------------------- os_tick_val -----------------------------------*/

/// \brief Get alternative hardware timer's current value (0 .. OS_TRV)
/// \return                             Current value of the alternative hardware timer
uint32_t os_tick_val (void) {
  return (0);
}

/*--------------------------- os_tick_ovf -----------------------------------*/

/// \brief Get alternative hardware timer's  overflow flag
/// \return                             Overflow flag\n
///                                     - 1 : overflow
///                                     - 0 : no overflow
uint32_t os_tick_ovf (void) {
  return (0);
}

/*--------------------------- os_tick_irqack --------------------------------*/

/// \brief Acknowledge alternative hardware timer interrupt
void os_tick_irqack (void) {
  /* ... */
}

#endif   // (OS_SYSTICK == 0)

/*--------------------------- os_error --------------------------------------*/

extern osThreadId svcThreadGetId (void);

#if 0   // move to ROM

/// \brief Called when a runtime error is detected
/// \param[in]   error_code   actual error code that has been detected
extern os_error_callback (uint32_t error_code);

__attribute__ ((__section__(".rtx.callback.text")))
void os_error (uint32_t error_code) {
    os_error_callback (error_code);
#endif

/*----------------------------------------------------------------------------
 *      RTX Configuration Functions
 *---------------------------------------------------------------------------*/

#include "RTX_CM_lib.h"
#include "RTX_Config.h"
/****** Patch for the RTX ROM porting *********/
const rtx_bss_allocation_t rtx_bss_allocation = {
    .mp_stk = mp_stk,
    .os_active_TCB = os_active_TCB,
    .os_stack_mem = os_stack_mem,
    .os_fifo = os_fifo,
    .mp_tcb = mp_tcb
};

#if 0//defined(CONFIG_BUILD_ALL) || defined (CONFIG_BUILD_ROM)
__attribute__ ((__section__(".rom.rtx.bss"))) osMessageQId osMessageQId_osTimerMessageQ;
__attribute__ ((__section__(".rom.rtx.bss"))) osThreadId osThreadId_osTimerThread;
#endif

__USED const rtx_cfg_const_data_t rtx_cfg_data = {
    .os_flags      = OS_RUNPRIV,
    .os_fifo_size = OS_FIFOSZ,
    .os_maxtaskrun = OS_TASK_CNT,
    .mp_tcb_size = sizeof(mp_tcb),
    .mp_tmr_size = 0U,
    .os_trv        = OS_TRV,
    .os_stackinfo  = (OS_STKINIT<<28) | (OS_STKCHECK<<24) | (OS_PRIV_CNT<<16) | (OS_STKSIZE*4),
    .os_rrobin     = (OS_ROBIN << 16) | OS_ROBINTOUT,
    .os_clockrate = OS_TICK,
    .os_timernum  = 0U,
    .mp_stk_size = sizeof(mp_stk),
    .m_tmr = NULL,
};


#if (OS_TIMERS != 0)
uint32_t os_messageQ_q_osTimerMessageQ[4+(OS_TIMERCBQS)];
#else
uint32_t os_messageQ_q_osTimerMessageQ[4];
#endif

__USED const rtx_cmsis_os_cfg_t rtx_cmsis_os_cfg = {
    .os_stack_sz = sizeof(os_stack_mem),
#if (OS_TIMERS != 0)
    .os_thread_def_osTimerThread = {(osTimerThread), ((osPriority)(OS_TIMERPRIO-3)), 1, (4*OS_TIMERSTKSZ)},
    .os_messageQ_def_osTimerMessageQ = {OS_TIMERCBQS, os_messageQ_q_osTimerMessageQ}
#else
    .os_thread_def_osTimerThread = { NULL, osPriorityNormal, 0U, 0U },
    .os_messageQ_def_osTimerMessageQ = {0, os_messageQ_q_osTimerMessageQ}
#endif
};

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
