/**
 ******************************************************************************
 *This file contains sensor configurations for AmebaPro platform
 ******************************************************************************
*/


#ifndef __SENSOR_H
#define __SENSOR_H

#ifdef __cplusplus
 extern "C" {
#endif 



/**
@code  
 The table below gives an overview of the hardware resources supported by each 
 AmebaPro EVAL board.
     - Sensor board: 

 =================================================================================================================+
   AmebaPro EVAL  | Sensor board |  
 =================================================================================================================+
   AmebaPro-EVAL   |  SC2232      |        
 -----------------------------------------------------------------------------------------------------------------+
   AmebaPro-EVAL   |  OV2735      |
 -----------------------------------------------------------------------------------------------------------------+
   AmebaPro-EVAL   |  HM2140      |
 -----------------------------------------------------------------------------------------------------------------+
 =================================================================================================================+
@endcode
*/
#define SENSOR_OV2735   		0x01
#define SENSOR_SC2232   		0x02
#define SENSOR_IMX307   		0x04
#define SENSOR_PS5260   		0x0C
#define SENSOR_GC2053       0x06
#define SENSOR_PS5270   		0x0F
#define SENSOR_ALL				0xff

#define SENSOR_HM2140   	0x03
#define SENSOR_SC4236       0x05
#define SENSOR_OV2740       0x07
#define SENSOR_GL3004       0x08
#define SENSOR_JXF37          0x09
#define SENSOR_SC2232H   	0x0A
#define SENSOR_SC2239   		0x0B
#define SENSOR_GC1054   		0x0D
#define SENSOR_PS5268   		0x0E

#define SENSOR_OV5640   		0x10

   
   
#define LIGHT_SENSOR_AP1522D  	0x01
#define LIGHT_SENSOR_AL3042   	0x02
#define LIGHT_SENSOR_AP1511B  	0x03

#define ISP_FW_FLASH   0x00
#define ISP_FW_DRAW    0x01

#define ISP_FW_INTERNAL  0x00
#define ISP_FW_USERSPACE 0x01

#define ISP_AUTO_SEL_DISABLE 0X00
#define ISP_AUTO_SEL_ENABLE  0X01

#define SENSOR_USE      	SENSOR_IMX307
#define SENSOR_AUTO_SEL         ISP_AUTO_SEL_ENABLE //Enalbe Auto select 
#if SENSOR_AUTO_SEL == 0X01 && SENSOR_USE == SENSOR_ALL
static const unsigned char sen_id[0x08]={SENSOR_OV2735,SENSOR_SC2232,SENSOR_IMX307,SENSOR_PS5260,SENSOR_GC2053,SENSOR_PS5270,SENSOR_ALL};//It need match with the above selection, it will scan the sequence from the array.
#endif
//#define LENS_USE      		LENS_YT3320
#define SENSOR_FPS			30
#define ISP_FW_LOCATION		ISP_FW_FLASH
#define ISP_FW_SPACE        ISP_FW_INTERNAL
#define SENSOR_DEFAULT 		0xFF  //It is for sensor all default value
#define SENSOR_FW_USER_ADDR 0x40220
#define SENSOR_FW_USER_SIZE 131072
   
#if SENSOR_USE == SENSOR_ALL
#define SENSOR_DEFAULT   SENSOR_SC2232 
#endif
   
#if (SENSOR_USE== SENSOR_OV2735 || SENSOR_DEFAULT == SENSOR_OV2735) //Sensor_OV2735
  #define ISP_PIN_IDX ISP_PIN_SEL_S0//ISP_PIN_SEL_S0: 2735 | ISP_PIN_SEL_S1: 2232  
#elif (SENSOR_USE ==  SENSOR_SC2232 || SENSOR_DEFAULT == SENSOR_SC2232)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_HM2140 || SENSOR_DEFAULT == SENSOR_HM2140)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_IMX307 || SENSOR_DEFAULT == SENSOR_IMX307)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_SC4236 || SENSOR_DEFAULT == SENSOR_SC4236)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_GC2053 || SENSOR_DEFAULT == SENSOR_GC2053) 
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_OV2740 || SENSOR_DEFAULT == SENSOR_OV2740)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_GL3004 || SENSOR_DEFAULT == SENSOR_GL3004)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_JXF37 || SENSOR_DEFAULT == SENSOR_JXF37)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_SC2232H || SENSOR_DEFAULT == SENSOR_SC2232H)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_SC2239 || SENSOR_DEFAULT == SENSOR_SC2239)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_PS5260 || SENSOR_DEFAULT == SENSOR_PS5260)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_GC1054 || SENSOR_DEFAULT == SENSOR_GC1054)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_PS5268 || SENSOR_DEFAULT == SENSOR_PS5268)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_PS5270 || SENSOR_DEFAULT == SENSOR_PS5270)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#elif (SENSOR_USE ==  SENSOR_OV5640 || SENSOR_DEFAULT == SENSOR_OV5640)
  #define ISP_PIN_IDX ISP_PIN_SEL_S1
#else	 
  #error "Please select first the sensor board to be used in sensor.h"
