/*
 * Copyright (c) 2006-2013, Texas Instruments Incorporated
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
 *  ======== videnc1_copy.c ========
 *  Video encoder "copy" algorithm.
 *
 *  This file contains an implementation of the IVIDENC1 interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/ividenc1.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(VIDENC1COPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(VIDENC1COPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(VIDENC1COPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(VIDENC1COPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(VIDENC1COPY_TI_alloc,   ".text:algAlloc")
#endif

#include "videnc1_copy_ti.h"
#include "videnc1_copy_ti_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &VIDENC1COPY_TI_IALG,   /* module ID */                         \
    NULL,                   /* activate */                          \
    VIDENC1COPY_TI_alloc,   /* alloc */                             \
    NULL,                   /* control (NULL => no control ops) */  \
    NULL,                   /* deactivate */                        \
    VIDENC1COPY_TI_free,    /* free */                              \
    VIDENC1COPY_TI_initObj, /* init */                              \
    NULL,                   /* moved */                             \
    NULL                    /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== VIDENC1COPY_TI_IVIDENCCOPY ========
 *  This structure defines TI's implementation of the IVIDENC1 interface
 *  for the VIDENC1COPY_TI module.
 */
IVIDENC1_Fxns VIDENC1COPY_TI_IVIDENC1COPY = {
    {IALGFXNS},
    VIDENC1COPY_TI_process,
    VIDENC1COPY_TI_control,
};

/*
 *  ======== VIDENC1COPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the VIDENC1COPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("VIDENC1COPY_TI_IALG .set VIDENC1COPY_TI_IVIDENC1COPY");

#else

/* Symbol has a single leading underscore */
asm("_VIDENC1COPY_TI_IALG .set _VIDENC1COPY_TI_IVIDENC1COPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns VIDENC1COPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IVIDENC1_Params VIDENC1COPY_TI_PARAMS = {
    sizeof(IVIDENC1_Params),
    0,                              /* encodingPreset - TODO */
    0,                              /* rateControlPreset - TODO */
    1024,                           /* maxHeight */
    1024,                           /* maxWidth */
    30000,                          /* maxFrameRate */
    10000000,                       /* maxBitRate */
    XDM_BYTE,                       /* dataEndianness */
    1,                              /* maxInterFrameInterval */
    XDM_CHROMAFORMAT_DEFAULT,       /* inputChromaFormat */
    IVIDEO_CONTENTTYPE_DEFAULT,     /* inputContentType */
    XDM_CHROMAFORMAT_DEFAULT        /* reconChromaFormat */
};

#ifdef USE_ECPY

/* Implementation of IRES interface functions & IRES_Fxns vtable */
#include <ti/xdais/ires.h>
#include <ti/sdo/fc/ecpy/ecpy.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>

#define NUM_LOGICAL_CH 1

/*
 *  ======== VIDENC1COPY_TI_deactivateAllRes ========
 */
static IRES_Status VIDENC1COPY_TI_deactivateAllRes(IALG_Handle handle)
{
    VIDENC1COPY_TI_Obj *alg = (VIDENC1COPY_TI_Obj *)handle;
    /* Deactivate all resources, this may mean saving the resource
       as the algorithm no longer owns it after this call. */
    return (IRES_OK);
}


/*
 *  ======== VIDENC1COPY_TI_activateAllRes ========
 */
static IRES_Status VIDENC1COPY_TI_activateAllRes(IALG_Handle handle)
{
    VIDENC1COPY_TI_Obj *alg = (VIDENC1COPY_TI_Obj *)handle;
    /* Activate all resources, this may mean initializing the resource
       as the algorithm truly owns it at this stage */
    return (IRES_OK);
}

/*
 *  ======== VIDENC1COPY_TI_activateRes ========
 *
 *  This function is only applicable for 'LATEACQUIRED' resources.
 */
