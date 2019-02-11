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
 * \defgroup ALGORITHM_LINK_VPE_SW_MS_API  VPE Software Mosaic \
 *                                        API
 *
 * \brief  This module has the interface for the algorithm plugin which uses
 *         VPE to perform the function of Software mosaic
 *
 *         This plugin can run on DSP, A15 and IPU1
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_VPESwMs.h
 *
 * \brief  VPE Software Mosaic API
 *
 * \version 0.0 (Aug 2013) : [KC] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_VPE_SW_MS_H_
#define ALGORITHM_LINK_VPE_SW_MS_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <src/rtos/utils_common/include/utils_buf.h>
#include <include/link_api/systemLink_ipu1_0_params.h>

/**
 *******************************************************************************
 *
 *   \brief Maximum number of windows in Mosaic layout
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_VPE_SW_MS_MAX_WINDOWS    (8)

/**
 *******************************************************************************
 *
 *   \brief Invalid channel ID
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_VPE_SW_MS_INVALID_CH_ID  ((UInt32)-1)

/**
 *******************************************************************************
 *
 * \brief Max No. Of channels VPE link supports.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define ALGORITHM_LINK_VPE_SW_MS_MAX_CH                  (8U)
/**
 *******************************************************************************
 *
 * \brief Max VPE outputs/output queues
 *
 * SUPPORTED in ALL platforms
 *
 * VPE validated for only one output queue as of today
 *
 *******************************************************************************
*/
#define ALGORITHM_LINK_VPE_SW_MS_OUT_QUE_ID_MAX          (2U)

/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup ALGORITHM_LINK_VPE_SW_MS_API_CMD \
 *                  VPE Software Mosaic Control Commands
 *
 *   @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Alg Link Config CMD: Set SW Mosaic Layout parameters
 *
 *   \param AlgorithmLink_VpeSwMsLayoutParams [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_VPE_SW_MS_CONFIG_CMD_SET_LAYOUT_PARAMS     (0x0001)

/**
 *******************************************************************************
 *
 *   \brief Alg Link Config CMD: Get SW Mosaic Layout parameters
 *
 *   \param AlgorithmLink_VpeSwMsLayoutParams [OUT]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALGORITHM_LINK_VPE_SW_MS_CONFIG_CMD_GET_LAYOUT_PARAMS     (0x0002)

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
 *   \brief SW Mosaic window information
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 chId;
    /**< Channel associated with this window
     *
     *   If chId is \ref ALGORITHM_LINK_VPE_SW_MS_INVALID_CH_ID blank data
     *   is copied into the window
     */

    UInt32 inStartX;
    /**< X-position in input frame from where to copy */

    UInt32 inStartY;
    /**< Y-position in input frame from where to copy */

    UInt32 outStartX;
    /**< X-position in output frame to where to copy */

    UInt32 outStartY;
    /**< Y-position in output frame to where to copy */

    UInt32 width;
    /**< Window width,
     *   if window width < input width, cropped input is copied
     *   if window width > input width, rest of window is filled with blank data
     */

    UInt32 height;
    /**< Window height,
     *   if window height < input height, cropped input is copied
     *   if window height > input height, rest of window is filled with blank
     *      data
     */

} AlgorithmLink_VpeSwMsLayoutWinInfo;


/**
 *******************************************************************************
 * \brief Ouput param representation for VPE link.
 *
\ *
 *******************************************************************************
*/
typedef struct
{
    UInt32 width;
    /**< Width of the video frame or field in pixels. */

    UInt32 height;
    /**< Height of the video frame or field in lines. */

    System_VideoDataFormat dataFormat;
    /**< Output Frame data Format.
     *   VPE link is validated only for the following output dataformats
     *   1. SYSTEM_DF_YUV422I_YUYV
     *   2. SYSTEM_DF_YUV420SP_UV
     */

    UInt32 numBufsPerCh;
    /**< Number of output buffers per channel */

    UInt32 inputFrameRate;
    /**< applicable for progressive input OR when DEI bypass is TRUE
     *   inputFrameRate + outputFrameRate should be set to control required fps
     */
    UInt32 outputFrameRate;
    /**< applicable for progressive input OR when DEI bypass is TRUE
     *   inputFrameRate + outputFrameRate should be set to control required fps
     */
}AlgorithmLink_VpeSwMsOutParams;

