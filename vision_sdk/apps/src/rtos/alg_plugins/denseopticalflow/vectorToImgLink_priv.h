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
 * \file vectorToImageLink_priv.h Vector to Image Algorithm Link private
 *                            API/Data structures
 *
 * \brief  This link private header file has defined
 *         - Algorithm link instance/handle object
 *         - All the local data structures
 *         - Algorithm plug in function interfaces
 *
 * \version 0.0 (Nov 2013) : [PS] First version
 *
 *******************************************************************************
 */

#ifndef _VECTORTOIMAGE_LINK_PRIV_H_
#define _VECTORTOIMAGE_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_vectorToImage.h>
#include <include/link_api/algorithmLink_algPluginSupport.h>
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_que.h>
#include <src/rtos/utils_common/include/utils_mem.h>
#include <include/link_api/system_common.h>

#include "vectorToImgLink_dma.h"
#include <src/rtos/utils_common/include/utils_link_stats_if.h>


/*******************************************************************************
 *  Enums
 *******************************************************************************
 */

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define ALG_VECTOR_TO_IMAGE_ENABLE_DMA      (1)

#define ALG_VECTOR_TO_IMAGE_LUT_BPP         (2)
#define ALG_VECTOR_TO_IMAGE_LUT_YUV422_BPP  (4)
#define ALG_VECTOR_TO_IMAGE_INPUT_BPP       (1)

#define ALG_VECTOR_TO_IMAGE_LUT65x65_WIDTH  (65)
#define ALG_VECTOR_TO_IMAGE_LUT65x65_HEIGHT (65)

#define ALG_VECTOR_TO_IMAGE_LUT129x129_WIDTH  (129)
#define ALG_VECTOR_TO_IMAGE_LUT129x129_HEIGHT (129)

#define DOPT_FLOW_WIDTH_PADDING_FACTOR      (48)
#define DOPT_FLOW_HEIGHT_PADDING_FACTOR     (34)

/**
 *******************************************************************************
 *
 *   \brief Max number of output images
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define VECTORTOIMAGE_LINK_MAX_NUM_OUTPUT (8)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Structure containing vector to image algorithm link parameters
 *
 *          This structure holds any algorithm parameters specific to this link.
 *
 *******************************************************************************
*/
typedef  struct
{
    void                      * algHandle;
    /**< Handle of the algorithm */

    AlgorithmLink_VectorToImageCreateParams             algLinkCreateParams;
    /**< Create params of the vector to image algorithm Link*/

    System_Buffer buffers[VECTORTOIMAGE_LINK_MAX_NUM_OUTPUT];
    /**< System buffer data structure to exchange buffers between links */

    System_VideoFrameBuffer vectorToImageFrame[VECTORTOIMAGE_LINK_MAX_NUM_OUTPUT];
    /**< Payload for System buffers */

    AlgorithmLink_OutputQueueInfo outputQInfo;
    /**< All the information about output Queues used */

    AlgorithmLink_InputQueueInfo  inputQInfo;
    /**< All the information about input Queues used */

    UInt32                        outBufSize;
    /**< Size of output buffer */

    UInt32                        inPitch;
    /**< Pitch of input data */

    AlgorithmLink_VectorToImageDmaObj  dmaObj;
    /**< DMA related info */

    UInt32                        useDma;
    /**< Flag to control usage of DMA */

    Utils_LatencyStats  linkLatency;
    /**< Structure to find out min, max and average latency of the link */

    Utils_LatencyStats  srcToLinkLatency;
    /**< Structure to find out min, max and average latency from
     *   source to this link
     */

    char    *pVectorToImageLUT;
    /**< LUT to use for vector to image */

    char    *pVectorToImageYUV422LUT;
    /**<
     *   LUT represented in YUV422 format
     */

    UInt32  lutBpp;
    /**< LUT bytes per pixel */

    UInt32  lutPitch;
    /**< LUT pitch in bytes */

    UInt32  lutWidth;
    /**< Width of LUT in pixels */

    UInt32  lutHeight;
    /**< Height of LUT in lines */

    UInt32  lutOffset;
    /**< Offset to add to vector to make it fall in the co-ordinate range
     *   of the LUT
     */

    UInt32  vectorToImageYUV422LUTSize;
    /**< Sizeof YUV422 LUT in bytes */

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
} AlgorithmLink_VectorToImageObj;


/*
 * Extern's
 */
extern char gAlg_vectorToImageLUT_16x16x0_25_129x129_0[];
extern char gAlg_vectorToImageLUT_16x16x0_25_129x129_1[];
extern char gAlg_vectorToImageLUT_8x8x0_25_65x65_0[];
extern char gAlg_vectorToImageLUT_8x8x0_25_65x65_1[];

/*******************************************************************************
 *  Algorithm Link Private Functions
 *******************************************************************************
 */
Int32 AlgorithmLink_vectorToImageCreate(void * pObj, void * pCreateParams);
Int32 AlgorithmLink_vectorToImageProcess(void * pObj);
Int32 AlgorithmLink_vectorToImageControl(void * pObj, void * pControlParams);
Int32 AlgorithmLink_vectorToImageStop(void * pObj);
Int32 AlgorithmLink_vectorToImageDelete(void * pObj);
Int32 AlgorithmLink_vectorToImagePrintStatistics(void *pObj,
                       AlgorithmLink_VectorToImageObj *pPhotometricAlignmentObj);

Int32 AlgorithmLink_vectorToImageConvert(
                               AlgorithmLink_VectorToImageObj *pVectorToImageObj,
                               Int8  *pVectorX,
                               Int8  *pVectorY,
                               UInt32  inPitch,
                               UInt8  *pImage,
                               UInt32  width,
                               UInt32  height,
                               UInt32  outPitch,
                               UInt16   *pColorMapLut
                               );


/*******************************************************************************
 *  Functions related to DMA
 *******************************************************************************
 */

Int32 AlgorithmLink_vectorToImageDmaCreate(AlgorithmLink_VectorToImageObj *pObj);
Int32 AlgorithmLink_vectorToImageDmaDelete(AlgorithmLink_VectorToImageObj *pObj);
Int32 AlgorithmLink_vectorToImageDmaConvert(
                               AlgorithmLink_VectorToImageObj *pDmaObj,
                               Int8  *pVectorX,
                               Int8  *pVectorY,
                               UInt32  inPitch,
                               UInt8  *pImage,
                               UInt32  width,
                               UInt32  height,
                               UInt32  outPitch
                               );
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */
