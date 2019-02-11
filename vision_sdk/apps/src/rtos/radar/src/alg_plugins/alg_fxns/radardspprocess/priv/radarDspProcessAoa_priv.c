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

/**
 *******************************************************************************
 * \file radarDspProcessAoa_priv.c
 *
 * \brief  This file contains plug in functions for radar DSP based peak
 *         detection CFAR Processing.
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_mem.h>
#include <math.h>
#include <stdio.h>
#include "c6x.h"
#include <ti/dsplib/dsplib.h>
#include <ti/mathlib/mathlib.h>
#include <src/rtos/radar/src/alg_plugins/alg_fxns/radardspprocess/radarDspProcess_Priv.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define pi 3.141592654

/*******************************************************************************
 *  Algorithm Link Private Function Declaration
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspAoaGetAntennaData(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    UInt16 rangeIdx, UInt16 dopplerIdx);
static Void  AlgorithmFxn_RadarDspAoaConfigInpEdma(
    AlgorithmFxn_RadarDspProcessObj * pObj);

Void radarCascadeAoA_RxChPhaseMeasure (__float2_t * restrict xf,
                                       __float2_t * restrict chCompCoefs,
                                       UInt32 numVirtualAnt);
Void radarCascadeAoA_RxChPhaseMeasureIntInp (int64_t * restrict xf,
                                             __float2_t * restrict chCompCoefs,
                                             UInt32 numVirtualAnt);
Void radarCascadeAoA_mapSymbolsToAzimFftInput (
    AlgorithmFxn_RadarDspProcessObj *pObj, Int32 targetDopIdxSigned);
Void radarCascadeAoA_magSquare(
    AlgorithmFxn_RadarDspProcessComplexNum * restrict inBuf,
    float * restrict magSqBuf,
    UInt16 numPoints);
float radarCascadeAoA_singlePeakSearchMax(float * x,
                                          UInt16 numPoints);

Int32 EstimateExtendedVelocity(
    AlgorithmFxn_RadarDspProcessComplexNum *x2DFetched,
    AlgorithmFxn_RadarDspProcessComplexNum *rxChCompCoefs,
    UInt32 numDopBins,
    UInt32 numTxAnt,
    Int32 dopEstFftInd,
    Int32 numOverlapSymb,
    UInt32 *overlapAntennaPairs);
Int32 EstimateExtendedVelocityIntInp(
    AlgorithmFxn_RadarDspProcessComplexNum *x2DFetched,
    AlgorithmFxn_RadarDspProcessComplexNum *rxChCompCoefs,
    UInt32 numDopBins,
    UInt32 numTxAnt,
    Int32 dopEstFftInd,
    Int32 numOverlapSymb,
    UInt32 *overlapAntennaPairs);

Int16 radarCascadeAoA_singlePeakSearch(float * x,
                                        UInt16 numPoints);

Void radarCascadeAoA_mapSymbolsToElevFftInput (
    AlgorithmFxn_RadarDspProcessObj *pObj,
    UInt32 azimPeakPos);

/*******************************************************************************
 *  Algorithm Link Function Definition
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for the DSP Angle of Arrival.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None.
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspAoaCreate(AlgorithmFxn_RadarDspProcessObj *pObj)
{
    UInt32 numPingPongBuf = ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR;
    UInt32 i;
    AlgorithmFxn_RadarDspAoaObj * pAoaObj = &pObj->aoaObj;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        &pObj->algLinkCreateParams;
    pAoaObj->chanCompCoefs = (AlgorithmFxn_RadarDspProcessComplexNum *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pObj->maxNumVirtAnt *
        sizeof(AlgorithmFxn_RadarDspProcessComplexNum), 128U);
    UTILS_assert(pAoaObj->chanCompCoefs != NULL);

    for (i = 0; i < numPingPongBuf; i++)
    {
        pAoaObj->virtAntBuf[i] = (AlgorithmFxn_RadarDspProcessComplexNum *)
            Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pObj->maxNumVirtAnt *
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum),128U);
        UTILS_assert(pAoaObj->virtAntBuf[i] != NULL);
    }
    pAoaObj->writePingPongInd = ALG_FXN_RADAR_DSP_EDMA_PING_INDEX;
    pAoaObj->readPingPongInd = ALG_FXN_RADAR_DSP_EDMA_PING_INDEX;
    pAoaObj->azimFftInputBuf = (AlgorithmFxn_RadarDspProcessComplexNum *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
            pLinkCreateParams->aoaCreateParams.azimuthFFTsize *
            pLinkCreateParams->aoaCreateParams.numAzimuthFFTs *
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum),
            128U);
    UTILS_assert(pAoaObj->azimFftInputBuf != NULL);

    for (i = 0U; i < pLinkCreateParams->aoaCreateParams.numAzimuthFFTs; i++)
    {
        pAoaObj->azimFftOutputBuf[i] =
            (AlgorithmFxn_RadarDspProcessComplexNum *)
            Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
                pLinkCreateParams->aoaCreateParams.azimuthFFTsize *
                sizeof(AlgorithmFxn_RadarDspProcessComplexNum), 128U);
        UTILS_assert(pAoaObj->azimFftOutputBuf[i] != NULL);
    }

    pAoaObj->azimFftOutMagSquared = (float *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
            pLinkCreateParams->aoaCreateParams.azimuthFFTsize * sizeof(float),
            128U);
    UTILS_assert(pAoaObj->azimFftOutMagSquared != NULL);
    pAoaObj->azimFftOutPeakPosBuf = (UInt16 *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
            pLinkCreateParams->aoaCreateParams.azimuthFFTsize * sizeof(UInt16),
            128U);
    UTILS_assert(pAoaObj->azimFftOutPeakPosBuf != NULL);

    pAoaObj->elevFftInputBuf = (AlgorithmFxn_RadarDspProcessComplexNum *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
            pLinkCreateParams->aoaCreateParams.elevationFFTsize *
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum), 128U);
    UTILS_assert(pAoaObj->elevFftInputBuf != NULL);
    pAoaObj->elevFftOutputBuf = (AlgorithmFxn_RadarDspProcessComplexNum *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
            pLinkCreateParams->aoaCreateParams.elevationFFTsize *
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum), 128U);
    UTILS_assert(pAoaObj->elevFftOutputBuf != NULL);
    pAoaObj->elevOutputMagSquared = (float *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
            pLinkCreateParams->aoaCreateParams.elevationFFTsize * sizeof(float),
            128U);
    UTILS_assert(pAoaObj->elevOutputMagSquared != NULL);
    pAoaObj->twiddleAzimuth = (float *) Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
        2 * pLinkCreateParams->aoaCreateParams.azimuthFFTsize *
        sizeof(float), 128U);
    UTILS_assert(pAoaObj->twiddleAzimuth != NULL);
    gen_twiddle_fftSP(pAoaObj->twiddleAzimuth,
                      pLinkCreateParams->aoaCreateParams.azimuthFFTsize);
    pAoaObj->twiddleElevation = (float *) Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
        2 * pLinkCreateParams->aoaCreateParams.elevationFFTsize *
        sizeof(float), 128U);
    UTILS_assert(pAoaObj->twiddleElevation != NULL);
    gen_twiddle_fftSP(pAoaObj->twiddleElevation,
                      pLinkCreateParams->aoaCreateParams.elevationFFTsize);
    pAoaObj->edmaHandle = pObj->secondDimFftObj.edmaHandle;
    AlgorithmFxn_RadarDspAllocEdmaResource(pAoaObj->edmaHandle,
        &pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX], EDMA_INPUT_QUEUE_ID);
    AlgorithmFxn_RadarDspAllocEdmaResource(pAoaObj->edmaHandle,
        &pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX], EDMA_INPUT_QUEUE_ID);

    /* Initialize channel compensation. Copy to L2 RAM */
    for (i = 0; i < pObj->maxNumVirtAnt; i++)
    {
        pAoaObj->chanCompCoefs[i].real =
            pLinkCreateParams->aoaCreateParams.rxChPhaseComp[i].real;
        pAoaObj->chanCompCoefs[i].imag =
            pLinkCreateParams->aoaCreateParams.rxChPhaseComp[i].imag;
    }
    /* Initialize the calibration parameters */
    pAoaObj->calibState.currState =
        pLinkCreateParams->aoaCreateParams.calibParams.state;
    pAoaObj->calibState.currFrameCntr = 0U;
    memcpy (&pAoaObj->calibState.copyParams,
            &pLinkCreateParams->aoaCreateParams.calibParams,
            sizeof(AlgorithmFxn_RadarDspProcessCalibParams));
}

