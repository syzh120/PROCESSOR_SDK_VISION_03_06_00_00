/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   null2nsp.c
 *
 *  \brief  Translation/adaptation layer between Null Stack and NSP.
 *
 */

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* OS/Posix headers */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/hal/Cache.h>

/* NSP Dependencies */
#include <ti/nsp/drv/inc/gmacsw.h>

/* Project dependency headers */
#include "null_stack.h"
//#include "null_stack_priv.h"

/* This module's header */
#include "null2nsp.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define BUFF_DESC_PER_PACKET        ((uint32_t)1U)

#define NULL_RX_PACKET_TASK_PRI      (14)
#define NULL_RX_PACKET_TASK_STACK    (2048)

#define NULL_TX_PACKET_TASK_PRI      (14)
#define NULL_TX_PACKET_TASK_STACK    (2048)

#define NULL_CPTS_EVENT_TASK_PRI     (14)
#define NULL_CPTS_EVENT_TASK_STACK   (2048)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static void LOCAL_closeRxChannel(void *hCallbackArg);
static void LOCAL_notifyRxPackets(void *hCallbackArg);
static void LOCAL_rxPacketTask(UArg arg0, UArg arg1);
static void LOCAL_allocRxPackets(NULL2NSP_Handle hNULL2NSP);
static uint32_t LOCAL_prepRxPacketQueue(NULL2NSP_Handle hNULL2NSP, CPDMA_PacketQueue *pPacketQueue);

static void LOCAL_closeTxChannel(void *hCallbackArg);
static void LOCAL_notifyTxPackets(void *hCallbackArg);
static void LOCAL_txPacketTask(UArg arg0, UArg arg1);
static void LOCAL_allocTxPackets(NULL2NSP_Handle hNULL2NSP);
static uint32_t LOCAL_prepTxPacketQueue(NULL2NSP_Handle hNULL2NSP, CPDMA_PacketQueue *pPacketQueue);

static void LOCAL_pollingCallback(void *hCallbackArg);


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NULL_DYNAMIC_ALLOCATION)
NULL2NSP_Object NULL2NSP_stateObj;
#endif


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

NULL2NSP_Stats null2NspStats;


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

