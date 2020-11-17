/**************************************************************************//**
 * @file     rtl8195bhp_irq.h
 * @brief    CMSIS Device System Header File for the Rtl8195B High Power platform.
 *           Defines the IRQ number for the System interrupts and Peripheral
 *           interrupts.
 * @version  V1.00
 * @date     2016-07-19
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

#ifndef _8195BH_IRQ_PRI_H_
#define _8195BH_IRQ_PRI_H_


#ifdef __cplusplus
 extern "C" {
#endif
/**
 * @addtogroup hs_hal_irq IRQ
 * @ingroup 8195bh_hal
 * @{
 * @brief The IRQ APIs of the HS platform.
 */

/// Number of interrupt for the system level, it's defined by the ARM Cortex-M CPU.
#define MAX_SYSTEM_IRQ_NUM                  16
/// Number of interrupt for peripheral devices on this platform.
#define MAX_PERIPHERAL_IRQ_NUM              32
/// Total number of interrupt on this platform.
#define MAX_VECTOR_TABLE_NUM                (MAX_SYSTEM_IRQ_NUM + MAX_PERIPHERAL_IRQ_NUM)

/* -------------------------  Interrupt Priority Definition  ------------------------ */
/**
  \brief  Default interrupt priority for external(peripheral devices) interrupts.
*/
enum IRQ_Priority {
    SystemOn_IRQPri             =  0,       /*!< 16 System Interrupt Priority              */
    TimerGroup0_IRQPri          =  9,       /*!< 17 Timer Group0 Interrupt Priority        */
    TimerGroup1_IRQPri          =  9,       /*!< 18 Timer Group1 Interrupt Priority        */
    GPIO_IRQPri                 =  6,       /*!< 19 GPIO Interrupt Priority                */
    PWM_IRQPri                  = 12,       /*!< 20 PWM Interrupt Priority                 */
    ADC_IRQPri                  = 10,       /*!< 21 A/D Convertor Interrupt Priority       */
    SGPIO_IRQPri                = 11,       /*!< 22 Serial-GPIO Interrupt Priority         */
    UART_IRQPri                 =  8,       /*!< 23 UART Interrupt Priority                */
    I2C_IRQPri                  = 13,       /*!< 24 I2C Interrupt Priority                 */
    SPI_IRQPri                  =  7,       /*!< 25 SPI Interrupt Priority                 */
    I2S_IRQPri                  =  6,       /*!< 26 I2S/PCM Interrupt Priority             */
    I3C_IRQPri                  = 12,       /*!< 27 I3C Interrupt Priority                 */
    USB_IRQPri                  = 10,       /*!< 28 USB_OTG Interrupt Priority             */
    SDIOH_IRQPri                = 14,       /*!< 29 SDIO Host Interrupt Priority           */
    SDIOD_IRQPri                = 11,       /*!< 30 SDIO Device Interrupt Priority         */
    MII_IRQPri                  =  9,       /*!< 31 MII (GMAC) Interrupt Priority          */
    WLAN_IRQPri                 =  7,       /*!< 32 WLan Interrupt Priority                */
    GDMA0_IRQPri                = 14,       /*!< 33 General-DMA 0 Interrupt Priority       */
    GDMA1_IRQPri                = 14,       /*!< 34 General-DMA 1 Interrupt Priority       */
    Crypto_IRQPri               = 13,       /*!< 35 Crypto engine Interrupt Priority       */
    FlashCtrl_IRQPri            =  6,       /*!< 36 SPI Flash Controller Interrupt Priority    */
    ICC_IRQPri                  =  5,       /*!< 37 Inter CPU Communication Interrupt Priority */
    ISP_IRQPri                  =  9,       /*!< 38 Image Signal Processor Interrupt Priority  */
    H264Enc_IRQPri              =  8,       /*!< 39 H264 Encoder Interrupt Priority        */
    VOE_IRQPri                  =  5,       /*!< 40 VOE Interrupt Priority                 */
    TFTCtrl_IRQPri              = 11,       /*!< 41 TFT Controller Interrupt Priority      */
    JPEG_IRQPri                 = 12,       /*!< 42 JPEG Interrupt Priority               */
    SGDMA0_IRQPri               = 9,        /*!< 43 Secure GDMA0 Interrupt Priority       */
    SGDMA1_IRQPri               = 10,       /*!< 44 Secure GDMA1 Interrupt Priority       */
    SCrypto_IRQPri              = 13,       /*!< 45 Secure Crypto engine Interrupt Priority    */
    SLowPri_IRQPri              = 14,       /*!< 46 Secure low priority Interrupt Priority     */
    LowPri_IRQPri               = 15        /*!< 47 Low priority Interrupt Priority       */
};

