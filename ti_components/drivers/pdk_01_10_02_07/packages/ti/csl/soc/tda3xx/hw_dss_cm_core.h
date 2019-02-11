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
 *  \file   hw_dss_cm_core.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_DSS_CM_CORE_H_
#define HW_DSS_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
 * Register Definitions
 ****************************************************************************************************/

#define CM_DSS_CLKSTCTRL                                            (0x0U)
#define CM_DSS_STATICDEP                                            (0x4U)
#define CM_DSS_DYNAMICDEP                                           (0x8U)
#define CM_DSS_DSS_CLKCTRL                                          (0x20U)
#define CM_DSS_SDVENC_CLKCTRL                                       (0x3cU)

/****************************************************************************************************
 * Field Definition Macros
 ****************************************************************************************************/

#define CM_DSS_CLKSTCTRL_CLKTRCTRL_SHIFT                           (0U)
#define CM_DSS_CLKSTCTRL_CLKTRCTRL_MASK                            (0x00000003U)
#define CM_DSS_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                         (0U)
#define CM_DSS_CLKSTCTRL_CLKTRCTRL_SW_SLEEP                         (1U)
#define CM_DSS_CLKSTCTRL_CLKTRCTRL_SW_WKUP                          (2U)
#define CM_DSS_CLKSTCTRL_CLKTRCTRL_HW_AUTO                          (3U)

#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_L3_GICLK_SHIFT            (8U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_L3_GICLK_MASK             (0x00000100U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_L3_GICLK_INACT             (0U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_L3_GICLK_ACT               (1U)

#define CM_DSS_CLKSTCTRL_RESERVED_SHIFT                            (2U)
#define CM_DSS_CLKSTCTRL_RESERVED_MASK                             (0x000000fcU)

#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_GFCLK_SHIFT               (9U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_GFCLK_MASK                (0x00000200U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_GFCLK_INACT                (0U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_GFCLK_ACT                  (1U)

#define CM_DSS_CLKSTCTRL_CLKACTIVITY_VIDEO1_DPLL_CLK_SHIFT         (10U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_VIDEO1_DPLL_CLK_MASK          (0x00000400U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_VIDEO1_DPLL_CLK_INACT          (0U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_VIDEO1_DPLL_CLK_ACT            (1U)

#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_DPLL_CLK_SHIFT           (11U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_DPLL_CLK_MASK            (0x00000800U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_DPLL_CLK_INACT            (0U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_DPLL_CLK_ACT              (1U)

#define CM_DSS_CLKSTCTRL_CLKACTIVITY_VIDEO2_DPLL_CLK_SHIFT         (12U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_VIDEO2_DPLL_CLK_MASK          (0x00001000U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_VIDEO2_DPLL_CLK_INACT          (0U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_VIDEO2_DPLL_CLK_ACT            (1U)

#define CM_DSS_CLKSTCTRL_CLKACTIVITY_BB2D_GFCLK_SHIFT              (13U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_BB2D_GFCLK_MASK               (0x00002000U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_BB2D_GFCLK_INACT               (0U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_BB2D_GFCLK_ACT                 (1U)

#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_L4_GICLK_SHIFT            (15U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_L4_GICLK_MASK             (0x00008000U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_L4_GICLK_INACT             (0U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_L4_GICLK_ACT               (1U)

#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_SYS_GFCLK_SHIFT           (16U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_SYS_GFCLK_MASK            (0x00010000U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_SYS_GFCLK_INACT            (0U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_DSS_SYS_GFCLK_ACT              (1U)

#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_CEC_GFCLK_SHIFT          (17U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_CEC_GFCLK_MASK           (0x00020000U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_CEC_GFCLK_INACT           (0U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_CEC_GFCLK_ACT             (1U)

#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_PHY_GFCLK_SHIFT          (18U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_PHY_GFCLK_MASK           (0x00040000U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_PHY_GFCLK_INACT           (0U)
#define CM_DSS_CLKSTCTRL_CLKACTIVITY_HDMI_PHY_GFCLK_ACT             (1U)

#define CM_DSS_STATICDEP_EMIF_STATDEP_SHIFT                        (4U)
#define CM_DSS_STATICDEP_EMIF_STATDEP_MASK                         (0x00000010U)
#define CM_DSS_STATICDEP_EMIF_STATDEP_ENABLED                       (1U)
#define CM_DSS_STATICDEP_EMIF_STATDEP_DISABLED                      (0U)

#define CM_DSS_STATICDEP_L3MAIN1_STATDEP_SHIFT                     (5U)
#define CM_DSS_STATICDEP_L3MAIN1_STATDEP_MASK                      (0x00000020U)
#define CM_DSS_STATICDEP_L3MAIN1_STATDEP_ENABLED                    (1U)

