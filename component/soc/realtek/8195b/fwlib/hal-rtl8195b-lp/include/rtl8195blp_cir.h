 /**************************************************************************//**
  * @file     rtl8195blp_cir.h
  * @brief    The HAL related definition and macros for the CIR device.
  *           Includes Registers and data type definition.
  * @version  V1.00
  * @date     2016-06-14
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

#ifndef _RTL8195BLP_CIR_H_
#define _RTL8195BLP_CIR_H_

/** 
 * @addtogroup ls_hal_cir CIR
 * @{
 */

#include "basic_types.h"
#include "rtl8195blp_cir_type.h"

#define CIR_SCLK            2000000 ///< CIR sclk rate   
#define SYMCFG0_OFFSET      0x18    ///< use for CIR hal   
#define RXSYMT0_OFFSET      0x1C    ///< use for CIR hal   
#define TXSYMCFG0_OFFSET    0x74    ///< use for CIR hal 

/**
  \brief  Define the CIR port ID.
*/
enum  cir_id_e
{
    Cir_0      = 0,
    MaxCirNum  = 1
};
typedef uint8_t cir_id_t;

/**
  \brief CIR application pin mux selection. 
*/
enum  cir_app_pin_sel_e
{
    Cir_Pin_Tx  =   0x0,
    Cir_Pin_Rx  =   0x1,  
    Cir_Pin_TRx =   0x2  
};
typedef uint8_t cir_app_pin_sel_t;

/**
  \brief CIR pin mux selection.
*/
enum  cir_pin_sel_e
{
    Cir_PinSel_0       = 0,  
    Cir_PinSel_1       = 1,
    Cir_PinSel_Max     = 2
};
typedef uint8_t cir_pin_sel_t;

/**
  \brief Set the symbol is the carrier site or not.
*/
enum  cir_carrier_site_e
{
    None_Carrier_Site  = 0,   
    Carrier_Site       = 1    
};
typedef uint8_t cir_carrier_site_t;

/**
  \brief Define the CIR symbol. 
*/
enum  cir_sym_e
{
    Symbol_Rx_None = 0x00, 
    Symbol_Tx_None = 0x00, 
    Symbol_End     = 0x00,
    Symbol_01      = 0x01,
    Symbol_02      = 0x02,
    Symbol_03      = 0x03,
    Symbol_04      = 0x04,
    Symbol_05      = 0x05,
    Symbol_06      = 0x06,
    Symbol_07      = 0x07,
    Symbol_08      = 0x08, 
    Symbol_Tx_End  = 0x08, 
    MaxCirSym      = 0x09
};
typedef uint8_t cir_sym_t;

/**
  \brief Define the CIR symbol type.
*/
enum  cir_sym_type_e
{
    Space_Low     = 0x00,
    Space_High    = 0x01,
    Carrier_Tp    = 0x02,   
    MaxCirSymType = 0x03
};
typedef uint8_t cir_sym_type_t;

/**
  \brief Define the CIR reset control.
*/
enum  cir_TRX_e
{
    CirNon = 0x00,
    CirTx = 0x01,
    CirRx = 0x02,
    CirTRx = 0x03  
};
typedef uint8_t cir_TRX_t;

/**
  \brief Define the CIR symbol group.
*/
enum  cir_sym_group_e
{
    SymGroup0 = 0x00,
    SymGroup1 = 0x01,
    SymGroup2 = 0x02,
    SymGroup3 = 0x03    
};
typedef uint8_t cir_sym_group_t;

/**
  \brief Define the CIR initial is high or low.
*/
enum  cir_init_value_e
{
    Init_Low = 0x00, 
    Init_High = 0x01
};
typedef uint8_t cir_init_value_t;

/**
  \brief Define the CIR has carrier or not.
*/
enum  cir_carrier_e
{
    No_Carrier = 0x00, 
    Carrier = 0x01
};
typedef uint8_t cir_carrier_t;

/**
  \brief Define automatically set sclk divider.
*/
enum  cir_sclkdiv_e
{
    Auto = 0x00 
};
typedef uint32_t cir_sclkdiv_t;

/**
  \brief Define the CIR rx decode status.
*/
enum  cir_rx_status_e
{
    cir_success = 0x00, 
    cir_repeat = 0x01,
    cir_fail = 0x02,
    cir_repeat_header = 0x03
};
typedef uint8_t cir_rx_status_t;

/**
  \brief Define the NEC tx format.
*/
enum  cir_nec_tx_format_e
{
    NEC_Tx_Normal = 0x00, 
    NEC_Tx_Repeat = 0x01,
    NEC_Tx_Extend = 0x02
};
typedef uint8_t cir_nec_tx_format_t;

/**
  \brief Define the NEC rx format.
*/
enum  cir_nec_rx_format_e
{
    NEC_Rx_Normal = 0x00, 
    NEC_Rx_Extend = 0x02
};
typedef uint8_t cir_nec_rx_format_t;

/**
  \brief Define the Sony SIRC format.
*/
enum  cir_sony_sirc_format_e
{
    SonySIRC_12bits = 0x00, 
    SonySIRC_15bits = 0x01,
    SonySIRC_20bits = 0x02
};
typedef uint8_t cir_sony_sirc_format_t;

/**
  \brief Define the Philips Rc5 format.
*/
enum  cir_philips_rc5_format_e
{
    Philips_rc5_Normal = 0x00, 
};
typedef uint8_t cir_philips_rc5_format_t;

/**
  \brief Define the JVC tx format.
*/
enum  cir_jvc_tx_format_e
{
    Jvc_Tx_Normal = 0x00, 
    Jvc_Tx_Repeat_Header = 0x01,
    Jvc_Tx_Repeat_No_Header = 0x02
};
typedef uint8_t cir_jvc_tx_format_t;

