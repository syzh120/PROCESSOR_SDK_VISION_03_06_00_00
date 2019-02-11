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
 *  \file tfdtp_types.h
 *
 *  \brief The internal types used by the TFDTP layer
 */
#ifndef TFDTP_TYPES_H_
#define TFDTP_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include <stdint.h>
#include <stdbool.h>

/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/*! Maximum no. of receive TFDTP channels */
#define TFDTP_MAX_RX_CHANNELS              ((uint32_t)1U)

/*! Maximum no. of transmit TFDTP channels */
#define TFDTP_MAX_TX_CHANNELS              ((uint32_t)1U)

/*! Maximum no. of buffers allocated by application */
#define TFDTP_MAX_APP_BUF_CNT           (5U)

/*! Flags Definition */
#define TFDTP_SOF                       (0x0000BE00)
#define TFDTP_EOF                       (0x000000EF)
#define TFDTP_VER                       (0x01000000)
#define TFDTP_SOF_MASK                  (0x0000FF00)
#define TFDTP_EOF_MASK                  (0x000000FF)
#define TFDTP_VER_MASK                  (0xFF000000)

/*! Maximum frame length on Ethernet network */
#define ETH_MAX_FRAME_LEN  1514U

/*! Header sizes Network payloads */
#define ETH_HDR_SIZE                     (14U)
#define IP_HDR_SIZE                      (20U)
#define UDP_HDR_SIZE                     (8U)
#define TFDTP_HDR_SIZE                   (sizeof(tfdtp_header_t))

/*! TFDTP Frame header size */
#define TFDTP_PACKET_HEADER_SIZE        (ETH_HDR_SIZE +  IP_HDR_SIZE + UDP_HDR_SIZE + TFDTP_HDR_SIZE)

/*! TFDTP maximum payload size */
#define TFDTP_MAX_STREAM_PAYLOAD_SIZE   (ETH_MAX_FRAME_LEN - TFDTP_PACKET_HEADER_SIZE)

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/

/*! TFDTP stack object handle, returned to application calling TFDTP_open function*/
typedef struct tfdtp_object                 *tfdtp_handle_t;
/*! TFDTP Rx Channel handle, returned by TFDTP_openRxChannel function*/
typedef struct tfdtp_rx_channel             *tfdtp_rx_channel_handle_t;
/*! TFDTP Tx Channel handle, returned by TFDTP_openTxChannel function */
typedef struct tfdtp_tx_channel             *tfdtp_tx_channel_handle_t;
/*!
 * Receive Buffer details pointer to describe receive buffers to TFDTP,
 * filled by application
 */
typedef struct tfdtp_rx_buf_details         *tfdtp_rx_buf_details_t;
/*! TFDTP Rx buffer pointer */
typedef struct tfdtp_rx_buf                 *tfdtp_rx_buf_handle_t;
/*! TFDTP Tx buffer pointer */
typedef struct tfdtp_tx_buf                 *tfdtp_tx_buf_handle_t;

/*! \brief TI Fast Data Transport Trotocol (TFDTP) common header (lives inside ethernet frame payload)
 *         TFDTP Header size: 20Bytes
 * \ingroup group_tfdtp
 */
typedef struct tfdtp_header
{
    uint32_t flags;
    /*!< flags for information [VER|xx|SOF|EOF] */
    uint16_t frame_id;
    /*!< frame index */
    uint16_t channel_id;
    /*!< Channel id index */
    uint16_t seq_num;
    /*!< packet sequence number in the frame  */
    uint16_t total_seq_num;
    /*!< total number of packet sequence in the frame  */
    uint32_t length;
    /*!< Packet length */
    uint32_t frame_offset;
    /*!< packet location offset in the frame */
    uint32_t reserved;
    /*!< Reserved */
} tfdtp_header_t;

/*! \brief TFDTP block data unit definition (which is contained in an ethernet frame payload)
 * \ingroup group_tfdtp
 */
typedef struct {
    tfdtp_header_t header;
    /*!< TFDTP block data header  */
    uint8_t payload[TFDTP_MAX_STREAM_PAYLOAD_SIZE];
    /*!< The TFDTP block data payload */
} tfdtp_packet_t;


/*! \brief The list of possible buffer states
 * \ingroup group_tfdtp
 */
