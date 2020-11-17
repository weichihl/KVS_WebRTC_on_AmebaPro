/**************************************************************************//**
 * @file     rtx_rom_entry.h
 * @brief    This file defines the macros and data structure of the stub 
 *           functions for RTX API in ROM.
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

#ifndef _RTX_ROM_ENTRY_H_
#define _RTX_ROM_ENTRY_H_

#include "cmsis_os.h"
#include "RTX_Config.h"

/**
  \brief  The data structure of the stubs function for the RTX CMSIS OS API in ROM
*/
typedef struct cmsis_rtx_func_stubs_s {
    void (*rtx_cmsis_os_rom_init) (void *prtx_bss, void *prtx_cfg, void *pcmsis_os_cfg);
    void (*rtx_os_callback_init) (void *idle_cb, void *err_cb);
    void (*osThreadExit) (void);
    osStatus (*osKernelStart) (void);
    int32_t (*osKernelRunning)(void);
    uint32_t (*osKernelSysTick) (void);
    osThreadId (*osThreadCreate) (const osThreadDef_t *thread_def, void *argument);
    osThreadId (*osThreadGetId) (void);
    osStatus (*osThreadTerminate) (osThreadId thread_id);
    osStatus (*osThreadYield) (void);
    osStatus (*osThreadSetPriority) (osThreadId thread_id, osPriority priority);
    osPriority (*osThreadGetPriority) (osThreadId thread_id);
    osStatus (*osDelay) (uint32_t millisec);
    osTimerId (*osTimerCreate) (const osTimerDef_t *timer_def, os_timer_type type, void *argument);
    osStatus (*osTimerStart) (osTimerId timer_id, uint32_t millisec);
    osStatus (*osTimerStop) (osTimerId timer_id);
    osStatus (*osTimerDelete) (osTimerId timer_id);
    void (*osTimerThread) (void const *argument);
    int32_t (*osSignalSet) (osThreadId thread_id, int32_t signals);
    int32_t (*osSignalClear) (osThreadId thread_id, int32_t signals);
    osEvent (*osSignalWait) (int32_t signals, uint32_t millisec)os_InRegs;
    osMutexId (*osMutexCreate) (const osMutexDef_t *mutex_def);
    osStatus (*osMutexWait) (osMutexId mutex_id, uint32_t millisec);
    osStatus (*osMutexRelease) (osMutexId mutex_id);
    osStatus (*osMutexDelete) (osMutexId mutex_id);
    osSemaphoreId (*osSemaphoreCreate) (const osSemaphoreDef_t *semaphore_def, int32_t count);
    int32_t (*osSemaphoreWait) (osSemaphoreId semaphore_id, uint32_t millisec);
    osStatus (*osSemaphoreRelease) (osSemaphoreId semaphore_id);
    osStatus (*osSemaphoreDelete) (osSemaphoreId semaphore_id);
    osPoolId (*osPoolCreate) (const osPoolDef_t *pool_def);
    void *(*osPoolAlloc) (osPoolId pool_id);
    void *(*osPoolCAlloc) (osPoolId pool_id);
    osStatus (*osPoolFree) (osPoolId pool_id, void *block);
    osStatus (*osKernelInitialize) (void);
    osMessageQId (*osMessageCreate) (const osMessageQDef_t *queue_def, osThreadId thread_id);
    osStatus (*osMessagePut) (osMessageQId queue_id, uint32_t info, uint32_t millisec);
    osEvent (*osMessageGet) (osMessageQId queue_id, uint32_t millisec)os_InRegs;
    osMailQId (*osMailCreate) (const osMailQDef_t *queue_def, osThreadId thread_id);
    void *(*osMailAlloc) (osMailQId queue_id, uint32_t millisec);
    void *(*osMailCAlloc) (osMailQId queue_id, uint32_t millisec);
    osStatus (*osMailFree) (osMailQId queue_id, void *mail);
    osStatus (*osMailPut) (osMailQId queue_id, void *mail);
    osEvent (*osMailGet) (osMailQId queue_id, uint32_t millisec)os_InRegs;
    uint32_t (*os_suspend) (void);
    void (*os_resume) (uint32_t sleep_time);

    uint8_t *os_running;
    OS_TID (*rt_tsk_self) (void);
    void (*rt_mut_init) (OS_ID mutex);
    OS_RESULT (*rt_mut_wait) (OS_ID mutex, U16 timeout);
    OS_RESULT (*rt_mut_release) (OS_ID mutex);

    void (*SVC_Handler) (void);
    void (*PendSV_Handler) (void);
    void (*SysTick_Handler) (void);
    void (*OS_Tick_Handler) (void);

    // B-Cut
    uint32_t *os_time;
    void (*rt_tsk_lock) (void);
    void (*rt_tsk_unlock) (void);
    void (*rt_set_mem_func)(void *malloc, void *mfree);
    uint32_t reserved[12];  // reserved space for next ROM code version function table extending.
} cmsis_rtx_func_stubs_t;

#endif  // end of "#ifndef _RTX_ROM_ENTRY_H_"

