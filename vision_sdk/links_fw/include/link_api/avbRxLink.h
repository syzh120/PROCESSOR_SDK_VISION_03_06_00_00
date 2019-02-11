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
 *   \defgroup AVB_RX_LINK_API AVB Receive Link API
 *
 *   \brief AVB Receive Link captures MJPEG video frames from AVB IEEE 1722
 *   compliant sources (talker). AVB Rx link supports capture of MJPEG frames
 *   from multiple AVB cameras connected over ethernet. In a typical ethernet
 *   surround view based system, these MJPEG frames are then decoded & used for
 *   analytics and stitching. A unique channel ID is assigned to each AVB camera.
 *
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file avbRxLink.h
 *
 * \brief AVB Receive link API public header file.
 *
 * \version 0.0 (Nov 2013) : [KRB] First version
 * \version 0.1 (feb 2014) : [CM] AVB Link up
 *
 *******************************************************************************
 */

#ifndef AVB_RX_LINK_H_
#define AVB_RX_LINK_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <include/link_api/system.h>
#include <include/link_api/systemLink_ipu1_0_params.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Max AVB talkers supported
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define AVB_RX_LINK_MAX_TALKERS_DEFAULT (5U)


/**
 *******************************************************************************
 *
 * \brief Indicates the length of the stream id in bytes
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define AVB_RX_LINK_STREAM_ID_LENGTH (8U)

/**
 *******************************************************************************
 *
 * \brief Indicates the length of the mac id in bytes
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define AVB_RX_LINK_MAC_ID_LENGTH (8U)

/**
 *******************************************************************************
 *
 * \brief Indicates the minimum number of buffers required per channel
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define AVB_RX_LINK_NUM_BUFS_PER_TALKER_DEFAULT (6U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *  \brief Enumerations for AVB Src notification types
 *
 *  SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
typedef enum
{
    AVB_RX_LINK_BUF_NOTIFY_MJPEG_FRAME = 0,
    /**< Enable AVB to invoke callback once a complete MJPEG frame is detected */

    AVB_RX_LINK_BUF_NOTIFY_FULL = 1U,
    /**< Enable AVB to invoke callback when a particular buffer has been filled up
     *  but not necessarily a complete MJPEG frame
     */

    AVB_RX_LINK_BUF_USE_NEW_BUFFER_FOR_MJPEG = 2U,
    /**< Inform AVB to use a new buffer after previously detecting an MJPEG frame
     * instead of filling up the current buffer.
     */

    AVB_RX_LINK_BUF_NOTIFY_ERROR = 3U,
     /**< Enable AVB to invoke callback when an error occurs */

    AVB_RX_LINK_FRAME_NOTIFICATION_TYPE_FORCE32BITS = 0x7FFFFFFF
     /**< This should be the last value after the max enumeration value.
      *   This is to make sure enum size defaults to 32 bits always regardless
      *   of compiler.
      */
} AvbRxLink_FrameNotifcationType;

/* @} */

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
*/

/**
 *******************************************************************************
 * \brief AVBSrc link configuration parameters.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    System_LinkOutQueParams             outQueParams;
    /**< output queue information */

    UInt8                               streamId[AVB_RX_LINK_MAX_TALKERS_DEFAULT][AVB_RX_LINK_STREAM_ID_LENGTH];
    /**< streamId for the different AVB cameras connected */

    UInt8                               srcMacId[AVB_RX_LINK_MAX_TALKERS_DEFAULT][AVB_RX_LINK_MAC_ID_LENGTH];
    /**< Source MAC Address - Same MAC should be present in the stream ID */

    UInt8                               dstMacId[AVB_RX_LINK_MAC_ID_LENGTH];
    /**< Destination MAC Address */

    AvbRxLink_FrameNotifcationType      bufferNotificationType;
    /**< frame notification type */

    UInt32                              numCameras;
    /**< number of AVB cameras connected */

    UInt32                              numBufs;
    /**< Number of buffers to be allocated for the AVB Rx link. Minimum
     *   number of buffers required is 3 for AVB Rx link to capture without
     *   frame drops
     */
    UInt32                              height;
    /**< Input source height,
     */

    UInt32                              width;
    /**< Input source width,
     */

    UInt32                              buffSize;
    /**< Maximum buffer size for AVB Rx */

} AvbRxLink_CreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AvbRxLink_CreateParams_Init(AvbRxLink_CreateParams *pPrm);

 /**
 *******************************************************************************
 *
 * \brief Init function for AVB Src link. This function does the following for
 *   AVB Src link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AvbRxLink_init(void);

/**
 *******************************************************************************
 *
 * \brief De-init function for AVB Rx link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AvbRxLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Set default parameters for AVB Rx Link create time params
 *   This function does the following
 *      - memset create params object
 *      - Sets bufferNotificationType as AVBRX_LINK_BUF_NOTIFY_MJPEG_FRAME
 *      - Sets numCameras as AVB_RX_LINK_MAX_TALKERS_DEFAULT
 *      - Sets numBufs as AVB_RX_LINK_NUM_BUFS_PER_TALKER_DEFAULT
 * \param  pPrm  [OUT]  avbRxLink Create time Params
 *
 *******************************************************************************
 */
static inline void AvbRxLink_CreateParams_Init(AvbRxLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AvbRxLink_CreateParams));
    pPrm->bufferNotificationType = AVB_RX_LINK_BUF_NOTIFY_MJPEG_FRAME;
    pPrm->numCameras = AVB_RX_LINK_MAX_TALKERS_DEFAULT;
    pPrm->numBufs = AVB_RX_LINK_NUM_BUFS_PER_TALKER_DEFAULT;
    return;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
