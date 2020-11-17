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

#include "section_config.h"

#include "hal_power_mode.h"
#include "power_mode_api.h"
#include "sys_api_ext.h"

#include "gpio_api.h"       // mbed
#include "gpio_irq_api.h"   // mbed

extern void shell_cmd_init (void);
extern s32 shell_task(void);
extern int main(void);

#define ICC_CMD_REQ_DEEPSLEEP                   (0x10)
#define ICC_CMD_REQ_DEEPSLEEP_STIMER_DURATION   (0x11)

#define ICC_CMD_REQ_STANDBY                     (0x20)
#define ICC_CMD_REQ_STANDBY_STIMER_DURATION     (0x21)
#define ICC_CMD_REQ_STANDBY_GPIO_PIN            (0x22)
#define ICC_CMD_REQ_STANDBY_STIMER_WAKE         (0x23)
#define ICC_CMD_REQ_STANDBY_GPIO_WAKE           (0x24)
#define ICC_CMD_REQ_STANDBY_GPIO_SET            (0x25)
#define ICC_CMD_REQ_STANDBY_GPIO13_SET          (0x26)

#define ICC_CMD_REQ_GET_LS_WAKE_REASON          (0x30)
#define ICC_CMD_NOTIFY_LS_WAKE_REASON           (0x31)

static uint32_t deepsleep_stimer_duration = 60 * 1000 * 1000;

static uint32_t standby_stimer_duration = 60 * 1000 * 1000;

/**
 * Variables which are placed in data section would keep values after resume from Standby power saving
 * Please note that global variable with initial value 0 may put into BSS section.
 * BSS would be clean up to 0 in ram_start.
 */
SECTION(".data") static uint16_t standby_wake_event;
SECTION(".data") static PinName standby_gpio_pin = NC;
SECTION(".data") static uint32_t standby_wake_mask = 0;
SECTION(".data") static gpio_irq_t gpio_standby;
SECTION(".data") static uint32_t standby_stimer_wake = 1;
SECTION(".data") static uint32_t standby_gpio_wake = 1;
SECTION(".data") static uint32_t standby_wake_reason = 0;
SECTION(".data") volatile static uint32_t gpio_setting = 0x0;
SECTION(".data") volatile static uint32_t gpio13_setting = 0x0;
SECTION(".data") volatile static uint32_t gpio_pull_set = 0x0;

uint32_t sys_slp_wake_sts = 0;

void icc_req_deepsleep_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    icc_user_cmd_t icc_cmd;
    uint16_t wake_event;

    icc_cmd.cmd_w = cmd;
    wake_event = icc_cmd.cmd_b.para0;

    dbg_printf("deepsleep wake event:0x%04X\r\n", wake_event);

    DeepSleep(wake_event, deepsleep_stimer_duration, 1, 0);
}