typedef enum _buf_state_e
{
    /*! Indication that buffer has no valid data */
    BUFF_EMPTY = 0,
    /*! Indication that buffer has been filled and has valid data */
    BUFF_FULL,
    /*! Indication that buffer is currently being filled */
    BUFF_PARTIAL
} BuffState_e;

/*! \brief Buffer error status for received buffer
 * \ingroup group_tfdtp
 */
typedef enum error_status_e
{
    BUFF_NOERROR = 0,
    /*! Missing packets */
    BUFF_ERR_PACKET_DROP = (uint32_t)1U,
    /*! Packets out of sequence but no drop */
    BUFF_ERR_PACKET_SEQUENCE = (uint32_t)1U << 1U,
    /*! Received invalid packet size */
    BUFF_ERR_PACKET_SIZE = (uint32_t)1U << 2U,
    /*! Error while trying to setup DMA transfers */
    BUFF_ERR_DMA = (uint32_t)1U << 3U,
    /*! Insufficient output buffer size */
    BUFF_ERR_SIZE = (uint32_t)1U << 4U,
    /*! Error set when a new frame SOF marker has been detected but a frame EOF marker was expected*/
    BUFF_ERR_NO_EOI_DETECTED = (uint32_t)1U << 5U
} ErrorStatus_e;

/*! \brief A generic node structure for a single link list
 * \ingroup group_tfdtp
 */
typedef struct node_t_
{
    /*! Pointer to the next element in the list */
    struct node_t_ *pNext;
} node_t;

/*!
 *  \defgroup TFDTP_CONFIG_DEFINTIONS TFDTP Driver Configuration Definitions
 *
 *  This group contains structure and type definitions needed to properly construct the
 *  configuration structure needed to open the driver object and receive/tran channels.
 *
 *  @{
 */

/*! \brief The callback type invoked when receiving TFDTP data.
 * \param [in] appRxBuffh, the buffer containing received data
 * \param [in] cbdata The client private data (given during tfdtp_rx_channel_open)
 * \param [in] channelNum The channel number bound to the receive channel that invokes the callback
 * \see tfdtp_rx_channel_open
 */
typedef int32_t (*tfdtp_rcv_cb_t)(tfdtp_rx_buf_handle_t appRxBuffh, void *cbdata, uint32_t channelNum);

/*! \brief The callback type invoked when transmitting TFDTP data.
 * \param [in] appTxBuffh, the buffer containing transmitted data
 * \param [in] cbdata The client private data (given during tfdtp_tx_channel_open)
 * \param [in] channelNum The channel number bound to the transmit channel that invokes the callback
 * \see tfdtp_rx_channel_open
 */
typedef int32_t (*tfdtp_tx_cb_t)(tfdtp_tx_buf_handle_t appTxBuffh, void *cbdata, uint32_t channelNum);

/*! \brief The callback type invoked for debug print */
typedef void (*tfdtp_printfxm_cb_t)(const char * prnStr);

/*! \brief The client specified buffer structure for receive channel.
 */
struct tfdtp_rx_buf
{
    /*! Pointer to buffer data */
    uint8_t *bufPtr;
    /*! Frame Id associated with this buffer */
    uint16_t frame_id;
    /*! Total no. of sequence numbers in this buffers (used during packet receive) */
    uint16_t total_seq_num;
    /*! Sequence number count - used to keep track of no. of packets received in this buffer  */
    uint16_t seq_num_cnt;
    /*! Pointer to current buffer being used by TFDTP */
    //uint8_t *writePtr;
    /*! State of each buffer - see bufState enum
     * Client shall set the state to BUFF_EMPTY when it is done using the buffer. */
    uint16_t bufState;
    /*! Actual amount of data filled per buffer */
    uint32_t dataLength;
    /*! The last error encountered by the TFDTP parser
     * @see ErrorStatus_e
     */
    uint32_t error;
    /*! To store client private data per buffer. */
    void *bufMetaData;
};

/*! \brief Structure to track the client specified buffer array.
 */
struct tfdtp_rx_buf_details
{
    /*! Pointer to array of buffer pointers */
    struct tfdtp_rx_buf appBufArray[TFDTP_MAX_APP_BUF_CNT];
    /*! Size of each buffer in buffer array */
    uint32_t bufSize;
    /*! Number of buffers in the array */
    uint32_t bufCount;
    /*! Channel number the receiver will bind to */
    uint32_t channelNum;
};

