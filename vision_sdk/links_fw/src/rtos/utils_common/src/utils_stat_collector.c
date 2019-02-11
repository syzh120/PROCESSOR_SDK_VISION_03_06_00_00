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
 * \file utils_stat_collector.c
 *
 * \brief  This file has the implementataion of statCollector task.
 *
 *
 * \version 0.0 (Jan 2014) : [CM] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */
#include "utils_stat_collector_prv.h"
#include "utils_stat_collector_cfg.h"
#include <src/rtos/utils_common/include/utils_tsk.h>

/**
 *******************************************************************************
 * \brief Link Stack
 *******************************************************************************
 */
#pragma DATA_ALIGN(gUtilsStatColl_tskStack, 32)
#pragma DATA_SECTION(gUtilsStatColl_tskStack, ".bss:taskStackSection")
UInt8 gUtilsStatColl_tskStack[UTILS_STAT_COLL_TSK_STACK_SIZE];

#ifndef TDA3XX_FAMILY_BUILD
/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * MISRAC_WAIVER: All global variables are defined at the tope of the file.
 */
static Utils_StatCollSdramUsecase sdram_cfg_array_0[] =
                                UTILS_STAT_COLLECTOR_SDRAM_CFG_ARRAY_0;
#endif
/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * MISRAC_WAIVER: All global variables are defined at the tope of the file.
 */
static Utils_StatCollMstrUsecase mstr_cfg_array_0[] =
                                UTILS_STAT_COLLECTOR_MSTR_CFG_ARRAY_0;
/* MISRA.VAR.MIN.VIS
 * MISRAC_2004_Rule_8.7
 * MISRAC_WAIVER: All global variables are defined at the tope of the file.
 */
static Utils_StatCollMstrUsecase mstr_cfg_array_1[] =
                                UTILS_STAT_COLLECTOR_MSTR_CFG_ARRAY_1;

static Utils_StatCollDataVisCtrl data_vis_ctrl = \
                            UTILS_STAT_COLLECTOR_DATAVIS_CTRL_DEFAULT;

Utils_StatCollCtrl gUtils_statCollCtrl;

/* Theoretical Max value of the bandwidth. This is determined by L3 frequency */
#define UTILS_STATCOLL_THEORETICAL (266U*16U)

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
Void Utils_statColCompute(UInt32 statColType,
                               UInt32 diff,
                               UInt32 uc_idx,
                               UInt32 cfg_idx,
                               UInt64 elaspedTimeAvg,
                          UInt64 elaspedTimePeak,
                          UInt32 samplingWindow);

Void Utils_statCollectorPrintThroughPut(char *descr,
                        UInt64 avg,
                        UInt64 peak);


Void Utils_statCollectorPrintLatency(char *descr,
                        UInt64 avg,
                        UInt64 peak);

Void Utils_statCollectorRegisterMstr(UInt32 cfg_idx);

Void Utils_statCollectorRegisterSdram(UInt32 cfg_idx);

Void Utils_statCollectorResetCounters(void);

Void Utils_statCollectorTskMain(UArg arg0, UArg arg1);

Void Utils_statCollectorUnRegisterMstr(UInt32 cfg_idx);

Void Utils_statCollectorUnRegisterSdram(UInt32 cfg_idx);
 /**
 *******************************************************************************
 *
 * \brief   Comuputes the average of stat collector values
 *
 *          Function caluclates the average values and updates them once in
 *          every SAMPLING_WINDOW_WIDTH interval.
 *
 * DES_ID: DOX_DES_TAG(DES_DEBUG_STATS_001)
 * REQ_ID: DOX_REQ_TAG(ADASVISION-1540)
 *
 *******************************************************************************
 */
