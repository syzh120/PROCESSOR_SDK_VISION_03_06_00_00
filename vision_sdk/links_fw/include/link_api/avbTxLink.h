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
 *   \defgroup AVB_TX_LINK_API AVB transmit Link API
 *
 *   \brief AVB Tx Link acts as IEEE 1722 listener and sends MJPEG/H264 video
 *   frames or metadata frames in AVB IEEE 1722 compliant format. In a typical
 *   ethernet surround view based system, AVB Talker is used to transmit encoded
 *   MJPEG/H264 frames to the AVB listener (like PC, AVB display etc.)
 *   A unique channel ID is assigned to each AVB talker.
 *
 *
 *   @{
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file avbTxLink.h
 *
 * \brief AVB transmit link API public header file.
 *
 * \version 0.0 (March 2017) : [PYJ] First version
 *
 *******************************************************************************
 */

#ifndef AVB_TX_LINK_H_
#define AVB_TX_LINK_H_

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
#define AVB_TX_LINK_MAX_TALKERS_DEFAULT (6U)
#define AVB_TX_LINK_MAX_IN_QUE          (1U)

/**
 *******************************************************************************
 *
 * \brief Indicates the length of the stream id in bytes
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define AVB_TX_LINK_STREAM_ID_LENGTH (8U)

/**
 *******************************************************************************
 *
 * \brief Indicates the length of the mac id in bytes
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define AVB_TX_LINK_MAC_ID_LENGTH (8U)

/**
 *******************************************************************************
 *
 * \brief Indicates the minimum number of buffers required per channel
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
#define AVB_TX_LINK_MAX_NUM_BUFS_PER_TALKER  (SYSTEM_LINK_MAX_FRAMES_PER_CH)


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
 * \brief AVBSrc link configuration parameters.
 *
 * SUPPORTED in ALL platforms
 *
 * NOTE:  StreamId for the different AVB talkers is made using src address
 *        and talker index combination.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32  numInQue;
    /**< Number of input queues  */

    System_LinkInQueParams              inQueParams[AVB_TX_LINK_MAX_IN_QUE];
    /**< Input queue information */

    UInt8                               dstMacId[AVB_TX_LINK_MAX_TALKERS_DEFAULT][AVB_TX_LINK_MAC_ID_LENGTH];
    /**< Destination MAC Address */

    UInt8                               srcMacId[AVB_TX_LINK_MAX_TALKERS_DEFAULT][AVB_TX_LINK_MAC_ID_LENGTH];
    /**< Source MAC Address - Same MAC should be present in the stream ID */

    UInt8                               streamId[AVB_TX_LINK_MAX_TALKERS_DEFAULT][AVB_TX_LINK_STREAM_ID_LENGTH];
    /**< Stream Id - SRC MAC should be present in the stream ID */

    UInt32                              avbTpSubType[AVB_TX_LINK_MAX_TALKERS_DEFAULT];
    /**< AVBTP codec type - used as subtype in AVBTP packet header */

    UInt32                              cvFormatSubType[AVB_TX_LINK_MAX_TALKERS_DEFAULT];
    /**< Compressed video format sub type: 0x0 -  MJPEG MJPEG Format 0x1 - H.264 Format */

} AvbTxLink_CreateParams;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void AvbTxLink_CreateParams_Init(AvbTxLink_CreateParams *pPrm);

 /**
 *******************************************************************************
 *
 * \brief Init function for AVB tx link. This function does the following for
 *   AVB tx link,
 *  - Creates a task for the link
 *  - Registers this link with the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AvbTxLink_init(void);

/**
 *******************************************************************************
 *
 * \brief De-init function for AVB Tx link. This function de-registers this link
 *  from the system
 *
 * \return  SYSTEM_LINK_STATUS_SOK
 *
 *******************************************************************************
 */
Int32 AvbTxLink_deInit(void);

/**
 *******************************************************************************
 *
 * \brief Set default parameters for AVB Tx Link create time params
 *   This function does the following
 *      - memset create params object
 * \param  pPrm  [OUT]  avbTxLink Create time Params
 *
 *******************************************************************************
 */
static inline void AvbTxLink_CreateParams_Init(AvbTxLink_CreateParams *pPrm)
{
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004 Rule 8.5
 * Function Definition in header file
 * KW State: Defer -> Waiver -> Case by case
 * MISRAC_WAIVER: This function initializes the create time argument to default.
 *  Defining this in the header file aids maintainability.
 */
    memset(pPrm, 0, sizeof(AvbTxLink_CreateParams));
    return;
}


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif


/*@}*/
