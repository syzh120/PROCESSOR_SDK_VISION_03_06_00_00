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
 * \ingroup NETWORK_CTRL_API
 * \defgroup NETWORK_CTRL_IMPL NetworkCtrl  Implementation
 *
 * @{
 */

/**
 *******************************************************************************
 *
 * \file NetworkCtrl_priv.h NetworkCtrl  private API/Data structures
 *
 *******************************************************************************
 */

#ifndef _NETWORK_CTRL_PRIV_H_
#define _NETWORK_CTRL_PRIV_H_

#ifdef __cplusplus
extern "C" {
#endif


#include <networkCtrl_api.h>
#include <network_api.h>


#define NETWORK_CTRL_MAX_CMDS        (64)

#define NETWORK_CTRL_MAX_PARAMS     (32)

typedef struct {

    char cmd[NETWORK_CTRL_CMD_STRLEN_MAX];
    void (*handler)();
    int numParams;

} CommandHandler;

typedef struct {

    UInt16 serverPort;
    /**< Server port to use */

    char command[NETWORK_CTRL_CMD_STRLEN_MAX];

    char params[NETWORK_CTRL_MAX_PARAMS][NETWORK_CTRL_CMD_STRLEN_MAX];

    int numParams;

    char ipAddr[32];

    Network_SockObj sockObj;

    CommandHandler cmdHandler[NETWORK_CTRL_MAX_CMDS];

} NetworkCtrl_Obj;

extern NetworkCtrl_Obj gNetworkCtrl_obj;

void ShowUsage();
void ParseCmdLineArgs(int argc, char *argv[]);
void ConnectToServer();
void CloseConnection();
void CommandExecute();

void SendCommand(char *command, void *params, int size);
int RecvResponse(char *command, UInt32 *prmSize);
int RecvResponseParams(char *command, UInt8 *pPrm, UInt32 prmSize);
void RegisterHandler(char *command, void (*handler)(), int numParams);

void handleEcho();
void handleMemRd();
void handleMemWr();
void handleMemSave();
void handleIssRawSave();
void handleIssYuvSave();
void handleIssIspSave();
void handleIssSendDccFile();
void handleIssSaveDccFile();
void handleIssClearDccQspiMem();
void handleIssSensorRegWrite();
void handleIssSensorRegRead();
void handleIssRead2AParams();
void handleIssWrite2AParams();
void handleStereoCalibImageSave();
void handleStereoCalibSetParams();
void handleStereoSetDynamicParams();
void handleStereoWriteCalibLUTDataToQSPI();
void handleQspiSendFile();
void handleMmcsdSendFile();
void handleSysReset();
void handleObjectDetectSetDynamicParams();
void handleDevCtrl();
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


