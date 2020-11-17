#include "FreeRTOS.h"
#include "task.h"
#include "encoder_buffer_handler.h"

void enc_list_initial(struct enc_list_handle *enc_list)
{
    rtw_init_sema(&enc_list->enc_sema,0);
    rtw_init_listhead(&enc_list->enc_acti_list);
    rtw_init_listhead(&enc_list->enc_idle_list);
}

void enc_list_deinitial(struct enc_list_handle *enc_list)
{
    rtw_free_sema(&enc_list->enc_sema);
}

void enc_set_idle_buffer(struct enc_list_handle *enc_list,struct enc_buf_data *enc_data)
{       
    rtw_list_insert_tail(&enc_data->list, &enc_list->enc_idle_list);
}

void enc_set_acti_buffer(struct enc_list_handle *enc_list,struct enc_buf_data *enc_data)
{       
    rtw_list_insert_tail(&enc_data->list, &enc_list->enc_acti_list);
}

struct enc_buf_data *enc_get_idle_buffer(struct enc_list_handle *enc_list)
{
    struct enc_buf_data *enc_data;
    
    if(!rtw_is_list_empty(&enc_list->enc_idle_list)){
          enc_data = list_first_entry(&enc_list->enc_idle_list, struct enc_buf_data, list);
          rtw_list_delete(&enc_data->list);
          return enc_data;
    }else{
          return NULL;
    }
}

struct enc_buf_data *enc_get_acti_buffer(struct enc_list_handle *enc_list)
{
    struct enc_buf_data *enc_data;
    
    if(!rtw_is_list_empty(&enc_list->enc_acti_list)){
          enc_data = list_first_entry(&enc_list->enc_acti_list, struct enc_buf_data, list);
          rtw_list_delete(&enc_data->list);
          return enc_data;
    }else{
          return NULL;
    }
}
