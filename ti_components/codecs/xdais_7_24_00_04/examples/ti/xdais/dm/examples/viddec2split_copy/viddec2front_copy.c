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
 *  ======== viddec2front_copy.c ========
 *  Video decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IVIDDEC2FRONT interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/split/ividdec2.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDDEC2FRONTCOPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDDEC2FRONTCOPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDDEC2FRONTCOPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDDEC2FRONTCOPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDDEC2FRONTCOPY_TI_alloc,   ".text:algAlloc")
#endif

#include "viddec2front_copy_ti.h"
#include "viddec2front_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

typedef struct VIDDEC2FRONTCOPY_TI_CONTEXT {
    /* Only context we have to save is the entire OutArgs result */
    IVIDDEC2_OutArgs  outArgs;
} VIDDEC2FRONTCOPY_TI_CONTEXT;

extern IALG_Fxns VIDDEC2FRONTCOPY_TI_IALG;

#define IALGFXNS  \
    &VIDDEC2FRONTCOPY_TI_IALG,   /* module ID */                         \
    NULL,                        /* activate */                          \
    VIDDEC2FRONTCOPY_TI_alloc,   /* alloc */                             \
    NULL,                        /* control (NULL => no control ops) */  \
    NULL,                        /* deactivate */                        \
    VIDDEC2FRONTCOPY_TI_free,    /* free */                              \
    VIDDEC2FRONTCOPY_TI_initObj, /* init */                              \
    NULL,                        /* moved */                             \
    NULL                         /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDDEC2COPY_TI_IVIDDECCOPY ========
 *  This structure defines TI's implementation of the IVIDDEC2 interface
 *  for the VIDDEC2COPY_TI module.
 */
IVIDDEC2FRONT_Fxns VIDDEC2FRONTCOPY_TI_IVIDDEC2FRONTCOPY = {
    {IALGFXNS},
    VIDDEC2FRONTCOPY_TI_process,
    VIDDEC2FRONTCOPY_TI_control,
};

/*
 *  ======== VIDDEC2FRONTCOPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDDEC2FRONTCOPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("VIDDEC2FRONTCOPY_TI_IALG .set VIDDEC2FRONTCOPY_TI_IVIDDEC2FRONTCOPY");

#else

/* Symbol has a single leading underscore */
asm("_VIDDEC2FRONTCOPY_TI_IALG .set _VIDDEC2FRONTCOPY_TI_IVIDDEC2FRONTCOPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDDEC2FRONTCOPY_TI_IALG = {
    IALGFXNS
};

#endif

IVIDDEC2_Params VIDDEC2FRONTCOPY_TI_PARAMS = {
    sizeof(IVIDDEC2_Params),
    1024,                           /* maxHeight */
    1024,                           /* maxWidth */
    30000,                          /* maxFrameRate */
    10000000,                       /* maxBitRate */
    XDM_BYTE,                       /* dataEndianness */
    XDM_CHROMAFORMAT_DEFAULT        /* forceChromaFormat */
};

/*
 *  ======== VIDDEC2FRONTCOPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC2FRONTCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(VIDDEC2FRONTCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== VIDDEC2FRONTCOPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC2FRONTCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (VIDDEC2FRONTCOPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== VIDDEC2FRONTCOPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC2FRONTCOPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
        IALG_Handle parent, const IALG_Params *algParams)
{
    VIDDEC2FRONTCOPY_TI_Obj *obj = (VIDDEC2FRONTCOPY_TI_Obj *)handle;
    const IVIDDEC2_Params *params = (IVIDDEC2_Params *)algParams;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDDEC2FRONTCOPY_TI_PARAMS;
    }

    obj->outputChromaFormat = params->forceChromaFormat;

    return (IALG_EOK);
}


/*
 *  ======== VIDDEC2FRONTCOPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDDEC2FRONTCOPY_TI_process(IVIDDEC2FRONT_Handle h,
        IVIDDEC2_InArgs *inArgs, XDM_Context *context,
        IVIDDEC2FRONT_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;
    VIDDEC2FRONTCOPY_TI_CONTEXT *pAlgContext;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((context->numInBufs < 1) || (context->numOutBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDDEC2_EFAIL);
    }

    numInBytes = inArgs->numBytes;

    /*
     * Sanity check that context->inBufs[0].bufSize is really capable of holding
     * numInBytes bytes of data, and that context->outBufs[0].bufSize
     * can hold the 'encoded' data.
     */
    if ((context->inBufs[0].bufSize < inArgs->numBytes) ||
        (context->outBufs[0].bufSize < MINOUTBUFSIZE)){

        /* inBuf is smaller than provided data(!) or "too small" outBuf */
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDDEC2_EFAIL);
    }

    pAlgContext = (VIDDEC2FRONTCOPY_TI_CONTEXT *)(context->algContext.buf);

    /* validate pAlgContext */
    if (pAlgContext == NULL) {

        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDDEC2_EFAIL);
    }

    /* everything looks good, do the 'encode', set outArgs and return */
    memcpy(context->outBufs[0].buf, context->inBufs[0].buf, numInBytes);

    /* report _how_ we accessed the input buffer */
    context->inBufs[0].accessMask = 0;
    XDM_SETACCESSMODE_READ(context->inBufs[0].accessMask);

    /* outArgs->bytesConsumed reports the total number of bytes decoded */
    pAlgContext->outArgs.bytesConsumed = numInBytes;

    /* Fill out the rest of the outArgs struct */
    pAlgContext->outArgs.outputID[0] = inArgs->inputID;
    pAlgContext->outArgs.outputID[1] = 0;  /* end of array - invalid ID */

    pAlgContext->outArgs.decodedBufs.numBufs = 1;
    pAlgContext->outArgs.decodedBufs.frameWidth = numInBytes; /* minBytes wide */
    pAlgContext->outArgs.decodedBufs.frameHeight = 1;       /* one pixel high */
    pAlgContext->outArgs.decodedBufs.framePitch = 0;        /* TODO */

    /* initialize the accessMask, then indicate how we accessed it */
    context->outBufs[0].accessMask = 0;
    XDM_SETACCESSMODE_WRITE(context->outBufs[0].accessMask);

    pAlgContext->outArgs.decodedBufs.extendedError = 0;
    pAlgContext->outArgs.decodedBufs.frameType = 0;         /* TODO */
    pAlgContext->outArgs.decodedBufs.topFieldFirstFlag = XDAS_FALSE;  /* TODO */
    pAlgContext->outArgs.decodedBufs.repeatFirstFieldFlag = XDAS_FALSE;  /* TODO */
    pAlgContext->outArgs.decodedBufs.frameStatus = IVIDEO_FRAME_NOERROR;
    pAlgContext->outArgs.decodedBufs.repeatFrame = 0;  /* TODO */
    pAlgContext->outArgs.decodedBufs.contentType = IVIDEO_PROGRESSIVE;
    pAlgContext->outArgs.decodedBufs.chromaFormat = XDM_CHROMAFORMAT_DEFAULT;

    /* MB data support is TBD */
    pAlgContext->outArgs.outputMbDataID = 0;  /* invalid ID */
    pAlgContext->outArgs.mbDataBuf.buf = NULL;  /* Set to NULL if no MB Data! */

    pAlgContext->outArgs.freeBufID[0] = inArgs->inputID;  /* release the outBuf */
    pAlgContext->outArgs.freeBufID[1] = 0; /* end of array - invalid ID */
    pAlgContext->outArgs.outBufsInUseFlag = XDAS_FALSE;

    /* initialize the accessMask, then indicate how we accessed it */
    context->algContext.accessMask = 0;
    XDM_SETACCESSMODE_WRITE(context->algContext.accessMask);

    return (IVIDDEC2_EOK);
}


/*
 *  ======== VIDDEC2FRONTCOPY_TI_control ========
 */
