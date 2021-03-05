#ifndef _EXAMPLE_KVS_H
#define _EXAMPLE_KVS_H

void example_kvs(void);

/* Enter your AWS KVS key here */
#define KVS_WEBRTC_ACCESS_KEY   "XXXXXXXX"
#define KVS_WEBRTC_SECRET_KEY   "XXXXXXXX"

/* Setting your signaling channel name */
#define KVS_WEBRTC_CHANNEL_NAME "My_KVS_Signaling_Channel"

/* log level */
#define KVS_WEBRTC_LOG_LEVEL    LOG_LEVEL_WARN  //LOG_LEVEL_VERBOSE

/* Audio format setting */
#define AUDIO_G711_MULAW        1
#define AUDIO_G711_ALAW         0
#define AUDIO_OPUS              0

/* Enable two-way audio communication */
//#define ENABLE_AUDIO_SENDRECV

/* Enable data channel */
//#define ENABLE_DATA_CHANNEL

#endif /* _EXAMPLE_FATFS_H */

