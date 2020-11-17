/**************************************************************************//**
 * @file     i2s_api.c
 * @brief    This file implements the I2S Mbed HAL API functions.
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
#include "i2s_api.h"
#include "hal_i2s.h"

hal_i2s_def_setting_t i2s_def_setting = {

    .i2s_format = I2S_FORMAT_I2S,
    .i2s_master = I2S_MASTER_MODE,
    .i2s_ch_num = I2S_CH_STEREO,
    .i2s_page_num = I2S_4PAGE,
    .i2s_trx_act = I2S_TXRX,
    .i2s_word_len = I2S_WL_16,
    .i2s_page_size = 1320,
    .i2s_rate = I2S_SR_7p35KHZ,
    .i2s_burst_size = I2S_BURST8,
    .i2s_byte_swap = DISABLE,
    .i2s_sck_inv = DISABLE,
    .i2s_ws_swap = I2S_LEFT_PHASE,
    .i2s_loop_back = DISABLE,
    .i2s_edge_sw = I2S_NEGATIVE_EDGE,

    .i2s_tx_intr_msk = I2S_TX_INT_PAGE0_OK|I2S_TX_INT_PAGE1_OK| \
                    I2S_TX_INT_PAGE2_OK|I2S_TX_INT_PAGE3_OK,
    .i2s_rx_intr_msk = I2S_RX_INT_PAGE0_OK|I2S_RX_INT_PAGE1_OK| \
                    I2S_RX_INT_PAGE2_OK|I2S_RX_INT_PAGE3_OK
};

void i2s_sw_reset(i2s_t *obj)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_reset(pi2s_adapter);
}

void i2s_init(i2s_t *obj, PinName sck, PinName ws, PinName sd_tx0, PinName sd_rx, PinName mck, PinName sd_tx1, PinName sd_tx2)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;
    HAL_Status ret;
    uint8_t I2S0_S0[4] = {PE_5, PE_3, PE_4, PE_6};
    uint8_t I2S0_S1[4] = {PG_6, PG_3, PG_4, PG_5};
    uint8_t I2S1_S0[4] = {PB_6, PB_3, PB_4, PB_5};
    uint8_t I2S1_S1[4] = {PG_5, PG_9, PIN_LIST_END, PIN_LIST_END};
    uint8_t *pcmp_adr;
    u8 pin_error = 0;
    u8 pin_app_type = 0;

    pi2s_adapter->dev_num = I2s0_Sel;
    pi2s_adapter->pin_sel = I2s_PinSel_0;
    pi2s_adapter->i2s_app_pin_sel = I2s_2ch_Ws_Clk_Tx0;

    if ((ws == PE_0) && (sck == PE_1) && (sd_tx0 == PE_2)) {
        pcmp_adr = I2S0_S0;
    } else if ((ws == PG_0) && (sck == PG_1) && (sd_tx0 == PG_2)) {
        pi2s_adapter->pin_sel = I2s_PinSel_1;
        pcmp_adr = I2S0_S1;
    } else if ((ws == PB_0) && (sck == PB_1) && (sd_tx0 == PB_2)) {
        pi2s_adapter->dev_num = I2s1_Sel;
        pcmp_adr = I2S1_S0;
    } else if ((ws == PG_6) && (sck == PG_7) && (sd_tx0 == PG_8)) {
        pi2s_adapter->dev_num = I2s1_Sel;
        pi2s_adapter->pin_sel = I2s_PinSel_1;
        pcmp_adr = I2S1_S1;
    } else {
        pin_error = 1;
    }

    if (pin_error == 0x00) {
        if (sd_rx == *pcmp_adr) {
            pi2s_adapter->i2s_app_pin_sel = I2s_2ch_Ws_Clk_Tx0_Rx;
            pin_app_type = 1;
            if (mck == *(pcmp_adr + 1)) {
                pi2s_adapter->i2s_app_pin_sel = I2s_2ch_Ws_Clk_Tx0_Rx_Mclk;
                pin_app_type = 4;
            }
        } else if ((sd_tx1 == *(pcmp_adr + 2)) && (sd_tx2 == *(pcmp_adr + 3))) {
            pi2s_adapter->i2s_app_pin_sel = I2s_5p1ch_Ws_Clk_Tx0_Tx1_TX2;
            pin_app_type = 2;
            if (mck == *(pcmp_adr + 1)) {
                pi2s_adapter->i2s_app_pin_sel = I2s_5p1ch_Ws_Clk_Tx0_Tx1_TX2_Mclk;
                pin_app_type = 5;
            }
        } else if (mck == *(pcmp_adr + 1)) {
            pi2s_adapter->i2s_app_pin_sel = I2s_2ch_Ws_Clk_Tx0_Mclk;
            pin_app_type = 3;
        }
    } else {
        DBG_I2S_ERR("i2s_init : i2s pin is invalid\r\n");
    }

    if (pin_app_type == 0) {
        DBG_I2S_INFO("i2s_init pin: I2s_2ch_Ws_Clk_Tx0 \r\n");
    } else if (pin_app_type == 1) {
        DBG_I2S_INFO("i2s_init pin: I2s_2ch_Ws_Clk_Tx0_Rx \r\n");
    } else if (pin_app_type == 2) {
        DBG_I2S_INFO("i2s_init pin: I2s_5p1ch_Ws_Clk_Tx0_Tx1_TX2 \r\n");
    } else if (pin_app_type == 3) {
        DBG_I2S_INFO("i2s_init pin: I2s_2ch_Ws_Clk_Tx0_Mclk \r\n");
    } else if (pin_app_type == 4) {
        DBG_I2S_INFO("i2s_init pin: I2s_2ch_Ws_Clk_Tx0_Rx_Mclk \r\n");
    } else if (pin_app_type == 5) {
        DBG_I2S_INFO("i2s_init pin: I2s_5p1ch_Ws_Clk_Tx0_Tx1_TX2_Mclk \r\n");
    }

    pi2s_adapter->dcache_memory_en = 1;

    ret = hal_i2s_init(pi2s_adapter);

    if(ret != HAL_OK){
        DBG_I2S_ERR("i2s_init is failure\r\n");
    }

    hal_i2s_set_parameter(pi2s_adapter, &i2s_def_setting);

}

void i2s_set_dma_buffer(i2s_t *obj, char *tx_buf, char *rx_buf,
    u32 page_num, u32 page_size)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;
    u32 i;

    if ((page_num < 2) || (page_num > 4) || (page_size < 8)) {
        DBG_I2S_INFO("PageNum(%d) valid value is 2~4; PageSize(%d must > 8)\r\n", page_num, page_size);
        return;
    }

    pi2s_adapter->init_dat.i2s_tx_data = (u8 *)tx_buf;
    pi2s_adapter->init_dat.i2s_rx_data = (u8 *)rx_buf;

    hal_i2s_set_dma_buf(pi2s_adapter, (page_size/4 - 1), page_num);

    for (i=0;i<page_num;i++) {
        pi2s_adapter->ptx_page_list[i] = (u32 *)(tx_buf + ((page_size) * i));
        pi2s_adapter->prx_page_list[i] = (u32 *)(rx_buf + ((page_size) * i));
    }

}

void i2s_tx_irq_handler(i2s_t *obj, i2s_irq_handler handler, u32 id)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    pi2s_adapter->user_cb.tx_ccb = handler;
    pi2s_adapter->user_cb.tx_cbid = id;
}

void i2s_rx_irq_handler(i2s_t *obj, i2s_irq_handler handler, u32 id)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    pi2s_adapter->user_cb.rx_ccb = handler;
    pi2s_adapter->user_cb.rx_cbid = id;
}

void i2s_set_direction(i2s_t *obj, int trx_type)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_set_direction(pi2s_adapter, (uint8_t)trx_type);
}

void i2s_set_param(i2s_t *obj, int channel_num, int rate, int word_len)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

	hal_i2s_set_ch_num(pi2s_adapter, (uint8_t)channel_num);
    hal_i2s_set_rate(pi2s_adapter, (uint8_t)rate);
    hal_i2s_set_word_len(pi2s_adapter, (uint8_t)word_len);
}

void i2s_deinit(i2s_t *obj)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_deinit(pi2s_adapter);
}

int *i2s_get_tx_page(i2s_t *obj)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;
    u8 page_idx;

    page_idx = hal_i2s_get_tx_page(pi2s_adapter);

    if (page_idx <= pi2s_adapter->base_addr->page_size_rate_b.page_num) {
        return ((int *)pi2s_adapter->ptx_page_list[page_idx]);
    } else {
        DBG_I2S_ERR("Tx_page is busy: \r\n");
        DBG_I2S_ERR("page_idx: %d, I2SPageNum: %d \r\n", page_idx, pi2s_adapter->base_addr->page_size_rate_b.page_num);
        return NULL;
    }
}

void i2s_send_page(i2s_t *obj, u32 *pbuf)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;
    u32 page_num, i;

    page_num = pi2s_adapter->base_addr->page_size_rate_b.page_num + 1;
    for (i=0;i<page_num;i++) {

        if (pi2s_adapter->ptx_page_list[i] == pbuf) {
            hal_i2s_page_send(pi2s_adapter, i);
            break;  // break the for loop
        }
    }

    if (i == page_num) {
        DBG_I2S_ERR("i2s_send_page: the pbuf(0x%x) is not a DMA buffer\r\n", pbuf);
    }
}

void i2s_recv_page(i2s_t *obj)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_page_recv(pi2s_adapter);
}

void i2s_enable(i2s_t *obj)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_en_ctrl(pi2s_adapter, 1);
}

void i2s_disable(i2s_t *obj)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_en_ctrl(pi2s_adapter, 0);

    hal_i2s_reset(pi2s_adapter);
}

void i2s_set_format(i2s_t *obj, i2s_format format)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_set_format(pi2s_adapter, format);
}

void i2s_set_master(i2s_t *obj, i2s_ms_mode ms_mode)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_set_master(pi2s_adapter, ms_mode);
}

void i2s_set_dma_burst_size(i2s_t *obj, i2s_burst_size burst_size)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_set_lxbus_burst_size(pi2s_adapter, burst_size);
}

void i2s_set_byte_swap(i2s_t *obj, BOOL byte_swap_en)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_set_byte_swap(pi2s_adapter, byte_swap_en);
}

void i2s_set_sck_inv(i2s_t *obj, BOOL sck_inv_en)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_set_sck_inv(pi2s_adapter, sck_inv_en);
}

void i2s_set_ws_swap(i2s_t *obj, i2s_ws_swap ws_swap)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_set_ws_swap(pi2s_adapter, ws_swap);
}

void i2s_set_loopback(i2s_t *obj, BOOL loopback_en)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_set_loopback(pi2s_adapter, loopback_en);
}

void i2s_set_data_start_edge(i2s_t *obj, i2s_edge_sw edge_sw)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_set_data_start_edge(pi2s_adapter, edge_sw);
}

void i2s_set_mute(i2s_t *obj, BOOL mute_en)
{
    hal_i2s_adapter_t *pi2s_adapter = &obj->i2s_adapter;

    hal_i2s_set_mute(pi2s_adapter, mute_en);
}


