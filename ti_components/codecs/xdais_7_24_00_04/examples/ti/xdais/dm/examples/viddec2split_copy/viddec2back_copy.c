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
 *  ======== viddec2back_copy.c ========
 *  Video decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IVIDDEC2BACK interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/split/ividdec2.h>

#ifdef __TI_COMPILER_VERSION__
/* xDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDDEC2BACKCOPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDDEC2BACKCOPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDDEC2BACKCOPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDDEC2BACKCOPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDDEC2BACKCOPY_TI_alloc,   ".text:algAlloc")
#endif

#include "viddec2back_copy_ti.h"
#include "viddec2back_copy_ti_priv.h"

/* Must match VIDDEC2FRONTCOPY_TI_CONTEXT - belongs in shared header */
typedef struct VIDDEC2BACKCOPY_TI_CONTEXT {
    /* Only context we have to save is the entire OutArgs result */
    IVIDDEC2_OutArgs  outArgs;
} VIDDEC2BACKCOPY_TI_CONTEXT;

#define IALGFXNS  \
    &VIDDEC2BACKCOPY_TI_IALG,    /* module ID */                         \
    NULL,                        /* activate */                          \
    VIDDEC2BACKCOPY_TI_alloc,    /* alloc */                             \
    NULL,                        /* control (NULL => no control ops) */  \
    NULL,                        /* deactivate */                        \
    VIDDEC2BACKCOPY_TI_free,     /* free */                              \
    VIDDEC2BACKCOPY_TI_initObj,  /* init */                              \
    NULL,                        /* moved */                             \
    NULL                         /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDDEC2COPY_TI_IVIDDECCOPY ========
 *  This structure defines TI's implementation of the IVIDDEC2 interface
 *  for the VIDDEC2COPY_TI module.
 */
IVIDDEC2BACK_Fxns VIDDEC2BACKCOPY_TI_IVIDDEC2BACKCOPY = {
    {IALGFXNS},
    VIDDEC2BACKCOPY_TI_process,
    VIDDEC2BACKCOPY_TI_control,
};

/*
 *  ======== VIDDEC2BACKCOPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDDEC2BACKCOPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("VIDDEC2BACKCOPY_TI_IALG .set VIDDEC2BACKCOPY_TI_IVIDDEC2BACKCOPY");

#else

/* Symbol has a single leading underscore */
asm("_VIDDEC2BACKCOPY_TI_IALG .set _VIDDEC2BACKCOPY_TI_IVIDDEC2BACKCOPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDDEC2BACKCOPY_TI_IALG = {
    IALGFXNS
};

#endif

IVIDDEC2_Params VIDDEC2BACKCOPY_TI_PARAMS = {
    sizeof(IVIDDEC2_Params),
    1024,                           /* maxHeight */
    1024,                           /* maxWidth */
    30000,                          /* maxFrameRate */
    10000000,                       /* maxBitRate */
    XDM_BYTE,                       /* dataEndianness */
    XDM_CHROMAFORMAT_DEFAULT        /* forceChromaFormat */
};

