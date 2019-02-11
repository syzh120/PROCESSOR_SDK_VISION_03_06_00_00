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
 *   \defgroup CAPTURE_LINK_API Capture Link API
 *
 *
 *   Capture Link is used to capture video frames from VIP ports.
 *   Same link can be used to capture frames from multiple VIP ports.
 *   Each VIP port can be configured individually during create time.
 *
 *   The frames from these VIP ports can be output over a single output queue.
 *   The output queue can in turn to be connected to another link like Display.
 *   A unique channel ID is assigned to each VIP port, to distinguish frames
 *   from different VIP ports. This allows the next to handle each channel
 *   individually.
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file captureLink.h
 *
 * \brief Capture link API public header file.
 *
 * \version 0.0 (Jun 2013) : [HS] First version
 * \version 0.1 (Jul 2013) : [HS] Updates as per code review comments
 * \version 0.2 (Jul 2014) : [VT] Add subframe support
 *******************************************************************************
 */

#ifndef CAPTURE_LINK_H_
#define CAPTURE_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <include/link_api/systemLink_ipu1_0_params.h>
#include <include/link_api/system_inter_link_api.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 *
 * \brief Max outputs per VIP instance
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define CAPTURE_LINK_MAX_OUTPUT_PER_INST    (UInt32)(1U)

/**
 *******************************************************************************
 *
 * \brief Max Channels per output queue
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define CAPTURE_LINK_MAX_CH_PER_OUT_QUE     (UInt32)(8U)

/**
 *******************************************************************************
 *
 * \brief Indicates number of output buffers to be set to default
 *         value by the capture link
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT (UInt32)(4U)


/* @} */

/* Control Command's    */

/**
    \ingroup LINK_API_CMD
    \addtogroup CAPTURE_LINK_API_CMD  Capture Link Control Commands

    @{
*/

/**
 *******************************************************************************
 * \brief Link CMD: Command to set the Scalar Parameters.
 *
 *   This command is used to set the scalar parameters in VIP port.
 *
 *   \param CaptureLink_ScParams *pPrm [IN] queId, chId and scaling params.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define CAPTURE_LINK_CMD_SET_SC_PARAMS   (0x1003U)


/**
 *******************************************************************************
 *
 * \brief command to get VIP output ocmc frame info when subframe is enabled
 *
 * \param None
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_GET_SUBFRAME_INFO    (0x1004U)

/**
 *******************************************************************************
 *
 * \brief Command to update the Frame Skip Mask
 *
 * \param UInt32 * pPrm [IN] Frame Skip Mask to be applied
 *
 *******************************************************************************
 */
#define CAPTURE_LINK_CMD_SET_FRAME_SKIP_MASK   (0x1005U)



/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *  \brief Callback that is called when a frame is received at this link
 *
 *  \param appObj [IN] User pointer specified during create
 *  \param pFrame [IN] Pointer to the received frame
 *
 *  \return if return value is not SYSTEM_LINK_STATUS_SOK, frame is dropped
 *
 *******************************************************************************
 */
typedef Int32 (*CaptureLink_Callback)(Void *appObj,
                            System_Buffer *pBuffer);

/**
 *******************************************************************************
 *
 * \brief Params for \ref CAPTURE_LINK_CMD_SET_SC_PARAMS
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 queId;
    /**< Output Que ID */
    UInt32 chId;
    /**< Output CH ID */
    UInt32 scEnable;
    /**< Flag to enable/disable Scaler */
    UInt32 inWidth;
    /**< Scalar Input Width */
    UInt32 inHeight;
    /**< Scalar Input Height */
    UInt32 outWidth;
    /**< Scalar Input Width */
    UInt32 outHeight;
    /**< Scalar Input Height */
} CaptureLink_ScParams;

