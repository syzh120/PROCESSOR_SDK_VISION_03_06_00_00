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
 *  \file      hw_pmhal_data.c
 *
 *  \brief     This file contains macros and data-structures pertaining to
 *              StarterWare PMHAL_PRCM implementation.
 *
 *  \warning   This file is auto generated. So avoid manual changes.
 *              If manual changes are required the implications of the
 *              change in this and other auto generated files has to be
 *              completely understood.
 */

/* ========================================================================== */
/*                                Include Files                               */
/* ========================================================================== */

#include "stdint.h"
#if  ((!defined (__cplusplus)) && !(defined (_TMS320C6X)))
#include "stdbool.h"
#endif
#include "stdio.h"
#include "hw_pmhal_data.h"
#include "hw_pmhal_clocktree_data.h"
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                             Macros and Typedefs                            */
/* ========================================================================== */

#define VSIZE_TYPE(vec, type) (sizeof (vec) / sizeof (type))

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                            Structures and Enums                            */
/* ========================================================================== */

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_CAM
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_CAM_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_VIP
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_CORE
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_CORE_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_CORE_OTHER_BANK,
    PMHAL_PRCM_PHY_BANK_OCP_NRET_BANK,
    PMHAL_PRCM_PHY_BANK_CORE_OCMRAM,
    PMHAL_PRCM_PHY_BANK_IPU_L2RAM,
    PMHAL_PRCM_PHY_BANK_IPU_UNICACHE
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_DSP1
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_DSP1_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_DSP1_EDMA,
    PMHAL_PRCM_PHY_BANK_DSP1_L1,
    PMHAL_PRCM_PHY_BANK_DSP1_L2
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_DSP2
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_DSP2_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_DSP2_EDMA,
    PMHAL_PRCM_PHY_BANK_DSP2_L1,
    PMHAL_PRCM_PHY_BANK_DSP2_L2
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_DSS
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_DSS_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_DSS_MEM
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_EMU
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_EMU_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_EMU_BANK
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_EVE1
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_EVE1_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_EVE1_BANK
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_IPU
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_IPU_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_AESSMEM,
    PMHAL_PRCM_PHY_BANK_PERIPHMEM
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_L3INIT
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_L3INIT_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_L3INIT_BANK1,
    PMHAL_PRCM_PHY_BANK_L3INIT_BANK2,
    PMHAL_PRCM_PHY_BANK_GMAC_BANK
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_L4PER
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_L4PER_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_RETAINED_BANK,
    PMHAL_PRCM_PHY_BANK_NONRETAINED_BANK
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_ISS
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_ISS_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_ISS_BANK
};

/**
 *  \brief Structure defining Physical memory List of PMHAL_PRCM_PD_WKUPAON
 */
pmhalPrcmPhyMemBankId_t  PMHAL_PRCM_PD_WKUPAON_phyMemIdList[] =
{
    PMHAL_PRCM_PHY_BANK_WKUP_BANK
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_CAM
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_CAM_resetIdList[] =
{
    PMHAL_PRCM_RG_CAM_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_CORE
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_CORE_resetIdList[] =
{
    PMHAL_PRCM_RG_CM_CORE_PWRON_RET_RST,
    PMHAL_PRCM_RG_CM_CORE_RET_RST,
    PMHAL_PRCM_RG_CORE_PWRON_RET_RST,
    PMHAL_PRCM_RG_CORE_PWRON_RST,
    PMHAL_PRCM_RG_CORE_RET_RST,
    PMHAL_PRCM_RG_CORE_RST,
    PMHAL_PRCM_RG_DLL_RST,
    PMHAL_PRCM_RG_DMA_RET_RST,
    PMHAL_PRCM_RG_IPU2_PWRON_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_COREAON
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_COREAON_resetIdList[] =
{
    PMHAL_PRCM_RG_CM_CORE_AON_PWRON_RST,
    PMHAL_PRCM_RG_CM_CORE_AON_RST,
    PMHAL_PRCM_RG_COREAON_PWRON_RST,
    PMHAL_PRCM_RG_COREAON_RST,
    PMHAL_PRCM_RG_DPLL_IVA_PWRON_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_CUSTEFUSE
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_CUSTEFUSE_resetIdList[] =
{
    PMHAL_PRCM_RG_CUSTEFUSE_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_DSP1
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_DSP1_resetIdList[] =
{
    PMHAL_PRCM_RG_DSP1_RST,
    PMHAL_PRCM_RG_DSP1_PWRON_RST,
    PMHAL_PRCM_RG_DSP1_RET_RST,
    PMHAL_PRCM_RG_DSP1_SYS_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_DSP2
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_DSP2_resetIdList[] =
{
    PMHAL_PRCM_RG_DSP2_RST,
    PMHAL_PRCM_RG_DSP2_PWRON_RST,
    PMHAL_PRCM_RG_DSP2_RET_RST,
    PMHAL_PRCM_RG_DSP2_SYS_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_DSS
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_DSS_resetIdList[] =
{
    PMHAL_PRCM_RG_DSS_RET_RST,
    PMHAL_PRCM_RG_DSS_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_EMU
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_EMU_resetIdList[] =
{
    PMHAL_PRCM_RG_EMU_EARLY_PWRON_RST,
    PMHAL_PRCM_RG_EMU_PWRON_RST,
    PMHAL_PRCM_RG_EMU_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_EVE1
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_EVE1_resetIdList[] =
{
    PMHAL_PRCM_RG_EVE1_CPU_RST,
    PMHAL_PRCM_RG_EVE1_PWRON_RST,
    PMHAL_PRCM_RG_EVE1_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_IPU
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_IPU_resetIdList[] =
{
    PMHAL_PRCM_RG_IPU1_PWRON_RST,
    PMHAL_PRCM_RG_IPU1_RST,
    PMHAL_PRCM_RG_IPU1_RET_RST,
    PMHAL_PRCM_RG_IPU_RST,
    PMHAL_PRCM_RG_IPU_RET_RST,
    PMHAL_PRCM_RG_IPU1_CPU0_RST,
    PMHAL_PRCM_RG_IPU1_CPU1_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_L3INIT
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_L3INIT_resetIdList[] =
{
    PMHAL_PRCM_RG_L3INIT_PWRON_RST,
    PMHAL_PRCM_RG_L3INIT_RET_RST,
    PMHAL_PRCM_RG_L3INIT_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_L4PER
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_L4PER_resetIdList[] =
{
    PMHAL_PRCM_RG_L4PER_PWRON_RET_RST,
    PMHAL_PRCM_RG_L4PER_RET_RST,
    PMHAL_PRCM_RG_L4PER_RST,
    PMHAL_PRCM_RG_PRUSS1_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_ISS
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_ISS_resetIdList[] =
{
    PMHAL_PRCM_RG_VPE_RST
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_WKUPAON
 */
pmhalPrcmResetGroupId_t  PMHAL_PRCM_PD_WKUPAON_resetIdList[] =
{
    PMHAL_PRCM_RG_WKUPAON_PWRON_RST,
    PMHAL_PRCM_RG_WKUPAON_RST,
    PMHAL_PRCM_RG_WKUPAON_SYS_PWRON_RST,
    PMHAL_PRCM_RG_PRM_PWRON_RST,
    PMHAL_PRCM_RG_PRM_RST,
    PMHAL_PRCM_RG_LPRM_PWRON_RST,
    PMHAL_PRCM_RG_LPRM_RST
};

/**
 *  \brief structure defining Clock Domain List of PMHAL_PRCM_PD_CAM
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_CAM_clockDomainList[] =
{
    PMHAL_PRCM_CD_CAM
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_CORE
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_CORE_clockDomainList[] =
{
    PMHAL_PRCM_CD_CRC,
    PMHAL_PRCM_CD_EMIF,
    PMHAL_PRCM_CD_L3INSTR,
    PMHAL_PRCM_CD_L3MAIN1,
    PMHAL_PRCM_CD_L4CFG
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_COREAON
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_COREAON_clockDomainList[] =
{
    PMHAL_PRCM_CD_COREAON
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_CUSTEFUSE
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_CUSTEFUSE_clockDomainList[] =
{
    PMHAL_PRCM_CD_CUSTEFUSE
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_DSP1
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_DSP1_clockDomainList[] =
{
    PMHAL_PRCM_CD_DSP1
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_DSP2
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_DSP2_clockDomainList[] =
{
    PMHAL_PRCM_CD_DSP2
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_DSS
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_DSS_clockDomainList[] =
{
    PMHAL_PRCM_CD_DSS
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_EMU
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_EMU_clockDomainList[] =
{
    PMHAL_PRCM_CD_EMU
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_EVE1
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_EVE1_clockDomainList[] =
{
    PMHAL_PRCM_CD_EVE1
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_IPU
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_IPU_clockDomainList[] =
{
    PMHAL_PRCM_CD_IPU1,
    PMHAL_PRCM_CD_IPU
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_L3INIT
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_L3INIT_clockDomainList[] =
{
    PMHAL_PRCM_CD_GMAC,
    PMHAL_PRCM_CD_L3INIT
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_L4PER
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_L4PER_clockDomainList[] =
{
    PMHAL_PRCM_CD_L4PER2,
    PMHAL_PRCM_CD_L4PER3,
    PMHAL_PRCM_CD_L4PER1
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_ISS
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_ISS_clockDomainList[] =
{
    PMHAL_PRCM_CD_ISS
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_MMAON
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_MMAON_clockDomainList[] =
{
    PMHAL_PRCM_CD_MMAON
};

/**
 *  \brief structure defining Reset Domain List of PMHAL_PRCM_PD_WKUPAON
 */
pmhalPrcmCdId_t          PMHAL_PRCM_PD_WKUPAON_clockDomainList[] =
{
    PMHAL_PRCM_CD_WKUPAON
};

/**
 *  \brief structure defining Power Domain Elements in the device
 */
const pmhalPowerDomain_t pmhalPowerDomainElems[] =
{
    {
        /* PMHAL_PRCM_PD_CAM */
        PMHAL_PRCM_VD_CORE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_OFF) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_STATE_ON_INACTIVE) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE)),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        VSIZE_TYPE(PMHAL_PRCM_PD_CAM_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_CAM_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_CAM_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_CAM_phyMemIdList,
        PMHAL_PRCM_PD_CAM_resetIdList,
        PMHAL_PRCM_PD_CAM_clockDomainList,
        (SOC_CAM_PRM_BASE + PM_CAM_PWRSTCTRL),
        (SOC_CAM_PRM_BASE + PM_CAM_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_CORE */
        PMHAL_PRCM_VD_CORE,
        (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        VSIZE_TYPE(PMHAL_PRCM_PD_CORE_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_CORE_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_CORE_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_CORE_phyMemIdList,
        PMHAL_PRCM_PD_CORE_resetIdList,
        PMHAL_PRCM_PD_CORE_clockDomainList,
        (SOC_CORE_PRM_BASE + PM_CORE_PWRSTCTRL),
        (SOC_CORE_PRM_BASE + PM_CORE_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_COREAON */
        PMHAL_PRCM_VD_CORE,
        PMHAL_VALUE_NOTAPPLICABLE,
        PMHAL_VALUE_NOTAPPLICABLE,
        PMHAL_VALUE_NOTAPPLICABLE,
        0,
        VSIZE_TYPE(PMHAL_PRCM_PD_COREAON_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_COREAON_clockDomainList,
                   pmhalPrcmCdId_t),
        NULL,
        PMHAL_PRCM_PD_COREAON_resetIdList,
        PMHAL_PRCM_PD_COREAON_clockDomainList,
        PMHAL_REG_NOTAPPLICABLE,
        PMHAL_REG_NOTAPPLICABLE
    },
    {
        /* PMHAL_PRCM_PD_CUSTEFUSE */
        PMHAL_PRCM_VD_CORE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_OFF) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_STATE_ON_INACTIVE) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE)),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        0,
        VSIZE_TYPE(PMHAL_PRCM_PD_CUSTEFUSE_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_CUSTEFUSE_clockDomainList,
                   pmhalPrcmCdId_t),
        NULL,
        PMHAL_PRCM_PD_CUSTEFUSE_resetIdList,
        PMHAL_PRCM_PD_CUSTEFUSE_clockDomainList,
        (SOC_CUSTEFUSE_PRM_BASE + PM_CUSTEFUSE_PWRSTCTRL),
        (SOC_CUSTEFUSE_PRM_BASE + PM_CUSTEFUSE_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_DSP1 */
        PMHAL_PRCM_VD_DSPEVE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_OFF) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_STATE_ON_INACTIVE) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE)),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        VSIZE_TYPE(PMHAL_PRCM_PD_DSP1_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_DSP1_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_DSP1_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_DSP1_phyMemIdList,
        PMHAL_PRCM_PD_DSP1_resetIdList,
        PMHAL_PRCM_PD_DSP1_clockDomainList,
        (SOC_DSP1_PRM_BASE + PM_DSP1_PWRSTCTRL),
        (SOC_DSP1_PRM_BASE + PM_DSP1_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_DSP2 */
        PMHAL_PRCM_VD_DSPEVE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_OFF) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_STATE_ON_INACTIVE) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE)),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        0,
        VSIZE_TYPE(PMHAL_PRCM_PD_DSP2_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_DSP2_clockDomainList,
                   pmhalPrcmCdId_t),
        NULL,
        PMHAL_PRCM_PD_DSP2_resetIdList,
        PMHAL_PRCM_PD_DSP2_clockDomainList,
        (SOC_DSP2_PRM_BASE + PM_DSP2_PWRSTCTRL),
        (SOC_DSP2_PRM_BASE + PM_DSP2_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_DSS */
        PMHAL_PRCM_VD_CORE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_OFF) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_STATE_ON_INACTIVE) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE)),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        VSIZE_TYPE(PMHAL_PRCM_PD_DSS_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_DSS_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_DSS_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_DSS_phyMemIdList,
        PMHAL_PRCM_PD_DSS_resetIdList,
        PMHAL_PRCM_PD_DSS_clockDomainList,
        (SOC_DSS_PRM_BASE + PM_DSS_PWRSTCTRL),
        (SOC_DSS_PRM_BASE + PM_DSS_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_EMU */
        PMHAL_PRCM_VD_CORE,
        (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_OFF),
        PMHAL_VALUE_NOTAPPLICABLE,
        PMHAL_VALUE_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_PD_EMU_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_EMU_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_EMU_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_EMU_phyMemIdList,
        PMHAL_PRCM_PD_EMU_resetIdList,
        PMHAL_PRCM_PD_EMU_clockDomainList,
        (SOC_EMU_PRM_BASE + PM_EMU_PWRSTCTRL),
        (SOC_EMU_PRM_BASE + PM_EMU_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_EVE1 */
        PMHAL_PRCM_VD_DSPEVE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_OFF) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_STATE_ON_INACTIVE) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE)),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        VSIZE_TYPE(PMHAL_PRCM_PD_EVE1_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_EVE1_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_EVE1_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_EVE1_phyMemIdList,
        PMHAL_PRCM_PD_EVE1_resetIdList,
        PMHAL_PRCM_PD_EVE1_clockDomainList,
        (SOC_EVE1_PRM_BASE + PM_EVE1_PWRSTCTRL),
        (SOC_EVE1_PRM_BASE + PM_EVE1_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_IPU */
        PMHAL_PRCM_VD_CORE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_OFF) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_STATE_ON_INACTIVE) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE)),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        VSIZE_TYPE(PMHAL_PRCM_PD_IPU_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_IPU_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_IPU_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_IPU_phyMemIdList,
        PMHAL_PRCM_PD_IPU_resetIdList,
        PMHAL_PRCM_PD_IPU_clockDomainList,
        (SOC_IPU_PRM_BASE + PM_IPU_PWRSTCTRL),
        (SOC_IPU_PRM_BASE + PM_IPU_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_L3INIT */
        PMHAL_PRCM_VD_CORE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_OFF) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_STATE_ON_INACTIVE) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE)),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        VSIZE_TYPE(PMHAL_PRCM_PD_L3INIT_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_L3INIT_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_L3INIT_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_L3INIT_phyMemIdList,
        PMHAL_PRCM_PD_L3INIT_resetIdList,
        PMHAL_PRCM_PD_L3INIT_clockDomainList,
        (SOC_L3INIT_PRM_BASE + PM_L3INIT_PWRSTCTRL),
        (SOC_L3INIT_PRM_BASE + PM_L3INIT_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_L4PER */
        PMHAL_PRCM_VD_CORE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_STATE_ON_INACTIVE) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE)),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        VSIZE_TYPE(PMHAL_PRCM_PD_L4PER_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_L4PER_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_L4PER_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_L4PER_phyMemIdList,
        PMHAL_PRCM_PD_L4PER_resetIdList,
        PMHAL_PRCM_PD_L4PER_clockDomainList,
        (SOC_L4PER_PRM_BASE + PM_L4PER_PWRSTCTRL),
        (SOC_L4PER_PRM_BASE + PM_L4PER_PWRSTST)
    },
    {
        /* PMHAL_PRCM_PD_ISS */
        PMHAL_PRCM_VD_CORE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_OFF) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_STATE_ON_INACTIVE) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_STATE_ON_ACTIVE)),
        PMHAL_VALUE_NOTAPPLICABLE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_PD_LOW_PWR_NO_REQUEST) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_PD_LOW_PWR_REQUEST)),
        VSIZE_TYPE(PMHAL_PRCM_PD_ISS_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_ISS_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_ISS_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_ISS_phyMemIdList,
        PMHAL_PRCM_PD_ISS_resetIdList,
        PMHAL_PRCM_PD_ISS_clockDomainList,
        (SOC_VPE_PRM_BASE + PM_ISS_PWRSTCTRL),
        (SOC_VPE_PRM_BASE + PM_ISS_PWRSTST)
    },
    {   /* PMHAL_PRCM_PD_MMAON */
        PMHAL_PRCM_VD_DSPEVE,
        PMHAL_VALUE_NOTAPPLICABLE,
        PMHAL_VALUE_NOTAPPLICABLE,
        PMHAL_VALUE_NOTAPPLICABLE,
        0,
        0,
        VSIZE_TYPE(PMHAL_PRCM_PD_MMAON_clockDomainList,
                   pmhalPrcmCdId_t),
        NULL,
        NULL,
        PMHAL_PRCM_PD_MMAON_clockDomainList,
        PMHAL_REG_NOTAPPLICABLE,
        PMHAL_REG_NOTAPPLICABLE
    },
    {
        /* PMHAL_PRCM_PD_WKUPAON */
        PMHAL_PRCM_VD_CORE,
        PMHAL_VALUE_NOTAPPLICABLE,
        PMHAL_VALUE_NOTAPPLICABLE,
        PMHAL_VALUE_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_PD_WKUPAON_phyMemIdList,
                   pmhalPrcmPhyMemBankId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_WKUPAON_resetIdList,
                   pmhalPrcmResetGroupId_t),
        VSIZE_TYPE(PMHAL_PRCM_PD_WKUPAON_clockDomainList,
                   pmhalPrcmCdId_t),
        PMHAL_PRCM_PD_WKUPAON_phyMemIdList,
        PMHAL_PRCM_PD_WKUPAON_resetIdList,
        PMHAL_PRCM_PD_WKUPAON_clockDomainList,
        PMHAL_REG_NOTAPPLICABLE,
        PMHAL_REG_NOTAPPLICABLE
    }
};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_M2 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_M2_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_M2_DPLL_CORE),
 CM_DIV_M2_DPLL_CORE_DIVHS_MASK,
 CM_DIV_M2_DPLL_CORE_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_M3 divider.
 *         this is a re-purposed register of DSP DPLL used to configure CORE
 *         M3.
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_M3_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_M3_DPLL_EVE_VID_DSP),
 CM_DIV_M3_DPLL_EVE_VID_DSP_DIVHS_MASK,
 CM_DIV_M3_DPLL_EVE_VID_DSP_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H11 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H11_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H11_DPLL_CORE),
 CM_DIV_H11_DPLL_CORE_DIVHS_MASK,
 CM_DIV_H11_DPLL_CORE_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H12 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H12_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H12_DPLL_CORE),
 CM_DIV_H12_DPLL_CORE_DIVHS_MASK,
 CM_DIV_H12_DPLL_CORE_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H13 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H13_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H13_DPLL_CORE),
 CM_DIV_H13_DPLL_CORE_DIVHS_MASK,
 CM_DIV_H13_DPLL_CORE_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H14 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H14_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H14_DPLL_CORE),
 CM_DIV_H14_DPLL_CORE_DIVHS_MASK,
 CM_DIV_H14_DPLL_CORE_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H21 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H21_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H21_DPLL_CORE),
 CM_DIV_H22_DPLL_CORE_DIVHS_MASK,
 CM_DIV_H22_DPLL_CORE_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H22 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H22_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H22_DPLL_CORE),
 CM_DIV_H22_DPLL_CORE_DIVHS_MASK,
 CM_DIV_H22_DPLL_CORE_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H23 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H23_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H23_DPLL_CORE),
 CM_DIV_H23_DPLL_CORE_DIVHS_MASK,
 CM_DIV_H23_DPLL_CORE_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H24 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H24_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H24_DPLL_CORE),
 CM_DIV_H24_DPLL_CORE_DIVHS_MASK,
 CM_DIV_H24_DPLL_CORE_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_PER_M2 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_PER_M2_regBitField =
{(SOC_CKGEN_CM_CORE_BASE + CM_DIV_M2_DPLL_PER),
 CM_DIV_M2_DPLL_PER_DIVHS_MASK,
 CM_DIV_M2_DPLL_PER_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_PER_M3 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_PER_M3_regBitField =
{(SOC_CKGEN_CM_CORE_BASE + CM_DIV_M3_DPLL_PER),
 CM_DIV_M3_DPLL_PER_DIVHS_MASK,
 CM_DIV_M3_DPLL_PER_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_PER_H11 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_PER_H11_regBitField =
{(SOC_CKGEN_CM_CORE_BASE + CM_DIV_H11_DPLL_PER),
 CM_DIV_H11_DPLL_PER_DIVHS_MASK,
 CM_DIV_H11_DPLL_PER_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_PER_H12 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_PER_H12_regBitField =
{(SOC_CKGEN_CM_CORE_BASE + CM_DIV_H12_DPLL_PER),
 CM_DIV_H12_DPLL_PER_DIVHS_MASK,
 CM_DIV_H12_DPLL_PER_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_PER_H13 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_PER_H13_regBitField =
{(SOC_CKGEN_CM_CORE_BASE + CM_DIV_H13_DPLL_PER),
 CM_DIV_H13_DPLL_PER_DIVHS_MASK,
 CM_DIV_H13_DPLL_PER_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_PER_H14 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_PER_H14_regBitField =
{(SOC_CKGEN_CM_CORE_BASE + CM_DIV_H14_DPLL_PER),
 CM_DIV_H14_DPLL_PER_DIVHS_MASK,
 CM_DIV_H14_DPLL_PER_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DSP_GMAC_M2 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_DSP_GMAC_M2_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_M2_DPLL_DSP_GMAC),
 CM_DIV_M2_DPLL_DSP_GMAC_DIVHS_MASK,
 CM_DIV_M2_DPLL_DSP_GMAC_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DSP_GMAC_M3 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_DSP_GMAC_M3_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_M3_DPLL_DSP_GMAC),
 CM_DIV_M3_DPLL_DSP_GMAC_DIVHS_MASK,
 CM_DIV_M3_DPLL_DSP_GMAC_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DSP_GMAC_H11 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_DSP_GMAC_H11_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H11_DPLL_DSP_GMAC),
 CM_DIV_H11_DPLL_DSP_GMAC_DIVHS_MASK,
 CM_DIV_H11_DPLL_DSP_GMAC_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DSP_GMAC_H12 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_DSP_GMAC_H12_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H12_DPLL_DSP_GMAC),
 CM_DIV_H12_DPLL_DSP_GMAC_DIVHS_MASK,
 CM_DIV_H12_DPLL_DSP_GMAC_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DSP_GMAC_H13 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_DSP_GMAC_H13_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H13_DPLL_DSP_GMAC),
 CM_DIV_H13_DPLL_DSP_GMAC_DIVHS_MASK,
 CM_DIV_H13_DPLL_DSP_GMAC_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DSP_GMAC_H13 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_DSP_GMAC_H14_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H13_DPLL_DSP_GMAC),
 CM_DIV_H13_DPLL_DSP_GMAC_DIVHS_MASK,
 CM_DIV_H13_DPLL_DSP_GMAC_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DDR_M2 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_DDR_M2_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_M2_DPLL_DDR),
 CM_DIV_M2_DPLL_DDR_DIVHS_MASK,
 CM_DIV_M2_DPLL_DDR_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DDR_H11 divider
 */
regBitField_t      PMHAL_PRCM_DPLL_DDR_H11_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H11_DPLL_DDR),
 CM_DIV_H11_DPLL_DDR_DIVHS_MASK,
 CM_DIV_H11_DPLL_DDR_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DDR_H12 divider
 *         this is a re-purposed register of ABE DPLL used to configure
 *         DDR_H12
 */
regBitField_t      PMHAL_PRCM_DPLL_DDR_H12_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_H12_DPLL_DDR),
 CM_DIV_H12_DPLL_DDR_DIVHS_MASK,
 CM_DIV_H12_DPLL_DDR_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_EVE_VID_DSP_M2
 *         divider
 */
regBitField_t      PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_M2_DPLL_EVE_VID_DSP),
 CM_DIV_M2_DPLL_EVE_VID_DSP_DIVHS_MASK,
 CM_DIV_M2_DPLL_EVE_VID_DSP_DIVHS_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_EVE_VID_DSP_M3
 *         divider
 */
