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
 * \file radarDspProcessAoa_priv.h
 *
 * \brief  This file contains plug in functions for radar DSP based angle of
 *         arrival Processing.
 *
 *******************************************************************************
 */

#ifndef RADAR_DSP_PROCESS_AOA_PRIV_H_
#define RADAR_DSP_PROCESS_AOA_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/radar/src/alg_plugins/alg_fxns/radardspprocess/radarDspProcess_Priv.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define ALG_FXN_RADAR_DSP_PROCESS_AOA_MAX_AZIMUTH_FFT (4U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */
/**
 *  \brief   Calibration state of the AoA algorithm.
 */
typedef struct
{
    UInt32 currState;
    /**< Current Calibration state */
    UInt32 currFrameCntr;
    /**< Current Calibration frame counter */
    AlgorithmFxn_RadarDspProcessCalibParams copyParams;
    /**< Copy of the programmed parameters */
} AlgorithmFxn_RadarDspAoaCalibState;

/**< \brief Structure for the Angle of Arrival Processing Object */
typedef struct
{
    EDMA3_DRV_Handle      edmaHandle;
    /**< Handle to EDMA controller associated with this logical DMA channel */
    AlgorithmFxn_RadarDspEdmaResource edmaRes
        [ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR];
    /**< Edma Resource for Ping and Pong Buffer */
    AlgorithmFxn_RadarDspProcessComplexNum *chanCompCoefs;
    /**< Channel compensation coefficients */
    AlgorithmFxn_RadarDspProcessComplexNum *virtAntBuf
        [ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR];
    /**< ping/pong buffer for 2D-FFT Virtual antennas fetched by EDMA from
     *   2D-FFT radar matrix for particular Range/Doppler index,
     *   each buffer size = numVirtualAntenna
     */
    UInt32 writePingPongInd;
    /**< Current write index of two buffers in virtAntBuf*/
    UInt32 readPingPongInd;
    /**< Current read index of two buffers in virtAntBuf*/
    AlgorithmFxn_RadarDspProcessComplexNum *azimFftInputBuf;
    /**< Input buffer to azimuth FFT, size = azimuthFFTsize * numAzimuthFFTs */
    AlgorithmFxn_RadarDspProcessComplexNum *azimFftOutputBuf
        [ALG_FXN_RADAR_DSP_PROCESS_AOA_MAX_AZIMUTH_FFT];
    /**< Output buffer of azimuth FFT, size = azimuth FFT size*/
    float *azimFftOutMagSquared;
    /**< Magnitude squared output of azimuth FFT of one row */
    UInt16 *azimFftOutPeakPosBuf;
    /**< List of detected peaks in azimuth FFT output */
    AlgorithmFxn_RadarDspProcessComplexNum *elevFftInputBuf;
    /**< Input buffer to elevation FFT, size = elevation FFT size*/
    AlgorithmFxn_RadarDspProcessComplexNum *elevFftOutputBuf;
    /**< Output buffer of elevation FFT, size = elevation FFT size*/
    float *elevOutputMagSquared;
    /**< Magnitude squared output of elevation FFT*/
    float *twiddleAzimuth;
    /**< Twiddle Factor for Azimuth FFT */
    float *twiddleElevation;
    /**< Twiddle Factor for Elevation FFT */
    AlgorithmFxn_RadarDspAoaCalibState calibState;
    /**< Calibration State of the Angle of arrival algorithm */
    AlgorithmFxn_RadarDspProcessComplexNum **inputBuf;
    /**< Pointer to the original input buffers */
    AlgorithmFxn_RadarFftBuffDescriptor **bufDesc;
    /**< Pointer to the original buffer descriptors */
} AlgorithmFxn_RadarDspAoaObj;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* RADAR_DSP_PROCESS_AOA_PRIV_H_ */
