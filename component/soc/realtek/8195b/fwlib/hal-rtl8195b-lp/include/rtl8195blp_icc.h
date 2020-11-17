/**************************************************************************//**
 * @file     rtl8195blp_icc.h
 * @brief    Defines macro and data type for ICC HAL.
 * @version  1.0
 * @date     25. November 2016
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

#ifndef RTL8195BLP_ICC_H
#define RTL8195BLP_ICC_H

#ifdef __cplusplus
extern "C" {
#endif

/** 
 * @addtogroup ls_hal_icc ICC
 * @ingroup 8195bl_hal
 * @{
 * @brief The ICC(Inter CPU Communication) HAL on LS platform.
 *        The ICC implements a mechanism for communication between the HS platform and the LS platform.
 */

#include "rtl8195blp_icc_h_type.h"
#include "rtl8195blp_icc_l_type.h"
#include "rtl8195b_icc_cmd.h"

/// Defines the timeout period for the waiting of the ACK of a ICC command.
#define ICC_CMD_DEFAULT_TIMEOUT_US          (1000000)

/// The signature in the header of a ICC message
#define ICC_MSG_HDR_SIGN                    (0x8195)

typedef struct hal_icc_adapter_s hal_icc_adapter_t, *phal_icc_adapter_t;
    
/**
  \brief  The call back function type for a ICC queue reading/writeing is done.
*/
typedef void (*icc_callback_t)(void *callback_para, uint32_t tred_len);

/**
  \brief  The call back function type for the application level message
          queue data ready indication.
*/
typedef void (*icc_msg_q_ind_t)(void *adp, icc_cmd_msg_q_t *icc_cmd);

/**
  \brief  The function type for the OS task yield.
*/
typedef void (*icc_task_yield)(void);

/**
  \brief  The call back function type for a new L2H command indication.
*/
typedef void (*icc_cmd_ind)(void *para, uint32_t cmd_word0, uint32_t cmd_word1);

/**
  \brief  The call back function type for the indication of L2H message
          queue is updated.
*/
typedef uint32_t (*icc_q_ind)(hal_icc_adapter_t *para, uint32_t q_id);


/**
  \brief  The call back function type for the indication of H2L message
          queue is acknowledged.
*/
typedef void (*icc_q_ack)(hal_icc_adapter_t *para, uint32_t q_id);

/**
  \brief  The function type of ICC HAL command handler.
*/
typedef uint32_t (*icc_cmd_handler)(hal_icc_adapter_t *para, icc_cmd_general_t *cmd_word);

/**
  \brief  The data type to be used to pass arguments for message queue read/write request.
*/
typedef struct icc_q_rw_req_s {
    uint8_t *pbuf;              ///< the buffer to store data to be write to queue or data read from queue.
    uint32_t rw_len;            ///< the data length, in byte, to write to queue or to read from queue.
    uint32_t tred_len;          ///< the transfered data length, in byte.
    icc_callback_t callback;    ///< User callback function for the queue reading/writing is done.
    void *callback_para;        ///< the application data to be pass back with the callback function for the queue reading/writing is done.
} icc_q_rw_req_t, *picc_q_rw_req_t;

/**
  \brief  The data type of the pair of a ICC HAL command and its handler.
*/
typedef struct icc_cmd_entry_s {
    uint8_t cmd;                ///< the ICC command type
    icc_cmd_handler callback;   ///< the ICC command handler function
} icc_cmd_entry_t, *picc_cmd_entry_t;

/**
  \brief  The function type of a ICC user application command handler.
*/
typedef void (*icc_user_cmd_handler_t)(uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg);

/**
  \brief  The data type of a ICC user application command entry point.
          The entry point is a combination of a user ICC command and the handler of the ICC command.
*/
typedef struct icc_user_cmd_entry_s {
    uint8_t cmd;   ///< the ICC command type.
    icc_user_cmd_handler_t callback;  ///< the ICC command callback function.
    uint32_t cb_arg;   ///< the application data to be pass back with the ICC command callback function
} icc_user_cmd_entry_t, *picc_user_cmd_entry_t;

/*!< the ICC user message handler function type */
typedef int32_t (*icc_hal_msg_handler_t)(void *adp, uint32_t msg_op, uint32_t msg_size);

/**
  \brief  The data type of the pair of a ICC user application command and its handler.
*/
typedef struct icc_hal_msg_entry_s {
    uint8_t msg;   /*!< the ICC message type */
    icc_hal_msg_handler_t callback;  /*!< the ICC command callback function */
} icc_hal_msg_entry_t, *picc_hal_msg_entry_t;

/**
  \brief  The function type of the ICC user message handler.
*/
typedef int32_t (*icc_user_msg_handler_t)(uint32_t msg_op, uint32_t msg_size, uint32_t cb_arg);

/**
  \brief  The call back function type of the user message queue sending is done.
*/
typedef void (*icc_user_msg_tx_callback_t)(uint32_t cb_arg, int32_t result);

/**
  \brief  The function to copy data from/to message queue via GDMA.
*/
typedef hal_status_t (*icc_gdma_memcpy_t)(void *gdma_adp, void *pdest, void *psrc, uint32_t len);

/**
  \brief  The callback function to wake up ICC task to handle ICC IRQ button helf.
*/
typedef int32_t (*icc_task_up_t)(void *arg);

/**
  \brief  The callback function to get the mutex of the ICC HAL critical section protection.
*/
typedef void (*icc_enter_critical_t)(hal_icc_adapter_t *arg);

/**
  \brief  The callback function to release the mutex of the ICC HAL critical section protection.
*/
typedef void (*icc_exit_critical_t)(hal_icc_adapter_t *arg);

