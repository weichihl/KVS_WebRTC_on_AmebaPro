/**************************************************************************//**
 * @file     hal_misc.h
 * @brief    The HAL Misc. API implementation.
 * @version  V1.00
 * @date     2017-03-24
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************************/

#ifndef _HAL_MISC_H_
#define _HAL_MISC_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

/**
 * @addtogroup hs_hal_misc Misc.
 * @{
 */

extern const hal_misc_func_stubs_t hal_misc_stubs;

/**
  \brief  The data structure of the Co-Processor firmware image information (Start location & Image size)
*/
typedef struct cp_fw_info_s {
    uint32_t start_addr;
    uint32_t image_size;
} cp_fw_info_t;

/**
  \brief  The data structure for the collection of all Co-Processor firmware image information on AmebaPro.
*/
typedef struct sys_cp_fw_info_s {
	cp_fw_info_t wowlan_fw;
    cp_fw_info_t wlan_fw;
    cp_fw_info_t isp_fw;
    cp_fw_info_t voe_fw;
} sys_cp_fw_info_t;

/**
 *  @brief Enables the watch dog timer.
 *
 *  @returns    void
 */
void hal_misc_wdt_enable (void);

/**
 *  @brief Disables the watch dog timer.
 *
 *  @returns    void
 */
void hal_misc_wdt_disable (void);

/**
 *  @brief Refresh(reload) the watch dog timer counter.
 *         To prevents the watch dog timer timeout event occurred.
 *
 *  @returns    void
 */
void hal_misc_wdt_refresh (void);

/**
 *  @brief Initial the HAL Misc. management adapter.
 *
 *  @param[in]  pmisc_adp  The Misc. entity.
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_init (hal_misc_adapter_t *pmisc_adp)
{
    hal_misc_stubs.hal_misc_init (pmisc_adp);
}

/**
 *  @brief Changes the watch dog timer timeout period.
 *
 *  @param[in]  time_us  The timeout period in micro-second.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_wdt_set_timeout (uint32_t time_us)
{
    hal_misc_stubs.hal_misc_wdt_set_timeout (time_us);
}

/**
 *  @brief Initials the watch dog timer and setup the timeout period.
 *         The system will be reset by the watch dog timeout event by default.
 *
 *  @param[in]  time_us  The timeout period in micro-second.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_wdt_init (uint32_t time_us)
{
    hal_misc_stubs.hal_misc_wdt_init (time_us);
}

/**
 *  @brief Registers a handler for the watch dog timeout interrupt.
 *         The WDT timeout interrupt will trigger the NMI interrupt.
 *         However the NMI interrupt default is in secure region.
 *         To handle the NMI interrupt, we should make the AIRCR.BFHFNMINS = 1.
 *         We can do this by set SCB_AIRCR_BFHFNMINS_VAL = 1 at secure code build time.
 *
 *  @param[in]  handler  The interrupt handler.
 *  @param[in]  arg  The application data will be passed back to the application
 *                   with the callback function.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_wdt_reg_irq (irq_handler_t handler, void *arg)
{
    hal_misc_stubs.hal_misc_wdt_reg_irq (handler, arg);
}

/**
 *  @brief Registers a handler function for the NMI interrupt which is
 *         not triggered by the watch dog timer timeout event.
 *         The NMI interrupt default is in secure region.
 *         To handle the NMI interrupt, we should make the AIRCR.BFHFNMINS = 1.
 *         We can do this by set SCB_AIRCR_BFHFNMINS_VAL = 1 at secure code build time.
 *
 *  @param[in]  handler  The interrupt handler.
 *  @param[in]  arg  The application data will be passed back to the application
 *                   with the callback function.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_nmi_reg_irq (irq_handler_t handler, void *arg)
{
    hal_misc_stubs.hal_misc_nmi_reg_irq (handler, arg);
}

/**
 *  @brief Force triggers a watch dog timer timeout to cause a system reset.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_misc_rst_by_wdt (void)
{
    hal_misc_stubs.hal_misc_rst_by_wdt ();
}

/**
 *  @brief Invokes a CPU reset. Compares to the system reset, it only reset the
 *         CPU part and the program will be restarted. All other peripheral keeps
 *         their state.
 *
 *  @returns    void
 */
__STATIC_INLINE
void hal_misc_cpu_rst (void)
{
    hal_misc_stubs.hal_misc_cpu_rst ();
}

hal_status_t hal_misc_swd_pin_ctrl (uint8_t pin_sel, BOOL en);
hal_status_t hal_misc_jtag_pin_ctrl (uint8_t pin_sel, BOOL en);

/** @} */ /* End of group hs_hal_misc */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_MISC_H_"

