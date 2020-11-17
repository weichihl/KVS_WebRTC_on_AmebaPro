/**************************************************************************//**
 * @file     rtl8195blp_ramstart.h
 * @brief    The data type definition for RAM code entry functions.
 * @version  V1.00
 * @date     2016-06-30
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
 *
 ******************************************************************************/
#ifndef _RTL8195BLP_RAMSTART_H_
#define _RTL8195BLP_RAMSTART_H_

#ifdef  __cplusplus
 extern "C"
 {
#endif

enum fast_boot_ctrl_e {
    FastBootFlow0 = 0,  // default, do nothing and jump to RAM code dirctly
    FastBootFlow1 = 1,  // initial G-Timer, enable BG, LDO & HS Syson then jump to RAM code
    FastBootFlow2 = 2,  // initial XTal, HS fully initialed and then jump to RAM code
    FastBootFlow3 = 3   // do all initialization, just like normal booting
};

/**
  \brief Wakeup options for boot ROM control.
*/
typedef union {
  uint32_t w;                         /*!< all flags in a word                                  */

  struct {
    uint32_t ram_start_idx  : 3;            /*!< [0..2] the selection of RAM code function to jump */
    uint32_t boot_ctrl      : 3;            /*!< [3..5] the boot flow control */
    uint32_t reserved       : 25;           /*!< [6..30] reserved */
    uint32_t fast_boot      : 1;            /*!< [31..31] is fast booting, write by ROM boot code */
  } b;                                        /*!< bit fields for flags */
} fast_boot_option_t, *pfast_boot_option_t;

typedef struct _RAM_START_FUNCTION_ {
    void (*RamStartFun) (void);
}RAM_START_FUNCTION, *PRAM_START_FUNCTION;

typedef void (*ram_start_func_t) (void);

typedef struct _RAM_FUNCTION_START_TABLE_ {
    char *Signature;
    void (*RamStartFun) (void);
    void (*RamWakeupFun0) (void);
    fast_boot_option_t boot_option;
    void (*RamWakeupFun1) (void);
    void (*RamWakeupFun2) (void);
    void (*RamWakeupFun3) (void);
}RAM_FUNCTION_START_TABLE, *PRAM_FUNCTION_START_TABLE;


#ifdef  __cplusplus
}
#endif

#endif  // end of "#define _RTL8195BLP_RAMSTART_H_"

