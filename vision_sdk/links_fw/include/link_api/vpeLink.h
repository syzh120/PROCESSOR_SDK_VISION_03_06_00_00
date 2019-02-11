/*
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
*/

/**
 *******************************************************************************
 *   \ingroup FRAMEWORK_MODULE_API
 *   \defgroup VPE_LINK_API Video Processing Engine (VPE) Link API
 *
 *   VPE Link can be used to do processing on video input frames. These
 *   frames may be from capture or decoded video frames coming over network.
 *
 *   VPE can do
 *   - Color space conversion on input frames.
 *   - Color space conversion while outputting the frame to memory.
 *   - Scaling on input frames.
 *   - De-Interlacing, (conversion from field to frames )
 *
 *   Each output frame can be put in one of multiple output queues available.
 *  @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file vpeLink.h
 *
 * \brief VPE link API public header file.
 *
 * \version 0.0 (Aug 2013)  : [HS] First version
 * \version 0.1 (Sept 2013) : [SS] Second version
 * \version 0.2 (Nov 2014)  : [PS] Third version
 *
 *******************************************************************************
 */

#ifndef VPE_LINK_H_
#define VPE_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/systemLink_ipu1_0_params.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 *
 * \brief VPE scalar output Queue ID
 *        VPE implements two output Queues, The second queue is supported only
 *        with interlaced mode of input.  This is not validated currently as no
 *        HW support to test interlaced mode. The first output queue
 *        "VPE_LINK_OUT_QUE_ID_0" only validated as of today
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define VPE_LINK_OUT_QUE_ID_0            (0U)
#define VPE_LINK_OUT_QUE_ID_1            (1U)

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
#define VPE_LINK_OUT_QUE_ID_MAX          (2U)


/**
 *******************************************************************************
 *
 * \brief Max No. Of channels VPE link supports.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define VPE_LINK_MAX_CH                  (8U)

/**
 *******************************************************************************
 *
 * \brief Indicates number of output buffers to be set to default
 *         value by the VPE link
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define VPE_LINK_NUM_BUFS_PER_CH_DEFAULT (4U)

/* @} */

/**
    \ingroup LINK_API_CMD
    \addtogroup VPE_LINK_API_CMD VPE Link Control Commands

    @{
*/

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Enable channel
 *
 *   \param VpeLink_ChannelInfo * [IN] enable channel
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define VPE_LINK_CMD_ENABLE_CHANNEL          (0x3001U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Set resolution
 *
 *  Set VPE output resolution dynamically
 *
 *   \param VpeLink_ChDynamicSetOutRes * [IN] Output Resolution parameters
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define VPE_LINK_CMD_SET_OUTPUTRESOLUTION    (0x3002U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Get resolution
 *
 *  Get VPE output resolution dynamically
 *
 *   \param VpeLink_ChDynamicSetOutRes * [OUT] Output Resolution parameters
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define VPE_LINK_CMD_GET_OUTPUTRESOLUTION    (0x3003U)

/**
 *******************************************************************************
 *
 *    \brief Link CMD: Set Frame Rate
 *
 *  Set VPE input and output frame rate dynamically
 *
 *   \param VpeLink_ChFpsParams * [IN] VPE FPS parameters
 *
 *  SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define VPE_LINK_CMD_SET_FRAME_RATE          (0x3004U)

/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *  enum Vpe_ProcessingCore
 *  \brief Enumerations for selecting processing core for Video processing
 */
typedef enum
{
    VPE_PROCCORE_VPE = 0,
    /**< VPE is the processing core */
    VPE_PROCCORE_ISS = 1,
    /**< ISS is the processing core */
    VPE_PROCCORE_MAX = 2,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters.
     */
    VPE_PROCCORE_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
      *   This is to make sure enum size defaults to 32 bits always regardless
      *   of compiler.
      */
} VpeLink_ProcessingCore;

/**
 *  enum Vpe_DeiEdiMode
 *  \brief Enumerations for DEI Edge Directed Interpolation (EDI) mode.
 */
typedef enum
{
    VPE_DEI_EDIMODE_LINE_AVG = 0,
    /**< Line average. */
    VPE_DEI_EDIMODE_FLD_AVG = 1,
    /**< Field average. */
    VPE_DEI_EDIMODE_LUMA_ONLY = 2,
    /**< EDI for Luma only. */
    VPE_DEI_EDIMODE_LUMA_CHROMA = 3,
    /**< EDI for Luma and Chroma. */
    VPE_DEI_EDIMODE_MAX = 4,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters.
     */
    VPE_DEI_EDIMODE_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
      *   This is to make sure enum size defaults to 32 bits always regardless
      *   of compiler.
      */
} VpeLink_DeiEdiMode;

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief Ouput param representation for VPE link.
 *
 *
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
}VpeLink_OutParams;

/**
 *******************************************************************************
 * \brief De-Interlacer configuration for VPE link
 *
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 bypass;
    /**< DEI should be bypassed or not.
     *   1. For interlaced input and interlaced output from DEI/VIP scalar,
     *   the DEI could be operated in two modes.
     *      a. DEI in bypass mode and the respective scalar in non-interlacing
     *      mode (interlaced input DEI, interlaced output from Scalar).
     *      In this case,
     *      DEI bypass = TRUE
     *      Scalar bypass = TRUE/FALSE depending up on whether scaling is
     *      required or not.
     *      b. DEI in deinterlacing mode - converts interlaced input to
     *      progressive output to the scalar. Scalar in interlacing mode -
     *      converts the progressive input from DEI to interlaced output.
     *      In this case,
     *      DEI bypass = FALSE
     *      Scalar bypass = FALSE
     *   2. For progressive input and interlaced output, Scalar will be in
     *      interlacing mode.
     *      DEI bypass = TRUE
     *      Scalar bypass = FALSE
     *   3. For progressive input and progressive output,
     *      DEI bypass = TRUE
     *      Scalar bypass = TRUE/FALSE depending up on whether scaling is
     *      required or not.
     *   4. For interlaced input and progressive output,
     *      DEI bypass = FALSE
     *      Scalar bypass = TRUE/FALSE depending up on whether scaling is
     *      required or not.
     *   VPE is validated only for DEI in Bypass mode (Bypass = TRUE).  This
     *   is because no HW set-up available currently to feed interlaced input
     */
    VpeLink_DeiEdiMode inpMode;
    /**< Interpolation mode.*/
    UInt32 tempInpEnable;
    /**< 3D processing (temporal interpolation). */
    UInt32 tempInpChromaEnable;
    /**< 3D processing for chroma. */
    UInt32 spatMaxBypass;
    /**< Bypass spatial maximum filtering. */
    UInt32 tempMaxBypass;
    /**< Bypass temporal maximum filtering. */
} VpeLink_DeiCfg;

