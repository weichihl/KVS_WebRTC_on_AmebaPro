/**************************************************************************//**
* @file        efuse_logical_api.c
* @brief       This file implements the Efuse Mbed HAL API functions.
*
* @version     V1.00
* @date        2019-01-15
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
#include "hal_efuse_nsc.h"
#include "hal.h"
#include "memory.h"
#include "efuse_boot_cfg.h"

#if CONFIG_EFUSE_EN

//#define EFUSE_LOGICAL_SIM
#define EFUSE_LS

#define EFUSE_LOGICAL_MAP_SIZE			512
#define EFUSE_LOGICAL_MAP_HW_SIZE		0x100
#define EFUSE_LOGICAL_SBLOCK_OFFSET		0x19

#define EFUSE_CTRL_SETTING				0x37F00000
#define LDO_OUT_DEFAULT_VOLT			7

#ifdef EFUSE_LOGICAL_SIM
u8 efuse_sim_map[256];
#endif
int efuse_logical_read(u16 laddr, u16 size, u8 *pbuf)
{
    u16 phy_addr = 0;
    u8 offset, wden;
    u8 header, extheader, data;
    u16 i;
    uint32_t ret;

    if(!pbuf)
        return -1;

    memset(pbuf, 0xFF, size);
    /*Logical map size 512*/
    /*Logical map region on physical efuse: 0x0 ~ 0x99*/
    while (phy_addr < EFUSE_LOGICAL_MAP_HW_SIZE) {
         /*First two bytes are reserved for physical*/
        if(phy_addr == 0 || phy_addr == 1)
        {
            phy_addr++;
            continue;
        }
#ifdef EFUSE_LOGICAL_SIM
        static int map_inited = 0;
        if(!map_inited){
            map_inited = 1;
			for(i=0;i<EFUSE_LOGICAL_MAP_HW_SIZE;i++){
			#ifdef EFUSE_LS
				hal_icc_ls_efuse_read(i, &efuse_sim_map[i]);
			#else
                hal_efuse_read(EFUSE_CTRL_SETTING, i, &efuse_sim_map[i], LDO_OUT_DEFAULT_VOLT);
			#endif
			}
        }
        ret = _TRUE;
        header = efuse_sim_map[phy_addr++];
#else
	#ifdef EFUSE_LS
		ret = hal_icc_ls_efuse_read(phy_addr++, &header);
		if(ret != HAL_OK)
            return -1;
	#else
        ret = hal_efuse_read(EFUSE_CTRL_SETTING, phy_addr++, &header, LDO_OUT_DEFAULT_VOLT);
		if(ret != _TRUE)
            return -1;
	#endif
#endif
        if (header == 0xFF) {/* not write */
            break;
        }

        /* Check PG header for section num. */
        if ((header & 0x1F ) == 0x0F) {//extended header		
            offset = (header & 0xE0) >> 5;
#ifdef EFUSE_LOGICAL_SIM
            ret = _TRUE;
            extheader = efuse_sim_map[phy_addr++];
#else
		#ifdef EFUSE_LS
			ret = hal_icc_ls_efuse_read(phy_addr++, &extheader);
			if(ret != HAL_OK)
				return -1;
		#else
            ret = hal_efuse_read(EFUSE_CTRL_SETTING, phy_addr++, &extheader, LDO_OUT_DEFAULT_VOLT);
			if(ret != _TRUE)
                return -1;
		#endif
#endif
            if (((extheader & 0x0F) == 0x0F)) {/* not written */
                continue;
            }
            offset |= ((extheader & 0xF0) >> 1);
            wden = (extheader & 0x0F);
        } else {
            offset = ((header >> 4) & 0x0F);
            wden = (header & 0x0F);
        }

        /*One section has 8 bytes data, logical map has 512/8 = 64 sections*/
        if (offset < (EFUSE_LOGICAL_MAP_SIZE >> 3)) {
            u16 addr = 0;
            /* Get word enable value from PG header */
            addr = offset * 8;
            /*Each section has 4 words data*/
            for (i = 0; i < 4; i++) {
                /* Check word enable condition in the section */
                if (!(wden & (0x01<<i))) {
#ifdef EFUSE_LOGICAL_SIM
                    ret = _TRUE;
                    data = efuse_sim_map[phy_addr++];
#else
				#ifdef EFUSE_LS
					ret = hal_icc_ls_efuse_read(phy_addr++, &data);
					if(ret != HAL_OK)
                        return -1;
				#else
                    ret = hal_efuse_read(EFUSE_CTRL_SETTING, phy_addr++, &data, LDO_OUT_DEFAULT_VOLT);
					if(ret != _TRUE)
                        return -1;
				#endif
#endif
                    if(addr >= laddr && addr < (laddr+size))
                        pbuf[addr-laddr] = data;
#ifdef EFUSE_LOGICAL_SIM
                    ret = _TRUE;
                    data = efuse_sim_map[phy_addr++];
#else
				#ifdef EFUSE_LS
					ret = hal_icc_ls_efuse_read(phy_addr++, &data);
					 if(ret != HAL_OK)
                        return -1;
				#else
                    ret = hal_efuse_read(EFUSE_CTRL_SETTING, phy_addr++, &data, LDO_OUT_DEFAULT_VOLT);
					 if(ret != _TRUE)
                        return -1;
				#endif
#endif
                    if((addr+1) >= laddr && (addr+1) < (laddr+size))
                        pbuf[addr+1-laddr] = data;
                }
                addr += 2;
            }
        } else {
            u8 word_cnts = 0;
            if(!(wden & BIT(0)))	word_cnts++; // 0 : write enable
            if(!(wden & BIT(1)))	word_cnts++;
            if(!(wden & BIT(2)))	word_cnts++;
            if(!(wden & BIT(3)))	word_cnts++;
            phy_addr += word_cnts * 2; //word
        }
    }

    /*return used bytes*/
    return phy_addr-1;
}

