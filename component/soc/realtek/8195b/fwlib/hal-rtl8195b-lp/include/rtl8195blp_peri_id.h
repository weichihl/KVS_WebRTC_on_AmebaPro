/**************************************************************************//**
 * @file     rtl8195blp_peripheral_id.h
 * @brief    Define a identification ID for each peripheral device.
 * @version  V1.00
 * @date     2016-05-17
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
 *
 ******************************************************************************/


#ifndef _RTL8195BL_PHERI_ID_H_
#define _RTL8195BL_PHERI_ID_H_

#include "basic_types.h"

#ifdef __cplusplus
extern "C" {
#endif

enum  peripheral_id_e
{
  PID_SYSTEM       = 0x00,
    
  PID_TIMER0       = 0x01,
  PID_TIMER1       = (PID_TIMER0+1),
  PID_TIMER2       = (PID_TIMER0+2),
  PID_TIMER3       = (PID_TIMER0+3),
  PID_TIMER4       = (PID_TIMER0+4),
  PID_TIMER5       = (PID_TIMER0+5),
  PID_TIMER6       = (PID_TIMER0+6),
  PID_TIMER7       = (PID_TIMER0+7),
  
  PID_PWM0         = 0x10,
  PID_PWM1         = (PID_PWM0+1),
  PID_PWM2         = (PID_PWM0+2),
  PID_PWM3         = (PID_PWM0+3),
  PID_PWM4         = (PID_PWM0+4),
  PID_PWM5         = (PID_PWM0+5),
  PID_PWM6         = (PID_PWM0+6),
  PID_PWM7         = (PID_PWM0+7),
  
  PID_ADC0         = 0x18,
  PID_ADC1         = (PID_ADC0+1),
  PID_ADC2         = (PID_ADC0+2),
  PID_ADC3         = (PID_ADC0+3),
  PID_ADC4         = (PID_ADC0+4),
  PID_ADC5         = (PID_ADC0+5),
  PID_ADC6         = (PID_ADC0+6),
  
  PID_SGPIO0       = 0x20,
  PID_SGPIO1       = (PID_SGPIO0+1),
  PID_SGPIO2       = (PID_SGPIO0+2),
  PID_SGPIO3       = (PID_SGPIO0+3),
  
  PID_UART0        = 0x28,
  PID_UART1        = (PID_UART0+1),
  
  PID_I2C0         = 0x30,
  
  PID_GDMA0        = 0x38,
  PID_ICC          = 0x40,
  PID_WDT          = 0x41,

  PID_CIR0         = 0x42,
  PID_QDEC0        = 0x43,

  PID_GPIO         = 0x44,

  PID_SWD          = 0xE0,
  PID_ERR          = 0xFF
};

#ifdef __cplusplus
}
#endif


#endif //_RTL8195BL_PHERI_ID_H_