/**
 *******************************************************************************
 * \brief Channel configuration for each VPE Link channel
 *
 *
 *******************************************************************************
*/
typedef struct
{
    VpeLink_OutParams outParams[VPE_LINK_OUT_QUE_ID_MAX];
    /**< VPE link output params such as width, height, data format etc.*/
    VpeLink_DeiCfg deiCfg;
    /**< De-Interlace configuration. de-interlacing will be supported in
     *   future
     */
    System_ScConfig scCfg;
    /**< Scalar configuration for this channel */
    System_CropConfig scCropCfg;
    /**< Crop configuration for this channel */
}VpeLink_ChannelParams;

/**
 *******************************************************************************
 * \brief VPE Link create parameters.
 *
 *
 *******************************************************************************
*/
typedef struct
{
    System_LinkInQueParams inQueParams;
    /**< Input queue information. */

    System_LinkOutQueParams outQueParams[VPE_LINK_OUT_QUE_ID_MAX];
    /**< Output queue information. */

    VpeLink_ChannelParams chParams[VPE_LINK_MAX_CH];
    /**< Channel parameters for input. Each channel may have different
     *   parameters like width, height etc.
     */
    UInt32 enableOut[VPE_LINK_OUT_QUE_ID_MAX];
    /**< enableOut[x] = TRUE, enable the corresponding output
     *   enableOut[x] = FALSE, disable the corresponding output.
     */
    VpeLink_ProcessingCore procCore;
    /**< Refer enum VpeLink_ProcessingCore. */

    System_LinkMemAllocInfo memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */

} VpeLink_CreateParams;

/**
 *******************************************************************************
 * \brief VPE Link set output resolution
 *
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 chId;
    /**< channel Id */

    UInt32 outQueId;
    /**< output Queue ID.
     *   Possible values: VPE_LINK_OUT_QUE_ID_0 or VPE_LINK_OUT_QUE_ID_1
     *   Validated only single output [VPE_LINK_OUT_QUE_ID_0] mode
     */

    UInt32 width;
    /**< output width */

    UInt32 height;
    /**< output height */

} VpeLink_ChDynamicSetOutRes;

