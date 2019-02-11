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
 *  \file   avb2nsp.c
 *
 *  \brief  Translation/adaptation layer between AVBTP and NSP.
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
#include "avbtp.h"
#include "avbtp_priv.h"

/* This module's header */
#include "avb2nsp.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define RX_BUFF_DESC_PER_PACKET     ((uint32_t)1U)
#define TX_BUFF_DESC_PER_PACKET     ((uint32_t)2U)

#define AVB_RX_PACKET_TASK_PRI      (10)
#define AVB_RX_PACKET_TASK_STACK    (2048)

#define AVB_TX_PACKET_TASK_PRI      (14)
#define AVB_TX_PACKET_TASK_STACK    (2048)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static void LOCAL_closeRxChannel(void *hCallbackArg);
static void LOCAL_notifyRxPackets(void *hCallbackArg);
static void LOCAL_avbRxPacketTask(UArg arg0, UArg arg1);
static void LOCAL_allocRxPackets(AVB2NSP_Handle hAVB2NSP);
static uint32_t LOCAL_prepRxPacketQueue(AVB2NSP_Handle hAVB2NSP, CPDMA_PacketQueue *pPacketQueue);

static void LOCAL_closeTxChannel(void *hCallbackArg);
static void LOCAL_notifyTxPackets(void *hCallbackArg);
static void LOCAL_avbTxPacketTask(UArg arg0, UArg arg1);
static void LOCAL_allocTxPackets(AVB2NSP_Handle hAVB2NSP);
static uint32_t LOCAL_prepTxPacketQueue(AVB2NSP_Handle hAVB2NSP, CPDMA_PacketQueue *pPacketQueue);
static void LOCAL_sendTxPackets(AVB2NSP_Handle hAVB2NSP);

static void LOCAL_pollingCallback(void *hCallbackArg);


/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/
#if !defined(AVB_DYNAMIC_ALLOCATION)
AVB2NSP_Object AVB2NSP_stateObj;
#endif

/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

AVB2NSP_Stats avb2NspStats;


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

