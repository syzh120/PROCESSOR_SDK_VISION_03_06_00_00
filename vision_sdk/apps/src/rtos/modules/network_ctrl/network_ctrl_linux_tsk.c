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
  ******************************************************************************
 * \file networkCtrl_tsk.c
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "network_ctrl_priv.h"

#define NETWORK_CTRL_TSK_STACK_SIZE  (16*KB)

/**
 *******************************************************************************
 * \brief stores all module related information
 *******************************************************************************
 */
NetworkCtrl_Obj gNetworkCtrl_obj;

Void NetworkCtrl_cmdHandlerUnsupportedCmd(char *cmd, UInt32 prmSize)
{
    UInt8 *pBuf, *pVirtBuf;

    /* alloc tmp buffer for parameters */
    if(prmSize)
    {
        pBuf = ChainsCommon_Osal_memAlloc(prmSize, 32);
        UTILS_assert(pBuf != NULL);
        pVirtBuf = (UInt8*)ChainsCommon_Osal_getVirtAddr((UInt32)pBuf);

        /* read parameters */
        NetworkCtrl_readParams(pVirtBuf, prmSize);

        Vps_printf(" NETWORK_CTRL: %s: UNSUPPORTED CMD (prmSize=%d) !!!\n",
            cmd, prmSize);

        ChainsCommon_Osal_memFree(pBuf, prmSize);
    }

    /* send response */
    NetworkCtrl_writeParams(NULL, 0, (UInt32)-1);
}

Int32 NetworkCtrl_registerHandler(char *cmd, NetworkCtrl_Handler handler)
{
    NetworkCtrl_Obj *pObj = &gNetworkCtrl_obj;
    int i;
    int firstFreeIdx;

    firstFreeIdx = -1;

    /* check if command is already registered */
    for(i=0; i<NETWORK_CTRL_MAX_CMDS; i++)
    {
        if(pObj->cmdHandler[i].handler)
        {
            if(strncmp(
                pObj->cmdHandler[i].cmd,
                cmd,
                NETWORK_CTRL_CMD_STRLEN_MAX)
                ==0)
            {
                /* command already register, exit with error */
                return -1;
            }
        }
        else
        {
            if(firstFreeIdx==-1)
            {
                firstFreeIdx = i;
            }
        }
    }

    /* no space to register command */
    if(firstFreeIdx==-1)
        return -1;

    /* command not registered, register it */
    pObj->cmdHandler[firstFreeIdx].handler = handler;
    strcpy(pObj->cmdHandler[firstFreeIdx].cmd, cmd);

    return 0;
}

Int32 NetworkCtrl_unregisterHandler(char *cmd)
{
    NetworkCtrl_Obj *pObj = &gNetworkCtrl_obj;
    int i;

    /* check if command is already registered */
    for(i=0; i<NETWORK_CTRL_MAX_CMDS; i++)
    {
        if(pObj->cmdHandler[i].handler)
        {
            if(strncmp(
                pObj->cmdHandler[i].cmd,
                cmd,
                NETWORK_CTRL_CMD_STRLEN_MAX)
                ==0)
            {
                /* command found, unregister it */
                pObj->cmdHandler[i].handler = NULL;
                pObj->cmdHandler[i].cmd[0] = 0;
            }
        }
    }

    return 0;
}

Int32 NetworkCtrl_readParams(UInt8 *pPrm, UInt32 prmSize)
{
    NetworkCtrl_Obj *pObj = &gNetworkCtrl_obj;
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    if(prmSize)
    {
        status = Network_read(&pObj->sockObj, pPrm, &prmSize);

        if(status<0)
        {
            Vps_printf(
                " NETWORK_CTRL: Network_read() failed to read parameters (port=%d) !!!\n",
                    pObj->serverPort);
        }
    }

    return status;
}

