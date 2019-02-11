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
 *   \file  ndk2nsp.c
 *
 *   \brief
 *          Translation layer to go from NDK to NSP hardware driver.
 *
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>

/* OS/Posix headers */
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/hal/Cache.h>

/* NDK Dependencies */
#include <ti/ndk/inc/stkmain.h>

/* NSP GMACSW driver dependency headers */
#include "gmacsw.h"
#include "gmacsw_al.h"
#include "gmacsw_config.h"
#if defined(NSP_INSTRUMENTATION_ENABLED)
#include "private/timer_.h"
#endif
#include "private/debug_.h"

/* This module's header */
#include "ndk2nsp.h"

#if defined(TFDTP_STACK_ENABLED)
#include "tfdtp.h"
#include "tfdtp_priv.h"
#endif

/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/

extern PBMQ PBMQ_free;

/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/



#define BUFF_DESC_PER_PACKET        ((uint32_t)1U)

#define NDK_RX_PACKET_TASK_PRI      (OS_TASKPRIHIGH)
#define NDK_RX_PACKET_TASK_STACK    (2048)

#define NDK_TX_PACKET_TASK_PRI      (OS_TASKPRIHIGH)
#define NDK_TX_PACKET_TASK_STACK    (2048)

#define TFDTP_DEBUG 0

/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static void     LOCAL_closeRxChannel(void *hCallbackArg);
static void     LOCAL_notifyRxPackets(void *hCallbackArg);
static void     LOCAL_rxPacketTask(void *arg0);
static void     LOCAL_allocRxPackets(NDK2NSP_Handle hNDK2NSP);
static void     LOCAL_submitRxPackets(NDK2NSP_Handle hNDK2NSP);
static uint32_t LOCAL_prepRxPacketQueue(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *pPacketQueue);
static void     LOCAL_resubmitRxPacketQueue(NDK2NSP_Handle hNDK2NSP);
static void     LOCAL_closeTxChannel(void *hCallbackArg);
static void     LOCAL_notifyTxPackets(void *hCallbackArg);
static void     LOCAL_txPacketTask(void *arg0);
static void     LOCAL_allocTxPackets(NDK2NSP_Handle hNDK2NSP);
static uint32_t LOCAL_prepTxPacketQueue(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *pPacketQueue);
static void     LOCAL_pollingCallback(void *hCallbackArg);
static inline void LOCAL_print(char *prnStr, ...);

#if defined (TFDTP_STACK_ENABLED)
#if (1 == TFDTP_DEBUG)
static void LOCAL_discardTFDTPPackets(NDK2NSP_Handle hNDK2NSP);
#endif
static inline void LOCAL_freeTFDTPPackets(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *tempQueue);
static inline uint32_t LOCAL_checkTfdtpPacket(uint8_t *buffer, uint32_t rxUdpPort);
static inline void LOCAL_setEdmaParamSrcAddress(TFDTP_RxPacket *pPacket);
static uint32_t LOCAL_prepTFDTPRxPacketQueue(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *pPacketQueue);
static void LOCAL_resubmitTfdtpRxPacketQueue(NDK2NSP_Handle hNDK2NSP);
#else
static void LOCAL_freePBMPackets(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *tempQueue);
#endif

/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

#if !defined(NSP_DYNAMIC_ALLOCATION)
static NDK2NSP_Object NDK2NSP_object;
#endif
static NDK2NSP_Handle LOCAL_ndk2nspRef = NULL;

#if defined(TFDTP_STACK_ENABLED)
#if defined(__GNUC__)
TFDTP_RxPacket gTFDTPRxPackets[NDK_RX_PACKETS] __attribute__(( aligned(128), section(".far:TFDTP_MEMPOOL") ));
#else
#pragma DATA_ALIGN(gTFDTPRxPackets, 128);
#pragma DATA_SECTION(gTFDTPRxPackets, ".far:TFDTP_MEMPOOL");
TFDTP_RxPacket gTFDTPRxPackets[NDK_RX_PACKETS];
#endif
#endif

/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

NDK2NSP_Stats ndk2NspStats;

/*Keep a count, so that common configs are not repeated the second time*/
uint32_t LOCAL_ndk2nspRefCount = 0;

/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

/*!
 *  @b NDK2NSP_open
 *  @n
 *      Opens and configures GMACSW. Configures Interrupts, SGMII,
 *      and send and receive queues.
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *
 *  \retval
 *      Success -  0
 *  \retval
 *      Error   -  Any non-zero value
 */
