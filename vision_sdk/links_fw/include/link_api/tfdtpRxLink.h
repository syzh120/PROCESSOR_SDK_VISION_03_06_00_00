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
 *   \defgroup TFDTP_RX_LINK_API TFDTP Receive Link API
 *
 *   \brief TFDTP Receive Link receives data from TFDTP client. A unique channel
 *          ID is assigned to each TFDTP channel.
 *
 *   IMPORTANT NOTE: This is experimental link to test TFDTP RX. Users are
 *   advised to use TFDTP Rx link with NSP_TFDTP_INCLUDE enabled in order to
 *   receive data via TFDTP.
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file tfdtpRxLink.h
 *
 * \brief TFDTP Receive link API public header file.
 *
 * \version 0.0 (Nov 2016) : [PYJ] First version
 *
 *******************************************************************************
 */

#ifndef TFDTP_RX_LINK_H_
#define TFDTP_RX_LINK_H_

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
 * \brief Max TFDTP channels supported
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define TFDTP_RX_LINK_MAX_CHANNELS_DEFAULT (1U)


/**
 *******************************************************************************
 *
 * \brief Indicates the length of the mac id in bytes
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define TFDTP_RX_LINK_MAC_ID_LENGTH (8U)

/**
 *******************************************************************************
 *
 * \brief Indicates the minimum number of buffers required per channel
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT (5U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *  \brief Enumerations for TFDTP Src notification types
 *
 *  SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
typedef enum
{
    TFDTP_RX_LINK_BUF_NOTIFY_FRAME = 0,
    /**< Enable TFDTP to invoke callback once a complete frame is detected */

    TFDTP_RX_LINK_BUF_NOTIFY_FULL = 1,
    /**< Enable TFDTP to invoke callback when a particular buffer has been filled up
     *  but not necessarily a complete frame
     */

    TFDTP_RX_LINK_BUF_USE_NEW_BUFFER = 2,
    /**< Inform TFDTP to use a new buffer after previously detecting an frame
     * instead of filling up the current buffer.
     */

    TFDTP_RX_LINK_BUF_NOTIFY_ERROR = 3,
     /**< Enable TFDTP to invoke callback when an error occurs */

    TFDTP_RX_LINK_FRAME_NOTIFICATION_TYPE_FORCE32BITS = 0x7FFFFFFF
     /**< This should be the last value after the max enumeration value.
      *   This is to make sure enum size defaults to 32 bits always regardless
      *   of compiler.
      */
} TfdtpRxLink_FrameNotifcationType;

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

    System_LinkQueInfo                  outQueInfo;
    /**< Output queue information : This contains channel info which further
      *  details the buffer format and resolutions
      */

    TfdtpRxLink_FrameNotifcationType    bufferNotificationType;
    /**< frame notification type */

    UInt8                               txHostIpAddr[TFDTP_RX_LINK_MAX_CHANNELS_DEFAULT];
    /**< Host IP address for the different TFDTP channels connected */

    UInt8                               txHostMacAddr[TFDTP_RX_LINK_MAX_CHANNELS_DEFAULT][TFDTP_RX_LINK_MAC_ID_LENGTH];
    /**< Host MAC Address - Same MAC should be present */

    UInt32                              numChannels;
    /**< number of TFDTP channels connected */

    UInt32                              numBufs;
    /**< Number of buffers to be allocated for the TFDTP Rx link. Minimum
     *   number of buffers required is 3 for TFDTP Rx link to capture without
     *   frame drops
     */

    System_VideoDataFormat              videoDataFormat;
    /**< Input source data format (Supported format - YUV420 & YUV422
     */
} TfdtpRxLink_CreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void TfdtpRxLink_CreateParams_Init(TfdtpRxLink_CreateParams *pPrm);

 /**
 *******************************************************************************
 *
 * \brief Init function for TFDTP Src link. This function does the following for
 *   TFDTP Src link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 TfdtpRxLink_init(void);

/**
 *******************************************************************************
 *
 * \brief De-init function for TFDTP Rx link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 TfdtpRxLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Set default parameters for TFDTP Rx Link create time params
 *   This function does the following
 *      - memset create params object
 *      - Sets bufferNotificationType as AVBRX_LINK_BUF_NOTIFY_MJPEG_FRAME
 *      - Sets numChannels as TFDTP_RX_LINK_MAX_CHANNELS_DEFAULT
 *      - Sets numBufs as TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT
 * \param  pPrm  [OUT]  tfdtpRxLink Create time Params
 *
 *******************************************************************************
 */
static inline void TfdtpRxLink_CreateParams_Init(TfdtpRxLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(TfdtpRxLink_CreateParams));
    pPrm->bufferNotificationType = TFDTP_RX_LINK_BUF_NOTIFY_FRAME;
    pPrm->numChannels = TFDTP_RX_LINK_MAX_CHANNELS_DEFAULT;
    pPrm->numBufs = TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT;
    return;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
