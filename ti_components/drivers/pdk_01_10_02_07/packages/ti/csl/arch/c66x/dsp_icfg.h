/*
 *  Copyright (C) 2015-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \ingroup CSL_ARCH_C66X
 *  \defgroup CSL_ARCH_C66X_ICFG ICFG
 *
 *  @{
 */
/**
 *  \file     dsp_icfg.h
 *
 *  \brief    This file contains the prototypes of the APIs present in the
 *            device abstraction layer file of ICFG
 *            in the C66x DSP subsytems.
 *            This also include related macro definitions.
 *            All APIs should be called with interrupts disabled to
 *            ensure coherency.
 */

#ifndef DSP_ICFG_H_
#define DSP_ICFG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
/* None */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  Page size for L1P memory protection
 */
#define DSPICFG_L1P_PGSZ             (2048U)

/**
 * \brief  Page size for L1D memory protection
 */
#define DSPICFG_L1D_PGSZ             (2048U)

/**
 * \brief  Page size for L2 memory protection
 */
#define DSPICFG_L2_PGSZ              (16U * 1024U)

/**
 * \brief  Page size for MAR registers
 */
#define MAR_SECTION_SZ  (16U * 1024U * 1024U)

/**
 * \brief  Bit-Fields missing in hw_dsp_icfg.h
 */
#define DSP_MAR_PCX_SHIFT   (2U)
#define DSP_MAR_PCX_MASK    (0x00000004U)
#define DSP_MAR_WTE_SHIFT   (1U)
#define DSP_MAR_WTE_MASK    (0x00000002U)

/**
 * \brief  L1P Cache Line Size
 */
#define DSPICFG_L1P_CACHE_LINE_SIZE    (32U)

/**
 * \brief  L1D Cache Line Size
 */
#define DSPICFG_L1D_CACHE_LINE_SIZE    (64U)

/**
 * \brief  L2 Cache Line Size
 */
#define DSPICFG_L2_CACHE_LINE_SIZE    (128U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/**
 * \brief  Enum to create mask for MAR attributes.
 *         Refer to device specific documents to check if PCX and WTE are
 *         available.
 */
typedef enum dspicfgMARAttribute
{
    DSPICFG_MAR_PC = DSP_MAR_PC_MASK,
    /**< Specify if region is cacheable */
    DSPICFG_MAR_WTE = DSP_MAR_WTE_MASK,
    /**< Specify if region is write-through cacheable */
    DSPICFG_MAR_PCX = DSP_MAR_PCX_MASK,
    /**< Specify if region is cacheable in external cache like MSMC */
    DSPICFG_MAR_PFX = DSP_MAR_PFX_MASK
                      /**< Specify if region is pre-fetchable. Used by
                       *XMC/L2-Memory controller */
}dspicfgMARAttribute_t;

/**
 * \brief  Enum to create mask for L2MPPA (L2 memory protection attributes)
 *         registers for DSP L1P/L1D/L2 Memory .
 *
 */
typedef enum dspicfgL2Attribute
{
    DSPICFG_L2MPPA_LOCAL = DSP_L2MPPA_LOCAL_MASK,
    /**< Enable bit for Local DSP access to L1/L2 */
    DSPICFG_L2MPPA_SR = DSP_L2MPPA_SR_MASK,
    /**< Enable bit Supervisor mode Read access */
    DSPICFG_L2MPPA_SW = DSP_L2MPPA_SW_MASK,
    /**< Enable bit Supervisor mode Write access */
    DSPICFG_L2MPPA_SX = DSP_L2MPPA_SX_MASK,
    /**< Enable bit Supervisor mode Execute access */
    DSPICFG_L2MPPA_UR = DSP_L2MPPA_UR_MASK,
    /**< Enable bit User mode Read access */
    DSPICFG_L2MPPA_UW = DSP_L2MPPA_UW_MASK,
    /**< Enable bit User mode Write access */
    DSPICFG_L2MPPA_UX = DSP_L2MPPA_UX_MASK,
    /**< Enable bit User mode Execute access */
    DSPICFG_L2MPPA_AID_0 = DSP_L2MPPA_AID0_MASK,
    /**< Enable bit AID = 0 access */
    DSPICFG_L2MPPA_AID_1 = DSP_L2MPPA_AID1_MASK,
    /**< Enable bit AID = 1 access */
    DSPICFG_L2MPPA_AID_2 = DSP_L2MPPA_AID2_MASK,
    /**< Enable bit AID = 2 access */
    DSPICFG_L2MPPA_AID_3 = DSP_L2MPPA_AID3_MASK,
    /**< Enable bit AID = 3 access */
    DSPICFG_L2MPPA_AID_4 = DSP_L2MPPA_AID4_MASK,
    /**< Enable bit AID = 4 access */
    DSPICFG_L2MPPA_AID_5 = DSP_L2MPPA_AID5_MASK,
    /**< Enable bit AID = 5 access */
    DSPICFG_L2MPPA_AID_X = DSP_L2MPPA_AIDX_MASK
                           /**< Enable bit AID >= 6 access */
}dspicfgL2Attribute_t;

