This example is used to XXXXXX

Please follow the instructions for various options


	1. Set the parameter CONFIG_XXXXXXXX to 1 in platform_opts.h file

	2. To read and write on SD card, set the parameters as below

		--> FATFS_DISK_SD to 1 in platform_opts.h under CONFIG_EXAMPLE_FATFS and  FATFS_DISK_USB & FATFS_DISK_FLASH to 0
		--> _MAX_SS to 512  for SD card in ffconf.h to define the maximum sector size supported
		--> _USE_MKFS to 0 in ffconf.h  

        

[Supported List]
	Supported :
	    Ameba-pro