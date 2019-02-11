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
 ******************************************************************************
 *
 * \ingroup NETWORK_RX_LINK_API
 * \defgroup NETWORK_RX_LINK_IMPL Network Rx Link Implementation
 *
 * @{
 */

/**
 ******************************************************************************
 *
 * \file networkRxLink_priv.h Network Rx Link private API/Data structures
 *
 * \brief  This file is a private header file for network rx link
 * implementation. It lists the data structures, function prototypes which are
 * implemented and used as a part of network rx link.
 *
 * \version 0.0 (Dec 2013) : [VT] First version
 *
 ******************************************************************************
 */

#ifndef NETWORK_RX_LINK_PRIV_H_
#define NETWORK_RX_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/******************************************************************************
 *  Include files
 ******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/networkRxLink.h>
#include <src/rtos/utils_common/include/network_api.h>
#include <src/rtos/utils_common/include/network_tfdtp_api.h>

/******************************************************************************
 *  Defines
 ******************************************************************************
 */

/**
 ******************************************************************************
 *
 * \brief Maximum number of output buffers in network rx link
 *
 * SUPPORTED in ALL platforms
 *
 ******************************************************************************
 */
#define NETWORK_RX_LINK_MAX_OUT_BUFFERS   (NETWORK_RX_LINK_MAX_OUT_BUFS_PER_CH \
                                            * NETWORK_RX_LINK_MAX_CH)

/******************************************************************************
 *  Data structure's
 ******************************************************************************
 */

/**
 ******************************************************************************
 *
 * \brief Structure to hold all Network Rx link related to network receive
 *
 ******************************************************************************
 */
typedef struct {

    Network_SockObj sockObj;
    /**< Information about network socket */

    UInt32 state;
    /**< State of server socket */

} NetworkRxLink_NetworkRxObj;

/**
 ******************************************************************************
 *
 * \brief Structure to hold all Network Rx link related information
 *
 ******************************************************************************
 */

typedef struct {
    UInt32 tskId;
    /**< Placeholder to store network rx link source task id */

    char name[32];
    /**< Link name */

    Utils_TskHndl tsk;
    /**< Handle to network rx link task */

    NetworkRxLink_CreateParams createArgs;
    /**< Create params for network rx link */

    Utils_QueHandle fullOutBufQue;
    /**< Network Rx link output side full buffer queue */

    System_Buffer *pBufferOnFullQ[NETWORK_RX_LINK_MAX_OUT_BUFFERS];
    /** Holds full buffers */

    Utils_QueHandle emptyOutBufQue[NETWORK_RX_LINK_MAX_CH];
    /**< Network Rx link output side empty buffer queue */

    System_Buffer *pBufferOnEmptyQ[NETWORK_RX_LINK_MAX_CH]
                                  [NETWORK_RX_LINK_MAX_OUT_BUFS_PER_CH];
   /** Holds individual channel empty buffers */

    System_Buffer buffers[NETWORK_RX_LINK_MAX_CH]
                         [NETWORK_RX_LINK_MAX_OUT_BUFS_PER_CH];
    /**< System buffer data structure to exchange buffers between links */

    System_VideoFrameBuffer videoFrames[NETWORK_RX_LINK_MAX_CH]
                                       [NETWORK_RX_LINK_MAX_OUT_BUFS_PER_CH];
    /**< Payload for System buffers in case of YUV data*/

    System_BitstreamBuffer bitstreamBuf[NETWORK_RX_LINK_MAX_CH]
                                       [NETWORK_RX_LINK_MAX_OUT_BUFS_PER_CH];
    /*< Payload for System buffers in case of compressed data*/

    System_MetaDataBuffer metaDataBuf[NETWORK_RX_LINK_MAX_CH]
                                       [NETWORK_RX_LINK_MAX_OUT_BUFS_PER_CH];
    /*< Payload for System buffers in case of meta data*/

    BspOsal_ClockHandle timer;
    /**<Timer used to generate new data at a set interval*/

    System_LinkInfo linkInfo;
    /* Network Rx link info that is returned when queried by next link */

    Int32 fpDataStream[NETWORK_RX_LINK_MAX_CH];
    /**< Binary File containing the stream data.*/

    Int32 fpIndexFile[NETWORK_RX_LINK_MAX_CH];
    /**< File used to index into fpDataStream.
    * It will contain frame sizes in bytes.
    */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool isFirstBufferSent;
    /**< flag indicates if Network Rx Link has sent any buffers to next link yet*/

    UInt32 numPendingCmds;
    /**< Number of pending NEW_DATA_CMD that are yet to handled */

    NetworkRxLink_NetworkRxObj netRxObj;
    /**< Information related to receiving data over network */

    UInt32 curFrameId;
    /**< Current frame being parsed from file */

    UInt32 *frameSizes;
    /**< Used when frames are read from file */

    UInt32 numFrames;
    /**< Used when frames are read from file */

} NetworkRxLink_Obj;


Void NetworkRxLink_tskMain(struct Utils_TskHndl_t *pTsk, Utils_MsgHndl *pMsg);
Int32 NetworkRxLink_drvCreate(NetworkRxLink_Obj *pObj);
Int32 NetworkRxLink_drvDelete(NetworkRxLink_Obj *pObj);
Int32 NetworkRxLink_drvFillData(NetworkRxLink_Obj * pObj, UInt32 channelId,
                                    const System_Buffer *pBuffer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/*@}*/
