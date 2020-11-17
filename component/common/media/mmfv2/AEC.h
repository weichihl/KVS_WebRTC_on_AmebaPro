#ifndef AEC_H
#define AEC_H

#include <stdint.h>

typedef enum 
{
    SPEEX_AEC,
    WEBRTC_AEC,
    WEBRTC_AECM
}AEC_CORE;

typedef struct speex_aec_property
{
    void* speex_echo_state;
    void* speex_preprocess_state;
    void* speex_preprocess_state_tmp;

    int16_t frame_size;
    int32_t filter_length;
    int32_t sample_freq;
    int32_t* nosie;
}speex_aec_property;

typedef struct webrtc_aec_property
{
    void* webrtc_aec;
    void* webrtc_ns;
    void* webrtc_agc;

    int16_t frame_size;
    int32_t sample_freq;
    int32_t sndcard_sample_freq;
    int16_t sndcard_delay_ms;
}webrtc_aec_property;

typedef struct farend_pcm_pack
{
    unsigned long time_usec;
    int flag;

    unsigned char* pcm_buf;
    unsigned int length;
}farend_pcm_pack;

#define FAREND_PCM_PACK_INITIALIZER {0, 0, 0, 0};
#define FAREND_PCM_PACK_MIN_DIFF_TIME 500000 // usec
extern int PLAYBACK_DELAY;

/**
 *      - agc_mode           : 0 - Unchanged
 *                          : 1 - Adaptive Analog Automatic Gain Control -3dBOv
 *                          : 2 - Adaptive Digital Automatic Gain Control -3dBOv
 *                          : 3 - Fixed Digital Gain 0dB
 *
 *      - ns_mode	: 0: Mild, 1: Medium , 2: Aggressive
**/


void AEC_init(int16_t frame_size , int32_t sample_freq , AEC_CORE aec_core,
                  int speex_filter_length, int16_t agc_mode, int16_t compression_gain_db, uint8_t limiter_enable, int ns_mode, float snd_amplification);

#define AEC_init_default() AEC_init(160, 8000, SPEEX_AEC, 160*20, 1, 18, 0, 1, 1.0f)

int AEC_process(const int16_t* farend, const int16_t* nearend, int16_t* out);
void AEC_destory();
int AEC_agc(int16_t* out);


int speex_aec_playback_for_async(int16_t* farend, float snd_amplification);
#define speex_aec_playback_for_async_default(farend) speex_aec_playback_for_async(farend, 1.0f)

void set_sndcard_delay_ms_for_webrtc(int16_t ms);

void AGC_init(int32_t sample_freq, int16_t agc_mode, int16_t compression_gain_db, uint8_t limiter_enable);
void AGC_destory(void);
void AGC_process(int16_t frame_size, int16_t* out);

#endif // AEC_H
