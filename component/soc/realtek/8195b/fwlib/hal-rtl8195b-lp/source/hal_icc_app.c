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
#include "cmsis.h"
#include "hal.h"
#include "memory.h"
#include "hal_sys_ctrl.h"
#include "hal_icc_app.h"
#include "hal_power_mode.h"
#ifdef CONFIG_ICC_EN

/** 
 * @addtogroup ls_hal_icc ICC
 * @{
 */

/// Defines the stack size of the HAL ICC task
#define ICC_TASK_STACK_SIZE        (1024)
/// Defines the HAL ICC task priority
#define ICC_TASK_PRIORITY           osPriorityHigh

/// The size, in command entity, of the ICC HAL command callback register table
#define ICC_HAL_CMD_TBL_SIZE        20
/// The size of the ICC HAL message callback register table
#define ICC_HAL_MSG_TBL_SIZE        0
/// The size (in number of ICC command) of ICC command RX queue
#define ICC_CMD_Q_SIZE              10
/// The size of ICC application message callback register table
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

hal_icc_adapter_t icc_hal_adp;
#if (ICC_HAL_CMD_TBL_SIZE > 0)
icc_user_cmd_entry_t icc_hal_cmd_tbl[ICC_HAL_CMD_TBL_SIZE];
#endif
#if (ICC_HAL_MSG_TBL_SIZE > 0)
icc_user_msg_entry_t icc_hal_msg_tbl[ICC_HAL_MSG_TBL_SIZE];
#endif

#if (ICC_MSG_REG_TBL_SIZE > 0)
icc_msg_entry_t icc_msg_reg_table[ICC_MSG_REG_TBL_SIZE];
#endif

#if (ICC_MSG_TX_REQ_NUM > 0)
icc_msg_tx_req_t icc_msg_txreq[ICC_MSG_TX_REQ_NUM];
#endif

#if (ICC_MSG_HQRX_REQ_NUM > 0)
icc_msg_rx_req_t icc_msg_hqrx_req[ICC_MSG_HQRX_REQ_NUM];
__ALIGNED(4) uint8_t icc_msg_hqrx_req_buf[ICC_MSG_HQRX_REQ_NUM][ICC_MSG_HQRX_REQ_BUF_SIZE];
#endif

#if (ICC_MSG_LQRX_REQ_NUM > 0)
icc_msg_rx_req_t icc_msg_lqrx_req[ICC_MSG_LQRX_REQ_NUM];
__ALIGNED(4) uint8_t icc_msg_lqrx_req_buf[ICC_MSG_LQRX_REQ_NUM][ICC_MSG_LQRX_REQ_BUF_SIZE];
#endif

#if (ICC_CMD_Q_SIZE > 0)
uint32_t icc_cmd_q_buf[ICC_CMD_Q_SIZE * 2];     // each ICC command entity use 2 Double-Words of size
#endif

#ifdef CONFIG_LS_RESET_REQ_EN
extern void platform_reset_req_handler (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg);
#endif
#ifdef CONFIG_SWWDT_EN
extern void ls_setup_swwdt (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg);
extern void ls_start_swwdt (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg);
extern void ls_refresh_swwdt (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg);
#endif

static uint8_t icc_hal_adp_inited;
static uint8_t icc_task_started;

#if CONFIG_CMSIS_RTX_EN | CONFIG_CMSIS_FREERTOS_EN
int32_t icc_task_wakeup (void *arg);
void icc_task (void const *arg);
osThreadId tid_icc_task;                                // ICC task for ICC IRQ button half handling
osThreadDef (icc_task, ICC_TASK_PRIORITY, 1, ICC_TASK_STACK_SIZE);         // thread object
osSemaphoreId icc_up_sema;                              // Semaphore ID for ICC task wakeup
osSemaphoreDef(icc_up_sema);                            // Semaphore definition
osMutexId icc_hal_mutex;                                // the mutex for ICC HAL critical section protection
osMutexDef (icc_hal_mutex);
#endif      // end of "#if CONFIG_CMSIS_RTX_EN | CONFIG_CMSIS_FREERTOS_EN"

/** 
 *  @brief Initials the ICC HAL application resource. 
 *
 *  @returns void.
 */
