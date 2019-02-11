/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2014
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
 * \file  hw_pciectrl_pl.h
 *
 * \brief Register-level header file for PCIECTRL_PL [default]
 *
**/

#ifndef HW_PCIECTRL_PL_H_
#define HW_PCIECTRL_PL_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Component offset
****************************************************************************************************/
#define PCIECTRL_PL_OFFSET 											(0x700U)

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define PCIECTRL_PL_LAT_REL_TIM                                     (0x0U)
#define PCIECTRL_PL_VENDOR_SPECIFIC_DLLP                            (0x4U)
#define PCIECTRL_PL_PT_LNK_R                                        (0x8U)
#define PCIECTRL_PL_ACK_FREQ_ASPM                                   (0xcU)
#define PCIECTRL_PL_PT_LNK_CTRL_R                                   (0x10U)
#define PCIECTRL_PL_LN_SKW_R                                        (0x14U)
#define PCIECTRL_PL_SYMB_N_R                                        (0x18U)
#define PCIECTRL_PL_SYMB_T_R                                        (0x1cU)
#define PCIECTRL_PL_FL_MSK_R2                                       (0x20U)
#define PCIECTRL_PL_OBNP_SUBREQ_CTRL                                (0x24U)
#define PCIECTRL_PL_DB_R0                                           (0x28U)
#define PCIECTRL_PL_DB_R1                                           (0x2cU)
#define PCIECTRL_PL_TR_P_STS_R                                      (0x30U)
#define PCIECTRL_PL_TR_NP_STS_R                                     (0x34U)
#define PCIECTRL_PL_TR_C_STS_R                                      (0x38U)
#define PCIECTRL_PL_Q_STS_R                                         (0x3cU)
#define PCIECTRL_PL_VC_TR_A_R1                                      (0x40U)
#define PCIECTRL_PL_VC_TR_A_R2                                      (0x44U)
#define PCIECTRL_PL_VC0_PR_Q_C                                      (0x48U)
#define PCIECTRL_PL_VC0_NPR_Q_C                                     (0x4cU)
#define PCIECTRL_PL_VC0_CR_Q_C                                      (0x50U)
#define PCIECTRL_PL_WIDTH_SPEED_CTL                                 (0x10cU)
#define PCIECTRL_PL_PHY_STS_R                                       (0x110U)
#define PCIECTRL_PL_PHY_CTRL_R                                      (0x114U)
#define PCIECTRL_PL_MSI_CTRL_ADDRESS                                (0x120U)
#define PCIECTRL_PL_MSI_CTRL_UPPER_ADDRESS                          (0x124U)
#define PCIECTRL_PL_MSI_CTRL_INT_ENABLE(m)                          ((uint32_t)0x128U + ((m) * 0xcU))
#define PCIECTRL_PL_MSI_CTRL_INT_ENABLE_NUM_ELEMS                   (8U)
#define PCIECTRL_PL_MSI_CTRL_INT_MASK(m)                            ((uint32_t)0x12CU + ((m) * 0xcU))
#define PCIECTRL_PL_MSI_CTRL_INT_MASK_NUM_ELEMS                     (8U)
#define PCIECTRL_PL_MSI_CTRL_INT_STATUS(m)                          ((uint32_t)0x130U + ((m) * 0xcU))
#define PCIECTRL_PL_MSI_CTRL_INT_STATUS_NUM_ELEMS                   (8U)
#define PCIECTRL_PL_MSI_CTRL_GPIO                                   (0x188U)
#define PCIECTRL_PL_PIPE_LOOPBACK                                   (0x1B8U)
#define PCIECTRL_PL_DBI_RO_WR_EN                                    (0x1BCU)
#define PCIECTRL_PL_AXIS_SLV_ERR_RESP                               (0x1D0U)
#define PCIECTRL_PL_AXIS_SLV_TIMEOUT                                (0x1D4U)
#define PCIECTRL_PL_IATU_INDEX                                      (0x200U)
#define PCIECTRL_PL_IATU_REG_CTRL_1                                 (0x204U)
#define PCIECTRL_PL_IATU_REG_CTRL_2                                 (0x208U)
#define PCIECTRL_PL_IATU_REG_LOWER_BASE                             (0x20cU)
#define PCIECTRL_PL_IATU_REG_UPPER_BASE                             (0x210U)
#define PCIECTRL_PL_IATU_REG_LIMIT                                  (0x214U)
#define PCIECTRL_PL_IATU_REG_LOWER_TARGET                           (0x218U)
#define PCIECTRL_PL_IATU_REG_UPPER_TARGET                           (0x21cU)
#define PCIECTRL_PL_IATU_REG_CTRL_3                                 (0x220U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PCIECTRL_PL_LAT_REL_TIM_ACK_LATENCY_TIME_LIMIT_SHIFT                            (0U)
#define PCIECTRL_PL_LAT_REL_TIM_ACK_LATENCY_TIME_LIMIT_MASK                             (0x0000ffffU)

