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
 * \ingroup UTILS_API
 * \defgroup UTILS_LINK_STATS_IF_API Link Statistics Interface
 *
 * \brief Link statistics layer allows to keep the all the statistics in
 *        a common shared location.
 *
 * @{
 *******************************************************************************
 */

 /**
 *******************************************************************************
 *
 * \file utils_link_stats_if.h
 *
 * \brief  Link Statistics Layer interface file, keeps definitaion of the
 *         data structures accessible by each link.
 *
 *******************************************************************************
 */

#ifndef LINK_STATS_IF_
#define LINK_STATS_IF_

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 *  Includes
 *******************************************************************************
 */
#include <include/link_api/system.h>
#include <src/rtos/utils_common/include/utils_stat_collector.h>
#include <src/rtos/utils_common/include/utils_mem.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Tag used to identify Link Statistics object
 *        Used to check log object is valid or not
 *
 *******************************************************************************
*/
#define LINK_STATS_HEADER_TAG               (0xFFABCDEFU)

/**
 *******************************************************************************
 *
 * \brief Maximum number of Link Stats object supported
 *
 *******************************************************************************
*/
#define LINK_STATS_MAX_STATS_INST            (145U)

/**
 *******************************************************************************
 *
 * \brief Maximum number of Utils perf handles allowed
 *
 *******************************************************************************
*/
#define LINK_STATS_PRF_MAX_TSK               (342U)

/**
 *******************************************************************************
 *
 * \brief Command to Reset the Link Statistics.
 *        When link gets this command, it resets the link statistics
 *        information.
 *
 *******************************************************************************
*/
#define LINK_STATS_CMD_RESET_STATS          (0x1000U)

/**
 *******************************************************************************
 *
 * \brief Command to inform that the Reset is done.
 *        This is sent by the link to the monitor thread that the
 *        reset is completed.
 *
 *******************************************************************************
*/
#define LINK_STATS_CMD_RESET_STATS_DONE     (0x1001U)

/**
 *******************************************************************************
 *
 * \brief Command to copy core load information to the shared memory.
 *        This is sent by the monitor thread to copy the core load
 *        into share memory.
 *
 *******************************************************************************
*/
#define LINK_STATS_CMD_COPY_CORE_LOAD       (0x1002U)

/**
 *******************************************************************************
 *
 * \brief Command to inform that core loading/performance data is copied
 *        into shared memory.
 *
 *******************************************************************************
*/
#define LINK_STATS_CMD_COPY_CORE_LOAD_DONE  (0x1003U)

/*******************************************************************************
 *  Enum's
 *******************************************************************************
 */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure for Link Statistics command object.
 *
 *          This structure is implement a queue of depth 1 between
 *          monitor thread and each link thread. Monitor thread posts
 *          command into this queue and when each link link sees
 *          this command, it performs actions based on the command.
 *          There is one command object between each link and monitor.
 *
 *******************************************************************************
*/
typedef struct
{
  volatile UInt32 cmd;
  /**< variable containing command value*/
  volatile UInt32 rdIdx;
  /**< Command Read Index */
  volatile UInt32 wrIdx;
  /**< Command Write Index */
} System_LinkStatsCmdObj;

/**
 *******************************************************************************
 *
 *  \brief  Structure for storing load information for the core.
 *
 *          This structure stores the complete load information
 *          of the core. It keeps time spent on Hwi, Swi etc.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 totalSwiThreadTimeHi;
    /**< Upper 32bits of Total time spent in swi */
    UInt32 totalSwiThreadTimeLo;
    /**< Lower 32bits of Total time spent in swi */
    UInt32 totalHwiThreadTimeHi;
    /**< Upper 32bits of Total time spent in hwi */
    UInt32 totalHwiThreadTimeLo;
    /**< Lower 32bits of Total time spent in hwi */
    UInt32 totalTimeHi;
    /**< Upper 32bits of Total time spent */
    UInt32 totalTimeLo;
    /**< Lower 32bits of Total time spent */
    UInt32 totalIdlTskTimeHi[2U];
    /**< Upper 32bits of Total time spent in idle task
     * Note:  creating array of 2U for SMP where both cores idle load needs
     *        to be taken separately
     */
    UInt32 totalIdlTskTimeLo[2U];
    /**< Lower 32bits of Total time spent in idle task
     * Note:  creating array of 2U for SMP where both cores idle load needs
     *        to be taken separately
     */
    UInt32 totalLowPowerTimeHi;
    /**< Upper 32bits of the time for which the cpu was in low power */
    UInt32 totalLowPowerTimeLo;
    /**< Lower 32bits of the time for which the cpu was in low power */
} System_LinkStatsAccPrfLoadObj;

