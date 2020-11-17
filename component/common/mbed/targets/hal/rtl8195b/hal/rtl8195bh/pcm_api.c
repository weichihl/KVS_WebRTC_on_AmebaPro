/**************************************************************************//**
 * @file     pcm_api.c
 * @brief    This file implements the PCM Mbed HAL API functions.
 *
 * @version  V1.00
 * @date     2017-05-03
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of version 2 of the GNU General Public License as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
 *
 ******************************************************************************/
#include "objects.h"
#include "pinmap.h"
#include "pcm_api.h"
#include "hal_pcm.h"

void pcm_init(pcm_t *obj, PinName sync, PinName clk, PinName out, PinName in)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    HAL_Status ret;
    u8 i;
    u32 pin_combin_tp;
    s32 pin_combin[4] = {(PE_0 << 24) | (PE_1 << 16) | (PE_2 << 8) | PE_3,\
                         (PG_0 << 24) | (PG_1 << 16) | (PG_2 << 8) | PG_3,\
                         (PB_0 << 24) | (PB_1 << 16) | (PB_2 << 8) | PB_3,\
                         (PG_6 << 24) | (PG_7 << 16) | (PG_8 << 8) | PG_9};

    pin_combin_tp = (u32)((sync << 24) | (clk << 16) | (out << 8) | in);

    for (i = 0; i < 4; i++) {
        if (pin_combin_tp == (u32)pin_combin[i]) {
            ppcm_adapter->pcm_index = (i & 0x02) >> 1;
            ppcm_adapter->pin_sel = (i & 0x01);
            DBG_PCM_INFO("pcm_init pin, id:%d, pcm_index:%d, pin_sel: %d\r\n", i, ppcm_adapter->pcm_index, ppcm_adapter->pin_sel);
            break;
        }
    }

    if (i == 4) {
        DBG_PCM_WARN("pcm_init, did not meet the pin group of pcm \r\n");
    }

    ppcm_adapter->user_cb.tx_cbid = (u32)obj;
    ppcm_adapter->user_cb.rx_cbid = (u32)obj;

    ppcm_adapter->dcache_memory_en = 1;

    ret = hal_pcm_init(ppcm_adapter);

    if(ret != HAL_OK){
        DBG_PCM_ERR("pcm_init is failure\r\n");
    } else {
        hal_pcm_en_ctrl(&obj->pcm_adapter, 1);
    }

}

void pcm_tx_irq_handler(pcm_t *obj, pcm_ch chan, pcm_irq_handler handler)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    ppcm_adapter->user_cb.tx_ccb[chan] = handler;
}

void pcm_rx_irq_handler(pcm_t *obj, pcm_ch chan, pcm_irq_handler handler)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    ppcm_adapter->user_cb.rx_ccb[chan] = handler;
}

void pcm_set_format(pcm_t *obj, pcm_ms_mode ms_mode, pcm_mode linear_mode, pcm_loopback_mode loop_back, pcm_endian_swap endian_swap, pcm_frame_active fs_inv)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    hal_pcm_format_t pcm_format;

    pcm_format.pcm_slave = ms_mode;
    pcm_format.pcm_linear_mode = linear_mode;
    pcm_format.pcm_loop_back = loop_back;
    pcm_format.pcm_endian_swap = endian_swap;
    pcm_format.pcm_fs_inv = fs_inv;
    hal_pcm_set_format(ppcm_adapter, &pcm_format);

    pcm_reset(obj);
}

void pcm_set_dma_buffer(pcm_t *obj, pcm_ch chan, u16 *tx_buf, u16 *rx_buf)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    hal_pcm_set_ch_tx_adr(ppcm_adapter, chan, tx_buf);
    hal_pcm_set_ch_rx_adr(ppcm_adapter, chan, rx_buf);
}

