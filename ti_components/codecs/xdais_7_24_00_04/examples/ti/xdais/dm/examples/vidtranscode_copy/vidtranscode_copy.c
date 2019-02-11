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
 *  ======== vidtranscode_copy.c ========
 *  Video transcoder "copy" algorithm.
 *
 *  This file contains an implementation of the IVIDTRANSCODE interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/ividtranscode.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDTRANSCODECOPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDTRANSCODECOPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDTRANSCODECOPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDTRANSCODECOPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDTRANSCODECOPY_TI_alloc,   ".text:algAlloc")
#endif

#include "vidtranscode_copy_ti.h"
#include "vidtranscode_copy_ti_priv.h"

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
    &VIDTRANSCODECOPY_TI_IALG,  /* module ID */                         \
    NULL,                       /* activate */                          \
    VIDTRANSCODECOPY_TI_alloc,  /* alloc */                             \
    NULL,                       /* control (NULL => no control ops) */  \
    NULL,                       /* deactivate */                        \
    VIDTRANSCODECOPY_TI_free,   /* free */                              \
    VIDTRANSCODECOPY_TI_initObj,/* init */                              \
    NULL,                       /* moved */                             \
    NULL                        /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDTRANSCODECOPY_TI_IVIDTRANSCODECOPY ========
 *  This structure defines TI's implementation of the IVIDTRANSCODE interface
 *  for the VIDTRANSCODECOPY_TI module.
 */
IVIDTRANSCODE_Fxns VIDTRANSCODECOPY_TI_IVIDTRANSCODECOPY = {
    {IALGFXNS},
    VIDTRANSCODECOPY_TI_process,
    VIDTRANSCODECOPY_TI_control,
};

/*
 *  ======== VIDTRANSCODECOPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDTRANSCODECOPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("VIDTRANSCODECOPY_TI_IALG .set VIDTRANSCODECOPY_TI_IVIDTRANSCODECOPY");

#else

/* Symbol has a single leading underscore */
asm("_VIDTRANSCODECOPY_TI_IALG .set _VIDTRANSCODECOPY_TI_IVIDTRANSCODECOPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDTRANSCODECOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IVIDTRANSCODE_Params VIDTRANSCODECOPY_TI_PARAMS = {
    sizeof(IVIDTRANSCODE_Params),       /* size */
    1,                                  /* numOutputStreams */
    IVIDEO_MPEG2SP,                     /* formatInput */
    {
        IVIDEO_H264BP,                  /* formatOutput[0] */
        0,                              /* formatOutput[1] - don't care */
    },
        1024,                           /* maxHeightInput */
        1024,                           /* maxWidthInput */
        30000,                          /* maxFrameRateInput */
        10000000,                       /* maxBitRateInput */
    {
        1024,                           /* maxHeightOutput[0] */
        0,                              /* maxHeightOutput[1] - don't care */
    },
    {
        1024,                           /* maxWidthOutput[0] */
        0,                              /* maxWidthOutput[1] - don't care */
    },
    {
        30000,                          /* maxFrameRateOutput[0] */
        0,                              /* maxFrameRateOutput[1] - don't care */
    },
    {
        10000000,                       /* maxBitRateOutput[0] */
        0,                              /* maxBitRateOutput[1] - don't care */
    },
    XDM_BYTE                            /* dataEndianness */
};


/*
 *  ======== VIDTRANSCODECOPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDTRANSCODECOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(VIDTRANSCODECOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== VIDTRANSCODECOPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDTRANSCODECOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (VIDTRANSCODECOPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== VIDTRANSCODECOPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDTRANSCODECOPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    const IVIDTRANSCODE_Params *params = (IVIDTRANSCODE_Params *)algParams;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDTRANSCODECOPY_TI_PARAMS;
    }

    return (IALG_EOK);
}


/*
 *  ======== VIDTRANSCODECOPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDTRANSCODECOPY_TI_process(IVIDTRANSCODE_Handle h,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs,
    IVIDTRANSCODE_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDTRANSCODE_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDTRANSCODE_EFAIL);
    }

    numInBytes = inArgs->numBytes;

    /*
     * Sanity check that inBufs->descs[0].bufSize is really capable of holding
     * numInBytes bytes of data, and that outBufs->bufSizes[0]
     * can hold the 'transcoded' data.
     */
    if ((inBufs->descs[0].bufSize < inArgs->numBytes) ||
        (outBufs->bufSizes[0] < MINOUTBUFSIZE)){

        /* inBuf is smaller than provided data(!) or "too small" outBuf */
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDTRANSCODE_EFAIL);
    }

    /* everything looks good, do the 'transcode', set outArgs and return */
    memcpy(outBufs->bufs[0], inBufs->descs[0].buf, numInBytes);

    /* report _how_ we accessed the input buffer */
    XDM_CLEARACCESSMODE_WRITE(inBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->descs[0].accessMask);


    /* outArgs->bytesConsumed reports the total number of bytes decoded */
    outArgs->bitsConsumed = numInBytes * BITSPERBYTE;

    outArgs->bitsGenerated[0] = outArgs->bitsConsumed;
    outArgs->bitsGenerated[1] = 0;

    outArgs->decodedPictureType = IVIDEO_I_PICTURE;  /* Simple for now */
    outArgs->decodedPictureStructure = IVIDEO_INTERLACED_FRAME;

    outArgs->encodedPictureType[0] = IVIDEO_I_PICTURE;
    outArgs->encodedPictureType[1] = IVIDEO_NA_PICTURE;

    outArgs->encodedPictureStructure[0] = IVIDEO_INTERLACED_FRAME;
    outArgs->encodedPictureStructure[1] = IVIDEO_CONTENTTYPE_NA;

    outArgs->decodedHeight = 1;  /* one pixel high */
    outArgs->decodedWidth = numInBytes;  /* numInBytes wide */

    outArgs->outputID[0] = inArgs->inputID;
    outArgs->outputID[1] = 0;  /* invalid ID */

    outArgs->inputFrameSkipTranscodeFlag[0] = XDAS_FALSE;
    outArgs->inputFrameSkipTranscodeFlag[1] = XDAS_TRUE;  /* don't care */

    outArgs->encodedBuf[0].buf = outBufs->bufs[0];
    outArgs->encodedBuf[0].bufSize = outBufs->bufSizes[0];

    /* initialize the accessMask, then indicate how we accessed it */
    outArgs->encodedBuf[0].accessMask = 0;
    XDM_SETACCESSMODE_WRITE(outArgs->encodedBuf[0].accessMask);

    outArgs->outBufsInUseFlag = XDAS_FALSE;

    return (IVIDTRANSCODE_EOK);
}


/*
 *  ======== VIDTRANSCODECOPY_TI_control ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDTRANSCODECOPY_TI_control(IVIDTRANSCODE_Handle handle,
    IVIDTRANSCODE_Cmd id, IVIDTRANSCODE_DynamicParams *dynParams,
    IVIDTRANSCODE_Status *status)
{
    XDAS_Int32 retVal;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->size != sizeof(*status))) {
        return (IVIDTRANSCODE_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IVIDTRANSCODE_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IVIDTRANSCODE_EOK;
            break;

        case XDM_SETDEFAULT:
            retVal = IVIDTRANSCODE_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IVIDTRANSCODE_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize > strlen(VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IVIDTRANSCODE_EOK;
            }
            else {
                retVal = IVIDTRANSCODE_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IVIDTRANSCODE_EFAIL;
            break;
    }

    return (retVal);
}
