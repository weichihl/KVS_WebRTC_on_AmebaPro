/**************************************************************************//**
 * @file     spi_api.c
 * @brief    This file implements the DMA Mbed HAL API functions.
 * 
 * @version  V1.00
 * @date     2017-05-31
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
#include "cmsis.h"
#include "objects.h"
#include "spi_api.h"
#include "spi_ex_api.h"
#include "PinNames.h"
#include "pinmap.h"
#include "hal_ssi.h"
#include "string.h"

void spi_tx_done_callback(VOID *obj);
void spi_rx_done_callback(VOID *obj);
void spi_bus_tx_done_callback(VOID *obj);

u8 format_is_set[4];

static const PinMap PinMap_SSI_MOSI[] = {
    {PG_8,  RTL_PIN_PERI(PID_SPI0, 0, S0), RTL_PIN_FUNC(PID_SPI0, S0)},
    {PE_14, RTL_PIN_PERI(PID_SPI0, 0, S1), RTL_PIN_FUNC(PID_SPI0, S1)},
    {PE_2,  RTL_PIN_PERI(PID_SPI1, 1, S0), RTL_PIN_FUNC(PID_SPI1, S0)},
    {PG_2,  RTL_PIN_PERI(PID_SPI1, 1, S1), RTL_PIN_FUNC(PID_SPI1, S1)},
    {PB_2,  RTL_PIN_PERI(PID_SPI2, 2, S0), RTL_PIN_FUNC(PID_SPI2, S0)},
    {PC_2,  RTL_PIN_PERI(PID_SPI2, 2, S1), RTL_PIN_FUNC(PID_SPI2, S1)},
    {PE_6,  RTL_PIN_PERI(PID_SPI3, 3, S0), RTL_PIN_FUNC(PID_SPI3, S0)},
    {PH_2,  RTL_PIN_PERI(PID_SPI3, 3, S1), RTL_PIN_FUNC(PID_SPI3, S1)},
    {NC,    NC,     0}
};

static const PinMap PinMap_SSI_MISO[] = {
    {PG_9,  RTL_PIN_PERI(PID_SPI0, 0, S0), RTL_PIN_FUNC(PID_SPI0, S0)},
    {PE_15, RTL_PIN_PERI(PID_SPI0, 0, S1), RTL_PIN_FUNC(PID_SPI0, S1)},
    {PE_3,  RTL_PIN_PERI(PID_SPI1, 1, S0), RTL_PIN_FUNC(PID_SPI1, S0)},
    {PG_3,  RTL_PIN_PERI(PID_SPI1, 1, S1), RTL_PIN_FUNC(PID_SPI1, S1)},
    {PB_3,  RTL_PIN_PERI(PID_SPI2, 2, S0), RTL_PIN_FUNC(PID_SPI2, S0)},
    {PC_3,  RTL_PIN_PERI(PID_SPI2, 2, S1), RTL_PIN_FUNC(PID_SPI2, S1)},
    {PE_7,  RTL_PIN_PERI(PID_SPI3, 3, S0), RTL_PIN_FUNC(PID_SPI3, S0)},
    {PH_3,  RTL_PIN_PERI(PID_SPI3, 3, S1), RTL_PIN_FUNC(PID_SPI3, S1)},
    {NC,    NC,     0}
};


void spi_init (spi_t *obj, PinName mosi, PinName miso, PinName sclk, PinName ssel)
{
    uint32_t ssi_mosi, ssi_miso, ssi_peri;
    uint8_t  ssi_idx, ssi_pinmux;
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    
    memset((void*)obj, 0, sizeof(spi_t));
    obj->state = 0;

    ssi_mosi = pinmap_peripheral(mosi, PinMap_SSI_MOSI);
    ssi_miso = pinmap_peripheral(miso, PinMap_SSI_MISO);
    DBG_SSI_INFO("ssi_mosi: %d, ssi_miso: %d\n", ssi_mosi, ssi_miso);

    ssi_peri = pinmap_merge(ssi_mosi, ssi_miso);
    if (unlikely(ssi_peri == NC)) {
        DBG_SSI_ERR("spi_init(): Cannot find matched SSI index.\n");
        return;
    }
    obj->sclk = (u8)sclk;
    ssi_idx = RTL_GET_PERI_IDX(ssi_peri);
    ssi_pinmux = RTL_GET_PERI_SEL(ssi_peri);
    DBG_SSI_INFO("ssi_peri: %d, ssi_idx: %d, ssi_pinmux: %d\n", ssi_peri, ssi_idx, ssi_pinmux);

    if((hal_ssi_init(phal_ssi_adaptor, ssi_idx, (spi_pin_sel_t) ssi_pinmux)) != HAL_OK){
        DBG_SSI_ERR(ANSI_COLOR_RED"spi_init(): SPI %x init fails.\n"ANSI_COLOR_RESET,ssi_idx);
        return;        
    }

    format_is_set[ssi_idx] = 0;

    phal_ssi_adaptor->tx_done_callback = spi_tx_done_callback;
    phal_ssi_adaptor->tx_done_cb_para = (void*)obj;
    phal_ssi_adaptor->rx_done_callback = spi_rx_done_callback;
    phal_ssi_adaptor->rx_done_cb_para = (void*)obj;
    phal_ssi_adaptor->tx_idle_callback = spi_bus_tx_done_callback;
    phal_ssi_adaptor->tx_idle_cb_para = (void*)obj;

    /*Initialize ISR setting to prevent from inadvert effects*/
    hal_ssi_set_interrupt_mask(phal_ssi_adaptor, 0);

