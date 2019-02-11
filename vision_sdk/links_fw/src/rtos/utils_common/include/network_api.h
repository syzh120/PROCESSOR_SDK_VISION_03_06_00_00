/*
Copyright (c) [2012 - 2017] Texas Instruments Incorporated

All rights reserved not granted herein.

Limited License.

 Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
 license under copyrights and patents it now or hereafter owns or controls to
 make,  have made, use, import, offer to sell and sell ("Utilize") this software
 subject to the terms herein.  With respect to the foregoing patent license,
 such license is granted  solely to the extent that any such patent is necessary
 to Utilize the software alone.  The patent license shall not apply to any
 combinations which include this software, other than combinations with devices
 manufactured by or for TI ("TI Devices").  No hardware patent is licensed
 hereunder.

 Redistributions must preserve existing copyright notices and reproduce this
 license (including the above copyright notice and the disclaimer and
 (if applicable) source code license limitations below) in the documentation
 and/or other materials provided with the distribution

 Redistribution and use in binary form, without modification, are permitted
 provided that the following conditions are met:

 * No reverse engineering, decompilation, or disassembly of this software
   is permitted with respect to any software provided in binary form.

 * Any redistribution and use are licensed by TI for use only with TI Devices.

 * Nothing shall obligate TI to provide you with source code for the software
   licensed and provided to you in object code.

 If software source code is provided to you, modification and redistribution of
 the source code are permitted provided that the following conditions are met:

 * Any redistribution and use of the source code, including any resulting
   derivative works, are licensed by TI for use only with TI Devices.

 * Any redistribution and use of any object code compiled from the source code
   and any resulting derivative works, are licensed by TI for use only with TI
   Devices.

 Neither the name of Texas Instruments Incorporated nor the names of its
 suppliers may be used to endorse or promote products derived from this software
 without specific prior written permission.

 DISCLAIMER.

 THIS SOFTWARE IS PROVIDED BY TI AND TI’S LICENSORS "AS IS" AND ANY EXPRESS OR
 IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 IN NO EVENT SHALL TI AND TI’S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 *******************************************************************************
 *
 * \file network_api.h Wrapper API's to use TCP/IP sockets
 *
 *******************************************************************************
 */

#ifndef NETWORK_API_H_
#define NETWORK_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

#include <include/link_api/networkCtrl_api.h>

#include <ti/drv/vps/include/osal/bsp_osal.h>

/* NDK Dependencies */
#include <ti/ndk/inc/netmain.h>
#include <ti/ndk/inc/tools/servers.h>
#include <ti/ndk/inc/stkmain.h>
#include <ti/ndk/inc/stack/stack.h>

#if (defined(NSP_TFDTP_INCLUDE))
/* TFDTP Dependencies */
#include <ti/nsp/drv/inc/tfdtp.h>
#endif

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define NETWORK_ERROR       (-(Int32)1)
#define NETWORK_SUCCESS     (0)

typedef enum {
    TFDTP_TRANSMIT_OK      = 0x1U,
    TFDTP_TRANSMIT_FAIL    = 0x2U,
    TFDTP_TRANSMIT_INVALID = 0xFFU
} NetworkTfdtp_TransmitAck;

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */
#if (defined(NSP_TFDTP_INCLUDE))
/*******************************************************************************
 *  \brief TFDTP Rx and Tx channel structures
 *******************************************************************************
 */
typedef struct {

    TFDTP_RxChOpenPrm_t tfdtpRxChOpenPrms;
    /**< TFDTP Receive Channel Open Parameters */

    tfdtp_rx_channel_handle_t hTfdtpRxCh;
    /**< Handle of TFDTP Receive Channel */

    BspOsal_SemHandle rxFrameDone;
    /**< Handle of Frame RX complete semaphore */

    struct tfdtp_rx_buf_details bufArrayDesc;
    /**< RX buffer array descriptor */

}Network_tfdtpRxChObj;
#endif

#if (defined(NSP_TFDTP_INCLUDE))
typedef struct {

    TFDTP_TxChOpenPrm_t tfdtpTxChOpenPrms;
    /**< TFDTP Transmit Channel Open Parameters */

    tfdtp_tx_channel_handle_t hTfdtpTxCh;
    /**< Handle of TFDTP Receive Channel */

    BspOsal_SemHandle txFrameDone;
    /**< Handle of Frame TX complete semaphore */

}Network_tfdtpTxChObj;
#endif

/*******************************************************************************
 *  \brief Information related to network socket
 *******************************************************************************
 */
typedef struct {

    SOCKET sockFd;
    /**< Server socket handle */

    UInt32 port;
    /**< port on which server is listening */

    SOCKET connectedSockFd;
    /**< socket handle of client that is connected */

    FDPOLLITEM pollitem[1U];
    /**< Polling structure to use with fdPoll() */

#if (defined(NSP_TFDTP_INCLUDE))
    tfdtp_handle_t hTfdtp;
    /**< Handle of TFDTP Stack */

    Network_tfdtpTxChObj tfdtpTxChObj;
    /**< TFDTP Tx channel object (used by Null link) */

    Network_tfdtpRxChObj tfdtpRxChObj;
    /**< TFDTP Tx channel object (used by Null source link) */

    UInt32 retryCount;
    /**< TFDTP No. of Retries */
#endif

} Network_SockObj;

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

Int32 Network_open(Network_SockObj *pObj, UInt32 port);
Int32 Network_close(Network_SockObj *pObj, Bool closeServerSock);
Int32 Network_waitConnect(Network_SockObj *pObj, UInt32 timeout);
Int32 Network_read(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 *dataSize);
Int32 Network_write(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 dataSize);
Int32 Network_sessionOpen(BspOsal_TaskHandle handle);
Int32 Network_sessionClose(BspOsal_TaskHandle handle);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