void icc_hal_app_init (void)
{
//    hal_status_t ret;
//    uint32_t i;
//    icc_cmd_general_t icc_cmd;
    
    if (icc_hal_adp_inited) {
        // ICC adapter has been initialed
        return;
    }
    memset ((void *)&icc_hal_adp, 0, sizeof(hal_icc_adapter_t));
    hal_icc_init(&icc_hal_adp);    
    hal_icc_set_timeout(&icc_hal_adp, 100000);
#if (ICC_HAL_CMD_TBL_SIZE > 0)
    hal_icc_set_hal_cmd_tbl(&icc_hal_adp, &icc_hal_cmd_tbl[0], ICC_HAL_CMD_TBL_SIZE);
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_CMD_DBG_PORT_CFG, dbg_port_cfg_noti_handler, NULL);
#ifdef CONFIG_LS_RESET_REQ_EN    
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_CMD_LS_RST_REQ, platform_reset_req_handler, NULL);
#endif
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_HP_CG, slp_ls_cg_cmd_handler, NULL);
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_HP_PD, slp_ls_pd_cmd_handler, NULL);
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_CMD_LS_EFUSE_RWB, icc_hal_efuse_rw_cmd_cb, NULL);
#ifdef CONFIG_SWWDT_EN
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_CMD_LS_SWWDT_INIT, ls_setup_swwdt, NULL);
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_CMD_LS_SWWDT_START, ls_start_swwdt, NULL);
    hal_icc_hal_cmd_register(&icc_hal_adp, HAL_ICC_CMD_LS_SWWDT_REFLESH, ls_refresh_swwdt, NULL);
#endif
#endif
#if (ICC_HAL_MSG_TBL_SIZE > 0)
    hal_icc_set_hal_msg_tbl(&icc_hal_adp, &icc_hal_msg_tbl[0], ICC_HAL_MSG_TBL_SIZE);
#endif
#if (ICC_CMD_Q_SIZE > 0)
    hal_icc_init_cmd_q (&icc_hal_adp, icc_cmd_q_buf, ICC_CMD_Q_SIZE);
#endif

    // Notify HS that LS is ready
#if 0    // somehow the HS initial takes too long to response LS ICC command, so skip the LS ready notification.
    icc_cmd.word0 = 0;
    icc_cmd.word0_b.cmd = HAL_ICC_CMD_LS_RDY;
    // HA may not ready yet, so we turn off the error message templorary.
    DBG_ERR_MSG_OFF (_DBG_ICC_);
    for (i=0; i<100; i++) {
        if (hal_icc_l2h_cmd_send(&icc_hal_adp, icc_cmd.word0, 0, 500) == HAL_OK) {
            break;
        }
    }
    DBG_ERR_MSG_ON (_DBG_ICC_);
    if (i >= 100) {
        DBG_ICC_ERR("HS ICC No response!\r\n");
    }
#endif

#if ICC_MSG_REG_TBL_SIZE
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
    
        hal_icc_msg_rx_req_submit (&icc_hal_adp, &icc_msg_hqrx_req[i]);
    }
#endif
    
    icc_hal_adp_inited = 1;
}

void icc_hal_efuse_rw_cmd_cb (uint32_t icc_cmd_word0, uint32_t icc_cmd_word1, uint32_t arg)
{
    icc_cmd_ls_efuse_rw_t efuse_rw_cmd;
    icc_cmd_ls_efuse_rw_ret_t efuse_rw_ret;
    uint16_t addr;
    uint8_t data;
    uint8_t byte_cnt;
    uint8_t i;
    uint8_t rw_flag;
    uint8_t read_data = 0;
    uint32_t ret = _FALSE;
    

    efuse_rw_cmd.cmd_w = icc_cmd_word0;
    byte_cnt = efuse_rw_cmd.cmd_b.byte_cnt + 1;
    rw_flag = efuse_rw_cmd.cmd_b.rw_flag;
    addr = efuse_rw_cmd.cmd_b.addr;
    for (i=0; i < byte_cnt; i++) {
        if (rw_flag == ICC_LS_EFUSE_READ) {
            // read efuse data
            ret = hal_efuse_read (EFUSE_CTRL_SETTING, (addr + i), &data, 7); 
            read_data |= data << (8 * i);
        } else {
            data = (icc_cmd_word1 >> (8 * i)) & 0xFF;
            ret = hal_efuse_write (EFUSE_CTRL_SETTING, (addr + i), data, 7); 
        }
        
        if (ret != _TRUE) {
            break;
        }
    }

    // to do: send efuse read/write result ICC command
    efuse_rw_ret.cmd_w = icc_cmd_word0;
    efuse_rw_ret.cmd_b.cmd = HAL_ICC_CMD_LS_EFUSE_RW_RET;
    if (ret == _TRUE) {
        efuse_rw_ret.cmd_b.status = SUCCESS;
    } else {
        efuse_rw_ret.cmd_b.status = FAIL;
    }
    ret = hal_icc_l2h_cmd_send (&icc_hal_adp, efuse_rw_ret.cmd_w, read_data, 0);
    
}

