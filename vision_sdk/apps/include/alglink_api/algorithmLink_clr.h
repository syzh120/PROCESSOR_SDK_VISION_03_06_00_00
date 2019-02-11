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
 * \defgroup ALGORITHM_LINK_CLR  Circular Light Recognition API
 *
 * \brief  This module has the interface for using Circular Light Recognition
 *         algorithm
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_clr.h
 *
 * \brief Algorithm Link API specific to algorithm
 *
 * \version 0.0 (Feb 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_CLR_H_
#define ALGORITHM_LINK_CLR_H_

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
 * Maximum number of color lights to be dected
 */
#define ALGORITHM_LINK_CLR_MAX_NUM_COLOR_LIGHTS   (2)


/**
 * Maximum number of radii for which CLR will be performed
 */
#define ALGORITHM_LINK_CLR_MAX_NUM_RADIUS   (32)


/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup ALGORITHM_LINK_CLR_CMD CLR Control Commands
 *   @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Alg Link Config CMD: Enable/Disable algorithm
 *
 *   \param AlgorithmLink_ClrAlgParams [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_CLR_CMD_SET_PARAMS     (0x3000)

/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Parameters to set specific ROI
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    UInt32 lightBrightnessThr[ALGORITHM_LINK_CLR_MAX_NUM_COLOR_LIGHTS];
    /**< Light Brightness Threshold */
    UInt32 lightColor[ALGORITHM_LINK_CLR_MAX_NUM_COLOR_LIGHTS];
    /**< Light color Threshold */
    UInt32 lightThr1[ALGORITHM_LINK_CLR_MAX_NUM_COLOR_LIGHTS];
    /**< Light Threshold1 */
    UInt32 lightThr2[ALGORITHM_LINK_CLR_MAX_NUM_COLOR_LIGHTS];
    /**< Light Threshold2 */
    UInt32 falseFilterThr[ALGORITHM_LINK_CLR_MAX_NUM_COLOR_LIGHTS];
    /**< False Filter Threshold */
    UInt32 numRadius;
    /**< Number of Radius  */
    UInt32 radius[ALGORITHM_LINK_CLR_MAX_NUM_RADIUS];
    /**< Radius */
    UInt32 circleDetectionThr[ALGORITHM_LINK_CLR_MAX_NUM_RADIUS];
    /**< Circle Detection Threshold */
    UInt32 scalingFactor[ALGORITHM_LINK_CLR_MAX_NUM_RADIUS];
    /**< Scaling Factor */
    UInt32 morphologyMethod;
    /**< Morphology Method */
    UInt32 groupingWindowSize;
    /**< Grouping Window Size */

    UInt32 roiStartX;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */
    UInt32 roiStartY;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */
    UInt32 roiWidth;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */
    UInt32 roiHeight;
    /**< ROI to process relative within imgFrameWidthximgFrameHeight */
} AlgorithmLink_ClrAlgParams;


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

} AlgorithmLink_ClrCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_ClrControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmLink_Clr_Init(
                            AlgorithmLink_ClrCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_Clr_Init(
    AlgorithmLink_ClrCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AlgorithmLink_ClrCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                                sizeof(AlgorithmLink_ClrCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_CLR;

    pPrm->imgFrameStartX    = 0U;
    pPrm->imgFrameStartY    = 0U;
    pPrm->imgFrameWidth     = 1280U;
    pPrm->imgFrameHeight    = 720U;

    pPrm->roiStartX    = 0U;
    pPrm->roiStartY    = 0U;
    pPrm->roiWidth     = 1280U;
    pPrm->roiHeight    = 720U;

    pPrm->inQueParams.prevLinkId = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
    pPrm->numOutBuffers = 3U;
    pPrm->outQueParams.nextLink = SYSTEM_LINK_ID_INVALID;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_clr_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
