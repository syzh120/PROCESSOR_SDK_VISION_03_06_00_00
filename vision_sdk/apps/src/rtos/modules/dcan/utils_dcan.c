/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 * \file utils_dcan.c
 *
 * \brief  This file implements the DCAN TX/RX functionality
 *
 *
 *
 * \version 0.0 (Dec 2014) : First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/knl/Event.h>
#include <ti/sysbios/gates/GateMutexPri.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>

#include <ti/csl/csl_types.h>
#include <ti/drv/vps/include/common/bsp_utils.h>
#include <ti/csl/hw_types.h>
#include <ti/drv/stw_lld/platform/irq_xbar_interrupt_ids.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>

#include "include/link_api/system.h"
#include "include/link_api/system_common.h"

/* Application header files */
#include "src/rtos/utils_common/include/utils.h"
#include "src/rtos/utils_common/include/utils_que.h"
#include "src/rtos/utils_common/include/utils_tsk.h"
#include "utils_dcan.h"




/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/** \brief DCAN bit time calculation maximum error value. */
#define UTILS_DCAN_CALC_MAX_ERROR         (50U)

/** \brief Macro used to extract bit rate prescaler value. */
#define UTILS_DCAN_EXTRACT_BRPE_VAL       (0x3C0U)

/** \brief Shift value used for bit rate prescaler. */
#define UTILS_DCAN_BRPE_SHIFT             (6U)

/** \brief DCAN instance used */
#define UTILS_DCAN_INST                   (SOC_DCAN1_BASE)

/** \brief DCAN TX message object used */
#define UTILS_DCAN_TX_MSG_OBJ                 (0x1U)
/** \brief DCAN RX message object used */
#define UTILS_DCAN_RX_MSG_OBJ                 (0x2U)
/** \brief DCAN TX message object used */
#define UTILS_DCAN_TX_ACK_MSG_OBJ             (0x3U)
/** \brief DCAN RX message object used */
#define UTILS_DCAN_RX_ACK_MSG_OBJ             (0x4U)

#define UTILS_DCAN_CTRL_MSG_ID                (0xC1)
#define UTILS_DCAN_CTRL_ACK_MSG_ID            (0xC2)

/** \brief DCAN TX interface register used */
#define UTILS_DCAN_TX_IF_REG              (DCAN_IF_REG_NUM_1)
/** \brief DCAN RX interface register used */
#define UTILS_DCAN_RX_IF_REG              (DCAN_IF_REG_NUM_2)

/** \brief Offset of DRM SUSPEND_CTRL1 register */
#define DRM_SUSPEND_CTRL1               (0x204)
/** \brief DRM_SUSPEND_CTRL1 is mapped to DCAN1 Suspend Output line */
#define DRM_SUSPEND_CTRL_DCAN1          (SOC_I_DRM_BASE + DRM_SUSPEND_CTRL1)

/** \brief DRM SUSPEND Source as M4 */
#define DRM_SUSPEND_SRC_IPU1_C0         (0x3)


#define UTILS_DCAN_MAX_QUEUE_PER_MBX    (0x2U)


#define UTILS_DCAN_TSK_EXIT_EVENT       (Event_Id_31)
#define UTILS_DCAN_TX_PRD_EVENT         (Event_Id_00)




/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 *  \brief    Enumerates the values used to represent the DCAN bit time
 *            calculation error values.
 */
typedef enum dcanBitTimeCalcErrType
{
    DCAN_BIT_RATE_ERR_MAX = 1,
    /**< Bitrate error maximum value */
    DCAN_BIT_RATE_ERR_WARN = 2,
    /**< Bitrate error warning value */
    DCAN_BIT_RATE_ERR_NONE = 3
                             /**< No bit rate error */
} dcanBitTimeCalcErrType_t;

typedef enum dcanQueMsgState_e
{
    DCAN_MSG_STATE_IN_FREEQ,
    DCAN_MSG_STATE_IN_RX_QUE,
    DCAN_MSG_STATE_ISR,
    DCAN_MSG_STATE_MSG_RX,
    DCAN_MSG_STATE_MSG_TX,
    DCAN_MSG_STATE_MSG_RX_ACK
} dcanQueMsgState_e;

typedef enum dcanRxTaskState_e
{
    DCAN_RX_TSK_STATE_START,
    DCAN_RX_TSK_STATE_WAITEVENT,
    DCAN_RX_TSK_STATE_RXMSGCALLBACK,
    DCAN_RX_TSK_STATE_RXACK,
    DCAN_RX_TSK_STATE_STOP
} dcanRxTaskState_e;

typedef enum dcanTxTaskState_e
{
    DCAN_TX_TSK_STATE_START,
    DCAN_TX_TSK_STATE_WAITEVENT,
    DCAN_TX_TSK_STATE_SENDMSG,
    DCAN_TX_TSK_STATE_PROCESSACK,
    DCAN_TX_TSK_STATE_STOP
} dcanTxTaskState_e;

/** \brief Structure holding Bit Time parameters for DCAN application. */
typedef struct dcanBitTimeParamsLocal
{
    UInt32 samplePnt;
    UInt32 timeQuanta;
    UInt32 propSeg;
    UInt32 phaseSeg1;
    UInt32 phaseSeg2;
    UInt32 syncJumpWidth;
    UInt32 bitRatePrescaler;
    UInt32 tseg1Min;
    UInt32 tseg1Max;
    UInt32 tseg2Min;
    UInt32 tseg2Max;
    UInt32 syncJumpWidthMax;
    UInt32 bitRatePrescalerMin;
    UInt32 bitRatePrescalerMax;
    UInt32 bitRatePrescalerInc;
    UInt32 bitRate;
} dcanBitTimeParamsLocal_t;

const UInt32 dcanRxMbxId[] = {UTILS_DCAN_RX_MSG_OBJ,UTILS_DCAN_RX_ACK_MSG_OBJ};
const UInt32 dcanTxMbxId[] = {UTILS_DCAN_TX_MSG_OBJ,UTILS_DCAN_TX_ACK_MSG_OBJ};
#define UTILS_DCAN_NUM_RX_MAILBOX       (UTILS_ARRAYSIZE(dcanRxMbxId))
#define UTILS_DCAN_NUM_TX_MAILBOX       (UTILS_ARRAYSIZE(dcanTxMbxId))

typedef struct dcanRxMsgObj_tag
{
    BspOsal_TaskHandle dcanRxTsk;
    /**< DCAN RX thread */

    Event_Handle dcanRxEvent;
    Event_Struct dcanRxEventMem;
    UInt32 mbxMask;
    dcanRxTaskState_e state;

    struct dcanQueMsgs_s {
        dcanMsg_t msg;
        dcanQueMsgState_e  state;
    } dcanQueMsgs[(UTILS_DCAN_NUM_RX_MAILBOX * UTILS_DCAN_MAX_QUEUE_PER_MBX)];
    struct freeQ_t {
        Utils_QueHandle handle;
        struct dcanQueMsgs_s  *queMem[(UTILS_DCAN_NUM_RX_MAILBOX * UTILS_DCAN_MAX_QUEUE_PER_MBX)];
    } freeQ;
    struct rxMsgQ_t {
        Utils_QueHandle handle;
        struct dcanQueMsgs_s  *queMem[UTILS_DCAN_MAX_QUEUE_PER_MBX * 4];
    } rxMsgQ[UTILS_DCAN_NUM_RX_MAILBOX];
} dcanRxMsgObj_t;

typedef struct dcanTxMsgAckObj_tag
{
  BspOsal_SemHandle semTxComplete;
  /**< Tx complete semaphore handle */

}dcanTxMsgAck_t;


typedef struct dcanTxMsgPeriodicObj_t
{
    BspOsal_ClockHandle clkHandle;
    Bool clkStarted;
} dcanTxMsgPeriodicObj_t;



typedef struct dcanTxMsgObj_tag
{
    BspOsal_TaskHandle dcanTxTsk;
    /**< DCAN RX thread */
    dcanTxTaskState_e state;
    Event_Handle dcanRxAckEvent;
    Utils_QueHandle *dcanRxAckQue;
    Utils_QueHandle *dcanRxAckFreeQue;
    Event_Handle dcanTxEvent;
    Event_Struct dcanTxEventMem;
    dcanTxMsgPeriodicObj_t prd;
    dcanTxMsgAck_t dcanTxMsgAckObj[UTILS_DCAN_NUM_TX_MAILBOX];
} dcanTxMsgObj_t;


typedef struct dcanMbx2MsgIdMap_tag
{
    UInt32 mbxId;
    UInt32 msgId;
} dcanMbx2MsgIdMap_t;