/**
  \brief Define the JVC rx format.
*/
enum  cir_jvc_rx_format_e
{
    Jvc_Rx_Normal = 0x00, 
};
typedef uint8_t cir_jvc_rx_format_t;

/**
  \brief Define the content of the NEC format.
*/
typedef union {
  __IOM uint32_t w;                        
  
  struct {
    __IOM uint32_t address      : 8;                                                                          
    __IOM uint32_t inv_address  : 8;           
    __IOM uint32_t command      : 8;                                                                          
    __IOM uint32_t inv_command  : 8;                                                                    
  } b;
  
} hal_cir_nec_format1_t, *phal_cir_nec_format1_t;

/**
  \brief Define the NEC normal format for the application.
*/
typedef union {
  __IOM uint32_t w;                        
  
  struct {
    __IOM uint32_t address      : 8;                                                                                    
    __IOM uint32_t command      : 8;                                                                                                                                          
  } b;
  
} hal_cir_nec_normal_format_t, *phal_cir_nec_normal_format_t;

/**
  \brief Define the NEC extend format for the application.
*/
typedef union {
  __IOM uint32_t w;                        
  
  struct {
    __IOM uint32_t address_l    : 8;
    __IOM uint32_t address_h    : 8; 
    __IOM uint32_t command      : 8;                                                                                                                                          
  } b;
  
} hal_cir_nec_extend_format_t, *phal_cir_nec_extend_format_t;

/**
  \brief Define the Sony SIRC 12bits format for the application.
*/
typedef union {
  __IOM uint32_t w;                        
  
  struct {
    __IOM uint32_t command    : 7;
    __IOM uint32_t address    : 5;                                                                                                                                          
  } b;
  
} hal_cir_sony_src_12bits_t, *phal_cir_sony_src_12bits_t;

/**
  \brief Define the Sony SIRC 15bits format for the application.
*/
typedef union {
  __IOM uint32_t w;                        
  
  struct {
    __IOM uint32_t command    : 7;
    __IOM uint32_t address    : 8;                                                                                                                                          
  } b;
  
} hal_cir_sony_src_15bits_t, *phal_cir_sony_src_15bits_t;

/**
  \brief Define the Sony SIRC 20bits format for the application.
*/
typedef union {
  __IOM uint32_t w;                        
  
  struct {
    __IOM uint32_t command    : 7;
    __IOM uint32_t address    : 5;      
    __IOM uint32_t extend     : 8;       
  } b;
  
} hal_cir_sony_src_20bits_t, *phal_cir_sony_src_20bits_t;

/**
  \brief Define the Philips Rc5 format for the application.
*/
typedef union {
  __IOM uint32_t w;                        
  
  struct {
    __IOM uint32_t field    : 1;                                                                                    
    __IOM uint32_t toggle   : 1;  
    __IOM uint32_t address  : 5;  
    __IOM uint32_t command  : 6;    
  } b;
  
} hal_cir_philips_rc5_format_t, *phal_cir_philips_rc5_format_t;

/**
  \brief Define the JVC format for the application.
*/
typedef union {
  __IOM uint32_t w;                        
  
  struct {
    __IOM uint32_t address      : 8;                                                                                    
    __IOM uint32_t command      : 8;                                                                                                                                          
  } b;
  
} hal_cir_jvc_format_t, *phal_cir_jvc_format_t;

/**
  \brief  CIR call back function for the interrupt event
*/
typedef void (*cir_irq_user_cb_t)(void *);

/**
  \brief Define CIR tx symbol description
*/
typedef struct hal_cir_tx_symdesc_s {
    u16 time_us;                /*!< Set the tx symbol time, the unit is us  */
    cir_sym_t symbol;           /*!< Set the tx symbol   */
    cir_sym_type_t symtype;     /*!< Set the tx symbol type   */
} hal_cir_tx_symdesc_t, *phal_cir_tx_symdesc_t;

/**
  \brief Define CIR rx symbol description
*/
typedef struct hal_cir_rx_symdesc_s {
    u16 time_us;                /*!< Set the rx symbol time, the unit is us  */ 
    cir_sym_t symbol;           /*!< Set the rx symbol   */
    cir_sym_type_t symtype;     /*!< Set the rx symbol type   */
    u16 time_tolerance_us;      /*!< Set the the time tolerance of the rx symbol for checking the symbol is valid */
    u16 carrier_tolerance_cnt;  /*!< Set the the carrier tolerance of the rx symbol for checking the symbol is valid */
} hal_cir_rx_symdesc_t, *phal_cir_rx_symdesc_t;

/**
  \brief Separate one receiving symbol into two symbols  
*/
typedef struct hal_cir_symsprt_s {
    cir_sym_t symbol_in;            /*!< Set the rx separated symbol  */ 
    cir_sym_t symbol_out_first;     /*!< Set the first generated symbol by separating  */ 
    cir_sym_t symbol_out_second;    /*!< Set the second generated symbol by separating */  
} hal_cir_symsprt_t, *phal_cir_symsprt_t;

/**
  \brief Two symbols normally become the encoding data
*/
typedef struct hal_cir_sym_in_s {
    cir_sym_t symbol_in_first;      /*!< Set the first symbol  */ 
    cir_sym_t symbol_in_second;     /*!< Set the second symbol  */ 
} hal_cir_sym_in_t, *phal_cir_sym_in_t;

