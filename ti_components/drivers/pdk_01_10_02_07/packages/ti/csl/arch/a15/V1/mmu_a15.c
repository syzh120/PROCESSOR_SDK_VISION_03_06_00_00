/*
 *  Copyright (c) Texas Instruments Incorporated 2015
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
 *  \file     mmu_a15.c
 *
 *  \brief    This file contains the A15 MMU HAL APIs.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <mmu_a15.h>
#include <mmu_a15_gcc_asm.h>
#include <cache_a15.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define MMU_A15_LEVEL2_BLOCK_DESC_SHIFT                 ((uint32_t) 21U)
#define MMU_A15_LEVEL1_TABLE_DESC_SHIFT                 ((uint32_t) 30U)

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

void MMUA15Init(void)
{
    MMUA15InitASM();
}

uint32_t MMUA15IsEnabled(void)
{
    uint32_t retVal = 0U;

    retVal = MMUA15IsEnabledASM();

    return retVal;
}

void MMUA15TLBInvalidate(uint32_t startAddr, uint32_t len)
{
    MMUA15TLBInvalidateASM(startAddr, len);
}

void MMUA15TLBInvalidateAll(void)
{
    MMUA15TLBInvalidateAllASM();
}

void MMUA15Disable(void)
{
    uint32_t cacheType;

    /* Check if MMU is already disabled */
    if (0U != MMUA15IsEnabledASM())
    {
        /* Get the cache enabled type */
        cacheType = CACHEA15GetEnabled();

        if (0U != (((uint32_t) CACHE_A15_TYPE_L1D) & cacheType))
        {
            /* Writeback Invalidate All Data Cache */
            CACHEA15WriteBackAndInvalidateAll();

            /* Drain Write Buffer */
            CACHEA15Wait();

            /* Disable L1 Data Cache */
            CACHEA15Disable(CACHE_A15_TYPE_L1D);
        }

        if (0U != (((uint32_t) CACHE_A15_TYPE_L1I) & cacheType))
        {
            /* Invalidate I Cache */
            CACHEA15InvalidateL1IAll();

            /* Disable L1 Instruction Cache */
            CACHEA15Disable(CACHE_A15_TYPE_L1I);
        }

        /* Disable MMU */
        MMUA15DisableASM();

        /* Invalidate all TLBs */
        MMUA15TLBInvalidateAll();

        /* Enable Cache */
        CACHEA15Enable(cacheType);
    }
}

void MMUA15Enable(const mmuA15ModuleTable_t *mmuTable)
{
    uint32_t cacheType;

    /* Check if MMU is already enabled */
    if ((0U == MMUA15IsEnabledASM()) && (NULL != mmuTable))
    {
        /* Get the cache enabled type */
        cacheType = CACHEA15GetEnabled();

        if (0U != (((uint32_t) CACHE_A15_TYPE_ALLI) & cacheType))
        {
            /* Invalidate I Cache */
            CACHEA15InvalidateL1IAll();

            /* Disable All Instruction Cache */
            CACHEA15Disable(CACHE_A15_TYPE_ALLI);
        }

        /* Invalidate all TLBs */
        MMUA15TLBInvalidateAll();

        /* Enable MMU */
        MMUA15EnableASM(mmuTable->firstLevelTableBuff);

        /* Enable Cache */
        CACHEA15Enable(cacheType);
    }
}

void MMUA15InitDescAttrs(mmuA15DescriptorAttrs_t *attrs)
{
    if (NULL != attrs)
    {
        attrs->descriptorType = MMU_A15_DESCRIPTOR_TYPE_TABLE;
        attrs->nsTable        = MMU_A15_NT_MEM_SPACE_SECURE;
        attrs->apTable        = MMU_A15_NT_ACC_PERM_NO_EFFECT;
        attrs->xnTable        = MMU_A15_NT_XN_NO_EFFECT;
        attrs->pxnTable       = MMU_A15_NT_PXN_NO_EFFECT;
        attrs->noExecute      = MMU_A15_XN_DISABLE;
        attrs->privNoExecute  = MMU_A15_PXN_DISABLE;
        attrs->contiguous     = MMU_A15_CONTIGUOUS_HINT_DISABLE;
        attrs->notGlobal      = MMU_A15_NOT_GLOBAL_DISABLE;
        attrs->accessFlag     = MMU_A15_ACCESS_FLAG_ENABLE;
        attrs->shareable      = MMU_A15_NON_SHAREABLE;
        attrs->accPerm        = MMU_A15_ACC_PERM_RW_PL1;
        attrs->nonSecure      = MMU_A15_NON_SECURE_DISABLE;
        attrs->attrIndx       = MMU_A15_ATTR_INDEX_0;
    }
}

