/********************************************************************
 * Copyright (C) 2013-2014 Texas Instruments Incorporated.
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
#ifndef CSLR_PLCONF_H
#define CSLR_PLCONF_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for MSI_ADDRESS
**************************************************************************/
typedef struct {
    volatile Uint32 MSI_CTRL_ADDRESS;
    volatile Uint32 MSI_CTRL_UPPER_ADDRESS;
} CSL_PlconfMsi_addressRegs;


/**************************************************************************
* Register Overlay Structure for MSI_CTRL
**************************************************************************/
typedef struct {
    volatile Uint32 MSI_CTRL_INT_ENABLE;
    volatile Uint32 MSI_CTRL_INT_MASK;
    volatile Uint32 MSI_CTRL_INT_STATUS;
} CSL_PlconfMsi_ctrlRegs;


/**************************************************************************
* Register Overlay Structure for Config
**************************************************************************/
typedef struct {
    volatile Uint32 MSI_CTRL_GPIO;
    volatile Uint8  RSVD0[44];
    volatile Uint32 PIPE_LOOPBACK;
    volatile Uint32 DBI_RO_WR_EN;
    volatile Uint8  RSVD1[16];
    volatile Uint32 AXI_SLV_ERR_RESP;
    volatile Uint32 AXI_SLV_TIMEOUT;
} CSL_PlconfConfigRegs;


/**************************************************************************
* Register Overlay Structure for IATU
**************************************************************************/
typedef struct {
    volatile Uint32 IATU_INDEX;
    volatile Uint32 IATU_REG_CTRL_1;
    volatile Uint32 IATU_REG_CTRL_2;
    volatile Uint32 IATU_REG_LOWER_BASE;
    volatile Uint32 IATU_REG_UPPER_BASE;
    volatile Uint32 IATU_REG_LIMIT;
    volatile Uint32 IATU_REG_LOWER_TARGET;
    volatile Uint32 IATU_REG_UPPER_TARGET;
    volatile Uint32 IATU_REG_CTRL_3;
    volatile Uint8  RSVD0[76];
} CSL_PlconfIatuRegs;


/**************************************************************************
* Register Overlay Structure
**************************************************************************/
typedef struct {
    volatile Uint32 LAT_REL_TIM;
    volatile Uint32 VENDOR_SPECIFIC_DLLP;
    volatile Uint32 PT_LNK_R;
    volatile Uint32 ACK_FREQ_ASPM;
    volatile Uint32 PT_LNK_CTRL_R;
    volatile Uint32 LN_SKW_R;
    volatile Uint32 SYMB_N_R;
    volatile Uint32 SYMB_T_R;
    volatile Uint32 FL_MSK_R2;
    volatile Uint32 OBNP_SUBREQ_CTRL;
    volatile Uint32 DB_R0;
    volatile Uint32 DB_R1;
    volatile Uint32 TR_P_STS_R;
    volatile Uint32 TR_NP_STS_R;
    volatile Uint32 TR_C_STS_R;
    volatile Uint32 Q_STS_R;
    volatile Uint32 VC_TR_A_R1;
    volatile Uint32 VC_TR_A_R2;
    volatile Uint32 VC0_PR_Q_C;
    volatile Uint32 VC0_NPR_Q_C;
    volatile Uint32 VC0_CR_Q_C;
    volatile Uint8  RSVD1[184];
    volatile Uint32 WIDTH_SPEED_CTL;
    volatile Uint32 PHY_STS_R;
    volatile Uint32 PHY_CTRL_R;
    volatile Uint8  RSVD2[8];
    CSL_PlconfMsi_addressRegs	MSI_ADDRESS;
    CSL_PlconfMsi_ctrlRegs	MSI_CTRL[8];
    CSL_PlconfConfigRegs	CONFIG;
    volatile Uint8  RSVD3[40];
    CSL_PlconfIatuRegs	IATU;
} CSL_PlConfRegs;




/**************************************************************************
* Register Macros
**************************************************************************/

/* Ack Latency and Replay Timer Register */
#define CSL_PLCONF_LAT_REL_TIM                                  (0x0U)

/* Vendor Specific DLLP Register */
#define CSL_PLCONF_VENDOR_SPECIFIC_DLLP                         (0x4U)

/* Port Force Link Register */
#define CSL_PLCONF_PT_LNK_R                                     (0x8U)

/* Ack Frequency and L0-L1 ASPM Control Register (Sticky) */
#define CSL_PLCONF_ACK_FREQ_ASPM                                (0xCU)

/* Port Link Control Register (Sticky) */
#define CSL_PLCONF_PT_LNK_CTRL_R                                (0x10U)

/* Lane Skew Register (Sticky) */
#define CSL_PLCONF_LN_SKW_R                                     (0x14U)

/* Timer Control and Symbol Number Register (Sticky) */
#define CSL_PLCONF_SYMB_N_R                                     (0x18U)

/* Symbol Timer Register and Filter Mask Register 1 (Sticky) */
#define CSL_PLCONF_SYMB_T_R                                     (0x1CU)

/* Filter Mask Register 2 (Sticky) */
#define CSL_PLCONF_FL_MSK_R2                                    (0x20U)

/* AXI Multiple Outbound Decomposed NP SubRequests Control Register (Sticky) */
#define CSL_PLCONF_OBNP_SUBREQ_CTRL                             (0x24U)

/* Debug Register 0; Reset value is not expected to be accurate */
#define CSL_PLCONF_DB_R0                                        (0x28U)

/* Debug Register 1; Reset value is not expected to be accurate */
#define CSL_PLCONF_DB_R1                                        (0x2CU)

/* Transmit Posted FC Credit Status Register (Sticky) */
#define CSL_PLCONF_TR_P_STS_R                                   (0x30U)

/* Transmit Non-Posted FC Credit Status Register (Sticky) */
#define CSL_PLCONF_TR_NP_STS_R                                  (0x34U)

/* Transmit Completion FC Credit Status Register (Sticky) */
#define CSL_PLCONF_TR_C_STS_R                                   (0x38U)

/* Queue Status Register (Sticky) */
#define CSL_PLCONF_Q_STS_R                                      (0x3CU)

/* VC Transmit Arbitration Register 1 (Sticky) */
#define CSL_PLCONF_VC_TR_A_R1                                   (0x40U)

/* VC Transmit Arbitration Register 2 (Sticky) */
#define CSL_PLCONF_VC_TR_A_R2                                   (0x44U)

/* VC0 Posted Receive Queue Control (Sticky) */
#define CSL_PLCONF_VC0_PR_Q_C                                   (0x48U)

/* VC0 Non-Posted Receive Queue Control (Sticky) */
#define CSL_PLCONF_VC0_NPR_Q_C                                  (0x4CU)

/* VC0 Completion Receive Queue Control (Sticky) */
#define CSL_PLCONF_VC0_CR_Q_C                                   (0x50U)

/* Link Width and Speed Change Control Register (Sticky) */
#define CSL_PLCONF_WIDTH_SPEED_CTL                              (0x10CU)

/* PHY Status Register (Sticky) */
#define CSL_PLCONF_PHY_STS_R                                    (0x110U)

/* PHY Control Register (Sticky) */
#define CSL_PLCONF_PHY_CTRL_R                                   (0x114U)

/* MSI Controller Address Register (RC-mode MSI receiver) */
#define CSL_PLCONF_MSI_CTRL_ADDRESS                             (0x120U)

/* MSI Controller Upper Address Register (RC-mode MSI receiver) */
#define CSL_PLCONF_MSI_CTRL_UPPER_ADDRESS                       (0x124U)

/* MSI Controller Interrupt#N Enable Register (RC-mode MSI receiver) with N = 
 * MSI data [7:5] and ENABLE[i] = enable MSI vector #i, with i = MSI data 
 * [4:0] */
#define CSL_PLCONF_MSI_CTRL_INT_ENABLE(n)                       (0x128U + ((n) * (0xcU)))

/* MSI Controller Interrupt#N Mask Register (RC-mode MSI receiver) with N = 
 * MSI data [7:5] and MASK[i] = mask of MSI vector #i, with i = MSI data [4:0] */
#define CSL_PLCONF_MSI_CTRL_INT_MASK(n)                         (0x12CU + ((n) * (0xcU)))

/* MSI Controller Interrupt#N Status Register (RC-mode MSI receiver) with N = 
 * MSI data [7:5] and STATUS[i] = status of MSI vector #i, with i = MSI data 
 * [4:0] */
#define CSL_PLCONF_MSI_CTRL_INT_STATUS(n)                       (0x130U + ((n) * (0xcU)))

/* MSI Controller General Purpose IO Register (RC-mode MSI receiver) */
#define CSL_PLCONF_MSI_CTRL_GPIO                                (0x188U)

/* PIPE loopback control register (Sticky) */
#define CSL_PLCONF_PIPE_LOOPBACK                                (0x1B8U)

/* DBI Read-Only register Write Enable (Sticky) */
#define CSL_PLCONF_DBI_RO_WR_EN                                 (0x1BCU)

