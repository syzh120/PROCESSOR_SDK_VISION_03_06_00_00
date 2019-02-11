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
 * \file remote_log_server.c
 *
 * \brief  This file has the implementation for logging log information
 *
 *         This file has implementation for writing and reading data into/from
 *         a shared memory.
 * \version 0.0 (Jul 2013) : [HS] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <osa_mem_map.h>
#include <osa.h>
#include <osa_mutex.h>
#include <osa_mem.h>
#include <osa_remote_log_if.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Max allowed parameter buffer size
 *
 *******************************************************************************
 */
#define REMOTE_LOG_SERVER_PRINT_BUF_LEN        (1024*4)

#define REMOTE_LOG_SERVER_IPU1_0_INST_START (0U)
#ifdef IPU_PRIMARY_CORE_IPU1
#define REMOTE_LOG_SERVER_IPU1_0_INST_SIZE  (58*1024U)
#else
#define REMOTE_LOG_SERVER_IPU1_0_INST_SIZE  (10*1024U)
#endif
#define REMOTE_LOG_SERVER_IPU1_0_INST_END   (REMOTE_LOG_SERVER_IPU1_0_INST_START +\
                                            REMOTE_LOG_SERVER_IPU1_0_INST_SIZE)

#define REMOTE_LOG_SERVER_IPU1_1_INST_START (REMOTE_LOG_SERVER_IPU1_0_INST_END)
#define REMOTE_LOG_SERVER_IPU1_1_INST_SIZE  (10*1024U)
#define REMOTE_LOG_SERVER_IPU1_1_INST_END   (REMOTE_LOG_SERVER_IPU1_1_INST_START +\
                                            REMOTE_LOG_SERVER_IPU1_1_INST_SIZE)

#define REMOTE_LOG_SERVER_A15_0_INST_START  (REMOTE_LOG_SERVER_IPU1_1_INST_END)
#define REMOTE_LOG_SERVER_A15_0_INST_SIZE   (20*1024U)
#define REMOTE_LOG_SERVER_A15_0_INST_END    (REMOTE_LOG_SERVER_A15_0_INST_START +\
                                            REMOTE_LOG_SERVER_A15_0_INST_SIZE)

#define REMOTE_LOG_SERVER_DSP1_INST_START   (REMOTE_LOG_SERVER_A15_0_INST_END)
#define REMOTE_LOG_SERVER_DSP1_INST_SIZE    (10*1024U)
#define REMOTE_LOG_SERVER_DSP1_INST_END     (REMOTE_LOG_SERVER_DSP1_INST_START +\
                                            REMOTE_LOG_SERVER_DSP1_INST_SIZE)

#define REMOTE_LOG_SERVER_DSP2_INST_START   (REMOTE_LOG_SERVER_DSP1_INST_END)
#define REMOTE_LOG_SERVER_DSP2_INST_SIZE    (10*1024U)
#define REMOTE_LOG_SERVER_DSP2_INST_END     (REMOTE_LOG_SERVER_DSP2_INST_START +\
                                            REMOTE_LOG_SERVER_DSP2_INST_SIZE)

#define REMOTE_LOG_SERVER_EVE1_INST_START   (REMOTE_LOG_SERVER_DSP2_INST_END)
#define REMOTE_LOG_SERVER_EVE1_INST_SIZE    (10*1024U)
#define REMOTE_LOG_SERVER_EVE1_INST_END     (REMOTE_LOG_SERVER_EVE1_INST_START +\
                                            REMOTE_LOG_SERVER_EVE1_INST_SIZE)

#define REMOTE_LOG_SERVER_EVE2_INST_START   (REMOTE_LOG_SERVER_EVE1_INST_END)
#define REMOTE_LOG_SERVER_EVE2_INST_SIZE    (10*1024U)
#define REMOTE_LOG_SERVER_EVE2_INST_END     (REMOTE_LOG_SERVER_EVE2_INST_START +\
                                            REMOTE_LOG_SERVER_EVE2_INST_SIZE)

#define REMOTE_LOG_SERVER_EVE3_INST_START   (REMOTE_LOG_SERVER_EVE2_INST_END)
#define REMOTE_LOG_SERVER_EVE3_INST_SIZE    (10*1024U)
#define REMOTE_LOG_SERVER_EVE3_INST_END     (REMOTE_LOG_SERVER_EVE3_INST_START +\
                                            REMOTE_LOG_SERVER_EVE3_INST_SIZE)

#define REMOTE_LOG_SERVER_EVE4_INST_START   (REMOTE_LOG_SERVER_EVE3_INST_END)
#define REMOTE_LOG_SERVER_EVE4_INST_SIZE    (10*1024U)
#define REMOTE_LOG_SERVER_EVE4_INST_END     (REMOTE_LOG_SERVER_EVE4_INST_START +\
                                            REMOTE_LOG_SERVER_EVE4_INST_SIZE)

