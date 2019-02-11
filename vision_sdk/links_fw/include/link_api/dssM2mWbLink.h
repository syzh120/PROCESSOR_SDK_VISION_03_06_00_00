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
 *   \defgroup DSSM2MWB_LINK_API Video Processing Engine (DSSM2MWB) Link API
 *
 *   DSSM2MWB Link can be used to do processing on video input frames. These
 *   frames may be from capture or decoded video frames coming over network.
 *
 *   DSSM2MWB can do
 *   - Color space conversion on input frames.
 *   - Color space conversion while outputting the frame to memory.
 *   - Scaling on input frames.
 *
 *   Each output frame can be put in one of multiple output queues available.
 *  @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file dssM2mWbLink.h
 *
 * \brief DSSM2MWB link API public header file.
 *
 * \version 0.0 (Aug 2013)  : [HS] First version
 * \version 0.1 (Sept 2013) : [SS] Second version
 * \version 0.2 (Nov 2014)  : [PS] Third version
 *
 *******************************************************************************
 */

#ifndef DSSM2MWB_LINK_H_
#define DSSM2MWB_LINK_H_

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
 * \brief Max No. Of Input Queues DSSM2MWB link supports.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#ifdef TDA2XX_FAMILY_BUILD
    /* VID1, VID2,VID3 and GFX */
    #define DSSM2MWB_LINK_MAX_IN_CH                         (4U)
#else
    #ifdef TDA3XX_FAMILY_BUILD
        /* VID1, VID2 and GFX */
        #define DSSM2MWB_LINK_MAX_IN_CH                     (3U)
    #else
        /* VID1, VID2 and GFX */
        #define DSSM2MWB_LINK_MAX_IN_CH                     (3U)
    #endif
#endif

/**
 *******************************************************************************
 *
 * \brief Indicates number of output buffers to be set to default
 *         value by the DSSM2MWB link
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define DSSM2MWB_LINK_NUM_BUFS_PER_CH_DEFAULT       (4U)

/* @} */

/**
    \ingroup LINK_API_CMD
    \addtogroup DSSM2MWB_LINK_API_CMD DSSM2MWB Link Control Commands

    @{
*/

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Enable channel
 *
 *   \param DssM2mWbLink_ChannelInfo * [IN] enable channel
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DSSM2MWB_LINK_CMD_ENABLE_CHANNEL            (0x6001U)

/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */
typedef enum
{
    DSSM2MWBLINK_DISPC_WB_IN_NODE_VID1 = 1,
    /**< VID1 pipeline is connected to Writeback. */
    DSSM2MWBLINK_DISPC_WB_IN_NODE_VID2 = 2,
    /**< VID2 pipeline is connected to Writeback. */
    DSSM2MWBLINK_DISPC_WB_IN_NODE_VID3 = 3,
    /**< VID3 pipeline is connected to Writeback
     *    Not applicable for tda3xx platform. */
    DSSM2MWBLINK_DISPC_WB_IN_NODE_GFX = 4,
    /**< GFX pipeline is connected to Writeback*/
    DSSM2MWBLINK_DISPC_WB_IN_NODE_LCD1 = 6,
    /**< LCD1 Overlay is connected to Writeback*/
    DSSM2MWBLINK_DISPC_WB_IN_NODE_LCD2 = 7,
    /**< LCD2 Overlay is connected to Writeback
     *    Not applicable for tda3xx platform. */
    DSSM2MWBLINK_DISPC_WB_IN_NODE_LCD3 = 8,
    /**< LCD3 Overlay is connected to Writeback
     *    Not applicable for tda3xx platform. */
    DSSM2MWBLINK_DISPC_WB_IN_NODE_TV = 9,
    /**< TV Overlay is connected to Writeback
     *    Not applicable for tda3xx platform. */
    DSSM2MWBLINK_DISPC_WB_IN_NODE_MAX = 10,
                                   /**< Should be the last value of this
                                    * enumeration. Will be used by driver for
                                    * validating the input parameters. */
    DSSM2MWBLINK_DISPC_WB_IN_NODE_FORCE32BITS = 0x7FFFFFFF
} DssM2mWbLink_DssDispcWbInNode;


