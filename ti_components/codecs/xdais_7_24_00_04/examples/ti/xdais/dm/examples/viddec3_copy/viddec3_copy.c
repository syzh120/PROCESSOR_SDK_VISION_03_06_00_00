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
 *  ======== viddec3_copy.c ========
 *  Video decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IVIDDEC3 interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/ividdec3.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDDEC3COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDDEC3COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDDEC3COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDDEC3COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDDEC3COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "viddec3_copy_ti.h"
#include "viddec3_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &VIDDEC3COPY_TI_IALG,   /* module ID */                         \
    NULL,                   /* activate */                          \
    VIDDEC3COPY_TI_alloc,   /* alloc */                             \
    NULL,                   /* control (NULL => no control ops) */  \
    NULL,                   /* deactivate */                        \
    VIDDEC3COPY_TI_free,    /* free */                              \
    VIDDEC3COPY_TI_initObj, /* init */                              \
    NULL,                   /* moved */                             \
    NULL                    /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDDEC3COPY_TI_IVIDDECCOPY ========
 *  This structure defines TI's implementation of the IVIDDEC3 interface
 *  for the VIDDEC3COPY_TI module.
 */
IVIDDEC3_Fxns VIDDEC3COPY_TI_IVIDDEC3COPY = {
    {IALGFXNS},
    VIDDEC3COPY_TI_process,
    VIDDEC3COPY_TI_control,
};

/*
 *  ======== VIDDEC3COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDDEC3COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("VIDDEC3COPY_TI_IALG .set VIDDEC3COPY_TI_IVIDDEC3COPY");

#else

/* Symbol has a single leading underscore */
asm("_VIDDEC3COPY_TI_IALG .set _VIDDEC3COPY_TI_IVIDDEC3COPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDDEC3COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IVIDDEC3_Params VIDDEC3COPY_TI_PARAMS = {
    sizeof(IVIDDEC3_Params),
    1024,                           /* maxHeight */
    1024,                           /* maxWidth */
    30000,                          /* maxFrameRate */
    10000000,                       /* maxBitRate */
    XDM_BYTE,                       /* dataEndianness */
    XDM_CHROMAFORMAT_DEFAULT,       /* forceChromaFormat */
    0,                              /* operatingMode - todo */
    IVIDDEC3_DISPLAYDELAY_DEFAULT,  /* displayDelay */
    0,                              /* inputDataMode - todo */
    0,                              /* inputDataMode - todo */
    0,                              /* numInputDataUnits - todo */
    0,                              /* numOutputDataUnits - todo */
    0,                              /* errorInfoMode - todo */
    IVIDDEC3_DISPLAYBUFS_EMBEDDED,  /* displayBufsMode */
    {
        IVIDEO_METADATAPLANE_NONE,  /* metadataType[0] */
        IVIDEO_METADATAPLANE_NONE,  /* metadataType[1] */
        IVIDEO_METADATAPLANE_NONE,  /* metadataType[2] */
    }
};

/*
 *  ======== VIDDEC3COPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC3COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    const IVIDDEC3_Params *params = (IVIDDEC3_Params *)algParams;

    /*
     * Validate create params.  Note that we return a unique, clear error
     * to the application so they know exactly why this create failed.
     * Returning generic error codes (e.g. IVIDDEC3_EFAIL) leads to support
     * issues as it's unclear why the creation failed (unsupported params,
     * out of memory/resources, etc).
     */
    if (params != NULL) {
        if ((params->metadataType[0] != IVIDEO_METADATAPLANE_NONE) ||
                (params->metadataType[1] != IVIDEO_METADATAPLANE_NONE) ||
                (params->metadataType[2] != IVIDEO_METADATAPLANE_NONE)) {
            /* We don't support metadata */
            return (VIDDEC3COPY_TI_EUNSUPPORTEDMETADATAPARAM);
        }

        if ((params->inputDataMode != IVIDEO_ENTIREFRAME) ||
                (params->outputDataMode != IVIDEO_ENTIREFRAME)) {
            /* We don't support subframe processing */
            return (VIDDEC3COPY_TI_EUNSUPPORTEDDATAMODE);
        }
    }

    /* Request memory for my object */
    memTab[0].size = sizeof(VIDDEC3COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== VIDDEC3COPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC3COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (VIDDEC3COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== VIDDEC3COPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDDEC3COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
        IALG_Handle parent, const IALG_Params *algParams)
{
    VIDDEC3COPY_TI_Obj *obj = (VIDDEC3COPY_TI_Obj *)handle;
    const IVIDDEC3_Params *params = (IVIDDEC3_Params *)algParams;
    Int retval = IALG_EOK;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDDEC3COPY_TI_PARAMS;
    }

    /* validate that we support the options supplied */
    if (params->displayBufsMode != IVIDDEC3_DISPLAYBUFS_EMBEDDED) {
        /* error, this implementation only supports embedded displaybufs */
        retval = IALG_EFAIL;
    }

    obj->forceChromaFormat = params->forceChromaFormat;

    return (retval);
}


