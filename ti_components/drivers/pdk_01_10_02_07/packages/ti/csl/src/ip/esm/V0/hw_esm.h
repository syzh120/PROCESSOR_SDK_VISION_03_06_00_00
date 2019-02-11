/*
 *  Copyright (c) Texas Instruments Incorporated 2015
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

#ifndef HW_ESM_H_
#define HW_ESM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define ESM_ESMIEPSR1                                               (0x0U)
#define ESM_ESMIEPCR1                                               (0x4U)
#define ESM_ESMIESR1                                                (0x8U)
#define ESM_ESMIECR1                                                (0xcU)
#define ESM_ESMILSR1                                                (0x10U)
#define ESM_ESMILCR1                                                (0x14U)
#define ESM_ESMSR1                                                  (0x18U)
#define ESM_ESMSR2                                                  (0x1cU)
#define ESM_ESMSR3                                                  (0x20U)
#define ESM_ESMEPSR                                                 (0x24U)
#define ESM_ESMIOFFHR                                               (0x28U)
#define ESM_ESMIOFFLR                                               (0x2cU)
#define ESM_ESMLTCR                                                 (0x30U)
#define ESM_ESMLTCPR                                                (0x34U)
#define ESM_ESMEKR                                                  (0x38U)
#define ESM_ESMSSR2                                                 (0x3cU)
#define ESM_ESMIEPSR4                                               (0x40U)
#define ESM_ESMIEPCR4                                               (0x44U)
#define ESM_ESMIESR4                                                (0x48U)
#define ESM_ESMIECR4                                                (0x4cU)
#define ESM_ESMILSR4                                                (0x50U)
#define ESM_ESMILCR4                                                (0x54U)
#define ESM_ESMSR4                                                  (0x58U)
#define ESM_ESMSR5                                                  (0x5cU)
#define ESM_ESMSR6                                                  (0x60U)
#define ESM_ESMSSR5                                                 (0x64U)
#define ESM_ESMIEPSR7                                               (0x80U)
#define ESM_ESMIEPCR7                                               (0x84U)
#define ESM_ESMIESR7                                                (0x88U)
#define ESM_ESMIECR7                                                (0x8cU)
#define ESM_ESMILSR7                                                (0x90U)
#define ESM_ESMILCR7                                                (0x94U)
#define ESM_ESMSR7                                                  (0x98U)
#define ESM_ESMSR8                                                  (0x9cU)
#define ESM_ESMSR9                                                  (0xa0U)
#define ESM_ESMSSR8                                                 (0xa4U)
#define ESM_ESMIEPSR10                                              (0xc0U)
#define ESM_ESMIEPCR10                                              (0xc4U)
#define ESM_ESMIESR10                                               (0xc8U)
#define ESM_ESMIECR10                                               (0xccU)
#define ESM_ESMILSR10                                               (0xd0U)
#define ESM_ESMILCR10                                               (0xd4U)
#define ESM_ESMSR10                                                 (0xd8U)
#define ESM_ESMSR11                                                 (0xdcU)
#define ESM_ESMSR12                                                 (0xe0U)
#define ESM_ESMSSR11                                                (0xe4U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define ESM_ESMIEPSR1_IEPSET_SHIFT                                                      (0U)
#define ESM_ESMIEPSR1_IEPSET_MASK                                                       (0xffffffffU)

#define ESM_ESMIEPCR1_IEPCLR_SHIFT                                                      (0U)
#define ESM_ESMIEPCR1_IEPCLR_MASK                                                       (0xffffffffU)

#define ESM_ESMIESR1_INTENSET_SHIFT                                                     (0U)
#define ESM_ESMIESR1_INTENSET_MASK                                                      (0xffffffffU)

#define ESM_ESMIECR1_INTENCLR_SHIFT                                                     (0U)
#define ESM_ESMIECR1_INTENCLR_MASK                                                      (0xffffffffU)

#define ESM_ESMILSR1_INTLVLSET_SHIFT                                                    (0U)
#define ESM_ESMILSR1_INTLVLSET_MASK                                                     (0xffffffffU)

#define ESM_ESMILCR1_INTLVLCLR_SHIFT                                                    (0U)
#define ESM_ESMILCR1_INTLVLCLR_MASK                                                     (0xffffffffU)

#define ESM_ESMSR1_ESF_SHIFT                                                            (0U)
#define ESM_ESMSR1_ESF_MASK                                                             (0xffffffffU)

#define ESM_ESMSR2_ESF_SHIFT                                                            (0U)
#define ESM_ESMSR2_ESF_MASK                                                             (0xffffffffU)

#define ESM_ESMSR3_ESF_SHIFT                                                            (0U)
#define ESM_ESMSR3_ESF_MASK                                                             (0xffffffffU)

#define ESM_ESMEPSR_EPSF_SHIFT                                                          (0U)
#define ESM_ESMEPSR_EPSF_MASK                                                           (0x00000001U)

#define ESM_ESMEPSR_RES_SHIFT                                                           (1U)
#define ESM_ESMEPSR_RES_MASK                                                            (0xfffffffeU)

#define ESM_ESMIOFFHR_INTOFFH_SHIFT                                                     (0U)
#define ESM_ESMIOFFHR_INTOFFH_MASK                                                      (0x000001ffU)

#define ESM_ESMIOFFHR_RES_SHIFT                                                         (9U)
#define ESM_ESMIOFFHR_RES_MASK                                                          (0xfffffe00U)

#define ESM_ESMIOFFLR_INTOFFL_SHIFT                                                     (0U)
#define ESM_ESMIOFFLR_INTOFFL_MASK                                                      (0x000000ffU)

#define ESM_ESMIOFFLR_RES_SHIFT                                                         (8U)
#define ESM_ESMIOFFLR_RES_MASK                                                          (0xffffff00U)

#define ESM_ESMLTCR_LTC_SHIFT                                                           (0U)
#define ESM_ESMLTCR_LTC_MASK                                                            (0x0000ffffU)

#define ESM_ESMLTCR_RES_SHIFT                                                           (16U)
#define ESM_ESMLTCR_RES_MASK                                                            (0xffff0000U)

#define ESM_ESMLTCPR_LTCPR_SHIFT                                                        (0U)
#define ESM_ESMLTCPR_LTCPR_MASK                                                         (0x0000ffffU)
#define ESM_ESMLTCPR_LTCPR_MAX                                                          (0xffffU)

#define ESM_ESMLTCPR_LTCPW_SHIFT                                                        (14U)
#define ESM_ESMLTCPR_LTCPW_MASK                                                         (0x0000c000U)

#define ESM_ESMLTCPR_RES_SHIFT                                                          (16U)
#define ESM_ESMLTCPR_RES_MASK                                                           (0xffff0000U)

#define ESM_ESMEKR_EKEY_SHIFT                                                           (0U)
#define ESM_ESMEKR_EKEY_MASK                                                            (0x0000000fU)
#define ESM_ESMEKR_EKEY_NORMAL_MODE                                                     (0x0U)
#define ESM_ESMEKR_EKEY_ERROR_PIN_RESET                                                 (0x5U)
#define ESM_ESMEKR_EKEY_ERROR_FORCE_MODE                                                (0xAU)

#define ESM_ESMEKR_RES_SHIFT                                                            (4U)
#define ESM_ESMEKR_RES_MASK                                                             (0xfffffff0U)

#define ESM_ESMSSR2_ESF_SHIFT                                                           (0U)
#define ESM_ESMSSR2_ESF_MASK                                                            (0xffffffffU)

#define ESM_ESMIEPSR4_IEPSET_SHIFT                                                      (0U)
#define ESM_ESMIEPSR4_IEPSET_MASK                                                       (0xffffffffU)

#define ESM_ESMIEPCR4_IEPCLR_SHIFT                                                      (0U)
#define ESM_ESMIEPCR4_IEPCLR_MASK                                                       (0xffffffffU)

#define ESM_ESMIESR4_INTENSET_SHIFT                                                     (0U)
#define ESM_ESMIESR4_INTENSET_MASK                                                      (0xffffffffU)

#define ESM_ESMIECR4_INTENCLR_SHIFT                                                     (0U)
#define ESM_ESMIECR4_INTENCLR_MASK                                                      (0xffffffffU)

#define ESM_ESMILSR4_INTLVLSET_SHIFT                                                    (0U)
#define ESM_ESMILSR4_INTLVLSET_MASK                                                     (0xffffffffU)

#define ESM_ESMILCR4_INTLVLCLR_SHIFT                                                    (0U)
#define ESM_ESMILCR4_INTLVLCLR_MASK                                                     (0xffffffffU)

#define ESM_ESMSR4_ESF_SHIFT                                                            (0U)
#define ESM_ESMSR4_ESF_MASK                                                             (0xffffffffU)

#define ESM_ESMSR5_ESF_SHIFT                                                            (0U)
#define ESM_ESMSR5_ESF_MASK                                                             (0xffffffffU)

#define ESM_ESMSR6_ESF_SHIFT                                                            (0U)
#define ESM_ESMSR6_ESF_MASK                                                             (0xffffffffU)

#define ESM_ESMSSR5_ESF_SHIFT                                                           (0U)
#define ESM_ESMSSR5_ESF_MASK                                                            (0xffffffffU)

#define ESM_ESMIEPSR7_IEPSET_SHIFT                                                      (0U)
#define ESM_ESMIEPSR7_IEPSET_MASK                                                       (0xffffffffU)

#define ESM_ESMIEPCR7_IEPCLR_SHIFT                                                      (0U)
#define ESM_ESMIEPCR7_IEPCLR_MASK                                                       (0xffffffffU)

#define ESM_ESMIESR7_INTENSET_SHIFT                                                     (0U)
#define ESM_ESMIESR7_INTENSET_MASK                                                      (0xffffffffU)

#define ESM_ESMIECR7_INTENCLR_SHIFT                                                     (0U)
#define ESM_ESMIECR7_INTENCLR_MASK                                                      (0xffffffffU)

#define ESM_ESMILSR7_INTLVLSET_SHIFT                                                    (0U)
#define ESM_ESMILSR7_INTLVLSET_MASK                                                     (0xffffffffU)

#define ESM_ESMILCR7_INTLVLCLR_SHIFT                                                    (0U)
#define ESM_ESMILCR7_INTLVLCLR_MASK                                                     (0xffffffffU)

#define ESM_ESMSR7_ESF_SHIFT                                                            (0U)
#define ESM_ESMSR7_ESF_MASK                                                             (0xffffffffU)

#define ESM_ESMSR8_ESF_SHIFT                                                            (0U)
#define ESM_ESMSR8_ESF_MASK                                                             (0xffffffffU)

#define ESM_ESMSR9_ESF_SHIFT                                                            (0U)
#define ESM_ESMSR9_ESF_MASK                                                             (0xffffffffU)

#define ESM_ESMSSR8_ESF_SHIFT                                                           (0U)
#define ESM_ESMSSR8_ESF_MASK                                                            (0xffffffffU)

#define ESM_ESMIEPSR10_IEPSET_SHIFT                                                     (0U)
#define ESM_ESMIEPSR10_IEPSET_MASK                                                      (0xffffffffU)

#define ESM_ESMIEPCR10_IEPCLR_SHIFT                                                     (0U)
#define ESM_ESMIEPCR10_IEPCLR_MASK                                                      (0xffffffffU)

#define ESM_ESMIESR10_INTENSET_SHIFT                                                    (0U)
#define ESM_ESMIESR10_INTENSET_MASK                                                     (0xffffffffU)

#define ESM_ESMIECR10_INTENCLR_SHIFT                                                    (0U)
#define ESM_ESMIECR10_INTENCLR_MASK                                                     (0xffffffffU)

#define ESM_ESMILSR10_INTLVLSET_SHIFT                                                   (0U)
#define ESM_ESMILSR10_INTLVLSET_MASK                                                    (0xffffffffU)

#define ESM_ESMILCR10_INTLVLCLR_SHIFT                                                   (0U)
#define ESM_ESMILCR10_INTLVLCLR_MASK                                                    (0xffffffffU)

#define ESM_ESMSR10_ESF_SHIFT                                                           (0U)
#define ESM_ESMSR10_ESF_MASK                                                            (0xffffffffU)

#define ESM_ESMSR11_ESF_SHIFT                                                           (0U)
#define ESM_ESMSR11_ESF_MASK                                                            (0xffffffffU)

#define ESM_ESMSR12_ESF_SHIFT                                                           (0U)
#define ESM_ESMSR12_ESF_MASK                                                            (0xffffffffU)

#define ESM_ESMSSR11_ESF_SHIFT                                                          (0U)
#define ESM_ESMSSR11_ESF_MASK                                                           (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_ESM_H_ */