#define REMOTE_LOG_SERVER_IPU2_INST_START   (REMOTE_LOG_SERVER_EVE4_INST_END)
#ifdef IPU_PRIMARY_CORE_IPU1
#define REMOTE_LOG_SERVER_IPU2_INST_SIZE    (10*1024U)
#else
#define REMOTE_LOG_SERVER_IPU2_INST_SIZE    (58*1024U)
#endif
#define REMOTE_LOG_SERVER_IPU2_INST_END     (REMOTE_LOG_SERVER_IPU2_INST_START +\
                                            REMOTE_LOG_SERVER_IPU2_INST_SIZE)

/** \brief Guard macro */
#if (REMOTE_LOG_SERVER_IPU2_INST_END > REMOTE_LOG_LOG_BUF_SIZE)
    #error "Increase REMOTE_LOG_LOG_BUF_SIZE in file osa_remote_log_if.h"
#endif


/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure for remote log object (local).
 *
 *          This structure is used by a remote core to store information about
 *          log buffer.
 *
 *******************************************************************************
 */
typedef struct
{
    unsigned int coreId;
    /**< Used to identify core */
    char printBuf[REMOTE_LOG_SERVER_PRINT_BUF_LEN];
    /**< local buffer which can hold one line of log */
    OSA_MutexHndl lock;
    /**< Lock used to protect prints from multiple threads */
} RemoteLog_ServerObj;

/**
 *******************************************************************************
 *
 *  \brief  Pointer to base of remote log object structure
 *
 *******************************************************************************
 */
RemoteLog_CoreObj *gRemoteLog_coreObj;

/**
 *******************************************************************************
 *
 *  \brief  Structure containing start pointer and size for log memory
 *
 *******************************************************************************
 */
RemoteLog_ServerIndexInfo gRemoteLog_ServerIdxInfo[SYSTEM_PROC_MAX] =
{
    {REMOTE_LOG_SERVER_IPU1_0_INST_START, REMOTE_LOG_SERVER_IPU1_0_INST_SIZE},
    {REMOTE_LOG_SERVER_IPU1_1_INST_START, REMOTE_LOG_SERVER_IPU1_1_INST_SIZE},
    {REMOTE_LOG_SERVER_A15_0_INST_START, REMOTE_LOG_SERVER_A15_0_INST_SIZE},
    {REMOTE_LOG_SERVER_DSP1_INST_START, REMOTE_LOG_SERVER_DSP1_INST_SIZE},
    {REMOTE_LOG_SERVER_DSP2_INST_START, REMOTE_LOG_SERVER_DSP2_INST_SIZE},
    {REMOTE_LOG_SERVER_EVE1_INST_START, REMOTE_LOG_SERVER_EVE1_INST_SIZE},
    {REMOTE_LOG_SERVER_EVE2_INST_START, REMOTE_LOG_SERVER_EVE2_INST_SIZE},
    {REMOTE_LOG_SERVER_EVE3_INST_START, REMOTE_LOG_SERVER_EVE3_INST_SIZE},
    {REMOTE_LOG_SERVER_EVE4_INST_START, REMOTE_LOG_SERVER_EVE4_INST_SIZE},
    {REMOTE_LOG_SERVER_IPU2_INST_START, REMOTE_LOG_SERVER_IPU2_INST_SIZE}
};



/**
 *******************************************************************************
 *
 *  \brief  Global remote log server object
 *
 *
 *******************************************************************************
 */
RemoteLog_ServerObj gRemoteLog_serverObj;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \brief Put a string into shared memory
 *
 * \param  coreId   [IN] Id of the core to log
 * \param  pString  [IN] String to put into shared memory

 * \return  returns 0 on success
 *
 *******************************************************************************
 */