regBitField_t      PMHAL_PRCM_DPLL_EVE_VID_DSP_M3_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_DIV_M2_DPLL_EVE_VID_DSP),
 CM_DIV_M2_DPLL_EVE_VID_DSP_DIVHS_MASK,
 CM_DIV_M2_DPLL_EVE_VID_DSP_DIVHS_SHIFT};

/**
 *  \brief Structure defining PMHAL_PRCM_DPLL_CORE divider configuration
 */
pmhalDpllPostDiv_t PMHAL_PRCM_DPLL_CORE_postdividers[] =
{
    {   /* PMHAL_PRCM_DPLL_CORE_M2 */
        PMHAL_PRCM_DPLL_POST_DIV_M2,
        &PMHAL_PRCM_DPLL_CORE_M2_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_CORE_M3 */
        PMHAL_PRCM_DPLL_POST_DIV_M3,
        &PMHAL_PRCM_DPLL_CORE_M3_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H11 */
        PMHAL_PRCM_DPLL_POST_DIV_H11,
        &PMHAL_PRCM_DPLL_CORE_H11_regBitField,
        PMHAL_CTRL_POSTDIV_DPLL_CORE_H11
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H12 */
        PMHAL_PRCM_DPLL_POST_DIV_H12,
        &PMHAL_PRCM_DPLL_CORE_H12_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H13 */
        PMHAL_PRCM_DPLL_POST_DIV_H13,
        &PMHAL_PRCM_DPLL_CORE_H13_regBitField,
        PMHAL_CTRL_POSTDIV_DPLL_CORE_H13
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H14 */
        PMHAL_PRCM_DPLL_POST_DIV_H14,
        &PMHAL_PRCM_DPLL_CORE_H14_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H21 */
        PMHAL_PRCM_DPLL_POST_DIV_H21,
        &PMHAL_PRCM_DPLL_CORE_H21_regBitField,
        PMHAL_CTRL_POSTDIV_DPLL_CORE_H21
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H22 */
        PMHAL_PRCM_DPLL_POST_DIV_H22,
        &PMHAL_PRCM_DPLL_CORE_H22_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H23 */
        PMHAL_PRCM_DPLL_POST_DIV_H23,
        &PMHAL_PRCM_DPLL_CORE_H23_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H24 */
        PMHAL_PRCM_DPLL_POST_DIV_H24,
        &PMHAL_PRCM_DPLL_CORE_H24_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    }
};

/**
 *  \brief Structure defining PMHAL_PRCM_DPLL_PER divider configuration
 */
pmhalDpllPostDiv_t PMHAL_PRCM_DPLL_PER_postdividers[] =
{
    {   /* PMHAL_PRCM_DPLL_PER_M2 */
        PMHAL_PRCM_DPLL_POST_DIV_M2,
        &PMHAL_PRCM_DPLL_PER_M2_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_PER_M2X2 */
        PMHAL_PRCM_DPLL_POST_DIV_M2X2,
        &PMHAL_PRCM_DPLL_PER_M2_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_PER_M3 */
        PMHAL_PRCM_DPLL_POST_DIV_M3,
        &PMHAL_PRCM_DPLL_PER_M3_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_PER_H11 */
        PMHAL_PRCM_DPLL_POST_DIV_H11,
        &PMHAL_PRCM_DPLL_PER_H11_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_PER_H12 */
        PMHAL_PRCM_DPLL_POST_DIV_H12,
        &PMHAL_PRCM_DPLL_PER_H12_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_PER_H13 */
        PMHAL_PRCM_DPLL_POST_DIV_H13,
        &PMHAL_PRCM_DPLL_PER_H13_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_PER_H14 */
        PMHAL_PRCM_DPLL_POST_DIV_H14,
        &PMHAL_PRCM_DPLL_PER_H14_regBitField,
        PMHAL_CTRL_POSTDIV_DPLL_PER_H14
    }
};

/**
 *  \brief Structure defining PMHAL_PRCM_DPLL_DSP_GMAC divider configuration
 */
pmhalDpllPostDiv_t PMHAL_PRCM_DPLL_DSP_GMAC_postdividers[] =
{
    {   /* PMHAL_PRCM_DPLL_DSP_GMAC_M2 */
        PMHAL_PRCM_DPLL_POST_DIV_M2,
        &PMHAL_PRCM_DPLL_DSP_GMAC_M2_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_DSP_GMAC_M3 */
        PMHAL_PRCM_DPLL_POST_DIV_M3,
        &PMHAL_PRCM_DPLL_DSP_GMAC_M3_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_DSP_GMAC_H11 */
        PMHAL_PRCM_DPLL_POST_DIV_H11,
        &PMHAL_PRCM_DPLL_DSP_GMAC_H11_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_DSP_GMAC_H12 */
        PMHAL_PRCM_DPLL_POST_DIV_H12,
        &PMHAL_PRCM_DPLL_DSP_GMAC_H12_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_DSP_GMAC_H13 */
        PMHAL_PRCM_DPLL_POST_DIV_H13,
        &PMHAL_PRCM_DPLL_DSP_GMAC_H13_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_DSP_GMAC_H14 */
        PMHAL_PRCM_DPLL_POST_DIV_H14,
        &PMHAL_PRCM_DPLL_DSP_GMAC_H14_regBitField,
        PMHAL_CTRL_POSTDIV_DPLL_DSP_GMAC_H14
    }
};

/**
 *  \brief Structure defining PMHAL_PRCM_DPLL_DDR divider configuration
 */
pmhalDpllPostDiv_t PMHAL_PRCM_DPLL_DDR_postdividers[] =
{
    {   /* PMHAL_PRCM_DPLL_DDR_M2 */
        PMHAL_PRCM_DPLL_POST_DIV_M2,
        &PMHAL_PRCM_DPLL_DDR_M2_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_DDR_H11 */
        PMHAL_PRCM_DPLL_POST_DIV_H11,
        &PMHAL_PRCM_DPLL_DDR_H11_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_DDR_H12 */
        PMHAL_PRCM_DPLL_POST_DIV_H12,
        &PMHAL_PRCM_DPLL_DDR_H12_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    }
};

/**
 *  \brief Structure defining PMHAL_PRCM_DPLL_EVE_VID_DSP divider configuration
 */
pmhalDpllPostDiv_t PMHAL_PRCM_DPLL_EVE_VID_DSP_postdividers[] =
{
    {   /* PMHAL_PRCM_DPLL_EVE_VID_DSP_M2 */
        PMHAL_PRCM_DPLL_POST_DIV_M2,
        &PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_regBitField,
        PMHAL_CTRL_POSTDIV_DPLL_EVE_VID_DSP_M2
    },
    {   /* PMHAL_PRCM_DPLL_EVE_VID_DSP_M2X2 */
        PMHAL_PRCM_DPLL_POST_DIV_M2X2,
        &PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_regBitField,
        PMHAL_CTRL_POSTDIV_DPLL_EVE_VID_DSP_M2
    },
    {   /* PMHAL_PRCM_DPLL_EVE_VID_DSP_M3 */
        PMHAL_PRCM_DPLL_POST_DIV_M3,
        &PMHAL_PRCM_DPLL_EVE_VID_DSP_M3_regBitField,
        PMHAL_CTRL_POSTDIV_NOTAPPLICABLE
    }
};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H1_muxselect
 *         register configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H1_muxselect =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_DBG_ATB_CLK_TENABLEDIV_SEL_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_DBG_ATB_CLK_TENABLEDIV_SEL_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H2_muxselect
 *         register configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H2_muxselect =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_TENABLEDIV_SEL_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_TENABLEDIV_SEL_SHIFT};

/**
 *  \brief Structure defining registers for
 *         PMHAL_PRCM_DPLL_DSP_GMAC_H14_muxselect register configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_DSP_GMAC_H14_muxselect =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_SMA_SW_17),
 CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_TENABLEDIV_SEL_MASK,
 CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_TENABLEDIV_SEL_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H11 T-Enable
 *         register configuration
 */
regBitFieldShift_t PMHAL_PRCM_DPLL_CORE_H11_TEnableregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_TENABLEDIV_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H11 control
 *         module over-ridden divider configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H11_HsValregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_DIV_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_ATB_CLK_DIV_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H11 control
 *         module over-ridden divider configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H11_HsDivEnableregBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H13 T-Enable
 *         register configuration
 */
regBitFieldShift_t PMHAL_PRCM_DPLL_CORE_H13_TEnableregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_LATCH_EN_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H13 control
 *         module over-ridden divider configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H13_HsValregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H13 control
 *         module over-ridden divider configuration for enabling divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H13_HsDivEnableregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_EN_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_HSDIV_EN_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H21 T-Enable
 *         register configuration
 */
regBitFieldShift_t PMHAL_PRCM_DPLL_CORE_H21_TEnableregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_TENABLEDIV_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DSP_GMAC_H14
 *         T-Enable register configuration
 */
regBitFieldShift_t PMHAL_PRCM_DPLL_DSP_GMAC_H14_TEnableregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_SMA_SW_17),
 CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_LATCH_EN_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H21 control
 *         module over-ridden divider configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H21_HsValregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_DIV_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_STM_EXPT_CLK_DIV_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DSP_GMAC_H14
 *         control module over-ridden divider configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_DSP_GMAC_H14_HsValregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_SMA_SW_17),
 CTRL_CORE_SEC_SMA_SW_17_MCAN_CLKHSDIV_MASK,
 CTRL_CORE_SEC_SMA_SW_17_MCAN_CLKHSDIV_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_CORE_H21 control
 *         module over-ridden divider configuration to enable divider
 */
regBitField_t      PMHAL_PRCM_DPLL_CORE_H21_HsDivEnableregBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_DSP_GMAC_H14
 *         control module over-ridden divider configuration to enable divider
 */
regBitField_t
    PMHAL_PRCM_DPLL_DSP_GMAC_H14_HsDivEnableregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_SMA_SW_17),
 CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_EN_MASK,
 CTRL_CORE_SEC_SMA_SW_17_MCAN_CLK_HSDIV_EN_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_PER_H1_muxselect
 *         register configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_PER_H1_muxselect =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_TENABLEDIV_SEL_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_TENABLEDIV_SEL_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_PER_H14 T-Enable
 *         register configuration
 */
regBitFieldShift_t PMHAL_PRCM_DPLL_PER_H14_TEnableregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_TENABLEDIV_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_PER_H14 control
 *         module over-ridden divider configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_PER_H14_HsValregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_DIV_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL1_DBG_TRC_EXPT_CLK_DIV_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_PER_H14 control
 *         module over-ridden divider configuration to enable divider
 */
regBitField_t      PMHAL_PRCM_DPLL_PER_H14_HsDivEnableregBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_EVE_VID_DSP_M2
 *         muxselect register configuration
 */
regBitField_t      PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_muxselect =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_TENABLEDIV_SEL_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_TENABLEDIV_SEL_SHIFT};

/**
 *  \brief Structure defining registers for PMHAL_PRCM_DPLL_EVE_VID_DSP_M2
 *         T-Enable register configuration
 */
regBitFieldShift_t
    PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_TEnableregBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_LATCH_EN_SHIFT};

/**
 *  \brief  Structure defining registers for PMHAL_PRCM_DPLL_EVE_VID_DSP_M2
 *          control module over-ridden divider configuration.
 */
regBitField_t      PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_HsValregBitField
    =
    {(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2),
     CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_MASK,
     CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_SHIFT};

/**
 *  \brief  Structure defining registers for PMHAL_PRCM_DPLL_EVE_VID_DSP_M2
 *          control module over-ridden divider configuration to enable divider.
 */
regBitField_t
    PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_HsDivEnableregBitField
    =
    {(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2),
     CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_EN_MASK,
     CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_EN_SHIFT};

/**
 *  \brief Structure defining DPLL Post Dividers controlled by control module
 */
const pmhalDpllCtrlMdlHsDiv_t pmhalCtrlModuleDpllDividerElems[] =
{
    {   /* PMHAL_PRCM_DPLL_EVE_VID_DSP_M2 */
        PMHAL_PRCM_DPLL_POST_DIV_M2,
        &PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_TEnableregBitField,
        &PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_HsValregBitField,
        &PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_HsDivEnableregBitField,
        &PMHAL_PRCM_DPLL_EVE_VID_DSP_M2_muxselect,
        PMHAL_CTRLMDL_POSTDIV_MUXSEL0_VAL,
        0U
    },
    {   /* PMHAL_PRCM_DPLL_PER_H14 */
        PMHAL_PRCM_DPLL_POST_DIV_H14,
        &PMHAL_PRCM_DPLL_PER_H14_TEnableregBitField,
        &PMHAL_PRCM_DPLL_PER_H14_HsValregBitField,
        &PMHAL_PRCM_DPLL_PER_H14_HsDivEnableregBitField,
        &PMHAL_PRCM_DPLL_PER_H1_muxselect,
        PMHAL_CTRLMDL_POSTDIV_MUXSEL1_VAL,
        1U
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H11 */
        PMHAL_PRCM_DPLL_POST_DIV_H11,
        &PMHAL_PRCM_DPLL_CORE_H11_TEnableregBitField,
        &PMHAL_PRCM_DPLL_CORE_H11_HsValregBitField,
        &PMHAL_PRCM_DPLL_CORE_H11_HsDivEnableregBitField,
        &PMHAL_PRCM_DPLL_CORE_H1_muxselect,
        PMHAL_CTRLMDL_POSTDIV_MUXSEL2_VAL,
        1U
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H13 */
        PMHAL_PRCM_DPLL_POST_DIV_H13,
        &PMHAL_PRCM_DPLL_CORE_H13_TEnableregBitField,
        &PMHAL_PRCM_DPLL_CORE_H13_HsValregBitField,
        &PMHAL_PRCM_DPLL_CORE_H13_HsDivEnableregBitField,
        &PMHAL_PRCM_DPLL_CORE_H1_muxselect,
        PMHAL_CTRLMDL_POSTDIV_MUXSEL3_VAL,
        1U
    },
    {   /* PMHAL_PRCM_DPLL_CORE_H21 */
        PMHAL_PRCM_DPLL_POST_DIV_H21,
        &PMHAL_PRCM_DPLL_CORE_H21_TEnableregBitField,
        &PMHAL_PRCM_DPLL_CORE_H21_HsValregBitField,
        &PMHAL_PRCM_DPLL_CORE_H21_HsDivEnableregBitField,
        &PMHAL_PRCM_DPLL_CORE_H2_muxselect,
        PMHAL_CTRLMDL_POSTDIV_MUXSEL4_VAL,
        1U
    },
    {   /* PMHAL_PRCM_DPLL_DSP_GMAC_H14 */
        PMHAL_PRCM_DPLL_POST_DIV_H14,
        &PMHAL_PRCM_DPLL_DSP_GMAC_H14_TEnableregBitField,
        &PMHAL_PRCM_DPLL_DSP_GMAC_H14_HsValregBitField,
        &PMHAL_PRCM_DPLL_DSP_GMAC_H14_HsDivEnableregBitField,
        &PMHAL_PRCM_DPLL_DSP_GMAC_H14_muxselect,
        PMHAL_CTRLMDL_POSTDIV_MUXSEL1_VAL,
        1U
    }
};

/**
 *  \brief Structure defining DPLL Element List
 */
const pmhalDpll_t  pmhalDpllElems[] =
{
    {   /* PMHAL_PRCM_DPLL_CORE */
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_CLKMODE_DPLL_CORE),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_IDLEST_DPLL_CORE),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_AUTOIDLE_DPLL_CORE),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_CLKSEL_DPLL_CORE),
        PMHAL_REG_NOTAPPLICABLE,
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_SSC_DELTAMSTEP_DPLL_CORE),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_SSC_MODFREQDIV_DPLL_CORE),
        PMHAL_REG_NOTAPPLICABLE,
        CM_CLKSEL_DPLL_CORE_DPLL_DIV_MASK,
        CM_CLKSEL_DPLL_CORE_DPLL_MULT_MASK,
        CM_AUTOIDLE_DPLL_CORE_AUTO_DPLL_MODE_MASK,
        CM_CLKMODE_DPLL_CORE_DPLL_EN_MASK,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_FR_BYP_MODE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_LOCK_MODE)),
        PMHAL_PRCM_DPLL_TYPE_ADPLLM,
        VSIZE_TYPE(PMHAL_PRCM_DPLL_CORE_postdividers,
                   pmhalDpllPostDiv_t),
        PMHAL_PRCM_DPLL_CORE_postdividers,
        PMHAL_EDGE_DPLL_CORE,
        (SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_SMA_SW_22)
    },
    {   /* PMHAL_PRCM_DPLL_DDR */
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_CLKMODE_DPLL_DDR),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_IDLEST_DPLL_DDR),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_AUTOIDLE_DPLL_DDR),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_CLKSEL_DPLL_DDR),
        PMHAL_REG_NOTAPPLICABLE,
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_SSC_DELTAMSTEP_DPLL_DDR),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_SSC_MODFREQDIV_DPLL_DDR),
        PMHAL_REG_NOTAPPLICABLE,
        CM_CLKSEL_DPLL_DDR_DPLL_DIV_MASK,
        CM_CLKSEL_DPLL_DDR_DPLL_MULT_MASK,
        CM_AUTOIDLE_DPLL_DDR_AUTO_DPLL_MODE_MASK,
        CM_CLKMODE_DPLL_DDR_DPLL_EN_MASK,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_FR_BYP_MODE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_LOCK_MODE)),
        PMHAL_PRCM_DPLL_TYPE_ADPLLM,
        VSIZE_TYPE(PMHAL_PRCM_DPLL_DDR_postdividers,
                   pmhalDpllPostDiv_t),
        PMHAL_PRCM_DPLL_DDR_postdividers,
        PMHAL_EDGE_DPLL_DDR,
        PMHAL_REG_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_DSP_GMAC */
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_CLKMODE_DPLL_DSP_GMAC),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_IDLEST_DPLL_DSP_GMAC),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_AUTOIDLE_DPLL_DSP_GMAC),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_CLKSEL_DPLL_DSP_GMAC),
        PMHAL_REG_NOTAPPLICABLE,
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_SSC_DELTAMSTEP_DPLL_DSP_GMAC),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_SSC_MODFREQDIV_DPLL_DSP_GMAC),
        PMHAL_REG_NOTAPPLICABLE,
        CM_CLKSEL_DPLL_DSP_GMAC_DPLL_DIV_MASK,
        CM_CLKSEL_DPLL_DSP_GMAC_DPLL_MULT_MASK,
        CM_AUTOIDLE_DPLL_DSP_GMAC_AUTO_DPLL_MODE_MASK,
        CM_CLKMODE_DPLL_DSP_GMAC_DPLL_EN_MASK,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_FR_BYP_MODE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_LOCK_MODE)),
        PMHAL_PRCM_DPLL_TYPE_ADPLLM,
        VSIZE_TYPE(PMHAL_PRCM_DPLL_DSP_GMAC_postdividers,
                   pmhalDpllPostDiv_t),
        PMHAL_PRCM_DPLL_DSP_GMAC_postdividers,
        PMHAL_EDGE_DPLL_DSP_GMAC,
        PMHAL_REG_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_PER */
        (SOC_CKGEN_CM_CORE_BASE + CM_CLKMODE_DPLL_PER),
        (SOC_CKGEN_CM_CORE_BASE + CM_IDLEST_DPLL_PER),
        (SOC_CKGEN_CM_CORE_BASE + CM_AUTOIDLE_DPLL_PER),
        (SOC_CKGEN_CM_CORE_BASE + CM_CLKSEL_DPLL_PER),
        PMHAL_REG_NOTAPPLICABLE,
        (SOC_CKGEN_CM_CORE_BASE + CM_SSC_DELTAMSTEP_DPLL_PER),
        (SOC_CKGEN_CM_CORE_BASE + CM_SSC_MODFREQDIV_DPLL_PER),
        PMHAL_REG_NOTAPPLICABLE,
        CM_CLKSEL_DPLL_PER_DPLL_DIV_MASK,
        CM_CLKSEL_DPLL_PER_DPLL_MULT_MASK,
        CM_AUTOIDLE_DPLL_PER_AUTO_DPLL_MODE_MASK,
        CM_CLKMODE_DPLL_PER_DPLL_EN_MASK,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_FR_BYP_MODE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_LOCK_MODE)),
        PMHAL_PRCM_DPLL_TYPE_ADPLLM,
        VSIZE_TYPE(PMHAL_PRCM_DPLL_PER_postdividers,
                   pmhalDpllPostDiv_t),
        PMHAL_PRCM_DPLL_PER_postdividers,
        PMHAL_EDGE_DPLL_PER,
        PMHAL_REG_NOTAPPLICABLE
    },
    {   /* PMHAL_PRCM_DPLL_EVE_VID_DSP */
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_CLKMODE_DPLL_EVE_VID_DSP),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_IDLEST_DPLL_EVE_VID_DSP),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_AUTOIDLE_DPLL_EVE_VID_DSP),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_CLKSEL_DPLL_EVE_VID_DSP),
        PMHAL_REG_NOTAPPLICABLE,
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_SSC_DELTAMSTEP_DPLL_EVE_VID_DSP),
        (SOC_CKGEN_CM_CORE_AON_BASE + CM_SSC_MODFREQDIV_DPLL_EVE_VID_DSP),
        PMHAL_REG_NOTAPPLICABLE,
        CM_CLKSEL_DPLL_EVE_VID_DSP_DPLL_DIV_MASK,
        CM_CLKSEL_DPLL_EVE_VID_DSP_DPLL_MULT_MASK,
        CM_AUTOIDLE_DPLL_EVE_VID_DSP_AUTO_DPLL_MODE_MASK,
        CM_CLKMODE_DPLL_EVE_VID_DSP_DPLL_EN_MASK,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_LP_BYP_MODE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_FR_BYP_MODE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_DPLL_POWER_MODE_LOCK_MODE)),
        PMHAL_PRCM_DPLL_TYPE_ADPLLM,
        VSIZE_TYPE(PMHAL_PRCM_DPLL_EVE_VID_DSP_postdividers,
                   pmhalDpllPostDiv_t),
        PMHAL_PRCM_DPLL_EVE_VID_DSP_postdividers,
        PMHAL_EDGE_DPLL_EVE_VID_DSP,
        PMHAL_REG_NOTAPPLICABLE
    }
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_IPU1_GFCLK_MUX
 */
validEnumValue_t   PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_validEnumValues[]
    =
    {
    {PMHAL_PRCM_DPLL_CORE,
     CM_IPU1_IPU1_CLKCTRL_CLKSEL_SEL_CORE_IPU_ISS_BOOST_CLK},
    {PMHAL_PRCM_DPLL_DDR,
     CM_IPU1_IPU1_CLKCTRL_CLKSEL_SEL_DPLL_ABE_X2_CLK}
    };

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_ADC_MUX
 */
validEnumValue_t   PMHAL_PRCM_MUX_ADC_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_SYS_CLK2},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_SYS_CLK1},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_XREF_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_QSPI_GFCLK_MUX
 */
validEnumValue_t   PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_validEnumValues[]
    =
    {
    {PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX,
     CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE_SEL_FUNC_128M_CLK},
    {PMHAL_PRCM_DPLL_PER,
     CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE_SEL_PER_QSPI_CLK}
    };

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_VIP1_GCLK_MUX
 */
validEnumValue_t   PMHAL_PRCM_MUX_VIP1_GCLK_MUX_validEnumValues[]
    =
    {
    {PMHAL_PRCM_DPLL_CORE,   CM_CAM_VIP1_CLKCTRL_CLKSEL_SEL_CORE_ISS_MAIN_CLK},
    {PMHAL_PRCM_DIV_L3_ICLK, CM_CAM_VIP1_CLKCTRL_CLKSEL_SEL_L3_ICLK          }
    };

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_DIV_SYS_CLK2_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_PER_CLKOUT},
    {PMHAL_PRCM_DIV_L3INIT_480M_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_USB_CLKOUT},
    {PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_CORE_CLKOUT},
    {PMHAL_PRCM_DIV_DSP_GCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_DSP_CLKOUT},
    {PMHAL_PRCM_DIV_EVE_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_EVE_CLKOUT},
    {PMHAL_PRCM_DIV_IVA_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_IVA_CLKOUT},
    {PMHAL_PRCM_DIV_MPU_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_MPU_CLKOUT},
    {PMHAL_PRCM_DIV_EMIF_PHY_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_DDR_CLKOUT},
    {PMHAL_PRCM_DIV_GMAC_250M_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_GMAC_CLKOUT},
    {PMHAL_PRCM_DIV_GPU_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_GPU_CLKOUT},
    {PMHAL_PRCM_DIV_PER_ABE_X1_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_ABE_CLKOUT},
    {PMHAL_PRCM_DIV_SYS_CLK1_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_SYS_CLK1},
    {PMHAL_PRCM_DIV_PCIE2_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_PCIE2_CLKOUT},
    {PMHAL_PRCM_DIV_PCIE_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_PCIE1_CLKOUT},
    {PMHAL_PRCM_DIV_HDMI_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_HDMI_CLKOUT},
    {PMHAL_PRCM_DIV_VIDEO1_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_VIDEO1_CLKOUT},
    {PMHAL_PRCM_DIV_USB_OTG_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_USB_OTG_CLKOUT},
    {PMHAL_PRCM_DIV_VIDEO2_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_VIDEO2_CLKOUT},
    {PMHAL_PRCM_DIV_EMU_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_DEBUG_CLKOUT},
    {PMHAL_PRCM_DIV_SECURE_32K_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_RC_CLK},
    {PMHAL_PRCM_DIV_SATA_DCLK,
     CM_CLKSEL_CLKOUTMUX0_CLKSEL_SEL_DPLL_SATA_CLKOUT}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX_validEnumValues
