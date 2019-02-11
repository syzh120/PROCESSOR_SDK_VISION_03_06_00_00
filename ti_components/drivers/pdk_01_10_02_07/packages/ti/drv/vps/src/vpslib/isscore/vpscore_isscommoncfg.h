/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2013-2015
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
 *  \file vpscore_isscommoncfg.h
 *
 *  \brief  Provides interfaces/defines for the common configuration.
 *
 */

#ifndef VPSCORE_ISS_COMMON_CFG_H_
#define VPSCORE_ISS_COMMON_CFG_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

/**
 *  \brief Resizer high threshold should be set to slightly less
 *         than the output frame width. This define is used to set
 *         width offset. This number is subtracted from the width
 *         and used to configure the resizer hight threshold.
 */
#define VCORE_ISS_RSZ_HIGH_THRESHOLD_OFFSET         (30U)

/**
 *  \brief Read address used for GLBCE startup sequence. This should be some
 *         valid address. If this is invalid adress, RD DMA could
 *         cause a exception
 */
#define VCORE_ISS_READ_ADDR_GBLCE_STARTUP_SEQ       (0x80000000U)

/**
 *  \brief When WDR mode is enabled in the IPIPEIF, ipipeif read input
 *         requires to be delayed by 2 lines to match it with the
 *         incoming vport input. This macro is used for defining these
 *         2 lines delay.
 */
#define VCORE_ISS_IPIPEIF_WDR_DELAY_LINES           (0x2)

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

#endif  /* #ifndef VPSCORE_ISS_COMMON_CFG_H_ */
