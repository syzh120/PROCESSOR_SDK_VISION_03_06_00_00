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
 *  \file vpshal_cscDefaults.h
 *
 *  \brief VPS CSC HAL default configuration file
 *  This file contains default configuration i.e. expert values for
 *  Color Space Convertor.
 *
 */

#ifndef VPSHAL_CSCDEFAULTS_H_
#define VPSHAL_CSCDEFAULTS_H_

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
#define VPSHAL_CSC_DEFAULT_EXPERT_VAL                           \
    {                                                           \
        /* VPS_CSC_MODE_SDTV_LIMITED_RANGE_R2Y */               \
        {{{0x0132, 0x0259, 0x0075}, {0x1F50, 0x1EA5, 0x020B},   \
          {0x020B, 0x1EA4, 0x1FAB}}, {0x0000, 0x0200, 0x0200}}, \
                                                                \
        /* VPS_CSC_MODE_SDTV_LIMITED_RANGE_Y2R */               \
        {{{0x0400, 0x0000, 0x057D}, {0x0400, 0x1EA7, 0x1D35},   \
          {0x0400, 0x06EF, 0x1FFE}}, {0x0D40, 0x0210, 0x0C88}}, \
                                                                \
        /* VPS_CSC_MODE_SDTV_FULL_RANGE_R2Y */                  \
        {{{0x0107, 0x0204, 0x0064}, {0x1F68, 0x1ED6, 0x01C2},   \
          {0x01C2, 0x1E87, 0x1FB7}}, {0x0040, 0x0200, 0x0200}}, \
                                                                \
        /* VPS_CSC_MODE_SDTV_FULL_RANGE_Y2R */                  \
        {{{0x04A8, 0x1FFE, 0x0662}, {0x04A8, 0x1E6F, 0x1CBF},   \
          {0x04A8, 0x0812, 0x1FFF}}, {0x0C84, 0x0220, 0x0BAC}}, \
                                                                \
        /* VPS_CSC_MODE_HDTV_LIMITED_RANGE_R2Y */               \
        {{{0x00DA, 0x02DC, 0x004A}, {0x1F88, 0x1E6C, 0x020C},   \
          {0x020C, 0x1E24, 0x1FD0}}, {0x0000, 0x0200, 0x0200}}, \
                                                                \
        /* VPS_CSC_MODE_HDTV_LIMITED_RANGE_Y2R */               \
        {{{0x0400, 0x0000, 0x0629}, {0x0400, 0x1F45, 0x1E2B},   \
          {0x0400, 0x0742, 0x0000}}, {0x0CEC, 0x0148, 0x0C60}}, \
                                                                \
        /* VPS_CSC_MODE_HDTV_FULL_RANGE_R2Y */                  \
        {{{0x00BB, 0x0275, 0x003F}, {0x1F99, 0x1EA5, 0x01C2},   \
          {0x01C2, 0x1E67, 0x1FD7}}, {0x0040, 0x0200, 0x0200}}, \
                                                                \
        /* VPS_CSC_MODE_HDTV_FULL_RANGE_Y2R   */                \
        {{{0x04A8, 0x0000, 0x072C}, {0x04A8, 0x1F26, 0x1DDE},   \
          {0x04A8, 0x0873, 0x0000}}, {0x0C20, 0x0134, 0x0B7C}}  \
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

#endif  /* #ifndef VPSHAL_CSCDEFAULTS_H_ */
