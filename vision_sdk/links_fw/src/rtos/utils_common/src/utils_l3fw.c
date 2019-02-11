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
 * \file utils_l3fw.c
 *
 * \brief  This file has the implementation for utility functions for using
 *         firewalls on TDA2x and TDA3x.
 *         Currently supports only following firewalls:
 *          - EMIF (EMIF1 only)
 *          - MA-MPU (EMIF accesses from A15 in TDA2x)
 *         The VisionSDK example will demonstrate FFI only on following:
 *          - DSP and DSP_EDMA (using XMC - not present in this file)
 *          - EVE and EVE_EDMA (using Firewalls)
 *         FFI on EVE and EVE_EDMA
 *          We do not demonstrate protection on code-regions on EVE to avoid
 *          complexities in VisionSDK framework.
 *          We demonstrate how to prevent write-access from EVE to two specific
 *          ASIL regions - UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL and
 *          UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL.
 *          VisionSDK framework on EVE will have full access to these regions.
 *          Only the "safeFrameCopyPlugin" will be denied access.
 *          VisionSDK framework will ensure firewall permission switch before
 *          executing this plugin.
 *          To demonstrate error detection, we will generate write accesses to
 *          these regions in the safeFrameCopyPlugin and demonstrate that these
 *          accesses are prevented by firewalls and detected by the VisionSDK
 *          framework.
 *
 * \version 0.0 (Dec 2015) : [CSG] First version
 *
 *******************************************************************************
*/

/*******************************************************************************
 *  INCLUDE FILES
 *******************************************************************************
 */

#include <xdc/std.h>
#include <string.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/irq_xbar_interrupt_ids.h>
#include <ti/sysbios/family/shared/vayu/IntXbar.h>
#include "utils_common/include/utils_l3fw.h"
#include "utils_common/include/utils_mem.h"
#include "utils_common/include/utils_spinlock.h"
#include <ti/drv/fw_l3l4/fwlibl3.h>
#include <ti/drv/vps/include/osal/bsp_safety_osal.h>
#include <ti/drv/pm/pmhal.h>

/*******************************************************************************
 *  Defines
 *******************************************************************************
 */
/* Interrupt ID for firewall violations */
#define L3FW_IPU_INTR_ID            (50U)

#define EMIF1_FW_PORT_NUM           (0x0U)
#define EMIF2_FW_PORT_NUM           (0x1U)

/* Macros for Region numbers - Don't exceed 8 regions for TDA2x */
#define L3FW_VSDK_REGION_BACKGROUND      (0x0U)
#define L3FW_VSDK_REGION_ECC_ASIL        (0x1U)
#define L3FW_VSDK_REGION_ECC_QM          (0x2U)
#define L3FW_VSDK_REGION_NON_ECC_ASIL    (0x3U)
#define L3FW_VSDK_REGION_IPC_NON_CACHED  (0x4U)
#define L3FW_VSDK_REGION_DSP1_DATA       (0x5U)
#define L3FW_VSDK_REGION_DSP2_DATA       (0x6U)
#define L3FW_VSDK_REGION_EVE1_DATA       (0x7U)
#ifndef TDA2EX_BUILD
#define L3FW_VSDK_REGION_COUNT           (L3FW_VSDK_REGION_EVE1_DATA + 1U)
#else
#define L3FW_VSDK_REGION_COUNT           (L3FW_VSDK_REGION_DSP1_DATA + 1U)
#endif

/* Permission summary:
 * Firewall is recommended to be used to control access from EVE and
 * peripherals like VIP/DSS
 * For these masters, it is not possible to control permissions based on
 * USER and SUPERVISOR mode due to lack of MREQSUPERVISOR signal in HW.
 * Therefore, all USR/SPV bits need to be set in firewall registers.
 * Permissions to master should be controlled by enabling all-READ or all-WRITE
 * accesses using the firewall
 *
 * DBG access will be enabled for all regions
 *   - If this is not done, breakpoints will not work in ASIL regions
 *
 * All masters are assumed in DOMAIN0.
 * For TDA2x-GP devices, this is fixed in HW.
 * For TDA2x-HS/TDA3x devices, this can be changed - but not supported by this
 * SW layer.
 */

