#ifndef EXAMPLE_MEDIA_UVCD_H
#define EXAMPLE_MEDIA_UVCD_H

#include "sensor.h"
#include "video_common_api.h"
#include "platform_opts.h"
#if (SENSOR_USE== SENSOR_PS5270)
#define MAX_W 1440
#define MAX_H 1440
#else
#define MAX_W 1920
#define MAX_H 1080
#endif

#define UVCD_YUY2 1
#define UVCD_NV12 1
#define UVCD_MJPG 1
#define UVCD_H264 1

void example_media_uvcd(void);

#endif /* MMF2_EXAMPLE_H */