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
 *  \ingroup CSL_ARCH_M4
 *  \defgroup CSL_ARCH_M4_AMMU AMMU
 *
 *  @{
 */
/**
 *  \file     ammu.h
 *
 *  \brief    This file contains the interfaces present in the AMMU HAL.
 *            This also contains some related macros, structures and enums.
 *
 */

#ifndef AMMU_H_
#define AMMU_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <ti/csl/cslr_mmu.h>

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 * \brief  This macro defines the number of small AMMU pages.
 */
#define AMMU_NUM_SMALL_PAGES                           ((uint32_t) 0xAU)

/**
 * \brief  This macro defines the number of medium AMMU pages.
 */
#define AMMU_NUM_MEDIUM_PAGES                          ((uint32_t) 0x2U)

/**
 * \brief  This macro defines the number of large AMMU pages.
 */
#define AMMU_NUM_LARGE_PAGES                           ((uint32_t) 0x4U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Enum to select the AMMU Page Type.
 */
typedef enum
{
    AMMU_PAGE_TYPE_SMALL,
    /**< AMMU page type: Small. Valid size: 4 KB or 16 KB */
    AMMU_PAGE_TYPE_MEDIUM,
    /**< AMMU page type: Medium. Valid size: 128 KB or 256 KB */
    AMMU_PAGE_TYPE_LARGE,
    /**< AMMU page type: Large. Valid size: 32 MB or 512 MB */
    AMMU_PAGE_TYPE_INVALID
    /**< AMMU page type: Invalid */
}ammuPageType_t;

/**
 * \brief  Enum to select the AMMU Page Size.
 */
typedef enum ammuPageSize
{
    AMMU_PAGE_SIZE_4KB = IPU_SMALL_POLICY_SIZE_4KB,
    /**< AMMU page size: 4 KB */
    AMMU_PAGE_SIZE_16KB = IPU_SMALL_POLICY_SIZE_16KB,
    /**< AMMU page size: 16 KB */
    AMMU_PAGE_SIZE_128KB = IPU_MED_POLICY_SIZE_128KB,
    /**< AMMU page size: 128 KB */
    AMMU_PAGE_SIZE_256KB = IPU_MED_POLICY_SIZE_256KB,
    /**< AMMU page size: 256 KB */
    AMMU_PAGE_SIZE_32MB = IPU_LARGE_POLICY_SIZE_32MB,
    /**< AMMU page size: 32 MB */
    AMMU_PAGE_SIZE_512MB = IPU_LARGE_POLICY_SIZE_512MB,
    /**< AMMU page size: 512 MB */
    AMMU_PAGE_SIZE_INVALID = 0xFFU
                             /**< AMMU page size: Invalid */
}ammuPageSize_t;

/**
 * \brief  Enum to enable/disable the AMMU Page.
 */
typedef enum ammuPageEnable
{
    AMMU_PAGE_DISABLED = IPU_LARGE_POLICY_ENABLE_DISABLE,
    /**< Disable AMMU Page */
    AMMU_PAGE_ENABLED = IPU_LARGE_POLICY_ENABLE_ENABLE
                        /**< Enable AMMU Page */
}ammuPageEnable_t;

/**
 * \brief  Enum to enable/disable Pre-load for AMMU Page.
 */
typedef enum ammuPreloadEnable
{
    AMMU_PRELOAD_DISABLED = IPU_LARGE_POLICY_PRELOAD_DISABLE,
    /**< Disable AMMU Page Pre-load */
    AMMU_PRELOAD_ENABLED = IPU_LARGE_POLICY_PRELOAD_ENABLE
                           /**< Enable AMMU Page Pre-load */
}ammuPreloadEnable_t;

/**
 * \brief  Enum to enable/disable L1 cache for AMMU page.
 */
typedef enum ammuL1CacheEnable
{
    AMMU_L1_CACHE_DISABLED = IPU_LARGE_POLICY_L1_CACHEABLE_DISABLE,
    /**< Disable the L1 Cache */
    AMMU_L1_CACHE_ENABLED = IPU_LARGE_POLICY_L1_CACHEABLE_ENABLE
                            /**< Enable the L1 Cache */
}ammuL1CacheEnable_t;

/**
 * \brief  Enum to set L1 posted write policy of AMMU page.
 */
typedef enum ammuL1PostedWrite
{
    AMMU_L1_POSTED_WRITE_DISABLED =
        IPU_LARGE_POLICY_L1_POSTED_NON_POSTED,
    /**< Set L1 Posted Write Policy as Not Posted */
    AMMU_L1_POSTED_WRITE_ENABLED = IPU_LARGE_POLICY_L1_POSTED_POSTED
                                   /**< Set L1 Posted Write Policy as
                                    *   Posted */
}ammuL1PostedWrite_t;

/**
 * \brief  Enum to set L1 Write allocate policy of AMMU page.
 */
typedef enum ammuL1AllocateWrite
{
    AMMU_L1_ALLOCATE_WRITE_DISABLED =
        IPU_LARGE_POLICY_L1_ALLOCATE_NON_ALLOCATE,
    /**< Writes are Not Allocated */
    AMMU_L1_ALLOCATE_WRITE_ENABLED =
        IPU_LARGE_POLICY_L1_ALLOCATE_ALLOCATE
        /**< Writes are Allocated */
}ammuL1AllocateWrite_t;

/**
 * \brief  Enum to set L1 write policy for AMMU page.
 */
typedef enum ammuL1WritePolicy
{
    AMMU_L1_WRITE_POLICY_WRITETHROUGH = IPU_LARGE_POLICY_L1_WR_POLICY_WT,
    /**< Set write policy as Write Through */
    AMMU_L1_WRITE_POLICY_WRITEBACK = IPU_LARGE_POLICY_L1_WR_POLICY_WB
                                     /**< Set write policy as Write Back */
}ammuL1WritePolicy_t;

/**
 *  \brief This structure defines the parameters needed for configuring a
 *         particular AMMU page.
 */
typedef struct ammuPageConfig
{
    uint32_t physicalAddress;
    /**< Physical Address that is mapped to logical address */
    uint32_t logicalAddress;
    /**< Logical Address to which physical address is mapped */
    uint32_t policyRegVal;
    /**< Value of the policy register */
    uint32_t ammuPageType;
    /**< AMMU Page Type. Refer enum #ammuPageType_t for values */
    uint32_t ammuPageNum;
    /**< AMMU Page Number. Number of pages present in hardware differs for
     *   different page types */
}ammuPageConfig_t;

/**
 *  \brief This structure defines the parameters needed for configuring a
 *         particular AMMU page's policy register.
 */
typedef struct ammuPolicyRegParams
{
    uint32_t pageEnable;
    /**< Enable AMMU Page
     *   Refer enum #ammuPageEnable_t for values */
    uint32_t pageSize;
    /**< Size of AMMU Page
     *   Large Page: 512 MB or 32 MB
     *   Medium Page: 256 KB or 128 KB
     *   Small Page: 16 KB or 4 KB
     *   Refer enum #ammuPageSize_t for details */
    uint32_t volatileEnable;
    /**< Volatile Qualifier
     *   Refer enum #ammuVolatileEnable_t for values
     *   Deprecated field. Not supported by hardware.
     */
    uint32_t preloadEnable;
    /**< Preload Region
     *   Refer enum #ammuPreloadEnable_t for values */
    uint32_t cacheExclusionEnable;
    /**< Cache exclusion
     *   Refer enum #ammuCacheExclusionEnable_t for values
     *   Deprecated field. Not supported by hardware.
     */
    uint32_t l1CacheEnable;
    /**< L1 cache enable
     *   Refer enum #ammuL1CacheEnable_t for values */
    uint32_t l1PostedWrite;
    /**< L1 posted write policy
     *   Refer enum #ammuL1PostedWrite_t for values */
    uint32_t l1AllocateWrite;
    /**< L1 allocate write policy
     *   Refer enum #ammuL1AllocateWrite_t for values */
    uint32_t l1WritePolicy;
    /**< L1 write policy
     *   Refer enum #ammuL1WritePolicy_t for values */
    uint32_t l2CacheEnable;
    /**< L2 cache enable
     *   Refer enum #ammuL2CacheEnable_t for values
     *   Deprecated field. Not supported by hardware.
     */
    uint32_t l2PostedWrite;
    /**< L2 posted write policy
     *   Refer enum #ammuL2PostedWrite_t for values
     *   Deprecated field. Not supported by hardware.
     */
    uint32_t l2AllocateWrite;
    /**< L2 allocate write policy
     *   Refer enum #ammuL2AllocateWrite_t for values
     *   Deprecated field. Not supported by hardware.
     */
    uint32_t l2WritePolicy;
    /**< L2 write policy
     *   Refer enum #ammuL2WritePolicy_t for values
     *   Deprecated field. Not supported by hardware.
     */
}ammuPolicyRegParams_t;

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   This function configures the particular AMMU page.
 *
 * \param   baseAddr       Base Address of AMMU registers.
 * \param   ammuPageCfg    AMMU page configuration.
 *
 * \return  status         Whether AMMU page is configured correctly.
 *                         STW_SOK   : Success
 *                         STW_EFAIL : Failure
 */
int32_t AMMUConfigPage(uint32_t baseAddr, const ammuPageConfig_t *ammuPageCfg);

/**
 * \brief   This utility function forms the policy register value depending on
 *          the passed values.
 *
 * \param   policyParams   AMMU Page's policy parameters
 *
 * \return  poilcyRegVal   Value of the policy register.
 */
uint32_t AMMUMakePolicyReg(const ammuPolicyRegParams_t *policyParams);

/**
 * \brief   This function initializes the policy parameters to a default
 *          value.
 *
 * \param   policyParams   AMMU Page's policy parameters.
 *
 * \return  None.
 */
void AMMUInitPolicyParams(ammuPolicyRegParams_t *policyParams);

/* -------------------------------------------------------------------------- */
/*                         Deprecated Enums                                   */
/* -------------------------------------------------------------------------- */

/**
 * \brief  Enum to enable volatile qualifier for AMMU page.
 */
typedef enum ammuVolatileEnable
{
    AMMU_VOLATILE_DISABLED = IPU_LARGE_POLICY_VOLATILE_DISABLE,
    /**< Disable volatile qualifier for AMMU Page */
    AMMU_VOLATILE_ENABLED = IPU_LARGE_POLICY_VOLATILE_ENABLE
                            /**< Enable volatile qualifier for AMMU Page
                            **/
}ammuVolatileEnable_t;

/**
 * \brief  Enum to set Cache Exclusion property of AMMU page.
 */
typedef enum ammuCacheExclusionEnable
{
    AMMU_CACHE_EXCLUSION_DISABLED = IPU_LARGE_POLICY_EXCLUSION_DISABLE,
    /**< Do not send exclusion side-band */
    AMMU_CACHE_EXCLUSION_ENABLED = IPU_LARGE_POLICY_EXCLUSION_ENABLE
                                   /**< Send exclusion side-band */
}ammuCacheExclusionEnable_t;

/**
 * \brief  Enum to enable/disable L2 cache for AMMU page.
 */
typedef enum ammuL2CacheEnable
{
    AMMU_L2_CACHE_DISABLED = IPU_LARGE_POLICY_L2_CACHEABLE_NON_CACHEABLE,
    /**< Disable the L2 Cache */
    AMMU_L2_CACHE_ENABLED = IPU_LARGE_POLICY_L2_CACHEABLE_CACHEABLE
                            /**< Enable the L2 Cache */
}ammuL2CacheEnable_t;

/**
 * \brief  Enum to set L2 posted write policy of AMMU page.
 */
typedef enum ammuL2PostedWrite
{
    AMMU_L2_POSTED_WRITE_DISABLED =
        IPU_LARGE_POLICY_L2_POSTED_NON_POSTED,
    /**< Set L2 Posted Write Policy as Not Posted */
    AMMU_L2_POSTED_WRITE_ENABLED = IPU_LARGE_POLICY_L2_POSTED_POSTED
                                   /**< Set L2 Posted Write Policy as
                                    *   Posted */
}ammuL2PostedWrite_t;

/**
 * \brief  Enum to set L2 Write allocate policy of AMMU page.
 */
typedef enum ammuL2AllocateWrite
{
    AMMU_L2_ALLOCATE_WRITE_DISABLED =
        IPU_LARGE_POLICY_L2_ALLOCATE_NON_ALLOCATE,
    /**< Writes are Not Allocated */
    AMMU_L2_ALLOCATE_WRITE_ENABLED =
        IPU_LARGE_POLICY_L2_ALLOCATE_ALLOCATE
        /**< Writes are Allocated */
}ammuL2AllocateWrite_t;

/**
 * \brief  Enum to set L2 write policy for AMMU page.
 */
typedef enum ammuL2WritePolicy
{
    AMMU_L2_WRITE_POLICY_WRITETHROUGH = IPU_LARGE_POLICY_L2_WR_POLICY_WT,
    /**< Set write policy as Write Through */
    AMMU_L2_WRITE_POLICY_WRITEBACK = IPU_LARGE_POLICY_L2_WR_POLICY_WB
                                     /**< Set write policy as Write Back */
}ammuL2WritePolicy_t;

#ifdef __cplusplus
}

#endif

#endif /*#ifdef AMMU_H_ */
 /** @} */