static IRES_Status VIDENC1COPY_TI_activateRes(IALG_Handle handle,
        IRES_Handle res)
{
    return (IRES_OK);
}

/*
 *  ======== VIDENC1COPY_TI_deactivateRes ========
 *
 *  This function is only applicable for 'LATEACQUIRED' resources.
 */
static IRES_Status VIDENC1COPY_TI_deactivateRes(IALG_Handle handle,
        IRES_Handle res)
{
    return (IRES_OK);
}

/*
 *  ======== VIDENC1COPY_TI_deInitResources ========
 */
static IRES_Status VIDENC1COPY_TI_deInitResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc)
{
    VIDENC1COPY_TI_Obj *alg = (VIDENC1COPY_TI_Obj *)h;
    if (desc[0].handle == (IRES_Handle)alg->edmaHandle[0]) {

        ECPY_deleteHandle(alg->ecpyHandle[0]);

        alg->ecpyHandle[0] = NULL;
        alg->edmaHandle[0] = NULL;
    }
    else {
        return (IRES_ENOTFOUND);
    }
    return (IRES_OK);
}


/*
 *  ======== VIDENC1COPY_TI_reInitResources ========
 */
static IRES_Status VIDENC1COPY_TI_reInitResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs)
{
    VIDENC1COPY_TI_Obj *alg = (VIDENC1COPY_TI_Obj *)h;
    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;

    /*
     * This function implies that the resource holdings of the algorithms have
     * been changed.
     * Update them in the algorithm instance object.
     */
    alg->edmaHandle[0] = (IRES_EDMA3CHAN2_Handle)desc[0].handle;
    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;

    return (IRES_OK);
}


/*
 *  ======== VIDENC1COPY_TI_initResources ========
 */
static IRES_Status VIDENC1COPY_TI_initResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs)
{
    VIDENC1COPY_TI_Obj *alg = (VIDENC1COPY_TI_Obj *)h;

    /*
     * Resource manager has returned a resource handle. Save it in the
     * algorithm's instance object
     */
    alg->edmaHandle[0] = (IRES_EDMA3CHAN2_Handle)desc[0].handle;
    alg->ecpyHandle[0] =
            ECPY_createHandle((IRES_EDMA3CHAN2_Handle)desc[0].handle, h);

    /*
     * Resource Manager also provides yield functions and yield Args alongwith
     * the resource handle.
     */
    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;

    return (IRES_OK);

}


/*
 *  ======== VIDENC1COPY_TI_numResources ========
 */
static Int32 VIDENC1COPY_TI_numResources(IALG_Handle handle)
{
    return (NUM_LOGICAL_CH);
}

/*
 *  ======== VIDENC1COPY_TI_getResources ========
 */

static IRES_Status VIDENC1COPY_TI_getResources(ALG_Handle h,
        IRES_ResourceDescriptor *desc)
{
    VIDENC1COPY_TI_Obj *alg = (VIDENC1COPY_TI_Obj *)h;
    desc[0].resourceName = IRES_EDMA3CHAN_PROTOCOLNAME;
    desc[0].revision = &(alg->edma3chanRev);
    desc[0].protocolArgs = (IRES_ProtocolArgs *)&(alg->edmaArgs);
    (alg->edmaArgs).size = sizeof(IRES_EDMA3CHAN_ProtocolArgs);
    (alg->edmaArgs).numPaRams = 1;
    (alg->edmaArgs).paRamIndex = IRES_EDMA3CHAN_PARAM_ANY;
    (alg->edmaArgs).tccIndex = IRES_EDMA3CHAN_TCC_ANY;
    (alg->edmaArgs).numTccs = 1;
    (alg->edmaArgs).qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
    (alg->edmaArgs).edmaChan = IRES_EDMA3CHAN_EDMACHAN_ANY;
    desc[0].handle = (IRES_Handle)alg->edmaHandle[0];

    return (IRES_OK);
}


