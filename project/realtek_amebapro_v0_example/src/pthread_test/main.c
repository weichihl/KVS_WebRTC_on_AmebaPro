#include "FreeRTOS.h"
#include "task.h"
#include "diag.h"
#include "main.h"
#include <example_entry.h>
#include "platform_autoconf.h"
#include "FreeRTOS_POSIX.h"

extern void console_init(void);

//pthread test
extern int hello(void);
extern int hello_arg1(void);
extern int hello_arg2(void);
extern int join (void);
extern int stack_mgr(void);
extern int dotprod_mutex (void);
extern int condvar(void);

   
void test_thread(void *param) {
  
     //pthread test
	  printf("****start pthread test****\r\n");
	  printf("--pthread hello example begin--\r\n");
      hello();
	  vTaskDelay(1000);
	  printf("--pthread hello example end--\r\n");
	  printf("--pthread hello arg1 example begin--\r\n");
      hello_arg1();
	  vTaskDelay(1000);
	  printf("--pthread hello arg1 example end--\r\n");
	  printf("--pthread hello arg2 example begin--\r\n");
      hello_arg2();
	  vTaskDelay(1000);
	  printf("--pthread hello arg2 example end--\r\n");
	  printf("--pthread join example begin--\r\n");
      join();
	  vTaskDelay(2000);
	  printf("--pthread join example end--\r\n");
	  printf("--pthread stack_mgr example begin--\r\n");
      stack_mgr();
	  vTaskDelay(2000);
	  printf("--pthread stack_mgr example end--\r\n");
	  printf("--pthread dotprod_mutex example begin--\r\n");
      dotprod_mutex();
	  vTaskDelay(3000);
	  printf("--pthread dotprod_mutex example end--\r\n");
	  printf("--pthread condvar example begin--\r\n");
      condvar();
	  vTaskDelay(5000);
	  printf("--pthread condvar example end--\r\n");
	  printf("****pthread test end****\r\n");

     while(1)
     {
         vTaskDelay(1000);
     }
}

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
	//wlan_network();
#endif
#endif
	/* Execute application example */
        
	if(xTaskCreate(test_thread, ((const char*)"test_thread"), 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
		printf("\r\n test_thread: Create Task Error\n");
	}       

    /*Enable Schedule, Start Kernel*/
#if defined(CONFIG_KERNEL) && !TASK_SCHEDULER_DISABLED
	#ifdef PLATFORM_FREERTOS
	vTaskStartScheduler();
	#endif
#endif
	
	while(1);
}
