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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include <stdarg.h>

#ifdef USE_HOST_FILE_IO
#include <inttypes.h>
#include "ti_file_io.h"

MSG_Q             *msg_q;
volatile uint32_t *sync;
static uint32_t    msg_q_init = 0;


static void init_MSG_Q(void)
{
    msg_q = (MSG_Q *)(FILE_IO_SHARED_MEM_BASE);
    sync  = (volatile uint32_t *)(FILE_IO_SHARED_MEM_CORE_SYNC);
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
    msg_q->numMsg = 0;
}

void setnumMsg(uint8_t num)
{
    msg_q->numMsg = num;
    while(msg_q->numMsg);
}

void fill_msg_q(uint8_t index, uint8_t msgType, char *ptr, uint32_t size)
{
    msg_q->msgList[index].msgType = msgType;
    msg_q->msgList[index].ptr     = ptr;
    msg_q->msgList[index].size    = size;
}


/*File I/O Functions Start Here*/

/* Open a file */
HOSTFILE* ti_fileio_fopen(const char *filename, const char *mode)
{
    OpStruct *opStruct1;
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

    hf        = malloc(sizeof *hf);
    if(!hf)
    {
        goto EXIT;
    }

    memset(hf, 0, sizeof(HOSTFILE));

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
        if(!msg_q_init)
        {
            init_MSG_Q();
        }

        opStruct1 = malloc(sizeof *opStruct1);
        if(!opStruct1)
        {
            free(hf);
            goto EXIT;
        }

        opStruct1->opCode = TI_FILEIO_OPCODE_FOPEN;
        strcpy(opStruct1->fileName, filename);
        strcpy(opStruct1->mode, mode);

        //fill the MSG_Q struct
        fill_msg_q(0, 0, (char *) opStruct1, sizeof(OpStruct));
        fill_msg_q(1, 1, (char *) hf,        sizeof(HOSTFILE));
        setnumMsg(2);

        free(opStruct1);
        hf->fp = NULL;

        if(!hf->id)
        {
            free(hf);
            hf = NULL;
            goto EXIT;
        }

    }else
    {
        hf->fp = fopen(filename, mode);
    }
EXIT:
    return hf;
}


//close a file
int8_t ti_fileio_fclose(HOSTFILE *fp)
{
    int8_t    r;
    OpStruct *opStruct2;
    RETVALUE *retValue2;

    if(!fp)
    {
        r = EOF;
        goto EXIT;
    }

    if(!fp->fp)
    {
        opStruct2 = malloc(sizeof *opStruct2);
        retValue2 = malloc(sizeof *retValue2);

        if(!opStruct2 || !retValue2)
        {
            r = EOF;
            goto EXIT;
        }

        memset(retValue2, 0, sizeof(RETVALUE));

        opStruct2->opCode = TI_FILEIO_OPCODE_FCLOSE;
        opStruct2->fid    = fp->id;

        fill_msg_q(0, 0, (char *) opStruct2, sizeof(OpStruct));
        fill_msg_q(1, 1, (char *) retValue2, sizeof(RETVALUE));
        setnumMsg(2);

        r = (int8_t)(retValue2->ret);

        free(retValue2);
        free(opStruct2);
    }else
    {
        r = fclose(fp->fp);
    }

EXIT:
    if(fp)
    {
        free(fp);
    }
    return r;
}


//read a file

size_t ti_fileio_fread(void * ptr, size_t size, size_t count, HOSTFILE *fp)
{
    size_t    numElems;
    OpStruct *opStruct3;

    if(!fp)
    {
        numElems = 0;
        goto EXIT;
    }

    if(!ptr)
    {
        numElems = 0;
        goto EXIT;
    }

    if(!fp->fp)
    {
        opStruct3 = malloc(sizeof *opStruct3);
        if(!opStruct3)
        {
            numElems = 0;
            goto EXIT;
        }

        opStruct3->opCode = TI_FILEIO_OPCODE_FREAD;
        opStruct3->fid    = fp->id;
        opStruct3->size   = size;
        opStruct3->count  = count;

        numElems = count;

        fill_msg_q(0, 0, (char *) opStruct3, sizeof(OpStruct));
        fill_msg_q(1, 1, (char*) ptr, numElems*size);
        setnumMsg(2);

        free(opStruct3);
    }else
    {
        numElems = fread(ptr, size, count, fp->fp);
    }

EXIT:
    return numElems;
}