#define PCIECTRL_PL_LAT_REL_TIM_REPLAY_TIME_LIMIT_SHIFT                                 (16U)
#define PCIECTRL_PL_LAT_REL_TIM_REPLAY_TIME_LIMIT_MASK                                  (0xffff0000U)

#define PCIECTRL_PL_VENDOR_SPECIFIC_DLLP_VEN_REG_SHIFT                                  (0U)
#define PCIECTRL_PL_VENDOR_SPECIFIC_DLLP_VEN_REG_MASK                                   (0xffffffffU)

#define PCIECTRL_PL_PT_LNK_R_LINK_NUM_SHIFT                                             (0U)
#define PCIECTRL_PL_PT_LNK_R_LINK_NUM_MASK                                              (0x000000ffU)

#define PCIECTRL_PL_PT_LNK_R_FORCE_LINK_SHIFT                                           (15U)
#define PCIECTRL_PL_PT_LNK_R_FORCE_LINK_MASK                                            (0x00008000U)
#define PCIECTRL_PL_PT_LNK_R_FORCE_LINK                                                  (1U)

#define PCIECTRL_PL_PT_LNK_R_FORCED_LINK_COMMAND_SHIFT                                  (16U)
#define PCIECTRL_PL_PT_LNK_R_FORCED_LINK_COMMAND_MASK                                   (0x003f0000U)

#define PCIECTRL_PL_PT_LNK_R_LOW_POWER_ENTR_CNT_SHIFT                                   (24U)
#define PCIECTRL_PL_PT_LNK_R_LOW_POWER_ENTR_CNT_MASK                                    (0xff000000U)

#define PCIECTRL_PL_PT_LNK_R_FORCED_LTSSM_STATE_SHIFT                                   (8U)
#define PCIECTRL_PL_PT_LNK_R_FORCED_LTSSM_STATE_MASK                                    (0x00000f00U)

#define PCIECTRL_PL_ACK_FREQ_ASPM_SHIFT                                                 (0U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_MASK                                                  (0x000000ffU)

#define PCIECTRL_PL_ACK_FREQ_ASPM_N_FTS_SHIFT                                           (8U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_N_FTS_MASK                                            (0x0000ff00U)

#define PCIECTRL_PL_ACK_FREQ_ASPM_COMMOM_CLK_N_FTS_SHIFT                                (16U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_COMMOM_CLK_N_FTS_MASK                                 (0x00ff0000U)

#define PCIECTRL_PL_ACK_FREQ_ASPM_L0S_ENTR_LAT_SHIFT                                    (24U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L0S_ENTR_LAT_MASK                                     (0x07000000U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L0S_ENTR_LAT_1                                         (0U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L0S_ENTR_LAT_2                                         (1U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L0S_ENTR_LAT_3                                         (2U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L0S_ENTR_LAT_4                                         (3U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L0S_ENTR_LAT_5                                         (4U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L0S_ENTR_LAT_6                                         (5U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L0S_ENTR_LAT_7                                         (6U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L0S_ENTR_LAT_7_ALT                                     (7U)

#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_LAT_SHIFT                                     (27U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_LAT_MASK                                      (0x38000000U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_LAT_1                                          (0U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_LAT_2                                          (1U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_LAT_3                                          (2U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_LAT_8                                          (3U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_LAT_16                                         (4U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_LAT_32                                         (5U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_LAT_65                                         (6U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_LAT_64_ALT                                     (7U)

#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_WO_L0S_SHIFT                                  (30U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_L1_ENTR_WO_L0S_MASK                                   (0x40000000U)

#define PCIECTRL_PL_ACK_FREQ_ASPM_RSVD_SHIFT                                            (31U)
#define PCIECTRL_PL_ACK_FREQ_ASPM_RSVD_MASK                                             (0x80000000U)

