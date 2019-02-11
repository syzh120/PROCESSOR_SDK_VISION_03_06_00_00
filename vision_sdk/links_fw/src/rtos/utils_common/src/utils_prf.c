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
 *  \file utils_prf.c
 *
 *  \brief This file has implementation for UTILS PERF API
 *
 *
 *  \version 0.0 (Jun 2013) : [NN] First version
 *  \version 0.1 (Jul 2013) : [NN] Updates as per code review comments
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils_prf.h>
#include <src/rtos/utils_common/include/utils_idle.h>
#include <src/rtos/utils_common/src/utils_link_stats_collector.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \brief Convert float to int by rounding off
 *
 *******************************************************************************
*/
#ifdef BUILD_M4_0
#define UTILS_PRF_MAX_TASK_INST (UTILS_LINK_STATS_PRF_IPU1_0_INST_NUM)
#endif

#ifdef BUILD_M4_1
#define UTILS_PRF_MAX_TASK_INST (UTILS_LINK_STATS_PRF_IPU1_1_INST_NUM)
#endif

#ifdef BUILD_M4_2
#define UTILS_PRF_MAX_TASK_INST (UTILS_LINK_STATS_PRF_IPU2_INST_NUM)
#endif

#ifdef BUILD_A15
#define UTILS_PRF_MAX_TASK_INST (UTILS_LINK_STATS_PRF_A15_0_INST_NUM)
#endif

#ifdef BUILD_DSP_1
#define UTILS_PRF_MAX_TASK_INST (UTILS_LINK_STATS_PRF_DSP1_INST_NUM)
#endif

#ifdef BUILD_DSP_2
#define UTILS_PRF_MAX_TASK_INST (UTILS_LINK_STATS_PRF_DSP2_INST_NUM)
#endif

#ifdef BUILD_ARP32_1
#define UTILS_PRF_MAX_TASK_INST (UTILS_LINK_STATS_PRF_EVE1_INST_NUM)
#endif

#ifdef BUILD_ARP32_2
#define UTILS_PRF_MAX_TASK_INST (UTILS_LINK_STATS_PRF_EVE2_INST_NUM)
#endif

#ifdef BUILD_ARP32_3
#define UTILS_PRF_MAX_TASK_INST (UTILS_LINK_STATS_PRF_EVE3_INST_NUM)
#endif

#ifdef BUILD_ARP32_4
#define UTILS_PRF_MAX_TASK_INST (UTILS_LINK_STATS_PRF_EVE4_INST_NUM)
#endif




/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 *  \brief  Structure containing profiling information for a task.
 *
 *******************************************************************************
 */
typedef struct
{
    uint32_t isAlloc;
    /**< Flag to indicate if this instance is allocated or not */
    BspOsal_TaskHandle pTsk;
    /**< Handle to the task */
    char name[32];
    /**< name of the task */
    uint64_t totalTskThreadTime;
    /**< Total time the task has spent */
} Utils_PrfTsHndl;

/**
 *******************************************************************************
 *
 *  \brief  Structure containing profiling information for all tasks.
 *
 *******************************************************************************
*/
typedef struct
{
    Utils_PrfTsHndl                tskHndlObj[UTILS_PRF_MAX_TASK_INST];
    /**< Array of Utils_PrfTsHndl objects */
    System_LinkStatsPrfLoadObj     *pPrfLoadObj;
    /**< Pointer to the Performance Load information for the tasks
         stored in shared location.
         This memory gets updated only when Copy command is received */
    System_LinkStatsAccPrfLoadObj   accPrfLoadObj;
    /**< Local Copy of the accumulated performance load object */

    System_LinkStatsCorePrfObj     *pCorePrfLoadObj;
    /**< Core performance object,
         will be updated when monitor thread sends command to copy
         performance/load parameters */
} Utils_PrfObj;


/**
 *******************************************************************************
 *
 *  \brief  Structure containing accumulated
 *          profiling information for all tasks.
 *
 *******************************************************************************
*/


/**
 *******************************************************************************
 * \brief An instance of Utils_PrfObj
 *******************************************************************************
 */
Utils_PrfObj gUtils_prfObj;

/**
 *******************************************************************************
 * \brief Varibale to enable or disable Load calculation
 *******************************************************************************
 */
uint32_t gUtils_startLoadCalc = 0;


/*******************************************************************************
 *  Local Function Declaration
 *******************************************************************************
 */
static Void UtilsPrf_ProcessLinkStatsCommand(
    System_LinkStatsCorePrfObj *pCorePrfObj);


