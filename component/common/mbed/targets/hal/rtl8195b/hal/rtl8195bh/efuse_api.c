/**************************************************************************//**
 * @file     efuse_api.c
 * @brief    This file implements the EFUSE Mbed HAL API functions.
 * 
 * @version  V1.00
 * @date     2018-05-02
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
#include "hal_efuse.h"
#include "efuse_api.h"
#include "string.h"

#if CONFIG_EFUSE_EN

int efuse_get_remaining_length(void)
{
    //not support
    return -1;
}

void efuse_mtp_read(uint8_t * data)
{
    //not support
}

int efuse_mtp_write(uint8_t *data, uint8_t len)
{
    //not support
    return -1;
}

int efuse_disable_jtag(void)
{
    //not support
    return -1;
}

#if !defined(CONFIG_BUILD_NONSECURE)
int efuse_otp_read(u8 address, u8 len, u8 *buf)
{
    u8 content[32];	// the OTP max length is 32
	
	if((address+len) > 32)
		return -1;

    hal_user_otp_get(content);
	memcpy(buf, content+address, len);
	return 0;
}

int efuse_otp_write(u8 address, u8 len, u8 *buf)
{
    u8 content[32];	// the OTP max length is 32
	
	if((address+len) > 32)
		return -1;
    
	memset(content, 0xFF, 32);
	memcpy(content+address, buf, len);
	hal_user_otp_set(content);
	return 0;
}

int efuse_sec_key_write(u8 *buf)
{
    if(hal_sec_key_write(buf) == _FALSE)
        return -1;

    return 0;
}

int efuse_susec_key_write(u8 *buf)
{
    if(hal_susec_key_write(buf) == _FALSE)
        return -1;

    return 0;
}
#endif // #if !defined(CONFIG_BUILD_NONSECURE)

#if defined(CONFIG_BUILD_NONSECURE)
int efuse_otp_read(u8 address, u8 len, u8 *buf)
{
    //not support
    return -1;
}

int efuse_otp_write(u8 address, u8 len, u8 *buf)
{
    //not support
    return -1;
}

int efuse_sec_key_write(u8 *buf)
{
    //not support
    return -1;    
}

int efuse_susec_key_write(u8 *buf)
{
    //not support
    return -1;     
}
#endif // #if defined(CONFIG_BUILD_NONSECURE)

#endif // #if CONFIG_EFUSE_EN

