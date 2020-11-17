/**************************************************************************//**
 * @file     consol_cmds.c
 * @brief    Some commands implementation for the shell command. It provides
 *           some basic memory write and dump commands.
 * @version  V1.00
 * @date     2016-05-30
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
#include <arm_cmse.h>   /* Use CMSE intrinsics */
#include "cmsis.h"
#include "shell.h"
#include "diag.h"
#include "utility.h"
#include <string.h>
#include <stdlib.h>

//extern unsigned long strtoul (const char *nptr, char **endptr, int base);

s32 cmd_dump_byte(u32 argc, u8 *argv[]);
s32 cmd_dump_helfword(u32 argc, u8 *argv[]);
s32 cmd_dump_word(u32 argc, u8 *argv[]);
s32 cmd_write_byte(u32 argc, u8 *argv[]);
s32 cmd_write_word(u32 argc, u8 *argv[]);

s32 cmd_dump_byte(u32 argc, u8 *argv[])
{
    u32 src;
    u32 len;

    if(argc<1) {    
        dbg_printf ("Wrong argument number!\r\n");
        return FALSE;
    }
    
    src = strtoul((const char*)(argv[0]), (char **)NULL, 16);       

    if(!argv[1]) {
        len = 16;
    } else {
        len = strtoul((const char*)(argv[1]), (char **)NULL, 10);
    }

    dump_bytes((u8 *)src,(u8)len);

    return _TRUE ;
}

s32 cmd_dump_helfword(u32 argc, u8  *argv[])
{
    u32 src;
    u32 len;
    u32 i;

    if(argc<1) {
        dbg_printf ("Wrong argument number!\r\n");
        return _FALSE;
    }
    
    if(argv[0]) {
        src= strtoul((const char*)(argv[0]), (char **)NULL, 16);
    } else {   
        dbg_printf("Wrong argument number!\r\n");
        return _FALSE;      
    }
                
    if(!argv[1]) {
        len = 1;
    } else {
        len = strtoul((const char*)(argv[1]), (char **)NULL, 10);
    }
    
    while ( (src) & 0x01) {
        src++;
    }

    for(i = 0; i < len; i+=4, src+=16) {   
        dbg_printf("%08X:  %04X    %04X    %04X    %04X    %04X    %04X    %04X    %04X\r\n",
        src, *(u16 *)(src), *(u16 *)(src+2), 
        *(u16 *)(src+4), *(u16 *)(src+6),
        *(u16 *)(src+8), *(u16 *)(src+10),
        *(u16 *)(src+12), *(u16 *)(src+14));
    }
    return _TRUE;

}

s32 cmd_dump_word(u32 argc, u8  *argv[])
{
    u32 src;
    u32 len;
    u32 i;

    if(argc<1) {    
        dbg_printf("Wrong argument number!\r\n");
        return _FALSE;
    }
    
    if(argv[0]) {
        src= strtoul((const char*)(argv[0]), (char **)NULL, 16);
    } else {    
        dbg_printf("Wrong argument number!\r\n");
        return _FALSE;      
    }
                
    if(!argv[1]) {
        len = 1;
    } else {
        len = strtoul((const char*)(argv[1]), (char **)NULL, 10);
    }
    
    while ( (src) & 0x03) {
        src++;
    }

    dbg_printf ("\r\n");
    for(i = 0; i < len; i+=4, src+=16) {   
        dbg_printf("%08X:    %08X", src, *(u32 *)(src));
        dbg_printf("    %08X", *(u32 *)(src+4));
        dbg_printf("    %08X", *(u32 *)(src+8));
        dbg_printf("    %08X\r\n", *(u32 *)(src+12));
    }
    return _TRUE;
}

s32 cmd_write_byte(u32 argc, u8  *argv[])
{
    u32 src;
    u8 value,i;

    src = strtoul((const char*)(argv[0]), (char **)NULL, 16);       

    for(i=0;i<argc-1;i++,src++) {
        value= strtoul((const char*)(argv[i+1]), (char **)NULL, 16);    
        dbg_printf("0x%08X = 0x%02X\r\n", src, value);
        *(volatile u8 *)(src) = value;
    }

    return 0;
}

s32 cmd_write_word(u32 argc, u8  *argv[])
{
    u32 src;
    u32 value,i;
    
    src = strtoul((const char*)(argv[0]), (char **)NULL, 16);       
    while ( (src) & 0x03) {
        src++;
    }

    for(i = 0; i < (argc - 1); i++,src+=4) {
        value= strtoul((const char*)(argv[i+1]), (char **)NULL, 16);
        dbg_printf("0x%08X = 0x%08X\r\n", src, value);
        *(volatile u32 *)(src) = value;
    }
    
    return 0;
}

#if !defined(CONFIG_BUILD_BOOT)

SECTION_NS_ENTRY_FUNC
s32 NS_ENTRY cmd_dump_byte_s(u32 argc, u8 *argv[])
{
    return cmd_dump_byte(argc, argv);
}

SECTION_NS_ENTRY_FUNC
s32 NS_ENTRY cmd_dump_helfword_s(u32 argc, u8 *argv[])
{
    return cmd_dump_helfword(argc, argv);
}

SECTION_NS_ENTRY_FUNC
s32 NS_ENTRY cmd_dump_word_s(u32 argc, u8 *argv[])
{
    return cmd_dump_word(argc, argv);
}

SECTION_NS_ENTRY_FUNC
s32 NS_ENTRY cmd_write_byte_s(u32 argc, u8 *argv[])
{
    return cmd_write_byte(argc, argv);
}

SECTION_NS_ENTRY_FUNC
s32 NS_ENTRY cmd_write_word_s(u32 argc, u8 *argv[])
{
    return cmd_write_word(argc, argv);
}
#endif  //#if !defined(CONFIG_BUILD_BOOT)