UInt16  radarCascadeAoA_multiPeakSearch(float * restrict x,
                                    UInt16 * peakIdxBuf,
                                    UInt16 numPoints,  /* Assume power of 2 */
                                    float thresholdScale)
{

    UInt16 numDetPeaks = 0;
    UInt32 i, iLeft, iRight;
    UInt32 mask = numPoints - 1;
    float maxPeakVal;
    float threshold;

    maxPeakVal = 0;
    #pragma MUST_ITERATE(2, ,2)
    for (i = 0; i < numPoints; i++)
    {
        if (x[i] > maxPeakVal)
        {
            maxPeakVal = x[i];
        }
    }

    threshold = maxPeakVal * thresholdScale;

    for (i = 0; i < numPoints; i++)
    {
        iLeft = (i - 1) & mask;
        iRight = (i + 1) & mask;

        if ((x[i] >= x[iLeft]) && (x[i] >= x[iRight]) && (x[i] > threshold))
        {
            peakIdxBuf[numDetPeaks] = i;
            numDetPeaks++;
        }
    }

    return numDetPeaks;
}

Void AlgorithmFxn_RadarDspAoaProcessHeatMap (AlgorithmFxn_RadarDspProcessObj * pObj,   UInt16 dopplerIndexProcess, float *outBuf)
{
    UInt32  rangeIdx;
    UInt32  currCh       = pObj->currCh;
    UInt32  currProfile  = pObj->currProfile;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
                                                    &pObj->algLinkCreateParams;
    AlgorithmFxn_RadarDspAoaObj * pAoaObj = &pObj->aoaObj;
    UInt32 azimuthFFTsize = pLinkCreateParams->aoaCreateParams.azimuthFFTsize;

    /* Run for all the range-bins */
    UInt32 numRangeBins = pObj->chObj[currCh].numRangeBins[currProfile];

    for (rangeIdx = 0; rangeIdx < numRangeBins; rangeIdx++)
    {

       AlgorithmFxn_RadarDspAoaGetAntennaData(pObj,
                                               rangeIdx,
                                               dopplerIndexProcess);

       radarCascadeAoA_mapSymbolsToAzimFftInput (pObj, dopplerIndexProcess);
       DSPF_sp_fftSPxSP(
                azimuthFFTsize,
                (float *) &pAoaObj->azimFftInputBuf[0],
                (float *) pAoaObj->twiddleAzimuth,
                (float *) pAoaObj->azimFftOutputBuf[0],
                0,
                2,
                0,
                azimuthFFTsize);

        radarCascadeAoA_magSquare(
                                  pAoaObj->azimFftOutputBuf[0],
                                  &(outBuf[rangeIdx*azimuthFFTsize]),
                                  azimuthFFTsize);
    }
}

