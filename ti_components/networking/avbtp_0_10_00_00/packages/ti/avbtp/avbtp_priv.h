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

/**
 *  \file avbtp_private.h
 *
 *  \brief AVBTP private header file.
 */

#ifndef AVBTP_PRIV_H_
#define AVBTP_PRIV_H_

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
#include "avb2nsp.h"

/* EDMA3 header */
/* #define USE_DMA_INTERRUPTS */
#include <sample.h>


/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

#define MAX_ETH_PAYLOAD_LEN 1500U

#define AVBTP_MAX_STREAM_PAYLOAD_SIZE 1472U

#define AVBTP_PACKET_HEADER_SIZE (sizeof(ether_frame_header_t) + sizeof(avbtp_cm_stream_header_t))

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*! \brief The list of possible buffer states
 * \ingroup group_avbtp
 */
typedef enum _h264_nalutype_e
{
    /*! Unspecified NALU Type */
    H264_NALU_TYPE_UNSPECIFIED = 0U,
    /*! Non- IDR Picture (I, P and B slice type) */
    H264_NALU_TYPE_NONIDR = 1U,
    /*! IDR Picture */
    H264_NALU_TYPE_IDR = 5U
} H264NALUType_e;

/*---------------------------------------------------------------------------*\
|                           AVB Ethernet frame definitions                   |
\*---------------------------------------------------------------------------*/

/*! \brief 802.1Q tag field in an ethernet frame
 * \ingroup group_avbtp_priv
 */
struct vlan_af
{
    uint16_t tpid;
    uint16_t tci;
};

/*! \brief The main Ethernet frame header
 * \ingroup group_avbtp_priv
 */
typedef struct ether_frame_header
{
    /*! Destination MAC address */
    uint8_t dstMac[6];
    /*! Source MAC address */
    uint8_t srcMac[6];
    /*! VLAN tag */
    struct vlan_af vlanaf;
    /*! The frame type */
    uint16_t etherType;
} ether_frame_header_t;

/*! \brief An ethernet frame
 * \ingroup group_avbtp_priv
 */
typedef struct ether_frame
{
    /*! Header */
    ether_frame_header_t header;
    /*! The generic data payload */
    uint8_t payload[MAX_ETH_PAYLOAD_LEN];
} ether_frame_t;

/*! \brief AV transport protocol (AVTP) common header (lives inside ethernet frame payload)
 * \ingroup group_avbtp_priv
 */
typedef struct avbtp_cm_header
{
    /*! These octets have different interpretations depending on AVB packet type */
    uint8_t oct[4];
    /*! The AVB packet stream ID (6-byte source MAC addr + 2 byte unique AVB identifier) */
    uint8_t stream_id[8];
} avbtp_cm_header_t;

/* AVBTP common stream header */
/*! \brief AVBTP common header for streaming data - refer to section 4.4.4.1 1722-2016.pdf
 * \ingroup group_avbtp_priv
 */
typedef struct avbtp_cm_stream_header
{
    /* The AVTP common header*/
    avbtp_cm_header_t cmh;
    /* The stream time for this packet */
    uint32_t timestamp;
    /* The AVTP packet data length */
    uint32_t format_specific_data[2];
    /* Format specific data for subtype*/
} avbtp_cm_stream_header_t;


/* AVBTP IEC 61883 stream header */
/*! \brief AVBTP header for streaming data
 * \ingroup group_avbtp_priv
 */
typedef struct avbtp_IEC_61883_fmt_data
{
    /* The AVTP packet data length */
    uint32_t gw_info;
    /* Gateway_info field - reserved for use by AVTP gateways that are not defined by this standard */
    uint16_t pd_length;
    /*! Media protocol specific header */
    uint16_t ps_header;
} avbtp_IEC_61883_fmt_data_t;

/* AVBTP Compressed video format stream header */
/*! \brief AVBTP header for streaming data
 * \ingroup group_avbtp_priv
 */
typedef struct avbtp_cvf_fmt_data
{
    /* The Compressed video Format info */
    uint8_t format_info[4];
    /* The AVTP packet data length */
    uint16_t pd_length;
    /*! Media protocol specific header */
    uint16_t ps_header;
} avbtp_cvf_fmt_data_t;

/*! \brief AVBTP stream data unit definition (which is contained in an ethernet frame payload)
 * \ingroup group_avbtp_priv
 */
typedef struct avbtp_cm_stream_packet
{
    /*! The AVTP stream data header*/
    avbtp_cm_stream_header_t cmsh;
    /*! The AVTP stream media data payload */
    uint8_t payload[AVBTP_MAX_STREAM_PAYLOAD_SIZE];
} avbtp_cm_stream_packet_t;

/*! \brief Structure for holding the state information of an AVB listener
 * \ingroup group_avbtp_priv
 */
