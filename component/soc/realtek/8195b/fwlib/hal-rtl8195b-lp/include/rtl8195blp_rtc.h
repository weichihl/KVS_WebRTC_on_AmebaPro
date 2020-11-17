 /**************************************************************************//**
  * @file     rtl8195blp_rtc.h
  * @brief    The HAL related definition and macros for the RTC device.
  *           Includes Registers and data type definition.
  * @version  V1.00
  * @date     2016-06-14
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

#ifndef _RTL8195BLP_RTC_H_
#define _RTL8195BLP_RTC_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup ls_hal_rtc RTC
 * @{
 */

/**
  * \brief The RTC register parameter
**/

enum  rtc_reg_sel_e {
    Rtc_Fen       = 0x00,   //!< REG_RTC_FEN
    Rtc_Cmp       = 0x08,   //!< REG_RTC_CMP
    Rtc_Imr       = 0x10,   //!< REG_RTC_IMR
    Rtc_Isr       = 0x14,   //!< REG_RTC_ISR
    Rtc_Tim0      = 0x20,   //!< REG_RTC_TIM0
    Rtc_Tim1      = 0x24,   //!< REG_RTC_TIM1
    Rtc_Tim2      = 0x28,   //!< REG_RTC_TIM2
    Rtc_Ctrl0     = 0x30,   //!< REG_RTC_ALRM_CTRL0
    Rtc_Ctrl1     = 0x34,   //!< REG_RTC_ALRM_CTRL1
    Rtc_Ctrl2     = 0x38    //!< REG_RTC_ALRM_CTRL2

};
typedef uint8_t rtc_reg_sel_t;

/**
  * \brief The RTC wake-up register parameter
**/

enum  rtc_wake_event_e {
    RTC_Wake     = 0x04,            //!< 1: enable RTC wake, BIT2
    RTC_Rst      = (0x20000UL),     //!< 1: enable RTC RST, BIT17
    AON_Wakeup   = (0x20000000UL)   //!< 1: enable AON Wakeup event, BIT29

};
typedef uint32_t rtc_wake_event_t;

/*! define RTC interrupt call back function */
typedef void (*rtc_alarm_callback_t) (void *);

/**
  * \brief The tm structure with the time information filled in.
**/

typedef struct hal_tm_reg_s {
    int sec;         //!< seconds,  range 0 to 59
    int min;         //!< minutes, range 0 to 59
    int hour;        //!< hours, range 0 to 23
    int mday;        //!< day of the month, range 1 to 31
    int mon;         //!< month, range 0 to 11
    int year;        //!< The number of years since 1900
    int wday;        //!< day of the week, range 0 to 6
    int yday;        //!< day in the year, range 0 to 365
    int isdst;       //!< daylight saving time
} hal_tm_reg_t, *phal_tm_reg_t;

/**
  * \brief The RTC alarm structure
**/

typedef struct hal_rtc_alarm_s {
	uint32_t yday;   //!< day in the year, range 1 to 366
	uint32_t hour;   //!< hours, range 0 to 23
	uint32_t min;    //!< minutes, range 0 to 59
	uint32_t sec;    //!< seconds,  range 0 to 59
}hal_rtc_alarm_t, *phal_rtc_alarm_t;

/**
  * \brief The Real Time Clock (RTC) data structure
**/

