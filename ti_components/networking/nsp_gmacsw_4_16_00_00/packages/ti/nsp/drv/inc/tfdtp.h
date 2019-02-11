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
 *  \file tfdtp.h
 *
 *  \brief TFDTP main header file.
 */

#ifndef TFDTP_H_
#define TFDTP_H_

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------------*\
|                                Header Files                                 |
\*---------------------------------------------------------------------------*/

/* Standard language headers */
#include "tfdtp_types.h"

/* OS/Posix headers */

/* NDK Dependencies */

/*---------------------------------------------------------------------------*\
|                           Global Macros/Defines                             |
\*---------------------------------------------------------------------------*/


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

/*!
 *  \defgroup   TFDTP_APIS   TFDTP  Top-level APIs
 *
 *  Programming interfaces for TFDTP driver.
 *
 *  @{
 */

/*!
 *  @b Description
 *  @n Creates and returns an TFDTP handle.
 *
 *     This TFDTP_open() API keeps
 *     a reference count that increments for every call and which is decremented
 *     for every TFDTP_close call. For the first call to this functions, when the
 *     reference count is zero, the application must supply a valid TFDTP_OpenPrm_t
 *     configuration structure or the open call will fail. When the reference
 *     count is non-zero, the configuration structure parameter is not required
 *     and can be NULL.
 *
 *     Data from the config structure is
 *     copied into the device's internal instance structure so the structure
 *     may be discarded after TFDTP_open() returns. In order to change an item
 *     in the configuration, the TFDTP must be closed and then
 *     re-opened with the new configuration. A driver reset is achieved by calling
 *     TFDTP_close() until the reference count is zero, followed by TFDTP_open().
 *
 *     An TFDTP object handle is returned to the caller. This handle must be saved
 *     by the caller and then passed to other TFDTP functions like open channel,
 *     close channel, start/stop TFDTP.
 *
 *
 *  <b> Pre Condition </b>
 *  @n  None
 *
 *  <b> Post Condition </b>
 *  @n  Creates TFDTP driver object with given configuration.
 *
 *  \param[in] tfdtpOpenPrms
 *      Pointer to configuration structure of type GMACSW_Config
 *
 *  \return
 *      @n Non-NULL pointer to a tfdtp_handle_t instance
 *      @n If open call fails, the return value is NULL.
 *
 */
tfdtp_handle_t TFDTP_open(TFDTP_OpenPrm_t *tfdtpOpenPrms);

/*!
 *  @b Description
 *  @n Close the TFDTP indicated by the supplied instance handle.
 *     Calling this API will decrement the outstanding reference counter for
 *     the driver. If the reference count becomes zero, the TFDTP will close both
 *     send and receive channels.
 *
 *     The function returns zero on success, or an error code on failure.
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_open function must be called and have returned a valid handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n The TFDTP will shutdown both send and receive
 *     operations, and free all pending transmit and receive packets.
 *
 *  \param[in]  hTfdtp
 *      Handle to opened the TFDTP object.
 *
 *  \return
 *      @n (0) - Operation completed with no error
 *      @n Any other returned value represents an error
 *
 */
extern int32_t TFDTP_close(tfdtp_handle_t hTfdtp);

/*!
 *  @b Description
 *  @n Opens a TFDTP receive channel for given TFDTP object
 *     Calling this API will return handle to newly created channel if valid free
 *     channel is available and increament no. of allocated Rx channels.
 *
 *     A Receive channel object handle is returned to the caller. This handle must be saved
 *     by the caller and then passed to other channel functions like submit Rx buffer,
 *     get channel statistics and stop channel.
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_open function must be called and have returned a valid handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n TFDTP receive channel object allocated for given configuration.
 *
 *  \param[in]  hTfdtp
 *      Handle to opened the TFDTP object.
 *  \param [in] pTfdtpRxChOpenPrms
 *      Pointer to TFDTP_RxChOpenPrm_t structure containing channel initialization parameters.
 *
 *  \return
 *      @n Non-NULL pointer to a tfdtp_rx_channel_handle_t instance
 *      @n If open call fails, the return value is NULL.
 *
 */
