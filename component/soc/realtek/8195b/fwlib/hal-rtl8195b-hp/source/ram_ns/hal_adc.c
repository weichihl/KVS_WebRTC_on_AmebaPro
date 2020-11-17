/**************************************************************************//**
 * @file     hal_adc.c
 * @brief    This file implements the ADC HAL functions.
 *
 * @version  V1.00
 * @date     2017-01-18
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

#include "cmsis.h"
#include "hal_adc.h"
#include "hal_gdma.h"
#include "hal_pinmux.h"
#include "hal_cache.h"
#include "hal_timer.h"
#include "hal_sys_ctrl.h"
#include "hal_efuse.h"
#include "hal_irq.h"
#include "rtl8195bhp_syson.h"

#if defined ( __GNUC__ )
#include <limits.h>
#else
#include "__limits.h"
#endif

#ifdef CONFIG_ADC_EN

uint8_t hp_adc_ch_pin_en_sts;

#if   defined ( __CC_ARM )                                            /* ARM Compiler 4/5 */
extern hal_adc_func_stubs_t Image$$_STUB_ADC$$Base;     // symbol from linker script
#define __rom_stubs_hal_adc Image$$_STUB_ADC$$Base
#elif defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)       /* ARM Compiler 6 */
extern hal_adc_func_stubs_t Image$$_STUB_ADC$$Base;     // symbol from linker script
#define __rom_stubs_hal_adc Image$$_STUB_ADC$$Base
#elif defined ( __GNUC__ )
extern hal_adc_func_stubs_t __rom_stubs_hal_adc;     // symbol from linker script
#elif defined ( __ICCARM__ )
extern hal_adc_func_stubs_t __rom_stubs_hal_adc;     // symbol from linker script
#endif

//volatile uint8_t analog_func_en_cnt  = 0;
volatile uint8_t lp_adc_ch_pin_en_sts  = 0;
extern const hal_adc_func_stubs_t hal_adc_stubs;
//extern uint16_t hal_adc_single_read_rtl8195bhp_patch (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no);

/**
 * @addtogroup hs_hal_adc ADC
 * @{
 */

/** \brief Description of hal_adc_pwr_init
 *
 *    hal_adc_pwr_init is used for adc power initialization.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:    Pointer to ADC control adapter.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_adc_pwr_init (hal_adc_adapter_t *phal_adc_adapter)
{
#if (CHIP_VER == CHIP_A_CUT) && (defined(CONFIG_BUILD_RAM))
    return hal_adc_pwr_init_rtl8195bhp_patch(phal_adc_adapter);
#else
    return __rom_stubs_hal_adc.hal_adc_pwr_init(phal_adc_adapter);
#endif
}


/** \brief Description of hal_adc_pwr_deinit
 *
 *    hal_adc_pwr_deinit is used for adc power de-initialization.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_adc_pwr_deinit (hal_adc_adapter_t *phal_adc_adapter)
{
    return __rom_stubs_hal_adc.hal_adc_pwr_deinit(phal_adc_adapter);
}

/** \brief Description of hal_adc_pin_init
 *
 *    hal_adc_pin_init is used for adc pinmux initialization and register.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_adc_pin_init(hal_adc_adapter_t *phal_adc_adapter)
{
    uint8_t adc_ch_cnt;
    hal_status_t retv;
    uint32_t reg_tmp;
    
    for (adc_ch_cnt = HP_ADC_EXCH_NO; adc_ch_cnt < HP_ADC_CH_NO; adc_ch_cnt++) {
        if (phal_adc_adapter->plft_dat.pin_en.w & ((uint32_t)0x01 << adc_ch_cnt)) {
            hal_syson_adc_ctrl(adc_ch_cnt, ENABLE);

            if ((hp_adc_ch_pin_en_sts & ((uint32_t)0x01 << adc_ch_cnt)) == 0) {
                retv = hal_pinmux_register((io_pin_t *)&(__rom_stubs_hal_adc.hal_adc_pin_list[adc_ch_cnt]), PID_ADC0+adc_ch_cnt);
                //reg_tmp = HAL_READ32(0x40000000, 0x288);
                //reg_tmp &= ~(0x01 << (16 + adc_ch_cnt - HP_ADC_EXCH_NO));
                //HAL_WRITE32(0x40000000, 0x288, reg_tmp);
                /* (adc_ch_cnt - HP_ADC_EXCH_NO) is for patch */
                //hal_pin_pwrup((io_pin_t *)&(__rom_stubs_hal_adc.hal_adc_pin_list[adc_ch_cnt]), adc_ch_cnt - HP_ADC_EXCH_NO);
                reg_tmp = HAL_READ32(0x40000000, 0x288);
                reg_tmp &= ~(0x01 << (16 + adc_ch_cnt - HP_ADC_EXCH_NO));
                HAL_WRITE32(0x40000000, 0x288, reg_tmp);
                
                /* power down gpio */
                //reg_tmp = HAL_READ32(0x40000000, 0x280);
                //reg_tmp |= BIT6;
                //HAL_WRITE32(0x40000000, 0x280, reg_tmp);
                
                if (retv != HAL_OK) {
                    return retv;
                }
                reg_tmp = HAL_READ32(0x40000000, 0x230);
                reg_tmp |= (BIT0 << (8 + adc_ch_cnt - HP_ADC_EXCH_NO));
                HAL_WRITE32(0x40000000, 0x230, reg_tmp);
                if (retv != HAL_OK) {
                    return retv;
                }

                hp_adc_ch_pin_en_sts |= ((uint32_t)0x01 << adc_ch_cnt);
            } else {
                DBG_ADC_WARN("ch-%d pin has been enabled.", adc_ch_cnt);
                DBG_ADC_WARN("adc pin sts: %x\n", hp_adc_ch_pin_en_sts);
            }
        }
    }

    //reg_tmp = HAL_READ32(0x40000000, 0x288);
    //reg_tmp &= 0xFFF0FFFF;
    //HAL_WRITE32(0x40000000, 0x288, reg_tmp);
    return HAL_OK;
}

