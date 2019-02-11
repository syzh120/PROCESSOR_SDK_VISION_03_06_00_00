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
 * \file utils_remote_log_server.c
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
#include <src/rtos/utils_common/include/utils.h>
#include <src/rtos/utils_common/include/utils_uart.h>
#include <include/link_api/system_common.h>

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
#define REMOTE_LOG_SERVER_PRINT_BUF_LEN     (1024U*4U)

#define REMOTE_LOG_SERVER_IPU1_0_INST_START (0U)
#ifdef IPU_PRIMARY_CORE_IPU1
#define REMOTE_LOG_SERVER_IPU1_0_INST_SIZE  (58U*1024U)
#else
#define REMOTE_LOG_SERVER_IPU1_0_INST_SIZE  (10U*1024U)
#endif
#define REMOTE_LOG_SERVER_IPU1_0_INST_END   (REMOTE_LOG_SERVER_IPU1_0_INST_START +\
                                            REMOTE_LOG_SERVER_IPU1_0_INST_SIZE)

#define REMOTE_LOG_SERVER_IPU1_1_INST_START (REMOTE_LOG_SERVER_IPU1_0_INST_END)
#define REMOTE_LOG_SERVER_IPU1_1_INST_SIZE  (10U*1024U)
#define REMOTE_LOG_SERVER_IPU1_1_INST_END   (REMOTE_LOG_SERVER_IPU1_1_INST_START +\
                                            REMOTE_LOG_SERVER_IPU1_1_INST_SIZE)

#define REMOTE_LOG_SERVER_A15_0_INST_START  (REMOTE_LOG_SERVER_IPU1_1_INST_END)
#define REMOTE_LOG_SERVER_A15_0_INST_SIZE   (20U*1024U)
#define REMOTE_LOG_SERVER_A15_0_INST_END    (REMOTE_LOG_SERVER_A15_0_INST_START +\
                                            REMOTE_LOG_SERVER_A15_0_INST_SIZE)

#define REMOTE_LOG_SERVER_DSP1_INST_START   (REMOTE_LOG_SERVER_A15_0_INST_END)
#define REMOTE_LOG_SERVER_DSP1_INST_SIZE    (10U*1024U)
#define REMOTE_LOG_SERVER_DSP1_INST_END     (REMOTE_LOG_SERVER_DSP1_INST_START +\
                                            REMOTE_LOG_SERVER_DSP1_INST_SIZE)

#define REMOTE_LOG_SERVER_DSP2_INST_START   (REMOTE_LOG_SERVER_DSP1_INST_END)
#define REMOTE_LOG_SERVER_DSP2_INST_SIZE    (10U*1024U)
#define REMOTE_LOG_SERVER_DSP2_INST_END     (REMOTE_LOG_SERVER_DSP2_INST_START +\
                                            REMOTE_LOG_SERVER_DSP2_INST_SIZE)

#define REMOTE_LOG_SERVER_EVE1_INST_START   (REMOTE_LOG_SERVER_DSP2_INST_END)
#define REMOTE_LOG_SERVER_EVE1_INST_SIZE    (10U*1024U)
#define REMOTE_LOG_SERVER_EVE1_INST_END     (REMOTE_LOG_SERVER_EVE1_INST_START +\
                                            REMOTE_LOG_SERVER_EVE1_INST_SIZE)

#define REMOTE_LOG_SERVER_EVE2_INST_START   (REMOTE_LOG_SERVER_EVE1_INST_END)
#define REMOTE_LOG_SERVER_EVE2_INST_SIZE    (10U*1024U)
#define REMOTE_LOG_SERVER_EVE2_INST_END     (REMOTE_LOG_SERVER_EVE2_INST_START +\
                                            REMOTE_LOG_SERVER_EVE2_INST_SIZE)

#define REMOTE_LOG_SERVER_EVE3_INST_START   (REMOTE_LOG_SERVER_EVE2_INST_END)
#define REMOTE_LOG_SERVER_EVE3_INST_SIZE    (10U*1024U)
#define REMOTE_LOG_SERVER_EVE3_INST_END     (REMOTE_LOG_SERVER_EVE3_INST_START +\
                                            REMOTE_LOG_SERVER_EVE3_INST_SIZE)

#define REMOTE_LOG_SERVER_EVE4_INST_START   (REMOTE_LOG_SERVER_EVE3_INST_END)
#define REMOTE_LOG_SERVER_EVE4_INST_SIZE    (10U*1024U)
#define REMOTE_LOG_SERVER_EVE4_INST_END     (REMOTE_LOG_SERVER_EVE4_INST_START +\
                                            REMOTE_LOG_SERVER_EVE4_INST_SIZE)