extern tfdtp_rx_channel_handle_t TFDTP_openRxChannel(tfdtp_handle_t hTfdtp, TFDTP_RxChOpenPrm_t *pTfdtpRxChOpenPrms);

/*!
 *  @b Description
 *  @n Close the TFDTP Receive channel indicated by the supplied channel handle
 *     and decrement the no. of allocated Rx channels.
 *
 *     The function returns zero on success, or an error code on failure.
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_openRxChannel function must be called and have returned a valid channel
 *     handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n The TFDTP will close receive channel and decrement no. of allocated channels count
 *
 *  \param[in]  hTfdtpRxCh
 *      Handle to opened the TFDTP channel object.
 *
 *  \return
 *      @n (0) - Operation completed with no error
 *      @n Any other returned value represents an error
 *
 */
extern int32_t TFDTP_closeRxChannel(tfdtp_rx_channel_handle_t hTfdtpRxCh);

/*!
 *  @b Description
 *  @n Opens a TFDTP transmit channel for given TFDTP object
 *     Calling this API will return handle to newly created channel if valid
 *     channel is available.
 *
 *     A Transmit channel object handle is returned to the caller. This handle must be saved
 *     by the caller and then passed to other channel functions like submit Tx buffer,
 *     and stop channel.
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_open function must be called and have returned a valid handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n TFDTP transmit channel object allocated for given configuration.
 *
 *  \param[in]  hTfdtp
 *      Handle to opened the TFDTP object.
 *  \param [in] pTfdtpTxChOpenPrms
 *      Pointer to TFDTP_TxChOpenPrm_t structure containing channel initialization parameters.
 *
 *  \return
 *      @n Non-NULL pointer to a tfdtp_tx_channel_handle_t instance
 *      @n If open call fails, the return value is NULL.
 *
 */
extern tfdtp_tx_channel_handle_t TFDTP_openTxChannel(tfdtp_handle_t hTfdtp, TFDTP_TxChOpenPrm_t *pTfdtpTxChOpenPrms);

/*!
 *  @b Description
 *  @n Close the TFDTP Transmit channel indicated by the supplied channel handle.
 *
 *     The function returns zero on success, or an error code on failure.
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_openTxChannel function must be called and have returned a valid channel
 *     handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n The TFDTP will close Transmit channel.
 *
 *  \param[in]  hTfdtpTxCh
 *      Handle to opened the TFDTP channel object.
 *
 *  \return
 *      @n (0) - Operation completed with no error
 *      @n Any other returned value represents an error
 *
 */
extern int32_t TFDTP_closeTxChannel(tfdtp_tx_channel_handle_t hTfdtpTxCh);

/*!
 *  @b Description
 *  @n Start TFDTP receive and transmit operations for given TFDTP handle.
 *     For receive channels it sets flag to enable UDP port based filtering of packets
 *     in NDK2NSP layer.
 *     For transmit channels it opens new CPDMA transmit channel in TFDTP2NSP layer
 *     starts opened Tx channel
 *
 *     The function returns zero on success, or an error code on failure.
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_open function must be called and have returned a valid handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n The TFDTP will start receive and transmit processing.
 *
 *  \param[in]  hTfdtp
 *      Handle to opened the TFDTP object.
 *
 *  \return
 *      @n (0) - Operation completed with no error
 *      @n Any other returned value represents an error
 *
 */
extern int32_t TFDTP_start(tfdtp_handle_t hTfdtp);

/*!
 *  @b Description
 *  @n Binds an array of buffers to a given receive channel.
 *
 *     The function returns zero on success, or an error code on failure.
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_openRxChannel function must be called and have returned a valid channel
 *     handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n The TFDTP will use these buffers for receiving data for this channel.
 *
 *  \param[in]  hTfdtpRxCh
 *      Handle to opened the TFDTP receive channel object.
 *  \param[in] buff_details
 *      structure describing the buffer array and how often to invoke callbacks.
 *
 *  \return
 *      @n (0) - Operation completed with no error
 *      @n Any other returned value represents an error
 *
 */