/** \brief Description of hal_adc_pin_deinit
 *
 *    hal_adc_pin_deinit is used for adc pinmux un-initialization and un-register.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:       Pointer to ADC control adapter.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_adc_pin_deinit(hal_adc_adapter_t *phal_adc_adapter)
{
    uint8_t adc_ch_cnt;
    hal_status_t retv = HAL_OK;
    uint32_t reg_tmp;

    for (adc_ch_cnt = HP_ADC_EXCH_NO; adc_ch_cnt < HP_ADC_CH_NO; adc_ch_cnt++) {
        if (!(phal_adc_adapter->plft_dat.pin_en.w & ((uint32_t)0x01 << adc_ch_cnt))) {
            hal_syson_adc_ctrl(adc_ch_cnt, DISABLE);

            if ((hp_adc_ch_pin_en_sts & ((uint32_t)0x01 << adc_ch_cnt)) != 0) {
                retv = hal_pinmux_unregister((io_pin_t *)&(__rom_stubs_hal_adc.hal_adc_pin_list[adc_ch_cnt]), PID_ADC0+adc_ch_cnt);
                if (retv != HAL_OK) {
                    return retv;
                }

                /* (adc_ch_cnt - HP_ADC_EXCH_NO) is for patch */
                //hal_pin_pwrdwn((io_pin_t *)&(__rom_stubs_hal_adc.hal_adc_pin_list[adc_ch_cnt]), adc_ch_cnt - HP_ADC_EXCH_NO);
                reg_tmp = HAL_READ32(0x40000000, 0x288);
                reg_tmp |= (0x01 << (16 + adc_ch_cnt - HP_ADC_EXCH_NO));
                HAL_WRITE32(0x40000000, 0x288, reg_tmp);
                
                reg_tmp = HAL_READ32(0x40000000, 0x230);
                reg_tmp &= ~(BIT0 << (8 + adc_ch_cnt - HP_ADC_EXCH_NO));
                HAL_WRITE32(0x40000000, 0x230, reg_tmp);
                if (retv != HAL_OK) {
                    return retv;
                }
                hp_adc_ch_pin_en_sts &= ~((uint32_t)0x01 << adc_ch_cnt);
            } else {
                DBG_ADC_WARN("ch-%d pin is NOT disabled.", adc_ch_cnt);
                DBG_ADC_WARN("since comparator is NOT disabled.");
                DBG_ADC_WARN("adc pin sts: %x\n", hp_adc_ch_pin_en_sts);
            }
        }
    }

    if (hp_adc_ch_pin_en_sts == 0) {
        /* release digital gpio */
        /* power up gpio */
        reg_tmp = HAL_READ32(0x40000000, 0x280);
        reg_tmp &= ~BIT6;
        HAL_WRITE32(0x40000000, 0x280, reg_tmp);
    }
    
    return HAL_OK;
}

/** \brief Description of hal_adc_init
 *
 *    hal_adc_init is used for adc initialization including pinmux control.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_adc_init (hal_adc_adapter_t *phal_adc_adapter)
{
    hal_status_t retv;

    hal_adc_pwr_init(phal_adc_adapter);
    /* Pinmux Initialization */
    retv = hal_adc_pin_init(phal_adc_adapter);
    if (retv != HAL_OK) {
        return retv;
    } else {
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
		retv = __rom_stubs_hal_adc.hal_adc_init(phal_adc_adapter);
		// additional patch
        {
            uint32_t reg_tmp;
            uint8_t cnt_tmp;
            SYSON->hs_adc_ctrl_b.ctrl_msr_sel = 1;
            /* modify ad2, ad3 */
            reg_tmp = SYSON->hs_adc_ctrl2;
            DBG_ADC_INFO("ana2: %x\n", reg_tmp);
            reg_tmp = 0x21086310;
            SYSON->hs_adc_ctrl2 = reg_tmp;
            DBG_ADC_INFO("ana2 new: %x\n", reg_tmp);
            
            reg_tmp = SYSON->hs_adc_ctrl3;
            DBG_ADC_INFO("ana3: %x\n", reg_tmp);
            reg_tmp = 0x02082110;
            SYSON->hs_adc_ctrl3 = reg_tmp;
            DBG_ADC_INFO("ana3 new: %x\n", reg_tmp);
            
            reg_tmp = SYSON->hs_adc_ctrl0;
            DBG_ADC_INFO("ana0: %x\n", reg_tmp);
            reg_tmp |= BIT1;
            SYSON->hs_adc_ctrl0 = reg_tmp;

            reg_tmp = SYSON->hs_adc_ctrl0;
            reg_tmp |= 0x000000;

            SYSON->hs_adc_ctrl0 = reg_tmp;
            DBG_ADC_INFO("ana0 by: %x\n", SYSON->hs_adc_ctrl0);

            for (cnt_tmp = 100; cnt_tmp > 0; cnt_tmp--) {
                reg_tmp = SYSON->hs_adc_ctrl0;
                reg_tmp |= BIT3;
                SYSON->hs_adc_ctrl0 = reg_tmp;
                SYSON->hs_adc_ctrl0 = reg_tmp;
                hal_delay_ms(10);
                DBG_ADC_INFO("ana0 cal en: %x\n", SYSON->hs_adc_ctrl0);
                
                DBG_ADC_INFO("sts(0x9C): %x\n", HAL_READ32(0x40010000, 0x9C));

                reg_tmp = SYSON->hs_adc_ctrl0;
                reg_tmp &= ~BIT3;
                SYSON->hs_adc_ctrl0 = reg_tmp;
                SYSON->hs_adc_ctrl0 = reg_tmp;
                hal_delay_ms(10);
                DBG_ADC_INFO("ana0 cal en: %x\n", SYSON->hs_adc_ctrl0);

                if ((HAL_READ32(0x40010000, 0x9C) & 0xFFFF0000) != 0) {
                    if (((HAL_READ32(0x40010000, 0x9C) & 0xFFFF0000) >> 24) != 0x7F) {
                        DBG_ADC_INFO("cal failed\n\n");
                    } else {
                        DBG_ADC_INFO("cal ok\n\n");
                    }
                    
                    break;
                }
            }

            reg_tmp = SYSON->hs_adc_ctrl0;
            reg_tmp &= ~BIT1;
            SYSON->hs_adc_ctrl0 = reg_tmp;
            DBG_ADC_INFO("ana0 end: %x\n", reg_tmp);
            SYSON->hs_adc_ctrl_b.ctrl_msr_sel = 0;

            DBG_ADC_INFO("sts(0x9C): %x\n", HAL_READ32(0x40010000, 0x9C));
        }

		return retv;
#else 
        return __rom_stubs_hal_adc.hal_adc_init(phal_adc_adapter);
#endif
    }
}

