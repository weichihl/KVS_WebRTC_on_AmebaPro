/**************************************************************************//**
 * @file     diag.h
 * @brief    This file defines macros for debug message printing.
 * @version  V1.00
 * @date     2016-7-20
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

#ifndef _DIAG_H_
#define _DIAG_H_
#include "platform_conf.h"
#include "basic_types.h"
#include <stdarg.h>
#include <stddef.h> /* for size_t */
#include "log_buf.h"
#include "rt_printf.h"
#include "utility.h"

#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
extern osMutexId PrintLock_id;
extern log_buf_type_t debug_log;
#endif

#if defined(ROM_REGION)
extern u32 ConfigDebugErr;
extern u32 ConfigDebugInfo;
extern u32 ConfigDebugWarn;
#else
#define ConfigDebugErr          (*(utility_stubs.config_debug_err))
#define ConfigDebugWarn         (*(utility_stubs.config_debug_warn))
#define ConfigDebugInfo         (*(utility_stubs.config_debug_info))
#if !defined(CONFIG_BUILD_SECURE) && !defined(CONFIG_BUILD_NONSECURE)
#define ConfigDebugErr_NS       (*(__rom_stubs_utility_ns.config_debug_err))
#define ConfigDebugWarn_NS      (*(__rom_stubs_utility_ns.config_debug_warn))
#define ConfigDebugInfo_NS      (*(__rom_stubs_utility_ns.config_debug_info))
#endif
#endif

#if defined(CONFIG_PLATFORM_8195BHP) && !defined(CONFIG_BUILD_SECURE) && !defined(CONFIG_BUILD_NONSECURE)
#define DBG_ERR_MSG_ON(x)       do {(ConfigDebugErr |= (x)); (ConfigDebugErr_NS |= (x));} while(0)
#define DBG_WARN_MSG_ON(x)      do {(ConfigDebugWarn |= (x)); (ConfigDebugWarn_NS |= (x));} while(0)
#define DBG_INFO_MSG_ON(x)      do {(ConfigDebugInfo |= (x)); (ConfigDebugInfo_NS |= (x));} while(0)

#define DBG_ERR_MSG_OFF(x)      do {(ConfigDebugErr &= ~(x)); (ConfigDebugErr_NS &= ~(x));} while(0)
#define DBG_WARN_MSG_OFF(x)     do {(ConfigDebugWarn &= ~(x)); (ConfigDebugWarn_NS &= ~(x));} while(0)
#define DBG_INFO_MSG_OFF(x)     do {(ConfigDebugInfo &= ~(x)); (ConfigDebugInfo_NS &= ~(x));} while(0)
#else
#define DBG_ERR_MSG_ON(x)       (ConfigDebugErr |= (x))
#define DBG_WARN_MSG_ON(x)      (ConfigDebugWarn |= (x))
#define DBG_INFO_MSG_ON(x)      (ConfigDebugInfo |= (x))

#define DBG_ERR_MSG_OFF(x)      (ConfigDebugErr &= ~(x))
#define DBG_WARN_MSG_OFF(x)     (ConfigDebugWarn &= ~(x))
#define DBG_INFO_MSG_OFF(x)     (ConfigDebugInfo &= ~(x))
#endif

// Define debug group
#define	_DBG_BOOT_          	0x00000001
#define	_DBG_GDMA_          	0x00000002
#define	_DBG_GPIO_			    0x00000004
#define	_DBG_TIMER_         	0x00000008
#define	_DBG_I2C_           	0x00000010
#define	_DBG_I2S_           	0x00000020
#define	_DBG_ETH_           	0x00000040
#define	_DBG_SGPIO_           	0x00000080
#define	_DBG_PCM_           	0x00000100
#define	_DBG_PWM_           	0x00000200
#define	_DBG_SSI_           	0x00000400
#define	_DBG_SPI_FLASH_         0x00000800
#define	_DBG_SDR_           	0x00001000
#define	_DBG_SDIO_DEV_         	0x00001000
#define	_DBG_UART_          	0x00002000
#define	_DBG_ADC_           	0x00004000
#define	_DBG_CHG_               0x00008000
#define	_DBG_QDEC_              0x00010000
#define	_DBG_CIR_               0x00020000
#define	_DBG_ICC_               0x00040000
#define	_DBG_SDIO_HOST_         0x00080000
#define	_DBG_COMP_              0x00100000
#define _DBG_CRYPTO_            0x00200000
#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define _DBG_MAIN_              0x00200000
#define _DBG_FIBO_              0x00400000
#endif
#define _DBG_SCE_               0x00800000
#define	_DBG_OTG_               0x01000000
#define _DBG_ISP_	            0x02000000
#define _DBG_ENC_	            0x04000000
#define _DBG_VOE_	            0x04000000
#define _DBG_LCDC_	            0x08000000
#define _DBG_DRAM_              0x10000000
#define	_DBG_AUDIO_           	0x20000000
#define _DBG_MISC_              0x40000000
#define	_DBG_FAULT_        	    0x80000000

