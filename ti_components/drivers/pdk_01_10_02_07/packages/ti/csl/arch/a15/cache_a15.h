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
 *  \ingroup CSL_ARCH_A15
 *  \defgroup CSL_ARCH_A15_CACHE Cache
 *
 *  @{
 */
/**
 *  \file     cache_a15.h
 *
 *  \brief    This file contains the interfaces present in the A15 Cache HAL.
 *            This also contains some related macros, structures and enums.
 */

#ifndef CACHE_A15_H_
#define CACHE_A15_H_

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

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/*
 * Macro to select the A15's cache type.
 *
 * \note   There is only one bit that will enable/disable L1D and L2 Cache
 *         (Unified in current implementation). Bit for enabling L1I Cache is
 *         different. L1D/L2: Bit[2], C Bit and L1P: Bit[12], I Bit are present
 *         in Control or SCTLR Register.
 */
/** \brief Cache Type is L1I (or L1P) */
#define CACHE_A15_TYPE_L1I          (0x1U)
/** \brief Cache Type is L1D */
#define CACHE_A15_TYPE_L1D          (0x2U)
/** \brief Cache Type is L1 */
#define CACHE_A15_TYPE_L1           (CACHE_A15_TYPE_L1I | CACHE_A15_TYPE_L1D)
/** \brief Cache Type is L2I (or L2P) */
#define CACHE_A15_TYPE_L2I          (0x4U)
/** \brief Cache Type is L2D */
#define CACHE_A15_TYPE_L2D          (0x8U)
/** \brief Cache Type is L2 */
#define CACHE_A15_TYPE_L2           (CACHE_A15_TYPE_L2I | CACHE_A15_TYPE_L2D)
/** \brief Cache Type is ALLI (or ALLP) */
#define CACHE_A15_TYPE_ALLI         (CACHE_A15_TYPE_L1I | CACHE_A15_TYPE_L2I)
/** \brief Cache Type is ALLD */
#define CACHE_A15_TYPE_ALLD         (CACHE_A15_TYPE_L1D | CACHE_A15_TYPE_L2D)
/** \brief Cache Type is ALL */
#define CACHE_A15_TYPE_ALL          (0x7FFFU)

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
 * \brief   This function gets the mask corresponding to enabled A15 cache.
 *
 * \return  enabledCache     Mask corresponding to enabled cache.
 */
uint32_t CACHEA15GetEnabled(void);

/**
 * \brief   This function first checks if cache is enabled and enables it if
 *          it is not enabled.
 *
 * \param   cacheType   A15's cache type.
 *
 * \return  None.
 */
void CACHEA15Enable(uint32_t cacheType);

/**
 * \brief   This function disables the A15 cache.
 *
 * \param   cacheType   A15's cache type.
 *
 * \return  None.
 */
void CACHEA15Disable(uint32_t cacheType);

/**
 * \brief   This function invalidates the cache lines in the region defined by
 *          maintenance start/end address.
 *
 * \param   cacheType     A15's cache type.
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 *
 * \return  None.
 */
void CACHEA15Invalidate(uint32_t cacheType,
                        uint32_t startAddress,
                        uint32_t byteCount);

/**
 * \brief   This function evicts the dirty cache lines in the region defined by
 *          maintenance start/end address.
 *
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 *
 * \return  None.
 */
void CACHEA15WriteBack(uint32_t startAddress, uint32_t byteCount);

/**
 * \brief   This function pre-loads the region defined by maintenance start/end
 *          address.
 *
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 *
 * \return  None.
 */
void CACHEA15Preload(uint32_t startAddress, uint32_t byteCount);

/**
 * \brief   This function invalidates and evicts the cache lines in the region
 *          defined by maintenance start/end address.
 *
 * \param   startAddress  Maintenance region start address.
 * \param   byteCount     Length of the maintenance region.
 *
 * \return  None.
 */
void CACHEA15WriteBackAndInvalidate(uint32_t startAddress, uint32_t byteCount);

/**
 * \brief   This function invalidates the whole A15 L1I Cache.
 *
 * \return  None.
 */
void CACHEA15InvalidateL1IAll(void);

/**
 * \brief   This function invalidates the whole A15 L1D Cache.
 *
 * \return  None.
 */
void CACHEA15InvalidateL1DAll(void);

/**
 * \brief   This function evicts the whole A15 Cache.
 *
 * \return  None.
 */
void CACHEA15WriteBackAll(void);

/**
 * \brief   This function evicts and invalidates the whole A15 Cache.
 *
 * \return  None.
 */
void CACHEA15WriteBackAndInvalidateAll(void);

/**
 * \brief   This function waits for A15 drain write buffer to complete.
 *
 * \return  None.
 */
void CACHEA15Wait(void);

/**
 * \brief   This function enables the branch prediction.
 *
 * \return  None.
 */
void CACHEA15EnableBP(void);

/**
 * \brief   This function disables the branch prediction.
 *
 * \return  None.
 */
void CACHEA15DisableBP(void);

/**
 * \brief   This function disables streaming cache line and configures all write
 *          allocate lines allocate in L1 or L2 Cache
 *
 * \return  None.
 */
void CACHEA15DisableStreamCacheLine(void);

#ifdef __cplusplus
}

#endif

#endif
 /** @} */
