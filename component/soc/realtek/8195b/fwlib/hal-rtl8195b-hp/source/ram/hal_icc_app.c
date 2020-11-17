/**************************************************************************//**
 * @file     hal_icc_app.c
 * @brief    This file implement the application for HS/LS platform HAL module
 *           communication over ICC.
 *
 * @version  V1.00
 * @date     2017-06-19
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

#include "cmsis.h"
#include "hal.h"
#include "hal_icc_app.h"
#include "memory.h"
#include "hal_sys_ctrl.h"
#include "osdep_service.h"
#include "hal_power_mode.h"
#include "hal_power_mode_nsc.h"
//#include "cmsis_os.h"               // CMSIS RTOS header file

#ifdef CONFIG_ICC_EN

/// Defines the stack size of the HAL ICC task
#define ICC_TASK_STACK_SIZE        (1024)
/// Defines the HAL ICC task priority, it can be 0(lowest) ~ configMAX_PRIORITIES-1(highest)
#define ICC_TASK_PRIORITY           11//7

#if defined (CONFIG_BUILD_NONSECURE)
// define size of the ICC HAL command callback register table
#define ICC_HAL_CMD_TBL_SIZE        6
// define size of the ICC message callback register table
#define ICC_HAL_MSG_TBL_SIZE        0

icc_ns_adapter_t icc_hal_adp;

#if (ICC_HAL_CMD_TBL_SIZE > 0)
icc_user_cmd_ns_entry_t icc_hal_cmd_tbl[ICC_HAL_CMD_TBL_SIZE];
#endif

#if (ICC_HAL_MSG_TBL_SIZE > 0)
icc_user_msg_ns_entry_t icc_hal_msg_tbl[ICC_HAL_MSG_TBL_SIZE];
#endif

#else   // else of "#if defined (CONFIG_BUILD_NONSECURE)"
// For (Ignore) Secure region
/// The size of the ICC HAL command callback register table
#define ICC_HAL_CMD_TBL_SIZE        5
/// The size of the ICC HAL message callback register table
#define ICC_HAL_MSG_TBL_SIZE        0
/// The size (in number of ICC command) of ICC command RX queue
#define ICC_CMD_Q_SIZE              10
/// The size of ICC message callback register table
#define ICC_MSG_REG_TBL_SIZE        0
/// The number of ICC message TX request entrys for message sending to HQ or LQ
#define ICC_MSG_TX_REQ_NUM          0
/// The number of RX requests is pending for ICC message receiving on HQ
#define ICC_MSG_HQRX_REQ_NUM        0
/// The number of RX requests is pending for ICC message receiving on LQ
#define ICC_MSG_LQRX_REQ_NUM        0
/// The size, in byte, of the ICC message data receiving buffer with the RX Req of HQ. An ICC message data size cannot over this size
#define ICC_MSG_HQRX_REQ_BUF_SIZE     1024
/// The size, in byte, of the ICC message data receiving buffer with the RX Req of LQ. An ICC message data size cannot over this size
#define ICC_MSG_LQRX_REQ_BUF_SIZE     1024
/// The size, in bytes, of the buffer for HS to LS High queue
#define ICC_HAL_H2L_HQ_SIZE         0
/// The size, in bytes, of the buffer for LS to HS High queue
#define ICC_HAL_L2H_HQ_SIZE         0

hal_icc_adapter_t icc_hal_adp;

#if (ICC_HAL_CMD_TBL_SIZE > 0)
icc_user_cmd_entry_t icc_hal_cmd_tbl[ICC_HAL_CMD_TBL_SIZE];
#endif

#if (ICC_HAL_MSG_TBL_SIZE > 0)
icc_user_msg_entry_t icc_hal_msg_tbl[ICC_HAL_MSG_TBL_SIZE];
#endif

#if (ICC_HAL_H2L_HQ_SIZE > 0)
SECTION_NS_BSS __ALIGNED(32) uint8_t icc_hal_h2l_hq_buf[ICC_HAL_H2L_HQ_SIZE];
#endif

#if (ICC_HAL_L2H_HQ_SIZE > 0)
SECTION_NS_BSS __ALIGNED(32) uint8_t icc_hal_l2h_hq_buf[ICC_HAL_L2H_HQ_SIZE];
#endif

#if (ICC_MSG_REG_TBL_SIZE > 0)
icc_msg_entry_t icc_msg_reg_table[ICC_MSG_REG_TBL_SIZE];
#endif

#if (ICC_MSG_TX_REQ_NUM > 0)
icc_msg_tx_req_t icc_msg_txreq[ICC_MSG_TX_REQ_NUM];
#endif

#if (ICC_MSG_HQRX_REQ_NUM > 0)
icc_msg_rx_req_t icc_msg_hqrx_req[ICC_MSG_HQRX_REQ_NUM];
uint8_t icc_msg_hqrx_req_buf[ICC_MSG_HQRX_REQ_NUM][ICC_MSG_HQRX_REQ_BUF_SIZE];
#endif

#if (ICC_MSG_LQRX_REQ_NUM > 0)
icc_msg_rx_req_t icc_msg_lqrx_req[ICC_MSG_LQRX_REQ_NUM];
uint8_t icc_msg_lqrx_req_buf[ICC_MSG_LQRX_REQ_NUM][ICC_MSG_LQRX_REQ_BUF_SIZE];
#endif

#if (ICC_CMD_Q_SIZE > 0)
uint32_t icc_cmd_q_buf[ICC_CMD_Q_SIZE * 2];     // each ICC command entity use 2 Double-Words of size
#endif

#endif      // end of else of "#if defined (CONFIG_BUILD_NONSECURE)"

#if CONFIG_CMSIS_RTX_EN | CONFIG_CMSIS_FREERTOS_EN
int32_t icc_task_wakeup (void *arg);
void hal_icc_task (void const *arg);

_sema icc_up_sema;  // Semaphore ID for ICC task wakeup
struct task_struct  icc_task;   // ICC task for ICC IRQ button half handling
_mutex icc_hal_mutex;   // the mutex for ICC HAL critical section protection
#endif      // end of "#if CONFIG_CMSIS_RTX_EN | CONFIG_CMSIS_FREERTOS_EN"

static uint8_t icc_hal_adp_inited;
static uint8_t icc_hal_ls_rdy;

void ls_ready_indication_handler (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg);
void hal_icc_ls_efuse_rw_ret_cb (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg);

/**
 *  @brief To initial the ICC HAL application resource.
 *         The secure region ICC application resource should be initialed first.
 *
 *  @returns void.
 */
void icc_hal_app_init (void)
{
#if !defined (CONFIG_BUILD_NONSECURE)
//    hal_status_t ret;
#endif

    if (icc_hal_adp_inited) {
        // ICC adapter has been initialed
        return;
    }

#if defined (CONFIG_BUILD_NONSECURE)
    memset ((void *)&icc_hal_adp, 0, sizeof(icc_ns_adapter_t));
#else
    memset ((void *)&icc_hal_adp, 0, sizeof(hal_icc_adapter_t));
#endif

    hal_icc_init(&icc_hal_adp);
#if !defined (CONFIG_BUILD_NONSECURE)
    hal_icc_set_timeout (&icc_hal_adp, 5000, 100000);  // cmd timeout = 5ms, LS read timeout = 100ms
#endif

#if (ICC_HAL_CMD_TBL_SIZE > 0)
    hal_icc_set_hal_cmd_tbl(&icc_hal_adp, &icc_hal_cmd_tbl[0], ICC_HAL_CMD_TBL_SIZE);
#if !defined (CONFIG_BUILD_NONSECURE)
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_LP_CG, slp_hs_cg_cmd_handler, NULL);
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_LP_PD, slp_hs_pd_cmd_handler, NULL);
#endif
#endif
#if (ICC_HAL_MSG_TBL_SIZE > 0)
    hal_icc_set_hal_msg_tbl(&icc_hal_adp, &icc_hal_msg_tbl[0], ICC_HAL_MSG_TBL_SIZE);
#endif

#if !defined (CONFIG_BUILD_NONSECURE)
    //    hal_icc_set_timeout(&icc_hal_adp, 10000, 10000);
#if (ICC_HAL_CMD_TBL_SIZE > 0)
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_CMD_DBG_PORT_CFG, dbg_port_cfg_noti_handler, NULL);
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_CMD_LS_RDY, ls_ready_indication_handler, NULL);
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_CMD_LS_EFUSE_RW_RET, hal_icc_ls_efuse_rw_ret_cb, NULL);
#endif

