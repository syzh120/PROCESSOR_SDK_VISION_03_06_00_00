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
 *  ======== sphdec1_copy.c ========
 *  Speech decoder "copy" algorithm, PCM codec family.
 *
 *  This file contains an implementation of the ISPHDEC1 interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/isphdec1.h>
#include <ti/xdais/dm/ispeech1_pcm.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(SPHDEC1COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(SPHDEC1COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(SPHDEC1COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(SPHDEC1COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(SPHDEC1COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "sphdec1_copy_ti.h"
#include "sphdec1_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &SPHDEC1COPY_TI_IALG,       /* module ID */                         \
    NULL,                       /* activate */                          \
    SPHDEC1COPY_TI_alloc,       /* alloc */                             \
    NULL,                       /* control (NULL => no control ops) */  \
    NULL,                       /* deactivate */                        \
    SPHDEC1COPY_TI_free,        /* free */                              \
    SPHDEC1COPY_TI_initObj,     /* init */                              \
    NULL,                       /* moved */                             \
    NULL                        /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== SPHDEC1COPY_TI_ISPHDECCOPY ========
 *  This structure defines TI's implementation of the ISPHDEC1 interface
 *  for the SPHDEC1COPY_TI module.
 */
ISPHDEC1_Fxns SPHDEC1COPY_TI_ISPHDEC1COPY = { /* module_vendor_interface */
    {IALGFXNS},
    SPHDEC1COPY_TI_process,
    SPHDEC1COPY_TI_control,
};

/*
 *  ======== SPHDEC1COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the SPHDEC1COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("SPHDEC1COPY_TI_IALG .set SPHDEC1COPY_TI_ISPHDEC1COPY");

#else

/* Symbol has a single leading underscore */
asm("_SPHDEC1COPY_TI_IALG .set _SPHDEC1COPY_TI_ISPHDEC1COPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns SPHDEC1COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

ISPHDEC1_Params SPHDEC1COPY_TI_PARAMS = {
    sizeof(ISPHDEC1_Params),
    ISPEECH1_PCM_COMPAND_DEFAULT,
    0,                              /* packingType is a don't care for PCM */
    0,                              /* codecSelect is a don't care for PCM */
    0,                              /* bitRate is a don't care for PCM */
    0,                              /* reserved */
    NULL
};

/*
 *  ======== SPHDEC1COPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int SPHDEC1COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(SPHDEC1COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== SPHDEC1COPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int SPHDEC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return(SPHDEC1COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== SPHDEC1COPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int SPHDEC1COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle parent, const IALG_Params *algParams)
{
    SPHDEC1COPY_TI_Obj *obj = (SPHDEC1COPY_TI_Obj *)handle;
    const ISPHDEC1_Params *params = (ISPHDEC1_Params *)algParams;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &SPHDEC1COPY_TI_PARAMS;
    }

    obj->compandingLaw = params->compandingLaw;
    obj->packingType = params->packingType;
    obj->codecSelection = params->codecSelection;
    obj->postFilter = ISPEECH1_POSTFILTER_DEFAULT;
    obj->bitRate = params->bitRate;

    return (IALG_EOK);
}


/*
 *  ======== SPHDEC1COPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 SPHDEC1COPY_TI_process(ISPHDEC1_Handle h,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    ISPHDEC1_InArgs *inArgs, ISPHDEC1_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (ISPHDEC1_EUNSUPPORTED);
    }

    /*
     * The number of bytes we can consume is the lesser of the specified
     * number of bytes to decode (inBuf->bufSize) and the size of the
     * buffer that will contain the output (outBuf->bufSize).
     */
    numInBytes = (inBuf->bufSize <= outBuf->bufSize) ?
            inBuf->bufSize : outBuf->bufSize;

    /* process the data: read input, produce output */
    memcpy(outBuf->buf, inBuf->buf, numInBytes);

    /* report how we accessed the data buffers */
    XDM_CLEARACCESSMODE_WRITE(inBuf->accessMask);
    XDM_SETACCESSMODE_READ(inBuf->accessMask);

    XDM_CLEARACCESSMODE_READ(outBuf->accessMask);
    XDM_SETACCESSMODE_WRITE(outBuf->accessMask);

    /* Fill out the rest of the outArgs struct */
    outArgs->dataSize = 0;  /* TBD */
    outArgs->extendedError = 0;

    return (ISPHDEC1_EOK);
}


/*
 *  ======== SPHDEC1COPY_TI_control ========
 */
XDAS_Int32 SPHDEC1COPY_TI_control(ISPHDEC1_Handle handle, ISPHDEC1_Cmd id,
    ISPHDEC1_DynamicParams *dynParams, ISPHDEC1_Status *status)
{
    XDAS_Int32 retVal;
    SPHDEC1COPY_TI_Obj *obj = (SPHDEC1COPY_TI_Obj *)handle;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->size != sizeof(*status))) {
        return (ISPHDEC1_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->postFilter = obj->postFilter;
            status->extendedError = 0;
            status->compandingLaw = obj->compandingLaw;
            status->packingType = obj->packingType;
            status->codecSelection = obj->codecSelection;
            status->bitRate = obj->bitRate;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = ISPHDEC1_EOK;
            break;

        case XDM_SETPARAMS:
            obj->postFilter = dynParams->postFilter;
            retVal = ISPHDEC1_EOK;
            break;

        case XDM_SETDEFAULT:
            obj->compandingLaw = SPHDEC1COPY_TI_PARAMS.compandingLaw;
            obj->packingType = SPHDEC1COPY_TI_PARAMS.packingType;
            obj->codecSelection = SPHDEC1COPY_TI_PARAMS.codecSelection;
            obj->postFilter = ISPEECH1_POSTFILTER_DEFAULT;

            retVal = ISPHDEC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = ISPHDEC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize > strlen(VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = ISPHDEC1_EOK;
            }
            else {
                retVal = ISPHDEC1_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = ISPHDEC1_EFAIL;
            break;
    }

    return (retVal);
}
