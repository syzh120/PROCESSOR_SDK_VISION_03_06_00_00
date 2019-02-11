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
 * \file featurePlaneCompLink_priv.h Feature Plane Computation Algorithm Link
 *       private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.0 (Nov 2015) : [YM] First version
 *
 *******************************************************************************
 */

#ifndef _FPCOMPUTE_LINK_PRIV_H_
#define _FPCOMPUTE_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_fpCompute.h>
#include <include/alglink_api/algorithmLink_imgPyramid.h>
#include <include/alglink_api/algorithmLink_imagePreProcess.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/alg_plugins/common/include/alg_ivision.h>
#include <include/link_api/system_common.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <iti_pd_feature_plane_computation_ti.h>
#include <src/rtos/utils_common/include/utils_link_stats_if.h>


/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define FPCOMPUTE_LINK_MAX_NUM_OUTPUT    (8)


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

typedef struct
{
    Void * handle;

    PD_FEATURE_PLANE_COMPUTATION_CreateParams prms;
    PD_FEATURE_PLANE_COMPUTATION_InArgs inArgs;
    PD_FEATURE_PLANE_COMPUTATION_OutArgs outArgs;

    IVISION_InBufs    inBufs;
    IVISION_OutBufs   outBufs;
    IVISION_BufDesc   inBufDesc[ALGORITHLINK_IMGPYRAMID_MAX_SCALES];
    IVISION_BufDesc   outBufDesc;
    IVISION_BufDesc   *inBufDescList[ALGORITHLINK_IMGPYRAMID_MAX_SCALES];
    IVISION_BufDesc   *outBufDescList[PD_FEATURE_PLANE_COMPUTATION_BUFDESC_OUT_TOTAL];

} Alg_FPComputeObj;


/**
 *******************************************************************************
 *
 *   \brief Structure containing feature plane computation algorithm link
 *          parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef struct
{
    Alg_FPComputeObj algFPComputeObj;

    AlgorithmLink_FPComputeCreateParams algLinkCreateParams;
    /**< Create params of feature plane computation algorithm link */

    System_Buffer buffers[FPCOMPUTE_LINK_MAX_NUM_OUTPUT];
    /**< System buffers to exchange data with next link */

    System_MetaDataBuffer featurePlanes[FPCOMPUTE_LINK_MAX_NUM_OUTPUT];
    /**< Payload for the system buffers */

    UInt32  outBufferSize;
    /**< Size of each output buffer */

    AlgorithmLink_InputQueueInfo  inputQInfo;
    /**< All the information about input Queue*/

    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Queue*/

    System_LinkChInfo inChInfo;
    /**< Information about input channel */

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

    UInt64 fpComputeTime;
    UInt64 frameCount;

} AlgorithmLink_FPComputeObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_fpComputeCreate(void * pObj,
                                              void * pCreateParams);
Int32 AlgorithmLink_fpComputeProcess(void * pObj);
Int32 AlgorithmLink_fpComputeControl(void * pObj,
                                               void * pControlParams);
Int32 AlgorithmLink_fpComputeStop(void * pObj);
Int32 AlgorithmLink_fpComputeDelete(void * pObj);
Int32 AlgorithmLink_fpComputePrintStatistics(void *pObj,
                AlgorithmLink_FPComputeObj *pFPComputeObj);

Int32 Alg_fpComputeCreate(
            Alg_FPComputeObj *pObj,
            AlgorithmLink_ImgPyramidInfo * pImgpmfInfo,
            UInt32 *outBufSize);

Int32 Alg_fpComputeProcess(
            Alg_FPComputeObj *pObj,
            Void *inBufAddr,
            Void *outBufAddr);

Int32 Alg_fpComputeDelete(
            Alg_FPComputeObj *pObj);



#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