/** \brief Description of hal_adc_deinit
 *
 *    hal_adc_deinit is used for adc deinitialization including pinmux control.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adapter.
 *   \return hal_status_t:        hal_status_t.
 */
hal_status_t hal_adc_deinit (hal_adc_adapter_t *phal_adc_adapter)
{
    hal_status_t retv;

    retv = __rom_stubs_hal_adc.hal_adc_deinit(phal_adc_adapter);
    if (retv != HAL_OK) {
        return retv;
    } else {
        retv = hal_adc_pin_deinit(phal_adc_adapter);
        if (retv != HAL_OK) {
            return retv;
        }

        hal_adc_pwr_deinit(phal_adc_adapter);
    }

    return HAL_OK;
}

/** \brief Description of hal_adc_dma_init
 *
 *    hal_adc_dma_init is to initialize DMA module for adc data collection.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] hal_gdma_adaptor_t *padc_gdma_adaptor:            Pointer to GDMA channel control type.
 *
 *   \return hal_status_t:
 */
hal_status_t hal_adc_dma_init (hal_adc_adapter_t *phal_adc_adapter, hal_gdma_adaptor_t *padc_gdma_adaptor)
{
    DBG_ADC_INFO("dma init >>\n");
    if (padc_gdma_adaptor == NULL) {
        return HAL_ERR_PARA;
    }

    phal_adc_adapter->dma_dat.padaptor = padc_gdma_adaptor;
    padc_gdma_adaptor->busy = 0;
    padc_gdma_adaptor->have_chnl = 0;

    /* Allocate DMA channel first */
    if (phal_adc_adapter->dma_dat.ch_sts == ADCDmaChNone) {
        /* alloc a single block channel first */
        if (hal_gdma_chnl_alloc(padc_gdma_adaptor, MultiBlkDis) != HAL_OK) {
            DBG_ADC_ERR("dma channel alloc failed\n");
            return HAL_ERR_HW;
        }
        phal_adc_adapter->dma_dat.ch_sts = ADCDmaChGot;
        phal_adc_adapter->use_dma = ADCEnable;
    }

    if (phal_adc_adapter->dma_dat.ch_sts != ADCDmaChInitialed) {
        padc_gdma_adaptor->gdma_isr_type = (TransferType|ErrType);

        padc_gdma_adaptor->gdma_ctl.int_en = 1;
#ifdef ADC_DMA_PATCH
        padc_gdma_adaptor->gdma_ctl.src_msize   = MsizeOne;
        padc_gdma_adaptor->gdma_ctl.src_tr_width= TrWidthTwoBytes;
        padc_gdma_adaptor->gdma_ctl.dest_msize  = MsizeOne;
        padc_gdma_adaptor->gdma_ctl.dst_tr_width= TrWidthTwoBytes;
#else
        padc_gdma_adaptor->gdma_ctl.src_msize   = MsizeFour;
        padc_gdma_adaptor->gdma_ctl.src_tr_width= TrWidthTwoBytes;
        padc_gdma_adaptor->gdma_ctl.dest_msize  = MsizeFour;
        padc_gdma_adaptor->gdma_ctl.dst_tr_width= TrWidthTwoBytes;
#endif
        padc_gdma_adaptor->gdma_ctl.dinc        = IncType;
        padc_gdma_adaptor->gdma_ctl.sinc        = NoChange;
        padc_gdma_adaptor->gdma_ctl.tt_fc       = TTFCPeriToMem;

        padc_gdma_adaptor->gdma_cfg.src_per    = GDMA_HANDSHAKE_ADC;

        hal_gdma_handshake_init(padc_gdma_adaptor, padc_gdma_adaptor->gdma_cfg.src_per);
        hal_gdma_chnl_init(padc_gdma_adaptor);
        hal_gdma_irq_reg(padc_gdma_adaptor,
                    (irq_handler_t)(__rom_stubs_hal_adc.hal_adc_dma_irq_handler), (void *)phal_adc_adapter);
        phal_adc_adapter->dma_dat.ch_sts = ADCDmaChInitialed;

        /* assign default d-cache handling function */
        phal_adc_adapter->dcache_invalidate_by_addr = hal_cache_stubs.dcache_invalidate_by_addr;
        phal_adc_adapter->dcache_clean_invalidate_by_addr = hal_cache_stubs.dcache_clean_invalidate_by_addr;
    }

    DBG_ADC_INFO("dma init <<\n");
    return HAL_OK;
}

/** \brief Description of hal_adc_dma_deinit
 *
 *    hal_adc_dma_deinit is to deinitialize DMA module for adc data collection.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *
 *   \return hal_status_t:
 */
hal_status_t hal_adc_dma_deinit (hal_adc_adapter_t *phal_adc_adapter)
{
    if (phal_adc_adapter->dma_dat.padaptor != NULL) {
        hal_gdma_chnl_free(phal_adc_adapter->dma_dat.padaptor);
    }

    /* remove default d-cache handling function */
    phal_adc_adapter->dcache_invalidate_by_addr = NULL;
    phal_adc_adapter->dcache_clean_invalidate_by_addr = NULL;

    phal_adc_adapter->use_dma = ADCDisable;
    phal_adc_adapter->dma_dat.ch_sts = ADCDmaChNone;
    return HAL_OK;
}

/** \brief Description of hal_adc_read_dma
 *
 *    hal_adc_read_dma is used to read data contiuously by using DMA module.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter
 *   \param[in] uint32_t dat_len:                       ADC conversion data length.
 *   \param[in] uint16_t *dat_buf:                      ADC conversion data pointer.
 *   \param[in] uint8_t trigger_source:                 Inform ADC the trigger source.
 *                                                  1: automatic, 2: timer, 3: comparator,
 *                                                  software trigger is not available when using DMA because
 *                                                  software trigger would occupy CPU resource and application could
 *                                                  not get any performance improvement even using DMA.
 *
 *   \return hal_status_t:
 */
hal_status_t hal_adc_read_dma (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf,
                                                    uint8_t trigger_source)
{
    ADC_Type *padc_reg = phal_adc_adapter->init_dat.reg_base;
    adc_conf_t adc_con_tmp;
    adc_intr_ctrl_t adc_intr_ctrl_tmp;

    volatile uint32_t gdma_idx;
    hal_status_t retv;
    uint8_t adc_dma_multi = 0;

    /* software trigger is not sugguested to use DMA */
    if (trigger_source == ADCSWTrigMod) {
        return HAL_ERR_PARA;
    }

    /* check ADC is in progress or not */
    if (phal_adc_adapter->status != ADCStatusIdle) {
        DBG_ADC_WARN("Hardware in NOT in idle state\n");
        if (phal_adc_adapter->status == ADCStatusCVing) {
            DBG_ADC_WARN("A conversion is in progress\n");
        }

        return HAL_NOT_READY;
    }



    if (dat_len > MAX_DMA_BLOCK_SIZE) {
        if (dat_len <= MAX_DMA_BLOCK_SIZE*MAX_MULTI_BLOCK_NUM) {
            // Need to use multiple block DMA
            if (phal_adc_adapter->dma_dat.padaptor->ch_num < 4) {
                // Current GDMA Channel didn't support multiple block DMA, re-allocate another one
                gdma_idx = phal_adc_adapter->dma_dat.padaptor->gdma_index;  // backup old GDMA index
                hal_gdma_chnl_free(phal_adc_adapter->dma_dat.padaptor);
                retv = hal_gdma_chnl_alloc(phal_adc_adapter->dma_dat.padaptor, MultiBlkEn);
                adc_dma_multi = 1;
                if (retv != HAL_OK) {
                    phal_adc_adapter->dma_dat.ch_sts = ADCDmaChNone;
                    //phal_adc_adapter->dma_dat.padaptor = NULL;
                    DBG_ADC_ERR("hal_uart_dma_recv: Err: re-allocate multiple block DMA channel failed(%d)\r\n", retv);
                    return retv;
                } else {
                    DBG_ADC_INFO("hal_uart_dma_recv: re-allocate GDMA %u chnl %u\r\n",
                        phal_adc_adapter->dma_dat.padaptor->gdma_index, phal_adc_adapter->dma_dat.padaptor->ch_num);
                    hal_gdma_chnl_init(phal_adc_adapter->dma_dat.padaptor);
                }

                // Update GDMA handshake bit and IRQ handler(since may use different GDMA HW)
                if (gdma_idx != phal_adc_adapter->dma_dat.padaptor->gdma_index) {
                    // allocated to different GDMA HW, update the handshake bit
                    hal_gdma_handshake_init (phal_adc_adapter->dma_dat.padaptor, phal_adc_adapter->dma_dat.padaptor->gdma_cfg.src_per);
                    phal_adc_adapter->dma_dat.ch_sts = ADCDmaChInitialed;
                }

                hal_gdma_irq_reg((phal_adc_adapter->dma_dat.padaptor),
                                    (irq_handler_t)(__rom_stubs_hal_adc.hal_adc_dma_irq_handler), (void *)phal_adc_adapter);
            }

        }else {
            DBG_ADC_ERR("hal_adc_dma: Err: RX Len(%lu) too big\n", dat_len);
            return HAL_ERR_PARA;
        }
    }

    DBG_ADC_ERR("dat_len: %d\n", dat_len);
    phal_adc_adapter->use_dma = ADCEnable;
    phal_adc_adapter->cv_dat_len = dat_len;
    phal_adc_adapter->cv_dat_buf = dat_buf;
    
    if (phal_adc_adapter->dma_dat.padaptor->gdma_ctl.src_tr_width == TrWidthFourBytes) {
        phal_adc_adapter->cv_dat_len = dat_len*4;
    } else {
        phal_adc_adapter->cv_dat_len = dat_len*2;
    }
    
    phal_adc_adapter->cv_dat_buf = dat_buf;

    phal_adc_adapter->status = ADCStatusCVing;
    phal_adc_adapter->dma_dat.padaptor->ch_sar = (uint32_t)&(padc_reg->dat_global);
    phal_adc_adapter->dma_dat.padaptor->ch_dar = (uint32_t)phal_adc_adapter->cv_dat_buf;
    phal_adc_adapter->dma_dat.padaptor->gdma_ctl.block_size = dat_len;

    /* deal with d-cache sync. (clean-invalidate) */
    if (is_dcache_enabled ()) {
        if (phal_adc_adapter->dcache_clean_invalidate_by_addr != NULL) {
            phal_adc_adapter->dcache_clean_invalidate_by_addr((uint32_t *)phal_adc_adapter->cv_dat_buf, (int32_t)phal_adc_adapter->cv_dat_len);
        } else {
            DBG_ADC_WARN("D-Cache is enabled but clean_invalidate function is NOT available before GDMA starts.\n");
        }
    }

    if (adc_dma_multi) {
        hal_gdma_transfer_start((void *)phal_adc_adapter->dma_dat.padaptor, MultiBlkEn);
    } else {
        hal_gdma_transfer_start((void *)phal_adc_adapter->dma_dat.padaptor, MultiBlkDis);
    }

    hal_adc_reset_list(phal_adc_adapter);
    hal_adc_clear_fifo(phal_adc_adapter);

    padc_reg->intr_sts = 0xFFFFFFFF;
    adc_intr_ctrl_tmp.w = padc_reg->intr_ctrl;
    adc_intr_ctrl_tmp.b.it_fifo_over_en = 1;
    adc_intr_ctrl_tmp.b.it_err_en = 1;
    padc_reg->intr_ctrl = adc_intr_ctrl_tmp.w;

    adc_con_tmp.w = padc_reg->conf;
    adc_con_tmp.b.en = ADCEnable;

    /* enable lp ADC power cut manually */
    hal_lp_adc_en_pwr_by_hp();
    padc_reg->dma_con_b.lvl = phal_adc_adapter->init_dat.dma_rq_lv;
    padc_reg->dma_con_b.en  = ADCEnable;

   if (trigger_source == ADCAutoMod) {
        phal_adc_adapter->init_dat.hw_mode = ADCAutoMod;
        adc_con_tmp.b.op_mod = ADCAutoMod;
        padc_reg->conf = adc_con_tmp.w;
        hal_adc_auto_chsw_ctrl(phal_adc_adapter, ADCEnable);
    } else if (trigger_source == ADCTmTrigMod) {
        phal_adc_adapter->init_dat.hw_mode = ADCTmTrigMod;
        adc_con_tmp.b.op_mod = ADCTmTrigMod;
        padc_reg->conf = adc_con_tmp.w;
    } else if (trigger_source == ADCCompTrigMod) {
        phal_adc_adapter->init_dat.hw_mode = ADCCompTrigMod;
        adc_con_tmp.b.op_mod = ADCCompTrigMod;
        padc_reg->conf = adc_con_tmp.w;
    }

    return HAL_OK;
}