/* All Supervisor/User accesses need to be enabled in Firewall.
 * This is because IPU/EVE/Peripherals like VIP/DSS do not support sending
 * MREQSUPERVISOR signal in their transactions.
 */
#define L3FW_REGION_PERMISSION_MODE_FULL  \
    (L3FW_REGION_PERMISSION_PUB_USR_EXE   | \
     L3FW_REGION_PERMISSION_PUB_USR_WRITE | \
     L3FW_REGION_PERMISSION_PUB_USR_READ  | \
     L3FW_REGION_PERMISSION_PUB_PRV_EXE   | \
     L3FW_REGION_PERMISSION_PUB_PRV_WRITE | \
     L3FW_REGION_PERMISSION_PUB_PRV_READ  | \
     L3FW_REGION_PERMISSION_PUB_USR_DEBUG | \
     L3FW_REGION_PERMISSION_PUB_PRV_DEBUG | \
     L3FW_REGION_PERMISSION_SEC_USR_EXE   | \
     L3FW_REGION_PERMISSION_SEC_USR_WRITE | \
     L3FW_REGION_PERMISSION_SEC_USR_READ  | \
     L3FW_REGION_PERMISSION_SEC_PRV_EXE   | \
     L3FW_REGION_PERMISSION_SEC_PRV_WRITE | \
     L3FW_REGION_PERMISSION_SEC_PRV_READ  | \
     L3FW_REGION_PERMISSION_SEC_USR_DEBUG | \
     L3FW_REGION_PERMISSION_SEC_PRV_DEBUG | \
     L3FW_REGION_PERMISSION_DOMAIN0_FUNC  | \
     L3FW_REGION_PERMISSION_DOMAIN0_DBG)

/*******************************************************************************
 *  Data structures
 *******************************************************************************
 */
/**
 *******************************************************************************
 *
 *  \brief  Structure containing information on firewalls supported in this
 *          layer.
 *
 *******************************************************************************
*/
typedef struct Utils_l3FwInstSummary_t
{
    char fwName[32];
    /**< Base Address of Firewall instance */
    UInt32 baseAddr;
    /**< Base Address of Firewall instance */
    UInt32 portNum;
    /**< Port Number supported */
    UInt32 memBaseAddr;
    /**< Base address of the protected instance */
} Utils_l3FwInstSummary;

/*******************************************************************************
 *  Global variables
 *******************************************************************************
 */
static volatile UInt32 gInitDone = 0U;

/* Scratch masterList array with maximum size to use in firewall
 * configuration. Always initialize before using this!
 */
static l3fwMasterList_t gTempMasterList[L3FW_NUM_MASTER_MAX];

static BspOsal_IntrHandle gl3FwErrHwiHandle = NULL;
static const Utils_l3FwInstSummary gL3FwInstSummary[] =
{
    {"FW_EMIF1", L3FW_EMIF_INST, EMIF1_FW_PORT_NUM, 0x80000000U},
#if defined(TDA2XX_BUILD) || defined(TDA2EX_BUILD) || defined(TDA2PX_BUILD)
    {"FW_MA_MPU_EMIF1", L3FW_MA_MPU_NTTP_INST, EMIF1_FW_PORT_NUM, 0x80000000U},
#endif
};

#if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
static UInt32 DSP1_DATA_START_ADDR = 0U;
static UInt32 DSP1_DATA_SIZE = 0U;
#ifndef TDA2EX_BUILD
static UInt32 DSP2_DATA_START_ADDR = 0U;
static UInt32 DSP2_DATA_SIZE = 0U;
static UInt32 EVE1_DATA_SIZE = 0U;
static UInt32 EVE1_DATA_START_ADDR = 0U;
#endif
static UInt32 LINK_STATS_START_ADDR = 0U;
static UInt32 LINK_STATS_SIZE = 0U;
#endif

/*******************************************************************************
 *  Function prototypes
 *******************************************************************************
 */
static Void Utils_genDefMasterList(void);
static UInt32 Utils_getFwInstIdx(UInt32 baseAddr);
static Void Utils_l3FwErrISR(UArg ctx);

/*******************************************************************************
 *  Functions
 *******************************************************************************
 */
