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
#include "radarFft2_priv.h"
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/**
 *******************************************************************************
 * \brief   Global structure containing Algorithm Functions
 *******************************************************************************
 */
static AlgRadarProcessFxns_FxnTable gAlgorithmFxn_RadarFft_fxns =
{
    &AlgorithmFxn_RadarFftCreate,
    &AlgorithmFxn_RadarFftProcess,
    &AlgorithmFxn_RadarFftControl,
    &AlgorithmFxn_RadarFftDelete
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
AlgRadarProcessFxns_FxnTable *AlgorithmFxn_RadarFft2_getFunctions(void)
{
    return &gAlgorithmFxn_RadarFft_fxns;
}


static void AlgorithmFxn_RadarFftAllocWorkArgs(AlgorithmFxn_RadarFftObj * pObj)
{
    Int32 status;

    pObj->workCpuId = pObj->algLinkCreateParams.workQcpuId;

    pObj->createInArgsSize
        = SystemUtils_align(sizeof(RadarFftWork_CreateInArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->createOutArgsSize
        = SystemUtils_align(sizeof(RadarFftWork_CreateOutArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->processInArgsSize
        = SystemUtils_align(sizeof(RadarFftWork_ProcessInArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->processOutArgsSize
        = SystemUtils_align(sizeof(RadarFftWork_ProcessOutArgs), SYSTEM_WORK_ARGS_ALIGN);
    pObj->deleteInArgsSize
        = SystemUtils_align(sizeof(RadarFftWork_DeleteInArgs), SYSTEM_WORK_ARGS_ALIGN);

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

    status = System_workAllocObj(&pObj->createWorkObjId, SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    System_workSetInArgs(pObj->createWorkObjId, pObj->pCreateInArgs, pObj->createInArgsSize);
    System_workSetOutArgs(pObj->createWorkObjId, pObj->pCreateOutArgs, pObj->createOutArgsSize);
    System_workSetCommand(pObj->createWorkObjId, RADAR_FFT_WORK_FXN_ID, RADAR_FFT_WORK_FXN_CMD_CREATE);

    status = System_workAllocObj(&pObj->processWorkObjId, SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    System_workSetInArgs(pObj->processWorkObjId, pObj->pProcessInArgs, pObj->processInArgsSize);
    System_workSetOutArgs(pObj->processWorkObjId, pObj->pProcessOutArgs, pObj->processOutArgsSize);
    System_workSetCommand(pObj->processWorkObjId, RADAR_FFT_WORK_FXN_ID, RADAR_FFT_WORK_FXN_CMD_PROCESS);

    status = System_workAllocObj(&pObj->deleteWorkObjId, SYSTEM_WORK_OBJ_ALLOC_FLAG_USE_ACK_SEM);
    UTILS_assert(status==SYSTEM_LINK_STATUS_SOK);

    System_workSetInArgs(pObj->deleteWorkObjId, pObj->pDeleteInArgs, pObj->deleteInArgsSize);
    System_workSetOutArgs(pObj->deleteWorkObjId, NULL, 0);
    System_workSetCommand(pObj->deleteWorkObjId, RADAR_FFT_WORK_FXN_ID, RADAR_FFT_WORK_FXN_CMD_DELETE);
}

static void AlgorithmFxn_RadarFftFreeWorkArgs(AlgorithmFxn_RadarFftObj * pObj)
{
    System_workFreeObj(&pObj->createWorkObjId);
    System_workFreeObj(&pObj->processWorkObjId);
    System_workFreeObj(&pObj->deleteWorkObjId);

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pObj->pCreateInArgs, pObj->createInArgsSize);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pObj->pCreateOutArgs, pObj->createOutArgsSize);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pObj->pProcessInArgs, pObj->processInArgsSize);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pObj->pProcessOutArgs, pObj->processOutArgsSize);
    Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR, pObj->pDeleteInArgs, pObj->deleteInArgsSize);
}

static void AlgorithmFxn_RadarFftSetupWorkProcessDeleteArgs(AlgorithmFxn_RadarFftObj * pObj)
{
    UInt32 numObj;

    pObj->pProcessInArgs->numObjs = pObj->pCreateInArgs->numObjs;
    pObj->pDeleteInArgs->numObjs = pObj->pCreateInArgs->numObjs;

    for(numObj=0; numObj<pObj->pCreateInArgs->numObjs; numObj++ )
    {
        pObj->pProcessInArgs->fftAlghandle[numObj] =
            pObj->pCreateOutArgs->fftAlghandle[numObj];
        pObj->pDeleteInArgs->fftAlghandle[numObj] =
            pObj->pCreateOutArgs->fftAlghandle[numObj];
    }
}

static void AlgorithmFxn_RadarFftSetAlgCreateParams(AlgorithmFxn_RadarFftObj * pObj)
{
    UInt32 numObj;
    FFT_TI_CreateParams *pFftcreateParams;

    /*-----------------------------------------------------------------
    Set algorithm parameters
    -----------------------------------------------------------------*/
    pObj->pCreateInArgs->numObjs = 0;
    if(pObj->algLinkCreateParams.algFFTMode == RADAR_FFT_MODE_HORIZONTAL)
    {
        pObj->pCreateInArgs->fftcreateParams[0].fftDirection = FFT_TI_DIRECTION_HORIZONTAL;
        pObj->pCreateInArgs->numObjs = 1;
    }
    else if(pObj->algLinkCreateParams.algFFTMode == RADAR_FFT_MODE_VERTICAL)
    {
        pObj->pCreateInArgs->fftcreateParams[0].fftDirection = FFT_TI_DIRECTION_VERTICAL;
        pObj->pCreateInArgs->numObjs = 1;
    }
    else if(pObj->algLinkCreateParams.algFFTMode == RADAR_FFT_MODE_HORZ_AND_VERT)
    {
        pObj->pCreateInArgs->fftcreateParams[0].fftDirection = FFT_TI_DIRECTION_HORIZONTAL;
        pObj->pCreateInArgs->fftcreateParams[1].fftDirection = FFT_TI_DIRECTION_VERTICAL;
        pObj->pCreateInArgs->numObjs = 2;
    }
    else
    {
        /* Should never enter here */
        UTILS_assert(0);
    }

    for(numObj = 0; numObj < pObj->pCreateInArgs->numObjs; numObj++)
    {
        pFftcreateParams = &pObj->pCreateInArgs->fftcreateParams[numObj];
        pFftcreateParams->inputContainerFormat = FFT_TI_CONTAINER_FORMAT_16BIT;
        pFftcreateParams->outputContainerFormat = pObj->algLinkCreateParams.algCreatePrm[numObj].outputContainerFormat;

        pFftcreateParams->visionParams.algParams.size = sizeof(FFT_TI_CreateParams);
        pFftcreateParams->visionParams.cacheWriteBack = NULL;
    }
}

static void AlgorithmFxn_RadarFftSetAlgProcessParams(AlgorithmFxn_RadarFftObj * pObj)
{
    AlgorithmFxn_RadarFftCreateParams *algLinkParams;
    UInt32 i,numObj;

    algLinkParams = &pObj->algLinkCreateParams;

    for(numObj=0; numObj<pObj->pProcessInArgs->numObjs; numObj++)
    {
        RadarFftWork_ProcessInAlgArgs *pProcessInAlgArgs;
        AlgorithmFxn_RadarFftAlgCreateParams *algParams;

        pProcessInAlgArgs = &pObj->pProcessInArgs->inAlgArgs[numObj];

        pProcessInAlgArgs->inArgs.iVisionInArgs.size   = sizeof(FFT_TI_InArgs);
        pProcessInAlgArgs->inArgs.iVisionInArgs.subFrameInfo = 0;
        pObj->pProcessOutArgs->outArgs[numObj].iVisionOutArgs.size = sizeof(FFT_TI_OutArgs);

        for(i = 0 ; i < FFT_TI_BUFDESC_IN_TOTAL ;i++)
        {
            pProcessInAlgArgs->inBufDescList[i]  = &pProcessInAlgArgs->inBufDesc[i];
        }
        for(i = 0 ; i < FFT_TI_BUFDESC_OUT_TOTAL ;i++)
        {
            pProcessInAlgArgs->outBufDescList[i] = &pProcessInAlgArgs->outBufDesc[i];
        }

        pProcessInAlgArgs->inBufs.bufDesc  = pProcessInAlgArgs->inBufDescList;
        pProcessInAlgArgs->outBufs.bufDesc = pProcessInAlgArgs->outBufDescList;

        algParams = &algLinkParams->algCreatePrm[numObj];

        if (algParams->enableWindowing)
        {
            pProcessInAlgArgs->inBufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF].numPlanes = 1;
        }

        if ( pObj->pCreateInArgs->fftcreateParams[numObj].fftDirection == FFT_TI_DIRECTION_HORIZONTAL )
        {
            pProcessInAlgArgs->inArgs.enableDcOffset               = algParams->enableDcoffset;
            pProcessInAlgArgs->inArgs.enable32bitsIntermResults    = 0;
            pProcessInAlgArgs->inArgs.enableDopplerCorrection      = 0;
            pProcessInAlgArgs->inArgs.enableInterferenceZeroOut    = algParams->enableInterferenceZeroOut;
            pProcessInAlgArgs->inArgs.interferenceZeroOutThreshold = algParams->interferenceThreshold;
            pProcessInAlgArgs->inArgs.enableWindowing              = algParams->enableWindowing;
            pProcessInAlgArgs->inArgs.windowingScaleFactor         = algParams->windowingScaleFactor;

            for ( i = 0; i < FFT_TI_MAX_NUM_STAGES; i++)
            {
                pProcessInAlgArgs->inArgs.scaleFactors[i]          = algLinkParams->algCreatePrm[0].scaleFactors[i];
            }
        }
        if ( pObj->pCreateInArgs->fftcreateParams[numObj].fftDirection == FFT_TI_DIRECTION_VERTICAL)
        {
            pProcessInAlgArgs->inArgs.enableDcOffset               = 0;
            pProcessInAlgArgs->inArgs.enable32bitsIntermResults    = 0;
            pProcessInAlgArgs->inArgs.enableDopplerCorrection      = algParams->enableDopplerCorrection;
            pProcessInAlgArgs->inArgs.enableInterferenceZeroOut    = 0;
            pProcessInAlgArgs->inArgs.interferenceZeroOutThreshold = 0;
            pProcessInAlgArgs->inArgs.enableWindowing              = algParams->enableWindowing;
            pProcessInAlgArgs->inArgs.windowingScaleFactor         = algParams->windowingScaleFactor;

            for ( i = 0; i < FFT_TI_MAX_NUM_STAGES; i++)
            {
                pProcessInAlgArgs->inArgs.scaleFactors[i]          = algLinkParams->algCreatePrm[1].scaleFactors[i];
            }
        }
        pProcessInAlgArgs->inArgs.inDataRange = 15;
        pProcessInAlgArgs->inArgs.bufDescription.numChunks           = 1;
    }
}

static void AlgorithmFxn_RadarFftDoWorkCreate(AlgorithmFxn_RadarFftObj * pObj)
{
    UInt32 numObj;

    /* alloc memory and object required to submit work to EVE */
    AlgorithmFxn_RadarFftAllocWorkArgs(pObj);

    /* Setup algorithm create parameters */
    AlgorithmFxn_RadarFftSetAlgCreateParams(pObj);

    System_workSubmit(pObj->createWorkObjId, pObj->workCpuId);
    System_workWaitComplete(pObj->createWorkObjId, SYSTEM_WORK_TIMEOUT_FOREVER);

    for(numObj=0; numObj<pObj->pCreateInArgs->numObjs; numObj++ )
    {
        UTILS_assert(pObj->pCreateOutArgs->fftAlghandle[numObj] != NULL);
    }

    AlgorithmFxn_RadarFftSetupWorkProcessDeleteArgs(pObj);
}

static Int32 AlgorithmFxn_RadarFftDoWorkProcess(AlgorithmFxn_RadarFftObj * pObj)
{
    UInt32 status;

    System_workSubmit(pObj->processWorkObjId, pObj->workCpuId);
    System_workWaitComplete(pObj->processWorkObjId, SYSTEM_WORK_TIMEOUT_FOREVER);
    System_workGetStatus(pObj->processWorkObjId, &status);

    return (Int32)status;
}

static void AlgorithmFxn_RadarFftDoWorkDelete(AlgorithmFxn_RadarFftObj * pObj)
{
    System_workSubmit(pObj->deleteWorkObjId, pObj->workCpuId);
    System_workWaitComplete(pObj->deleteWorkObjId, SYSTEM_WORK_TIMEOUT_FOREVER);

    AlgorithmFxn_RadarFftFreeWorkArgs(pObj);
}

static UInt32 AlgorithmFxn_RadarFftFindMax(UInt32 *arr, UInt32 arrSize)
{
    UInt32 max = 0U, i = 0U;
    for (i = 0U; i < arrSize; i++)
    {
        if (max < arr[i])
        {
            max = arr[i];
        }
    }
    return max;
}

void * AlgorithmFxn_RadarFftCreate(
    AlgorithmLink_RadarProcessCreateParams *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams)
{
    AlgorithmFxn_RadarFftCreateParams *pLinkCreateParams;
    System_LinkChInfo * pOutChInfo;
    AlgorithmFxn_RadarFftObj * pObj;
    UInt32 chId;
    ChainsCommon_Ar12xxConfigOut *pRadarCfg;
    ChainsCommon_RadarParams *pRadarParams;
    UInt16 nextPowerOf2;
    UInt32 i;
    UInt32 imgFrameWidth[RADAR_FFT_MAX_NUM_PROFILE];
    UInt32 imgFrameHeight[RADAR_FFT_MAX_NUM_PROFILE];
    UInt32 outputBufferpitch[RADAR_FFT_MAX_NUM_PROFILE];
    UInt32                    prevLinkQueId;
    System_LinkInfo           prevLinkInfo;
    UInt32 numBytesPerSample;

    pLinkCreateParams = (AlgorithmFxn_RadarFftCreateParams *)createParams;

    pObj = (AlgorithmFxn_RadarFftObj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmFxn_RadarFftObj), 32);
    UTILS_assert(pObj != NULL);

    /*
    * Taking copy of needed create time parameters in local object for future
    * reference.
    */
    memcpy((void*)(&pObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmFxn_RadarFftCreateParams));

    pRadarCfg = pLinkCreateParams->pRadarCfg;
    if(pObj->algLinkCreateParams.algFFTMode == RADAR_FFT_MODE_HORZ_AND_VERT)
    {
        if (pObj->algLinkCreateParams.algCreatePrm[0].outputContainerFormat == FFT_TI_CONTAINER_FORMAT_32BIT)
        {
            Vps_printf(" ALG_FXN: RADARFFT: Output Container Format for 1D FFT should not be 32-bit if input is given to 2D FFT !!\n\r");
            UTILS_assert(0);
        }
    }
    /* Fill the output buffer information */
    for (chId = 0; chId < pRadarCfg->numRadars; chId++)
    {
        pRadarParams = &pRadarCfg->radarParams[chId];
        for (i = 0U; i < pRadarParams->numProfiles; i++)
        {
            nextPowerOf2 = pRadarParams->radarWidth[i];
            nextPowerOf2--;
            nextPowerOf2 |= nextPowerOf2 >> 1;
            nextPowerOf2 |= nextPowerOf2 >> 2;
            nextPowerOf2 |= nextPowerOf2 >> 4;
            nextPowerOf2 |= nextPowerOf2 >> 8;
            nextPowerOf2++;
            imgFrameWidth[i]  = pRadarParams->numRxAntenna[i] * nextPowerOf2;

            nextPowerOf2 = pRadarParams->radarHeight[i];
            nextPowerOf2--;
            nextPowerOf2 |= nextPowerOf2 >> 1;
            nextPowerOf2 |= nextPowerOf2 >> 2;
            nextPowerOf2 |= nextPowerOf2 >> 4;
            nextPowerOf2 |= nextPowerOf2 >> 8;
            nextPowerOf2++;
            imgFrameHeight[i] = nextPowerOf2 * pRadarParams->numTxAntenna[i];

            pObj->offsetBwAntennas[chId][0][i] = pRadarParams->offsetBwAntennas[i]; /* Number of Bytes */
            pObj->irregularityFrequency[chId][0][i] = pRadarParams->numRxAntenna[i] - 1;
            pObj->offsetBwAntennas1[chId][0][i] =
                SystemUtils_align(pRadarParams->csi2OutWidth*2, VPS_BUFFER_ALIGNMENT*2) -
                    (pRadarParams->numRxAntenna[i]-1) * pRadarParams->offsetBwAntennas[i]; /* Number of Bytes */
            pObj->offsetBwAntennas[chId][1][i] = pRadarParams->radarWidth[i] * sizeof(UInt32); /* Number of Bytes */
            pObj->irregularityFrequency[chId][1][i] = 0U;
            pObj->offsetBwAntennas1[chId][1][i] = 0U;
            if(pObj->algLinkCreateParams.algFFTMode == RADAR_FFT_MODE_HORZ_AND_VERT)
            {
                if (pObj->algLinkCreateParams.algCreatePrm[1].outputContainerFormat == FFT_TI_CONTAINER_FORMAT_32BIT)
                {
                    numBytesPerSample = sizeof(UInt64);
                }
                else
                {
                    numBytesPerSample = sizeof(UInt32);
                }
            }
            else
            {
                if (pObj->algLinkCreateParams.algCreatePrm[0].outputContainerFormat == FFT_TI_CONTAINER_FORMAT_32BIT)
                {
                    numBytesPerSample = sizeof(UInt64);
                }
                else
                {
                    numBytesPerSample = sizeof(UInt32);
                }
            }
            outputBufferpitch[i] = imgFrameWidth[i] * numBytesPerSample; /* Number of Bytes */
            pObj->numPoints[chId][i] = pRadarParams->radarWidth[i];
            pObj->numLines[chId][i] = pRadarParams->radarHeight[i];
            pObj->imgFrameWidth[chId][i] = imgFrameWidth[i];
            pObj->imgFrameHeight[chId][i] = imgFrameHeight[i];
            pObj->numAntennas[chId][i] = pRadarParams->numTxAntenna[i] * pRadarParams->numRxAntenna[i];
        }
        pObj->inBufAddrOffset[chId] = pRadarParams->inBufAddrOffset; /* Number of Bytes */
        pObj->numValidBits[chId] = pRadarParams->numValidBits;

        pOutChInfo          = &opParams->outputChannelInfo[chId];

        pOutChInfo->height = AlgorithmFxn_RadarFftFindMax(imgFrameHeight, pRadarParams->numProfiles);
        pOutChInfo->width  = AlgorithmFxn_RadarFftFindMax(imgFrameWidth, pRadarParams->numProfiles);
        pOutChInfo->startX = 0;
        pOutChInfo->startY = 0;
        pOutChInfo->flags  = 0;

        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Scan_Format(
                                                pOutChInfo->flags,
                                                SYSTEM_SF_PROGRESSIVE);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Mem_Type(
                                                pOutChInfo->flags,
                                                SYSTEM_MT_NONTILEDMEM);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Data_Format(
                                                pOutChInfo->flags,
                                                pObj->algLinkCreateParams.dataFormat);
        pOutChInfo->flags = System_Link_Ch_Info_Set_Flag_Buf_Type(
                                                pOutChInfo->flags,
                                                SYSTEM_BUFFER_TYPE_VIDEO_FRAME);

        pOutChInfo->pitch[0] = AlgorithmFxn_RadarFftFindMax(outputBufferpitch, pRadarParams->numProfiles);
        pOutChInfo->pitch[1] = pOutChInfo->pitch[0];
        pOutChInfo->pitch[2] = pOutChInfo->pitch[0];

        opParams->outputBufferSize[chId] = pOutChInfo->pitch[0] * pOutChInfo->height;
        opParams->metaBufSize[chId][0] = sizeof(AlgorithmFxn_RadarFftBuffDescriptor);
    }
    opParams->outputBufferType = SYSTEM_BUFFER_TYPE_VIDEO_FRAME;
    opParams->inputBufCacheOps = ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_NONE;
    opParams->outputBufCacheOps = ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_NONE;
    prevLinkQueId = createParams->inQueParams.prevLinkQueId;
    System_linkGetInfo(createParams->inQueParams.prevLinkId, &prevLinkInfo);
    opParams->numOutputCh = prevLinkInfo.queInfo[prevLinkQueId].numCh;


    if(pObj->algLinkCreateParams.algFFTMode == RADAR_FFT_MODE_HORZ_AND_VERT)
    {
        pObj->intermediateBufSize = AlgorithmFxn_RadarFftFindMax(opParams->outputBufferSize,
                                                             pRadarCfg->numRadars);
        if (pObj->algLinkCreateParams.algCreatePrm[1].outputContainerFormat == FFT_TI_CONTAINER_FORMAT_32BIT)
        {
            pObj->intermediateBufSize = pObj->intermediateBufSize/2U;
        }
        /* Allocate local buff for doppler mode */
        pObj->intermediateBuf = Utils_memAlloc (UTILS_HEAPID_DDR_CACHED_SR,
                                        pObj->intermediateBufSize,
                                        ALGORITHMLINK_FRAME_ALIGN);
        UTILS_assert(pObj->intermediateBuf != NULL);
    }

    /* Submit work to create algorithm */
    AlgorithmFxn_RadarFftDoWorkCreate(pObj);
    /* Setup algorithm process parameters */
    AlgorithmFxn_RadarFftSetAlgProcessParams(pObj);

    return (void *) pObj;
}
Int32 AlgorithmFxn_RadarFftProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarFftObj *pObj;
    System_VideoFrameBuffer  *pInputVideoBuffer;
    System_VideoFrameBuffer  *pOutputVideoBuffer;
    UInt8  *inBufAddr, *outBufAddr, *metaDataBuffAddr, *coeffAddr;
    AlgorithmFxn_RadarFftCreateParams *algLinkParams;
    UInt32 currProfile = 0U;
    UInt16 nextPowerOf2;
    UInt32 chId;

    pObj = (AlgorithmFxn_RadarFftObj *)alg_handle;

    pInputVideoBuffer   = (System_VideoFrameBuffer *)in_buf->payload;
    pOutputVideoBuffer  = (System_VideoFrameBuffer *)out_buf->payload;

    inBufAddr           = (UInt8 *)pInputVideoBuffer->bufAddr[0];
    outBufAddr          = (UInt8 *)pOutputVideoBuffer->bufAddr[0];
    metaDataBuffAddr    = (UInt8 *)pOutputVideoBuffer->metaBufAddr;

    chId = in_buf->chNum;
    algLinkParams = &pObj->algLinkCreateParams;

    if (( algLinkParams->algFFTMode == RADAR_FFT_MODE_HORIZONTAL ) ||
        ( algLinkParams->algFFTMode == RADAR_FFT_MODE_VERTICAL ))
    {
        pObj->pProcessInArgs->inAlgArgs[0].inBufs.bufDesc[FFT_TI_BUFDESC_IN_LISTBUFFER]->bufPlanes[0].buf =
            inBufAddr + pObj->inBufAddrOffset[chId];
        pObj->pProcessInArgs->inAlgArgs[0].outBufs.bufDesc[FFT_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf = outBufAddr;
        pObj->pProcessInArgs->inAlgArgs[0].outBufs.bufDesc[FFT_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].width = 0;
    }
    else if(algLinkParams->algFFTMode == RADAR_FFT_MODE_HORZ_AND_VERT)
    {
        pObj->pProcessInArgs->inAlgArgs[0].inBufs.bufDesc[FFT_TI_BUFDESC_IN_LISTBUFFER]->bufPlanes[0].buf =
            inBufAddr + pObj->inBufAddrOffset[chId];
        pObj->pProcessInArgs->inAlgArgs[0].outBufs.bufDesc[FFT_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf = pObj->intermediateBuf;
        pObj->pProcessInArgs->inAlgArgs[0].outBufs.bufDesc[FFT_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].width = 0;

        pObj->pProcessInArgs->inAlgArgs[1].inBufs.bufDesc[FFT_TI_BUFDESC_IN_LISTBUFFER]->bufPlanes[0].buf = pObj->intermediateBuf;
        pObj->pProcessInArgs->inAlgArgs[1].outBufs.bufDesc[FFT_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].buf = outBufAddr;
        pObj->pProcessInArgs->inAlgArgs[1].outBufs.bufDesc[FFT_TI_BUFDESC_OUT_BUFFER]->bufPlanes[0].width = 0;
    }
    if (pObj->inBufAddrOffset[chId] > 0U)
    {
        currProfile = ((*(UInt32*)inBufAddr) >> 2U) & 0xFU;
    }
    nextPowerOf2 = pObj->numPoints[chId][currProfile];
    nextPowerOf2--;
    nextPowerOf2 |= nextPowerOf2 >> 1;
    nextPowerOf2 |= nextPowerOf2 >> 2;
    nextPowerOf2 |= nextPowerOf2 >> 4;
    nextPowerOf2 |= nextPowerOf2 >> 8;
    nextPowerOf2++;
    switch(nextPowerOf2)
    {
        case FFT_TI_NUM_POINTS_1024: coeffAddr = (UInt8*) algLinkParams->algCreatePrm[0].windowCoeffAddr[RADAR_FFT_NUM_POINTS_1024]; break;
        case FFT_TI_NUM_POINTS_512: coeffAddr = (UInt8*) algLinkParams->algCreatePrm[0].windowCoeffAddr[RADAR_FFT_NUM_POINTS_512]; break;
        case FFT_TI_NUM_POINTS_256: coeffAddr = (UInt8*) algLinkParams->algCreatePrm[0].windowCoeffAddr[RADAR_FFT_NUM_POINTS_256]; break;
        case FFT_TI_NUM_POINTS_128: coeffAddr = (UInt8*) algLinkParams->algCreatePrm[0].windowCoeffAddr[RADAR_FFT_NUM_POINTS_128]; break;
        case FFT_TI_NUM_POINTS_64: coeffAddr = (UInt8*) algLinkParams->algCreatePrm[0].windowCoeffAddr[RADAR_FFT_NUM_POINTS_64]; break;
        default: coeffAddr = NULL;
    }
    pObj->pProcessInArgs->inAlgArgs[0].inBufs.bufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF]->bufPlanes[0].buf = coeffAddr;
    switch(pObj->numLines[chId][currProfile])
    {
        case FFT_TI_NUM_POINTS_1024: coeffAddr = (UInt8*) algLinkParams->algCreatePrm[1].windowCoeffAddr[RADAR_FFT_NUM_POINTS_1024]; break;
        case FFT_TI_NUM_POINTS_512: coeffAddr = (UInt8*) algLinkParams->algCreatePrm[1].windowCoeffAddr[RADAR_FFT_NUM_POINTS_512]; break;
        case FFT_TI_NUM_POINTS_256: coeffAddr = (UInt8*) algLinkParams->algCreatePrm[1].windowCoeffAddr[RADAR_FFT_NUM_POINTS_256]; break;
        case FFT_TI_NUM_POINTS_128: coeffAddr = (UInt8*) algLinkParams->algCreatePrm[1].windowCoeffAddr[RADAR_FFT_NUM_POINTS_128]; break;
        case FFT_TI_NUM_POINTS_64: coeffAddr = (UInt8*) algLinkParams->algCreatePrm[1].windowCoeffAddr[RADAR_FFT_NUM_POINTS_64]; break;
        default: coeffAddr = NULL;
    }
    pObj->pProcessInArgs->inAlgArgs[1].inBufs.bufDesc[FFT_TI_BUFDESC_IN_WINDOWING_COEFF_BUF]->bufPlanes[0].buf = coeffAddr;

    pObj->pProcessInArgs->inAlgArgs[0].inArgs.numPointsZeroPadding = nextPowerOf2 - pObj->numPoints[chId][currProfile];
    if ((pObj->pProcessInArgs->inAlgArgs[0].inArgs.numPointsZeroPadding % 8U) != 0U)
    {
        /* This is added as EVE FFT is found to hang or give incorrect output */
        Vps_printf(" ALG_FXN: RADARFFT: Zero Padding should be multiple of 8. Adjust range dimension to meet this!!\n\r");
        UTILS_assert(0);
    }
    pObj->pProcessInArgs->inAlgArgs[0].inArgs.bufDescription.numHorzPoints[0] = pObj->numPoints[chId][currProfile];
    pObj->pProcessInArgs->inAlgArgs[0].inArgs.bufDescription.numVertPoints = pObj->numLines[chId][currProfile];
    pObj->pProcessInArgs->inAlgArgs[0].inArgs.bufDescription.pitch[0] =
        pObj->offsetBwAntennas[chId][0][currProfile] * pObj->numAntennas[chId][currProfile];
    pObj->pProcessInArgs->inAlgArgs[0].inArgs.bufDescription.offsetBwAntennas[0] = pObj->offsetBwAntennas[chId][0][currProfile];
    pObj->pProcessInArgs->inAlgArgs[0].inArgs.bufDescription.irregularityFrequency = pObj->irregularityFrequency[chId][0][currProfile];
    pObj->pProcessInArgs->inAlgArgs[0].inArgs.bufDescription.offsetBwAntennas1[0] = pObj->offsetBwAntennas1[chId][0][currProfile];

    /* Additional inArgs not set in SetAlgProcessParams() */
    pObj->pProcessInArgs->inAlgArgs[0].inArgs.numValidBits = pObj->numValidBits[chId];
    pObj->pProcessInArgs->inAlgArgs[0].inArgs.bufDescription.numAntennas = pObj->numAntennas[chId][currProfile];
    if(algLinkParams->algFFTMode == RADAR_FFT_MODE_HORZ_AND_VERT)
    {
        pObj->pProcessInArgs->inAlgArgs[1].inArgs.numValidBits = pObj->numValidBits[chId];
        pObj->pProcessInArgs->inAlgArgs[1].inArgs.bufDescription.numAntennas = pObj->numAntennas[chId][currProfile];
    }

    status = AlgorithmFxn_RadarFftDoWorkProcess(pObj);

    if(status==SYSTEM_LINK_STATUS_SOK)
    {
        AlgorithmFxn_RadarFftBuffDescriptor * bufDesc =
            (AlgorithmFxn_RadarFftBuffDescriptor *) metaDataBuffAddr;
        memcpy(
                metaDataBuffAddr,
                &pObj->pProcessOutArgs->outArgs[
                        pObj->pProcessInArgs->numObjs-1].bufDescription,
                sizeof(FFT_TI_BufferDescriptor)
            );
        bufDesc->profileId = currProfile;
        pOutputVideoBuffer->chInfo.width = pObj->imgFrameWidth[chId][currProfile];
        pOutputVideoBuffer->chInfo.height = pObj->imgFrameHeight[chId][currProfile];
        BspOsal_cacheWbInv(
            metaDataBuffAddr,
            sizeof(AlgorithmFxn_RadarFftBuffDescriptor),
            BSP_OSAL_CT_ALLD, BSP_OSAL_WAIT_FOREVER);
    }

    return status;
}

Int32 AlgorithmFxn_RadarFftControl(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams)
{
    return SYSTEM_LINK_STATUS_SOK;
}

Int32 AlgorithmFxn_RadarFftDelete(void *alg_handle)
{
    UInt32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarFftObj *pObj;

    pObj = (AlgorithmFxn_RadarFftObj *)alg_handle;

    AlgorithmFxn_RadarFftDoWorkDelete(pObj);

    if(pObj->intermediateBuf != NULL)
    {
        Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                        pObj->intermediateBuf,
                        pObj->intermediateBufSize);
    }

    Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                  pObj,
                  sizeof(AlgorithmFxn_RadarFftObj)
                    );
    return status;
}
