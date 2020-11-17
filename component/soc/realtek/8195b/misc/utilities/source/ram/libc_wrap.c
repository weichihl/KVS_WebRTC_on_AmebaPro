/**************************************************************************//**
* @file     libc_wrap.c
* @brief    The wraper functions of ROM code to replace some of utility
*           functions in Compiler's Library.
* @version  V1.00
* @date     2018-08-15
*
* @note
*
******************************************************************************
*
* Copyright(c) 2007 - 2018 Realtek Corporation. All rights reserved.
*
* SPDX-License-Identifier: Apache-2.0
*
* Licensed under the Apache License, Version 2.0 (the License); you may
* not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an AS IS BASIS, WITHOUT
* WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*
******************************************************************************/
#if defined(CONFIG_PLATFORM_8195BHP) || defined(CONFIG_PLATFORM_8195BLP)
#include "platform_conf.h"
#endif
#include "basic_types.h"
#include "memory.h"

/* for GNU C++ */
#if defined(__GNUC__)
void* __dso_handle = 0;
#endif

#if defined(CONFIG_CMSIS_FREERTOS_EN) && (CONFIG_CMSIS_FREERTOS_EN != 0)
/**************************************************
* FreeRTOS memory management functions's wrapper to replace 
* malloc/free/realloc of GCC Lib.
**************************************************/
//#include "FreeRTOS.h"
// pvPortReAlloc currently not defined in portalbe.h
extern void* pvPortReAlloc( void *pv,  size_t xWantedSize );
extern void *pvPortMalloc( size_t xWantedSize );
extern void vPortFree( void *pv );

void* __wrap_malloc( size_t size )
{
	return pvPortMalloc(size);
}

void* __wrap_realloc( void *p, size_t size )
{
	return (void*)pvPortReAlloc(p, size);
}

void* __wrap_calloc( size_t n, size_t size )
{
	void* tmp = pvPortMalloc(n*size);
	if(tmp) rt_memset(tmp, 0, n*size);
	return tmp;
    //return (void*)calloc_freertos(n, size);
}

void __wrap_free( void *p )
{
	vPortFree(p);
}
#endif  //  #if defined(CONFIG_CMSIS_FREERTOS_EN) && (CONFIG_CMSIS_FREERTOS_EN != 0)

/**************************************************
* string and memory api wrap for compiler
*
**************************************************/

#if defined(CONFIG_PLATFORM_8195BHP) || defined(CONFIG_PLATFORM_8195BLP)
#include "stdio_port.h"
#include "rt_printf.h"

int __wrap_printf(const char * fmt,...)
{
	int count;
	va_list list;
	va_start(list, fmt);	
#if defined(CONFIG_BUILD_SECURE)	
	count = stdio_printf_stubs.printf_corel(stdio_printf_stubs.stdio_port_sputc, (void*)NULL, fmt, list);
#else
	count = stdio_printf_stubs.printf_core(stdio_printf_stubs.stdio_port_sputc, (void*)NULL, fmt, list);
#endif
	va_end(list);
	return count;
}

int __wrap_vprintf(const char *fmt, va_list args)
{
	int count;
#if defined(CONFIG_BUILD_SECURE)     
	count = stdio_printf_stubs.printf_corel(stdio_printf_stubs.stdio_port_sputc, (void*)NULL, fmt, args);
#else
	count = stdio_printf_stubs.printf_core(stdio_printf_stubs.stdio_port_sputc, (void*)NULL, fmt, args);
#endif
	return count;
}

int __wrap_sprintf(char *buf, const char * fmt,...)
{
	int count;
	va_list list;
	stdio_buf_t pnt_buf;
	
	pnt_buf.pbuf = buf;
	pnt_buf.pbuf_lim = 0;
	
	va_start(list, fmt);
#if defined(CONFIG_BUILD_SECURE)		
	count = stdio_printf_stubs.printf_corel(stdio_printf_stubs.stdio_port_bufputc, (void *)&pnt_buf, fmt, list);
#else
	count = stdio_printf_stubs.printf_core(stdio_printf_stubs.stdio_port_bufputc, (void *)&pnt_buf, fmt, list);
#endif
	*(pnt_buf.pbuf) = 0;
	va_end(list);
	
	return count;	
}

