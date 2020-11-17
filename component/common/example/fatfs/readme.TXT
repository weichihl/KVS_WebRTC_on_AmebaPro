This example is used to read/write on various storage devices like SD card, USB, flash memory usig FAT Filesystem

Please follow the instructions for various options


	1. Set the parameter CONFIG_EXAMPLE_FATFS to 1 in platform_opts.h file

	2. To read and write on SD card, set the parameters as below

		--> FATFS_DISK_SD to 1 in platform_opts.h under CONFIG_EXAMPLE_FATFS and  FATFS_DISK_USB & FATFS_DISK_FLASH to 0
		--> _MAX_SS to 512  for SD card in ffconf.h to define the maximum sector size supported
		--> _USE_MKFS to 0 in ffconf.h  

	3. To read and write on USB, set the parameters as below [!! Only supports Ameba-1 !!]

		--> FATFS_DISK_USB to 1 in platform_opts.h under CONFIG_EXAMPLE_FATFS and  FATFS_DISK_SD & FATFS_DISK_FLASH to 0
		--> _MAX_SS to 512  for USB in ffconf.h to define the maximum sector size supported
		--> _USE_MKFS to 0 in ffconf.h  

	4. To read and write on Flash, set the parameters as below

		--> FATFS_DISK_FLASH to 1 in platform_opts.h under CONFIG_EXAMPLE_FATFS and FATFS_DISK_USB & FATFS_DISK_SD to 0
		--> _MAX_SS to 4096 for flash in ffconf.h to define the maximum sector size supported
		--> _USE_MKFS to 1 in ffconf.h to enable f_mkfs() function which creates FATFS volume on Flash
		--> 512 KB of on-board Ameba flash memory with the starting adddress of #define FLASH_APP_BASE  0x180000 is used for this example, refer flash_fatfs.c
			-> Change the FLASH_APP_BASE (starting address) according to your requirements
		--> The stack size of the example needs to be at least 4096
     
	5. To test dual FAT filesystem function, set the parameters as below [!! Only supports Ameba-Pro !!]

		--> Set both FATFS_DISK_FLASH and FATFS_DISK_SD to 1 in platform_opts.h
		--> Set _MAX_SS to 4096
		--> Set _USE_MKFS to 1 in ffconf.h to enable f_mkfs() function which creates FATFS volume on Flash
		--> Set _VOLUMES to 2 in ffconf.h				
		--> 512 KB of on-board Ameba flash memory with the starting adddress of #define FLASH_APP_BASE  0x180000 is used for this example, refer flash_fatfs.c
			-> Change the FLASH_APP_BASE (starting address) according to your requirements
		--> The stack size of the example needs to be at least 4096

        

[Supported List]
	Supported :
	    Ameba-1, Ameba-pro
	Source code not in project:
	    Ameba-z