typedef struct dcanIsrContext_tag
{
    dcanRxMsgObj_t *rxMsgObj;
    dcanTxMsgObj_t *txMsgObj;
    BspOsal_IntrHandle  hwi;
    GateMutexPri_Handle mutex;
    GateMutexPri_Struct mutexMem;
} dcanIsrContext_t;


#define UTILS_DCAN_TSK_STACK_SIZE (2 * 1024)

#pragma DATA_ALIGN(gUtilsDcanRx_tskStack, 32)
#pragma DATA_SECTION(gUtilsDcanRx_tskStack, ".bss:taskStackSection")
static UInt8 gUtilsDcanRx_tskStack[UTILS_DCAN_TSK_STACK_SIZE];

#pragma DATA_ALIGN(gUtilsDcanTx_tskStack, 32)
#pragma DATA_SECTION(gUtilsDcanTx_tskStack, ".bss:taskStackSection")
static UInt8 gUtilsDcanTx_tskStack[UTILS_DCAN_TSK_STACK_SIZE];


static dcanRxMsgObj_t dcanRxMsgObj;
static dcanTxMsgObj_t dcanTxMsgObj;
static dcanIsrContext_t dcanIsrContext;
static dcanConfig_t dcanConfig;

static dcanMbx2MsgIdMap_t dcanMbx2MsgIdMap[UTILS_DCAN_NUM_TX_MAILBOX + UTILS_DCAN_NUM_RX_MAILBOX];

static Bool dcanInitDone = FALSE;

static IArg Utils_dcanTxMutexEnter();
static Void Utils_dcanTxMutexLeave(IArg key);
static void Utils_dcanWaitForIfReg(UInt32 baseAddr, UInt32 ifRegNum);
static void Utils_dcanInitTxMsgParams(dcanTxParams_t *pDcanTxPrms,
                                      UInt8 *msgData,
                                      UInt8 length);
static void Utils_dcanInitRxMsgObjParams(dcanMsgObjCfgParams_t *pDcanRxCfgPrms,
                                         UInt32 msgId,UInt32 msgType);
static void Utils_dcanInitTxMsgObjParams(dcanMsgObjCfgParams_t *pDcanTxCfgPrms,
                                         UInt32 msgId,UInt32 msgType);
static void Utils_dcanInitControllerParams(dcanCfgParams_t       *pDcanCfgPrms);
static void Utils_dcanUnRegisterIntr(void);
static void Utils_dcanConfigIntr(void);
static void Utils_dcanInt1Isr();

static UInt32 Utils_dcanBitTimeCalculator(
    dcanBitTimeParamsLocal_t *pBitTimeParam,
    UInt32                  clkFreq);

static int32_t Utils_dcanUpdateSamplePnt(dcanBitTimeParamsLocal_t *pBitTimeParam,
                                      int32_t                   samplePnt,
                                      int32_t                   tseg,
                                      int32_t                  *tseg1,
                                      int32_t                  *tseg2);


static void Utils_dcanWaitForIfReg(UInt32 baseAddr, UInt32 ifRegNum);
static UInt32 Utils_dcanCalculateBitTimeParams(UInt32             clkFreq,
                                                 UInt32             bitRate,
                                                 dcanBitTimeParams_t *pBitTimePrms);
static Void Utils_dcanTxSendMsg();
static UInt Utils_dcanGetTxMbxIndex(UInt32 mailBoxId);
static void Utils_dcanConfigRxMsgObj(UInt32 rxMailboxId);
static Void Utils_dcanSetMailboxMsgId(UInt32 mailboxId,UInt32 msgId);


/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
  *****************************************************************************
  * \brief UtilsDcan wrapper around Utils_quePut
  *
  *  Function performs additional setting of msg state before putting in que
  *
  *****************************************************************************
*/
static Void  Utils_dcanQuePut(Utils_QueHandle * handle, struct dcanQueMsgs_s *msg,
                              dcanQueMsgState_e state)
{
    Int32 status;

    msg->state = state;
    status = Utils_quePut(handle,msg,BIOS_NO_WAIT);
    UTILS_assert(status == 0);
}

/**
  *****************************************************************************
  * \brief UtilsDcan wrapper around Utils_queGet
  *
  *  Function performs additional checks on msg state
  *
  *****************************************************************************
*/
static Void  Utils_dcanQueGet(Utils_QueHandle * handle,
                              struct dcanQueMsgs_s **msgPtr,
                              dcanMsg_t **rxMsgPtr,
                              dcanQueMsgState_e expectedState,
                              dcanQueMsgState_e newState)
{
    Int32 status;


    status = Utils_queGet(handle,(Ptr *)msgPtr,1, BIOS_NO_WAIT);
    UTILS_assert(status == 0);
    UTILS_assert((*msgPtr)->state == expectedState);
    (*msgPtr)->state = newState;
    *rxMsgPtr = &((*msgPtr)->msg);
}


/**
  *****************************************************************************
  * \brief PRD callout function
  *
  *****************************************************************************
*/
static Void Utils_dcanPrdCalloutFcn(UArg arg)
{
    dcanTxMsgObj_t *pObj = (dcanTxMsgObj_t *) arg;

    Event_post (pObj->dcanTxEvent,UTILS_DCAN_TX_PRD_EVENT);

}

/**
  *****************************************************************************
  * \brief Create prd object
  *
  *****************************************************************************
*/
static Void Utils_dcanCreatePrdObj(dcanTxMsgObj_t *pObj, UInt32 period)
{
    pObj->prd.clkHandle = BspOsal_clockCreate(
                            (BspOsal_ClockFuncPtr)Utils_dcanPrdCalloutFcn,
                            period,
                            FALSE,
                            pObj
                            );
    UTILS_assert(pObj->prd.clkHandle != NULL);

    BspOsal_clockStart(pObj->prd.clkHandle);

    pObj->prd.clkStarted = TRUE;

    return;

}

/**
  *****************************************************************************
  * \brief Delete prd object
  *
  *****************************************************************************
*/
static Void Utils_dcanDeletePrdObj(dcanTxMsgObj_t * pObj)
{
    /* Stop the clock */
    BspOsal_clockStop(pObj->prd.clkHandle);
    BspOsal_clockDelete(&pObj->prd.clkHandle);
    pObj->prd.clkHandle = NULL;
    pObj->prd.clkStarted = FALSE;

    return;
}

static void Utils_dcanInitRxQueue(dcanRxMsgObj_t *dcanRxMsg)
{
    Int32 status;
    Int i;

    status =
        Utils_queCreate(&dcanRxMsg->freeQ.handle,
                        UTILS_ARRAYSIZE(dcanRxMsg->freeQ.queMem),
                        &dcanRxMsg->freeQ.queMem[0],
                        UTILS_QUE_FLAG_NO_BLOCK_QUE);
    UTILS_assert(0 == status);
    for ( i = 0; i < UTILS_ARRAYSIZE(dcanRxMsg->dcanQueMsgs);i++)
    {
        Utils_dcanQuePut(&dcanRxMsg->freeQ.handle,
                         &dcanRxMsg->dcanQueMsgs[i],
                         DCAN_MSG_STATE_IN_FREEQ);
    }
    for (i = 0; i < UTILS_ARRAYSIZE(dcanRxMsg->rxMsgQ);i++)
    {
        status =
            Utils_queCreate(&dcanRxMsg->rxMsgQ[i].handle,
                UTILS_ARRAYSIZE(dcanRxMsg->rxMsgQ[i].queMem),
                &dcanRxMsg->rxMsgQ[i].queMem[0],
                UTILS_QUE_FLAG_NO_BLOCK_QUE);
        UTILS_assert(0 == status);
    }
}

/**
  *****************************************************************************
  * \brief Deinitialize DCAN rx msg queue
  *
  *****************************************************************************
*/
static void Utils_dcanDeInitRxQueue(dcanRxMsgObj_t *dcanRxMsg)
{


    Int32 status;
    Int i;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanRxMsg->rxMsgQ);i++)
    {
        status =
            Utils_queDelete(&dcanRxMsg->rxMsgQ[i].handle);
        UTILS_assert(0 == status);
    }
    status =
        Utils_queDelete(&dcanRxMsg->freeQ.handle);
    UTILS_assert(0 == status);
}

/**
  *****************************************************************************
  * \brief Wait for DCAN Tx Msg transmission completion
  *
  *****************************************************************************
*/
static void Utils_dcanWaitForTxComplete(UInt32 txMbxIndex)
{
    Bool semPendStatus;

    UTILS_assert(txMbxIndex < UTILS_ARRAYSIZE(dcanTxMsgObj.dcanTxMsgAckObj));
    UTILS_assert(dcanTxMsgObj.dcanTxMsgAckObj[txMbxIndex].semTxComplete != NULL);

    semPendStatus = BspOsal_semWait(dcanTxMsgObj.dcanTxMsgAckObj[txMbxIndex].semTxComplete,
                                BSP_OSAL_WAIT_FOREVER);
    UTILS_assert(semPendStatus == TRUE);
}

