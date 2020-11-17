/**************************************************************************//**
 * @file     hal_spic_nsc.h
 * @brief    The header file of hal_spic_nsc.c
 * @version  1.00
 * @date     2017-08-22
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


#ifndef _HAL_SPIC_NSC_H_
#define _HAL_SPIC_NSC_H_
#include "cmsis.h"
#include <arm_cmse.h>   /* Use CMSE intrinsics */

#ifdef  __cplusplus
      extern "C"
      {
#endif

#if defined(CONFIG_BUILD_SECURE)

/**

        \addtogroup hs_hal_spic_nsc_api Flash Controller HAL NSC APIs
        \ingroup hs_hal_spic
        \brief The Flash Controller HAL NSC (Non-Secure Callable) APIs. Non-secure domain is allowed to access secure functions through NSC APIs.
        @{
*/


void NS_ENTRY spic_load_default_setting_nsc(pspic_init_para_t pspic_init_data);
u8 NS_ENTRY spic_query_system_clk_nsc(void);
void NS_ENTRY spic_clock_ctrl_nsc(u8 ctl);
void NS_ENTRY spic_pin_ctrl_nsc(u8 io_pin_sel, u8 ctl);
hal_status_t NS_ENTRY spic_init_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode);
void NS_ENTRY spic_load_calibration_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY spic_store_calibration_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY spic_config_dtr_read_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY spic_config_auto_mode_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY spic_config_user_mode_nsc(phal_spic_adaptor_t phal_spic_adaptor);
BOOL NS_ENTRY spic_verify_calibration_para_nsc(void);
void NS_ENTRY spic_enable_seq_read_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY spic_disable_seq_read_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY spic_set_chnl_num_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void NS_ENTRY spic_set_delay_line_nsc(u8 delay_line);
void NS_ENTRY spic_rx_cmd_8io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void NS_ENTRY spic_rx_cmd_4io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void NS_ENTRY spic_rx_cmd_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void NS_ENTRY spic_tx_cmd_8io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void NS_ENTRY spic_tx_cmd_4io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void NS_ENTRY spic_tx_cmd_8io_no_check_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void NS_ENTRY spic_tx_cmd_4io_no_check_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void NS_ENTRY spic_tx_cmd_no_check_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void NS_ENTRY spic_tx_cmd_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void NS_ENTRY spic_wait_ready_nsc(SPIC_Type *spic_dev);
void NS_ENTRY spic_flush_fifo_nsc(SPIC_Type *spic_dev);
hal_status_t NS_ENTRY spic_pinmux_init_nsc(phal_spic_adaptor_t phal_spic_adaptor,u8 io_pin_sel);
hal_status_t NS_ENTRY spic_init_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode, u8 io_pin_sel);
hal_status_t NS_ENTRY spic_deinit_nsc(phal_spic_adaptor_t phal_spic_adaptor);
BOOL NS_ENTRY spic_calibration_nsc(phal_spic_adaptor_t phal_spic_adaptor, u32 default_dummy_cycle);
void NS_ENTRY spic_store_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor, phal_spic_restore_setting_t phal_spic_setting);
void NS_ENTRY spic_recover_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor, phal_spic_restore_setting_t phal_spic_setting);

/** *@} */ /* End of group hs_hal_spic_nsc_api */

#endif // end of "#if defined(CONFIG_BUILD_SECURE)"


