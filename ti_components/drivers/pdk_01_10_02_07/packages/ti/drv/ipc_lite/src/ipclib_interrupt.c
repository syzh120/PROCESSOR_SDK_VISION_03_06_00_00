/*
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *
 */
/**
 *  @file   ipclib_interrupt.c
 *
 *  @brief  This file contains the implementation for ipclib interrupt module.
 *
 *
 */

/*_______________________________ Include Files _____________________________*/
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/csl_types.h>
#include <ipclib_interrupt.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_mailbox.h>
#include <ipclib_interrupt_priv.h>

/******************************************************************************
 *                  ipclib object definition
 *****************************************************************************/
static IpcLib_InterruptModuleObject gIpcLibInterruptModuleObj;

/******************************************************************************
 *                  ipclib API implementation
 *****************************************************************************/

 /** DES_ID : DOX_DES_TAG(DES_IPC_LITE_006) */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1426) DOX_REQ_TAG(PDK-1411) DOX_REQ_TAG(PDK-1417)
 */
/**
 * \brief     This API is used to initialize ipc interrupt module
 *
 * \param     ipclibInterruptInitPrm_t initialization parameters for ipclib
 *            interrupt module
 *
 * \return    Status of initilization
 *
 * \note      This API is valid only for Tdaxx
 */
int32_t IpcLib_interruptInit(const IpcLib_InterruptInitPrms *pPrm)
{
    int32_t  retVal = IPCLIB_SOK;
    uint32_t i, j, indx, src, dst, isRegistered;
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;

    /* Initialize all table entries  */
    for (i = 0U; i < IPCLIB_MAX_PROC; i++)
    {
        pObj->procTable.selfProcId     = IPCLIB_INVALID_INFO;
        pObj->procTable.procInfo[i].id = IPCLIB_INVALID_INFO;
        memset((void *) pObj->procTable.procInfo[i].name,
               0,
               IPCLIB_MAX_PROCNAME_LEN);

        pObj->interruptTable[i]       = IPCLIB_INVALID_INFO;
        pObj->registeredInterrupts[i] = IPCLIB_INVALID_INFO;
        pObj->intrHandle[i]           = NULL;

        for (j = 0U; j < IPCLIB_MAX_EVENTS; j++)
        {
            pObj->callbackTable.fxns[i][j] = NULL;
            pObj->callbackTable.args[i][j] = NULL;
        }

        for (j = 0U; j < IPCLIB_MAX_PROC; j++)
        {
            pObj->mailboxTable[i][j].mbxId  = IPCLIB_INVALID_INFO;
            pObj->mailboxTable[i][j].userId = IPCLIB_INVALID_INFO;
            pObj->mailboxTable[i][j].fifo   = IPCLIB_INVALID_INFO;
        }
    }

    /* Copy init params */
    memcpy(&pObj->initPrms,
           pPrm,
           sizeof (IpcLib_InterruptInitPrms));

    /* Read table entries for procTable from platform specific
     * configuration file
     */
    memcpy(&pObj->procTable,
           &IpcLib_gProcConfig,
           sizeof (IpcLib_InterruptProcCfg));

    /* Read table entries for interrupt table from platform specific
     * configuration file but only for proc participating in ipc.
     * Also register interrupt callback isr.
     */

    for (i = 0U; i < pObj->initPrms.numValidProcs; i++)
    {
        indx = pPrm->validProcIds[i];
        pObj->interruptTable[indx] = IpcLib_gIntNumConfig[indx];

        isRegistered = (uint32_t) FALSE;
        for (j = 0U; j < IPCLIB_MAX_PROC; j++)
        {
            if (pObj->interruptTable[indx] == pObj->registeredInterrupts[j])
            {
                isRegistered = (uint32_t) TRUE;
                break;
            }
        }

        if (isRegistered != TRUE)
        {
            pObj->registeredInterrupts[indx] = pObj->interruptTable[indx];
            if (pObj->interruptTable[indx] != IPCLIB_INVALID_INFO)
            {
                /* Register common ISR */
                pObj->intrHandle[indx] =
                    BspOsal_registerIntr(pObj->interruptTable[indx],
                                         ipcLibISR,
                                         (void *) pObj->interruptTable[indx]);
                if (pObj->intrHandle[indx] == NULL)
                {
                    retVal = IPCLIB_EFAIL;
                    break;
                }
            }
        }
    }

    if (retVal == IPCLIB_SOK)
    {
        /* Read table entries for mailboxTable from platform specific
         * configuration file but only for proc participating in ipc
         */

        for (i = 0U; i < pObj->initPrms.numValidProcs; i++)
        {
            src = pPrm->validProcIds[i];
            for (j = 0U; j < pObj->initPrms.numValidProcs; j++)
            {
                dst = pPrm->validProcIds[j];
                if (src != dst)
                {
                    /* Use mailboxes only for procIds enabled by user */
                    pObj->mailboxTable[src][dst] =
                        IpcLib_gMailboxConfig[src][dst];
                }
            }
        }

        /* Set up interrupts controllers with source of an interrupt
         *
         * For a new platform this needs to be implemented in respective
         * platform file.
         */
        ipcLibInitInterrupts();

        /* Create module wide semaphore lock */
        pObj->lockSem = BspOsal_semCreate((int32_t) 1, TRUE);
        if (NULL == pObj->lockSem)
        {
            retVal = IPCLIB_EFAIL;
        }
    }

    return retVal;
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_006) */
/**
 * REQ_ID : DOX_REQ_TAG(PDK-1418)
 */
/**
 * \brief     This API is used to de-initialize ipc interrupt module
 *
 * \return    Status of initilization
 *
 * \note      This API is valid only for Tdaxx
 */
void IpcLib_interruptDeInit(void)
{
    uint32_t indx;
    uint32_t i;
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;

    /* Disconnect interrupts controllers with source of an interrupt
     *
     * For a new platform this needs to be implemented in respective
     * platform file.
     */
    ipcLibDeInitInterrupts();

    for (i = 0U; i < pObj->initPrms.numValidProcs; i++)
    {
        indx = pObj->initPrms.validProcIds[i];
        if (pObj->intrHandle[indx] != NULL)
        {
            /* Un-register common ISR */
            BspOsal_unRegisterIntr(&(pObj->intrHandle[indx]));
            pObj->intrHandle[indx] = NULL;
        }
    }

    /* Delete module wide sem lock */
    if (pObj->lockSem != NULL)
    {
        BspOsal_semDelete(&(pObj->lockSem));
        pObj->lockSem = NULL;
    }
}

/**
 * \brief     This API is used to set default params
 *
 * \param     ipclibInterruptInitPrm_t initialization parameters for ipclib
 *            interrupt module
 *
 * \return    None
 *
 * \note      This API is valid only for Tdaxx
 */
void IpcLib_interruptSetDefaultInitPrm(IpcLib_InterruptInitPrms *pPrm)
{
    uint32_t i;

    /* Assume all processor to be enabled */
    pPrm->numValidProcs = IPCLIB_MAX_PROC;
    for (i = 0; i < IPCLIB_MAX_PROC; i++)
    {
        pPrm->validProcIds[i] = IpcLib_gProcConfig.procInfo[i].id;
    }
    pPrm->msgTimeOut = 0xFFFFFFFFU;
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_007) */
/**
 *  REQ_ID : DOX_REQ_TAG(PDK-1434) DOX_REQ_TAG(PDK-1408)
 *           DOX_REQ_TAG(PDK-1438)
 */
/**
 * \brief     This API is used to registers interrupt callback function
 *
 * \param     remoteProcId remote processor id for which event is being
 *            registered
 *                         (remote processor from which interrupt is expected)
 * \param     eventId      event number less than maximum supported events
 * \param     Fxn          callback function to be registered
 * \params    Arg          argument to the callback function
 *
 * \return    Status codes
 *
 * \note      This API is valid only for Tdaxx
 */
