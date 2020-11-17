Example Description

This example is a doorbell reference design.

Requirement Components:

*Copy all files in "doorbell" folder to "src" folder.

HS:
For IAR, add files to "user" folder of application_is workspace in Project_is
1. doorbell_demo.c
2. firebase_message.c
3. icc_procedure.c
4. media_doorbell_broadcast.c
5. mmf2_h264_2way_audio_pcmu_doorbell_init.c
6. qrcode_scanner.c
For GCC, add files to SRC_C in application.is.mk
1. doorbell_demo.c
2. firebase_message.c
3. icc_procedure.c
4. media_doorbell_broadcast.c
5. mmf2_h264_2way_audio_pcmu_doorbell_init.c
6. qrcode_scanner.c

After adding example code, user should use platform_opts.h to switch on the example.
#define CONFIG_EXAMPLE_DOORBELL		1

ffconfig.h modify:
#define	_USE_LFN	2
#define	_FS_LOCK	6
#define _FS_REENTRANT	1

lS:
For IAR, add pir.c to "user" folder of application_lp workspace in Project_lp
For GCC, add pir.c to SRC_C in application.lp.mk

app_setting.h:
#define DOORBELL_TARGET_BROAD, when you used our doorbell target broad.
And the isp.bin in doorbell folder should be used to replace original isp.bin.
(\component\soc\realtek\8195b\misc\bsp\image\isp.bin) 