int32_t MMUA15SetFirstLevelDesc(mmuA15ModuleTable_t           *mmuTable,
                                uint32_t                       virtualAddr,
                                uint64_t                       phyAddr,
                                const mmuA15DescriptorAttrs_t *attrs)
{
    uint32_t index = virtualAddr >> MMU_A15_LEVEL1_TABLE_DESC_SHIFT;
    uint64_t desc;
    uint32_t enabled;
    uint64_t tempPhyAddr64bit;
    uint32_t tempPhyAddr32bit;
    void    *tempPhyAddrPtr;
    int32_t  retVal = STW_SOK;

    /* Determine the current state of MMU */
    enabled = MMUA15IsEnabledASM();

    /* Disable the MMU (if already enabled, does nothing) */
    MMUA15Disable();

    /* Determine which type of descriptor */
    switch (attrs->descriptorType)
    {
        case MMU_A15_DESCRIPTOR_TYPE_TABLE:
            /* For TABLE descriptors determine second level table address */
            /* Physical address is 40 bits long and virtual address is 32 bits
             * long. In current systems the pointer variable is 32 bits long.
             * Due to this first typecast to void pointer and then typecast to
             * 32 bit variable and finally 64 bit variable.
             */
            tempPhyAddrPtr =
                (void *) (&mmuTable->secondLevelTableBuff[index][0U]);
            tempPhyAddr32bit = ((uint32_t) tempPhyAddrPtr);
            tempPhyAddr64bit = ((uint64_t) tempPhyAddr32bit);
            /* Page table descriptor */
            desc = (((uint64_t) attrs->descriptorType & 0x3U) |
                    (tempPhyAddr64bit & 0xFFFFFFF000U) |
                    ((((uint64_t) attrs->pxnTable & 0x1U) << 59U)) |
                    ((((uint64_t) attrs->xnTable & 0x1U) << 60U)) |
                    ((((uint64_t) attrs->apTable & 0x3U) << 61U)) |
                    ((((uint64_t) attrs->nsTable & 0x1U) << 63U)));
            break;

        /* Section descriptor */
        case MMU_A15_DESCRIPTOR_TYPE_BLOCK:
            desc = (((uint64_t) attrs->descriptorType & 0x3U) |
                    ((((uint64_t) attrs->attrIndx & 0x7U) << 2U)) |
                    ((((uint64_t) attrs->nonSecure & 0x1U) << 5U)) |
                    ((((uint64_t) attrs->accPerm & 0x3U) << 6U)) |
                    ((((uint64_t) attrs->shareable & 0x3U) << 8U)) |
                    ((((uint64_t) attrs->accessFlag & 0x1U) << 10U)) |
                    ((((uint64_t) attrs->notGlobal & 0x1U) << 11U)) |
                    (phyAddr & 0xFFC0000000U) |
                    ((((uint64_t) attrs->contiguous & 0x1U) << 52U)) |
                    ((((uint64_t) attrs->privNoExecute & 0x1U) << 53U)) |
                    ((((uint64_t) attrs->noExecute & 0x1U) << 54U)));
            break;
        default:
            retVal = STW_EFAIL;
            break;
    }

    if (STW_SOK == retVal)
    {
        /* set the entry in the first level descriptor table */
        mmuTable->firstLevelTableBuff[index] = desc;

        if (0U != enabled)
        {
            /* If MMU was enabled, then re-enable it */
            MMUA15Enable(mmuTable);
        }
    }

    return retVal;
}

void MMUA15SetMAIR(mmuA15ModuleTable_t *mmuTable,
                   uint32_t             attrIndx,
                   uint32_t             attr)
{
    /* Update module state mairRegAttr */
    mmuTable->mairRegAttr[attrIndx] = attr;

    /* Write attr to MAIRn register */
    MMUA15WriteMAIRASM(attrIndx, attr);

    /* Invalidate the entire TLB (broadcast to other cores) */
    MMUA15TLBInvalidateAll();
}

int32_t MMUA15SetSecondLevelDesc(mmuA15ModuleTable_t           *mmuTable,
                                 uint32_t                       virtualAddr,
                                 uint64_t                       phyAddr,
                                 const mmuA15DescriptorAttrs_t *attrs)
{
    uint32_t index = virtualAddr >> MMU_A15_LEVEL2_BLOCK_DESC_SHIFT;
    uint64_t desc;
    uint32_t enabled;
    int32_t  retVal = STW_SOK;

    /* Determine the current state of MMU */
    enabled = MMUA15IsEnabledASM();

    /* Disable the MMU (if already enabled, does nothing) */
    MMUA15Disable();

    /* Determine which type of descriptor */
    switch (attrs->descriptorType)
    {
        case MMU_A15_DESCRIPTOR_TYPE_TABLE:
            /* Page table descriptor */
            desc = (((uint64_t) attrs->descriptorType & 0x3U) |
                    (phyAddr & 0xFFFFFFF000U) |
                    ((((uint64_t) attrs->pxnTable & 0x1U) << 59U)) |
                    ((((uint64_t) attrs->xnTable & 0x1U) << 60U)) |
                    ((((uint64_t) attrs->apTable & 0x3U) << 61U)) |
                    ((((uint64_t) attrs->nsTable & 0x1U) << 63U)));
            break;

        /* Section descriptor */
        case MMU_A15_DESCRIPTOR_TYPE_BLOCK:
            desc = (((uint64_t) attrs->descriptorType & 0x3U) |
                    ((((uint64_t) attrs->attrIndx & 0x7U) << 2U)) |
                    ((((uint64_t) attrs->nonSecure & 0x1U) << 5U)) |
                    ((((uint64_t) attrs->accPerm & 0x3U) << 6U)) |
                    ((((uint64_t) attrs->shareable & 0x3U) << 8U)) |
                    ((((uint64_t) attrs->accessFlag & 0x1U) << 10U)) |
                    ((((uint64_t) attrs->notGlobal & 0x1U) << 11U)) |
                    (phyAddr & 0xFFFFE00000U) |
                    ((((uint64_t) attrs->contiguous & 0x1U) << 52U)) |
                    ((((uint64_t) attrs->privNoExecute & 0x1U) << 53U)) |
                    ((((uint64_t) attrs->noExecute & 0x1U) << 54U)));
            break;
        default:
            retVal = STW_EFAIL;
            break;
    }

    if (STW_SOK == retVal)
    {
        /* set the entry in the second level descriptor table */
        mmuTable->secondLevelTableBuff[index >> 9U][index & 0x1FFU] = desc;

        if (0U != enabled)
        {
            /* If MMU was enabled, then re-enable it */
            MMUA15Enable(mmuTable);
        }
    }

    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