Void Utils_statColCompute(UInt32 statColType,
                               UInt32 diff,
                               UInt32 uc_idx,
                               UInt32 cfg_idx,
                               UInt64 elaspedTimeAvg,
                          UInt64 elaspedTimePeak,
                          UInt32 samplingWindow)
{
    UInt32 i = 0;
    UInt32 oldIntState;
    UInt64 tmpPeak = 0;

    if((statColType == SDRAM) && (cfg_idx < MAX_SDRAM_CFGS))
    {
        Utils_StatCollSdramCfg *pCfg;

        pCfg = &gUtils_statCollCtrl.sdramCfg[cfg_idx];

        for( i= 0;
            i < pCfg->data[uc_idx].numCounters;
            i++)
        {
            pCfg->total[uc_idx] += diff;

            /* For each interval at calculate what is the
             * peak bandwidth.
             */
            tmpPeak = ((UInt64)diff*(UInt64)1000000)/elaspedTimePeak;

            if ((tmpPeak/(UInt64)1000000) < UTILS_STATCOLL_THEORETICAL)
            {
                /* Discount the value if greater than theoretical max.
                 * Not expected to be here but added just in case.
                 */

                if(tmpPeak > pCfg->data[uc_idx].peak[i])
                {
                    pCfg->data[uc_idx].peak[i] = tmpPeak;
                }
            }
            if((elaspedTimeAvg/1000U) > samplingWindow)
            {
                oldIntState = Hwi_disable();

                pCfg->data[uc_idx].avg[i]
                    = (pCfg->total[uc_idx]*(UInt64)1000000)/elaspedTimeAvg;

                pCfg->data[uc_idx].peakRate[i]
                    = pCfg->data[uc_idx].peak[i];

                pCfg->total[uc_idx] = 0;
                pCfg->data[uc_idx].peak[i] = 0;

                Hwi_restore(oldIntState);
            }
        }
    }
    else if((statColType == MSTR) && (cfg_idx < MAX_MSTR_CFGS))
    {
        Utils_StatCollMstrCfg *pCfg;

        pCfg = &gUtils_statCollCtrl.mstrCfg[cfg_idx];

        for( i= 0;
            i < pCfg->data[uc_idx].numCounters;
            i++)
        {
            pCfg->total[uc_idx] += diff;
            pCfg->count[uc_idx] ++;

            /*
            * MISRA.PTR.ARITH
            * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:
            * Pointer is used in arithmetic or array index expression
            * KW State: Defer -> Waiver -> Case by case
            */
            if(pCfg->cfg[uc_idx].cfg.usecase==SCI_MSTR_THROUGHPUT)
            {
                tmpPeak = ((UInt64)diff*1000000U)/elaspedTimePeak;
            }
            else
            {
                tmpPeak = diff;
            }

            if ((tmpPeak/(UInt64)1000000) < UTILS_STATCOLL_THEORETICAL)
            {
                /* Discount the value if greater than theoretical max.
                 * Not expected to be here but added just in case.
                 */
                if(tmpPeak > pCfg->data[uc_idx].peak[i])
                {
                    pCfg->data[uc_idx].peak[i] = tmpPeak;
                }
            }

            if((elaspedTimeAvg/1000U) > samplingWindow)
            {
                oldIntState = Hwi_disable();

                if(pCfg->cfg[uc_idx].cfg.usecase==SCI_MSTR_THROUGHPUT)
                {
                    pCfg->data[uc_idx].avg[i]
                        = (pCfg->total[uc_idx]*(UInt64)1000000)/elaspedTimeAvg;

                    pCfg->data[uc_idx].peakRate[i]
                        = pCfg->data[uc_idx].peak[i];
                }
                else
                {
                    pCfg->data[uc_idx].avg[i]
                        = pCfg->total[uc_idx]/pCfg->count[uc_idx];

                    pCfg->data[uc_idx].peakRate[i]
                        = pCfg->data[uc_idx].peak[i];
                }

                pCfg->total[uc_idx] = 0;
                pCfg->count[uc_idx] = 0;
                pCfg->data[uc_idx].peak[i] = 0;

                Hwi_restore(oldIntState);
            }
        }
    }
    else
    {
        /* MISRA-C Requires else for every else if */
    }
}

/**
 *******************************************************************************
 *
 * \brief   Reset the stat collector values
 *
 *          Function itrates through a loop of number of statcol usecase and
 *          resets the values.
 *
 *
 *******************************************************************************
*/
Void Utils_statCollectorReset(void)
{
    gUtils_statCollCtrl.doReset = (Bool)TRUE;
}


