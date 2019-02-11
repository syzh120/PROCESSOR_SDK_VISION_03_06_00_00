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
 *  @file       ti/sdo/fc/ires/iresman.h
 *
 *  @brief      Device specific Resource Manager Interface Definitions
 *              IRESMAN - Interface that needs to be implemented
 *              and registered with the generic RMAN Resource Registry that
 *              are called to manage corresponding IRES resources
 */

/**
 *  @defgroup   ti_sdo_fc_ires_IRESMAN  Resource manager interface
 *
 *              The IRESMAN interface needs to be implemented and registered
 *              with the generic RMAN Resource Registry and is called by the
 *              Framework resource manager (RMAN) to manage corresponding
 *              IRES resources
 */

#ifndef ti_sdo_fc_ires_IRESMAN_
#define ti_sdo_fc_ires_IRESMAN_

/** @ingroup    ti_sdo_fc_ires_IRESMAN */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ires_common.h>
#include <ti/xdais/ires.h>

/**
 *  @brief      Memory allocation function for all of ResMan and other
 *              IRES protocol's memory requirements
 */
typedef Bool (IRESMAN_PersistentAllocFxn)(IALG_MemRec *memTab, Int numRecs);

/**
 *  @brief      Memory free functions for all of ResMan and other IRES
 *              protocol's memory requirements
 */
typedef Void (IRESMAN_PersistentFreeFxn)(IALG_MemRec *memTab, Int numRecs);


/**
 * @brief       Configuration Parameters required by the Resource Manager
 *              implementation. These can be extended by individual resource
 *              managers if required.
 */
typedef struct IRESMAN_Params {
    Int32 size;         /**< Size of this structure */

    /**
     *  @brief              Function to allocate memory required by the resource
     *                      manager implementation and the protocol
     */
    IRESMAN_PersistentAllocFxn * allocFxn;

    /**
     *  @brief              Function to free memory released by the resource
     *                      manager implementation and the protocol
     */
    IRESMAN_PersistentFreeFxn * freeFxn;

} IRESMAN_Params;

typedef struct IRESMAN_Fxns {

    /**
     *  @brief              Function to query the name of the protocol
     */
    String (*getProtocolName)();

    /**
     *  @brief              Function to query the revision of hte protocol
     *  @retval             Pointer to the protocol revision structure
     */
    IRES_ProtocolRevision * (* getProtocolRevision)();

    /**
     *  @brief              Function to create and initialize the device
     *                      specific resource manager implementation
     *  @param[in]          initArgs            Initialization arguments maybe
     *                                          interpreted by device specific
     *                                          implementation
     *  @retval             IRESMAN_EOK         Success
     *                      IRESMAN_EEXISTS     RESMAN already initialized
     *                      IRESMAN_EERROR      RESMAN could not be initialized
     *
     */
    IRES_Status (* init)(IRESMAN_Params * initArgs);

    /**
     *  @brief              Function called when RESMAN is no longer needed.
     *                      Use it to free memory allocated etc
     *  @retval             IRESMAN_EOK         Success
     *                      IRESMAN_ENOINIT     RESMAN not initialized
     *                      IRESMAN_EERROR      RESMAN could not be reset
     */
    IRES_Status (* exit)();

    /**
     *  @brief              Function that returns the IRES_Handle to resource
     *                      requested using the IRES_ProtocolArgs
     *  @param[in]          algHandle           Handle of the algorithm that
     *                                          is requesting the resources
     *  @param[in]          resDesc             Arguments to be interpreted by
     *                                          IRES_Manager implementation to
     *                                          determine actual physical
     *                                          resources to obtain
     *  @param[in]          scratchGroupId      Scratch Group Id where resources
     *                                          should be allocated
     *  @param[out]         status              IRESMAN_EOK         Success
     *                                          IRESMAN_ENORESOURCE Resource
     *                                                              unavailable
     *                                          IRESMAN_EERROR      Error
     *                                                              obtaining
     *                                                              handles
     */
    IRES_Handle (* getHandle)(IALG_Handle algHandle,
            IRES_ResourceDescriptor * resDesc, Int scratchGroupId,
            IRES_Status * status);

    /**
     *  @brief              Frees handles back to the resource pool
     *  @param[in]          algHandle           Handle of the algorithm that
     *                                          is releasing the resources
     *  @param[in]          resourceHandle      Handle that is to be released
     *  @param[in]          resDesc             Arguments that help determine
     *                                          which resources to free
     *  @retval             IRESMAN_EOK         Success
     *                      IRESMAN_EERROR      Handle could not be freed
     */
    IRES_Status (* freeHandle)(IALG_Handle algHandle,
            IRES_Handle resourceHandle, IRES_ResourceDescriptor * resDesc,
            Int scratchGroupId);

    /* Two new optional APIs */
    Void (* activateResource)(IALG_Handle algHandle, IRES_Fxns * resFxns);

    Void (* deactivateResource)(IALG_Handle algHandle, IRES_Fxns * resFxns);

} IRESMAN_Fxns;

#ifdef __cplusplus
}
#endif

/*@}*/

#endif
