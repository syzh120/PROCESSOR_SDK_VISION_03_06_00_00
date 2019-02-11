/*
 *  Copyright (C) 2008-2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_mpu_wugen.h
 *
 *  \brief  register-level header file for MPU
 *
**/

#ifndef HW_MPU_WUGEN_H_
#define HW_MPU_WUGEN_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define MPU_WKG_CONTROL_0                                                                                  (0x0U)
#define MPU_WKG_ENB_A_0                                                                                    (uint32_t)(0x10U)
#define MPU_WKG_ENB_B_0                                                                                    (0x14U)
#define MPU_WKG_ENB_C_0                                                                                    (0x18U)
#define MPU_WKG_ENB_D_0                                                                                    (0x1cU)
#define MPU_WKG_ENB_E_0                                                                                    (0x20U)
#define MPU_WKG_CONTROL_1                                                                                  (0x400U)
#define MPU_WKG_ENB_A_1                                                                                    (uint32_t)(0x410U)
#define MPU_WKG_ENB_B_1                                                                                    (0x414U)
#define MPU_WKG_ENB_C_1                                                                                    (0x418U)
#define MPU_WKG_ENB_D_1                                                                                    (0x41cU)
#define MPU_WKG_ENB_E_1                                                                                    (0x420U)
#define MPU_AUX_CORE_BOOT_0                                                                                (0x800U)
#define MPU_AUX_CORE_BOOT_1                                                                                (0x804U)
#define MPU_STM_HWEVENTS_INV                                                                               (0x808U)
#define MPU_AMBA_IF_MODE                                                                                   (0x80cU)
#define MPU_TIMESTAMPCYCLELO                                                                               (0xc08U)
#define MPU_TIMESTAMPCYCLEHI                                                                               (0xc0cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define MPU_WKG_CONTROL_0_RESERVED_SHIFT                                                                  (0U)
#define MPU_WKG_CONTROL_0_RESERVED_MASK                                                                   (0x000000ffU)

#define MPU_WKG_CONTROL_0_STANDBYWFI_SHIFT                                                                (8U)
#define MPU_WKG_CONTROL_0_STANDBYWFI_MASK                                                                 (0x00000100U)

#define MPU_WKG_CONTROL_0_STANDBYWFE_SHIFT                                                                (9U)
#define MPU_WKG_CONTROL_0_STANDBYWFE_MASK                                                                 (0x00000200U)

#define MPU_WKG_CONTROL_0_EVENTO_SHIFT                                                                    (10U)
#define MPU_WKG_CONTROL_0_EVENTO_MASK                                                                     (0x00000400U)

#define MPU_WKG_CONTROL_0_MPU_COLD_RESET_SHIFT                                                            (13U)
#define MPU_WKG_CONTROL_0_MPU_COLD_RESET_MASK                                                             (0x00002000U)

#define MPU_WKG_CONTROL_0_MPU_WARM_RESET_SHIFT                                                            (14U)
#define MPU_WKG_CONTROL_0_MPU_WARM_RESET_MASK                                                             (0x00004000U)

#define MPU_WKG_CONTROL_0_RESERVED3_SHIFT                                                                 (16U)
#define MPU_WKG_CONTROL_0_RESERVED3_MASK                                                                  (0xffff0000U)

#define MPU_WKG_CONTROL_0_RESERVED2_SHIFT                                                                 (11U)
#define MPU_WKG_CONTROL_0_RESERVED2_MASK                                                                  (0x00001800U)

