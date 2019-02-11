/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     ammu.c
 *
 *  \brief    This file contains the AMMU HAL APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ammu.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

int32_t AMMUConfigPage(uint32_t baseAddr, const ammuPageConfig_t *ammuPageCfg)
{
    int32_t  retVal = STW_SOK;
    uint32_t ammuPolicyRegOffset      = 0U;
    uint32_t ammuPhyAddrRegOffset     = 0U;
    uint32_t ammuLogicalAddrRegOffset = 0U;

    switch (ammuPageCfg->ammuPageType)
    {
        case AMMU_PAGE_TYPE_SMALL:
            if (ammuPageCfg->ammuPageNum >= AMMU_NUM_SMALL_PAGES)
            {
                retVal = STW_EFAIL;
            }
            else
            {
                ammuPolicyRegOffset =
                    IPU_SMALL_POLICY(ammuPageCfg->ammuPageNum);
                ammuPhyAddrRegOffset =
                    IPU_SMALL_XLTE(ammuPageCfg->ammuPageNum);
                ammuLogicalAddrRegOffset =
                    IPU_SMALL_ADDR(ammuPageCfg->ammuPageNum);
            }
            break;
        case AMMU_PAGE_TYPE_MEDIUM:
            if (ammuPageCfg->ammuPageNum >= AMMU_NUM_MEDIUM_PAGES)
            {
                retVal = STW_EFAIL;
            }
            else
            {
                ammuPolicyRegOffset =
                    IPU_MED_POLICY(ammuPageCfg->ammuPageNum);
                ammuPhyAddrRegOffset =
                    IPU_MED_XLTE(ammuPageCfg->ammuPageNum);
                ammuLogicalAddrRegOffset =
                    IPU_MED_ADDR(ammuPageCfg->ammuPageNum);
            }
            break;
        case AMMU_PAGE_TYPE_LARGE:
            if (ammuPageCfg->ammuPageNum >= AMMU_NUM_LARGE_PAGES)
            {
                retVal = STW_EFAIL;
            }
            else
            {
                ammuPolicyRegOffset =
                    IPU_LARGE_POLICY(ammuPageCfg->ammuPageNum);
                ammuPhyAddrRegOffset =
                    IPU_LARGE_XLTE(ammuPageCfg->ammuPageNum);
                ammuLogicalAddrRegOffset =
                    IPU_LARGE_ADDR(ammuPageCfg->ammuPageNum);
            }
            break;
        case AMMU_PAGE_TYPE_INVALID:
            retVal = STW_EFAIL;
            break;
        default:
            retVal = STW_EFAIL;
            break;
    }

    if (STW_SOK == retVal)
    {
        /* First clear any previous configuration */
        /* Policy Register */
        HW_WR_REG32(baseAddr + ammuPolicyRegOffset, 0x00000000U);
        /* Logical Address */
        HW_WR_REG32(baseAddr + ammuLogicalAddrRegOffset, 0x00000000U);
        /* Physical Address */
        HW_WR_REG32(baseAddr + ammuPhyAddrRegOffset, 0x00000000U);

        /* Map the new configuration */
        if (0U != ammuPageCfg->policyRegVal)
        {
            /* Logical Address */
            HW_WR_REG32(baseAddr + ammuLogicalAddrRegOffset,
                        ammuPageCfg->logicalAddress);
            /* Physical Address */
            HW_WR_REG32(baseAddr + ammuPhyAddrRegOffset,
                        ammuPageCfg->physicalAddress);
            /* Policy Register */
            HW_WR_REG32(baseAddr + ammuPolicyRegOffset,
                        ammuPageCfg->policyRegVal);
        }
    }

    return retVal;
}

uint32_t AMMUMakePolicyReg(const ammuPolicyRegParams_t *policyParams)
{
    uint32_t policyRegVal = 0U;

    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_ENABLE,
                   policyParams->pageEnable);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_SIZE,
                   policyParams->pageSize);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_PRELOAD,
                   policyParams->preloadEnable);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L1_CACHEABLE,
                   policyParams->l1CacheEnable);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L1_POSTED,
                   policyParams->l1PostedWrite);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L1_ALLOCATE,
                   policyParams->l1AllocateWrite);
    HW_SET_FIELD32(policyRegVal,
                   IPU_LARGE_POLICY_L1_WR_POLICY,
                   policyParams->l1WritePolicy);

    return policyRegVal;
}

void AMMUInitPolicyParams(ammuPolicyRegParams_t *policyParams)
{
    policyParams->pageEnable           = AMMU_PAGE_DISABLED;
    policyParams->pageSize             = AMMU_PAGE_SIZE_INVALID;
    policyParams->preloadEnable        = AMMU_PRELOAD_DISABLED;
    policyParams->l1CacheEnable        = AMMU_L1_CACHE_DISABLED;
    policyParams->l1PostedWrite        = AMMU_L1_POSTED_WRITE_DISABLED;
    policyParams->l1AllocateWrite      = AMMU_L1_ALLOCATE_WRITE_DISABLED;
    policyParams->l1WritePolicy        = AMMU_L1_WRITE_POLICY_WRITETHROUGH;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
