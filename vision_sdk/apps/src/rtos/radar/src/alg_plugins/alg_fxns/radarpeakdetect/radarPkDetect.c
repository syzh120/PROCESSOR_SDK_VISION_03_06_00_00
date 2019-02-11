/******************************************************************************
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/


/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "radarPkDetect_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/**
 *******************************************************************************
 * \brief   Global structure containing Algorithm Functions
 *******************************************************************************
 */
static AlgRadarProcessFxns_FxnTable gAlgorithmFxn_RadarPkDetect_fxns =
{
    &AlgorithmFxn_RadarPkDetectCreate,
    &AlgorithmFxn_RadarPkDetectProcess,
    &AlgorithmFxn_RadarPkDetectControl,
    &AlgorithmFxn_RadarPkDetectDelete
};

/**
 *******************************************************************************
 *
 * \brief Implementation of get functions for the algorithm functions
 *
 *        This function will be called to get the pointer to the table of
 *        functions which correspond to this algorithm.
 *
 * \return  AlgRadarProcessFxns_FxnTable pointer.
 *
 *******************************************************************************
 */
AlgRadarProcessFxns_FxnTable *AlgorithmFxn_RadarPkDetect_getFunctions(void)
{
    return &gAlgorithmFxn_RadarPkDetect_fxns;
}


static void AlgorithmFxn_RadarPkDetectAllocWorkArgs(AlgorithmFxn_RadarPkDetectObj * pObj)
{
    Int32 status;

    /* Define the processor on which the peak detection work queue will run */
    pObj->workCpuId = SYSTEM_PROC_EVE1;

    /* Allocate buffers where the different parameters of the work queue will
     * be passed.
     */
    pObj->createInArgsSize
        = SystemUtils_align(sizeof(RadarPkDetectWork_CreateInArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->createOutArgsSize
        = SystemUtils_align(sizeof(RadarPkDetectWork_CreateOutArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->processInArgsSize
        = SystemUtils_align(sizeof(RadarPkDetectWork_ProcessInArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->processOutArgsSize
        = SystemUtils_align(sizeof(RadarPkDetectWork_ProcessOutArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->deleteInArgsSize
        = SystemUtils_align(sizeof(RadarPkDetectWork_DeleteInArgs), SYSTEM_WORK_ARGS_ALIGN);

    pObj->pCreateInArgs = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                    pObj->createInArgsSize,
                                    SYSTEM_WORK_ARGS_ALIGN);
    UTILS_assert(pObj->pCreateInArgs!=NULL);

    pObj->pCreateOutArgs = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                    pObj->createOutArgsSize,
                                    SYSTEM_WORK_ARGS_ALIGN);
    UTILS_assert(pObj->pCreateOutArgs!=NULL);

    pObj->pProcessInArgs = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                    pObj->processInArgsSize,
                                    SYSTEM_WORK_ARGS_ALIGN);
    UTILS_assert(pObj->pProcessInArgs!=NULL);

    pObj->pProcessOutArgs = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                    pObj->processOutArgsSize,
                                    SYSTEM_WORK_ARGS_ALIGN);
    UTILS_assert(pObj->pProcessOutArgs!=NULL);

    pObj->pDeleteInArgs = Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                    pObj->deleteInArgsSize,
                                    SYSTEM_WORK_ARGS_ALIGN);
    UTILS_assert(pObj->pDeleteInArgs!=NULL);
    /* Allocate a work queue object to talk from the host to the EVE work queue */
    status = System_workAllocObj(&pObj->createWorkObjId, SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    System_workSetInArgs(pObj->createWorkObjId, pObj->pCreateInArgs, pObj->createInArgsSize);
    System_workSetOutArgs(pObj->createWorkObjId, pObj->pCreateOutArgs, pObj->createOutArgsSize);
    System_workSetCommand(pObj->createWorkObjId, RADAR_PKDETECT_WORK_FXN_ID, RADAR_PKDETECT_WORK_FXN_CMD_CREATE);

    status = System_workAllocObj(&pObj->processWorkObjId, SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    System_workSetInArgs(pObj->processWorkObjId, pObj->pProcessInArgs, pObj->processInArgsSize);
    System_workSetOutArgs(pObj->processWorkObjId, pObj->pProcessOutArgs, pObj->processOutArgsSize);
    System_workSetCommand(pObj->processWorkObjId, RADAR_PKDETECT_WORK_FXN_ID, RADAR_PKDETECT_WORK_FXN_CMD_PROCESS);

    status = System_workAllocObj(&pObj->deleteWorkObjId, SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    System_workSetInArgs(pObj->deleteWorkObjId, pObj->pDeleteInArgs, pObj->deleteInArgsSize);
    System_workSetOutArgs(pObj->deleteWorkObjId, NULL, 0);
    System_workSetCommand(pObj->deleteWorkObjId, RADAR_PKDETECT_WORK_FXN_ID, RADAR_PKDETECT_WORK_FXN_CMD_DELETE);
}

static void AlgorithmFxn_RadarPkDetectFreeWorkArgs(AlgorithmFxn_RadarPkDetectObj * pObj)
{
    /* Free all allocated work queue objects and corresponding allocated buffers.
     * This should be the same as the ones created in the create time.
     */
    System_workFreeObj(&pObj->createWorkObjId);
    System_workFreeObj(&pObj->processWorkObjId);
    System_workFreeObj(&pObj->deleteWorkObjId);

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pObj->pCreateInArgs, pObj->createInArgsSize);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pObj->pCreateOutArgs, pObj->createOutArgsSize);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pObj->pProcessInArgs, pObj->processInArgsSize);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pObj->pProcessOutArgs, pObj->processOutArgsSize);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pObj->pDeleteInArgs, pObj->deleteInArgsSize);
}

static void AlgorithmFxn_RadarPkDetectSetupWorkProcessDeleteArgs(AlgorithmFxn_RadarPkDetectObj * pObj)
{
    pObj->pProcessInArgs->pkDetAlghandle =
            pObj->pCreateOutArgs->pkDetAlghandle;
    pObj->pDeleteInArgs->pkDetAlghandle =
        pObj->pCreateOutArgs->pkDetAlghandle;
}

static void AlgorithmFxn_RadarPkDetectSetAlgCreateParams(AlgorithmFxn_RadarPkDetectObj * pObj)
{
    PEAK_DETECTION_TI_CreateParams *pPkDetectcreateParams;
    pPkDetectcreateParams = &pObj->pCreateInArgs->pkDetcreateParams;

    /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/
    pPkDetectcreateParams->maxNumAntenna        = pObj->algLinkCreateParams.maxNumAntenna;
    pPkDetectcreateParams->maxNumTx             = pObj->algLinkCreateParams.maxNumTx;
    pPkDetectcreateParams->maxRangeDimension    = pObj->algLinkCreateParams.maxRangeDimension;
    pPkDetectcreateParams->maxDopplerDimension  = pObj->algLinkCreateParams.maxDopplerDimension;
    pPkDetectcreateParams->detectionMethod      = pObj->algLinkCreateParams.detectionMethod;
    pPkDetectcreateParams->enableAntennaDataOut = pObj->algLinkCreateParams.enableAntennaDataOut;
    pPkDetectcreateParams->algoCreateParams.cfarCaDb.maxNoiseLen = pObj->algLinkCreateParams.algoCreateParams.cfarCaDb.maxNoiseLen;
    pPkDetectcreateParams->algoCreateParams.cfarCaDb.maxGaurdLen = pObj->algLinkCreateParams.algoCreateParams.cfarCaDb.maxGaurdLen;

    pPkDetectcreateParams->visionParams.algParams.size = sizeof(PEAK_DETECTION_TI_CreateParams);
    pPkDetectcreateParams->visionParams.cacheWriteBack = NULL;
}

static void AlgorithmFxn_RadarPkDetectSetAlgProcessParams(AlgorithmFxn_RadarPkDetectObj * pObj)
{
    AlgorithmFxn_RadarPkDetectCreateParams *algLinkParams;
    RadarPkDetectWork_ProcessInAlgArgs *pProcessInAlgArgs;
    UInt32 i;

    algLinkParams = &pObj->algLinkCreateParams;

    pProcessInAlgArgs = &pObj->pProcessInArgs->inAlgArgs;

    pProcessInAlgArgs->inArgs.iVisionInArgs.size   = sizeof(PEAK_DETECTION_TI_InArgs);
    pProcessInAlgArgs->inArgs.iVisionInArgs.subFrameInfo = 0;
    pObj->pProcessOutArgs->outArgs.iVisionOutArgs.size = sizeof(PEAK_DETECTION_TI_OutArgs);

    for(i = 0 ; i < PEAK_DETECTION_TI_BUFDESC_IN_TOTAL ;i++)
    {
        pProcessInAlgArgs->inBufDescList[i]  = &pProcessInAlgArgs->inBufDesc[i];
    }
    for(i = 0 ; i < PEAK_DETECTION_TI_BUFDESC_OUT_TOTAL ;i++)
    {
        pProcessInAlgArgs->outBufDescList[i] = &pProcessInAlgArgs->outBufDesc[i];
    }

    pProcessInAlgArgs->inBufs.bufDesc  = pProcessInAlgArgs->inBufDescList;
    pProcessInAlgArgs->outBufs.bufDesc = pProcessInAlgArgs->outBufDescList;

    pProcessInAlgArgs->inArgs.enableTxDecoding       = algLinkParams->enableTxDecoding;
    pProcessInAlgArgs->inArgs.numTx                  = algLinkParams->numTx[0];
    pProcessInAlgArgs->inArgs.numRx                  = algLinkParams->numRx[0];
    memcpy((void *)pProcessInAlgArgs->inArgs.txDecodingCoefficients,
           (void*)algLinkParams->txDecodingCoefficients, sizeof(Int16) * RADAR_PKDETECT_MAX_TX * RADAR_PKDETECT_MAX_TX);
    pProcessInAlgArgs->inArgs.rangeDim               = algLinkParams->rangeDim[0];
    pProcessInAlgArgs->inArgs.dopplerDim             = algLinkParams->dopplerDim[0];
    pProcessInAlgArgs->inArgs.algoParams.cfarCaDb.noiseLen  = algLinkParams->cfarCaDb.noiseLen;
    pProcessInAlgArgs->inArgs.algoParams.cfarCaDb.gaurdLen  = algLinkParams->cfarCaDb.gaurdLen;
    pProcessInAlgArgs->inArgs.algoParams.cfarCaDb.constant1 = algLinkParams->cfarCaDb.constant1;
    pProcessInAlgArgs->inArgs.algoParams.cfarCaDb.constant2 = algLinkParams->cfarCaDb.constant2;
}

static void AlgorithmFxn_RadarPkDetectDoWorkCreate(AlgorithmFxn_RadarPkDetectObj * pObj)
{
    /* alloc memory and object required to submit work to EVE */
    AlgorithmFxn_RadarPkDetectAllocWorkArgs(pObj);

    /* Setup algorithm create parameters */
    AlgorithmFxn_RadarPkDetectSetAlgCreateParams(pObj);

    System_workSubmit(pObj->createWorkObjId, pObj->workCpuId);
    System_workWaitComplete(pObj->createWorkObjId, SYSTEM_WORK_TIMEOUT_FOREVER);

    UTILS_assert(pObj->pCreateOutArgs->pkDetAlghandle != NULL);

    AlgorithmFxn_RadarPkDetectSetupWorkProcessDeleteArgs(pObj);
}

static Int32 AlgorithmFxn_RadarPkDetectDoWorkProcess(AlgorithmFxn_RadarPkDetectObj * pObj)
{
    UInt32 status;

    System_workSubmit(pObj->processWorkObjId, pObj->workCpuId);
    System_workWaitComplete(pObj->processWorkObjId, SYSTEM_WORK_TIMEOUT_FOREVER);
    System_workGetStatus(pObj->processWorkObjId, &status);

    return (Int32)status;
}

static void AlgorithmFxn_RadarPkDetectDoWorkDelete(AlgorithmFxn_RadarPkDetectObj * pObj)
{
    System_workSubmit(pObj->deleteWorkObjId, pObj->workCpuId);
    System_workWaitComplete(pObj->deleteWorkObjId, SYSTEM_WORK_TIMEOUT_FOREVER);

    AlgorithmFxn_RadarPkDetectFreeWorkArgs(pObj);
}

void * AlgorithmFxn_RadarPkDetectCreate(
    AlgorithmLink_RadarProcessCreateParams *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams)
{
    AlgorithmFxn_RadarPkDetectCreateParams *pLinkCreateParams;
    System_LinkChInfo * pOutChInfo;
    AlgorithmFxn_RadarPkDetectObj * pObj;
    System_LinkInfo prevLinkInfo;
    UInt32 prevLinkQueId;
    UInt32 chId;

    pLinkCreateParams = (AlgorithmFxn_RadarPkDetectCreateParams *)createParams;

    pObj = (AlgorithmFxn_RadarPkDetectObj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmFxn_RadarPkDetectObj), 32);
    UTILS_assert(pObj != NULL);

    /*
    * Taking copy of needed create time parameters in local object for future
    * reference.
    */
    memcpy((void*)(&pObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmFxn_RadarPkDetectCreateParams));

    /* Keep a copy of the run time parameters */
    pObj->algLinkControlParams.enableTxDecoding       = pLinkCreateParams->enableTxDecoding;
    memcpy(pObj->algLinkControlParams.numTx, pLinkCreateParams->numTx, RADAR_PKDETECT_MAX_NUM_PROFILE*sizeof(UInt16));
    memcpy(pObj->algLinkControlParams.numRx, pLinkCreateParams->numRx, RADAR_PKDETECT_MAX_NUM_PROFILE*sizeof(UInt16));
    memcpy((void*)pObj->algLinkControlParams.txDecodingCoefficients, (void*)pLinkCreateParams->txDecodingCoefficients, pLinkCreateParams->numTx[0] * pLinkCreateParams->numTx[0] * sizeof(Int16));
    memcpy(pObj->algLinkControlParams.rangeDim, pLinkCreateParams->rangeDim, RADAR_PKDETECT_MAX_NUM_PROFILE*sizeof(UInt16));
    memcpy(pObj->algLinkControlParams.dopplerDim, pLinkCreateParams->dopplerDim, RADAR_PKDETECT_MAX_NUM_PROFILE*sizeof(UInt16));
    pObj->algLinkControlParams.cfarCaDb.noiseLen  = pLinkCreateParams->cfarCaDb.noiseLen;
    pObj->algLinkControlParams.cfarCaDb.gaurdLen  = pLinkCreateParams->cfarCaDb.gaurdLen;
    pObj->algLinkControlParams.cfarCaDb.constant1 = pLinkCreateParams->cfarCaDb.constant1;
    pObj->algLinkControlParams.cfarCaDb.constant2 = pLinkCreateParams->cfarCaDb.constant2;

    /* Fill the output buffer information */
    for (chId = 0; chId < SYSTEM_MAX_CH_PER_OUT_QUE; chId++)
    {
        pOutChInfo          = &opParams->outputChannelInfo[chId];

        pOutChInfo->height = 0;
        pOutChInfo->width  = 0;
        pOutChInfo->startX = 0;
        pOutChInfo->startY = 0;
        pOutChInfo->flags  = 0;

        pOutChInfo->pitch[0] = 0;
        pOutChInfo->pitch[1] = pOutChInfo->pitch[0];
        pOutChInfo->pitch[2] = pOutChInfo->pitch[0];
        opParams->outputBufferSize[chId] = sizeof(AlgorithmFxn_RadarPkDetectBuffDescriptor);
        opParams->metaBufSize[chId][0] = opParams->outputBufferSize[chId];
    }

    opParams->outputBufferType = SYSTEM_BUFFER_TYPE_METADATA;
    opParams->numMetaDataPlanes = 1;
    opParams->inputBufCacheOps = ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_NONE;
    opParams->outputBufCacheOps = ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_NONE;

    System_linkGetInfo(createParams->inQueParams.prevLinkId,
                                &prevLinkInfo);
    prevLinkQueId = createParams->inQueParams.prevLinkQueId;
    opParams->numOutputCh = prevLinkInfo.queInfo[prevLinkQueId].numCh;
    memcpy(&pObj->prevChInfo, &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0]),
            sizeof(System_LinkChInfo)
           );

    /* Submit work to create algorithm */
    AlgorithmFxn_RadarPkDetectDoWorkCreate(pObj);
    /* Setup algorithm process parameters */
    AlgorithmFxn_RadarPkDetectSetAlgProcessParams(pObj);

    return (void *) pObj;
}

