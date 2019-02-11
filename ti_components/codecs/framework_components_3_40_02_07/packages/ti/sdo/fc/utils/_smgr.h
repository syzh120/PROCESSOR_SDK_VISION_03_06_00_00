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
 *
 */
/*
 *  ======== _smgr.h ========
 */

#ifndef _SMGR_H__
#define _SMGR_H__

#include "smgr.h"

#define SMGR_RESAVAILABLE       0xFFFF
#define SMGR_RESPERSISTENT      -1
#define SMGR_RESANY                -1

/* Convenience macros */
#define MIN(i,j) ((i) > (j)) ? (j) : (i)
#define MAX(i,j) ((i) > (j)) ? (i) : (j)

#define RESLIST(i) ((SMGR_Counter *)((UInt32)handle + \
        handle->resourceListOffset + sizeof(SMGR_Counter) * (i)))

#define RESSTAT(i) ((RESLIST(i))->scratchId)
#define RESALG(i) ((RESLIST(i))->alg)
#define RESCOUNT(i) ((RESLIST(i)->counter))
#define RESMAXID (handle->maxId)

#define TAX(i) ((RESSTAT(i) == SMGR_RESAVAILABLE) ? 1 : 0)

/*
 *  ======== SMGR_Counter ========
 *  This is the information stored for each SMGR resource.
 */

typedef struct SMGR_Counter {
    Int     scratchId;
    Int     counter;
    IALG_Handle alg;
} SMGR_Counter;

/*
 *  ======== SMGR_Obj ========
 *  Object that holds the information regarding the SMGR instance for this
 *  resources
 */
typedef struct SMGR_Obj {
    Int             numResources;
    Int             numGroups;
    UInt32          resourceListOffset;
    Int             segid;           /* Memory segment to allocate from */
    SMGR_allocFxn   allocFxn;
    SMGR_freeFxn    freeFxn;
    Int             maxId;          /* Store maximum allocated for scratch id*/
} SMGR_Obj;

#endif /* _SMGR_H__ */
