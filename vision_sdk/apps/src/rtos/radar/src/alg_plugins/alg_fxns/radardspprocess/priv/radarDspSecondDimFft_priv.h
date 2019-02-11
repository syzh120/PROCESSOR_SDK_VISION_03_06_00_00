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
 * \file radarDspSecondDimFft_priv.h
 *
 * \brief  This file contains plug in functions for radar DSP based second
 *         dimension FFT Processing.
 *
 *******************************************************************************
 */
#ifndef ALG_FXN_RADAR_DSP_SECOND_DIM_FFT_H_
#define ALG_FXN_RADAR_DSP_SECOND_DIM_FFT_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <ti/sdo/edma3/drv/edma3_drv.h>
#include <src/rtos/radar/src/alg_plugins/alg_fxns/radardspprocess/radarDspProcess_Priv.h>
#include "radarDspProcessEdmaUtils.h"
#include <include/alg_fxns/radarFFT_if.h>

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/** DDR performance will be maximized when input block length creates EDMA
 *  full burst beyond which there is no benefit. L2SRAM scratchBuf size will be
 *  influenced by this parameter */
#define EDMA_MAX_INPUT_BLOCK_LENGTH \
    (ALG_FXN_RADAR_DSP_EDMA_DEFAULT_BURST_SIZE_IN_BYTES/ \
    sizeof(AlgorithmFxn_RadarDspProcessComplexNum16bit))

/** Output length provided as separate configuration to balance between L2SRAM
 *  scratchBuf size and performance benefit (less CPU book-keeping, bursts on DDR
 *  are already good for 2D output).
 *  To prevent complexity of remainder processing, make this such that it divides
 *  input length (asserted later)
 */
#define EDMA_MAX_2D_FFT_OUTPUT_BLOCK_LENGTH (EDMA_MAX_INPUT_BLOCK_LENGTH/4U)

/** EDMA Input Queue Id */
#define EDMA_INPUT_QUEUE_ID (ALG_FXN_RADAR_DSP_EDMA_QUEUE_ID_0)
/** EDMA Output Queue Id */
#define EDMA_OUTPUT_QUEUE_ID (ALG_FXN_RADAR_DSP_EDMA_QUEUE_ID_1)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/** \brief Input FFT EDMA Context Structure */
typedef struct
{
    AlgorithmFxn_RadarDspEdmaResource
        resource[ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR];
    /**< First resource of the EDMA */
    UInt8 blockLength;
    /**< Block Length for transfer */
    AlgorithmFxn_RadarDspProcessComplexNum16bit
        *scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR];
    /**< Scratch Buffer for the input buffer */
    AlgorithmFxn_RadarDspProcessComplexNum16bit *scratchCommonBuf;
    /**< Scratch Common Buffer for the input buffer */
    UInt32 pingOrPongLength;
    /**< Length of the buffer */
} AlgorithmFxn_RadarDspSecondDimInpEdma;

/** \brief Output FFT EDMA Context Structure */
typedef struct
{
    AlgorithmFxn_RadarDspEdmaResource
        resource[ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR]
           [EDMA_MAX_2D_FFT_OUTPUT_BLOCK_LENGTH];
    /**< EDMA resource for the Output EDMA */
    UInt8 blockLength;
    /**< Block Length for transfer */
    AlgorithmFxn_RadarDspProcessComplexNum
        *scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR];
    /**< Scratch buffer to hold the output buffers */
    UInt32 pingOrPongLength;
    /**< Length of the buffer */
} AlgorithmFxn_RadarDspSecondDimOpEdma;

/** \brief Energy Sum EDMA Context Structure */
typedef struct
{
    AlgorithmFxn_RadarDspEdmaResource
        resource[ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR];
    /**< EDMA resource for the Energy Sum EDMA */
    UInt8 blockLength;
    /**< Block Length for transfer */
    float *scratchBuf[ALG_FXN_RADAR_DSP_EDMA_PING_PONG_FACTOR];
    /**< Scratch buffer to hold the Energy Sum buffers */
} AlgorithmFxn_RadarDspSecondDimEnergySumEdma;

/** \brief Second Dimension FFT operation object */
typedef struct
{
    UInt32                edmaInstId;
    /**< EDMA Instance Id. */
    EDMA3_DRV_Handle      edmaHandle;
    /**< Handle to EDMA controller associated with this logical DMA channel */
    AlgorithmFxn_RadarDspSecondDimInpEdma       inputEdma;
    /**< Input EDMA configuration parameters */
    AlgorithmFxn_RadarDspSecondDimOpEdma        fftOutputEdma;
    /**< Output EDMA configuration parameters */
    AlgorithmFxn_RadarDspSecondDimEnergySumEdma detectionMatrixEdma;
    /**< Detection Matrix EDMA configuration parameters */
    AlgorithmFxn_RadarDspProcessComplexNum      *twiddleFactBuf;
    /**< Buffer to hold the Twiddle Factors */
    AlgorithmFxn_RadarDspProcessComplexNum      *windowedOutputBuf;
    /**< Buffer to hold the Windowing output and input to the FFT */
    Int16                                       *windowCoeffBuf;
    /**< Buffer to hold the Windowing Coefficients */
} AlgorithmFxn_RadarDspSecondDimFftObj;

/*******************************************************************************
 *  Algorithm Function Private Functions
 *******************************************************************************
 */

#endif /* ALG_FXN_RADAR_DSP_SECOND_DIM_FFT_H_ */