#if CONFIG_LIGHT_PRINTF
// Light weight printf
#if defined(ROM_REGION)
#define dbg_printf(...)                     do { if(ConfigDebugErr & _DBG_BOOT_){_rtl_printf(__VA_ARGS__);} }while(0)
#define dbg_sprintf(buf, ...)               do { _rtl_sprintf(buf, __VA_ARGS__); }while(0)
#define dbg_snprintf(buf, size, ...)        do { _rtl_snprintf(buf, size, __VA_ARGS__); }while(0)
// Verifi mode, _DbgDump() for ROM Code
#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define _DbgDump(...) do{\
    if(PrintLock_id != NULL) \
        _mutex_rtl_printf(PrintLock_id,__VA_ARGS__);\
    else \
        _rtl_printf(__VA_ARGS__); \
}while(0)
#else
#define _DbgDump                            _rtl_printf
#endif

#else
#define dbg_printf                          rt_printfl
#define dbg_sprintf                         rt_sprintfl
#define dbg_snprintf                        rt_snprintfl
// Verifi mode, _DbgDump() for RAM Code
#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define _DbgDump(...) do{\
    if(PrintLock_id != NULL) \
        _mutex_rtl_printf(PrintLock_id,__VA_ARGS__);\
    else \
        rt_printfl(__VA_ARGS__); \
}while(0)
#else
#define _DbgDump                            rt_printfl
#endif
#endif

#else
// all-format printf
#if defined(ROM_REGION)
#define dbg_printf(...)                     do { if(ConfigDebugErr & _DBG_BOOT_){_xprintf(__VA_ARGS__);} }while(0)
#define dbg_sprintf(buf, ...)               do { _xsprintf(buf, __VA_ARGS__); }while(0)
#define dbg_snprintf(buf, size, ...)        do { _xsnprintf(buf, size, __VA_ARGS__); }while(0)
#define _DbgDump                            _xprintf
#else
#define dbg_printf                          rt_printf
#define dbg_sprintf                         rt_sprintf
#define dbg_snprintf                        rt_snprintf
#define _DbgDump                            rt_printf
#endif
#endif

#if defined(ROM_REGION)
#define log_printf(plog, ...)       do { _log_buf_printf(plog, __VA_ARGS__); }while(0)
#else
// Verifi mode, log_printf() for RAM Code
#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define log_printf(...) do {\
    rt_log_printf(&debug_log,__VA_ARGS__); \
}while(0)
#else
#define log_printf                  rt_log_printf
#endif
#endif

#define DRIVER_PREFIX	        "[Driver]: "
#define HAL_PREFIX              "[HAL]: "

#define BOOT_ERR_PREFIX         "[BOOT Err]"
#define BOOT_WARN_PREFIX        "[BOOT Wrn]"
#define BOOT_INFO_PREFIX        "[BOOT Inf]"

#define GDMA_ERR_PREFIX         "[GDMA Err]"
#define GDMA_WARN_PREFIX        "[GDMA Wrn]"
#define GDMA_INFO_PREFIX        "[GDMA Inf]"

#define GPIO_ERR_PREFIX         "[GPIO Err]"
#define GPIO_WARN_PREFIX        "[GPIO Wrn]"
#define GPIO_INFO_PREFIX        "[GPIO Inf]"

#define TIMER_ERR_PREFIX        "[TIMR Err]"
#define TIMER_WARN_PREFIX       "[TIMR Wrn]"
#define TIMER_INFO_PREFIX       "[TIMR Inf]"

#define I2C_ERR_PREFIX          "[I2C  Err]"
#define I2C_WARN_PREFIX         "[I2C  Wrn]"
#define I2C_INFO_PREFIX         "[I2C  Inf]"

#define I2S_ERR_PREFIX          "[I2S  Err]"
#define I2S_WARN_PREFIX         "[I2S  Wrn]"
#define I2S_INFO_PREFIX         "[I2S  Inf]"

#define ETH_ERR_PREFIX          "[ETH  Err]"
#define ETH_WARN_PREFIX         "[ETH  Wrn]"
#define ETH_INFO_PREFIX         "[ETH  Inf]"

#define NFC_ERR_PREFIX          "[NFC  Err]"
#define NFC_WARN_PREFIX         "[NFC  Wrn]"
#define NFC_INFO_PREFIX         "[NFC  Inf]"

#define PCM_ERR_PREFIX          "[PCM  Err]"
#define PCM_WARN_PREFIX         "[PCM  Wrn]"
#define PCM_INFO_PREFIX         "[PCM  Inf]"

#define PWM_ERR_PREFIX          "[PWM  Err]"
#define PWM_WARN_PREFIX         "[PWM  Wrn]"
#define PWM_INFO_PREFIX         "[PWM  Inf]"

#define SSI_ERR_PREFIX          "[SSI  Err]"
#define SSI_WARN_PREFIX         "[SSI  Wrn]"
#define SSI_INFO_PREFIX         "[SSI  Inf]"

#define SPIF_ERR_PREFIX         "[SPIF Err]"
#define SPIF_WARN_PREFIX        "[SPIF Wrn]"
#define SPIF_INFO_PREFIX        "[SPIF Inf]"

#define SDR_ERR_PREFIX          "[SDR  Err]"
#define SDR_WARN_PREFIX         "[SDR  Wrn]"
#define SDR_INFO_PREFIX         "[SDR  Inf]"

#define SDIO_DEV_ERR_PREFIX     "[SDIOD  Err]"
#define SDIO_DEV_WARN_PREFIX    "[SDIOD  Wrn]"
#define SDIO_DEV_INFO_PREFIX    "[SDIOD  Inf]"

#define UART_ERR_PREFIX         "[UART Err]"
#define UART_WARN_PREFIX        "[UART Wrn]"
#define UART_INFO_PREFIX        "[UART Inf]"

#define USB_ERR_PREFIX          "[USB  Err]"
#define USB_WARN_PREFIX         "[USB  Wrn]"
#define USB_INFO_PREFIX         "[USB  Inf]"

#define IPSEC_ERR_PREFIX        "[CRYP Err]"
#define IPSEC_WARN_PREFIX       "[CRYP Wrn]"
#define IPSEC_INFO_PREFIX       "[CRYP Inf]"

#define ADC_ERR_PREFIX          "[ADC  Err]"
#define ADC_WARN_PREFIX         "[ADC  Wrn]"
#define ADC_INFO_PREFIX         "[ADC  Inf]"

#define CHG_ERR_PREFIX          "[CHG  Err]"
#define CHG_WARN_PREFIX         "[CHG  Wrn]"
#define CHG_INFO_PREFIX         "[CHG  Inf]"

#define SGPIO_ERR_PREFIX        "[SGPIO Err]"
#define SGPIO_WARN_PREFIX       "[SGPIO Wrn]"
#define SGPIO_INFO_PREFIX       "[SGPIO Inf]"

#define OTG_ERR_PREFIX          "[OTG Err]"
#define OTG_WARN_PREFIX         "[OTG Wrn]"
#define OTG_INFO_PREFIX         "[OTG Inf]"

#define QDEC_ERR_PREFIX         "[QDEC  Err]"
#define QDEC_WARN_PREFIX        "[QDEC  Wrn]"
#define QDEC_INFO_PREFIX        "[QDEC  Inf]"

#define CIR_ERR_PREFIX          "[CIR  Err]"
#define CIR_WARN_PREFIX         "[CIR  Wrn]"
#define CIR_INFO_PREFIX         "[CIR  Inf]"

#define ICC_ERR_PREFIX          "[ICC  Err]"
#define ICC_WARN_PREFIX         "[ICC  Wrn]"
#define ICC_INFO_PREFIX         "[ICC  Inf]"

#define MISC_ERR_PREFIX         "[MISC Err]"
#define MISC_WARN_PREFIX        "[MISC Wrn]"
#define MISC_INFO_PREFIX        "[MISC Inf]"

#define SDIOH_ERR_PREFIX        "[SDIOH Err]"
#define SDIOH_WARN_PREFIX       "[SDIOH Wrn]"
#define SDIOH_INFO_PREFIX       "[SDIOH Inf]"
#define COMP_ERR_PREFIX         "[COMP Err]"
#define COMP_WARN_PREFIX        "[COMP Wrn]"
#define COMP_INFO_PREFIX        "[COMP Inf]"


#define ISP_ERR_PREFIX			"[ISP Err]"
#define ISP_WARN_PREFIX			"[ISP Wrn]"
#define ISP_INFO_PREFIX			"[ISP Inf]"

#define ENC_ERR_PREFIX			"[ENC Err]"
#define ENC_WARN_PREFIX			"[ENC Wrn]"
#define ENC_INFO_PREFIX			"[ENC Inf]"

#define VOE_ERR_PREFIX			"[VOE Err]"
#define VOE_WARN_PREFIX			"[VOE Wrn]"
#define VOE_INFO_PREFIX			"[VOE Inf]"

#define LCDC_ERR_PREFIX         "[LCDC Err]"
#define LCDC_WARN_PREFIX        "[LCDC Wrn]"
#define LCDC_INFO_PREFIX        "[LCDC Inf]"

#define DRAM_ERR_PREFIX         "[DRAM Err]"
#define DRAM_WARN_PREFIX        "[DRAM Wrn]"
#define DRAM_INFO_PREFIX        "[DRAM Inf]"

#define SCE_ERR_PREFIX          "[SCE Err]"
#define SCE_WARN_PREFIX         "[SCE Wrn]"
#define SCE_INFO_PREFIX         "[SCE Inf]"

#define AUDIO_ERR_PREFIX        "[AUDIO  Err]"
#define AUDIO_WARN_PREFIX       "[AUDIO  Wrn]"
#define AUDIO_INFO_PREFIX       "[AUDIO  Inf]"

#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define MAIN_INFO_PREFIX        "[MAIN Inf]"
#define FIBO_INFO_PREFIX        "[FIBO Inf]"
#endif


#ifndef likely
#define likely(x)               (x)
#define unlikely(x)             (x)
#endif

#if CONFIG_DEBUG_LOG

#if CONFIG_DEBUG_ERROR      // if Build-In Debug Error Message

