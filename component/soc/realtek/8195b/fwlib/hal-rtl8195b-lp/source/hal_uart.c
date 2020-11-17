/**************************************************************************//**
 * @file     rtl8195blp_uart.c
 * @brief    This file implements the UART HAL functions.
 * 
 * @version  V1.00
 * @date     2016-05-26
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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
#include "hal_gpio.h"
#include "hal_pinmux.h"
#include "hal_irq.h"
     
#if CONFIG_UART_EN
/** 
 * @addtogroup ls_hal_uart UART
 * @{
 */

/** 
 *  @brief To initial a UART port adapter. This function must be called before any UART port
 *         operation. This function will do:
 *           - enable the UART hardware.
 *           - register the interrupt handler.
 *           - configures the pin mux.
 *
 *  @param[in]  puart_adapter  The UART adapter. 
 *  @param[in]  uart_idx The UART index. The value can be 0 .. 1.
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
                            uint8_t pin_sel, phal_uart_defconfig_t pconfig)
{
    uint32_t rx_pin;
    hal_status_t ret;
    
    // RX Pin pull-high to prevent this folating on this pin
    if (uart_idx == 0) {
        rx_pin = PIN_A7;
    } else {
        rx_pin = PIN_A0;
    }
    hal_gpio_pull_ctrl (rx_pin, Pin_PullUp);
    
    //* Init the UART port hadware
    ret = hal_uart_stubs.hal_uart_init (puart_adapter, uart_idx, pconfig);
    if (ret == HAL_OK) {
        hal_irq_enable (UART_IRQn);
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
    uint32_t rx_pin;

    if (puart_adapter->uart_idx == 0) {
        rx_pin = PIN_A7;
    } else {
        rx_pin = PIN_A0;
    }

    hal_uart_stubs.hal_uart_deinit (puart_adapter);
    
    // Release RX Pin pull control
    hal_gpio_pull_ctrl (rx_pin, Pin_PullNone);
}

/** 
 *  @brief To wait TX FIFO is writable and then send a char.
 *
 *  @param[in]  puart_adapter The UART adapter.
 *  @param[in]  tx_data The data(1 byte) to be send.
 *
 *  @returns    void.
 */
void hal_uart_wputc (phal_uart_adapter_t puart_adapter, u8 tx_data)
{
#if defined(CONFIG_BUILD_RAM) && (CHIP_VER == CHIP_A_CUT)
    uint32_t tx_fifo_lv;

    do {
        tx_fifo_lv = puart_adapter->base_addr->tflvr_b.tx_fifo_lv;
    } while ((tx_fifo_lv != puart_adapter->base_addr->tflvr_b.tx_fifo_lv) || (tx_fifo_lv >= (Uart_Tx_FIFO_Size - 1)));
    puart_adapter->base_addr->thr = tx_data;
#else
    while (puart_adapter->base_addr->tflvr_b.tx_fifo_lv >= (Uart_Tx_FIFO_Size - 1));
    puart_adapter->base_addr->thr = tx_data;
#endif
}

/** @} */ /* End of group ls_hal_uart */

#endif

