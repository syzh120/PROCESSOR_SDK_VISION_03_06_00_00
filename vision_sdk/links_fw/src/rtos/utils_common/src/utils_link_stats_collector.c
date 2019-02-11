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
 * \file utils_link_stats_collector.c
 *
 * \brief  This file currently just keeps a global variable in
 *         a shared memory, This variable is used for storing link
 *         statistics information.
 *
 * \version 0.0 (Mar 2015) : First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/src/utils_link_stats_collector.h>


/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/* None */

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure stores start index and size information.
 *
 *          The number of link stats objects and performance stats objects
 *          are different for each core. There is a big array of
 *          link stats and performance objects allocated in
 *          #System_LinkStatsCoreObj. This structure is used to get
 *          start index and number of instances into this big array
 *          for each core.
 *******************************************************************************
*/
typedef struct Utils_LinkStatsIndexInfo
{
    UInt32 startIdx;
    /**< Start Index */
    UInt32 numInst;
    /**< Number of instances */
} Utils_LinkStatsIndexInfo_t;

/**
 *******************************************************************************
 *
 *  \brief  Structure for link Statistics Collector Object.
 *
 *          It stores link state colletors local information like which
 *          list state object is allocated for this core.
 *******************************************************************************
*/
typedef struct Utils_LinkStateCollectorObj
{
    UInt32  coreId;
    /**< Core Id, storing it locally */
    BspOsal_SemHandle semHandle;
    /**< Semaphore Handle to protect allocFlags */
    Utils_LinkStatsIndexInfo_t  linkStatsIdxInfo[SYSTEM_PROC_MAX];
    /**< Index information for link stats for each core */
    Utils_LinkStatsIndexInfo_t  prfLoadInstIdxInfo[SYSTEM_PROC_MAX];
    /**< Index information for performance objects for each core */
} Utils_LinkStateCollectorObj_t;



/**
 *******************************************************************************
 *
 *  \brief  Global array for Link Statistics information.
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
#pragma DATA_SECTION(gSystemLinkStatsCoreObj,".bss:extMemNonCache:linkStats");
#pragma DATA_ALIGN(gSystemLinkStatsCoreObj, 128);
#endif
System_LinkStatsCoreObj gSystemLinkStatsCoreObj
#ifdef BUILD_A15
__attribute__ ((section(".bss:extMemNonCache:linkStats")))
__attribute__ ((aligned(128)))
#endif
    ;

/*******************************************************************************
 *  Global structures
 *******************************************************************************
 */


static Utils_LinkStateCollectorObj_t gUtilsLinkStateCollectorObj =
{
    0, NULL,
    {
        {UTILS_LINK_STATS_IPU1_0_INST_START, UTILS_LINK_STATS_IPU1_0_INST_NUM},
        {UTILS_LINK_STATS_IPU1_1_INST_START, UTILS_LINK_STATS_IPU1_1_INST_NUM},
        {UTILS_LINK_STATS_A15_0_INST_START, UTILS_LINK_STATS_A15_0_INST_NUM},
        {UTILS_LINK_STATS_DSP1_INST_START, UTILS_LINK_STATS_DSP1_INST_NUM},
        {UTILS_LINK_STATS_DSP2_INST_START, UTILS_LINK_STATS_DSP2_INST_NUM},
        {UTILS_LINK_STATS_EVE1_INST_START, UTILS_LINK_STATS_EVE1_INST_NUM},
        {UTILS_LINK_STATS_EVE2_INST_START, UTILS_LINK_STATS_EVE2_INST_NUM},
        {UTILS_LINK_STATS_EVE3_INST_START, UTILS_LINK_STATS_EVE3_INST_NUM},
        {UTILS_LINK_STATS_EVE4_INST_START, UTILS_LINK_STATS_EVE4_INST_NUM},
        {UTILS_LINK_STATS_IPU2_INST_START, UTILS_LINK_STATS_IPU2_INST_NUM}
    },
    {
        {UTILS_LINK_STATS_PRF_IPU1_0_INST_START,
            UTILS_LINK_STATS_PRF_IPU1_0_INST_NUM},
        {UTILS_LINK_STATS_PRF_IPU1_1_INST_START,
            UTILS_LINK_STATS_PRF_IPU1_1_INST_NUM},
        {UTILS_LINK_STATS_PRF_A15_0_INST_START,
            UTILS_LINK_STATS_PRF_A15_0_INST_NUM},
        {UTILS_LINK_STATS_PRF_DSP1_INST_START,
            UTILS_LINK_STATS_PRF_DSP1_INST_NUM},
        {UTILS_LINK_STATS_PRF_DSP2_INST_START,
            UTILS_LINK_STATS_PRF_DSP2_INST_NUM},
        {UTILS_LINK_STATS_PRF_EVE1_INST_START,
            UTILS_LINK_STATS_PRF_EVE1_INST_NUM},
        {UTILS_LINK_STATS_PRF_EVE2_INST_START,
            UTILS_LINK_STATS_PRF_EVE2_INST_NUM},
        {UTILS_LINK_STATS_PRF_EVE3_INST_START,
            UTILS_LINK_STATS_PRF_EVE3_INST_NUM},
        {UTILS_LINK_STATS_PRF_EVE4_INST_START,
            UTILS_LINK_STATS_PRF_EVE4_INST_NUM},
        {UTILS_LINK_STATS_PRF_IPU2_INST_START,
            UTILS_LINK_STATS_PRF_IPU2_INST_NUM}
    }
};


