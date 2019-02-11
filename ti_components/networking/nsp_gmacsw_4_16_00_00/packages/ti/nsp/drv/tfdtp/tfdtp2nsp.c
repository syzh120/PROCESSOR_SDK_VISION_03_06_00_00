/*
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*!
 *  \file   tfdtp2nsp.c
 *
 *  \brief  Translation/adaptation layer between TFDTP and NSP.
 *
 */

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

/* OS/Posix headers */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/hal/Cache.h>

/* NSP Dependencies */
#include <ti/nsp/drv/inc/gmacsw.h>

/* TFDTP_NDK2_NSP layer Dependencies */
#include <ti/nsp/drv/ndk2nsp/ndk2nsp.h>

/* Project dependency headers */
#include "tfdtp.h"
#include "tfdtp_priv.h"

/* This module's header */
#include "tfdtp2nsp.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define TX_BUFF_DESC_PER_PACKET     ((uint32_t)2U)

#define TFDTP_TX_PACKET_TASK_PRI      (OS_TASKPRIHIGH)
#define TFDTP_TX_PACKET_TASK_STACK    (2048)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static void LOCAL_closeTxChannel(void *hCallbackArg);
static void LOCAL_notifyTxPackets(void *hCallbackArg);
static void LOCAL_tfdtpTxPacketTask(UArg arg0, UArg arg1);
static void LOCAL_allocTxPackets(TFDTP2NSP_Handle hTFDTP2NSP);
static uint32_t LOCAL_prepTxPacketQueue(TFDTP2NSP_Handle hTFDTP2NSP, CPDMA_PacketQueue *pPacketQueue);
static void LOCAL_sendTxPackets(TFDTP2NSP_Handle hTFDTP2NSP);
static void LOCAL_pollingCallback(void *hCallbackArg);


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/
#if !defined(NSP_DYNAMIC_ALLOCATION)
TFDTP2NSP_Object TFDTP2NSP_stateObj;
#endif

/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

TFDTP2NSP_Stats tfdtp2NspStats;


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

TFDTP2NSP_Handle TFDTP2NSP_open(const TFDTP2NSP_Config *config)
{
    TFDTP2NSP_Handle hTFDTP2NSP;

    if (config == NULL) { return NULL; }

#if defined(TFDTP_INSTRUMENTATION_ENABLED)
    /* Clear instrumentation statistics structure */
    memset(&tfdtp2NspStats, 0, sizeof(TFDTP2NSP_Stats));
#endif

#if defined(NSP_DYNAMIC_ALLOCATION)
    hTFDTP2NSP = (TFDTP2NSP_Handle)calloc(1U, sizeof(TFDTP2NSP_Object));
    if (hTFDTP2NSP == NULL) return NULL;
#else
    hTFDTP2NSP = &TFDTP2NSP_stateObj;
    memset(hTFDTP2NSP, 0, sizeof(TFDTP2NSP_Object));
#endif

    /* Initialize the Rx Queues & Data */
    //TFDTP_queueInit(&hTFDTP2NSP->rxReadyTFDTPPacketQueue);

    /* Initialize the Tx Queues & Data */
    TFDTP_queueInit(&hTFDTP2NSP->txReadyTFDTPPacketQueue);
    CPDMA_packetQueueInit(&hTFDTP2NSP->txFreeCPDMAPacketQueue);

    /* Register this stack/translation layer's polling callback with the hardware driver */
    hTFDTP2NSP->hGMACSW = GMACSW_open(NULL);
    if (NULL == hTFDTP2NSP->hGMACSW) { goto teardown; }

    /* Save config info */
    memcpy(&hTFDTP2NSP->config, config, sizeof(TFDTP2NSP_Config));

    /* Open Tx Channel */
    {
        CPDMA_OpenTxChannelIoctlCmd cmd;
        CPDMA_TxChannelConfig       chanConfig;

        cmd.pTxChannelConfig                        = &chanConfig;
        cmd.pTxChannelHandle                        = &hTFDTP2NSP->hTxChannel;

        chanConfig.packetCount                      = (uint32_t)TFDTP2NSP_TX_PACKETS;
        chanConfig.buffersPerPacketCount            = (uint32_t)TX_BUFF_DESC_PER_PACKET;
        chanConfig.packetMem                        = (void *) hTFDTP2NSP->txPacketMem;
        chanConfig.callbacks.pFxnCbCloseChannel     = &LOCAL_closeTxChannel;
        chanConfig.callbacks.pFxnCbUsedPacketNotify = &LOCAL_notifyTxPackets;
        chanConfig.callbacks.hCallbackArg           = (void *) hTFDTP2NSP;

        GMACSW_ioctl(hTFDTP2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_OPEN_TX_CHANNEL,
                     (void *)&cmd,
                     sizeof(CPDMA_OpenTxChannelIoctlCmd));
        if (NULL == hTFDTP2NSP->hTxChannel) { goto teardown; }
    }

    /* Create semaphore objects, init shutDown status */
    {
        Semaphore_Params semParams;

        hTFDTP2NSP->shutDown = (bool)false;

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_COUNTING;
        hTFDTP2NSP->shutDownSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hTFDTP2NSP->shutDownSem) { goto teardown; }

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        hTFDTP2NSP->txPacketSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hTFDTP2NSP->txPacketSem) { goto teardown; }

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        hTFDTP2NSP->txPacketFreeSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hTFDTP2NSP->txPacketFreeSem) { goto teardown; }
    }

    /* Start the packet processing tasks now that the channels are open */
    {
        Task_Params taskParams;

        Task_Params_init(&taskParams);
        taskParams.stackSize = TFDTP_TX_PACKET_TASK_STACK;
        taskParams.priority = TFDTP_TX_PACKET_TASK_PRI;
        taskParams.instance->name = "TFDTP2NSP_TxPacketTask";
        taskParams.arg0 = (UArg)hTFDTP2NSP;
        hTFDTP2NSP->txPacketTask = Task_create(&LOCAL_tfdtpTxPacketTask, &taskParams, NULL);
        if (hTFDTP2NSP->txPacketTask == NULL) { goto teardown; }
    }

    /* Register a local function for 100ms-period callback */
    {
        GMACSW_TickFxnIoctlCmd cmd;

        cmd.pTickFxnCallback    = &LOCAL_pollingCallback;
        cmd.hTickFxnCallbackArg = (void *) hTFDTP2NSP;
        cmd.hRegisteredTickFxn  = &hTFDTP2NSP->hRegisteredTickFxn;

        GMACSW_ioctl(hTFDTP2NSP->hGMACSW,
                     GMACSW_IOCTL_REGISTER_TICK_FXN,
                     (void *)&cmd,
                     sizeof(GMACSW_TickFxnIoctlCmd));
        if (NULL == hTFDTP2NSP->hRegisteredTickFxn) { goto teardown; }

    }

    /* Queue up some Tx packets, that the alloc callback will use */
    LOCAL_allocTxPackets(hTFDTP2NSP);

    return hTFDTP2NSP;

teardown:
    TFDTP2NSP_close(hTFDTP2NSP);
    return NULL;
}

