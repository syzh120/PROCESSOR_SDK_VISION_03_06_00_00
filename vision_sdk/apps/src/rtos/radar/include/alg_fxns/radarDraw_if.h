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
 * \file radarDraw_if.h
 *
 * \brief Plugin that draws the radar output on the display
 *
 * \version 0.0 (Sept 2016) : [PG] First version
 *
 *******************************************************************************
 */

#ifndef ALG_FXN_RADAR_DRAW_H_
#define ALG_FXN_RADAR_DRAW_H_

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

/**< \brief Max nummber of input algos for drawing */
#define ALG_FXN_RADAR_DRAW_MAX_DRAW_ALG     (8)

/**< \brief Maximum Number of profiles which is possible from the AR device */
#define ALG_FXN_RADAR_DRAW_MAX_PROFILES     (4U)

/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup ALG_FXN_RADAR_DRAW_CMD \
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
typedef enum
{
    ALG_FXN_RADAR_DRAW_FFT_OUTPUT = 0x1,
    /**< Draw the radar FFT output */
    ALG_FXN_RADAR_DRAW_DETECT_OUTPUT = 0x2,
    /**< Draw the radar detection output */
    ALG_FXN_RADAR_DRAW_ALL_OUTPUT = 0x3,
    /**< Draw the all radar stage outputs */
    ALG_FXN_RADAR_DRAW_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} AlgorithmFxn_RadarDrawOption;

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for which object type the algorithm should draw.
 *
 *
 *******************************************************************************
*/
typedef enum
{
    ALG_FXN_RADAR_DRAW_ALG_FFT = 0,
    /**< Algorithm providing input is FFT */

    ALG_FXN_RADAR_DRAW_ALG_DETECT = 1,
    /**< Algorithm providing input is radar object detection */

    ALG_FXN_RADAR_DRAW_ALG_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} AlgorithmFxn_RadarDrawAlgId;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Parameters to set drawing parameters
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_RadarProcessControlParams baseClassControl;
    /**< Base class control params */

    AlgorithmFxn_RadarDrawOption drawOption;
    /**< Algo information to draw */

} AlgorithmFxn_RadarDrawSetDrawParams;

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
    UInt32                   imgFrameWidth;
    /**< Width of frame which is to be output by the algorithm function */
    UInt32                   imgFrameHeight;
    /**< Height of frame which is to be output by the algorithm function */
    UInt32                   numDrawAlg;
    /**< Number of different algorithms for which drawing is required */
    AlgorithmFxn_RadarDrawAlgId drawAlgId[ALG_FXN_RADAR_DRAW_MAX_DRAW_ALG];
    /**< ID of the algorithm for which drawing is required */
    AlgorithmFxn_RadarDrawOption drawOption;
    /**< Option of Object to Draw */
    UInt32 scale;
    /**< Scale of the Cone */
    float                    rangeRes[ALG_FXN_RADAR_DRAW_MAX_PROFILES];
    /**< Range Resolution */
    float                    velocityRes[ALG_FXN_RADAR_DRAW_MAX_PROFILES];
    /**< Velocity Resolution */
    float                    azimAngleRes[ALG_FXN_RADAR_DRAW_MAX_PROFILES];
    /**< Azimuth Angle Resolution */
    float                    elevAngleRes[ALG_FXN_RADAR_DRAW_MAX_PROFILES];
    /**< Elevation Angle Resolution */
    UInt32                   maxVelocityBinNum[ALG_FXN_RADAR_DRAW_MAX_PROFILES];
    /**< Maximum Velocity Bin Number */
    UInt32                   numProfiles;
    /**< Number of profiles for the heat map creation */
    UInt32                   numHorzAngles;
    /**< Number of Horizontal Angles */
    UInt32                   numVertAngles;
    /**< Number of Vertical Angles */
} AlgorithmFxn_RadarDrawCreateParams;

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
    /**< Profile Id */
    float                    rangeRes;
    /**< Range Resolution */
    float                    velocityRes;
    /**< Velocity Resolution */
    float                    azimAngleRes;
    /**< Azimuthal Resolution */
    float                    elevAngleRes;
    /**< Elevation Angle Resolution */
} AlgorithmFxn_RadarDrawControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarDraw_Init(
                                AlgorithmFxn_RadarDrawCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmFxn_RadarDraw_Init(
    AlgorithmFxn_RadarDrawCreateParams *pPrm)
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
                                sizeof(AlgorithmFxn_RadarDrawCreateParams);
    strcpy(pPrm->baseClassCreateParams.algFxnName, "ti.radar.draw");
    pPrm->imgFrameWidth     = 1920U;
    pPrm->imgFrameHeight    = 1080U;
    pPrm->numDrawAlg = 1U;
    pPrm->drawAlgId[0] = ALG_FXN_RADAR_DRAW_ALG_DETECT;
    pPrm->drawOption = ALG_FXN_RADAR_DRAW_DETECT_OUTPUT;
    pPrm->scale = 1;
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
AlgRadarProcessFxns_FxnTable * AlgorithmFxn_RadarDraw_getFunctions(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
