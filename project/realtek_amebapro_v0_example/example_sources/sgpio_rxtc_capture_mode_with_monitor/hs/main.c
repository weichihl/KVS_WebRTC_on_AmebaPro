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

#define SGPIO_TX_OUTPUT_CNT 3 

static sgpio_t sgpio_obj; 

volatile u32 timeout = 0;
volatile u32 timeout_cnt = 0;
volatile u32 capture_monitor = 0;

void sgpio_multc_rst_timeout_handler(void *data)
{
    timeout_cnt++;
    timeout = 1;
}

void sgpio_rxtc_capture_monitor_handler(void *data)
{
    capture_monitor = 1;
}

void main(void)
{    
    // Init SGPIO 
    sgpio_init (&sgpio_obj, SGPIO_TX_PIN, SGPIO_RX_PIN); 

    // Init RXTC to become the capture mode
    sgpio_rxtc_capture_mode (&sgpio_obj, ENABLE, RXTC_RISE_EDGE, RXTC_FALL_EDGE, RXTC_RESET_STOP, 30000, NULL, NULL); 

    // Set capture monitor
    sgpio_rxtc_capture_monitor (&sgpio_obj, ENABLE, UNIT_US, 500, 3, sgpio_rxtc_capture_monitor_handler, &sgpio_obj);

    // Init SGPIO TX is low 
    sgpio_set_output_value (&sgpio_obj, OUTPUT_LOW);

    // Init MULTC to become the timer mode
    sgpio_multc_timer_mode (&sgpio_obj, ENABLE, UNIT_US, 1000, sgpio_multc_rst_timeout_handler, NULL);

    // Set MULTC match time to make the external output
    sgpio_multc_timer_counter_match_output (&sgpio_obj, UNIT_US, MATCH_OUTPUT_HIGH, 0, MATCH_OUTPUT_LOW, 1000, MATCH_OUTPUT_NONE, 0);

    // Start MULTC                
    sgpio_multc_start_en (&sgpio_obj, ENABLE);

    while (1) {

        if (timeout) {
            timeout = 0;
            if (timeout_cnt < SGPIO_TX_OUTPUT_CNT) {
                // Start MULTC                
                sgpio_multc_start_en (&sgpio_obj, ENABLE);
                hal_delay_ms(10);
            }
        }

        if (capture_monitor) {
            capture_monitor = 0;
            dbg_printf("Occur the capture monitor event \r\n");;
        }    
    }

    while (1);

}