NULL2NSP_Handle NULL2NSP_open(const NULL2NSP_Config *config)
{
    NULL2NSP_Handle hNULL2NSP;


    if (config == NULL) { return NULL; }

#if defined(NULL_INSTRUMENTATION_ENABLED)
    /* Clear instrumentation statistics structure */
    memset(&null2NspStats, 0, sizeof(NULL2NSP_Stats));
#endif

#if defined(NULL_DYNAMIC_ALLOCATION)
    hNULL2NSP = (NULL2NSP_Handle) calloc(1U, sizeof(NULL2NSP_Object));
    if (hNULL2NSP == NULL) return NULL;
#else
    hNULL2NSP = &NULL2NSP_stateObj;
    memset(hNULL2NSP, 0, sizeof(NULL2NSP_Object));
#endif

    /* Initialize the Rx Queues & Data */
    NULL_packetQueueInit(&hNULL2NSP->rxReadyNULLPacketQueue);
    NULL_packetQueueInit(&hNULL2NSP->rxFreeNULLPacketQueue);

    /* Initialize the Tx Queues & Data */
    NULL_packetQueueInit(&hNULL2NSP->txReadyNULLPacketQueue);
    CPDMA_packetQueueInit(&hNULL2NSP->txFreeCPDMAPacketQueue);

    /* Register this stack/translation layer's polling callback with the hardware driver */
    hNULL2NSP->hGMACSW = GMACSW_open(NULL);
    if (hNULL2NSP->hGMACSW == NULL) { goto teardown; }

    /* Save config info */
    memcpy(&hNULL2NSP->config, config, sizeof(NULL2NSP_Config));

    /* Open Rx Channel */
    {
        CPDMA_OpenRxChannelIoctlCmd cmd;
        CPDMA_RxChannelConfig       config;

        cmd.pRxChannelConfig                    = &config;
        cmd.pRxChannelHandle                    = &hNULL2NSP->hRxChannel;


        config.packetCount                      = NULL2NSP_RX_PACKETS;
        config.buffersPerPacketCount            = BUFF_DESC_PER_PACKET;
        config.packetMem                        = (void *) hNULL2NSP->rxPacketMem;
        config.rxThreshCount                    = (NULL2NSP_RX_PACKETS * BUFF_DESC_PER_PACKET * 3U) / 8U; /* Set threshold at 37.5% of total */
        config.callbacks.pFxnCbCloseChannel     = &LOCAL_closeRxChannel;
        config.callbacks.pFxnCbUsedPacketNotify = &LOCAL_notifyRxPackets;
        config.callbacks.hCallbackArg           = (void *) hNULL2NSP;

        GMACSW_ioctl(hNULL2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_OPEN_RX_CHANNEL,
                     (void *)&cmd,
                     sizeof(CPDMA_OpenRxChannelIoctlCmd));
        if (NULL == hNULL2NSP->hRxChannel) { goto teardown; }
    }

    /* Setup Rx priority mapping */
    {
        PORT_AddRxPriorityMappingIoctlCmd   cmd;
        PORT_RxPriorityConfig               config;

        cmd.pPriConfig                                  = &config;
        cmd.pRxPriorityMapHandle                        = &hNULL2NSP->hRxPriorityMap;

        config.hCpdmaRxChannel                          = hNULL2NSP->hRxChannel;
        config.switchPriority                           = PORT_SWITCH_PRIORITY_HIGH;
        config.rxSource                                 = PORT_RX_SOURCE_MAC_BOTH;
        config.rxPriorityType                           = PORT_RX_PRIORITY_TYPE_VLAN_TAGGED;
        config.rxPriorityOption.vlanTagged.priority     = NULL_VLAN_PRIORITY;
        config.rxPriorityOption.vlanTagged.vlanID       = NULL_VLAN_ID;

        GMACSW_ioctl(hNULL2NSP->hGMACSW,
                     GMACSW_IOCTL_PORT_ADD_RX_PRIORITY_MAPPING,
                     (void *)&cmd,
                     sizeof(PORT_AddRxPriorityMappingIoctlCmd));
        if (NULL == hNULL2NSP->hRxPriorityMap) { goto teardown; }
    }

    /* Open Tx Channel */
    {
        CPDMA_OpenTxChannelIoctlCmd cmd;
        CPDMA_TxChannelConfig       config;

        cmd.pTxChannelConfig                    = &config;
        cmd.pTxChannelHandle                    = &hNULL2NSP->hTxChannel;

        config.packetCount                      = NULL2NSP_TX_PACKETS;
        config.buffersPerPacketCount            = BUFF_DESC_PER_PACKET;
        config.packetMem                        = (void *) hNULL2NSP->txPacketMem;
        config.callbacks.pFxnCbCloseChannel     = &LOCAL_closeTxChannel;
        config.callbacks.pFxnCbUsedPacketNotify = &LOCAL_notifyTxPackets;
        config.callbacks.hCallbackArg           = (void *) hNULL2NSP;

        GMACSW_ioctl(hNULL2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_OPEN_TX_CHANNEL,
                     (void *)&cmd,
                     sizeof(CPDMA_OpenTxChannelIoctlCmd));
        if (NULL == hNULL2NSP->hTxChannel) { goto teardown; }
    }

    /* Create semaphore objects, init shutDown status */
    {
        Semaphore_Params semParams;

        hNULL2NSP->shutDown = (uint32_t)false;

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_COUNTING;
        hNULL2NSP->shutDownSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hNULL2NSP->shutDownSem) { goto teardown; }

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        hNULL2NSP->rxPacketSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hNULL2NSP->rxPacketSem) { goto teardown; }

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        hNULL2NSP->txPacketSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hNULL2NSP->txPacketSem) { goto teardown; }
    }

    /* Start the packet processing tasks now that the channels are open */
    {
        Task_Params taskParams;

        Task_Params_init(&taskParams);
        taskParams.stackSize = NULL_RX_PACKET_TASK_STACK;
        taskParams.priority = NULL_RX_PACKET_TASK_PRI;
        taskParams.instance->name = "NULL2NSP_RxPacketTask";
        taskParams.arg0 = (UArg)hNULL2NSP;
        hNULL2NSP->rxPacketTask = Task_create(&LOCAL_rxPacketTask, &taskParams, NULL);
        if (hNULL2NSP->rxPacketTask == NULL) { goto teardown; }

        Task_Params_init(&taskParams);
        taskParams.stackSize = NULL_TX_PACKET_TASK_STACK;
        taskParams.priority = NULL_TX_PACKET_TASK_PRI;
        taskParams.instance->name = "NULL2NSP_TxPacketTask";
        taskParams.arg0 = (UArg)hNULL2NSP;
        hNULL2NSP->txPacketTask = Task_create(&LOCAL_txPacketTask, &taskParams, NULL);
        if (hNULL2NSP->txPacketTask == NULL) { goto teardown; }
    }

    /* Register a local function for 100ms-period callback */
    {
        GMACSW_TickFxnIoctlCmd cmd;

        cmd.pTickFxnCallback    = &LOCAL_pollingCallback;
        cmd.hTickFxnCallbackArg = (void *) hNULL2NSP;
        cmd.hRegisteredTickFxn  = &hNULL2NSP->hRegisteredTickFxn;

        GMACSW_ioctl(hNULL2NSP->hGMACSW,
                     GMACSW_IOCTL_REGISTER_TICK_FXN,
                     (void *)&cmd,
                     sizeof(GMACSW_TickFxnIoctlCmd));
        if (NULL == hNULL2NSP->hRegisteredTickFxn) { goto teardown; }

    }

    /* Queue up some Rx packets, that the alloc callback will use */
    LOCAL_allocRxPackets(hNULL2NSP);

    /* Queue up some Tx packets, that the alloc callback will use */
    LOCAL_allocTxPackets(hNULL2NSP);

    /* Start the Rx Channel */
    GMACSW_ioctl(hNULL2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_START_RX_CHANNEL,
                 (void *)&hNULL2NSP->hRxChannel,
                 sizeof(CPDMA_ChannelHandle));

    /* Start the Tx Channel */
    GMACSW_ioctl(hNULL2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_START_TX_CHANNEL,
                 (void *)&hNULL2NSP->hTxChannel,
                 sizeof(CPDMA_ChannelHandle));

    return hNULL2NSP;