static Void Utils_genDefMasterList(void)
{
    UInt32 i = 0U;

    for(i = 0U; i < L3FW_NUM_MASTER_MAX; i++)
    {
        gTempMasterList[i].connId     = (i << 2U);
        gTempMasterList[i].permission = L3FW_MRM_RW_PERMISSION_READ_WRITE;
    }
}


static UInt32 Utils_getFwInstIdx(UInt32 baseAddr)
{
    UInt32 idx, numInst;
    numInst = sizeof(gL3FwInstSummary)/sizeof(Utils_l3FwInstSummary);
    for(idx = 0; idx < numInst; idx++)
    {
        if(gL3FwInstSummary[idx].baseAddr == baseAddr)
        {
            break;
        }
    }
    if (idx == numInst)
    {
        UTILS_assert((Bool)FALSE);
    }
    return idx;
}

static Void Utils_l3FwErrISR(UArg ctx)
{
    UInt32 i, numInst;
    Int32  retVal;
    l3fwRegionErrorStatus_t errorLog;
    numInst = sizeof(gL3FwInstSummary)/sizeof(Utils_l3FwInstSummary);

    for(i = 0; i < numInst; i++)
    {
        retVal = FWLIBL3GetErrorLog(gL3FwInstSummary[i].baseAddr,
                                    gL3FwInstSummary[i].portNum,
                                    &errorLog);
        if(SYSTEM_LINK_STATUS_SOK == retVal)
        {
            Vps_printf(" UTILS: L3FW: Firewall violation occured!!!\n");
            Vps_printf(" UTILS: L3FW: Name:                       %s\n",
                       gL3FwInstSummary[i].fwName);
            Vps_printf(" UTILS: L3FW: Location:                   0x%x\n",
                       gL3FwInstSummary[i].memBaseAddr + errorLog.addrOffset);
            Vps_printf(" UTILS: L3FW: ConnId:                     0x%x\n",
                       (errorLog.connIdMSB4bit << 2U));
            Vps_printf(" UTILS: L3FW: Type (0-Data,1-Prog):       0x%x\n",
                       errorLog.mReqType);
            Vps_printf(" UTILS: L3FW: Access (0-Read,1-Write):    0x%x\n",
                       errorLog.accessType);
            Vps_printf(" UTILS: L3FW: Mode (0-User,1-Supervisor): 0x%x\n",
                       errorLog.mReqSupervisor);
            FWLIBL3ClearErrorLog(gL3FwInstSummary[i].baseAddr,
                                 gL3FwInstSummary[i].portNum);
        }
    }
}

/*
 * \brief Setup L3FW error handlers
 *
 * \param  None
 *
 * \return None
 */
