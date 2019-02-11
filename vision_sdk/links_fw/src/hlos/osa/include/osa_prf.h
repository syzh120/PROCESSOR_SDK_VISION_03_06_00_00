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
  ******************************************************************************
  *
  *  \ingroup OSA_API
  *  \defgroup OSA_PRF_API Profiling API
  *
  *   OSA_prfTsXxxx - APIs to measure and print elasped time
  *                     @ 64-bit precision
  *
  *   OSA_prfLoadXxxx - APIs to measure and print CPU load at task,
  *                       HWI, SWI, global level
  *  @{
  *
  ******************************************************************************
  */

#ifndef _OSA_PRF_H_
#define _OSA_PRF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */


#include <osa.h>
#include <osa_types.h>

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure containing latency information for a task.
 *
 *******************************************************************************
 */
typedef struct
{
    UInt64 maxLatency;
    /**< Maximum latency for this link */
    UInt64 minLatency;
    /**< Minimum latency for this link */
    UInt64 accumulatedLatency;
    /**< Accumulated latency added for every frame */
    UInt64 count;
    /**< Number of times latency update is called */
} OSA_LatencyStats;

/**
 *******************************************************************************
 *
 * \brief Common statistics maintained across all links for a given channel
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 inBufRecvCount;
    /**< Number of input buffers received */

    UInt32 inBufDropCount;
    /**< Number of input buffers dropped by link auto-matically due to
     *   internal processing constraints
     */

    UInt32 inBufUserDropCount;
    /**< Number of input buffers dropped by link due to user specified
     *   parameter
     */

    UInt32 inBufProcessCount;
    /**< Number of input buffers actually processed by the link */

    UInt32 numOut;
    /**< Number of outputs from this channel */

    UInt32 outBufCount[SYSTEM_MAX_OUT_QUE];
    /**< Number of buffers output for this channel */

    UInt32 outBufDropCount[SYSTEM_MAX_OUT_QUE];
    /**< Number of output buffers dropped by link auto-matically due to
     *   internal processing constraints
     */

    UInt32 outBufUserDropCount[SYSTEM_MAX_OUT_QUE];
    /**< Number of output buffers dropped by link due to user specified
     *   parameter
     */

} OSA_LinkChStatistics;

/**
 *******************************************************************************
 *
 * \brief Common statistics maintained across all links
 *
 *        A link implementation is recommended to use maintain these statistics.
 *
 *        Some link may need to maintain additional link specific statistics.
 *        Such link specific statistics can be maintain inside the link itself.
 *
 *        Common Utility APIs to print the stats can be used by a link to print
 *        this information.
 *
 *******************************************************************************
 */
typedef struct {

    UInt32 numCh;
    /**< number of channels in the link */

    OSA_LinkChStatistics chStats[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< Channel specific statistics */

    UInt32 inBufErrorCount;
    /**< Invalid buffers received at input */

    UInt32 outBufErrorCount;
    /**< Invalid buffers received at output */

    UInt32 statsStartTime;
    /**< Time at which stats were started */

    UInt32 newDataCmdCount;
    /**< Number of times 'NEW_DATA' command was received */

    UInt32 releaseDataCmdCount;
    /**< Number of times 'RELEASE_DATA' command was received */

    UInt32 getFullBufCount;
    /**< Number of times 'getFullBuf' callback was called by next link */

    UInt32 putEmptyBufCount;
    /**< Number of times 'putEmptyBuf' callback was called by next link */

    UInt32 notifyEventCount;
    /**< Number of times 'notify' callback was called by a link
     *   Notify could mean display ISR for display link
     *   Capture ISR for capture link
     *   IPC Notify ISR for IPC link
     */

} OSA_LinkStatistics;


Void OSA_resetLatency(OSA_LatencyStats *lStats);
Void OSA_updateLatency(OSA_LatencyStats *lStats,
                         UInt64 linkLocalTime);
Void OSA_printLatency(char *name,
                        OSA_LatencyStats *localLinkstats,
                        OSA_LatencyStats *srcToLinkstats,
                        Bool resetStats
                        );

Void OSA_resetLinkStatistics(OSA_LinkStatistics *pPrm,
                                UInt32 numCh,
                                UInt32 numOut);
Void OSA_printLinkStatistics(OSA_LinkStatistics *pPrm, char *name,
                                Bool resetStats);
UInt32 OSA_calcFps(UInt32 count, UInt32 divValue);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
