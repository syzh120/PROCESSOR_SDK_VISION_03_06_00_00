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
 *  \file   hw_cam_cm_core.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_CAM_CM_CORE_H_
#define HW_CAM_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define CM_CAM_CLKSTCTRL                                        (0x0U)
#define CM_CAM_STATICDEP                                        (0x4U)
#define CM_CAM_VIP1_CLKCTRL                                     (0x20U)
#define CM_CAM_VIP2_CLKCTRL                                     (0x28U)
#define CM_CAM_VIP3_CLKCTRL                                     (0x30U)
#define CM_CAM_LVDSRX_CLKCTRL                                   (0x38U)
#define CM_CAM_CSI1_CLKCTRL                                     (0x40U)
#define CM_CAM_CSI2_CLKCTRL                                     (0x48U)


/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CM_CAM_CLKSTCTRL_CLKTRCTRL_SHIFT                        (0U)
#define CM_CAM_CLKSTCTRL_CLKTRCTRL_MASK                         (0x00000003U)
#define CM_CAM_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                      (0U)
#define CM_CAM_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                      (1U)
#define CM_CAM_CLKSTCTRL_CLKTRCTRL_SW_WKUP                       (2U)
#define CM_CAM_CLKSTCTRL_CLKTRCTRL_HW_AUTO                       (3U)

#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP1_GCLK_SHIFT            (8U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP1_GCLK_MASK             (0x00000100U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP1_GCLK_INACT             (0U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP1_GCLK_ACT               (1U)

#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP2_GCLK_SHIFT            (9U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP2_GCLK_MASK             (0x00000200U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP2_GCLK_INACT             (0U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP2_GCLK_ACT               (1U)

#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP3_GCLK_SHIFT            (10U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP3_GCLK_MASK             (0x00000400U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP3_GCLK_INACT             (0U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_VIP3_GCLK_ACT               (1U)

#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_L4_GICLK_SHIFT      (11U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_L4_GICLK_MASK       (0x00000800U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_L4_GICLK_INACT       (0U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_L4_GICLK_ACT         (1U)

#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_96M_GFCLK_SHIFT     (12U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_96M_GFCLK_MASK      (0x00001000U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_96M_GFCLK_INACT      (0U)
#define CM_CAM_CLKSTCTRL_CLKACTIVITY_LVDSRX_96M_GFCLK_ACT        (1U)

#define CM_CAM_STATICDEP_IVA_STATDEP_SHIFT                      (2U)
#define CM_CAM_STATICDEP_IVA_STATDEP_MASK                       (0x00000004U)
#define CM_CAM_STATICDEP_IVA_STATDEP_ENABLED                     (1U)
#define CM_CAM_STATICDEP_IVA_STATDEP_DISABLED                    (0U)

#define CM_CAM_STATICDEP_EMIF_STATDEP_SHIFT                     (4U)
#define CM_CAM_STATICDEP_EMIF_STATDEP_MASK                      (0x00000010U)
#define CM_CAM_STATICDEP_EMIF_STATDEP_ENABLED                    (1U)
#define CM_CAM_STATICDEP_EMIF_STATDEP_DISABLED                   (0U)

#define CM_CAM_STATICDEP_L3MAIN1_STATDEP_SHIFT                  (5U)
#define CM_CAM_STATICDEP_L3MAIN1_STATDEP_MASK                   (0x00000020U)
#define CM_CAM_STATICDEP_L3MAIN1_STATDEP_ENABLED                 (1U)

#define CM_CAM_STATICDEP_L4CFG_STATDEP_SHIFT                    (12U)
#define CM_CAM_STATICDEP_L4CFG_STATDEP_MASK                     (0x00001000U)
#define CM_CAM_STATICDEP_L4CFG_STATDEP_DISABLED                  (0U)

#define CM_CAM_STATICDEP_EVE1_STATDEP_SHIFT                     (19U)
#define CM_CAM_STATICDEP_EVE1_STATDEP_MASK                      (0x00080000U)
#define CM_CAM_STATICDEP_EVE1_STATDEP_ENABLED                    (1U)
#define CM_CAM_STATICDEP_EVE1_STATDEP_DISABLED                   (0U)

#define CM_CAM_STATICDEP_EVE2_STATDEP_SHIFT                     (20U)
#define CM_CAM_STATICDEP_EVE2_STATDEP_MASK                      (0x00100000U)
#define CM_CAM_STATICDEP_EVE2_STATDEP_ENABLED                    (1U)
#define CM_CAM_STATICDEP_EVE2_STATDEP_DISABLED                   (0U)

#define CM_CAM_STATICDEP_EVE3_STATDEP_SHIFT                     (21U)
#define CM_CAM_STATICDEP_EVE3_STATDEP_MASK                      (0x00200000U)
#define CM_CAM_STATICDEP_EVE3_STATDEP_ENABLED                    (1U)
#define CM_CAM_STATICDEP_EVE3_STATDEP_DISABLED                   (0U)

