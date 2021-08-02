#ifndef _MODULE_KVS_WEBRTC_H
#define _MODULE_KVS_WEBRTC_H

#include "mmf2_module.h"

#define CMD_KVS_WEBRTC_SET_PARAMS			MM_MODULE_CMD(0x00)
#define CMD_KVS_WEBRTC_GET_PARAMS			MM_MODULE_CMD(0x01)
#define CMD_KVS_WEBRTC_SET_APPLY			MM_MODULE_CMD(0x02)

#define KVS_WEBRTC_BITRATE      1*1024*1024

typedef struct kvs_webrtc_ctx_s
{
    void* parent;

}kvs_webrtc_ctx_t;

extern mm_module_t kvs_webrtc_module;

#endif /* _MODULE_KVS_WEBRTC_H */