 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/
#include "platform_stdlib.h"
#include "ff.h"
#include <fatfs_ext/inc/ff_driver.h>
#include "sdio_combine.h"
#include "sdio_host.h"
#include <disk_if/inc/sdcard.h>
#include "fatfs_sdcard_api.h"
#include "gpio_api.h"

#include "icc_api.h"
#include "sys_api_ext.h"
#include "hal_power_mode.h"
#include "power_mode_api.h"
#include "wifi_conf.h"

#include "gpio_irq_api.h"   // mbed

#if CONFIG_EXAMPLE_SD_HOT_PLUG

//#define USE_GPIO_DETECT
#define USE_SD_DETECT

#define ICC_CMD_REQ_STANDBY                     (0x20)
#define ICC_CMD_REQ_STANDBY_STIMER_DURATION     (0x21)

static fatfs_sd_params_t fatfs_sd;
extern phal_sdio_host_adapter_t psdioh_adapter;

#define QFN_128_SD_POWER_PIN    PE_12
#define DEMO_Board_SD_POWER_PIN PH_0
#define SD_CARD_CD_PIN PB_6

#define USE_DEMO_BOARD
#define ENABLE_SD_POWER_RESET
#define SD_POWER_RESET_DELAY_TIME 200

static gpio_t gpio_sd_power;

static void *sd_sema = NULL;
static uint8_t sd_checking = 0;
    
#define SD_CARD_DETECT_TYPE     1
#define GPIO_CARD_DETECT_TYPE   0
static int card_detect_type = GPIO_CARD_DETECT_TYPE;  

//#define SD_REST_TEST_STANDBY_MODE  //We need to use ls power save example code to trigger the standby mode

void sd_gpio_init(void)
{
#ifdef USE_DEMO_BOARD
        gpio_init(&gpio_sd_power, DEMO_Board_SD_POWER_PIN);
#else
        gpio_init(&gpio_sd_power, QFN_128_SD_POWER_PIN);
#endif
        gpio_dir(&gpio_sd_power, PIN_OUTPUT);    // Direction: Output
        gpio_mode(&gpio_sd_power, PullNone);     // No pull
        gpio_write(&gpio_sd_power, 0);
}
void sd_gpio_power_reset(void)
{
        int i = 0;
        gpio_write(&gpio_sd_power, 1);
        vTaskDelay(SD_POWER_RESET_DELAY_TIME);//The time is depend on drop speed oof your gpio, or we can read the gpio status
        gpio_write(&gpio_sd_power, 0);
}

void sd_gpio_power_off(void)
{
        gpio_write(&gpio_sd_power, 1);
        vTaskDelay(SD_POWER_RESET_DELAY_TIME);//The time is depend on drop speed oof your gpio, or we can read the gpio status
}

void sd_gpio_power_on(void)
{
        gpio_write(&gpio_sd_power, 0);
        vTaskDelay(SD_POWER_RESET_DELAY_TIME);//The time is depend on drop speed oof your gpio, or we can read the gpio status
}


static gpio_irq_t gpio_sd_detect_irq = NULL;

void gpio_demo_irq_handler (uint32_t id, gpio_irq_event event)
{
    gpio_t *gpio_led;
    card_detect_type = GPIO_CARD_DETECT_TYPE; 
    gpio_led = (gpio_t *)id;
    
    printf("SD CARD DETECT = %d\r\n",gpio_read(gpio_led));
    
    if(!sd_checking){
          if(sd_sema)
                  rtw_up_sema_from_isr(&sd_sema);
    }
}

void sd_card_detect_init(void)
{
    gpio_irq_init(&gpio_sd_detect_irq, SD_CARD_CD_PIN, gpio_demo_irq_handler, (uint32_t)(&gpio_sd_detect_irq));
    gpio_irq_set(&gpio_sd_detect_irq, IRQ_FALL, 1);   // Falling Edge Trigger
    gpio_irq_enable(&gpio_sd_detect_irq);
}

int sd_card_dc_status(void)
{

        int value = 0;
        
        value = hal_gpio_irq_read(&gpio_sd_detect_irq.gpio_irq_adp);
		printf("card detect status = %d\r\n",value);
        if(value == 0)
			return 1;
		else
			return 0;
}
int sd_gpio_detect_disable()
{
    printf("disalbe sd gpio detect\r\n");
    gpio_irq_free(&gpio_sd_detect_irq);
}


void sdh_card_insert_callback(void *pdata)
{
        printf("[In]\r\n");
        card_detect_type = SD_CARD_DETECT_TYPE; 
        for(int i =0;i<50000;i++){
                asm("nop");
        }
        if(!sd_checking){
          if(sd_sema)
                rtw_up_sema_from_isr(&sd_sema);
        }

}
void sdh_card_remove_callback(void *pdata)
{
        printf("[Out]\r\n");
        card_detect_type = SD_CARD_DETECT_TYPE;
        for(int i =0;i<50000;i++){
                asm("nop");
        }
        if(!sd_checking){
          if(sd_sema)
                  rtw_up_sema_from_isr(&sd_sema);
        }
}

int sd_do_mount(void *parm)
{
      int i = 0;
      int res = 0;
#ifdef ENABLE_SD_POWER_RESET
      sd_gpio_power_reset();
#endif
      res = f_mount(NULL, fatfs_sd.drv, 1);
      if(res)
            printf("UMount failed %d\r\n",res);
      else
            printf("UMount Successful\r\n");
      for(int i =0;i<50000;i++){
              asm("nop");
      }
      res = f_mount(&fatfs_sd.fs, fatfs_sd.drv, 1);
      if(res)
            printf("Mount failed %d\r\n",res);
      else
            printf("Mount Successful\r\n");
      return res;
}

