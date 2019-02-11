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
#ifndef CSLR_SC_H_
#define CSLR_SC_H_

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
    volatile Uint32 SC_CFG_0;
    volatile Uint32 SC_CFG_1;
    volatile Uint32 SC_CFG_2;
    volatile Uint32 SC_CFG_3;
    volatile Uint32 SC_CFG_4;
    volatile Uint32 SC_CFG_5;
    volatile Uint32 SC_CFG_6;
    volatile Uint32 SC_CFG_7;
    volatile Uint32 SC_CFG_8;
    volatile Uint32 SC_CFG_9;
    volatile Uint32 SC_CFG_10;
    volatile Uint32 SC_CFG_11;
    volatile Uint32 SC_CFG_12;
    volatile Uint32 SC_CFG_13;
    volatile Uint32 SC_CFG_14;
    volatile Uint32 SC_CFG_15;
    volatile Uint32 SC_CFG_16;
    volatile Uint8  RSVD0[4];
    volatile Uint32 SC_CFG_18;
    volatile Uint32 SC_CFG_19;
    volatile Uint32 SC_CFG_20;
    volatile Uint32 SC_CFG_21;
    volatile Uint32 SC_CFG_22;
    volatile Uint8  RSVD1[4];
    volatile Uint32 SC_CFG_24;
    volatile Uint32 SC_CFG_25;
    volatile Uint32 SC_CFG_26;
    volatile Uint32 SC_CFG_27;
    volatile Uint32 SC_CFG_28;
    volatile Uint32 SC_CFG_29;
    volatile Uint32 SC_CFG_30;
    volatile Uint32 SC_CFG_31;
} CSL_ScRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* SC_CFG_0 */
#define CSL_SC_SC_CFG_0                                         (0x0U)

/* SC_CFG_1 */
#define CSL_SC_SC_CFG_1                                         (0x4U)

/* SC_CFG_2 */
#define CSL_SC_SC_CFG_2                                         (0x8U)

/* SC_CFG_3 */
#define CSL_SC_SC_CFG_3                                         (0xCU)

/* SC_CFG_4 */
#define CSL_SC_SC_CFG_4                                         (0x10U)

/* SC_CFG_5 */
#define CSL_SC_SC_CFG_5                                         (0x14U)

/* SC_CFG_6 */
#define CSL_SC_SC_CFG_6                                         (0x18U)

/* SC_CFG_7 */
#define CSL_SC_SC_CFG_7                                         (0x1CU)

/* SC_CFG_8 */
#define CSL_SC_SC_CFG_8                                         (0x20U)

/* SC_CFG_9 */
#define CSL_SC_SC_CFG_9                                         (0x24U)

/* SC_CFG_10 */
#define CSL_SC_SC_CFG_10                                        (0x28U)

/* SC_CFG_11 */
#define CSL_SC_SC_CFG_11                                        (0x2CU)

/* SC_CFG_12 */
#define CSL_SC_SC_CFG_12                                        (0x30U)

/* SC_CFG_13 */
#define CSL_SC_SC_CFG_13                                        (0x34U)

/* SC_CFG_14 */
#define CSL_SC_SC_CFG_14                                        (0x38U)

/* SC_CFG_15 */
#define CSL_SC_SC_CFG_15                                        (0x3CU)

/* SC_CFG_16 */
#define CSL_SC_SC_CFG_16                                        (0x40U)

/* SC_CFG_18 */
#define CSL_SC_SC_CFG_18                                        (0x48U)

/* SC_CFG_19 */
#define CSL_SC_SC_CFG_19                                        (0x4CU)

/* SC_CFG_20 */
#define CSL_SC_SC_CFG_20                                        (0x50U)

/* SC_CFG_21 */
#define CSL_SC_SC_CFG_21                                        (0x54U)

/* SC_CFG_22 */
#define CSL_SC_SC_CFG_22                                        (0x58U)

/* SC_CFG_24 */
#define CSL_SC_SC_CFG_24                                        (0x60U)

/* SC_CFG_25 */
#define CSL_SC_SC_CFG_25                                        (0x64U)

/* SC_CFG_26 */
#define CSL_SC_SC_CFG_26                                        (0x68U)

/* SC_CFG_27 */
#define CSL_SC_SC_CFG_27                                        (0x6CU)

/* SC_CFG_28 */
#define CSL_SC_SC_CFG_28                                        (0x70U)

/* SC_CFG_29 */
#define CSL_SC_SC_CFG_29                                        (0x74U)

/* SC_CFG_30 */
#define CSL_SC_SC_CFG_30                                        (0x78U)

/* SC_CFG_31 */
#define CSL_SC_SC_CFG_31                                        (0x7CU)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* SC_CFG_0 */

#define CSL_SC_SC_CFG_0_INTERLACE_O_MASK                        (0x00000001U)
#define CSL_SC_SC_CFG_0_INTERLACE_O_SHIFT                       (0U)
#define CSL_SC_SC_CFG_0_INTERLACE_O_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_0_INTERLACE_O_MAX                         (0x00000001U)

#define CSL_SC_SC_CFG_0_LINEAR_MASK                             (0x00000002U)
#define CSL_SC_SC_CFG_0_LINEAR_SHIFT                            (1U)
#define CSL_SC_SC_CFG_0_LINEAR_RESETVAL                         (0x00000000U)
#define CSL_SC_SC_CFG_0_LINEAR_MAX                              (0x00000001U)

#define CSL_SC_SC_CFG_0_SC_BYPASS_MASK                          (0x00000004U)
#define CSL_SC_SC_CFG_0_SC_BYPASS_SHIFT                         (2U)
#define CSL_SC_SC_CFG_0_SC_BYPASS_RESETVAL                      (0x00000000U)
#define CSL_SC_SC_CFG_0_SC_BYPASS_MAX                           (0x00000001U)

#define CSL_SC_SC_CFG_0_INVT_FID_MASK                           (0x00000008U)
#define CSL_SC_SC_CFG_0_INVT_FID_SHIFT                          (3U)
#define CSL_SC_SC_CFG_0_INVT_FID_RESETVAL                       (0x00000000U)
#define CSL_SC_SC_CFG_0_INVT_FID_MAX                            (0x00000001U)

#define CSL_SC_SC_CFG_0_USE_RAV_MASK                            (0x00000010U)
#define CSL_SC_SC_CFG_0_USE_RAV_SHIFT                           (4U)
#define CSL_SC_SC_CFG_0_USE_RAV_RESETVAL                        (0x00000000U)
#define CSL_SC_SC_CFG_0_USE_RAV_MAX                             (0x00000001U)

#define CSL_SC_SC_CFG_0_ENABLE_EV_MASK                          (0x00000020U)
#define CSL_SC_SC_CFG_0_ENABLE_EV_SHIFT                         (5U)
#define CSL_SC_SC_CFG_0_ENABLE_EV_RESETVAL                      (0x00000000U)
#define CSL_SC_SC_CFG_0_ENABLE_EV_MAX                           (0x00000001U)

#define CSL_SC_SC_CFG_0_AUTO_HS_MASK                            (0x00000040U)
#define CSL_SC_SC_CFG_0_AUTO_HS_SHIFT                           (6U)
#define CSL_SC_SC_CFG_0_AUTO_HS_RESETVAL                        (0x00000000U)
#define CSL_SC_SC_CFG_0_AUTO_HS_MAX                             (0x00000001U)

#define CSL_SC_SC_CFG_0_DCM_2X_MASK                             (0x00000080U)
#define CSL_SC_SC_CFG_0_DCM_2X_SHIFT                            (7U)
#define CSL_SC_SC_CFG_0_DCM_2X_RESETVAL                         (0x00000000U)
#define CSL_SC_SC_CFG_0_DCM_2X_MAX                              (0x00000001U)

#define CSL_SC_SC_CFG_0_DCM_4X_MASK                             (0x00000100U)
#define CSL_SC_SC_CFG_0_DCM_4X_SHIFT                            (8U)
#define CSL_SC_SC_CFG_0_DCM_4X_RESETVAL                         (0x00000000U)
#define CSL_SC_SC_CFG_0_DCM_4X_MAX                              (0x00000001U)

