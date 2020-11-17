/**************************************************************************//**
 * @file     hal_gdma.h
 * @brief    Provide stub functions for RAM code to access GDMA ROM functions.
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

#ifndef _HAL_GDMA_H_
#define _HAL_GDMA_H_
#include "cmsis.h"

#ifdef  __cplusplus
extern "C"
{
#endif

extern const hal_gdma_func_stubs_t hal_gdma_stubs;

/**

        \addtogroup ls_hal_gdma_ram_func GDMA HAL RAM APIs
        \ingroup ls_hal_gdma
        \brief The GDMA HAL APIs. Functions become an interface between API functions and ROM codes.
        @{
*/


/** \brief Description of hal_gdma_on
 *
 *    hal_gdma_on is used to turn on GDMA IP.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_on(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_on(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_off
 *
 *    hal_gdma_off is used to turn off GDMA IP.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_off(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_off(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_chnl_en
 *
 *    hal_gdma_chnl_en is used to enable the GDMA channel, then GDMA transfer will start.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_chnl_en (phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_chnl_en (phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_chnl_dis
 *
 *    hal_gdma_chnl_dis is used to disable the GDMA channel, then GDMA transfer stops.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_chnl_dis (phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_chnl_dis (phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_isr_en
 *
 *    hal_gdma_isr_en is used to enable(unmask) GDMA ISR Type.
 *    Typically we will unmask Transfer type interrupt to notify all transfer are complete
 *    and Error type interrupt to inform us an error occurs during transmission
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_isr_en(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_isr_en(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_isr_dis
 *
 *    hal_gdma_isr_dis is used to mask GDMA ISR type.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_isr_dis(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_isr_dis(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_clean_pending_isr
 *
 *    hal_gdma_clean_pending_isr is used to clear pending interrupt regardless of ISR types.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_clean_pending_isr(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_clean_pending_isr(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_clean_chnl_isr
 *
 *    hal_gdma_clean_chnl_isr is used to clean pending interrupts which we unmask .
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_clean_chnl_isr (phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_clean_chnl_isr (phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_chnl_setting
 *
 *    hal_gdma_chnl_setting is used to set GDMA registers.
 *    Four registers are configured according to information carried by the adaptor:
 *    SAR(Source address), DAR(Destination address), CTL(Control register), CFG(Configuration register)
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return hal_statu_t.
 */