/* AXI Slave Error Response Register (Sticky) */
#define CSL_PLCONF_AXI_SLV_ERR_RESP                             (0x1D0U)

/* Link Down AXI Slave Timeout Register (Sticky) */
#define CSL_PLCONF_AXI_SLV_TIMEOUT                              (0x1D4U)

/* iATU Viewport Register: makes the registers of the corresponding iATU 
 * region accessible. */
#define CSL_PLCONF_IATU_INDEX                                   (0x200U)

/* iATU Region Control 1 Register */
#define CSL_PLCONF_IATU_REG_CTRL_1                              (0x204U)

/* iATU Region Control 2 Register */
#define CSL_PLCONF_IATU_REG_CTRL_2                              (0x208U)

/* iATU Region Lower Base Address Register (2**12 = 4kbyte - aligned) */
#define CSL_PLCONF_IATU_REG_LOWER_BASE                          (0x20CU)

/* iATU Region Upper Base Address Register */
#define CSL_PLCONF_IATU_REG_UPPER_BASE                          (0x210U)

/* iATU Region Limit Address Register */
#define CSL_PLCONF_IATU_REG_LIMIT                               (0x214U)

/* iATU Region Lower Target Address Register (2**12 = 4kbyte - aligned) */
#define CSL_PLCONF_IATU_REG_LOWER_TARGET                        (0x218U)

/* iATU Region Upper Target Address Register */
#define CSL_PLCONF_IATU_REG_UPPER_TARGET                        (0x21CU)

/* iATU Region Control 3 Register; VIRTUAL FUNCTIONS NOT IMPLEMENTED: NOT USED */
#define CSL_PLCONF_IATU_REG_CTRL_3                              (0x220U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* LAT_REL_TIM */

#define CSL_PLCONF_LAT_REL_TIM_ACK_LATENCY_TIME_LIMIT_MASK      (0x0000FFFFU)
#define CSL_PLCONF_LAT_REL_TIM_ACK_LATENCY_TIME_LIMIT_SHIFT     (0U)
#define CSL_PLCONF_LAT_REL_TIM_ACK_LATENCY_TIME_LIMIT_RESETVAL  (0x00000040U)
#define CSL_PLCONF_LAT_REL_TIM_ACK_LATENCY_TIME_LIMIT_MAX       (0x0000ffffU)

#define CSL_PLCONF_LAT_REL_TIM_REPLAY_TIME_LIMIT_MASK           (0xFFFF0000U)
#define CSL_PLCONF_LAT_REL_TIM_REPLAY_TIME_LIMIT_SHIFT          (16U)
#define CSL_PLCONF_LAT_REL_TIM_REPLAY_TIME_LIMIT_RESETVAL       (0x000000c0U)
#define CSL_PLCONF_LAT_REL_TIM_REPLAY_TIME_LIMIT_MAX            (0x0000ffffU)

#define CSL_PLCONF_LAT_REL_TIM_RESETVAL                         (0x00c00040U)

/* VENDOR_SPECIFIC_DLLP */

#define CSL_PLCONF_VENDOR_SPECIFIC_DLLP_VEN_DLLP_REG_MASK       (0xFFFFFFFFU)
#define CSL_PLCONF_VENDOR_SPECIFIC_DLLP_VEN_DLLP_REG_SHIFT      (0U)
#define CSL_PLCONF_VENDOR_SPECIFIC_DLLP_VEN_DLLP_REG_RESETVAL   (0xffffffffU)
#define CSL_PLCONF_VENDOR_SPECIFIC_DLLP_VEN_DLLP_REG_MAX        (0xffffffffU)

#define CSL_PLCONF_VENDOR_SPECIFIC_DLLP_RESETVAL                (0xffffffffU)

/* PT_LNK_R */

#define CSL_PLCONF_PT_LNK_R_LINK_NUM_MASK                       (0x000000FFU)
#define CSL_PLCONF_PT_LNK_R_LINK_NUM_SHIFT                      (0U)
#define CSL_PLCONF_PT_LNK_R_LINK_NUM_RESETVAL                   (0x00000004U)
#define CSL_PLCONF_PT_LNK_R_LINK_NUM_MAX                        (0x000000ffU)

#define CSL_PLCONF_PT_LNK_R_FORCE_LINK_MASK                     (0x00008000U)
#define CSL_PLCONF_PT_LNK_R_FORCE_LINK_SHIFT                    (15U)
#define CSL_PLCONF_PT_LNK_R_FORCE_LINK_RESETVAL                 (0x00000000U)
#define CSL_PLCONF_PT_LNK_R_FORCE_LINK_FORCE                    (0x00000001U)

#define CSL_PLCONF_PT_LNK_R_FORCED_LINK_COMMAND_MASK            (0x003F0000U)
#define CSL_PLCONF_PT_LNK_R_FORCED_LINK_COMMAND_SHIFT           (16U)
#define CSL_PLCONF_PT_LNK_R_FORCED_LINK_COMMAND_RESETVAL        (0x00000000U)
#define CSL_PLCONF_PT_LNK_R_FORCED_LINK_COMMAND_MAX             (0x0000003fU)

#define CSL_PLCONF_PT_LNK_R_LOW_POWER_ENTR_CNT_MASK             (0xFF000000U)
#define CSL_PLCONF_PT_LNK_R_LOW_POWER_ENTR_CNT_SHIFT            (24U)
#define CSL_PLCONF_PT_LNK_R_LOW_POWER_ENTR_CNT_RESETVAL         (0x00000007U)
#define CSL_PLCONF_PT_LNK_R_LOW_POWER_ENTR_CNT_MAX              (0x000000ffU)

#define CSL_PLCONF_PT_LNK_R_FORCED_LTSSM_STATE_MASK             (0x00000F00U)
#define CSL_PLCONF_PT_LNK_R_FORCED_LTSSM_STATE_SHIFT            (8U)
#define CSL_PLCONF_PT_LNK_R_FORCED_LTSSM_STATE_RESETVAL         (0x00000000U)
#define CSL_PLCONF_PT_LNK_R_FORCED_LTSSM_STATE_MAX              (0x0000000fU)

#define CSL_PLCONF_PT_LNK_R_RESETVAL                            (0x07000004U)

/* ACK_FREQ_ASPM */

#define CSL_PLCONF_ACK_FREQ_ASPM_ACK_FREQ_MASK                  (0x000000FFU)
#define CSL_PLCONF_ACK_FREQ_ASPM_ACK_FREQ_SHIFT                 (0U)
#define CSL_PLCONF_ACK_FREQ_ASPM_ACK_FREQ_RESETVAL              (0x00000000U)
#define CSL_PLCONF_ACK_FREQ_ASPM_ACK_FREQ_MAX                   (0x000000ffU)

#define CSL_PLCONF_ACK_FREQ_ASPM_N_FTS_MASK                     (0x0000FF00U)
#define CSL_PLCONF_ACK_FREQ_ASPM_N_FTS_SHIFT                    (8U)
#define CSL_PLCONF_ACK_FREQ_ASPM_N_FTS_RESETVAL                 (0x0000000fU)
#define CSL_PLCONF_ACK_FREQ_ASPM_N_FTS_MAX                      (0x000000ffU)

#define CSL_PLCONF_ACK_FREQ_ASPM_COMMOM_CLK_N_FTS_MASK          (0x00FF0000U)
#define CSL_PLCONF_ACK_FREQ_ASPM_COMMOM_CLK_N_FTS_SHIFT         (16U)
#define CSL_PLCONF_ACK_FREQ_ASPM_COMMOM_CLK_N_FTS_RESETVAL      (0x0000000fU)
#define CSL_PLCONF_ACK_FREQ_ASPM_COMMOM_CLK_N_FTS_MAX           (0x000000ffU)

#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT_MASK              (0x07000000U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT_SHIFT             (24U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT_RESETVAL          (0x00000003U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT__1                (0x00000000U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT__2                (0x00000001U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT__3                (0x00000002U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT__4                (0x00000003U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT__5                (0x00000004U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT__6                (0x00000005U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT__7                (0x00000006U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L0S_ENTR_LAT__7_ALT            (0x00000007U)

#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT_MASK               (0x38000000U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT_SHIFT              (27U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT_RESETVAL           (0x00000003U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT__1                 (0x00000000U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT__2                 (0x00000001U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT__3                 (0x00000002U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT__8                 (0x00000003U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT__16                (0x00000004U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT__32                (0x00000005U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT__65                (0x00000006U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_LAT__64_ALT            (0x00000007U)

#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_WO_L0S_MASK            (0x40000000U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_WO_L0S_SHIFT           (30U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_WO_L0S_RESETVAL        (0x00000000U)
#define CSL_PLCONF_ACK_FREQ_ASPM_L1_ENTR_WO_L0S_MAX             (0x00000001U)

#define CSL_PLCONF_ACK_FREQ_ASPM_RSVD_MASK                      (0x80000000U)
#define CSL_PLCONF_ACK_FREQ_ASPM_RSVD_SHIFT                     (31U)
#define CSL_PLCONF_ACK_FREQ_ASPM_RSVD_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_ACK_FREQ_ASPM_RSVD_MAX                       (0x00000001U)