Void AlgorithmFxn_RadarDspAoaProcess (AlgorithmFxn_RadarDspProcessObj * pObj)
{
    AlgorithmFxn_RadarDspProcessOutputHeader  *pMsgHeader;
    AlgorithmFxn_RadarDspProcessOpCloudPoint  *pPointCloud;
    UInt32  detObjIdx;
    UInt32  finalDetObjIdx;
    UInt32  rowIdx;
    UInt32  numAzimDetPeaks;
    UInt32  azimPeakIdx;
    Int16   elevPeakPos;
    Int16   azimuthPeakPos;
    Int32   targetDopIdxSigned;
    Int32   extVelocityOverlapAntInd;
    UInt32  calibRefTargetRangePos;
    UInt32  currCh       = pObj->currCh;
    UInt32  currProfile  = pObj->currProfile;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        &pObj->algLinkCreateParams;
    AlgorithmFxn_RadarDspAoaObj * pAoaObj = &pObj->aoaObj;
    UInt32 numVirtualAnt = pObj->chObj[currCh].numVirtualAntenna[currProfile];
    UInt32 numDopplerBins = pObj->chObj[currCh].numDopplerBins[currProfile];
    UInt32 numTxAnt = pLinkCreateParams->chCreateParams[currCh].
                                      numTxAnt[0][currProfile];
    UInt32 azimuthFFTsize = pLinkCreateParams->aoaCreateParams.azimuthFFTsize;
    UInt32 elevationFFTsize = pLinkCreateParams->aoaCreateParams.elevationFFTsize;
    float cosElevation;
    float tempVal;

    /* Configure the EDMA based on the input channel and the current profile */
    AlgorithmFxn_RadarDspAoaConfigInpEdma(pObj);
    /* Get pointers to the output buffer */
    pMsgHeader = pObj->opBufPointers.pMsgHeader;
    pPointCloud = pObj->opBufPointers.pPointCloud;
    /* Initialize the ping pong index */
    pAoaObj->readPingPongInd = ALG_FXN_RADAR_DSP_EDMA_PING_INDEX;
    pAoaObj->writePingPongInd = ALG_FXN_RADAR_DSP_EDMA_PING_INDEX;

    if (pObj->opBufCFAR->numObjDetected == 0U)
    {
        pMsgHeader->objectCount = 0;
        return;
    }

    AlgorithmFxn_RadarDspAoaGetAntennaData(pObj,
        pObj->opBufCFAR->rangeInd[0],
        pObj->opBufCFAR->dopplerInd[0]);

    if (pObj->opBufCFAR->numObjDetected > 1)
    {
        AlgorithmFxn_RadarDspAoaGetAntennaData(pObj,
            pObj->opBufCFAR->rangeInd[1],
            pObj->opBufCFAR->dopplerInd[1]);
    }

    /* Check for Calibration */
    if(pAoaObj->calibState.currState ==
        ALGORITHMFXN_RADAR_DSP_PROCESS_CALIBRATION)
    {
        /* Find target Peak position inside expected range */
        UInt32 i;
        UInt32 startInd =
            pAoaObj->calibState.copyParams.refTargetRangeWindowStart;
        UInt32 endInd   =
            pAoaObj->calibState.copyParams.refTargetRangeWindowEnd;
        float *rangeProfile     = pObj->opBufEnergySum;
        float rangeProfileMax   = rangeProfile[startInd];
        calibRefTargetRangePos  = startInd;

        for (i = startInd; i <= endInd; i++)
        {
            if (rangeProfile[i] > rangeProfileMax)
            {
                rangeProfileMax = rangeProfile[i];
                calibRefTargetRangePos = i;
            }
        }
    }

    finalDetObjIdx = 0;
    for (detObjIdx = 0; detObjIdx < pObj->opBufCFAR->numObjDetected; detObjIdx++)
    {
        AlgorithmFxn_RadarDspWaitUntilEdmaTransferDone(
                    pAoaObj->edmaHandle,
                    &pAoaObj->edmaRes[pAoaObj->readPingPongInd]);
        /* Check for Calibration */
        if(pAoaObj->calibState.currState ==
            ALGORITHMFXN_RADAR_DSP_PROCESS_CALIBRATION)
        {
            if ((pObj->opBufCFAR->rangeInd[detObjIdx] == calibRefTargetRangePos)
                && (pObj->opBufCFAR->dopplerInd[detObjIdx] == 0))
            {
                if (pLinkCreateParams->skipDopplerFft == 0U)
                {
                    radarCascadeAoA_RxChPhaseMeasure (
                        (__float2_t *) pAoaObj->virtAntBuf[pAoaObj->readPingPongInd],
                        (__float2_t *) pAoaObj->chanCompCoefs,
                        numVirtualAnt);
                }
                else
                {
                    radarCascadeAoA_RxChPhaseMeasureIntInp (
                        (int64_t *) pAoaObj->virtAntBuf[pAoaObj->readPingPongInd],
                        (__float2_t *) pAoaObj->chanCompCoefs,
                        numVirtualAnt);
                }
            }
        }
        if (pObj->opBufCFAR->dopplerInd[detObjIdx] < numDopplerBins/2)
        {
            targetDopIdxSigned = pObj->opBufCFAR->dopplerInd[detObjIdx];
        }
        else
        {
            targetDopIdxSigned =
                ((Int32) pObj->opBufCFAR->dopplerInd[detObjIdx]) -
                ((Int32) numDopplerBins);
        }

        /* Extended Velocity */
        if (pLinkCreateParams->aoaCreateParams.enableExtendedMaxVelocity == 1U)
        {
            Int32 targetDopIndHypotheses
                    [ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_NUM_TX_ANTENNA];
            float fftOutPeaks
                    [ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_NUM_TX_ANTENNA];
            Int32 i;
            Int32 offs;
            float fftOutMaxPeak;
            Int32 fftOutMaxPeakInd;
            if (numTxAnt & 0x1 == 0x1)
            {
                offs = -((Int32) numTxAnt)/2;
            }
            else
            {
                if (targetDopIdxSigned > 0)
                {
                    offs = -((Int32) numTxAnt)/2;
                }
                else
                {
                    offs = -((Int32) numTxAnt)/2 + 1;
                }
            }
            for (i = 0; i < numTxAnt; i++)
            {
                targetDopIndHypotheses[i] =
                    targetDopIdxSigned + offs * numDopplerBins;
                offs++;
            }

            for (i = 0; i < numTxAnt; i++)
            {
                radarCascadeAoA_mapSymbolsToAzimFftInput (pObj, targetDopIndHypotheses[i]);

                /* Only FFT of row=0 ie rxMainRowIndex*/
                DSPF_sp_fftSPxSP(azimuthFFTsize,
                    (float *) &pAoaObj->azimFftInputBuf[
                        pLinkCreateParams->aoaCreateParams.rxMainRowIndex *
                        azimuthFFTsize],
                    (float *) pAoaObj->twiddleAzimuth,
                    (float *) pAoaObj->azimFftOutputBuf[
                        pLinkCreateParams->aoaCreateParams.rxMainRowIndex],
                    0,
                    2,
                    0,
                    azimuthFFTsize);

                radarCascadeAoA_magSquare(
                    pAoaObj->azimFftOutputBuf[
                        pLinkCreateParams->aoaCreateParams.rxMainRowIndex],
                    pAoaObj->azimFftOutMagSquared, azimuthFFTsize);

                fftOutPeaks[i] = radarCascadeAoA_singlePeakSearchMax(
                    pAoaObj->azimFftOutMagSquared, azimuthFFTsize);
            }

            fftOutMaxPeakInd = 0;
            fftOutMaxPeak = fftOutPeaks[fftOutMaxPeakInd];
            for (i = 1; i < numTxAnt; i++)
            {
                if (fftOutPeaks[i] > fftOutMaxPeak)
                {
                    fftOutMaxPeak = fftOutPeaks[i];
                    fftOutMaxPeakInd = i;
                }
            }
            /* Estimated extended Velocity/Doppler index*/
            targetDopIdxSigned = targetDopIndHypotheses[fftOutMaxPeakInd];
        }
        if (pLinkCreateParams->aoaCreateParams.enableExtendedMaxVelocity == 2)
        {
            /* Estimate extended velocity based on overlapped antenna symbols */
            if (pLinkCreateParams->skipDopplerFft == 0U)
            {
                extVelocityOverlapAntInd = EstimateExtendedVelocity(
                    pAoaObj->virtAntBuf[pAoaObj->readPingPongInd],
                    pAoaObj->chanCompCoefs,
                    numDopplerBins,
                    numTxAnt,
                    pObj->opBufCFAR->dopplerInd[detObjIdx],
                    /* Unsigned doppler index based on 2D FFT */
                    pLinkCreateParams->aoaCreateParams.numOverlapAntennaPairs,
                    pLinkCreateParams->aoaCreateParams.overlapAntennaPairs);
            }
            else
            {
                extVelocityOverlapAntInd = EstimateExtendedVelocityIntInp(
                    pAoaObj->virtAntBuf[pAoaObj->readPingPongInd],
                    pAoaObj->chanCompCoefs,
                    numDopplerBins,
                    numTxAnt,
                    pObj->opBufCFAR->dopplerInd[detObjIdx],
                    /* Unsigned doppler index based on 2D FFT */
                    pLinkCreateParams->aoaCreateParams.numOverlapAntennaPairs,
                    pLinkCreateParams->aoaCreateParams.overlapAntennaPairs);
            }
            targetDopIdxSigned = extVelocityOverlapAntInd;
        }

        /* Do mapping again using extended Doppler index- need to optimize this code */
        radarCascadeAoA_mapSymbolsToAzimFftInput (pObj, targetDopIdxSigned);

        for (rowIdx = 0;
            rowIdx < pLinkCreateParams->aoaCreateParams.numAzimuthFFTs;
            rowIdx++)
        {
            DSPF_sp_fftSPxSP(azimuthFFTsize,
                (float *) &pAoaObj->azimFftInputBuf[
                    rowIdx * azimuthFFTsize],
                (float *) pAoaObj->twiddleAzimuth,
                (float *) pAoaObj->azimFftOutputBuf[rowIdx],
                0,
                2,
                0,
                azimuthFFTsize);
        }

        radarCascadeAoA_magSquare(
            pAoaObj->azimFftOutputBuf[
                pLinkCreateParams->aoaCreateParams.rxMainRowIndex],
            pAoaObj->azimFftOutMagSquared, azimuthFFTsize);

        numAzimDetPeaks = radarCascadeAoA_multiPeakSearch(
            pAoaObj->azimFftOutMagSquared,
            pAoaObj->azimFftOutPeakPosBuf, azimuthFFTsize,
            pLinkCreateParams->aoaCreateParams.multiPeakThresholdScale);

        for (azimPeakIdx = 0; azimPeakIdx < numAzimDetPeaks; azimPeakIdx++)
        {
            pPointCloud[finalDetObjIdx].rangeInd =
                pObj->opBufCFAR->rangeInd[detObjIdx];
            pPointCloud[finalDetObjIdx].dopplerInd =
                (Int16) targetDopIdxSigned;
            pPointCloud[finalDetObjIdx].range =
                pObj->opBufCFAR->rangeEst[detObjIdx];
            pPointCloud[finalDetObjIdx].doppler =
                targetDopIdxSigned * pLinkCreateParams->chCreateParams[currCh].
                    dopplerRes[currProfile];
            pPointCloud[finalDetObjIdx].snr =
                pObj->opBufCFAR->snrEst[detObjIdx];
            azimuthPeakPos = pAoaObj->azimFftOutPeakPosBuf[azimPeakIdx];
            if (azimuthPeakPos >= (azimuthFFTsize >> 1))
            {
                azimuthPeakPos -= azimuthFFTsize;
            }
            pPointCloud[finalDetObjIdx].azimuthAngleInd = azimuthPeakPos;

            /* Elevation */
            radarCascadeAoA_mapSymbolsToElevFftInput(pObj,
                pAoaObj->azimFftOutPeakPosBuf[azimPeakIdx]);

            DSPF_sp_fftSPxSP(
                elevationFFTsize,
                (float *) pAoaObj->elevFftInputBuf,
                (float *) pAoaObj->twiddleElevation,
                (float *) pAoaObj->elevFftOutputBuf,
                0,
                2,
                0,
                elevationFFTsize);

            radarCascadeAoA_magSquare(pAoaObj->elevFftOutputBuf,
                pAoaObj->elevOutputMagSquared, elevationFFTsize);

            elevPeakPos = radarCascadeAoA_singlePeakSearch(
                pAoaObj->elevOutputMagSquared, elevationFFTsize);

            if (elevPeakPos >= (elevationFFTsize >> 1))
            {
                elevPeakPos -= elevationFFTsize;
            }
            pPointCloud[finalDetObjIdx].elevationAngleInd = elevPeakPos;

            pPointCloud[finalDetObjIdx].elevationAngle =
                    asinsp_i(divsp_i(2.0 * elevPeakPos, elevationFFTsize));
            cosElevation = cossp_i(pPointCloud[finalDetObjIdx].elevationAngle);
            tempVal = divsp_i(
                2.0 * azimuthPeakPos, azimuthFFTsize * cosElevation);
            if (tempVal > 1.0)
            {
                tempVal = 1.0;
            }
            if (tempVal < -1.0)
            {
                tempVal = -1.0;
            }
            pPointCloud[finalDetObjIdx].azimuthAngle = -asinsp_i(tempVal);
            finalDetObjIdx++;
        }

        if ((detObjIdx+2) < pObj->opBufCFAR->numObjDetected)
        {
            AlgorithmFxn_RadarDspAoaGetAntennaData(
                pObj,
                pObj->opBufCFAR->rangeInd[detObjIdx+2],
                pObj->opBufCFAR->dopplerInd[detObjIdx+2]);
        }

        pAoaObj->readPingPongInd ^= 1;
    }
    pMsgHeader->objectCount = finalDetObjIdx;

    /* Check for end of Calibration if it was enabled */
    if(pAoaObj->calibState.currState ==
        ALGORITHMFXN_RADAR_DSP_PROCESS_CALIBRATION)
    {
        /*Copy coeficients to output*/
        memcpy(pObj->opBufPointers.pCalibrationCoefs,
               pAoaObj->chanCompCoefs,
               numVirtualAnt * sizeof(AlgorithmFxn_RadarDspProcessComplexNum));

        pAoaObj->calibState.currFrameCntr++;
        if (pAoaObj->calibState.currFrameCntr ==
            pAoaObj->calibState.copyParams.numFrames)
        {
            Vps_printf(" RADAR DSP PROCESS: Calibration Complete\n");
            pAoaObj->calibState.currState =
                ALGORITHMFXN_RADAR_DSP_PROCESS_NORMAL_RUNNING;
        }
    }
}

Void AlgorithmFxn_RadarDspAoaDelete(AlgorithmFxn_RadarDspProcessObj *pObj)
{
    UInt32 i;
    AlgorithmFxn_RadarDspAoaObj * pAoaObj = &pObj->aoaObj;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        &pObj->algLinkCreateParams;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->chanCompCoefs, pObj->maxNumVirtAnt *
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (i = 0; i < ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR; i++)
    {
        status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->virtAntBuf[i], pObj->maxNumVirtAnt *
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }
    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->azimFftInputBuf,
            pLinkCreateParams->aoaCreateParams.azimuthFFTsize *
            pLinkCreateParams->aoaCreateParams.numAzimuthFFTs *
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    for (i = 0U; i < pLinkCreateParams->aoaCreateParams.numAzimuthFFTs; i++)
    {
        status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->azimFftOutputBuf[i],
            pLinkCreateParams->aoaCreateParams.azimuthFFTsize *
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum));
        UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    }

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->azimFftOutMagSquared,
            pLinkCreateParams->aoaCreateParams.azimuthFFTsize * sizeof(float));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->azimFftOutPeakPosBuf,
            pLinkCreateParams->aoaCreateParams.azimuthFFTsize * sizeof(UInt16));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->elevFftInputBuf,
            pLinkCreateParams->aoaCreateParams.elevationFFTsize *
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum));
    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->elevFftOutputBuf,
            pLinkCreateParams->aoaCreateParams.elevationFFTsize *
            sizeof(AlgorithmFxn_RadarDspProcessComplexNum));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->elevOutputMagSquared,
            pLinkCreateParams->aoaCreateParams.elevationFFTsize * sizeof(float));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->twiddleAzimuth,
            2 * pLinkCreateParams->aoaCreateParams.azimuthFFTsize *
            sizeof(float));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
            pAoaObj->twiddleElevation,
            2 * pLinkCreateParams->aoaCreateParams.elevationFFTsize *
            sizeof(float));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    AlgorithmFxn_RadarDspDeallocEdmaResource(pAoaObj->edmaHandle,
        &pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX]);
    AlgorithmFxn_RadarDspDeallocEdmaResource(pAoaObj->edmaHandle,
        &pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX]);
}