/**
  \brief  The callback function type for the ICC command queue pop and handle.
*/
typedef void (*icc_cmd_q_handler_t) (void *icc_adapter);

/**
  \brief  The function type of a ICC message RX indication callback function.
*/
typedef void (*icc_msg_rx_cb_t)(     uint8_t *pmsg_buf, uint32_t msg_size, uint32_t cb_arg);

/**
  \brief  The function type of the a ICC message TX done callback function.
*/
typedef void (*icc_msg_tx_cb_t)(     uint32_t cb_arg);

/**
  \brief  The data type of the pair of a ICC user application message and its handler.
*/
typedef struct icc_user_msg_entry_s {
    uint8_t msg;   ///< the ICC message type
    icc_user_msg_handler_t callback;  ///< the ICC command handler function
    uint32_t cb_arg;   ///< the application data will be pass back with the ICC command callback function
} icc_user_msg_entry_t, *picc_user_msg_entry_t;

/**
  \brief  The data type of the pair of a ICC message and its handler.
*/
typedef struct icc_msg_entry_s {
    uint8_t msg;                        ///< the ICC message type
    uint8_t frame;                      ///< the ICC message frame type
    uint8_t reserved[2];
    icc_msg_rx_cb_t callback;         ///< the ICC command handler function
    uint32_t cb_arg;                    ///< the application data will be pass back with the ICC command callback function
} icc_msg_entry_t, *picc_msg_entry_t;

/**
  \brief  The data type to be used to pass arguments for a user application message sending/receiving.
*/
typedef struct icc_msg_type_s {
    uint8_t msg_type;   ///< the user application message type
    uint8_t msg_op;     ///< the operland of the message type
    uint8_t msg_q;      ///< the message queue id to be used for this message sending
    uint8_t reserved;
    uint32_t msg_size;  ///< the length of data will following the message type to be send 
    uint8_t *msg_data;  ///< the data buffer of the message data
} icc_msg_type_t, *picc_msg_type_t;

/**
  \brief  The data structure of the header of an ICC message.
*/
typedef struct icc_msg_hdr_s {
    uint16_t sign;                  ///< signature, the value always is 0x8195
    uint8_t frame_type;             ///< the frame type of the message
    uint8_t msg_type;               ///< the message type
    uint16_t seq_num;               ///< the sequence number
    uint16_t msg_len;               ///< the length of message data
} icc_msg_hdr_t, *picc_msg_hdr_t;

/**
  \brief  The data type for a ICC message queue TX request submit
*/
typedef struct icc_msg_tx_req_s icc_msg_tx_req_t, *picc_msg_tx_req_t;
struct icc_msg_tx_req_s {
    uint8_t frame_type;             ///< the frame type of the message, frame type 0xE0 ~ 0xFF is reserved for lower level HAL
    uint8_t msg_type;               ///< the message type
    uint8_t q_id;                   ///< the message queue id to be used for this message sending
    uint8_t reserved1;
    uint16_t msg_len;               ///< the length of message data
    uint16_t reserved2;
    uint8_t *msg_data;              ///< the data buffer of the message data
    icc_msg_tx_cb_t pcallback;      ///< the callback function for the message transmission is done
    uint32_t callback_arg;          ///< the argument of the callback function
    icc_msg_tx_req_t *pnext;        ///< point to next message Q request
};

/**
  \brief  The data type for a ICC message queue RX request submit
*/
typedef struct icc_msg_rx_req_s icc_msg_rx_req_t, *picc_msg_rx_req_t;
struct icc_msg_rx_req_s {
    uint8_t q_id;                   ///< the message queue id to be used for this message sending
    uint8_t msg_type;               ///< the type of the received message
    uint8_t frame_type;             ///< the frame type of the received message
    uint8_t reserved1;
    uint16_t buf_size;              ///< the size of the buffer, in byte, the message length cannot over this size
    uint16_t tred_len;              ///< transferen data length in the message buffer
    uint8_t *msg_buf;               ///< the data buffer of the message data
    icc_msg_rx_req_t *pnext;    ///< point to next message Q request
};

/**
  \brief  The data type for the ICC entity HAL control ad management.
*/
struct hal_icc_adapter_s {
    union {
        volatile uint32_t flags;
        struct {
            uint32_t h2l_q_rdy:1;                       ///< indication of the H2L Queue ready
            uint32_t l2h_q_rdy:1;                       ///< indication of the L2H Queue ready
            volatile uint32_t l2h_cmd_busy:1;           ///< indication of the L2H command is busy
            volatile uint32_t msg_tx_w4_ack:1;          ///< the user message queue TX state: is waitting for peer acknowledge
            volatile uint32_t msghq_tx_w4_data_done:1;  ///< the user message Hi-queue TX state: waiting of queue data write done
            volatile uint32_t msglq_tx_w4_data_done:1;  ///< the user message Lo-queue TX state: waiting of queue data write done
            // B-Cut           
            volatile uint32_t msghq_tx_w4_ack:1;   ///< the user message queue TX state: is waitting for peer acknowledge
            volatile uint32_t msglq_tx_w4_ack:1;   ///< the user message queue TX state: is waitting for peer acknowledge
        } flags_b;
    };
    
    uint32_t critical_lv;       ///< to record ICC enter critical section level
    
