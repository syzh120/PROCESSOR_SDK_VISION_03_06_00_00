/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_ctrl_core_pad.h
 *
 *  \brief  Register-level header file for CTRL_CORE_PAD
 *
**/

#ifndef HW_CTRL_CORE_PAD_H_
#define HW_CTRL_CORE_PAD_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/

#define CTRL_CORE_CONTROL_I2C_0                                 (0x64U)
#define CTRL_CORE_CONTROL_CAMERA_RX                             (0x68U)
#define CTRL_CORE_CONTROL_DDRCACH1_0                            (0x90U)
#define CTRL_CORE_CONTROL_DDRCH1_0                              (0x98U)
#define CTRL_CORE_CONTROL_DDRCH1_1                              (0x9cU)
#define CTRL_CORE_CONTROL_DDRCH1_2                              (0xa8U)
#define CTRL_CORE_CONTROL_DDRIO_0                               (0xb0U)
#define CTRL_CORE_CONTROL_SPARE_RW                              (0x7cU)
#define CTRL_CORE_CONTROL_SPARE_R                               (0x80U)
#define CTRL_CORE_CONTROL_SPARE_R_C0                            (0x84U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0                           (0x9cU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_GLFENB_SHIFT                               (31U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_GLFENB_MASK                                (0x80000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_GLFENB_ENABLE                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_GLFENB_DISABLE                              (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_PULLUPRESX_SHIFT                           (30U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_PULLUPRESX_MASK                            (0x40000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_PULLUPRESX_DISABLE                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SDA_PULLUPRESX_ENABLE                           (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_GLFENB_SHIFT                               (29U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_GLFENB_MASK                                (0x20000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_GLFENB_ENABLE                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_GLFENB_DISABLE                              (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_PULLUPRESX_SHIFT                           (28U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_PULLUPRESX_MASK                            (0x10000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_PULLUPRESX_DISABLE                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SDA_PULLUPRESX_ENABLE                           (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_GLFENB_SHIFT                               (27U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_GLFENB_MASK                                (0x08000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_GLFENB_ENABLE                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_GLFENB_DISABLE                              (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_PULLUPRESX_SHIFT                           (26U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_PULLUPRESX_MASK                            (0x04000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_PULLUPRESX_DISABLE                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SDA_PULLUPRESX_ENABLE                           (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_GLFENB_SHIFT                          (25U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_GLFENB_MASK                           (0x02000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_GLFENB_ENABLE                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_GLFENB_DISABLE                         (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_PULLUPRESX_SHIFT                      (24U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_PULLUPRESX_MASK                       (0x01000000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_PULLUPRESX_DISABLE                     (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SDA_PULLUPRESX_ENABLE                      (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_GLFENB_SHIFT                               (23U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_GLFENB_MASK                                (0x00800000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_GLFENB_ENABLE                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_GLFENB_DISABLE                              (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_PULLUPRESX_SHIFT                           (22U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_PULLUPRESX_MASK                            (0x00400000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_PULLUPRESX_DISABLE                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C4_SCL_PULLUPRESX_ENABLE                           (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_GLFENB_SHIFT                               (21U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_GLFENB_MASK                                (0x00200000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_GLFENB_ENABLE                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_GLFENB_DISABLE                              (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_PULLUPRESX_SHIFT                           (20U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_PULLUPRESX_MASK                            (0x00100000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_PULLUPRESX_DISABLE                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C3_SCL_PULLUPRESX_ENABLE                           (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_GLFENB_SHIFT                               (19U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_GLFENB_MASK                                (0x00080000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_GLFENB_ENABLE                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_GLFENB_DISABLE                              (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_PULLUPRESX_SHIFT                           (18U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_PULLUPRESX_MASK                            (0x00040000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_PULLUPRESX_DISABLE                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C2_SCL_PULLUPRESX_ENABLE                           (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_GLFENB_SHIFT                          (17U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_GLFENB_MASK                           (0x00020000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_GLFENB_ENABLE                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_GLFENB_DISABLE                         (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_PULLUPRESX_SHIFT                      (16U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_PULLUPRESX_MASK                       (0x00010000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_PULLUPRESX_DISABLE                     (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C1_PMIC_SCL_PULLUPRESX_ENABLE                      (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_GLFENB_SHIFT                               (15U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_GLFENB_MASK                                (0x00008000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_GLFENB_ENABLE                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_GLFENB_DISABLE                              (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_PULLUPRESX_SHIFT                           (14U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_PULLUPRESX_MASK                            (0x00004000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_PULLUPRESX_DISABLE                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SDA_PULLUPRESX_ENABLE                           (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_GLFENB_SHIFT                               (13U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_GLFENB_MASK                                (0x00002000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_GLFENB_ENABLE                               (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_GLFENB_DISABLE                              (0U)

