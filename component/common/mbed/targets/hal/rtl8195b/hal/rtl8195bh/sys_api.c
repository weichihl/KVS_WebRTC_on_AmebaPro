/* mbed Microcontroller Library
 *******************************************************************************
 * Copyright (c) 2014, Realtek
 * All rights reserved.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *******************************************************************************
 */
#include "cmsis.h"
#include "sys_api.h"
#include "flash_api.h"
#include "osdep_service.h"
#include "device_lock.h"
#include "hal_flash_boot.h"

#define FLASH_SECTOR_SIZE				0x1000

/**
  * @brief  Clear OTA signature so that boot code load default image.
  * @retval none
  */
void sys_clear_ota_signature(void)
{
	flash_t	flash;
	uint32_t targetFWaddr;
	uint8_t *pbuf = NULL;
	fw_img_export_info_type_t *pfw_image_info;

	pfw_image_info = get_fw_img_info_tbl();

	if(!(pfw_image_info->fw1_valid == 1 && pfw_image_info->fw2_valid == 1)){
		printf("\n\rOnly one valid fw, no target fw to clear");
		return;
	}
	
	if(pfw_image_info->fw2_sn >= pfw_image_info->fw1_sn)
		// FW2 is upgraded fw, set target to it
		targetFWaddr = pfw_image_info->fw2_start_offset;
	else
		// FW1 is upgraded fw, set target to it
		targetFWaddr = pfw_image_info->fw1_start_offset;
	
	printf("\n\rtarget FW addr = 0x%08X", targetFWaddr);
	
	pbuf = malloc(FLASH_SECTOR_SIZE);
	if(!pbuf){
		printf("\n\rAllocate buf fail");
		return;
	}
	
	// need to enter critical section to prevent executing the XIP code at first sector after we erase it.
	rtw_enter_critical(NULL, NULL);
	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_stream_read(&flash, targetFWaddr, FLASH_SECTOR_SIZE, pbuf);
	// NOT the first byte of ota signature to make it invalid
	pbuf[0] = ~(pbuf[0]);
	flash_erase_sector(&flash, targetFWaddr);
	flash_burst_write(&flash, targetFWaddr, FLASH_SECTOR_SIZE, pbuf);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
	rtw_exit_critical(NULL, NULL);
	
	free(pbuf);
	printf("\n\rClear OTA signature success.");
}

/**
  * @brief  Recover OTA signature so that boot code load upgraded image(ota image).
  * @retval none
  */
void sys_recover_ota_signature(void)
{
	flash_t	flash;
	uint32_t targetFWaddr;
	uint8_t *pbuf = NULL;
	fw_img_export_info_type_t *pfw_image_info;

	pfw_image_info = get_fw_img_info_tbl();

	if(pfw_image_info->fw1_valid == 1 && pfw_image_info->fw2_valid == 1){
		printf("\n\rBoth fw valid, no target fw to recover");
		return;
	}
	
	if(pfw_image_info->loaded_fw_idx == 1)
		// FW2 is upgraded fw, set target to it
		targetFWaddr = pfw_image_info->fw2_start_offset;
	else
		// FW1 is upgraded fw, set target to it
		targetFWaddr = pfw_image_info->fw1_start_offset;
	
	printf("\n\rtarget FW addr = 0x%08X", targetFWaddr);
	
	pbuf = malloc(FLASH_SECTOR_SIZE);
	if(!pbuf){
		printf("\n\rAllocate buf fail");
		return;
	}

	device_mutex_lock(RT_DEV_LOCK_FLASH);
	flash_stream_read(&flash, targetFWaddr, FLASH_SECTOR_SIZE, pbuf);
	// NOT the first byte of ota signature to make it valid
	pbuf[0] = ~(pbuf[0]);
	flash_erase_sector(&flash, targetFWaddr);
	flash_burst_write(&flash, targetFWaddr, FLASH_SECTOR_SIZE, pbuf);
	device_mutex_unlock(RT_DEV_LOCK_FLASH);
	
	free(pbuf);
	printf("\n\rRecover OTA signature success.");
}

/**
  * @brief  Switch from current firmware to the other (if existed)
  * @retval none
  */
void sys_select_alternative_ota_signature(void){

	fw_img_export_info_type_t *pfw_image_info;

	pfw_image_info = get_fw_img_info_tbl();

	if(pfw_image_info->fw1_valid == 1 && pfw_image_info->fw2_valid == 1){
		sys_clear_ota_signature();
	}else if(pfw_image_info->fw1_valid == 1 || pfw_image_info->fw2_valid == 1){
		sys_recover_ota_signature();
	}else
		printf("No valid FW.\r\n");

}
	

