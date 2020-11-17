#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include <example_entry.h>
#include "platform_autoconf.h"
#include "doorbell_demo.h"
#include "app_setting.h"

extern void console_init(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

void main(void)
{
	/* Initialize log uart and at command service */
        console_init();
	
#if USE_WOWLAN  
	uint8_t wowlan_wake_reason = rtl8195b_wowlan_wake_reason();
	if (wowlan_wake_reason != 0) {
	    printf("\r\nwake fom wlan: 0x%02X\r\n", wowlan_wake_reason);
	}
	else
	{
	    wifi_off();
	}
#endif 
	
#if ISP_BOOT_MODE_ENABLE == 0
	/* pre-processor of application example */
	pre_example_entry(); 

	/* wlan intialization */
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
	wlan_network();
#endif
#endif

	/* Execute application*/
        doorbell_init_function(NULL); 

    	/*Enable Schedule, Start Kernel*/
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
	#ifdef PLATFORM_FREERTOS
	vTaskStartScheduler();
	#endif
#else
	RtlConsolTaskRom(NULL);
#endif
}