/*******************************************************************************
 *  Functions
 *******************************************************************************
 */

static inline UInt32 Utits_isDispLink(UInt32 linkId);


/**
 *******************************************************************************
 *
 *  \brief  Function to initialize link stats collector.
 *
 *          This api initializes Link stats collector, it resets the flags,
 *          counter for each core
 *
 * DES_ID: DOX_DES_TAG(DES_DEBUG_STATS_001)
 * REQ_ID: DOX_REQ_TAG(ADASVISION-1539)
 * REQ_ID: DOX_REQ_TAG(ADASVISION-1538)
 * REQ_ID: DOX_REQ_TAG(ADASVISION-1537)
 *
 *  \returns    0: Collector is initialized and ready to be used
 *              any other number: collector is not initialized and
 *                                return the error
 *******************************************************************************
 */
Int32 Utils_linkStatsCollectorInit(void)
{
    UInt32 cnt;
    UInt32 coreId;
    UInt32 startIdx, numInst;

    gUtilsLinkStateCollectorObj.semHandle = BspOsal_semCreate(
        (Int32)1, (Bool)TRUE);
    UTILS_assert(gUtilsLinkStateCollectorObj.semHandle != NULL);

    /* Locally store the core id of this core,
       so that dont need to get coreId on every alloc/dealloc call */
    gUtilsLinkStateCollectorObj.coreId = System_getSelfProcId();

    /* Initialize all link stats object on the IPU1_0 core */
    if (SYSTEM_IPU_PROC_PRIMARY == gUtilsLinkStateCollectorObj.coreId)
    {
        memset(&gSystemLinkStatsCoreObj, 0x0, sizeof(System_LinkStatsCoreObj));
    }

    coreId = gUtilsLinkStateCollectorObj.coreId;
    startIdx = gUtilsLinkStateCollectorObj.prfLoadInstIdxInfo[coreId].startIdx;
    numInst = gUtilsLinkStateCollectorObj.prfLoadInstIdxInfo[coreId].numInst;
    for (cnt = startIdx; cnt < (numInst + startIdx); cnt ++)
    {
        gSystemLinkStatsCoreObj.linkStats[cnt].isAlloc = (UInt32)FALSE;
    }

    return (0);
}


/**
 *******************************************************************************
 *
 *  \brief  Function to Deinitialize collector.
 *          checks if all link stats objects are de-allocated or not,
 *          Asserts if this is not the case.
 *          This API should be called after deinit of all links
 *
 *******************************************************************************
 */
