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
 * \file radarDspSecondDimFft_priv.c
 *
 * \brief  This file contains plug in functions for radar DSP based second
 *         dimension FFT Processing.
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
#include <src/rtos/radar/src/alg_plugins/alg_fxns/radardspprocess/radarDspProcess_Priv.h>
#include <ti/alg/mmwavelib/mmwavelib.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/** Windowing coefficient type - Rectangle */
#define RECTANGLE       (0U)
/** Windowing coefficient type - Hamming */
#define HAMMING         (1U)
/** Windowing coefficient type - Hanning */
#define HANNING         (2U)
/** Windowing coefficient type - Blackman */
#define BLACKMAN        (3U)
/** Windowing coefficient type - Cosine */
#define COSINE          (4U)
/** Windowing coefficient type - Exponential */
#define EXPONENTIAL     (5U)
/** Windowing coefficient type - Kaiser */
#define KAISER          (6U)

/** Q15 format for floating point */
#define Q15FORMAT       (0U)
#define ONE_Q15         (1U << 15U)
/** Q19 format for floating point */
#define Q19FORMAT       (1U)
#define ONE_Q19         (1U << 19U)

#define IN
#define OUT
#define RESTRICT restrict

/** Value of PI */
#define PI 3.1415926535897

/** Macro to align the value x to the value y */
#define ALIGN(x,y)         (((x) + (y) - 1U)/(y))*(y)
/** Number of lanes in VCOP SIMD */
#define VCOP_SIMD_WIDTH    (8u)
/** Maximum EDMA pitch supported by the EVE FFT Operation */
#define FFT_TI_MAX_PITCH_SUPPORTED (32767U)

/** Global Array to hold the Second dimension bit reversal opearation */
static UInt8 gRadarDspSecondDimReverseTable[64] = {
    0x0, 0x20, 0x10, 0x30, 0x8, 0x28, 0x18, 0x38,
    0x4, 0x24, 0x14, 0x34, 0xc, 0x2c, 0x1c, 0x3c,
    0x2, 0x22, 0x12, 0x32, 0xa, 0x2a, 0x1a, 0x3a,
    0x6, 0x26, 0x16, 0x36, 0xe, 0x2e, 0x1e, 0x3e,
    0x1, 0x21, 0x11, 0x31, 0x9, 0x29, 0x19, 0x39,
    0x5, 0x25, 0x15, 0x35, 0xd, 0x2d, 0x1d, 0x3d,
    0x3, 0x23, 0x13, 0x33, 0xb, 0x2b, 0x1b, 0x3b,
    0x7, 0x27, 0x17, 0x37, 0xf, 0x2f, 0x1f, 0x3f
};
/*******************************************************************************
 *  Algorithm Link Private Function Declaration
 *******************************************************************************
 */
static UInt32 AlgorithmFxn_OneDimFftgetBufferSplit(UInt16 numAntennas,
                                                   UInt16 numPoints,
                                                   UInt16 * numPointPerSplit);
static Void AlgorithmFxn_RadarDspSecondDimInpEdmaCreate(
    AlgorithmFxn_RadarDspProcessObj * pObj);
static Void AlgorithmFxn_RadarDspSecondDimOpEdmaCreate(
    AlgorithmFxn_RadarDspProcessObj * pObj);
static Void AlgorithmFxn_RadarDspSecondDimEnergySumEdmaCreate(
    AlgorithmFxn_RadarDspProcessObj * pObj);

static Void AlgorithmFxn_RadarDspSecondDimInpEdmaConfig(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    UInt32 inpBufPitch,
    UInt32 srcAddr,
    UInt32 numHorzPoints);
static Void AlgorithmFxn_RadarDspSecondDimOpEdmaConfig(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    UInt32 numDopplerBins,
    UInt32 numVirtualAntenna);
static Void AlgorithmFxn_RadarDspSecondDimEnergySumEdmaConfig(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    UInt32 numDopplerBins,
    UInt32 numRangeBins);

static Void AlgorithmFxn_RadarDspSecondDimInpEdmaDelete(
    AlgorithmFxn_RadarDspProcessObj * pObj);
static Void AlgorithmFxn_RadarDspSecondDimOpEdmaDelete(
    AlgorithmFxn_RadarDspProcessObj * pObj);
static Void AlgorithmFxn_RadarDspSecondDimEnergySumEdmaDelete(
    AlgorithmFxn_RadarDspProcessObj * pObj);

static Void AlgorithmFxn_RadarDspComputeBlockDopplerFft(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    AlgorithmFxn_RadarDspProcessComplexNum16bit *input,
    AlgorithmFxn_RadarDspProcessComplexNum *output);

static Void AlgorithmFxn_RadarDspSecondDimSetEdmaDestAddr(
    AlgorithmFxn_RadarDspSecondDimOpEdma *pObj,
    UInt32 pingPongIndx,
    AlgorithmFxn_RadarDspProcessComplexNum *destAddr,
    UInt32 numSamplesPerRangeBin);

static Void AlgorithmFxn_RadarDspSecondDimCalcEnergySum(
    AlgorithmFxn_RadarDspProcessComplexNum *input, float *output,
    UInt32 blockLen, UInt32 accumFlag, UInt32 numDopplerBins);

static Void gen_window_coeffs(UInt16 winsize, UInt8 winType, UInt8 format,
                              Void *coeff);
static Void DSP_transpose_i_row_order (
    short * restrict  ptr_Op,
    const short * restrict  ptr_Inp,
    const unsigned int rows_Inp,
    const unsigned int columns_Inp );

static Void    RADARDEMO_dopplerProcCRDCremoval(
                            IN  UInt32 inputSize,
                            OUT float * sigBuf);
static inline void mmwavelib_accumPowerFltp_32bitIntInp(uint32_t length,
                        int32_t accumFlag,
                        int32_t * inputPtr,
                        float32_t * outputPtr);

/*******************************************************************************
 *  Algorithm Link Function Definition
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for the DSP Second Dimension FFT.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None.
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspSecondDimFftCreate(
    AlgorithmFxn_RadarDspProcessObj *pObj)
{
    AlgorithmFxn_RadarDspSecondDimFftObj * p2DObj = &pObj->secondDimFftObj;

    /* Create a EDMA Handle */
    p2DObj->edmaInstId = UTILS_DMA_LOCAL_EDMA_INST_ID;
    p2DObj->edmaHandle = Utils_dmaGetEdma3Hndl(p2DObj->edmaInstId);

    if (pObj->algLinkCreateParams.skipDopplerFft == 0U)
    {
        AlgorithmFxn_RadarDspSecondDimInpEdmaCreate(pObj);

        /* needs block length computed from prior call */
        AlgorithmFxn_RadarDspSecondDimOpEdmaCreate(pObj);

        /* needs block length computed from prior call */
        AlgorithmFxn_RadarDspSecondDimEnergySumEdmaCreate(pObj);

        /* Allocate Buffer for the Twiddle Factors */
        p2DObj->twiddleFactBuf =
            (AlgorithmFxn_RadarDspProcessComplexNum *)
            Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pObj->maxDopplerBins *
                sizeof(AlgorithmFxn_RadarDspProcessComplexNum), 8);

        UTILS_assert(p2DObj->twiddleFactBuf != NULL);
        gen_twiddle_fftSP((float *)p2DObj->twiddleFactBuf, pObj->maxDopplerBins);

        /* Window utility assumes storage needed is half the windowCoeffBuf size
         * due to assumption of symmetric windowCoeffBuf, hence the division by
         * 2 below.
         */
        UTILS_assert((pObj->maxNumVirtChirps % 2) == 0);
        /* Allocate Buffer for the Windowing coefficients */
        p2DObj->windowCoeffBuf = (Int16 *) Utils_memAlloc(UTILS_HEAPID_L2_LOCAL,
                                              (pObj->maxNumVirtChirps / 2)*
                                              sizeof(Int16), 8);
        UTILS_assert(p2DObj->windowCoeffBuf != NULL);
        gen_window_coeffs(pObj->maxNumVirtChirps, RECTANGLE, Q15FORMAT,
                         (Void *)p2DObj->windowCoeffBuf);

        /* Allocate Buffer for the FFT Input Buffer after Windowing */
        p2DObj->windowedOutputBuf =
            (AlgorithmFxn_RadarDspProcessComplexNum *)
                Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pObj->maxDopplerBins *
                    sizeof(AlgorithmFxn_RadarDspProcessComplexNum), 8);
        UTILS_assert(p2DObj->windowedOutputBuf != NULL);
    }
}

