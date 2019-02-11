/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     dsp_icfg.c
 *
 *  \brief    This file contains the implementation of the APIs present in the
 *            device abstraction layer file of DSP L1/L2 memory controller.
 *            This include APIs for cache usage and DSP memory protection
 *            unit usage.
 *            This also include related macro definitions.
 *            All APIs should be called with interrupts disabled to
 *            ensure coherency.
 */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Max word count for cache operations.
 * Needs to be cache-line aligned. Use 0xFF00 instead of 0xFFFF to keep in
 * compliant with C64+ requirements.
 */
#define DSPICFG_MAXWC   (0xFF00U)

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void DSPICFGGetRegInfo(uint32_t  memType,
                              uint32_t *pMemBase,
                              uint32_t *pPgSize,
                              uint32_t *pMppaAddr);
/**
 * \brief   Common function for all Cache block operations
 *
 * \param   baseAddr        Base Address of the DSP_ICFG instance.
 *                          (SOC_DSP_ICFG_BASE)
 *
 * \param   blockPtr        Starting address on which the cache-operation
 *                          occurs.
 * \param   byteCnt         Specify the range in number of bytes on which cache
 *                          operation occurs.
 * \param   barRegOfst      Block Access register offset.
 *
 * \return  status          Always STW_SOK for success
 */
static void DSPICFGCacheBlock(uint32_t baseAddr,
                              uint32_t blockPtr,
                              uint32_t byteCnt,
                              uint32_t barRegOfst);

/* ========================================================================== */
/*                          Function Definitions                              */
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
 *                          DSPICFG_MEM_L1ALL is not supported.
 *
 * \param   attributeMask   Permission masks created by bit-wise "OR"ing of
 *                          #dspicfgL2Attribute_t enums.
 *
 *
 * \return  status          Returns STW_SOK indicating success
 *                          Returns STW_EFAIL for invalid arguments
 */
int32_t DSPICFGSetAttribute(uint32_t baseAddr,
                            uint32_t memType,
                            uint32_t pageAddr,
                            uint32_t attributeMask)
{
    int32_t  retVal   = STW_EFAIL;
    uint32_t pageOfst = 0U;
    uint32_t memBase  = 0U;
    uint32_t pgSize   = 0U;
    uint32_t mppaAddr = 0U;

    DSPICFGGetRegInfo(memType,
                      &memBase,
                      &pgSize,
                      &mppaAddr);

    if (0U != memBase)
    {
        retVal = STW_SOK;

        pageOfst = ((pageAddr - memBase) / pgSize) * 4U;
        HW_WR_REG32((baseAddr + mppaAddr + pageOfst), attributeMask);
    }

    return retVal;
}

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
                             uint32_t pageAddr)
{
    uint32_t attributeMask;
    uint32_t pageOfst = 0U;
    uint32_t memBase  = 0U;
    uint32_t pgSize   = 0U;
    uint32_t mppaAddr = 0U;

    DSPICFGGetRegInfo(memType,
                      &memBase,
                      &pgSize,
                      &mppaAddr);

    if (0U != memBase)
    {
        pageOfst      = ((pageAddr - memBase) / pgSize) * 4U;
        attributeMask = HW_RD_REG32(baseAddr + mppaAddr + pageOfst);
    }
    else
    {
        attributeMask = 0U;
    }

    return attributeMask;
}

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
                      uint32_t attributeMask)
{
    int32_t  retVal = STW_EFAIL;
    uint32_t marIdx = (startAddr / MAR_SECTION_SZ);

    /* Only MARn with n>=12 can be modified */
    if (marIdx >= 12U)
    {
        HW_WR_REG32(baseAddr + DSP_MAR(marIdx), attributeMask);
    }

    return retVal;
}

/**
 * \brief   Get the Memory Attribute Register in DSP for the 16MiB page
 *          specified by startAddr.
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
                       uint32_t startAddr)
{
    uint32_t attributeMask = 0U;
    uint32_t marIdx        = (startAddr / MAR_SECTION_SZ);

    attributeMask = HW_RD_REG32(baseAddr + DSP_MAR(marIdx));

    return attributeMask;
}

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
                           uint32_t size)
{
    int32_t  retVal  = STW_EFAIL;
    uint32_t regAddr = 0U;

    if (DSPICFG_MEM_L1D == cacheType)
    {
        regAddr = baseAddr + DSP_L1DCFG;
    }
    if (DSPICFG_MEM_L1P == cacheType)
    {
        regAddr = baseAddr + DSP_L1PCFG;
    }
    if (DSPICFG_MEM_L2 == cacheType)
    {
        regAddr = baseAddr + DSP_L2CFG;
    }

    if (0U != regAddr)
    {
        retVal = STW_SOK;
        HW_WR_REG32(regAddr, size);

        /* Dummy read - CPU stalls in this read until configuration
         * is completed.
         */
        HW_RD_REG32(regAddr);
    }

    return retVal;
}

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
int32_t DSPICFGCacheWriteBackAll(uint32_t baseAddr, uint32_t cacheType)
{
    int32_t  retVal  = STW_EFAIL;
    uint32_t regAddr = 0U;

    if (DSPICFG_MEM_L1D == cacheType)
    {
        regAddr = baseAddr + DSP_L1DWB;
    }
    if (DSPICFG_MEM_L2 == cacheType)
    {
        regAddr = baseAddr + DSP_L2WB;
    }

    if (0U != regAddr)
    {
        retVal = STW_SOK;
        HW_WR_REG32(regAddr, DSP_L1DWB_C_MASK);

        while (0U != HW_RD_REG32(regAddr))
        {
            /* Wait till operation completes */
        }
    }

    return retVal;
}

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
int32_t DSPICFGCacheInvalidateAll(uint32_t baseAddr, uint32_t cacheType)
{
    int32_t  retVal  = STW_EFAIL;
    uint32_t regAddr = 0U;

    if (DSPICFG_MEM_L1P == cacheType)
    {
        regAddr = baseAddr + DSP_L1PINV;
    }
    if (DSPICFG_MEM_L1D == cacheType)
    {
        regAddr = baseAddr + DSP_L1DINV;
    }
    if (DSPICFG_MEM_L2 == cacheType)
    {
        regAddr = baseAddr + DSP_L2INV;
    }

    if (0U != regAddr)
    {
        retVal = STW_SOK;
        HW_WR_REG32(regAddr, DSP_L1DINV_I_MASK);

        while (0U != HW_RD_REG32(regAddr))
        {
            /* Wait till operation completes */
        }
    }

    return retVal;
}

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
                                           uint32_t cacheType)
{
    int32_t  retVal  = STW_EFAIL;
    uint32_t regAddr = 0U;

    if (DSPICFG_MEM_L1P == cacheType)
    {
        regAddr = 0U;
    }
    if (DSPICFG_MEM_L1D == cacheType)
    {
        regAddr = baseAddr + DSP_L1DWBINV;
    }
    if (DSPICFG_MEM_L2 == cacheType)
    {
        regAddr = baseAddr + DSP_L2WBINV;
    }

    if (0U != regAddr)
    {
        retVal = STW_SOK;
        HW_WR_REG32(regAddr, DSP_L1DWBINV_C_MASK);

        while (0U != HW_RD_REG32(regAddr))
        {
            /* Wait till operation completes */
        }
    }

    return retVal;
}

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
                              uint32_t numBytes)
{
    DSPICFGCacheBlock(baseAddr,
                      startAddr,
                      numBytes,
                      DSP_L2WBAR);

    return STW_SOK;
}

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
                               uint32_t numBytes)
{
    DSPICFGCacheBlock(baseAddr,
                      startAddr,
                      numBytes,
                      DSP_L2IBAR);

    return STW_SOK;
}

