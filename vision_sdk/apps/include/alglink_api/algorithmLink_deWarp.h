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
 *   \ingroup ALGORITHM_LINK_PLUGIN
 *   \defgroup ALGORITHM_LINK_DEWARP  Distortion Correction \
 *             API
 *
 *   This plugin operates in M2M mode (Input Data read from memory, operation by
 *   SIMCOP (LDC) and Output Data written back to memory).
 *
 *   This plugin can be operated with H/W LDC (TDA3xx), where distortion
 *      correction or image could be dewarped
 *
 *   This plugin can operate on multiple channels.
 *
 *   This plugin cannot co-exist with ISSM2MSIMCOP
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file algorithmLink_deWarp.h
 *
 * \brief DeWarp Plugin API : Specific to dewarpping operation
 *
 * \version 0.0 (Jan 2016) : [SS] First version
 *
 *******************************************************************************
 */

#ifndef ALGORITHM_LINK_DEWARP_H_
#define ALGORITHM_LINK_DEWARP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/algorithmLink.h>
#include <include/alglink_api/algorithmLink_srvCommon.h>
#include <include/link_api/systemLink_ipu1_0_params.h>
#include <ti/drv/vps/include/fvid2/fvid2_dataTypes.h>
#include <ti/drv/vps/include/iss/vps_cfgldc.h>
#include <ti/drv/vps/include/iss/vps_cfgvtnf.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 * \brief Max Channels / individual streams of video
 *******************************************************************************
*/
#define ALG_LINK_DEWARP_MAX_CH                  (ALGLINK_SRV_COMMON_MAX_CAMERAS)

/**
 *******************************************************************************
 * \brief Max num of slices for each channel
 *******************************************************************************
*/
#define ALG_LINK_DEWARP_MAX_SLICES              (4U)

/* @} */

/* Control Command's    */

