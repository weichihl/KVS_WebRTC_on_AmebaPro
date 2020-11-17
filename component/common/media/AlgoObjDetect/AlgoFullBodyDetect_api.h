#ifndef __ALGOFULLBODYDETECT_API_H__
#define __ALGOFULLBODYDETECT_API_H__
#include "AlgoObjDetect.h"

int AlgoFullBodyDetect_Init (
  OD_INIT_S *od_init_s
);

int AlgoFullBodyDetect_Run (
  unsigned char* y_in,
  DET_RESULT_S * det_result
);

int AlgoFullBodyDetect_Deinit (void);

void AlgoFullBodyDetect_SetParam(cmd_e cmd, unsigned int value);

unsigned int AlgoFullBodyDetect_GetParam(cmd_e cmd_id);

int AlgoFullBodyDetect_Check(void);

#endif