#if defined(CONFIG_BUILD_NONSECURE)
void spic_load_default_setting_nsc(pspic_init_para_t pspic_init_data);
u8 spic_query_system_clk_nsc(void);
void spic_clock_ctrl_nsc(u8 ctl);
void spic_pin_ctrl_nsc(u8 io_pin_sel, u8 ctl);
hal_status_t spic_init_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode);
void spic_load_calibration_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void spic_store_calibration_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void spic_config_dtr_read_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void spic_config_auto_mode_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void spic_config_user_mode_nsc(phal_spic_adaptor_t phal_spic_adaptor);
BOOL spic_verify_calibration_para_nsc(void);
void spic_enable_seq_read_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void spic_disable_seq_read_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void spic_set_chnl_num_nsc(phal_spic_adaptor_t phal_spic_adaptor);
void spic_set_delay_line_nsc(u8 delay_line);
void spic_rx_cmd_8io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_rx_cmd_4io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_rx_cmd_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_8io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_4io_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_8io_no_check_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_4io_no_check_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_no_check_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_tx_cmd_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 cmd, u8 data_phase_len, u8 *pdata);
void spic_wait_ready_nsc(SPIC_Type *spic_dev);
void spic_flush_fifo_nsc(SPIC_Type *spic_dev);
hal_status_t spic_pinmux_init_nsc(phal_spic_adaptor_t phal_spic_adaptor,u8 io_pin_sel);
hal_status_t spic_init_nsc(phal_spic_adaptor_t phal_spic_adaptor, u8 spic_bit_mode, u8 io_pin_sel);
hal_status_t spic_deinit_nsc(phal_spic_adaptor_t phal_spic_adaptor);
BOOL spic_calibration_nsc(phal_spic_adaptor_t phal_spic_adaptor, u32 default_dummy_cycle);
void spic_store_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor, phal_spic_restore_setting_t phal_spic_setting);
void spic_recover_setting_nsc(phal_spic_adaptor_t phal_spic_adaptor, phal_spic_restore_setting_t phal_spic_setting);


#define spic_load_default_setting	    spic_load_default_setting_nsc
#define spic_query_system_clk	        spic_query_system_clk_nsc
#define spic_clock_ctrl	                spic_clock_ctrl_nsc
#define spic_pin_ctrl	                spic_pin_ctrl_nsc
#define spic_init_setting	            spic_init_setting_nsc
#define spic_load_calibration_setting	spic_load_calibration_setting_nsc
#define spic_store_calibration_setting	spic_store_calibration_setting_nsc
#define spic_config_dtr_read	        spic_config_dtr_read_nsc
#define spic_config_auto_mode	        spic_config_auto_mode_nsc
#define spic_config_user_mode	        spic_config_user_mode_nsc
#define spic_verify_calibration_para	spic_verify_calibration_para_nsc
#define spic_enable_seq_read	        spic_enable_seq_read_nsc
#define spic_disable_seq_read	        spic_disable_seq_read_nsc
#define spic_set_chnl_num	            spic_set_chnl_num_nsc
#define spic_set_delay_line	            spic_set_delay_line_nsc
#define spic_rx_cmd_8io	                spic_rx_cmd_8io_nsc
#define spic_rx_cmd_4io	                spic_rx_cmd_4io_nsc
#define spic_rx_cmd	                    spic_rx_cmd_nsc
#define spic_tx_cmd_8io	                spic_tx_cmd_8io_nsc
#define spic_tx_cmd_4io	                spic_tx_cmd_4io_nsc
#define spic_tx_cmd_8io_no_check	    spic_tx_cmd_8io_no_check_nsc
#define spic_tx_cmd_4io_no_check	    spic_tx_cmd_4io_no_check_nsc
#define spic_tx_cmd_no_check	        spic_tx_cmd_no_check_nsc
#define spic_tx_cmd	                    spic_tx_cmd_nsc
#define spic_wait_ready	                spic_wait_ready_nsc
#define spic_flush_fifo	                spic_flush_fifo_nsc
#define spic_pinmux_init                spic_pinmux_init_nsc
#define spic_init                       spic_init_nsc
#define spic_deinit                     spic_deinit_nsc
#define spic_calibration                spic_calibration_nsc
#define spic_store_setting              spic_store_setting_nsc
#define spic_recover_setting            spic_recover_setting_nsc
#endif  // end of "#if defined(CONFIG_BUILD_NONSECURE)"

#ifdef  __cplusplus
      }
#endif


#endif  // end of "#define _HAL_SPIC_NSC_H_"