extern
int32_t TFDTP_submitRxBuf(tfdtp_rx_channel_handle_t hTfdtpRxCh, tfdtp_rx_buf_details_t buff_details);

/*!
 *  @b Description
 *  @n Enqueues given buffers to their respective transmit channels.
 *
 *     The function returns zero on success, or an error code on failure.
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_openTxChannel function must be called and have returned a valid channel
 *     handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n The TFDTP start transmitting submitted buffers for given Tx channels.
 *
 *  \param[in]  hTfdtp
 *      Handle to the TFDTP object.
 *  \param[in] buffers
        An array of pointers to the buffers to enqueue
 *  \param[in] size
        The size of the buffers array
 *
 *  \return
 *      @n (0) - Operation completed with no error
 *      @n Any other returned value represents an error
 *
 */
extern void TFDTP_submitTxBuf(tfdtp_handle_t hTfdtp, tfdtp_tx_buf_t **buffers, uint32_t size);

/*!
 *  @b Description
 *  @n Obtains statistics gathered by TFDTP.
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_open function must be called and have returned a valid
 *     handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n none.
 *
 *  \param[in]  hTfdtp
 *      Handle to the TFDTP object.
 *  \param[out] stats
 *      Structure containing the TFDTP statistics
 *
 *  \return
 *      @n None
 *
 */
extern void TFDTP_getStats(tfdtp_handle_t hTfdtp, struct tfdtp_stats *stats);

/*!
 *  @b Description
 *  @n Clears statistics gathered by TFDTP.
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_open function must be called and have returned a valid
 *     handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n TFDTP stats cleared.
 *
 *  \param[in]  hTfdtp
 *      Handle to the TFDTP object.
 *
 *  \return
 *      @n None
 *
 */
extern void TFDTP_clearStats(tfdtp_handle_t hTfdtp);

/*!
 *  @b Description
 *  @n Obtains the load of the TFDTP Rx task
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_open function must be called and have returned a valid
 *     handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n none.
 *
 *  \param[in]  hTfdtp
 *      Handle to the TFDTP object.
 *
 *  \return
 *      @n TFDTP Rx task load in percent (0-100)
 *
 */
extern uint32_t TFDTP_getRxLoad(tfdtp_handle_t hTfdtp);

/*!
 *  @b Description
 *  @n Obtains the load of the TFDTP Tx task
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_open function must be called and have returned a valid
 *     handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n none.
 *
 *  \param[in]  hTfdtp
 *      Handle to the TFDTP object.
 *
 *  \return
 *      @n TFDTP Tx task load in percent (0-100)
 *
 */
extern uint32_t TFDTP_getTxLoad(tfdtp_handle_t hTfdtp);

/*!
 *  @b Description
 *  @n Obtains statistics gathered by TFDTP for a specific receive channel
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_open function must be called and have returned a valid
 *     handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n none.
 *
 *  \param[in] hTfdtpRxCh
 *      Handle obtained from TFDTP_openRxChannel
 * \param [out] stats
 *      Structure containing the TFDTP statistics
 *
 *  \return
 *      @n none
 *
 */
extern void TFDTP_getRcvrStats(tfdtp_rx_channel_handle_t hTfdtpRxCh, struct tfdtp_stats *stats);

/*!
 *  @b Description
 *  @n Clears statistics gathered by TFDTP for a specific receive channel
 *
 *  <b> Pre Condition </b>
 *  @n TFDTP_openRxChannel function must be called and have returned a valid
 *     channel handle before calling this API.
 *
 *  <b> Post Condition </b>
 *  @n Clear receive channel stats.
 *
 *  \param[in] hTfdtpRxCh
 *      Handle obtained from TFDTP_openRxChannel
 *
 *  \return
 *      @n none
 *
 */
extern void TFDTP_clearRcvrStats(tfdtp_rx_channel_handle_t hTfdtpRxCh);
/*!
 *  @}
 */

/*---------------------------------------------------------------------------*\
|                                 End of File                                 |
\*---------------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif

#endif /* TFDTP_H_ */
