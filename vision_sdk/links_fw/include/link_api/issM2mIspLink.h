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
 *
 *   \ingroup FRAMEWORK_MODULE_API
 *   \defgroup ISSM2MISP_LINK_API ISS M2M ISP Link API
 *
 *
 *   ISS M2M Isp Link is used for ISP operations available in ISS
 *   This link operates in M2M mode (Input Data read from memory, operation by
 *   ISP and Output Data written back to memory)
 *
 *   This link can be operated in two main modes
 *   - ISSM2MISP_LINK_OPMODE_12BITLINEAR: This
 *     mode is typically used for RAW Bayear to YUV format conversion with
 *     relevant image signal processing.
 *   - ISSM2MISP_LINK_OPMODE_20BITWDR: This
 *     mode is typically used for Wide Dynamic Range operations.
 *
 *   This link can operate on multiple channels.
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file issM2mIspLink.h
 *
 * \brief ISS M2M Isp link API public header file.
 *
 * \version 0.0 (Jun 2014) : [PS] First version
 * \version 0.1 (Aug 2014) : [PS] Addressed review comments given by team
 *
 *******************************************************************************
 */

#ifndef ISSM2MISP_LINK_H_
#define ISSM2MISP_LINK_H_

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
 * \brief Max Channels of operation
 *******************************************************************************
*/
#define ISSM2MISP_LINK_MAX_CH     (4U)

/**
 *******************************************************************************
 *
 * \brief Indicates number of output buffers to be set to default
 *         value by the link
 *******************************************************************************
*/
#define ISSM2MISP_LINK_NUM_BUFS_PER_CH_DEFAULT (3U)

/**
 *******************************************************************************
 * \brief Buffer Alignment requirement for ISP Resizer Output 
 *******************************************************************************
*/
#define ISSM2MISP_LINK_RSZ_BUF_ALIGN  (128U)


/* @} */

/* Control Command's    */

/**
    \ingroup LINK_API_CMD
    \addtogroup ISSM2MISP_LINK_API_CMD  ISS M2M ISP Link Control Commands

    @{
*/

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To set configuration for different modules of ISP
 *
 *          Needs be set by user before calling System_linkStart()
 *
 *   \param IssIspConfigurationParameters *pIspConfig
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSM2MISP_LINK_CMD_SET_ISPCONFIG             (0x5001U)


/**
 *******************************************************************************
 *
 *   \brief Link CMD: To set AE and AWB parameters and set the ISP
 *          configuration accordingly
 *
 *          AEWB algorithm calls this ioctl through Vid_Sensor layer
 *
 *   \param IssAewbAlgOutParams *pAewbConfig
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSM2MISP_LINK_CMD_SET_AEWB_PARAMS           (0x5002U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To set ISP merge parameters based on the exposure ratio
 *
 *          AEWB algorithm calls this ioctl through Vid_Sensor layer
 *
 *   \param IssAewbAlgOutParams *pAewbConfig
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSM2MISP_LINK_CMD_SET_WDR_MERGE_PARAMS      (0x5003U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To save ISP output
 *
 *   \param chId Channel Id
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSM2MISP_LINK_CMD_SAVE_FRAME                (0x5004U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Return's pointer to saved frame
 *
 *   \param IssM2mIspLink_GetSaveFrameStatus   [OUT]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSM2MISP_LINK_CMD_GET_SAVE_FRAME_STATUS      (0x5005U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To set the Tap Pointer
 *          This allows to save/view output of the ISP at various isp modules.
 *          Within the module, submodules can be enabled/disabled using DCC
 *          Only available if ISS_ENABLE_DEBUG_TAPS build macro is set.
 *
 *   \param pTapPrms Pointer to IssM2mIspLink_IspOutputTapParams
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSM2MISP_LINK_CMD_SET_TAP_PARAMS            (0x5006U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To move the ISP traffic on NRT2
 *          This allows to save/view output of the ISP at various isp modules.
 *          Within the module, submodules can be enabled/disabled using DCC
 *          Only available if ISS_ENABLE_DEBUG_TAPS build macro is set.
 *
 *   \param pTapPrms Pointer to IssM2mIspLink_IspOutputTapParams
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSM2MISP_LINK_CMD_SET_ISP_ROUTE_CFG  (0x5007U)

/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for operating modes of ISS M2M Link
 *
 *          List of operating modes
 *
 *******************************************************************************
*/
typedef enum
{
    ISSM2MISP_LINK_OPMODE_12BIT_LINEAR = 0,
    /**< upto 12-bit linear mode of operation */

    ISSM2MISP_LINK_OPMODE_1PASS_WDR = 1,
    /**< Single Pass WDR mode of operation */

    ISSM2MISP_LINK_OPMODE_2PASS_WDR = 2,
    /**< Two Pass WDR mode of operation */

    ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED = 3,
    /**< Two Pass WDR Line Interleaved mode */

    ISSM2MISP_LINK_OPMODE_12BIT_MONOCHROME = 4,
    /**< 12Bit Mononchroma mode,
         In this mode, ISP reads 12bit data,
            does few processing like DPC/NSF3/Black Level subtraction/GLBCE
            and outputs 8bit monochroma data from resizer */

    ISSM2MISP_LINK_OPMODE_MAXNUM = 5,
    /**< Maximum number of operating modes for this link */

    ISSM2MISP_LINK_OPMODE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */

} IssM2mIspLink_OperatingMode;