/**
 *******************************************************************************
 *
 *  \brief  Structure containing profiling information for a task.
 *
 *******************************************************************************
*/
typedef struct
{
    UInt32 isAlloc;
    /**< Flag to indicate if this instance is allocated or not */
    char name[32];
    /**< name of the task */
    UInt32 totalTskThreadTimeHi;
    /**< Upper 32bits of Total time the task has spent */
    UInt32 totalTskThreadTimeLo;
    /**< Lower 32bits of Total time the task has spent */
} System_LinkStatsPrfLoadObj;



/**
 *******************************************************************************
 *
 *  \brief  Structure for link statistics.
 *
 *          This structure is used by each link on all core for storing link
 *          statistics. Each link gets the pointer to this structure
 *          and updates link statistics
 *******************************************************************************
*/
typedef struct
{
    UInt32             isAlloc;
    /**< Flag to indicate if this instance is allocated or not */

    Int32              linkId;
    /**< Storing link id locally so that each statistics instance
         can be identified. */
    char                 linkName[32];
    /**< String to hold link name */

    Utils_LinkStatistics linkStats;
    /**< links statistics like frames captured/processed, dropped etc
     */
    Utils_LatencyStats   linkLatency;
    /**< Structure to find out min, max and average latency of the link */
    Utils_LatencyStats   srcToLinkLatency;
    /**< Structure to find out min, max and average latency from
     *   source to this link
     */
    UInt32                 underFlowOverFlowStatus;
    /**< UnderFlow/OverFlow Status of the link */
    System_LinkStatsCmdObj srcToLinkCmdObj;
    /**< Link Stats Command Queue, used to send/receive command from
         monitor thread to Link */
    System_LinkStatsCmdObj linkToSrcCmdObj;
    /**< Link Stats Command Queue, used to send/receive command from
         Link to Monitor thread */
} System_LinkStatistics;

typedef struct
{
    System_LinkStatsAccPrfLoadObj  accPrfLoadObj;
    /**< Array of Accumulated performance load objects,
         one for each core,
         Stores core load information like
         time spent on executing interrup or software interrupt etc. */
    Utils_MemHeapStats             heapStats[UTILS_HEAPID_MAXNUMHEAPS];
    /**< System Heap Status */

    UInt32                         maxSemaphoreObjs;
    /**< Maximum statically allocated semaphore objects */

    UInt32                         freeSemaphoreObjs;
    /**< Number of free semaphore objects */

    UInt32                         maxClockObjs;
    /**< Maximum statically allocated Clock objects */

    UInt32                         freeClockObjs;
    /**< Number of free Clock objects */

    UInt32                         maxTaskObjs;
    /**< Maximum statically allocated Task objects */

    UInt32                         freeTaskObjs;
    /**< Number of free Task objects */

    UInt32                         maxHwiObjs;
    /**< Maximum statically allocated Hwi objects */

    UInt32                         freeHwiObjs;
    /**< Number of free Hwi objects */

    System_LinkStatsCmdObj         srcToLinkCmdObj;
    /**< Link Stats Command Queue, used to send/receive command from
         monitor thread to Link */
    System_LinkStatsCmdObj         linkToSrcCmdObj;
    /**< Link Stats Command Queue, used to send/receive command from
         Link to Monitor thread */
} System_LinkStatsCorePrfObj;

/**
 *******************************************************************************
 *
 *  \brief  Structure for link Statistics core Object.
 *
 *          This structure contains link statistics object instaces for all
 *          links on all cores, Currently, it does not contains any additional
 *          information, but it can be used to store any additional/common
 *          statistics information.
 *******************************************************************************
*/
typedef struct
{
    System_LinkStatsPrfLoadObj     prfLoadObj[LINK_STATS_PRF_MAX_TSK];
    /* Performance Task Object,
       Stores task loading information,
       There are #LINK_STATS_PRF_MAX_TSK tasks supported */

    System_LinkStatsCorePrfObj     corePrfObj[SYSTEM_PROC_MAX];
    /**< Core Performance Object
         Contains accumulated performance and each tasks
         performance for each core. */

    System_LinkStatistics          linkStats[LINK_STATS_MAX_STATS_INST];
    /**< Link statistics for all links on all cores */
    UInt32                         syncLost1;
    /**< syncLost1 Error Count for LCD1 Overlay. */
    UInt32                         syncLost2;
    /**< syncLost2 Error Count for LCD2 Overlay.
         Not applicable for Tda3xx platform. */
    UInt32                         syncLost3;
    /**< syncLost3 Error Count for LCD3 Overlay.
         Not applicable for Tda3xx platform. */
    UInt32                         syncLostTV;
    /**< syncLostTV Error Count for TV Overlay.
         Not applicable for Tda3xx platform. */
    UInt32                         dispOcpError;
    /**< Display Ocp Error Count. */
} System_LinkStatsCoreObj;


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Function to allocate link state object.
 *          Collector keeps a pool of link state object for each core.
 *          This API is used to allocates link state instance from this pool.
 *          Each link calls this api at create time to get link state object.
 *
 *  \return Pointer to link state object
 *          NULL in case there is no free instance in the pool
 *
 *******************************************************************************
 */
System_LinkStatistics *Utils_linkStatsCollectorAllocInst(
    UInt32 linkId, const char linkName[]);

/**
 *******************************************************************************
 *
 *  \brief  Function to De-allocate link state object.
 *          Function deallocates the link state object and returns it
 *          to the pool.
 *
 *  \param  linkStats   Pointer to the link state object
 *
 *  \return Pointer to link state object
 *          NULL in case there is no free instance in the pool
 *
 *******************************************************************************
 */
Int32 Utils_linkStatsCollectorDeAllocInst(System_LinkStatistics *linkStats);

/**
 *******************************************************************************
 *
 *  \brief  Function to print link statistics given a link ID
 *
 *******************************************************************************
 */
Void Utils_linkStatsPrintLinkStatistics(UInt32 linkId);

/**
 *******************************************************************************
 *
 *  \brief  Function to print display errors
 *
 *******************************************************************************
 */
Void Utils_linkStatsPrintDisplayErrorStats(void);


/**
 *******************************************************************************
 *
 *  \brief  Function to reset link stats based on received command
 *
 *******************************************************************************
 */
Void  Utils_linkStatsCollectorProcessCmd(System_LinkStatistics *linkStatsInfo);

/**
 *******************************************************************************
 *
 *  \brief  Function to send command.
 *
 *          Function sets command in the queue of the list stat
 *          object of the link. This is usually used by the monitor thread
 *          to send the command to the link.
 *
 *  \param  pCmdObj     Pointer to command Object
 *  \param  cmd         Command id
 *
 *  \return 0       on success
 *         -1       if command cannot be written to queue
 *
 *******************************************************************************
 */
Int32 Utils_linkStatsSendCommand(System_LinkStatsCmdObj *pCmdObj, UInt32 cmd);

/**
 *******************************************************************************
 *
 *  \brief  Function to receive command.
 *
 *          Function gets command in the queue of the list stat
 *          object of the link. This is used by the each link to
 *          get the command and process it accordingly in the link.
 *
 *  \param  pCmdObj     Pointer to command Object
 *  \param  cmd         Command Id
 *
 *  \return 0       on success
 *         -1       if command queue is empty
 *
 *******************************************************************************
 */
Int32 Utils_linkStatsRecvCommand(System_LinkStatsCmdObj *pCmdObj, UInt32 *cmd);

/**
 *******************************************************************************
 *
 *  \brief  Function to get pointer to link stat instance for the
 *          given Link Id and Core Id.
 *
 *  \param  linkId   Id of the Link
 *
 *  \return 0       on success
 *         -1       if command queue is empty
 *
 *******************************************************************************
 */
System_LinkStatistics *Utils_linkStatsGetLinkStatInst(UInt32 linkId);

/**
 *******************************************************************************
 *
 *  \brief  Function to allocate Performance Load Instance on the give core.
 *
 *          It is used by the utils_prf utility when a new task is created.
 *          The performance load instance stores the task load on this core.
 *
 *  \param  coreId   Id of the Core
 *
 *  \return pPrfLoadObj     Pointer to Performance Load Object
 *          NULL            If there are no free performance load instances
 *
 *******************************************************************************
 */
System_LinkStatsCorePrfObj *Utils_linkStatsGetPrfLoadInst(UInt32 coreId);

/**
 *******************************************************************************
 *
 *  \brief  Function returns performance load object for the task and also
 *          max instances supported for this core.
 *
 *          It is used by the utils_prf utility to create local tasks objects.
 *          The performance load instance stores the task load on this core.
 *
 *  \param  coreId          Id of the Core
 *  \param  maxLoadInst     Max Load/Task Instances supported for this core,
 *                          returned by the core.
 *
 *  \return pPrfLoadObj     Start pointer to performance load/task instancs
 *          NULL            if core id is wrong or maxLoadInst pointer is null.
 *
 *******************************************************************************
 */
System_LinkStatsPrfLoadObj *Utils_linkStatsGetGetMaxPrfLoadInst(
    UInt32 coreId,
    UInt32 *maxLoadInst);

/**
 *******************************************************************************
 *
 *  \brief  Function to set the sync lost status for different LCD output
 *          from display controller to shared memory
 *
 *  \param  syncLostLcd1    SyncLost Status of LCD1
 *  \param  syncLostLcd2    SyncLost Status of LCD2, Not Applicable for TDA3xx
 *  \param  syncLostLcd3    SyncLost Status of LCD3, Not Applicable for TDA3xx
 *  \param  syncLostTv      SyncLost Status of TV/HDMI,Not Applicable for TDA3xx
 *  \param  dispOcpError    OCP Error count
 *
 *******************************************************************************
 */
Void Utils_linkStatsSetSyncLostCount(UInt32 syncLostLcd1, UInt32 syncLostLcd2,
    UInt32 syncLostLcd3, UInt32 syncLostTv, UInt32 dispOcpError);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif

/* @} */