#define PCIECTRL_PL_PT_LNK_CTRL_R_VEN_DLLP_REQ_SHIFT                                    (0U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_VEN_DLLP_REQ_MASK                                     (0x00000001U)

#define PCIECTRL_PL_PT_LNK_CTRL_R_SCRAMBLE_DIS_SHIFT                                    (1U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_SCRAMBLE_DIS_MASK                                     (0x00000002U)

#define PCIECTRL_PL_PT_LNK_CTRL_R_LB_EN_SHIFT                                           (2U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_LB_EN_MASK                                            (0x00000004U)

#define PCIECTRL_PL_PT_LNK_CTRL_R_RESET_ASSERT_SHIFT                                    (3U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_RESET_ASSERT_MASK                                     (0x00000008U)

#define PCIECTRL_PL_PT_LNK_CTRL_R_DL_EN_SHIFT                                           (5U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_DL_EN_MASK                                            (0x00000020U)

#define PCIECTRL_PL_PT_LNK_CTRL_R_FAST_LINK_SHIFT                                       (7U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_FAST_LINK_MASK                                        (0x00000080U)

#define PCIECTRL_PL_PT_LNK_CTRL_R_LINK_MODE_SHIFT                                       (16U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_LINK_MODE_MASK                                        (0x003f0000U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_LINK_MODE_1X                                           (1U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_LINK_MODE_2X                                           (3U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_LINK_MODE_4X                                           (7U)

#define PCIECTRL_PL_PT_LNK_CTRL_R_CROSSLINK_EN_SHIFT                                    (22U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_CROSSLINK_EN_MASK                                     (0x00400000U)

#define PCIECTRL_PL_PT_LNK_CTRL_R_CROSSLINK_ACT_SHIFT                                   (23U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_CROSSLINK_ACT_MASK                                    (0x00800000U)

#define PCIECTRL_PL_PT_LNK_CTRL_R_RSVD4_SHIFT                                           (24U)
#define PCIECTRL_PL_PT_LNK_CTRL_R_RSVD4_MASK                                            (0xff000000U)

#define PCIECTRL_PL_LN_SKW_R_LANE_SKEW_SHIFT                                            (0U)
#define PCIECTRL_PL_LN_SKW_R_LANE_SKEW_MASK                                             (0x00ffffffU)

#define PCIECTRL_PL_LN_SKW_R_FC_DIS_SHIFT                                               (24U)
#define PCIECTRL_PL_LN_SKW_R_FC_DIS_MASK                                                (0x01000000U)

#define PCIECTRL_PL_LN_SKW_R_ACKNAK_DIS_SHIFT                                           (25U)
#define PCIECTRL_PL_LN_SKW_R_ACKNAK_DIS_MASK                                            (0x02000000U)

#define PCIECTRL_PL_LN_SKW_R_RSVD_SHIFT                                                 (26U)
#define PCIECTRL_PL_LN_SKW_R_RSVD_MASK                                                  (0x7c000000U)

#define PCIECTRL_PL_LN_SKW_R_DIS_L2L_SKEW_SHIFT                                         (31U)
#define PCIECTRL_PL_LN_SKW_R_DIS_L2L_SKEW_MASK                                          (0x80000000U)

#define PCIECTRL_PL_SYMB_N_R_MAX_FUNC_SHIFT                                             (0U)
#define PCIECTRL_PL_SYMB_N_R_MAX_FUNC_MASK                                              (0x000000ffU)

#define PCIECTRL_PL_SYMB_N_R_REPLAY_ADJ_SHIFT                                           (14U)
#define PCIECTRL_PL_SYMB_N_R_REPLAY_ADJ_MASK                                            (0x0007c000U)

#define PCIECTRL_PL_SYMB_N_R_ACK_LATENCY_INC_SHIFT                                      (19U)
#define PCIECTRL_PL_SYMB_N_R_ACK_LATENCY_INC_MASK                                       (0x00f80000U)

#define PCIECTRL_PL_SYMB_T_R_SKP_INT_SHIFT                                              (0U)
#define PCIECTRL_PL_SYMB_T_R_SKP_INT_MASK                                               (0x000007ffU)

