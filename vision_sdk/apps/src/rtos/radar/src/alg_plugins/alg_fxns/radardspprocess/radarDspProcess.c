/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
******************************************************************************/

/**
 *******************************************************************************
 * \file radarDspProcess.c
 *
 * \brief  This file contains plug in functions for radar DSP based 2D FFT,
 *         Object detection and angle of arrival estimation.
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "c6x.h"
#include <include/link_api/algorithmLink.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <include/alglink_api/algorithmLink_radarProcess.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <include/alg_fxns/radarDspProcess_if.h>
#include <src/rtos/radar/src/alg_plugins/alg_fxns/radardspprocess/radarDspProcess_Priv.h>

static UInt32 AlgorithmFxn_RadarDspProcessFindNxtPower (UInt32 number);
static UInt32 AlgorithmFxn_RadarDspProcessFindMax(UInt16 *arr, UInt32 arrSize);
static Void AlgorithmFxn_RadarDspSetOpPointers(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    System_MetaDataBuffer *pOutputMetaDataBuffer);

/**
 *******************************************************************************
 * \brief   Global structure containing Algorithm Functions
 *******************************************************************************
 */
static AlgRadarProcessFxns_FxnTable gAlgorithmFxn_RadarDspProcess_fxns =
{
    &AlgorithmFxn_RadarDspProcessCreate,
    &AlgorithmFxn_RadarDspProcessProcess,
    &AlgorithmFxn_RadarDspProcessControlHandler,
    &AlgorithmFxn_RadarDspProcessDelete
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
AlgRadarProcessFxns_FxnTable *AlgorithmFxn_RadarDspProcess_getFunctions(void)
{
    return &gAlgorithmFxn_RadarDspProcess_fxns;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create Plugin for Radar DSP Process Algorithm
 *        Function.
 *
 * \param  createParams     [IN] Pointer to create time parameters
 * \param  opParams         [OUT] This is populated by the API to get nature
 *                                of the output generated by this algorithm
 *                                function.
 *
 * \return  Pointer to Handle for the Algorithm Function.
 *
 *******************************************************************************
 */
void * AlgorithmFxn_RadarDspProcessCreate(
    AlgorithmLink_RadarProcessCreateParams      *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams)
{
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams;
    System_LinkChInfo                        *pOutChInfo;
    AlgorithmFxn_RadarDspProcessObj          *pObj;
    UInt32                                   chId;
    UInt32                                   profId;
    UInt32                                   devId;
    UInt32                                   maxRangeBins,
                                             maxDopplerBins,
                                             maxVirtAntennas,
                                             maxNumVirtChirps;
    /* Get create parameter and cast it to DSP Process definition */
    pLinkCreateParams =
        (AlgorithmFxn_RadarDspProcessCreateParams *)createParams;

    /* Allocating data object to store DSP Process Algo internal info */
    pObj = (AlgorithmFxn_RadarDspProcessObj *)
                    Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_LOCAL,
                        sizeof(AlgorithmFxn_RadarDspProcessObj), 32);
    UTILS_assert(pObj != NULL);

    /*
     * Taking copy of needed create time parameters in local object for future
     * reference.
     */
    memcpy((void*)(&pObj->algLinkCreateParams),
            (void*)(pLinkCreateParams),
            sizeof(AlgorithmFxn_RadarDspProcessCreateParams));
    /* Perform Channel Wise parameter check and output buffer properties
     * calculation */
     maxRangeBins = 0U;
     maxDopplerBins = 0U;
     maxVirtAntennas = 0U;
     maxNumVirtChirps = 0U;
    for (chId = 0U; chId < pLinkCreateParams->numChannels; chId++)
    {
        UInt32 tempMax = 0U;
        /* Auto Derive the parameters based on input parameters
         * Additionally check the input parameters for sanity.
         */
        for (profId = 0U; profId < pLinkCreateParams->chCreateParams[chId].numProfiles;
             profId++)
        {
            UInt32 totalNumTx = 0U, totalNumRx = 0U;
            pObj->chObj[chId].numRangeBins[profId] = (UInt16)
                AlgorithmFxn_RadarDspProcessFindNxtPower (
                    (UInt32)pLinkCreateParams->chCreateParams[chId].
                    numAdcSamples[profId]);
            pObj->chObj[chId].numDopplerBins[profId] = (UInt16)
                AlgorithmFxn_RadarDspProcessFindNxtPower (
                    (UInt32)pLinkCreateParams->chCreateParams[chId].
                    numChirpLoops[profId]);
            for (devId = 0U;
            devId < pLinkCreateParams->chCreateParams[chId].numSensorDevPerChannel;
            devId++)
            {
                totalNumRx += (UInt32)pLinkCreateParams->chCreateParams[chId].
                                      numRxAnt[devId][profId];
                totalNumTx += (UInt32)pLinkCreateParams->chCreateParams[chId].
                                      numTxAnt[devId][profId];
            }
            if (maxNumVirtChirps < (pLinkCreateParams->chCreateParams[chId].
               numChirpLoops[profId]))
            {
                maxNumVirtChirps = pLinkCreateParams->chCreateParams[chId].
                                   numChirpLoops[profId];
            }
            pObj->chObj[chId].numVirtualAntenna[profId] =
                totalNumRx * totalNumTx;
            pObj->chObj[chId].totalNumTx[profId] = totalNumTx;
        }

        /* Fill the output buffer information */
        pOutChInfo          = &opParams->outputChannelInfo[chId];

        memset((void *)pOutChInfo, 0 , sizeof(pOutChInfo));

        opParams->outputBufferType = SYSTEM_BUFFER_TYPE_METADATA;
        opParams->numMetaDataPlanes = 1U;
        /* The maximum values for the profiles are already considered in
         * the size of the structure AlgorithmFxn_RadarDspProcessOutput.
         */
        opParams->metaBufSize[chId][0U] =
            sizeof (AlgorithmFxn_RadarDspProcessOutput);

        opParams->inputBufCacheOps = ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_INV;
        opParams->outputBufCacheOps = ALGORITHM_LINK_RADAR_PROCESS_CACHE_OPS_WB;
        opParams->numOutputCh = pLinkCreateParams->numChannels;
        /* Find the maximum range and Doppler Bin size. This is used for
         * memory allocation.
         */
        tempMax = AlgorithmFxn_RadarDspProcessFindMax(
                    pObj->chObj[chId].numRangeBins,
                    ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE);
        if (maxRangeBins < tempMax)
        {
            maxRangeBins = tempMax;
        }
        tempMax = AlgorithmFxn_RadarDspProcessFindMax(
                    pObj->chObj[chId].numDopplerBins,
                    ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE);
        if (maxDopplerBins < tempMax)
        {
            maxDopplerBins = tempMax;
        }
        tempMax = AlgorithmFxn_RadarDspProcessFindMax(
                    pObj->chObj[chId].numVirtualAntenna,
                    ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE);
        if (maxVirtAntennas < tempMax)
        {
            maxVirtAntennas = tempMax;
        }
    }
    pObj->maxRangeBins = maxRangeBins;
    pObj->maxDopplerBins = maxDopplerBins;
    pObj->maxNumVirtChirps = maxNumVirtChirps;
    pObj->maxNumVirtAnt = maxVirtAntennas;
    /* Memory Allocation for the internal temporary Buffers */
    /* Memory allocation for internal buffers */

    /* FFT 2D output */
    pObj->opBufSize2Dfft = maxRangeBins *
                           maxDopplerBins *
                           maxVirtAntennas *
                           sizeof(AlgorithmFxn_RadarDspProcessComplexNum);
    pObj->opBuf2Dfft = (AlgorithmFxn_RadarDspProcessComplexNum *)
                     Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                               pObj->opBufSize2Dfft,
                               8U);
    UTILS_assert(pObj->opBuf2Dfft != NULL);

    /* Energy Sum accross the antennas */
    pObj->opBufSizeEnergySum = maxRangeBins * maxDopplerBins * sizeof(float);
    pObj->opBufEnergySum = (float *)Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                                 pObj->opBufSizeEnergySum,
                                 128);
    UTILS_assert(pObj->opBufEnergySum  != NULL);

    /* Allocate memory to store CFAR output */
    pObj->opBufCFAR = (AlgorithmFxn_RadarDspProcessCFAROut *)
                        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
                        sizeof(AlgorithmFxn_RadarDspProcessCFAROut),
                        16);
    UTILS_assert(pObj->opBufCFAR != NULL);

    pObj->opBufSizeStaticHeatMap = (maxRangeBins)*( pLinkCreateParams->aoaCreateParams.azimuthFFTsize)*sizeof(float);

    pObj->opBufStaticHeatMap = (float *)
                            Utils_memAlloc(UTILS_HEAPID_DDR_CACHED_SR,
                            pObj->opBufSizeStaticHeatMap,
                            128);
   UTILS_assert(pObj->opBufStaticHeatMap != NULL);
    /* Create Individual Stages of the Algorithm */
    /* 2D FFT */
    AlgorithmFxn_RadarDspSecondDimFftCreate(pObj);
    /* CFAR */
    AlgorithmFxn_RadarDspCfarCreate(pObj);
    /* AoA */
    AlgorithmFxn_RadarDspAoaCreate(pObj);

    return (void *) pObj;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Process Plugin of the Algorithm Function
 *
 *        This function and the algorithm process function execute
 *        on same processor core. Hence processor gets
 *        locked with execution of the function, until completion. Only a
 *        link with higher priority can preempt this function execution.
 *
 * \param  alg_handle     [IN] Algorithm Function object handle
 * \param  in_buf         [IN] Input buffer from the previous Link
 * \param  out_buf        [IN] Output buffer to the next Link
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
volatile UInt64 timeStart, timeEnd;
volatile UInt64 fftTime[1024] = {0};
volatile UInt64 cfarTime [1024] = {0};
volatile UInt64 aoaTime [1024] = {0};
volatile UInt16 frameCount = 0U;
Int32 AlgorithmFxn_RadarDspProcessProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf)
{
    Int32                               status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarDspProcessObj     *pObj;
    System_VideoFrameCompositeBuffer    *pInputCompositeVideoBuffer;
    System_VideoFrameBuffer             *pSystemVideoFrameBufferInput;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams;
    System_MetaDataBuffer *pOutputMetaDataBuffer;
    AlgorithmFxn_RadarDspProcessComplexNum16bit *
        inBufAddr[ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_RADAR_SENSOR];
    AlgorithmFxn_RadarFftBuffDescriptor *
        metaDataBuffAddr[ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_RADAR_SENSOR];
    UInt32 numFrames;
    AlgorithmFxn_RadarDspProcessOpBufPointers * outputSectionPointers;
    AlgorithmFxn_RadarDspProcessOutput * opPtr;

    pObj = (AlgorithmFxn_RadarDspProcessObj *)alg_handle;
    pLinkCreateParams =
        (AlgorithmFxn_RadarDspProcessCreateParams *)&pObj->algLinkCreateParams;
    pOutputMetaDataBuffer  = (System_MetaDataBuffer *)(out_buf->payload);

    /* Prepare Input Buffer */
    if (pLinkCreateParams->inputBufferType ==
        SYSTEM_BUFFER_TYPE_VIDEO_FRAME_CONTAINER)
    {
        UInt32 frameIdx = 0U;
        pInputCompositeVideoBuffer =
            (System_VideoFrameCompositeBuffer *)in_buf->payload;
        numFrames = pInputCompositeVideoBuffer->numFrames;
        for (frameIdx = 0; frameIdx < numFrames; frameIdx++)
        {
            inBufAddr[frameIdx] =
                (AlgorithmFxn_RadarDspProcessComplexNum16bit*)
                pInputCompositeVideoBuffer->bufAddr[0][frameIdx];
            metaDataBuffAddr[frameIdx] =
                (AlgorithmFxn_RadarFftBuffDescriptor*)
                pInputCompositeVideoBuffer->metaBufAddr[frameIdx];
            UTILS_assert(inBufAddr[frameIdx] != NULL);
        }
    }
    else if (pLinkCreateParams->inputBufferType ==
        SYSTEM_BUFFER_TYPE_VIDEO_FRAME)
    {
        pSystemVideoFrameBufferInput =
            (System_VideoFrameBuffer *)in_buf->payload;
        numFrames = 1U;
        inBufAddr[0U] = (AlgorithmFxn_RadarDspProcessComplexNum16bit*)
                pSystemVideoFrameBufferInput->bufAddr[0U];
        metaDataBuffAddr[0U] =
                (AlgorithmFxn_RadarFftBuffDescriptor*)
                pSystemVideoFrameBufferInput->metaBufAddr;
    }
    /* Find the current profile and channel */
    pObj->currCh = in_buf->chNum;
    pObj->currProfile = metaDataBuffAddr[0U]->profileId;

    /* Prepare Output Buffer */
    AlgorithmFxn_RadarDspSetOpPointers(pObj, pOutputMetaDataBuffer);
    opPtr = (AlgorithmFxn_RadarDspProcessOutput *)
           pOutputMetaDataBuffer->bufAddr[0];
    opPtr->opHdr.frameId = in_buf->frameId;
    /* Perform Second Dimention Doppler FFT */
    timeStart = Utils_getCurTimeInUsec();
    if (pLinkCreateParams->skipDopplerFft == 0U)
    {
        AlgorithmFxn_RadarDspSecondDimFftProcess(pObj, inBufAddr,
            metaDataBuffAddr, numFrames);
    }
    else
    {
        AlgorithmFxn_RadarDspCalcEnergySum(pObj, (AlgorithmFxn_RadarDspProcessComplexNum **)inBufAddr,
             metaDataBuffAddr, numFrames);
    }
    /* Invalidate the detection matrix since it is copied through EDMA */
    Cache_inv (pObj->opBufEnergySum,
               sizeof(float) *
               pObj->chObj[pObj->currCh].numRangeBins[pObj->currProfile] *
               pObj->chObj[pObj->currCh].numDopplerBins[pObj->currProfile],
               Cache_Type_ALLD, TRUE);
    timeEnd = Utils_getCurTimeInUsec();
    fftTime[frameCount] = timeEnd - timeStart;
    timeStart = Utils_getCurTimeInUsec();
    /* Perform CFAR based object detection */
    AlgorithmFxn_RadarDspCfarProcess(pObj);
    timeEnd = Utils_getCurTimeInUsec();
    cfarTime[frameCount] = timeEnd - timeStart;
    timeStart = Utils_getCurTimeInUsec();
    /* Perform Angle of Arrival estimation */
    pObj->aoaObj.inputBuf =
        (AlgorithmFxn_RadarDspProcessComplexNum **) inBufAddr;
    pObj->aoaObj.bufDesc =
        (AlgorithmFxn_RadarFftBuffDescriptor **) metaDataBuffAddr;
    AlgorithmFxn_RadarDspAoaProcess(pObj);
    timeEnd = Utils_getCurTimeInUsec();
    aoaTime[frameCount] = timeEnd - timeStart;
    frameCount = (frameCount + 1) % 1024;
    /* Set frame number in output buffer */
    out_buf->frameId =  in_buf->frameId;
    outputSectionPointers = &pObj->opBufPointers;
    outputSectionPointers->pSystemInfo->rangeRes = pLinkCreateParams->
        chCreateParams[pObj->currCh].rangeRes[pObj->currProfile];
    outputSectionPointers->pSystemInfo->dopplerRes = pLinkCreateParams->
        chCreateParams[pObj->currCh].dopplerRes[pObj->currProfile];
    outputSectionPointers->pSystemInfo->numRangeBins = pObj->
        chObj[pObj->currCh].numRangeBins[pObj->currProfile];
    outputSectionPointers->pSystemInfo->numDopplerBins = pObj->
        chObj[pObj->currCh].numDopplerBins[pObj->currProfile];
    outputSectionPointers->pSystemInfo->numSensors = pLinkCreateParams->
        chCreateParams[pObj->currCh].numSensorDevPerChannel;
    outputSectionPointers->pSystemInfo->numTxAnt = pLinkCreateParams->
        chCreateParams[pObj->currCh].numTxAnt[0][pObj->currProfile];
    outputSectionPointers->pSystemInfo->numRxAnt = pLinkCreateParams->
        chCreateParams[pObj->currCh].numRxAnt[0][pObj->currProfile];

    if (pLinkCreateParams->opControlParams.pointCloud == (UInt8)1)
    {
        outputSectionPointers->pPointCloudSectionHeader->sectionLength =
            outputSectionPointers->pMsgHeader->objectCount *
            sizeof(AlgorithmFxn_RadarDspProcessOpCloudPoint);
        opPtr->opHdr.totalOutputSize = opPtr->opHdr.totalOutputSize +
            outputSectionPointers->pPointCloudSectionHeader->sectionLength +
            sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
    }
    if (pLinkCreateParams->opControlParams.rangeProfile == (UInt8)1)
    {
        memcpy(outputSectionPointers->pRangeProfile,
               pObj->opBufEnergySum, sizeof(float) *
               pObj->chObj[pObj->currCh].numRangeBins[pObj->currProfile]);
    }
    if (pLinkCreateParams->opControlParams.rangeDopHeatMap == (UInt8)1)
    {
        memcpy(outputSectionPointers->pRangeDopplerHeatmap,
               pObj->opBufEnergySum, sizeof(float) *
            pObj->chObj[pObj->currCh].numRangeBins[pObj->currProfile] *
            pObj->chObj[pObj->currCh].numDopplerBins[pObj->currProfile]);
    }
    if (pLinkCreateParams->opControlParams.azimuthHeatMap == (UInt8)1)
    {
        Int32 numDopplerBins =
            pObj->chObj[pObj->currCh].numDopplerBins[pObj->currProfile];
        Int32 numRangeBins =
            pObj->chObj[pObj->currCh].numRangeBins[pObj->currProfile];
        UInt32 writeStep =
            pObj->chObj[pObj->currCh].numVirtualAntenna[pObj->currProfile];

        Cache_inv ((void *) pObj->opBuf2Dfft,
                  numRangeBins * numDopplerBins *
                  sizeof(AlgorithmFxn_RadarDspProcessComplexNum) * writeStep,
                  Cache_Type_ALLD,
                  TRUE);

        /* Static Range-Azimuth Heat-map Generation  */
        AlgorithmFxn_RadarDspAoaProcessHeatMap(pObj, 0, pObj->opBufStaticHeatMap );
        memcpy(&(outputSectionPointers->pStaticAzimHeatmap[0]),
                pObj->opBufStaticHeatMap,
                pObj->opBufSizeStaticHeatMap);
    }
    pOutputMetaDataBuffer->metaFillLength[0] = opPtr->opHdr.totalOutputSize;
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Control function for the Algorithm Function
 *
 * \param  alg_handle     [IN] Algorithm Function object handle
 * \param  controlParams  [IN] Pointer to control parameters
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmFxn_RadarDspProcessControlHandler(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarDspProcessObj *pObj;
    AlgorithmLink_ControlParams * pAlgLinkControlPrm;
    AlgorithmFxn_RadarDspProcessControlParams *pControlPrms;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams;

    pObj = (AlgorithmFxn_RadarDspProcessObj *)alg_handle;
    pAlgLinkControlPrm = (AlgorithmLink_ControlParams *)controlParams;
    if(pAlgLinkControlPrm->size !=
        sizeof(AlgorithmFxn_RadarDspProcessControlParams))
    {
        status = SYSTEM_LINK_STATUS_EINVALID_PARAMS;
    }
    else
    {
        pControlPrms = (AlgorithmFxn_RadarDspProcessControlParams *)controlParams;
        switch(pControlPrms->dspControlCmd)
        {
            case ALGORITHM_FXN_RADAR_DSP_PROCESS_CMD_CHANGE_GUI:
            {
                Vps_printf(" RADAR DSP PROCESS: Changing the GUI parameters \n");
                pLinkCreateParams =
                (AlgorithmFxn_RadarDspProcessCreateParams *)&pObj->algLinkCreateParams;
                memcpy(&pLinkCreateParams->opControlParams, &pControlPrms->opControlParams,
                        sizeof(AlgorithmFxn_RadarDspProcessOpBlobControlParams));
                break;
            }
            case ALGORITHM_FXN_RADAR_DSP_PROCESS_CMD_RUN_CALIBRATION:
            {
                AlgorithmFxn_RadarDspAoaObj * pAoaObj = &pObj->aoaObj;
                Vps_printf(" RADAR DSP PROCESS: Enabling Calibration\n");
                pAoaObj->calibState.currState =
                    pControlPrms->calibParams.state;
                pAoaObj->calibState.currFrameCntr = 0U;
                memcpy (&pAoaObj->calibState.copyParams,
                    &pControlPrms->calibParams,
                sizeof(AlgorithmFxn_RadarDspProcessCalibParams));
                break;
            }
            default : status = SYSTEM_LINK_STATUS_EINVALID_PARAMS; break;
        }
    }
    return status;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete Function for the Algorithm Function
 *
 * \param  alg_handle     [IN] Algorithm Function object handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmFxn_RadarDspProcessDelete(void *alg_handle)
{
    UInt32 status = SYSTEM_LINK_STATUS_SOK;
    AlgorithmFxn_RadarDspProcessObj *pObj;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams;

    pObj = (AlgorithmFxn_RadarDspProcessObj *)alg_handle;
    pLinkCreateParams =
        (AlgorithmFxn_RadarDspProcessCreateParams *)&pObj->algLinkCreateParams;

    /* Delete Individual Stages of the Algorithm */
    /* AoA */
    AlgorithmFxn_RadarDspAoaDelete(pObj);
    /* CFAR */
    AlgorithmFxn_RadarDspCfarDelete(pObj);

    /* Free memory for internal buffers */
    if (pLinkCreateParams->skipDopplerFft == 0U)
    {
        /* 2D FFT */
        AlgorithmFxn_RadarDspSecondDimFftDelete(pObj);
        /* Free memory to store FFT 2D output */
        status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           pObj->opBuf2Dfft,
                           pObj->opBufSize2Dfft);
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    /* Free memory to store Energy Sum output */
    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           (Ptr) pObj->opBufEnergySum,
                           pObj->opBufSizeEnergySum);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_SR,
                           (Ptr) pObj->opBufStaticHeatMap,
                           pObj->opBufSizeStaticHeatMap);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    /* Free memory to store CFAR output */
    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                           (Ptr) pObj->opBufCFAR,
                           sizeof(AlgorithmFxn_RadarDspProcessCFAROut));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    /* Free DSP Data Processing object */
    status = Utils_memFree(UTILS_HEAPID_DDR_CACHED_LOCAL,
                           (Ptr) pObj,
                           sizeof(AlgorithmFxn_RadarDspProcessObj));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    return status;
}


