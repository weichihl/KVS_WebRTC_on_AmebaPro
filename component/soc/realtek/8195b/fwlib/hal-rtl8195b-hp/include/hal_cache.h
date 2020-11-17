/**************************************************************************//**
 * @file     hal_cache.h
 * @brief    The HAL API implementation for the Cache control.
 * @version  V1.00
 * @date     2017-02-02
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2017 Realtek Corporation. All rights reserved.
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
 *
 ******************************************************************************/

#ifndef _HAL_CACHE_H_
#define _HAL_CACHE_H_
#include "cmsis.h"

#if defined(HAL_CACHE_ASSERT)
#include <assert.h>
#endif
 
#ifdef  __cplusplus
extern "C"
{
#endif

/** 
* @addtogroup hs_hal_cache Cache
* @{
*/

extern const hal_cache_func_stubs_t hal_cache_stubs;

/**
  \brief   Enable I-Cache
  \details Turns on I-Cache
  */
__STATIC_INLINE void icache_enable (void)
{
    hal_cache_stubs.icache_enable ();
}


/**
  \brief   Disable I-Cache
  \details Turns off I-Cache
  */
__STATIC_INLINE void icache_disable (void)
{
    hal_cache_stubs.icache_disable ();
}


/**
  \brief   Invalidate I-Cache
  \details Invalidates I-Cache
  */
__STATIC_INLINE void icache_invalidate (void)
{
    hal_cache_stubs.icache_invalidate ();
}


/**
  \brief   Enable D-Cache
  \details Turns on D-Cache
  */
__STATIC_INLINE void dcache_enable (void)
{
    hal_cache_stubs.dcache_enable ();
}


/**
  \brief   Disable D-Cache
  \details Turns off D-Cache
  */
__STATIC_INLINE void dcache_disable (void)
{
    hal_cache_stubs.dcache_disable ();
}


/**
  \brief   Invalidate D-Cache
  \details Invalidates D-Cache
  */
__STATIC_INLINE void dcache_invalidate (void)
{
    hal_cache_stubs.dcache_invalidate ();
}


/**
  \brief   Clean D-Cache
  \details Cleans D-Cache
  */
__STATIC_INLINE void dcache_clean (void)
{
    hal_cache_stubs.dcache_clean ();
}


/**
  \brief   Clean & Invalidate D-Cache
  \details Cleans and Invalidates D-Cache
  */
__STATIC_INLINE void dcache_clean_invalidate (void)
{
    hal_cache_stubs.dcache_clean_invalidate ();
}


/**
  \brief   D-Cache Invalidate by address
  \details Invalidates D-Cache for the given address
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void dcache_invalidate_by_addr (uint32_t *addr, int32_t dsize)
{
#if defined(HAL_CACHE_ASSERT)	
    assert(((uint32_t)addr&0x1f)==0);
    assert((dsize&0x1f)==0);
#endif		
    hal_cache_stubs.dcache_invalidate_by_addr (addr, dsize);
}


/**
  \brief   D-Cache Clean by address
  \details Cleans D-Cache for the given address
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void dcache_clean_by_addr (uint32_t *addr, int32_t dsize)
{
#if defined(HAL_CACHE_ASSERT)	
    assert(((uint32_t)addr&0x1f)==0);
    assert((dsize&0x1f)==0);
#endif		
    hal_cache_stubs.dcache_clean_by_addr (addr, dsize);
}


/**
  \brief   D-Cache Clean and Invalidate by address
  \details Cleans and invalidates D_Cache for the given address
  \param[in]   addr    address (aligned to 32-byte boundary)
  \param[in]   dsize   size of memory block (in number of bytes)
*/
__STATIC_INLINE void dcache_clean_invalidate_by_addr (uint32_t *addr, int32_t dsize)
{
#if defined(HAL_CACHE_ASSERT)	
    assert(((uint32_t)addr&0x1f)==0);
    assert((dsize&0x1f)==0);
#endif	
    hal_cache_stubs.dcache_clean_invalidate_by_addr (addr, dsize);
}

/** @} */ /* End of group hs_hal_cache */

#ifdef  __cplusplus
}
#endif


#endif  // end of "#define _HAL_CACHE_H_"