    uint32_t h2l_hq_head_addr;  ///< the head address of H2L High-Q
    uint32_t h2l_hq_tail_addr;  ///< the tail address of H2L High-Q
    uint32_t h2l_hq_size;       ///< the buffer size of H2L High-Q
    uint32_t h2l_lq_head_addr;  ///< the head address of H2L Low-Q
    uint32_t h2l_lq_tail_addr;  ///< the tail address of H2L Low-Q
    uint32_t h2l_lq_size;       ///< the buffer size of H2L Low-Q
    uint32_t l2h_hq_head_addr;  ///< the head address of L2H High-Q
    uint32_t l2h_hq_tail_addr;  ///< the tail address of L2H High-Q
    uint32_t l2h_hq_size;       ///< the buffer size of L2H High-Q
    uint32_t l2h_lq_head_addr;  ///< the head address of L2H Low-Q
    uint32_t l2h_lq_tail_addr;  ///< the tail address of L2H Low-Q
    uint32_t l2h_lq_size;       ///< the buffer size of L2H Low-Q

    icc_q_rw_req_t l2h_hq_wr_req; ///< to store the writing request to the L2H_HQ, for interrupt mode writing
    icc_q_rw_req_t l2h_lq_wr_req; ///< to store the writing request to the L2H_LQ, for interrupt mode writing
    icc_q_rw_req_t h2l_hq_rd_req; ///< to store the reading request to the H2L_HQ, for interrupt mode reading
    icc_q_rw_req_t h2l_lq_rd_req; ///< to store the reading request to the H2L_LQ, for interrupt mode reading
    
    icc_task_yield task_yield;  /*!< the OS task yield function. The ICC HAL will call this function during
                                     a busy waitting, so the OS can do a force task switching to prevent other task 
                                     starvation. The user application is responsible to hook this function on. */
    icc_cmd_ind h2l_cmd_ind;        ///< callback function for a new H2L command indication
    void *h2l_cmd_ind_cb_para;      ///< the application data will be pass back with the callback function of new H2L command indication
    icc_q_ind h2l_msg_q_ind;        ///< callback function for the indication of H2L message queue is updated(H2L_Q write pointer is updated).
    void *h2l_msg_q_ind_cb_para;    ///< the application data will be pass back with the callback function of message queue is updated.
    icc_q_ack l2h_msg_q_ack;        ///< callback function for a L2H message queue is acknowledged(L2H_Q read pinter is updated).
    void *l2h_msg_q_ack_cb_para;    ///< the application data will be pass back with the callback function of message queue is updated.
    uint32_t mem_wr_addr;           ///< stores the address templorary for memory write command from HS
    uint32_t mem_wr_limit_addr;     ///< the limit address for memory write command from HS

    icc_cmd_entry_t const *phal_rom_cmd_tbl;        ///< the HAL ICC command table in ROM.
    icc_user_cmd_entry_t *phal_cmd_tbl;             ///< the HAL ICC command table in RAM, it is registable.
    uint32_t hal_cmd_tbl_size;                      ///< the ICC HAL command table(in RAM) size
    icc_user_cmd_entry_t *pcmd_tbl;                 ///< the user application ICC command register table
    uint32_t cmd_tbl_size;                          ///< the user application ICC command table size
    icc_msg_q_ind_t user_msg_q_ind;                 ///< the call-back function for user application message queue data ready 
    icc_user_msg_entry_t *phal_msg_tbl;             ///< the HAL ICC message register table (RAM)
    uint32_t hal_msg_tbl_size;                      ///< the ICC HAL message register table size
    icc_user_msg_entry_t *pmsg_tbl;                 ///< the user application ICC message register table
    uint32_t msg_tbl_size;                          ///< the user application ICC message register table size
    volatile uint32_t msghq_tx_result;              ///< the result of user application message high queue sending
    volatile uint32_t msglq_tx_result;              ///< the result of user application message low queue sending
    icc_user_msg_tx_callback_t user_msghq_txd_cb;   ///< the callback function of user message Hi-queue interrupt mode sending is done
    uint32_t user_msghq_txd_cb_arg;                 /*!< the application data will to be passed back with the callback
                                                         function of user message Hi-queue interrupt mode sending is done */
    icc_user_msg_tx_callback_t user_msglq_txd_cb;   ///< the callback function of user message Lo-queue interrupt mode sending is done
    uint32_t user_msglq_txd_cb_arg;                 /*!< the application data will to be passed back with the callback
                                                         function of user message Lo-queue interrupt mode sending is done */
    icc_user_cmd_handler_t ping_callback;           ///< the callback function for a ICC Ping command is received
    uint32_t ping_cb_arg;                           ///< the application data will to be passed back with the ICC Ping command callback function

    uint32_t cmd_timeout_us;     ///< the timeout period(in us) for waiting of ICC command sending acknowledge

    void *gdma_adp;                                 ///< GDMA adapter, the GDMA for memory copy from/to message queue
    icc_gdma_memcpy_t gdma_memcpy;                  ///< the function of GDMA mode memory copy
    volatile uint8_t dma_copy_busy;                 ///< the flag to indicates the GDMA mode memory copy is in progress.
    volatile uint32_t pending_isr;                  ///< ICC HAL pending interrupt status, it is got from register in the ISR
    icc_task_up_t task_up;                          ///< the callback function (to wake up the ICC task) to handle IRQ
    void *task_up_arg;                              ///< the argument(or semaphore) of the ICC wake up callback function
    icc_enter_critical_t enter_critical;            ///< the callback function to get the mutext for the ICC HAL protection
    icc_exit_critical_t exit_critical;              ///< the callback function to release the mutext for the ICC HAL protection
    uint8_t mutex_locked;                           ///< mutex level control
    uint8_t cmd_q_in;                               ///< ICC command queue push index
    uint8_t cmd_q_out;                              ///< ICC command queue pop index
    uint8_t cmd_q_size;                             ///< ICC command queue size (number of ICC command), each ICC command use 2 DW of space
    uint8_t cmd_q_sn;                               ///< ICC command toggle bit value, it should toggle for each incoming ICC command
    uint8_t msg_regtbl_sz;                          ///< ICC message register table size
    uint32_t *pcmd_q_buf;                           ///< ICC command queue buffer
    icc_cmd_q_handler_t cmd_q_handler;              ///< the callback function to pop and handle ICC command in the command queue

