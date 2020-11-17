 /**************************************************************************//**
  * @file     rtl8195bh_pcm.h
  * @brief    The HAL related definition and macros for the PCM device.
  *           Includes Registers and data type definition.
  * @version  V1.00
  * @date     2016-07-20
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

#ifndef _RTL8195BH_PCM_H_
#define _RTL8195BH_PCM_H_
 
#ifdef __cplusplus
 extern "C" {
#endif

/** 
 * @addtogroup hs_hal_pcm PCM
 * @{
 */

#include "rtl8195bhp_pcm_type.h"

typedef union {
  __IOM uint32_t w;                           
  
  struct {
    __IOM uint32_t chnre      : 1;   
    __IOM uint32_t chnte      : 1; 
    __IOM uint32_t chnua      : 1;            
    __IOM uint32_t chnband    : 1;         
  } b;
} chn_cnr_t, *pchn_cnr_t;

typedef union {
  __IOM uint32_t w;                           
  
  struct {
    __IOM uint32_t chg3_cnr   : 4;                                                                          
    __IM  uint32_t            : 4;
    __IOM uint32_t chg2_cnr   : 4;                                             
    __IM  uint32_t            : 4;
    __IOM uint32_t chg1_cnr   : 4;           
    __IM  uint32_t            : 4;
    __IOM uint32_t chg0_cnr   : 4;          
  } b;
} pachgn_cnr_t, *ppachgn_cnr_t;

typedef union {
  __IOM uint32_t w;                          
  
  struct {
    __IOM uint32_t chg3_wtsa  : 5;           
    __IM  uint32_t            : 3;
    __IOM uint32_t chg2_wtsa  : 5;        
    __IM  uint32_t            : 3;
    __IOM uint32_t chg1_wtsa  : 5;         
    __IM  uint32_t            : 3;
    __IOM uint32_t chg0_wtsa  : 5;           
  } b;
} pawtsrgn_t, *ppawtsrgn_t;

typedef union {
  __IOM uint32_t w;                           
  
  struct {
    __IOM uint32_t p0own      : 1;            
    __IOM uint32_t p1own      : 1;           
    __IOM uint32_t bufptr     : 30;          
  } b;
} chgn_atxbsa_t, *pchgn_atxbsa_t;

typedef union {
  __IOM uint32_t w;                           
  
  struct {
    __IOM uint32_t p0own      : 1;            
    __IOM uint32_t p1own      : 1;            
    __IOM uint32_t bufptr     : 30;           
  } b;
} chgn_arxbsa_t, *pchgn_arxbsa_t;

typedef union {
  __IOM uint32_t w;                          
  
  struct {
    __IOM uint32_t chnrbp1uaie : 1;           
    __IOM uint32_t chnrbp0uaie : 1;           
    __IOM uint32_t chntbp1uaie : 1;          
    __IOM uint32_t chntbp0uaie : 1;           
    __IOM uint32_t chnp1rokie : 1;           
    __IOM uint32_t chnp0rokie : 1;           
    __IOM uint32_t chnp1tokie : 1;           
    __IOM uint32_t chnp0tokie : 1;             
  } b;
} paimr_n_t, *ppaimr_n_t;

typedef union {
  __IOM uint32_t w;                          
  
  struct {
    __IOM uint32_t paimr_g3_t : 8;           
    __IOM uint32_t paimr_g2_t : 8; 
    __IOM uint32_t paimr_g1_t : 8; 
    __IOM uint32_t paimr_g0_t : 8;           
  } b;
} paimr_gn_t, *ppaimr_gn_t;

typedef union {
  __IOM uint32_t w;                          
  
  struct {
    __IOM uint32_t chnrxp1ua : 1;           
    __IOM uint32_t chnrxp0ua : 1;           
    __IOM uint32_t chntxp1ua : 1;          
    __IOM uint32_t chntxp0ua : 1;           
    __IOM uint32_t chnrxp1ip : 1;           
    __IOM uint32_t chnrxp0ip : 1;           
    __IOM uint32_t chntxp1ip : 1;           
    __IOM uint32_t chntxp0ip : 1;             
  } b;
} paisr_n_t, *ppaisr_n_t;

