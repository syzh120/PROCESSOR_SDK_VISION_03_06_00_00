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
 *  ======== auddec1copy.c ========
 *  Audio decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IAUDDEC1 interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/iauddec1.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(AUDDEC1COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(AUDDEC1COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(AUDDEC1COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(AUDDEC1COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(AUDDEC1COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "auddec1copy_ti.h"
#include "auddec1copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &AUDDEC1COPY_TI_IALG,/* module ID */                        \
    NULL,               /* activate */                          \
    &AUDDEC1COPY_TI_alloc,/* alloc */                           \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    &AUDDEC1COPY_TI_free, /* free */                            \
    &AUDDEC1COPY_TI_initObj, /* init */                         \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== AUDDEC1COPY_TI_AUDDEC1COPY ========
 *  This structure defines TI's implementation of the IAUDDEC1 interface
 *  for the AUDDEC1COPY_TI module.
 */
IAUDDEC1_Fxns AUDDEC1COPY_TI_IAUDDEC1COPY = {    /* module_vendor_interface */
    {IALGFXNS},
    &AUDDEC1COPY_TI_process,
    &AUDDEC1COPY_TI_control,
};

/*
 *  ======== AUDDEC1COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the AUDDEC1COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("AUDDEC1COPY_TI_IALG .set AUDDEC1COPY_TI_IAUDDEC1COPY");

#else

/* Symbol has a single leading underscore */
asm("_AUDDEC1COPY_TI_IALG .set _AUDDEC1COPY_TI_IAUDDEC1COPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns AUDDEC1COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IAUDDEC1_Params AUDDEC1COPY_TI_PARAMS = {
    sizeof(IAUDDEC1_Params),
    8,                              /* outputPCMWidth */
    IAUDIO_BLOCK,                   /* pcmFormat */
    XDM_BYTE                        /* dataEndianness */
};

/*
 *  ======== AUDDEC1COPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int AUDDEC1COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(AUDDEC1COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== AUDDEC1COPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int AUDDEC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (AUDDEC1COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== AUDDEC1COPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int AUDDEC1COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
        IALG_Handle parent, const IALG_Params *algParams)
{
    const IAUDDEC1_Params *params = (const IAUDDEC1_Params *)algParams;
    AUDDEC1COPY_TI_Obj *obj = (AUDDEC1COPY_TI_Obj *)handle;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &AUDDEC1COPY_TI_PARAMS;
    }

    obj->outputPCMWidth = params->outputPCMWidth;
    obj->pcmFormat = params->pcmFormat;
    obj->dataEndianness = params->dataEndianness;

    return (IALG_EOK);
}


/*
 *  ======== AUDDEC1COPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 AUDDEC1COPY_TI_process(IAUDDEC1_Handle handle, XDM1_BufDesc *inBufs,
    XDM1_BufDesc *outBufs, IAUDDEC1_InArgs *inArgs, IAUDDEC1_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IAUDDEC1_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IAUDDEC1_EFAIL);
    }

    numInBytes = inArgs->numBytes;

    /*
     * Sanity check that inBufs->descs[0].bufSize is really capable of holding
     * numInBytes bytes of data, and that outBufs->descs[0].bufSize
     * can hold the 'encoded' data.
     */
    if ((numInBytes > inBufs->descs[0].bufSize) ||
            (numInBytes > outBufs->descs[0].bufSize)) {

        /* inBuf is smaller than provided data(!) or "too small" outBuf */
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IAUDDEC1_EFAIL);
    }

    /* everything looks good, do the decode, set outArgs and return */
    memcpy(outBufs->descs[0].buf, inBufs->descs[0].buf, numInBytes);

    /* report how we accessed the data buffers */
    XDM_CLEARACCESSMODE_WRITE(inBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->descs[0].accessMask);

    XDM_CLEARACCESSMODE_READ(outBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_WRITE(outBufs->descs[0].accessMask);

    /* outArgs->bytesGenerated reports the total number of bytes encoded */
    outArgs->bytesConsumed = numInBytes;

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;
    outArgs->numSamples = outArgs->bytesConsumed;  /* a sample == a byte */
    outArgs->channelMode = IAUDIO_2_0;  /* TODO */
    outArgs->lfeFlag = XDAS_FALSE;  /* TODO */
    outArgs->dualMonoMode = 0;  /* TODO */
    outArgs->sampleRate = 0;  /* TODO */

    return (IAUDDEC1_EOK);
}


/*
 *  ======== AUDDEC1COPY_TI_control ========
 */
XDAS_Int32 AUDDEC1COPY_TI_control(IAUDDEC1_Handle handle, IAUDDEC1_Cmd id,
    IAUDDEC1_DynamicParams *dynParams, IAUDDEC1_Status *status)
{
    XDAS_Int32 retVal;
    AUDDEC1COPY_TI_Obj *obj = (AUDDEC1COPY_TI_Obj *)handle;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->size != sizeof(*status))) {

        return (IAUDDEC1_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;
            status->validFlag = XDAS_TRUE;
            status->lfeFlag = XDAS_FALSE;  /* TODO */
            status->bitRate = 0;  /* TODO */
            status->sampleRate = 0;  /* TODO */
            status->channelMode = IAUDIO_2_0;  /* TODO */
            status->pcmFormat = obj->pcmFormat;
            status->numSamples = 0;  /* TODO */
            status->outputBitsPerSample = 8;  /* a sample == a byte */
            status->dualMonoMode = 0;  /* TODO */

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IAUDDEC1_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IAUDDEC1_EOK;
            break;

        case XDM_SETDEFAULT:
            obj->outputPCMWidth = AUDDEC1COPY_TI_PARAMS.outputPCMWidth;
            obj->pcmFormat = AUDDEC1COPY_TI_PARAMS.pcmFormat;
            obj->dataEndianness = AUDDEC1COPY_TI_PARAMS.dataEndianness;

            retVal = IAUDDEC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IAUDDEC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                    (status->data.bufSize > strlen(VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IAUDDEC1_EOK;
            }
            else {
                retVal = IAUDDEC1_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IAUDDEC1_EUNSUPPORTED;
            break;
    }

    return (retVal);
}
