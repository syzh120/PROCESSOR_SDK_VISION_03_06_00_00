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
 * \ingroup  ALGORITHM_FUNCTION
 * \defgroup ALGORITHM_RADARDRAW  Object Draw Link API
 *
 * \brief  This file contains plug in functions for drawing the radar
 *         processing output
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file radarDrawFFTHeatMap_if.h
 *
 * \brief Plugin that draws the radar output on the display
 *
 * \version 0.0 (Sept 2016) : [PG] First version
 *
 *******************************************************************************
 */

#ifndef ALG_FXN_RADAR_DRAW_FFT_HEATMAP_H_
#define ALG_FXN_RADAR_DRAW_FFT_HEATMAP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_radarProcess.h>
#include <include/common/alg_functions.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Max nummber of input algos for drawing
 *
 *******************************************************************************
 */
#define ALG_FXN_RADAR_DRAW_FFT_HEATMAP_MAX_NUM_BUFFERS     (3U)

#define ALG_FXN_RADAR_DRAW_FFT_HEATMAP_MAX_BINS            (32U)

/**< \brief Maximum Number of profiles which is possible from the AR device */
#define ALG_FXN_RADAR_DRAW_FFT_HEATMAP_MAX_PROFILES  (4U)

/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup ALG_FXN_RADAR_DRAW_FFT_HEATMAP_CMD \
 *                  Object Detect Draw Control Commands
 *   @{
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 *  \brief  Enumerations for which type the algorithm should draw.
 *
 *
 *******************************************************************************
*/


/**
 *******************************************************************************
 *
 *  \brief  Enumerations for which object type the algorithm should draw.
 *
 *
 *******************************************************************************
*/


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

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
    UInt32                    outBufWidth;
    /**< Output Buffer Width */
    float                    rangeRes[ALG_FXN_RADAR_DRAW_FFT_HEATMAP_MAX_PROFILES];
    /**< Range Resolution */
    float                    velocityRes[ALG_FXN_RADAR_DRAW_FFT_HEATMAP_MAX_PROFILES];
    /**< Velocity Resolution */
    UInt32                    outBufHeight;
    /**< Output Buffer Height */
    UInt32                    outBufStartX;
    /**< OutputBuffer Position */
    UInt32                    outBufStartY;
    /**< OutputBuffer Position */
    UInt32                    numBuffers;
    /**< Number of output buffers to be allocated */
    UInt32                    numBins;
    /**< Number of bins for displaying heat*/
    UInt32                    binRange[ALG_FXN_RADAR_DRAW_FFT_HEATMAP_MAX_BINS];
    /**< Bin Range, assumed index0 has lowest bin range */
    UInt32                    rgb565Color[ALG_FXN_RADAR_DRAW_FFT_HEATMAP_MAX_BINS];
    /**< Color for the bins */
    UInt32                    numTxAntenna[ALG_FXN_RADAR_DRAW_FFT_HEATMAP_MAX_PROFILES];
    /**< Number of transmit antenna active */
    UInt32                    numRxAntenna[ALG_FXN_RADAR_DRAW_FFT_HEATMAP_MAX_PROFILES];
    /**< Number of recieve antenna active */
    UInt32                    numProfiles;
    /**< Number of profiles for the heat map creation */
} AlgorithmFxn_RadarDrawFFTHeatMapCreateParams;

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
    UInt32 profileId;
    /**< Profile ID of the heat map to be shown */
    UInt32 reserved;
    /**< Used for aligning the float words for DSP */
    float rangeRes;
    /**< Range Resolution */
    float velocityRes;
    /**< Velocity Resolution */
} AlgorithmFxn_RadarDrawFFTHeatMapControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarDrawFFTHeatMap_Init(
                                AlgorithmFxn_RadarDrawFFTHeatMapCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarDrawFFTHeatMap_Init(
    AlgorithmFxn_RadarDrawFFTHeatMapCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    pPrm->baseClassCreateParams.baseClassCreate.size = (UInt32)
                                sizeof(AlgorithmFxn_RadarDrawFFTHeatMapCreateParams);
    strcpy(pPrm->baseClassCreateParams.algFxnName, "ti.radar.drawfftheatmap");
    pPrm->numBuffers = ALG_FXN_RADAR_DRAW_FFT_HEATMAP_MAX_NUM_BUFFERS;
    pPrm->numBins = 1U;
    pPrm->binRange[0U] = 0xFFFFFFFFU;
    pPrm->rgb565Color[0U] = 0xFFFFU;
    pPrm->outBufWidth = 720;
    pPrm->outBufHeight = 480;
    pPrm->outBufStartX = 0;
    pPrm->outBufStartY = 0;
    pPrm->rangeRes[0] = 1.0;
    pPrm->velocityRes[0]  = 1.0;
    pPrm->numRxAntenna[0] = 4;
    pPrm->numTxAntenna[0]  = 1;
    pPrm->numProfiles  = 1;

    return;
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
AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarDrawFFTHeatMap_getFunctions(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
