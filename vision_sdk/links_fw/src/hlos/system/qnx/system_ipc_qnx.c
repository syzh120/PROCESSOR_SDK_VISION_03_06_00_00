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
 * \file system_ipc.c
 *
 * \brief  Wrapper around system rpmsg components calls.
 *
 *         This file implements wrapper around rpmsg calls.
 *
 * \version 0.0 (May 2014) : [YM] First version implemented
 *
 *******************************************************************************
 */

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <osa_mem_map.h>
#include "system_priv_ipc.h"
#include <sys/types.h>

#include <errno.h>

/* Ipc Socket Protocol Family */
#include <ti/ipc/TiIpcFxns.h>
#include <ti/ipc/ti_ipc.h>

System_IpcSharedMemObj  *gSystem_ipcSharedMemObj;

/**
 *******************************************************************************
 *
 * \brief Wrapper to initialize IPC sub-system.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_ipcInit(void)
{
    Int32 status;

    Vps_printf(" SYSTEM: IPC: Init in progress !!!\n");

    gSystem_ipcSharedMemObj = (System_IpcSharedMemObj*)
                                OSA_memPhys2Virt(
                                    SYSTEM_IPC_SHM_MEM_ADDR,
                                    OSA_MEM_REGION_TYPE_SYSTEM_IPC
                                );
    OSA_assert(gSystem_ipcSharedMemObj!=NULL);

    status = System_ipcNotifyInit();
    OSA_assertSuccess(status);

    status = System_ipcMsgQInit();
    OSA_assertSuccess(status);

    Vps_printf(" SYSTEM: IPC: Init DONE !!!\n");

    return SYSTEM_LINK_STATUS_SOK;
}
/**
 *******************************************************************************
 *
 * \brief Wrapper to de-initialize IPC sub-system.
 *
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
Int32 System_ipcDeInit(void)
{
    Vps_printf(" SYSTEM: IPC: De-init in progress !!!\n");

    System_ipcMsgQDeInit();
    System_ipcNotifyDeInit();

    Vps_printf(" SYSTEM: IPC: De-init DONE !!!\n");

    return SYSTEM_LINK_STATUS_SOK;
}

Bool System_isProcEnabled(UInt32 procId)
{
     UInt32 i;
     Bool isEnabled;

     i = 0;
     isEnabled = FALSE;

     while (gSystem_ipcEnableProcId[i] != SYSTEM_PROC_MAX)
     {
         if(procId == gSystem_ipcEnableProcId[i])
         {
             isEnabled = TRUE;
             break;
         }

         i++;
     }

     return isEnabled;
}

char *System_getProcName(UInt32 procId)
{
    if(procId==SYSTEM_PROC_DSP1)
        return SYSTEM_IPC_PROC_NAME_DSP1;

    if(procId==SYSTEM_PROC_DSP2)
        return SYSTEM_IPC_PROC_NAME_DSP2;

    if(procId==SYSTEM_PROC_EVE1)
        return SYSTEM_IPC_PROC_NAME_EVE1;

    if(procId==SYSTEM_PROC_EVE2)
        return SYSTEM_IPC_PROC_NAME_EVE2;

    if(procId==SYSTEM_PROC_EVE3)
        return SYSTEM_IPC_PROC_NAME_EVE3;

    if(procId==SYSTEM_PROC_EVE4)
        return SYSTEM_IPC_PROC_NAME_EVE4;

    if(procId==SYSTEM_PROC_IPU1_0)
        return SYSTEM_IPC_PROC_NAME_IPU1_0;

    if(procId==SYSTEM_PROC_IPU1_1)
        return SYSTEM_IPC_PROC_NAME_IPU1_1;

    if(procId==SYSTEM_PROC_IPU2)
        return SYSTEM_IPC_PROC_NAME_IPU2;

    if(procId==SYSTEM_PROC_A15_0)
        return SYSTEM_IPC_PROC_NAME_A15_0;

    return SYSTEM_IPC_PROC_NAME_INVALID;
}


Int32 System_ipcCreateChannel(UInt32 procId, UInt32 endpt, UInt32 channelType)
{
    UInt32 syslinkProcId = System_getSyslinkProcId(procId);
    Int32 err = 0;
    Int32 fd  = 0;

    /* create an RPMSG socket */
    fd = open("/dev/tiipc", O_RDWR);
    if (fd < 0) {
        Vps_printf(" SYSTEM: IPC: [%s] socket open failed (%s, %d) !!!\n",
                System_getProcName(procId), strerror(errno), errno);
        return -1;
    }

    if(channelType == SYSTEM_RPMSG_RX_CHANNEL)
    {
        err = TiIpcFxns_connect(fd, (UInt16)_MultiProc_cfg.rprocList[syslinkProcId], endpt);
        if(err>=0)
        {
            Vps_printf(" SYSTEM: IPC: [%s] RX - TiIpcFxns_connect success !!!"
                        " (endpt = %d)\n",
                        System_getProcName(procId),
                        endpt);
        }
        else
        {
            Vps_printf(" SYSTEM: IPC: [%s] RX - TiIpcFxns_connect failed (%d) !!!\n",
                System_getProcName(procId), err);
            return -1;
        }

        err = TiIpcFxns_bindAddr(fd, endpt);
        if (err >= 0) {
            Vps_printf(" SYSTEM: IPC: [%s] RX - TiIpcFxns_bindAddr success !!!"
                    " (endpt = %d)\n",
                    System_getProcName(procId),
                    endpt);
        }
        else
        {
            Vps_printf(" SYSTEM: IPC: [%s] RX - TiIpcFxns_bindAddr failed (%d) !!!\n",
                System_getProcName(procId), err);
            return -1;
        }
    }
    else if(channelType == SYSTEM_RPMSG_TX_CHANNEL)
    {
        err = TiIpcFxns_connect(fd, (UInt16)_MultiProc_cfg.rprocList[syslinkProcId], endpt);
        if(err>=0)
        {
            Vps_printf(" SYSTEM: IPC: [%s] TX - TiIpcFxns_connect success !!!"
                        " (endpt = %d)\n",
                        System_getProcName(procId),
                        endpt);
        }
        else
        {
            Vps_printf(" SYSTEM: IPC: [%s] TX - TiIpcFxns_connect failed (%d) !!!\n",
                System_getProcName(procId), err);
            return -1;
        }

        err = TiIpcFxns_bindAddr(fd, TIIPC_ADDRANY);
        if (err >= 0) {
            Vps_printf(" SYSTEM: IPC: [%s] TX - TiIpcFxns_bindAddr success !!!"
                    " (endpt = %d)\n",
                    System_getProcName(procId),
                    endpt);
        }
        else
        {
            Vps_printf(" SYSTEM: IPC: [%s] TX - TiIpcFxns_bindAddr failed to get local addr(%d) !!!\n",
            System_getProcName(procId), err);
            return -1;
        }
    }
    else
    {
        OSA_assert(0);
    }

    /* let's see what local address we got, this will be required to validate source
     * of the received message on remote end to avoid acting on any malicious message.
     */
    tiipc_local_params local;
    err = ioctl(fd, TIIPC_IOCGETLOCAL, &local);
    if (err < 0) {
        Vps_printf(" SYSTEM: IPC: [%s] ioctl TIIPC_IOCGETLOCAL failed (%d) !!!\n",
            System_getProcName(procId), err);
        return -1;
    }

    Vps_printf(" SYSTEM: IPC: [%s] socket info (endpt = %d) !!!\n",
        System_getProcName(procId), endpt);

    return fd;

}