__STATIC_INLINE hal_status_t hal_gdma_chnl_setting(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    return hal_gdma_stubs.hal_gdma_chnl_setting(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_query_dar
 *
 *    hal_gdma_query_dar is used to get current destination address.
 *    The address may not be accurate. It is recommended to use query receive/send byte functions to get correct information.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return u32: current destination address .
 */
__STATIC_INLINE u32 hal_gdma_query_dar(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    return hal_gdma_stubs.hal_gdma_query_dar(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_query_sar
 *
 *    hal_gdma_query_sar is used to get current source address.
 *    The address may not be accurate. It is recommended to use query receive/send byte functions to get correct information.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return u32: current source address .
 */
__STATIC_INLINE u32 hal_gdma_query_sar(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    return hal_gdma_stubs.hal_gdma_query_sar(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_query_send_bytes
 *
 *    hal_gdma_query_send_bytes is used to query how many bytes GDMA sent when it stops or finishes.
 *    Source : Memory , Destination : Peripheral. Query how many bytes being sent from the source.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return u32: Number of bytes already sent from the source.
 */
__STATIC_INLINE u32 hal_gdma_query_send_bytes(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    return hal_gdma_stubs.hal_gdma_query_send_bytes(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_query_recv_bytes
 *
 *    hal_gdma_query_recv_bytes is used to query how many bytes GDMA received when the transmission is complete or aborted.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return u32: Number of bytes already received by the destination.
 */
__STATIC_INLINE u32 hal_gdma_query_recv_bytes(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    return hal_gdma_stubs.hal_gdma_query_recv_bytes(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_query_chnl_en
 *
 *    hal_gdma_query_chnl_en is used to check whether the channel is enabled or not.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return BOOL: 1: Channel is enabled, 0: Channel is disabled.
 */
__STATIC_INLINE BOOL hal_gdma_query_chnl_en (phal_gdma_adaptor_t phal_gdma_adaptor)
{
    return hal_gdma_stubs.hal_gdma_query_chnl_en (phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_chnl_register
 *
 *    hal_gdma_chnl_register is used to manage and register GDMA channel.
 *    It will check the viability of the target channel.
 *    If no one occupies this channel, the target channel is registered so that others cannot use this one.
 *    The GDMA clock is enabled and the reset is released if target GDMA has not been used before(GDMA is off).
 *
 *   \param u8 gdma_index:      The target GDMA, could be GDMA0 or GDMA1.
 *   \param u8 chnl_num:      The target GDMA channel, could be 0~5.
 *
 *   \return hal_status.
 */
__STATIC_INLINE hal_status_t hal_gdma_chnl_register(u8 gdma_index, u8 chnl_num)
{
    return hal_gdma_stubs.hal_gdma_chnl_register(gdma_index, chnl_num);
}

/** \brief Description of hal_gdma_chnl_unregister
 *
 *    hal_gdma_chnl_unregister is used to manage and unregister GDMA channel.
 *    When the transfer is complete and the channel is no long used, we can release this channel by unregistering it.
 *    The GDMA clock is disabled if no one uses this GDMA.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return hal_status.
 */
__STATIC_INLINE hal_status_t hal_gdma_chnl_unregister (phal_gdma_adaptor_t phal_gdma_adaptor)
{
    return hal_gdma_stubs.hal_gdma_chnl_unregister (phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_chnl_alloc
 *
 *    hal_gdma_chnl_alloc is used to determine viable channels and check which channel can be allocated one by one.
 *    If the channel is verified by hal_gdma_chnl_register_rtl8195blp that can be allocated,
 *    the channel is assigned to the gdma adaptor.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor   :      The pointer of GDMA adaptor.
 *
 *   \return hal_status_t.
 */
__STATIC_INLINE hal_status_t hal_gdma_chnl_alloc (phal_gdma_adaptor_t phal_gdma_adaptor)
{
    return hal_gdma_stubs.hal_gdma_chnl_alloc (phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_chnl_init
 *
 *    hal_gdma_chnl_init is used to initialize register bases and channel related settings when the target channel is specified.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return hal_status_t.
 */
__STATIC_INLINE hal_status_t hal_gdma_chnl_init(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    return hal_gdma_stubs.hal_gdma_chnl_init(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_chnl_irq_free
 *
 *    hal_gdma_chnl_irq_free is used to disable GDMA IRQ for the corresponding GDMA.
 *    Before disabling the GDMA IRQ, it will check all channels of the GDMA are not used.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_chnl_irq_free (phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_chnl_irq_free (phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_chnl_free
 *
 *    hal_gdma_chnl_free is used to release channel completely.
 *    The channel is unregistered and its IRQ would also be disabled.
 *    At the end of this function, the gdma adaptor is marked to have no channel.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_chnl_free (phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_chnl_free (phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_memcpy_irq_hook
 *
 *    hal_gdma_memcpy_irq_hook is used to initialize the callback function and its parameter for memcpy transfer.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *   \param gdma_callback_t gdma_cb_func:      The pointer of the callback function.
 *   \param void* gdma_cb_data:      The pointer of the paramter of the callback function.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_memcpy_irq_hook(phal_gdma_adaptor_t phal_gdma_adaptor, gdma_callback_t gdma_cb_func, void *gdma_cb_data)
{
    hal_gdma_stubs.hal_gdma_memcpy_irq_hook(phal_gdma_adaptor, gdma_cb_func, gdma_cb_data);
}

/** \brief Description of hal_gdma_memcpy_irq_handler
 *
 *    hal_gdma_memcpy_irq_handler is the memcpy irq handler function.
 *    Once GDMA identifies which channel triggers interrupt, it then enters this function to jump to callback function of this channel.
 *    The IRQ flow is shown below:
 *    GDMA_IRQHandler(This function is reigstered to NVIC IRQ vector)-> hal_gdma_memcpy_irq_handler_rtl8195blp
 *      -> channel callback function(callback function carried by hal_gdma_memcpy_irq_hook_rtl8195blp).
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_memcpy_irq_handler(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_memcpy_irq_handler(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_irq_handler
 *
 *    hal_gdma_irq_handler is used to handle GDMA interrupt.
 *    This function is the first function being called when the interrupt is triggered.
 *    It is also the function to be registered in NVIC.
 *    Since all channels share the same interrupt signal, this function will read the vendor register to identify which
 *    channel triggers the interrupt. It then jump to the corresponding channel irq handler function.
 *
 *   \param void.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_irq_handler(void)
{
    hal_gdma_stubs.hal_gdma_irq_handler();
}

/** \brief Description of hal_gdma_irq_set_priority
 *
 *    hal_gdma_irq_set_priority is used to set irq priority of the target GDMA.
 *
 *   \param u32 irq_priority:      The priority.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_irq_set_priority(u32 irq_priority)
{
    hal_gdma_stubs.hal_gdma_irq_set_priority(irq_priority);
}

/** \brief Description of hal_gdma_irq_reg
 *
 *    hal_gdma_irq_reg is used to initialize irq number, channel irq handler function and parameter.
 *    Each periperhal which interacts with GDMA, including GDMA itself for memcpy, should call this function to initialize its GDMA channel irq handler function.
 *    The IRQ is enabled if it was not enabled before.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *   \param irq_handler_t irq_handler:      The pointer of GDMA irq handler.
 *   \param void* irq_data:      The pointer of the irq parameter.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_irq_reg(phal_gdma_adaptor_t phal_gdma_adaptor, irq_handler_t irq_handler, void *irq_data)
{
    hal_gdma_stubs.hal_gdma_irq_reg(phal_gdma_adaptor, irq_handler, irq_data);
}

/** \brief Description of hal_gdma_group_init
 *
 *    hal_gdma_group_init is used to assign the address of gdma group adaptor and initialize global IRQ setting.
 *    GDMA group adoptor plays an important role to manage channel usage, the address of the group adaptor is carried via this function.
 *    The IRQ handler, IRQ number are fixed values and should not be modified, so we initialize these parameters before any other gdma functions.
 *
 *   \param phal_gdma_group_t pgdma_group:      The pointer of GDMA group adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_group_init(phal_gdma_group_t pgdma_group)
{
    hal_gdma_stubs.hal_gdma_group_init(pgdma_group);
}

/** \brief Description of hal_gdma_memcpy_init
 *
 *    hal_gdma_memcpy_init is used to initialize memory copy transfer by gdma.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor   :      The pointer of GDMA adaptor.
 *
 *   \return BOOL: 1: Succeed 0: Fail.
 */
__STATIC_INLINE void hal_gdma_memcpy_init(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_memcpy_init(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_memcpy_deinit
 *
 *    hal_gdma_memcpy_deinit is used to deinit the gdma channel after the memcpy is complete and no longer needed.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_memcpy_deinit(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_memcpy_deinit(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_transfer_start
 *
 *    hal_gdma_transfer_start consists of several steps:
 *    Turn on GDMA IP-> Enable ISR(Unmask)->Set GDMA registers->Enable channel to start a transfer
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_transfer_start(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_transfer_start(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_memcpy
 *
 *    hal_gdma_memcpy is used to configure gdma setting for the current transfer and start the transfer at the end of the function.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor   :      The pointer of GDMA adaptor.
 *   \param void *pdest                             :      The destination address.
 *   \param void *psrc                              :      The source address.
 *   \param u32 len                                 :      The transfer length, the unit is byte.
 *
 *   \return hal_status_t.
 */
__STATIC_INLINE hal_status_t hal_gdma_memcpy(phal_gdma_adaptor_t phal_gdma_adaptor, void *pdest, void *psrc, u32 len)
{
    return hal_gdma_stubs.hal_gdma_memcpy(phal_gdma_adaptor, pdest, psrc, len);
}

/** \brief Description of hal_gdma_abort
 *
 *    hal_gdma_abort is used to stop gdma transfer.
 *    Once the transfer is terminated, it cannot resume.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_abort(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_abort(phal_gdma_adaptor);
}

/** \brief Description of hal_gdma_chnl_reset
 *
 *    hal_gdma_chnl_reset is used to reset gdma channel.
 *
 *   \param phal_gdma_adaptor_t phal_gdma_adaptor:      The pointer of GDMA adaptor.
 *
 *   \return void.
 */
__STATIC_INLINE void hal_gdma_chnl_reset(phal_gdma_adaptor_t phal_gdma_adaptor)
{
    hal_gdma_stubs.hal_gdma_chnl_reset(phal_gdma_adaptor);
}

/** *@} */ /* End of group hs_hal_gdma_ram_func */


#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_GDMA_H_"


