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
 *  \file avbtp.h
 *
 *  \brief AVBTP main header file.
 */

#ifndef AVBTP_H_
#define AVBTP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include "avbtp_types.h"

/* OS/Posix headers */

/* NDK Dependencies */

/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/

/* AVBTP Protocol specific defines */
/* SUBTYPE 61883 */
#define AVBTP_SUBTYPE_61883_IIDC 0x0U
/* SUBTYPE CVF (compressed video format) */
#define AVBTP_SUBTYPE_CVF        0x3U

/* CV Format type for RFC payload */
#define AVBTP_CV_FORMAT_RFC      0x2

/* CVF - format subtypes */
#define AVBTP_CVF_FORMAT_SUBTYPE_MJPEG      0x0
#define AVBTP_CVF_FORMAT_SUBTYPE_H264       0x1
#define AVBTP_CVF_FORMAT_SUBTYPE_JPEG2000   0x2

/*---------------------------------------------------------------------------*\
|                           Global Typedefs/Enums                             |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Variable Declarations                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                   Global Inline Function Definitions                        |
\*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*\
|                         Global Function Declarations                        |
\*---------------------------------------------------------------------------*/

/*! \brief Creates and returns an AVBTP handle.
 * \returns handle to instance of the AVBTP parser.
 * \ingroup group_avbtp
 */
extern avbtp_handle_t avbtp_open(void);

/*! \brief Closes the given AVBTP handle, including any bound listeneners
 * \param [in] avh AVBTP handle
 * \ingroup group_avbtp
 */
extern void avbtp_close(avbtp_handle_t avh);

/*! \brief Opens a channel to listen for MJPEG frames
 * \param [in] avh Handle obtained from avbtp_open
 * \param [in] talker_addr MAC address of talker this listener will bind to (array of 6 bytes).
 * \param [in] rcv_sd_cb Callback to receive stream data when available (maybe invoked at slice or full frame level depending on configuration)
 * \param [in] rcv_sd_cbdata Pointer to private client data to be used in the rcv_sd_cb callback
 * \param [in] rcv_cd_cb Callback to receiuve control data (not currently supported)
 * \param [in] rcv_cd_cbdata Pointer to private client data to be used in the rcv_cd_cb callback
 * \param [in] Pointer to 8-byte array describing the stream ID of the talker to bind to.
 * \returns handle to instance of an AVBTP listener
 * \ingroup group_avbtp
 */
extern avbtp_listener_handle_t avbtp_listener_open(
        avbtp_handle_t avh,
        const uint8_t *talker_addr,
        avbtp_rcv_sd_cb_t rcv_sd_cb,
        void *rcv_sd_cbdata,
        avbtp_rcv_cd_cb_t rcv_cd_cb,
        void *rcv_cd_cbdata,
        const uint8_t *streamID);

/*! \brief Closes the given AVBTP listener handle - no more callbacks will be invoked and handle is destroyed.
 * \param [in] avh AVBTP listener handle
 * \ingroup group_avbtp
 */
extern void avbtp_listener_close(avbtp_listener_handle_t avlh);

/*! \brief Opens a channel for sending AVBTP data
 * \param [in] avh Handle obtained from avbtp_open
 * \param [in] Pointer to 6-byte array describing the MAC address of the listener to bind to. If set to NULL, the destination MAC address will be the "broadcast" address.
 * \param [in] cb Callback invoked when a queued buffer has been emptied out
 * \returns handle to instance of an AVBTP talker
 * \ingroup group_avbtp
 */
extern avbtp_talker_handle_t avbtp_talker_open(
        avbtp_handle_t avh,
        const uint8_t *listenerMAC,
        avbtp_talker_cb cb,
        void *talker_cbdata,
        uint32_t avbTpSubType,
        uint32_t cvFormatSubType);


/*! \brief Closes the given AVBTP talker handle - do not call if in the middle of avbtp_talker_send
 * \param [in] avth AVBTP talker handle to close
 * \ingroup group_avbtp
 */
extern void avbtp_talker_close(avbtp_talker_handle_t avth);

/*! \brief Binds an array of buffers to a listener instance
 * \param [in] avlh AVBTP listener handle
 * \param [in] buff_details structure describing the buffer array and how often to invoke callbacks.
 * \ingroup group_avbtp
 */
extern void avbtp_submit_buffer(avbtp_listener_handle_t avlh, app_buff_details_t buff_details);

/*! \brief Enables listeners to start receiving data and talkers to be able to send data
 * \param [in] avh Handle obtained from avbtp_open
 * \returns 0 on success, -1 if failed to start
 * \ingroup group_avbtp
 */
extern int32_t avbtp_start(avbtp_handle_t avh);

/*! \brief Obtains statistics gathered by AVB
 * \param [in] avh Handle obtained from avbtp_open
 * \param [out] stats Structure containing the AVB statistics
 * \ingroup group_avbtp
 */
extern void avbtp_get_statistics(avbtp_handle_t avh, struct avbtp_stats *stats);

/*! \brief Clear global statistics gathered by AVB
 * \param [in] avh Handle obtained from avbtp_open
 * \ingroup group_avbtp
 */
extern void avbtp_clear_statistics(avbtp_handle_t avh);

/*! \brief Obtains the load of the internal listener task
 * \param [in] avh Handle obtained from avbtp_open
 * \returns the task load in percent (0-100)
 * \ingroup group_avbtp
 */
extern uint32_t avbtp_get_rx_load(avbtp_handle_t avh);

/*! \brief Obtains the load of the internal talker task
 * \param [in] avh Handle obtained from avbtp_open
 * \returns the task load in percent (0-100)
 * \ingroup group_avbtp
 */
extern uint32_t avbtp_get_tx_load(avbtp_handle_t avh);

/*! \brief Obtains statistics gathered by AVB for a specific listener
 * \param [in] avlh Handle obtained from avbtp_listener_open
 * \param [out] stats Structure containing the AVB statistics
 * \ingroup group_avbtp
 */
extern void avbtp_get_listener_stats(avbtp_listener_handle_t avlh, struct avbtp_stats *stats);

/*! \brief Clears statistics gathered by AVB for a specific listener
 * \param [in] avlh Handle obtained from avbtp_listener_open
 * \ingroup group_avbtp
 */
extern void avbtp_clear_listener_stats(avbtp_listener_handle_t avlh);

/*! \brief Configures the VLAN id and priority for the given AVB talker
 * \param [in] avth Handle obtained from avbtp_talker_open
 * \param [in] vlanId The VLAN Id to use for this talker
 * \param [in] vlanPriority The VLAN priority code to use for this talker
 * \ingroup group_avbtp
 */
extern void avbtp_talker_set_vlan_info(avbtp_talker_handle_t avth, uint16_t vlanId, uint8_t vlanPriority);

/*! \brief Enqueues a multiple buffers to their respective talkers
 * \param [in] avh Handle obtained from avbtp_open
 * \param [in] buffers an array of pointers to the buffers to enqueue
 * \param [in] size the size of the buffers array
 * \ingroup group_avbtp
 */
extern void avbtp_talker_enqueue(avbtp_handle_t avh, avbtp_tx_buffer **buffers, uint32_t size);


/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* AVBTP_H_ */