#define CSL_PLCONF_ACK_FREQ_ASPM_RESETVAL                       (0x1b0f0f00U)

/* PT_LNK_CTRL_R */

#define CSL_PLCONF_PT_LNK_CTRL_R_VEN_DLLP_REQ_MASK              (0x00000001U)
#define CSL_PLCONF_PT_LNK_CTRL_R_VEN_DLLP_REQ_SHIFT             (0U)
#define CSL_PLCONF_PT_LNK_CTRL_R_VEN_DLLP_REQ_RESETVAL          (0x00000000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_VEN_DLLP_REQ_MAX               (0x00000001U)

#define CSL_PLCONF_PT_LNK_CTRL_R_SCRAMBLE_DIS_MASK              (0x00000002U)
#define CSL_PLCONF_PT_LNK_CTRL_R_SCRAMBLE_DIS_SHIFT             (1U)
#define CSL_PLCONF_PT_LNK_CTRL_R_SCRAMBLE_DIS_RESETVAL          (0x00000000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_SCRAMBLE_DIS_MAX               (0x00000001U)

#define CSL_PLCONF_PT_LNK_CTRL_R_LB_EN_MASK                     (0x00000004U)
#define CSL_PLCONF_PT_LNK_CTRL_R_LB_EN_SHIFT                    (2U)
#define CSL_PLCONF_PT_LNK_CTRL_R_LB_EN_RESETVAL                 (0x00000000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_LB_EN_MAX                      (0x00000001U)

#define CSL_PLCONF_PT_LNK_CTRL_R_RESET_ASSERT_MASK              (0x00000008U)
#define CSL_PLCONF_PT_LNK_CTRL_R_RESET_ASSERT_SHIFT             (3U)
#define CSL_PLCONF_PT_LNK_CTRL_R_RESET_ASSERT_RESETVAL          (0x00000000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_RESET_ASSERT_MAX               (0x00000001U)

#define CSL_PLCONF_PT_LNK_CTRL_R_DL_EN_MASK                     (0x00000020U)
#define CSL_PLCONF_PT_LNK_CTRL_R_DL_EN_SHIFT                    (5U)
#define CSL_PLCONF_PT_LNK_CTRL_R_DL_EN_RESETVAL                 (0x00000001U)
#define CSL_PLCONF_PT_LNK_CTRL_R_DL_EN_MAX                      (0x00000001U)

#define CSL_PLCONF_PT_LNK_CTRL_R_FAST_LINK_MASK                 (0x00000080U)
#define CSL_PLCONF_PT_LNK_CTRL_R_FAST_LINK_SHIFT                (7U)
#define CSL_PLCONF_PT_LNK_CTRL_R_FAST_LINK_RESETVAL             (0x00000000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_FAST_LINK_MAX                  (0x00000001U)

#define CSL_PLCONF_PT_LNK_CTRL_R_LINK_MODE_MASK                 (0x003F0000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_LINK_MODE_SHIFT                (16U)
#define CSL_PLCONF_PT_LNK_CTRL_R_LINK_MODE_RESETVAL             (0x00000003U)
#define CSL_PLCONF_PT_LNK_CTRL_R_LINK_MODE_MAX                  (0x0000003fU)

#define CSL_PLCONF_PT_LNK_CTRL_R_CROSSLINK_EN_MASK              (0x00400000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_CROSSLINK_EN_SHIFT             (22U)
#define CSL_PLCONF_PT_LNK_CTRL_R_CROSSLINK_EN_RESETVAL          (0x00000000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_CROSSLINK_EN_MAX               (0x00000001U)

#define CSL_PLCONF_PT_LNK_CTRL_R_CROSSLINK_ACT_MASK             (0x00800000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_CROSSLINK_ACT_SHIFT            (23U)
#define CSL_PLCONF_PT_LNK_CTRL_R_CROSSLINK_ACT_RESETVAL         (0x00000000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_CROSSLINK_ACT_MAX              (0x00000001U)

#define CSL_PLCONF_PT_LNK_CTRL_R_RSVD4_MASK                     (0xFF000000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_RSVD4_SHIFT                    (24U)
#define CSL_PLCONF_PT_LNK_CTRL_R_RSVD4_RESETVAL                 (0x00000000U)
#define CSL_PLCONF_PT_LNK_CTRL_R_RSVD4_MAX                      (0x000000ffU)

#define CSL_PLCONF_PT_LNK_CTRL_R_RESETVAL                       (0x00030120U)

/* LN_SKW_R */

#define CSL_PLCONF_LN_SKW_R_LANE_SKEW_MASK                      (0x00FFFFFFU)
#define CSL_PLCONF_LN_SKW_R_LANE_SKEW_SHIFT                     (0U)
#define CSL_PLCONF_LN_SKW_R_LANE_SKEW_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_LN_SKW_R_LANE_SKEW_MAX                       (0x00ffffffU)

#define CSL_PLCONF_LN_SKW_R_FC_DIS_MASK                         (0x01000000U)
#define CSL_PLCONF_LN_SKW_R_FC_DIS_SHIFT                        (24U)
#define CSL_PLCONF_LN_SKW_R_FC_DIS_RESETVAL                     (0x00000000U)
#define CSL_PLCONF_LN_SKW_R_FC_DIS_MAX                          (0x00000001U)

#define CSL_PLCONF_LN_SKW_R_ACKNAK_DIS_MASK                     (0x02000000U)
#define CSL_PLCONF_LN_SKW_R_ACKNAK_DIS_SHIFT                    (25U)
#define CSL_PLCONF_LN_SKW_R_ACKNAK_DIS_RESETVAL                 (0x00000000U)
#define CSL_PLCONF_LN_SKW_R_ACKNAK_DIS_MAX                      (0x00000001U)

#define CSL_PLCONF_LN_SKW_R_RSVD_MASK                           (0x7C000000U)
#define CSL_PLCONF_LN_SKW_R_RSVD_SHIFT                          (26U)
#define CSL_PLCONF_LN_SKW_R_RSVD_RESETVAL                       (0x00000000U)
#define CSL_PLCONF_LN_SKW_R_RSVD_MAX                            (0x0000001fU)

#define CSL_PLCONF_LN_SKW_R_DIS_L2L_SKEW_MASK                   (0x80000000U)
#define CSL_PLCONF_LN_SKW_R_DIS_L2L_SKEW_SHIFT                  (31U)
#define CSL_PLCONF_LN_SKW_R_DIS_L2L_SKEW_RESETVAL               (0x00000000U)
#define CSL_PLCONF_LN_SKW_R_DIS_L2L_SKEW_MAX                    (0x00000001U)

#define CSL_PLCONF_LN_SKW_R_RESETVAL                            (0x00000000U)

/* SYMB_N_R */

#define CSL_PLCONF_SYMB_N_R_MAX_FUNC_MASK                       (0x000000FFU)
#define CSL_PLCONF_SYMB_N_R_MAX_FUNC_SHIFT                      (0U)
#define CSL_PLCONF_SYMB_N_R_MAX_FUNC_RESETVAL                   (0x00000000U)
#define CSL_PLCONF_SYMB_N_R_MAX_FUNC_MAX                        (0x000000ffU)

#define CSL_PLCONF_SYMB_N_R_REPLAY_ADJ_MASK                     (0x0007C000U)
#define CSL_PLCONF_SYMB_N_R_REPLAY_ADJ_SHIFT                    (14U)
#define CSL_PLCONF_SYMB_N_R_REPLAY_ADJ_RESETVAL                 (0x00000001U)
#define CSL_PLCONF_SYMB_N_R_REPLAY_ADJ_MAX                      (0x0000001fU)

#define CSL_PLCONF_SYMB_N_R_ACK_LATENCY_INC_MASK                (0x00F80000U)
#define CSL_PLCONF_SYMB_N_R_ACK_LATENCY_INC_SHIFT               (19U)
#define CSL_PLCONF_SYMB_N_R_ACK_LATENCY_INC_RESETVAL            (0x00000000U)
#define CSL_PLCONF_SYMB_N_R_ACK_LATENCY_INC_MAX                 (0x0000001fU)

#define CSL_PLCONF_SYMB_N_R_RESETVAL                            (0x00004000U)

/* SYMB_T_R */

#define CSL_PLCONF_SYMB_T_R_SKP_INT_MASK                        (0x000007FFU)
#define CSL_PLCONF_SYMB_T_R_SKP_INT_SHIFT                       (0U)
#define CSL_PLCONF_SYMB_T_R_SKP_INT_RESETVAL                    (0x00000500U)
#define CSL_PLCONF_SYMB_T_R_SKP_INT_MAX                         (0x000007ffU)

#define CSL_PLCONF_SYMB_T_R_RSVD_MASK                           (0x00007800U)
#define CSL_PLCONF_SYMB_T_R_RSVD_SHIFT                          (11U)
#define CSL_PLCONF_SYMB_T_R_RSVD_RESETVAL                       (0x00000000U)
#define CSL_PLCONF_SYMB_T_R_RSVD_MAX                            (0x0000000fU)