void Utils_l3FwSetup(void)
{
    Utils_MemHeapStats       heapStats;
    UInt32                   regionId;
    UInt32                   fwInstIdx;
    Int32                    status;
    l3fwRegionConfigParams_t configParams;
    UInt32                   fwIdx;
    UInt32                   selfProcId = System_getSelfProcId();
    UInt32                   numInst;

    if((NULL == gl3FwErrHwiHandle) &&
       (SYSTEM_IPU_PROC_PRIMARY == selfProcId))
    {
        status = PMHALModuleModeSet(PMHAL_PRCM_MOD_SPINLOCK,
                                    PMHAL_PRCM_MODULE_MODE_ENABLED,
                                    PM_TIMEOUT_INFINITE);

        /* MISRA.CAST.Func.Ptr
         * MISRAC_2004_Rule_11.1
         * MISRAC_WAIVER:
         * Casting it to BspOsal_IntrFuncPtr as required by the OSAL API
         */
        /* Enable interrupt in XBAR and register ISR */
        IntXbar_connectIRQ(L3FW_IPU_INTR_ID, CTRL_MODULE_CORE_IRQ_SEC_EVTS);
        gl3FwErrHwiHandle =
            BspOsal_registerIntr(L3FW_IPU_INTR_ID,
                                 (BspOsal_IntrFuncPtr) &Utils_l3FwErrISR,
                                 NULL);

        numInst = sizeof(gL3FwInstSummary)/sizeof(Utils_l3FwInstSummary);
        /* Define regions with full permissions for all in EMIF
         * and MA-MPU firewalls.
         */
        for(fwIdx = 0; fwIdx < numInst; fwIdx++)
        {
            /* INVARIANT_CONDITION.UNREACH
            * MISRAC_2004_Rule_13.7
            * MISRAC_WAIVER:
            * Code is currently unreachable.
            * This is tool issue . Loop unrecognised .
            */
            if(0U == fwIdx)
            {
                fwInstIdx = Utils_getFwInstIdx(L3FW_EMIF_INST);
            }
            else if(1U == fwIdx)
            {
#if defined(TDA2XX_BUILD) || defined(TDA2EX_BUILD) || defined(TDA2PX_BUILD)
                fwInstIdx = Utils_getFwInstIdx(L3FW_MA_MPU_NTTP_INST);
#else
                /* UNREACH.GEN
                 * MISRAC_2004_Rule_14.1
                 * MISRAC_WAIVER:
                 * Code is currently unreachable.
                 * This is kept to ensure future updates implement this section.
                 */
                UTILS_assert(FALSE);
#endif
            }
            else
            {
                /* UNREACH.GEN
                 * MISRAC_2004_Rule_14.1
                 * MISRAC_WAIVER:
                 * Code is currently unreachable.
                 * This is kept to ensure future updates implement this section.
                 */
                UTILS_assert(FALSE);
            }
            configParams.targetBaseAddr =
                gL3FwInstSummary[fwInstIdx].memBaseAddr;
            for(regionId = 0U; regionId < L3FW_VSDK_REGION_COUNT; regionId++)
            {
                Utils_genDefMasterList();
                configParams.regionId = regionId;

                switch (regionId)
                {
                    case L3FW_VSDK_REGION_BACKGROUND:
                        /* Region 0 - entire EMIF */
                        configParams.regionStartAddr =
                            NULL; /* Don't care for region 0 */
                        configParams.regionEndAddr =
                            NULL; /* Don't care for region 0 */
                        configParams.regionPermission =
                            L3FW_REGION_PERMISSION_MODE_FULL;
                        break;

                    case L3FW_VSDK_REGION_ECC_ASIL:
                        /* Region 1 */
                        Utils_memGetHeapStats(
                            UTILS_HEAPID_DDR_CACHED_SR_ECC_ASIL,
                            &heapStats);
                        configParams.regionPermission =
                            L3FW_REGION_PERMISSION_MODE_FULL;
                        break;
                    case L3FW_VSDK_REGION_ECC_QM:
                        /* Region 1 */
                        Utils_memGetHeapStats(
                            UTILS_HEAPID_DDR_CACHED_SR_ECC_QM,
                            &heapStats);
                        /* 2MB after UTILS_HEAPID_DDR_CACHED_SR_ECC_QM
                         * is reserved for DSP1/DSP2 in .xs file
                         */
                        heapStats.heapSize += (2U*MB);
                        configParams.regionPermission =
                            L3FW_REGION_PERMISSION_MODE_FULL;
                        break;
                    case L3FW_VSDK_REGION_NON_ECC_ASIL:
                        /* Region 3 */
                        Utils_memGetHeapStats(
                            UTILS_HEAPID_DDR_CACHED_SR_NON_ECC_ASIL,
                            &heapStats);
                        configParams.regionPermission =
                            L3FW_REGION_PERMISSION_MODE_FULL;
                        break;
                    #if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
                    case L3FW_VSDK_REGION_IPC_NON_CACHED:
                        /* DSP1 DATA */
                        configParams.regionStartAddr =
                            LINK_STATS_START_ADDR;
                        configParams.regionEndAddr =
                            LINK_STATS_START_ADDR +
                            LINK_STATS_SIZE;
                        /* Allow all writes */
                        configParams.regionPermission =
                            L3FW_REGION_PERMISSION_MODE_FULL;
                        break;
                    case L3FW_VSDK_REGION_DSP1_DATA:
                        /* DSP1 DATA */
                        configParams.regionStartAddr =
                            DSP1_DATA_START_ADDR;
                        configParams.regionEndAddr =
                            DSP1_DATA_START_ADDR +
                            DSP1_DATA_SIZE;
                        /* Block only USR writes */
                        configParams.regionPermission =
                            L3FW_REGION_PERMISSION_MODE_FULL;
                        configParams.regionPermission &=
                            ((UInt32)
                             (~(UInt32)(L3FW_REGION_PERMISSION_PUB_USR_WRITE)));
                        break;
                    #ifndef TDA2EX_BUILD
                    case L3FW_VSDK_REGION_DSP2_DATA:
                        /* DSP2 DATA */
                        configParams.regionStartAddr =
                            DSP2_DATA_START_ADDR;
                        configParams.regionEndAddr =
                            DSP2_DATA_START_ADDR +
                            DSP2_DATA_SIZE;
                        /* Block only USR writes */
                        configParams.regionPermission =
                            L3FW_REGION_PERMISSION_MODE_FULL;
                        configParams.regionPermission &=
                            ((UInt32)
                             (~(UInt32)(L3FW_REGION_PERMISSION_PUB_USR_WRITE)));
                        break;
                    case L3FW_VSDK_REGION_EVE1_DATA:
                        /* EVE DATA */
                        configParams.regionStartAddr =
                            EVE1_DATA_START_ADDR;
                        configParams.regionEndAddr =
                            EVE1_DATA_START_ADDR +
                            EVE1_DATA_SIZE;
                        configParams.regionPermission =
                            L3FW_REGION_PERMISSION_MODE_FULL;
                        break;
                    #endif
                    #endif
                    default:
                        UTILS_assert(FALSE);
                        break;
                }

                if((regionId == L3FW_VSDK_REGION_ECC_ASIL) ||
                   (regionId == L3FW_VSDK_REGION_ECC_QM) ||
                   (regionId == L3FW_VSDK_REGION_NON_ECC_ASIL))
                {
                    Vps_printf(" UTILS: L3FW: 0x%08x - 0x%08x\n",
                               heapStats.heapAddr, heapStats.heapSize);
                    UTILS_assert
                        (0U == (heapStats.heapAddr % L3FW_ADDRESS_ALIGNMENT));
                    UTILS_assert
                        (0U == (heapStats.heapSize % L3FW_ADDRESS_ALIGNMENT));
                    configParams.targetBaseAddr =
                        gL3FwInstSummary[fwInstIdx].memBaseAddr;
                    configParams.regionStartAddr =
                        heapStats.heapAddr;
                    configParams.regionEndAddr =
                        heapStats.heapAddr +
                        heapStats.heapSize;
                }

                /* Configure L3FW module */
                status = FWLIBL3ConfigRegion(
                    gL3FwInstSummary[fwInstIdx].baseAddr,
                    &configParams,
                    L3FW_NUM_MASTER_MAX,
                    (const l3fwMasterList_t *)gTempMasterList);
                UTILS_assert(0 == status);

                status = FWLIBL3RegionEnable(
                    gL3FwInstSummary[fwInstIdx].baseAddr,
                    configParams.regionId,
                    gL3FwInstSummary[fwInstIdx].portNum);
                UTILS_assert(0 == status);
            }
        }
        gInitDone = 1U;
    }
    else
    {
        gInitDone = 1U;
    }
}

