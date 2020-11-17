/**************************************************************************//**
 * @file     RTX_os_callback.c
 * @brief    This file implements the callback function for RTX RTOS.
 * 
 * @version  V1.00
 * @date     2016-06-29
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

#undef ROM_REGION

#include "cmsis.h"
#include "cmsis_os.h"

/* OS Error Codes */
#define OS_ERROR_STACK_OVF      1
#define OS_ERROR_FIFO_OVF       2
#define OS_ERROR_MBX_OVF        3
#define OS_ERROR_TIMER_OVF      4


/// \brief The idle demon is running when no other thread is ready to run
void os_idle_callback (void) {
    for (;;) {
      /* HERE: include optional user code to be executed when no thread runs.*/
    }
}

/// \brief Called when a runtime error is detected
/// \param[in]   error_code   actual error code that has been detected
void os_error_callback (uint32_t error_code) {
    dbg_printf ("OS Error(%d)\r\n", error_code);

  /* HERE: include optional code to be executed on runtime error. */
  switch (error_code) {
    case OS_ERROR_STACK_OVF:
        dbg_printf ("OS Error: Stack Overflow\r\n");
      /* Stack overflow detected for the currently running task. */
      /* Thread can be identified by calling svcThreadGetId().   */
      break;
    case OS_ERROR_FIFO_OVF:
      /* ISR FIFO Queue buffer overflow detected. */
      break;
    case OS_ERROR_MBX_OVF:
      /* Mailbox overflow detected. */
      break;
    case OS_ERROR_TIMER_OVF:
      /* User Timer Callback Queue overflow detected. */
      break;
    default:
      break;
  }
  for (;;);
}