#define CSL_PLCONF_SYMB_T_R_DIS_FC_TIM_MASK                     (0x00008000U)
#define CSL_PLCONF_SYMB_T_R_DIS_FC_TIM_SHIFT                    (15U)
#define CSL_PLCONF_SYMB_T_R_DIS_FC_TIM_RESETVAL                 (0x00000000U)
#define CSL_PLCONF_SYMB_T_R_DIS_FC_TIM_MAX                      (0x00000001U)

#define CSL_PLCONF_SYMB_T_R_FLT_MSK_1_MASK                      (0xFFFF0000U)
#define CSL_PLCONF_SYMB_T_R_FLT_MSK_1_SHIFT                     (16U)
#define CSL_PLCONF_SYMB_T_R_FLT_MSK_1_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_SYMB_T_R_FLT_MSK_1_MAX                       (0x0000ffffU)

#define CSL_PLCONF_SYMB_T_R_RESETVAL                            (0x00000780U)

/* FL_MSK_R2 */

#define CSL_PLCONF_FL_MSK_R2_FLT_MSK_2_MASK                     (0xFFFFFFFFU)
#define CSL_PLCONF_FL_MSK_R2_FLT_MSK_2_SHIFT                    (0U)
#define CSL_PLCONF_FL_MSK_R2_FLT_MSK_2_RESETVAL                 (0x00000000U)
#define CSL_PLCONF_FL_MSK_R2_FLT_MSK_2_MAX                      (0xffffffffU)

#define CSL_PLCONF_FL_MSK_R2_RESETVAL                           (0x00000000U)

/* OBNP_SUBREQ_CTRL */

#define CSL_PLCONF_OBNP_SUBREQ_CTRL_EN_OBNP_SUBREQ_MASK         (0x00000001U)
#define CSL_PLCONF_OBNP_SUBREQ_CTRL_EN_OBNP_SUBREQ_SHIFT        (0U)
#define CSL_PLCONF_OBNP_SUBREQ_CTRL_EN_OBNP_SUBREQ_RESETVAL     (0x00000001U)
#define CSL_PLCONF_OBNP_SUBREQ_CTRL_EN_OBNP_SUBREQ_MAX          (0x00000001U)

#define CSL_PLCONF_OBNP_SUBREQ_CTRL_RSVD_MASK                   (0xFFFFFFFEU)
#define CSL_PLCONF_OBNP_SUBREQ_CTRL_RSVD_SHIFT                  (1U)
#define CSL_PLCONF_OBNP_SUBREQ_CTRL_RSVD_RESETVAL               (0x00000000U)
#define CSL_PLCONF_OBNP_SUBREQ_CTRL_RSVD_MAX                    (0x7fffffffU)

#define CSL_PLCONF_OBNP_SUBREQ_CTRL_RESETVAL                    (0x00000001U)

/* DB_R0 */

#define CSL_PLCONF_DB_R0_DBG_R0_MASK                            (0xFFFFFFFFU)
#define CSL_PLCONF_DB_R0_DBG_R0_SHIFT                           (0U)
#define CSL_PLCONF_DB_R0_DBG_R0_RESETVAL                        (0x00000000U)
#define CSL_PLCONF_DB_R0_DBG_R0_MAX                             (0xffffffffU)

#define CSL_PLCONF_DB_R0_RESETVAL                               (0x00000000U)

/* DB_R1 */

#define CSL_PLCONF_DB_R1_DBG_R1_MASK                            (0xFFFFFFFFU)
#define CSL_PLCONF_DB_R1_DBG_R1_SHIFT                           (0U)
#define CSL_PLCONF_DB_R1_DBG_R1_RESETVAL                        (0x00000000U)
#define CSL_PLCONF_DB_R1_DBG_R1_MAX                             (0xffffffffU)

#define CSL_PLCONF_DB_R1_RESETVAL                               (0x00000000U)

/* TR_P_STS_R */

#define CSL_PLCONF_TR_P_STS_R_PD_CRDT_MASK                      (0x00000FFFU)
#define CSL_PLCONF_TR_P_STS_R_PD_CRDT_SHIFT                     (0U)
#define CSL_PLCONF_TR_P_STS_R_PD_CRDT_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_TR_P_STS_R_PD_CRDT_MAX                       (0x00000fffU)

#define CSL_PLCONF_TR_P_STS_R_PH_CRDT_MASK                      (0x000FF000U)
#define CSL_PLCONF_TR_P_STS_R_PH_CRDT_SHIFT                     (12U)
#define CSL_PLCONF_TR_P_STS_R_PH_CRDT_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_TR_P_STS_R_PH_CRDT_MAX                       (0x000000ffU)

#define CSL_PLCONF_TR_P_STS_R_RSVD_MASK                         (0xFFF00000U)
#define CSL_PLCONF_TR_P_STS_R_RSVD_SHIFT                        (20U)
#define CSL_PLCONF_TR_P_STS_R_RSVD_RESETVAL                     (0x00000000U)
#define CSL_PLCONF_TR_P_STS_R_RSVD_MAX                          (0x00000fffU)

#define CSL_PLCONF_TR_P_STS_R_RESETVAL                          (0x00000000U)

/* TR_NP_STS_R */

#define CSL_PLCONF_TR_NP_STS_R_NPD_CRDT_MASK                    (0x00000FFFU)
#define CSL_PLCONF_TR_NP_STS_R_NPD_CRDT_SHIFT                   (0U)
#define CSL_PLCONF_TR_NP_STS_R_NPD_CRDT_RESETVAL                (0x00000000U)
#define CSL_PLCONF_TR_NP_STS_R_NPD_CRDT_MAX                     (0x00000fffU)

#define CSL_PLCONF_TR_NP_STS_R_NPH_CRDT_MASK                    (0x000FF000U)
#define CSL_PLCONF_TR_NP_STS_R_NPH_CRDT_SHIFT                   (12U)
#define CSL_PLCONF_TR_NP_STS_R_NPH_CRDT_RESETVAL                (0x00000000U)
#define CSL_PLCONF_TR_NP_STS_R_NPH_CRDT_MAX                     (0x000000ffU)

#define CSL_PLCONF_TR_NP_STS_R_RSVD_MASK                        (0xFFF00000U)
#define CSL_PLCONF_TR_NP_STS_R_RSVD_SHIFT                       (20U)
#define CSL_PLCONF_TR_NP_STS_R_RSVD_RESETVAL                    (0x00000000U)
#define CSL_PLCONF_TR_NP_STS_R_RSVD_MAX                         (0x00000fffU)

#define CSL_PLCONF_TR_NP_STS_R_RESETVAL                         (0x00000000U)

/* TR_C_STS_R */

#define CSL_PLCONF_TR_C_STS_R_CPLD_CRDT_MASK                    (0x00000FFFU)
#define CSL_PLCONF_TR_C_STS_R_CPLD_CRDT_SHIFT                   (0U)
#define CSL_PLCONF_TR_C_STS_R_CPLD_CRDT_RESETVAL                (0x00000000U)
#define CSL_PLCONF_TR_C_STS_R_CPLD_CRDT_MAX                     (0x00000fffU)

#define CSL_PLCONF_TR_C_STS_R_CPLH_CRDT_MASK                    (0x000FF000U)
#define CSL_PLCONF_TR_C_STS_R_CPLH_CRDT_SHIFT                   (12U)
#define CSL_PLCONF_TR_C_STS_R_CPLH_CRDT_RESETVAL                (0x00000000U)
#define CSL_PLCONF_TR_C_STS_R_CPLH_CRDT_MAX                     (0x000000ffU)

#define CSL_PLCONF_TR_C_STS_R_RSVD_MASK                         (0xFFF00000U)
#define CSL_PLCONF_TR_C_STS_R_RSVD_SHIFT                        (20U)
#define CSL_PLCONF_TR_C_STS_R_RSVD_RESETVAL                     (0x00000000U)
#define CSL_PLCONF_TR_C_STS_R_RSVD_MAX                          (0x00000fffU)

#define CSL_PLCONF_TR_C_STS_R_RESETVAL                          (0x00000000U)

/* Q_STS_R */

#define CSL_PLCONF_Q_STS_R_CRDT_NOT_RTRN_MASK                   (0x00000001U)
#define CSL_PLCONF_Q_STS_R_CRDT_NOT_RTRN_SHIFT                  (0U)
#define CSL_PLCONF_Q_STS_R_CRDT_NOT_RTRN_RESETVAL               (0x00000000U)
#define CSL_PLCONF_Q_STS_R_CRDT_NOT_RTRN_MAX                    (0x00000001U)

#define CSL_PLCONF_Q_STS_R_RTYB_NOT_EMPTY_MASK                  (0x00000002U)
#define CSL_PLCONF_Q_STS_R_RTYB_NOT_EMPTY_SHIFT                 (1U)
#define CSL_PLCONF_Q_STS_R_RTYB_NOT_EMPTY_RESETVAL              (0x00000000U)
#define CSL_PLCONF_Q_STS_R_RTYB_NOT_EMPTY_MAX                   (0x00000001U)

