
/**************************************************************************//**
 * @file     qdec_api.c
 * @brief    This file implements the QDEC Mbed HAL API functions.
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
#include "qdec_api.h"
#include "hal_qdec.h"
#include "hal.h"

static const qdec_def_setting_t qdec_def_setting = {
    .smp_div = 0,
    .resolution = ONE_PHASE_COUNT,
    .pc_maximum = 0,
    .rotation_mode = PC_OVER_UNDER_FLOW,
    .filter_enable = DISABLE,
    .filter_time = 0,
    .index_enable = DISABLE,
    .index_level = INPUT_INIT_LOW,
    .index_rst = INDEX_NO_RST
};

extern void hal_syson_sel_qdec_sclk(u8 sclk_sel);

void qdec_init (qdec_t *obj, PinName pha, PinName phb, PinName idx, qdec_clk_source source_clk)
{

    hal_qdec_adapter_t *pqdec_adapter = &obj->qdec_adapter;
    qdec_pin_sel_t qdec_pin_sel = Qdec_PinSel_Max;
    qdec_app_pin_sel_t app_pin_sel = Qdec_Pin_Pha_Phb_Idx;
    u16 pin_combin_tp;
    s32 pin_combin[2] = {(PA_1 << 8) | PA_0, (PA_7 << 8) | PA_13};
    u32 i;

    pin_combin_tp = (u16)((phb << 8) | pha);

    if (pin_combin_tp == (u16)pin_combin[0]) {
        qdec_pin_sel = Qdec_PinSel_0;
        if (idx != PA_2) {
            app_pin_sel = Qdec_Pin_Pha_Phb;
        }
    } else if (pin_combin_tp == (u16)pin_combin[1]) {
        qdec_pin_sel = Qdec_PinSel_1;
        if (idx != PA_8) {
            app_pin_sel = Qdec_Pin_Pha_Phb;
        }
    } else {
        DBG_QDEC_ERR("qdec_init, did not meet the pin group of qdec \r\n");
    }

    if (qdec_pin_sel != Qdec_PinSel_Max) {
        DBG_QDEC_INFO("qdec_init, qdec_pin_sel: %d, app_pin_sel: %d \r\n", qdec_pin_sel, app_pin_sel);
        hal_qdec_init (pqdec_adapter, source_clk, qdec_pin_sel, app_pin_sel);

        qdec_set_filter_init(obj, ENABLE, 0);
        qdec_set_en(obj, ENABLE);
        for (i = 0; i < 10 ; i++) {
            __NOP();
        }            
        qdec_set_filter_init(obj, DISABLE, 0);
        qdec_set_en(obj, DISABLE);
            
        pqdec_adapter->qdec_init_para.smp_div = qdec_def_setting.smp_div;
        pqdec_adapter->qdec_init_para.resolution = qdec_def_setting.resolution;
        pqdec_adapter->qdec_init_para.pc_maximum = qdec_def_setting.pc_maximum;
        pqdec_adapter->qdec_init_para.rotation_mode = qdec_def_setting.rotation_mode;
        pqdec_adapter->qdec_init_para.filter_enable = qdec_def_setting.filter_enable;
        pqdec_adapter->qdec_init_para.filter_time = qdec_def_setting.filter_time;
        pqdec_adapter->qdec_init_para.index_enable = qdec_def_setting.index_enable;
        pqdec_adapter->qdec_init_para.index_level = qdec_def_setting.index_level;
        pqdec_adapter->qdec_init_para.index_rst = qdec_def_setting.index_rst;
        hal_qdec_set_parameter (pqdec_adapter, &pqdec_adapter->qdec_init_para);
    }

}

void qdec_deinit (qdec_t *obj)
{
    hal_qdec_adapter_t *pqdec_adp = &obj->qdec_adapter;

    hal_qdec_deinit(pqdec_adp);
}

void qdec_set_sampling_div (qdec_t *obj, u8 smp_div)
{
    hal_qdec_adapter_t *pqdec_adp = &obj->qdec_adapter;
    pqdec_adp->qdec_init_para.smp_div = smp_div;
    hal_qdec_set_parameter (pqdec_adp, &pqdec_adp->qdec_init_para);
}

void qdec_set_resolution (qdec_t *obj, qdec_resolution resolution)
{
    hal_qdec_adapter_t *pqdec_adp = &obj->qdec_adapter;

    pqdec_adp->qdec_init_para.resolution = resolution;
    hal_qdec_set_parameter (pqdec_adp, &pqdec_adp->qdec_init_para);
}

void qdec_set_pc_maximum (qdec_t *obj, u16 pc_maximum)
{
    hal_qdec_adapter_t *pqdec_adp = &obj->qdec_adapter;

    pqdec_adp->qdec_init_para.pc_maximum = pc_maximum;
    hal_qdec_set_parameter (pqdec_adp, &pqdec_adp->qdec_init_para);
}

void qdec_set_rotation_mode (qdec_t *obj, qdec_rotation_source rotation_mode)
{
    hal_qdec_adapter_t *pqdec_adp = &obj->qdec_adapter;

    pqdec_adp->qdec_init_para.rotation_mode = rotation_mode;
    hal_qdec_set_parameter (pqdec_adp, &pqdec_adp->qdec_init_para);
}

void qdec_set_filter_init (qdec_t *obj, BOOL filter_enable, u16 filter_time)
{
    hal_qdec_adapter_t *pqdec_adp = &obj->qdec_adapter;

    pqdec_adp->qdec_init_para.filter_enable = filter_enable;
    pqdec_adp->qdec_init_para.filter_time = filter_time;
    hal_qdec_set_parameter (pqdec_adp, &pqdec_adp->qdec_init_para);
}

void qdec_set_index_init (qdec_t *obj, BOOL index_enable, qdec_index_level index_level, qdec_index_rst index_rst)
{
    hal_qdec_adapter_t *pqdec_adp = &obj->qdec_adapter;

    pqdec_adp->qdec_init_para.index_enable = index_enable;
    pqdec_adp->qdec_init_para.index_level = index_level;
    pqdec_adp->qdec_init_para.index_rst = index_rst;
    hal_qdec_set_parameter (pqdec_adp, &pqdec_adp->qdec_init_para);
}

void qdec_set_en (qdec_t *obj, BOOL qdec_en_ctrl)
{
    hal_qdec_set_en (&obj->qdec_adapter, qdec_en_ctrl);
    hal_delay_us(150);
}

void qdec_set_position_direction_change_init (qdec_t *obj, BOOL en, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_position_direction_change_init (&obj->qdec_adapter, &qdec_set_irq);
}

void qdec_set_position_count_change_init (qdec_t *obj, BOOL en, qdec_cnt_chg count_change_value, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_position_count_change_init (&obj->qdec_adapter, count_change_value, &qdec_set_irq);
}

void qdec_set_position_compare_init (qdec_t *obj, BOOL en, u16 compare_value, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_position_compare_init (&obj->qdec_adapter, compare_value, &qdec_set_irq);
}

void qdec_set_position_overflow_init (qdec_t *obj, BOOL en, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_position_overflow_init (&obj->qdec_adapter, &qdec_set_irq);
}

void qdec_set_position_underflow_init (qdec_t *obj, BOOL en, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_position_underflow_init (&obj->qdec_adapter, &qdec_set_irq);
}

void qdec_set_rotation_compare_init (qdec_t *obj, BOOL en, u16 compare_value, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_rotation_compare_init (&obj->qdec_adapter, compare_value, &qdec_set_irq);
}

void qdec_set_rotation_overflow_init (qdec_t *obj, BOOL en, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_rotation_overflow_init (&obj->qdec_adapter, &qdec_set_irq);
}

void qdec_set_rotation_underflow_init (qdec_t *obj, BOOL en, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_rotation_underflow_init (&obj->qdec_adapter, &qdec_set_irq);
}

void qdec_set_velocity_measure_cnt_init (qdec_t *obj, BOOL en, qdec_vmuc_mode vmuc_mode, u32 time_us, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_adapter_t *pqdec_adp = &obj->qdec_adapter;
    hal_qdec_set_irq_t qdec_set_irq;
    u32 vt_div = 0;
    u32 time_cnt;

    while (vt_div < 256) {
        hal_qdec_set_velocity_cnt_init (pqdec_adp, vmuc_mode, (u8)vt_div);
        time_cnt = hal_qdec_time_us_to_cnt (pqdec_adp, (float)time_us);
        if ((time_cnt & 0xFFFF0000) == 0x00) {
            break;
        }
        vt_div++;
    }

    if (vt_div > 255) {
        DBG_QDEC_ERR("qdec_set_velocity_measure_cnt_init, Need to add vt_div to avoid that the counter is overflow  \r\n");
    } else {
        DBG_QDEC_INFO("qdec_set_velocity_measure_cnt_init, vt_div: %d  \r\n", vt_div);
        DBG_QDEC_INFO("qdec_set_velocity_measure_cnt_init, time_cnt: %d  \r\n", time_cnt);

        hal_qdec_set_velocity_cnt_period (pqdec_adp, (u16)time_cnt);
        qdec_set_irq.int_en = 1;
        qdec_set_irq.imr_en = 0;
        qdec_set_irq.callback_reg_en = en;
        qdec_set_irq.callback = qdec_cb;
        qdec_set_irq.arg = pqdec_arg;
        hal_qdec_set_velocity_cnt_interrupt (pqdec_adp, &qdec_set_irq);
    }

}

void qdec_set_velocity_measure_cnt_lowlmt_init (qdec_t *obj, BOOL en, u16 low_limit_cnt, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_velocity_cnt_lowlmt_init (&obj->qdec_adapter, low_limit_cnt, &qdec_set_irq);
}

void qdec_set_velocity_measure_cnt_uplmt_init (qdec_t *obj, BOOL en, u16 up_limit_cnt, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_velocity_cnt_uplmt_init (&obj->qdec_adapter, up_limit_cnt, &qdec_set_irq);
}

void qdec_set_index_present_init (qdec_t *obj, BOOL en, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_index_present_init (&obj->qdec_adapter, &qdec_set_irq);
}

void qdec_set_index_check_position_init (qdec_t *obj, BOOL en, qdec_irq_handler qdec_cb, void *pqdec_arg)
{
    hal_qdec_set_irq_t qdec_set_irq;

    qdec_set_irq.int_en = 1;
    qdec_set_irq.imr_en = 0;
    qdec_set_irq.callback_reg_en = en;
    qdec_set_irq.callback = qdec_cb;
    qdec_set_irq.arg = pqdec_arg;
    hal_qdec_set_index_check_init (&obj->qdec_adapter, &qdec_set_irq);
}

void qdec_position_reset (qdec_t *obj)
{
    hal_qdec_position_reset (&obj->qdec_adapter);
}

void qdec_rotation_reset (qdec_t *obj)
{
    hal_qdec_rotation_reset (&obj->qdec_adapter);
}

void qdec_velocity_cnt_reset (qdec_t *obj)
{
    hal_qdec_velocity_cnt_reset (&obj->qdec_adapter);
}

void qdec_start_velocity_measure_cnt (qdec_t *obj, BOOL en)
{
    hal_qdec_start_velocity_cnt (&obj->qdec_adapter, en);
}

u16 qdec_get_velocity_measure_cnt (qdec_t *obj)
{
    return hal_qdec_get_velocity_cnt (&obj->qdec_adapter);
}

float qdec_get_velocity_measure_cnt_rpm (qdec_t *obj, u16 velocity_cnt)
{
    hal_qdec_adapter_t *pqdec_adp = &obj->qdec_adapter;
    u32 hw_pulse_per_rev;

    hw_pulse_per_rev = (u32)(pqdec_adp->qdec_init_para.pc_maximum + 1);

    if (pqdec_adp->qdec_init_para.resolution == ONE_PHASE_COUNT) {
        hw_pulse_per_rev = hw_pulse_per_rev >> 2;
    } else {
        hw_pulse_per_rev = hw_pulse_per_rev >> 1;
    }

    return hal_qdec_get_velocity_cnt_rpm (pqdec_adp, hw_pulse_per_rev, velocity_cnt);
}

u16 qdec_get_position (qdec_t *obj)
{
    return hal_qdec_get_pc (&obj->qdec_adapter);
}

u16 qdec_get_rotation (qdec_t *obj)
{
    return hal_qdec_get_rc (&obj->qdec_adapter);
}

u8 qdec_get_direction (qdec_t *obj)
{
    return hal_qdec_get_direction (&obj->qdec_adapter);
}

u8 qdec_get_phase_state (qdec_t *obj)
{
    return hal_qdec_get_phase_state (&obj->qdec_adapter);
}

