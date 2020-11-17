#include <stdlib.h>
//common header for all types of object detection
#include "AlgoObjDetect.h"
#include "AlgoObjDetect_util.h"
#include "tm9_cp3.h"


#if ( OBJDET_TYPE == FACE_DET )
#include "AlgoFaceDetect_api.h"     //Header to static lib
#elif ( OBJDET_TYPE == HALFBODY_DET )
#include "AlgoHalfBodyDetect_api.h"     //Header to static lib
#elif ( OBJDET_TYPE == FULLBODY_DET )
#include "AlgoFullBodyDetect_api.h"     //Header to static lib
#endif

#define INPUT_W 640
#define INPUT_H 360

int  AlgoObjDetect_Run (unsigned char *y_in, DET_RESULT_S *det_result);
void AlgoObjDetect_Init(OD_INIT_S*);
void AlgoObjDetect_Deinit(void);
void AlgoObjDetect_SetParam(cmd_e cmd, unsigned int value);
unsigned int AlgoObjDetect_GetParam(cmd_e cmd);

int main(void) {

    int idx_result;
    OD_INIT_S od_init_s;
    DET_RESULT_S det_result; //detection results - rect
    unsigned char* img_luma;

    od_init_s.in_width        = INPUT_W;
    od_init_s.in_height       = INPUT_H;
    od_init_s.roi_topx        = 0;
    od_init_s.roi_topy        = 0;
    od_init_s.roi_width       = 0;
    od_init_s.roi_height      = 0;
    od_init_s.isUseDefaultROI = 1;


    /*
     *  ¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{
     * ¢y                                                                           ¢y
     * ¢y          AlgoObjDetect_Init                                               ¢y
     * ¢y                                                                           ¢y
     *  ¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}
     */
    AlgoObjDetect_Init(&od_init_s);

    /*
     *  ¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{
     * ¢y                                                                           ¢y
     * ¢y          AlgoObjDetect_SetParam                                           ¢y
     * ¢y                                                                           ¢y
     *  ¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}
     */
        PRINTF("release date %d\n",     AlgoObjDetect_GetParam(REL_DATE));
        PRINTF("release version %d\n",  AlgoObjDetect_GetParam(REL_VERSION));
        PRINTF("release GIT Tag %d\n",  AlgoObjDetect_GetParam(REL_GIT_TAG));
        PRINTF("img width %d\n",        AlgoObjDetect_GetParam(IMG_WIDTH_CMD));
        PRINTF("img height %d\n",       AlgoObjDetect_GetParam(IMG_HEIGHT_CMD));
        PRINTF("img maxgrey %d\n",      AlgoObjDetect_GetParam(IMG_MAXGREY_CMD));
        PRINTF("prepro gamma %d\n",     AlgoObjDetect_GetParam(PREPRO_GAMMA));
        PRINTF("prepro histeq %d\n",    AlgoObjDetect_GetParam(PREPRO_HISTEQ));
        PRINTF("roi topx %d\n",         AlgoObjDetect_GetParam(ROI_TOPX_CMD));
        PRINTF("roi topy %d\n",         AlgoObjDetect_GetParam(ROI_TOPY_CMD));
        PRINTF("roi width %d\n",        AlgoObjDetect_GetParam(ROI_WIDTH_CMD));
        PRINTF("roi height %d\n",       AlgoObjDetect_GetParam(ROI_HEIGHT_CMD));
        PRINTF("minsize %d\n",          AlgoObjDetect_GetParam(OBJ_MINSIZE_CMD));
        PRINTF("maxsize %d\n",          AlgoObjDetect_GetParam(OBJ_MAXSIZE_CMD));
        PRINTF("win width %d\n",        AlgoObjDetect_GetParam(WIN_WIDTH_CMD));
        PRINTF("win height %d\n",       AlgoObjDetect_GetParam(WIN_HEIGHT_CMD));
        PRINTF("min neighbour %d\n",    AlgoObjDetect_GetParam(PAR_MINNEIGH_CMD));
        PRINTF("scalefactor %d\n",      AlgoObjDetect_GetParam(PAR_SCALEFACTOR_CMD));

#if ( OBJDET_TYPE == FULLBODY_DET)
    AlgoObjDetect_SetParam(PREPRO_GAMMA  ,20);
        PRINTF("user set prepro gamma %d\n",  AlgoObjDetect_GetParam(PREPRO_GAMMA));
#endif
//    AlgoObjDetect_SetParam(PAR_SCALEFACTOR_CMD  ,12);
//        PRINTF("user set scale factor %d\n",  AlgoObjDetect_GetParam(PAR_SCALEFACTOR_CMD));

    /*
     *  ¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{
     * ¢y                                                                           ¢y
     * ¢y          AlgoObjDetect_Run                                                ¢y
     * ¢y                                                                           ¢y
     *  ¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}
     */



    do
    {
    //User please assign luma input frame pointer 
    //img_luma = test_in;

    //init counter
    CP3_Set_Lo_Counter(COUNT_CYCLES, STOP_COUNTER, STOP_COUNTER, STOP_COUNTER);
    CP3_Set_Counter_Dual_Mode(NULL);
    //start counter
    CP3_Enable_Counter();
        if (AlgoObjDetect_Run(img_luma, &det_result)!= OBJDET_OK)
        {
            PRINTF("Check Error code\n");
        }
    CP3_Disable_Counter();
    PRINTF("cycle : %d\r\n",CP3_ReadAndClean_Counter(COUNTER0_LO));

        PRINTF("Find %d objects\n",det_result.det_obj_num);
        for (idx_result = 0; idx_result < det_result.det_obj_num; idx_result++)
        {
            PRINTF("tpchua aab %d.  ",idx_result);
            PRINTF("pos_x %d\t pos_y %d\t Width %d\t Height %d\n",
                    det_result.det_rect[idx_result].PosX,
                    det_result.det_rect[idx_result].PosY,
                    det_result.det_rect[idx_result].Width,
                    det_result.det_rect[idx_result].Height);
        }
    }while(1); //while loop

    /*
     *  ¢z¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢{
     * ¢y                                                                           ¢y
     * ¢y               AlgoObjDetect_Deinit                                        ¢y
     * ¢y                                                                           ¢y
     *  ¢|¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢w¢}
     */
    AlgoObjDetect_Deinit();

    return 0;
}