static int RemoteLog_serverPutString(unsigned int coreId, char *pString)
{
    volatile unsigned int maxBytes, numBytes, copyBytes, serverIdx, clientIdx;
    volatile unsigned char *pDst;
    volatile RemoteLog_MemInfo *pMemInfo;
    RemoteLog_ServerIndexInfo *pIdxInfo;
    RemoteLog_CoreObj *pCoreObj;

    if (coreId >= SYSTEM_PROC_MAX)
        return -1;

    pCoreObj = gRemoteLog_coreObj;
    pMemInfo = &gRemoteLog_coreObj->memInfo[coreId];
    pIdxInfo = &gRemoteLog_ServerIdxInfo[coreId];

    if (pMemInfo->headerTag != REMOTE_LOG_HEADER_TAG)
        return -1;

    numBytes = strlen(pString);

    if (numBytes <= 0)
        return -1;

    serverIdx = pMemInfo->serverIdx;
    clientIdx = pMemInfo->clientIdx;

    if (serverIdx < clientIdx)
        maxBytes = clientIdx - serverIdx;
    else
        maxBytes = (pIdxInfo->size - serverIdx) + clientIdx;

    if (numBytes > (maxBytes-1))
        return -1;

    pDst = &pCoreObj->serverLogBuf[pIdxInfo->startIdx];

    for (copyBytes = 0; copyBytes < numBytes; copyBytes++)
    {
        if (serverIdx >= pIdxInfo->size)
            serverIdx = 0;

        pDst[serverIdx] = *pString++;
        serverIdx++;
    }

    if (serverIdx >= pIdxInfo->size)
        serverIdx = 0;

    pDst[serverIdx] = 0;
    serverIdx++;

    pMemInfo->serverIdx = serverIdx;

    /* dummy read to resure data is written to memory */
    serverIdx = pMemInfo->serverIdx;

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Put variable arguments into shared memory
 *        Provides a C style printf which puts variable arguments as a string
 *        into a shared memory
 *
 * \param  format   [IN] variable argument list
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
int Vps_printf(const char *format, ...)
{
    int retVal;
    va_list vaArgPtr;
    char *buf = NULL;
    UInt32 strnlen = 0;
    UInt64 timeInUsec;

    OSA_mutexLock(&gRemoteLog_serverObj.lock);

    buf = &gRemoteLog_serverObj.printBuf[0];

    timeInUsec = (UInt32)OSA_getCurGlobalTimeInUsec();
    strnlen = snprintf(buf, REMOTE_LOG_SERVER_PRINT_BUF_LEN, "%6d.%06u s: ",
                (unsigned int)timeInUsec/1000000,
                (unsigned int)timeInUsec%1000000
              );

    va_start(vaArgPtr, format);
    vsnprintf(buf + strnlen,
              REMOTE_LOG_SERVER_PRINT_BUF_LEN,
              format, vaArgPtr);
    va_end(vaArgPtr);

    retVal = RemoteLog_serverPutString(gRemoteLog_serverObj.coreId, buf);

    OSA_mutexUnlock(&gRemoteLog_serverObj.lock);

    return (retVal);
}

/**
 *******************************************************************************
 *
 * \brief This function is used for initiating remote log
 *
 * \param  coreId   [IN] Id of the core to log
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
int RemoteLog_init(void)
{
    volatile RemoteLog_MemInfo *pMemInfo;
    UInt32 coreId = System_getSelfProcId();
    Int32 status;

    if (coreId >= SYSTEM_PROC_MAX)
        return -1;

    gRemoteLog_coreObj = (RemoteLog_CoreObj*)
                        OSA_memPhys2Virt(
                            REMOTE_LOG_MEM_ADDR,
                            OSA_MEM_REGION_TYPE_REMOTE_LOG);

    OSA_assert(gRemoteLog_coreObj!=NULL);

    pMemInfo = &gRemoteLog_coreObj->memInfo[coreId];
    pMemInfo->headerTag = REMOTE_LOG_HEADER_TAG;
    pMemInfo->serverIdx = 0;
    pMemInfo->clientIdx = 0;
    pMemInfo->appInitState = CORE_APP_INITSTATUS_INIT_DONE;
    gRemoteLog_serverObj.coreId = coreId;

    status = OSA_mutexCreate(&gRemoteLog_serverObj.lock);
    OSA_assertSuccess(status);

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Set the application initialization state of the
 *        specified core
 *
 * \param coreId    [IN] Core ID of the core to send the char
 * \param state     [IN] Value of the application intialization state to set
 *
 * \return returns 0 on success
 *
 *******************************************************************************
 */
int RemoteLog_setAppInitState(int coreId, unsigned int state)
{
    if (coreId >= SYSTEM_PROC_MAX)
        return -1;

    gRemoteLog_coreObj->memInfo[coreId].appInitState = state;

    return 0;
}

/**
 *******************************************************************************
 *
 * \brief Return the application initialization state of the
 *        specified core
 *
 * \param pState    [OUT] Application initialization state
 * \param coreId    [IN]  Id of the core
 *
 * \return returns 0 on success
 *
 *******************************************************************************
 */
int RemoteLog_getAppInitState(int coreId, unsigned int *pState)
{
    if (coreId >= SYSTEM_PROC_MAX)
        return -1;

    *pState = gRemoteLog_coreObj->memInfo[coreId].appInitState;

    return 0;
}


/**
 *******************************************************************************
 *
 * \brief Return Index information for the given core
 *
 * \param coreId    [IN]  Id of the core
 *
 * \return returns 0 on success
 *
 *******************************************************************************
 */
RemoteLog_ServerIndexInfo *RemoteLog_getCoreIdxInfo(int coreId)
{
    RemoteLog_ServerIndexInfo *pIdxInfo = NULL;

    if (coreId < SYSTEM_PROC_MAX)
    {
        pIdxInfo = &gRemoteLog_ServerIdxInfo[coreId];
    }

    return pIdxInfo;
}


