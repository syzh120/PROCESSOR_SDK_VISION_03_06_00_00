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
 * \file vpshalChrusDefaults.h
 *
 * \brief VPS CHR_US HAL default configuration file
 * This file contains default configuration i.e. expert values for
 * Chroma UpSampler.
 *
 */

#ifndef VPSHAL_CHRUS_DEFAULTS_H_
#define VPSHAL_CHRUS_DEFAULTS_H_

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
 *  \brief Expert value for the anchor and interpolated pixel
 */
#define VPSHAL_CHRUS_DEFAULT_EXPERT_VAL                                  \
    {                                                                    \
        /* Coefficients for progressive input */                         \
        {{{0x0C8, 0x348, 0x18, 0x3FD8}, {0x3FB8, 0x378, 0xE8, 0x3FE8},   \
          {0x0C8, 0x348, 0x18, 0x3FD8}, {0x3FB8, 0x378, 0xE8, 0x3FE8}}}, \
        /* Coefficients for Top Field Interlaced input */                \
        {{{0x51, 0x3D5, 0x3FE3, 0x3FF7}, {0x3FB5, 0x2E9, 0x18F, 0x3FD3}, \
          /* Coefficients for Bottom Field Interlaced input */           \
          {0x16B, 0x247, 0xB1, 0x3F9D}, {0x3FCF, 0x3DB, 0x5D, 0x3FF9}}}  \
    }

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None*/

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

/* None */

#ifdef __cplusplus
}
#endif

#endif /* #ifndef VPSHAL_CHRUS_DEFAULTS_H_ */