void pcm_chan_trx_ctrl(pcm_t *obj, pcm_ch chan, BOOL tx_en, BOOL rx_en)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    paisr_n_t paisr_n;
    paimr_n_t paimr_n;

    paisr_n.w = 0xFF;
    hal_pcm_clr_ch_intr_ctrl(ppcm_adapter, chan, paisr_n);

    paimr_n.w = 0x00;
    if(tx_en == 0){
        paimr_n.b.chnp0tokie = 0;
        paimr_n.b.chnp1tokie = 0;
    } else {
        paimr_n.b.chnp0tokie = 1;
        paimr_n.b.chnp1tokie = 1;
    }

    if(rx_en == 0){
        paimr_n.b.chnp0rokie = 0;
        paimr_n.b.chnp1rokie = 0;
    } else {
        paimr_n.b.chnp0rokie = 1;
        paimr_n.b.chnp1rokie = 1;
    }
    hal_pcm_set_ch_intr_ctrl(ppcm_adapter, chan, paimr_n);

    hal_pcm_reg_ch_tx_en(ppcm_adapter, chan, tx_en);
    hal_pcm_reg_ch_rx_en(ppcm_adapter, chan, rx_en);

}

void pcm_chan_page_size(pcm_t *obj, pcm_ch chan, u32 page_size)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    u32 page_size_word;
    u8 error_flag;

    error_flag = 0;
    if (page_size < 2) {
        error_flag = 1;
        DBG_PCM_ERR("pcm_chan_page_size, the minimum page_size is 2  \r\n");
    }

    if (page_size > 512) {
        error_flag = 1;
        DBG_PCM_ERR("pcm_chan_page_size, the maximum page_size is 512  \r\n");
    }

    if ((page_size & 0x01) == 0x01) {
        error_flag = 1;
        DBG_PCM_ERR("pcm_chan_page_size, page_size needs the even value  \r\n");
    }

    if (error_flag == 0x00) {
        /*PCM Page Size: 2~512, need the even value, unit: 2 bytes */
        page_size_word = (page_size >> 1) - 1;
        hal_pcm_set_ch_page_size(ppcm_adapter, chan, (u8)page_size_word);
    }

}

void pcm_chan_time_slot(pcm_t *obj, pcm_ch chan, pcm_slot slot)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    u32 linear_mode_tp;
    u8 error_flag = 0;

    linear_mode_tp = hal_pcm_get_linear_mode(ppcm_adapter);

    if (linear_mode_tp == 0x01) {
        if ((slot & 0x01) != 0x00) {
            error_flag = 1;
            DBG_PCM_ERR("pcm_chan_time_slot: In the linear mode, the slot needs the even number. \r\n");
        }
    }

    if (error_flag == 0x00) {
        /*PCM Time slot assignment  slot: 0~31*/
        hal_pcm_set_ch_time_slot(ppcm_adapter, chan, slot);
    }
}

void pcm_chan_wideband(pcm_t *obj, pcm_ch chan, BOOL wband_en, pcm_slot wtsa)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    u32 linear_mode_tp;
    u8 error_flag = 0;

    if (wband_en == 1) {

        linear_mode_tp = hal_pcm_get_linear_mode(ppcm_adapter);

        if (linear_mode_tp == 0x01) {
            if ((wtsa & 0x01) != 0x00) {
                error_flag = 1;
                DBG_PCM_ERR("pcm_chan_wideband: In the linear mode, the slot needs the even number. \r\n");
            }
        }

        if (error_flag == 0x00) {
            if (chan < 8) {
                /*PCM Wideband enable for ch0~ch7*/
                hal_pcm_set_ch_wideband_en(ppcm_adapter, chan, 1);
                /*PCM Wideband time slot assignment  slot0...slot31 only for ch0~ch7*/
                hal_pcm_set_ch_wb_time_slot(ppcm_adapter, chan, wtsa);
            } else {
                DBG_PCM_ERR("pcm_chan_wideband: The Channel %d is invalid. The valid channels are CH0~CH7\n", chan);
            }
        }

    } else {
        hal_pcm_set_ch_wideband_en(ppcm_adapter, chan, 0);
    }

}

void pcm_chan_compender_law(pcm_t *obj, pcm_ch chan, pcm_ua_law ua_law)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    /*PCM Choice U-law: 0 or A-law: 1 in compander mode*/
    hal_pcm_set_ch_ua_law(ppcm_adapter, chan, ua_law);
}

