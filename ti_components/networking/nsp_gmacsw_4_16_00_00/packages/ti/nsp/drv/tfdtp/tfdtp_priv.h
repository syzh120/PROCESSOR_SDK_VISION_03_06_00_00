/*
 * Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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

/**
 *  \file tfdtp_priv.h
 *
 *  \brief TFDTP private header file.
 */

#ifndef TFDTP_PRIV_H_
#define TFDTP_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdint.h>
#include <stdbool.h>

/* OS/Posix headers */
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>

/* Project dependency headers */
#include "tfdtp2nsp.h"

/* EDMA3 header */
/* #define USE_DMA_INTERRUPTS */
#include <sample.h>


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define ETHERTYPE_IPV4 0x0800
#define IP_PROTOCOL_ID_UDP 17
#define MAX_ETH_PAYLOAD_LEN 1500U

#define IP_HDR_INDEX 0U

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                           TFDTP Ethernet frame definitions                   |
\*---------------------------------------------------------------------------*/

/*! \brief The main Ethernet frame header
 * \ingroup group_tfdtp_priv
 */
typedef struct ether_frame_header
{
    /*! Destination MAC address */
    uint8_t             dstMac[6];
    /*! Source MAC address */
    uint8_t             srcMac[6];
    /*! The frame type */
    uint16_t            etherType;
} ether_frame_header_t;

/*! \brief An ethernet frame
 * \ingroup group_tfdtp_priv
 */
typedef struct ether_frame
{
    /*! Header */
    ether_frame_header_t        header;
    /*! The generic data payload */
    uint8_t                     payload[MAX_ETH_PAYLOAD_LEN];
} ether_frame_t;


/*! \brief The IP header structure (Cant use NDK IPHDR due to options field)
 * \ingroup group_tfdtp_priv
 */
typedef struct
{
    UINT8    VerLen;
    UINT8    Tos;
    UINT16   TotalLen;
    UINT16   Id;
    UINT16   FlagOff;
    UINT8    Ttl;
    UINT8    Protocol;
    UINT16   Checksum;
    IPN      IPSrc;
    IPN      IPDst;
#if 0U
    UINT8    Options[1];
#endif
} ip_header_t;

/* UDP HEADER */
/*! \brief The UDP header structure (Copying from NDK to avoid dependency
 * \ingroup group_tfdtp_priv
 */
typedef struct
{
    UINT16   SrcPort;
    UINT16   DstPort;
    UINT16   Length;
    UINT16   UDPChecksum;
} udp_header_t;

/*TFDTP common stream header */
/*! \brief Ethernet Payload(TFDTP header + data) structure header for data
 * \ingroup group_tfdtp_priv
 */
typedef struct tfdtp_stream_header
{
    /*! IP header */
    ip_header_t         ip_hdr;
    /*! UDP header */
    udp_header_t        udp_hdr;
    /*! TFDTP block common header */
    tfdtp_header_t      tfdtp_hdr;
} tfdtp_stream_header_t;

/*! \brief TFDTP block data packet(TFDTP header + data)
 * \ingroup group_tfdtp_priv
 */
typedef struct tfdtp_data_packet
{
    /*! TFDTP block data header */
    tfdtp_stream_header_t       tfdtp_bhdr;
    /*! The TFDTP block data payload */
    uint8_t                     payload[TFDTP_MAX_STREAM_PAYLOAD_SIZE];
} tfdtp_stream_packet_t;

/*! \brief TFDTP receive state object to hold metadata during receive op
 * \ingroup group_tfdtp_priv
 */
typedef struct tfdtp_rx_state
{
    /*! Current buffer being filled up */
    tfdtp_rx_buf_handle_t     pCurrBuff;
    /*! Next buffer pointer */
    tfdtp_rx_buf_handle_t     pNextBuff;
} tfdtp_rx_state;

/*! \brief Structure for holding the state information of an TFDTP receiver
 * \ingroup group_tfdtp_priv
 */
struct tfdtp_rx_channel
{
    /*! An index indicating the position of this channel in the TFDTP channel array */
    uint32_t                        index;
    /*! TFDTP Channel id - used to identify multiple data streams */
    uint16_t                        channelId;
    /*! Channel allocation flag */
    uint32_t                        isAllocated;
    /*! A pointer to the instance of an TFDTP stack for which this channel belongs to */
    tfdtp_handle_t                  hTfdtp;
    /*! The client callback to be invoked after stream data is available or fully assembled */
    tfdtp_rcv_cb_t                  rcv_cb_fxn;
    /*! The client callback to be invoked when TFDTP control data is received */
    void                            *rcv_cb_data;
    /*! The ID of the stream from an TFDTP transmitter which this receiver is bound to */
    uint16_t                        dstUdpPort;
    /*! A pointer to a buffer array registered by the client for this receiver */
    tfdtp_rx_buf_details_t            buffDetails;
    /*! Previous buffer index - used to keep track of out of seq. packets */
    struct tfdtp_rx_buf               *pPrevAppBuff;
    /*! The buffer currently being filled */
    struct tfdtp_rx_buf               *pCurrAppBuff;
    /*! The buffer currently being filled */
    uint32_t                        inUseBufferIdx;
    /*! The TFDTP stats object for receiver */
    struct tfdtp_stats              stats;
};

/*! \brief Structure for holding the state information of an TFDTP transmit channel
 * \ingroup group_tfdtp_priv
 */
