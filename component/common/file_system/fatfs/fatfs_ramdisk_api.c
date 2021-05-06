#include "platform_opts.h"
#if FATFS_DISK_RAM
#include "platform_stdlib.h"
#include "ff.h"
#include "fatfs_ramdisk_api.h"
#include "integer.h"
#include "stdint.h"
#include "stdio.h"
#include "fatfs_ext/inc/ff_driver.h"
#if defined(CONFIG_PLATFORM_8195BHP)
#include "timer_api.h"
#include "task.h"
#endif

////**** Implement the basic functions for RAM FatFs ****////
#define RAM_DISK_SZIE 1204*1024*2
#define SECTOR_SIZE_RAM		512
#define SECTOR_COUNT_RAM (RAM_DISK_SZIE/512)	//4096  // File system volumes = SECTOR_SIZE_RAM * SECTOR_COUNT_RAM

static char *diskMem = NULL;

DSTATUS RAM_disk_initialize(void){
    return RES_OK;
}

DSTATUS RAM_disk_status(void){
    return RES_OK;
}

DSTATUS RAM_disk_deinitialize(void){
	return RES_OK;
}

/* Read sector(s) --------------------------------------------*/
DRESULT RAM_disk_read(BYTE *buff, DWORD sector, UINT count){
    memcpy(buff, diskMem + sector * SECTOR_SIZE_RAM, count * SECTOR_SIZE_RAM);
    return RES_OK;
}

/* Write sector(s) --------------------------------------------*/
#if _USE_WRITE == 1
DRESULT RAM_disk_write(BYTE const *buff, DWORD sector, UINT count){
    memcpy(diskMem + sector * SECTOR_SIZE_RAM, buff, count * SECTOR_SIZE_RAM);
    return RES_OK;
}
#endif


/* IOCTL sector(s) --------------------------------------------*/
#if _USE_IOCTL == 1
DRESULT RAM_disk_ioctl(BYTE cmd, void * buff){
    DRESULT result;

    switch (cmd) {
        case CTRL_SYNC:
            result = RES_OK;
            break;
            
        case GET_BLOCK_SIZE:
        case CTRL_ERASE_SECTOR:
            result = RES_PARERR;
            break;

        case GET_SECTOR_SIZE:
            *(WORD *)buff = SECTOR_SIZE_RAM;
            result = RES_OK;
            break;

        case GET_SECTOR_COUNT:
            *(DWORD *)buff = SECTOR_COUNT_RAM;
            result = RES_OK;
            break;

        default:
            result = RES_ERROR;
            break;
    }

    return (result);
}
#endif


ll_diskio_drv RAM_disk_Driver ={
	.disk_initialize = RAM_disk_initialize,
	.disk_status = RAM_disk_status,
	.disk_read = RAM_disk_read,
	.disk_deinitialize = RAM_disk_deinitialize,
#if _USE_WRITE == 1
	.disk_write = RAM_disk_write,
#endif
#if _USE_IOCTL == 1
	.disk_ioctl = RAM_disk_ioctl,
#endif
	.TAG	= "RAM"
};


////**** API for the usage of the FatFs on RAM ****////

static fatfs_ram_params_t fatfs_ram_param;
static uint8_t fatfs_ram_init_done = 0;
static FIL     fatfs_ram_file;

int fatfs_ram_close(){
	
	if (fatfs_ram_init_done) {
		if(f_mount(NULL,fatfs_ram_param.drv, 1) != FR_OK){
			printf("FATFS unmount ram logical drive fail.\n");
		}

		if(FATFS_UnRegisterDiskDriver(fatfs_ram_param.drv_num))
			printf("Unregister ram disk driver from FATFS fail.\n");

		fatfs_ram_init_done = 0;
		
		free(diskMem);
	}
	return 0;
}

int fatfs_ram_init(){
	
	int ret = 0;
	
	if (!fatfs_ram_init_done) {
		diskMem = (char*)malloc(sizeof(char)*SECTOR_SIZE_RAM*SECTOR_COUNT_RAM);  // malloc 2MB ram memory size for file system
		memset(diskMem, 0, sizeof(char)*SECTOR_SIZE_RAM*SECTOR_COUNT_RAM);
                
		int Fatfs_ok = 0;
		FRESULT res1, res2;
		char path[64];
		char ram_test_fn[64] = "ram_drive_test.txt";
		
		// Register disk driver to Fatfs
		printf("Register ram disk driver to Fatfs.\n\r");
		fatfs_ram_param.drv_num = FATFS_RegisterDiskDriver(&RAM_disk_Driver);

		if(fatfs_ram_param.drv_num < 0){
			printf("Register ram disk driver to FATFS fail.\n\r");
		}else{
			Fatfs_ok = 1;
			fatfs_ram_param.drv[0] = fatfs_ram_param.drv_num + '0';
			fatfs_ram_param.drv[1] = ':';
			fatfs_ram_param.drv[2] = '/';
			fatfs_ram_param.drv[3] = 0;

			printf("Ram drive path: %s\n\r", fatfs_ram_param.drv);
		}
		if(!Fatfs_ok) {
			ret = -1;
			goto fatfs_init_err;
		}
		res1 = f_mount(&fatfs_ram_param.fs, fatfs_ram_param.drv, 1);
		// test ram
        printf("Test ram drive (file: %s)\n\n\r",ram_test_fn);
        strcpy(path, fatfs_ram_param.drv);
		sprintf(&path[strlen(path)],"%s",ram_test_fn);		
		res2 = f_open(&fatfs_ram_file, path, FA_OPEN_ALWAYS | FA_READ | FA_WRITE);
		if(res1 || res2){
			MKFS_PARM opt;
			opt.fmt = FM_ANY;
			opt.au_size = 0;
			ret = f_mkfs(fatfs_ram_param.drv, &opt, diskMem, 512);     // NULL
				if(ret != FR_OK){
				printf("Create FAT volume on Ram fail. (%d)\n\r", ret);
				goto fatfs_init_err;
			}
			if(f_mount(&fatfs_ram_param.fs, fatfs_ram_param.drv, 0)!= FR_OK){
				printf("FATFS mount logical drive on Ram fail.\n\r");
				goto fatfs_init_err;
 			}
            printf("ram mkfs and mount OK\n\r");
		}
		else {
			printf("ram mount OK\n\r");
		}
		fatfs_ram_init_done = 1;
	}
	else {
		ret = -2;
	}
	
	return 0;
	
fatfs_init_err:
	fatfs_ram_close();
	return ret;
}

int fatfs_ram_get_param(fatfs_ram_params_t *param)
{
	if (fatfs_ram_init_done){
		memcpy(param, &fatfs_ram_param, sizeof(fatfs_ram_params_t));
		return 0;
	}
	else {
		memset(param, 0, sizeof(fatfs_ram_params_t));
		return -1;
	}
}

#endif //FATFS_DISK_RAM