#define MPU_WKG_CONTROL_0_DOMAINRESET_SHIFT                                                               (15U)
#define MPU_WKG_CONTROL_0_DOMAINRESET_MASK                                                                (0x00008000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR0_SHIFT                                                           (0U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR0_MASK                                                            (0x00000001U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR1_SHIFT                                                           (1U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR1_MASK                                                            (0x00000002U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR2_SHIFT                                                           (2U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR2_MASK                                                            (0x00000004U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR3_SHIFT                                                           (3U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR3_MASK                                                            (0x00000008U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR4_SHIFT                                                           (4U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR4_MASK                                                            (0x00000010U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR5_SHIFT                                                           (5U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR5_MASK                                                            (0x00000020U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR6_SHIFT                                                           (6U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR6_MASK                                                            (0x00000040U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR7_SHIFT                                                           (7U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR7_MASK                                                            (0x00000080U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR8_SHIFT                                                           (8U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR8_MASK                                                            (0x00000100U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR9_SHIFT                                                           (9U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR9_MASK                                                            (0x00000200U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR10_SHIFT                                                          (10U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR10_MASK                                                           (0x00000400U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR11_SHIFT                                                          (11U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR11_MASK                                                           (0x00000800U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR12_SHIFT                                                          (12U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR12_MASK                                                           (0x00001000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR13_SHIFT                                                          (13U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR13_MASK                                                           (0x00002000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR14_SHIFT                                                          (14U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR14_MASK                                                           (0x00004000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR15_SHIFT                                                          (15U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR15_MASK                                                           (0x00008000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR16_SHIFT                                                          (16U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR16_MASK                                                           (0x00010000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR17_SHIFT                                                          (17U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR17_MASK                                                           (0x00020000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR18_SHIFT                                                          (18U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR18_MASK                                                           (0x00040000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR19_SHIFT                                                          (19U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR19_MASK                                                           (0x00080000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR20_SHIFT                                                          (20U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR20_MASK                                                           (0x00100000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR21_SHIFT                                                          (21U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR21_MASK                                                           (0x00200000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR22_SHIFT                                                          (22U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR22_MASK                                                           (0x00400000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR23_SHIFT                                                          (23U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR23_MASK                                                           (0x00800000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR24_SHIFT                                                          (24U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR24_MASK                                                           (0x01000000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR25_SHIFT                                                          (25U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR25_MASK                                                           (0x02000000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR26_SHIFT                                                          (26U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR26_MASK                                                           (0x04000000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR27_SHIFT                                                          (27U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR27_MASK                                                           (0x08000000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR28_SHIFT                                                          (28U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR28_MASK                                                           (0x10000000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR29_SHIFT                                                          (29U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR29_MASK                                                           (0x20000000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR30_SHIFT                                                          (30U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR30_MASK                                                           (0x40000000U)

#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR31_SHIFT                                                          (31U)
#define MPU_WKG_ENB_A_0_WKG_ENB_FOR_INTR31_MASK                                                           (0x80000000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR32_SHIFT                                                          (0U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR32_MASK                                                           (0x00000001U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR33_SHIFT                                                          (1U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR33_MASK                                                           (0x00000002U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR34_SHIFT                                                          (2U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR34_MASK                                                           (0x00000004U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR35_SHIFT                                                          (3U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR35_MASK                                                           (0x00000008U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR36_SHIFT                                                          (4U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR36_MASK                                                           (0x00000010U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR37_SHIFT                                                          (5U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR37_MASK                                                           (0x00000020U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR38_SHIFT                                                          (6U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR38_MASK                                                           (0x00000040U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR39_SHIFT                                                          (7U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR39_MASK                                                           (0x00000080U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR40_SHIFT                                                          (8U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR40_MASK                                                           (0x00000100U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR41_SHIFT                                                          (9U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR41_MASK                                                           (0x00000200U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR42_SHIFT                                                          (10U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR42_MASK                                                           (0x00000400U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR43_SHIFT                                                          (11U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR43_MASK                                                           (0x00000800U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR44_SHIFT                                                          (12U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR44_MASK                                                           (0x00001000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR45_SHIFT                                                          (13U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR45_MASK                                                           (0x00002000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR46_SHIFT                                                          (14U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR46_MASK                                                           (0x00004000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR47_SHIFT                                                          (15U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR47_MASK                                                           (0x00008000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR48_SHIFT                                                          (16U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR48_MASK                                                           (0x00010000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR49_SHIFT                                                          (17U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR49_MASK                                                           (0x00020000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR50_SHIFT                                                          (18U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR50_MASK                                                           (0x00040000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR51_SHIFT                                                          (19U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR51_MASK                                                           (0x00080000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR52_SHIFT                                                          (20U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR52_MASK                                                           (0x00100000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR53_SHIFT                                                          (21U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR53_MASK                                                           (0x00200000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR54_SHIFT                                                          (22U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR54_MASK                                                           (0x00400000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR55_SHIFT                                                          (23U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR55_MASK                                                           (0x00800000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR56_SHIFT                                                          (24U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR56_MASK                                                           (0x01000000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR57_SHIFT                                                          (25U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR57_MASK                                                           (0x02000000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR58_SHIFT                                                          (26U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR58_MASK                                                           (0x04000000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR59_SHIFT                                                          (27U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR59_MASK                                                           (0x08000000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR60_SHIFT                                                          (28U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR60_MASK                                                           (0x10000000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR61_SHIFT                                                          (29U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR61_MASK                                                           (0x20000000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR62_SHIFT                                                          (30U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR62_MASK                                                           (0x40000000U)