struct avbtp_listener
{
    /*! An index indicating the position of this listener in the AVB stack listener array */
    uint32_t index;
    /*! A pointer to the instance of an AVB stack for which this listener belongs to */
    avbtp_handle_t avh;
    /*! The client callback to be invoked after stream data is available or fully assembled */
    avbtp_rcv_sd_cb_t rcv_sd_cb;
    /*! The client callback to be invoked when AVTP control data is received */
    void *rcv_sd_cbdata;
    /*! The talker MAC address this listener is bound to */
    uint8_t talker_addr[6];
    /*! The ID of the stream from an AVB talker which this listener is bound to */
    uint8_t streamID[8];
    /*! The previous packet sequence number - used to detect out-of-sequence and packet loss */
    uint32_t prevSeqNum;
    /*! A pointer to a buffer array registered by the client for this listener */
    app_buff_details_t buffDetails;
    /*! Flag to indicate notify per packet receive */
    int32_t notifyPerPacket;
    /*! Flag to indicate notify per Jpeg restart */
    int32_t notifyJpegRestart;
    /*! Statistics object for this listener */
    struct avbtp_stats stats;
    /*! AVB payload format type */
    int32_t avbTpSubType;
    /*! First frame received flag - used for H264 codec */
    int32_t firstFrameFlag;
};

struct avbtp_talker
{
    /*! An index indicating the position of this talker in the AVB talker array */
    uint32_t index;
    /*! A pointer to the instance of an AVB stack for which this talker belongs to */
    avbtp_handle_t avh;
    /*! The source MAC address for this AVB talker */
    uint8_t srcMAC[6];
    /*! The listener MAC address bound to this AVB talker */
    uint8_t dstMAC[6];
    /*! The VLAN id associated with this AVB talker */
    uint16_t vlanId;
    /*! The VLAN id associated with this AVB talker */
    uint8_t vlanPriority;
    /*! The ID of the stream from an AVB talker which this listener is bound to */
    uint8_t streamID[8];
    /*! The previous packet sequence number */
    uint8_t prevSeqNum;
    /*! A queue to hold filled buffers from client */
    queue_t readyBufferQ;
    /*! The buffer currently being emptied out */
    avbtp_tx_buffer *inUseBuffer;
    /*! The amount of data left in the current buffer */
    uint32_t *inUseBufferRemaining;
    /*! The callback to invoke when a queued buffer has been sent */
    avbtp_talker_cb callBack;
    /*! The callback to invoke when a queued buffer has been sent */
    void                            *txCbData;
    /*! AVB payload data format type */
    int32_t avbTpSubType;
    /*! AVB Compressed video format subtype */
    int32_t cvFormatSubType;
};

/*! \brief Structure for holding the state information of an instance of the AVB stack
 * \ingroup group_avbtp_priv
 */
struct avbtp_state
{
    /*! The list of all active listeners */
    struct avbtp_listener *listeners[AVBTP_MAX_LISTENERS];
    /*! The list of all active talkers */
    struct avbtp_talker *talkers[AVBTP_MAX_TALKERS];
    /*! The number of active talkers */
    uint32_t numTalkersOpen;
    /*! AVBTP initialization flag */
    uint32_t initFlag;
    /*! The handle to the translation layer between AVB and NSP driver */
    AVB2NSP_Handle hAVB2NSP;
    /*! The queue holding packets that can be used for receiving data */
    queue_t rxFreeAVBPacketQueue;
    /*! The queue holding packets that can be used for transmitting data */
    queue_t txFreeAVBPacketQueue;

    /*! The handle to the edma driver */
    EDMA3_DRV_Handle edma;
    /*! An EDMA PaRAM set used to trigger linked-list transfers */
    EDMA3_DRV_ParamentryRegs *pEdmaParams;
    /*! The EDMA channel assigned to our EDMA instance */
    uint32_t edmaChId;
    /*! The EDMA transfer controller ID assigned to our EDMA instance */
    uint32_t edmaTCC;
    /*! A linked list of pending edma transfers */
    queue_t pendingDMAPacketQueue;
#if defined(USE_DMA_INTERRUPTS)
    /*! A semaphore used to signal completion of all pending edma transfers */
    Semaphore_Handle edmaSem;
#endif
    struct avbtp_stats stats;
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
 * \ingroup group_avbtp
 */
extern void         AVBTP_processRxPackets(avbtp_handle_t avh, queue_t *pReadyQueue);

/*! \brief Blocking call that waits until all received packets are processed
 * \ingroup group_avbtp
 */
extern void         AVBTP_waitForPendingRxPackets(avbtp_handle_t avh);

extern void         AVBTP_fillTxQueue(avbtp_handle_t avh, queue_t *pReadyQueue);

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif  /* AVBTP_PRIV_H_ */