AVB2NSP_Handle AVB2NSP_open(const AVB2NSP_Config *config)
{
    AVB2NSP_Handle hAVB2NSP;

    if (config == NULL) { return NULL; }

    /* Clear instrumentation statistics structure */
    memset(&avb2NspStats, 0, sizeof(AVB2NSP_Stats));

#if defined(AVB_DYNAMIC_ALLOCATION)
    hAVB2NSP = (AVB2NSP_Handle)calloc(1, sizeof(AVB2NSP_Object));
    if (hAVB2NSP == NULL) return NULL;
#else
    hAVB2NSP = &AVB2NSP_stateObj;
    memset(hAVB2NSP, 0, sizeof(AVB2NSP_Object));
#endif

    /* Initialize the Rx Queues & Data */
    AVBTP_queueInit(&hAVB2NSP->rxReadyAVBTPPacketQueue);

    /* Initialize the Tx Queues & Data */
    AVBTP_queueInit(&hAVB2NSP->txReadyAVBTPPacketQueue);
    CPDMA_packetQueueInit(&hAVB2NSP->txFreeCPDMAPacketQueue);

    /* Register this stack/translation layer's polling callback with the hardware driver */
    hAVB2NSP->hGMACSW = GMACSW_open(NULL);
    if (NULL == hAVB2NSP->hGMACSW) { goto teardown; }

    /* Save config info */
    memcpy(&hAVB2NSP->config, config, sizeof(AVB2NSP_Config));

    /* Open Rx Channel */
    {
        CPDMA_OpenRxChannelIoctlCmd cmd;
        CPDMA_RxChannelConfig       chanConfig;

        cmd.pRxChannelConfig                        = &chanConfig;
        cmd.pRxChannelHandle                        = &hAVB2NSP->hRxChannel;

        chanConfig.packetCount                      = (uint32_t)AVB2NSP_RX_PACKETS;
        chanConfig.buffersPerPacketCount            = (uint32_t)RX_BUFF_DESC_PER_PACKET;
        chanConfig.packetMem                        = (void *) hAVB2NSP->rxPacketMem;
        chanConfig.rxThreshCount                    = ((uint32_t)AVB2NSP_RX_PACKETS * (uint32_t)RX_BUFF_DESC_PER_PACKET) / 4U; /* Set threshold at 25% of total */
        chanConfig.callbacks.pFxnCbCloseChannel     = &LOCAL_closeRxChannel;
        chanConfig.callbacks.pFxnCbUsedPacketNotify = &LOCAL_notifyRxPackets;
        chanConfig.callbacks.hCallbackArg           = (void *) hAVB2NSP;

        GMACSW_ioctl(hAVB2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_OPEN_RX_CHANNEL,
                     (void *)&cmd,
                     sizeof(CPDMA_OpenRxChannelIoctlCmd));
        if (NULL == hAVB2NSP->hRxChannel) { goto teardown; }
    }

    /* Setup Rx priority mapping */
    {
        PORT_AddRxPriorityMappingIoctlCmd   cmd;
        PORT_RxPriorityConfig               portConfig;

        cmd.pPriConfig                                      = &portConfig;
        cmd.pRxPriorityMapHandle                            = &hAVB2NSP->hRxPriorityMap;

        portConfig.hCpdmaRxChannel                          = hAVB2NSP->hRxChannel;

        portConfig.switchPriority                           = PORT_SWITCH_PRIORITY_HIGH;
        portConfig.rxSource                                 = PORT_RX_SOURCE_MAC_BOTH;
        portConfig.rxPriorityType                           = PORT_RX_PRIORITY_TYPE_VLAN_TAGGED;
        portConfig.rxPriorityOption.vlanTagged.priority     = AVBTP_VLAN_PRIORITY;
        portConfig.rxPriorityOption.vlanTagged.vlanID       = AVBTP_VLAN_ID;

        GMACSW_ioctl(hAVB2NSP->hGMACSW,
                     GMACSW_IOCTL_PORT_ADD_RX_PRIORITY_MAPPING,
                     (void *)&cmd,
                     sizeof(PORT_AddRxPriorityMappingIoctlCmd));
        if (NULL == hAVB2NSP->hRxPriorityMap) { goto teardown; }
    }

    /* Open Tx Channel */
    {
        CPDMA_OpenTxChannelIoctlCmd cmd;
        CPDMA_TxChannelConfig       chanConfig;

        cmd.pTxChannelConfig                        = &chanConfig;
        cmd.pTxChannelHandle                        = &hAVB2NSP->hTxChannel;

        chanConfig.packetCount                      = (uint32_t)AVB2NSP_TX_PACKETS;
        chanConfig.buffersPerPacketCount            = (uint32_t)TX_BUFF_DESC_PER_PACKET;
        chanConfig.packetMem                        = (void *) hAVB2NSP->txPacketMem;
        chanConfig.callbacks.pFxnCbCloseChannel     = &LOCAL_closeTxChannel;
        chanConfig.callbacks.pFxnCbUsedPacketNotify = &LOCAL_notifyTxPackets;
        chanConfig.callbacks.hCallbackArg           = (void *) hAVB2NSP;

        GMACSW_ioctl(hAVB2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_OPEN_TX_CHANNEL,
                     (void *)&cmd,
                     sizeof(CPDMA_OpenTxChannelIoctlCmd));
        if (NULL == hAVB2NSP->hTxChannel) { goto teardown; }
    }

    /* Create semaphore objects, init shutDown status */
    {
        Semaphore_Params semParams;

        hAVB2NSP->shutDown = (bool)false;

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        hAVB2NSP->txTaskShutDownSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hAVB2NSP->txTaskShutDownSem) { goto teardown; }

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        hAVB2NSP->rxTaskShutDownSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hAVB2NSP->rxTaskShutDownSem) { goto teardown; }

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        hAVB2NSP->rxPacketSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hAVB2NSP->rxPacketSem) { goto teardown; }

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        hAVB2NSP->txPacketSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hAVB2NSP->txPacketSem) { goto teardown; }

        Semaphore_Params_init(&semParams);
        semParams.mode = Semaphore_Mode_BINARY;
        hAVB2NSP->txPacketFreeSem = Semaphore_create(0, &semParams, NULL);
        if (NULL == hAVB2NSP->txPacketFreeSem) { goto teardown; }
    }

    /* Start the packet processing tasks now that the channels are open */
    {
        Task_Params taskParams;

        Task_Params_init(&taskParams);
        taskParams.stackSize = AVB_RX_PACKET_TASK_STACK;
        taskParams.priority = AVB_RX_PACKET_TASK_PRI;
        taskParams.instance->name = "AVB2NSP_RxPacketTask";
        taskParams.arg0 = (UArg)hAVB2NSP;
        hAVB2NSP->rxPacketTask = Task_create(&LOCAL_avbRxPacketTask, &taskParams, NULL);
        if (hAVB2NSP->rxPacketTask == NULL) { goto teardown; }

        Task_Params_init(&taskParams);
        taskParams.stackSize = AVB_TX_PACKET_TASK_STACK;
        taskParams.priority = AVB_TX_PACKET_TASK_PRI;
        taskParams.instance->name = "AVB2NSP_TxPacketTask";
        taskParams.arg0 = (UArg)hAVB2NSP;
        hAVB2NSP->txPacketTask = Task_create(&LOCAL_avbTxPacketTask, &taskParams, NULL);
        if (hAVB2NSP->txPacketTask == NULL) { goto teardown; }
    }

    /* Register a local function for 100ms-period callback */
    {
        GMACSW_TickFxnIoctlCmd cmd;

        cmd.pTickFxnCallback    = &LOCAL_pollingCallback;
        cmd.hTickFxnCallbackArg = (void *) hAVB2NSP;
        cmd.hRegisteredTickFxn  = &hAVB2NSP->hRegisteredTickFxn;

        GMACSW_ioctl(hAVB2NSP->hGMACSW,
                     GMACSW_IOCTL_REGISTER_TICK_FXN,
                     (void *)&cmd,
                     sizeof(GMACSW_TickFxnIoctlCmd));
        if (NULL == hAVB2NSP->hRegisteredTickFxn) { goto teardown; }

    }

    /* Queue up some Rx packets, that the alloc callback will use */
    LOCAL_allocRxPackets(hAVB2NSP);

    /* Queue up some Tx packets, that the alloc callback will use */
    LOCAL_allocTxPackets(hAVB2NSP);

    return hAVB2NSP;

