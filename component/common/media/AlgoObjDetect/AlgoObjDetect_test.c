#include "AlgoObjDetect_util.h"
#include "AlgoObjDetect.h"
#include "AlgoObjDetect_test.h"

int draw_BB_all (
  unsigned char *img_in,
  OD_INIT_S *od_init_s,
  DET_RESULT_S *det_result
) {

  //Draw ROI box
  RECT_INFO roi_rect;
  roi_rect.PosX = od_init_s->roi_topx;
  roi_rect.PosY = od_init_s->roi_topy;
  roi_rect.Width = od_init_s->roi_width;
  roi_rect.Height = od_init_s->roi_height;

  draw_BB ( img_in,
            od_init_s,
            &roi_rect);


  int idx_result;
  for (idx_result = 0; idx_result < det_result->det_obj_num; idx_result++) {
/**
     PRINTF("pos_x %d pos_y %d Width %d Height %d\n",
            det_result->det_rect[idx_result].PosX,
            det_result->det_rect[idx_result].PosY,
            det_result->det_rect[idx_result].Width,
            det_result->det_rect[idx_result].Height);
**/
     draw_BB (
       img_in,
       od_init_s,
       &det_result->det_rect[idx_result]);
   }
}


int draw_BB (
  unsigned char *img_in,
  OD_INIT_S *od_init_s,
  RECT_INFO *rect_info
) {

    if ((rect_info->PosX < 0) ||
        (rect_info->PosX > od_init_s->in_width) ||
        (rect_info->PosX + rect_info->Width  > od_init_s->in_width) ||
        (rect_info->PosY < 0) ||
        (rect_info->PosY > od_init_s->in_height) ||
        (rect_info->PosY + rect_info->Height > od_init_s->in_height) 
    ){
      PRINTF("Error: Detection Bounding Box out of picture\n");
      return OBJDET_NG;
    }

    unsigned char *current_ptr; 
    unsigned char *current_str = img_in + 
                                 rect_info->PosY*od_init_s->in_width + 
                                 rect_info->PosX ;
    int index;


    //draw top line
    current_ptr = current_str;
    for (index = 0; index < rect_info->Width; index++) {
      *current_ptr++ = 255; //white
    }
    //draw left line
    current_ptr = current_str;
    for (index = 0; index < rect_info->Height; index++) {
      *current_ptr = 255; //white
       current_ptr += od_init_s->in_width;
    }
    //draw right line
    current_ptr = current_str + rect_info->Width;
    for (index = 0; index < rect_info->Height; index++) {
      *current_ptr = 255; //white
       current_ptr += od_init_s->in_width;
    }
    //draw bottom line
    current_ptr = current_str + rect_info->Height*od_init_s->in_width;
    for (index = 0; index < rect_info->Width; index++) {
      *current_ptr++ = 255; //white
    }

    return OBJDET_OK;

}
 
