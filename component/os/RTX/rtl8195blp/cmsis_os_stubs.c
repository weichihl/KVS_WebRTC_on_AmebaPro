/**************************************************************************//**
 * @file     cmsis_os_stubs.c
 * @brief    This file implements the entry functions of the RTX CMSIS OS API in ROM.
 * 
 * @version  V1.00
 * @date     2016-07-05
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 ******************************************************************************/

#include "platform_conf.h"

#if CONFIG_CMSIS_RTX_EN

#undef ROM_REGION
#include "cmsis_os.h"
#include "cmsis_os_stubs.h"

void rtx_cmsis_os_rom_init (void *prtx_bss, void *prtx_cfg, void *pcmsis_os_cfg)
{
    cmsis_os_rtx_stubs.rtx_cmsis_os_rom_init(prtx_bss, prtx_cfg, pcmsis_os_cfg);
}

void rtx_os_callback_init (void *idle_cb, void *err_cb)
{
    cmsis_os_rtx_stubs.rtx_os_callback_init (idle_cb, err_cb);
}

void osThreadExit (void)
{
    cmsis_os_rtx_stubs.osThreadExit();
}

osStatus osKernelStart (void)
{
    return  cmsis_os_rtx_stubs.osKernelStart();
}

int32_t osKernelRunning (void)
{
    return cmsis_os_rtx_stubs.osKernelRunning();
}

uint32_t osKernelSysTick (void)
{
    return cmsis_os_rtx_stubs.osKernelSysTick ();
}

osThreadId osThreadCreate (const osThreadDef_t *thread_def, void *argument)
{
    return cmsis_os_rtx_stubs.osThreadCreate (thread_def, argument);
}

osThreadId osThreadGetId (void)
{
    return cmsis_os_rtx_stubs.osThreadGetId ();
}

osStatus osThreadTerminate (osThreadId thread_id)
{
    return cmsis_os_rtx_stubs.osThreadTerminate (thread_id);
}

osStatus osThreadYield (void)
{
    return cmsis_os_rtx_stubs.osThreadYield ();
}

osStatus osThreadSetPriority (osThreadId thread_id, osPriority priority)
{
    return cmsis_os_rtx_stubs.osThreadSetPriority (thread_id, priority);
}

osPriority osThreadGetPriority (osThreadId thread_id)
{
    return cmsis_os_rtx_stubs.osThreadGetPriority (thread_id);
}

osStatus osDelay (uint32_t millisec)
{
    return cmsis_os_rtx_stubs.osDelay (millisec);
}

osTimerId osTimerCreate (const osTimerDef_t *timer_def, os_timer_type type, void *argument)
{
    return cmsis_os_rtx_stubs.osTimerCreate (timer_def, type, argument);
}

osStatus osTimerStart (osTimerId timer_id, uint32_t millisec)
{
    return cmsis_os_rtx_stubs.osTimerStart (timer_id, millisec);
}

osStatus osTimerStop (osTimerId timer_id)
{
    return cmsis_os_rtx_stubs.osTimerStop (timer_id);
}

osStatus osTimerDelete (osTimerId timer_id)
{
    return cmsis_os_rtx_stubs.osTimerDelete (timer_id);
}

void osTimerThread (void const *argument)
{
    cmsis_os_rtx_stubs.osTimerThread (argument);
}

int32_t osSignalSet (osThreadId thread_id, int32_t signals)
{
    return cmsis_os_rtx_stubs.osSignalSet (thread_id, signals);
}

int32_t osSignalClear (osThreadId thread_id, int32_t signals)
{
    return cmsis_os_rtx_stubs.osSignalClear (thread_id, signals);
}

osEvent osSignalWait (int32_t signals, uint32_t millisec)
{
    return cmsis_os_rtx_stubs.osSignalWait (signals, millisec);
}

osMutexId osMutexCreate (const osMutexDef_t *mutex_def)
{
    return cmsis_os_rtx_stubs.osMutexCreate (mutex_def);
}

osStatus osMutexWait (osMutexId mutex_id, uint32_t millisec)
{
    return cmsis_os_rtx_stubs.osMutexWait (mutex_id, millisec);
}

osStatus osMutexRelease (osMutexId mutex_id)
{
    return cmsis_os_rtx_stubs.osMutexRelease (mutex_id);
}

osStatus osMutexDelete (osMutexId mutex_id)
{
    return cmsis_os_rtx_stubs.osMutexDelete (mutex_id);
}

osSemaphoreId osSemaphoreCreate (const osSemaphoreDef_t *semaphore_def, int32_t count)
{
    return cmsis_os_rtx_stubs.osSemaphoreCreate (semaphore_def, count);
}