#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR63_SHIFT                                                          (31U)
#define MPU_WKG_ENB_B_0_WKG_ENB_FOR_INTR63_MASK                                                           (0x80000000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR64_SHIFT                                                          (0U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR64_MASK                                                           (0x00000001U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR65_SHIFT                                                          (1U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR65_MASK                                                           (0x00000002U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR66_SHIFT                                                          (2U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR66_MASK                                                           (0x00000004U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR67_SHIFT                                                          (3U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR67_MASK                                                           (0x00000008U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR68_SHIFT                                                          (4U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR68_MASK                                                           (0x00000010U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR69_SHIFT                                                          (5U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR69_MASK                                                           (0x00000020U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR70_SHIFT                                                          (6U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR70_MASK                                                           (0x00000040U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR71_SHIFT                                                          (7U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR71_MASK                                                           (0x00000080U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR72_SHIFT                                                          (8U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR72_MASK                                                           (0x00000100U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR73_SHIFT                                                          (9U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR73_MASK                                                           (0x00000200U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR74_SHIFT                                                          (10U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR74_MASK                                                           (0x00000400U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR75_SHIFT                                                          (11U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR75_MASK                                                           (0x00000800U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR76_SHIFT                                                          (12U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR76_MASK                                                           (0x00001000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR77_SHIFT                                                          (13U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR77_MASK                                                           (0x00002000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR78_SHIFT                                                          (14U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR78_MASK                                                           (0x00004000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR79_SHIFT                                                          (15U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR79_MASK                                                           (0x00008000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR80_SHIFT                                                          (16U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR80_MASK                                                           (0x00010000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR81_SHIFT                                                          (17U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR81_MASK                                                           (0x00020000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR82_SHIFT                                                          (18U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR82_MASK                                                           (0x00040000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR83_SHIFT                                                          (19U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR83_MASK                                                           (0x00080000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR84_SHIFT                                                          (20U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR84_MASK                                                           (0x00100000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR85_SHIFT                                                          (21U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR85_MASK                                                           (0x00200000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR86_SHIFT                                                          (22U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR86_MASK                                                           (0x00400000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR87_SHIFT                                                          (23U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR87_MASK                                                           (0x00800000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR88_SHIFT                                                          (24U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR88_MASK                                                           (0x01000000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR89_SHIFT                                                          (25U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR89_MASK                                                           (0x02000000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR90_SHIFT                                                          (26U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR90_MASK                                                           (0x04000000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR91_SHIFT                                                          (27U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR91_MASK                                                           (0x08000000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR92_SHIFT                                                          (28U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR92_MASK                                                           (0x10000000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR93_SHIFT                                                          (29U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR93_MASK                                                           (0x20000000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR94_SHIFT                                                          (30U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR94_MASK                                                           (0x40000000U)

#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR95_SHIFT                                                          (31U)
#define MPU_WKG_ENB_C_0_WKG_ENB_FOR_INTR95_MASK                                                           (0x80000000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR96_SHIFT                                                          (0U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR96_MASK                                                           (0x00000001U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR97_SHIFT                                                          (1U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR97_MASK                                                           (0x00000002U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR98_SHIFT                                                          (2U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR98_MASK                                                           (0x00000004U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR99_SHIFT                                                          (3U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR99_MASK                                                           (0x00000008U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR100_SHIFT                                                         (4U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR100_MASK                                                          (0x00000010U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR101_SHIFT                                                         (5U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR101_MASK                                                          (0x00000020U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR102_SHIFT                                                         (6U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR102_MASK                                                          (0x00000040U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR103_SHIFT                                                         (7U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR103_MASK                                                          (0x00000080U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR104_SHIFT                                                         (8U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR104_MASK                                                          (0x00000100U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR105_SHIFT                                                         (9U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR105_MASK                                                          (0x00000200U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR106_SHIFT                                                         (10U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR106_MASK                                                          (0x00000400U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR107_SHIFT                                                         (11U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR107_MASK                                                          (0x00000800U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR108_SHIFT                                                         (12U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR108_MASK                                                          (0x00001000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR109_SHIFT                                                         (13U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR109_MASK                                                          (0x00002000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR110_SHIFT                                                         (14U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR110_MASK                                                          (0x00004000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR111_SHIFT                                                         (15U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR111_MASK                                                          (0x00008000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR112_SHIFT                                                         (16U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR112_MASK                                                          (0x00010000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR113_SHIFT                                                         (17U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR113_MASK                                                          (0x00020000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR114_SHIFT                                                         (18U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR114_MASK                                                          (0x00040000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR115_SHIFT                                                         (19U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR115_MASK                                                          (0x00080000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR116_SHIFT                                                         (20U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR116_MASK                                                          (0x00100000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR117_SHIFT                                                         (21U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR117_MASK                                                          (0x00200000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR118_SHIFT                                                         (22U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR118_MASK                                                          (0x00400000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR119_SHIFT                                                         (23U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR119_MASK                                                          (0x00800000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR120_SHIFT                                                         (24U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR120_MASK                                                          (0x01000000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR121_SHIFT                                                         (25U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR121_MASK                                                          (0x02000000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR122_SHIFT                                                         (26U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR122_MASK                                                          (0x04000000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR123_SHIFT                                                         (27U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR123_MASK                                                          (0x08000000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR124_SHIFT                                                         (28U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR124_MASK                                                          (0x10000000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR125_SHIFT                                                         (29U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR125_MASK                                                          (0x20000000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR126_SHIFT                                                         (30U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR126_MASK                                                          (0x40000000U)

