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

#include "cmsis_os.h"
#include "icc_api.h"
#include "hal_rtc.h"
#include "wait_api.h"
#include "hal_power_mode.h"
#include "power_mode_api.h"
#include "gpio_api.h"
#include "gpio_irq_api.h"
#include "analogin_api.h"

#define ActionCAM_Old    0
#define ActionCAM_New    0
#if ActionCAM_Old
#define ADC_PIN          PA_2
#define ADC_THRESHOLD    0x308
#elif ActionCAM_New
#define ADC_PIN          PA_4
#define ADC_THRESHOLD    0x200
#endif
#define BTN_PIN          PA_13

#define ICC_CMD_SHORT    0x10
#define ICC_CMD_LONG     0x11
#define ICC_CMD_POWERON  0x12
#define ICC_CMD_POWEROFF 0x13
#define ICC_CMD_RTC      0x14
#define ICC_CMD_RTC_SET  0x15
#define ICC_CMD_BATTOFF  0x16

static gpio_t gpio_btn;
static gpio_irq_t gpio_irq_btn;
#if defined(ADC_PIN)
static analogin_t adc_batt;
#endif
static hal_rtc_adapter_t sw_rtc;
static hal_tm_reg_t rtc_reg;

osSemaphoreId btn_sema;                                  // Semaphore ID for ICC task wakeup
osSemaphoreDef(btn_sema);                                // Semaphore definition
void main_task(void const *args);                        // thread function
osThreadDef (main_task, osPriorityNormal, 1, 1024);      // thread object
#if defined(ADC_PIN)
void adc_task(void const *args);                         // thread function
osThreadDef (adc_task, osPriorityNormal, 1, 1024);       // thread object
#endif

static uint8_t is_leap_year(unsigned int year)
{
	return (!(year % 4) && (year % 100)) || !(year % 400);
}

void icc_cmd_poweroff_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	dbg_printf("\n\r%s\n\r", __FUNCTION__);

	dbg_printf("enter DeepSleep\r\n");
	DeepSleep(DS_GPIO_RISE, 0, 1, 0);
}

void icc_cmd_rtc_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	dbg_printf("\n\r%s\n\r", __FUNCTION__);

	void send_icc_cmd_rtc(void);
	send_icc_cmd_rtc();
}

void icc_cmd_rtc_set_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	dbg_printf("\n\r%s %x\n\r", __FUNCTION__, op);

	//para0[24]=sec[6]:min[6]:hrs[5]:dow[3]
	//para1[32]=dom[5]:mon[4]:year[12]:doy[9]
	icc_user_cmd_t icc_cmd;
	icc_cmd.cmd_w = cmd;
	rtc_reg.sec  = (icc_cmd.cmd_b.para0 & (0x3F << 14)) >> 14;
	rtc_reg.min  = (icc_cmd.cmd_b.para0 & (0x3F << 8)) >> 8;
	rtc_reg.hour = (icc_cmd.cmd_b.para0 & (0x1F << 3)) >> 3;
	rtc_reg.wday = icc_cmd.cmd_b.para0 & 0x7;
	rtc_reg.mday = (op & (0x1F << 25)) >> 25;
	rtc_reg.mon  = (op & (0xF << 21)) >> 21;
	rtc_reg.year = (op & (0xFFF << 9)) >> 9;
	rtc_reg.yday = op & 0x1FF;
	uint8_t leap_year = is_leap_year(rtc_reg.year + 1900);
	hal_rtc_set_time(&sw_rtc, &rtc_reg, leap_year);
}

void send_icc_cmd_short(void)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_SHORT;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_long(void)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_LONG;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_long_ex1(void)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_LONG;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 1, 2000000, NULL);
}

void send_icc_cmd_poweron(void)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_POWERON;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_poweroff(void)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_POWEROFF;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_rtc(void)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_RTC;
	cmd.cmd_b.para0 = 0;
	hal_rtc_read_time(&sw_rtc);
	//para0[24]=sec[6]:min[6]:hrs[5]:dow[3]
	//para1[32]=dom[5]:mon[4]:year[12]:doy[9]
	cmd.cmd_b.para0 = 
		(sw_rtc.rtc_reg.tim0_b.rtc_sec << 14) |
		(sw_rtc.rtc_reg.tim0_b.rtc_min << 8) |
		(sw_rtc.rtc_reg.tim0_b.rtc_hrs << 3) |
		sw_rtc.rtc_reg.tim0_b.rtc_dow;
	uint32_t para1 =
		(sw_rtc.rtc_reg.tim1_b.rtc_dom << 25) |
		((sw_rtc.rtc_reg.tim1_b.rtc_mon - 1) << 21) |
		((sw_rtc.rtc_reg.tim1_b.rtc_year - 1900) << 9) |
		(sw_rtc.rtc_reg.tim2_b.rtc_doy - 1);

	icc_cmd_send(cmd.cmd_w, para1, 2000000, NULL);
}

