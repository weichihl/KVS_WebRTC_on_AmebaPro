#ifndef __SECTION_CONFIG_H__
#define __SECTION_CONFIG_H__

#include "AlgoObjDetect_util.h"

#if (defined(PLATFORM) && (PLATFORM==PC))
#define OBJDETECT_TEXT_SECTION
#define OBJDETECT_DATA_SECTION
#define OBJDETECT_BSS_SECTION

// Use for face detect
#define OBJDETECT_FACE_RODATA_SECTION

// Use for halfbody detect
#define OBJDETECT_HALFBODY_RODATA_SECTION

// Use for fullbody detect
#define OBJDETECT_FULLBODY_SECTION
#endif


#if (defined(PLATFORM) &&((PLATFORM==AMEBA_PRO) || (PLATFORM==AMEBA_PROII)))
//#define SECTION(name) __attribute__ ((__section__(name)))
#include "platform_conf.h"
#include "basic_types.h"

/** for release **/
#define OBJDETECT_TEXT_SECTION 
//#define OBJDETECT_TEXT_SECTION SECTION(".objdetect.text")
#define OBJDETECT_DATA_SECTION SECTION(".objdetect.data")
#define OBJDETECT_BSS_SECTION SECTION(".objdetect.bss")

// Use for face detect
#define OBJDETECT_FACE_RODATA_SECTION LPDDR_DATA_SECTION
#define OBJDETECT_HALFBODY_RODATA_SECTION LPDDR_DATA_SECTION 
#define OBJDETECT_FULLBODY_SECTION LPDDR_DATA_SECTION

#endif

#endif