Void Utils_statCollectorResetCounters(void)
{
    UInt32 uc_idx, cfg_idx;
    UInt32 tmpNumCounters;
    UInt32 oldIntState;

    oldIntState = Hwi_disable();

    for(cfg_idx=0U; cfg_idx<MAX_SDRAM_CFGS; cfg_idx++)
    {
        Utils_StatCollSdramCfg *pCfg;

        pCfg = &gUtils_statCollCtrl.sdramCfg[cfg_idx];

        for(uc_idx = 0; uc_idx < pCfg->num_uc; uc_idx++)
        {
            tmpNumCounters = pCfg->data[uc_idx].numCounters;

            memset( &pCfg->data[uc_idx],
                    0,
                    sizeof(pCfg->data[uc_idx])
                );

            memset( &pCfg->total[uc_idx],
                    0,
                    sizeof(pCfg->total[uc_idx])
                );

            pCfg->data[uc_idx].numCounters = tmpNumCounters;
        }
    }

    for(cfg_idx=0U; cfg_idx<MAX_MSTR_CFGS; cfg_idx++)
    {
        Utils_StatCollMstrCfg *pCfg;

        pCfg = &gUtils_statCollCtrl.mstrCfg[cfg_idx];

        for(uc_idx = 0; uc_idx < pCfg->num_uc; uc_idx++)
        {
            tmpNumCounters = pCfg->data[uc_idx].numCounters;

            memset( &pCfg->data[uc_idx],
                    0,
                    sizeof(pCfg->data[uc_idx])
                );

            memset( &pCfg->total[uc_idx],
                    0,
                    sizeof(pCfg->total[uc_idx])
                );

            memset( &pCfg->count[uc_idx],
                    0,
                    sizeof(pCfg->count[uc_idx])
                );

            pCfg->data[uc_idx].numCounters = tmpNumCounters;
        }
    }

    Hwi_restore(oldIntState);
}


Void Utils_statCollectorPrintThroughPut(char *descr,
                        UInt64 avg,
                        UInt64 peak)
{
    UInt32 peakInt = (UInt32) (peak/(UInt64)1000000);
    UInt32 peakFrac = (UInt32) (peak%(UInt64)1000000);
    UInt32 avgInt = (UInt32) (avg/(UInt64)1000000);
    UInt32 avgFrac = (UInt32) (avg%(UInt64)1000000);
    Vps_printf(" %-20s | %6d.%06d %6d.%06d\n",
        descr,
        avgInt,
        avgFrac,
        peakInt,
        peakFrac
    );
}

Void Utils_statCollectorPrintLatency(char *descr,
                        UInt64 avg,
                        UInt64 peak)
{
    Vps_printf(" %-20s | %6llu        %6llu cycles\n",
        descr,
        avg,
        peak
    );
}

