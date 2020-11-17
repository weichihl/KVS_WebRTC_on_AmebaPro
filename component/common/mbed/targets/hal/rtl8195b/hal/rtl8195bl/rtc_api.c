/**************************************************************************//**
 * @file     rtc_api.c
 * @brief    This file implements the RTC Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-25
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

#include "rtc_api.h"

#if DEVICE_RTC
#include <time.h>
#include "timer_api.h"      // software-RTC: use a g-timer for the tick of the RTC

//#define SW_RTC_TIMER_ID        TIMER4

//static gtimer_t sw_rtc;
static struct tm rtc_timeinfo;
static hal_rtc_adapter_t sw_rtc;
static hal_tm_reg_t rtc_reg;
static hal_rtc_alarm_t rtc_alarm;

static int sw_rtc_en;
static u32 year_now;

//const static u8 dim[14] = {
//	31, 0, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31, 28 };

static inline bool is_leap_year(unsigned int year)
{
	return (!(year % 4) && (year % 100)) || !(year % 400);
}

/*
static u8 days_in_month (u8 month, u8 year)
{
	u8 ret = dim [ month - 1 ];
	if (ret == 0)
		ret = is_leap_year (year) ? 29 : 28;
	return ret;
}
*/
void rtc_init(void)
{
    // Enable RTC function
    hal_rtc_init (&sw_rtc);
    sw_rtc_en = 1;
}

void rtc_free(void)
{
    // Disable RTC function
    sw_rtc_en = 0;
    hal_rtc_deinit (&sw_rtc);
}

int rtc_isenabled(void)
{
    return sw_rtc_en;
}

time_t rtc_read(void)
{
    time_t t;

    // Read the RTC
    hal_rtc_read_time(&sw_rtc); // Read RTC

    if (year_now != (sw_rtc.rtc_reg.tim1_b.rtc_year)) { // When next year is coming, reset leap year register
        if (is_leap_year(sw_rtc.rtc_reg.tim1_b.rtc_year)) { // Is leap year?!
            sw_rtc.rtc_reg.tim2_b.rtc_m4iscyr = 0;   // Year is leap year
        } else {
            sw_rtc.rtc_reg.tim2_b.rtc_m4iscyr = 1;   // Year is not leap year
        }
        hal_rtc_set_leap_year (&sw_rtc);
        year_now = sw_rtc.rtc_reg.tim1_b.rtc_year;
    }
    rtc_timeinfo.tm_sec = sw_rtc.rtc_reg.tim0_b.rtc_sec;          /* seconds,  range 0 to 59          */
    rtc_timeinfo.tm_min = sw_rtc.rtc_reg.tim0_b.rtc_min;          /* minutes, range 0 to 59           */
    rtc_timeinfo.tm_hour = sw_rtc.rtc_reg.tim0_b.rtc_hrs;         /* hours, range 0 to 23             */
    rtc_timeinfo.tm_mday = sw_rtc.rtc_reg.tim1_b.rtc_dom;         /* day of the month, range 1 to 31  */
    rtc_timeinfo.tm_wday = sw_rtc.rtc_reg.tim0_b.rtc_dow;         /* day of the week, range 0 to 6    */
    rtc_timeinfo.tm_yday = sw_rtc.rtc_reg.tim2_b.rtc_doy-1;       /* day in the year, range 0 to 365  */
    rtc_timeinfo.tm_mon = sw_rtc.rtc_reg.tim1_b.rtc_mon-1;        /* month, range 0 to 11             */
    rtc_timeinfo.tm_year = sw_rtc.rtc_reg.tim1_b.rtc_year-1900;   /* The number of years since 1900   */

    // Convert to timestamp
    t = mktime(&rtc_timeinfo);

    //hal_rtc_read_alarm(&sw_rtc); // Read Alarm
    return t;
}

void rtc_write(time_t t)
{
    // Convert the time in to a tm
    struct tm *timeinfo = localtime(&t); // When time_t is 32bit, it will overflow after 18 Jan 2038.
    u8 leap_year =0;    // 1: Leap Year
    //struct tm *timeinfo = gmtime(&t);

    if (timeinfo == NULL) {
        // Error
        return;
    }
    leap_year = is_leap_year(timeinfo->tm_year+1900);
    year_now = timeinfo->tm_year+1900;
    // Set the RTC
    rtc_reg.sec  = timeinfo->tm_sec;
    rtc_reg.min  = timeinfo->tm_min;
    rtc_reg.hour = timeinfo->tm_hour;
    rtc_reg.mday = timeinfo->tm_mday;
    rtc_reg.wday = timeinfo->tm_wday;
    rtc_reg.yday = timeinfo->tm_yday;
    rtc_reg.mon  = timeinfo->tm_mon;
    rtc_reg.year = timeinfo->tm_year;
    if (hal_rtc_set_time (&sw_rtc, &rtc_reg, leap_year) != HAL_OK) {
        return;
    }
    //dbg_printf("year_Day %d\r\n",timeinfo->tm_yday);
    //dbg_printf("Current local time and date: %s\r\n", asctime(timeinfo));

}

/**
  * @brief  Set the specified RTC Alarm and interrupt.
  * @param  alarm: alarm object define in application software.
  * @param  alarmHandler:  alarm interrupt callback function.
  * @retval   status:
  *            - 1: success
  *            - Others: failure
  */
u32 rtc_set_alarm(alarm_t *alrm, alarm_irq_handler alarmHandler)
{
	//rtc_alarm_handler = alarmHandler;

	/* set alarm */
    rtc_alarm.sec  = alrm->sec;
    rtc_alarm.min  = alrm->min;
    rtc_alarm.hour = alrm->hour;
    rtc_alarm.yday = alrm->yday;
    if (hal_rtc_set_alarm(&sw_rtc, &rtc_alarm) != HAL_OK) {
        return _FALSE;
    }
    hal_rtc_reg_alarm_irq(&sw_rtc, (rtc_alarm_callback_t)alarmHandler, (void *)0);
	return _TRUE;
}

/**
  * @brief  Disable RTC Alarm and function.
  * @param  none
  * @retval   none
  */
void rtc_disable_alarm(void)
{
    hal_rtc_unreg_alarm_irq(&sw_rtc);
	//rtc_alarm_handler = NULL;
}

/**
  * @brief  To set the compensation value of the RTC CLK.
  * @param  func_en The RTC compensation function enable. 1: Enable; 0:Disable
  * @retval   status:
  *            - 1: success
  *            - Others: failure
  */
u32 rtc_set_comp(u8 func_en)
{
    if (hal_rtc_set_comp(&sw_rtc, func_en) != HAL_OK) {
        return _FALSE;
    }
	return _TRUE;
}

#endif  // endof "#if DEVICE_RTC"
