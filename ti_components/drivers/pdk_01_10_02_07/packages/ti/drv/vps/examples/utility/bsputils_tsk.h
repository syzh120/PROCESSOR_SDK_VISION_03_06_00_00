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
 *  \defgroup BSPUTILS_TSK_API Task wrapper APIs
 *
 *  APIs in this file couple a BIOS Task with a mailbox in order to allow
 *  application to implement a state machine kind of logic, where in state
 *  change happens based on received message's
 *
 *  @{
 */

/**
 *  \file bsputils_tsk.h
 *  \brief Task wrapper API
 */

#ifndef BSPUTILS_TSK_H_
#define BSPUTILS_TSK_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/drv/vps/include/osal/bsp_osal.h>
#include <ti/drv/vps/examples/utility/bsputils_mbx.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#ifndef xdc_target_types__
#ifndef UArg
/** \brief Typedef for Argument of type unsigned int */
typedef unsigned int UArg;
#endif
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

struct BspUtils_TskHndl_t;

/**
 *  \brief Task main function
 *
 *  This function is called when a message is received by the
 *  task.
 *
 *  \param pHndl [OUT] Task handle
 *  \param pMsg  [OUT] Received message
 */
typedef void (*BspUtils_TskFuncMain)(struct BspUtils_TskHndl_t *pHndl,
                                     BspUtils_MsgHndl          *pMsg);

/**
 *  \brief Task handle.
 */
typedef struct BspUtils_TskHndl_t
{
    BspOsal_TaskHandle   tsk;
    /**< BIOS Task handle. */
    BspUtils_MbxHndl     mbx;
    /**< Mail box associated with this task. */

    UInt8               *stackAddr;
    /**< Task stack address. */
    UInt32               stackSize;
    /**< Task stack size. */

    UInt32               tskPri;
    /**< Task priority as defined by BIOS. */
    BspUtils_TskFuncMain funcMain;
    /**< Task main.
     *  Note, this is different from BIOS Task, since this function
     *  is entered ONLY when a message is received. */
    Ptr                  appData;
    /**< Application specific data. */
    UInt32               tskAffinity;
    /**< Used only in SMP mode, otherwise ignored.
      *  By setting tskAffinity, user can bind the task with any one of
      *  the cores in SMP mode */
} BspUtils_TskHndl;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 *  \brief Create a task
 *
 *  \param pHndl        [OUT] Task handle
 *  \param funcMain     [IN]  Task main,
 *                            Note, this is different from BIOS Task, since
 *                            this function
 *                            is entered ONLY when a message is received.
 *  \param tskPri       [IN]  Task priority as defined by BIOS
 *  \param stackAddr    [IN]  Task stack address
 *  \param stackSize    [IN]  Task stack size
 *  \param appData      [IN]  Application specific data
 *  \param tskName      [IN]  Task name
 *
 *  \return FVID2_SOK on success else failure
 */
Int32 BspUtils_tskCreate(BspUtils_TskHndl    *pHndl,
                         BspUtils_TskFuncMain funcMain,
                         UInt32               tskPri,
                         UInt8               *stackAddr,
                         UInt32               stackSize,
                         Ptr                  appData,
                         char                 *tskName);

/**
 *  \brief Delete a task
 *
 *  \param pHndl        [OUT] Task handle
 *
 *  \return FVID2_SOK on success else failure
 */
Int32 BspUtils_tskDelete(BspUtils_TskHndl *pHndl);

/**
 *  \brief Send message from one task to another task
 *
 *  Refer to BspUtils_mbxSendMsg() for details
 */
static inline Int32 BspUtils_tskSendMsg(BspUtils_TskHndl *pFrom,
                                        BspUtils_TskHndl *pTo,
                                        UInt32            cmd,
                                        void             *pPrm,
                                        UInt32            msgFlags);

/**
 *  \brief Send 32-bit command to another task
 *
 *  Refer to BspUtils_mbxSendCmd() for details
 */
static inline Int32 BspUtils_tskSendCmd(BspUtils_TskHndl *pTo,
                                        UInt32            cmd);

/**
 *  \brief Wait for a message to arrive
 *
 *  Refer to BspUtils_mbxRecvMsg() for details
 */
static inline Int32 BspUtils_tskRecvMsg(BspUtils_TskHndl  *pHndl,
                                        BspUtils_MsgHndl **pMsg,
                                        UInt32             timeout);

/**
 *  \brief ACK or free received message
 *
 *  Refer to BspUtils_mbxAckOrFreeMsg() for details
 */
static inline Int32 BspUtils_tskAckOrFreeMsg(BspUtils_MsgHndl *pMsg,
                                             Int32             result);

/**
 *  \brief Wait until user specified command is received
 *
 *  Refer to BspUtils_mbxWaitCmd() for details
 */
static inline Int32 BspUtils_tskWaitCmd(BspUtils_TskHndl  *pHndl,
                                        BspUtils_MsgHndl **pMsg,
                                        UInt32             cmdToWait);

/* ========================================================================== */
/*                          Static Function Definition                        */
/* ========================================================================== */

static inline Int32 BspUtils_tskSendMsg(BspUtils_TskHndl *pFrom,
                                        BspUtils_TskHndl *pTo,
                                        UInt32            cmd,
                                        void             *pPrm,
                                        UInt32            msgFlags)
{
    return BspUtils_mbxSendMsg(&pFrom->mbx, &pTo->mbx, cmd, pPrm, msgFlags);
}

static inline Int32 BspUtils_tskSendCmd(BspUtils_TskHndl *pTo,
                                        UInt32            cmd)
{
    return BspUtils_mbxSendCmd(&pTo->mbx, cmd);
}

static inline Int32 BspUtils_tskRecvMsg(BspUtils_TskHndl  *pHndl,
                                        BspUtils_MsgHndl **pMsg,
                                        UInt32             timeout)
{
    return BspUtils_mbxRecvMsg(&pHndl->mbx, pMsg, timeout);
}

static inline Int32 BspUtils_tskAckOrFreeMsg(BspUtils_MsgHndl *pMsg,
                                             Int32             result)
{
    return BspUtils_mbxAckOrFreeMsg(pMsg, result);
}

static inline Int32 BspUtils_tskWaitCmd(BspUtils_TskHndl  *pHndl,
                                        BspUtils_MsgHndl **pMsg,
                                        UInt32             cmdToWait)
{
    return BspUtils_mbxWaitCmd(&pHndl->mbx, pMsg, cmdToWait);
}

#ifdef __cplusplus
}
#endif

#endif  /* #define BSPUTILS_TSK_H_ */

/* @} */
