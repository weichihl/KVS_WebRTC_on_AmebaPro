#ifndef _EXAMPLE_KVS_PRODUCER_H_
#define _EXAMPLE_KVS_PRODUCER_H_

#define AWS_ACCESS_KEY          "xxxxxxxxxxxxxxxxxxxx"
#define AWS_SECRET_KEY          "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"

#define DEVICE_NAME             "DEV_12345678"

#define KVS_DATA_ENDPOINT_MAX_SIZE  ( 128 )

#define AWS_KVS_REGION      "us-east-1"
#define AWS_KVS_SERVICE     "kinesisvideo"
#define AWS_KVS_HOST        AWS_KVS_SERVICE "." AWS_KVS_REGION ".amazonaws.com"
#define HTTP_AGENT          "myagent"
#define KVS_STREAM_NAME     "my-kvs-stream"
//#define KVS_STREAM_NAME         "kvs_example_camera_stream"
#define DATA_RETENTION_IN_HOURS ( 2 )

#define USE_IOT_CERT                        ( 0 )
#if USE_IOT_CERT
#define CREDENTIALS_HOST    "xxxxxxxxxxxxxx.credentials.iot.us-east-1.amazonaws.com"
#define ROLE_ALIAS          "KvsCameraIoTRoleAlias"
#define THING_NAME          KVS_STREAM_NAME

#define ROOT_CA \
"-----BEGIN CERTIFICATE-----\n" \
"......" \
"-----END CERTIFICATE-----\n"

#define CERTIFICATE \
"-----BEGIN CERTIFICATE-----\n" \
"......" \
"-----END CERTIFICATE-----\n"

#define PRIVATE_KEY \
"-----BEGIN RSA PRIVATE KEY-----\n" \
"......" \
"-----END RSA PRIVATE KEY-----\n"
#endif // #if USE_IOT_CERT

#define HAS_AUDIO                           (1)

/* https://www.iana.org/assignments/media-types/media-types.xhtml */
#if HAS_AUDIO
#define MEDIA_TYPE                          "video/h264,audio/mulaw"
#else
#define MEDIA_TYPE                          "video/h264"
#endif

/* https://www.matroska.org/technical/codec_specs.html */
#define VIDEO_CODEC_NAME                    "V_MPEG4/ISO/AVC"
#define VIDEO_FPS                           30
//#define VIDEO_WIDTH                         1920
//#define VIDEO_HEIGHT                        1080
#define VIDEO_WIDTH                         1920
#define VIDEO_HEIGHT                        1080
#define VIDEO_NAME                          "my video"

#if HAS_AUDIO
//#define AUDIO_CODEC_NAME                    "A_PCM/INT/BIG"
//#define AUDIO_CODEC_NAME                    "A_PCM/INT/LIT"
//#define AUDIO_CODEC_NAME                    "A_MS/ACM"
#define AUDIO_CODEC_NAME                    "A_AAC"
#define AUDIO_FPS                           5
#define AUDIO_SAMPLING_RATE                 8000
#define AUDIO_CHANNEL_NUMBER                1
#define AUDIO_NAME                          "my audio"
#endif

void example_kvs_producer( void );

#endif // #ifndef _EXAMPLE_KVS_PRODUCER_H_