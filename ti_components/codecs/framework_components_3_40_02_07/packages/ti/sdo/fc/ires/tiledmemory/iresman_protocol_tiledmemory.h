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
 *  @file       ti/sdo/fc/ires/tiledmemory/iresman_protocol_tiledmemory.h
 *
 *  @brief      IRESMAN PROTOCOL TILEDMEMORY Interface Definitions -
 *              Interface of the protocol implementation to the device
 *              specific resman, for the construction/deletion of
 *              TILEDMEMORY resource handles
 */

#ifndef IRESMAN_PROTOCOL_TILEDMEMORY_
#define IRESMAN_PROTOCOL_TILEDMEMORY_

/** @ingroup    ti_sdo_fc_ires_tiledmemory_IRESMAN_TILEDMEMORY */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sdo/fc/ires/iresman_protocol.h>
#include <ti/sdo/fc/ires/tiledmemory/ires_tiledmemory.h>

/*
 * @brief           Arguments that are passed from the IRES Resource manager
 *                  to intialize the handle
 */
typedef struct IRESMAN_TILEDMEMORY_ConstructHandleArgs {

    IRESMAN_ConstructArgs args;

    Void *memBaseAddr;                 /* Process specific virtual address */
    Void *tilerBaseAddr;               /* Base address of tiler hardware */
    Void * systemSpaceBaseAddress;     /* tiler space address of alloc memory */
    IRES_TILEDMEMORY_AccessUnit unit;   /* unit that was finally allocated  */

    Void *info;                         /* Info  */

    Bool persistent;

    Int sizeTiledMemory;         /* size of allocated memory for the request */
    Int isTiledMemory;           /* TRUE if allocation is done
                                  *   in Physical TILED Memory */


} IRESMAN_TILEDMEMORY_ConstructHandleArgs;


/*
 * Interface to expose to the resource manager to be able to construct handles
 */
extern IRESMAN_ConstructFxns IRESMAN_TILEDMEMORY_CONSTRUCTFXNS;

/*@}*/ /** @ingroup    DSPIRESPROTTILEDMEMORY */


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  /* IRESMAN_PROTOCOL_TILEDMEMORY_ */
