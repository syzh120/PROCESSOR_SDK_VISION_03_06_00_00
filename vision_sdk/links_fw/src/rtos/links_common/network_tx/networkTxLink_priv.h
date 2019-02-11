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
 * \ingroup NETWORK_TX_LINK_API
 * \defgroup NETWORK_TX_LINK_IMPL NetworkTx Link Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file networkTxLink_priv.h NetworkTx Link private API/Data structures
 *
 * \brief  This file is a private header file for networkTx link implementation
 *         This file lists the data structures, function prototypes which are
 *         implemented and used as a part of networkTx link.
 *
 * \version 0.0 (Dec 2017) : [NN] First version
 *
 *******************************************************************************
 */

#ifndef NETWORK_TX_LINK_PRIV_H_
#define NETWORK_TX_LINK_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_0.h>
#include <include/link_api/networkTxLink.h>
#include <src/rtos/utils_common/include/network_api.h>
#include <src/rtos/utils_common/include/network_tfdtp_api.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Maximum number of networkTx link objects
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define NETWORK_TX_LINK_OBJ_MAX    (1U)

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 ******************************************************************************
 *
 * \brief Structure to hold all NetworkTx link related to network receive
 *
 ******************************************************************************
 */
typedef struct {

    Network_SockObj sockObj;
    /**< Information about network socket */

    UInt32 state;
    /**< State of server socket */

} NetworkTxLink_NetworkTxObj;

/**
 *******************************************************************************
 *
 * \brief Information about frames dump memory and its current state
 *
 *******************************************************************************
 */
typedef struct {

    UInt16 inQueId;
    /**< Input Que ID to which this channel belongs */

    UInt32 memAddr;
    /**< Base address to where frames should be copied */

    UInt32 memSize;
    /**< Size of memory segment */

    UInt32 curMemOffset;
    /**< Current offset in memory segment where frames should be copied */

    UInt32 numFrames;
    /**< Number of frames dumped to memory */

} NetworkTxLink_DumpFramesObj;

/**
 *******************************************************************************
 *
 * \brief Structure to hold all Dup link related information
 *
 *******************************************************************************
 */

typedef struct {
    UInt32 tskId;
    /**< Placeholder to store networkTx link task id */

    char name[32];
    /**< Link name */

    Utils_TskHndl tsk;
    /**< Handle to networkTx link task */

    NetworkTxLink_CreateParams createArgs;
    /**< Create params for networkTx link */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    Bool isFirstFrameRecv;
    /**< flag indicates if NetworkTx Link has received any buffers from previous link yet*/

    System_LinkQueInfo  inQueInfo[NETWORK_TX_LINK_MAX_IN_QUE];
    /**< Input Queue info */

    NetworkTxLink_DumpFramesObj dumpFramesObj[NETWORK_TX_LINK_MAX_IN_QUE][SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< Information about frames dump memory and its current state */

    Utils_DmaChObj  dumpFramesDmaObj;
    /**< DMA object to use when dumping frames to memory */

    UInt32 recvCount;
    /**< Count of buffers received */

    UInt8 *dataDumpPtr;
    /* Memory Ptr to dump bitstream data */

    UInt32 dataDumpSize;
    /* Size of the Memory dump for bitstream data */

    NetworkTxLink_NetworkTxObj netTxObj;
    /**< Information related to sending data over network */

} NetworkTxLink_Obj;

Int32 NetworkTxLink_printLinkStats(const NetworkTxLink_Obj * pObj);
Void NetworkTxLink_tskMain(struct Utils_TskHndl_t * pTsk, Utils_MsgHndl * pMsg);
Int32 NetworkTxLink_drvCreate(NetworkTxLink_Obj *pObj);
Int32 NetworkTxLink_drvDelete(NetworkTxLink_Obj *pObj);
Int32 NetworkTxLink_drvSendData(NetworkTxLink_Obj * pObj, UInt32 queId,
                                 UInt32 channelId,
                                 const System_Buffer *pBuffer);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
