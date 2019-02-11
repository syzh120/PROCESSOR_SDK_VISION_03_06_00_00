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
 * \file disparityHamDistLink_priv.h Disparity Haming Distance Algorithm Link
 *       private API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.1 (Sept 2014) : [SR] First version
 *
 *******************************************************************************
 */

#ifndef _DISPARITY_HAMDIST_LINK_PRIV_H_
#define _DISPARITY_HAMDIST_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_disparityHamDist.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <apps/disparity/algo/inc/iDisparity_ti.h>
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

/**
 *******************************************************************************
 *
 *   \brief Threshold size beyond which memory gets allocated in Shared area
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DISPARITY_HAMDIST_ALGLINK_SRMEM_THRESHOLD (ALGORITHMLINK_SRMEM_THRESHOLD)

/**
 *******************************************************************************
 *
 *   \brief Max number of channels per output queue
 *
 *   Census alg works on Stereo sensors - so 2 channels data the link can
 *   handle
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DISPARITY_HAMDIST_MAX_CH_PER_OUT_QUE    (2)

/**
 *******************************************************************************
 *
 *   \brief Max number of buffers
 *
 *   Soft Isp alg takes an input frame and generates an output
 *   frame. The format of output is not known. It can be considered as a meta
 *   data buffer. This macro defines the maximum number of such buffers this
 *   link can handle
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DISPARITY_HAMDIST_LINK_MAX_NUM_OUTPUT    (6)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

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
    System_LinkOutQueParams         outQueParams;
    /**< Output queue information */
    System_LinkInQueParams          inQueParams;
    /**< Input queue information */
    AlgorithmLink_InputQueueInfo    inputQInfo;
    /**< All the information about input Queue*/
    AlgorithmLink_OutputQueueInfo   outputQInfo;
    /**< All the information about output Queue*/
    UInt32                          numInputChannels;
    /**< Number of input channels on input Q (Prev link output Q) */
    System_LinkChInfo       inputChInfo[DISPARITY_HAMDIST_MAX_CH_PER_OUT_QUE];
    /**< channel info of input */

    Void *               handle;
    Void *               rlHandle; /* to hold handle for the instance in charge of performing right to left execution */
    
    /**< Handle to the algorithm */
    AlgorithmLink_DisparityHamDistCreateParams    algLinkCreateParams;
    /**< Create params of soft isp algorithm link */
    DISPARITY_TI_CreateParams   algCreateParams;
    DISPARITY_TI_CreateParams   rlAlgCreateParams; /* for right to left execution */
    /**< Create parameters for the algorithm */
    IVISION_InArgs          inArgs;
    /**< inArgs for the algorithm */
    DISPARITY_TI_outArgs    outArgs;
    /**< outArgs for the algorithm */

    IVISION_InBufs          inBufs;
    IVISION_InBufs          rlInBufs;
    /**< input buffers for the algorithm */
    IVISION_OutBufs         outBufs;
    IVISION_OutBufs         rlOutBufs;
    /**< output buffers for the algorithm */
    IVISION_BufDesc     inBufDesc[DISPARITY_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc     rlInBufDesc[DISPARITY_TI_BUFDESC_IN_TOTAL];
    /**< input buffer descriptor */
    IVISION_BufDesc     outBufDesc[DISPARITY_TI_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc     rlOutBufDesc[DISPARITY_TI_BUFDESC_OUT_TOTAL];
    /**< output buffer descriptor */
    IVISION_BufDesc     *inBufDescList[DISPARITY_TI_BUFDESC_IN_TOTAL];
    IVISION_BufDesc     *rlInBufDescList[DISPARITY_TI_BUFDESC_IN_TOTAL];
    /**< list of input buffer descriptors */
    IVISION_BufDesc     *outBufDescList[DISPARITY_TI_BUFDESC_OUT_TOTAL];
    IVISION_BufDesc     *rlOutBufDescList[DISPARITY_TI_BUFDESC_OUT_TOTAL];
    /**< list of input buffer descriptors */
    System_Buffer       buffers[DISPARITY_HAMDIST_LINK_MAX_NUM_OUTPUT];
    System_Buffer       rlBuffers[DISPARITY_HAMDIST_LINK_MAX_NUM_OUTPUT];
    /**< System buffers to exchange data with next link */
    System_MetaDataBuffer   disparityHamDistOpBuffers
                                [DISPARITY_HAMDIST_LINK_MAX_NUM_OUTPUT];
    System_MetaDataBuffer   rlDisparityHamDistOpBuffers
                                [DISPARITY_HAMDIST_LINK_MAX_NUM_OUTPUT];
    /**< Payload for the system buffers System_MetaDataBuffer */
    UInt32                  outBufferSize;
    UInt32                  rlOutBufferSize;
    /**< Size of each output buffer */
    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool                    isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */
} AlgorithmLink_DisparityHamDistObj;

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_disparityHamDistCreate
                                        (void * pObj, void * pCreateParams);
Int32 AlgorithmLink_disparityHamDistProcess(void * pObj);
Int32 AlgorithmLink_disparityHamDistControl
                                        (void * pObj, void * pControlParams);
Int32 AlgorithmLink_disparityHamDistStop(void * pObj);
Int32 AlgorithmLink_disparityHamDistDelete(void * pObj);
Int32 AlgorithmLink_disparityHamDistPrintStatistics
        (void *pObj, AlgorithmLink_DisparityHamDistObj *pDisparityHamDistObj);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