#if (ICC_HAL_H2L_HQ_SIZE > 0)    
    hal_icc_set_h2l_hq (&icc_hal_adp, (uint32_t)icc_hal_h2l_hq_buf, ICC_HAL_H2L_HQ_SIZE);
#endif
#if (ICC_HAL_L2H_HQ_SIZE > 0)
    hal_icc_set_l2h_hq (&icc_hal_adp, (uint32_t)icc_hal_l2h_hq_buf, ICC_HAL_L2H_HQ_SIZE);
#endif
#if ICC_CMD_Q_SIZE    
    hal_icc_init_cmd_q (&icc_hal_adp, icc_cmd_q_buf, ICC_CMD_Q_SIZE);
#endif

#if (ICC_MSG_REG_TBL_SIZE > 0)
    icc_hal_adp.pmsg_regtbl = icc_msg_reg_table;
    icc_hal_adp.msg_regtbl_sz = ICC_MSG_REG_TBL_SIZE;
#endif

#if (ICC_MSG_TX_REQ_NUM > 0)
    for (uint32_t i=0; i<ICC_MSG_TX_REQ_NUM; i++) {
        hal_icc_tx_req_pool_fill(&icc_hal_adp, &icc_msg_txreq[i]);
    }
#endif
    
#if (ICC_MSG_HQRX_REQ_NUM > 0)
    for (uint32_t i=0; i<ICC_MSG_HQRX_REQ_NUM; i++) {
        icc_msg_hqrx_req[i].q_id = ICC_HQ;
        icc_msg_hqrx_req[i].msg_buf = &icc_msg_hqrx_req_buf[i][0];
        icc_msg_hqrx_req[i].buf_size = ICC_MSG_HQRX_REQ_BUF_SIZE;
    
        hal_icc_msg_rx_req_submit (&icc_hal_adp, &icc_msg_hqrx_req[i]);
    }
#endif

#if (ICC_MSG_LQRX_REQ_NUM > 0)
    for (uint32_t i=0; i<ICC_MSG_LQRX_REQ_NUM; i++) {
        icc_msg_lqrx_req[i].q_id = ICC_LQ;
        icc_msg_lqrx_req[i].msg_buf = &icc_msg_lqrx_req_buf[i][0];
        icc_msg_lqrx_req[i].buf_size = ICC_MSG_LQRX_REQ_BUF_SIZE;
    
        hal_icc_msg_rx_req_submit (&icc_hal_adp, &icc_msg_lqrx_req[i]);
    }
#endif
#endif  // end of "#if !defined (CONFIG_BUILD_NONSECURE)"

    icc_hal_adp_inited = 1;
}

#if !defined (CONFIG_BUILD_NONSECURE)
void ls_ready_indication_handler (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg)
{
    icc_hal_ls_rdy = 1;
}

void hal_icc_ls_efuse_rw_ret_cb (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg)
{
    icc_hal_adp.ls_op_ret = icc_cmd_word0;
    icc_hal_adp.ls_op_data = icc_cmd_word1;
}

hal_status_t hal_icc_ls_efuse_write (uint16_t addr, uint8_t data)
{
    icc_cmd_ls_efuse_rw_t icc_cmd;
    picc_cmd_ls_efuse_rw_ret_t picc_cmd_ret;
    hal_status_t ret;
    uint32_t wdata;
    uint32_t i;
    uint32_t start_us;

    // Set the write address first
    icc_cmd.cmd_b.cmd = HAL_ICC_CMD_LS_EFUSE_RWB;
    icc_cmd.cmd_b.addr = addr;
    icc_cmd.cmd_b.rw_flag = ICC_LS_EFUSE_WRITE;
    icc_cmd.cmd_b.byte_cnt = 0; // 1 byte
    wdata = data;
    icc_hal_adp.ls_op_ret = 0;
    icc_hal_adp.ls_op_data = 0;
    ret = hal_icc_h2l_cmd_send (&icc_hal_adp, icc_cmd.cmd_w, wdata, 1000);
    if (ret != HAL_OK) {
        DBG_ICC_ERR ("hal_ls_efuse_write send cmd err(%lu)\r\n", ret);
        return ret;
    }

    start_us = hal_read_cur_time();
    picc_cmd_ret = (picc_cmd_ls_efuse_rw_ret_t)&(icc_hal_adp.ls_op_ret);
    // wait LS data
    while (picc_cmd_ret->cmd_b.cmd != HAL_ICC_CMD_LS_EFUSE_RW_RET) {
        if (hal_is_timeout (start_us, 100000)) {
            DBG_ICC_ERR ("hal_ls_efuse_write timeout!!\r\n");
            return HAL_TIMEOUT;
        } else {
            if (icc_hal_adp.task_yield != NULL) {
                (icc_hal_adp.task_yield)();
            }
        }
    }

    if (picc_cmd_ret->cmd_b.status == SUCCESS) {
        return HAL_OK;
    } else {
        return HAL_ERR_MEM;
    }
}

