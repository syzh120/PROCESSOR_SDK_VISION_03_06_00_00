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
 *   \defgroup ISSCAPTURE_LINK_API ISS Capture Link API
 *
 *
 *   ISS Capture Link is used to capture video frames from ISS ports
 *   Camera Rx Phy (CSI2 / LVDS) OR Parallel Port and store in DDR.
 *   Data path which gets serviced by this link is as follows
 *   CSI2 / LVDS / Parallel port -> CAL -> DDR
 *
 *   Each single capture interface needs one instantiation
 *   of the ISS capture link.
 *
 *   The captured frames will be output on a single output queue. In case of
 *      CSI2 interface multiple virtual channels can be captured. For every
 *      virtual channel, the captured frame will sent on a separate channel but
 *      on the same output queue.
 *   The output queue can in turn to be connected to another link like M2M ISP
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file issCaptureLink.h
 *
 * \brief ISS Capture link API public header file.
 *
 * \version 0.0 (Apr 2014) : [PS] First version
 * \version 0.1 (Apr 2015) : [Suj] Updated to support multiple channel
 *                                  reception on CSI2 interface.
 *
 *******************************************************************************
 */

#ifndef ISSCAPTURE_LINK_H_
#define ISSCAPTURE_LINK_H_

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
 * \brief Max Channels number of channel that could be received.
 *      Note only CSI2 interface supports capture of multiple channels. For
 *      other interfaces, we can capture only 1 channel.
 *******************************************************************************
*/
#define ISSCAPT_LINK_MAX_CH          (8U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of complext io instances supported.
 *        On TDA3xX, there is only one complex io instance whereas on TDA2EX
 *        there are two instances of complex io.
 *        This macro is mainly used for reserving memory.
 *
 *******************************************************************************
*/
#define ISSCAPT_LINK_MAX_CMPLXIO_INST    (2U)

/**
 *******************************************************************************
 *
 * \brief Controls the default number of output buffer allocated for each
 *          channel.
 *
 *******************************************************************************
*/
#define ISSCAPTURE_LINK_NUM_BUFS_DEFAULT    (3U)


/* @} */

/* Control Command's    */