/**
 *******************************************************************************
 *
 * \brief Implementation of the Process function for the DSP Second Dimension
 *        FFT.
 *
 * \param  pObj     [IN/OUT] Radar DSP Process Object
 * \param  inputBuf [IN] Input Buffer to the 2nd Dimension FFT.
 * \param  bufDesc [IN] Input Buffer descriptor for each buffer.
 * \param  numDevices[IN] Number of frames in the input buffer.
 *
 * \return  SYSTEM_LINK_STATUS_SOK if the operation is successful.
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspSecondDimFftProcess(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    AlgorithmFxn_RadarDspProcessComplexNum16bit *inputBuf[],
    AlgorithmFxn_RadarFftBuffDescriptor *bufDesc[],
    UInt32 numDevices)
{
    UInt32 chunkIndx,
           fftOutProcIndx, rangeIndx, rxAntIndx, subRangeIndx, i;
    AlgorithmFxn_RadarDspProcessComplexNum16bit *inputAddr, *fftInpScratchAddr;
    AlgorithmFxn_RadarDspProcessComplexNum *fftOutScratchAddr;
    float *detMatAddr, *detMatScratchAddr;
    UInt32 fftOut2DpingPongIndx = ALG_FXN_RADAR_DSP_EDMA_PING_INDEX;
    UInt32 detMatPingPongIndx = ALG_FXN_RADAR_DSP_EDMA_PING_INDEX;
    UInt32 twoDEdmaOutStarted = ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR;
    UInt32 detMatEdmaOutStarted = ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR;
    /* This is the frame index used to access the parameters of the
     * bufdescription. This is kept as 0 as the in the case of multiple single
     * channel Radars the data comes channel by channel and there would be aCnt
     * single frame and in the case of the cascade multi frame case all the
     * frames are assumed to have the same number of horizontal points.
     */
    const UInt32 frameIdx = 0U;
    UInt32 nextSensorIndx;
    UInt32 nextRangePerChunkIndx = 0;
    UInt32 accumChunkSamples;
    UInt32 chId = pObj->currCh;
    UInt32 currProfile = pObj->currProfile;
    UInt32 totalNumChunks = bufDesc[frameIdx]->bufDesc.numChunks;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        (AlgorithmFxn_RadarDspProcessCreateParams *)&pObj->algLinkCreateParams;
    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;
    UInt32 numSamplesPerRangeBin, numDopplerBins, numVirtAntPerSensor,
           numSamplesPerRangeBinPerSensor, numInputXfers;
    UInt32 inputPingPongIndx = ALG_FXN_RADAR_DSP_EDMA_PING_INDEX;
    UInt32 inputXferCount = 0U;
    UInt32 numChirpsLoops = 0U;
    UInt32 sensorIndx;

    /* Calculate the parameters for the number of times the FFT loop will
     * run.
     */
    numDopplerBins = pObj->chObj[chId].numDopplerBins[currProfile];
    numSamplesPerRangeBin = numDopplerBins * pObj->chObj[chId].numVirtualAntenna[currProfile];
    numVirtAntPerSensor =
        pObj->chObj[chId].totalNumTx[currProfile] *
        pLinkCreateParams->chCreateParams[chId].numRxAnt[0U][currProfile];
    numInputXfers =
        pObj->chObj[chId].numVirtualAntenna[currProfile] *
        (pObj->chObj[chId].numRangeBins[currProfile] /
         p2DObj->inputEdma.blockLength);
    numSamplesPerRangeBinPerSensor = numVirtAntPerSensor * numDopplerBins;
    /* Calculate the number of virtual chirps */
    numChirpsLoops = pLinkCreateParams->chCreateParams[chId].
               numChirpLoops[currProfile];

    /* Start the input EDMA. The first sensor is input first */
    inputAddr = inputBuf[0];
    /* Set the input EDMA parameters. This is done every frame to be flexible
     * for the advanced frame which can have different block length and
     * different pitch.
     */
    AlgorithmFxn_RadarDspSecondDimInpEdmaConfig(pObj,
        bufDesc[frameIdx]->bufDesc.pitch[0],
        (UInt32) inputAddr,
        (UInt32)bufDesc[frameIdx]->bufDesc.numHorzPoints[0]);
    AlgorithmFxn_RadarDspSecondDimOpEdmaConfig(pObj,
        numDopplerBins,
        pObj->chObj[chId].numVirtualAntenna[currProfile]);
    AlgorithmFxn_RadarDspSecondDimEnergySumEdmaConfig(pObj, numDopplerBins,
        pObj->chObj[chId].numRangeBins[currProfile]);
    /* Start the EDMA transfer */
    AlgorithmFxn_RadarDspStartEdmaTransfer(p2DObj->edmaHandle,
        &p2DObj->inputEdma.resource[inputPingPongIndx]);
    /* Initialize the range indices and keep track of the input transfers */
    inputXferCount++;
    rangeIndx = 0U;
    accumChunkSamples = 0U;
    detMatAddr = pObj->opBufEnergySum;
    /* Loop Through Number of Chunks of the 1D FFT output of EVE */
    for(chunkIndx = 0U; chunkIndx < totalNumChunks; chunkIndx++)
    {
        UInt32 rangePerChunkIndx;
        UInt32 numHorzPoints =
            bufDesc[frameIdx]->bufDesc.numHorzPoints[chunkIndx];
        /* Loop Through the Range in steps of the block Length */
        for(rangePerChunkIndx = 0U; rangePerChunkIndx < numHorzPoints;
            rangePerChunkIndx += p2DObj->inputEdma.blockLength)
        {
            rxAntIndx = 0U;
            /* Loop Through the number of sensors connected per channel */
            for(sensorIndx = 0U; sensorIndx <
                pLinkCreateParams->chCreateParams[chId].numSensorDevPerChannel;
                sensorIndx++)
            {
                UInt32 rxVirtAntPerSensorIndx;
                /* Loop Through the number of Tx * Rx antennas per sensor */
                for(rxVirtAntPerSensorIndx = 0U; rxVirtAntPerSensorIndx <
                    numVirtAntPerSensor; rxVirtAntPerSensorIndx++)
                {
                    /* prepare for next input transfer, unless it was the very
                     * (entire frame) last one */
                    if (inputXferCount < numInputXfers)
                    {
                        if (rxVirtAntPerSensorIndx == (numVirtAntPerSensor - 1))
                        {
                            nextSensorIndx = sensorIndx + 1;
                            if (nextSensorIndx ==
                                pLinkCreateParams->chCreateParams[chId].
                                numSensorDevPerChannel)
                            {
                                nextSensorIndx = 0;
                                nextRangePerChunkIndx = rangePerChunkIndx +
                                    p2DObj->inputEdma.blockLength;
                                if (nextRangePerChunkIndx == numHorzPoints)
                                {
                                    nextRangePerChunkIndx = 0;
                                    accumChunkSamples +=
                                        (numHorzPoints * numSamplesPerRangeBinPerSensor);
                                }
                            }
                            inputAddr = inputBuf[nextSensorIndx] +
                                nextRangePerChunkIndx + accumChunkSamples;
                        }
                        else
                        {
                            inputAddr += numHorzPoints;   /* + freqOffset[][] */
                        }
                        AlgorithmFxn_RadarDspSetSourceAddress(
                            &p2DObj->inputEdma.resource[inputPingPongIndx ^ 1],
                            (UInt32) inputAddr);
                    }
                    if (inputXferCount < numInputXfers)
                    {
                        AlgorithmFxn_RadarDspStartEdmaTransfer(p2DObj->edmaHandle,
                            &p2DObj->inputEdma.resource[(inputPingPongIndx ^ 1)]);
                        inputXferCount++;
                    }
                    AlgorithmFxn_RadarDspWaitUntilEdmaTransferDone(
                        p2DObj->edmaHandle,
                        &p2DObj->inputEdma.resource[inputPingPongIndx]);
                    fftInpScratchAddr = p2DObj->inputEdma.scratchCommonBuf;
                    /* Transpose the Input Buffer */
                    DSP_transpose_i_row_order(
                        (short *)fftInpScratchAddr,
                        (const short *)p2DObj->inputEdma.scratchBuf[inputPingPongIndx],
                        numChirpsLoops, p2DObj->inputEdma.blockLength);
                    subRangeIndx = 0U;
                    detMatScratchAddr =
                        p2DObj->detectionMatrixEdma.scratchBuf[detMatPingPongIndx];
                    /* process previous one */
                    for(fftOutProcIndx = 0U; fftOutProcIndx <
                        p2DObj->inputEdma.blockLength/p2DObj->fftOutputEdma.blockLength;
                        fftOutProcIndx++)
                    {
                        fftOutScratchAddr =
                            p2DObj->fftOutputEdma.scratchBuf[fftOut2DpingPongIndx];

                        /* process one output fft block length */
                        AlgorithmFxn_RadarDspComputeBlockDopplerFft(
                            pObj, fftInpScratchAddr, fftOutScratchAddr);
                        /* initiate transfer out of the fft processed result */
                        if (twoDEdmaOutStarted == 0U)
                        {
                            AlgorithmFxn_RadarDspWaitUntilEdmaTransferDone(
                                p2DObj->edmaHandle,
                                &p2DObj->fftOutputEdma.resource[fftOut2DpingPongIndx]
                                [p2DObj->fftOutputEdma.blockLength-1]);
                        }
                        else
                        {
                            twoDEdmaOutStarted--;
                        }
                        AlgorithmFxn_RadarDspSecondDimSetEdmaDestAddr(
                                 &p2DObj->fftOutputEdma,
                                 fftOut2DpingPongIndx,
                                 &pObj->opBuf2Dfft[
                                 (rangeIndx + subRangeIndx) * numSamplesPerRangeBin +
                                 rxAntIndx * numDopplerBins],
                                 numSamplesPerRangeBin);

                        AlgorithmFxn_RadarDspStartEdmaTransfer(
                            p2DObj->edmaHandle,
                            &p2DObj->fftOutputEdma.resource
                            [fftOut2DpingPongIndx][0]);
                        AlgorithmFxn_RadarDspSecondDimCalcEnergySum(
                            fftOutScratchAddr,
                            detMatScratchAddr,
                            p2DObj->fftOutputEdma.blockLength,
                            (rxAntIndx != 0),
                            numDopplerBins);
                        fftInpScratchAddr +=
                            (p2DObj->fftOutputEdma.blockLength * numChirpsLoops);
                        detMatScratchAddr +=
                            (p2DObj->fftOutputEdma.blockLength * numDopplerBins);
                        subRangeIndx += p2DObj->fftOutputEdma.blockLength;
                        fftOut2DpingPongIndx ^= 1;
                    } /* fftOutProcIndx */
                    inputPingPongIndx ^= 1;
                    rxAntIndx++;
                } /* rxVirtAntPerSensorIndx */
            } /* sensorIndx */
            if (detMatEdmaOutStarted == 0)
            {
                AlgorithmFxn_RadarDspWaitUntilEdmaTransferDone(
                    p2DObj->edmaHandle,
                    &p2DObj->detectionMatrixEdma.resource[detMatPingPongIndx]);
            }
            else
            {
                detMatEdmaOutStarted--;
            }
            AlgorithmFxn_RadarDspSetDestinationAddress(
                &p2DObj->detectionMatrixEdma.resource[detMatPingPongIndx],
                (UInt32) detMatAddr);
            AlgorithmFxn_RadarDspStartEdmaTransfer(p2DObj->edmaHandle,
                &p2DObj->detectionMatrixEdma.resource[detMatPingPongIndx]);
            detMatPingPongIndx ^= 1;
            rangeIndx += p2DObj->inputEdma.blockLength;
            detMatAddr += p2DObj->inputEdma.blockLength;
        } /* rangePerChunkIndx */
    } /* chunkIndx */

    for (i = 0; i < ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR; i++)
    {
        AlgorithmFxn_RadarDspWaitUntilEdmaTransferDone(
                                p2DObj->edmaHandle,
                                &p2DObj->fftOutputEdma.resource[fftOut2DpingPongIndx]
                                [p2DObj->fftOutputEdma.blockLength-1]);
        fftOut2DpingPongIndx ^= 1;
        AlgorithmFxn_RadarDspWaitUntilEdmaTransferDone(
                    p2DObj->edmaHandle,
                    &p2DObj->detectionMatrixEdma.resource[detMatPingPongIndx]);
        detMatPingPongIndx ^= 1;
    }
}
/**
 *******************************************************************************
 *
 * \brief Implementation of the Process function for the DSP Energy caculation
 *        assuming the 2D FFT is output from EVE.
 *
 * \param  pObj     [IN/OUT] Radar DSP Process Object
 * \param  inputBuf [IN] Input Buffer to the Energy Sum calculation.
 * \param  bufDesc [IN] Input Buffer descriptor for each buffer.
 * \param  numDevices[IN] Number of frames in the input buffer.
 *
 * \return  None
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspCalcEnergySum(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    AlgorithmFxn_RadarDspProcessComplexNum *inputBuf[],
    AlgorithmFxn_RadarFftBuffDescriptor *bufDesc[],
    UInt32 numDevices)
{
    UInt32 inputAddr;
    float *detMatAddr;
    UInt32 numVirtAntPerSensor;
    /* This is the frame index used to access the parameters of the
     * bufdescription. This is kept as 0 as the in the case of multiple single
     * channel Radars the data comes channel by channel and there would be aCnt
     * single frame and in the case of the cascade multi frame case all the
     * frames are assumed to have the same number of horizontal points.
     */
    const UInt32 frameIdx = 0U;
    const UInt32 chunkIndx = 0U;
    UInt32 chId = pObj->currCh;
    UInt32 currProfile = pObj->currProfile;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        (AlgorithmFxn_RadarDspProcessCreateParams *)&pObj->algLinkCreateParams;
    UInt32 sensorIndx;
    UInt32 numDopplerBins, numVertBlocks;
    UInt32 numVertPoints = bufDesc[frameIdx]->bufDesc.numVertPoints;
    UInt32 detMatCurAddr, opPitch;
    UInt32 vertPoint, dopplerBin;
    UInt32 numHorzPoints =
        bufDesc[frameIdx]->bufDesc.numHorzPoints[chunkIndx];
    UInt32 pitch =
        bufDesc[frameIdx]->bufDesc.pitch[chunkIndx];
    UInt32 offsetBwAntenna =
        bufDesc[frameIdx]->bufDesc.offsetBwAntennas[chunkIndx];
    UInt32 opJump = numHorzPoints * sizeof(float);

    /* Calculate the parameters for the number of times the FFT loop will
     * run.
     */
    numVirtAntPerSensor =
        pObj->chObj[chId].totalNumTx[currProfile] *
        pLinkCreateParams->chCreateParams[chId].numRxAnt[0U][currProfile];
    numDopplerBins = pObj->chObj[chId].numDopplerBins[currProfile];
    numVertBlocks = numVertPoints/numDopplerBins;
    opPitch = pObj->chObj[chId].numRangeBins[currProfile] * sizeof(float);

    /* Initialize the range indices and keep track of the input transfers */
    detMatAddr = pObj->opBufEnergySum;

    /* Loop Through the number of vertical points */
    for(vertPoint = 0U; vertPoint < numVertBlocks ; vertPoint++)
    {
        for (dopplerBin = 0; dopplerBin < numDopplerBins; dopplerBin++)
        {
            UInt32 rxAntIndx = 0U;
            UInt32 offsetIn = (vertPoint * numDopplerBins + dopplerBin) * pitch;
            detMatCurAddr =
                (UInt32) detMatAddr + opJump * vertPoint + dopplerBin * opPitch;
            /* Loop Through the number of sensors connected per channel */
            for(sensorIndx = 0U; sensorIndx <
                pLinkCreateParams->chCreateParams[chId].numSensorDevPerChannel;
                sensorIndx++)
            {
                UInt32 rxVirtAntPerSensorIndx;
                inputAddr = (UInt32)inputBuf[sensorIndx] + offsetIn;
                /* Loop Through the number of Tx * Rx antennas per sensor */
                for(rxVirtAntPerSensorIndx = 0U; rxVirtAntPerSensorIndx <
                    numVirtAntPerSensor; rxVirtAntPerSensorIndx++)
                {
                    mmwavelib_accumPowerFltp_32bitIntInp(numHorzPoints,
                                                 (rxAntIndx != 0),
                                                 (int32_t *)inputAddr,
                                                 (float *)detMatCurAddr);
                    rxAntIndx++;
                    inputAddr += offsetBwAntenna;
                } /* rxVirtAntPerSensorIndx */
            } /* sensorIndx */
        } /* dopplerBin */
    } /* vertPoint */
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Delete function for the DSP Second Dimension FFT.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  SYSTEM_LINK_STATUS_SOK if the operation is successful.
 *
 *******************************************************************************
 */
