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
 * \ingroup  ALGORITHM_LINK_PLUGIN
 * \defgroup ALGORITHM_LINK_LANEDETECT  Lane Detect API
 *
 * \brief  This module has the interface for using Lane Detect algorithm
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_laneDetect.h
 *
 * \brief Algorithm Link API specific to lane detect algorithm
 *
 * \version 0.0 (Feb 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_LANEDETECT_H_
#define ALGORITHM_LINK_LANEDETECT_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define LD_FILTER_TAP_X     (3U)


/**
 *******************************************************************************
 *
 *   \brief Alg Link Config CMD: Enable/Disable algorithm
 *
 *   \param AlgorithmLink_LaneDetectAlgParams [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_LD_CMD_SET_PARAMS     (0x4000)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params. This structure should be first element */
    System_LinkOutQueParams  outQueParams;
    /**< Output queue information */
    System_LinkInQueParams   inQueParams;
    /**< Input queue information */
    UInt32                   numOutBuffers;
    /**< Number of output Buffers */
    UInt32                   imgFrameStartX;
    /**< Start of actual video relative to start of input buffer */
    UInt32                   imgFrameStartY;
    /**< Start of actual video relative to start of input buffer */
    UInt32                   imgFrameWidth;
    /**< Width of the input frame */
    UInt32                   imgFrameHeight;
    /**< Height of the input frame */

    UInt32                   roiStartX;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */
    UInt32                   roiStartY;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */
    UInt32                   roiWidth;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */
    UInt32                   roiHeight;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */

    UInt32                   isImgPmdInputType;
    /**< TRUE: input is image pyramid from image pyramid algorithm,
        FALSE: input is video frame */

    UInt32                   imgPmdScaleIdx;
    /**< Index of scale to use as input for lane detect */

    /*   Lane Detect Advanced parmaeters,
     *   refer Lane detect algo user guide for more details
     */
    UInt32  cannyHighThresh;
    UInt32  cannyLowThresh;
    UInt32  houghNmsThresh;
    UInt32  startThetaLeft;
    UInt32  endThetaLeft;
    UInt32  startThetaRight;
    UInt32  endThetaRight;
    UInt32  thetaStepSize;
    UInt32  numHoughMaximasDet;
    UInt32  numHoughMaximasTrack;
    UInt32  trackingMethod;
    /* 0: tracking disable, 1: tracking enable */
    UInt32  warningMethod;
    /* 0: Warning disable, 1: warning enable */
    UInt32  departThetaLeftMin;
    UInt32  departThetaLeftMax;
    UInt32  departRhoLeftMin;
    UInt32  departRhoLeftMax;
    UInt32  departThetaRightMin;
    UInt32  departThetaRightMax;
    UInt32  departRhoRightMin;
    UInt32  departRhoRightMax;
    UInt32  maxRho;
    UInt32  enableLD;
    /**< Enable lane detection */


} AlgorithmLink_LaneDetectCreateParams;



typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    UInt32                   changeEnableLD;
    /**< When TRUE, the parameter enableLD is changed during the
     *              ALGORITHM_LINK_LD_CMD_SET_PARAMS call.
     *   When FALSE, the parameter enableLD is not changed.
     */

    UInt32                   enableLD;
    /**< Enables detection of lanes */

    UInt32                   enableAdvConfig;
    /**< When TRUE, parameters specified below are used,
     *   When FALSE, parameters specified below are not used
     */

    UInt32                   roiStartX;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */
    UInt32                   roiStartY;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */
    UInt32                   roiWidth;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */
    UInt32                   roiHeight;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */


    UInt32  cannyHighThresh;
    UInt32  cannyLowThresh;
    UInt32  houghNmsThresh;
    UInt32  startThetaLeft;
    UInt32  endThetaLeft;
    UInt32  startThetaRight;
    UInt32  endThetaRight;
    UInt32  thetaStepSize;
    UInt32  numHoughMaximasDet;
    UInt32  numHoughMaximasTrack;
    UInt32  trackingMethod;
    /* 0: tracking disable, 1: tracking enable */
    UInt32  warningMethod;
    /* 0: Warning disable, 1: warning enable */
    UInt32  departThetaLeftMin;
    UInt32  departThetaLeftMax;
    UInt32  departRhoLeftMin;
    UInt32  departRhoLeftMax;
    UInt32  departThetaRightMin;
    UInt32  departThetaRightMax;
    UInt32  departRhoRightMin;
    UInt32  departRhoRightMax;

} AlgorithmLink_LaneDetectAlgParams;


/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Lane detect algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_LaneDetectControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmLink_LaneDetect_Init(
                            AlgorithmLink_LaneDetectCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_LaneDetect_Init(
    AlgorithmLink_LaneDetectCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AlgorithmLink_LaneDetectCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                                sizeof(AlgorithmLink_LaneDetectCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_LANE_DETECT;
    pPrm->enableLD              = (UInt32) TRUE;

    pPrm->imgFrameStartX    = 0U;
    pPrm->imgFrameStartY    = 0U;
    pPrm->imgFrameWidth     = 640U;
    pPrm->imgFrameHeight    = 360U;

    pPrm->roiStartX     = 190U - LD_FILTER_TAP_X;
    pPrm->roiStartY     = 210U;
    pPrm->roiWidth      = 222U + (2U*LD_FILTER_TAP_X);
    pPrm->roiHeight     = 70U;

    pPrm->cannyHighThresh        = 60U;
    pPrm->cannyLowThresh         = 50U;
    pPrm->houghNmsThresh         = 10U;
    pPrm->startThetaLeft         = 0U;
    pPrm->endThetaLeft           = 150U;
    pPrm->startThetaRight        = 0U;
    pPrm->endThetaRight          = 150U;
    pPrm->thetaStepSize          = 1U;
    pPrm->numHoughMaximasDet     = 6U;
    pPrm->numHoughMaximasTrack   = 3U;
    pPrm->trackingMethod         = 1U;
    pPrm->warningMethod          = 1U;
    pPrm->departThetaLeftMin     = 126U;
    pPrm->departThetaLeftMax     = 135U;
    pPrm->departRhoLeftMin       = 126U;
    pPrm->departRhoLeftMax       = 140U;
    pPrm->departThetaRightMin    = 45U;
    pPrm->departThetaRightMax    = 48U;
    pPrm->departRhoRightMin      = 150U;
    pPrm->departRhoRightMax      = 152U;
    pPrm->maxRho                 = 232;


    pPrm->inQueParams.prevLinkId = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
    pPrm->numOutBuffers = 3U;
    pPrm->outQueParams.nextLink = SYSTEM_LINK_ID_INVALID;

    pPrm->isImgPmdInputType = FALSE;
    pPrm->imgPmdScaleIdx = 0;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of lane detect algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_laneDetect_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