/** \brief Description of hal_adc_timeout_chk
 *
 *    hal_adc_timeout_chk is used to check if adc operation is timeout.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:    Pointer to ADC control adapter.
 *   \param[in] uint32_t start_cnt:                     Timer start count.
 *   \return uint8_t:                                   Timeout or not.\n
 *                                                      0: not time-out. 1: time-out.
 */
uint8_t hal_adc_timeout_chk (hal_adc_adapter_t *phal_adc_adapter, uint32_t start_cnt)
{
    return __rom_stubs_hal_adc.hal_adc_timeout_chk(phal_adc_adapter, start_cnt);
}

/** \brief Description of hal_adc_sw_cv_trig
 *
 *    hal_adc_sw_cv_trig is used to execute ADC software conversion trigger.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
void hal_adc_sw_cv_trig (hal_adc_adapter_t *phal_adc_adapter)
{
    __rom_stubs_hal_adc.hal_adc_sw_cv_trig(phal_adc_adapter);
}

/** \brief Description of hal_adc_pure_init
 *
 *    hal_adc_pure_init is used to initialize ADC module.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:       Pointer to ADC control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_adc_pure_init (hal_adc_adapter_t *phal_adc_adapter)
{
    return __rom_stubs_hal_adc.hal_adc_pure_init(phal_adc_adapter);
}

/** \brief Description of hal_adc_pure_deinit
 *
 *    hal_adc_deinit is used to initialize ADC module.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:       Pointer to ADC control adapter.
 *   \return hal_status_t
 */
hal_status_t hal_adc_pure_deinit (hal_adc_adapter_t *phal_adc_adapter)
{
    return __rom_stubs_hal_adc.hal_adc_pure_deinit(phal_adc_adapter);
}

/** \brief Description of hal_adc_set_in_type
 *
 *    hal_adc_set_in_type is used to set ADC channel input type.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \param[in] uint8_t input_type:                 Input type.
 *   \return hal_status_t:          return HAL_OK when the given parameters is correct.
 *                                  Only ch0~ch5 are capable of two input type (single-end and differential)
 */
hal_status_t hal_adc_set_in_type (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t input_type)
{
    return __rom_stubs_hal_adc.hal_adc_set_in_type(phal_adc_adapter, ch_no, input_type);
}

/** \brief Description of hal_adc_get_in_type
 *
 *    hal_adc_get_in_type is used to set ADC channel input type.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                              ADC channel number.
 *   \return uint8_t:                               channel input type.\n
 *                                                  0: single end, 1: differential.
 */
uint8_t hal_adc_get_in_type (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
    return __rom_stubs_hal_adc.hal_adc_get_in_type(phal_adc_adapter, ch_no);
}

/** \brief Description of hal_adc_set_comp_thld
 *
 *    hal_adc_set_comp_thld is used to set ADC channel comparison threshold.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \param[in] uint16_t thld_high:                 Comparison high threshold.
 *   \param[in] uint16_t thld_low:                  Comparison low threshold.
 *   \return hal_status_t
 */
hal_status_t hal_adc_set_comp_thld (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint16_t thld_high, uint16_t thld_low)
{
    return __rom_stubs_hal_adc.hal_adc_set_comp_thld(phal_adc_adapter, ch_no, thld_high, thld_low);
}

/** \brief Description of hal_adc_set_comp_rule
 *
 *    hal_adc_set_comp_rule is used to set ADC channel comparison control. When this is set to a particular
 *    criterion, the related comparison status and interrupt would be triggered.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \param[in] uint8_t comp_rule:                  Comparison rule.
 *   \return hal_status_t
 */
hal_status_t hal_adc_set_comp_rule (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t comp_rule)
{
    return __rom_stubs_hal_adc.hal_adc_set_comp_rule(phal_adc_adapter, ch_no, comp_rule);
}

/** \brief Description of hal_adc_clear_comp_intr_sts
 *
 *    hal_adc_clear_comp_intr_sts is used to clear adc comparison interrupt status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \return void
 */
void hal_adc_clear_comp_intr_sts (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
    __rom_stubs_hal_adc.hal_adc_clear_comp_intr_sts(phal_adc_adapter, ch_no);
}

/** \brief Description of hal_adc_comp_intr_ctrl
 *
 *    hal_adc_comp_intr_ctrl is used to set ADC channel comparison control. When this is set to a particular
 *    criterion, the related comparison status and interrupt would be triggered.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t intr_option:                Interrupt option (source).\n
 *                                              0: cvlist end.          1: cv end.\n
 *                                              2: channel cv end.      3: fifo full.\n
 *                                              4: fifo over.           5: fifo empty.\n
 *                                              6: dat ovw.             7: err.
 *
 *   \param[in] uint8_t intr_enable:                Interrupt enable control.
 *   \return void
 */