/**
 *******************************************************************************
 * \brief Channel configuration for each VPE Link channel
 *
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_VpeSwMsOutParams outParams[ALGORITHM_LINK_VPE_SW_MS_OUT_QUE_ID_MAX];
    /**< VPE link output params such as width, height, data format etc.*/
    System_ScConfig scCfg;
    /**< Scalar configuration for this channel */
    System_CropConfig scCropCfg;
    /**< Crop configuration for this channel */
}AlgorithmLink_VpeSwMsChannelParams;
/**
 *******************************************************************************
 *
 *   \brief SW Mosaic layout parameters
 *
 *******************************************************************************
*/
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    UInt32 numWin;
    /**< Number of windows in the SW Mosaic */

    AlgorithmLink_VpeSwMsLayoutWinInfo winInfo
                [ALGORITHM_LINK_VPE_SW_MS_MAX_WINDOWS];
    /**< Information of individual window's in the output */

    UInt32 outBufWidth;
    /**< MUST be <= AlgorithmLink_VpeSwMsCreateParams.maxOutBufWidth */

    UInt32 outBufHeight;
    /**< MUST be <= AlgorithmLink_VpeSwMsCreateParams.maxOutBufHeight */

} AlgorithmLink_VpeSwMsLayoutParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing create time parameters for VPE SW Mosaic
 *
 *******************************************************************************
 */
typedef struct
{
    AlgorithmLink_CreateParams baseClassCreate;
    /**< Base class create params */

    System_LinkInQueParams    inQueParams;
    /**< Input queue information */

    System_LinkOutQueParams   outQueParams;
    /**< Output queue information */

    AlgorithmLink_VpeSwMsLayoutParams initLayoutParams;
    /**< Initial window layout parameters */

    UInt32 maxOutBufWidth;
    /**< Max possible output buffer width */

    UInt32 maxOutBufHeight;
    /**< Max possible output buffer height */

    UInt32 numOutBuf;
    /**< Number of buffer to allocate for the output */

    UInt32 numInputCh;
    /**< Number of buffer to allocate for the output */

    AlgorithmLink_VpeSwMsChannelParams chParams[ALGORITHM_LINK_VPE_SW_MS_MAX_CH];
    /**< Channel parameters for input. Each channel may have different
     *   parameters like width, height etc.
     */
    Bool enableOut[ALGORITHM_LINK_VPE_SW_MS_OUT_QUE_ID_MAX];
    /**< Output Queue enable/disable flag */
} AlgorithmLink_VpeSwMsCreateParams;


/*******************************************************************************
 *  Function Prototypes
 *******************************************************************************
 */
static inline Void AlgorithmLink_VpeSwMsLayoutParams_Init(
                                    AlgorithmLink_VpeSwMsLayoutParams *pPrm);
static inline Void AlgorithmLink_VpeSwMsCreateParams_Init(
                                    AlgorithmLink_VpeSwMsCreateParams *pPrm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Set default values for Layout parameters
 *
 *******************************************************************************
 */
static inline Void AlgorithmLink_VpeSwMsLayoutParams_Init(
                    AlgorithmLink_VpeSwMsLayoutParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AlgorithmLink_VpeSwMsLayoutParams));

    pPrm->baseClassControl.size = (UInt32)
                                    sizeof(AlgorithmLink_VpeSwMsLayoutParams);
    pPrm->baseClassControl.controlCmd
            = ALGORITHM_LINK_VPE_SW_MS_CONFIG_CMD_SET_LAYOUT_PARAMS;

    pPrm->numWin = 0U;
    pPrm->outBufWidth  = 1920U;
    pPrm->outBufHeight = 1080U;
}

/**
 *******************************************************************************
 *
 * \brief Set default values for create parameters
 *
 *******************************************************************************
 */
static inline Void AlgorithmLink_VpeSwMsCreateParams_Init(
                    AlgorithmLink_VpeSwMsCreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AlgorithmLink_VpeSwMsCreateParams));

    pPrm->baseClassCreate.size = (UInt32)
                                    sizeof(AlgorithmLink_VpeSwMsCreateParams);
    pPrm->baseClassCreate.algId = ALGORITHM_LINK_IPU_ALG_VPE_SWMS;
    pPrm->maxOutBufWidth = 1920U;
    pPrm->maxOutBufHeight = 1080U;
    pPrm->numOutBuf = 4U;

    AlgorithmLink_VpeSwMsLayoutParams_Init(&pPrm->initLayoutParams);
}

/**
 *******************************************************************************
 *
 * \brief Implementation of function to init plugins()
 *
 *        This function will be called by AlgorithmLink_initAlgPlugins, so as
 *        register plugins of frame copy algorithm
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgorithmLink_VpeSwMs_initPlugin(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