#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_PULLUPRESX_SHIFT                           (12U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_PULLUPRESX_MASK                            (0x00001000U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_PULLUPRESX_DISABLE                          (1U)
#define CTRL_CORE_CONTROL_I2C_0_I2C5_SCL_PULLUPRESX_ENABLE                           (0U)

#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_MODE_SHIFT                             (8U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_MODE_MASK                              (0x00000100U)

#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_LANEENABLE_SHIFT                       (3U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_LANEENABLE_MASK                        (0x000000f8U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_LANEENABLE_ENABLE                       (1U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_LANEENABLE_DISABLE                      (0U)

#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_SHIFT                          (1U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_MASK                           (0x00000006U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_CCP2_DATA_STROBE                (1U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_GPI                             (3U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_DPHY                            (0U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CAMMODE_CCP2_DATA_CLOCK                 (2U)

#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_SHIFT                        (0U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_MASK                         (0x00000001U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_ENABLE                        (1U)
#define CTRL_CORE_CONTROL_CAMERA_RX_CSIPORTA_CTRLCLKEN_DISABLE                       (0U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_SHIFT                           (29U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_MASK                            (0xe0000000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_0P73REXT                         (6U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_0P88REXT                         (4U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_1P33REXT                         (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_REXT                             (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_1P6REXT                          (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_0P67REXT                         (7U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_1P14REXT                         (2U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_I_0P8REXT                          (5U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_SHIFT                          (26U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_MASK                           (0x1c000000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_SLOW                            (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_FASTEST                         (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_SLOWEST                         (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_SR_FAST                            (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_SHIFT                          (24U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_MASK                           (0x03000000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_PU                              (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_KEEPER                          (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_NONE                            (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART0_WD_PD                              (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_SHIFT                          (21U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_MASK                           (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_0P73REXT                        (6U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_0P88REXT                        (4U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_1P33REXT                        (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_REXT                            (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_1P6REXT                         (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_0P67REXT                        (7U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_1P14REXT                        (2U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_I_0P8REXT                         (5U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_SHIFT                         (18U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_MASK                          (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_SLOW                           (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_FASTEST                        (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_SLOWEST                        (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_SR_FAST                           (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_SHIFT                         (16U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_MASK                          (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_PU                             (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_KEEPER                         (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_NONE                           (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5A_WD_PD                             (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_SHIFT                          (13U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_MASK                           (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_0P73REXT                        (6U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_0P88REXT                        (4U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_1P33REXT                        (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_REXT                            (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_1P6REXT                         (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_0P67REXT                        (7U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_1P14REXT                        (2U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_I_0P8REXT                         (5U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_SHIFT                         (10U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_MASK                          (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_SLOW                           (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_FASTEST                        (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_SLOWEST                        (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_SR_FAST                           (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_SHIFT                         (8U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_MASK                          (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_PU                             (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_KEEPER                         (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_NONE                           (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART5B_WD_PD                             (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_SHIFT                           (5U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_MASK                            (0x000000e0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_0P73REXT                         (6U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_0P88REXT                         (4U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_1P33REXT                         (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_REXT                             (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_1P6REXT                          (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_0P67REXT                         (7U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_1P14REXT                         (2U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_I_0P8REXT                          (5U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_SHIFT                          (2U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_MASK                           (0x0000001cU)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_SLOW                            (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_FASTEST                         (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_SLOWEST                         (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_SR_FAST                            (2U)

