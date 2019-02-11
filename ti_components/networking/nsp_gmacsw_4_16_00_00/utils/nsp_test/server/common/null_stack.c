/*
 * Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
 *
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

/*!
 *  \file   null_stack.c
 *
 *  \brief  Null/Dummy stack implementation file.
 */


/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* OS/Posix headers */
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/utils/Load.h>

/* NDK Dependencies */
#include <ti/ndk/inc/stkmain.h>

/* This module's header */
#include "null_packet.h"
#include "null_stack_priv.h"
#include "null_stack.h"


/*---------------------------------------------------------------------------*\
|                             Extern Declarations                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                            Local Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#if defined(DEBUG)
#define LOGE(x, y) printf(x, y)
#else
#define LOGE(x, y)
#endif

/* TODO: Make this configurable via XDC */
#define NUMBER_OF_FRAMES    (NULL2NSP_RX_PACKETS * (uint32_t)2U)
#define EXPECTED_ETHERTYPE  (0x88B5U)


/*---------------------------------------------------------------------------*\
|                            Local Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Local Function Declarations                         |
\*---------------------------------------------------------------------------*/

static bool isBrokenSequence(uint32_t seqNum, uint32_t prevSeqNum);

/*---------------------------------------------------------------------------*\
|                         Local Variable Declarations                         |
\*---------------------------------------------------------------------------*/

/* Queue for Pooled Packets */
NULL_PacketQueue gNULLPacketQueue;
#if !defined(NULL_DYNAMIC_ALLOCATION)
NULL_State NULL_stateObj;
#endif


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/

#if defined(__GNUC__)
uint8_t gNullMemoryPool[DEFAULT_PACKET_SIZE * NUMBER_OF_FRAMES] __attribute__(( aligned(128), section(".far:NULL_MEMPOOL") ));
#else
#pragma DATA_ALIGN(gNullMemoryPool, 128);
#pragma DATA_SECTION(gNullMemoryPool, ".far:NULL_MEMPOOL");
uint8_t gNullMemoryPool[DEFAULT_PACKET_SIZE * NUMBER_OF_FRAMES];
#endif

#if defined(__GNUC__)
NULL_Packet gNullPackets[NUMBER_OF_FRAMES] __attribute__(( aligned(128), section(".far:NULL_MEMPOOL") ));
#else
#pragma DATA_ALIGN(gNullPackets, 128);
#pragma DATA_SECTION(gNullPackets, ".far:NULL_MEMPOOL");
NULL_Packet gNullPackets[NUMBER_OF_FRAMES];
#endif


/*---------------------------------------------------------------------------*\
|                          Global Function Definitions                        |
\*---------------------------------------------------------------------------*/

NULL_Handle NULL_open(void)
{
    NULL_Handle pNullStack;
    uint32_t i;

#if defined(NULL_DYNAMIC_ALLOCATION)
    pNullStack = calloc(1U, sizeof(NULL_State));
    if (pNullStack == NULL) return NULL;
#else
    pNullStack = &NULL_stateObj;
    memset(pNullStack, 0, sizeof(NULL_State));
#endif

    /* Clear the entire packet array */
    memset(gNullPackets, 0, sizeof(gNullPackets));

    /* Initialize the packet pool which is used by the NULL2NSP translation
     * layer to receive data
     */
    NULL_packetQueueInit(&gNULLPacketQueue);
    for (i = 0U; i < (uint32_t)NUMBER_OF_FRAMES; i++)
    {
        gNullPackets[i].pNextPacket = NULL;
        gNullPackets[i].pBuffer = &gNullMemoryPool[i * (uint32_t)DEFAULT_PACKET_SIZE];
        gNullPackets[i].bufferSize = DEFAULT_PACKET_SIZE;

        NULL_packetEnqueue(&gNULLPacketQueue, &gNullPackets[i]);
    }

    /* Open up the Stack-to-driver translation layer */
    {
        NULL2NSP_Config null2NspConfig;

        null2NspConfig.clientData   = pNullStack;
        pNullStack->hNULL2NSP = NULL2NSP_open(&null2NspConfig);
        if (pNullStack->hNULL2NSP == NULL)
        {
#if defined(NULL_DYNAMIC_ALLOCATION)
            free(pNullStack);
#endif
            return NULL;
        }
    }

    pNullStack->checkPackets = false;

    return pNullStack;
}