teardown:
    AVB2NSP_close(hAVB2NSP);
    return NULL;
}

void AVB2NSP_close(AVB2NSP_Handle hAVB2NSP)
{
    if (hAVB2NSP == NULL) { return; }

    /* Stop activity for this stack */
    if (hAVB2NSP->hGMACSW)
    {
        if (hAVB2NSP->hTxChannel)
        {
            /* Stop the Tx Channel */
            GMACSW_ioctl(hAVB2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_STOP_TX_CHANNEL,
                        (void *)&hAVB2NSP->hTxChannel,
                        sizeof(CPDMA_ChannelHandle));
        }

        if (hAVB2NSP->hRxChannel)
        {
            /* Stop the Rx Channel */
            GMACSW_ioctl(hAVB2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_STOP_RX_CHANNEL,
                        (void *)&hAVB2NSP->hRxChannel,
                        sizeof(CPDMA_ChannelHandle));
        }


        if (hAVB2NSP->hRegisteredTickFxn != NULL)
        {
            /* Unregister the 100ms-period callback */
            GMACSW_ioctl(hAVB2NSP->hGMACSW,
                         GMACSW_IOCTL_UNREGISTER_TICK_FXN,
                         (void *)&hAVB2NSP->hRegisteredTickFxn,
                         sizeof(GMACSW_RegisteredTickFxnHandle));
            hAVB2NSP->hRegisteredTickFxn = NULL;
        }

        if (hAVB2NSP->hTxChannel != NULL)
        {
            /* Close the Tx Channel */
            GMACSW_ioctl(hAVB2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_CLOSE_TX_CHANNEL,
                         (void *)&hAVB2NSP->hTxChannel,
                         sizeof(CPDMA_ChannelHandle));
            hAVB2NSP->hTxChannel = NULL;
        }

        if (hAVB2NSP->hRxPriorityMap != NULL)
        {
            /* Remove the priority mapping */
            GMACSW_ioctl(hAVB2NSP->hGMACSW,
                         GMACSW_IOCTL_PORT_REMOVE_RX_PRIORITY_MAPPING,
                         (void *) &hAVB2NSP->hRxPriorityMap,
                         sizeof(PORT_RxPriorityMapHandle));
            hAVB2NSP->hRxPriorityMap = NULL;
        }

        if (hAVB2NSP->hRxChannel != NULL)
        {
            /* Close the Rx Channel */
            GMACSW_ioctl(hAVB2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_CLOSE_RX_CHANNEL,
                         (void *)&hAVB2NSP->hRxChannel,
                         sizeof(CPDMA_ChannelHandle));
            hAVB2NSP->hRxChannel = NULL;
        }

        /* Set the translation layer shutDown flag */
        hAVB2NSP->shutDown = (bool)true;

        /* Close reference to the GMACSW hardware driver */
        GMACSW_close(hAVB2NSP->hGMACSW);
    }

    /*
     * Wait for parser task to shutDown completely before deleting
     * any resources the task is using.
     */
    if (hAVB2NSP->rxTaskShutDownSem != NULL)
    {
        if (hAVB2NSP->rxPacketTask != NULL)
        {
            /* If we are tearing down because something failed during open, we need
             * to wake up the task so it exits normally.
             */
            Semaphore_post(hAVB2NSP->rxPacketSem);
            Semaphore_pend(hAVB2NSP->rxTaskShutDownSem, BIOS_WAIT_FOREVER);
        }
        Semaphore_delete(&hAVB2NSP->rxTaskShutDownSem);
    }
    if (hAVB2NSP->txTaskShutDownSem != NULL)
    {
        if (hAVB2NSP->txPacketTask != NULL)
        {
            /* If we are tearing down because something failed during open, we need
             * to wake up the task so it exits normally.
             */
            Semaphore_post(hAVB2NSP->txPacketSem);
            Semaphore_pend(hAVB2NSP->txTaskShutDownSem, BIOS_WAIT_FOREVER);
        }
        Semaphore_delete(&hAVB2NSP->txTaskShutDownSem);
    }

    if (hAVB2NSP->rxPacketSem != NULL) { Semaphore_delete(&hAVB2NSP->rxPacketSem); }
    if (hAVB2NSP->txPacketSem != NULL) { Semaphore_delete(&hAVB2NSP->txPacketSem); }
    if (hAVB2NSP->txPacketFreeSem != NULL) { Semaphore_delete(&hAVB2NSP->txPacketFreeSem); }

    /*
     * We don't do task deletion since the NDK forces the
     * Task.deleteTerminatedTasks option be true, which means
     * the rxPacketTask and txPacketTask are auto-deleted.
     */

#if defined(AVB_DYNAMIC_ALLOCATION)
    free(hAVB2NSP);
#endif
}