/**
 *******************************************************************************
 *
 * \brief   Prints the stat collector values
 *
 *          Function itrates through a loop of number of statcol usecase and
 *          prints the averaged values. These are been updated once in
 *          SAMPLING_WINDOW_WIDTH duration.
 *
 *
 *******************************************************************************
*/
Void Utils_statCollectorPrintCount(void)
{
    Int32 uc_idx = 0;
    Int32 num_counters = 0;
    UInt32 cfg_idx;

    Vps_printf(" \r\n");
    Vps_printf(" Statistics Collector,\r\n");
    Vps_printf(" \r\n");
    Vps_printf("       STATISTIC          Avg Data        Peak Data \r\n");
    Vps_printf("       COLLECTOR          MB/s            MB/s      \r\n");
    Vps_printf(" -------------------------------------------------- \r\n");

    for(cfg_idx=0U; cfg_idx<MAX_SDRAM_CFGS; cfg_idx++)
    {
        Utils_StatCollSdramCfg *pCfg;

        pCfg = &gUtils_statCollCtrl.sdramCfg[cfg_idx];

        for(uc_idx = 0; uc_idx < pCfg->num_uc; uc_idx++)
        {
            num_counters = pCfg->data[uc_idx].numCounters;

            switch(num_counters)
            {
                /*
                * MISRA.PTR.ARITH
                * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:
                * Pointer is used in arithmetic or array index expression
                * KW State: Defer -> Waiver -> Case by case
                */
                case 1  :
                    Utils_statCollectorPrintThroughPut(
                        pCfg->cfg[uc_idx].descr,
                        pCfg->data[uc_idx].avg[0],
                        pCfg->data[uc_idx].peakRate[0]
                    );
                    break;

                case 2  :
                    Utils_statCollectorPrintThroughPut(
                        pCfg->cfg[uc_idx].descr,
                        pCfg->data[uc_idx].avg[0],
                        pCfg->data[uc_idx].peakRate[0]
                    );
                    Utils_statCollectorPrintThroughPut(
                        pCfg->cfg[uc_idx].descr,
                        pCfg->data[uc_idx].avg[1],
                        pCfg->data[uc_idx].peakRate[1]
                    );
                    break;
                default:
                    break;
            }
        }
    }
    for(cfg_idx=0U; cfg_idx<MAX_MSTR_CFGS; cfg_idx++)
    {
        Utils_StatCollMstrCfg *pCfg;

        pCfg = &gUtils_statCollCtrl.mstrCfg[cfg_idx];

        for(uc_idx = 0; uc_idx < pCfg->num_uc; uc_idx++)
        {
            num_counters = pCfg->data[uc_idx].numCounters;

            switch(num_counters)
            {
                case 1  :
                    if(pCfg->cfg[uc_idx].cfg.usecase==SCI_MSTR_THROUGHPUT)
                    {
                        Utils_statCollectorPrintThroughPut(
                            pCfg->cfg[uc_idx].descr,
                            pCfg->data[uc_idx].avg[0],
                            pCfg->data[uc_idx].peakRate[0]
                        );
                    }
                    else
                    {
                        Utils_statCollectorPrintLatency(
                            pCfg->cfg[uc_idx].descr,
                            pCfg->data[uc_idx].avg[0],
                            pCfg->data[uc_idx].peakRate[0]
                        );

                    }
                    break;

                case 2  :
                    if(pCfg->cfg[uc_idx].cfg.usecase==SCI_MSTR_THROUGHPUT)
                    {
                        Utils_statCollectorPrintThroughPut(
                            pCfg->cfg[uc_idx].descr,
                            pCfg->data[uc_idx].avg[0],
                            pCfg->data[uc_idx].peakRate[0]
                        );
                        Utils_statCollectorPrintThroughPut(
                            pCfg->cfg[uc_idx].descr,
                            pCfg->data[uc_idx].avg[1],
                            pCfg->data[uc_idx].peakRate[1]
                        );

                    }
                    else
                    {
                        Utils_statCollectorPrintLatency(
                            pCfg->cfg[uc_idx].descr,
                            pCfg->data[uc_idx].avg[0],
                            pCfg->data[uc_idx].peakRate[0]
                        );
                        Utils_statCollectorPrintLatency(
                            pCfg->cfg[uc_idx].descr,
                            pCfg->data[uc_idx].avg[1],
                            pCfg->data[uc_idx].peakRate[1]
                        );
                    }
                    break;
                default:
                    break;

            }
        }
    }
}

Void Utils_statCollectorRegisterMstr(UInt32 cfg_idx)
{
    UInt32 uc_idx;
    Int32 total_cntrs = 0;
    sci_err_t system_sci_err;

    struct sci_config_mstr *pSciCfg = NULL;
    Utils_StatCollMstrCfg *pCfg;

    pCfg = &gUtils_statCollCtrl.mstrCfg[cfg_idx];

    for(uc_idx = 0U;
        uc_idx < pCfg->num_uc;
        uc_idx++ )
    {
    /*
     * MISRA.PTR.ARITH
     * MISRAC_2004_Rule_17.1 MISRAC_2004_Rule_17.4:
     * Pointer is used in arithmetic or array index expression
     * KW State: Defer -> Waiver -> Case by case
     */
        pSciCfg = &pCfg->cfg[uc_idx].cfg;

        system_sci_err = sci_reg_usecase_mstr(
                                    gUtils_statCollCtrl.psci_hdl,
                                    pSciCfg,
                                    &pCfg->uc_key[uc_idx]
                                    );

        UTILS_assert(system_sci_err == SCI_SUCCESS);

        sci_dump_info(gUtils_statCollCtrl.psci_hdl,
                        &pCfg->uc_key[uc_idx],
                        1U,
                        &total_cntrs);

        pCfg->data[uc_idx].numCounters = total_cntrs;
    }
}

