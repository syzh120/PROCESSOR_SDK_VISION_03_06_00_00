/*
* hw_dss_vp.h
*
* Register-level header file for DSS_VP
*
* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
*
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

#ifndef HW_DSS_VP_H_
#define HW_DSS_VP_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define DSS_VP_CONFIG                                               (0x0U)
#define DSS_VP_CONTROL                                              (0x4U)
#define DSS_VP_CPR_COEF_B                                           (0x8U)
#define DSS_VP_CPR_COEF_G                                           (0xcU)
#define DSS_VP_CPR_COEF_R                                           (0x10U)
#define DSS_VP_DATA_CYCLE(n)                                        (0x14U + (((uint32_t)(n)) * 0x4U))
#define DSS_VP_GAMMA_TABLE                                          (0x20U)
#define DSS_VP_IRQENABLE                                            (0x3cU)
#define DSS_VP_IRQSTATUS                                            (0x40U)
#define DSS_VP_LINE_NUMBER                                          (0x44U)
#define DSS_VP_LINE_STATUS                                          (0x48U)
#define DSS_VP_POL_FREQ                                             (0x4cU)
#define DSS_VP_SIZE_SCREEN                                          (0x50U)
#define DSS_VP_TIMING_H                                             (0x54U)
#define DSS_VP_TIMING_V                                             (0x58U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DSS_VP_CONFIG_PIXELDATAGATED_SHIFT                                              (4U)
#define DSS_VP_CONFIG_PIXELDATAGATED_MASK                                               (0x00000010U)
#define DSS_VP_CONFIG_PIXELDATAGATED_PDGDIS                                              (0U)
#define DSS_VP_CONFIG_PIXELDATAGATED_PDGENB                                              (1U)

#define DSS_VP_CONFIG_HSYNCGATED_SHIFT                                                  (6U)
#define DSS_VP_CONFIG_HSYNCGATED_MASK                                                   (0x00000040U)
#define DSS_VP_CONFIG_HSYNCGATED_HGDIS                                                   (0U)
#define DSS_VP_CONFIG_HSYNCGATED_HGENB                                                   (1U)

#define DSS_VP_CONFIG_PIXELCLOCKGATED_SHIFT                                             (5U)
#define DSS_VP_CONFIG_PIXELCLOCKGATED_MASK                                              (0x00000020U)
#define DSS_VP_CONFIG_PIXELCLOCKGATED_PCGDIS                                             (0U)
#define DSS_VP_CONFIG_PIXELCLOCKGATED_PCGENB                                             (1U)

#define DSS_VP_CONFIG_VSYNCGATED_SHIFT                                                  (7U)
#define DSS_VP_CONFIG_VSYNCGATED_MASK                                                   (0x00000080U)
#define DSS_VP_CONFIG_VSYNCGATED_VGDIS                                                   (0U)
#define DSS_VP_CONFIG_VSYNCGATED_VGENB                                                   (1U)

#define DSS_VP_CONFIG_PIXELGATED_SHIFT                                                  (0U)
#define DSS_VP_CONFIG_PIXELGATED_MASK                                                   (0x00000001U)
#define DSS_VP_CONFIG_PIXELGATED_PCLKTOGA                                                (0U)
#define DSS_VP_CONFIG_PIXELGATED_PCLKTOGV                                                (1U)

#define DSS_VP_CONFIG_BT656ENABLE_SHIFT                                                 (20U)
#define DSS_VP_CONFIG_BT656ENABLE_MASK                                                  (0x00100000U)
#define DSS_VP_CONFIG_BT656ENABLE_DISABLE                                                (0U)
#define DSS_VP_CONFIG_BT656ENABLE_ENABLE                                                 (1U)

#define DSS_VP_CONFIG_BT1120ENABLE_SHIFT                                                (21U)
#define DSS_VP_CONFIG_BT1120ENABLE_MASK                                                 (0x00200000U)
#define DSS_VP_CONFIG_BT1120ENABLE_DISABLE                                               (0U)
#define DSS_VP_CONFIG_BT1120ENABLE_ENABLE                                                (1U)

#define DSS_VP_CONFIG_OUTPUTMODEENABLE_SHIFT                                            (22U)
#define DSS_VP_CONFIG_OUTPUTMODEENABLE_MASK                                             (0x00400000U)
#define DSS_VP_CONFIG_OUTPUTMODEENABLE_DISABLE                                           (0U)
#define DSS_VP_CONFIG_OUTPUTMODEENABLE_ENABLE                                            (1U)

#define DSS_VP_CONFIG_CPR_SHIFT                                                         (15U)
#define DSS_VP_CONFIG_CPR_MASK                                                          (0x00008000U)
#define DSS_VP_CONFIG_CPR_CPRDIS                                                         (0U)
#define DSS_VP_CONFIG_CPR_CPRENB                                                         (1U)

#define DSS_VP_CONFIG_FIDFIRST_SHIFT                                                    (23U)
#define DSS_VP_CONFIG_FIDFIRST_MASK                                                     (0x00800000U)
#define DSS_VP_CONFIG_FIDFIRST_EVEN                                                      (0U)
#define DSS_VP_CONFIG_FIDFIRST_ODD                                                       (1U)

#define DSS_VP_CONFIG_COLORCONVENABLE_SHIFT                                             (24U)
#define DSS_VP_CONFIG_COLORCONVENABLE_MASK                                              (0x01000000U)
#define DSS_VP_CONFIG_COLORCONVENABLE_COLSPCDIS                                          (0U)
#define DSS_VP_CONFIG_COLORCONVENABLE_COLSPCENB                                          (1U)

#define DSS_VP_CONFIG_FULLRANGE_SHIFT                                                   (25U)
#define DSS_VP_CONFIG_FULLRANGE_MASK                                                    (0x02000000U)
#define DSS_VP_CONFIG_FULLRANGE_LIMRANGE                                                 (0U)
#define DSS_VP_CONFIG_FULLRANGE                                                          (1U)

#define DSS_VP_CONFIG_DATAENABLEGATED_SHIFT                                             (1U)
#define DSS_VP_CONFIG_DATAENABLEGATED_MASK                                              (0x00000002U)
#define DSS_VP_CONFIG_DATAENABLEGATED_DEGDIS                                             (0U)
#define DSS_VP_CONFIG_DATAENABLEGATED_DEGENB                                             (1U)

#define DSS_VP_CONFIG_GAMMAENABLE_SHIFT                                                 (2U)
#define DSS_VP_CONFIG_GAMMAENABLE_MASK                                                  (0x00000004U)
#define DSS_VP_CONFIG_GAMMAENABLE_GAMMADIS                                               (0U)
#define DSS_VP_CONFIG_GAMMAENABLE_GAMMAENB                                               (1U)

#define DSS_VP_CONFIG_BUFFERHANDSHAKE_SHIFT                                             (16U)
#define DSS_VP_CONFIG_BUFFERHANDSHAKE_MASK                                              (0x00010000U)
#define DSS_VP_CONFIG_BUFFERHANDSHAKE_HANDCHECKDIS                                       (0U)
#define DSS_VP_CONFIG_BUFFERHANDSHAKE_HANDCHECKENB                                       (1U)

#define DSS_VP_CONFIG_HDMIMODE_SHIFT                                                    (3U)
#define DSS_VP_CONFIG_HDMIMODE_MASK                                                     (0x00000008U)
#define DSS_VP_CONFIG_HDMIMODE_HDMIMODEDIS                                               (0U)
#define DSS_VP_CONFIG_HDMIMODE_HDMIMODEEN                                                (1U)

#define DSS_VP_CONFIG_EXTERNALSYNCEN_SHIFT                                              (8U)
#define DSS_VP_CONFIG_EXTERNALSYNCEN_MASK                                               (0x00000100U)
#define DSS_VP_CONFIG_EXTERNALSYNCEN_DISABLE                                             (0U)
#define DSS_VP_CONFIG_EXTERNALSYNCEN_ENABLE                                              (1U)

#define DSS_VP_CONTROL_STDITHERENABLE_SHIFT                                             (7U)
#define DSS_VP_CONTROL_STDITHERENABLE_MASK                                              (0x00000080U)
#define DSS_VP_CONTROL_STDITHERENABLE_STDITHDIS                                          (0U)
#define DSS_VP_CONTROL_STDITHERENABLE_STDITHENB                                          (1U)

#define DSS_VP_CONTROL_DATALINES_SHIFT                                                  (8U)
#define DSS_VP_CONTROL_DATALINES_MASK                                                   (0x00000700U)
#define DSS_VP_CONTROL_DATALINES_OALSB12B                                                (0U)
#define DSS_VP_CONTROL_DATALINES_OALSB16B                                                (1U)
#define DSS_VP_CONTROL_DATALINES_OALSB18B                                                (2U)
#define DSS_VP_CONTROL_DATALINES_OALSB24B                                                (3U)
#define DSS_VP_CONTROL_DATALINES_OALSB30B                                                (4U)
#define DSS_VP_CONTROL_DATALINES_OALSB36B                                                (5U)

#define DSS_VP_CONTROL_STALLMODE_SHIFT                                                  (11U)
#define DSS_VP_CONTROL_STALLMODE_MASK                                                   (0x00000800U)
#define DSS_VP_CONTROL_STALLMODE_NMODE                                                   (0U)
#define DSS_VP_CONTROL_STALLMODE_RFBIMODE                                                (1U)

#define DSS_VP_CONTROL_GOBIT_SHIFT                                                      (5U)
#define DSS_VP_CONTROL_GOBIT_MASK                                                       (0x00000020U)
#define DSS_VP_CONTROL_GOBIT_HFUISR                                                      (0U)
#define DSS_VP_CONTROL_GOBIT_UFPSR                                                       (1U)

#define DSS_VP_CONTROL_VPENABLE_SHIFT                                                   (0U)
#define DSS_VP_CONTROL_VPENABLE_MASK                                                    (0x00000001U)
#define DSS_VP_CONTROL_VPENABLE_LCDOPDIS                                                 (0U)
#define DSS_VP_CONTROL_VPENABLE_LCDOPENB                                                 (1U)

#define DSS_VP_CONTROL_SPATIALTEMPORALDITHERINGFRAMES_SHIFT                             (30U)
#define DSS_VP_CONTROL_SPATIALTEMPORALDITHERINGFRAMES_MASK                              (0xc0000000U)
#define DSS_VP_CONTROL_SPATIALTEMPORALDITHERINGFRAMES_ONEFRAME                           (0U)
#define DSS_VP_CONTROL_SPATIALTEMPORALDITHERINGFRAMES_TWOFRAMES                          (1U)
#define DSS_VP_CONTROL_SPATIALTEMPORALDITHERINGFRAMES_FOURFRAMES                         (2U)
#define DSS_VP_CONTROL_SPATIALTEMPORALDITHERINGFRAMES_RESERVED                           (3U)

#define DSS_VP_CONTROL_TDMUNUSEDBITS_SHIFT                                              (25U)
#define DSS_VP_CONTROL_TDMUNUSEDBITS_MASK                                               (0x06000000U)
#define DSS_VP_CONTROL_TDMUNUSEDBITS_LOWLEVEL                                            (0U)
#define DSS_VP_CONTROL_TDMUNUSEDBITS_HIGHLEVEL                                           (1U)
#define DSS_VP_CONTROL_TDMUNUSEDBITS_UNCHANGED                                           (2U)
#define DSS_VP_CONTROL_TDMUNUSEDBITS_RES                                                 (3U)

#define DSS_VP_CONTROL_TDMENABLE_SHIFT                                                  (20U)
#define DSS_VP_CONTROL_TDMENABLE_MASK                                                   (0x00100000U)
#define DSS_VP_CONTROL_TDMENABLE_TDMDIS                                                  (0U)
#define DSS_VP_CONTROL_TDMENABLE_TDMENB                                                  (1U)

#define DSS_VP_CONTROL_TDMPARALLELMODE_SHIFT                                            (21U)
#define DSS_VP_CONTROL_TDMPARALLELMODE_MASK                                             (0x00600000U)
#define DSS_VP_CONTROL_TDMPARALLELMODE_8BPARAINT                                         (0U)
#define DSS_VP_CONTROL_TDMPARALLELMODE_9BPARAINT                                         (1U)
#define DSS_VP_CONTROL_TDMPARALLELMODE_12BPARAINT                                        (2U)
#define DSS_VP_CONTROL_TDMPARALLELMODE_16BPARAINT                                        (3U)

#define DSS_VP_CONTROL_TDMCYCLEFORMAT_SHIFT                                             (23U)
#define DSS_VP_CONTROL_TDMCYCLEFORMAT_MASK                                              (0x01800000U)
#define DSS_VP_CONTROL_TDMCYCLEFORMAT_1CYCPERPIX                                         (0U)
#define DSS_VP_CONTROL_TDMCYCLEFORMAT_2CYCPERPIX                                         (1U)
#define DSS_VP_CONTROL_TDMCYCLEFORMAT_3CYCPERPIX                                         (2U)
#define DSS_VP_CONTROL_TDMCYCLEFORMAT_3CYCPER2PIX                                        (3U)

#define DSS_VP_CONTROL_HT_SHIFT                                                         (14U)
#define DSS_VP_CONTROL_HT_MASK                                                          (0x0001c000U)

#define DSS_VP_CONTROL_VPPROGLINENUMBERMODULO_SHIFT                                     (1U)
#define DSS_VP_CONTROL_VPPROGLINENUMBERMODULO_MASK                                      (0x00000002U)
#define DSS_VP_CONTROL_VPPROGLINENUMBERMODULO_MODDIS                                     (0U)
#define DSS_VP_CONTROL_VPPROGLINENUMBERMODULO_MODEN                                      (1U)

#define DSS_VP_CPR_COEF_B_BB_SHIFT                                                      (0U)
#define DSS_VP_CPR_COEF_B_BB_MASK                                                       (0x000003ffU)

#define DSS_VP_CPR_COEF_B_BR_SHIFT                                                      (22U)
#define DSS_VP_CPR_COEF_B_BR_MASK                                                       (0xffc00000U)

#define DSS_VP_CPR_COEF_B_BG_SHIFT                                                      (11U)
#define DSS_VP_CPR_COEF_B_BG_MASK                                                       (0x001ff800U)

#define DSS_VP_CPR_COEF_G_GB_SHIFT                                                      (0U)
#define DSS_VP_CPR_COEF_G_GB_MASK                                                       (0x000003ffU)

#define DSS_VP_CPR_COEF_G_GR_SHIFT                                                      (22U)
#define DSS_VP_CPR_COEF_G_GR_MASK                                                       (0xffc00000U)

#define DSS_VP_CPR_COEF_G_GG_SHIFT                                                      (11U)
#define DSS_VP_CPR_COEF_G_GG_MASK                                                       (0x001ff800U)

#define DSS_VP_CPR_COEF_R_RB_SHIFT                                                      (0U)
#define DSS_VP_CPR_COEF_R_RB_MASK                                                       (0x000003ffU)

#define DSS_VP_CPR_COEF_R_RR_SHIFT                                                      (22U)
#define DSS_VP_CPR_COEF_R_RR_MASK                                                       (0xffc00000U)

#define DSS_VP_CPR_COEF_R_RG_SHIFT                                                      (11U)
#define DSS_VP_CPR_COEF_R_RG_MASK                                                       (0x001ff800U)

#define DSS_VP_DATA_CYCLE_NBBITSPIXEL2_SHIFT                                            (16U)
#define DSS_VP_DATA_CYCLE_NBBITSPIXEL2_MASK                                             (0x001f0000U)

#define DSS_VP_DATA_CYCLE_BITALIGNMENTPIXEL1_SHIFT                                      (8U)
#define DSS_VP_DATA_CYCLE_BITALIGNMENTPIXEL1_MASK                                       (0x00000f00U)

#define DSS_VP_DATA_CYCLE_NBBITSPIXEL1_SHIFT                                            (0U)
#define DSS_VP_DATA_CYCLE_NBBITSPIXEL1_MASK                                             (0x0000001fU)

#define DSS_VP_DATA_CYCLE_BITALIGNMENTPIXEL2_SHIFT                                      (24U)
#define DSS_VP_DATA_CYCLE_BITALIGNMENTPIXEL2_MASK                                       (0x0f000000U)

#define DSS_VP_GAMMA_TABLE_VALUE_R_SHIFT                                                (16U)
#define DSS_VP_GAMMA_TABLE_VALUE_R_MASK                                                 (0x00ff0000U)

#define DSS_VP_GAMMA_TABLE_INDEX_SHIFT                                                  (24U)
#define DSS_VP_GAMMA_TABLE_INDEX_MASK                                                   (0xff000000U)

#define DSS_VP_GAMMA_TABLE_VALUE_G_SHIFT                                                (8U)
#define DSS_VP_GAMMA_TABLE_VALUE_G_MASK                                                 (0x0000ff00U)

#define DSS_VP_GAMMA_TABLE_VALUE_B_SHIFT                                                (0U)
#define DSS_VP_GAMMA_TABLE_VALUE_B_MASK                                                 (0x000000ffU)

#define DSS_VP_IRQENABLE_VPVSYNC_ODD_EN_SHIFT                                           (2U)
#define DSS_VP_IRQENABLE_VPVSYNC_ODD_EN_MASK                                            (0x00000004U)
#define DSS_VP_IRQENABLE_VPVSYNC_ODD_EN_MASKED                                           (0U)
#define DSS_VP_IRQENABLE_VPVSYNC_ODD_EN_GENINT                                           (1U)

#define DSS_VP_IRQENABLE_VPFRAMEDONE_EN_SHIFT                                           (0U)
#define DSS_VP_IRQENABLE_VPFRAMEDONE_EN_MASK                                            (0x00000001U)
#define DSS_VP_IRQENABLE_VPFRAMEDONE_EN_MASKED                                           (0U)
#define DSS_VP_IRQENABLE_VPFRAMEDONE_EN_GENINT                                           (1U)

#define DSS_VP_IRQENABLE_VPVSYNC_EN_SHIFT                                               (1U)
#define DSS_VP_IRQENABLE_VPVSYNC_EN_MASK                                                (0x00000002U)
#define DSS_VP_IRQENABLE_VPVSYNC_EN_MASKED                                               (0U)
#define DSS_VP_IRQENABLE_VPVSYNC_EN_GENINT                                               (1U)

#define DSS_VP_IRQENABLE_VPSYNCLOST_EN_SHIFT                                            (4U)
#define DSS_VP_IRQENABLE_VPSYNCLOST_EN_MASK                                             (0x00000010U)
#define DSS_VP_IRQENABLE_VPSYNCLOST_EN_MASKED                                            (0U)
#define DSS_VP_IRQENABLE_VPSYNCLOST_EN_GENINT                                            (1U)

#define DSS_VP_IRQENABLE_VPPROGRAMMEDLINENUMBER_EN_SHIFT                                (3U)
#define DSS_VP_IRQENABLE_VPPROGRAMMEDLINENUMBER_EN_MASK                                 (0x00000008U)
#define DSS_VP_IRQENABLE_VPPROGRAMMEDLINENUMBER_EN_MASKED                                (0U)
#define DSS_VP_IRQENABLE_VPPROGRAMMEDLINENUMBER_EN_GENINT                                (1U)

#define DSS_VP_IRQSTATUS_VPSYNCLOST_IRQ_SHIFT                                           (4U)
#define DSS_VP_IRQSTATUS_VPSYNCLOST_IRQ_MASK                                            (0x00000010U)
#define DSS_VP_IRQSTATUS_VPSYNCLOST_IRQ_FALSE                                            (0U)
#define DSS_VP_IRQSTATUS_VPSYNCLOST_IRQ_TRUE                                             (1U)

#define DSS_VP_IRQSTATUS_VPPROGRAMMEDLINENUMBER_IRQ_SHIFT                               (3U)
#define DSS_VP_IRQSTATUS_VPPROGRAMMEDLINENUMBER_IRQ_MASK                                (0x00000008U)
#define DSS_VP_IRQSTATUS_VPPROGRAMMEDLINENUMBER_IRQ_FALSE                                (0U)
#define DSS_VP_IRQSTATUS_VPPROGRAMMEDLINENUMBER_IRQ_TRUE                                 (1U)

#define DSS_VP_IRQSTATUS_VPFRAMEDONE_IRQ_SHIFT                                          (0U)
#define DSS_VP_IRQSTATUS_VPFRAMEDONE_IRQ_MASK                                           (0x00000001U)
#define DSS_VP_IRQSTATUS_VPFRAMEDONE_IRQ_FALSE                                           (0U)
#define DSS_VP_IRQSTATUS_VPFRAMEDONE_IRQ_TRUE                                            (1U)

#define DSS_VP_IRQSTATUS_VPVSYNC_IRQ_SHIFT                                              (1U)
#define DSS_VP_IRQSTATUS_VPVSYNC_IRQ_MASK                                               (0x00000002U)
#define DSS_VP_IRQSTATUS_VPVSYNC_IRQ_FALSE                                               (0U)
#define DSS_VP_IRQSTATUS_VPVSYNC_IRQ_TRUE                                                (1U)

#define DSS_VP_IRQSTATUS_VPVSYNC_ODD_IRQ_SHIFT                                          (2U)
#define DSS_VP_IRQSTATUS_VPVSYNC_ODD_IRQ_MASK                                           (0x00000004U)
#define DSS_VP_IRQSTATUS_VPVSYNC_ODD_IRQ_FALSE                                           (0U)
#define DSS_VP_IRQSTATUS_VPVSYNC_ODD_IRQ_TRUE                                            (1U)

#define DSS_VP_LINE_NUMBER_LINENUMBER_SHIFT                                             (0U)
#define DSS_VP_LINE_NUMBER_LINENUMBER_MASK                                              (0x00000fffU)

#define DSS_VP_LINE_STATUS_LINENUMBER_SHIFT                                             (0U)
#define DSS_VP_LINE_STATUS_LINENUMBER_MASK                                              (0x00000fffU)

#define DSS_VP_POL_FREQ_IHS_SHIFT                                                       (13U)
#define DSS_VP_POL_FREQ_IHS_MASK                                                        (0x00002000U)
#define DSS_VP_POL_FREQ_IHS_LCKPINAH                                                     (0U)
#define DSS_VP_POL_FREQ_IHS_LCKPINAL                                                     (1U)

#define DSS_VP_POL_FREQ_IEO_SHIFT                                                       (15U)
#define DSS_VP_POL_FREQ_IEO_MASK                                                        (0x00008000U)
#define DSS_VP_POL_FREQ_IEO_ACBAHIGH                                                     (0U)
#define DSS_VP_POL_FREQ_IEO_ACBALOW                                                      (1U)

#define DSS_VP_POL_FREQ_ONOFF_SHIFT                                                     (17U)
#define DSS_VP_POL_FREQ_ONOFF_MASK                                                      (0x00020000U)
#define DSS_VP_POL_FREQ_ONOFF_DOPEDPCK                                                   (0U)
#define DSS_VP_POL_FREQ_ONOFF_DBIT16                                                     (1U)

#define DSS_VP_POL_FREQ_IVS_SHIFT                                                       (12U)
#define DSS_VP_POL_FREQ_IVS_MASK                                                        (0x00001000U)
#define DSS_VP_POL_FREQ_IVS_FCKPINAH                                                     (0U)
#define DSS_VP_POL_FREQ_IVS_FCKPINAL                                                     (1U)

#define DSS_VP_POL_FREQ_IPC_SHIFT                                                       (14U)
#define DSS_VP_POL_FREQ_IPC_MASK                                                        (0x00004000U)
#define DSS_VP_POL_FREQ_IPC_DRPCK                                                        (0U)
#define DSS_VP_POL_FREQ_IPC_DFPCK                                                        (1U)

#define DSS_VP_POL_FREQ_RF_SHIFT                                                        (16U)
#define DSS_VP_POL_FREQ_RF_MASK                                                         (0x00010000U)
#define DSS_VP_POL_FREQ_RF_DFEDPCK                                                       (0U)
#define DSS_VP_POL_FREQ_RF_DRIEDPCK                                                      (1U)

#define DSS_VP_POL_FREQ_ALIGN_SHIFT                                                     (18U)
#define DSS_VP_POL_FREQ_ALIGN_MASK                                                      (0x00040000U)
#define DSS_VP_POL_FREQ_ALIGN_NOTALIGNED                                                 (0U)
#define DSS_VP_POL_FREQ_ALIGN_ALIGNED                                                    (1U)

#define DSS_VP_SIZE_SCREEN_LPP_SHIFT                                                    (16U)
#define DSS_VP_SIZE_SCREEN_LPP_MASK                                                     (0x0fff0000U)

#define DSS_VP_SIZE_SCREEN_PPL_SHIFT                                                    (0U)
#define DSS_VP_SIZE_SCREEN_PPL_MASK                                                     (0x00000fffU)

#define DSS_VP_SIZE_SCREEN_DELTA_LPP_SHIFT                                              (14U)
#define DSS_VP_SIZE_SCREEN_DELTA_LPP_MASK                                               (0x0000c000U)
#define DSS_VP_SIZE_SCREEN_DELTA_LPP_SAME                                                (0U)
#define DSS_VP_SIZE_SCREEN_DELTA_LPP_PLUSONE                                             (1U)
#define DSS_VP_SIZE_SCREEN_DELTA_LPP_MINUSONE                                            (2U)

#define DSS_VP_TIMING_H_HBP_SHIFT                                                       (20U)
#define DSS_VP_TIMING_H_HBP_MASK                                                        (0xfff00000U)

#define DSS_VP_TIMING_H_HFP_SHIFT                                                       (8U)
#define DSS_VP_TIMING_H_HFP_MASK                                                        (0x000fff00U)

#define DSS_VP_TIMING_H_HSW_SHIFT                                                       (0U)
#define DSS_VP_TIMING_H_HSW_MASK                                                        (0x000000ffU)

#define DSS_VP_TIMING_V_VBP_SHIFT                                                       (20U)
#define DSS_VP_TIMING_V_VBP_MASK                                                        (0xfff00000U)

#define DSS_VP_TIMING_V_VFP_SHIFT                                                       (8U)
#define DSS_VP_TIMING_V_VFP_MASK                                                        (0x000fff00U)

#define DSS_VP_TIMING_V_VSW_SHIFT                                                       (0U)
#define DSS_VP_TIMING_V_VSW_MASK                                                        (0x000000ffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DSS_VP_H_ */

