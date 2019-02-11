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
 *  \file avbtp_packet.h
 *
 *  \brief AVBTP private Packet and Packet queue definitions.
 */

#ifndef AVBTP_PACKET_H_
#define AVBTP_PACKET_H_

#ifdef __cplusplus
extern "C" {
#endif

/* EDMA3 header */
#include <sample.h>
#include <avbtp_queue.h>

/*! \brief Structure representing an AVB Rx packet as a node in a linked list
 * \ingroup group_avbtp
 */
typedef struct AVBTP_RX_PACKET_
{
    /*! The node element so this packet can be added to a queue */
    node_t                   node;
    /*! Pointer to the data payload */
    uint8_t                  *pBuffer;
    /*! The size of the payload */
    uint32_t                 bufferSize;
    /*! The EDMA PaRAM set associated with this packet (node in linked-list of edma PaRAM sets) */
    EDMA3_DRV_ParamentryRegs *pEdmaParams;
    /*! The edma channel ID associated with the EDMA PaRAM set described in pEdmaParams*/
    uint32_t                 edmaChId;
    /*! Points to the next PaRAM set; used to avoid having to read the PaRAM set LINK register*/
    EDMA3_DRV_ParamentryRegs *pNextEdmaParams;
}
AVBTP_RxPacket;

/*! \brief Structure representing an AVB tx packet as a node in a linked list
 * \ingroup group_avbtp
 */
typedef struct AVBTP_TX_PACKET_
{
    /*! The node element so this packet can be added to a queue */
    node_t                   node;
    /*! Pointer to the data payload */
    uint8_t                  *pBuffer;
    /*! The size of the payload */
    uint32_t                 bufferSize;
    /*! Pointer to the AVB/ethernet header for this packet */
    uint8_t                  *pHeader;
    /*! Boolean flag that can be used to mark the end of a complete buffer */
    uint32_t                 notifyFree;
    /*! Invoked if notifyFree is set and this packet is beeing freed */
    avbtp_talker_cb         callBack;
    /*! The callback to invoke when a queued buffer has been sent */
    void                            *txCbData;
    /*! The talker index to which packet bind to */
    uint32_t                 talkerIndex;
    /*! The client buffer associated with this packet - used as argument into callback */
    avbtp_tx_buffer         *buffer;
}
AVBTP_TxPacket;

#ifdef __cplusplus
}
#endif

#endif