/**
    \ingroup LINK_API_CMD
    \addtogroup ISSCAPTURE_LINK_API_CMD  ISS Capture Link Control Commands

    @{
*/

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
 *   \param None
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSCAPTURE_LINK_CMD_SAVE_FRAME             (0x5000U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Return's pointer to saved frame
 *
 *   \param IssCaptureLink_GetSaveFrameStatus   [OUT]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define ISSCAPTURE_LINK_CMD_GET_SAVE_FRAME_STATUS      (0x5001U)

/**
 *******************************************************************************
 *
 *   \brief Link CMD: To enable detection & reporting of errors.
 *
 *   \param IssCaptureLink_SetErrorNotification   [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *   \attention All the error cannot be detected on all the interfaces. Please
 *              refer IssCaptureLink_DetectableErrors for details.
 *
 *              This command is honoured only when CAL is idle (i.e. capture has
 *              not yet started)
 *
 *******************************************************************************
 */
#define ISSCAPTURE_LINK_CMD_SET_ERROR_NOTIFICATION     (0x5002U)

/* @} */


/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *  \brief List the errors that could be detected when receiving via CSI2 &
 *          parallel interface.
 *
 *          Values of these each members is expressed in power of 2. This to
 *          enable notification/registration of multiple error in one call.
 *******************************************************************************
*/
typedef enum
{
    ISSCAPTURE_LINK_ENABLE_ERROR_ECC_NO_CORRECTION = 1,
    /**< Detect un correctable ECC errors. Indicate that there were more than
            1 bit ECC errors. This is catastrophic error, frames received on any
            virtual channel could be corrupted.
            Detectable on CSI2 interface only */
    ISSCAPTURE_LINK_ENABLE_ERROR_FIFO_OVERFLOW = 2,
    /**< Detect internal FIFO overflows.
            This is an catastrophic error, indicates that the CAL could not
            write all the received data. Typically indicates a system problem/
            error.
            Detectable on CSI2 & parallel interface */
    ISSCAPTURE_LINK_ENABLE_ERROR_CRC_MISMATCH = 4,
    /**< CRC computed (& sent) by the sensor do not match with CRC computed.
            Enables CRC verification for data
            Once enabled, this is enabled for all virtual channels that are
            active.
            This is a catastrophic error, indicates that the data transmitted by
            the sensor is altered before it was received by the sensor.
            Detectable on CSI2 interface only */
    ISSCAPTURE_LINK_ENABLE_ERROR_ECC_CORRECTED = 8,
    /**< There was 1 bit ECC, which was corrected
            Enable detection of ECC correction
            Once enabled, this is enabled for all virtual channels that are
            active.
            Usually indicate a potential problem
            Detectable on CSI2 interface only. */
    ISSCAPTURE_LINK_FORCE32BITS = 0x7FFFFFFF
    /**< To make sure enum is 32 bits */

} IssCaptureLink_DetectableErrors;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
*/

/**
 *******************************************************************************
 *  \brief Callback that is called when a frame is received at this link
 *
 *  \param appObj [IN] User pointer specified during create
 *  \param pFrame [IN] Pointer to the received frame
 *
 *******************************************************************************
 */
typedef Void (*IssCaptureLink_Callback)(Void *appObj,
                            System_Buffer *pBuffer);


/**
 *******************************************************************************
 *  \brief Callback that is called when an frame ERROR is detected.
 *
 *  \param appObj [IN] User pointer specified during create
 *  \param pFrame [IN] Pointer to the received frame
 *
 *  \return SYSTEM_FRAME_STATUS_COMPLETED, when the link could further process
 *      this frame (other links connected to this link can receive & process),
 *      SYSTEM_FRAME_STATUS_ABORTED If this frame is NOT to be processed i.e.
 *      discarded. Other links connected to this will not receive this frame.
 *
 *******************************************************************************
 */
typedef System_VideoFrameStatus (*IssCaptureLink_ErrCallback)(Void *appObj,
                                System_Buffer *pBuffer,
                                System_VideoFrameStatus error);

/**
 *******************************************************************************
 *  \brief Information of saved RAW data frame
 *******************************************************************************
 */
typedef struct
{
    UInt32 isSaveFrameComplete;
    /**< TRUE: Frame is saved at address mentioned in 'bufAddr'
     *   FALSE: Frame is not yet saved, try after some time
     */

    UInt32 bufAddr;
    /**< Address where frame is saved */

    UInt32 bufSize;
    /**< Size of buffer where frame is saved */

} IssCaptureLink_GetSaveFrameStatus;

/**
 *******************************************************************************
 *  \brief Configure the position and order of lane for the complex IO.
 *******************************************************************************
 */
typedef struct
{
    UInt32 pol;
    /**< TRUE configures for - / + order of differential signal.
        + / - order otherwise */
    UInt32 position;
    /**< Specify if this lane is to be used, if so, on which position.
        0x0 - Not used / disabled lane
        0x1 - Position 1
        0x2 - Position 2
        0x3 - Position 3
        0x4 - Position 4
        0x5 - Position 5 */
} IssCaptureLink_CalCmplxIoLaneCfg;

/**
 *******************************************************************************
 *  \brief Lane configuration complex IO.
 *******************************************************************************
 */
typedef struct
{
    IssCaptureLink_CalCmplxIoLaneCfg clockLane;
    /**< Configure position and order of differential signal */
    IssCaptureLink_CalCmplxIoLaneCfg data1Lane;
    /**< Configure position and order of differential signal */
    IssCaptureLink_CalCmplxIoLaneCfg data2Lane;
    /**< Configure position and order of differential signal */
    IssCaptureLink_CalCmplxIoLaneCfg data3Lane;
    /**< Configure position and order of differential signal */
    IssCaptureLink_CalCmplxIoLaneCfg data4Lane;
    /**< Configure position and order of differential signal */
} IssCaptureLink_CalCmplxIoCfg;

/**
 *******************************************************************************
 * \brief ISS capture link CSI2 related parameters
 *******************************************************************************
*/
typedef struct
{
    uint32_t                           isCmplxIoCfgValid;
    /**< Specify if the complex IO configurations should be applied or the
            default config should be applied.
        TRUE - Complex IO configuration provided below is valid and will be
                applied.
        FALSE - Default complex IO configuration would be applied. */
    IssCaptureLink_CalCmplxIoCfg       cmplxIoCfg;
    /**< Number of data lanes that will be used - Value between 1 - 4 */

    UInt32                  csi2PhyClk;
    /**< Clock provided to CSI2 Phy by the SoC */

} IssCaptureLink_Csi2Params;

/**
 *******************************************************************************
 * \brief ISS capture link LVDS related parameters.
 *          LVDS interface is not yet supported.
 *******************************************************************************
*/
typedef struct
{
    UInt32 reserved;
    /* Reserved */
} IssCaptureLink_LvdsParams;

/**
 *******************************************************************************
 * \brief ISS capture link Parallel port related parameters.
 *
 * Reserved for future.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 reserved;
    /* Reserved */
} IssCaptureLink_ParallelPortParams;