#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR127_SHIFT                                                         (31U)
#define MPU_WKG_ENB_D_0_WKG_ENB_FOR_INTR127_MASK                                                          (0x80000000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR128_SHIFT                                                         (0U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR128_MASK                                                          (0x00000001U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR129_SHIFT                                                         (1U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR129_MASK                                                          (0x00000002U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR130_SHIFT                                                         (2U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR130_MASK                                                          (0x00000004U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR131_SHIFT                                                         (3U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR131_MASK                                                          (0x00000008U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR132_SHIFT                                                         (4U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR132_MASK                                                          (0x00000010U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR133_SHIFT                                                         (5U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR133_MASK                                                          (0x00000020U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR134_SHIFT                                                         (6U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR134_MASK                                                          (0x00000040U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR135_SHIFT                                                         (7U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR135_MASK                                                          (0x00000080U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR136_SHIFT                                                         (8U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR136_MASK                                                          (0x00000100U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR137_SHIFT                                                         (9U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR137_MASK                                                          (0x00000200U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR138_SHIFT                                                         (10U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR138_MASK                                                          (0x00000400U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR139_SHIFT                                                         (11U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR139_MASK                                                          (0x00000800U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR140_SHIFT                                                         (12U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR140_MASK                                                          (0x00001000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR141_SHIFT                                                         (13U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR141_MASK                                                          (0x00002000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR142_SHIFT                                                         (14U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR142_MASK                                                          (0x00004000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR143_SHIFT                                                         (15U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR143_MASK                                                          (0x00008000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR144_SHIFT                                                         (16U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR144_MASK                                                          (0x00010000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR145_SHIFT                                                         (17U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR145_MASK                                                          (0x00020000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR146_SHIFT                                                         (18U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR146_MASK                                                          (0x00040000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR147_SHIFT                                                         (19U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR147_MASK                                                          (0x00080000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR148_SHIFT                                                         (20U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR148_MASK                                                          (0x00100000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR149_SHIFT                                                         (21U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR149_MASK                                                          (0x00200000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR150_SHIFT                                                         (22U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR150_MASK                                                          (0x00400000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR151_SHIFT                                                         (23U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR151_MASK                                                          (0x00800000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR152_SHIFT                                                         (24U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR152_MASK                                                          (0x01000000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR153_SHIFT                                                         (25U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR153_MASK                                                          (0x02000000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR154_SHIFT                                                         (26U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR154_MASK                                                          (0x04000000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR155_SHIFT                                                         (27U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR155_MASK                                                          (0x08000000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR156_SHIFT                                                         (28U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR156_MASK                                                          (0x10000000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR157_SHIFT                                                         (29U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR157_MASK                                                          (0x20000000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR158_SHIFT                                                         (30U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR158_MASK                                                          (0x40000000U)

#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR159_SHIFT                                                         (31U)
#define MPU_WKG_ENB_E_0_WKG_ENB_FOR_INTR159_MASK                                                          (0x80000000U)

#define MPU_WKG_CONTROL_1_RESERVED_SHIFT                                                                  (0U)
#define MPU_WKG_CONTROL_1_RESERVED_MASK                                                                   (0x000000ffU)

#define MPU_WKG_CONTROL_1_STANDBYWFI_SHIFT                                                                (8U)
#define MPU_WKG_CONTROL_1_STANDBYWFI_MASK                                                                 (0x00000100U)

#define MPU_WKG_CONTROL_1_STANDBYWFE_SHIFT                                                                (9U)
#define MPU_WKG_CONTROL_1_STANDBYWFE_MASK                                                                 (0x00000200U)

#define MPU_WKG_CONTROL_1_EVENTO_SHIFT                                                                    (10U)
#define MPU_WKG_CONTROL_1_EVENTO_MASK                                                                     (0x00000400U)

#define MPU_WKG_CONTROL_1_MPU_COLD_RESET_SHIFT                                                            (13U)
#define MPU_WKG_CONTROL_1_MPU_COLD_RESET_MASK                                                             (0x00002000U)

#define MPU_WKG_CONTROL_1_MPU_WARM_RESET_SHIFT                                                            (14U)
#define MPU_WKG_CONTROL_1_MPU_WARM_RESET_MASK                                                             (0x00004000U)

#define MPU_WKG_CONTROL_1_RESERVED3_SHIFT                                                                 (16U)
#define MPU_WKG_CONTROL_1_RESERVED3_MASK                                                                  (0xffff0000U)

#define MPU_WKG_CONTROL_1_RESERVED2_SHIFT                                                                 (11U)
#define MPU_WKG_CONTROL_1_RESERVED2_MASK                                                                  (0x00001800U)

