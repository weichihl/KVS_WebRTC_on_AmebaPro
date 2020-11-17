#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "gpio_api.h"   // mbed
#include "main.h"
#include <example_entry.h>
#include "platform_autoconf.h"

extern void console_init(void);

const char *test = "string in main.c";

u8 g_load_radioa_fib_table_en;
u8 g_load_radioa_no_fib_table_en;

#define GPIO_LED_PIN1       PH_0

static TimerHandle_t my_timer1;
gpio_t gpio_led1;

volatile uint32_t time2_expired=0;

void timer1_timeout_handler(void *param)
{
    gpio_write(&gpio_led1, !gpio_read(&gpio_led1));   
}

static void example_my_timer1(void *param)
{
    // Init LED control pin
    gpio_init(&gpio_led1, GPIO_LED_PIN1);
    gpio_dir(&gpio_led1, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_led1, PullNone);     // No pull

    // Create a periodical timer
   
    my_timer1 = xTimerCreate( "my timer1",   /* Text name to facilitate debugging. */
    1000/portTICK_RATE_MS, /* Tick every 1 sec */
    pdTRUE,     /* The timer will auto-reload themselves when they expire. */
    NULL,     /* In this case this is not used as the timer has its own callback. */
    timer1_timeout_handler ); /* The callback to be called when the timer expires. */

    xTimerStart(my_timer1, ( TickType_t ) 0); 
    while(1){
        
    }
}
void main(void)
{
    
    rt_printf("hello IS - %s, %x\n\r", test, malloc(100));
	/* Initialize log uart and at command service */
	console_init();	
    
	/* pre-processor of application example */
	//pre_example_entry();

	/* wlan intialization */
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
	g_load_radioa_fib_table_en = 0;
	g_load_radioa_no_fib_table_en = 1;
#if(CHIP_VER == CHIP_B_CUT)
	g_load_radioa_fib_table_en = 1;
	g_load_radioa_no_fib_table_en = 0;
#endif
	wlan_network();
#endif
    xTaskCreate(example_my_timer1, (const char *)"AAA", 512, NULL, tskIDLE_PRIORITY + 1, NULL);
	/* Execute application example */
	example_entry();

    	/*Enable Schedule, Start Kernel*/
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
	#ifdef PLATFORM_FREERTOS
	vTaskStartScheduler();
	#endif
#else
	RtlConsolTaskRom(NULL);
#endif
}