#define CSL_SC_SC_CFG_0_HP_BYPASS_MASK                          (0x00000200U)
#define CSL_SC_SC_CFG_0_HP_BYPASS_SHIFT                         (9U)
#define CSL_SC_SC_CFG_0_HP_BYPASS_RESETVAL                      (0x00000000U)
#define CSL_SC_SC_CFG_0_HP_BYPASS_MAX                           (0x00000001U)

#define CSL_SC_SC_CFG_0_INTERLACE_I_MASK                        (0x00000400U)
#define CSL_SC_SC_CFG_0_INTERLACE_I_SHIFT                       (10U)
#define CSL_SC_SC_CFG_0_INTERLACE_I_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_0_INTERLACE_I_MAX                         (0x00000001U)

#define CSL_SC_SC_CFG_0_ENABLE_Y_PK_MASK                        (0x00004000U)
#define CSL_SC_SC_CFG_0_ENABLE_Y_PK_SHIFT                       (14U)
#define CSL_SC_SC_CFG_0_ENABLE_Y_PK_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_0_ENABLE_Y_PK_MAX                         (0x00000001U)

#define CSL_SC_SC_CFG_0_ENABLE_TRIM_MASK                        (0x00008000U)
#define CSL_SC_SC_CFG_0_ENABLE_TRIM_SHIFT                       (15U)
#define CSL_SC_SC_CFG_0_ENABLE_TRIM_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_0_ENABLE_TRIM_MAX                         (0x00000001U)

#define CSL_SC_SC_CFG_0_ENABLE_FID_SELFGEN_MASK                 (0x00010000U)
#define CSL_SC_SC_CFG_0_ENABLE_FID_SELFGEN_SHIFT                (16U)
#define CSL_SC_SC_CFG_0_ENABLE_FID_SELFGEN_RESETVAL             (0x00000000U)
#define CSL_SC_SC_CFG_0_ENABLE_FID_SELFGEN_MAX                  (0x00000001U)

#define CSL_SC_SC_CFG_0_RESETVAL                                (0x00000000U)

/* SC_CFG_1 */

#define CSL_SC_SC_CFG_1_ROW_ACC_INC_MASK                        (0x07FFFFFFU)
#define CSL_SC_SC_CFG_1_ROW_ACC_INC_SHIFT                       (0U)
#define CSL_SC_SC_CFG_1_ROW_ACC_INC_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_1_ROW_ACC_INC_MAX                         (0x07ffffffU)

#define CSL_SC_SC_CFG_1_RESETVAL                                (0x00000000U)

/* SC_CFG_2 */

#define CSL_SC_SC_CFG_2_ROW_ACC_OFFSET_MASK                     (0x0FFFFFFFU)
#define CSL_SC_SC_CFG_2_ROW_ACC_OFFSET_SHIFT                    (0U)
#define CSL_SC_SC_CFG_2_ROW_ACC_OFFSET_RESETVAL                 (0x00000000U)
#define CSL_SC_SC_CFG_2_ROW_ACC_OFFSET_MAX                      (0x0fffffffU)

#define CSL_SC_SC_CFG_2_RESETVAL                                (0x00000000U)

/* SC_CFG_3 */

#define CSL_SC_SC_CFG_3_ROW_ACC_OFFSET_B_MASK                   (0x0FFFFFFFU)
#define CSL_SC_SC_CFG_3_ROW_ACC_OFFSET_B_SHIFT                  (0U)
#define CSL_SC_SC_CFG_3_ROW_ACC_OFFSET_B_RESETVAL               (0x00000000U)
#define CSL_SC_SC_CFG_3_ROW_ACC_OFFSET_B_MAX                    (0x0fffffffU)

#define CSL_SC_SC_CFG_3_RESETVAL                                (0x00000000U)

/* SC_CFG_4 */

#define CSL_SC_SC_CFG_4_TAR_H_MASK                              (0x000007FFU)
#define CSL_SC_SC_CFG_4_TAR_H_SHIFT                             (0U)
#define CSL_SC_SC_CFG_4_TAR_H_RESETVAL                          (0x00000000U)
#define CSL_SC_SC_CFG_4_TAR_H_MAX                               (0x000007ffU)