#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_SHIFT                          (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_MASK                           (0x00000003U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_PU                              (1U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_KEEPER                          (3U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_NONE                            (0U)
#define CTRL_CORE_CONTROL_DDRCACH1_0_DDRCH1_PART6_WD_PD                              (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_I_SHIFT                                   (29U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_I_MASK                                    (0xe0000000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_I_0P73REXT                                 (6U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_I_0P88REXT                                 (4U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_I_1P33REXT                                 (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_I_REXT                                     (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_I_1P6REXT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_I_0P67REXT                                 (7U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_I_1P14REXT                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_I_0P8REXT                                  (5U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_SR_SHIFT                                  (26U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_SR_MASK                                   (0x1c000000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_SR_SLOW                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_SR_FASTEST                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_SR_SLOWEST                                 (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_SR_FAST                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_WD_SHIFT                                  (24U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_WD_MASK                                   (0x03000000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_WD_PU                                      (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_WD_KEEPER                                  (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_WD_NONE                                    (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1A_WD_PD                                      (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_I_SHIFT                                   (21U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_I_MASK                                    (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_I_0P73REXT                                 (6U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_I_0P88REXT                                 (4U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_I_1P33REXT                                 (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_I_REXT                                     (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_I_1P6REXT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_I_0P67REXT                                 (7U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_I_1P14REXT                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_I_0P8REXT                                  (5U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_SR_SHIFT                                  (18U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_SR_MASK                                   (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_SR_SLOW                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_SR_FASTEST                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_SR_SLOWEST                                 (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_SR_FAST                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_WD_SHIFT                                  (16U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_WD_MASK                                   (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_WD_PU                                      (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_WD_KEEPER                                  (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_WD_NONE                                    (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART1B_WD_PD                                      (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_I_SHIFT                                   (13U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_I_MASK                                    (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_I_0P73REXT                                 (6U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_I_0P88REXT                                 (4U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_I_1P33REXT                                 (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_I_REXT                                     (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_I_1P6REXT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_I_0P67REXT                                 (7U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_I_1P14REXT                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_I_0P8REXT                                  (5U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_SR_SHIFT                                  (10U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_SR_MASK                                   (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_SR_SLOW                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_SR_FASTEST                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_SR_SLOWEST                                 (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_SR_FAST                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_WD_SHIFT                                  (8U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_WD_MASK                                   (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_WD_PU                                      (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_WD_KEEPER                                  (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_WD_NONE                                    (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2A_WD_PD                                      (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_I_SHIFT                                   (5U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_I_MASK                                    (0x000000e0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_I_0P73REXT                                 (6U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_I_0P88REXT                                 (4U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_I_1P33REXT                                 (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_I_REXT                                     (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_I_1P6REXT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_I_0P67REXT                                 (7U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_I_1P14REXT                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_I_0P8REXT                                  (5U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_SR_SHIFT                                  (2U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_SR_MASK                                   (0x0000001cU)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_SR_SLOW                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_SR_FASTEST                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_SR_SLOWEST                                 (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_SR_FAST                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_WD_SHIFT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_WD_MASK                                   (0x00000003U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_WD_PU                                      (1U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_WD_KEEPER                                  (3U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_WD_NONE                                    (0U)
#define CTRL_CORE_CONTROL_DDRCH1_0_PART2B_WD_PD                                      (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_I_SHIFT                                   (29U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_I_MASK                                    (0xe0000000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_I_0P73REXT                                 (6U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_I_0P88REXT                                 (4U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_I_1P33REXT                                 (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_I_REXT                                     (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_I_1P6REXT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_I_0P67REXT                                 (7U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_I_1P14REXT                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_I_0P8REXT                                  (5U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_SR_SHIFT                                  (26U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_SR_MASK                                   (0x1c000000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_SR_SLOW                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_SR_FASTEST                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_SR_SLOWEST                                 (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_SR_FAST                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_WD_SHIFT                                  (24U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_WD_MASK                                   (0x03000000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_WD_PU                                      (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_WD_KEEPER                                  (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_WD_NONE                                    (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3A_WD_PD                                      (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_I_SHIFT                                   (21U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_I_MASK                                    (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_I_0P73REXT                                 (6U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_I_0P88REXT                                 (4U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_I_1P33REXT                                 (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_I_REXT                                     (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_I_1P6REXT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_I_0P67REXT                                 (7U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_I_1P14REXT                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_I_0P8REXT                                  (5U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_SR_SHIFT                                  (18U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_SR_MASK                                   (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_SR_SLOW                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_SR_FASTEST                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_SR_SLOWEST                                 (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_SR_FAST                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_WD_SHIFT                                  (16U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_WD_MASK                                   (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_WD_PU                                      (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_WD_KEEPER                                  (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_WD_NONE                                    (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART3B_WD_PD                                      (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_I_SHIFT                                   (13U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_I_MASK                                    (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_I_0P73REXT                                 (6U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_I_0P88REXT                                 (4U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_I_1P33REXT                                 (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_I_REXT                                     (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_I_1P6REXT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_I_0P67REXT                                 (7U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_I_1P14REXT                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_I_0P8REXT                                  (5U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_SR_SHIFT                                  (10U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_SR_MASK                                   (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_SR_SLOW                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_SR_FASTEST                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_SR_SLOWEST                                 (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_SR_FAST                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_WD_SHIFT                                  (8U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_WD_MASK                                   (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_WD_PU                                      (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_WD_KEEPER                                  (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_WD_NONE                                    (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4A_WD_PD                                      (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_I_SHIFT                                   (5U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_I_MASK                                    (0x000000e0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_I_0P73REXT                                 (6U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_I_0P88REXT                                 (4U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_I_1P33REXT                                 (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_I_REXT                                     (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_I_1P6REXT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_I_0P67REXT                                 (7U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_I_1P14REXT                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_I_0P8REXT                                  (5U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_SR_SHIFT                                  (2U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_SR_MASK                                   (0x0000001cU)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_SR_SLOW                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_SR_FASTEST                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_SR_SLOWEST                                 (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_SR_FAST                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_WD_SHIFT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_WD_MASK                                   (0x00000003U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_WD_PU                                      (1U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_WD_KEEPER                                  (3U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_WD_NONE                                    (0U)
#define CTRL_CORE_CONTROL_DDRCH1_1_PART4B_WD_PD                                      (2U)

#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_I_SHIFT                                   (21U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_I_MASK                                    (0x00e00000U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_I_0P73REXT                                 (6U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_I_0P88REXT                                 (4U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_I_1P33REXT                                 (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_I_REXT                                     (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_I_1P6REXT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_I_0P67REXT                                 (7U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_I_1P14REXT                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_I_0P8REXT                                  (5U)

#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_SR_SHIFT                                  (18U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_SR_MASK                                   (0x001c0000U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_SR_SLOW                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_SR_FASTEST                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_SR_SLOWEST                                 (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_SR_FAST                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_WD_SHIFT                                  (16U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_WD_MASK                                   (0x00030000U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_WD_PU                                      (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_WD_KEEPER                                  (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_WD_NONE                                    (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7A_WD_PD                                      (2U)

#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_I_SHIFT                                   (13U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_I_MASK                                    (0x0000e000U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_I_0P73REXT                                 (6U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_I_0P88REXT                                 (4U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_I_1P33REXT                                 (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_I_REXT                                     (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_I_1P6REXT                                  (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_I_0P67REXT                                 (7U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_I_1P14REXT                                 (2U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_I_0P8REXT                                  (5U)

#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_SR_SHIFT                                  (10U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_SR_MASK                                   (0x00001c00U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_SR_SLOW                                    (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_SR_FASTEST                                 (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_SR_SLOWEST                                 (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_SR_FAST                                    (2U)

#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_WD_SHIFT                                  (8U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_WD_MASK                                   (0x00000300U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_WD_PU                                      (1U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_WD_KEEPER                                  (3U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_WD_NONE                                    (0U)
#define CTRL_CORE_CONTROL_DDRCH1_2_PART7B_WD_PD                                      (2U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP0_SHIFT                   (19U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP0_MASK                    (0x00080000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP0_ENABLE                   (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP0_DISABLE                  (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP1_SHIFT                   (18U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP1_MASK                    (0x00040000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP1_ENABLE                   (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_CCAP1_DISABLE                  (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP0_SHIFT                    (17U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP0_MASK                     (0x00020000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP0_ENABLE                    (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP0_DISABLE                   (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP1_SHIFT                    (16U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP1_MASK                     (0x00010000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP1_ENABLE                    (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_TAP1_DISABLE                   (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_EN_SHIFT                      (15U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_EN_MASK                       (0x00008000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_EN_ENABLE                      (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ0_INT_EN_DISABLE                     (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP0_SHIFT                   (14U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP0_MASK                    (0x00004000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP0_ENABLE                   (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP0_DISABLE                  (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP1_SHIFT                   (13U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP1_MASK                    (0x00002000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP1_ENABLE                   (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_CCAP1_DISABLE                  (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP0_SHIFT                    (12U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP0_MASK                     (0x00001000U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP0_ENABLE                    (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP0_DISABLE                   (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP1_SHIFT                    (11U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP1_MASK                     (0x00000800U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP1_ENABLE                    (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_TAP1_DISABLE                   (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_EN_SHIFT                      (10U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_EN_MASK                       (0x00000400U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_EN_ENABLE                      (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ1_INT_EN_DISABLE                     (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP0_SHIFT                   (9U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP0_MASK                    (0x00000200U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP0_ENABLE                   (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP0_DISABLE                  (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP1_SHIFT                   (8U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP1_MASK                    (0x00000100U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP1_ENABLE                   (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_CCAP1_DISABLE                  (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP0_SHIFT                    (7U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP0_MASK                     (0x00000080U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP0_ENABLE                    (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP0_DISABLE                   (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP1_SHIFT                    (6U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP1_MASK                     (0x00000040U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP1_ENABLE                    (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_TAP1_DISABLE                   (0U)