void NULL_close(NULL_Handle hNullStack)
{
    NULL_State *pNullStack = (NULL_State *) hNullStack;

    NULL2NSP_close(pNullStack->hNULL2NSP);

#if defined(NULL_DYNAMIC_ALLOCATION)
    free(pNullStack);
#endif
}

void NULL_getStatistics(NULL_Handle hNullStack, NULL_Stats *stats)
{
    NULL_State *pNullStack = (NULL_State *) hNullStack;

    *stats = pNullStack->stats;
}

void NULL_clearStatistics(NULL_Handle hNullStack)
{
    NULL_State *pNullStack = (NULL_State *) hNullStack;

    memset(&(pNullStack->stats), 0, sizeof(NULL_Stats));
}

void NULL_setPacketChecks(NULL_Handle hNullStack, bool enabled)
{
    NULL_State *pNullStack = (NULL_State *) hNullStack;

    pNullStack->checkPackets = enabled;
}

uint32_t NULL_getRxLoad(NULL_Handle hNullStack)
{
    NULL_State *pNullStack = (NULL_State *) hNullStack;
    Load_Stat stat;

    if (Load_getTaskLoad(pNullStack->hNULL2NSP->rxPacketTask, &stat))
    {
        return Load_calculateLoad(&stat);
    }
    return 0;
}

uint32_t NULL_getTxLoad(NULL_Handle hNullStack)
{
    NULL_State *pNullStack = (NULL_State *) hNullStack;
    Load_Stat stat;

    if (Load_getTaskLoad(pNullStack->hNULL2NSP->txPacketTask, &stat))
    {
        return Load_calculateLoad(&stat);
    }
    return 0;
}

void NULL_processRxPackets(NULL_Handle hNullStack)
{
    NULL_State *pNullStack = (NULL_State *) hNullStack;
    NULL2NSP_Handle hNULL2NSP = (NULL2NSP_Handle) pNullStack->hNULL2NSP;
    NULL_Packet *pNULLPacket;

    uint32_t packetCount = 0;

#if defined(NULL_INSTRUMENTATION_ENABLED)
    static uint32_t procCount = 0;
    uint32_t time1;
#endif

    pNULLPacket = NULL_packetDequeue(&hNULL2NSP->rxReadyNULLPacketQueue);
    /* Go through each arrived packet and process it */
    while (pNULLPacket != NULL)
    {
        packetCount++;
#if defined(NULL_INSTRUMENTATION_ENABLED)
        null2NspStats.rxReadyNULLPacketDequeue++;
        time1 = TIMER_READ();
#endif
        if (pNullStack->checkPackets)
        {
            ether_frame_t *frame = (ether_frame_t *)pNULLPacket->pBuffer;
            null_frame_payload_t *nfp = (null_frame_payload_t *) frame->payload;
            uint32_t payloadSize;
            uint32_t seqNum;

            /*
             * Packet data is written to memory by hardware so we need to ensure cache coherency when
             * parsing it
             */
            Cache_inv((Ptr)pNULLPacket->pBuffer, pNULLPacket->bufferSize, (Bits16)Cache_Type_ALL, (Bool)1U);

            if (frame->header.etherType != ntohs(EXPECTED_ETHERTYPE))
            {
                pNullStack->stats.errorCnt++;
                pNullStack->stats.unexpectedEtherType++;
                goto next_packet;
            }

            payloadSize = ntohs(nfp->length);

            if ((payloadSize == 0) || (payloadSize > MAX_ETH_PAYLOAD_LEN))
            {
                pNullStack->stats.errorCnt++;
                pNullStack->stats.invalidPacketSizeError++;
                goto next_packet;
            }

            seqNum = nfp->seq_num;
            if (isBrokenSequence(seqNum, pNullStack->prevSeqNum))
            {
                pNullStack->stats.errorCnt++;
                pNullStack->stats.outOfSequenceError++;
            }
            else
            {
                pNullStack->prevSeqNum = seqNum;
            }
        }
next_packet:
        NULL_packetEnqueue(&hNULL2NSP->rxFreeNULLPacketQueue, pNULLPacket);

        pNULLPacket = NULL_packetDequeue(&hNULL2NSP->rxReadyNULLPacketQueue);

#if defined(NULL_INSTRUMENTATION_ENABLED)
        null2NspStats.rxFreeNULLPacketEnqueue++;
        {
            uint32_t timeDiff = TIMER_READ_AND_DIFF(time1);

            null2NspStats.procStats.lastCycleCnt = timeDiff;
            null2NspStats.procStats.totalCycleCnt += timeDiff;
        }
#endif
    }

    pNullStack->stats.packetCnt += packetCount;

#if defined(NULL_INSTRUMENTATION_ENABLED)
    null2NspStats.procStats.packetsPerProcessingCall[procCount] = packetCount;
    null2NspStats.procStats.totalPacketCount += packetCount;
    if (packetCount > null2NspStats.procStats.packetsPerProcessingCallMax)
    {
       null2NspStats.procStats.packetsPerProcessingCallMax = packetCount;
    }

    procCount = (procCount + 1) & 0xFF;
#endif
}