/**
  \brief Describe tx protocol frame for CIR HAL
*/
typedef struct hal_cir_tx_protocol_frame_s {  
    cir_sym_t tx_start_sym[2];      /*!< Record the tx symbol of encoding the start symbol  */ 
    u8  tx_start_len;               /*!< Record the symbol length of encoding the start symbol */ 
    cir_sym_t tx_bit0_sym[2];       /*!< Record the tx symbol of encoding bit0  */ 
    u8  tx_bit0_len;                /*!< Record the symbol length of encoding bit0  */ 
    cir_sym_t tx_bit1_sym[2];       /*!< Record the tx symbol of encoding bit1  */ 
    u8  tx_bit1_len;                /*!< Record the symbol length of encoding bit1  */ 
    cir_sym_t tx_end_sym[2];        /*!< Record the tx symbol of encoding the end symbol  */ 
    u8  tx_end_len;                 /*!< Record the symbol length of encoding the end symbol */ 
    u32 tx_payload;                 /*!< Record the encoding payload*/ 
} hal_cir_tx_protocol_frame_t, *phal_cir_tx_protocol_frame_t;

/**
  \brief Describe rx protocol frame and set the parameter for CIR HAL
*/
typedef struct hal_cir_rx_protocol_frame_s { 
    u8 cir_format;                      /*!< Record the protocol format  */ 
    cir_rx_status_t cir_format_result;  /*!< Record the rx status  */ 
    u16 time_tolerance_us;              /*!< Record the the time tolerance of the rx symbol */
    u16 carrier_tolerance_cnt;          /*!< Record the the carrier tolerance of the rx symbol */
    cir_irq_user_cb_t irq_rx_end_cb;    /*!< Record the rx end callback function */
    void *irq_rx_end_arg;               /*!< Record the argument of the rx end callback function */
} hal_cir_rx_protocol_frame_t, *phal_cir_rx_protocol_frame_t;

/**
  \brief Set the tx parameter of the tx protocol frame for CIR API
*/
typedef struct hal_cir_tx_protocol_setting_s {  
    cir_init_value_t output_init;       /*!< Set the tx initial level   */ 
    cir_carrier_t carrier;              /*!< Set the protocol has the carrier site or not   */ 
    cir_sclkdiv_t tx_sclkdiv;           /*!< Set tx sclk to divide   */ 
    cir_irq_user_cb_t irq_tx_end_cb;    /*!< Set the tx end callback function */
    void *irq_tx_end_arg;               /*!< Set the argument of the tx end callback function */
} hal_cir_tx_protocol_setting_t, *phal_cir_tx_protocol_setting_t;

/**
  \brief Set the rx parameter of the rx protocol frame for CIR API
*/
typedef struct hal_cir_rx_protocol_desc_s {  
    cir_init_value_t input_init;        /*!< Set the rx initial level   */ 
    cir_carrier_t carrier;              /*!< Set the protocol has the carrier site or not   */ 
    cir_sclkdiv_t rx_sclkdiv;           /*!< Set rx sclk to divide   */ 
    u16 symbol_time_tolerance_us;       /*!< Set the the time tolerance of the rx symbol */
    u16 carrier_tolerance_cnt;          /*!< Set the the carrier tolerance of the rx symbol */
    u16 check_frame_end_time_us;        /*!< Set the end time after receiving the last symbol */
    cir_irq_user_cb_t irq_rx_end_cb;    /*!< Set the rx end callback function */
    void *irq_rx_end_arg;               /*!< Set the argument of the rx end callback function */
} hal_cir_rx_protocol_desc_t, *phal_cir_rx_protocol_desc_t;

/**
  \brief The tx parameter table to describe the tx protocol . 
*/
typedef struct hal_cir_tx_protocol_s {  
    u32 carrier_frequency;                  /*!< Set the tx carrier frequency   */ 
    u16 symbol_01_time_us;                  /*!< Set the symbol01 duration   */ 
    u16 symbol_02_time_us;                  /*!< Set the symbol02 duration   */ 
    u16 symbol_03_time_us;                  /*!< Set the symbol03 duration   */ 
    u16 symbol_04_time_us;                  /*!< Set the symbol04 duration   */ 
    u16 symbol_05_time_us;                  /*!< Set the symbol05 duration   */ 
    u16 symbol_06_time_us;                  /*!< Set the symbol06 duration   */ 
    u16 symbol_07_time_us;                  /*!< Set the symbol07 duration   */ 

    cir_sym_t  tx_start_first_symbol   : 4; /*!< Set the tx first symbol of encoding the start symbol  */ 
    cir_sym_t  tx_start_second_symbol  : 4; /*!< Set the tx second symbol of encoding the start symbol  */ 
    cir_sym_t  tx_bit0_first_symbol    : 4; /*!< Set the tx first symbol of encoding bit0  */ 
    cir_sym_t  tx_bit0_second_symbol   : 4; /*!< Set the tx second symbol of encoding bit0  */ 
    cir_sym_t  tx_bit1_first_symbol    : 4; /*!< Set the tx first symbol of encoding bit1  */ 
    cir_sym_t  tx_bit1_second_symbol   : 4; /*!< Set the tx second symbol of encoding bit1  */ 
    cir_sym_t  tx_end_first_symbol     : 4; /*!< Set the tx first symbol of encoding the end symbol  */ 
    cir_sym_t  tx_end_second_symbol    : 4; /*!< Set the tx second symbol of encoding the end symbol  */ 

    cir_carrier_site_t  symbol_01_type  : 1;/*!< Set the symbol01 is the carrier site or not   */     
    cir_carrier_site_t  symbol_02_type  : 1;/*!< Set the symbol02 is the carrier site or not   */ 
    cir_carrier_site_t  symbol_03_type  : 1;/*!< Set the symbol03 is the carrier site or not   */ 
    cir_carrier_site_t  symbol_04_type  : 1;/*!< Set the symbol04 is the carrier site or not   */ 
    cir_carrier_site_t  symbol_05_type  : 1;/*!< Set the symbol05 is the carrier site or not   */ 
    cir_carrier_site_t  symbol_06_type  : 1;/*!< Set the symbol06 is the carrier site or not   */ 
    cir_carrier_site_t  symbol_07_type  : 1;/*!< Set the symbol07 is the carrier site or not   */ 
} hal_cir_tx_protocol_t, *phal_cir_tx_protocol_t;