teardown:
    NULL2NSP_close(hNULL2NSP);
    return NULL;
}

void NULL2NSP_close(NULL2NSP_Handle hNULL2NSP)
{
    if (hNULL2NSP == NULL) { return; }

    /* Set the translation layer shutDown flag */
    hNULL2NSP->shutDown = (uint32_t)true;

    /* Stop activity for this stack */
    if (hNULL2NSP->hGMACSW)
    {
        if (hNULL2NSP->hTxChannel)
        {
            /* Stop the Tx Channel */
            GMACSW_ioctl(hNULL2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_STOP_TX_CHANNEL,
                        (void *)&hNULL2NSP->hTxChannel,
                        sizeof(CPDMA_ChannelHandle));
        }

        if (hNULL2NSP->hRxChannel)
        {
            /* Stop the Rx Channel */
            GMACSW_ioctl(hNULL2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_STOP_RX_CHANNEL,
                        (void *)&hNULL2NSP->hRxChannel,
                        sizeof(CPDMA_ChannelHandle));
        }

        if (hNULL2NSP->hRegisteredTickFxn != NULL)
        {
            /* Unregister the 100ms-period callback */
            GMACSW_ioctl(hNULL2NSP->hGMACSW,
                         GMACSW_IOCTL_UNREGISTER_TICK_FXN,
                         (void *)&hNULL2NSP->hRegisteredTickFxn,
                         sizeof(GMACSW_RegisteredTickFxnHandle));
            hNULL2NSP->hRegisteredTickFxn = NULL;
        }

        if (hNULL2NSP->hTxChannel != NULL)
        {
            /* Close the Tx Channel */
            GMACSW_ioctl(hNULL2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_CLOSE_TX_CHANNEL,
                         (void *)&hNULL2NSP->hTxChannel,
                         sizeof(CPDMA_ChannelHandle));
            hNULL2NSP->hTxChannel = NULL;
        }

        if (hNULL2NSP->hRxPriorityMap != NULL)
        {
            /* Remove the priority mapping */
            GMACSW_ioctl(hNULL2NSP->hGMACSW,
                         GMACSW_IOCTL_PORT_REMOVE_RX_PRIORITY_MAPPING,
                         (void *) &hNULL2NSP->hRxPriorityMap,
                         sizeof(PORT_RxPriorityMapHandle));
            hNULL2NSP->hRxPriorityMap = NULL;
        }

        if (hNULL2NSP->hRxChannel != NULL)
        {
            /* Close the Rx Channel */
            GMACSW_ioctl(hNULL2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_CLOSE_RX_CHANNEL,
                         (void *)&hNULL2NSP->hRxChannel,
                         sizeof(CPDMA_ChannelHandle));
            hNULL2NSP->hRxChannel = NULL;
        }

        /* Close reference to the GMACSW hardware driver */
        GMACSW_close(hNULL2NSP->hGMACSW);
    }

    /*
     * Wait for parser task to shutDown completely before deleting
     * any resources the task is using.
     */
    if (hNULL2NSP->shutDownSem != NULL)
    {
        if (hNULL2NSP->rxPacketTask != NULL)
        {
            /* If we are tearing down because something failed during open, we need
             * to wake up the task so it exits normally.
             */
            Semaphore_post(hNULL2NSP->rxPacketSem);
            Semaphore_pend(hNULL2NSP->shutDownSem, BIOS_WAIT_FOREVER);
        }
        if (hNULL2NSP->txPacketTask != NULL)
        {
            /* If we are tearing down because something failed during open, we need
             * to wake up the task so it exits normally.
             */
            Semaphore_post(hNULL2NSP->txPacketSem);
            Semaphore_pend(hNULL2NSP->shutDownSem, BIOS_WAIT_FOREVER);
        }
        Semaphore_delete(&hNULL2NSP->shutDownSem);
    }

    if (hNULL2NSP->rxPacketSem != NULL) { Semaphore_delete(&hNULL2NSP->rxPacketSem); }
    if (hNULL2NSP->txPacketSem != NULL) { Semaphore_delete(&hNULL2NSP->txPacketSem); }

    /*
     * We don't do task deletion since the NDK forces the
     * Task.deleteTerminatedTasks option be true, which means
     * the rxPacketTask and txPacketTask are auto-deleted.
     */

#if defined(NULL_DYNAMIC_ALLOCATION)
    free(hNULL2NSP);
#endif
}

void NULL2NSP_sendTxPackets(NULL2NSP_Handle hNULL2NSP)
{
    CPDMA_Packet *pPrevCPDMAPacket = NULL;
    NULL_Packet *hNULLPacket;
    CPDMA_PacketQueue tempQueue;

    CPDMA_packetQueueInit(&tempQueue);

    /* If there is nothing queued to transmit, simply return */
    hNULLPacket = NULL_packetDequeue(&hNULL2NSP->txReadyNULLPacketQueue);
    while (NULL != hNULLPacket)
    {
        CPDMA_Packet *pCurrCPDMAPacket;

        /* Allocate a packet from the Tx CPDMA packet pool */
        pCurrCPDMAPacket = CPDMA_packetDequeue(&hNULL2NSP->txFreeCPDMAPacketQueue);
        if (NULL != pCurrCPDMAPacket)
        {
            /* Populate the packet and the buffer descriptor(s) it contains */
            CPDMA_BuffDesc      *pFirstBuffDesc = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);
            CPDMA_BuffDesc      *pLastBuffDesc = CPDMA_packetGetLastDesc(pCurrCPDMAPacket);

            /*
             * Save off the NULL packet handle so it can be freed when the CPDMA
             * packet is freed via the callback after it is transmitted
             */
            pCurrCPDMAPacket->hPrivate = (void *)hNULLPacket;

            CPDMA_setHardwareAsOwner(pFirstBuffDesc);
            CPDMA_setStartOfPacket  (pFirstBuffDesc);
            CPDMA_setDataBuffer     (pFirstBuffDesc, hNULLPacket->pBuffer);
            CPDMA_setBufferLength   (pFirstBuffDesc, hNULLPacket->bufferSize);
            CPDMA_setBufferOffset   (pFirstBuffDesc, 0);
            CPDMA_setPacketLength   (pFirstBuffDesc, hNULLPacket->bufferSize);
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
            /* Free the packet as we couldn't allocate an associated CPDMA packet */
            NULL_packetFree(hNULLPacket);
        }
        hNULLPacket = NULL_packetDequeue(&hNULL2NSP->txReadyNULLPacketQueue);
    }

    /* Give the accumulated packets to the hardware */
    {
        CPDMA_SubmitPacketQueueIoctlCmd cmd;

        cmd.hChannel                    = hNULL2NSP->hTxChannel;
        cmd.pToChannelQueue             = &tempQueue;

        GMACSW_ioctl(hNULL2NSP->hGMACSW,
                    GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS,
                    (void *)&cmd,
                    sizeof(CPDMA_SubmitPacketQueueIoctlCmd));
    }
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static void LOCAL_closeRxChannel(void *hCallbackArg)
{
    CPDMA_PacketQueue tempQueue;
    CPDMA_Packet *pCurrCPDMAPacket;
    uint32_t i;
    NULL2NSP_Handle hNULL2NSP = (NULL2NSP_Handle) hCallbackArg;

    /* Post to rx packet task so that it will terminate (shutDown flag is already set) */
    if (hNULL2NSP->rxPacketTask != NULL)
    {
        Semaphore_post(hNULL2NSP->rxPacketSem);
    }

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * being returned from the hardware.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNULL2NSP->hRxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNULL2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Take all NULL packets from the fromHardware queue and put them on the
     * rxFreePBMPacketQueue.
     */
    pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the NULL packets that need to be freed */
        NULL_Packet *hNULLPacket = (NULL_Packet *) pCurrCPDMAPacket->hPrivate;

        if (hNULLPacket)
        {
            NULL_packetEnqueue(&hNULL2NSP->rxFreeNULLPacketQueue, hNULLPacket);
        }
        pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    }

    /* Free all NULL packets (this should be all of them) */
    for (i = 0U; i < ((uint32_t)NULL2NSP_RX_PACKETS*(uint32_t)2U); i++)
    {
        NULL_Packet *hNULLPacket = NULL_packetDequeue(&hNULL2NSP->rxFreeNULLPacketQueue);
        if (hNULLPacket != NULL)
        {
            NULL_packetFree(hNULLPacket);
        }
    }
}

