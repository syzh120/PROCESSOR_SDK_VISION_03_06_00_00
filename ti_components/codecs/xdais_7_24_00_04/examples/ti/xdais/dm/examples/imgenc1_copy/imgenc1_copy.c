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
 *  ======== imgenc1_copy.c ========
 *  Image encoder "copy" algorithm.
 *
 *  This file contains an implementation of the IIMGENC1 interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/iimgenc1.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(IMGENC1COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(IMGENC1COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(IMGENC1COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(IMGENC1COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(IMGENC1COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "imgenc1_copy_ti.h"
#include "imgenc1_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &IMGENC1COPY_TI_IALG,/* module ID */                        \
    NULL,               /* activate */                          \
    IMGENC1COPY_TI_alloc,/* alloc */                            \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    IMGENC1COPY_TI_free, /* free */                             \
    IMGENC1COPY_TI_initObj, /* init */                          \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== IMGENC1COPY_TI_IIMGENCCOPY ========
 *  This structure defines TI's implementation of the IIMGENC1 interface
 *  for the IMGENC1COPY_TI module.
 */
IIMGENC1_Fxns IMGENC1COPY_TI_IIMGENC1COPY = {    /* module_vendor_interface */
    {IALGFXNS},
    IMGENC1COPY_TI_process,
    IMGENC1COPY_TI_control,
};

/*
 *  ======== IMGENC1COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the IMGENC1COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("IMGENC1COPY_TI_IALG .set IMGENC1COPY_TI_IIMGENC1COPY");

#else

/* Symbol has a single leading underscore */
asm("_IMGENC1COPY_TI_IALG .set _IMGENC1COPY_TI_IIMGENC1COPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns IMGENC1COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IIMGENC1_Params IMGENC1COPY_TI_PARAMS = {
    sizeof(IIMGENC1_Params),
    1024,                           /* maxHeight */
    1024,                           /* maxWidth */
    1,                              /* maxScans */
    XDM_BYTE,                       /* dataEndianness */
    XDM_CHROMAFORMAT_DEFAULT        /* forceChromaFormat */
};


/*
 *  ======== IMGENC1COPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int IMGENC1COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(IMGENC1COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== IMGENC1COPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int IMGENC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return(IMGENC1COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== IMGENC1COPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int IMGENC1COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    const IIMGENC1_Params *params = (IIMGENC1_Params *)algParams;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &IMGENC1COPY_TI_PARAMS;
    }

    return (IALG_EOK);
}


/*
 *  ======== IMGENC1COPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 IMGENC1COPY_TI_process(IIMGENC1_Handle h, XDM1_BufDesc *inBufs,
    XDM1_BufDesc *outBufs, IIMGENC1_InArgs *inArgs, IIMGENC1_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IIMGENC1_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IIMGENC1_EFAIL);
    }

    numInBytes = inBufs->descs[0].bufSize < outBufs->descs[0].bufSize ?
        inBufs->descs[0].bufSize : outBufs->descs[0].bufSize;

    /* everything looks good, do the 'encode', set outArgs and return */
    memcpy(outBufs->descs[0].buf, inBufs->descs[0].buf, numInBytes);

    /* report how we accessed the data buffers */
    XDM_CLEARACCESSMODE_WRITE(inBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->descs[0].accessMask);

    XDM_CLEARACCESSMODE_READ(outBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_WRITE(outBufs->descs[0].accessMask);

    /* outArgs->bytesGenerated reports the total number of bytes encoded */
    outArgs->bytesGenerated = numInBytes;

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;
    outArgs->currentAU = 0;  /* TODO */

    return (IIMGENC1_EOK);
}


/*
 *  ======== IMGENC1COPY_TI_control ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 IMGENC1COPY_TI_control(IIMGENC1_Handle handle, IIMGENC1_Cmd id,
    IIMGENC1_DynamicParams *dynParams, IIMGENC1_Status *status)
{
    XDAS_Int32 retVal;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->size != sizeof(*status))) {
        return (IIMGENC1_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;
            status->totalAU = 0;  /* TODO */

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IIMGENC1_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IIMGENC1_EOK;
            break;

        case XDM_SETDEFAULT:
            retVal = IIMGENC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IIMGENC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize > strlen(VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IIMGENC1_EOK;
            }
            else {
                retVal = IIMGENC1_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IIMGENC1_EFAIL;

            break;
    }

    return (retVal);
}
