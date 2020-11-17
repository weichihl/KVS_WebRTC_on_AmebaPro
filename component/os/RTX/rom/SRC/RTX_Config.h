/*----------------------------------------------------------------------------
 *      CMSIS-RTOS  -  RTX
 *----------------------------------------------------------------------------
 *      Name:    RTX_CONFIG.H
 *      Purpose: Exported functions of RTX_Config.c
 *      Rev.:    V4.81
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

#include <stdint.h>
#include "platform_conf.h"

#ifndef _RTX_CONFIG_H_
#define _RTX_CONFIG_H_
 
#ifdef  __cplusplus
extern "C"
{
#endif

#include "rt_TypeDef.h"
#include "cmsis_os.h"

/* Error Codes */
#define OS_ERR_STK_OVF          1U
#define OS_ERR_FIFO_OVF         2U
#define OS_ERR_MBX_OVF          3U
#define OS_ERR_TIMER_OVF        4U

/* Definitions */
#define BOX_ALIGN_8                   0x80000000U
#ifndef _declare_box
#define _declare_box(pool,size,cnt)   U32 pool[(((size)+3)/4)*(cnt) + 3]
#endif
#ifndef _declare_box8
#define _declare_box8(pool,size,cnt)  U64 pool[(((size)+7)/8)*(cnt) + 2]
#endif
#define _init_box8(pool,size,bsize)   _init_box (pool,size,(bsize) | BOX_ALIGN_8)

typedef void (*os_idle_cb) (void);
typedef void (*os_err_cb) (uint32_t error_code);

#if 0
/* Variables */
extern U32 mp_tcb[];
extern U64 mp_stk[];
extern U32 os_fifo[];
extern void *os_active_TCB[];

/* Constants */

extern U16 const os_maxtaskrun;
extern U32 const os_trv;
extern U8  const os_flags;
extern U32 const os_stackinfo;
extern U32 const os_rrobin;
extern U32 const os_clockrate;
extern U32 const os_timernum;
extern U16 const mp_tcb_size;
extern U32 const mp_stk_size;
extern U32 const *m_tmr;
extern U16 const mp_tmr_size;
extern U8  const os_fifo_size;
#else
/* Constants */
typedef struct rtx_cfg_const_data_s {
    uint8_t  os_flags;      // os_flags must be the 1st member, sinc HAL_CM0.S will reference
    uint8_t  os_fifo_size;    
    uint16_t os_maxtaskrun;
    uint16_t mp_tcb_size;
    uint16_t mp_tmr_size;
    uint32_t os_trv;
    uint32_t os_stackinfo;
    uint32_t os_rrobin;
    uint32_t os_clockrate;
    uint32_t os_timernum;
    uint32_t mp_stk_size;
    uint32_t *m_tmr;
} rtx_cfg_const_data_t;

//extern const rtx_cfg_const_data_t rtx_cfg_data;
extern rtx_cfg_const_data_t *prtx_cfg_data;

#if CONFIG_RTX_IN_ROM && defined(ROM_REGION)
#define os_maxtaskrun       (prtx_cfg_data->os_maxtaskrun)
#define os_trv              (prtx_cfg_data->os_trv)
#define os_stackinfo		(prtx_cfg_data->os_stackinfo)
#define os_rrobin			(prtx_cfg_data->os_rrobin)
#define os_clockrate		(prtx_cfg_data->os_clockrate)
#define os_timernum			(prtx_cfg_data->os_timernum)
#define mp_tcb_size			(prtx_cfg_data->mp_tcb_size)
#define mp_stk_size			(prtx_cfg_data->mp_stk_size)
#define m_tmr				(prtx_cfg_data->m_tmr)
#define mp_tmr_size			(prtx_cfg_data->mp_tmr_size)
#define os_fifo_size		(prtx_cfg_data->os_fifo_size)
extern uint8_t  os_flags;
#endif

/* Variables */
typedef struct rtx_bss_allocation_s {
    uint64_t *mp_stk;
    void **os_active_TCB;
    uint64_t *os_stack_mem;
    uint32_t *os_fifo;
    uint32_t *mp_tcb;
} rtx_bss_allocation_t;

#if CONFIG_RTX_IN_ROM && defined(ROM_REGION)
// RTX ROM function rename
#define rt_tsk_self                        _rt_tsk_self
#define rt_mut_init                        _rt_mut_init
#define rt_mut_wait                        _rt_mut_wait
#define rt_mut_release                     _rt_mut_release

#define SVC_Handler                        _SVC_Handler
#define PendSV_Handler                     _PendSV_Handler
#define SysTick_Handler                    _SysTick_Handler
#define OS_Tick_Handler                    _OS_Tick_Handler

extern rtx_bss_allocation_t *prtx_bss_allocation;

#define os_stack_mem        ((uint64_t *)(prtx_bss_allocation->os_stack_mem))
#define os_active_TCB       ((void **)(prtx_bss_allocation->os_active_TCB))
#define os_psq              ((P_PSQ)(&prtx_bss_allocation->os_fifo[0]))
#define mp_stk              ((uint64_t *)(prtx_bss_allocation->mp_stk))
#define mp_tcb              ((uint32_t *)(prtx_bss_allocation->mp_tcb))
#endif

#endif

/* Functions */
extern void os_idle_demon   (void);
extern S32  os_tick_init    (void);
extern U32  os_tick_val     (void);
extern U32  os_tick_ovf     (void);
extern void os_tick_irqack  (void);
extern void os_tmr_call     (U16 info);
extern void os_error        (uint32_t err_code);

typedef struct rtx_cmsis_os_cfg_s {
    uint32_t os_stack_sz;
    osThreadDef_t os_thread_def_osTimerThread;
    osMessageQDef_t os_messageQ_def_osTimerMessageQ;
} rtx_cmsis_os_cfg_t;

#if CONFIG_RTX_IN_ROM && defined(ROM_REGION)
extern rtx_cmsis_os_cfg_t *prtx_cmsis_os_cfg;

#define os_stack_sz                         (prtx_cmsis_os_cfg->os_stack_sz)
#define os_thread_def_osTimerThread         (prtx_cmsis_os_cfg->os_thread_def_osTimerThread)
#define os_messageQ_def_osTimerMessageQ     (prtx_cmsis_os_cfg->os_messageQ_def_osTimerMessageQ)
#endif

#ifdef  __cplusplus
 }
#endif
 
#endif  // end of "#define _RTX_CONFIG_H_"

/*----------------------------------------------------------------------------
 * end of file
 *---------------------------------------------------------------------------*/
 