typedef enum
{
    DSSM2MWBLINK_DISPC_PIPE_VID1 = 0,
    /**< Video1 Pipeline. */
    DSSM2MWBLINK_DISPC_PIPE_VID2 = 1,
    /**< Video2 Pipeline. */
    DSSM2MWBLINK_DISPC_PIPE_VID3 = 2,
    /**< Video3 Pipeline. */
    DSSM2MWBLINK_DISPC_PIPE_GFX1 = 3,
    /**< GFX1 Pipeline. */
    DSSM2MWBLINK_DISPC_PIPE_WB = 4,
    /**< Write back. */
    DSSM2MWBLINK_DISPC_PIPE_MAX = 5,
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
    DSSM2MWBLINK_DISPC_PIPE_FORCE32BITS = 0x7FFFFFFF
} DssM2mWbLink_DssDispcPipes;

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 * \brief DSSM2MWB Link create parameters.
 *
 *
 *******************************************************************************
*/
typedef struct
{
    System_LinkInQueParams inQueParams;
    /**< Input queue information. */

    System_LinkOutQueParams outQueParams;
    /**< Output queue information. */

    UInt32 enableOut;
    /**< enableOut[x] = TRUE, enable the corresponding output
     *   enableOut[x] = FALSE, disable the corresponding output.
     */

    DssM2mWbLink_DssDispcWbInNode wbInNode;
    /**< write back input Node */

    UInt32 numInPipeLines;
    /**< No of input queues */

    DssM2mWbLink_DssDispcPipes inPipelines[DSSM2MWB_LINK_MAX_IN_CH];
    /**< Input DISPC pipelines */

    System_VideoDataFormat outDataFmt;
    /**< Output queue data format */

    UInt32 inTarWidth[DSSM2MWB_LINK_MAX_IN_CH];
    /**< Input target widths */

    UInt32 inTarHeight[DSSM2MWB_LINK_MAX_IN_CH];
    /**< Input target heights */

    UInt32 inPosX[DSSM2MWB_LINK_MAX_IN_CH];
    /**< Input position X */

    UInt32 inPosY[DSSM2MWB_LINK_MAX_IN_CH];
    /**< Input position Y */

    UInt32 outWidth;
    /**< Output width */

    UInt32 outHeight;
    /**< Output height */

    UInt32 ovlyWidth;
    /**< Overlay width */

    UInt32 ovlyHeight;
    /**< Overlay height */

    System_LinkMemAllocInfo memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */

} DssM2mWbLink_CreateParams;


/**
 *******************************************************************************
 * \brief DSSM2MWB Link channel info
 *
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 chId;
    /**< DSSM2MWB link channel number */

    UInt32 enable;
    /**< DSSM2MWB channel enable or disable flag */
} DssM2mWbLink_ChannelInfo;

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

static inline void DssM2mWbLink_CreateParams_Init(DssM2mWbLink_CreateParams *pPrm);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief DSSM2MWB Link register and init
 *
 * Creates the tasks for the link. Registers Link within System with
 * unique link ID and callback functions.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DssM2mWbLink_init(void);

/**
 *******************************************************************************
 *
 * \brief DSSM2MWB Link de-register and de-init
 *
 * Delete the tasks and de-registers itself from the system.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 DssM2mWbLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Set defaults for create parameter
 *
 *  Currently defaults are set for xxx usecase.
 *  For any other use case example has to call this function
 *  and change the required parameter accordingly.
 *
 * \param  pPrm [OUT] Create parameters for DSSM2MWB link.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void DssM2mWbLink_CreateParams_Init(DssM2mWbLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(DssM2mWbLink_CreateParams));

    pPrm->inQueParams.prevLinkId = SYSTEM_LINK_ID_INVALID;
    pPrm->inQueParams.prevLinkQueId = 0U;
    pPrm->outQueParams.nextLink = SYSTEM_LINK_ID_INVALID;
    pPrm->enableOut = (UInt32)TRUE;
    pPrm->wbInNode = DSSM2MWBLINK_DISPC_WB_IN_NODE_VID1;
    pPrm->numInPipeLines = 1U;
    pPrm->inPipelines[0U] = DSSM2MWBLINK_DISPC_PIPE_VID1;
    pPrm->outDataFmt = SYSTEM_DF_YUV422I_YUYV;
    pPrm->inTarWidth[0U] = 1280U;
    pPrm->inTarHeight[0U] = 720U;
    pPrm->inPosX[0U] = 0U;
    pPrm->inPosY[0U] = 0U;
    pPrm->outWidth = 1280U;
    pPrm->outHeight = 720U;
    pPrm->ovlyWidth = 1280U;
    pPrm->ovlyHeight = 720U;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/

/* Nothing beyond this point */