Int32 AlgorithmFxn_RadarPkDetectProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarPkDetectObj *pObj;
    System_VideoFrameBuffer  *pInputVideoBuffer;
    System_MetaDataBuffer    *pOutputVideoBuffer;
    UInt8  *inBufAddr;
    AlgorithmFxn_RadarFftBuffDescriptor *metaDataBuffAddr;
    AlgorithmFxn_RadarPkDetectBuffDescriptor *outBuf;
    AlgorithmFxn_RadarPkDetectCreateParams *algLinkParams;
    AlgorithmFxn_RadarPkDetectControlParams *algLinkCtrlParams;
    UInt32 currProfile = 0U, i = 0U;

    pObj = (AlgorithmFxn_RadarPkDetectObj *)alg_handle;

    pInputVideoBuffer   = (System_VideoFrameBuffer *)in_buf->payload;
    pOutputVideoBuffer  = (System_MetaDataBuffer *)out_buf->payload;

    inBufAddr           = (UInt8 *)pInputVideoBuffer->bufAddr[0];
    outBuf          = (AlgorithmFxn_RadarPkDetectBuffDescriptor *)
        pOutputVideoBuffer->bufAddr[0];
    metaDataBuffAddr    = (AlgorithmFxn_RadarFftBuffDescriptor *)
        pInputVideoBuffer->metaBufAddr;

    algLinkParams = &pObj->algLinkCreateParams;
    algLinkCtrlParams = &pObj->algLinkControlParams;

    pObj->pProcessInArgs->inAlgArgs.inBufs.bufDesc[
        PEAK_DETECTION_TI_BUFDESC_IN_ANTENNA_DATA_BUF]->bufPlanes[0].buf =
            inBufAddr;
    pObj->pProcessInArgs->inAlgArgs.outBufs.bufDesc[
        PEAK_DETECTION_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf =
            (UInt8  *)&outBuf->objBuf;
    pObj->pProcessInArgs->inAlgArgs.outBufs.bufDesc[
        PEAK_DETECTION_TI_BUFDESC_OUT_ENERGY_BUFFER]->bufPlanes[0].buf =
            (UInt8  *)&outBuf->energyBuf;
    if (algLinkParams->enableAntennaDataOut == 1)
    {
        pObj->pProcessInArgs->inAlgArgs.outBufs.bufDesc[
        PEAK_DETECTION_TI_BUFDESC_OUT_ANTENNA_DATA]->bufPlanes[0].buf =
            (UInt8  *)&outBuf->antData;
    }

    pObj->pProcessInArgs->inAlgArgs.inArgs.bufDescription.numChunks = metaDataBuffAddr->bufDesc.numChunks;
    pObj->pProcessInArgs->inAlgArgs.inArgs.bufDescription.numAntennas = metaDataBuffAddr->bufDesc.numAntennas;
    pObj->pProcessInArgs->inAlgArgs.inArgs.bufDescription.numVertPoints = metaDataBuffAddr->bufDesc.numVertPoints;
    currProfile = metaDataBuffAddr->profileId;
    for (i = 0U; i < metaDataBuffAddr->bufDesc.numChunks; i++)
    {
        pObj->pProcessInArgs->inAlgArgs.inArgs.bufDescription.numHorzPoints[i] = metaDataBuffAddr->bufDesc.numHorzPoints[i];
        pObj->pProcessInArgs->inAlgArgs.inArgs.bufDescription.offsetBwAntennas[i] = metaDataBuffAddr->bufDesc.offsetBwAntennas[i];
        pObj->pProcessInArgs->inAlgArgs.inArgs.bufDescription.pitch[i] = metaDataBuffAddr->bufDesc.pitch[i];
    }
    pObj->pProcessInArgs->inAlgArgs.inArgs.enableTxDecoding = algLinkCtrlParams->enableTxDecoding;
    pObj->pProcessInArgs->inAlgArgs.inArgs.numTx = algLinkCtrlParams->numTx[currProfile];
    pObj->pProcessInArgs->inAlgArgs.inArgs.numRx = algLinkCtrlParams->numRx[currProfile];
    pObj->pProcessInArgs->inAlgArgs.inArgs.offsetBwTx = metaDataBuffAddr->bufDesc.offsetBwAntennas[0] * algLinkCtrlParams->numRx[currProfile];
    pObj->pProcessInArgs->inAlgArgs.inArgs.offsetBwRx = metaDataBuffAddr->bufDesc.offsetBwAntennas[0];
    pObj->pProcessInArgs->inAlgArgs.inArgs.txDecodingCoefficients = (Int16*)algLinkCtrlParams->txDecodingCoefficients;
    pObj->pProcessInArgs->inAlgArgs.inArgs.rangeDim = algLinkCtrlParams->rangeDim[currProfile];
    pObj->pProcessInArgs->inAlgArgs.inArgs.dopplerDim = algLinkCtrlParams->dopplerDim[currProfile];
    memcpy((void *)&pObj->pProcessInArgs->inAlgArgs.inArgs.algoParams.cfarCaDb, (const void *)&algLinkCtrlParams->cfarCaDb, sizeof(PEAK_DETECTION_TI_CfarCaDbParams));

    status = AlgorithmFxn_RadarPkDetectDoWorkProcess(pObj);

    if(status==SYSTEM_LINK_STATUS_SOK)
    {
        AlgorithmFxn_RadarPkDetectBuffDescriptor * bufDesc =
            (AlgorithmFxn_RadarPkDetectBuffDescriptor *) outBuf;
        bufDesc->profileId = currProfile;
        bufDesc->numDetections = pObj->pProcessOutArgs->outArgs.numDetections;
        /* Write Back optimization of only first two words of the buf desc */
        BspOsal_cacheWbInv(
            (UInt8*)&bufDesc->profileId,
            sizeof(UInt32),
            BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
        BspOsal_cacheWbInv(
            (UInt8*)&bufDesc->numDetections,
            sizeof(UInt32),
            BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
        #if 0
        if (bufDesc->numDetections > 0)
    	{
            for (i = 0; i < bufDesc->numDetections; i++)
            {
                Vps_printf("%d) Doppler = %d, Range = %d\n\r",i, bufDesc->objBuf[i].dopplerIdx, bufDesc->objBuf[i].rangeIdx);
            }
            Vps_printf("------------------------------------------------------\n");
        }
        #endif
    }

    return status;
}

Int32 AlgorithmFxn_RadarPkDetectControl(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams)
{
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 AlgorithmFxn_RadarPkDetectDelete(void *alg_handle)
{
    UInt32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarPkDetectObj *pObj;

    pObj = (AlgorithmFxn_RadarPkDetectObj *)alg_handle;

    AlgorithmFxn_RadarPkDetectDoWorkDelete(pObj);

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                  pObj,
                  sizeof(AlgorithmFxn_RadarPkDetectObj)
                    );
    return status;
}
