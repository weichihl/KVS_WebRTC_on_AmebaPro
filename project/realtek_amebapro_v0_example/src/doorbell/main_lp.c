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
#include "section_config.h"
#include "hal_power_mode.h"
#include "power_mode_api.h"
#include "gpio_api.h"
#include "gpio_irq_api.h"
#include "analogin_api.h"
#include "app_setting.h"
#include "sys_api_ext.h"

static hal_rtc_adapter_t sw_rtc;
static hal_tm_reg_t rtc_reg;

SECTION(".data") static uint16_t standby_wake_event;
SECTION(".data") static PinName standby_gpio_pin = NC;
SECTION(".data") static uint32_t standby_wake_mask = 0;
SECTION(".data") static gpio_irq_t gpio_standby;
SECTION(".data") static uint32_t standby_stimer_wake = 1;
SECTION(".data") static uint32_t standby_gpio_wake = 1;
SECTION(".data") static uint32_t standby_wake_reason = 0;

static uint8_t is_leap_year(unsigned int year)
{
	return (!(year % 4) && (year % 100)) || !(year % 400);
}


#define USE_IRQ 0

//Button variable
#if USE_PUSH_BUTTON   
static gpio_t gpio_btn;
static gpio_irq_t gpio_irq_btn;
osSemaphoreId btn_sema;                                  // Semaphore ID for ICC task wakeup
osSemaphoreDef(btn_sema);                                // Semaphore definition
#endif   

//PIR variable
#if USE_PIR_SENSOR                          
#define PIR_START       1
#define PIR_STOP        0 
static gpio_t gpio_led_pir;
static gpio_t gpio_ctr_pir;
extern void pir_start(void);
extern void pir_stop(void);
extern void readlowpowerpyro(void); 
int pir_debounce = 0;
#endif

//Battery detect
#if USE_BATTERY_DETECT   
static analogin_t adc33;
void adc_task(void const *args);                         // thread function
osThreadDef (adc_task, osPriorityNormal, 1, 1024);       // thread object
#endif   

//status control
static int startup_status = 0;
uint32_t sys_slp_wake_sts = 0;
uint32_t wake_reason = 0;
int icc_ready = 0;
   
#define NORMAL_STATUS   0
#define BTN_STATUS_RING 1
#define BTN_STATUS_QR   2
#define PIR_STATUS_RUN  3
#define PIR_STATUS_STOP 4
#define WOWLAN_STATUS   5
#define QR_TIME_LEN 30

//Task definition
void main_task(void const *args);                        // thread function
osThreadDef (main_task, osPriorityNormal, 1, 1024);      // thread object


#if USE_WOWLAN
#if USE_PIR_SENSOR
#define TRIGGER_NUM 3
#else
#define TRIGGER_NUM 2
#endif
#else
#if USE_PIR_SENSOR
#define TRIGGER_NUM 2
#else
#define TRIGGER_NUM 1
#endif
#endif
wakeup_source_t wakeup_source[TRIGGER_NUM]=
{
#if USE_PIR_SENSOR
  {DSTBY_GPIO, 0, PA_3},
#endif  
  {DSTBY_GPIO, 0, PA_13},
#if USE_WOWLAN  
  {DSTBY_WLAN, 0, 0},
#endif  
  //{DSTBY_STIMER,60000000, 0}
};