Int32 System_ipcDeleteChannel(Int32 fd)
{
    Int32 err = 0;

    err = close(fd);

    if(err < 0)
    {
        Vps_printf(" SYSTEM: IPC: socket close failed (%s, %d) !!!\n",
                strerror(errno), errno);
    }

    return err;
}

UInt32 System_getSyslinkProcId(UInt32 procId)
{
    char *procName = System_getProcName(procId);

    if(strcmp(procName, SYSTEM_IPC_PROC_NAME_INVALID)!=0)
    {
        return MultiProc_getId(procName);
    }

    return MultiProc_INVALIDID;
}

System_IpcMsg *System_ipcGetMsg(uint32_t procId)
{
    System_IpcSharedMemObj *pObj = gSystem_ipcSharedMemObj;
    System_IpcMsg *pPrm = NULL;

    if(procId < SYSTEM_PROC_MAX)
    {
        pPrm = &pObj->ipcMsgObj.procMsg[procId];
    }

    return pPrm;
}

System_IpcQueObj *System_ipcGetIpcOut2InQue(uint32_t ipcOutLinkId)
{
    System_IpcSharedMemObj *pObj = gSystem_ipcSharedMemObj;
    System_IpcQueObj *pPrm = NULL;
    UInt32 procId = SYSTEM_GET_PROC_ID(ipcOutLinkId);
    UInt32 linkId = SYSTEM_GET_LINK_ID(ipcOutLinkId);
    UInt32 linkInstId;

    if(     procId < SYSTEM_PROC_MAX
        &&  linkId < SYSTEM_LINK_ID_MAX
        &&  (Int32)linkId >= SYSTEM_LINK_ID_IPC_OUT_0
        )
    {
        linkInstId = linkId - SYSTEM_LINK_ID_IPC_OUT_0;

        if(linkInstId < SYSTEM_IPC_OUT_LINK_MAX)
        {
            pPrm =
                &pObj->ipcQueObj.ipcQueProcObj[procId].queOut2InObj[linkInstId];
        }
    }

    return pPrm;
}