Void AlgorithmFxn_RadarDspSecondDimFftDelete(
    AlgorithmFxn_RadarDspProcessObj *pObj)
{
    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    AlgorithmFxn_RadarDspSecondDimInpEdmaDelete(pObj);

    /* needs block length computed from prior call */
    AlgorithmFxn_RadarDspSecondDimOpEdmaDelete(pObj);

    /* needs block length computed from prior call */
    AlgorithmFxn_RadarDspSecondDimEnergySumEdmaDelete(pObj);

    /* Free Buffer for the Twiddle Factors */
    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                           p2DObj->twiddleFactBuf,
                           pObj->maxDopplerBins *
                           sizeof(AlgorithmFxn_RadarDspProcessComplexNum));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    /* Free Buffer for the Windowing coefficients */
    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                           p2DObj->windowCoeffBuf,
                           (pObj->maxNumVirtChirps / 2)*
                                          sizeof(Int16));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
    /* Free Buffer for the FFT Input Buffer after Windowing */
    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                           p2DObj->windowedOutputBuf,
                           pObj->maxDopplerBins *
                           sizeof(AlgorithmFxn_RadarDspProcessComplexNum));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
}


/******************************************************************************
 *  Internal Functions
******************************************************************************/
/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for the DSP Second Dimension FFT
 *        Input EDMA.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimInpEdmaCreate(
    AlgorithmFxn_RadarDspProcessObj * pObj)
{
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams;
    UInt32 pingOrPongLength;
    UInt32 numHorzPoints;
    UInt32 chId;
    UInt32 profId;
    UInt32 devId;

    UInt32 maxNumHorzPoints = 0xFFFFFFFFU;

    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;

    AlgorithmFxn_RadarDspAllocEdmaResource(p2DObj->edmaHandle,
        &p2DObj->inputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX], EDMA_INPUT_QUEUE_ID);
    AlgorithmFxn_RadarDspAllocEdmaResource(p2DObj->edmaHandle,
        &p2DObj->inputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX], EDMA_INPUT_QUEUE_ID);

    pLinkCreateParams = &pObj->algLinkCreateParams;

    for (chId = 0U; chId < pLinkCreateParams->numChannels; chId++)
    {
        for (profId = 0U; profId < ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE;
             profId++)
        {
            UInt32 totalNumTx = 0U;
            for (devId = 0U;
            devId < ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_RADAR_SENSOR;
            devId++)
            {
                totalNumTx += (UInt32)pLinkCreateParams->chCreateParams[chId].
                                      numTxAnt[devId][profId];

            }
            AlgorithmFxn_OneDimFftgetBufferSplit(
                pLinkCreateParams->chCreateParams[chId].numRxAnt[0U][profId] *
                totalNumTx,
                pObj->chObj[chId].numRangeBins[profId],
                (UInt16*)&numHorzPoints);
            if (maxNumHorzPoints < numHorzPoints)
            {
                /* Select the maximum as that will be the largest size of the
                 * buffer.
                 */
                maxNumHorzPoints = numHorzPoints;
            }
        }
    }
    if (maxNumHorzPoints < EDMA_MAX_INPUT_BLOCK_LENGTH)
    {
        p2DObj->inputEdma.blockLength = maxNumHorzPoints;
    }
    else
    {
        p2DObj->inputEdma.blockLength = EDMA_MAX_INPUT_BLOCK_LENGTH;
    }
    /* Currently only the case where the block length is a exact dividor of the
     * Maximum Block Length.
     */
    UTILS_assert((EDMA_MAX_INPUT_BLOCK_LENGTH %
        p2DObj->inputEdma.blockLength) == 0);

    pingOrPongLength = pObj->maxNumVirtChirps * p2DObj->inputEdma.blockLength *
                       sizeof(AlgorithmFxn_RadarDspProcessComplexNum16bit);

    p2DObj->inputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX] =
        (AlgorithmFxn_RadarDspProcessComplexNum16bit *)
            Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pingOrPongLength, 128);
    p2DObj->inputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX] =
        (AlgorithmFxn_RadarDspProcessComplexNum16bit *)
            Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pingOrPongLength, 128);
    p2DObj->inputEdma.scratchCommonBuf =
        (AlgorithmFxn_RadarDspProcessComplexNum16bit *)
            Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pingOrPongLength, 128);
    /* Store the ping pong length for de-allocation */
    p2DObj->inputEdma.pingOrPongLength = pingOrPongLength;
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for the DSP Second Dimension FFT
 *        Output EDMA.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimOpEdmaCreate(
    AlgorithmFxn_RadarDspProcessObj * pObj)
{
    UInt32 pingOrPongLength;
    UInt32 i;
    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;

    if (p2DObj->inputEdma.blockLength < EDMA_MAX_2D_FFT_OUTPUT_BLOCK_LENGTH)
    {
        p2DObj->fftOutputEdma.blockLength = p2DObj->inputEdma.blockLength;
    }
    else
    {
        p2DObj->fftOutputEdma.blockLength = EDMA_MAX_2D_FFT_OUTPUT_BLOCK_LENGTH;
    }

    for (i = 0; i < p2DObj->fftOutputEdma.blockLength; i++)
    {
        AlgorithmFxn_RadarDspAllocEdmaResource(p2DObj->edmaHandle,
            &p2DObj->fftOutputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX][i],
            EDMA_OUTPUT_QUEUE_ID);
        AlgorithmFxn_RadarDspAllocEdmaResource(p2DObj->edmaHandle,
            &p2DObj->fftOutputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX][i],
            EDMA_OUTPUT_QUEUE_ID);
    }

    pingOrPongLength = pObj->maxDopplerBins *
                       p2DObj->fftOutputEdma.blockLength *
                       sizeof(AlgorithmFxn_RadarDspProcessComplexNum);

    p2DObj->fftOutputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX] =
        (AlgorithmFxn_RadarDspProcessComplexNum *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pingOrPongLength, 128);
    p2DObj->fftOutputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX] =
        (AlgorithmFxn_RadarDspProcessComplexNum *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pingOrPongLength, 128);
    p2DObj->fftOutputEdma.pingOrPongLength = pingOrPongLength;
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for the DSP Second Dimension FFT
 *        Energy Sum EDMA.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimEnergySumEdmaCreate(
    AlgorithmFxn_RadarDspProcessObj * pObj)
{
    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;

    AlgorithmFxn_RadarDspAllocEdmaResource(p2DObj->edmaHandle,
        &p2DObj->detectionMatrixEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX],
        EDMA_OUTPUT_QUEUE_ID);
    AlgorithmFxn_RadarDspAllocEdmaResource(p2DObj->edmaHandle,
        &p2DObj->detectionMatrixEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX],
        EDMA_OUTPUT_QUEUE_ID);

    p2DObj->detectionMatrixEdma.blockLength = p2DObj->inputEdma.blockLength;

    p2DObj->detectionMatrixEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX] = (float *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pObj->maxDopplerBins *
            p2DObj->detectionMatrixEdma.blockLength * sizeof(float), 128);

    p2DObj->detectionMatrixEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX] = (float *)
        Utils_memAlloc(UTILS_HEAPID_L2_LOCAL, pObj->maxDopplerBins *
            p2DObj->detectionMatrixEdma.blockLength * sizeof(float), 128);
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Config function for the DSP Second Dimension FFT
 *        Input EDMA.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 * \param  inpBufPitch [IN] Input Buffer Pitch from the input buffer descriptor
 * \param  srcAddr [IN] Source Address of the buffer
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimInpEdmaConfig(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    UInt32 inpBufPitch,
    UInt32 srcAddr,
    UInt32 numHorzPoints)
{
    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;
    UInt32 bytesPerSample = sizeof(AlgorithmFxn_RadarDspProcessComplexNum16bit);
    EDMA3_DRV_PaRAMRegs *pParamSetPing, *pParamSetShadowPing;
    EDMA3_DRV_PaRAMRegs *pParamSetPong, *pParamSetShadowPong;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        (AlgorithmFxn_RadarDspProcessCreateParams *)&pObj->algLinkCreateParams;
    UInt32 opt = 0U;

    /* Update the block length based on the current frame configurations
     * number of horizontal points
     */
    if (numHorzPoints < EDMA_MAX_INPUT_BLOCK_LENGTH)
    {
        p2DObj->inputEdma.blockLength = numHorzPoints;
    }
    else
    {
        p2DObj->inputEdma.blockLength = EDMA_MAX_INPUT_BLOCK_LENGTH;
    }
    /* Currently only the case where the block length is a exact dividor of the
     * Maximum Block Length.
     */
    UTILS_assert(
        (EDMA_MAX_INPUT_BLOCK_LENGTH % p2DObj->inputEdma.blockLength) == 0);
    /* Config Resource1 Ping EDMA param set and shadow param set */
    pParamSetPing =
        p2DObj->inputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].
        pChParamRegs;
    memset(pParamSetPing, 0x0, sizeof(EDMA3_DRV_PaRAMRegs));
    pParamSetPing->opt        = 0;
    pParamSetPing->srcAddr    = srcAddr;
    pParamSetPing->aCnt       = p2DObj->inputEdma.blockLength * bytesPerSample;
    pParamSetPing->bCnt       = pLinkCreateParams->chCreateParams[pObj->currCh].
                                numChirpLoops[pObj->currProfile];
    pParamSetPing->cCnt       = 1;
    pParamSetPing->srcBIdx    = inpBufPitch;
    pParamSetPing->destBIdx   = pParamSetPing->aCnt;
    pParamSetPing->srcCIdx    = 0;
    pParamSetPing->destCIdx   = 0;
    pParamSetPing->linkAddr   = (UInt32)((UInt32)p2DObj->inputEdma.
        resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].pShadowParamRegs & 0x3FFFU);
    /* enable interrupt for last Transfer ONLY */
    opt |= (EDMA3_CCRL_OPT_TCINTEN_ENABLE
                << EDMA3_CCRL_OPT_TCINTEN_SHIFT) |
                (EDMA3_CCRL_OPT_SYNCDIM_ABSYNC <<
                EDMA3_CCRL_OPT_SYNCDIM_SHIFT);
    pParamSetPing->opt = opt | ((p2DObj->inputEdma.
            resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].tccId <<
            EDMA3_CCRL_OPT_TCC_SHIFT) & EDMA3_CCRL_OPT_TCC_MASK);
    pParamSetPing->destAddr   = (UInt32)
        p2DObj->inputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX];
    /* Shadow copy */
    pParamSetShadowPing =
        p2DObj->inputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].
        pShadowParamRegs;
    /* For Ping Buffer copy the shadow parameter as well. */
    memcpy(pParamSetShadowPing, pParamSetPing, sizeof(EDMA3_DRV_PaRAMRegs));

    /* Config Resource1 Pong EDMA param set and shadow param set */
    pParamSetPong =
        p2DObj->inputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].
        pChParamRegs;
    memcpy(pParamSetPong, pParamSetPing, sizeof(EDMA3_DRV_PaRAMRegs));
    pParamSetPong->opt = opt | ((p2DObj->inputEdma.
                resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].tccId <<
                EDMA3_CCRL_OPT_TCC_SHIFT) & EDMA3_CCRL_OPT_TCC_MASK);
    pParamSetPong->destAddr =
        (UInt32) p2DObj->inputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX];
    pParamSetPong->linkAddr   = (UInt32)((UInt32)p2DObj->inputEdma.
        resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].pShadowParamRegs & 0x3FFFU);
    /* Shadow copy */
    pParamSetShadowPong =
        p2DObj->inputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].
        pShadowParamRegs;
    /* For Pong Buffer copy the shadow parameter as well. */
    memcpy(pParamSetShadowPong, pParamSetPong, sizeof(EDMA3_DRV_PaRAMRegs));
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Config function for the DSP Second Dimension FFT
 *        Output EDMA.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimOpEdmaConfig(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    UInt32 numDopplerBins,
    UInt32 numVirtualAntenna)
{
    UInt32 i;
    EDMA3_DRV_PaRAMRegs *pParamSetPing, *pParamSetShadowPing;
    EDMA3_DRV_PaRAMRegs *pParamSetPong, *pParamSetShadowPong;
    UInt32 bytesPerSample = sizeof(AlgorithmFxn_RadarDspProcessComplexNum);
    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;
    UInt32 opt = 0U;

    if (p2DObj->inputEdma.blockLength < EDMA_MAX_2D_FFT_OUTPUT_BLOCK_LENGTH)
    {
        p2DObj->fftOutputEdma.blockLength = p2DObj->inputEdma.blockLength;
    }
    else
    {
        p2DObj->fftOutputEdma.blockLength = EDMA_MAX_2D_FFT_OUTPUT_BLOCK_LENGTH;
    }

    UTILS_assert((numVirtualAntenna % ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR) == 0);

    /* Config Resource Ping EDMA param set and shadow param set */
    for (i = 0; i < p2DObj->fftOutputEdma.blockLength; i++)
    {
        pParamSetPing =
            p2DObj->fftOutputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX][i].
            pChParamRegs;
        memset(pParamSetPing, 0x0, sizeof(EDMA3_DRV_PaRAMRegs));
        /* end the chain on the last one and set completion notifications enable */
        if (i == (p2DObj->fftOutputEdma.blockLength - 1))
        {
            UInt32 intChId = p2DObj->fftOutputEdma.
                                resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX][i].tccId;
            opt = ((UInt32)((UInt32)EDMA3_CCRL_OPT_SYNCDIM_ASYNC <<
                    EDMA3_CCRL_OPT_SYNCDIM_SHIFT));
            opt |= (UInt32)(((UInt32)EDMA3_CCRL_OPT_TCINTEN_ENABLE
                << EDMA3_CCRL_OPT_TCINTEN_SHIFT) |
                (UInt32)((UInt32)EDMA3_CCRL_OPT_ITCINTEN_ENABLE
                << EDMA3_CCRL_OPT_ITCINTEN_SHIFT));
            pParamSetPing->opt = opt |
                                ((intChId <<
                                EDMA3_CCRL_OPT_TCC_SHIFT) & EDMA3_CCRL_OPT_TCC_MASK);
        }
        else
        {
            UInt32 chainChId = p2DObj->fftOutputEdma.
                    resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX][i+1].chId;
            /* enable chaining for last Transfer and intermediate transfer */
            opt = ((UInt32)((UInt32)EDMA3_CCRL_OPT_SYNCDIM_ASYNC <<
                    EDMA3_CCRL_OPT_SYNCDIM_SHIFT));
            opt |= (UInt32)(((UInt32)EDMA3_CCRL_OPT_TCCHEN_ENABLE
                << EDMA3_CCRL_OPT_TCCHEN_SHIFT) |
                (UInt32)((UInt32)EDMA3_CCRL_OPT_ITCCHEN_ENABLE
                << EDMA3_CCRL_OPT_ITCCHEN_SHIFT));
            pParamSetPing->opt = opt |
                    ((chainChId <<
                    EDMA3_CCRL_OPT_TCC_SHIFT) & EDMA3_CCRL_OPT_TCC_MASK);
        }

        pParamSetPing->aCnt = numDopplerBins * bytesPerSample;
        pParamSetPing->bCnt = numVirtualAntenna/ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR;
        pParamSetPing->bCntReload = pParamSetPing->bCnt;
        pParamSetPing->cCnt = 1U;
        pParamSetPing->destBIdx = pParamSetPing->aCnt *
            ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR;
        pParamSetPing->linkAddr   = (UInt32)((UInt32)p2DObj->fftOutputEdma.
            resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX][i].pShadowParamRegs & 0x3FFFU);
        pParamSetPing->srcAddr =
            (UInt32) p2DObj->fftOutputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX] +
            i * pParamSetPing->aCnt;
        /* Shadow copy */
        pParamSetShadowPing =
            p2DObj->fftOutputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX][i].
            pShadowParamRegs;
        /* For Ping Buffer copy the shadow parameter as well. */
        memcpy(pParamSetShadowPing, pParamSetPing, sizeof(EDMA3_DRV_PaRAMRegs));

        /* Config Resource1 Pong EDMA param set and shadow param set */
        pParamSetPong =
            p2DObj->fftOutputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX][i].
            pChParamRegs;
        memcpy(pParamSetPong, pParamSetPing, sizeof(EDMA3_DRV_PaRAMRegs));
        pParamSetPong->srcAddr =
            (UInt32) p2DObj->fftOutputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX] +
            i * pParamSetPing->aCnt;
        pParamSetPong->linkAddr   = (UInt32)((UInt32)p2DObj->fftOutputEdma.
            resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX][i].pShadowParamRegs & 0x3FFFU);
        if (i < (p2DObj->fftOutputEdma.blockLength - 1))
        {
            pParamSetPong->opt = opt |
                ((UInt32)((UInt32)p2DObj->fftOutputEdma.
                resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX][i+1].chId <<
                EDMA3_CCRL_OPT_TCC_SHIFT) & EDMA3_CCRL_OPT_TCC_MASK);
        }
        else
        {
            UInt32 intChId = p2DObj->fftOutputEdma.
                                resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX][i].tccId;
            pParamSetPong->opt = opt |
                                ((intChId <<
                                EDMA3_CCRL_OPT_TCC_SHIFT) & EDMA3_CCRL_OPT_TCC_MASK);
        }
        /* Shadow copy */
        pParamSetShadowPong =
            p2DObj->fftOutputEdma.
            resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX][i].pShadowParamRegs;
        /* For Pong Buffer copy the shadow parameter as well. */
        memcpy(pParamSetShadowPong, pParamSetPong, sizeof(EDMA3_DRV_PaRAMRegs));
    }
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Config function for the DSP Second Dimension FFT
 *        Energy Sum EDMA.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimEnergySumEdmaConfig(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    UInt32 numDopplerBins,
    UInt32 numRangeBins)
{
    UInt32 bytesPerSample = sizeof(float);
    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;
    EDMA3_DRV_PaRAMRegs *pParamSetPing, *pParamSetShadowPing;
    EDMA3_DRV_PaRAMRegs *pParamSetPong, *pParamSetShadowPong;
    UInt32 opt = 0U;

    /* Config Resource1 Ping EDMA param set and shadow param set */
    pParamSetPing =
        p2DObj->detectionMatrixEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].
        pChParamRegs;
    memset(pParamSetPing, 0x0, sizeof(EDMA3_DRV_PaRAMRegs));
    pParamSetPing->opt        = 0;
    pParamSetPing->srcAddr    =
        (UInt32) p2DObj->detectionMatrixEdma.
            scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX];
    pParamSetPing->aCnt       = bytesPerSample;
    pParamSetPing->bCnt       = p2DObj->detectionMatrixEdma.blockLength;
    pParamSetPing->cCnt       = numDopplerBins;
    pParamSetPing->srcBIdx    = pParamSetPing->aCnt * pParamSetPing->cCnt;
    pParamSetPing->destBIdx   = pParamSetPing->aCnt;
    pParamSetPing->srcCIdx    = pParamSetPing->aCnt;
    pParamSetPing->destCIdx   = numRangeBins * pParamSetPing->aCnt;
    pParamSetPing->linkAddr   = (UInt32)((UInt32)p2DObj->detectionMatrixEdma.
        resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].pShadowParamRegs & 0x3FFFU);
    opt  = (EDMA3_CCRL_OPT_SYNCDIM_ABSYNC << EDMA3_CCRL_OPT_SYNCDIM_SHIFT);
    /* enable chaining for last Transfer */
    opt |= (UInt32)((UInt32)EDMA3_CCRL_OPT_ITCCHEN_ENABLE
                << EDMA3_CCRL_OPT_ITCCHEN_SHIFT);
    /* enable interrupt for last Transfer */
    opt |= (UInt32)((UInt32)EDMA3_CCRL_OPT_TCINTEN_ENABLE
                << EDMA3_CCRL_OPT_TCINTEN_SHIFT);
    pParamSetPing->opt = opt | ((p2DObj->detectionMatrixEdma.
            resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].tccId <<
            EDMA3_CCRL_OPT_TCC_SHIFT) & EDMA3_CCRL_OPT_TCC_MASK);
    pParamSetPing->destAddr   = (UInt32)
        p2DObj->detectionMatrixEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX];
    /* Shadow copy */
    pParamSetShadowPing =
        p2DObj->detectionMatrixEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX].
        pShadowParamRegs;
    /* For Ping Buffer copy the shadow parameter as well. */
    memcpy(pParamSetShadowPing, pParamSetPing, sizeof(EDMA3_DRV_PaRAMRegs));

    /* Config Resource1 Pong EDMA param set and shadow param set */
    pParamSetPong =
        p2DObj->detectionMatrixEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].
        pChParamRegs;
    memcpy(pParamSetPong, pParamSetPing, sizeof(EDMA3_DRV_PaRAMRegs));
    pParamSetPong->srcAddr    =
        (UInt32) p2DObj->detectionMatrixEdma.
            scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX];
    pParamSetPong->linkAddr   = (UInt32)((UInt32)p2DObj->detectionMatrixEdma.
        resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].pShadowParamRegs & 0x3FFFU);
    pParamSetPong->opt = opt | ((p2DObj->detectionMatrixEdma.
                resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].tccId <<
                EDMA3_CCRL_OPT_TCC_SHIFT) & EDMA3_CCRL_OPT_TCC_MASK);
    /* Shadow copy */
    pParamSetShadowPong =
        p2DObj->detectionMatrixEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX].
        pShadowParamRegs;
    /* For Pong Buffer copy the shadow parameter as well. */
    memcpy(pParamSetShadowPong, pParamSetPong, sizeof(EDMA3_DRV_PaRAMRegs));
}

