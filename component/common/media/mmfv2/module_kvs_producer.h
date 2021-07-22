#ifndef _MODULE_KVS_PRODUCER_H
#define _MODULE_KVS_PRODUCER_H

#include "mmf2_module.h"

#define CMD_KVS_PRODUCER_SET_PARAMS			MM_MODULE_CMD(0x00)
#define CMD_KVS_PRODUCER_GET_PARAMS			MM_MODULE_CMD(0x01)
#define CMD_KVS_PRODUCER_SET_APPLY			MM_MODULE_CMD(0x02)

/* Headers for KVS */
#include "kvs/restapi.h"
#include "kvs/stream.h"

typedef struct Kvs
{
    KvsServiceParameter_t xServicePara;
    KvsDescribeStreamParameter_t xDescPara;
    KvsCreateStreamParameter_t xCreatePara;
    KvsGetDataEndpointParameter_t xGetDataEpPara;
    KvsPutMediaParameter_t xPutMediaPara;

    StreamHandle xStreamHandle;
    PutMediaHandle xPutMediaHandle;

    VideoTrackInfo_t *pVideoTrackInfo;
    AudioTrackInfo_t *pAudioTrackInfo;
} Kvs_t;

typedef struct kvs_producer_ctx_s
{
	void* parent;
}kvs_producer_ctx_t;

extern mm_module_t kvs_producer_module;

#endif