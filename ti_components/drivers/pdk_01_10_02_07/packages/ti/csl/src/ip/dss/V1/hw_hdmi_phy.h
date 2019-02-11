/*
* hw_hdmi_phy.h
*
* Register-level header file for HDMI_PHY
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
#ifndef HW_HDMI_PHY_H_
#define HW_HDMI_PHY_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define HDMI_TX_CONTROL                                         (0x0U)
#define HDMI_DIGITAL_CONTROL                                    (0x4U)
#define HDMI_POWER_CONTROL                                      (0x8U)
#define HDMI_PAD_CONFIG_CONTROL                                 (0xcU)
#define HDMI_TRIM_AND_TEST_CONTROL                              (0x10U)
#define HDMI_ANALOG_INTERFACE_CONTROL                           (0x14U)
#define HDMI_DATA_INTERFACE_CONTROL                             (0x18U)
#define HDMI_BIST_CONTROL                                       (0x1cU)


/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define HDMI_TX_CONTROL_TXLOWI_SHIFT                            (1U)
#define HDMI_TX_CONTROL_TXLOWI_MASK                             (0x00000006U)

#define HDMI_TX_CONTROL_TXLOWCM_SHIFT                           (3U)
#define HDMI_TX_CONTROL_TXLOWCM_MASK                            (0x00000008U)

#define HDMI_TX_CONTROL_SLOWEDGE_CLK_SHIFT                      (4U)
#define HDMI_TX_CONTROL_SLOWEDGE_CLK_MASK                       (0x00000030U)

#define HDMI_TX_CONTROL_SLOWEDGE_D2_SHIFT                       (6U)
#define HDMI_TX_CONTROL_SLOWEDGE_D2_MASK                        (0x000000c0U)

#define HDMI_TX_CONTROL_SLOWEDGE_D1_SHIFT                       (8U)
#define HDMI_TX_CONTROL_SLOWEDGE_D1_MASK                        (0x00000300U)

#define HDMI_TX_CONTROL_SLOWEDGE_D0_SHIFT                       (10U)
#define HDMI_TX_CONTROL_SLOWEDGE_D0_MASK                        (0x00000c00U)

#define HDMI_TX_CONTROL_PROGEM_CLK_SHIFT                        (12U)
#define HDMI_TX_CONTROL_PROGEM_CLK_MASK                         (0x00007000U)

#define HDMI_TX_CONTROL_PROGEM_D2_SHIFT                         (15U)
#define HDMI_TX_CONTROL_PROGEM_D2_MASK                          (0x00038000U)

#define HDMI_TX_CONTROL_PROGEM_D1_SHIFT                         (18U)
#define HDMI_TX_CONTROL_PROGEM_D1_MASK                          (0x001c0000U)

#define HDMI_TX_CONTROL_PROGEM_D0_SHIFT                         (21U)
#define HDMI_TX_CONTROL_PROGEM_D0_MASK                          (0x00e00000U)

#define HDMI_TX_CONTROL_EMPEN_CLK_SHIFT                         (24U)
#define HDMI_TX_CONTROL_EMPEN_CLK_MASK                          (0x01000000U)

#define HDMI_TX_CONTROL_EMPEN_D2_SHIFT                          (25U)
#define HDMI_TX_CONTROL_EMPEN_D2_MASK                           (0x02000000U)

#define HDMI_TX_CONTROL_EMPEN_D1_SHIFT                          (26U)
#define HDMI_TX_CONTROL_EMPEN_D1_MASK                           (0x04000000U)

#define HDMI_TX_CONTROL_EMPEN_D0_SHIFT                          (27U)
#define HDMI_TX_CONTROL_EMPEN_D0_MASK                           (0x08000000U)

#define HDMI_TX_CONTROL_SRCTERMCNTL_SHIFT                       (28U)
#define HDMI_TX_CONTROL_SRCTERMCNTL_MASK                        (0x30000000U)

#define HDMI_TX_CONTROL_FREQOUT_SHIFT                           (30U)
#define HDMI_TX_CONTROL_FREQOUT_MASK                            (0xc0000000U)

#define HDMI_DIGITAL_CONTROL_SPAREIN_SHIFT                      (0U)
#define HDMI_DIGITAL_CONTROL_SPAREIN_MASK                       (0x000000ffU)

#define HDMI_DIGITAL_CONTROL_TXVALID_SHIFT                      (28U)
#define HDMI_DIGITAL_CONTROL_TXVALID_MASK                       (0x10000000U)

#define HDMI_DIGITAL_CONTROL_USE_TXVALID_SHIFT                  (29U)
#define HDMI_DIGITAL_CONTROL_USE_TXVALID_MASK                   (0x20000000U)

#define HDMI_DIGITAL_CONTROL_TMDSCLKEN_SHIFT                    (30U)
#define HDMI_DIGITAL_CONTROL_TMDSCLKEN_MASK                     (0x40000000U)

#define HDMI_DIGITAL_CONTROL_USE_TMDSCLKEN_SHIFT                (31U)
#define HDMI_DIGITAL_CONTROL_USE_TMDSCLKEN_MASK                 (0x80000000U)

#define HDMI_DIGITAL_CONTROL_ENBYPASSCLK_SHIFT                  (26U)
#define HDMI_DIGITAL_CONTROL_ENBYPASSCLK_MASK                   (0x04000000U)

#define HDMI_DIGITAL_CONTROL_USE_ENBYPASSCLK_SHIFT              (27U)
#define HDMI_DIGITAL_CONTROL_USE_ENBYPASSCLK_MASK               (0x08000000U)

#define HDMI_DIGITAL_CONTROL_ANA_TM_SHIFT                       (8U)
#define HDMI_DIGITAL_CONTROL_ANA_TM_MASK                        (0x00003f00U)

#define HDMI_POWER_CONTROL_LDOVOLTAGE_SHIFT                     (0U)
#define HDMI_POWER_CONTROL_LDOVOLTAGE_MASK                      (0x0000000fU)

#define HDMI_POWER_CONTROL_TEST_EN_SC_FORCE_SHIFT               (4U)
#define HDMI_POWER_CONTROL_TEST_EN_SC_FORCE_MASK                (0x00000010U)

#define HDMI_POWER_CONTROL_TEST_EN_BG_FORCE_SHIFT               (5U)
#define HDMI_POWER_CONTROL_TEST_EN_BG_FORCE_MASK                (0x00000020U)

#define HDMI_POWER_CONTROL_TEST_EN_LDO_FORCE_SHIFT              (6U)
#define HDMI_POWER_CONTROL_TEST_EN_LDO_FORCE_MASK               (0x00000040U)

#define HDMI_POWER_CONTROL_TBIAS_COUNTER_SHIFT                  (7U)
#define HDMI_POWER_CONTROL_TBIAS_COUNTER_MASK                   (0x00003f80U)

#define HDMI_POWER_CONTROL_RESETDONEREFCLK_SHIFT                (14U)
#define HDMI_POWER_CONTROL_RESETDONEREFCLK_MASK                 (0x00004000U)

#define HDMI_POWER_CONTROL_RESETDONESCPCLK_SHIFT                (15U)
#define HDMI_POWER_CONTROL_RESETDONESCPCLK_MASK                 (0x00008000U)

#define HDMI_POWER_CONTROL_RESETDONEPWRCLK_SHIFT                (16U)
#define HDMI_POWER_CONTROL_RESETDONEPWRCLK_MASK                 (0x00010000U)

#define HDMI_POWER_CONTROL_RESETDONEPIXELCLK_SHIFT              (17U)
#define HDMI_POWER_CONTROL_RESETDONEPIXELCLK_MASK               (0x00020000U)

#define HDMI_POWER_CONTROL_BGON_COUNTER_SHIFT                   (19U)
#define HDMI_POWER_CONTROL_BGON_COUNTER_MASK                    (0x00f80000U)

#define HDMI_POWER_CONTROL_LDO_POWERUP_COUNTER_SHIFT            (24U)
#define HDMI_POWER_CONTROL_LDO_POWERUP_COUNTER_MASK             (0x7f000000U)

#define HDMI_POWER_CONTROL_FORCELDOON_SHIFT                     (31U)
#define HDMI_POWER_CONTROL_FORCELDOON_MASK                      (0x80000000U)

#define HDMI_PAD_CONFIG_CONTROL_FORCE_DET5VSHT_SHIFT            (0U)
#define HDMI_PAD_CONFIG_CONTROL_FORCE_DET5VSHT_MASK             (0x00000001U)

#define HDMI_PAD_CONFIG_CONTROL_DET5VSHT_DATA_SHIFT             (1U)
#define HDMI_PAD_CONFIG_CONTROL_DET5VSHT_DATA_MASK              (0x0000007eU)

#define HDMI_PAD_CONFIG_CONTROL_RXDET_LINE_SHIFT                (7U)
#define HDMI_PAD_CONFIG_CONTROL_RXDET_LINE_MASK                 (0x00007f80U)

#define HDMI_PAD_CONFIG_CONTROL_FORCE_RXDET_HIGH_SHIFT          (15U)
#define HDMI_PAD_CONFIG_CONTROL_FORCE_RXDET_HIGH_MASK           (0x00008000U)

#define HDMI_PAD_CONFIG_CONTROL_VTHRESHPU_CNTL_SHIFT            (16U)
#define HDMI_PAD_CONFIG_CONTROL_VTHRESHPU_CNTL_MASK             (0x00030000U)

#define HDMI_PAD_CONFIG_CONTROL_DET5VSHT_CLK_SHIFT              (18U)
#define HDMI_PAD_CONFIG_CONTROL_DET5VSHT_CLK_MASK               (0x000c0000U)

#define HDMI_PAD_CONFIG_CONTROL_PD_PULLUPDET_SHIFT              (20U)
#define HDMI_PAD_CONFIG_CONTROL_PD_PULLUPDET_MASK               (0x00100000U)

#define HDMI_PAD_CONFIG_CONTROL_ASSIGN_CH_SHIFT                 (22U)
#define HDMI_PAD_CONFIG_CONTROL_ASSIGN_CH_MASK                  (0x07c00000U)

#define HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_CLK_SHIFT        (27U)
#define HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_CLK_MASK         (0x08000000U)

#define HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_D2_SHIFT         (28U)
#define HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_D2_MASK          (0x10000000U)

#define HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_D1_SHIFT         (29U)
#define HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_D1_MASK          (0x20000000U)

#define HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_D0_SHIFT         (30U)
#define HDMI_PAD_CONFIG_CONTROL_FLIP_P_N_ORDER_D0_MASK          (0x40000000U)

#define HDMI_PAD_CONFIG_CONTROL_PADORDER_SHIFT                  (31U)
#define HDMI_PAD_CONFIG_CONTROL_PADORDER_MASK                   (0x80000000U)

#define HDMI_PAD_CONFIG_CONTROL_USE_PD_PULLUPDET_SHIFT          (21U)
#define HDMI_PAD_CONFIG_CONTROL_USE_PD_PULLUPDET_MASK           (0x00200000U)

#define HDMI_TRIM_AND_TEST_CONTROL_FORCE_SERIAL_DATA_SHIFT      (0U)
#define HDMI_TRIM_AND_TEST_CONTROL_FORCE_SERIAL_DATA_MASK       (0x0000000fU)

#define HDMI_TRIM_AND_TEST_CONTROL_USE_TRIMMODE_REGS_SHIFT      (5U)
#define HDMI_TRIM_AND_TEST_CONTROL_USE_TRIMMODE_REGS_MASK       (0x00000020U)

#define HDMI_TRIM_AND_TEST_CONTROL_TRIMMODE_SC_SHIFT            (6U)
#define HDMI_TRIM_AND_TEST_CONTROL_TRIMMODE_SC_MASK             (0x00000040U)

#define HDMI_TRIM_AND_TEST_CONTROL_TRIMMODE_BG_SHIFT            (7U)
#define HDMI_TRIM_AND_TEST_CONTROL_TRIMMODE_BG_MASK             (0x00000080U)

#define HDMI_TRIM_AND_TEST_CONTROL_SWTRIM_SHIFT                 (8U)
#define HDMI_TRIM_AND_TEST_CONTROL_SWTRIM_MASK                  (0x00007f00U)

#define HDMI_TRIM_AND_TEST_CONTROL_USE_SWTRIM_REG_SHIFT         (15U)
#define HDMI_TRIM_AND_TEST_CONTROL_USE_SWTRIM_REG_MASK          (0x00008000U)

#define HDMI_TRIM_AND_TEST_CONTROL_BGTRIM_SHIFT                 (16U)
#define HDMI_TRIM_AND_TEST_CONTROL_BGTRIM_MASK                  (0x7fff0000U)

#define HDMI_TRIM_AND_TEST_CONTROL_USE_BGTRIM_REG_SHIFT         (31U)
#define HDMI_TRIM_AND_TEST_CONTROL_USE_BGTRIM_REG_MASK          (0x80000000U)

#define HDMI_TRIM_AND_TEST_CONTROL_USE_FORCE_SERIAL_DATA_SHIFT  (4U)
#define HDMI_TRIM_AND_TEST_CONTROL_USE_FORCE_SERIAL_DATA_MASK   (0x00000010U)

#define HDMI_ANALOG_INTERFACE_CONTROL_CHAR_SHIFT                (0U)
#define HDMI_ANALOG_INTERFACE_CONTROL_CHAR_MASK                 (0x000000ffU)

#define HDMI_ANALOG_INTERFACE_CONTROL_CLOCK_LANE_POS_SHIFT      (8U)
#define HDMI_ANALOG_INTERFACE_CONTROL_CLOCK_LANE_POS_MASK       (0x00000300U)

#define HDMI_ANALOG_INTERFACE_CONTROL_USE_CLOCKLANEPOS_SHIFT    (10U)
#define HDMI_ANALOG_INTERFACE_CONTROL_USE_CLOCKLANEPOS_MASK     (0x00000400U)

#define HDMI_ANALOG_INTERFACE_CONTROL_TXONDELAYED_SHIFT         (11U)
#define HDMI_ANALOG_INTERFACE_CONTROL_TXONDELAYED_MASK          (0x00000800U)

#define HDMI_ANALOG_INTERFACE_CONTROL_TXON_SHIFT                (12U)
#define HDMI_ANALOG_INTERFACE_CONTROL_TXON_MASK                 (0x00001000U)

#define HDMI_ANALOG_INTERFACE_CONTROL_BGON_SHIFT                (13U)
#define HDMI_ANALOG_INTERFACE_CONTROL_BGON_MASK                 (0x00002000U)

#define HDMI_ANALOG_INTERFACE_CONTROL_LDOPGD_SHIFT              (14U)
#define HDMI_ANALOG_INTERFACE_CONTROL_LDOPGD_MASK               (0x00004000U)

#define HDMI_ANALOG_INTERFACE_CONTROL_USELDOPGD_REG_SHIFT       (15U)
#define HDMI_ANALOG_INTERFACE_CONTROL_USELDOPGD_REG_MASK        (0x00008000U)

#define HDMI_ANALOG_INTERFACE_CONTROL_DEBUG_SHIFT               (16U)
#define HDMI_ANALOG_INTERFACE_CONTROL_DEBUG_MASK                (0xffff0000U)

#define HDMI_DATA_INTERFACE_CONTROL_D2_OVERRIDE_SHIFT           (0U)
#define HDMI_DATA_INTERFACE_CONTROL_D2_OVERRIDE_MASK            (0x000003ffU)

#define HDMI_DATA_INTERFACE_CONTROL_D1_OVERRIDE_SHIFT           (10U)
#define HDMI_DATA_INTERFACE_CONTROL_D1_OVERRIDE_MASK            (0x000ffc00U)

#define HDMI_DATA_INTERFACE_CONTROL_D0_OVERRIDE_SHIFT           (21U)
#define HDMI_DATA_INTERFACE_CONTROL_D0_OVERRIDE_MASK            (0x7fe00000U)

#define HDMI_DATA_INTERFACE_CONTROL_USE_REG_SHIFT               (31U)
#define HDMI_DATA_INTERFACE_CONTROL_USE_REG_MASK                (0x80000000U)

#define HDMI_BIST_CONTROL_BGOBSERVE_FLIP_SHIFT                  (0U)
#define HDMI_BIST_CONTROL_BGOBSERVE_FLIP_MASK                   (0x00000001U)

#define HDMI_BIST_CONTROL_PRBS_EN_SHIFT                         (18U)
#define HDMI_BIST_CONTROL_PRBS_EN_MASK                          (0x003c0000U)

#define HDMI_BIST_CONTROL_LB_LANE_SEL_SHIFT                     (22U)
#define HDMI_BIST_CONTROL_LB_LANE_SEL_MASK                      (0x00c00000U)

#define HDMI_BIST_CONTROL_USE_LB_LANE_SEL_SHIFT                 (24U)
#define HDMI_BIST_CONTROL_USE_LB_LANE_SEL_MASK                  (0x01000000U)

#define HDMI_BIST_CONTROL_LB_COMP_SHIFT                         (25U)
#define HDMI_BIST_CONTROL_LB_COMP_MASK                          (0x02000000U)

#define HDMI_BIST_CONTROL_LB_MODE_SHIFT                         (26U)
#define HDMI_BIST_CONTROL_LB_MODE_MASK                          (0x04000000U)

#define HDMI_BIST_CONTROL_USE_LB_MODE_SHIFT                     (27U)
#define HDMI_BIST_CONTROL_USE_LB_MODE_MASK                      (0x08000000U)

#define HDMI_BIST_CONTROL_LDO_OK1_SHIFT                         (29U)
#define HDMI_BIST_CONTROL_LDO_OK1_MASK                          (0x20000000U)

#define HDMI_BIST_CONTROL_LDO_OK2_SHIFT                         (28U)
#define HDMI_BIST_CONTROL_LDO_OK2_MASK                          (0x10000000U)

#define HDMI_BIST_CONTROL_LDOBIST_CTRL_SHIFT                    (30U)
#define HDMI_BIST_CONTROL_LDOBIST_CTRL_MASK                     (0x40000000U)

#define HDMI_BIST_CONTROL_USE_LDOBIST_CTRL_SHIFT                (31U)
#define HDMI_BIST_CONTROL_USE_LDOBIST_CTRL_MASK                 (0x80000000U)

#define HDMI_BIST_CONTROL_LB_RXCLK_PHASE_SEL_SHIFT              (8U)
#define HDMI_BIST_CONTROL_LB_RXCLK_PHASE_SEL_MASK               (0x00000100U)

#define HDMI_BIST_CONTROL_USE_LB_RXCLK_PHASE_SEL_SHIFT          (9U)
#define HDMI_BIST_CONTROL_USE_LB_RXCLK_PHASE_SEL_MASK           (0x00000200U)

#define HDMI_BIST_CONTROL_DCC_EN_HFBITCLK_SHIFT                 (10U)
#define HDMI_BIST_CONTROL_DCC_EN_HFBITCLK_MASK                  (0x00000400U)

#define HDMI_BIST_CONTROL_DIV2EN_HFBITCLK_SHIFT                 (11U)
#define HDMI_BIST_CONTROL_DIV2EN_HFBITCLK_MASK                  (0x00000800U)

#define HDMI_BIST_CONTROL_BYPASS_REFCLK_DIV_SHIFT               (12U)
#define HDMI_BIST_CONTROL_BYPASS_REFCLK_DIV_MASK                (0x00001000U)

#define HDMI_BIST_CONTROL_LDO_BISTEN_SHIFT                      (13U)
#define HDMI_BIST_CONTROL_LDO_BISTEN_MASK                       (0x00002000U)

#define HDMI_BIST_CONTROL_LDO_SHIFT                             (14U)
#define HDMI_BIST_CONTROL_LDO_MASK                              (0x00004000U)

#define HDMI_BIST_CONTROL_USE_LDO_SHIFT                         (15U)
#define HDMI_BIST_CONTROL_USE_LDO_MASK                          (0x00008000U)

#define HDMI_BIST_CONTROL_LB_MODE_RX_PWR_UP_SHIFT               (16U)
#define HDMI_BIST_CONTROL_LB_MODE_RX_PWR_UP_MASK                (0x00010000U)

#define HDMI_BIST_CONTROL_TEST_EN_DIV_HFBITCLK_SHIFT            (17U)
#define HDMI_BIST_CONTROL_TEST_EN_DIV_HFBITCLK_MASK             (0x00020000U)

#ifdef __cplusplus
}
#endif

#endif /* HW_HDMI_PHY_H_ */

