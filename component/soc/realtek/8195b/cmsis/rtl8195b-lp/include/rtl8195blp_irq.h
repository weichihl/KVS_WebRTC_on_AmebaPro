/**************************************************************************//**
 * @file     rtl8195blp_irq.h
 * @brief    CMSIS Device System Header File for the Rtl8195B Low Power platform.
 *           Defines the IRQ API and priority.
 * @version  V1.00
 * @date     2016-05-17
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

#ifndef _8195BLP_IRQ_H_
#define _8195BLP_IRQ_H_

#ifdef __cplusplus
 extern "C" {
#endif
/**
 * @addtogroup ls_hal_irq IRQ
 * @ingroup 8195bl_hal
 * @{
 * @brief The IRQ APIs of the LS platform.
 */

/// Number of interrupt for the system level, it's defined by the ARM Cortex-M CPU.
#define MAX_SYSTEM_IRQ_NUM                  16
/// Number of interrupt for peripheral devices on this platform.
#define MAX_PERIPHERAL_IRQ_NUM              16
/// Total number of interrupt on this platform.
#define MAX_VECTOR_TABLE_NUM                32

/**
 * \brief  Default interrupt priority for external(peripheral devices) interrupts.
 */
enum IRQ_Priority {
    SystemOn_IRQPri                 =  0,       /*!< System Interrupt Priority                   */
    TimerGroup0_IRQPri              =  3,       /*!< Timer Group0 Interrupt Priority             */
    GPIO_IRQPri                     =  2,       /*!< GPIO Interrupt Priority                     */
    PWM_IRQPri                      =  3,      /*!< PWM Interrupt Priority                      */
    ADC_IRQPri                      =  3,      /*!< A/D Convertor Interrupt Priority            */
    Comp_IRQPri                     =  3,      /*!< Comparator Interrupt Priority            */
    SGPIO_IRQPri                    =  2,       /*!< Serial-GPIO Interrupt Priority              */
    UART_IRQPri                     =  3,      /*!< UART Interrupt Priority                     */
    I2C_IRQPri                      =  3,      /*!< I2C Interrupt Priority                      */
    GDMA_IRQPri                     =  1,       /*!< General-DMA Interrupt Priority              */
    ICC_IRQPri                      =  1,       /*!< Inter CPU Communication Interrupt Priority  */
    QDec_IRQPri                     =  3,       /*!< Quadrature Decoder Interrupt  Priority      */
    CIR_IRQPri                      =  3,       /*!< Consumer IR Interrupt  Priority             */
    WLan0_IRQPri                    =  2,       /*!< WLan Interrupt 0  Priority                  */
    WLan1_IRQPri                    =  2,       /*!< WLan Interrupt 1  Priority                  */
    LowPri_IRQPri                   =  2       /*!< Low Priority Interrupt Priority             */
};

/**
 * \brief  Function type of interrupt handler.
 */
typedef void (*int_vector_t) (void);

/**
 * \brief  User application call back function for an interrupt.
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
    uint32_t msp_start;     /*!< the start address of the MSP */
    uint32_t msp_limit;     /*!< the end address of the MSP */
    uint32_t psp_limit;     /*!< the end address of the current PSP */
    uint32_t *ptxt_range_list;  /*!< point to the array for the list of text code range */
    uint32_t trace_depth;   /*!< the size of the trace buffer */
    uint32_t *ptrace_buf;   /*!< point to the trace buffer */
} fault_handler_back_trace_t, *pfault_handler_back_trace_t;

/**
 * \brief  The data structure of the IRQ API function table.
 *         For RAM code can hook another optional IRQ APIs for ROM HAL code.
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
} hal_irq_api_t;

/**
 * \brief  The stubs function table type of the IRQ HAL functions in ROM.
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
    uint32_t reserved[7];  // reserved space for next ROM code version function table extending.
} hal_int_vector_func_stubs_t;

/// @cond DOXYGEN_ROM_HAL_API

/**
 * @addtogroup ls_hal_irq_rom_func IRQ ROM APIs.
 * @{
 */

void hal_vector_table_init_rtl8195blp(uint32_t stack_ptr, int_vector_t *vector_tbl);
void _default_handler_rtl8195blp(void);
void hal_irq_api_init_rtl8195blp(hal_irq_api_t *pirq_api);
void hal_irq_enable_rtl8195blp(int32_t irqn);
void hal_irq_disable_rtl8195blp(int32_t irqn);
void hal_irq_set_vector_rtl8195blp(int32_t irqn, uint32_t vector);
uint32_t hal_irq_get_vector_rtl8195blp(int32_t irqn);
void hal_irq_set_priority_rtl8195blp(int32_t irqn, uint32_t priority);
uint32_t hal_irq_get_priority_rtl8195blp(int32_t irqn);
void hal_irq_set_pending_rtl8195blp(int32_t irqn);
uint32_t hal_irq_get_pending_rtl8195blp(int32_t irqn);
void hal_irq_clear_pending_rtl8195blp(int32_t irqn);
void hal_irq_unreg_rtl8195blp(int32_t irqn);

/** @} */ /* End of group ls_hal_irq_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */


/** @} */ /* End of group ls_hal_irq */

#ifdef __cplusplus
}
#endif

#endif //_8195BLP_IRQ_H_