/**
 *******************************************************************************
 * \brief Structure for setting the output buffer and stream
 *        parameters for capture.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                         width;
    /**<  Output width, in pixels.
     *   This represents the scaler output width to be programmed if scaler
     *   is used. Otherwise output width is equal to the capture source width
     *   or is limited by max width parameter.
     */

    UInt32                         height;
    /**< Output height, in lines.
     *   This represents the scaler output height to be programmed if scaler
     *   is used. Otherwise output height is equal to the capture source height
     *   or is limited by max height parameter.
     */

    System_VideoDataFormat         dataFormat;
    /**< Output Data format, valid options are
     *   SYSTEM_DF_YUV422I_YUYV,<br>
     *   SYSTEM_DF_YUV420SP_UV,<br>
     *   SYSTEM_DF_YUV422SP_UV,<br>
     *   SYSTEM_DF_BGR24_888,<br>
     *   SYSTEM_DF_ABGR32_8888, <br>
     *   SYSTEM_DF_RAW_VBI.<br>
     *   For valid values see #System_VideoDataFormat.<br>
     *
     *   If SYSTEM_DF_YUV422SP_UV is used as output format, it must
     *   be the first output format (output format at the
     *   index 0 in outStreamInfo in #CaptureLink_VipInstParams).
     */
    UInt32                         maxWidth;
    /**< There is a scalar in VIP path. so width can be changed at run time.
     *  Maximum width that can be scaled to at run time. This should be
     *  smaller than or equal to input width, since scalar support only
     *  downscaling.
     */

    UInt32                         maxHeight;
    /**< There is a scalar in VIP path. so height can be changed at run time.
     *  Maximum height that can be scaled to at run time. This should be
     *  smaller than or equal to input height, since scalar support only
     *  downscaling.
     */

    UInt32                         scEnable;
    /**< TRUE: Use scaler before writing video data to memory,
     *   FALSE: Scaler is not used in capture path
     *   MUST be FALSE for line-multiplexed, pixel multiplexed modes. */

    System_SubFrameParams          subFrmPrms;
    /**< Sub frame parameters. */

    UInt32                         frameSkipMask;
    /**<
     *   Frame Skip Mask (bit0..bit29) bitN = 1 Skip frame,
     *   bitN = 0 DO NOT skip frame
     *   Example, 0x0 for no frame skip, 0x2AAAAAAA for skipping
     *   alternate frames.
     */
} CaptureLink_OutParams;

/**
 *******************************************************************************
 * \brief Structure for setting input stream parameters for capture link
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                  width;
    /**< Input source width, MUST be >= actual or expected
     *   video source input width.
     *   This represents the scaler input width to be programmed if scaler
     *   is used.
     */
    UInt32                  height;
    /**< Input source height, MUST be >= actual or expected
     *   video source input height.
     *   This represents the scaler input height to be programmed if scaler
     *   is used.<br>
     *   Height should be field height in case source is interlaced<br>
     *   Height should be frame height in case source is progressive<br>
     */
    System_VideoDataFormat  dataFormat;
    /**< Input source color data format, valid values are given below<br>
     *   SYSTEM_DF_YUV422P, ('P' is not relavent for input data format)<br>
     *   SYSTEM_DF_YUV444P, ('P' is not relavent for input data format)<br>
     *   SYSTEM_DF_RGB24_888.<br>
     *   For valid values see #System_VideoDataFormat.
     */
    System_VideoScanFormat  scanFormat;
    /**< Input source scan format - interlaced or progressive.
     *   For valid values see #System_VideoScanFormat.
     */

} CaptureLink_InParams;

/**
 *******************************************************************************
 * \brief Scaling parameters for incoming stream.
 *
 * Only valid when scEnable is or can be TRUE.
 * Note, Only downscaling is supported
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
typedef struct
{
    System_CropConfig    inCropCfg;
    /**< Scaler input crop config. */
    System_ScConfig      scCfg;
    /**< Scaler config. */
    System_ScCoeffParams scCoeffCfg;
    /**< Scaler coeff config. */
    UInt32               userCoeff;
    /**<
      Set this flag if Vps_scCoeffParams is loaded with coefficient set
     *  which user needs to program. Else driver will decided the right
     *  coefficient flag
     */
} CaptureLink_VipScParams;

/**
 *******************************************************************************
 * \brief VIP Port configuration.
 *
 * This strucutre mainly deals with paramters regarding how external sensor
 * or decoder is connected with VIP Port.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32              clipActive;
    /**< FALSE: Do not clip active Data
     *   TRUE : Clip active Data. */
    UInt32              clipBlank;
    /**< FALSE: Do not clip blanking Data
     *   TRUE : Clip blanking Data. */
    System_VideoIfWidth intfWidth;
    /**< Interface mode. */
} CaptureLink_VipPortIntfConfig;


