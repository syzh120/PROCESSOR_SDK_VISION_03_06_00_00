/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015
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

#ifndef HW_DCC_H_
#define HW_DCC_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define DCC_DCCGCTRL                                                (0x0U)
#define DCC_DCCREV                                                  (0x4U)
#define DCC_DCCCNTSEED0                                             (0x8U)
#define DCC_DCCVALIDSEED0                                           (0xcU)
#define DCC_DCCCNTSEED1                                             (0x10U)
#define DCC_DCCSTAT                                                 (0x14U)
#define DCC_DCCCNT0                                                 (0x18U)
#define DCC_DCCVALID0                                               (0x1cU)
#define DCC_DCCCNT1                                                 (0x20U)
#define DCC_DCCCLKSRC1                                              (0x24U)
#define DCC_DCCCLKSRC0                                              (0x28U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DCC_DCCGCTRL_DCCENA_SHIFT                                                       (0U)
#define DCC_DCCGCTRL_DCCENA_MASK                                                        (0x0000000fU)
#define DCC_DCCGCTRL_DCCENA_ENABLE                                                      (0xFU)
#define DCC_DCCGCTRL_DCCENA_DISABLE                                                     (0x5U)

#define DCC_DCCGCTRL_ERRENA_SHIFT                                                       (4U)
#define DCC_DCCGCTRL_ERRENA_MASK                                                        (0x000000f0U)
#define DCC_DCCGCTRL_ERRENA_ENABLE                                                      (0xFU)
#define DCC_DCCGCTRL_ERRENA_DISABLE                                                     (0x5U)

#define DCC_DCCGCTRL_SINGLESHOT_SHIFT                                                   (8U)
#define DCC_DCCGCTRL_SINGLESHOT_MASK                                                    (0x00000f00U)
#define DCC_DCCGCTRL_SINGLESHOT_MODE1                                                   (0xAU)
#define DCC_DCCGCTRL_SINGLESHOT_MODE2                                                   (0xBU)
#define DCC_DCCGCTRL_SINGLESHOT_DISABLE                                                 (0x0U)

#define DCC_DCCGCTRL_DONEENA_SHIFT                                                      (12U)
#define DCC_DCCGCTRL_DONEENA_MASK                                                       (0x0000f000U)
#define DCC_DCCGCTRL_DONEENA_ENABLE                                                     (0xFU)
#define DCC_DCCGCTRL_DONEENA_DISABLE                                                    (0x5U)

#define DCC_DCCGCTRL_RES_SHIFT                                                          (16U)
#define DCC_DCCGCTRL_RES_MASK                                                           (0xffff0000U)

#define DCC_DCCREV_MINOR_SHIFT                                                          (0U)
#define DCC_DCCREV_MINOR_MASK                                                           (0x0000003fU)

#define DCC_DCCREV_CUSTOM_SHIFT                                                         (6U)
#define DCC_DCCREV_CUSTOM_MASK                                                          (0x000000c0U)

#define DCC_DCCREV_MAJOR_SHIFT                                                          (8U)
#define DCC_DCCREV_MAJOR_MASK                                                           (0x00000700U)

#define DCC_DCCREV_RTL_SHIFT                                                            (11U)
#define DCC_DCCREV_RTL_MASK                                                             (0x0000f800U)

#define DCC_DCCREV_FUNC_SHIFT                                                           (16U)
#define DCC_DCCREV_FUNC_MASK                                                            (0x0fff0000U)

#define DCC_DCCREV_RES_SHIFT                                                            (28U)
#define DCC_DCCREV_RES_MASK                                                             (0x30000000U)

#define DCC_DCCREV_SCHEME_SHIFT                                                         (30U)
#define DCC_DCCREV_SCHEME_MASK                                                          (0xc0000000U)

#define DCC_DCCCNTSEED0_COUNTSEED0_SHIFT                                                (0U)
#define DCC_DCCCNTSEED0_COUNTSEED0_MASK                                                 (0x000fffffU)

#define DCC_DCCCNTSEED0_RES_SHIFT                                                       (20U)
#define DCC_DCCCNTSEED0_RES_MASK                                                        (0xfff00000U)

#define DCC_DCCVALIDSEED0_VALIDSEED0_SHIFT                                              (0U)
#define DCC_DCCVALIDSEED0_VALIDSEED0_MASK                                               (0x0000ffffU)

#define DCC_DCCVALIDSEED0_RES_SHIFT                                                     (16U)
#define DCC_DCCVALIDSEED0_RES_MASK                                                      (0xffff0000U)