void icc_req_standby_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    icc_user_cmd_t icc_cmd;

    icc_cmd.cmd_w = cmd;
    uint32_t wake_event = icc_cmd.cmd_b.para0;
    standby_wake_event |= wake_event;
    
    if(gpio_pull_set == 1){
	ls_sys_gpio_pull_ctrl(gpio_setting);
    }
  
    if (standby_gpio_pin == 13) {
        if (gpio13_setting == 1) {
            gpio_irq_init(&gpio_standby, standby_gpio_pin, NULL, NULL);
            gpio_irq_pull_ctrl(&gpio_standby, PullUp);
            gpio_irq_set(&gpio_standby, IRQ_FALL, 1);
        }else{   
            gpio_irq_init(&gpio_standby, standby_gpio_pin, NULL, NULL);
            gpio_irq_pull_ctrl(&gpio_standby, PullDown);
            gpio_irq_set(&gpio_standby, IRQ_RISE, 1);
        }
        uint32_t btn_state = hal_gpio_irq_read(&(gpio_standby.gpio_irq_adp));
        dbg_printf("btn_state:%d\r\n", btn_state);
    }
    else if (standby_gpio_pin != NC) {
 	if(gpio_pull_set == 0){       
	    gpio_irq_init(&gpio_standby, standby_gpio_pin, NULL, NULL);
	    gpio_irq_pull_ctrl(&gpio_standby, PullDown);
	    gpio_irq_set(&gpio_standby, IRQ_RISE, 1);
	}
	else
	{
	    if(((gpio_setting & (0x11 << standby_gpio_pin))>> standby_gpio_pin) == 0x10)
	    {
		gpio_irq_init(&gpio_standby, standby_gpio_pin, NULL, NULL);
		gpio_irq_pull_ctrl(&gpio_standby, PullUp);
		gpio_irq_set(&gpio_standby, IRQ_FALL, 1);	        
	    }
	    else
	    {
		gpio_irq_init(&gpio_standby, standby_gpio_pin, NULL, NULL);
		gpio_irq_pull_ctrl(&gpio_standby, PullDown);
		gpio_irq_set(&gpio_standby, IRQ_RISE, 1);	       
	    }
	}
        uint32_t btn_state = hal_gpio_irq_read(&(gpio_standby.gpio_irq_adp));

        dbg_printf("btn_state:%d\r\n", btn_state);
    }
    
    standby_wake_mask = 0;
    if (standby_wake_event & DSTBY_WLAN)    standby_wake_mask |= LS_WAKE_EVENT_HS;
    if (standby_wake_event & DSTBY_STIMER)  standby_wake_mask |= LS_WAKE_EVENT_AON_TIMER;
    if (standby_wake_event & DSTBY_GPIO)    standby_wake_mask |= LS_WAKE_EVENT_AON_GPIO | LS_WAKE_EVENT_GPIO;
      
    dbg_printf("Standby wake event:0x%04X wake mask:%08X\r\n", standby_wake_event, standby_wake_mask);
    LsStandby(standby_wake_event, standby_stimer_duration, 1, standby_gpio_pin);
}

void icc_req_change_config_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    icc_user_cmd_t icc_cmd;
    uint32_t value;

    icc_cmd.cmd_w = cmd;
    value = icc_cmd.cmd_b.para0;

    switch(arg)
    {
        case ICC_CMD_REQ_DEEPSLEEP_STIMER_DURATION:
        {
            deepsleep_stimer_duration = value * 1000 * 1000;
            break;
        }
        case ICC_CMD_REQ_STANDBY_STIMER_DURATION:
        {
            standby_wake_event |= DSTBY_STIMER;
            standby_stimer_duration = value * 1000 * 1000;
            break;
        }
        case ICC_CMD_REQ_STANDBY_GPIO_PIN:
        {
            standby_wake_event |= DSTBY_GPIO;
            standby_gpio_pin = (PinName) value;  // GPIO A starts from 0 to 13
            break;
        }
        case ICC_CMD_REQ_STANDBY_STIMER_WAKE:
        {
            standby_stimer_wake = value;
            break;
        }
        case ICC_CMD_REQ_STANDBY_GPIO_WAKE:
        {
            standby_gpio_wake = value;
            break;
        }
        case ICC_CMD_REQ_STANDBY_GPIO_SET:
        {
            gpio_pull_set=1;
            gpio_setting = value;
            break;
        }
        case ICC_CMD_REQ_STANDBY_GPIO13_SET:
        {
            gpio13_setting = value;
            break;
        }
    }
}

void icc_req_get_ls_wake_reason_handler (uint32_t cmd, uint32_t op, uint32_t arg)
{
    icc_user_cmd_t cmd_ret = { .cmd_b.cmd = ICC_CMD_NOTIFY_LS_WAKE_REASON, .cmd_b.para0 = standby_wake_reason };
    icc_cmd_send (cmd_ret.cmd_w, 0, 1000, NULL); // icc timeout 1000us
}

