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
 * \ingroup AVB_RX_LINK_API
 * \defgroup AVB_RX_LINK_IMPL AVB Recieve Link Implementation
 *
 * @{
 */


/**
 *******************************************************************************
 *
 * \file avbRxLink_priv.h
 *
 * \brief This file is a private header file for AvbRx link implementation.
 *
 *        This file lists the data structures, function prototypes which are
 *        implemented and used as a part of AvbRx link.
 *
 * \version 0.0 (Nov 2013) : [KRB] First version
 *
 *******************************************************************************
 */

#ifndef AVB_RX_LINK_PRIV_H_
#define AVB_RX_LINK_PRIV_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/links_ipu/system/system_priv_ipu1_1.h>
#include <ti/avbtp/inc/avbtp.h>

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
 * SUPPORTED in ALL platforms
 *
 ********************************************************************************
 */
#define AVB_RX_LINK_MAX_OUT_QUE         (1U)


/* @} */

/* Control Command's    */

/**
    \ingroup LINK_API_CMD
    \addtogroup AVB_SOURCE_LINK_API_CMD  Capture Link Control Commands

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
    struct app_buff_details avbBufDetails;
    /**<  */

    uint8_t  avbBufState[AVB_RX_LINK_NUM_BUFS_PER_TALKER_DEFAULT];
    /**<  */

    UInt32 avbBufValidLen[AVB_RX_LINK_NUM_BUFS_PER_TALKER_DEFAULT];
    /**< */

    uint8_t * avbBufPtr[AVB_RX_LINK_NUM_BUFS_PER_TALKER_DEFAULT];
    /**< */
} AvbRxLink_avbBuffDesc;

/**
 *******************************************************************************
 *
 * \brief Forward declaration of AvbRx object.
 *
 *******************************************************************************
 */

typedef struct AvbRxLink_Obj_t AvbRxLink_Obj;


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
    /**< AVBRx Talker channel ID */

    avbtp_listener_handle_t listenerHandle;
    /**< AVBRx Handle */

    uint8_t streamId[AVB_RX_LINK_STREAM_ID_LENGTH];
    /**< AVBRx StreamId */

    uint8_t talkerMacAddr[AVB_RX_LINK_MAC_ID_LENGTH];
    /**< AVBRx Talker MAC Addr */

    AvbRxLink_avbBuffDesc avbBuffDescriptor;
    /**< AVBRx Buffer Descriptor */

    System_Buffer buffers[AVB_RX_LINK_NUM_BUFS_PER_TALKER_DEFAULT];
    /**< System buffer data structure to exchange buffers between links */

    System_BitstreamBuffer bitstreamBuf[AVB_RX_LINK_NUM_BUFS_PER_TALKER_DEFAULT];
    /**< Payload for System buffers */

    UInt32 numBufs;
    /**< Number of buffers allocated for this instance */

    UInt32  bufferSize;
    /**< Width of the buffers allocated */

    UInt32 dataReadyIndex;
    /**< Index into the buffer descriptor that is ready to be consumed */

} AvbRxLink_ChObj;

/**
 *******************************************************************************
 * \brief Structure containing Link object information
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
struct AvbRxLink_Obj_t
{
    UInt32 tskId;
    /**< Link ID for this link */

    Utils_TskHndl tsk;
    /**< Handle to AvbRx link task */

    AvbRxLink_CreateParams createArgs;
    /**< Create params for AvbRx link */

    Utils_BufHndl bufQue;
    /**< Handle to buffer queue */

    avbtp_handle_t avbHandle;
    /**< Global AVB handle */

    AvbRxLink_ChObj avbSrcObj[AVB_RX_LINK_MAX_TALKERS_DEFAULT];
    /**< Array of AvbRx link instance objects. Fields specific to instance */

    System_LinkInfo info;
    /**< AvbRx link information */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Memory used by AvbRx link */

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

extern AvbRxLink_Obj gAvbRxLink_obj;


Int32 AvbRxLink_drvCreate(AvbRxLink_Obj * pObj,
                          const AvbRxLink_CreateParams * pPrm);

Int32 AvbRxLink_drvStart(AvbRxLink_Obj * pObj);
Int32 AvbRxLink_drvStop(AvbRxLink_Obj * pObj);
Int32 AvbRxLink_drvDelete(AvbRxLink_Obj * pObj);
Int32 AvbRxLink_drvPrintStatus(const AvbRxLink_Obj * pObj);
Int32 AvbRxLink_drvPutEmptyBuffers(AvbRxLink_Obj * pObj, System_BufferList * pBufList);
Int32 AvbRxLink_printBufferStatus(AvbRxLink_Obj * pObj);
Int32 AvbRxLink_getFullBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList);
Int32 AvbRxLink_putEmptyBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList);
Int32 AvbRxLink_getInfo(Void * ptr, System_LinkInfo * info);
#endif


/*@}*/