    icc_msg_entry_t *pmsg_regtbl;                   ///< the HAL ICC message register table (RAM)
    uint8_t msg_q_tx_state[2];                      ///< the state of message TX
    uint8_t msg_q_rx_state[2];                      ///< the state of message RX
    uint16_t msg_q_tx_sn[2];                        ///< the sequence number of message TX
    uint16_t msg_q_rx_sn[2];                        ///< the sequence number of message RX
    icc_msg_hdr_t msg_rx_hdr[2];                     ///< the buffer for message header RX
    icc_msg_tx_req_t *tx_q_h[2];                ///< the message TX queue head, this queue head will move forward for a new TX request is submitted
    icc_msg_tx_req_t *tx_q_t[2];                ///< the message TX queue tail, this queue tail will move forward for a TX request processing is done
    icc_msg_rx_req_t *rx_q_h[2];                ///< the message RX queue head, this queue head will move forward for a new RX request is submitted
    icc_msg_rx_req_t *rx_q_t[2];                ///< the message RX queue tail, this queue tail will move forward for a RX request processing is done
    icc_msg_rx_req_t *rx_done_q_h[2];                ///< the head of RX Req transfer done FIFO queue
    icc_msg_rx_req_t *rx_done_q_t[2];                ///< the tail of RX Req transfer done FIFO queue
    uint16_t tx_q_sn[2];                            ///< the message TX queue sequence number, it's increased by 1 for every message transmission
    uint16_t rx_q_sn[2];                            ///< the message RX queue sequence number, it's increased by 1 for a message is received
    icc_msg_tx_req_t *free_tx_req_h;             ///< the message queue TX/RX request pool head, this pool should be filled when ICC HAL initialization
    icc_msg_tx_req_t *free_tx_req_t;             ///< the message queue TX/RX request pool tail

    uint32_t reserved[2];
};

/**
  \brief  Define the ICC interrupt enable / disable / pending
*/
enum icc_toggle_interrupt {
    IccTgIntDisable       = 0,
    IccTgIntEnable        = 1,
    IccTgIntPending       = 1
};

/**
  \brief  Define the message queue ID
*/
enum icc_msg_qid_e {
    QID_H2L_HQ          = 0,
    QID_H2L_LQ          = 1,
    QID_L2H_HQ          = 2,
    QID_L2H_LQ          = 3
};

/**
  \brief  Defines the message queue name.
*/
enum icc_msg_queue_e {
    ICC_HQ          = 0,
    ICC_LQ          = 1,

    ICC_MAX_QID     = 1
};

/**
  \brief  Defines the ICC hardware semaphore ID.
*/
enum icc_sema_id_e {
    IccSema0            = 0,
    IccSema1            = 1,
    IccSema2            = 2,
    IccSema3            = 3,
    IccSema4            = 4,
    IccSema5            = 5,
    IccSema6            = 6,
    IccSema7            = 7,
    IccSema8            = 8,
    IccSema9            = 9,
    IccSema10           = 10,
    IccSema11           = 11,
    IccSema12           = 12,
    IccSema13           = 13,
    IccSema14           = 14,
    IccSema15           = 15,

    MaxIccSemaId        = 15
};
typedef uint32_t icc_sema_id_t;

/**
  \brief  Defines the ICC hardware semaphore owner.
*/
enum icc_sema_owner_e {
    IccSemaOwnerHS    = 2,  ///< this semaphore is owned by the HS platform
    IccSemaOwnerLS    = 1   ///< this semaphore is owned by the LS platform
};
typedef uint8_t icc_sema_owner_t;

/**
  \brief  Defines the ICC message TX state
*/
enum icc_msg_tx_state_e {
    ICC_TX_IDLE         = 0,        ///< idle state
    ICC_TX_DATA_STAGE   = 1,         ///< message data sending stage
    ICC_TX_W4_DONE      = 2         ///< message data sending stage
};
typedef uint8_t icc_msg_tx_state_t;

/**
  \brief  Defines the ICC message RX state
*/
enum icc_msg_rx_state_e {
    ICC_RX_IDLE         = 0,        ///< idle state
    ICC_RX_HDR_STAGE    = 1,        ///< wait for message header
    ICC_RX_DATA_STAGE   = 2,        ///< wait for message data transfer done

    ICC_RX_STATE_ERR    = 0x0E      ///< in error state
};
typedef uint8_t icc_msg_rx_state_t;

/* Defines the ICC registers are used for the implementation of the ICC LS to HS command */
/// HS to LS ICC command word0
#define H2L_CMD_WORD0                       (ICC_H->hlrw0)
/// HS to LS ICC command word1
#define H2L_CMD_WORD1                       (ICC_H->hlrw1)
/// HS to LS ICC command toggle bit
#define H2L_CMD_TG                          (ICC_H->hptg_b.h2ltg0)
/// HS to LS ICC command indication interrupt enable
#define H2L_CMD_IND_IE                      (ICC_L->hptgie_b.h2ltgie0)
/// HS to LS ICC command indication interrupt status
#define H2L_CMD_IND_IS                      (ICC_L->hptgis_b.h2ltgis0)
/// HS to LS ICC command indication interrupt status mask
#define H2L_CMD_IND_IS_MASK                 ((uint32_t)(1 << 16))
/// Toggle bit for HS to LS ICC command acknowledge
#define H2L_CMD_ACK_TG                      (ICC_H->lptg_b.l2htg3)
/// LS to HS ICC command word0
#define L2H_CMD_WORD0                       (ICC_H->hlrw2)
/// LS to HS ICC command word1
#define L2H_CMD_WORD1                       (ICC_H->hlrw3)
/// Toggle bit for LS to HS ICC command indication
#define L2H_CMD_TG                          (ICC_H->lptg_b.l2htg2)
/// LS to HS ICC command acknowledge interrupt enable
#define L2H_CMD_ACK_IE                      (ICC_L->hptgie_b.h2ltgie1)
/// LS to HS ICC command acknowledge interrupt status
#define L2H_CMD_ACK_IS                      (ICC_L->hptgis_b.h2ltgis1)
/// LS to HS ICC command acknowledge interrupt status mask
#define L2H_CMD_ACK_IS_MASK                 ((uint32_t)(1 << 17))