static void LOCAL_notifyRxPackets(void *hCallbackArg)
{
    NULL2NSP_Handle hNULL2NSP = (NULL2NSP_Handle) hCallbackArg;

    Semaphore_post(hNULL2NSP->rxPacketSem);
}

static void LOCAL_rxPacketTask(UArg arg0, UArg arg1)
{
    NULL2NSP_Handle hNULL2NSP = (NULL2NSP_Handle)arg0;
    CPDMA_PacketQueue tempQueue;
#if defined(NULL_INSTRUMENTATION_ENABLED)
    uint32_t time1 = 0;
    uint32_t packetCount = 0;
#endif

    while (!hNULL2NSP->shutDown)
    {
        /* Wait for the Rx ISR to notify us that packets are available with data */
        Semaphore_pend(hNULL2NSP->rxPacketSem, BIOS_WAIT_FOREVER);

#if defined(NULL_INSTRUMENTATION_ENABLED)
        time1 = TIMER_READ();
        null2NspStats.rxStats.rawNotificationCount++;
        packetCount = 0;
#endif

        /* Retrieve the used (filled) packets from the channel */
        {
            CPDMA_RetrievePacketQueueIoctlCmd cmd;

            CPDMA_packetQueueInit(&tempQueue);

            cmd.hChannel                    = hNULL2NSP->hRxChannel;
            cmd.pFromChannelQueue           = &tempQueue;

            /* This function will initialize the tempQueue variable */
            GMACSW_ioctl(hNULL2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
        }

        if (tempQueue.count != 0U)
        {
            /*
             * Get all used Rx CPDMA packets from the hardware, then send the buffers
             * of those packets on to the NULL stack to be parsed/processed.
             */
#if defined(NULL_INSTRUMENTATION_ENABLED)
            packetCount =
#endif
            LOCAL_prepRxPacketQueue(hNULL2NSP, &tempQueue);
        }
#if defined(NULL_INSTRUMENTATION_ENABLED)
        else
        {
            null2NspStats.rxStats.zeroNotificationCount++;
        }

        /*
         * We don't want to time the semaphore post used to notify the NULL stack as that may cause
         * task transition. We don't want to time the semaphore pend, since that would be us doing
         * nothing but waiting.
         */
        if (packetCount != 0)
        {
            uint32_t notificationCount;
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
            uint32_t timePerPacket = timeDiff/packetCount;
            Load_Stat loadStat;

            notificationCount = null2NspStats.rxStats.dataNotificationCount & (HISTORY_CNT - 1);
            null2NspStats.rxStats.dataNotificationCount++;

            null2NspStats.rxStats.totalPacketCount += packetCount;
            null2NspStats.rxStats.totalCycleCnt += timeDiff;

            null2NspStats.rxStats.cycleCountPerNotification[notificationCount] = timeDiff;
            if (timeDiff > null2NspStats.rxStats.cycleCountPerNotificationMax)
            {
                null2NspStats.rxStats.cycleCountPerNotificationMax = timeDiff;
            }

            null2NspStats.rxStats.packetsPerNotification[notificationCount] = packetCount;
            if (packetCount > null2NspStats.rxStats.packetsPerNotificationMax)
            {
                null2NspStats.rxStats.packetsPerNotificationMax = packetCount;
            }

            null2NspStats.rxStats.cycleCountPerPacket[notificationCount] = timePerPacket;
            if (timePerPacket >null2NspStats.rxStats.cycleCountPerPacketMax)
            {
                null2NspStats.rxStats.cycleCountPerPacketMax = timePerPacket;
            }

            if (Load_getTaskLoad(Task_self(), &loadStat))
            {
                null2NspStats.rxStats.taskLoad[notificationCount] = Load_calculateLoad(&loadStat);
            }
        }
#endif
        if (hNULL2NSP->rxReadyNULLPacketQueue.count != 0)
        {
            /* A function pointer could be used here - but a direct call is used instead
             * so a link-time optimization can occur
             */
            NULL_processRxPackets((NULL_Handle) hNULL2NSP->config.clientData);
        }
    }

    /* We are shutting down, notify that we are done */
    Semaphore_post(hNULL2NSP->shutDownSem);
}

static void LOCAL_allocRxPackets(NULL2NSP_Handle hNULL2NSP)
{
    CPDMA_PacketQueue tempQueue;
    uint32_t i;

    /*
     * Pre-allocate twice as many NULL stack packets as we plan to give to/get from the hardware.
     * The idea here is that even if we fill up all the buffer descriptors in the active
     * queue, we will have another complete set to swap in right away.
     */
    for (i = 0U; i < ((uint32_t)NULL2NSP_RX_PACKETS*(uint32_t)2U); i++)
    {
        NULL_Packet *hNULLPacket = NULL_packetAlloc(DEFAULT_PACKET_SIZE);
        if (hNULLPacket != NULL)
        {
            /* Enqueue to the free queue */
            NULL_packetEnqueue(&hNULL2NSP->rxFreeNULLPacketQueue, hNULLPacket);
#if defined(NULL_INSTRUMENTATION_ENABLED)
            null2NspStats.rxFreeNULLPacketEnqueue++;
#endif
        }
    }

    /*
     * Get the contents of the fromHardware queue, which should contain all packets
     * initially allocated by the channel open function.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNULL2NSP->hRxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNULL2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Go through packets in the queue, prep them to give to the
     * CPDMA Rx channel, then submit them to the channel
     */
    LOCAL_prepRxPacketQueue(hNULL2NSP, &tempQueue);
}

static uint32_t LOCAL_prepRxPacketQueue(NULL2NSP_Handle hNULL2NSP, CPDMA_PacketQueue *pPacketQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;
    CPDMA_Packet *pNextCPDMAPacket;

    uint32_t packetCount = 0;

    if (pPacketQueue->count > hNULL2NSP->rxFreeNULLPacketQueue.count)
    {
        printf("ERROR! CPDMA packets to free=%d > NULL packets available=%d\n",pPacketQueue->count,hNULL2NSP->rxFreeNULLPacketQueue.count);

        exit(-1);
    }

    /*
     * Get all used Rx CPDMA packets from the hardware, then send the buffers
     * of those packets on to the NULL stack to be parsed/processed.
     */
    pCurrCPDMAPacket = pPacketQueue->pHead;
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the full NULL packet that needs to be returned to the NULL stack */
        NULL_Packet *hNULLPacket = (NULL_Packet *) pCurrCPDMAPacket->hPrivate;

        if (hNULLPacket != NULL)
        {
            /* Fill in the packet size as returned by the hardware */
            hNULLPacket->bufferSize = CPDMA_packetGetLength(pCurrCPDMAPacket);

            /* Enqueue the receive packet so that it can be consumed by the NULL layer */
            NULL_packetEnqueue(&hNULL2NSP->rxReadyNULLPacketQueue, hNULLPacket);

#if defined(NULL_INSTRUMENTATION_ENABLED)
            null2NspStats.rxReadyNULLPacketEnqueue++;
#endif
            packetCount++;
        }

        /* Dequeue an empty NULL packet to be associated with a CPDMA packet for the hardware */
        hNULLPacket = NULL_packetDequeue(&hNULL2NSP->rxFreeNULLPacketQueue);
        if (hNULLPacket != NULL)
        {
#if defined(NULL_INSTRUMENTATION_ENABLED)
            null2NspStats.rxFreeNULLPacketDequeue++;
#endif
            /* Each CPDMA packet has only one buffer descriptor */
            CPDMA_BuffDesc *pBuffDesc   = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);

            /* Save off the NULL packet handle so it can be handled by the NULL stack later */
            pCurrCPDMAPacket->hPrivate = (void *)hNULLPacket;

            /* Mark the packet as owned by the hardware */
            pBuffDesc->pDataBuffer              = hNULLPacket->pBuffer;
            pBuffDesc->bufferOffsetAndLength    = DEFAULT_PACKET_SIZE;
            pBuffDesc->flagsAndPacketLength     = CPDMA_BUF_DESC_OWNER_FLAG;

#if (0)
            /* Pre-invalidate the data buffer so we don't need to do it on reception*/
            Cache_inv((Ptr)hNULLPacket->pBuffer,
                      (SizeT)DEFAULT_PACKET_SIZE,
                      (Bits16)Cache_Type_ALLD,
                      (Bool)1U);
#endif

            /* Link the packets' buffer descriptor queues as we go through them */
            pNextCPDMAPacket = pCurrCPDMAPacket->pNextPacket;
            if (pNextCPDMAPacket != NULL)
            {
                pBuffDesc->pNextBufferDescriptor = pNextCPDMAPacket->buffDescQueue.pHead;
            }
            else
            {
                pBuffDesc->pNextBufferDescriptor = NULL;
            }
            pCurrCPDMAPacket = pNextCPDMAPacket;
        }
        else
        {
            pCurrCPDMAPacket = NULL;
        }
    }

    /* Return same CPDMA packets back to the CPDMA channel */
    {
        CPDMA_SubmitPacketQueueIoctlCmd cmd;

        cmd.hChannel                    = hNULL2NSP->hRxChannel;
        cmd.pToChannelQueue             = pPacketQueue;

        GMACSW_ioctl(hNULL2NSP->hGMACSW,
                    GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS,
                    (void *)&cmd,
                    sizeof(CPDMA_SubmitPacketQueueIoctlCmd));
    }

    return packetCount;
}

static void LOCAL_closeTxChannel(void *hCallbackArg)
{
    NULL2NSP_Handle hNULL2NSP = (NULL2NSP_Handle ) hCallbackArg;
    CPDMA_PacketQueue tempQueue;
    CPDMA_Packet *pCurrCPDMAPacket;

    /* Post to rx packet task so that it will terminate (shutDown flag is already set) */
    if (hNULL2NSP->txPacketTask != NULL)
    {
        Semaphore_post(hNULL2NSP->txPacketSem);
    }

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * being returned from the hardware.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNULL2NSP->hTxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNULL2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Take all CPDMA packets from the fromHardware queue and free any
     * attached NULL packets.
     */
    pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the PBM packets that need to be freed */
        NULL_Packet *hNULLPacket = (NULL_Packet *) pCurrCPDMAPacket->hPrivate;

        if (hNULLPacket)
        {
            NULL_packetFree(hNULLPacket);
        }
        pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    }
}

static void LOCAL_notifyTxPackets(void *hCallbackArg)
{
    NULL2NSP_Handle hNULL2NSP = (NULL2NSP_Handle)hCallbackArg;

    Semaphore_post(hNULL2NSP->txPacketSem);
}

static void LOCAL_txPacketTask(UArg arg0, UArg arg1)
{
    NULL2NSP_Handle hNULL2NSP = (NULL2NSP_Handle) arg0;
    CPDMA_PacketQueue tempQueue;
#if defined(NULL_INSTRUMENTATION_ENABLED)
    uint32_t time1 = 0;
    uint32_t packetCount = 0;
#endif

    while (!hNULL2NSP->shutDown)
    {
        /*
         * Wait for the Tx ISR to notify us that empty packets are available
         * that were used to send data
         */
        Semaphore_pend(hNULL2NSP->txPacketSem, BIOS_WAIT_FOREVER);
#if defined(NULL_INSTRUMENTATION_ENABLED)
        time1 = TIMER_READ();
        null2NspStats.txStats.rawNotificationCount++;
        packetCount = 0;
#endif

        /* Retrieve the used (sent/empty) packets from the channel */
        {
            CPDMA_RetrievePacketQueueIoctlCmd cmd;

            CPDMA_packetQueueInit(&tempQueue);

            cmd.hChannel                    = hNULL2NSP->hTxChannel;
            cmd.pFromChannelQueue           = &tempQueue;

            /* This function will initialize the tempQueue variable */
            GMACSW_ioctl(hNULL2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
        }

        if (tempQueue.count > 0)
        {
#if defined(NULL_INSTRUMENTATION_ENABLED)
            packetCount =
#endif
            LOCAL_prepTxPacketQueue(hNULL2NSP, &tempQueue);
        }
#if defined(NULL_INSTRUMENTATION_ENABLED)
        else
        {
            null2NspStats.rxStats.zeroNotificationCount++;
        }

        if (packetCount != 0)
        {
            uint32_t notificationCount;
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
            uint32_t timePerPacket = timeDiff/packetCount;
            Load_Stat loadStat;

            notificationCount = null2NspStats.rxStats.dataNotificationCount & (HISTORY_CNT - 1);
            null2NspStats.txStats.dataNotificationCount++;

            null2NspStats.txStats.totalPacketCount += packetCount;
            null2NspStats.txStats.totalCycleCnt += timeDiff;

            null2NspStats.txStats.cycleCountPerNotification[notificationCount] = timeDiff;
            if (timeDiff > null2NspStats.txStats.cycleCountPerNotificationMax)
            {
                null2NspStats.txStats.cycleCountPerNotificationMax = timeDiff;
            }

            null2NspStats.txStats.packetsPerNotification[notificationCount] = packetCount;
            if (packetCount > null2NspStats.txStats.packetsPerNotificationMax)
            {
                null2NspStats.txStats.packetsPerNotificationMax = packetCount;
            }

            null2NspStats.txStats.cycleCountPerPacket[notificationCount] = timePerPacket;
            if (timePerPacket >null2NspStats.txStats.cycleCountPerPacketMax)
            {
                null2NspStats.txStats.cycleCountPerPacketMax = timePerPacket;
            }

            if (Load_getTaskLoad(Task_self(), &loadStat))
            {
                null2NspStats.txStats.taskLoad[notificationCount] = Load_calculateLoad(&loadStat);
            }
        }
#endif
    }

    /* We are shutting down, notify that we are done */
    Semaphore_post(hNULL2NSP->shutDownSem);
}

static void LOCAL_allocTxPackets(NULL2NSP_Handle hNULL2NSP)
{
    CPDMA_PacketQueue tempQueue;

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * initially allocated by the channel open function.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNULL2NSP->hTxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNULL2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Go through the CPDMA packets in the queue, and move them to the
     * txFreeCPDMAPacketQueue so they are ready to be used when the stack
     * wants to send a packet
     */
    LOCAL_prepTxPacketQueue(hNULL2NSP, &tempQueue);
}

static uint32_t LOCAL_prepTxPacketQueue(NULL2NSP_Handle hNULL2NSP, CPDMA_PacketQueue *pPacketQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;

    uint32_t packetCount = 0;

    pCurrCPDMAPacket = pPacketQueue->pHead;
    while (pCurrCPDMAPacket)
    {
        NULL_Packet *hNULLPacket = (NULL_Packet *)pCurrCPDMAPacket->hPrivate;

        /* Free the packet - it was allocated by the stack/sender */
        if (hNULLPacket != NULL)
        {
            NULL_packetFree(hNULLPacket);
            packetCount++;
        }

        /* Unlink the packets' buffer descriptor queues as we go through them */
        pCurrCPDMAPacket->buffDescQueue.pTail->pNextBufferDescriptor = NULL;

        pCurrCPDMAPacket = pCurrCPDMAPacket->pNextPacket;
    }

    /* Attach the queue of packets being returned from the hardware to the free packet queue */
    {
        uint32_t key = GMACSW_AL_globalInterruptDisable();

        /* Moved the queue of packets into the txFreeCPDMAPacketQueue */
        CPDMA_appendPacketQueue(&hNULL2NSP->txFreeCPDMAPacketQueue, pPacketQueue);

#if defined(NULL_INSTRUMENTATION_ENABLED)
        null2NspStats.txFreeCPDMAPacketEnqueue += pPacketQueue->count;
#endif

        /* Clear the input queue */
        CPDMA_packetQueueInit(pPacketQueue);

        GMACSW_AL_globalInterruptEnable(key);
    }

    return packetCount;
}

static void LOCAL_pollingCallback(void *hCallbackArg)
{
    static uint32_t loadCount = 0;
    Load_Stat stat;

    NULL2NSP_Handle hNULL2NSP = (NULL2NSP_Handle) hCallbackArg;

    if (Load_getTaskLoad(hNULL2NSP->rxPacketTask, &stat))
    {
        null2NspStats.rxStats.taskLoad[loadCount] = Load_calculateLoad(&stat);
    }
    if (Load_getTaskLoad(hNULL2NSP->txPacketTask, &stat))
    {
        null2NspStats.txStats.taskLoad[loadCount] = Load_calculateLoad(&stat);
    }

    loadCount = (loadCount+1U) & ((uint32_t)HISTORY_CNT - 1U);
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