NDK2NSP_Handle NDK2NSP_open(STKEVENT_Handle hEvent)
{
    /* Increment the count here so that we know the next time it is called, 
     * it's the second time
     */
    LOCAL_ndk2nspRefCount++;

    NDK2NSP_Handle  hNDK2NSP;

    /* A count of 2 means that the function is being called for the second time.
     * This happens only for the dual mac case. But when dual mac is enabled, 
     * the initializations are already done. Instead of repeating that, we can 
     * simply return the pointer to the existing handle
     */
    if(1U == LOCAL_ndk2nspRefCount)
    {
            uint32_t i;

            uint32_t devIdx;
            uint32_t numPorts;

            GMACSW_Config   *pGMACSWConfig;

        #if defined(NSP_DYNAMIC_ALLOCATION)
            hNDK2NSP = (NDK2NSP_Handle ) calloc(1U, sizeof(NDK2NSP_Object));
            if (hNDK2NSP == NULL)
            {
                LOCAL_ndk2nspRefCount--;
                LOCAL_print("ERROR: Unable to allocate packet device object!\n");
                return NULL;
            }
        #else
            hNDK2NSP = &NDK2NSP_object;
        #endif

            /* Save NDK2NSP object into global handle */
            LOCAL_ndk2nspRef = hNDK2NSP;

            /* Clear instrumentation statistics structure */
            memset(&ndk2NspStats, 0, sizeof(NDK2NSP_Stats));

            /* Initialize the allocated memory block. */
            memset(hNDK2NSP, 0, sizeof(NDK2NSP_Object));

            /* Set the dual mac enable flag if its enabled*/
            #ifdef DUAL_MAC_MODE
            hNDK2NSP->enableDualMac = 1;
            #else
            hNDK2NSP->enableDualMac = 0;
            #endif

            /* Create PBM Q access semaphore here as it is accessed by below functions */
            hNDK2NSP->pbmQAccessSem = SemCreateBinary(1);

            /* Loop bound set to initialize the queues,
             * taking dual mac into consideration
             */
            numPorts = (1U == hNDK2NSP->enableDualMac) ? 2U : 1U;

            /* Initialize the Rx Queues & Data */
            for(devIdx = 0; devIdx < numPorts; devIdx++)
            {
                PBMQ_init(&hNDK2NSP->rxReadyPBMPacketQueue[devIdx]);
            }

        #if defined (TFDTP_STACK_ENABLED)
            PBMQ_init(&hNDK2NSP->rxReadyTFDTPPacketQueue);
            TFDTP_queueInit(&hNDK2NSP->rxFreeTFDTPNDKPacketQueue);
        #else
            PBMQ_init(&hNDK2NSP->rxFreePBMPacketQueue);
        #endif

            /* Initialize the Tx Queues & Data */
            for(devIdx = 0; devIdx < numPorts; devIdx++)
            {
                PBMQ_init(&hNDK2NSP->txReadyPBMPacketQueue[devIdx]);
            }

            CPDMA_packetQueueInit(&hNDK2NSP->txFreeCPDMAPacketQueue);

            /* Keep stack event handle to use to signal the NDK stack */
            hNDK2NSP->hEvent = hEvent;

            /* MCast List is EMPTY */
            hNDK2NSP->MCastCnt = 0;

            /* Init internal bookkeeping fields */
            hNDK2NSP->OldMCastCnt = 0;

            /* Get application provided driver configuration */
            pGMACSWConfig = GMACSW_getConfig();

            /* If configuration structure is invalid, get the driver default */
            if (NULL == pGMACSWConfig)
            {
                pGMACSWConfig = GMACSW_CONFIG_getDefaultConfig();
            }

            /* Open the hardware driver using the obtained configuration */
            hNDK2NSP->hGMACSW = GMACSW_open(pGMACSWConfig);
            if (NULL == hNDK2NSP->hGMACSW)
            {
                LOCAL_print("GMACSW_open() Returned error \n");

        #if defined(NSP_DYNAMIC_ALLOCATION)
                free(hNDK2NSP);
        #endif
                return NULL;
            }

            /* Get initial link/interface status from the driver */
            for(devIdx = 0; devIdx < numPorts; devIdx++)
            {
                GMACSW_getLinkStatus(hNDK2NSP->hGMACSW, &hNDK2NSP->linkIsUp[devIdx], devIdx);
            }

            hNDK2NSP->PktMTU = pGMACSWConfig->PktMTU;

            hNDK2NSP->inDLBMode = pGMACSWConfig->dlbMode;

        /* Copy the MAC address(es) into the translation layer structure */
        for( i=0; i < MAC_NUM_PORTS; i++ )
        {
            if ((1U << i) & (uint32_t)pGMACSWConfig->activeMACPortMask )
            {
                memcpy( (void *)&(hNDK2NSP->bMacAddr[i][0]), (void *)&(pGMACSWConfig->macInitCfg[i].macAddr[0]), (size_t)6U);
            }
        }
            /* Open Rx Channel */
            {
                CPDMA_OpenRxChannelIoctlCmd cmd;
                CPDMA_RxChannelConfig       config;

                cmd.pRxChannelConfig                    = &config;
                cmd.pRxChannelHandle                    = &hNDK2NSP->hRxChannel;

                config.packetCount                      = NDK2NSP_RX_PACKETS;
                config.buffersPerPacketCount            = BUFF_DESC_PER_PACKET;
                config.packetMem                        = (void *) hNDK2NSP->rxPacketMem;
                config.rxThreshCount                    = (NDK2NSP_RX_PACKETS * BUFF_DESC_PER_PACKET) / 4U; /* Set threshold at 25% of total */
                config.callbacks.pFxnCbCloseChannel     = &LOCAL_closeRxChannel;
                config.callbacks.pFxnCbUsedPacketNotify = &LOCAL_notifyRxPackets;
                config.callbacks.hCallbackArg           = (void *) hNDK2NSP;

                GMACSW_ioctl(hNDK2NSP->hGMACSW,
                             GMACSW_IOCTL_CPDMA_OPEN_RX_CHANNEL,
                             (void *)&cmd,
                             sizeof(CPDMA_OpenRxChannelIoctlCmd));
                assert(NULL != hNDK2NSP->hRxChannel);
            }

            /* Config Rx Channel for best effort traffic */
            {
                PORT_AddRxPriorityMappingIoctlCmd   cmd;
                PORT_RxPriorityConfig               config;

                cmd.pPriConfig              = &config;
                cmd.pRxPriorityMapHandle    = &hNDK2NSP->hRxPriorityMap;

                config.hCpdmaRxChannel  = hNDK2NSP->hRxChannel;
                config.switchPriority   = PORT_SWITCH_PRIORITY_NONE;
                config.rxSource         = PORT_RX_SOURCE_MAC_BOTH;
                config.rxPriorityType   = PORT_RX_PRIORITY_TYPE_ALL_UNTAGGED;
                config.rxPriorityOption.untagged.priority  = 0;

                GMACSW_ioctl(hNDK2NSP->hGMACSW,
                             GMACSW_IOCTL_PORT_ADD_RX_PRIORITY_MAPPING,
                             (void *)&cmd,
                             sizeof(PORT_AddRxPriorityMappingIoctlCmd));
                assert(NULL != hNDK2NSP->hRxPriorityMap);
            }

            /* Open Tx Channel */
            {
                CPDMA_OpenTxChannelIoctlCmd cmd;
                CPDMA_TxChannelConfig       config;

                cmd.pTxChannelConfig                    = &config;
                cmd.pTxChannelHandle                    = &hNDK2NSP->hTxChannel;

                config.packetCount                      = NDK2NSP_TX_PACKETS;
                config.buffersPerPacketCount            = BUFF_DESC_PER_PACKET;
                config.packetMem                        = (void *) hNDK2NSP->txPacketMem;
                config.callbacks.pFxnCbCloseChannel     = &LOCAL_closeTxChannel;
                config.callbacks.pFxnCbUsedPacketNotify = &LOCAL_notifyTxPackets;
                config.callbacks.hCallbackArg           = (void *) hNDK2NSP;

                GMACSW_ioctl(hNDK2NSP->hGMACSW,
                             GMACSW_IOCTL_CPDMA_OPEN_TX_CHANNEL,
                             (void *)&cmd,
                             sizeof(CPDMA_OpenTxChannelIoctlCmd));
                assert(NULL != hNDK2NSP->hTxChannel);
            }

            /* Register a local function for 100ms-period callback */
            {
                GMACSW_TickFxnIoctlCmd cmd;

                cmd.pTickFxnCallback    = &LOCAL_pollingCallback;
                cmd.hTickFxnCallbackArg = (void *) hNDK2NSP;
                cmd.hRegisteredTickFxn  = &hNDK2NSP->hRegisteredTickFxn;

                GMACSW_ioctl(hNDK2NSP->hGMACSW,
                             GMACSW_IOCTL_REGISTER_TICK_FXN,
                             (void *)&cmd,
                             sizeof(GMACSW_TickFxnIoctlCmd));
                assert(NULL != hNDK2NSP->hRegisteredTickFxn);
            }

            /* Allocate/fill the PBM/CPDMA packets for the Rx channel */
            LOCAL_allocRxPackets(hNDK2NSP);

            /* Initialize the free packet queue */
            CPDMA_packetQueueInit(&hNDK2NSP->rxFreePacketQueue);
            /* Allocate/fill the CPDMA packets for the Tx channel */
            LOCAL_allocTxPackets(hNDK2NSP);

        #if defined (TFDTP_STACK_ENABLED)
            /* Initialize TFDTP stack and link EDMA PaRAMs to each of packets */
            /* NOTE: This should be done before LOCAL_submitRxPackets as we want to
             * associate EDMA PaRAMs to each packet so should be done before giving any
             * packet to Hardware */
            hNDK2NSP->hTfdtp = TFDTP_initStack(hNDK2NSP);
            /* Disable TFDTP receive until explicitly enabled by TFDTP_start */
            hNDK2NSP->tfdtpRxFlag   = FALSE;
        #endif

            LOCAL_submitRxPackets(hNDK2NSP);

            /* Create semaphore objects, init shutDown status */
            hNDK2NSP->shutDown      = 0U;
            hNDK2NSP->shutDownSem   = SemCreate(0);
            hNDK2NSP->rxPacketSem   = SemCreateBinary(0);
            hNDK2NSP->txPacketSem   = SemCreateBinary(0);

            /* Start the packet processing tasks now that the channels are open */
            hNDK2NSP->rxPacketTask  = TaskCreate(&LOCAL_rxPacketTask, "NDK2NSP_RxPacketTask",
                                                 (int)NDK_RX_PACKET_TASK_PRI, (uint)NDK_RX_PACKET_TASK_STACK,
                                                 (uint32_t) hNDK2NSP, (uint32_t)0, (uint32_t)0 );
            hNDK2NSP->txPacketTask  = TaskCreate(&LOCAL_txPacketTask, "NDK2NSP_TxPacketTask",
                                                 (int)NDK_TX_PACKET_TASK_PRI, (uint)NDK_TX_PACKET_TASK_STACK,
                                                 (uint32_t) hNDK2NSP, (uint32_t)0, (uint32_t)0 );

            /* Start the Rx Channel */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_START_RX_CHANNEL,
                         (void *)&hNDK2NSP->hRxChannel,
                         sizeof(CPDMA_ChannelHandle));

            /* Start the Tx Channel */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_START_TX_CHANNEL,
                         (void *)&hNDK2NSP->hTxChannel,
                         sizeof(CPDMA_ChannelHandle));
    }
    else
    {
        hNDK2NSP = LOCAL_ndk2nspRef;
    }
    return hNDK2NSP;
}

/*!
 *  @b NDK2NSP_close
 *  @n
 *      Closes GMACSW and disables interrupts.
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *
 *  \retval
 *      void
 */