System_IpcQueObj *System_ipcGetIpcIn2OutQue(uint32_t ipcOutLinkId)
{
    System_IpcSharedMemObj *pObj = gSystem_ipcSharedMemObj;
    System_IpcQueObj *pPrm = NULL;
    UInt32 procId = SYSTEM_GET_PROC_ID(ipcOutLinkId);
    UInt32 linkId = SYSTEM_GET_LINK_ID(ipcOutLinkId);
    UInt32 linkInstId;

    if(     procId < SYSTEM_PROC_MAX
        &&  linkId < SYSTEM_LINK_ID_MAX
        &&  (Int32)linkId >= SYSTEM_LINK_ID_IPC_OUT_0
        )
    {
        linkInstId = linkId - SYSTEM_LINK_ID_IPC_OUT_0;

        if(linkInstId < SYSTEM_IPC_OUT_LINK_MAX)
        {
            pPrm =
                &pObj->ipcQueObj.ipcQueProcObj[procId].queIn2OutObj[linkInstId];
        }
    }

    return pPrm;
}

System_IpcBuffer *System_ipcGetIpcBuffer(uint32_t ipcOutLinkId, uint32_t index)
{
    System_IpcSharedMemObj *pObj = gSystem_ipcSharedMemObj;
    System_IpcBuffer *pPrm = NULL;
    UInt32 procId = SYSTEM_GET_PROC_ID(ipcOutLinkId);
    UInt32 linkId = SYSTEM_GET_LINK_ID(ipcOutLinkId);
    UInt32 linkInstId;

    if(     procId < SYSTEM_PROC_MAX
        &&  linkId < SYSTEM_LINK_ID_MAX
        &&  index  < SYSTEM_IPC_OUT_LINK_IPC_QUE_MAX_ELEMENTS
        &&  (Int32)linkId >= SYSTEM_LINK_ID_IPC_OUT_0
        )
    {
        linkInstId = linkId - SYSTEM_LINK_ID_IPC_OUT_0;

        if(linkInstId < SYSTEM_IPC_OUT_LINK_MAX)
        {
            pPrm =
                &pObj->ipcQueObj.ipcQueProcObj[procId].queElements[linkInstId][index];
        }
    }

    return pPrm;
}


UInt32 System_ipcMemAlloc(UInt32 heapId, UInt32 memSize, UInt32 memAlign)
{
    Int32 status;
    SystemCommon_AllocBuffer prms;

    prms.heapId = heapId;
    prms.size   = memSize;
    prms.align  = memAlign;

    status = System_linkControl(SYSTEM_LINK_ID_IPU1_0,
                                SYSTEM_COMMON_CMD_ALLOC_BUFFER,
                                (Void *)&prms,
                                sizeof(SystemCommon_AllocBuffer),
                                TRUE);


    OSA_assert((UInt32 *)prms.bufferPtr != NULL);
    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);

    return (prms.bufferPtr);
}


Void System_ipcMemFree(UInt32 heapId, UInt32 addr, UInt32 memSize)
{
    Int32 status;
    SystemCommon_FreeBuffer prms;

    prms.heapId    = heapId;
    prms.size      = memSize;
    prms.bufferPtr = addr;

    status = System_linkControl(SYSTEM_LINK_ID_IPU1_0,
                                SYSTEM_COMMON_CMD_FREE_BUFFER,
                                (Void *)&prms,
                                sizeof(SystemCommon_FreeBuffer),
                                TRUE);

    OSA_assert(status == SYSTEM_LINK_STATUS_SOK);
}