/**
 *******************************************************************************
 *  \brief  Enumerations for output queue IDs
 *******************************************************************************
*/
typedef enum
{
    ISSM2MISP_LINK_INPUTQUE_RAW_IMAGE = 0,
    /**< Input queue for raw image input to this link */

    ISSM2MISP_LINK_INPUTQUE_MAXNUM = 1,
    /**< Number of Input queues for this link */

    ISSM2MISP_LINK_INPUTQUE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} IssM2mIspLink_InputQueId;

/**
 *******************************************************************************
 *  \brief  Enumerations for output queue IDs
 *******************************************************************************
*/
typedef enum
{
    ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A = 0,
    /**< Output queue for image output of re-sizer A */

    ISSM2MISP_LINK_OUTPUTQUE_H3A = 1,
    /**< Output queue for H3A statistics */

    ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B = 2,
    /**< Output queue for image output of re-sizer B */

    ISSM2MISP_LINK_OUTPUTQUE_H3A_AF = 3,
    /**< Output queue for H3A statistics */

    ISSM2MISP_LINK_OUTPUTQUE_MAXNUM = 4,
    /**< Number of Output queues for this link */

    ISSM2MISP_LINK_OUTPUTQUE_FORCE32BITS = 0x7FFFFFFF
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} IssM2mIspLink_OutputQueId;

/**
 *******************************************************************************
 *  \brief  Enumerations for output Tap Points,
 *          Used only when ISS_ENABLE_DEBUG_TAPS is enabled
 *
 *******************************************************************************
*/
typedef enum
{
    ISSM2MISP_LINK_ISP_TAP_RESIZER_OUTPUT = 0,
    /**< Enable Resizer Output for Frame dumping */
    ISSM2MISP_LINK_ISP_TAP_IPIPE_OUTPUT = 1,
    /**< Enable IPIPE Output for Frame dumping */
    ISSM2MISP_LINK_ISP_TAP_GLBCE_OUTPUT = 2,
    /**< Enable GLBCE Output for Frame dumping */
    ISSM2MISP_LINK_ISP_TAP_IPIPEIF_OUTPUT = 3,
    /**< Enable IPIPEIF Output for Frame dumping */
    ISSM2MISP_LINK_ISP_TAP_INTERMED_OUTPUT = 4
    /**< Enable Intermediate/Pass1 Output for Frame dumping for 2 pass wdr */
} IssM2mIspLink_IspOutputTapPoints;