void pcm_reset(pcm_t *obj)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    u32 en_ctrl_tp;

    //PCM reset
    hal_pcm_dis_all_trx(ppcm_adapter);
    en_ctrl_tp = hal_pcm_get_en_ctrl(ppcm_adapter);
    hal_pcm_en_ctrl(ppcm_adapter, ENABLE);
    hal_pcm_en_ctrl(ppcm_adapter, DISABLE);
    hal_pcm_en_ctrl(ppcm_adapter, en_ctrl_tp);

    //PCM Clear all interrupts
    hal_pcm_clr_all_intr(ppcm_adapter);

    ppcm_adapter->pcm_tx_page_idx_table = 0x00;
    ppcm_adapter->pcm_rx_page_idx_table = 0x00;

}

void pcm_clear_all_Intr(pcm_t *obj)
{
    hal_pcm_clr_all_intr(&obj->pcm_adapter);
}

void pcm_disable_all_Intr(pcm_t *obj)
{
    hal_pcm_dis_all_intr(&obj->pcm_adapter);
}

void pcm_disable(pcm_t *obj)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    hal_pcm_dis_all_trx(ppcm_adapter);
    hal_pcm_dis_all_intr(ppcm_adapter);
    hal_pcm_clr_all_intr(ppcm_adapter);
    hal_pcm_en_ctrl(ppcm_adapter, DISABLE);
}

void pcm_enable(pcm_t *obj)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    hal_pcm_en_ctrl(ppcm_adapter, ENABLE);
    hal_pcm_dis_all_trx(ppcm_adapter);
    hal_pcm_dis_all_intr(ppcm_adapter);
    hal_pcm_clr_all_intr(ppcm_adapter);
}

void pcm_deinit(pcm_t *obj)
{
    hal_pcm_dis_all_trx(&obj->pcm_adapter);
    hal_pcm_dis_all_intr(&obj->pcm_adapter);
    hal_pcm_clr_all_intr(&obj->pcm_adapter);
    hal_pcm_deinit(&obj->pcm_adapter);
}

void pcm_start_trx(pcm_t *obj)
{
    u32 i;
    u16 pcm_tx_ch_table_tp, pcm_rx_ch_table_tp;

    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    ppcm_adapter->pcm_tx_page_idx_table = 0x00;
    ppcm_adapter->pcm_rx_page_idx_table = 0x00;

    hal_pcm_clr_all_intr(ppcm_adapter);

    pcm_tx_ch_table_tp = ppcm_adapter->pcm_tx_ch_table;
    pcm_rx_ch_table_tp = ppcm_adapter->pcm_rx_ch_table;

    for(i=0;i<16;i++){

        if ((pcm_tx_ch_table_tp & 0x01) == 0x01) {
            hal_pcm_ch_write_memory_cache_clean(ppcm_adapter, i, 0);
            hal_pcm_ch_write_memory_cache_clean(ppcm_adapter, i, 1);
            hal_pcm_set_ch_tx_own(ppcm_adapter, i, 1, 1);
        }
        pcm_tx_ch_table_tp = pcm_tx_ch_table_tp >> 1;

        if ((pcm_rx_ch_table_tp & 0x01) == 0x01) {
            hal_pcm_set_ch_rx_own(ppcm_adapter, i, 1, 1);
        }
        pcm_rx_ch_table_tp = pcm_rx_ch_table_tp >> 1;

    }

    hal_pcm_start_trx(ppcm_adapter);

}

void pcm_start_tx_chan(pcm_t *obj, pcm_ch chan)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    paisr_n_t paisr_n;
    u16 idex_tp, pcm_tx_ch_table_tp;

    idex_tp = 0x01 << chan;
    ppcm_adapter->pcm_tx_page_idx_table &= (~idex_tp);

    pcm_tx_ch_table_tp = ppcm_adapter->pcm_tx_ch_table;
    if ((pcm_tx_ch_table_tp & idex_tp) == idex_tp) {

        paisr_n.b.chntxp1ua = 1;
        paisr_n.b.chntxp0ua = 1;
        paisr_n.b.chntxp1ip = 1;
        paisr_n.b.chntxp0ip = 1;
        hal_pcm_clr_ch_intr_ctrl(ppcm_adapter, chan, paisr_n);

        hal_pcm_ch_write_memory_cache_clean(ppcm_adapter, chan, 0);
        hal_pcm_ch_write_memory_cache_clean(ppcm_adapter, chan, 1);
        hal_pcm_set_ch_tx_own(ppcm_adapter, chan, 1, 1);
        hal_pcm_set_ch_tx_en(ppcm_adapter, chan, 1);
    }

}

