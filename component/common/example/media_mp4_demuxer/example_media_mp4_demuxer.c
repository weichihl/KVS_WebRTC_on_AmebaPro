#include <stdint.h>
#include "mp4_demuxer.h"
#include "fatfs_sdcard_api.h"
static FIL     w_file;
static void mp4_demuxer_thread(void *param){
		
        int i = 0;
        int size = 0;
        int bw = 0;
        unsigned char key_frame = 0;
        unsigned int video_timestamp = 0;
        unsigned int audio_timestamp = 0;
        unsigned int video_duration = 0;
        unsigned int audio_duration = 0;
        unsigned char *video_buf = NULL;
        unsigned char *audio_buf = NULL;
        char *file_name = NULL;
        char *mp4_name = "AMEBA_PRO.mp4";
        int ret = 0;
        
        mp4_demux *mp4_demuxer_ctx = NULL;
        mp4_demuxer_ctx = (mp4_demux *)malloc(sizeof(mp4_demux));
        if(mp4_demuxer_ctx == NULL){
              printf("It can't be allocated the buffer\r\n");
              goto mp4_create_fail;
        }else{
              memset(mp4_demuxer_ctx,0,sizeof(mp4_demux));
        }
        
        fatfs_sd_params_t *fatfs_params = NULL;
        fatfs_params = malloc(sizeof(fatfs_sd_params_t));
        if(fatfs_sd_init()<0){
                goto mp4_create_fail;
        }
        fatfs_sd_get_param(fatfs_params);
        set_mp4_demuxer_fatfs_param(mp4_demuxer_ctx,fatfs_params);
 
		
        file_name = malloc(128);
        memset(file_name,0,128);
        
        strcpy(file_name,fatfs_params->drv);
        sprintf(file_name+strlen(file_name),"%s",mp4_name);
        printf("mp4_demuxer->filename = %s\r\n",file_name);
        
        mp4_demuxer_open(mp4_demuxer_ctx,file_name);
        
        ret = f_open(&w_file,"0:/ameba_video.h264",FA_OPEN_ALWAYS | FA_READ | FA_WRITE);// res = f_open(&m_file, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
        if(ret != 0){
                printf("Can't open file\r\n");
                goto mp4_create_fail;
        }
        
        video_buf = (unsigned char *)malloc(mp4_demuxer_ctx->video_max_size);
        for(i =0;i<mp4_demuxer_ctx->video_len;i++){
		size = get_video_frame(mp4_demuxer_ctx,video_buf,i,&key_frame,&video_duration,&video_timestamp);
		f_write(&w_file,video_buf,size,&bw);
                //printf("Write video data = %d key = %d video_timestamp = %d\r\n",size,key_frame,video_timestamp);
        }
        printf("Write video done\r\n");
        f_close(&w_file);
        
        ret = f_open(&w_file,"0:/ameba_audio.aac",FA_OPEN_ALWAYS | FA_READ | FA_WRITE);// res = f_open(&m_file, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
        if(ret != 0){
                printf("Can't open file\r\n");
                goto mp4_create_fail;
        }
        
        audio_buf = (unsigned char *)malloc(mp4_demuxer_ctx->audio_max_size);
        for(i =0;i<mp4_demuxer_ctx->audio_len;i++){
		size = get_audio_frame(mp4_demuxer_ctx,audio_buf,i,&audio_duration,&audio_timestamp);
		f_write(&w_file,audio_buf,size,&bw);
                //printf("Write audio data %d timestamp = %d\r\n",size,audio_timestamp);
        }
        printf("Write audio done\r\n");
        f_close(&w_file);
        
        
        printf("mp4_demuxer_close\r\n");
        mp4_demuxer_close(mp4_demuxer_ctx);
        if(fatfs_params)
          free(fatfs_params);
        if(video_buf)
          free(video_buf);
        if(audio_buf)
          free(audio_buf);
        if(file_name)
          free(file_name);
        
EXIT:
mp4_create_fail:
        vTaskDelete(NULL);
}

void example_media_mp4_demuxer(void){
        if(xTaskCreate(mp4_demuxer_thread, ((const char*)"mp4_demuxer_thread"), 1024, NULL, 1 , NULL) != pdPASS)
            printf("\n\r%s xTaskCreate(mp4_demuxer_thread) failed\n\r", __FUNCTION__);
    return;
}