#define MPU_WKG_CONTROL_1_DOMAINRESET_SHIFT                                                               (15U)
#define MPU_WKG_CONTROL_1_DOMAINRESET_MASK                                                                (0x00008000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR0_SHIFT                                                           (0U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR0_MASK                                                            (0x00000001U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR1_SHIFT                                                           (1U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR1_MASK                                                            (0x00000002U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR2_SHIFT                                                           (2U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR2_MASK                                                            (0x00000004U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR3_SHIFT                                                           (3U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR3_MASK                                                            (0x00000008U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR4_SHIFT                                                           (4U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR4_MASK                                                            (0x00000010U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR5_SHIFT                                                           (5U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR5_MASK                                                            (0x00000020U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR6_SHIFT                                                           (6U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR6_MASK                                                            (0x00000040U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR7_SHIFT                                                           (7U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR7_MASK                                                            (0x00000080U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR8_SHIFT                                                           (8U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR8_MASK                                                            (0x00000100U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR9_SHIFT                                                           (9U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR9_MASK                                                            (0x00000200U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR10_SHIFT                                                          (10U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR10_MASK                                                           (0x00000400U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR11_SHIFT                                                          (11U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR11_MASK                                                           (0x00000800U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR12_SHIFT                                                          (12U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR12_MASK                                                           (0x00001000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR13_SHIFT                                                          (13U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR13_MASK                                                           (0x00002000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR14_SHIFT                                                          (14U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR14_MASK                                                           (0x00004000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR15_SHIFT                                                          (15U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR15_MASK                                                           (0x00008000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR16_SHIFT                                                          (16U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR16_MASK                                                           (0x00010000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR17_SHIFT                                                          (17U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR17_MASK                                                           (0x00020000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR18_SHIFT                                                          (18U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR18_MASK                                                           (0x00040000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR19_SHIFT                                                          (19U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR19_MASK                                                           (0x00080000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR20_SHIFT                                                          (20U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR20_MASK                                                           (0x00100000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR21_SHIFT                                                          (21U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR21_MASK                                                           (0x00200000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR22_SHIFT                                                          (22U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR22_MASK                                                           (0x00400000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR23_SHIFT                                                          (23U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR23_MASK                                                           (0x00800000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR24_SHIFT                                                          (24U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR24_MASK                                                           (0x01000000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR25_SHIFT                                                          (25U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR25_MASK                                                           (0x02000000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR26_SHIFT                                                          (26U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR26_MASK                                                           (0x04000000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR27_SHIFT                                                          (27U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR27_MASK                                                           (0x08000000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR28_SHIFT                                                          (28U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR28_MASK                                                           (0x10000000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR29_SHIFT                                                          (29U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR29_MASK                                                           (0x20000000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR30_SHIFT                                                          (30U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR30_MASK                                                           (0x40000000U)

#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR31_SHIFT                                                          (31U)
#define MPU_WKG_ENB_A_1_WKG_ENB_FOR_INTR31_MASK                                                           (0x80000000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR32_SHIFT                                                          (0U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR32_MASK                                                           (0x00000001U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR33_SHIFT                                                          (1U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR33_MASK                                                           (0x00000002U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR34_SHIFT                                                          (2U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR34_MASK                                                           (0x00000004U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR35_SHIFT                                                          (3U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR35_MASK                                                           (0x00000008U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR36_SHIFT                                                          (4U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR36_MASK                                                           (0x00000010U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR37_SHIFT                                                          (5U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR37_MASK                                                           (0x00000020U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR38_SHIFT                                                          (6U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR38_MASK                                                           (0x00000040U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR39_SHIFT                                                          (7U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR39_MASK                                                           (0x00000080U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR40_SHIFT                                                          (8U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR40_MASK                                                           (0x00000100U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR41_SHIFT                                                          (9U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR41_MASK                                                           (0x00000200U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR42_SHIFT                                                          (10U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR42_MASK                                                           (0x00000400U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR43_SHIFT                                                          (11U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR43_MASK                                                           (0x00000800U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR44_SHIFT                                                          (12U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR44_MASK                                                           (0x00001000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR45_SHIFT                                                          (13U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR45_MASK                                                           (0x00002000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR46_SHIFT                                                          (14U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR46_MASK                                                           (0x00004000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR47_SHIFT                                                          (15U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR47_MASK                                                           (0x00008000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR48_SHIFT                                                          (16U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR48_MASK                                                           (0x00010000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR49_SHIFT                                                          (17U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR49_MASK                                                           (0x00020000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR50_SHIFT                                                          (18U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR50_MASK                                                           (0x00040000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR51_SHIFT                                                          (19U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR51_MASK                                                           (0x00080000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR52_SHIFT                                                          (20U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR52_MASK                                                           (0x00100000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR53_SHIFT                                                          (21U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR53_MASK                                                           (0x00200000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR54_SHIFT                                                          (22U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR54_MASK                                                           (0x00400000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR55_SHIFT                                                          (23U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR55_MASK                                                           (0x00800000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR56_SHIFT                                                          (24U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR56_MASK                                                           (0x01000000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR57_SHIFT                                                          (25U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR57_MASK                                                           (0x02000000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR58_SHIFT                                                          (26U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR58_MASK                                                           (0x04000000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR59_SHIFT                                                          (27U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR59_MASK                                                           (0x08000000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR60_SHIFT                                                          (28U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR60_MASK                                                           (0x10000000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR61_SHIFT                                                          (29U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR61_MASK                                                           (0x20000000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR62_SHIFT                                                          (30U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR62_MASK                                                           (0x40000000U)

