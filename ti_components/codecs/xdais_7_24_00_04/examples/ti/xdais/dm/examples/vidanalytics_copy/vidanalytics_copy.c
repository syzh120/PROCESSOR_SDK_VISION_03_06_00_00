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
 *  ======== vidanalytics_copy.c ========
 *  Video analytics "copy" algorithm.
 *
 *  This file contains an implementation of the IVIDANALYTICS interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/ividanalytics.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDANALYTICSCOPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDANALYTICSCOPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDANALYTICSCOPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDANALYTICSCOPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDANALYTICSCOPY_TI_alloc,   ".text:algAlloc")
#endif

#include "vidanalytics_copy_ti.h"
#include "vidanalytics_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

/* Helper definitions */
#define BITSPERBYTE     8       /* number of bits in a byte */

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &VIDANALYTICSCOPY_TI_IALG,  /* module ID */                         \
    NULL,                       /* activate */                          \
    VIDANALYTICSCOPY_TI_alloc,  /* alloc */                             \
    NULL,                       /* control (NULL => no control ops) */  \
    NULL,                       /* deactivate */                        \
    VIDANALYTICSCOPY_TI_free,   /* free */                              \
    VIDANALYTICSCOPY_TI_initObj,/* init */                              \
    NULL,                       /* moved */                             \
    NULL                        /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDANALYTICSCOPY_TI_IVIDANALYTICSCOPY ========
 *  This structure defines TI's implementation of the IVIDANALYTICS interface
 *  for the VIDANALYTICSCOPY_TI module.
 */
IVIDANALYTICS_Fxns VIDANALYTICSCOPY_TI_IVIDANALYTICSCOPY = {
    {IALGFXNS},
    VIDANALYTICSCOPY_TI_process,
    VIDANALYTICSCOPY_TI_control,
};

/*
 *  ======== VIDANALYTICSCOPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDANALYTICSCOPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("VIDANALYTICSCOPY_TI_IALG .set VIDANALYTICSCOPY_TI_IVIDANALYTICSCOPY");

#else

/* Symbol has a single leading underscore */
asm("_VIDANALYTICSCOPY_TI_IALG .set _VIDANALYTICSCOPY_TI_IVIDANALYTICSCOPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDANALYTICSCOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IVIDANALYTICS_Params VIDANALYTICSCOPY_TI_PARAMS = {
    sizeof(IVIDANALYTICS_Params),       /* size */
    10000,                              /* maxHeight */
    10000,                              /* maxWidth */
    10000,                              /* maxFrameRate */
    XDM_BYTE,                           /* dataEndianness */
    XDM_CHROMAFORMAT_DEFAULT,           /* inputChromaFormat */
    10                                  /* maxRules */
};

/*
 *  ======== VIDANALYTICSCOPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDANALYTICSCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(VIDANALYTICSCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== VIDANALYTICSCOPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDANALYTICSCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (VIDANALYTICSCOPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== VIDANALYTICSCOPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDANALYTICSCOPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    const IVIDANALYTICS_Params *params = (IVIDANALYTICS_Params *)algParams;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDANALYTICSCOPY_TI_PARAMS;
    }

    return (IALG_EOK);
}


/*
 *  ======== VIDANALYTICSCOPY_TI_process ========
 */
XDAS_Int32 VIDANALYTICSCOPY_TI_process(IVIDANALYTICS_Handle handle,
    XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, IVIDANALYTICS_InArgs *inArgs,
    IVIDANALYTICS_OutArgs *outArgs)
{
    VIDANALYTICSCOPY_TI_Obj *obj = (VIDANALYTICSCOPY_TI_Obj *)handle;

    /* begin this process call with 'good' view */
    obj->viewState = IVIDANALYTICS_VIEWSTATE_GOOD;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);
        XDM_SETUNSUPPORTEDPARAM(obj->extendedError);

        return (IVIDANALYTICS_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);
        XDM_SETUNSUPPORTEDPARAM(obj->extendedError);

        return (IVIDANALYTICS_EFAIL);
    }

    /*
     * Sanity check that outBufs->descs[0].bufSize can hold the
     * 'analyzed' data.
     */
    if (outBufs->descs[0].bufSize < inBufs->descs[0].bufSize){

        /* "too small" outBuf */
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);
        XDM_SETUNSUPPORTEDPARAM(obj->extendedError);

        return (IVIDANALYTICS_EFAIL);
    }

    /* everything looks good, do the 'analysis', set outArgs and return */
    memcpy(outBufs->descs[0].buf, inBufs->descs[0].buf,
        inBufs->descs[0].bufSize);

    /* report _how_ we accessed the input buffer */
    XDM_CLEARACCESSMODE_WRITE(inBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->descs[0].accessMask);

    /* indicate how we accessed outBufs it */
    XDM_CLEARACCESSMODE_READ(outBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_WRITE(outBufs->descs[0].accessMask);

    /* didn't detect anything. */
    outArgs->numTargets = 0;
    outArgs->numEvents = 0;

    /* note that this example doesn't set outArgs->date. */

    outArgs->extendedError = 0;

    return (IVIDANALYTICS_EOK);
}


/*
 *  ======== VIDANALYTICSCOPY_TI_control ========
 */
XDAS_Int32 VIDANALYTICSCOPY_TI_control(IVIDANALYTICS_Handle handle,
    IVIDANALYTICS_Cmd id, IVIDANALYTICS_DynamicParams *dynParams,
    IVIDANALYTICS_Status *status)
{
    VIDANALYTICSCOPY_TI_Obj *obj = (VIDANALYTICSCOPY_TI_Obj *)handle;
    XDAS_Int32 retVal;
    Int i;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->size != sizeof(*status))) {
        return (IVIDANALYTICS_EUNSUPPORTED);
    }

    /* validate data field. */
    if (status->data.numBufs > XDM_MAX_IO_BUFFERS) {
        /* too many buffers.  App forgot to initialize the data field? */
        return (IVIDANALYTICS_EUNSUPPORTED);
    }

    /*
     * Initialize for the general case where we don't access any data buffers.
     * Note, this is not a sparse array.
     */
    for (i = 0; i < status->data.numBufs; i++) {
        XDM_CLEARACCESSMODE_READ(status->data.descs[i].accessMask);
        XDM_CLEARACCESSMODE_WRITE(status->data.descs[i].accessMask);
    }

    switch (id) {
        case XDM_GETSTATUS:
            status->extendedError = obj->extendedError;
            status->viewState = obj->viewState;

            retVal = IVIDANALYTICS_EOK;
            break;

        case XDM_GETBUFINFO:
            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IVIDANALYTICS_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IVIDANALYTICS_EOK;
            break;

        case XDM_SETDEFAULT:
            retVal = IVIDANALYTICS_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            obj->viewState = IVIDANALYTICS_VIEWSTATE_GOOD;
            obj->extendedError = 0;

            retVal = IVIDANALYTICS_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.descs[0].buf != NULL) &&
                    (status->data.descs[0].bufSize >
                        strlen(VERSIONSTRING))) {

                strncpy((char *)status->data.descs[0].buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.descs[0].accessMask);

                retVal = IVIDANALYTICS_EOK;
            }
            else {
                retVal = IVIDANALYTICS_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IVIDANALYTICS_EFAIL;
            break;
    }

    return (retVal);
}