void hal_adc_intr_ctrl (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option, uint8_t intr_enable)
{
    __rom_stubs_hal_adc.hal_adc_intr_ctrl(phal_adc_adapter, intr_option, intr_enable);
}

/** \brief Description of hal_adc_clear_intr_sts
 *
 *    hal_adc_clear_intr_sts is used to clear adc interrupt interrupt status.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t intr_option:                Interrupt option (source).\n
 *                                              0: cvlist end.          1: cv end.\n
 *                                              2: channel cv end.      3: fifo full.\n
 *                                              4: fifo over.           5: fifo empty.\n
 *                                              6: dat ovw.             7: err.
 *   \return void
 */
void hal_adc_clear_intr_sts (hal_adc_adapter_t *phal_adc_adapter, uint8_t intr_option)
{
    __rom_stubs_hal_adc.hal_adc_clear_intr_sts(phal_adc_adapter, intr_option);
}

/** \brief Description of hal_adc_set_cvlist
 *
 *    hal_adc_set_cvlist is used to set ADC channel conversion list.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t *cvlist:                    Pointer to a channel conversion list. It should be an array start address.
 *   \param[in] uint8_t cvlist_len:                 Conversion list length.
 *   \return hal_status_t
 */
hal_status_t hal_adc_set_cvlist (hal_adc_adapter_t *phal_adc_adapter, uint8_t *cvlist, uint8_t cvlist_len)
{
    return __rom_stubs_hal_adc.hal_adc_set_cvlist(phal_adc_adapter, cvlist, cvlist_len);
}

/** \brief Description of hal_adc_item_to_ch
 *
 *    hal_adc_item_to_ch is used to transfer a list item to channel number.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adapter.
 *   \param[in] uint8_t item_no:                    Item number in the hardware list register.
 *   \return uint8_t:                           Channel number of the list item.
 */
uint8_t hal_adc_item_to_ch (hal_adc_adapter_t *phal_adc_adapter, uint8_t item_no)
{
    return __rom_stubs_hal_adc.hal_adc_item_to_ch(phal_adc_adapter, item_no);
}

/** \brief Description of hal_adc_load_default
 *
 *    hal_adc_load_default is used to load default value for data structure.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return void
 */
void hal_adc_load_default (hal_adc_adapter_t *phal_adc_adapter)
{
    __rom_stubs_hal_adc.hal_adc_load_default(phal_adc_adapter);
}


/** \brief Description of hal_adc_single_read
 *
 *    hal_adc_single_read is used for single for particular channel. \n
 *    This function would automatically execute software trigger flow and return the channel data.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:      Pointer to ADC control adaptor.
 *   \param[in] uint8_t ch_no:                      ADC channel number.
 *   \return uint16_t:            ADC sample data.
 */
uint16_t hal_adc_single_read (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
        hal_adc_cali_para_t adc_cali_paras_tmp;
        uint8_t cali_flag = phal_adc_adapter->use_cali;
        uint16_t adc_dat_tmp;
    
        hal_adc_read_cali_param(HP_ADC_GAIN_DENO_ADDR, &adc_cali_paras_tmp.gain_deno, 2);
        hal_adc_read_cali_param(HP_ADC_GAIN_MOLE_ADDR, &adc_cali_paras_tmp.gain_mole, 2);
        hal_adc_read_cali_param(HP_ADC_OFFSET_DENO_ADDR, &adc_cali_paras_tmp.offset_deno, 4);
        hal_adc_read_cali_param(HP_ADC_OFFSET_MOLE_ADDR, &adc_cali_paras_tmp.offset_mole, 2);
        DBG_8195BL("gain deno: %08x\n", adc_cali_paras_tmp.gain_deno);
        DBG_8195BL("gain mole: %08x\n", adc_cali_paras_tmp.gain_mole);
        DBG_8195BL("offset deno: %08x\n", adc_cali_paras_tmp.offset_deno);
        DBG_8195BL("offset mole: %08x\n", adc_cali_paras_tmp.offset_mole);

        hal_lp_adc_en_pwr_by_hp();
        phal_adc_adapter->use_cali = ADCDisable;
        adc_dat_tmp = __rom_stubs_hal_adc.hal_adc_single_read(phal_adc_adapter, ch_no);
        DBG_8195BL("raw data adc: %x\n", adc_dat_tmp);
        phal_adc_adapter->use_cali = cali_flag;
        if (phal_adc_adapter->use_cali != 0) {
            adc_dat_tmp = hal_adc_calc_cali_val((uint16_t)adc_dat_tmp, (hal_adc_cali_para_t *)&adc_cali_paras_tmp);
            return (uint16_t)(adc_dat_tmp & HP_ADC_DATA_MASK);
        } else {
            return (uint16_t)(adc_dat_tmp & HP_ADC_DATA_MASK);
        }
#else
        hal_lp_adc_en_pwr_by_hp();
        return hal_adc_single_read_rtl8195bhp_patch (phal_adc_adapter, ch_no);
#endif
}

/** \brief Description of hal_adc_clear_fifo
 *
 *    hal_adc_clear_fifo is used to clear FIFO to the default state.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \return void
 */
void hal_adc_clear_fifo (hal_adc_adapter_t *phal_adc_adapter)
{
    __rom_stubs_hal_adc.hal_adc_clear_fifo(phal_adc_adapter);
}

/** \brief Description of hal_adc_read_ch_dat
 *
 *    hal_adc_read_ch_dat is used to read the channel data directly without any trigger operation.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter.
 *   \param[in] uint8_t ch_no:                          Channel number.
 *   \return uint16_t:                              channel conversion data.\n
 *                                                  If the data is NOT ready or overwritten, a value of 0xFFFF would\n
 *                                                  be returned.
 */

uint16_t hal_adc_read_ch_dat (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no, uint8_t out_raw)
{
    return __rom_stubs_hal_adc.hal_adc_read_ch_dat(phal_adc_adapter, ch_no, out_raw);
}

