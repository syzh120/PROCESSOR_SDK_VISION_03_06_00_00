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
 *
 * \file radarDspProcess_priv.h  Radar DSP based Radar processing
 *                               private header file.
 *
 * \brief  This link private header file has defined
 *         - Algorithm function instance/handle object
 *         - All the local data structures
 *         - Algorithm function interfaces
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_RADAR_DSP_PROCESS_PRIV_H
#define ALGORITHM_LINK_RADAR_DSP_PROCESS_PRIV_H

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/algorithmLink.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <include/alg_fxns/radarDspProcess_if.h>
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <src/rtos/utils_common/include/utils_dma.h>
#include "priv/radarDspSecondDimFft_priv.h"
#include "priv/radarDspProcessAoa_priv.h"
#include <ti/sdo/edma3/drv/edma3_drv.h>

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *  \brief   Structure contains channel specific Object Information.
 *
 */
typedef struct
{
    UInt16     numRangeBins[ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE];
    /**< Holds the next power of 2 of the number of ADC samples */
    UInt16     numDopplerBins[ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE];
    /**< Holds the next power of 2 of the number of chirp loops */
    UInt16     numVirtualAntenna[ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE];
    /**< Total number of virtual antennas */
    UInt16     totalNumTx[ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_PROFILE];
    /**< Total number of transmit antenna */
} AlgorithmFxn_RadarDspProcessChannelObj;

/**
 *  \brief   Structure contains results from CFAR algorithm
 */
typedef struct
{
    UInt16     numObjDetected;
    /**< number of objectes detected*/
    UInt16     rangeInd[ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS];
    /**< range index pointer*/
    UInt16     dopplerInd[ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS];
    /**< Doppler index pointer*/
    float      rangeEst[ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS];
    /**< range estimation pointer*/
    float      dopplerEst[ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS];
    /**< Doppler estimation pointer*/
    float      snrEst[ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS];
    /**< linear snr estimation pointer*/
    float      noise[ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS];
    /**< Total noise estimation*/
    float      rangeVar[ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS];
    /**< Variance for range estimation*/
    float      dopplerVar[ALGORITHMFXN_RADAR_DSP_PROCESS_MAX_OBJECTS];
    /**< Variance for Doppler estimation*/
} AlgorithmFxn_RadarDspProcessCFAROut;

/**
 *  \brief   Structure contains pointers in DSP Processing output
 */
typedef struct
{
    AlgorithmFxn_RadarDspProcessOutputHeader *pMsgHeader;
    /**< In the output blob this is the pointer to the output header */
    AlgorithmFxn_RadarDspProcessOpSectionHdr *pPointCloudSectionHeader;
    /**< Section Header for the point cloud */
    AlgorithmFxn_RadarDspProcessOpCloudPoint *pPointCloud;
    /**< In the output blob this is the pointer to the point cloud */
    float                                    *pRangeProfile;
    /**< In the output blob this is the pointer to the range profile */
    float                                    *pRangeDopplerHeatmap;
    /**< In the output blob this is the pointer to the range doppler heat map */
    float                                    *pStaticAzimHeatmap;
    /**< In the output blob this is the pointer to the azimuth heat map */
    AlgorithmFxn_RadarDspProcessOpSystemInfo *pSystemInfo;
    /**< In the output blob this is the pointer to the System Information */
    AlgorithmFxn_RadarDspProcessComplexNum   *pCalibrationCoefs;
    /**< In the output blob this is the pointer to the calibration
     *   coefficients */
} AlgorithmFxn_RadarDspProcessOpBufPointers;

/**
 *  \brief   Structure contains data Objects shared inside Radar DSP Processing.
 */
