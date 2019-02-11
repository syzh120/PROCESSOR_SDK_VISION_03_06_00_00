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
 * \ingroup AVB_TX_LINK_API
 * \defgroup AVB_TX_LINK_IMPL AVB Transmit Link Implementation
 *
 * @{
 */


/**
 *******************************************************************************
 *
 * \file avbTxLink_priv.h
 *
 * \brief This file is a private header file for AvbTx link implementation.
 *
 *        This file lists the data structures, function prototypes which are
 *        implemented and used as a part of AvbTx link.
 *
 * \version 0.0 (Nov 2013) : [KRB] First version
 *
 *******************************************************************************
 */

#ifndef _AVB_TX_LINK_PRIV_H_
#define _AVB_TX_LINK_PRIV_H_

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
#define AVB_TX_LINK_OBJ_MAX         (1U)


/**
 *******************************************************************************
 *
 *   \brief Link local CMD: Releases displayed frames to previous link
 *
 *******************************************************************************
 */
#define AVB_TX_LINK_CMD_RELEASE_FRAMES                (0x5500U)

/**
 *******************************************************************************
 *
 *   \brief The MAX number of FVID2 frames to be allocated in the display link
 *
 *          This is set to max number of frames queued. Though display link
 *          can support multiple channels, only one channel is selected
 *          and active.
 *
 *   SUPPORTED in ALL platforms
 *
 *******************************************************************************
 */
#define AVB_TX_LINK_MAX_FRAMES_PER_HANDLE     (SYSTEM_LINK_MAX_FRAMES_PER_CH)


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
 *
 * \brief Forward declaration of AvbTx object.
 *
 *******************************************************************************
 */

typedef struct AvbTxLink_Obj_t AvbTxLink_Obj;

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
    UInt16 inQueId;
    /**< Input Que ID to which this channel belongs */

    avbtp_tx_buffer buffer;
    /**< AVBTx Buffer object */

    BuffState_e bufState;
    /**< Tx buffer state */

    System_Buffer *pSysBuffer;
    /**< System buffer this desc. is used to transmit */

} avbtp_tx_buff_desc;

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
    UInt32 avbChID;
    /**< AVBTx Talker channel ID */

    UInt16 inQueId;
    /**< Input Que ID to which this channel belongs */

    avbtp_talker_handle_t avbTalkerHandle;
    /**< AVBTx Handle */

    uint8_t streamId[AVB_TX_LINK_STREAM_ID_LENGTH];
    /**< AVBTx StreamId */

    uint8_t talkerMacAddr[AVB_TX_LINK_MAC_ID_LENGTH];
    /**< AVBTx Talker MAC Addr */

    avbtp_tx_buff_desc avbTxbuffDesc[AVB_TX_LINK_MAX_NUM_BUFS_PER_TALKER];
    /**< AVBTx Buffer Descriptor */

    UInt32 freeBufIdx;
    /**< Index of free AVB Tx buffer */

} AvbTxLink_avbTalkerObj;

/**
 *******************************************************************************
 * \brief Structure containing Link object information
 *
 * SUPPORTED in ALL platforms
 *
 *******************************************************************************
*/
struct AvbTxLink_Obj_t
{
    UInt32 tskId;
    /**< Link ID for this link */

    char name[32];
    /**< Link name */

    Utils_TskHndl tsk;
    /**< Handle to AvbTx link task */

    AvbTxLink_CreateParams createArgs;
    /**< Create params for AvbTx link */

    Utils_BufHndl bufQue;
    /**< Handle to buffer queue */

    avbtp_handle_t avbHandle;
    /**< Global AVB handle */

    AvbTxLink_avbTalkerObj avbTxTalkerInst[AVB_TX_LINK_MAX_IN_QUE][AVB_TX_LINK_MAX_TALKERS_DEFAULT];
    /**< Array of AvbTx link instance objects. Fields specific to instance */

    Utils_QueHandle systemBufferQueue[AVB_TX_LINK_MAX_IN_QUE];
    /**< Free system buffers queue for keeping system buffers returned
        from AVB Tx callback */
    System_Buffer *systemBufferQueueMem[AVB_TX_LINK_MAX_IN_QUE][AVB_TX_LINK_MAX_FRAMES_PER_HANDLE];
    /**< Free buffers Queue Mem */

    System_LinkInfo info;
    /**< AvbTx link information */

    UInt32 memUsed[UTILS_MEM_MAXHEAPS];
    /**< Memory used by AvbTx link */

    System_LinkQueInfo  inQueInfo[AVB_TX_LINK_MAX_IN_QUE];
    /**< Input Queue info */

    System_LinkStatistics   *linkStatsInfo;
    /**< Pointer to the Link statistics information,
         used to store below information
            1, min, max and average latency of the link
            2, min, max and average latency from source to this link
            3, links statistics like frames captured, dropped etc
        Pointer is assigned at the link create time from shared
        memory maintained by utils_link_stats layer */

    UInt32 recvCount;
    /**< Count of buffers received */

    Bool isFirstFrameRecv;
    /**< Flag to indicate if first frame is received, this is used as trigger
     *   to start stats counting
     */
    };

/******************************************************************************
 *  Functions
 *******************************************************************************
 */

extern AvbTxLink_Obj gAvbTxLink_obj[AVB_TX_LINK_OBJ_MAX];;


Int32 AvbTxLink_drvCreate(AvbTxLink_Obj * pObj,
                                    const AvbTxLink_CreateParams * pPrm);

Int32 AvbTxLink_drvStart(AvbTxLink_Obj * pObj);
Int32 AvbTxLink_drvStop(AvbTxLink_Obj * pObj);
Int32 AvbTxLink_drvDelete(AvbTxLink_Obj * pObj);
Int32 AvbTxLink_drvReleaseData(AvbTxLink_Obj * pObj);
Int32 AvbTxLink_drvProcessFrames(AvbTxLink_Obj * pObj);
Int32 AvbTxLink_drvPrintStatus(const AvbTxLink_Obj * pObj);
Int32 AvbTxLink_drvPutEmptyBuffers(AvbTxLink_Obj * pObj, System_BufferList * pBufList);
Int32 AvbTxLink_printBufferStatus(AvbTxLink_Obj * pObj);
Int32 AvbTxLink_getFullBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList);
Int32 AvbTxLink_putEmptyBuffers(Void * ptr, UInt16 queId, System_BufferList * pBufList);
Int32 AvbTxLink_getInfo(Void * ptr, System_LinkInfo * info);

#endif


/*@}*/