#define CM_CAM_STATICDEP_EVE4_STATDEP_SHIFT                     (22U)
#define CM_CAM_STATICDEP_EVE4_STATDEP_MASK                      (0x00400000U)
#define CM_CAM_STATICDEP_EVE4_STATDEP_ENABLED                    (1U)
#define CM_CAM_STATICDEP_EVE4_STATDEP_DISABLED                   (0U)

#define CM_CAM_STATICDEP_GMAC_STATDEP_SHIFT                     (25U)
#define CM_CAM_STATICDEP_GMAC_STATDEP_MASK                      (0x02000000U)
#define CM_CAM_STATICDEP_GMAC_STATDEP_ENABLED                    (1U)
#define CM_CAM_STATICDEP_GMAC_STATDEP_DISABLED                   (0U)

#define CM_CAM_STATICDEP_L4PER3_STATDEP_SHIFT                   (27U)
#define CM_CAM_STATICDEP_L4PER3_STATDEP_MASK                    (0x08000000U)
#define CM_CAM_STATICDEP_L4PER3_STATDEP_ENABLED                  (1U)
#define CM_CAM_STATICDEP_L4PER3_STATDEP_DISABLED                 (0U)

#define CM_CAM_STATICDEP_VPE_STATDEP_SHIFT                      (28U)
#define CM_CAM_STATICDEP_VPE_STATDEP_MASK                       (0x10000000U)
#define CM_CAM_STATICDEP_VPE_STATDEP_ENABLED                     (1U)
#define CM_CAM_STATICDEP_VPE_STATDEP_DISABLED                    (0U)

#define CM_CAM_VIP1_CLKCTRL_IDLEST_SHIFT                        (16U)
#define CM_CAM_VIP1_CLKCTRL_IDLEST_MASK                         (0x00030000U)
#define CM_CAM_VIP1_CLKCTRL_IDLEST_DISABLE                       (3U)
#define CM_CAM_VIP1_CLKCTRL_IDLEST_IDLE                          (2U)
#define CM_CAM_VIP1_CLKCTRL_IDLEST_FUNC                          (0U)
#define CM_CAM_VIP1_CLKCTRL_IDLEST_TRANS                         (1U)

#define CM_CAM_VIP1_CLKCTRL_STBYST_SHIFT                        (18U)
#define CM_CAM_VIP1_CLKCTRL_STBYST_MASK                         (0x00040000U)
#define CM_CAM_VIP1_CLKCTRL_STBYST_FUNC                          (0U)
#define CM_CAM_VIP1_CLKCTRL_STBYST_STANDBY                       (1U)

#define CM_CAM_VIP1_CLKCTRL_CLKSEL_SHIFT                        (24U)
#define CM_CAM_VIP1_CLKCTRL_CLKSEL_MASK                         (0x01000000U)
#define CM_CAM_VIP1_CLKCTRL_CLKSEL_SEL_L3_ICLK                   (0U)
#define CM_CAM_VIP1_CLKCTRL_CLKSEL_SEL_CORE_ISS_MAIN_CLK         (1U)

#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_SHIFT                    (0U)
#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_MASK                     (0x00000003U)
#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_DISABLED                  (0U)
#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_AUTO                      (1U)
#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_RESERVED_2                (2U)
#define CM_CAM_VIP1_CLKCTRL_MODULEMODE_RESERVED                  (3U)

#define CM_CAM_VIP2_CLKCTRL_IDLEST_SHIFT                        (16U)
#define CM_CAM_VIP2_CLKCTRL_IDLEST_MASK                         (0x00030000U)
#define CM_CAM_VIP2_CLKCTRL_IDLEST_DISABLE                       (3U)
#define CM_CAM_VIP2_CLKCTRL_IDLEST_IDLE                          (2U)
#define CM_CAM_VIP2_CLKCTRL_IDLEST_FUNC                          (0U)
#define CM_CAM_VIP2_CLKCTRL_IDLEST_TRANS                         (1U)

#define CM_CAM_VIP2_CLKCTRL_STBYST_SHIFT                        (18U)
#define CM_CAM_VIP2_CLKCTRL_STBYST_MASK                         (0x00040000U)
#define CM_CAM_VIP2_CLKCTRL_STBYST_FUNC                          (0U)
#define CM_CAM_VIP2_CLKCTRL_STBYST_STANDBY                       (1U)

#define CM_CAM_VIP2_CLKCTRL_CLKSEL_SHIFT                        (24U)
#define CM_CAM_VIP2_CLKCTRL_CLKSEL_MASK                         (0x01000000U)
#define CM_CAM_VIP2_CLKCTRL_CLKSEL_SEL_L3_ICLK                   (0U)
#define CM_CAM_VIP2_CLKCTRL_CLKSEL_SEL_CORE_ISS_MAIN_CLK         (1U)

#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_SHIFT                    (0U)
#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_MASK                     (0x00000003U)
#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_DISABLED                  (0U)
#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_AUTO                      (1U)
#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_RESERVED_2                (2U)
#define CM_CAM_VIP2_CLKCTRL_MODULEMODE_RESERVED                  (3U)

