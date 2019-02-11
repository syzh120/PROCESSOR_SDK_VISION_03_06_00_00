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
 *  ======== g711enc_sun_ialg.c ========
 *  Implementation of the G711ENC_SUN.h interface; SUN's implementation
 *  of the ISPHENC1 interface.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/isphenc1.h>
#include <ti/xdais/dm/ispeech1_pcm.h>

#ifdef __TI_COMPILER_VERSION__
/* XDAIS Rule 13 - this #pragma should only apply to TI codegen */
#pragma CODE_SECTION(G711ENC_SUN_control, ".text:algControl")
#pragma CODE_SECTION(G711ENC_SUN_encode,  ".text:algProcess")
#pragma CODE_SECTION(G711ENC_SUN_initObj, ".text:algInit")
#pragma CODE_SECTION(G711ENC_SUN_free,    ".text:algFree")
#pragma CODE_SECTION(G711ENC_SUN_alloc,   ".text:algAlloc")
#endif

#include "g711enc_sun.h"
#include "g711_sun_internal.h"
#include "g711enc_sun_priv.h"

/* TODO, need to autogenerate this */
#define VERSIONSTRING "1.00.00.00"

typedef unsigned char (*EncodeFxn)(short);

/*
 *  ======== G711ENC_SUN_Obj ========
 */
typedef struct G711ENC_SUN_Obj {
    IALG_Obj alg;              /* MUST be first field of all XDAIS inst objs */
    EncodeFxn fxn;             /* dynamically set to u-law or a-law */
    Int frameLen;              /* frame length in samples. */
    XDAS_Int16 compandingLaw;  /* companding setting. */
} G711ENC_SUN_Obj;

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    sizeof(short)
#define MINOUTBUFSIZE   sizeof(char)


#define IALGFXNS \
    &G711ENC_SUN_IALG,  /* module ID */                         \
    NULL,               /* activate */                          \
    G711ENC_SUN_alloc,  /* algAlloc */                          \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    G711ENC_SUN_free,   /* free */                              \
    G711ENC_SUN_initObj,/* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc */

/*
 *  ======== G711ENC_SUN_IG711ENC ========
 *  This structure defines SUN's implementation of the ISPHENC1 interface
 *  for the G711ENC_SUN module.
 */
ISPHENC1_Fxns G711ENC_SUN_IG711ENC = {  /* module_vendor_interface */
    {IALGFXNS},
    G711ENC_SUN_encode,
    G711ENC_SUN_control,
};

/*
 *  ======== G711ENC_SUN_IALG ========
 *  This structure defines SUN's implementation of the IALG interface
 *  for the G711ENC_SUN module.
 */
#ifdef __TI_COMPILER_VERSION__
/* satisfy XDAIS symbol requirement without any overhead */
#if defined(__TI_ELFABI__) || defined(__TI_EABI_SUPPORT__)

/* Symbol doesn't have any leading underscores */
asm("G711ENC_SUN_IALG .set G711ENC_SUN_IG711ENC");

#else

/* Symbol has a single leading underscore */
asm("_G711ENC_SUN_IALG .set _G711ENC_SUN_IG711ENC");

#endif
#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run using non-TI toolchains at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns G711ENC_SUN_IALG = {  /* module_vendor_interface */
    IALGFXNS
};

#endif

ISPHENC1_Params G711ENC_SUN_PARAMS = {
    sizeof(ISPHENC1_Params),
    MININBUFSIZE,               /* frameSize */
    ISPEECH1_PCM_COMPAND_ALAW,  /* a-law companding */
    0,                          /* packingType is a don't care for PCM */
    0,                          /* vadSelection is a don't care for PCM */
    0,                          /* codecSelection is a don't care for PCM */
    0,                          /* bitRate is a don't care for PCM */
    0,                          /* reserved */
    NULL                        /* tablesPtr isn't supported */
};

/*
 *  ======== G711ENC_SUN_alloc ========
 *  Return a table of memory descriptors that describe the memory needed
 *  to construct a G711ENC_SUN_Obj structure.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int G711ENC_SUN_alloc(const IALG_Params *g711Params, IALG_Fxns **pf,
    IALG_MemRec memTab[])
{
    const ISPHENC1_Params *params = (ISPHENC1_Params *)g711Params;

    if ((params != NULL) && (params->tablesPtr != NULL)) {
        /*
         * We don't support tablesPtr.  Return a unique, clear error to the
         * so they know exactly why their create failed.
         */
        return (G711ENC_SUN_EUNSUPPORTEDTABLESPTRPARAM);
    }

    /* Request memory for G711 object */
    memTab[0].size = sizeof(G711ENC_SUN_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== G711ENC_SUN_free ========
 *  Return a table of memory pointers that should be freed.  Note
 *  that this should include *all* memory requested in the
 *  G711ENC_SUN_alloc operation above.
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int G711ENC_SUN_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (G711ENC_SUN_alloc(NULL, NULL, memTab));
}


/*
 *  ======== G711ENC_SUN_initObj ========
 *  Initialize the memory allocated on our behalf (including our object).
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int G711ENC_SUN_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    G711ENC_SUN_Obj *g711Enc = (Void *)handle;
    const ISPHENC1_Params *params = (ISPHENC1_Params *)algParams;
    Int status = IALG_EOK;

    /*
     * In lieu of XDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &G711ENC_SUN_PARAMS;
    }

    /*
     * Note that we already checked that params->tablesPtr != NULL in
     * our algAlloc() fxn, so we don't need to check again here.  Rather,
     * we could assert that (params->tablesPtr == NULL).
     */

    switch (params->compandingLaw) {
        case ISPEECH1_PCM_COMPAND_ALAW:
            g711Enc->fxn = G711_SUN_linear2alaw;
            g711Enc->compandingLaw = ISPEECH1_PCM_COMPAND_ALAW;
            break;

        case ISPEECH1_PCM_COMPAND_ULAW:
            g711Enc->fxn = G711_SUN_linear2ulaw;
            g711Enc->compandingLaw = ISPEECH1_PCM_COMPAND_ULAW;
            break;

        default:
            status = IALG_EFAIL;
            break;
    }

    g711Enc->frameLen = params->frameSize / sizeof(short);

    /* the rest of the input params are don't-care's */

    return (status);
}


/*
 *  ======== G711ENC_SUN_encode ========
 *
 *  G711ENC_SUN_encode - implements ISPHENC1::process() function.
 */
XDAS_Int32 G711ENC_SUN_encode(ISPHENC1_Handle handle,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    ISPHENC1_InArgs *inArgs, ISPHENC1_OutArgs *outArgs)
{
    G711ENC_SUN_Obj *g711Enc = (Void *)handle;
    Int i;

    short *in          = (short *)inBuf->buf;
    unsigned char *out = (unsigned char *)outBuf->buf;

    Int frameLen = inBuf->bufSize / sizeof(short);

    /* validate arguments - this codec only supports "base" XDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        XDM_SETUNSUPPORTEDPARAM(outArgs->extendedError);

        return (ISPHENC1_EUNSUPPORTED);
    }

    /* validate arguments - outBuf needs to be big enough to hold output */
    if (outBuf->bufSize < (frameLen * sizeof(char))) {
        XDM_SETINSUFFICIENTDATA(outArgs->extendedError);

        return (ISPHENC1_EFAIL);
    }

    /* process the data: read input, produce output */
    for (i = 0; i < frameLen; i++) {
        *out++ = g711Enc->fxn(*in++);
    }

    /* report how large, in 8-bit bytes, the encoded outBuf buffer is */
    outBuf->bufSize = frameLen;

    /* report _how_ we accessed the 2 data buffers */
    XDM_CLEARACCESSMODE_WRITE(inBuf->accessMask);
    XDM_SETACCESSMODE_READ(inBuf->accessMask);

    XDM_CLEARACCESSMODE_READ(outBuf->accessMask);
    XDM_SETACCESSMODE_WRITE(outBuf->accessMask);

    /* Fill out the rest of the outArgs struct */
    outArgs->frameType = ISPHENC1_FTYPE_SPEECH;
    outArgs->extendedError = 0;

    return (ISPHENC1_EOK);
}


/*
 *  ======== G711ENC_SUN_control ========
 */
XDAS_Int32 G711ENC_SUN_control(ISPHENC1_Handle handle, ISPHENC1_Cmd id,
    ISPHENC1_DynamicParams *dynParams, ISPHENC1_Status *status)
{
    XDAS_Int32 retVal;
    G711ENC_SUN_Obj *obj = (G711ENC_SUN_Obj *)handle;

    /* validate arguments - this codec only supports "base" XDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
            (status->size != sizeof(*status))) {
        XDM_SETUNSUPPORTEDPARAM(status->extendedError);

        return (ISPHENC1_EUNSUPPORTED);
    }

    /* Think positive... */
    status->extendedError = 0;

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->frameSize = obj->frameLen;
            status->compandingLaw = obj->compandingLaw;

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = ISPHENC1_EOK;

            break;

        case XDM_SETPARAMS:
            obj->frameLen = dynParams->frameSize / sizeof(short);

            /* the rest are don't cares */

            retVal = ISPHENC1_EOK;
            break;

        case XDM_SETDEFAULT:
            obj->fxn = G711_SUN_linear2alaw;
            obj->compandingLaw = ISPEECH1_PCM_COMPAND_ALAW;
            obj->frameLen = G711ENC_SUN_PARAMS.frameSize / sizeof(short);

            retVal = ISPHENC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = ISPHENC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize > strlen(VERSIONSTRING))) {
                strncpy((char *)status->data.buf, VERSIONSTRING,
                        strlen(VERSIONSTRING) + 1);

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = ISPHENC1_EOK;
            }
            else {
                retVal = ISPHENC1_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = ISPHENC1_EFAIL;

            break;
    }

    return (retVal);
}