/**
 *******************************************************************************
 *  \brief  Enumerations for ISP Route config
 *******************************************************************************
*/
typedef enum
{
    ISSM2MISP_LINK_ROUTE_NRT1 = 0,
    /**< ISP Traffic on NRT1 */

    ISSM2MISP_LINK_ROUTE_NRT2 = 1
    /**< ISP Traffic on NRT2 */

} IssM2mIspLink_Route;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
*/

/**
 *******************************************************************************
 *  \brief Information of saved data frame
 *******************************************************************************
 */
typedef struct
{
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

    UInt32 saveBufAddr[2];
    /**< Address where frame is saved */

    UInt32 saveBufSize[2];
    /**< Size of buffer where frame is saved */

} IssM2mIspLink_GetSaveFrameStatus;

/**
 *******************************************************************************
 *  \brief  ISS M2m Isp link Tap Params, used for enabling
 *          output dumping at different ISP modules.
 *          Used only when ISS_ENABLE_DEBUG_TAPS is enabled
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                           chId;
    /**< Id of the channel */

    IssM2mIspLink_IspOutputTapPoints outputTapModule;
    /**< Enable frame dumping for given output */
} IssM2mIspLink_IspOutputTapParams;

/**
 *******************************************************************************
 * \brief ISS M2m Isp link output image format
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                           heightRszA;
    /**< Height of the output frame for Re-sizer.
     *   Don't care if  enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A] = 0
     */

    UInt32                           widthRszA;
    /**< Width of the output frame for Re-sizer.
     *   Don't care if  enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A] = 0
     */

    UInt32                           heightRszB;
    /**< Height of the output frame for Re-sizer.
     *   Don't care if  enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0
     */

    UInt32                           widthRszB;
    /**< Width of the output frame for Re-sizer.
     *   Don't care if  enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_B] = 0
     */

    UInt32                           winWidthH3a;
    /**< Width of H3A window, this parameter is mainly used to
     *    allocate output buffer for H3A
     *
     *   Actually H3A info is provided
     *   via IssIspConfigurationParameters->aewbCfg
     */

    UInt32                           winHeightH3a;
    /**< Height of H3A window, this parameter is mainly used to
     *    allocate output buffer for H3A
     *
     *   Actually H3A info is provided
     *   via IssIspConfigurationParameters->aewbCfg
     */

    UInt32                           paxelNumHaf;
    /**< Number of horizontal AF paxels,  this parameter is mainly used to
     *    allocate output buffer for Auto-focus
     */

    UInt32                           paxelNumVaf;
    /**< Number of vertical AF paxels,  this parameter is mainly used to
     *    allocate output buffer for Auto-focus
     */
    System_VideoDataFormat           dataFormat;
    /**< Output Frame data Format.
     *   Only following output data formats are supported
     *       SYSTEM_DF_YUV422I_YUYV
     *       SYSTEM_DF_YUV420SP_UV,
     */

} IssM2mIspLink_OutputParams;

typedef struct IssM2mIspLink_WdrOffsetParams
{
    UInt32 longLineOffset;
    /**< In case of WDR Line Interleaved offset, this is used to get
         the start offset for the long channel
         Not used for other operating modes */
    UInt32 shortLineOffset;
    /**< In case of WDR Line Interleaved offset, this is used to get
         the start offset for the long channel
         Not used for other operating modes */
    UInt32 longPixelOffset;
    /**< In WDR Line Interleaved mode, this is used to get the the
         start pixel offset for the long exposure channel. This is used
         in addition to #longLineOffset.
         Not used for other operating modes */
    UInt32 shortPixelOffset;
    /**< In WDR Line Interleaved mode, this is used to get the the
         start pixel offset for the short exposure channel. This is used
         in addition to #shortLineOffset.
         Not used for other operating modes */
    UInt32 width;
    /**< In case of WDR Line Interleaved offset,
         this is used to set the ISP frame size
         This is added because input frame from capture could
         have big frame */
    UInt32 height;
    /**< In case of WDR Line Interleaved offset,
         this is used to set the ISP frame size
         This is added because input frame from capture could
         have big frame */
} IssM2mIspLink_WdrOffsetParams_t;

