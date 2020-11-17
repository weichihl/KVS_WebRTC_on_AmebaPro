#ifndef _MODULE_OPENCV_H
#define _MODULE_OPENCV_H

#include <stdint.h>

#define CMD_OPENCV_SET_PARAMS     	MM_MODULE_CMD(0x00)  // set parameter
#define CMD_OPENCV_GET_PARAMS     	MM_MODULE_CMD(0x01)  // get parameter
#define CMD_OPENCV_SET_ROI_BUF		MM_MODULE_CMD(0x02)
#define CMD_OPENCV_SET_ROI_COUNT	MM_MODULE_CMD(0x03)



#define CMD_OPENCV_APPLY				MM_MODULE_CMD(0x20)  // for hardware module

typedef struct opencv_param_s{
    int dummy;
}opencv_params_t;

typedef struct roi_s{
	uint16_t x,y,w,h;
}roi_t;


typedef struct opencv_ctx_s{
    void* parent;
    
	opencv_params_t params;
	
	roi_t *ret_roi;
	int *ret_roi_count;
}opencv_ctx_t;

extern mm_module_t opencv_module;

#endif