static int efuse_pg_packet(u8 offset , u8 wden, u8 *data)
{
    u16 idx = 2;//the first two addresses are reserved
    u8 temp0, temp1, WordEn;//, Addr;
    u8 ret;
    u8 Len = 0;
    u8 word_idx;

    /* WordEnable bit=0 means write this bit */
    if ((wden&0xF) == 0xF){
        return -1;
    }

    if(offset == 0) {
        if(!(wden & BIT(0))){
            dbg_printf("\r\nCan't program Word0 for Offset 0\r\n");
            return -1;
        }
    }
    //count the physical written num of word
    while(idx < EFUSE_LOGICAL_MAP_HW_SIZE) {
#ifdef EFUSE_LOGICAL_SIM
        ret = _TRUE;
        temp0 = efuse_sim_map[idx];
#else
	#ifdef EFUSE_LS
		ret = hal_icc_ls_efuse_read(idx, &temp0);
		if(ret != HAL_OK)
            return -1;
	#else
        ret = hal_efuse_read(EFUSE_CTRL_SETTING, idx, &temp0, LDO_OUT_DEFAULT_VOLT);
        if(ret != _TRUE)
            return -1;
	#endif
#endif
        if (temp0 != 0xff) {//used

            if((temp0&0x0f) == 0xf){//ext header

                idx++;
#ifdef EFUSE_LOGICAL_SIM
                ret = _TRUE;
                temp1 = efuse_sim_map[idx];
#else
			#ifdef EFUSE_LS
				ret = hal_icc_ls_efuse_read(idx, &temp1);
				if(ret != HAL_OK)
                    return -1;
			#else
                ret = hal_efuse_read(EFUSE_CTRL_SETTING, idx, &temp1, LDO_OUT_DEFAULT_VOLT);
                if(ret != _TRUE)
                    return -1;
			#endif
#endif
                //Addr = (((temp1&0xf0)|((temp0)>>4))>>1);//logical addr
                WordEn = ((~temp1)&0x0f);//~ write enbale

                // bit=0: word not write
                // bit=1: word have write
                while(WordEn!=0){
                    if (WordEn & BIT0) {
                        idx = idx + 2; //word have write
                    }
                    WordEn = WordEn>>1;
                }
            } else {//normal header
                WordEn = ((~temp0)&0x0f);
                while(WordEn!=0){
                    if (WordEn & BIT0) {
                        idx = idx + 2;
                    }
                    WordEn = WordEn>>1;
                }
            }
        } else {//find address not written
            break;
        }
        idx++;
    }
    //CODE WORD
    wden = wden & 0xf;

    if((wden & BIT(0)) == 0)	Len = Len + 2; // 0 : write enable
    if((wden & BIT(1)) == 0)	Len = Len + 2;
    if((wden & BIT(2)) == 0)	Len = Len + 2;
    if((wden & BIT(3)) == 0)	Len = Len + 2;


    /*Efuse could PG to 0x99 at most*/
    if ((idx + Len) < (EFUSE_LOGICAL_MAP_HW_SIZE)) {
        if(offset >= 0xF){//ext header
#ifdef EFUSE_LOGICAL_SIM
            ret = _TRUE;
            efuse_sim_map[idx] = (((offset<<5)|0x0f));
#else
		#ifdef EFUSE_LS
			ret = hal_icc_ls_efuse_write(idx, (((offset<<5)|0x0f)));
			if(ret != HAL_OK)
				return -1;
		#else
            ret = hal_efuse_write(EFUSE_CTRL_SETTING, idx, (((offset<<5)|0x0f)), LDO_OUT_DEFAULT_VOLT);//addr[2:0]
            if (ret != _TRUE)
                return -1;
		#endif
#endif
            idx++;
#ifdef EFUSE_LOGICAL_SIM
            ret = _TRUE;
            efuse_sim_map[idx] = (((offset<<1)&0xf0)|wden);
#else
		#ifdef EFUSE_LS
			ret = hal_icc_ls_efuse_write(idx, (((offset<<1)&0xf0)|wden));
			if (ret != HAL_OK)
                return -1;
		#else
            ret = hal_efuse_write(EFUSE_CTRL_SETTING, idx, (((offset<<1)&0xf0)|wden), LDO_OUT_DEFAULT_VOLT);//addr[6:3]
            if (ret != _TRUE)
                return -1;
		#endif
#endif
            idx++;
        }else{
#ifdef EFUSE_LOGICAL_SIM
            ret = _TRUE;
            efuse_sim_map[idx] = (((offset<<4)&0xf0)|wden);
#else
		#ifdef EFUSE_LS
			ret = hal_icc_ls_efuse_write(idx, (((offset<<4)&0xf0)|wden));
			if (ret != HAL_OK)
                return -1;
		#else
            ret = hal_efuse_write(EFUSE_CTRL_SETTING, idx, (((offset<<4)&0xf0)|wden), LDO_OUT_DEFAULT_VOLT);
            if (ret != _TRUE)
                return -1;
		#endif
#endif
            idx++;
        }
        for (word_idx = 0; word_idx < 4; word_idx ++) {
            if ((wden & BIT(word_idx)) == 0) {
#ifdef EFUSE_LOGICAL_SIM
                ret = _TRUE;
                efuse_sim_map[idx] = *(data+word_idx*2);
#else
			#ifdef EFUSE_LS
				ret = hal_icc_ls_efuse_write(idx, *(data+word_idx*2));
				if (ret != HAL_OK)
                    return -1;
			#else
                ret = hal_efuse_write(EFUSE_CTRL_SETTING, idx, *(data+word_idx*2), LDO_OUT_DEFAULT_VOLT);
                if (ret != _TRUE)
                    return -1;
			#endif
#endif
                idx++;
#ifdef EFUSE_LOGICAL_SIM
                ret = _TRUE;
                efuse_sim_map[idx] = *(data+word_idx*2+1);
#else
			#ifdef EFUSE_LS
				ret = hal_icc_ls_efuse_write(idx, *(data+word_idx*2+1));
				if (ret != HAL_OK)
                    return -1;
			#else
                ret = hal_efuse_write(EFUSE_CTRL_SETTING, idx,  *(data+word_idx*2+1), LDO_OUT_DEFAULT_VOLT);
                if (ret != _TRUE)
                    return -1;
			#endif
#endif
                idx++;
            }
        }
    } else {
        dbg_printf("EFUSE PG No Enough Space!\n");
        return -1;
    }
    return 0;
}

