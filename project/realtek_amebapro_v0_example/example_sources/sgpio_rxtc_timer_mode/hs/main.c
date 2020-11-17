/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "sgpio_api.h"

#define SGPIO_TX_PIN    PG_8 //PA_8
#define SGPIO_RX_PIN    PG_9 //PA_7

static sgpio_t sgpio_obj; 

volatile u32 timeout;

void sgpio_rxtc_timeout1_handler(void *data)
{
    timeout = 1;
}

void sgpio_rxtc_timeout2_handler(void *data)
{
    timeout = 2;
}

void sgpio_rxtc_rst_timeout3_handler(void *data)
{
    timeout = 3;
}

void main(void)
{    
    // Init SGPIO 
    sgpio_init (&sgpio_obj, SGPIO_TX_PIN, SGPIO_RX_PIN); 

    // Release SGPIO pins to other peripherals.
    sgpio_pin_free (&sgpio_obj);

    // Set Timeout: t1, t2, t3 reset, repeat
    sgpio_rxtc_timer_mode (&sgpio_obj, DISABLE, UNIT_NS, 
        1000000000, sgpio_rxtc_timeout1_handler, NULL,
        2000000000, sgpio_rxtc_timeout2_handler, NULL,
        3000000000, sgpio_rxtc_rst_timeout3_handler, NULL);
    
    // Start rxtc timer
    sgpio_rxtc_start_en (&sgpio_obj, ENABLE);

    while (1) {
        if (timeout != 0x00) {

            if (timeout == 1) {
                dbg_printf(" 1S \r\n");
            } else if (timeout == 2) {
                dbg_printf(" 2S \r\n");
            } else if (timeout == 3) {
                dbg_printf(" 3S \r\n");
            } 
            timeout = 0;
        }
    }
   
}

