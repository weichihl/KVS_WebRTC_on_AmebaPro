#ifndef _FATFS_RAM_API_H
#define _FATFS_RAM_API_H
#include "ff.h"

typedef struct fatfs_ram_param_s{
	int drv_num;
	char drv[4];
	FATFS fs;
} fatfs_ram_params_t;

int fatfs_ram_init();
int fatfs_ram_close();
int fatfs_ram_get_param(fatfs_ram_params_t *param);

#endif //_FATFS_RAM_API_H