/**
  \brief The rx parameter table to describe the rx protocol . 
*/
typedef struct hal_cir_rx_protocol_s {  
    u32 carrier_frequency;                          /*!< Set the rx carrier frequency   */ 
    u16 symbol_01_time_us;                          /*!< Set the symbol01 duration   */ 
    u16 symbol_02_time_us;                          /*!< Set the symbol02 duration   */ 
    u16 symbol_03_time_us;                          /*!< Set the symbol03 duration   */ 
    u16 symbol_04_time_us;                          /*!< Set the symbol04 duration   */ 
    u16 symbol_05_time_us;                          /*!< Set the symbol05 duration   */ 
    u16 symbol_06_time_us;                          /*!< Set the symbol06 duration   */ 
    u16 symbol_07_time_us;                          /*!< Set the symbol07 duration   */ 
    u16 symbol_08_time_us;                          /*!< Set the symbol08 duration   */ 

    cir_sym_t  rx_start_first_symbol_gp0   : 4;     /*!< Start to decode the first symbol of the group 0  */ 
    cir_sym_t  rx_start_second_symbol_gp0  : 4;     /*!< Start to decode the second symbol of the group 0  */ 
    cir_sym_t  rx_start_first_symbol_gp1   : 4;     /*!< Start to decode the first symbol of the group 1  */
    cir_sym_t  rx_start_second_symbol_gp1  : 4;     /*!< Start to decode the second symbol of the group 1  */ 
    cir_sym_t  rx_start_first_symbol_gp2   : 4;     /*!< Start to decode the first symbol of the group 2  */ 
    cir_sym_t  rx_start_second_symbol_gp2  : 4;     /*!< Start to decode the second symbol of the group 2  */ 
    cir_sym_t  rx_start_first_symbol_gp3   : 4;     /*!< Start to decode the first symbol of the group 3  */ 
    cir_sym_t  rx_start_second_symbol_gp3  : 4;     /*!< Start to decode the second symbol of the group 3  */ 
    
    cir_sym_t  rx_bit0_first_symbol_gp0    : 4;     /*!< Set the first symbol of the group 0 to decode bit 0  */ 
    cir_sym_t  rx_bit0_second_symbol_gp0   : 4;     /*!< Set the second symbol of the group 0 to decode bit 0  */ 
    cir_sym_t  rx_bit0_first_symbol_gp1    : 4;     /*!< Set the first symbol of the group 1 to decode bit 0  */ 
    cir_sym_t  rx_bit0_second_symbol_gp1   : 4;     /*!< Set the second symbol of the group 1 to decode bit 0  */ 
    
    cir_sym_t  rx_bit1_first_symbol_gp0    : 4;     /*!< Set the first symbol of the group 0 to decode bit 1  */
    cir_sym_t  rx_bit1_second_symbol_gp0   : 4;     /*!< Set the second symbol of the group 0 to decode bit 1  */
    cir_sym_t  rx_bit1_first_symbol_gp1    : 4;     /*!< Set the first symbol of the group 1 to decode bit 1  */      
    cir_sym_t  rx_bit1_second_symbol_gp1   : 4;     /*!< Set the second symbol of the group 1 to decode bit 1  */

    cir_sym_t  rx_separate_symbol_in_gp0       : 4; /*!< Set the rx separated symbol of the group 0  */  
    cir_sym_t  rx_separate_first_symbol_gp0    : 4; /*!< Set the first generated symbol of the group 0  */ 
    cir_sym_t  rx_separate_second_symbol_gp0   : 4; /*!< Set the second generated symbol of the group 0  */ 
    cir_sym_t  rx_separate_symbol_in_gp1       : 4; /*!< Set the rx separated symbol of the group 1  */  
    cir_sym_t  rx_separate_first_symbol_gp1    : 4; /*!< Set the first generated symbol of the group 1  */
    cir_sym_t  rx_separate_second_symbol_gp1   : 4; /*!< Set the second generated symbol of the group 1  */

    cir_carrier_site_t  symbol_01_type  : 1;        /*!< Set the symbol01 is the carrier site or not   */  
    cir_carrier_site_t  symbol_02_type  : 1;        /*!< Set the symbol02 is the carrier site or not   */            
    cir_carrier_site_t  symbol_03_type  : 1;        /*!< Set the symbol03 is the carrier site or not   */  
    cir_carrier_site_t  symbol_04_type  : 1;        /*!< Set the symbol04 is the carrier site or not   */  
    cir_carrier_site_t  symbol_05_type  : 1;        /*!< Set the symbol05 is the carrier site or not   */  
    cir_carrier_site_t  symbol_06_type  : 1;        /*!< Set the symbol06 is the carrier site or not   */  
    cir_carrier_site_t  symbol_07_type  : 1;        /*!< Set the symbol07 is the carrier site or not   */  
    cir_carrier_site_t  symbol_08_type  : 1;        /*!< Set the symbol08 is the carrier site or not   */  
} hal_cir_rx_protocol_t, *phal_cir_rx_protocol_t;

