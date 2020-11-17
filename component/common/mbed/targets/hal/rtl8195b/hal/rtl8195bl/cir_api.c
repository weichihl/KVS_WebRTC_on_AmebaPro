
/**************************************************************************//**
 * @file     cir_api.c
 * @brief    This file implements the CIR Mbed HAL API functions.
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
#include "cir_api.h"
#include "hal_cir.h"

void cir_init (cir_t *obj, PinName tx, PinName rx)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    cir_pin_sel_t cir_pin_sel = Cir_PinSel_Max;
    cir_app_pin_sel_t app_pin_sel = Cir_Pin_TRx;
    u16 pin_combin_tp;
    s32 pin_combin[2] = {(PA_7 << 8) | PA_8, (PA_3 << 8) | PA_2};

    pin_combin_tp = (u16)((rx << 8) | tx);

    if (pin_combin_tp == (u16)pin_combin[0]) {
        cir_pin_sel = Cir_PinSel_0;
    } else if (pin_combin_tp == (u16)pin_combin[1]) {
        cir_pin_sel = Cir_PinSel_1;
    } else if ((tx == PA_8) || (tx == PA_2)) {
        app_pin_sel = Cir_Pin_Tx;
        if (tx == PA_8) {
            cir_pin_sel = Cir_PinSel_0;
        } else {
            cir_pin_sel = Cir_PinSel_1;
        }
    } else if ((rx == PA_7) || (rx == PA_3)) {
        app_pin_sel = Cir_Pin_Rx;
        if (tx == PA_7) {
            cir_pin_sel = Cir_PinSel_0;
        } else {
            cir_pin_sel = Cir_PinSel_1;
        }
    }

    if (cir_pin_sel == Cir_PinSel_Max) {
        DBG_CIR_ERR("cir_init, did not meet the pin group of cir \r\n");

    } else {
        DBG_CIR_INFO("cir_init, cir_pin_sel: %d\r\n", cir_pin_sel);
        DBG_CIR_INFO("cir_init, app_pin_sel: %d\r\n", app_pin_sel);
        hal_cir_init (pcir_adapter, cir_pin_sel, app_pin_sel);
    }

}

void cir_deinit (cir_t *obj)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    hal_cir_deinit(pcir_adapter);
}

void cir_set_tx_protocol (cir_t *obj, cir_protocol protocol, cir_init_value output_init, cir_carrier carrier, cir_sclkdiv tx_sclkdiv,
                            cir_irq_handler irq_tx_end_cb, void *irq_tx_end_arg)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_tx_protocol_setting_t tx_protocol_setting;

    tx_protocol_setting.output_init = output_init;
    tx_protocol_setting.carrier = carrier;
    tx_protocol_setting.tx_sclkdiv = tx_sclkdiv;
    tx_protocol_setting.irq_tx_end_cb = irq_tx_end_cb;
    tx_protocol_setting.irq_tx_end_arg = irq_tx_end_arg;

    switch (protocol) {

        case NEC:
            hal_cir_set_nec_tx_protocol(pcir_adapter, &tx_protocol_setting);
            break;

        case SONY:
            hal_cir_set_sony_sirc_tx_protocol(pcir_adapter, &tx_protocol_setting);
            break;

        case PHILIPS:
            hal_cir_set_philips_rc5_tx_protocol(pcir_adapter, &tx_protocol_setting);
            break;

        case JVC:
            hal_cir_set_jvc_tx_protocol(pcir_adapter, &tx_protocol_setting);
            break;

        default:

            break;
    }

}

void cir_set_rx_protocol (cir_t *obj, cir_protocol protocol, cir_init_value input_init, cir_carrier carrier, cir_sclkdiv rx_sclkdiv,
                            u16 symbol_time_tolerance_us, u16 carrier_tolerance_cnt, u16 check_frame_end_time_us,
                            cir_irq_handler irq_rx_end_cb, void *irq_rx_end_arg)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_rx_protocol_desc_t rx_protocol_desc;

    rx_protocol_desc.input_init = input_init;
    rx_protocol_desc.carrier = carrier;
    rx_protocol_desc.rx_sclkdiv = rx_sclkdiv;
    rx_protocol_desc.symbol_time_tolerance_us = symbol_time_tolerance_us;
    rx_protocol_desc.carrier_tolerance_cnt = carrier_tolerance_cnt;
    rx_protocol_desc.check_frame_end_time_us = check_frame_end_time_us;
    rx_protocol_desc.irq_rx_end_cb = irq_rx_end_cb;
    rx_protocol_desc.irq_rx_end_arg = irq_rx_end_arg;

    switch (protocol) {

        case NEC:
            hal_cir_set_nec_rx_protocol(pcir_adapter, &rx_protocol_desc);
            break;

        case SONY:
            hal_cir_set_sony_sirc_rx_protocol(pcir_adapter, &rx_protocol_desc);
            break;

        case PHILIPS:
            hal_cir_set_philips_rc5_rx_protocol(pcir_adapter, &rx_protocol_desc);
            break;

        case JVC:
            hal_cir_set_jvc_rx_protocol(pcir_adapter, &rx_protocol_desc);
            break;

        default:

            break;
    }

}

void cir_nec_recv_normal_format (cir_t *obj, u32 *data)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    obj->pcir_rx_pointer = data;

    hal_cir_protocol_recv (pcir_adapter, data, NEC_Rx_Normal, 1);
}

void cir_nec_recv_extend_format (cir_t *obj, u32 *data)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    obj->pcir_rx_pointer = data;

    hal_cir_protocol_recv (pcir_adapter, data, NEC_Rx_Extend, 1);
}

void cir_nec_send_normal_format (cir_t *obj, u8 address, u8 command)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_nec_normal_format_t nec_normal_format;

    nec_normal_format.b.address = address;
    nec_normal_format.b.command = command;
    hal_cir_nec_send (pcir_adapter, &nec_normal_format, NEC_Tx_Normal);
}

void cir_nec_send_extend_format (cir_t *obj, u8 address_l, u8 address_h, u8 command)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_nec_extend_format_t nec_extend_format;

    nec_extend_format.b.address_l = address_l;
    nec_extend_format.b.address_h = address_h;
    nec_extend_format.b.command = command;
    hal_cir_nec_send (pcir_adapter, &nec_extend_format, NEC_Tx_Extend);
}

void cir_nec_send_repeat_format (cir_t *obj)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    hal_cir_nec_send (pcir_adapter, NULL, NEC_Tx_Repeat);
}

void cir_monitor_nec_normal_format (cir_t *obj, u8 address, u8 command, cir_irq_handler irq_monitor_cb, void *irq_monitor_arg)
{
    u32 monitor_data = 0x00;

    monitor_data = address;
    monitor_data |= ((~address) << 8) & 0x0ff00;
    monitor_data |= (command << 16) & 0x0ff0000;
    monitor_data |= ((~command) << 24) & 0xff000000;

    cir_recv_monitor_mode(obj, 1, monitor_data, 32, irq_monitor_cb, irq_monitor_arg);
}

void cir_monitor_nec_extend_format (cir_t *obj, u8 address_l, u8 address_h, u8 command, cir_irq_handler irq_monitor_cb, void *irq_monitor_arg)
{
    u32 monitor_data = 0x00;

    monitor_data = address_l;
    monitor_data |= (address_h << 8) & 0x0ff00;
    monitor_data |= (command << 16) & 0x0ff0000;
    monitor_data |= ((~command) << 24) & 0xff000000;

    cir_recv_monitor_mode(obj, 1, monitor_data, 32, irq_monitor_cb, irq_monitor_arg);
}

u8 cir_nec_get_normal_address (cir_t *obj)
{
    recv_nec_normal_format_t recv_nec_normal_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_nec_normal_format.w = *prx_pointer;
    temp = (u8)recv_nec_normal_format.b.address;

    return temp ;
}

u8 cir_nec_get_normal_command (cir_t *obj)
{
    recv_nec_normal_format_t recv_nec_normal_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_nec_normal_format.w = *prx_pointer;
    temp = (u8)recv_nec_normal_format.b.command;

    return temp;
}

u8 cir_nec_get_extend_address_low (cir_t *obj)
{
    recv_nec_extend_format_t recv_nec_extend_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_nec_extend_format.w = *prx_pointer;
    temp = (u8)recv_nec_extend_format.b.address_l;

    return temp;
}

u8 cir_nec_get_extend_address_high (cir_t *obj)
{
    recv_nec_extend_format_t recv_nec_extend_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_nec_extend_format.w = *prx_pointer;
    temp = (u8)recv_nec_extend_format.b.address_h;

    return temp;
}

u8 cir_nec_get_extend_command (cir_t *obj)
{
    recv_nec_extend_format_t recv_nec_extend_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_nec_extend_format.w = *prx_pointer;
    temp = (u8)recv_nec_extend_format.b.command;

    return temp;
}

void cir_sony_recv_12bit_format (cir_t *obj, u32 *data)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    obj->pcir_rx_pointer = data;

    hal_cir_protocol_recv (pcir_adapter, data, SONY_SIRC_12BITS, 1);
}

void cir_sony_recv_15bit_format (cir_t *obj, u32 *data)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    obj->pcir_rx_pointer = data;

    hal_cir_protocol_recv (pcir_adapter, data, SONY_SIRC_15BITS, 1);
}

void cir_sony_recv_20bit_format (cir_t *obj, u32 *data)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    obj->pcir_rx_pointer = data;

    hal_cir_protocol_recv (pcir_adapter, data, SONY_SIRC_20BITS, 1);
}

void cir_sony_send_12bit_format (cir_t *obj, u8 address_5bits, u8 command_7bits)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_sony_src_12bits_t sony_src_12bits;

    sony_src_12bits.b.address = address_5bits;
    sony_src_12bits.b.command = command_7bits;
    hal_cir_sony_sirc_send (pcir_adapter, &sony_src_12bits, SONY_SIRC_12BITS);
}

void cir_sony_send_15bit_format (cir_t *obj, u8 address_8bits, u8 command_7bits)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_sony_src_15bits_t sony_src_15bits;

    sony_src_15bits.b.address = address_8bits;
    sony_src_15bits.b.command = command_7bits;
    hal_cir_sony_sirc_send (pcir_adapter, &sony_src_15bits, SONY_SIRC_15BITS);
}

void cir_sony_send_20bit_format (cir_t *obj, u8 address_5bits, u8 command_7bits, u8 extend_8bits)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_sony_src_20bits_t sony_src_20bits;

    sony_src_20bits.b.address = address_5bits;
    sony_src_20bits.b.command = command_7bits;
    sony_src_20bits.b.extend = extend_8bits;
    hal_cir_sony_sirc_send (pcir_adapter, &sony_src_20bits, SONY_SIRC_20BITS);
}

void cir_monitor_sony_12bit_format (cir_t *obj, u8 address_5bits, u8 command_7bits, cir_irq_handler irq_monitor_cb, void *irq_monitor_arg)
{
    u32 monitor_data = 0x00;

    monitor_data = command_7bits & 0x7f;
    monitor_data |= (address_5bits & 0x1f) << 7;

    cir_recv_monitor_mode(obj, 1, monitor_data, 12, irq_monitor_cb, irq_monitor_arg);
}

void cir_monitor_sony_15bit_format (cir_t *obj, u8 address_8bits, u8 command_7bits, cir_irq_handler irq_monitor_cb, void *irq_monitor_arg)
{
    u32 monitor_data = 0x00;

    monitor_data = command_7bits & 0x7f;
    monitor_data |= address_8bits << 7;

    cir_recv_monitor_mode(obj, 1, monitor_data, 15, irq_monitor_cb, irq_monitor_arg);
}

void cir_monitor_sony_20bit_format (cir_t *obj, u8 address_5bits, u8 command_7bits, u8 extend_8bits, cir_irq_handler irq_monitor_cb, void *irq_monitor_arg)
{
    u32 monitor_data = 0x00;

    monitor_data = command_7bits & 0x7f;
    monitor_data |= (address_5bits & 0x1f) << 7;
    monitor_data |= extend_8bits << 12;

    cir_recv_monitor_mode(obj, 1, monitor_data, 20, irq_monitor_cb, irq_monitor_arg);
}

u8 cir_sony_get_12bit_format_address (cir_t *obj)
{
    recv_sony_src_12bits_t recv_sony_src_12bits;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_sony_src_12bits.w = *prx_pointer;
    temp = (u8)recv_sony_src_12bits.b.address;

    return temp;
}

u8 cir_sony_get_12bit_format_command (cir_t *obj)
{
    recv_sony_src_12bits_t recv_sony_src_12bits;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_sony_src_12bits.w = *prx_pointer;
    temp = (u8)recv_sony_src_12bits.b.command;

    return temp;
}

u8 cir_sony_get_15bit_format_address (cir_t *obj)
{
    recv_sony_src_15bits_t recv_sony_src_15bits;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_sony_src_15bits.w = *prx_pointer;
    temp = (u8)recv_sony_src_15bits.b.address;

    return temp;
}

u8 cir_sony_get_15bit_format_command (cir_t *obj)
{
    recv_sony_src_15bits_t recv_sony_src_15bits;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_sony_src_15bits.w = *prx_pointer;
    temp = (u8)recv_sony_src_15bits.b.command;

    return temp;
}

u8 cir_sony_get_20bit_format_address (cir_t *obj)
{
    recv_sony_src_20bits_t recv_sony_src_20bits;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_sony_src_20bits.w = *prx_pointer;
    temp = (u8)recv_sony_src_20bits.b.address;

    return temp;
}

u8 cir_sony_get_20bit_format_command (cir_t *obj)
{
    recv_sony_src_20bits_t recv_sony_src_20bits;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_sony_src_20bits.w = *prx_pointer;
    temp = (u8)recv_sony_src_20bits.b.command;

    return temp;
}

u8 cir_sony_get_20bit_format_extend (cir_t *obj)
{
    recv_sony_src_20bits_t recv_sony_src_20bits;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_sony_src_20bits.w = *prx_pointer;
    temp = (u8)recv_sony_src_20bits.b.extend;

    return temp;
}

void cir_philips_rc5_recv_format (cir_t *obj, u32 *data)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    obj->pcir_rx_pointer = data;

    hal_cir_protocol_recv (pcir_adapter, data, PHILIPS_RC5, 1);
}

void cir_philips_rc5_send_format (cir_t *obj, u8 field_1bits, u8 toggle_1bits, u8 address_5bits, u8 command_6bits)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_philips_rc5_format_t philips_rc5_format;

    philips_rc5_format.b.field = field_1bits;
    philips_rc5_format.b.toggle = toggle_1bits;
    philips_rc5_format.b.address = address_5bits;
    philips_rc5_format.b.command = command_6bits;
    hal_cir_philips_rc5_send (pcir_adapter, &philips_rc5_format);
}

void cir_monitor_philips_rc5_format (cir_t *obj, u8 field_1bits, u8 toggle_1bits, u8 address_5bits, u8 command_6bits, cir_irq_handler irq_monitor_cb, void *irq_monitor_arg)
{
    u32 monitor_data = 0x00;
    u8 address_5bits_inv;
    u8 command_6bits_inv;

    monitor_data = field_1bits & 0x01;
    monitor_data |= (toggle_1bits & 0x01) << 1;
    address_5bits_inv = hal_cir_data_reverse(address_5bits) >> (32 - 5);
    monitor_data |= (address_5bits_inv & 0x01f) << 2;
    command_6bits_inv = hal_cir_data_reverse(command_6bits) >> (32 - 6);
    monitor_data |= (command_6bits_inv & 0x03f) << 7;

    cir_recv_monitor_mode(obj, 1, monitor_data, 13, irq_monitor_cb, irq_monitor_arg);
}

u8 cir_philips_rc5_get_address (cir_t *obj)
{
    recv_philips_rc5_format_t recv_philips_rc5_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_philips_rc5_format.w = *prx_pointer;
    temp = (u8)recv_philips_rc5_format.b.address;

    return temp;
}

u8 cir_philips_rc5_get_command (cir_t *obj)
{
    recv_philips_rc5_format_t recv_philips_rc5_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_philips_rc5_format.w = *prx_pointer;
    temp = (u8)recv_philips_rc5_format.b.command;

    return temp;
}

u8 cir_philips_rc5_get_format_field (cir_t *obj)
{
    recv_philips_rc5_format_t recv_philips_rc5_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_philips_rc5_format.w = *prx_pointer;
    temp = (u8)recv_philips_rc5_format.b.field;

    return temp;
}

u8 cir_philips_rc5_get_format_toggle (cir_t *obj)
{
    recv_philips_rc5_format_t recv_philips_rc5_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_philips_rc5_format.w = *prx_pointer;
    temp = (u8)recv_philips_rc5_format.b.toggle;

    return temp;
}

void cir_jvc_recv_format (cir_t *obj, u32 *data)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    obj->pcir_rx_pointer = data;

    hal_cir_protocol_recv (pcir_adapter, data, JVC_NORMAL_RX, 1);
}

void cir_jvc_send_normal_format (cir_t *obj, u8 address_8bits,  u8 command_8bits)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_jvc_format_t jvc_send_format;

    jvc_send_format.b.address = address_8bits;
    jvc_send_format.b.command = command_8bits;
    hal_cir_jvc_send (pcir_adapter, &jvc_send_format, JVC_NORMAL_TX);
}

void cir_jvc_send_repeat_header_format (cir_t *obj, u8 address_8bits,  u8 command_8bits)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_jvc_format_t jvc_send_format;

    jvc_send_format.b.address = address_8bits;
    jvc_send_format.b.command = command_8bits;
    hal_cir_jvc_send (pcir_adapter, &jvc_send_format, JVC_REPEAT_HEADER_TX);
}

void cir_jvc_send_repeat_no_header_format (cir_t *obj, u8 address_8bits,  u8 command_8bits)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_jvc_format_t jvc_send_format;

    jvc_send_format.b.address = address_8bits;
    jvc_send_format.b.command = command_8bits;
    hal_cir_jvc_send (pcir_adapter, &jvc_send_format, JVC_REPEAT_NO_HEADER_TX);
}

void cir_monitor_jvc_format (cir_t *obj, u8 address_8bits,  u8 command_8bits, cir_irq_handler irq_monitor_cb, void *irq_monitor_arg)
{
    u32 monitor_data = 0x00;

    monitor_data = address_8bits;
    monitor_data |= command_8bits << 8;

    cir_recv_monitor_mode(obj, 1, monitor_data, 16, irq_monitor_cb, irq_monitor_arg);
}

u8 cir_jvc_get_address (cir_t *obj)
{
    recv_jvc_format_t recv_jvc_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_jvc_format.w = *prx_pointer;
    temp = (u8)recv_jvc_format.b.address;

    return temp;
}

u8 cir_jvc_get_command (cir_t *obj)
{
    recv_jvc_format_t recv_jvc_format;
    u32 *prx_pointer = obj->pcir_rx_pointer;
    u8 temp;

    recv_jvc_format.w = *prx_pointer;
    temp = (u8)recv_jvc_format.b.command;

    return temp;
}

cir_rx_status cir_get_protocol_rx_status (cir_t *obj)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    u8 rx_status;

    rx_status = (u8)hal_cir_get_protocol_rx_status (pcir_adapter);

    return (cir_rx_status)rx_status;
}

void cir_recv_monitor_mode (cir_t *obj, BOOL en, u32 monitor_data,  u32 monitor_cnt, cir_irq_handler monitor_cb, void *pmonitor_arg)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    hal_cir_set_monitor (pcir_adapter, monitor_data, monitor_cnt, en);
    pcir_adapter->monitor_rxprocess_dis = 0;     
    hal_cir_set_monitor_int(pcir_adapter, 1, 0);
    hal_cir_irq_monitor_cb (pcir_adapter, monitor_cb, pmonitor_arg);
}

void cir_make_tx_protocol (cir_t *obj, cir_tx_protocol_t *ptx_protocol, cir_init_value output_init, cir_carrier carrier, cir_sclkdiv tx_sclkdiv,
                            cir_irq_handler irq_tx_end_cb, void *irq_tx_end_arg)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_tx_protocol_setting_t tx_protocol_setting;

    tx_protocol_setting.output_init = output_init;
    tx_protocol_setting.carrier = carrier;
    tx_protocol_setting.tx_sclkdiv = tx_sclkdiv;
    tx_protocol_setting.irq_tx_end_cb = irq_tx_end_cb;
    tx_protocol_setting.irq_tx_end_arg = irq_tx_end_arg;

    hal_cir_set_tx_protocol (pcir_adapter, &tx_protocol_setting, (hal_cir_tx_protocol_t *)ptx_protocol);
}

void cir_change_tx_start_symbol (cir_t *obj, cir_symbol_t first_symbol, cir_symbol_t second_symbol)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    pcir_adapter->tx_protocol_frame.tx_start_sym[0] = first_symbol;
    pcir_adapter->tx_protocol_frame.tx_start_sym[1] = second_symbol;
}

void cir_change_tx_bit0_symbol (cir_t *obj, cir_symbol_t first_symbol, cir_symbol_t second_symbol)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    pcir_adapter->tx_protocol_frame.tx_bit0_sym[0] = first_symbol;
    pcir_adapter->tx_protocol_frame.tx_bit0_sym[1] = second_symbol;
}

void cir_change_tx_bit1_symbol (cir_t *obj, cir_symbol_t first_symbol, cir_symbol_t second_symbol)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    pcir_adapter->tx_protocol_frame.tx_bit1_sym[0] = first_symbol;
    pcir_adapter->tx_protocol_frame.tx_bit1_sym[1] = second_symbol;
}

void cir_change_tx_end_symbol (cir_t *obj, cir_symbol_t first_symbol, cir_symbol_t second_symbol)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    pcir_adapter->tx_protocol_frame.tx_end_sym[0] = first_symbol;
    pcir_adapter->tx_protocol_frame.tx_end_sym[1] = second_symbol;
}

void cir_send_make_protocol (cir_t *obj, u32 *data, u32 length)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    hal_cir_send_protocol(pcir_adapter, data, length);
}

void cir_make_rx_protocol (cir_t *obj, cir_rx_protocol_t *prx_protocol, cir_init_value input_init, cir_carrier carrier, cir_sclkdiv rx_sclkdiv,
                            u16 symbol_time_tolerance_us, u16 carrier_tolerance_cnt, u16 check_frame_end_time_us,
                            cir_irq_handler irq_rx_end_cb, void *irq_rx_end_arg)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    hal_cir_rx_protocol_desc_t rx_protocol_desc;

    rx_protocol_desc.input_init = input_init;
    rx_protocol_desc.carrier = carrier;
    rx_protocol_desc.rx_sclkdiv = rx_sclkdiv;
    rx_protocol_desc.symbol_time_tolerance_us = symbol_time_tolerance_us;
    rx_protocol_desc.carrier_tolerance_cnt = carrier_tolerance_cnt;
    rx_protocol_desc.check_frame_end_time_us = check_frame_end_time_us;
    rx_protocol_desc.irq_rx_end_cb = irq_rx_end_cb;
    rx_protocol_desc.irq_rx_end_arg = irq_rx_end_arg;

    hal_cir_irq_recv_cb(pcir_adapter, (cir_irq_user_cb_t)irq_rx_end_cb, irq_rx_end_arg);
    hal_cir_set_rx_protocol(pcir_adapter, &rx_protocol_desc, (hal_cir_rx_protocol_t *)prx_protocol);
}

void cir_recv_make_protocol (cir_t *obj, u32 *data, u32 data_32bits_num)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;

    obj->pcir_rx_pointer = data;

    hal_cir_protocol_recv (pcir_adapter, data, 0x00, data_32bits_num);
}

u32 cir_recv_bit_length (cir_t *obj)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    u32 temp;

    temp = hal_cir_recv_bit_length(pcir_adapter);
    return temp;
}

BOOL cir_get_start_match_gp0_status (cir_t *obj)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    u8 temp;

    temp = hal_cir_get_start_match_gp0_status(pcir_adapter);
    return temp;
}

BOOL cir_get_start_match_gp1_status (cir_t *obj)
{
    hal_cir_adapter_t *pcir_adapter = &obj->cir_adapter;
    u8 temp;

    temp = hal_cir_get_start_match_gp1_status(pcir_adapter);
    return temp;
}

void cir_reset (void)
{
    hal_cir_reset();
}

