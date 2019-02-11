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
 *  ======== imgdec1_copy.c ========
 *  Image decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IIMGDEC1 interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/iimgdec1.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(IMGDEC1COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(IMGDEC1COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(IMGDEC1COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(IMGDEC1COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(IMGDEC1COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "imgdec1_copy_ti.h"
#include "imgdec1_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &IMGDEC1COPY_TI_IALG,/* module ID */                        \
    NULL,               /* activate */                          \
    IMGDEC1COPY_TI_alloc,/* alloc */                            \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    IMGDEC1COPY_TI_free, /* free */                             \
    IMGDEC1COPY_TI_initObj, /* init */                          \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== IMGDEC1COPY_TI_IIMGDECCOPY ========
 *  This structure defines TI's implementation of the IIMGDEC1 interface
 *  for the IMGDEC1COPY_TI module.
 */
IIMGDEC1_Fxns IMGDEC1COPY_TI_IIMGDEC1COPY = {    /* module_vendor_interface */
    {IALGFXNS},
    IMGDEC1COPY_TI_process,
    IMGDEC1COPY_TI_control,
};

/*
 *  ======== IMGDEC1COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the IMGDEC1COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("IMGDEC1COPY_TI_IALG .set IMGDEC1COPY_TI_IIMGDEC1COPY");

#else

/* Symbol has a single leading underscore */
asm("_IMGDEC1COPY_TI_IALG .set _IMGDEC1COPY_TI_IIMGDEC1COPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns IMGDEC1COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IIMGDEC1_Params IMGDEC1COPY_TI_PARAMS = {
    sizeof(IIMGDEC1_Params),
    1024,                           /* maxHeight */
    1024,                           /* maxWidth */
    1,                              /* maxScans */
    XDM_BYTE,                       /* dataEndianness */
    XDM_CHROMAFORMAT_DEFAULT        /* forceChromaFormat */
};

/*
 *  ======== IMGDEC1COPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int IMGDEC1COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(IMGDEC1COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== IMGDEC1COPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int IMGDEC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return(IMGDEC1COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== IMGDEC1COPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int IMGDEC1COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    IMGDEC1COPY_TI_Obj *obj = (IMGDEC1COPY_TI_Obj *)handle;
    const IIMGDEC1_Params *params = (IIMGDEC1_Params *)algParams;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &IMGDEC1COPY_TI_PARAMS;
    }

    obj->outputChromaFormat = params->forceChromaFormat;

    return (IALG_EOK);
}


/*
 *  ======== IMGDEC1COPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 IMGDEC1COPY_TI_process(IIMGDEC1_Handle h, XDM1_BufDesc *inBufs,
    XDM1_BufDesc *outBufs, IIMGDEC1_InArgs *inArgs, IIMGDEC1_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IIMGDEC1_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IIMGDEC1_EFAIL);
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

        return (IIMGDEC1_EFAIL);
    }

    /* everything looks good, do the decode, set outArgs and return */
    memcpy(outBufs->descs[0].buf, inBufs->descs[0].buf, numInBytes);

    /* report how we accessed the data buffers */
    XDM_CLEARACCESSMODE_WRITE(inBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->descs[0].accessMask);

    XDM_CLEARACCESSMODE_READ(outBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_WRITE(outBufs->descs[0].accessMask);

    /* outArgs->bytesConsumed reports the total number of bytes decoded */
    outArgs->bytesConsumed = numInBytes;

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;
    outArgs->currentAU = 0;  /* TODO */
    outArgs->currentScan = 0;  /* TODO */

    return (IIMGDEC1_EOK);
}


/*
 *  ======== IMGDEC1COPY_TI_control ========
 */
XDAS_Int32 IMGDEC1COPY_TI_control(IIMGDEC1_Handle handle, IIMGDEC1_Cmd id,
    IIMGDEC1_DynamicParams *dynParams, IIMGDEC1_Status *status)
{
    XDAS_Int32 retVal;
    IMGDEC1COPY_TI_Obj *obj = (IMGDEC1COPY_TI_Obj *)handle;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->size != sizeof(*status))) {
        return (IIMGDEC1_EUNSUPPORTED);
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
            status->imageWidth = 0;  /* TODO */
            status->outputChromaFormat = obj->outputChromaFormat;
            status->totalAU = 0;  /* TODO */
            status->totalScan = 0;  /* TODO */

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IIMGDEC1_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IIMGDEC1_EOK;
            break;

        case XDM_SETDEFAULT:
            obj->outputChromaFormat = IMGDEC1COPY_TI_PARAMS.forceChromaFormat;

            retVal = IIMGDEC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IIMGDEC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize > strlen(VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IIMGDEC1_EOK;
            }
            else {
                retVal = IIMGDEC1_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IIMGDEC1_EFAIL;
            break;
    }

    return (retVal);
}