void pcm_start_rx_chan(pcm_t *obj, pcm_ch chan)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    paisr_n_t paisr_n;
    u16 idex_tp, pcm_rx_ch_table_tp;

    idex_tp = 0x01 << chan;
    ppcm_adapter->pcm_rx_page_idx_table &= (~idex_tp);

    pcm_rx_ch_table_tp = ppcm_adapter->pcm_rx_ch_table;
    if ((pcm_rx_ch_table_tp & idex_tp) == idex_tp) {

        paisr_n.b.chnrxp1ua = 1;
        paisr_n.b.chnrxp0ua = 1;
        paisr_n.b.chnrxp1ip = 1;
        paisr_n.b.chnrxp0ip = 1;
        hal_pcm_clr_ch_intr_ctrl(ppcm_adapter, chan, paisr_n);

        hal_pcm_set_ch_rx_own(ppcm_adapter, chan, 1, 1);
        hal_pcm_set_ch_rx_en(ppcm_adapter, chan, 1);
    }

}

void pcm_stop_trx_all_chan(pcm_t *obj)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    u32 i;
    u16 pcm_rx_ch_table_tp;

    ppcm_adapter->pcm_tx_page_idx_table = 0x00;
    ppcm_adapter->pcm_rx_page_idx_table = 0x00;

    hal_pcm_dis_all_trx(ppcm_adapter);
    hal_pcm_clr_all_intr(ppcm_adapter);

    pcm_rx_ch_table_tp = ppcm_adapter->pcm_rx_ch_table;
    for (i = 0; i < 16; i++) {

        if ((pcm_rx_ch_table_tp & 0x01) == 0x01) {
            hal_pcm_ch_read_memory_cache_invalidate(ppcm_adapter, i, 0);
            hal_pcm_ch_read_memory_cache_invalidate(ppcm_adapter, i, 1);
        }
        pcm_rx_ch_table_tp = pcm_rx_ch_table_tp >> 1;
    }

}

void pcm_stop_tx_all_chan(pcm_t *obj)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    ppcm_adapter->pcm_tx_page_idx_table = 0x00;
    hal_pcm_dis_all_tx(&obj->pcm_adapter);
}

void pcm_stop_rx_all_chan(pcm_t *obj)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    u32 i;
    u16 pcm_rx_ch_table_tp;

    ppcm_adapter->pcm_rx_page_idx_table = 0x00;
    hal_pcm_dis_all_rx(&obj->pcm_adapter);

    pcm_rx_ch_table_tp = ppcm_adapter->pcm_rx_ch_table;
    for (i = 0; i < 16; i++) {

        if ((pcm_rx_ch_table_tp & 0x01) == 0x01) {
            hal_pcm_ch_read_memory_cache_invalidate(ppcm_adapter, i, 0);
            hal_pcm_ch_read_memory_cache_invalidate(ppcm_adapter, i, 1);
        }
        pcm_rx_ch_table_tp = pcm_rx_ch_table_tp >> 1;
    }

}

void pcm_stop_tx_chan(pcm_t *obj, pcm_ch chan)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    paisr_n_t paisr_n;

    ppcm_adapter->pcm_tx_page_idx_table &= (~(0x01 << chan));

    hal_pcm_set_ch_tx_en(ppcm_adapter, chan, 0);
    paisr_n.w = 0;
    paisr_n.b.chntxp1ua = 1;
    paisr_n.b.chntxp0ua = 1;
    paisr_n.b.chntxp1ip = 1;
    paisr_n.b.chntxp0ip = 1;
    hal_pcm_clr_ch_intr_ctrl(ppcm_adapter, chan, paisr_n);
}