IRES_Fxns VIDENC1COPY_TI_IRES = {
    &VIDENC1COPY_TI_IALG,
    VIDENC1COPY_TI_getResources,
    VIDENC1COPY_TI_numResources,
    VIDENC1COPY_TI_initResources,
    VIDENC1COPY_TI_reInitResources,
    VIDENC1COPY_TI_deInitResources,
    VIDENC1COPY_TI_activateRes,
    VIDENC1COPY_TI_activateAllRes,
    VIDENC1COPY_TI_deactivateRes,
    VIDENC1COPY_TI_deactivateAllRes

};

#endif


/*
 *  ======== VIDENC1COPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDENC1COPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(VIDENC1COPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== VIDENC1COPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDENC1COPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (VIDENC1COPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== VIDENC1COPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int VIDENC1COPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
        IALG_Handle parent, const IALG_Params *algParams)
{
    const IVIDENC1_Params *params = (IVIDENC1_Params *)algParams;
#ifdef USE_ECPY
    VIDENC1COPY_TI_Obj *obj = (VIDENC1COPY_TI_Obj *)handle;

    /*
     * Save the context save restore functions in the algorithm instance
     * This can be done any time after the algorithm instance is created.
     * Not necessary to do it here
     */
    (obj->yieldContext).contextSave = NULL;
    (obj->yieldContext).contextRestore = NULL;
    (obj->yieldContext).contextArgs = NULL;

    (obj->edma3chanRev).Major = 2;
    (obj->edma3chanRev).Source = 0;
    (obj->edma3chanRev).Radius = 0;
#endif

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &VIDENC1COPY_TI_PARAMS;
    }

    return (IALG_EOK);
}


/*
 *  ======== VIDENC1COPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDENC1COPY_TI_process(IVIDENC1_Handle h, IVIDEO1_BufDescIn *inBufs,
    XDM_BufDesc *outBufs, IVIDENC1_InArgs *inArgs, IVIDENC1_OutArgs *outArgs)
{
    XDAS_Int32 numInBytes;

#ifdef USE_ECPY
    const Uint32 maxTransferChunkSize       = 0xffff;
    Uint32       thisTransferChunkSize      = 0x0;
    Uint32       remainingTransferChunkSize;
    Uint32       thisTransferSrcAddr, thisTransferDstAddr;

    ECPY_Params params;
    VIDENC1COPY_TI_Obj *videncObj = (VIDENC1COPY_TI_Obj *)h;
#endif
    /*
     * Validate arguments - this codec supports "base" XDM and an extended
     * inArgs.
     */
    if (((inArgs->size != sizeof(*inArgs)) &&
            (inArgs->size != sizeof(IVIDENC1CPY_InArgs))) ||
            (outArgs->size != sizeof(*outArgs))) {

        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDENC1_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDENC1_EFAIL);
    }

    /* validate inputID */
    if (inArgs->inputID == 0) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IVIDENC1_EFAIL);
    }

    /* there's an available in and out buffer, how many samples? */
    numInBytes = inBufs->bufDesc[0].bufSize < outBufs->bufSizes[0] ?
        inBufs->bufDesc[0].bufSize : outBufs->bufSizes[0];

    /* and honor the extended maxBytes if it was provided */
    if (inArgs->size == sizeof(IVIDENC1CPY_InArgs)) {
        if (numInBytes > ((IVIDENC1CPY_InArgs *)inArgs)->maxBytes) {
            numInBytes = ((IVIDENC1CPY_InArgs *)inArgs)->maxBytes;
        }
    }