#define DBG_BOOT_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_BOOT_)) \
        _DbgDump("\r" BOOT_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GDMA_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_GDMA_)) \
        _DbgDump("\r" GDMA_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GPIO_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_GPIO_)) \
        _DbgDump("\r" GPIO_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_TIMER_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_TIMER_)) \
        _DbgDump("\r" TIMER_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2C_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_I2C_)) \
        _DbgDump("\r" I2C_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2S_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_I2S_)) \
        _DbgDump("\r" I2S_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ETH_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_ETH_)) \
        _DbgDump("\r" ETH_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_NFC_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_NFC_)) \
        _DbgDump("\r" NFC_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PCM_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_PCM_)) \
        _DbgDump("\r" PCM_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PWM_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_PWM_)) \
        _DbgDump("\r" PWM_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SSI_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SSI_)) \
        _DbgDump("\r" SSI_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SPIF_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SPI_FLASH_)) \
        _DbgDump("\r" SPIF_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDR_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SDR_)) \
        _DbgDump("\r" SDR_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDIO_DEV_ERR(...)     do {\
        if (likely(ConfigDebugErr & _DBG_SDIO_DEV_)) \
            _DbgDump("\r" SDIO_DEV_ERR_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_UART_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_UART_)) \
        _DbgDump("\r" UART_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_CRYPTO_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_CRYPTO_)) \
        _DbgDump("\r" IPSEC_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ADC_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_ADC_)) \
        _DbgDump("\r" ADC_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_CHG_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_CHG_)) \
        _DbgDump("\r" CHG_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SGPIO_ERR(...)     do {\
                if (likely(ConfigDebugErr & _DBG_SGPIO_)) \
                    _DbgDump("\r" SGPIO_ERR_PREFIX __VA_ARGS__);\
            }while(0)
        
#define DBG_QDEC_ERR(...)     do {\
                if (likely(ConfigDebugErr & _DBG_QDEC_)) \
                    _DbgDump("\r" QDEC_ERR_PREFIX __VA_ARGS__);\
            }while(0)

#define DBG_CIR_ERR(...)     do {\
                if (likely(ConfigDebugErr & _DBG_CIR_)) \
                    _DbgDump("\r" CIR_ERR_PREFIX __VA_ARGS__);\
            }while(0)

#define DBG_ICC_ERR(...)     do {\
                if (likely(ConfigDebugErr & _DBG_ICC_)) \
                    _DbgDump("\r" ICC_ERR_PREFIX __VA_ARGS__);\
            }while(0)