int efuse_logical_write(u16 addr, u16 cnts, u8 *data)
{
    u8	offset, word_en;
    u8	map[EFUSE_LOGICAL_MAP_SIZE];
    u16	mapLen = EFUSE_LOGICAL_MAP_SIZE;
    u8	newdata[8];
    s32	i, idx; //j, ;
    int	ret = 0, used_bytes;

    if ((addr + cnts) > mapLen)
        return -1;

    used_bytes = efuse_logical_read(0, mapLen, map);
    if (used_bytes < 0)
        return -1;

    offset = (addr >> 3);
    word_en = 0xF;
    memset(newdata, 0xFF, 8);
    i = addr & 0x7;	// index of one package
    idx = 0;	// data index

    if (i & 0x1) {
        // odd start
        if (data[idx] != map[addr+idx]) {
            word_en &= ~(BIT(i >> 1));
            newdata[i-1] = map[addr+idx-1];
            newdata[i] = data[idx];
        }
        i++;
        idx++;
    }
    do {
        for (; i < 8; i += 2)
        {
            if (cnts == idx) break;
            if ((cnts - idx) == 1) {
                if (data[idx] != map[addr+idx]) {
                    word_en &= ~(BIT(i >> 1));
                    newdata[i] = data[idx];
                    newdata[i+1] = map[addr+idx+1];
                }
                idx++;
                break;
            } else {
                if ((data[idx] != map[addr+idx]) ||
                    (data[idx+1] != map[addr+idx+1]))
                {
                    word_en &= ~(BIT(i >> 1));
                    newdata[i] = data[idx];
                    newdata[i+1] = data[idx + 1];
                }
                idx += 2;
            }
            if (idx == cnts) break;
        }

        if (word_en != 0xF) {
            ret = efuse_pg_packet(offset, word_en, newdata);
            /*
            dbg_printf("offset=%x \n",offset);
            dbg_printf("word_en=%x \n",word_en);

            for(i=0;i<8;i++)
            {
            dbg_printf("data=%x \t",newdata[i]);
            }
            */
            if (ret<0) return ret;
        }

        if (idx == cnts) break;

        offset++;
        i = 0;
        word_en = 0xF;
        memset(newdata, 0xFF, 8);
    } while (1);
#ifdef EFUSE_LOGICAL_SIM
    dbg_printf("\n\r");
    for (i = 0; i < EFUSE_LOGICAL_MAP_HW_SIZE; i += 16)
    {
        int j;
    	dbg_printf("0x%03x\t", i);
    	for (j=0; j<8; j++) {
    		dbg_printf("%02X ", efuse_sim_map[i+j]);
    	}
    	dbg_printf("\t");
    	for (; j<16; j++) {
    		dbg_printf("%02X ", efuse_sim_map[i+j]);
    	}
    	dbg_printf("\n\r");
    }
#endif
    return 0;
}

int efuse_lp_logical_read(u16 laddr, u16 size, u8 *pbuf)
{
	return(efuse_logical_read(laddr, size, pbuf));
}

int efuse_lp_logical_write(u16 addr, u16 cnts, u8 *data)
{
	return(efuse_logical_write(addr, cnts, data));
}
#endif
