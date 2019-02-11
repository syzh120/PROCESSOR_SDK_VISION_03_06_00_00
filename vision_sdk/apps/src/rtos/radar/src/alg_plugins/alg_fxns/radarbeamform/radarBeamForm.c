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
#include "radarBeamForm_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/**
 *******************************************************************************
 * \brief   Global structure containing Algorithm Functions
 *******************************************************************************
 */
static AlgRadarProcessFxns_FxnTable gAlgorithmFxn_RadarBeamForm_fxns =
{
    &AlgorithmFxn_RadarBeamFormCreate,
    &AlgorithmFxn_RadarBeamFormProcess,
    &AlgorithmFxn_RadarBeamFormControl,
    &AlgorithmFxn_RadarBeamFormDelete
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
AlgRadarProcessFxns_FxnTable *AlgorithmFxn_RadarBeamForm_getFunctions(void)
{
    return &gAlgorithmFxn_RadarBeamForm_fxns;
}


static void AlgorithmFxn_RadarBeamFormAllocWorkArgs(AlgorithmFxn_RadarBeamFormObj * pObj)
{
    Int32 status;

    /* Define the processor on which the peak detection work queue will run */
    pObj->workCpuId = SYSTEM_PROC_EVE1;

    /* Allocate buffers where the different parameters of the work queue will
     * be passed.
     */
    pObj->createInArgsSize
        = SystemUtils_align(sizeof(RadarBeamFormWork_CreateInArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->createOutArgsSize
        = SystemUtils_align(sizeof(RadarBeamFormWork_CreateOutArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->processInArgsSize
        = SystemUtils_align(sizeof(RadarBeamFormWork_ProcessInArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->processOutArgsSize
        = SystemUtils_align(sizeof(RadarBeamFormWork_ProcessOutArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->deleteInArgsSize
        = SystemUtils_align(sizeof(RadarBeamFormWork_DeleteInArgs), SYSTEM_WORK_ARGS_ALIGN);

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
    System_workSetCommand(pObj->createWorkObjId, RADAR_BEAMFORM_WORK_FXN_ID, RADAR_BEAMFORM_WORK_FXN_CMD_CREATE);

    status = System_workAllocObj(&pObj->processWorkObjId, SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    System_workSetInArgs(pObj->processWorkObjId, pObj->pProcessInArgs, pObj->processInArgsSize);
    System_workSetOutArgs(pObj->processWorkObjId, pObj->pProcessOutArgs, pObj->processOutArgsSize);
    System_workSetCommand(pObj->processWorkObjId, RADAR_BEAMFORM_WORK_FXN_ID, RADAR_BEAMFORM_WORK_FXN_CMD_PROCESS);

    status = System_workAllocObj(&pObj->deleteWorkObjId, SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    System_workSetInArgs(pObj->deleteWorkObjId, pObj->pDeleteInArgs, pObj->deleteInArgsSize);
    System_workSetOutArgs(pObj->deleteWorkObjId, NULL, 0);
    System_workSetCommand(pObj->deleteWorkObjId, RADAR_BEAMFORM_WORK_FXN_ID, RADAR_BEAMFORM_WORK_FXN_CMD_DELETE);
}

static void AlgorithmFxn_RadarBeamFormFreeWorkArgs(AlgorithmFxn_RadarBeamFormObj * pObj)
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

static void AlgorithmFxn_RadarBeamFormSetupWorkProcessDeleteArgs(AlgorithmFxn_RadarBeamFormObj * pObj)
{
    pObj->pProcessInArgs->beamFormAlghandle =
            pObj->pCreateOutArgs->beamFormAlghandle;
    pObj->pDeleteInArgs->beamFormAlghandle =
        pObj->pCreateOutArgs->beamFormAlghandle;
}

static void AlgorithmFxn_RadarBeamFormSetAlgCreateParams(AlgorithmFxn_RadarBeamFormObj * pObj)
{
    BEAM_FORMING_TI_CreateParams *pBeamFormcreateParams;
    pBeamFormcreateParams = &pObj->pCreateInArgs->beamFormcreateParams;

    /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/
    pBeamFormcreateParams->maxNumAntenna        = pObj->algLinkCreateParams.maxNumAntenna;
    pBeamFormcreateParams->maxNumDetection      = pObj->algLinkCreateParams.maxNumDetection;
    pBeamFormcreateParams->maxNumAngle          = pObj->algLinkCreateParams.maxNumAngle;
    pBeamFormcreateParams->coordinateBufFormat  = pObj->algLinkCreateParams.coordinateBufFormat;

    pBeamFormcreateParams->visionParams.algParams.size = sizeof(BEAM_FORMING_TI_CreateParams);
    pBeamFormcreateParams->visionParams.cacheWriteBack = NULL;
}

static void AlgorithmFxn_RadarBeamFormSetAlgProcessParams(AlgorithmFxn_RadarBeamFormObj * pObj)
{
    AlgorithmFxn_RadarBeamFormCreateParams *algLinkParams;
    RadarBeamFormWork_ProcessInAlgArgs *pProcessInAlgArgs;
    UInt32 i;

    algLinkParams = &pObj->algLinkCreateParams;

    pProcessInAlgArgs = &pObj->pProcessInArgs->inAlgArgs;

    pProcessInAlgArgs->inArgs.iVisionInArgs.size   = sizeof(BEAM_FORMING_TI_InArgs);
    pProcessInAlgArgs->inArgs.iVisionInArgs.subFrameInfo = 0;
    pObj->pProcessOutArgs->outArgs.iVisionOutArgs.size = sizeof(BEAM_FORMING_TI_OutArgs);

    for(i = 0 ; i < BEAM_FORMING_TI_BUFDESC_IN_TOTAL ;i++)
    {
        pProcessInAlgArgs->inBufDescList[i]  = &pProcessInAlgArgs->inBufDesc[i];
    }
    for(i = 0 ; i < BEAM_FORMING_TI_BUFDESC_OUT_TOTAL ;i++)
    {
        pProcessInAlgArgs->outBufDescList[i] = &pProcessInAlgArgs->outBufDesc[i];
    }

    pProcessInAlgArgs->inBufs.bufDesc  = pProcessInAlgArgs->inBufDescList;
    pProcessInAlgArgs->outBufs.bufDesc = pProcessInAlgArgs->outBufDescList;

    /* numDetections is obtained from the previous link buffer */
    pProcessInAlgArgs->inArgs.numDetections          = 0;
    pProcessInAlgArgs->inArgs.numAntennas            = algLinkParams->numAntennas[0];
    pProcessInAlgArgs->inArgs.numAngles              = algLinkParams->numAngles;
    pProcessInAlgArgs->inArgs.beamFormingScaling     = algLinkParams->beamFormingScaling;
    pProcessInAlgArgs->inArgs.energyScaling          = algLinkParams->energyScaling;
}

static void AlgorithmFxn_RadarBeamFormDoWorkCreate(AlgorithmFxn_RadarBeamFormObj * pObj)
{
    /* alloc memory and object required to submit work to EVE */
    AlgorithmFxn_RadarBeamFormAllocWorkArgs(pObj);

    /* Setup algorithm create parameters */
    AlgorithmFxn_RadarBeamFormSetAlgCreateParams(pObj);

    System_workSubmit(pObj->createWorkObjId, pObj->workCpuId);
    System_workWaitComplete(pObj->createWorkObjId, SYSTEM_WORK_TIMEOUT_FOREVER);

    UTILS_assert(pObj->pCreateOutArgs->beamFormAlghandle != NULL);

    AlgorithmFxn_RadarBeamFormSetupWorkProcessDeleteArgs(pObj);
}

static Int32 AlgorithmFxn_RadarBeamFormDoWorkProcess(AlgorithmFxn_RadarBeamFormObj * pObj)
{
    UInt32 status;

    System_workSubmit(pObj->processWorkObjId, pObj->workCpuId);
    System_workWaitComplete(pObj->processWorkObjId, SYSTEM_WORK_TIMEOUT_FOREVER);
    System_workGetStatus(pObj->processWorkObjId, &status);

    return (Int32)status;
}

static void AlgorithmFxn_RadarBeamFormDoWorkDelete(AlgorithmFxn_RadarBeamFormObj * pObj)
{
    System_workSubmit(pObj->deleteWorkObjId, pObj->workCpuId);
    System_workWaitComplete(pObj->deleteWorkObjId, SYSTEM_WORK_TIMEOUT_FOREVER);

    AlgorithmFxn_RadarBeamFormFreeWorkArgs(pObj);
}

void * AlgorithmFxn_RadarBeamFormCreate(
    AlgorithmLink_RadarProcessCreateParams *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams)
{
    AlgorithmFxn_RadarBeamFormCreateParams *pLinkCreateParams;
    System_LinkChInfo * pOutChInfo;
    AlgorithmFxn_RadarBeamFormObj * pObj;
    System_LinkInfo prevLinkInfo;
    UInt32 prevLinkQueId;
    UInt32 chId;

    pLinkCreateParams = (AlgorithmFxn_RadarBeamFormCreateParams *)createParams;

    pObj = (AlgorithmFxn_RadarBeamFormObj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmFxn_RadarBeamFormObj), 32);
    UTILS_assert(pObj != NULL);

    /*
    * Taking copy of needed create time parameters in local object for future
    * reference.
    */
    memcpy((void*)(&pObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmFxn_RadarBeamFormCreateParams));

    /* Keep a copy of the run time parameters */
    memcpy((void *)pObj->algLinkControlParams.numAntennas, (void *)pLinkCreateParams->numAntennas, sizeof(UInt16)*RADAR_BEAMFORM_MAX_NUM_PROFILE);
    pObj->algLinkControlParams.numAngles         = pLinkCreateParams->numAngles;
    pObj->algLinkControlParams.beamFormingScaling = pLinkCreateParams->beamFormingScaling;
    pObj->algLinkControlParams.energyScaling     = pLinkCreateParams->energyScaling;
    memcpy((void *)pObj->algLinkControlParams.steeringBuf, (void *)pLinkCreateParams->steeringBuf, sizeof(UInt8*)*RADAR_BEAMFORM_MAX_NUM_PROFILE);

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

        opParams->outputBufferSize[chId] = sizeof(AlgorithmFxn_RadarBeamFormBuffDescriptor);
        opParams->metaBufSize[chId][0] = opParams->outputBufferSize[chId];
    }
    opParams->outputBufferType = SYSTEM_BUFFER_TYPE_METADATA;
    opParams->numMetaDataPlanes = 1;
    opParams->inputBufCacheOps = ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_NONE;
    opParams->outputBufCacheOps = ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_NONE;
    prevLinkQueId = createParams->inQueParams.prevLinkQueId;
    System_linkGetInfo(createParams->inQueParams.prevLinkId, &prevLinkInfo);
    opParams->numOutputCh = prevLinkInfo.queInfo[prevLinkQueId].numCh;

    memcpy(&pObj->prevChInfo, &(prevLinkInfo.queInfo[prevLinkQueId].chInfo[0]),
            sizeof(System_LinkChInfo)
           );

    /* Submit work to create algorithm */
    AlgorithmFxn_RadarBeamFormDoWorkCreate(pObj);
    /* Setup algorithm process parameters */
    AlgorithmFxn_RadarBeamFormSetAlgProcessParams(pObj);

    return (void *) pObj;
}

Int32 AlgorithmFxn_RadarBeamFormProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarBeamFormObj *pObj;
    System_MetaDataBuffer  *pInputMetaBuffer;
    System_MetaDataBuffer  *pOutputMetaBuffer;
    AlgorithmFxn_RadarPkDetectBuffDescriptor  *inBufAddr;
    AlgorithmFxn_RadarBeamFormBuffDescriptor *outBuf;
    AlgorithmFxn_RadarBeamFormControlParams *algLinkCtrlParams;

    pObj = (AlgorithmFxn_RadarBeamFormObj *)alg_handle;

    pInputMetaBuffer   = (System_MetaDataBuffer *)in_buf->payload;
    pOutputMetaBuffer  = (System_MetaDataBuffer *)out_buf->payload;

    inBufAddr           = (AlgorithmFxn_RadarPkDetectBuffDescriptor *)
        pInputMetaBuffer->bufAddr[0];
    outBuf          = (AlgorithmFxn_RadarBeamFormBuffDescriptor *)
        pOutputMetaBuffer->bufAddr[0];
    algLinkCtrlParams = &pObj->algLinkControlParams;

    pObj->pProcessInArgs->inAlgArgs.inBufs.bufDesc[
        BEAM_FORMING_TI_BUFDESC_IN_ANTENNA_DATA_BUF]->bufPlanes[0].buf =
            (UInt8 *)&inBufAddr->antData;
    pObj->pProcessInArgs->inAlgArgs.inBufs.bufDesc[
        BEAM_FORMING_TI_BUFDESC_IN_COORDINATE_BUF]->bufPlanes[0].buf =
            (UInt8 *)&inBufAddr->objBuf;
    pObj->pProcessInArgs->inAlgArgs.inBufs.bufDesc[
        BEAM_FORMING_TI_BUFDESC_IN_STEERINGMATRIX_BUF]->bufPlanes[0].buf =
            (UInt8 *)algLinkCtrlParams->steeringBuf[inBufAddr->profileId];
    pObj->pProcessInArgs->inAlgArgs.outBufs.bufDesc[
        BEAM_FORMING_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf =
            (UInt8  *)outBuf;

    pObj->pProcessInArgs->inAlgArgs.inArgs.numDetections = inBufAddr->numDetections;
    pObj->pProcessInArgs->inAlgArgs.inArgs.numAntennas = algLinkCtrlParams->numAntennas[inBufAddr->profileId];
    pObj->pProcessInArgs->inAlgArgs.inArgs.numAngles = algLinkCtrlParams->numAngles;
    pObj->pProcessInArgs->inAlgArgs.inArgs.beamFormingScaling = algLinkCtrlParams->beamFormingScaling;
    pObj->pProcessInArgs->inAlgArgs.inArgs.energyScaling = algLinkCtrlParams->energyScaling;

    if (inBufAddr->numDetections > 0)
    {
        /* Call the beam forming only when the number of detections is greater than 0 */
        status = AlgorithmFxn_RadarBeamFormDoWorkProcess(pObj);
    }

    if(status==SYSTEM_LINK_STATUS_SOK)
    {
        AlgorithmFxn_RadarBeamFormBuffDescriptor * bufDesc =
            (AlgorithmFxn_RadarBeamFormBuffDescriptor *) outBuf;
        bufDesc->profileId = inBufAddr->profileId;
        bufDesc->numDetections = inBufAddr->numDetections;
        BspOsal_cacheWbInv(
            (UInt8*)bufDesc,
            sizeof(AlgorithmFxn_RadarBeamFormBuffDescriptor),
            BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
#if 0
        if (bufDesc->numDetections > 0)
        {
            UInt32 i = 0U;
            for (i = 0; i < bufDesc->numDetections; i++)
            {
                Vps_printf(
                    "%d) Doppler = %d, Range = %d, Energy = %d, Angle = %d\n\r",
                    i, bufDesc->objBuf[i].velocity,
                    bufDesc->objBuf[i].range,
                    bufDesc->objBuf[i].energy,
                    bufDesc->objBuf[i].angleBin
                    );
            }
            Vps_printf("------------------------------------------------------\n");
        }
#endif
    }

    return status;
}

Int32 AlgorithmFxn_RadarBeamFormControl(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams)
{
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 AlgorithmFxn_RadarBeamFormDelete(void *alg_handle)
{
    UInt32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarBeamFormObj *pObj;

    pObj = (AlgorithmFxn_RadarBeamFormObj *)alg_handle;

    AlgorithmFxn_RadarBeamFormDoWorkDelete(pObj);

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                  pObj,
                  sizeof(AlgorithmFxn_RadarBeamFormObj)
                    );
    return status;
}