void NDK2NSP_close( NDK2NSP_Handle hNDK2NSP )
{
    uint32_t retVal;

    uint32_t devIdx;
    uint32_t numPorts;

    LOCAL_ndk2nspRefCount--;

    if(0U == LOCAL_ndk2nspRefCount)
    {
            /* Stop the Tx Channel */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_STOP_TX_CHANNEL,
                         (void *)&hNDK2NSP->hTxChannel,
                         sizeof(CPDMA_ChannelHandle));

            /* Stop the Rx Channel */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_STOP_RX_CHANNEL,
                         (void *)&hNDK2NSP->hRxChannel,
                         sizeof(CPDMA_ChannelHandle));

            /* Set the translation layer shutdown flag */
            hNDK2NSP->shutDown = 1U;

            /* Unregister the 100ms-period callback */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                         GMACSW_IOCTL_UNREGISTER_TICK_FXN,
                         (void *)&hNDK2NSP->hRegisteredTickFxn,
                         sizeof(GMACSW_RegisteredTickFxnHandle));

            /* Close the Tx Channel */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_CLOSE_TX_CHANNEL,
                         (void *)&hNDK2NSP->hTxChannel,
                         sizeof(CPDMA_ChannelHandle));
            hNDK2NSP->hTxChannel = NULL;

            /* Remove the best effort Rx priority mapping */
            GMACSW_ioctl( hNDK2NSP->hGMACSW,
                          GMACSW_IOCTL_PORT_REMOVE_RX_PRIORITY_MAPPING,
                          (void *)&hNDK2NSP->hRxPriorityMap,
                          sizeof(PORT_RxPriorityMapHandle));
            hNDK2NSP->hRxPriorityMap = NULL;

            /* Close the Rx Channel */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                         GMACSW_IOCTL_CPDMA_CLOSE_RX_CHANNEL,
                         (void *)&hNDK2NSP->hRxChannel,
                         sizeof(CPDMA_ChannelHandle));
            hNDK2NSP->hRxChannel = NULL;

            /* Now close the driver */
            retVal = GMACSW_close(hNDK2NSP->hGMACSW);
            if(retVal != 0)
            {
                LOCAL_print("GMACSW Close Returned error %08x\n",retVal);
            }

            /* Loop bound set to free the queues,
             * taking dual mac into consideration
             */
            numPorts = (1U == hNDK2NSP->enableDualMac) ? 2U : 1U;

            /* Flush out our pending receive queue */
            for(devIdx = 0; devIdx < numPorts; devIdx++)
            {
                while (PBMQ_count(&hNDK2NSP->rxReadyPBMPacketQueue[devIdx]) != 0)
                {
                    PBM_free( My_PBMQ_deq(&hNDK2NSP->rxReadyPBMPacketQueue[devIdx]) );
            #if defined(NSP_INSTRUMENTATION_ENABLED)
                    ndk2NspStats.rxReadyPBMPacketDequeue[devIdx]++;
            #endif
                }
            }

        #if defined (TFDTP_STACK_ENABLED)
            TFDTP_deInitStack(hNDK2NSP, hNDK2NSP->hTfdtp);
            /* Flush out our pending receive queue */
            TFDTP_RxPacket *hTFDTPPacket = (TFDTP_RxPacket *)TFDTP_dequeue(&hNDK2NSP->rxReadyTFDTPPacketQueue);
            PBM_Handle hPBMPacket = hTFDTPPacket->hPBMPacket;
            if (hPBMPacket)
            {
                PBM_free(hPBMPacket);
            }
        #endif

            /* Pend on shutDownSem (twice for two sub-tasks) */
            SemPend(hNDK2NSP->shutDownSem, (uint32_t)SEM_FOREVER);
            SemPend(hNDK2NSP->shutDownSem, (uint32_t)SEM_FOREVER);

            /* Delete the semaphore objects */
            SemDelete(hNDK2NSP->rxPacketSem);
            SemDelete(hNDK2NSP->txPacketSem);
            SemDelete(hNDK2NSP->shutDownSem);
            SemDelete(hNDK2NSP->pbmQAccessSem);

            /*
             * We don't do task deletion since the NDK forces the
             * Task.deleteTerminatedTasks option be true, which means
             * the rxPacketTask and txPacketTask are auto-deleted.
             */

            /* Clear the allocated translation */
            memset(hNDK2NSP, 0, sizeof(NDK2NSP_Object));

        #if defined(NSP_DYNAMIC_ALLOCATION)
            free(hNDK2NSP);
        #endif

    }
}

/*!
 *  @b NDK2NSP_setRx
 *  @n
 *      Sets the filter for GMACSW. Sets up the multicast addresses in
 *      the ALE.
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *
 *  \retval
 *      void
 */
void NDK2NSP_setRx( NDK2NSP_Handle hNDK2NSP )
{
    uint32_t i;
    uint32_t key = 0;

    key = GMACSW_AL_globalInterruptDisable();

    /* Configure the Receive filter */
    GMACSW_ioctl(hNDK2NSP->hGMACSW,
                 GMACSW_IOCTL_ALE_SET_RX_FILTER,
                 (void *)&hNDK2NSP->Filter,
                 sizeof(uint32_t));


    /* Clear the Old multicast list settings */
    {
        ALE_MulticastIoctlCmd cmd;

        cmd.addrCount   = hNDK2NSP->OldMCastCnt;
        cmd.pMCastList  = hNDK2NSP->bOldMCast;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                    GMACSW_IOCTL_ALE_CLEAR_MULTICAST,
                    (void *)&cmd,
                    sizeof(ALE_MulticastIoctlCmd));
    }

    hNDK2NSP->OldMCastCnt = 0;

    /* Finally configure the Filter and new multicast settings in the GMACSW ALE. */
    {
        ALE_MulticastIoctlCmd cmd;

        cmd.addrCount   = hNDK2NSP->MCastCnt;
        cmd.pMCastList  = hNDK2NSP->bMCast;

        i = GMACSW_ioctl(hNDK2NSP->hGMACSW,
                    GMACSW_IOCTL_ALE_SET_MULTICAST,
                    (void *)&cmd,
                    sizeof(ALE_MulticastIoctlCmd));
        if (i != 0)
        {
            LOCAL_print("GMACSW_setMulticast Returned error %0x08X\n",i);
            return;
        }
    }
    GMACSW_AL_globalInterruptEnable(key);

    /* Save count and entries for deletion next time around */
    hNDK2NSP->OldMCastCnt = hNDK2NSP->MCastCnt;
    for(i = 0; i < hNDK2NSP->MCastCnt; i++)
    {
        mmCopy(&hNDK2NSP->bOldMCast[(uint32_t)6U*i], &hNDK2NSP->bMCast[(uint32_t)6U*i], (uint)6U);
    }
}

/*!
 *  @b NDK2NSP_sendTxPackets
 *  @n
 *      Routine to send out queued Tx packets to the hardware driver
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *
 *  \retval
 *      void
 */
void NDK2NSP_sendTxPackets( NDK2NSP_Handle hNDK2NSP, uint32_t devIdx )
{
    uint32_t linkVar = hNDK2NSP->linkIsUp[devIdx];
    /* If link is not up, simply return */

    if (1U == linkVar)
    {
        CPDMA_Packet *pPrevCPDMAPacket = NULL;
        PBM_Handle hPBMPacket;
        CPDMA_PacketQueue tempQueue;

        CPDMA_packetQueueInit(&tempQueue);

        /* If there is nothing queued to transmit, simply return */
        hPBMPacket = My_PBMQ_deq(&hNDK2NSP->txReadyPBMPacketQueue[devIdx]);
        while (NULL != hPBMPacket)
        {
            CPDMA_Packet *pCurrCPDMAPacket;

#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.txReadyPBMPacketDequeue[devIdx]++;
#endif

            /* Allocate a packet from the Tx CPDMA packet pool */
            pCurrCPDMAPacket = CPDMA_packetDequeue(&hNDK2NSP->txFreeCPDMAPacketQueue);
            if (NULL != pCurrCPDMAPacket)
            {
                /* Populate the packet and the buffer descriptor(s) it contains */
                uint8_t             *buffer = PBM_getDataBuffer(hPBMPacket) + PBM_getDataOffset(hPBMPacket);
                uint32_t            length = PBM_getValidLen(hPBMPacket);
                CPDMA_BuffDesc      *pFirstBuffDesc = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);
                CPDMA_BuffDesc      *pLastBuffDesc = CPDMA_packetGetLastDesc(pCurrCPDMAPacket);

#if defined(NSP_INSTRUMENTATION_ENABLED)
                ndk2NspStats.txFreeCPDMAPacketDequeue++;
#endif

#if defined(DATA_BUFFERS_IN_CACHED_MEMORY)
                /* Clean the cache for the packet data so CPDMA gets correct data */
                Cache_wbInv( (Ptr)(PBM_getDataBuffer(hPBMPacket)),
                             (SizeT)(length + PBM_getDataOffset(hPBMPacket)),
                             (Bits16)Cache_Type_ALLD,
                             (Bool)1U);
#endif

                /*
                 * Save off the PBM packet handle so it can be freed when the CPDMA
                 * packet is freed via the callback after it is transmitted
                 */
                pCurrCPDMAPacket->hPrivate = (void *)hPBMPacket;

                CPDMA_setHardwareAsOwner(pFirstBuffDesc);
                CPDMA_setStartOfPacket  (pFirstBuffDesc);
                CPDMA_setDataBuffer     (pFirstBuffDesc, buffer);
                CPDMA_setBufferLength   (pFirstBuffDesc, (uint16_t)length);
                CPDMA_setBufferOffset   (pFirstBuffDesc, 0);
                CPDMA_setPacketLength   (pFirstBuffDesc, (uint16_t)length);
                CPDMA_setEndOfPacket    (pLastBuffDesc);
                CPDMA_clearEndOfQueue   (pLastBuffDesc);

                if (1U == hNDK2NSP->inDLBMode)
                {
                    /*
                     * In digital loopback mode, we only want to send to SL/MAC port 1, so we only get one Rx in return.
                     * To accomplish that, we make the buffer descriptor be directed.
                     */
                    CPDMA_setTxToPort(pFirstBuffDesc, (uint32_t)1U);
                }

                if(1U == hNDK2NSP->enableDualMac)
                {
                    CPDMA_setTxToPort(pFirstBuffDesc, (uint32_t)devIdx+1U);
                }

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
                PBM_free(hPBMPacket);
#if defined(NSP_INSTRUMENTATION_ENABLED)
                ndk2NspStats.txDroppedPacketCount++;
#endif
            }
            hPBMPacket = My_PBMQ_deq(&hNDK2NSP->txReadyPBMPacketQueue[devIdx]);
        }

        /* Give the accumulated packets to the hardware */
        {
            CPDMA_SubmitPacketQueueIoctlCmd cmd;

            cmd.hChannel                    = hNDK2NSP->hTxChannel;
            cmd.pToChannelQueue             = &tempQueue;

            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_SubmitPacketQueueIoctlCmd));
        }
    }
}

