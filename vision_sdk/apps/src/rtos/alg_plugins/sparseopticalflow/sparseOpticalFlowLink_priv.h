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
 * \ingroup ALGORITHM_LINK_API
 * \defgroup ALGORITHM_LINK_IMPL Algorithm Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file sparseOpticalFlowLink_priv.h Sparse Optical Flow Link private API/Data
 *       structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.0 (Apr 2013) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef _SPARSEOPTICALFLOW_LINK_PRIV_H_
#define _SPARSEOPTICALFLOW_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_sparseOpticalFlow.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <algorithms/pyramid_lk_sof/algo/inc/isof_ti.h>
#include <edma_utils/edma_utils_memcpy.h>
#include <src/rtos/alg_plugins/common/include/alg_ivision.h>
#include <src/rtos/utils_common/include/utils_link_stats_if.h>

/*******************************************************************************
 *  Enums
 *******************************************************************************
 */


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define SOF_ALGLINK_PAD_PIXELS                  (16)

#define SOF_ALGLINK_TRACK_POINTS_MAX            (1200)
#define SOF_ALGLINK_FLOW_TRACK_POINTS_BUF_SIZE  (SOF_ALGLINK_TRACK_POINTS_MAX*sizeof(strackInfo))


/**
 *******************************************************************************
 *
 *   \brief Max number of buffers
 *
 *   SOF generates flow vectors for the objects in the frame. Flow vectors
 *   give the direction of motion of the object. The SOF algorithm generates
 *   flow vectors for a group of pixels.
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define SPARSEOPTICALFLOW_LINK_MAX_NUM_OUTPUT    (8)

/**
 *******************************************************************************
 *
 *   \brief Max number of channels
 *
 *******************************************************************************
 */
#define SPARSEOPTICALFLOW_LINK_MAX_CH             (5)


/**
 *******************************************************************************
 *
 *   \brief Size of meta data buffer for SFM input data
 *
 *******************************************************************************
 */
#define SPARSEOPTICALFLOW_SFM_META_DATA_MAX_SIZE      (256)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

typedef struct
{
    Void               *algSofHandle;
    SOF_TI_CreateParams algSofCreateParams;

    SOF_TI_InArgs       algSofInArgs;
    SOF_TI_OutArgs      algSofOutArgs;

    IVISION_InBufs      algSofInBufs;
    IVISION_OutBufs     algSofOutBufs;

    IVISION_BufDesc     algSofInBufDescImage;
    IVISION_BufDesc     algSofInBufDescKeyPoints;
    IVISION_BufDesc    *algSofInBufDesc[2];

    IVISION_BufDesc     algSofOutBufDescKeyPoints;
    IVISION_BufDesc     algSofOutBufDescErrEst;
    IVISION_BufDesc     algSofOutBufDescTrackedPoints;
    IVISION_BufDesc    *algSofOutBufDesc[3];

    Void               *pAlgSofOutBufKeyPoints;
    Void               *pAlgSofOutBufErrEst;
    Void               *pAlgSofOutBufTrackedPoints;

    UInt32             algSofOutBufSizeKeyPoints;
    UInt32             algSofOutBufSizeErrEst;
    UInt32             algSofOutBufSizeTrackedPoints;

    System_Buffer buffers[SPARSEOPTICALFLOW_LINK_MAX_NUM_OUTPUT];
    /**< System buffers to exchange data with next link */

    System_MetaDataBuffer metaDataBuffers[SPARSEOPTICALFLOW_LINK_MAX_NUM_OUTPUT];
    /**< Payload for the system buffers */

} AlgorithmLink_SparseOpticalFlowChObj;


/**
 *******************************************************************************
 *
 *   \brief Structure containing sparse optical flow algorithm link
 *          parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_SparseOpticalFlowCreateParams algLinkCreateParams;

    AlgorithmLink_SparseOpticalFlowChObj
                chObj[SPARSEOPTICALFLOW_LINK_MAX_CH];

    AlgorithmLink_InputQueueInfo  inputQInfo;
    /**< All the information about input Queue*/

    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Queue*/

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */

} AlgorithmLink_SparseOpticalFlowObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_sparseOpticalFlowCreate(void * pObj,
                                              void * pCreateParams);
Int32 AlgorithmLink_sparseOpticalFlowProcess(void * pObj);
Int32 AlgorithmLink_sparseOpticalFlowControl(void * pObj,
                                               void * pControlParams);
Int32 AlgorithmLink_sparseOpticalFlowStop(void * pObj);
Int32 AlgorithmLink_sparseOpticalFlowDelete(void * pObj);
Int32 AlgorithmLink_sparseOpticalFlowPrintStatistics(void *pObj,
                AlgorithmLink_SparseOpticalFlowObj *pSparseOpticalFlowObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