typedef union {
  __IOM uint32_t w;                          
  
  struct {
    __IOM uint32_t paisr_g3_t : 8;           
    __IOM uint32_t paisr_g2_t : 8; 
    __IOM uint32_t paisr_g1_t : 8; 
    __IOM uint32_t paisr_g0_t : 8;           
  } b;
} paisr_gn_t, *ppaisr_gn_t;

/**
  \brief  Define the PCM port ID.
*/
enum  pcm_index_sel_e
{
    Pcm0_Sel    =   0x0,
    Pcm1_Sel    =   0x1,
    Pcm_Max_Id  =   0x2
};
typedef uint8_t pcm_index_sel_t;

/**
  \brief PCM pin mux selection.
*/
enum  pcm_pin_sel_e
{
    Pcm_PinSel_0    =   0,
    Pcm_PinSel_1    =   1,
    Pcm_PinSel_Max  =   2
};
typedef uint8_t pcm_pin_sel_t;

/**
  \brief PCM Device Mode. 
*/
enum  pcm_mode_e
{
    PCM_MASTER_MODE =   0x0,
    PCM_SLAVE_MODE  =   0x1  
};
typedef uint8_t pcm_mode_t;

/**
  \brief PCM frame sync active. 
*/
enum  pcm_frame_active_e     
{
	PCM_FRAME_HIGH_ACTIVE = 0,
	PCM_FRAME_LOW_ACTIVE = 1
};
typedef uint8_t pcm_frame_active_t;

/**
  \brief PCM the linear or compender mode. 
*/
enum  pcm_linear_mode_e 
{
	PCM_COMPENDER_MODE = 0,
	PCM_LINEAR_MODE = 1
};
typedef uint8_t pcm_linear_mode_t;

/**
  \brief PCM loopback mode. 
*/
enum  pcm_loopback_mode_e 
{
	PCM_LOOPBACK_DISABLE = 0,
	PCM_LOOPBACK_ENABLE = 1
};
typedef uint8_t pcm_loopback_mode_t;

/**
  \brief PCM data endian swap. 
*/
enum  pcm_endian_swap_e 
{
	PCM_ENDIANSWAP_DISABLE = 0,
	PCM_ENDIANSWAP_ENABLE = 1
};
typedef uint8_t pcm_endian_swap_t;

/**
  \brief PCM compender method. 
*/
enum  pcm_ua_law_e
{
    PCM_U_LAW   =   0,
    PCM_A_LAW   =   1, 
};
typedef uint8_t pcm_ua_law_t; 

/**
  \brief PCM channel, CH0~CH15. 
*/
enum  pcm_ch_e
{
    PCM_CH0       =   0,
    PCM_CH1       =   1,
    PCM_CH2       =   2,
    PCM_CH3       =   3,
    PCM_CH4       =   4,
    PCM_CH5       =   5,
    PCM_CH6       =   6,
    PCM_CH7       =   7,
    PCM_CH8       =   8,
    PCM_CH9       =   9,
    PCM_CH10      =   10,
    PCM_CH11      =   11,
    PCM_CH12      =   12,
    PCM_CH13      =   13,
    PCM_CH14      =   14,
    PCM_CH15      =   15  
};
typedef uint8_t pcm_ch_t; 

/**
  \brief PCM time slot 0~31. 
*/
enum  pcm_slot_e
{
    PCM_SLOT0       =   0,
    PCM_SLOT1       =   1,
    PCM_SLOT2       =   2,
    PCM_SLOT3       =   3,
    PCM_SLOT4       =   4,
    PCM_SLOT5       =   5,
    PCM_SLOT6       =   6,
    PCM_SLOT7       =   7,
    PCM_SLOT8       =   8,
    PCM_SLOT9       =   9,
    PCM_SLOT10      =   10,
    PCM_SLOT11      =   11,
    PCM_SLOT12      =   12,
    PCM_SLOT13      =   13,
    PCM_SLOT14      =   14,
    PCM_SLOT15      =   15,
    PCM_SLOT16      =   16,
    PCM_SLOT17      =   17,
    PCM_SLOT18      =   18,
    PCM_SLOT19      =   19,
    PCM_SLOT20      =   20,
    PCM_SLOT21      =   21,
    PCM_SLOT22      =   22,
    PCM_SLOT23      =   23,
    PCM_SLOT24      =   24,
    PCM_SLOT25      =   25,
    PCM_SLOT26      =   26,
    PCM_SLOT27      =   27,
    PCM_SLOT28      =   28,
    PCM_SLOT29      =   29,
    PCM_SLOT30      =   30,
    PCM_SLOT31      =   31
};
typedef uint8_t pcm_slot_t; 