#define CSL_SC_SC_CFG_4_TAR_W_MASK                              (0x007FF000U)
#define CSL_SC_SC_CFG_4_TAR_W_SHIFT                             (12U)
#define CSL_SC_SC_CFG_4_TAR_W_RESETVAL                          (0x00000000U)
#define CSL_SC_SC_CFG_4_TAR_W_MAX                               (0x000007ffU)

#define CSL_SC_SC_CFG_4_LIN_ACC_INC_U_MASK                      (0x07000000U)
#define CSL_SC_SC_CFG_4_LIN_ACC_INC_U_SHIFT                     (24U)
#define CSL_SC_SC_CFG_4_LIN_ACC_INC_U_RESETVAL                  (0x00000000U)
#define CSL_SC_SC_CFG_4_LIN_ACC_INC_U_MAX                       (0x00000007U)

#define CSL_SC_SC_CFG_4_NLIN_ACC_INIT_U_MASK                    (0x70000000U)
#define CSL_SC_SC_CFG_4_NLIN_ACC_INIT_U_SHIFT                   (28U)
#define CSL_SC_SC_CFG_4_NLIN_ACC_INIT_U_RESETVAL                (0x00000000U)
#define CSL_SC_SC_CFG_4_NLIN_ACC_INIT_U_MAX                     (0x00000007U)

#define CSL_SC_SC_CFG_4_RESETVAL                                (0x00000000U)

/* SC_CFG_5 */

#define CSL_SC_SC_CFG_5_SRC_H_MASK                              (0x000007FFU)
#define CSL_SC_SC_CFG_5_SRC_H_SHIFT                             (0U)
#define CSL_SC_SC_CFG_5_SRC_H_RESETVAL                          (0x00000000U)
#define CSL_SC_SC_CFG_5_SRC_H_MAX                               (0x000007ffU)

#define CSL_SC_SC_CFG_5_SRC_W_MASK                              (0x007FF000U)
#define CSL_SC_SC_CFG_5_SRC_W_SHIFT                             (12U)
#define CSL_SC_SC_CFG_5_SRC_W_RESETVAL                          (0x00000000U)
#define CSL_SC_SC_CFG_5_SRC_W_MAX                               (0x000007ffU)

#define CSL_SC_SC_CFG_5_NLIN_ACC_INC_U_MASK                     (0x07000000U)
#define CSL_SC_SC_CFG_5_NLIN_ACC_INC_U_SHIFT                    (24U)
#define CSL_SC_SC_CFG_5_NLIN_ACC_INC_U_RESETVAL                 (0x00000000U)
#define CSL_SC_SC_CFG_5_NLIN_ACC_INC_U_MAX                      (0x00000007U)

#define CSL_SC_SC_CFG_5_RESETVAL                                (0x00000000U)

/* SC_CFG_6 */

#define CSL_SC_SC_CFG_6_ROW_ACC_INIT_RAV_MASK                   (0x000003FFU)
#define CSL_SC_SC_CFG_6_ROW_ACC_INIT_RAV_SHIFT                  (0U)
#define CSL_SC_SC_CFG_6_ROW_ACC_INIT_RAV_RESETVAL               (0x00000000U)
#define CSL_SC_SC_CFG_6_ROW_ACC_INIT_RAV_MAX                    (0x000003ffU)

#define CSL_SC_SC_CFG_6_ROW_ACC_INIT_RAV_B_MASK                 (0x000FFC00U)
#define CSL_SC_SC_CFG_6_ROW_ACC_INIT_RAV_B_SHIFT                (10U)
#define CSL_SC_SC_CFG_6_ROW_ACC_INIT_RAV_B_RESETVAL             (0x00000000U)
#define CSL_SC_SC_CFG_6_ROW_ACC_INIT_RAV_B_MAX                  (0x000003ffU)

#define CSL_SC_SC_CFG_6_RESETVAL                                (0x00000000U)

/* SC_CFG_7 */

#define CSL_SC_SC_CFG_7_RESETVAL                                (0x00000000U)

/* SC_CFG_8 */