/** \brief Description of hal_adc_read_continuous
 *
 *    hal_adc_read_continuous is used to read the channel data continuously according to cvlist and different
 *                                          trigger source.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter
 *   \param[in] uint32_t dat_len:                       ADC conversion data length.
 *   \param[in] uint16_t *dat_buf:                      ADC conversion data pointer.
 *   \param[in] uint8_t trigger_source:                 Inform ADC the trigger source.
 *                                                  0: software, 1: automatic, 2: timer, 3: comparator
 *   \return hal_status_t.
 */
hal_status_t hal_adc_read_continuous (hal_adc_adapter_t *phal_adc_adapter, uint32_t dat_len, uint16_t *dat_buf,
                                                    uint8_t trigger_source)
{
    hal_lp_adc_en_pwr_by_hp();
    return __rom_stubs_hal_adc.hal_adc_read_continuous(phal_adc_adapter, dat_len, dat_buf, trigger_source);
}

/** \brief Description of hal_adc_reg_irq
 *
 *    hal_adc_reg_irq is used to register a irq handler

 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \param[in] irq_handler_t handler:                IRQ handler function.
 *   \return void
 */
void hal_adc_reg_irq (hal_adc_adapter_t *phal_adc_adapter, irq_handler_t handler)
{
    __rom_stubs_hal_adc.hal_adc_reg_irq (phal_adc_adapter, handler);
}

/** \brief Description of hal_adc_unreg_irq
 *
 *    hal_adc_unreg_irq is used to unregister a irq handler

 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:        Pointer to ADC control adaptor.
 *   \return void
 */
void hal_adc_unreg_irq (hal_adc_adapter_t *phal_adc_adapter)
{
    __rom_stubs_hal_adc.hal_adc_unreg_irq (phal_adc_adapter);
}

/** \brief Description of hal_adc_gen_rand_dat32
 *
 *    hal_adc_gen_rand_dat32 is used to read adc channel data contiuously and get a random number.
 *
 *   \param[in] hal_adc_adapter_t *phal_adc_adapter:          Pointer to ADC control adapter
 *   \prarm[in] uint32_t *ret_rand_dat:         random data pointer
 *   \prarm[in] uint32_t len:           random data length (bit count)
 *   \return uint32_t
 */
uint32_t hal_adc_gen_rand_dat32 (hal_adc_adapter_t *phal_adc_adapter, uint8_t ch_no)
{
    return __rom_stubs_hal_adc.hal_adc_gen_rand_dat32(phal_adc_adapter, ch_no);
}

/** \brief Description of hal_adc_cal_gain_deno_rtl8195blp
 *
 *    hal_adc_cal_gain_deno_rtl8195blp is used to calculate denominator part of adc gain.
 *
 *   \param[in] int16_t ideal code 0
 *   \param[in] int16_t ideal code 1
 *   \return int32_t
 */
int16_t hal_adc_calc_gain_deno(int16_t ideal_co_1, int16_t ideal_co_0)
{
    return (int16_t)__rom_stubs_hal_adc.hal_adc_calc_gain_deno(ideal_co_1, ideal_co_0);
}

/** \brief Description of hal_adc_cal_gain_mole_rtl8195blp
 *
 *    hal_adc_cal_gain_mole_rtl8195blp is used to calculate molecular part of adc gain.
 *
 *   \param[in] int16_t real code 0
 *   \param[in] int16_t real code 1
 *   \return int32_t
 */
int16_t hal_adc_calc_gain_mole(int16_t real_co_1, int16_t real_co_0)
{
    return (int16_t)__rom_stubs_hal_adc.hal_adc_calc_gain_mole(real_co_1, real_co_0);
}

/** \brief Description of hal_adc_cal_offet_deno_rtl8195blp
 *
 *    hal_adc_cal_offet_deno_rtl8195blp is used to calculate denominator part of adc offset.
 *
 *   \param[in] int16_t ideal code 0
 *   \param[in] int16_t ideal code 1
 *   \param[in] int16_t real code 0
 *   \param[in] int16_t real code 1
 *   \return int32_t
 */
int32_t hal_adc_calc_offset_deno(int16_t ideal_co_1, int16_t ideal_co_0, int16_t real_co_1, int16_t real_co_0)
{
    return (int32_t)__rom_stubs_hal_adc.hal_adc_calc_offset_deno(ideal_co_1, ideal_co_0, real_co_1, real_co_0);
}

/** \brief Description of hal_adc_cal_offset_mole_rtl8195blp
 *
 *    hal_adc_cal_offset_mole_rtl8195blp is used to calculate molecular part of adc offset.
 *
 *   \param[in] int16_t real code 0
 *   \param[in] int16_t real code 1
 *   \return int32_t
 */
int16_t hal_adc_calc_offset_mole(int16_t real_co_1, int16_t real_co_0)
{
    return (int16_t)__rom_stubs_hal_adc.hal_adc_calc_offset_mole(real_co_1, real_co_0);
}

typedef union bytes_tr_s {
    int64_t w64;
    struct {
        int64_t b0 :8;
        int64_t b1 :8;
        int64_t b2 :8;
        int64_t b3 :8;
        
        int64_t b4 :8;
        int64_t b5 :8;
        int64_t b6 :8;
        int64_t b7 :8;
    }b;
}bytes_tr_t, *pbytes_tr_t;

/** \brief Description of hal_adc_calc_cali_val_rtl8195blp
 *
 *    hal_adc_calc_cali_val_rtl8195blp is used to calculate calibration value
 *
 *   \param[in] uint16_t adc real value
 *   \param[in] hal_adc_cali_para_t *phal_adc_cali_para
 *   \return int32_t
 */