#define PCIECTRL_PL_SYMB_T_R_RSVD_SHIFT                                                 (11U)
#define PCIECTRL_PL_SYMB_T_R_RSVD_MASK                                                  (0x00007800U)

#define PCIECTRL_PL_SYMB_T_R_DIS_FC_TIM_SHIFT                                           (15U)
#define PCIECTRL_PL_SYMB_T_R_DIS_FC_TIM_MASK                                            (0x00008000U)

#define PCIECTRL_PL_SYMB_T_R_FLT_MSK_1_SHIFT                                            (16U)
#define PCIECTRL_PL_SYMB_T_R_FLT_MSK_1_MASK                                             (0xffff0000U)

#define PCIECTRL_PL_FL_MSK_R2_FLT_2_SHIFT                                               (0U)
#define PCIECTRL_PL_FL_MSK_R2_FLT_2_MASK                                                (0xffffffffU)

#define PCIECTRL_PL_OBNP_SUBREQ_CTRL_EN_SHIFT                                           (0U)
#define PCIECTRL_PL_OBNP_SUBREQ_CTRL_EN_MASK                                            (0x00000001U)

#define PCIECTRL_PL_OBNP_SUBREQ_CTRL_RSVD_SHIFT                                         (1U)
#define PCIECTRL_PL_OBNP_SUBREQ_CTRL_RSVD_MASK                                          (0xfffffffeU)

#define PCIECTRL_PL_DB_R0_DBG_SHIFT                                                     (0U)
#define PCIECTRL_PL_DB_R0_DBG_MASK                                                      (0xffffffffU)

#define PCIECTRL_PL_DB_R1_DBG_SHIFT                                                     (0U)
#define PCIECTRL_PL_DB_R1_DBG_MASK                                                      (0xffffffffU)

#define PCIECTRL_PL_TR_P_STS_R_PD_CRDT_SHIFT                                            (0U)
#define PCIECTRL_PL_TR_P_STS_R_PD_CRDT_MASK                                             (0x00000fffU)

#define PCIECTRL_PL_TR_P_STS_R_PH_CRDT_SHIFT                                            (12U)
#define PCIECTRL_PL_TR_P_STS_R_PH_CRDT_MASK                                             (0x000ff000U)

#define PCIECTRL_PL_TR_P_STS_R_RSVD_SHIFT                                               (20U)
#define PCIECTRL_PL_TR_P_STS_R_RSVD_MASK                                                (0xfff00000U)

#define PCIECTRL_PL_TR_NP_STS_R_NPD_CRDT_SHIFT                                          (0U)
#define PCIECTRL_PL_TR_NP_STS_R_NPD_CRDT_MASK                                           (0x00000fffU)

#define PCIECTRL_PL_TR_NP_STS_R_NPH_CRDT_SHIFT                                          (12U)
#define PCIECTRL_PL_TR_NP_STS_R_NPH_CRDT_MASK                                           (0x000ff000U)

#define PCIECTRL_PL_TR_NP_STS_R_RSVD_SHIFT                                              (20U)
#define PCIECTRL_PL_TR_NP_STS_R_RSVD_MASK                                               (0xfff00000U)

#define PCIECTRL_PL_TR_C_STS_R_CPLD_CRDT_SHIFT                                          (0U)
#define PCIECTRL_PL_TR_C_STS_R_CPLD_CRDT_MASK                                           (0x00000fffU)

#define PCIECTRL_PL_TR_C_STS_R_CPLH_CRDT_SHIFT                                          (12U)
#define PCIECTRL_PL_TR_C_STS_R_CPLH_CRDT_MASK                                           (0x000ff000U)

#define PCIECTRL_PL_TR_C_STS_R_RSVD_SHIFT                                               (20U)
#define PCIECTRL_PL_TR_C_STS_R_RSVD_MASK                                                (0xfff00000U)

#define PCIECTRL_PL_Q_STS_R_CRDT_NOT_RTRN_SHIFT                                         (0U)
#define PCIECTRL_PL_Q_STS_R_CRDT_NOT_RTRN_MASK                                          (0x00000001U)

#define PCIECTRL_PL_Q_STS_R_RTYB_NOT_EMPTY_SHIFT                                        (1U)
#define PCIECTRL_PL_Q_STS_R_RTYB_NOT_EMPTY_MASK                                         (0x00000002U)