/**
  *****************************************************************************
  * \brief Write MSG to DCAN bus
  *
  *****************************************************************************
*/
static void Utils_dcanWrite(dcanTxParams_t *msg,UInt32 mbxId)
{
    IArg key;
    Int32 retVal;
    UInt32 mbxIndex;

    mbxIndex = Utils_dcanGetTxMbxIndex(mbxId);

    key = Utils_dcanTxMutexEnter();
    Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_TX_IF_REG);
    retVal = DCANTransmitData(UTILS_DCAN_INST,
               mbxId,
               UTILS_DCAN_TX_IF_REG,
               msg,
               0);
    UTILS_assert(retVal == 0);
    /* Wait for config to be copied to internal message RAM */
    Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_TX_IF_REG);
    Utils_dcanWaitForTxComplete(mbxIndex);
    Utils_dcanTxMutexLeave(key);
}

/**
  *****************************************************************************
  * \brief Initialize xmit completion related data structures
  *
  *****************************************************************************
*/
static void Utils_dcanInitTxAckObj(dcanTxMsgObj_t *dcanTxMsgObj)
{
    Int i;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanTxMsgObj->dcanTxMsgAckObj); i++)
    {
        dcanTxMsgObj->dcanTxMsgAckObj[i].semTxComplete =
          BspOsal_semCreate(0, TRUE);
    }
}

/**
  *****************************************************************************
  * \brief Initialize critical section associated with DCAN msg xmit
  *
  *****************************************************************************
*/
static Void Utils_dcanInitGateObj(dcanIsrContext_t *dcanIsrContext)
{
    GateMutexPri_Params prms;

    GateMutexPri_Params_init(&prms);
    GateMutexPri_construct(&dcanIsrContext->mutexMem,&prms);
    dcanIsrContext->mutex =  GateMutexPri_handle(&dcanIsrContext->mutexMem);
}

/**
  *****************************************************************************
  * \brief DeInitialize critical section associated with DCAN msg xmit
  *
  *****************************************************************************
*/
static Void Utils_dcanDeInitGateObj(dcanIsrContext_t *dcanIsrContext)
{
    GateMutexPri_destruct(&dcanIsrContext->mutexMem);
    dcanIsrContext->mutex =  NULL;
}

/**
  *****************************************************************************
  * \brief Enter critical section associated with DCAN msg xmit
  *
  *****************************************************************************
*/
static IArg Utils_dcanTxMutexEnter()
{
    UTILS_assert(NULL != dcanIsrContext.mutex);

    return (GateMutexPri_enter(dcanIsrContext.mutex));
}

/**
  *****************************************************************************
  * \brief Leave critical section associated with DCAN msg xmit
  *
  *****************************************************************************
*/
static Void Utils_dcanTxMutexLeave(IArg key)
{
    UTILS_assert(NULL != dcanIsrContext.mutex);

    GateMutexPri_leave(dcanIsrContext.mutex,key);
}

/**
  *****************************************************************************
  * \brief Deintialize DCAN xmit msg completion related data structures
  *
  *****************************************************************************
*/
static void Utils_dcanDeInitTxAckObj(dcanTxMsgObj_t *dcanTxMsgObj)
{
    Int i;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanTxMsgObj->dcanTxMsgAckObj); i++)
    {
        BspOsal_semDelete(&dcanTxMsgObj->dcanTxMsgAckObj[i].semTxComplete);
    }
}

/**
  *****************************************************************************
  * \brief DCAN RX Get mailbox index for the passed mailbox id
  *
  *****************************************************************************
*/
static UInt Utils_dcanGetRxMbxIndex(UInt32 mailBoxId)
{
    UInt i;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanRxMbxId); i++)
    {
        if (dcanRxMbxId[i] == mailBoxId)
        {
            break;
        }
    }
    UTILS_assert(i < UTILS_ARRAYSIZE(dcanRxMbxId));
    return i;
}

/**
  *****************************************************************************
  * \brief DCAN TX Get mailbox index for the passed mailbox id
  *
  *****************************************************************************
*/
static UInt Utils_dcanGetTxMbxIndex(UInt32 mailBoxId)
{
    UInt i;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanTxMbxId); i++)
    {
        if (dcanTxMbxId[i] == mailBoxId)
        {
            break;
        }
    }
    UTILS_assert(i < UTILS_ARRAYSIZE(dcanTxMbxId));
    return i;
}

/**
  *****************************************************************************
  * \brief DCAN rx msg callback
  *
  *****************************************************************************
*/
static Void Utils_dcanRxMsgProcess(dcanMsg_t *msg)
{
    if (dcanConfig.rxMsgCb)
    {
        dcanConfig.rxMsgCb(msg);
    }
}

/**
  *****************************************************************************
  * \brief Get msg id corresponding to passed mailboxId
  *
  *****************************************************************************
*/
static UInt32 Utils_dcanMapMailboxId2MsgId(UInt32 mailboxId)
{
    Int i;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanMbx2MsgIdMap); i++)
    {
        if (dcanMbx2MsgIdMap[i].mbxId == mailboxId)
        {
            break;
        }
    }
    UTILS_assert(i < UTILS_ARRAYSIZE(dcanMbx2MsgIdMap));
    return dcanMbx2MsgIdMap[i].msgId;
}

/**
  *****************************************************************************
  * \brief Get mailbox id corresponding to passed msgId
  *
  *****************************************************************************
*/
static UInt32 Utils_dcanMapMsgId2MailboxId(UInt32 msgId)
{
    Int i;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanMbx2MsgIdMap); i++)
    {
        if (dcanMbx2MsgIdMap[i].msgId == msgId)
        {
            break;
        }
    }
    UTILS_assert(i < UTILS_ARRAYSIZE(dcanMbx2MsgIdMap));
    return dcanMbx2MsgIdMap[i].mbxId;
}

/**
  *****************************************************************************
  * \brief Set msgId for specified mailbox
  *
  *****************************************************************************
*/
static Void Utils_dcanSetMailboxMsgId(UInt32 mailboxId,UInt32 msgId)
{
    Int i;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanMbx2MsgIdMap); i++)
    {
        if (dcanMbx2MsgIdMap[i].mbxId == mailboxId)
        {
            break;
        }
    }
    UTILS_assert(i < UTILS_ARRAYSIZE(dcanMbx2MsgIdMap));
    dcanMbx2MsgIdMap[i].msgId = msgId;
}

/**
  *****************************************************************************
  * \brief Send Rx Ack msg
  *
  * Ack msg is copy of received msg with only msgId modified
  *****************************************************************************
*/
static Void Utils_dcanRxSendAckMsg(dcanMsg_t *rxMsg)
{
    dcanTxParams_t txAckParams;

    Utils_dcanInitTxMsgParams(&txAckParams,&rxMsg->appMsgPrms.msgData[0],
                              rxMsg->appMsgPrms.dataLength);
    Utils_dcanWrite(&txAckParams,UTILS_DCAN_TX_ACK_MSG_OBJ);
}

/**
  *****************************************************************************
  * \brief Send periodic DCAN xmit msg
  *
  *****************************************************************************
*/
static Void Utils_dcanTxSendMsg()
{
    dcanTxParams_t txAckParams;
    Int i,j;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanTxMbxId)-1; i++)
    {
        if (dcanConfig.enableTxMsgCycle)
         {
            for (j = 0; j < UTILS_ARRAYSIZE(dcanConfig.dcanTxPrdMsg.msgData); j++)
             {
                dcanConfig.dcanTxPrdMsg.msgData[j] =
                                (dcanConfig.dcanTxPrdMsg.msgData[j] + 1) % 256;
             }
         }
        Utils_dcanInitTxMsgParams(&txAckParams,&dcanConfig.dcanTxPrdMsg.msgData[0],
                                  UTILS_ARRAYSIZE(dcanConfig.dcanTxPrdMsg.msgData));
        Utils_dcanWrite(&txAckParams,dcanTxMbxId[i]);
    }
}

