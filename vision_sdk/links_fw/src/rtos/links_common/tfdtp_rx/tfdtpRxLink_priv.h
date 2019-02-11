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
 ********************************************************************************
 *
 * \ingroup TFDTP_RX_LINK_API
 * \defgroup TFDTP_RX_LINK_IMPL TFDTP Receive Link Implementation
 *
 * @{
 */


/**
 *******************************************************************************
 *
 * \file tfdtpRxLink_priv.h
 *
 * \brief This file is a private header file for TfdtpRx link implementation.
 *
 *        This file lists the data structures, function prototypes which are
 *        implemented and used as a part of TfdtpRx link.
 *
 * \version 0.0 (Nov 2016) : [PYJ] First version
 *
 *******************************************************************************
 */

#ifndef TFDTP_RX_LINK_PRIV_H
#define TFDTP_RX_LINK_PRIV_H

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_1.h>
#include <src/rtos/utils_common/include/network_tfdtp_api.h>
#include <ti/nsp/drv/inc/tfdtp.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 ********************************************************************************
 *
 * \brief Maximum number of output queues that capture link supports.
 *
 ********************************************************************************
 */
#define TFDTP_RX_LINK_MAX_OUT_QUE         (1U)

/**
 ********************************************************************************
 *
 * \brief Maximum number of TFDTP channels
 *
 ********************************************************************************
 */
#define TFDTP_SRC_LINK_MAX_CH             (1U)


/* @} */

/* Control Command's    */

/**
    \ingroup LINK_API_CMD
    \addtogroup TFDTP_SOURCE_LINK_API_CMD  TFDTP Rx Link Control Commands

    @{
*/


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
 * \brief configuration for VIP instnace.
 *
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
typedef struct
{
    struct tfdtp_rx_buf_details tfdtpBufDetails;
    /**<  */

    uint8_t  tfdtpBufState[TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT];
    /**<  */

    UInt32 tfdtpBufValidLen[TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT];
    /**< */

} TfdtpRxLink_tfdtpBuffDesc;

/**
 *******************************************************************************
 *
 * \brief Forward declaration of TfdtpRx object.
 *
 *******************************************************************************
 */

typedef struct TfdtpRxLink_Obj_t TfdtpRxLink_Obj;


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
    UInt32 chID;
    /**< TFDTPRx channel ID */

    tfdtp_rx_channel_handle_t rxChannelHandle;
    /**< TFDTPRx Handle */

    TfdtpRxLink_tfdtpBuffDesc tfdtpBuffDescriptor;
    /**< TFDTPRx Buffer Descriptor */

    System_Buffer buffers[TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT];
    /**< System buffer data structure to exchange buffers between links */

    System_VideoFrameBuffer videoFrames[TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT];
    /**< Payload for System buffers in case of YUV data*/

    System_BitstreamBuffer bitstreamBuf[TFDTP_RX_LINK_NUM_BUFS_PER_CHANNEL_DEFAULT];
    /*< Payload for System buffers in case of compressed data*/

    UInt32 numBufs;
    /**< Number of buffers allocated for this instance */

    UInt32  bufferSize;
    /**< Width of the buffers allocated */

    UInt32 dataReadyIndex;
    /**< Index into the buffer descriptor that is ready to be consumed */

} TfdtpRxLink_ChObj;

/**
 *******************************************************************************
 * \brief Structure containing Link object information
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
struct TfdtpRxLink_Obj_t
{
    UInt32 tskId;
    /**< Link ID for this link */

    Utils_TskHndl tsk;
    /**< Handle to TfdtpRx link task */

    TfdtpRxLink_CreateParams createArgs;
    /**< Create params for TfdtpRx link */

    Utils_BufHndl bufQue;
    /**< Handle to buffer queue */

    tfdtp_handle_t tfdtpHandle;
    /**< Global TFDTP handle */

    TfdtpRxLink_ChObj tfdtpSrcObj[TFDTP_RX_LINK_MAX_CHANNELS_DEFAULT];
    /**< Array of TfdtpRx link instance objects. Fields specific to instance */

    System_LinkInfo linkInfo;
    /**< TfdtpRx link information */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Memory used by TfdtpRx link */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */
};

/******************************************************************************
 *  Functions
 *******************************************************************************
 */

extern TfdtpRxLink_Obj gTfdtpRxLink_obj;

Int32 TfdtpRxLink_drvCreate(TfdtpRxLink_Obj * pObj,
                             const TfdtpRxLink_CreateParams * pPrm);

Int32 TfdtpRxLink_drvStart(TfdtpRxLink_Obj * pObj);
Int32 TfdtpRxLink_drvStop(TfdtpRxLink_Obj * pObj);
Int32 TfdtpRxLink_drvDelete(TfdtpRxLink_Obj * pObj);
Int32 TfdtpRxLink_drvPrintStatus(TfdtpRxLink_Obj * pObj);
Int32 TfdtpRxLink_drvPutEmptyBuffers(TfdtpRxLink_Obj * pObj, System_BufferList * pBufList);
Int32 TfdtpRxLink_printBufferStatus(TfdtpRxLink_Obj * pObj);
Int32 TfdtpRxLink_getFullBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList);
Int32 TfdtpRxLink_putEmptyBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList);
Int32 TfdtpRxLink_getInfo(Void * ptr, System_LinkInfo * info);
#endif


/*@}*/