int __wrap_snprintf(char *buf, size_t size, const char *fmt,...)
{
	int count;
	va_list list;
	stdio_buf_t pnt_buf;
	
	pnt_buf.pbuf = buf;
	pnt_buf.pbuf_lim = buf + size - 1;  // reserve 1 byte for 'end of string'
	
	va_start(list,fmt);
#if defined(CONFIG_BUILD_SECURE)
	count = stdio_printf_stubs.printf_corel(stdio_printf_stubs.stdio_port_bufputc,(void *)&pnt_buf, fmt, list);
#else
	count = stdio_printf_stubs.printf_core(stdio_printf_stubs.stdio_port_bufputc,(void *)&pnt_buf, fmt, list);
#endif
	*(pnt_buf.pbuf) = 0;
	va_end(list);
	
	return count;	
}

int __wrap_vsnprintf(char *buf, size_t size, const char *fmt, va_list args)
{
	int count;
	stdio_buf_t pnt_buf;
	
	pnt_buf.pbuf = buf;
	pnt_buf.pbuf_lim = buf + size - 1;  // reserve 1 byte for 'end of string'
#if defined(CONFIG_BUILD_SECURE)
	count = stdio_printf_stubs.printf_corel(stdio_printf_stubs.stdio_port_bufputc,(void *)&pnt_buf, fmt, args);
#else
	count = stdio_printf_stubs.printf_core(stdio_printf_stubs.stdio_port_bufputc,(void *)&pnt_buf, fmt, args);
#endif
	*(pnt_buf.pbuf) = 0;
	
	return count;	
}

int __wrap_vsprintf(char *buf, const char *fmt, va_list args)
{
    int count;
    stdio_buf_t pnt_buf;

    pnt_buf.pbuf = buf;
    pnt_buf.pbuf_lim = 0;
#if defined(CONFIG_BUILD_SECURE)
    count = stdio_printf_stubs.printf_corel(stdio_printf_stubs.stdio_port_bufputc,(void *)&pnt_buf, fmt, args);
#else
	count = stdio_printf_stubs.printf_core(stdio_printf_stubs.stdio_port_bufputc,(void *)&pnt_buf, fmt, args);
#endif
    *(pnt_buf.pbuf) = 0;

    return count;	
}

int __wrap_puts(const char *str)
{
	return __wrap_printf("%s\n", str);
}

// define in AmebaPro utilites/include/memory.h
int __wrap_memcmp(const void *av, const void *bv, size_t len)
{
	return rt_memcmp(av, bv, len);
}

void *__wrap_memcpy( void *s1, const void *s2, size_t n )
{
	return rt_memcpy(s1, s2, n);
}

void *__wrap_memmove (void *destaddr, const void *sourceaddr, unsigned length)
{
	return rt_memmove (destaddr, sourceaddr, length);
}

void *__wrap_memset(void *dst0, int val, size_t length)
{
	return rt_memset(dst0, val, length);
}
// define in AmebaPro utilites/include/strporc.h
// replace by linking command
#include "strproc.h"
char *__wrap_strcat(char *dest,  char const *src)
{
	return strcat(dest, src);
}

char *__wrap_strchr(const char *s, int c)
{
	return strchr(s, c);
}

int __wrap_strcmp(char const *cs, char const *ct)
{
	return strcmp(cs, ct);
}

int __wrap_strncmp(char const *cs, char const *ct, size_t count)
{
	return strncmp(cs, ct, count);
}

int __wrap_strnicmp(char const *s1, char const *s2, size_t len)
{
	return strnicmp(s1, s2, len);
}


char *__wrap_strcpy(char *dest, char const *src)
{
	return strcpy(dest, src);
}


char *__wrap_strncpy(char *dest, char const *src, size_t count)
{
	return strncpy(dest, src, count);
}


size_t __wrap_strlcpy(char *dst, char const *src, size_t s)
{
	return strlcpy(dst, src, s);
}


size_t __wrap_strlen(char const *s)
{
	return strlen(s);
}


size_t __wrap_strnlen(char const *s, size_t count)
{
	return strnlen(s, count);
}


char *__wrap_strncat(char *dest, char const *src, size_t count)
{
	return strncat(dest, src, count);
}

char *__wrap_strpbrk(char const *cs, char const *ct)
{
	return strpbrk(cs, ct);
}


size_t __wrap_strspn(char const *s, char const *accept)
{
	return strspn(s, accept);
}


char *__wrap_strstr(char const *s1, char const *s2)
{
	return strstr(s1, s2);
}


char *__wrap_strtok(char *s, char const *ct)
{
	return strtok(s, ct);
}


size_t __wrap_strxfrm(char *dest, const char *src, size_t n)
{
	return strxfrm(dest, src, n);
}

char *__wrap_strsep(char **s, const char *ct)
{
	return strsep(s, ct);
}

double __wrap_strtod(const char *str, char **endptr)
{
	return strtod(str, endptr);
}

