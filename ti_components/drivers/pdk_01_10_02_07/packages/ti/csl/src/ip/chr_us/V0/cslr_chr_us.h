/********************************************************************
 * Copyright (C) 2013-2015 Texas Instruments Incorporated.
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
#ifndef CSLR_DEI_H_
#define CSLR_DEI_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for mmr_generated_address_block
**************************************************************************/
typedef struct {
    volatile Uint32 PID;
    volatile Uint32 REG0;
    volatile Uint32 REG1;
    volatile Uint32 REG2;
    volatile Uint32 REG3;
    volatile Uint32 REG4;
    volatile Uint32 REG5;
    volatile Uint32 REG6;
    volatile Uint32 REG7;
} CSL_Chr_UsRegs;


/**************************************************************************
* Register Macros
**************************************************************************/
#define CSL_CHR_US_PID                                          (0x0U)
#define CSL_CHR_US_REG0                                         (0x4U)
#define CSL_CHR_US_REG1                                         (0x8U)
#define CSL_CHR_US_REG2                                         (0xCU)
#define CSL_CHR_US_REG3                                         (0x10U)
#define CSL_CHR_US_REG4                                         (0x14U)
#define CSL_CHR_US_REG5                                         (0x18U)
#define CSL_CHR_US_REG6                                         (0x1CU)
#define CSL_CHR_US_REG7                                         (0x20U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* PID */

#define CSL_CHR_US_PID_RESETVAL                                 (0x00000000U)

/* REG0 */

#define CSL_CHR_US_REG0_CFG_MODE_MASK                           (0x00030000U)
#define CSL_CHR_US_REG0_CFG_MODE_SHIFT                          (16U)
#define CSL_CHR_US_REG0_CFG_MODE_RESETVAL                       (0x00000000U)
#define CSL_CHR_US_REG0_CFG_MODE_MAX                            (0x00000003U)

#define CSL_CHR_US_REG0_ANCHOR_FID0_C0_MASK                     (0xFFFC0000U)
#define CSL_CHR_US_REG0_ANCHOR_FID0_C0_SHIFT                    (18U)
#define CSL_CHR_US_REG0_ANCHOR_FID0_C0_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG0_ANCHOR_FID0_C0_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG0_ANCHOR_FID0_C1_MASK                     (0x0000FFFCU)
#define CSL_CHR_US_REG0_ANCHOR_FID0_C1_SHIFT                    (2U)
#define CSL_CHR_US_REG0_ANCHOR_FID0_C1_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG0_ANCHOR_FID0_C1_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG0_RESETVAL                                (0x00000000U)

/* REG1 */

#define CSL_CHR_US_REG1_ANCHOR_FID0_C2_MASK                     (0xFFFC0000U)
#define CSL_CHR_US_REG1_ANCHOR_FID0_C2_SHIFT                    (18U)
#define CSL_CHR_US_REG1_ANCHOR_FID0_C2_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG1_ANCHOR_FID0_C2_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG1_ANCHOR_FID0_C3_MASK                     (0x0000FFFCU)
#define CSL_CHR_US_REG1_ANCHOR_FID0_C3_SHIFT                    (2U)
#define CSL_CHR_US_REG1_ANCHOR_FID0_C3_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG1_ANCHOR_FID0_C3_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG1_RESETVAL                                (0x00000000U)

/* REG2 */

#define CSL_CHR_US_REG2_INTERP_FID0_C0_MASK                     (0xFFFC0000U)
#define CSL_CHR_US_REG2_INTERP_FID0_C0_SHIFT                    (18U)
#define CSL_CHR_US_REG2_INTERP_FID0_C0_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG2_INTERP_FID0_C0_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG2_INTERP_FID0_C1_MASK                     (0x0000FFFCU)
#define CSL_CHR_US_REG2_INTERP_FID0_C1_SHIFT                    (2U)
#define CSL_CHR_US_REG2_INTERP_FID0_C1_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG2_INTERP_FID0_C1_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG2_RESETVAL                                (0x00000000U)

/* REG3 */

#define CSL_CHR_US_REG3_INTERP_FID0_C2_MASK                     (0xFFFC0000U)
#define CSL_CHR_US_REG3_INTERP_FID0_C2_SHIFT                    (18U)
#define CSL_CHR_US_REG3_INTERP_FID0_C2_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG3_INTERP_FID0_C2_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG3_INTERP_FID0_C3_MASK                     (0x0000FFFCU)
#define CSL_CHR_US_REG3_INTERP_FID0_C3_SHIFT                    (2U)
#define CSL_CHR_US_REG3_INTERP_FID0_C3_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG3_INTERP_FID0_C3_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG3_RESETVAL                                (0x00000000U)

/* REG4 */

#define CSL_CHR_US_REG4_ANCHOR_FID1_C0_MASK                     (0xFFFC0000U)
#define CSL_CHR_US_REG4_ANCHOR_FID1_C0_SHIFT                    (18U)
#define CSL_CHR_US_REG4_ANCHOR_FID1_C0_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG4_ANCHOR_FID1_C0_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG4_ANCHOR_FID1_C1_MASK                     (0x0000FFFCU)
#define CSL_CHR_US_REG4_ANCHOR_FID1_C1_SHIFT                    (2U)
#define CSL_CHR_US_REG4_ANCHOR_FID1_C1_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG4_ANCHOR_FID1_C1_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG4_RESETVAL                                (0x00000000U)

/* REG5 */

#define CSL_CHR_US_REG5_ANCHOR_FID1_C2_MASK                     (0xFFFC0000U)
#define CSL_CHR_US_REG5_ANCHOR_FID1_C2_SHIFT                    (18U)
#define CSL_CHR_US_REG5_ANCHOR_FID1_C2_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG5_ANCHOR_FID1_C2_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG5_ANCHOR_FID1_C3_MASK                     (0x0000FFFCU)
#define CSL_CHR_US_REG5_ANCHOR_FID1_C3_SHIFT                    (2U)
#define CSL_CHR_US_REG5_ANCHOR_FID1_C3_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG5_ANCHOR_FID1_C3_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG5_RESETVAL                                (0x00000000U)

/* REG6 */

#define CSL_CHR_US_REG6_INTERP_FID1_C0_MASK                     (0xFFFC0000U)
#define CSL_CHR_US_REG6_INTERP_FID1_C0_SHIFT                    (18U)
#define CSL_CHR_US_REG6_INTERP_FID1_C0_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG6_INTERP_FID1_C0_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG6_INTERP_FID1_C1_MASK                     (0x0000FFFCU)
#define CSL_CHR_US_REG6_INTERP_FID1_C1_SHIFT                    (2U)
#define CSL_CHR_US_REG6_INTERP_FID1_C1_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG6_INTERP_FID1_C1_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG6_RESETVAL                                (0x00000000U)

/* REG7 */

#define CSL_CHR_US_REG7_INTERP_FID1_C2_MASK                     (0xFFFC0000U)
#define CSL_CHR_US_REG7_INTERP_FID1_C2_SHIFT                    (18U)
#define CSL_CHR_US_REG7_INTERP_FID1_C2_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG7_INTERP_FID1_C2_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG7_INTERP_FID1_C3_MASK                     (0x0000FFFCU)
#define CSL_CHR_US_REG7_INTERP_FID1_C3_SHIFT                    (2U)
#define CSL_CHR_US_REG7_INTERP_FID1_C3_RESETVAL                 (0x00000000U)
#define CSL_CHR_US_REG7_INTERP_FID1_C3_MAX                      (0x00003fffU)

#define CSL_CHR_US_REG7_RESETVAL                                (0x00000000U)

#ifdef __cplusplus
}
#endif

#endif
