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
 * \defgroup ALGORITHM_LINK_STEREO_POST_PROCESS Stereo Stereo Post Process API
 *
 * \brief  This module has the interface for post-processing algorithm
 *         used in Stereo processing
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_stereoPostProcess.h
 *
 * \brief Algorithm Link API specific to stereo post process algorithm and
 *          visualisation
 * \version 0.0 (Oct 2014) : [VT] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_STEREO_POST_PROCESS_H_
#define ALGORITHM_LINK_STEREO_POST_PROCESS_H_

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
 *   \brief Link CMD: To update post processing's dynamic parameters
 *
 *
 *******************************************************************************
 */
#define STEREO_POSTPROCESS_LINK_CMD_SET_DYNAMIC_PARAMS             (0x5000)

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
 * \brief Enum for the input Q IDs
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_STEREOPP_OPQID_DISPARITY = 0x0,
    /**< QueueId for disparity map */

    ALGLINK_STEREOPP_OPQID_16BIT_DISPARITY = 1,
    /**< QueueId for 3D point cloud */

    ALGLINK_STEREOPP_OPQID_MAXOPQ = 2,
    /**< Maximum number of input queues */

    ALGLINK_STEREOPP_OPQID_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

} AlgorithmLink_StereoPostProcessOutputQueId;

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for stereo post process
 *          and visualisation algorithm
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params. This structure should be first element */
    System_LinkOutQueParams  outQueParams[ALGLINK_STEREOPP_OPQID_MAXOPQ];
    /**< Output queue information */
    System_LinkInQueParams   inQueParams;
    /**< Input queue information */
    UInt32                   numOutBuffers;
    /**< Number of output Buffers */
    UInt32                   num16BitDispOutBuffers;
    /**< Number of output buffers for `16 bit disparity */

    UInt32 maxImageRoiWidth;
    UInt32 maxImageRoiHeight;
    UInt32 inputBitDepth;
    UInt32 censusWinWidth;
    UInt32 censusWinHeight;
    UInt32 disparityWinWidth;
    UInt32 disparityWinHeight;
    UInt32 numDisparities;
    UInt32 disparityStep;
    UInt32 costMaxThreshold;
    UInt32 minConfidenceThreshold;
    UInt32 holeFillingStrength;
    UInt32 textureLumaHiThresh;  /* 0 - 100 */
    UInt32 textureLumaLoThresh;  /* 0 - 100 */
    UInt32 textureThreshold;
    UInt32 lrMaxDiffThreshold;
    UInt32 maxDispDissimilarity;
    UInt32 minConfidentNSegment;
    UInt32 censusSrcImageWidth;
    UInt32 censusSrcImageHeight;
    UInt32 temporalFilterNumFrames;
    UInt32 minDisparityToDisplay;
    UInt32 colorMapIndex; /*0: multi-color, 1: blue */
    UInt32 disparityExtraRightLeft;
    UInt32 disparitySearchDir;
    UInt32 imageStartX;
    UInt32 imageStartY;
    UInt8  numFracBits;
    Bool   useGrayScale;
    UInt8  enable16BitsDispOut;

#if 0
    UInt32                   censusSrcImageWidth;
    /**< Width of the input frame */
    UInt32                   censusSrcImageHeight;
    /**< Height of the input frame */
    UInt32                   censusImageRoiWidth;
    /**< Width of the input frame */
    UInt32                   censusImageRoiHeight;
    /**< Height of the input frame */
#endif
} AlgorithmLink_StereoPostProcessCreateParams;

/*NOTE: This struct is also defined in netwrork_ctrl tools in network_ctrl_handle_stereo_set_dynamic_params.c
Please make sure the two are matching, if any changes are made.
*/
typedef struct
{
    UInt32 postproc_cost_max_threshold;
    UInt32 postproc_conf_min_thrseshold;
    UInt32 postproc_texture_lumalothresh;
    UInt32 postproc_texture_lumahithresh;
    UInt32 postproc_texture_threshold;
    UInt32 postproc_lrmaxdiff_threshold;
    UInt32 postproc_maxdisp_dissimilarity;
    UInt32 postproc_minconf_nseg_threshold;
} AlgorithmLink_StereoPostProcessDynamicParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing control parameters for  stereo post process
 *          algorithm
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */
    AlgorithmLink_StereoPostProcessDynamicParams stereoParams;
    /**< Dynamic stereo params */
} AlgorithmLink_StereoPostProcessControlParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgorithmLink_StereoPostProcess_Init(
                        AlgorithmLink_StereoPostProcessCreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Set defaults for plugin create parameters
 *
 * \param pPrm  [OUT] plugin create parameters
 *
 *******************************************************************************
 */
static inline void AlgorithmLink_StereoPostProcess_Init(
    AlgorithmLink_StereoPostProcessCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AlgorithmLink_StereoPostProcessCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                        sizeof(AlgorithmLink_StereoPostProcessCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_DSP_ALG_STEREO_POST_PROCESS;

    pPrm->numDisparities    = 64U;

    pPrm->inQueParams.prevLinkId    = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
    pPrm->outQueParams[ALGLINK_STEREOPP_OPQID_DISPARITY].nextLink       = SYSTEM_LINK_ID_INVALID;
    pPrm->outQueParams[ALGLINK_STEREOPP_OPQID_16BIT_DISPARITY].nextLink = SYSTEM_LINK_ID_INVALID;
    pPrm->numOutBuffers             = 4U;
    pPrm->num16BitDispOutBuffers    = 4U;
}


/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of soft isp algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_StereoPostProcess_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