hal_status_t hal_icc_ls_efuse_read (uint16_t addr, uint8_t *pdata)
{
    icc_cmd_ls_efuse_rw_t icc_cmd;
    picc_cmd_ls_efuse_rw_ret_t picc_cmd_ret;
    hal_status_t ret;
    uint32_t wdata;
    uint32_t i;
    uint32_t start_us;

    // Set the write address first
    icc_cmd.cmd_b.cmd = HAL_ICC_CMD_LS_EFUSE_RWB;
    icc_cmd.cmd_b.addr = addr;
    icc_cmd.cmd_b.rw_flag = ICC_LS_EFUSE_READ;
    icc_cmd.cmd_b.byte_cnt = 0; // 1 byte
    wdata = *pdata;
    icc_hal_adp.ls_op_ret = 0;
    icc_hal_adp.ls_op_data = 0;
    ret = hal_icc_h2l_cmd_send (&icc_hal_adp, icc_cmd.cmd_w, wdata, 1000);
    if (ret != HAL_OK) {
        DBG_ICC_ERR ("hal_ls_efuse_read send cmd err(%lu)\r\n", ret);
        return ret;
    }

    start_us = hal_read_cur_time();
    picc_cmd_ret = (picc_cmd_ls_efuse_rw_ret_t)&(icc_hal_adp.ls_op_ret);
    // wait LS data
    while (picc_cmd_ret->cmd_b.cmd != HAL_ICC_CMD_LS_EFUSE_RW_RET) {
        if (hal_is_timeout (start_us, 100000)) {
            DBG_ICC_ERR ("hal_ls_efuse_write timeout!!\r\n");
            return HAL_TIMEOUT;
        } else {
            if (icc_hal_adp.task_yield != NULL) {
                (icc_hal_adp.task_yield)();
            }
        }
    }

    if (picc_cmd_ret->cmd_b.status == SUCCESS) {
        *pdata = (uint8_t)icc_hal_adp.ls_op_data;
        return HAL_OK;
    } else {
        return HAL_ERR_MEM;
    }
}

#endif  // end of "#if !defined (CONFIG_BUILD_NONSECURE)"

hal_status_t wait_ls_icc_ready (uint32_t wait_us)
{
    uint32_t i;
    uint32_t loop_cnt;
    hal_status_t ret;

    if (icc_hal_ls_rdy) {
        return HAL_OK;
    } else if (wait_us > 0) {
        // wait LS image boot ready: in the case of this function be called from ram_start();
        DBG_ERR_MSG_OFF(_DBG_ICC_);
        loop_cnt = wait_us/100 + 1;
        for (i=0; i<loop_cnt; i++) {
            ret = hal_icc_ping(&icc_hal_adp, 0, 100);
            if (ret == HAL_OK) {
                icc_hal_ls_rdy = 1;
                break;
            }
        }
        DBG_ERR_MSG_ON(_DBG_ICC_);
        
        if (ret != HAL_OK) {
            DBG_ICC_ERR ("LS ICC not ready!\r\n");
        }
        return ret;
    } else {
        return HAL_OK;
    }
}

/**
 *  @brief To write LS platform registers through ICC
 *
 *  @param addr The LS platform register address to write
 *  @param value the 32-bits aligned data for LS register write.
 *
 *  @returns The result.
 */
hal_status_t icc_happ_ls_write_reg (uint32_t addr, uint32_t value)
{
    return hal_icc_ls_write_reg (&icc_hal_adp, addr, value);
}

