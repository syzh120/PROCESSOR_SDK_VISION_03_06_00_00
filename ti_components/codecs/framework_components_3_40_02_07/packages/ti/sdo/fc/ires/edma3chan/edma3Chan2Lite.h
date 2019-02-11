/*
 * Copyright (c) 2013, Texas Instruments Incorporated
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
 */

/**
 *  @file
 *
 *  @brief
 *
 *
 */

/**
 *  @addtogroup
 *
 */

#ifndef ti_sdo_fc_ires_edma3chan_EDMA3CHAN2LITE
#define ti_sdo_fc_ires_edma3chan_EDMA3CHAN2LITE

/** @ingroup   */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

#define EDMA3CHANLITE_MAX_TCCS      3
#define EDMA3CHANLITE_MAX_PARAMS    5
#define EDMA3CHANLITE_MAX_RESOURCES 5

#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>


/**
 * @brief        Configuration parameters for Edma3Chan resman
 *               implementation
 */

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
IRES_EDMA3CHAN2_Handle EDMA3CHAN2_createHandle (IALG_Handle alg,
        IRES_EDMA3CHAN_ProtocolArgs * args, Int scratchId);

/*
IRES_Handle IRESMAN_EDMA3CHAN_getHandles(IALG_Handle algHandle,
        IRES_ResourceDescriptor *resDesc, Int scratchGroupId,
        IRES_Status *status);
*/

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
IRES_Status EDMA3CHAN2_freeHandle (IALG_Handle alg, IRES_EDMA3CHAN2_Handle h,
        IRES_EDMA3CHAN_ProtocolArgs *args,  Int scratchId);

/*
IRES_Status IRESMAN_EDMA3CHAN_freeHandle(IALG_Handle algHandle,
        IRES_Handle algResourceHandle, IRES_ResourceDescriptor *resDesc,
        Int scratchGroupId);
*/


typedef struct EDMA3CHANLITE_logicalChannel {
    int chanNo;
    int numTccs;
    int tccArr[EDMA3CHANLITE_MAX_TCCS];
    int numParams;
    int paramArr[EDMA3CHANLITE_MAX_PARAMS];
    int scratchGrp;
    int numUsers;
} EDMA3CHANLITE_logicalChannel;


extern EDMA3CHANLITE_logicalChannel
        ti_sdo_fc_ires_edma3chan_EDMA3CHANLITE_chanArray[EDMA3CHANLITE_MAX_RESOURCES];

extern Int ti_sdo_fc_ires_edma3chan_EDMA3CHANLITE_numChans;


extern UInt ti_sdo_fc_ires_edma3chan_EDMA3CHANLITE_baseAddr;

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/ /** @ingroup */
#endif /* ti_sdo_fc_ires_edma3chan_EDMA3CHAN2LITE */
