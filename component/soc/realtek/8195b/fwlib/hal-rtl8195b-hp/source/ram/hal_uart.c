/**************************************************************************//**
 * @file     hal_uart.c
 * @brief    This UART HAL API functions.
 *
 * @version  V1.00
 * @date     2016-07-15
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

#include "hal_uart.h"
#include "hal_gdma.h"
#include "hal_pinmux.h"
#include "hal_cache.h"
#include "hal_gpio.h"
#include "hal_irq.h"
#include "memory.h"

#if CONFIG_UART_EN

extern hal_status_t hal_gpio_pull_ctrl (uint32_t pin_name, pin_pull_type_t pull_type);

/**
 * @addtogroup hs_hal_uart UART
 * @{
 * @brief The UART HAL APIs.
 */

#define UART_GDMA_MAX_BLOCK         16
gdma_ch_lli_t uart_tx_gdma_ch_lli[MAX_UART_PORT][UART_GDMA_MAX_BLOCK] __ALIGNED(32);
gdma_ch_lli_t uart_rx_gdma_ch_lli[MAX_UART_PORT][UART_GDMA_MAX_BLOCK] __ALIGNED(32);

/**
 *  @brief To initial a UART port adapter. This function must be called before any UART port
 *         operation. This function will do:
 *           - enable the UART hardware.
 *           - register the interrupt handler.
 *           - configures the pin mux.
 *
 *  @param[in]  puart_adapter  The UART adapter.
 *  @param[in]  uart_idx The UART index. The value can be 0 .. 2.
 *  @param[in]  pin_sel  The pin mux selection.
 *  @param[in]  pconfig  The extra UART port setting for the initial configuration.
 *                       This is an UART adapter initial value. If this value is not NULL,
 *                       the initialization function will initial the new UART adapter by
 *                       this initial value. And also will do further configure, configures
 *                       the bard rate, hardware flow control and the frame format.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  UART port initialization OK.
 */
hal_status_t hal_uart_init (phal_uart_adapter_t puart_adapter, uint32_t uart_idx,
                            uart_pin_sel_t pin_sel, phal_uart_defconfig_t pconfig)
{
    hal_status_t ret;
    io_pin_t *pin_list;
    uint8_t uart_rx_pin;
    uint32_t i;

    pin_list = (io_pin_t *)&hal_uart_stubs.uart_tr_pin[(uart_idx*12) + (pin_sel*3)];
    ret = hal_pinmux_register (pin_list, (PID_UART0+uart_idx));
    if (ret == HAL_OK) {
        // RX Pin pull-high to prevent this folating on this pin
        uart_rx_pin = hal_uart_stubs.uart_tr_pin[(uart_idx*12) + (pin_sel*3)];
        hal_gpio_pull_ctrl (uart_rx_pin, Pin_PullUp);
        // wait ready, delay ~4us
        for (i=0; i<135; i++) {
            __NOP();
            __NOP();
            __NOP();
            __NOP();
            __NOP();
        }
        ret = hal_uart_stubs.hal_uart_init (puart_adapter, uart_idx, pin_sel, pconfig);
        if (ret == HAL_OK) {
            hal_irq_enable (UART_IRQn);
        }
        
    }
    return ret;
}

/**
 *  @brief Disable the given UART port. It will do:
 *           - disable UART hardware function.
 *           - disable UART GDMA channel.
 *           - disable UART pins.
 *
 *  @param[in]  puart_adapter  The UART adapter.
 *
 *  @returns void
 */
void hal_uart_deinit (phal_uart_adapter_t puart_adapter)
{
    uint32_t uart_idx = puart_adapter->uart_idx;
    uint32_t pin_sel = puart_adapter->pin_mux_sel;
    io_pin_t *pin_list;
    uint8_t uart_rx_pin;

    hal_uart_stubs.hal_uart_deinit(puart_adapter);
    pin_list = (io_pin_t *)&hal_uart_stubs.uart_tr_pin[(uart_idx*12) + (pin_sel*3)];
    hal_pinmux_unregister (pin_list, (PID_UART0+uart_idx));
    uart_rx_pin = hal_uart_stubs.uart_tr_pin[(uart_idx*12) + (pin_sel*3)];
    hal_gpio_pull_ctrl (uart_rx_pin, Pin_PullNone);
}