#define CSL_PLCONF_Q_STS_R_RCVQ_NOT_EMPTY_MASK                  (0x00000004U)
#define CSL_PLCONF_Q_STS_R_RCVQ_NOT_EMPTY_SHIFT                 (2U)
#define CSL_PLCONF_Q_STS_R_RCVQ_NOT_EMPTY_RESETVAL              (0x00000000U)
#define CSL_PLCONF_Q_STS_R_RCVQ_NOT_EMPTY_MAX                   (0x00000001U)

#define CSL_PLCONF_Q_STS_R_FC_LATENCY_OVR_MASK                  (0x1FFF0000U)
#define CSL_PLCONF_Q_STS_R_FC_LATENCY_OVR_SHIFT                 (16U)
#define CSL_PLCONF_Q_STS_R_FC_LATENCY_OVR_RESETVAL              (0x00000000U)
#define CSL_PLCONF_Q_STS_R_FC_LATENCY_OVR_MAX                   (0x00001fffU)

#define CSL_PLCONF_Q_STS_R_FC_LATENCY_OVR_EN_MASK               (0x80000000U)
#define CSL_PLCONF_Q_STS_R_FC_LATENCY_OVR_EN_SHIFT              (31U)
#define CSL_PLCONF_Q_STS_R_FC_LATENCY_OVR_EN_RESETVAL           (0x00000000U)
#define CSL_PLCONF_Q_STS_R_FC_LATENCY_OVR_EN_MAX                (0x00000001U)

#define CSL_PLCONF_Q_STS_R_RESETVAL                             (0x00000000U)

/* VC_TR_A_R1 */

#define CSL_PLCONF_VC_TR_A_R1_WRR_VC0_MASK                      (0x000000FFU)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC0_SHIFT                     (0U)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC0_RESETVAL                  (0x0000000fU)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC0_MAX                       (0x000000ffU)

#define CSL_PLCONF_VC_TR_A_R1_WRR_VC1_MASK                      (0x0000FF00U)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC1_SHIFT                     (8U)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC1_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC1_MAX                       (0x000000ffU)

#define CSL_PLCONF_VC_TR_A_R1_WRR_VC2_MASK                      (0x00FF0000U)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC2_SHIFT                     (16U)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC2_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC2_MAX                       (0x000000ffU)

#define CSL_PLCONF_VC_TR_A_R1_WRR_VC3_MASK                      (0xFF000000U)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC3_SHIFT                     (24U)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC3_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_VC_TR_A_R1_WRR_VC3_MAX                       (0x000000ffU)

#define CSL_PLCONF_VC_TR_A_R1_RESETVAL                          (0x0000000fU)

/* VC_TR_A_R2 */

#define CSL_PLCONF_VC_TR_A_R2_WRR_VC4_MASK                      (0x000000FFU)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC4_SHIFT                     (0U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC4_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC4_MAX                       (0x000000ffU)

#define CSL_PLCONF_VC_TR_A_R2_WRR_VC5_MASK                      (0x0000FF00U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC5_SHIFT                     (8U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC5_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC5_MAX                       (0x000000ffU)

#define CSL_PLCONF_VC_TR_A_R2_WRR_VC6_MASK                      (0x00FF0000U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC6_SHIFT                     (16U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC6_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC6_MAX                       (0x000000ffU)

#define CSL_PLCONF_VC_TR_A_R2_WRR_VC7_MASK                      (0xFF000000U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC7_SHIFT                     (24U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC7_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_VC_TR_A_R2_WRR_VC7_MAX                       (0x000000ffU)

#define CSL_PLCONF_VC_TR_A_R2_RESETVAL                          (0x00000000U)

/* VC0_PR_Q_C */

#define CSL_PLCONF_VC0_PR_Q_C_P_DCRD_MASK                       (0x00000FFFU)
#define CSL_PLCONF_VC0_PR_Q_C_P_DCRD_SHIFT                      (0U)
#define CSL_PLCONF_VC0_PR_Q_C_P_DCRD_RESETVAL                   (0x0000002dU)
#define CSL_PLCONF_VC0_PR_Q_C_P_DCRD_MAX                        (0x00000fffU)

#define CSL_PLCONF_VC0_PR_Q_C_P_HCRD_MASK                       (0x000FF000U)
#define CSL_PLCONF_VC0_PR_Q_C_P_HCRD_SHIFT                      (12U)
#define CSL_PLCONF_VC0_PR_Q_C_P_HCRD_RESETVAL                   (0x00000015U)
#define CSL_PLCONF_VC0_PR_Q_C_P_HCRD_MAX                        (0x000000ffU)

#define CSL_PLCONF_VC0_PR_Q_C_ORDERING_RULES_MASK               (0x40000000U)
#define CSL_PLCONF_VC0_PR_Q_C_ORDERING_RULES_SHIFT              (30U)
#define CSL_PLCONF_VC0_PR_Q_C_ORDERING_RULES_RESETVAL           (0x00000001U)
#define CSL_PLCONF_VC0_PR_Q_C_ORDERING_RULES_STRICT             (0x00000000U)
#define CSL_PLCONF_VC0_PR_Q_C_ORDERING_RULES_STANDARD           (0x00000001U)

#define CSL_PLCONF_VC0_PR_Q_C_STRICT_VC_PRIORITY_MASK           (0x80000000U)
#define CSL_PLCONF_VC0_PR_Q_C_STRICT_VC_PRIORITY_SHIFT          (31U)
#define CSL_PLCONF_VC0_PR_Q_C_STRICT_VC_PRIORITY_RESETVAL       (0x00000000U)
#define CSL_PLCONF_VC0_PR_Q_C_STRICT_VC_PRIORITY_ROUND_ROBIN    (0x00000000U)
#define CSL_PLCONF_VC0_PR_Q_C_STRICT_VC_PRIORITY_STRICT         (0x00000001U)

#define CSL_PLCONF_VC0_PR_Q_C_P_QMODE_MASK                      (0x00E00000U)
#define CSL_PLCONF_VC0_PR_Q_C_P_QMODE_SHIFT                     (21U)
#define CSL_PLCONF_VC0_PR_Q_C_P_QMODE_RESETVAL                  (0x00000001U)
#define CSL_PLCONF_VC0_PR_Q_C_P_QMODE_STORE_AND_FORWARD         (0x00000001U)
#define CSL_PLCONF_VC0_PR_Q_C_P_QMODE_CUT_THROUGH               (0x00000002U)
#define CSL_PLCONF_VC0_PR_Q_C_P_QMODE_BYPASS                    (0x00000004U)

#define CSL_PLCONF_VC0_PR_Q_C_RESETVAL                          (0x4021502dU)

/* VC0_NPR_Q_C */

#define CSL_PLCONF_VC0_NPR_Q_C_NP_DCRD_MASK                     (0x00000FFFU)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_DCRD_SHIFT                    (0U)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_DCRD_RESETVAL                 (0x00000005U)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_DCRD_MAX                      (0x00000fffU)

#define CSL_PLCONF_VC0_NPR_Q_C_NP_HCRD_MASK                     (0x000FF000U)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_HCRD_SHIFT                    (12U)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_HCRD_RESETVAL                 (0x00000015U)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_HCRD_MAX                      (0x000000ffU)

#define CSL_PLCONF_VC0_NPR_Q_C_NP_QMODE_MASK                    (0x00E00000U)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_QMODE_SHIFT                   (21U)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_QMODE_RESETVAL                (0x00000001U)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_QMODE_STORE_AND_FORWARD       (0x00000001U)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_QMODE_CUT_THROUGH             (0x00000002U)
#define CSL_PLCONF_VC0_NPR_Q_C_NP_QMODE_BYPASS                  (0x00000004U)

#define CSL_PLCONF_VC0_NPR_Q_C_RESETVAL                         (0x00215005U)

/* VC0_CR_Q_C */

#define CSL_PLCONF_VC0_CR_Q_C_CPL_DCRD_MASK                     (0x00000FFFU)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_DCRD_SHIFT                    (0U)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_DCRD_RESETVAL                 (0x00000000U)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_DCRD_MAX                      (0x00000fffU)

#define CSL_PLCONF_VC0_CR_Q_C_CPL_HCRD_MASK                     (0x000FF000U)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_HCRD_SHIFT                    (12U)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_HCRD_RESETVAL                 (0x00000000U)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_HCRD_MAX                      (0x000000ffU)

#define CSL_PLCONF_VC0_CR_Q_C_CPL_QMODE_MASK                    (0x00E00000U)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_QMODE_SHIFT                   (21U)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_QMODE_RESETVAL                (0x00000004U)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_QMODE_STORE_AND_FORWARD       (0x00000001U)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_QMODE_CUT_THROUGH             (0x00000002U)
#define CSL_PLCONF_VC0_CR_Q_C_CPL_QMODE_BYPASS                  (0x00000004U)

#define CSL_PLCONF_VC0_CR_Q_C_RESETVAL                          (0x00800000U)

/* WIDTH_SPEED_CTL */

#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_GEN2_N_FTS_MASK          (0x000000FFU)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_GEN2_N_FTS_SHIFT         (0U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_GEN2_N_FTS_RESETVAL      (0x0000000fU)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_GEN2_N_FTS_MAX           (0x000000ffU)

#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_LANE_EN_MASK             (0x0001FF00U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_LANE_EN_SHIFT            (8U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_LANE_EN_RESETVAL         (0x00000002U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_LANE_EN_MAX              (0x000001ffU)

#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_DIRECTED_SPEED_CHANGE_MASK  (0x00020000U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_DIRECTED_SPEED_CHANGE_SHIFT  (17U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_DIRECTED_SPEED_CHANGE_RESETVAL  (0x00000001U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_DIRECTED_SPEED_CHANGE_MAX  (0x00000001U)

#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_PHY_TXSWING_MASK         (0x00040000U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_PHY_TXSWING_SHIFT        (18U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_PHY_TXSWING_RESETVAL     (0x00000000U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_PHY_TXSWING_MAX          (0x00000001U)

#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_TX_COMPLIANCE_RCV_MASK   (0x00080000U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_TX_COMPLIANCE_RCV_SHIFT  (19U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_TX_COMPLIANCE_RCV_RESETVAL  (0x00000000U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_TX_COMPLIANCE_RCV_MAX    (0x00000001U)

#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_UP_SEL_DEEMPH_MASK       (0x00100000U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_UP_SEL_DEEMPH_SHIFT      (20U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_UP_SEL_DEEMPH_RESETVAL   (0x00000000U)
#define CSL_PLCONF_WIDTH_SPEED_CTL_CFG_UP_SEL_DEEMPH_MAX        (0x00000001U)

#define CSL_PLCONF_WIDTH_SPEED_CTL_RESETVAL                     (0x0002020fU)

/* PHY_STS_R */

#define CSL_PLCONF_PHY_STS_R_PHY_STS_MASK                       (0xFFFFFFFFU)
#define CSL_PLCONF_PHY_STS_R_PHY_STS_SHIFT                      (0U)
#define CSL_PLCONF_PHY_STS_R_PHY_STS_RESETVAL                   (0x00000000U)
#define CSL_PLCONF_PHY_STS_R_PHY_STS_MAX                        (0xffffffffU)

#define CSL_PLCONF_PHY_STS_R_RESETVAL                           (0x00000000U)

/* PHY_CTRL_R */

#define CSL_PLCONF_PHY_CTRL_R_PHY_CTRL_MASK                     (0xFFFFFFFFU)
#define CSL_PLCONF_PHY_CTRL_R_PHY_CTRL_SHIFT                    (0U)
#define CSL_PLCONF_PHY_CTRL_R_PHY_CTRL_RESETVAL                 (0x00000000U)
#define CSL_PLCONF_PHY_CTRL_R_PHY_CTRL_MAX                      (0xffffffffU)

#define CSL_PLCONF_PHY_CTRL_R_RESETVAL                          (0x00000000U)

/* MSI_CTRL_ADDRESS */

#define CSL_PLCONF_MSI_CTRL_ADDRESS_MSI_CTRL_ADDRESS_MASK       (0xFFFFFFFFU)
#define CSL_PLCONF_MSI_CTRL_ADDRESS_MSI_CTRL_ADDRESS_SHIFT      (0U)
#define CSL_PLCONF_MSI_CTRL_ADDRESS_MSI_CTRL_ADDRESS_RESETVAL   (0x00000000U)
#define CSL_PLCONF_MSI_CTRL_ADDRESS_MSI_CTRL_ADDRESS_MAX        (0xffffffffU)

#define CSL_PLCONF_MSI_CTRL_ADDRESS_RESETVAL                    (0x00000000U)

/* MSI_CTRL_UPPER_ADDRESS */

#define CSL_PLCONF_MSI_CTRL_UPPER_ADDRESS_MSI_CTRL_UPPER_ADDRESS_MASK  (0xFFFFFFFFU)
#define CSL_PLCONF_MSI_CTRL_UPPER_ADDRESS_MSI_CTRL_UPPER_ADDRESS_SHIFT  (0U)
#define CSL_PLCONF_MSI_CTRL_UPPER_ADDRESS_MSI_CTRL_UPPER_ADDRESS_RESETVAL  (0x00000000U)
#define CSL_PLCONF_MSI_CTRL_UPPER_ADDRESS_MSI_CTRL_UPPER_ADDRESS_MAX  (0xffffffffU)

#define CSL_PLCONF_MSI_CTRL_UPPER_ADDRESS_RESETVAL              (0x00000000U)

/* MSI_CTRL_INT_ENABLE */

#define CSL_PLCONF_MSI_CTRL_INT_ENABLE_MSI_CTRL_INT_ENABLE_MASK  (0xFFFFFFFFU)
#define CSL_PLCONF_MSI_CTRL_INT_ENABLE_MSI_CTRL_INT_ENABLE_SHIFT  (0U)
#define CSL_PLCONF_MSI_CTRL_INT_ENABLE_MSI_CTRL_INT_ENABLE_RESETVAL  (0x00000000U)
#define CSL_PLCONF_MSI_CTRL_INT_ENABLE_MSI_CTRL_INT_ENABLE_MAX  (0xffffffffU)

#define CSL_PLCONF_MSI_CTRL_INT_ENABLE_RESETVAL                 (0x00000000U)

/* MSI_CTRL_INT_MASK */

#define CSL_PLCONF_MSI_CTRL_INT_MASK_MSI_CTRL_INT_MASK_MASK     (0xFFFFFFFFU)
#define CSL_PLCONF_MSI_CTRL_INT_MASK_MSI_CTRL_INT_MASK_SHIFT    (0U)
#define CSL_PLCONF_MSI_CTRL_INT_MASK_MSI_CTRL_INT_MASK_RESETVAL  (0x00000000U)
#define CSL_PLCONF_MSI_CTRL_INT_MASK_MSI_CTRL_INT_MASK_MAX      (0xffffffffU)

#define CSL_PLCONF_MSI_CTRL_INT_MASK_RESETVAL                   (0x00000000U)

/* MSI_CTRL_INT_STATUS */

#define CSL_PLCONF_MSI_CTRL_INT_STATUS_MSI_CTRL_INT_STATUS_MASK  (0xFFFFFFFFU)
#define CSL_PLCONF_MSI_CTRL_INT_STATUS_MSI_CTRL_INT_STATUS_SHIFT  (0U)
#define CSL_PLCONF_MSI_CTRL_INT_STATUS_MSI_CTRL_INT_STATUS_RESETVAL  (0x00000000U)
#define CSL_PLCONF_MSI_CTRL_INT_STATUS_MSI_CTRL_INT_STATUS_MAX  (0xffffffffU)

#define CSL_PLCONF_MSI_CTRL_INT_STATUS_RESETVAL                 (0x00000000U)

/* MSI_CTRL_GPIO */

#define CSL_PLCONF_MSI_CTRL_GPIO_MSI_CTRL_GPIO_MASK             (0xFFFFFFFFU)
#define CSL_PLCONF_MSI_CTRL_GPIO_MSI_CTRL_GPIO_SHIFT            (0U)
#define CSL_PLCONF_MSI_CTRL_GPIO_MSI_CTRL_GPIO_RESETVAL         (0x00000000U)
#define CSL_PLCONF_MSI_CTRL_GPIO_MSI_CTRL_GPIO_MAX              (0xffffffffU)

#define CSL_PLCONF_MSI_CTRL_GPIO_RESETVAL                       (0x00000000U)

/* PIPE_LOOPBACK */

#define CSL_PLCONF_PIPE_LOOPBACK_LOOPBACK_EN_MASK               (0x80000000U)
#define CSL_PLCONF_PIPE_LOOPBACK_LOOPBACK_EN_SHIFT              (31U)
#define CSL_PLCONF_PIPE_LOOPBACK_LOOPBACK_EN_RESETVAL           (0x00000000U)
#define CSL_PLCONF_PIPE_LOOPBACK_LOOPBACK_EN_MAX                (0x00000001U)

#define CSL_PLCONF_PIPE_LOOPBACK_RESETVAL                       (0x00000000U)

/* DBI_RO_WR_EN */

#define CSL_PLCONF_DBI_RO_WR_EN_CX_DBI_RO_WR_EN_MASK            (0x00000001U)
#define CSL_PLCONF_DBI_RO_WR_EN_CX_DBI_RO_WR_EN_SHIFT           (0U)
#define CSL_PLCONF_DBI_RO_WR_EN_CX_DBI_RO_WR_EN_RESETVAL        (0x00000001U)
#define CSL_PLCONF_DBI_RO_WR_EN_CX_DBI_RO_WR_EN_WRDIS           (0x00000000U)
#define CSL_PLCONF_DBI_RO_WR_EN_CX_DBI_RO_WR_EN_WREN            (0x00000001U)

#define CSL_PLCONF_DBI_RO_WR_EN_RESETVAL                        (0x00000001U)

/* AXI_SLV_ERR_RESP */

