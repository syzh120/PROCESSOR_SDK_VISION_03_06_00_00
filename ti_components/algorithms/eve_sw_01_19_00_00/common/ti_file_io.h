/*
*
* Copyright (c) {YEAR} Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


#ifndef _FILE_IO_TEST_H_
#define _FILE_IO_TEST_H_

#include "ti_file_io_msg.h"

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
#endif

#endif /* _FILE_IO_TEST_H_ */
