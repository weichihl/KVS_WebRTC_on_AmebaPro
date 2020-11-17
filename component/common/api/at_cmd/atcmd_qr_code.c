#include "FreeRTOS.h"
#include "semphr.h"
#include "platform_opts.h"
#include "log_service.h"

#if CONFIG_EXAMPLE_QR_CODE_SCANNER

extern SemaphoreHandle_t g_qr_code_scanner_sema;

void fATQ0(void *arg)
{
	if(g_qr_code_scanner_sema)
		xSemaphoreGive(g_qr_code_scanner_sema);
}

log_item_t at_qr_code_items[] = {
	{"ATQ0", fATQ0,}
};

void at_qr_code_init(void)
{
	log_service_add_table(at_qr_code_items, sizeof(at_qr_code_items)/sizeof(at_qr_code_items[0]));
	printf("qr code log service start\r\n");
}

log_module_init(at_qr_code_init);

#endif

