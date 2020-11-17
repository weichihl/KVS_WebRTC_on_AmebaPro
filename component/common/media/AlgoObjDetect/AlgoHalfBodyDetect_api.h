#ifndef __ALGOHALFBODYDETECT_API_H__
#define __ALGOHALFBODYDETECT_API_H__
#include "AlgoObjDetect.h"

int AlgoHalfBodyDetect_Init (
  OD_INIT_S *od_init_s
);

int AlgoHalfBodyDetect_Run (
  unsigned char* y_in,
  DET_RESULT_S * det_result
);

int AlgoHalfBodyDetect_Deinit (void);

void AlgoHalfBodyDetect_SetParam(cmd_e cmd, unsigned int value);

unsigned int AlgoHalfBodyDetect_GetParam(cmd_e cmd_id);

int AlgoHalfBodyDetect_Check(void);

#endif
