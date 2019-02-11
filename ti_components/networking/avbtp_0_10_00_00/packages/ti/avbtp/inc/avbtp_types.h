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
 *  \file avbtp_types.h
 *
 *  \brief The internal types used by the AVBTP layer
 */
#ifndef AVBTP_TYPES_H_
#define AVBTP_TYPES_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
/* Standard language headers */
#include <stdbool.h>

/*! \brief Stream data information
 * \ingroup group_avbtp
 */
typedef struct avbtp_sd_info
{
    bool media_restart;
    bool timestamp_uncertain;
    uint8_t stream_id[8];
    uint8_t seqn_diff;
} avbtp_sd_info_t;

/*! \brief The callback type invoked when receiving AVBTP streaming data.
 * \param [in] buf, the buffer containing stream data
 * \param [in] size, the amount of valid data in the buffer
 * \param [in] rsdinfo Stream information
 * \param [in] cbdata The client private data (given during avbtp_listener_open)
 * \param [in] channelNum The channel number bound to the listener that invokes the callback
 * \param [in] buffIndex index to array of buffers corresponding where buf is taken from
 * \see avbtp_listener_open
 * \ingroup group_avbtp
 */
typedef int32_t (*avbtp_rcv_sd_cb_t)(uint8_t *buf, uint32_t size, avbtp_sd_info_t *rsdinfo,
        void *cbdata, uint32_t channelNum, uint32_t buffIndex);

/*! \brief Control data info
 * \ingroup group_avbtp
 */
typedef struct avbtp_cd_info
{
    uint8_t control_data;
    uint8_t status;
} avbtp_cd_info_t;

/*! \brief The callback type invoked for control data.
 * \param [in] buf, the buffer containing control data
 * \param [in] size, the amount of valid data in the buffer
 * \param [in] cdinfo Control packet status info
 * \param [in] cbdata The client private data (given during avbtp_listener_open)
 * \see avbtp_listener_open
 * \ingroup group_avbtp
 */
typedef int32_t (*avbtp_rcv_cd_cb_t)(uint8_t *buf, uint32_t size, avbtp_cd_info_t *cdinfo, void *cbdata);

typedef struct app_buff_details *app_buff_details_t;
typedef struct avbtp_state *avbtp_handle_t;
typedef struct avbtp_listener *avbtp_listener_handle_t;
typedef struct avbtp_talker *avbtp_talker_handle_t;

/*! \brief The list of possible buffer states
 * \ingroup group_avbtp
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

typedef enum buf_config_e
{
    BUFF_NOTIFY_DEFAULT = 0,
    /*! Enable AVB to invoke stream data callback when a JPEG restart marker is detected*/
    BUFF_NOTIFY_MJPEG_RST = (uint32_t)1U << 1U,
    BUFF_NOTIFY_PACKET = (uint32_t)1U << 2U
} ConfigBits_e;

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
    /*! Error set when a new JPEG SOI marker has been detected but a JPEG EOI marker was expected*/
    BUFF_ERR_NO_EOI_DETECTED = (uint32_t)1U << 5U
} ErrorStatus_e;

/*! \brief A generic node structure for a single link list
 * \ingroup group_avbtp
 */
typedef struct node_t_
{
    /*! Pointer to the next element in the list */
    struct node_t_ *pNext;
} node_t;

/*! \brief Structure to track the client specified buffer array.
 * \ingroup group_avbtp
 */
struct app_buff_details
{
    /*! Pointer to array of buffer pointers */
    uint8_t **arrBuffPtr;
    /*! Size of each buffer in buffer array */
    uint32_t buffSize;
    /*! Number of buffers in the array */
    uint32_t buffCount;
    /*! Channel number the listener will bind to */
    uint32_t channelNum;
    /*! Configuration bits that specify when to callback client
     * @see ConfigBits_e
     */
    uint32_t configBits;
    /*! Pointer to current buffer being used by AVB - one of the entries in arrBuffPtr */
    uint8_t *writePtr;
    /*! Array of size buffCount describing the state of each buffer - see buffState enum
     * Client shall set the state to BUFF_EMPTY when it is done using the buffer. */
    uint8_t *buffState;
    /*! Array of size buffCount describing the actual amount of data filled per buffer */
    uint32_t *dataLength;
    /*! The last error encountered by the AVBTP parser
     * @see ErrorStatus_e
     */
    uint32_t error;
    /*! Current buffer index in use by AVBTP listener */
    uint32_t buffIndex;
    /*! Array of size buffCount to store client private data per buffer. */
    void *buffMetaData;
};

typedef struct avbtp_tx_buffer_t
{
    /*! Node element so this structure can be part of a single link list */
    node_t node;
    /*! Pointer to data */
    uint8_t *pData;
    /*! Size of data */
    uint32_t size;
    /*! Indicates if this buffer needs to be flushed from cache to maintain coherency */
    uint32_t needsFlushing;
    /*! The AVBTP talker instance this buffer is associated with */
    avbtp_talker_handle_t avth;
    /*! The data still left to send (used internally by the AVB talker)  */
    uint32_t remaining;
    /*! The current read pointer (used internally by the AVB talker)  */
    uint8_t *pRead;
    /*! To store client private data per buffer. */
    void *buffMetaData;
} avbtp_tx_buffer;

/*! \brief Structure to report successfully processed packet counts and parser error counts.
 * \ingroup group_avbtp
 */
struct avbtp_stats
{
    /*! Number of stream data packets successfully parsed and processed by AVB stack */
    uint32_t packetCnt;
    /*! Number of ignored data packets that are dropped by the AVB stack */
    uint32_t ignoredPacketCnt;
    /*! Number of parser errors encountered by the AVB stack */
    uint32_t errorCnt;
    /*! Number of control packets received */
    uint32_t controlPacketCnt;
    /*! Number of packets with an unexpected ether type field */
    uint32_t unexpectedEtherType;
    /*! Number of packets with an unexpected AVTP subtype field */
    uint32_t unexpectedSubType;
    /*! Number of packets with an unexpected CV Format field */
    uint32_t unexpectedCvformatType;
    /*! Number of packets with an unexpected CV Format SubType (codec type) field */
    uint32_t unexpectedCvformatSubType;
    /*! Number of packets tagged with a stream ID which does not refer to any registered listener */
    uint32_t unexpectedStreamID;
    /*! Number of stream data packets that did not signal stream ID valid flag (violation of the standard) */
    uint32_t svFlagError;
    /*! Number of packets with zero size or bigger than the maximum allowed AVTP payload */
    uint32_t invalidPacketSizeError;
    /*! Number of times the parser encountered an out-of-sequence packet (either from packet loss or truly out of sequence) */
    uint32_t outOfSequenceError;
    /*! Number of times the parser could not find a free buffer to write into */
    uint32_t noBuffersAvailable;
    /*! Number of times the parser ran out of buffer space while assembling an output frame */
    uint32_t insufficientSizeError;
    /*! Number of times the parser encountered a JPEG SOI marker before an EOI marker */
    uint32_t missedEOIError;
    /*! Number of times the parser encountered a JPEG RST marker - tracked only if RST marker detection is enabled*/
    uint32_t numRestartMarkers;
    /*! Number of times the parser encountered a JPEG SOI marker */
    uint32_t numSOIMarkers;
    /*! Number of times the parser encountered a JPEG EOI marker */
    uint32_t numEOIMarkers;
};

/*! \brief The callback type invoked for AVB stream data.
 * \param [in] buff, the buffer that has been emptied out
 * \see avbtp_listener_open
 * \ingroup group_avbtp
 */
typedef void (*avbtp_talker_cb)(avbtp_tx_buffer *buff, void *cbdata, uint32_t channelNum);

#ifdef __cplusplus
}
#endif

#endif
