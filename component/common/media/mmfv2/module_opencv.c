 /******************************************************************************
 *
 * Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
 *
 ******************************************************************************/

#include <stdint.h>
#include <stdlib.h>

#include "mmf2_module.h"

#include "module_opencv.h"

#include "AlgoObjDetect.h"
#include "AlgoObjDetect_util.h"


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

OD_INIT_S od_init_s;
DET_RESULT_S det_result;

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

//------------------------------------------------------------------------------
int opencv_handle(void* p, void* input, void* output)
{
    opencv_ctx_t *ctx = (opencv_ctx_t*)p;
	mm_queue_item_t* input_item = (mm_queue_item_t*)input;
	mm_queue_item_t* output_item = (mm_queue_item_t*)output;
	
	if (AlgoObjDetect_Run((unsigned char*)input_item->data_addr, &det_result)!= OBJDET_OK)
	{
		PRINTF("Check Error code\n\r");
	}	
	
	*ctx->ret_roi_count = det_result.det_obj_num;
	for (int idx_result = 0; idx_result < det_result.det_obj_num; idx_result++)
	{
		PRINTF("tpchua aab %d.  ",idx_result);
		PRINTF("pos_x %d\t pos_y %d\t Width %d\t Height %d\n\r",
				det_result.det_rect[idx_result].PosX,
				det_result.det_rect[idx_result].PosY,
				det_result.det_rect[idx_result].Width,
				det_result.det_rect[idx_result].Height);
		
		if(ctx->ret_roi){
			ctx->ret_roi[idx_result].x = det_result.det_rect[idx_result].PosX;
			ctx->ret_roi[idx_result].y = det_result.det_rect[idx_result].PosY;
			ctx->ret_roi[idx_result].w = det_result.det_rect[idx_result].Width;
			ctx->ret_roi[idx_result].h = det_result.det_rect[idx_result].Height;
		}
	}
	
	if(det_result.det_obj_num == 0) 
		PRINTF("No object in image\n\r");
    return 0;
}

int opencv_control(void *p, int cmd, int arg)
{
	opencv_ctx_t *ctx = (opencv_ctx_t *)p;
	
	switch(cmd){
	case CMD_OPENCV_SET_PARAMS:
		memcpy(&ctx->params, ((opencv_params_t*)arg), sizeof(opencv_params_t));
	#if ( OBJDET_TYPE == FULLBODY_DET)
		AlgoObjDetect_SetParam(PREPRO_GAMMA  ,20);
			PRINTF("user set prepro gamma %d\n",  AlgoObjDetect_GetParam(PREPRO_GAMMA));
	#endif		
		break;
	case CMD_OPENCV_GET_PARAMS:
        PRINTF("release date %d\n\r",     AlgoObjDetect_GetParam(REL_DATE));
        PRINTF("release version %d\n\r",  AlgoObjDetect_GetParam(REL_VERSION));
        PRINTF("release GIT Tag %d\n\r",  AlgoObjDetect_GetParam(REL_GIT_TAG));
        PRINTF("img width %d\n\r",        AlgoObjDetect_GetParam(IMG_WIDTH_CMD));
        PRINTF("img height %d\n\r",       AlgoObjDetect_GetParam(IMG_HEIGHT_CMD));
        PRINTF("img maxgrey %d\n\r",      AlgoObjDetect_GetParam(IMG_MAXGREY_CMD));
        PRINTF("prepro gamma %d\n\r",     AlgoObjDetect_GetParam(PREPRO_GAMMA));
        PRINTF("prepro histeq %d\n\r",    AlgoObjDetect_GetParam(PREPRO_HISTEQ));
        PRINTF("roi topx %d\n\r",         AlgoObjDetect_GetParam(ROI_TOPX_CMD));
        PRINTF("roi topy %d\n\r",         AlgoObjDetect_GetParam(ROI_TOPY_CMD));
        PRINTF("roi width %d\n\r",        AlgoObjDetect_GetParam(ROI_WIDTH_CMD));
        PRINTF("roi height %d\n\r",       AlgoObjDetect_GetParam(ROI_HEIGHT_CMD));
        PRINTF("minsize %d\n\r",          AlgoObjDetect_GetParam(OBJ_MINSIZE_CMD));
        PRINTF("maxsize %d\n\r",          AlgoObjDetect_GetParam(OBJ_MAXSIZE_CMD));
        PRINTF("win width %d\n\r",        AlgoObjDetect_GetParam(WIN_WIDTH_CMD));
        PRINTF("win height %d\n\r",       AlgoObjDetect_GetParam(WIN_HEIGHT_CMD));
        PRINTF("min neighbour %d\n\r",    AlgoObjDetect_GetParam(PAR_MINNEIGH_CMD));
        PRINTF("scalefactor %d\n\r",      AlgoObjDetect_GetParam(PAR_SCALEFACTOR_CMD));		
		
		memcpy(((opencv_params_t*)arg), &ctx->params, sizeof(opencv_params_t));
		break;
	case CMD_OPENCV_SET_ROI_BUF:
		ctx->ret_roi = (roi_t*)arg;
		break;
	case CMD_OPENCV_SET_ROI_COUNT:
		ctx->ret_roi_count = (int*)arg;
		break;
	}
	
    return 0;
}

void* opencv_destroy(void* p)
{
	opencv_ctx_t *ctx = (opencv_ctx_t *)p;
	
    if(ctx) free(ctx);
        
    return NULL;
}

void* opencv_create(void* parent)
{
    opencv_ctx_t* ctx = (opencv_ctx_t*)malloc(sizeof(opencv_ctx_t));
    if(!ctx) return NULL;
    memset(ctx, 0, sizeof(opencv_ctx_t));
    ctx->parent = parent;
	
    od_init_s.in_width        = INPUT_W;
    od_init_s.in_height       = INPUT_H;
    od_init_s.roi_topx        = INPUT_W/4;
    od_init_s.roi_topy        = 0;
    od_init_s.roi_width       = INPUT_W/2;
    od_init_s.roi_height      = INPUT_H;
    od_init_s.isUseDefaultROI = 0;	
	AlgoObjDetect_Init(&od_init_s);
		
	return ctx;
}


mm_module_t opencv_module = {
    .create = opencv_create,
    .destroy = opencv_destroy,
    .control = opencv_control,
    .handle = opencv_handle,
    
    .output_type = MM_TYPE_NONE,     
    .module_type = MM_TYPE_VDSP,
	.name = "opencv"
};
