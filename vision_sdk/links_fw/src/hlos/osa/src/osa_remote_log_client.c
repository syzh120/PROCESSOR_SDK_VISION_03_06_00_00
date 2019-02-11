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
 * \file remote_log_client.c
 *
 * \brief  This file implements remote log client.
 *
 *         This file reads the data from shared memory between host CPU and
 *         all remote cores. It prints the data to console.
 *
 * \version 0.1 (Jul 2013) : [HS] First version
 *
 *******************************************************************************
*/
/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <osa_mem_map.h>
#include "osa_remote_log_client.h"
#include <osa_debug.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define OSA_DEBUG_REMOTE_LOG

/**
 *******************************************************************************
 *
 * \brief Global remote log client object
 *
 *******************************************************************************
*/
static RemoteLog_ClientObj gRemoteLog_clientObj;

/**
 *******************************************************************************
 *
 * \brief Assign the physical address of the buffer to client object
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
static Int32 RemoteLog_mapMem(void)
{
    /* Mmap is not required since client is on M4, phy and virt address are
     * same
     */
    gRemoteLog_clientObj.coreObjVirtBaseAddr = (unsigned char *)
                OSA_memPhys2Virt(gRemoteLog_clientObj.coreObjPhysBaseAddr,
                                OSA_MEM_REGION_TYPE_REMOTE_LOG
                                );

    if (gRemoteLog_clientObj.coreObjVirtBaseAddr==0)
    {
        OSA_printf(" OSA: REMOTELOG: ERROR: mmap() failed !!!\n");
        return -1;
    }

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Get the line of buffer from array of lines.
 *
 * \param  coreId    [IN] Id of the core to log
 * \param  pString   [IN] String to put into shared memory
 * \param  strSize   [OUT] Size of string copied from log buffer
 *
 *
 * \return  returns number of bytes extracted form the log buffer
 *
 *******************************************************************************
 */
static Int32 RemoteLog_clientGetLine(UInt32 coreId, char * pString,
                UInt32 *strSize)
{
    volatile UInt32 numBytes, copyBytes=0, serverIdx, clientIdx;
    volatile unsigned char *pSrc;
    volatile unsigned char curChar;
    volatile RemoteLog_MemInfo *pMemInfo =
                gRemoteLog_clientObj.pMemInfo[coreId];
    RemoteLog_ServerIndexInfo *idxInfo = NULL;

    if(pMemInfo->headerTag != REMOTE_LOG_HEADER_TAG)
        return 0;

    idxInfo = RemoteLog_getCoreIdxInfo(coreId);
    if (NULL == idxInfo)
        return 0;

    serverIdx = pMemInfo->serverIdx;
    clientIdx = pMemInfo->clientIdx;

    if(clientIdx>serverIdx)
        numBytes = (idxInfo->size - clientIdx) + serverIdx;
    else
        numBytes = serverIdx - clientIdx;

    if(numBytes>0)
    {
        pSrc = &gRemoteLog_clientObj.pServerLogBuf[idxInfo->startIdx];

        for(copyBytes=0; copyBytes<numBytes; copyBytes++)
        {
          if(clientIdx>=idxInfo->size)
            clientIdx = 0;

          curChar = pSrc[clientIdx];

          clientIdx++;

          if(curChar==0xA0 || curChar=='\r' ||
             curChar=='\n' ||curChar==0     ||
             copyBytes > (REMOTE_LOG_LINE_BUF_SIZE - 32) ||
             copyBytes >= idxInfo->size)
            break;
          else
            *pString++ = curChar;
        }

        pMemInfo->clientIdx = clientIdx;

        /* dummy read to resure data is written to memory */
        clientIdx = pMemInfo->clientIdx;
    }

    *pString = 0;
    *strSize = copyBytes;

    return numBytes;
}

/**
 *******************************************************************************
 *
 * \brief Run the periodic task for printing data from shared memory
 *
 * \param  arg0     [IN]  Not used
 * \param  arg1     [IN] Not used

 * \return  returns 0 on success
 *
 *******************************************************************************
 */
