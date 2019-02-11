/******************************************************************************
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
******************************************************************************/

/**
 *******************************************************************************
 *
 * \file networkCtrl_if.h
 *
 * \brief Header and command interface between PC application
 *        and target application
 *
 *        This file will be common bewteen the PC application
 *        and target application, hence it should not include any target
 *        specific data types and include files
 *
 *******************************************************************************
 */

#ifndef _NETWORK_CTRL_IF_H_
#define _NETWORK_CTRL_IF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/*******************************************************************************
 *  \brief TCP/IP port on which the server is listening
 *******************************************************************************
 */
#define NETWORK_CTRL_SERVER_PORT              (5000)


/*******************************************************************************
 *  \brief Default TCP/IP port on which the network RX link will listen
 *******************************************************************************
 */
#define NETWORK_RX_SERVER_PORT                (29171)

/*******************************************************************************
 *  \brief Default TCP/IP port on which the network TX link will listen
 *******************************************************************************
 */
#define NETWORK_TX_SERVER_PORT                (29172)

/*******************************************************************************
 *  \brief Default TFDTP server UDP port on which the TFDTP stack filter traffic
 *******************************************************************************
 */
#define NETWORK_TFDTP_RXFILTER_UDP_PORT       (29173)

/*******************************************************************************
 *  \brief Default TFDTP server UDP port on which the TFDTP stack filter traffic
 *******************************************************************************
 */
#define NETWORK_TFDTP_RX_CHANNEL_NUM          (55)

/*******************************************************************************
 *  \brief Default TFDTP client UDP port for receive
 *******************************************************************************
 */
#define NETWORK_TFDTP_HOST_UDP_PORT           (29174)

/*******************************************************************************
 *  \brief Default TFDTP server UDP port on which the TFDTP stack filter traffic
 *******************************************************************************
 */
#define NETWORK_TFDTP_TX_CHANNEL_NUM          (66)

/*******************************************************************************
 *  \brief Default number of TFDTP re-transmit count
 *******************************************************************************
 */
#define NETWORK_TFDTP_RETRANSMIT_COUNT        (2)

/*******************************************************************************
 *  \brief Header packet magic number to confirm received packet is a header
 *******************************************************************************
 */
#define NETWORK_CTRL_HEADER         (0x1234ABCD)
#define NETWORK_RX_HEADER           (0x5678ABCD)
#define NETWORK_TX_HEADER           (0xABCD4321)

/*******************************************************************************
 *  \brief Max length of command string
 *******************************************************************************
 */
#define NETWORK_CTRL_CMD_STRLEN_MAX     (64)

/*******************************************************************************
 *  \brief Flag that is set in the 'flags' field of the header to indicate
 *         this packet is a ACK packet for a previously send command
 *******************************************************************************
 */
#define NETWORK_CTRL_FLAG_ACK            (0x00000001)



/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */
/*
 *  Note: These structures are shared between PC and EVM so dont use any platform
 *        dependent types. Also disable struct padding to avoid potential size
 *        mismatch between client and server
 */

typedef struct {

    unsigned int header;
    /**< Header magic number NETWORK_CTRL_HEADER */

    char         cmd[NETWORK_CTRL_CMD_STRLEN_MAX];
    /**< Command, specified as a string of char's */

    unsigned int returnValue;
    /**< Return value that is set by teh command handler */

    unsigned int flags;
    /**< command specified flags, see NETWORK_CTRL_FLAG_* */

    unsigned int prmSize;
    /**< Size of input parameters in units of bytes.
     *   Can be 0 if no parameters need to sned for a command
     */

} NetworkCtrl_CmdHeader;

/**
 *******************************************************************************
 *
 * \brief Types of payload's that can be exchanged over network
 *
 *******************************************************************************
 */
#define NETWORK_RX_TYPE_META_DATA                    (0x1)
#define NETWORK_RX_TYPE_BITSTREAM_MJPEG              (0x2)
#define NETWORK_RX_TYPE_VIDEO_FRAME_YUV422I_YUYV     (0x8)
#define NETWORK_RX_TYPE_VIDEO_FRAME_YUV420SP_UV      (0x9)


typedef struct {
    unsigned int numBuf;
    /**< Number of buffers */

    unsigned int header;
    /**< Header magic number NETWORK_RX_HEADER */

    unsigned int payloadType;
    /**< Payload type NETWORK_RX_TYPE_* */

    unsigned int chNum;
    /**< channel ID */

    unsigned int dataSize;
    /**< Size of payload data in bytes */

    unsigned int width;
    /**< Width of video frame */

    unsigned int height;
    /**< Height of video frame */

    unsigned int pitch[2];
    /**< Pitch of video frame in bytes */

} NetworkRx_CmdHeader;

typedef struct
{
    /* TFDTP channel Id */
    unsigned int channelId;
    /* For transmit from EVM */
    unsigned int thruput;
    /* Client IP address */
    unsigned int IPAddress;
    /* Client MAC address */
    char MACAddr[16];
    /* Retransmit Count */
    unsigned int retryCount;
}
NetworkTfdtp_channelParams;

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