void print_wake_reason(uint32_t wake_reason) {
    if ( wake_reason & LS_WAKE_EVENT_STIMER )      dbg_printf("wake from STIMER\r\n");
    if ( wake_reason & LS_WAKE_EVENT_GTIMER )      dbg_printf("wake from GTIMER\r\n");
    if ( wake_reason & LS_WAKE_EVENT_GPIO )        dbg_printf("wake from GPIO\r\n");
    if ( wake_reason & LS_WAKE_EVENT_PWM )         dbg_printf("wake from PWM\r\n");
    if ( wake_reason & LS_WAKE_EVENT_WLAN )        dbg_printf("wake from WLAN\r\n");
    if ( wake_reason & LS_WAKE_EVENT_UART )        dbg_printf("wake from UART\r\n");
    if ( wake_reason & LS_WAKE_EVENT_I2C )         dbg_printf("wake from I2C\r\n");
    if ( wake_reason & LS_WAKE_EVENT_ADC )         dbg_printf("wake from ADC\r\n");
    if ( wake_reason & LS_WAKE_EVENT_COMP )        dbg_printf("wake from COMP\r\n");
    if ( wake_reason & LS_WAKE_EVENT_SGPIO )       dbg_printf("wake from SGPIO\r\n");
    if ( wake_reason & LS_WAKE_EVENT_AON_GPIO )    dbg_printf("wake from AON_GPIO\r\n");
    if ( wake_reason & LS_WAKE_EVENT_AON_TIMER )   dbg_printf("wake from AON_TIMER\r\n");
    if ( wake_reason & LS_WAKE_EVENT_AON_RTC )     dbg_printf("wake from AON_RTC\r\n");
    if ( wake_reason & LS_WAKE_EVENT_AON_ADAPTER ) dbg_printf("wake from AON_ADAPTER\r\n");
    if ( wake_reason & LS_WAKE_EVENT_HS )          dbg_printf("wake from HS\r\n");
}

void do_LsStandby()
{
    if(gpio_pull_set == 1){

	ls_sys_gpio_pull_ctrl(gpio_setting);
    } 
  
    if (standby_gpio_pin == 13) {
        if (gpio13_setting == 1) {
            gpio_irq_init(&gpio_standby, standby_gpio_pin, NULL, NULL);
            gpio_irq_pull_ctrl(&gpio_standby, PullUp);
            gpio_irq_set(&gpio_standby, IRQ_FALL, 1);
        }else{   
            gpio_irq_init(&gpio_standby, standby_gpio_pin, NULL, NULL);
            gpio_irq_pull_ctrl(&gpio_standby, PullDown);
            gpio_irq_set(&gpio_standby, IRQ_RISE, 1);
        }
        uint32_t btn_state = hal_gpio_irq_read(&(gpio_standby.gpio_irq_adp));
    }
    else if (standby_gpio_pin != NC) {
 	if(gpio_pull_set == 0){       
	    gpio_irq_init(&gpio_standby, standby_gpio_pin, NULL, NULL);
	    gpio_irq_pull_ctrl(&gpio_standby, PullDown);
	    gpio_irq_set(&gpio_standby, IRQ_RISE, 1);
	}
	else
	{
	    if(((gpio_setting & (0x11 << standby_gpio_pin))>> standby_gpio_pin) == 0x10)
	    {
		gpio_irq_init(&gpio_standby, standby_gpio_pin, NULL, NULL);
		gpio_irq_pull_ctrl(&gpio_standby, PullUp);
		gpio_irq_set(&gpio_standby, IRQ_FALL, 1);	        
	    }
	    else
	    {
		gpio_irq_init(&gpio_standby, standby_gpio_pin, NULL, NULL);
		gpio_irq_pull_ctrl(&gpio_standby, PullDown);
		gpio_irq_set(&gpio_standby, IRQ_RISE, 1);	       
	    }
	}
        uint32_t btn_state = hal_gpio_irq_read(&(gpio_standby.gpio_irq_adp));
    }
		
    LsStandby(standby_wake_event, standby_stimer_duration, 1, standby_gpio_pin); 
}

