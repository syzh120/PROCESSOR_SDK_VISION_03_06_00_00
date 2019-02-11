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
 *  ======== videnc2_copy.c ========
 *  Video encoder "copy" algorithm.
 *
 *  This file contains an implementation of the IVIDENC2 interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/ividenc2.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDENC2COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDENC2COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDENC2COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDENC2COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDENC2COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "videnc2_copy_ti.h"
#include "videnc2_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &VIDENC2COPY_TI_IALG,       /* module ID */                         \
    NULL,                       /* activate */                          \
    VIDENC2COPY_TI_alloc,       /* alloc */                             \
    NULL,                       /* control (NULL => no control ops) */  \
    NULL,                       /* deactivate */                        \
    VIDENC2COPY_TI_free,        /* free */                              \
    VIDENC2COPY_TI_initObj,     /* init */                              \
    NULL,                       /* moved */                             \
    NULL                        /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDENC2COPY_TI_IVIDENCCOPY ========
 *  This structure defines TI's implementation of the IVIDENC2 interface
 *  for the VIDENC2COPY_TI module.
 */
IVIDENC2_Fxns VIDENC2COPY_TI_IVIDENC2COPY = {    /* module_vendor_interface */
    {IALGFXNS},
    VIDENC2COPY_TI_process,
    VIDENC2COPY_TI_control,
};

/*
 *  ======== VIDENC2COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDENC2COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("VIDENC2COPY_TI_IALG .set VIDENC2COPY_TI_IVIDENC2COPY");

#else

/* Symbol has a single leading underscore */
asm("_VIDENC2COPY_TI_IALG .set _VIDENC2COPY_TI_IVIDENC2COPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDENC2COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IVIDENC2_Params VIDENC2COPY_TI_PARAMS = {
    sizeof(IVIDENC2_Params),
    0,                              /* encodingPreset - TODO */
    0,                              /* rateControlPreset - TODO */
    1024,                           /* maxHeight */
    1024,                           /* maxWidth */
    XDM_BYTE,                       /* dataEndianness */
    1,                              /* maxInterFrameInterval */
    0,                              /* maxBitRate - TODO */
    0,                              /* minBitRate - TODO */
    XDM_CHROMAFORMAT_DEFAULT,       /* inputChromaFormat */
    IVIDEO_CONTENTTYPE_DEFAULT,     /* inputContentType */
    IVIDEO_ENCODE_ONLY,             /* operatingMode */
    IVIDENC2_DEFAULTPROFILE,        /* profile */
    IVIDENC2_DEFAULTLEVEL,          /* level */
    IVIDEO_ENTIREFRAME,             /* inputDataMode */
    IVIDEO_ENTIREFRAME,             /* outputDataMode */
    0,                              /* numInputDataUnits */
    0,                              /* numOutputDataUnits */
    {
        IVIDEO_METADATAPLANE_NONE,  /* metadataType[0] */
        IVIDEO_METADATAPLANE_NONE,  /* metadataType[1] */
        IVIDEO_METADATAPLANE_NONE,  /* metadataType[2] */
    }
};

/*
 *  ======== VIDENC2COPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDENC2COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    const IVIDENC2_Params *params = (IVIDENC2_Params *)algParams;

    /*
     * Validate create params.  Note that we return a unique, clear error
     * to the application so they know exactly why this create failed.
     * Returning generic error codes (e.g. IVIDENC2_EFAIL) leads to support
     * issues as it's unclear why the creation failed (unsupported params,
     * out of memory/resources, etc).
     */
    if (params != NULL) {
        if ((params->metadataType[0] != IVIDEO_METADATAPLANE_NONE) ||
                (params->metadataType[1] != IVIDEO_METADATAPLANE_NONE) ||
                (params->metadataType[2] != IVIDEO_METADATAPLANE_NONE)) {
            /* We don't support metadata */
            return (VIDENC2COPY_TI_EUNSUPPORTEDMETADATAPARAM);
        }

        if ((params->inputDataMode != IVIDEO_ENTIREFRAME) ||
                (params->outputDataMode != IVIDEO_ENTIREFRAME)) {
            /* We don't support subframe processing */
            return (VIDENC2COPY_TI_EUNSUPPORTEDDATAMODE);
        }
    }

    /* Request memory for my object */
    memTab[0].size = sizeof(VIDENC2COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== VIDENC2COPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDENC2COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (VIDENC2COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== VIDENC2COPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDENC2COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
        IALG_Handle parent, const IALG_Params *algParams)
{
    const IVIDENC2_Params *params = (IVIDENC2_Params *)algParams;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDENC2COPY_TI_PARAMS;
    }

    return (IALG_EOK);
}