/******************************************************************************
 *  Internal Functions
******************************************************************************/
/**
 *******************************************************************************
 *
 * \brief Implementation of Config function for the DSP Angle of Arrival
 *        Input EDMA.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void  AlgorithmFxn_RadarDspAoaConfigInpEdma(
    AlgorithmFxn_RadarDspProcessObj* pObj)
{
    AlgorithmFxn_RadarDspAoaObj * pAoaObj = &pObj->aoaObj;
    EDMA3_DRV_PaRAMRegs *pParamSetPing, *pParamSetShadowPing;
    EDMA3_DRV_PaRAMRegs *pParamSetPong, *pParamSetShadowPong;
    UInt32 currCh = pObj->currCh;
    UInt32 currProfile = pObj->currProfile;
    UInt32 bytesPerSample = sizeof(AlgorithmFxn_RadarDspProcessComplexNum);
    UInt32 opt = 0U;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        (AlgorithmFxn_RadarDspProcessCreateParams *)&pObj->algLinkCreateParams;
    /* Assume there is a single frame with a single chunk after 2D FFT */
    const UInt32 frameIdx = 0U;
    const UInt32 chunkIndx = 0U;

    /* Config Ping EDMA param set and shadow param set */
    pParamSetPing =
        pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].pChParamRegs;
    memset(pParamSetPing, 0, sizeof(EDMA3_DRV_PaRAMRegs));
    pParamSetPing->opt      = 0;
    pParamSetPing->aCnt     = bytesPerSample;
    if (pLinkCreateParams->skipDopplerFft == 0U)
    {
        pParamSetPing->bCnt = pObj->chObj[currCh].numVirtualAntenna[currProfile];
        pParamSetPing->srcBIdx  =
            pObj->chObj[currCh].numDopplerBins[currProfile] *
            pParamSetPing->aCnt;
    }
    else
    {
        AlgorithmFxn_RadarFftBuffDescriptor **bufDesc;
        UInt32 numHorzPoints;
        /* Number of virtual antennas per sensor */
        pParamSetPing->bCnt =
            pObj->chObj[currCh].totalNumTx[currProfile] *
            pLinkCreateParams->chCreateParams[currCh].numRxAnt[0U][currProfile];
        bufDesc  = pAoaObj->bufDesc;
        numHorzPoints = bufDesc[frameIdx]->bufDesc.numHorzPoints[chunkIndx];
        pParamSetPing->srcBIdx  = numHorzPoints * pParamSetPing->aCnt;
    }
    pParamSetPing->cCnt     = 1U;
    pParamSetPing->destBIdx = pParamSetPing->aCnt;
    opt  = (EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT);
    /* enable interrupt for last Transfer ONLY */
    opt |= (UInt32)((UInt32)EDMA3_CCRL_OPT_TCINTEN_ENABLE
                << EDMA3_CCRL_OPT_TCINTEN_SHIFT);
    pParamSetPing->opt = opt | ((pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].tccId <<
                EDMA3_CCRL_OPT_TCC_SHIFT) & EDMA3_CCRL_OPT_TCC_MASK);
    pParamSetPing->destAddr   = (UInt32)
        pAoaObj->virtAntBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX];
    pParamSetPing->linkAddr   = (UInt32)((UInt32)
            pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].pShadowParamRegs &
            0x3FFFU);
    /* Shadow copy */
    pParamSetShadowPing = pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].
        pShadowParamRegs;
    /* For Ping Buffer copy the shadow parameter as well. */
    memcpy(pParamSetShadowPing, pParamSetPing, sizeof(EDMA3_DRV_PaRAMRegs));

    /* Config Resource1 Pong EDMA param set and shadow param set */
    pParamSetPong =
        pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].
        pChParamRegs;
    memcpy(pParamSetPong, pParamSetPing, sizeof(EDMA3_DRV_PaRAMRegs));
    pParamSetPong->destAddr =
        (UInt32) pAoaObj->virtAntBuf[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX];
    pParamSetPong->linkAddr   = (UInt32)((UInt32)
        pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].pShadowParamRegs &
        0x3FFFU);
    pParamSetPong->opt = opt | ((pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].tccId <<
                    EDMA3_CCRL_OPT_TCC_SHIFT) & EDMA3_CCRL_OPT_TCC_MASK);
    /* Shadow copy */
    pParamSetShadowPong =
        pAoaObj->edmaRes[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].
        pShadowParamRegs;
    /* For Pong Buffer copy the shadow parameter as well. */
    memcpy(pParamSetShadowPong, pParamSetPong, sizeof(EDMA3_DRV_PaRAMRegs));
}
/**
 *******************************************************************************
 *
 * \brief Implementation of edma trigger to fetch the antenna data
 *
 * \param  pObj         [IN] Radar DSP Process Object
 * \param  rangeIdx     [IN] Range index of the detected object
 * \param  dopplerIdx   [IN] Doppler index of the detected object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspAoaGetAntennaData(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    UInt16 rangeIdx, UInt16 dopplerIdx)
{
    AlgorithmFxn_RadarDspAoaObj * pAoaObj = &pObj->aoaObj;
    UInt32 currCh = pObj->currCh;
    UInt32 currProfile = pObj->currProfile;
    UInt32 numDopplerBins = pObj->chObj[currCh].numDopplerBins[currProfile];
    UInt32 numVirtualAnt = pObj->chObj[currCh].numVirtualAntenna[currProfile];
    UInt32 srcOffs, destOffs;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams;
    AlgorithmFxn_RadarFftBuffDescriptor **bufDesc;
    AlgorithmFxn_RadarDspProcessComplexNum *inputBuf;
    /* Assume there is a single frame with a single chunk after 2D FFT */
    const UInt32 frameIdx = 0U;
    const UInt32 chunkIndx = 0U;
    AlgorithmFxn_RadarDspEdmaResource *edmaRes;

    pLinkCreateParams =
        (AlgorithmFxn_RadarDspProcessCreateParams *)&pObj->algLinkCreateParams;
    edmaRes = &pAoaObj->edmaRes[pAoaObj->writePingPongInd];
    if (pLinkCreateParams->skipDopplerFft == 0U)
    {
        srcOffs = rangeIdx * (numDopplerBins * numVirtualAnt) + dopplerIdx;
        AlgorithmFxn_RadarDspSetSourceAddress(edmaRes,
            (UInt32)&pObj->opBuf2Dfft[srcOffs]);
    }
    else
    {
        UInt32 numHorzPoints, pitch, sensorIndx;
        bufDesc  = pAoaObj->bufDesc;
        pitch = bufDesc[frameIdx]->bufDesc.pitch[chunkIndx];
        numHorzPoints = bufDesc[frameIdx]->bufDesc.numHorzPoints[chunkIndx];
        srcOffs  = ((rangeIdx % numHorzPoints) *
                    sizeof(AlgorithmFxn_RadarDspProcessComplexNum)) +
                   ((((rangeIdx / numHorzPoints) * numDopplerBins)
                      + dopplerIdx) * pitch);
        destOffs = edmaRes->pChParamRegs->bCnt * edmaRes->pChParamRegs->aCnt;
        for(sensorIndx = 0U; sensorIndx <
            (pLinkCreateParams->chCreateParams[currCh].numSensorDevPerChannel - 1U);
            sensorIndx++)
        {
            inputBuf = pAoaObj->inputBuf[sensorIndx];
            AlgorithmFxn_RadarDspSetSourceAddress(edmaRes,
                (UInt32)inputBuf + srcOffs);
            AlgorithmFxn_RadarDspSetDestinationAddress(edmaRes,
                (UInt32) pAoaObj->virtAntBuf[pAoaObj->writePingPongInd]
                + destOffs * sensorIndx);
            AlgorithmFxn_RadarDspStartEdmaTransfer(
                pAoaObj->edmaHandle, edmaRes);
            AlgorithmFxn_RadarDspWaitUntilEdmaTransferDone(pAoaObj->edmaHandle,
                edmaRes);
        }
        inputBuf = pAoaObj->inputBuf[sensorIndx];
        AlgorithmFxn_RadarDspSetSourceAddress(edmaRes,
            (UInt32)inputBuf + srcOffs);
        AlgorithmFxn_RadarDspSetDestinationAddress(edmaRes,
            (UInt32) pAoaObj->virtAntBuf[pAoaObj->writePingPongInd]
            + destOffs * sensorIndx);
    }
    AlgorithmFxn_RadarDspStartEdmaTransfer(pAoaObj->edmaHandle, edmaRes);
    pAoaObj->writePingPongInd ^= 1;
}

/******************************************************************************
 *  Algorithm Specific Functions - To be linked to libraries
******************************************************************************/

Void radarCascadeAoA_RxChPhaseMeasure (__float2_t * restrict xf,
                                       __float2_t * restrict chCompCoefs,
                                       UInt32 numVirtualAnt)
{
    UInt32 i;
    __float2_t x;
    __float2_t coef;
    __float2_t magMean2;
    __float2_t b;
    float magSqMean;
    float magSq, recMagSq;
    float magMean;

    /* Calculate reciprocal of magnitude square of each antenna and find mean
     * magnitude square*/
    magSqMean = 0.0;
    for (i = 0; i < numVirtualAnt; i++)
    {
        x = _amem8_f2(&xf[i]);
        b = _dmpysp(x, x);
        magSq = _hif2(b) + _lof2(b);
        recMagSq = divsp_i(1.0, magSq);
        magSqMean += magSq;
        _amem8_f2(&chCompCoefs[i]) = _fdmv_f2(recMagSq, recMagSq);
    }
    magSqMean = divsp_i(magSqMean, (float) numVirtualAnt);
    magMean = sqrtsp(magSqMean);
    magMean2 = _fdmv_f2(magMean, magMean);

    for (i = 0; i < numVirtualAnt; i++)
    {
        x = _amem8_f2(&xf[i]);
        x = _fdmv_f2(_lof2(x), _hif2(x));
        coef = _amem8_f2(&chCompCoefs[i]);
        coef = _dmpysp(x, coef);
        coef = _dmpysp(coef, magMean2);
        _amem8_f2(&chCompCoefs[i]) =  coef;
    }
}

Void radarCascadeAoA_RxChPhaseMeasureIntInp (int64_t * restrict xf,
                                             __float2_t * restrict chCompCoefs,
                                             UInt32 numVirtualAnt)
{
    UInt32 i;
    int64_t x_temp;
    __float2_t x;
    __float2_t coef;
    __float2_t magMean2;
    __float2_t b;
    float magSqMean;
    float magSq, recMagSq;
    float magMean;

    /* Calculate reciprocal of magnitude square of each antenna and find mean
     * magnitude square*/
    magSqMean = 0.0;
    #pragma MUST_ITERATE(2, ,2)
    for (i = 0; i < numVirtualAnt; i++)
    {
        x_temp = _amem8(&xf[i]);
        x = _dintsp(x_temp);
        b = _dmpysp(x, x);
        magSq = _hif2(b) + _lof2(b);
        recMagSq = divsp_i(1.0, magSq);
        magSqMean += magSq;
        _amem8_f2(&chCompCoefs[i]) = _fdmv_f2(recMagSq, recMagSq);
    }
    magSqMean = divsp_i(magSqMean, (float) numVirtualAnt);
    magMean = sqrtsp(magSqMean);
    magMean2 = _fdmv_f2(magMean, magMean);
    #pragma MUST_ITERATE(2, ,2)
    for (i = 0; i < numVirtualAnt; i++)
    {
        x_temp = _amem8(&xf[i]);
        x = _dintsp(x_temp);
        x = _fdmv_f2(_lof2(x), _hif2(x));
        coef = _amem8_f2(&chCompCoefs[i]);
        coef = _dmpysp(x, coef);
        coef = _dmpysp(coef, magMean2);
        _amem8_f2(&chCompCoefs[i]) =  coef;
    }
}

