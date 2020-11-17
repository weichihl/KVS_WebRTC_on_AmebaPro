/**************************************************************************//**
 * @file     port_api.c
 * @brief    Implements the mbed GPIO port API.
 *
 * @version  V1.00
 * @date     2017-09-27
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
#include "objects.h"
#include "port_api.h"
#include "pinmap.h"
#include "gpio_api.h"
#include "PinNames.h"
//#include "mbed_error.h"

extern hal_gpio_comm_adapter_t mbd_gpio_com_adp;
extern uint32_t is_mbd_gpio_com_inited;

#if DEVICE_PORTIN || DEVICE_PORTOUT

/**
  * @brief  Initializes the GPIO device port, include data direction registers.
  * @param[in]  obj: gpio port object defines in application software.
  * @param[in]  port: PortName according to pinmux spec, this parameter can be one of the following values:
  *		@arg PortA: port A, has 13 pins
  * @param[in]  mask: One bit one gpio pin, select one or multiple pins of the specified port.
  * @param[in]  dir: gpio port direction, this parameter can be one of the following values:
  *		@arg PIN_INPUT: port pins are input
  *		@arg PIN_OUTPUT: port pins are output
  * @retval none
  */
void port_init (port_t *obj, PortName port, int mask, PinDirection dir)
{
    hal_status_t ret;
    
    if (!is_mbd_gpio_com_inited) {
        hal_gpio_comm_init (&mbd_gpio_com_adp);
        is_mbd_gpio_com_inited = 1;
    }

    ret = hal_gpio_port_init (&obj->hal_port, (uint32_t)port, mask, dir);
    if (ret != HAL_OK) {
        DBG_GPIO_ERR ("port_init error (%d)\r\n", ret);
    }
}

/**
  * @brief  Set GPIO port pins data direction.
  * @param[in]  obj: gpio port object defines in application software.
  * @param[in]  dir: this parameter can be one of the following values:
  *		@arg PIN_INPUT: port pins are input
  *		@arg PIN_OUTPUT: port pins are output
  * @retval none
  */
void port_dir (port_t *obj, PinDirection dir)
{
    uint32_t *port_dir_en;

    if (obj->hal_port.port_idx != 0) {
        // this platform only has 1 GPIO port(port index = 0)
        DBG_GPIO_ERR ("port_dir error, incorrect port index, didn't init?\r\n");
        return;
    }

    if (dir == PIN_INPUT) {
        port_dir_en = (uint32_t *)&(GPIO->port_a_idm_en);
    } else {
        port_dir_en = (uint32_t *)&(GPIO->port_a_odm_en);
    }
    *port_dir_en = obj->hal_port.pin_mask;
}

/**
  * @brief  Configure GPIO port pins pull up/pull down.
  * @param[in]  obj: gpio port object define in application software.
  * @param[in]  mode: this parameter can be one of the following values:
  *		@arg PullNone: HighZ
  *		@arg OpenDrain(is OpenDrain output): no pull + OUT + GPIO[gpio_bit] = 0
  *		@arg PullDown: pull down
  *		@arg PullUp: pull up
  * @retval none
  */
void port_mode (port_t *obj, PinMode mode)
{
    uint32_t i;
    phal_gpio_port_adapter_t phal_port;
    uint8_t pin_name;

    phal_port = &obj->hal_port;
    for (i = 0; i < MAX_PIN_IN_PORT; i++) { // Process all pins
        if ((phal_port->pin_mask & (1 << i)) != 0) {
            pin_name = PIN_NAME(phal_port->port_idx, i);
            hal_gpio_pull_ctrl (pin_name, mode);
        }
    }
}

/**
  * @brief  Sets value to the selected port pins.
  * @param[in]  obj: gpio port object define in application software.
  * @param[in]  value: One bit one gpio pin, set value to one or multiple pins of the specified port.
  * @retval none
  * @note corresponding bit is 1, pin state set to high; corresponding bit is 0, pin state set to low
  */
void port_write (port_t *obj, int value)
{
    hal_gpio_port_write (&obj->hal_port, value);
}

/**
  * @brief  Reads the specified gpio port pins.
  * @param[in]  obj: gpio port object define in application software.
  * @retval[in] : state of the specified gpio port pins
  * @note corresponding bit is 1, pin state is high; corresponding bit is 0, pin state is low
  */
int port_read (port_t *obj)
{
    return hal_gpio_port_read (&obj->hal_port);
}

#endif