/**
 * \brief  Enum to specify cache type in cache APIs provided in the file.
 *
 */
typedef enum dspicfgMemType
{
    DSPICFG_MEM_L1D,
    /**< L1 Data memory */
    DSPICFG_MEM_L1P,
    /**< L1 Program memory */
    DSPICFG_MEM_L2
    /**< L2 memory */
}dspicfgMemType_t;

/**
 * \brief  Enum to specify L1 cache size in cache APIs provided in the file.
 *
 */
typedef enum dspicfgCacheSizeL1
{
    DSPICFG_CACHE_SIZE_L1_DISABLED = 0x0U,
    DSPICFG_CACHE_SIZE_L1_4K       = 0x1U,
    DSPICFG_CACHE_SIZE_L1_8K       = 0x2U,
    DSPICFG_CACHE_SIZE_L1_16K      = 0x3U,
    DSPICFG_CACHE_SIZE_L1_32K      = 0x4U,
    DSPICFG_CACHE_SIZE_L1_MAX      = 0x5U
}dspicfgCacheSizeL1_t;

/**
 * \brief  Enum to specify L2 cache size in cache APIs provided in the file.
 *         If the devices L2 memory is less than the specified value, all
 *         L2 memory will be used as cache.
 *         eg: Using DSPICFG_CACHE_SIZE_L2_1024K in TDA2x will be same as
 *             using DSPICFG_CACHE_SIZE_L2_256K or DSPICFG_CACHE_SIZE_L2_512K
 *             or DSPICFG_CACHE_SIZE_L2_MAX since total L2 memory is 256kiB.
 */
typedef enum dspicfgCacheSizeL2
{
    DSPICFG_CACHE_SIZE_L2_DISABLED = 0x0U,
    DSPICFG_CACHE_SIZE_L2_32K      = 0x1U,
    DSPICFG_CACHE_SIZE_L2_64K      = 0x2U,
    DSPICFG_CACHE_SIZE_L2_128K     = 0x3U,
    DSPICFG_CACHE_SIZE_L2_256K     = 0x4U,
    DSPICFG_CACHE_SIZE_L2_512K     = 0x5U,
    DSPICFG_CACHE_SIZE_L2_1024K    = 0x6U,
    DSPICFG_CACHE_SIZE_L2_MAX      = 0x7U
}dspicfgCacheSizeL2_t;

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/**
 * \brief   Set memory protection attributes for specified L1/L2 memory page.
 *          Should be called in supervisor mode only.
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   pageAddr        Starting address of the page in L1/L2 Memory which
 *                          needs to be protected.
 *                          Base of L1P Memory address is assumed to be
 *                          SOC_DSP_L1P_BASE.
 *                          Base of L1D Memory address is assumed to be
 *                          SOC_DSP_L1D_BASE.
 *                          Base of L2 Memory address is assumed to be
 *                          SOC_DSP_L2_BASE.
 *                          Therefore, pageAddr == SOC_DSP_L2_BASE will
 *                          configure 0th page of L2, i.e, (SOC_DSP_L2_BASE to
 *                          (SOC_DSP_L2_BASE + L2_PAGE_SIZE)).
 *                          Similar convention applies for L1P/L1D.
 *                          All addresses will be assumed to be aligned as per
 *                          DSPICFG_L2_PGSZ, DSPICFG_L1P_PGSZ or
 *                          DSPICFG_L1D_PGSZ
 *
 * \param   memType         Use enum #dspicfgMemType_t to specify memory.
 *
 * \param   attributeMask   Permission masks created by bit-wise "OR"ing of
 *                          #dspicfgL2Attribute_t enums.
 *
 * \return  status          Returns STW_SOK indicating success
 *                          Returns STW_EFAIL for invalid arguments
 */
int32_t DSPICFGSetAttribute(uint32_t baseAddr,
                            uint32_t memType,
                            uint32_t pageAddr,
                            uint32_t attributeMask);

