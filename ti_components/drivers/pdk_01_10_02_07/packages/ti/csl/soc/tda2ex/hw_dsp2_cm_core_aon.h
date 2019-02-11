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
 *  \file   hw_dsp2_cm_core_aon.h
 *
 *  \brief  register-level header file for PRCM
 *
**/

#ifndef HW_DSP2_CM_CORE_AON_H_
#define HW_DSP2_CM_CORE_AON_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define CM_DSP2_CLKSTCTRL                                                                                   (0x0U)
#define CM_DSP2_STATICDEP                                                                                   (0x4U)
#define CM_DSP2_DYNAMICDEP                                                                                  (0x8U)
#define CM_DSP2_DSP2_CLKCTRL                                                                                (0x20U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CM_DSP2_CLKSTCTRL_CLKTRCTRL_SHIFT                                                                   (0U)
#define CM_DSP2_CLKSTCTRL_CLKTRCTRL_MASK                                                                    (0x00000003U)
#define CM_DSP2_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                                                 (0U)
#define CM_DSP2_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                                                                 (1U)
#define CM_DSP2_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                                                  (2U)
#define CM_DSP2_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                                                  (3U)

#define CM_DSP2_CLKSTCTRL_CLKACTIVITY_DSP2_GFCLK_SHIFT                                                      (8U)
#define CM_DSP2_CLKSTCTRL_CLKACTIVITY_DSP2_GFCLK_MASK                                                       (0x00000100U)
#define CM_DSP2_CLKSTCTRL_CLKACTIVITY_DSP2_GFCLK_INACT                                                       (0U)
#define CM_DSP2_CLKSTCTRL_CLKACTIVITY_DSP2_GFCLK_ACT                                                         (1U)

#define CM_DSP2_CLKSTCTRL_RESERVED_SHIFT                                                                    (2U)
#define CM_DSP2_CLKSTCTRL_RESERVED_MASK                                                                     (0x000000fcU)

#define CM_DSP2_CLKSTCTRL_RESERVED1_SHIFT                                                                   (9U)
#define CM_DSP2_CLKSTCTRL_RESERVED1_MASK                                                                    (0xfffffe00U)

#define CM_DSP2_STATICDEP_IVA_STATDEP_SHIFT                                                                 (2U)
#define CM_DSP2_STATICDEP_IVA_STATDEP_MASK                                                                  (0x00000004U)
#define CM_DSP2_STATICDEP_IVA_STATDEP_ENABLED                                                                (1U)
#define CM_DSP2_STATICDEP_IVA_STATDEP_DISABLED                                                               (0U)

#define CM_DSP2_STATICDEP_EMIF_STATDEP_SHIFT                                                                (4U)
#define CM_DSP2_STATICDEP_EMIF_STATDEP_MASK                                                                 (0x00000010U)
#define CM_DSP2_STATICDEP_EMIF_STATDEP_ENABLED                                                               (1U)
#define CM_DSP2_STATICDEP_EMIF_STATDEP_DISABLED                                                              (0U)

#define CM_DSP2_STATICDEP_L3MAIN1_STATDEP_SHIFT                                                             (5U)
#define CM_DSP2_STATICDEP_L3MAIN1_STATDEP_MASK                                                              (0x00000020U)
#define CM_DSP2_STATICDEP_L3MAIN1_STATDEP_ENABLED                                                            (1U)

#define CM_DSP2_STATICDEP_L3INIT_STATDEP_SHIFT                                                              (7U)
#define CM_DSP2_STATICDEP_L3INIT_STATDEP_MASK                                                               (0x00000080U)
#define CM_DSP2_STATICDEP_L3INIT_STATDEP_ENABLED                                                             (1U)
#define CM_DSP2_STATICDEP_L3INIT_STATDEP_DISABLED                                                            (0U)

#define CM_DSP2_STATICDEP_CAM_STATDEP_SHIFT                                                                 (9U)
#define CM_DSP2_STATICDEP_CAM_STATDEP_MASK                                                                  (0x00000200U)
#define CM_DSP2_STATICDEP_CAM_STATDEP_ENABLED                                                                (1U)
#define CM_DSP2_STATICDEP_CAM_STATDEP_DISABLED                                                               (0U)

#define CM_DSP2_STATICDEP_L4CFG_STATDEP_SHIFT                                                               (12U)
#define CM_DSP2_STATICDEP_L4CFG_STATDEP_MASK                                                                (0x00001000U)
#define CM_DSP2_STATICDEP_L4CFG_STATDEP_DISABLED                                                             (0U)

#define CM_DSP2_STATICDEP_L4PER_STATDEP_SHIFT                                                               (13U)
#define CM_DSP2_STATICDEP_L4PER_STATDEP_MASK                                                                (0x00002000U)
#define CM_DSP2_STATICDEP_L4PER_STATDEP_ENABLED                                                              (1U)
#define CM_DSP2_STATICDEP_L4PER_STATDEP_DISABLED                                                             (0U)

#define CM_DSP2_STATICDEP_COREAON_STATDEP_SHIFT                                                             (16U)
#define CM_DSP2_STATICDEP_COREAON_STATDEP_MASK                                                              (0x00010000U)
#define CM_DSP2_STATICDEP_COREAON_STATDEP_DISABLED                                                           (0U)

#define CM_DSP2_STATICDEP_CUSTEFUSE_STATDEP_SHIFT                                                           (17U)
#define CM_DSP2_STATICDEP_CUSTEFUSE_STATDEP_MASK                                                            (0x00020000U)
#define CM_DSP2_STATICDEP_CUSTEFUSE_STATDEP_DISABLED                                                         (0U)

#define CM_DSP2_STATICDEP_WKUPAON_STATDEP_SHIFT                                                             (15U)
#define CM_DSP2_STATICDEP_WKUPAON_STATDEP_MASK                                                              (0x00008000U)
#define CM_DSP2_STATICDEP_WKUPAON_STATDEP_ENABLED                                                            (1U)
#define CM_DSP2_STATICDEP_WKUPAON_STATDEP_DISABLED                                                           (0U)

#define CM_DSP2_STATICDEP_ATL_STATDEP_SHIFT                                                                 (30U)
#define CM_DSP2_STATICDEP_ATL_STATDEP_MASK                                                                  (0x40000000U)
#define CM_DSP2_STATICDEP_ATL_STATDEP_ENABLED                                                                (1U)
#define CM_DSP2_STATICDEP_ATL_STATDEP_DISABLED                                                               (0U)

#define CM_DSP2_STATICDEP_DSS_STATDEP_SHIFT                                                                 (8U)
#define CM_DSP2_STATICDEP_DSS_STATDEP_MASK                                                                  (0x00000100U)
#define CM_DSP2_STATICDEP_DSS_STATDEP_ENABLED                                                                (1U)
#define CM_DSP2_STATICDEP_DSS_STATDEP_DISABLED                                                               (0U)

#define CM_DSP2_STATICDEP_EVE1_STATDEP_SHIFT                                                                (19U)
#define CM_DSP2_STATICDEP_EVE1_STATDEP_MASK                                                                 (0x00080000U)
#define CM_DSP2_STATICDEP_EVE1_STATDEP_ENABLED                                                               (1U)
#define CM_DSP2_STATICDEP_EVE1_STATDEP_DISABLED                                                              (0U)

#define CM_DSP2_STATICDEP_EVE2_STATDEP_SHIFT                                                                (20U)
#define CM_DSP2_STATICDEP_EVE2_STATDEP_MASK                                                                 (0x00100000U)
#define CM_DSP2_STATICDEP_EVE2_STATDEP_ENABLED                                                               (1U)
#define CM_DSP2_STATICDEP_EVE2_STATDEP_DISABLED                                                              (0U)

#define CM_DSP2_STATICDEP_EVE3_STATDEP_SHIFT                                                                (21U)
#define CM_DSP2_STATICDEP_EVE3_STATDEP_MASK                                                                 (0x00200000U)
#define CM_DSP2_STATICDEP_EVE3_STATDEP_ENABLED                                                               (1U)
#define CM_DSP2_STATICDEP_EVE3_STATDEP_DISABLED                                                              (0U)

#define CM_DSP2_STATICDEP_EVE4_STATDEP_SHIFT                                                                (22U)
#define CM_DSP2_STATICDEP_EVE4_STATDEP_MASK                                                                 (0x00400000U)
#define CM_DSP2_STATICDEP_EVE4_STATDEP_ENABLED                                                               (1U)
#define CM_DSP2_STATICDEP_EVE4_STATDEP_DISABLED                                                              (0U)

#define CM_DSP2_STATICDEP_GPU_STATDEP_SHIFT                                                                 (10U)
#define CM_DSP2_STATICDEP_GPU_STATDEP_MASK                                                                  (0x00000400U)
#define CM_DSP2_STATICDEP_GPU_STATDEP_ENABLED                                                                (1U)
#define CM_DSP2_STATICDEP_GPU_STATDEP_DISABLED                                                               (0U)

#define CM_DSP2_STATICDEP_IPU_STATDEP_SHIFT                                                                 (24U)
#define CM_DSP2_STATICDEP_IPU_STATDEP_MASK                                                                  (0x01000000U)
#define CM_DSP2_STATICDEP_IPU_STATDEP_ENABLED                                                                (1U)
#define CM_DSP2_STATICDEP_IPU_STATDEP_DISABLED                                                               (0U)

#define CM_DSP2_STATICDEP_GMAC_STATDEP_SHIFT                                                                (25U)
#define CM_DSP2_STATICDEP_GMAC_STATDEP_MASK                                                                 (0x02000000U)
#define CM_DSP2_STATICDEP_GMAC_STATDEP_ENABLED                                                               (1U)
#define CM_DSP2_STATICDEP_GMAC_STATDEP_DISABLED                                                              (0U)

#define CM_DSP2_STATICDEP_L4PER2_STATDEP_SHIFT                                                              (26U)
#define CM_DSP2_STATICDEP_L4PER2_STATDEP_MASK                                                               (0x04000000U)
#define CM_DSP2_STATICDEP_L4PER2_STATDEP_ENABLED                                                             (1U)
#define CM_DSP2_STATICDEP_L4PER2_STATDEP_DISABLED                                                            (0U)

#define CM_DSP2_STATICDEP_L4PER3_STATDEP_SHIFT                                                              (27U)
#define CM_DSP2_STATICDEP_L4PER3_STATDEP_MASK                                                               (0x08000000U)
#define CM_DSP2_STATICDEP_L4PER3_STATDEP_ENABLED                                                             (1U)
#define CM_DSP2_STATICDEP_L4PER3_STATDEP_DISABLED                                                            (0U)

#define CM_DSP2_STATICDEP_L4SEC_STATDEP_SHIFT                                                               (14U)
#define CM_DSP2_STATICDEP_L4SEC_STATDEP_MASK                                                                (0x00004000U)
#define CM_DSP2_STATICDEP_L4SEC_STATDEP_ENABLED                                                              (1U)
#define CM_DSP2_STATICDEP_L4SEC_STATDEP_DISABLED                                                             (0U)

#define CM_DSP2_STATICDEP_VPE_STATDEP_SHIFT                                                                 (28U)
#define CM_DSP2_STATICDEP_VPE_STATDEP_MASK                                                                  (0x10000000U)
#define CM_DSP2_STATICDEP_VPE_STATDEP_ENABLED                                                                (1U)
#define CM_DSP2_STATICDEP_VPE_STATDEP_DISABLED                                                               (0U)

#define CM_DSP2_STATICDEP_PCIE_STATDEP_SHIFT                                                                (29U)
#define CM_DSP2_STATICDEP_PCIE_STATDEP_MASK                                                                 (0x20000000U)
#define CM_DSP2_STATICDEP_PCIE_STATDEP_ENABLED                                                               (1U)
#define CM_DSP2_STATICDEP_PCIE_STATDEP_DISABLED                                                              (0U)

#define CM_DSP2_STATICDEP_RESERVED1_SHIFT                                                                   (3U)
#define CM_DSP2_STATICDEP_RESERVED1_MASK                                                                    (0x00000008U)

#define CM_DSP2_STATICDEP_RESERVED2_SHIFT                                                                   (6U)
#define CM_DSP2_STATICDEP_RESERVED2_MASK                                                                    (0x00000040U)

#define CM_DSP2_STATICDEP_RESERVED3_SHIFT                                                                   (11U)
#define CM_DSP2_STATICDEP_RESERVED3_MASK                                                                    (0x00000800U)

#define CM_DSP2_STATICDEP_RESERVED5_SHIFT                                                                   (31U)
#define CM_DSP2_STATICDEP_RESERVED5_MASK                                                                    (0x80000000U)

