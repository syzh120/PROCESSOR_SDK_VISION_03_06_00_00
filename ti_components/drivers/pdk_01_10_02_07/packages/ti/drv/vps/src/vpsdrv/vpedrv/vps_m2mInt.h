/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2012-2015
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
 *  \file vps_m2mInt.h
 *
 *  \brief VPS Mem-Mem driver common header file.
 *
 */

#ifndef VPS_M2MINT_H_
#define VPS_M2MINT_H_

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
 *  struct VpsMdrv_SyncMode
 *  \brief Enum to indicate whether Sync on Channel (SOCH) or
 *  Sync on Client (SOC) to be used between each channel descriptors while
 *  chaining.
 */
typedef enum
{
    VPSMDRV_SYNC_MODE_SOCH,
    /**< Use Sync on Channel. */
    VPSMDRV_SYNC_MODE_SOC,
    /**< Use Sync on Client. */
    VPSMDRV_SYNC_MODE_MAX
    /**< Should be the last value of this enumeration.
     *   Will be used by driver for validating the input parameters. */
} VpsMdrv_SyncMode;

/**
 *  struct VpsMdrv_QueObjType
 *  \brief To know whether the queue objects contain the frames or
 *  coefficient descriptors. So that it can be returned to appropriate
 *  queue after callback.
 */
typedef enum
{
    VPSMDRV_QOBJ_TYPE_FRAMES,
    /**< Container contains process list to be processed. */
    VPSMDRV_QOBJ_TYPE_COEFF,
    /**< Container contains the coefficients. */
    VPSMDRV_QOBJ_TYPE_MAX
    /**< Should be the last value of this enumeration. */
} VpsMdrv_QueObjType;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* VPS_M2MINT_H_ */
