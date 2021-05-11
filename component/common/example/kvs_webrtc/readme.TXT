This example is used to demo Amazon KVS(Kinesis Video Streams) with WebRTC

Please follow the instructions for various options


	1. Set the parameter CONFIG_EXAMPLE_KVS_WEBRTC to 1 in platform_opts.h file

	2. To read and write on SD card, set the parameters as below

		--> FATFS_DISK_SD to 1 in platform_opts.h under CONFIG_EXAMPLE_KVS_WEBRTC
		--> FF_MAX_SS to 512  for SD card in ffconf.h to define the maximum sector size supported
		--> FF_USE_MKFS to 0 in ffconf.h  

	3. Configure AWS KVS service setting in example_kvs_webrtc.h.
        

[Supported List] 
	Supported :
	    Ameba-pro