Void Utils_linkStatsCollectorDeInit(void)
{
    UInt32 cnt;
    UInt32 startIdx, numInst;
    UInt32 coreId;

    /* Check to see if all link stat instances are deallocated */
    coreId = gUtilsLinkStateCollectorObj.coreId;
    startIdx = gUtilsLinkStateCollectorObj.prfLoadInstIdxInfo[coreId].startIdx;
    numInst = gUtilsLinkStateCollectorObj.prfLoadInstIdxInfo[coreId].numInst;
    for (cnt = startIdx; cnt < (numInst + startIdx); cnt ++)
    {
        if ((UInt32)TRUE == gSystemLinkStatsCoreObj.linkStats[cnt].isAlloc)
        {
            UTILS_assert((Bool)FALSE);
        }
    }

    if (NULL != gUtilsLinkStateCollectorObj.semHandle)
    {
        BspOsal_semDelete(&gUtilsLinkStateCollectorObj.semHandle);
    }
}

/**
 *******************************************************************************
 *
 *  \brief  Function to allocate link state object.
 *          Collector keeps a pool of link state object for each core.
 *          This API is used to allocates link state instance from this pool.
 *          Each link calls this api at create time to get link state object.
 *
 *
 *
 *  \return Pointer to link state object
 *          NULL in case there is no free instance in the pool
 *
 *******************************************************************************
 */
System_LinkStatistics *Utils_linkStatsCollectorAllocInst(
    UInt32 linkId, const char linkName[])
{
    UInt32 cnt;
    UInt32 coreId;
    UInt32 dummyCmd;
    System_LinkStatistics *linkStats = NULL;
    Utils_LinkStatsIndexInfo_t *idxInfo = NULL;

    BspOsal_semWait(gUtilsLinkStateCollectorObj.semHandle, BSP_OSAL_WAIT_FOREVER);

    coreId = gUtilsLinkStateCollectorObj.coreId;
    idxInfo = &gUtilsLinkStateCollectorObj.linkStatsIdxInfo[coreId];

    for (cnt = idxInfo->startIdx;
            cnt < (idxInfo->numInst + idxInfo->startIdx);
            cnt ++)
    {
        if ((UInt32)FALSE == gSystemLinkStatsCoreObj.linkStats[cnt].isAlloc)
        {
            linkStats = &gSystemLinkStatsCoreObj.linkStats[cnt];

            /* Initialize command object */
            memset(linkStats, 0x0, sizeof(System_LinkStatistics));

            Utils_resetLinkStatistics(
                &linkStats->linkStats,
                SYSTEM_MAX_CH_PER_OUT_QUE,
                SYSTEM_MAX_OUT_QUE);

            Utils_resetLatency(&linkStats->linkLatency);
            Utils_resetLatency(&linkStats->srcToLinkLatency);

            strncpy(linkStats->linkName, linkName,
                sizeof(linkStats->linkName) - 1U);
            /* The maximum size of name permitted is 31 characters now.
                In cases where the name was exactly 32 characters, there would
                be no space for the string null terminator.
                Also, if the name was > 32 characters and dosent have a null
                terminator. The destination linkStats->linkName will be a
                non-null terminated string. */
            linkStats->linkName[sizeof(linkStats->linkName) - 1U] = (char)'\0';

            /* Dummy Read to clear command queue */
            Utils_linkStatsRecvCommand(
                &linkStats->srcToLinkCmdObj, &dummyCmd);
            Utils_linkStatsRecvCommand(
                &linkStats->linkToSrcCmdObj, &dummyCmd);

            linkStats->linkId = linkId;

            linkStats->isAlloc = (UInt32)TRUE;
            break;
        }
    }

    BspOsal_semPost(gUtilsLinkStateCollectorObj.semHandle);

    return (linkStats);
}

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
Int32 Utils_linkStatsCollectorDeAllocInst(System_LinkStatistics *linkStats)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    UInt32 cnt;
    UInt32 coreId;
    Utils_LinkStatsIndexInfo_t *idxInfo = NULL;

    BspOsal_semWait(gUtilsLinkStateCollectorObj.semHandle, BSP_OSAL_WAIT_FOREVER);

    coreId = gUtilsLinkStateCollectorObj.coreId;
    idxInfo = &gUtilsLinkStateCollectorObj.linkStatsIdxInfo[coreId];

    for (cnt = idxInfo->startIdx;
            cnt < (idxInfo->numInst + idxInfo->startIdx); cnt ++)
    {
        if (linkStats == &gSystemLinkStatsCoreObj.linkStats[cnt])
        {
            /* Alloc flag must be set to TRUE */
            UTILS_assert((UInt32)TRUE == linkStats->isAlloc);

            linkStats->isAlloc = (UInt32)FALSE;

            linkStats = NULL;

            status = SYSTEM_LINK_STATUS_SOK;
            break;
        }
    }

    BspOsal_semPost(gUtilsLinkStateCollectorObj.semHandle);

    return (status);
}