/*!
 *  @b NDK2NSP_ioctl
 *  @n
 *  Low level driver Ioctl interface. This interface can be used for
 *  ALE configuration,control,statistics
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *  \param[in]  cmd
 *      Ioctl command.
 *  \param[in]  pBuf
 *      Ioctl buffer with commands and params to set/get
 *      configuration from hardware.
 *  \param[in]  size
 *      Size of Ioctl buffer.
 *
 *  \retval
 *      void
 */
uint32_t NDK2NSP_ioctl(NDK2NSP_Handle hNDK2NSP, uint32_t cmd, void* param, uint32_t size)
{
    uint32_t retVal = 0U;

    /* Decode the command and act on it */
    switch (cmd)
    {
        /* Rx Task Load IOCTL */
        case NDK2NSP_IOCTL_GET_RXTASK_LOAD:
        {
            Load_Stat stat;
            if (Load_getTaskLoad(hNDK2NSP->rxPacketTask, &stat))
            {
                retVal =  Load_calculateLoad(&stat);
            }
            break;
        }
        /* Adding Tx Task Load  */
        case NDK2NSP_IOCTL_GET_TXTASK_LOAD:
        {
            Load_Stat stat;
            if (Load_getTaskLoad(hNDK2NSP->txPacketTask, &stat))
            {
                retVal =  Load_calculateLoad(&stat);
            }
            break;
        }
        default:
        {
            /* NDK2NSP doesn't have any of its own IOCTL commands, so pass it to the driver */
            retVal = GMACSW_ioctl(hNDK2NSP->hGMACSW, cmd, param, size);
            break;
        }
    }
    return retVal;
}

#if defined (TFDTP_STACK_ENABLED)
/*!
 *  @b NDK2NSP_startTfdtpRx
 *  @n
 *      Routine to start TFDTP receive
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *
 *  \retval
 *      void
 */
void NDK2NSP_startTfdtpRx( NDK2NSP_Handle hNDK2NSP )
{
    hNDK2NSP->tfdtpRxFlag   = TRUE;
}

/*!
 *  @b NDK2NSP_stopTfdtpRx
 *  @n
 *      Routine to stop processing TFDTP receive
 *
 *  \param[in]  hNDK2NSP
 *      NDK2NSP_object structure pointer.
 *
 *  \retval
 *      void
 */
void NDK2NSP_stopTfdtpRx( NDK2NSP_Handle hNDK2NSP )
{
    hNDK2NSP->tfdtpRxFlag   = FALSE;
}

#endif
/*!
 *  @b NDK2NSP_registerPrintFxnCb
 *  @n
 *      Register callback debug print statement with GMAC driver
 *
 *  \param[in]  hNDK2NSP    NDK2NSP_object structure pointer.
 *  \param[in]  printFxn    Pointer to callback function.
 *
 *  \retval
 *      void
 */
void NDK2NSP_registerPrintFxnCb( NDK2NSP_Handle hNDK2NSP, GMACSW_PrintFxnCallback printFxn )
{
    /* Register callback function for NDK2NSP layer */
    hNDK2NSP->printFxnCb = printFxn;

    /* Register same callback function with GMAC driver */
    GMACSW_PrintFxnIoctlCmd cmd;
    cmd.pPrintFxnCallback                    = printFxn;
    /* Set the debug print function callback */
    GMACSW_ioctl(hNDK2NSP->hGMACSW,
                 GMACSW_IOCTL_REGISTER_PRINT_FXN,
                 (void *)&cmd,
                 sizeof(GMACSW_PrintFxnIoctlCmd));
}

/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static void LOCAL_pollingCallback(void *hCallbackArg)
{
    static uint32_t loadCount = 0;
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle) hCallbackArg;
    Load_Stat stat;

    uint32_t prevLinkState[2];
    uint32_t devIdx;
    uint32_t numPorts;

    numPorts = (1U == hNDK2NSP->enableDualMac) ? 2U : 1U;

    for(devIdx = 0; devIdx < numPorts; devIdx++)
    {
        prevLinkState[devIdx] = hNDK2NSP->linkIsUp[devIdx];
    }
    /*
     * If the receive interrupt ran out of PBM packet buffers, allow the system to recover
     * gracefully if buffers are eventually returned.
     */
    LOCAL_resubmitRxPacketQueue(hNDK2NSP);

    ndk2NspStats.gCpuLoad[loadCount] = Load_getCPULoad();

    if (Load_getGlobalHwiLoad(&stat))
    {
        ndk2NspStats.gHwiLoad[loadCount] = Load_calculateLoad(&stat);
    }
    if (Load_getTaskLoad(hNDK2NSP->rxPacketTask, &stat))
    {
        ndk2NspStats.rxStats.taskLoad[loadCount] = Load_calculateLoad(&stat);
    }
    if (Load_getTaskLoad(hNDK2NSP->txPacketTask, &stat))
    {
        ndk2NspStats.txStats.taskLoad[loadCount] = Load_calculateLoad(&stat);
    }

    loadCount = (loadCount + 1U) & (HISTORY_CNT - 1U);

    /* Get current link status as reported by the hardware driver */
    for(devIdx = 0; devIdx < numPorts; devIdx++)
    {
        GMACSW_getLinkStatus(hNDK2NSP->hGMACSW, &hNDK2NSP->linkIsUp[devIdx], devIdx);    
    }

    /* If link status changed from down->up, then send any queued packets */
    for(devIdx = 0; devIdx < numPorts; devIdx++)
    {
        if ((prevLinkState[devIdx] == 0) && (0U != hNDK2NSP->linkIsUp[devIdx]))
        {
            NDK2NSP_sendTxPackets( hNDK2NSP, devIdx);
        }
    }
}

static void LOCAL_closeRxChannel(void *hCallbackArg)
{
    CPDMA_PacketQueue tempQueue;
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle ) hCallbackArg;

    /* Post to rx packet task so that it will terminate (shutDown flag is already set) */
    if (hNDK2NSP->rxPacketTask != NULL)
    {
        SemPost(hNDK2NSP->rxPacketSem);
    }

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * being returned from the hardware.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNDK2NSP->hRxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

#if defined (TFDTP_STACK_ENABLED)
    LOCAL_freeTFDTPPackets(hNDK2NSP, &tempQueue);
#else
    LOCAL_freePBMPackets(hNDK2NSP, &tempQueue);
#endif

}

#if !defined (TFDTP_STACK_ENABLED)
static void LOCAL_freePBMPackets(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *tempQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;
    uint32_t i;
    
    /* Take all PBM packets from the fromHardware queue and put them on the
     * rxFreePBMPacketQueue.
     */
    pCurrCPDMAPacket = CPDMA_packetDequeue(tempQueue);
    
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the PBM packets that need to be freed */
        PBM_Handle hPBMPacket = (PBM_Handle) pCurrCPDMAPacket->hPrivate;

        if (hPBMPacket)
        {
            My_PBMQ_enq(&hNDK2NSP->rxFreePBMPacketQueue, hPBMPacket);
        }
        pCurrCPDMAPacket = CPDMA_packetDequeue(tempQueue);
    }

    /* Free all PBM packets (this should be all of them) */
    for (i = 0U; i< ((uint32_t)NDK_RX_PACKETS); i++)
    {
        PBM_Handle hPBMPacket = My_PBMQ_deq(&hNDK2NSP->rxFreePBMPacketQueue);
        if (hPBMPacket)
        {
            PBM_free(hPBMPacket);
        }
    }
}
#endif

static void LOCAL_closeTxChannel(void *hCallbackArg)
{
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle ) hCallbackArg;
    CPDMA_PacketQueue tempQueue;
    CPDMA_Packet *pCurrCPDMAPacket;

    /* Post to rx packet task so that it will terminate (shutDown flag is already set) */
    SemPost(hNDK2NSP->txPacketSem);
    /*
     * Clear out the fromHardware queue, which should contain all packets
     * being returned from the hardware.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNDK2NSP->hTxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Take all PBM packets from the fromHardware queue and free any
     * PBM attached packets.
     */
    pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the PBM packets that need to be freed */
        PBM_Handle hPBMPacket = (PBM_Handle) pCurrCPDMAPacket->hPrivate;

        if (hPBMPacket)
        {
            PBM_free(hPBMPacket);
        }
        pCurrCPDMAPacket = CPDMA_packetDequeue(&tempQueue);
    }
}

static void LOCAL_notifyRxPackets(void *hCallbackArg)
{
    /* Post semaphore to rx handling task */
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle ) hCallbackArg;

    SemPost(hNDK2NSP->rxPacketSem);
}

static void LOCAL_notifyTxPackets(void *hCallbackArg)
{
    /* Post semaphore to tx handling task */
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle ) hCallbackArg;

    SemPost(hNDK2NSP->txPacketSem);
}

