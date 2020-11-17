#ifndef SYS_API_EXT_H
#define SYS_API_EXT_H

#include <inttypes.h>

#define LS_WAKE_EVENT_STIMER       ( 1 <<  0 )
#define LS_WAKE_EVENT_GTIMER       ( 1 <<  1 )
#define LS_WAKE_EVENT_GPIO         ( 1 <<  2 )
#define LS_WAKE_EVENT_PWM          ( 1 <<  3 )
#define LS_WAKE_EVENT_WLAN         ( 1 <<  4 )
#define LS_WAKE_EVENT_UART         ( 1 <<  5 )
#define LS_WAKE_EVENT_I2C          ( 1 <<  6 )
#define LS_WAKE_EVENT_ADC          ( 1 <<  7 )
#define LS_WAKE_EVENT_COMP         ( 1 <<  8 )
#define LS_WAKE_EVENT_SGPIO        ( 1 <<  9 )
#define LS_WAKE_EVENT_AON_GPIO     ( 1 << 10 )
#define LS_WAKE_EVENT_AON_TIMER    ( 1 << 11 )
#define LS_WAKE_EVENT_AON_RTC      ( 1 << 12 )
#define LS_WAKE_EVENT_AON_ADAPTER  ( 1 << 13 )
#define LS_WAKE_EVENT_HS           ( 1 << 14 )

#if defined (CONFIG_PLATFORM_8195BHP)

void ls_sys_reset( void );
void sys_reset( void );
void compatibility_check(void);
uint32_t sys_chip_id(void);
uint32_t CmdDumpWord(uint16_t argc, uint8_t *argv[]);
uint32_t CmdWriteWord(uint16_t argc, uint8_t *argv[]);
void wowlan_prepare_warm_boot(void );

#elif defined (CONFIG_PLATFORM_8195BLP)

/**
 *  @brief This function return if HS core is suspend or power off
 */
int hs_is_suspend(void);

/**
 *  @brief Return the wake reason
 */
uint32_t ls_get_wake_reason(void);

/**
 *  @brief The function is for clear wake reason which is persist after standby
 */
void ls_clear_wake_reason(void);

/** 
 *  @brief The function for ls standby mode.
 *         
 *  @param[in]  Option, To slect AON Timer,GPIO...etc
 *                - bit[4]: the UART Wake up event.
 *                - bit[3]: the PWM Wake up event.
 *                - bit[2]: the GPIO Wake up event.
 *                - bit[1]: the GTimer Wake up event. Not ready
 *                - bit[0]: the AON Timer Wake up event.
 *  @param[in]  SDuration, wake up after SDuration value. Uint: us
 *  @param[in]  Memsel, 1: Enable memory, 0: Disable memory.
 *  @param[in]  GpioOption, GPIOA0~A13 as a wake up trigger.
 *
 *  @returns void
 */
void LsStandby (uint16_t Option, uint64_t SDuration, uint8_t Memsel, uint8_t GpioOption);
   
void LsClearWLSLP(void);
void LsCheckWlan_wakeup(void);

#endif

#endif