static UInt32 AlgorithmFxn_RadarDspProcessFindNxtPower (UInt32 number)
{
    UInt32 nextPowerOf2 = number;
    nextPowerOf2--;
    nextPowerOf2 |= nextPowerOf2 >> 1;
    nextPowerOf2 |= nextPowerOf2 >> 2;
    nextPowerOf2 |= nextPowerOf2 >> 4;
    nextPowerOf2 |= nextPowerOf2 >> 8;
    nextPowerOf2++;
    return nextPowerOf2;
}

static UInt32 AlgorithmFxn_RadarDspProcessFindMax(UInt16 *arr, UInt32 arrSize)
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

static Void AlgorithmFxn_RadarDspSetOpPointers(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    System_MetaDataBuffer *pOutputMetaDataBuffer)
{
    AlgorithmFxn_RadarDspProcessOutput * opPtr;
    AlgorithmFxn_RadarDspProcessOpBufPointers * outputSectionPointers;
    UInt16 syncWord[4U] = {0x0102, 0x0304, 0x0506, 0x0708};
    UInt32 opBlobPtr;
    AlgorithmFxn_RadarDspProcessOpSectionHdr *sectionHeader;
    AlgorithmFxn_RadarDspAoaObj * pAoaObj = &pObj->aoaObj;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        &pObj->algLinkCreateParams;
    /* Prepare output buffer */
    opPtr = (AlgorithmFxn_RadarDspProcessOutput *)
        pOutputMetaDataBuffer->bufAddr[0];
    outputSectionPointers = &pObj->opBufPointers;
    /* Make note of the pointer */
    outputSectionPointers->pMsgHeader = &opPtr->opHdr;
    /* Prepare the top level header */
    memcpy(opPtr->opHdr.syncWord, syncWord, sizeof(syncWord));
    opPtr->opHdr.dspId = DNUM;
    opPtr->opHdr.numSections = 0;
    opPtr->opHdr.totalOutputSize = sizeof(AlgorithmFxn_RadarDspProcessOutputHeader);

    opBlobPtr = (UInt32) &opPtr->opBlob[0];
    /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_SYSTEM_INFO */
    sectionHeader = (AlgorithmFxn_RadarDspProcessOpSectionHdr *)opBlobPtr;
    sectionHeader->sectionType   = ALGORITHMFXN_RADAR_DSP_PROCESS_OP_SYSTEM_INFO;
    sectionHeader->sectionLength = sizeof(
        AlgorithmFxn_RadarDspProcessOpSystemInfo);
    opBlobPtr = opBlobPtr + sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
    /* Make note of the pointer */
    outputSectionPointers->pSystemInfo =
        (AlgorithmFxn_RadarDspProcessOpSystemInfo *)opBlobPtr;
    opBlobPtr = opBlobPtr + sectionHeader->sectionLength;
    opPtr->opHdr.numSections = opPtr->opHdr.numSections + 1;
    opPtr->opHdr.totalOutputSize = opPtr->opHdr.totalOutputSize +
                                   sectionHeader->sectionLength +
                                   sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
    /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_CALIBRATION_COEFFS */
    if(pAoaObj->calibState.currState ==
        ALGORITHMFXN_RADAR_DSP_PROCESS_CALIBRATION)
    {
        sectionHeader = (AlgorithmFxn_RadarDspProcessOpSectionHdr *)opBlobPtr;
        sectionHeader->sectionType   =
            ALGORITHMFXN_RADAR_DSP_PROCESS_OP_CALIBRATION_COEFFS;
        sectionHeader->sectionLength =
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum) *
            pObj->chObj[pObj->currCh].numVirtualAntenna[pObj->currProfile];
        opBlobPtr = opBlobPtr + sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
        /* Make note of the pointer */
        outputSectionPointers->pCalibrationCoefs =
            (AlgorithmFxn_RadarDspProcessComplexNum *)opBlobPtr;
        opBlobPtr = opBlobPtr + sectionHeader->sectionLength;
        opPtr->opHdr.numSections = opPtr->opHdr.numSections + 1;
        opPtr->opHdr.totalOutputSize = opPtr->opHdr.totalOutputSize +
                                   sectionHeader->sectionLength +
                                   sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
    }
    /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_RANGE_PROFILE */
    if (pLinkCreateParams->opControlParams.rangeProfile == (UInt8)1)
    {
        sectionHeader = (AlgorithmFxn_RadarDspProcessOpSectionHdr *)opBlobPtr;
        sectionHeader->sectionType   =
            ALGORITHMFXN_RADAR_DSP_PROCESS_OP_RANGE_PROFILE;
        sectionHeader->sectionLength =
            sizeof(float) *
            pObj->chObj[pObj->currCh].numRangeBins[pObj->currProfile];
        opBlobPtr = opBlobPtr + sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
        /* Make note of the pointer */
        outputSectionPointers->pRangeProfile = (float *)opBlobPtr;
        opBlobPtr = opBlobPtr + sectionHeader->sectionLength;
        opPtr->opHdr.numSections = opPtr->opHdr.numSections + 1;
        opPtr->opHdr.totalOutputSize = opPtr->opHdr.totalOutputSize +
                                   sectionHeader->sectionLength +
                                   sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
    }
    /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_RANGE_DOPPLER_HEAT_MAP */
    if (pLinkCreateParams->opControlParams.rangeDopHeatMap == (UInt8)1)
    {
        sectionHeader = (AlgorithmFxn_RadarDspProcessOpSectionHdr *)opBlobPtr;
        sectionHeader->sectionType   =
            ALGORITHMFXN_RADAR_DSP_PROCESS_OP_RANGE_DOPPLER_HEAT_MAP;
        sectionHeader->sectionLength =
            sizeof(float) *
            pObj->chObj[pObj->currCh].numRangeBins[pObj->currProfile] *
            pObj->chObj[pObj->currCh].numDopplerBins[pObj->currProfile];
        opBlobPtr = opBlobPtr + sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
        /* Make note of the pointer */
        outputSectionPointers->pRangeDopplerHeatmap = (float *)opBlobPtr;
        opBlobPtr = opBlobPtr + sectionHeader->sectionLength;
        opPtr->opHdr.numSections = opPtr->opHdr.numSections + 1;
        opPtr->opHdr.totalOutputSize = opPtr->opHdr.totalOutputSize +
                                   sectionHeader->sectionLength +
                                   sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
    }
    /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_AZIMUT_STATIC_HEAT_MAP */
    if (pLinkCreateParams->opControlParams.azimuthHeatMap == (UInt8)1)
    {
        sectionHeader = (AlgorithmFxn_RadarDspProcessOpSectionHdr *)opBlobPtr;
        sectionHeader->sectionType   =
            ALGORITHMFXN_RADAR_DSP_PROCESS_OP_AZIMUT_STATIC_HEAT_MAP;
        sectionHeader->sectionLength =
            sizeof(float) *
            pObj->chObj[pObj->currCh].numRangeBins[pObj->currProfile] *
            pLinkCreateParams->aoaCreateParams.azimuthFFTsize;
        opBlobPtr = opBlobPtr + sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
        /* Make note of the pointer */
        outputSectionPointers->pStaticAzimHeatmap =
            (float *)opBlobPtr;
        opBlobPtr = opBlobPtr + sectionHeader->sectionLength;
        opPtr->opHdr.numSections = opPtr->opHdr.numSections + 1;
        opPtr->opHdr.totalOutputSize = opPtr->opHdr.totalOutputSize +
                                   sectionHeader->sectionLength +
                                   sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
    }
    /* ALGORITHMFXN_RADAR_DSP_PROCESS_OP_DETECTED_POINTS */
    if (pLinkCreateParams->opControlParams.pointCloud == (UInt8)1)
    {
        sectionHeader = (AlgorithmFxn_RadarDspProcessOpSectionHdr *)opBlobPtr;
        sectionHeader->sectionType   =
            ALGORITHMFXN_RADAR_DSP_PROCESS_OP_DETECTED_POINTS;
        opBlobPtr = opBlobPtr + sizeof(AlgorithmFxn_RadarDspProcessOpSectionHdr);
        /* Make note of the pointer */
        outputSectionPointers->pPointCloud =
            (AlgorithmFxn_RadarDspProcessOpCloudPoint *)opBlobPtr;
        outputSectionPointers->pPointCloudSectionHeader = sectionHeader;
        opPtr->opHdr.numSections = opPtr->opHdr.numSections + 1;
    }
}