static void LOCAL_rxPacketTask(void *arg0)
{
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle) arg0;
    CPDMA_PacketQueue tempQueue;
#if defined(NSP_INSTRUMENTATION_ENABLED)
    uint32_t time1 = 0;
    uint32_t packetCount;
#endif

    while (0U == hNDK2NSP->shutDown)
    {
        /* Wait for the Rx ISR to notify us that packets are available with data */
        SemPend(hNDK2NSP->rxPacketSem, (uint32_t)SEM_FOREVER);

        if (hNDK2NSP->shutDown)
        {
            /* This translation layer is shutting down, don't give anything else to the stack */
            break;
        }

#if defined(NSP_INSTRUMENTATION_ENABLED)
        time1 = TIMER_READ();
        ndk2NspStats.rxStats.rawNotificationCount++;
        packetCount = 0;
#endif

        /* Retrieve the used (filled) packets from the channel */
        {
            CPDMA_RetrievePacketQueueIoctlCmd cmd;

            CPDMA_packetQueueInit(&tempQueue);

            cmd.hChannel                    = hNDK2NSP->hRxChannel;
            cmd.pFromChannelQueue           = &tempQueue;

            /* This function will initialize the tempQueue variable */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
        }

#if defined(NSP_INSTRUMENTATION_ENABLED)
        if (tempQueue.count == 0)
        {
            ndk2NspStats.rxStats.zeroNotificationCount++;
        }
#endif
        /*
         * Call LOCAL_prepRxPacketQueue() even if no packets were received.
         * This allows new packets to be submitted if PBM buffers became
         * newly available and there were outstanding free packets.
         */
        {
            /*
             * Get all used Rx CPDMA packets from the hardware, then send the buffers
             * of those packets on to the NDK stack to be parsed/processed.
             */
#if defined(NSP_INSTRUMENTATION_ENABLED)
            packetCount =
#endif
            LOCAL_prepRxPacketQueue(hNDK2NSP, &tempQueue);
        }
#if defined(NSP_INSTRUMENTATION_ENABLED)
        /*
         * We don't want to time the semaphore post used to notify the NDK stack as that may cause a
         * task transition. We don't want to time the semaphore pend, since that would time us doing
         * nothing but waiting.
         */
        if (packetCount != 0)
        {
            uint32_t notificationCount;
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
            uint32_t timePerPacket = timeDiff/packetCount;

            notificationCount = ndk2NspStats.rxStats.dataNotificationCount & (HISTORY_CNT - 1U);
            ndk2NspStats.rxStats.dataNotificationCount++;

            ndk2NspStats.rxStats.totalPacketCnt += packetCount;
            ndk2NspStats.rxStats.totalCycleCnt += timeDiff;

            ndk2NspStats.rxStats.cycleCountPerNotification[notificationCount] = timeDiff;
            if (timeDiff > ndk2NspStats.rxStats.cycleCountPerNotificationMax)
            {
                ndk2NspStats.rxStats.cycleCountPerNotificationMax = timeDiff;
            }

            ndk2NspStats.rxStats.packetsPerNotification[notificationCount] = packetCount;
            if (packetCount > ndk2NspStats.rxStats.packetsPerNotificationMax)
            {
                ndk2NspStats.rxStats.packetsPerNotificationMax = packetCount;
            }

            ndk2NspStats.rxStats.cycleCountPerPacket[notificationCount] = timePerPacket;
            if (timePerPacket >ndk2NspStats.rxStats.cycleCountPerPacketMax)
            {
                ndk2NspStats.rxStats.cycleCountPerPacketMax = timePerPacket;
            }
        }
#endif
        /* Notify NDK stack that packets are available (this is basically a SemPost) */
        uint32_t isPacketAvailable;
        if(1U == hNDK2NSP->enableDualMac)
        {
            isPacketAvailable = (uint32_t)((PBMQ_count(&hNDK2NSP->rxReadyPBMPacketQueue[0]) != 0U) || \
                                           (PBMQ_count(&hNDK2NSP->rxReadyPBMPacketQueue[1]) != 0U));
        }
        else
        {
            isPacketAvailable = (uint32_t)(PBMQ_count(&hNDK2NSP->rxReadyPBMPacketQueue[0]) != 0U);
        }

        if (isPacketAvailable)
        {
            ((STKEVENT *)(hNDK2NSP->hEvent))->EventCodes[STKEVENT_ETHERNET] = 1U;
            if( ((STKEVENT *)(hNDK2NSP->hEvent))->hSemEvent != NULL)
            {
                SemPost( ((STKEVENT *)(hNDK2NSP->hEvent))->hSemEvent );
            }
#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.ndkStackNotifyCount++;
#endif
        }
#if defined (TFDTP_STACK_ENABLED)
        if (hNDK2NSP->rxReadyTFDTPPacketQueue.count != 0U)
        {
#if (1 == TFDTP_DEBUG)
            LOCAL_discardTFDTPPackets(hNDK2NSP);
#else
            /* A function pointer could be used here - but a direct call is used instead
             * so a link-time optimization can occur
             */
            TFDTP_processRxPackets(hNDK2NSP->hTfdtp, &hNDK2NSP->rxReadyTFDTPPacketQueue);
#endif
        }
#endif
    }

    /* We are shutting down, notify that we are done */
    SemPost(hNDK2NSP->shutDownSem);
}

static void LOCAL_txPacketTask(void *arg0)
{
    NDK2NSP_Handle hNDK2NSP = (NDK2NSP_Handle) arg0;
    CPDMA_PacketQueue tempQueue;

#if defined(NSP_INSTRUMENTATION_ENABLED)
    uint32_t time1 = 0;
    uint32_t packetCount = 0;
#endif

    while (0U == hNDK2NSP->shutDown)
    {
        /*
         * Wait for the Tx ISR to notify us that empty packets are available
         * that were used to send data
         */
        SemPend(hNDK2NSP->txPacketSem, (uint32_t)SEM_FOREVER);
#if defined(NSP_INSTRUMENTATION_ENABLED)
        time1 = TIMER_READ();
        ndk2NspStats.txStats.rawNotificationCount++;
        packetCount = 0;
#endif

        /* Retrieve the used (sent/empty) packets from the channel */
        {
            CPDMA_RetrievePacketQueueIoctlCmd cmd;

            CPDMA_packetQueueInit(&tempQueue);

            cmd.hChannel                    = hNDK2NSP->hTxChannel;
            cmd.pFromChannelQueue           = &tempQueue;

            /* This function will initialize the tempQueue variable */
            GMACSW_ioctl(hNDK2NSP->hGMACSW,
                        GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                        (void *)&cmd,
                        sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
        }

        if (tempQueue.count != 0U)
        {
            /*
             * Get all used Tx CPDMA packets from the hardware, then return those
             * buffers to the txFreePacketQueue so they can be used later to send with.
             */
#if defined(NSP_INSTRUMENTATION_ENABLED)
            packetCount =
#endif
            LOCAL_prepTxPacketQueue(hNDK2NSP, &tempQueue);
        }
#if defined(NSP_INSTRUMENTATION_ENABLED)
        else
        {
            ndk2NspStats.txStats.zeroNotificationCount++;
        }

        if (packetCount != 0)
        {
            uint32_t notificationCount;
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);
            uint32_t timePerPacket = timeDiff/packetCount;

            notificationCount = ndk2NspStats.txStats.dataNotificationCount & (HISTORY_CNT - 1U);
            ndk2NspStats.txStats.dataNotificationCount++;

            ndk2NspStats.txStats.totalPacketCnt += packetCount;
            ndk2NspStats.txStats.totalCycleCnt += timeDiff;

            ndk2NspStats.txStats.cycleCountPerNotification[notificationCount] = timeDiff;
            if (timeDiff > ndk2NspStats.txStats.cycleCountPerNotificationMax)
            {
                ndk2NspStats.txStats.cycleCountPerNotificationMax = timeDiff;
            }

            ndk2NspStats.txStats.packetsPerNotification[notificationCount] = packetCount;
            if (packetCount > ndk2NspStats.txStats.packetsPerNotificationMax)
            {
                ndk2NspStats.txStats.packetsPerNotificationMax = packetCount;
            }

            ndk2NspStats.txStats.cycleCountPerPacket[notificationCount] = timePerPacket;
            if (timePerPacket >ndk2NspStats.txStats.cycleCountPerPacketMax)
            {
                ndk2NspStats.txStats.cycleCountPerPacketMax = timePerPacket;
            }
        }
#endif
    }

    /* We are shutting down, notify that we are done */
    SemPost(hNDK2NSP->shutDownSem);
}