/*
 *  ======== VIDENC2COPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDENC2COPY_TI_process(IVIDENC2_Handle h, IVIDEO2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDENC2_InArgs *inArgs, IVIDENC2_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* Validate arguments - this codec supports "base" XDM. */
    if (((inArgs->size != sizeof(*inArgs))) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDENC2_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numPlanes < 1) || (outBufs->numBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDENC2_EFAIL);
    }

    /* currently this codec only supports standard, flat, "raw" memory */
    if (outBufs->descs[0].memType != XDM_MEMTYPE_RAW) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDENC2_EFAIL);
    }

    /* validate inputID */
    if (inArgs->inputID == 0) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDENC2_EFAIL);
    }

    /* validate control */
    if (inArgs->control != IVIDENC2_CTRL_NONE) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDENC2_EFAIL);
    }

    /* there's an available in and out buffer, how many samples? */
    numInBytes = (inBufs->planeDesc[0].bufSize.bytes <
            outBufs->descs[0].bufSize.bytes) ?
                inBufs->planeDesc[0].bufSize.bytes :
                outBufs->descs[0].bufSize.bytes;

    /* everything looks good, do the 'encode', set outArgs and return */
    memcpy(outBufs->descs[0].buf, inBufs->planeDesc[0].buf, numInBytes);

    /* memcpy read from inBuf and wrote to encodedBuf (in our case, outBuf) */
    XDM_CLEARACCESSMODE_WRITE(inBufs->planeDesc[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->planeDesc[0].accessMask);

    XDM_CLEARACCESSMODE_READ(outBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_WRITE(outBufs->descs[0].accessMask);

    /* outArgs->bytesGenerated reports the total number of bytes encoded */
    outArgs->bytesGenerated = numInBytes;

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;
    outArgs->encodedFrameType = 0;     /* TODO */
    outArgs->inputFrameSkip = IVIDEO_FRAME_ENCODED;
    outArgs->freeBufID[0] = inArgs->inputID;
    outArgs->freeBufID[1] = 0; /* zero-terminate the list */

    /* TODO - add support for reconBufs */
    outArgs->reconBufs.numPlanes = 0;
    outArgs->reconBufs.numMetaPlanes = 0;

    return (IVIDENC2_EOK);
}


/*
 *  ======== VIDENC2COPY_TI_control ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDENC2COPY_TI_control(IVIDENC2_Handle handle, IVIDENC2_Cmd id,
    IVIDENC2_DynamicParams *params, IVIDENC2_Status *status)
{
    XDAS_Int32 retVal;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((params->size != sizeof(*params)) ||
            (status->size != sizeof(*status))) {
        return (IVIDENC2_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;

            status->encodingPreset = 0; /* todo */
            status->rateControlPreset = 0; /* todo */
            status->maxInterFrameInterval = 0; /* todo */
            status->inputChromaFormat = 0; /* todo */
            status->inputContentType = 0; /* todo */
            status->operatingMode = 0; /* todo */
            status->profile = 0; /* todo */
            status->level = 0; /* todo */
            status->inputDataMode = 0; /* todo */
            status->outputDataMode = 0; /* todo */
            status->numInputDataUnits = 0; /* todo */
            status->numOutputDataUnits = 0; /* todo */
            status->configurationID = 0; /* todo */

            /*
             * This copy codec doesn't support metadata... the check
             * was done at create time.
             */
            status->metadataType[0] = IVIDEO_METADATAPLANE_NONE;
            status->metadataType[1] = IVIDEO_METADATAPLANE_NONE;
            status->metadataType[2] = IVIDEO_METADATAPLANE_NONE;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0].bytes = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0].bytes = MINOUTBUFSIZE;
            status->bufInfo.inBufMemoryType[0] = XDM_MEMTYPE_RAW;
            status->bufInfo.outBufMemoryType[0] = XDM_MEMTYPE_RAW;
            status->bufInfo.minNumBufSets = 0; /* todo */

            status->encDynamicParams.inputHeight = 0; /* todo */
            status->encDynamicParams.inputWidth = 0; /* todo */
            status->encDynamicParams.refFrameRate = 0; /* todo */
            status->encDynamicParams.targetFrameRate = 0; /* todo */
            status->encDynamicParams.targetBitRate = 0; /* todo */
            status->encDynamicParams.intraFrameInterval = 0; /* todo */
            status->encDynamicParams.generateHeader = 0; /* todo */
            status->encDynamicParams.captureWidth = 0; /* todo */
            status->encDynamicParams.interFrameInterval = 0; /* todo */
            status->encDynamicParams.mvAccuracy = 0; /* todo */
            status->encDynamicParams.sampleAspectRatioWidth = 0; /* todo */
            status->encDynamicParams.sampleAspectRatioHeight = 0; /* todo */
            status->encDynamicParams.ignoreOutbufSizeFlag = XDAS_FALSE; /* todo */
            status->encDynamicParams.putDataFxn = NULL; /* todo */
            status->encDynamicParams.putDataHandle = 0; /* todo */
            status->encDynamicParams.getDataFxn = NULL; /* todo */
            status->encDynamicParams.getDataHandle = 0; /* todo */
            status->encDynamicParams.getBufferFxn = NULL; /* todo */
            status->encDynamicParams.getBufferHandle = 0; /* todo */

            retVal = IVIDENC2_EOK;
            break;

        case XDM_SETPARAMS:
        case XDM_SETLATEACQUIREARG:
            retVal = IVIDENC2_EOK;
            break;

        case XDM_SETDEFAULT:
            retVal = IVIDENC2_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IVIDENC2_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize > strlen(VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IVIDENC2_EOK;
            }
            else {
                retVal = IVIDENC2_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IVIDENC2_EUNSUPPORTED;
            break;
    }

    return (retVal);
}