/**
  \brief  The data structure for an CIR port HAL operations.
*/
typedef struct hal_cir_adapter_s {
    CIR_Type *base_addr;                    /*!< The CIR common register base address */
    cir_pin_sel_t pin_sel;                  /*!< The CIR pin mux selection */
    cir_app_pin_sel_t app_pin_sel;          /*!< The CIR pin mux for the application */
    cir_isr_t cir_isr_req;                  /*!< Record the CIR isr */
    cir_isr_t cir_isr_req_ever;             /*!< Record the CIR isr */

    u32 cir_sclk_fq;                        /*!< Record the CIR SCLK */
    u32 carrier_fq_hw;                      /*!< Record the tx initial result */ 
    u32 tx_tick_fq;                         /*!< Record the tx initial result */ 
    u32 half_carrier_time_us;               /*!< Record the tx initial result */ 
    
    u32 rx_tick_fq;                         /*!< Record the rx initial result */  
    u32 rx_carrier_fq;                      /*!< Record the rx initial result */ 

    u16 cari_hl_ratio;                      /*!< Record the high and low ratio for the carrier */  
    u8  monitor_rxprocess_dis;              /*!< Record CIR rx process in the monitor mode */  
        
    u8  start_len;                          /*!< The CIR tx irq is used */                            
    u8  end_len;                            /*!< The CIR tx irq is used */                               
    u8  tx_send_en;                         /*!< The CIR tx irq is used */  
    u32 *pframe_data;                       /*!< The CIR tx irq is used */   
    u8  data_len;                           /*!< The CIR tx irq is used */  
    u8  data_ptr;                           /*!< The CIR tx irq is used */   
    
    u32 *recv_data;                         /*!< The CIR rx irq is used */   
    u8  recv_data_ptr;                      /*!< The CIR rx irq is used */  
    u32 recv_data_limit;                    /*!< The CIR rx irq is used */ 
    
    hal_cir_tx_protocol_frame_t tx_protocol_frame; /*!< Save the setting for tx protocol  */  
    hal_cir_rx_protocol_frame_t rx_protocol_frame; /*!< Save the setting for rx protocol  */  

    cir_irq_user_cb_t rxsym0_cb;            /*!< The start matching callback function of the group 0 */ 
    void *rxsym0_arg;                       /*!< The start matching argument of the group 0 */ 
    cir_irq_user_cb_t rxsym1_cb;            /*!< The start matching callback function of the group 1 */ 
    void *rxsym1_arg;                       /*!< The start matching argument of the group 1 */ 
    cir_irq_user_cb_t monitor_cb;           /*!< The start monitor callback function */ 
    void *monitor_arg;                      /*!< The start monitor argument  */ 
    cir_irq_user_cb_t cirsend_cb;           /*!< The tx end callback function */ 
    void *cirsend_arg;                      /*!< The tx end argument */ 
    cir_irq_user_cb_t cirrecv_cb;           /*!< The rx end callback function */ 
    void *cirrecv_arg;                      /*!< The rx end argument */ 
    cir_irq_user_cb_t cirie_cb;             /*!< The reserve callback function */ 
    void *cirie_arg;                        /*!< The reserve argument */ 
    cir_irq_user_cb_t filter_cb;            /*!< The start filter callback function */ 
    void *filter_arg;                       /*!< The start filter argument  */ 
    
} hal_cir_adapter_t, *phal_cir_adapter_t;

/**
  \brief  The data structure to handle multiple CIR adapters.
*/
typedef struct hal_cir_group_adapter_s {
    volatile uint32_t critical_lv;                  /*!< to record CIR HAL enter critical section level */
    hal_cir_adapter_t *pcir_adapter[MaxCirNum];     /*!< All the CIR adapters of this platform */
    irq_handler_t   irq_fun[MaxCirNum];             /*!< the IRQ handler for different CIR adapters */
} hal_cir_group_adapter_t, *phal_cir_group_adapter_t;

/// @cond DOXYGEN_ROM_HAL_API

/** 
 * @addtogroup ls_hal_cir_rom_func CIR HAL ROM APIs.
 * @{
 */

void hal_cir_irq_handler_rtl8195blp (void *hid);
void hal_cir_irq_reg_rtl8195blp (irq_handler_t handler);
void hal_cir_irq_unreg_rtl8195blp (void);

void hal_cir_init_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_pin_sel_t pin_sel, cir_app_pin_sel_t app_pin_sel);
void hal_cir_deinit_rtl8195blp (hal_cir_adapter_t *pcir_adp);
void hal_cir_enter_critical_rtl8195blp (void);
void hal_cir_exit_critical_rtl8195blp (void);
HAL_Status hal_cir_tx_carrier_init_rtl8195blp (hal_cir_adapter_t *pcir_adp, u32 carrier_fq, u32 tx_sclkdiv, u16 cari_hl_ratio);
HAL_Status hal_cir_rx_carrier_init_rtl8195blp (hal_cir_adapter_t *pcir_adp, u32 carrier_fq, u32 rx_sclkdiv);
HAL_Status hal_cir_set_tx_symbol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_tx_symdesc_t *psymdesc);
HAL_Status hal_cir_set_rx_symbol_rtl8195blp(hal_cir_adapter_t *pcir_adp, hal_cir_rx_symdesc_t *psymdesc);  
void hal_cir_set_rx_timeout_rtl8195blp(hal_cir_adapter_t *pcir_adp, u16 time_us);    
void hal_cir_rst_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_TRX_t cir_trx);
HAL_Status hal_cir_symbol_separate_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_symsprt_t *psymsprt, cir_sym_group_t group);
HAL_Status hal_cir_symbol_bit0_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group);
HAL_Status hal_cir_symbol_bit1_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group);
HAL_Status hal_cir_symbol_strm_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group);
void hal_cir_irq_strm_gp0_cb_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
void hal_cir_irq_strm_gp1_cb_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
void hal_cir_set_monitor_rtl8195blp (hal_cir_adapter_t *pcir_adp, u32 monitor_data, u32 monitor_cnt, BOOL en);
void hal_cir_irq_monitor_cb_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);

void hal_cir_irq_send_cb_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
void hal_cir_recv_rtl8195blp (hal_cir_adapter_t *pcir_adp, u32 *data, u32 data_limit);
void hal_cir_irq_recv_cb_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);

void hal_cir_irq_ie_cb_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
cir_sym_type_t hal_cir_get_carrier_init_level_rtl8195blp (cir_carrier_t carrier, cir_init_value_t value);

void hal_cir_set_tx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting, hal_cir_tx_protocol_t *pcir_tx_protocol);
void hal_cir_load_tx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_t *pcir_tx_protocol, cir_sym_type_t symtype_level, cir_sym_type_t symtype_carrier);