/*
 *  ======== VIDDEC3COPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDDEC3COPY_TI_process(IVIDDEC3_Handle h, XDM2_BufDesc *inBufs,
    XDM2_BufDesc *outBufs, IVIDDEC3_InArgs *inArgs, IVIDDEC3_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDDEC3_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDDEC3_EFAIL);
    }

    /* currently this codec only supports standard, flat, "raw" memory */
    if (outBufs->descs[0].memType != XDM_MEMTYPE_RAW) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDDEC3_EFAIL);
    }

    numInBytes = inArgs->numBytes;

    /*
     * Sanity check that inBufs->descs[0].bufSize is really capable of holding
     * numInBytes bytes of data, and that outBufs->bufSizes[0]
     * can hold the 'encoded' data.
     */
    if ((inBufs->descs[0].bufSize.bytes < inArgs->numBytes) ||
            (outBufs->descs[0].bufSize.bytes < MINOUTBUFSIZE)){
        /* inBuf is smaller than provided data(!) or "too small" outBuf */
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDDEC3_EFAIL);
    }

    /* everything looks good, do the 'encode', set outArgs and return */
    memcpy(outBufs->descs[0].buf, inBufs->descs[0].buf, numInBytes);

    /* report _how_ we accessed the input buffer */
    inBufs->descs[0].accessMask = 0;
    XDM_SETACCESSMODE_READ(inBufs->descs[0].accessMask);

    /* outArgs->bytesConsumed reports the total number of bytes decoded */
    outArgs->bytesConsumed = numInBytes;

    /* Fill out the rest of the outArgs struct */
    outArgs->outputID[0] = inArgs->inputID;
    outArgs->outputID[1] = 0;  /* end of array - invalid ID */

    /* contrived here... indicate we have a 1 pixel high, very wide image */
    outArgs->decodedBufs.imageRegion.topLeft.x = 0;
    outArgs->decodedBufs.imageRegion.topLeft.y = 0;
    outArgs->decodedBufs.imageRegion.bottomRight.x = 0;
    outArgs->decodedBufs.imageRegion.bottomRight.y = numInBytes;
    outArgs->decodedBufs.activeFrameRegion.topLeft.x = 0;
    outArgs->decodedBufs.activeFrameRegion.topLeft.y = 0;
    outArgs->decodedBufs.activeFrameRegion.bottomRight.x = 0;
    outArgs->decodedBufs.activeFrameRegion.bottomRight.x = numInBytes;
    outArgs->decodedBufs.numPlanes = 1;         /* just one plane of data */
    outArgs->decodedBufs.dataLayout = 0;        /* TODO */

    outArgs->decodedBufs.planeDesc[0].buf = outBufs->descs[0].buf;
    outArgs->decodedBufs.planeDesc[0].bufSize.bytes =
            outBufs->descs[0].bufSize.bytes;

    /* initialize the accessMask, then indicate how we accessed it */
    outArgs->decodedBufs.planeDesc[0].accessMask = 0;
    XDM_SETACCESSMODE_WRITE(outArgs->decodedBufs.planeDesc[0].accessMask);

    /* no meta planes of data */
    outArgs->decodedBufs.numMetaPlanes = 0;
    outArgs->decodedBufs.metadataPlaneDesc[0].buf = NULL;  /* just to be safe */

    outArgs->decodedBufs.extendedError = 0;
    outArgs->decodedBufs.frameType = 0;             /* TODO */
    outArgs->decodedBufs.topFieldFirstFlag = XDAS_FALSE;  /* TODO */
    outArgs->decodedBufs.repeatFirstFieldFlag = XDAS_FALSE;  /* TODO */
    outArgs->decodedBufs.frameStatus = IVIDEO_FRAME_NOERROR;
    outArgs->decodedBufs.repeatFrame = 0;           /* TODO */
    outArgs->decodedBufs.contentType = IVIDEO_PROGRESSIVE;
    outArgs->decodedBufs.chromaFormat = XDM_CHROMAFORMAT_DEFAULT;

    /* Single display buf equivalent to the decoded buf above */
    outArgs->displayBufsMode = IVIDDEC3_DISPLAYBUFS_EMBEDDED;
    outArgs->displayBufs.bufDesc[0] = outArgs->decodedBufs;

    /*
     * Note, we only provide 1 'embedded' displaybuf.  Don't access
     * anything beyond displayBufs.bufDesc[0]!
     */

    outArgs->freeBufID[0] = inArgs->inputID;  /* release the only outBuf */
    outArgs->freeBufID[1] = 0; /* end of array - invalid ID */
    outArgs->outBufsInUseFlag = XDAS_FALSE;

    return (IVIDDEC3_EOK);
}