Int32 NetworkCtrl_writeParams(UInt8 *pPrm, UInt32 prmSize, UInt32 returnStatus)
{
    NetworkCtrl_Obj *pObj = &gNetworkCtrl_obj;
    Int32 status;

    pObj->cmdBuf.prmSize = prmSize;
    pObj->cmdBuf.returnValue = returnStatus;
    pObj->cmdBuf.flags = NETWORK_CTRL_FLAG_ACK;

    status = Network_write(&pObj->sockObj, (UInt8*)&pObj->cmdBuf,
        sizeof(pObj->cmdBuf));

    if(status<0)
    {
        Vps_printf(
            " NETWORK_CTRL: Network_write() failed to write response header (port=%d) !!!\n",
                pObj->serverPort);

        return status;
    }

    if(prmSize)
    {
        status = Network_write(&pObj->sockObj, pPrm, prmSize);

        if(status<0)
        {
            Vps_printf(
                " NETWORK_CTRL: Network_write() failed to write parameters (port=%d) !!!\n",
                    pObj->serverPort);
        }
    }

    return status;
}

void *NetworkCtrl_tskMain(void *arg0)
{
    NetworkCtrl_Obj *pObj = (NetworkCtrl_Obj*)arg0;
    Int32 status;
    volatile UInt32 dataSize;

    Vps_printf(
        " NETWORK_CTRL: Starting Server (port=%d) !!!\n", pObj->serverPort
        );

    status = Network_open(&pObj->sockObj, pObj->serverPort);
    UTILS_assert(status==0);

    Vps_printf(
        " NETWORK_CTRL: Starting Server ... DONE (port=%d) !!!\n",
        pObj->serverPort
        );

    while(!gNetworkCtrl_obj.tskExit)
    {
        status = Network_waitConnect(&pObj->sockObj, 10000);

        if(status<0)
            break;

        if(status==0)
            continue;

        dataSize = sizeof(pObj->cmdBuf);

        /* read command header */
        status = Network_read(&pObj->sockObj, (UInt8*)&pObj->cmdBuf,
            (UInt32*)&dataSize);

        if(status==SYSTEM_LINK_STATUS_SOK && dataSize==sizeof(pObj->cmdBuf))
        {
            /* handle command */
            if(pObj->cmdBuf.header != NETWORK_CTRL_HEADER)
            {
                Vps_printf(
                    " NETWORK_CTRL: Invalid header received (port=%d) !!!\n",
                    pObj->serverPort);
            }
            else
            {
                Bool isCmdHandled;
                int i;

                isCmdHandled = FALSE;

                /* valid header received */
                for(i=0; i<NETWORK_CTRL_MAX_CMDS; i++)
                {
                    if(strncmp(
                        pObj->cmdHandler[i].cmd,
                        pObj->cmdBuf.cmd,
                        NETWORK_CTRL_CMD_STRLEN_MAX)
                        ==0)
                    {
                        /* matched a register command */

                        if(pObj->cmdHandler[i].handler)
                        {
                            Vps_printf(
                                " NETWORK_CTRL: Received command [%s], with %d bytes of parameters\n",
                                pObj->cmdBuf.cmd,
                                pObj->cmdBuf.prmSize
                                );

                            pObj->cmdHandler[i].handler(
                                pObj->cmdBuf.cmd,
                                pObj->cmdBuf.prmSize
                                );

                            Vps_printf(
                                " NETWORK_CTRL: Sent response for command [%s], with %d bytes of parameters\n",
                                pObj->cmdBuf.cmd,
                                pObj->cmdBuf.prmSize
                                );

                            isCmdHandled = TRUE;
                            break;
                        }
                    }
                }

                if(isCmdHandled == FALSE)
                {
                    /* if command is not handled, then read the params and
                       ACK it with error */
                    NetworkCtrl_cmdHandlerUnsupportedCmd(
                        pObj->cmdBuf.cmd,
                        pObj->cmdBuf.prmSize
                        );
                }
            }
        }
        else
        {
            Vps_printf(" NETWORK_CTRL: recv() failed (port=%d) !!!\n",
                pObj->serverPort);
        }

        /* close socket */
        Network_close(&pObj->sockObj, FALSE);
    }

    Vps_printf(
        " NETWORK_CTRL: Closing Server (port=%d) !!!\n", pObj->serverPort
        );

    Network_close(&pObj->sockObj, TRUE);

    Vps_printf(
        " NETWORK_CTRL: Closing Server ... DONE (port=%d) !!!\n", pObj->serverPort
        );

    return NULL;
}