Void Utils_statCollectorRegisterSdram(UInt32 cfg_idx)
{
    Int32 uc_idx;
    Int32 total_cntrs = 0;
    sci_err_t system_sci_err;

    sci_config_sdram_t *pSciCfg = NULL;
    Utils_StatCollSdramCfg *pCfg;

    pCfg = &gUtils_statCollCtrl.sdramCfg[cfg_idx];

    for(uc_idx = 0;
        uc_idx < pCfg->num_uc;
        uc_idx++ )
    {
        pSciCfg = &pCfg->cfg[uc_idx].cfg;

        system_sci_err = sci_reg_usecase_sdram(
                                    gUtils_statCollCtrl.psci_hdl,
                                    pSciCfg,
                                    &pCfg->uc_key[uc_idx]
                                    );

        UTILS_assert(system_sci_err == SCI_SUCCESS);

        sci_dump_info(gUtils_statCollCtrl.psci_hdl,
                        &pCfg->uc_key[uc_idx],
                        1U,
                        &total_cntrs);

        pCfg->data[uc_idx].numCounters = total_cntrs;
    }
}

Void Utils_statCollectorUnRegisterMstr(UInt32 cfg_idx)
{
    Int32 uc_idx;
    sci_err_t system_sci_err;
    Utils_StatCollMstrCfg *pCfg;

    pCfg = &gUtils_statCollCtrl.mstrCfg[cfg_idx];

    for(uc_idx = 0;
        uc_idx < pCfg->num_uc;
        uc_idx++ )
    {
        system_sci_err = sci_remove_usecase(
                                    gUtils_statCollCtrl.psci_hdl,
                                    &pCfg->uc_key[uc_idx]
                            );

        UTILS_assert(system_sci_err == SCI_SUCCESS);
    }
}

Void Utils_statCollectorUnRegisterSdram(UInt32 cfg_idx)
{
    Int32 uc_idx;
    sci_err_t system_sci_err;
    Utils_StatCollSdramCfg *pCfg;

    pCfg = &gUtils_statCollCtrl.sdramCfg[cfg_idx];

    for(uc_idx = 0;
        uc_idx < pCfg->num_uc;
        uc_idx++ )
    {
        system_sci_err = sci_remove_usecase(
                                    gUtils_statCollCtrl.psci_hdl,
                                    &pCfg->uc_key[uc_idx]
                            );

        UTILS_assert(system_sci_err == SCI_SUCCESS);
    }
}