/**
  *****************************************************************************
  * \brief Dequeue and process any dcan rx msgs across all rx mailbox queues
  *
  *****************************************************************************
*/
static Void Utils_dcanRxProcessMailbox(dcanRxMsgObj_t * dcanRxMsg,
                                       UInt postedEvents)
{
    Int i;
    dcanMsg_t *rxMsg = NULL;
    struct dcanQueMsgs_s * queMsg = NULL;


    for (i = 0; i < UTILS_ARRAYSIZE(dcanRxMbxId) ; i++)
    {
         if (postedEvents & (0x1U << i))
         {
             while (Utils_queGetQueuedCount(&dcanRxMsg->rxMsgQ[i].handle))
             {
                 Utils_dcanQueGet(&dcanRxMsg->rxMsgQ[i].handle,
                                  &queMsg,
                                  &rxMsg,
                                  DCAN_MSG_STATE_IN_RX_QUE,
                                  DCAN_MSG_STATE_MSG_RX);
                 dcanRxMsg->state = DCAN_RX_TSK_STATE_RXMSGCALLBACK;
                 Utils_dcanRxMsgProcess(rxMsg);
                 dcanRxMsg->state = DCAN_RX_TSK_STATE_RXACK;
                 Utils_dcanRxSendAckMsg(rxMsg);
                 Utils_dcanQuePut(&dcanRxMsg->freeQ.handle,
                                  queMsg,
                                  DCAN_MSG_STATE_IN_FREEQ);
                 Utils_dcanConfigRxMsgObj(dcanRxMbxId[i]);
             }
         }
    }
}

/**
  *****************************************************************************
  * \brief DCAN RX thread handler function
  *
  *****************************************************************************
*/
static Void Utils_dcanRxTsk(UArg arg0, UArg arg1)
{
    dcanRxMsgObj_t *dcanRxMsg = (dcanRxMsgObj_t *)arg0;
    UInt32 mbxMask = dcanRxMsg->mbxMask;
    Bool exitLoop = FALSE;
    UInt postedEvents;

    mbxMask |= UTILS_DCAN_TSK_EXIT_EVENT;
    dcanRxMsg->state = DCAN_RX_TSK_STATE_START;

    do {
        dcanRxMsg->state = DCAN_RX_TSK_STATE_WAITEVENT;
        postedEvents = Event_pend(dcanRxMsg->dcanRxEvent,0,mbxMask,
                                  BSP_OSAL_WAIT_FOREVER);
        if (postedEvents & UTILS_DCAN_TSK_EXIT_EVENT)
        {
            exitLoop = TRUE;
        }
        else
        {
            Utils_dcanRxProcessMailbox(dcanRxMsg,postedEvents);

        }
    } while(exitLoop != TRUE);
    dcanRxMsg->state = DCAN_RX_TSK_STATE_STOP;
}

/**
  *****************************************************************************
  * \brief Initialize DCAN Rx thread
  *
  *****************************************************************************
*/
static void Utils_dcanInitRxThread(dcanRxMsgObj_t *dcanRxMsg,UInt32 mbxMask)
{
    Event_Params eventParams;

    Event_Params_init(&eventParams);
    Event_construct(&dcanRxMsg->dcanRxEventMem, &eventParams);
    dcanRxMsg->dcanRxEvent =  Event_handle(&dcanRxMsg->dcanRxEventMem);

    dcanRxMsg->mbxMask = mbxMask;
    dcanRxMsg->dcanRxTsk = BspOsal_taskCreate(
                                (BspOsal_TaskFuncPtr)Utils_dcanRxTsk,
                                "DCAN Rx Task",
                                dcanConfig.dcanRxTskPri,
                                &gUtilsDcanRx_tskStack[0],
                                sizeof(gUtilsDcanRx_tskStack),
                                dcanRxMsg,
                                UTILS_TSK_AFFINITY_CORE0
                                );

    UTILS_assert(dcanRxMsg->dcanRxTsk != NULL);
    Utils_prfLoadRegister(dcanRxMsg->dcanRxTsk, "DCANRX");
}

static UInt32 Utils_dcanResetRxAckMbxMask(UInt32 mbxMask)
{
    UInt rxAckMbxIndex;


    rxAckMbxIndex = Utils_dcanGetRxMbxIndex(UTILS_DCAN_RX_ACK_MSG_OBJ);
    return (mbxMask & ~(0x1U << rxAckMbxIndex));
}

/**
  *****************************************************************************
  * \brief Deinitialize DCAN Rx thread
  *
  *****************************************************************************
*/
static void Utils_dcanDeInitRxThread(dcanRxMsgObj_t *dcanRxMsg)
{
    Event_post(dcanRxMsg->dcanRxEvent,UTILS_DCAN_TSK_EXIT_EVENT);

    Utils_prfLoadUnRegister(dcanRxMsg->dcanRxTsk);

    BspOsal_taskDelete(&dcanRxMsg->dcanRxTsk);

    dcanRxMsg->dcanRxTsk = NULL;
}

/**
  *****************************************************************************
  * \brief Callback function to handle Rx Ack msg
  *
  *****************************************************************************
*/
static Void Utils_dcanTxMsgProcessAck(dcanMsg_t *rxMsg)
{
    if (dcanConfig.rxAckMsgCb)
    {
        dcanConfig.rxAckMsgCb(rxMsg);
    }
}

/**
  *****************************************************************************
  * \brief Rx ack msg handler function
  *
  *****************************************************************************
*/
static Void Utils_dcanTxHandleRxAck(dcanTxMsgObj_t *dcanTxMsg,
                                    UInt postedEvents)
{
    Int i;
    dcanMsg_t *rxMsg = NULL;
    struct dcanQueMsgs_s *queMsg;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanRxMbxId) ; i++)
    {
         if (postedEvents & (0x1U << i))
         {
             Utils_dcanQueGet(dcanTxMsg->dcanRxAckQue,
                              &queMsg,
                              &rxMsg,
                              DCAN_MSG_STATE_IN_RX_QUE,
                              DCAN_MSG_STATE_MSG_RX_ACK);
             Utils_dcanTxMsgProcessAck(rxMsg);
             Utils_dcanQuePut(dcanTxMsg->dcanRxAckFreeQue,
                              queMsg,
                              DCAN_MSG_STATE_IN_FREEQ);
             Utils_dcanConfigRxMsgObj(dcanRxMbxId[i]);
         }
    }
}

/**
  *****************************************************************************
  * \brief DCAN periodic thread handler function
  *
  *****************************************************************************
*/
static Void Utils_dcanTxTsk(UArg arg0, UArg arg1)
{
    dcanTxMsgObj_t *dcanTxMsg = (dcanTxMsgObj_t *)arg0;
    Bool exitLoop = FALSE;
    UInt32 eventMask = 0;
    UInt postedEvents;
    UInt rxAckMbxIndex;

    rxAckMbxIndex = Utils_dcanGetRxMbxIndex(UTILS_DCAN_RX_ACK_MSG_OBJ);
    eventMask |= UTILS_DCAN_TSK_EXIT_EVENT;
    eventMask |= UTILS_DCAN_TX_PRD_EVENT;
    dcanTxMsg->state = DCAN_TX_TSK_STATE_START;

    do {
        dcanTxMsg->state = DCAN_TX_TSK_STATE_WAITEVENT;
        postedEvents = Event_pend(dcanTxMsg->dcanTxEvent,0,eventMask,
                                  BSP_OSAL_WAIT_FOREVER);
        if (postedEvents & UTILS_DCAN_TSK_EXIT_EVENT)
        {
            exitLoop = TRUE;
        }
        else
        {
            postedEvents =
            Event_pend(dcanTxMsg->dcanRxAckEvent,
                       0,
                       (0x1U << rxAckMbxIndex),
                       0);
            if (postedEvents && dcanConfig.enableSendRxAck)
            {
                dcanTxMsg->state = DCAN_TX_TSK_STATE_PROCESSACK;
                Utils_dcanTxHandleRxAck(dcanTxMsg,postedEvents);
            }
            dcanTxMsg->state = DCAN_TX_TSK_STATE_SENDMSG;
            Utils_dcanTxSendMsg();
        }
    } while(exitLoop != TRUE);
    dcanTxMsg->state = DCAN_TX_TSK_STATE_STOP;
}


/**
  *****************************************************************************
  * \brief Initialize DCAN Tx thread
  *
  *****************************************************************************
*/
static void Utils_dcanInitTxThread(dcanTxMsgObj_t *dcanTxMsg)
{
    Event_Params eventParams;

    Event_Params_init(&eventParams);
    Event_construct(&dcanTxMsg->dcanTxEventMem, &eventParams);
    dcanTxMsg->dcanTxEvent =  Event_handle(&dcanTxMsg->dcanTxEventMem);


    dcanTxMsg->dcanTxTsk = BspOsal_taskCreate(
                                (BspOsal_TaskFuncPtr)Utils_dcanTxTsk,
                                "DCAN Tx Task",
                                dcanConfig.dcanTxTskPri,
                                &gUtilsDcanTx_tskStack[0],
                                sizeof(gUtilsDcanTx_tskStack),
                                dcanTxMsg,
                                UTILS_TSK_AFFINITY_CORE0
                            );

    UTILS_assert(dcanTxMsg->dcanTxTsk != NULL);
    Utils_prfLoadRegister(dcanTxMsg->dcanTxTsk, "DCANTX");
}

/**
  *****************************************************************************
  * \brief Deinitialize DCAN Tx thread
  *
  *****************************************************************************
*/
static void Utils_dcanDeInitTxThread(dcanTxMsgObj_t *dcanTxMsg)
{
    Event_post(dcanTxMsg->dcanTxEvent,UTILS_DCAN_TSK_EXIT_EVENT);

    Utils_prfLoadUnRegister(dcanTxMsg->dcanTxTsk);

    BspOsal_taskDelete(&dcanTxMsg->dcanTxTsk);

    dcanTxMsg->dcanTxTsk = NULL;
}

/**
  *****************************************************************************
  * \brief Platform related initialization of DCAN1 interface
  *
  * PRCM enabled for DCAN1 and setup pinumux for DCAN1 TX / RX pins
  *
  *****************************************************************************
*/
static Void Utils_dcanPlatformInit()
{
    /* DRM_SUSPEND_CTRL_DCAN1 - SUSPEND_SEL(Suspend source selection) as IPU1_C0
     * & SENS_CTRL(Sensitivity control) as 1 means suspend signal must reach the
     * peripheral-IP  */
    //HW_WR_REG32(DRM_SUSPEND_CTRL_DCAN1, ((DRM_SUSPEND_SRC_IPU1_C0 << 4) | 0x1));

    /*Unlock the Crossbar register */
    PlatformUnlockMMR();

    /* Clock Configuration. */
    PlatformDCAN1PrcmEnable();

    /* Perform the DCAN pinmux. */
    PlatformDCAN1SetPinMux();

    /* Initialize the DCAN message RAM. */
    PlatformDcanMessageRamInit(0);
}

/**
  *****************************************************************************
  * \brief Intialize DCAN rx Mailbox config structure
  *
  *****************************************************************************
*/
static void Utils_dcanConfigRxMsgObj(UInt32 rxMailboxId)
{
    Int32               retVal    = STW_SOK;
    dcanMsgObjCfgParams_t appDcanRxCfgPrms;

    /* Wait for interface to become free */
    Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_RX_IF_REG);
    Utils_dcanInitRxMsgObjParams(&appDcanRxCfgPrms,
                                 Utils_dcanMapMailboxId2MsgId(rxMailboxId),FALSE);
    retVal = DCANConfigMsgObj(UTILS_DCAN_INST,
                              rxMailboxId,
                              UTILS_DCAN_RX_IF_REG,
                              &appDcanRxCfgPrms);
    UTILS_assert(retVal == 0);
    /* Wait for config to be copied to internal message RAM */
    Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_RX_IF_REG);
}

/**
  *****************************************************************************
  * \brief Intialize DCAN Rx thread
  *
  *****************************************************************************
*/
static void Utils_dcanInitRx()
{
    Int i;
    UInt32 mbxMask = 0;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanRxMbxId); i++)
    {
        Utils_dcanConfigRxMsgObj(dcanRxMbxId[i]);
        mbxMask |= (0x1U << i);
    }
    Utils_dcanInitRxQueue(&dcanRxMsgObj);
    Utils_dcanInitRxThread(&dcanRxMsgObj,Utils_dcanResetRxAckMbxMask(mbxMask));
}


/**
  *****************************************************************************
  * \brief DeIntialize DCAN Rx thread
  *
  *****************************************************************************
*/
static void Utils_dcanDeInitRx()
{
    Utils_dcanDeInitRxThread(&dcanRxMsgObj);
    Utils_dcanDeInitRxQueue(&dcanRxMsgObj);
}

/**
  *****************************************************************************
  * \brief Intialize DCAN Rx ack related datasturctures
  *
  *****************************************************************************
*/
static void Utils_dcanTxInitAckInfo(dcanTxMsgObj_t *dcanTxMsgObj,
                                    dcanRxMsgObj_t *dcanRxMsgObj)
{
    UInt32 rxAckMbxIndex;

    rxAckMbxIndex = Utils_dcanGetRxMbxIndex(UTILS_DCAN_RX_ACK_MSG_OBJ);
    dcanTxMsgObj->dcanRxAckEvent = dcanRxMsgObj->dcanRxEvent;
    UTILS_assert(NULL != dcanTxMsgObj->dcanRxAckEvent);
    dcanTxMsgObj->dcanRxAckFreeQue = &dcanRxMsgObj->freeQ.handle;
    dcanTxMsgObj->dcanRxAckQue     = &dcanRxMsgObj->rxMsgQ[rxAckMbxIndex].handle;
}

/**
  *****************************************************************************
  * \brief Intialize DCAN TX prd object
  *
  *****************************************************************************
*/
static void Utils_dcanTxInitPrdObj(dcanTxMsgObj_t *dcanTxMsgObj)
{
    Utils_dcanCreatePrdObj(dcanTxMsgObj, dcanConfig.txMsgPeriod_ms);
}

/**
  *****************************************************************************
  * \brief DeIntialize DCAN TX prd object
  *
  *****************************************************************************
*/
static void Utils_dcanTxDeInitPrdObj(dcanTxMsgObj_t *dcanTxMsgObj)
{
    Utils_dcanDeletePrdObj(dcanTxMsgObj);
}

/**
  *****************************************************************************
  * \brief Intialize DCAN TX periodic thread
  *
  *****************************************************************************
*/
static void Utils_dcanInitTx()
{
    Int i;
    Int32               retVal    = STW_SOK;
    dcanMsgObjCfgParams_t appDcanTxCfgPrms;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanTxMbxId); i++)
    {
        /* Wait for interface to become free */
        Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_TX_IF_REG);
        Utils_dcanInitTxMsgObjParams(&appDcanTxCfgPrms,
                                     Utils_dcanMapMailboxId2MsgId(dcanTxMbxId[i]),FALSE);
        retVal = DCANConfigMsgObj(UTILS_DCAN_INST,
                                  dcanTxMbxId[i],
                                  UTILS_DCAN_TX_IF_REG,
                                  &appDcanTxCfgPrms);
        UTILS_assert(retVal == 0);
        /* Wait for config to be copied to internal message RAM */
        Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_TX_IF_REG);
    }
    Utils_dcanInitTxAckObj(&dcanTxMsgObj);
    Utils_dcanTxInitAckInfo(&dcanTxMsgObj,&dcanRxMsgObj);
    if ((dcanConfig.enablePeriodicTx) || (dcanConfig.enableLoopback))
    {
        Utils_dcanTxInitPrdObj(&dcanTxMsgObj);
        Utils_dcanInitTxThread(&dcanTxMsgObj);
    }
}

/**
  *****************************************************************************
  * \brief DeIntialize DCAN TX periodic thread
  *
  *****************************************************************************
*/
static void Utils_dcanDeInitTx()
{
    if ((dcanConfig.enablePeriodicTx) || (dcanConfig.enableLoopback))
    {
        Utils_dcanDeInitTxThread(&dcanTxMsgObj);
        Utils_dcanTxDeInitPrdObj(&dcanTxMsgObj);
    }
    Utils_dcanDeInitTxAckObj(&dcanTxMsgObj);
}

/**
  *****************************************************************************
  * \brief Intialize default mapping between mailbox and msgid
  *
  *****************************************************************************
*/
static Void Utils_dcanInitDefaultMbx2MsgIdMap()
{
    dcanMbx2MsgIdMap[0].mbxId = UTILS_DCAN_RX_MSG_OBJ;
    dcanMbx2MsgIdMap[0].msgId = UTILS_DCAN_CTRL_MSG_ID;
    dcanMbx2MsgIdMap[1].mbxId = UTILS_DCAN_TX_MSG_OBJ;
    dcanMbx2MsgIdMap[1].msgId = UTILS_DCAN_CTRL_MSG_ID;
    dcanMbx2MsgIdMap[2].mbxId = UTILS_DCAN_RX_ACK_MSG_OBJ;
    dcanMbx2MsgIdMap[2].msgId = UTILS_DCAN_CTRL_ACK_MSG_ID;
    dcanMbx2MsgIdMap[3].mbxId = UTILS_DCAN_TX_ACK_MSG_OBJ;
    dcanMbx2MsgIdMap[3].msgId = UTILS_DCAN_CTRL_ACK_MSG_ID;
}

/**
  *****************************************************************************
  * \brief Intialize Utils_dcan global structures
  *
  *****************************************************************************
*/
static Void Utils_dcanInitStruct()
{
    Utils_dcanInitDefaultMbx2MsgIdMap();
    memset(&dcanTxMsgObj,0,sizeof(dcanTxMsgObj));
    memset(&dcanRxMsgObj,0,sizeof(dcanRxMsgObj));
    memset(&dcanIsrContext,0,sizeof(dcanIsrContext));
    dcanIsrContext.rxMsgObj = &dcanRxMsgObj;
    dcanIsrContext.txMsgObj = &dcanTxMsgObj;


}


/**
  *****************************************************************************
  * \brief Intialize default values for DCAN tx msg
  *
  *****************************************************************************
*/
static void Utils_dcanInitTxMsgParams(dcanTxParams_t        *pDcanTxPrms,
                                      UInt8 *msgData,
                                      UInt8 length)
{
    Int i;

    /*Intialize DCAN Tx transfer Params*/
    pDcanTxPrms->dataLength  = length;
    for (i = 0; i < length;i++)
    {
        pDcanTxPrms->msgData[i]  = msgData[i];
    }
}

/**
  *****************************************************************************
  * \brief Intialize default values for DCAN rx mailbox configuration
  *
  * \param pDcanRxCfgPrms Config params rx mailbox intialization
  * \param msgId Message Id asscoiated with the mailbox
  *
  *****************************************************************************
*/
static void Utils_dcanInitRxMsgObjParams(dcanMsgObjCfgParams_t *pDcanRxCfgPrms,
                                         UInt32 msgId,UInt32 msgType)
{
    /*Intialize DCAN Rx Config Params*/
    pDcanRxCfgPrms->xIdFlagMask       = 0x1;
    pDcanRxCfgPrms->dirMask           = 0x1;
    pDcanRxCfgPrms->msgIdentifierMask = 0x1FFFFFFF;

    pDcanRxCfgPrms->msgValid      = TRUE;
    pDcanRxCfgPrms->xIdFlag       = msgType;
    pDcanRxCfgPrms->direction     = DCAN_DIR_RX;
    if (FALSE == pDcanRxCfgPrms->xIdFlag)
    {
        msgId = (msgId & 0x7FF) << 18;
    }
    pDcanRxCfgPrms->msgIdentifier = msgId;

    pDcanRxCfgPrms->uMaskUsed    = TRUE;
    pDcanRxCfgPrms->intEnable    = TRUE;
    pDcanRxCfgPrms->remoteEnable = FALSE;

    pDcanRxCfgPrms->fifoEOBFlag  = TRUE;

}

/**
  *****************************************************************************
  * \brief Intialize default values for DCAN tx mailbox configuration
  *
  * \param pDcanTxCfgPrms Config params tx mailbox intialization
  * \param msgId Message Id asscoiated with the mailbox
  *
  *****************************************************************************
*/
static void Utils_dcanInitTxMsgObjParams(dcanMsgObjCfgParams_t *pDcanTxCfgPrms,
                                         UInt32 msgId,UInt32 msgType)
{
    /*Intialize DCAN tx Config Params*/
    pDcanTxCfgPrms->xIdFlagMask       = 0x1;
    pDcanTxCfgPrms->dirMask           = 0x1;
    pDcanTxCfgPrms->msgIdentifierMask = 0x1FFFFFFF;

    pDcanTxCfgPrms->msgValid      = TRUE;
    pDcanTxCfgPrms->xIdFlag       = msgType;
    pDcanTxCfgPrms->direction     = DCAN_DIR_TX;
    if (FALSE == pDcanTxCfgPrms->xIdFlag)
    {
        msgId = (msgId & 0x7FF) << 18;
    }
    pDcanTxCfgPrms->msgIdentifier = msgId;

    pDcanTxCfgPrms->uMaskUsed    = TRUE;
    pDcanTxCfgPrms->intEnable    = TRUE;
    pDcanTxCfgPrms->remoteEnable = FALSE;

    pDcanTxCfgPrms->fifoEOBFlag  = TRUE;
}


/**
  *****************************************************************************
  * \brief DCAN controller configuration default params initialization
  *
  * \param pDcanCfgPrms Config params to intialize
  *
  *****************************************************************************
*/
static void Utils_dcanInitControllerParams(dcanCfgParams_t       *pDcanCfgPrms)
{
    /*Intialize DCAN Config Params*/
    pDcanCfgPrms->parityEnable          = FALSE;
    pDcanCfgPrms->autoRetransmitDisable = TRUE;
    pDcanCfgPrms->autoBusOnEnable       = FALSE;
    pDcanCfgPrms->intrLine0Enable       = FALSE;
    pDcanCfgPrms->intrLine1Enable       = TRUE;
    pDcanCfgPrms->errIntrEnable         = FALSE;
    pDcanCfgPrms->stsChangeIntrEnable   = FALSE;
#ifdef TDA3XX_FAMILY_BUILD
    pDcanCfgPrms->eccModeEnable = FALSE;
#endif
    pDcanCfgPrms->autoBusOnTimerVal = FALSE;
    if (dcanConfig.enableLoopback)
    {
        pDcanCfgPrms->testModeEnable    = TRUE;
        pDcanCfgPrms->testMode          = DCAN_TEST_MODE_EXT_LPBACK;
    }
    else
    {
        pDcanCfgPrms->testModeEnable    = FALSE;
        pDcanCfgPrms->testMode          = DCAN_TEST_MODE_NONE;
    }
    pDcanCfgPrms->if1DmaEnable      = FALSE;
    pDcanCfgPrms->if2DmaEnable      = FALSE;
    pDcanCfgPrms->if3DmaEnable      = FALSE;
    pDcanCfgPrms->ramAccessEnable   = FALSE;
}

/**
 * \brief   This function takes I/P Clk frequency, required bit-rate on the
 *          CAN bus and calculates the value to be programmed for DCAN BTR
 *          register. This API doesn't to the actual programming. This is
 *          intended to be used as a utility function. And the application
 *          should call the #DCANSetBitTime function to do the actual
 *          programming.
 *
 * \param   clkFreq        I/P clock frequency to DCAN controller in Hz.
 * \param   bitRate        Required bit-rate on the CAN bus in bits per second.
 * \param   pBitTimePrms   Pointer to params where the calculated register
 *                         fields are populated
 *
 * \return  errVal         Returns Bit Time calculation error of type enum
 *                         dcanBitTimeCalcErrType_t
 */
static UInt32 Utils_dcanCalculateBitTimeParams(UInt32             clkFreq,
                                                 UInt32             bitRate,
                                                 dcanBitTimeParams_t *pBitTimePrms)
{
    UInt32 errVal;
    dcanBitTimeParamsLocal_t bitTimePrms;

    bitTimePrms.samplePnt           = 0U;
    bitTimePrms.timeQuanta          = 0U;
    bitTimePrms.propSeg             = 0U;
    bitTimePrms.phaseSeg1           = 0U;
    bitTimePrms.phaseSeg2           = 0U;
    bitTimePrms.syncJumpWidth       = 0U;
    bitTimePrms.bitRatePrescaler    = 0U;
    bitTimePrms.tseg1Min            = 1U;
    bitTimePrms.tseg1Max            = 16U;
    bitTimePrms.tseg2Min            = 1U;
    bitTimePrms.tseg2Max            = 8U;
    bitTimePrms.syncJumpWidthMax    = 4U;
    bitTimePrms.bitRatePrescalerMin = 1U;
    bitTimePrms.bitRatePrescalerMax = 1024U;
    bitTimePrms.bitRatePrescalerInc = 1U;
    bitTimePrms.bitRate             = bitRate;

    errVal = Utils_dcanBitTimeCalculator(&bitTimePrms, clkFreq);

    pBitTimePrms->baudRatePrescaler =
        ((bitTimePrms.bitRatePrescaler - 1U) & DCAN_BTR_BRP_MASK);
    pBitTimePrms->syncJumpWidth = bitTimePrms.syncJumpWidth;
    pBitTimePrms->timeSegment1  =
        (bitTimePrms.phaseSeg1 + bitTimePrms.propSeg - 1U);
    pBitTimePrms->timeSegment2         = (bitTimePrms.phaseSeg2 - 1U);
    pBitTimePrms->baudRatePrescalerExt =
        (((bitTimePrms.bitRatePrescaler -
           1U) & UTILS_DCAN_EXTRACT_BRPE_VAL) >> UTILS_DCAN_BRPE_SHIFT);

    return (errVal);
}

/**
  *****************************************************************************
  * \brief DCAN bit timing calcuation related function
  *
  *****************************************************************************
*/
static UInt32 Utils_dcanBitTimeCalculator(
    dcanBitTimeParamsLocal_t *pBitTimeParam,
    UInt32                  clkFreq)
{
    Int32  samplePnt = 0U, samplePntErr = 1000U, tsegAll = 0U;
    Int32  tseg      = 0U, tseg1 = 0U, tseg2 = 0U;
    Int32  brp       = 0U, samplePntNew = 0U, bestTseg = 0U, bestBrp = 0U;
    Long   err       = 0U, bestErr = 1000000000U;
    UInt32 errVal    = DCAN_BIT_RATE_ERR_NONE;
    UInt32 rate      = 0U, timeQuanta = 0U;

    if (pBitTimeParam->bitRate > 800000U)
    {
        samplePnt = 750U;
    }
    else if (pBitTimeParam->bitRate > 500000U)
    {
        samplePnt = 800U;
    }
    else
    {
        samplePnt = 875U;
    }

    for (tseg = (pBitTimeParam->tseg1Max + pBitTimeParam->tseg2Max) * 2 + 1;
         tseg >= (pBitTimeParam->tseg1Min + pBitTimeParam->tseg2Min) * 2;
         tseg--)
    {
        tsegAll = 1 + tseg / 2;

        /* Compute all possible tseg choices (tseg = tseg1+tseg2) */
        brp = clkFreq / (tsegAll * pBitTimeParam->bitRate) + tseg % 2;

        /* chose brp step which is possible in system */
        brp = (brp / pBitTimeParam->bitRatePrescalerInc) *
              pBitTimeParam->bitRatePrescalerInc;

        if ((brp < pBitTimeParam->bitRatePrescalerMin) ||
            (brp > pBitTimeParam->bitRatePrescalerMax))
        {
            continue;
        }

        rate = clkFreq / (brp * tsegAll);
        err  = pBitTimeParam->bitRate - rate;

        /* tseg brp biterror */
        if (err < 0)
        {
            err = -err;
        }
        if (err > bestErr)
        {
            continue;
        }
        bestErr = err;
        if (err == 0)
        {
            samplePntNew = Utils_dcanUpdateSamplePnt(pBitTimeParam,
                                                  samplePnt,
                                                  tseg / 2,
                                                  &tseg1,
                                                  &tseg2);

            err = samplePnt - samplePntNew;
            if (err < 0)
            {
                err = -err;
            }
            if (err > samplePntErr)
            {
                continue;
            }
            samplePntErr = err;
        }
        bestTseg = tseg / 2;
        bestBrp  = brp;
        if (err == 0)
        {
            break;
        }
    }

    if (bestErr)
    {
        /* Error in one-tenth of a percent */
        err = (bestErr * 1000) / pBitTimeParam->bitRate;
        if (err > UTILS_DCAN_CALC_MAX_ERROR)
        {
            errVal = DCAN_BIT_RATE_ERR_MAX;
        }
        else
        {
            errVal = DCAN_BIT_RATE_ERR_WARN;
        }
    }

    /* real sample point */
    pBitTimeParam->samplePnt = Utils_dcanUpdateSamplePnt(pBitTimeParam,
                                                      samplePnt,
                                                      bestTseg,
                                                      &tseg1,
                                                      &tseg2);

    /* Calculate the time quanta value. */
    timeQuanta = bestBrp * 1000000000UL;

    pBitTimeParam->timeQuanta       = timeQuanta;
    pBitTimeParam->propSeg          = tseg1 / 2;
    pBitTimeParam->phaseSeg1        = tseg1 - pBitTimeParam->propSeg;
    pBitTimeParam->phaseSeg2        = tseg2;
    pBitTimeParam->syncJumpWidth    = 1;
    pBitTimeParam->bitRatePrescaler = bestBrp;

    /* Real bit-rate */
    pBitTimeParam->bitRate =
        clkFreq / (pBitTimeParam->bitRatePrescaler * (tseg1 + tseg2 + 1));

    return (errVal);
}

/**
  *****************************************************************************
  * \brief DCAN bit timing calcuation related function
  *
  *****************************************************************************
*/
static Int32 Utils_dcanUpdateSamplePnt(dcanBitTimeParamsLocal_t *pBitTimeParam,
                                      Int32                   samplePnt,
                                      Int32                   tseg,
                                      Int32                  *tseg1,
                                      Int32                  *tseg2)
{
    *tseg2 = tseg + 1 - (samplePnt * (tseg + 1)) / 1000;

    if (*tseg2 < pBitTimeParam->tseg2Min)
    {
        *tseg2 = pBitTimeParam->tseg2Min;
    }

    if (*tseg2 > pBitTimeParam->tseg2Max)
    {
        *tseg2 = pBitTimeParam->tseg2Max;
    }

    *tseg1 = tseg - *tseg2;

    if (*tseg1 > pBitTimeParam->tseg1Max)
    {
        *tseg1 = pBitTimeParam->tseg1Max;
        *tseg2 = tseg - *tseg1;
    }
    return (1000 * (tseg + 1 - *tseg2) / (tseg + 1));
}

/**
  *****************************************************************************
  * \brief Register the dcan controller interrupt handler
  *
  * \param  NONE
  *
  * \return NONE
  *****************************************************************************
*/
static void Utils_dcanConfigIntr(void)
{
    UInt32 cookie = 0;
    const UInt32 intrId = dcanConfig.dcanCntrlIntrId;

    IntXbar_connectIRQ(intrId, DCAN1_IRQ_INT1);

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

    Vps_printf(" UTILS: DCAN INTERRUPT: HWI Create for INT%d !!!\n", intrId);

    dcanIsrContext.hwi = BspOsal_registerIntr(intrId,
                                    (BspOsal_IntrFuncPtr)Utils_dcanInt1Isr,
                                    &dcanIsrContext
                                    );

    if( dcanIsrContext.hwi == NULL)
    {
        Vps_printf(" UTILS: DCAN INTERRUPT: HWI Create Failed !!!\n");
        UTILS_assert(0);
    }

    /* Enable the interrupt */
    Hwi_enableInterrupt(intrId);

    /* Restore interrupts */
    Hwi_restore(cookie);
}

/**
  *****************************************************************************
  * \brief Unregister the dcan interrupt handler
  *
  * \param  NONE
  *
  * \return NONE
  *****************************************************************************
*/
static void Utils_dcanUnRegisterIntr(void)
{
    UInt32 cookie = 0;
    const UInt32 intrId = dcanConfig.dcanCntrlIntrId;

    /* Disabling the global interrupts */
    cookie = Hwi_disable();

    /* Enable the interrupt */
    Hwi_disableInterrupt(intrId);

    BspOsal_unRegisterIntr(&dcanIsrContext.hwi);

    /* Restore interrupts */
    Hwi_restore(cookie);

    IntXbar_disconnectIRQ(intrId);
}

/**
  *****************************************************************************
  * \brief Initialize DCAN Rx Msg structure
  *
  * \param  rxMsg         Pointer to dcan rx msg stucure
  *
  * \return NONE
  *****************************************************************************
*/
static void Utils_dcanResetRxMsg(dcanMsg_t *rxMsg)
{
    rxMsg->appMsgPrms.dataLength  = 0;
}

/**
  *****************************************************************************
  * \brief DCAN1 controller ISR receive specific handling
  *
  * \param  dcanRxMsgObj  Pointer to recv msg obj
  * \param  mbxId         Recv mailbox id
  * \param  rxMbxIndex    Recv mailbox index
  *
  * \return NONE
  *****************************************************************************
*/
static void Utils_dcanRxIsrCb(dcanRxMsgObj_t *dcanRxMsgObj,
                              UInt32 mbxId,
                              UInt32 rxMbxIndex)
{

    dcanMsg_t *rxMsg = NULL;
    struct dcanQueMsgs_s * queMsg = NULL;
    Int32 retVal;

    /* Get free can rx msg  */
    Utils_dcanQueGet(&dcanRxMsgObj->freeQ.handle,
                     &queMsg,
                     &rxMsg,
                     DCAN_MSG_STATE_IN_FREEQ,
                     DCAN_MSG_STATE_ISR);
    Utils_dcanResetRxMsg(rxMsg);

    /* Wait for interface to become free */
    Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_RX_IF_REG);
    /* Get data from CAN mailbox */
    retVal = DCANGetData(UTILS_DCAN_INST,
                         mbxId,
                         UTILS_DCAN_RX_IF_REG,
                         &rxMsg->appMsgPrms,
                         0);
    UTILS_assert(retVal == 0);
    Utils_dcanConfigRxMsgObj(mbxId);
    /* Copy CAN RX msg to free  msg  */
    rxMsg->msgId = Utils_dcanMapMailboxId2MsgId(mbxId);
    UTILS_assert(rxMbxIndex < UTILS_ARRAYSIZE(dcanRxMsgObj->rxMsgQ));
    /* Put received  msg into CAN RX mailbox specific queue */
    Utils_dcanQuePut(&dcanRxMsgObj->rxMsgQ[rxMbxIndex].handle,
                     queMsg,
                     DCAN_MSG_STATE_IN_RX_QUE);
    UTILS_assert(rxMbxIndex < UTILS_ARRAYSIZE(dcanRxMbxId));
    Event_post(dcanRxMsgObj->dcanRxEvent,(0x1U << rxMbxIndex));
}

