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

/**
 *******************************************************************************
 *
 * \ingroup  ALGORITHM_FUNCTION
 * \defgroup ALGORITHM_RADARFFT  Fast Fourier Transform API
 *
 * \brief  This file contains plug in functions for radar fft.
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_radarFft.h
 *
 * \brief Plugin for Radar fft.
 *
 * \version 0.0 (Oct 2016) : [CM] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_RADAR_FFT_H_
#define ALGORITHM_LINK_RADAR_FFT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/common/alg_functions.h>
#include <include/common/chains_radar_cfg.h>
#include <include/alglink_api/algorithmLink_radarProcess.h>
#include "ifft_ti.h"

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define RADAR_FFT_MAX_CONFIG (2U)
#define RADAR_FFT_MAX_NUM_STAGES (8U)
#define RADAR_FFT_MAX_NUM_CHUNKS (8U)
#define RADAR_FFT_MAX_NUM_PROFILE (4U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
  @brief The directions in which FFT can be calculated. Below enums define for this

  FFT_TI_DIRECTION_HORIZONTAL: FFT is calculated along the direction of 1st dimension (horizontal) of buffer

  FFT_TI_DIRECTION_VERTICAL: FFT is calculated along the direction of 2nd dimension (vertical) of buffer
*/
typedef enum
{
    RADAR_FFT_MODE_HORIZONTAL = 0,
    RADAR_FFT_MODE_VERTICAL = 1,
    RADAR_FFT_MODE_HORZ_AND_VERT = 2,
    RADAR_FFT_MODE_FORCE_32BITS = 0x7FFFFFFFU
} AlgorithmFxn_RadarFftAlgMode ;

/**
  @brief The number of point in the direction of FFT. Below enums define for this

  RADAR_FFT_NUM_POINTS_1024:  Number of point of along the direction of FFT is 1024
  RADAR_FFT_NUM_POINTS_512:  Number of point of along the direction of FFT is 512
  RADAR_FFT_NUM_POINTS_256 : Number of point along the direction of FFT is 256
  RADAR_FFT_NUM_POINTS_128 : Number of point along the direction of FFT is 128
  RADAR_FFT_NUM_POINTS_64 : Number of point along the direction of FFT is 64
*/
typedef enum
{
    RADAR_FFT_NUM_POINTS_1024 = 0,
    RADAR_FFT_NUM_POINTS_512,
    RADAR_FFT_NUM_POINTS_256,
    RADAR_FFT_NUM_POINTS_128,
    RADAR_FFT_NUM_POINTS_64,
    RADAR_FFT_NUM_POINTS_MAX
} AlgorithmFxn_RadarFftNumPoints;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for FFT algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32        winCoefficients[RADAR_FFT_MAX_NUM_STAGES];
    /**< winCoefficients */
    UInt32        enableWindowing;
    /**< Enable Windowing */
    UInt32        enableDcoffset;
    /**< Enable Dcoffset */
    UInt32        enableInterferenceZeroOut;
    /**< Enable InterferenceZeroOut */
    UInt32        enableDopplerCorrection;
    /**< Enable DopplerCorrection */
    UInt32       windowingScaleFactor;
    /**< Enable Windowing */
    UInt32       scaleFactors[RADAR_FFT_MAX_NUM_STAGES];
    /**< Enable Windowing */
    UInt32       interferenceThreshold;
    /**< Enable Windowing */
    UInt32      windowCoeffAddr[RADAR_FFT_NUM_POINTS_MAX];
    /**< Window coefficient buffer addresses supported */
    UInt8        enableOverFlowDetection;
    /**< Set it to 1 to enable overflow detection else set it to zero.
     * If enabled the applet will return the scale factors to be applied
     * at each stage as part of outArgs. if scale factors are zero for
     * each stage then there is no overflow detected.
     */
    UInt8        outputContainerFormat;
    /**< Output container format. Care should be taken as the input
     *   format for the FFT operation (Horizontal or Vertical) is 16-bit.
     *   If you set the outputContainerFormat is set as 32 bit for First
     *   dimension FFT then the second Dimension would not be able to
     *   take this input.
     */
}AlgorithmFxn_RadarFftAlgCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure is used to describe the buffers output params from fft alg
 *
 *******************************************************************************
*/
typedef struct
{
    FFT_TI_BufferDescriptor bufDesc;
    /**< Buffer Descriptor parameters */
    UInt32       profileId;
    /**< Index of the profile for which the frame is generated */
}AlgorithmFxn_RadarFftBuffDescriptor;
/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_RadarProcessCreateParams baseClassCreateParams;
    /**< Base Class Create Parameters. This should be the first element
     *   of this structure.
     */
    ChainsCommon_Ar12xxConfigOut *pRadarCfg;
    /**< Radar Configurations */
    System_VideoDataFormat              dataFormat;
    /**< Input Data Format */
    AlgorithmFxn_RadarFftAlgMode        algFFTMode;
    /**< Alg mode in which is applicable refer #AlgorithmFxn_RadarFftAlgMode */
    AlgorithmFxn_RadarFftAlgCreateParams algCreatePrm[RADAR_FFT_MAX_CONFIG];
    /**< create time params for fft algo */
    UInt32                              workQcpuId;
    /**< Work Q CPU Id for running */
} AlgorithmFxn_RadarFftCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Object Draw
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_RadarProcessControlParams baseClassControl;
    /**< Base class control parameters */
    UInt32 reserved;
    /**< Reserved parameter */
} AlgorithmFxn_RadarFftControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarFft_Init(
                                AlgorithmFxn_RadarFftCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarFft_Init(
    AlgorithmFxn_RadarFftCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    /* Update the size of the parameter */
    pPrm->baseClassCreateParams.baseClassCreate.size = (UInt32)
                                sizeof(AlgorithmFxn_RadarFftCreateParams);
    strcpy(pPrm->baseClassCreateParams.algFxnName, "ti.radar.fft");
    pPrm->dataFormat = SYSTEM_DF_BAYER_BGGR;
    pPrm->pRadarCfg = NULL;
}

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
AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarFft_getFunctions(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
