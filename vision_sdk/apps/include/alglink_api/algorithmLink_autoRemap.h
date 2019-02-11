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
 * \defgroup ALGORITHM_LINK_REMAPMERGE Algorithm Plugin: Auto Remap API
 *
 *
 * \brief  This module has the interface for using Auto Remap algorithm
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_autoRemap.h
 *
 * \brief Algorithm Plugin : Auto remap API
 *
 * \version 0.0 (Sep 2016) : First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_AUTOREMAP_H_
#define ALGORITHM_LINK_AUTOREMAP_H_

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

#if 0
/**
 *******************************************************************************
 *
 *   \brief Link CMD: To save/dump captured frame into extra frame
 *                    Dumps the frame allocated at CreateTime
 *                    If extra frame buffer is not allocated at create time
 *                      returns Error
 *
 *      Can be used to save frame only when capture is running
 *
 *******************************************************************************
 */
#define AUTO_REMAP_LINK_CMD_SAVE_FRAME             (0x5000)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Return's pointer to saved frame
 *
 *******************************************************************************
 */
#define AUTO_REMAP_LINK_CMD_GET_SAVE_FRAME_STATUS      (0x5001)
#endif


#define AUTO_REMAP_LINK_CMD_FEATURE_COLLECT_NEW         (0x5000)

#define AUTO_REMAP_LINK_CMD_FEATURE_COLLECT             (0x5001)

#define AUTO_REMAP_LINK_CMD_PERSMAT_CAL                 (0x5002)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

typedef enum
{
    autoRemapTileApproach      = 0,
    /**< More cycles, optimized on memory utilization */
    autoRemapBBApproach        = 1,
    /**< Optimized on cycles, increased memory utilization */
    autoRemapTileAndBBApproach = 2
    /**< TBD */
} AutoRemap_Approach;


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

typedef struct
{
    UInt8 isValid;
    UInt8 *pCalibLUTBuf;
    UInt32 calibLUTBufSize;
    UInt32 calibLUTHeaderSize;
    UInt32 calibLUTQSPIOffset;
    UInt32 calibLUTTagID;
} AlgorithmLink_AutoRemapCalibBufParams;


typedef struct
{
	// header includes
	// 1. flag indicating feature detected - 2byte,
	// 2. startIdx of feature pts (2byte),
	// 3. endIdx of feature Pts (2byte)
	UInt32 featurePtsNum;
	UInt32 featureHeaderSize;
	UInt32 featureBufSize;

    UInt8 *pFeatureBuf;

} AlgorithmLink_AutoRemapFeatureBufParams;


/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for feature plane
 *          computation algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params. This structure should be first element */

    UInt32                   maxInputWidth;
    /**< Max width of the input frame */
    UInt32                   maxInputHeight;
    /**< Max weight of the input frame */

    UInt32                   inFrameWidth;
    /**< Width of the input frame */
    UInt32                   inFrameHeight;
    /**< Height of the input frame */

    UInt16                   cropOffsetX;
    /**< Cropped offset from original captured input */
    UInt16                   cropOffsetY;
    /**< Cropped offset from original captured input */

    Bool                     autoRemapForTDA2x;
    /**< auto remap for TDA2x if 1 */

    System_LinkOutQueParams  outQueParams;
    /**< Output queue information */
    System_LinkInQueParams   inQueParams;
    /**< Input queue information */
    UInt32                   numOutBuffers;
    /**< Number of output Buffers */

    // for EVE format LUT
    AutoRemap_Approach       autoRemapApproach;
    /**< Auto remap approach - different approaches supported
         by auto remap algorithm */
    UInt32                   enableMerge;
    /**< Based on this 2nd stage (Merge stage) of the alg is used */
    UInt32                   dstFormat;
    /**< Output format */
    UInt32                   srcFormat;
    /**< Input format */
    UInt32                   isSrcMapFloat;
    /**< Input format */
    UInt32                   blockWidthBB;
    /**< Input format */
    UInt32                   blockHeightBB;
    /**< Input format */
    UInt32                   interpolationLuma;
    /**< Input format */
    UInt32                   interpolationChroma;
    /**< Input format */
    UInt32                   mapQshift;
    /**< Input format */
    UInt32                   rightShift;
    /**< Input format */
    UInt32                   sat_high;
    /**< Input format */
    UInt32                   sat_high_set;
    /**< Input format */
    UInt32                   sat_low;
    /**< Input format */
    UInt32                   sat_low_set;
    /**< Input format */
    UInt32                   pairIdx;
    /**< Input format */


    // for perspective matrix estimation
    Int16                    numCameras;
    /**< number of cameras */
    Bool                     useRansac;
    /**< whether to use RANSAC */
    Int16                    numRansacIters;
    /**< number of iteration for RANSAC */
    Int16                    numRansacData;
    /**< number of data points needed for each iteration */


    float                    roiRegion;
    /**< roi region for which feature points are used */
    float                    sfWidth;
    /**< horizontal scaling factor after downscaling of input image */
    float                    sfHeight;
    /**< vertical scaling factor after downscaling of input image */

    Int16                    lutWidth;
    /**< LUT width */
    Int16                    lutHeight;
    /**< LUT height */

    Bool                     fishEyeRect;
    /**< auto remap for fisheye input if 1 */



    UInt32                   allocBufferForRawDump;
    /**< [IN] Flag to allocate extra frame buffer for RAW dump
              1, extra frame buffer is allocated
              0, extra frame buffer is not allocated, so RAW frames
                 cannot be dumped */

    AlgorithmLink_AutoRemapCalibBufParams  calibLUTBufPrms;

    AlgorithmLink_AutoRemapFeatureBufParams featureBufPrms;

} AlgorithmLink_AutoRemapCreateParams;


/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for auto rectification
 *          algorithm
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

} AlgorithmLink_AutoRemapControlParams;

/**
 *******************************************************************************
 *  \brief Information of saved RAW data frame
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    UInt32 isSaveFrameComplete;
    /**< TRUE: Frame is saved at address mentioned in 'bufAddr'
     *   FALSE: Frame is not yet saved, try after some time
     */

    UInt32 bufAddr;
    /**< Address where frame is saved for both left and right channel*/

    UInt32 bufSize;
    /**< Size of buffer where frame is saved */

} AlgorithmLink_AutoRemapSaveFrameStatus;


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmLink_AutoRemap_Init(
                        AlgorithmLink_AutoRemapCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_AutoRemap_Init(
    AlgorithmLink_AutoRemapCreateParams *pPrm)
{
    memset(pPrm, 0, sizeof(AlgorithmLink_AutoRemapCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                                sizeof(AlgorithmLink_AutoRemapCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_AUTOREMAP;

    pPrm->maxInputWidth = 1280U;
    pPrm->maxInputHeight = 720U;

    pPrm->inQueParams.prevLinkId    = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
    pPrm->outQueParams.nextLink     = SYSTEM_LINK_ID_INVALID;

    pPrm->numOutBuffers             = 4U;


    pPrm->isSrcMapFloat       = 0U;
    pPrm->srcFormat           = 0U;
    pPrm->mapQshift           = 2U;
    pPrm->interpolationLuma   = 1U;
    pPrm->interpolationChroma = 0U;
    pPrm->rightShift          = 0U;
    pPrm->sat_high            = 255U;
    pPrm->sat_high_set        = 255U;
    pPrm->sat_low             = 0U;
    pPrm->sat_low_set         = 0U;
    pPrm->enableMerge         = 0U;
    pPrm->dstFormat           = 0U;
    pPrm->pairIdx             = 0U;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of Auto Remap algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_AutoRemap_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