/**
  \brief Select to control tx or rx. 
*/
enum  pcm_trx_ctrl_e
{
    PCM_RX_CTRL =   0,
    PCM_TX_CTRL =   1
};
typedef uint8_t pcm_trx_ctrl_t; 

/**
  \brief Select to own the page 0 or page 1. 
*/
enum  pcm_page_own_e
{
    PCM_PAGE0_OWN   =   1,
    PCM_PAGE1_OWN   =   2 
};
typedef uint8_t pcm_page_own_t; 

/**
  \brief  The data structure of the PCM setting.
*/
typedef struct hal_pcm_format_s {  
    u8                  pcm_slave;  
    u8                  pcm_linear_mode;     
    u8                  pcm_loop_back;   
    u8                  pcm_endian_swap; 
    u8                  pcm_fs_inv;     
} hal_pcm_format_t, *phal_pcm_format_t;

/**
  \brief  The PCM information structure.
*/
typedef struct hal_pcm_irqinfo_ch_s {
    u32                 tx_p0_adr;        /*Output: Get PCM Tx Page0 address*/
    u32                 tx_p1_adr;        /*Output: Get PCM Tx Page1 address*/    
    u32                 rx_p0_adr;        /*Output: Get PCM Rx Page0 address*/ 
    u32                 rx_p1_adr;        /*Output: Get PCM Rx Page1 address*/ 
    u8                  tx_own_sta[2];    /*Output: Get PCM Tx Page Own State*/ 
    u8                  rx_own_sta[2];    /*Output: Get PCM Rx Page Own State*/         

    u8                  channel_info;     /*Output: Get channel*/    
    u32                 buf_size_info;    /*Output: Get PCMBufSize, Unit: Byte*/  
    u8                  irq_page_info;    /*Output: Get interrupt page*/ 
}hal_pcm_irqinfo_ch_t, *phal_pcm_irqinfo_ch_t;

/**
  \brief  PCM call back function for the interrupt.
*/
typedef struct hal_pcm_user_cb_s{
    VOID (*tx_ccb[16])(void *data,u16 *pbuf);
    u32 tx_cbid;
    VOID (*rx_ccb[16])(void *data,u16 *pbuf);
    u32 rx_cbid;
} hal_pcm_user_cb_t,*phal_pcm_user_cb_t;

/**
  \brief  The data structure for an PCM port HAL operations.
*/
typedef struct hal_pcm_adapter_s{
    pcm_pin_sel_t pin_sel;              /*!< PCM pin mux seletion */
    pcm_index_sel_t pcm_index;
    PCM0_Type *base_addr;               /*!< The PCM register base address */

    u16 pcm_tx_page_idx_table;          /*!< The page index of  every channel for tx */
    u16 pcm_rx_page_idx_table;          /*!< The page index of  every channel for rx */

    u16 pcm_tx_ch_table;                /*!< The table of enable channel for tx */
    u16 pcm_rx_ch_table;                /*!< The table of enable channel for rx */

    u32 pcm_pachcnr03;                  /*!< Record the register for enabling tx or rx fast  */
    u32 pcm_pachcnr47;                  /*!< Record the register for enabling tx or rx fast  */
    u32 pcm_pachcnr811;                 /*!< Record the register for enabling tx or rx fast  */
    u32 pcm_pachcnr1215;                /*!< Record the register for enabling tx or rx fast  */
 
    hal_pcm_irqinfo_ch_t irq_info_ch;   /*!< PCM HAL IRQ information sub structure */
    hal_pcm_user_cb_t user_cb;          /*!< Pointer to PCMUser Callback */

    u8 dcache_memory_en;                /*!< check the memory is cache or not  */

    void (*dcache_invalidate_by_addr)(uint32_t *addr, int32_t dsize);   /*! callback function to do the D-cache invalidate  */
    void (*dcache_clean_by_addr) (uint32_t *addr, int32_t dsize);       /*! callback function to do the D-cache clean  */     
} hal_pcm_adapter_t, *phal_pcm_adapter_t;

