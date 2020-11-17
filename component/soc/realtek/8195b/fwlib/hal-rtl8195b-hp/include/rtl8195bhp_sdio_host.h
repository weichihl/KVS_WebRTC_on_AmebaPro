/**************************************************************************//**
 * @file    rtl8195bhp_sdio_host.h
 * @brief    The HAL related definition and macros for SDIO Host controller.
 *           Includes Registers and data type definition.
 * @version V1.00
 * @date    2017-07-12
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
#ifndef _RTL8195BH_SDIO_HOST_H_
#define _RTL8195BH_SDIO_HOST_H_

#ifdef  __cplusplus
extern "C"
{
#endif

/** 
 * @addtogroup hs_hal_sdio_host SDIO_HOST
 * @ingroup 8195bh_hal
 * @{
 * @brief The SDIO Host HAL module of the HS platform.
 */

#include "rtl8195bhp_sdio_host_type.h"



/// Defines the max. timeout value when checking the flag of command complete
#define SDIOH_CMD_CPLT_TIMEOUT      5000        // 5000 us
/// Defines the max. timeout value when checking the flag of transfer complete
#define SDIOH_XFER_CPLT_TIMEOUT     0xF0000000

/// Defines the mask of register "SD Bus Status"
#define SDIOH_BUS_STS_MASK          0x1F        // 0x585 bit[4:0]
/// Defines the mask of register "SD_CMD0"
#define SDIOH_CMD_IDX_MASK          0x3F        // 0x589 bit[5:0]

/// Defines the value of "VHS" field in CMD8
#define SDIOH_CMD8_VHS              0x1         // 2.7-3.6V
/// Defines the value of "Check pattern" field in CMD8
#define SDIOH_CMD8_CHK_PATN         0xAA

/// Defines the value of "OCR" field in ACMD41
#define SDIOH_OCR_VDD_WIN           0xFF8000    // OCR bit[23:0]
/// Defines the time interval when checking the process of card initialization
#define SDIOH_ACMD41_POLL_INTERVAL  10000       // 10 ms
/// Defines the max. timeout value when checking the process of card initialization
#define SDIOH_ACMD41_TIMEOUT        1000000     // 1 sec	
/// Defines the length of CSD register
#define SDIOH_CSD_LEN               16          // 128 bits
/// Defines the buffer length for storing the returned data of CMD6, R2 response, etc.
#define SDIOH_C6R2_BUF_LEN          64          // buffer for CMD6, R2, etc.
/// Defines the size of one data block
#define SDIOH_ONE_BLK_LEN           512         // 512 Bytes

/// Defines the total number of phases when tuning sample clock
#define SDIOH_RX_CLK_TOTAL_PHASE    6


/**
  \brief  Defines SDIO host pinmux selection.
*/
enum  sdioh_pin_sel_e
{
    SdiohPinSel0    = 0,
    SdiohPinSel1    = 1,
    SdiohPinSel2    = 2
};
typedef uint8_t sdioh_pin_sel_t;

/**
  \brief  Defines SDIO Host DMA transfer type.
*/
enum  sdioh_dma_type_e
{
    SdiohDmaNormal  = 0,
    SdiohDma64b     = 1,
    SdiohDmaR2      = 2
};

/**
  \brief  Defines SDIO Host DMA operation.
*/
enum  sdioh_dma_op_e
{
    SdiohDmaWrite   = 0,
    SdiohDmaRead    = 1
};

/**
  \brief  Defines SDIO Host clock source.
*/
enum  sdioh_clk_src_e
{
    SdiohSscClk     = 0,
    SdiohSscClkVp0  = 1,
    SdiohSscClkVp1  = 2
};

/**
  \brief  Defines SDIO Host clock divider.
*/
enum  sdioh_clk_div_e
{
    SdiohClkDiv1    = 0,
    SdiohClkDiv2    = 1,
    SdiohClkDiv4    = 2,
    SdiohClkDiv8    = 3
};

/**
  \brief  Defines SDCLK divider.
*/
enum  sdioh_sdclk_divider_e
{
    SdiohSdclkDiv128    = 0,
    SdiohSdclkDiv256    = 1
};

/**
  \brief  Defines SDIO Host mode selection.
*/
enum  sdioh_mode_sel_e
{
    SdiohModeSd20   = 0,
    SdiohModeDdr    = 1,
    SdiohModeSd30   = 2
};