Void radarCascadeAoA_mapSymbolsToAzimFftInput (
    AlgorithmFxn_RadarDspProcessObj *pObj, Int32 targetDopIdxSigned)
{
    AlgorithmFxn_RadarDspAoaObj * pAoaObj = &pObj->aoaObj;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        &pObj->algLinkCreateParams;
    UInt32 currCh = pObj->currCh;
    UInt32 currProfile = pObj->currProfile;
    UInt32 rowIdx;
    UInt32 azimIdx;
    UInt32 outIdx;
    UInt32 i;
    UInt32 rxAntIdx = 0;
    UInt32 numRxAnt = pLinkCreateParams->chCreateParams[currCh].
        numRxAnt[0][currProfile];
    UInt32 txAntIdx = 0;
    UInt32 numTxAnt = pLinkCreateParams->chCreateParams[currCh].
        numTxAnt[0][currProfile];
    UInt32 numDopBins = pObj->chObj[currCh].numDopplerBins[currProfile];
    UInt32 azimuthFftSize = pLinkCreateParams->aoaCreateParams.azimuthFFTsize;
    UInt16 * pRxRowIndxLUT = pLinkCreateParams->aoaCreateParams.rxRowIndxLUT;
    UInt16 * pRxAngleIndxLUT =
        pLinkCreateParams->aoaCreateParams.rxAngleIndxLUT;
    UInt32 numVirtualAnt = pObj->chObj[currCh].numVirtualAntenna[currProfile];

    __float2_t eInc;
    __float2_t x, y;
    __float2_t e, e0, coef;
    __float2_t * restrict chCompCoefs;

    /* For Doppler compensation */
    e0 = _ftof2(1.0F, 0.0F);
    eInc = _ftof2(cossp(2*pi*(float)targetDopIdxSigned/
                        (float)numDopBins/(float)numTxAnt),
                        sinsp(2*pi*(float)targetDopIdxSigned/
                        (float)numDopBins/(float)numTxAnt));


    memset(pAoaObj->azimFftInputBuf,
           0,
           azimuthFftSize *
           pLinkCreateParams->aoaCreateParams.numAzimuthFFTs *
           sizeof(AlgorithmFxn_RadarDspProcessComplexNum));

    e = e0;
    if (pLinkCreateParams->skipDopplerFft == 0U)
    {
        __float2_t * restrict xf, * restrict yf;
        xf = (__float2_t *) pAoaObj->virtAntBuf[pAoaObj->readPingPongInd];
        yf = (__float2_t *) pAoaObj->azimFftInputBuf;
        chCompCoefs = (__float2_t *) pAoaObj->chanCompCoefs;

        for (i = 0; i < numVirtualAnt; i++)
        {
            rowIdx = pRxRowIndxLUT[i];
            azimIdx = pRxAngleIndxLUT[i];
            outIdx = rowIdx * azimuthFftSize + azimIdx;

            x = _amem8_f2(&xf[i]);
            coef = _amem8_f2(&chCompCoefs[i]);
            y = _complex_mpysp(x, e);
            y = _complex_mpysp(y, coef);
            _amem8_f2(&yf[outIdx]) =  y;

            rxAntIdx++;
            if (rxAntIdx == numRxAnt)
            {
                rxAntIdx = 0;
                txAntIdx++;
                e = _complex_mpysp(e, eInc);;
            }
            if (txAntIdx == numTxAnt)
            {
                e = e0;
                txAntIdx = 0;
            }
        }
    }
    else
    {
        int64_t * restrict xInt;
        int64_t xTemp;
        __float2_t * restrict yf;
        xInt = (int64_t *) pAoaObj->virtAntBuf[pAoaObj->readPingPongInd];
        yf = (__float2_t *) pAoaObj->azimFftInputBuf;
        chCompCoefs = (__float2_t *) pAoaObj->chanCompCoefs;
        for (i = 0; i < numVirtualAnt; i++)
        {
            rowIdx = pRxRowIndxLUT[i];
            azimIdx = pRxAngleIndxLUT[i];
            outIdx = rowIdx * azimuthFftSize + azimIdx;

            /* Read integers and convert to float */
            xTemp = _amem8(&xInt[i]);
            x = _dintsp(xTemp);
            coef = _amem8_f2(&chCompCoefs[i]);
            y = _complex_mpysp(x, e);
            y = _complex_mpysp(y, coef);
            _amem8_f2(&yf[outIdx]) =  y;

            rxAntIdx++;
            if (rxAntIdx == numRxAnt)
            {
                rxAntIdx = 0;
                txAntIdx++;
                e = _complex_mpysp(e, eInc);;
            }
            if (txAntIdx == numTxAnt)
            {
                e = e0;
                txAntIdx = 0;
            }
        }
    }
}

Void radarCascadeAoA_magSquare(
    AlgorithmFxn_RadarDspProcessComplexNum * restrict inBuf,
    float * restrict magSqBuf,
    UInt16 numPoints)
{
    UInt16 i;
    #pragma MUST_ITERATE(2, ,2)
    for (i = 0; i < numPoints; i++)
    {
        magSqBuf[i] = inBuf[i].real * inBuf[i].real + inBuf[i].imag * inBuf[i].imag;
    }
}

float radarCascadeAoA_singlePeakSearchMax(float * x,
                                          UInt16 numPoints)
{
    UInt16 i;
    float maxPeakVal = 0;
    #pragma MUST_ITERATE(2, ,2)
    for (i = 0; i < numPoints; i++)
    {
        if (x[i] > maxPeakVal)
        {
            maxPeakVal = x[i];
        }
    }
    return maxPeakVal;
}

Int32 EstimateExtendedVelocity(
    AlgorithmFxn_RadarDspProcessComplexNum *x2DFetched,
    AlgorithmFxn_RadarDspProcessComplexNum *rxChCompCoefs,
    UInt32 numDopBins,
    UInt32 numTxAnt,
    Int32 dopEstFftInd,
    Int32 numOverlapSymb,
    UInt32 *overlapAntennaPairs)
{
    __float2_t xCurr;
    __float2_t xPrev;
    __float2_t coefCurr;
    __float2_t coefPrev;
    __float2_t * restrict xPtr;
    __float2_t product;
    __float2_t sum;
    Int32 indCurrent;
    Int32 indPrev;
    UInt32 indPair;
    UInt32 * restrict tablePtr;
    __float2_t * restrict coefs;
    Int32 k;
    Int32 extendedDopEstArray[12];
    Int32 offset;
    float absDiff;
    float overlapAntEstInd;

    float minAbsDiff;
    Int32 minDiffInd;

    xPtr = (__float2_t *) x2DFetched;
    coefs = (__float2_t *) rxChCompCoefs;

    tablePtr = (UInt32 *) overlapAntennaPairs;

    sum = 0.0;
    for (k = 0; k < numOverlapSymb; k++)
    {
        indPair = _amem4(&tablePtr[k]);
        indPrev = indPair & 0xffff;
        indCurrent = (indPair>>16) & 0xffff;

        xCurr =  _amem8_f2(&xPtr[indCurrent]);
        xPrev =  _amem8_f2(&xPtr[indPrev]);

        coefCurr = _amem8_f2(&coefs[indCurrent]);
        coefPrev = _amem8_f2(&coefs[indPrev]);

        /* Phase correction */
        xCurr = _complex_mpysp(xCurr, coefCurr);
        xPrev = _complex_mpysp(xPrev, coefPrev);

        /* Swap real imaginary */
        xCurr = _ftof2(_lof2(xCurr), _hif2(xCurr));
        xPrev = _ftof2(_lof2(xPrev), _hif2(xPrev));

        /* product = conj(xPrev) * xCurr */
        product = _complex_conjugate_mpysp(xPrev, xCurr);
        sum = _daddsp(sum, product);
    }

    /* overlapAntEstInd is floating point value */
    overlapAntEstInd = (float) numTxAnt * atan2sp(_lof2(sum),
        _hif2(sum))/(2.*pi)*numDopBins;

    /* Make dopEstFftInd signed */
    if (dopEstFftInd >= numDopBins/2)
    {
        dopEstFftInd = dopEstFftInd - numDopBins;
    }

    /* Create Hypotheses. Number of hypotheses is equal to number of Tx
     * antennas.
     */
    if (numTxAnt & 0x1)
    {
        /* Odd number of Tx antennas */
        offset = -((Int32)(numTxAnt >> 1));
    }
    else
    {
        /* Even number of Tx antennas */
        if (dopEstFftInd > 0)
        {
            offset = -((Int32)(numTxAnt >> 1));
        }
        else
        {
            offset = -((Int32)(numTxAnt >> 1)) + 1;
        }
    }
    for (k = 0; k < numTxAnt; k++)
    {
        extendedDopEstArray[k] =  dopEstFftInd + offset * numDopBins;
        offset++;
    }

    /* Search for best fit, minimum absolute difference */

    k = 0;
    minAbsDiff = (float)extendedDopEstArray[k] -  overlapAntEstInd;
    if (minAbsDiff < 0.0)
    {
        minAbsDiff = - minAbsDiff;
    }
    minDiffInd = k;
    for (k = 1; k < numTxAnt; k++)
    {
        absDiff = (float)extendedDopEstArray[k] -  overlapAntEstInd;
        if (absDiff < 0.0)
        {
            absDiff = - absDiff;
        }
        if (absDiff < minAbsDiff)
        {
            minAbsDiff = absDiff;
            minDiffInd = k;
        }
    }
    return (extendedDopEstArray[minDiffInd]);
}