/**
 *******************************************************************************
 * \brief VPE Link channel info
 *
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 chId;
    /**< VPE link channel number */

    UInt32 outQueId;
    /**< output Queue ID.
     *   Possible values: VPE_LINK_OUT_QUE_ID_0 or VPE_LINK_OUT_QUE_ID_1
     *   Validated only single output [VPE_LINK_OUT_QUE_ID_0] mode
     */

    UInt32 enable;
    /**< VPE channel enable or disable flag */
} VpeLink_ChannelInfo;

/**
 *******************************************************************************
 * \brief VPE Link channel dynamic set config params
 *
 * Defines VPE FPS parameters that can be changed dynamically
 * on a per channel basis
 *
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 chId;
    /**< channel number */

    UInt32 outQueId;
    /**< output Queue ID.
     *   Possible values: VPE_LINK_OUT_QUE_ID_0 or VPE_LINK_OUT_QUE_ID_1
     *   Validated only single output [VPE_LINK_OUT_QUE_ID_0] mode
     */

    UInt32 inputFrameRate;
    /**< input frame rate - 60 or 50 fps if interlaced */

    UInt32 outputFrameRate;
    /**< Expected output frame rate */

} VpeLink_ChFpsParams;

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

static inline void VpeLink_CreateParams_Init(VpeLink_CreateParams *pPrm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief VPE Link register and init
 *
 * Creates the tasks for the link. Registers Link within System with
 * unique link ID and callback functions.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 VpeLink_init(void);

/**
 *******************************************************************************
 *
 * \brief VPE Link de-register and de-init
 *
 * Delete the tasks and de-registers itself from the system.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 VpeLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Set defaults for create parameter
 *
 *  Currently defaults are set for xxx usecase.
 *  For any other use case example has to call this function
 *  and change the required parameter accordingly.
 *
 * \param  pPrm [OUT] Create parameters for VPE link.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void VpeLink_CreateParams_Init(VpeLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    UInt32 outId, chId;
    VpeLink_ChannelParams *chPrms;

    memset(pPrm, 0, sizeof(VpeLink_CreateParams));

#if defined(TDA2XX_BUILD) || defined(TDA2PX_BUILD)
    pPrm->procCore = VPE_PROCCORE_VPE;
#endif

#ifdef TDA3XX_BUILD
    pPrm->procCore = VPE_PROCCORE_ISS;
#endif

    pPrm->inQueParams.prevLinkId = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;

    for(outId=0U; outId<VPE_LINK_OUT_QUE_ID_MAX; outId++)
    {
        pPrm->outQueParams[outId].nextLink = SYSTEM_LINK_ID_INVALID;
        pPrm->enableOut[outId] = (UInt32) FALSE;

    }
    for(outId=0U; outId<VPE_LINK_OUT_QUE_ID_MAX; outId++)
    {
        for (chId = 0U; chId < VPE_LINK_MAX_CH; chId++)
        {
            chPrms = &pPrm->chParams[chId];
            chPrms->outParams[outId].numBufsPerCh =
                                     VPE_LINK_NUM_BUFS_PER_CH_DEFAULT;
            chPrms->outParams[outId].inputFrameRate = 30U;
            chPrms->outParams[outId].outputFrameRate = 30U;

            chPrms->outParams[outId].width = 1280U;
            chPrms->outParams[outId].height = 720U;
            chPrms->outParams[outId].dataFormat = SYSTEM_DF_YUV422I_YUYV;

            chPrms->deiCfg.bypass = (UInt32) TRUE;
            /* All below are don't care since DEI is in bypassed state */
            chPrms->deiCfg.inpMode = VPE_DEI_EDIMODE_LINE_AVG;
            chPrms->deiCfg.tempInpEnable = (UInt32) FALSE;
            chPrms->deiCfg.tempInpChromaEnable = (UInt32) FALSE;
            chPrms->deiCfg.spatMaxBypass = (UInt32) TRUE;
            chPrms->deiCfg.tempMaxBypass = (UInt32) TRUE;

            chPrms->scCfg.bypass       = (UInt32) FALSE;
            chPrms->scCfg.nonLinear    = (UInt32) FALSE;
            chPrms->scCfg.stripSize    = 0U;

            /*
             * If crop width and height are set to zero, link internally takes it as
             * ouputwidth and outputheight.
             */
            chPrms->scCropCfg.cropStartX = 0U;
            chPrms->scCropCfg.cropStartY = 0U;
            chPrms->scCropCfg.cropWidth = 0U;
            chPrms->scCropCfg.cropHeight = 0U;
        }
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */

