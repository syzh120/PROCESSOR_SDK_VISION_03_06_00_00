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
 *  \file     unicache.c
 *
 *  \brief    This file contains the Uni-cache HAL APIs.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/hw_types.h>
#include <cslr_cache.h>
#include <unicache.h>

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

void UNICACHEEnable(uint32_t baseAddr)
{
    /* Check if Uni-Cache is already enabled to prevent hard fault */
    if (IPU_UNICACHE_CONFIG_BYPASS_NORMAL !=
        HW_RD_FIELD32(baseAddr + IPU_UNICACHE_CONFIG,
                      IPU_UNICACHE_CONFIG_BYPASS))
    {
        /* Enable Uni-Cache */
        HW_WR_FIELD32(baseAddr + IPU_UNICACHE_CONFIG,
                      IPU_UNICACHE_CONFIG_BYPASS,
                      IPU_UNICACHE_CONFIG_BYPASS_NORMAL);
    }
}

void UNICACHEDisable(uint32_t baseAddr)
{
    /* Disable Uni-Cache */
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_CONFIG,
                  IPU_UNICACHE_CONFIG_BYPASS,
                  IPU_UNICACHE_CONFIG_BYPASS_BYPASS);
}

void UNICACHEInvalidateCacheLine(uint32_t baseAddr,
                                 uint32_t maintenanceAddr)
{
    /* Invalidate One Cache Line */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, maintenanceAddr);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND, maintenanceAddr);
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_INVALIDATE,
                  IPU_UNICACHE_MAINT_INVALIDATE_ENABLE);
    /* App should take care of timing requirements */
}

int32_t UNICACHEWaitCacheMaint(uint32_t baseAddr, uint32_t numRetries)
{
    int32_t  retVal = STW_SOK;
    if (UNICACHE_WAIT_INFINITE != numRetries)
    {
        /* Wait for operation to finish */
        while ((0U != numRetries) &&
               (IPU_UNICACHE_MAINT_INVALIDATE_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_INVALIDATE)))
        {
            numRetries--;
        }
        if (0U == numRetries)
        {
            /* Check if operation has completed in stipulated time */
            if (IPU_UNICACHE_MAINT_INVALIDATE_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_INVALIDATE))
            {
                /* Mark result as fail if operation is still not finished */
                retVal = STW_EFAIL;
            }
        }
    }
    else
    {
        while (IPU_UNICACHE_MAINT_INVALIDATE_DISABLE !=
               HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                             IPU_UNICACHE_MAINT_INVALIDATE))
        {
            /* Wait Infinitely */
        }
    }
    return retVal;
}
int32_t UNICACHEInvalidate(uint32_t baseAddr,
                           uint32_t startAddress,
                           uint32_t byteCount,
                           uint32_t tWait)
{
    int32_t  retVal = STW_SOK;
    uint32_t lineAddr;
    uint32_t timeToWait = tWait;

    /* Cache operations are more efficient if performed on single line for
     * buffers before size UNICACHE_MAX_LINE_MODE_BUFF_SIZE
     */
    if (byteCount <= UNICACHE_MAX_LINE_MODE_BUFF_SIZE)
    {
        /* Align line address according to UNICACHE_LINE_SIZE */
        lineAddr = startAddress & UNICACHE_LINE_ADDRESS_MASK;
        do
        {
            /* Invalidate Cache Line */
            UNICACHEInvalidateCacheLine(baseAddr, lineAddr);
            lineAddr += UNICACHE_LINE_SIZE;

            while (IPU_UNICACHE_MAINT_INVALIDATE_DISABLE !=
                   HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                 IPU_UNICACHE_MAINT_INVALIDATE))
            {
                /* Wait for maintenance operation to finish */
            }
        } while (lineAddr < (startAddress + byteCount));
    }
    else
    {
        /* Perform cache operation on whole block */
        HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, startAddress);
        HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND,
                    (startAddress + (byteCount - 1U)));
        HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                      IPU_UNICACHE_MAINT_INVALIDATE,
                      IPU_UNICACHE_MAINT_INVALIDATE_ENABLE);

        if (UNICACHE_WAIT_INFINITE != timeToWait)
        {
            /* Wait for operation to finish */
            while ((0U != timeToWait) &&
                   (IPU_UNICACHE_MAINT_INVALIDATE_DISABLE !=
                    HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                  IPU_UNICACHE_MAINT_INVALIDATE)))
            {
                timeToWait--;
            }
            if (0U == timeToWait)
            {
                /* Check if operation has completed in stipulated time */
                if (IPU_UNICACHE_MAINT_INVALIDATE_DISABLE !=
                    HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                  IPU_UNICACHE_MAINT_INVALIDATE))
                {
                    /* Mark result as fail if operation is still not finished */
                    retVal = STW_EFAIL;
                }
            }
        }
        else
        {
            while (IPU_UNICACHE_MAINT_INVALIDATE_DISABLE !=
                   HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                 IPU_UNICACHE_MAINT_INVALIDATE))
            {
                /* Wait Infinitely */
            }
        }
    }
    return retVal;
}

void UNICACHEWriteBackCacheLine(uint32_t baseAddr,
                                uint32_t maintenanceAddr)
{
    /* Evict One Cache Line */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, maintenanceAddr);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND, maintenanceAddr);
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_CLEAN,
                  IPU_UNICACHE_MAINT_CLEAN_ENABLE);
    /* App should take care of timing requirements */
}

int32_t UNICACHEWriteBack(uint32_t baseAddr,
                          uint32_t startAddress,
                          uint32_t byteCount,
                          uint32_t tWait)
{
    int32_t  retVal = STW_SOK;
    uint32_t lineAddr;
    uint32_t timeToWait = tWait;

    /* Cache operations are more efficient if performed on single line for
     * buffers before size UNICACHE_MAX_LINE_MODE_BUFF_SIZE
     */
    if (byteCount <= UNICACHE_MAX_LINE_MODE_BUFF_SIZE)
    {
        /* Align line address according to UNICACHE_LINE_SIZE */
        lineAddr = startAddress & UNICACHE_LINE_ADDRESS_MASK;
        do
        {
            /* Evict Cache Line */
            UNICACHEWriteBackCacheLine(baseAddr, lineAddr);
            lineAddr += UNICACHE_LINE_SIZE;
            while (IPU_UNICACHE_MAINT_CLEAN_DISABLE !=
                   HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                 IPU_UNICACHE_MAINT_CLEAN))
            {
                /* Wait for maintenance operation to finish */
            }
        } while (lineAddr < (startAddress + byteCount));
    }
    else
    {
        /* Perform cache operation on whole block */
        HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, startAddress);
        HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND,
                    (startAddress + (byteCount - 1U)));
        HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                      IPU_UNICACHE_MAINT_CLEAN,
                      IPU_UNICACHE_MAINT_CLEAN_ENABLE);

        if (UNICACHE_WAIT_INFINITE != timeToWait)
        {
            /* Wait for operation to finish */
            while ((0U != timeToWait) &&
                   (IPU_UNICACHE_MAINT_CLEAN_DISABLE !=
                    HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                  IPU_UNICACHE_MAINT_CLEAN)))
            {
                timeToWait--;
            }
            if (0U == timeToWait)
            {
                /* Check if operation has completed in stipulated time */
                if (IPU_UNICACHE_MAINT_CLEAN_DISABLE !=
                    HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                  IPU_UNICACHE_MAINT_CLEAN))
                {
                    /* Mark result as fail if operation is still not finished */
                    retVal = STW_EFAIL;
                }
            }
        }
        else
        {
            while (IPU_UNICACHE_MAINT_CLEAN_DISABLE !=
                   HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                 IPU_UNICACHE_MAINT_CLEAN))
            {
                /* Wait Infinitely */
            }
        }
    }
    return retVal;
}

void UNICACHELockCacheLine(uint32_t baseAddr,
                           uint32_t maintenanceAddr)
{
    /* Lock One Cache Line */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, maintenanceAddr);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND, maintenanceAddr);
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_LOCK,
                  IPU_UNICACHE_MAINT_LOCK_ENABLE);
    /* App should take care of timing requirements */
}

int32_t UNICACHELock(uint32_t baseAddr,
                     uint32_t startAddress,
                     uint32_t byteCount,
                     uint32_t tWait)
{
    int32_t  retVal     = STW_SOK;
    uint32_t timeToWait = tWait;

    /* Perform cache operation on whole block */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, startAddress);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND,
                (startAddress + (byteCount - 1U)));
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_LOCK,
                  IPU_UNICACHE_MAINT_LOCK_ENABLE);

    if (UNICACHE_WAIT_INFINITE != timeToWait)
    {
        /* Wait for operation to finish */
        while ((0U != timeToWait) &&
               (IPU_UNICACHE_MAINT_LOCK_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_LOCK)))
        {
            timeToWait--;
        }
        if (0U == timeToWait)
        {
            /* Check if operation has completed in stipulated time */
            if (IPU_UNICACHE_MAINT_LOCK_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_LOCK))
            {
                /* Mark result as fail if operation is still not finished */
                retVal = STW_EFAIL;
            }
        }
    }
    else
    {
        while (IPU_UNICACHE_MAINT_LOCK_DISABLE !=
               HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                             IPU_UNICACHE_MAINT_LOCK))
        {
            /* Wait Infinitely */
        }
    }
    return retVal;
}

void UNICACHEUnlockCacheLine(uint32_t baseAddr,
                             uint32_t maintenanceAddr)
{
    /* Unlock One Cache Line */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, maintenanceAddr);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND, maintenanceAddr);
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_UNLOCK,
                  IPU_UNICACHE_MAINT_UNLOCK_ENABLE);
    /* App should take care of timing requirements */
}

int32_t UNICACHEUnlock(uint32_t baseAddr,
                       uint32_t startAddress,
                       uint32_t byteCount,
                       uint32_t tWait)
{
    int32_t  retVal     = STW_SOK;
    uint32_t timeToWait = tWait;

    /* Perform cache operation on whole block */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, startAddress);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND,
                (startAddress + (byteCount - 1U)));
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_UNLOCK,
                  IPU_UNICACHE_MAINT_UNLOCK_ENABLE);

    if (UNICACHE_WAIT_INFINITE != timeToWait)
    {
        /* Wait for operation to finish */
        while ((0U != timeToWait) &&
               (IPU_UNICACHE_MAINT_UNLOCK_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_UNLOCK)))
        {
            timeToWait--;
        }
        if (0U == timeToWait)
        {
            /* Check if operation has completed in stipulated time */
            if (IPU_UNICACHE_MAINT_UNLOCK_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_UNLOCK))
            {
                /* Mark result as fail if operation is still not finished */
                retVal = STW_EFAIL;
            }
        }
    }
    else
    {
        while (IPU_UNICACHE_MAINT_UNLOCK_DISABLE !=
               HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                             IPU_UNICACHE_MAINT_UNLOCK))
        {
            /* Wait Infinitely */
        }
    }
    return retVal;
}

void UNICACHEPreloadCacheLine(uint32_t baseAddr,
                              uint32_t maintenanceAddr)
{
    /* Pre-load One Cache Line */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, maintenanceAddr);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND, maintenanceAddr);
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_PRELOAD,
                  IPU_UNICACHE_MAINT_PRELOAD_ENABLE);
    /* App should take care of timing requirements */
}

int32_t UNICACHEPreload(uint32_t baseAddr,
                        uint32_t startAddress,
                        uint32_t byteCount,
                        uint32_t tWait)
{
    int32_t  retVal     = STW_SOK;
    uint32_t timeToWait = tWait;

    /* Perform cache operation on whole block */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, startAddress);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND,
                (startAddress + (byteCount - 1U)));
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_PRELOAD,
                  IPU_UNICACHE_MAINT_PRELOAD_ENABLE);

    if (UNICACHE_WAIT_INFINITE != timeToWait)
    {
        /* Wait for operation to finish */
        while ((0U != timeToWait) &&
               (IPU_UNICACHE_MAINT_PRELOAD_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_PRELOAD)))
        {
            timeToWait--;
        }
        if (0U == timeToWait)
        {
            /* Check if operation has completed in stipulated time */
            if (IPU_UNICACHE_MAINT_PRELOAD_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_PRELOAD))
            {
                /* Mark result as fail if operation is still not finished */
                retVal = STW_EFAIL;
            }
        }
    }
    else
    {
        while (IPU_UNICACHE_MAINT_PRELOAD_DISABLE !=
               HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                             IPU_UNICACHE_MAINT_PRELOAD))
        {
            /* Wait Infinitely */
        }
    }

    return retVal;
}

void UNICACHEWriteBackAndInvalidateCacheLine(uint32_t baseAddr,
                                             uint32_t maintenanceAddr)
{
    /* Evict and Invalidate One Cache Line */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, maintenanceAddr);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND, maintenanceAddr);
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_CLEANANDINVALIDATE,
                  IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_ENABLE);
    /* App should take care of timing requirements */
}

int32_t UNICACHEWriteBackAndInvalidate(uint32_t baseAddr,
                                       uint32_t startAddress,
                                       uint32_t byteCount,
                                       uint32_t tWait)
{
    int32_t  retVal = STW_SOK;
    uint32_t lineAddr;
    uint32_t timeToWait = tWait;

    /* Cache operations are more efficient if performed on single line for
     * buffers before size UNICACHE_MAX_LINE_MODE_BUFF_SIZE
     */
    if (byteCount <= UNICACHE_MAX_LINE_MODE_BUFF_SIZE)
    {
        /* Align line address according to UNICACHE_LINE_SIZE */
        lineAddr = startAddress & UNICACHE_LINE_ADDRESS_MASK;
        do
        {
            /* Evict and Invalidate Cache Line */
            UNICACHEWriteBackAndInvalidateCacheLine(baseAddr, lineAddr);
            lineAddr += UNICACHE_LINE_SIZE;
            while (IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_DISABLE !=
                   HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                 IPU_UNICACHE_MAINT_CLEANANDINVALIDATE))
            {
                /* Wait for maintenance operation to finish */
            }
        } while (lineAddr < (startAddress + byteCount));
    }
    else
    {
        /* Perform cache operation on whole block */
        HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, startAddress);
        HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND,
                    (startAddress + (byteCount - 1U)));
        HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                      IPU_UNICACHE_MAINT_CLEANANDINVALIDATE,
                      IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_ENABLE);

        if (UNICACHE_WAIT_INFINITE != timeToWait)
        {
            /* Wait for operation to finish */
            while ((0U != timeToWait) &&
                   (IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_DISABLE !=
                    HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                  IPU_UNICACHE_MAINT_CLEANANDINVALIDATE)))
            {
                timeToWait--;
            }
            if (0U == timeToWait)
            {
                /* Check if operation has completed in stipulated time */
                if (IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_DISABLE !=
                    HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                  IPU_UNICACHE_MAINT_CLEANANDINVALIDATE))
                {
                    /* Mark result as fail if operation is still not finished */
                    retVal = STW_EFAIL;
                }
            }
        }
        else
        {
            while (IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_DISABLE !=
                   HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                                 IPU_UNICACHE_MAINT_CLEANANDINVALIDATE))
            {
                /* Wait Infinitely */
            }
        }
    }
    return retVal;
}

void UNICACHEPreloadAndLockCacheLine(uint32_t baseAddr,
                                     uint32_t maintenanceAddr)
{
    /* Pre-load and lock One Cache Line */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, maintenanceAddr);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND, maintenanceAddr);
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_PRELOADANDLOCK,
                  IPU_UNICACHE_MAINT_PRELOADANDLOCK_ENABLE);
    /* App should take care of timing requirements */
}

int32_t UNICACHEPreloadAndLock(uint32_t baseAddr,
                               uint32_t startAddress,
                               uint32_t byteCount,
                               uint32_t tWait)
{
    int32_t  retVal     = STW_SOK;
    uint32_t timeToWait = tWait;

    /* Perform cache operation on whole block */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, startAddress);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND,
                (startAddress + (byteCount - 1U)));
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_PRELOADANDLOCK,
                  IPU_UNICACHE_MAINT_PRELOADANDLOCK_ENABLE);

    if (UNICACHE_WAIT_INFINITE != timeToWait)
    {
        /* Wait for operation to finish */
        while ((0U != timeToWait) &&
               (IPU_UNICACHE_MAINT_PRELOADANDLOCK_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_PRELOADANDLOCK)))
        {
            timeToWait--;
        }
        if (0U == timeToWait)
        {
            /* Check if operation has completed in stipulated time */
            if (IPU_UNICACHE_MAINT_PRELOADANDLOCK_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_PRELOADANDLOCK))
            {
                /* Mark result as fail if operation is still not finished */
                retVal = STW_EFAIL;
            }
        }
    }
    else
    {
        while (IPU_UNICACHE_MAINT_PRELOADANDLOCK_DISABLE !=
               HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                             IPU_UNICACHE_MAINT_PRELOADANDLOCK))
        {
            /* Wait Infinitely */
        }
    }

    return retVal;
}