int main (void)
{
    if (hs_is_suspend())
    {
        // if LS is wake from WLAN TBTT, do nothing here until expected wake event happened
        while( ((standby_wake_reason = ls_get_wake_reason()) & standby_wake_mask) == 0 ) ;

        LsClearWLSLP();
        print_wake_reason(standby_wake_reason);

        if (standby_wake_reason & LS_WAKE_EVENT_HS)
        {
           HS_Power_On();
        }
        else if (standby_wake_reason & LS_WAKE_EVENT_AON_TIMER)
        {
            if (standby_stimer_wake == 1) {
                HS_Power_On();
            } else {
                standby_stimer_wake = (standby_stimer_wake == 0) ? 0 : standby_stimer_wake - 1;
                dbg_printf("do stimer task here, standby_stimer_wake:%d\r\n", standby_stimer_wake);
                do_LsStandby();
            }
        }
        else if (standby_wake_reason & (LS_WAKE_EVENT_AON_GPIO | LS_WAKE_EVENT_GPIO))
        {
            if (standby_gpio_wake == 1) {
                HS_Power_On();
            } else {
                standby_gpio_wake = (standby_gpio_wake == 0) ? 0 : standby_gpio_wake - 1;            
                dbg_printf("do gpio task here, standby_gpio_wake:%d\r\n", standby_gpio_wake);
                do_LsStandby();
            }
        }
        else
        {
            dbg_printf("un-expected wake event!\r\n");
        }
    }

    standby_wake_event = 0;
    standby_gpio_pin = NC;
    standby_wake_mask = 0;
    osKernelInitialize ();

    icc_init ();

    icc_cmd_register(ICC_CMD_REQ_DEEPSLEEP, (icc_user_cmd_callback_t)icc_req_deepsleep_handler, ICC_CMD_REQ_DEEPSLEEP);
    icc_cmd_register(ICC_CMD_REQ_STANDBY, (icc_user_cmd_callback_t)icc_req_standby_handler, ICC_CMD_REQ_STANDBY);

    icc_cmd_register(ICC_CMD_REQ_DEEPSLEEP_STIMER_DURATION, (icc_user_cmd_callback_t)icc_req_change_config_handler, ICC_CMD_REQ_DEEPSLEEP_STIMER_DURATION);
    icc_cmd_register(ICC_CMD_REQ_STANDBY_STIMER_DURATION, (icc_user_cmd_callback_t)icc_req_change_config_handler, ICC_CMD_REQ_STANDBY_STIMER_DURATION);
    icc_cmd_register(ICC_CMD_REQ_STANDBY_GPIO_PIN, (icc_user_cmd_callback_t)icc_req_change_config_handler, ICC_CMD_REQ_STANDBY_GPIO_PIN);
    icc_cmd_register(ICC_CMD_REQ_STANDBY_STIMER_WAKE, (icc_user_cmd_callback_t)icc_req_change_config_handler, ICC_CMD_REQ_STANDBY_STIMER_WAKE);
    icc_cmd_register(ICC_CMD_REQ_STANDBY_GPIO_WAKE, (icc_user_cmd_callback_t)icc_req_change_config_handler, ICC_CMD_REQ_STANDBY_GPIO_WAKE);
    icc_cmd_register(ICC_CMD_REQ_STANDBY_GPIO_SET, (icc_user_cmd_callback_t)icc_req_change_config_handler, ICC_CMD_REQ_STANDBY_GPIO_SET);
    icc_cmd_register(ICC_CMD_REQ_STANDBY_GPIO13_SET, (icc_user_cmd_callback_t)icc_req_change_config_handler, ICC_CMD_REQ_STANDBY_GPIO13_SET);

    icc_cmd_register(ICC_CMD_REQ_GET_LS_WAKE_REASON, (icc_user_cmd_callback_t)icc_req_get_ls_wake_reason_handler, ICC_CMD_REQ_GET_LS_WAKE_REASON);

    osKernelStart ();

    return 0;
}