/// HS to LS message Hi-queue write pointer
#define H2L_HQ_WR_PTR                       (ICC_H->hwlr0)
/// HS to LS message Lo-queue write pointer
#define H2L_LQ_WR_PTR                       (ICC_H->hwlr1)
/// LS to HS message Hi-queue read pointer
#define L2H_HQ_RD_PTR                       (ICC_H->hwlr2)
/// LS to HS message Lo-queue read pointer
#define L2H_LQ_RD_PTR                       (ICC_H->hwlr3)

/// LS to HS message Hi-queue write pointer
#define L2H_HQ_WR_PTR                       (ICC_H->hrlw0)
/// LS to HS message Lo-queue write pointer
#define L2H_LQ_WR_PTR                       (ICC_H->hrlw1)
/// HS to LS message Hi-queue read pointer
#define H2L_HQ_RD_PTR                       (ICC_H->hrlw2)
/// HS to LS message Lo-queue read pointer
#define H2L_LQ_RD_PTR                       (ICC_H->hrlw3)

/// Toggle bit of the LS to HS Hi-queue write pointer update indication
#define L2H_HQ_IND_TG                       (ICC_H->lptg_b.lptg0)
/// Toggle bit of the LS to HS Lo-queue write pointer update indication
#define L2H_LQ_IND_TG                       (ICC_H->lptg_b.lptg1)
/// Toggle bit of the HS to LS Hi-queue read pointer update indication
#define H2L_HQ_ACK_TG                       (ICC_H->lptg_b.lptg2)
/// Toggle bit of the HS to LS Lo-queue read pointer update indication
#define H2L_LQ_ACK_TG                       (ICC_H->lptg_b.lptg3)

/// HS to LS Hi-queue write pointer update interrupt enable
#define H2L_HQ_IND_IE                       (ICC_L->hptgie_b.hptgie0)
/// HS to LS Hi-queue write pointer update interrupt status
#define H2L_HQ_IND_IS                       (ICC_L->hptgis_b.hptgis0)
/// HS to LS Hi-queue write pointer update interrupt status mask
#define H2L_HQ_IND_IS_MASK                  ((uint32_t)(1 << 0))
/// HS to LS Lo-queue write pointer update interrupt enable
#define H2L_LQ_IND_IE                       (ICC_L->hptgie_b.hptgie1)
/// HS to LS Lo-queue write pointer update interrupt status
#define H2L_LQ_IND_IS                       (ICC_L->hptgis_b.hptgis1)
/// HS to LS Lo-queue write pointer update interrupt status mask
#define H2L_LQ_IND_IS_MASK                  ((uint32_t)(1 << 1))

/// LS to HS Hi-queue read pointer update interrupt enable
#define L2H_HQ_ACK_IE                       (ICC_L->hptgie_b.hptgie2)
/// LS to HS Hi-queue read pointer update interrupt status
#define L2H_HQ_ACK_IS                       (ICC_L->hptgis_b.hptgis2)
/// LS to HS Hi-queue read pointer update interrupt status mask
#define L2H_HQ_ACK_IS_MASK                  ((uint32_t)(1 << 2))
/// LS to HS Lo-queue read pointer update interrupt enable
#define L2H_LQ_ACK_IE                       (ICC_L->hptgie_b.hptgie3)
/// LS to HS Lo-queue read pointer update interrupt status
#define L2H_LQ_ACK_IS                       (ICC_L->hptgis_b.hptgis3)
/// LS to HS Lo-queue read pointer update interrupt status mask
#define L2H_LQ_ACK_IS_MASK                  ((uint32_t)(1 << 3))

/// Toggle bit of the semaphore update
#define L2H_SEMA_TG                         (ICC_H->lptg_b.l2htgs)

/// Toggle bit of the LS to HS ICC command indication
#define L2H_CMD_ACK                         (ICC_H->hptg_b.h2ltg1)

/// @cond DOXYGEN_ROM_HAL_API

/** 
 * @addtogroup ls_hal_icc_rom_func ICC HAL ROM APIs.
 * @ingroup ls_hal_icc
 * @{
 */

void hal_icc_irq_handler_bh_rtl8195blp (void);
void hal_icc_enter_critical_rtl8195blp (hal_icc_adapter_t *icc_adapter);
void hal_icc_exit_critical_rtl8195blp (hal_icc_adapter_t *icc_adapter);
void hal_icc_reg_irq_rtl8195blp (irq_handler_t handler);
hal_status_t hal_icc_l2h_cmd_send_rtl8195blp  (hal_icc_adapter_t *icc_adapter, uint32_t cmd_word0, 
                                                uint32_t cmd_word1, uint32_t timeout_us);