[]
    =
    {
    {PMHAL_PRCM_DIV_SYS_CLK2_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_PER_CLKOUT},
    {PMHAL_PRCM_DIV_L3INIT_480M_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_USB_CLKOUT},
    {PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_CORE_CLKOUT},
    {PMHAL_PRCM_DIV_DSP_GCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_DSP_CLKOUT},
    {PMHAL_PRCM_DIV_EVE_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_EVE_CLKOUT},
    {PMHAL_PRCM_DIV_IVA_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_IVA_CLKOUT},
    {PMHAL_PRCM_DIV_MPU_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_MPU_CLKOUT},
    {PMHAL_PRCM_DIV_EMIF_PHY_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_DDR_CLKOUT},
    {PMHAL_PRCM_DIV_GMAC_250M_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_GMAC_CLKOUT},
    {PMHAL_PRCM_DIV_GPU_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_GPU_CLKOUT},
    {PMHAL_PRCM_DIV_PER_ABE_X1_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_ABE_CLKOUT},
    {PMHAL_PRCM_DIV_SYS_CLK1_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_SYS_CLK1},
    {PMHAL_PRCM_DIV_PCIE2_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_PCIE2_CLKOUT},
    {PMHAL_PRCM_DIV_PCIE_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_PCIE1_CLKOUT},
    {PMHAL_PRCM_DIV_HDMI_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_HDMI_CLKOUT},
    {PMHAL_PRCM_DIV_VIDEO1_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_VIDEO1_CLKOUT},
    {PMHAL_PRCM_DIV_USB_OTG_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_USB_OTG_CLKOUT},
    {PMHAL_PRCM_DIV_VIDEO2_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_VIDEO2_CLKOUT},
    {PMHAL_PRCM_DIV_EMU_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_DEBUG_CLKOUT},
    {PMHAL_PRCM_DIV_SECURE_32K_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_RC_CLK},
    {PMHAL_PRCM_DIV_SATA_DCLK,
     CM_CLKSEL_CLKOUTMUX1_CLKSEL_SEL_DPLL_SATA_CLKOUT}
    };

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX_validEnumValues
[]
    =
    {
    {PMHAL_PRCM_DIV_SYS_CLK2_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_PER_CLKOUT},
    {PMHAL_PRCM_DIV_L3INIT_480M_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_USB_CLKOUT},
    {PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_CORE_CLKOUT},
    {PMHAL_PRCM_DIV_DSP_GCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_DSP_CLKOUT},
    {PMHAL_PRCM_DIV_EVE_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_EVE_CLKOUT},
    {PMHAL_PRCM_DIV_IVA_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_IVA_CLKOUT},
    {PMHAL_PRCM_DIV_MPU_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_MPU_CLKOUT},
    {PMHAL_PRCM_DIV_EMIF_PHY_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_DDR_CLKOUT},
    {PMHAL_PRCM_DIV_GMAC_250M_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_GMAC_CLKOUT},
    {PMHAL_PRCM_DIV_GPU_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_GPU_CLKOUT},
    {PMHAL_PRCM_DIV_PER_ABE_X1_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_ABE_CLKOUT},
    {PMHAL_PRCM_DIV_SYS_CLK1_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_SYS_CLK1},
    {PMHAL_PRCM_DIV_PCIE2_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_PCIE2_CLKOUT},
    {PMHAL_PRCM_DIV_PCIE_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_PCIE1_CLKOUT},
    {PMHAL_PRCM_DIV_HDMI_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_HDMI_CLKOUT},
    {PMHAL_PRCM_DIV_VIDEO1_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_VIDEO1_CLKOUT},
    {PMHAL_PRCM_DIV_USB_OTG_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_USB_OTG_CLKOUT},
    {PMHAL_PRCM_DIV_VIDEO2_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_VIDEO2_CLKOUT},
    {PMHAL_PRCM_DIV_EMU_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_DEBUG_CLKOUT},
    {PMHAL_PRCM_DIV_SECURE_32K_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_RC_CLK},
    {PMHAL_PRCM_DIV_SATA_DCLK,
     CM_CLKSEL_CLKOUTMUX2_CLKSEL_SEL_DPLL_SATA_CLKOUT}
    };

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX
 */
validEnumValue_t PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_DIV_L3_ICLK,
     CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SEL_L3_ICLK},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SEL_PER_ABE_X1_GFCLK},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CM_GMAC_GMAC_CLKCTRL_CLKSEL_RFT_SEL_HDMI_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_MMC4_GFCLK_MUX
 */
validEnumValue_t PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_validEnumValues[]
    =
    {
    {PMHAL_PRCM_DIV_FUNC_48M_FCLK,
     CM_L4PER_MMC4_CLKCTRL_CLKSEL_MUX_SEL_FUNC_48M_CLK},
    {PMHAL_PRCM_DPLL_PER,
     CM_L4PER_MMC4_CLKCTRL_CLKSEL_MUX_SEL_FUNC_192M_CLK}
    };

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_RMII_50M_CLK_MUX
 */
validEnumValue_t PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_DPLL_DSP_GMAC,
     CM_GMAC_GMAC_CLKCTRL_CLKSEL_REF_SEL_GMAC_RMII_HS_CLK},
    {PMHAL_PRCM_NODE_UNDEF,
     PMHAL_MUX_ENUM_NOTAPPLICABLE}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_DIV_L4_ROOT_CLK,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AUX_CLK_SEL_L4_ICLK},
    {PMHAL_PRCM_DIV_VIDEO2_CLK2,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AUX_CLK_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK2,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AUX_CLK_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK2,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AUX_CLK_SEL_HDMI_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *        PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK2},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK1},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK0},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK3},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_FUNC_24M_CLK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_FUNC_24M_GFCLK},
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_ABE_24M_GFCLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_ABE_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_MLB_CLK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_MLB_CLK},
    {PMHAL_PRCM_DIV_MLBP_CLK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SEL_MLBP_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK2},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK1},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK0},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK3},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_FUNC_24M_CLK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_FUNC_24M_GFCLK},
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_ABE_24M_GFCLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_ABE_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK3},
    {PMHAL_PRCM_DIV_MLB_CLK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_MLB_CLK},
    {PMHAL_PRCM_DIV_MLBP_CLK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SEL_MLBP_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_DIV_L4_ROOT_CLK,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AUX_CLK_SEL_L4_ICLK},
    {PMHAL_PRCM_DIV_VIDEO2_CLK2,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AUX_CLK_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK2,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AUX_CLK_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK2,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AUX_CLK_SEL_HDMI_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *        PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK2},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK1},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK0},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK3},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_FUNC_24M_CLK,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_FUNC_24M_GFCLK},
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_ABE_24M_GFCLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_ABE_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_MLB_CLK,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_MLB_CLK},
    {PMHAL_PRCM_DIV_MLBP_CLK,
     CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_SEL_MLBP_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK2},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK1},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK0},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK3},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_FUNC_24M_CLK,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_FUNC_24M_GFCLK},
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_ABE_24M_GFCLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_ABE_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_MLB_CLK,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_MLB_CLK},
    {PMHAL_PRCM_DIV_MLBP_CLK,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_SEL_MLBP_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_DIV_L4_ROOT_CLK,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AUX_CLK_SEL_L4_ICLK},
    {PMHAL_PRCM_DIV_VIDEO2_CLK2,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AUX_CLK_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK2,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AUX_CLK_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK2,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AUX_CLK_SEL_HDMI_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *        PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK2},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK1},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK0},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_ATL_CLK3},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_FUNC_24M_CLK,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_FUNC_24M_GFCLK},
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_ABE_24M_GFCLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_ABE_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_MLB_CLK,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_MLB_CLK},
    {PMHAL_PRCM_DIV_MLBP_CLK,
     CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_SEL_MLBP_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN2,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK2},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN1,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK1},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN0,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK0},
    {PMHAL_PRCM_ROOT_CLK_ATL_CLKIN3,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_ATL_CLK3},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_FUNC_24M_CLK,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_FUNC_24M_GFCLK},
    {PMHAL_PRCM_DIV_ABE_24M_FCLK,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_ABE_24M_GFCLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_ABE_SYS_CLK,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_ABE_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN2,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_MLB_CLK,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_MLB_CLK},
    {PMHAL_PRCM_DIV_MLBP_CLK,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_SEL_MLBP_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_CLKOUTMUX_CLK},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_ABE_GICLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_TIMER_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_XREF_CLK3},
    {PMHAL_PRCM_DIV_VIDEO2_CLK,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_HDMI_CLK},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CM_IPU_TIMER5_CLKCTRL_CLKSEL_SEL_SYS_CLK1_32K_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_CLKOUTMUX_CLK},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_ABE_GICLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_TIMER_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_XREF_CLK3},
    {PMHAL_PRCM_DIV_VIDEO2_CLK,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_HDMI_CLK},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CM_IPU_TIMER6_CLKCTRL_CLKSEL_SEL_SYS_CLK1_32K_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_CLKOUTMUX_CLK},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_ABE_GICLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_TIMER_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_XREF_CLK3},
    {PMHAL_PRCM_DIV_VIDEO2_CLK,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_HDMI_CLK},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CM_IPU_TIMER7_CLKCTRL_CLKSEL_SEL_SYS_CLK1_32K_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_CLKOUTMUX_CLK},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_ABE_GICLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_TIMER_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_XREF_CLK3},
    {PMHAL_PRCM_DIV_VIDEO2_CLK,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_HDMI_CLK},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CM_IPU_TIMER8_CLKCTRL_CLKSEL_SEL_SYS_CLK1_32K_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_ABE_GICLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_TIMER_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_XREF_CLK3},
    {PMHAL_PRCM_DIV_VIDEO2_CLK,
     CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK,
     CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK,
     CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_HDMI_CLK},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SEL_SYS_CLK1_32K_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_ABE_GICLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_TIMER_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_XREF_CLK3},
    {PMHAL_PRCM_DIV_VIDEO2_CLK,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_HDMI_CLK},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SEL_SYS_CLK1_32K_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_PER_ABE_X1_GFCLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_TIMER_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_XREF_CLK3},
    {PMHAL_PRCM_DIV_VIDEO2_CLK,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_HDMI_CLK},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SEL_SYS_CLK1_32K_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_DIV_ABE_GICLK,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_PER_ABE_X1_GFCLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_XREF_CLK1},
    {PMHAL_PRCM_DIV_TIMER_SYS_CLK,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_TIMER_SYS_CLK},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_XREF_CLK2},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN0,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_XREF_CLK0},
    {PMHAL_PRCM_ROOT_CLK_REF_CLKIN1,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_XREF_CLK3},
    {PMHAL_PRCM_DIV_VIDEO2_CLK,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_VIDEO2_CLK},
    {PMHAL_PRCM_DIV_VIDEO1_CLK,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_VIDEO1_CLK},
    {PMHAL_PRCM_DIV_HDMI_CLK,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_HDMI_CLK},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SEL_SYS_CLK1_32K_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_UART1_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_UART1_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_DIV_FUNC_48M_FCLK,
     CM_L4PER_UART1_CLKCTRL_CLKSEL_SEL_FUNC_48M_CLK},
    {PMHAL_PRCM_DPLL_PER,
     CM_L4PER_UART1_CLKCTRL_CLKSEL_SEL_FUNC_192M_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_UART2_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_UART2_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_DIV_FUNC_48M_FCLK,
     CM_L4PER_UART2_CLKCTRL_CLKSEL_SEL_FUNC_48M_CLK},
    {PMHAL_PRCM_DPLL_PER,
     CM_L4PER_UART2_CLKCTRL_CLKSEL_SEL_FUNC_192M_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_UART3_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_UART3_GFCLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_DIV_FUNC_48M_FCLK,
     CM_L4PER_UART3_CLKCTRL_CLKSEL_SEL_FUNC_48M_CLK},
    {PMHAL_PRCM_DPLL_PER,
     CM_L4PER_UART3_CLKCTRL_CLKSEL_SEL_FUNC_192M_CLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX
 */
validEnumValue_t
    PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CM_WKUPAON_DCAN1_CLKCTRL_CLKSEL_SEL_SYS_CLK2},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CM_WKUPAON_DCAN1_CLKCTRL_CLKSEL_SEL_SYS_CLK1}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1, CM_CLKSEL_WKUPAON_CLKSEL_SEL_SYS_CLK}
};

/**
 *  \brief structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_DSP_GFCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_DSP_GFCLK_MUX_validEnumValues[]
    =
    {
    {PMHAL_PRCM_DPLL_DSP_GMAC,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_DSP0_CLK},
    {PMHAL_PRCM_DPLL_EVE_VID_DSP,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_DSP1_CLK},
    {PMHAL_PRCM_DPLL_CORE,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_DSP2_CLK}
    };

/**
 *  \brief structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_RTI1_CLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_RTI1_CLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_DIV_SYS_CLK1,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_SYS_CLK1},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_XREF_CLK},
    {PMHAL_PRCM_DIV_SYS_CLK2,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_SYS_CLK2}
};

/**
 *  \brief structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_RTI2_CLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_RTI2_CLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_DIV_SYS_CLK1,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_SYS_CLK1},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_XREF_CLK},
    {PMHAL_PRCM_DIV_SYS_CLK2,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_SYS_CLK2}
};

/**
 *  \brief structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_RTI3_CLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_RTI3_CLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_DIV_SYS_CLK1,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_SYS_CLK1},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_XREF_CLK},
    {PMHAL_PRCM_DIV_SYS_CLK2,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_SYS_CLK2}
};

/**
 *  \brief structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_RTI4_CLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_RTI4_CLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_DIV_SYS_CLK1,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_SYS_CLK1},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_XREF_CLK},
    {PMHAL_PRCM_DIV_SYS_CLK2,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_SYS_CLK2}
};

/**
 *  \brief structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_RTI5_CLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_RTI5_CLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_DIV_SYS_CLK1,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_SYS_CLK1},
    {PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_XREF_CLK},
    {PMHAL_PRCM_DIV_SYS_CLK2,
     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_SYS_CLK2}
};

/**
 *  \brief structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_validEnumValues
[] =
{
    {PMHAL_PRCM_DIV_FUNC_32K_CLK,
     PMHAL_VALUE_NOTAPPLICABLE},
    {PMHAL_PRCM_MUX_UNDEF,
     PMHAL_VALUE_NOTAPPLICABLE},
};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_IPU1_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_regBitField =
{(SOC_IPU_CM_CORE_AON_BASE + CM_IPU1_IPU1_CLKCTRL),
 CM_IPU1_IPU1_CLKCTRL_CLKSEL_MASK,
 CM_IPU1_IPU1_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_ADC_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_ADC_MUX_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL),
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_MASK,
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_ADC_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_QSPI_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL),
 CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE_MASK,
 CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_VIP1_GCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_VIP1_GCLK_MUX_regBitField =
{(SOC_CAM_CM_CORE_BASE + CM_CAM_VIP1_CLKCTRL),
 CM_CAM_VIP1_CLKCTRL_CLKSEL_MASK,
 CM_CAM_VIP1_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_CLKOUTMUX0),
 CM_CLKSEL_CLKOUTMUX0_CLKSEL_MASK,
 CM_CLKSEL_CLKOUTMUX0_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_CLKOUTMUX1),
 CM_CLKSEL_CLKOUTMUX1_CLKSEL_MASK,
 CM_CLKSEL_CLKOUTMUX1_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_CLKOUTMUX2),
 CM_CLKSEL_CLKOUTMUX2_CLKSEL_MASK,
 CM_CLKSEL_CLKOUTMUX2_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_regBitField =
{(SOC_L3INIT_CM_CORE_BASE + CM_GMAC_GMAC_CLKCTRL),
 CM_GMAC_GMAC_CLKCTRL_CLKSEL_REF_MASK,
 CM_GMAC_GMAC_CLKCTRL_CLKSEL_REF_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_MMC4_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL),
 CM_L4PER_MMC4_CLKCTRL_CLKSEL_MUX_MASK,
 CM_L4PER_MMC4_CLKCTRL_CLKSEL_MUX_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_RMII_50M_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_regBitField =
{(SOC_L3INIT_CM_CORE_BASE + CM_GMAC_GMAC_CLKCTRL),
 CM_GMAC_GMAC_CLKCTRL_CLKSEL_REF_MASK,
 CM_GMAC_GMAC_CLKCTRL_CLKSEL_REF_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_regBitField
    =
    {(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_MCASP1_CLKCTRL),
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AUX_CLK_MASK,
     CM_IPU_MCASP1_CLKCTRL_CLKSEL_AUX_CLK_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_regBitField =
{(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_MCASP1_CLKCTRL),
 CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_MASK,
 CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKR_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_regBitField =
{(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_MCASP1_CLKCTRL),
 CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_MASK,
 CM_IPU_MCASP1_CLKCTRL_CLKSEL_AHCLKX_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_regBitField
    =
    {(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_MCASP4_CLKCTRL),
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AUX_CLK_MASK,
     CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AUX_CLK_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_MCASP6_CLKCTRL),
 CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_CLK_MASK,
 CM_L4PER2_MCASP6_CLKCTRL_CLKSEL_AHCLKR_CLK_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_MCASP4_CLKCTRL),
 CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_CLK_MASK,
 CM_L4PER2_MCASP4_CLKCTRL_CLKSEL_AHCLKX_CLK_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_regBitField
    =
    {(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_MCASP5_CLKCTRL),
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AUX_CLK_MASK,
     CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AUX_CLK_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_MCASP7_CLKCTRL),
 CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_CLK_MASK,
 CM_L4PER2_MCASP7_CLKCTRL_CLKSEL_AHCLKR_CLK_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_MCASP5_CLKCTRL),
 CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_CLK_MASK,
 CM_L4PER2_MCASP5_CLKCTRL_CLKSEL_AHCLKX_CLK_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_regBitField =
{(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_TIMER5_CLKCTRL),
 CM_IPU_TIMER5_CLKCTRL_CLKSEL_MASK,
 CM_IPU_TIMER5_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_regBitField =
{(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_TIMER6_CLKCTRL),
 CM_IPU_TIMER6_CLKCTRL_CLKSEL_MASK,
 CM_IPU_TIMER6_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_regBitField =
{(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_TIMER7_CLKCTRL),
 CM_IPU_TIMER7_CLKCTRL_CLKSEL_MASK,
 CM_IPU_TIMER7_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_regBitField =
{(SOC_IPU_CM_CORE_AON_BASE + CM_IPU_TIMER8_CLKCTRL),
 CM_IPU_TIMER8_CLKCTRL_CLKSEL_MASK,
 CM_IPU_TIMER8_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_regBitField =
{(SOC_WKUPAON_CM_BASE + CM_WKUPAON_TIMER1_CLKCTRL),
 CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_MASK,
 CM_WKUPAON_TIMER1_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER2_CLKCTRL),
 CM_L4PER_TIMER2_CLKCTRL_CLKSEL_MASK,
 CM_L4PER_TIMER2_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER3_CLKCTRL),
 CM_L4PER_TIMER3_CLKCTRL_CLKSEL_MASK,
 CM_L4PER_TIMER3_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER4_CLKCTRL),
 CM_L4PER_TIMER4_CLKCTRL_CLKSEL_MASK,
 CM_L4PER_TIMER4_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_UART10_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_UART10_GFCLK_MUX_regBitField =
{(SOC_WKUPAON_CM_BASE + CM_WKUPAON_UART10_CLKCTRL),
 CM_WKUPAON_UART10_CLKCTRL_CLKSEL_MASK,
 CM_WKUPAON_UART10_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_UART1_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_UART1_GFCLK_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART1_CLKCTRL),
 CM_L4PER_UART1_CLKCTRL_CLKSEL_MASK,
 CM_L4PER_UART1_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_UART2_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_UART2_GFCLK_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART2_CLKCTRL),
 CM_L4PER_UART2_CLKCTRL_CLKSEL_MASK,
 CM_L4PER_UART2_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_UART3_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_UART3_GFCLK_MUX_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART3_CLKCTRL),
 CM_L4PER_UART3_CLKCTRL_CLKSEL_MASK,
 CM_L4PER_UART3_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_regBitField =
{(SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL),
 CM_WKUPAON_DCAN1_CLKCTRL_CLKSEL_MASK,
 CM_WKUPAON_DCAN1_CLKCTRL_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_WKUPAON),
 CM_CLKSEL_WKUPAON_CLKSEL_MASK,
 CM_CLKSEL_WKUPAON_CLKSEL_SHIFT};

/**
 *  \brief structure defining register structures for
 *         PMHAL_PRCM_MUX_DSP_GFCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_DSP_GFCLK_MUX_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL),
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_MASK,
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_DSP_SHIFT};

/**
 *  \brief structure defining register structures for
 *         PMHAL_PRCM_MUX_RTI1_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_RTI1_CLK_MUX_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL),
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_MASK,
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI1_SHIFT};

/**
 *  \brief structure defining register structures for
 *         PMHAL_PRCM_MUX_RTI2_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_RTI2_CLK_MUX_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL),
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_MASK,
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI2_SHIFT};

/**
 *  \brief structure defining register structures for
 *         PMHAL_PRCM_MUX_RTI3_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_RTI3_CLK_MUX_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL),
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_MASK,
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI3_SHIFT};

/**
 *  \brief structure defining register structures for
 *         PMHAL_PRCM_MUX_RTI4_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_RTI4_CLK_MUX_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL),
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_MASK,
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI4_SHIFT};

/**
 *  \brief structure defining register structures for
 *         PMHAL_PRCM_MUX_RTI5_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_RTI5_CLK_MUX_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL),
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_MASK,
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_RTI5_SHIFT};

/**
 *  \brief structure defining register structures for
 *         PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_regBitField =
{(SOC_CTRL_MODULE_CORE_BASE + CTRL_CORE_BOOTSTRAP),
 CTRL_CORE_BOOTSTRAP_SYSBOOT_9_SYSCLK_SPEED_SELECT_MASK,
 CTRL_CORE_BOOTSTRAP_SYSBOOT_9_SYSCLK_SPEED_SELECT_SHIFT};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_EVE_CLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_EVE_CLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_MUX_EVE_GCLK_MUX, CM_CLKSEL_EVE_CLK_CLKSEL_SEL_EVE_GCLK },
    {PMHAL_PRCM_DPLL_EVE_VID_DSP, CM_CLKSEL_EVE_CLK_CLKSEL_SEL_EVE_GFCLK}
};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_EVE_GCLK_MUX
 */
validEnumValue_t                PMHAL_PRCM_MUX_EVE_GCLK_MUX_validEnumValues[] =
{
    {PMHAL_PRCM_DPLL_DSP_GMAC, CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_EVE_EVE1_GCLK},
    {PMHAL_PRCM_DPLL_CORE,     CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_EVE_EVE2_GCLK}
};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_EVE_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_EVE_CLK_MUX_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_EVE_CLK),
 CM_CLKSEL_EVE_CLK_CLKSEL_MASK,
 CM_CLKSEL_EVE_CLK_CLKSEL_SHIFT};

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_EVE_GCLK_MUX
 */
regBitField_t                   PMHAL_PRCM_MUX_EVE_GCLK_MUX_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL),
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_EVE_MASK,
 CTRL_CORE_SEC_PRCM_CLKSEL_CONTROL_EVE_SHIFT};

/**
 *  \brief Structure defining valid Enumeration values for
 *         PMHAL_PRCM_MUX_DPLL_CORE_CLK
 */
validEnumValue_t                PMHAL_PRCM_MUX_DPLL_CORE_CLK_validEnumValues[]
    =
    {
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN1,
     CTRL_CORE_SEC_SMA_SW_16_CORE_DPLL_INPUT_CLK_SYS_CLK1},
    {PMHAL_PRCM_ROOT_CLK_SYS_CLKIN2,
     CTRL_CORE_SEC_SMA_SW_16_CORE_DPLL_INPUT_CLK_SYS_CLK2}
    };

/**
 *  \brief Structure defining register structures for
 *         PMHAL_PRCM_MUX_DPLL_CORE_CLK
 */
regBitField_t                   PMHAL_PRCM_MUX_DPLL_CORE_CLK_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_SMA_SW_16),
 CTRL_CORE_SEC_SMA_SW_16_CORE_DPLL_INPUT_CLK_SELECTION_MASK,
 CTRL_CORE_SEC_SMA_SW_16_CORE_DPLL_INPUT_CLK_SELECTION_SHIFT};

/**
 *  \brief Structure defining Mux Elements
 */
