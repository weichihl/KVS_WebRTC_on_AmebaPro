#ifndef __COMMON_OBJDETECT__
#define __COMMON_OBJDETECT__

//Choose one algo only
#define FACE_DET      0xFF
#define HALFBODY_DET  0xFE
#define FULLBODY_DET  0xFC

//#define OBJDET_TYPE FULLBODY_DET
#define OBJDET_TYPE FACE_DET
//#define OBJDET_TYPE HALFBODY_DET


#if !defined(OBJDET_TYPE) && ((OBJDET_TYPE!=FACE_DET) && (OBJDET_TYPE!=HALFBODY_DET) && (OBJDET_TYPE!=FULLBODY_DET))
#error Please select at least one object detection algorithm !!
#endif


//Algo Definition
#define OBJDET_NUMDETECT_MAX   (20)

//Error code
#define OBJDET_OK               (0)
#define OBJDET_NG               (-1)
#define OBJDET_NG_PARAM         (-2)


//Setting command ID
typedef enum {
    REL_DATE            =    0,
    REL_VERSION         =    1,
    REL_GIT_TAG         =    2,
    IMG_WIDTH_CMD       =    3,
    IMG_HEIGHT_CMD      =    4,
    IMG_MAXGREY_CMD     =    5,
    PREPRO_GAMMA        =    6,
    PREPRO_HISTEQ       =    7,
    ROI_TOPX_CMD        =    8,
    ROI_TOPY_CMD        =    9,
    ROI_WIDTH_CMD       =    10,
    ROI_HEIGHT_CMD      =    11,
    OBJ_MINSIZE_CMD     =    12,
    OBJ_MAXSIZE_CMD     =    13,
    WIN_WIDTH_CMD       =    14,
    WIN_HEIGHT_CMD      =    15,
    PAR_MINNEIGH_CMD    =    16,
    PAR_SCALEFACTOR_CMD =    17 
}cmd_e;

typedef struct OD_INIT_S
{
    unsigned int  in_width;
    unsigned int  in_height;
    unsigned int  roi_topx;
    unsigned int  roi_topy;
    unsigned int  roi_width;
    unsigned int  roi_height;
    unsigned char isUseDefaultROI;

}OD_INIT_S;

typedef struct RECT_INFO {
    unsigned PosX;
    unsigned PosY;
    unsigned Width;
    unsigned Height;
} RECT_INFO;

typedef struct DET_RESULT_S{
    unsigned det_obj_num;  //Max is 20
    RECT_INFO det_rect[OBJDET_NUMDETECT_MAX];
} DET_RESULT_S;


/*
 *  ¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{
 * ¢y                                                                           ¢y
 * ¢y                       Function Prototype                                  ¢y
 * ¢y                                                                           ¢y
 *  ¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}
 */
#if ( OBJDET_TYPE == FULLBODY_DET )
#include "AlgoFullBodyDetect_api.h"
#elif ( OBJDET_TYPE == FACE_DET )
#include "AlgoFaceDetect_api.h"
#elif ( OBJDET_TYPE == HALFBODY_DET )
#include "AlgoHalfBodyDetect_api.h"
#endif


#endif //__COMMON_OBJDETECT__



