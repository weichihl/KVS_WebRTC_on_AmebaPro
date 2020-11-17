/**************************************************************************//**
 * @file     app_start.c
 * @brief    The application entry function implementation. It initial the 
 *           application functions.
 * @version  V1.00
 * @date     2016-05-27
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

extern void shell_cmd_init (void);
extern void shell_task (void);

//void app_start (void) __attribute__ ((noreturn));

#if !defined ( __CC_ARM ) && !(defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)) /* ARM Compiler 4/5 */
// for __CC_ARM compiler, it will add a __ARM_use_no_argv symbol for every main() function, that cause linker report error 
/// default main
__weak int main (void)
{
    while (1) {
        shell_task ();
    }
    return 0;
}
#endif

#if defined ( __ICCARM__ )
extern void *__iar_cstart_call_ctors(void *ptr);
extern void __iar_data_init3(void);

#endif

#if defined(__GNUC__)
__weak void _init(void)
{
	
}
#endif

__weak void wowlan_prepare_warm_boot(void)
{
	// necessary, do not remove it, implement in SDK
}

void app_start (void)
{    
    dbg_printf ("Build @ %s, %s\r\n", __TIME__, __DATE__);
	
#if defined (__ICCARM__)
	// __iar_data_init3 replaced by __iar_cstart_call_ctors, just do c++ constructor
	__iar_cstart_call_ctors(NULL);
#elif defined(__GNUC__)
	__libc_init_array();

#endif

    // it only has effect when wlan is alive and resume from system suspend
    wowlan_prepare_warm_boot();
	
    shell_cmd_init ();
    main();
#if defined ( __ICCARM__ )
	// for compile issue, If user never call this function, Liking fail 
	__iar_data_init3();
#endif
}