void AVB2NSP_start(AVB2NSP_Handle hAVB2NSP)
{
    /* Start the Rx Channel */
    GMACSW_ioctl(hAVB2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_START_RX_CHANNEL,
                 (void *)&hAVB2NSP->hRxChannel,
                 sizeof(CPDMA_ChannelHandle));

    /* Start the Tx Channel */
    GMACSW_ioctl(hAVB2NSP->hGMACSW,
                 GMACSW_IOCTL_CPDMA_START_TX_CHANNEL,
                 (void *)&hAVB2NSP->hTxChannel,
                 sizeof(CPDMA_ChannelHandle));
}

void AVB2NSP_kickTx(AVB2NSP_Handle hAVB2NSP)
{
    Semaphore_post(hAVB2NSP->txPacketSem);
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static void LOCAL_closeRxChannel(void *hCallbackArg)
{
    CPDMA_PacketQueue   tempQueue;
    CPDMA_Packet        *pCurrCPDMAPacket;
    AVB2NSP_Handle      hAVB2NSP = (AVB2NSP_Handle) hCallbackArg;

    /* Post to rx packet task so that it will terminate (shutDown flag is already set) */
    if (hAVB2NSP->rxPacketTask != NULL)
    {
        Semaphore_post(hAVB2NSP->rxPacketSem);
    }

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * being returned from the hardware.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hAVB2NSP->hRxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hAVB2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Take all AVBTP packets from the fromHardware queue and put them on the
     * rxFreeAVBTPPacketQueue.
     */
    pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the NULL packets that need to be freed */
        AVBTP_RxPacket *hAVBTPPacket = (AVBTP_RxPacket *) pCurrCPDMAPacket->hPrivate;

        if (hAVBTPPacket)
        {
            AVBTP_enqueue(hAVB2NSP->config.rxFreeAVBTPPacketQueue, (node_t *)hAVBTPPacket);
        }
        pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    }
}

static void LOCAL_notifyRxPackets(void *hCallbackArg)
{
    AVB2NSP_Handle hAVB2NSP = (AVB2NSP_Handle) hCallbackArg;

    Semaphore_post(hAVB2NSP->rxPacketSem);
}

