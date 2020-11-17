#include "osdep_service.h"

/**
  * @brief  Lock resource before flash processing
  * @param  none
  * @retval  none
  */
extern void isp_mcu_lock(void);
extern void isp_mcu_release(void);
void flash_resource_lock( void )
{
    isp_mcu_lock();
    rtw_cpu_lock();
}

/**
  * @brief  Unlock resource after flash processing
  * @param  none
  * @retval  none
  */
void flash_resource_unlock( void )
{
    isp_mcu_release();
    rtw_cpu_unlock();
}

/**
  * @brief  Unlock flash write protect for winbond
  * @param  none
  * @retval  none
  */
#include "flash_api.h"
#define WINBOND 0XEF
#define MANU_ID 0X00
void flash_unprotect_winbond(void)
{
      extern hal_spic_adaptor_t *pglob_spic_adaptor;
      flash_t         flash;
      int status  = 0;
      int status2 = 0;
      int status3 = 0;
      if(pglob_spic_adaptor != NULL){
            if(pglob_spic_adaptor->flash_id[MANU_ID] == WINBOND){
                //status = flash_get_status(&flash);
                status2 = flash_get_status2(&flash);
                status3 = flash_get_status3(&flash);
                flash_set_status(&flash,0);
                flash_set_status2(&flash,status2&0x02);//Keep the quad mode enable
                flash_set_status3(&flash,status3&0x60);//Kepp the driving strength
                //dbg_printf("Status 0:%x 1:%x 2:%x\r\n",flash_get_status(&flash),flash_get_status2(&flash),flash_get_status3(&flash));
            }
      }
}