#define CSL_SC_SC_CFG_8_NLIN_LEFT_MASK                          (0x000007FFU)
#define CSL_SC_SC_CFG_8_NLIN_LEFT_SHIFT                         (0U)
#define CSL_SC_SC_CFG_8_NLIN_LEFT_RESETVAL                      (0x00000000U)
#define CSL_SC_SC_CFG_8_NLIN_LEFT_MAX                           (0x000007ffU)

#define CSL_SC_SC_CFG_8_NLIN_RIGHT_MASK                         (0x007FF000U)
#define CSL_SC_SC_CFG_8_NLIN_RIGHT_SHIFT                        (12U)
#define CSL_SC_SC_CFG_8_NLIN_RIGHT_RESETVAL                     (0x00000000U)
#define CSL_SC_SC_CFG_8_NLIN_RIGHT_MAX                          (0x000007ffU)

#define CSL_SC_SC_CFG_8_RESETVAL                                (0x00000000U)

/* SC_CFG_9 */

#define CSL_SC_SC_CFG_9_LIN_ACC_INC_MASK                        (0xFFFFFFFFU)
#define CSL_SC_SC_CFG_9_LIN_ACC_INC_SHIFT                       (0U)
#define CSL_SC_SC_CFG_9_LIN_ACC_INC_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_9_LIN_ACC_INC_MAX                         (0xffffffffU)

#define CSL_SC_SC_CFG_9_RESETVAL                                (0x00000000U)

/* SC_CFG_10 */

#define CSL_SC_SC_CFG_10_NLIN_ACC_INIT_MASK                     (0xFFFFFFFFU)
#define CSL_SC_SC_CFG_10_NLIN_ACC_INIT_SHIFT                    (0U)
#define CSL_SC_SC_CFG_10_NLIN_ACC_INIT_RESETVAL                 (0x00000000U)
#define CSL_SC_SC_CFG_10_NLIN_ACC_INIT_MAX                      (0xffffffffU)

#define CSL_SC_SC_CFG_10_RESETVAL                               (0x00000000U)

/* SC_CFG_11 */

#define CSL_SC_SC_CFG_11_NLIN_ACC_INC_MASK                      (0xFFFFFFFFU)
#define CSL_SC_SC_CFG_11_NLIN_ACC_INC_SHIFT                     (0U)
#define CSL_SC_SC_CFG_11_NLIN_ACC_INC_RESETVAL                  (0x00000000U)
#define CSL_SC_SC_CFG_11_NLIN_ACC_INC_MAX                       (0xffffffffU)

#define CSL_SC_SC_CFG_11_RESETVAL                               (0x00000000U)

/* SC_CFG_12 */

#define CSL_SC_SC_CFG_12_COL_ACC_OFFSET_MASK                    (0x01FFFFFFU)
#define CSL_SC_SC_CFG_12_COL_ACC_OFFSET_SHIFT                   (0U)
#define CSL_SC_SC_CFG_12_COL_ACC_OFFSET_RESETVAL                (0x00000000U)
#define CSL_SC_SC_CFG_12_COL_ACC_OFFSET_MAX                     (0x01ffffffU)

#define CSL_SC_SC_CFG_12_RESETVAL                               (0x00000000U)

/* SC_CFG_13 */

#define CSL_SC_SC_CFG_13_SC_FACTOR_RAV_MASK                     (0x000003FFU)
#define CSL_SC_SC_CFG_13_SC_FACTOR_RAV_SHIFT                    (0U)
#define CSL_SC_SC_CFG_13_SC_FACTOR_RAV_RESETVAL                 (0x00000000U)
#define CSL_SC_SC_CFG_13_SC_FACTOR_RAV_MAX                      (0x000003ffU)

#define CSL_SC_SC_CFG_13_RESETVAL                               (0x00000000U)

/* SC_CFG_14 */

#define CSL_SC_SC_CFG_14_RESETVAL                               (0x00000000U)

/* SC_CFG_15 */

#define CSL_SC_SC_CFG_15_RESETVAL                               (0x00000000U)

/* SC_CFG_16 */

#define CSL_SC_SC_CFG_16_RESETVAL                               (0x00000000U)

/* SC_CFG_18 */

