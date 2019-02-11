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
 *  @file       ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h
 *
 *  @brief      IRESMAN EDMA3 specific Resource Manager Definitions -
 *              EDMA3 resource manager implementation
 *
 */

/**
 *  @addtogroup ti_sdo_fc_ires_edma3chan_IRESMAN_EDMA3CHAN IRESMAN EDMA3 -
 *              EDMA3 specific Resource Manager and corresponding
 *              IRES Protocol Implementation
 */

#ifndef ti_sdo_fc_ires_edma3chan_IRESMAN_EDMA3CHAN_
#define ti_sdo_fc_ires_edma3chan_IRESMAN_EDMA3CHAN_

/** @ingroup    ti_sdo_fc_ires_edma3chan_IRESMAN_EDMA3CHAN */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/iresman_protocol.h>

#include "iresman_protocol_edma3Chan.h"

/**
 * @brief        Configuration parameters for Edma3Chan resman
 *               implementation
 */
typedef struct IRESMAN_Edma3ChanParams {

    /**
     * The base configuration information
     */
    IRESMAN_Params baseConfig;

} IRESMAN_Edma3ChanParams ;

/**
 *  @brief        Function to return the name of the protocol
 *  @retval       String name identifying the protocol
 */
String IRESMAN_EDMA3CHAN_getProtocolName();

/**
 *  @brief        Function to return the revision of the protocol
 *  @retval       Revision identifying the protocol
 */
IRES_ProtocolRevision * IRESMAN_EDMA3CHAN_getProtocolRevision();

/**
 *  @brief        Function to initialize the device specific resource manager
 *                implementation
 *  @param[in]    initArgs           Initialization arguments that may be
 *                                   interpreted by the device specific
 *                                   implementation
 *  @retval       IRES_Status        IRES_OK         Success
 *                                   IRES_EEXISTS    Already initialized
 *                                   IRES_EFAIL      Error
 *
 */
IRES_Status IRESMAN_EDMA3CHAN_init( IRESMAN_Params * initArgs);

/**
 *  @brief        Function called when RESMAN is no longer needed. Use it to
 *                free memory allocated etc
 *  @retval       IRES_Status        IRES_OK         Success
 *                                   IRES_ENOINIT    Not initialized
 *                                   IRES_EFAIL      Error
 */
IRES_Status IRESMAN_EDMA3CHAN_exit();

/**
 *  @brief        Function that returns the IRES_Handle to the resource
 *                requested using the IRES_ResourceProtocolArgs.
 *
 *  @param[in]    algHandle          Handle of the algorithm that requests
 *                                   the resources
 *  @param[in]    resDesc            Arguments to be interpreted by the
 *                                   IRES_Manager implementation to determine
 *                                   which actual physical resources to obtain
 *  @param[in]    scratchGroupId     Group Id required if scratch resources are
 *                                   requested, -1 otherwise
 *  @param[out]   status             Status of this call
 *
 *  @retval       IRES_Handle        Valid handle corresponding to the resource
 *                                   requested on success, or NULL on error.
 */
IRES_Handle IRESMAN_EDMA3CHAN_getHandles(IALG_Handle algHandle,
        IRES_ResourceDescriptor *resDesc, Int scratchGroupId,
        IRES_Status *status);

/**
 *  @brief        Frees handles back to the resource pool
 *
 *  @param[in]    algHandle          Handle of the algorithm that frees
 *                                   the resources
 *  @param[in]    algResourceHandle  Handle that is to be released
 *  @param[in]    resDesc            Arguments that help determine which
 *                                   resources to free
 *  @param[in]    scratchGroupId     Group Id required if scratch resources are
 *                                   requested, -1 otherwise
 *
 *  @retval       IRES_Status        IRES_OK     Success
 *                                   IRES_EFAIL  Failure
 */
IRES_Status IRESMAN_EDMA3CHAN_freeHandle(IALG_Handle algHandle,
        IRES_Handle algResourceHandle, IRES_ResourceDescriptor *resDesc,
        Int scratchGroupId);

/**
 *  @brief       Memory allocation functions for all of RMANs
 *               and other IRES rotocol's memory requirements
 */
extern __FAR__ IRESMAN_PersistentAllocFxn _RMAN_allocPersistent;

/**
 *  @brief       Memory free functions for all of RMANs
 *               and other IRES protocol's memory requirements
 */
extern __FAR__ IRESMAN_PersistentFreeFxn _RMAN_freePersistent;

/**
 * @brief        IRES RESMAN implementation for EDMA3 Linked transfers
 */
extern IRESMAN_Fxns IRESMAN_EDMA3CHAN;

#ifdef __cplusplus
}
#endif /* extern "C" */


/*@}*/ /** @ingroup */

#endif
