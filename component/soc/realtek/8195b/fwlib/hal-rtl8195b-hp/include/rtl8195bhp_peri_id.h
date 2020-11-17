/**************************************************************************//**
 * @file     rtl8195bh_peripheral_id.h
 * @brief    Define a identification ID for each peripheral device.
 * @version  V1.00
 * @date     2016-07-20
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/


#ifndef _RTL8195BH_PHERI_ID_H_
#define _RTL8195BH_PHERI_ID_H_

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
  PID_TIMER8       = (PID_TIMER0+8),
  PID_TIMER9       = (PID_TIMER0+9),
  PID_TIMER10      = (PID_TIMER0+10),
  PID_TIMER11      = (PID_TIMER0+11),
  PID_TIMER12      = (PID_TIMER0+12),
  PID_TIMER13      = (PID_TIMER0+13),
  PID_TIMER14      = (PID_TIMER0+14),
  PID_TIMER15      = (PID_TIMER0+15),
  
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
  PID_ADC7         = (PID_ADC0+7),
  
  PID_SGPIO0       = 0x20,
  PID_SGPIO1       = (PID_SGPIO0+1),
  PID_SGPIO2       = (PID_SGPIO0+2),
  PID_SGPIO3       = (PID_SGPIO0+3),
  
  PID_UART0        = 0x28,
  PID_UART1        = (PID_UART0+1),
  PID_UART2        = (PID_UART0+2),
  
  PID_I2C0         = 0x30,
  PID_I2C1         = (PID_I2C0+1),
  PID_I2C2         = (PID_I2C0+2),
  PID_I2C3         = (PID_I2C0+3),

  PID_SPI0         = 0x34,
  PID_SPI1         = (PID_SPI0+1),
  PID_SPI2         = (PID_SPI0+2),
  PID_SPI3         = (PID_SPI0+3),
  
  PID_GDMA0        = 0x38,
  PID_GDMA1        = 0x39,
  PID_ICC          = 0x40,
  PID_WDT          = 0x41,
  PID_FLASH        = 0x42,
  PID_MIPI         = 0x43,
  PID_ETH          = 0x44,
  PID_I2S0         = 0x45,
  PID_I2S1         = (PID_I2S0+1),

  PID_PCM0         = 0x47,
  PID_PCM1         = (PID_PCM0+1),
  PID_SDIOH        = 0x49,
  PID_SDIOD        = 0x4A,
  PID_GPIO         = 0x5A,
  PID_LCDC         = 0x5B,

  PID_ISP_CONTROL0 = 0x70,
  PID_ISP_CONTROL1 = (PID_ISP_CONTROL0+1),
  PID_ISP_INTERFACE_PARALLEL = 0x72,

  PID_SWD          = 0xE0,
  PID_JTAG         = 0xE1,
  
  PID_ERR          = 0xFF
};

#ifdef __cplusplus
}
#endif


#endif //_RTL8195BH_PHERI_ID_H_