/* icc handler*/
void icc_cmd_poweroff_handler(uint32_t cmd, uint32_t op, uint32_t arg)
{
	dbg_printf("\n\r%s\n\r", __FUNCTION__);
	
#ifdef QFN_128_BOARD  
	hal_dbg_port_disable();
#endif	
	//free all gpio interrupt
#if USE_IRQ
#else	
	gpio_deinit(&gpio_btn);
#endif	

#if POWER_SAVE_MODE	
	int i = 0;
	u16 Option = 0;
	u32 SDuration = 60*1000*1000;
	standby_wake_mask = 0;		
	// register wakeup source
	for(i=0; i<TRIGGER_NUM; i++)
	{
	    Option|= wakeup_source[i].Option;
	    if(wakeup_source[i].Option == DSTBY_GPIO){
		gpio_irq_init(&gpio_irq_btn, wakeup_source[i].gpio_reg, NULL, NULL);
		//gpio_irq_pull_ctrl(&gpio_irq_btn, PullDown);
		//gpio_irq_debounce_set(&gpio_irq_btn,1000*512,1);
		gpio_irq_set(&gpio_irq_btn, IRQ_RISE, 0);
		gpio_irq_enable(&gpio_irq_btn);
	    }
	    else if(wakeup_source[i].Option == DSTBY_STIMER){
		SDuration = wakeup_source[i].SDuration;
	    }
	    
	    if (wakeup_source[i].Option & DSTBY_WLAN)    standby_wake_mask |= LS_WAKE_EVENT_HS;
	    if (wakeup_source[i].Option & DSTBY_STIMER)  standby_wake_mask |= LS_WAKE_EVENT_AON_TIMER;
	    if (wakeup_source[i].Option & DSTBY_GPIO)    standby_wake_mask |= LS_WAKE_EVENT_AON_GPIO;
	    if (wakeup_source[i].Option & DSTBY_GPIO)    standby_wake_mask |= LS_WAKE_EVENT_GPIO;
	}
	
			
	//Enter Standby
	dbg_printf("Enter Standby mode\r\n");
	LsStandby(Option, SDuration, 1, PA_13);
	while(1);
#else	
	dbg_printf("Enter deepsleep mode\r\n");
	DeepSleep(BIT2, 1000000, 1, 0);
#endif	
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
	dbg_printf("send_icc_cmd_short\r\n");
  	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_SHORT;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_long(void)
{
	dbg_printf("send_icc_cmd_long\r\n");
  	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_LONG;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_poweron(void)
{
	dbg_printf("send_icc_cmd_poweron\r\n");
  	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_POWERON;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_poweroff(void)
{
	dbg_printf("send_icc_cmd_poweroff\r\n");
  	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_POWEROFF;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, 0, 2000000, NULL);
}

void send_icc_cmd_battoff(uint16_t data)
{
	dbg_printf("send_icc_cmd_battoff\r\n");
  	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_BATTOFF;
	cmd.cmd_b.para0 = 0;
	uint32_t para1 = data;
	icc_cmd_send(cmd.cmd_w, para1, 2000000, NULL);
}

void send_icc_cmd_rtc(void)
{
	dbg_printf("send_icc_cmd_rtc\r\n");
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

void gpio_btn_irq_handler(uint32_t id, gpio_irq_event event)
{
	//dbg_printf("irq\r\n");
	gpio_irq_disable(&gpio_irq_btn);
	osSemaphoreRelease(btn_sema);
}

#if USE_BATTERY_DETECT
void adc_task(void const *args)
{
	uint16_t adc33_data = 0;
	int i, count = 0;

	while(1) {
		adc33_data = analogin_read_u16(&adc33);

		if(adc33_data < ADC_THRESHOLD) {
			count = 0;

			for(i = 0; i < 5; i ++) {
				adc33_data = analogin_read_u16(&adc33);

				if(adc33_data < ADC_THRESHOLD)
					count ++;
				else
					break;

				wait_ms(2000);
			}

			if(count == 5)
				send_icc_cmd_battoff(adc33_data);
		}

		wait_ms(30*1000);
	}
}
#endif

void main_task(void const *args)
{
	int count = 0;

#if USE_PUSH_BUTTON
	//if(wake_reason == 0)
	{
	    while(gpio_read(&gpio_btn) == 1) {
		count ++;
		if(count >= QR_TIME_LEN){		
		    startup_status = BTN_STATUS_QR;
		    break;
		}
		else
		{	
#if (POWER_SAVE_MODE == 0)
		startup_status = BTN_STATUS_RING;
#endif			
		
		}
		wait_ms (100);
	    }
	}
#endif
		
	wait_ms (100);

	
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

	
	if(startup_status == PIR_STATUS_RUN){
#if USE_PIR_SENSOR	  
		send_icc_cmd_pir(1); 
#endif		
	}	
	else if(startup_status == BTN_STATUS_QR){
              send_icc_cmd_long();  
        }else if(startup_status == BTN_STATUS_RING){
              send_icc_cmd_short();
	      
        }
	
#if USE_PUSH_BUTTON
	//debunce
	 while(gpio_read(&gpio_btn) == 1) {
	  	wait_ms (100); 
	 }
#endif	
	
	startup_status = NORMAL_STATUS;
	icc_ready = 1;
			 
#if USE_IRQ
	gpio_deinit(&gpio_btn);
	// button Semaphore
	btn_sema = osSemaphoreCreate(osSemaphore(btn_sema), 0);

	// button IRQ
	gpio_irq_init(&gpio_irq_btn, BTN_PIN, gpio_btn_irq_handler, NULL);
	//gpio_irq_pull_ctrl(&gpio_irq_btn, PullDown);
	//gpio_irq_debounce_set(&gpio_irq_btn,1000*512,1);
	gpio_irq_set(&gpio_irq_btn, IRQ_RISE, 0);
        gpio_irq_enable(&gpio_irq_btn);
	
	while(1) {
		osSemaphoreWait(btn_sema, osWaitForever);
			  	
		send_icc_cmd_short();

		gpio_irq_enable(&gpio_irq_btn);
	}
#else
	while(1) {
		
	  	if(gpio_read(&gpio_btn) == 1) {                
		      send_icc_cmd_short();
		
		      while(gpio_read(&gpio_btn) == 1) {
			  wait_ms(100);
		      }
		}
		else{
		  	wait_ms(33);
#if USE_PIR_SENSOR
			pir_debounce++;
#endif
		}

	}
#endif	
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
}

int main(void)
{
	uint32_t ret;      	
	startup_status = NORMAL_STATUS;
	icc_ready = 0;

#if POWER_SAVE_MODE
    if (hs_is_suspend())
    {
        // if LS is wake from WLAN TBTT, do nothing here until expected wake event happened
        while( ((standby_wake_reason = ls_get_wake_reason()) & standby_wake_mask) == 0 ) ;

        print_wake_reason(standby_wake_reason);

        if (standby_wake_reason & LS_WAKE_EVENT_HS)
        {
             HS_Power_On();
        }
        else if (standby_wake_reason & (LS_WAKE_EVENT_AON_GPIO | LS_WAKE_EVENT_GPIO))
        {
             HS_Power_On();
        }
        else
        {
            dbg_printf("un-expected wake event!\r\n");
        }
    }	
	
#if USE_PIR_SENSOR
		uint32_t volatile sys_slp_wake_io = hal_ls_gpio_wake_sts();
		dbg_printf("\r\sys_slp_wake_io:0x%X\r\n", sys_slp_wake_io);
		print_wake_reason(wake_reason);    
		switch(sys_slp_wake_io)
		{
		case 0x1:
			startup_status = PIR_STATUS_RUN;  
			break;
		case 0x2:
			startup_status = BTN_STATUS_RING;
			break;  
		}
#else
		startup_status = BTN_STATUS_RING;
#endif

#endif	

	       
// PIR initial
#if USE_PIR_SENSOR 
	pir_start();
#endif             

#if USE_PUSH_BUTTON
	// Button initial
	gpio_init(&gpio_btn, BTN_PIN); 
	gpio_dir(&gpio_btn, PIN_INPUT);
	gpio_mode(&gpio_btn, PullDown);
#endif	
		
#if USE_BATTERY_DETECT
	// ADC
	analogin_init(&adc33, ADC_PIN);
#endif
		
	// CMSIS-RTOS
	ret = osKernelInitialize();
	if(ret != osOK) {
		dbg_printf("KernelInitErr(0x%x)\r\n", ret);
		while(1);
	}
	
	// ICC
	icc_init();
	icc_cmd_register(ICC_CMD_POWEROFF, (icc_user_cmd_callback_t) icc_cmd_poweroff_handler, NULL);
	icc_cmd_register(ICC_CMD_RTC, (icc_user_cmd_callback_t) icc_cmd_rtc_handler, NULL);
	icc_cmd_register(ICC_CMD_RTC_SET, (icc_user_cmd_callback_t) icc_cmd_rtc_set_handler, NULL);
	dbg_printf("startup_status1 = %d\r\n",startup_status);

	if(osThreadCreate(osThread(main_task), NULL) == 0) {
		dbg_printf ("ERROR: osThreadCreate\r\n");
	}
	 dbg_printf("startup_status2 = %d\r\n",startup_status);

#if USE_BATTERY_DETECT	
	if(osThreadCreate(osThread(adc_task), NULL) == 0) {
		dbg_printf ("ERROR: osThreadCreate adc_task\r\n");
	}
#endif
			          
	osKernelStart();
}
