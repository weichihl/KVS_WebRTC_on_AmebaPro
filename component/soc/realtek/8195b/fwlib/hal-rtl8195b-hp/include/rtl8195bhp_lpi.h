/**************************************************************************//**
 * @file     rtl8195bhp_lpi.h
 * @brief    The rtl8195b-hp platform low priority interrupt handler header file.
 * @version  V1.00
 * @date     2016-07-04
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
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

#ifndef _RTL8195BHP_LPI_H_
#define _RTL8195BHP_LPI_H_
#include "basic_types.h"
 
#ifdef  __cplusplus
extern "C"
{
#endif

/* define the Low Priority Interrupt trigger signal type */
enum  low_pri_int_mode_e
{
    LPInt_Level_Trigger       = 0,
    LPInt_Edge_Trigger        = 1
};
typedef uint8_t low_pri_int_mode_t;

/* define the Low Priority Interrupt event ID */
enum  low_pri_int_event_e
{
//    LPInt_WDT_VOE       = 0,    // VOE MCU WDT Timeout
    LPInt_WDT_WL        = 1,    // WLan MCU WDT Timeout
    LPInt_Bst_OCP       = 2,    // Boost OCP
    LPInt_SWR_OCP       = 3,    // Switch Regulator Current Over Limitation
    LPInt_RXI_Bus       = 9,    // RXI300 Bus Interrupt
    LPInt_DDRPhy_Int0   = 16,   // DDR Phy DPI Interrupt 0
    LPInt_DDRPhy_Int1   = 17,   // DDR Phy DPI Interrupt 1
    LPInt_DDRPhy_Int2   = 18,   // DDR Phy DPI Interrupt 2
    LPInt_DDRPhy_Int3   = 19    // DDR Phy DPI Interrupt 3
};

typedef struct hal_lpi_int_s {
    /* Low Priority IRQ (IRQ 31) Handler */
//    irq_handler_t voe_wdt_handler;    /* the VOE MCU WDT timeout handler */
//    void *voe_wdt_arg;    /* the argument of VOE WDT timeout handler */
    irq_handler_t wl_wdt_handler;    /* the WLan WDT Timeout handler */
    void *wl_wdt_arg;    /* the argument of WLan WDT Timeout handler */
    irq_handler_t bst_ocp_handler;    /* the Boost OCP interrupt handler */
    void *bst_ocp_arg;    /* the argument of Boost OCP interrupt handler */
    irq_handler_t swr_ocp_handler;    /* the switch regulator over current protection interrupt handler */
    void *swr_ocp_arg;    /* the argument of switch regulator over current protection interrupt handler */
    irq_handler_t rxi_bus_handler;    /* the RXI bus interrupt handler */
    void *rxi_bus_arg;    /* the argument of RXI bus  interrupt handler */
    irq_handler_t ddrphy_int_handler[4];    /* the DDR Phy DPI interrupt handler */
    void *ddrphy_int_arg[4];    /* the argument of DDR Phy DPI interrupt handler */
} hal_lpi_int_t, *phal_lpi_int_t;

void hal_lpi_init_rtl8195bhp (hal_lpi_int_t *plpi_hdl);
void hal_lpi_handler_reg_rtl8195bhp (uint8_t int_id, low_pri_int_mode_t int_trig_type, irq_handler_t handler, void *arg);
void hal_lpi_en_rtl8195bhp (uint8_t int_id);
void hal_lpi_dis_rtl8195bhp (uint8_t int_id);
void hal_lpi_reg_irq_rtl8195bhp (irq_handler_t handler, uint8_t priority);

/**
  \brief  The data structure of the stubs function for the Low Priority Interrupt API functions in ROM
*/
typedef struct hal_lpi_func_stubs_s {
    /* Low Priority Interrupt API*/
    void (*hal_lpi_init) (hal_lpi_int_t *plpi_hdl);
    void (*hal_lpi_handler_reg) (uint8_t int_id, low_pri_int_mode_t int_trig_type, irq_handler_t handler, void *arg);
    void (*hal_lpi_en) (uint8_t int_id);
    void (*hal_lpi_dis) (uint8_t int_id);
    void (*hal_lpi_reg_irq) (irq_handler_t handler, uint8_t priority);
    
    uint32_t reserved[8];  // reserved space for next ROM code version function table extending.
} hal_lpi_func_stubs_t;


#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _RTL8195BHP_LPI_H_"