void pcm_stop_rx_chan(pcm_t *obj, pcm_ch chan)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    paisr_n_t paisr_n;

    ppcm_adapter->pcm_rx_page_idx_table &= (~(0x01 << chan));

    hal_pcm_set_ch_rx_en(ppcm_adapter, chan, 0);
    paisr_n.w = 0;
    paisr_n.b.chnrxp1ua = 1;
    paisr_n.b.chnrxp0ua = 1;
    paisr_n.b.chnrxp1ip = 1;
    paisr_n.b.chnrxp0ip = 1;
    hal_pcm_clr_ch_intr_ctrl(ppcm_adapter, chan, paisr_n);

    hal_pcm_ch_read_memory_cache_invalidate(ppcm_adapter, chan, 0);
    hal_pcm_ch_read_memory_cache_invalidate(ppcm_adapter, chan, 1);

}

u8 *pcm_irq_get_tx_next_page_adr(pcm_t *obj)
{
    u16 pcm_tx_page_idx_table;
    u8 channel;
    u8 page_own_tp;
    u8 *page_adr_tp;

    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    pcm_tx_page_idx_table = ppcm_adapter->pcm_tx_page_idx_table;
    channel = ppcm_adapter->irq_info_ch.channel_info;
    pcm_tx_page_idx_table = pcm_tx_page_idx_table & (1 << channel);

    if (pcm_tx_page_idx_table == 0x00) {
        page_own_tp = ppcm_adapter->irq_info_ch.tx_own_sta[0];
        page_adr_tp = (u8 *)ppcm_adapter->irq_info_ch.tx_p0_adr;
    } else {
        page_own_tp = ppcm_adapter->irq_info_ch.tx_own_sta[1];
        page_adr_tp = (u8 *)ppcm_adapter->irq_info_ch.tx_p1_adr;
    }

    if (page_own_tp == 0x00) {
        return page_adr_tp;
    } else {
        DBG_PCM_WARN("pcm_irq_get_tx_next_page_adr: page_own is error!!! \r\n");
        return NULL;
    }

}

void pcm_irq_set_txpage(pcm_t *obj)
{
    u16 pcm_tx_page_idx_table;
    u8 channel;

    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    pcm_tx_page_idx_table = ppcm_adapter->pcm_tx_page_idx_table;
    channel = ppcm_adapter->irq_info_ch.channel_info;
    pcm_tx_page_idx_table = pcm_tx_page_idx_table & (1 << channel);

    if (pcm_tx_page_idx_table == 0x00) {
        hal_pcm_ch_write_memory_cache_clean(ppcm_adapter, channel, 0);
        hal_pcm_set_ch_tx_own(ppcm_adapter, channel, 1, 0);
    } else {
        hal_pcm_ch_write_memory_cache_clean(ppcm_adapter, channel, 1);
        hal_pcm_set_ch_tx_own(ppcm_adapter, channel, 0, 1);
    }

    hal_pcm_update_sw_ch_tx_idx(ppcm_adapter, channel);
}

void pcm_irq_set_rxpage(pcm_t *obj)
{
    u16 pcm_rx_page_idx_table;
    u8 channel;

    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    pcm_rx_page_idx_table = ppcm_adapter->pcm_rx_page_idx_table;
    channel = ppcm_adapter->irq_info_ch.channel_info;
    pcm_rx_page_idx_table = pcm_rx_page_idx_table & (1 << channel);

    if (pcm_rx_page_idx_table == 0x00) {
        hal_pcm_set_ch_rx_own(ppcm_adapter, channel, 1, 0);
    } else {
        hal_pcm_set_ch_rx_own(ppcm_adapter, channel, 0, 1);
    }

    hal_pcm_update_sw_ch_rx_idx(ppcm_adapter, channel);
}

u8 pcm_irq_get_channel(pcm_t *obj)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    return ppcm_adapter->irq_info_ch.channel_info;
}

u32 pcm_irq_get_buffer_size(pcm_t *obj)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    return ppcm_adapter->irq_info_ch.buf_size_info;
}

u8 pcm_irq_get_page_0_or_1(pcm_t *obj)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    return ppcm_adapter->irq_info_ch.irq_page_info;
}