float __wrap_strtof(const char *str, char **endptr)
{
	return strtof(str, endptr);
}


long double __wrap_strtold(const char *str, char **endptr)
{
	return strtold(str, endptr);
}

long __wrap_strtol(const char *nptr, char **endptr, int base)
{
	return strtol(nptr, endptr, base);
}


long long __wrap_strtoll(const char *nptr, char **endptr, int base)
{
	return strtoll(nptr, endptr, base);
}


unsigned long __wrap_strtoul(const char *nptr, char **endptr, int base)
{
	return strtoul(nptr, endptr, base);
}


unsigned long long __wrap_strtoull(const char *nptr, char **endptr, int base)
{
	return strtoull(nptr, endptr, base);
}

int __wrap_atoi(const char *num)
{
	return atoi(num);
}

unsigned int __wrap_atoui(const char *num)
{
	return atoui(num);
}

long __wrap_atol(const char *num)
{
	return atol(num);
}

unsigned long __wrap_atoul(const char *num)
{
	return atoul(num);
}


unsigned long long __wrap_atoull(const char *num)
{
	return atoull(num);
}


double __wrap_atof(const char *str)
{
	return atof(str);
}	

#endif // CONFIG_PLATFORM_8195BHP

void __wrap_abort(void)
{
	__wrap_printf("\n\rabort execution\n\r");
	while(1);
}

/**************************************************
* FILE api wrap for compiler
*
**************************************************/
//#if defined(CONFIG_FATFS_WRAPPER) && (CONFIG_FATFS_WRAPPER == 1)
/*
--redirect fopen=__wrap_fopen
--redirect fclose=__wrap_fclose
--redirect fread=__wrap_fread
--redirect fwrite=__wrap_fwrite
--redirect fseek=__wrap_fseek
--redirect fsetpos=__wrap_fsetpos
--redirect fgetpos=__wrap_fgetpos
--redirect rewind=__wrap_rewind
--redirect fflush=__wrap_fflush
--redirect remove=__wrap_remove
--redirect rename=__wrap_rename
--redirect feof=__wrap_feof
--redirect ferror=__wrap_ferror
--redirect ftell=__wrap_ftell
--redirect fputc=__wrap_fputc
--redirect fputs=__wrap_fputs
--redirect fgets=__wrap_fgets
*/


#include <stdio.h>
#include "ff.h"

FILE * __wrap_fopen( const char * filename, const char * mode )
{
	FIL *fil = __wrap_malloc(sizeof(FIL));
	int do_seek_end = 0; // for mode "a" mapping
	
	if(!fil) 
		return NULL;
	
	uint8_t mode_mapping = 0;
	
	if(strchr(mode,'r'))
		mode_mapping |= FA_READ;
	if(strchr(mode,'w')) {
		if(strchr(mode,'x'))
			mode_mapping |= (FA_CREATE_NEW | FA_WRITE);
		else
			mode_mapping |= (FA_CREATE_ALWAYS | FA_WRITE);
	}
	if(strchr(mode,'a')) {
		mode_mapping |= (FA_OPEN_ALWAYS | FA_WRITE);
		do_seek_end = 1;
	}
	if(strchr(mode,'+'))
		mode_mapping |= (FA_READ | FA_WRITE);
	
	
	
	FRESULT res = f_open(fil, filename, mode_mapping);
	if(res != 0){
		vPortFree(fil);
		return NULL;
	}
	if(do_seek_end == 1) {
		f_lseek(fil, f_size(fil)); // Move r/w pointer to end of the file
	}
	printf("Open file mode 0x%x\n\r", mode_mapping);
	
	return (FILE*)fil;
}

int __wrap_fclose ( FILE * stream )
{
	FIL *fil = (FIL*)stream;
	
	FRESULT res = f_close(fil);
	vPortFree(fil);
	
	return -res;
}

size_t __wrap_fread ( void * ptr, size_t size, size_t count, FILE * stream )
{
	FIL *fil = (FIL*)stream;
	size_t br;
	
	FRESULT res = f_read(fil, ptr, size*count, &br);
	if(res > 0)
		return -1;
	
	return br;
}

size_t __wrap_fwrite ( const void * ptr, size_t size, size_t count, FILE * stream )
{
	// only support size = 1byte
	FIL *fil = (FIL*)stream;
	size_t bw;
	
	FRESULT res = f_write(fil, ptr, size*count, &bw);
	if(res > 0)
		return -1;
	
	return bw;
}