/**
 *******************************************************************************
 * \brief configure VIP port for discrete sync capture.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                                  fidSkewPostCnt;
    /**< Post count value when using vsync skew in FID determination. */
    UInt32                                  fidSkewPreCnt;
    /**< Pre count value when using vsync skew in FID determination. */
    System_VipLineCaptureStyle              lineCaptureStyle;
    /**< For valid values see #System_VipLineCaptureStyle. */
    System_VipFidDetectMode                 fidDetectMode;
    /**< For valid values see #System_VipFidDetectMode. */
    System_Polarity                         actvidPol;
    /**< For valid values see #System_Polarity. */
    System_Polarity                         vsyncPol;
    /**< For valid values see #System_Polarity. */
    System_Polarity                         hsyncPol;
    /**< For valid values see #System_Polarity. */
    UInt32                                  discreteBasicMode;
    /**< FALSE = Normal Discrete Mode, TRUE = Basic Discrete Mode.
     *   TRUE = DE signal need not be active during the VBLANK period. Most of
     *     the encoder provide the discrete signals in this way.
     *   FALSE = DE signal needs to be active during the VBLANK period. */
} CaptureLink_VipPortDisConfig;

/**
 *******************************************************************************
 * \brief Configure VIP port for embedded and discrete sync common
 *        configuration
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    System_VipCtrlChanSel       ctrlChanSel;
    /**< On which channel control signals is coming. Like embedded syncs etc.
     *   For valid values see #System_VipCtrlChanSel. */
    System_VipAncChSel8b        ancChSel8b;
    /**< For valid values see #System_VipAncChSel8b.
     * On which channel control signals is coming. Like embedded syncs etc.*/
    System_EdgePolarity         pixClkEdgePol;
    /**< Pixel clock polarity, For valid values see #System_EdgePolarity. */
    UInt32                      invertFidPol;
    /**< FALSE: Keep FID as found, TRUE: Invert Value of FID. */
    UInt32                      enablePort;
    /**< '0' = Disable Port, '1' = Enable Port.
     *   Keep 0 when doing setCfg, set to 1 using enablePort API. */
    /**< '0' = Normal,  '1' = Clear Async FIFO Write Logic. */
    UInt32                      expectedNumLines;
    /**< Expected number of lines in the source. */
    UInt32                      expectedNumPix;
    /**< Expected number of pixels per line in the source. */
    System_VipRepackMode        repackerMode;
    /**< How incoming data is repacked into memory */
} CaptureLink_VipPortComConfig;

/**
 *******************************************************************************
 * \brief VIP port crop configuration.
 *
 * VIP port can crop the incoming stream. This structure represents the cropping
 * configuration. Its mostly used to crop blanking data if present with data.
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32            srcNum;
    /**< Cropping module works on only one srcNum. */
    System_CropConfig cropCfg;
    /**< VIP Port crop configuration. */
} CaptureLink_VipPortCropConfig;


/**
 *******************************************************************************
 * \brief VIP port configuration parameter
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    System_VipSyncType              syncType;
    /**< Sync Type. Also indicates which among
     *   embCfg and disCfg contains valid data. */
    UInt32                          actCropEnable;
    /**< Is cropping enabled for active video channel. Indicates if actCropCfg
     *   contains valid data. */
    UInt32                          ancCropEnable;
    /**< Is cropping enabled for ancillary channel. Indicates if ancCropCfg
     *   contains valid data. */

    CaptureLink_VipPortIntfConfig   intfCfg;
    /**< Basic port configuration parameters. */

    CaptureLink_VipPortDisConfig    disCfg;
    /**< Configuration parameters specific to Discrete Sync mode. */

    CaptureLink_VipPortComConfig    comCfg;
    /**< Configuration parameter common to both Embedded/Discrete Sync modes. */

    CaptureLink_VipPortCropConfig   actCropCfg;
    /**< Cropping parameters for active video channel. */
    CaptureLink_VipPortCropConfig   ancCropCfg;
    /**< Cropping parameters for ancillary channel. */
} CaptureLink_VipPortConfig;


/**
 *******************************************************************************
 * \brief configuration for VIP instance.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                         vipInstId;
    /**< VIP capture driver instance ID, see SYSTEM_CAPTURE_INST_VIPx_PORTy */
    System_VideoIfMode             videoIfMode;
    /**< [IN] Video capture mode. */
    System_VideoIfWidth            videoIfWidth;
    /**< [IN] Video interface mode. */
    System_CaptBufferCaptMode      bufCaptMode;
    /**< [IN] Buffer capture mode.
     *   For valid values see #System_CaptBufferCaptMode. */
    UInt32                         numStream;
    /**< Number of outputs per VIP */
    CaptureLink_InParams           inParams;
    /**< Information about input parameters */

    CaptureLink_OutParams          outParams[CAPTURE_LINK_MAX_OUTPUT_PER_INST];
    /**< Information about each output */

    CaptureLink_VipScParams        scPrms;
    /**< Scaler parameters to use when
     *   outParams[x].scEnable = TRUE
     *   Parameters are ignored when outStreamInfo[x].scEnable = FALSE.
     *
     *   Note: Upscaling is not supported in the inline scaling in capture
     *   path because of hardware limitation.
     */
    CaptureLink_VipPortConfig      vipPortCfg;
    /**< VIP Parser port config */
    UInt32                         numBufs;
    /**< Number of buffers to be allocated for the capture link. Minimum
     *   number of buffers required is 3 for capture link to capture without
     *   frame drops
     */

} CaptureLink_VipInstParams;