void NULL_sendPacket(NULL_Handle pNullStack, NULL_Packet *pNULLPacket)
{
    NULL2NSP_Handle hNULL2NSP = (NULL2NSP_Handle) pNullStack->hNULL2NSP;

    NULL_packetEnqueue(&hNULL2NSP->txReadyNULLPacketQueue, pNULLPacket);
#if defined(NULL_INSTRUMENTATION_ENABLED)
    null2NspStats.txReadyNULLPacketEnqueue++;
#endif

    NULL2NSP_sendTxPackets(hNULL2NSP);
}

/* Packet and Packet Queue Routines */
NULL_Packet *NULL_packetAlloc(uint32_t maxSize)
{
    NULL_Packet *hNULLPacket = NULL;

    if (maxSize <= DEFAULT_PACKET_SIZE)
    {
        hNULLPacket = NULL_packetDequeue(&gNULLPacketQueue);
    }

    return hNULLPacket;
}

void NULL_packetFree(NULL_Packet *pNULLPacket)
{
    if (pNULLPacket != NULL)
    {
        NULL_packetEnqueue(&gNULLPacketQueue, pNULLPacket);
    }
}

void NULL_packetQueueInit(NULL_PacketQueue *pNULLQueue)
{
    pNULLQueue->count = 0;
    pNULLQueue->pHead = NULL;
    pNULLQueue->pTail = NULL;
}

void NULL_packetQueueCopy(NULL_PacketQueue *pDstQueue, const NULL_PacketQueue *pSrcQueue)
{
    pDstQueue->pHead = pSrcQueue->pHead;
    pDstQueue->pTail = pSrcQueue->pTail;
    pDstQueue->count = pSrcQueue->count;
}

void NULL_packetEnqueue(NULL_PacketQueue *pNULLQueue, NULL_Packet *pNULLPacket)
{
    uint32_t key = OEMSysCritOn();

    pNULLPacket->pNextPacket = NULL;

    if (0 == pNULLQueue->count)
    {
        /* Queue is empty - Initialize it with this one packet */
        pNULLQueue->pHead = pNULLPacket;
    }
    else
    {
        /* Queue is not empty - Push onto END */
        pNULLQueue->pTail->pNextPacket = pNULLPacket;
    }

    /* Make tail of queue point to new */
    pNULLQueue->pTail = pNULLPacket;
    pNULLQueue->count++;

    OEMSysCritOff(key);
}

NULL_Packet *NULL_packetDequeue(NULL_PacketQueue *pNULLQueue)
{
    NULL_Packet *pNULLPacket;
    uint32_t key = OEMSysCritOn();

    pNULLPacket = pNULLQueue->pHead;

    if (pNULLPacket != NULL)
    {
        pNULLQueue->pHead = pNULLPacket->pNextPacket;
        if (NULL == pNULLQueue->pHead)
        {
            pNULLQueue->pTail = NULL;
        }
        pNULLQueue->count--;
        pNULLPacket->pNextPacket = NULL;
    }

    OEMSysCritOff(key);

    return (pNULLPacket);
}


/*---------------------------------------------------------------------------*\
|                           Local Function Definitions                        |
\*---------------------------------------------------------------------------*/

static bool isBrokenSequence(uint32_t seqNum, uint32_t prevSeqNum)
{
    /* 8-bit packet sequence number field rolls-over*/
    uint32_t expectedSeq = (prevSeqNum + 1U) & (uint32_t)0xFFU;
    return (bool)(expectedSeq != seqNum);
}


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

