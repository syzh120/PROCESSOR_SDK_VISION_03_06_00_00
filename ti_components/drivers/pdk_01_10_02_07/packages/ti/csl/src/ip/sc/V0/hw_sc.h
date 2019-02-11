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
 *  \file       hw_sc.h
 *
 *  \brief      register-level header file for SC
 *
**/

#ifndef HW_SC_H_
#define HW_SC_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define SC_CFG_0                                                                                            (0x0U)
#define SC_CFG_1                                                                                            (0x4U)
#define SC_CFG_2                                                                                            (0x8U)
#define SC_CFG_3                                                                                            (0xcU)
#define SC_CFG_4                                                                                            (0x10U)
#define SC_CFG_5                                                                                            (0x14U)
#define SC_CFG_6                                                                                            (0x18U)
#define SC_CFG_7                                                                                            (0x1cU)
#define SC_CFG_8                                                                                            (0x20U)
#define SC_CFG_9                                                                                            (0x24U)
#define SC_CFG_10                                                                                           (0x28U)
#define SC_CFG_11                                                                                           (0x2cU)
#define SC_CFG_12                                                                                           (0x30U)
#define SC_CFG_13                                                                                           (0x34U)
#define SC_CFG_14                                                                                           (0x38U)
#define SC_CFG_15                                                                                           (0x3cU)
#define SC_CFG_16                                                                                           (0x40U)
#define SC_CFG_18                                                                                           (0x48U)
#define SC_CFG_19                                                                                           (0x4cU)
#define SC_CFG_20                                                                                           (0x50U)
#define SC_CFG_21                                                                                           (0x54U)
#define SC_CFG_22                                                                                           (0x58U)
#define SC_CFG_24                                                                                           (0x60U)
#define SC_CFG_25                                                                                           (0x64U)
#define SC_CFG_26                                                                                           (0x68U)
#define SC_CFG_27                                                                                           (0x6cU)
#define SC_CFG_28                                                                                           (0x70U)
#define SC_CFG_29                                                                                           (0x74U)
#define SC_CFG_30                                                                                           (0x78U)
#define SC_CFG_31                                                                                           (0x7cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define SC_CFG_0_INTERLACE_O_SHIFT                                                                          (0U)
#define SC_CFG_0_INTERLACE_O_MASK                                                                           (0x00000001U)

#define SC_CFG_0_LINEAR_SHIFT                                                                               (1U)
#define SC_CFG_0_LINEAR_MASK                                                                                (0x00000002U)

#define SC_CFG_0_SC_BYPASS_SHIFT                                                                            (2U)
#define SC_CFG_0_SC_BYPASS_MASK                                                                             (0x00000004U)

#define SC_CFG_0_INVT_FID_SHIFT                                                                             (3U)
#define SC_CFG_0_INVT_FID_MASK                                                                              (0x00000008U)

#define SC_CFG_0_USE_RAV_SHIFT                                                                              (4U)
#define SC_CFG_0_USE_RAV_MASK                                                                               (0x00000010U)

#define SC_CFG_0_ENABLE_EV_SHIFT                                                                            (5U)
#define SC_CFG_0_ENABLE_EV_MASK                                                                             (0x00000020U)

#define SC_CFG_0_AUTO_HS_SHIFT                                                                              (6U)
#define SC_CFG_0_AUTO_HS_MASK                                                                               (0x00000040U)

#define SC_CFG_0_DCM_2X_SHIFT                                                                               (7U)
#define SC_CFG_0_DCM_2X_MASK                                                                                (0x00000080U)

#define SC_CFG_0_DCM_4X_SHIFT                                                                               (8U)
#define SC_CFG_0_DCM_4X_MASK                                                                                (0x00000100U)

#define SC_CFG_0_HP_BYPASS_SHIFT                                                                            (9U)
#define SC_CFG_0_HP_BYPASS_MASK                                                                             (0x00000200U)

