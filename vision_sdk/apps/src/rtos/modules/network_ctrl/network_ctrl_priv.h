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

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */

#if defined(LINUX_BUILD)
#include <src/hlos/utils/network/network_api.h>
#include <osa_tsk.h>
#include <osa_mem.h>
#else
#include <include/link_api/networkCtrl_api.h>
#include <src/rtos/links_common/system/system_priv_common.h>
#include <src/rtos/utils_common/include/network_api.h>
#include <src/rtos/utils_common/include/utils_tsk.h>
#endif
#include <src/include/chains_common_osal.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define NETWORK_CTRL_MAX_CMDS           (64)


/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */


typedef struct {

    char cmd[NETWORK_CTRL_CMD_STRLEN_MAX];
    NetworkCtrl_Handler handler;

} NetworkCtrl_CmdHandler;


/**
 *******************************************************************************
 *
 * \brief Structure to hold all NetworkCtrl  related information
 *
 *******************************************************************************
 */
typedef struct {

#if defined(LINUX_BUILD)
    OSA_ThrHndl thrHndl;
#else
    BspOsal_TaskHandle task;
    /**< Task to handle commands from networking */
#endif

    Bool tskExit;
    /**< Flag to exit task */

    UInt16 serverPort;
    /**< Server port to use */

    NetworkCtrl_CmdHeader cmdBuf;
    /**< Buffer for recevied command header */

    Network_SockObj sockObj;
    /**< Networking socket */

    NetworkCtrl_CmdHandler cmdHandler[NETWORK_CTRL_MAX_CMDS];

} NetworkCtrl_Obj;


Int32 NetworkCtrl_init();
Int32 NetworkCtrl_deInit();

Void NetworkCtrl_cmdHandlerUnsupportedCmd(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerEcho(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerMemRd(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerMemWr(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerMemSave(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerIssRawSave(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerIssYuvSave(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerIssIspSave(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerIssDccSendFile(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerIssSaveDccFile(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerIssClearDccQspiMem(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandleIssWriteSensorReg(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandleIssReadSensorReg(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandleIssRead2AParams(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandleIssWrite2AParams(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerStereoCalibImageSave(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerStereoWriteCalibLUTToQSPI(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerStereoSetParams(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerStereoSetDynamicParams(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerQspiWrite(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerMmcsdWrite_proxy(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerSysReset(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerObjectDetectSetDynamicParams(char *cmd, UInt32 prmSize);
Void NetworkCtrl_cmdHandlerdevRequest(char *cmd, UInt32 prmSize);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */


