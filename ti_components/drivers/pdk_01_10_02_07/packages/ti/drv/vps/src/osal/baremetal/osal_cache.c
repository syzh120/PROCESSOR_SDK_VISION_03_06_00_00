/*
 *  Copyright (c) Texas Instruments Incorporated 2015-2016
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
 */

/**
 *  \file osal_cache.c
 *
 *  \brief OSAL Cache API
 *  This file implements the OSAL cache functionality.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/drv/vps/include/osal/bsp_osal.h>

#if defined (__ARM_ARCH_7A__)
#include <ti/csl/arch/csl_arch.h>
#endif
#if defined (__TI_ARM_V7M4__)
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/* Check macros values. */
#if defined (__ARM_ARCH_7A__)
#if ((BSP_OSAL_CT_L1P != CACHE_A15_TYPE_L1I) ||                             \
     (BSP_OSAL_CT_L1D != CACHE_A15_TYPE_L1D) ||                             \
     (BSP_OSAL_CT_L1 != CACHE_A15_TYPE_L1) ||                               \
     (BSP_OSAL_CT_L2P != CACHE_A15_TYPE_L2I) ||                             \
     (BSP_OSAL_CT_L2D != CACHE_A15_TYPE_L2D) ||                             \
     (BSP_OSAL_CT_L2 != CACHE_A15_TYPE_L2) ||                               \
     (BSP_OSAL_CT_ALLP != CACHE_A15_TYPE_ALLI) ||                           \
     (BSP_OSAL_CT_ALLD != CACHE_A15_TYPE_ALLD) ||                           \
     (BSP_OSAL_CT_ALL != CACHE_A15_TYPE_ALL))
    #error "OSAL and A15 Cache type enums are not same!!"
#endif
#endif

#if defined (__TI_ARM_V7M4__)
#if (BSP_OSAL_WAIT_FOREVER != UNICACHE_WAIT_INFINITE)
    #error "OSAL and UNICACHE wait forever macros are not same!!"
#endif
#if (BSP_OSAL_NO_WAIT != UNICACHE_WAIT_NOWAIT)
    #error "OSAL and UNICACHE no-wait macros are not same!!"
#endif
#endif

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

void BspOsal_cacheDisable(UInt32 type)
{
#if defined (__ARM_ARCH_7A__)
    CACHEA15Disable(type);
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEDisable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
#endif

    return;
}

void BspOsal_cacheEnable(UInt32 type)
{
#if defined (__ARM_ARCH_7A__)
    CACHEA15Enable(type);
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEEnable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
#endif

    return;
}

void BspOsal_cacheInv(void *blockPtr,
                      UInt32 byteCnt,
                      UInt32 type,
                      UInt32 timeOut)
{
#if defined (__ARM_ARCH_7A__)
    CACHEA15Invalidate(type, (uint32_t) blockPtr, byteCnt);
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEInvalidate(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        (uint32_t) blockPtr,
        byteCnt,
        timeOut);
#endif

    return;
}

void BspOsal_cacheInvAll(void)
{
#if defined (__ARM_ARCH_7A__)
    CACHEA15InvalidateL1IAll();
    CACHEA15InvalidateL1DAll();
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEInvalidateAll(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        UNICACHE_WAIT_INFINITE);
#endif

    return;
}

void BspOsal_cacheWb(void *blockPtr,
                     UInt32 byteCnt,
                     UInt32 type,
                     UInt32 timeOut)
{
#if defined (__ARM_ARCH_7A__)
    CACHEA15WriteBack((uint32_t) blockPtr, byteCnt);
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEWriteBack(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        (uint32_t) blockPtr,
        byteCnt,
        timeOut);
#endif

    return;
}

void BspOsal_cacheWbAll(void)
{
#if defined (__ARM_ARCH_7A__)
    CACHEA15WriteBackAll();
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEWriteBackAll(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        UNICACHE_WAIT_INFINITE);
#endif

    return;
}

void BspOsal_cacheWbInv(void *blockPtr,
                        UInt32 byteCnt,
                        UInt32 type,
                        UInt32 timeOut)
{
#if defined (__ARM_ARCH_7A__)
    CACHEA15WriteBackAndInvalidate((uint32_t) blockPtr, byteCnt);
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEWriteBackAndInvalidate(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        (uint32_t) blockPtr,
        byteCnt,
        timeOut);
#endif

    return;
}

void BspOsal_cacheWbInvAll(void)
{
#if defined (__ARM_ARCH_7A__)
    CACHEA15WriteBackAndInvalidateAll();
#endif

#if defined (__TI_ARM_V7M4__)
    UNICACHEWriteBackAndInvalidateAll(
        SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE,
        UNICACHE_WAIT_INFINITE);
#endif

    return;
}