#define REMOTE_LOG_SERVER_IPU2_INST_START   (REMOTE_LOG_SERVER_EVE4_INST_END)
#ifdef IPU_PRIMARY_CORE_IPU1
#define REMOTE_LOG_SERVER_IPU2_INST_SIZE    (10U*1024U)
#else
#define REMOTE_LOG_SERVER_IPU2_INST_SIZE    (58U*1024U)
#endif
#define REMOTE_LOG_SERVER_IPU2_INST_END     (REMOTE_LOG_SERVER_IPU2_INST_START +\
                                            REMOTE_LOG_SERVER_IPU2_INST_SIZE)

/** \brief Guard macro */
#if (REMOTE_LOG_SERVER_IPU2_INST_END > REMOTE_LOG_LOG_BUF_SIZE)
    #error "Increase REMOTE_LOG_LOG_BUF_SIZE in file utils_remote_log_if.h"
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
    UInt32 coreId;
    /**< Used to identify core */
    char printBuf[REMOTE_LOG_SERVER_PRINT_BUF_LEN];
    /**< local buffer which can hold one line of log */
} RemoteLog_ServerObj;

/**
 *******************************************************************************
 *
 *  \brief  Global array for remote log object structure, one for each core.
 *
 *
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
#ifndef BUILD_A15
#pragma DATA_SECTION(gRemoteLog_coreObj,".bss:extMemNonCache:remoteLogCoreShm");
#pragma DATA_ALIGN(gRemoteLog_coreObj, 4);
#endif
RemoteLog_CoreObj gRemoteLog_coreObj
#ifdef BUILD_A15
__attribute__ ((section(".bss:extMemNonCache:remoteLogCoreShm")))
__attribute__ ((aligned(4)))
#endif
;



/**
 *******************************************************************************
 *
 *  \brief  Global remote log server object
 *
 *
 *******************************************************************************
 */
RemoteLog_ServerObj gRemoteLog_serverObj;

RemoteLog_ServerIndexInfo gRemoteLog_ServerIdxInfo[SYSTEM_PROC_MAX] =
{
    {REMOTE_LOG_SERVER_IPU1_0_INST_START, REMOTE_LOG_SERVER_IPU1_0_INST_SIZE - 1U},
    {REMOTE_LOG_SERVER_IPU1_1_INST_START, REMOTE_LOG_SERVER_IPU1_1_INST_SIZE - 1U},
    {REMOTE_LOG_SERVER_A15_0_INST_START, REMOTE_LOG_SERVER_A15_0_INST_SIZE - 1U},
    {REMOTE_LOG_SERVER_DSP1_INST_START, REMOTE_LOG_SERVER_DSP1_INST_SIZE - 1U},
    {REMOTE_LOG_SERVER_DSP2_INST_START, REMOTE_LOG_SERVER_DSP2_INST_SIZE - 1U},
    {REMOTE_LOG_SERVER_EVE1_INST_START, REMOTE_LOG_SERVER_EVE1_INST_SIZE - 1U},
    {REMOTE_LOG_SERVER_EVE2_INST_START, REMOTE_LOG_SERVER_EVE2_INST_SIZE - 1U},
    {REMOTE_LOG_SERVER_EVE3_INST_START, REMOTE_LOG_SERVER_EVE3_INST_SIZE - 1U},
    {REMOTE_LOG_SERVER_EVE4_INST_START, REMOTE_LOG_SERVER_EVE4_INST_SIZE - 1U},
    {REMOTE_LOG_SERVER_IPU2_INST_START, REMOTE_LOG_SERVER_IPU2_INST_SIZE - 1U}
};