/**
 *******************************************************************************
 * \brief Structure for setting the output buffer and stream
 *        parameters for capture.
 *******************************************************************************
*/
typedef struct
{
    UInt32                          width;
    /**<  Output width, in pixels.
     *
     *   This represents the output width of the data that is captured
     */

    UInt32                          height;
    /**< Output height, in lines.
     *
     *   This represents the output height of the data that is captured
     */

    System_VideoDataFormat          dataFormat;
    /**< Output Data format, valid options are
     *
     *   SYSTEM_DF_BAYER_RAW
     */

    System_Csi2DataFormat           inCsi2DataFormat;
    /**< Specify CSI2 input data format.
     *
     *   Valid only when videoIfMode == SYSTEM_VIFM_SCH_CSI2.
     *   Ignored for others
     */

    UInt32                          inCsi2VirtualChanNum;
    /**< Specify the CSI2 virtual channel number
     *
     *   Valid only when videoIfMode == SYSTEM_VIFM_SCH_CSI2.
     *   0 <= value < 4.
     *   Ignored for others
     */

    UInt32                          maxWidth;
    /**< Max width in pixels
     *
     *   This should be >= width
     *   This field decides the width of buffer that is allocated.
     */

    UInt32                          maxHeight;
    /**< Max height in pixels
     *
     *   This should be >= height
     *   This field decides the height of buffer that is allocated.
     */

    UInt32                          numOutBuf;
     /**< Number of output buffer to allocate */

    System_VideoDataFormat          outDataFormat;
    /**< Specify output video data format. Expected to be used when standard
     *   video format is transported on CSI2 I/F with an non CSI2 data format.
     *
     *   Valid only when videoIfMode == SYSTEM_VIFM_SCH_CSI2 &&
     *   inCsi2DataFormat is SYSTEM_CSI2_RAW10 and output format one of
     *   (SYSTEM_DF_YUV422I_UYVY, SYSTEM_DF_YUV422I_YUYV,
     *    SYSTEM_DF_YUV422I_YVYU, SYSTEM_DF_YUV422I_VYUY)
     */

    UInt32                          phyInstance;
    /**< Specify the instance of PHY on which this stream is expected to be
            received from.
        Valid values are 0 & 1.
        Please refer device specific TRM for number of PHY's supported.
        for TDA3x it should be 0
        for TDA2x Entry it should be 0
        for TDA2x Eco it can be 0 or 1 */
    System_BitsPerPixel             outBpp;
    /**< Output Storage format in BPP,
         For most of the cases, it is set to SYSTEM_BPP_BITS16.
         For SRV usecases, it can be used to get output in MIPI format */
} IssCaptureLink_OutParams;


/**
 *******************************************************************************
 * \brief ISS capture link creation parameters.
 *******************************************************************************
*/
typedef struct
{
    System_VideoIfMode videoIfMode;
    /**< [IN] Video capture mode.
     *
     *    Valid values are,
     *    SYSTEM_VIFM_SCH_CSI2  - CSI2 - csi2Params are used
     *    SYSTEM_VIFM_SCH_LVDS  - LVDS - lvdsParams are used
     *    SYSTEM_VIFM_SCH_CPI   - parallel port - parallelPortParams are used
     */

    System_VideoIfWidth videoIfWidth;
    /**< [IN] Video interface mode. */

    System_CaptBufferCaptMode bufCaptMode;
    /**< [IN] Buffer capture mode.
     *   For valid values see #System_CaptBufferCaptMode. */

    IssCaptureLink_Csi2Params csi2Params[ISSCAPT_LINK_MAX_CMPLXIO_INST];
    /**< Only valid when videoIfMode == SYSTEM_VIFM_SCH_CSI2
     */

    UInt32                    numCh;
    /**< Number of channels to be received.
     *  0 <= value < 4 (ISSCAPT_LINK_MAX_CH)
     *  Valid only when videoIfMode == SYSTEM_VIFM_SCH_CSI2.
     *  For other it HAS to be 1.
     */

    IssCaptureLink_LvdsParams lvdsParams;
    /**< Only valid when videoIfMode == SYSTEM_VIFM_SCH_LVDS
     */

    IssCaptureLink_ParallelPortParams parallelPortParams;
    /**< Only valid when videoIfMode == SYSTEM_VIFM_SCH_CPI
     */

    IssCaptureLink_OutParams outParams[ISSCAPT_LINK_MAX_CH];
    /**< Data Output related parameters. */

    System_LinkOutQueParams outQueParams;
    /**< Output queue information */

    IssCaptureLink_Callback callback;
    /**< User defined callback that is called when a frame is received at
     *   this link
     */

    Void                    *appObj;
    /**< User specified pointer that is returned to user via the callback */

    UInt32                  allocBufferForRawDump;
    /**< [IN] Flag to allocate extra frame buffer for RAW dump
              1, extra frame buffer is allocated
              0, extra frame buffer is not allocated, so RAW frames
                 cannot be dumped */

    System_LinkMemAllocInfo memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */

} IssCaptureLink_CreateParams;

