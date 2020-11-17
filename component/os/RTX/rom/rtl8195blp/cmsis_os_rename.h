/**************************************************************************//**
 * @file     cmsis_os_rename.h
 * @brief    Define macros to rename the RTX CMSIS OS API in ROM.
 * @version  V1.00
 * @date     2016-09-26
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
 *
 ******************************************************************************/

#ifndef _CMSIS_OS_RENAME_H_
#define _CMSIS_OS_RENAME_H_
 
#ifdef  __cplusplus
extern "C"
{
#endif
#define osThreadExit                        _osThreadExit
#define osKernelStart                       _osKernelStart
#define osKernelRunning                     _osKernelRunning
#define osKernelSysTick                     _osKernelSysTick
#define osThreadCreate                      _osThreadCreate
#define osThreadGetId                       _osThreadGetId
#define osThreadTerminate                   _osThreadTerminate
#define osThreadYield                       _osThreadYield
#define osThreadSetPriority                 _osThreadSetPriority
#define osThreadGetPriority                 _osThreadGetPriority
#define osDelay                             _osDelay
#define osWait                              _osWait
#define osTimerCreate                       _osTimerCreate
#define osTimerStart                        _osTimerStart
#define osTimerStop                         _osTimerStop
#define osTimerDelete                       _osTimerDelete
#define osTimerThread                       _osTimerThread
#define osSignalSet                         _osSignalSet
#define osSignalClear                       _osSignalClear
#define osSignalWait                        _osSignalWait
#define osMutexCreate                       _osMutexCreate
#define osMutexWait                         _osMutexWait
#define osMutexRelease                      _osMutexRelease
#define osMutexDelete                       _osMutexDelete
#define osSemaphoreCreate                   _osSemaphoreCreate
#define osSemaphoreWait                     _osSemaphoreWait
#define osSemaphoreRelease                  _osSemaphoreRelease
#define osSemaphoreDelete                   _osSemaphoreDelete
#define osPoolCreate                        _osPoolCreate
#define osPoolAlloc                         _osPoolAlloc
#define osPoolCAlloc                        _osPoolCAlloc
#define osPoolFree                          _osPoolFree
#define osKernelInitialize                  _osKernelInitialize
#define osMessageCreate                     _osMessageCreate
#define osMessagePut                        _osMessagePut
#define osMessageGet                        _osMessageGet
#define osMailCreate                        _osMailCreate
#define osMailAlloc                         _osMailAlloc
#define osMailCAlloc                        _osMailCAlloc
#define osMailFree                          _osMailFree
#define osMailPut                           _osMailPut
#define osMailGet                           _osMailGet
#define os_suspend                          _os_suspend
#define os_resume                           _os_resume
#define os_running                          _os_running
// new for B-Cut
#define os_time                             _os_time
#define rt_tsk_lock                         _rt_tsk_lock
#define rt_tsk_unlock                       _rt_tsk_unlock
#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _CMSIS_OS_RENAME_H_"

