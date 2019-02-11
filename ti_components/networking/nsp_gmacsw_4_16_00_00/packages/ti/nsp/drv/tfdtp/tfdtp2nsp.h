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

/**
 *   @file  tfdtp2nsp.h
 *
 *   @brief
 *      Header file for TFDTP To NSP API layer
 *
 */


#ifndef TFDTP_2_NSP_H_
#define TFDTP_2_NSP_H_

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
#include "tfdtp_types.h"
#include "tfdtp_packet.h"
#include "tfdtp_queue.h"

/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/
#define DEFAULT_PACKET_SIZE     ((uint32_t)1536U)
#define TFDTP2NSP_TX_PACKETS      ((uint32_t)128U)

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

typedef struct TFDTP2NSP_PACKET_TASK_STATS_
{
#if defined(TFDTP_INSTRUMENTATION_ENABLED)
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
TFDTP2NSP_PacketTaskStats;

typedef struct TFDTP2NSP_PROCESSING_STATS_
{
#if defined(TFDTP_INSTRUMENTATION_ENABLED)
    uint32_t rawProcessingCallCount;
    uint32_t totalPacketCount;
    uint32_t lastCycleCnt;
    uint32_t totalCycleCnt;

    uint32_t packetsPerProcessingCallMax;
    uint32_t packetsPerProcessingCall[HISTORY_CNT];
    uint32_t cycleCountPerNotificationMax;
    uint32_t cycleCountPerNotification[HISTORY_CNT];

    uint32_t fullFrameCnt[TFDTP_MAX_RX_CHANNELS];
    uint32_t edmaPacketsPerProcessingCall[HISTORY_CNT];
#endif
    uint32_t taskLoad[HISTORY_CNT];
}
TFDTP2NSP_ProcessingStats;

typedef struct TFDTP2NSP_STATS_
{
    TFDTP2NSP_PacketTaskStats rxStats;
    TFDTP2NSP_PacketTaskStats txStats;
    TFDTP2NSP_ProcessingStats procStats;
#if defined(TFDTP_INSTRUMENTATION_ENABLED)
    uint32_t rxReadyTFDTPPacketEnqueue;
    uint32_t rxReadyTFDTPPacketDequeue;
    uint32_t rxFreeTFDTPPacketEnqueue;
    uint32_t rxFreeTFDTPPacketDequeue;

    uint32_t txReadyTFDTPPacketEnqueue;
    uint32_t txReadyTFDTPPacketDequeue;
    uint32_t txFreeCPDMAPacketEnqueue;
    uint32_t txFreeCPDMAPacketDequeue;
#endif
    uint32_t txFreeCPDMAPacketUnderflow;
    uint32_t txFreeTFDTPPacketQueueUnderflow;
}
TFDTP2NSP_Stats;

typedef struct TFDTP2NSP_CONFIG_
{
    /*! Client private data */
    void *clientData;
    /*! The free Tx packet queue allocated by the client */
    queue_t *txFreeTFDTPPacketQueue;
}
TFDTP2NSP_Config;

typedef struct TFDTP2NSP_OBJECT_
{
    TFDTP2NSP_Config                  config;
    GMACSW_DeviceHandle             hGMACSW;

    GMACSW_RegisteredTickFxnHandle  hRegisteredTickFxn;

    bool                            shutDown;
    Semaphore_Handle                shutDownSem;

    CPDMA_Packet                    txPacketMem[TFDTP2NSP_TX_PACKETS];
    CPDMA_ChannelHandle             hTxChannel;
    CPDMA_PacketQueue               txFreeCPDMAPacketQueue;
    queue_t                         txReadyTFDTPPacketQueue;
    Task_Handle                     txPacketTask;
    Semaphore_Handle                txPacketSem;
    Semaphore_Handle                txPacketFreeSem;
}
TFDTP2NSP_Object, *TFDTP2NSP_Handle;


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

extern TFDTP2NSP_Stats tfdtp2NspStats;


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


#if defined(TFDTP_INSTRUMENTATION_ENABLED)
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


/*! \brief Opens a handle to the translation layer which registers the TFDTP stack with the NSP driver
 * \param [in] config Configuration parameters such as callbacks and memory pool
 * \returns handle to an instance of the translation layer
 * \ingroup group_nspraw
 */
extern TFDTP2NSP_Handle TFDTP2NSP_open(TFDTP2NSP_Config const *config);

/*! \brief Closes channel
 * \param [in] hTFDTP2NSP handle given by TFDTP2NSP_open
 * \ingroup group_nspraw
 */
extern void TFDTP2NSP_close(TFDTP2NSP_Handle hTFDTP2NSP);

/*! \brief Enables processing of packets
 * \param [in] hTFDTP2NSP handle given by TFDTP2NSP_open
 * \ingroup group_nspraw
 */
extern void TFDTP2NSP_start(TFDTP2NSP_Handle hTFDTP2NSP);

/*! \brief If Tx is not currently active, start transmission
 * \param [in] hTFDTP2NSP handle given by TFDTP2NSP_open
 * \ingroup group_nspraw
 */
extern void TFDTP2NSP_kickTx(TFDTP2NSP_Handle hTFDTP2NSP);

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/


#ifdef __cplusplus
}
#endif

#endif /* TFDTP_2_NSP_H_ */
