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

#ifndef NETWORK_TFDTP_API_H_
#define NETWORK_TFDTP_API_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

/* TFDTP Dependencies */
#include <ti/nsp/drv/inc/tfdtp.h>
#include <src/rtos/utils_common/include/network_api.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define TFDTP_RX_TIMEOUT                        (200U)

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */
/**
 *******************************************************************************
 * \brief Enum for TFDTP channel type
 *******************************************************************************
*/
typedef enum
{
    TFDTP_CHANNEL_MODE_RX = 0x0,
    /**< Channel type receive  */
    TFDTP_CHANNEL_MODE_TX = 0x1
    /**< Channel type transmit  */

}Tfdtp_channelType;

/**
 ******************************************************************************
 *
 * \brief Structure to hold all Null link related to network receive
 *
 ******************************************************************************
 */

/*******************************************************************************
 *  Function's
 *******************************************************************************
 */

tfdtp_handle_t Network_tfdtpOpen(void);
void Network_tfdtpClose(tfdtp_handle_t hTfdtph);

void Network_initTfdtp(Network_SockObj *pObj);
void Network_deInitTfdtp(Network_SockObj *pObj);
void Network_getTfdtpChParams(Network_SockObj *pObj, Tfdtp_channelType chType);
void Network_initTfdtpChannel(Network_SockObj *pObj, Tfdtp_channelType chType);
Int32 Network_submitTfdtpRxBufs(tfdtp_rx_channel_handle_t hTfdtpRxCh,
                                tfdtp_rx_buf_details_t bufArrayDesc);
void Network_deInitTfdtpChannel(Network_SockObj *pObj, Tfdtp_channelType chType);
void Network_startTfdtp(Network_SockObj *pObj);
Int32 Network_tfdtpRead(Network_SockObj *pObj, UInt8 *dataBuf, const UInt32 *dataSize);
Int32 Network_tfdtpWrite(Network_SockObj *pObj, UInt8 *dataBuf, UInt32 dataSize);
UInt32 Network_tfdtpWaitAck(Network_SockObj *pObj);
Int32 Network_tfdtpSendAck(Network_SockObj *pObj, UInt32 ack);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