#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR63_SHIFT                                                          (31U)
#define MPU_WKG_ENB_B_1_WKG_ENB_FOR_INTR63_MASK                                                           (0x80000000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR64_SHIFT                                                          (0U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR64_MASK                                                           (0x00000001U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR65_SHIFT                                                          (1U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR65_MASK                                                           (0x00000002U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR66_SHIFT                                                          (2U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR66_MASK                                                           (0x00000004U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR67_SHIFT                                                          (3U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR67_MASK                                                           (0x00000008U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR68_SHIFT                                                          (4U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR68_MASK                                                           (0x00000010U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR69_SHIFT                                                          (5U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR69_MASK                                                           (0x00000020U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR70_SHIFT                                                          (6U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR70_MASK                                                           (0x00000040U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR71_SHIFT                                                          (7U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR71_MASK                                                           (0x00000080U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR72_SHIFT                                                          (8U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR72_MASK                                                           (0x00000100U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR73_SHIFT                                                          (9U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR73_MASK                                                           (0x00000200U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR74_SHIFT                                                          (10U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR74_MASK                                                           (0x00000400U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR75_SHIFT                                                          (11U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR75_MASK                                                           (0x00000800U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR76_SHIFT                                                          (12U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR76_MASK                                                           (0x00001000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR77_SHIFT                                                          (13U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR77_MASK                                                           (0x00002000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR78_SHIFT                                                          (14U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR78_MASK                                                           (0x00004000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR79_SHIFT                                                          (15U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR79_MASK                                                           (0x00008000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR80_SHIFT                                                          (16U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR80_MASK                                                           (0x00010000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR81_SHIFT                                                          (17U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR81_MASK                                                           (0x00020000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR82_SHIFT                                                          (18U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR82_MASK                                                           (0x00040000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR83_SHIFT                                                          (19U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR83_MASK                                                           (0x00080000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR84_SHIFT                                                          (20U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR84_MASK                                                           (0x00100000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR85_SHIFT                                                          (21U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR85_MASK                                                           (0x00200000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR86_SHIFT                                                          (22U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR86_MASK                                                           (0x00400000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR87_SHIFT                                                          (23U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR87_MASK                                                           (0x00800000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR88_SHIFT                                                          (24U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR88_MASK                                                           (0x01000000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR89_SHIFT                                                          (25U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR89_MASK                                                           (0x02000000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR90_SHIFT                                                          (26U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR90_MASK                                                           (0x04000000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR91_SHIFT                                                          (27U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR91_MASK                                                           (0x08000000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR92_SHIFT                                                          (28U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR92_MASK                                                           (0x10000000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR93_SHIFT                                                          (29U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR93_MASK                                                           (0x20000000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR94_SHIFT                                                          (30U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR94_MASK                                                           (0x40000000U)

#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR95_SHIFT                                                          (31U)
#define MPU_WKG_ENB_C_1_WKG_ENB_FOR_INTR95_MASK                                                           (0x80000000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR96_SHIFT                                                          (0U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR96_MASK                                                           (0x00000001U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR97_SHIFT                                                          (1U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR97_MASK                                                           (0x00000002U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR98_SHIFT                                                          (2U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR98_MASK                                                           (0x00000004U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR99_SHIFT                                                          (3U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR99_MASK                                                           (0x00000008U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR100_SHIFT                                                         (4U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR100_MASK                                                          (0x00000010U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR101_SHIFT                                                         (5U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR101_MASK                                                          (0x00000020U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR102_SHIFT                                                         (6U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR102_MASK                                                          (0x00000040U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR103_SHIFT                                                         (7U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR103_MASK                                                          (0x00000080U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR104_SHIFT                                                         (8U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR104_MASK                                                          (0x00000100U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR105_SHIFT                                                         (9U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR105_MASK                                                          (0x00000200U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR106_SHIFT                                                         (10U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR106_MASK                                                          (0x00000400U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR107_SHIFT                                                         (11U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR107_MASK                                                          (0x00000800U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR108_SHIFT                                                         (12U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR108_MASK                                                          (0x00001000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR109_SHIFT                                                         (13U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR109_MASK                                                          (0x00002000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR110_SHIFT                                                         (14U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR110_MASK                                                          (0x00004000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR111_SHIFT                                                         (15U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR111_MASK                                                          (0x00008000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR112_SHIFT                                                         (16U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR112_MASK                                                          (0x00010000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR113_SHIFT                                                         (17U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR113_MASK                                                          (0x00020000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR114_SHIFT                                                         (18U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR114_MASK                                                          (0x00040000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR115_SHIFT                                                         (19U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR115_MASK                                                          (0x00080000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR116_SHIFT                                                         (20U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR116_MASK                                                          (0x00100000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR117_SHIFT                                                         (21U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR117_MASK                                                          (0x00200000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR118_SHIFT                                                         (22U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR118_MASK                                                          (0x00400000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR119_SHIFT                                                         (23U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR119_MASK                                                          (0x00800000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR120_SHIFT                                                         (24U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR120_MASK                                                          (0x01000000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR121_SHIFT                                                         (25U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR121_MASK                                                          (0x02000000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR122_SHIFT                                                         (26U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR122_MASK                                                          (0x04000000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR123_SHIFT                                                         (27U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR123_MASK                                                          (0x08000000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR124_SHIFT                                                         (28U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR124_MASK                                                          (0x10000000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR125_SHIFT                                                         (29U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR125_MASK                                                          (0x20000000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR126_SHIFT                                                         (30U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR126_MASK                                                          (0x40000000U)

