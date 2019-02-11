/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/**
 * \file hw_pmhal_vmdata.c
 *
 * \brief   Voltage Domain Information specific to the SoC.
 *
 *          The Voltage Domain structures are populated with data specific to
 *          TDA2xx
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include "pm_types.h"
#include "pm_utils.h"
#include "pmhal_pmic.h"
#include "pmhal_vm.h"
#include "hw_pmhal_vmdata.h"
#include "hw_pmhal_data.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Enum to index into the gPmhalVmOpp array.
 */
typedef enum pmhalVmVoltOppIndex
{
    PMHAL_VM_INDEX_MIN = 0U,
    /**< Min Index for gPmhalVmOpp array */
    PMHAL_VM_INDEX_MPU_LOW = PMHAL_VM_INDEX_MIN,
    /**< VDD_MPU, OPP_LOW Index */
    PMHAL_VM_INDEX_MPU_NOM = 1U,
    /**< VDD_MPU, OPP_NOM Index */
    PMHAL_VM_INDEX_MPU_OD = 2U,
    /**< VDD_MPU, OPP_OD Index */
    PMHAL_VM_INDEX_MPU_HIGH = 3U,
    /**< VDD_MPU, OPP_HIGH Index */
    PMHAL_VM_INDEX_CORE_NOM = 4U,
    /**< VDD_CORE, OPP_NOM Index */
    PMHAL_VM_INDEX_IVA_NOM = 5U,
    /**< VDD_IVA, OPP_NOM Index */
    PMHAL_VM_INDEX_IVA_OD = 6U,
    /**< VDD_IVA, OPP_OD Index */
    PMHAL_VM_INDEX_IVA_HIGH = 7U,
    /**< VDD_IVA, OPP_HIGH Index */
    PMHAL_VM_INDEX_DSPEVE_NOM = 8U,
    /**< VDD_DSPEVE, OPP_NOM Index */
    PMHAL_VM_INDEX_DSPEVE_OD = 9U,
    /**< VDD_DSPEVE, OPP_OD Index */
    PMHAL_VM_INDEX_DSPEVE_HIGH = 10U,
    /**< VDD_DSPEVE, OPP_HIGH Index */
    PMHAL_VM_INDEX_GPU_NOM = 11U,
    /**< VDD_GPU, OPP_NOM Index */
    PMHAL_VM_INDEX_GPU_OD = 12U,
    /**< VDD_IVA, OPP_OD Index */
    PMHAL_VM_INDEX_GPU_HIGH = 13U,
    /**< VDD_GPU, OPP_HIGH Index */
    PMHAL_VM_INDEX_RTC_NOM = 14U,
    /**< VDD_RTC, OPP_NOM Index */
#if defined (SOC_TDA2EX)
    PMHAL_VM_INDEX_IVA_PLUS = 15U,
    /**< VDD_IVA, OPP_PLUS Index */
    PMHAL_VM_INDEX_DSPEVE_PLUS = 16U,
    /**< VDD_DSPEVE, OPP_PLUS Index */
    PMHAL_VM_INDEX_MAX = PMHAL_VM_INDEX_DSPEVE_PLUS,
    /**< Max Index for gPmhalVmOpp array */
#else
    PMHAL_VM_INDEX_MAX = PMHAL_VM_INDEX_RTC_NOM,
    /**< Max Index for gPmhalVmOpp array */
#endif
    PMHAL_VM_INDEX_COUNT = PMHAL_VM_INDEX_MAX + 1U
                           /**< Count of Indices for gPmhalVmOpp array */
} pmhalVmVoltOppIndex_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/**
 *  \brief Array defining CPU Id list of PMHAL_PRCM_VD_MPU
 */
pmhalPrcmCpuId_t PMHAL_PRCM_VD_MPU_cpuIdList[] =
{
    PMHAL_PRCM_CPU_ID_MPU
};
/**
 *  \brief Array defining CPU Id list of PMHAL_PRCM_VD_CORE
 */