#define CM_CAM_VIP3_CLKCTRL_IDLEST_SHIFT                        (16U)
#define CM_CAM_VIP3_CLKCTRL_IDLEST_MASK                         (0x00030000U)
#define CM_CAM_VIP3_CLKCTRL_IDLEST_DISABLE                       (3U)
#define CM_CAM_VIP3_CLKCTRL_IDLEST_IDLE                          (2U)
#define CM_CAM_VIP3_CLKCTRL_IDLEST_FUNC                          (0U)
#define CM_CAM_VIP3_CLKCTRL_IDLEST_TRANS                         (1U)

#define CM_CAM_VIP3_CLKCTRL_STBYST_SHIFT                        (18U)
#define CM_CAM_VIP3_CLKCTRL_STBYST_MASK                         (0x00040000U)
#define CM_CAM_VIP3_CLKCTRL_STBYST_FUNC                          (0U)
#define CM_CAM_VIP3_CLKCTRL_STBYST_STANDBY                       (1U)

#define CM_CAM_VIP3_CLKCTRL_CLKSEL_SHIFT                        (24U)
#define CM_CAM_VIP3_CLKCTRL_CLKSEL_MASK                         (0x01000000U)
#define CM_CAM_VIP3_CLKCTRL_CLKSEL_SEL_L3_ICLK                   (0U)
#define CM_CAM_VIP3_CLKCTRL_CLKSEL_SEL_CORE_ISS_MAIN_CLK         (1U)

#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_SHIFT                    (0U)
#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_MASK                     (0x00000003U)
#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_DISABLED                  (0U)
#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_AUTO                      (1U)
#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_RESERVED_2                (2U)
#define CM_CAM_VIP3_CLKCTRL_MODULEMODE_RESERVED                  (3U)

#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_SHIFT                      (16U)
#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_MASK                       (0x00030000U)
#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_DISABLE                     (3U)
#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_IDLE                        (2U)
#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_FUNC                        (0U)
#define CM_CAM_LVDSRX_CLKCTRL_IDLEST_TRANS                       (1U)

#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_SHIFT                  (0U)
#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_MASK                   (0x00000003U)
#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_DISABLED                (0U)
#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_RESERVED_1              (1U)
#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_ENABLE                  (2U)
#define CM_CAM_LVDSRX_CLKCTRL_MODULEMODE_RESERVED                (3U)

#define CM_CAM_CSI1_CLKCTRL_IDLEST_SHIFT                        (16U)
#define CM_CAM_CSI1_CLKCTRL_IDLEST_MASK                         (0x00030000U)
#define CM_CAM_CSI1_CLKCTRL_IDLEST_DISABLE                       (3U)
#define CM_CAM_CSI1_CLKCTRL_IDLEST_IDLE                          (2U)
#define CM_CAM_CSI1_CLKCTRL_IDLEST_FUNC                          (0U)
#define CM_CAM_CSI1_CLKCTRL_IDLEST_TRANS                         (1U)

#define CM_CAM_CSI1_CLKCTRL_STBYST_SHIFT                        (18U)
#define CM_CAM_CSI1_CLKCTRL_STBYST_MASK                         (0x00040000U)
#define CM_CAM_CSI1_CLKCTRL_STBYST_FUNC                          (0U)
#define CM_CAM_CSI1_CLKCTRL_STBYST_STANDBY                       (1U)

#define CM_CAM_CSI1_CLKCTRL_MODULEMODE_SHIFT                    (0U)
#define CM_CAM_CSI1_CLKCTRL_MODULEMODE_MASK                     (0x00000003U)
#define CM_CAM_CSI1_CLKCTRL_MODULEMODE_AUTO                      (1U)

#define CM_CAM_CSI2_CLKCTRL_IDLEST_SHIFT                        (16U)
#define CM_CAM_CSI2_CLKCTRL_IDLEST_MASK                         (0x00030000U)
#define CM_CAM_CSI2_CLKCTRL_IDLEST_DISABLE                       (3U)
#define CM_CAM_CSI2_CLKCTRL_IDLEST_IDLE                          (2U)
#define CM_CAM_CSI2_CLKCTRL_IDLEST_FUNC                          (0U)
#define CM_CAM_CSI2_CLKCTRL_IDLEST_TRANS                         (1U)

#define CM_CAM_CSI2_CLKCTRL_STBYST_SHIFT                        (18U)
#define CM_CAM_CSI2_CLKCTRL_STBYST_MASK                         (0x00040000U)
#define CM_CAM_CSI2_CLKCTRL_STBYST_FUNC                          (0U)
#define CM_CAM_CSI2_CLKCTRL_STBYST_STANDBY                       (1U)

#define CM_CAM_CSI2_CLKCTRL_MODULEMODE_SHIFT                    (0U)
#define CM_CAM_CSI2_CLKCTRL_MODULEMODE_MASK                     (0x00000003U)
#define CM_CAM_CSI2_CLKCTRL_MODULEMODE_AUTO                      (1U)

#ifdef __cplusplus
}
#endif

#endif /* HW_CAM_CM_CORE_H_ */