#define PCIECTRL_PL_Q_STS_R_RCVQ_NOT_EMPTY_SHIFT                                        (2U)
#define PCIECTRL_PL_Q_STS_R_RCVQ_NOT_EMPTY_MASK                                         (0x00000004U)

#define PCIECTRL_PL_Q_STS_R_FC_LATENCY_OVR_SHIFT                                        (16U)
#define PCIECTRL_PL_Q_STS_R_FC_LATENCY_OVR_MASK                                         (0x1fff0000U)

#define PCIECTRL_PL_Q_STS_R_FC_LATENCY_OVR_EN_SHIFT                                     (31U)
#define PCIECTRL_PL_Q_STS_R_FC_LATENCY_OVR_EN_MASK                                      (0x80000000U)

#define PCIECTRL_PL_VC0_PR_Q_C_P_DCRD_SHIFT                                             (0U)
#define PCIECTRL_PL_VC0_PR_Q_C_P_DCRD_MASK                                              (0x00000fffU)

#define PCIECTRL_PL_VC0_PR_Q_C_P_HCRD_SHIFT                                             (12U)
#define PCIECTRL_PL_VC0_PR_Q_C_P_HCRD_MASK                                              (0x000ff000U)

#define PCIECTRL_PL_VC0_PR_Q_C_ORDERING_RULES_SHIFT                                     (30U)
#define PCIECTRL_PL_VC0_PR_Q_C_ORDERING_RULES_MASK                                      (0x40000000U)
#define PCIECTRL_PL_VC0_PR_Q_C_ORDERING_RULES_STRICT                                     (0U)
#define PCIECTRL_PL_VC0_PR_Q_C_ORDERING_RULES_STANDARD                                   (1U)

#define PCIECTRL_PL_VC0_PR_Q_C_STRICT_VC_PRIORITY_SHIFT                                 (31U)
#define PCIECTRL_PL_VC0_PR_Q_C_STRICT_VC_PRIORITY_MASK                                  (0x80000000U)
#define PCIECTRL_PL_VC0_PR_Q_C_STRICT_VC_PRIORITY_ROUND_ROBIN                            (0U)
#define PCIECTRL_PL_VC0_PR_Q_C_STRICT_VC_PRIORITY                                        (1U)

#define PCIECTRL_PL_VC0_PR_Q_C_P_QMODE_SHIFT                                            (21U)
#define PCIECTRL_PL_VC0_PR_Q_C_P_QMODE_MASK                                             (0x00e00000U)
#define PCIECTRL_PL_VC0_PR_Q_C_P_QMODE_STORE_AND_FORWARD                                 (1U)
#define PCIECTRL_PL_VC0_PR_Q_C_P_QMODE_CUT_THROUGH                                       (2U)
#define PCIECTRL_PL_VC0_PR_Q_C_P_QMODE_BYPASS                                            (4U)

#define PCIECTRL_PL_VC0_NPR_Q_C_NP_DCRD_SHIFT                                           (0U)
#define PCIECTRL_PL_VC0_NPR_Q_C_NP_DCRD_MASK                                            (0x00000fffU)

#define PCIECTRL_PL_VC0_NPR_Q_C_NP_HCRD_SHIFT                                           (12U)
#define PCIECTRL_PL_VC0_NPR_Q_C_NP_HCRD_MASK                                            (0x000ff000U)

#define PCIECTRL_PL_VC0_NPR_Q_C_NP_QMODE_SHIFT                                          (21U)
#define PCIECTRL_PL_VC0_NPR_Q_C_NP_QMODE_MASK                                           (0x00e00000U)
#define PCIECTRL_PL_VC0_NPR_Q_C_NP_QMODE_STORE_AND_FORWARD                               (1U)
#define PCIECTRL_PL_VC0_NPR_Q_C_NP_QMODE_CUT_THROUGH                                     (2U)
#define PCIECTRL_PL_VC0_NPR_Q_C_NP_QMODE_BYPASS                                          (4U)

#define PCIECTRL_PL_VC0_CR_Q_C_CPL_DCRD_SHIFT                                           (0U)
#define PCIECTRL_PL_VC0_CR_Q_C_CPL_DCRD_MASK                                            (0x00000fffU)

#define PCIECTRL_PL_VC0_CR_Q_C_CPL_HCRD_SHIFT                                           (12U)
#define PCIECTRL_PL_VC0_CR_Q_C_CPL_HCRD_MASK                                            (0x000ff000U)

