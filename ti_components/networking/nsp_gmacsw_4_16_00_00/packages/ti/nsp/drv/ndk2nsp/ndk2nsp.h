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
 *   \file  ndk2nsp.h
 *
 *   \brief
 *      Header file for ethernet packet driver written using the NIMU
 *      Packet Architecture Guidelines
 *
 */


#ifndef NDK2NSP_H_
#define NDK2NSP_H_

#ifdef __cplusplus
extern "C" {
#endif


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdint.h>

/* OS/Posix headers */

/* NDK Dependencies */
#include <ti/ndk/inc/stkmain.h>

/* Project dependency headers */
#include "gmacsw.h"

#if defined (TFDTP_STACK_ENABLED)
#include "tfdtp_queue.h"
#endif

/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/*
 * Packet count of packets given to the hardware. We should use twice this number
 * for the number of packets maintained
 */
/*RX packets to be kept 128 to account for DUAL MAC and TFDTP enabled case*/
#define NDK2NSP_RX_PACKETS   (128U)
#define NDK2NSP_TX_PACKETS   (64U)

#define NDK_RX_PACKETS (NDK2NSP_RX_PACKETS * (uint32_t)2U)

/*
 * This should be set when allocated buffers are in cacheable memory of the current
 * CPU
 */
#define     DATA_BUFFERS_IN_CACHED_MEMORY

/*
 * Pre-Pad Packet Data Offset
 *
 *   The TCP/IP stack library requires that every packet device
 *   include enough L2 header room for all supported headers. In
 *   order to support PPPoE, this requires a 22 byte L2 header.
 *   Thus, since standard Ethernet is only 14 bytes, we must add
 *   on an additional 8 byte offset, or PPPoE can not function
 *   with our driver.
*/
#define     PKT_PREPAD                      ((uint32_t)8U)

/* Indicates whether RAM based multicast lists are suported for this
 * GMACSW peripheral.
 */
#define     RAM_MCAST                       0U

/* Indicates whether HASH based multicasting is suported for this
 * GMACSW peripheral.
 */
#define     HASH_MCAST                      0U

/* Multicast Address List Size */
#define     PKT_MAX_MCAST                   ((uint32_t)31U)


/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

enum NDK2NSP_IOCTL_
{
    NDK2NSP_IOCTL_BASE                   = 0x00000000,
    /*! NDK2NSP get rxPacketTask load function IOCTL value. IOCTL param is empty */
    /* IMP: Taking this value as it should not conflict with GMACSW IOCTL commands */
    NDK2NSP_IOCTL_GET_RXTASK_LOAD        = 0x0000ABAA,
    /*! NDK2NSP get txPacketTask load function IOCTL value. IOCTL param is empty */
    /* IMP: Taking this value as it should not conflict with GMACSW IOCTL commands */
    NDK2NSP_IOCTL_GET_TXTASK_LOAD        = 0x0000ABAB
};

#define HISTORY_CNT ((uint32_t)256U)

typedef struct NDK2NSP_PACKET_TASK_STATS_
{
#if defined(NSP_INSTRUMENTATION_ENABLED)
    uint32_t rawNotificationCount;
    uint32_t dataNotificationCount;
    uint32_t zeroNotificationCount;
    uint32_t totalPacketCnt;
    uint32_t totalCycleCnt;

    uint32_t packetsPerNotificationMax;
    uint32_t packetsPerNotification[HISTORY_CNT];
    uint32_t cycleCountPerNotificationMax;
    uint32_t cycleCountPerNotification[HISTORY_CNT];
    uint32_t cycleCountPerPacketMax;
    uint32_t cycleCountPerPacket[HISTORY_CNT];
#endif
    uint32_t taskLoad[HISTORY_CNT];
}
NDK2NSP_PacketTaskStats;

typedef struct NDK2NSP_STATS_
{
    NDK2NSP_PacketTaskStats rxStats;
#if defined(NSP_INSTRUMENTATION_ENABLED)
    uint32_t rxReadyPBMPacketEnqueue[MAC_NUM_PORTS];
    uint32_t rxUnderFlowCount;
    uint32_t rxReadyPBMPacketDequeue[MAC_NUM_PORTS];
#if defined TFDTP_STACK_ENABLED
    uint32_t rxReadyTFDTPPacketEnqueue;
    uint32_t rxReadyTFDTPPacketDequeue;
    uint32_t rxFreeTFDTPPBMPacketEnqueue;
    uint32_t rxFreeTFDTPPBMPacketDequeue;
#else
    /* If TFDTP stack is enabled, we use TFDTP RX Packet Q for packet allocation */
    uint32_t rxFreePBMPacketEnqueue;
    uint32_t rxFreePBMPacketDequeue;
#endif
    uint32_t ndkStackNotifyCount;
#endif

    NDK2NSP_PacketTaskStats txStats;
#if defined(NSP_INSTRUMENTATION_ENABLED)
    uint32_t txReadyPBMPacketEnqueue[MAC_NUM_PORTS];
    uint32_t txReadyPBMPacketDequeue[MAC_NUM_PORTS];
    uint32_t txFreeCPDMAPacketEnqueue;
    uint32_t txFreeCPDMAPacketDequeue;
    uint32_t txDroppedPacketCount;
#endif
    uint32_t gCpuLoad[HISTORY_CNT];
    uint32_t gHwiLoad[HISTORY_CNT];
}
NDK2NSP_Stats;

/*!
 * \brief
 *  Packet device information
 *
 * \details
 *  This structure caches the device info.
 */
typedef struct NDK2NSP_OBJECT_
{
    /*!
     * \brief       Index of currently connect physical port.
     */
    uint32_t                currLinkedInterface;
    /*!
     * \brief       Handle to hardware driver.
     */
    GMACSW_DeviceHandle     hGMACSW;
    /*!
     * \brief       Semaphore handle used by NDK stack and driver
     *              to communicate any pending Rx events that need
     *              to be serviced by NDK ethernet stack.
     */
    STKEVENT_Handle         hEvent;
    /*!
     * \brief       MAC Address
     */
    uint8_t         bMacAddr[MAC_NUM_PORTS][6];
    /*!
     * \brief       Current RX filter
     */
    uint32_t        Filter;
    /*!
     * \brief       Previous MCast Address Countr
     */
    uint32_t        OldMCastCnt;
    /*!
     * \brief       Previous Multicast list configured by the Application.
     */
    uint8_t         bOldMCast[(uint32_t)6U*PKT_MAX_MCAST];
    /*!
     * \brief       Current MCast Address Counter
     */
    uint32_t        MCastCnt;
    /*!
     * \brief       Multicast list configured by the Application.
     */
    uint8_t         bMCast[(uint32_t)6U*PKT_MAX_MCAST];
    /*!
     * \brief       Packet Device Maximum Transmission Unit
     */
    uint32_t        PktMTU;
    /*!
     * \brief       Link is up flag.
     */
    uint32_t        linkIsUp[MAC_NUM_PORTS];
    /*!
     * \brief       Device is operating in test digital loopback mode.
     */
    uint32_t        inDLBMode;

    /*!
     * \brief       CPDMA receive packet memory
     */
    CPDMA_Packet    rxPacketMem[NDK2NSP_RX_PACKETS];
    /*!
     * \brief       CPDMA receive channel
     */
    CPDMA_ChannelHandle hRxChannel;
    /*!
     * \brief       NDK PBM Rx ready queue (holds packets ready to be received by the NDK stack)
     */
    PBMQ            rxReadyPBMPacketQueue[MAC_NUM_PORTS];
#if defined (TFDTP_STACK_ENABLED)
    /*!
     * \brief       TFDTP Rx ready queue (holds packets ready to be received by the TFDTP stack)
     */
    queue_t            rxReadyTFDTPPacketQueue;
    /*!
     * \brief       TFDTP + NDK Rx Packet free queue (holds packets ready to be given to the hardware)
     */
    queue_t            rxFreeTFDTPNDKPacketQueue;
    /*!
     * \brief       TFDTP handle.
     */
    tfdtp_handle_t  hTfdtp;
    /*!
     * \brief       Flag to enable packet seggregation for TFDTP packets.
     */
    uint32_t        tfdtpRxFlag;
#else
    /*!
     * \brief       NDK PBM Rx free queue (holds packets ready to be given to the hardware)
     */
    PBMQ            rxFreePBMPacketQueue;
#endif
    /*!
     * \brief       Handle to Rx task, whose job it is to receive packets
     *              used by the hardware and give them to the NDK stack,
     *              and return freed packets back to the hardware.
     */
    HANDLE          rxPacketTask;
    /*!
     * \brief       Handle to Rx semaphore, on which the rxPacketTask
     *              awaits for notification of used packets available.
     */
    HANDLE          rxPacketSem;
    /*!
     * \brief       Handle to PBM Q access semaphore. This semaphore is needed
     *              in case of SMP environment as two core can access PBM Qs 
     *              simultaneously.
     */
    HANDLE          pbmQAccessSem;
    /*!
     * \brief       CPDMA Rx free pcaket queue (holds packets removed from
     *              fromHardwarePacketQueue and ready to be added to
                    toHardwarePacketQueue);.
     */
    CPDMA_PacketQueue rxFreePacketQueue;

    /*!
     * \brief       CPDMA transmit packet memory
     */
    CPDMA_Packet    txPacketMem[NDK2NSP_TX_PACKETS];
    /*!
     * \brief       CPDMA transmit channel
     */
    CPDMA_ChannelHandle hTxChannel;
    /*!
     * \brief       NDK PBM Tx ready queue (holds packets ready to be sent to the hardware)
     */
    PBMQ            txReadyPBMPacketQueue[MAC_NUM_PORTS];
    /*!
     * \brief       NSP CPDMA Tx free queue (holds free hardware packets awaiting)
     */
    CPDMA_PacketQueue   txFreeCPDMAPacketQueue;
    /*!
     * \brief       Handle to Rx task, whose job it is to receive packets
     *              used by the hardware and give them to the NDK stack,
     *              and return freed packets back to the hardware.
     */
    HANDLE          txPacketTask;
    /*!
     * \brief       Handle to Tx semaphore, on which the txPacketTask
     *              awaits for notification of used packets available.
     */
    HANDLE          txPacketSem;

    /*!
     * \brief       Handle to counting shutdown semaphore, which all subtasks
     *              created in the open function must post before the close
     *              operation can complete.
     */
    HANDLE          shutDownSem;
    /*!
     * \brief       Boolean to indicate shutDown status of translation layer.
     */
    uint32_t        shutDown;

    /*!
     * \brief       Rx Priority Mapping handle.
     */
    PORT_RxPriorityMapHandle        hRxPriorityMap;

    /*!
     * \brief       Registered Tick Fxn Handle.
     */
    GMACSW_RegisteredTickFxnHandle  hRegisteredTickFxn;

    /*!
     * \brief       Registered Print Fxn Handle.
     */
    GMACSW_PrintFxnCallback  printFxnCb;

    /*!
     * \brief       Dual MAC enable flag.
     */
    uint32_t        enableDualMac;
}
NDK2NSP_Object, *NDK2NSP_Handle;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

#if defined(NSP_INSTRUMENTATION_ENABLED)
extern NDK2NSP_Stats ndk2NspStats;
#endif


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

/*
 * Functions Provided by our translation layer code
 */
extern NDK2NSP_Handle NDK2NSP_open(STKEVENT_Handle hEvent);
extern void NDK2NSP_close(NDK2NSP_Handle hNDK2NSP);
extern void NDK2NSP_setRx(NDK2NSP_Handle hNDK2NSP);

extern void NDK2NSP_sendTxPackets(NDK2NSP_Handle hNDK2NSP, uint32_t devIdx);

extern uint32_t NDK2NSP_ioctl(NDK2NSP_Handle hNDK2NSP, uint32_t cmd, void* param, uint32_t size);
extern void NDK2NSP_poll(NDK2NSP_Handle hNDK2NSP, uint32_t fTimerTick );
extern void NDK2NSP_registerPrintFxnCb( NDK2NSP_Handle hNDK2NSP, GMACSW_PrintFxnCallback printFxn );

#if defined (TFDTP_STACK_ENABLED)
extern void             NDK2NSP_startTfdtpRx( NDK2NSP_Handle hNDK2NSP );
extern void             NDK2NSP_stopTfdtpRx( NDK2NSP_Handle hNDK2NSP );
#endif

void My_PBMQ_enq(PBMQ *pQ, PBM_Handle hPkt);
PBM_Handle My_PBMQ_deq(PBMQ *pQ); 
/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* NDK2NSP_H_ */
