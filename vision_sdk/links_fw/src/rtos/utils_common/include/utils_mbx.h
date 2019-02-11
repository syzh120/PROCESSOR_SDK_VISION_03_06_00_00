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
 * \ingroup UTILS_API
 * \defgroup UTILS_MBX_API Message exchange API
 *
 * \brief  APIs from this file are used to exchange messages between two
 *         tasks in the links and chains examples.
 *
 *         A message consists of a 32-bit command and optional 32-bit parameter
 *         value.
 *
 *         The 32-bit command is defined by the user.
 *
 *         The 32-bit parameter could inturn point to a bigger data structure
 *         as defined by user.
 *
 *         The APIs allow a user to send a message and wait for ACK before
 *         proceeding further.
 *
 *         Internally message passing is implemented using queue's
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_mbx.h
 *
 * \brief Message exchange API
 *
 * \version 0.0 First version
 * \version 0.1 Updates as per code review comments
 *
 *******************************************************************************
 */

#ifndef UTILS_MBX_H_
#define UTILS_MBX_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_que.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* @{ */

/**
 *******************************************************************************
 * \brief Maximum receive que length
 *******************************************************************************
*/
#define UTILS_MBX_RECV_QUE_LEN_MAX (1024U)

/**
 *******************************************************************************
 * \brief Maximum acknowledgement que length
 *******************************************************************************
*/
#define UTILS_MBX_ACK_QUE_LEN_MAX  (2U)

/**
 *******************************************************************************
 * \brief Message flag: wait for ACK when this flag is set
 *******************************************************************************
*/
#define UTILS_MBX_FLAG_WAIT_ACK    (1U)

/**
 *******************************************************************************
 * \brief Maximum number of ack queues.This allows multiple tasks to wait
 *        on different ack msgs
 *******************************************************************************
*/
#define UTILS_MBX_ACK_QUE_CNT_MAX  (4U)

/**
 *******************************************************************************
 * \brief Get 32-bit command from message pointer
 *******************************************************************************
*/
#define Utils_msgGetCmd(pMsg)      ((pMsg)->cmd)

/**
 *******************************************************************************
 * \brief Get 32-bit parameter pointer from message pointer
 *******************************************************************************
*/
#define Utils_msgGetPrm(pMsg)      ((pMsg)->pPrm)

/* @} */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Mailbox handle
 *
 *******************************************************************************
*/
typedef struct {
    Utils_QueHandle recvQue;
  /**< message receive queue  */

    Utils_QueHandle ackQue[UTILS_MBX_ACK_QUE_CNT_MAX];
  /**< ack message receive queue  */

    Bool ackQueInUse[UTILS_MBX_ACK_QUE_CNT_MAX];
  /**< flag indicating whether this que is expecting ack */

    Ptr memRecvQue[UTILS_MBX_RECV_QUE_LEN_MAX];
  /**< memory for receive queue */

    Ptr memAckQue[UTILS_MBX_ACK_QUE_CNT_MAX][UTILS_MBX_ACK_QUE_LEN_MAX];
  /**< memory for ack queue */

    Void *pTsk;
    /**< Handle to tsk handle
     *   MUST be VALID, if pFuncMultiMbxTrigger is NOT NULL
     */

    Int32 (*pFuncMultiMbxTrigger)(Void *pTsk,
                                Int32 timeout);
    /**< Function to invoke to trigger the multi-mbx task
     *   If set to NULL, this feature is not used
     */

} Utils_MbxHndl;

/**
 *******************************************************************************
 *
 *  \brief  Message structure
 *
 *******************************************************************************
*/
typedef struct {
    Utils_MbxHndl *pFrom;
  /**< sender mailbox */

    Int32 result;
  /**< result to be sent as part of ACK */

    Void *pPrm;
  /**< parameters sent by sender  */

    UInt32 cmd;
  /**< command sent by sender */

    UInt32 flags;
  /**< message flags set by sender */

    Utils_QueHandle *ackQue;
  /**< ack queue to which msg will be acknowledged */

} Utils_MsgHndl;

/**
 *******************************************************************************
 * \brief Utils_mbxCreate create parameters
 *******************************************************************************
 */
typedef struct {

    Void *pTsk;
    /**< Handle to tsk handle
     *   MUST be VALID, if pFuncMultiMbxTrigger is NOT NULL
     */

    Int32 (*pFuncMultiMbxTrigger)(Void *pTsk, Int32 timeout);
    /**< Function to invoke to trigger the multi-mbx task
     *   If set to NULL, this feature is not used
     */

} Utils_MbxCreatePrm;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static inline void Utils_MbxCreatePrm_Init(Utils_MbxCreatePrm *pPrm);
static inline void Utils_MbxCreatePrm_Init(Utils_MbxCreatePrm *pPrm)
{
    memset((void *)pPrm, 0, sizeof(Utils_MbxCreatePrm));
}

Int32 Utils_mbxInit(void);

Int32 Utils_mbxDeInit(void);

Int32 Utils_mbxCreate(Utils_MbxHndl * pMbx, const Utils_MbxCreatePrm *pPrm);

Int32 Utils_mbxDelete(Utils_MbxHndl * pMbx);

Int32 Utils_mbxSendMsg(Utils_MbxHndl * pFrom,
                       Utils_MbxHndl * pTo,
                       UInt32 cmd,
                       Void * pPrm,
                       UInt32 msgFlags);

Int32 Utils_mbxSendCmd(Utils_MbxHndl * pTo, UInt32 cmd, Void *payload);

Int32 Utils_mbxRecvMsg(Utils_MbxHndl * pMbxHndl,
                       Utils_MsgHndl ** pMsg,
                       UInt32 timeout);

Int32 Utils_mbxPeekMsg(const Utils_MbxHndl * pMbxHndl, Utils_MsgHndl ** pMsg);

Int32 Utils_mbxAckOrFreeMsg(Utils_MsgHndl * pMsg, Int32 ackRetVal);

Int32 Utils_mbxWaitCmd(Utils_MbxHndl * pMbxHndl,
                       Utils_MsgHndl ** pMsg,
                       UInt32 waitCmd);

UInt32 Utils_mbxGetFreeMsgCount(void);

#endif

/* @} */