XDAS_Int32 VIDDEC2FRONTCOPY_TI_control(IVIDDEC2FRONT_Handle handle,
        IVIDDEC2_Cmd id, IVIDDEC2_DynamicParams *dynParams,
        XDM_Context *context, IVIDDEC2FRONT_Status *status)
{
    XDAS_Int32 retVal;
    VIDDEC2FRONTCOPY_TI_Obj *obj = (VIDDEC2FRONTCOPY_TI_Obj *)handle;
    XDAS_Int32 i;

    /*
     * In this codec, the front part can handle control() requests, so we
     * initialize status->nextPartRequired to XDAS_FALSE.
     *
     * Note that codecs need to set this status->nextPartRequiredFlag
     * to XDAS_FALSE when returning errors as well, so we initialize it
     * early, just in case.
     */
    status->nextPartRequiredFlag = XDAS_FALSE;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->fullStatus.size != sizeof(status->fullStatus))) {

        XDM_SETUNSUPPORTEDPARAM(status->partialExtendedError);

        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* Initialize extendedError */
    status->partialExtendedError = 0;

    /* Note that context is option, check before touching it! */
    if (context != NULL) {
        /* Initialize for the general case where we don't access any buffers */
        if (context->algContext.buf != NULL) {
            context->algContext.accessMask = 0;
        }

        for (i = 0; (i < XDM_MAX_CONTEXT_BUFFERS) && (i < context->numInBufs);
             i++) {
            if (context->inBufs[i].buf != NULL) {
                context->inBufs[i].accessMask = 0;
            }
        }
        for (i = 0; (i < XDM_MAX_CONTEXT_BUFFERS) && (i < context->numOutBufs);
             i++) {
            if (context->outBufs[i].buf != NULL) {
                context->outBufs[i].accessMask = 0;
            }
        }
        for (i = 0; (i < XDM_MAX_CONTEXT_BUFFERS) && (i < context->numInOutBufs);
             i++) {
            if (context->inOutBufs[i].buf != NULL) {
                context->inOutBufs[i].accessMask = 0;
            }
        }
        for (i = 0; (i < XDM_MAX_CONTEXT_BUFFERS); i++) {
            if (context->intermediateBufs[i].buf != NULL) {
                context->intermediateBufs[i].accessMask = 0;
            }
            else {
                /* intermidateBufs is a null terminated array */
                break;
            }
        }
    }

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->fullStatus.outputHeight = 0;  /* TODO */
            status->fullStatus.outputWidth = 0;  /* TODO */
            status->fullStatus.frameRate = 0;  /* TODO */
            status->fullStatus.bitRate = 0;  /* TODO */
            status->fullStatus.contentType = 0;  /* TODO */
            status->fullStatus.outputChromaFormat = obj->outputChromaFormat;

            status->fullStatus.bufInfo.minNumInBufs = MININBUFS;
            status->fullStatus.bufInfo.minNumOutBufs = MINOUTBUFS;
            status->fullStatus.bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->fullStatus.bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IVIDDEC2_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IVIDDEC2_EOK;
            break;

        case XDM_SETDEFAULT:
            obj->outputChromaFormat =
                VIDDEC2FRONTCOPY_TI_PARAMS.forceChromaFormat;

            retVal = IVIDDEC2_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IVIDDEC2_EOK;
            break;

        case XDM_GETVERSION:
            if ((context != NULL) && (context->numOutBufs >= 1) &&
                    (context->outBufs[0].buf != NULL) &&
                    (context->outBufs[0].bufSize >
                            strlen(VERSIONSTRING))) {
                strncpy((char *)(context->outBufs[0].buf), VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(context->outBufs[0].accessMask);

                retVal = IVIDDEC2_EOK;
            }
            else {
                retVal = IVIDDEC2_EFAIL;
            }

            break;

        case XDM_GETCONTEXTINFO:
            status->contextInfo.minContextSize =
                sizeof(VIDDEC2FRONTCOPY_TI_CONTEXT);

            /* no intermediate data bufs */
            status->contextInfo.minIntermediateBufSizes[0] = 0;

            retVal = IVIDDEC2_EOK;
            break;

        default:
            /* unsupported cmd */
            retVal = IVIDDEC2_EFAIL;

            break;
    }

    return (retVal);
}
