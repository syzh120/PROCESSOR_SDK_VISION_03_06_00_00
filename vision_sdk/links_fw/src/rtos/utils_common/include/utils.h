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
 *
 * \defgroup UTILS_API Utility functions
 *
 * \brief This module define APIs for commonly used utility functions
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils.h
 *
 * \brief Utility functions
 *
 * \version 0.0 (July 2013) : [KC] First version
 *
 *******************************************************************************
 */

#ifndef UTILS_H_
#define UTILS_H_

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <include/link_api/system.h>

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <xdc/std.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Types.h>
#include <xdc/runtime/Timestamp.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/IHeap.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Text.h>

#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/heaps/HeapMem.h>
#include <ti/sysbios/utils/Load.h>
#include <ti/sysbios/hal/Cache.h>
#include <ti/sysbios/knl/Clock.h>
#include <ti/drv/vps/include/vps.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_remote_log_if.h>

#include <include/link_api/system_inter_link_api.h>
#include <include/link_api/systemLink_common.h>



/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Get number of elements in a array
 *
 * \param array [IN] array  data type
 *
 * \return number of elements in the array
 *
 *******************************************************************************
 */
/* MISRA.DEFINE.FUNC
 * MISRAC_2004_Rule_19.7
 * Simple calculation done using macro for performance reasons
 */
#define UTILS_ARRAYSIZE(array)             ((sizeof(array)/sizeof((array)[0U])))

/**
 *******************************************************************************
 *
 * \brief Get index of a element in a array
 *
 * \param elem     [IN] pointer to a element in the array
 * \param array    [IN] array data type
 *
 * \return index of the element in the array
 *
 *******************************************************************************
 */
/* MISRA.DEFINE.FUNC
 * MISRAC_2004_Rule_19.7
 * Simple calculation done using macro for performance reasons
 */
#define UTILS_ARRAYINDEX(elem,array)                   ((elem) - &((array)[0U]))

/**
 *******************************************************************************
 *
 * \brief Check if element is a valid entry of the array
 *
 * \param elem     [IN] pointer to a element in the array
 * \param array    [IN] array data type
 *
 * \return TRUE: element lies inside the array \n
 *         FALSE: element lies outside the array
 *
 *******************************************************************************
 */
/* MISRA.DEFINE.FUNC
 * MISRAC_2004_Rule_19.7
 * Simple calculation done using macro for performance reasons
 */
#define UTILS_ARRAYISVALIDENTRY(elem,array) ((UTILS_ARRAYINDEX((elem),(array)) <   \
                                             UTILS_ARRAYSIZE((array)))         \
                                             ? (Bool)TRUE                      \
                                             : (Bool)FALSE)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */


/**
 *******************************************************************************
 *  \brief Clock ID to be used with Utils_getClkHz()
 *******************************************************************************
 */
typedef enum {

    UTILS_CLK_ID_EVE,
    /**< EVE CPU ID */

    UTILS_CLK_ID_DSP,
    /**< DSP CPU ID */

    UTILS_CLK_ID_IPU,
    /**< IPU CPU ID */

    UTILS_CLK_ID_A15,
    /**< A15 CPU ID */

    UTILS_CLK_ID_MAX
    /**< Max clock ID */

} Utils_ClkId;

/*******************************************************************************
 *  Data structure's
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Context information related to skipping of buffer's
 *
 *******************************************************************************
 */
typedef struct {
    Int32 inputFrameRate;
    /**< Incoming buffer frame-rate */

    Int32 outputFrameRate;
    /**< Outgoing buffer frame-rate */

    Int32 firstTime;
    /**< Flag to indicate if buffer skiplogic is being called for first frame */

    Int32 inCnt;
    /**< Current rate of incoming buffers */

    Int32 outCnt;
    /**< Current rate of outgoing buffers */

    Int32 multipleCnt;
    /**< inputFrameRate x outputFrameRate */

} Utils_BufSkipContext;

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */


Int32    xstrtoi(char *hex);

Int32  Utils_setCpuFrequency (UInt32 freq);

UInt32 Utils_getCurTimeInMsec(void);

UInt64 Utils_getCurTimeInUsec(void);

Void   Utils_resetSkipBufContext(Utils_BufSkipContext *skipCtx,
                    UInt32 inputFrameRate, UInt32 outputFrameRate);

Bool   Utils_doSkipBuf(Utils_BufSkipContext *skipCtx );

Int32 Utils_getAppInitState(UInt32 coreId, UInt32 *pState);

Int32 Utils_setAppInitState(UInt32 coreId, UInt32 state);

Int32 Utils_globalTimerInit(void);

Void Utils_getGlobalTimeCounterValue(UInt32 *valueH, UInt32 *valueL);

UInt32 Utils_getClkHz(Utils_ClkId clkId);

Int32 Utils_netGetIpAddrStr(char *ipAddrStr, UInt32 ifIdx);

Bool Utils_netIsNetworkEnabled(void);

void  Utils_ndkGetIpAddrStr(char *ipAddrStr, UInt32 ifIdx);

UInt32 Utils_netGetProcId(void);

void Utils_cioInit(void);

void Utils_cioDeInit(void);

/**
 *******************************************************************************
 *
 * \brief Get number of planes corresponding to a given data format
 *
 * \param dataFormat [IN] data format
 *
 * \return Number of planes, 0 is returned in case dataFormat is unknown
 *
 *******************************************************************************
 */
static inline UInt32 Utils_getNumPlanes(FVID2_DataFormat dataFormat);
/* MISRA.ONEDEFRULE.FUNC
 * MISRAC_2004_Rule_8.5
 * Static inline function in header file for performance reasons
 */
static inline UInt32 Utils_getNumPlanes(FVID2_DataFormat dataFormat)
{
    UInt32 numPlanes = 0;

    switch(dataFormat)
    {
        case FVID2_DF_YUV422I_UYVY:
        case FVID2_DF_YUV422I_YUYV:
        case FVID2_DF_YUV422I_YVYU:
        case FVID2_DF_YUV422I_VYUY:
        case FVID2_DF_YUV444I:
        case FVID2_DF_RGB24_888:
        case FVID2_DF_BGR24_888:
        case FVID2_DF_BGR16_565:
        case FVID2_DF_ARGB32_8888:
        case FVID2_DF_RGBA32_8888:
        case FVID2_DF_ABGR32_8888:
        case FVID2_DF_BGRA32_8888:
        case FVID2_DF_BGRA16_4444:
            numPlanes = 1U;
            break;
        case FVID2_DF_YUV422SP_UV:
        case FVID2_DF_YUV422SP_VU:
        case FVID2_DF_YUV420SP_UV:
        case FVID2_DF_YUV420SP_VU:
            numPlanes = 2U;
            break;
        case FVID2_DF_YUV422P:
        case FVID2_DF_YUV420P:
        case FVID2_DF_YUV444P:
            numPlanes = 3U;
            break;
        default:
            Vps_printf(" UTILS: WARNING: Unknown data format [%d]."
                       " Setting numPlanes to zero!!!\n",
                       dataFormat);
            numPlanes = 0U;
            break;
    }
    return numPlanes;
}

#endif /* ifndef UTILS_H_ */

/* @} */