/**
 *******************************************************************************
 * \brief ISS M2m Isp link output image format
 *
 *******************************************************************************
*/
typedef struct
{
    IssM2mIspLink_OperatingMode        operatingMode;
    /**< Refer IssM2mIspLink_OperatingMode for details */

    IssM2mIspLink_WdrOffsetParams_t    wdrOffsetPrms;
    /**< WDR Offset parameters for Line Interleaved WDR mode */

    System_BitsPerPixel                inBpp;
    /**< Input Bits per pixel
     *   - As output by image censor
     *   - In case of 16-bit WDR and 20-bit WDR mode
     *     - This specifies BPP after companding
     */

    System_BitsPerPixel                decmpBpp;
    /**< Input Bits per pixel after decompaning
     *   - Only valid in 16-bit WDR and 20-bit WDR mode
     *   - Ignored in 12-bit linear mode
     */

    UInt32                             numBuffersPerCh;
    /**< Number of image buffers per output channel */

    UInt32                             enableOut[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM];
    /**< enableOut[x] = 1, enable the corresponding output
     *   enableOut[x] = 0, disable the corresponding output.
     *   For possible value of x, refer enum IssM2mIspLink_OutputQueId
     */

    IssM2mIspLink_OutputParams         outParams;
    /**< Parameters for output queue */

    UInt32                             useBufSizePrmsFlag;
    /**< 1: Use #maxBufWidth and #maxBufHeight Parameters for
            buffer allocation
         0: Use resizer output size for allocating buffer */
    UInt32                             maxBufWidth;
    /**< Maximum buffer width,
         Used only when #useBufSizePrmsFlag is set to 1
         Used for allocating buffer */
    UInt32                             maxBufHeight;
    /**< Maximum buffer height,
         Used only when #useBufSizePrmsFlag is set to 1
         Used for allocating buffer */
    UInt32 flipCtrl;
    /**< Maximum flip Control parameter used to flip the video,
         if we are not receiving properly. */

    UInt32                       horizontalFlip;
    /**< Horizontal Flip Mode */

    UInt32                       verticalFlip;
    /**< Vertical Flip Mode */
} IssM2mIspLink_ChannelParams;

/**
 *******************************************************************************
 * \brief ISS M2m Isp link Route Config parameters
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    IssM2mIspLink_Route route;
    /**< ISP route */

} IssM2mIspLink_RouteCfg;

/**
 *******************************************************************************
 * \brief ISS M2m Isp link create time parameters
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    System_LinkInQueParams       inQueParams[ISSM2MISP_LINK_INPUTQUE_MAXNUM];
    /**< Input queue information */

    System_LinkOutQueParams      outQueParams[ISSM2MISP_LINK_OUTPUTQUE_MAXNUM];
    /**< Output queue information */

    IssM2mIspLink_ChannelParams  channelParams[ISSM2MISP_LINK_MAX_CH];
    /**< Parameters for each channel */

    System_LinkMemAllocInfo      memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */

    UInt32                       allocBufferForDump;
    /**< Allocates the extra buffer for saving the ISP output,
         Used for debug only */
} IssM2mIspLink_CreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Iss M2m Isp Link register and init
 *
 * Creates the tasks for the link. Registers Link within System with
 * unique link ID and callback functions.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mIspLink_init(void);

/**
 *******************************************************************************
 *
 * \brief Iss M2m Isp Link de-register and de-init
 *
 * Delete the tasks and de-registers itself from the system.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssM2mIspLink_deInit(void);


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
static inline void IssM2mIspLink_CreateParams_Init(
    IssM2mIspLink_CreateParams *pPrm);



/**
 *******************************************************************************
 *
 * \brief Checks if given mode is wdr or not
 *
 * \param  opMode [In] ISP operating mode
 *
 * \return  TRUE if given mode is wdr mode
 *          FALSE otherwise
 *
 *******************************************************************************
 */