static void LOCAL_avbRxPacketTask(UArg arg0, UArg arg1)
{
    AVB2NSP_Handle hAVB2NSP = (AVB2NSP_Handle)arg0;
    CPDMA_PacketQueue tempQueue;
#if defined(AVBTP_INSTRUMENTATION_ENABLED)
    uint32_t time1;
    uint32_t packetCount;
#endif

    while (!hAVB2NSP->shutDown)
    {
        /* Wait for this translation layer to notify of initial packets to fill for hardware */
        Semaphore_pend(hAVB2NSP->rxPacketSem, BIOS_WAIT_FOREVER);

        if (hAVB2NSP->shutDown)
        {
            /* This translation layer is shutting down, don't give anything else to the stack */
            break;
        }

#if defined(AVBTP_INSTRUMENTATION_ENABLED)
        time1 = TIMER_READ();
        avb2NspStats.rxStats.rawNotificationCount++;
        packetCount = 0;
#endif

        /* Retrieve the used (filled) packets from the channel */
        {
            CPDMA_RetrievePacketQueueIoctlCmd cmd;

            CPDMA_packetQueueInit(&tempQueue);

            cmd.hChannel                    = hAVB2NSP->hRxChannel;
            cmd.pFromChannelQueue           = &tempQueue;

            /* This function will initialize the tempQueue variable */
            GMACSW_ioctl(hAVB2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
        }

        if (tempQueue.count != 0U)
        {
            /*
             * Get all used Rx CPDMA packets from the hardware, then send the buffers
             * of those packets on to the AVB stack to be parsed/processed.
             */
#if defined(AVBTP_INSTRUMENTATION_ENABLED)
            packetCount =
#endif
            LOCAL_prepRxPacketQueue(hAVB2NSP, &tempQueue);
        }
#if defined(AVBTP_INSTRUMENTATION_ENABLED)
        else
        {
            avb2NspStats.rxStats.zeroNotificationCount++;
        }

        /*
         * We don't want to time the semaphore post used to notify the AVBTP stack as that may cause
         * task transition. We don't want to time the semaphore pend, since that would be us doing
         * nothing but waiting.
         */
        if (packetCount != 0)
        {
            uint32_t notificationCount;
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
            uint32_t timePerPacket = timeDiff/packetCount;
            Load_Stat loadStat;

            notificationCount = avb2NspStats.rxStats.dataNotificationCount & (HISTORY_CNT - 1);
            avb2NspStats.rxStats.dataNotificationCount++;

            avb2NspStats.rxStats.totalPacketCount += packetCount;
            avb2NspStats.rxStats.totalCycleCnt += timeDiff;

            avb2NspStats.rxStats.cycleCountPerNotification[notificationCount] = timeDiff;
            if (timeDiff > avb2NspStats.rxStats.cycleCountPerNotificationMax)
            {
                avb2NspStats.rxStats.cycleCountPerNotificationMax = timeDiff;
            }

            avb2NspStats.rxStats.packetsPerNotification[notificationCount] = packetCount;
            if (packetCount > avb2NspStats.rxStats.packetsPerNotificationMax)
            {
                avb2NspStats.rxStats.packetsPerNotificationMax = packetCount;
            }

            avb2NspStats.rxStats.cycleCountPerPacket[notificationCount] = timePerPacket;
            if (timePerPacket >avb2NspStats.rxStats.cycleCountPerPacketMax)
            {
                avb2NspStats.rxStats.cycleCountPerPacketMax = timePerPacket;
            }

            if (Load_getTaskLoad(Task_self(), &loadStat))
            {
                avb2NspStats.rxStats.taskLoad[notificationCount] = Load_calculateLoad(&loadStat);
            }
        }
#endif
        if (hAVB2NSP->rxReadyAVBTPPacketQueue.count != 0)
        {
            /* A function pointer could be used here - but a direct call is used instead
             * so a link-time optimization can occur
             */
            AVBTP_processRxPackets((avbtp_handle_t)hAVB2NSP->config.clientData, &hAVB2NSP->rxReadyAVBTPPacketQueue);
        }
    }

    /* We are shutting down, notify that we are done */
    Semaphore_post(hAVB2NSP->rxTaskShutDownSem);
}

static void LOCAL_allocRxPackets(AVB2NSP_Handle hAVB2NSP)
{
    CPDMA_PacketQueue tempQueue;

    /*
     * Get the contents of the fromHardware queue, which should contain all packets
     * initially allocated by the channel open function.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hAVB2NSP->hRxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hAVB2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Go through packets in the queue and prep them to give to the
     * hardware
     */
    LOCAL_prepRxPacketQueue(hAVB2NSP, &tempQueue);
}

static uint32_t LOCAL_prepRxPacketQueue(AVB2NSP_Handle hAVB2NSP, CPDMA_PacketQueue *pPacketQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;
    CPDMA_Packet *pNextCPDMAPacket;

    uint32_t packetCount = 0;

    /*
     * AVBTP_processRxPackets is asynchronous so it may have held packets; if there
     * aren't enough free AVB packets available then we must wait until more become available.
     */
    if (hAVB2NSP->config.rxFreeAVBTPPacketQueue->count < pPacketQueue->count)
    {
        AVBTP_waitForPendingRxPackets((avbtp_handle_t)hAVB2NSP->config.clientData);
    }

    /*
     * Get all used Rx CPDMA packets from the hardware, then send the buffers
     * of those packets on to the AVBTP stack to be parsed/processed.
     */
    pCurrCPDMAPacket = pPacketQueue->pHead;
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the full AVBTP packet that needs to be returned to the AVB stack */
        AVBTP_RxPacket *hAVBTPPacket = (AVBTP_RxPacket *) pCurrCPDMAPacket->hPrivate;

        if (hAVBTPPacket != NULL)
        {
            /* Fill in the packet size as returned by the hardware */
            hAVBTPPacket->bufferSize = CPDMA_packetGetLength(pCurrCPDMAPacket);

            /* Enqueue the receive packet so that it can be consumed by the AVBTP layer */
            AVBTP_enqueue(&hAVB2NSP->rxReadyAVBTPPacketQueue, (node_t *)hAVBTPPacket);

#if defined(AVBTP_INSTRUMENTATION_ENABLED)
            avb2NspStats.rxReadyAVBTPPacketEnqueue++;
#endif
            packetCount++;
        }

        /* Dequeue an empty AVBTP packet to be associated with a CPDMA packet for the hardware */
        hAVBTPPacket = (AVBTP_RxPacket *)AVBTP_dequeue(hAVB2NSP->config.rxFreeAVBTPPacketQueue);
        if (hAVBTPPacket != NULL)
        {
#if defined(AVBTP_INSTRUMENTATION_ENABLED)
            avb2NspStats.rxFreeAVBTPPacketDequeue++;
#endif
            /* Each CPDMA packet has only one buffer descriptor */
            CPDMA_BuffDesc *pBuffDesc   = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);

            /* Save off the AVBTP packet handle so it can be handled by the AVBTP stack later */
            pCurrCPDMAPacket->hPrivate = (void *)hAVBTPPacket;

            /* Mark the packet as owned by the hardware */
            pBuffDesc->pDataBuffer              = hAVBTPPacket->pBuffer;
            pBuffDesc->bufferOffsetAndLength    = DEFAULT_PACKET_SIZE;
            pBuffDesc->flagsAndPacketLength     = CPDMA_BUF_DESC_OWNER_FLAG;

#if (0)
/*
 * FIXME: This shouldn't be needed as long as we never write data into the Rx buffers.
 * If we do that, then there may be evictions that we need to watch out for. The case of speculative
 * reads is handled since we are already doing invalidates in the avbtp.c file to be able to see the
 * correct header data.
 */
#if defined(CORTEX_AX)
            /*
             * Pre-invalidate the data buffer so that no spurious evictions will possibly
             * corrupt the packet buffer while the hardware CPDMA has ownership. We invalidate
             * the entire buffer since we don't know how big the arriving packets will be.
             */
            Cache_inv((Ptr)hAVBTPPacket->pBuffer,
                      (SizeT)DEFAULT_PACKET_SIZE,
                      (Bits16)Cache_Type_ALLD,
                      (Bool)1U);
#endif
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

        cmd.hChannel                    = hAVB2NSP->hRxChannel;
        cmd.pToChannelQueue             = pPacketQueue;

        GMACSW_ioctl(hAVB2NSP->hGMACSW,
                    GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS,
                    (void *)&cmd,
                    sizeof(CPDMA_SubmitPacketQueueIoctlCmd));
    }

    return packetCount;
}