/*
 * \brief Unregister L3FW error handlers
 *
 * \param  None
 *
 * \return None
 */
void Utils_l3FwReset(void)
{
    UInt32 i;
    UInt32 numInst = sizeof(gL3FwInstSummary)/sizeof(Utils_l3FwInstSummary);
    UInt32 selfProcId = System_getSelfProcId();

    if(SYSTEM_IPU_PROC_PRIMARY == selfProcId)
    {
        for(i = 0; i < numInst; i++)
        {
            L3FWResetAllRegions(gL3FwInstSummary[i].baseAddr);
        }
        IntXbar_disconnectIRQ(L3FW_IPU_INTR_ID);
        if(NULL != gl3FwErrHwiHandle)
        {
            BspOsal_unRegisterIntr(&gl3FwErrHwiHandle);
            gl3FwErrHwiHandle = NULL;
        }
    }
    gInitDone = 0U;
}

/*
 * \brief  Switch background region to READ-ONLY or READ-WRITE for EVE
 *
 * \param  safetyMode - BSP_SAFETY_OSAL_MODE_ASIL/BSP_SAFETY_OSAL_MODE_QM
 *
 * \return None
 */
void Utils_l3FwSwitchSafetyMode(UInt32 safetyMode)
{
#ifdef TDA3XX_BUILD
/* Firewall permission switching is allowed only on TDA3XX_BUILD.
 * TDA2X ES1.x/ES2.0, TDA2EX ES1.x can lock up if firewall permissions
 * are changed at run-time
 */
#if defined(BUILD_DSP_1) || defined(BUILD_DSP_2) || defined(BUILD_ARP32_1)
    UInt32 fwIdx;
    UInt32 numInst = sizeof(gL3FwInstSummary)/sizeof(Utils_l3FwInstSummary);
    UInt32 perms;
    UInt32 fwInstIdx;

    if(1U == gInitDone)
    {
        Utils_acquireSpinLock(UTILS_SPINLOCK_BASE_UTILS_L3FW,
                              UTILS_SPINLOCK_ID_UTILS_L3FW,
                              FALSE);
    }


    for(fwIdx = 0; fwIdx < numInst; fwIdx++)
    {
        if(1U != gInitDone)
        {
            /* Skip all configuration */
            break;
        }
        /* INVARIANT_CONDITION.UNREACH
        * MISRAC_2004_Rule_13.7
        * MISRAC_WAIVER:
        * Code is currently unreachable.
        * This is tool issue . Loop unrecognised .
        */
        if(0U == fwIdx)
        {
            fwInstIdx = Utils_getFwInstIdx(L3FW_EMIF_INST);
        }
        else if(1U == fwIdx)
        {
#if defined(TDA2XX_BUILD) || defined(TDA2EX_BUILD) || defined(TDA2PX_BUILD)
            fwInstIdx = Utils_getFwInstIdx(L3FW_MA_MPU_NTTP_INST);
#else
            /* UNREACH.GEN
             * MISRAC_2004_Rule_14.1
             * MISRAC_WAIVER:
             * Code is currently unreachable.
             * This is kept to ensure future updates implement this section.
             */
            UTILS_assert(FALSE);
#endif
        }
        else
        {
            /* UNREACH.GEN
             * MISRAC_2004_Rule_14.1
             * MISRAC_WAIVER:
             * Code is currently unreachable.
             * This is kept to ensure future updates implement this section.
             */
            UTILS_assert(FALSE);
        }

        if(BSP_SAFETY_OSAL_MODE_ASIL == safetyMode)
        {
            perms = L3FW_MRM_RW_PERMISSION_READ_WRITE;
        }
        else /* BSP_SAFETY_OSAL_MODE_QM == safetyMode */
        {
            perms = L3FW_MRM_RW_PERMISSION_READ_ONLY;
        }

#ifdef BUILD_DSP_1
        L3FWSetRegionMRMPermission(
            gL3FwInstSummary[fwInstIdx].baseAddr, /* baseAddr   */
            L3FW_VSDK_REGION_BACKGROUND,          /* regionId   */
            SOC_CONNID_DSP1_DMA,                  /* connId     */
            perms);                               /* accessType */
        L3FWSetRegionMRMPermission(
            gL3FwInstSummary[fwInstIdx].baseAddr, /* baseAddr   */
            L3FW_VSDK_REGION_ECC_ASIL,            /* regionId   */
            SOC_CONNID_DSP1_DMA,                  /* connId     */
            perms);                               /* accessType */
        L3FWSetRegionMRMPermission(
            gL3FwInstSummary[fwInstIdx].baseAddr, /* baseAddr   */
            L3FW_VSDK_REGION_NON_ECC_ASIL,        /* regionId   */
            SOC_CONNID_DSP1_DMA,                  /* connId     */
            perms);                               /* accessType */
#endif /* BUILD_DSP_1 */

#ifndef TDA2EX_BUILD
#ifdef BUILD_DSP_2
        L3FWSetRegionMRMPermission(
            gL3FwInstSummary[fwInstIdx].baseAddr, /* baseAddr   */
            L3FW_VSDK_REGION_BACKGROUND,          /* regionId   */
            SOC_CONNID_DSP2_DMA,                  /* connId     */
            perms);                               /* accessType */
        L3FWSetRegionMRMPermission(
            gL3FwInstSummary[fwInstIdx].baseAddr, /* baseAddr   */
            L3FW_VSDK_REGION_ECC_ASIL,            /* regionId   */
            SOC_CONNID_DSP2_DMA,                  /* connId     */
            perms);                               /* accessType */
        L3FWSetRegionMRMPermission(
            gL3FwInstSummary[fwInstIdx].baseAddr, /* baseAddr   */
            L3FW_VSDK_REGION_NON_ECC_ASIL,        /* regionId   */
            SOC_CONNID_DSP2_DMA,                  /* connId     */
            perms);                               /* accessType */
#endif /* BUILD_DSP_2 */

#ifdef BUILD_ARP32_1
        /* Permissions for Region 0/1/3 will only change.
         * Region 2 always has full permissions
         */
        L3FWSetRegionMRMPermission(
            gL3FwInstSummary[fwInstIdx].baseAddr, /* baseAddr   */
            L3FW_VSDK_REGION_BACKGROUND,          /* regionId   */
            SOC_CONNID_EVE1_MMU0,                 /* connId     */
            perms);                               /* accessType */
        L3FWSetRegionMRMPermission(
            gL3FwInstSummary[fwInstIdx].baseAddr, /* baseAddr   */
            L3FW_VSDK_REGION_ECC_ASIL,            /* regionId   */
            SOC_CONNID_EVE1_MMU0,                 /* connId     */
            perms);                               /* accessType */
        L3FWSetRegionMRMPermission(
            gL3FwInstSummary[fwInstIdx].baseAddr, /* baseAddr   */
            L3FW_VSDK_REGION_NON_ECC_ASIL,        /* regionId   */
            SOC_CONNID_EVE1_MMU0,                 /* connId     */
            perms);                               /* accessType */
#endif /* BUILD_ARP32_1 */
#endif /* TDA2EX_BUILD */
    }

    if(1U == gInitDone)
    {
        Utils_freeSpinLock(UTILS_SPINLOCK_BASE_UTILS_L3FW,
                           UTILS_SPINLOCK_ID_UTILS_L3FW);
    }
#endif /* (BUILD_DSP_1) || (BUILD_DSP_2) || (BUILD_ARP32_1) */
#endif /* TDA3XX_BUILD */
}