int32_t IpcLib_interruptRegisterEvent(uint32_t                 remoteProcId,
                                      uint32_t                 eventId,
                                      IpcLib_InterruptCallback fxn,
                                      void                    *arg)
{
    int32_t retVal = IPCLIB_SOK;
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;

    /* Take module level lock */
    BspOsal_semWait(pObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Params validation */
    if ((fxn == NULL) ||
        (remoteProcId >= IPCLIB_MAX_PROC) ||
        (eventId >= IPCLIB_MAX_EVENTS))
    {
        retVal = IPCLIB_EBADARGS;
    }

    if (retVal == IPCLIB_SOK)
    {
        /* Register the callback if it is already not registered */
        if (pObj->callbackTable.fxns[remoteProcId][eventId] != NULL)
        {
            retVal = IPCLIB_EALREADYREGISTERED;
        }
        else
        {
            pObj->callbackTable.fxns[remoteProcId][eventId] = fxn;
            pObj->callbackTable.args[remoteProcId][eventId] = arg;
        }
    }

    /* Enable mailboxes */
    IpcLib_interruptEnable(remoteProcId);

    /* Release module level lock */
    BspOsal_semPost(pObj->lockSem);

    return retVal;
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_007) */
/**
 *  REQ_ID : DOX_REQ_TAG(PDK-1604)
 */
/**
 * \brief     This API is used to enable mailboxes
 *
 * \param     remoteProcId remote processor id for which mailboxes need to be
 *                         enabled
 *
 * \return    Status codes
 *
 * \note      This API is valid only for Tdaxx
 */
int32_t IpcLib_interruptEnable(uint32_t remoteProcId)
{
    uint32_t mbxBaseIdx, mbxBase, mbxUser, mbxFifo;
    int32_t  retVal = IPCLIB_SOK;
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;
    uint32_t selfProcId = IpcLib_interruptGetSelfProcId();

    /* Params validation */
    if (remoteProcId >= IPCLIB_MAX_PROC)
    {
        retVal = IPCLIB_EBADARGS;
    }

    if (retVal == IPCLIB_SOK)
    {
        /* Get mailbox details based on parameters */
        mbxBaseIdx = pObj->mailboxTable[remoteProcId][selfProcId].mbxId;
        mbxUser    = pObj->mailboxTable[remoteProcId][selfProcId].userId;
        mbxFifo    = pObj->mailboxTable[remoteProcId][selfProcId].fifo;
        mbxBase    = IpcLib_gMailboxBaseAddr[mbxBaseIdx];

        /* Set mailbox MAILBOX_IRQENABLE_CLR to enable event */
        MailboxEnableNewMsgInt(mbxBase, mbxUser, mbxFifo);
    }

    return retVal;
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_007) */
/**
 *  REQ_ID : DOX_REQ_TAG(PDK-1434) DOX_REQ_TAG(PDK-1413) DOX_REQ_TAG(PDK-1419)
 */
/**
 * \brief     This API is used to unregisters interrupt callback function
 *
 * \param     remoteProcId remote processor id for which event is being
 *            registered
 *                         (remote processor from which interrupt is expected)
 * \param     eventId      event number less than maximum supported events
 * \param     Fxn          callback function to be unregistered
 * \params    Arg          argument to the callback function
 *
 * \return    Status codes
 *
 * \note      This API is valid only for Tdaxx
 */
int32_t IpcLib_interruptUnregisterEvent(uint32_t remoteProcId, uint32_t eventId)
{
    int32_t retVal = IPCLIB_SOK;
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;

    /* Take module level lock */
    BspOsal_semWait(pObj->lockSem, BSP_OSAL_WAIT_FOREVER);

    /* Params validation */
    if ((remoteProcId >= IPCLIB_MAX_PROC) ||
        (eventId >= IPCLIB_MAX_EVENTS))
    {
        retVal = IPCLIB_EBADARGS;
    }

    if (retVal == IPCLIB_SOK)
    {
        /* Reset mailbox MAILBOX_IRQENABLE_CLR to disable event */
        IpcLib_interruptDisable(remoteProcId);

        /* Unregister the callback if already registered*/
        if (pObj->callbackTable.fxns[remoteProcId][eventId] == NULL)
        {
            retVal = IPCLIB_EFAIL;
        }
        else
        {
            pObj->callbackTable.fxns[remoteProcId][eventId] = NULL;
            pObj->callbackTable.args[remoteProcId][eventId] = NULL;
        }
    }

    /* Release module level lock */
    BspOsal_semPost(pObj->lockSem);

    return retVal;
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_007) */
/**
 *  REQ_ID : DOX_REQ_TAG(PDK-1592)
 */
/**
 * \brief     This API is used to Disable mailboxes
 *
 * \param     remoteProcId remote processor id for which mailboxes need to be
 *                         enabled
 *
 * \return    Status codes
 *
 * \note      This API is valid only for Tdaxx
 */
int32_t IpcLib_interruptDisable(uint32_t remoteProcId)
{
    uint32_t mbxBaseIdx, mbxBase, mbxUser, mbxFifo;
    int32_t  retVal = IPCLIB_SOK;
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;
    uint32_t selfProcId = IpcLib_interruptGetSelfProcId();

    /* Params validation */
    if (remoteProcId >= IPCLIB_MAX_PROC)
    {
        retVal = IPCLIB_EBADARGS;
    }

    if (retVal == IPCLIB_SOK)
    {
        /* Get mailbox details based on parameters */
        mbxBaseIdx = pObj->mailboxTable[remoteProcId][selfProcId].mbxId;
        mbxUser    = pObj->mailboxTable[remoteProcId][selfProcId].userId;
        mbxFifo    = pObj->mailboxTable[remoteProcId][selfProcId].fifo;
        mbxBase    = IpcLib_gMailboxBaseAddr[mbxBaseIdx];

        /* Set mailbox MAILBOX_IRQENABLE_CLR to enable event */
        MailboxDisableNewMsgInt(mbxBase, mbxUser, mbxFifo);
    }

    return retVal;
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_008) */
/**
 *  REQ_ID : DOX_REQ_TAG(PDK-1435) DOX_REQ_TAG(PDK-1434) DOX_REQ_TAG(PDK-1405)
             DOX_REQ_TAG(PDK-1413) DOX_REQ_TAG(PDK-1416)
 */
/**
 * \brief     This API is used to send 32 bit value to remote core and interrupt
 *             remote core
 *
 * \param     remoteProcId  remote processor id to which interrupt is to be sent
 * \param     eventId       event number on which interrupt is to be sent
 * \param     payload       value that needs to be sent accross
 * \params    waitClear     flag which ensures interrupt is delivered
 *                          processed
 *                          by intented remote core.
 *
 * \return    Status codes
 *
 * \note      This API is valid only for Tdaxx
 */
int32_t IpcLib_interruptSendEvent(uint32_t remoteProcId,
                                  uint32_t eventId,
                                  uint32_t payload,
                                  uint32_t waitClear)
{
    uint32_t numMsgs, key, smallPayload, mbxBaseIdx, mbxBase, mbxFifo;
    int32_t  retVal     = IPCLIB_SOK;
    uint32_t selfProcId = IpcLib_interruptGetSelfProcId();
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;

    /* Params validation */
    if ((remoteProcId >= IPCLIB_MAX_PROC) ||
        (eventId >= IPCLIB_MAX_EVENTS))
    {
        retVal = IPCLIB_EBADARGS;
    }
    else
    {
        /* Get mailbox details based on parameters */
        mbxBaseIdx = pObj->mailboxTable[selfProcId][remoteProcId].mbxId;
        mbxFifo    = pObj->mailboxTable[selfProcId][remoteProcId].fifo;
        mbxBase    = IpcLib_gMailboxBaseAddr[mbxBaseIdx];

        ipcLibUpdateMbxAddr(selfProcId, remoteProcId, &mbxBase);

        if ((mbxBase == IPCLIB_INVALID_INFO) ||
            (mbxFifo == IPCLIB_INVALID_INFO))
        {
            retVal = IPCLIB_ENOTSUPPORTED;
        }
        else
        {
            /* Decide if the payload is small enough to fit in the first msg
             * Last 5 bits of the first msg are used to store eventId, if
             * msg value can not fit into 27 bits use another message in the
             * mailbox fifo.
             */
            if (payload < IPCLIB_SMALL_PAYLOAD_MAX)
            {
                smallPayload = payload << 5U;
                numMsgs      = 1U;
            }
            else
            {
                smallPayload = IPCLIB_SMALL_PAYLOAD_MASK;
                numMsgs      = 2U;
            }

            /* Disable interrupts */
            key = BspOsal_disableInterrupt();

            /* If waitClear is TRUE wait till mailbox has enough space to
             * put numMsgs.
             * If waitClear is FALSE return error so that user can call the
             * API again based on status.
             */
            while (((IPCLIB_MAILBOX_FIFOLENGTH -
                     MailboxGetMessageCount(mbxBase, mbxFifo)) < numMsgs))
            {
                /* Enable interrupts */
                BspOsal_restoreInterrupt(key);
                if (waitClear == (uint32_t) FALSE)
                {
                    retVal = IPCLIB_ESENDFAILED;
                    break;
                }
                BspOsal_sleep(1U);
                /* Disable interrupts */
                key = BspOsal_disableInterrupt();
            }

            if (retVal == IPCLIB_SOK)
            {
                /* Send messages through mailbox */
                MailboxWriteMessage(mbxBase, mbxFifo, eventId + smallPayload);

                if (smallPayload == IPCLIB_SMALL_PAYLOAD_MASK)
                {
                    MailboxWriteMessage(mbxBase, mbxFifo, payload);
                }
                /* Enable interrupts */
                BspOsal_restoreInterrupt(key);
            }
        }
    }

    return retVal;
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_006) */
/**
 *  REQ_ID : DOX_REQ_TAG(PDK-1410)
 */
/**
 * \brief     This function return procId of executing processor.
 *
 * \return    procId
 *
 * \note      This internal fucntion is valid only for Tdaxx
 */
uint32_t IpcLib_interruptGetSelfProcId(void)
{
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;

    return (pObj->procTable.selfProcId);
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_006) */
/**
 *  REQ_ID : DOX_REQ_TAG(PDK-1415)
 */
/**
 * \brief     This function return procId based on procName.
 *
 * \param     name output - proc name
 *
 * \return    procId
 *
 * \note      This internal fucntion is valid only for Tdaxx
 */
uint32_t IpcLib_interruptGetProcId(const char *name)
{
    uint32_t i;
    uint32_t indx;
    uint32_t id = IPCLIB_INVALID_INFO;
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;

    for (i = 0U; i < pObj->initPrms.numValidProcs; i++)
    {
        indx = pObj->initPrms.validProcIds[i];
        if (strcmp(pObj->procTable.procInfo[indx].name, name) == 0)
        {
            break;
        }
    }

    if (i != pObj->initPrms.numValidProcs)
    {
        id = pObj->procTable.procInfo[indx].id;
    }

    return (id);
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_006) */
/**
 *  REQ_ID : DOX_REQ_TAG(PDK-1415)
 */
/**
 * \brief     This function return proc name based on procId.
 *
 * \param     name     - OUT param proc name
 * \param     length   - string length
 * \param     id input - proc id for which name needs to be retrieved
 *
 * \return    Status codes
 *
 * \note      This internal fucntion is valid only for Tdaxx
 */
int32_t IpcLib_interruptGetProcName(char *name, uint32_t length, uint32_t id)
{
    uint32_t i;
    uint32_t indx;
    int32_t  retVal = IPCLIB_SOK;
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;

    for (i = 0U; i < pObj->initPrms.numValidProcs; i++)
    {
        indx = pObj->initPrms.validProcIds[i];
        if (pObj->procTable.procInfo[indx].id == id)
        {
            break;
        }
    }

    if (i != pObj->initPrms.numValidProcs)
    {
        strncpy(name, pObj->procTable.procInfo[indx].name, length);
    }
    else
    {
        retVal = IPCLIB_EFAIL;
    }

    return (retVal);
}

/******************************************************************************
 *                  ipclib internal functions
 *****************************************************************************/

 /** DES_ID : DOX_DES_TAG(DES_IPC_LITE_008) */
 /**
 *  REQ_ID : DOX_REQ_TAG(PDK-1482) DOX_REQ_TAG(PDK-1405) DOX_REQ_TAG(PDK-1406)
 */
/**
 * \brief     This function is used internally by ipc interrupt module
 *            It is the interrupt service routine for mailbox based interrupt.
 *
 * \note      This is an internal fucntion
 */
void ipcLibISR(uint32_t arg)
{
    uint32_t numProcessed, i, remoteProcId, msgCount, irqEnableStatus;
    uint32_t mbxIdx, mbxBase, mbxUser, mbxFifo;
    uint32_t selfProcId = IpcLib_interruptGetSelfProcId();
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;

    do {
        numProcessed = 0;
        /* Check which processors can generate this interrupt and get
         * remoteProcId. This for loop is required since interrupt
         * numbers / lines can be shared by more than one remote processor.
         */
        for (i = 0U; i < pObj->initPrms.numValidProcs; i++)
        {
            msgCount        = 0U;
            irqEnableStatus = 0U;

            if (arg == pObj->interruptTable[pObj->initPrms.validProcIds[i]])
            {
                remoteProcId = pObj->initPrms.validProcIds[i];

                /* Get mailbox details based on parameters */
                mbxUser = pObj->mailboxTable[remoteProcId][selfProcId].userId;
                mbxFifo = pObj->mailboxTable[remoteProcId][selfProcId].fifo;
                mbxIdx  = pObj->mailboxTable[remoteProcId][selfProcId].mbxId;

                /* Check if mbxIdx is valid mailbox to prevent wrong indexing.
                 * Especially when selfProcId and remoteProcId are same, user
                 * may have enabled the mailbox or it could be invalid entry.
                 */
                if (mbxIdx < IPCLIB_MAX_MAILBOXES)
                {
                    mbxBase = IpcLib_gMailboxBaseAddr[mbxIdx];
                    /* mbxBase can be invalid if the mailbox entry is not
                     * a valid address in IpcLib_gMailboxBaseAddr, this can
                     * occur if number of mailboxes actually used are less
                     * than IPCLIB_MAX_MAILBOXES.
                     */
                    if (mbxBase != IPCLIB_INVALID_INFO)
                    {
                        /* Check message count and irq enable status */
                        msgCount = MailboxGetMessageCount(mbxBase,
                                                          mbxFifo);
                        irqEnableStatus = MailboxGetIrqEnableStatus(mbxBase,
                                                                    mbxUser,
                                                                    mbxFifo);
                    }
                }
            }

            if ((msgCount != 0U) && (irqEnableStatus != 0U))
            {
                /* Deliver payload to registered callback */
                ipcLibDeliverMessage(mbxBase, mbxUser, mbxFifo, remoteProcId);
                numProcessed++;
            }
        }
    } while (numProcessed != 0);
}

/** DES_ID : DOX_DES_TAG(DES_IPC_LITE_009) */
/**
 *  REQ_ID : DOX_REQ_TAG(PDK-1482) DOX_REQ_TAG(PDK-1405) DOX_REQ_TAG(PDK-1406)
 */
/**
 * \brief     This function is used internally by ipcLibISR.
 *
 *
 * \note      This is an internal fucntion
 */
void ipcLibDeliverMessage(uint32_t mbxBase,
                          uint32_t mbxUser,
                          uint32_t mbxFifo,
                          uint32_t remoteProcId)
{
    uint32_t msg, eventId, payload, msgTimeOut, msgCount;
    int32_t  status = IPCLIB_SOK;
    IpcLib_InterruptModuleObject *pObj = &gIpcLibInterruptModuleObj;

    /* Read mailbox message */
    MailboxGetMessage(mbxBase, mbxFifo, &msg);

    eventId = (uint32_t) (msg & 0x1FU);
    payload = msg >> 5U;

    /* Check if there is 2nd relavent message in the mailbox fifo
     * incase of bigger payload
     */
    if (payload == IPCLIB_SMALL_PAYLOAD_MAX)
    {
        msgCount   = 0U;
        msgTimeOut = pObj->initPrms.msgTimeOut;
        do
        {
            /* Timeout here ensure no busy wait forever */
            msgCount = MailboxGetMessageCount(mbxBase, mbxFifo);
            msgTimeOut--;
        } while ((msgCount == 0U) && (msgTimeOut != 0U));

        if ((msgCount == 0U) && (msgTimeOut == 0U))
        {
            status = IPCLIB_ETIMEOUT;
        }
        else
        {
            /* Deliver payload to registered callback */
            MailboxGetMessage(mbxBase, mbxFifo, &payload);
        }
    }

    /* Clear msg status */
    MailboxClrNewMsgStatus(mbxBase, mbxUser, mbxFifo);

    if (pObj->callbackTable.fxns[remoteProcId][eventId] != NULL)
    {
        /* Invoke callback function to deliver the event */
        (pObj->callbackTable.fxns[remoteProcId][eventId])(
            remoteProcId,
            eventId,
            payload,
            pObj->callbackTable.args[remoteProcId][eventId],
            status);
    }

    /* Ensure no interrupt is missed, interrupt can occur while processor
     * is in this ISR, writing EOI will ensure that is not missed
     * and gets processed in the next callback.
     */
    MailboxWriteEOI(mbxBase, mbxUser);
}

/* Nothing beyond this point */