static void LOCAL_closeTxChannel(void *hCallbackArg)
{
    AVB2NSP_Handle      hAVB2NSP = (AVB2NSP_Handle ) hCallbackArg;
    CPDMA_PacketQueue   tempQueue;

    /* Post to rx packet task so that it will terminate (shutDown flag is already set) */
    if (hAVB2NSP->txPacketTask != NULL)
    {
        Semaphore_post(hAVB2NSP->txPacketSem);
    }

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * being returned from the hardware.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hAVB2NSP->hTxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hAVB2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

#if (0)
    /* FIXME: The buffer descriptor free happens in the CPDMA channel close */
    uint32_t i;
    for (i = 0U; i < (uint32_t)AVB2NSP_TX_PACKETS; i++)
    {
        CPDMA_Packet *pCPDMAPacket = &hAVB2NSP->txPacketMem[i];
        CPDMA_freePacketBufferDescriptors(hAVB2NSP->hTxChannel, pCPDMAPacket);
    }
#endif
}

static void LOCAL_notifyTxPackets(void *hCallbackArg)
{
    AVB2NSP_Handle hAVB2NSP = (AVB2NSP_Handle)hCallbackArg;

    Semaphore_post(hAVB2NSP->txPacketSem);
}

static void LOCAL_avbTxPacketTask(UArg arg0, UArg arg1)
{
    AVB2NSP_Handle hAVB2NSP = (AVB2NSP_Handle) arg0;
    CPDMA_PacketQueue tempQueue;
#if defined(AVBTP_INSTRUMENTATION_ENABLED)
    uint32_t time1 = 0;
    uint32_t packetCount = 0;
#endif

    while (!hAVB2NSP->shutDown)
    {
        /*
         * Wait for the Tx ISR to notify us that empty packets are available
         * that were used to send data
         */
        Semaphore_pend(hAVB2NSP->txPacketSem, BIOS_WAIT_FOREVER);

#if defined(AVBTP_INSTRUMENTATION_ENABLED)
        time1 = TIMER_READ();
        avb2NspStats.txStats.rawNotificationCount++;
        packetCount = 0;
#endif

        /* Retrieve the used (sent/empty) packets from the channel */
        {
            CPDMA_RetrievePacketQueueIoctlCmd cmd;

            CPDMA_packetQueueInit(&tempQueue);

            cmd.hChannel                    = hAVB2NSP->hTxChannel;
            cmd.pFromChannelQueue           = &tempQueue;

            /* This function will initialize the tempQueue variable */
            GMACSW_ioctl(hAVB2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
        }

        if (tempQueue.count > 0)
        {
            LOCAL_prepTxPacketQueue(hAVB2NSP, &tempQueue);
        }
        LOCAL_sendTxPackets(hAVB2NSP);
        AVBTP_fillTxQueue((avbtp_handle_t)hAVB2NSP->config.clientData, &hAVB2NSP->txReadyAVBTPPacketQueue);
        LOCAL_sendTxPackets(hAVB2NSP);

#if defined(AVBTP_INSTRUMENTATION_ENABLED)
        if (tempQueue.count == 0)
        {
            avb2NspStats.txStats.zeroNotificationCount++;
        }

        if (packetCount != 0)
        {
            uint32_t notificationCount;
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
            uint32_t timePerPacket = timeDiff/packetCount;
            Load_Stat loadStat;

            notificationCount = avb2NspStats.rxStats.dataNotificationCount & (HISTORY_CNT - 1);
            avb2NspStats.txStats.dataNotificationCount++;

            avb2NspStats.txStats.totalPacketCount += packetCount;
            avb2NspStats.txStats.totalCycleCnt += timeDiff;

            avb2NspStats.txStats.cycleCountPerNotification[notificationCount] = timeDiff;
            if (timeDiff > avb2NspStats.txStats.cycleCountPerNotificationMax)
            {
                avb2NspStats.txStats.cycleCountPerNotificationMax = timeDiff;
            }

            avb2NspStats.txStats.packetsPerNotification[notificationCount] = packetCount;
            if (packetCount > avb2NspStats.txStats.packetsPerNotificationMax)
            {
                avb2NspStats.txStats.packetsPerNotificationMax = packetCount;
            }

            avb2NspStats.txStats.cycleCountPerPacket[notificationCount] = timePerPacket;
            if (timePerPacket >avb2NspStats.txStats.cycleCountPerPacketMax)
            {
                avb2NspStats.txStats.cycleCountPerPacketMax = timePerPacket;
            }

            if (Load_getTaskLoad(Task_self(), &loadStat))
            {
                avb2NspStats.txStats.taskLoad[notificationCount] = Load_calculateLoad(&loadStat);
            }
        }
#endif
    }

    /* We are shutting down, notify that we are done */
    Semaphore_post(hAVB2NSP->txTaskShutDownSem);
}

static void LOCAL_allocTxPackets(AVB2NSP_Handle hAVB2NSP)
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

        cmd.hChannel                    = hAVB2NSP->hTxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hAVB2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Go through the CPDMA packets in the queue, and move them to the
     * txFreeCPDMAPacketQueue so they are ready to be used when the stack
     * wants to send a packet
     */
    LOCAL_prepTxPacketQueue(hAVB2NSP, &tempQueue);
}