#define DCC_DCCCNTSEED1_COUNTSEED1_SHIFT                                                (0U)
#define DCC_DCCCNTSEED1_COUNTSEED1_MASK                                                 (0x000fffffU)

#define DCC_DCCCNTSEED1_RES_SHIFT                                                       (20U)
#define DCC_DCCCNTSEED1_RES_MASK                                                        (0xfff00000U)

#define DCC_DCCSTAT_ERRFLG_SHIFT                                                        (0U)
#define DCC_DCCSTAT_ERRFLG_MASK                                                         (0x00000001U)

#define DCC_DCCSTAT_DONEFLG_SHIFT                                                       (1U)
#define DCC_DCCSTAT_DONEFLG_MASK                                                        (0x00000002U)

#define DCC_DCCSTAT_RES_SHIFT                                                           (2U)
#define DCC_DCCSTAT_RES_MASK                                                            (0xfffffffcU)

#define DCC_DCCCNT0_COUNT0_SHIFT                                                        (0U)
#define DCC_DCCCNT0_COUNT0_MASK                                                         (0x000fffffU)

#define DCC_DCCCNT0_RES_SHIFT                                                           (20U)
#define DCC_DCCCNT0_RES_MASK                                                            (0xfff00000U)

#define DCC_DCCVALID0_VALID0_SHIFT                                                      (0U)
#define DCC_DCCVALID0_VALID0_MASK                                                       (0x0000ffffU)

#define DCC_DCCVALID0_RES_SHIFT                                                         (16U)
#define DCC_DCCVALID0_RES_MASK                                                          (0xffff0000U)

#define DCC_DCCCNT1_COUNT1_SHIFT                                                        (0U)
#define DCC_DCCCNT1_COUNT1_MASK                                                         (0x000fffffU)

#define DCC_DCCCNT1_RES_SHIFT                                                           (20U)
#define DCC_DCCCNT1_RES_MASK                                                            (0xfff00000U)

#define DCC_DCCCLKSRC1_CLKSRC_SHIFT                                                     (0U)
#define DCC_DCCCLKSRC1_CLKSRC_MASK                                                      (0x0000000fU)
#define DCC_DCCCLKSRC1_CLKSRC_0                                                         (0x0U)
#define DCC_DCCCLKSRC1_CLKSRC_1                                                         (0x1U)
#define DCC_DCCCLKSRC1_CLKSRC_2                                                         (0x2U)
#define DCC_DCCCLKSRC1_CLKSRC_3                                                         (0x3U)
#define DCC_DCCCLKSRC1_CLKSRC_4                                                         (0x4U)
#define DCC_DCCCLKSRC1_CLKSRC_5                                                         (0x5U)
#define DCC_DCCCLKSRC1_CLKSRC_6                                                         (0x6U)
#define DCC_DCCCLKSRC1_CLKSRC_7                                                         (0x7U)
#define DCC_DCCCLKSRC1_CLKSRC_OTHER                                                     (0xFU)

#define DCC_DCCCLKSRC1_RES1_SHIFT                                                       (4U)
#define DCC_DCCCLKSRC1_RES1_MASK                                                        (0x00000ff0U)

#define DCC_DCCCLKSRC1_KEY_SHIFT                                                        (12U)
#define DCC_DCCCLKSRC1_KEY_MASK                                                         (0x0000f000U)
#define DCC_DCCCLKSRC1_KEY_ENABLE                                                       (0xAU)
#define DCC_DCCCLKSRC1_KEY_DISABLE                                                      (0x0U)

#define DCC_DCCCLKSRC1_RES0_SHIFT                                                       (16U)
#define DCC_DCCCLKSRC1_RES0_MASK                                                        (0xffff0000U)

#define DCC_DCCCLKSRC0_CLKSRC0_SHIFT                                                    (0U)
#define DCC_DCCCLKSRC0_CLKSRC0_MASK                                                     (0x0000000fU)
#define DCC_DCCCLKSRC0_CLKSRC0_0                                                        (0x0U)
#define DCC_DCCCLKSRC0_CLKSRC0_1                                                        (0xAU)
#define DCC_DCCCLKSRC0_CLKSRC0_2                                                        (0x5U)


#define DCC_DCCCLKSRC0_RES_SHIFT                                                        (4U)
#define DCC_DCCCLKSRC0_RES_MASK                                                         (0xfffffff0U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DCC_H_ */