#define SC_CFG_0_INTERLACE_I_SHIFT                                                                          (10U)
#define SC_CFG_0_INTERLACE_I_MASK                                                                           (0x00000400U)

#define SC_CFG_0_ENABLE_Y_PK_SHIFT                                                                          (14U)
#define SC_CFG_0_ENABLE_Y_PK_MASK                                                                           (0x00004000U)

#define SC_CFG_0_ENABLE_TRIM_SHIFT                                                                          (15U)
#define SC_CFG_0_ENABLE_TRIM_MASK                                                                           (0x00008000U)

#define SC_CFG_0_ENABLE_FID_SELFGEN_SHIFT                                                                   (16U)
#define SC_CFG_0_ENABLE_FID_SELFGEN_MASK                                                                    (0x00010000U)

#define SC_CFG_1_ROW_ACC_INC_SHIFT                                                                          (0U)
#define SC_CFG_1_ROW_ACC_INC_MASK                                                                           (0x07ffffffU)

#define SC_CFG_2_ROW_ACC_OFFSET_SHIFT                                                                       (0U)
#define SC_CFG_2_ROW_ACC_OFFSET_MASK                                                                        (0x0fffffffU)

#define SC_CFG_3_ROW_ACC_OFFSET_B_SHIFT                                                                     (0U)
#define SC_CFG_3_ROW_ACC_OFFSET_B_MASK                                                                      (0x0fffffffU)

#define SC_CFG_4_TAR_H_SHIFT                                                                                (0U)
#define SC_CFG_4_TAR_H_MASK                                                                                 (0x000007ffU)

#define SC_CFG_4_TAR_W_SHIFT                                                                                (12U)
#define SC_CFG_4_TAR_W_MASK                                                                                 (0x007ff000U)

#define SC_CFG_4_LIN_ACC_INC_U_SHIFT                                                                        (24U)
#define SC_CFG_4_LIN_ACC_INC_U_MASK                                                                         (0x07000000U)

#define SC_CFG_4_NLIN_ACC_INIT_U_SHIFT                                                                      (28U)
#define SC_CFG_4_NLIN_ACC_INIT_U_MASK                                                                       (0x70000000U)

#define SC_CFG_5_SRC_H_SHIFT                                                                                (0U)
#define SC_CFG_5_SRC_H_MASK                                                                                 (0x000007ffU)

#define SC_CFG_5_SRC_W_SHIFT                                                                                (12U)
#define SC_CFG_5_SRC_W_MASK                                                                                 (0x007ff000U)

#define SC_CFG_5_NLIN_ACC_INC_U_SHIFT                                                                       (24U)
#define SC_CFG_5_NLIN_ACC_INC_U_MASK                                                                        (0x07000000U)

#define SC_CFG_6_ROW_ACC_INIT_RAV_SHIFT                                                                     (0U)
#define SC_CFG_6_ROW_ACC_INIT_RAV_MASK                                                                      (0x000003ffU)

#define SC_CFG_6_ROW_ACC_INIT_RAV_B_SHIFT                                                                   (10U)
#define SC_CFG_6_ROW_ACC_INIT_RAV_B_MASK                                                                    (0x000ffc00U)

#define SC_CFG_8_NLIN_LEFT_SHIFT                                                                            (0U)
#define SC_CFG_8_NLIN_LEFT_MASK                                                                             (0x000007ffU)

#define SC_CFG_8_NLIN_RIGHT_SHIFT                                                                           (12U)
#define SC_CFG_8_NLIN_RIGHT_MASK                                                                            (0x007ff000U)

#define SC_CFG_9_LIN_ACC_INC_SHIFT                                                                          (0U)
#define SC_CFG_9_LIN_ACC_INC_MASK                                                                           (0xffffffffU)

#define SC_CFG_10_NLIN_ACC_INIT_SHIFT                                                                       (0U)
#define SC_CFG_10_NLIN_ACC_INIT_MASK                                                                        (0xffffffffU)

