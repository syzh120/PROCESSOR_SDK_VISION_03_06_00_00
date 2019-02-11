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
 *  \file   hw_mpu_prcm_device.h
 *
 *  \brief  Register-level header file for MPU
 *
**/

#ifndef HW_MPU_PRCM_DEVICE_H_
#define HW_MPU_PRCM_DEVICE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define MPU_PRM_RSTST                                                                                      (0x0U)
#define MPU_PRM_PSCON_COUNT                                                                                (0x4U)
#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR                                                                 (0x10U)
#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD                                                        (0x14U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define MPU_PRM_RSTST_GLOBAL_COLD_RST_SHIFT                                                               (0U)
#define MPU_PRM_RSTST_GLOBAL_COLD_RST_MASK                                                                (0x00000001U)
#define MPU_PRM_RSTST_GLOBAL_COLD_RST_0X0                                                                 (0U)
#define MPU_PRM_RSTST_GLOBAL_COLD_RST_0X1                                                                 (1U)

#define MPU_PRM_RSTST_GLOBAL_WARM_RST_SHIFT                                                               (1U)
#define MPU_PRM_RSTST_GLOBAL_WARM_RST_MASK                                                                (0x00000002U)
#define MPU_PRM_RSTST_GLOBAL_WARM_RST_0X0                                                                 (0U)
#define MPU_PRM_RSTST_GLOBAL_WARM_RST_0X1                                                                 (1U)

#define MPU_PRM_RSTST_RESERVED_SHIFT                                                                      (2U)
#define MPU_PRM_RSTST_RESERVED_MASK                                                                       (0xfffffffcU)

#define MPU_PRM_PSCON_COUNT_PCHARGE_TIME_SHIFT                                                            (0U)
#define MPU_PRM_PSCON_COUNT_PCHARGE_TIME_MASK                                                             (0x000000ffU)

#define MPU_PRM_PSCON_COUNT_RESERVED_SHIFT                                                                (8U)
#define MPU_PRM_PSCON_COUNT_RESERVED_MASK                                                                 (0x0000ff00U)

#define MPU_PRM_PSCON_COUNT_RESERVED1_SHIFT                                                               (26U)
#define MPU_PRM_PSCON_COUNT_RESERVED1_MASK                                                                (0xfc000000U)

#define MPU_PRM_PSCON_COUNT_HG_PONOUT_2_PGDOODIN_TIME_SHIFT                                               (16U)
#define MPU_PRM_PSCON_COUNT_HG_PONOUT_2_PGDOODIN_TIME_MASK                                                (0x00ff0000U)

#define MPU_PRM_PSCON_COUNT_HG_RAMPUP_SHIFT                                                               (25U)
#define MPU_PRM_PSCON_COUNT_HG_RAMPUP_MASK                                                                (0x02000000U)
#define MPU_PRM_PSCON_COUNT_HG_RAMPUP_SLOW                                                                (0U)
#define MPU_PRM_PSCON_COUNT_HG_RAMPUP_FAST                                                                (1U)

#define MPU_PRM_PSCON_COUNT_HG_EN_SHIFT                                                                   (24U)
#define MPU_PRM_PSCON_COUNT_HG_EN_MASK                                                                    (0x01000000U)
#define MPU_PRM_PSCON_COUNT_HG_EN_HG_DISABLE                                                              (0U)
#define MPU_PRM_PSCON_COUNT_HG_EN_HG_ENABLE                                                               (1U)

#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_SYS_MODE_NUMERATOR_SHIFT                                       (0U)
#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_SYS_MODE_NUMERATOR_MASK                                        (0x00000fffU)

#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_RESERVED_SHIFT                                                 (12U)
#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_RESERVED_MASK                                                  (0x0000f000U)

#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_RESERVED1_SHIFT                                                (28U)
#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_RESERVED1_MASK                                                 (0xf0000000U)

#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_ABE_LP_MODE_NUMERATOR_SHIFT                                    (16U)
#define MPU_PRM_FRAC_INCREMENTER_NUMERATOR_ABE_LP_MODE_NUMERATOR_MASK                                     (0x0fff0000U)

#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_DENOMINATOR_SHIFT                                     (0U)
#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_DENOMINATOR_MASK                                      (0x00000fffU)

#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RESERVED_SHIFT                                        (12U)
#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RESERVED_MASK                                         (0x0000f000U)

#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RESERVED1_SHIFT                                       (17U)
#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RESERVED1_MASK                                        (0xfffe0000U)

#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RELOAD_SHIFT                                          (16U)
#define MPU_PRM_FRAC_INCREMENTER_DENUMERATOR_RELOAD_RELOAD_MASK                                           (0x00010000U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_MPU_PRCM_DEVICE_H_ */
