/*
 * Copyright (c) 2012, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * */
/*
 * ======== oskern.h ========
 *
 * Private include files for kernel objects
 *
 */

#ifndef _C_OSKERN_H
#define _C_OSKERN_H

/* Kernel HTYPE's */
#define HTYPE_CFG               0x0102
#define HTYPE_CFGENTRY          0x0103
#define HTYPE_EFSFILEHEADER     0x0104
#define HTYPE_EFSFILEPOINTER    0x0105

/*--------------------------------------------- */
/*--------------------------------------------- */
/* TASK */
/*--------------------------------------------- */
/*--------------------------------------------- */

/* Task Functions used by the Scheduler */
_extern void   _TaskInit();
_extern void   _TaskShutdown();

/*--------------------------------------------- */
/*--------------------------------------------- */
/* MEMORY */
/*--------------------------------------------- */
/*--------------------------------------------- */

/* P.I.T. Entry */
typedef struct {
                UINT8           *pPageStart;
                uint            PageSize;
                uint            BlockSize;
                uint            BlockSizeIdx;
                uint            BlocksPerPage;
                uint            AllocCount;
                uint            IdxFreeCheck;
               } PITENTRY;

/* Memory functions not used by the Scheduler */
_extern int    _mmInit();
_extern void   _mmCheck( uint CallMode, int (*pPrn)(const char *,...) );
#define MMCHECK_MAP             0       /* Map out allocated memory */
#define MMCHECK_DUMP            1       /* Dump allocated block ID's */
#define MMCHECK_SHUTDOWN        2       /* Dump allocated block's & free */

_extern void   _mmBulkAllocSeg( uint segId );

#endif
