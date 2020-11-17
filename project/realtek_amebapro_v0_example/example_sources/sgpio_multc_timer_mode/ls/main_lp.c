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

#define SGPIO_TX_PIN    PA_2 //PA_8
#define SGPIO_RX_PIN    PA_3 //PA_7

sgpio_t sgpio_obj; 

volatile u32 timeout = 0;
volatile u32 timeout_cnt = 0;

void sgpio_multc_rst_timeout1_handler(void *data)
{
    timeout = 1;
}

void main(void)
{    
    // Init SGPIO 
    sgpio_init (&sgpio_obj, SGPIO_TX_PIN, SGPIO_RX_PIN); 

    // Release SGPIO pins to other peripherals.
    sgpio_pin_free (&sgpio_obj);

    // Set Timeout: reset, repeat
    sgpio_multc_timer_mode (&sgpio_obj, DISABLE, UNIT_NS, 1000000000, sgpio_multc_rst_timeout1_handler, NULL);
    
    // Start multc timer
    sgpio_multc_start_en (&sgpio_obj, ENABLE);

    while (1) {
        if (timeout) {
            timeout = 0;
            timeout_cnt++;
            if (timeout_cnt <= 10) {
                dbg_printf(" timeout: 1s \r\n "); 
            } else {
                sgpio_multc_start_en (&sgpio_obj, DISABLE);
                sgpio_reset_multc (&sgpio_obj);
                while(1);
            }
        }
    }

}