/**
 *******************************************************************************
 *
 *  \brief  Function to send command.
 *
 *          Function sets command in the queue of the list stat
 *          object of the link. This is usually used by the monitor thread
 *          to send the command to the link.
 *
 *  \param  pCmdObj     Pointer to command object
 *  \param  cmd         Command id
 *
 *  \return 0       on success
 *         -1       if command cannot be written to queue
 *
 *******************************************************************************
 */
Int32 Utils_linkStatsSendCommand(System_LinkStatsCmdObj *pCmdObj, UInt32 cmd)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    volatile UInt32 tmpValue;

    /* Error checking */
    if (NULL != pCmdObj)
    {
        if(pCmdObj->rdIdx == pCmdObj->wrIdx)
        {
            /* new command can be written */
            pCmdObj->cmd = cmd;

            /* flip write index */
            pCmdObj->wrIdx ^= 1U;

            /* to make sure earlier write's are written to memory */
            tmpValue = pCmdObj->wrIdx;

            status = SYSTEM_LINK_STATUS_SOK;
        }
        else
        {
            /* old command is not yet read, so new command
                 cannot be written */
            status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    return (status);
}


/**
 *******************************************************************************
 *
 *  \brief  Function to receive command.
 *
 *          Function gets command in the queue of the list stat
 *          object of the link. This is used by the each link to
 *          get the command and process it accordingly in the link.
 *
 *  \param  pCmdObj     Pointer to the link state object
 *  \param  cmd         Command Id
 *
 *  \return 0       on success
 *         -1       if command queue is empty
 *
 *******************************************************************************
 */
Int32 Utils_linkStatsRecvCommand(System_LinkStatsCmdObj *pCmdObj, UInt32 *cmd)
{
    Int32 status = SYSTEM_LINK_STATUS_EFAIL;
    volatile UInt32 tmpValue;

    if ((NULL != pCmdObj) && (NULL != cmd))
    {
        if(pCmdObj->rdIdx != pCmdObj->wrIdx)
        {
              /* new command is written and can be read */
              *cmd = pCmdObj->cmd;

              /* flip read index */
              pCmdObj->rdIdx ^= 1U;

              /* to make sure earlier write's are written to memory */
              tmpValue = pCmdObj->rdIdx;

              status = SYSTEM_LINK_STATUS_SOK;
        }
        else
        {
              /* no new command available */
              status = SYSTEM_LINK_STATUS_EFAIL;
        }
    }

    return status;
}

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
System_LinkStatistics *Utils_linkStatsGetLinkStatInst(UInt32 linkId)
{
    UInt32 coreId;
    UInt32 linkCnt;
    System_LinkStatistics *tmpLinkStats = NULL;
    System_LinkStatistics *linkStats = NULL;
    Utils_LinkStatsIndexInfo_t *idxInfo = NULL;

    coreId = SYSTEM_GET_PROC_ID(linkId);

    if (coreId < SYSTEM_PROC_MAX)
    {
        idxInfo = &gUtilsLinkStateCollectorObj.linkStatsIdxInfo[coreId];

        for (linkCnt = idxInfo->startIdx;
                linkCnt < (idxInfo->numInst + idxInfo->startIdx); linkCnt ++)
        {
            tmpLinkStats = &gSystemLinkStatsCoreObj.linkStats[linkCnt];
            if (((UInt32)TRUE == tmpLinkStats->isAlloc) &&
                (SYSTEM_GET_LINK_ID(linkId) == SYSTEM_GET_LINK_ID(
                    tmpLinkStats->linkId)))
            {
                linkStats = tmpLinkStats;
                break;
            }
        }
    }

    return (linkStats);
}

/**
 *******************************************************************************
 *
 *  \brief  Function to Pointer to accumulated performance load object.
 *
 *          Accumulated performance object keeps load information for each core.
 *          There is one object created for each core. This function is used to
 *          get pointer to this object.
 *          This is used by utils_prf.c utility to print the total load
 *          and also to store the load statistics in shared memory.
 *
 * DES_ID: DES_DEBUG_STATS_001
 * ARC_ID: ARC_PSDKV_089
 * REQ_ID: ADASVISION-1539
 * REQ_ID: ADASVISION-1538
 * REQ_ID: ADASVISION-1537
 *
 *  \param  coreId          Id of the Core
 *
 *  \return pAccPrfLoadObj  Pointer to Accumulated performance load
 *          NULL            If core Id is invalid.
 *
 *******************************************************************************
 */
System_LinkStatsCorePrfObj *Utils_linkStatsGetPrfLoadInst(UInt32 coreId)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    System_LinkStatsCorePrfObj *pCoreLoadObj = NULL;

    /* Check for errors */
    if (coreId >= SYSTEM_PROC_MAX)
    {
        status = SYSTEM_LINK_STATUS_EFAIL;
    }

    if (0 == status)
    {
        pCoreLoadObj = &gSystemLinkStatsCoreObj.corePrfObj[coreId];
    }

    return (pCoreLoadObj);
}


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
    UInt32 *maxLoadInst)
{
    UInt32 startIdx;
    System_LinkStatsPrfLoadObj *pPrfLoadObjStart = NULL;

    /* Check for errors */
    if ((coreId >= SYSTEM_PROC_MAX) || (NULL == maxLoadInst))
    {
        pPrfLoadObjStart = NULL;
    }
    else
    {
        startIdx = gUtilsLinkStateCollectorObj.prfLoadInstIdxInfo[coreId].
                        startIdx;
        *maxLoadInst = gUtilsLinkStateCollectorObj.prfLoadInstIdxInfo
                            [coreId].numInst;
        pPrfLoadObjStart = &gSystemLinkStatsCoreObj.prfLoadObj[startIdx];
    }

    return (pPrfLoadObjStart);
}