/**
 *******************************************************************************
 * \brief capture link DSS WB configuration parameters.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                      dssWbInstId;
    /**< DSS WB capture driver instance ID */
    System_DssWbInputParams     dssWbInputPrms;
    /**< Capture DSS WB additional Input parameters. */
    System_DssWbOutputParams    dssWbOutputPrms;
    /**< Capture DSS WB additional output parameters. */
    UInt32                      numBufs;
    /**< Number of buffers to be allocated for the capture link. Minimum
     *   number of buffers required is 3 for capture link to capture without
     *   frame drops
     */

} CaptureLink_DssWbInstParams;

/**
 *******************************************************************************
 * \brief capture link configuration parameters.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                      numVipInst;
    /**< Number of VIP instances in this link */

    CaptureLink_VipInstParams   vipInst[SYSTEM_CAPTURE_VIP_INST_MAX];
    /**< VIP instance information */

    UInt32                      numDssWbInst;
    /**< Number of DSS WB instances in this link */

    CaptureLink_DssWbInstParams dssWbInst[SYSTEM_CAPTURE_DSSWB_INST_MAX];
    /**< Dss WB capture instance information */

    System_LinkOutQueParams     outQueParams;
    /**< Output queue information */

    CaptureLink_Callback        callback;
    /**< User defined callback that is called when a frame is received at
     *   this link
     */

    Void                       *appObj;
    /**< User specified pointer that is returned to user via the callback */

    System_LinkMemAllocInfo memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */

} CaptureLink_CreateParams;

/**
 *******************************************************************************
 *
 * \brief Subframe buffer information to be exchanged between subframe capture
 * and process links
 *
 *******************************************************************************
 */
typedef struct {

    UInt32              inChannelId;
    /* [IN] Instance ID for which ocmcbuf Info is requested*/

    UInt32              ocmcCBufVirtAddr[SYSTEM_MAX_PLANES];
    /**< [OUT] OCMC buffer virtual start address*/

    UInt32              numLinesPerSubFrame;
    /**< [OUT] number of lines in every subframe*/

} CaptureLink_Subframe_Info;

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */

static inline void CaptureLink_CreateParams_Init(CaptureLink_CreateParams *pPrm);


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Capture link register and init
 *
 * Creates the tasks for the link. Registers Link within System with
 * unique link ID and callback functions.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_init(void);


