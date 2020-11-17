#ifndef APP_SETTING_H
#define APP_SETTING_H

#include "basic_types.h"

//#define DOORBELL_TARGET_BROAD
//#define QFN_128_BOARD
/* --------- LS Setting --------- */
#define USE_PIR_SENSOR     1
#define USE_PROXIMITY      0
#define USE_BLUETOOTH      0
#define USE_WLAN           0
#define USE_BATTERY_DETECT 0
#define USE_TIMER          0
#define USE_PUSH_BUTTON    1
#define USE_RESET_BUTTON   0
#ifdef DOORBELL_TARGET_BROAD
#define USE_WOWLAN         0
#else
#define USE_WOWLAN         1
#endif


/* --------- HS Setting --------- */
#define USE_LIGHT_SENSOR   0
#define USE_MCU430         0
#define USE_IR_LED         0
#define USE_BUZZER         0


/* --------- Power save mode ---- */
#ifdef DOORBELL_TARGET_BROAD
#define POWER_SAVE_MODE    0 //0:deepsleep, 1:standby, 2:sleepPG
#else
#define POWER_SAVE_MODE    1 //0:deepsleep, 1:standby, 2:sleepPG
#endif

/* --------- ICC command --------*/
#define ICC_CMD_SHORT    0x10 //RING
#define ICC_CMD_LONG     0x11 //QRCODE 
#define ICC_CMD_POWERON  0x12
#define ICC_CMD_POWEROFF 0x13
#define ICC_CMD_RTC      0x14
#define ICC_CMD_RTC_SET  0x15
#define ICC_CMD_PIR      0x16
#define ICC_CMD_BATTOFF  0x17

#define ICC_CMD_REQ_GET_LS_WAKE_REASON          (0x30)
#define ICC_CMD_NOTIFY_LS_WAKE_REASON           (0x31)


/* -------- doorbell state ------*/
#define STATE_NORMAL          0x00
#define STATE_WIFI_CONNECTED  0x01
#define STATE_SD_INSERT       0x02
#define STATE_MEDIA_READY     0x04
#define STATE_RESERVE2        0x08

#define STATE_QRCODE          0x10
#define STATE_RING            0x20
#define STATE_ARAM            0x40
#define STATE_RESERVE3        0x80

#define STATE_RECORD          0x100
#define STATE_PLAYPACK        0x200
#define STATE_NONESD          0x400
#define STATE_RESERVE5        0x800

#define RESET_TRIGGER         0x01
#define CALL_TRIGGER          0x02
#define PIR_TRIGGER           0x04
#define RF_TRIGGER            0x08

//wakeup source setting
typedef struct wakeup_source_s{
	u16 Option;
	u32 SDuration; 
	int32_t gpio_reg;
}wakeup_source_t;

typedef struct doorbell_ctr_s{
    uint32_t doorbell_state;
    uint32_t new_state;

}doorbell_ctr_t;

/* -------- PIN define ---------*/
#if USE_PIR_SENSOR
#ifdef QFN_128_BOARD
#define GPIO_SERIN PA_2
#define GPIO_DLA PA_7
#else
#define GPIO_SERIN       PA_2
#define GPIO_DLA         PA_3
#endif
#endif

#if USE_PUSH_BUTTON
#define BTN_PIN          PA_13
#endif

#if USE_BATTERY_DETECT
#define ADC_PIN          PA_4
#define ADC_THRESHOLD    0x308
#endif

#ifdef DOORBELL_TARGET_BROAD
#define DOORBELL_AMP_ENABLE	0
#else
#define DOORBELL_AMP_ENABLE	0
#endif

#define AMP_PIN PE_0

#ifdef DOORBELL_TARGET_BROAD
#define BTN_RED  PE_6
#define BTN_BLUE PE_7
#else
#define BTN_RED  PC_9
#define BTN_BLUE PC_8
#endif

/* ------- application define ----*/

#define SNAPSHOT_DIR     "PHOTO"
#define MP4_DIR          "VIDEO"

#endif //APP_SETTING_H