/**
  \brief  Defines SDIO Host bus width.
*/
enum  sdioh_bus_width_e
{
    SdiohBus1bit    = 0,
    SdiohBus4bit    = 1
};

/**
  \brief  Defines SDIO Host response type.
*/
enum  sdioh_rsp_type_e
{
    SdiohNoRsp      = 0,
    SdiohRsp6Bytes  = 1,
    SdiohRsp17Bytes = 2
};

/**
  \brief  Defines SDIO bus status.
*/
enum  sdioh_bus_status_e
{
    SdiohBusLow     = 0,
    SdiohBusHigh    = 1
};

/**
  \brief  Defines SDIO Host command code.
*/
enum  sdioh_cmd_code_e
{
    SdiohCmdNormalWr        = 0,
    SdiohCmdAutoWr3         = 1,
    SdiohCmdAutoWr4         = 2,
    SdiohCmdAutoRd3         = 5,
    SdiohCmdAutoRd4         = 6,
    SdiohCmdSendCmdGetRsp   = 8,
    SdiohCmdAutoWr1         = 9,
    SdiohCmdAutoWr2         = 10,
    SdiohCmdNormalRd        = 12,
    SdiohCmdAutoRd1         = 13,
    SdiohCmdAutoRd2         = 14,
    SdiohCmdTuning          = 15
};

/**
  \brief  Defines SDIO Bus Signaling Level.
*/
enum  sdioh_sig_level_e
{
    SdiohSigVol33           = 0,
    SdiohSigVol18           = 1
};

/**
  \brief  Defines the data present select in current transaction.
*/
enum  sdioh_data_present_e
{
    SdiohNoDataPresent      = 0,
    SdiohDataPresent        = 1
};

/**
  \brief  Defines CMD6 operation mode.
*/
enum  sdioh_cmd6_mode_e
{
    SdiohCmd6CheckMode      = 0,
    SdiohCmd6SwitchMode     = 1
};

/**
  \brief  Defines CMD6 function group 1 (access mode).
*/
enum  sdioh_access_mode_e
{
    SdiohSpeedDS            = 0,  // 3.3V Function 0
    SdiohSpeedHS            = 1,  // 3.3V Function 1
    SdiohSpeedSDR12         = 2,  // 1.8V Function 0
    SdiohSpeedSDR25         = 3,  // 1.8V Function 1
    SdiohSpeedSDR50         = 4,  // 1.8V Function 2
    SdiohSpeedSDR104        = 5,  // 1.8V Function 3
    SdiohSpeedDDR50         = 6,  // 1.8V Function 4
    SdiohKeepCurSpd         = 15
};

/**
  \brief  Defines CMD6 function group 3 (driver strength).
*/
enum  sdioh_driver_strength_e
{
    SdiohDriverTypeB        = 0,
    SdiohDriverTypeA        = 1,
    SdiohDriverTypeC        = 2,
    SdiohDriverTypeD        = 3
};

/**
  \brief  Defines CMD6 function group 4 (current limit).
*/
enum  sdioh_current_limit_e
{
    SdiohCurLim200mA        = 0,
    SdiohCurLim400mA        = 1,
    SdiohCurLim600mA        = 2,
    SdiohCurLim800mA        = 3,
};

/**
  \brief  Defines CMD7 select/de-select card.
*/
enum  sdioh_card_selection_e
{
    SdiohDeselCard          = 0,
    SdiohSelCard            = 1
};

/**
  \brief  Defines host capacity support (ACMD41).
*/
enum  sdioh_host_capacity_e
{
    SdiohSupportSdscOnly    = 0,
    SdiohSupportSdhcSdxc    = 1
};

/**
  \brief  Defines SDXC power control (ACMD41).
*/
enum  sdioh_sdxc_pwr_ctl_e
{
    SdiohPwrSaving          = 0,
    SdiohMaxPerformance     = 1
};

/**
  \brief  Defines switch to 1.8V request (ACMD41).
*/
enum  sdioh_switch_18v_req_e
{
    SdiohUseCurrSigVol      = 0,
    SdiohSwitch18v          = 1
};

/**
  \brief  Defines SD card's current state (Card Status bit[12:9]).
*/
enum  sdioh_card_curr_ste_e
{
    SdiohCardSteIdle        = 0,
    SdiohCardSteReady       = 1,
    SdiohCardSteIdent       = 2,
    SdiohCardSteStby        = 3,
    SdiohCardSteTran        = 4,
    SdiohCardSteData        = 5,
    SdiohCardSteRcv         = 6,
    SdiohCardStePrg         = 7,
    SdiohCardSteDis         = 8
};