int  __wrap_fseek ( FILE * stream, long int offset, int origin ) 
{
	// only support origin = SEEK_SET(from Beginning of file)
	FIL *fil = (FIL*)stream;
	int size = f_size(fil);
	int curr = f_tell(fil);
	FRESULT res = -1;
	
	switch(origin){
	case SEEK_SET:
		res = f_lseek(fil, offset);	
		break;
	case SEEK_CUR:
		res = f_lseek(fil, curr + offset);	
		break;
	case SEEK_END:
		res = f_lseek(fil, size - offset);
		break;
	}
	
	return -res;
}

void  __wrap_rewind( FILE * stream )
{
	FIL *fil = (FIL*)stream;
	f_lseek(fil, 0);	
}

int __wrap_fgetpos(FILE * stream, fpos_t *  p)
{
	FIL *fil = (FIL*)stream;
#if defined(__ICCARM__)
	p->_Off = f_tell(fil);
#elif defined(__GNUC__)
	*p = (fpos_t)f_tell(fil);
#endif
	return 0;
}

int __wrap_fsetpos(FILE * stream, fpos_t *  p)
{
	FIL *fil = (FIL*)stream;
#if defined(__ICCARM__)
	int res = f_lseek(fil, p->_Off);
#elif defined(__GNUC__)
	int res = f_lseek(fil, (unsigned int)*p);
#endif
	return -res;
}

int  __wrap_fflush ( FILE * stream ) 
{
	FIL *fil = (FIL*)stream;
	
	if(stream == stdout || stream == stderr)
		return 0;
	
	FRESULT res = f_sync(fil);	
	
	return res;
}

int __wrap_remove ( const char * filename )
{
	FRESULT res = f_unlink(filename);	
	
	return res;
}

int __wrap_rename ( const char * oldname, const char * newname )
{
	FRESULT res = f_rename(oldname, newname);	
	
	return res;
}

int __wrap_feof ( FILE * stream )
{
	FIL *fil = (FIL*)stream;
	
	return f_eof(fil);
}

int __wrap_ferror ( FILE * stream )
{
	FIL *fil = (FIL*)stream;
	
	return f_error(fil);
}

long int __wrap_ftell ( FILE * stream )
{
	FIL *fil = (FIL*)stream;
	
	return f_tell(fil);
}

#include "stdio_port_func.h"
int __wrap_fputc ( int character, FILE * stream )
{
	FIL *fil = (FIL*)stream;
	
	if(stream == stdout || stream == stderr){
		stdio_port_putc(character);
		if(character=='\n')
			stdio_port_putc('\r');
		return character;
	}
	
	FRESULT res = f_putc((unsigned char)character, fil);	
	if(res > 0)
		return EOF;
	
	return character;
}

int __wrap_fputs ( const char * str, FILE * stream )
{
	FIL *fil = (FIL*)stream;
	
	FRESULT res = f_puts(str, fil);	
	if(res > 0)
		return EOF;
	
	return res;
}

char * __wrap_fgets ( char * str, int num, FILE * stream )
{
	FIL *fil = (FIL*)stream;
	
	char* res = f_gets(str, num, fil);	
	if(res == 0)
		return NULL;
	
	return str;
}


#include "fatfs_wrap.h"
#include "time.h"
DIR *__wrap_opendir(const char *name)
{
	DIR *pdir = __wrap_malloc(sizeof(DIR));
	
	FRESULT res = f_opendir(pdir, name);
	if(res > 0) {
		printf("opendir error (%d)\n\r", res);
		free(pdir);
		return NULL;
	}
	
	return pdir;
}

struct dirent *__wrap_readdir(DIR *pdir)
{
	FILINFO m_fileinfo;
	FRESULT res;
	char *fn;
	struct dirent *ent = __wrap_malloc(sizeof(struct dirent));
	
#if _USE_LFN
	static char lfn[_MAX_LFN + 1];
	m_fileinfo.lfname = lfn;
	m_fileinfo.lfsize = sizeof(lfn);
#endif
	res = f_readdir(pdir, &m_fileinfo);
	if (res != FR_OK) {
		printf("readdir: error (%d)\n\r", res);
		return NULL;
	}
	
	if (m_fileinfo.fname[0] == 0) {
		return NULL;
	}
#if _USE_LFN
	fn = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
	fn = m_fileinfo.fname;
#endif	
	ent->d_ino = 0;
	ent->d_off = 0;
	ent->d_reclen = m_fileinfo.fsize;
	if(m_fileinfo.fattrib & AM_DIR)
		ent->d_type = DT_DIR; // directory
	else
		ent->d_type = DT_REG; // regular file
#if _USE_LFN
	fn = *m_fileinfo.lfname ? m_fileinfo.lfname : m_fileinfo.fname;
#else
	fn = m_fileinfo.fname;
#endif
	sprintf(ent->d_name, "%s", fn);
	
