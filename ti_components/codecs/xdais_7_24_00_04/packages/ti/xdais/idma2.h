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
 *  @file idma2.h
 *
 *  @brief Declaration of the IDMA2 interface. (Deprecated)
 *
 *  @idmaDeprecated
 */

#ifndef IDMA2_
#define IDMA2_

#include "ialg.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== IDMA2_Handle ========
 *  Handle to "logical" DMA channel.
 */
typedef struct IDMA2_Obj *IDMA2_Handle;

#if defined(_54_) || defined(_55_)
typedef Void (*IDMA2_AdrPtr)();
#define IDMA2_ADRPTR(addr) ((IDMA2_AdrPtr)((LgUns)addr<<1))
#else
typedef Void * IDMA2_AdrPtr;
#endif

/*
 *  ======== IDMA2_ElementSize ========
 *  8, 16 or 32-bit aligned transfer.
 */
typedef enum IDMA2_ElementSize {
    IDMA2_ELEM8,         /* 8-bit data element */
    IDMA2_ELEM16,        /* 16-bit data element */
    IDMA2_ELEM32         /* 32-bit data element */
} IDMA2_ElementSize;

/*
 *  ======== IDMA2_TransferType ========
 *  Type of the DMA transfer.
 */
typedef enum IDMA2_TransferType {
    IDMA2_1D1D,          /* 1-dimensional to 1-dimensional transfer */
    IDMA2_1D2D,          /* 1-dimensional to 2-dimensional transfer */
    IDMA2_2D1D,          /* 2-dimensional to 1-dimensional transfer */
    IDMA2_2D2D           /* 2-dimensional to 2-dimensional transfer */
} IDMA2_TransferType;

/*
 *  ======== IDMA2_Params ========
 *  DMA transfer specific parameters. Defines the configuration of a
 *  logical channel.
 */
typedef struct IDMA2_Params {
    IDMA2_TransferType xType;           /* 1D1D, 1D2D, 2D1D or 2D2D */
    IDMA2_ElementSize  elemSize;        /* Element transfer size */
    Uns    numFrames;       /* Num of frames for 2D transfers */
    Int    srcElementIndex; /* In 8-bit bytes  */
    Int    dstElementIndex; /* In 8-bit bytes */
    Int    srcFrameIndex;   /* Jump in 8-bit bytes for 2D transfers */
    Int    dstFrameIndex;   /* Jump in 8-bit bytes for 2D transfers */
} IDMA2_Params;

/*
 *  ======== IDMA2_ChannelRec ========
 *  DMA record used to describe the logical channels.
 */
typedef struct IDMA2_ChannelRec {
    IDMA2_Handle  handle;       /* Handle to logical DMA channel */
    Int           queueId;      /* Selects the serialization queue */
} IDMA2_ChannelRec;

/*
 *  ======== IDMA2_Fxns ========
 *  These fxns are used to query/grant the DMA resources requested by
 *  the algorithm at initialization time, and to change these resources
 *  at runtime. All these fxns are implemented by the algorithm, and
 *  called by the client of the algorithm.
 *
 *    implementationId    - unique pointer that identifies the module
 *                          implementing this interface.
 *    dmaChangeChannels() - apps call this whenever the logical channels
 *                          are moved at runtime.
 *    dmaGetChannelCnt()  - apps call this to query algorithm about max
 *                          number of logical dma channel requested.
 *    dmaGetChannels()    - apps call this to query algorithm about its
 *                          dma channel requests at init time, or to get
 *                          the current channel holdings.
 *    dmaInit()           - apps call this to grant dma handle(s) to the
 *                          algorithm at initialization. Algorithm initializes
 *                          the instance object.
 */
typedef struct IDMA2_Fxns {
    Void        *implementationId;
    Void        (*dmaChangeChannels)(IALG_Handle, IDMA2_ChannelRec *);
    Int         (*dmaGetChannelCnt)(Void);
    Int         (*dmaGetChannels)(IALG_Handle, IDMA2_ChannelRec *);
    Int         (*dmaInit)(IALG_Handle, IDMA2_ChannelRec *);
} IDMA2_Fxns;

#ifdef __cplusplus
}
#endif

#endif  /* IDMA2_ */