#define DBG_MISC_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_MISC_)) \
        _DbgDump("\r" MISC_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDIOH_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_SDIO_HOST_)) \
        _DbgDump("\r" SDIOH_ERR_PREFIX __VA_ARGS__);\
}while(0)
#define DBG_COMP_ERR(...)     do {\
        if (likely(ConfigDebugErr & _DBG_COMP_)) \
            _DbgDump("\r" COMP_ERR_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_OTG_ERR(...)     do {\
        if (likely(ConfigDebugErr & _DBG_OTG_)) \
            _DbgDump("\r" OTG_ERR_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_SCE_ERR(...)     do {\
                if (likely(ConfigDebugErr & _DBG_SCE_)) \
                    _DbgDump("\r" SCE_ERR_PREFIX __VA_ARGS__);\
            }while(0)

#define DBG_DRAM_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_DRAM_)) \
        _DbgDump("\r" DRAM_ERR_PREFIX __VA_ARGS__);\
    }while(0)        

#define DBG_ISP_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_ISP_)) \
        _DbgDump("\r" ISP_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ENC_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_ENC_)) \
        _DbgDump("\r" ENC_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_VOE_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_VOE_)) \
        _DbgDump("\r" VOE_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_LCDC_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_LCDC_)) \
        _DbgDump("\r" LCDC_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_AUDIO_ERR(...)     do {\
    if (likely(ConfigDebugErr & _DBG_AUDIO_)) \
        _DbgDump("\r" AUDIO_ERR_PREFIX __VA_ARGS__);\
}while(0)

#else   // else of "#if CONFIG_DEBUG_ERROR"

#define DBG_BOOT_ERR(...)
#define DBG_GDMA_ERR(...)
#define DBG_GPIO_ERR(...)
#define DBG_TIMER_ERR(...)
#define DBG_I2C_ERR(...)
#define DBG_I2S_ERR(...)
#define DBG_ETH_ERR(...)
#define DBG_NFC_ERR(...)
#define DBG_PCM_ERR(...)
#define DBG_PWM_ERR(...)
#define DBG_SSI_ERR(...)
#define DBG_SPIF_ERR(...)
#define DBG_SDR_ERR(...)
#define DBG_UART_ERR(...)
#define DBG_CRYPTO_ERR(...)
#define DBG_ADC_ERR(...)
#define DBG_CHG_ERR(...)
#define DBG_SGPIO_ERR(...)
#define DBG_QDEC_ERR(...)
#define DBG_CIR_ERR(...)
#define DBG_MISC_ERR(...)
#define DBG_ICC_ERR(...)
#define DBG_SDIOH_ERR(...)
#define DBG_COMP_ERR(...)
#define DBG_OTG_ERR(...)
#define DBG_DRAM_ERR(...)

#define DBG_ISP_ERR(...)
#define DBG_ENC_ERR(...)
#define DBG_VOE_ERR(...)
#define DBG_LCDC_ERR(...)

#define DBG_AUDIO_ERR(...)

#define MSG_MBOX_ERR(...)
#define MSG_TIMER_ERR(...)

#endif  // end of else of "#if CONFIG_DEBUG_ERROR"

// =============================================================

#if CONFIG_DEBUG_WARN     // if Build-In Debug Warring Message

#define DBG_BOOT_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn& _DBG_BOOT_)) \
        _DbgDump("\r" BOOT_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GDMA_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_GDMA_)) \
        _DbgDump("\r" GDMA_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GPIO_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_GPIO_)) \
        _DbgDump("\r" GPIO_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_TIMER_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_TIMER_)) \
        _DbgDump("\r" TIMER_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2C_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_I2C_)) \
        _DbgDump("\r" I2C_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2S_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_I2S_)) \
        _DbgDump("\r" I2S_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ETH_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_ETH_)) \
        _DbgDump("\r" ETH_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_NFC_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_NFC_)) \
        _DbgDump("\r" NFC_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PCM_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_PCM_)) \
        _DbgDump("\r" PCM_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PWM_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_PWM_)) \
        _DbgDump("\r" PWM_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SSI_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_SSI_)) \
        _DbgDump("\r" SSI_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SPIF_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_SPI_FLASH_)) \
        _DbgDump("\r" SPIF_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDR_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_SDR_)) \
        _DbgDump("\r" SDR_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDIO_DEV_WARN(...)     do {\
        if (unlikely(ConfigDebugWarn & _DBG_SDIO_DEV_)) \
            _DbgDump("\r" SDIO_DEV_WARN_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_UART_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_UART_)) \
        _DbgDump("\r" UART_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_CRYPTO_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_CRYPTO_)) \
        _DbgDump("\r" IPSEC_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ADC_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_ADC_)) \
        _DbgDump("\r" ADC_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_CHG_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_CHG_)) \
        _DbgDump("\r" CHG_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SGPIO_WARN(...)     do {\
        if (unlikely(ConfigDebugWarn & _DBG_SGPIO_)) \
            _DbgDump("\r" SGPIO_WARN_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_QDEC_WARN(...)     do {\
            if (unlikely(ConfigDebugWarn & _DBG_QDEC_)) \
                _DbgDump("\r" QDEC_WARN_PREFIX __VA_ARGS__);\
        }while(0)
    
#define DBG_CIR_WARN(...)     do {\
            if (unlikely(ConfigDebugWarn & _DBG_CIR_)) \
                _DbgDump("\r" CIR_WARN_PREFIX __VA_ARGS__);\
        }while(0)

#define DBG_ICC_WARN(...)     do {\
            if (unlikely(ConfigDebugWarn & _DBG_ICC_)) \
                _DbgDump("\r" ICC_WARN_PREFIX __VA_ARGS__);\
        }while(0)

#define DBG_COMP_WARN(...)     do {\
            if (unlikely(ConfigDebugWarn & _DBG_COMP_)) \
                _DbgDump("\r" COMP_WARN_PREFIX __VA_ARGS__);\
        }while(0)            
        
