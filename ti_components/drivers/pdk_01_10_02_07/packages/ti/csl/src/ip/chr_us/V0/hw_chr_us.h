/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2008-2015
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
 *  \file       hw_chr_us.h
 *
 *  \brief      register-level header file for CHR_US
 *
**/

#ifndef HW_CHR_US_H_
#define HW_CHR_US_H_

#ifdef __cplusplus
extern "C"
{
#endif

#define CHR_US_PID                                                                                          (0x0U)
#define CHR_US_REG0                                                                                         (0x4U)
#define CHR_US_REG1                                                                                         (0x8U)
#define CHR_US_REG2                                                                                         (0xcU)
#define CHR_US_REG3                                                                                         (0x10U)
#define CHR_US_REG4                                                                                         (0x14U)
#define CHR_US_REG5                                                                                         (0x18U)
#define CHR_US_REG6                                                                                         (0x1cU)
#define CHR_US_REG7                                                                                         (0x20U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CHR_US_REG0_CFG_MODE_SHIFT                                                                          (16U)
#define CHR_US_REG0_CFG_MODE_MASK                                                                           (0x00030000U)

#define CHR_US_REG0_ANCHOR_FID0_C0_SHIFT                                                                    (18U)
#define CHR_US_REG0_ANCHOR_FID0_C0_MASK                                                                     (0xfffc0000U)

#define CHR_US_REG0_ANCHOR_FID0_C1_SHIFT                                                                    (2U)
#define CHR_US_REG0_ANCHOR_FID0_C1_MASK                                                                     (0x0000fffcU)

#define CHR_US_REG1_ANCHOR_FID0_C2_SHIFT                                                                    (18U)
#define CHR_US_REG1_ANCHOR_FID0_C2_MASK                                                                     (0xfffc0000U)

#define CHR_US_REG1_ANCHOR_FID0_C3_SHIFT                                                                    (2U)
#define CHR_US_REG1_ANCHOR_FID0_C3_MASK                                                                     (0x0000fffcU)

#define CHR_US_REG2_INTERP_FID0_C0_SHIFT                                                                    (18U)
#define CHR_US_REG2_INTERP_FID0_C0_MASK                                                                     (0xfffc0000U)

#define CHR_US_REG2_INTERP_FID0_C1_SHIFT                                                                    (2U)
#define CHR_US_REG2_INTERP_FID0_C1_MASK                                                                     (0x0000fffcU)

#define CHR_US_REG3_INTERP_FID0_C2_SHIFT                                                                    (18U)
#define CHR_US_REG3_INTERP_FID0_C2_MASK                                                                     (0xfffc0000U)

#define CHR_US_REG3_INTERP_FID0_C3_SHIFT                                                                    (2U)
#define CHR_US_REG3_INTERP_FID0_C3_MASK                                                                     (0x0000fffcU)

#define CHR_US_REG4_ANCHOR_FID1_C0_SHIFT                                                                    (18U)
#define CHR_US_REG4_ANCHOR_FID1_C0_MASK                                                                     (0xfffc0000U)

#define CHR_US_REG4_ANCHOR_FID1_C1_SHIFT                                                                    (2U)
#define CHR_US_REG4_ANCHOR_FID1_C1_MASK                                                                     (0x0000fffcU)

#define CHR_US_REG5_ANCHOR_FID1_C2_SHIFT                                                                    (18U)
#define CHR_US_REG5_ANCHOR_FID1_C2_MASK                                                                     (0xfffc0000U)

#define CHR_US_REG5_ANCHOR_FID1_C3_SHIFT                                                                    (2U)
#define CHR_US_REG5_ANCHOR_FID1_C3_MASK                                                                     (0x0000fffcU)

#define CHR_US_REG6_INTERP_FID1_C0_SHIFT                                                                    (18U)
#define CHR_US_REG6_INTERP_FID1_C0_MASK                                                                     (0xfffc0000U)

#define CHR_US_REG6_INTERP_FID1_C1_SHIFT                                                                    (2U)
#define CHR_US_REG6_INTERP_FID1_C1_MASK                                                                     (0x0000fffcU)

#define CHR_US_REG7_INTERP_FID1_C2_SHIFT                                                                    (18U)
#define CHR_US_REG7_INTERP_FID1_C2_MASK                                                                     (0xfffc0000U)

#define CHR_US_REG7_INTERP_FID1_C3_SHIFT                                                                    (2U)
#define CHR_US_REG7_INTERP_FID1_C3_MASK                                                                     (0x0000fffcU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CHR_US_H_ */

