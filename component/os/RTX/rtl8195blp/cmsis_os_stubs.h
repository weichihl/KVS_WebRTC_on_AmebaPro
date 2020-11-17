/**************************************************************************//**
 * @file     cmsis_os_stubs.h
 * @brief    Define macros to reference the RTX CMSIS OS API in ROM.
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

#ifndef _CMSIS_OS_STUBS_H_
#define _CMSIS_OS_STUBS_H_

#ifdef  __cplusplus
extern "C"
{
#endif

#include "rt_TypeDef.h"
#include "rtx_rom_entry.h"

extern const cmsis_rtx_func_stubs_t cmsis_os_rtx_stubs;

#if !defined(ROM_REGION)
// Re-direct to the handler in ROM
#define os_running            (*((uint8_t*)(cmsis_os_rtx_stubs.os_running)))
#define os_time               (*((uint32_t*)(cmsis_os_rtx_stubs.os_time)))
#define SVC_Handler           (cmsis_os_rtx_stubs.SVC_Handler)
#define PendSV_Handler        (cmsis_os_rtx_stubs.PendSV_Handler)
#define SysTick_Handler       (cmsis_os_rtx_stubs.SysTick_Handler)
#define OS_Tick_Handler       (cmsis_os_rtx_stubs.OS_Tick_Handler)
#endif

void rtx_cmsis_os_rom_init (void *prtx_bss, void *prtx_cfg, void *pcmsis_os_cfg);
void rtx_os_callback_init (void *idle_cb, void *err_cb);

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _CMSIS_OS_STUBS_H_"

