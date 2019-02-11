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

#ifndef SYSTEM_TRACE_H_
#define SYSTEM_TRACE_H_


#include <xdc/runtime/System.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 *******************************************************************************
 *
 *  \ingroup SYSTEM_LINK_API
 *  \defgroup SYSTEM_LINK_TRACE_API  System Link Trace, Debug, Utility APIs
 *
 *  Utility APIs for system tracing, debug and other function's
 *
 *  @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \file system_trace.h
 *  \brief  System Link Trace, Debug, Utility APIs
 *
 *******************************************************************************
 */


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief Prints to Shared memory and CCS console
 *
 *  This function prints the provided formatted string to shared memory and CCS
 *  console
 *
 * DES_ID: DOX_DES_TAG(DES_DEBUG_STATS_002)
 * REQ_ID: DOX_REQ_TAG(ADASVISION-1541)
 *
 *  \param format       [IN] Formatted string followed by variable arguments
 *
 *  \return SYSTEM_LINK_STATUS_SOK on success, else appropriate error code on
 *          failure.
 *
 *******************************************************************************
 */
/* MISRA.PTR.ARITH
 * MISRAC_2004_Rule_16.1
 * MISRAC_WAIVER: Can be included for Debug, Utility, Trace Functions
 */
Int32 Vps_printf(const char * format, ... );

Int32 Vps_vprintf(const char * format, va_list vaArgPtr );

#define UTILS_COMPILETIME_ASSERT(condition)                               \
   do {                                                                   \
           typedef char ErrorCheck##__FILE__##__LINE__[((condition) == TRUE) ? 1 : -(Int32)1]; \
      } while(0)

#define UTILS_ISERROR(errCode)                                  ((errCode) < 0)

extern volatile Int32 g_AssertFailLoop;

static inline void UTILS_assertLocal(Bool   condition,
                                     const Char  *str,
                                     const Char  *fileName,
                                     Int32  lineNum);

static inline void UTILS_assertErrorLocal(Bool   condition,
                                          UInt32 statusVar,
                                          UInt32 errorCode,
                                          UInt32 linkID,
                                          UInt32 channelID,
                                          Char  *str,
                                          Char  *fileName,
                                          Int32  lineNum);

/*
 * DES_ID: DOX_DES_TAG(DES_DEBUG_STATS_002)
 * REQ_ID: DOX_REQ_TAG(ADASVISION-1536)
 */
#define UTILS_assert(y)                                     \
    (UTILS_assertLocal((Bool) (y), (const Char *) # y, \
                       (const Char *) __FILE__, (Int32) __LINE__))
#define UTILS_assertError(condition, statusVar, errorCode, linkID, channelID)  \
    (UTILS_assertErrorLocal((Bool) (condition),                                \
                            (UInt32) (statusVar),                              \
                            (UInt32) (errorCode),                              \
                            (UInt32) (linkID),                                 \
                            (UInt32) (channelID),                              \
                            (Char *) #condition,                               \
                            (Char *) __FILE__, (Int32) __LINE__))

static inline void UTILS_assertLocal(Bool   condition,
                                     const Char  *str,
                                     const Char  *fileName,
                                     Int32  lineNum)
{
#ifdef UTILS_ASSERT_ENABLE
    if (condition == FALSE) {
        Vps_printf(" Assertion @ Line: %d in %s: %s : failed !!!\n",
                lineNum, fileName, str);
        System_printf(" Assertion @ Line: %d in %s: %s : failed !!!\n",
                lineNum, fileName, str);
        while(g_AssertFailLoop)
        {
            BspOsal_sleep(1U);
        }
    }
#endif
    return;
}

/*
* MISRA.ONEDEFRULE.FUNC
* MISRAC_2004_Rule_8.5
* Waiver for static inline functions defined in header
* file doing init of interface structure and small
* functions for performance reasons
*/

static inline void UTILS_assertErrorLocal(Bool   condition,
                                          UInt32 statusVar,
                                          UInt32 errorCode,
                                          UInt32 linkID,
                                          UInt32 channelID,
                                          Char  *str,
                                          Char  *fileName,
                                          Int32  lineNum)
{
#ifdef UTILS_ASSERT_ENABLE
    if (condition == FALSE) {
        statusVar = errorCode;
        Vps_printf(" LINK ERR::linkID:%x::channelID:%d::errorCode:%d::FileName:%s::linuNum:%d::errorCondition:%s\n",
                     linkID, channelID, statusVar, fileName, lineNum, str);
    }
#endif
    return;
}

/**
 *******************************************************************************
 *
 *  \brief Get current timestamp in msec
 *
 * DES_ID: DES_DEBUG_STATS_002
 * ARC_ID: ARC_PSDKV_089
 * REQ_ID: ADASVISION-1541
 *
 *  \return timestamp in msec
 *
 *******************************************************************************
 */
UInt64 Utils_getCurGlobalTimeInMsec(void);

/**
 *******************************************************************************
 *
 *  \brief Get current timestamp in usec
 *
 *  \return timestamp in msec
 *
 *******************************************************************************
 */
UInt64 Utils_getCurGlobalTimeInUsec(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif  /* ifndef
         * SYSTEM_TRACE_H_
         */
/* @} */
