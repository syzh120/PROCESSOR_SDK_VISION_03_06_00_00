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
  *  \ingroup UTILS_API
  *  \defgroup UTILS_PRF_API Profiling API
  *
  *   Utils_prfTsXxxx - APIs to measure and print elasped time
  *                     @ 64-bit precision
  *
  *   Utils_prfLoadXxxx - APIs to measure and print CPU load at task,
  *                       HWI, SWI, global level
  *  @{
  *
  ******************************************************************************
  */

#ifndef UTILS_PRF_H_
#define UTILS_PRF_H_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Maximum number of Utils perf handles allowed
 *
 *******************************************************************************
*/
#define UTILS_PRF_MAX_HNDL     (64)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure containing load information.
 *
 *          This structure is used to store load of various components of BIOS
 *
 *******************************************************************************
*/
typedef struct
{
    int32_t cpuLoad;
    /**< cpu load */
    int32_t hwiLoad;
    /**< hardware interrupt load */
    int32_t swiLoad;
    /**< software interrupt load */
    int32_t tskLoad;
    /**< task load */
} Utils_PrfLoad;

/**
 *******************************************************************************
 *
 * \brief Typedef for the loadupdate function for the user
 *
 *******************************************************************************
 */
typedef Void(*Utils_loadUpdate) (Utils_PrfLoad *pPrfLoad);

/**
 *******************************************************************************
 *
 *  \brief  Structure containing latency information for a task.
 *
 *******************************************************************************
 */
typedef struct
{
    uint32_t maxLatencyHi;
    /**< Upper 32 bits of Maximum latency for this link */
    uint32_t maxLatencyLo;
    /**< Lower 32 bits of Maximum latency for this link */
    uint32_t minLatencyHi;
    /**< Upper 32 bits of Minimum latency for this link */
    uint32_t minLatencyLo;
    /**< Lower 32 bits of Minimum latency for this link */
    uint32_t accumulatedLatencyHi;
    /**< Upper 32 bis of Accumulated latency added for every frame */
    uint32_t accumulatedLatencyLo;
    /**< Lower 32 bis of Accumulated latency added for every frame */
    uint32_t countHi;
    /**< Upper 32 bits of Number of times latency update is called */
    uint32_t countLo;
    /**< Lower 32 bits of Number of times latency update is called */
} Utils_LatencyStats;

/**
 *******************************************************************************
 *
 * \brief Common statistics maintained across all links for a given channel
 *
 *******************************************************************************
 */
typedef struct {

    uint32_t inBufRecvCount;
    /**< Number of input buffers received */

    uint32_t inBufDropCount;
    /**< Number of input buffers dropped by link auto-matically due to
     *   internal processing constraints
     */

    uint32_t inBufUserDropCount;
    /**< Number of input buffers dropped by link due to user specified
     *   parameter
     */

    uint32_t inBufProcessCount;
    /**< Number of input buffers actually processed by the link */

    uint32_t numOut;
    /**< Number of outputs from this channel */

    uint32_t outBufCount[SYSTEM_MAX_OUT_QUE];
    /**< Number of buffers output for this channel */

    uint32_t outBufDropCount[SYSTEM_MAX_OUT_QUE];
    /**< Number of output buffers dropped by link auto-matically due to
     *   internal processing constraints
     */

    uint32_t outBufUserDropCount[SYSTEM_MAX_OUT_QUE];
    /**< Number of output buffers dropped by link due to user specified
     *   parameter
     */

} Utils_LinkChStatistics;

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

    uint32_t numCh;
    /**< number of channels in the link */

    Utils_LinkChStatistics chStats[SYSTEM_MAX_CH_PER_OUT_QUE];
    /**< Channel specific statistics */

    uint32_t inBufErrorCount;
    /**< Invalid buffers received at input */

    uint32_t outBufErrorCount;
    /**< Invalid buffers received at output */

    uint32_t statsStartTime;
    /**< Time at which stats were started */

    uint32_t newDataCmdCount;
    /**< Number of times 'NEW_DATA' command was received */

    uint32_t releaseDataCmdCount;
    /**< Number of times 'RELEASE_DATA' command was received */

    uint32_t getFullBufCount;
    /**< Number of times 'getFullBuf' callback was called by next link */

    uint32_t putEmptyBufCount;
    /**< Number of times 'putEmptyBuf' callback was called by next link */

    uint32_t notifyEventCount;
    /**< Number of times 'notify' callback was called by a link
     *   Notify could mean display ISR for display link
     *   Capture ISR for capture link
     *   IPC Notify ISR for IPC link
     */

} Utils_LinkStatistics;

typedef struct {

    struct TotalLoad{

        uint32_t integerValue;
        uint32_t fractionalValue;

    } totalLoadParams;

} Utils_SystemLoadStats;


int32_t Utils_prfInit(void);
int32_t Utils_prfDeInit(void);

uint64_t Utils_prfTsGet64(void);

Void   Utils_prfLoadUpdate(void);
int32_t  Utils_prfLoadRegister(BspOsal_TaskHandle pTsk, char *name);
int32_t  Utils_prfLoadUnRegister(BspOsal_TaskHandle pTsk);
int32_t  Utils_prfLoadPrintAll(Bool printTskLoad);
int32_t  Utils_prfGetLoad(Utils_SystemLoadStats * pStats);
Void   Utils_prfLoadCalcStart(void);
Void   Utils_prfLoadCalcStop(void);
Void   Utils_prfLoadCalcReset(void);


Void Utils_resetLatency(Utils_LatencyStats *lStats);
Void Utils_updateLatency(Utils_LatencyStats *lStats,
                         uint64_t linkLocalTime);
Void Utils_printLatency(char *name,
                        Utils_LatencyStats *localLinkstats,
                        Utils_LatencyStats *srcToLinkstats,
                        Bool resetStats
                        );

Void Utils_resetLinkStatistics(Utils_LinkStatistics *pPrm,
                                uint32_t numCh,
                                uint32_t numOut);
Void Utils_printLinkStatistics(Utils_LinkStatistics *pPrm, char *name,
                                Bool resetStats);

uint32_t Utils_calcFps(uint32_t count, uint32_t divValue);

#if defined (BUILD_ARP32)
Void Utils_prfUpdateEveLoadPreAutoCg(UInt64 totalTime);
Void Utils_prfUpdateEveLoadPostAutoCg(UInt64 totalTimeIdle);
#endif


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