#define PCIECTRL_PL_VC0_CR_Q_C_CPL_QMODE_SHIFT                                          (21U)
#define PCIECTRL_PL_VC0_CR_Q_C_CPL_QMODE_MASK                                           (0x00e00000U)
#define PCIECTRL_PL_VC0_CR_Q_C_CPL_QMODE_STORE_AND_FORWARD                               (1U)
#define PCIECTRL_PL_VC0_CR_Q_C_CPL_QMODE_CUT_THROUGH                                     (2U)
#define PCIECTRL_PL_VC0_CR_Q_C_CPL_QMODE_BYPASS                                          (4U)

#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_GEN2_N_FTS_SHIFT                                (0U)
#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_GEN2_N_FTS_MASK                                 (0x000000ffU)

#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_LANE_EN_SHIFT                                   (8U)
#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_LANE_EN_MASK                                    (0x0001ff00U)

#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_DIRECTED_CHANGE_SHIFT                           (17U)
#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_DIRECTED_CHANGE_MASK                            (0x00020000U)
#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_DIRECTED_CHANGE_ENABLE                          (1U)
#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_DIRECTED_CHANGE_DISABLE                         (0U)

#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_PHY_TXSWING_SHIFT                               (18U)
#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_PHY_TXSWING_MASK                                (0x00040000U)

#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_TX_COMPLIANCE_RCV_SHIFT                         (19U)
#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_TX_COMPLIANCE_RCV_MASK                          (0x00080000U)

#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_UP_SEL_DEEMPH_SHIFT                             (20U)
#define PCIECTRL_PL_WIDTH_SPEED_CTL_CFG_UP_SEL_DEEMPH_MASK                              (0x00100000U)

#define PCIECTRL_PL_PHY_STS_R_SHIFT                                                     (0U)
#define PCIECTRL_PL_PHY_STS_R_MASK                                                      (0xffffffffU)

#define PCIECTRL_PL_PHY_CTRL_R_SHIFT                                                    (0U)
#define PCIECTRL_PL_PHY_CTRL_R_MASK                                                     (0xffffffffU)

#define PCIECTRL_PL_MSI_CTRL_ADDRESS_SHIFT                                              (0U)
#define PCIECTRL_PL_MSI_CTRL_ADDRESS_MASK                                               (0xffffffffU)

#define PCIECTRL_PL_MSI_CTRL_UPPER_ADDRESS_SHIFT                                        (0U)
#define PCIECTRL_PL_MSI_CTRL_UPPER_ADDRESS_MASK                                         (0xffffffffU)

#define PCIECTRL_PL_MSI_CTRL_INT_ENABLE_SHIFT                                           (0U)
#define PCIECTRL_PL_MSI_CTRL_INT_ENABLE_MASK                                            (0xffffffffU)

#define PCIECTRL_PL_MSI_CTRL_INT_MASK_SHIFT                                             (0U)
#define PCIECTRL_PL_MSI_CTRL_INT_MASK_MASK                                              (0xffffffffU)

#define PCIECTRL_PL_MSI_CTRL_INT_STATUS_SHIFT                                           (0U)
#define PCIECTRL_PL_MSI_CTRL_INT_STATUS_MASK                                            (0xffffffffU)

#define PCIECTRL_PL_MSI_CTRL_GPIO_SHIFT                                                 (0U)
#define PCIECTRL_PL_MSI_CTRL_GPIO_MASK                                                  (0xffffffffU)

#define PCIECTRL_PL_PIPE_LOOPBACK_EN_SHIFT                                              (31U)
#define PCIECTRL_PL_PIPE_LOOPBACK_EN_MASK                                               (0x80000000U)

#define PCIECTRL_PL_DBI_RO_WR_EN_CX_SHIFT                                               (0U)
#define PCIECTRL_PL_DBI_RO_WR_EN_CX_MASK                                                (0x00000001U)
#define PCIECTRL_PL_DBI_RO_WR_EN_CX_WRDIS                                                (0U)
#define PCIECTRL_PL_DBI_RO_WR_EN_CX_WREN                                                 (1U)

#define PCIECTRL_PL_AXIS_SLV_ERR_RESP_SLAVE_MAP_SHIFT                                   (0U)
#define PCIECTRL_PL_AXIS_SLV_ERR_RESP_SLAVE_MAP_MASK                                    (0x00000001U)

