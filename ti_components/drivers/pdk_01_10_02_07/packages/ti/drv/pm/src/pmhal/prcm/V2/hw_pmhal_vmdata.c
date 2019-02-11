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
 *          TDA3xx
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
    PMHAL_VM_INDEX_CORE_NOM = PMHAL_VM_INDEX_MIN,
    /**< VDD_CORE, OPP_NOM Index */
    PMHAL_VM_INDEX_DSPEVE_NOM = 1U,
    /**< VDD_DSPEVE, OPP_NOM Index */
    PMHAL_VM_INDEX_DSPEVE_OD = 2U,
    /**< VDD_DSPEVE, OPP_OD Index */
    PMHAL_VM_INDEX_DSPEVE_HIGH = 3U,
    /**< VDD_DSPEVE, OPP_HIGH Index */
    PMHAL_VM_INDEX_MAX = PMHAL_VM_INDEX_DSPEVE_HIGH,
    /**< Max Index for gPmhalVmOpp array */
    PMHAL_VM_INDEX_COUNT = PMHAL_VM_INDEX_MAX + 1U
                           /**< Count of Indices for gPmhalVmOpp array */
} pmhalVmVoltOppIndex_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/**
 *  \brief Array defining CPU Id list of PMHAL_PRCM_VD_CORE
 */
pmhalPrcmCpuId_t PMHAL_PRCM_VD_CORE_cpuIdList[] =
{
    PMHAL_PRCM_CPU_ID_IPU
};
/**
 *  \brief Array defining CPU Id list of PMHAL_PRCM_VD_DSPEVE
 */
pmhalPrcmCpuId_t PMHAL_PRCM_VD_DSPEVE_cpuIdList[] =
{
    PMHAL_PRCM_CPU_ID_DSP,
    PMHAL_PRCM_CPU_ID_EVE
};
/*
 *  OPP Voltage Table for TDA2xx devices.
 *
 *     +------------+-----------------+----------------+-----------------+
 *     | Voltage    |     OPP_NOM     |     OPP_OD     |    OPP_HIGH     |
 *     | Domain     |   Min/Nom/Max   |   Min/Nom/Max  |   Min/Nom/Max   |
 *     +------------+-----------------+----------------+-----------------+
 *     | VD_CORE    |                 |                |                 |
 *     | AVS Not En | 0.990/1.03/1.11 |      NA        |        NA       |
 *     | AVS En     |  AVS / AVS/1.11 |      NA        |        NA       |
 *     +------------+-----------------+----------------+-----------------+
 *     | VD_DSPEVE  |                 |                |                 |
 *       AVS Not En | 0.990/1.06/1.11 |      NA        |        NA       |
 *     | AVS En     |  AVS-/ AVS/1.11 |      NA        |        NA       |
 *     |            |  3.5%           |                |                 |
 *     +------------+-----------------+----------------+-----------------+
 *
 */

static const pmhalVmOppVoltage_t gPmhalVmOpp[PMHAL_VM_INDEX_COUNT] =
{
    {
        /*
         * VD_CORE, OPP NOM Voltage Initialization : AVS Supported,
         * ABB is not supported.
         */
        {1030U, 1030U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_2,
        0U,
        0U,
        0U,
        0U,
        0U,
        1U,
        0U
    },
    {
        /* VD_DSPEVE OPP NOM Voltage Initialization : AVS Supported,
         * ABB is not supported.
         */
        {1060U, 1060U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_2,
        0U,
        0U,
        0U,
        0U,
        0U,
        1U,
        0U
    },
    {
        /* VD_DSPEVE OPP OD Voltage Initialization : AVS Supported,
         * ABB is not supported.
         */
        {1150U, 1150U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_3,
        0U,
        0U,
        0U,
        0U,
        0U,
        1U,
        0U
    },
    {
        /*
         * VD_DSPEVE OPP HIGH Voltage Initialization: AVS Supported,
         * ABB is not supported.
         */
        {1250U, 1250U},
        SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_4,
        0U,
        0U,
        0U,
        0U,
        0U,
        1U,
        0U
    }
};

const pmhalVmVoltageDomain_t     gPmhalVmDomains[PMHAL_PRCM_VD_COUNT] =
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
    /* VD_CORE */
    {850U,                                    1250U,
      1020U,
      1170U,
      SOC_DEVICE_PRM_BASE + PRM_SLDO_CORE_SETUP,
      SOC_DEVICE_PRM_BASE + PRM_SLDO_CORE_CTRL,
      (uint8_t) ((uint32_t) 1U <<
                 (uint32_t) PMHAL_PRCM_SRAM_LDO_RET_STATE_NO_RET),
      {&gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM],
      &gPmhalVmOpp[PMHAL_VM_INDEX_CORE_NOM]},
      {PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM, PMHAL_VM_OPP_NOM},
      PMHAL_PRCM_VD_CORE_cpuIdList,
      PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_CORE_cpuIdList, pmhalPrcmCpuId_t)},
    /* VD_DSPEVE */
    {850U, 1250U, 1020U, 1170U,
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
     PM_UTIL_VSIZE_TYPE(PMHAL_PRCM_VD_DSPEVE_cpuIdList, pmhalPrcmCpuId_t)}
};

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
    if (vId >= PMHAL_PRCM_VD_COUNT)
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
        case PMHAL_PRCM_VD_CORE:
            regId = PMHAL_PRCM_PMIC_REGULATOR_CORE;
            break;

        case PMHAL_PRCM_VD_DSPEVE:
            regId = PMHAL_PRCM_PMIC_REGULATOR_DSPEVE;
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

