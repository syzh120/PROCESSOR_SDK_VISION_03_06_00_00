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
 * \defgroup ALGORITHM_LINK_OCL_OBJECTDETECTION Object detection API
 *
 * \brief  This module has the interface for using feature plane classification
 *         algorithm
 *         Feature Plane classification algorithm link -
 *             1. This alg takes input from feature plane compute link
 *                and generates co-ordinates of the rectangles where
 *                objects are present in the frame
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_objectDetection.h
 *
 * \brief Algorithm Link API specific to feature plane classification algorithm
 *
 * \version 0.0 (Feb 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_OBJECTDETECTION_H_
#define ALGORITHM_LINK_OBJECTDETECTION_H_

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


/**
 *******************************************************************************
 *
 * \ingroup LINK_API_CMD
 * \addtogroup ALGORITHM_LINK_OCL_OBJECT_DETECT_CMD Object Detect Control
 *             Commands
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Alg Link Config CMD: Enable/Disable algorithm
 *
 *   \param AlgorithmLink_ObjectDetectEnableAlgParams [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_OBJECT_DETECT_CMD_ENABLE_ALG     (0x2000)

/* @} */

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

    UInt32                   enablePD;
    /**< Enabled detection of Pedestrians */
    UInt32                   enableTSR;
    /**< Enabled detection of Traffic signs */
    UInt32                   enableVD;
    /**< Enabled detection of Vehicle's */

    UInt32                   enableAdvConfig;
    /**< When TRUE, parameters specified below are used,
     *   When FALSE, parameters specified below are not used
     */
    UInt32 detectorTypePD;
    /**< Advanced parameter, used for tuning algorithm */
    UInt32 trackingMethodPD;
    /**< Advanced parameter, used for tuning algorithm */
    UInt32 softCascadeThPD;
    /**< Advanced parameter, used for tuning algorithm */
    UInt32 strongCascadeThPD;
    /**< Advanced parameter, used for tuning algorithm */

    UInt32 detectorTypeTSR;
    /**< Advanced parameter, used for tuning algorithm */
    UInt32 trackingMethodTSR;
    /**< Advanced parameter, used for tuning algorithm */
    UInt32 recognitionMethodTSR;
    /**< Advanced parameter, used for tuning algorithm */
    UInt32 softCascadeThTSR;
    /**< Advanced parameter, used for tuning algorithm */
    UInt32 strongCascadeThTSR;
    /**< Advanced parameter, used for tuning algorithm */

    UInt32 detectorTypeVD;
    /**< Advanced parameter, used for tuning algorithm */
    UInt32 trackingMethodVD;
    /**< Advanced parameter, used for tuning algorithm */
    UInt32 softCascadeThVD;
    /**< Advanced parameter, used for tuning algorithm */
    UInt32 strongCascadeThVD;
    /**< Advanced parameter, used for tuning algorithm */

} AlgorithmLink_ObjectDetectEnableAlgParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for feature plane
 *          classification algorithm
 *
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
    /**< Number of output buffers */
    UInt32                   enablePD;
    /**< Enabled detection of Pedestrians */
    UInt32                   enableTSR;
    /**< Enabled detection of Traffic signs */
    UInt32                   enableVD;
    /**< Enabled detection of Vehicles */
    UInt32                   imgFrameWidth;
    /**< Width of the input frame */
    UInt32                   imgFrameHeight;
    /**< Height of the input frame */
} AlgorithmLink_ObjectDetectionCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Geometric Alignment
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_ObjectDetectionControlParams;

/*******************************************************************************
 *  Function Prototypes
 *******************************************************************************
 */
static inline void AlgorithmLink_ObjectDetection_Init(
                        AlgorithmLink_ObjectDetectionCreateParams *pPrm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_ObjectDetection_Init(
    AlgorithmLink_ObjectDetectionCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AlgorithmLink_ObjectDetectionCreateParams));

    pPrm->baseClassCreate.size      = (UInt32)
                            sizeof(AlgorithmLink_ObjectDetectionCreateParams);
    pPrm->baseClassCreate.algId     = ALGORITHM_LINK_DSP_ALG_OBJECTDETECTION;
    pPrm->inQueParams.prevLinkId    = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
    pPrm->outQueParams.nextLink     = SYSTEM_LINK_ID_INVALID;
    pPrm->numOutBuffers             = 4U;
    pPrm->enablePD                  = (UInt32) TRUE;
    pPrm->enableTSR                 = (UInt32) FALSE;
    pPrm->enableVD                  = (UInt32) FALSE;
    pPrm->imgFrameWidth             = 640U;
    pPrm->imgFrameHeight            = 360U;

}


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of feature plane classification algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_ObjectDetection_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