/**
 *******************************************************************************
 *
 * \brief   Stat Collector Task Function
 *
 *          This functions executes on saperate thread
 *
 *          Stat Collector is initialized and started.
 *          Periodically the values are optamed avgrage is computed.
 *
 *
 *******************************************************************************
*/
Void Utils_statCollectorTskMain(UArg arg0, UArg arg1)
{
    sci_config_t system_sci_config;
    sci_err_t system_sci_err;
    Utils_StatCollSdramCfg *pSdramCfg;
    Utils_StatCollMstrCfg *pMstrCfg;
    UInt32 samplingWindow = SAMPLING_WINDOW_WIDTH;

    UInt32 mstr_cfg_idx, sdram_cfg_idx, uc_idx;
    UInt64 elaspedTimeAvg, elaspedTimePeak;
    UInt32 oldIntState;

    gUtils_statCollCtrl.mstrCfg[0].num_uc = UTILS_ARRAYSIZE(mstr_cfg_array_0);
    gUtils_statCollCtrl.mstrCfg[0].cfg    = mstr_cfg_array_0;

    gUtils_statCollCtrl.mstrCfg[1].num_uc = UTILS_ARRAYSIZE(mstr_cfg_array_1);
    gUtils_statCollCtrl.mstrCfg[1].cfg    = mstr_cfg_array_1;

#ifdef TDA3XX_FAMILY_BUILD
    gUtils_statCollCtrl.sdramCfg[0].num_uc = 0;
    gUtils_statCollCtrl.sdramCfg[0].cfg    = NULL;
#else
    gUtils_statCollCtrl.sdramCfg[0].num_uc = UTILS_ARRAYSIZE(sdram_cfg_array_0);
    gUtils_statCollCtrl.sdramCfg[0].cfg    = sdram_cfg_array_0;
#endif
    system_sci_config.errhandler = NULL;
    system_sci_config.data_options = 0;
    system_sci_config.sdram_msg_rate = 8192;
    system_sci_config.mstr_msg_rate = 256;
    system_sci_config.trigger_enable = (bool)FALSE;
    system_sci_config.mode = SCI_MODE_DUMP;

    system_sci_err = sci_open(&gUtils_statCollCtrl.psci_hdl, &system_sci_config);
    UTILS_assert(system_sci_err == SCI_SUCCESS);

    mstr_cfg_idx = 0;
    sdram_cfg_idx = 0;

    Utils_statCollectorRegisterMstr(mstr_cfg_idx);
    Utils_statCollectorRegisterSdram(sdram_cfg_idx);

    system_sci_err = sci_global_enable(gUtils_statCollCtrl.psci_hdl);
    UTILS_assert(system_sci_err == SCI_SUCCESS);

    Utils_statCollectorReset();

    while(!gUtils_statCollCtrl.doStop)
    {
        pMstrCfg  = &gUtils_statCollCtrl.mstrCfg[mstr_cfg_idx];
        pSdramCfg = &gUtils_statCollCtrl.sdramCfg[sdram_cfg_idx];

#ifdef DATA_VIS_INCLUDE
        {
            Bool isUpdate;
            UInt32 sampleDuration;

            if(NULL != data_vis_ctrl.getSampleDuration)
            {
                data_vis_ctrl.getSampleDuration(&isUpdate, &sampleDuration);
                if((Bool)TRUE == isUpdate)
                {
                    samplingWindow = sampleDuration;
                }
            }
        }
#endif

        if(gUtils_statCollCtrl.doReset)
        {
            oldIntState = Hwi_disable();
            gUtils_statCollCtrl.doReset = (Bool)FALSE;
            Utils_statCollectorResetCounters();
            sci_dump(gUtils_statCollCtrl.psci_hdl);
            gUtils_statCollCtrl.startTimeAvg = Utils_getCurGlobalTimeInUsec();
            gUtils_statCollCtrl.startTimePeak = Utils_getCurGlobalTimeInUsec();
            Hwi_restore(oldIntState);
        }
        else
        {
            oldIntState = Hwi_disable();
            sci_dump_cntrs(gUtils_statCollCtrl.psci_hdl,
                            pSdramCfg->uc_key,
                            pSdramCfg->num_uc,
                            pSdramCfg->stat_buf);

            sci_dump_cntrs(gUtils_statCollCtrl.psci_hdl,
                            pMstrCfg->uc_key,
                            pMstrCfg->num_uc,
                            pMstrCfg->stat_buf);

            sci_dump(gUtils_statCollCtrl.psci_hdl);
            elaspedTimeAvg = Utils_getCurGlobalTimeInUsec() - gUtils_statCollCtrl.startTimeAvg;
            elaspedTimePeak = Utils_getCurGlobalTimeInUsec() - gUtils_statCollCtrl.startTimePeak;

            gUtils_statCollCtrl.startTimePeak = Utils_getCurGlobalTimeInUsec();
            Hwi_restore(oldIntState);
            for( uc_idx = 0; uc_idx < pSdramCfg->num_uc; uc_idx++)
            {
                Utils_statColCompute(SDRAM,
                                    pSdramCfg->stat_buf[uc_idx],
                                    uc_idx,
                                    sdram_cfg_idx,
                                    elaspedTimeAvg,
                                    elaspedTimePeak,
                                    samplingWindow);
            }

            for( uc_idx = 0; uc_idx < pMstrCfg->num_uc; uc_idx++)
            {
                Utils_statColCompute(MSTR,
                                        pMstrCfg->stat_buf[uc_idx],
                                        uc_idx,
                                        mstr_cfg_idx,
                                        elaspedTimeAvg,
                                        elaspedTimePeak,
                                        samplingWindow);
            }

            if((elaspedTimeAvg/1000U) > samplingWindow)
            {
                system_sci_err = sci_global_disable(gUtils_statCollCtrl.psci_hdl);
                UTILS_assert(system_sci_err == SCI_SUCCESS);

#ifdef DATA_VIS_INCLUDE
                if(NULL != data_vis_ctrl.getLogForVis)
                {
                    data_vis_ctrl.getLogForVis();
                }
#endif

                Utils_statCollectorUnRegisterSdram(sdram_cfg_idx);
                Utils_statCollectorUnRegisterMstr(mstr_cfg_idx);

                mstr_cfg_idx = (mstr_cfg_idx+1U)%MAX_MSTR_CFGS;
                sdram_cfg_idx = (sdram_cfg_idx+1U)%MAX_SDRAM_CFGS;

                Utils_statCollectorRegisterMstr(mstr_cfg_idx);
                Utils_statCollectorRegisterSdram(sdram_cfg_idx);
                oldIntState = Hwi_disable();
                system_sci_err = sci_global_enable(gUtils_statCollCtrl.psci_hdl);
                UTILS_assert(system_sci_err == SCI_SUCCESS);

                gUtils_statCollCtrl.startTimeAvg = Utils_getCurGlobalTimeInUsec();
                gUtils_statCollCtrl.startTimePeak = Utils_getCurGlobalTimeInUsec();
                sci_dump(gUtils_statCollCtrl.psci_hdl);
                Hwi_restore(oldIntState);
            }
        }
        BspOsal_sleep(CNTR_DUMP_INTRVL);
    }

    system_sci_err = sci_global_disable(gUtils_statCollCtrl.psci_hdl);
    UTILS_assert(system_sci_err == SCI_SUCCESS);


    Utils_statCollectorUnRegisterSdram(sdram_cfg_idx);
    Utils_statCollectorUnRegisterMstr(mstr_cfg_idx);

    system_sci_err = sci_close(&gUtils_statCollCtrl.psci_hdl);
    UTILS_assert(system_sci_err == SCI_SUCCESS);

    gUtils_statCollCtrl.doStop = (Bool)FALSE;
}

