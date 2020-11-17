/**************************************************************************//**
 * @file     hal_i2c.c
 * @brief    This file implements the I2C HAL functions.
 *
 * @version  V1.00
 * @date     2016-09-19
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


#include "hal_i2c.h"
//#include "rtl8195blp_syson.h"
#include "hal_sys_ctrl.h"

extern uint32_t get_xtal_in_clk_ram(void);

#ifdef CONFIG_I2C_EN

#if   defined ( __CC_ARM )                                            /* ARM Compiler 4/5 */
extern hal_i2c_func_stubs_t Image$$_STUB_I2C$$Base;     // symbol from linker script
#define __rom_stubs_hal_i2c Image$$_STUB_I2C$$Base
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)       /* ARM Compiler 6 */
extern hal_i2c_func_stubs_t Image$$_STUB_I2C$$Base;     // symbol from linker script
#define __rom_stubs_hal_i2c Image$$_STUB_I2C$$Base
#elif defined ( __GNUC__ )
extern hal_i2c_func_stubs_t __rom_stubs_hal_i2c;     // symbol from linker script
#elif defined ( __ICCARM__ )
extern hal_i2c_func_stubs_t __rom_stubs_hal_i2c;     // symbol from linker script
#endif

/**
 * @addtogroup ls_hal_i2c I2C
 * @{
 */

/** \brief Description of hal_i2c_timeout_chk
 *
 *    hal_i2c_timeout_chk is used to check if I2C operation is time-out.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter: Pointer to I2C control adapter.
 *   \param[in] uint32_t start_cnt: Start system time count.
 *
 *   \return uint8_t:       Time out result \n\t
 *                          0: NOT time-out, 1: Time-out.
 */
uint8_t hal_i2c_timeout_chk (hal_i2c_adapter_t *phal_i2c_adapter, uint32_t start_cnt)
{
    return __rom_stubs_hal_i2c.hal_i2c_timeout_chk(phal_i2c_adapter, start_cnt);
}

/** \brief Description of hal_i2c_chk_mod
 *
 *    hal_i2c_chk_mod is used to check I2C operation mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:           Check mode status. \n
 *                              0: Slave mode\n
 *                              1: Master mode\n
 *                              2: Configuration error.\n
 */
uint8_t hal_i2c_chk_mod (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_chk_mod(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_pure_init
 *
 *    hal_i2c_pure_init is used to initialize I2C module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t :      i2c enable status
 */
uint8_t hal_i2c_pure_init (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_pure_init(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_pure_deinit
 *
 *    hal_i2c_pure_deinit is used to deinit I2C module.
 *    It's directly to disable I2C module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t: I2C enable status.
 */
uint8_t hal_i2c_pure_deinit (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_pure_deinit(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_en_ctrl
 *
 *    hal_i2c_en_ctrl is used to enable/disable I2C module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t enable: To enable/disable I2C.\n
 *                                  0: Disable.\n
 *                                  1: Enable\n
 *                                  2: Force Disable
 *   \retrun uint8_t:               I2C enable status.
 */
uint8_t hal_i2c_en_ctrl (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable)
{
    return __rom_stubs_hal_i2c.hal_i2c_en_ctrl(phal_i2c_adapter, enable);
}

/** \brief Description of hal_i2c_set_clk
 *
 *    hal_i2c_set_clk is used to set I2C clock.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return hal_status_t:      HAL status.
 */
hal_status_t hal_i2c_set_clk (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_set_clk(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_intr_ctrl
 *
 *    hal_i2c_intr_ctrl is used to set/clear interrupt mask bits.\n
 *    The given intrmsk bits would be cleared first in this function therefore the related\n
 *    interrupt mask is masked.\n
 *    If it's to set mask bits, the related interrupt mask would be set therefore the realted\n
 *    interrupt mask is unmasked.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter: Pointer to I2C control adapter.
 *   \param[in] uint8_t set_clr: To set or clear interrupt. \n
 *                               The interrupt mask register is active low.\n
 *                                1: set, which means the related interrupt mask is unmasked.\n
 *                                0: clear, which means the related interrupt mask is masked.\n
 *   \param[in] uint16_t intr_msk: I2C interrupt mask bit.
 *   \return hal_status_t:      HAL status.
 */
hal_status_t hal_i2c_intr_ctrl (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t set_clr, uint16_t intr_msk)
{
    return __rom_stubs_hal_i2c.hal_i2c_intr_ctrl(phal_i2c_adapter, set_clr, intr_msk);
}

/** \brief Description of hal_i2c_wr
 *
 *    hal_i2c_wr is used to send I2C data. In master mode, this function could send write command, too.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] const uint8_t *dat_buf:     Data buffer address for I2C write.
 *   \param[in] uint32_t dat_len:           Data length for I2C write.
 *   \param[in] uint8_t ctrl:           To control what I2C would do when data is all sent. (Only for Master Mode)\n
 *                                      In slave mode, this part should be always 0.\n
 *                                      0: Do nothing. There will not be a STOP condition when all data is sent.\n
 *                                      And there will not be any START/RESTART condition in the next transmission ,either.\n
 *                                      1: Send STOP after the last data.\n
 *                                      2: There will NOT be a STOP condition after the last data sent. But\n
 *                                      the next transmision would have a START/RESTART condition sent first.\n
 *                                      So setting 2 to this field could influence the following transmission.\n
 *   \return hal_status_t:      When the given Ctrl is NOT fit with hardware setting, a value of HAL_STS_ERR_HW\n
 *                              will be returned. Otherwise, a value of HAL_STS_OK will be returned.
 */
hal_status_t hal_i2c_wr (hal_i2c_adapter_t *phal_i2c_adapter, const uint8_t *dat_buf, uint32_t dat_len, uint8_t ctrl)
{
    return __rom_stubs_hal_i2c.hal_i2c_wr(phal_i2c_adapter, dat_buf, dat_len, ctrl);
}

/** \brief Description of hal_i2c_mst_send_rdcmd
 *
 *    hal_i2c_mst_send_rdcmd is used to send I2C master read command.
 *    It should only be used for master mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint32_t cmd_len:           Read commnad length for I2C read.
 *   \param[in] uint8_t ctrl:               To control what I2C would do when data is all sent. (Only for Master Mode)\n
 *                                      0: Do nothing. There will not be a STOP condition when all data is sent.\n
 *                                      And there will not be any START/RESTART condition in the next transmission ,either.\n
 *                                      1: Send STOP after the last data.\n
 *                                      2: There will NOT be a STOP condition after the last data sent. But\n
 *                                      the next transmision would have a START/RESTART condition sent first.\n
 *                                      So setting 2 to this field could influence the following transmission.
 *
 *  \return void
 */
void hal_i2c_mst_send_rdcmd (hal_i2c_adapter_t *phal_i2c_adapter, uint32_t cmd_len, uint8_t ctrl)
{
    __rom_stubs_hal_i2c.hal_i2c_mst_send_rdcmd(phal_i2c_adapter, cmd_len, ctrl);
}

/** \brief Description of hal_i2c_dma_ctrl
 *
 *    hal_i2c_dma_ctrl is used to enable/disable I2C DMA function.\n
 *    Enable is used to control that this function performs enable or disable operaiton.\n
 *    And it would set/clear related register according to the given DMAEnMsk.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t enable:             To enable/disable I2C DMA function.\n
 *                                      0: Disable.\n
 *                                      1: Enable.
 *   \return uint32_t:         I2C DMA enable status.
 */
uint32_t hal_i2c_dma_ctrl (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable)
{
    return __rom_stubs_hal_i2c.hal_i2c_dma_ctrl(phal_i2c_adapter, enable);
}

/** \brief Description of hal_i2c_mst_restr_ctrl
 *
 *    hal_i2c_mst_restr_ctrl is used to enable/disable RESTART feature.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t restr_en:               To enable/disable I2C RESTART fearture. Software should enable\n
 *                                              this feature before it sets RESTART command in REG_IC_DATA_CMD\n
 *                                              register.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_mst_restr_ctrl (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t restr_en)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_i2c_mst_restr_ctrl_rtl8195blp_patch(phal_i2c_adapter, restr_en);
#else
    return __rom_stubs_hal_i2c.hal_i2c_mst_restr_ctrl(phal_i2c_adapter, restr_en);
#endif
}

/** \brief Description of hal_i2c_mst_gc_sb_ctrl
 *
 *    hal_i2c_mst_gc_sb_ctrl is used to enable/disable General Call or START Byte features.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t enable:             To enable/disable I2C General Call or START Byte feature.
 *   \param[in] uint8_t gc_sb:          Select General Call or START Byte feature.\n
 *                                      0: General Call\n
 *                                      1: START Byte
 *   \return hal_status_t
 */
hal_status_t hal_i2c_mst_gc_sb_ctrl (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t enable, uint8_t gc_sb)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_i2c_mst_gc_sb_ctrl_rtl8195blp_patch(phal_i2c_adapter, enable, gc_sb);
#else
    return __rom_stubs_hal_i2c.hal_i2c_mst_gc_sb_ctrl(phal_i2c_adapter, enable, gc_sb);
#endif
}

/** \brief Description of hal_i2c_slv_no_ack_ctrl
 *
 *    hal_i2c_slv_no_ack_ctrl is used to enable/disable no acknowledge feature in\n
 *    slave mode. If SlvNoAck is enabled, I2C would generate NACK after a data byte is \n
 *    received in slave mode. If SlvNoAck is disabled, I2C would gernerate ACK/NACK,\n
 *    depending on normal criteria.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t no_ack_en:              To enable/disable slave no ack feature.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_slv_no_ack_ctrl (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t no_ack_en)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_no_ack_ctrl(phal_i2c_adapter, no_ack_en);
}

/** \brief Description of hal_i2c_slv_no_ack_sts
 *
 *    hal_i2c_slv_no_ack_sts is used to get the enable status of slave no ack function.\n
 *    If its return value is 0, I2C slave no ack is disabled and could ack to normal transfermation.\n
 *    If its return value is 1, I2C slave no ack is enabled and could ONLY send NACK to all
 *    master command or data.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:               slave mode no-ack status.\n
 *                                  0: slave no ack disabled. 1: slave no ack enabled.
 */
uint8_t hal_i2c_slv_no_ack_sts (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_no_ack_sts(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_ack_gc_ctrl
 *
 *    hal_i2c_slv_ack_gc_ctrl is used to enable/disable I2C responding General Call \n
 *    feature. If it's enabled, I2C could responds to a General Call.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \param[in] uint8_t slv_gc_en:      To enable/disable slave ack General Call feature.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_slv_ack_gc_ctrl (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t slv_gc_en)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_ack_gc_ctrl(phal_i2c_adapter, slv_gc_en);
}

/** \brief Description of hal_i2c_slv_ack_gc_sts
 *
 *    hal_i2c_slv_ack_gc_sts is used to get the enable status of slave ack General
 *    Call.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:               slave mode adc GC status.\n
 *                                  0: Slave does NOT ack GC. 1: Slave could ack GC.
 */
uint8_t hal_i2c_slv_ack_gc_sts (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_ack_gc_sts(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_to_slp
 *
 *    hal_i2c_slv_to_slp is used to set I2C slave into sleep state.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_slv_to_slp (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_to_slp(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_chk_mst_wr
 *
 *    hal_i2c_slv_chk_mst_wr is used to check if there is a master write command for slave addresses of
 *    rtl8195b.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:               0: An master write command for slave address 0 is matched.\n
 *                                  1: An master write command for slave address 1 is matched.\n
 *                                  0xEF: Error status, disable/deinit process is recommended.\n
 *                                  0xFF: No write commnad rtl8195b I2C slave.
 */
uint8_t hal_i2c_slv_chk_mst_wr (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_chk_mst_wr(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_chk_rd_req
 *
 *    hal_i2c_slv_chk_rd_req is used to check if there is a master read command for slave addresses of
 *    rtl8195b.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:     Pointer to I2C control adapter.
 *   \return uint8_t:       0: An master read command for slave address 0 is matched.\n
 *                          1: An master read command for slave address 1 is matched.\n
 *                          0xEF: Error status, disable/deinit process is recommended.\n
 *                          0xFF: No read commnad rtl8195b I2C slave.
 *
 */
uint8_t hal_i2c_slv_chk_rd_req (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_chk_rd_req(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_pin_init
 *
 *    hal_i2c_pin_init is used to initialize i2c clock and pin.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_pin_init (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_pin_init(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_pin_deinit
 *
 *    hal_i2c_pin_deinit is used to deinitialize i2c clock and pin.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_pin_deinit (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_pin_deinit(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_init
 *
 *    hal_i2c_init is used to initialize i2c including platform related features.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_init (hal_i2c_adapter_t *phal_i2c_adapter)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_i2c_init_rtl8195blp_patch(phal_i2c_adapter);
#else
    return __rom_stubs_hal_i2c.hal_i2c_init(phal_i2c_adapter);
#endif
}

/** \brief Description of hal_i2c_deinit
 *
 *    hal_i2c_deinit is used to deinitialize i2c including platform related features.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_deinit (hal_i2c_adapter_t *phal_i2c_adapter)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    return hal_i2c_deinit_rtl8195blp_patch(phal_i2c_adapter);
#else
    return __rom_stubs_hal_i2c.hal_i2c_deinit(phal_i2c_adapter);
#endif
}

/** \brief Description of hal_i2c_load_default
 *
 *    hal_i2c_load_default is used to load default setting for i2c module.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] uint8_t index:   i2c device index.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_load_default (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t index)
{
    return __rom_stubs_hal_i2c.hal_i2c_load_default(phal_i2c_adapter, index);
}

/** \brief Description of hal_i2c_set_tar
 *
 *    hal_i2c_set_tar is to set target slave address in master mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] uint8_t mst_rw:   This target address is for read or write usage.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_set_tar (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t mst_rw)
{
    return __rom_stubs_hal_i2c.hal_i2c_set_tar(phal_i2c_adapter, mst_rw);
}

/** \brief Description of hal_i2c_send_addr_retry
 *
 *    hal_i2c_send_addr_retry is to send address and the first data byte with fail retry.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_addr_retry (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_send_addr_retry(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_send_poll
 *
 *    hal_i2c_send_poll is to send i2c data by polling (blocking) mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_poll (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_send_poll(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_send_intr
 *
 *    hal_i2c_send_intr is to send i2c data by interrupt mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_intr (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_send_intr(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_send_dma_init
 *
 *    hal_i2c_send_dma_init is to allocate a GDMA channel and initialize I2C send DMA data structure.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] hal_gdma_adaptor_t *pi2c_gdma_tx_adaptor:   pointer to I2C GDMA TX adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_dma_init (hal_i2c_adapter_t *phal_i2c_adapter, hal_gdma_adaptor_t *padc_gdma_tx_adaptor)
{
    return __rom_stubs_hal_i2c.hal_i2c_send_dma_init(phal_i2c_adapter, padc_gdma_tx_adaptor);
}

/** \brief Description of hal_i2c_send_dma_deinit
 *
 *    hal_i2c_send_dma_deinit is to free a GDMA channel and de-initialize I2C send DMA data structure.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_dma_deinit (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_send_dma_deinit(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_send_dma
 *
 *    hal_i2c_send_dma is to execute I2C master TX transfer with DMA and the related TX information should be\n
 *    given in phal_i2c_adapter->tx_dat.\n
 *    hal_i2c_send_dma_init MUST be invoked first before using this function.\n
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send_dma (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_send_dma(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_send
 *
 *    hal_i2c_send is an upper layer I2C master send transfer API. It executes the related send(TX) API according\n
 *    to the phal_i2c_adapter->op_mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_send (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_send(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_recv_addr_retry
 *
 *    hal_i2c_recv_addr_retry is to send slave address and the first read command with retry features.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_addr_retry (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_recv_addr_retry(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_recv_poll
 *
 *    hal_i2c_recv_poll is to receive I2C data by polling (blocking) mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_poll (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_recv_poll(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_recv_intr
 *
 *    hal_i2c_recv_intr is to receive I2C data by interrupt (non-blocking) mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_intr (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_recv_intr(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_recv_dma_init
 *
 *    hal_i2c_recv_dma_init is to allocate DMA channel and initialize I2C DMA data structure.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] hal_gdma_adaptor_t *pi2c_gdma_rx_adaptor:   pointer to I2C GDMA RX adatper.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_dma_init (hal_i2c_adapter_t *phal_i2c_adapter, hal_gdma_adaptor_t *padc_gdma_rx_adaptor)
{
    return __rom_stubs_hal_i2c.hal_i2c_recv_dma_init(phal_i2c_adapter, padc_gdma_rx_adaptor);
}

/** \brief Description of hal_i2c_recv_dma_deinit
 *
 *    hal_i2c_recv_dma_deinit is to free DMA channel and deinitialize I2C DMA data structure.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_dma_deinit (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_recv_dma_deinit(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_recv_dma
 *
 *    hal_i2c_recv_dma is to execute I2C master receive by DMA transfer.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_recv_dma (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_recv_dma(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_receive
 *
 *    hal_i2c_receive is an upper layer I2C master receive transfer API. It executes the related receive(RX) API according \n
 *    to the phal_i2c_adapter->op_mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_receive (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_receive(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_set_sar
 *
 *    hal_i2c_set_sar is to set slave own address in slave mode.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \param[in] uint8_t sar_idx:                 slave address index.
 *   \param[in] uint16_t slv_addr:               slave address.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_set_sar (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t sar_idx, uint16_t slv_addr)
{
    return __rom_stubs_hal_i2c.hal_i2c_set_sar(phal_i2c_adapter, sar_idx, slv_addr);
}

/** \brief Description of hal_i2c_slv_recv_poll
 *
 *    hal_i2c_slv_recv_poll is to execute I2C slave receive in polling(blocking) mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t      received data length in byte.
 */
uint32_t hal_i2c_slv_recv_poll (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_recv_poll(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_recv_intr
 *
 *    hal_i2c_slv_recv_intr is to execute I2C slave receive in interrupt(non-blocking) mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t      received data length in byte. (always return 0 at present)
 */
uint32_t hal_i2c_slv_recv_intr (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_recv_intr(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_recv_dma
 *
 *    hal_i2c_slv_recv_dma is to execute I2C slave receive in DMA(non-blocking) mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t      received data length in byte. (always return 0 at present)
 */
uint32_t hal_i2c_slv_recv_dma (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_recv_dma(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_recv
 *
 *    hal_i2c_slv_recv is to execute i2C slave receive upper level API according to phal_i2c_adapter->op_mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_slv_recv (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_recv(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_send_poll
 *
 *    hal_i2c_slv_send_poll is to execute I2C slave send transfer by polling mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t      sent data length in byte.
 */
uint32_t hal_i2c_slv_send_poll (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_send_poll(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_send_intr
 *
 *    hal_i2c_slv_send_intr is to execute I2C slave send transfer by interrupt mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t      sent data length in byte. (always 0 at present)
 */
uint32_t hal_i2c_slv_send_intr (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_send_intr(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_send_dma
 *
 *    hal_i2c_slv_send_dma is to execute i2C slave send transfer by DMA mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return uint32_t      sent data length in byte. (always 0 at present)
 */
uint32_t hal_i2c_slv_send_dma (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_send_dma(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_slv_send
 *
 *    hal_i2c_slv_send is to execute I2C slave send upper level API according to phal_i2c_adapter->op_mode.
 *
 *   \param hal_i2c_adapter_t *phal_i2c_adapter:   pointer to I2C control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_i2c_slv_send (hal_i2c_adapter_t *phal_i2c_adapter)
{
    return __rom_stubs_hal_i2c.hal_i2c_slv_send(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_reg_irq
 *
 *    hal_i2c_reg_irq is used to register a irq handler
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:        Pointer to I2C control adaptor.
 *   \param[in] irq_handler_t handler:                IRQ handler function.
 *   \return void.
 */
void hal_i2c_reg_irq (hal_i2c_adapter_t *phal_i2c_adapter, irq_handler_t handler)
{
    __rom_stubs_hal_i2c.hal_i2c_reg_irq(phal_i2c_adapter, handler);
}

/** \brief Description of hal_i2c_unreg_irq
 *
 *    hal_i2c_unreg_irq is used to unregister a irq handler
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:        Pointer to I2C control adaptor.
 *   \return void.
 */
void hal_i2c_unreg_irq (hal_i2c_adapter_t *phal_i2c_adapter)
{
    __rom_stubs_hal_i2c.hal_i2c_unreg_irq(phal_i2c_adapter);
}

/** \brief Description of hal_i2c_fltr_qk_cali
 *
 *    hal_i2c_fltr_qk_cali is to do a i2c analog filter quick calibration.
 *
 *   \param[in] hal_i2c_adapter_t *phal_i2c_adapter:        Pointer to I2C control adaptor.
 *   \param[in] uint8_t pin_sel:        I2C pin seletion.
 *   \return uint8_t        0: Find a best configuration.\n
 *                          1: Can't find a best, using a good one configuration.\n
 *                          2: Error.
 */
uint8_t hal_i2c_fltr_qk_cali (hal_i2c_adapter_t *phal_i2c_adapter, uint8_t pin_sel)
{
//    I2C_Type *pi2c_reg = phal_i2c_adapter->init_dat.reg_base;
    uint32_t cap_l_cnt;
    uint32_t cap_l_tmp;
    uint8_t cap_m_cnt;
    uint8_t cap_m_tmp;
    uint32_t rsts_m_cnt;
    uint32_t rsts_m_tmp;
    uint32_t reg_offset;

    uint32_t cap_l_best = 0;
    uint8_t cap_m_best = 0;
    uint32_t rsts_m_best = 0;
    uint32_t rsts_m_best_cnt = 0;
    uint32_t status_temp;
    
    if (get_xtal_in_clk_ram() != 0) {
        DBG_I2C_ERR("XTAL is NOT 40MHz. Cali. aborted.\n");
        return 2;
    }

    /* enable filter and calibrator input */
    hal_syson_i2c_filter_ctrl(ENABLE);
    hal_syson_i2c_cali_in_ctrl(ENABLE);
    hal_i2c_fltr_ana_ctrl(ENABLE);
    
    /* pin_sel: 0 for data, 1 for clock */
    reg_offset = (uint32_t)(&(I2C_BASE_REG->dat_fltr_rsts_m));
    if (pin_sel) {
        reg_offset = (uint32_t)(&(I2C_BASE_REG->clk_fltr_rsts_m));
    }


    /* calibrate for data pin */
    for (rsts_m_tmp = 0, rsts_m_cnt = 0; rsts_m_cnt <= LP_I2C_FLTR_RSTS_M_LEN; rsts_m_cnt++) {
        if (rsts_m_cnt) {
            rsts_m_tmp |= (BIT0 << (rsts_m_cnt - 1));
        }
        
        HAL_I2C_WRITE32(reg_offset, rsts_m_tmp);
        /* read rsts_m after write for check */
        HAL_I2C_READ32(reg_offset);
        for (cap_m_tmp = 0, cap_m_cnt = 0; cap_m_cnt <= LP_I2C_FLTR_CAP_M_LEN; cap_m_cnt++) {
            if (cap_m_cnt) {
                cap_m_tmp |= (BIT0 << (cap_m_cnt - 1));
            }
            
            HAL_I2C_WRITE32((reg_offset+0x10), cap_m_tmp);
            /* read cap_m after write for check */
            HAL_I2C_READ32(reg_offset+0x10);
            for (cap_l_tmp = 0, cap_l_cnt = 0; cap_l_cnt <= LP_I2C_FLTR_CAP_L_LEN; cap_l_cnt++) {
                if (cap_l_cnt) {
                    cap_l_tmp |= (BIT0 << (cap_l_cnt - 1));
                }
                
                HAL_I2C_WRITE32((reg_offset+0x0C), cap_l_tmp);
                /* read cap_l after write for check */
                HAL_I2C_READ32(reg_offset+0x0C);

                /* enable and then check status */
                DBG_I2C_INFO("default deglitch reg: %x\n", hal_i2c_read_dglch_reg());
                hal_i2c_dglch_ctrl(ENABLE);
                hal_i2c_dglch_ctrl_chk();

                if (!pin_sel) {
                    if ((hal_i2c_read_dglch_reg() & (uint32_t)0x300) == (uint32_t)0x000) {
                        DBG_I2C_INFO("Find a good RC match:\n");
                        DBG_I2C_INFO("OK -> R: %08x, C_m: %08x, C_l: %08x\n", rsts_m_tmp, cap_m_tmp, cap_l_tmp);
                        
                        /* scale it */
#if 0 //remove scale 20180104
                        cap_l_tmp = (rsts_m_cnt+1) * 2;
                        if (rsts_m_cnt > (uint32_t)(LP_I2C_FLTR_RSTS_M_LEN/2)) {
                            DBG_I2C_ERR("Could NOT scale to the double value\n");
                        }

                        for (rsts_m_best_cnt = (rsts_m_cnt+1);
                                ((rsts_m_best_cnt < cap_l_tmp) && (rsts_m_best_cnt < LP_I2C_FLTR_RSTS_M_LEN)); rsts_m_best_cnt++) {
                            rsts_m_tmp |= (BIT0 << rsts_m_best_cnt);
                        }

                        HAL_I2C_WRITE32(reg_offset, rsts_m_tmp);
                        /* read rsts_m after write for check */
                        HAL_I2C_READ32(reg_offset);
                        DBG_I2C_INFO("After scaling R: %08x\n", rsts_m_tmp);
#endif
                        /* disable calibrator input */
                        hal_syson_i2c_cali_in_ctrl(DISABLE);
                        hal_i2c_en_ctrl(phal_i2c_adapter, I2CDisable);
                        hal_i2c_en_ctrl(phal_i2c_adapter, I2CEnable);
                        return 0;
                    } else if ((hal_i2c_read_dglch_reg() & (uint32_t)0x300) != (uint32_t)0x300) {
                        DBG_I2C_INFO("mid -> R: %08x, C_m: %08x, C_l: %08x\n", rsts_m_tmp, cap_m_tmp, cap_l_tmp);
                        /* not find the good one yet, but record the current best */
                        cap_l_best = cap_l_tmp;
                        cap_m_best = cap_m_tmp;
                        rsts_m_best = rsts_m_tmp;
                        rsts_m_best_cnt = rsts_m_cnt;
                    } else {
                        continue;
                    }
                } else {
                    if ((hal_i2c_read_dglch_reg() & (uint32_t)0xC00) == (uint32_t)0x000) {
                        DBG_I2C_INFO("Find a good RC match:\n");
                        DBG_I2C_INFO("OK -> R: %08x, C_m: %08x, C_l: %08x\n", rsts_m_tmp, cap_m_tmp, cap_l_tmp);
                        /* scale it */
#if 0 //remove scale 20180104
                        cap_l_tmp = (rsts_m_cnt+1) * 2;
                        if (rsts_m_cnt > (uint32_t)(LP_I2C_FLTR_RSTS_M_LEN/2)) {
                            DBG_I2C_ERR("Could NOT scale to the double value\n");
                        }

                        for (rsts_m_best_cnt = (rsts_m_cnt+1);
                                ((rsts_m_best_cnt < cap_l_tmp) && (rsts_m_best_cnt < LP_I2C_FLTR_RSTS_M_LEN)); rsts_m_best_cnt++) {
                            rsts_m_tmp |= (BIT0 << rsts_m_best_cnt);
                        }

                        HAL_I2C_WRITE32(reg_offset, rsts_m_tmp);
                        /* read rsts_m after write for check */
                        HAL_I2C_READ32(reg_offset);
                        DBG_I2C_INFO("After scaling R: %08x\n", rsts_m_tmp);
#endif
                        /* disable calibrator input */
                        hal_syson_i2c_cali_in_ctrl(DISABLE);
                        hal_i2c_en_ctrl(phal_i2c_adapter, I2CDisable);
                        hal_i2c_en_ctrl(phal_i2c_adapter, I2CEnable);
                        return 0;
                    } else if ((hal_i2c_read_dglch_reg() & 0xC00) != 0xC00) {
                        DBG_I2C_INFO("mid -> %x\n", hal_i2c_read_dglch_reg());
                        DBG_I2C_INFO("mid -> R: %08x, C_m: %08x, C_l: %08x\n", rsts_m_tmp, cap_m_tmp, cap_l_tmp);
                        /* not find the good one yet, but record the current best */
                        cap_l_best = cap_l_tmp;
                        cap_m_best = cap_m_tmp;
                        rsts_m_best = rsts_m_tmp;
                        rsts_m_best_cnt = rsts_m_cnt;
                    } else {
                        continue;
                    }
                }
            }
        }
    }

    /* disable calibrator input */
    hal_syson_i2c_cali_in_ctrl(DISABLE);    
    hal_i2c_en_ctrl(phal_i2c_adapter, I2CDisable);
    hal_i2c_en_ctrl(phal_i2c_adapter, I2CEnable);
    if ((rsts_m_cnt == LP_I2C_FLTR_RSTS_M_LEN) && (cap_m_cnt == LP_I2C_FLTR_CAP_M_LEN)
        && (cap_l_cnt == LP_I2C_FLTR_CAP_L_LEN)) {
        DBG_I2C_ERR("Not find a good RC match at all.\n");
        if (rsts_m_best != 0) {
            DBG_I2C_ERR("Use the best RC match that we could find.\n");
            HAL_I2C_WRITE32(reg_offset, rsts_m_best);
            HAL_I2C_WRITE32((reg_offset+0x10), cap_m_best);
            HAL_I2C_WRITE32((reg_offset+0x0C), cap_l_best);
            DBG_I2C_INFO("R: %08x, C_m: %08x, C_l: %08x\n", HAL_I2C_READ32(reg_offset), HAL_I2C_READ32(reg_offset+0x10),
                                            HAL_I2C_READ32(reg_offset+0x0C));
            /* scale it */
#if 0   //remove scale 20180104
            rsts_m_tmp = rsts_m_best;
            cap_l_tmp = (rsts_m_best_cnt+1) * 2;
            if (rsts_m_best_cnt > (uint32_t)(LP_I2C_FLTR_RSTS_M_LEN/2)) {
                DBG_I2C_ERR("Could NOT scale to the double value\n");
            }

            for (cap_m_tmp = (rsts_m_best_cnt+1);
                    ((cap_m_tmp < cap_l_tmp) || (cap_m_tmp < LP_I2C_FLTR_RSTS_M_LEN)); cap_m_tmp++) {
                rsts_m_tmp |= (BIT0 << cap_m_tmp);
            }

            HAL_I2C_WRITE32(reg_offset, rsts_m_tmp);

            /* read rsts_m after write for check */
            HAL_I2C_READ32(reg_offset);
            DBG_I2C_INFO("After scaling R: %08x\n", rsts_m_tmp);
#endif
            return 1;
        } else {
            DBG_I2C_ERR("Could not even find a usable RC match. Disable Filter!!\n");
            hal_syson_i2c_filter_ctrl(DISABLE);
            hal_i2c_fltr_ana_ctrl(DISABLE);
            return 2;
        }
    } else {
        return 2;
    }
}

/** @} */ /* End of group ls_hal_i2c */

#endif

