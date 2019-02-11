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

/**
 *   @file  avb2nsp.h
 *
 *   @brief
 *      Header file for AVB To NSP API layer
 *
 */


#ifndef AVB_2_NSP_H_
#define AVB_2_NSP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* OS/Posix headers */
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

/* NSP Dependencies */
#include <ti/nsp/drv/inc/gmacsw.h>

/* Project dependency headers */
#include "avbtp_types.h"
#include "avbtp_packet.h"
#include "avbtp_queue.h"

/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define AVBTP_MAX_LISTENERS     ((uint32_t)6U)
#define AVBTP_MAX_TALKERS       ((uint32_t)6U)

#define DEFAULT_PACKET_SIZE     ((uint32_t)1536U)
#define AVB2NSP_TX_PACKETS      ((uint32_t)128U)
#define AVB2NSP_RX_PACKETS      ((uint32_t)64U)

/* Use VLAN defaults if not defined by the build system */
#ifndef AVBTP_VLAN_ID
#define AVBTP_VLAN_ID 1024U
#endif
#ifndef AVBTP_VLAN_PRIORITY
#define AVBTP_VLAN_PRIORITY 5U
#endif

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

#define HISTORY_CNT (256U)

typedef struct AVB2NSP_PACKET_TASK_STATS_
{
#if defined(AVBTP_INSTRUMENTATION_ENABLED)
    uint32_t rawNotificationCount;
    uint32_t dataNotificationCount;
    uint32_t zeroNotificationCount;
    uint32_t totalPacketCount;
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
AVB2NSP_PacketTaskStats;

typedef struct AVB2NSP_PROCESSING_STATS_
{
#if defined(AVBTP_INSTRUMENTATION_ENABLED)
    uint32_t rawProcessingCallCount;
    uint32_t totalPacketCount;
    uint32_t lastCycleCnt;
    uint32_t totalCycleCnt;

    uint32_t packetsPerProcessingCallMax;
    uint32_t packetsPerProcessingCall[HISTORY_CNT];
    uint32_t cycleCountPerNotificationMax;
    uint32_t cycleCountPerNotification[HISTORY_CNT];

    uint32_t jpegFrameFullCallbackCount[AVBTP_MAX_LISTENERS];
#endif
    uint32_t taskLoad[HISTORY_CNT];
}
AVB2NSP_ProcessingStats;

typedef struct AVB2NSP_STATS_
{
    AVB2NSP_PacketTaskStats rxStats;
    AVB2NSP_PacketTaskStats txStats;
    AVB2NSP_ProcessingStats procStats;
#if defined(AVBTP_INSTRUMENTATION_ENABLED)
    uint32_t rxReadyAVBTPPacketEnqueue;
    uint32_t rxReadyAVBTPPacketDequeue;
    uint32_t rxFreeAVBTPPacketEnqueue;
    uint32_t rxFreeAVBTPPacketDequeue;

    uint32_t txReadyAVBTPPacketEnqueue;
    uint32_t txReadyAVBTPPacketDequeue;
    uint32_t txFreeCPDMAPacketEnqueue;
    uint32_t txFreeCPDMAPacketDequeue;

    uint32_t etherTypeError;
    uint32_t controlDataPacketCount;
    uint32_t streamIDValidFlagError;
    uint32_t avbSubTypeError;
    uint32_t invalidStreamIDError;
    uint32_t invalidPacketSizeError;
    uint32_t noBuffersAvailable;
    uint32_t outOfSequenceError;
    uint32_t insufficientSizeError;
#endif
    uint32_t txDroppedPacketCount;
}
AVB2NSP_Stats;

typedef struct AVB2NSP_CONFIG_
{
    /*! Client private data */
    void *clientData;
    /*! The free Rx packet queue allocated by the client */
    queue_t *rxFreeAVBTPPacketQueue;
    /*! The free Tx packet queue allocated by the client */
    queue_t *txFreeAVBTPPacketQueue;
}
AVB2NSP_Config;

typedef struct AVB2NSP_OBJECT_
{
    AVB2NSP_Config                  config;
    GMACSW_DeviceHandle             hGMACSW;

    GMACSW_RegisteredTickFxnHandle  hRegisteredTickFxn;

    bool                            shutDown;
    Semaphore_Handle                rxTaskShutDownSem;
    Semaphore_Handle                txTaskShutDownSem;

    CPDMA_Packet                    rxPacketMem[AVB2NSP_RX_PACKETS];
    CPDMA_ChannelHandle             hRxChannel;
    PORT_RxPriorityMapHandle        hRxPriorityMap;
    queue_t                         rxReadyAVBTPPacketQueue;
    Task_Handle                     rxPacketTask;
    Semaphore_Handle                rxPacketSem;

    CPDMA_Packet                    txPacketMem[AVB2NSP_TX_PACKETS];
    CPDMA_ChannelHandle             hTxChannel;
    CPDMA_PacketQueue               txFreeCPDMAPacketQueue;
    queue_t                         txReadyAVBTPPacketQueue;
    Task_Handle                     txPacketTask;
    Semaphore_Handle                txPacketSem;
    Semaphore_Handle                txPacketFreeSem;
}
AVB2NSP_Object, *AVB2NSP_Handle;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

extern AVB2NSP_Stats avb2NspStats;


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


#if defined(AVBTP_INSTRUMENTATION_ENABLED)
/*---------------------------------------------------------------------------*\
|            Helper timer functions for the ARM and DSP families              |
\*---------------------------------------------------------------------------*/
#if defined(CORTEX_MX)
/* Cortex M3/M4 timer registers */
#define SYSTICKREG                (*((volatile uint32_t*)0xE000E010))
#define SYSTICKREL                (*((volatile uint32_t*)0xE000E014))
#define SYSTICKVAL                (*((volatile uint32_t*)0xE000E018))
static inline void TIMER_START(void)
{
    /* The timer has already been initialized by SYS/BIOS*/
    SYSTICKREL = 0x00FFFFFFU;
    SYSTICKREG = 0x00000005U;
}

/* Reads the current tick of the timer - for Cortex M3/M4 it will be number of cycles*/
static inline uint32_t TIMER_READ(void)
{
  uint32_t cntl = SYSTICKVAL;
  return (cntl);
}

static inline uint32_t TIMER_DIFF(uint32_t time1, uint32_t time2)
{
  /* Handle counter overflow, the max value possible is given by the SYSTICKREL register*/
  return (time1 >= time2) ? (time1 - time2) : (time1 + (SYSTICKREL-time2));
}

static inline uint32_t TIMER_READ_AND_DIFF(uint32_t time1)
{
  uint32_t time2 = TIMER_READ();
  return TIMER_DIFF(time1, time2);
}
#elif defined(CORTEX_AX)
static inline void TIMER_START(void)
{
    /* TODO: Which timer to use in Cortex Ax families */
}

static inline uint32_t TIMER_READ(void)
{
    /* TODO: Access tick timer in A15/A8 */
    return 0;
}

static inline uint32_t TIMER_DIFF(uint32_t time1, uint32_t time2)
{
    /* Handle counter overflow - TODO: which max value to use for Ax families? */
    return (time2 >= time1) ? (time2 - time1) : (time2 + (UINT32_MAX-time1));
}

static inline uint32_t TIMER_READ_AND_DIFF(uint32_t time1)
{
    uint32_t time2 = TIMER_READ();
    return TIMER_DIFF(time1, time2);
}
#elif defined(__TMS320C6X__)
#include <c6x.h>
/* A read of the  TSCL/TSCH registers in C6x provides a 64-bit counter of the number of cycles
 * passed since the first time any of them were written to.
 */
static inline void TIMER_START(void)
{
    /* Write to the register to start the internal counter */
    TSCL = 0;
}

static inline uint64_t TIMER_READ(void)
{
    uint32_t cntl = TSCL;
    return ((uint64_t) _itoll( TSCH, cntl ));
}

static inline uint64_t TIMER_DIFF(uint32_t time1, uint32_t time2)
{
    /* Handle 64-bit counter overflow */
    return (time2 >= time1) ? (time2 - time1) : (time2 + (UINT64_MAX-time1));
}

static inline uint64_t TIMER_READ_AND_DIFF(uint32_t time1)
{
    uint64_t time2 = TIMER_READ();
    return TIMER_DIFF(time1, time2);
}
#endif
#endif


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/


/*! \brief Opens a handle to the translation layer which registers the AVB stack with the NSP driver
 * \param [in] config Configuration parameters such as callbacks and memory pool
 * \returns handle to an instance of the translation layer
 * \ingroup group_nspraw
 */
extern AVB2NSP_Handle AVB2NSP_open(AVB2NSP_Config const *config);

/*! \brief Closes channel
 * \param [in] hAVB2NSP handle given by AVB2NSP_open
 * \ingroup group_nspraw
 */
extern void AVB2NSP_close(AVB2NSP_Handle hAVB2NSP);

/*! \brief Enables processing of packets
 * \param [in] hAVB2NSP handle given by AVB2NSP_open
 * \ingroup group_nspraw
 */
extern void AVB2NSP_start(AVB2NSP_Handle hAVB2NSP);

/*! \brief If Tx is not currently active, start transmission
 * \param [in] hAVB2NSP handle given by AVB2NSP_open
 * \ingroup group_nspraw
 */
extern void AVB2NSP_kickTx(AVB2NSP_Handle hAVB2NSP);

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* AVB_2_NSP_H_ */