Int32 EstimateExtendedVelocityIntInp(
    AlgorithmFxn_RadarDspProcessComplexNum *x2DFetched,
    AlgorithmFxn_RadarDspProcessComplexNum *rxChCompCoefs,
    UInt32 numDopBins,
    UInt32 numTxAnt,
    Int32 dopEstFftInd,
    Int32 numOverlapSymb,
    UInt32 *overlapAntennaPairs)
{
    __float2_t xCurr;
    __float2_t xPrev;
    __float2_t coefCurr;
    __float2_t coefPrev;
    int64_t * restrict xPtr;
    int64_t   xTemp1, xTemp2;
    __float2_t product;
    __float2_t sum;
    Int32 indCurrent;
    Int32 indPrev;
    UInt32 indPair;
    UInt32 * restrict tablePtr;
    __float2_t * restrict coefs;
    Int32 k;
    Int32 extendedDopEstArray[12];
    Int32 offset;
    float absDiff;
    float overlapAntEstInd;

    float minAbsDiff;
    Int32 minDiffInd;

    xPtr = (int64_t *) x2DFetched;
    coefs = (__float2_t *) rxChCompCoefs;

    tablePtr = (UInt32 *) overlapAntennaPairs;

    sum = 0.0;
    for (k = 0; k < numOverlapSymb; k++)
    {
        indPair = _amem4(&tablePtr[k]);
        indPrev = indPair & 0xffff;
        indCurrent = (indPair>>16) & 0xffff;

        xTemp1 = _amem8(&xPtr[indCurrent]);
        xCurr =  _dintsp(xTemp1);
        xTemp2 = _amem8(&xPtr[indPrev]);
        xPrev =  _dintsp(xTemp2);

        coefCurr = _amem8_f2(&coefs[indCurrent]);
        coefPrev = _amem8_f2(&coefs[indPrev]);

        /* Phase correction */
        xCurr = _complex_mpysp(xCurr, coefCurr);
        xPrev = _complex_mpysp(xPrev, coefPrev);

        /* Swap real imaginary */
        xCurr = _ftof2(_lof2(xCurr), _hif2(xCurr));
        xPrev = _ftof2(_lof2(xPrev), _hif2(xPrev));

        /* product = conj(xPrev) * xCurr */
        product = _complex_conjugate_mpysp(xPrev, xCurr);
        sum = _daddsp(sum, product);
    }

    /* overlapAntEstInd is floating point value */
    overlapAntEstInd = (float) numTxAnt * atan2sp(_lof2(sum),
        _hif2(sum))/(2.*pi)*numDopBins;

    /* Make dopEstFftInd signed */
    if (dopEstFftInd >= numDopBins/2)
    {
        dopEstFftInd = dopEstFftInd - numDopBins;
    }

    /* Create Hypotheses. Number of hypotheses is equal to number of Tx
     * antennas.
     */
    if (numTxAnt & 0x1)
    {
        /* Odd number of Tx antennas */
        offset = -((Int32)(numTxAnt >> 1));
    }
    else
    {
        /* Even number of Tx antennas */
        if (dopEstFftInd > 0)
        {
            offset = -((Int32)(numTxAnt >> 1));
        }
        else
        {
            offset = -((Int32)(numTxAnt >> 1)) + 1;
        }
    }
    for (k = 0; k < numTxAnt; k++)
    {
        extendedDopEstArray[k] =  dopEstFftInd + offset * numDopBins;
        offset++;
    }

    /* Search for best fit, minimum absolute difference */

    k = 0;
    minAbsDiff = (float)extendedDopEstArray[k] -  overlapAntEstInd;
    if (minAbsDiff < 0.0)
    {
        minAbsDiff = - minAbsDiff;
    }
    minDiffInd = k;
    for (k = 1; k < numTxAnt; k++)
    {
        absDiff = (float)extendedDopEstArray[k] -  overlapAntEstInd;
        if (absDiff < 0.0)
        {
            absDiff = - absDiff;
        }
        if (absDiff < minAbsDiff)
        {
            minAbsDiff = absDiff;
            minDiffInd = k;
        }
    }
    return (extendedDopEstArray[minDiffInd]);
}

Void radarCascadeAoA_mapSymbolsToElevFftInput (
    AlgorithmFxn_RadarDspProcessObj *pObj,
    UInt32 azimPeakPos)
{
    UInt32 rowIdx;
    AlgorithmFxn_RadarDspAoaObj * pAoaObj = &pObj->aoaObj;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        &pObj->algLinkCreateParams;
    memset(pAoaObj->elevFftInputBuf, 0,
           pLinkCreateParams->aoaCreateParams.elevationFFTsize *
           sizeof(AlgorithmFxn_RadarDspProcessComplexNum));
    for (rowIdx = 0;
         rowIdx < pLinkCreateParams->aoaCreateParams.numAzimuthFFTs; rowIdx++)
    {
        pAoaObj->elevFftInputBuf[
            pLinkCreateParams->aoaCreateParams.rxRowToElevIdxLUT[rowIdx]] =
                pAoaObj->azimFftOutputBuf[rowIdx][azimPeakPos];
    }
}

Int16 radarCascadeAoA_singlePeakSearch(float * x,
                                        UInt16 numPoints)
{
    UInt16 i;
    float maxPeakVal = 0;
    Int16 peakPos = 0;
    #pragma MUST_ITERATE(2, ,2)
    for (i = 0; i < numPoints; i++)
    {
        if (x[i] > maxPeakVal)
        {
            maxPeakVal = x[i];
            peakPos = i;
        }
    }
    return peakPos;
}