hal_status_t hal_icc_reset_queue_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
void hal_icc_h2l_cmd_ind_hook_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_cmd_ind pcallback, void *pdata);
void hal_icc_h2l_queue_ind_hook_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_q_ind pcallback, void *pdata);
void hal_icc_l2h_queue_ack_hook_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_q_ack pcallback, void *pdata);
void hal_icc_task_yield_hook_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_task_yield task_yield);
void hal_icc_init_rtl8195blp  (hal_icc_adapter_t *icc_adapter);
void hal_icc_deinit_rtl8195blp  (hal_icc_adapter_t *icc_adapter);
hal_status_t hal_icc_push_l2hq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t q_id_size, 
                                            uint8_t *pbuf, uint32_t timeout_us);
uint32_t hal_icc_pull_h2lq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t q_id, 
                                            uint8_t *pbuf, uint32_t size);
BOOL hal_icc_is_queue_empty_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
uint32_t hal_icc_get_queue_free_size_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
hal_status_t hal_icc_push_l2h_hq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, 
                                            uint32_t size, uint32_t timeout_us);
hal_status_t hal_icc_push_l2h_lq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, 
                                            uint32_t size, uint32_t timeout_us);
uint32_t hal_icc_pull_h2l_hq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size);
uint32_t hal_icc_pull_h2l_lq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size);
hal_status_t hal_icc_send_l2h_hq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size, 
                                            uint32_t timeout_us);
hal_status_t hal_icc_send_l2h_lq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size, 
                                            uint32_t timeout_us);
hal_status_t hal_icc_send_l2hq_int_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t q_id, icc_q_rw_req_t *send_req);
uint32_t hal_icc_send_l2hq_abort_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
hal_status_t hal_icc_send_l2h_hq_int_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *send_req);
hal_status_t hal_icc_send_l2h_lq_int_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *send_req);
uint32_t hal_icc_send_l2h_hq_abort_rtl8195blp (hal_icc_adapter_t *icc_adapter);
uint32_t hal_icc_send_l2h_lq_abort_rtl8195blp (hal_icc_adapter_t *icc_adapter);
uint32_t hal_icc_recv_h2lq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t q_id_size, 
                                        uint8_t *pbuf, uint32_t timeout_us);
uint32_t hal_icc_recv_h2l_hq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, 
                                            uint32_t size, uint32_t timeout_us);
uint32_t hal_icc_recv_h2l_lq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, 
                                            uint32_t size, uint32_t timeout_us);
hal_status_t hal_icc_recv_h2lq_int_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t q_id, icc_q_rw_req_t *rcv_req);
hal_status_t hal_icc_recv_h2l_hq_int_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *rcv_req);
hal_status_t hal_icc_recv_h2l_lq_int_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_q_rw_req_t *rcv_req);
uint32_t hal_icc_recv_h2lq_abort_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
uint32_t hal_icc_recv_h2l_hq_abort_rtl8195blp (hal_icc_adapter_t *icc_adapter);
uint32_t hal_icc_recv_h2l_lq_abort_rtl8195blp (hal_icc_adapter_t *icc_adapter);
hal_status_t hal_icc_get_sema_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_sema_id_t sema_id);
hal_status_t hal_icc_release_sema_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_sema_id_t sema_id);
void hal_icc_set_hal_cmd_tbl_rtl8195blp(hal_icc_adapter_t *icc_adapter, icc_user_cmd_entry_t *pcmd_tbl, uint32_t cmd_tbl_size);
void hal_icc_set_cmd_tbl_rtl8195blp(hal_icc_adapter_t *icc_adapter, icc_user_cmd_entry_t *pcmd_tbl, 
                         uint32_t cmd_tbl_size);
hal_status_t hal_icc_hal_cmd_register_rtl8195blp(hal_icc_adapter_t *icc_adapter, uint8_t cmd,
                                        icc_user_cmd_handler_t callback, uint32_t cb_arg);
void hal_icc_hal_cmd_unregister_all_rtl8195blp(hal_icc_adapter_t *icc_adapter);
void hal_icc_hal_cmd_unregister_rtl8195blp(hal_icc_adapter_t *icc_adapter, uint8_t cmd);
hal_status_t hal_icc_cmd_register_rtl8195blp(hal_icc_adapter_t *icc_adapter, uint8_t cmd,
                                        icc_user_cmd_handler_t callback, uint32_t cb_arg);
void hal_icc_cmd_unregister_all_rtl8195blp(hal_icc_adapter_t *icc_adapter);
void hal_icc_cmd_unregister_rtl8195blp(hal_icc_adapter_t *icc_adapter, uint8_t cmd);
hal_status_t hal_icc_send_msg_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_msg_type_t *picc_msg, 
                                             uint32_t timeout_us);
hal_status_t hal_icc_send_msg_int_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_msg_type_t *picc_msg,
                                              icc_user_msg_tx_callback_t callback, uint32_t callback_para);
void hal_icc_msg_queue_ind_hook_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_msg_q_ind_t pcallback);
void hal_icc_set_hal_msg_tbl_rtl8195blp(hal_icc_adapter_t *icc_adapter, icc_user_msg_entry_t *pmsg_tbl, uint32_t msg_tbl_size);
void hal_icc_set_msg_tbl_rtl8195blp(hal_icc_adapter_t *icc_adapter, icc_user_msg_entry_t *pmsg_tbl, 
                         uint32_t msg_tbl_size);
hal_status_t hal_icc_hal_msg_register_rtl8195blp(hal_icc_adapter_t *icc_adapter, uint8_t msg,
                                        icc_user_msg_handler_t callback, uint32_t cb_arg);
