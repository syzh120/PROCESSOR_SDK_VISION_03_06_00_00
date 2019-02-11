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
 * \file utils_remote_log_client.c
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
#include "utils_remote_log_client.h"
#include <src/rtos/utils_common/include/utils.h>
#include <src/rtos/utils_common/include/utils_uart.h>
#include <include/link_api/system_common.h>
#include <src/rtos/links_common/system/system_priv_common.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

#define UTILS_REMOTE_LOG_CLIENT_ASCII_0     (48)
#define UTILS_REMOTE_LOG_CLIENT_ASCII_9     (57)


/**
 *******************************************************************************
 * \brief Task Stack
 *******************************************************************************
 */
/* MISRA.PRAGMA
 * MISRAC_2004 Rule_3.4
 * Non-documented pragma directive.
 * KW State: Fixed in Later Release -> Waiver
 * MISRAC_WAIVER:
 * KW tool cannot understand the pragma supported by CGTools like
 * DATA_ALIGN and DATA_SECTION. But these are valid pragmas.
 */
#pragma DATA_ALIGN(gRemoteLogClient_tskStack, 32)
#pragma DATA_SECTION(gRemoteLogClient_tskStack, ".bss:taskStackSection")

/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * Name 'gRemoteLogClient_tskStack' visibility is too wide.
 * KW State: Ignore -> Waiver -> Case by case
 * MISRAC_WAIVER:
 * static global variable used in many functions, but not accessed by any
 * other file.
 */
static UInt8 gRemoteLogClient_tskStack[REMOTE_LOG_CLIENT_TSK_STACK_SIZE];

/**
 *******************************************************************************
 *
 * \brief Global remote log client object
 *
 *******************************************************************************
*/
static RemoteLog_ClientObj gRemoteLog_clientObj;

/*******************************************************************************
 *  Local Functions Declarations
 *******************************************************************************
 */
static Int32 RemoteLog_mapMem(void);
static Void remoteLogClientPrdFunc(UArg arg);
static UInt32 RemoteLog_clientGetLine(UInt32 coreId, char pString[],
                UInt32 *strSize);
static Void RemoteLog_clientRun(UArg arg0, UArg arg1);

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
    Int32 status = SYSTEM_LINK_STATUS_SOK;

    /* Mmap is not required since client is on M4, phy and virt address are
     * same
     */
    gRemoteLog_clientObj.coreObjVirtBaseAddr =
        gRemoteLog_clientObj.coreObjPhysBaseAddr;

    if (gRemoteLog_clientObj.coreObjVirtBaseAddr == 0U)
    {
        /* MISRA.STDLIB.STDIO
         * MISRAC_2004 Rule_20.9
         * App utils can use printf,scanf functions for debug purpose..
         */
        printf(" ERROR: mmap() failed !!!\n");
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

  return (status);
}

/**
 *******************************************************************************
 *
 * \brief Remote log client periodic call back function
 *
 *       This function is a periodic callback function for remote log client.
 *       This function post semaphores on which actual function which reads
 *       from remote buffers and print on uart gets unblocked
 *
 * \param   arg     [IN] Remote log client object
 *
 * \return  None
 *
 *******************************************************************************
 */
