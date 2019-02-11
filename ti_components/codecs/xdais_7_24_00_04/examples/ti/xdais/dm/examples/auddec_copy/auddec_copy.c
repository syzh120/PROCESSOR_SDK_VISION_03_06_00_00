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
 *  ======== auddec_copy.c ========
 *  Audio decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IAUDDEC interface
 *  defined by XDM.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/iauddec.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(AUDDECCOPY_TI_control, ".text:algControl")
#pragma CODE_SECTION(AUDDECCOPY_TI_process, ".text:algProcess")
#pragma CODE_SECTION(AUDDECCOPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(AUDDECCOPY_TI_free,    ".text:algFree")
#pragma CODE_SECTION(AUDDECCOPY_TI_alloc,   ".text:algAlloc")
#endif

#include "auddec_copy_ti.h"
#include "auddec_copy_ti_priv.h"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define IALGFXNS  \
    &AUDDECCOPY_TI_IALG,/* module ID */                         \
    NULL,               /* activate */                          \
    AUDDECCOPY_TI_alloc,/* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    AUDDECCOPY_TI_free, /* free */                              \
    AUDDECCOPY_TI_initObj, /* init */                           \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== AUDDECCOPY_TI_AUDDECCOPY ========
 *  This structure defines TI's implementation of the IAUDDEC interface
 *  for the AUDDECCOPY_TI module.
 */
IAUDDEC_Fxns AUDDECCOPY_TI_IAUDDECCOPY = {    /* module_vendor_interface */
    {IALGFXNS},
    AUDDECCOPY_TI_process,
    AUDDECCOPY_TI_control,
};

/*
 *  ======== AUDDECCOPY_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the AUDDECCOPY_TI module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("AUDDECCOPY_TI_IALG .set AUDDECCOPY_TI_IAUDDECCOPY");

#else

/* Symbol has a single leading underscore */
asm("_AUDDECCOPY_TI_IALG .set _AUDDECCOPY_TI_IAUDDECCOPY");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns AUDDECCOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

/*
 *  ======== AUDDECCOPY_TI_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct our object.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int AUDDECCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(AUDDECCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    /* Return the number of records in the memTab */
    return (1);
}


/*
 *  ======== AUDDECCOPY_TI_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int AUDDECCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (AUDDECCOPY_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== AUDDECCOPY_TI_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int AUDDECCOPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    return (IALG_EOK);
}


/*
 *  ======== AUDDECCOPY_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 AUDDECCOPY_TI_process(IAUDDEC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IAUDDEC_InArgs *inArgs, IAUDDEC_OutArgs *outArgs)
{
    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IAUDDEC_EFAIL);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (IAUDDEC_EFAIL);
    }

    /*
     * The number of bytes we can consume is the lesser of the specified
     * number of bytes to decode (inArgs->numBytes) and the size of the
     * buffer that will contain the output (outBufs->bufSizes[0]).
     */
    outArgs->bytesConsumed = (inArgs->numBytes <= outBufs->bufSizes[0]) ?
        inArgs->numBytes : outBufs->bufSizes[0];

    /* process the data: read input, produce output */
    memcpy(outBufs->bufs[0], inBufs->bufs[0], outArgs->bytesConsumed);

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;

    return (IAUDDEC_EOK);
}


/*
 *  ======== AUDDECCOPY_TI_control ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 AUDDECCOPY_TI_control(IAUDDEC_Handle handle, IAUDDEC_Cmd id,
    IAUDDEC_DynamicParams *dynParams, IAUDDEC_Status *status)
{
    XDAS_Int32 retVal;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->size != sizeof(*status))) {
        return (IAUDDEC_EFAIL);
    }

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;
            status->bitRate = 0;  /* TODO */
            status->sampleRate = 0;  /* TODO */
            status->numChannels = 0;  /* TODO */
            status->numLFEChannels = 0;  /* TODO */
            status->outputFormat = 0;  /* TODO */
            status->autoPosition = 0;  /* TODO */
            status->fastFwdLen = 0;  /* TODO */
            status->frameLen = 0;  /* TODO */
            status->outputBitsPerSample = 0;  /* TODO */
            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IAUDDEC_EOK;

            break;

        case XDM_SETPARAMS:
        case XDM_SETDEFAULT:
            /* Not really supported, TBD.  But, we return success anyway... */
            retVal = IAUDDEC_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IAUDDEC_EOK;
            break;

        default:
            /* unsupported cmd */
            retVal = IAUDDEC_EFAIL;

            break;
    }

    return (retVal);
}