#define PCIECTRL_PL_AXIS_SLV_ERR_RESP_DBI_MAP_SHIFT                                     (1U)
#define PCIECTRL_PL_AXIS_SLV_ERR_RESP_DBI_MAP_MASK                                      (0x00000002U)

#define PCIECTRL_PL_AXIS_SLV_ERR_RESP_NO_VID_MAP_SHIFT                                  (2U)
#define PCIECTRL_PL_AXIS_SLV_ERR_RESP_NO_VID_MAP_MASK                                   (0x00000004U)

#define PCIECTRL_PL_AXIS_SLV_ERR_RESP_RESET_TIMEOUT_MAP_SHIFT                           (3U)
#define PCIECTRL_PL_AXIS_SLV_ERR_RESP_RESET_TIMEOUT_MAP_MASK                            (0x00000008U)

#define PCIECTRL_PL_AXIS_SLV_TIMEOUT_VALUE_SHIFT                                        (0U)
#define PCIECTRL_PL_AXIS_SLV_TIMEOUT_VALUE_MASK                                         (0x000000ffU)

#define PCIECTRL_PL_AXIS_SLV_TIMEOUT_FLUSH_EN_SHIFT                                     (8U)
#define PCIECTRL_PL_AXIS_SLV_TIMEOUT_FLUSH_EN_MASK                                      (0x00000100U)

#define PCIECTRL_PL_IATU_INDEX_REGION_DIRECTION_SHIFT                                   (31U)
#define PCIECTRL_PL_IATU_INDEX_REGION_DIRECTION_MASK                                    (0x80000000U)
#define PCIECTRL_PL_IATU_INDEX_REGION_DIRECTION_OUTBOUND                                 (0U)
#define PCIECTRL_PL_IATU_INDEX_REGION_DIRECTION_INBOUND                                  (1U)

#define PCIECTRL_PL_IATU_INDEX_REGION_SHIFT                                             (0U)
#define PCIECTRL_PL_IATU_INDEX_REGION_MASK                                              (0x0000000FU)

#define PCIECTRL_PL_IATU_REG_CTRL_1_TYPE_SHIFT                                          (0U)
#define PCIECTRL_PL_IATU_REG_CTRL_1_TYPE_MASK                                           (0x0000001fU)

#define PCIECTRL_PL_IATU_REG_CTRL_1_TC_SHIFT                                            (5U)
#define PCIECTRL_PL_IATU_REG_CTRL_1_TC_MASK                                             (0x000000e0U)

#define PCIECTRL_PL_IATU_REG_CTRL_1_TD_SHIFT                                            (8U)
#define PCIECTRL_PL_IATU_REG_CTRL_1_TD_MASK                                             (0x00000100U)

#define PCIECTRL_PL_IATU_REG_CTRL_1_ATTR_SHIFT                                          (9U)
#define PCIECTRL_PL_IATU_REG_CTRL_1_ATTR_MASK                                           (0x00000600U)

#define PCIECTRL_PL_IATU_REG_CTRL_1_AT_SHIFT                                            (16U)
#define PCIECTRL_PL_IATU_REG_CTRL_1_AT_MASK                                             (0x00030000U)

