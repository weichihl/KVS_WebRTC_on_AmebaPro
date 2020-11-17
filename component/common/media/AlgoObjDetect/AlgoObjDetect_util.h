#ifndef __ALGO_OBJDETECT_UTIL_H__
#define __ALGO_OBJDETECT_UTIL_H__

#define AMEBA_PRO    0xff
#define AMEBA_PROII  0xfe
#define PC           0x1
//#define PLATFORM     PC
#define PLATFORM     AMEBA_PRO


#if (defined(PLATFORM) &&((PLATFORM==AMEBA_PRO) || (PLATFORM==AMEBA_PROII)))
#include "cmsis.h"
#include "shell.h"
#include "cmsis_os.h"               // CMSIS RTOS header file
#include <math.h>
#include "hal_timer.h"
//#include "basic_types.h"
//#include "section_config.h"
#endif

#if (defined(PLATFORM) &&(PLATFORM==PC) )
#include <stdlib.h> 
#include <math.h>
#endif

#define ALGO_MALLOC malloc
#define ALGO_FREE free

//some compiler treat undefined macro as 0
#if (defined(PLATFORM) &&((PLATFORM==AMEBA_PRO) || (PLATFORM==AMEBA_PROII)))
#define PRINTF dbg_printf
#else
#include "stdio.h"
#define PRINTF printf
#endif

#endif //__ALGO_OBJDETECT_UTIL_H__