#define CSL_SC_SC_CFG_18_HS_FACTOR_MASK                         (0x000003FFU)
#define CSL_SC_SC_CFG_18_HS_FACTOR_SHIFT                        (0U)
#define CSL_SC_SC_CFG_18_HS_FACTOR_RESETVAL                     (0x00000000U)
#define CSL_SC_SC_CFG_18_HS_FACTOR_MAX                          (0x000003ffU)

#define CSL_SC_SC_CFG_18_RESETVAL                               (0x00000000U)

/* SC_CFG_19 */

#define CSL_SC_SC_CFG_19_HPF_COEFF0_MASK                        (0x000000FFU)
#define CSL_SC_SC_CFG_19_HPF_COEFF0_SHIFT                       (0U)
#define CSL_SC_SC_CFG_19_HPF_COEFF0_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_19_HPF_COEFF0_MAX                         (0x000000ffU)

#define CSL_SC_SC_CFG_19_HPF_COEFF1_MASK                        (0x0000FF00U)
#define CSL_SC_SC_CFG_19_HPF_COEFF1_SHIFT                       (8U)
#define CSL_SC_SC_CFG_19_HPF_COEFF1_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_19_HPF_COEFF1_MAX                         (0x000000ffU)

#define CSL_SC_SC_CFG_19_HPF_COEFF2_MASK                        (0x00FF0000U)
#define CSL_SC_SC_CFG_19_HPF_COEFF2_SHIFT                       (16U)
#define CSL_SC_SC_CFG_19_HPF_COEFF2_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_19_HPF_COEFF2_MAX                         (0x000000ffU)

#define CSL_SC_SC_CFG_19_HPF_COEFF3_MASK                        (0xFF000000U)
#define CSL_SC_SC_CFG_19_HPF_COEFF3_SHIFT                       (24U)
#define CSL_SC_SC_CFG_19_HPF_COEFF3_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_19_HPF_COEFF3_MAX                         (0x000000ffU)

#define CSL_SC_SC_CFG_19_RESETVAL                               (0x00000000U)

/* SC_CFG_20 */

#define CSL_SC_SC_CFG_20_HPF_COEFF4_MASK                        (0x000000FFU)
#define CSL_SC_SC_CFG_20_HPF_COEFF4_SHIFT                       (0U)
#define CSL_SC_SC_CFG_20_HPF_COEFF4_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_20_HPF_COEFF4_MAX                         (0x000000ffU)

#define CSL_SC_SC_CFG_20_HPF_COEFF5_MASK                        (0x0000FF00U)
#define CSL_SC_SC_CFG_20_HPF_COEFF5_SHIFT                       (8U)
#define CSL_SC_SC_CFG_20_HPF_COEFF5_RESETVAL                    (0x00000000U)
#define CSL_SC_SC_CFG_20_HPF_COEFF5_MAX                         (0x000000ffU)

#define CSL_SC_SC_CFG_20_HPF_NORM_SHIFT_MASK                    (0x00070000U)
#define CSL_SC_SC_CFG_20_HPF_NORM_SHIFT_SHIFT                   (16U)
#define CSL_SC_SC_CFG_20_HPF_NORM_SHIFT_RESETVAL                (0x00000000U)
#define CSL_SC_SC_CFG_20_HPF_NORM_SHIFT_MAX                     (0x00000007U)

#define CSL_SC_SC_CFG_20_NL_LIMIT_MASK                          (0x1FF00000U)
#define CSL_SC_SC_CFG_20_NL_LIMIT_SHIFT                         (20U)
#define CSL_SC_SC_CFG_20_NL_LIMIT_RESETVAL                      (0x00000000U)
#define CSL_SC_SC_CFG_20_NL_LIMIT_MAX                           (0x000001ffU)

#define CSL_SC_SC_CFG_20_RESETVAL                               (0x00000000U)

/* SC_CFG_21 */

#define CSL_SC_SC_CFG_21_NL_LO_THRLD_MASK                       (0x000001FFU)
#define CSL_SC_SC_CFG_21_NL_LO_THRLD_SHIFT                      (0U)
#define CSL_SC_SC_CFG_21_NL_LO_THRLD_RESETVAL                   (0x00000000U)
#define CSL_SC_SC_CFG_21_NL_LO_THRLD_MAX                        (0x000001ffU)