uint32_t hal_adc_calc_cali_val(uint16_t adc_read_val, hal_adc_cali_para_t *phal_adc_cali_para) 
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    bytes_tr_t bytes_tr;
    uint32_t ret_cali_val;
    int64_t read_val_scle = (int64_t)adc_read_val * (int64_t)HP_ADC_CALC_SCLE;
    int64_t gain_deno_scle = (int64_t)phal_adc_cali_para->gain_deno;
    int64_t gain_mole_scle = (int64_t)phal_adc_cali_para->gain_mole;
    int64_t offset_deno_scle = (int64_t)(phal_adc_cali_para->offset_deno) * (int64_t)HP_ADC_CALC_SCLE;
    int64_t offset_mole_scle = (int64_t)phal_adc_cali_para->offset_mole;

    if ((phal_adc_cali_para->gain_deno == 0xFFFF) || (phal_adc_cali_para->gain_mole == 0xFFFF) || 
        (phal_adc_cali_para->offset_deno == 0xFFFFFFFF) || (phal_adc_cali_para->offset_mole== 0xFFFF)) {
        DBG_ADC_ERR("Incorrect cali. value,\n gd: %08x, gm: %08x,\n od: %08x, om: %08x\n", phal_adc_cali_para->gain_deno, phal_adc_cali_para->gain_mole,
                     phal_adc_cali_para->offset_deno, phal_adc_cali_para->offset_mole);
        return (uint16_t)adc_read_val;
    }
    
    DBG_ADC_INFO("read val scaled:\n");
    bytes_tr.w64 = read_val_scle;
    DBG_ADC_INFO("b0: %02x\n", bytes_tr.b.b0);
    DBG_ADC_INFO("b1: %02x\n", bytes_tr.b.b1);
    DBG_ADC_INFO("b2: %02x\n", bytes_tr.b.b2);
    DBG_ADC_INFO("b3: %02x\n", bytes_tr.b.b3);
    DBG_ADC_INFO("b4: %02x\n", bytes_tr.b.b4);
    DBG_ADC_INFO("b5: %02x\n", bytes_tr.b.b5);
    DBG_ADC_INFO("b6: %02x\n", bytes_tr.b.b6);
    DBG_ADC_INFO("b7: %02x\n", bytes_tr.b.b7);
    DBG_ADC_INFO("offset deno scaled:\n");
    bytes_tr.w64 = offset_deno_scle;
    DBG_ADC_INFO("b0: %02x\n", bytes_tr.b.b0);
    DBG_ADC_INFO("b1: %02x\n", bytes_tr.b.b1);
    DBG_ADC_INFO("b2: %02x\n", bytes_tr.b.b2);
    DBG_ADC_INFO("b3: %02x\n", bytes_tr.b.b3);
    DBG_ADC_INFO("b4: %02x\n", bytes_tr.b.b4);
    DBG_ADC_INFO("b5: %02x\n", bytes_tr.b.b5);
    DBG_ADC_INFO("b6: %02x\n", bytes_tr.b.b6);
    DBG_ADC_INFO("b7: %02x\n", bytes_tr.b.b7);
    read_val_scle = (read_val_scle * gain_deno_scle * offset_mole_scle);    
    offset_deno_scle = offset_deno_scle * offset_mole_scle;
    read_val_scle = read_val_scle + offset_deno_scle;
    read_val_scle = read_val_scle / gain_mole_scle;
    read_val_scle = read_val_scle / offset_mole_scle;

    /* save read_val_scle to offset_deno_scle temporarily */
    offset_deno_scle = read_val_scle;
    read_val_scle = read_val_scle / HP_ADC_CALC_SCLE;
    if (offset_deno_scle < 0) {
        offset_deno_scle = offset_deno_scle * (-1);
    }
    
    if ((offset_deno_scle % HP_ADC_CALC_SCLE) > (HP_ADC_CALC_SCLE/2)) {
        DBG_ADC_WARN("final value is inreased/decresed by 1\n");
        if (read_val_scle > 0) {
            read_val_scle++;
        } else {
            read_val_scle--;
        }
    }
    
    ret_cali_val = (uint32_t)read_val_scle;

    if (read_val_scle < 0) {
        ret_cali_val = 0;
        DBG_ADC_WARN("cali value is less than 0.\n");
    } else if (read_val_scle > HP_ADC_CODE_MAX) {
        ret_cali_val = HP_ADC_CODE_MAX;
        DBG_ADC_WARN("cali value is greater than 4095.\n");
    }
    
    return (uint32_t)ret_cali_val;
#else
    return (uint32_t)__rom_stubs_hal_adc.hal_adc_calc_cali_val(adc_read_val, phal_adc_cali_para);
#endif
}


/** \brief Description of hal_adc_read_cali_param_rtl8195blp
 *
 *    hal_adc_read_cali_param_rtl8195blp is used to read calibration parameters.
 *
 *   \param[in] uint16_t parameters address
 *   \param[in] uint8_t *return data address
 *   \param[in] uint8_t parameter length
 *   \return void
 */
void hal_adc_read_cali_param(uint16_t addr, uint8_t *param_addr, uint8_t param_len)
{
#if defined(CONFIG_BUILD_RAM) && ((CHIP_VER == CHIP_A_CUT) || (CHIP_VER == CHIP_B_CUT))
    uint8_t rd_cnt;
    hal_efuse_func_stubs_t *efuse_stubs = 0x100af160;
    for (rd_cnt = 0; rd_cnt < param_len; rd_cnt++) {
        //hal_efuse_read_nsc(HP_ADC_FUSE_VAL, (addr+rd_cnt), (param_addr+rd_cnt), 7);
        efuse_stubs->hal_efuse_read(HP_ADC_FUSE_VAL, (addr+rd_cnt), (param_addr+rd_cnt), 7);
        DBG_ADC_INFO("read param(%x): %x\n", (addr+rd_cnt), *(param_addr+rd_cnt));
    }
#else
    __rom_stubs_hal_adc.hal_adc_read_cali_param(addr, param_addr, param_len);
#endif
}

/** \brief Description of hal_adc_write_cali_param_rtl8195blp
 *
 *    hal_adc_write_cali_param_rtl8195blp is used to read calibration parameters.
 *
 *   \param[in] uint16_t parameters address
 *   \param[in] uint8_t *data address
 *   \param[in] uint8_t parameter length
 *   \return void
 */
void hal_adc_write_cali_param(uint16_t addr, uint8_t *param_addr, uint8_t param_len)
{
    __rom_stubs_hal_adc.hal_adc_write_cali_param(addr, param_addr, param_len);
}
/** @} */ /* End of group hs_hal_adc */

#endif

