/******************************************************************************
Copyright (c) [2018] Texas Instruments Incorporated

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

#include "network_ctrl_priv.h"
#include <src/include/chains_common_osal.h>
#include <src/rtos/modules/devcontrol/devControl_priv.h>

#define NETWORK_CTRL_MAX_MESSAGE_SIZE (32*1024)

#define DEBUG_PRINT (1U)

Void NetworkCtrl_cmdHandlerdevRequest(char *cmd, UInt32 prmSize)
{
    Int32 status = 0;
    UInt32 linkId;
    UInt8 *gRequestBuf = ChainsCommon_Osal_memAlloc(NETWORK_CTRL_MAX_MESSAGE_SIZE,
                                                 32U);
    UInt8 *gRespBuf = ChainsCommon_Osal_memAlloc(NETWORK_CTRL_MAX_MESSAGE_SIZE,
                                                 32U);
    DevComm_NetworkCtrlReqPrms * devCtrlPrms = ChainsCommon_Osal_memAlloc(
                                    sizeof(DevComm_NetworkCtrlReqPrms),
                                    32U);
#if (DEBUG == (1U))
    Vps_printf(" NETWORK_CTRL: Waiting for device params\n");
#endif
    /* read parameters */
    NetworkCtrl_readParams((UInt8*)gRequestBuf, prmSize);

    /* send Request */
#if (DEBUG == (1U))
    Vps_printf(" NETWORK_CTRL: Sending control command to IPU1_0\n");
#endif
    devCtrlPrms->reqParam = gRequestBuf;
    devCtrlPrms->reqParamSize = prmSize;
    devCtrlPrms->respParam = gRespBuf;
    linkId = SYSTEM_LINK_ID_IPU1_0;
    System_linkControl(
        linkId,
        SYSTEM_LINK_CMD_DEV_COMM,
        devCtrlPrms,
        sizeof(DevComm_NetworkCtrlReqPrms),
        TRUE);
#if (DEBUG == (1U))
    Vps_printf(" NETWORK_CTRL: Returning from IPU1_0\n");
#endif
    if (status == 0)
    {
        /* send response */
        if (devCtrlPrms->respParamSize == 0U)
        {
            NetworkCtrl_writeParams(NULL, 0, 0);
        }
        else
        {
            Vps_printf(" RespParam = 0x%x\n", *(uint32_t*)devCtrlPrms->respParam);
            NetworkCtrl_writeParams(gRespBuf, devCtrlPrms->respParamSize, 0);
        }
    }
    else
    {
        /* send response */
        NetworkCtrl_writeParams(NULL, 0, (UInt32)-1);
    }
    ChainsCommon_Osal_memFree(gRequestBuf, NETWORK_CTRL_MAX_MESSAGE_SIZE);
    ChainsCommon_Osal_memFree(gRespBuf, NETWORK_CTRL_MAX_MESSAGE_SIZE);
    ChainsCommon_Osal_memFree(devCtrlPrms, sizeof(DevComm_NetworkCtrlReqPrms));
}