/**
    \ingroup LINK_API_CMD
    \addtogroup ALG_LINK_DEWARP_API_CMD De Warp Plugin control commands

    @{
*/

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To set configuration for LDC
 *
 *          Needs be set by user. If not set then default values will be used.
 *          Use AlgLink_DeWarpConfigParams_Init() to set default params
 *
 *   \param AlgLink_DeWarpConfigParams *pConfig
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALG_LINK_DEWARP_CMD_SET_LDCCONFIG   (0xA001U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To save/dump processed frame
 *      Space for additional frame should flagged at create time, failing which
 *      an error is returned.
 *
 *      Can be used to save frame only when this plugin is receiving frames
 *
 *   \param AlgLink_DeWarpSaveFrame.chId    [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALG_LINK_DEWARP_CMD_SAVE_FRAME      (0xA002U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Return's pointer to saved frame
 *
 *   \param AlgLink_DeWarpSaveFrame   [OUT]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALG_LINK_DEWARP_CMD_GET_SAVE_FRAME_STATUS   (0xA003U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Return's pointer to saved frame
 *
 *   \param AlgLink_DeWarpSaveFrame   [OUT]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALG_LINK_DEWARP_CMD_LDC_ROUTECFG   (0xA004U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Return's pointer to saved frame
 *
 *   \param AlgLink_DeWarpSaveFrame   [OUT]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALG_LINK_DEWARP_CMD_GET_TASKPRI     (0xA005U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Return's pointer to saved frame
 *
 *   \param AlgLink_DeWarpSaveFrame   [OUT]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ALG_LINK_DEWARP_CMD_SET_TASKPRI     (0xA006U)
/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *  \brief  Supported operating modes
 *******************************************************************************
*/
typedef enum
{
    ALGLINK_DEWARP_OPMODE_LDC = 0,
    /**< LDC operation only */

    ALGLINK_DEWARP_OPMODE_MAX = 1,
    /**< Maximum number of operating modes for this plugin */

    ALGLINK_DEWARP_OPMODE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} AlgLink_DeWarpOperatingMode;

/**
 *******************************************************************************
 *  \brief  Pre process output buffer fill type
 *******************************************************************************
*/

typedef enum
{
    ALGLINK_DEWARP_FILLTYPE_NONE,
    /**< No fill */

    ALGLINK_DEWARP_FILLTYPE_HORZ_DOWN,
    /**< Fill Horizontal Bottom strip */

    ALGLINK_DEWARP_FILLTYPE_VERT_LEFT,
    /**< Fill Vertical left strip */

    ALGLINK_DEWARP_FILLTYPE_HORZ_TOP,
    /**< Fill Horizontal Top strip */

    ALGLINK_DEWARP_FILLTYPE_VERT_RIGHT
    /**< Fill Vertical Right strip */

}ALGLINK_DEWARP_FILLTYPE;

/**
 *******************************************************************************
 *  \brief  LDC Traffic Route
 *******************************************************************************
*/

typedef enum
{
    ALG_PLUGIN_DEWARP_LDC_ROUTE_NRT1,
    /**< LDC traffic on NRT1 */

    ALG_PLUGIN_DEWARP_LDC_ROUTE_NRT2
    /**< LDC traffic on NRT2 */

}ALG_PLUGIN_DEWARP_LDC_ROUTE;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
*/

/**
 *******************************************************************************
 *
 * \brief View Point Parameters
 *
 *      In a typical surround view application, N number of video streams is
 *      used construct an surround view (SRV) from a given view point.
 *
 *      In an SRV, the whole captured frame is not displayed. This plugin
 *      provides the applications the ability to select required pixels.
 *      When a wide angle lens is used, this plugin provides the ability to
 *      correct lens distortion for multiple channels (N).
 *
 *      When a view point changes, the width/height and other parameters of each
 *      channel will change. This structure is used to define all required
 *      parameters for a view point, for all channels.
 *
 *******************************************************************************
 */
typedef AlgorithmLink_SrvCommonViewPointParams AlgLink_DeWarpViewPointParams;

/**
 *******************************************************************************
 *
 * \brief Configuration Parameters
 *
 *      Each channels LDC configuration could be overridden, its expected that
 *      applications would use this structure to specify required LDC config.
 *
 *******************************************************************************
 */
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    UInt32  chNum;
    /**< Channel ID for which these parameters are valid */

    /**< If the pointer is NULL: Indicates application is not interested
     *   in configuring or changing values.
     *   If the pointer is non-NULL:  Indicates application is providing new
     *   configuration.
     *   Note that, the structure (Memory) area pointed to these buffers are
     *   available for the link and they are not over-written,
     *   while the link is active.
     */

    vpsissldcConfig_t *ldcConfig;
    /**< Only Valid if
     *  AlgLink_DeWarpCreateParams.channelParams
     *       [AlgLink_DeWarpConfigParams.chNum].operatingMode
     *           = ALGLINK_DEWARP_OPMODE_LDC
     *
     *  Following field in ldcConfig, need not be set by user
     *   and link implementation will over-ride user set values,
     *    vpsissldcConfig_t.isAdvCfgValid
     *    vpsissldcConfig_t.advCfg
     *    vpsissldcConfig_t.inputFrameWidth
     *    vpsissldcConfig_t.inputFrameHeight
     *
     *  Other fields in vpsissldcConfig_t MUST be set by user
     *
     */

    vpsissvtnfConfig_t *vtnfConfig;
    /**< Not Supported for now, kept here for sake of compatibility with
            h/w and other apps */

} AlgLink_DeWarpConfigParams;

/**
 *******************************************************************************
 *
 * \brief De Warp channel parameters
 *
 *
 *        For LDC ONLY mode  , input MUST be YUV420SP data format
 *
 *******************************************************************************
 */
typedef struct
{
    AlgLink_DeWarpOperatingMode operatingMode;
    /**< Refer AlgLink_DeWarpOperatingMode for details */

    UInt32                      numBuffersPerCh;
    /**< Number of image buffers per output channel. Should be same for all
            channels. */

    UInt32                      overrideInFrmSize;
    /**< 1, Overrides the input frame size with the given frame size,
            Ignores frame size received from the previous link/plugin.
            This is useful when the output size is larger than the input size.
         0, Use the frame size received from previous link */
    UInt32                      inputFrameWidth;
    /**< Input frame width,
         Used only when #overrideInFrmSize set to TRUE,
         Used for setting LDC input frame size */
    UInt32                      inputFrameHeight;
    /**< Input frame height,
         Used only when #overrideInFrmSize set to TRUE,
         Used for setting LDC input frame size */

    UInt32                      useOutputFrameSize;
    /**< When the output size of each channel is different, this configuration
            Parameter could be used to specify size of output for each channel.
            Further, if the output size of each channel changes at run time
            this along with #useMaxOutputFrameSize could be used to specify the
            same.
         1, Use output frame size paramters #outputFrameWidth and
            #outputFrameHeight
         0, Output frame size is same as input frame size
         Used only when LDC outputs different frame size than input
         Used in LDC alone mode */
    UInt32                      outputFrameWidth;
    /**< Output Frame width */
    UInt32                      outputFrameHeight;
    /**< Output Frame height */

    UInt32                      useMaxOutputFrameSize;
    /**< Used to configure the maximum size of the output buffer. This is
            expected to be used, when a given channel output size change at run
            time. i.e. Initially this link outputs frame of size X (m x n)
            after an specific event, this link outputs frame of size Y (p x q)
            Where Y > X, in which case following configuration is expected.
            useOutputFrameSize = 1U;
            outputFrameWidth = m;
            outputFrameHeight = n;
            useMaxOutputFrameSize = 1U;
            maxOutputFrameWidth = max (m, p);
            maxOutputFrameHeight = max (n, q);
        1, Allocates output buffer size specified by #maxOutputFrameWidth x
                #maxOutputFrameHeight
        0, Values specified in #maxOutputFrameHeight & #maxOutputFrameHeight are
            ignored.
            */
    UInt32                      maxOutputFrameWidth;
    /**< Maximum frame width expected. */
    UInt32                      maxOutputFrameHeight;
    /**< Maximum frame height expected. */

} AlgLink_DeWarpChannelParams;

/**
 *******************************************************************************
 *  \brief Information of saved data frame
 *******************************************************************************
 */
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    UInt32  chId;
    /**< Channel id for which buffer information is requested */

    UInt32 isSaveFrameComplete;
    /**< TRUE: Frame is saved at address mentioned in 'bufAddr'
     *   FALSE: Frame is not yet saved, try after some time
     */

    UInt32 bufAddr;
    /**< Address where frame is saved */

    UInt32 bufSize;
    /**< Size of buffer where frame is saved */

} AlgLink_DeWarpSaveFrame;

/**
 *******************************************************************************
 *  \brief Set LDC Optimization parameters
 *******************************************************************************
 */
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    ALG_PLUGIN_DEWARP_LDC_ROUTE  route;
    /**< LDC traffic Route */

} AlgLink_DeWarpSetLdcRouteCfg;

/**
 *******************************************************************************
 *  \brief Set/Get Dewarp Task priority
 *******************************************************************************
 */
typedef struct
{
    AlgorithmLink_ControlParams baseClassControl;
    /**< Base class control params */

    UInt32 taskPriority;
    /**< Dewarp Task priority */

} AlgLink_DeWarpTaskPriority;

/**
 *******************************************************************************
 *  \brief  Applications are expected to provide the LDC LUT table for each
 *          channel. This function would be called by the plugin before frames
 *          are processed.
 *          \warning : LDC LUTs for all the active channel should be provided.
 *******************************************************************************
*/
typedef AlgLink_DeWarpViewPointParams *
            (* AlgLink_DeWarpGetViewPointCb)(UInt32 processedFrameCnt);

/**
 *******************************************************************************
 * \brief ISS M2m Simcop link create time parameters
 *******************************************************************************
 */
typedef struct
{
    AlgorithmLink_CreateParams  baseClassCreate;
    /**< Base class create params. This structure should be first element */
    System_LinkInQueParams      inQueParams;
    /**< Input queue information */

    UInt32                      numInQue;
    /**< Flag to enable second input queue for the LDC Lut */

    System_LinkOutQueParams     outQueParams;
    /**< Output queue information */

    AlgLink_DeWarpChannelParams channelParams[ALG_LINK_DEWARP_MAX_CH];
    /**< Parameters for each channel */

    UInt32                      allocBufferForDump;
    /**< [IN] Flag to allocate extra frame buffer for RAW dump
              1, extra frame buffer is allocated
              0, extra frame buffer is not allocated, so RAW frames
                 cannot be dumped */

    System_LinkMemAllocInfo     memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */

    AlgLink_DeWarpGetViewPointCb provideViewPointParams;
    /**< Application function that should return the view point
            to be activated */

    ALGLINK_DEWARP_FILLTYPE fillOutBuf[ALG_LINK_DEWARP_MAX_CH];
    /**< Enable/Disable filling of the dewarp output buffers with user
        provided fill values for Y and UV planes */

    UInt8 fillValueY;
    /**< Fill value for the Y plane */

    UInt8 fillValueUV;
    /**< Fill value for the Y plane */

    UInt8 fillRatio;
    /**< Fill value for the Y plane */

    UInt32 maxLdcLutSize;
    /**< Maximum LDC LUT size */

    Bool useOcmcLdcLut;
    /**< Enable/Disable OCMC for the LDC LUTs */

    UInt32 ldcRdMaxTagCnt;
    /**< LDC Read Max Tag Count */

} AlgLink_DeWarpCreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AlgLink_DeWarpCreateParams_Init(
                                            AlgLink_DeWarpCreateParams *pPrm);
static inline void AlgLink_DeWarpConfigParams_Init(
                                            AlgLink_DeWarpConfigParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Initilizes the pluin and register
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 AlgLink_DeWarpPlugin_init(void);


/**
 *******************************************************************************
 *
 * \brief Set defaults for creation time parameters
 *
 *  Currently defaults are set for 12 bit linear processing with output format of
 *  SYSTEM_DF_YUV420SP_UV.
 *  For any other use case, this function needs to be called
 *  and then change the required parameter accordingly.
 *
 * \param  pPrm [OUT] Create parameters for this link.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void AlgLink_DeWarpCreateParams_Init(
                                            AlgLink_DeWarpCreateParams *pPrm)
{
    /* MISRA.ONEDEFRULE.FUNC
     * MISRAC_2004 Rule 8.5
     * Function Definition in header file
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER: This function initializes the create time argument to
     *  default. Defining this in the header file aids maintainability.
     */
    UInt32 chId;

    memset(pPrm, 0, sizeof(AlgLink_DeWarpCreateParams));

    pPrm->allocBufferForDump = 1U;
    pPrm->numInQue = 1U;
    pPrm->provideViewPointParams = NULL;
    pPrm->fillValueY = 0x00;
    pPrm->fillValueUV = 0x00;
    pPrm->useOcmcLdcLut = FALSE;

    for(chId = 0; chId < ALG_LINK_DEWARP_MAX_CH; chId++)
    {
        pPrm->channelParams[chId].operatingMode   = ALGLINK_DEWARP_OPMODE_LDC;
        pPrm->channelParams[chId].numBuffersPerCh = 3U;
        pPrm->channelParams[chId].overrideInFrmSize = 0U;
        pPrm->channelParams[chId].useOutputFrameSize = 0U;
        pPrm->channelParams[chId].inputFrameWidth = 0U;
        pPrm->channelParams[chId].inputFrameHeight = 0U;
        pPrm->channelParams[chId].outputFrameWidth = 0U;
        pPrm->channelParams[chId].outputFrameHeight = 0U;
        pPrm->channelParams[chId].useMaxOutputFrameSize = 0U;
        pPrm->channelParams[chId].maxOutputFrameWidth = 0U;
        pPrm->channelParams[chId].maxOutputFrameHeight = 0U;
        pPrm->fillOutBuf[chId] = ALGLINK_DEWARP_FILLTYPE_NONE;
    }

    pPrm->ldcRdMaxTagCnt = 15U;
}

static inline void AlgLink_DeWarpConfigParams_Init
                                        (AlgLink_DeWarpConfigParams *pPrm)
{
    /* MISRA.ONEDEFRULE.FUNC
     * MISRAC_2004 Rule 8.5
     * Function Definition in header file
     * KW State: Defer -> Waiver -> Case by case
     * MISRAC_WAIVER: This function initializes the create time argument to
     *   default. Defining this in the header file aids maintainability.
     */
    memset(pPrm, 0, sizeof(AlgLink_DeWarpConfigParams));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* ALGORITHM_LINK_DEWARP_H_ */


/*@}*/
