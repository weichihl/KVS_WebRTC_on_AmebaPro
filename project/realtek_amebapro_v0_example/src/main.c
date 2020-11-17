#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include <example_entry.h>
#include "platform_autoconf.h"

extern void console_init(void);

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
void main(void)
{
	/* Initialize log uart and at command service */
#if WINBOND_FLASH_UNPROTECT
        extern void flash_unprotect_winbond(void);
        flash_unprotect_winbond();
#endif
        console_init();	
#if ISP_BOOT_MODE_ENABLE == 0
	/* pre-processor of application example */
	pre_example_entry();

	/* wlan intialization */
#if defined(CONFIG_WIFI_NORMAL) && defined(CONFIG_NETWORK)
	wlan_network();
#endif
#endif
	/* Execute application example */
	example_entry();

    	/*Enable Schedule, Start Kernel*/
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
	#ifdef PLATFORM_FREERTOS
	vTaskStartScheduler();
	#endif
#endif
	
	while(1);
}