/* ========================================================================== */
/*                          Local Function Prototypes                         */
/* ========================================================================== */
static Int32 RemoteLog_serverPutString(UInt32 coreId, const char pString[]);


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
static Int32 RemoteLog_serverPutString(UInt32 coreId, const char pString[])
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    volatile UInt32 maxBytes, numBytes, copyBytes;
    volatile UInt32 serverIdx, clientIdx, idx = 0U;
    volatile UInt8 *pDst;
    RemoteLog_ServerIndexInfo *pIdxInfo;
    RemoteLog_CoreObj *pCoreObj;

    if (coreId >= SYSTEM_PROC_MAX)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }
    else
    {
        pCoreObj = &gRemoteLog_coreObj;
        pIdxInfo = &gRemoteLog_ServerIdxInfo[coreId];

        if (pCoreObj->memInfo[coreId].headerTag != REMOTE_LOG_HEADER_TAG)
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    if (0 == status)
    {
        numBytes = strlen(pString);

        if (numBytes <= 0)
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    if (0 == status)
    {
        serverIdx = pCoreObj->memInfo[coreId].serverIdx;
        clientIdx = pCoreObj->memInfo[coreId].clientIdx;

        if (serverIdx < clientIdx)
        {
            maxBytes = clientIdx - serverIdx;
        }
        else
        {
            maxBytes = (pIdxInfo->size - serverIdx) + clientIdx;
        }

        if (numBytes > (maxBytes-1U))
        {
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    if (0 == status)
    {
        pDst = &pCoreObj->serverLogBuf[pIdxInfo->startIdx];
        for (copyBytes = 0; copyBytes < numBytes; copyBytes++)
        {
            if (serverIdx >= pIdxInfo->size)
            {
                serverIdx = 0;
            }
            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * Pointer is used in arithmetic or array index expression.
             * KW State: Ignore -> Waiver -> Case by case
             * MISRAC_WAIVER:
             * Pointer is accessed as an array
             * Check is added to make sure that
             * pointer is never accessed beyond size of the array.
             */
            pDst[serverIdx] = (UInt8)pString[idx];
            serverIdx ++;
            idx ++;
        }

        if (serverIdx >= pIdxInfo->size)
        {
            serverIdx = 0U;
        }

        /* MISRA.PTR.ARITH
         * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
         * Pointer is used in arithmetic or array index expression.
         * KW State: Ignore -> Waiver -> Case by case
         * MISRAC_WAIVER:
         * Pointer is accessed as an array
         * Check is added to make sure that
         * pointer is never accessed beyond size of the array.
         */
        pDst[serverIdx] = 0U;
        serverIdx ++ ;

        if (serverIdx >= pIdxInfo->size)
        {
            serverIdx = 0U;
        }

        pCoreObj->memInfo[coreId].serverIdx = serverIdx;

        /* dummy read to resure data is written to memory */
        serverIdx = pCoreObj->memInfo[coreId].serverIdx;
    }

    return (status);
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
/* MISRA.FUNC.VARARG
 * MISRAC_2004_Rule_16.1
 * MISRAC_WAIVER: Can be included for Debug, Utility, Trace Functions
 */
Int32 Vps_printf(const char *format, ...)
{
    Int32 retVal = SYSTEM_LINK_STATUS_EFAIL;
    va_list vaArgPtr;
    char *buf = NULL;
    UInt32 cookie;
    UInt32 nStrnLen = 0;
    UInt64 timeInUsec;


    cookie = Hwi_disable();

    buf = &gRemoteLog_serverObj.printBuf[0U];

    timeInUsec = Utils_getCurGlobalTimeInUsec();
    nStrnLen = (UInt32)snprintf(buf, REMOTE_LOG_SERVER_PRINT_BUF_LEN,
                "%6d.%06u s: ",
                (UInt32)(timeInUsec/1000000U),
                (UInt32)(timeInUsec%1000000U));

    /* if nStrnLen is equal to REMOTE_LOG_SERVER_PRINT_BUF_LEN,
       don't write string. */
    if (nStrnLen < REMOTE_LOG_SERVER_PRINT_BUF_LEN)
    {
        va_start(vaArgPtr, format);
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 and MISRAC_2004_Rule_17.4
         * Pointer is used in arithmatic or array index expression
         * KW State: Ignore -> Waiver -> Case by case
         * MISRAC_WAIVER: buf is pointing to printBuf array of size
         * REMOTE_LOG_SERVER_PRINT_BUF_LEN and it is passed to vsnprint api,
         * which makes sure that the buf is never accessed beyond
         * its REMOTE_LOG_SERVER_PRINT_BUF_LEN size
         */
        vsnprintf((char *)(buf + nStrnLen),
                  REMOTE_LOG_SERVER_PRINT_BUF_LEN,
                  format, vaArgPtr);
        va_end(vaArgPtr);

        retVal = RemoteLog_serverPutString(gRemoteLog_serverObj.coreId, buf);

        Hwi_restore(cookie);
    }

    if (BIOS_getThreadType() == BIOS_ThreadType_Task)
    {
        /* Printf should be called only from Task context as it does pend.
         * Calling from other context will cause exception
         */
#ifdef ENABLE_CCS_LOG
        System_printf(buf);
#endif
    }

    return (retVal);
}

/**
 *******************************************************************************
 *
 * \brief Put variable arguments into shared memory
 *        Provides a C style printf which puts variable arguments as a string
 *        into a shared memory
 *
 * \param  format   [IN] variable argument list
 * \param  vaArgPtr [IN] object representing the variable arguments list
 *
 * \return  returns 0 on success
 *
 *******************************************************************************
 */
/* MISRA.FUNC.VARARG
 * MISRAC_2004_Rule_16.1
 * MISRAC_WAIVER: Can be included for Debug, Utility, Trace Functions
 */
Int32 Vps_vprintf(const char *format, va_list vaArgPtr)
{
    Int32 retVal = SYSTEM_LINK_STATUS_EFAIL;
    char *buf = NULL;
    UInt32 cookie;
    UInt32 nStrnLen = 0;
    UInt64 timeInUsec;


    cookie = Hwi_disable();

    buf = &gRemoteLog_serverObj.printBuf[0U];

    timeInUsec = Utils_getCurGlobalTimeInUsec();
    nStrnLen = (UInt32)snprintf(buf, REMOTE_LOG_SERVER_PRINT_BUF_LEN,
                "%6d.%06u s: ",
                (UInt32)(timeInUsec/1000000U),
                (UInt32)(timeInUsec%1000000U));

    /* if nStrnLen is equal to REMOTE_LOG_SERVER_PRINT_BUF_LEN,
       don't write string. */
    if (nStrnLen < REMOTE_LOG_SERVER_PRINT_BUF_LEN)
    {
        /* MISRA.PTR.ARITH
         * MISRAC_2004_Rule_17.1 and MISRAC_2004_Rule_17.4
         * Pointer is used in arithmatic or array index expression
         * KW State: Ignore -> Waiver -> Case by case
         * MISRAC_WAIVER: buf is pointing to printBuf array of size
         * REMOTE_LOG_SERVER_PRINT_BUF_LEN and it is passed to vsnprint api,
         * which makes sure that the buf is never accessed beyond
         * its REMOTE_LOG_SERVER_PRINT_BUF_LEN size
         */
        vsnprintf((char *)(buf + nStrnLen),
                  REMOTE_LOG_SERVER_PRINT_BUF_LEN,
                  format, vaArgPtr);

        retVal = RemoteLog_serverPutString(gRemoteLog_serverObj.coreId, buf);

        Hwi_restore(cookie);
    }

    if (BIOS_getThreadType() == BIOS_ThreadType_Task)
    {
        /* Printf should be called only from Task context as it does pend.
         * Calling from other context will cause exception
         */
#ifdef ENABLE_CCS_LOG
        System_printf(buf);
#endif
    }

    return (retVal);
}


Int32 RemoteLog_init(void)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    volatile RemoteLog_CoreObj *pCoreObj;
    UInt32 coreId = System_getSelfProcId();

    if (coreId < (UInt32)SYSTEM_PROC_MAX)
    {
        pCoreObj = &gRemoteLog_coreObj;
        pCoreObj->memInfo[coreId].headerTag = REMOTE_LOG_HEADER_TAG;
        pCoreObj->memInfo[coreId].serverIdx = 0;
        pCoreObj->memInfo[coreId].clientIdx = 0;

        gRemoteLog_serverObj.coreId = coreId;
        status = SYSTEM_LINK_STATUS_SOK;
    }
#ifdef ENABLE_NETWORK_LOG
#ifdef BUILD_M4_0
    #ifdef NDK_PROC_TO_USE_IPU1_0
    Void NetworkCons_shmCreate();
    NetworkCons_shmCreate();
    #endif
#endif
#ifdef BUILD_M4_1
    #ifdef NDK_PROC_TO_USE_IPU1_1
    Void NetworkCons_shmCreate();
    NetworkCons_shmCreate();
    #endif
#endif
#ifdef BUILD_M4_2
    #ifdef NDK_PROC_TO_USE_IPU2
    Void NetworkCons_shmCreate();
    NetworkCons_shmCreate();
    #endif
#endif
#ifdef BUILD_A15
    #ifdef NDK_PROC_TO_USE_A15_0
    Void NetworkCons_shmCreate();
    NetworkCons_shmCreate();
    #endif
#endif
#endif
    return (status);
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
Int32 RemoteLog_setAppInitState(UInt32 coreId, UInt32 state)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    volatile RemoteLog_CoreObj *pCoreObj;

    if (coreId < SYSTEM_PROC_MAX)
    {
        pCoreObj = &gRemoteLog_coreObj;
        pCoreObj->memInfo[coreId].appInitState = state;
        status = SYSTEM_LINK_STATUS_SOK;
    }

    return (status);
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
Int32 RemoteLog_getAppInitState(UInt32 coreId, UInt32 *pState)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    volatile RemoteLog_CoreObj *pCoreObj;

    if (coreId < SYSTEM_PROC_MAX)
    {
        pCoreObj = &gRemoteLog_coreObj;
        *pState = pCoreObj->memInfo[coreId].appInitState;
        status = SYSTEM_LINK_STATUS_SOK;
    }

    return (status);
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
RemoteLog_ServerIndexInfo *RemoteLog_getCoreIdxInfo(UInt32 coreId)
{
    RemoteLog_ServerIndexInfo *pIdxInfo = NULL;

    if (coreId < SYSTEM_PROC_MAX)
    {
        pIdxInfo = &gRemoteLog_ServerIdxInfo[coreId];
    }

    return pIdxInfo;
}

