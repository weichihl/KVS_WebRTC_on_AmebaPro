ActionCAM Example Description
	SW
		V1: MP4 to SD recording
		V2: RTSP streaming
		V3: Snapshot
	HW
		LS GPIOA_13 is used to wakeup from Deep Sleep and to be a button for control

LS Setting
	Replace main_lp.c with actioncam\main_lp.c

HS Setting
	Replace main.c with actioncam\main.c
	For IAR, add actioncam\example_media_framework_modified.c, example_qr_code_scanner_modified.c, media_amebacam_broadcast_modified.c, mmf2_example_joint_test_rtsp_mp4_init_modified.c to "user" folder of application_is workspace in Project_is
	For GCC, add actioncam\example_media_framework_modified.c, example_qr_code_scanner_modified.c, media_amebacam_broadcast_modified.c, mmf2_example_joint_test_rtsp_mp4_init_modified.c to SRC_C in application.is.mk
	For GCC, remove example_media_framework_sd_detect.c from application.is.mk

	Modify project\realtek_amebapro_v0_example\inc\platform_opts.h
		#define CONFIG_EXAMPLE_ACTIONCAM    1

	Modify component\common\example\media_framework\example_media_framework.h
		//#define SNAPSHOT_TFTP_TYPE
		#define ENABLE_V3_JPEG						V3_JPEG_SNAPSHOT
		#define V3_RESOLUTION						VIDEO_1080P
		#define V3_JPEG_LEVEL						5

	Modify component\common\media\framework\jpeg_snapshot.c
		#define JPEG_SNAPSHOT_THRESHOLD 500