u8 *pcm_get_tx_next_page_adr(pcm_t *obj, pcm_ch chan)
{
    u16 pcm_tx_page_idx_table;
    u8 page_own_tp;
    u8 *page_adr_tp;
    hal_pcm_irqinfo_ch_t irq_info_ch;

    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    pcm_tx_page_idx_table = ppcm_adapter->pcm_tx_page_idx_table;
    pcm_tx_page_idx_table = pcm_tx_page_idx_table & (1 << chan);

    hal_pcm_get_ch_trx_info(ppcm_adapter, chan, &irq_info_ch);

    if (pcm_tx_page_idx_table == 0x00) {
        page_own_tp = irq_info_ch.tx_own_sta[0];
        page_adr_tp = (u8 *)irq_info_ch.tx_p0_adr;
    } else {
        page_own_tp = irq_info_ch.tx_own_sta[1];
        page_adr_tp = (u8 *)irq_info_ch.tx_p1_adr;
    }

    if (page_own_tp == 0x00) {
        return page_adr_tp;
    } else {
        DBG_PCM_WARN("pcm_irq_get_tx_next_page_adr: page_own is error!!! \r\n");
        return NULL;
    }

}

void pcm_set_txpage(pcm_t *obj, pcm_ch chan)
{
    u16 pcm_tx_page_idx_table;

    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    pcm_tx_page_idx_table = ppcm_adapter->pcm_tx_page_idx_table;
    pcm_tx_page_idx_table = pcm_tx_page_idx_table & (1 << chan);

    if (pcm_tx_page_idx_table == 0x00) {
        hal_pcm_ch_write_memory_cache_clean(ppcm_adapter, chan, 0);
        hal_pcm_set_ch_tx_own(ppcm_adapter, chan, 1, 0);
    } else {
        hal_pcm_ch_write_memory_cache_clean(ppcm_adapter, chan, 1);
        hal_pcm_set_ch_tx_own(ppcm_adapter, chan, 0, 1);
    }

    hal_pcm_update_sw_ch_tx_idx(ppcm_adapter, chan);
}

void pcm_set_rxpage(pcm_t *obj, pcm_ch chan)
{
    u16 pcm_rx_page_idx_table;

    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;

    pcm_rx_page_idx_table = ppcm_adapter->pcm_rx_page_idx_table;
    pcm_rx_page_idx_table = pcm_rx_page_idx_table & (1 << chan);

    if (pcm_rx_page_idx_table == 0x00) {
        hal_pcm_set_ch_rx_own(ppcm_adapter, chan, 1, 0);
    } else {
        hal_pcm_set_ch_rx_own(ppcm_adapter, chan, 0, 1);
    }

    hal_pcm_update_sw_ch_rx_idx(ppcm_adapter, chan);
}

u32 pcm_get_buffer_size(pcm_t *obj, pcm_ch chan)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    hal_pcm_irqinfo_ch_t irq_info_ch;

    hal_pcm_get_ch_trx_info(ppcm_adapter, chan, &irq_info_ch);

    return irq_info_ch.buf_size_info;
}

u32 pcm_get_tx_page0_adr(pcm_t *obj, pcm_ch chan)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    hal_pcm_irqinfo_ch_t irq_info_ch;

    hal_pcm_get_ch_trx_info(ppcm_adapter, chan, &irq_info_ch);

    return irq_info_ch.tx_p0_adr;
}

u32 pcm_get_tx_page1_adr(pcm_t *obj, pcm_ch chan)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    hal_pcm_irqinfo_ch_t irq_info_ch;

    hal_pcm_get_ch_trx_info(ppcm_adapter, chan, &irq_info_ch);

    return irq_info_ch.tx_p1_adr;
}

u32 pcm_get_rx_page0_adr(pcm_t *obj, pcm_ch chan)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    hal_pcm_irqinfo_ch_t irq_info_ch;

    hal_pcm_get_ch_trx_info(ppcm_adapter, chan, &irq_info_ch);

    return irq_info_ch.rx_p0_adr;
}

u32 pcm_get_rx_page1_adr(pcm_t *obj, pcm_ch chan)
{
    hal_pcm_adapter_t *ppcm_adapter = &obj->pcm_adapter;
    hal_pcm_irqinfo_ch_t irq_info_ch;

    hal_pcm_get_ch_trx_info(ppcm_adapter, chan, &irq_info_ch);

    return irq_info_ch.rx_p1_adr;
}

