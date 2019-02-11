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
 *  \file null_packet.h
 *
 *  \brief NULL private Packet and Packet queue definitions.
 */

#include <inttypes.h>

#ifndef NULL_PACKET_H_
#define NULL_PACKET_H_

#ifdef __cplusplus
extern "C" {
#endif

/*!
 *  \brief  Structure representing a NULL packet as a node in a linked list
 */
typedef struct NULL_PACKET_
{
    /*! The next node in the list */
    struct NULL_PACKET_    *pNextPacket;
    /*! Pointer to the data payload */
    uint8_t                 *pBuffer;
    /*! The size of the payload */
    uint32_t                bufferSize;
}
NULL_Packet;

/*!
 *  \brief  Structure representing a NULL packet queue (linked list)
 */
typedef struct NULL_PACKET_QUEUE_
{
    /*! The current number of entries in the queue */
    uint32_t count;
    /*! The top of the queue */
    NULL_Packet *pHead;
    /*! The end of the queue */
    NULL_Packet *pTail;
}
NULL_PacketQueue;

/*! \brief Allocates a packet with a payload of maxSize
 */
extern NULL_Packet *NULL_packetAlloc(uint32_t maxSize);
/*! \brief Frees the packet allocated by NULL_packetAlloc
 */
extern void         NULL_packetFree(NULL_Packet *pNULLPacket);

/*! \brief Initializes the packet queue - does not free or dequeue
 */
extern void         NULL_packetQueueInit(NULL_PacketQueue *pNULLQueue);
/*! \brief Does a shallow copy of the source queue
 */
extern void         NULL_packetQueueCopy(NULL_PacketQueue *pDstQueue, const NULL_PacketQueue *pSrcQueue);
/*! \brief Thread safe enqueue
 */
extern void         NULL_packetEnqueue(NULL_PacketQueue *pNULLQueue, NULL_Packet *pNULLPacket);
/*! \brief Thread safe dequeue
 */
extern NULL_Packet *NULL_packetDequeue(NULL_PacketQueue *pNULLQueue);

#ifdef __cplusplus
}
#endif

#endif