struct tfdtp_host_info
{
    /*! The host MAC address bound to this TFDTP transmitter */
    uint8_t                         hostMACAddr[6];
    /*! The host IP address bound to this TFDTP transmitter */
    uint32_t                        hostIpAddr;
    /*! UDP port of host attached to this Channel */
    uint32_t                        hostUdpPort;
};

/*! \brief Structure for holding the state information of an TFDTP transmitter
 * \ingroup group_tfdtp_priv
 */
struct tfdtp_tx_channel
{
    /*! An index indicating the position of this channel in the TFDTP channel array */
    uint32_t                        index;
    /*! TFDTP Channel id - used to identify multiple data streams */
    uint16_t                        channelId;
    /*! Channel allocation flag */
    uint32_t                        isAllocated;
    /*! A pointer to the instance of an TFDTP stack for which this channel belongs to */
    tfdtp_handle_t                  hTfdtp;
    /*! The source MAC address for this TFDTP transmitter */
    uint8_t                         srcMAC[6];
    /* ! Host info attached to this channel */
    struct tfdtp_host_info          hostInfo;
    /*! The previous packet sequence number */
    uint16_t                        prevSeqNum;
    /*! The Current frame id under transmission */
    uint16_t                        frame_id;
    /*! A queue to hold filled buffers from client */
    queue_t                         readyBufferQ;
    /*! The buffer currently being emptied out */
    tfdtp_tx_buf_t                    *inUseBuffer;
    /*! The amount of data left in the current buffer */
    uint32_t                        *inUseBufferRemaining;
    /*! The callback to invoke when a queued buffer has been sent */
    tfdtp_tx_cb_t                    txCbFxn;
    /*! The callback to invoke when a queued buffer has been sent */
    void                            *txCbData;
};

/*! \brief Structure for holding the state information of an instance of the TFDTP stack
 * \ingroup group_tfdtp_priv
 */
struct tfdtp_object
{
    /*! The list of all active receive channels */
    struct tfdtp_rx_channel         rxChannels[TFDTP_MAX_RX_CHANNELS];
    /*! The list of all active receive channels */
    struct tfdtp_tx_channel         txChannels[TFDTP_MAX_TX_CHANNELS];
    /*! Count of active channels */
    uint32_t                        numRxChannelsOpen;
    /*! Count of active channels */
    uint32_t                        numTxChannelsOpen;
    /*! TFDTP NDK2NSP layer channel initialization flag */
    uint32_t                        initFlag;
    /*! Receive UDP port used for TFDTP Traffic */
    uint32_t                        rxUdpPort;
    /*! IP address of this host, used to construct UDP transmit packet */
    uint32_t                        myIpAddr;
    /*! Debug print function callback */
    tfdtp_printfxm_cb_t             printFxnCb;
    /*! The handle to the translation layer between TFDTP and NSP driver */
    TFDTP2NSP_Handle                hTFDTP2NSP;
    /*! The handle to the translation layer between NDK and NSP driver */
    NDK2NSP_Handle                  hNDK2NSP;
    /*! The queue holding packets that can be used for receiving data. Please
     *  note during initialization packets and data buffers are allocated by
     *  NDK2NSP layer and handed over to TFDTP stack during TFDTP_initStack() call */
    /*! The free Rx packet queue allocated by the NDK2NSP */
    queue_t                         *rxFreeTFDTPPacketQueue;
    /*! The queue holding packets that can be used for transmitting data */
    queue_t                         txFreeTFDTPPacketQueue;

    /*! The handle to the edma driver */
    EDMA3_DRV_Handle                edma;
    /*! An EDMA PaRAM set used to trigger linked-list transfers */
    EDMA3_DRV_ParamentryRegs        *pEdmaParams;
    /*! The EDMA channel assigned to our EDMA instance */
    uint32_t                        edmaChId;
    /*! The EDMA transfer controller ID assigned to our EDMA instance */
    uint32_t                        edmaTCC;
    /*! A linked list of pending edma transfers */
    queue_t                         pendingDMAPacketQueue;
#if defined(USE_DMA_INTERRUPTS)
    /*! A semaphore used to signal completion of all pending edma transfers */
    Semaphore_Handle edmaSem;
#endif
    /*! TFDTP stats structure */
    struct tfdtp_stats              stats;
};

/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

/*! \brief Asynchronous call to parse and process packets from the ready queue.
 * \ingroup group_tfdtp
 */
extern void TFDTP_processRxPackets(tfdtp_handle_t hTfdtp, queue_t *pReadyQueue);

/*! \brief Blocking call that waits until all received packets are processed
 * \ingroup group_tfdtp
 */
extern void TFDTP_waitPendingRxPackets(tfdtp_handle_t hTfdtp);

/*! \brief Create transmit packets from application data
 * \ingroup group_tfdtp
 */
extern void TFDTP_fillTxQueue(tfdtp_handle_t hTfdtp, queue_t *pReadyQueue);

/*! \brief TFDTP stack basic Initialization. Called from ndk2nsp_open() for
 *         filling EDMA param info and other basic initialization.
 * \ingroup group_tfdtp
 */
extern tfdtp_handle_t TFDTP_initStack(NDK2NSP_Handle hNDK2NSP);

/*! \brief TFDTP stack basic deinit function. Called to remote EDMA association
 *         from receive packets.
 * \ingroup group_tfdtp
 */
extern void TFDTP_deInitStack(NDK2NSP_Handle hNDK2NSP, tfdtp_handle_t hTfdtp);

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif  /* TFDTP_PRIV_H_ */