/**
 * \brief   Get memory protection attributes for specified L1/L2 memory page.
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   pageAddr        Starting address of the page in L1/L2 Memory which
 *                          needs to be protected.
 *                          Base of L1P Memory address is assumed to be
 *                          SOC_DSP_L1P_BASE.
 *                          Base of L1D Memory address is assumed to be
 *                          SOC_DSP_L1D_BASE.
 *                          Base of L2 Memory address is assumed to be
 *                          SOC_DSP_L2_BASE.
 *                          Therefore, pageAddr == SOC_DSP_L2_BASE will
 *                          configure 0th page of L2, i.e, (SOC_DSP_L2_BASE to
 *                          (SOC_DSP_L2_BASE + L2_PAGE_SIZE)).
 *                          Similar convention applies for L1P/L1D.
 *                          All addresses will be assumed to be aligned as per
 *                          DSPICFG_L2_PGSZ, DSPICFG_L1P_PGSZ or
 *                          DSPICFG_L1D_PGSZ
 *
 * \param   memType         Use enum #dspicfgMemType_t to specify memory.
 *
 * \return  attributeMask   Permission masks created by bit-wise "OR"ing of
 *                          #dspicfgL2Attribute_t enums.
 *
 */
uint32_t DSPICFGGetAttribute(uint32_t baseAddr,
                             uint32_t memType,
                             uint32_t pageAddr);

/**
 * \brief   Configure the Memory Attribute Register in DSP for the 16MiB page
 *          specified by startAddr. Should be called in supervisor mode only.
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   startAddr       Specify the 16MiB aligned start address.
 *
 * \param   attributeMask   MAR attribute created by bit-wise "OR"ing of
 *                          #dspicfgMARAttribute_t enums.
 *                          For range 0x0C00_0000 to 0x0FFF_FFFF, only PFX can
 *                          be set.
 *
 * \return  status          Return -1 in case of invalid startAddress.
 *                          0 indicating success in all other cases.
 */
int32_t DSPICFGSetMAR(uint32_t baseAddr,
                      uint32_t startAddr,
                      uint32_t attributeMask);

/**
 * \brief   Get the Memory Attribute Register in DSP for the 16MiB page
 *          specified by startAddr
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   startAddr       Specify the 16MiB aligned start address.
 *
 * \return  attributeMask   MAR attribute created by bit-wise "OR"ing of
 *                          #dspicfgMARAttribute_t enums.
 */
uint32_t DSPICFGGetMAR(uint32_t baseAddr,
                       uint32_t startAddr);

/**
 * \brief   Enable/Disable specified cache.
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   cacheType       Use enum #dspicfgMemType_t to specify the cache.
 *
 * \param   size            Specify cache size. Remaining memory will be
 *                          available as RAM. Argument ignored if enable is 0.
 *                          Use #dspicfgCacheSizeL1_t or #dspicfgCacheSizeL2_t
 *                          enums for L1 and L2 caches respectively.
 *                          Use DSPICFG_CACHE_SIZEL1_DISABLE or
 *                          DSPICFG_CACHE_SIZEL2_DISABLE to disable cache.
 *
 * \return  status          STW_SOK/STW_EFAIL for success/fail
 */
int32_t DSPICFGCacheEnable(uint32_t baseAddr,
                           uint32_t cacheType,
                           uint32_t size);

/**
 * \brief   Write-back all cache specified by cacheType.
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   cacheType       Use enum #dspicfgMemType_t
 *                          Using argument DSPICFG_MEM_L2 causes, same
 *                          operation on L1D cache as well.
 *
 * \return  status          STW_SOK/STW_EFAIL for success/fail
 */
int32_t DSPICFGCacheWriteBackAll(uint32_t baseAddr, uint32_t cacheType);

/**
 * \brief   Invalidate all cache specified by cacheType.
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   cacheType       Use enum #dspicfgMemType_t
 *                          Using argument DSPICFG_MEM_L2 causes, same
 *                          operation on L1D cache as well.
 *
 * \return  status          STW_SOK/STW_EFAIL for success/fail
 */
int32_t DSPICFGCacheInvalidateAll(uint32_t baseAddr, uint32_t cacheType);

/**
 * \brief   Write-back and invalidate all cache specified by cacheType.
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   cacheType       Use enum #dspicfgMemType_t
 *                          Using argument DSPICFG_MEM_L2 causes, same
 *                          operation on L1D cache as well.
 *
 * \return  status          STW_SOK/STW_EFAIL for success/fail
 */
int32_t DSPICFGCacheWriteBackInvalidateAll(uint32_t baseAddr,
                                           uint32_t cacheType);

