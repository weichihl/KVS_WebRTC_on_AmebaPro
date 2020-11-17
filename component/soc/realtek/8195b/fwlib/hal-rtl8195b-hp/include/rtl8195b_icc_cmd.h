/**************************************************************************//**
 * @file     rtl8195b_icc_cmd.h
 * @brief    The ICC command type definition for Rtl8195b platform.
 * @version  V1.00
 * @date     2016-10-28
 *
 * @note
 *
 ******************************************************************************
 *
 * Copyright(c) 2007 - 2016 Realtek Corporation. All rights reserved.
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

#ifndef _8195B_ICC_CMD_H_
#define _8195B_ICC_CMD_H_

/**
 * @addtogroup hs_hal_icc ICC
 * @{
 */

#ifdef __cplusplus
extern "C" {
#endif

//1 Make sure both HP and LP use the same ICC command type definition
/**
  \brief  Define the ICC commands those are used in the communication between HS platform and LS platform.
*/
enum icc_commands {
    ICC_SetH2L_HQ           = 0xE0,     ///< setup the HS to LS message Hi-queue buffer and size, HS -> LS
    ICC_SetH2L_LQ           = 0xE1,     ///< setup the HS to LS message Lo-queue buffer and size, HS -> LS
    ICC_SetL2H_HQ           = 0xE2,     ///< setup the LS to HS message Hi-queue buffer and size, HS -> LS
    ICC_SetL2H_LQ           = 0xE3,     ///< setup the LS to HS message Lo-queue buffer and size, HS -> LS
    ICC_Reset_Q             = 0xE4,     ///< reset a message queue, HS <-> LS
    ICC_LS_Img_Rdy          = 0xE5,     ///< indication of LS platform RAM code image is ready, LS -> HS

    ICC_ReadMem_Addr        = 0xE6,     ///< LS memory/register read command, HS -> LS
    ICC_ReadMem_Data        = 0xE7,     ///< the result(data return) of the LS memory/register read command, LS -> HS
    ICC_WriteMem_Addr       = 0xE8,     ///< LS memory/register write: write address, HS -> LS
    ICC_WriteMem_Data       = 0xE9,     ///< LS memory/register write: write data, HS -> LS

    ICC_MsgQ_Ind            = 0xEA,     ///< new ICC message: the message type and message queue
    ICC_MsgQ_Ack            = 0xEB,     ///< acknowledge for a received ICC message

    ICC_Ping                = 0xEC,     ///< ping command

    ICC_Ack                 = 0xFE      ///< acknowledge for a received ICC command
};

/**
  \brief  Define the ICC commands general format
*/
typedef struct icc_cmd_general_s {
    union {
        uint32_t word0;
        struct {
            uint32_t para0:24;
            uint32_t cmd:8;
        } word0_b;
    };

    union {
        uint32_t word1;
        uint32_t para1;
    };
} icc_cmd_general_t, *picc_cmd_general_t;

/**
  \brief  The ICC commands for queue setup
*/
typedef struct icc_cmd_set_q_s {
    union {
        uint32_t hlrw0;
        struct {
            uint32_t q_size:24;
            uint32_t cmd:8;
        } hlrw0_b;
    };

    uint32_t start_addr;
} icc_cmd_set_q_t, *picc_cmd_set_q_t;


/**
  \brief  The queue reset ICC command
*/
typedef struct icc_cmd_q_rst_s {
    union {
        uint32_t word0;
        struct {
            uint32_t q_id:24;
            uint32_t cmd:8;
        } word0_b;
    };

    uint32_t word1;
} icc_cmd_q_rst_t, *picc_cmd_q_rst_t;

/**
  \brief  The ICC commands for LS Image load notification
*/
typedef struct icc_cmd_ls_img_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t para0:24;
            uint32_t cmd:8;
        } cmd_b;
    };

    uint32_t start_addr;
} icc_cmd_ls_img_t, *picc_cmd_ls_img_t;

/**
  \brief  The ICC commands for LS mem/reg read address
*/
typedef struct icc_cmd_mem_rd_addr_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t rd_cnt:24;
            uint32_t cmd:8;
        } cmd_b;
    };

    uint32_t addr;
} icc_cmd_mem_rd_addr_t, *picc_cmd_mem_rd_addr_t;

/**
  \brief  The ICC commands for LS mem/reg read data
*/
typedef struct icc_cmd_mem_rd_data_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t wd_offset:24;
            uint32_t cmd:8;
        } cmd_b;
    };

    uint32_t data;
} icc_cmd_mem_rd_data_t, *picc_cmd_mem_rd_data_t;

/**
  \brief  The ICC commands for LS mem/reg write address
*/
typedef struct icc_cmd_mem_wr_addr_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t wr_cnt:24;
            uint32_t cmd:8;
        } cmd_b;
    };

    uint32_t addr;
} icc_cmd_mem_wr_addr_t, *picc_cmd_mem_wr_addr_t;

/**
  \brief  The ICC commands for LS mem/reg write data
*/
typedef struct icc_cmd_mem_wr_data_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t wd_offset:24;
            uint32_t cmd:8;
        } cmd_b;
    };

    uint32_t data;
} icc_cmd_mem_wr_data_t, *picc_cmd_mem_wr_data_t;

/**
  \brief  The ICC commands for user message queue indication
*/
typedef struct icc_cmd_msg_q_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t msg_q:8;
            uint32_t msg_op:8;
            uint32_t msg_type:8;
            uint32_t cmd:8;
        } cmd_b;
    };

    uint32_t msg_len;
} icc_cmd_msg_q_t, *picc_cmd_msg_q_t;

typedef struct icc_msg_q_ind_cmd_s{
    union {
        uint32_t cmd_w;
        struct {
            uint32_t msg_q:8;
            uint32_t msg_op:8;
            uint32_t msg_type:8;
            uint32_t cmd:8;
        } cmd_b;
    };
} icc_msg_q_ind_cmd_t, *picc_msg_q_ind_cmd_t;

/**
  \brief  The ICC commands for user message queue acknowledge
*/
typedef struct icc_cmd_msg_q_ack_s {
    union {
        uint32_t cmd_w;
        struct {
            uint32_t msg_q:8;
            uint32_t msg_op:8;
            uint32_t msg_type:8;
            uint32_t cmd:8;
        } cmd_b;
    };

    int32_t ret;   // result
} icc_cmd_msg_q_ack_t, *picc_cmd_msg_q_ack_t;

#ifdef __cplusplus
}
#endif

/** @} */ /* End of group hs_hal_icc */

#endif