/**
  \brief  Defines SD physical layer specification version.
*/
enum  sdioh_sd_spec_e
{
    SdiohSdSpecV101         = 0,
    SdiohSdSpecV110         = 1,
    SdiohSdSpecV200         = 2,
    SdiohSdSpecV300         = 3
};

/**
  \brief  Defines SDIO command index.
*/
enum  sdioh_cmd_idx_e
{
    SdiohCmdGoIdleSte           = 0,
    SdiohCmdAllSendCid          = 2,
    SdiohCmdSendRelAddr         = 3,
    SdiohCmdSetDsr              = 4,
    SdiohCmdSwitchFunc          = 6,
    SdiohCmdSetBusWidth         = 6,  // ACMD6
    SdiohCmdSelDeselCard        = 7,
    SdiohCmdSendIfCond          = 8,
    SdiohCmdSendCsd             = 9,
    SdiohCmdSendCid             = 10,
    SdiohCmdVolSwitch           = 11,
    SdiohCmdStopXsmission       = 12,
    SdiohCmdSendSts             = 13,
    SdiohCmdSetBlklen           = 16,
    SdiohCmdRdSingleBlk         = 17,
    SdiohCmdRdMulBlk            = 18,
    SdiohCmdSendTuningBlk       = 19,
    SdiohCmdSendNumWrBlks       = 22,  // ACMD22
    SdiohCmdSetBlkCnt           = 23,
    SdiohCmdSetWrBlkEraseCnt    = 23,  // ACMD23
    SdiohCmdWrBlk               = 24,
    SdiohCmdWrMulBlk            = 25,
    SdiohCmdProgCsd             = 27,
    SdiohCmdEraseBlkSt          = 32,
    SdiohCmdEraseBlkEd          = 33,
    SdiohCmdErase               = 38,
    SdiohCmdSdSendOpCond        = 41,  // ACMD41
    SdiohCmdSendScr             = 51,  // ACMD51
    SdiohCmdAppCmd              = 55
};


/**
  \brief  Callback function for SD card detection event.
*/
typedef void (*sdioh_card_detect)(void *para);
/**
  \brief  Callback function to make OS do a context-switch while waiting.
*/
typedef void (*sdioh_task_yield)(void);


/**
  \brief  The structure of the settings for DMA control.
*/
typedef struct hal_sdioh_dma_ctrl_s {
    u32 start_addr;
    u16 blk_cnt;
    u8 op;
    u8 type;
} hal_sdioh_dma_ctrl_t, *phal_sdioh_dma_ctrl_t;

/**
  \brief  The structure of command attributes.
*/
typedef struct hal_sdioh_cmd_attr_s {
    u32 arg;
    u8 idx;
    u8 rsp_type;
    u8 rsp_crc_chk;
    u8 data_present;
} hal_sdioh_cmd_attr_t, *phal_sdioh_cmd_attr_t;

/**
  \brief  The data structure for SDIO host HAL operations.
*/
typedef struct hal_sdio_host_adapter_s {
    SDIO_HOST_Type *base_addr;
    u32 xfer_int_sts;
    u8 csd[SDIOH_CSD_LEN];
    u16 rca;
    volatile u8 is_card_inserted;
    volatile u8 is_wp;
    u8 curr_sig_level;
    u8 is_sdhc_sdxc;
    u8 card_curr_ste;
    u8 sd_spec_ver;
    u8 curr_bus_spd;
    u8 pin_mux_sel;
    u8 card_support_spd_mode;
    u8 is_s18a;
    u8 voltage_mismatch;
    u8 rsvd[3];
    sdioh_card_detect card_insert_cb;
    sdioh_card_detect card_remove_cb;
    void *card_insert_cb_para;
    void *card_remove_cb_para;
    sdioh_task_yield task_yield;
    void (*dcache_invalidate_by_addr)(uint32_t *addr, int32_t dsize);   /*! callback function to do the D-cache invalidate  */
    void (*dcache_clean_by_addr) (uint32_t *addr, int32_t dsize);   /*! callback function to do the D-cache clean  */
    u8 rsvd2[27];
    u8 c6r2_buf[SDIOH_C6R2_BUF_LEN] __attribute__((aligned(32)));
} hal_sdio_host_adapter_t, *phal_sdio_host_adapter_t;

