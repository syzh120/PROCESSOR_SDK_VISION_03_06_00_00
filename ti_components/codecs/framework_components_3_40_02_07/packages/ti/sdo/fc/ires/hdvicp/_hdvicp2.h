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

#ifndef _HDVICP2_H
#define _HDVICP2_H

#include <ti/xdais/ires.h>
#include <ti/sdo/fc/rman/rman.h>
#include "ires_hdvicp2.h"

typedef struct IRES_HDVICP2_IntObj {
    IRES_HDVICP2_Obj resObj;
    Bool lateAcquire;
    Int scratchGroup;           /* Info required to handle context release
                                   during lateAcquire etc */
    Int reqId;
} IRES_HDVICP2_IntObj;


extern XDAS_Void IRESMAN_HDVICP2_JITacquire (IALG_Handle algHandle,
        IRES_HDVICP2_Obj * hdvicpHandle, IRES_YieldContextHandle yieldCtxt,
        XDAS_UInt32 * reloadHDVICP, XDAS_UInt32 * modeId,
        XDAS_Int32 lateAcquireArg);
extern XDAS_Void IRESMAN_HDVICP2_JITrelease (IALG_Handle algHandle,
        IRES_HDVICP2_Obj * hdvicpHandle);
extern XDAS_UInt32 IRESMAN_HDVICP2_JITreacquire (IALG_Handle algHandle,
        IRES_HDVICP2_Obj * handle);

/* Id offset from _HDVICP2_ipcKeyBase to shared memory containing HDVICP2 object */
#define _HDVICP2_SHMID (_HDVICP2_ipcKeyBase)

/* Id offset from _HDVICP2_ipcKeyBase to semaphore used for critical sections */
#define _HDVICP2_CSID (_HDVICP2_ipcKeyBase + 1)

/* Id offset from _HDVICP2_ipcKeyBase to lock used for protecting HDVICP2 object */
#define _HDVICP2_LOCKID (_HDVICP2_ipcKeyBase + 2)

/* Id offset from _HDVICP2_ipcKeyBase to semaphore used for managing scratch
   HDVICP2 memory resources */
#define _HDVICP2_MEMID (_HDVICP2_ipcKeyBase + 3)

extern UInt32 _HDVICP2_ipcKeyBase;

#endif /* _HDVICP_H */