Int32 NetworkCtrl_init()
{
    int status;

    memset(&gNetworkCtrl_obj, 0, sizeof(gNetworkCtrl_obj));

    gNetworkCtrl_obj.serverPort = NETWORK_CTRL_SERVER_PORT;

    NetworkCtrl_registerHandler("echo", NetworkCtrl_cmdHandlerEcho);
    NetworkCtrl_registerHandler("mem_rd", NetworkCtrl_cmdHandlerMemRd);
    NetworkCtrl_registerHandler("mem_wr", NetworkCtrl_cmdHandlerMemWr);
#ifdef ISS_INCLUDE
    NetworkCtrl_registerHandler("iss_raw_save", NetworkCtrl_cmdHandlerIssRawSave);
    NetworkCtrl_registerHandler("iss_yuv_save", NetworkCtrl_cmdHandlerIssIspSave);
    NetworkCtrl_registerHandler("iss_isp_save", NetworkCtrl_cmdHandlerIssIspSave);
    NetworkCtrl_registerHandler("iss_send_dcc_file", NetworkCtrl_cmdHandlerIssDccSendFile);
    NetworkCtrl_registerHandler("iss_save_dcc_file", NetworkCtrl_cmdHandlerIssSaveDccFile);
    NetworkCtrl_registerHandler("iss_clear_dcc_qspi_mem", NetworkCtrl_cmdHandlerIssClearDccQspiMem);
    NetworkCtrl_registerHandler("iss_write_sensor_reg", NetworkCtrl_cmdHandleIssWriteSensorReg);
    NetworkCtrl_registerHandler("iss_read_sensor_reg", NetworkCtrl_cmdHandleIssReadSensorReg);
    NetworkCtrl_registerHandler("iss_read_2a_params", NetworkCtrl_cmdHandleIssRead2AParams);
    NetworkCtrl_registerHandler("iss_write_2a_params", NetworkCtrl_cmdHandleIssWrite2AParams);
#endif

    /*
     * Create task
     */
    status = OSA_thrCreate(&gNetworkCtrl_obj.thrHndl,
                           NetworkCtrl_tskMain,
                           OSA_THR_PRI_DEFAULT,
                           NETWORK_CTRL_TSK_STACK_SIZE,
                           (void *)&gNetworkCtrl_obj);
    UTILS_assert(0u == status);

    return SYSTEM_LINK_STATUS_SOK;
}

Int32 NetworkCtrl_deInit()
{
    gNetworkCtrl_obj.tskExit = TRUE;

    OSA_thrDelete(&gNetworkCtrl_obj.thrHndl);

    NetworkCtrl_unregisterHandler("echo");
    NetworkCtrl_unregisterHandler("mem_rd");
    NetworkCtrl_unregisterHandler("mem_wr");

    #ifdef ISS_INCLUDE
    NetworkCtrl_unregisterHandler("iss_raw_save");
    NetworkCtrl_unregisterHandler("iss_yuv_save");
    NetworkCtrl_unregisterHandler("iss_isp_save");
    NetworkCtrl_unregisterHandler("iss_send_dcc_file");
    NetworkCtrl_unregisterHandler("iss_save_dcc_file");
    NetworkCtrl_unregisterHandler("iss_clear_dcc_qspi_mem");
    NetworkCtrl_unregisterHandler("iss_write_sensor_reg");
    NetworkCtrl_unregisterHandler("iss_read_sensor_reg");
    NetworkCtrl_unregisterHandler("iss_read_2a_params");
    NetworkCtrl_unregisterHandler("iss_write_2a_params");
    #endif

    return SYSTEM_LINK_STATUS_SOK;
}