#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR127_SHIFT                                                         (31U)
#define MPU_WKG_ENB_D_1_WKG_ENB_FOR_INTR127_MASK                                                          (0x80000000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR128_SHIFT                                                         (0U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR128_MASK                                                          (0x00000001U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR129_SHIFT                                                         (1U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR129_MASK                                                          (0x00000002U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR130_SHIFT                                                         (2U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR130_MASK                                                          (0x00000004U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR131_SHIFT                                                         (3U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR131_MASK                                                          (0x00000008U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR132_SHIFT                                                         (4U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR132_MASK                                                          (0x00000010U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR133_SHIFT                                                         (5U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR133_MASK                                                          (0x00000020U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR134_SHIFT                                                         (6U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR134_MASK                                                          (0x00000040U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR135_SHIFT                                                         (7U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR135_MASK                                                          (0x00000080U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR136_SHIFT                                                         (8U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR136_MASK                                                          (0x00000100U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR137_SHIFT                                                         (9U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR137_MASK                                                          (0x00000200U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR138_SHIFT                                                         (10U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR138_MASK                                                          (0x00000400U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR139_SHIFT                                                         (11U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR139_MASK                                                          (0x00000800U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR140_SHIFT                                                         (12U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR140_MASK                                                          (0x00001000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR141_SHIFT                                                         (13U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR141_MASK                                                          (0x00002000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR142_SHIFT                                                         (14U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR142_MASK                                                          (0x00004000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR143_SHIFT                                                         (15U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR143_MASK                                                          (0x00008000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR144_SHIFT                                                         (16U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR144_MASK                                                          (0x00010000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR145_SHIFT                                                         (17U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR145_MASK                                                          (0x00020000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR146_SHIFT                                                         (18U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR146_MASK                                                          (0x00040000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR147_SHIFT                                                         (19U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR147_MASK                                                          (0x00080000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR148_SHIFT                                                         (20U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR148_MASK                                                          (0x00100000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR149_SHIFT                                                         (21U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR149_MASK                                                          (0x00200000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR150_SHIFT                                                         (22U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR150_MASK                                                          (0x00400000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR151_SHIFT                                                         (23U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR151_MASK                                                          (0x00800000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR152_SHIFT                                                         (24U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR152_MASK                                                          (0x01000000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR153_SHIFT                                                         (25U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR153_MASK                                                          (0x02000000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR154_SHIFT                                                         (26U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR154_MASK                                                          (0x04000000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR155_SHIFT                                                         (27U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR155_MASK                                                          (0x08000000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR156_SHIFT                                                         (28U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR156_MASK                                                          (0x10000000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR157_SHIFT                                                         (29U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR157_MASK                                                          (0x20000000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR158_SHIFT                                                         (30U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR158_MASK                                                          (0x40000000U)

#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR159_SHIFT                                                         (31U)
#define MPU_WKG_ENB_E_1_WKG_ENB_FOR_INTR159_MASK                                                          (0x80000000U)

#define MPU_AUX_CORE_BOOT_0_AUX_CORE_BOOT_0_SHIFT                                                         (0U)
#define MPU_AUX_CORE_BOOT_0_AUX_CORE_BOOT_0_MASK                                                          (0xffffffffU)