#define DBG_MISC_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_MISC_)) \
        _DbgDump("\r" MISC_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDIOH_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_SDIO_HOST_)) \
        _DbgDump("\r" SDIOH_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_OTG_WARN(...)     do {\
    if (likely(ConfigDebugWarn & _DBG_OTG_)) \
        _DbgDump("\r" OTG_ERR_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SCE_WARN(...)     do {\
        if (likely(ConfigDebugWarn & _DBG_SCE_)) \
            _DbgDump("\r" SCE_ERR_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_ISP_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_ISP_)) \
        _DbgDump("\r" ISP_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ENC_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_ENC_)) \
        _DbgDump("\r" ENC_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_VOE_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_VOE_)) \
        _DbgDump("\r" VOE_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_DRAM_WARN(...)     do {\
        if (unlikely(ConfigDebugWarn & _DBG_DRAM_)) \
            _DbgDump("\r" DRAM_WARN_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_LCDC_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_LCDC_)) \
        _DbgDump("\r" LCDC_WARN_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_AUDIO_WARN(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_AUDIO_)) \
        _DbgDump("\r" AUDIO_WARN_PREFIX __VA_ARGS__);\
}while(0)

#else   // else of "#if CONFIG_DEBUG_WARN"

#define DBG_BOOT_WARN(...)
#define DBG_GDMA_WARN(...)
#define DBG_GPIO_WARN(...)
#define DBG_TIMER_WARN(...)
#define DBG_I2C_WARN(...)
#define DBG_I2S_WARN(...)
#define DBG_ETH_WARN(...)
#define DBG_NFC_WARN(...)
#define DBG_PCM_WARN(...)
#define DBG_PWM_WARN(...)
#define DBG_SSI_WARN(...)
#define DBG_SPIF_WARN(...)
#define DBG_SDR_WARN(...)
#define DBG_UART_WARN(...)
#define DBG_CRYPTO_WARN(...)
#define DBG_ADC_WARN(...)
#define DBG_CHG_WARN(...)
#define DBG_SGPIO_WARN(...)
#define DBG_QDEC_WARN(...)
#define DBG_CIR_WARN(...)
#define DBG_ICC_WARN(...)
#define DBG_SDIOH_WARN(...)
#define DBG_COMP_WARN(...)
#define DBG_OTG_WARN(...)

#define DBG_ISP_WARN(...)
#define DBG_ENC_WARN(...)
#define DBG_VOE_WARN(...)
#define DBG_LCDC_WARN(...)

#define DBG_AUDIO_WARN(...)

#define DBG_MISC_WARN(...)

#define MSG_MBOX_WARN(...)
#define MSG_TIMER_WARN(...)

#define DBG_DRAM_WARN(...)

#endif  // end of else of "#if CONFIG_DEBUG_WARN"

// =============================================================
// Verifi mode for IP_CALL_BACK_INFO()
#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define DBG_I2C_CLBKINFO(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_I2C_)) \
        log_printf("\r" I2C_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_UART_CLBKINFO(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_UART_)) \
        log_printf("\r" UART_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_TIMER_CLBKINFO(...)     do {\
    if (unlikely(ConfigDebugWarn & _DBG_TIMER_)) \
        log_printf("\r" TIMER_INFO_PREFIX __VA_ARGS__);\
}while(0)

#endif

// =============================================================

#if CONFIG_DEBUG_INFO     // if Build-In Debug Information Message

#define DBG_BOOT_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_BOOT_)) \
        _DbgDump("\r" BOOT_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GDMA_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_GDMA_)) \
        _DbgDump("\r" GDMA_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_GPIO_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_GPIO_)) \
        _DbgDump("\r" GPIO_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_TIMER_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_TIMER_)) \
        _DbgDump("\r" TIMER_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2C_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_I2C_)) \
        _DbgDump("\r" I2C_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_I2S_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_I2S_)) \
        _DbgDump("\r" I2S_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ETH_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_ETH_)) \
        _DbgDump("\r" ETH_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_NFC_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_NFC_)) \
        _DbgDump("\r" NFC_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PCM_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_PCM_)) \
        _DbgDump("\r" PCM_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_PWM_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_PWM_)) \
        _DbgDump("\r" PWM_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SSI_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_SSI_)) \
        _DbgDump("\r" SSI_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SPIF_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_SPI_FLASH_)) \
        _DbgDump("\r" SPIF_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDR_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_SDR_)) \
        _DbgDump("\r" SDR_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDIO_DEV_INFO(...)     do {\
        if (unlikely(ConfigDebugInfo & _DBG_SDIO_DEV_)) \
            _DbgDump("\r" SDIO_DEV_INFO_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_UART_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_UART_)) \
        _DbgDump("\r" UART_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_CRYPTO_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_CRYPTO_)) \
        _DbgDump("\r" IPSEC_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ADC_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_ADC_)) \
        _DbgDump("\r" ADC_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_CHG_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_CHG_)) \
        _DbgDump("\r" CHG_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SGPIO_INFO(...)     do {\
        if (unlikely(ConfigDebugInfo & _DBG_SGPIO_)) \
            _DbgDump("\r" SGPIO_INFO_PREFIX __VA_ARGS__);\
    }while(0)
    
#define DBG_QDEC_INFO(...)     do {\
        if (unlikely(ConfigDebugInfo & _DBG_QDEC_)) \
            _DbgDump("\r" QDEC_INFO_PREFIX __VA_ARGS__);\
    }while(0)
    
#define DBG_CIR_INFO(...)     do {\
        if (unlikely(ConfigDebugInfo & _DBG_CIR_)) \
            _DbgDump("\r" CIR_INFO_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_ICC_INFO(...)     do {\
        if (unlikely(ConfigDebugInfo & _DBG_ICC_)) \
            _DbgDump("\r" ICC_INFO_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_COMP_INFO(...)     do {\
                if (unlikely(ConfigDebugInfo & _DBG_COMP_)) \
                    _DbgDump("\r" COMP_INFO_PREFIX __VA_ARGS__);\
            }while(0)

#define DBG_OTG_INFO(...)     do {\
        if (unlikely(ConfigDebugInfo & _DBG_OTG_)) \
            _DbgDump("\r" OTG_INFO_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_SCE_INFO(...)     do {\
                if (unlikely(ConfigDebugInfo & _DBG_SCE_)) \
                    _DbgDump("\r" SCE_INFO_PREFIX __VA_ARGS__);\
            }while(0)

#define DBG_DRAM_INFO(...)     do {\
            if (unlikely(ConfigDebugInfo & _DBG_DRAM_)) \
                _DbgDump("\r" DRAM_INFO_PREFIX __VA_ARGS__);\
        }while(0)

#define DBG_MISC_INFO(...)     do {\
    if (likely(ConfigDebugInfo & _DBG_MISC_)) \
        _DbgDump("\r" MISC_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_SDIOH_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_SDIO_HOST_)) \
        _DbgDump("\r" SDIOH_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ISP_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_ISP_)) \
        _DbgDump("\r" ISP_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_ENC_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_ENC_)) \
        _DbgDump("\r" ENC_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_VOE_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_VOE_)) \
        _DbgDump("\r" VOE_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_LCDC_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_LCDC_)) \
        _DbgDump("\r" LCDC_INFO_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_AUDIO_INFO(...)     do {\
    if (unlikely(ConfigDebugInfo & _DBG_AUDIO_)) \
        _DbgDump("\r" AUDIO_INFO_PREFIX __VA_ARGS__);\
}while(0)

#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define DBG_MAIN_INFO(...)     do {\
        if (unlikely(ConfigDebugInfo & _DBG_MAIN_)) \
            _DbgDump("\r" MAIN_INFO_PREFIX __VA_ARGS__);\
    }while(0)

