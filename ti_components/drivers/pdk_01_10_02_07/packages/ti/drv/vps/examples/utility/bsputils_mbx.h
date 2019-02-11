/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/**
 *  \ingroup BSPUTILS_API
 *  \defgroup BSPUTILS_MBX_API Message exchange API
 *
 *  APIs from this file are used to exchange messages between two tasks in the
 *  links and chains examples.
 *
 *  A message consists of a 32-bit command and optional 32-bit parameter value.
 *
 *  The 32-bit command is defined by the user.
 *
 *  The 32-bit parameter could inturn point to a bigger data structure as
 * defined
 *  by user.
 *
 *  The APIs allow a user to send a message and wait for ACK before proceeding
 *  further.
 *
 *  Internally message passing is implemented using queue's
 *
 *  @{
 */

/**
 *  \file bsputils_mbx.h
 *  \brief Message exchange API
 */

#ifndef BSPUTILS_MBX_H_
#define BSPUTILS_MBX_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/common/bsp_utilsQue.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/** \brief Maximum receive que length */
#define BSPUTILS_MBX_RECV_QUE_LEN_MAX ((UInt32) 1024U)

/** \brief Maximum acknowledgement que length */
#define BSPUTILS_MBX_ACK_QUE_LEN_MAX  ((UInt32) 2U)

/** \brief Message flag: wait for ACK when this flag is set */
#define BSPUTILS_MBX_FLAG_WAIT_ACK    ((UInt32) 0x01U)

/** \brief Get 32-bit command from message pointer */
#define BspUtils_msgGetCmd(pMsg)      ((pMsg)->cmd)

/** \brief Get 32-bit parameter pointer from message pointer */
#define BspUtils_msgGetPrm(pMsg)      ((pMsg)->pPrm)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/**
 * \brief Mailbox handle
 */
typedef struct
{
    BspUtils_QueHandle recvQue;
    /**< message receive queue  */
    BspUtils_QueHandle ackQue;
    /**< ack message receive queue  */
    Ptr                memRecvQue[BSPUTILS_MBX_RECV_QUE_LEN_MAX];
    /**< memory for receive queue */
    Ptr                memAckQue[BSPUTILS_MBX_ACK_QUE_LEN_MAX];
    /**< memory for ack queue */
} BspUtils_MbxHndl;

/**
 * \brief Message structure
 */
typedef struct
{
    BspUtils_MbxHndl *pFrom;
    /**< sender mailbox */
    Int32             result;
    /**< result to be sent as part of ACK */
    void             *pPrm;
    /**< parameters sent by sender  */
    UInt32            cmd;
    /**< command sent by sender */
    UInt32            flags;
    /**< message flags set by sender */
} BspUtils_MsgHndl;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief One-time system init for mailbox subsystem
 */
Int32 BspUtils_mbxInit(void);

/**
 * \brief Free's resources allocated during BspUtils_mbxInit()
 */
Int32 BspUtils_mbxDeInit(void);

/**
 * \brief Create's a message box and related resources
 *
 * \param pMbx      [OUT] Created handle
 *
 * \return FVID2_SOK on success else failure
 */
Int32 BspUtils_mbxCreate(BspUtils_MbxHndl *pMbx);

/**
 * \brief Free's resources allocated during BspUtils_mbxCreate()
 *
 * \param pMbx      [IN] Mail box handle
 *
 * \return FVID2_SOK on success else failure
 */
Int32 BspUtils_mbxDelete(BspUtils_MbxHndl *pMbx);

/**
 * \brief Send message from one mailbox to another mailbox
 *
 * When 'msgFlags' is BSPUTILS_MBX_FLAG_WAIT_ACK,
 *  the function waits until an ack is received
 *
 * When 'msgFlags' is 0,
 *  the function returns after message is sent to the receiver
 *
 * User can use 'pPrm' to pass a parameter pointer to the receiver.
 * Its upto user to manage the memory for this parameter pointer.
 *
 * 'cmd' can be any 32-bit value that is sent to the receiver
 *
 * When BSPUTILS_MBX_FLAG_WAIT_ACK is set,
 *  return value is the value sent via 'result' by the
 *  receiver when the receiver calls BspUtils_mbxAckOrFreeMsg()
 *
 * When BSPUTILS_MBX_FLAG_WAIT_ACK is not set,
 *  return value is message send status
 *
 * \param pFrom    [IN] Sender Mail box handle
 * \param pTo      [IN] Receiver mail box handle
 * \param cmd      [IN] 32-bit command
 * \param pPrm     [IN] 32-bit parameter pointer
 * \param msgFlags [IN] BSPUTILS_MBX_FLAG_xxxx
 *
 * \return FVID2_SOK on success else failure
 *
 */
Int32 BspUtils_mbxSendMsg(BspUtils_MbxHndl *pFrom,
                          BspUtils_MbxHndl *pTo,
                          UInt32            cmd,
                          void             *pPrm,
                          UInt32            msgFlags);

/**
 * \brief Send command to another mail box
 *
 * Same as BspUtils_mbxSendMsg() except,
 * - it can be called from interrupt context as well as task, SWI context
 * - ACK message cannot received
 *
 * \param pTo      [IN] Receiver mail box handle
 * \param cmd      [IN] Command to be sent
 *
 * \return FVID2_EFAIL in case message could not be sent
 */
Int32 BspUtils_mbxSendCmd(BspUtils_MbxHndl *pTo, UInt32 cmd);

/**
 * \brief Waits for a message to arrive
 *
 * When 'timeout' is BIOS_WAIT_FOREVER, it waits until atleast one message
 * arrives
 *
 * When 'timeout' is BIOS_NO_WAIT, it just checks for any available message.
 *  if no message is received then it return's with error
 *
 * User MUST call BspUtils_mbxAckOrFreeMsg() for every received message,
 * else message will not be free'ed and there will be memory leak.
 *
 * \param pMbxHndl  [IN] Receiver mail box
 * \param pMsg      [OUT] received message
 * \param timeout   [IN] BIOS_WAIT_FOREVER or BIOS_NO_WAIT
 *
 * \return FVID2_SOK on success else failure
 */
Int32 BspUtils_mbxRecvMsg(BspUtils_MbxHndl  *pMbxHndl,
                          BspUtils_MsgHndl **pMsg,
                          UInt32             timeout);

/**
 * \brief Acks or frees a message depending on flags set in the message
 *
 * if BSPUTILS_MBX_FLAG_WAIT_ACK is set,
 *  then an ack message is sent to the sender
 *
 * if BSPUTILS_MBX_FLAG_WAIT_ACK is not set,
 *  then it frees the memory associated with this message
 *
 * User MUST call this API for every message received using
 *  BspUtils_mbxRecvMsg() or BspUtils_mbxWaitCmd()
 * else message will not be free'ed and there will be memory leak.
 *
 * \param pMsg      [IN] Message to ACK'ed or free'ed
 * \param ackRetVal [IN] return code that is sent to the sender if an ack
 *                       message is sent to the sender
 *
 * \return FVID2_SOK on success else failure
 */
Int32 BspUtils_mbxAckOrFreeMsg(BspUtils_MsgHndl *pMsg, Int32 ackRetVal);

/**
 * \brief Waits until command of value 'cmdToWait' is received
 *
 * if 'pMsg' is NULL it frees the msg internally when it is received and returns
 *
 * if 'pMsg' is NOT NULL then it returns the received message to user. User
 *  needs to free the received message using BspUtils_mbxAckOrFreeMsg()
 *
 * \param pMbxHndl  [IN] Receiver mail box
 * \param pMsg      [OUT] received message
 * \param waitCmd   [IN] command to wait for
 *
 * \return FVID2_SOK on success else failure
 */
Int32 BspUtils_mbxWaitCmd(BspUtils_MbxHndl  *pMbxHndl,
                          BspUtils_MsgHndl **pMsg,
                          UInt32             waitCmd);

/**
 * \brief Returns the number of free messages in the mailbox.
 *
 * \return Number of free messages in the mailbox on success.
 */
UInt32 BspUtils_mbxGetFreeMsgCount(void);

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_MBX_H_ */

/* @} */