static uint32_t LOCAL_prepTxPacketQueue(AVB2NSP_Handle hAVB2NSP, CPDMA_PacketQueue *pPacketQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;

    uint32_t packetCount = 0;

    pCurrCPDMAPacket = pPacketQueue->pHead;
    while (pCurrCPDMAPacket)
    {
        AVBTP_TxPacket *hAVBTPPacket = (AVBTP_TxPacket *)pCurrCPDMAPacket->hPrivate;

        /* Free the packet - it was allocated by the stack/sender */
        if (hAVBTPPacket != NULL)
        {
            AVBTP_enqueue(hAVB2NSP->config.txFreeAVBTPPacketQueue, (node_t *)hAVBTPPacket);
            packetCount++;
            if (hAVBTPPacket->notifyFree)
            {
                hAVBTPPacket->callBack(hAVBTPPacket->buffer, hAVBTPPacket->txCbData, hAVBTPPacket->talkerIndex);
                hAVBTPPacket->notifyFree = false;
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
        CPDMA_appendPacketQueue(&hAVB2NSP->txFreeCPDMAPacketQueue, pPacketQueue);

#if defined(AVBTP_INSTRUMENTATION_ENABLED)
        avb2NspStats.txFreeCPDMAPacketEnqueue += pPacketQueue->count;
#endif

        /* Clear the input queue */
        CPDMA_packetQueueInit(pPacketQueue);

        GMACSW_AL_globalInterruptEnable(key);
    }

    if (packetCount > 0)
    {
        Semaphore_post(hAVB2NSP->txPacketFreeSem);
    }

    return packetCount;
}

void LOCAL_sendTxPackets(AVB2NSP_Handle hAVB2NSP)
{
    CPDMA_Packet *pPrevCPDMAPacket = NULL;
    AVBTP_TxPacket *hAVBTPPacket;
    CPDMA_PacketQueue tempQueue;

    CPDMA_packetQueueInit(&tempQueue);

    /* If there is nothing queued to transmit, simply return */
    hAVBTPPacket = (AVBTP_TxPacket *)AVBTP_dequeue(&hAVB2NSP->txReadyAVBTPPacketQueue);
    while (NULL != hAVBTPPacket)
    {
        CPDMA_Packet *pCurrCPDMAPacket;

        /* Allocate a packet from the Tx CPDMA packet pool */
        pCurrCPDMAPacket = CPDMA_packetDequeue(&hAVB2NSP->txFreeCPDMAPacketQueue);
        if (NULL != pCurrCPDMAPacket)
        {
            /* Populate the packet and the buffer descriptor(s) it contains */
            CPDMA_BuffDesc      *pFirstBuffDesc = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);
            CPDMA_BuffDesc      *pLastBuffDesc = CPDMA_packetGetLastDesc(pCurrCPDMAPacket);

            /*
             * Save off the AVBTP packet handle so it can be freed when the CPDMA
             * packet is freed via the callback after it is transmitted
             */
            pCurrCPDMAPacket->hPrivate = (void *)hAVBTPPacket;

            CPDMA_setHardwareAsOwner(pFirstBuffDesc);
            CPDMA_setStartOfPacket  (pFirstBuffDesc);
            CPDMA_setDataBuffer     (pFirstBuffDesc, hAVBTPPacket->pHeader);
            CPDMA_setBufferLength   (pFirstBuffDesc, AVBTP_PACKET_HEADER_SIZE);
            CPDMA_setBufferOffset   (pFirstBuffDesc, 0);
            CPDMA_setPacketLength   (pFirstBuffDesc, hAVBTPPacket->bufferSize + AVBTP_PACKET_HEADER_SIZE);
            CPDMA_setDataBuffer     (pLastBuffDesc, hAVBTPPacket->pBuffer);
            CPDMA_setBufferLength   (pLastBuffDesc, hAVBTPPacket->bufferSize);
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
            AVBTP_enqueueHead(&hAVB2NSP->txReadyAVBTPPacketQueue, (node_t *)hAVBTPPacket);
            avb2NspStats.txDroppedPacketCount++;
            break;
        }
        hAVBTPPacket = (AVBTP_TxPacket *)AVBTP_dequeue(&hAVB2NSP->txReadyAVBTPPacketQueue);
    }

    /* Give the accumulated packets to the hardware */
    {
        CPDMA_SubmitPacketQueueIoctlCmd cmd;

        cmd.hChannel                    = hAVB2NSP->hTxChannel;
        cmd.pToChannelQueue             = &tempQueue;

        GMACSW_ioctl(hAVB2NSP->hGMACSW,
                    GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS,
                    (void *)&cmd,
                    sizeof(CPDMA_SubmitPacketQueueIoctlCmd));
    }
}

static void LOCAL_pollingCallback(void *hCallbackArg)
{
    static uint32_t loadCount = 0;
    Load_Stat stat;

    AVB2NSP_Handle hAVB2NSP = (AVB2NSP_Handle) hCallbackArg;

    if (Load_getTaskLoad(hAVB2NSP->rxPacketTask, &stat))
    {
        avb2NspStats.rxStats.taskLoad[loadCount] = Load_calculateLoad(&stat);
    }
    if (Load_getTaskLoad(hAVB2NSP->txPacketTask, &stat))
    {
        avb2NspStats.txStats.taskLoad[loadCount] = Load_calculateLoad(&stat);
    }

    loadCount = (loadCount+1U) & ((uint32_t)HISTORY_CNT - 1U);
}

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

