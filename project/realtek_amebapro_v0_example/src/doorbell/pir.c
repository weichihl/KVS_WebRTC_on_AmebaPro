/*
 *  Routines to access hardware
 *
 *  Copyright (c) 2013 Realtek Semiconductor Corp.
 *
 *  This module is a confidential and proprietary property of RealTek and
 *  possession or use of this module requires written permission of RealTek.
 */
#include "app_setting.h"

#if USE_PIR_SENSOR
#include "device.h"
#include "gpio_api.h"
#include "gpio_irq_api.h"
#include "icc_api.h"

static gpio_t gpio_serin;
static gpio_t gpio_dla;
static gpio_irq_t gpio_irq_dla;
extern int icc_ready;
extern int pir_debounce;
   
void send_icc_cmd_pir(uint32_t pirstaus)
{
	dbg_printf("send_icc_cmd_pir\r\n");    
	icc_user_cmd_t cmd;
	cmd.cmd_b.cmd = ICC_CMD_PIR;
	cmd.cmd_b.para0 = 0;
	icc_cmd_send(cmd.cmd_w, pirstaus, 2000000, NULL);
}
 
void writeregval(uint32_t regval) {
    int i;
    uint8_t nextbit;
    uint32_t regmask = 0x1000000;

    dbg_printf("reg:%08X\r\n", regval);

    uint32_t serin_bit_mask = gpio_serin.adapter.bit_mask;
    uint32_t volatile *serin_out1_port = gpio_serin.adapter.out1_port;
    uint32_t volatile *serin_out0_port = gpio_serin.adapter.out0_port;

    for (i=0; i<25; i++) {
        nextbit = (regval & regmask) != 0;
        regmask >>= 1;
        *serin_out0_port = serin_bit_mask;
        *serin_out1_port = serin_bit_mask;
        if (nextbit) {
            *serin_out1_port = serin_bit_mask;
        } else {
            *serin_out0_port = serin_bit_mask;
        }
        hal_delay_us(100);
    }
    *serin_out0_port = serin_bit_mask;
    hal_delay_us(600);
}

void digipyro_set(uint8_t threshold, uint8_t blind_time, uint8_t pulse_counter, uint8_t window_time, uint8_t operation_mode, uint8_t filter_source)
{
    uint32_t val = ( (threshold      & 0xFF) << 17 ) |
                   ( (blind_time     & 0x0F) << 13 ) |
                   ( (pulse_counter  & 0x03) << 11 ) |
                   ( (window_time    & 0x03) <<  9 ) |
                   ( (operation_mode & 0x03) <<  7 ) |
                   ( (filter_source  & 0x03) <<  5 ) |
                   0x10;
    writeregval(val);
}

void readlowpowerpyro(void) {
    int i;
    uint32_t uibitmask;
    uint32_t ulbitmask;

    int PIRval = 0;
    uint32_t statcfg = 0;

    uint8_t dla_port_idx = gpio_dla.adapter.port_idx;
    uint8_t dla_pin_idx  = gpio_dla.adapter.pin_idx;
    uint32_t dla_bit_mask = gpio_dla.adapter.bit_mask;
    uint32_t volatile *dla_out1_port = gpio_dla.adapter.out1_port;
    uint32_t volatile *dla_out0_port = gpio_dla.adapter.out0_port;
    uint32_t volatile *dla_in_port = gpio_dla.adapter.in_port;

    uint32_t volatile *port_dir_en_in  = (uint32_t *)(0xA0001204 + 0x40 * dla_port_idx);
    uint32_t volatile *port_dir_en_out = (uint32_t *)(0xA0001208 + 0x40 * dla_port_idx);

    *dla_out1_port = dla_bit_mask;
    *port_dir_en_out = dla_bit_mask;
    hal_delay_us(150);

    // get first 15bit out-off-range and ADC value
    uibitmask = 0x4000;
    for (i=0; i<15; i++) {
        *dla_out0_port = dla_bit_mask;
        *port_dir_en_out = dla_bit_mask;
        *dla_out1_port = dla_bit_mask;
        *port_dir_en_in = dla_bit_mask;

        if ( (*dla_in_port) & dla_bit_mask ) PIRval |= uibitmask;
        uibitmask >>= 1;
    }

    // get 25bit status and config
    ulbitmask = 0x1000000;
    statcfg = 0;
    for (i=0; i<25; i++) {
        *dla_out0_port = dla_bit_mask;
        *port_dir_en_out = dla_bit_mask;
        *dla_out1_port = dla_bit_mask;
        *port_dir_en_in = dla_bit_mask;

        if ( (*dla_in_port) & dla_bit_mask ) statcfg |= ulbitmask;
        ulbitmask >>= 1;
    }

    *port_dir_en_out = dla_bit_mask;
    *dla_out0_port = dla_bit_mask;
    asm("nop");
    *port_dir_en_in = dla_bit_mask;

    PIRval &= 0x3FFF;
    if ( !(statcfg & 0x60) ) {
        if (PIRval & 0x2000) {
            PIRval -= 0x4000;
        }
    }

    //dbg_printf("pir:%d stat:%08X\r\n", PIRval, statcfg);
}

void gpio_irq_dla_handler (uint32_t id, gpio_irq_event event)
{
    gpio_irq_disable(&gpio_irq_dla);
    readlowpowerpyro();
    if(icc_ready && pir_debounce > 30)
    {     
    	send_icc_cmd_pir(1);
        pir_debounce = 0;
    }
    gpio_irq_enable(&gpio_irq_dla);
}

void pir_start(void)
{
    gpio_init(&gpio_serin, GPIO_SERIN);
    gpio_dir(&gpio_serin, PIN_OUTPUT);    // Direction: Output
    gpio_mode(&gpio_serin, PullDown);     // No pull
    gpio_write(&gpio_serin, 0);
    
    gpio_irq_init(&gpio_irq_dla, GPIO_DLA, gpio_irq_dla_handler, NULL);
    gpio_irq_set(&gpio_irq_dla, IRQ_RISE, 1);   // Falling Edge Trigger
    gpio_irq_enable(&gpio_irq_dla);
    //gpio_irq_debounce_set(&gpio_irq_dla,1000*512,1);

    //gpio_init(&gpio_dla, GPIO_DLA);
    hal_gpio_init(&(gpio_dla.adapter), GPIO_DLA);
    gpio_dir(&gpio_dla, PIN_INPUT);    // Direction: Output
    gpio_mode(&gpio_dla, PullDown);     // No pull

    digipyro_set(30, 5, 0, 0, 2, 1);
    readlowpowerpyro();
    
}

void pir_stop(void)
{
    gpio_deinit(&gpio_dla);
    gpio_irq_free(&gpio_irq_dla);
    gpio_deinit(&gpio_serin);
}
#endif