//write to a file
size_t ti_fileio_fwrite(void * ptr, size_t size, size_t count, HOSTFILE * fp)
{
    size_t    numElems;
    OpStruct *opStruct4;

    if(!ptr)
    {
        numElems = 0;
        goto EXIT;
    }

    if(!fp)
    {
        numElems = 0;
        goto EXIT;
    }

    if(!fp->fp)
    {
        opStruct4 = malloc(sizeof *opStruct4);
        if(!opStruct4)
        {
            numElems = 0;
            goto EXIT;
        }

        opStruct4->opCode = TI_FILEIO_OPCODE_FWRITE;
        opStruct4->fid    = fp->id;
        opStruct4->size   = size;
        opStruct4->count  = count;

        numElems = count;

        fill_msg_q(0, 0, (char *) opStruct4, sizeof(OpStruct));
        fill_msg_q(1, 0, (char*) ptr, numElems*size);
        setnumMsg(2);

        free(opStruct4);
    }else
    {
        numElems = fwrite(ptr, size, count, fp->fp);
    }

EXIT:
    return numElems;
}


int8_t ti_fileio_fseek(HOSTFILE * fp, int32_t offset, int32_t origin)
{
    int8_t    r;
    OpStruct *opStruct5;
    RETVALUE *retValue5;

    if(!fp)
    {
        r = -1;
        goto EXIT;
    }

    if(!fp->fp)
    {
        opStruct5 = malloc(sizeof *opStruct5);
        retValue5 = malloc(sizeof *retValue5);
        if(!opStruct5 || !retValue5)
        {
            r = -1;
            goto EXIT;
        }

        memset(retValue5, 0, sizeof(RETVALUE));

        opStruct5->opCode = TI_FILEIO_OPCODE_FSEEK;
        opStruct5->fid    = fp->id;
        opStruct5->offset = offset;
        opStruct5->count  = origin;

        fill_msg_q(0, 0, (char *) opStruct5, sizeof(OpStruct));
        fill_msg_q(1, 1, (char *) retValue5, sizeof(RETVALUE));
        setnumMsg(2);

        r = (int8_t)(retValue5->ret);

        free(retValue5);
        free(opStruct5);
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
    OpStruct *opStruct6;
    RETVALUE *retValue6;

    if(!fp)
    {
        r = -1;
        goto EXIT;
    }

    if(!fp->fp)
    {
        opStruct6 = malloc(sizeof *opStruct6);
        retValue6 = malloc(sizeof *retValue6);
        if(!opStruct6 || !retValue6)
        {
            r = -1;
            goto EXIT;
        }

        memset(retValue6, 0, sizeof(RETVALUE));

        opStruct6->opCode = TI_FILEIO_OPCODE_FTELL;
        opStruct6->fid    = fp->id;

        fill_msg_q(0, 0, (char *) opStruct6, sizeof(OpStruct));
        fill_msg_q(1, 1, (char *) retValue6, sizeof(RETVALUE));
        setnumMsg(2);

        r = retValue6->ret;

        free(retValue6);
        free(opStruct6);
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
    OpStruct *opStruct7;
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
        opStruct7 = malloc(sizeof *opStruct7);
        if(!opStruct7)
        {
            ret = NULL;
            goto EXIT;
        }

        opStruct7->opCode = TI_FILEIO_OPCODE_FGETS;
        opStruct7->fid    = fp->id;
        opStruct7->size   = num;

        fill_msg_q(0, 0, (char *) opStruct7, sizeof(OpStruct));
        fill_msg_q(1, 1, str, num);
        setnumMsg(2);

        free(opStruct7);
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

#endif

