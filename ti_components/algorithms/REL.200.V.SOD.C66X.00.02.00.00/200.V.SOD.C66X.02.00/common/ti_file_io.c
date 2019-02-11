/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
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


/** @file file_io_tb.c
*
*  @brief  This file contains code for Fast File IO Utility.
*
*
*  @date   June 2014
*
*  Description
*    This file contains test code to Network based fast file IO
*/

#pragma CHECK_MISRA ("none")

#if (!HOST_EMULATION)

#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h>

#include "ti_file_io.h"
#include "cache.h"

#ifdef USE_HOST_FILE_IO

#pragma DATA_SECTION(msg_q, ".fileio")
MSG_Q msg_q;

#pragma DATA_SECTION(opStruct, ".fileio")
OpStruct opStruct;

#pragma DATA_SECTION(retValue, ".fileio")
RETVALUE retValue;

#pragma DATA_SECTION(fileArray, ".fileio")
HOSTFILE fileArray[MAX_NUM_FILES];

#pragma DATA_SECTION(fileStatus, ".fileio")
int32_t fileStatus[MAX_NUM_FILES];

volatile uint32_t *sync;
static uint32_t    msg_q_init = 0;
static uint32_t    numFiles   = 0;

static HOSTFILE *allocFile()
{
   HOSTFILE *hf = NULL;
   uint32_t ctr;

   for(ctr = 0; ctr < MAX_NUM_FILES; ctr++)
   {
       if(fileStatus[ctr] == 0)
       {
           hf = (HOSTFILE *)&fileArray[ctr];
           fileStatus[ctr] = 1;
           numFiles++;
           break;
       }
   }

   return hf;
}

static int32_t releaseFile(HOSTFILE *hf)
{
   int32_t success = 0;
   uint32_t ctr;

   for(ctr = 0; ctr < MAX_NUM_FILES; ctr++)
   {
       HOSTFILE *cf = (HOSTFILE *)&fileArray[ctr];
       if((uint32_t)cf == (uint32_t)hf)
       {
           fileStatus[ctr] = 0;
           success = 1;
           numFiles--;
           break;
       }
   }

   return success;
}

static void init_MSG_Q(void)
{
//    msg_q = (MSG_Q    *)(FILE_IO_SHARED_MEM_BASE);
    sync  = (uint32_t *)(FILE_IO_SHARED_MEM_CORE_SYNC);
//    *sync = 0;

    /* Waiting for A15 to load. It will write into this memory. */
    while(1)
    {
        if(*sync == 0xE0F12E10)
        {
            msg_q_init = 1;
//            *sync      = 0x0;
            break;
        }
    }
    msg_q.numMsg = 0;
}

void setnumMsg(uint8_t num)
{
    volatile uint32_t* msgBaseAddr = (volatile uint32_t* )&msg_q;
    volatile uint32_t  rcvdNum;

    *msgBaseAddr = num;

    do{
      rcvdNum = (*msgBaseAddr)&0x000000FFU;
    }while(rcvdNum);

    //msg_q->numMsg = num;
    //while(msg_q->numMsg);
}

void fill_msg_q(uint8_t index, uint8_t msgType, char *ptr, uint32_t size)
{
    msg_q.msgList[index].msgType = msgType;
    msg_q.msgList[index].ptr     = ptr;
    msg_q.msgList[index].size    = size;
}


/*File I/O Functions Start Here*/
void ti_fileio_init()
{
    int32_t ctr;

    for(ctr = 0; ctr < MAX_NUM_FILES; ctr++)
    {
       fileStatus[ctr] = 0;
    }
}

/* Open a file */
HOSTFILE* ti_fileio_fopen(const char *filename, const char *mode)
{
    HOSTFILE *hf;
    uint8_t   enableFastFileIO, i;

    if(!strlen(filename))
    {
        hf = NULL;
        goto EXIT;
    }

    if(!strlen(mode))
    {
        hf = NULL;
        goto EXIT;
    }

    enableFastFileIO = 0;
    /* Search for binary "b" mode set by user. */
    for(i = 0; i < strlen(mode); i++) //    \0
    {
        if(mode[i] == 'b')
        {
            enableFastFileIO = 1;
            break;
        }
    }

    if(enableFastFileIO == 1)
    {
        hf = (HOSTFILE *)allocFile();
        if(!hf)
        {
            goto EXIT;
        }

        memset(hf, 0, sizeof(HOSTFILE));
        if(!msg_q_init)
        {
            init_MSG_Q();
        }

        opStruct.opCode = TI_FILEIO_OPCODE_FOPEN;
        strcpy(opStruct.fileName, filename);
        strcpy(opStruct.mode, mode);

        //fill the MSG_Q struct
        fill_msg_q(0, 0, (char *) &opStruct, sizeof(OpStruct));
        fill_msg_q(1, 1, (char *) hf,       sizeof(HOSTFILE));
        setnumMsg(2);

        hf->fp = NULL;

        if(!hf->id)
        {
            free(hf);
            hf = NULL;
            goto EXIT;
        }

    }else
    {
        hf = (HOSTFILE *)malloc(sizeof(HOSTFILE));
        hf->fp = fopen(filename, mode);
    }
EXIT:
    return hf;
}


//close a file
int8_t ti_fileio_fclose(HOSTFILE *hp)
{
    int8_t    r;

    if(!hp)
    {
        r = EOF;
        goto EXIT;
    }

    if(!hp->fp)
    {
        memset((void *)&retValue, 0, sizeof(RETVALUE));

        opStruct.opCode = TI_FILEIO_OPCODE_FCLOSE;
        opStruct.fid    = hp->id;

        fill_msg_q(0, 0, (char *) &opStruct, sizeof(OpStruct));
        fill_msg_q(1, 1, (char *) &retValue, sizeof(RETVALUE));
        setnumMsg(2);

        r = (int8_t)(retValue.ret);

    }else
    {
        r = fclose(hp->fp);
    }

EXIT:
    if(hp)
    {
        if(!hp->fp)
        {
           releaseFile(hp);
        }
        else
        {
           free(hp);
        }
    }
    return r;
}