#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_EN_SHIFT                      (5U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_EN_MASK                       (0x00000020U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_EN_ENABLE                      (1U)
#define CTRL_CORE_CONTROL_DDRIO_0_DDRCH1_VREF_DQ2_INT_EN_DISABLE                     (0U)

#define CTRL_CORE_CONTROL_SPARE_RW_SHIFT                                            (0U)
#define CTRL_CORE_CONTROL_SPARE_RW_MASK                                             (0xffffffffU)

#define CTRL_CORE_CONTROL_SPARE_R_SHIFT                                             (0U)
#define CTRL_CORE_CONTROL_SPARE_R_MASK                                              (0xffffffffU)

#define CTRL_CORE_CONTROL_SPARE_R_C0_SHIFT                                          (31U)
#define CTRL_CORE_CONTROL_SPARE_R_C0_MASK                                           (0x80000000U)

#define CTRL_CORE_CONTROL_SPARE_R_C0_C1_SHIFT                                       (30U)
#define CTRL_CORE_CONTROL_SPARE_R_C0_C1_MASK                                        (0x40000000U)

#define CTRL_CORE_CONTROL_SPARE_R_C0_C2_SHIFT                                       (29U)
#define CTRL_CORE_CONTROL_SPARE_R_C0_C2_MASK                                        (0x20000000U)

#define CTRL_CORE_CONTROL_SPARE_R_C0_C3_SHIFT                                       (28U)
#define CTRL_CORE_CONTROL_SPARE_R_C0_C3_MASK                                        (0x10000000U)

#define CTRL_CORE_CONTROL_SPARE_R_C0_C4_SHIFT                                       (27U)
#define CTRL_CORE_CONTROL_SPARE_R_C0_C4_MASK                                        (0x08000000U)

#define CTRL_CORE_CONTROL_SPARE_R_C0_C5_SHIFT                                       (26U)
#define CTRL_CORE_CONTROL_SPARE_R_C0_C5_MASK                                        (0x04000000U)

#define CTRL_CORE_CONTROL_SPARE_R_C0_C6_SHIFT                                       (25U)
#define CTRL_CORE_CONTROL_SPARE_R_C0_C6_MASK                                        (0x02000000U)

#define CTRL_CORE_CONTROL_SPARE_R_C0_C7_SHIFT                                       (24U)
#define CTRL_CORE_CONTROL_SPARE_R_C0_C7_MASK                                        (0x01000000U)

#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_CCAP0_SHIFT                  (31U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_CCAP0_MASK                   (0x80000000U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_CCAP0_ENABLE                  (1U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_CCAP0_DISABLE                 (0U)

#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_CCAP1_SHIFT                  (30U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_CCAP1_MASK                   (0x40000000U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_CCAP1_ENABLE                  (1U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_CCAP1_DISABLE                 (0U)

#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_TAP0_SHIFT                   (29U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_TAP0_MASK                    (0x20000000U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_TAP0_ENABLE                   (1U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_TAP0_DISABLE                  (0U)

#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_TAP1_SHIFT                   (28U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_TAP1_MASK                    (0x10000000U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_TAP1_ENABLE                   (1U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_TAP1_DISABLE                  (0U)

#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_EN_SHIFT                     (27U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_EN_MASK                      (0x08000000U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_EN_ENABLE                     (1U)
#define CTRL_CORE_CONTROL_DDRIO_EXT_0_DDR3CH1_VREF_CA1_EN_DISABLE                    (0U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CTRL_CORE_PAD_H_ */

