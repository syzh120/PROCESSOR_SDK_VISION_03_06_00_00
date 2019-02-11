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
 *  \file       hw_csc.h
 *
 *  \brief      register-level header file for CSC
 *
**/

#ifndef HW_CSC_H_
#define HW_CSC_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define CSC_00                                                                                              (0x0U)
#define CSC_01                                                                                              (0x4U)
#define CSC_02                                                                                              (0x8U)
#define CSC_03                                                                                              (0xcU)
#define CSC_04                                                                                              (0x10U)
#define CSC_05                                                                                              (0x14U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CSC_00_A0_SHIFT                                                                                     (0U)
#define CSC_00_A0_MASK                                                                                      (0x00001fffU)

#define CSC_00_B0_SHIFT                                                                                     (16U)
#define CSC_00_B0_MASK                                                                                      (0x1fff0000U)

#define CSC_01_C0_SHIFT                                                                                     (0U)
#define CSC_01_C0_MASK                                                                                      (0x00001fffU)

#define CSC_01_A1_SHIFT                                                                                     (16U)
#define CSC_01_A1_MASK                                                                                      (0x1fff0000U)

#define CSC_02_B1_SHIFT                                                                                     (0U)
#define CSC_02_B1_MASK                                                                                      (0x00001fffU)

#define CSC_02_C1_SHIFT                                                                                     (16U)
#define CSC_02_C1_MASK                                                                                      (0x1fff0000U)

#define CSC_03_A2_SHIFT                                                                                     (0U)
#define CSC_03_A2_MASK                                                                                      (0x00001fffU)

#define CSC_03_B2_SHIFT                                                                                     (16U)
#define CSC_03_B2_MASK                                                                                      (0x1fff0000U)

#define CSC_04_C2_SHIFT                                                                                     (0U)
#define CSC_04_C2_MASK                                                                                      (0x00001fffU)

#define CSC_04_D0_SHIFT                                                                                     (16U)
#define CSC_04_D0_MASK                                                                                      (0x0fff0000U)

#define CSC_05_D1_SHIFT                                                                                     (0U)
#define CSC_05_D1_MASK                                                                                      (0x00000fffU)

#define CSC_05_D2_SHIFT                                                                                     (16U)
#define CSC_05_D2_MASK                                                                                      (0x0fff0000U)

#define CSC_05_BYPASS_SHIFT                                                                                 (28U)
#define CSC_05_BYPASS_MASK                                                                                  (0x10000000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CSC_H_ */