pmhalPrcmCpuId_t PMHAL_PRCM_VD_CORE_cpuIdList[] =
{
    PMHAL_PRCM_CPU_ID_IPU
};
/**
 *  \brief Array defining CPU Id list of PMHAL_PRCM_VD_IVAHD
 */
pmhalPrcmCpuId_t PMHAL_PRCM_VD_IVAHD_cpuIdList[] =
{
    PMHAL_PRCM_CPU_ID_IVAHD
};
/**
 *  \brief Array defining CPU Id list of PMHAL_PRCM_VD_DSPEVE
 */
pmhalPrcmCpuId_t PMHAL_PRCM_VD_DSPEVE_cpuIdList[] =
{
    PMHAL_PRCM_CPU_ID_DSP,
#if defined (SOC_TDA2XX) || defined (SOC_AM572x) || defined (SOC_DRA75x)
    PMHAL_PRCM_CPU_ID_EVE
#endif
};
/**
 *  \brief Array defining CPU Id list of PMHAL_PRCM_VD_GPU
 */
pmhalPrcmCpuId_t PMHAL_PRCM_VD_GPU_cpuIdList[] =
{
    PMHAL_PRCM_CPU_ID_GPU
};
/**
 *  \brief Array defining CPU Id list of PMHAL_PRCM_VD_RTC
 */
pmhalPrcmCpuId_t PMHAL_PRCM_VD_RTC_cpuIdList[] =
{
    PMHAL_PRCM_CPU_ID_UNDEF
};
/*
 *  OPP Voltage Table for TDA2xx devices.
 *
 *     +------------+-----------------+----------------+-----------------+
 *     | Voltage    |     OPP_NOM     |     OPP_OD     |    OPP_HIGH     |
 *     | Domain     |   Min/Nom/Max   |   Min/Nom/Max  |   Min/Nom/Max   |
 *     +------------+-----------------+----------------+-----------------+
 *     | VD_MPU     |                 |                |                 |
 *       AVS Not En | 1.11/1.15/1.2   |      NA        |        NA       |
 *     | AVS En     |  AVS-/ AVS/1.2  | AVS-/AVS /AVS+ |  AVS-/AVS /AVS+ |
 *     |            |  3.5%           | 3.5%       5%  |  3.5%       5%  |
 *     +------------+-----------------+----------------+-----------------+
 *     | VD_CORE    |                 |                |                 |
 *     | AVS Not En | 1.11/1.15/1.2   |      NA        |        NA       |
 *     | AVS En     |  AVS / AVS/1.2  |      NA        |        NA       |
 *     +------------+-----------------+----------------+-----------------+
 *     | VD_IVA     |                 |                |                 |
 *       AVS Not En | 1.023/1.06/1.20 |      NA        |        NA       |
 *     | AVS En     |  AVS-/ AVS/1.20 | AVS-/AVS /AVS+ |  AVS-/AVS /AVS+ |
 *     |            |  3.5%           | 3.5%       5%  |  3.5%       5%  |
 *     +------------+-----------------+----------------+-----------------+
 *     | VD_DSPEVE  |                 |                |                 |
 *       AVS Not En | 1.023/1.06/1.20 |      NA        |        NA       |
 *     | AVS En     |  AVS-/ AVS/1.20 | AVS-/AVS /AVS+ |  AVS-/AVS /AVS+ |
 *     |            |  3.5%           | 3.5%       5%  |  3.5%       5%  |
 *     +------------+-----------------+----------------+-----------------+
 *     | VD_GPU     |                 |                |                 |
 *       AVS Not En | 1.023/1.06/1.2  |      NA        |        NA       |
 *     | AVS En     |  AVS-/ AVS/1.2  | AVS-/AVS /AVS+ |  AVS-/AVS /AVS+ |
 *     |            |  3.5%           | 3.5%       5%  |  3.5%       5%  |
 *     +------------+-----------------+----------------+-----------------+
 *
 */