static void LOCAL_allocRxPackets(NDK2NSP_Handle hNDK2NSP)
{
    uint32_t i;

#if defined (TFDTP_STACK_ENABLED)
    /* Clear the entire array as we'd like to avoid releasing
    * garbage edma channels during teardown when failing to
    * obtain a PaRAM set from setEdmaParam below
    */
    memset(gTFDTPRxPackets, 0, sizeof(gTFDTPRxPackets));
#endif
    /*
     * Pre-allocate twice as many NDK stack packets as we plan to give to/get from the hardware.
     * The idea here is that even if we fill up all the buffer descriptors in the inUse
     * queue, we will have another complete set to swap in right away.
     */
    for (i = 0U; i < ((uint32_t)NDK_RX_PACKETS); i++)
    {
        PBM_Handle hPBMPacket = PBM_alloc((uint)(hNDK2NSP->PktMTU + (uint32_t)4U + PKT_PREPAD));
        if (hPBMPacket)
        {
#if defined (TFDTP_STACK_ENABLED)
            /* Create TFDTP private data structure for EDMA bookkeeping information */
            gTFDTPRxPackets[i].hPBMPacket = hPBMPacket;
            TFDTP_enqueue(&hNDK2NSP->rxFreeTFDTPNDKPacketQueue, (node_t *)&gTFDTPRxPackets[i]);
#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.rxFreeTFDTPPBMPacketEnqueue++;
#endif
#else
            /* Enqueue to the free queue */
            My_PBMQ_enq(&hNDK2NSP->rxFreePBMPacketQueue, hPBMPacket);

#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.rxFreePBMPacketEnqueue++;
#endif
#endif
        }
        else
        {
            LOCAL_print("ERROR: PBM_alloc() failure...exiting!\n");
            LOCAL_print("PBMQ_free count = %d\n",PBMQ_count(&PBMQ_free));
            exit(1);
        }
}

}

static void LOCAL_submitRxPackets(NDK2NSP_Handle hNDK2NSP)
{
    CPDMA_PacketQueue tempQueue;

    /*
     * Get the contents of the fromHardware queue, which should contain all packets
     * initially allocated by the channel open function.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNDK2NSP->hRxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Go through packets in the queue, prep them to give to the
     * CPDMA Rx channel, then submit them to the channel
     */
    LOCAL_prepRxPacketQueue(hNDK2NSP, &tempQueue);
}

static void LOCAL_allocTxPackets(NDK2NSP_Handle hNDK2NSP)
{
    CPDMA_PacketQueue tempQueue;

    /*
     * Clear out the fromHardware queue, which should contain all packets
     * initially allocated by the channel open function.
     */
    {
        CPDMA_RetrievePacketQueueIoctlCmd cmd;

        CPDMA_packetQueueInit(&tempQueue);

        cmd.hChannel                    = hNDK2NSP->hTxChannel;
        cmd.pFromChannelQueue           = &tempQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                     GMACSW_IOCTL_CPDMA_RETRIEVE_PACKETS,
                     (void *)&cmd,
                     sizeof(CPDMA_RetrievePacketQueueIoctlCmd));
    }

    /*
     * Go through the CPDMA packets in the queue, and move them to the
     * txFreeCPDMAPacketQueue so they are ready to be used when the stack
     * wants to send a packet
     */
    LOCAL_prepTxPacketQueue(hNDK2NSP, &tempQueue);
}

/*
 * Enqueue a new packet and make sure that buffer descriptors are properly linked.
 * NOTE: Not thread safe
 */
static void LOCAL_resubmitRxPacketQueue(NDK2NSP_Handle hNDK2NSP)
{
#if defined(TFDTP_STACK_ENABLED)
    LOCAL_resubmitTfdtpRxPacketQueue(hNDK2NSP);
#else
    CPDMA_PacketQueue resubmitPacketQueue;

    CPDMA_packetQueueInit(&resubmitPacketQueue);
    /*
     * Fill in as many packets as we can with new PBM buffers so they can be
     * returned to the stack to be filled in.
     */
    while (CPDMA_getPacketQueueCount(&hNDK2NSP->rxFreePacketQueue) != 0)
    {
        /* Dequeue an empty PBM packet to be associated with a CPDMA packet for the hardware*/
        PBM_Handle hPBMPacket = My_PBMQ_deq(&hNDK2NSP->rxFreePBMPacketQueue);
        if (hPBMPacket)
        {
            CPDMA_Packet *pCurrCPDMAPacket = CPDMA_packetDequeue(&hNDK2NSP->rxFreePacketQueue);
            CPDMA_BuffDesc *pBuffDesc = 0;

            if (pCurrCPDMAPacket == NULL)
            {
                /* return our PBM and exit loop */
                My_PBMQ_enq(&hNDK2NSP->rxFreePBMPacketQueue, hPBMPacket);
                break;
            }
            pBuffDesc = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);

#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.rxFreePBMPacketDequeue++;
#endif
            uint8_t *buffer                     = PBM_getDataBuffer(hPBMPacket);
            uint32_t length                     = PBM_getBufferLen(hPBMPacket);

            /* The PBM packet has a data offset */
            PBM_setDataOffset( hPBMPacket, PKT_PREPAD );

            /* Save off the PBM packet handle so it can be handled by this layer later */
            pCurrCPDMAPacket->hPrivate          = (void *)hPBMPacket;

            /* The CPDMA buffer should skip past the NDK prepad */
            pBuffDesc->pDataBuffer              = buffer+PKT_PREPAD;
            pBuffDesc->bufferOffsetAndLength    = length-PKT_PREPAD;
            /* Mark the packet as owned by the hardware */
            pBuffDesc->flagsAndPacketLength     = CPDMA_BUF_DESC_OWNER_FLAG;

#if defined(DATA_BUFFERS_IN_CACHED_MEMORY)
            /*
             * Pre-invalidate the data buffer so that no spurious evictions will possibly
             * corrupt the packet buffer while the hardware CPDMA has ownership. We invalidate
             * the entire buffer since we don't know how big the arriving packets will be.
             */
            Cache_inv((Ptr)buffer,
                      (SizeT)length,
                      (Bits16)Cache_Type_ALLD,
                      (Bool)1U);
#endif

            if (resubmitPacketQueue.pTail)
            {
                CPDMA_BuffDesc *pBuffDescTail = CPDMA_packetGetFirstDesc(resubmitPacketQueue.pTail);
                pBuffDescTail->pNextBufferDescriptor = pBuffDesc;
            }
            pBuffDesc->pNextBufferDescriptor = NULL;
            CPDMA_packetEnqueue(&resubmitPacketQueue, pCurrCPDMAPacket);
        }
        else
        {
            break;
        }
    }
    /*
     * Return the same CPDMA packets back to the CPDMA channel (but now
     * associated with a new PBM Packet and buffer)
     */
    if (resubmitPacketQueue.count != 0)
    {
        CPDMA_SubmitPacketQueueIoctlCmd cmd;

        cmd.hChannel                    = hNDK2NSP->hRxChannel;
        cmd.pToChannelQueue             = &resubmitPacketQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                    GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS,
                    (void *)&cmd,
                    sizeof(CPDMA_SubmitPacketQueueIoctlCmd));
    }
#endif
}

static uint32_t LOCAL_prepRxPacketQueue(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *pPacketQueue)
{
    uint32_t packetCount = 0;

#if defined (TFDTP_STACK_ENABLED)
    packetCount = LOCAL_prepTFDTPRxPacketQueue(hNDK2NSP, pPacketQueue);
#else
    CPDMA_Packet *pCurrCPDMAPacket;

    pCurrCPDMAPacket = pPacketQueue->pHead;
    while (pCurrCPDMAPacket)
    {
        /* Get the full PBM packet that needs to be returned to the NDK stack */
        PBM_Handle hPBMPacket = (PBM_Handle) pCurrCPDMAPacket->hPrivate;
        if (hPBMPacket)
        {
            uint32_t validLen = CPDMA_packetGetLength(pCurrCPDMAPacket) - 4U;
            
            CPDMA_BuffDesc* pBuffDesc = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);
            uint32_t fromPort = CPDMA_getRxFromPort(pBuffDesc);
            /* Fill in PBM packet length field */
            PBM_setValidLen(hPBMPacket, validLen);

#if defined(DATA_BUFFERS_IN_CACHED_MEMORY)
#if defined(CORTEX_AX)
            /*
             * Invalidate the data buffer so the CPU is forced to read new data from HW.
             * We only need to so this on the Cortex v7A devices because of possible
             * speculative reads done by the CPU core while the buffers are owned by the
             * CPDMA hardware.
             */
            {
                uint8_t *buffer             = PBM_getDataBuffer(hPBMPacket);
                uint32_t length             = validLen + PKT_PREPAD;
                Cache_inv((Ptr)buffer,
                      (SizeT)length,
                      (Bits16)Cache_Type_ALLD,
                      (Bool)1U);
            }
#endif
#endif

            /* Enqueue the received packet so that it can be consumed by the NDK stack*/
            My_PBMQ_enq(&hNDK2NSP->rxReadyPBMPacketQueue[fromPort-1U], hPBMPacket);

#if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.rxReadyPBMPacketEnqueue[fromPort-1U]++;
#endif
            packetCount++;
        }

        /*
         * Add the current packet to the queue of packets which can be returned GMACSW
         * after they are associated with new PBM packet buffers
         */
        pCurrCPDMAPacket->hPrivate = NULL;
        pCurrCPDMAPacket = pCurrCPDMAPacket->pNextPacket;
    }

    /*
     * We have removed the PBM buffers from the Rx packets, now add them
     * back to the pool ready to be returned back to the GMACSW layer
     */
    if (pPacketQueue->count)
    {
      uint32_t key = GMACSW_AL_globalInterruptDisable();

      CPDMA_appendPacketQueue(&hNDK2NSP->rxFreePacketQueue, pPacketQueue);
      GMACSW_AL_globalInterruptEnable(key);
    }

    CPDMA_packetQueueInit(pPacketQueue);
    /* return as many packets to GMACSW as we can */
    LOCAL_resubmitRxPacketQueue(hNDK2NSP);