/**
 *******************************************************************************
 *
 * \brief Call this function before using any peformance or Timestamp utils
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
int32_t Utils_prfInit(void)
{
    uint32_t maxTskHndl;

    memset(&gUtils_prfObj, 0, sizeof(gUtils_prfObj));

    /* Due to a bug in the load module, you will need to call Load_reset().
       If this not called, then the load is sometimes incorrect the very
       first time, This will be fixed in future Bios release */
    Load_reset();

    /* Getting Core Performance object at init time, so that
       it can be used by other APIs */
    gUtils_prfObj.pCorePrfLoadObj =
        Utils_linkStatsGetPrfLoadInst(System_getSelfProcId());

    UTILS_assert(NULL != gUtils_prfObj.pCorePrfLoadObj);

    if(NULL != gUtils_prfObj.pCorePrfLoadObj)
    {
        /* Initalize core performance load object */
        memset(gUtils_prfObj.pCorePrfLoadObj,
            0x0, sizeof(System_LinkStatsCorePrfObj));
    }

    gUtils_prfObj.pPrfLoadObj = Utils_linkStatsGetGetMaxPrfLoadInst(
        System_getSelfProcId(),
        &maxTskHndl);
    UTILS_assert(0U != maxTskHndl);
    UTILS_assert(NULL != gUtils_prfObj.pPrfLoadObj);
    UTILS_assert(maxTskHndl == UTILS_PRF_MAX_TASK_INST);

    /* Reset allocated Task Handle Object */
    memset(gUtils_prfObj.tskHndlObj, 0,
        sizeof(Utils_PrfTsHndl) * UTILS_PRF_MAX_TASK_INST);

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief de-Init of the performance and timestamp utils
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
int32_t Utils_prfDeInit(void)
{
    gUtils_prfObj.pCorePrfLoadObj = NULL;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Get the 64-bit timer ticks
 *
 * \return  64-bit timer ticks
 *
 *******************************************************************************
 */
uint64_t Utils_prfTsGet64(void)
{
    Types_Timestamp64 ts64;
    uint64_t curTs;

    Timestamp_get64(&ts64);

    curTs = ((uint64_t) ts64.hi << 32) | ts64.lo;

    return curTs;
}

/**
 *******************************************************************************
 *
 * \brief Register a task for load calculation
 *
 * \param  pTsk     [IN] Task Handle
 * \param  name     [IN] A name for the task
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
int32_t Utils_prfLoadRegister(BspOsal_TaskHandle pTsk, char *name)
{
    uint32_t hndlId;
    uint32_t cookie;
    int32_t status = FVID2_EFAIL;
    Utils_PrfTsHndl *pHndl;
    System_LinkStatsCorePrfObj *pCorePrfLoadObj;

    pCorePrfLoadObj = gUtils_prfObj.pCorePrfLoadObj;
    UTILS_assert(NULL != pCorePrfLoadObj);

    cookie = Hwi_disable();

    for (hndlId = 0; hndlId < UTILS_PRF_MAX_TASK_INST; hndlId++)
    {
        pHndl = &gUtils_prfObj.tskHndlObj[hndlId];

        if (pHndl->isAlloc == (uint32_t)FALSE)
        {
            pHndl->isAlloc = (uint32_t)TRUE;
            pHndl->pTsk = pTsk;
            strncpy(pHndl->name, name, sizeof(pHndl->name) - 1U);
            /* The maximum size of name permitted is 31 characters now.
                In cases where the name was exactly 32 characters, there would
                be no space for the string null terminator.
                Also, if the name was > 32 characters and dosent have a null
                terminator. The destination pHndl->name will be a non-null
                terminated string. */
            pHndl->name[sizeof(pHndl->name) - 1U] = (char)'\0';

            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * MISRAC_WAIVER:
             * Pointer is accessed as an array. This is a pointer to
             * the global performance load object. Both global and local
             * performance load objects have same number of instances,
             * and this loop makes sure that it is never accessed out of
             * bound
             */
            /* Copy the parameters in the load object from shared memory,
               Same number of instances are allocated in the shared memory,
               so cnt can be used directly  */
            gUtils_prfObj.pPrfLoadObj[hndlId].isAlloc = (uint32_t)TRUE;

            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * MISRAC_WAIVER:
             * Pointer is accessed as an array. This is a pointer to
             * the global performance load object. Both global and local
             * performance load objects have same number of instances,
             * and this loop makes sure that it is never accessed out of
             * bound
             */
            /* This Alloc Flag can be used by the monitor thread to check
               which all instances are used */
            strncpy(gUtils_prfObj.pPrfLoadObj[hndlId].name,
                    name,
                    sizeof(gUtils_prfObj.pPrfLoadObj[hndlId].name) - 1U);

            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * MISRAC_WAIVER:
             * Pointer is accessed as an array. This is a pointer to
             * the global performance load object. Both global and local
             * performance load objects have same number of instances,
             * and this loop makes sure that it is never accessed out of
             * bound
             */
            /* The maximum size of name permitted is 31 characters now.
                In cases where the name was exactly 32 characters, there would
                be no space for the string null terminator.
                Also, if the name was > 32 characters and dosent have a null
                terminator. The destination pHndl->name will be a non-null
                terminated string. */
            gUtils_prfObj.pPrfLoadObj[hndlId].name \
                [sizeof(gUtils_prfObj.pPrfLoadObj[hndlId].name) - 1U] =
                    (char)'\0';
            status = SYSTEM_LINK_STATUS_SOK;
            break;
        }
    }

    if (SYSTEM_LINK_STATUS_SOK != status)
    {
        Vps_printf(" UTILS: PRF: ##### Cannot allocate Object for %s ####\n",
            name);
    }

    Hwi_restore(cookie);

    return status;
}

/**
 *******************************************************************************
 *
 * \brief Un-Register the task for load caculation
 *
 * \param  pTsk    [IN] Task Handle
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
int32_t Utils_prfLoadUnRegister(BspOsal_TaskHandle pTsk)
{
    uint32_t hndlId;
    uint32_t cookie;
    int32_t status = FVID2_EFAIL;
    Utils_PrfTsHndl *pHndl;
    System_LinkStatsCorePrfObj *pCorePrfLoadObj;

    pCorePrfLoadObj = gUtils_prfObj.pCorePrfLoadObj;
    UTILS_assert(NULL != pCorePrfLoadObj);

    cookie = Hwi_disable();

    for (hndlId = 0; hndlId < UTILS_PRF_MAX_TASK_INST; hndlId++)
    {
        pHndl = &gUtils_prfObj.tskHndlObj[hndlId];

        if (((uint32_t)TRUE == pHndl->isAlloc) && (pHndl->pTsk == pTsk))
        {
            pHndl->isAlloc = (uint32_t)FALSE;

            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * MISRAC_WAIVER:
             * Pointer is accessed as an array. This is a pointer to
             * the global performance load object. Both global and local
             * performance load objects have same number of instances,
             * and this loop makes sure that it is never accessed out of
             * bound
             */
            /* Dealloc this instance from the shared memory also,
               Same number of instances are allocated in the shared memory,
               so cnt can be used directly  */
            gUtils_prfObj.pPrfLoadObj[hndlId].isAlloc = (uint32_t)FALSE;

            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * MISRAC_WAIVER:
             * Pointer is accessed as an array. This is a pointer to
             * the global performance load object. Both global and local
             * performance load objects have same number of instances,
             * and this loop makes sure that it is never accessed out of
             * bound
             */
            strncpy(gUtils_prfObj.pPrfLoadObj[hndlId].name,
                    "",
                    sizeof(gUtils_prfObj.pPrfLoadObj[hndlId].name) - 1U);

            /* MISRA.PTR.ARITH
             * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
             * MISRAC_WAIVER:
             * Pointer is accessed as an array. This is a pointer to
             * the global performance load object. Both global and local
             * performance load objects have same number of instances,
             * and this loop makes sure that it is never accessed out of
             * bound
             */
            /* The maximum size of name permitted is 31 characters now.
            In cases where the name was exactly 32 characters, there would
            be no space for the string null terminator.
            Also, if the name was > 32 characters and dosent have a null
            terminator. The destination pMultiMbxTsk->tskName will be a non-null
            terminated string. */
            gUtils_prfObj.pPrfLoadObj[hndlId].name [\
                sizeof(gUtils_prfObj.pPrfLoadObj[hndlId].name) - 1U] =
                    (char)'\0';
            status = SYSTEM_LINK_STATUS_SOK;
            break;
        }
    }

    Hwi_restore(cookie);

    return status;
}


