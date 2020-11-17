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

#include "icc_api.h"

#include "hal_power_mode.h"
#include "power_mode_api.h"

#define ICC_CMD_REQ_STANDBY (0x10)

extern void shell_cmd_init (void);
extern s32 shell_task(void);
extern int main(void);

void icc_req_standby_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    dbg_printf("Stndby\r\n");
    Standby(DSTBY_WLAN, 0, 1, 0);
}

int main (void)
{
    osKernelInitialize ();

    icc_init ();

    icc_cmd_register(ICC_CMD_REQ_STANDBY, (icc_user_cmd_callback_t)icc_req_standby_handler, ICC_CMD_REQ_STANDBY);

    osKernelStart ();

    return 0;
}