	return ent;
}

int __wrap_closedir(DIR *dirp)
{
	FRESULT res = f_closedir(dirp);
	
	if(res > 0)
		return -1;
	
	return 0;
	
}

int __wrap_scandir(const char *dirp, struct dirent ***namelist,
				   int (*filter)(const struct dirent *),
				   int (*compar)(const struct dirent **, const struct dirent **))
{
	FRESULT res;    
	DIR *m_dir;
	FILINFO m_fileinfo;     
	char *filename;
	char path[1024];
	char file[512];  
	struct dirent *entry;
	struct dirent **list = *namelist;
	int count = 0;
	
	m_dir = __wrap_opendir(dirp);
	sprintf(path, "%s", dirp); 
	if(m_dir) {
		for (;;) {
			// read directory
			entry = __wrap_readdir(m_dir);
			
			if(!entry) {
				return count;//break;
			}
			filename = entry->d_name;
			//printf("%s  ", filename);
			list[count] = (struct dirent *)__wrap_malloc(sizeof(struct dirent));
			memcpy(list[count], entry, sizeof(struct dirent));
			
			count += 1;	
		}
	}
	// close directory
	res = __wrap_closedir(m_dir);
	
	return count;  
}

int __wrap_rmdir(const char *path) 
{
	FRESULT res = f_unlink(path);
	
	if(res > 0)
		return -1;
	
	return 0;
}

int __wrap_mkdir(const char *pathname, mode_t mode)
{
	// FatFS does not support "mode" parameter
	
	FRESULT res = f_mkdir(pathname);
	
	if(res > 0)
		return -1;
	
	return 0;
}

int __wrap_access(const char *pathname, int mode)
{
	FRESULT res;
	FILINFO finfo;
	
	res = f_stat(pathname, &finfo);
	
	printf("%s, check 0x%x\n\r", pathname, mode);
	
	if(res == FR_NO_FILE)
		return -1;
	
	
	
	if(mode & R_OK) {
		return 0;
	}
	
	if(mode & W_OK) {
		if(finfo.fattrib & AM_RDO) {
			return -1;
		}
		else {
			//printf("2  \n\r");
			return 0;
		}
	}
	
	if(mode & X_OK) {
		if(finfo.fattrib & AM_RDO)
			return -1;
		else
			return 0;
	}
	return 0;
}

int __wrap_stat(const char *path, struct stat *buf)
{
	FILINFO finfo;
	
	FRESULT res = f_stat(path, &finfo);
	if(res == FR_NO_FILE)
		return -1;
	
	buf->st_dev = 0;
	buf->st_ino = 0;
	
	mode_t st_mode = 0;
	if(finfo.fattrib & AM_DIR) {
		if(finfo.fattrib & AM_RDO)
			st_mode |= (S_IFDIR | 0x555);
		else
			st_mode |= (S_IFDIR | 0x777);
	}
	else {
		if(finfo.fattrib & AM_RDO)
			st_mode |= (S_IFREG | 0x555);
		else
			st_mode |= (S_IFREG | 0x777);        
	}
	
	buf->st_mode = st_mode;
	buf->st_nlink = 0;
	buf->st_uid = 0;
	buf->st_gid = 0;
	buf->st_rdev = 0;
	buf->st_size = finfo.fsize;
	buf->st_blksize = 0;
	buf->st_blocks = 0;
	
	struct tm tm  = {0};
	int year = (finfo.fdate >> 9) + 1980;
	int month = (finfo.fdate >> 5) & 15;
	int day = finfo.fdate & 31;
	int hour = finfo.ftime >> 11;
	int minute = (finfo.ftime >> 5) & 63;
	char timestr[512];
	snprintf(timestr, sizeof(timestr), "%d/%d/%d %d:%d", year, month, day, hour, minute);
	
	tm.tm_year = year - 1900; /* years since 1900 */
	tm.tm_mon = month - 1;
	tm.tm_mday = day;
	tm.tm_hour = hour;
	tm.tm_min = minute;
	
	time_t t = mktime(&tm);
	
	//printf("time %s --> %d\n\r", timestr, t);
	buf->st_atime = t;
	buf->st_mtime = t;
	buf->st_ctime = t;
	
	return 0;
}
//#endif

#if defined(__GNUC__)
#include <errno.h>

static int gnu_errno;
volatile int * __aeabi_errno_addr (void)
{
	return &gnu_errno;
}
#endif