static inline Bool IssM2mIspLink_IsWdrMode(IssM2mIspLink_OperatingMode opMode);

/**
 *******************************************************************************
 *
 * \brief Checks if given mode is wdr merge mode or now
 *
 * \param  opMode [In] ISP operating mode
 *
 * \return  TRUE if given mode is wdr mode
 *          FALSE otherwise
 *
 *******************************************************************************
 */
static inline Bool IssM2mIspLink_IsWdrMergeMode(
    IssM2mIspLink_OperatingMode opMode);

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
static inline void IssM2mIspLink_CreateParams_Init(
    IssM2mIspLink_CreateParams *pPrm)
{
    UInt32 chId, queId;
    IssM2mIspLink_ChannelParams *pChPrm;

    memset(pPrm, 0, sizeof(IssM2mIspLink_CreateParams));

    for(queId = 0U; queId < ISSM2MISP_LINK_INPUTQUE_MAXNUM; queId++)
    {
        pPrm->inQueParams[queId].prevLinkId = SYSTEM_LINK_ID_INVALID;
    }

    for(queId=0; queId<ISSM2MISP_LINK_OUTPUTQUE_MAXNUM; queId++)
    {
        pPrm->outQueParams[queId].nextLink = SYSTEM_LINK_ID_INVALID;
    }


    for(chId = 0U; chId < ISSM2MISP_LINK_MAX_CH; chId++)
    {
        pChPrm = &pPrm->channelParams[chId];

        pChPrm->inBpp = SYSTEM_BPP_BITS12;
        pChPrm->decmpBpp = SYSTEM_BPP_BITS20;
        pChPrm->operatingMode = ISSM2MISP_LINK_OPMODE_12BIT_LINEAR;
        pChPrm->numBuffersPerCh = ISSM2MISP_LINK_NUM_BUFS_PER_CH_DEFAULT;
        pChPrm->enableOut[ISSM2MISP_LINK_OUTPUTQUE_IMAGE_RSZ_A]  = 1U;
        pChPrm->outParams.heightRszA = 720U;
        pChPrm->outParams.widthRszA  = 1280U;
        pChPrm->outParams.winWidthH3a = 16U;
        pChPrm->outParams.winHeightH3a = 16U;
        pChPrm->outParams.dataFormat = SYSTEM_DF_YUV420SP_UV;
        pChPrm->useBufSizePrmsFlag = 0U;
        pChPrm->horizontalFlip = 0U;
        pChPrm->verticalFlip = 0U;
    }
}


/**
 *******************************************************************************
 *
 * \brief Checks if given mode is wdr or not
 *
 * \param  opMode [In] ISP operating mode
 *
 * \return  TRUE if given mode is wdr mode
 *          FALSE otherwise
 *
 *******************************************************************************
 */
static inline Bool IssM2mIspLink_IsWdrMode(IssM2mIspLink_OperatingMode opMode)
{
    Bool status = FALSE;

    if ((ISSM2MISP_LINK_OPMODE_1PASS_WDR == opMode) ||
        (ISSM2MISP_LINK_OPMODE_2PASS_WDR == opMode) ||
        (ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED == opMode))
    {
        status = (Bool)TRUE;
    }

    return (status);
}


/**
 *******************************************************************************
 *
 * \brief Checks if given mode is wdr merge mode or now
 *
 * \param  opMode [In] ISP operating mode
 *
 * \return  TRUE if given mode is wdr mode
 *          FALSE otherwise
 *
 *******************************************************************************
 */
static inline Bool IssM2mIspLink_IsWdrMergeMode(
    IssM2mIspLink_OperatingMode opMode)
{
    Bool status = FALSE;

    if ((ISSM2MISP_LINK_OPMODE_2PASS_WDR == opMode) ||
        (ISSM2MISP_LINK_OPMODE_2PASS_WDR_LINE_INTERLEAVED == opMode))
    {
        status = (Bool)TRUE;
    }

    return (status);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
