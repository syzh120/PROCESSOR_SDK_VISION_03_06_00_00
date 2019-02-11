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
 * \defgroup ALGORITHM_LINK_DENSEOPTICALFLOW_API  Dense\
 * Optical Flow API
 *
 * \brief  This module has the interface for using Dense Optical Flow algorithm
 *
 *         Dense Optical Flow algorithm link -
 *         - Takes the YUV video frame and process pixel by pixel.
 *         - Generate the horizontal and versical optical flow vectors.
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_denseOpticalFlow.h
 *
 * \brief Algorithm Link API specific to Dense Optical Flow algorithm
 *
 * \version 0.0 (Nov 2013) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_DENSEOPTICALFLOW_H_
#define ALGORITHM_LINK_DENSEOPTICALFLOW_H_

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
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief enum indication the number of levels of the image pyramid to use.
 *
 *
 *******************************************************************************
*/
typedef enum{
    ALGLINK_DENSEOPTFLOW_LKNUMPYR_1 = 1,
    ALGLINK_DENSEOPTFLOW_LKNUMPYR_2 = 2,
    ALGLINK_DENSEOPTFLOW_LKNUMPYR_3 = 3,
    ALGLINK_DENSEOPTFLOW_LKNUMPYR_4 = 4,
    ALGLINK_DENSEOPTFLOW_LKNUMPYR_5 = 5,
    ALGLINK_DENSEOPTFLOW_LKNUMPYR_MAX = 5,
    ALGLINK_DENSEOPTFLOW_LKNUMPYR_DEFAULT = 3,
    ALGLINK_DENSEOPTFLOW_LKNUMPYR_FORCE32BITS = 0x7FFFFFFF
} AlgorithmLink_DenseOptFlowLKnumPyr;

/**
 *******************************************************************************
 *
 *   \brief enum to set the size of the smoothing kernel used to preprocess
 *
 *
 *******************************************************************************
*/
typedef enum{
    ALGLINK_DENSEOPTFLOW_LKSMOOTHSIZE_3x3 = 3,
    ALGLINK_DENSEOPTFLOW_LKSMOOTHSIZE_5x5 = 5,
    ALGLINK_DENSEOPTFLOW_LKSMOOTHSIZE_7x7 = 7,
    ALGLINK_DENSEOPTFLOW_LKSMOOTHSIZE_MAX = 7,
    ALGLINK_DENSEOPTFLOW_LKSMOOTHSIZE_DEFAULT = 3,
    ALGLINK_DENSEOPTFLOW_LKSMOOTHSIZE_FORCE32BITS = 0x7FFFFFFF
} AlgorithmLink_DenseOptFlowLKsmoothSize;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for Dense Optical Flow
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params. This structure should be first element */
    AlgorithmLink_DenseOptFlowLKnumPyr      numPyramids;
    /**< Number of levels in the pyramid used in the algorithm */
    UInt32                   enableSmoothing;
    /**< Enables image smoothing before processing. 1:enable 0:disable */
    AlgorithmLink_DenseOptFlowLKsmoothSize  smoothingSize;
    /**< Sets the width and height of the smoothing kernel.
      *  Setting enableSmoothing to 0 will cause this value to be unused.*/
    UInt32                   maxVectorSizeX;
    /**< Clips u vectors (horizontal) to this magnitude */
    UInt32                   maxVectorSizeY;
    /**< Clips v vectors (vertical) to this magnitude */
    UInt32                   processPeriodicity;
    /**< Indicates the periodicity of processing input. If set as four, it
      *  means once every four input frames, actual algorithm processing
      *  will be done
      *
      *  ONLY valid when AlgorithmLink_DenseOptFlowCreateParams.roiEnable
      *  is FALSE
      */
    UInt32                   processStartFrame;
    /**< Indicates the first frame (Input) number which should be picked up
      *  for processing. Frame (Input) number begins from 0
      *
      *  ONLY valid when AlgorithmLink_DenseOptFlowCreateParams.roiEnable
      *  is FALSE
      */
    System_LinkOutQueParams  outQueParams;
    /**< Output queue information */
    System_LinkInQueParams   inQueParams;
    /**< Input queue information */

    UInt32                   numOutBuf;
    /**< Number of output buffer to allocate */

    UInt32                   algEnable;
    /**< Debug flag to control algorithm enable/disable */

    UInt32                   roiEnable;
    /**< Enable ROI based processing */

    AlgorithmLink_RoiParams  roiParams;
    /**< ROI params */

} AlgorithmLink_DenseOptFlowCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for Dense Optical Flow
 *          algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_DenseOptFlowControlParams;

/*******************************************************************************
 *  Function Prototypes
 *******************************************************************************
 */
static inline void AlgorithmLink_DenseOptFlowCreateParams_Init(
    AlgorithmLink_DenseOptFlowCreateParams *pPrm);

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
static inline void AlgorithmLink_DenseOptFlowCreateParams_Init(
    AlgorithmLink_DenseOptFlowCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AlgorithmLink_DenseOptFlowCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                                sizeof(AlgorithmLink_DenseOptFlowCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_EVE_ALG_DENSE_OPTICAL_FLOW;

    pPrm->numPyramids     = ALGLINK_DENSEOPTFLOW_LKNUMPYR_1;
    pPrm->enableSmoothing = (UInt32)TRUE;
    pPrm->smoothingSize   = ALGLINK_DENSEOPTFLOW_LKSMOOTHSIZE_3x3;
    pPrm->maxVectorSizeX  = 16U;
    pPrm->maxVectorSizeY  = 16U;
    pPrm->processPeriodicity = 1U;
    pPrm->processStartFrame = 1U;

    pPrm->inQueParams.prevLinkId = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;

    pPrm->outQueParams.nextLink = SYSTEM_LINK_ID_INVALID;

    pPrm->numOutBuf = 4U;

    pPrm->roiEnable = (UInt32)FALSE;
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of Dense Optical Flow algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_DenseOptFlow_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */

