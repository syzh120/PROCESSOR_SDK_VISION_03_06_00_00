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
#ifndef CSLR_CSC_H_
#define CSLR_CSC_H_

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
    volatile Uint32 CSC_00;
    volatile Uint32 CSC_01;
    volatile Uint32 CSC_02;
    volatile Uint32 CSC_03;
    volatile Uint32 CSC_04;
    volatile Uint32 CSC_05;
} CSL_CscRegs;


/**************************************************************************
* Register Macros
**************************************************************************/
#define CSL_CSC_CSC_00                                          (0x0U)
#define CSL_CSC_CSC_01                                          (0x4U)
#define CSL_CSC_CSC_02                                          (0x8U)
#define CSL_CSC_CSC_03                                          (0xCU)
#define CSL_CSC_CSC_04                                          (0x10U)
#define CSL_CSC_CSC_05                                          (0x14U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* CSC_00 */

#define CSL_CSC_CSC_00_A0_MASK                                  (0x00001FFFU)
#define CSL_CSC_CSC_00_A0_SHIFT                                 (0U)
#define CSL_CSC_CSC_00_A0_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_00_A0_MAX                                   (0x00001fffU)

#define CSL_CSC_CSC_00_B0_MASK                                  (0x1FFF0000U)
#define CSL_CSC_CSC_00_B0_SHIFT                                 (16U)
#define CSL_CSC_CSC_00_B0_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_00_B0_MAX                                   (0x00001fffU)

#define CSL_CSC_CSC_00_RESETVAL                                 (0x00000000U)

/* CSC_01 */

#define CSL_CSC_CSC_01_C0_MASK                                  (0x00001FFFU)
#define CSL_CSC_CSC_01_C0_SHIFT                                 (0U)
#define CSL_CSC_CSC_01_C0_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_01_C0_MAX                                   (0x00001fffU)

#define CSL_CSC_CSC_01_A1_MASK                                  (0x1FFF0000U)
#define CSL_CSC_CSC_01_A1_SHIFT                                 (16U)
#define CSL_CSC_CSC_01_A1_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_01_A1_MAX                                   (0x00001fffU)

#define CSL_CSC_CSC_01_RESETVAL                                 (0x00000000U)

/* CSC_02 */

#define CSL_CSC_CSC_02_B1_MASK                                  (0x00001FFFU)
#define CSL_CSC_CSC_02_B1_SHIFT                                 (0U)
#define CSL_CSC_CSC_02_B1_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_02_B1_MAX                                   (0x00001fffU)

#define CSL_CSC_CSC_02_C1_MASK                                  (0x1FFF0000U)
#define CSL_CSC_CSC_02_C1_SHIFT                                 (16U)
#define CSL_CSC_CSC_02_C1_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_02_C1_MAX                                   (0x00001fffU)

#define CSL_CSC_CSC_02_RESETVAL                                 (0x00000000U)

/* CSC_03 */

#define CSL_CSC_CSC_03_A2_MASK                                  (0x00001FFFU)
#define CSL_CSC_CSC_03_A2_SHIFT                                 (0U)
#define CSL_CSC_CSC_03_A2_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_03_A2_MAX                                   (0x00001fffU)

#define CSL_CSC_CSC_03_B2_MASK                                  (0x1FFF0000U)
#define CSL_CSC_CSC_03_B2_SHIFT                                 (16U)
#define CSL_CSC_CSC_03_B2_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_03_B2_MAX                                   (0x00001fffU)

#define CSL_CSC_CSC_03_RESETVAL                                 (0x00000000U)

/* CSC_04 */

#define CSL_CSC_CSC_04_C2_MASK                                  (0x00001FFFU)
#define CSL_CSC_CSC_04_C2_SHIFT                                 (0U)
#define CSL_CSC_CSC_04_C2_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_04_C2_MAX                                   (0x00001fffU)

#define CSL_CSC_CSC_04_D0_MASK                                  (0x0FFF0000U)
#define CSL_CSC_CSC_04_D0_SHIFT                                 (16U)
#define CSL_CSC_CSC_04_D0_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_04_D0_MAX                                   (0x00000fffU)

#define CSL_CSC_CSC_04_RESETVAL                                 (0x00000000U)

/* CSC_05 */

#define CSL_CSC_CSC_05_D1_MASK                                  (0x00000FFFU)
#define CSL_CSC_CSC_05_D1_SHIFT                                 (0U)
#define CSL_CSC_CSC_05_D1_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_05_D1_MAX                                   (0x00000fffU)

#define CSL_CSC_CSC_05_D2_MASK                                  (0x0FFF0000U)
#define CSL_CSC_CSC_05_D2_SHIFT                                 (16U)
#define CSL_CSC_CSC_05_D2_RESETVAL                              (0x00000000U)
#define CSL_CSC_CSC_05_D2_MAX                                   (0x00000fffU)

#define CSL_CSC_CSC_05_BYPASS_MASK                              (0x10000000U)
#define CSL_CSC_CSC_05_BYPASS_SHIFT                             (28U)
#define CSL_CSC_CSC_05_BYPASS_RESETVAL                          (0x00000000U)
#define CSL_CSC_CSC_05_BYPASS_MAX                               (0x00000001U)

#define CSL_CSC_CSC_05_RESETVAL                                 (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