int32_t UNICACHEWriteBackAll(uint32_t baseAddr, uint32_t tWait)
{
    int32_t  retVal     = STW_SOK;
    uint32_t timeToWait = tWait;

    /* Perform cache operation on whole block */
    /* Assign start and end address as whole address range */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, 0x00000000U);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND, 0xFFFFFFFFU);
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_CLEAN,
                  IPU_UNICACHE_MAINT_CLEAN_ENABLE);

    if (UNICACHE_WAIT_INFINITE != timeToWait)
    {
        /* Wait for operation to finish */
        while ((0U != timeToWait) &&
               (IPU_UNICACHE_MAINT_CLEAN_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_CLEAN)))
        {
            timeToWait--;
        }
        if (0U == timeToWait)
        {
            /* Check if operation has completed in stipulated time */
            if (IPU_UNICACHE_MAINT_CLEAN_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_CLEAN))
            {
                /* Mark result as fail if operation is still not finished */
                retVal = STW_EFAIL;
            }
        }
    }
    else
    {
        while (IPU_UNICACHE_MAINT_CLEAN_DISABLE !=
               HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                             IPU_UNICACHE_MAINT_CLEAN))
        {
            /* Wait Infinitely */
        }
    }

    return retVal;
}

int32_t UNICACHEInvalidateAll(uint32_t baseAddr, uint32_t tWait)
{
    int32_t  retVal     = STW_SOK;
    uint32_t timeToWait = tWait;

    /* Perform cache operation on whole block */
    /* Assign start and end address as whole address range */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, 0x00000000U);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND, 0xFFFFFFFFU);
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_INVALIDATE,
                  IPU_UNICACHE_MAINT_INVALIDATE_ENABLE);

    if (UNICACHE_WAIT_INFINITE != timeToWait)
    {
        /* Wait for operation to finish */
        while ((0U != timeToWait) &&
               (IPU_UNICACHE_MAINT_INVALIDATE_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_INVALIDATE)))
        {
            timeToWait--;
        }
        if (0U == timeToWait)
        {
            /* Check if operation has completed in stipulated time */
            if (IPU_UNICACHE_MAINT_INVALIDATE_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_INVALIDATE))
            {
                /* Mark result as fail if operation is still not finished */
                retVal = STW_EFAIL;
            }
        }
    }
    else
    {
        while (IPU_UNICACHE_MAINT_INVALIDATE_DISABLE !=
               HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                             IPU_UNICACHE_MAINT_INVALIDATE))
        {
            /* Wait Infinitely */
        }
    }

    return retVal;
}

int32_t UNICACHEWriteBackAndInvalidateAll(uint32_t baseAddr, uint32_t tWait)
{
    int32_t  retVal     = STW_SOK;
    uint32_t timeToWait = tWait;

    /* Perform cache operation on whole block */
    /* Assign start and end address as whole address range */
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTSTART, 0x00000000U);
    HW_WR_REG32(baseAddr + IPU_UNICACHE_MTEND, 0xFFFFFFFFU);
    HW_WR_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                  IPU_UNICACHE_MAINT_CLEANANDINVALIDATE,
                  IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_ENABLE);

    if (UNICACHE_WAIT_INFINITE != timeToWait)
    {
        /* Wait for operation to finish */
        while ((0U != timeToWait) &&
               (IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_CLEANANDINVALIDATE)))
        {
            timeToWait--;
        }
        if (0U == timeToWait)
        {
            /* Check if operation has completed in stipulated time */
            if (IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_DISABLE !=
                HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                              IPU_UNICACHE_MAINT_CLEANANDINVALIDATE))
            {
                /* Mark result as fail if operation is still not finished */
                retVal = STW_EFAIL;
            }
        }
    }
    else
    {
        while (IPU_UNICACHE_MAINT_CLEANANDINVALIDATE_DISABLE !=
               HW_RD_FIELD32(baseAddr + IPU_UNICACHE_MAINT,
                             IPU_UNICACHE_MAINT_CLEANANDINVALIDATE))
        {
            /* Wait Infinitely */
        }
    }

    return retVal;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