static void *RemoteLog_clientRun(void *pPrm)
{
    UInt32 coreId;
    UInt32 numBytes, strSize;
    char procName[16];

#ifdef QNX_BUILD
    pthread_setname_np(pthread_self(), "Remote log client thread");
#endif

    while (1)
    {
        OSA_waitMsecs(REMOTE_LOG_CLIENT_PERIOD_MS);

        if(gRemoteLog_clientObj.exitThr==1)
            break;

        for(coreId=0; coreId<SYSTEM_PROC_MAX; coreId++)
        {
            if(System_isProcEnabled(coreId))
            {
                snprintf(procName, sizeof(procName), "[%-6s] ", System_getProcName(coreId));
                do {
                    strSize = 0;
                    numBytes = RemoteLog_clientGetLine(coreId,
                            gRemoteLog_clientObj.lineBuf,
                            &strSize );
                    if(strSize>0)
                    {
#ifndef QNX_BUILD
                        OSA_printf( "%s%s\r\n", procName, gRemoteLog_clientObj.lineBuf);
#else
                        slogf(_SLOGC_INFOADAS_REMOTELOG, _SLOG_INFO, "%s%s", procName, gRemoteLog_clientObj.lineBuf);
#endif
                    }
                }
                while(numBytes);
            }
        }
    }

    gRemoteLog_clientObj.exitThr = 2;

    return NULL;
}

/**
 *******************************************************************************
 *
 * \brief Initializes the remote log client.
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
Int32 OSA_remoteLogClientInit(void)
{
    UInt32 coreId;
    Int32 status;

    memset(&gRemoteLog_clientObj, 0, sizeof(gRemoteLog_clientObj));

    gRemoteLog_clientObj.coreObjPhysBaseAddr =
                                    (UInt32)REMOTE_LOG_MEM_ADDR;

    gRemoteLog_clientObj.coreObjTotalMemSize =
                        sizeof(RemoteLog_CoreObj);

    status = RemoteLog_mapMem();
    if(status != 0)
        return -1;

    for(coreId=0; coreId<SYSTEM_PROC_MAX; coreId++)
    {
        gRemoteLog_clientObj.pMemInfo[coreId] =
            (RemoteLog_MemInfo*)(gRemoteLog_clientObj.coreObjVirtBaseAddr +
                sizeof(RemoteLog_MemInfo)*coreId);

        #ifdef OSA_DEBUG_REMOTE_LOG
        if(System_isProcEnabled(coreId))
        {
            OSA_printf(" OSA: %s Remote Log Shared Memory @ 0x%08x\n",
                System_getProcName(coreId),
                (unsigned int)gRemoteLog_clientObj.coreObjPhysBaseAddr +
                sizeof(RemoteLog_CoreObj)*coreId);
        }
        #endif

    }
    gRemoteLog_clientObj.pServerLogBuf =
        gRemoteLog_clientObj.coreObjVirtBaseAddr +
                sizeof(RemoteLog_MemInfo)*SYSTEM_PROC_MAX;

    /* Create task for printing remote core and local core messages from
     * buffer
     */

    OSA_thrCreate(  &gRemoteLog_clientObj.thrHndl,
                    RemoteLog_clientRun,
                    OSA_THR_PRI_DEFAULT,
                    OSA_THR_STACK_SIZE_DEFAULT,
                    NULL
                );

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Initializes the remote log client.
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
Int32 OSA_remoteLogClientDeInit(void)
{
    /* Create task for printing remote core and local core messages from
     * buffer
     */

    gRemoteLog_clientObj.exitThr = 1;

    while(gRemoteLog_clientObj.exitThr!=2)
        OSA_waitMsecs(1);

    OSA_thrDelete(  &gRemoteLog_clientObj.thrHndl );

    return SYSTEM_LINK_STATUS_SOK;
}