/**
 *******************************************************************************
 *
 * \brief   Stat Collector Init Function
 *
 *          This functions creates on saperate task which
 *          Stat Collector is initialized and started.
 *
 *******************************************************************************
*/
Void Utils_statCollectorInit(void)
{
    GetSampleDuration tempGetSampleDuration;
    GetLogForVis tempGetLogForVis;

    tempGetSampleDuration = data_vis_ctrl.getSampleDuration;
    tempGetLogForVis = data_vis_ctrl.getLogForVis;

    memset(&gUtils_statCollCtrl, 0, sizeof(gUtils_statCollCtrl));

    data_vis_ctrl.getSampleDuration = tempGetSampleDuration;
    data_vis_ctrl.getLogForVis = tempGetLogForVis;

    gUtils_statCollCtrl.doStop = (Bool)FALSE;

    gUtils_statCollCtrl.tskHndl =
        BspOsal_taskCreate(
                (BspOsal_TaskFuncPtr)Utils_statCollectorTskMain,
                "Utils_statCollectorTskMain",
                UTILS_STAT_COLL_TSK_PRI,
                gUtilsStatColl_tskStack,
                sizeof(gUtilsStatColl_tskStack),
                NULL,
                UTILS_TSK_AFFINITY_CORE0
            );
    UTILS_assert(gUtils_statCollCtrl.tskHndl != NULL);

    Utils_prfLoadRegister(gUtils_statCollCtrl.tskHndl, "STAT_COLL");
}

/**
 *******************************************************************************
 *
 * \brief   Stat Collector deInit Function
 *
 *          DeInit And terminate the thread
 *
 *******************************************************************************
*/
Void Utils_statCollectorDeInit(void)
{
    gUtils_statCollCtrl.doStop = (Bool)TRUE;

    Utils_prfLoadUnRegister(gUtils_statCollCtrl.tskHndl);

    BspOsal_taskDelete(&gUtils_statCollCtrl.tskHndl);
}

Void Utils_statCollectorRegistergetSampleDurationCb(
                                            GetSampleDuration sampleDurationCb)
{
    data_vis_ctrl.getSampleDuration = sampleDurationCb;
}

Void Utils_statCollectorRegistergetLogForVisCb(GetLogForVis getLogForVis)
{
    data_vis_ctrl.getLogForVis = getLogForVis;
}