const pmhalMultiplexer_t        pmhalMultiplexerElems[] =
{
    {   /* PMHAL_PRCM_MUX_IPU1_GFCLK_MUX */
        &PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_IPU1_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_ADC_MUX */
        &PMHAL_PRCM_MUX_ADC_MUX_regBitField,
        PMHAL_PRCM_MUX_ADC_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_ADC_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_EVE_GCLK_MUX */
        &PMHAL_PRCM_MUX_EVE_GCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_EVE_GCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_EVE_GCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_QSPI_GFCLK_MUX */
        &PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_QSPI_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_VIP1_GCLK_MUX */
        &PMHAL_PRCM_MUX_VIP1_GCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_VIP1_GCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_VIP1_GCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX */
        &PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_CLKOUTMUX0_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX */
        &PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_CLKOUTMUX1_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX */
        &PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_CLKOUTMUX2_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX */
        &PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_GMAC_RFT_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_MMC4_GFCLK_MUX */
        &PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_MMC4_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_RMII_50M_CLK_MUX */
        &PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_RMII_50M_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX */
        &PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP1_AUX_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX */
        &PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_regBitField,
        PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP1_AHCLKR_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX */
        &PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_regBitField,
        PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP1_AHCLKX_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX */
        &PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP2_AUX_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX */
        &PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_regBitField,
        PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP2_AHCLKR_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX */
        &PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_regBitField,
        PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP2_AHCLKX_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX */
        &PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP3_AUX_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX */
        &PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_regBitField,
        PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP3_AHCLKR_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX */
        &PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_regBitField,
        PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_MCASP3_AHCLKX_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX */
        &PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER5_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX */
        &PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER6_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX */
        &PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER7_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX */
        &PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER8_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX */
        &PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER1_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX */
        &PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER2_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX */
        &PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER3_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX */
        &PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_TIMER4_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_UART1_GFCLK_MUX */
        &PMHAL_PRCM_MUX_UART1_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_UART1_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_UART1_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_UART2_GFCLK_MUX */
        &PMHAL_PRCM_MUX_UART2_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_UART2_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_UART2_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_UART3_GFCLK_MUX */
        &PMHAL_PRCM_MUX_UART3_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_UART3_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_UART3_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX */
        &PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_DCAN1_SYS_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX */
        &PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_regBitField,
        PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_WKUPAON_ICLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_EVE_CLK_MUX */
        &PMHAL_PRCM_MUX_EVE_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_EVE_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_EVE_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_DSP_GFCLK_MUX */
        &PMHAL_PRCM_MUX_DSP_GFCLK_MUX_regBitField,
        PMHAL_PRCM_MUX_DSP_GFCLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_DSP_GFCLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_RTI1_CLK_MUX */
        &PMHAL_PRCM_MUX_RTI1_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_RTI1_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_RTI1_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_RTI2_CLK_MUX */
        &PMHAL_PRCM_MUX_RTI2_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_RTI2_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_RTI2_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_RTI3_CLK_MUX */
        &PMHAL_PRCM_MUX_RTI3_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_RTI3_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_RTI3_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_RTI4_CLK_MUX */
        &PMHAL_PRCM_MUX_RTI4_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_RTI4_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_RTI4_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_RTI5_CLK_MUX */
        &PMHAL_PRCM_MUX_RTI5_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_RTI5_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_RTI5_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX */
        &PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_regBitField,
        PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_FUNC_32K_CLK_MUX_validEnumValues,
                   validEnumValue_t)
    },
    {   /* PMHAL_PRCM_MUX_DPLL_CORE_CLK */
        &PMHAL_PRCM_MUX_DPLL_CORE_CLK_regBitField,
        PMHAL_PRCM_MUX_DPLL_CORE_CLK_validEnumValues,
        VSIZE_TYPE(PMHAL_PRCM_MUX_DPLL_CORE_CLK_validEnumValues,
                   validEnumValue_t)
    }
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_ABE_24M_FCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_ABE_24M_FCLK_validDivValues[] =
{
    {8U,  CM_CLKSEL_ABE_24M_CLKSEL_SYSCLK_DIV_8 },
    {16U, CM_CLKSEL_ABE_24M_CLKSEL_SYSCLK_DIV_16}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_ABE_LP_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_ABE_LP_CLK_validDivValues[] =
{
    {16U, CM_CLKSEL_ABE_LP_CLK_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_ABE_LP_CLK_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_validDivValues[]
    =
    {
    {1U, CM_BYPCLK_DPLL_EVE_VID_DSP_CLKSEL_CORE_X2_CLK_DIV_1},
    {2U, CM_BYPCLK_DPLL_EVE_VID_DSP_CLKSEL_CORE_X2_CLK_DIV_2},
    {4U, CM_BYPCLK_DPLL_EVE_VID_DSP_CLKSEL_CORE_X2_CLK_DIV_4},
    {8U, CM_BYPCLK_DPLL_EVE_VID_DSP_CLKSEL_CORE_X2_CLK_DIV_8}
    };

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_FUNC_24M_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_FUNC_24M_CLK_validDivValues[] =
{
    {4U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_L3_ICLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_L3_ICLK_validDivValues[] =
{
    {1U, CM_CLKSEL_CORE_CLKSEL_L3_CORE_CLK_DIV_1},
    {2U, CM_CLKSEL_CORE_CLKSEL_L3_CORE_CLK_DIV_2}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_L4_ROOT_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_L4_ROOT_CLK_validDivValues[] =
{
    {1U, CM_CLKSEL_CORE_CLKSEL_L4_L3_CLK_DIV_1},
    {2U, CM_CLKSEL_CORE_CLKSEL_L4_L3_CLK_DIV_2}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_PER_DPLL_HS_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_validDivValues[]
    =
    {
    {2U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
    };

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_ABE_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_ABE_CLK_validDivValues[] =
{
    {0U, CM_CLKSEL_ABE_CLK_DIV_CLKSEL_CLK_DIV_1 },
    {1U, CM_CLKSEL_ABE_CLK_DIV_CLKSEL_CLK_DIV_2 },
    {2U, CM_CLKSEL_ABE_CLK_DIV_CLKSEL_CLK_DIV_4 },
    {3U, CM_CLKSEL_ABE_CLK_DIV_CLKSEL_CLK_DIV_8 },
    {4U, CM_CLKSEL_ABE_CLK_DIV_CLKSEL_CLK_DIV_16}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_ABE_GICLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_ABE_GICLK_validDivValues[] =
{
    {0U, CM_CLKSEL_ABE_GICLK_DIV_CLKSEL_CLK_DIV_1},
    {1U, CM_CLKSEL_ABE_GICLK_DIV_CLKSEL_CLK_DIV_2}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_AESS_FCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_AESS_FCLK_validDivValues[] =
{
    {0U, CM_CLKSEL_AESS_FCLK_DIV_CLKSEL_CLK_DIV_1},
    {1U, CM_CLKSEL_AESS_FCLK_DIV_CLKSEL_CLK_DIV_2}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX
 */
validDivValue_t                 PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_validDivValues
[]
    =
    {
    {2U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
    };

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_QSPI_GFCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_QSPI_GFCLK_validDivValues[] =
{
    {1U, CM_L4PER2_QSPI_CLKCTRL_CLKSEL_DIV_DIV1},
    {2U, CM_L4PER2_QSPI_CLKCTRL_CLKSEL_DIV_DIV2},
    {4U, CM_L4PER2_QSPI_CLKCTRL_CLKSEL_DIV_DIV4}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK
 */
validDivValue_t
    PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_validDivValues
[]
    =
    {
    {1U,  CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
    };

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_DSP_GCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_DSP_GCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_DSP_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_DSP_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_DSP_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_DSP_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_DSP_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_DSP_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_EMIF_PHY_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_EMIF_PHY_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_EMU_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_EMU_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_EMU_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_EMU_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_EMU_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_EMU_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_EMU_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_EMU_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_EVE_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_EVE_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_EVE_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_EVE_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_EVE_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_EVE_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_EVE_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_EVE_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_validDivValues
[] =
{
    {1U,  CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_GMAC_250M_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_GMAC_250M_DCLK_validDivValues[]
    =
    {
    {1U,  CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
    };

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_GPU_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_GPU_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_GPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_GPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_GPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_GPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_GPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_GPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_HDMI_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_HDMI_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_HDMI_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_HDMI_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_HDMI_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_HDMI_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_HDMI_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_HDMI_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_IVA_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_IVA_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_IVA_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_IVA_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_IVA_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_IVA_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_IVA_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_IVA_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_L3INIT_480M_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_L3INIT_480M_DCLK_validDivValues
[] =
{
    {1U,  CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_MPU_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_MPU_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_MPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_MPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_MPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_MPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_MPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_MPU_GCLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_PCIE2_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_PCIE2_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_PCIE2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_PCIE2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_PCIE2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_PCIE2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_PCIE2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_PCIE2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_PCIE_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_PCIE_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_PCIE1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_PCIE1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_PCIE1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_PCIE1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_PCIE1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_PCIE1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_PER_ABE_X1_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_validDivValues[]
    =
    {
    {1U,  CM_CLKSEL_PER_ABE_X1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_PER_ABE_X1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_PER_ABE_X1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_PER_ABE_X1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_PER_ABE_X1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_PER_ABE_X1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
    };

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_SATA_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_SATA_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_SATA_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_SATA_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_SATA_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_SATA_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_SATA_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_SATA_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_SECURE_32K_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_SECURE_32K_DCLK_validDivValues[]
    =
    {
    {1U,  CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
    };

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_SYS_CLK1_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_SYS_CLK1_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_SYS_CLK1_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_SYS_CLK1_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_SYS_CLK1_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_SYS_CLK1_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_SYS_CLK1_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_SYS_CLK1_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_SYS_CLK2_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_SYS_CLK2_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_SYS_CLK2_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_SYS_CLK2_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_SYS_CLK2_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_SYS_CLK2_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_SYS_CLK2_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_SYS_CLK2_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_USB_OTG_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_USB_OTG_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_VIDEO1_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_VIDEO1_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_VIDEO2_DCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_VIDEO2_DCLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_16},
    {32U, CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_FUNC_48M_FCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_FUNC_48M_FCLK_validDivValues[] =
{
    {4U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_FUNC_96M_FCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_FUNC_96M_FCLK_validDivValues[] =
{
    {2U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK
 */
validDivValue_t
    PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_validDivValues
[] =
{
    {2U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_MMC4_GFCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_MMC4_GFCLK_validDivValues[] =
{
    {1U, CM_L4PER_MMC4_CLKCTRL_CLKSEL_DIV_MMCCLK_DIV_1},
    {2U, CM_L4PER_MMC4_CLKCTRL_CLKSEL_DIV_MMCCLK_DIV_2},
    {4U, CM_L4PER_MMC4_CLKCTRL_CLKSEL_DIV_MMCCLK_DIV_4}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_RGMII_5M_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_RGMII_5M_CLK_validDivValues
[] =
{
    {10U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_HDMI_CLK2
 */
validDivValue_t                 PMHAL_PRCM_DIV_HDMI_CLK2_validDivValues[] =
{
    {1U,  CM_CLKSEL_HDMI_MCASP_AUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_HDMI_MCASP_AUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_HDMI_MCASP_AUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_HDMI_MCASP_AUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_HDMI_MCASP_AUX_CLKSEL_CLK_DIV_16}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2
 */
validDivValue_t                 PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_validDivValues
[] =
{
    {1U,  CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX_CLKSEL_CLK_DIV_16}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_VIDEO1_CLK2
 */
validDivValue_t                 PMHAL_PRCM_DIV_VIDEO1_CLK2_validDivValues[] =
{
    {1U,  CM_CLKSEL_VIDEO1_MCASP_AUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_VIDEO1_MCASP_AUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_VIDEO1_MCASP_AUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_VIDEO1_MCASP_AUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_VIDEO1_MCASP_AUX_CLKSEL_CLK_DIV_16}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_VIDEO2_CLK2
 */
validDivValue_t                 PMHAL_PRCM_DIV_VIDEO2_CLK2_validDivValues[] =
{
    {1U,  CM_CLKSEL_VIDEO2_MCASP_AUX_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_VIDEO2_MCASP_AUX_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_VIDEO2_MCASP_AUX_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_VIDEO2_MCASP_AUX_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_VIDEO2_MCASP_AUX_CLKSEL_CLK_DIV_16}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_MLBP_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_MLBP_CLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_MLBP_MCASP_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_MLBP_MCASP_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_MLBP_MCASP_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_MLBP_MCASP_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_MLBP_MCASP_CLKSEL_CLK_DIV_16}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_MLB_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_MLB_CLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_MLB_MCASP_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_MLB_MCASP_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_MLB_MCASP_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_MLB_MCASP_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_MLB_MCASP_CLKSEL_CLK_DIV_16}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_HDMI_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_HDMI_CLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_HDMI_TIMER_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_HDMI_TIMER_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_HDMI_TIMER_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_HDMI_TIMER_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_HDMI_TIMER_CLKSEL_CLK_DIV_16},
    {22U, CM_CLKSEL_HDMI_TIMER_CLKSEL_CLK_DIV_22},
    {32U, CM_CLKSEL_HDMI_TIMER_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_VIDEO1_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_VIDEO1_CLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_VIDEO1_TIMER_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_VIDEO1_TIMER_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_VIDEO1_TIMER_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_VIDEO1_TIMER_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_VIDEO1_TIMER_CLKSEL_CLK_DIV_16},
    {22U, CM_CLKSEL_VIDEO1_TIMER_CLKSEL_CLK_DIV_22},
    {32U, CM_CLKSEL_VIDEO1_TIMER_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for PMHAL_PRCM_DIV_VIDEO2_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_VIDEO2_CLK_validDivValues[] =
{
    {1U,  CM_CLKSEL_VIDEO2_TIMER_CLKSEL_CLK_DIV_1 },
    {2U,  CM_CLKSEL_VIDEO2_TIMER_CLKSEL_CLK_DIV_2 },
    {4U,  CM_CLKSEL_VIDEO2_TIMER_CLKSEL_CLK_DIV_4 },
    {8U,  CM_CLKSEL_VIDEO2_TIMER_CLKSEL_CLK_DIV_8 },
    {16U, CM_CLKSEL_VIDEO2_TIMER_CLKSEL_CLK_DIV_16},
    {22U, CM_CLKSEL_VIDEO2_TIMER_CLKSEL_CLK_DIV_22},
    {32U, CM_CLKSEL_VIDEO2_TIMER_CLKSEL_CLK_DIV_32}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK
 */
validDivValue_t
    PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_validDivValues
[]
    =
    {
    {2U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
    };

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_ABE_SYS_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_ABE_SYS_CLK_validDivValues[] =
{
    {1U, CM_CLKSEL_ABE_SYS_CLKSEL_SYSCLK_DIV_1},
    {2U, CM_CLKSEL_ABE_SYS_CLKSEL_SYSCLK_DIV_2}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_L3INSTR_TS_GCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_L3INSTR_TS_GCLK_validDivValues[]
    =
    {
    {8U,  CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_DIV8 },
    {16U, CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_DIV16},
    {32U, CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_DIV32}
    };

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_TIMER_SYS_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_TIMER_SYS_CLK_validDivValues[] =
{
    {1U, CM_CLKSEL_TIMER_SYS_CLKSEL_SYSCLK_DIV_1},
    {2U, CM_CLKSEL_TIMER_SYS_CLKSEL_SYSCLK_DIV_2}
};

/**
 *  \brief structure define Valid divider Value for PMHAL_PRCM_DIV_TESOC_EXT_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_TESOC_EXT_CLK_validDivValues[] =
{
    {1U, CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_DIV1},
    {2U, CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_DIV2},
    {4U, CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_DIV4}
};

/**
 *  \brief structure define Valid divider Values for PMHAL_PRCM_DIV_VID_PIX_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_VID_PIX_CLK_validDivValues[] =
{
    {1U, CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_DIV1},
    {2U, CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_DIV2},
    {4U, CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_DIV4}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_SYS_CLK1
 */
validDivValue_t                 PMHAL_PRCM_DIV_SYS_CLK1_validDivValues[] =
{
    {4U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_SYS_CLK2
 */
validDivValue_t                 PMHAL_PRCM_DIV_SYS_CLK2_validDivValues[] =
{
    {4U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_IPU1_GCLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_IPU1_GCLK_validDivValues[] =
{
    {2U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
};

/**
 *  \brief Structure defining Valid divider Values for
 *         PMHAL_PRCM_DIV_FUNC_32K_CLK
 */
validDivValue_t                 PMHAL_PRCM_DIV_FUNC_32K_CLK_validDivValues[] =
{
    {610U, PMHAL_DIV_ENUM_NOTAPPLICABLE}
};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_ABE_24M_FCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_ABE_24M_FCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_ABE_24M),
 CM_CLKSEL_ABE_24M_CLKSEL_MASK,
 CM_CLKSEL_ABE_24M_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_ABE_LP_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_ABE_LP_CLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_ABE_LP_CLK),
 CM_CLKSEL_ABE_LP_CLK_CLKSEL_MASK,
 CM_CLKSEL_ABE_LP_CLK_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_BYPCLK_DPLL_EVE_VID_DSP),
 CM_BYPCLK_DPLL_EVE_VID_DSP_CLKSEL_MASK,
 CM_BYPCLK_DPLL_EVE_VID_DSP_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_FUNC_24M_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_FUNC_24M_CLK_regBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_L3_ICLK
 */
regBitField_t                   PMHAL_PRCM_DIV_L3_ICLK_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_CLKSEL_CORE),
 CM_CLKSEL_CORE_CLKSEL_L3_MASK,
 CM_CLKSEL_CORE_CLKSEL_L3_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_L4_ROOT_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_L4_ROOT_CLK_regBitField =
{(SOC_CKGEN_CM_CORE_AON_BASE + CM_CLKSEL_CORE),
 CM_CLKSEL_CORE_CLKSEL_L4_MASK,
 CM_CLKSEL_CORE_CLKSEL_L4_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_PER_DPLL_HS_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_regBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_ABE_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_ABE_CLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_ABE_CLK_DIV),
 CM_CLKSEL_ABE_CLK_DIV_CLKSEL_MASK,
 CM_CLKSEL_ABE_CLK_DIV_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_ABE_GICLK
 */
regBitField_t                   PMHAL_PRCM_DIV_ABE_GICLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_ABE_GICLK_DIV),
 CM_CLKSEL_ABE_GICLK_DIV_CLKSEL_MASK,
 CM_CLKSEL_ABE_GICLK_DIV_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_AESS_FCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_AESS_FCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_AESS_FCLK_DIV),
 CM_CLKSEL_AESS_FCLK_DIV_CLKSEL_MASK,
 CM_CLKSEL_AESS_FCLK_DIV_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX
 */
regBitField_t                   PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_regBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_QSPI_GFCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_QSPI_GFCLK_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL),
 CM_L4PER2_QSPI_CLKCTRL_CLKSEL_DIV_MASK,
 CM_L4PER2_QSPI_CLKCTRL_CLKSEL_DIV_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX),
 CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_CORE_DPLL_OUT_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_DSP_GCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_DSP_GCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_DSP_GFCLK_CLKOUTMUX),
 CM_CLKSEL_DSP_GFCLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_DSP_GFCLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_EMIF_PHY_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_EMIF_PHY_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX),
 CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_EMIF_PHY_GCLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_EMU_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_EMU_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_EMU_CLK_CLKOUTMUX),
 CM_CLKSEL_EMU_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_EMU_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_EVE_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_EVE_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_EVE_GFCLK_CLKOUTMUX),
 CM_CLKSEL_EVE_GFCLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_EVE_GFCLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX),
 CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_FUNC_96M_AON_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_GMAC_250M_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_GMAC_250M_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX),
 CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_GMAC_250M_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_GPU_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_GPU_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_GPU_GCLK_CLKOUTMUX),
 CM_CLKSEL_GPU_GCLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_GPU_GCLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_HDMI_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_HDMI_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_HDMI_CLK_CLKOUTMUX),
 CM_CLKSEL_HDMI_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_HDMI_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_IVA_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_IVA_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_IVA_GCLK_CLKOUTMUX),
 CM_CLKSEL_IVA_GCLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_IVA_GCLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_L3INIT_480M_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_L3INIT_480M_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX),
 CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_L3INIT_480M_GFCLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_MPU_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_MPU_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_MPU_GCLK_CLKOUTMUX),
 CM_CLKSEL_MPU_GCLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_MPU_GCLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_PCIE2_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_PCIE2_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_PCIE2_CLK_CLKOUTMUX),
 CM_CLKSEL_PCIE2_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_PCIE2_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_PCIE_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_PCIE_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_PCIE1_CLK_CLKOUTMUX),
 CM_CLKSEL_PCIE1_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_PCIE1_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_PER_ABE_X1_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_PCIE1_CLK_CLKOUTMUX),
 CM_CLKSEL_PCIE1_CLK_CLKOUTMUX_CLKSEL_SHIFT,
 CM_CLKSEL_PER_ABE_X1_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_SATA_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_SATA_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_SATA_CLK_CLKOUTMUX),
 CM_CLKSEL_SATA_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_SATA_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_SECURE_32K_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_SECURE_32K_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX),
 CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_SECURE_32K_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_SYS_CLK1_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_SYS_CLK1_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_SYS_CLK1_CLKOUTMUX),
 CM_CLKSEL_SYS_CLK1_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_SYS_CLK1_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_SYS_CLK2_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_SYS_CLK2_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_SYS_CLK2_CLKOUTMUX),
 CM_CLKSEL_SYS_CLK2_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_SYS_CLK2_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_USB_OTG_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_USB_OTG_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX),
 CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_USB_OTG_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_VIDEO1_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_VIDEO1_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX),
 CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_VIDEO1_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_VIDEO2_DCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_VIDEO2_DCLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX),
 CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX_CLKSEL_MASK,
 CM_CLKSEL_VIDEO2_CLK_CLKOUTMUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_FUNC_48M_FCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_FUNC_48M_FCLK_regBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_FUNC_96M_FCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_FUNC_96M_FCLK_regBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_regBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_MMC4_GFCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_MMC4_GFCLK_regBitField =
{(SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL),
 CM_L4PER_MMC4_CLKCTRL_CLKSEL_DIV_MASK,
 CM_L4PER_MMC4_CLKCTRL_CLKSEL_DIV_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_RGMII_5M_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_RGMII_5M_CLK_regBitField =
{PMHAL_REG_NOTAPPLICABLE, PMHAL_MASK_NOTAPPLICABLE, PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_HDMI_CLK2
 */
regBitField_t                   PMHAL_PRCM_DIV_HDMI_CLK2_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_HDMI_MCASP_AUX),
 CM_CLKSEL_HDMI_MCASP_AUX_CLKSEL_MASK,
 CM_CLKSEL_HDMI_MCASP_AUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2
 */
regBitField_t                   PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX),
 CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX_CLKSEL_MASK,
 CM_CLKSEL_PER_ABE_X1_GFCLK_MCASP_AUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_VIDEO1_CLK2
 */
regBitField_t                   PMHAL_PRCM_DIV_VIDEO1_CLK2_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_VIDEO1_MCASP_AUX),
 CM_CLKSEL_VIDEO1_MCASP_AUX_CLKSEL_MASK,
 CM_CLKSEL_VIDEO1_MCASP_AUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_VIDEO2_CLK2
 */
regBitField_t                   PMHAL_PRCM_DIV_VIDEO2_CLK2_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_VIDEO2_MCASP_AUX),
 CM_CLKSEL_VIDEO2_MCASP_AUX_CLKSEL_MASK,
 CM_CLKSEL_VIDEO2_MCASP_AUX_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_MLBP_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_MLBP_CLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_MLBP_MCASP),
 CM_CLKSEL_MLBP_MCASP_CLKSEL_MASK,
 CM_CLKSEL_MLBP_MCASP_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_MLB_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_MLB_CLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_MLB_MCASP),
 CM_CLKSEL_MLB_MCASP_CLKSEL_MASK,
 CM_CLKSEL_MLB_MCASP_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_HDMI_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_HDMI_CLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_HDMI_TIMER),
 CM_CLKSEL_HDMI_TIMER_CLKSEL_MASK,
 CM_CLKSEL_HDMI_TIMER_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_VIDEO1_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_VIDEO1_CLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_VIDEO1_TIMER),
 CM_CLKSEL_VIDEO1_TIMER_CLKSEL_MASK,
 CM_CLKSEL_VIDEO1_TIMER_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_VIDEO2_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_VIDEO2_CLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_VIDEO2_TIMER),
 CM_CLKSEL_VIDEO2_TIMER_CLKSEL_MASK,
 CM_CLKSEL_VIDEO2_TIMER_CLKSEL_SHIFT};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_regBitField
    =
    {PMHAL_REG_NOTAPPLICABLE,
     PMHAL_MASK_NOTAPPLICABLE,
     PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_ABE_SYS_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_ABE_SYS_CLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_ABE_SYS),
 CM_CLKSEL_ABE_SYS_CLKSEL_MASK,
 CM_CLKSEL_ABE_SYS_CLKSEL_SHIFT};
/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_L3INSTR_TS_GCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_L3INSTR_TS_GCLK_regBitField =
{(SOC_CORE_CM_CORE_BASE + CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL),
 CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_MASK,
 CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_SHIFT};
/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_TIMER_SYS_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_TIMER_SYS_CLK_regBitField =
{(SOC_CKGEN_PRM_BASE + CM_CLKSEL_TIMER_SYS),
 CM_CLKSEL_TIMER_SYS_CLKSEL_MASK,
 CM_CLKSEL_TIMER_SYS_CLKSEL_SHIFT};

/**
 *  \brief structure defining divider Registers for PMHAL_PRCM_DIV_TESOC_EXT_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_TESOC_EXT_CLK_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_TESOC_EXT_CLK_DIV_SHIFT};

/**
 *  \brief structure defining divider Registers for PMHAL_PRCM_DIV_VID_PIX_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_VID_PIX_CLK_regBitField =
{(SOC_SEC_EFUSE_REGISTERS_BASE + CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2),
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_MASK,
 CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_EXT_DIV_SHIFT};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_SYS_CLK1
 */
regBitField_t                   PMHAL_PRCM_DIV_SYS_CLK1_regBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for PMHAL_PRCM_DIV_SYS_CLK2
 */
regBitField_t                   PMHAL_PRCM_DIV_SYS_CLK2_regBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_IPU1_GCLK
 */
regBitField_t                   PMHAL_PRCM_DIV_IPU1_GCLK_regBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining divider Registers for
 *         PMHAL_PRCM_DIV_FUNC_32K_CLK
 */
regBitField_t                   PMHAL_PRCM_DIV_FUNC_32K_CLK_regBitField =
{PMHAL_REG_NOTAPPLICABLE,
 PMHAL_MASK_NOTAPPLICABLE,
 PMHAL_SHIFT_NOTAPPLICABLE};

/**
 *  \brief Structure defining Divider Elements
 */
const pmhalClockDivider_t       pmhalDividerElems[] =
{
    {   /* PMHAL_PRCM_DIV_ABE_24M_FCLK */
        &PMHAL_PRCM_DIV_ABE_24M_FCLK_regBitField,
        PMHAL_PRCM_DIV_ABE_24M_FCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_ABE_24M_FCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_ABE_LP_CLK */
        &PMHAL_PRCM_DIV_ABE_LP_CLK_regBitField,
        PMHAL_PRCM_DIV_ABE_LP_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_ABE_LP_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK */
        &PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_regBitField,
        PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_DSP_DPLL_HS_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_FUNC_24M_CLK */
        &PMHAL_PRCM_DIV_FUNC_24M_CLK_regBitField,
        PMHAL_PRCM_DIV_FUNC_24M_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_24M_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_L3_ICLK */
        &PMHAL_PRCM_DIV_L3_ICLK_regBitField,
        PMHAL_PRCM_DIV_L3_ICLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_L3_ICLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_L4_ROOT_CLK */
        &PMHAL_PRCM_DIV_L4_ROOT_CLK_regBitField,
        PMHAL_PRCM_DIV_L4_ROOT_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_L4_ROOT_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_PER_DPLL_HS_CLK */
        &PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_regBitField,
        PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_PER_DPLL_HS_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_ABE_CLK */
        &PMHAL_PRCM_DIV_ABE_CLK_regBitField,
        PMHAL_PRCM_DIV_ABE_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_ABE_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_ABE_GICLK */
        &PMHAL_PRCM_DIV_ABE_GICLK_regBitField,
        PMHAL_PRCM_DIV_ABE_GICLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_ABE_GICLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_AESS_FCLK */
        &PMHAL_PRCM_DIV_AESS_FCLK_regBitField,
        PMHAL_PRCM_DIV_AESS_FCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_AESS_FCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX */
        &PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_regBitField,
        PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_128M_CLK_MUX_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_QSPI_GFCLK */
        &PMHAL_PRCM_DIV_QSPI_GFCLK_regBitField,
        PMHAL_PRCM_DIV_QSPI_GFCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_QSPI_GFCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK */
        &PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_regBitField,
        PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_CORE_DPLL_OUT_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_DSP_GCLK */
        &PMHAL_PRCM_DIV_DSP_GCLK_regBitField,
        PMHAL_PRCM_DIV_DSP_GCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_DSP_GCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_EMIF_PHY_DCLK */
        &PMHAL_PRCM_DIV_EMIF_PHY_DCLK_regBitField,
        PMHAL_PRCM_DIV_EMIF_PHY_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_EMIF_PHY_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_EMU_DCLK */
        &PMHAL_PRCM_DIV_EMU_DCLK_regBitField,
        PMHAL_PRCM_DIV_EMU_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_EMU_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_EVE_DCLK */
        &PMHAL_PRCM_DIV_EVE_DCLK_regBitField,
        PMHAL_PRCM_DIV_EVE_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_EVE_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK */
        &PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_regBitField,
        PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_96M_AON_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_GMAC_250M_DCLK */
        &PMHAL_PRCM_DIV_GMAC_250M_DCLK_regBitField,
        PMHAL_PRCM_DIV_GMAC_250M_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_GMAC_250M_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_GPU_DCLK */
        &PMHAL_PRCM_DIV_GPU_DCLK_regBitField,
        PMHAL_PRCM_DIV_GPU_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_GPU_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_HDMI_DCLK */
        &PMHAL_PRCM_DIV_HDMI_DCLK_regBitField,
        PMHAL_PRCM_DIV_HDMI_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_HDMI_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_IVA_DCLK */
        &PMHAL_PRCM_DIV_IVA_DCLK_regBitField,
        PMHAL_PRCM_DIV_IVA_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_IVA_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_L3INIT_480M_DCLK */
        &PMHAL_PRCM_DIV_L3INIT_480M_DCLK_regBitField,
        PMHAL_PRCM_DIV_L3INIT_480M_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_L3INIT_480M_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_MPU_DCLK */
        &PMHAL_PRCM_DIV_MPU_DCLK_regBitField,
        PMHAL_PRCM_DIV_MPU_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_MPU_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_PCIE2_DCLK */
        &PMHAL_PRCM_DIV_PCIE2_DCLK_regBitField,
        PMHAL_PRCM_DIV_PCIE2_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_PCIE2_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_PCIE_DCLK */
        &PMHAL_PRCM_DIV_PCIE_DCLK_regBitField,
        PMHAL_PRCM_DIV_PCIE_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_PCIE_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_PER_ABE_X1_DCLK */
        &PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_regBitField,
        PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_PER_ABE_X1_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_SATA_DCLK */
        &PMHAL_PRCM_DIV_SATA_DCLK_regBitField,
        PMHAL_PRCM_DIV_SATA_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_SATA_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_SECURE_32K_DCLK */
        &PMHAL_PRCM_DIV_SECURE_32K_DCLK_regBitField,
        PMHAL_PRCM_DIV_SECURE_32K_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_SECURE_32K_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_SYS_CLK1_DCLK */
        &PMHAL_PRCM_DIV_SYS_CLK1_DCLK_regBitField,
        PMHAL_PRCM_DIV_SYS_CLK1_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_SYS_CLK1_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_SYS_CLK2_DCLK */
        &PMHAL_PRCM_DIV_SYS_CLK2_DCLK_regBitField,
        PMHAL_PRCM_DIV_SYS_CLK2_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_SYS_CLK2_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_USB_OTG_DCLK */
        &PMHAL_PRCM_DIV_USB_OTG_DCLK_regBitField,
        PMHAL_PRCM_DIV_USB_OTG_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_USB_OTG_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_VIDEO1_DCLK */
        &PMHAL_PRCM_DIV_VIDEO1_DCLK_regBitField,
        PMHAL_PRCM_DIV_VIDEO1_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO1_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_VIDEO2_DCLK */
        &PMHAL_PRCM_DIV_VIDEO2_DCLK_regBitField,
        PMHAL_PRCM_DIV_VIDEO2_DCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO2_DCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_FUNC_48M_FCLK */
        &PMHAL_PRCM_DIV_FUNC_48M_FCLK_regBitField,
        PMHAL_PRCM_DIV_FUNC_48M_FCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_48M_FCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_FUNC_96M_FCLK */
        &PMHAL_PRCM_DIV_FUNC_96M_FCLK_regBitField,
        PMHAL_PRCM_DIV_FUNC_96M_FCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_96M_FCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK */
        &PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_regBitField,
        PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_GMAC_GMII_MAIN_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_MMC4_GFCLK */
        &PMHAL_PRCM_DIV_MMC4_GFCLK_regBitField,
        PMHAL_PRCM_DIV_MMC4_GFCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_MMC4_GFCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_RGMII_5M_CLK */
        &PMHAL_PRCM_DIV_RGMII_5M_CLK_regBitField,
        PMHAL_PRCM_DIV_RGMII_5M_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_RGMII_5M_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_HDMI_CLK2 */
        &PMHAL_PRCM_DIV_HDMI_CLK2_regBitField,
        PMHAL_PRCM_DIV_HDMI_CLK2_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_HDMI_CLK2_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2 */
        &PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_regBitField,
        PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_PER_ABE_X1_GFCLK2_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_VIDEO1_CLK2 */
        &PMHAL_PRCM_DIV_VIDEO1_CLK2_regBitField,
        PMHAL_PRCM_DIV_VIDEO1_CLK2_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO1_CLK2_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_VIDEO2_CLK2 */
        &PMHAL_PRCM_DIV_VIDEO2_CLK2_regBitField,
        PMHAL_PRCM_DIV_VIDEO2_CLK2_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO2_CLK2_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_MLBP_CLK */
        &PMHAL_PRCM_DIV_MLBP_CLK_regBitField,
        PMHAL_PRCM_DIV_MLBP_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_MLBP_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_MLB_CLK */
        &PMHAL_PRCM_DIV_MLB_CLK_regBitField,
        PMHAL_PRCM_DIV_MLB_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_MLB_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_HDMI_CLK */
        &PMHAL_PRCM_DIV_HDMI_CLK_regBitField,
        PMHAL_PRCM_DIV_HDMI_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_HDMI_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_VIDEO1_CLK */
        &PMHAL_PRCM_DIV_VIDEO1_CLK_regBitField,
        PMHAL_PRCM_DIV_VIDEO1_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO1_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_VIDEO2_CLK */
        &PMHAL_PRCM_DIV_VIDEO2_CLK_regBitField,
        PMHAL_PRCM_DIV_VIDEO2_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_VIDEO2_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK */
        &PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_regBitField,
        PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_CUSTEFUSE_SYS_GFCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_ABE_SYS_CLK */
        &PMHAL_PRCM_DIV_ABE_SYS_CLK_regBitField,
        PMHAL_PRCM_DIV_ABE_SYS_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_ABE_SYS_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_L3INSTR_TS_GCLK */
        &PMHAL_PRCM_DIV_L3INSTR_TS_GCLK_regBitField,
        PMHAL_PRCM_DIV_L3INSTR_TS_GCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_L3INSTR_TS_GCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_TIMER_SYS_CLK */
        &PMHAL_PRCM_DIV_TIMER_SYS_CLK_regBitField,
        PMHAL_PRCM_DIV_TIMER_SYS_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_TIMER_SYS_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_TESOC_EXT_CLK */
        &PMHAL_PRCM_DIV_TESOC_EXT_CLK_regBitField,
        PMHAL_PRCM_DIV_TESOC_EXT_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_TESOC_EXT_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_VID_PIX_CLK */
        &PMHAL_PRCM_DIV_VID_PIX_CLK_regBitField,
        PMHAL_PRCM_DIV_VID_PIX_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_VID_PIX_CLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_SYS_CLK1 */
        &PMHAL_PRCM_DIV_SYS_CLK1_regBitField,
        PMHAL_PRCM_DIV_SYS_CLK1_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_SYS_CLK1_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_SYS_CLK2 */
        &PMHAL_PRCM_DIV_SYS_CLK2_regBitField,
        PMHAL_PRCM_DIV_SYS_CLK2_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_SYS_CLK2_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_IPU1_GCLK*/
        &PMHAL_PRCM_DIV_IPU1_GCLK_regBitField,
        PMHAL_PRCM_DIV_IPU1_GCLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_IPU1_GCLK_validDivValues,
                   validDivValue_t)
    },
    {   /* PMHAL_PRCM_DIV_FUNC_32K_CLK*/
        &PMHAL_PRCM_DIV_FUNC_32K_CLK_regBitField,
        PMHAL_PRCM_DIV_FUNC_32K_CLK_validDivValues,
        VSIZE_TYPE(PMHAL_PRCM_DIV_FUNC_32K_CLK_validDivValues,
                   validDivValue_t)
    }
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_DSP1_RET_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP1_RET_RST_rstCtrlRegBitField =
{
    (SOC_DSP1_PRM_BASE + RM_DSP1_RSTCTRL),
    RM_DSP1_RSTCTRL_RST_DSP1_SHIFT
};

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_DSP1_RET_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP1_RET_RST_rstStRegBitField =
{
    (SOC_DSP1_PRM_BASE + RM_DSP1_RSTST),
    RM_DSP1_RSTST_RST_DSP1_SHIFT
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_DSP1_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP1_RST_rstCtrlRegBitField =
{
    (SOC_DSP1_PRM_BASE + RM_DSP1_RSTCTRL),
    RM_DSP1_RSTCTRL_RST_DSP1_LRST_SHIFT
};

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_DSP1_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP1_RST_rstStRegBitField =
{
    (SOC_DSP1_PRM_BASE + RM_DSP1_RSTST),
    RM_DSP1_RSTST_RST_DSP1_LRST_SHIFT
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_DSP1_SYS_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP1_SYS_RST_rstCtrlRegBitField =
{
    (SOC_DSP1_PRM_BASE + RM_DSP1_RSTCTRL),
    RM_DSP1_RSTCTRL_RST_DSP1_SHIFT
};

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_DSP1_SYS_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP1_SYS_RST_rstStRegBitField =
{
    (SOC_DSP1_PRM_BASE + RM_DSP1_RSTST),
    RM_DSP1_RSTST_RST_DSP1_SHIFT
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_DSP2_RET_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP2_RET_RST_rstCtrlRegBitField =
{
    (SOC_DSP2_PRM_BASE + RM_DSP2_RSTCTRL),
    RM_DSP2_RSTCTRL_RST_DSP2_SHIFT
};

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_DSP2_RET_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP2_RET_RST_rstStRegBitField =
{
    (SOC_DSP2_PRM_BASE + RM_DSP2_RSTST),
    RM_DSP2_RSTST_RST_DSP2_SHIFT
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_DSP2_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP2_RST_rstCtrlRegBitField =
{
    (SOC_DSP2_PRM_BASE + RM_DSP2_RSTCTRL),
    RM_DSP2_RSTCTRL_RST_DSP2_LRST_SHIFT
};

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_DSP2_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP2_RST_rstStRegBitField =
{
    (SOC_DSP2_PRM_BASE + RM_DSP2_RSTST),
    RM_DSP2_RSTST_RST_DSP2_LRST_MASK
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_DSP2_SYS_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP2_SYS_RST_rstCtrlRegBitField =
{
    (SOC_DSP2_PRM_BASE + RM_DSP2_RSTCTRL),
    RM_DSP2_RSTCTRL_RST_DSP2_SHIFT
};

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_DSP2_SYS_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_DSP2_SYS_RST_rstStRegBitField =
{
    (SOC_DSP2_PRM_BASE + RM_DSP2_RSTST),
    RM_DSP2_RSTST_RST_DSP2_SHIFT
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_EVE1_CPU_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_EVE1_CPU_RST_rstCtrlRegBitField =
{
    (SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL),
    RM_EVE1_RSTCTRL_RST_EVE1_LRST_SHIFT
};

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_EVE1_CPU_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_EVE1_CPU_RST_rstStRegBitField =
{
    (SOC_EVE1_PRM_BASE + RM_EVE1_RSTST),
    RM_EVE1_RSTST_RST_EVE1_LRST_SHIFT
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_EVE1_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_EVE1_RST_rstCtrlRegBitField =
{
    (SOC_EVE1_PRM_BASE + RM_EVE1_RSTCTRL),
    RM_EVE1_RSTCTRL_RST_EVE1_SHIFT
};

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_EVE1_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_EVE1_RST_rstStRegBitField =
{
    (SOC_EVE1_PRM_BASE + RM_EVE1_RSTST),
    RM_EVE1_RSTST_RST_EVE1_SHIFT
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_IPU1_CPU0_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_IPU1_CPU0_RST_rstCtrlRegBitField
    =
    {
    (SOC_IPU_PRM_BASE + RM_IPU1_RSTCTRL),
    RM_IPU1_RSTCTRL_RST_CPU0_SHIFT
    };

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_IPU1_CPU0_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_IPU1_CPU0_RST_rstStRegBitField =
{
    (SOC_IPU_PRM_BASE + RM_IPU1_RSTST),
    RM_IPU1_RSTST_RST_CPU0_SHIFT
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_IPU1_CPU1_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_IPU1_CPU1_RST_rstCtrlRegBitField
    =
    {
    (SOC_IPU_PRM_BASE + RM_IPU1_RSTCTRL),
    RM_IPU1_RSTCTRL_RST_CPU1_SHIFT
    };

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_IPU1_CPU1_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_IPU1_CPU1_RST_rstStRegBitField =
{
    (SOC_IPU_PRM_BASE + RM_IPU1_RSTST),
    RM_IPU1_RSTST_RST_CPU1_SHIFT
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_IPU1_RET_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_IPU1_RET_RST_rstCtrlRegBitField =
{
    (SOC_IPU_PRM_BASE + RM_IPU1_RSTCTRL),
    RM_IPU1_RSTCTRL_RST_IPU_SHIFT
};

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_IPU1_RET_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_IPU1_RET_RST_rstStRegBitField =
{
    (SOC_IPU_PRM_BASE + RM_IPU1_RSTST),
    RM_IPU1_RSTST_RST_IPU_SHIFT
};

/**
 *  \brief structure defining CTRL Register for PMHAL_PRCM_RG_IPU1_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_IPU1_RST_rstCtrlRegBitField =
{
    (SOC_IPU_PRM_BASE + RM_IPU1_RSTCTRL),
    RM_IPU1_RSTCTRL_RST_IPU_SHIFT
};

/**
 *  \brief structure defining STATUS Register for PMHAL_PRCM_RG_IPU1_RST
 */
regBitFieldShift_t              PMHAL_PRCM_RG_IPU1_RST_rstStRegBitField =
{
    (SOC_IPU_PRM_BASE + RM_IPU1_RSTST),
    RM_IPU1_RSTST_RST_IPU_SHIFT
};

/**
 *  \brief structure defining programmable Reset Domain Elements
 */
const pmhalReset_t              pmhalResetDomainElems[] =
{
    {   /* PMHAL_PRCM_RG_DSP1_RET_RST */
        &PMHAL_PRCM_RG_DSP1_RET_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_DSP1_RET_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_UNDEF, /* To Subsystem */
        PMHAL_PRCM_MOD_UNDEF  /* To CPU */
    },
    {                         /* PMHAL_PRCM_RG_DSP1_RST */
        &PMHAL_PRCM_RG_DSP1_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_DSP1_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_UNDEF, /* To Subsystem */
        PMHAL_PRCM_MOD_DSP1   /* To CPU */
    },
    {                         /* PMHAL_PRCM_RG_DSP1_SYS_RST */
        &PMHAL_PRCM_RG_DSP1_SYS_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_DSP1_SYS_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_DSP1, /* To Subsystem */
        PMHAL_PRCM_MOD_UNDEF /* To CPU */
    },
    {                        /* PMHAL_PRCM_RG_DSP2_RET_RST */
        &PMHAL_PRCM_RG_DSP2_RET_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_DSP2_RET_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_UNDEF, /* To Subsystem */
        PMHAL_PRCM_MOD_UNDEF  /* To CPU */
    },
    {                         /* PMHAL_PRCM_RG_DSP2_RST */
        &PMHAL_PRCM_RG_DSP2_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_DSP2_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_UNDEF, /* To Subsystem */
        PMHAL_PRCM_MOD_DSP2   /* To CPU */
    },
    {                         /* PMHAL_PRCM_RG_DSP2_SYS_RST */
        &PMHAL_PRCM_RG_DSP2_SYS_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_DSP2_SYS_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_DSP2, /* To Subsystem */
        PMHAL_PRCM_MOD_UNDEF /* To CPU */
    },
    {                        /* PMHAL_PRCM_RG_EVE1_CPU_RST */
        &PMHAL_PRCM_RG_EVE1_CPU_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_EVE1_CPU_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_UNDEF, /* To Subsystem */
        PMHAL_PRCM_MOD_EVE1   /* To CPU */
    },
    {                         /* PMHAL_PRCM_RG_EVE1_RST */
        &PMHAL_PRCM_RG_EVE1_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_EVE1_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_EVE1, /* To Subsystem */
        PMHAL_PRCM_MOD_UNDEF /* To CPU */
    },
    {                        /* PMHAL_PRCM_RG_IPU1_CPU0_RST */
        &PMHAL_PRCM_RG_IPU1_CPU0_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_IPU1_CPU0_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_UNDEF,
        PMHAL_PRCM_MOD_UNDEF /* IPU is the boot master hence not resetting
                              * this in TDA3x */
    },
    {                        /* PMHAL_PRCM_RG_IPU1_CPU1_RST */
        &PMHAL_PRCM_RG_IPU1_CPU1_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_IPU1_CPU1_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_UNDEF,
        PMHAL_PRCM_MOD_UNDEF /* IPU is the boot master hence not resetting
                              * this in TDA3x */
    },
    {                        /* PMHAL_PRCM_RG_IPU1_RET_RST */
        &PMHAL_PRCM_RG_IPU1_RET_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_IPU1_RET_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_UNDEF, /* To Subsystem */
        PMHAL_PRCM_MOD_UNDEF  /* To CPU */
    },
    {                         /* PMHAL_PRCM_RG_IPU1_RST */
        &PMHAL_PRCM_RG_IPU1_RST_rstCtrlRegBitField,
        &PMHAL_PRCM_RG_IPU1_RST_rstStRegBitField,
        PMHAL_PRCM_MOD_IPU1, /* To Subsystem */
        PMHAL_PRCM_MOD_UNDEF /* To CPU */
    }
};

/**
 *  \brief structure defining Control Register for
 *         PMHAL_PRCM_PD_RM_OCCUR_GLOBAL_WARM_RESET
 */
regBitFieldShift_t
    PMHAL_PRCM_PD_RM_OCCUR_GLOBAL_WARM_RESET_rstctrlBitField =
{
    (SOC_DEVICE_PRM_BASE + PRM_RSTCTRL),
    PRM_RSTCTRL_RST_GLOBAL_WARM_SW_SHIFT
};

/**
 *  \brief structure defining Control Register for
 *         PMHAL_PRCM_PD_RM_OCCUR_GLOBAL_COLD_RESET
 */
regBitFieldShift_t
    PMHAL_PRCM_PD_RM_OCCUR_GLOBAL_COLD_RESET_rstctrlBitField =
{
    (SOC_DEVICE_PRM_BASE + PRM_RSTCTRL),
    PRM_RSTCTRL_RST_GLOBAL_COLD_SW_SHIFT
};

/**
 *  \brief structure defining Global Reset Domain Control elements
 */
const pmhalGlobalResetControl_t pmhalGlobalResetControlElems[] =
{
    {   /* PMHAL_PRCM_PD_RM_OCCUR_GLOBAL_COLD_RESET */
        &PMHAL_PRCM_PD_RM_OCCUR_GLOBAL_COLD_RESET_rstctrlBitField
    },
    {   /* PMHAL_PRCM_PD_RM_OCCUR_GLOBAL_WARM_RESET */
        &PMHAL_PRCM_PD_RM_OCCUR_GLOBAL_WARM_RESET_rstctrlBitField
    }
};

/**
 *  \brief structure defining Status Register for
 *         PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST
 */
regBitFieldShift_t              PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST_rstStBitField
    =
    {
    (SOC_DEVICE_PRM_BASE + PRM_RSTST),
    PRM_RSTST_GLOBAL_COLD_RST_SHIFT
    };

/**
 *  \brief structure defining Status Register for
 *         PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST
 */
regBitFieldShift_t
    PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST_rstStBitField =
{
    (SOC_DEVICE_PRM_BASE + PRM_RSTST),
    PRM_RSTST_GLOBAL_WARM_SW_RST_SHIFT
};

/**
 *  \brief structure defining Status Register for
 *         PMHAL_PRCM_GLB_RG_EXTERNAL_WARM_RST
 */
regBitFieldShift_t
    PMHAL_PRCM_GLB_RG_EXTERNAL_WARM_RST_rstStBitField =
{
    (SOC_DEVICE_PRM_BASE + PRM_RSTST),
    PRM_RSTST_EXTERNAL_WARM_RST_SHIFT
};

/**
 *  \brief structure defining Status Register for
 *         PMHAL_PRCM_GLB_RG_ICEPICK_RST
 */
regBitFieldShift_t              PMHAL_PRCM_GLB_RG_ICEPICK_RST_rstStBitField =
{
    (SOC_DEVICE_PRM_BASE + PRM_RSTST),
    PRM_RSTST_ICEPICK_RST_SHIFT
};

/**
 *  \brief structure defining Status Register for
 *         PMHAL_PRCM_GLB_RG_TSHUT_CORE_RST
 */
regBitFieldShift_t              PMHAL_PRCM_GLB_RG_TSHUT_CORE_RST_rstStBitField
    =
    {
    (SOC_DEVICE_PRM_BASE + PRM_RSTST),
    PRM_RSTST_TSHUT_CORE_RST_SHIFT
    };

const pmhalGlobalResetStatus_t  pmhalGlobalResetStatusElems[] =
{
    {   /* PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST */
        &PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST_rstStBitField
    },
    {   /* PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST */
        &PMHAL_PRCM_GLB_RG_GLOBAL_WARM_SW_RST_rstStBitField
    },
    {   /* PMHAL_PRCM_GLB_RG_EXTERNAL_WARM_RST */
        &PMHAL_PRCM_GLB_RG_EXTERNAL_WARM_RST_rstStBitField
    },
    {   /* PMHAL_PRCM_GLB_RG_ICEPICK_RST */
        &PMHAL_PRCM_GLB_RG_ICEPICK_RST_rstStBitField
    },
    {   /* PMHAL_PRCM_GLB_RG_TSHUT_CORE_RST */
        &PMHAL_PRCM_GLB_RG_TSHUT_CORE_RST_rstStBitField
    }
};

/**
 *  \brief Structure defining Physical Memory Elements List
 */
const pmhalPhysicalMemory_t     pmhalPhysicalMemoryElems[] =
{
    {   /* PMHAL_PRCM_PHY_BANK_VIP */
        PM_CAM_PWRSTCTRL_VIP_BANK_ONSTATE_SHIFT,
        PMHAL_SHIFT_NOTAPPLICABLE,
        PM_CAM_PWRSTST_VIP_BANK_STATEST_SHIFT,
        (uint8_t) PMHAL_BANK_RET_UNDEF
    },
    {   /* PMHAL_PRCM_PHY_BANK_CORE_OTHER_BANK */
        PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_ONSTATE_SHIFT,
        PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_RETSTATE_SHIFT,
        PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_SHIFT,
        (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_ON)
    },
    {   /* PMHAL_PRCM_PHY_BANK_OCP_NRET_BANK */
        PM_CORE_PWRSTCTRL_OCP_NRET_BANK_ONSTATE_SHIFT,
        PM_CORE_PWRSTCTRL_OCP_NRET_BANK_RETSTATE_SHIFT,
        PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_SHIFT,
        (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_OFF)
    },
    {   /* PMHAL_PRCM_PHY_BANK_CORE_OCMRAM */
        PM_CORE_PWRSTCTRL_CORE_OCMRAM_ONSTATE_SHIFT,
        PM_CORE_PWRSTCTRL_CORE_OCMRAM_RETSTATE_SHIFT,
        PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_SHIFT,
        (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_ON)
    },
    {   /* PMHAL_PRCM_PHY_BANK_IPU_L2RAM */
        PM_CORE_PWRSTCTRL_IPU_L2RAM_ONSTATE_SHIFT,
        PM_CORE_PWRSTCTRL_IPU_L2RAM_RETSTATE_SHIFT,
        PM_CORE_PWRSTST_IPU_L2RAM_STATEST_SHIFT,
        (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_OFF)
    },
    {   /* PMHAL_PRCM_PHY_BANK_IPU_UNICACHE */
        PM_CORE_PWRSTCTRL_IPU_UNICACHE_ONSTATE_SHIFT,
        PM_CORE_PWRSTCTRL_IPU_UNICACHE_RETSTATE_SHIFT,
        PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_SHIFT,
        (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_OFF)
    },
    {   /* PMHAL_PRCM_PHY_BANK_DSP1_EDMA */
        PM_DSP1_PWRSTCTRL_DSP1_EDMA_ONSTATE_SHIFT,
        PMHAL_SHIFT_NOTAPPLICABLE,
        PM_DSP1_PWRSTST_DSP1_EDMA_STATEST_SHIFT,
        (uint8_t) PMHAL_BANK_RET_UNDEF
    },
    {   /* PMHAL_PRCM_PHY_BANK_DSP1_L1 */
        PM_DSP1_PWRSTCTRL_DSP1_L1_ONSTATE_SHIFT,
        PMHAL_SHIFT_NOTAPPLICABLE,
        PM_DSP1_PWRSTST_DSP1_L1_STATEST_SHIFT,
        (uint8_t) PMHAL_BANK_RET_UNDEF
    },
    {   /* PMHAL_PRCM_PHY_BANK_DSP1_L2 */
        PM_DSP1_PWRSTCTRL_DSP1_L2_ONSTATE_SHIFT,
        PMHAL_SHIFT_NOTAPPLICABLE,
        PM_DSP1_PWRSTST_DSP1_L2_STATEST_SHIFT,
        (uint8_t) PMHAL_BANK_RET_UNDEF
    },
    {   /* PMHAL_PRCM_PHY_BANK_DSP2_EDMA */
        PM_DSP2_PWRSTCTRL_DSP2_EDMA_ONSTATE_SHIFT,
        PMHAL_SHIFT_NOTAPPLICABLE,
        PM_DSP2_PWRSTST_DSP2_EDMA_STATEST_SHIFT,
        (uint8_t) PMHAL_BANK_RET_UNDEF
    },
    {   /* PMHAL_PRCM_PHY_BANK_DSP2_L1 */
        PM_DSP2_PWRSTCTRL_DSP2_L1_ONSTATE_SHIFT,
        PMHAL_SHIFT_NOTAPPLICABLE,
        PM_DSP2_PWRSTST_DSP2_L1_STATEST_SHIFT,
        (uint8_t) PMHAL_BANK_RET_UNDEF
    },
    {   /* PMHAL_PRCM_PHY_BANK_DSP2_L2 */
        PM_DSP2_PWRSTCTRL_DSP2_L2_ONSTATE_SHIFT,
        PMHAL_SHIFT_NOTAPPLICABLE,
        PM_DSP2_PWRSTST_DSP2_L2_STATEST_SHIFT,
        (uint8_t) PMHAL_BANK_RET_UNDEF
    },
    {   /* PMHAL_PRCM_PHY_BANK_DSS_MEM */
        PM_DSS_PWRSTCTRL_DSS_MEM_ONSTATE_SHIFT,
        PM_DSS_PWRSTCTRL_DSS_MEM_RETSTATE_SHIFT,
        PM_DSS_PWRSTST_DSS_MEM_STATEST_SHIFT,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_OFF))
    },
    {   /* PMHAL_PRCM_PHY_BANK_EMU_BANK */
        PM_EMU_PWRSTCTRL_EMU_BANK_ONSTATE_SHIFT,
        PMHAL_SHIFT_NOTAPPLICABLE,
        PM_EMU_PWRSTST_EMU_BANK_STATEST_SHIFT,
        (uint8_t) PMHAL_BANK_RET_UNDEF
    },
    {   /* PMHAL_PRCM_PHY_BANK_EVE1_BANK */
        PM_EVE1_PWRSTCTRL_EVE1_BANK_ONSTATE_SHIFT,
        PMHAL_SHIFT_NOTAPPLICABLE,
        PM_EVE1_PWRSTST_EVE1_BANK_STATEST_SHIFT,
        (uint8_t) PMHAL_BANK_RET_UNDEF
    },
    {   /* PMHAL_PRCM_PHY_BANK_AESSMEM */
        PM_IPU_PWRSTCTRL_AESSMEM_ONSTATE_SHIFT,
        PM_IPU_PWRSTCTRL_AESSMEM_RETSTATE_SHIFT,
        PM_IPU_PWRSTST_AESSMEM_STATEST_SHIFT,
        (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_OFF)
    },
    {   /* PMHAL_PRCM_PHY_BANK_PERIPHMEM */
        PM_IPU_PWRSTCTRL_PERIPHMEM_ONSTATE_SHIFT,
        PM_IPU_PWRSTCTRL_PERIPHMEM_RETSTATE_SHIFT,
        PM_IPU_PWRSTST_PERIPHMEM_STATEST_SHIFT,
        (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_OFF)
    },
    {   /* PMHAL_PRCM_PHY_BANK_L3INIT_BANK1 */
        PM_L3INIT_PWRSTCTRL_L3INIT_BANK1_ONSTATE_SHIFT,
        PM_L3INIT_PWRSTCTRL_L3INIT_BANK1_RETSTATE_SHIFT,
        PM_L3INIT_PWRSTST_L3INIT_BANK1_STATEST_SHIFT,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_OFF))
    },
    {   /* PMHAL_PRCM_PHY_BANK_L3INIT_BANK2 */
        PM_L3INIT_PWRSTCTRL_L3INIT_BANK2_ONSTATE_SHIFT,
        PM_L3INIT_PWRSTCTRL_L3INIT_BANK2_RETSTATE_SHIFT,
        PM_L3INIT_PWRSTST_L3INIT_BANK2_STATEST_SHIFT,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_ON))
    },
    {   /* PMHAL_PRCM_PHY_BANK_GMAC_BANK */
        PM_L3INIT_PWRSTCTRL_GMAC_BANK_ONSTATE_SHIFT,
        PM_L3INIT_PWRSTCTRL_GMAC_BANK_RETSTATE_SHIFT,
        PM_L3INIT_PWRSTST_L3INIT_GMAC_STATEST_SHIFT,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_ON))
    },
    {   /* PMHAL_PRCM_PHY_BANK_RETAINED_BANK */
        PM_L4PER_PWRSTCTRL_RETAINED_BANK_ONSTATE_SHIFT,
        PM_L4PER_PWRSTCTRL_RETAINED_BANK_RETSTATE_SHIFT,
        PM_L4PER_PWRSTST_RETAINED_BANK_STATEST_SHIFT,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_ON))
    },
    {   /* PMHAL_PRCM_PHY_BANK_NONRETAINED_BANK */
        PM_L4PER_PWRSTCTRL_NONRETAINED_BANK_ONSTATE_SHIFT,
        PM_L4PER_PWRSTCTRL_NONRETAINED_BANK_RETSTATE_SHIFT,
        PM_L4PER_PWRSTST_NONRETAINED_BANK_STATEST_SHIFT,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_OFF))
    },
    {   /* PMHAL_PRCM_PHY_BANK_ISS_BANK */
        PM_ISS_PWRSTCTRL_ISS_BANK_ONSTATE_SHIFT,
        PM_ISS_PWRSTCTRL_ISS_BANK_RETSTATE_SHIFT,
        PM_ISS_PWRSTST_ISS_BANK_STATEST_SHIFT,
        (uint8_t) ((uint32_t) 1U << (uint32_t) PMHAL_BANK_RET_OFF)
    },
    {   /* PMHAL_PRCM_PHY_BANK_WKUP_BANK */
        PMHAL_SHIFT_NOTAPPLICABLE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_BANK_RET_UNDEF
    }
};