static Void remoteLogClientPrdFunc(UArg arg)
{
    /* Post semaphore so that  function which prints from the
     * the shared buffer gets scheduled
     */
    BspOsal_semPost(gRemoteLog_clientObj.lock);


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
static UInt32 RemoteLog_clientGetLine(UInt32 coreId, char pString[],
                UInt32 *strSize)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    volatile UInt32 breakLoop;
    volatile UInt32 numBytes = 0U, copyBytes = 0U, serverIdx;
    volatile UInt32 clientIdx, idx = 0U;
    volatile UInt8 curChar;
    volatile UInt8 *pSrc;
    volatile RemoteLog_MemInfo *pMemInfo =
                gRemoteLog_clientObj.pMemInfo[coreId];
    RemoteLog_ServerIndexInfo *idxInfo = NULL;

    if(pMemInfo->headerTag != REMOTE_LOG_HEADER_TAG)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        idxInfo = RemoteLog_getCoreIdxInfo(coreId);
        if (NULL == idxInfo)
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    if (0 == status)
    {
        serverIdx = pMemInfo->serverIdx;
        clientIdx = pMemInfo->clientIdx;

        if(clientIdx > serverIdx)
        {
            numBytes = (idxInfo->size - clientIdx) + serverIdx;
        }
        else
        {
            numBytes = serverIdx - clientIdx;
        }

        if(numBytes > 0U)
        {
            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * Pointer is used in arithmetic or array index expression.
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Pointer is initialized with the address of array variable and
             * then accessed as an array. Check is added to make sure that
             * pointer is never accessed beyond size of the array.
             */
            pSrc = &gRemoteLog_clientObj.pServerLogBuf[idxInfo->startIdx];

            for(copyBytes = 0U; copyBytes < numBytes; copyBytes ++)
            {
                if(clientIdx >= idxInfo->size)
                {
                    clientIdx = 0;
                }

                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * MISRAC_WAIVER:
                 * Pointer is initialized with the address of array variable and
                 * then accessed as an array
                 * Check is added to make sure that array/pointer access
                 * is never beyond its size
                 */
                curChar = pSrc[clientIdx];

                clientIdx++;

                if (curChar==(UInt8)0xA0)
                {
                    breakLoop = (UInt32)TRUE;
                }
                else if (curChar==(UInt8)'\r')
                {
                    breakLoop = (UInt32)TRUE;
                }
                else if (curChar==(UInt8)'\n')
                {
                    breakLoop = (UInt32)TRUE;
                }
                else if (curChar==(UInt8)0)
                {
                    breakLoop = (UInt32)TRUE;
                }
                else if (copyBytes >= idxInfo->size)
                {
                    breakLoop = (UInt32)TRUE;
                }
                else if (copyBytes > (REMOTE_LOG_LINE_BUF_SIZE - 32U))
                {
                    breakLoop = (UInt32)TRUE;
                }
                else
                {
                    pString[idx] = (char)curChar;
                    idx ++;
                    breakLoop = (UInt32)FALSE;
                }

                if ((UInt32)TRUE == breakLoop)
                {
                    break;
                }
            }

            pMemInfo->clientIdx = clientIdx;

            /* dummy read to resure data is written to memory */
            clientIdx = pMemInfo->clientIdx;
        }

        pString[idx] = (char)0;
        *strSize = copyBytes;
    }

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
static Void RemoteLog_clientRun(UArg arg0, UArg arg1)
{
    UInt32 coreId;
    UInt32 numBytes, strSize, doPrint;
    char procName[16];
    static char printString[1024];

    while (1)
    {
        doPrint = (UInt32)TRUE;

        BspOsal_semWait(gRemoteLog_clientObj.lock,
                       BSP_OSAL_WAIT_FOREVER);

        #ifdef ENABLE_UART_LOG
        if(!System_isUartInitDone())
        {
            doPrint = (UInt32)FALSE;
        }
        #endif

        if ((UInt32)TRUE == doPrint)
        {
            for(coreId=0U; coreId<SYSTEM_PROC_MAX; coreId++)
            {
                if(System_isProcEnabled(coreId))
                {
                    snprintf(procName, 16U, "[%-6s] ",
                        System_getProcName(coreId));
                    do
                    {
                        numBytes = RemoteLog_clientGetLine(coreId,
                                gRemoteLog_clientObj.lineBuf,
                                &strSize );
                        if(strSize>0)
                        {
                            snprintf(printString, sizeof(printString), "%s%s\r\n",
                                    procName,
                                    gRemoteLog_clientObj.lineBuf);

                            #ifdef ENABLE_UART_LOG
                            uartPrint(printString);
                            #endif

                            #ifdef ENABLE_NETWORK_LOG
                            {
                                Int32 NetworkCons_txWriteString(char *data);

                                NetworkCons_txWriteString(printString);
                            }
                            #endif

                            #ifdef ENABLE_CCS_LOG
                            {
                                /* WORKAROUND: Uncomment this is UART does
                                   not work on EVM
                                 */
                                System_printf(printString);
                            }
                            #endif
                        }
                    } while(numBytes);
                }
            }
        }
    }
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
Int32 Utils_remoteLogClientInit(void)
{
    UInt32 coreId;
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    volatile RemoteLog_MemInfo *pMemInfo;
    RemoteLog_ClientObj *pObj;
    BspOsal_TaskHandle tsk;
    volatile UInt32 startPtr;
    UInt32 memLocation;
    RemoteLog_ServerIndexInfo *idxInfo;

    memset(&gRemoteLog_clientObj, 0, sizeof(gRemoteLog_clientObj));

    /* MISRA.CAST.PTR_TO_INT
     * MISRAC_2004_Rule_11.3
     * Casting between a pointer to an integral type
     * KW State: Ignore -> Waiver -> Case by case
     * MISRAC_WAIVER:
     * Shared memory address is assigned to local variable.
     */
    gRemoteLog_clientObj.coreObjPhysBaseAddr =
                                    (UInt32)&gRemoteLog_coreObj;
    gRemoteLog_clientObj.coreObjTotalMemSize =
                        sizeof(RemoteLog_CoreObj);

    status = RemoteLog_mapMem();

    if (0 == status)
    {
        startPtr = gRemoteLog_clientObj.coreObjVirtBaseAddr +
            (sizeof(RemoteLog_MemInfo) * (UInt32)SYSTEM_PROC_MAX);

        for(coreId = 0U; coreId < SYSTEM_PROC_MAX; coreId ++)
        {
            memLocation = gRemoteLog_clientObj.coreObjVirtBaseAddr +
                (sizeof(RemoteLog_MemInfo) * (UInt32)coreId);

            /* MISRA.CAST.PTR_TO_INT
             * MISRAC_2004_Rule_11.3
             * Casting between a pointer to an integral type
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Shared memory address is assigned to local variable.
             */
            gRemoteLog_clientObj.pMemInfo[coreId] =
                (RemoteLog_MemInfo*)memLocation;

            idxInfo = RemoteLog_getCoreIdxInfo(coreId);
            if (NULL != idxInfo)
            {
                pMemInfo = gRemoteLog_clientObj.pMemInfo[coreId];

                pMemInfo->serverIdx = 0;
                pMemInfo->clientIdx = 0;
                pMemInfo->headerTag = REMOTE_LOG_HEADER_TAG;

                /* MISRA.STDLIB.STDIO
                 * MISRAC_2004 Rule_20.9
                 * App utils can use printf,scanf functions for debug purpose..
                 */
                printf(" %s Remote Log Shared Memory @ 0x%08x\n",
                    System_getProcName(coreId),
                    startPtr + idxInfo->startIdx);
            }
        }

        memLocation = gRemoteLog_clientObj.coreObjVirtBaseAddr +
                    (sizeof(RemoteLog_MemInfo) * (UInt32)SYSTEM_PROC_MAX);
        /* MISRA.CAST.PTR_TO_INT
         * MISRAC_2004_Rule_11.3
         * Casting between a pointer to an integral type
         * KW State: Ignore -> Waiver -> Case by case
         * MISRAC_WAIVER:
         * Shared memory address is assigned to local variable.
         */
        gRemoteLog_clientObj.pServerLogBuf = (volatile UInt8 *)memLocation;

        pObj = &gRemoteLog_clientObj;

        pObj->lock = BspOsal_semCreate(1, (Bool)TRUE);
        UTILS_assert(pObj->lock != NULL);

        /* MISRA.CAST.Func.Ptr
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Casting it to clock function pointer. this cannot be avoided as
         * clock create function expects function pointer of this type.
         */
        pObj->prd.clkHandle = BspOsal_clockCreate(
                                (BspOsal_ClockFuncPtr)remoteLogClientPrdFunc,
                                REMOTE_LOG_CLIENT_PERIOD_MS,
                                (Bool)FALSE,
                                pObj);
        UTILS_assert(pObj->prd.clkHandle!=NULL);
        pObj->prd.clkStarted = (Bool)FALSE;

        BspOsal_clockStart(pObj->prd.clkHandle);
        pObj->prd.clkStarted = (Bool)TRUE;

        /* MISRA.CAST.Func.Ptr
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Casting it to task function pointer. this cannot be avoided as
         * task create function expects function pointer of this type.
         */
        /* Create task for printing remote core and local core messages from
         * buffer
         */
        tsk = BspOsal_taskCreate(
                        (BspOsal_TaskFuncPtr)RemoteLog_clientRun,
                        "RemoteLog_clientRun",
                        (Int32)REMOTE_LOG_CLIENT_TSK_PRI,
                        (void *)gRemoteLogClient_tskStack,
                        sizeof(gRemoteLogClient_tskStack),
                        NULL,
                        UTILS_TSK_AFFINITY_CORE0
                    );
        UTILS_assert(tsk != NULL);
    }

    return (status);
}