typedef struct
{
    AlgorithmFxn_RadarDspProcessCreateParams algLinkCreateParams;
    /**< Cascade Algo Create Params  */
    AlgorithmFxn_RadarDspSecondDimFftObj     secondDimFftObj;
    /**< Second Dimension FFT operation object */
    UInt32                                 * cfarScratch;
    /**< Buffer pointer to the cfar scratch buffer */
    AlgorithmFxn_RadarDspAoaObj              aoaObj;
    /**< Angle of Arrival Processing object */
    AlgorithmFxn_RadarDspProcessComplexNum * opBuf2Dfft;
    /**< Pointer to the output buffer to the 2D FFT processing */
    UInt32                                   opBufSize2Dfft;
    /**< Size of the output buffer of the 2D FFT processing */
    float                                  * opBufEnergySum;
    /**< Pointer to the output buffer to the Energy Sum Calculation */
    UInt32                                   opBufSizeEnergySum;
    /**< Size of the output buffer of the Energy Sum Calculation */
    AlgorithmFxn_RadarDspProcessCFAROut    * opBufCFAR;
    /**< Pointer to the output buffer to the CFAR peak detection */
    AlgorithmFxn_RadarDspProcessOpBufPointers opBufPointers;
    /**< Object containing the pointers to the output blob */
    float                                   * opBufStaticHeatMap;
    /**< Pointer to the output buffer containing the Static HeatMap */
    UInt32                                   opBufSizeStaticHeatMap;
    /**< Size of the output buffer containing the Static HeatMap */
    AlgorithmFxn_RadarDspProcessChannelObj   chObj[
        ALGORITHM_FXN_RADAR_DSP_PROCESS_MAX_CHANNELS];
    /**< Structure contains channel specific Object Information. */
    UInt16                                   maxRangeBins;
    /**< Maximum Number of Range Bins for every channel and profile */
    UInt16                                   maxDopplerBins;
    /**< Maximum Number of Doppler Bins for every channel and profile */
    UInt16                                   maxNumVirtChirps;
    /**< Maximum Number of Virtual Chirps for every device */
    UInt16                                   maxNumVirtAnt;
    /**< Maximum number of Virtual antennas */
    UInt32                                   currCh;
    /**< Current Channel being processed */
    UInt32                                   currProfile;
    /**< Current Profile being processed */
} AlgorithmFxn_RadarDspProcessObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
void * AlgorithmFxn_RadarDspProcessCreate(
    AlgorithmLink_RadarProcessCreateParams *createParams,
    AlgorithmLink_RadarProcessAlgCreateOpParams *opParams);

Int32 AlgorithmFxn_RadarDspProcessProcess(void *alg_handle,
                                    System_Buffer *in_buf,
                                    System_Buffer *out_buf);

Int32 AlgorithmFxn_RadarDspProcessControlHandler(void *alg_handle,
    AlgorithmLink_RadarProcessControlParams *controlParams);

Int32 AlgorithmFxn_RadarDspProcessDelete(void *alg_handle);

Void AlgorithmFxn_RadarDspSecondDimFftCreate(
    AlgorithmFxn_RadarDspProcessObj *pObj);

Void AlgorithmFxn_RadarDspSecondDimFftProcess(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    AlgorithmFxn_RadarDspProcessComplexNum16bit *inputBuf[],
    AlgorithmFxn_RadarFftBuffDescriptor *bufDesc[],
    UInt32 numDevices);

Void AlgorithmFxn_RadarDspCalcEnergySum(
    AlgorithmFxn_RadarDspProcessObj *pObj,
    AlgorithmFxn_RadarDspProcessComplexNum *inputBuf[],
    AlgorithmFxn_RadarFftBuffDescriptor *bufDesc[],
    UInt32 numDevices);

Void AlgorithmFxn_RadarDspSecondDimFftDelete(
    AlgorithmFxn_RadarDspProcessObj *pObj);

Void AlgorithmFxn_RadarDspCfarCreate(AlgorithmFxn_RadarDspProcessObj *pObj);
Int32 AlgorithmFxn_RadarDspCfarProcess(AlgorithmFxn_RadarDspProcessObj *pObj);
Void AlgorithmFxn_RadarDspCfarDelete(AlgorithmFxn_RadarDspProcessObj *pObj);

Void AlgorithmFxn_RadarDspAoaCreate(AlgorithmFxn_RadarDspProcessObj *pObj);
Void AlgorithmFxn_RadarDspAoaProcess (AlgorithmFxn_RadarDspProcessObj * pObj);
Void AlgorithmFxn_RadarDspAoaDelete(AlgorithmFxn_RadarDspProcessObj *pObj);

Void AlgorithmFxn_RadarDspAoaProcessHeatMap (AlgorithmFxn_RadarDspProcessObj * pObj,   UInt16 dopplerIndexProcess, float *outBuf);
int gen_twiddle_fftSP(float *w, int n);

#endif /* ALGORITHM_LINK_RADAR_DSP_PROCESS_PRIV_H */