#define CM_DSS_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT                     (5U)
#define CM_DSS_DYNAMICDEP_L3MAIN1_DYNDEP_MASK                      (0x00000020U)
#define CM_DSS_DYNAMICDEP_L3MAIN1_DYNDEP_DISABLED                   (0U)

#define CM_DSS_DSS_CLKCTRL_IDLEST_SHIFT                            (16U)
#define CM_DSS_DSS_CLKCTRL_IDLEST_MASK                             (0x00030000U)
#define CM_DSS_DSS_CLKCTRL_IDLEST_DISABLE                           (3U)
#define CM_DSS_DSS_CLKCTRL_IDLEST_IDLE                              (2U)
#define CM_DSS_DSS_CLKCTRL_IDLEST_FUNC                              (0U)
#define CM_DSS_DSS_CLKCTRL_IDLEST_TRANS                             (1U)

#define CM_DSS_DSS_CLKCTRL_STBYST_SHIFT                            (18U)
#define CM_DSS_DSS_CLKCTRL_STBYST_MASK                             (0x00040000U)
#define CM_DSS_DSS_CLKCTRL_STBYST_FUNC                              (0U)
#define CM_DSS_DSS_CLKCTRL_STBYST_STANDBY                           (1U)

#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_DSSCLK_SHIFT                  (8U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_DSSCLK_MASK                   (0x00000100U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_DSSCLK_FCLK_EN                 (1U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_DSSCLK_FCLK_DIS                (0U)

#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_48MHZ_CLK_SHIFT               (9U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_48MHZ_CLK_MASK                (0x00000200U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_48MHZ_CLK_FCLK_EN              (1U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_48MHZ_CLK_FCLK_DIS             (0U)

#define CM_DSS_DSS_CLKCTRL_MODULEMODE_SHIFT                        (0U)
#define CM_DSS_DSS_CLKCTRL_MODULEMODE_MASK                         (0x00000003U)
#define CM_DSS_DSS_CLKCTRL_MODULEMODE_DISABLED                      (0U)
#define CM_DSS_DSS_CLKCTRL_MODULEMODE_RESERVED_1                    (1U)
#define CM_DSS_DSS_CLKCTRL_MODULEMODE_ENABLED                       (2U)
#define CM_DSS_DSS_CLKCTRL_MODULEMODE_RESERVED                      (3U)

#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_HDMI_CLK_SHIFT                (10U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_HDMI_CLK_MASK                 (0x00000400U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_HDMI_CLK_FCLK_EN               (1U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_HDMI_CLK_FCLK_DIS              (0U)

#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_32KHZ_CLK_SHIFT               (11U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_32KHZ_CLK_MASK                (0x00000800U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_32KHZ_CLK_FCLK_EN              (1U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_32KHZ_CLK_FCLK_DIS             (0U)

#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_VIDEO1_CLK_SHIFT              (12U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_VIDEO1_CLK_MASK               (0x00001000U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_VIDEO1_CLK_FCLK_EN             (1U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_VIDEO1_CLK_FCLK_DIS            (0U)

#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_VIDEO2_CLK_SHIFT              (13U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_VIDEO2_CLK_MASK               (0x00002000U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_VIDEO2_CLK_FCLK_EN             (1U)
#define CM_DSS_DSS_CLKCTRL_OPTFCLKEN_VIDEO2_CLK_FCLK_DIS            (0U)

#define CM_DSS_SDVENC_CLKCTRL_IDLEST_SHIFT                         (16U)
#define CM_DSS_SDVENC_CLKCTRL_IDLEST_MASK                          (0x00030000U)
#define CM_DSS_SDVENC_CLKCTRL_IDLEST_DISABLE                        (3U)
#define CM_DSS_SDVENC_CLKCTRL_IDLEST_IDLE                           (2U)
#define CM_DSS_SDVENC_CLKCTRL_IDLEST_FUNC                           (0U)
#define CM_DSS_SDVENC_CLKCTRL_IDLEST_TRANS                          (1U)

#define CM_DSS_SDVENC_CLKCTRL_MODULEMODE_SHIFT                     (0U)
#define CM_DSS_SDVENC_CLKCTRL_MODULEMODE_MASK                      (0x00000003U)
#define CM_DSS_SDVENC_CLKCTRL_MODULEMODE_DISABLED                   (0U)
#define CM_DSS_SDVENC_CLKCTRL_MODULEMODE_RESERVED_1                 (1U)
#define CM_DSS_SDVENC_CLKCTRL_MODULEMODE_ENABLE                     (2U)
#define CM_DSS_SDVENC_CLKCTRL_MODULEMODE_RESERVED                   (3U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DSS_CM_CORE_H_ */