static const pmhalVmOppVoltage_t
    gPmhalVmOpp[PMHAL_VM_INDEX_COUNT] =
{
    /* VD_MPU voltage domain OPP definitions */
    {
        /* VD_MPU, OPP Low Voltage Initialization, OPP_LOW is supported only
         * for 17x17 package */
        {0U,    1060U},
        SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_1,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU_2,
        PRM_IRQSTATUS_MPU_2_ABB_MPU_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_MPU_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_MPU_CTRL,
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL,
        1,
        1
    },
    {
        /* VD_MPU, OPP NOM voltage Initialization : AVS & ABB Supported */
        {1150U, 1150U},
        SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_2,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU_2,
        PRM_IRQSTATUS_MPU_2_ABB_MPU_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_MPU_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_MPU_CTRL,
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_MPU, OPP OD voltage Initialization : AVS & ABB Supported */
        {1150U, 1150U},
        SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_3,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU_2,
        PRM_IRQSTATUS_MPU_2_ABB_MPU_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_MPU_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_MPU_CTRL,
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_MPU, OPP High Voltage Initialization */
        {1250U, 1250U},
        SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_STD_FUSE_OPP_VMIN_MPU_4,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU_2,
        PRM_IRQSTATUS_MPU_2_ABB_MPU_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_MPU_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_MPU_CTRL,
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_LDOVBB_MPU_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /*
         * VD_CORE, OPP NOM Voltage Initialization : AVS Supported,
         * ABB is not supported.
         */
        {1150U, 1150U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_2,
        0U,
        0U,
        0U,
        0U,
        0U,
        1U,
        0U
    },
    {
        /* VD_IVAHD OPP NOM Voltage Initialization  : AVS & ABB Supported */
        {1060U, 1060U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_2,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_IVA_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_IVA_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_IVA_CTRL,
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_IVAHD OPP OD Voltage Initialization  : AVS & ABB Supported */
        {1150U, 1150U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_3,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_IVA_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_IVA_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_IVA_CTRL,
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_IVAHD OPP High Voltage Initialization : AVS & ABB Supported */
        {1250U, 1250U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_4,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_IVA_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_IVA_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_IVA_CTRL,
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_DSPEVE OPP NOM Voltage Initialization : AVS & ABB Supported */
        {1060U, 1060U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_2,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_DSPEVE_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_DSPEVE_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_DSPEVE_CTRL,
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_DSPEVE OPP OD Voltage Initialization : AVS & ABB Supported */
        {1150U, 1150U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_3,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_DSPEVE_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_DSPEVE_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_DSPEVE_CTRL,
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /*
         * VD_DSPEVE OPP High Voltage Initialization :
         * AVS & ABB Supported
         */
        {1250U, 1250U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_4,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_DSPEVE_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_DSPEVE_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_DSPEVE_CTRL,
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_GPU OPP NOM Voltage Initialization : AVS & ABB Supported */
        {1060U, 1060U},
        SOC_SEC_EFUSE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_2,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_GPU_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_GPU_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_GPU_CTRL,
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_GPU OPP OD Voltage Initialization : AVS & ABB Supported */
        {1150U, 1150U},
        SOC_SEC_EFUSE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_3,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_GPU_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_GPU_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_GPU_CTRL,
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_GPU OPP High Voltage Initialization : AVS & ABB Supported */
        {1250U, 1250U},
        SOC_SEC_EFUSE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_GPU_4,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_GPU_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_GPU_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_GPU_CTRL,
        SOC_CTRL_MODULE_WKUP_CORE_REGISTERS_BASE +
        CTRL_WKUP_LDOVBB_GPU_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_RTC OPP NOM Voltage Initialization : ABB and AVS are not
         * supported. DM mentions the range of NOM voltages is 880Uto 1030mv
         * The higher value is populated in this table.
         */
        {1030U, 1030U},
        0U,
        0U,
        0U,
        0U,
        0U,
        0U,
        0U,
        0U
    },
#if defined (SOC_TDA2EX)
    {
        /* VD_IVAHD OPP High Voltage Initialization : AVS & ABB Supported */
        {1250U, 1250U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_5,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_IVA_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_IVA_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_IVA_CTRL,
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL,
        1U,
        1U
    },
    {
        /* VD_DSPEVE OPP NOM Voltage Initialization : AVS & ABB Supported */
        {1250U, 1250U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_5,
        SOC_OCP_SOCKET_PRM_BASE + PRM_IRQSTATUS_MPU,
        PRM_IRQSTATUS_MPU_ABB_DSPEVE_DONE_ST_MASK,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_DSPEVE_SETUP,
        SOC_DEVICE_PRM_BASE + PRM_ABBLDO_DSPEVE_CTRL,
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL,
        1U,
        1U
    }
#endif
};

#if defined (SOC_TDA2EX)
const pmhalVmVoltageDomain_t gPmhalVmDomains[PMHAL_PRCM_VD_COUNT] =
{
    /*
     * minSafemV, maxSafemV, minOppNommV, maxOppNommV,
     * sldoSetupAddr,
     * sldoCtrlAddr,
     * sLdoValidRetMode,
     * {OppVoltage-Low,
     * OppVoltage-nom,
     * OppVoltage-OD,
     * OppVoltage-High,
     * OppVoltage-plus},
     * cpuIdArr,
     * numCpus
     */
    /* VD_MPU */
    {850U,                                    1250U,
      1023U, 1200U,
      SOC_DEVICE_PRM_BASE + PRM_SLDO_MPU_SETUP,
      SOC_DEVICE_PRM_BASE + PRM_SLDO_MPU_CTRL,
      (uint8_t) (((uint32_t) 1U <<
                  (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_NO_RET) |
                 ((uint32_t) 1U <<
                 (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_RET)),
      {&gPmhalVmOpp[PMHAL_VM_INDEX_MPU_LOW],
      &gPmhalVmOpp[PMHAL_VM_INDEX_MPU_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_MPU_OD],
      &gPmhalVmOpp[PMHAL_VM_INDEX_MPU_HIGH],
      &gPmhalVmOpp[PMHAL_VM_INDEX_MPU_HIGH]},
      {PMHAL_VM_OPP_LOW, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_OD, PMHAL_VM_OPP_HIGH,
      PMHAL_VM_INDEX_MPU_HIGH},
      PMHAL_PRCM_VD_MPU_cpuIdList,
      PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_MPU_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_CORE */
    {850U, 1250U, 990U, 1200U,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_CORE_SETUP,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_CORE_CTRL,
     (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_RET),
     {&gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM]},
     {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM,
     PMHAL_VM_OPP_NOM},
     PMHAL_PRCM_VD_CORE_cpuIdList,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_CORE_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_IVA */
    {850U, 1250U, 1023U, 1200U,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_IVA_SETUP,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_IVA_CTRL,
     (uint8_t) (((uint32_t) 1U <<
                 (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_NO_RET) |
                ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_RET)),
     {&gPmhalVmOpp[PMHAL_VM_INDEX_IVA_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_IVA_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_IVA_OD],
      &gPmhalVmOpp[PMHAL_VM_INDEX_IVA_HIGH],
      &gPmhalVmOpp[PMHAL_VM_INDEX_IVA_PLUS]},
     {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_OD, PMHAL_VM_OPP_HIGH, PMHAL_VM_OPP_PLUS},
     PMHAL_PRCM_VD_IVAHD_cpuIdList,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_IVAHD_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_DSPEVE */
    {850U, 1250U, 1023U, 1200U,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_DSPEVE_SETUP,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_DSPEVE_CTRL,
     (uint8_t) (((uint32_t) 1U <<
                 (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_NO_RET) |
                ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_RET)),
     {&gPmhalVmOpp[PMHAL_VM_INDEX_DSPEVE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_DSPEVE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_DSPEVE_OD],
      &gPmhalVmOpp[PMHAL_VM_INDEX_DSPEVE_HIGH],
      &gPmhalVmOpp[PMHAL_VM_INDEX_DSPEVE_PLUS]},
     {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_OD, PMHAL_VM_OPP_HIGH, PMHAL_VM_OPP_PLUS},
     PMHAL_PRCM_VD_DSPEVE_cpuIdList,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_DSPEVE_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_GPU */
    {850U, 1250U, 1023U, 1200U,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_GPU_SETUP,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_GPU_CTRL,
     (uint8_t) (((uint32_t) 1U <<
                 (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_NO_RET) |
                ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_RET)),
     {&gPmhalVmOpp[PMHAL_VM_INDEX_GPU_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_GPU_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_GPU_OD],
      &gPmhalVmOpp[PMHAL_VM_INDEX_GPU_HIGH],
      &gPmhalVmOpp[PMHAL_VM_INDEX_GPU_HIGH]},
     {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_OD, PMHAL_VM_OPP_HIGH,
     PMHAL_VM_OPP_HIGH},
     PMHAL_PRCM_VD_GPU_cpuIdList,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_GPU_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_RTC */
    {840U, 1250U, 840U, 1200U,
     PMHAL_REG_NOTAPPLICABLE,
     PMHAL_REG_NOTAPPLICABLE,
     0U,
     {&gPmhalVmOpp[PMHAL_VM_INDEX_RTC_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_RTC_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_RTC_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_RTC_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_RTC_NOM]},
     {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM,
      PMHAL_VM_OPP_NOM},
     PMHAL_PRCM_VD_RTC_cpuIdList,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_RTC_cpuIdList, pmhalPrcmCpuId_t)}
};
#else
const pmhalVmVoltageDomain_t gPmhalVmDomains[PMHAL_PRCM_VD_COUNT] =
{
    /*
     * minSafemV, maxSafemV, minOppNommV, maxOppNommV,
     * sldoSetupAddr,
     * sldoCtrlAddr,
     * sLdoValidRetMode,
     * {OppVoltage-Low,
     * OppVoltage-nom,
     * OppVoltage-OD,
     * OppVoltage-High},
     * cpuIdArr,
     * numCpus
     */
    /* VD_MPU */
    {850U,                                    1250U,
      1023U, 1200U,
      SOC_DEVICE_PRM_BASE + PRM_SLDO_MPU_SETUP,
      SOC_DEVICE_PRM_BASE + PRM_SLDO_MPU_CTRL,
      (uint8_t) (((uint32_t) 1U <<
                  (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_NO_RET) |
                 ((uint32_t) 1U <<
                 (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_RET)),
      {&gPmhalVmOpp[PMHAL_VM_INDEX_MPU_LOW],
      &gPmhalVmOpp[PMHAL_VM_INDEX_MPU_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_MPU_OD],
      &gPmhalVmOpp[PMHAL_VM_INDEX_MPU_HIGH]},
      {PMHAL_VM_OPP_LOW, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_OD, PMHAL_VM_OPP_HIGH},
      PMHAL_PRCM_VD_MPU_cpuIdList,
      PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_MPU_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_CORE */
    {850U, 1250U, 990U, 1200U,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_CORE_SETUP,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_CORE_CTRL,
     (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_RET),
     {&gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM]},
     {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM},
     PMHAL_PRCM_VD_CORE_cpuIdList,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_CORE_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_IVA */
    {850U, 1250U, 1023U, 1200U,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_IVA_SETUP,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_IVA_CTRL,
     (uint8_t) (((uint32_t) 1U <<
                 (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_NO_RET) |
                ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_RET)),
     {&gPmhalVmOpp[PMHAL_VM_INDEX_IVA_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_IVA_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_IVA_OD],
      &gPmhalVmOpp[PMHAL_VM_INDEX_IVA_HIGH]},
     {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_OD, PMHAL_VM_OPP_HIGH},
     PMHAL_PRCM_VD_IVAHD_cpuIdList,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_IVAHD_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_DSPEVE */
    {850U, 1250U, 1023U, 1200U,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_DSPEVE_SETUP,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_DSPEVE_CTRL,
     (uint8_t) (((uint32_t) 1U <<
                 (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_NO_RET) |
                ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_RET)),
     {&gPmhalVmOpp[PMHAL_VM_INDEX_DSPEVE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_DSPEVE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_DSPEVE_OD],
      &gPmhalVmOpp[PMHAL_VM_INDEX_DSPEVE_HIGH]},
     {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_OD, PMHAL_VM_OPP_HIGH},
     PMHAL_PRCM_VD_DSPEVE_cpuIdList,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_DSPEVE_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_GPU */
    {850U, 1250U, 1023U, 1200U,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_GPU_SETUP,
     SOC_DEVICE_PRM_BASE + PRM_SLDO_GPU_CTRL,
     (uint8_t) (((uint32_t) 1U <<
                 (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_NO_RET) |
                ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_RET)),
     {&gPmhalVmOpp[PMHAL_VM_INDEX_GPU_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_GPU_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_GPU_OD],
      &gPmhalVmOpp[PMHAL_VM_INDEX_GPU_HIGH]},
     {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_OD, PMHAL_VM_OPP_HIGH},
     PMHAL_PRCM_VD_GPU_cpuIdList,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_GPU_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_RTC */
    {840U, 1250U, 840U, 1200U,
     PMHAL_REG_NOTAPPLICABLE,
     PMHAL_REG_NOTAPPLICABLE,
     0U,
     {&gPmhalVmOpp[PMHAL_VM_INDEX_RTC_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_RTC_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_RTC_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_RTC_NOM]},
     {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM},
     PMHAL_PRCM_VD_RTC_cpuIdList,
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_RTC_cpuIdList, pmhalPrcmCpuId_t)}
};
#endif
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

const pmhalVmVoltageDomain_t *PmhalVmGetVoltageDomain(uint32_t vId)
{
    const pmhalVmVoltageDomain_t *vd = NULL;
    /* unsigned int need not be compared against minimum value of 0U */
    if (vId >= PMHAL_PRCM_VD_MAX)
    {
        vd = NULL;
    }
    else
    {
        vd = (const pmhalVmVoltageDomain_t *) &gPmhalVmDomains[vId];
    }
    return (const pmhalVmVoltageDomain_t *) vd;
}

const pmhalVmOppVoltage_t *PmhalVmGetOppVoltage(
    const pmhalVmVoltageDomain_t *vd,
    uint32_t                      oppId)
{
    const pmhalVmOppVoltage_t *oppVoltage = NULL;
    /* unsigned int oppId need not be compared against minimum value of 0U */
    if ((oppId >= PMHAL_VM_OPP_MAX) || (vd == NULL))
    {
        oppVoltage = NULL;
    }
    else
    {
        oppVoltage = (const pmhalVmOppVoltage_t *) vd->oppVoltages[oppId];
    }
    return (const pmhalVmOppVoltage_t *) oppVoltage;
}

pmhalPrcmPmicRegulatorId_t PmhalVmGetRegulatorId(pmhalPrcmVdId_t voltDomId)
{
    pmhalPrcmPmicRegulatorId_t regId = PMHAL_PRCM_PMIC_REGULATOR_INVALID;

    switch (voltDomId)
    {
        case PMHAL_PRCM_VD_MPU:
            regId = PMHAL_PRCM_PMIC_REGULATOR_MPU;
            break;

        case PMHAL_PRCM_VD_CORE:
            regId = PMHAL_PRCM_PMIC_REGULATOR_CORE;
            break;

        case PMHAL_PRCM_VD_IVAHD:
            regId = PMHAL_PRCM_PMIC_REGULATOR_IVA;
            break;

        case PMHAL_PRCM_VD_DSPEVE:
            regId = PMHAL_PRCM_PMIC_REGULATOR_DSPEVE;
            break;

        case PMHAL_PRCM_VD_GPU:
            regId = PMHAL_PRCM_PMIC_REGULATOR_GPU;
            break;

        default:
            regId = PMHAL_PRCM_PMIC_REGULATOR_INVALID;
            break;
    }

    return regId;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */

