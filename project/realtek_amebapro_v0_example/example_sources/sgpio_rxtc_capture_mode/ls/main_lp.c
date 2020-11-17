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

volatile u32 capture_end = 0;
volatile u32 capture_time = 0;

sgpio_t sgpio_obj; 

void sgpio_rxtc_capture_handler(void *data)
{
    sgpio_t *obj = (sgpio_t *)data;
    
    capture_time = sgpio_get_rxtc_capture_time(obj, UNIT_NS);
    capture_end = 1;
}

void main(void)
{          
    // Init SGPIO 
    sgpio_init (&sgpio_obj, SGPIO_TX_PIN, SGPIO_RX_PIN); 

    // Init RXTC to become the capture mode
    sgpio_rxtc_capture_mode (&sgpio_obj, ENABLE, RXTC_RISE_EDGE, RXTC_FALL_EDGE, RXTC_RESET_STOP, 30000, sgpio_rxtc_capture_handler, &sgpio_obj); 

    // Init SGPIO TX is low 
    sgpio_set_output_value (&sgpio_obj, OUTPUT_LOW);

    // Init MULTC to become the timer mode
    sgpio_multc_timer_mode (&sgpio_obj, ENABLE, UNIT_US, 1000, NULL, NULL);

    // Set MULTC match time to make the external output
    sgpio_multc_timer_counter_match_output (&sgpio_obj, UNIT_US, MATCH_OUTPUT_HIGH, 400, MATCH_OUTPUT_LOW, 1000, MATCH_OUTPUT_NONE, 0);

    // Start MULTC
    sgpio_multc_start_en (&sgpio_obj, ENABLE);

    while (1) {
        if (capture_end == 1) {
            dbg_printf("Capture time: %d ns \r\n", capture_time);
            break;
        }
    }

    while (1);

}