/**
 *******************************************************************************
 *
 * \brief Capture link de-register and de-init
 *
 * Delete the tasks and de-registers itself from the system.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 CaptureLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Set defaults for in link channel information.
 *
 *  Currently defaults are set for vip_single_cam_view usecase.
 *  For any other use case example has to call this function
 *  and change the required parameter accordingly.
 *
 * \param  pPrm [OUT] Create parameters for capture link.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void CaptureLink_CreateParams_Init(CaptureLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    UInt32 i, streamId;
    CaptureLink_VipInstParams *pInstPrm;
    CaptureLink_InParams *pInprms;
    CaptureLink_OutParams *pOutprms;
    CaptureLink_VipScParams *pScPrms;
    CaptureLink_VipPortConfig    *pPortCfg;

    memset(pPrm, 0, sizeof(CaptureLink_CreateParams));

    pPrm->numVipInst = 1U;
    pPrm->numDssWbInst = 0U;

    for (i = 0U; i < SYSTEM_CAPTURE_VIP_INST_MAX; i++)
    {
        pInstPrm = &pPrm->vipInst[i];
        pInstPrm->vipInstId     =   i;
        pInstPrm->videoIfMode   =   SYSTEM_VIFM_SCH_DS_HSYNC_VSYNC;
        pInstPrm->videoIfWidth  =   SYSTEM_VIFW_8BIT;
        pInstPrm->bufCaptMode   =   SYSTEM_CAPT_BCM_LAST_FRM_REPEAT;
        pInstPrm->numStream     =   1U;

        pInprms = &pInstPrm->inParams;

        pInprms->width      =   1280U;
        pInprms->height     =   720U;
        pInprms->dataFormat =   SYSTEM_DF_YUV422P;
        pInprms->scanFormat =   SYSTEM_SF_PROGRESSIVE;

        for (streamId = 0U;
             streamId < CAPTURE_LINK_MAX_OUTPUT_PER_INST;
                streamId++)
        {
            pOutprms = &pInstPrm->outParams[streamId];
            pOutprms->width         =   800U;
            pOutprms->height        =   480U;
            pOutprms->dataFormat    =   SYSTEM_DF_YUV422P;
            pOutprms->maxWidth      =   pOutprms->width;
            pOutprms->maxHeight     =   pOutprms->height;
            pOutprms->scEnable      =   (UInt32) TRUE;
            pOutprms->subFrmPrms.subFrameEnable = (UInt32) FALSE;
            pOutprms->subFrmPrms.numLinesPerSubFrame = 0U;
            pOutprms->frameSkipMask = 0U;
        }
        pScPrms = &pInstPrm->scPrms;
        pScPrms->inCropCfg.cropStartX = 0U;
        pScPrms->inCropCfg.cropStartY = 0U;
        pScPrms->inCropCfg.cropWidth = pInprms->width;
        pScPrms->inCropCfg.cropHeight = pInprms->height;

        pScPrms->scCfg.bypass       = (UInt32) FALSE;
        pScPrms->scCfg.nonLinear    = (UInt32) FALSE;
        pScPrms->scCfg.stripSize    = 0U;

        pScPrms->userCoeff = (UInt32) FALSE;

        /* pScPrms->scCoeffCfg is not required in case
         * pScPrms->userCoeff is FALSE
         */
        pPortCfg = &pInstPrm->vipPortCfg;
        pPortCfg->syncType          =   SYSTEM_VIP_SYNC_TYPE_DIS_SINGLE_YUV;
        pPortCfg->ancCropEnable     =   (UInt32) FALSE;



        pPortCfg->intfCfg.clipActive    =   (UInt32) FALSE;
        pPortCfg->intfCfg.clipBlank     =   (UInt32) FALSE;
        pPortCfg->intfCfg.intfWidth     =   SYSTEM_VIFW_16BIT;

        pPortCfg->disCfg.fidSkewPostCnt     =   0U;
        pPortCfg->disCfg.fidSkewPreCnt      =   0U;
        pPortCfg->disCfg.lineCaptureStyle   =
            SYSTEM_VIP_LINE_CAPTURE_STYLE_ACTVID;
        pPortCfg->disCfg.fidDetectMode      =   SYSTEM_VIP_FID_DETECT_MODE_PIN;
        pPortCfg->disCfg.actvidPol          =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.vsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.hsyncPol           =   SYSTEM_POL_HIGH;
        pPortCfg->disCfg.discreteBasicMode  =   (UInt32) TRUE;

        pPortCfg->comCfg.ctrlChanSel        =   SYSTEM_VIP_CTRL_CHAN_SEL_7_0;
        pPortCfg->comCfg.ancChSel8b         =
            SYSTEM_VIP_ANC_CH_SEL_8B_LUMA_SIDE;
        pPortCfg->comCfg.pixClkEdgePol      =   SYSTEM_EDGE_POL_RISING;
        pPortCfg->comCfg.invertFidPol       =   (UInt32) FALSE;
        pPortCfg->comCfg.enablePort         =   (UInt32) FALSE;
        pPortCfg->comCfg.expectedNumLines   =   720U;
        pPortCfg->comCfg.expectedNumPix     =   1280U;
        pPortCfg->comCfg.repackerMode       =   SYSTEM_VIP_REPACK_CBA_TO_CBA;

        pPortCfg->actCropEnable                         =   (UInt32) TRUE;
        pPortCfg->actCropCfg.srcNum                     =   0U;
        pPortCfg->actCropCfg.cropCfg.cropStartX         =   0U;
        pPortCfg->actCropCfg.cropCfg.cropStartY         =   0U;
        pPortCfg->actCropCfg.cropCfg.cropWidth          =   1280U;
        pPortCfg->actCropCfg.cropCfg.cropHeight         =   720U;

        pPortCfg->ancCropCfg.srcNum                     =   0U;
        pPortCfg->ancCropCfg.cropCfg.cropStartX         =   0U;
        pPortCfg->ancCropCfg.cropCfg.cropStartY         =   0U;
        pPortCfg->ancCropCfg.cropCfg.cropWidth          =   0U;
        pPortCfg->ancCropCfg.cropCfg.cropHeight         =   0U;

        pInstPrm->numBufs = CAPTURE_LINK_NUM_BUFS_PER_CH_DEFAULT;

    }
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