void hal_icc_hal_msg_unregister_all_rtl8195blp(hal_icc_adapter_t *icc_adapter);
void hal_icc_hal_msg_unregister_rtl8195blp(hal_icc_adapter_t *icc_adapter, uint8_t msg);
hal_status_t hal_icc_msg_register_rtl8195blp(hal_icc_adapter_t *icc_adapter, uint8_t msg,
                                        icc_user_msg_handler_t callback, uint32_t cb_arg);
void hal_icc_msg_unregister_all_rtl8195blp(hal_icc_adapter_t *icc_adapter);
void hal_icc_msg_unregister_rtl8195blp(hal_icc_adapter_t *icc_adapter, uint8_t msg);
void hal_icc_set_timeout_rtl8195blp(hal_icc_adapter_t *icc_adapter, uint32_t cmd_timeout_us);
hal_status_t hal_icc_ping_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t ping_data, uint32_t timeout_us);
void hal_icc_init_cmd_q_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint32_t *pbuf, uint8_t cmd_q_size);
void hal_icc_tx_req_pool_fill_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_msg_tx_req_t *q_req);
picc_msg_tx_req_t hal_icc_tx_req_pool_get_rtl8195blp (hal_icc_adapter_t *icc_adapter);
void hal_icc_msg_tx_req_pending_process_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
hal_status_t hal_icc_msg_tx_req_submit_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_msg_tx_req_t *q_req);
picc_msg_rx_req_t hal_icc_msg_rx_req_done_deq_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
void icc_msg_rx_ready_handler_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t frame_type, uint8_t msg_type,
                                          uint8_t *pmsg_data, uint32_t msg_len);
void hal_icc_msg_rx_req_done_process_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
hal_status_t hal_icc_msg_rx_req_submit_rtl8195blp (hal_icc_adapter_t *icc_adapter, icc_msg_rx_req_t *q_req);
void hal_icc_msg_rx_req_pending_process_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
hal_status_t hal_icc_msg_tbl_reg_rtl8195blp(hal_icc_adapter_t *icc_adapter, uint8_t msg, uint8_t frame,
                                                     icc_msg_rx_cb_t callback, uint32_t cb_arg);
void hal_icc_msg_tbl_unreg_rtl8195blp (hal_icc_adapter_t *icc_adapter, uint8_t msg, uint8_t frame);

/** @} */ /* End of group ls_hal_icc_rom_func */

/// @endcond    /* End of cond DOXYGEN_ROM_HAL_API */

