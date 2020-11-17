/**************************************************************************//**
 * @file     rtx_rom_entry.c
 * @brief    This file defines the RTX CMSIS OS API entry functions table.
 * 
 * @version  V1.00
 * @date     2016-09-28
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
#include "rt_TypeDef.h"
#include "basic_types.h"
#include "cmsis_os.h"
#include "RTX_Config.h"
#include "rtx_rom_entry.h"

#define SECTION_CMSIS_RTX_STUBS          SECTION(".rom.cmsisrtx.stubs")

extern void _rtx_cmsis_os_rom_init (void *prtx_bss, void *prtx_cfg, void *pcmsis_os_cfg);
extern void _rtx_os_callback_init (void *idle_cb, void *err_cb);

extern  void osThreadExit (void);
extern void osTimerThread (void const *argument);

extern uint8_t os_running;

extern OS_TID rt_tsk_self (void);
extern void rt_mut_init (OS_ID mutex);
extern OS_RESULT rt_mut_wait (OS_ID mutex, U16 timeout);
extern OS_RESULT rt_mut_release (OS_ID mutex);

extern void SVC_Handler (void);
extern void PendSV_Handler (void);
extern void SysTick_Handler (void);
extern void OS_Tick_Handler (void);
extern U32 os_time;
extern void rt_tsk_lock   (void);
extern void rt_tsk_unlock (void);
extern void rtw_set_mem_func (void *malloc, void *mfree);

SECTION_CMSIS_RTX_STUBS const cmsis_rtx_func_stubs_t cmsis_os_rtx_stubs = {
    .rtx_cmsis_os_rom_init = _rtx_cmsis_os_rom_init,
    .rtx_os_callback_init = _rtx_os_callback_init,
    .osThreadExit = osThreadExit,
    .osKernelStart = osKernelStart,
    .osKernelRunning = osKernelRunning,
    .osKernelSysTick = osKernelSysTick,
    .osThreadCreate = osThreadCreate,
    .osThreadGetId = osThreadGetId,
    .osThreadTerminate = osThreadTerminate,
    .osThreadYield = osThreadYield,
    .osThreadSetPriority = osThreadSetPriority,
    .osThreadGetPriority = osThreadGetPriority,
    .osDelay = osDelay,
    .osTimerCreate = osTimerCreate,
    .osTimerStart = osTimerStart,
    .osTimerStop = osTimerStop,
    .osTimerDelete = osTimerDelete,
    .osTimerThread  = osTimerThread,
    .osSignalSet = osSignalSet,
    .osSignalClear = osSignalClear,
    .osSignalWait = osSignalWait,
    .osMutexCreate = osMutexCreate,
    .osMutexWait = osMutexWait,
    .osMutexRelease = osMutexRelease,
    .osMutexDelete = osMutexDelete,
    .osSemaphoreCreate = osSemaphoreCreate,
    .osSemaphoreWait = osSemaphoreWait,
    .osSemaphoreRelease = osSemaphoreRelease,
    .osSemaphoreDelete = osSemaphoreDelete,
    .osPoolCreate = osPoolCreate,
    .osPoolAlloc = osPoolAlloc,
    .osPoolCAlloc = osPoolCAlloc,
    .osPoolFree = osPoolFree,
    .osKernelInitialize = osKernelInitialize,
    .osMessageCreate = osMessageCreate,
    .osMessagePut = osMessagePut,
    .osMessageGet = osMessageGet,
    .osMailCreate = osMailCreate,
    .osMailAlloc = osMailAlloc,
    .osMailCAlloc = osMailCAlloc,
    .osMailFree = osMailFree,
    .osMailPut = osMailPut,
    .osMailGet = osMailGet,
    .os_suspend = os_suspend,
    .os_resume = os_resume,

    .os_running = &os_running,
    .rt_tsk_self = rt_tsk_self,
    .rt_mut_init = rt_mut_init,
    .rt_mut_wait = rt_mut_wait,
    .rt_mut_release = rt_mut_release,

    .SVC_Handler = SVC_Handler,
    .PendSV_Handler = PendSV_Handler,
    .SysTick_Handler = SysTick_Handler,
    .OS_Tick_Handler = OS_Tick_Handler,
    
// new for B-Cut    
    .os_time = &os_time,
    .rt_tsk_lock = rt_tsk_lock,
    .rt_tsk_unlock = rt_tsk_unlock,
    .rt_set_mem_func = rtw_set_mem_func
};