#if CONFIG_CMSIS_RTX_EN | CONFIG_CMSIS_FREERTOS_EN
/** 
 *  @brief Wakes up the ICC task to handle the button half of IRQ.
 *
 *  @returns void.
 */
int32_t icc_task_wakeup (void *arg)
{
    osSemaphoreRelease (icc_up_sema);
    return 0;
}

/** 
 *  @brief Gets the mutex of the ICC HAL critical section protection.
 *
 *  @returns void.
 */
void _hal_icc_lock (hal_icc_adapter_t *arg)
{
    (void) arg;
    
    osMutexWait(icc_hal_mutex, osWaitForever);
    icc_hal_adp.mutex_locked = 1;
}

/** 
 *  @brief  Release the mutex of the ICC HAL critical section protection.
 *
 *  @returns void.
 */
void _hal_icc_unlock (hal_icc_adapter_t *arg)
{
    (void) arg;

    if (icc_hal_adp.mutex_locked) {
        icc_hal_adp.mutex_locked = 0;
        osMutexRelease(icc_hal_mutex);
    }
}

/** 
 *  @brief  Creates the ICC task for the ICC HAL interrupt handling.
 *
 *  @returns void.
 */
void icc_task_init(void)
{
    if (icc_task_started) {
        return;
    }
    
    tid_icc_task = osThreadCreate (osThread(icc_task), NULL);
    if (tid_icc_task == NULL) {
        DBG_ICC_ERR ("%s: Create ICC task error\r\n", __func__);
    } else {
        dbg_printf("ICC task created!!\r\n");
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
    
    osThreadTerminate (tid_icc_task);
    osMutexDelete (icc_hal_mutex);
    osSemaphoreRelease (icc_up_sema);
    icc_task_started = 0;
}

/** 
 *  @brief  The ICC task for the ICC HAL interrupt handling.
 *
 *  @returns void.
 */
void icc_task (void const *arg)
{
    hal_icc_adapter_t *icc_adapter = &icc_hal_adp;
#ifdef CONFIG_SWWDT_EN    
    // init sw wdt
    ls_init_swwdt();
#endif	
    dbg_printf("%s=>\r\n", __func__);
    icc_task_started = 1;
    
    icc_hal_mutex = osMutexCreate (osMutex (icc_hal_mutex));
    if (icc_hal_mutex == NULL)  {
        // Mutex object create failed
        DBG_ICC_ERR("ICC HAL mutex create error!!\r\n");
    } else {
        icc_adapter->enter_critical = _hal_icc_lock;
        icc_adapter->exit_critical = _hal_icc_unlock;
    }

    icc_up_sema = osSemaphoreCreate(osSemaphore(icc_up_sema), 1);
    if (icc_up_sema == NULL) {
        DBG_ICC_ERR ("%s: Create ICC semaphore error\r\n", __func__);
    } else {
        icc_adapter->task_up = icc_task_wakeup;
    }

    while (1) {
        osSemaphoreWait (icc_up_sema, osWaitForever);
        hal_icc_lock (icc_adapter);
        hal_icc_irq_handler_bh ();        
        hal_icc_msg_rx_req_done_process(icc_adapter, ICC_HQ);
        hal_icc_msg_rx_req_pending_process (icc_adapter, ICC_HQ);
        hal_icc_msg_tx_req_pending_process (icc_adapter, ICC_HQ);
        hal_icc_msg_rx_req_done_process(icc_adapter, ICC_LQ);
        hal_icc_msg_rx_req_pending_process (icc_adapter, ICC_LQ);
        hal_icc_msg_tx_req_pending_process (icc_adapter, ICC_LQ);
        hal_icc_unlock (icc_adapter);
    }
}
#endif

/** @} */ /* End of group ls_hal_icc */

#endif  // end of "#ifdef CONFIG_ICC_EN"