void send_icc_cmd_battoff(uint16_t data)
{
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_BATTOFF;
	cmd.cmd_b.para0 = 0;
	uint32_t para1 = data;
	icc_cmd_send(cmd.cmd_w, para1, 2000000, NULL);
}

void gpio_btn_irq_handler(uint32_t id, gpio_irq_event event)
{
	dbg_printf("irq\r\n");
	gpio_irq_disable(&gpio_irq_btn);
	osSemaphoreRelease(btn_sema);
}

#if defined(ADC_PIN)
void adc_task(void const *args)
{
	uint16_t adc_data = 0;
	int i, count = 0;

	while(1) {
		adc_data = analogin_read_u16(&adc_batt);

		if(adc_data < ADC_THRESHOLD) {
			count = 0;

			for(i = 0; i < 5; i ++) {
				adc_data = analogin_read_u16(&adc_batt);

				if(adc_data < ADC_THRESHOLD)
					count ++;
				else
					break;

				wait_ms(2000);
			}

			if(count == 5)
				send_icc_cmd_battoff(adc_data);
		}

		wait_ms(30*1000);
	}
}
#endif

void main_task(void const *args)
{
	int count = 0;

	// RTC
	hal_rtc_init(&sw_rtc);
	hal_rtc_read_time(&sw_rtc);
	if(sw_rtc.rtc_reg.tim1_b.rtc_year == 0) {
		// 2017/12/31 16:00:00 UTC+0 = 2018/01/01 00:00:00 UTC+8
		uint8_t leap_year = is_leap_year(2017);
		rtc_reg.sec  = 0;
		rtc_reg.min  = 0;
		rtc_reg.hour = 16;
		rtc_reg.mday = 31;
		rtc_reg.wday = 0;
		rtc_reg.yday = 364;
		rtc_reg.mon  = 11;
		rtc_reg.year = 117;
		hal_rtc_set_time(&sw_rtc, &rtc_reg, leap_year);
	}
	send_icc_cmd_rtc();

	// ICC
	icc_init();
	icc_cmd_register(ICC_CMD_POWEROFF, (icc_user_cmd_callback_t) icc_cmd_poweroff_handler, NULL);
	icc_cmd_register(ICC_CMD_RTC, (icc_user_cmd_callback_t) icc_cmd_rtc_handler, NULL);
	icc_cmd_register(ICC_CMD_RTC_SET, (icc_user_cmd_callback_t) icc_cmd_rtc_set_handler, NULL);

	// Semaphore
	btn_sema = osSemaphoreCreate(osSemaphore(btn_sema), 0);

	// Btn IRQ
	gpio_irq_init(&gpio_irq_btn, BTN_PIN, gpio_btn_irq_handler, NULL);
	gpio_irq_set(&gpio_irq_btn, IRQ_RISE, 1);

	while(1) {
		osSemaphoreWait(btn_sema, osWaitForever);

		count = 0;
		while(gpio_read(&gpio_btn) == 1) {
			if(count == 15) {
				send_icc_cmd_long();
			}
			else if(count == 30) {
				send_icc_cmd_long_ex1();
			}
			else if(count == 50) {
				break;
			}

			count ++;
			wait_ms(100);
		}

		if((count > 0) && (count < 15)) {
			send_icc_cmd_short();
		}
		else if(count == 50) {
			send_icc_cmd_poweroff();
			osSemaphoreWait(btn_sema, osWaitForever); // blocked
		}

		gpio_irq_enable(&gpio_irq_btn);
	}
}

int main(void)
{
	uint32_t ret;
	int count = 0;

	// Btn GPIO
	gpio_init(&gpio_btn, BTN_PIN);
	gpio_dir(&gpio_btn, PIN_INPUT);
	gpio_mode(&gpio_btn, PullDown);

	while(gpio_read(&gpio_btn) == 1) {
		if(count == 15)
			break;

		count ++;
		wait_ms (100);
	}

	// DeepSleep
	if(count < 15) {
		dbg_printf("enter DeepSleep\r\n");
		DeepSleep(DS_GPIO_RISE, 0, 1, 0);
	}

	send_icc_cmd_poweron();

	// wait for btn release	
	while(gpio_read(&gpio_btn) == 1) {
		wait_ms(100);
	}

	gpio_deinit(&gpio_btn);

#if defined(ADC_PIN)
	// ADC
	analogin_init(&adc_batt, ADC_PIN);
#endif
	// CMSIS-RTOS
	ret = osKernelInitialize();
	if(ret != osOK) {
		dbg_printf("KernelInitErr(0x%x)\r\n", ret);
		while(1);
	}

	if(osThreadCreate(osThread(main_task), NULL) == 0) {
		dbg_printf ("ERROR: osThreadCreate main_task\r\n");
	}

#if defined(ADC_PIN)
	if(osThreadCreate(osThread(adc_task), NULL) == 0) {
		dbg_printf ("ERROR: osThreadCreate adc_task\r\n");
	}
#endif
	osKernelStart();
}
