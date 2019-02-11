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
 *  ======== viddec2_copy.c ========
 *  Video decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IVIDDEC2 interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/ividdec2.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDDEC2COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDDEC2COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDDEC2COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDDEC2COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDDEC2COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "viddec2_copy_ti.h"
#include "viddec2_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &VIDDEC2COPY_TI_IALG,   /* module ID */                         \
    NULL,                   /* activate */                          \
    VIDDEC2COPY_TI_alloc,   /* alloc */                             \
    NULL,                   /* control (NULL => no control ops) */  \
    NULL,                   /* deactivate */                        \
    VIDDEC2COPY_TI_free,    /* free */                              \
    VIDDEC2COPY_TI_initObj, /* init */                              \
    NULL,                   /* moved */                             \
    NULL                    /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDDEC2COPY_TI_IVIDDECCOPY ========
 *  This structure defines TI's implementation of the IVIDDEC2 interface
 *  for the VIDDEC2COPY_TI module.
 */
IVIDDEC2_Fxns VIDDEC2COPY_TI_IVIDDEC2COPY = {
    {IALGFXNS},
    VIDDEC2COPY_TI_process,
    VIDDEC2COPY_TI_control,
};

/*
 *  ======== VIDDEC2COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDDEC2COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("VIDDEC2COPY_TI_IALG .set VIDDEC2COPY_TI_IVIDDEC2COPY");

#else

/* Symbol has a single leading underscore */
asm("_VIDDEC2COPY_TI_IALG .set _VIDDEC2COPY_TI_IVIDDEC2COPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDDEC2COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IVIDDEC2_Params VIDDEC2COPY_TI_PARAMS = {
    sizeof(IVIDDEC2_Params),
    1024,                           /* maxHeight */
    1024,                           /* maxWidth */
    30000,                          /* maxFrameRate */
    10000000,                       /* maxBitRate */
    XDM_BYTE,                       /* dataEndianness */
    XDM_CHROMAFORMAT_DEFAULT        /* forceChromaFormat */
};

/*
 *  ======== VIDDEC2COPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC2COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(VIDDEC2COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== VIDDEC2COPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC2COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (VIDDEC2COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== VIDDEC2COPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC2COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
        IALG_Handle parent, const IALG_Params *algParams)
{
    VIDDEC2COPY_TI_Obj *obj = (VIDDEC2COPY_TI_Obj *)handle;
    const IVIDDEC2_Params *params = (IVIDDEC2_Params *)algParams;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDDEC2COPY_TI_PARAMS;
    }

    obj->outputChromaFormat = params->forceChromaFormat;

    return (IALG_EOK);
}


/*
 *  ======== VIDDEC2COPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDDEC2COPY_TI_process(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->decodedBufs.extendedError);

        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->decodedBufs.extendedError);

        return (IVIDDEC2_EFAIL);
    }

    numInBytes = inArgs->numBytes;

    /*
     * Sanity check that inBufs->descs[0].bufSize is really capable of holding
     * numInBytes bytes of data, and that outBufs->bufSizes[0]
     * can hold the 'encoded' data.
     */
    if ((inBufs->descs[0].bufSize < inArgs->numBytes) ||
            (outBufs->bufSizes[0] < MINOUTBUFSIZE)){
        /* inBuf is smaller than provided data(!) or "too small" outBuf */
        XDM_SETUNSUPPORTEDPARAM(outArgs->decodedBufs.extendedError);

        return (IVIDDEC2_EFAIL);
    }

    /* everything looks good, do the 'encode', set outArgs and return */
    memcpy(outBufs->bufs[0], inBufs->descs[0].buf, numInBytes);

    /* report how we accessed the input buffer */
    inBufs->descs[0].accessMask = 0;
    XDM_SETACCESSMODE_READ(inBufs->descs[0].accessMask);

    /* outArgs->bytesConsumed reports the total number of bytes decoded */
    outArgs->bytesConsumed = numInBytes;

    /* Fill out the rest of the outArgs struct */
    outArgs->outputID[0] = inArgs->inputID;
    outArgs->outputID[1] = 0;  /* end of array - invalid ID */

    outArgs->decodedBufs.numBufs = 1;
    outArgs->decodedBufs.frameWidth = numInBytes; /* minBytes wide */
    outArgs->decodedBufs.frameHeight = 1;       /* one pixel high */
    outArgs->decodedBufs.framePitch = 0;        /* TODO */

    outArgs->decodedBufs.bufDesc[0].buf = outBufs->bufs[0];
    outArgs->decodedBufs.bufDesc[0].bufSize = outBufs->bufSizes[0];

    /* initialize the accessMask, then indicate how we accessed it */
    outArgs->decodedBufs.bufDesc[0].accessMask = 0;
    XDM_SETACCESSMODE_WRITE(outArgs->decodedBufs.bufDesc[0].accessMask);

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

    outArgs->freeBufID[0] = inArgs->inputID;  /* release the only outBuf */
    outArgs->freeBufID[1] = 0; /* end of array - invalid ID */
    outArgs->outBufsInUseFlag = XDAS_FALSE;

    return (IVIDDEC2_EOK);
}


/*
 *  ======== VIDDEC2COPY_TI_control ========
 */
XDAS_Int32 VIDDEC2COPY_TI_control(IVIDDEC2_Handle handle, IVIDDEC2_Cmd id,
    IVIDDEC2_DynamicParams *dynParams, IVIDDEC2_Status *status)
{
    XDAS_Int32 retVal;
    VIDDEC2COPY_TI_Obj *obj = (VIDDEC2COPY_TI_Obj *)handle;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->size != sizeof(*status))) {
        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;
            status->outputHeight = 0;  /* TODO */
            status->outputWidth = 0;  /* TODO */
            status->frameRate = 0;  /* TODO */
            status->bitRate = 0;  /* TODO */
            status->contentType = 0;  /* TODO */
            status->outputChromaFormat = obj->outputChromaFormat;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IVIDDEC2_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IVIDDEC2_EOK;
            break;

        case XDM_SETDEFAULT:
            obj->outputChromaFormat = VIDDEC2COPY_TI_PARAMS.forceChromaFormat;

            retVal = IVIDDEC2_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IVIDDEC2_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize > strlen(VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IVIDDEC2_EOK;
            }
            else {
                retVal = IVIDDEC2_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IVIDDEC2_EFAIL;
            break;
    }

    return (retVal);
}