#define DBG_FIBO_INFO(...)     do {\
        if (unlikely(ConfigDebugInfo & _DBG_FIBO_)) \
            _DbgDump("\r" FIBO_INFO_PREFIX __VA_ARGS__);\
    }while(0)
#endif

#else   // else of "#if CONFIG_DEBUG_INFO"

#define DBG_BOOT_INFO(...)
#define DBG_GDMA_INFO(...)
#define DBG_GPIO_INFO(...)
#define DBG_TIMER_INFO(...)
#define DBG_I2C_INFO(...)
#define DBG_I2S_INFO(...)
#define DBG_ETH_INFO(...)
#define DBG_NFC_INFO(...)
#define DBG_PCM_INFO(...)
#define DBG_PWM_INFO(...)
#define DBG_SSI_INFO(...)
#define DBG_SPIF_INFO(...)
#define DBG_SDR_INFO(...)
#define DBG_UART_INFO(...)
#define DBG_CRYPTO_INFO(...)
#define DBG_ADC_INFO(...)
#define DBG_CHG_INFO(...)
#define DBG_SGPIO_INFO(...)
#define DBG_QDEC_INFO(...)
#define DBG_CIR_INFO(...)
#define DBG_ICC_INFO(...)
#define DBG_SDIOH_INFO(...)
#define DBG_COMP_INFO(...)
#define DBG_OTG_INFO(...)
#define DBG_DRAM_INFO(...)

#define DBG_ISP_INFO(...)
#define DBG_ENC_INFO(...)
#define DBG_VOE_INFO(...)
#define DBG_LCDC_INFO(...)

#define DBG_AUDIO_INFO(...)

#if defined(CONFIG_VRF_MODE) && (CONFIG_VRF_MODE==1)
#define DBG_MAIN_INFO(...)
#define DBG_FIBO_INFO(...)
#endif

#define DBG_MISC_INFO(...)

#define MSG_MBOX_INFO(...)
#define MSG_TIMER_INFO(...)

#endif  // end of else of "#if CONFIG_DEBUG_INFO"

#define DBG_8195BL_DRIVER(...)     do {\
    if (unlikely(ConfigDebugErr & (_DBG_I2S_|_DBG_PCM_|_DBG_TIMER_))) \
        _DbgDump("\r" DRIVER_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_8195BL_HAL(...)     do {\
    if (unlikely(ConfigDebugErr & (_DBG_SDR_|_DBG_MISC_))) \
        _DbgDump("\r" HAL_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_8195BL_DMA(...)     do {\
    if (unlikely(ConfigDebugErr & _DBG_GDMA_)) \
        _DbgDump("\r" DMA_PREFIX __VA_ARGS__);\
}while(0)

#define DBG_8195BL(...)     do {\
    if (unlikely(ConfigDebugErr & _DBG_MISC_)) \
        _DbgDump("\r" __VA_ARGS__);\
}while(0)

#define MONITOR_LOG(...)     do {\
    if (unlikely(ConfigDebugErr & _DBG_MISC_)) \
        _DbgDump( __VA_ARGS__);\
}while(0)

#define DBG_ERROR_LOG(...)     do {\
    if (unlikely(ConfigDebugErr & _DBG_FAULT_)) \
        _DbgDump( __VA_ARGS__);\
}while(0)


#ifndef DBG_ASSERT
// TODO : include dbg_assert.h to collect the defination to one place
#define DBG_ASSERT(x, msg)		do { \
						if((x) == 0) \
							printf("\n\r%s, Assert(" #x ") failed on line %d in file %s", msg, __LINE__, __FILE__); \
					} while(0)
#endif  // #ifndef DBG_ASSERT


#else   // else of "#if CONFIG_DEBUG_LOG"
#define DBG_8195BL_DRIVER(...)

#define DBG_8195BL_HAL(...)

#define DBG_8195BL(...)

#define DBG_8195BL_DMA(...)

#define MONITOR_LOG(...)

#define DBG_ERROR_LOG(...)