#ifdef CONFIG_GDMA_EN 
    phal_ssi_adaptor->ptx_gdma_adaptor = &obj->spi_gdma_adp_tx;
    phal_ssi_adaptor->prx_gdma_adaptor = &obj->spi_gdma_adp_rx;
    obj->dma_en = 0;
#endif
}

void spi_free (spi_t *obj)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

    hal_ssi_deinit(phal_ssi_adaptor);
    obj->dma_en = 0;
}

/*
 * mode | POL PHA
 * -----+--------
 *   0  |  0   0
 *   1  |  0   1
 *   2  |  1   0
 *   3  |  1   1
 *
 * SCPOL_INACTIVE_IS_LOW  = 0,
 * SCPOL_INACTIVE_IS_HIGH = 1
 *
 * SCPH_TOGGLES_IN_MIDDLE = 0,
 * SCPH_TOGGLES_AT_START  = 1
 */
void spi_format (spi_t *obj, int bits, int mode, int slave)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

    if (slave) {
        hal_ssi_set_device_role(phal_ssi_adaptor, SsiSlave);
    } else {
        hal_ssi_set_device_role(phal_ssi_adaptor, SsiMaster);
    }
    
    hal_spi_format(phal_ssi_adaptor, bits-1, mode);

    if (slave) {
        if (phal_ssi_adaptor->sclk_polarity == ScpolInactiveIsLow) {
            hal_gpio_pull_ctrl((u32)obj->sclk, PullCtrl_PullLow);
        } else {
            hal_gpio_pull_ctrl((u32)obj->sclk, PullCtrl_PullHigh);
        }
    }
    
    format_is_set[phal_ssi_adaptor->index] = 1;
}

void spi_frequency (spi_t *obj, int hz)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

    if (format_is_set[phal_ssi_adaptor->index] == 0) {
        DBG_SSI_ERR("Please initialize SPI format first!\r\n");
    }

    hal_ssi_set_sclk(phal_ssi_adaptor, hz);
}

static inline void ssi_write (spi_t *obj, int value)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

    while (!hal_ssi_writable(phal_ssi_adaptor));
    hal_ssi_write(phal_ssi_adaptor, value);
}

