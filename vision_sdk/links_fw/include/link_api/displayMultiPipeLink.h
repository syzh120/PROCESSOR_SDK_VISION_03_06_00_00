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
 * \ingroup SAMPLE_MODULE_API
 * \defgroup DISPLAY_SYNC_PIPE_LINK_API Display Link API supporting synced pipes
 *
 * \brief  This module has the interface for using Display Link
 *
 *         Display Link is used to feed video frames over a video/graphics
 *         pipe to a connected VENC. The connection of input pipe to a VENC
 *         is done by Display Controller. This link deals with actually
 *         displaying the video/graphic frames from a previous link onto the
 *         display device.
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file displayMultiPipeLink.h
 *
 * \brief Display Sync Pipe Link API
 *
 * \version 0.0 (Jan 2017) : [BJ] First version
 *
 *******************************************************************************
 */

#ifndef DISPLAY_MULTI_PIPE_LINK_H_
#define DISPLAY_MULTI_PIPE_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <include/link_api/system.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */
/**
 *******************************************************************************
 *
 *   \brief Default value of maximum number of frames allowed to be
 *          queued into the display driver
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define DISPLAY_MP_LINK_MAX_DRIVER_QUEUE_LENGTH_DEFAULT (0U)


#define DISPLAY_MP_LINK_MAX_PIPE                  (2U)

/* @} */

/**
 *******************************************************************************
 *
 *   \ingroup LINK_API_CMD
 *   \addtogroup DISPLAY_MP_LINK_API_CMD Display Link Control Commands
 *
 *   @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *   \brief Link CMD: Switch input channel that is being displayed
 *
 *   SUPPORTED platforms - None of the platforms is supported this as of today
 *
 *   MUST be set by user
 *
 *   \param DisplayLink_SwitchChannelParams *pPrm [IN]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define DISPLAY_MP_LINK_CMD_SWITCH_CH                   (0x4000U)


/**
 *******************************************************************************
 *
 *   \brief Link CMD: Run time Command to get display performance statistics
 *
 *   \param DisplaySpLink_Statistics  [OUT]
 *
 *   \return SYSTEM_STATUS_SOK on success
 *
 *******************************************************************************
 */
#define DISPLAY_MP_LINK_CMD_GET_STATISTICS              (0x4003U)

/* @} */

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Enumerations for the display instances (Pipes) supported
 *
 *          List of the supported display instance IDs to be configured by
 *          user/App while creating a specific display link instance.
 *          Please note that SDK do not support multiple display link instances
 *          with same displayId. However Display link as such supported
 *          multiple instances with each configured with a unique displayId
 *******************************************************************************
*/
typedef enum
{
    DISPLAY_MP_LINK_INST_DSS_VID1 = 0U,
    /**< Video1 Pipeline. */
    DISPLAY_MP_LINK_INST_DSS_VID2 = 1U,
    /**< Video2 Pipeline. */
    DISPLAY_MP_LINK_INST_DSS_VID3 = 2U,
    /**< Video3 Pipeline. */
    DISPLAY_MP_LINK_INST_DSS_GFX1 = 3U,
    /**< GFX1 Pipeline. */
    DISPLAY_MP_LINK_INST_DSS_MAX = 4U,
    /**< Should be the last value of this enumeration.
     *   Will be used by Link/driver for validating the input parameters. */
    DISPLAY_MP_LINK_INST_DSS_FORCE32BITS = 0x7FFFFFFFU
    /**< This should be the last value after the max enumeration value.
     *   This is to make sure enum size defaults to 32 bits always regardless
     *   of compiler.
     */
} DisplayMpLink_displayID;

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */


/**
 *******************************************************************************
 *
 *   \brief Display link statistics
 *
 *          All count values are relative to last reset of the counter's
 *          Counter's are reset when 'resetStatistics' is TRUE or
 *          when 'Print Statistics' command is called.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 resetStatistics;
    /**< TRUE: Reset counter after getting the values */

    UInt32 elaspedTimeInMsec;
    /**< Time since since start last reset of statistics */

    UInt32 inBufRecvCount;
    /**< Number of frames received on active channel */

    UInt32 inBufDropCount;
    /**< Number of frames that were dropped and could not be displayed */

    UInt32 inBufDisplayCount;
    /**< Number of frames that were displayed on the screen */

    UInt32 displayIsrCount;
    /**< Number of display ISR's */

} DisplayMpLink_Statistics;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Display link real time parameters
 *
 *          Display link supports run time configuration of the output image
 *          resolution and the output window size. All the Below parameters
 *          need to be populated properly for any dynamic display resolution
 *          or window position update.
 *          Real time display update is not supported as of today
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                   overrideSrcSize;
    UInt32                   srcWidth;
    UInt32                   srcHeight;
    UInt32                   srcPitch[3U];
    System_VideoDataFormat   srcDataFormat;

    UInt32                   tarWidth;
    /**< Horizontal Size of the picture at output of video display
     *   Not used in case of Graphics instance */

    UInt32                   tarHeight;
    /**< vertical Size of picture at output of video display
     *   Not used in case of Graphics instance */

    UInt32                   posX;
    /**< X-Coordinate position of the frame in the output Video Window */

    UInt32                   posY;
    /**< Y-Coordinate position of the frame in the output Video Window */
} DisplayMpLink_RtParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Display link create time parameters
 *
 *          This structure is used to create and configure a Display link
 *          instance.
 *
 *******************************************************************************
*/
typedef struct
{
    System_LinkInQueParams   inQueParams;
    /**< Display link input queue information */
    UInt32                   displayId[DISPLAY_MP_LINK_MAX_PIPE];
    /**< Used to select the display driver to be used in this link instance.
     *   See DisplaySpLink_displayID for the supported values */
    UInt32                   displayScanFormat;
    /**< Display device scanformat type. Display link support both
     *   progressive and interlaced display devices
     *   See System_VideoScanFormat for the supported values */
    DisplayMpLink_RtParams   prms[DISPLAY_MP_LINK_MAX_PIPE];
    /**< Display link real time configuration parameters
     *   This needs to be configured at create time as well,
     *   IF not set, then assume tarWidth & tarHeight as input
     *   width & height and both posX & posY as 0 */
    UInt32                   numPipes;
    /**< Valid entries in prms/displayId arrays */
    System_LinkMemAllocInfo  memAllocInfo;
    /**< Memory alloc region info, used to pass user alloc memory address */
} DisplayMpLink_CreateParams;

/**
 *******************************************************************************
 *
 *   \brief Structure containing the Display link switch channel parameters
 *
 *          The display link can only take input for a single input queue.
 *          The single input queue can contain multiple channels, but only
 *          one of the channel can be shown at a time.
 *          Real time input channel switch is not supported as of today
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32                   activeChId;
    /**< Active chID from which frames should be displayed */
} DisplayMpLink_SwitchChannelParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/*******************************************************************************
 *                  Internal Function Declarations
 *******************************************************************************
 */
static inline Void DisplayMpLink_CreateParams_Init(
    DisplayMpLink_CreateParams *prm);

/**
 *******************************************************************************
 *
 *   \brief Display link register and init function
 *
 *          For each display instance (VID1, VID2, VID3 or GRPX1)
 *          - Creates link task
 *          - Registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DisplayMpLink_init(void);

/**
 *******************************************************************************
 *
 *   \brief Display link de-register and de-init function
 *
 *          For each display instance (VID1, VID2, VID3 or GRPX1)
 *          - Deletes link task
 *          - De-registers as a link with the system API
 *
 *   \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
*/
Int32 DisplayMpLink_deInit(void);

/**
 *******************************************************************************
 *
 *   \brief Function to initialize the Display Link Create Params
 *
 *          Sets default values for Display link create time parameters
 *          User/App can override these default values later.
 *
 *   \param prm [IN] Display Link create parameters
 *
 *   \return void
 *
 *******************************************************************************
*/
static inline Void DisplayMpLink_CreateParams_Init(DisplayMpLink_CreateParams *prm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(prm, 0, sizeof(DisplayMpLink_CreateParams));

    prm->displayId[0u] = DISPLAY_MP_LINK_INST_DSS_VID1;
    prm->displayScanFormat = SYSTEM_SF_PROGRESSIVE;
    prm->numPipes = 1U;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */

/* Nothing beyond this point */