int32_t osSemaphoreWait (osSemaphoreId semaphore_id, uint32_t millisec)
{
    return cmsis_os_rtx_stubs.osSemaphoreWait (semaphore_id, millisec);
}

osStatus osSemaphoreRelease (osSemaphoreId semaphore_id)
{
    return cmsis_os_rtx_stubs.osSemaphoreRelease (semaphore_id);
}

osStatus osSemaphoreDelete (osSemaphoreId semaphore_id)
{
    return cmsis_os_rtx_stubs.osSemaphoreDelete (semaphore_id);
}

osPoolId osPoolCreate (const osPoolDef_t *pool_def)
{
    return cmsis_os_rtx_stubs.osPoolCreate (pool_def);
}

void *osPoolAlloc (osPoolId pool_id)
{
    return cmsis_os_rtx_stubs.osPoolAlloc (pool_id);
}

void *osPoolCAlloc (osPoolId pool_id)
{
    return cmsis_os_rtx_stubs.osPoolCAlloc (pool_id);
}

osStatus osPoolFree (osPoolId pool_id, void *block)
{
    return cmsis_os_rtx_stubs.osPoolFree (pool_id, block);
}

osStatus osKernelInitialize (void)
{
    return cmsis_os_rtx_stubs.osKernelInitialize ();
}

osMessageQId osMessageCreate (const osMessageQDef_t *queue_def, osThreadId thread_id)
{
    return cmsis_os_rtx_stubs.osMessageCreate (queue_def, thread_id);
}

osStatus osMessagePut (osMessageQId queue_id, uint32_t info, uint32_t millisec)
{
    return cmsis_os_rtx_stubs.osMessagePut (queue_id, info, millisec);
}

osEvent osMessageGet (osMessageQId queue_id, uint32_t millisec)
{
    return cmsis_os_rtx_stubs.osMessageGet (queue_id, millisec);
}

osMailQId osMailCreate (const osMailQDef_t *queue_def, osThreadId thread_id)
{
    return cmsis_os_rtx_stubs.osMailCreate (queue_def, thread_id);
}

void *osMailAlloc (osMailQId queue_id, uint32_t millisec)
{
    return cmsis_os_rtx_stubs.osMailAlloc (queue_id, millisec);
}

void *osMailCAlloc (osMailQId queue_id, uint32_t millisec)
{
    return cmsis_os_rtx_stubs.osMailCAlloc (queue_id, millisec);
}

osStatus osMailFree (osMailQId queue_id, void *mail)
{
    return cmsis_os_rtx_stubs.osMailFree (queue_id, mail);
}

osStatus osMailPut (osMailQId queue_id, void *mail)
{
    return cmsis_os_rtx_stubs.osMailPut (queue_id, mail);
}

osEvent osMailGet (osMailQId queue_id, uint32_t millisec)
{
    return cmsis_os_rtx_stubs.osMailGet (queue_id, millisec);
}

uint32_t os_suspend (void)
{
    return cmsis_os_rtx_stubs.os_suspend ();
}

void os_resume (uint32_t sleep_time)
{
    cmsis_os_rtx_stubs.os_resume (sleep_time);
}

OS_TID rt_tsk_self (void)
{
    return cmsis_os_rtx_stubs.rt_tsk_self ();
}

void rt_mut_init (OS_ID mutex)
{
    cmsis_os_rtx_stubs.rt_mut_init (mutex);
}

OS_RESULT rt_mut_wait (OS_ID mutex, U16 timeout)
{
    return cmsis_os_rtx_stubs.rt_mut_wait (mutex, timeout);
}

OS_RESULT rt_mut_release (OS_ID mutex)
{
    return cmsis_os_rtx_stubs.rt_mut_release (mutex);
}

void rt_tsk_lock (void)
{
    cmsis_os_rtx_stubs.rt_tsk_lock();
}

void rt_tsk_unlock (void)
{
    cmsis_os_rtx_stubs.rt_tsk_unlock();
}

#if 0
void SVC_Handler (void)
{
    cmsis_os_rtx_stubs.SVC_Handler ();
}

void PendSV_Handler (void)
{
    cmsis_os_rtx_stubs.PendSV_Handler ();
}

void SysTick_Handler (void)
{
    cmsis_os_rtx_stubs.SysTick_Handler ();
}

void OS_Tick_Handler (void)
{
    cmsis_os_rtx_stubs.OS_Tick_Handler ();
}
#endif
#endif  /* end of "#if CONFIG_CMSIS_RTX_EN" */