/**
  \brief  The data structure of the IRQ API function table.
          For RAM code can hook another optional IRQ APIs for ROM HAL code.
*/
typedef struct hal_irq_api_s {
    void     (*irq_enable)(int32_t irqn);           /*!< enable interrupt */
    void     (*irq_disable)(int32_t irqn);          /*!< disable interrupt */
    void     (*irq_set_vector)(int32_t irqn, uint32_t vector);      /*!< set interrupt vector */
    uint32_t (*irq_get_vector)(int32_t irqn);       /*!< get interrupt vector */
    void     (*irq_set_priority)(int32_t irqn, uint32_t priority);  /*!< set interrupt priority */
    uint32_t (*irq_get_priority)(int32_t irqn);     /*!< get interrupt priority */
    void     (*irq_set_pending)(int32_t irqn);      /*!< set pending interrupt */
    uint32_t (*irq_get_pending)(int32_t irqn);      /*!< get pending interrupt */
    void     (*irq_clear_pending)(int32_t irqn);    /*!< clear pending interrupt */
    void     (*interrupt_enable)(void);             /*!< enable all interrupts */
    void     (*interrupt_disable)(void);            /*!< disable all interrupts */
} hal_irq_api_t;

/**
  \brief  Function type of interrupt handler.
*/
typedef void (*int_vector_t) (void);

/**
  \brief  User application call back function for an interrupt.
*/
typedef void (*irq_handler_t)(void *data);

typedef struct irq_config_s {
    irq_handler_t   irq_fun;
    void            *data;
    int16_t         irq_num;
    uint16_t        priority;
} irq_config_t, *pirq_config_t;

/**
  \brief  The structure of the handler for stack back trace. 
          It is used to list of the call trace when a hard fault is occurred.
*/
typedef struct fault_handler_back_trace_s {
    uint32_t msp_top;       /*!< the top address of the MSP */
    uint32_t msp_limit;     /*!< the end address of the MSP */
    uint32_t psp_max_size;  /*!< the maximum size of process stack */
    uint32_t *ptxt_range_list;  /*!< point to the array for the list of text code range */
    uint32_t trace_depth;   /*!< the size of the trace buffer */
    uint32_t *ptrace_buf;   /*!< point to the trace buffer */
} fault_handler_back_trace_t, *pfault_handler_back_trace_t;


/**
  \brief  The stubs function table type of the IRQ HAL functions in ROM.
*/
typedef struct hal_int_vector_func_stubs_s {
    int_vector_t *ram_vector_table;
    hal_irq_api_t *pirq_api_tbl;

    void (*hal_vector_table_init)(uint32_t stack_ptr, int_vector_t *vector_tbl);
    void (*hal_irq_api_init)(hal_irq_api_t *pirq_api);
    void (*hal_irq_enable)(int32_t irqn);
    void (*hal_irq_disable)(int32_t irqn);
    void (*hal_irq_set_vector)(int32_t irqn, uint32_t vector);
    uint32_t (*hal_irq_get_vector)(int32_t irqn);
    void (*hal_irq_set_priority)(int32_t irqn, uint32_t priority);
    uint32_t (*hal_irq_get_priority)(int32_t irqn);
    void (*hal_irq_set_pending)(int32_t irqn);
    uint32_t (*hal_irq_get_pending)(int32_t irqn);
    void (*hal_irq_clear_pending)(int32_t irqn);
    void (*hal_irq_unreg)(int32_t irqn);

    pfault_handler_back_trace_t *ppbk_trace_hdl;
    pfault_handler_back_trace_t *ppbk_trace_hdl_ns;

    uint32_t reserved[2];  // reserved space for next ROM code version function table extending.
} hal_int_vector_func_stubs_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup hs_hal_irq_rom_func IRQ ROM APIs.
 * @{
 */

void hal_vector_table_init_rtl8195bhp(uint32_t stack_ptr, int_vector_t *vector_tbl);

void _default_handler_rtl8195bhp(void);
void hal_irq_api_init_rtl8195bhp(hal_irq_api_t *pirq_api);
void hal_irq_enable_rtl8195bhp(int32_t irqn);
void hal_irq_disable_rtl8195bhp(int32_t irqn);
void hal_irq_set_vector_rtl8195bhp(int32_t irqn, uint32_t vector);
uint32_t hal_irq_get_vector_rtl8195bhp(int32_t irqn);
void hal_irq_set_priority_rtl8195bhp(int32_t irqn, uint32_t priority);
uint32_t hal_irq_get_priority_rtl8195bhp(int32_t irqn);
void hal_irq_set_pending_rtl8195bhp(int32_t irqn);
uint32_t hal_irq_get_pending_rtl8195bhp(int32_t irqn);
void hal_irq_clear_pending_rtl8195bhp(int32_t irqn);
void hal_irq_unreg_rtl8195bhp(int32_t irqn);
void hal_interrupt_enable_rtl8195bhp(void);
void hal_interrupt_disable_rtl8195bhp(void);

/** @} */ /* End of group hs_hal_irq_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */


/** @} */ /* End of group hs_hal_irq */

#ifdef __cplusplus
}
#endif

#endif //_8195BH_IRQ_PRI_H_