#ifdef USE_ECPY
    /*
     * Activate Channel scratch DMA channels.
     */
    ECPY_activate(videncObj->dmaHandle1D1D8B);

    thisTransferSrcAddr        = (Uint32)inBufs->bufDesc[0].buf;
    thisTransferDstAddr        = (Uint32)outBufs->bufs[0];
    remainingTransferChunkSize = numInBytes;

    while (remainingTransferChunkSize > 0) {

        if (remainingTransferChunkSize > maxTransferChunkSize) {
           thisTransferChunkSize = maxTransferChunkSize;
        }
        else {
           thisTransferChunkSize = remainingTransferChunkSize;
        }

        /* Configure the logical channel */
        params.transferType = ECPY_1D1D;
        params.srcAddr      = (void *)thisTransferSrcAddr;
        params.dstAddr      = (void *)thisTransferDstAddr;
        params.elementSize  = thisTransferChunkSize;
        params.numElements  = 1;
        params.numFrames    = 1;

        remainingTransferChunkSize -= thisTransferChunkSize;
        thisTransferSrcAddr += thisTransferChunkSize;
        thisTransferDstAddr += thisTransferChunkSize;

        /* Configure logical dma channel */
        ECPY_configure(videncObj->dmaHandle1D1D8B, &params, 1);

        /* Use DMA to copy data */
        ECPY_start(videncObj->dmaHandle1D1D8B);

        /* wait for transfer to finish  */
        ECPY_wait(videncObj->dmaHandle1D1D8B);
    }

    /*
     * Deactivate Channel scratch DMA channels.
     */
    ECPY_deactivate(videncObj->dmaHandle1D1D8B);

    /*
     * Because we used DMA, the algo processor didn't access either of the
     * 2 data buffers.
     */
    XDM_CLEARACCESSMODE_READ(inBufs->bufDesc[0].accessMask);
    XDM_CLEARACCESSMODE_WRITE(inBufs->bufDesc[0].accessMask);

    XDM_CLEARACCESSMODE_READ(outArgs->encodedBuf.accessMask);
    XDM_CLEARACCESSMODE_WRITE(outArgs->encodedBuf.accessMask);

#else
    /* everything looks good, do the 'encode', set outArgs and return */
    memcpy(outBufs->bufs[0], inBufs->bufDesc[0].buf, numInBytes);

    /* memcpy read from inBuf and wrote to encodedBuf (in our case, outBuf) */
    XDM_CLEARACCESSMODE_WRITE(inBufs->bufDesc[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->bufDesc[0].accessMask);

    XDM_CLEARACCESSMODE_READ(outArgs->encodedBuf.accessMask);
    XDM_SETACCESSMODE_WRITE(outArgs->encodedBuf.accessMask);
#endif

    /* outArgs->bytesGenerated reports the total number of bytes encoded */
    outArgs->bytesGenerated = numInBytes;

    /* report that the encoded data is in outArgs->encodedBuf */
    outArgs->encodedBuf.buf = outBufs->bufs[0];
    outArgs->encodedBuf.bufSize = outBufs->bufSizes[0];

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;
    outArgs->encodedFrameType = 0;     /* TODO */
    outArgs->inputFrameSkip = IVIDEO_FRAME_ENCODED;
    outArgs->outputID = inArgs->inputID;

    /* TODO - add support for reconBufs */
    outArgs->reconBufs.numBufs = 0;

    return (IVIDENC1_EOK);
}


/*
 *  ======== VIDENC1COPY_TI_control ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 VIDENC1COPY_TI_control(IVIDENC1_Handle handle, IVIDENC1_Cmd id,
    IVIDENC1_DynamicParams *params, IVIDENC1_Status *status)
{
    XDAS_Int32 retVal;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((params->size != sizeof(*params)) ||
            (status->size != sizeof(*status))) {
        return (IVIDENC1_EUNSUPPORTED);
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

            retVal = IVIDENC1_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IVIDENC1_EOK;
            break;

        case XDM_SETDEFAULT:
            retVal = IVIDENC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IVIDENC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize > strlen(VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IVIDENC1_EOK;
            }
            else {
                retVal = IVIDENC1_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IVIDENC1_EUNSUPPORTED;
            break;
    }

    return (retVal);
}
