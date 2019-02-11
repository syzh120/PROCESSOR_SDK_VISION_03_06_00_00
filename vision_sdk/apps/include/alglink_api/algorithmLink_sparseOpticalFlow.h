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
 * \defgroup ALGORITHM_LINK_SPARSEOPTICALFLOW Sparse Optical Flow API
 *
 * \brief  This module has the interface for using SOF algorithm
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_sparseOpticalFlow.h
 *
 * \brief Algorithm Link API specific to feature plane computation algorithm
 *
 * \version 0.0 (Feb 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_SPARSEOPTICALFLOW_H_
#define ALGORITHM_LINK_SPARSEOPTICALFLOW_H_

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
#define PYRAMID_LK_TRACKER_TI_MAXLEVELS (8)


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 *  \brief  Enumerations for sof config.
 *
 *          Different configs need to be supported for different usecases
 *
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
    UInt32                   enableRoi;
    /**< Flag to enable/disable ROI */
    UInt32                   roiStartX;
    /**< Roi horizontal start position */
    UInt32                   roiStartY;
    /**< Roi vertical start position */
    UInt32                   roiWidth;
    /**< Width of ROI relative to frameWidth */
    UInt32                   roiHeight;
    /**< Height of ROI relative to frameHeight */
    UInt32                   trackErrThr;
    /**<Refer to isof_ti.h> */
    UInt32                   trackMinFlowQ4;
    /**<Refer to isof_ti.h> */
    UInt32                   trackNmsWinSize;
    /**<Refer to isof_ti.h> */
    UInt32                   numLevels;
    /**<Refer to isof_ti.h> */
    UInt32                   keyPointDetectMethod;
    /**<Refer to isof_ti.h> */
    UInt32                   keyPointDetectInterval;
    /**<Refer to isof_ti.h> */
    UInt32                   maxNumKeyPoints;
    /**<Refer to isof_ti.h> */
    UInt32                   maxPrevTrackPoints;
    /**<Refer to isof_ti.h> */
    UInt32                   fast9Threshold;
    /**<Refer to isof_ti.h> */
    UInt32                   scoreMethod;
    /**<Refer to isof_ti.h> */
    Int32                    harrisScaling;
    /**<Refer to isof_ti.h> */
    Int32                    nmsThreshold;
    /**<Refer to isof_ti.h> */
    UInt32                   harrisScoreMethod;
    /**<Refer to isof_ti.h> */
    UInt32                   harrisWindowSize;
    /**<Refer to isof_ti.h> */
    UInt32                   suppressionMethod;
    /**<Refer to isof_ti.h> */
    UInt32                   trackOffsetMethod;
    /**<Refer to isof_ti.h> */
    UInt32 maxItersLK[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
    /**<Refer to isof_ti.h> */
    UInt32 minErrValue[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
    /**<Refer to isof_ti.h> */
    UInt32  searchRange[PYRAMID_LK_TRACKER_TI_MAXLEVELS];
    /**<Refer to isof_ti.h> */
    Int32                    compositeBufferInput;
    /**< if >=0: Input is composite buffer and compositeBufferInput
     *           tells which buffer SOF operates on
     *   if =-1: Input is video frame buffer> */

} AlgorithmLink_SparseOpticalFlowCreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for SOF algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
} AlgorithmLink_SparseOpticalFlowControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmLink_SparseOpticalFlow_Init(
                        AlgorithmLink_SparseOpticalFlowCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_SparseOpticalFlow_Init(
    AlgorithmLink_SparseOpticalFlowCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    UInt32 i;
    memset(pPrm, 0, sizeof(AlgorithmLink_SparseOpticalFlowCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                            sizeof(AlgorithmLink_SparseOpticalFlowCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_EVE_ALG_SPARSE_OPTICAL_FLOW;

    pPrm->inQueParams.prevLinkId = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
    pPrm->numOutBuffers = 3U;
    pPrm->outQueParams.nextLink = SYSTEM_LINK_ID_INVALID;

    pPrm->imgFrameStartX    = 0U;
    pPrm->imgFrameStartY    = 0U;
    pPrm->imgFrameWidth     = 640U;
    pPrm->imgFrameHeight    = 360U;

    pPrm->enableRoi         = FALSE;
    pPrm->roiWidth          = 640U;
    pPrm->roiHeight         = 360U;
    pPrm->roiStartX         = 0U;
    pPrm->roiStartY         = 0U;

    pPrm->trackErrThr       = 441U;
    pPrm->trackMinFlowQ4    = 0U;
    pPrm->trackNmsWinSize   = 3U;

    pPrm->numLevels         = 5U;

    pPrm->keyPointDetectMethod = 1U;
    pPrm->keyPointDetectInterval = 0U;

    pPrm->maxNumKeyPoints    = 600U;
    pPrm->maxPrevTrackPoints = 600U;
    pPrm->fast9Threshold    = 80U;
    pPrm->scoreMethod = 0U;
    pPrm->harrisScaling     = 1350;
    pPrm->nmsThreshold      = 1350;
    pPrm->harrisScoreMethod = 1U;
    pPrm->harrisWindowSize = 2U;
    pPrm->suppressionMethod = 0U;
    pPrm->trackOffsetMethod = 0U;

    pPrm->maxItersLK[0U]  = 8U;
    pPrm->maxItersLK[1U]  = 7U;
    pPrm->maxItersLK[2U]  = 7U;
    pPrm->maxItersLK[3U]  = 6U;
    pPrm->maxItersLK[4U]  = 6U;
    pPrm->maxItersLK[5U]  = 10U;
    pPrm->maxItersLK[6U]  = 10U;
    pPrm->maxItersLK[7U]  = 10U;

    for(i=0U; i<(UInt32)PYRAMID_LK_TRACKER_TI_MAXLEVELS;i++)
    {
         pPrm->minErrValue[i] = 51U;
         pPrm->searchRange[i] = 12U;
    }

    pPrm->compositeBufferInput   = -1;

}


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of sparse optical flow algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_sparseOpticalFlow_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
