#include <string.h>
#include "section_config.h"
#include "cmsis.h"
#include "hal_irq.h"
#include "sys_api_ext.h"

/**
 * @addtogroup hs_hal_misc Misc.
 * @{
 */
extern const hal_misc_func_stubs_t __rom_stubs_hal_misc;

//SECTION(".itcm.bss")
static struct wdt_patch_irq_s{
	irq_handler_t user_handler;
	void* user_handler_id;
}wdt_patch_irq;

static int swwdt_timeout;

void hal_misc_wdt_default_handler(void* id);
void hal_misc_wdt_init_patch (uint32_t time_us);
void hal_misc_wdt_reg_irq_patch (irq_handler_t handler, void *arg);
void hal_misc_init_patch(hal_misc_adapter_t *pmisc_adp);

/*
SECTION(".itcm.bss")
static hal_misc_adapter_t *pmisc_adapter;

SECTION(".itcm.text")
void nmi_irq_patch (void)
{
    VDR_Type *vendor = VDR;

    if (pmisc_adapter == NULL) {
        DBG_MISC_ERR ("No handler for NMI\r\n");
        return;
    }
    
    if (vendor->watch_dog_tmr_b.wdt_to) {
        vendor->watch_dog_tmr_b.wdt_en = 0; // disable WDT
        vendor->watch_dog_tmr_b.wdt_to = 1; // clear timeout flag
        // NMI triggered by WDT
        if (pmisc_adapter->wdt_handler != NULL) {
            (pmisc_adapter->wdt_handler)(pmisc_adapter->wdt_arg);
        } else {
            DBG_MISC_ERR ("No handler for WDT Timeout\r\n");
        }
    } else {
        if (pmisc_adapter->nmi_handler != NULL) {
            (pmisc_adapter->nmi_handler)(pmisc_adapter->nmi_arg);
        } else {
            DBG_MISC_ERR ("No handler for NMI\r\n");
        }
    }
}
*/

hal_misc_func_stubs_t hal_misc_stubs = {

    .hal_misc_init = hal_misc_init_patch,

    .hal_misc_wdt_init = hal_misc_wdt_init_patch,
    .hal_misc_wdt_reg_irq = hal_misc_wdt_reg_irq_patch,

};

void hal_misc_wdt_enable_extra_action(void)
{
	ls_sys_start_sswdt(swwdt_timeout);
}

void hal_misc_wdt_disable_extra_action(void)
{
	ls_sys_stop_sswdt();
}

void hal_misc_wdt_refresh_extra_action(void)
{
	ls_sys_refresh_sswdt();
}

_WEAK int sswdt_is_reset_lp = 1;// 0: reset HS, 1: reset System
_WEAK int bus_lock_sim = 0;
void hal_misc_wdt_reset_platform(int ena)
{
	sswdt_is_reset_lp = ena;
	ls_sys_setup_sswdt(ena);
}

void watchdog_reset_platform(int ena)
{
	hal_misc_wdt_reset_platform(ena);
}

void hal_misc_wdt_default_handler(void* id)
{
	if(bus_lock_sim)	while(1);

	// calling user registering handler
	if(wdt_patch_irq.user_handler)
		wdt_patch_irq.user_handler(wdt_patch_irq.user_handler_id);
	
	// patch before doing watchdog reset
	*(uint32_t*)0x4000020C = 0;
	// add ls core deep sleep here
	if(sswdt_is_reset_lp == 0){
		//printf("Reset HS!!\r\n");
		ls_sys_stop_sswdt();
		ls_sys_hs_reset();
	}else{
		// do watchdog reset
		//printf("Reset Platform!!\r\n");
		*(uint32_t*)0x40002800 = 0x410103FF;		
		ls_sys_reset();
	}
	
	// continue disable decoder
	*(uint32_t*)0x40000238 = 0;
	*(uint32_t*)0x40000244 = 0;
	*(uint32_t*)0x40000248 = 0;	
	*(uint32_t*)0x4000023C = 0;
	*(uint32_t*)0x40000240 = 0;	
	while(1);
}

void hal_misc_wdt_init_patch (uint32_t time_us)
{
	__rom_stubs_hal_misc.hal_misc_wdt_init(time_us);
	__rom_stubs_hal_misc.hal_misc_wdt_reg_irq(hal_misc_wdt_default_handler, 0);
	
	wdt_patch_irq.user_handler = NULL;
	wdt_patch_irq.user_handler_id = 0;
	// at least 100 ms, reduce LS effort
	int time_ms = ((time_us+999)/1000)+10;
	if(time_ms < 100) time_ms = 100;	
	//ls_sys_start_sswdt(time_ms);
	swwdt_timeout = time_ms;
	
	// stop previous timer
	ls_sys_stop_sswdt();
}

void hal_misc_wdt_reg_irq_patch (irq_handler_t handler, void *arg)
{
	//printf("User IRQ reg\n\r");
	wdt_patch_irq.user_handler = handler;
	wdt_patch_irq.user_handler_id = arg;
}

void hal_misc_init_patch(hal_misc_adapter_t *pmisc_adp)
{
	memcpy(&hal_misc_stubs, &__rom_stubs_hal_misc, sizeof(hal_misc_stubs)) ;
	
	hal_misc_stubs.hal_misc_init = hal_misc_init_patch;

    hal_misc_stubs.hal_misc_wdt_init = hal_misc_wdt_init_patch;
    hal_misc_stubs.hal_misc_wdt_reg_irq = hal_misc_wdt_reg_irq_patch;
	
	//pmisc_adapter = pmisc_adp;
	//hal_irq_set_vector (NonMaskableInt_IRQn, (uint32_t)nmi_irq_patch);
	__rom_stubs_hal_misc.hal_misc_init (pmisc_adp);
}


