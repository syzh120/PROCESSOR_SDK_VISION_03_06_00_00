/*
 *
 * Copyright (C) 2018 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the  
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef _FILE_IO_TEST_H_
#define _FILE_IO_TEST_H_

#if(!HOST_EMULATION)
//#define USE_HOST_FILE_IO
#endif

#ifndef USE_HOST_FILE_IO
#define TI_FILE FILE
#define FOPEN   fopen
#define FCLOSE  fclose
#define FREAD   fread
#define FWRITE  fwrite
#define FSEEK   fseek
#define FTELL   ftell
#define FGETS   fgets
#define FPRINTF fprintf
#define FSCANF  fscanf
#else

#include "ti_file_io_msg.h"
#define TI_FILE HOSTFILE
#define FOPEN   ti_fileio_fopen
#define FCLOSE  ti_fileio_fclose
#define FREAD   ti_fileio_fread
#define FWRITE  ti_fileio_fwrite
#define FSEEK   ti_fileio_fseek
#define FTELL   ti_fileio_ftell
#define FGETS   ti_fileio_fgets
#define FPRINTF ti_fileio_fprintf
#define FSCANF  ti_fileio_fscanf

typedef enum {
    TI_FILEIO_OPCODE_FOPEN = 1,
    TI_FILEIO_OPCODE_FCLOSE,
    TI_FILEIO_OPCODE_FREAD,
    TI_FILEIO_OPCODE_FWRITE,
    TI_FILEIO_OPCODE_FSEEK,
    TI_FILEIO_OPCODE_FTELL,
    TI_FILEIO_OPCODE_FGETS,
    TI_FILEIO_OPCODE_FPRINTF,
    TI_FILEIO_OPCODE_FSCANF
} TI_FILEIO_OPCODE;


HOSTFILE* ti_fileio_fopen(const char * filename, const char * mode);
int8_t    ti_fileio_fclose(HOSTFILE * fp);
size_t    ti_fileio_fread(void * ptr, size_t size, size_t count, HOSTFILE * fp);
size_t    ti_fileio_fwrite(void * ptr, size_t size, size_t count, HOSTFILE * fp);
int8_t    ti_fileio_fseek(HOSTFILE * fp, int32_t offset, int32_t origin);
int32_t   ti_fileio_ftell(HOSTFILE * fp);
char *    ti_fileio_fgets(char * str, int32_t num, HOSTFILE * fp);
int32_t   ti_fileio_fprintf(HOSTFILE *fp, char *format, ...);
int32_t   ti_fileio_fscanf(HOSTFILE *fp, char *format, ...);
void      ti_fileio_init();
#endif

#endif /* _FILE_IO_TEST_H_ */