/**
  \brief  The data structure to handle multiple PCM adapters.
*/
typedef struct hal_pcm_group_adapter_s{    
    volatile uint32_t critical_lv;                  /*!< to record PCM HAL enter critical section level */
    hal_pcm_adapter_t *ppcm_adapter[Pcm_Max_Id];    /*!< All the PCM adapters of this platform */
    irq_handler_t   irq_fun[Pcm_Max_Id];            /*!< the IRQ handler for different PCM adapters */      
} hal_pcm_group_adapter_t, *phal_pcm_group_adapter_t;

/// @cond DOXYGEN_ROM_HAL_API

/** 
 * @addtogroup hs_hal_pcm_rom_func PCM HAL ROM APIs.
 * @{
 */

void hal_pcm_irq_handler_rtl8195bhp (void *hid);
void hal_pcm_irq_reg_rtl8195bhp (void);
void hal_pcm_irq_unreg_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter);
HAL_Status hal_pcm_en_rtl8195bhp (pcm_index_sel_t index_sel, BOOL en);
HAL_Status hal_pcm_clk_ctrl_rtl8195bhp (pcm_index_sel_t index_sel, BOOL en);
HAL_Status hal_pcm_pin_ctrl_rtl8195bhp (pcm_index_sel_t index_sel, pcm_pin_sel_t pin_sel, BOOL en);
HAL_Status hal_pcm_func_ctrl_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, BOOL pcm_func_en);
HAL_Status hal_pcm_init_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter);
HAL_Status hal_pcm_deinit_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_set_format_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, hal_pcm_format_t *ppcm_format);
void hal_pcm_enter_critical_rtl8195bhp (void);
void hal_pcm_exit_critical_rtl8195bhp (void);
void hal_pcm_en_ctrl_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, BOOL pcm_en_ctrl);
HAL_Status hal_pcm_set_ch_time_slot_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_slot_t pcm_slot);
u32 hal_pcm_set_ch_rem_time_slot_rtl8195bhp (u32 pcm_ch_rem, u32 patsrgn, pcm_slot_t pcm_slot);
HAL_Status hal_pcm_set_ch_wb_time_slot_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_slot_t pcm_slot);
HAL_Status hal_pcm_set_ch_wideband_en_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_en_ctrl);
u32 hal_pcm_set_ch_rem_wideband_en_rtl8195bhp (u32 pcm_ch_rem, u32 pachgn_cnr, BOOL pcm_en_ctrl);
HAL_Status hal_pcm_set_ch_ua_law_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_ua_law_t pcm_ua_law);
u32 hal_pcm_set_ch_rem_ua_law_rtl8195bhp (u32 pcm_ch_rem, u32 pachgn_cnr, pcm_ua_law_t pcm_ua_law);
HAL_Status hal_pcm_set_ch_tx_en_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_tx_en);
HAL_Status hal_pcm_reg_ch_tx_en_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_tx_en);
HAL_Status hal_pcm_set_ch_rx_en_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_rx_en);
HAL_Status hal_pcm_reg_ch_rx_en_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_rx_en);
u32 hal_pcm_set_ch_rem_trx_en_rtl8195bhp (u32 pcm_ch_rem, u32 pachgn_cnr, pcm_trx_ctrl_t pcm_trx_ctrl, BOOL pcm_trx_en);
HAL_Status hal_pcm_set_ch_page_size_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 pcm_page_size);
u32 hal_pcm_set_ch_rem_page_size_rtl8195bhp (u32 pcm_ch_rem, u32 pabsizegn, u8 pcm_page_size);
HAL_Status hal_pcm_clr_ch_intr_ctrl_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, paisr_n_t paisr_n);
u32 hal_pcm_clr_ch_rem_intr_ctrl_rtl8195bhp (u32 pcm_ch_rem, u32 paisr_gn, paisr_n_t paisr_n);
HAL_Status hal_pcm_set_ch_intr_ctrl_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, paimr_n_t paimr_n);
u32 hal_pcm_set_ch_rem_intr_ctrl_rtl8195bhp (u32 pcm_ch_rem, u32 paimr_gn, paimr_n_t paimr_n);
u32* hal_pcm_get_ch_tx_adr_reg_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
HAL_Status hal_pcm_set_ch_tx_adr_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u16 *pcm_tx_adr);
u32* hal_pcm_get_ch_rx_adr_reg_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
HAL_Status hal_pcm_set_ch_rx_adr_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u16 *pcm_rx_adr);
u8 hal_pcm_get_ch_page_size_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
HAL_Status hal_pcm_get_ch_trx_info_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, hal_pcm_irqinfo_ch_t *pirq_info_ch);
HAL_Status hal_pcm_set_ch_tx_own_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u32 pcm_page0_own, u32 pcm_page1_own);
HAL_Status hal_pcm_set_ch_rx_own_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u32 pcm_page0_own, u32 pcm_page1_own);
HAL_Status hal_pcm_update_sw_ch_tx_idx_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
HAL_Status hal_pcm_update_sw_ch_rx_idx_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
void hal_pcm_clr_all_intr_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_dis_all_intr_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_dis_all_trx_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_dis_all_tx_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter);
void hal_pcm_dis_all_rx_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter);
HAL_Status hal_pcm_ch_read_memory_cache_invalidate_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 page_idx);
HAL_Status hal_pcm_ch_write_memory_cache_clean_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 page_idx);
void hal_pcm_start_trx_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter);

