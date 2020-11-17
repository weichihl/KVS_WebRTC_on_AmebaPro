#ifndef __ALGOFACEDETECT_API_H__
#define __ALGOFACEDETECT_API_H__
#include "AlgoObjDetect.h"

int AlgoFaceDetect_Init (
  OD_INIT_S *od_init_s
);

int AlgoFaceDetect_Run (
  unsigned char* y_in,
  DET_RESULT_S * det_result
);

int AlgoFaceDetect_Deinit (void);

void AlgoFaceDetect_SetParam(cmd_e cmd, unsigned int value);

unsigned int AlgoFaceDetect_GetParam(cmd_e cmd_id);

int AlgoFaceDetect_Check(void);

#endif
