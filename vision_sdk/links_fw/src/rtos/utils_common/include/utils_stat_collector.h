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
 * \defgroup UTILS_STATCOLLECTOR_API Stat Collector related utilities
 *
 * @{
 *
 *******************************************************************************
 */

/**
 *******************************************************************************
 *
 * \file utils_stat_collector.h
 *
 * \brief  Stat Collector related utilities
 *
 * \version 0.0 (Jan 2014) : [CM] First version
 *
 *
 *******************************************************************************
 */

#ifndef UTILS_STAT_COLLECTOR_H
#define UTILS_STAT_COLLECTOR_H

#ifdef __cplusplus
extern "C"
{
#endif

/*******************************************************************************
 *  Include files
 *******************************************************************************
 */
#include <src/rtos/utils_common/include/utils.h>
#include <src/rtos/utils_common/include/sci.h>
#ifdef TDA3XX_FAMILY_BUILD
#include <src/rtos/utils_common/include/sci_tda3x.h>
#else
#include <src/rtos/utils_common/include/sci_dra7xx.h>
#endif

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
#define MAX_SDRAM_USECASES          16
#define MAX_SDRAM_CFGS              1U
#define MAX_CNTRS_REQD              2
#define MAX_MSTR_USECASES           36
#define MAX_MSTR_CFGS               2U

/*******************************************************************************
 *  ENUMS
 *******************************************************************************
 */
#ifdef TDA3XX_BUILD
typedef enum {
    UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_WR,
    UTILS_STATCOLL_DATA_BW_MOD_IPU1,
    UTILS_STATCOLL_DATA_BW_MOD_DSP1_MDMA,
    UTILS_STATCOLL_DATA_BW_MOD_DSP2_MDMA,
    UTILS_STATCOLL_DATA_BW_MOD_DSS,
    UTILS_STATCOLL_DATA_BW_MOD_MMU,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_RD,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_WR,
    UTILS_STATCOLL_DATA_BW_MOD_VIP1_P1,
    UTILS_STATCOLL_DATA_BW_MOD_VIP1_P2,
    UTILS_STATCOLL_DATA_BW_MOD_ISS_RT,
    UTILS_STATCOLL_DATA_BW_MOD_ISS_NRT2,
    UTILS_STATCOLL_DATA_BW_MOD_EVE1_P1,
    UTILS_STATCOLL_DATA_BW_MOD_EVE1_P2,
    UTILS_STATCOLL_DATA_BW_MOD_GMAC_SW,
    UTILS_STATCOLL_DATA_BW_MOD_ISS_NRT1,
    UTILS_STATCOLL_DATA_BW_MOD_DSP2_CFG,
    UTILS_STATCOLL_DATA_BW_MOD_DSP2_EDMA,
    UTILS_STATCOLL_DATA_BW_MOD_OCMC_RAM,
    UTILS_STATCOLL_DATA_BW_MOD_DSP1_CFG,
    UTILS_STATCOLL_DATA_BW_MOD_DSP1_EDMA,
    UTILS_STATCOLL_DATA_BW_MOD_GPMC,
    UTILS_STATCOLL_DATA_BW_MOD_MCASP,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_RD,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_WR,
    UTILS_STATCOLL_DATA_BW_MOD_MAX
} Utils_StatCollDataBwModule;
#elif defined(TDA2XX_BUILD)
typedef enum {

    UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_WR,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF2_RD_WR,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_ONLY,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF1_WR_ONLY,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF2_RD_ONLY,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF2_WR_ONLY,
    UTILS_STATCOLL_DATA_BW_MOD_MA_MPU_P1,
    UTILS_STATCOLL_DATA_BW_MOD_MA_MPU_P2,
    UTILS_STATCOLL_DATA_BW_MOD_DSS,
    UTILS_STATCOLL_DATA_BW_MOD_IPU1,
    UTILS_STATCOLL_DATA_BW_MOD_VIP1_P1,
    UTILS_STATCOLL_DATA_BW_MOD_VIP1_P2,
    UTILS_STATCOLL_DATA_BW_MOD_VPE_P1,
    UTILS_STATCOLL_DATA_BW_MOD_VPE_P2,
    UTILS_STATCOLL_DATA_BW_MOD_DSP1_MDMA,
    UTILS_STATCOLL_DATA_BW_MOD_DSP1_EDMA,
    UTILS_STATCOLL_DATA_BW_MOD_DSP2_MDMA,
    UTILS_STATCOLL_DATA_BW_MOD_DSP2_EDMA,
    UTILS_STATCOLL_DATA_BW_MOD_EVE1_TC0,
    UTILS_STATCOLL_DATA_BW_MOD_EVE1_TC1,
    UTILS_STATCOLL_DATA_BW_MOD_EVE2_TC0,
    UTILS_STATCOLL_DATA_BW_MOD_EVE2_TC1,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_RD,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_WR,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_RD,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_WR,
    UTILS_STATCOLL_DATA_BW_MOD_VIP2_P1,
    UTILS_STATCOLL_DATA_BW_MOD_VIP2_P2,
    UTILS_STATCOLL_DATA_BW_MOD_VIP3_P1,
    UTILS_STATCOLL_DATA_BW_MOD_VIP3_P2,
    UTILS_STATCOLL_DATA_BW_MOD_EVE3_TC0,
    UTILS_STATCOLL_DATA_BW_MOD_EVE3_TC1,
    UTILS_STATCOLL_DATA_BW_MOD_EVE4_TC0,
    UTILS_STATCOLL_DATA_BW_MOD_EVE4_TC1,
    UTILS_STATCOLL_DATA_BW_MOD_IVA,
    UTILS_STATCOLL_DATA_BW_MOD_GPU_P1,
    UTILS_STATCOLL_DATA_BW_MOD_GPU_P2,
    UTILS_STATCOLL_DATA_BW_MOD_GMAC_SW,
    UTILS_STATCOLL_DATA_BW_MOD_OCMC_RAM1,
    UTILS_STATCOLL_DATA_BW_MOD_OCMC_RAM2,
    UTILS_STATCOLL_DATA_BW_MOD_OCMC_RAM3,
    UTILS_STATCOLL_DATA_BW_MOD_MAX

} Utils_StatCollDataBwModule;
#elif defined(TDA2PX_BUILD)
typedef enum {

    UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_WR,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF2_RD_WR,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_ONLY,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF1_WR_ONLY,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF2_RD_ONLY,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF2_WR_ONLY,
    UTILS_STATCOLL_DATA_BW_MOD_MA_MPU_P1,
    UTILS_STATCOLL_DATA_BW_MOD_MA_MPU_P2,
    UTILS_STATCOLL_DATA_BW_MOD_DSS,
    UTILS_STATCOLL_DATA_BW_MOD_IPU1,
    UTILS_STATCOLL_DATA_BW_MOD_VIP1_P1,
    UTILS_STATCOLL_DATA_BW_MOD_VIP1_P2,
    UTILS_STATCOLL_DATA_BW_MOD_VPE_P1,
    UTILS_STATCOLL_DATA_BW_MOD_VPE_P2,
    UTILS_STATCOLL_DATA_BW_MOD_DSP1_MDMA,
    UTILS_STATCOLL_DATA_BW_MOD_DSP1_EDMA,
    UTILS_STATCOLL_DATA_BW_MOD_DSP2_MDMA,
    UTILS_STATCOLL_DATA_BW_MOD_DSP2_EDMA,
    UTILS_STATCOLL_DATA_BW_MOD_EVE1_TC0,
    UTILS_STATCOLL_DATA_BW_MOD_EVE1_TC1,
    UTILS_STATCOLL_DATA_BW_MOD_EVE2_TC0,
    UTILS_STATCOLL_DATA_BW_MOD_EVE2_TC1,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_RD,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_WR,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_RD,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_WR,
    UTILS_STATCOLL_DATA_BW_MOD_VIP2_P1,
    UTILS_STATCOLL_DATA_BW_MOD_VIP2_P2,
    UTILS_STATCOLL_DATA_BW_MOD_IVA,
    UTILS_STATCOLL_DATA_BW_MOD_GPU_P1,
    UTILS_STATCOLL_DATA_BW_MOD_GPU_P2,
    UTILS_STATCOLL_DATA_BW_MOD_GMAC_SW,
    UTILS_STATCOLL_DATA_BW_MOD_OCMC_RAM1,
    UTILS_STATCOLL_DATA_BW_MOD_OCMC_RAM2,
    UTILS_STATCOLL_DATA_BW_MOD_OCMC_RAM3,
    UTILS_STATCOLL_DATA_BW_MOD_ISS_RT,
    UTILS_STATCOLL_DATA_BW_MOD_ISS_NRT1,
    UTILS_STATCOLL_DATA_BW_MOD_ISS_NRT2,
    UTILS_STATCOLL_DATA_BW_MOD_CAL,
    UTILS_STATCOLL_DATA_BW_MOD_MAX

} Utils_StatCollDataBwModule;
#elif defined(TDA2EX_BUILD)
typedef enum {

    UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_WR,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF1_RD_ONLY,
    UTILS_STATCOLL_DATA_BW_MOD_EMIF1_WR_ONLY,
    UTILS_STATCOLL_DATA_BW_MOD_MA_MPU_P1,
    UTILS_STATCOLL_DATA_BW_MOD_MA_MPU_P2,
    UTILS_STATCOLL_DATA_BW_MOD_DSS,
    UTILS_STATCOLL_DATA_BW_MOD_IPU1,
    UTILS_STATCOLL_DATA_BW_MOD_VIP1_P1,
    UTILS_STATCOLL_DATA_BW_MOD_VIP1_P2,
    UTILS_STATCOLL_DATA_BW_MOD_VPE_P1,
    UTILS_STATCOLL_DATA_BW_MOD_VPE_P2,
    UTILS_STATCOLL_DATA_BW_MOD_DSP1_MDMA,
    UTILS_STATCOLL_DATA_BW_MOD_DSP1_EDMA,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_RD,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC0_WR,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_RD,
    UTILS_STATCOLL_DATA_BW_MOD_EDMA_TC1_WR,
    UTILS_STATCOLL_DATA_BW_MOD_CAL,
    UTILS_STATCOLL_DATA_BW_MOD_IVA,
    UTILS_STATCOLL_DATA_BW_MOD_GPU_P1,
    UTILS_STATCOLL_DATA_BW_MOD_GPU_P2,
    UTILS_STATCOLL_DATA_BW_MOD_GMAC_SW,
    UTILS_STATCOLL_DATA_BW_MOD_MAX

} Utils_StatCollDataBwModule;
#endif

/*******************************************************************************
 *  Structures
 *******************************************************************************
 */
typedef Void (*GetSampleDuration)(Bool *pIsUpdate,UInt32 *pSampleDuration);
typedef Void (*GetLogForVis)(Void);

typedef struct {

    UInt64 avg[MAX_CNTRS_REQD];
    /**< Average Stat Collector in Time Window */

    UInt64 peakRate[MAX_CNTRS_REQD];
    /**< Peak MB/s Stat Collector in Time Window */

    UInt64 peak[MAX_CNTRS_REQD];
    /**< Peak bytes Stat Collector in Time Window */

    UInt32 numCounters;
    /**< number of counter for stat collector */

} Utils_StatCollData;

typedef struct {

    char *descr;
    Utils_StatCollDataBwModule idx;
    struct sci_config_mstr cfg;

}Utils_StatCollMstrUsecase;

typedef struct {

    UInt32                     stat_buf[MAX_MSTR_USECASES];
    sci_usecase_key            uc_key[MAX_MSTR_USECASES];
    Utils_StatCollData         data[MAX_MSTR_USECASES];
    UInt64                     total[MAX_MSTR_USECASES];
    UInt64                     count[MAX_MSTR_USECASES];
    Utils_StatCollMstrUsecase *cfg;
    UInt32                     num_uc;

} Utils_StatCollMstrCfg;

typedef struct {

    char *descr;
    Utils_StatCollDataBwModule idx;
    sci_config_sdram_t cfg;

} Utils_StatCollSdramUsecase;

typedef struct {

    UInt32                      stat_buf[MAX_SDRAM_USECASES];
    sci_usecase_key             uc_key[MAX_SDRAM_USECASES];
    Utils_StatCollData          data[MAX_SDRAM_USECASES];
    UInt64                      total[MAX_SDRAM_USECASES];
    Utils_StatCollSdramUsecase *cfg;
    UInt32                      num_uc;

} Utils_StatCollSdramCfg;

typedef struct {

    Utils_StatCollMstrCfg    mstrCfg[MAX_MSTR_CFGS];
    Utils_StatCollSdramCfg   sdramCfg[MAX_SDRAM_CFGS];
    volatile Bool            doStop;
    volatile Bool            doReset;
    psci_handle              psci_hdl;
    UInt64                   startTimeAvg;
    UInt64                   startTimePeak;
    BspOsal_TaskHandle       tskHndl;

} Utils_StatCollCtrl;

/*******************************************************************************
 *  EXTERNS
 *******************************************************************************
 */
extern Utils_StatCollCtrl gUtils_statCollCtrl;
/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
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

Void Utils_statCollectorInit(void);
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
Void Utils_statCollectorPrintCount(void);

/**
 *******************************************************************************
 *
 * \brief   Stat Collector deInit Function
 *
 *          DeInit And terminate the thread
 *
 *******************************************************************************
*/

Void Utils_statCollectorDeInit(void);

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

Void Utils_statCollectorReset(void);

Void Utils_statCollectorRegistergetSampleDurationCb(
                                            GetSampleDuration sampleDurationCb);
Void Utils_statCollectorRegistergetLogForVisCb(GetLogForVis getLogForVis);

#ifdef __cplusplus
}
#endif

#endif /* UTILS_STAT_COLLECTOR_H */

/* @} */
