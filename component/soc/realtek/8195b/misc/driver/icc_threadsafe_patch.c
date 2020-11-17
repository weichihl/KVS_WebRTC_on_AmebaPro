#include <string.h>
#include <cmsis.h>
#include <osdep_service.h>

//-------------------------
extern int freertos_queue_size;
void setup_mpu(uint32_t start, uint32_t end, uint32_t ena)
{
	MPU->MAIR0 = 0;
	MPU->RNR = 0x1; // region 1
	MPU->RBAR = (start&(~0x1F))|(0<<3)|(0x2<<1)|0; // non-sharable readonly no exectualbe
	if(ena){
		MPU->RLAR = (end&(~0x1F))|(0<<4)|(2<<2)|1; // use attr2, EN=1
		MPU->CTRL |= MPU_CTRL_ENABLE_Msk;
	}else{
		MPU->RLAR = (end&(~0x1F))|(0<<4)|(2<<2)|0; // use attr2, EN=1
		MPU->CTRL &= (~MPU_CTRL_ENABLE_Msk);
	}
}
 
//-------------------------


// Thread safe protection
#define THREAD_SAFE_DEF(name) _mutex thsafe_mutex_##name = NULL;
#define THREAD_SAFE_INIT(name) do{ rtw_mutex_init(&thsafe_mutex_##name); printf("tsi %x\n\r", thsafe_mutex_##name);} while(0)
#define THREAD_SAFE_FREE(name) do{ rtw_mutex_free(&thsafe_mutex_##name); } while(0)

#define DEBUG_MUTEX_POLLUTION 0
#if (DEBUG_MUTEX_POLLUTION == 1)
#define THREAD_SAFE(name, expression) do{ \
		setup_mpu((uint32_t)thsafe_mutex_##name, (uint32_t)thsafe_mutex_##name+freertos_queue_size, 0); \
		rtw_mutex_get(&thsafe_mutex_##name); \
		expression; \
		rtw_mutex_put(&thsafe_mutex_##name); \
		setup_mpu((uint32_t)thsafe_mutex_##name, (uint32_t)thsafe_mutex_##name+freertos_queue_size, 1); \
}while(0)
#else
#define THREAD_SAFE(name, expression) do{ \
		rtw_mutex_get(&thsafe_mutex_##name); \
		expression; \
		rtw_mutex_put(&thsafe_mutex_##name); \
}while(0)
#endif

/*
#define THREAD_SAFE(name, expression) do{ \
		expression; \
}while(0)
*/
extern const hal_icc_func_stubs_t __rom_stubs_hal_icc;

THREAD_SAFE_DEF(icc);

void hal_icc_init_thread_safe_patch (hal_icc_adapter_t *icc_adapter);

// fill from rom code
hal_icc_func_stubs_t hal_icc_stubs = {
    .hal_icc_init = hal_icc_init_thread_safe_patch,
};

hal_status_t hal_icc_ls_write_cmd_thread_safe_patch (hal_icc_adapter_t *icc_adapter, uint32_t addr, uint32_t *pdata, uint32_t len_dw)
{
	hal_status_t status;
	THREAD_SAFE(icc, status = __rom_stubs_hal_icc.hal_icc_ls_write_cmd(icc_adapter, addr, pdata, len_dw));
	return status;
}

hal_status_t hal_icc_ls_read_cmd_thread_safe_patch (hal_icc_adapter_t *icc_adapter, uint32_t addr, uint32_t *pbuf, uint32_t len_dw)
{
	hal_status_t status;
	THREAD_SAFE(icc, status = __rom_stubs_hal_icc.hal_icc_ls_read_cmd(icc_adapter, addr, pbuf, len_dw));
	return status;	
}

hal_status_t hal_icc_ping_thread_safe_patch (hal_icc_adapter_t *icc_adapter, uint32_t ping_data, uint32_t timeout_us)
{
	hal_status_t status;
	THREAD_SAFE(icc, status = __rom_stubs_hal_icc.hal_icc_ping(icc_adapter, ping_data, timeout_us));
	return status;		
}

hal_status_t hal_icc_h2l_cmd_send_thread_safe_patch (hal_icc_adapter_t *icc_adapter, uint32_t cmd_word0, 
                                            uint32_t cmd_word1, uint32_t timeout_us)
{
	hal_status_t status;
	THREAD_SAFE(icc, status = __rom_stubs_hal_icc.hal_icc_h2l_cmd_send(icc_adapter, cmd_word0, cmd_word1, timeout_us));
	return status;		
}

void hal_icc_init_thread_safe_patch (hal_icc_adapter_t *icc_adapter)
{
	// copy from rom table
	memcpy(&hal_icc_stubs, &__rom_stubs_hal_icc, sizeof(hal_icc_func_stubs_t));
	
	// init mutex
	THREAD_SAFE_INIT(icc);
	
	__rom_stubs_hal_icc.hal_icc_init(icc_adapter);
	hal_icc_stubs.hal_icc_init = hal_icc_init_thread_safe_patch;
	// other patch function
	hal_icc_stubs.hal_icc_ls_write_cmd = hal_icc_ls_write_cmd_thread_safe_patch;
	hal_icc_stubs.hal_icc_ls_read_cmd = hal_icc_ls_read_cmd_thread_safe_patch;
	hal_icc_stubs.hal_icc_ping = hal_icc_ping_thread_safe_patch;
	hal_icc_stubs.hal_icc_h2l_cmd_send = hal_icc_h2l_cmd_send_thread_safe_patch;
	
	
}