#define CM_DSP2_STATICDEP_DSP1_STATDEP_SHIFT                                                                (1U)
#define CM_DSP2_STATICDEP_DSP1_STATDEP_MASK                                                                 (0x00000002U)
#define CM_DSP2_STATICDEP_DSP1_STATDEP_ENABLED                                                               (1U)
#define CM_DSP2_STATICDEP_DSP1_STATDEP_DISABLED                                                              (0U)

#define CM_DSP2_STATICDEP_RESERVED6_SHIFT                                                                   (18U)
#define CM_DSP2_STATICDEP_RESERVED6_MASK                                                                    (0x00040000U)

#define CM_DSP2_STATICDEP_IPU2_STATDEP_SHIFT                                                                (0U)
#define CM_DSP2_STATICDEP_IPU2_STATDEP_MASK                                                                 (0x00000001U)
#define CM_DSP2_STATICDEP_IPU2_STATDEP_ENABLED                                                               (1U)
#define CM_DSP2_STATICDEP_IPU2_STATDEP_DISABLED                                                              (0U)

#define CM_DSP2_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT                                                             (5U)
#define CM_DSP2_DYNAMICDEP_L3MAIN1_DYNDEP_MASK                                                              (0x00000020U)
#define CM_DSP2_DYNAMICDEP_L3MAIN1_DYNDEP_ENABLED                                                            (1U)

#define CM_DSP2_DYNAMICDEP_RESERVED1_SHIFT                                                                  (28U)
#define CM_DSP2_DYNAMICDEP_RESERVED1_MASK                                                                   (0xf0000000U)

#define CM_DSP2_DYNAMICDEP_RESERVED3_SHIFT                                                                  (6U)
#define CM_DSP2_DYNAMICDEP_RESERVED3_MASK                                                                   (0x00ffffc0U)

#define CM_DSP2_DYNAMICDEP_WINDOWSIZE_SHIFT                                                                 (24U)
#define CM_DSP2_DYNAMICDEP_WINDOWSIZE_MASK                                                                  (0x0f000000U)

#define CM_DSP2_DYNAMICDEP_RESERVED_SHIFT                                                                   (0U)
#define CM_DSP2_DYNAMICDEP_RESERVED_MASK                                                                    (0x0000001fU)

#define CM_DSP2_DSP2_CLKCTRL_RESERVED_SHIFT                                                                 (2U)
#define CM_DSP2_DSP2_CLKCTRL_RESERVED_MASK                                                                  (0x0000fffcU)

#define CM_DSP2_DSP2_CLKCTRL_RESERVED1_SHIFT                                                                (19U)
#define CM_DSP2_DSP2_CLKCTRL_RESERVED1_MASK                                                                 (0xfff80000U)

#define CM_DSP2_DSP2_CLKCTRL_IDLEST_SHIFT                                                                   (16U)
#define CM_DSP2_DSP2_CLKCTRL_IDLEST_MASK                                                                    (0x00030000U)
#define CM_DSP2_DSP2_CLKCTRL_IDLEST_DISABLE                                                                  (3U)
#define CM_DSP2_DSP2_CLKCTRL_IDLEST_IDLE                                                                     (2U)
#define CM_DSP2_DSP2_CLKCTRL_IDLEST_FUNC                                                                     (0U)
#define CM_DSP2_DSP2_CLKCTRL_IDLEST_TRANS                                                                    (1U)

#define CM_DSP2_DSP2_CLKCTRL_STBYST_SHIFT                                                                   (18U)
#define CM_DSP2_DSP2_CLKCTRL_STBYST_MASK                                                                    (0x00040000U)
#define CM_DSP2_DSP2_CLKCTRL_STBYST_FUNC                                                                     (0U)
#define CM_DSP2_DSP2_CLKCTRL_STBYST_STANDBY                                                                  (1U)

#define CM_DSP2_DSP2_CLKCTRL_MODULEMODE_SHIFT                                                               (0U)
#define CM_DSP2_DSP2_CLKCTRL_MODULEMODE_MASK                                                                (0x00000003U)
#define CM_DSP2_DSP2_CLKCTRL_MODULEMODE_DISABLED                                                             (0U)
#define CM_DSP2_DSP2_CLKCTRL_MODULEMODE_AUTO                                                                 (1U)
#define CM_DSP2_DSP2_CLKCTRL_MODULEMODE_RESERVED_2                                                           (2U)
#define CM_DSP2_DSP2_CLKCTRL_MODULEMODE_RESERVED                                                             (3U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_DSP2_CM_CORE_AON_H_ */