#define SC_CFG_11_NLIN_ACC_INC_SHIFT                                                                        (0U)
#define SC_CFG_11_NLIN_ACC_INC_MASK                                                                         (0xffffffffU)

#define SC_CFG_12_COL_ACC_OFFSET_SHIFT                                                                      (0U)
#define SC_CFG_12_COL_ACC_OFFSET_MASK                                                                       (0x01ffffffU)

#define SC_CFG_13_SC_FACTOR_RAV_SHIFT                                                                       (0U)
#define SC_CFG_13_SC_FACTOR_RAV_MASK                                                                        (0x000003ffU)

#define SC_CFG_18_HS_FACTOR_SHIFT                                                                           (0U)
#define SC_CFG_18_HS_FACTOR_MASK                                                                            (0x000003ffU)

#define SC_CFG_19_HPF_COEFF0_SHIFT                                                                          (0U)
#define SC_CFG_19_HPF_COEFF0_MASK                                                                           (0x000000ffU)

#define SC_CFG_19_HPF_COEFF1_SHIFT                                                                          (8U)
#define SC_CFG_19_HPF_COEFF1_MASK                                                                           (0x0000ff00U)

#define SC_CFG_19_HPF_COEFF2_SHIFT                                                                          (16U)
#define SC_CFG_19_HPF_COEFF2_MASK                                                                           (0x00ff0000U)

#define SC_CFG_19_HPF_COEFF3_SHIFT                                                                          (24U)
#define SC_CFG_19_HPF_COEFF3_MASK                                                                           (0xff000000U)

#define SC_CFG_20_HPF_COEFF4_SHIFT                                                                          (0U)
#define SC_CFG_20_HPF_COEFF4_MASK                                                                           (0x000000ffU)

#define SC_CFG_20_HPF_COEFF5_SHIFT                                                                          (8U)
#define SC_CFG_20_HPF_COEFF5_MASK                                                                           (0x0000ff00U)

#define SC_CFG_20_HPF_NORM_SHIFT_SHIFT                                                                      (16U)
#define SC_CFG_20_HPF_NORM_SHIFT_MASK                                                                       (0x00070000U)

#define SC_CFG_20_NL_LIMIT_SHIFT                                                                            (20U)
#define SC_CFG_20_NL_LIMIT_MASK                                                                             (0x1ff00000U)

#define SC_CFG_21_NL_LO_THRLD_SHIFT                                                                         (0U)
#define SC_CFG_21_NL_LO_THRLD_MASK                                                                          (0x000001ffU)

#define SC_CFG_21_NL_LO_SLOPE_SHIFT                                                                         (16U)
#define SC_CFG_21_NL_LO_SLOPE_MASK                                                                          (0x00ff0000U)

#define SC_CFG_22_NL_HI_THRLD_SHIFT                                                                         (0U)
#define SC_CFG_22_NL_HI_THRLD_MASK                                                                          (0x000001ffU)

#define SC_CFG_22_NL_HI_SLOPE_SHIFT_SHIFT                                                                   (16U)
#define SC_CFG_22_NL_HI_SLOPE_SHIFT_MASK                                                                    (0x00070000U)

#define SC_CFG_24_ORG_H_SHIFT                                                                               (0U)
#define SC_CFG_24_ORG_H_MASK                                                                                (0x000007ffU)

#define SC_CFG_24_ORG_W_SHIFT                                                                               (16U)
#define SC_CFG_24_ORG_W_MASK                                                                                (0x07ff0000U)

#define SC_CFG_25_OFF_H_SHIFT                                                                               (0U)
#define SC_CFG_25_OFF_H_MASK                                                                                (0x000007ffU)

#define SC_CFG_25_OFF_W_SHIFT                                                                               (16U)
#define SC_CFG_25_OFF_W_MASK                                                                                (0x07ff0000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_SC_H_ */