#define MPU_AUX_CORE_BOOT_1_AUX_CORE_BOOT_1_SHIFT                                                         (0U)
#define MPU_AUX_CORE_BOOT_1_AUX_CORE_BOOT_1_MASK                                                          (0xffffffffU)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_0_SHIFT                                                      (0U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_0_MASK                                                       (0x00000001U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_1_SHIFT                                                      (1U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_1_MASK                                                       (0x00000002U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_2_SHIFT                                                      (2U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_2_MASK                                                       (0x00000004U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_3_SHIFT                                                      (3U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_3_MASK                                                       (0x00000008U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_4_SHIFT                                                      (4U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_4_MASK                                                       (0x00000010U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_5_SHIFT                                                      (5U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_5_MASK                                                       (0x00000020U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_6_SHIFT                                                      (6U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_6_MASK                                                       (0x00000040U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_7_SHIFT                                                      (7U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_7_MASK                                                       (0x00000080U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_8_SHIFT                                                      (8U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_8_MASK                                                       (0x00000100U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_9_SHIFT                                                      (9U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_9_MASK                                                       (0x00000200U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_10_SHIFT                                                     (10U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_10_MASK                                                      (0x00000400U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_11_SHIFT                                                     (11U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_11_MASK                                                      (0x00000800U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_12_SHIFT                                                     (12U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_12_MASK                                                      (0x00001000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_13_SHIFT                                                     (13U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_13_MASK                                                      (0x00002000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_14_SHIFT                                                     (14U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_14_MASK                                                      (0x00004000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_15_SHIFT                                                     (15U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_15_MASK                                                      (0x00008000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_16_SHIFT                                                     (16U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_16_MASK                                                      (0x00010000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_17_SHIFT                                                     (17U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_17_MASK                                                      (0x00020000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_18_SHIFT                                                     (18U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_18_MASK                                                      (0x00040000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_19_SHIFT                                                     (19U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_19_MASK                                                      (0x00080000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_20_SHIFT                                                     (20U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_20_MASK                                                      (0x00100000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_21_SHIFT                                                     (21U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_21_MASK                                                      (0x00200000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_22_SHIFT                                                     (22U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_22_MASK                                                      (0x00400000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_23_SHIFT                                                     (23U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_23_MASK                                                      (0x00800000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_24_SHIFT                                                     (24U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_24_MASK                                                      (0x01000000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_25_SHIFT                                                     (25U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_25_MASK                                                      (0x02000000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_26_SHIFT                                                     (26U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_26_MASK                                                      (0x04000000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_27_SHIFT                                                     (27U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_27_MASK                                                      (0x08000000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_28_SHIFT                                                     (28U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_28_MASK                                                      (0x10000000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_29_SHIFT                                                     (29U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_29_MASK                                                      (0x20000000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_30_SHIFT                                                     (30U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_30_MASK                                                      (0x40000000U)

#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_31_SHIFT                                                     (31U)
#define MPU_STM_HWEVENTS_INV_STM_HWEVENT_INV_31_MASK                                                      (0x80000000U)

#define MPU_AMBA_IF_MODE_SBD_SHIFT                                                                        (0U)
#define MPU_AMBA_IF_MODE_SBD_MASK                                                                         (0x00000001U)

#define MPU_AMBA_IF_MODE_BCM_SHIFT                                                                        (1U)
#define MPU_AMBA_IF_MODE_BCM_MASK                                                                         (0x00000002U)

#define MPU_AMBA_IF_MODE_BO_SHIFT                                                                         (2U)
#define MPU_AMBA_IF_MODE_BO_MASK                                                                          (0x00000004U)

#define MPU_AMBA_IF_MODE_BI_SHIFT                                                                         (3U)
#define MPU_AMBA_IF_MODE_BI_MASK                                                                          (0x00000008U)

#define MPU_AMBA_IF_MODE_APB_FENCE_EN_SHIFT                                                               (4U)
#define MPU_AMBA_IF_MODE_APB_FENCE_EN_MASK                                                                (0x00000010U)

#define MPU_AMBA_IF_MODE_RESERVED_SHIFT                                                                   (6U)
#define MPU_AMBA_IF_MODE_RESERVED_MASK                                                                    (0xffffffc0U)

#define MPU_AMBA_IF_MODE_ES2_PM_MODE_SHIFT                                                                (5U)
#define MPU_AMBA_IF_MODE_ES2_PM_MODE_MASK                                                                 (0x00000020U)

#define MPU_TIMESTAMPCYCLELO_COUNTER_31_0_SHIFT                                                           (0U)
#define MPU_TIMESTAMPCYCLELO_COUNTER_31_0_MASK                                                            (0xffffffffU)

#define MPU_TIMESTAMPCYCLEHI_COUNTER_47_32_SHIFT                                                          (0U)
#define MPU_TIMESTAMPCYCLEHI_COUNTER_47_32_MASK                                                           (0x0000ffffU)

#define MPU_TIMESTAMPCYCLEHI_RESERVED_SHIFT                                                               (16U)
#define MPU_TIMESTAMPCYCLEHI_RESERVED_MASK                                                                (0xffff0000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_WUGEN_H_ */
