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

#ifndef _NETWORK_TX_PRIV_H_
#define _NETWORK_TX_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <osa.h>
#include <networkCtrl_if.h>
#include <network_api.h>

#define TFDTP_DEFAULT_RX_THRUPUT 350

/* If you change below make sure to change similar in chains_tfdtpRx_Display.c */
#define TFDTP_CH_MAX_FRAME_WIDTH 1280
#define TFDTP_CH_MAX_FRAME_HEIGHT 720

/* Enable streaming mode (no server) */
#define TFDTP_TX_STREAMING_MODE 0

#if (1 == TFDTP_TX_STREAMING_MODE)
#define SYSTEM_DF_YUV420SP_UV  0
#define SYSTEM_DF_YUV422I_YUYV 1
#endif

#define MAX_CH  (8)

#define NETWORK_ERROR   (-1)
#define NETWORK_INVALID_HEADER  (-2)

#define MAX_BUF_SIZE    (1920*1080*2)

typedef struct {

    UInt16 serverPort;
    /**< Server port to use */

    char srcIpAddr[32], dstIpAddr[32];

    Network_SockObj sockObj;

    int numCh;

    char fileName[MAX_CH][1024];

    UInt8 *dataBuf;

    FILE *fd[MAX_CH];

    int frameCount[MAX_CH];

    int thruput;
    int usetfdtp;
    int verbose;
    int noLoop;
    int delay;
    int retryCount;

} NetworkTx_Obj;

extern NetworkTx_Obj gNetworkTx_obj;

void ShowUsage();
void ParseCmdLineArgs(int argc, char *argv[]);
int  ConnectToServer();
void CloseConnection();
void Init();
void DeInit();

int WriteCmdHeader(NetworkRx_CmdHeader *pHeader);
int ReadCmdHeader(NetworkRx_CmdHeader *pHeader);
int WriteData(NetworkRx_CmdHeader *pHeader);
void SendData();
int ReadData(NetworkRx_CmdHeader *pHeader);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