/*! \brief The client specified buffer structure for transmit channel.
 */
typedef struct tfdtp_tx_buf
{
    /*! Node element so this structure can be part of a single link list */
    node_t node;
    /*! Pointer to data */
    uint8_t *pData;
    /*! The current read pointer (used internally by the TFDTP transmitter)  */
    uint8_t *pRead;
    /*! Size of data */
    uint32_t size;
    /*! Buffer ID, used as TFDTP frame id */
    uint16_t buf_id;
    /*! Total sequence number, used in TFDTP header to construct
     *  frame back and find out of order and missing packets.
     *  total_seq_num = size/TFDTP_MAX_STREAM_PAYLOAD_SIZE */
    uint16_t total_seq_num;
    /*! Indicates if this buffer needs to be flushed from cache to maintain coherency */
    uint32_t needsFlushing;
    /*! The TFDTP transmitter instance this buffer is associated with */
    tfdtp_tx_channel_handle_t hTfdtpTxCh;
    /*! The data still left to send (used internally by the TFDTP transmitter)  */
    uint32_t remaining;
}tfdtp_tx_buf_t;

/*! \brief Structure to report successfully processed packet counts and parser error counts.
 */
struct tfdtp_stats
{
    /*! Number of stream data packets successfully parsed and processed by TFDTP stack */
    uint32_t packetCount;
    /*! Number of ignored data packets that are dropped by the TFDTP stack */
    uint32_t ignoredPacketCnt;
    /*! Number of parser errors encountered by the TFDTP stack */
    uint32_t errorCnt;
    /*! Number of packets with invalid channel id */
    uint32_t invalidChannelIDError;
    /*! Number of times the parser could not find a free buffer to write into (buffer underflow) */
    uint32_t noBuffersAvailable;
    /*! Number of times the parser encountered an out-of-sequence packet (either from packet loss or truly out of sequence)  */
    uint32_t outOfSequenceError;
    /*! Number of times the parser ran out of buffer space while assembling an output frame  */
    uint32_t insufficientSizeError;
    /*! Number of packets with zero size or bigger than the maximum allowed TFDTP payload */
    uint32_t invalidPacketSizeError;
    /*! Buffer bigger than allocated size */
    uint32_t invalidBufferSizeError;
};

/*! \brief TFDTP Channel Open parameters structure
 */
typedef struct TFDTP_RxChOpenPrm
{
    /*! TFDTP Channel id - used to identify multiple data streams */
    uint16_t                channelId;
    /*! rcv_cb Callback to receive stream data when available (maybe invoked at slice or full frame level depending on configuration) */
    tfdtp_rcv_cb_t          rcv_cb_fxn;
    /*! rcv_cbdata Pointer to private client data to be used in the rcv_sd_cb callback */
    void                    *rcv_cb_data;
    /*! Pointer to application data - not used */
    void                    *appObj;
}TFDTP_RxChOpenPrm_t;

/*! \brief TFDTP Channel Open parameters structure
 */
typedef struct TFDTP_TxChOpenPrm
{
    /*! TFDTP Channel id - used to identify multiple data streams */
    uint16_t                channelId;
    /*! Transmit UDP port used for TFDTP transmitter */
    uint16_t                hostUdpPort;
    /*! IP address of target, used to construct UDP transmit packet */
    uint32_t                hostIpAddr;
    /*! MAC address of target, used to construct UDP transmit packet */
    uint8_t                 hostMacAddr[6];
    /*! The callback to invoke when a queued buffer has been sent */
    tfdtp_tx_cb_t           tx_cb_fxn;
    /*! Pointer to private client data to be used in the txCallBack callback */
    void                    *tx_cb_data;
    /*! Pointer to application data - not used */
    void                    *appObj;
}TFDTP_TxChOpenPrm_t;

/*! \brief TFDTP Open parameters structure
 */
typedef struct TFDTP_OpenPrm
{
    /*! Receive UDP port used for TFDTP Traffic */
    uint16_t rxUdpPort;
    /*! IP address of this host, used to construct UDP transmit packet */
    uint32_t  myIpAddr;
    /*! Debug print function callback */
    tfdtp_printfxm_cb_t printFxnCb;
} TFDTP_OpenPrm_t;

/*!
 * @}
 */
#ifdef __cplusplus
}
#endif

#endif /* _TFDTP_ECHO_TEST_H_ */