void hal_cir_set_rx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc, hal_cir_rx_protocol_t *pcir_rx_protocol);
void hal_cir_load_rx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_t *pcir_rx_protocol, cir_sym_type_t symtype_level, cir_sym_type_t symtype_carrier);

void hal_cir_protocol_recv_rtl8195blp (hal_cir_adapter_t *pcir_adp, u32 *data, u8 format, u32 data_32bits_num);

u32 hal_cir_data_reverse_rtl8195blp(u32 x);
void hal_cir_set_rx_filter_en_rtl8195blp (hal_cir_adapter_t *pcir_adp, BOOL en, u8 filter_sym_cnt);
void hal_cir_set_rx_filter_reset_rtl8195blp (hal_cir_adapter_t *pcir_adp);
HAL_Status hal_cir_set_rx_filter_timeout_rtl8195blp (hal_cir_adapter_t *pcir_adp, BOOL en, u32 ftime_us);
HAL_Status hal_cir_set_rx_filter_symbol_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_sym_t symbol, u8 symb_in_seq);
void hal_cir_irq_filter_cb_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);


void hal_cir_init_output_frame_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_sym_type_t symtype_level);
void hal_cir_send_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, u32 *data, u32 length);

void hal_cir_set_nec_tx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
void hal_cir_nec_send_rtl8195blp (hal_cir_adapter_t *pcir_adp, void *data, cir_nec_tx_format_t format);
void hal_cir_set_nec_rx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
void hal_cir_rx_nec_pre_irq_rtl8195blp(void *data);

void hal_cir_set_sony_sirc_tx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
void hal_cir_sony_sirc_send_rtl8195blp (hal_cir_adapter_t *pcir_adp, void *data, cir_sony_sirc_format_t format);
void hal_cir_set_sony_sirc_rx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
void hal_cir_rx_sony_sirc_pre_irq_rtl8195blp(void *data);

void hal_cir_set_philips_rc5_tx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
void hal_cir_philips_rc5_send_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_philips_rc5_format_t *data);
void hal_cir_set_philips_rc5_rx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
void hal_cir_rx_philips_rc5_pre_irq_rtl8195blp(void *data);