/** 
 *  @brief Get the pcm enable value.
 *   
 *  @param[in] ppcm_adapter The PCM adapter. 
 *
 *  @returns The enable value.
 */
__STATIC_INLINE
u32 hal_pcm_get_en_ctrl_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter)
{
    return (ppcm_adapter->base_addr->pcmcr_b.pcm_en);
}

/** 
 *  @brief Get the pcm mode.
 *   
 *  @param[in] ppcm_adapter The PCM adapter. 
 *
 *  @returns The linear mode(1) or compender mode(0).
 */
__STATIC_INLINE
u32 hal_pcm_get_linear_mode_rtl8195bhp (hal_pcm_adapter_t *ppcm_adapter)
{
    return (ppcm_adapter->base_addr->pcmcr_b.linear_mode);
}

/** @} */ /* End of group hs_hal_pcm_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/**
  \brief  The data structure of the stubs function for the Timer HAL functions in ROM
*/
typedef struct hal_pcm_func_stubs_s {

    hal_pcm_group_adapter_t *ppcm_group_adapter;
    const uint8_t *ppcm_pin;
    void (*hal_pcm_irq_handler) (void *hid);
    void (*hal_pcm_irq_reg) (void);
    void (*hal_pcm_irq_unreg) (hal_pcm_adapter_t *ppcm_adapter);

    HAL_Status (*hal_pcm_en) (pcm_index_sel_t index_sel, BOOL en);
    HAL_Status (*hal_pcm_clk_ctrl) (pcm_index_sel_t index_sel, BOOL en);
    HAL_Status (*hal_pcm_pin_ctrl) (pcm_index_sel_t index_sel, pcm_pin_sel_t pin_sel, BOOL en);
    HAL_Status (*hal_pcm_func_ctrl) (hal_pcm_adapter_t *ppcm_adapter, BOOL pcm_func_en);
    
    HAL_Status (*hal_pcm_init) (hal_pcm_adapter_t *ppcm_adapter);
    HAL_Status (*hal_pcm_deinit) (hal_pcm_adapter_t *ppcm_adapter);
    void (*hal_pcm_set_format) (hal_pcm_adapter_t *ppcm_adapter, hal_pcm_format_t *ppcm_format);

    void (*hal_pcm_enter_critical) (void);
    void (*hal_pcm_exit_critical) (void);

    void (*hal_pcm_en_ctrl) (hal_pcm_adapter_t *ppcm_adapter, BOOL pcm_en_ctrl);
    HAL_Status (*hal_pcm_set_ch_time_slot) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_slot_t pcm_slot);
    u32 (*hal_pcm_set_ch_rem_time_slot) (u32 pcm_ch_rem, u32 patsrgn, pcm_slot_t pcm_slot);
    HAL_Status (*hal_pcm_set_ch_wb_time_slot) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_slot_t pcm_slot);
    HAL_Status (*hal_pcm_set_ch_wideband_en) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_en_ctrl);
    u32 (*hal_pcm_set_ch_rem_wideband_en) (u32 pcm_ch_rem, u32 pachgn_cnr, BOOL pcm_en_ctrl);
    HAL_Status (*hal_pcm_set_ch_ua_law) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, pcm_ua_law_t pcm_ua_law);
    u32 (*hal_pcm_set_ch_rem_ua_law) (u32 pcm_ch_rem, u32 pachgn_cnr, pcm_ua_law_t pcm_ua_law);
    HAL_Status (*hal_pcm_set_ch_tx_en) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_tx_en);
    HAL_Status (*hal_pcm_reg_ch_tx_en) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_tx_en);    
    HAL_Status (*hal_pcm_set_ch_rx_en) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_rx_en);
    HAL_Status (*hal_pcm_reg_ch_rx_en) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, BOOL pcm_rx_en);    
    u32 (*hal_pcm_set_ch_rem_trx_en) (u32 pcm_ch_rem, u32 pachgn_cnr, pcm_trx_ctrl_t pcm_trx_ctrl, BOOL pcm_trx_en);
    HAL_Status (*hal_pcm_set_ch_page_size) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 pcm_page_size);
    u32 (*hal_pcm_set_ch_rem_page_size) (u32 pcm_ch_rem, u32 pabsizegn, u8 pcm_page_size);
    HAL_Status (*hal_pcm_clr_ch_intr_ctrl) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, paisr_n_t paisr_n);
    u32 (*hal_pcm_clr_ch_rem_intr_ctrl) (u32 pcm_ch_rem, u32 paisr_gn, paisr_n_t paisr_n);
    HAL_Status (*hal_pcm_set_ch_intr_ctrl) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, paimr_n_t paimr_n);
    u32 (*hal_pcm_set_ch_rem_intr_ctrl) (u32 pcm_ch_rem, u32 paimr_gn, paimr_n_t paimr_n);
    u32* (*hal_pcm_get_ch_tx_adr_reg) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
    HAL_Status (*hal_pcm_set_ch_tx_adr) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u16 *pcm_tx_adr);
    u32* (*hal_pcm_get_ch_rx_adr_reg) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
    HAL_Status (*hal_pcm_set_ch_rx_adr) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u16 *pcm_rx_adr);
    u8 (*hal_pcm_get_ch_page_size) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
    HAL_Status (*hal_pcm_get_ch_trx_info) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, hal_pcm_irqinfo_ch_t *pirq_info_ch);
    HAL_Status (*hal_pcm_set_ch_tx_own) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u32 pcm_page0_own, u32 pcm_page1_own);
    HAL_Status (*hal_pcm_set_ch_rx_own) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u32 pcm_page0_own, u32 pcm_page1_own);
    HAL_Status (*hal_pcm_update_sw_ch_tx_idx) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
    HAL_Status (*hal_pcm_update_sw_ch_rx_idx) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch);
    void (*hal_pcm_clr_all_intr) (hal_pcm_adapter_t *ppcm_adapter);
    void (*hal_pcm_dis_all_intr) (hal_pcm_adapter_t *ppcm_adapter);
    void (*hal_pcm_dis_all_trx) (hal_pcm_adapter_t *ppcm_adapter);
    void (*hal_pcm_dis_all_tx) (hal_pcm_adapter_t *ppcm_adapter);
    void (*hal_pcm_dis_all_rx) (hal_pcm_adapter_t *ppcm_adapter);

    HAL_Status (*hal_pcm_ch_read_memory_cache_invalidate) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 page_idx);
    HAL_Status (*hal_pcm_ch_write_memory_cache_clean) (hal_pcm_adapter_t *ppcm_adapter, pcm_ch_t pcm_ch, u8 page_idx);
    void (*hal_pcm_start_trx) (hal_pcm_adapter_t *ppcm_adapter);
    uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} hal_pcm_func_stubs_t;

/** @} */ /* End of group hs_hal_pcm */


#ifdef __cplusplus
}
#endif

#endif  // #ifndef _RTL8195BH_PCM_H_