#define CSL_PLCONF_AXI_SLV_ERR_RESP_SLAVE_ERR_MAP_MASK          (0x00000001U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_SLAVE_ERR_MAP_SHIFT         (0U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_SLAVE_ERR_MAP_RESETVAL      (0x00000000U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_SLAVE_ERR_MAP_MAX           (0x00000001U)

#define CSL_PLCONF_AXI_SLV_ERR_RESP_DBI_ERR_MAP_MASK            (0x00000002U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_DBI_ERR_MAP_SHIFT           (1U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_DBI_ERR_MAP_RESETVAL        (0x00000000U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_DBI_ERR_MAP_MAX             (0x00000001U)

#define CSL_PLCONF_AXI_SLV_ERR_RESP_NO_VID_ERR_MAP_MASK         (0x00000004U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_NO_VID_ERR_MAP_SHIFT        (2U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_NO_VID_ERR_MAP_RESETVAL     (0x00000000U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_NO_VID_ERR_MAP_MAX          (0x00000001U)

#define CSL_PLCONF_AXI_SLV_ERR_RESP_RESET_TIMEOUT_ERR_MAP_MASK  (0x00000008U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_RESET_TIMEOUT_ERR_MAP_SHIFT  (3U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_RESET_TIMEOUT_ERR_MAP_RESETVAL  (0x00000000U)
#define CSL_PLCONF_AXI_SLV_ERR_RESP_RESET_TIMEOUT_ERR_MAP_MAX   (0x00000001U)

#define CSL_PLCONF_AXI_SLV_ERR_RESP_RESETVAL                    (0x00000000U)

/* AXI_SLV_TIMEOUT */

#define CSL_PLCONF_AXI_SLV_TIMEOUT_TIMEOUT_VALUE_MASK           (0x000000FFU)
#define CSL_PLCONF_AXI_SLV_TIMEOUT_TIMEOUT_VALUE_SHIFT          (0U)
#define CSL_PLCONF_AXI_SLV_TIMEOUT_TIMEOUT_VALUE_RESETVAL       (0x00000032U)
#define CSL_PLCONF_AXI_SLV_TIMEOUT_TIMEOUT_VALUE_MAX            (0x000000ffU)

#define CSL_PLCONF_AXI_SLV_TIMEOUT_FLUSH_EN_MASK                (0x00000100U)
#define CSL_PLCONF_AXI_SLV_TIMEOUT_FLUSH_EN_SHIFT               (8U)
#define CSL_PLCONF_AXI_SLV_TIMEOUT_FLUSH_EN_RESETVAL            (0x00000000U)
#define CSL_PLCONF_AXI_SLV_TIMEOUT_FLUSH_EN_MAX                 (0x00000001U)

#define CSL_PLCONF_AXI_SLV_TIMEOUT_RESETVAL                     (0x00000032U)

/* IATU_INDEX */

#define CSL_PLCONF_IATU_INDEX_REGION_DIRECTION_MASK             (0x80000000U)
#define CSL_PLCONF_IATU_INDEX_REGION_DIRECTION_SHIFT            (31U)
#define CSL_PLCONF_IATU_INDEX_REGION_DIRECTION_RESETVAL         (0x00000000U)
#define CSL_PLCONF_IATU_INDEX_REGION_DIRECTION_OUTBOUND         (0x00000000U)
#define CSL_PLCONF_IATU_INDEX_REGION_DIRECTION_INBOUND          (0x00000001U)

#define CSL_PLCONF_IATU_INDEX_REGION_INDEX_MASK                 (0x0000000FU)
#define CSL_PLCONF_IATU_INDEX_REGION_INDEX_SHIFT                (0U)
#define CSL_PLCONF_IATU_INDEX_REGION_INDEX_RESETVAL             (0x00000000U)
#define CSL_PLCONF_IATU_INDEX_REGION_INDEX_MAX                  (0x0000000fU)

#define CSL_PLCONF_IATU_INDEX_RESETVAL                          (0x00000000U)

/* IATU_REG_CTRL_1 */

#define CSL_PLCONF_IATU_REG_CTRL_1_TYPE_MASK                    (0x0000001FU)
#define CSL_PLCONF_IATU_REG_CTRL_1_TYPE_SHIFT                   (0U)
#define CSL_PLCONF_IATU_REG_CTRL_1_TYPE_RESETVAL                (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_1_TYPE_MAX                     (0x0000001fU)

#define CSL_PLCONF_IATU_REG_CTRL_1_TC_MASK                      (0x000000E0U)
#define CSL_PLCONF_IATU_REG_CTRL_1_TC_SHIFT                     (5U)
#define CSL_PLCONF_IATU_REG_CTRL_1_TC_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_1_TC_MAX                       (0x00000007U)

#define CSL_PLCONF_IATU_REG_CTRL_1_TD_MASK                      (0x00000100U)
#define CSL_PLCONF_IATU_REG_CTRL_1_TD_SHIFT                     (8U)
#define CSL_PLCONF_IATU_REG_CTRL_1_TD_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_1_TD_MAX                       (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_1_ATTR_MASK                    (0x00000600U)
#define CSL_PLCONF_IATU_REG_CTRL_1_ATTR_SHIFT                   (9U)
#define CSL_PLCONF_IATU_REG_CTRL_1_ATTR_RESETVAL                (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_1_ATTR_MAX                     (0x00000003U)

#define CSL_PLCONF_IATU_REG_CTRL_1_AT_MASK                      (0x00030000U)
#define CSL_PLCONF_IATU_REG_CTRL_1_AT_SHIFT                     (16U)
#define CSL_PLCONF_IATU_REG_CTRL_1_AT_RESETVAL                  (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_1_AT_MAX                       (0x00000003U)

#define CSL_PLCONF_IATU_REG_CTRL_1_FUNCTION_NUMBER_MASK         (0x01F00000U)
#define CSL_PLCONF_IATU_REG_CTRL_1_FUNCTION_NUMBER_SHIFT        (20U)
#define CSL_PLCONF_IATU_REG_CTRL_1_FUNCTION_NUMBER_RESETVAL     (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_1_FUNCTION_NUMBER_MAX          (0x0000001fU)

#define CSL_PLCONF_IATU_REG_CTRL_1_RESETVAL                     (0x00000000U)

/* IATU_REG_CTRL_2 */

#define CSL_PLCONF_IATU_REG_CTRL_2_MESSAGECODE_MASK             (0x000000FFU)
#define CSL_PLCONF_IATU_REG_CTRL_2_MESSAGECODE_SHIFT            (0U)
#define CSL_PLCONF_IATU_REG_CTRL_2_MESSAGECODE_RESETVAL         (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_MESSAGECODE_MAX              (0x000000ffU)

#define CSL_PLCONF_IATU_REG_CTRL_2_BAR_NUMBER_MASK              (0x00000700U)
#define CSL_PLCONF_IATU_REG_CTRL_2_BAR_NUMBER_SHIFT             (8U)
#define CSL_PLCONF_IATU_REG_CTRL_2_BAR_NUMBER_RESETVAL          (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_BAR_NUMBER_BAR0              (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_BAR_NUMBER_BAR1              (0x00000001U)
#define CSL_PLCONF_IATU_REG_CTRL_2_BAR_NUMBER_BAR2              (0x00000002U)
#define CSL_PLCONF_IATU_REG_CTRL_2_BAR_NUMBER_BAR3              (0x00000003U)
#define CSL_PLCONF_IATU_REG_CTRL_2_BAR_NUMBER_BAR4              (0x00000004U)
#define CSL_PLCONF_IATU_REG_CTRL_2_BAR_NUMBER_BAR5              (0x00000005U)
#define CSL_PLCONF_IATU_REG_CTRL_2_BAR_NUMBER_ROM               (0x00000006U)