#endif

    return packetCount;
}

static uint32_t LOCAL_prepTxPacketQueue(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *pPacketQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;

    uint32_t packetCount = 0;

    pCurrCPDMAPacket = pPacketQueue->pHead;
    while (pCurrCPDMAPacket)
    {
        PBM_Handle hPBMPacket = (PBM_Handle) pCurrCPDMAPacket->hPrivate;

        /* Free the packet - it was allocated by the stack/sender */
        if (hPBMPacket)
        {
            PBM_free(hPBMPacket);
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
        CPDMA_appendPacketQueue(&hNDK2NSP->txFreeCPDMAPacketQueue, pPacketQueue);

        /* Clear the input queue */
        CPDMA_packetQueueInit(pPacketQueue);

        GMACSW_AL_globalInterruptEnable(key);
    }

#if defined(NSP_INSTRUMENTATION_ENABLED)
    ndk2NspStats.txFreeCPDMAPacketEnqueue += packetCount;
#endif

    return packetCount;
}


static inline void LOCAL_print(char *prnStr, ...)
{
    static char str[100];

    if (NULL != LOCAL_ndk2nspRef->printFxnCb)
    {
        /* Function is non- reentrant */
        snprintf (str, 100U, prnStr);
        (*LOCAL_ndk2nspRef->printFxnCb)(str);
    }
    else
    {
#if defined (DEBUG)
        printf(prnStr);
#endif
    }
}

#if defined (TFDTP_STACK_ENABLED)
static uint32_t LOCAL_prepTFDTPRxPacketQueue(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *pPacketQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;
    TFDTP_RxPacket *hTFDTPPacket;
    uint32_t packetCount = 0;
    uint8_t length;
    uint8_t *pBuffer;
    uint32_t fromPort;

    /*
     * TFDTP_processRxPackets is asynchronous so it may have held packets; if there
     * aren't enough free TFDTP packets available then we must wait until more become available.
     */
    if (hNDK2NSP->rxFreeTFDTPNDKPacketQueue.count < pPacketQueue->count)
    {
        TFDTP_waitPendingRxPackets(hNDK2NSP->hTfdtp);
    }

    pCurrCPDMAPacket = pPacketQueue->pHead;
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the full PBM packet that needs to be returned to the NDK stack */
        hTFDTPPacket = (TFDTP_RxPacket *) pCurrCPDMAPacket->hPrivate;

        if (hTFDTPPacket != NULL)
        {
            /* Fill in the packet size as returned by the hardware */
            uint32_t validLen = CPDMA_packetGetLength(pCurrCPDMAPacket) - 4U;
            CPDMA_BuffDesc* pBuffDesc = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);
            fromPort = CPDMA_getRxFromPort(pBuffDesc);

            /* Fill in PBM packet length field */
            PBM_setValidLen(hTFDTPPacket->hPBMPacket, validLen);
#if defined(DATA_BUFFERS_IN_CACHED_MEMORY)
#if defined(CORTEX_AX)
            /*
             * Invalidate the data buffer so the CPU is forced to read new data from HW.
             * We only need to so this on the Cortex v7A devices because of possible
             * speculative reads done by the CPU core while the buffers are owned by the
             * CPDMA hardware.
             */
            {
                pBuffer                     = PBM_getDataBuffer(hTFDTPPacket->hPBMPacket);
                length             = validLen + PKT_PREPAD;
                Cache_inv((Ptr)pBuffer,
                      (SizeT)length,
                      (Bits16)Cache_Type_ALLD,
                      (Bool)1U);
            }
#endif
#endif
            /* Packet inspection for checking if packet belongs to NDK or TFDTP */
            pBuffer = PBM_getDataBuffer(hTFDTPPacket->hPBMPacket);
            if ( (TRUE == LOCAL_checkTfdtpPacket(pBuffer, hNDK2NSP->hTfdtp->rxUdpPort)) &&
                                            (TRUE == hNDK2NSP->tfdtpRxFlag) )
            {
                /* Enqueue the receive packet so that it can be consumed by the TFDTP layer */
                TFDTP_enqueue(&hNDK2NSP->rxReadyTFDTPPacketQueue, (node_t *)hTFDTPPacket);
#if defined(NSP_INSTRUMENTATION_ENABLED)
                ndk2NspStats.rxReadyTFDTPPacketEnqueue++;
#endif
            }
            else
            {
                /* Enqueue the received packet so that it can be consumed by the NDK stack*/
                My_PBMQ_enq(&hNDK2NSP->rxReadyPBMPacketQueue[fromPort-1U], hTFDTPPacket->hPBMPacket);
#if defined(NSP_INSTRUMENTATION_ENABLED)
                ndk2NspStats.rxReadyPBMPacketEnqueue[fromPort-1U]++;
#endif
                /* Add back TFDTP_RxPacket back to free pool as it's payload belongs to NDK */
                PBM_Handle hPBMPacket = PBM_alloc((uint)(hNDK2NSP->PktMTU + (uint32_t)4U + PKT_PREPAD));
                if (NULL == hPBMPacket)
                {
                    LOCAL_print("ERROR: PBM_alloc() failure...exiting!\n");
                    LOCAL_print("PBMQ_free count = %d\n",PBMQ_count(&PBMQ_free));
                    exit(1);
                }
                else
                {
                    uint8_t *pBuffer = PBM_getDataBuffer(hPBMPacket);
                    length  = PBM_getBufferLen(hPBMPacket);
#if defined(DATA_BUFFERS_IN_CACHED_MEMORY)
                    /* TODO review if this is correct */
                    /*
                    * Pre-invalidate the data buffer so that no spurious evictions will possibly
                    * corrupt the packet buffer while the hardware CPDMA has ownership. We invalidate
                    * the entire buffer since we don't know how big the arriving packets will be.
                    */
                    Cache_inv((Ptr)pBuffer,
                            (SizeT)length,
                            (Bits16)Cache_Type_ALLD,
                            (Bool)1U);
#endif
                    hTFDTPPacket->hPBMPacket = hPBMPacket;
                    LOCAL_setEdmaParamSrcAddress(hTFDTPPacket);
                }

                TFDTP_enqueue(&hNDK2NSP->rxFreeTFDTPNDKPacketQueue,          (node_t *)hTFDTPPacket);
#if defined(NSP_INSTRUMENTATION_ENABLED)
                ndk2NspStats.rxFreeTFDTPPBMPacketEnqueue++;
#endif
            }
            packetCount++;
        }

        /*
         * Add the current packet to the queue of packets which can be returned GMACSW
         * after they are associated with new PBM packet buffers
         */
        pCurrCPDMAPacket->hPrivate = NULL;
        pCurrCPDMAPacket = pCurrCPDMAPacket->pNextPacket;
    }
    /*
     * We have removed the PBM buffers from the Rx packets, now add them
     * back to the pool ready to be returned back to the GMACSW layer
     */
    if (pPacketQueue->count)
    {
      uint32_t key = GMACSW_AL_globalInterruptDisable();

      CPDMA_appendPacketQueue(&hNDK2NSP->rxFreePacketQueue, pPacketQueue);
      GMACSW_AL_globalInterruptEnable(key);
    }

    CPDMA_packetQueueInit(pPacketQueue);

    /* return as many packets to GMACSW as we can */
    LOCAL_resubmitRxPacketQueue(hNDK2NSP);

    return packetCount;
}
#endif

#if defined (TFDTP_STACK_ENABLED)
static inline uint32_t LOCAL_checkTfdtpPacket(uint8_t *buffer, uint32_t rxUdpPort)
{
    uint32_t tfdtpPktFlag = FALSE;

    ether_frame_t *eth_frame = (ether_frame_t *)(buffer + PKT_PREPAD);
    tfdtp_stream_header_t *eth_payload = (tfdtp_stream_header_t *)(&eth_frame->payload);

    /* Invalidate both ethernet & payload header so dont have to do again if
     * ethertype matches IPv4 */
    Cache_inv((Ptr)buffer, TFDTP_PACKET_HEADER_SIZE, (Bits16)Cache_Type_ALLD, (Bool)1U);
    if ( (eth_frame->header.etherType == ntohs(ETHERTYPE_IPV4)) &&
                    (eth_payload->ip_hdr.Protocol == IPPROTO_UDP) )
    {
        if (eth_payload->udp_hdr.DstPort == ntohs(rxUdpPort))
        {
            tfdtpPktFlag = TRUE;
        }
    }

    return tfdtpPktFlag;
}
#endif