/**
 *******************************************************************************
 *  \brief Used to enable / disable error detection / reporting
 *******************************************************************************
 */
typedef struct
{
    IssCaptureLink_ErrCallback errorCallback;
    /**< Function pointer that would be called on detection of configured
     *      errors
     */

    UInt32 errorsToDetect;
    /**< Enable detection of errors, defined in #IssCaptureLink_DetectableErrors
     *      Each error is logically ORed, as show below
     *      errorToDetect = ISSCAPTURE_LINK_ENABLE_ERROR_FIFO_OVERFLOW |
     *                      ISSCAPTURE_LINK_ENABLE_ERROR_CRC_MISMATCH
     */

    Void *appObj;
    /**< User specified pointer that is returned to user via the callback */

} IssCaptureLink_SetErrorNotification;

/*******************************************************************************
 *  Functions Prototypes
 *******************************************************************************
 */
static inline void IssCaptureLink_CreateParams_Init (
                                            IssCaptureLink_CreateParams *pPrm);

/**
 *******************************************************************************
 *
 * \brief Iss Capture link register and init
 *
 * Creates the tasks for the link. Registers Link within System with
 * unique link ID and callback functions.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_init(void);


/**
 *******************************************************************************
 *
 * \brief Iss Capture link de-register and de-init
 *
 * Delete the tasks and de-registers itself from the system.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 IssCaptureLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Set defaults for creation time parameters
 *
 * \param  pPrm [OUT] Create parameters for capture link.
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
static inline void IssCaptureLink_CreateParams_Init (
                                            IssCaptureLink_CreateParams *pPrm)
{
    UInt32 cnt;
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(IssCaptureLink_CreateParams));

    pPrm->videoIfMode = SYSTEM_VIFM_SCH_CSI2;
    pPrm->videoIfWidth = SYSTEM_VIFW_4LANES;
    pPrm->bufCaptMode = SYSTEM_CAPT_BCM_LAST_FRM_REPEAT;
    pPrm->allocBufferForRawDump = 0U;
    pPrm->numCh = 1U;

    for (cnt = 0u; cnt < ISSCAPT_LINK_MAX_CH; cnt ++)
    {
        pPrm->outParams[cnt].width = 1280U;
        pPrm->outParams[cnt].height = 720U;
        pPrm->outParams[cnt].dataFormat = SYSTEM_DF_BAYER_BGGR;
        pPrm->outParams[cnt].inCsi2DataFormat = SYSTEM_CSI2_RAW12;
        pPrm->outParams[cnt].outDataFormat = SYSTEM_DF_INVALID;
        pPrm->outParams[cnt].inCsi2VirtualChanNum = 0U;
        pPrm->outParams[cnt].maxWidth = pPrm->outParams[0U].width;
        pPrm->outParams[cnt].maxHeight = pPrm->outParams[0U].height;
        pPrm->outParams[cnt].numOutBuf = ISSCAPTURE_LINK_NUM_BUFS_DEFAULT;
        pPrm->outParams[cnt].outBpp = SYSTEM_BPP_BITS16;
    }

    pPrm->csi2Params[0].isCmplxIoCfgValid              = (UInt32) TRUE;
    pPrm->csi2Params[0].cmplxIoCfg.clockLane.pol       = (UInt32) FALSE;
    pPrm->csi2Params[0].cmplxIoCfg.clockLane.position  = 2U;
    pPrm->csi2Params[0].cmplxIoCfg.data1Lane.pol       = (UInt32) FALSE;
    pPrm->csi2Params[0].cmplxIoCfg.data1Lane.position  = 1U;
    pPrm->csi2Params[0].cmplxIoCfg.data2Lane.pol       = (UInt32) FALSE;
    pPrm->csi2Params[0].cmplxIoCfg.data2Lane.position  = 3U;
    pPrm->csi2Params[0].cmplxIoCfg.data3Lane.pol       = (UInt32) FALSE;
    pPrm->csi2Params[0].cmplxIoCfg.data3Lane.position  = 4U;
    pPrm->csi2Params[0].cmplxIoCfg.data4Lane.pol       = (UInt32) FALSE;
    pPrm->csi2Params[0].cmplxIoCfg.data4Lane.position  = 5U;
    pPrm->csi2Params[0].csi2PhyClk                     = 400U;
    pPrm->outParams[0U].phyInstance                    = 0U;

}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