/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for the DSP Second Dimension FFT
 *        Input EDMA.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimInpEdmaDelete(
    AlgorithmFxn_RadarDspProcessObj * pObj)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;

    AlgorithmFxn_RadarDspDeallocEdmaResource(p2DObj->edmaHandle,
        &p2DObj->inputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX]);
    AlgorithmFxn_RadarDspDeallocEdmaResource(p2DObj->edmaHandle,
        &p2DObj->inputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX]);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                           p2DObj->inputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX],
                           p2DObj->inputEdma.pingOrPongLength);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                           p2DObj->inputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX],
                           p2DObj->inputEdma.pingOrPongLength);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                           p2DObj->inputEdma.scratchCommonBuf,
                           p2DObj->inputEdma.pingOrPongLength);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for the DSP Second Dimension FFT
 *        Output EDMA.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimOpEdmaDelete(
    AlgorithmFxn_RadarDspProcessObj * pObj)
{
    UInt32 i;
    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    for (i = 0; i < p2DObj->fftOutputEdma.blockLength; i++)
    {
        AlgorithmFxn_RadarDspDeallocEdmaResource(p2DObj->edmaHandle,
            &p2DObj->fftOutputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX][i]);
        AlgorithmFxn_RadarDspDeallocEdmaResource(p2DObj->edmaHandle,
            &p2DObj->fftOutputEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX][i]);
    }

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                           p2DObj->fftOutputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX],
                           p2DObj->fftOutputEdma.pingOrPongLength);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
                           p2DObj->fftOutputEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX],
                           p2DObj->fftOutputEdma.pingOrPongLength);
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
}
/**
 *******************************************************************************
 *
 * \brief Implementation of Create function for the DSP Second Dimension FFT
 *        Energy Sum EDMA.
 *
 * \param  pObj     [IN] Radar DSP Process Object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimEnergySumEdmaDelete(
    AlgorithmFxn_RadarDspProcessObj * pObj)
{
    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    AlgorithmFxn_RadarDspDeallocEdmaResource(p2DObj->edmaHandle,
        &p2DObj->detectionMatrixEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX]);
    AlgorithmFxn_RadarDspDeallocEdmaResource(p2DObj->edmaHandle,
        &p2DObj->detectionMatrixEdma.resource[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX]);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
        p2DObj->detectionMatrixEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_INDEX],
        p2DObj->detectionMatrixEdma.blockLength * sizeof(float));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);

    status = Utils_memFree(UTILS_HEAPID_L2_LOCAL,
        p2DObj->detectionMatrixEdma.scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PONG_INDEX],
        p2DObj->detectionMatrixEdma.blockLength * sizeof(float));
    UTILS_assert(status == SYSTEM_LINK_STATUS_SOK);
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to calculate the chunking done by the
 *        1D FFT running on the EVE.
 *
 * \param  numAntennas     [IN] Number of antennas per device.
 * \param  numPoints       [IN] Number of range points per device.
 * \param  numPointPerSplit[OUT] Gives out the number of horzontal points per
 *                               chunk split.
 *
 * \return numSplitRequired Number of chunks required.
 *
 *******************************************************************************
 */