/**
  \brief  The data structure of the stubs function for the ICC HAL functions in ROM
*/
typedef struct hal_icc_func_stubs_s {
    void (*hal_icc_enter_critical)(hal_icc_adapter_t *icc_adapter);
    void (*hal_icc_exit_critical)(hal_icc_adapter_t *icc_adapter);
    void (*hal_icc_reg_irq)(irq_handler_t handler);
    hal_status_t (*hal_icc_l2h_cmd_send)(hal_icc_adapter_t *icc_adapter, uint32_t cmd_word0, \
                                         uint32_t cmd_word1, uint32_t timeout_us);
    hal_status_t (*hal_icc_reset_queue)(hal_icc_adapter_t *icc_adapter, uint32_t q_id);    
    void (*hal_icc_h2l_cmd_ind_hook)(hal_icc_adapter_t *icc_adapter, icc_cmd_ind pcallback, void *pdata);
    void (*hal_icc_h2l_queue_ind_hook)(hal_icc_adapter_t *icc_adapter, icc_q_ind pcallback, void *pdata);
    void (*hal_icc_l2h_queue_ack_hook)(hal_icc_adapter_t *icc_adapter, icc_q_ack pcallback, void *pdata);
    void (*hal_icc_task_yield_hook)(hal_icc_adapter_t *icc_adapter, icc_task_yield task_yield);
    void (*hal_icc_init) (hal_icc_adapter_t *icc_adapter);
    void (*hal_icc_deinit) (hal_icc_adapter_t *icc_adapter);
    hal_status_t (*hal_icc_push_l2hq)(hal_icc_adapter_t *icc_adapter, uint32_t q_id_size, 
                                       uint8_t *pbuf, uint32_t timeout_us);
    uint32_t (*hal_icc_pull_h2lq)(hal_icc_adapter_t *icc_adapter, uint32_t q_id, 
                                                uint8_t *pbuf, uint32_t size);
    BOOL (*hal_icc_is_queue_empty) (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
    uint32_t (*hal_icc_get_queue_free_size) (hal_icc_adapter_t *icc_adapter, uint32_t q_id);
    hal_status_t (*hal_icc_send_l2h_hq) (hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size, 
                                         uint32_t timeout_us);
    hal_status_t (*hal_icc_send_l2h_lq)(hal_icc_adapter_t *icc_adapter, uint8_t *pbuf, uint32_t size, 
                                        uint32_t timeout_us);
    hal_status_t (*hal_icc_send_l2hq_int)(hal_icc_adapter_t *icc_adapter, uint32_t q_id, icc_q_rw_req_t *send_req);
    uint32_t (*hal_icc_send_l2hq_abort)(hal_icc_adapter_t *icc_adapter, uint32_t q_id);
    uint32_t (*hal_icc_recv_h2lq)(hal_icc_adapter_t *icc_adapter, uint32_t q_id_size, 
                                  uint8_t *pbuf, uint32_t timeout_us);
    hal_status_t (*hal_icc_recv_h2lq_int)(hal_icc_adapter_t *icc_adapter, uint32_t q_id, icc_q_rw_req_t *rcv_req);
    uint32_t (*hal_icc_recv_h2lq_abort)(hal_icc_adapter_t *icc_adapter, uint32_t q_id);
    hal_status_t (*hal_icc_get_sema) (hal_icc_adapter_t *icc_adapter, icc_sema_id_t sema_id);
    hal_status_t (*hal_icc_release_sema) (hal_icc_adapter_t *icc_adapter, icc_sema_id_t sema_id);
    void (*hal_icc_set_hal_cmd_tbl)(hal_icc_adapter_t *icc_adapter, icc_user_cmd_entry_t *pcmd_tbl, uint32_t cmd_tbl_size);    
    void (*hal_icc_set_cmd_tbl)(hal_icc_adapter_t *icc_adapter, icc_user_cmd_entry_t *pcmd_tbl, uint32_t cmd_tbl_size);
    hal_status_t (*hal_icc_hal_cmd_register)(hal_icc_adapter_t *icc_adapter, uint8_t cmd,
                                    icc_user_cmd_handler_t callback, uint32_t cb_arg);
    void (*hal_icc_hal_cmd_unregister_all)(hal_icc_adapter_t *icc_adapter);
    void (*hal_icc_hal_cmd_unregister)(hal_icc_adapter_t *icc_adapter, uint8_t cmd);
    hal_status_t (*hal_icc_cmd_register)(hal_icc_adapter_t *icc_adapter, uint8_t cmd,
                                    icc_user_cmd_handler_t callback, uint32_t cb_arg);
    void (*hal_icc_cmd_unregister_all)(hal_icc_adapter_t *icc_adapter);
    void (*hal_icc_cmd_unregister)(hal_icc_adapter_t *icc_adapter, uint8_t cmd);
    hal_status_t (*hal_icc_send_msg) (hal_icc_adapter_t *icc_adapter, icc_msg_type_t *picc_msg, uint32_t timeout_us);
    hal_status_t (*hal_icc_send_msg_int) (hal_icc_adapter_t *icc_adapter, icc_msg_type_t *picc_msg,
                                          icc_user_msg_tx_callback_t callback, uint32_t callback_para);
    void (*hal_icc_msg_queue_ind_hook)(hal_icc_adapter_t *icc_adapter, icc_msg_q_ind_t pcallback);
    void (*hal_icc_set_hal_msg_tbl)(hal_icc_adapter_t *icc_adapter, icc_user_msg_entry_t *pmsg_tbl, uint32_t msg_tbl_size);
    void (*hal_icc_set_msg_tbl)(hal_icc_adapter_t *icc_adapter, icc_user_msg_entry_t *pmsg_tbl, 
                             uint32_t msg_tbl_size);
    hal_status_t (*hal_icc_hal_msg_register)(hal_icc_adapter_t *icc_adapter, uint8_t msg,
                                    icc_user_msg_handler_t callback, uint32_t cb_arg);
    void (*hal_icc_hal_msg_unregister_all)(hal_icc_adapter_t *icc_adapter);
    void (*hal_icc_hal_msg_unregister)(hal_icc_adapter_t *icc_adapter, uint8_t msg);
    hal_status_t (*hal_icc_msg_register)(hal_icc_adapter_t *icc_adapter, uint8_t msg,
                                    icc_user_msg_handler_t callback, uint32_t cb_arg);
    void (*hal_icc_msg_unregister_all)(hal_icc_adapter_t *icc_adapter);
    void (*hal_icc_msg_unregister)(hal_icc_adapter_t *icc_adapter, uint8_t msg);
    void (*hal_icc_set_timeout)(hal_icc_adapter_t *icc_adapter, uint32_t cmd_timeout_us);
    hal_status_t (*hal_icc_ping) (hal_icc_adapter_t *icc_adapter, uint32_t ping_data, uint32_t timeout_us);

    icc_cmd_entry_t *rom_cmd_table;
    
    // B-Cut
    phal_icc_adapter_t *ppicc_adapter;
    void (*hal_icc_irq_handler_bh) (void);
    void (*hal_icc_init_cmd_q) (hal_icc_adapter_t *icc_adapter, uint32_t *pbuf, uint8_t cmd_q_size);
    void (*hal_icc_tx_req_pool_fill) (hal_icc_adapter_t *icc_adapter, icc_msg_tx_req_t *q_req);
    picc_msg_tx_req_t (*hal_icc_tx_req_pool_get) (hal_icc_adapter_t *icc_adapter);
    void (*hal_icc_msg_tx_req_pending_process) (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
    hal_status_t (*hal_icc_msg_tx_req_submit) (hal_icc_adapter_t *icc_adapter, icc_msg_tx_req_t *q_req);
    picc_msg_rx_req_t (*hal_icc_msg_rx_req_done_deq) (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
    void (*icc_msg_rx_ready_handler) (hal_icc_adapter_t *icc_adapter, uint8_t frame_type, uint8_t msg_type,
                                       uint8_t *pmsg_data, uint32_t msg_len);
    void (*hal_icc_msg_rx_req_done_process) (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
    hal_status_t (*hal_icc_msg_rx_req_submit) (hal_icc_adapter_t *icc_adapter, icc_msg_rx_req_t *q_req);
    void (*hal_icc_msg_rx_req_pending_process) (hal_icc_adapter_t *icc_adapter, uint8_t q_id);
    hal_status_t (*hal_icc_msg_tbl_reg)(hal_icc_adapter_t *icc_adapter, uint8_t msg, uint8_t frame,
                                        icc_msg_rx_cb_t callback, uint32_t cb_arg);
    void (*hal_icc_msg_tbl_unreg) (hal_icc_adapter_t *icc_adapter, uint8_t msg, uint8_t frame);

    uint32_t reserved[2];  // reserved space for next ROM code version function table extending.
} hal_icc_func_stubs_t;

/** @} */ /* End of group ls_hal_icc */

#ifdef __cplusplus
}
#endif

#endif /* RTL8195BLP_ICC_H */