#if defined (TFDTP_STACK_ENABLED)
static void LOCAL_setEdmaParamSrcAddress(TFDTP_RxPacket *pPacket)
{
    /* We know TFDTP packet will always come through Eth interface and not thru
     * PPPoE so add PKT_PREPAD to data buffer */
    uint8_t *pBuffer = PBM_getDataBuffer(pPacket->hPBMPacket) + PKT_PREPAD;
    /* Double cast to avoid MISRA-C:2004 11.4 */
    ether_frame_t *frame = (ether_frame_t *)((void *)pBuffer);
    tfdtp_stream_packet_t *tfdtpsp = (tfdtp_stream_packet_t *)frame->payload;

    /* This needs to be done for as buffer is reallocated to this packet due to
     * packet belonging to NDK */
    pPacket->pEdmaParams->SRC = (uint32_t)tfdtpsp->payload;
    pPacket->pEdmaParams->CCNT = 1U;
}
#endif

#if defined (TFDTP_STACK_ENABLED)
static inline void LOCAL_freeTFDTPPackets(NDK2NSP_Handle hNDK2NSP, CPDMA_PacketQueue *tempQueue)
{
    CPDMA_Packet *pCurrCPDMAPacket;
    uint32_t i;

    /* Take all TFDTP Rx packets from the fromHardware queue and put them on the
     * rxFreeTFDTPNDKPacketQueue.
     */
    pCurrCPDMAPacket = CPDMA_packetDequeue(tempQueue);
    while (NULL != pCurrCPDMAPacket)
    {
        /* Get the PBM packets that need to be freed */
        TFDTP_RxPacket *hTFDTPPacket = (TFDTP_RxPacket *) pCurrCPDMAPacket->hPrivate;

        if (hTFDTPPacket)
        {
            TFDTP_enqueue(&hNDK2NSP->rxFreeTFDTPNDKPacketQueue, (node_t *)hTFDTPPacket);
        }
        pCurrCPDMAPacket = CPDMA_packetDequeue(tempQueue);
    }

    /* Free all PBM packets (this should be all of them) */
    for (i = 0U; i< ((uint32_t)NDK_RX_PACKETS); i++)
    {
        TFDTP_RxPacket *hTFDTPPacket = (TFDTP_RxPacket *)TFDTP_dequeue(&hNDK2NSP->rxFreeTFDTPNDKPacketQueue);
        PBM_Handle hPBMPacket = hTFDTPPacket->hPBMPacket;
        if (hPBMPacket)
        {
            PBM_free(hPBMPacket);
        }
    }
}
#endif

#if defined (TFDTP_STACK_ENABLED)
/*
 * Enqueue a new packet and make sure that buffer descriptors are properly linked.
 * NOTE: Not thread safe
 */
static void LOCAL_resubmitTfdtpRxPacketQueue(NDK2NSP_Handle hNDK2NSP)
{
    CPDMA_PacketQueue resubmitPacketQueue;
    TFDTP_RxPacket *hTFDTPPacket;

    CPDMA_packetQueueInit(&resubmitPacketQueue);

    /*
     * Fill in as many packets as we can with new PBM buffers so they can be
     * returned to the stack to be filled in.
     */
    while (CPDMA_getPacketQueueCount(&hNDK2NSP->rxFreePacketQueue) != 0)
    {

        hTFDTPPacket = (TFDTP_RxPacket *)TFDTP_dequeue (&hNDK2NSP->rxFreeTFDTPNDKPacketQueue);

        if (hTFDTPPacket)
        {
            PBM_Handle hPBMPacket = hTFDTPPacket->hPBMPacket;
            #if defined(NSP_INSTRUMENTATION_ENABLED)
            ndk2NspStats.rxFreeTFDTPPBMPacketDequeue++;
            #endif
            CPDMA_Packet *pCurrCPDMAPacket = CPDMA_packetDequeue(&hNDK2NSP->rxFreePacketQueue);
            if (pCurrCPDMAPacket == NULL)
            {
              /* return our PBM and exit loop */
              TFDTP_enqueue (&hNDK2NSP->rxFreeTFDTPNDKPacketQueue, (node_t *)hTFDTPPacket);
              break;
            }
            /* Link the new PBM packet to the CPDMA packet */
            CPDMA_BuffDesc *pBuffDesc           = CPDMA_packetGetFirstDesc(pCurrCPDMAPacket);
            uint8_t *buffer                     = PBM_getDataBuffer(hPBMPacket);
            uint32_t length                              = PBM_getBufferLen(hPBMPacket);

            /* The PBM packet has a data offset */
            PBM_setDataOffset( hPBMPacket, PKT_PREPAD );

            /* Save off the PBM packet handle so it can be handled by this layer later */
            pCurrCPDMAPacket->hPrivate          = (void *)hTFDTPPacket;;

            /* The CPDMA buffer should skip past the NDK prepad */
            pBuffDesc->pDataBuffer              = buffer+PKT_PREPAD;
            pBuffDesc->bufferOffsetAndLength    = length-PKT_PREPAD;
            /* Mark the packet as owned by the hardware */
            pBuffDesc->flagsAndPacketLength     = CPDMA_BUF_DESC_OWNER_FLAG;

            #if defined(DATA_BUFFERS_IN_CACHED_MEMORY)
            /* TODO review if this is correct */
            /*
             * Pre-invalidate the data buffer so that no spurious evictions will possibly
             * corrupt the packet buffer while the hardware CPDMA has ownership. We invalidate
             * the entire buffer since we don't know how big the arriving packets will be.
             */
            Cache_inv((Ptr)buffer,
                      (SizeT)length,
                      (Bits16)Cache_Type_ALLD,
                      (Bool)1U);
            #endif

            if (resubmitPacketQueue.pTail)
            {
                CPDMA_BuffDesc *pBuffDescTail = CPDMA_packetGetFirstDesc(resubmitPacketQueue.pTail);
                pBuffDescTail->pNextBufferDescriptor = pBuffDesc;
            }
            pBuffDesc->pNextBufferDescriptor = NULL;
            CPDMA_packetEnqueue(&resubmitPacketQueue, pCurrCPDMAPacket);
        }
        else
        {
          break;
        }
    }

    /*
     * Return the same CPDMA packets back to the CPDMA channel (but now
     * associated with a new PBM Packet and buffer)
     */
    if (resubmitPacketQueue.count != 0)
    {
        CPDMA_SubmitPacketQueueIoctlCmd cmd;

        cmd.hChannel                    = hNDK2NSP->hRxChannel;
        cmd.pToChannelQueue             = &resubmitPacketQueue;

        GMACSW_ioctl(hNDK2NSP->hGMACSW,
                    GMACSW_IOCTL_CPDMA_SUBMIT_PACKETS,
                    (void *)&cmd,
                    sizeof(CPDMA_SubmitPacketQueueIoctlCmd));
    }
}
#endif

#if defined (TFDTP_STACK_ENABLED) && (1 == TFDTP_DEBUG)
static void LOCAL_discardTFDTPPackets(NDK2NSP_Handle hNDK2NSP)
{
    TFDTP_RxPacket *hTFDTPPacket = (TFDTP_RxPacket *)TFDTP_dequeue(&hNDK2NSP->rxReadyTFDTPPacketQueue);

    while (NULL != hTFDTPPacket)
    {
        /* Immediately releasing TFDTP_RxPacket and associated PBM packet as well */
        TFDTP_enqueue(&hNDK2NSP->rxFreeTFDTPNDKPacketQueue, (node_t *)hTFDTPPacket);
#if defined(NSP_INSTRUMENTATION_ENABLED)
                ndk2NspStats.rxFreeTFDTPPBMPacketEnqueue++;
#endif
        /* Get the PBM packets that need to be freed */
        hTFDTPPacket = (TFDTP_RxPacket *)TFDTP_dequeue(&hNDK2NSP->rxReadyTFDTPPacketQueue);
#if defined(NSP_INSTRUMENTATION_ENABLED)
        ndk2NspStats.rxReadyTFDTPPacketDequeue++;
#endif
    }
}
#endif

void My_PBMQ_enq(PBMQ *pQ, PBM_Handle hPkt)
{
    SemPend(LOCAL_ndk2nspRef->pbmQAccessSem, (uint32_t)SEM_FOREVER);
    PBMQ_enq(pQ, hPkt);
    SemPost(LOCAL_ndk2nspRef->pbmQAccessSem);
}

PBM_Handle My_PBMQ_deq(PBMQ *pQ)
{
    PBM_Pkt *pPkt;
    SemPend(LOCAL_ndk2nspRef->pbmQAccessSem, (uint32_t)SEM_FOREVER);
    pPkt = PBMQ_deq(pQ);
    SemPost(LOCAL_ndk2nspRef->pbmQAccessSem);
    return pPkt;
}
/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