static UInt32 AlgorithmFxn_OneDimFftgetBufferSplit(UInt16 numAntennas,
                                                   UInt16 numPoints,
                                                   UInt16 * numPointPerSplit)
{
    UInt32 pointPerSplit;
    UInt32 numSplitRequired;

    numSplitRequired = 1U;

    do
    {
        pointPerSplit = ALIGN( (numPoints/numSplitRequired) , VCOP_SIMD_WIDTH);
        numSplitRequired++;

    } while ( (pointPerSplit * sizeof(Int32) * numAntennas)
               >  FFT_TI_MAX_PITCH_SUPPORTED );

    numSplitRequired =     numSplitRequired - 1U;

    *numPointPerSplit = (UInt16)pointPerSplit;
    return numSplitRequired;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to calculate the block of Doppler FFT.
 *
 * \param  pObj            [IN] Radar DSP Process Object.
 * \param  input           [IN] 1D FFT input samples.
 * \param  output          [OUT] 2D FFT output samples.
 *
 * \return None.
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspComputeBlockDopplerFft(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    AlgorithmFxn_RadarDspProcessComplexNum16bit *input,
    AlgorithmFxn_RadarDspProcessComplexNum *output)
{
    UInt32 i, j;
    AlgorithmFxn_RadarDspProcessComplexNum16bit *inp = input;
    AlgorithmFxn_RadarDspProcessComplexNum *out = output;
    UInt32 radix;
    UInt32 currProfile = pObj->currProfile;
    UInt32 currCh = pObj->currCh;
    UInt32 numDopplerBins = pObj->chObj[currCh].numDopplerBins[currProfile];
    AlgorithmFxn_RadarDspSecondDimFftObj *p2DObj = &pObj->secondDimFftObj;
    AlgorithmFxn_RadarDspProcessCreateParams *pLinkCreateParams =
        (AlgorithmFxn_RadarDspProcessCreateParams *)&pObj->algLinkCreateParams;
    UInt32 numChirpsLoops = pLinkCreateParams->chCreateParams[currCh].
               numChirpLoops[currProfile];

    if (numDopplerBins & 0x55555555U)
    {
        radix = 4;
    }
    else
    {
        radix = 2;
    }

    for(i = 0; i < p2DObj->fftOutputEdma.blockLength; i++)
    {
        mmwavelib_dopplerProcWin2DFxdpinFltOut(numChirpsLoops,
                                               (Int16 *)inp,
                                               (Int16 *)p2DObj->windowCoeffBuf,
                                               (float *)p2DObj->windowedOutputBuf);

        /* DSPlib FFT function overwrites the input, so must zero fill every time */
        for(j = numChirpsLoops; j < numDopplerBins; j++)
        {
            p2DObj->windowedOutputBuf[j].real = 0.0;
            p2DObj->windowedOutputBuf[j].imag = 0.0;
        }

        if (pLinkCreateParams->enableClutterRemoval)
        {
            RADARDEMO_dopplerProcCRDCremoval(numChirpsLoops,
                (float *)&p2DObj->windowedOutputBuf[0]);
        }

        DSPF_sp_fftSPxSP (numDopplerBins,  (float *)p2DObj->windowedOutputBuf,
                          (float *)p2DObj->twiddleFactBuf, (float *)out,
                          gRadarDspSecondDimReverseTable,
                           radix, 0, numDopplerBins);

        inp += numChirpsLoops;
        out += numDopplerBins;
    }
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to set the EDMA destination Address.
 *
 * \param  pObj            [IN] Second Dimension FFT Output EDMA Object Handler.
 * \param  hEdma           [IN] EDMA Handle.
 * \param  pingPongIndx    [IN] Ping or Pong Index.
 * \param  destAddr        [IN] Destination address of the buffer.
 * \param  numSamplesPerRangeBin [IN] Number of samples per range bin.
 *
 * \return None.
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimSetEdmaDestAddr(
    AlgorithmFxn_RadarDspSecondDimOpEdma *pObj,
    UInt32 pingPongIndx,
    AlgorithmFxn_RadarDspProcessComplexNum *destAddr,
    UInt32 numSamplesPerRangeBin)
{
    UInt32 i;
    AlgorithmFxn_RadarDspProcessComplexNum *dAddr = destAddr;

    for(i = 0; i < pObj->blockLength; i++)
    {
        AlgorithmFxn_RadarDspSetDestinationAddress(
            &pObj->resource[pingPongIndx][i], (UInt32)dAddr);
        dAddr += numSamplesPerRangeBin;
    }
}
/**
 *******************************************************************************
 *
 * \brief Implementation of function to set the EDMA destination Address.
 *
 * \param  pObj            [IN] Second Dimension FFT Output EDMA Object Handler.
 * \param  hEdma           [IN] EDMA Handle.
 * \param  pingPongIndx    [IN] Ping or Pong Index.
 * \param  destAddr        [IN] Destination address of the buffer.
 * \param  numSamplesPerRangeBin [IN] Number of samples per range bin.
 *
 * \return None.
 *
 *******************************************************************************
 */
static Void AlgorithmFxn_RadarDspSecondDimCalcEnergySum(
    AlgorithmFxn_RadarDspProcessComplexNum *input, float *output,
    UInt32 blockLen, UInt32 accumFlag, UInt32 numDopplerBins)
{
    UInt32 i;
    AlgorithmFxn_RadarDspProcessComplexNum *inp = input;
    float *out = output;

    for(i = 0; i < blockLen; i++)
    {
        mmwavelib_accumPowerFltp(numDopplerBins,
                                 accumFlag, (float *)inp,
                                 out);

        inp += numDopplerBins;
        out += numDopplerBins;
    }
}

/******************************************************************************
 *  Algorithm Specific Functions - To be linked to libraries
******************************************************************************/

/*------------------------------------------------------------*/
/* Bessel function of first kind and order  */
/*          0 at input x                                      */
/*------------------------------------------------------------*/

static double bessj0( double x )
{

    double fac[6]={1,4,36,576, 14400, 518400};
    UInt8 ii;
    double xx,y,ans,ans1;

    ans = 1;
    xx = x * x;
    y = xx/4.f;

    ans1 = 1;
    for (ii=0;ii<6;ii++)
    {
        //ans1 = pow(y,ii+1);
        ans1 *= y;
        ans += (ans1/fac[ii]);
    }

   return ans;
}

Void gen_window_coeffs(UInt16 winsize, UInt8 winType, UInt8 format,  Void *coeff)
{

    UInt16 i;
    float temp;
    Int16 itemp16;
    Int32 itemp32;
    Int32 oneformat;
    Int16 * coeffQ15 = (Int16 *) coeff;
    Int32 * coeffQ19 = (Int32 *) coeff;
    double tempd;
    double tempd1;

    if (format==Q15FORMAT)
        oneformat = ONE_Q15;
    else if (format==Q19FORMAT)
        oneformat = ONE_Q19;

    if (winType == KAISER)
        tempd = bessj0(3*PI);
    for (i = 0; i < winsize/2; i++)
    {

        if (winType == HAMMING)
        {
            /* wn = 0.54-0.46*cos(2*pi*n/(N-1))*/
            temp = oneformat * (0.54-0.46 * cos(2*PI*i/(winsize-1)));
        }
        else if (winType==HANNING)
        {
            /*wn = 0.5*[1-cos(2*pi*i/(N-1));*/
            temp = oneformat * (0.5*(1-cos(2*PI*i/(winsize-1))));
        }
        else if (winType==BLACKMAN)
        {
            /* wn = 0.42659-0.49656*cos(2*pi*n/(N-1))+0.076849*cos(4*pi*n/(N-1))*/
            temp = oneformat * (0.42659-0.49656*cos(2*PI*i/(winsize-1))+0.076849*cos(4*PI*i/(winsize-1)));
        }
        else if (winType==COSINE)
        {
            temp = oneformat*cos(PI*i/(winsize-1)-PI/2);
        }
        else if (winType==RECTANGLE)
        {
            temp = oneformat-1;
        }
        else if (winType == EXPONENTIAL)
        {
            temp = oneformat * exp(-(winsize/2-i)*2/winsize);
        }
        else if (winType == KAISER)
        {
            tempd1 = 1-(double)2*i/(winsize-1); //2n/(N-1)-1
            tempd1 = tempd1*tempd1; //^2
            temp = oneformat * (bessj0(3*PI*sqrt(1-tempd1))/tempd);
        }


        if (temp>0)
        {
            temp = temp + 0.5;
        }
        else
        {
            temp = temp - 0.5;
        }

        if (format==Q15FORMAT)
        {
            itemp16 = (Int16) temp;

            if (itemp16>=ONE_Q15)
                itemp16 = ONE_Q15 - 1;

            coeffQ15[i] = itemp16;

        }
        else if (format ==Q19FORMAT )
        {
            itemp32 = (Int32) temp;

            if (itemp32 >= ONE_Q19)
                itemp32 = ONE_Q19 - 1;

            coeffQ19[i] = itemp32;

        }
    }

}/*gen_window_coeffs*/

int gen_twiddle_fftSP(float *w, int n)
{
    int i, j, k, s=0, t;

    for (j = 1, k = 0; j < n >> 2; j = j << 2, s++) {
        for (i = t=0; i < n >> 2; i += j, t++) {
            w[k +  5] =  cos(6.0 * PI * i / n);
            w[k +  4] =  sin(6.0 * PI * i / n);

            w[k +  3] =  cos(4.0 * PI * i / n);
            w[k +  2] =  sin(4.0 * PI * i / n);

            w[k +  1] =  cos(2.0 * PI * i / n);
            w[k +  0] =  sin(2.0 * PI * i / n);

            k += 6;
        }
    }
    return k;
}

/* Modified code from above code provided originally by Anil Mani. We swap the order
 * of processing so we navigate along row direction of input in the inner loop
 * because that is the bigger dimension for cascade use case (doppler is 128)
 * compared to the column dimension (= 32, the input edma block size to max out EDMA/DDR burst).
 */
static inline Void DSP_transpose_i_row_order (
    short * restrict  ptr_Op,
    const short * restrict  ptr_Inp,
    const unsigned int rows_Inp,
    const unsigned int columns_Inp )
{


    unsigned int r, c;
    unsigned int cols2, rows2;
    unsigned long long doubleWord_Inp0,doubleWord_Inp1;
    unsigned long long doubleWord_Op0, doubleWord_Op1;
    unsigned long long * restrict pRead0;
    unsigned long long * restrict pRead1;
    unsigned long long * restrict pWrite0;
    unsigned long long * restrict pWrite1;


    unsigned int loWordInp0,loWordInp1, hiWordInp0, hiWordInp1;

    cols2 = columns_Inp >> 1;
    rows2 = rows_Inp >> 1;

    _nassert((int)(ptr_Inp) % 8 == 0);
    _nassert((int)(ptr_Op) % 8 == 0);

    pWrite0 = (unsigned long long *) ptr_Op;
    /* ptr_Inp is a short*, there are 2*columns_Inp elements in a column
       because it is a 16 bit complex matrix. 'pRead' being a long long *
       is incremented by (2*columns_Inp)/4 to get the next column */
    pWrite1 = (unsigned long long *) ptr_Op + (rows2);

    /* We read 2x2 complex words (using double loads) from 2 consecutive
     * rows of the matrix.  We then transpose the 2x2 matrix and then
     * populate the output matrix. */
    #pragma MUST_ITERATE(2, ,2)
    for(r = 0; r < cols2; r ++)
    {
    /* ptr_Op is a short*, there are 2*rows_Inp elements in a column
       * because the output is a transposed version of the complex input
       * matrix. 'pWrite' being a long long, is  incremented by
       * (2*rows_Inp)/4 to get the next column. Since we are processing
       * two columns in parallel, we have to increment by twice as much
       * or 'rows_Inp'. */

        pRead0 = (unsigned long long *) ptr_Inp;
        pRead1 = (unsigned long long *) ptr_Inp + cols2;

        #pragma MUST_ITERATE(2, ,2)
        for(c = 0; c < rows2; c ++)
        {
               doubleWord_Inp0 = *pRead0;
               loWordInp0 = _loll(doubleWord_Inp0);
               hiWordInp0 = _hill(doubleWord_Inp0);
               pRead0 += (2*cols2);

               doubleWord_Inp1 = *pRead1;
               loWordInp1 = _loll(doubleWord_Inp1);
               hiWordInp1 = _hill(doubleWord_Inp1);
               pRead1 += (2*cols2);

               /* 2x2 transpose. */
               doubleWord_Op0 = _itoll(loWordInp1,loWordInp0);
               doubleWord_Op1 = _itoll(hiWordInp1,hiWordInp0);

               *pWrite0++ = doubleWord_Op0;
               *pWrite1++ = doubleWord_Op1;
        }

        pWrite0 += (rows2);
        pWrite1 += (rows2);

        /* ptr_Op is a short and as such is incremented by four to access the
        * double word.
        */
        ptr_Inp += 4;
    }
}

/*!
   \fn     RADARDEMO_dopplerProcCRDCremoval

   \brief   Clutter removal by subtracting DC value.

   \param[in]    fftSize2D
               Input 2D FFT size.

   \param[in, out]    sigBuf
               Pointer to floating point I/Q samples.

   \pre       LITTLE ENDIAN ONLY

   \post      none


 */
static inline  Void    RADARDEMO_dopplerProcCRDCremoval(
                            IN  UInt32 inputSize,
                            OUT float * sigBuf)
{
    Int32     j, inputSizeby2;
    __float2_t  * RESTRICT input1, * RESTRICT input2, sum1, sum2, f2temp, avg;
    __float2_t   * RESTRICT output1, * RESTRICT output2;
    float       ftemp;

    inputSizeby2    =   inputSize >> 1;
    input1      =   (__float2_t  *) &sigBuf[0];
    input2      =   (__float2_t  *) &sigBuf[inputSizeby2 << 1];
    sum1        =   _ftof2(0.f, 0.f);
    sum2        =   _ftof2(0.f, 0.f);
    ftemp       =   _rcpsp((float)inputSize);
    ftemp       =   ftemp * (2.f - ftemp * (float)inputSize);
    ftemp       =   ftemp * (2.f - ftemp * (float)inputSize);
    f2temp      =   _ftof2(ftemp, ftemp);

    /* windowing - no assumption of symmetric*/
    for (j = 0; j < (Int32) inputSizeby2; j++)
    {
        sum1        =   _daddsp(sum1, _amem8_f2(input1++));
        sum2        =   _daddsp(sum2, _amem8_f2(input2++));
    }
    if (inputSize & 1)
        sum2        =   _daddsp(sum2, _amem8_f2(input2++));
    sum1        =   _daddsp(sum1, sum2);
    avg         =   _dmpysp(sum1, f2temp);

    output1     =   (__float2_t  *) &sigBuf[0];
    output2     =   (__float2_t  *) &sigBuf[inputSizeby2 << 1];

    for (j = 0; j < (Int32) inputSizeby2; j++)
    {
        f2temp                  =   _dsubsp(_amem8_f2(output1), avg);
        _amem8_f2(output1++)    =   f2temp;
        f2temp                  =   _dsubsp(_amem8_f2(output2), avg);
        _amem8_f2(output2++)    =   f2temp;
    }
    if (inputSize & 1)
        _amem8_f2(output2)      =   _dsubsp(_amem8_f2(output2), avg);
}

static inline void mmwavelib_accumPowerFltp_32bitIntInp(uint32_t length,
                        int32_t accumFlag,
                        int32_t * inputPtr,
                        float32_t * outputPtr)
{
    int32_t     j;
    int64_t  * restrict input1;
    float32_t   * restrict output;
    float32_t   * restrict output2;
    int64_t  lltemp2;
    __float2_t  lltemp1;
    __float2_t  results;

    if (accumFlag == 0)
    {
        input1 = (int64_t  *) inputPtr;
        output = (float32_t *)  outputPtr;
        output2 = ((float32_t*)  outputPtr) + 1;
        #pragma MUST_ITERATE(2, ,2)
        for (j = 0; j < (int32_t) length; j += 2)
        {
            lltemp2     =   _amem8(input1);
            lltemp1     =   _dintsp(lltemp2);
            input1++;
            results     =   _dmpysp(lltemp1,lltemp1);
            *output     =   _hif2(results) + _lof2(results);
            output+=2;
            lltemp2     =   _amem8(input1);
            lltemp1     =   _dintsp(lltemp2);
            input1++;
            results     =   _dmpysp(lltemp1,lltemp1);
            *output2     =   _hif2(results) + _lof2(results);
            output2+=2;
        }
    }
    else
    {
        input1 = (int64_t  *) inputPtr;
        output = (float32_t *)  outputPtr;
        output2 = ((float32_t*)  outputPtr) + 1;
        #pragma MUST_ITERATE(2, ,2)
        for (j = 0; j < (int32_t) length; j += 2)
        {
            lltemp2     =   _amem8(input1);
            lltemp1     =   _dintsp(lltemp2);
            input1++;
            results     =   _dmpysp(lltemp1,lltemp1);
            *output     +=  _hif2(results) + _lof2(results);
            output+=2;
            lltemp2     =   _amem8(input1);
            lltemp1     =   _dintsp(lltemp2);
            input1++;
            results     =   _dmpysp(lltemp1,lltemp1);
            *output2     +=  _hif2(results) + _lof2(results);
            output2+=2;
        }
    }
}