/*
 *  ======== VIDDEC2BACKCOPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC2BACKCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(VIDDEC2BACKCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== VIDDEC2BACKCOPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC2BACKCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (VIDDEC2BACKCOPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== VIDDEC2BACKCOPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC2BACKCOPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
        IALG_Handle parent, const IALG_Params *algParams)
{
    VIDDEC2BACKCOPY_TI_Obj *obj = (VIDDEC2BACKCOPY_TI_Obj *)handle;
    const IVIDDEC2_Params *params = (IVIDDEC2_Params *)algParams;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDDEC2BACKCOPY_TI_PARAMS;
    }

    obj->outputChromaFormat = params->forceChromaFormat;

    return (IALG_EOK);
}


/*
 *  ======== VIDDEC2BACKCOPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDDEC2BACKCOPY_TI_process(IVIDDEC2BACK_Handle h,
        XDM_Context *context, IVIDDEC2_OutArgs *outArgs)
{
    VIDDEC2BACKCOPY_TI_CONTEXT *pAlgContext;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((outArgs->size) != sizeof(*outArgs)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->decodedBufs.extendedError);

        return (IVIDDEC2_EUNSUPPORTED);
    }

    if (context == NULL) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->decodedBufs.extendedError);

        return (IVIDDEC2_EUNSUPPORTED);
    }

    pAlgContext =
        (VIDDEC2BACKCOPY_TI_CONTEXT *)(context->algContext.buf);

    /* report _how_ we accessed the various buffers */
    context->inBufs[0].accessMask = 0;  /* no access */
    context->outBufs[0].accessMask = 0; /* no access */

    context->algContext.accessMask = 0;        /* clear it... */
    XDM_SETACCESSMODE_READ(context->algContext.accessMask); /* ... read it */

    /* outArgs->bytesConsumed reports the total number of bytes decoded */
    outArgs->bytesConsumed = pAlgContext->outArgs.bytesConsumed;

    /* Fill out the rest of the outArgs struct */
    outArgs->outputID[0] = pAlgContext->outArgs.outputID[0];
    outArgs->outputID[1] = 0;  /* end of array - invalid ID */

    outArgs->decodedBufs.numBufs = 1;
    outArgs->decodedBufs.frameWidth = pAlgContext->outArgs.decodedBufs.frameWidth; /* minBytes wide */
    outArgs->decodedBufs.frameHeight = 1;       /* one pixel high */
    outArgs->decodedBufs.framePitch = 0;        /* TODO */

    outArgs->decodedBufs.bufDesc[0].buf = context->outBufs[0].buf;
    outArgs->decodedBufs.bufDesc[0].bufSize = context->outBufs[0].bufSize;

    /* initialize accessMask, then indicate how we accessed it (we didn't!) */
    outArgs->decodedBufs.bufDesc[0].accessMask = 0;

    outArgs->decodedBufs.extendedError = 0;
    outArgs->decodedBufs.frameType = 0;         /* TODO */
    outArgs->decodedBufs.topFieldFirstFlag = XDAS_FALSE;  /* TODO */
    outArgs->decodedBufs.repeatFirstFieldFlag = XDAS_FALSE;  /* TODO */
    outArgs->decodedBufs.frameStatus = IVIDEO_FRAME_NOERROR;
    outArgs->decodedBufs.repeatFrame = 0;  /* TODO */
    outArgs->decodedBufs.contentType = IVIDEO_PROGRESSIVE;
    outArgs->decodedBufs.chromaFormat = XDM_CHROMAFORMAT_DEFAULT;

    /* Single display buf equivalent to the decoded buf above */
    outArgs->displayBufs[0] = outArgs->decodedBufs;
    outArgs->displayBufs[1].numBufs = 0;   /* end of array */

    /* MB data support is TBD */
    outArgs->outputMbDataID = 0;  /* invalid ID */
    outArgs->mbDataBuf.buf = NULL;  /* important, set to NULL if no MB Data! */

    /* release the outBuf */
    outArgs->freeBufID[0] = pAlgContext->outArgs.freeBufID[0];
    outArgs->freeBufID[1] = 0; /* end of array - invalid ID */
    outArgs->outBufsInUseFlag = XDAS_FALSE;

    return (IVIDDEC2_EOK);
}


/*
 *  ======== VIDDEC2BACKCOPY_TI_control ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDDEC2BACKCOPY_TI_control(IVIDDEC2BACK_Handle handle,
        XDM_Context *context, IVIDDEC2_Status *status)
{
    XDAS_Int32 retVal;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((status->size) != sizeof(*status)) {
        XDM_SETUNSUPPORTEDPARAM(status->extendedError);

        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* Initialize extendedError */
    status->extendedError = 0;

    /* initialize for the general case where we don't access the data buffer */
    status->data.accessMask = 0;

    /*
     *  In this BACK codec, we don't do anything.  The FRONT handles everything,
     *  so in all cases, just return success.
     */
    retVal = IVIDDEC2_EOK;

    return (retVal);
}