/*
 *  ======== VIDDEC3COPY_TI_control ========
 */
XDAS_Int32 VIDDEC3COPY_TI_control(IVIDDEC3_Handle handle, IVIDDEC3_Cmd id,
        IVIDDEC3_DynamicParams *dynParams, IVIDDEC3_Status *status)
{
    XDAS_Int32 retVal;
    VIDDEC3COPY_TI_Obj *obj = (VIDDEC3COPY_TI_Obj *)handle;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->size != sizeof(*status))) {
        return (IVIDDEC3_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;

            status->maxNumDisplayBufs = 1; /* todo  */
            status->maxOutArgsDisplayBufs = 1; /* 1 display buf in OutArgs */
            status->outputHeight = 0;  /* todo */
            status->outputWidth = 0;  /* todo */
            status->frameRate = 0;  /* todo */
            status->bitRate = 0;  /* todo */
            status->contentType = 0;  /* todo */
            status->sampleAspectRatioHeight = 0; /* todo */
            status->sampleAspectRatioWidth = 0;  /* todo */
            status->bitRange = 0;  /* todo */
            status->forceChromaFormat = obj->forceChromaFormat;
            status->operatingMode = 0; /* todo */
            status->frameOrder = 0; /* todo */
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
            status->bufInfo.minNumBufSets = 1; /* TODO */

            status->decDynamicParams.decodeHeader = 0; /* TODO */
            status->decDynamicParams.displayWidth = 0; /* TODO */
            status->decDynamicParams.frameSkipMode = 0; /* TODO */
            status->decDynamicParams.newFrameFlag = XDAS_FALSE; /* TODO */

            status->decDynamicParams.putDataFxn = FALSE; /* TODO */
            status->decDynamicParams.putDataHandle = 0; /* TODO */
            status->decDynamicParams.getDataFxn = FALSE; /* TODO */
            status->decDynamicParams.getDataHandle = 0; /* TODO */
            status->decDynamicParams.putBufferFxn = NULL; /* todo */
            status->decDynamicParams.putBufferHandle = 0; /* todo */

            retVal = IVIDDEC3_EOK;
            break;

        case XDM_SETPARAMS:
        case XDM_SETLATEACQUIREARG:
            retVal = IVIDDEC3_EOK;
            break;

        case XDM_SETDEFAULT:
            obj->forceChromaFormat = VIDDEC3COPY_TI_PARAMS.forceChromaFormat;

            retVal = IVIDDEC3_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IVIDDEC3_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize > strlen(VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IVIDDEC3_EOK;
            }
            else {
                retVal = IVIDDEC3_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IVIDDEC3_EFAIL;
            break;
    }

    return (retVal);
}
