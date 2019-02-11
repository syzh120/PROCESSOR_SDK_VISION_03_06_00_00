/*
 * Copyright (c) 2012, Texas Instruments Incorporated
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
/**
 *  @file       ti/sdo/fc/ires/edma3chan/iresman_protocol_edma3Chan.h
 *
 *  @brief      IRESMAN PROTOCOL EDMA3CHAN Interface Definitions -
 *              Interface of the protocol implementation to the device
 *              specific resman, for the construction/deletion of
 *              EDMA3CHAN resource handles
 */

#ifndef IRESMAN_PROTOCOL_EDMA3CHAN_
#define IRESMAN_PROTOCOL_EDMA3CHAN_

/** @ingroup    ti_sdo_fc_ires_edma3Chan_IRESMAN_EDMA3CHAN */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sdo/fc/ires/iresman_protocol.h>

#define IRESMAN_PROTOCOL_EDMA3CHAN_MAX_MEMRECS  1
/*
 * @brief           Arguments that are passed from the IRES Resource manager
 *                  to intialize the handle
 */
typedef struct IRESMAN_EDMA3CHAN_ConstructHandleArgs {
    short edma3Chan;                            /*
                                                 * EDMA channel allocated.
                                                 * May be NONE if no EDMA
                                                 * channel was requested.
                                                 */

    short qdmaChan;                             /*
                                                 * QDMA channel allocated.
                                                 * May be NONE if no QDMA
                                                 * channel was requested.
                                                 */
    short numTccs;                              /* Number of Tccs requested */
    short numPaRams;                            /* Number of params allocated */
    short * tccIndex;                           /*
                                                 * Actual indices of tcc(s)
                                                 * allocated for this handle
                                                 * by the EDMA3 RM
                                                 */
    short * paRamIndex;                         /*
                                                 * Actual indices of params
                                                 * allocated for this handle
                                                 * by the EDMA3 RM
                                                 */
    int persistent;                             /*
                                                 * Resource property,
                                                 * persistent or non-persistent
                                                 */
    unsigned int edma3CCBaseAddress;            /*
                                                 * Base address of the EDMA3 CC
                                                 */
} IRESMAN_EDMA3CHAN_ConstructHandleArgs;


/*
 * Interface to expose to the resource manager to be able to construct handles
 */
extern IRESMAN_ConstructFxns IRESMAN_EDMA3CHAN_CONSTRUCTFXNS;

/*@}*/ /** @ingroup    DSPIRESPROTEDMA3CHAN */


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  /* IRESMAN_PROTOCOL_EDMA3CHAN_ */
