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

volatile u32 timeout_done = 0;
volatile u32 counter_match = 0;

void sgpio_multc_counter_match_handler(void *data)
{
    counter_match = 1;  
}

void sgpio_multc_counter_timeout_handler(void *data)
{
    timeout_done = 1; 
}

void main(void)
{   
    u16 multc_value;   
        
    // Init SGPIO 
    sgpio_init (&sgpio_obj, SGPIO_TX_PIN, SGPIO_RX_PIN); 

    // Make SGPIO become the counter mode
    sgpio_multc_counter_mode(&sgpio_obj, ENABLE, INPUT_BOTH_EDGE, 4, sgpio_multc_counter_match_handler, &sgpio_obj, MULTC_RESET, 
                                UNIT_US, 200, sgpio_multc_counter_timeout_handler, &sgpio_obj);

    // TX Start, multc_value is 0
    sgpio_set_inverse_output (&sgpio_obj); //multc_value is 1.
    sgpio_set_inverse_output (&sgpio_obj); //multc_value is 2.
    sgpio_set_inverse_output (&sgpio_obj); //multc_value is 3.
    sgpio_set_inverse_output (&sgpio_obj); //multc_value is 4. Happen the match interrupt, and make the multc value 0.   

    while (1) {
        if (counter_match) {
            counter_match = 0;
            dbg_printf(" multc match \r\n "); 
            break;
        }
    }

    sgpio_set_inverse_output (&sgpio_obj); //multc_value is 1.    
    sgpio_set_inverse_output (&sgpio_obj); //multc_value is 2.    
    sgpio_set_inverse_output (&sgpio_obj); //multc_value is 3.        

    while (1) {
        if (timeout_done) {
            timeout_done = 0;
            multc_value = sgpio_get_multc_value(&sgpio_obj);
            dbg_printf(" The multc is reset, and this value is %d. \r\n ", multc_value);  
        }
    }

}

