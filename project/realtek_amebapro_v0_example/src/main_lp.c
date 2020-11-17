/**************************************************************************//**
 * @file     main.c
 * @brief    main function example.
 * @version  V1.00
 * @date     2016-06-08
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

#include "cmsis.h"

extern void shell_cmd_init (void);
extern s32 shell_task(void);
extern int main(void);

void malloc_test(void)
{
    void* res = (void*)malloc(1024);
    dbg_printf("res0 %x\n\r", res);
    free(res);
    
    res = (void*)malloc(512);
    dbg_printf("res1 %x\n\r", res);
    free(res);
    
    res = (void*)malloc(123);
    dbg_printf("res1 %x\n\r", res);
    free(res);
    
    res = (void*)malloc(333);
    dbg_printf("res1 %x\n\r", res);
    free(res);
}

int main (void)
{   
    malloc_test();
    dbg_printf ("Build @ %s, %s\r\n", __TIME__, __DATE__);
    shell_cmd_init ();
    while (1) {
        shell_task ();
    }
    return 0;
}