/**
  *****************************************************************************
  * \brief DCAN1 controller ISR transmit specific handling
  *
  * \param  dcanTxMsgObj  Pointer to xmit msg obj
  * \param  txMbxIndex    Xmit mailbox index
  *
  * \return NONE
  *****************************************************************************
*/
static void Utils_dcanTxIsrCb(dcanTxMsgObj_t *dcanTxMsgObj,
                              UInt32 txMbxIndex)
{
    UTILS_assert(txMbxIndex < UTILS_ARRAYSIZE(dcanTxMsgObj->dcanTxMsgAckObj));
    BspOsal_semPost(dcanTxMsgObj->dcanTxMsgAckObj[txMbxIndex].semTxComplete);
}

/**
  *****************************************************************************
  * \brief DCAN1 controller interrupt handler
  *
  * \param  ctx      Pointer to DCAN controller ISR context
  *
  * \return NONE
  *****************************************************************************
*/
static void Utils_dcanInt1Isr(UArg ctx)
{
    Int i;
    dcanIsrContext_t *dcanIsrCtx = (dcanIsrContext_t *)ctx;

    for (i = 0; i < UTILS_ARRAYSIZE(dcanTxMbxId);i++)
    {
        if ((DCANIsMsgObjIntrPending(UTILS_DCAN_INST, dcanTxMbxId[i])) == TRUE)
        {
            Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_TX_IF_REG);
            /* Clear the interrupts  of MSG_OBJ 1 for transmit */
            DCANIntrClearStatus(UTILS_DCAN_INST, dcanTxMbxId[i],
                                UTILS_DCAN_TX_IF_REG);
            Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_TX_IF_REG);
            Utils_dcanTxIsrCb(dcanIsrCtx->txMsgObj,i);
        }
    }
    for (i = 0; i < UTILS_ARRAYSIZE(dcanRxMbxId);i++)
    {
        if ((DCANIsMsgObjIntrPending(UTILS_DCAN_INST, dcanRxMbxId[i])) == TRUE)
        {
            Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_RX_IF_REG);
            /* Clear the interrupts  of MSG_OBJ 2 for Receive */
            DCANIntrClearStatus(UTILS_DCAN_INST, dcanRxMbxId[i],
                                UTILS_DCAN_RX_IF_REG);
            Utils_dcanWaitForIfReg(UTILS_DCAN_INST, UTILS_DCAN_RX_IF_REG);
            Utils_dcanRxIsrCb(dcanIsrCtx->rxMsgObj,dcanRxMbxId[i],i);
        }
    }
}

/**
  *****************************************************************************
  * \brief Wait for DCAN interface regiter to become free
  *
  * \param  baseAddr DCAN IFREG base address
  * \param  ifRegNum DCAN interface register number
  *
  * \return NONE
  *****************************************************************************
*/
static void Utils_dcanWaitForIfReg(UInt32 baseAddr, UInt32 ifRegNum)
{
    do
    {
        if (TRUE != DCANIsIfRegBusy(baseAddr, ifRegNum))
        {
            break;
        }
    }
    while (1);
}

/**
  *****************************************************************************
  * \brief Intialize DCAN mailbox to msgid mapping
  *
  * \param  NONE
  * \return NONE
  *****************************************************************************
*/
static Void Utils_dcanInitMbx2MsgIdMap()
{
    if ((dcanConfig.enablePeriodicTx) || (dcanConfig.enableLoopback))
    {
        Utils_dcanSetMailboxMsgId(UTILS_DCAN_TX_MSG_OBJ,dcanConfig.txMsgId);
        if (dcanConfig.enableLoopback)
        {
            dcanConfig.rxMsgId = dcanConfig.txMsgId;
        }
    }
    if (dcanConfig.enableSendRxAck)
    {
        Utils_dcanSetMailboxMsgId(UTILS_DCAN_TX_ACK_MSG_OBJ,dcanConfig.txAckMsgId);
        if (dcanConfig.enableLoopback)
        {
            Utils_dcanSetMailboxMsgId(UTILS_DCAN_RX_ACK_MSG_OBJ,
                                      dcanConfig.txAckMsgId);
        }
    }

    if (dcanConfig.enableReceiveRxAck && !dcanConfig.enableLoopback)
    {
        Utils_dcanSetMailboxMsgId(UTILS_DCAN_RX_ACK_MSG_OBJ,
                                  dcanConfig.rxAckMsgId);
    }

    Utils_dcanSetMailboxMsgId(UTILS_DCAN_RX_MSG_OBJ,dcanConfig.rxMsgId);
}

/**
  *****************************************************************************
  * \brief Initialize DCAN interface
  *
  * \param  dcanCfg Configuration structure used to initialize DCAN interface
  * \return NONE
  *****************************************************************************
*/
Void Utils_dcanInit(dcanConfig_t *dcanCfg)
{
    Int32               retVal    = STW_SOK;
    Int32               errStatus = STW_SOK;
    dcanBitTimeParams_t   appDcanBitTimePrms;
    dcanCfgParams_t       appDcanCfgPrms;
    Int i;

    UTILS_COMPILETIME_ASSERT(UTILS_ARRAYSIZE(dcanMbx2MsgIdMap) ==
                             (UTILS_ARRAYSIZE(dcanRxMbxId) +
                              UTILS_ARRAYSIZE(dcanTxMbxId)));
    if (FALSE == dcanInitDone)
    {
        dcanConfig = *dcanCfg;
        Utils_dcanInitStruct();
        Utils_dcanInitMbx2MsgIdMap();

        Utils_dcanPlatformInit();
        /* Register Crossbars and IRQ numbers */
        Utils_dcanConfigIntr();

        Utils_dcanInitGateObj(&dcanIsrContext);
        /* Reset the DCAN IP */
        retVal = DCANReset(UTILS_DCAN_INST, BSP_OSAL_WAIT_FOREVER);
        if (retVal == STW_SOK)
        {
            /* Set the desired bit rate based on input clock */
            DCANSetMode(UTILS_DCAN_INST, DCAN_MODE_INIT);
            errStatus = Utils_dcanCalculateBitTimeParams(dcanConfig.dcanInputClk_hz,
                                                   dcanConfig.dcanBaudRate_hz,
                                                   &appDcanBitTimePrms);
            UTILS_assert (errStatus == DCAN_BIT_RATE_ERR_NONE);
            DCANSetBitTime(UTILS_DCAN_INST, &appDcanBitTimePrms);
            DCANSetMode(UTILS_DCAN_INST, DCAN_MODE_NORMAL);

            /* Configure DCAN controller */
            Utils_dcanInitControllerParams(&appDcanCfgPrms);

            DCANConfig(UTILS_DCAN_INST, &appDcanCfgPrms);

        }

        if (retVal == STW_SOK)
        {
            Utils_dcanInitRx();
        }

        if (retVal == STW_SOK)
        {
            Utils_dcanInitTx();
        }
       if(retVal == STW_SOK)
       {
           /*
            * Enable message object interrupt to route interrupt line 1
            */
          for (i = 0; i < UTILS_ARRAYSIZE(dcanMbx2MsgIdMap); i++)
          {
             DCANConfigIntrMux(UTILS_DCAN_INST,
                               DCAN_INTR_LINE_NUM_1,
                           dcanMbx2MsgIdMap[i].mbxId);
          }
       }
       dcanInitDone = TRUE;
    }
}

/**
  *****************************************************************************
  * \brief Deinitialize DCAN interface
  *
  * \param  NONE
  * \return NONE
  *****************************************************************************
*/
Void Utils_dcanDeInit(void)
{
    if (dcanInitDone)
    {
        Utils_dcanDeInitTx();
        Utils_dcanDeInitRx();
        Utils_dcanDeInitGateObj(&dcanIsrContext);
        Utils_dcanUnRegisterIntr();
        dcanInitDone = FALSE;
    }
}

/**
  *****************************************************************************
  * \brief Write DCAN msg
  *
  * \param msg Message to be written to DCAN bus
  * \return NONE
  *****************************************************************************
*/
void Utils_dcanWriteMsg(dcanMsg_t *msg)
{
    Utils_dcanWrite(&msg->appMsgPrms,
                    Utils_dcanMapMsgId2MailboxId(msg->msgId));
}