void hal_cir_set_jvc_tx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
void hal_cir_jvc_send_rtl8195blp (hal_cir_adapter_t *pcir_adp, void *data, cir_jvc_tx_format_t format);
void hal_cir_set_jvc_rx_protocol_rtl8195blp (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
void hal_cir_rx_jvc_pre_irq_rtl8195blp(void *data);

/** 
 *  @brief TX output enable/disable.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] tx_out_ctrl 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_tx_en_rtl8195blp (hal_cir_adapter_t *pcir_adp, BOOL tx_out_ctrl)
{
     pcir_adp->base_addr->ctrl_b.txen = tx_out_ctrl;    
}

/** 
 *  @brief RX input enable/disable.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] rx_out_ctrl 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_rx_en_rtl8195blp (hal_cir_adapter_t *pcir_adp, BOOL rx_in_ctrl)
{
     pcir_adp->base_addr->ctrl_b.rxen = rx_in_ctrl;    
}

/** 
 *  @brief Write the symbol to FIFO .
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] symbol The symbol is Symbol_01 ~ Symbol_08. 
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_send_tx_symbol_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_sym_t symbol)
{
     pcir_adp->base_addr->txwr_b.txwr = symbol;    
}

/** 
 *  @brief Control to enable the interrupt and mask the interrupt for matching the start symbol of SymGroup0. 
 * 
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] int_en 0: disable, 1:Enable to update cir isr and make the interrupt.
 *  @param[in] imr_en 0: disable, 1:Mask the interrupt and the cir isr still updated. 
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_strm_gp0_int_rtl8195blp (hal_cir_adapter_t *pcir_adp, BOOL int_en, BOOL imr_en)
{
    pcir_adp->base_addr->ier_b.ie_rxsym0strm = int_en;
    pcir_adp->base_addr->imr_b.im_rxsym0strm = imr_en;
}

/** 
 *  @brief Control to enable the interrupt and mask the interrupt for matching the start symbol of SymGroup1. 
 * 
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] int_en 0: disable, 1:Enable to update cir isr and make the interrupt.
 *  @param[in] imr_en 0: disable, 1:Mask the interrupt and the cir isr still updated. 
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_strm_gp1_int_rtl8195blp (hal_cir_adapter_t *pcir_adp, BOOL int_en, BOOL imr_en)
{
    pcir_adp->base_addr->ier_b.ie_rxsym1strm = int_en;
    pcir_adp->base_addr->imr_b.im_rxsym1strm = imr_en;
}

/** 
 *  @brief Cir decoder enable/disable.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] en 0: disable, 1: enable.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_decoder_en_rtl8195blp (hal_cir_adapter_t *pcir_adp, BOOL en)
{
     pcir_adp->base_addr->rxdcctrl_b.rxdc_en = en;    
}

/** 
 *  @brief  Close RX FIFO  is enabled/disabled.
 *
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] en 0: not close RX FIFO, 1: close RX FIFO.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_rxfifo_close_en_rtl8195blp (hal_cir_adapter_t *pcir_adp, BOOL en)
{
     pcir_adp->base_addr->rxdcctrl_b.rxfifodis = en;    
}

/** 
 *  @brief Control to enable the interrupt and mask the interrupt for the monitor.
 * 
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] int_en 0: disable, 1:Enable to update cir isr and make the interrupt.
 *  @param[in] imr_en 0: disable, 1:Mask the interrupt and the cir isr still updated. 
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_monitor_int_rtl8195blp (hal_cir_adapter_t *pcir_adp, BOOL int_en, BOOL imr_en)
{
    pcir_adp->base_addr->isr_b.is_monitor = 1;
    pcir_adp->base_addr->ier_b.ie_monitor = int_en;
    pcir_adp->base_addr->imr_b.im_monitor = imr_en;
}

/** 
 *  @brief Get the CIR decoded data. 
 * 
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The decoded data. 
 */
__STATIC_INLINE
u32 hal_cir_get_decode_data_rtl8195blp (hal_cir_adapter_t *pcir_adp)
{
    return (pcir_adp->base_addr->rxdcdata);
}

/** 
 *  @brief When the decoded data are bigger than 32 bits, this the first 32-bit data will are saved in rxdcdata_dp.
 * 
 *  @param[in]  pcir_adp The cir adapter.
 *
 *  @returns The first 32-bit decoded data.
 */
__STATIC_INLINE
u32 hal_cir_get_decode_data_dp_rtl8195blp (hal_cir_adapter_t *pcir_adp)
{
    return (pcir_adp->base_addr->rxdcdata_dp);
}

/** 
 *  @brief Get FIFO status.
 * 
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns FIFO status. [0]: RXRDY, [1]: TXFULL, [2]: TX2EMP. 
 */
__STATIC_INLINE
u32 hal_cir_fifo_status_rtl8195blp (hal_cir_adapter_t *pcir_adp)
{
    return (pcir_adp->base_addr->fsts);
}

/** 
 *  @brief Get the start matching isr status for the group 0.
 * 
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The start matching status. 0: no interrupt, 1: interrupt is pending.
 */
__STATIC_INLINE
BOOL hal_cir_get_start_match_gp0_status_rtl8195blp (hal_cir_adapter_t *pcir_adp)
{
    return (pcir_adp->cir_isr_req_ever.b.is_rxsym0strm);
}

/** 
 *  @brief Get the start matching isr status for the group 1.
 * 
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The start matching status. 0: no interrupt, 1: interrupt is pending.
 */
__STATIC_INLINE
BOOL hal_cir_get_start_match_gp1_status_rtl8195blp (hal_cir_adapter_t *pcir_adp)
{
    return (pcir_adp->cir_isr_req_ever.b.is_rxsym1strm);
}

/** 
 *  @brief Get the argument of the rx end callback function.
 * 
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The argument of the rx end callback function.
 */
__STATIC_INLINE
void* hal_cir_get_irq_rx_end_arg_from_adapter_rtl8195blp (hal_cir_adapter_t *pcir_adp)
{
    return (pcir_adp->rx_protocol_frame.irq_rx_end_arg);
}

/** 
 *  @brief Get the number of decoded bits.
 * 
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The number of decoded bits.
 */
__STATIC_INLINE
u32 hal_cir_recv_bit_length_rtl8195blp (hal_cir_adapter_t *pcir_adp)
{
    return (pcir_adp->base_addr->rxdatacnt);
}

/** 
 *  @brief Set the interrupt mask.
 * 
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] cir_imr The bit mask.
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_imr_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_imr_t cir_imr)
{
    pcir_adp->base_addr->imr = cir_imr.w;
}

/** 
 *  @brief Set the interrupt event.
 *  
 *  @param[in] pcir_adp The cir adapter.
 *  @param[in] cir_ier The bit event. 
 *
 *  @returns void
 */
__STATIC_INLINE
void hal_cir_set_ie_rtl8195blp (hal_cir_adapter_t *pcir_adp, cir_ier_t cir_ier)
{
    pcir_adp->base_addr->ier = cir_ier.w;
}

/** 
 *  @brief Get the interrupt pending status.
 *   
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The interrupt pending status.
 */
__STATIC_INLINE
u32 hal_cir_get_isr_rtl8195blp (hal_cir_adapter_t *pcir_adp)
{
    return (pcir_adp->base_addr->isr);
}

/** 
 *  @brief Get the RX decode status.
 *    
 *  @param[in] pcir_adp The cir adapter.
 *
 *  @returns The RX decode status.
 *                      0: Success. 
 *                      1: Repeat frame. 
 *                      2: Fail.
 *                      3: Repeat header.
 */
__STATIC_INLINE
cir_rx_status_t hal_cir_get_protocol_rx_status_rtl8195blp (hal_cir_adapter_t *pcir_adp)
{
    return (pcir_adp->rx_protocol_frame.cir_format_result); 
}

/** @} */ /* End of group ls_hal_cir_rom_func */
/// @endcond /* End of condition DOXYGEN_ROM_HAL_API */

/**
  \brief  The data structure of the stubs functions of the CIR HAL functions in ROM
*/
typedef struct hal_cir_func_stubs_s {
    hal_cir_group_adapter_t *pcir_gadapter;
    const uint8_t *pcir_pin_group;
    const hal_cir_tx_protocol_t *phal_cir_nec_tx_protocol;  
    const hal_cir_rx_protocol_t *phal_cir_nec_rx_protocol;
    const hal_cir_tx_protocol_t *phal_cir_sony_sirc_tx_protocol;
    const hal_cir_rx_protocol_t *phal_cir_sony_sirc_rx_protocol;
    const hal_cir_tx_protocol_t *phal_cir_philips_rc5_tx_protocol;
    const hal_cir_rx_protocol_t *phal_cir_philips_rc5_rx_protocol;
    const hal_cir_tx_protocol_t *phal_cir_jvc_tx_protocol;
    const hal_cir_rx_protocol_t *phal_cir_jvc_rx_protocol;
    void (*hal_cir_irq_handler) (void *hid);
    void (*hal_cir_irq_reg) (irq_handler_t handler);
    void (*hal_cir_irq_unreg) (void);
    void (*hal_cir_init) (hal_cir_adapter_t *pcir_adp, cir_pin_sel_t pin_sel, cir_app_pin_sel_t app_pin_sel);
    void (*hal_cir_deinit) (hal_cir_adapter_t *pcir_adp);
    void (*hal_cir_enter_critical) (void);
    void (*hal_cir_exit_critical) (void);
    HAL_Status (*hal_cir_tx_carrier_init) (hal_cir_adapter_t *pcir_adp, u32 carrier_fq, u32 tx_sclkdiv, u16 cari_hl_ratio);
    HAL_Status (*hal_cir_rx_carrier_init) (hal_cir_adapter_t *pcir_adp, u32 carrier_fq, u32 rx_sclkdiv);
    HAL_Status (*hal_cir_set_tx_symbol) (hal_cir_adapter_t *pcir_adp, hal_cir_tx_symdesc_t *psymdesc);
    HAL_Status (*hal_cir_set_rx_symbol) (hal_cir_adapter_t *pcir_adp, hal_cir_rx_symdesc_t *psymdesc);  
    void (*hal_cir_set_rx_timeout) (hal_cir_adapter_t *pcir_adp, u16 time_us); 
    void (*hal_cir_rst) (hal_cir_adapter_t *pcir_adp, cir_TRX_t cir_trx);
    HAL_Status (*hal_cir_symbol_separate) (hal_cir_adapter_t *pcir_adp, hal_cir_symsprt_t *psymsprt, cir_sym_group_t group);
    HAL_Status (*hal_cir_symbol_bit0) (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group);
    HAL_Status (*hal_cir_symbol_bit1) (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group);
    HAL_Status (*hal_cir_symbol_strm) (hal_cir_adapter_t *pcir_adp, hal_cir_sym_in_t *psym_in, cir_sym_group_t group);
    void (*hal_cir_irq_strm_gp0_cb) (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
    void (*hal_cir_irq_strm_gp1_cb) (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
    void (*hal_cir_set_monitor) (hal_cir_adapter_t *pcir_adp, u32 monitor_data, u32 monitor_cnt, BOOL en);
    void (*hal_cir_irq_monitor_cb) (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
    void (*hal_cir_send_protocol) (hal_cir_adapter_t *pcir_adp, u32 *data, u32 length);
    void (*hal_cir_irq_send_cb) (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
    void (*hal_cir_recv) (hal_cir_adapter_t *pcir_adp, u32 *data, u32 data_limit);
    void (*hal_cir_irq_recv_cb) (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
    void (*hal_cir_irq_ie_cb) (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);
    cir_sym_type_t (*hal_cir_get_carrier_init_level) (cir_carrier_t carrier, cir_init_value_t value);
    void (*hal_cir_init_output_frame) (hal_cir_adapter_t *pcir_adp, cir_sym_type_t symtype_level);
    void (*hal_cir_set_tx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting, hal_cir_tx_protocol_t *pcir_tx_protocol);
    void (*hal_cir_set_rx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc, hal_cir_rx_protocol_t *pcir_rx_protocol);
    u32 (*hal_cir_data_reverse)(u32 x);
    void (*hal_cir_set_nec_tx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
    void (*hal_cir_nec_send) (hal_cir_adapter_t *pcir_adp, void *data, cir_nec_tx_format_t format);
    void (*hal_cir_set_nec_rx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
    void (*hal_cir_protocol_recv) (hal_cir_adapter_t *pcir_adp, u32 *data, u8 format, u32 data_32bits_num);
    void (*hal_cir_rx_nec_pre_irq) (void *data);
    void (*hal_cir_set_sony_sirc_tx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
    void (*hal_cir_sony_sirc_send) (hal_cir_adapter_t *pcir_adp, void *data, cir_sony_sirc_format_t format);
    void (*hal_cir_set_sony_sirc_rx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
    void (*hal_cir_rx_sony_sirc_pre_irq) (void *data);
    void (*hal_cir_set_philips_rc5_tx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
    void (*hal_cir_philips_rc5_send) (hal_cir_adapter_t *pcir_adp, hal_cir_philips_rc5_format_t *data);
    void (*hal_cir_set_philips_rc5_rx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
    void (*hal_cir_rx_philips_rc5_pre_irq) (void *data);    
    void (*hal_cir_set_jvc_tx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_setting_t *ptx_protocol_setting);
    void (*hal_cir_jvc_send) (hal_cir_adapter_t *pcir_adp, void *data, cir_jvc_tx_format_t format);
    void (*hal_cir_set_jvc_rx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_desc_t *prx_protocol_desc);
    void (*hal_cir_rx_jvc_pre_irq) (void *data);
    void (*hal_cir_load_tx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_tx_protocol_t *pcir_tx_protocol, cir_sym_type_t symtype_level, cir_sym_type_t symtype_carrier);
    void (*hal_cir_load_rx_protocol) (hal_cir_adapter_t *pcir_adp, hal_cir_rx_protocol_t *pcir_rx_protocol, cir_sym_type_t symtype_level, cir_sym_type_t symtype_carrier);
    void (*hal_cir_set_rx_filter_en) (hal_cir_adapter_t *pcir_adp, BOOL en, u8 filter_sym_cnt);
    void (*hal_cir_set_rx_filter_reset) (hal_cir_adapter_t *pcir_adp);
    HAL_Status (*hal_cir_set_rx_filter_timeout) (hal_cir_adapter_t *pcir_adp, BOOL en, u32 ftime_us);
    HAL_Status (*hal_cir_set_rx_filter_symbol) (hal_cir_adapter_t *pcir_adp, cir_sym_t symbol, u8 symb_in_seq);
    void (*hal_cir_irq_filter_cb) (hal_cir_adapter_t *pcir_adp, cir_irq_user_cb_t callback, void *arg);    
    uint32_t reserved[16];  // reserved space for next ROM code version function table extending.
} hal_cir_func_stubs_t;

/** @} */ /* End of group ls_hal_cir */

#endif  // end of "#define _RTL8195BLP_CIR_H_"