/**
  \brief  The data structure of the stubs function for the SDIO Host HAL functions in ROM
*/
typedef struct hal_sdioh_func_stubs_s {
    io_pin_t *sdioh_pin_table;
    void (*hal_sdioh_pin_ctrl) (sdioh_pin_sel_t pin_sel, BOOL en);
    void (*hal_sdioh_irq_handler) (void);
    void (*hal_sdioh_irq_reg) (irq_handler_t irq_handler);
    void (*hal_sdioh_irq_unreg) (void);
    hal_status_t (*hal_sdioh_init_host) (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_pin_sel_t pin_sel);
    hal_status_t (*hal_sdioh_init_card) (hal_sdio_host_adapter_t *psdioh_adapter);
    void (*hal_sdioh_deinit) (hal_sdio_host_adapter_t *psdioh_adapter);
    hal_status_t (*hal_sdioh_read_data) (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u16 blk_cnt, u8 *rbuf_32align);
    hal_status_t (*hal_sdioh_write_data) (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u16 blk_cnt, u8 *wbuf_32align);
    hal_status_t (*hal_sdioh_erase) (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u64 end_addr);
    hal_status_t (*hal_sdioh_stop_transmission) (hal_sdio_host_adapter_t *psdioh_adapter);
    hal_status_t (*hal_sdioh_get_card_status) (hal_sdio_host_adapter_t *psdioh_adapter);
    hal_status_t (*hal_sdioh_get_sd_status) (hal_sdio_host_adapter_t *psdioh_adapter, u8 *buf_32align);
    hal_status_t (*hal_sdioh_switch_bus_speed) (hal_sdio_host_adapter_t *psdioh_adapter, u8 speed);
    u8 (*hal_sdioh_get_curr_signal_level) (hal_sdio_host_adapter_t *psdioh_adapter);
    hal_status_t (*hal_sdioh_get_supported_speed) (hal_sdio_host_adapter_t *psdioh_adapter, u8 *value);
    void (*hal_sdioh_card_insert_hook) (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_card_detect pcallback, void *pdata);
    void (*hal_sdioh_card_remove_hook) (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_card_detect pcallback, void *pdata);
    void (*hal_sdioh_task_yield_hook) (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_task_yield task_yield);
    uint32_t reserved[8];  // reserved space for next ROM code version function table extending.
} hal_sdioh_func_stubs_t;


/// @cond DOXYGEN_ROM_HAL_API

/** 
 * @addtogroup hs_hal_sdio_host_rom_func SDIO Host HAL ROM APIs.
 * @ingroup hs_hal_sdio_host
 * @{
 */

void hal_sdioh_pin_ctrl_rtl8195bhp (sdioh_pin_sel_t pin_sel, BOOL en);
void hal_sdioh_irq_reg_rtl8195bhp (irq_handler_t irq_handler);
void hal_sdioh_irq_unreg_rtl8195bhp (void);
hal_status_t hal_sdioh_init_host_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_pin_sel_t pin_sel);
hal_status_t hal_sdioh_init_card_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter);
void hal_sdioh_deinit_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter);
hal_status_t hal_sdioh_read_data_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u16 blk_cnt, u8 *rbuf_32align);
hal_status_t hal_sdioh_write_data_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u16 blk_cnt, u8 *wbuf_32align);
hal_status_t hal_sdioh_erase_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter, u64 start_addr, u64 end_addr);
hal_status_t hal_sdioh_stop_transmission_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter);
hal_status_t hal_sdioh_get_card_status_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter);
hal_status_t hal_sdioh_get_sd_status_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter, u8 *buf_32align);
hal_status_t hal_sdioh_switch_bus_speed_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter, u8 speed);
u8 hal_sdioh_get_curr_signal_level_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter);
hal_status_t hal_sdioh_get_supported_speed_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter, u8 *value);
void hal_sdioh_card_insert_hook_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_card_detect pcallback, void *pdata);
void hal_sdioh_card_remove_hook_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_card_detect pcallback, void *pdata);
void hal_sdioh_task_yield_hook_rtl8195bhp (hal_sdio_host_adapter_t *psdioh_adapter, sdioh_task_yield task_yield);

/** @} */ /* End of group hs_hal_sdio_host_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */
/** @} */ /* End of group hs_hal_sdio_host */

#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _RTL8195BH_SDIO_HOST_H_"