void TFDTP2NSP_close(TFDTP2NSP_Handle hTFDTP2NSP)
{
    if (hTFDTP2NSP == NULL) { return; }


    /* Stop activity for this stack */
    if (hTFDTP2NSP->hGMACSW)
    {
        if (hTFDTP2NSP->hTxChannel)
        {
            /* Stop the Tx Channel */
            GMACSW_ioctl(hTFDTP2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_STOP_TX_CHANNEL,
                        (void *)&hTFDTP2NSP->hTxChannel,
                        sizeof(CPDMA_ChannelHandle));
        }

        /* Set the translation layer shutDown flag */
        hTFDTP2NSP->shutDown = (bool)true;

        if (hTFDTP2NSP->hRegisteredTickFxn != NULL)
        {
            /* Unregister the 100ms-period callback */
            GMACSW_ioctl(hTFDTP2NSP->hGMACSW,
                         GMACSW_IOCTL_UNREGISTER_TICK_FXN,
                         (void *)&hTFDTP2NSP->hRegisteredTickFxn,
                         sizeof(GMACSW_RegisteredTickFxnHandle));
            hTFDTP2NSP->hRegisteredTickFxn = NULL;
        }

        if (hTFDTP2NSP->hTxChannel != NULL)
        {
            /* Close the Tx Channel */
            GMACSW_ioctl(hTFDTP2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_CLOSE_TX_CHANNEL,
                         (void *)&hTFDTP2NSP->hTxChannel,
                         sizeof(CPDMA_ChannelHandle));
            hTFDTP2NSP->hTxChannel = NULL;
        }

        /* Close reference to the GMACSW hardware driver */
        GMACSW_close(hTFDTP2NSP->hGMACSW);
    }

    /*
     * Wait for parser task to shutDown completely before deleting
     * any resources the task is using.
     */
    if (hTFDTP2NSP->shutDownSem != NULL)
    {
        if (hTFDTP2NSP->txPacketTask != NULL)
        {
            /* If we are tearing down because something failed during open, we need
             * to wake up the task so it exits normally.
             */
            Semaphore_post(hTFDTP2NSP->txPacketSem);
            Semaphore_pend(hTFDTP2NSP->shutDownSem, BIOS_WAIT_FOREVER);
        }
        Semaphore_delete(&hTFDTP2NSP->shutDownSem);
    }

    if (hTFDTP2NSP->txPacketFreeSem != NULL) { Semaphore_delete(&hTFDTP2NSP->txPacketFreeSem); }

    /*
     * We don't do task deletion since the NDK forces the
     * Task.deleteTerminatedTasks option be true, which means
     * the rxPacketTask and txPacketTask are auto-deleted.
     */

#if defined(NSP_DYNAMIC_ALLOCATION)
    free(hTFDTP2NSP);
#endif
}

void TFDTP2NSP_start(TFDTP2NSP_Handle hTFDTP2NSP)
{
    /* Start the Tx Channel */
    GMACSW_ioctl(hTFDTP2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_START_TX_CHANNEL,
                 (void *)&hTFDTP2NSP->hTxChannel,
                 sizeof(CPDMA_ChannelHandle));
}

void TFDTP2NSP_kickTx(TFDTP2NSP_Handle hTFDTP2NSP)
{
    Semaphore_post(hTFDTP2NSP->txPacketSem);
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static void LOCAL_closeTxChannel(void *hCallbackArg)
{
    TFDTP2NSP_Handle      hTFDTP2NSP = (TFDTP2NSP_Handle ) hCallbackArg;
    CPDMA_PacketQueue   tempQueue;

    /* Post to rx packet task so that it will terminate (shutDown flag is already set) */
    if (hTFDTP2NSP->txPacketTask != NULL)
    {
        Semaphore_post(hTFDTP2NSP->txPacketSem);
    }

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * being returned from the hardware.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hTFDTP2NSP->hTxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hTFDTP2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

#if (0)
    /* FIXME: The buffer descriptor free happens in the CPDMA channel close */
    uint32_t i;
    for (i = 0U; i < (uint32_t)TFDTP2NSP_TX_PACKETS; i++)
    {
        CPDMA_Packet *pCPDMAPacket = &hTFDTP2NSP->txPacketMem[i];
        CPDMA_freePacketBufferDescriptors(hTFDTP2NSP->hTxChannel, pCPDMAPacket);
    }
#endif
}

static void LOCAL_notifyTxPackets(void *hCallbackArg)
{
    TFDTP2NSP_Handle hTFDTP2NSP = (TFDTP2NSP_Handle)hCallbackArg;

    Semaphore_post(hTFDTP2NSP->txPacketSem);
}

static void LOCAL_tfdtpTxPacketTask(UArg arg0, UArg arg1)
{
    TFDTP2NSP_Handle hTFDTP2NSP = (TFDTP2NSP_Handle) arg0;
    CPDMA_PacketQueue tempQueue;
#if defined(TFDTP_INSTRUMENTATION_ENABLED)
    uint32_t time1 = 0;
    uint32_t packetCount = 0;
#endif

    while (!hTFDTP2NSP->shutDown)
    {
        /*
         * Wait for the Tx ISR to notify us that empty packets are available
         * that were used to send data
         */
        Semaphore_pend(hTFDTP2NSP->txPacketSem, BIOS_WAIT_FOREVER);
#if defined(TFDTP_INSTRUMENTATION_ENABLED)
        time1 = TIMER_READ();
        tfdtp2NspStats.txStats.rawNotificationCount++;
        packetCount = 0;
#endif

        /* Retrieve the used (sent/empty) packets from the channel */
        {
            CPDMA_RetrievePacketQueueIoctlCmd cmd;

            CPDMA_packetQueueInit(&tempQueue);

            cmd.hChannel                    = hTFDTP2NSP->hTxChannel;
            cmd.pFromChannelQueue           = &tempQueue;

            /* This function will initialize the tempQueue variable */
            GMACSW_ioctl(hTFDTP2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
        }

        if (tempQueue.count > 0)
        {
#if defined(TFDTP_INSTRUMENTATION_ENABLED)^M
            packetCount =
#endif
            LOCAL_prepTxPacketQueue(hTFDTP2NSP, &tempQueue);
        }

#if defined(TFDTP_INSTRUMENTATION_ENABLED)
        else
        {
            tfdtp2NspStats.rxStats.zeroNotificationCount++;
        }

        if (packetCount != 0)
        {
            uint32_t notificationCount;
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
            uint32_t timePerPacket = timeDiff/packetCount;
            Load_Stat loadStat;

            notificationCount = tfdtp2NspStats.txStats.dataNotificationCount & (HISTORY_CNT - 1);
            tfdtp2NspStats.txStats.dataNotificationCount++;

            tfdtp2NspStats.txStats.totalPacketCount += packetCount;
            tfdtp2NspStats.txStats.totalCycleCnt += timeDiff;

            tfdtp2NspStats.txStats.cycleCountPerNotification[notificationCount] = timeDiff;
            if (timeDiff > tfdtp2NspStats.txStats.cycleCountPerNotificationMax)
            {
                tfdtp2NspStats.txStats.cycleCountPerNotificationMax = timeDiff;
            }

            tfdtp2NspStats.txStats.packetsPerNotification[notificationCount] = packetCount;
            if (packetCount > tfdtp2NspStats.txStats.packetsPerNotificationMax)
            {
                tfdtp2NspStats.txStats.packetsPerNotificationMax = packetCount;
            }

            tfdtp2NspStats.txStats.cycleCountPerPacket[notificationCount] = timePerPacket;
            if (timePerPacket >tfdtp2NspStats.txStats.cycleCountPerPacketMax)
            {
                tfdtp2NspStats.txStats.cycleCountPerPacketMax = timePerPacket;
            }

            if (Load_getTaskLoad(Task_self(), &loadStat))
            {
                tfdtp2NspStats.txStats.taskLoad[notificationCount] = Load_calculateLoad(&loadStat);
            }
        }
#endif
        LOCAL_sendTxPackets(hTFDTP2NSP);
        TFDTP_fillTxQueue((tfdtp_handle_t)hTFDTP2NSP->config.clientData, &hTFDTP2NSP->txReadyTFDTPPacketQueue);
        LOCAL_sendTxPackets(hTFDTP2NSP);
    }

    /* We are shutting down, notify that we are done */
    Semaphore_post(hTFDTP2NSP->shutDownSem);
}

static void LOCAL_allocTxPackets(TFDTP2NSP_Handle hTFDTP2NSP)
{
    CPDMA_PacketQueue tempQueue;

    CPDMA_packetQueueInit(&tempQueue);

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * initially allocated by the channel open function.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hTFDTP2NSP->hTxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hTFDTP2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Go through the CPDMA packets in the queue, and move them to the
     * txFreeCPDMAPacketQueue so they are ready to be used when the stack
     * wants to send a packet
     */
    LOCAL_prepTxPacketQueue(hTFDTP2NSP, &tempQueue);
}

static uint32_t LOCAL_prepTxPacketQueue(TFDTP2NSP_Handle hTFDTP2NSP, CPDMA_PacketQueue *pPacketQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;

    uint32_t packetCount = 0;

    pCurrCPDMAPacket = pPacketQueue->pHead;
    while (pCurrCPDMAPacket)
    {
        TFDTP_TxPacket *hTFDTPPacket = (TFDTP_TxPacket *)pCurrCPDMAPacket->hPrivate;

        /* Free the packet - it was allocated by the stack/sender */
        if (hTFDTPPacket != NULL)
        {
            TFDTP_enqueue(hTFDTP2NSP->config.txFreeTFDTPPacketQueue, (node_t *)hTFDTPPacket);
            packetCount++;
            if (hTFDTPPacket->notifyFree)
            {
                hTFDTPPacket->txCbFxn(hTFDTPPacket->pAppTxBuf, hTFDTPPacket->txCbData,
                                    hTFDTPPacket->pAppTxBuf->hTfdtpTxCh->channelId);
                hTFDTPPacket->notifyFree = false;
            }
        }

        /* Unlink the packets' buffer descriptor queues as we go through them */
        pCurrCPDMAPacket->buffDescQueue.pTail->pNextBufferDescriptor = NULL;

        pCurrCPDMAPacket = pCurrCPDMAPacket->pNextPacket;
    }

    /* Attach the queue of packets being returned from the hardware to the free packet queue */
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        /* Moved the queue of packets into the txFreeCPDMAPacketQueue */
        CPDMA_appendPacketQueue(&hTFDTP2NSP->txFreeCPDMAPacketQueue, pPacketQueue);

#if defined(TFDTP_INSTRUMENTATION_ENABLED)
        tfdtp2NspStats.txFreeCPDMAPacketEnqueue += pPacketQueue->count;
#endif

        /* Clear the input queue */
        CPDMA_packetQueueInit(pPacketQueue);

        GMACSW_AL_globalInterruptEnable(key);
    }

    if (packetCount > 0)
    {
        Semaphore_post(hTFDTP2NSP->txPacketFreeSem);
    }

    return packetCount;
}

void LOCAL_sendTxPackets(TFDTP2NSP_Handle hTFDTP2NSP)
{
    CPDMA_Packet *pPrevCPDMAPacket = NULL;
    TFDTP_TxPacket *hTFDTPPacket;
    CPDMA_PacketQueue tempQueue;

    CPDMA_packetQueueInit(&tempQueue);

    /* If there is nothing queued to transmit, simply return */
    hTFDTPPacket = (TFDTP_TxPacket *)TFDTP_dequeue(&hTFDTP2NSP->txReadyTFDTPPacketQueue);
    while (NULL != hTFDTPPacket)
    {
        CPDMA_Packet *pCurrCPDMAPacket;

#if defined(NSP_INSTRUMENTATION_ENABLED)
        ndk2NspStats.txReadyPBMPacketDequeue[0U]++;
#endif

        /* Allocate a packet from the Tx CPDMA packet pool */
        pCurrCPDMAPacket = CPDMA_packetDequeue(&hTFDTP2NSP->txFreeCPDMAPacketQueue);
        if (NULL != pCurrCPDMAPacket)
        {
            /* Populate the packet and the buffer descriptor(s) it contains */
            CPDMA_BuffDesc      *pFirstBuffDesc = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);
            CPDMA_BuffDesc      *pLastBuffDesc = CPDMA_packetGetLastDesc(pCurrCPDMAPacket);
#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.txFreeCPDMAPacketDequeue++;
#endif
            /*
             * Save off the TFDTP packet handle so it can be freed when the CPDMA
             * packet is freed via the callback after it is transmitted
             */
            pCurrCPDMAPacket->hPrivate = (void *)hTFDTPPacket;

            CPDMA_setHardwareAsOwner(pFirstBuffDesc);
            CPDMA_setStartOfPacket  (pFirstBuffDesc);
            CPDMA_setDataBuffer     (pFirstBuffDesc, hTFDTPPacket->pHeader);
            CPDMA_setBufferLength   (pFirstBuffDesc, TFDTP_PACKET_HEADER_SIZE);
            CPDMA_setBufferOffset   (pFirstBuffDesc, 0);
            CPDMA_setPacketLength   (pFirstBuffDesc, hTFDTPPacket->bufferSize + TFDTP_PACKET_HEADER_SIZE);
            CPDMA_setDataBuffer     (pLastBuffDesc, hTFDTPPacket->dataPtr);
            CPDMA_setBufferLength   (pLastBuffDesc, hTFDTPPacket->bufferSize);
            CPDMA_setEndOfPacket    (pLastBuffDesc);
            CPDMA_clearEndOfQueue   (pLastBuffDesc);

            /* Link the packets' buffer descriptor queues as we go through them */
            if (pPrevCPDMAPacket)
            {
                pPrevCPDMAPacket->buffDescQueue.pTail->pNextBufferDescriptor = pFirstBuffDesc;
            }
            pPrevCPDMAPacket = pCurrCPDMAPacket;

            CPDMA_packetEnqueue(&tempQueue, pCurrCPDMAPacket);
        }
        else
        {
            /* Return the packet to the ready queue
             * as we couldn't allocate an associated CPDMA packet.
             * Do not free as its delivery should be postponed not dropped.
             */
            TFDTP_enqueueHead(&hTFDTP2NSP->txReadyTFDTPPacketQueue, (node_t *)hTFDTPPacket);
#if defined(TFDTP_INSTRUMENTATION_ENABLED)
            tfdtp2NspStats.txReadyTFDTPPacketEnqueue++;
#endif
            tfdtp2NspStats.txFreeCPDMAPacketUnderflow++;
            break;
        }
        hTFDTPPacket = (TFDTP_TxPacket *)TFDTP_dequeue(&hTFDTP2NSP->txReadyTFDTPPacketQueue);
    }

    /* Give the accumulated packets to the hardware */
    {
        CPDMA_SubmitPacketQueueIoctlCmd cmd;

        cmd.hChannel                    = hTFDTP2NSP->hTxChannel;
        cmd.pToChannelQueue             = &tempQueue;

        GMACSW_ioctl(hTFDTP2NSP->hGMACSW,
                    GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS,
                    (void *)&cmd,
                    sizeof(CPDMA_SubmitPacketQueueIoctlCmd));
    }
}

static void LOCAL_pollingCallback(void *hCallbackArg)
{
    static uint32_t loadCount = 0;
    Load_Stat stat;

    TFDTP2NSP_Handle hTFDTP2NSP = (TFDTP2NSP_Handle) hCallbackArg;

    if (Load_getTaskLoad(hTFDTP2NSP->txPacketTask, &stat))
    {
        tfdtp2NspStats.txStats.taskLoad[loadCount] = Load_calculateLoad(&stat);
    }

    loadCount = (loadCount+1U) & ((uint32_t)HISTORY_CNT - 1U);
}

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