void AlgoObjDetect_Init(OD_INIT_S *od_init_s)
{
#if ( OBJDET_TYPE == FACE_DET )
    AlgoFaceDetect_Init
#endif
#if ( OBJDET_TYPE == HALFBODY_DET )
    AlgoHalfBodyDetect_Init
#endif
#if ( OBJDET_TYPE == FULLBODY_DET )
    AlgoFullBodyDetect_Init
#endif
    (
            od_init_s
    );

    return;
}


int AlgoObjDetect_Run (
        unsigned char *y_in,
        DET_RESULT_S  *det_result
)
{
    int det_result_state;
#if ( OBJDET_TYPE == FACE_DET )
    det_result_state = AlgoFaceDetect_Run
#endif
#if ( OBJDET_TYPE == HALFBODY_DET )
    det_result_state = AlgoHalfBodyDetect_Run
#endif
#if ( OBJDET_TYPE == FULLBODY_DET )
    det_result_state = AlgoFullBodyDetect_Run
#endif
    (
            y_in,
            det_result
    );


    return det_result_state;
}


void AlgoObjDetect_Deinit(void)
{
#if ( OBJDET_TYPE == FACE_DET )
    AlgoFaceDetect_Deinit();
#endif
#if ( OBJDET_TYPE == HALFBODY_DET )
    AlgoHalfBodyDetect_Deinit();
#endif
#if ( OBJDET_TYPE == FULLBODY_DET )
    AlgoFullBodyDetect_Deinit();
#endif

    return;
}

void AlgoObjDetect_SetParam(cmd_e cmd, unsigned int value)
{
#if ( OBJDET_TYPE == FACE_DET )
    AlgoFaceDetect_SetParam(cmd, value);
#endif
#if ( OBJDET_TYPE == HALFBODY_DET )
    AlgoHalfBodyDetect_SetParam(cmd, value);
#endif
#if ( OBJDET_TYPE == FULLBODY_DET )
    AlgoFullBodyDetect_SetParam(cmd, value);
#endif

    return;
}



unsigned int AlgoObjDetect_GetParam(cmd_e cmd)
{
#if ( OBJDET_TYPE == FACE_DET )
    return AlgoFaceDetect_GetParam(cmd);
#endif
#if ( OBJDET_TYPE == HALFBODY_DET )
    return AlgoHalfBodyDetect_GetParam(cmd);
#endif
#if ( OBJDET_TYPE == FULLBODY_DET )
    return AlgoFullBodyDetect_GetParam(cmd);
#endif

}