#endif
   
#if (SENSOR_USE== SENSOR_OV2735 || SENSOR_DEFAULT == OV2735)//Sensor_OV2735
  #define SENSOR_CLK_USE ISP_FREQ_24//ISP_PIN_SEL_S0: 2735 | ISP_PIN_SEL_S1: 2232  
#elif (SENSOR_USE ==  SENSOR_SC2232 || SENSOR_DEFAULT == SENSOR_SC2232)
  #define SENSOR_CLK_USE ISP_FREQ_27
#elif (SENSOR_USE ==  SENSOR_HM2140 || SENSOR_DEFAULT == SENSOR_HM2140)
  #define SENSOR_CLK_USE ISP_FREQ_24	
#elif (SENSOR_USE ==  SENSOR_IMX307 || SENSOR_DEFAULT == SENSOR_IMX307)
  #define SENSOR_CLK_USE ISP_FREQ_37_125
#elif (SENSOR_USE ==  SENSOR_SC4236  || SENSOR_DEFAULT == SENSOR_SC4236)
  #define SENSOR_CLK_USE ISP_FREQ_27
#elif (SENSOR_USE ==  SENSOR_GC2053  || SENSOR_DEFAULT == SENSOR_GC2053)
  #define SENSOR_CLK_USE ISP_FREQ_24
#elif (SENSOR_USE ==  SENSOR_OV2740   || SENSOR_DEFAULT == SENSOR_OV2740)
  #define SENSOR_CLK_USE ISP_FREQ_24
#elif (SENSOR_USE ==  SENSOR_GL3004   || SENSOR_DEFAULT == SENSOR_GL3004)
  #define SENSOR_CLK_USE ISP_FREQ_24
#elif (SENSOR_USE ==  SENSOR_JXF37   || SENSOR_DEFAULT == SENSOR_JXF37)
  #define SENSOR_CLK_USE ISP_FREQ_27
#elif (SENSOR_USE ==  SENSOR_SC2232H || SENSOR_DEFAULT == SENSOR_SC2232H)
  #define SENSOR_CLK_USE ISP_FREQ_27
#elif (SENSOR_USE ==  SENSOR_SC2239 || SENSOR_DEFAULT == SENSOR_SC2239)
  #define SENSOR_CLK_USE ISP_FREQ_27
#elif (SENSOR_USE ==  SENSOR_PS5260 || SENSOR_DEFAULT == SENSOR_PS5260)
  #define SENSOR_CLK_USE ISP_FREQ_27
#elif (SENSOR_USE ==  SENSOR_GC1054 || SENSOR_DEFAULT == SENSOR_GC1054)
  #define SENSOR_CLK_USE ISP_FREQ_27
#elif (SENSOR_USE ==  SENSOR_PS5268 || SENSOR_DEFAULT == SENSOR_PS5268)
  #define SENSOR_CLK_USE ISP_FREQ_24
#elif (SENSOR_USE ==  SENSOR_PS5270 || SENSOR_DEFAULT == SENSOR_PS5270)
  #define SENSOR_CLK_USE ISP_FREQ_27
#elif (SENSOR_USE ==  SENSOR_OV5640 || SENSOR_DEFAULT == SENSOR_OV5640)
  #define SENSOR_CLK_USE ISP_FREQ_24
#else
  #error "Please select first the sensor board to be used in sensor.h"
#endif   

#define LDC_STATE LDC_OFF //LDC_STATE is useless, initial state of LDC is defined in ISP FW now
	 
//#if LENS_USE== LENS_TK632
//  #define LDC_STATE LDC_OFF
//#elif LENS_USE ==  LENS_YT3320
//  #define LDC_STATE LDC_ON
//#elif LENS_USE ==  LENS_YTOT10046
//  #define LDC_STATE LDC_ON
//#elif LENS_USE ==  LENS_HX1350D
//  #define LDC_STATE LDC_ON
//#else
//  #error "Please select first the lens to be used in sensor.h"
//#endif   

/*************Auto multi sensor selection****************/
#define SENSOR_RESET_PIN 0X00
#define SENSOR_POWER_DONE_PIN 0X01
#define SENSOR_POWER_ENABLE_PIN 0X02

#define SENSOR_GPIO_OUTPUT 0X01
#define SENSOR_GPIO_INPUT 0X00
#define EN_DELAYTIME 5

#define SENSOR_POWER_ACTIVE

#ifdef SENSOR_POWER_ACTIVE
#define SWITCH_OFF 0x00
#define SWITCH_ON 0x01
#else
#define SWITCH_OFF 0x01
#define SWITCH_ON 0x00
#endif

#define CLOCK_SWITCH_OFF 0X00
#define CLOCK_SWITCH_ON  0X01

#define SENSOR_PIN_HIGH 0X01
#define SENSOR_PIN_LOW  0X00

#define SENSOR_CLOCK_SWITCH_REG 0xfe89

/*************Auto multi sensor selection****************/

#ifdef __cplusplus
}
#endif


#endif /* __AMEBAPRO_SENSOR_EVAL_H */
