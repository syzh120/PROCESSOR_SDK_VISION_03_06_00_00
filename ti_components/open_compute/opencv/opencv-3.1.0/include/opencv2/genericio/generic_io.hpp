/* Fill preamble
 *
 *
 */

/*
 * Includes
 */

#ifndef __GENERIC_FS_H__
#define __GENERIC_FS_H__

#include <stdio.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C"
{
#endif

#define GENERIC_STREAM_PRINTF generic_printf

#ifdef GENERIC_ARM

typedef int GENERIC_FILE;
#define generic_null -1
#define GENERIC_IF_EXISTS(fp) if(fp != -1)
#define GENERIC_IF_NOT_EXISTS(fp) if(fp == -1)
	
#else

#include <stdio.h>
#include <sys/stat.h>
typedef FILE*  GENERIC_FILE;
#define generic_null NULL
#define GENERIC_IF_EXISTS(fp) if(fp)    
#define GENERIC_IF_NOT_EXISTS(fp) if(!fp)    

#endif /* End of GENERIC_ARM */

/*
 * File access APIs
 */
	
GENERIC_FILE generic_fopen(const char* fileName, char* mode);
int generic_fflush(GENERIC_FILE fileDescriptor);
int generic_fclose(GENERIC_FILE fileDescriptor);

/*
 * Direct input/output APIs
 */

size_t generic_fread( void * ptr, size_t size, size_t count, GENERIC_FILE fileDescriptor );
size_t generic_fwrite( const void * ptr, size_t size, size_t count, GENERIC_FILE fileDescriptor );

/*
 * Unformatted input/output APIs
 */
    
char* generic_fgets(char *str, int n, GENERIC_FILE fileDescriptor);
int generic_fputc(int character, GENERIC_FILE fileDescriptor);
int generic_fputs(const char* str, GENERIC_FILE fileDescriptor);

/*
 * Formatted input/output APIs
 */

void generic_printf(char* format, ...);
int generic_fprintf(GENERIC_FILE file, char* format, ...);
void generic_vprintf(char* format, va_list arguments);

/*
 * File positioning
 */

long int generic_ftell( GENERIC_FILE fileDescriptor);
int generic_fseek( GENERIC_FILE fileDescriptor, long int offset, int origin );
int generic_frewind(GENERIC_FILE fileDescriptor);

/*
 * Error handling
 */

int generic_feof(GENERIC_FILE fileDescriptor);
int generic_ferror(GENERIC_FILE fileDescriptor);
    
/* 
 *Other
 */

#ifdef GENERIC_ARM
int generic_mkdir(char* filename);
#else
int generic_mkdir(char* filename, mode_t mode);
#endif
char* generic_getcwd(char *buf, int buflen);
int generic_isdir(char* path);    
        
#ifdef __cplusplus
}
#endif /* __cplusplus */
    
#endif /* EOF */

