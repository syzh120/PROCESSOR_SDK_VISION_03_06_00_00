/*
 * Copyright (c) 2006-2012, Texas Instruments Incorporated
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
 *  ======== viddec1_copy_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for VIDDEC1COPY
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the VIDDEC1COPY algorithm.
 */
#include <ti/xdais/dm/ividdec1.h>

#ifndef VIDDEC1COPY_TI_PRIV_
#define VIDDEC1COPY_TI_PRIV_

typedef struct VIDDEC1COPY_TI_Obj {
    IALG_Obj    alg;            /* MUST be first field of all XDAS algs */
    XDAS_Int32  outputChromaFormat;
} VIDDEC1COPY_TI_Obj;

extern Int VIDDEC1COPY_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int VIDDEC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int VIDDEC1COPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle parent,
    const IALG_Params *algParams);

extern XDAS_Int32 VIDDEC1COPY_TI_process(IVIDDEC1_Handle h,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDDEC1_InArgs *inArgs,
    IVIDDEC1_OutArgs *outArgs);

extern XDAS_Int32 VIDDEC1COPY_TI_control(IVIDDEC1_Handle handle,
    IVIDDEC1_Cmd id, IVIDDEC1_DynamicParams *params, IVIDDEC1_Status *status);

#endif