/**
 *  @brief To read LS platform registers through ICC
 *
 *  @param addr The LS platform register address to read.
 *
 *  @returns The read register value. If error occurred, the return value will be 0x00.
 */
uint32_t icc_happ_ls_read_reg (uint32_t addr)
{
    return hal_icc_ls_read_reg (&icc_hal_adp, addr);
}

#if !defined (CONFIG_BUILD_SECURE) && (CONFIG_CMSIS_RTX_EN || CONFIG_CMSIS_FREERTOS_EN)
static uint8_t icc_task_started;

int32_t icc_task_wakeup (void *arg)
{
    (void) arg;

    if (__get_IPSR () == 0U) {
        // Not in an ISR
        rtw_up_sema (&icc_up_sema);
    } else {
        // In an ISR
        rtw_up_sema_from_isr (&icc_up_sema);
    }    

    return 0;
}

void _hal_icc_lock (void *arg)
{
    (void) arg;
    
    rtw_mutex_get (&icc_hal_mutex);
    icc_hal_adp.mutex_locked = 1;
}

void _hal_icc_unlock (void *arg)
{
    (void) arg;
    
    if (icc_hal_adp.mutex_locked) {
        icc_hal_adp.mutex_locked = 0;
        rtw_mutex_put (&icc_hal_mutex);
    }
}

/** 
 *  @brief  Creates the ICC task for the ICC HAL interrupt handling and ICC message processing.
 *
 *  @returns void.
 */
void icc_task_init(void)
{
    int os_ret;

    if (icc_task_started) {
        return;
    }
    
    os_ret = rtw_create_task (&icc_task, "ICC_TASK", ICC_TASK_STACK_SIZE, ICC_TASK_PRIORITY, 
                              (thread_func_t)hal_icc_task, (void *)&icc_hal_adp);
    if (!os_ret) {
        DBG_ICC_ERR ("%s: Create ICC task error\r\n", __func__);
    }
}

/** 
 *  @brief  Stop and delete the ICC task.
 *
 *  @returns void.
 */
void icc_task_deinit(void)
{
    if (!icc_task_started) {
        return;
    }
    __disable_irq();
    icc_hal_adp.enter_critical = NULL;
    icc_hal_adp.exit_critical = NULL;
    icc_hal_adp.task_up = NULL;
    __enable_irq();
    
    rtw_delete_task(&icc_task);
    rtw_mutex_free (&icc_hal_mutex);
    icc_task_started = 0;
}

/** 
 *  @brief  The ICC task for the ICC HAL interrupt handling.
 *
 *  @returns void.
 */
void hal_icc_task (void const *arg)
{
    icc_task_started = 1;
    rtw_mutex_init (&icc_hal_mutex);
    if (icc_hal_mutex != NULL) {
        icc_hal_adp.enter_critical = _hal_icc_lock;
        icc_hal_adp.exit_critical = _hal_icc_unlock;
    } else {
        DBG_ICC_ERR ("%s: init mutex task error\r\n", __func__);
    }

    rtw_init_sema (&icc_up_sema, 1);
    icc_hal_adp.task_up = icc_task_wakeup;

    icc_task_wakeup(NULL);

    while (1) {
        rtw_down_sema (&icc_up_sema);

        hal_icc_lock (&icc_hal_adp);
        hal_icc_irq_handler_bh ();
        hal_icc_msg_rx_req_done_process(&icc_hal_adp, ICC_HQ);
        hal_icc_msg_rx_req_pending_process (&icc_hal_adp, ICC_HQ);
        hal_icc_msg_tx_req_pending_process (&icc_hal_adp, ICC_HQ);
        hal_icc_msg_rx_req_done_process (&icc_hal_adp, ICC_LQ);
        hal_icc_msg_rx_req_pending_process (&icc_hal_adp, ICC_LQ);
        hal_icc_msg_tx_req_pending_process (&icc_hal_adp, ICC_LQ);
        hal_icc_unlock (&icc_hal_adp);
        if (icc_task.blocked) {
            break;  // break the task while loop
        }
    }
    rtw_thread_exit ();
}
#endif      // end of "#if !defined (CONFIG_BUILD_SECURE) && (CONFIG_CMSIS_RTX_EN || CONFIG_CMSIS_FREERTOS_EN)"

#endif  // end of "#ifdef CONFIG_ICC_EN"