#define CSL_PLCONF_IATU_REG_CTRL_2_TC_MATCH_ENABLE_MASK         (0x00004000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_TC_MATCH_ENABLE_SHIFT        (14U)
#define CSL_PLCONF_IATU_REG_CTRL_2_TC_MATCH_ENABLE_RESETVAL     (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_TC_MATCH_ENABLE_MAX          (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_TD_MATCH_ENABLE_MASK         (0x00008000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_TD_MATCH_ENABLE_SHIFT        (15U)
#define CSL_PLCONF_IATU_REG_CTRL_2_TD_MATCH_ENABLE_RESETVAL     (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_TD_MATCH_ENABLE_MAX          (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_ATTR_MATCH_ENABLE_MASK       (0x00010000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_ATTR_MATCH_ENABLE_SHIFT      (16U)
#define CSL_PLCONF_IATU_REG_CTRL_2_ATTR_MATCH_ENABLE_RESETVAL   (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_ATTR_MATCH_ENABLE_MAX        (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_AT_MATCH_ENABLE_MASK         (0x00040000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_AT_MATCH_ENABLE_SHIFT        (18U)
#define CSL_PLCONF_IATU_REG_CTRL_2_AT_MATCH_ENABLE_RESETVAL     (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_AT_MATCH_ENABLE_MAX          (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_FUNCTION_NUMBER_MATCH_ENABLE_MASK  (0x00080000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_FUNCTION_NUMBER_MATCH_ENABLE_SHIFT  (19U)
#define CSL_PLCONF_IATU_REG_CTRL_2_FUNCTION_NUMBER_MATCH_ENABLE_RESETVAL  (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_FUNCTION_NUMBER_MATCH_ENABLE_MAX  (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_VIRTUAL_FUNCTION_NUMBER_MATCH_ENABLE_MASK  (0x00100000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_VIRTUAL_FUNCTION_NUMBER_MATCH_ENABLE_SHIFT  (20U)
#define CSL_PLCONF_IATU_REG_CTRL_2_VIRTUAL_FUNCTION_NUMBER_MATCH_ENABLE_RESETVAL  (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_VIRTUAL_FUNCTION_NUMBER_MATCH_ENABLE_MAX  (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_MESSAGE_CODE_MATCH_ENABLE_MASK  (0x00200000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_MESSAGE_CODE_MATCH_ENABLE_SHIFT  (21U)
#define CSL_PLCONF_IATU_REG_CTRL_2_MESSAGE_CODE_MATCH_ENABLE_RESETVAL  (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_MESSAGE_CODE_MATCH_ENABLE_MAX  (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_RESPONSE_CODE_MASK           (0x03000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_RESPONSE_CODE_SHIFT          (24U)
#define CSL_PLCONF_IATU_REG_CTRL_2_RESPONSE_CODE_RESETVAL       (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_RESPONSE_CODE_NONE           (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_RESPONSE_CODE_UR             (0x00000001U)
#define CSL_PLCONF_IATU_REG_CTRL_2_RESPONSE_CODE_CA             (0x00000002U)

#define CSL_PLCONF_IATU_REG_CTRL_2_FUZZY_TYPE_MATCH_MODE_MASK   (0x08000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_FUZZY_TYPE_MATCH_MODE_SHIFT  (27U)
#define CSL_PLCONF_IATU_REG_CTRL_2_FUZZY_TYPE_MATCH_MODE_RESETVAL  (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_FUZZY_TYPE_MATCH_MODE_MAX    (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_CFG_SHIFT_MODE_MASK          (0x10000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_CFG_SHIFT_MODE_SHIFT         (28U)
#define CSL_PLCONF_IATU_REG_CTRL_2_CFG_SHIFT_MODE_RESETVAL      (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_CFG_SHIFT_MODE_MAX           (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_INVERT_MODE_MASK             (0x20000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_INVERT_MODE_SHIFT            (29U)
#define CSL_PLCONF_IATU_REG_CTRL_2_INVERT_MODE_RESETVAL         (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_INVERT_MODE_MAX              (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_MATCH_MODE_MASK              (0x40000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_MATCH_MODE_SHIFT             (30U)
#define CSL_PLCONF_IATU_REG_CTRL_2_MATCH_MODE_RESETVAL          (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_MATCH_MODE__0                (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_MATCH_MODE__1                (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_REGION_ENABLE_MASK           (0x80000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_REGION_ENABLE_SHIFT          (31U)
#define CSL_PLCONF_IATU_REG_CTRL_2_REGION_ENABLE_RESETVAL       (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_2_REGION_ENABLE_MAX            (0x00000001U)

#define CSL_PLCONF_IATU_REG_CTRL_2_RESETVAL                     (0x00000000U)

/* IATU_REG_LOWER_BASE */

#define CSL_PLCONF_IATU_REG_LOWER_BASE_IATU_REG_LOWER_BASE_MASK  (0xFFFFF000U)
#define CSL_PLCONF_IATU_REG_LOWER_BASE_IATU_REG_LOWER_BASE_SHIFT  (12U)
#define CSL_PLCONF_IATU_REG_LOWER_BASE_IATU_REG_LOWER_BASE_RESETVAL  (0x00000000U)
#define CSL_PLCONF_IATU_REG_LOWER_BASE_IATU_REG_LOWER_BASE_MAX  (0x000fffffU)

#define CSL_PLCONF_IATU_REG_LOWER_BASE_ZERO_MASK                (0x00000FFFU)
#define CSL_PLCONF_IATU_REG_LOWER_BASE_ZERO_SHIFT               (0U)
#define CSL_PLCONF_IATU_REG_LOWER_BASE_ZERO_RESETVAL            (0x00000000U)
#define CSL_PLCONF_IATU_REG_LOWER_BASE_ZERO_MAX                 (0x00000fffU)

#define CSL_PLCONF_IATU_REG_LOWER_BASE_RESETVAL                 (0x00000000U)

/* IATU_REG_UPPER_BASE */

#define CSL_PLCONF_IATU_REG_UPPER_BASE_IATU_REG_UPPER_BASE_MASK  (0xFFFFFFFFU)
#define CSL_PLCONF_IATU_REG_UPPER_BASE_IATU_REG_UPPER_BASE_SHIFT  (0U)
#define CSL_PLCONF_IATU_REG_UPPER_BASE_IATU_REG_UPPER_BASE_RESETVAL  (0x00000000U)
#define CSL_PLCONF_IATU_REG_UPPER_BASE_IATU_REG_UPPER_BASE_MAX  (0xffffffffU)

#define CSL_PLCONF_IATU_REG_UPPER_BASE_RESETVAL                 (0x00000000U)

/* IATU_REG_LIMIT */

#define CSL_PLCONF_IATU_REG_LIMIT_IATU_REG_LIMIT_MASK           (0xFFFFF000U)
#define CSL_PLCONF_IATU_REG_LIMIT_IATU_REG_LIMIT_SHIFT          (12U)
#define CSL_PLCONF_IATU_REG_LIMIT_IATU_REG_LIMIT_RESETVAL       (0x00000000U)
#define CSL_PLCONF_IATU_REG_LIMIT_IATU_REG_LIMIT_MAX            (0x000fffffU)

#define CSL_PLCONF_IATU_REG_LIMIT_ONES_MASK                     (0x00000FFFU)
#define CSL_PLCONF_IATU_REG_LIMIT_ONES_SHIFT                    (0U)
#define CSL_PLCONF_IATU_REG_LIMIT_ONES_RESETVAL                 (0x00000fffU)
#define CSL_PLCONF_IATU_REG_LIMIT_ONES_MAX                      (0x00000fffU)

#define CSL_PLCONF_IATU_REG_LIMIT_RESETVAL                      (0x00000fffU)

/* IATU_REG_LOWER_TARGET */

#define CSL_PLCONF_IATU_REG_LOWER_TARGET_IATU_REG_LOWER_TARGET_MASK  (0xFFFFF000U)
#define CSL_PLCONF_IATU_REG_LOWER_TARGET_IATU_REG_LOWER_TARGET_SHIFT  (12U)
#define CSL_PLCONF_IATU_REG_LOWER_TARGET_IATU_REG_LOWER_TARGET_RESETVAL  (0x00000000U)
#define CSL_PLCONF_IATU_REG_LOWER_TARGET_IATU_REG_LOWER_TARGET_MAX  (0x000fffffU)

#define CSL_PLCONF_IATU_REG_LOWER_TARGET_ZERO_MASK              (0x00000FFFU)
#define CSL_PLCONF_IATU_REG_LOWER_TARGET_ZERO_SHIFT             (0U)
#define CSL_PLCONF_IATU_REG_LOWER_TARGET_ZERO_RESETVAL          (0x00000000U)
#define CSL_PLCONF_IATU_REG_LOWER_TARGET_ZERO_MAX               (0x00000fffU)

#define CSL_PLCONF_IATU_REG_LOWER_TARGET_RESETVAL               (0x00000000U)

/* IATU_REG_UPPER_TARGET */

#define CSL_PLCONF_IATU_REG_UPPER_TARGET_IATU_REG_UPPER_TARGET_MASK  (0xFFFFFFFFU)
#define CSL_PLCONF_IATU_REG_UPPER_TARGET_IATU_REG_UPPER_TARGET_SHIFT  (0U)
#define CSL_PLCONF_IATU_REG_UPPER_TARGET_IATU_REG_UPPER_TARGET_RESETVAL  (0x00000000U)
#define CSL_PLCONF_IATU_REG_UPPER_TARGET_IATU_REG_UPPER_TARGET_MAX  (0xffffffffU)

#define CSL_PLCONF_IATU_REG_UPPER_TARGET_RESETVAL               (0x00000000U)

/* IATU_REG_CTRL_3 */

#define CSL_PLCONF_IATU_REG_CTRL_3_IATU_REG_CTRL_3_MASK         (0xFFFFFFFFU)
#define CSL_PLCONF_IATU_REG_CTRL_3_IATU_REG_CTRL_3_SHIFT        (0U)
#define CSL_PLCONF_IATU_REG_CTRL_3_IATU_REG_CTRL_3_RESETVAL     (0x00000000U)
#define CSL_PLCONF_IATU_REG_CTRL_3_IATU_REG_CTRL_3_MAX          (0xffffffffU)

#define CSL_PLCONF_IATU_REG_CTRL_3_RESETVAL                     (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
