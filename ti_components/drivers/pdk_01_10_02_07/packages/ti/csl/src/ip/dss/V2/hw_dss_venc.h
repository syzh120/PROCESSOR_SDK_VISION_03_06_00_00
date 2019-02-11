/*
* hw_dss_venc.h
*
* Register-level header file for DSS_VENC
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

#ifndef HW_DSS_VENC_H_
#define HW_DSS_VENC_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define DSS_VENC_REV_ID                                             (0x0U)
#define DSS_VENC_STATUS                                             (0x4U)
#define DSS_VENC_F_CONTROL                                          (0x8U)
#define DSS_VENC_VIDOUT_CTRL                                        (0x10U)
#define DSS_VENC_SYNC_CTRL                                          (0x14U)
#define DSS_VENC_LLEN                                               (0x1cU)
#define DSS_VENC_FLENS                                              (0x20U)
#define DSS_VENC_HFLTR_CTRL                                         (0x24U)
#define DSS_VENC_CC_CARR_WSS                                        (0x28U)
#define DSS_VENC_C_PHASE                                            (0x2cU)
#define DSS_VENC_GAIN_U                                             (0x30U)
#define DSS_VENC_GAIN_V                                             (0x34U)
#define DSS_VENC_GAIN_Y                                             (0x38U)
#define DSS_VENC_BLACK_LEVEL                                        (0x3cU)
#define DSS_VENC_BLANK_LEVEL                                        (0x40U)
#define DSS_VENC_X_COLOR                                            (0x44U)
#define DSS_VENC_M_CONTROL                                          (0x48U)
#define DSS_VENC_BSTAMP_WSS_DATA                                    (0x4cU)
#define DSS_VENC_S_CARR                                             (0x50U)
#define DSS_VENC_LINE21                                             (0x54U)
#define DSS_VENC_LN_SEL                                             (0x58U)
#define DSS_VENC_L21_WC_CTL                                         (0x5cU)
#define DSS_VENC_HTRIGGER_VTRIGGER                                  (0x60U)
#define DSS_VENC_SAVID_EAVID                                        (0x64U)
#define DSS_VENC_FLEN_FAL                                           (0x68U)
#define DSS_VENC_LAL_PHASE_RESET                                    (0x6cU)
#define DSS_VENC_HS_INT_START_STOP_X                                (0x70U)
#define DSS_VENC_HS_EXT_START_STOP_X                                (0x74U)
#define DSS_VENC_VS_INT_START_X                                     (0x78U)
#define DSS_VENC_VS_INT_STOP_X_START_Y                              (0x7cU)
#define DSS_VENC_VS_INT_STOP_Y_EXT_START_X                          (0x80U)
#define DSS_VENC_VS_EXT_STOP_X_START_Y                              (0x84U)
#define DSS_VENC_VS_EXT_STOP_Y                                      (0x88U)
#define DSS_VENC_AVID_START_STOP_X                                  (0x90U)
#define DSS_VENC_AVID_START_STOP_Y                                  (0x94U)
#define DSS_VENC_FID_INT_START_X_Y                                  (0xa0U)
#define DSS_VENC_FID_INT_OFFSET_Y_EXT_START_X                       (0xa4U)
#define DSS_VENC_FID_EXT_START_Y_OFFSET                             (0xa8U)
#define DSS_VENC_TVDETGP_INT_START_STOP_X                           (0xb0U)
#define DSS_VENC_TVDETGP_INT_START_STOP_Y                           (0xb4U)
#define DSS_VENC_GEN_CTRL                                           (0xb8U)
#define DSS_VENC_OUTPUT_CONTROL                                     (0xc4U)
#define DSS_VENC_OUTPUT_TEST                                        (0xc8U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define DSS_VENC_REV_ID_SHIFT                                                           (0U)
#define DSS_VENC_REV_ID_MASK                                                            (0x000000ffU)

#define DSS_VENC_STATUS_FSQ_SHIFT                                                       (0U)
#define DSS_VENC_STATUS_FSQ_MASK                                                        (0x00000007U)
#define DSS_VENC_STATUS_FSQ_ODD                                                          (0U)
#define DSS_VENC_STATUS_FSQ_EVEN                                                         (1U)

#define DSS_VENC_STATUS_CCO_SHIFT                                                       (3U)
#define DSS_VENC_STATUS_CCO_MASK                                                        (0x00000008U)

#define DSS_VENC_STATUS_CCE_SHIFT                                                       (4U)
#define DSS_VENC_STATUS_CCE_MASK                                                        (0x00000010U)

#define DSS_VENC_F_CONTROL_FMT_SHIFT                                                    (0U)
#define DSS_VENC_F_CONTROL_FMT_MASK                                                     (0x00000003U)
#define DSS_VENC_F_CONTROL_FMT_RGB24B                                                    (0U)
#define DSS_VENC_F_CONTROL_FMT_YCBCR24B                                                  (1U)
#define DSS_VENC_F_CONTROL_FMT_YCBCR16B                                                  (2U)
#define DSS_VENC_F_CONTROL_FMT_YCBCR8B                                                   (3U)

#define DSS_VENC_F_CONTROL_BCOLOR_SHIFT                                                 (2U)
#define DSS_VENC_F_CONTROL_BCOLOR_MASK                                                  (0x0000001cU)
#define DSS_VENC_F_CONTROL_BCOLOR_BLACK                                                  (0U)
#define DSS_VENC_F_CONTROL_BCOLOR_BLUE                                                   (1U)
#define DSS_VENC_F_CONTROL_BCOLOR_RED                                                    (2U)
#define DSS_VENC_F_CONTROL_BCOLOR_MAGENTA                                                (3U)
#define DSS_VENC_F_CONTROL_BCOLOR_GREEN                                                  (4U)
#define DSS_VENC_F_CONTROL_BCOLOR_CYAN                                                   (5U)
#define DSS_VENC_F_CONTROL_BCOLOR_YELLOW                                                 (6U)
#define DSS_VENC_F_CONTROL_BCOLOR_WHITE                                                  (7U)

#define DSS_VENC_F_CONTROL_RGBF_SHIFT                                                   (5U)
#define DSS_VENC_F_CONTROL_RGBF_MASK                                                    (0x00000020U)
#define DSS_VENC_F_CONTROL_RGBF_RANGEMISC                                                (1U)
#define DSS_VENC_F_CONTROL_RGBF_RANGE0_255                                               (0U)

#define DSS_VENC_F_CONTROL_SVDS_SHIFT                                                   (6U)
#define DSS_VENC_F_CONTROL_SVDS_MASK                                                    (0x000000c0U)
#define DSS_VENC_F_CONTROL_SVDS_EXTERNALVIDEOSOURCE                                      (0U)
#define DSS_VENC_F_CONTROL_SVDS_INTERNALCOLORBAR                                         (1U)
#define DSS_VENC_F_CONTROL_SVDS_BACKGROUNDCOLOR                                          (2U)
#define DSS_VENC_F_CONTROL_SVDS_RESERVED                                                 (3U)

#define DSS_VENC_F_CONTROL_RESET_SHIFT                                                  (8U)
#define DSS_VENC_F_CONTROL_RESET_MASK                                                   (0x00000100U)
#define DSS_VENC_F_CONTROL_RESET_NOEFFECT                                                (0U)
#define DSS_VENC_F_CONTROL_RESET_RESETENCODER                                            (1U)

#define DSS_VENC_VIDOUT_CTRL_MHZ_27_54_SHIFT                                            (0U)
#define DSS_VENC_VIDOUT_CTRL_MHZ_27_54_MASK                                             (0x00000001U)
#define DSS_VENC_VIDOUT_CTRL_MHZ_27_54_DISABLE                                                  (0U)
#define DSS_VENC_VIDOUT_CTRL_MHZ_27_54_ENABLE                                                  (1U)

#define DSS_VENC_SYNC_CTRL_FID_POL_SHIFT                                                (6U)
#define DSS_VENC_SYNC_CTRL_FID_POL_MASK                                                 (0x00000040U)
#define DSS_VENC_SYNC_CTRL_FID_POL_ODD0EVEN1                                             (0U)
#define DSS_VENC_SYNC_CTRL_FID_POL_ODD1EVEN0                                             (1U)

#define DSS_VENC_SYNC_CTRL_M_S_SHIFT                                                    (7U)
#define DSS_VENC_SYNC_CTRL_M_S_MASK                                                     (0x00000080U)
#define DSS_VENC_SYNC_CTRL_M_S_SYNCMASTER                                                (0U)
#define DSS_VENC_SYNC_CTRL_M_S_SYNCSLAVE                                                 (1U)

#define DSS_VENC_SYNC_CTRL_HBLKM_SHIFT                                                  (8U)
#define DSS_VENC_SYNC_CTRL_HBLKM_MASK                                                   (0x00000300U)
#define DSS_VENC_SYNC_CTRL_HBLKM_EXTERNAL                                                (2U)
#define DSS_VENC_SYNC_CTRL_HBLKM_RESERVED                                                (3U)
#define DSS_VENC_SYNC_CTRL_HBLKM_INTERNALDEFAULT                                         (0U)
#define DSS_VENC_SYNC_CTRL_HBLKM_INTERNALPROGRAMMABLE                                    (1U)

#define DSS_VENC_SYNC_CTRL_VBLKM_SHIFT                                                  (10U)
#define DSS_VENC_SYNC_CTRL_VBLKM_MASK                                                   (0x00000c00U)
#define DSS_VENC_SYNC_CTRL_VBLKM_INTERNALDEFAULT                                         (0U)
#define DSS_VENC_SYNC_CTRL_VBLKM_INTERNALDEFAULTANDINTERNALPROGRAMMABLE                  (1U)
#define DSS_VENC_SYNC_CTRL_VBLKM_RESERVED0X2                                             (2U)
#define DSS_VENC_SYNC_CTRL_VBLKM_RESERVED0X3                                             (3U)

#define DSS_VENC_SYNC_CTRL_NBLNKS_SHIFT                                                 (12U)
#define DSS_VENC_SYNC_CTRL_NBLNKS_MASK                                                  (0x00001000U)
#define DSS_VENC_SYNC_CTRL_NBLNKS_ENABLED                                                (0U)
#define DSS_VENC_SYNC_CTRL_NBLNKS_DISABLED                                               (1U)

#define DSS_VENC_SYNC_CTRL_IGNP_SHIFT                                                   (13U)
#define DSS_VENC_SYNC_CTRL_IGNP_MASK                                                    (0x00002000U)
#define DSS_VENC_SYNC_CTRL_IGNP_NOTIGNORED                                               (0U)
#define DSS_VENC_SYNC_CTRL_IGNP_IGNORED                                                  (1U)

#define DSS_VENC_SYNC_CTRL_ESAV_SHIFT                                                   (14U)
#define DSS_VENC_SYNC_CTRL_ESAV_MASK                                                    (0x00004000U)
#define DSS_VENC_SYNC_CTRL_ESAV_EAVANDSAV                                                (0U)
#define DSS_VENC_SYNC_CTRL_ESAV_EAVONLY                                                  (1U)

#define DSS_VENC_SYNC_CTRL_FREE_SHIFT                                                   (15U)
#define DSS_VENC_SYNC_CTRL_FREE_MASK                                                    (0x00008000U)
#define DSS_VENC_SYNC_CTRL_FREE_DISABLED                                                 (0U)
#define DSS_VENC_SYNC_CTRL_FREE_ENABLED                                                  (1U)

#define DSS_VENC_SYNC_CTRL_VS_POL_SHIFT                                                 (3U)
#define DSS_VENC_SYNC_CTRL_VS_POL_MASK                                                  (0x00000008U)
#define DSS_VENC_SYNC_CTRL_VS_POL_ACTIVEHIGH                                             (0U)
#define DSS_VENC_SYNC_CTRL_VS_POL_ACTIVELOW                                              (1U)

#define DSS_VENC_SYNC_CTRL_HS_POL_SHIFT                                                 (2U)
#define DSS_VENC_SYNC_CTRL_HS_POL_MASK                                                  (0x00000004U)
#define DSS_VENC_SYNC_CTRL_HS_POL_ACTIVEHIGH                                             (0U)
#define DSS_VENC_SYNC_CTRL_HS_POL_ACTIVELOW                                              (1U)

#define DSS_VENC_SYNC_CTRL_FHVMOD_SHIFT                                                 (0U)
#define DSS_VENC_SYNC_CTRL_FHVMOD_MASK                                                  (0x00000001U)
#define DSS_VENC_SYNC_CTRL_FHVMOD_EXTERNALFID                                            (0U)
#define DSS_VENC_SYNC_CTRL_FHVMOD_HSYNC_VSYNC                                            (1U)

#define DSS_VENC_LLEN_SHIFT                                                             (0U)
#define DSS_VENC_LLEN_MASK                                                              (0x000007ffU)

#define DSS_VENC_LLEN_EN_SHIFT                                                          (15U)
#define DSS_VENC_LLEN_EN_MASK                                                           (0x00008000U)
#define DSS_VENC_LLEN_EN_DISABLED                                                        (0U)
#define DSS_VENC_LLEN_EN_ENABLED                                                         (1U)

#define DSS_VENC_FLENS_SHIFT                                                            (0U)
#define DSS_VENC_FLENS_MASK                                                             (0x000007ffU)

#define DSS_VENC_HFLTR_CTRL_CINTP_SHIFT                                                 (1U)
#define DSS_VENC_HFLTR_CTRL_CINTP_MASK                                                  (0x00000006U)
#define DSS_VENC_HFLTR_CTRL_CINTP_ENABLED                                                (0U)
#define DSS_VENC_HFLTR_CTRL_CINTP_FIRSTSECTIONBYPASSED                                   (1U)
#define DSS_VENC_HFLTR_CTRL_CINTP_SECONDSECTIONBYPASSED                                  (2U)
#define DSS_VENC_HFLTR_CTRL_CINTP_BYPASSED                                               (3U)

#define DSS_VENC_HFLTR_CTRL_YINTP_SHIFT                                                 (0U)
#define DSS_VENC_HFLTR_CTRL_YINTP_MASK                                                  (0x00000001U)
#define DSS_VENC_HFLTR_CTRL_YINTP_ENABLED                                                (0U)
#define DSS_VENC_HFLTR_CTRL_YINTP_DISABLED                                               (1U)

#define DSS_VENC_CC_CARR_WSS_FCC_SHIFT                                                  (0U)
#define DSS_VENC_CC_CARR_WSS_FCC_MASK                                                   (0x0000ffffU)

#define DSS_VENC_CC_CARR_WSS_FWSS_SHIFT                                                 (16U)
#define DSS_VENC_CC_CARR_WSS_FWSS_MASK                                                  (0xffff0000U)

#define DSS_VENC_C_PHASE_CPHS_SHIFT                                                     (0U)
#define DSS_VENC_C_PHASE_CPHS_MASK                                                      (0x000000ffU)

#define DSS_VENC_GAIN_U_GU_SHIFT                                                        (0U)
#define DSS_VENC_GAIN_U_GU_MASK                                                         (0x000001ffU)

#define DSS_VENC_GAIN_V_GV_SHIFT                                                        (0U)
#define DSS_VENC_GAIN_V_GV_MASK                                                         (0x000001ffU)

#define DSS_VENC_GAIN_Y_GY_SHIFT                                                        (0U)
#define DSS_VENC_GAIN_Y_GY_MASK                                                         (0x000001ffU)

#define DSS_VENC_BLACK_LEVEL_SHIFT                                                      (0U)
#define DSS_VENC_BLACK_LEVEL_MASK                                                       (0x0000007fU)

#define DSS_VENC_BLANK_LEVEL_SHIFT                                                      (0U)
#define DSS_VENC_BLANK_LEVEL_MASK                                                       (0x0000007fU)

#define DSS_VENC_X_COLOR_LCD_SHIFT                                                      (0U)
#define DSS_VENC_X_COLOR_LCD_MASK                                                       (0x00000007U)
#define DSS_VENC_X_COLOR_LCD_0PIXEL                                                      (0U)
#define DSS_VENC_X_COLOR_LCD_P0_5PIXEL                                                   (1U)
#define DSS_VENC_X_COLOR_LCD_P1_0PIXEL                                                   (2U)
#define DSS_VENC_X_COLOR_LCD_P1_5PIXEL                                                   (3U)
#define DSS_VENC_X_COLOR_LCD_M2_0PIXEL                                                   (4U)
#define DSS_VENC_X_COLOR_LCD_M1_5PIXEL                                                   (5U)
#define DSS_VENC_X_COLOR_LCD_M1_0PIXEL                                                   (6U)
#define DSS_VENC_X_COLOR_LCD_M0_5PIXEL                                                   (7U)

#define DSS_VENC_X_COLOR_XCBW_SHIFT                                                     (3U)
#define DSS_VENC_X_COLOR_XCBW_MASK                                                      (0x00000018U)
#define DSS_VENC_X_COLOR_XCBW_32_8                                                       (0U)
#define DSS_VENC_X_COLOR_XCBW_26_5                                                       (1U)
#define DSS_VENC_X_COLOR_XCBW_30_0                                                       (2U)
#define DSS_VENC_X_COLOR_XCBW_29_2                                                       (3U)

#define DSS_VENC_X_COLOR_XCE_SHIFT                                                      (6U)
#define DSS_VENC_X_COLOR_XCE_MASK                                                       (0x00000040U)
#define DSS_VENC_X_COLOR_XCE_DISABLED                                                    (0U)
#define DSS_VENC_X_COLOR_XCE_ENABLED                                                     (1U)

#define DSS_VENC_M_CONTROL_FFRQ_SHIFT                                                   (0U)
#define DSS_VENC_M_CONTROL_FFRQ_MASK                                                    (0x00000001U)

#define DSS_VENC_M_CONTROL_PAL_SHIFT                                                    (1U)
#define DSS_VENC_M_CONTROL_PAL_MASK                                                     (0x00000002U)
#define DSS_VENC_M_CONTROL_PAL_DISABLED                                                  (0U)
#define DSS_VENC_M_CONTROL_PAL_ENABLED                                                   (1U)

#define DSS_VENC_M_CONTROL_CBW_SHIFT                                                    (2U)
#define DSS_VENC_M_CONTROL_CBW_MASK                                                     (0x0000001cU)
#define DSS_VENC_M_CONTROL_CBW_21_8                                                      (0U)
#define DSS_VENC_M_CONTROL_CBW_19_8                                                      (1U)
#define DSS_VENC_M_CONTROL_CBW_18_0                                                      (2U)
#define DSS_VENC_M_CONTROL_CBW_RESERVED0X3                                               (3U)
#define DSS_VENC_M_CONTROL_CBW_RESERVED0X4                                               (4U)
#define DSS_VENC_M_CONTROL_CBW_23_7                                                      (5U)
#define DSS_VENC_M_CONTROL_CBW_26_8                                                      (6U)
#define DSS_VENC_M_CONTROL_CBW_BYPASSED                                                  (7U)

#define DSS_VENC_M_CONTROL_PALPHS_SHIFT                                                 (5U)
#define DSS_VENC_M_CONTROL_PALPHS_MASK                                                  (0x00000020U)
#define DSS_VENC_M_CONTROL_PALPHS_NOMINAL                                                (0U)
#define DSS_VENC_M_CONTROL_PALPHS_INVERTED                                               (1U)

#define DSS_VENC_M_CONTROL_PALN_SHIFT                                                   (6U)
#define DSS_VENC_M_CONTROL_PALN_MASK                                                    (0x00000040U)
#define DSS_VENC_M_CONTROL_PALN_PAL_N_OFF                                                (0U)
#define DSS_VENC_M_CONTROL_PALN_PAL_N_ON                                                 (1U)

#define DSS_VENC_M_CONTROL_PALI_SHIFT                                                   (7U)
#define DSS_VENC_M_CONTROL_PALI_MASK                                                    (0x00000080U)
#define DSS_VENC_M_CONTROL_PALI_PAL_I_OFF                                                (0U)
#define DSS_VENC_M_CONTROL_PALI_PAL_I_ON                                                 (1U)

#define DSS_VENC_BSTAMP_WSS_DATA_SQP_SHIFT                                              (7U)
#define DSS_VENC_BSTAMP_WSS_DATA_SQP_MASK                                               (0x00000080U)
#define DSS_VENC_BSTAMP_WSS_DATA_SQP_ITU                                                 (0U)
#define DSS_VENC_BSTAMP_WSS_DATA_SQP_SQUAREPIXEL                                         (1U)

#define DSS_VENC_BSTAMP_WSS_DATA_D_SHIFT                                                (8U)
#define DSS_VENC_BSTAMP_WSS_DATA_D_MASK                                                 (0x0fffff00U)

#define DSS_VENC_BSTAMP_WSS_DATA_BSTAP_SHIFT                                            (0U)
#define DSS_VENC_BSTAMP_WSS_DATA_BSTAP_MASK                                             (0x0000007fU)

#define DSS_VENC_S_CARR_FSC_SHIFT                                                       (0U)
#define DSS_VENC_S_CARR_FSC_MASK                                                        (0xffffffffU)

#define DSS_VENC_LINE21_L21E_SHIFT                                                      (16U)
#define DSS_VENC_LINE21_L21E_MASK                                                       (0xffff0000U)

#define DSS_VENC_LINE21_L21O_SHIFT                                                      (0U)
#define DSS_VENC_LINE21_L21O_MASK                                                       (0x0000ffffU)

#define DSS_VENC_LN_SEL_SLINE_SHIFT                                                     (0U)
#define DSS_VENC_LN_SEL_SLINE_MASK                                                      (0x0000001fU)

#define DSS_VENC_LN_SEL_LN21_RUNIN_SHIFT                                                (16U)
#define DSS_VENC_LN_SEL_LN21_RUNIN_MASK                                                 (0x03ff0000U)

#define DSS_VENC_L21_WC_CTL_LINE_SHIFT                                                  (8U)
#define DSS_VENC_L21_WC_CTL_LINE_MASK                                                   (0x00001f00U)

#define DSS_VENC_L21_WC_CTL_INV_SHIFT                                                   (15U)
#define DSS_VENC_L21_WC_CTL_INV_MASK                                                    (0x00008000U)
#define DSS_VENC_L21_WC_CTL_INV_DISABLED                                                 (0U)
#define DSS_VENC_L21_WC_CTL_INV_ENABLED                                                  (1U)

#define DSS_VENC_L21_WC_CTL_EVEN_ODD_EN_SHIFT                                           (13U)
#define DSS_VENC_L21_WC_CTL_EVEN_ODD_EN_MASK                                            (0x00006000U)
#define DSS_VENC_L21_WC_CTL_EVEN_ODD_EN_DISABLED                                         (0U)
#define DSS_VENC_L21_WC_CTL_EVEN_ODD_EN_SECONDFIELDENABLED                               (1U)
#define DSS_VENC_L21_WC_CTL_EVEN_ODD_EN_FIRSTFIELDENABLED                                (2U)
#define DSS_VENC_L21_WC_CTL_EVEN_ODD_EN_ENABLED                                          (3U)

#define DSS_VENC_L21_WC_CTL_L21EN_SHIFT                                                 (0U)
#define DSS_VENC_L21_WC_CTL_L21EN_MASK                                                  (0x00000003U)
#define DSS_VENC_L21_WC_CTL_L21EN_DISABLED                                               (0U)
#define DSS_VENC_L21_WC_CTL_L21EN_FIRSTFIELDENABLED                                      (1U)
#define DSS_VENC_L21_WC_CTL_L21EN_SECONDFIELDENABLED                                     (2U)
#define DSS_VENC_L21_WC_CTL_L21EN_ENABLED                                                (3U)

#define DSS_VENC_HTRIGGER_VTRIGGER_VTRIG_SHIFT                                          (16U)
#define DSS_VENC_HTRIGGER_VTRIGGER_VTRIG_MASK                                           (0x03ff0000U)

#define DSS_VENC_HTRIGGER_VTRIGGER_HTRIG_SHIFT                                          (0U)
#define DSS_VENC_HTRIGGER_VTRIGGER_HTRIG_MASK                                           (0x000007ffU)

#define DSS_VENC_SAVID_EAVID_SAVID_SHIFT                                                      (0U)
#define DSS_VENC_SAVID_EAVID_SAVID_MASK                                                       (0x000007ffU)

#define DSS_VENC_SAVID_EAVID_EAVID_SHIFT                                                      (16U)
#define DSS_VENC_SAVID_EAVID_EAVID_MASK                                                       (0x07ff0000U)

#define DSS_VENC_FLEN_FAL_FLEN_SHIFT                                                         (0U)
#define DSS_VENC_FLEN_FAL_FLEN_MASK                                                          (0x000003ffU)

#define DSS_VENC_FLEN_FAL_FAL_SHIFT                                                         (16U)
#define DSS_VENC_FLEN_FAL_FAL_MASK                                                          (0x01ff0000U)

#define DSS_VENC_LAL_PHASE_RESET_PRES_SHIFT                                             (17U)
#define DSS_VENC_LAL_PHASE_RESET_PRES_MASK                                              (0x00060000U)
#define DSS_VENC_LAL_PHASE_RESET_PRES_NORESET                                            (0U)
#define DSS_VENC_LAL_PHASE_RESET_PRES_EVERY2LINES                                        (1U)
#define DSS_VENC_LAL_PHASE_RESET_PRES_EVERY8FIELDS                                       (2U)
#define DSS_VENC_LAL_PHASE_RESET_PRES_EVERY4FIELDS                                       (3U)

#define DSS_VENC_LAL_PHASE_RESET_SHIFT                                                  (0U)
#define DSS_VENC_LAL_PHASE_RESET_MASK                                                   (0x000001ffU)

#define DSS_VENC_LAL_PHASE_RESET_SBLANK_SHIFT                                           (16U)
#define DSS_VENC_LAL_PHASE_RESET_SBLANK_MASK                                            (0x00010000U)
#define DSS_VENC_LAL_PHASE_RESET_SBLANK_DEFINEDBYSETTING                                 (0U)
#define DSS_VENC_LAL_PHASE_RESET_SBLANK_FORCEDAUTOMATICALLY                              (1U)

#define DSS_VENC_HS_INT_START_STOP_X_START_X_SHIFT                                              (0U)
#define DSS_VENC_HS_INT_START_STOP_X_START_X_MASK                                               (0x000003ffU)

#define DSS_VENC_HS_INT_START_STOP_X_STOP_X_SHIFT                                              (16U)
#define DSS_VENC_HS_INT_START_STOP_X_STOP_X_MASK                                               (0x03ff0000U)

#define DSS_VENC_HS_EXT_START_STOP_X_SHIFT                                              (16U)
#define DSS_VENC_HS_EXT_START_STOP_X_MASK                                               (0x03ff0000U)

#define DSS_VENC_HS_EXT_START_STOP_X_START_X_SHIFT                                              (0U)
#define DSS_VENC_HS_EXT_START_STOP_X_START_X_MASK                                               (0x000003ffU)

#define DSS_VENC_VS_INT_START_X_STOP_X_SHIFT                                                   (16U)
#define DSS_VENC_VS_INT_START_X_STOP_X_MASK                                                    (0x03ff0000U)

#define DSS_VENC_VS_INT_STOP_X_START_Y_STOP_X_SHIFT                                            (16U)
#define DSS_VENC_VS_INT_STOP_X_START_Y_STOP_X_MASK                                             (0x03ff0000U)

#define DSS_VENC_VS_INT_STOP_X_START_Y_START_Y_SHIFT                                            (0U)
#define DSS_VENC_VS_INT_STOP_X_START_Y_START_Y_MASK                                             (0x000003ffU)

#define DSS_VENC_VS_INT_STOP_Y_EXT_START_X_SHIFT                                        (0U)
#define DSS_VENC_VS_INT_STOP_Y_EXT_START_X_MASK                                         (0x000003ffU)

#define DSS_VENC_VS_EXT_STOP_X_START_Y_START_Y_SHIFT                                            (16U)
#define DSS_VENC_VS_EXT_STOP_X_START_Y_START_Y_MASK                                             (0x03ff0000U)

#define DSS_VENC_VS_EXT_STOP_X_START_Y_STOP_X_SHIFT                                            (0U)
#define DSS_VENC_VS_EXT_STOP_X_START_Y_STOP_X_MASK                                             (0x000003ffU)

#define DSS_VENC_VS_EXT_STOP_Y_SHIFT                                                    (0U)
#define DSS_VENC_VS_EXT_STOP_Y_MASK                                                     (0x000003ffU)

#define DSS_VENC_AVID_START_STOP_X_START_X_SHIFT                                                (0U)
#define DSS_VENC_AVID_START_STOP_X_START_X_MASK                                                 (0x000003ffU)

#define DSS_VENC_AVID_START_STOP_X_STOP_X_SHIFT                                                (16U)
#define DSS_VENC_AVID_START_STOP_X_STOP_X_MASK                                                 (0x03ff0000U)

#define DSS_VENC_AVID_START_STOP_Y_START_Y_SHIFT                                                (0U)
#define DSS_VENC_AVID_START_STOP_Y_START_Y_MASK                                                 (0x000003ffU)

#define DSS_VENC_AVID_START_STOP_Y_STOP_Y_SHIFT                                                (16U)
#define DSS_VENC_AVID_START_STOP_Y_STOP_Y_MASK                                                 (0x03ff0000U)

#define DSS_VENC_FID_INT_START_X_Y_START_Y_SHIFT                                                (16U)
#define DSS_VENC_FID_INT_START_X_Y_START_Y_MASK                                                 (0x03ff0000U)

#define DSS_VENC_FID_INT_START_X_Y_START_X_SHIFT                                                (0U)
#define DSS_VENC_FID_INT_START_X_Y_START_X_MASK                                                 (0x000003ffU)

#define DSS_VENC_FID_INT_OFFSET_Y_EXT_START_X_OFFSET_Y_SHIFT                                     (0U)
#define DSS_VENC_FID_INT_OFFSET_Y_EXT_START_X_OFFSET_Y_MASK                                      (0x000003ffU)

#define DSS_VENC_FID_INT_OFFSET_Y_EXT_START_X_START_X_SHIFT                                     (16U)
#define DSS_VENC_FID_INT_OFFSET_Y_EXT_START_X_START_X_MASK                                      (0x03ff0000U)

#define DSS_VENC_FID_EXT_START_Y_OFFSET_START_Y_SHIFT                                           (0U)
#define DSS_VENC_FID_EXT_START_Y_OFFSET_START_Y_MASK                                            (0x000003ffU)

#define DSS_VENC_FID_EXT_START_Y_OFFSET_OFFSET_Y_SHIFT                                           (16U)
#define DSS_VENC_FID_EXT_START_Y_OFFSET_OFFSET_Y_MASK                                            (0x03ff0000U)

#define DSS_VENC_TVDETGP_INT_START_STOP_X_START_X_SHIFT                                         (0U)
#define DSS_VENC_TVDETGP_INT_START_STOP_X_START_X_MASK                                          (0x000003ffU)

#define DSS_VENC_TVDETGP_INT_START_STOP_X_STOP_X_SHIFT                                         (16U)
#define DSS_VENC_TVDETGP_INT_START_STOP_X_STOP_X_MASK                                          (0x03ff0000U)

#define DSS_VENC_TVDETGP_INT_START_STOP_Y_SHIFT                                         (0U)
#define DSS_VENC_TVDETGP_INT_START_STOP_Y_MASK                                          (0x000003ffU)

#define DSS_VENC_TVDETGP_INT_START_STOP_Y_STOP_Y_SHIFT                                         (16U)
#define DSS_VENC_TVDETGP_INT_START_STOP_Y_STOP_Y_MASK                                          (0x03ff0000U)

#define DSS_VENC_GEN_CTRL_AVIDP_SHIFT                                                   (19U)
#define DSS_VENC_GEN_CTRL_AVIDP_MASK                                                    (0x00080000U)
#define DSS_VENC_GEN_CTRL_AVIDP_ACTIVELOW                                                (0U)
#define DSS_VENC_GEN_CTRL_AVIDP_ACTIVEHIGH                                               (1U)

#define DSS_VENC_GEN_CTRL_FIP_SHIFT                                                     (18U)
#define DSS_VENC_GEN_CTRL_FIP_MASK                                                      (0x00040000U)
#define DSS_VENC_GEN_CTRL_FIP_ACTIVELOW                                                  (0U)
#define DSS_VENC_GEN_CTRL_FIP_ACTIVEHIGH                                                 (1U)

#define DSS_VENC_GEN_CTRL_FEP_SHIFT                                                     (17U)
#define DSS_VENC_GEN_CTRL_FEP_MASK                                                      (0x00020000U)
#define DSS_VENC_GEN_CTRL_FEP_ACTIVELOW                                                  (0U)
#define DSS_VENC_GEN_CTRL_FEP_ACTIVEHIGH                                                 (1U)

#define DSS_VENC_GEN_CTRL_TVDP_SHIFT                                                    (16U)
#define DSS_VENC_GEN_CTRL_TVDP_MASK                                                     (0x00010000U)
#define DSS_VENC_GEN_CTRL_TVDP_ACTIVELOW                                                 (0U)
#define DSS_VENC_GEN_CTRL_TVDP_ACTIVEHIGH                                                (1U)

#define DSS_VENC_GEN_CTRL_EN_SHIFT                                                      (0U)
#define DSS_VENC_GEN_CTRL_EN_MASK                                                       (0x00000001U)
#define DSS_VENC_GEN_CTRL_EN_DISABLED                                                    (0U)
#define DSS_VENC_GEN_CTRL_EN_ENABLED                                                     (1U)

#define DSS_VENC_GEN_CTRL_MS_SHIFT                                                      (26U)
#define DSS_VENC_GEN_CTRL_MS_MASK                                                       (0x04000000U)
#define DSS_VENC_GEN_CTRL_MS_CBCR                                                        (0U)
#define DSS_VENC_GEN_CTRL_MS_CRCB                                                        (1U)

#define DSS_VENC_GEN_CTRL_UVPHASE_POL_656_SHIFT                                         (25U)
#define DSS_VENC_GEN_CTRL_UVPHASE_POL_656_MASK                                          (0x02000000U)
#define DSS_VENC_GEN_CTRL_UVPHASE_POL_656_CBCR                                           (0U)
#define DSS_VENC_GEN_CTRL_UVPHASE_POL_656_CRCB                                           (1U)

#define DSS_VENC_GEN_CTRL_CBAR_SHIFT                                                    (24U)
#define DSS_VENC_GEN_CTRL_CBAR_MASK                                                     (0x01000000U)
#define DSS_VENC_GEN_CTRL_CBAR_CBCR                                                      (0U)
#define DSS_VENC_GEN_CTRL_CBAR_CRCB                                                      (1U)

#define DSS_VENC_GEN_CTRL_HIP_SHIFT                                                     (23U)
#define DSS_VENC_GEN_CTRL_HIP_MASK                                                      (0x00800000U)
#define DSS_VENC_GEN_CTRL_HIP_ACTIVELOW                                                  (0U)
#define DSS_VENC_GEN_CTRL_HIP_ACTIVEHIGH                                                 (1U)

#define DSS_VENC_GEN_CTRL_VIP_SHIFT                                                     (22U)
#define DSS_VENC_GEN_CTRL_VIP_MASK                                                      (0x00400000U)
#define DSS_VENC_GEN_CTRL_VIP_ACTIVELOW                                                  (0U)
#define DSS_VENC_GEN_CTRL_VIP_ACTIVEHIGH                                                 (1U)

#define DSS_VENC_GEN_CTRL_HEP_SHIFT                                                     (21U)
#define DSS_VENC_GEN_CTRL_HEP_MASK                                                      (0x00200000U)
#define DSS_VENC_GEN_CTRL_HEP_ACTIVELOW                                                  (0U)
#define DSS_VENC_GEN_CTRL_HEP_ACTIVEHIGH                                                 (1U)

#define DSS_VENC_GEN_CTRL_VEP_SHIFT                                                     (20U)
#define DSS_VENC_GEN_CTRL_VEP_MASK                                                      (0x00100000U)
#define DSS_VENC_GEN_CTRL_VEP_ACTIVELOW                                                  (0U)
#define DSS_VENC_GEN_CTRL_VEP_ACTIVEHIGH                                                 (1U)

#define DSS_VENC_OUTPUT_CONTROL_CHROMA_SOURCE_SHIFT                                     (7U)
#define DSS_VENC_OUTPUT_CONTROL_CHROMA_SOURCE_MASK                                      (0x00000080U)
#define DSS_VENC_OUTPUT_CONTROL_CHROMA_SOURCE_INTERNAL                                   (0U)
#define DSS_VENC_OUTPUT_CONTROL_CHROMA_SOURCE_DIRECTLYCONNECTED                          (1U)

#define DSS_VENC_OUTPUT_CONTROL_COMPOSITE_SOURCE_SHIFT                                  (6U)
#define DSS_VENC_OUTPUT_CONTROL_COMPOSITE_SOURCE_MASK                                   (0x00000040U)
#define DSS_VENC_OUTPUT_CONTROL_COMPOSITE_SOURCE_DIRECTLYCONNECTED                       (1U)
#define DSS_VENC_OUTPUT_CONTROL_COMPOSITE_SOURCE_INTERNAL                                (0U)

#define DSS_VENC_OUTPUT_CONTROL_LUMA_SOURCE_SHIFT                                       (5U)
#define DSS_VENC_OUTPUT_CONTROL_LUMA_SOURCE_MASK                                        (0x00000020U)
#define DSS_VENC_OUTPUT_CONTROL_LUMA_SOURCE_INTERNAL                                     (0U)
#define DSS_VENC_OUTPUT_CONTROL_LUMA_SOURCE_DIRECTLYCONNECTED                            (1U)

#define DSS_VENC_OUTPUT_CONTROL_TEST_MODE_SHIFT                                         (4U)
#define DSS_VENC_OUTPUT_CONTROL_TEST_MODE_MASK                                          (0x00000010U)
#define DSS_VENC_OUTPUT_CONTROL_TEST_MODE_NORMALOPERATION                                (0U)
#define DSS_VENC_OUTPUT_CONTROL_TEST_MODE_TESTMODE                                       (1U)

#define DSS_VENC_OUTPUT_CONTROL_VIDEO_INVERT_SHIFT                                      (3U)
#define DSS_VENC_OUTPUT_CONTROL_VIDEO_INVERT_MASK                                       (0x00000008U)
#define DSS_VENC_OUTPUT_CONTROL_VIDEO_INVERT_NORMALOPERATION                             (1U)
#define DSS_VENC_OUTPUT_CONTROL_VIDEO_INVERT_INVERTED                                    (0U)

#define DSS_VENC_OUTPUT_CONTROL_CHROMA_ENABLE_SHIFT                                     (2U)
#define DSS_VENC_OUTPUT_CONTROL_CHROMA_ENABLE_MASK                                      (0x00000004U)
#define DSS_VENC_OUTPUT_CONTROL_CHROMA_ENABLE_DISABLED                                   (0U)
#define DSS_VENC_OUTPUT_CONTROL_CHROMA_ENABLE_ENABLED                                    (1U)

#define DSS_VENC_OUTPUT_CONTROL_COMPOSITE_ENABLE_SHIFT                                  (1U)
#define DSS_VENC_OUTPUT_CONTROL_COMPOSITE_ENABLE_MASK                                   (0x00000002U)
#define DSS_VENC_OUTPUT_CONTROL_COMPOSITE_ENABLE_DISABLED                                (0U)
#define DSS_VENC_OUTPUT_CONTROL_COMPOSITE_ENABLE_ENABLED                                 (1U)

#define DSS_VENC_OUTPUT_CONTROL_LUMA_ENABLE_SHIFT                                       (0U)
#define DSS_VENC_OUTPUT_CONTROL_LUMA_ENABLE_MASK                                        (0x00000001U)
#define DSS_VENC_OUTPUT_CONTROL_LUMA_ENABLE_ENABLED                                      (1U)
#define DSS_VENC_OUTPUT_CONTROL_LUMA_ENABLE_DISABLED                                     (0U)

#define DSS_VENC_OUTPUT_CONTROL_LUMA_TEST_SHIFT                                         (16U)
#define DSS_VENC_OUTPUT_CONTROL_LUMA_TEST_MASK                                          (0x03ff0000U)

#define DSS_VENC_OUTPUT_TEST_CHROMA_SHIFT                                               (16U)
#define DSS_VENC_OUTPUT_TEST_CHROMA_MASK                                                (0x03ff0000U)

#define DSS_VENC_OUTPUT_TEST_COMPOSITE_SHIFT                                            (0U)
#define DSS_VENC_OUTPUT_TEST_COMPOSITE_MASK                                             (0x000003ffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_DSS_VENC_H_ */