int32_t Utils_prfGetLoad(Utils_SystemLoadStats *pStats)
{
    uint32_t cpuLoad;
    uint32_t cookie;
    uint64_t idlTime64, totalTime64, temp;

    cookie = Hwi_disable();

    idlTime64 = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeLo[0U] &
        0xFFFFFFFFU;
    temp = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeHi[0U] &
        0xFFFFFFFFU;
    idlTime64 = idlTime64 | (temp << 32U);

    /* Local Call, so getting performance numbers from the local object */
    totalTime64 = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalTimeLo &
        0xFFFFFFFFU;
    temp = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalTimeHi & 0xFFFFFFFFU;
    totalTime64 = totalTime64 | (temp << 32U);

    cpuLoad = 1000U - (uint32_t)((idlTime64 * 1000U) / totalTime64);

#if defined(BUILD_M4_0) && defined(IPU1_SMP_BIOS_INCLUDE)
    /* In case of SMP both cores idle load needs to be taken separately, hence
       we use totalIdlTskTimeLo[1U] for core1 CPU load computation */
    idlTime64 = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeLo[1U] &
        0xFFFFFFFFU;
    temp = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeHi[1U] &
        0xFFFFFFFFU;
    idlTime64 = idlTime64 | (temp << 32U);
    if (0U != idlTime64)
    {
        cpuLoad = cpuLoad + (1000U - (uint32_t)((idlTime64 * 1000U) / totalTime64));
        /* Take average of two cores as cpuLoad for SMP */
        cpuLoad /= 2U;
    }
#endif


    Hwi_restore(cookie);

    pStats->totalLoadParams.integerValue    = cpuLoad/10U;
    pStats->totalLoadParams.fractionalValue = cpuLoad%10U;

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Print loads for all the registered tasks
 *
 * \param  printTskLoad    [IN] print task load if true
 *
 * \return  SYSTEM_LINK_STATUS_SOK on success
 *
 *******************************************************************************
 */
int32_t Utils_prfLoadPrintAll(Bool printTskLoad)
{
    uint32_t hwiLoad, swiLoad, tskLoad, totalLoad, otherLoad;
    uint32_t cpuLoad[2U] = {0U}, smpCpuLoad;
    uint32_t hndlId;
    Utils_PrfTsHndl *pHndl;
    System_LinkStatsAccPrfLoadObj *pAccPrfLoadObj;
    uint64_t totalTime, time64, temp;

    /* Reading from Local Object */
    pAccPrfLoadObj = &gUtils_prfObj.accPrfLoadObj;

    hwiLoad = swiLoad = tskLoad = 0U;

    totalTime = (uint64_t)pAccPrfLoadObj->totalTimeLo & 0xFFFFFFFFU;
    temp = (uint64_t)pAccPrfLoadObj->totalTimeHi & 0xFFFFFFFFU;
    totalTime = totalTime | (temp << 32U);

    time64 = (uint64_t)pAccPrfLoadObj->totalHwiThreadTimeLo & 0xFFFFFFFFU;
    temp = (uint64_t)pAccPrfLoadObj->totalHwiThreadTimeHi & 0xFFFFFFFFU;
    time64 = time64 | (temp << 32U);
    hwiLoad = (uint32_t)((time64 * 1000U) / totalTime);

    time64 = (uint64_t)pAccPrfLoadObj->totalSwiThreadTimeLo & 0xFFFFFFFFU;
    temp = (uint64_t)pAccPrfLoadObj->totalSwiThreadTimeHi & 0xFFFFFFFFU;
    time64 = time64 | (temp << 32U);
    swiLoad = (uint32_t)((time64 * 1000U) / totalTime);

    time64 = (uint64_t)pAccPrfLoadObj->totalIdlTskTimeLo[0U] & 0xFFFFFFFFU;
    temp = (uint64_t)pAccPrfLoadObj->totalIdlTskTimeHi[0U] & 0xFFFFFFFFU;
    time64 = time64 | (temp << 32U);
    cpuLoad[0U] = (uint32_t)((uint64_t)1000U - ((time64 * 1000U) / totalTime));

#if defined(BUILD_M4_0) && defined(IPU1_SMP_BIOS_INCLUDE)
    /* In case of SMP both cores idle load needs to be taken separately, hence
       we use totalIdlTskTimeLo[1U] for core1 CPU load computation */
    time64 = (uint64_t)pAccPrfLoadObj->totalIdlTskTimeLo[1U] & 0xFFFFFFFFU;
    temp = (uint64_t)pAccPrfLoadObj->totalIdlTskTimeHi[1U] & 0xFFFFFFFFU;
    time64 = time64 | (temp << 32U);
    cpuLoad[1U] = ((uint32_t)((uint64_t)1000U - ((time64 * 1000U) / totalTime)));
#endif

    totalLoad = hwiLoad+swiLoad;

    if(System_getSelfProcId()==SYSTEM_IPU_PROC_PRIMARY)
    {
        Vps_printf(" \n");
        Vps_printf(" #### EVE CLK = %4d.%-6d Mhz \n",
            Utils_getClkHz(UTILS_CLK_ID_EVE)/1000000U,
            Utils_getClkHz(UTILS_CLK_ID_EVE)%1000000U
            );
        Vps_printf(" #### DSP CLK = %4d.%-6d Mhz \n",
            Utils_getClkHz(UTILS_CLK_ID_DSP)/1000000U,
            Utils_getClkHz(UTILS_CLK_ID_DSP)%1000000U
            );
        Vps_printf(" #### IPU CLK = %4d.%-6d Mhz \n",
            Utils_getClkHz(UTILS_CLK_ID_IPU)/1000000U,
            Utils_getClkHz(UTILS_CLK_ID_IPU)%1000000U
            );
        Vps_printf(" #### A15 CLK = %4d.%-6d Mhz \n",
            Utils_getClkHz(UTILS_CLK_ID_A15)/1000000U,
            Utils_getClkHz(UTILS_CLK_ID_A15)%1000000U
            );
        Vps_printf(" \n");
    }

    if (totalTime != 0U)
    {
        Vps_printf(" \n");
        if (0U != cpuLoad[1U])
        {
            /* Take average of two cores as cpuLoad for SMP */
            smpCpuLoad = (cpuLoad[0U] + cpuLoad[1U])/2U;
        }
        else
        {
            smpCpuLoad = cpuLoad[0U];
        }

        Vps_printf(" LOAD: CPU: %d.%d%% HWI: %d.%d%%, SWI:%d.%d%% \n",
                    smpCpuLoad/10U, smpCpuLoad%10U,
                    hwiLoad/10U, hwiLoad%10U,
                    swiLoad/10U, swiLoad%10U
                    );

        if (printTskLoad)
        {
            Vps_printf(" \n");

            for (hndlId = 0U; hndlId < UTILS_PRF_MAX_TASK_INST; hndlId++)
            {
                pHndl = &gUtils_prfObj.tskHndlObj[hndlId];

                if ((uint32_t)TRUE == pHndl->isAlloc)
                {
                    tskLoad = 0U;

                    tskLoad = (uint32_t)((pHndl->totalTskThreadTime *
                        (uint64_t)1000U) / totalTime);

                    totalLoad += tskLoad;

                    if (tskLoad)
                    {
                        Vps_printf(" LOAD: TSK: %-20s: %d.%d%% \r\n",
                               pHndl->name,
                               tskLoad/10U,
                               tskLoad%10U
                            );
                    }
                }
            }

            if (0U != cpuLoad[1U])
            {
                /* Take cumulative CPU load of finding misc. load of both cores */
                cpuLoad[0U] += cpuLoad[1U];
            }

            otherLoad = cpuLoad[0U] - totalLoad;

            Vps_printf(" LOAD: TSK: %-20s: %d.%d%% \r\n",
                   "MISC",
                   otherLoad/10U,
                   otherLoad%10U
                );
        }
        Vps_printf(" \n");
    }

    return SYSTEM_LINK_STATUS_SOK;
}

/**
 *******************************************************************************
 *
 * \brief Start taking the performance load for all the registered tasks
 *
 *******************************************************************************
 */
Void Utils_prfLoadCalcStart(void)
{
    uint32_t cookie;
    cookie = Hwi_disable();
    gUtils_startLoadCalc = (uint32_t)TRUE;
    Hwi_restore(cookie);
}

/**
 *******************************************************************************
 *
 * \brief Stop taking the load for all the registered tasks
 *
 *******************************************************************************
 */
Void Utils_prfLoadCalcStop(void)
{
    uint32_t cookie;

    cookie = Hwi_disable();
    gUtils_startLoadCalc = (uint32_t)FALSE;
    Hwi_restore(cookie);
}

/**
 *******************************************************************************
 *
 * \brief Reset the load calculation mainly for next cycle of run
 *
 * \return  None
 *
 *******************************************************************************
 */
Void Utils_prfLoadCalcReset(void)
{
    uint32_t hndlId;
    uint32_t cookie;
    Utils_PrfTsHndl *pHndl;
    System_LinkStatsCorePrfObj *pCorePrfObj;

    /* Global Performance object */
    pCorePrfObj = gUtils_prfObj.pCorePrfLoadObj;
    UTILS_assert(NULL != pCorePrfObj);

    cookie = Hwi_disable();

    /* Reset Local Parameters */
    gUtils_prfObj.accPrfLoadObj.totalHwiThreadTimeHi = 0U;
    gUtils_prfObj.accPrfLoadObj.totalSwiThreadTimeHi = 0U;
    gUtils_prfObj.accPrfLoadObj.totalTimeHi = 0U;
    gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeHi[0U] = 0U;
    gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeHi[1U] = 0U;
    gUtils_prfObj.accPrfLoadObj.totalHwiThreadTimeLo = 0U;
    gUtils_prfObj.accPrfLoadObj.totalSwiThreadTimeLo = 0U;
    gUtils_prfObj.accPrfLoadObj.totalTimeLo = 0U;
    gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeLo[0U] = 0U;
    gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeLo[1U] = 0U;
    gUtils_prfObj.accPrfLoadObj.totalLowPowerTimeHi = 0U;
    gUtils_prfObj.accPrfLoadObj.totalLowPowerTimeLo = 0U;


    /* Reset the performace loads accumulator */
    for (hndlId = 0; hndlId < UTILS_PRF_MAX_TASK_INST; hndlId++)
    {
        pHndl = &gUtils_prfObj.tskHndlObj[hndlId];

        if (((uint32_t)TRUE == pHndl->isAlloc) &&
            (NULL != pHndl->pTsk))
        {
            pHndl->totalTskThreadTime = 0U;
        }
    }

    Hwi_restore(cookie);
}

/**
 *******************************************************************************
 *
 * \brief This function processes link statistics commands
 *
 *        Link stat monitor thread sends different command to each link
 *        This function receives this command and processes it.
 *        Currently only command supported is RESET Link Statistics.
 *
 * \param  pCorePrfObj     [IN] Link Stats Instance handle
 *
 * \return None
 *
 *******************************************************************************
 */
static Void UtilsPrf_ProcessLinkStatsCommand(
    System_LinkStatsCorePrfObj *pCorePrfObj)
{
    int32_t status = 0;
    uint32_t cmd, hndlId;
    Utils_PrfTsHndl *pHndlLcl;
    System_LinkStatsPrfLoadObj *pHndlGbl;
    System_LinkStatsAccPrfLoadObj *pAccPrfLoadLcl, *pAccPrfLoadGbl;

    UTILS_assert(NULL != pCorePrfObj);

    status = Utils_linkStatsRecvCommand(&pCorePrfObj->srcToLinkCmdObj, &cmd);

    if (0 == status)
    {
        if (LINK_STATS_CMD_COPY_CORE_LOAD == cmd)
        {
            pAccPrfLoadLcl = &gUtils_prfObj.accPrfLoadObj;
            pAccPrfLoadGbl = &pCorePrfObj->accPrfLoadObj;

            /* Copy Global Parameters */
            pAccPrfLoadGbl->totalHwiThreadTimeHi =
                pAccPrfLoadLcl->totalHwiThreadTimeHi;
            pAccPrfLoadGbl->totalSwiThreadTimeHi =
                pAccPrfLoadLcl->totalSwiThreadTimeHi;
            pAccPrfLoadGbl->totalTimeHi =
                pAccPrfLoadLcl->totalTimeHi;
            pAccPrfLoadGbl->totalIdlTskTimeHi[0U] =
                pAccPrfLoadLcl->totalIdlTskTimeHi[0U];
#if defined(BUILD_M4_0) && defined(IPU1_SMP_BIOS_INCLUDE)
            pAccPrfLoadGbl->totalIdlTskTimeHi[1U] =
                pAccPrfLoadLcl->totalIdlTskTimeHi[1U];
#endif
            pAccPrfLoadGbl->totalLowPowerTimeHi =
                pAccPrfLoadLcl->totalLowPowerTimeHi;

            pAccPrfLoadGbl->totalHwiThreadTimeLo =
                pAccPrfLoadLcl->totalHwiThreadTimeLo;
            pAccPrfLoadGbl->totalSwiThreadTimeLo =
                pAccPrfLoadLcl->totalSwiThreadTimeLo;
            pAccPrfLoadGbl->totalTimeLo =
                pAccPrfLoadLcl->totalTimeLo;
            pAccPrfLoadGbl->totalIdlTskTimeLo[0U] =
                pAccPrfLoadLcl->totalIdlTskTimeLo[0U];
#if defined(BUILD_M4_0) && defined(IPU1_SMP_BIOS_INCLUDE)
            pAccPrfLoadGbl->totalIdlTskTimeLo[1U] =
                pAccPrfLoadLcl->totalIdlTskTimeLo[1U];
#endif
            pAccPrfLoadGbl->totalLowPowerTimeLo =
                pAccPrfLoadLcl->totalLowPowerTimeLo;

            /* Call the load updated function of each registered task one by one
             * along with the swiLoad, hwiLoad, and Task's own load */
            for (hndlId = 0; hndlId < UTILS_PRF_MAX_TASK_INST; hndlId++)
            {
                pHndlLcl = &gUtils_prfObj.tskHndlObj[hndlId];

                /* MISRA.PTR.ARITH
                 * MISRAC_2004 Rule_17.1 and MISRAC_2004 Rule_17.4
                 * MISRAC_WAIVER:
                 * Pointer is accessed as an array. This is a pointer to
                 * the global performance load object. Both global and local
                 * performance load objects have same number of instances,
                 * and this loop makes sure that it is never accessed out of
                 * bound
                 */
                pHndlGbl = &gUtils_prfObj.pPrfLoadObj[hndlId];

                if (((uint32_t)TRUE == pHndlLcl->isAlloc) &&
                    (NULL != pHndlLcl->pTsk) &&
                    (0 == strncmp(pHndlGbl->name,
                        pHndlLcl->name,
                        sizeof(pHndlGbl->name))))
                {
                    pHndlGbl->totalTskThreadTimeHi =
                        (pHndlLcl->totalTskThreadTime >> 32U) & 0xFFFFFFFFU;
                    pHndlGbl->totalTskThreadTimeLo =
                        (pHndlLcl->totalTskThreadTime) & 0xFFFFFFFFU;
                }
            }

            /* Get the Heap information */
            Utils_memGetHeapStats(UTILS_HEAPID_L2_LOCAL,
                &pCorePrfObj->heapStats[UTILS_HEAPID_L2_LOCAL]);
            Utils_memGetHeapStats(UTILS_HEAPID_DDR_CACHED_LOCAL,
                &pCorePrfObj->heapStats[UTILS_HEAPID_DDR_CACHED_LOCAL]);
            if(System_getSelfProcId()==SYSTEM_IPU_PROC_PRIMARY)
            {
                Utils_memGetHeapStats(UTILS_HEAPID_OCMC_SR,
                    &pCorePrfObj->heapStats[UTILS_HEAPID_OCMC_SR]);
                Utils_memGetHeapStats(UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL,
                    &pCorePrfObj->heapStats[UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL]);
                Utils_memGetHeapStats(UTILS_HEAPID_DDR_CACHED_SR_ECC_QM,
                    &pCorePrfObj->heapStats[UTILS_HEAPID_DDR_CACHED_SR_ECC_QM]);
                Utils_memGetHeapStats(UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL,
                    &pCorePrfObj->heapStats[UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL]);
                Utils_memGetHeapStats(UTILS_HEAPID_DDR_CACHED_SR,
                    &pCorePrfObj->heapStats[UTILS_HEAPID_DDR_CACHED_SR]);
                Utils_memGetHeapStats(UTILS_HEAPID_DDR_NON_CACHED_SR0,
                    &pCorePrfObj->heapStats[UTILS_HEAPID_DDR_NON_CACHED_SR0]);
            }

            {
                BspOsal_StaticMemStatus staticMemStatus;

                BspOsal_getStaticMemStatus(&staticMemStatus);

                pCorePrfObj->maxSemaphoreObjs  = staticMemStatus.numMaxSemObjs;
                pCorePrfObj->freeSemaphoreObjs = staticMemStatus.numFreeSemObjs;
                pCorePrfObj->maxTaskObjs      = staticMemStatus.numMaxTaskObjs;
                pCorePrfObj->freeTaskObjs     = staticMemStatus.numFreeTaskObjs;
                pCorePrfObj->maxClockObjs       = staticMemStatus.numMaxClockObjs;
                pCorePrfObj->freeClockObjs      = staticMemStatus.numFreeClockObjs;
                pCorePrfObj->maxHwiObjs        = staticMemStatus.numMaxHwiObjs;
                pCorePrfObj->freeHwiObjs       = staticMemStatus.numFreeHwiObjs;
            }

            /* Copy is done so send copy_done command to monitor thread */
            cmd = LINK_STATS_CMD_COPY_CORE_LOAD_DONE;
            status = Utils_linkStatsSendCommand(
                &pCorePrfObj->linkToSrcCmdObj, cmd);
            /* This call will not fail as queue is empty as the reset
               command is just successfully read */
            if(status!=0)
            {
                Vps_printf(" UTILS_PRF: Unable to send command [0x%04x] !!!\n", cmd);
            }
        }
    }
}

/**
 *******************************************************************************
 *
 * \brief Function called by Loadupdate for each update cycle
 *
 *******************************************************************************
 */
Void Utils_prfLoadUpdate(void)
{
    Utils_PrfTsHndl *pHndlLcl;
    Load_Stat hwiLoadStat, swiLoadStat, tskLoadStat, idlTskLoadStat[2U];
    Task_Handle idlTskHndl[2U] = {NULL};
    UInt32 hndlId;
    System_LinkStatsAccPrfLoadObj *pAccPrfLoadLcl;
    uint64_t time64, temp;

    if ((uint32_t)TRUE == gUtils_startLoadCalc)
    {
        /* Get the Local Object */
        pAccPrfLoadLcl = &gUtils_prfObj.accPrfLoadObj;

        /* Get the all loads first */
        idlTskHndl[0U] = Task_getIdleTaskHandle(0U);
        Load_getTaskLoad(idlTskHndl[0U], &idlTskLoadStat[0U]);
        Load_getGlobalHwiLoad(&hwiLoadStat);
        Load_getGlobalSwiLoad(&swiLoadStat);

#if defined(BUILD_M4_0) && defined(IPU1_SMP_BIOS_INCLUDE)
        idlTskHndl[1U] = Task_getIdleTaskHandle(1U);
        Load_getTaskLoad(idlTskHndl[1U], &idlTskLoadStat[1U]);
#endif

        time64 = (uint64_t)pAccPrfLoadLcl->totalIdlTskTimeLo[0U] & 0xFFFFFFFFU;
        temp = (uint64_t)pAccPrfLoadLcl->totalIdlTskTimeHi[0U] & 0xFFFFFFFFU;
        time64 = time64 | (temp << 32U);
        time64 += idlTskLoadStat[0U].threadTime;
        pAccPrfLoadLcl->totalIdlTskTimeLo[0U] = (UInt32)time64 & 0xFFFFFFFFU;
        pAccPrfLoadLcl->totalIdlTskTimeHi[0U] = (UInt32)(((UInt32)(time64 >> 32U)) & 0xFFFFFFFFU);

#if defined(BUILD_M4_0) && defined(IPU1_SMP_BIOS_INCLUDE)
        /* Save core1 CPU idle stats in totalIdlTskTimeLo[1U] for core1 CPU
           load computation */
        if (idlTskLoadStat[1U].threadTime > idlTskLoadStat[1U].totalTime)
        {
#ifdef DEBUGPRINT
            Vps_printf( " Utils Prf : Core1 Idle Time = %4d,  Total Time = %4d ",
                        idlTskLoadStat[1U].threadTime, idlTskLoadStat[1U].totalTime);
#endif
            /* Due to some BIOS bug, thread time is more than idle time. We workaround
               by making both equal */
            idlTskLoadStat[1U].threadTime = idlTskLoadStat[1U].totalTime;
        }

        time64 = (uint64_t)pAccPrfLoadLcl->totalIdlTskTimeLo[1U] & 0xFFFFFFFFU;
        temp = (uint64_t)pAccPrfLoadLcl->totalIdlTskTimeHi[1U] & 0xFFFFFFFFU;
        time64 = time64 | (temp << 32U);
        time64 += idlTskLoadStat[1U].threadTime;
        pAccPrfLoadLcl->totalIdlTskTimeLo[1U] = time64 & 0xFFFFFFFFU;
        pAccPrfLoadLcl->totalIdlTskTimeHi[1U] = (time64 >> 32U) & 0xFFFFFFFFU;

#endif

        time64 = (uint64_t)pAccPrfLoadLcl->totalHwiThreadTimeLo & 0xFFFFFFFFU;
        temp = (uint64_t)pAccPrfLoadLcl->totalHwiThreadTimeHi & 0xFFFFFFFFU;
        time64 = time64 | (temp << 32U);
        time64 += hwiLoadStat.threadTime;
        pAccPrfLoadLcl->totalHwiThreadTimeLo = time64 & 0xFFFFFFFFU;
        pAccPrfLoadLcl->totalHwiThreadTimeHi = (time64 >> 32U) & 0xFFFFFFFFU;

        time64 = (uint64_t)pAccPrfLoadLcl->totalSwiThreadTimeLo & 0xFFFFFFFFU;
        temp = (uint64_t)pAccPrfLoadLcl->totalSwiThreadTimeHi & 0xFFFFFFFFU;
        time64 = time64 | (temp << 32U);
        time64 += swiLoadStat.threadTime;
        pAccPrfLoadLcl->totalSwiThreadTimeLo = time64 & 0xFFFFFFFFU;
        pAccPrfLoadLcl->totalSwiThreadTimeHi = (time64 >> 32U) & 0xFFFFFFFFU;

        time64 = (uint64_t)pAccPrfLoadLcl->totalTimeLo & 0xFFFFFFFFU;
        temp = (uint64_t)pAccPrfLoadLcl->totalTimeHi & 0xFFFFFFFFU;
        time64 = time64 | (temp << 32U);
        time64 += hwiLoadStat.totalTime;
        pAccPrfLoadLcl->totalTimeLo = time64 & 0xFFFFFFFFU;
        pAccPrfLoadLcl->totalTimeHi = (time64 >> 32U) & 0xFFFFFFFFU;

        time64 = (uint64_t)pAccPrfLoadLcl->totalLowPowerTimeLo & 0xFFFFFFFFU;
        temp = (uint64_t)pAccPrfLoadLcl->totalLowPowerTimeHi & 0xFFFFFFFFU;
        time64 = time64 | (temp << 32U);
        time64 += Utils_idleGetLowPowerTime();
        pAccPrfLoadLcl->totalLowPowerTimeLo = time64 & 0xFFFFFFFFU;
        pAccPrfLoadLcl->totalLowPowerTimeHi = (time64 >> 32U) & 0xFFFFFFFFU;

        /* Call the load updated function of each registered task one by one
         * along with the swiLoad, hwiLoad, and Task's own load */
        for (hndlId = 0; hndlId < UTILS_PRF_MAX_TASK_INST; hndlId++)
        {
            /* Get the local object */
            pHndlLcl = &gUtils_prfObj.tskHndlObj[hndlId];

            if (((uint32_t)TRUE == pHndlLcl->isAlloc) &&
                (NULL != pHndlLcl->pTsk))
            {
                Load_getTaskLoad(pHndlLcl->pTsk, &tskLoadStat);
                pHndlLcl->totalTskThreadTime += tskLoadStat.threadTime;
            }
        }

        /* Check and process command received from monitor thread */
        UtilsPrf_ProcessLinkStatsCommand(gUtils_prfObj.pCorePrfLoadObj);
    }
}

/**
 *******************************************************************************
 *
 * \brief Reset latency stats
 *
 * \param  lStats    [OUT] latency statistics
 *
 *******************************************************************************
 */
Void Utils_resetLatency(Utils_LatencyStats *lStats)
{
    lStats->accumulatedLatencyHi = lStats->accumulatedLatencyLo = 0U;
    lStats->minLatencyHi = lStats->minLatencyLo = 0xFFFFFFFFU;
    lStats->maxLatencyHi = lStats->maxLatencyLo = 0x0U;
    lStats->countHi = lStats->countLo = 0U;
}

/**
 *******************************************************************************
 *
 * \brief Calculate latency
 *
 * \param  lStats    [OUT] latency statistics
 * \param  linkLocalTime     [IN]  time at which frame was received at the link
 *
 *******************************************************************************
 */
Void Utils_updateLatency(Utils_LatencyStats *lStats,
                         uint64_t linkLocalTime)
{
    uint64_t latency;
    uint64_t curTime = Utils_getCurGlobalTimeInUsec();
    uint64_t time64, temp;

    latency = curTime - linkLocalTime;

    time64 = (uint64_t)lStats->minLatencyLo & 0xFFFFFFFFU;
    temp = (uint64_t)lStats->minLatencyHi & 0xFFFFFFFFU;
    time64 = time64 | (temp << 32U);
    if (time64 > latency)
    {
        lStats->minLatencyHi = (latency >> 32U) & 0xFFFFFFFFU;
        lStats->minLatencyLo = (latency) & 0xFFFFFFFFU;
    }

    time64 = (uint64_t)lStats->maxLatencyLo & 0xFFFFFFFFU;
    temp = (uint64_t)lStats->maxLatencyHi & 0xFFFFFFFFU;
    time64 = time64  | (temp << 32U);
    if (latency > time64)
    {
        lStats->maxLatencyHi = (latency >> 32U) & 0xFFFFFFFFU;
        lStats->maxLatencyLo = (latency) & 0xFFFFFFFFU;
    }

    time64 = (uint64_t)lStats->accumulatedLatencyLo & 0xFFFFFFFFU;
    temp = (uint64_t)lStats->accumulatedLatencyHi & 0xFFFFFFFFU;
    time64 = time64 | (temp << 32U);
    time64 += latency;
    lStats->accumulatedLatencyHi = (time64 >> 32U) & 0xFFFFFFFFU;
    lStats->accumulatedLatencyLo = (time64) & 0xFFFFFFFFU;

    time64 = (uint64_t)lStats->countLo & 0xFFFFFFFFU;
    temp = (uint64_t)lStats->countHi & 0xFFFFFFFFU;
    time64 = time64 | (temp << 32U);
    time64 ++;
    lStats->countHi = (time64 >> 32U) & 0xFFFFFFFFU;
    lStats->countLo = (time64) & 0xFFFFFFFFU;

}

/**
 *******************************************************************************
 *
 * \brief Print the latency statistics
 *
 * \param  name              [IN] Name of module
 * \param  localLinkstats    [IN] local link latency
 * \param  srcToLinkstats    [IN] source to link latency
 * \param  resetStats        [IN] TRUE: reset counters to 0 after printing
 *
 *******************************************************************************
 */
Void Utils_printLatency(char *name,
                        Utils_LatencyStats *localLinkstats,
                        Utils_LatencyStats *srcToLinkstats,
                        Bool resetStats)
{
    uint64_t accLatency64, count64, temp;

    /* Divide by 1000 is done to convert micro second to millisecond */
    Vps_printf( " \n");
    Vps_printf( " [ %s ] LATENCY,\n", name);
    Vps_printf( " ********************\n", name);

    count64 = (uint64_t)localLinkstats->countLo & 0xFFFFFFFFU;
    temp = (uint64_t)localLinkstats->countHi & 0xFFFFFFFFU;
    count64 = count64 | (temp << 32U);
    if(count64)
    {
        accLatency64 = (uint64_t)
            localLinkstats->accumulatedLatencyLo & 0xFFFFFFFFU;
        temp = (uint64_t)localLinkstats->accumulatedLatencyHi &
            0xFFFFFFFFU;
        accLatency64 = accLatency64 | (temp << 32U);

        Vps_printf( " Local Link Latency     : Avg = %6d us, Min = %6d us, Max = %6d us, \r\n",
            (uint32_t)(accLatency64/count64),
            localLinkstats->minLatencyLo,
            localLinkstats->maxLatencyLo);
    }

    count64 = (uint64_t)srcToLinkstats->countLo & 0xFFFFFFFFU;
    temp = (uint64_t)srcToLinkstats->countHi & 0xFFFFFFFFU;
    count64 = count64 | (temp << 32U);
    if(count64)
    {
        accLatency64 = (uint64_t)srcToLinkstats->accumulatedLatencyLo &
            0xFFFFFFFFU;
        temp = (uint64_t)srcToLinkstats->accumulatedLatencyHi & 0xFFFFFFFFU;
        accLatency64 = accLatency64 | (temp << 32U);

        Vps_printf( " Source to Link Latency : Avg = %6d us, Min = %6d us, Max = %6d us, \r\n",
            (uint32_t)(accLatency64/count64),
            srcToLinkstats->minLatencyLo,
            srcToLinkstats->maxLatencyLo);
    }
    Vps_printf( " \n");

    if (resetStats)
    {
        Utils_resetLatency(localLinkstats);
        Utils_resetLatency(srcToLinkstats);
    }

}

/**
 *******************************************************************************
 *
 * \brief Divide between a count value and div value
 *
 *        Returns in units as explained below
 *        - 3000 = 30.00
 *        - 2997 = 29.97
 *
 * \param  count        [IN] count
 * \param  divValue     [IN] divisor
 *
 * \return FPS in units of XXX.DD
 *
 *******************************************************************************
 */

uint32_t Utils_calcFps(uint32_t count, uint32_t divValue)
{
    uint32_t fps, mult, divide;

    /*
     * multiplier and divider is selected based on precision possible in a
     * 32-bit count value
     * i.e make sure count*mult does not overflow the 32-bit value
     *
     */
    if(count < 40000U)
    {
        mult = 1000U*100U;
        divide  = 1U;
    }
    else
    if(count < 400000U)
    {
        mult = 100U*100U;
        divide  = 10U;
    }
    else
    if(count < 4000000U)
    {
        mult = 10U*100U;
        divide  = 100U;
    }
    else
    if(count < 40000000U)
    {
        mult = 1U*100U;
        divide  = 1000U;
    }
    else
    if(count < 400000000U)
    {
        mult = 1U*10U;
        divide  = 10000U;
    }
    else
    {
        mult = 1U*1U;
        divide  = 100000U;
    }

    divide = divValue / divide;

    if(divide==0U)
    {
        fps = 0U;
    }
    else
    {
        fps = (count * mult) / divide;
    }

    return fps;
}

/**
 *******************************************************************************
 *
 * \brief Reset the link statistics
 *
 * \param  pPrm         [OUT] link statistics
 * \param  numCh        [IN]  Number of channels for which statistics
 *                            is collected
 * \param  numOut       [IN]  Number of outputs associated with this channel
 *
 *******************************************************************************
 */
Void Utils_resetLinkStatistics(Utils_LinkStatistics *pPrm,
                                uint32_t numCh,
                                uint32_t numOut)
{
    Utils_LinkChStatistics *pChStats;
    uint32_t chId, outId;


    pPrm->numCh = numCh;

    pPrm->inBufErrorCount = 0U;
    pPrm->outBufErrorCount = 0U;
    pPrm->newDataCmdCount = 0U;
    pPrm->releaseDataCmdCount = 0U;
    pPrm->getFullBufCount = 0U;
    pPrm->putEmptyBufCount = 0U;
    pPrm->notifyEventCount = 0U;

    for(chId=0; chId<pPrm->numCh; chId++)
    {
        pChStats = &pPrm->chStats[chId];

        pChStats->numOut = numOut;
        pChStats->inBufRecvCount = 0U;
        pChStats->inBufDropCount = 0U;
        pChStats->inBufUserDropCount = 0U;
        pChStats->inBufProcessCount = 0U;

        for(outId=0; outId<pChStats->numOut; outId++)
        {
            pChStats->outBufCount[outId] = 0U;
            pChStats->outBufDropCount[outId] = 0U;
            pChStats->outBufUserDropCount[outId] = 0U;
        }
    }

    /* reset stats Start time */
    pPrm->statsStartTime = Utils_getCurGlobalTimeInMsec();
}

/**
 *******************************************************************************
 *
 * \brief Print the link statistics
 *
 * \param  pPrm         [IN] link statistics
 * \param  name         [IN] Link task name
 * \param  resetStats   [IN] TRUE, Reset stats after print
 *
 *******************************************************************************
 */
Void Utils_printLinkStatistics(Utils_LinkStatistics *pPrm, char *name,
                                Bool resetStats)
{
    uint32_t elaspedTime;
    uint32_t chId, outId;
    Utils_LinkChStatistics *pChStats;
    uint32_t value1, value2, value3, value4;

    elaspedTime = (UInt32)Utils_getCurGlobalTimeInMsec() - pPrm->statsStartTime;

    Vps_printf(" \r\n");
    Vps_printf(" [ %s ] Link Statistics,\r\n", name);
    Vps_printf(" ******************************\r\n");
    Vps_printf(" \r\n");
    Vps_printf(" Elapsed time       = %d msec\r\n", elaspedTime);
    Vps_printf(" \r\n");

    if(pPrm->inBufErrorCount)
    {
        Vps_printf(" In Buf Error Count = %d frames\r\n", pPrm->inBufErrorCount);
    }

    if(pPrm->outBufErrorCount)
    {
        Vps_printf(" Out Buf Error Count = %d frames\r\n", pPrm->outBufErrorCount);
    }

    if(pPrm->newDataCmdCount)
    {
        value1 = Utils_calcFps(pPrm->newDataCmdCount, elaspedTime);

        Vps_printf(" New data Recv      = %3d.%d fps\r\n",
                        value1/100U,
                        value1%100U
                    );
    }

    if(pPrm->releaseDataCmdCount)
    {
        value1 = Utils_calcFps(pPrm->releaseDataCmdCount, elaspedTime);

        Vps_printf(" Release data Recv  = %3d.%d fps\r\n",
                        value1/100U,
                        value1%100U
                    );
    }

    if(pPrm->getFullBufCount)
    {
        value1 = Utils_calcFps(pPrm->getFullBufCount, elaspedTime);

        Vps_printf(" Get Full Buf Cb    = %3d.%d fps\r\n",
                        value1/100U,
                        value1%100U
                    );
    }

    if(pPrm->putEmptyBufCount)
    {
        value1 = Utils_calcFps(pPrm->putEmptyBufCount, elaspedTime);

        Vps_printf(" Put Empty Buf Cb   = %3d.%d fps\r\n",
                        value1/100U,
                        value1%100U
                    );
    }

    if(pPrm->notifyEventCount)
    {
        value1 = Utils_calcFps(pPrm->notifyEventCount, elaspedTime);

        Vps_printf(" Driver/Notify Cb   = %3d.%d fps\r\n",
                        value1/100U,
                        value1%100U
                    );
    }

    if(pPrm->numCh)
    {
        Vps_printf(" \r\n");
        Vps_printf(" Input Statistics,\r\n");
        Vps_printf(" \r\n");
        Vps_printf(" CH | In Recv | In Drop | In User Drop | In Process \r\n");
        Vps_printf("    | FPS     | FPS     | FPS          | FPS        \r\n");
        Vps_printf(" -------------------------------------------------- \r\n");

        for(chId=0; chId<pPrm->numCh; chId++)
        {
            pChStats = &pPrm->chStats[chId];

            if((0U != pChStats->inBufRecvCount) ||
               (0U !=  pChStats->inBufDropCount) ||
               (0U !=  pChStats->inBufUserDropCount) ||
               (0U != pChStats->inBufProcessCount))
            {
                value1 = Utils_calcFps(pChStats->inBufRecvCount, elaspedTime);
                value2 = Utils_calcFps(pChStats->inBufDropCount, elaspedTime);
                value3 = Utils_calcFps(pChStats->inBufUserDropCount, elaspedTime);
                value4 = Utils_calcFps(pChStats->inBufProcessCount, elaspedTime);

                Vps_printf(" %2d | %3d.%2d    %3d.%2d    %3d.%2d         %3d.%2d \r\n",
                            chId,
                            value1/100U, value1%100U,
                            value2/100U, value2%100U,
                            value3/100U, value3%100U,
                            value4/100U, value4%100U);
            }
        }
    }

    if((0U != pPrm->numCh) && (0U != pPrm->chStats[0].numOut))
    {
        Vps_printf(" \r\n");
        Vps_printf(" Output Statistics,\r\n");
        Vps_printf(" \r\n");
        Vps_printf(" CH | Out | Out     | Out Drop | Out User Drop \r\n");
        Vps_printf("    | ID  | FPS     | FPS      | FPS           \r\n");
        Vps_printf(" --------------------------------------------- \r\n");

        for(chId=0; chId<pPrm->numCh; chId++)
        {
            pChStats = &pPrm->chStats[chId];

            for(outId=0; outId<pChStats->numOut; outId++)
            {
                if((0U != pChStats->outBufCount[outId]) ||
                   (0U != pChStats->outBufDropCount[outId]) ||
                   (0U != pChStats->outBufUserDropCount[outId]))
                {
                    value1 = Utils_calcFps(
                                pChStats->outBufCount[outId],
                                elaspedTime);

                    value2 = Utils_calcFps(
                                pChStats->outBufDropCount[outId],
                                elaspedTime);

                    value3 = Utils_calcFps(
                                pChStats->outBufUserDropCount[outId],
                                elaspedTime);

                    Vps_printf( " %2d | %2d    %3d.%2d   %3d.%2d    %3d.%2d \r\n",
                        chId,
                        outId,
                        value1/100U, value1%100U,
                        value2/100U, value2%100U,
                        value3/100U, value3%100U
                        );
                }
            }
        }
    }

    if(resetStats)
    {
        /* assume number of outputs = number of outputs of CH0 */
        Utils_resetLinkStatistics(pPrm, pPrm->numCh, pPrm->chStats[0].numOut);
    }
}

#if defined (BUILD_ARP32)
/**
 *******************************************************************************
 *
 * \brief Update the EVE CPU load values when the EVE Auto Clock Gating is
 *        enabled.
 *
 * \param  totalTime   [IN] The total Time calculated before going to Auto CG
 *
 *******************************************************************************
 */
Void Utils_prfUpdateEveLoadPreAutoCg(UInt64 totalTime)
{
    uint64_t time64, temp;
    time64 = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalTimeLo & 0xFFFFFFFFU;
    temp = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalTimeHi & 0xFFFFFFFFU;
    time64 = time64 | (temp << 32U);
    time64 += totalTime;
    gUtils_prfObj.accPrfLoadObj.totalTimeLo = time64 & 0xFFFFFFFFU;
    gUtils_prfObj.accPrfLoadObj.totalTimeHi = (time64 >> 32U) & 0xFFFFFFFFU;
    UtilsPrf_ProcessLinkStatsCommand(gUtils_prfObj.pCorePrfLoadObj);
}

/**
 *******************************************************************************
 *
 * \brief Update the EVE CPU load values when the EVE Auto Clock Gating is
 *        enabled.
 *
 * \param  totalTimeIdle  [IN] The total Time calculated after coming out of
 *                             Auto CG
 *
 *******************************************************************************
 */
Void Utils_prfUpdateEveLoadPostAutoCg(UInt64 totalTimeIdle)
{
    uint64_t time64, temp;
    time64 = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeLo[0U] &
        0xFFFFFFFFU;
    temp = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeHi[0U] &
        0xFFFFFFFFU;
    time64 = time64  | (temp << 32U);
    time64 += totalTimeIdle;
    gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeLo[0U] = (UInt32)time64 & 0xFFFFFFFFU;
    gUtils_prfObj.accPrfLoadObj.totalIdlTskTimeHi[0U] = (UInt32)(((UInt32)(time64 >> 32U)) & 0xFFFFFFFFU);

    time64 = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalTimeLo & 0xFFFFFFFFU;
    temp = (uint64_t)gUtils_prfObj.accPrfLoadObj.totalTimeHi & 0xFFFFFFFFU;
    time64 = time64 | (temp << 32U);
    time64 += totalTimeIdle;
    gUtils_prfObj.accPrfLoadObj.totalTimeLo = time64 & 0xFFFFFFFFU;
    gUtils_prfObj.accPrfLoadObj.totalTimeHi = (time64 >> 32U) & 0xFFFFFFFFU;
}

#endif