static inline int ssi_read(spi_t *obj)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

    while (!hal_ssi_readable(phal_ssi_adaptor));
    return (int)hal_ssi_read(phal_ssi_adaptor);
}

int spi_master_write (spi_t *obj, int value)
{
    ssi_write(obj, value);
    return ssi_read(obj);
}

int spi_slave_receive (spi_t *obj)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int readable;
    int busy;

    readable = hal_ssi_readable(phal_ssi_adaptor);
    busy = hal_ssi_get_busy(phal_ssi_adaptor);
    return ((readable && !busy) ? 1 : 0);
}

int spi_slave_read (spi_t *obj)
{
    return ssi_read(obj);
}

void spi_slave_write (spi_t *obj, int value)
{
    ssi_write(obj, value);
}

int spi_busy (spi_t *obj)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

    return (int)hal_ssi_get_busy(phal_ssi_adaptor);
}

//Discard data in the rx fifo, SPI bus can observe these data
void spi_flush_rx_fifo (spi_t *obj)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    u32 rx_fifo_level;
    u32 i;
    
    while (hal_ssi_readable(phal_ssi_adaptor)) {
        rx_fifo_level = hal_ssi_get_rxfifo_level(phal_ssi_adaptor);
        for (i = 0; i < rx_fifo_level; i++) {
            hal_ssi_read(phal_ssi_adaptor);
        }
    }
}

//This function is only for the slave device to flush tx fifo
//It will discard all data in both tx fifo and rx fifo, then reset the state of slave tx. 
//Data in the tx & rx fifo will be dropped without being able to be observed from SPI bus
void spi_slave_flush_fifo(spi_t *obj)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    u8 role;

    role = phal_ssi_adaptor->role;
    
    if (role != SsiSlave) {
        DBG_SSI_ERR("The SPI is not a slave\n");
    }
    
    hal_ssi_disable(phal_ssi_adaptor);
    hal_ssi_enable(phal_ssi_adaptor);
    obj->state &= ~SPI_STATE_TX_BUSY;
}

// Bus Idle: Real TX done, TX FIFO empty and bus shift all data out already
void spi_bus_tx_done_callback(VOID *obj)
{
    spi_t *spi_obj = (spi_t *)obj;
    spi_irq_handler handler;

    if (spi_obj->bus_tx_done_handler) {
        handler = (spi_irq_handler)spi_obj->bus_tx_done_handler;
        handler(spi_obj->bus_tx_done_irq_id, 0);
    }    
}

void spi_tx_done_callback(VOID *obj)
{
    spi_t *spi_obj = (spi_t *)obj;
    spi_irq_handler handler;

    if (spi_obj->state & SPI_STATE_TX_BUSY) {
        spi_obj->state &= ~SPI_STATE_TX_BUSY;
        if (spi_obj->irq_handler) {
            handler = (spi_irq_handler)spi_obj->irq_handler;
            handler(spi_obj->irq_id, SpiTxIrq);
        }
    }
}

void spi_rx_done_callback(VOID *obj)
{
    spi_t *spi_obj = (spi_t *)obj;
    spi_irq_handler handler;

    spi_obj->state &= ~SPI_STATE_RX_BUSY;
    if (spi_obj->irq_handler) {
        handler = (spi_irq_handler)spi_obj->irq_handler;
        handler(spi_obj->irq_id, SpiRxIrq);
    }
}

void spi_irq_hook(spi_t *obj, spi_irq_handler handler, uint32_t id) 
{
    obj->irq_handler = (u32)handler;
    obj->irq_id = (u32)id;
}

void spi_bus_tx_done_irq_hook(spi_t *obj, spi_irq_handler handler, uint32_t id) 
{
    obj->bus_tx_done_handler = (u32)handler;
    obj->bus_tx_done_irq_id = (u32)id;
}

void spi_enable(spi_t *obj)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

    hal_ssi_enable(phal_ssi_adaptor);
}

void spi_disable(spi_t *obj)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

    hal_ssi_disable(phal_ssi_adaptor);
}

// Slave mode read a sequence of data by interrupt mode
int32_t spi_slave_read_stream(spi_t *obj, char *rx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int32_t ret;

    if (obj->state & SPI_STATE_RX_BUSY) {
        DBG_SSI_WARN("spi_slave_read_stream: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    DBG_SSI_INFO("rx_buffer addr: %X, length: %d\n", rx_buffer, length);
    obj->state |= SPI_STATE_RX_BUSY;
    
    if ((ret = hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length)) != HAL_OK) {
        obj->state &= ~SPI_STATE_RX_BUSY;
    }

    return ret;
}

// Slave mode write a sequence of data by interrupt mode
int32_t spi_slave_write_stream(spi_t *obj, char *tx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int32_t ret;

    if (obj->state & SPI_STATE_TX_BUSY) {
        DBG_SSI_WARN("spi_slave_write_stream: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    obj->state |= SPI_STATE_TX_BUSY;
    
    if ((ret = hal_ssi_interrupt_init_write(phal_ssi_adaptor, tx_buffer, length)) != HAL_OK) {
        obj->state &= ~SPI_STATE_TX_BUSY;
    }
    
    return ret;
}

// Master mode read a sequence of data by interrupt mode
// The length unit is byte, for both 16-bits and 8-bits mode
int32_t spi_master_read_stream(spi_t *obj, char *rx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int32_t ret;

    if (obj->state & SPI_STATE_RX_BUSY) {
        DBG_SSI_WARN("spi_master_read_stream: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    // wait bus idle
    while(hal_ssi_get_busy(phal_ssi_adaptor));

    obj->state |= SPI_STATE_RX_BUSY;
    if ((ret = hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length)) == HAL_OK) {
        /* as Master mode, it need to push data to TX FIFO to generate clock out 
           then the slave can transmit data out */
        // send some dummy data out
        if ((ret = hal_ssi_interrupt_init_write(phal_ssi_adaptor, NULL, length)) != HAL_OK) {
            obj->state &= ~SPI_STATE_RX_BUSY;
        }
    } else {
        obj->state &= ~SPI_STATE_RX_BUSY;
    }

    return ret;
}

// Master mode write a sequence of data by interrupt mode
// The length unit is byte, for both 16-bits and 8-bits mode
int32_t spi_master_write_stream(spi_t *obj, char *tx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int32_t ret;

    if (obj->state & SPI_STATE_TX_BUSY) {
        DBG_SSI_WARN("spi_master_write_stream: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    obj->state |= SPI_STATE_TX_BUSY;
    
    /* as Master mode, sending data will receive data at sametime, so we need to
       drop those received dummy data */
    if ((ret = hal_ssi_interrupt_init_write(phal_ssi_adaptor, tx_buffer, length)) != HAL_OK) {
        obj->state &= ~SPI_STATE_TX_BUSY;
    }
    
    return ret;
}

// Master mode write a sequence of data by interrupt mode
// The length unit is byte, for both 16-bits and 8-bits mode
int32_t spi_master_write_read_stream(spi_t *obj, char *tx_buffer, 
        char *rx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int32_t ret;

    if (obj->state & (SPI_STATE_RX_BUSY|SPI_STATE_TX_BUSY)) {
        DBG_SSI_WARN("spi_master_write_and_read_stream: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    // wait bus idle
    while(hal_ssi_get_busy(phal_ssi_adaptor));

    obj->state |= SPI_STATE_RX_BUSY;
    /* as Master mode, sending data will receive data at sametime */
    if ((ret = hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length)) == HAL_OK) {
        obj->state |= SPI_STATE_TX_BUSY;
        if ((ret = hal_ssi_interrupt_init_write(phal_ssi_adaptor, tx_buffer, length)) != HAL_OK) {
            obj->state &= ~(SPI_STATE_RX_BUSY|SPI_STATE_TX_BUSY);
        }
    } else {
        obj->state &= ~(SPI_STATE_RX_BUSY);
    }
    
    return ret;
}

int32_t spi_slave_read_stream_timeout(spi_t *obj, char *rx_buffer, uint32_t length, uint32_t timeout_ms)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int ret,timeout = 0;
    u32 start_us;

    if (obj->state & SPI_STATE_RX_BUSY) {
        DBG_SSI_WARN("spi_slave_read_stream: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    obj->state |= SPI_STATE_RX_BUSY;
    
    hal_ssi_enter_critical(phal_ssi_adaptor);
    if ((ret = hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length)) != HAL_OK) {
        obj->state &= ~SPI_STATE_RX_BUSY;
    }
    hal_ssi_exit_critical(phal_ssi_adaptor);
    
    if ((ret == HAL_OK) && (timeout_ms > 0)) {
        start_us = hal_read_cur_time();
        while (obj->state & SPI_STATE_RX_BUSY) {
            if (hal_is_timeout(start_us, timeout_ms*1000)) {
                ret = hal_ssi_stop_recv(phal_ssi_adaptor);
                obj->state &= ~ SPI_STATE_RX_BUSY;
                timeout = 1;
                DBG_SSI_INFO("Slave is timeout\n");
                break;
            }
        }
        
        if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits) {
            phal_ssi_adaptor->rx_length <<= 1;
        }

        if(timeout) {
            return (length - phal_ssi_adaptor->rx_length);
        } else {
            return length;
        }
    } else {
        return (-ret);
    }
}

int32_t spi_slave_read_stream_terminate(spi_t *obj, char *rx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    volatile u8 cs_stop;
    int ret;

    cs_stop = 0;
    if (obj->state & SPI_STATE_RX_BUSY) {
        DBG_SSI_WARN("spi_slave_read_stream_dma: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }    

    obj->state |= SPI_STATE_RX_BUSY;
    hal_ssi_enter_critical(phal_ssi_adaptor);
    if ((ret = hal_ssi_interrupt_init_read(phal_ssi_adaptor, rx_buffer, length)) != HAL_OK) {
        obj->state &= ~SPI_STATE_RX_BUSY;
    }
    hal_ssi_exit_critical(phal_ssi_adaptor);

    while(obj->state & SPI_STATE_RX_BUSY){
        while(hal_ssi_get_busy(phal_ssi_adaptor)){

            /*Transfer is complete*/
            if((obj->state & SPI_STATE_RX_BUSY) == 0){   
                cs_stop = 0;
                break;
            }   

            /*Transfer is not complete, but the SPI de-select the slave to cancel the transfer*/
            if(hal_ssi_get_busy(phal_ssi_adaptor) == 0){
                ret = hal_ssi_stop_recv(phal_ssi_adaptor); 
                goto EndOfCS;
            }
        }
    }
EndOfCS:
    if((obj->state & SPI_STATE_RX_BUSY) != 0){ 
        cs_stop = 1;
        obj->state &= ~ SPI_STATE_RX_BUSY;
    }

    if (phal_ssi_adaptor->data_frame_size == DfsSixteenBits){
        phal_ssi_adaptor->rx_length <<= 1;
    }    
    
    if(cs_stop == 1) {
        return (length - phal_ssi_adaptor->rx_length);
    } else {
        return length;
    }
}

#ifdef CONFIG_GDMA_EN    
int32_t spi_slave_read_stream_dma(spi_t *obj, char *rx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int32_t ret;

    if (obj->state & SPI_STATE_RX_BUSY) {
        DBG_SSI_WARN("spi_slave_read_stream_dma: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    if ((obj->dma_en & SPI_DMA_RX_EN)==0) {
        if (HAL_OK == hal_ssi_rx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->prx_gdma_adaptor)) {
            obj->dma_en |= SPI_DMA_RX_EN;
        } else {
            return HAL_BUSY;
        }
    }
    
    obj->state |= SPI_STATE_RX_BUSY;
    ret = hal_ssi_dma_recv(phal_ssi_adaptor, (u8*)rx_buffer, length);

    if (ret != HAL_OK) {
        obj->state &= ~SPI_STATE_RX_BUSY;
    }
    
    return (ret);
}

int32_t spi_slave_write_stream_dma(spi_t *obj, char *tx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int32_t ret;

    if (obj->state & SPI_STATE_TX_BUSY) {
        DBG_SSI_WARN("spi_slave_write_stream_dma: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    if ((obj->dma_en & SPI_DMA_TX_EN)==0) {
        if (HAL_OK == hal_ssi_tx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->ptx_gdma_adaptor)) {
            obj->dma_en |= SPI_DMA_TX_EN;
        } else {
            return HAL_BUSY;
        }
    }
    
    obj->state |= SPI_STATE_TX_BUSY;
    ret = hal_ssi_dma_send(phal_ssi_adaptor, (u8*)tx_buffer, length);
    
    if (ret != HAL_OK) {
        obj->state &= ~SPI_STATE_TX_BUSY;
    }
    
    return (ret);
}

int32_t spi_master_read_stream_dma(spi_t *obj, char *rx_buffer, uint32_t length)
{
    return spi_master_write_read_stream_dma(obj, rx_buffer, rx_buffer, length);
}

int32_t spi_master_write_stream_dma(spi_t *obj, char *tx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int32_t ret;

    if (obj->state & SPI_STATE_TX_BUSY) {
        DBG_SSI_WARN("spi_master_write_stream_dma: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    if ((obj->dma_en & SPI_DMA_TX_EN)==0) {
        if (HAL_OK == hal_ssi_tx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->ptx_gdma_adaptor)) {
            obj->dma_en |= SPI_DMA_TX_EN;
        } else {
            return HAL_BUSY;
        }
    }
    
    obj->state |= SPI_STATE_TX_BUSY;
    ret = hal_ssi_dma_send(phal_ssi_adaptor, (u8*)tx_buffer, length);
    
    if (ret != HAL_OK) {
        obj->state &= ~SPI_STATE_TX_BUSY;
    }

    return ret;
}

int32_t spi_master_write_read_stream_dma(spi_t *obj, char *tx_buffer, char *rx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    int32_t ret;

    if (obj->state & (SPI_STATE_RX_BUSY|SPI_STATE_TX_BUSY)) {
        DBG_SSI_WARN("spi_master_write_and_read_stream: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    if ((obj->dma_en & SPI_DMA_TX_EN)==0) {
        if (HAL_OK == hal_ssi_tx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->ptx_gdma_adaptor)) {
            obj->dma_en |= SPI_DMA_TX_EN;
        } else {
            return HAL_BUSY;
        }
    }
    
    if ((obj->dma_en & SPI_DMA_RX_EN)==0) {
        if (HAL_OK == hal_ssi_rx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->prx_gdma_adaptor)) {
            obj->dma_en |= SPI_DMA_RX_EN;
        } else {
            return HAL_BUSY;
        }
    }
    
    obj->state |= SPI_STATE_RX_BUSY;
    /* as Master mode, sending data will receive data at sametime */
    if ((ret = hal_ssi_dma_recv(phal_ssi_adaptor, (u8*)rx_buffer, length)) == HAL_OK) {
        obj->state |= SPI_STATE_TX_BUSY;
        if ((ret = hal_ssi_dma_send(phal_ssi_adaptor, (u8*)tx_buffer, length)) != HAL_OK) {
            obj->state &= ~(SPI_STATE_RX_BUSY|SPI_STATE_TX_BUSY);
        }
    } else {
        obj->state &= ~(SPI_STATE_RX_BUSY);
    }    

    return ret;
}

int32_t spi_slave_read_stream_dma_timeout(spi_t *obj, char *rx_buffer, uint32_t length, uint32_t timeout_ms)
{
    int ret,timeout = 0;
    u32 start_us;
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);

    if (obj->state & SPI_STATE_RX_BUSY) {
        DBG_SSI_WARN("spi_slave_read_stream_dma: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
    
    if ((obj->dma_en & SPI_DMA_RX_EN)==0) {
        if (HAL_OK == hal_ssi_rx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->prx_gdma_adaptor)) {
            obj->dma_en |= SPI_DMA_RX_EN;
        } else {
            return HAL_BUSY;
        }
    }
    
    obj->state |= SPI_STATE_RX_BUSY;

    hal_ssi_enter_critical(phal_ssi_adaptor);
    ret = hal_ssi_dma_recv(phal_ssi_adaptor, (u8*)rx_buffer, length);
    hal_ssi_exit_critical(phal_ssi_adaptor);
    
    if ((ret == HAL_OK) && (timeout_ms > 0)) {
        start_us = hal_read_cur_time();
        while (obj->state & SPI_STATE_RX_BUSY) {
             if (hal_is_timeout(start_us, timeout_ms*1000)) {
                ret = hal_ssi_stop_recv(phal_ssi_adaptor);
                obj->state &= ~ SPI_STATE_RX_BUSY;
                timeout = 1;
                DBG_SSI_INFO("Slave is timeout\n");
                break;
            }
        }

        if(timeout)
            return (length - phal_ssi_adaptor->rx_length);
        else
            return length;
               
    } 
    else {
        obj->state &= ~ SPI_STATE_RX_BUSY;
        return (-ret);
    }
}

int32_t spi_slave_read_stream_dma_terminate(spi_t *obj, char *rx_buffer, uint32_t length)
{
    phal_ssi_adaptor_t phal_ssi_adaptor = &(obj->hal_ssi_adaptor);
    volatile u8 cs_stop;
    int ret;

    cs_stop = 0;
    if (obj->state & SPI_STATE_RX_BUSY) {
        DBG_SSI_WARN("spi_slave_read_stream_dma: state(0x%x) is not ready\r\n", 
            obj->state);
        return HAL_BUSY;
    }
        
    if ((obj->dma_en & SPI_DMA_RX_EN)==0) {
        if (HAL_OK == hal_ssi_rx_gdma_init(phal_ssi_adaptor, phal_ssi_adaptor->prx_gdma_adaptor)) {
            obj->dma_en |= SPI_DMA_RX_EN;
        } else {
            return HAL_BUSY;
        }
    }

    obj->state |= SPI_STATE_RX_BUSY;
    hal_ssi_enter_critical(phal_ssi_adaptor);
    if ((ret = hal_ssi_dma_recv(phal_ssi_adaptor, (u8*)rx_buffer, length)) != HAL_OK) {
        obj->state &= ~ SPI_STATE_RX_BUSY;
    }
    hal_ssi_exit_critical(phal_ssi_adaptor);

    while(obj->state & SPI_STATE_RX_BUSY){
        while(hal_ssi_get_busy(phal_ssi_adaptor)){
            if((obj->state & SPI_STATE_RX_BUSY) == 0){   
                cs_stop = 0;
                break;
            } 
            
            if(hal_ssi_get_busy(phal_ssi_adaptor) == 0){
                ret = hal_ssi_stop_recv(phal_ssi_adaptor);
                goto EndOfDMACS;
            }
        }
    }
EndOfDMACS:
    if((obj->state & SPI_STATE_RX_BUSY) != 0){ 
        cs_stop = 1;
        obj->state &= ~ SPI_STATE_RX_BUSY;
    }
    
    if(cs_stop == 1)
        return (length - phal_ssi_adaptor->rx_length);
    else
        return length;
}

#endif  // end of "#ifdef CONFIG_GDMA_EN"
