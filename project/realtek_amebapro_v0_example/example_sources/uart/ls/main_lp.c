/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */

#include "device.h"
#include "serial_api.h"
#include "hal_sys_ctrl.h"
//#include "main.h"

#define UART_TX    PA_8
#define UART_RX    PA_7


void uart_send_str(serial_t *sobj, char *pstr)
{
    unsigned int i=0;

    while (*(pstr+i) != 0) {
        serial_putc(sobj, *(pstr+i));
        
        i++;
    }
}


void main(void)
{
    hal_dbg_port_disable(); // since UART0 pin conflict with SWD
    // sample text
    char rc;
    serial_t    sobj;

    // mbed uart test

    serial_init(&sobj,UART_TX,UART_RX);
    serial_baud(&sobj,38400);
    serial_format(&sobj, 8, ParityNone, 1);
    uart_send_str(&sobj, "UART API Demo...\r\n");
    uart_send_str(&sobj, "Hello World!!\r\n");

    while(1){
        uart_send_str(&sobj, "\r\n8195a$");
        rc = serial_getc(&sobj);
        serial_putc(&sobj, rc);
    }
}