/**
 * \brief   Write-back all cache as per input range
 *          specified by startAddr and numBytes.
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   startAddr       Starting address on which the cache-operation
 *                          occurs.
 *
 * \param   numBytes        Specify the range in number of bytes on which cache
 *                          operation occurs
 *
 * \return  status          Always STW_SOK for success
 */
int32_t DSPICFGCacheWriteBack(uint32_t baseAddr,
                              uint32_t startAddr,
                              uint32_t numBytes);

/**
 * \brief   Invalidate all cache as per input range
 *          specified by startAddr and numBytes.
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   startAddr       Starting address on which the cache-operation
 *                          occurs.
 *
 * \param   numBytes        Specify the range in number of bytes on which cache
 *                          operation occurs
 *
 * \return  status          Always STW_SOK for success
 */
int32_t DSPICFGCacheInvalidate(uint32_t baseAddr,
                               uint32_t startAddr,
                               uint32_t numBytes);

/**
 * \brief   Write-back and Invalidate all cache as per input
 *          range specified by startAddr and numBytes.
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   startAddr       Starting address on which the` cache-operation
 *                          occurs.
 *
 * \param   numBytes        Specify the range in number of bytes on which cache
 *                          operation occurs
 *
 * \return  status          Always STW_SOK for success
 */
int32_t DSPICFGCacheWriteBackInvalidate(uint32_t baseAddr,
                                        uint32_t startAddr,
                                        uint32_t numBytes);

/**
 * \brief   Lock Memory Protection registers for Memory Protection Unit and
 *          XMC
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   key0            First Key
 * \param   key1            Second Key
 * \param   key2            Third Key
 * \param   key3            Fourth Key
 *
 * \return  status          Returns STW_SOK if the Memory Protection Lock
 *                          status is LOCKed
 */
int32_t DSPICFGMemoryProtectionLock(uint32_t baseAddr,
                                    uint32_t key0,
                                    uint32_t key1,
                                    uint32_t key2,
                                    uint32_t key3);
/**
 * \brief   Unlock Memory Protection registers for Memory Protection Unit and
 *          XMC
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   key0            First Key
 * \param   key1            Second Key
 * \param   key2            Third Key
 * \param   key3            Fourth Key
 *
 * \return  status          Returns STW_SOK if the Memory Protection Lock
 *                          status is UNLOCKed
 */
int32_t DSPICFGMemoryProtectionUnlock(uint32_t baseAddr,
                                      uint32_t key0,
                                      uint32_t key1,
                                      uint32_t key2,
                                      uint32_t key3);

/**
 * \brief   Clear the MDMA Error Event register
 *
 * \param   baseAddress   Base Address of the XMC instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPICFGClearMdmaErrEvt(uint32_t baseAddress);

/**
 * \brief   Get the fault location as reported by L2 MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultAddr     Address where the first fault was generated
 */
uint32_t DSPICFGGetL2MPUFaultAddr(uint32_t baseAddress);

/**
 * \brief   Get the fault status as reported by L2 MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultStatus   Masks created by bit-wise "OR"ing of
 *                        #dspicfgL2Attribute_t enums.
 */
uint32_t DSPICFGGetL2MPUFaultStatus(uint32_t baseAddress);

/**
 * \brief   Clear the fault registers for location and status in the L2 MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPICFGClearL2MPUFaultRegs(uint32_t baseAddress);

/**
 * \brief   Get the fault location as reported by L1D MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultAddr     Address where the first fault was generated
 */
uint32_t DSPICFGGetL1DMPUFaultAddr(uint32_t baseAddress);

/**
 * \brief   Get the fault status as reported by L1D MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultStatus   Masks created by bit-wise "OR"ing of
 *                        #dspicfgL2Attribute_t enums.
 */
uint32_t DSPICFGGetL1DMPUFaultStatus(uint32_t baseAddress);

/**
 * \brief   Clear the fault registers for location and status in the L1D MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPICFGClearL1DMPUFaultRegs(uint32_t baseAddress);

/**
 * \brief   Get the fault location as reported by L1P MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultAddr     Address where the first fault was generated
 */
uint32_t DSPICFGGetL1PMPUFaultAddr(uint32_t baseAddress);

/**
 * \brief   Get the fault status as reported by L1P MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultStatus   Masks created by bit-wise "OR"ing of
 *                        #dspicfgL2Attribute_t enums.
 */
uint32_t DSPICFGGetL1PMPUFaultStatus(uint32_t baseAddress);

/**
 * \brief   Clear the fault registers for location and status in the L1P MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPICFGClearL1PMPUFaultRegs(uint32_t baseAddress);

#ifdef __cplusplus
}
#endif

#endif /* DSP_ICFG_H_ */
 /** @} */