#define DBG_BOOT_ERR(...)
#define DBG_GDMA_ERR(...)
#define DBG_GPIO_ERR(...)
#define DBG_TIMER_ERR(...)
#define DBG_I2C_ERR(...)
#define DBG_I2S_ERR(...)
#define DBG_ETH_ERR(...)
#define DBG_NFC_ERR(...)
#define DBG_PCM_ERR(...)
#define DBG_PWM_ERR(...)
#define DBG_SSI_ERR(...)
#define DBG_SPIF_ERR(...)
#define DBG_SDR_ERR(...)
#define DBG_UART_ERR(...)
#define DBG_CRYPTO_ERR(...)
#define DBG_ADC_ERR(...)
#define DBG_CHG_ERR(...)
#define DBG_SGPIO_ERR(...)
#define DBG_QDEC_ERR(...)
#define DBG_CIR_ERR(...)
#define DBG_ICC_ERR(...)
#define DBG_MISC_ERR(...)
#define DBG_SDIOH_ERR(...)
#define DBG_OTG_ERR(...)
#define DBG_DRAM_ERR(...)
#define DBG_ISP_ERR(...)
#define DBG_ENC_ERR(...)
#define DBG_VOE_ERR(...)
#define DBG_LCDC_ERR(...)
#define DBG_AUDIO_ERR(...)

#define MSG_MBOX_ERR(...)
#define MSG_TIMER_ERR(...)

#define DBG_BOOT_WARN(...)
#define DBG_GDMA_WARN(...)
#define DBG_GPIO_WARN(...)
#define DBG_TIMER_WARN(...)
#define DBG_I2C_WARN(...)
#define DBG_I2S_WARN(...)
#define DBG_ETH_WARN(...)
#define DBG_NFC_WARN(...)
#define DBG_PCM_WARN(...)
#define DBG_PWM_WARN(...)
#define DBG_SSI_WARN(...)
#define DBG_SPIF_WARN(...)
#define DBG_SDR_WARN(...)
#define DBG_UART_WARN(...)
#define DBG_CRYPTO_WARN(...)
#define DBG_ADC_WARN(...)
#define DBG_CHG_WARN(...)
#define DBG_SGPIO_WARN(...)
#define DBG_QDEC_WARN(...)
#define DBG_CIR_WARN(...)
#define DBG_ICC_WARN(...)
#define DBG_MISC_WARN(...)
#define DBG_SDIOH_WARN(...)
#define DBG_OTG_WARN(...)
#define DBG_DRAM_WARN(...)
#define DBG_ISP_WARN(...)
#define DBG_ENC_WARN(...)
#define DBG_VOE_WARN(...)
#define DBG_LCDC_WARN(...)
#define DBG_AUDIO_WARN(...)

#define MSG_MBOX_WARN(...)
#define MSG_TIMER_WARN(...)

#define DBG_BOOT_INFO(...)
#define DBG_GDMA_INFO(...)
#define DBG_GPIO_INFO(...)
#define DBG_TIMER_INFO(...)
#define DBG_I2C_INFO(...)
#define DBG_I2S_INFO(...)
#define DBG_ETH_INFO(...)
#define DBG_NFC_INFO(...)
#define DBG_PCM_INFO(...)
#define DBG_PWM_INFO(...)
#define DBG_SSI_INFO(...)
#define DBG_SPIF_INFO(...)
#define DBG_SDR_INFO(...)
#define DBG_UART_INFO(...)
#define DBG_CRYPTO_INFO(...)
#define DBG_ADC_INFO(...)
#define DBG_CHG_INFO(...)
#define DBG_SGPIO_INFO(...)
#define DBG_QDEC_INFO(...)
#define DBG_CIR_INFO(...)
#define DBG_ICC_INFO(...)
#define DBG_MISC_INFO(...)
#define DBG_SDIOH_INFO(...)
#define DBG_OTG_INFO(...)
#define DBG_DRAM_INFO(...)
#define DBG_ISP_INFO(...)
#define DBG_ENC_INFO(...)
#define DBG_VOE_INFO(...)
#define DBG_LCDC_INFO(...)
#define DBG_AUDIO_INFO(...)

#define MSG_MBOX_INFO(...)
#define MSG_TIMER_INFO(...)

#define DBG_ASSERT(x)

#endif

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define IDENT_ONE_SPACE    " "
#define IDENT_TWO_SPACE    "  "
#define IDENT_FOUR_SPACE   "    "
#define IDENT_SIX_SPACE    "      "
#define IDENT_EIGHT_SPACE  "        "

#if CONFIG_DEBUG_LOG
typedef enum _DBG_CFG_TYPE_ {
	DBG_CFG_ERR=0,
	DBG_CFG_WARN=1,
	DBG_CFG_INFO=2
} DBG_CFG_TYPE;

typedef struct _DBG_CFG_CMD_ {
	u8 cmd_name[16];
	u32	cmd_type;
} DBG_CFG_CMD, *PDBG_CFG_CMD;

#endif

typedef enum _CONSOLE_OP_STAGE_ {
    ROM_STAGE = 0,
    RAM_STAGE = 1
}CONSOLE_OP_STAGE;

#endif //_DIAG_H_