//read a file

size_t ti_fileio_fread(void * ptr, size_t size, size_t count, HOSTFILE *fp)
{
    size_t   bytestoRead;

    if(!fp)
    {
        bytestoRead = 0;
        goto EXIT;
    }

    if(!ptr)
    {
        bytestoRead = 0;
        goto EXIT;
    }

    if(!fp->fp)
    {
        opStruct.opCode = TI_FILEIO_OPCODE_FREAD;
        opStruct.fid    = fp->id;
        opStruct.size   = size;
        opStruct.count  = count;

        bytestoRead = size * count;

        fill_msg_q(0, 0, (char *) &opStruct, sizeof(OpStruct));
        fill_msg_q(1, 1, (char *) ptr, bytestoRead);
        setnumMsg(2);

    }else
    {
        bytestoRead = fread(ptr, size, count, fp->fp);
    }

EXIT:
    return bytestoRead;
}

//write to a file
size_t ti_fileio_fwrite(void * ptr, size_t size, size_t count, HOSTFILE * fp)
{
    size_t    bytestoWrite;

    if(!ptr)
    {
        bytestoWrite = 0;
        goto EXIT;
    }

    if(!fp)
    {
        bytestoWrite = 0;
        goto EXIT;
    }

    if(!fp->fp)
    {
        opStruct.opCode = TI_FILEIO_OPCODE_FWRITE;
        opStruct.fid    = fp->id;
        opStruct.size   = size;
        opStruct.count  = count;

        bytestoWrite = size * count;

        fill_msg_q(0, 0, (char *) &opStruct, sizeof(OpStruct));
        fill_msg_q(1, 0, (char*) ptr, bytestoWrite);
        setnumMsg(2);

    }else
    {
        bytestoWrite = fwrite(ptr, size, count, fp->fp);
    }

EXIT:
    return bytestoWrite;
}


int8_t ti_fileio_fseek(HOSTFILE * fp, int32_t offset, int32_t origin)
{
    int8_t    r;

    if(!fp)
    {
        r = -1;
        goto EXIT;
    }

    if(!fp->fp)
    {
        memset((void *)&retValue, 0, sizeof(RETVALUE));

        opStruct.opCode = TI_FILEIO_OPCODE_FSEEK;
        opStruct.fid    = fp->id;
        opStruct.offset = offset;
        opStruct.count  = origin;

        fill_msg_q(0, 0, (char *) &opStruct, sizeof(OpStruct));
        fill_msg_q(1, 1, (char *) &retValue, sizeof(RETVALUE));
        setnumMsg(2);

        r = (int8_t)(retValue.ret);

    }else
    {
        fseek(fp->fp, offset, origin);
    }

EXIT:
    return r;
}


//get current position in stream
int32_t ti_fileio_ftell(HOSTFILE * fp)
{
    int32_t   r;

    if(!fp)
    {
        r = -1;
        goto EXIT;
    }

    if(!fp->fp)
    {
        memset((void *)&retValue, 0, sizeof(RETVALUE));

        opStruct.opCode = TI_FILEIO_OPCODE_FTELL;
        opStruct.fid    = fp->id;

        fill_msg_q(0, 0, (char *) &opStruct, sizeof(OpStruct));
        fill_msg_q(1, 1, (char *) &retValue, sizeof(RETVALUE));
        setnumMsg(2);

        r = retValue.ret;

    }else
    {
        r = ftell(fp->fp);
    }

EXIT:
    return r;
}


//get string from stream
char * ti_fileio_fgets(char *str, int32_t num, HOSTFILE * fp)
{
    char     *ret;

    if(!fp)
    {
        ret = NULL;
        goto EXIT;
    }

    if(!str)
    {
        ret = NULL;
        goto EXIT;
    }

    if(!fp->fp)
    {
        opStruct.opCode = TI_FILEIO_OPCODE_FGETS;
        opStruct.fid    = fp->id;
        opStruct.size   = num;

        fill_msg_q(0, 0, (char *) &opStruct, sizeof(OpStruct));
        fill_msg_q(1, 1, str, num);
        setnumMsg(2);

        ret = str;
    } else
    {
        ret = fgets(str, num, fp->fp);
    }

EXIT:
    return ret;
}

int32_t   ti_fileio_fprintf(HOSTFILE *fp, char *format, ...)
{
    va_list   argptr;
    int32_t   r;

    if(!fp)
    {
        r = -1;
        goto EXIT;
    }

    /* Read the variable number of arguments. */
    va_start(argptr, format);

    /* File IO mode not needed and therefore not supported for fprintf. */
    if(!fp->fp)
    {
        r = -1;
        goto EXIT;
    } else
    {
        r = vfprintf(fp->fp, format, argptr);
    }

EXIT:
    va_end(argptr);

    return r;
}

int32_t   ti_fileio_fscanf(HOSTFILE *fp, char *format, ...)
{
    va_list   argptr;
    int32_t   r;

    if(!fp)
    {
        r = -1;
        goto EXIT;
    }

    /* Read the variable number of arguments. */
    va_start(argptr, format);

    /* File IO mode not needed and therefore not supported for fscanf. */
    if(!fp->fp)
    {
        r = -1;
        goto EXIT;
    } else
    {
        r = vfscanf(fp->fp, format, argptr);
    }

EXIT:
    va_end(argptr);

    return r;
}

#endif //!HOST_EMULATION
#endif