int sd_do_unmount(void *parm)
{
      int res = 0;
      res = f_mount(NULL, fatfs_sd.drv, 1);
      if(res)
            printf("UMount failed %d\r\n",res);
      else
            printf("UMount Successful\r\n");

      return res;
}

void sd_enter_standby_sleep_mode()
{
    wifi_off();
    uint16_t wakeup_event = BIT0; // default BIT0 for DS_STIMER
    icc_user_cmd_t cmd = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY_STIMER_DURATION, .cmd_b.para0 = 1 };
    icc_cmd_send (cmd.cmd_w, 0, 1000, NULL); // icc timeout 1000us
    wakeup_event |= BIT0; // DS_STIMER
    
    icc_user_cmd_t cmd_s = { .cmd_b.cmd = ICC_CMD_REQ_STANDBY, .cmd_b.para0 = wakeup_event }; // BIT0 for DSTBY_STIMER
    icc_cmd_send (cmd_s.cmd_w, 0, 1000, NULL); // icc timeout 1000us
    printf("Enter standby mode\r\n");
    while(1)
      vTaskDelay(1000);
}

static void sd_hot_plug_thread(void *param)
{
        int res = 0;
        sd_card_detect_init();
        
        //DBG_INFO_MSG_ON(_DBG_SDIO_HOST_);
        //DBG_WARN_MSG_ON(_DBG_SDIO_HOST_);
#ifdef SD_REST_TEST_STANDBY_MODE
        icc_init();
#endif
        
        #ifdef ENABLE_SD_POWER_RESET
        sd_gpio_power_reset();
        #endif
        sd_gpio_init();
        sdio_driver_init();
        sdio_set_init_retry_time(2);
        
        fatfs_sd.drv_num = FATFS_RegisterDiskDriver(&SD_disk_Driver);
  
        if(fatfs_sd.drv_num < 0){
                printf("Rigester disk driver to FATFS fail.\n\r");
        }else{
                fatfs_sd.drv[0] = fatfs_sd.drv_num + '0';
                fatfs_sd.drv[1] = ':';
                fatfs_sd.drv[2] = '/';
                fatfs_sd.drv[3] = 0;
        }
        if(sd_card_dc_status()){
                sd_gpio_detect_disable();
                res = f_mount(&fatfs_sd.fs, fatfs_sd.drv, 1);
                if(res)
                        printf("Mount failed %d\r\n",res);
                else
                        printf("Mount Successful\r\n");
        }
#ifdef SD_REST_TEST_STANDBY_MODE
        if(res){
            printf("Mount failed\r\n");
            while(1){
              vTaskDelay(1000);
            }
        }
       sd_enter_standby_sleep_mode();         
#endif       
        rtw_init_sema(&sd_sema, 0);
#ifdef USE_SD_DETECT
        while(1) {
		rtw_down_sema(&sd_sema);
		sd_checking = 1;
		vTaskDelay(200);	// delay to get correct sd voltage

		SDIO_HOST_Type *psdioh = SDIO_HOST;
		if(psdioh->card_exist_b.sd_exist) {
			printf("card inserted!\n");
                        res = sd_do_mount(NULL);
                        if(res)//Try again for fast hot plug
                          sd_do_mount(NULL);
		}
		else {
			printf("card OUT!\r\n");
                        if(psdioh->card_exist_b.sd_exist) {
                          sd_do_mount(NULL);
                        }
		}
		sd_checking = 0;
        }
#else
        while(1) {
		rtw_down_sema(&sd_sema);
		sd_checking = 1;
		vTaskDelay(200);	// delay to get correct sd voltage

		SDIO_HOST_Type *psdioh = SDIO_HOST;
                

                if(card_detect_type == GPIO_CARD_DETECT_TYPE){
                    printf("GPIO_CARD_DETECT_TYPE\r\n");
                    if(sd_card_dc_status()){
                      sd_gpio_detect_disable();
                      printf("card inserted!\n");
                        res = sd_do_mount(NULL);
                        if(res)//Try again for fast hot plug
                          sd_do_mount(NULL);
                    }
                }else{
                    printf("SD_CARD_DETECT_TYPE\r\n");
                    if(psdioh->card_exist_b.sd_exist) {
                            printf("card inserted!\n");
                            res = sd_do_mount(NULL);
                            if(res)//Try again for fast hot plug
                              sd_do_mount(NULL);
                            if(!psdioh->card_exist_b.sd_exist) {
                              sd_do_unmount(NULL);
                              sd_card_detect_init();
                            }else{
                              if(res){
                                sd_do_unmount(NULL);
                                sd_card_detect_init();
                              }
                            }
                    }
                    else {
                            printf("card OUT!\r\n");
                            if(psdioh->card_exist_b.sd_exist) {
                              res = sd_do_mount(NULL);
                              if(!psdioh->card_exist_b.sd_exist) {
                                sd_do_unmount(NULL);
                                sd_card_detect_init();
                              }
                            }else{
                              sd_do_unmount(NULL);
                              sd_card_detect_init();
                            }
                    }
                }
		sd_checking = 0;
	}
#endif
fail:
        vTaskDelete(NULL);
}


void example_sd_hot_plug(void)
{
	if(xTaskCreate(sd_hot_plug_thread, ((const char*)"sd_hot_plug"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(sd_hot_plug) failed", __FUNCTION__);
}
#endif