#define PCIECTRL_PL_IATU_REG_CTRL_1_FUNCTION_NUMBER_SHIFT                               (20U)
#define PCIECTRL_PL_IATU_REG_CTRL_1_FUNCTION_NUMBER_MASK                                (0x01f00000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_MESSAGECODE_SHIFT                                   (0U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_MESSAGECODE_MASK                                    (0x000000ffU)
#define PCIECTRL_PL_IATU_REG_CTRL_2_MESSAGECODE_MEM                                     (0U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_MESSAGECODE_IO                                      (2U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_MESSAGECODE_CFG                                     (4U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_BAR_NUMBER_SHIFT                                    (8U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_BAR_NUMBER_MASK                                     (0x00000700U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_BAR_NUMBER_BAR0                                      (0U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_BAR_NUMBER_BAR1                                      (1U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_BAR_NUMBER_BAR2                                      (2U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_BAR_NUMBER_BAR3                                      (3U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_BAR_NUMBER_BAR4                                      (4U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_BAR_NUMBER_BAR5                                      (5U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_BAR_NUMBER_ROM                                       (6U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_TC_MATCH_ENABLE_SHIFT                               (14U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_TC_MATCH_ENABLE_MASK                                (0x00004000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_TD_MATCH_ENABLE_SHIFT                               (15U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_TD_MATCH_ENABLE_MASK                                (0x00008000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_ATTR_MATCH_ENABLE_SHIFT                             (16U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_ATTR_MATCH_ENABLE_MASK                              (0x00010000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_AT_MATCH_ENABLE_SHIFT                               (18U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_AT_MATCH_ENABLE_MASK                                (0x00040000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_FUNCTION_NUMBER_MATCH_ENABLE_SHIFT                  (19U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_FUNCTION_NUMBER_MATCH_ENABLE_MASK                   (0x00080000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_VIRTUAL_FUNCTION_NUMBER_MATCH_ENABLE_SHIFT          (20U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_VIRTUAL_FUNCTION_NUMBER_MATCH_ENABLE_MASK           (0x00100000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_MESSAGE_CODE_MATCH_ENABLE_SHIFT                     (21U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_MESSAGE_CODE_MATCH_ENABLE_MASK                      (0x00200000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_RESPONSE_CODE_SHIFT                                 (24U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_RESPONSE_CODE_MASK                                  (0x03000000U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_RESPONSE_CODE_NONE                                   (0U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_RESPONSE_CODE_UR                                     (1U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_RESPONSE_CODE_CA                                     (2U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_FUZZY_TYPE_MATCH_MODE_SHIFT                         (27U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_FUZZY_TYPE_MATCH_MODE_MASK                          (0x08000000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_CFG_SHIFT_MODE_SHIFT                                (28U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_CFG_SHIFT_MODE_MASK                                 (0x10000000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_INVERT_MODE_SHIFT                                   (29U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_INVERT_MODE_MASK                                    (0x20000000U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_MATCH_MODE_SHIFT                                    (30U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_MATCH_MODE_MASK                                     (0x40000000U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_MATCH_MODE_0                                         (0U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_MATCH_MODE_1                                         (1U)

#define PCIECTRL_PL_IATU_REG_CTRL_2_REGION_ENABLE_SHIFT                                 (31U)
#define PCIECTRL_PL_IATU_REG_CTRL_2_REGION_ENABLE_MASK                                  (0x80000000U)

#define PCIECTRL_PL_IATU_REG_LOWER_BASE_SHIFT                                           (12U)
#define PCIECTRL_PL_IATU_REG_LOWER_BASE_MASK                                            (0xfffff000U)

#define PCIECTRL_PL_IATU_REG_LOWER_BASE_ZERO_SHIFT                                      (0U)
#define PCIECTRL_PL_IATU_REG_LOWER_BASE_ZERO_MASK                                       (0x00000fffU)

#define PCIECTRL_PL_IATU_REG_UPPER_BASE_SHIFT                                           (0U)
#define PCIECTRL_PL_IATU_REG_UPPER_BASE_MASK                                            (0xffffffffU)

#define PCIECTRL_PL_IATU_REG_LIMIT_SHIFT                                                (12U)
#define PCIECTRL_PL_IATU_REG_LIMIT_MASK                                                 (0xfffff000U)

#define PCIECTRL_PL_IATU_REG_LIMIT_ONES_SHIFT                                           (0U)
#define PCIECTRL_PL_IATU_REG_LIMIT_ONES_MASK                                            (0x00000fffU)

#define PCIECTRL_PL_IATU_REG_LOWER_TARGET_SHIFT                                         (12U)
#define PCIECTRL_PL_IATU_REG_LOWER_TARGET_MASK                                          (0xfffff000U)

#define PCIECTRL_PL_IATU_REG_LOWER_TARGET_ZERO_SHIFT                                    (0U)
#define PCIECTRL_PL_IATU_REG_LOWER_TARGET_ZERO_MASK                                     (0x00000fffU)

#define PCIECTRL_PL_IATU_REG_UPPER_TARGET_SHIFT                                         (0U)
#define PCIECTRL_PL_IATU_REG_UPPER_TARGET_MASK                                          (0xffffffffU)

#define PCIECTRL_PL_IATU_REG_CTRL_3_SHIFT                                               (0U)
#define PCIECTRL_PL_IATU_REG_CTRL_3_MASK                                                (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* HW_PCIECTRL_PL_H_ */