/**
 * \brief   Write-back and Invalidate all cache as per input
 *          range specified by startAddr and numBytes.
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
int32_t DSPICFGCacheWriteBackInvalidate(uint32_t baseAddr,
                                        uint32_t startAddr,
                                        uint32_t numBytes)
{
    DSPICFGCacheBlock(baseAddr,
                      startAddr,
                      numBytes,
                      DSP_L2WIBAR);

    return STW_SOK;
}

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
                                    uint32_t key3)
{
    int32_t retVal = STW_SOK;

    if (0U == HW_RD_FIELD32(baseAddr + DSP_MPLKSTAT, DSP_MPLKSTAT_LK))
    {
        /* Don't use HW_WR_FIELD32 for DSP_MPLKCMD - it doesn't work since
         * register is write-only
         */
        HW_WR_REG32(baseAddr + DSP_MPLKCMD, DSP_MPLKCMD_KEYR_MASK);
        HW_WR_REG32(baseAddr + DSP_MPLK0, key0);
        HW_WR_REG32(baseAddr + DSP_MPLK1, key1);
        HW_WR_REG32(baseAddr + DSP_MPLK2, key2);
        HW_WR_REG32(baseAddr + DSP_MPLK3, key3);
        HW_WR_REG32(baseAddr + DSP_MPLKCMD, DSP_MPLKCMD_LOCK_MASK);
    }

    if (0U == HW_RD_FIELD32(baseAddr + DSP_MPLKSTAT, DSP_MPLKSTAT_LK))
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

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
                                      uint32_t key3)
{
    int32_t retVal = STW_SOK;

    if (1U == HW_RD_FIELD32(baseAddr + DSP_MPLKSTAT, DSP_MPLKSTAT_LK))
    {
        /* Don't use HW_WR_FIELD32 for DSP_MPLKCMD - it doesn't work since
         * register is write-only
         */
        HW_WR_REG32(baseAddr + DSP_MPLKCMD, DSP_MPLKCMD_KEYR_MASK);
        HW_WR_REG32(baseAddr + DSP_MPLK0, key0);
        HW_WR_REG32(baseAddr + DSP_MPLK1, key1);
        HW_WR_REG32(baseAddr + DSP_MPLK2, key2);
        HW_WR_REG32(baseAddr + DSP_MPLK3, key3);
        HW_WR_REG32(baseAddr + DSP_MPLKCMD, DSP_MPLKCMD_UNLOCK_MASK);
    }

    if (1U == HW_RD_FIELD32(baseAddr + DSP_MPLKSTAT, DSP_MPLKSTAT_LK))
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

/**
 * \brief   Clear the MDMA Error Event register
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPICFGClearMdmaErrEvt(uint32_t baseAddress)
{
    HW_WR_REG32(baseAddress + DSP_MDMAERRCLR, DSP_MDMAERRCLR_CLR_MASK);
    return STW_SOK;
}

/**
 * \brief   Get the fault location as reported by L2 MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultAddr     Address where the first fault was generated
 */
uint32_t DSPICFGGetL2MPUFaultAddr(uint32_t baseAddress)
{
    return HW_RD_REG32(baseAddress + DSP_L2MPFAR);
}

/**
 * \brief   Get the fault status as reported by L2 MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultStatus   Masks created by bit-wise "OR"ing of
 *                        #dspicfgL2Attribute_t enums.
 */
uint32_t DSPICFGGetL2MPUFaultStatus(uint32_t baseAddress)
{
    return (HW_RD_REG32(baseAddress + DSP_L2MPFSR) & 0x3FU);
}

/**
 * \brief   Clear the fault registers for location and status in the L2 MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPICFGClearL2MPUFaultRegs(uint32_t baseAddress)
{
    HW_WR_REG32((baseAddress + DSP_L2MPFCR), 0x1U);
    return STW_SOK;
}

/**
 * \brief   Get the fault location as reported by L1D MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultAddr     Address where the first fault was generated
 */
uint32_t DSPICFGGetL1DMPUFaultAddr(uint32_t baseAddress)
{
    return HW_RD_REG32(baseAddress + DSP_L1DMPFAR);
}

/**
 * \brief   Get the fault status as reported by L1D MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultStatus   Masks created by bit-wise "OR"ing of
 *                        #dspicfgL2Attribute_t enums.
 */
uint32_t DSPICFGGetL1DMPUFaultStatus(uint32_t baseAddress)
{
    return (HW_RD_REG32(baseAddress + DSP_L1DMPFSR) & 0x3FU);
}

/**
 * \brief   Clear the fault registers for location and status in the L1D MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPICFGClearL1DMPUFaultRegs(uint32_t baseAddress)
{
    HW_WR_REG32((baseAddress + DSP_L1DMPFCR), 0x1U);
    return STW_SOK;
}

/**
 * \brief   Get the fault location as reported by L1P MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultAddr     Address where the first fault was generated
 */
uint32_t DSPICFGGetL1PMPUFaultAddr(uint32_t baseAddress)
{
    return HW_RD_REG32(baseAddress + DSP_L1PMPFAR);
}

/**
 * \brief   Get the fault status as reported by L1P MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  faultStatus   Masks created by bit-wise "OR"ing of
 *                        #dspicfgL2Attribute_t enums.
 */
uint32_t DSPICFGGetL1PMPUFaultStatus(uint32_t baseAddress)
{
    return (HW_RD_REG32(baseAddress + DSP_L1PMPFSR) & 0x3FU);
}

/**
 * \brief   Clear the fault registers for location and status in the L1P MPU
 *
 * \param   baseAddress   Base Address of the DSP_ICFG instance
 *                        (SOC_DSP_ICFG_BASE)
 *
 * \return  status        Always returns STW_SOK
 */
int32_t DSPICFGClearL1PMPUFaultRegs(uint32_t baseAddress)
{
    HW_WR_REG32((baseAddress + DSP_L1PMPFCR), 0x1U);
    return STW_SOK;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

static void DSPICFGGetRegInfo(uint32_t  memType,
                              uint32_t *pMemBase,
                              uint32_t *pPgSize,
                              uint32_t *pMppaAddr)
{
    *pMemBase  = 0U;
    *pPgSize   = 0U;
    *pMppaAddr = 0U;

    if (DSPICFG_MEM_L1P == memType)
    {
        *pMemBase  = SOC_DSP_L1P_BASE;
        *pPgSize   = DSPICFG_L1P_PGSZ;
        *pMppaAddr = DSP_L1PMPPA16;
    }

    if (DSPICFG_MEM_L1D == memType)
    {
        *pMemBase  = SOC_DSP_L1D_BASE;
        *pPgSize   = DSPICFG_L1D_PGSZ;
        *pMppaAddr = DSP_L1DMPPA16;
    }

    if (DSPICFG_MEM_L2 == memType)
    {
        *pMemBase  = SOC_DSP_L2_BASE;
        *pPgSize   = DSPICFG_L2_PGSZ;
        *pMppaAddr = DSP_L2MPPA(0U);
    }
}

/*
 * \brief Common implementation for all cache block operations
 *        Based on implementation done in SYS/BIOS v6_41_04_54
 */
static void DSPICFGCacheBlock(uint32_t baseAddr,
                              uint32_t blockPtr,
                              uint32_t byteCnt,
                              uint32_t barRegOfst)
{
    uint32_t wordCnt, alignAddr, tempWordCnt;

    /* WORD COUNT register is always four bytes after BAR register */
    uint32_t wcRegOfst = barRegOfst + sizeof (int32_t);

    /* Align the address if required */
    alignAddr = (uint32_t) blockPtr & (uint32_t) (~(uint32_t) 3U);

    /* convert from byte to word since cache operation takes words */
    wordCnt = (byteCnt + 3U + ((UInt32) blockPtr - alignAddr)) >> 2U;

    while (wordCnt > 0U)
    {
        while (0U != HW_RD_REG32(baseAddr + wcRegOfst))
        {
            /* Wait until previous cache operations are completed */
        }

        /* Setup start address for cache operation */
        HW_WR_REG32((baseAddr + barRegOfst), alignAddr);

        /* Setup word count and trigger cache operation */
        tempWordCnt = (wordCnt > DSPICFG_MAXWC) ? DSPICFG_MAXWC : wordCnt;
        HW_WR_REG32((baseAddr + wcRegOfst), tempWordCnt);

        wordCnt    = wordCnt - tempWordCnt;
        alignAddr += (DSPICFG_MAXWC * sizeof (int32_t));
    }

    while (0U != HW_RD_REG32(baseAddr + wcRegOfst))
    {
        /* Wait until previous cache operations are completed */
    }
}