/**
 *  @brief Configures the UART hardware auto flow-control setting.
 *
 *  @param[in]  puart_adapter  The UART adapter.
 *  @param[in]  flow_ctrl  The flow control setting.
 *                           - 0: no hardware flow control.
 *                           - 1: enable RX (RTS) flow control.
 *                           - 2: enable TX (CTS) flow control.
 *                           - 3: enable RTS and CTS hardware flow control.
 *
 *  @returns    Always return HAL_OK
 */
hal_status_t hal_uart_set_flow_control (phal_uart_adapter_t puart_adapter, uint32_t flow_ctrl)
{
    uint32_t uart_idx = puart_adapter->uart_idx;
    uint32_t pin_sel = puart_adapter->pin_mux_sel;
    io_pin_t *pin_list;
    hal_status_t ret;

    pin_list = (io_pin_t *)&hal_uart_stubs.uart_fc_pin[(uart_idx*12) + (pin_sel*3)];

    if (flow_ctrl == UartFlowCtlNone) {
        ret = hal_pinmux_unregister (pin_list, (PID_UART0+uart_idx));
    } else {
        ret = hal_pinmux_register (pin_list, (PID_UART0+uart_idx));
        if (ret != HAL_OK) {
            return ret;
        }
    }
    return hal_uart_stubs.hal_uart_set_flow_control (puart_adapter, flow_ctrl);
}

/**
 *  @brief To initial a GDMA channel for the UART TX DMA mode transfer.
 *
 *  @param[in]  puart_adapter  The UART adapter.
 *  @param[in]  pgdma_chnl The GDMA channel adapter. It is use to control
 *              the GDMA channel transfer.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GDMA channel initialization OK.
 */
hal_status_t hal_uart_tx_gdma_init(phal_uart_adapter_t puart_adapter, phal_gdma_adaptor_t pgdma_chnl)
{
    hal_status_t ret;

	memset((void *)pgdma_chnl, 0, sizeof(hal_gdma_adaptor_t));
    ret = hal_gdma_chnl_alloc (pgdma_chnl, MultiBlkDis);    // default no-multiple block support

    if (ret == HAL_OK) {
        ret = hal_uart_stubs.hal_uart_tx_gdma_init(puart_adapter, pgdma_chnl);
        if (ret == HAL_OK) {
            puart_adapter->dcache_clean_by_addr = hal_cache_stubs.dcache_clean_by_addr;
            hal_gdma_chnl_init (pgdma_chnl);
//            hal_gdma_handshake_init (pgdma_chnl, pgdma_chnl->gdma_cfg.dest_per);
//            hal_gdma_irq_reg (pgdma_chnl, hal_uart_stubs.uart_tx_dma_irq_handler, puart_adapter);
        } else {
            DBG_UART_ERR("hal_uart_tx_gdma_init: GDMA init failed(%d)\r\n", ret);
            hal_gdma_chnl_free (pgdma_chnl);
        }
    } else {
        DBG_UART_ERR("hal_uart_tx_gdma_init: GDMA channel allocate failed(%d)\r\n", ret);
    }

    return ret;
}

/**
 *  @brief To de-initial the UART TX GDMA channel.
 *         Also will disable the UART TX DMA transfer mode.
 *
 *  @param[in]  puart_adapter  The UART adapter.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GDMA channel de-initialization OK.
 */
hal_status_t hal_uart_tx_gdma_deinit(phal_uart_adapter_t puart_adapter)
{
    hal_gdma_chnl_free (puart_adapter->ptx_gdma);
    return hal_uart_stubs.hal_uart_tx_gdma_deinit(puart_adapter);
}

/**
 *  @brief To initial a GDMA channel for the UART RX DMA mode transfer.
 *
 *  @param[in]  puart_adapter  The UART adapter.
 *  @param[in]  pgdma_chnl The GDMA channel adapter. It is use to control
 *              the GDMA channel transfer.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GDMA channel initialization OK.
 */
hal_status_t hal_uart_rx_gdma_init(phal_uart_adapter_t puart_adapter, phal_gdma_adaptor_t pgdma_chnl)
{
    hal_status_t ret;

	memset((void *)pgdma_chnl, 0, sizeof(hal_gdma_adaptor_t));
    ret = hal_gdma_chnl_alloc (pgdma_chnl, MultiBlkDis);    // default no-multiple block support

    if (ret == HAL_OK) {
        ret = hal_uart_stubs.hal_uart_rx_gdma_init(puart_adapter, pgdma_chnl);
        if (ret == HAL_OK) {
            puart_adapter->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;
//            puart_adapter->dcache_invalidate_by_addr = dcache_invalidate_by_addr_ual32;
            hal_gdma_chnl_init (pgdma_chnl);
//            hal_gdma_handshake_init (pgdma_chnl, pgdma_chnl->gdma_cfg.src_per);
//            hal_gdma_irq_reg (pgdma_chnl, hal_uart_stubs.uart_rx_dma_irq_handler, puart_adapter);
        } else {
            DBG_UART_ERR("hal_uart_rx_gdma_init: GDMA init failed(%d)\r\n", ret);
            hal_gdma_chnl_free (pgdma_chnl);
        }
    } else {
        DBG_UART_ERR("hal_uart_rx_gdma_init: GDMA channel allocate failed(%d)\r\n", ret);
    }

    return ret;
}

/**
 *  @brief To de-initial the UART RX GDMA channel.
 *         Also will disable the UART RX DMA transfer mode.
 *
 *  @param[in]  puart_adapter  The UART adapter.
 *
 *  @return     HAL_ERR_PARA:  Input arguments are invalid.
 *  @return     HAL_OK:  GDMA channel de-initialization OK.
 */
hal_status_t hal_uart_rx_gdma_deinit(phal_uart_adapter_t puart_adapter)
{
    hal_gdma_chnl_free (puart_adapter->prx_gdma);
    return hal_uart_stubs.hal_uart_rx_gdma_deinit(puart_adapter);
}

/**
 *  @brief To receive a block of data by the DMA mode.
 *         This function returns without waiting of data receiving done.
 *
 *  @param[in]  puart_adapter The UART adapter.
 *  @param[out] prx_buf The buffer for the data receiving.
 *  @param[in]  len  The length of data, in byte, are going to receive.
 *
 *  @return     HAL_OK: function execution OK.
 *  @return     HAL_BUSY: UART RX is in busy state, previous receiving is not finished yet.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_NO_RESOURCE: Multiple-block DMA channel allocation failed.
 */
hal_status_t hal_uart_dma_recv (phal_uart_adapter_t puart_adapter, uint8_t *prx_buf, uint32_t len)
{
    hal_gdma_adaptor_t *pgdma_chnl = puart_adapter->prx_gdma;
    hal_status_t ret;

    volatile uint32_t gdma_idx;

    if (pgdma_chnl == NULL) {
        DBG_UART_ERR("hal_uart_dma_recv: No GDMA Chnl\r\n");
        return HAL_NO_RESOURCE;
    }

    if (len > MAX_DMA_BLOCK_SIZE) {
        if (len <= MAX_DMA_BLOCK_SIZE*32) {
            // Need to use multiple block DMA
            if (pgdma_chnl->ch_num < 4) {
                // Current GDMA Channel didn't support multiple block DMA, re-allocate another one
                gdma_idx = pgdma_chnl->gdma_index;  // backup old GDMA index
                hal_gdma_chnl_free (pgdma_chnl);
                ret = hal_gdma_chnl_alloc (pgdma_chnl, MultiBlkEn);
                if (ret != HAL_OK) {
                    puart_adapter->prx_gdma = NULL;
                    DBG_UART_ERR("hal_uart_dma_recv: Err: re-allocate multiple block DMA channel failed(%d)\r\n", ret);
                    return ret;
                } else {
                    DBG_UART_INFO("hal_uart_dma_recv: re-allocate GDMA %u chnl %u\r\n", pgdma_chnl->gdma_index, pgdma_chnl->ch_num );
                    pgdma_chnl->pgdma_ch_lli = &uart_rx_gdma_ch_lli[puart_adapter->uart_idx][0];
                    hal_gdma_chnl_init (pgdma_chnl);
                }

                // Update GDMA handshake bit and IRQ handler(since may use different GDMA HW)
                if (gdma_idx != pgdma_chnl->gdma_index) {
                    // allocated to different GDMA HW, update the handshake bit
                    hal_gdma_handshake_init (pgdma_chnl, pgdma_chnl->gdma_cfg.src_per);
                }
                hal_gdma_irq_reg (pgdma_chnl, (irq_handler_t)hal_uart_stubs.uart_rx_dma_irq_handler, puart_adapter);
            }

        }else {
            DBG_UART_ERR("hal_uart_dma_recv: Err: RX Len(%lu) too big\n", len);
            return HAL_ERR_PARA;
        }
    }
    return hal_uart_stubs.hal_uart_dma_recv (puart_adapter, prx_buf, len);
}

/**
 *  @brief To send a block of data by the DMA transmission mode.
 *
 *  @param[in]  puart_adapter  The UART adapter.
 *  @param[in]  ptx_buf  The buffer of data to be transmitted.
 *  @param[in]  len  The length of data in bytes to be transmitted.
 *
 *  @return     HAL_OK: function execution OK.
 *  @return     HAL_BUSY: UART TX is in busy state, previous transmission is not finished yet.
 *  @return     HAL_ERR_PARA: Input arguments are invalid.
 *  @return     HAL_NO_RESOURCE: Multiple-block DMA channel allocation failed.
 */
hal_status_t hal_uart_dma_send (phal_uart_adapter_t puart_adapter, uint8_t *ptx_buf, uint32_t len)
{
    hal_gdma_adaptor_t *pgdma_chnl = puart_adapter->ptx_gdma;
    uint32_t block_size;
    hal_status_t ret;
    volatile uint32_t gdma_idx;

    if (pgdma_chnl == NULL) {
        DBG_UART_ERR("hal_uart_dma_send: No GDMA Chnl\r\n");
        return HAL_NO_RESOURCE;
    }

    if (((len & 0x03)==0) && (((uint32_t)(ptx_buf) & 0x03)==0)) {
        // 4-bytes aligned, move 4 bytes each transfer
        block_size = len >> 2;
    } else {
        block_size = len;
    }

    if (block_size > MAX_DMA_BLOCK_SIZE) {
        if (block_size <= MAX_DMA_BLOCK_SIZE*32){
            // Need to use multiple block DMA
            if (pgdma_chnl->ch_num < 4) {
                // Current GDMA Channel didn't support multiple block DMA, re-allocate another one
                DBG_UART_INFO("hal_uart_dma_send: re-allocate GDMA chnl to support Multi-Blk transfer\r\n");
                gdma_idx = pgdma_chnl->gdma_index;  // backup old GDMA index
                hal_gdma_chnl_free (pgdma_chnl);
                ret = hal_gdma_chnl_alloc (pgdma_chnl, MultiBlkEn);

                if (ret != HAL_OK) {
                    puart_adapter->ptx_gdma = NULL;
                    DBG_UART_ERR("hal_uart_dma_send: Err: re-allocate multiple block DMA channel failed(%d)\r\n", ret);
                    return ret;
                } else {
                    DBG_UART_INFO("hal_uart_dma_send: re-allocated GDMA %u chnl %u\r\n", pgdma_chnl->gdma_index, pgdma_chnl->ch_num );
                    pgdma_chnl->pgdma_ch_lli = &uart_tx_gdma_ch_lli[puart_adapter->uart_idx][0];
                    hal_gdma_chnl_init (pgdma_chnl);
                }

                // Update GDMA handshake bit and IRQ handler(since may use different GDMA HW)
                if (gdma_idx != pgdma_chnl->gdma_index) {
                    // allocated to different GDMA HW, update the handshake bit
                    hal_gdma_handshake_init (pgdma_chnl, pgdma_chnl->gdma_cfg.dest_per);
                }
                hal_gdma_irq_reg (pgdma_chnl, (irq_handler_t)hal_uart_stubs.uart_tx_dma_irq_handler, puart_adapter);
            }
        }else {
            DBG_UART_ERR("hal_uart_dma_send: Err: TX length too big(%lu)\r\n", len);
            return HAL_ERR_PARA;
        }
    }

    return hal_uart_stubs.hal_uart_dma_send (puart_adapter, ptx_buf, len);
}

/** @} */ /* End of group hs_hal_uart */

#endif  // end of "#if CONFIG_UART_EN"