/**
 *  \brief structure defining PMHAL_PRCM_CD_CAM modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_CAM_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
    PMHAL_PRCM_MOD_VIP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_CRC modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_CRC_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CRC
    PMHAL_PRCM_MOD_CRC
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CRC */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_EMIF modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_EMIF_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
    PMHAL_PRCM_MOD_DLL,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    PMHAL_PRCM_MOD_EMIF1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_L3INSTR modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_L3INSTR_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
    PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING
    PMHAL_PRCM_MOD_DLL_AGING,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR
    PMHAL_PRCM_MOD_L3_INSTR,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
    PMHAL_PRCM_MOD_L3_MAIN_2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
    PMHAL_PRCM_MOD_OCP_WP_NOC
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_L3MAIN1 modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_L3MAIN1_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
    PMHAL_PRCM_MOD_GPMC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
    PMHAL_PRCM_MOD_L3_MAIN_1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    PMHAL_PRCM_MOD_OCMC_RAM1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
    PMHAL_PRCM_MOD_TESOC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
    PMHAL_PRCM_MOD_MMU_EDMA,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPCC
    PMHAL_PRCM_MOD_TPCC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPCC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC1
    PMHAL_PRCM_MOD_TPTC1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC2
    PMHAL_PRCM_MOD_TPTC2
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_L4CFG modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_L4CFG_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
    PMHAL_PRCM_MOD_L4_CFG,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    PMHAL_PRCM_MOD_MAILBOX1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    PMHAL_PRCM_MOD_MAILBOX2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    PMHAL_PRCM_MOD_SPINLOCK,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_COREAON modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_COREAON_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
    PMHAL_PRCM_MOD_SMARTREFLEX_CORE,