static inline UInt32 Utits_isDispLink(UInt32 linkId)
{
    UInt32 isDispLink = (UInt32)FALSE;

    if ((linkId == SYSTEM_LINK_ID_DISPLAY_0) ||
        (linkId == SYSTEM_LINK_ID_DISPLAY_1) ||
        (linkId == SYSTEM_LINK_ID_DISPLAY_2) ||
        (linkId == SYSTEM_LINK_ID_DISPLAY_3))
    {
        isDispLink = (UInt32)TRUE;
    }

    return (isDispLink);
}

Void Utils_linkStatsPrintLinkStatistics(UInt32 linkId)
{
    System_LinkStatistics *pLinkStats;
    Utils_LinkStatistics linkStats;
    Utils_LatencyStats   linkLatency;
    Utils_LatencyStats   srcToLinkLatency;
    UInt32 cmd;

    pLinkStats = Utils_linkStatsGetLinkStatInst(linkId);
    if(pLinkStats==NULL)
    {
        Vps_printf(" CPU [%8s], LinkID [%3d], Link Statistics not available !\n",
                System_getProcName(SYSTEM_GET_PROC_ID(linkId)),
                SYSTEM_GET_LINK_ID(linkId)
            );
    }
    else
    {
        /* take a local copy */
        linkStats = pLinkStats->linkStats;
        linkLatency = pLinkStats->linkLatency;
        srcToLinkLatency = pLinkStats->srcToLinkLatency;

        Vps_printf(" \n");
        Vps_printf(" ### CPU [%6s], LinkID [%3d],\n",
                System_getProcName(SYSTEM_GET_PROC_ID(linkId)),
                SYSTEM_GET_LINK_ID(linkId)
            );
        Utils_printLinkStatistics(&linkStats, pLinkStats->linkName,
            (Bool)FALSE);

        Utils_printLatency(pLinkStats->linkName,
                           &linkLatency,
                           &srcToLinkLatency,
                           (Bool)FALSE);

        if ((UInt32)TRUE == Utits_isDispLink(SYSTEM_GET_LINK_ID(linkId)))
        {
            Vps_printf(" Display UnderFlow Count = %d\n",
                pLinkStats->underFlowOverFlowStatus);
            Vps_printf(" \n");
        }

        /* reset link stats */
        Utils_linkStatsSendCommand(
                    &pLinkStats->srcToLinkCmdObj,
                    LINK_STATS_CMD_RESET_STATS);

        /* clear any pending commands */
        Utils_linkStatsRecvCommand(&pLinkStats->linkToSrcCmdObj, &cmd);
    }
}

Void  Utils_linkStatsCollectorProcessCmd(System_LinkStatistics *linkStatsInfo)
{
    Int32 status = SYSTEM_LINK_STATUS_SOK;
    UInt32 cmd;

    UTILS_assert(NULL != linkStatsInfo);


    if(linkStatsInfo->isAlloc)
    {
        status = Utils_linkStatsRecvCommand(&linkStatsInfo->srcToLinkCmdObj, &cmd);

        if (0 == status)
        {
            if (LINK_STATS_CMD_RESET_STATS == cmd)
            {
                Utils_resetLinkStatistics(
                    &linkStatsInfo->linkStats,
                    SYSTEM_MAX_CH_PER_OUT_QUE,
                    1U);

                Utils_resetLatency(&linkStatsInfo->linkLatency);
                Utils_resetLatency(&linkStatsInfo->srcToLinkLatency);

                /* Reset is done so send reset_done command to monitor thread */
                cmd = LINK_STATS_CMD_RESET_STATS_DONE;
                Utils_linkStatsSendCommand(
                    &linkStatsInfo->linkToSrcCmdObj, cmd);
            }
        }
    }
}

Void Utils_linkStatsSetSyncLostCount(UInt32 syncLostLcd1, UInt32 syncLostLcd2,
    UInt32 syncLostLcd3, UInt32 syncLostTv, UInt32 dispOcpError)
{
    gSystemLinkStatsCoreObj.syncLost1 = syncLostLcd1;
    gSystemLinkStatsCoreObj.syncLost2 = syncLostLcd2;
    gSystemLinkStatsCoreObj.syncLost3 = syncLostLcd3;
    gSystemLinkStatsCoreObj.syncLostTV = syncLostTv;
    gSystemLinkStatsCoreObj.dispOcpError = dispOcpError;
}

Void Utils_linkStatsPrintDisplayErrorStats(void)
{
    Vps_printf(" \n");

    if (0U != gSystemLinkStatsCoreObj.dispOcpError)
    {
        Vps_printf(" DISPLAY: OCP Error Count = %d\n",
            gSystemLinkStatsCoreObj.dispOcpError);
    }
    if (0U != gSystemLinkStatsCoreObj.syncLost1)
    {
        Vps_printf(" DISPLAY: LCD1 Sync Lost Count = %d\n",
            gSystemLinkStatsCoreObj.syncLost1);
    }

#if defined (SOC_TDA2PX) || defined (SOC_TDA2XX) || defined (SOC_TDA2EX)
    if (0U != gSystemLinkStatsCoreObj.syncLost2)
    {
        Vps_printf(" DISPLAY: LCD2 Sync Lost Count = %d\n",
            gSystemLinkStatsCoreObj.syncLost2);
    }
    if (0U != gSystemLinkStatsCoreObj.syncLost3)
    {
        Vps_printf(" DISPLAY: LCD3 Sync Lost Count = %d\n",
            gSystemLinkStatsCoreObj.syncLost3);
    }
    if (0U != gSystemLinkStatsCoreObj.syncLostTV)
    {
        Vps_printf(" DISPLAY: TV/HDMI Sync Lost Count = %d\n",
            gSystemLinkStatsCoreObj.syncLostTV);
    }
#endif

    Vps_printf(" \n");
}

/*******************************************************************************
 *  Local Functions
 *******************************************************************************
 */

/* None */