#define CSL_SC_SC_CFG_21_NL_LO_SLOPE_MASK                       (0x00FF0000U)
#define CSL_SC_SC_CFG_21_NL_LO_SLOPE_SHIFT                      (16U)
#define CSL_SC_SC_CFG_21_NL_LO_SLOPE_RESETVAL                   (0x00000000U)
#define CSL_SC_SC_CFG_21_NL_LO_SLOPE_MAX                        (0x000000ffU)

#define CSL_SC_SC_CFG_21_RESETVAL                               (0x00000000U)

/* SC_CFG_22 */

#define CSL_SC_SC_CFG_22_NL_HI_THRLD_MASK                       (0x000001FFU)
#define CSL_SC_SC_CFG_22_NL_HI_THRLD_SHIFT                      (0U)
#define CSL_SC_SC_CFG_22_NL_HI_THRLD_RESETVAL                   (0x00000000U)
#define CSL_SC_SC_CFG_22_NL_HI_THRLD_MAX                        (0x000001ffU)

#define CSL_SC_SC_CFG_22_NL_HI_SLOPE_SHIFT_MASK                 (0x00070000U)
#define CSL_SC_SC_CFG_22_NL_HI_SLOPE_SHIFT_SHIFT                (16U)
#define CSL_SC_SC_CFG_22_NL_HI_SLOPE_SHIFT_RESETVAL             (0x00000000U)
#define CSL_SC_SC_CFG_22_NL_HI_SLOPE_SHIFT_MAX                  (0x00000007U)

#define CSL_SC_SC_CFG_22_RESETVAL                               (0x00000000U)

/* SC_CFG_24 */

#define CSL_SC_SC_CFG_24_ORG_H_MASK                             (0x000007FFU)
#define CSL_SC_SC_CFG_24_ORG_H_SHIFT                            (0U)
#define CSL_SC_SC_CFG_24_ORG_H_RESETVAL                         (0x00000000U)
#define CSL_SC_SC_CFG_24_ORG_H_MAX                              (0x000007ffU)

#define CSL_SC_SC_CFG_24_ORG_W_MASK                             (0x07FF0000U)
#define CSL_SC_SC_CFG_24_ORG_W_SHIFT                            (16U)
#define CSL_SC_SC_CFG_24_ORG_W_RESETVAL                         (0x00000000U)
#define CSL_SC_SC_CFG_24_ORG_W_MAX                              (0x000007ffU)

#define CSL_SC_SC_CFG_24_RESETVAL                               (0x00000000U)

/* SC_CFG_25 */

#define CSL_SC_SC_CFG_25_OFF_H_MASK                             (0x000007FFU)
#define CSL_SC_SC_CFG_25_OFF_H_SHIFT                            (0U)
#define CSL_SC_SC_CFG_25_OFF_H_RESETVAL                         (0x00000000U)
#define CSL_SC_SC_CFG_25_OFF_H_MAX                              (0x000007ffU)

#define CSL_SC_SC_CFG_25_OFF_W_MASK                             (0x07FF0000U)
#define CSL_SC_SC_CFG_25_OFF_W_SHIFT                            (16U)
#define CSL_SC_SC_CFG_25_OFF_W_RESETVAL                         (0x00000000U)
#define CSL_SC_SC_CFG_25_OFF_W_MAX                              (0x000007ffU)

#define CSL_SC_SC_CFG_25_RESETVAL                               (0x00000000U)

/* SC_CFG_26 */

#define CSL_SC_SC_CFG_26_RESETVAL                               (0x00000000U)

/* SC_CFG_27 */

#define CSL_SC_SC_CFG_27_RESETVAL                               (0x00000000U)

/* SC_CFG_28 */

#define CSL_SC_SC_CFG_28_RESETVAL                               (0x00000000U)

/* SC_CFG_29 */

#define CSL_SC_SC_CFG_29_RESETVAL                               (0x00000000U)

/* SC_CFG_30 */

#define CSL_SC_SC_CFG_30_RESETVAL                               (0x00000000U)

/* SC_CFG_31 */

#define CSL_SC_SC_CFG_31_RESETVAL                               (0x00000000U)

#ifdef __cplusplus
}
#endif

#endif