#else
    PMHAL_PRCM_MOD_UNDEF,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_CUSTEFUSE modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_CUSTEFUSE_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
    PMHAL_PRCM_MOD_EFUSE_CTRL_CUST,
#else
    PMHAL_PRCM_MOD_UNDEF,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_DSP1 modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_DSP1_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
    PMHAL_PRCM_MOD_DSP1
#else
    PMHAL_PRCM_MOD_UNDEF,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_DSP2 modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_DSP2_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
    PMHAL_PRCM_MOD_DSP2
#else
    PMHAL_PRCM_MOD_UNDEF,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_DSS modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_DSS_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    PMHAL_PRCM_MOD_DSS
#else
    PMHAL_PRCM_MOD_UNDEF,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_EMU modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_EMU_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    PMHAL_PRCM_MOD_DEBUG_LOGIC
#else
    PMHAL_PRCM_MOD_UNDEF,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_EVE1 modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_EVE1_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
    PMHAL_PRCM_MOD_EVE1
#else
    PMHAL_PRCM_MOD_UNDEF,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_IPU1 modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_IPU1_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
    PMHAL_PRCM_MOD_IPU1
#else
    PMHAL_PRCM_MOD_UNDEF,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_IPU modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_IPU_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
    PMHAL_PRCM_MOD_MCASP1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
    PMHAL_PRCM_MOD_TIMER5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
    PMHAL_PRCM_MOD_TIMER6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
    PMHAL_PRCM_MOD_TIMER7,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
    PMHAL_PRCM_MOD_TIMER8,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_GMAC modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_GMAC_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    PMHAL_PRCM_MOD_CPGMAC
#else
    PMHAL_PRCM_MOD_UNDEF,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_L3INIT modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_L3INIT_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
    PMHAL_PRCM_MOD_IEEE1500_2_OCP,
#else
    PMHAL_PRCM_MOD_UNDEF,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_L4PER2 modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_L4PER2_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
    PMHAL_PRCM_MOD_L4_PER2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
    PMHAL_PRCM_MOD_DCAN2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    PMHAL_PRCM_MOD_PWMSS1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
    PMHAL_PRCM_MOD_ADC,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    PMHAL_PRCM_MOD_QSPI
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_L4PER3 modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_L4PER3_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
    PMHAL_PRCM_MOD_L4_PER3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC1
    PMHAL_PRCM_MOD_DCC1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC2
    PMHAL_PRCM_MOD_DCC2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC3
    PMHAL_PRCM_MOD_DCC3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC4
    PMHAL_PRCM_MOD_DCC4
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC4 */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_L4PER modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_L4PER1_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
    PMHAL_PRCM_MOD_L4_PER1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    PMHAL_PRCM_MOD_I2C1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    PMHAL_PRCM_MOD_I2C2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
    PMHAL_PRCM_MOD_TIMER2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
    PMHAL_PRCM_MOD_TIMER3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
    PMHAL_PRCM_MOD_TIMER4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
    PMHAL_PRCM_MOD_MCSPI1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
    PMHAL_PRCM_MOD_MCSPI2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
    PMHAL_PRCM_MOD_MCSPI3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
    PMHAL_PRCM_MOD_MCSPI4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
    PMHAL_PRCM_MOD_UART1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
    PMHAL_PRCM_MOD_UART2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
    PMHAL_PRCM_MOD_UART3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    PMHAL_PRCM_MOD_ELM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    PMHAL_PRCM_MOD_MMC4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
    PMHAL_PRCM_MOD_GPIO2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
    PMHAL_PRCM_MOD_GPIO3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
    PMHAL_PRCM_MOD_GPIO4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
    PMHAL_PRCM_MOD_ESM,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC5
    PMHAL_PRCM_MOD_DCC5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC6
    PMHAL_PRCM_MOD_DCC6,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC7
    PMHAL_PRCM_MOD_DCC7
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC7 */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_ISS modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_ISS_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
    PMHAL_PRCM_MOD_ISS,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAMERARX
    PMHAL_PRCM_MOD_CAMERARX
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
};

/**
 *  \brief Structure defining PMHAL_PRCM_CD_WKUPAON modules
 */
pmhalPrcmModuleId_t             PMHAL_PRCM_CD_WKUPAON_modules[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
    PMHAL_PRCM_MOD_L4_WKUP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
    PMHAL_PRCM_MOD_GPIO1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
    PMHAL_PRCM_MOD_DCAN1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
    PMHAL_PRCM_MOD_TIMER1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
    PMHAL_PRCM_MOD_COUNTER_32K,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
    PMHAL_PRCM_MOD_CTRL_MODULE_WKUP,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI1
    PMHAL_PRCM_MOD_RTI1,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI2
    PMHAL_PRCM_MOD_RTI2,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI3
    PMHAL_PRCM_MOD_RTI3,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI4
    PMHAL_PRCM_MOD_RTI4,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI5
    PMHAL_PRCM_MOD_RTI5,
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI5 */
};

/**
 *  \brief Structure defining Clock Domain Elements
 */
const pmhalClkDomain_t          pmhalClockDomainElems[] =
{
    {   /* PMHAL_PRCM_CD_CAM */
        PMHAL_PRCM_PD_CAM,
        (SOC_CAM_CM_CORE_BASE + CM_CAM_CLKSTCTRL),
        PMHAL_PRCM_CD_CAM_modules,
        (SOC_CAM_CM_CORE_BASE + CM_CAM_STATICDEP),
        CM_DSP1_STATICDEP_CAM_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_CAM_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP))
    },
    {   /* PMHAL_PRCM_CD_CRC */
        PMHAL_PRCM_PD_CORE,
        (SOC_CORE_CM_CORE_BASE + CM_CRC_CLKSTCTRL),
        PMHAL_PRCM_CD_CRC_modules,
        PMHAL_REG_NOTAPPLICABLE,
        CM_DSP1_STATICDEP_CRC_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_CRC_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },

    {   /* PMHAL_PRCM_CD_EMIF */
        PMHAL_PRCM_PD_CORE,
        (SOC_CORE_CM_CORE_BASE + CM_EMIF_CLKSTCTRL),
        PMHAL_PRCM_CD_EMIF_modules,
        PMHAL_REG_NOTAPPLICABLE,
        CM_DSP1_STATICDEP_EMIF_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_EMIF_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },

    {   /* PMHAL_PRCM_CD_L3INSTR */
        PMHAL_PRCM_PD_CORE,
        (SOC_CORE_CM_CORE_BASE + CM_L3INSTR_CLKSTCTRL),
        PMHAL_PRCM_CD_L3INSTR_modules,
        PMHAL_REG_NOTAPPLICABLE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_CD_L3INSTR_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) ((uint32_t) 1U <<
                   (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO)
    },
    {   /* PMHAL_PRCM_CD_L3MAIN1 */
        PMHAL_PRCM_PD_CORE,
        (SOC_CORE_CM_CORE_BASE + CM_L3MAIN1_CLKSTCTRL),
        PMHAL_PRCM_CD_L3MAIN1_modules,
        PMHAL_REG_NOTAPPLICABLE,
        CM_DSP1_STATICDEP_L3MAIN1_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_L3MAIN1_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO))
    },
    {   /* PMHAL_PRCM_CD_L4CFG */
        PMHAL_PRCM_PD_CORE,
        (SOC_CORE_CM_CORE_BASE + CM_L4CFG_CLKSTCTRL),
        PMHAL_PRCM_CD_L4CFG_modules,
        PMHAL_REG_NOTAPPLICABLE,
        CM_DSP1_STATICDEP_L4CFG_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_L4CFG_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO))
    },
    {   /* PMHAL_PRCM_CD_COREAON */
        PMHAL_PRCM_PD_COREAON,
        (SOC_COREAON_CM_CORE_BASE + CM_COREAON_CLKSTCTRL),
        PMHAL_PRCM_CD_COREAON_modules,
        PMHAL_REG_NOTAPPLICABLE,
        CM_DSP1_STATICDEP_COREAON_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_COREAON_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },
    {   /* PMHAL_PRCM_CD_CUSTEFUSE */
        PMHAL_PRCM_PD_CUSTEFUSE,
        (SOC_CUSTEFUSE_CM_CORE_BASE + CM_CUSTEFUSE_CLKSTCTRL),
        PMHAL_PRCM_CD_CUSTEFUSE_modules,
        PMHAL_REG_NOTAPPLICABLE,
        CM_DSP1_STATICDEP_CUSTEFUSE_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_CUSTEFUSE_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },
    {   /* PMHAL_PRCM_CD_DSP1 */
        PMHAL_PRCM_PD_DSP1,
        (SOC_DSP1_CM_CORE_AON_BASE + CM_DSP1_CLKSTCTRL),
        PMHAL_PRCM_CD_DSP1_modules,
        (SOC_DSP1_CM_CORE_AON_BASE + CM_DSP1_STATICDEP),
        CM_DSP2_STATICDEP_DSP1_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_DSP1_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },
    {   /* PMHAL_PRCM_CD_DSP2 */
        PMHAL_PRCM_PD_DSP2,
        (SOC_DSP2_CM_CORE_AON_BASE + CM_DSP2_CLKSTCTRL),
        PMHAL_PRCM_CD_DSP2_modules,
        (SOC_DSP2_CM_CORE_AON_BASE + CM_DSP2_STATICDEP),
        CM_DSP1_STATICDEP_DSP2_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_DSP2_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },
    {   /* PMHAL_PRCM_CD_DSS */
        PMHAL_PRCM_PD_DSS,
        (SOC_DSS_CM_CORE_BASE + CM_DSS_CLKSTCTRL),
        PMHAL_PRCM_CD_DSS_modules,
        (SOC_DSS_CM_CORE_BASE + CM_DSS_STATICDEP),
        CM_DSP1_STATICDEP_DSS_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_DSS_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },
    {   /* PMHAL_PRCM_CD_EMU */
        PMHAL_PRCM_PD_EMU,
        (SOC_EMU_CM_BASE + CM_EMU_CLKSTCTRL),
        PMHAL_PRCM_CD_EMU_modules,
        PMHAL_REG_NOTAPPLICABLE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_CD_EMU_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },
    {   /* PMHAL_PRCM_CD_EVE1 */
        PMHAL_PRCM_PD_EVE1,
        (SOC_EVE1_CM_CORE_AON_BASE + CM_EVE1_CLKSTCTRL),
        PMHAL_PRCM_CD_EVE1_modules,
        (SOC_EVE1_CM_CORE_AON_BASE + CM_EVE1_STATICDEP),
        CM_DSP1_STATICDEP_EVE1_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_EVE1_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },
    {   /* PMHAL_PRCM_CD_IPU1 */
        PMHAL_PRCM_PD_IPU,
        (SOC_IPU_CM_CORE_AON_BASE + CM_IPU1_CLKSTCTRL),
        PMHAL_PRCM_CD_IPU1_modules,
        (SOC_IPU_CM_CORE_AON_BASE + CM_IPU1_STATICDEP),
        CM_DSP1_STATICDEP_IPU1_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_IPU1_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },
    {   /* PMHAL_PRCM_CD_IPU */
        PMHAL_PRCM_PD_IPU,
        (SOC_IPU_CM_CORE_AON_BASE + CM_IPU_CLKSTCTRL),
        PMHAL_PRCM_CD_IPU_modules,
        PMHAL_REG_NOTAPPLICABLE,
        CM_DSP1_STATICDEP_IPU_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_IPU_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },

    {   /* PMHAL_PRCM_CD_GMAC */
        PMHAL_PRCM_PD_L3INIT,
        (SOC_L3INIT_CM_CORE_BASE + CM_GMAC_CLKSTCTRL),
        PMHAL_PRCM_CD_GMAC_modules,
        (SOC_L3INIT_CM_CORE_BASE + CM_GMAC_STATICDEP),
        CM_DSP1_STATICDEP_GMAC_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_GMAC_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },
    {   /* PMHAL_PRCM_CD_L3INIT */
        PMHAL_PRCM_PD_L3INIT,
        (SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_CLKSTCTRL),
        PMHAL_PRCM_CD_L3INIT_modules,
        (SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_STATICDEP),
        CM_DSP1_STATICDEP_L3INIT_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_L3INIT_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    },
    {   /* PMHAL_PRCM_CD_L4PER2 */
        PMHAL_PRCM_PD_L4PER,
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_CLKSTCTRL),
        PMHAL_PRCM_CD_L4PER2_modules,
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_STATICDEP),
        CM_DSP1_STATICDEP_L4PER2_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_L4PER2_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP))
    },
    {   /* PMHAL_PRCM_CD_L4PER3 */
        PMHAL_PRCM_PD_L4PER,
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER3_CLKSTCTRL),
        PMHAL_PRCM_CD_L4PER3_modules,
        PMHAL_REG_NOTAPPLICABLE,
        CM_DSP1_STATICDEP_L4PER3_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_L4PER3_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP))
    },
    {   /* PMHAL_PRCM_CD_L4PER1 */
        PMHAL_PRCM_PD_L4PER,
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_CLKSTCTRL),
        PMHAL_PRCM_CD_L4PER1_modules,
        PMHAL_REG_NOTAPPLICABLE,
        CM_DSP1_STATICDEP_L4PER_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_L4PER1_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP))
    },
    {   /* PMHAL_PRCM_CD_MMAON */
        PMHAL_PRCM_PD_MMAON,
        PMHAL_REG_NOTAPPLICABLE,
        NULL,
        PMHAL_REG_NOTAPPLICABLE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        0,
        (uint8_t) ((uint32_t) 1U <<
                   (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP)
    },
    {   /* PMHAL_PRCM_CD_ISS */
        PMHAL_PRCM_PD_ISS,
        (SOC_VPE_CM_CORE_AON_BASE + CM_ISS_CLKSTCTRL),
        PMHAL_PRCM_CD_ISS_modules,
        (SOC_VPE_CM_CORE_AON_BASE + CM_ISS_STATICDEP),
        CM_DSP1_STATICDEP_ISS_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_ISS_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_SLEEP))
    },
    {   /* PMHAL_PRCM_CD_WKUPAON */
        PMHAL_PRCM_PD_WKUPAON,
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_CLKSTCTRL),
        PMHAL_PRCM_CD_WKUPAON_modules,
        PMHAL_REG_NOTAPPLICABLE,
        CM_DSP1_STATICDEP_WKUPAON_STATDEP_SHIFT,
        VSIZE_TYPE(PMHAL_PRCM_CD_WKUPAON_modules,
                   pmhalPrcmModuleId_t),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_HW_AUTO) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_NO_SLEEP) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_CD_CLKTRNMODES_SW_WAKEUP))
    }
};