#ifdef BUILD_ARP32
UInt32 Utils_l3FwGetSafetyMode(Void)
{
    UInt32 fwMode, safetyMode;

    L3FWGetRegionMRMPermission(
        L3FW_EMIF_INST, 0U, SOC_CONNID_EVE1_MMU0, &fwMode);

    if(L3FW_MRM_RW_PERMISSION_READ_WRITE == fwMode)
    {
        safetyMode = BSP_SAFETY_OSAL_MODE_ASIL;
    }
    else
    {
        safetyMode = BSP_SAFETY_OSAL_MODE_QM;
    }

    return safetyMode;
}
#endif

#if ((defined(BUILD_M4_0) && defined(IPU_PRIMARY_CORE_IPU1)) || (defined(BUILD_M4_2) && defined(IPU_PRIMARY_CORE_IPU2)))
void Utils_l3FwSetDsp1DataSectInfo(UInt32 addr, UInt32 size)
{
    DSP1_DATA_START_ADDR = addr;
    DSP1_DATA_SIZE = size;
}

#ifndef TDA2EX_BUILD
void Utils_l3FwSetDsp2DataSectInfo(UInt32 addr, UInt32 size)
{
    DSP2_DATA_START_ADDR = addr;
    DSP2_DATA_SIZE = size;
}

void Utils_l3FwSetEve1DataSectInfo(UInt32 addr, UInt32 size)
{
    EVE1_DATA_START_ADDR = addr;
    EVE1_DATA_SIZE = size;
}
#endif /* TDA2EX_BUILD */

void Utils_l3FwSetLinkStatSectInfo(UInt32 addr, UInt32 size)
{
    LINK_STATS_START_ADDR = addr;
    LINK_STATS_SIZE = size;
}
#endif /* BUILD_M4_0 */