typedef struct hal_rtc_reg_s{                                /*!< (@ 0x00000000) RTC Structure                                              */

  union {
    __IOM uint32_t rtc_fen;                          /*!< (@ 0x00000000) REG_RTC_FEN                                 */

    struct {
        __IOM uint32_t rtc_en              : 1;           /*!< [0..0], 1:Enable RTC; 0:Disable RTC                               */
        __IOM uint32_t ckdiv_en            : 1;           /*!< [1..1], 1:Enable RTC CLK divider                              */

        __IM  uint32_t                     : 2;
        __IOM uint32_t ckdiv_mod_sel       : 1;           /*!< [4..4], 0: Normal mode 1024 for 1s; 1: test mode 64 for 1s                            */

    } fen_b;
  } ;

  union {
    __IOM uint32_t rtc_cmp;                          /*!< (@ 0x00000004) REG_RTC_CMP                   */

    struct {
        __IOM uint32_t rtc_adjust_period_sel: 18;          /*!< [0..17], unit: s                               */
        __IOM uint32_t adjust_direction     : 1;           /*!< [18..18], 0: plus, 1 mimus                  */

        __IM  uint32_t                      : 12;
        __IOM uint32_t function_en          : 1;           /*!< [31..31], 0: Func disable; 1: Func Enable     */

    } cmp_b;
  } ;

  union {
    __IOM uint32_t rtc_imr;                          /*!< (@ 0x00000008) REG_RTC_IMR                                 */

    struct {
        __IOM uint32_t cnt_sec_imr          : 1;           /*!< [0..0], 1:cnt_sec_imr                              */
        __IOM uint32_t cnt_min_imr          : 1;           /*!< [1..1], 1:cnt_min_imr                              */
        __IOM uint32_t cnt_hrs_imr          : 1;           /*!< [2..2], 1:cnt_hrs_imr                              */
        __IOM uint32_t cnt_dow_imr          : 1;           /*!< [3..3], 1:cnt_dow_imr                             */
        __IOM uint32_t cnt_dom_imr          : 1;           /*!< [4..4], 1:cnt_dom_imr                             */
        __IOM uint32_t cnt_mth_imr          : 1;           /*!< [5..5], 1:cnt_mth_imr                              */
        __IOM uint32_t cnt_yrs_imr          : 1;           /*!< [6..6], 1:cnt_yrs_imr                               */
        __IOM uint32_t cnt_doy_imr          : 1;           /*!< [7..7], 1:cnt_doy_imr                              */
        __IOM uint32_t alrm_sec_imr         : 1;           /*!< [8..8], 1:alrm_sec_imr                              */
        __IOM uint32_t alrm_min_imr         : 1;           /*!< [9.9], 1:alrm_min_imr                              */
        __IOM uint32_t alrm_hrs_imr         : 1;           /*!< 10..10], 1:alrm_hrs_imr                               */
        __IOM uint32_t alrm_dow_imr         : 1;           /*!< [11..11], 1:alrm_dow_imr                             */
        __IOM uint32_t alrm_dom_imr         : 1;           /*!< [12..12], 1:alrm_dom_imr                              */
        __IOM uint32_t alrm_mth_imr         : 1;           /*!< [13..13], 1:alrm_mth_imr                             */
        __IOM uint32_t alrm_yrs_imr         : 1;           /*!< [14..14], 1:alrm_yrs_imr                               */
        __IOM uint32_t alrm_doy_imr         : 1;           /*!< [15..15], 1:alrm_doy_imr                              */
        __IOM uint32_t alrm_imr             : 1;           /*!< [16..16], 1:alrm_imr                               */


    } imr_b;
 } ;

 union {
   __IOM uint32_t rtc_isr;                          /*!< (@ 0x0000000C) REG_RTC_ISR                                 */

   struct {
       __IOM uint32_t cnt_sec_isr          : 1;           /*!< [0..0], 1:cnt_sec_isr                              */
       __IOM uint32_t cnt_min_isr          : 1;           /*!< [1..1], 1:cnt_min_isr                              */
       __IOM uint32_t cnt_hrs_isr          : 1;           /*!< [2..2], 1:cnt_hrs_isr                              */
       __IOM uint32_t cnt_dow_isr          : 1;           /*!< [3..3], 1:cnt_dow_isr                             */
       __IOM uint32_t cnt_dom_isr          : 1;           /*!< [4..4], 1:cnt_dom_isr                             */
       __IOM uint32_t cnt_mth_isr          : 1;           /*!< [5..5], 1:cnt_mth_isr                              */
       __IOM uint32_t cnt_yrs_isr          : 1;           /*!< [6..6], 1:cnt_yrs_isr                               */
       __IOM uint32_t cnt_doy_isr          : 1;           /*!< [7..7], 1:cnt_doy_isr                              */
       __IOM uint32_t alrm_sec_isr         : 1;           /*!< [8..8], 1:alrm_sec_isr                              */
       __IOM uint32_t alrm_min_isr         : 1;           /*!< [9.9], 1:alrm_min_isr                              */
       __IOM uint32_t alrm_hrs_isr         : 1;           /*!< 10..10], 1:alrm_hrs_isr                               */
       __IOM uint32_t alrm_dow_isr         : 1;           /*!< [11..11], 1:alrm_dow_isr                             */
       __IOM uint32_t alrm_dom_isr         : 1;           /*!< [12..12], 1:alrm_dom_isr                              */
       __IOM uint32_t alrm_mth_isr         : 1;           /*!< [13..13], 1:alrm_mth_isr                             */
       __IOM uint32_t alrm_yrs_isr         : 1;           /*!< [14..14], 1:alrm_yrs_isr                               */
       __IOM uint32_t alrm_doy_isr         : 1;           /*!< [15..15], 1:alrm_doy_isr                              */
       __IOM uint32_t alrm_isr             : 1;           /*!< [16..16], 1:alrm_isr                               */


  } isr_b;
 } ;

  union {
   __IOM uint32_t rtc_tim0;                          /*!< (@ 0x000000010) REG_RTC_TIM0                                 */

   struct {
       __IOM uint32_t rtc_sec              : 6;           /*!< [0..5], Seconds value in the range of 0 to 59       */

       __IM  uint32_t                      : 2;           /*!< [6..7],                            */
       __IOM uint32_t rtc_min              : 6;           /*!< [8..13], Minutes value in the range of 0 to 59                              */

       __IM  uint32_t                      : 2;           /*!< [14..15],                             */
       __IOM uint32_t rtc_hrs              : 5;           /*!< [16..20], Hours value in the range of 0 to 23                           */

       __IM  uint32_t                      : 3;           /*!< [21..23],                              */
       __IOM uint32_t rtc_dow              : 3;           /*!< [24..26], Day of week value in the range of 0 to 6                             */

  } tim0_b;
 } ;


  union {
  __IOM uint32_t rtc_tim1;                          /*!< (@ 0x00000014) REG_RTC_TIM1                                 */

  struct {
      __IOM uint32_t rtc_dom              : 5;           /*!< [0..4], Day of month value in the range of 1 to 28, 29, 30, or 31       */

      __IM  uint32_t                      : 3;           /*!< [5..7],                            */
      __IOM uint32_t rtc_mon              : 4;           /*!< [8..11], Month value in the range of 1 to 12                             */

      __IM  uint32_t                      : 4;           /*!< [12..15],                             */
      __IOM uint32_t rtc_year             : 12;          /*!< [16..27], Year value in the range of 0 to 4095.                       */

  } tim1_b;
 } ;



  union {
  __IOM uint32_t rtc_tim2;                          /*!< (@ 0x00000018) REG_RTC_TIM2                                 */

  struct {
      __IOM uint32_t rtc_doy              : 9;           /*!< [0..8], Day of year, value in the range of 1 to 365       */

      __IM  uint32_t                      : 7;           /*!< [9..15],                            */
      __IOM uint32_t rtc_m4iscyr          : 1;           /*!< [16..16], 0: Leap year                           */

  } tim2_b;
 } ;


  union {
   __IOM uint32_t rtc_alrm_ctr0;                          /*!< (@ 0x0000001C) REG_RTC_ALRM_CTRL0                                 */

   struct {
       __IOM uint32_t rtc_alrm_sec        : 6;           /*!< [0..5], Seconds value in the range of 0 to 59      */

       __IM  uint32_t                     : 2;           /*!< [6..7],                            */
       __IOM uint32_t rtc_alrm_min        : 6;           /*!< [8..13], Minutes value in the range of 0 to 59                              */

       __IM  uint32_t                     : 2;           /*!< [14..15],                             */
       __IOM uint32_t rtc_alrm_hrs        : 5;           /*!< [16..20], Hours value in the range of 0 to 23                           */

       __IM  uint32_t                     : 3;           /*!< [21..23],                              */
       __IOM uint32_t rtc_alrm_dow        : 3;           /*!< [24..26], Day of week value in the range of 0 to 6                             */

  } ctr0_b;
 } ;

 union {
  __IOM uint32_t rtc_alrm_ctr1;                          /*!< (@ 0x00000020) REG_RTC_ALRM_CTRL1                                 */

  struct {
      __IOM uint32_t rtc_alrm_dom         : 5;           /*!< [0..4], Day of month value in the range of 1 to 28, 29, 30, or 31       */

      __IM  uint32_t                      : 3;           /*!< [5..7],                            */
      __IOM uint32_t rtc_alrm_mon         : 4;           /*!< [8..11], Month value in the range of 1 to 12                             */

      __IM  uint32_t                      : 4;           /*!< [12..15],                             */
      __IOM uint32_t rtc_alrm_year        : 12;          /*!< [16..27], Year value in the range of 0 to 4095.                       */

  } ctr1_b;
 } ;

 union {
  __IOM uint32_t rtc_alrm_ctr2;                          /*!< (@ 0x00000024) REG_RTC_ALRM_CTRL2                                 */

  struct {
      __IOM uint32_t rtc_alrm_doy          : 9;           /*!< [0..8], Day of year, value in the range of 1 to 365       */

      __IM  uint32_t                       : 7;
      __IOM uint32_t rtc_alrm_sec_en       : 1;           /*!< [16..16], 1: Enable Second timer value match alrm_sec        */
      __IOM uint32_t rtc_alrm_min_en       : 1;           /*!< [17..17], 1: Enable Minute timer value match alrm_min        */
      __IOM uint32_t rtc_alrm_hrs_en       : 1;           /*!< [18..18], 1: Enable Hour timer value match alrm_hrs        */
      __IOM uint32_t rtc_alrm_dow_en       : 1;           /*!< [19..19], 1: Enable DOW timer value match alrm_dow        */
      __IOM uint32_t rtc_alrm_dom_en       : 1;           /*!< [20..20], 1: Enable DOM timer value match alrm_dom        */
      __IOM uint32_t rtc_alrm_mth_en       : 1;           /*!< [21..21], 1: Enable MTH timer value match alrm_mth        */
      __IOM uint32_t rtc_alrm_yrs_en       : 1;           /*!< [22..22], 1: Enable Year timer value match alrm_yrs        */
      __IOM uint32_t rtc_alrm_doy_en       : 1;           /*!< [23..23], 1: Enable DOY timer value match alrm_doy        */

  } ctr2_b;
 } ;
} hal_rtc_reg_t, *phal_rtc_reg_t;

/**
  \brief  The data structure of the RTC adapter
*/
typedef struct hal_rtc_adapter_s {
    RTC_Type *base_addr;    //!< The RTC registers base address
    hal_rtc_reg_t rtc_reg;  //!< The data structure to control the RTC register.
    rtc_alarm_callback_t  alarm_callback;      //!< User callback function for RTC Alarm
    void *rtc_cb_para;   //!< the argument for RTC callback function
} hal_rtc_adapter_t, *phal_rtc_adapter_t;


/**
  \brief  The data structure of the stubs function for the RTC HAL functions in ROM
*/
typedef struct hal_rtc_func_stubs_s {
    phal_rtc_adapter_t *prtc_adp;
    void (*hal_rtc_irq_handler) (void);
    void (*hal_rtc_comm_irq_reg) (irq_handler_t irq_handler);
    void (*hal_rtc_comm_irq_unreg) (void);
    hal_status_t (*hal_rtc_init) (hal_rtc_adapter_t *prtc_adp);
    hal_status_t (*hal_rtc_deinit) (hal_rtc_adapter_t *prtc_adp);
    void (*hal_rtc_enable) (hal_rtc_adapter_t *prtc_adp);
    void (*hal_rtc_disable) (hal_rtc_adapter_t *prtc_adp);
    //int  (*hal_rtc_isenable) (hal_rtc_adapter_t *prtc_adp);
    void (*hal_rtc_wait_ctrl_ready) (hal_rtc_adapter_t *prtc_adp);
    void (*hal_rtc_write) (hal_rtc_adapter_t *prtc_adp, u16 addr, u32 data);
    u32 (*hal_rtc_read) (hal_rtc_adapter_t *prtc_adp, u16 addr);
    hal_status_t (*hal_rtc_set_time) (hal_rtc_adapter_t *prtc_adp, hal_tm_reg_t *ptm_reg, u16 leap_year);
    u32 (*hal_rtc_read_time) (hal_rtc_adapter_t *prtc_adp);
    hal_status_t (*hal_rtc_set_alarm) (hal_rtc_adapter_t *prtc_adp, hal_rtc_alarm_t *prtc_alarm);
    u32 (*hal_rtc_read_alarm) (hal_rtc_adapter_t *prtc_adp);
    void (*hal_rtc_reg_alarm_irq) (hal_rtc_adapter_t *prtc_adp, rtc_alarm_callback_t callback, void *arg);
    void (*hal_rtc_unreg_alarm_irq) (hal_rtc_adapter_t *prtc_adp);
    hal_status_t (*hal_rtc_set_cnt_alarm)  (hal_rtc_adapter_t *prtc_adp, u8 cnt_alarm);
    hal_status_t (*hal_rtc_set_comp) (hal_rtc_adapter_t *prtc_adp, u8 func_en);
    uint32_t reserved[3];  // reserved space for next ROM code version function table extending.
}hal_rtc_func_stubs_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup ls_hal_rtc_rom_func RTC HAL ROM APIs.
 * @{
 */

void hal_rtc_comm_irq_reg_rtl8195blp (irq_handler_t irq_handler);
void hal_rtc_comm_irq_unreg_rtl8195blp (void);
hal_status_t hal_rtc_init_rtl8195blp (hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtc_deinit_rtl8195blp (hal_rtc_adapter_t *prtc_adp);
void hal_rtc_enable_rtl8195blp (hal_rtc_adapter_t *prtc_adp);
void hal_rtc_disable_rtl8195blp (hal_rtc_adapter_t *prtc_adp);
//int hal_rtc_isenable_rtl8195blp (hal_rtc_adapter_t *prtc_adp);
void hal_rtc_wait_ctrl_ready_rtl8195blp (hal_rtc_adapter_t *prtc_adp);
void hal_rtc_write_rtl8195blp (hal_rtc_adapter_t *prtc_adp, u16 addr, u32 data);
u32 hal_rtc_read_rtl8195blp (hal_rtc_adapter_t *prtc_adp, u16 addr);
hal_status_t hal_rtc_set_time_rtl8195blp (hal_rtc_adapter_t *prtc_adp, hal_tm_reg_t *ptm_reg, u16 leap_year);
u32 hal_rtc_read_time_rtl8195blp (hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtc_set_alarm_rtl8195blp (hal_rtc_adapter_t *prtc_adp, hal_rtc_alarm_t *prtc_alarm);
u32 hal_rtc_read_alarm_rtl8195blp (hal_rtc_adapter_t *prtc_adp);
void hal_rtc_reg_alarm_irq_rtl8195blp (hal_rtc_adapter_t *prtc_adp, rtc_alarm_callback_t callback, void *arg);
void hal_rtc_unreg_alarm_irq_rtl8195blp (hal_rtc_adapter_t *prtc_adp);
hal_status_t hal_rtc_set_cnt_alarm_rtl8195blp  (hal_rtc_adapter_t *prtc_adp, u8 cnt_alarm);
hal_status_t hal_rtc_set_comp_rtl8195blp (hal_rtc_adapter_t *prtc_adp, u8 func_en);

/** @} */ /* End of group ls_hal_rtc_rom_func */

/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

#ifdef  __cplusplus
}
#endif

/** @} */ /* End of group ls_hal_rtc */

#endif  // end of "#define _RTL8195BLP_RTC_H_"