#ifdef BUILDCFG_PMHAL_PRCM_MOD_CRC
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_CRC
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_CRC_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_CRC_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_CRC_CLKSTCTRL_CLKACTIVITY_CRC_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CRC */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_SMARTREFLEX_CORE
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_SMARTREFLEX_CORE_ClkSelectCfg[]
    =
    {
    {PMHAL_PRCM_CLK_SR_CORE_SYS_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_CORE_SYS_GFCLK_SHIFT},
    };
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_ClkSelectCfg
[] =
{
    {PMHAL_PRCM_CLK_SR_DSPEVE_SYS_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_COREAON_CLKSTCTRL_CLKACTIVITY_SR_DSPEVE_SYS_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_CUSTEFUSE_SYS_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_CUSTEFUSE_CLKSTCTRL_CLKACTIVITY_CUSTEFUSE_SYS_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DSP1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DSP1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_DSP1_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_DSP1_CLKSTCTRL_CLKACTIVITY_DSP1_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DSP2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DSP2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_DSP2_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_DSP2_CLKSTCTRL_CLKACTIVITY_DSP2_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DSS
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DSS_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_HDMI_CEC_GFCLK,
     CM_DSS_DSS_CLKCTRL_OPTFCLKEN_32KHZ_CLK_SHIFT,
     CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_CEC_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_HDMI_PHY_GFCLK,
     CM_DSS_DSS_CLKCTRL_OPTFCLKEN_48MHZ_CLK_SHIFT,
     CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_PHY_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_DSS_GFCLK,
     CM_DSS_DSS_CLKCTRL_OPTFCLKEN_DSSCLK_SHIFT,
     CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_HDMI_DPLL_CLK,
     CM_DSS_DSS_CLKCTRL_OPTFCLKEN_HDMI_CLK_SHIFT,
     CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_DPLL_CLK_SHIFT},
    {PMHAL_PRCM_CLK_VIDEO1_DPLL_CLK,
     CM_DSS_DSS_CLKCTRL_OPTFCLKEN_VIDEO1_CLK_SHIFT,
     CM_DSS_CLKSTCTRL_CLKACTIVITY_VIDEO1_DPLL_CLK_SHIFT},
    {PMHAL_PRCM_CLK_VIDEO2_DPLL_CLK,
     CM_DSS_DSS_CLKCTRL_OPTFCLKEN_VIDEO2_CLK_SHIFT,
     CM_DSS_CLKSTCTRL_CLKACTIVITY_VIDEO2_DPLL_CLK_SHIFT},
    {PMHAL_PRCM_CLK_VID_PIX_CLK,
     CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_EN_SHIFT,
     CTRL_CORE_SEC_PRCM_CLKDIV_CONTROL2_VID_PIX_CLK_HSDIV_EN_ACK_SHIFT}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DLL
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DLL_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_EMIF_DLL_GCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_DLL_GCLK_SHIFT}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_EMIF1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_EMIF1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_EMIF_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_EMIF_DLL_GCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_DLL_GCLK_SHIFT},
    {PMHAL_PRCM_CLK_EMIF_PHY_GCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_PHY_GCLK_SHIFT}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_EVE1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_EVE1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_EVE1_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_EVE1_CLKSTCTRL_CLKACTIVITY_EVE1_GFCLK_SHIFT}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_CPGMAC
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_CPGMAC_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_GMAC_RFT_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMAC_RFT_CLK_SHIFT},
    {PMHAL_PRCM_CLK_GMAC_MAIN_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMAC_MAIN_CLK_SHIFT},
    {PMHAL_PRCM_CLK_GMII_250MHZ_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_GMAC_CLKSTCTRL_CLKACTIVITY_GMII_250MHZ_CLK_SHIFT},
    {PMHAL_PRCM_CLK_RMII_50MHZ_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_GMAC_CLKSTCTRL_CLKACTIVITY_RMII_50MHZ_CLK_SHIFT},
    {PMHAL_PRCM_CLK_RGMII_5MHZ_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_GMAC_CLKSTCTRL_CLKACTIVITY_RGMII_5MHZ_CLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MCASP1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_MCASP1_AHCLKR,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_IPU_CLKSTCTRL_CLKACTIVITY_MCASP1_AHCLKR_SHIFT},
    {PMHAL_PRCM_CLK_MCASP1_AHCLKX,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_IPU_CLKSTCTRL_CLKACTIVITY_MCASP1_AHCLKX_SHIFT},
    {PMHAL_PRCM_CLK_MCASP1_AUX_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_IPU_CLKSTCTRL_CLKACTIVITY_MCASP1_AUX_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TIMER5
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TIMER5_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_TIMER5_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_IPU_CLKSTCTRL_CLKACTIVITY_TIMER5_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TIMER6
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TIMER6_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_TIMER6_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_IPU_CLKSTCTRL_CLKACTIVITY_TIMER6_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TIMER7
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TIMER7_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_TIMER7_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_IPU_CLKSTCTRL_CLKACTIVITY_TIMER7_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TIMER8
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TIMER8_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_TIMER8_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_IPU_CLKSTCTRL_CLKACTIVITY_TIMER8_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_IPU1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_IPU1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_IPU1_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_IPU1_CLKSTCTRL_CLKACTIVITY_IPU1_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_IEEE1500_2_OCP
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_IEEE1500_2_OCP_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3INIT_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3INIT_CLKSTCTRL_CLKACTIVITY_L3INIT_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP_ClkSelectCfg
[] =
{
    {PMHAL_PRCM_CLK_L3INSTR_TS_GCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_TS_GCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DLL_AGING
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DLL_AGING_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3INSTR_DLL_AGING_GCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_DLL_AGING_GCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_L3_INSTR
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_L3_INSTR_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_L3_MAIN_2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_L3_MAIN_2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_OCP_WP_NOC
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_OCP_WP_NOC_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3INSTR_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_GPMC
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_GPMC_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_L3_MAIN_1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_L3_MAIN_1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_MMU_EDMA
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MMU_EDMA_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_OCMC_RAM1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_OCMC_RAM1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TESOC
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TESOC_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_TESOC_EXT_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPCC
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TPCC
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TPCC_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPCC */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TPTC1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TPTC1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TPTC2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TPTC2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L3MAIN1_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L3MAIN1_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_L4_CFG
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_L4_CFG_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_SPINLOCK
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_SPINLOCK_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_MAILBOX1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MAILBOX1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_MAILBOX2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MAILBOX2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4CFG_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4CFG_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_I2C1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_I2C1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_PER_96M_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_PER_96M_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_I2C2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_I2C2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_PER_96M_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_PER_96M_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_L4_PER1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_L4_PER1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC6
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DCC6
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DCC6_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC6 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC7
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DCC7
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DCC7_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC7 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TIMER2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TIMER2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_TIMER2_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_TIMER2_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TIMER3
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TIMER3_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_TIMER3_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_TIMER3_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TIMER4
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TIMER4_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_TIMER4_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_TIMER4_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC5
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DCC5
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DCC5_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC5 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_ELM
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_ELM_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_ESM
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_ESM_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_MCSPI1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MCSPI1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_PER_48M_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_PER_48M_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_MCSPI2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MCSPI2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_PER_48M_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_PER_48M_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_MCSPI3
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MCSPI3_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_PER_48M_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_PER_48M_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_MCSPI4
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MCSPI4_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_PER_48M_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_PER_48M_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_UART1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_UART1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_UART1_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_UART1_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_UART2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_UART2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_UART2_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_UART2_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_UART3
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_UART3_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_UART3_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_UART3_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_GPIO2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_GPIO2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_GPIO_GFCLK,
     CM_L4PER_GPIO2_CLKCTRL_OPTFCLKEN_DBCLK_SHIFT,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_GPIO_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_GPIO3
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_GPIO3_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_GPIO_GFCLK,
     CM_L4PER_GPIO3_CLKCTRL_OPTFCLKEN_DBCLK_SHIFT,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_GPIO_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_GPIO4
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_GPIO4_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_GPIO_GFCLK,
     CM_L4PER_GPIO4_CLKCTRL_OPTFCLKEN_DBCLK_SHIFT,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_GPIO_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_MMC4
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MMC4_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_MMC4_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_MMC4_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER_32K_GFCLK,
     CM_L4PER_MMC4_CLKCTRL_OPTFCLKEN_CLK32K_SHIFT,
     CM_L4PER_CLKSTCTRL_CLKACTIVITY_L4PER_32K_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DCAN2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DCAN2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_DCAN2_SYS_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_DCAN2_SYS_CLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_L4PER2_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_L4_PER2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_L4_PER2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_L4PER2_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_ADC
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_ADC_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER2_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_L4PER2_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_ADC_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_ADC_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_PWMSS1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_PWMSS1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_L4PER2_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_QSPI
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_QSPI_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_L4PER2_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_QSPI_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_QSPI_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_L4_PER3
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_L4_PER3_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER3_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER3_CLKSTCTRL_CLKACTIVITY_L4PER3_L3_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DCC1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DCC1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER3_CLKSTCTRL_CLKACTIVITY_L4PER3_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DCC2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DCC2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER3_CLKSTCTRL_CLKACTIVITY_L4PER3_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC3
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DCC3
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DCC3_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER3_CLKSTCTRL_CLKACTIVITY_L4PER3_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC3 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC4
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DCC4
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DCC4_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER3_L4_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER3_CLKSTCTRL_CLKACTIVITY_L4PER3_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC4 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_VIP1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_VIP1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_VIP1_GCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP1_GCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_ISS
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_ISS_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_ISS_GCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_ISS_CLKSTCTRL_CLKACTIVITY_ISS_GCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DEBUG_LOGIC
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DEBUG_LOGIC_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_EMU_SYS_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_EMU_CLKSTCTRL_CLKACTIVITY_EMU_SYS_CLK_SHIFT},
    {PMHAL_PRCM_CLK_DEBUG_ATB_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_DEBUG_TREXCPT_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_DEBUG_STMEXPT_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_COUNTER_32K
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_COUNTER_32K_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_FUNC_32K_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE},
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_CTRL_MODULE_WKUP_ClkSelectCfg[]
    =
    {
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT},
    };
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_DCAN1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_DCAN1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_DCAN1_SYS_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_SYS_CLK_SHIFT},
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_GPIO1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_GPIO1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_WKUPAON_SYS_GFCLK,
     CM_WKUPAON_GPIO1_CLKCTRL_OPTFCLKEN_DBCLK_SHIFT,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_SYS_GFCLK_SHIFT},
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_L4_WKUP
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_L4_WKUP_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_TIMER1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_TIMER1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_TIMER1_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_TIMER1_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI1
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_RTI1
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_RTI1_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_RTI1_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI1 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI2
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_RTI2
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_RTI2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_RTI2_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI2 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI3
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_RTI3
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_RTI3_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_RTI3_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI3 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI4
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_RTI4
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_RTI4_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_RTI4_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI4 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI5
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_RTI5
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_RTI5_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_WKUPAON_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_WKUPAON_CLKSTCTRL_CLKACTIVITY_WKUPAON_GICLK_SHIFT},
    {PMHAL_PRCM_CLK_RTI5_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI5 */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAMERARX
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_CAMERARX
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_CAMERARX_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_ISS_GCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_ISS_CLKSTCTRL_CLKACTIVITY_ISS_GCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CAMERARX */

#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_MCAN
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MCAN_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_MCAN_CLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_DCAN2_SYS_CLK_SHIFT},
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_L4PER2_L3_GICLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
/**
 *  \brief structure defining Clock Select Configuration for
 *          PMHAL_PRCM_MOD_ATL
 *          [TODO]: ATL can take in 3 clocks. Need to find
 *                  what else is connected in SR2.0.
 */
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_ATL_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_L4PER2_L3_GICLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_L4PER2_L3_GICLK_SHIFT}
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MCASP2_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_MCASP2_AHCLKR,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_MCASP6_AHCLKX_SHIFT},
    {PMHAL_PRCM_CLK_MCASP2_AHCLKX,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_MCASP4_AHCLKX_SHIFT},
    {PMHAL_PRCM_CLK_MCASP2_AUX_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_MCASP4_AUX_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
pmhalClockSelConfig_t           PMHAL_PRCM_MOD_MCASP3_ClkSelectCfg[] =
{
    {PMHAL_PRCM_CLK_MCASP3_AHCLKR,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_MCASP7_AHCLKX_SHIFT},
    {PMHAL_PRCM_CLK_MCASP3_AHCLKX,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_MCASP5_AHCLKX_SHIFT},
    {PMHAL_PRCM_CLK_MCASP3_AUX_GFCLK,
     PMHAL_CLKSELCTRL_NOTAPPLICABLE,
     CM_L4PER2_CLKSTCTRL_CLKACTIVITY_MCASP5_AUX_GFCLK_SHIFT},
};
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
/**
 *  \brief Structure defining SysConfig Elements
 */
const pmhalSysConfig_t          pmhalSysConfigElems[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
    {   /* PMHAL_PRCM_MOD_DSP1 */
        (SOC_DSP1_SYSTEM_BASE + DSP_SYSCONFIG),
        DSP_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        SYSCONFIG_STANDBYMODE_SHIFT,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY_WAKEUP_CAPABLE)),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /*BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
    {   /* PMHAL_PRCM_MOD_DSP2 */
        (SOC_DSP2_SYSTEM_BASE + DSP_SYSCONFIG),
        DSP_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        SYSCONFIG_STANDBYMODE_SHIFT,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY_WAKEUP_CAPABLE)),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /*BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    {   /* PMHAL_PRCM_MOD_DSS */
        (SOC_DISPC_COMMON_BASE + DSS_DISPC_SYSCONFIG),
        DSS_DISPC_SYSCONFIG_SIDLEMODE_SHIFT,
        TRUE,
        DSS_DISPC_SYSCONFIG_MIDLEMODE_SHIFT,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY)),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /*BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILD_C66X
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
    {   /* PMHAL_PRCM_MOD_EVE1 */
        (SOC_EVE1_EVE_CONTROL_BASE + EVE_SYSCONFIG),
        EVE_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        SYSCONFIG_STANDBYMODE_SHIFT,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY_WAKEUP_CAPABLE)),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
    {   /* PMHAL_PRCM_MOD_GPMC */
        (SOC_GPMC_CONF_REGS_BASE + GPMC_SYSCONFIG),
        GPMC_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#ifdef BUILD_C66X
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
    {   /* PMHAL_PRCM_MOD_MMU_EDMA */
        (SOC_MMU_BASE + MMU_SYSCONFIG),
        MMU_SYSCONFIG_IDLEMODE_SHIFT,
        TRUE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#endif
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    {   /* PMHAL_PRCM_MOD_OCMC_RAM1 */
        (SOC_OCMC_RAM1_CFG_BASE + OCMC_RAM_OCMC_SYSCONFIG_PM),
        OCMC_RAM_OCMC_SYSCONFIG_PM_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
    {   /* PMHAL_PRCM_MOD_TESOC */
        (SOC_TESOC_BASE + TESOC_IP_SYSCONFIG),
        PMHAL_SHIFT_NOTAPPLICABLE,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    {   /* PMHAL_PRCM_MOD_SPINLOCK */
        (SOC_SPINLOCK_BASE + SPINLOCK_SYSCONFIG),
        SPINLOCK_SYSCONFIG_SIDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    {   /* PMHAL_PRCM_MOD_MAILBOX1 */
        (SOC_MAILBOX1_BASE + MAILBOX_SYSCONFIG),
        MAILBOX_SYSCONFIG_SIDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    {   /* PMHAL_PRCM_MOD_MAILBOX2 */
        (SOC_MAILBOX2_BASE + MAILBOX_SYSCONFIG),
        MAILBOX_SYSCONFIG_SIDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    {   /* PMHAL_PRCM_MOD_I2C1 */
        (SOC_I2C1_BASE + I2C_SYSC),
        I2C_SYSC_IDLEMODE_SHIFT,
        TRUE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    {   /* PMHAL_PRCM_MOD_I2C2 */
        (SOC_I2C2_BASE + I2C_SYSC),
        I2C_SYSC_IDLEMODE_SHIFT,
        TRUE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
    {   /* PMHAL_PRCM_MOD_MCSPI1 */
        (SOC_MCSPI1_BASE + MCSPI_SYSCONFIG),
        MCSPI_SYSCONFIG_SIDLEMODE_SHIFT,
        TRUE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
    {   /* PMHAL_PRCM_MOD_MCSPI2 */
        (SOC_MCSPI2_BASE + MCSPI_SYSCONFIG),
        MCSPI_SYSCONFIG_SIDLEMODE_SHIFT,
        TRUE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
    {   /* PMHAL_PRCM_MOD_MCSPI3 */
        (SOC_MCSPI3_BASE + MCSPI_SYSCONFIG),
        MCSPI_SYSCONFIG_SIDLEMODE_SHIFT,
        TRUE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
    {   /* PMHAL_PRCM_MOD_MCSPI4 */
        (SOC_MCSPI4_BASE + MCSPI_SYSCONFIG),
        MCSPI_SYSCONFIG_SIDLEMODE_SHIFT,
        TRUE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
    {   /* PMHAL_PRCM_MOD_UART1 */
        (SOC_UART1_BASE + UART_SYSC),
        UART_SYSC_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
    {   /* PMHAL_PRCM_MOD_UART2 */
        (SOC_UART2_BASE + UART_SYSC),
        UART_SYSC_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
    {   /* PMHAL_PRCM_MOD_UART3 */
        (SOC_UART3_BASE + UART_SYSC),
        UART_SYSC_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
    {   /* PMHAL_PRCM_MOD_GPIO1 */
        (SOC_GPIO1_BASE + GPIO_SYSCONFIG),
        GPIO_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
    {   /* PMHAL_PRCM_MOD_GPIO2 */
        (SOC_GPIO2_BASE + GPIO_SYSCONFIG),
        GPIO_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
    {   /* PMHAL_PRCM_MOD_GPIO3 */
        (SOC_GPIO3_BASE + GPIO_SYSCONFIG),
        GPIO_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
    {   /* PMHAL_PRCM_MOD_GPIO4 */
        (SOC_GPIO4_BASE + GPIO_SYSCONFIG),
        GPIO_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    {   /* PMHAL_PRCM_MOD_QSPI */
        (SOC_QSPI_ADDRSP0_BASE + QSPI_SYSCONFIG),
        QSPI_SYSCONFIG_IDLE_MODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
    {   /* PMHAL_PRCM_MOD_VIP1 */
        (SOC_VIP1_VIP_REGS_BASE + VIP_SYSCONFIG),
        VIP_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        SYSCONFIG_STANDBYMODE_SHIFT,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY)),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
    {   /* PMHAL_PRCM_MOD_ISS */
        (SOC_ISS_REGS_BASE + ISS_HL_SYSCONFIG),
        ISS_HL_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        SYSCONFIG_STANDBYMODE_SHIFT,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY_WAKEUP_CAPABLE)),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
    {   /* PMHAL_PRCM_MOD_COUNTER_32K */
        (SOC_COUNTER_32K_BASE + COUNTER_32K_SYSCONFIG),
        COUNTER_32K_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    {   /* PMHAL_PRCM_MOD_ELM */
        (SOC_ELM_BASE + ELM_SYSCONFIG),
        ELM_SYSCONFIG_SIDLEMODE_SHIFT,
        TRUE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
    {
        PMHAL_REG_NOTAPPLICABLE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) PMHAL_PRCM_MODULE_SIDLEMODE_INVALID
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    {
        (SOC_PWMSS1_IPWMSS_BASE + PWMSS_SYSCONFIG),
        PWMSS_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    {
        (SOC_MMC4_BASE + MMC_SYSCONFIG),
        MMC_SYSCONFIG_SIDLEMODE_SHIFT,
        FALSE,
        MMC_SYSCONFIG_STANDBYMODE_SHIFT,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY)),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t)
                    PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE_WAKEUP_CAPABLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
    {   /* PMHAL_PRCM_MOD_MCASP1 */
        (SOC_MCASP1_CFG_BASE + MCASP_PWRIDLESYSCONFIG),
        MCASP_PWRIDLESYSCONFIG_IDLE_MODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifndef __TI_ARM_V7M4__
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC1
    {
        (SOC_DSP1_EDMA_TC0_BASE + EDMA_TC_SYSCONFIG),
        EDMA_TC_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        EDMA_TC_SYSCONFIG_STANDBYMODE_SHIFT,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY)),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC2
    {
        (SOC_DSP1_EDMA_TC1_BASE + EDMA_TC_SYSCONFIG),
        EDMA_TC_SYSCONFIG_IDLEMODE_SHIFT,
        FALSE,
        EDMA_TC_SYSCONFIG_STANDBYMODE_SHIFT,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_SMART_STANDBY)),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */
#endif /* __TI_ARM_V7M4__ */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
    {   /* PMHAL_PRCM_MOD_MCASP2 */
        (SOC_MCASP2_CFG_BASE + MCASP_PWRIDLESYSCONFIG),
        MCASP_PWRIDLESYSCONFIG_IDLE_MODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
    {   /* PMHAL_PRCM_MOD_MCASP3 */
        (SOC_MCASP3_CFG_BASE + MCASP_PWRIDLESYSCONFIG),
        MCASP_PWRIDLESYSCONFIG_IDLE_MODE_SHIFT,
        FALSE,
        PMHAL_SHIFT_NOTAPPLICABLE,
        (uint8_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_INVALID,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_SMART_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    {   /* PMHAL_PRCM_MOD_CPGMAC */
        (SOC_GMAC_WR_BASE + CPSW_WR_CTRL),
        CPSW_WR_CTRL_MMR_IDLEMODE_SHIFT,
        FALSE,
        CPSW_WR_CTRL_MMR_STDBYMODE_SHIFT,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_FORCE_STANDBY) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MSTANDBYMODE_NO_STANDBY)),
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_FORCE_IDLE) |
                   ((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_SIDLEMODE_NO_IDLE))
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
};

/**
 *  \brief Structure defining Module Elements List
 */
const pmhalModule_t             pmhalModuleElems[] =
{
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CRC
    {   /* PMHAL_PRCM_MOD_CRC */
        PMHAL_PRCM_CD_CRC,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_CRC_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_CRC_CRC_CLKCTRL),
        PMHAL_PRCM_MOD_CRC_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CRC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE
    { /* PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
        PMHAL_PRCM_CD_COREAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_CORE_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_COREAON_CM_CORE_BASE + CM_COREAON_SMARTREFLEX_CORE_CLKCTRL),
        PMHAL_PRCM_MOD_SMARTREFLEX_CORE_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_SMARTREFLEX_CORE,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_CORE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE
    { /* PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
        PMHAL_PRCM_CD_COREAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_COREAON_CM_CORE_BASE + CM_COREAON_SMARTREFLEX_DSPEVE_CLKCTRL),
        PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_SMARTREFLEX_DSPEVE,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SMARTREFLEX_DSPEVE */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST
    { /* PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
        PMHAL_PRCM_CD_CUSTEFUSE,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CUSTEFUSE_CM_CORE_BASE + CM_CUSTEFUSE_EFUSE_CTRL_CUST_CLKCTRL),
        PMHAL_PRCM_MOD_EFUSE_CTRL_CUST_ClkSelectCfg,
        FALSE,
        (uint8_t) ((uint32_t) 1U <<
                   (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED),
        PMHAL_EDGE_MOD_EFUSE_CTRL_CUST,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EFUSE_CTRL_CUST */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP1
    { /* PMHAL_PRCM_MOD_DSP1 */
        PMHAL_PRCM_CD_DSP1,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_DSP1,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DSP1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_DSP1_CM_CORE_AON_BASE + CM_DSP1_DSP1_CLKCTRL),
        PMHAL_PRCM_MOD_DSP1_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_DSP
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSP2
    {   /* PMHAL_PRCM_MOD_DSP2 */
        PMHAL_PRCM_CD_DSP2,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_DSP2,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DSP2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_DSP2_CM_CORE_AON_BASE + CM_DSP2_DSP2_CLKCTRL),
        PMHAL_PRCM_MOD_DSP2_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_DSP
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DSS
    { /* PMHAL_PRCM_MOD_DSS */
        PMHAL_PRCM_CD_DSS,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_DSS,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DSS_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_DSS_CM_CORE_BASE + CM_DSS_DSS_CLKCTRL),
        PMHAL_PRCM_MOD_DSS_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_DSS,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DSS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL
    { /* PMHAL_PRCM_MOD_DLL */
        PMHAL_PRCM_CD_EMIF,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DLL_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_EMIF_EMIF_DLL_CLKCTRL),
        PMHAL_PRCM_MOD_DLL_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EMIF1
    { /* PMHAL_PRCM_MOD_EMIF1 */
        PMHAL_PRCM_CD_EMIF,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_EMIF1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_EMIF_EMIF1_CLKCTRL),
        PMHAL_PRCM_MOD_EMIF1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_EMIF1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EMIF1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_EVE1
    {   /* PMHAL_PRCM_MOD_EVE1 */
        PMHAL_PRCM_CD_EVE1,
        PMHAL_PRCM_RT_NO_RETENTION,
#ifdef BUILD_C66X
        PMHAL_PRCM_SYSCFG_EVE1,
#else
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
#endif
        VSIZE_TYPE(PMHAL_PRCM_MOD_EVE1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_EVE1_CM_CORE_AON_BASE + CM_EVE1_EVE1_CLKCTRL),
        PMHAL_PRCM_MOD_EVE1_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_EVE
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_EVE1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CPGMAC
    { /* PMHAL_PRCM_MOD_CPGMAC */
        PMHAL_PRCM_CD_GMAC,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_CPGMAC,
        VSIZE_TYPE(PMHAL_PRCM_MOD_CPGMAC_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L3INIT_CM_CORE_BASE + CM_GMAC_GMAC_CLKCTRL),
        PMHAL_PRCM_MOD_CPGMAC_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_CPGMAC,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CPGMAC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP1
    {   /* PMHAL_PRCM_MOD_MCASP1 */
        PMHAL_PRCM_CD_IPU,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_MCASP1,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_IPU_CM_CORE_AON_BASE + CM_IPU_MCASP1_CLKCTRL),
        PMHAL_PRCM_MOD_MCASP1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_MCASP1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER5
    { /* PMHAL_PRCM_MOD_TIMER5 */
        PMHAL_PRCM_CD_IPU,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER5_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_IPU_CM_CORE_AON_BASE + CM_IPU_TIMER5_CLKCTRL),
        PMHAL_PRCM_MOD_TIMER5_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_TIMER5,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER6
    { /* PMHAL_PRCM_MOD_TIMER6 */
        PMHAL_PRCM_CD_IPU,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER6_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_IPU_CM_CORE_AON_BASE + CM_IPU_TIMER6_CLKCTRL),
        PMHAL_PRCM_MOD_TIMER6_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_TIMER6,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER7
    { /* PMHAL_PRCM_MOD_TIMER7 */
        PMHAL_PRCM_CD_IPU,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER7_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_IPU_CM_CORE_AON_BASE + CM_IPU_TIMER7_CLKCTRL),
        PMHAL_PRCM_MOD_TIMER7_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_TIMER7,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER8
    { /* PMHAL_PRCM_MOD_TIMER8 */
        PMHAL_PRCM_CD_IPU,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER8_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_IPU_CM_CORE_AON_BASE + CM_IPU_TIMER8_CLKCTRL),
        PMHAL_PRCM_MOD_TIMER8_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_TIMER8,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER8 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IPU1
    { /* PMHAL_PRCM_MOD_IPU1 */
        PMHAL_PRCM_CD_IPU1,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_IPU1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_IPU_CM_CORE_AON_BASE + CM_IPU1_IPU1_CLKCTRL),
        PMHAL_PRCM_MOD_IPU1_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_IPU
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IPU1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP
    { /* PMHAL_PRCM_MOD_IEEE1500_2_OCP */
        PMHAL_PRCM_CD_L3INIT,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_IEEE1500_2_OCP_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L3INIT_CM_CORE_BASE + CM_L3INIT_IEEE1500_2_OCP_CLKCTRL),
        PMHAL_PRCM_MOD_IEEE1500_2_OCP_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_IEEE1500_2_OCP,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_IEEE1500_2_OCP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP
    { /* PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */
        PMHAL_PRCM_CD_L3INSTR,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL),
        PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_BANDGAP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING
    { /* PMHAL_PRCM_MOD_DLL_AGING */
        PMHAL_PRCM_CD_L3INSTR,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DLL_AGING_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3INSTR_DLL_AGING_CLKCTRL),
        PMHAL_PRCM_MOD_DLL_AGING_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DLL_AGING */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR
    { /* PMHAL_PRCM_MOD_L3_INSTR */
        PMHAL_PRCM_CD_L3INSTR,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_L3_INSTR_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3INSTR_L3_INSTR_CLKCTRL),
        PMHAL_PRCM_MOD_L3_INSTR_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_INSTR */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2
    { /* PMHAL_PRCM_MOD_L3_MAIN_2 */
        PMHAL_PRCM_CD_L3INSTR,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_L3_MAIN_2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3INSTR_L3_MAIN_2_CLKCTRL),
        PMHAL_PRCM_MOD_L3_MAIN_2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_L3_MAIN_2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC
    { /* PMHAL_PRCM_MOD_OCP_WP_NOC */
        PMHAL_PRCM_CD_L3INSTR,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_OCP_WP_NOC_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3INSTR_OCP_WP_NOC_CLKCTRL),
        PMHAL_PRCM_MOD_OCP_WP_NOC_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_OCP_WP_NOC,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCP_WP_NOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPMC
    { /* PMHAL_PRCM_MOD_GPMC */
        PMHAL_PRCM_CD_L3MAIN1,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_GPMC,
        VSIZE_TYPE(PMHAL_PRCM_MOD_GPMC_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3MAIN1_GPMC_CLKCTRL),
        PMHAL_PRCM_MOD_GPMC_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPMC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1
    { /* PMHAL_PRCM_MOD_L3_MAIN_1 */
        PMHAL_PRCM_CD_L3MAIN1,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_L3_MAIN_1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3MAIN1_L3_MAIN_1_CLKCTRL),
        PMHAL_PRCM_MOD_L3_MAIN_1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_L3_MAIN_1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L3_MAIN_1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA
    { /* PMHAL_PRCM_MOD_MMU_EDMA */
        PMHAL_PRCM_CD_L3MAIN1,
        PMHAL_PRCM_RT_NO_RETENTION,
#ifdef BUILD_C66X
        PMHAL_PRCM_SYSCFG_MMU_EDMA,
#else
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
#endif
        VSIZE_TYPE(PMHAL_PRCM_MOD_MMU_EDMA_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3MAIN1_MMU_EDMA_CLKCTRL),
        PMHAL_PRCM_MOD_MMU_EDMA_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_MMU_EDMA,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMU_EDMA */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1
    { /* PMHAL_PRCM_MOD_OCMC_RAM1 */
        PMHAL_PRCM_CD_L3MAIN1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_OCMC_RAM1,
        VSIZE_TYPE(PMHAL_PRCM_MOD_OCMC_RAM1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3MAIN1_OCMC_RAM1_CLKCTRL),
        PMHAL_PRCM_MOD_OCMC_RAM1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_OCMC_RAM1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_OCMC_RAM1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TESOC
    { /* PMHAL_PRCM_MOD_TESOC */
        PMHAL_PRCM_CD_L3MAIN1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_TESOC,
        VSIZE_TYPE(PMHAL_PRCM_MOD_TESOC_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3MAIN1_TESOC_CLKCTRL),
        PMHAL_PRCM_MOD_TESOC_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_TESOC,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TESOC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPCC
    { /* PMHAL_PRCM_MOD_TPCC */
        PMHAL_PRCM_CD_L3MAIN1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_TPCC_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3MAIN1_TPCC_CLKCTRL),
        PMHAL_PRCM_MOD_TPCC_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPCC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC1
    { /* PMHAL_PRCM_MOD_TPTC1 */
        PMHAL_PRCM_CD_L3MAIN1,
        PMHAL_PRCM_RT_NO_RETENTION,
        #ifndef __TI_ARM_V7M4__
        PMHAL_PRCM_SYSCFG_TPTC1,
        #else
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        #endif /* __TI_ARM_V7M4__ */
        VSIZE_TYPE(PMHAL_PRCM_MOD_TPTC1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3MAIN1_TPTC1_CLKCTRL),
        PMHAL_PRCM_MOD_TPTC1_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TPTC2
    { /* PMHAL_PRCM_MOD_TPTC2 */
        PMHAL_PRCM_CD_L3MAIN1,
        PMHAL_PRCM_RT_NO_RETENTION,
        #ifndef __TI_ARM_V7M4__
        PMHAL_PRCM_SYSCFG_TPTC2,
        #else
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        #endif /* __TI_ARM_V7M4__ */
        VSIZE_TYPE(PMHAL_PRCM_MOD_TPTC2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L3MAIN1_TPTC2_CLKCTRL),
        PMHAL_PRCM_MOD_TPTC2_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TPTC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_CFG
    { /* PMHAL_PRCM_MOD_L4_CFG */
        PMHAL_PRCM_CD_L4CFG,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_L4_CFG_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L4CFG_L4_CFG_CLKCTRL),
        PMHAL_PRCM_MOD_L4_CFG_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_L4_CFG,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_CFG */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK
    { /* PMHAL_PRCM_MOD_SPINLOCK */
        PMHAL_PRCM_CD_L4CFG,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_SPINLOCK,
        VSIZE_TYPE(PMHAL_PRCM_MOD_SPINLOCK_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L4CFG_SPINLOCK_CLKCTRL),
        PMHAL_PRCM_MOD_SPINLOCK_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_SPINLOCK,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_SPINLOCK */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1
    { /* PMHAL_PRCM_MOD_MAILBOX1 */
        PMHAL_PRCM_CD_L4CFG,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_MAILBOX1,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L4CFG_MAILBOX1_CLKCTRL),
        PMHAL_PRCM_MOD_MAILBOX1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_MAILBOX1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2
    { /* PMHAL_PRCM_MOD_MAILBOX2 */
        PMHAL_PRCM_CD_L4CFG,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_MAILBOX2,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MAILBOX2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CORE_CM_CORE_BASE + CM_L4CFG_MAILBOX2_CLKCTRL),
        PMHAL_PRCM_MOD_MAILBOX2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_MAILBOX2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MAILBOX2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C1
    { /* PMHAL_PRCM_MOD_I2C1 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_I2C1,
        VSIZE_TYPE(PMHAL_PRCM_MOD_I2C1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_I2C1_CLKCTRL),
        PMHAL_PRCM_MOD_I2C1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_I2C1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_I2C2
    { /* PMHAL_PRCM_MOD_I2C2 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_I2C2,
        VSIZE_TYPE(PMHAL_PRCM_MOD_I2C2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_I2C2_CLKCTRL),
        PMHAL_PRCM_MOD_I2C2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_I2C2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_I2C2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER1
    { /* PMHAL_PRCM_MOD_L4_PER1 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_L4_PER1_CLKCTRL),
        PMHAL_PRCM_MOD_L4_PER1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_L4_PER1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC6
    { /* PMHAL_PRCM_MOD_DCC6 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DCC6_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_DCC6_CLKCTRL),
        PMHAL_PRCM_MOD_DCC6_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC6 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC7
    { /* PMHAL_PRCM_MOD_DCC7 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DCC7_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_DCC7_CLKCTRL),
        PMHAL_PRCM_MOD_DCC7_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC7 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER2
    { /* PMHAL_PRCM_MOD_TIMER2 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER2_CLKCTRL),
        PMHAL_PRCM_MOD_TIMER2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_TIMER2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER3
    { /* PMHAL_PRCM_MOD_TIMER3 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER3_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER3_CLKCTRL),
        PMHAL_PRCM_MOD_TIMER3_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_TIMER3,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER4
    { /* PMHAL_PRCM_MOD_TIMER4 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER4_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER4_CLKCTRL),
        PMHAL_PRCM_MOD_TIMER4_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_TIMER4,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC5
    { /* PMHAL_PRCM_MOD_DCC5 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DCC5_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_DCC5_CLKCTRL),
        PMHAL_PRCM_MOD_DCC5_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_DCC5,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ELM
    { /* PMHAL_PRCM_MOD_ELM */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_ELM,
        VSIZE_TYPE(PMHAL_PRCM_MOD_ELM_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_ELM_CLKCTRL),
        PMHAL_PRCM_MOD_ELM_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_ELM,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ELM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ESM
    { /* PMHAL_PRCM_MOD_ESM */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_ESM,
        VSIZE_TYPE(PMHAL_PRCM_MOD_ESM_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_ESM_CLKCTRL),
        PMHAL_PRCM_MOD_ESM_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_ESM,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ESM */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI1
    { /* PMHAL_PRCM_MOD_MCSPI1 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_MCSPI1,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI1_CLKCTRL),
        PMHAL_PRCM_MOD_MCSPI1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_MCSPI1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI2
    { /* PMHAL_PRCM_MOD_MCSPI2 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_MCSPI2,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI2_CLKCTRL),
        PMHAL_PRCM_MOD_MCSPI2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_MCSPI2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI3
    { /* PMHAL_PRCM_MOD_MCSPI3 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_MCSPI3,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI3_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI3_CLKCTRL),
        PMHAL_PRCM_MOD_MCSPI3_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_MCSPI3,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCSPI4
    { /* PMHAL_PRCM_MOD_MCSPI4 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_MCSPI4,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MCSPI4_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_MCSPI4_CLKCTRL),
        PMHAL_PRCM_MOD_MCSPI4_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_MCSPI4,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCSPI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART1
    { /* PMHAL_PRCM_MOD_UART1 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_UART1,
        VSIZE_TYPE(PMHAL_PRCM_MOD_UART1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART1_CLKCTRL),
        PMHAL_PRCM_MOD_UART1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_UART1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART2
    { /* PMHAL_PRCM_MOD_UART2 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_UART2,
        VSIZE_TYPE(PMHAL_PRCM_MOD_UART2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART2_CLKCTRL),
        PMHAL_PRCM_MOD_UART2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_UART2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_UART3
    { /* PMHAL_PRCM_MOD_UART3 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_UART3,
        VSIZE_TYPE(PMHAL_PRCM_MOD_UART3_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_UART3_CLKCTRL),
        PMHAL_PRCM_MOD_UART3_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_UART3,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_UART3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO2
    { /* PMHAL_PRCM_MOD_GPIO2 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_GPIO2,
        VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_GPIO2_CLKCTRL),
        PMHAL_PRCM_MOD_GPIO2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_GPIO2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO3
    { /* PMHAL_PRCM_MOD_GPIO3 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_GPIO3,
        VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO3_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_GPIO3_CLKCTRL),
        PMHAL_PRCM_MOD_GPIO3_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_GPIO3,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO4
    { /* PMHAL_PRCM_MOD_GPIO4 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_GPIO4,
        VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO4_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_GPIO4_CLKCTRL),
        PMHAL_PRCM_MOD_GPIO4_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_GPIO4,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MMC4
    { /* PMHAL_PRCM_MOD_MMC4 */
        PMHAL_PRCM_CD_L4PER1,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_MMC4,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MMC4_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER_MMC4_CLKCTRL),
        PMHAL_PRCM_MOD_MMC4_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_MMC4,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MMC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN2
    { /* PMHAL_PRCM_MOD_DCAN2 */
        PMHAL_PRCM_CD_L4PER2,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DCAN2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL),
        PMHAL_PRCM_MOD_DCAN2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_DCAN2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER2
    { /* PMHAL_PRCM_MOD_L4_PER2 */
        PMHAL_PRCM_CD_L4PER2,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_L4_PER2_CLKCTRL),
        PMHAL_PRCM_MOD_L4_PER2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_L4_PER2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ADC
    { /* PMHAL_PRCM_MOD_ADC */
        PMHAL_PRCM_CD_L4PER2,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_ADC_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_ADC_CLKCTRL),
        PMHAL_PRCM_MOD_ADC_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_ADC,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ADC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_PWMSS1
    { /* PMHAL_PRCM_MOD_PWMSS1 */
        PMHAL_PRCM_CD_L4PER2,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_PWMSS1,
        VSIZE_TYPE(PMHAL_PRCM_MOD_PWMSS1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_PWMSS1_CLKCTRL),
        PMHAL_PRCM_MOD_PWMSS1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_PWMSS1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_PWMSS1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_QSPI
    { /* PMHAL_PRCM_MOD_QSPI */
        PMHAL_PRCM_CD_L4PER2,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_QSPI,
        VSIZE_TYPE(PMHAL_PRCM_MOD_QSPI_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL),
        PMHAL_PRCM_MOD_QSPI_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_QSPI,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_QSPI */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_PER3
    { /* PMHAL_PRCM_MOD_L4_PER3 */
        PMHAL_PRCM_CD_L4PER3,
        PMHAL_PRCM_RT_PARTIAL_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_L4_PER3_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER3_L4_PER3_CLKCTRL),
        PMHAL_PRCM_MOD_L4_PER3_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_L4_PER3,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_PER3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC1
    { /* PMHAL_PRCM_MOD_DCC1 */
        PMHAL_PRCM_CD_L4PER3,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DCC1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER3_DCC1_CLKCTRL),
        PMHAL_PRCM_MOD_DCC1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_DCC1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC2
    { /* PMHAL_PRCM_MOD_DCC2 */
        PMHAL_PRCM_CD_L4PER3,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DCC2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER3_DCC2_CLKCTRL),
        PMHAL_PRCM_MOD_DCC2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_DCC2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC3
    { /* PMHAL_PRCM_MOD_DCC3 */
        PMHAL_PRCM_CD_L4PER3,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DCC3_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER3_DCC3_CLKCTRL),
        PMHAL_PRCM_MOD_DCC3_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_DCC3,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCC4
    { /* PMHAL_PRCM_MOD_DCC4 */
        PMHAL_PRCM_CD_L4PER3,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DCC4_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER3_DCC4_CLKCTRL),
        PMHAL_PRCM_MOD_DCC4_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_DCC4,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCC4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_VIP1
    { /* PMHAL_PRCM_MOD_VIP1 */
        PMHAL_PRCM_CD_CAM,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_VIP1,
        VSIZE_TYPE(PMHAL_PRCM_MOD_VIP1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_CAM_CM_CORE_BASE + CM_CAM_VIP1_CLKCTRL),
        PMHAL_PRCM_MOD_VIP1_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_VIP1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ISS
    { /* PMHAL_PRCM_MOD_ISS */
        PMHAL_PRCM_CD_ISS,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_ISS,
        VSIZE_TYPE(PMHAL_PRCM_MOD_ISS_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_VPE_CM_CORE_AON_BASE + CM_ISS_ISS_CLKCTRL),
        PMHAL_PRCM_MOD_ISS_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ISS */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC
    { /* PMHAL_PRCM_MOD_DEBUG_LOGIC */
        PMHAL_PRCM_CD_EMU,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DEBUG_LOGIC_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_EMU_CM_BASE + CM_EMU_DEBUGSS_CLKCTRL),
        PMHAL_PRCM_MOD_DEBUG_LOGIC_ClkSelectCfg,
        TRUE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_DEBUG_LOGIC,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DEBUG_LOGIC */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K
    { /* PMHAL_PRCM_MOD_COUNTER_32K */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_COUNTER_32K,
        VSIZE_TYPE(PMHAL_PRCM_MOD_COUNTER_32K_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_COUNTER_32K_CLKCTRL),
        PMHAL_PRCM_MOD_COUNTER_32K_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_COUNTER_32K,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_COUNTER_32K */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP
    { /* PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_CTRL_MODULE_WKUP_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        PMHAL_INVALID_REGADDR,
        PMHAL_PRCM_MOD_CTRL_MODULE_WKUP_ClkSelectCfg,
        FALSE,
        ((uint8_t) (PMHAL_MODULEMODE_NOTAPPLICABLE)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CTRL_MODULE_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_DCAN1
    { /* PMHAL_PRCM_MOD_DCAN1 */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_DCAN1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_DCAN1_CLKCTRL),
        PMHAL_PRCM_MOD_DCAN1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_DCAN1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_DCAN1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_GPIO1
    { /* PMHAL_PRCM_MOD_GPIO1 */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_FULL_RETENTION,
        PMHAL_PRCM_SYSCFG_GPIO1,
        VSIZE_TYPE(PMHAL_PRCM_MOD_GPIO1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_GPIO1_CLKCTRL),
        PMHAL_PRCM_MOD_GPIO1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_GPIO1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_GPIO1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP
    { /* PMHAL_PRCM_MOD_L4_WKUP */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_L4_WKUP_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_L4_WKUP_CLKCTRL),
        PMHAL_PRCM_MOD_L4_WKUP_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_L4_WKUP */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI1
    { /* PMHAL_PRCM_MOD_RTI1 */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_RTI1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_RTI1_CLKCTRL),
        PMHAL_PRCM_MOD_RTI1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_RTI1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI2
    { /* PMHAL_PRCM_MOD_RTI2 */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_RTI2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_RTI2_CLKCTRL),
        PMHAL_PRCM_MOD_RTI2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_RTI2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI3
    { /* PMHAL_PRCM_MOD_RTI3 */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_RTI3_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_RTI3_CLKCTRL),
        PMHAL_PRCM_MOD_RTI3_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_RTI3,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI3 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI4
    { /* PMHAL_PRCM_MOD_RTI4 */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_RTI4_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_RTI4_CLKCTRL),
        PMHAL_PRCM_MOD_RTI4_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_RTI4,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI4 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_RTI5
    { /* PMHAL_PRCM_MOD_RTI5 */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_RTI5_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_RTI5_CLKCTRL),
        PMHAL_PRCM_MOD_RTI5_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_AUTO)),
        PMHAL_EDGE_MOD_RTI5,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_RTI5 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_TIMER1
    { /* PMHAL_PRCM_MOD_TIMER1 */
        PMHAL_PRCM_CD_WKUPAON,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_TIMER1_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_WKUPAON_CM_BASE + CM_WKUPAON_TIMER1_CLKCTRL),
        PMHAL_PRCM_MOD_TIMER1_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED)),
        PMHAL_EDGE_MOD_TIMER1,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_TIMER1 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_CAMERARX
    { /* PMHAL_PRCM_MOD_CAMERARX */
        PMHAL_PRCM_CD_ISS,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_CAMERARX_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        PMHAL_REG_NOTAPPLICABLE,
        PMHAL_PRCM_MOD_CAMERARX_ClkSelectCfg,
        FALSE,
        (uint8_t) (PMHAL_MODULEMODE_NOTAPPLICABLE),
        PMHAL_EDGE_UNDEF,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_CAMERARX */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCAN
    { /* PMHAL_PRCM_MOD_MCAN */
        PMHAL_PRCM_CD_L4PER2,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MCAN_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_DCAN2_CLKCTRL),
        PMHAL_PRCM_MOD_MCAN_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_MCAN,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCAN */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_ATL
    {   /* PMHAL_PRCM_MOD_ATL */
        PMHAL_PRCM_CD_L4PER2,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_NOTAPPLICABLE,
        VSIZE_TYPE(PMHAL_PRCM_MOD_ATL_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_ATL_CLKCTRL),
        PMHAL_PRCM_MOD_ATL_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_ATL,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_ATL */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP2
    {   /* PMHAL_PRCM_MOD_MCASP2 */
        PMHAL_PRCM_CD_L4PER2,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_MCASP2,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP2_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_MCASP4_CLKCTRL),
        PMHAL_PRCM_MOD_MCASP2_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_MCASP2,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP2 */
#ifdef BUILDCFG_PMHAL_PRCM_MOD_MCASP3
    {   /* PMHAL_PRCM_MOD_MCASP3 */
        PMHAL_PRCM_CD_L4PER2,
        PMHAL_PRCM_RT_NO_RETENTION,
        PMHAL_PRCM_SYSCFG_MCASP3,
        VSIZE_TYPE(PMHAL_PRCM_MOD_MCASP3_ClkSelectCfg,
                   pmhalClockSelConfig_t),
        (SOC_L4PER_CM_CORE_BASE + CM_L4PER2_MCASP5_CLKCTRL),
        PMHAL_PRCM_MOD_MCASP3_ClkSelectCfg,
        FALSE,
        (uint8_t) (((uint32_t) 1U <<
                    (uint32_t) PMHAL_PRCM_MODULE_MODE_ENABLED) |
                   ((uint32_t) 1U << (uint32_t) PMHAL_PRCM_MODULE_MODE_DISABLED)),
        PMHAL_EDGE_MOD_MCASP3,
        PMHAL_PRCM_CPU_ID_UNDEF
    },
#endif /* BUILDCFG_PMHAL_PRCM_MOD_MCASP3 */
};

/**
 *  \note  The following structures should not be changed as they define silicon
 *         characteristics or supported frequencies for a given OPP.
 */
/**
 *
 * \brief OPP Table for TDA3xx devices. This is used to figure out which
 *        input frequency belongs to which OPP
 *
 *   2. Frequency Table
 *     +-----------+-----------+--------------+-------------+-------------+
 *     | Voltage   |  Module   |   OPP_NOM    |   OPP_OD    |   OPP_HIGH  |
 *     | Domain    |           | Max Freq MHz | Max Freq MHz| Max Freq MHz|
 *     +-----------+-----------+--------------+-------------+-------------+
 *     | VD_CORE   |  IPU      |     212.8    |     NA      |     NA      |
 *     | VD_CORE   |  L3       |     266.0    |     NA      |     NA      |
 *     | VD_DSPEVE |  DSP      |     500.0    |     NA      |     NA      |
 *     | VD_DSPEVE |  EVE      |     500.0    |     NA      |     NA      |
 *     +-----------+-----------+--------------+-------------+-------------+
 *
 */
uint32_t pmhalOppModuleMaxRate[PMHAL_PRCM_CPU_ID_COUNT][PMHAL_VM_OPP_MAX] =
{
    /* PMLIB_CPU_ID_IPU */
    {0U, 212800000U, 0U, 0U},
    /* PMLIB_CPU_ID_DSP*/
    {0U, 500000000U, 0U, 0U},
    /* PMLIB_CPU_ID_EVE*/
    {0U, 500000000U, 0U, 0U},
};

/** \brief Array defining the dependent CPU's for a given CPU ID. */
pmhalPrcmCpuId_t                pmhalDepCpuList[] =
{
    PMHAL_PRCM_CPU_ID_UNDEF,
    PMHAL_PRCM_CPU_ID_EVE,
    PMHAL_PRCM_CPU_ID_DSP
};

pmhalPrcmModuleId_t             pmhalCpuModuleId[] =
{
    PMHAL_PRCM_MOD_IPU1,
    PMHAL_PRCM_MOD_DSP1,
    PMHAL_PRCM_MOD_EVE1
};

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/** \brief Array defining the list of valid system clock frequencies in kHz. */
const uint32_t                  gPmhalSysClkFreqkHz[PMHAL_PRCM_SYSCLK_COUNT] =
{
    0U,     /* PMHAL_PRCM_SYSCLK_UNINITIALIZED */
    12000U, /* PMHAL_PRCM_SYSCLK_12_MHZ */
    20000U, /* PMHAL_PRCM_SYSCLK_20_MHZ */
    16800U, /* PMHAL_PRCM_SYSCLK_16_8_MHZ */
    19200U, /* PMHAL_PRCM_SYSCLK_19_2_MHZ */
    26000U, /* PMHAL_PRCM_SYSCLK_26_MHZ */
    27000U, /* PMHAL_PRCM_SYSCLK_27_MHZ */
    38400U  /* PMHAL_PRCM_SYSCLK_38_4_MHZ */
};

/* ========================================================================== */
/*                            Function Declarations                           */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif
