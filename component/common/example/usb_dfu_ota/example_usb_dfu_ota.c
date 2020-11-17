#include "FreeRTOS.h"
#include "task.h"
#include <platform/platform_stdlib.h>
#include "basic_types.h"
#include "platform_opts.h"

#include "usb.h"
#include "dfu/inc/usbd_dfu.h"

void example_usb_dfu_ota_thread(void* param){
	int status = 0;

	_usb_init();
	status = wait_usb_ready();
	if(status != USB_INIT_OK){
		if(status == USB_NOT_ATTACHED)
			printf("\r\n NO USB device attached\n");
		else
			printf("\r\n USB init fail\n");
		goto exit;
	}
        status = usbd_dfu_init();
	if(status){
		printf("USB DFU driver load fail.\n");
	}else{
		printf("USB DFU driver load done, Available heap [0x%x]\n", xPortGetFreeHeapSize());
	}
exit:
	vTaskDelete(NULL);
}


void example_usb_dfu_ota(void)
{
	if(xTaskCreate(example_usb_dfu_ota_thread, ((const char*)"example_usb_dfu_ota_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
		printf("\n\r%s xTaskCreate(example_usb_dfu_ota_thread) failed", __FUNCTION__);
}