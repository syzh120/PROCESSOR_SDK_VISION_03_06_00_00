/* hw_ctrl_core.h
*
* Register-level header file for CTRL_CORE
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

#ifndef HW_CTRL_CORE_H_
#define HW_CTRL_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/

#define CTRL_CORE_EXTERNAL_SEC                                      (0x0U)
#define CTRL_CORE_SEC_SW_HW                                         (0x4U)
#define CTRL_CORE_MREQDOMAIN_EXP1                                   (0x8U)
#define CTRL_CORE_MREQDOMAIN_EXP2                                   (0xcU)
#define CTRL_CORE_MREQDOMAIN_EXP3                                   (0x10U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1               (0x14U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1              (0x18U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF                     (0x1cU)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE                        (0x20U)
#define CTRL_CORE_SECURE_EMIF_OBFUSC_KEY                            (0x28U)
#define CTRL_CORE_SEC_RO                                            (0x2cU)
#define CTRL_CORE_SSM_END_FAST_SECRAM                               (0x30U)
#define CTRL_CORE_STATUS                                            (0x34U)
#define CTRL_CORE_SEC_STATUS                                        (0x38U)
#define CTRL_CORE_SEC_MEM_STATUS                                    (0x3cU)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE                           (0x40U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE                       (0x44U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1                             (0x48U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1                (0x4cU)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1                            (0x50U)
#define CTRL_CORE_HDCP_SEED0                                        (0x54U)
#define CTRL_CORE_HDCP_SEED1                                        (0x58U)
#define CTRL_CORE_KEK_SW_0                                          (0x60U)
#define CTRL_CORE_KEK_SW_1                                          (0x64U)
#define CTRL_CORE_KEK_SW_2                                          (0x68U)
#define CTRL_CORE_KEK_SW_3                                          (0x6cU)
#define CTRL_CORE_KEK_SW_4                                          (0x70U)
#define CTRL_CORE_KEK_SW_5                                          (0x74U)
#define CTRL_CORE_KEK_SW_6                                          (0x78U)
#define CTRL_CORE_KEK_SW_7                                          (0x7cU)
#define CTRL_CORE_CEK_0                                             (0x80U)
#define CTRL_CORE_CEK_1                                             (0x84U)
#define CTRL_CORE_CEK_2                                             (0x88U)
#define CTRL_CORE_CEK_3                                             (0x8cU)
#define CTRL_CORE_MSV                                               (0x90U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_0                                (0xccU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_1                                (0xd0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_2                                (0xd4U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_3                                (0xd8U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_4                                (0xdcU)
#define CTRL_CORE_STD_FUSE_OPP_BGAP                                 (0xe8U)
#define CTRL_CORE_STD_FUSE_MPK_0                                    (0x120U)
#define CTRL_CORE_STD_FUSE_MPK_1                                    (0x124U)
#define CTRL_CORE_STD_FUSE_MPK_2                                    (0x128U)
#define CTRL_CORE_STD_FUSE_MPK_3                                    (0x12cU)
#define CTRL_CORE_STD_FUSE_MPK_4                                    (0x130U)
#define CTRL_CORE_STD_FUSE_MPK_5                                    (0x134U)
#define CTRL_CORE_STD_FUSE_MPK_6                                    (0x138U)
#define CTRL_CORE_STD_FUSE_MPK_7                                    (0x13cU)
#define CTRL_CORE_CUST_FUSE_CEK_BCH_0                               (0x18cU)
#define CTRL_CORE_CUST_FUSE_CEK_BCH_1                               (0x190U)
#define CTRL_CORE_CUST_FUSE_CEK_BCH_2                               (0x194U)
#define CTRL_CORE_CUST_FUSE_CEK_BCH_3                               (0x198U)
#define CTRL_CORE_CUST_FUSE_CEK_BCH_4                               (0x19cU)
#define CTRL_CORE_CUST_FUSE_CEK2_BCH_0                              (0x1a0U)
#define CTRL_CORE_CUST_FUSE_CEK2_BCH_1                              (0x1a4U)
#define CTRL_CORE_CUST_FUSE_CEK2_BCH_2                              (0x1a8U)
#define CTRL_CORE_CUST_FUSE_CEK2_BCH_3                              (0x1acU)
#define CTRL_CORE_CUST_FUSE_CEK2_BCH_4                              (0x1b0U)
#define CTRL_CORE_CUST_FUSE_MSV_BCH_0                               (0x1b4U)
#define CTRL_CORE_CUST_FUSE_MSV_BCH_1                               (0x1b8U)
#define CTRL_CORE_CUST_FUSE_SWRV_0                                  (0x1bcU)
#define CTRL_CORE_CUST_FUSE_SWRV_1                                  (0x1c0U)
#define CTRL_CORE_CUST_FUSE_SWRV_2                                  (0x1c4U)
#define CTRL_CORE_CUST_FUSE_SWRV_3                                  (0x1c8U)
#define CTRL_CORE_CUST_FUSE_SWRV_4                                  (0x1ccU)
#define CTRL_CORE_CUST_FUSE_SWRV_5                                  (0x1d0U)
#define CTRL_CORE_CUST_FUSE_SWRV_6                                  (0x1d4U)
#define CTRL_CORE_BREG_SELECTION                                    (0x1e0U)
#define CTRL_CORE_DPLL_BCLK                                         (0x1e4U)
#define CTRL_CORE_DPLL_BADDR_BDATAW                                 (0x1e8U)
#define CTRL_CORE_DPLL_BDATAR                                       (0x1ecU)
#define CTRL_CORE_TEMP_SENSOR                                       (0x234U)
#define CTRL_CORE_STD_FUSE_DFT_MEM_RW                               (0x244U)
#define CTRL_CORE_DUCATI_MMUADDRTRANSLTR                            (0x258U)
#define CTRL_CORE_DUCATI_MMUADDRLOGICTR                             (0x25cU)
#define CTRL_CORE_HWOBS_CONTROL                                     (0x260U)
#define CTRL_CORE_BANDGAP_MASK_1                                    (0x280U)
#define CTRL_CORE_BANDGAP_THRESHOLD                                 (0x28cU)
#define CTRL_CORE_BANDGAP_TSHUT                                     (0x298U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP                               (0x2a4U)
#define CTRL_CORE_BANDGAP_STATUS_1                                  (0x2a8U)
#define CTRL_CORE_CEK2_0                                            (0x2b0U)
#define CTRL_CORE_CEK2_1                                            (0x2b4U)
#define CTRL_CORE_CEK2_2                                            (0x2b8U)
#define CTRL_CORE_CEK2_3                                            (0x2bcU)
#define CTRL_CORE_DTEMP_0                                           (0x2e8U)
#define CTRL_CORE_DTEMP_1                                           (0x2ecU)
#define CTRL_CORE_DTEMP_2                                           (0x2f0U)
#define CTRL_CORE_DTEMP_3                                           (0x2f4U)
#define CTRL_CORE_DTEMP_4                                           (0x2f8U)
#define CTRL_CORE_SMA_SW_0                                          (0x2fcU)
#define CTRL_CORE_MREQDOMAIN_EXP4                                   (0x300U)
#define CTRL_CORE_MREQDOMAIN_EXP5                                   (0x304U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2               (0x308U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2              (0x30cU)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2                             (0x314U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2                (0x318U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2                            (0x31cU)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1                         (0x320U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2                         (0x324U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3                         (0x328U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4                         (0x32cU)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5                         (0x330U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6                         (0x334U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_7                         (0x338U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1                           (0x33cU)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2                           (0x340U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_3                           (0x344U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4                           (0x348U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_5                           (0x34cU)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6                           (0x350U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_7                           (0x354U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE                             (0x36cU)
#define CTRL_CORE_CUST_FUSE_UID_0                                   (0x3e8U)
#define CTRL_CORE_CUST_FUSE_UID_1                                   (0x3ecU)
#define CTRL_CORE_CUST_FUSE_UID_2                                   (0x3f0U)
#define CTRL_CORE_CUST_FUSE_UID_3                                   (0x3f4U)
#define CTRL_CORE_CUST_FUSE_UID_4                                   (0x3f8U)
#define CTRL_CORE_CUST_FUSE_UID_5                                   (0x3fcU)
#define CTRL_CORE_CUST_FUSE_UID_6                                   (0x400U)
#define CTRL_CORE_MAC_ID_SW_0                                       (0x414U)
#define CTRL_CORE_MAC_ID_SW_1                                       (0x418U)
#define CTRL_CORE_MAC_ID_SW_2                                       (0x41cU)
#define CTRL_CORE_MAC_ID_SW_3                                       (0x420U)
#define CTRL_CORE_SW_ID_0                                           (0x424U)
#define CTRL_CORE_SW_ID_1                                           (0x428U)
#define CTRL_CORE_EFUSE_DISABLE_SW_0                                (0x42cU)
#define CTRL_CORE_SLEW_SW_0                                         (0x430U)
#define CTRL_CORE_SMA_SW_1                                          (0x434U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_8                         (0x43cU)
#define CTRL_CORE_MMR_LOCK_1                                        (0x440U)
#define CTRL_CORE_MMR_LOCK_2                                        (0x444U)
#define CTRL_CORE_MMR_LOCK_3                                        (0x448U)
#define CTRL_CORE_MMR_LOCK_4                                        (0x44cU)
#define CTRL_CORE_MMR_LOCK_5                                        (0x450U)
#define CTRL_CORE_CONTROL_IO_1                                      (0x454U)
#define CTRL_CORE_CONTROL_IO_2                                      (0x458U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT                             (0x45cU)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT                             (0x460U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE                            (0x46cU)
#define CTRL_CORE_TEMP_SENSOR_DSPEVE                                (0x474U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_0                        (0x4d8U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_1                        (0x4dcU)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_2                        (0x4e0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_3                        (0x4e4U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_4                        (0x4e8U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_0                               (0x4ecU)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_1                               (0x4f0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_2                               (0x4f4U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_3                               (0x4f8U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_4                               (0x4fcU)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE                                 (0x580U)
#define CTRL_CORE_EFUSE_DISABLE_SW_1                                (0x588U)
#define CTRL_CORE_NMI_DESTINATION_1                                 (0x58cU)
#define CTRL_CORE_NMI_DESTINATION_2                                 (0x590U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_0                         (0x5a0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_1                         (0x5a4U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_2                         (0x5a8U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_3                         (0x5acU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_4                         (0x5b0U)
#define CTRL_CORE_CUST_FUSE_SWRV_7                                  (0x5b4U)
#define CTRL_CORE_BOOTSTRAP                                         (0x5c4U)
#define CTRL_CORE_MEK_BCH_0                                         (0x600U)
#define CTRL_CORE_MEK_BCH_1                                         (0x604U)
#define CTRL_CORE_MEK_BCH_2                                         (0x608U)
#define CTRL_CORE_MEK_BCH_3                                         (0x60cU)
#define CTRL_CORE_MEK_BCH_4                                         (0x610U)
#define CTRL_CORE_MEK_BCH_5                                         (0x614U)
#define CTRL_CORE_MEK_BCH_6                                         (0x618U)
#define CTRL_CORE_MEK_BCH_7                                         (0x61cU)
#define CTRL_CORE_MEK_BCH_8                                         (0x620U)
#define CTRL_CORE_MEK_0                                             (0x624U)
#define CTRL_CORE_MEK_1                                             (0x628U)
#define CTRL_CORE_MEK_2                                             (0x62cU)
#define CTRL_CORE_MEK_3                                             (0x630U)
#define CTRL_CORE_MEK_4                                             (0x634U)
#define CTRL_CORE_MEK_5                                             (0x638U)
#define CTRL_CORE_MEK_6                                             (0x63cU)
#define CTRL_CORE_MEK_7                                             (0x640U)
#define CTRL_CORE_SMPK_BCH_0                                        (0x644U)
#define CTRL_CORE_SMPK_BCH_1                                        (0x648U)
#define CTRL_CORE_SMPK_BCH_2                                        (0x64cU)
#define CTRL_CORE_SMPK_BCH_3                                        (0x650U)
#define CTRL_CORE_SMPK_BCH_4                                        (0x654U)
#define CTRL_CORE_SMPK_BCH_5                                        (0x658U)
#define CTRL_CORE_SMPK_BCH_6                                        (0x65cU)
#define CTRL_CORE_SMPK_BCH_7                                        (0x660U)
#define CTRL_CORE_SMPK_BCH_8                                        (0x664U)
#define CTRL_CORE_SMPK_0                                            (0x668U)
#define CTRL_CORE_SMPK_1                                            (0x66cU)
#define CTRL_CORE_SMPK_2                                            (0x670U)
#define CTRL_CORE_SMPK_3                                            (0x674U)
#define CTRL_CORE_SMPK_4                                            (0x678U)
#define CTRL_CORE_SMPK_5                                            (0x67cU)
#define CTRL_CORE_SMPK_6                                            (0x680U)
#define CTRL_CORE_SMPK_7                                            (0x684U)
#define CTRL_CORE_SEC_SWRV_0                                        (0x688U)
#define CTRL_CORE_SEC_SWRV_1                                        (0x68cU)
#define CTRL_CORE_MREQDOMAIN_EXP6                                   (0x690U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_3                             (0x694U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_3                (0x698U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_3                            (0x69cU)

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define CTRL_CORE_EXTERNAL_SEC_COMPANION1_CHIP_ENABLE_SHIFT                             (3U)
#define CTRL_CORE_EXTERNAL_SEC_COMPANION1_CHIP_ENABLE_MASK                              (0x00000008U)
#define CTRL_CORE_EXTERNAL_SEC_COMPANION1_CHIP_ENABLE_ALLOWED                            (1U)
#define CTRL_CORE_EXTERNAL_SEC_COMPANION1_CHIP_ENABLE_FORBIDDEN                          (0U)

#define CTRL_CORE_EXTERNAL_SEC_I2CS_ENABLE_SHIFT                                        (2U)
#define CTRL_CORE_EXTERNAL_SEC_I2CS_ENABLE_MASK                                         (0x00000004U)
#define CTRL_CORE_EXTERNAL_SEC_I2CS_ENABLE_RESTRICTED                                    (1U)
#define CTRL_CORE_EXTERNAL_SEC_I2CS_ENABLE_UNRESTRICTED                                  (0U)

#define CTRL_CORE_EXTERNAL_SEC_COMPANION0_CHIP_ENABLE_SHIFT                             (1U)
#define CTRL_CORE_EXTERNAL_SEC_COMPANION0_CHIP_ENABLE_MASK                              (0x00000002U)
#define CTRL_CORE_EXTERNAL_SEC_COMPANION0_CHIP_ENABLE_ALLOWED                            (1U)
#define CTRL_CORE_EXTERNAL_SEC_COMPANION0_CHIP_ENABLE_FORBIDDEN                          (0U)

#define CTRL_CORE_EXTERNAL_SEC_SECURE_EXECUTION_INDICATOR_SHIFT                         (0U)
#define CTRL_CORE_EXTERNAL_SEC_SECURE_EXECUTION_INDICATOR_MASK                          (0x00000001U)
#define CTRL_CORE_EXTERNAL_SEC_SECURE_EXECUTION_INDICATOR_SET                            (1U)
#define CTRL_CORE_EXTERNAL_SEC_SECURE_EXECUTION_INDICATOR_RESET                          (0U)

#define CTRL_CORE_SEC_SW_HW_PARAM_SHIFT                                                 (0U)
#define CTRL_CORE_SEC_SW_HW_PARAM_MASK                                                  (0xffffffffU)

#define CTRL_CORE_MREQDOMAIN_EXP1_LOCK_SHIFT                                            (31U)
#define CTRL_CORE_MREQDOMAIN_EXP1_LOCK_MASK                                             (0x80000000U)

#define CTRL_CORE_MREQDOMAIN_EXP1_DSP2_CFG_SHIFT                                        (24U)
#define CTRL_CORE_MREQDOMAIN_EXP1_DSP2_CFG_MASK                                         (0x07000000U)

#define CTRL_CORE_MREQDOMAIN_EXP1_IPU1_SHIFT                                            (18U)
#define CTRL_CORE_MREQDOMAIN_EXP1_IPU1_MASK                                             (0x001c0000U)

#define CTRL_CORE_MREQDOMAIN_EXP1_ISS_SHIFT                                             (15U)
#define CTRL_CORE_MREQDOMAIN_EXP1_ISS_MASK                                              (0x00038000U)

#define CTRL_CORE_MREQDOMAIN_EXP1_DSS_SHIFT                                             (9U)
#define CTRL_CORE_MREQDOMAIN_EXP1_DSS_MASK                                              (0x00000e00U)

#define CTRL_CORE_MREQDOMAIN_EXP1_DSP1_CFG_SHIFT                                        (6U)
#define CTRL_CORE_MREQDOMAIN_EXP1_DSP1_CFG_MASK                                         (0x000001c0U)

#define CTRL_CORE_MREQDOMAIN_EXP1_P1500_SHIFT                                           (0U)
#define CTRL_CORE_MREQDOMAIN_EXP1_P1500_MASK                                            (0x00000007U)

#define CTRL_CORE_MREQDOMAIN_EXP2_LOCK_SHIFT                                            (31U)
#define CTRL_CORE_MREQDOMAIN_EXP2_LOCK_MASK                                             (0x80000000U)

#define CTRL_CORE_MREQDOMAIN_EXP2_EVE1_TC0_SHIFT                                        (6U)
#define CTRL_CORE_MREQDOMAIN_EXP2_EVE1_TC0_MASK                                         (0x000001c0U)

#define CTRL_CORE_MREQDOMAIN_EXP3_LOCK_SHIFT                                            (31U)
#define CTRL_CORE_MREQDOMAIN_EXP3_LOCK_MASK                                             (0x80000000U)

#define CTRL_CORE_MREQDOMAIN_EXP3_VIP1_P1_SHIFT                                         (15U)
#define CTRL_CORE_MREQDOMAIN_EXP3_VIP1_P1_MASK                                          (0x00038000U)

#define CTRL_CORE_MREQDOMAIN_EXP3_PRUSS1_PRU0_SHIFT                                     (9U)
#define CTRL_CORE_MREQDOMAIN_EXP3_PRUSS1_PRU0_MASK                                      (0x00000e00U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_MCASP1_SECDBG_EN_SHIFT            (26U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_MCASP1_SECDBG_EN_MASK             (0x04000000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_IPU1_SECDBG_EN_SHIFT              (22U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_IPU1_SECDBG_EN_MASK               (0x00400000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_EVE1_SECDBG_EN_SHIFT              (16U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_EVE1_SECDBG_EN_MASK               (0x00010000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_CT_TBR_SECDBG_EN_SHIFT            (13U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_CT_TBR_SECDBG_EN_MASK             (0x00002000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_DEBUGSS_SECDBG_EN_SHIFT           (12U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_DEBUGSS_SECDBG_EN_MASK            (0x00001000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_EMIF_SECDBG_EN_SHIFT              (11U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_EMIF_SECDBG_EN_MASK               (0x00000800U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_OCMC_ROM_SECDBG_EN_SHIFT          (10U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_OCMC_ROM_SECDBG_EN_MASK           (0x00000400U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_ISS_SECDBG_EN_SHIFT               (5U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_ISS_SECDBG_EN_MASK                (0x00000020U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_DSS_SECDBG_EN_SHIFT               (4U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_DSS_SECDBG_EN_MASK                (0x00000010U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_L3RAM1_SECDBG_EN_SHIFT            (3U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_L3RAM1_SECDBG_EN_MASK             (0x00000008U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_GPMC_SECDBG_EN_SHIFT              (0U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_1_GPMC_SECDBG_EN_MASK               (0x00000001U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_MCASP1_SECLOCK_EN_SHIFT          (26U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_MCASP1_SECLOCK_EN_MASK           (0x04000000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_IPU1_SECLOCK_EN_SHIFT            (22U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_IPU1_SECLOCK_EN_MASK             (0x00400000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_PCIESS1_SECLOCK_EN_SHIFT         (20U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_PCIESS1_SECLOCK_EN_MASK          (0x00100000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_EVE1_SECLOCK_EN_SHIFT            (16U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_EVE1_SECLOCK_EN_MASK             (0x00010000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_CT_TBR_SECLOCK_EN_SHIFT          (13U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_CT_TBR_SECLOCK_EN_MASK           (0x00002000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_DEBUGSS_SECLOCK_EN_SHIFT         (12U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_DEBUGSS_SECLOCK_EN_MASK          (0x00001000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_EMIF_SECLOCK_EN_SHIFT            (11U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_EMIF_SECLOCK_EN_MASK             (0x00000800U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_OCMC_ROM_SECLOCK_EN_SHIFT        (10U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_OCMC_ROM_SECLOCK_EN_MASK         (0x00000400U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_ISS_SECLOCK_EN_SHIFT             (5U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_ISS_SECLOCK_EN_MASK              (0x00000020U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_DSS_SECLOCK_EN_SHIFT             (4U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_DSS_SECLOCK_EN_MASK              (0x00000010U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_L3RAM1_SECLOCK_EN_SHIFT          (3U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_L3RAM1_SECLOCK_EN_MASK           (0x00000008U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_GPMC_SECLOCK_EN_SHIFT            (0U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_1_GPMC_SECLOCK_EN_MASK             (0x00000001U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER3_SECURETARGETS_SECDBG_EN_SHIFT    (28U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER3_SECURETARGETS_SECDBG_EN_MASK     (0x10000000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER3_AP_SECDBG_EN_SHIFT               (27U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER3_AP_SECDBG_EN_MASK                (0x08000000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER2_SECURETARGETS_SECDBG_EN_SHIFT    (26U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER2_SECURETARGETS_SECDBG_EN_MASK     (0x04000000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER2_AP_SECDBG_EN_SHIFT               (25U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER2_AP_SECDBG_EN_MASK                (0x02000000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4WAKEUP_SECURETARGETS_SECDBG_EN_SHIFT  (24U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4WAKEUP_SECURETARGETS_SECDBG_EN_MASK   (0x01000000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4WAKEUP_AP_SECDBG_EN_SHIFT             (23U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4WAKEUP_AP_SECDBG_EN_MASK              (0x00800000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4CONFIG_SECURETARGETS_SECDBG_EN_SHIFT  (21U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4CONFIG_SECURETARGETS_SECDBG_EN_MASK   (0x00200000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4CONFIG_AP_SECDBG_EN_SHIFT             (20U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4CONFIG_AP_SECDBG_EN_MASK              (0x00100000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER1_CRYPTO_SECDBG_EN_SHIFT           (17U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER1_CRYPTO_SECDBG_EN_MASK            (0x00020000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER1_AP_SECDBG_EN_SHIFT               (16U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER1_AP_SECDBG_EN_MASK                (0x00010000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER3_SECURETARGETS_SECLOCK_EN_SHIFT   (12U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER3_SECURETARGETS_SECLOCK_EN_MASK    (0x00001000U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER3_AP_SECLOCK_EN_SHIFT              (11U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER3_AP_SECLOCK_EN_MASK               (0x00000800U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER2_SECURETARGETS_SECLOCK_EN_SHIFT   (10U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER2_SECURETARGETS_SECLOCK_EN_MASK    (0x00000400U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER2_AP_SECLOCK_EN_SHIFT              (9U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER2_AP_SECLOCK_EN_MASK               (0x00000200U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4WAKEUP_SECURETARGETS_SECLOCK_EN_SHIFT (8U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4WAKEUP_SECURETARGETS_SECLOCK_EN_MASK  (0x00000100U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4WAKEUP_AP_SECLOCK_EN_SHIFT            (7U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4WAKEUP_AP_SECLOCK_EN_MASK             (0x00000080U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4CONFIG_SECURETARGETS_SECLOCK_EN_SHIFT (5U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4CONFIG_SECURETARGETS_SECLOCK_EN_MASK  (0x00000020U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4CONFIG_AP_SECLOCK_EN_SHIFT            (4U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4CONFIG_AP_SECLOCK_EN_MASK             (0x00000010U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER1_CRYPTO_SECLOCK_EN_SHIFT          (1U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER1_CRYPTO_SECLOCK_EN_MASK           (0x00000002U)

#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER1_AP_SECLOCK_EN_SHIFT              (0U)
#define CTRL_CORE_L4_HW_FW_EXPORTED_VALUES_CONF_L4PER1_AP_SECLOCK_EN_MASK               (0x00000001U)

#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER3_REQN_SHIFT                         (5U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER3_REQN_MASK                          (0x00000020U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER3_REQN_LOADED                         (1U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER3_REQN_REQUESTED                      (0U)

#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER2_REQN_SHIFT                         (4U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER2_REQN_MASK                          (0x00000010U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER2_REQN_LOADED                         (1U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER2_REQN_REQUESTED                      (0U)

#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER1_REQN_SHIFT                         (3U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER1_REQN_MASK                          (0x00000008U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER1_REQN_LOADED                         (1U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_PER1_REQN_REQUESTED                      (0U)

#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_CONFIG_REQN_SHIFT                       (2U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_CONFIG_REQN_MASK                        (0x00000004U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_CONFIG_REQN_LOADED                       (1U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_CONFIG_REQN_REQUESTED                    (0U)

#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_WAKEUP_REQN_SHIFT                       (1U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_WAKEUP_REQN_MASK                        (0x00000002U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_WAKEUP_REQN_LOADED                       (1U)
#define CTRL_CORE_SEC_LOAD_FW_EXPORTED_VALUE_L4_WAKEUP_REQN_REQUESTED                    (0U)

#define CTRL_CORE_SECURE_EMIF_OBFUSC_KEY_SHIFT                                          (0U)
#define CTRL_CORE_SECURE_EMIF_OBFUSC_KEY_MASK                                           (0x0000ffffU)

#define CTRL_CORE_SEC_RO_SECKEYACCENABLE_SHIFT                                          (3U)
#define CTRL_CORE_SEC_RO_SECKEYACCENABLE_MASK                                           (0x00000008U)
#define CTRL_CORE_SEC_RO_SECKEYACCENABLE_ALLOWED                                         (1U)
#define CTRL_CORE_SEC_RO_SECKEYACCENABLE_FORBIDDEN                                       (0U)

#define CTRL_CORE_SEC_RO_SECURE_EMIF_OBFUSC_EN_SHIFT                                    (2U)
#define CTRL_CORE_SEC_RO_SECURE_EMIF_OBFUSC_EN_MASK                                     (0x00000004U)

#define CTRL_CORE_SEC_RO_SECURE_SAR_MEMORY_EN_SHIFT                                     (0U)
#define CTRL_CORE_SEC_RO_SECURE_SAR_MEMORY_EN_MASK                                      (0x00000001U)
#define CTRL_CORE_SEC_RO_SECURE_SAR_MEMORY_EN                                            (1U)
#define CTRL_CORE_SEC_RO_SECURE_SAR_MEMORY_EN_RW                                         (0U)

#define CTRL_CORE_SSM_END_FAST_SECRAM_SHIFT                                             (10U)
#define CTRL_CORE_SSM_END_FAST_SECRAM_MASK                                              (0x0000fc00U)

#define CTRL_CORE_STATUS_HIGHLY_SECURE_SHIFT                                            (9U)
#define CTRL_CORE_STATUS_HIGHLY_SECURE_MASK                                             (0x00000200U)

#define CTRL_CORE_STATUS_DEVICE_TYPE_SHIFT                                              (6U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_MASK                                               (0x000001c0U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_B_2                                             (6U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_B_0                                             (4U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_E                                               (1U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_GP                                              (3U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_T                                               (0U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_B_3                                             (7U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_HS                                              (2U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_B_1                                             (5U)

#define CTRL_CORE_SEC_STATUS_IPU1_RST_ACT_ST_SHIFT                                      (23U)
#define CTRL_CORE_SEC_STATUS_IPU1_RST_ACT_ST_MASK                                       (0x00800000U)
#define CTRL_CORE_SEC_STATUS_IPU1_RST_ACT_ST_IPU1RESET                                   (1U)
#define CTRL_CORE_SEC_STATUS_IPU1_RST_ACT_ST_NO_IPU1RESET                                (0U)

#define CTRL_CORE_SEC_STATUS_EVE1_RST_ACT_ST_SHIFT                                      (19U)
#define CTRL_CORE_SEC_STATUS_EVE1_RST_ACT_ST_MASK                                       (0x00080000U)
#define CTRL_CORE_SEC_STATUS_EVE1_RST_ACT_ST_EVE1RESET                                   (1U)
#define CTRL_CORE_SEC_STATUS_EVE1_RST_ACT_ST_NO_EVE1RESET                                (0U)

#define CTRL_CORE_SEC_STATUS_DSP2_RST_ACT_ST_SHIFT                                      (18U)
#define CTRL_CORE_SEC_STATUS_DSP2_RST_ACT_ST_MASK                                       (0x00040000U)
#define CTRL_CORE_SEC_STATUS_DSP2_RST_ACT_ST_DSP2RESET                                   (1U)
#define CTRL_CORE_SEC_STATUS_DSP2_RST_ACT_ST_NO_DSP2RESET                                (0U)

#define CTRL_CORE_SEC_STATUS_CPFROM_RST_ACT_ST_SHIFT                                    (15U)
#define CTRL_CORE_SEC_STATUS_CPFROM_RST_ACT_ST_MASK                                     (0x00008000U)
#define CTRL_CORE_SEC_STATUS_CPFROM_RST_ACT_ST_CPFROMRESET                               (1U)
#define CTRL_CORE_SEC_STATUS_CPFROM_RST_ACT_ST_NO_CPFROMRESET                            (0U)

#define CTRL_CORE_SEC_STATUS_EMU_RST_ACT_ST_SHIFT                                       (14U)
#define CTRL_CORE_SEC_STATUS_EMU_RST_ACT_ST_MASK                                        (0x00004000U)
#define CTRL_CORE_SEC_STATUS_EMU_RST_ACT_ST_EMURESET                                     (1U)
#define CTRL_CORE_SEC_STATUS_EMU_RST_ACT_ST_NO_EMURESET                                  (0U)

#define CTRL_CORE_SEC_STATUS_L4PER_RST_ACT_ST_SHIFT                                     (13U)
#define CTRL_CORE_SEC_STATUS_L4PER_RST_ACT_ST_MASK                                      (0x00002000U)
#define CTRL_CORE_SEC_STATUS_L4PER_RST_ACT_ST_L4PERRESET                                 (1U)
#define CTRL_CORE_SEC_STATUS_L4PER_RST_ACT_ST_NO_L4PERRESET                              (0U)

#define CTRL_CORE_SEC_STATUS_L3INIT_RST_ACT_ST_SHIFT                                    (12U)
#define CTRL_CORE_SEC_STATUS_L3INIT_RST_ACT_ST_MASK                                     (0x00001000U)
#define CTRL_CORE_SEC_STATUS_L3INIT_RST_ACT_ST_L3INITRESET                               (1U)
#define CTRL_CORE_SEC_STATUS_L3INIT_RST_ACT_ST_NO_L3INITRESET                            (0U)

#define CTRL_CORE_SEC_STATUS_RST_ACT_ST_SHIFT                                           (11U)
#define CTRL_CORE_SEC_STATUS_RST_ACT_ST_MASK                                            (0x00000800U)
#define CTRL_CORE_SEC_STATUS_RST_ACT_ST_CORERESET                                        (1U)
#define CTRL_CORE_SEC_STATUS_RST_ACT_ST_NO_CORERESET                                     (0U)

#define CTRL_CORE_SEC_STATUS_DSS_RST_ACT_ST_SHIFT                                       (7U)
#define CTRL_CORE_SEC_STATUS_DSS_RST_ACT_ST_MASK                                        (0x00000080U)
#define CTRL_CORE_SEC_STATUS_DSS_RST_ACT_ST_DSSRESET                                     (1U)
#define CTRL_CORE_SEC_STATUS_DSS_RST_ACT_ST_NO_DSSRESET                                  (0U)

#define CTRL_CORE_SEC_STATUS_DSP1_RST_ACT_ST_SHIFT                                      (6U)
#define CTRL_CORE_SEC_STATUS_DSP1_RST_ACT_ST_MASK                                       (0x00000040U)
#define CTRL_CORE_SEC_STATUS_DSP1_RST_ACT_ST_DSP1RESET                                   (1U)
#define CTRL_CORE_SEC_STATUS_DSP1_RST_ACT_ST_NO_DSP1RESET                                (0U)

#define CTRL_CORE_SEC_STATUS_VIOL_RST_ACT_ST_SHIFT                                      (3U)
#define CTRL_CORE_SEC_STATUS_VIOL_RST_ACT_ST_MASK                                       (0x00000008U)
#define CTRL_CORE_SEC_STATUS_VIOL_RST_ACT_ST_VIOLATION                                   (1U)
#define CTRL_CORE_SEC_STATUS_VIOL_RST_ACT_ST_NO_VIOLATION                                (0U)

#define CTRL_CORE_SEC_STATUS_WD_RST_ACT_ST_SHIFT                                        (2U)
#define CTRL_CORE_SEC_STATUS_WD_RST_ACT_ST_MASK                                         (0x00000004U)
#define CTRL_CORE_SEC_STATUS_WD_RST_ACT_ST_PREV_WAS_SWD                                  (1U)
#define CTRL_CORE_SEC_STATUS_WD_RST_ACT_ST_PREV_WAS_NOT_SWD                              (0U)

#define CTRL_CORE_SEC_STATUS_GLBL_WARM_RST_ACT_ST_SHIFT                                 (1U)
#define CTRL_CORE_SEC_STATUS_GLBL_WARM_RST_ACT_ST_MASK                                  (0x00000002U)
#define CTRL_CORE_SEC_STATUS_GLBL_WARM_RST_ACT_ST_PREV_WAS_SW                            (1U)
#define CTRL_CORE_SEC_STATUS_GLBL_WARM_RST_ACT_ST_PREV_WAS_NOT_SW                        (0U)

#define CTRL_CORE_SEC_STATUS_POWERON_RST_ACT_ST_SHIFT                                   (0U)
#define CTRL_CORE_SEC_STATUS_POWERON_RST_ACT_ST_MASK                                    (0x00000001U)
#define CTRL_CORE_SEC_STATUS_POWERON_RST_ACT_ST_PREV_WAS_PWR                             (1U)
#define CTRL_CORE_SEC_STATUS_POWERON_RST_ACT_ST_PREV_WAS_NOT_PWR                         (0U)

#define CTRL_CORE_SEC_MEM_STATUS_L3SECRAM1_NOT_ACCESSIBLE_SHIFT                         (19U)
#define CTRL_CORE_SEC_MEM_STATUS_L3SECRAM1_NOT_ACCESSIBLE_MASK                          (0x00080000U)
#define CTRL_CORE_SEC_MEM_STATUS_L3SECRAM1_NOT_ACCESSIBLE_NO_ACCESS                      (1U)
#define CTRL_CORE_SEC_MEM_STATUS_L3SECRAM1_NOT_ACCESSIBLE_ACCESS                         (0U)

#define CTRL_CORE_SEC_MEM_STATUS_FASTSECRAMBANK_NOT_ACCESSIBLE_SHIFT                    (18U)
#define CTRL_CORE_SEC_MEM_STATUS_FASTSECRAMBANK_NOT_ACCESSIBLE_MASK                     (0x00040000U)
#define CTRL_CORE_SEC_MEM_STATUS_FASTSECRAMBANK_NOT_ACCESSIBLE_NO_ACCESS                 (1U)
#define CTRL_CORE_SEC_MEM_STATUS_FASTSECRAMBANK_NOT_ACCESSIBLE_ACCESS                    (0U)

#define CTRL_CORE_SEC_MEM_STATUS_L3SECRAM1_DESTROYED_SHIFT                              (3U)
#define CTRL_CORE_SEC_MEM_STATUS_L3SECRAM1_DESTROYED_MASK                               (0x00000008U)
#define CTRL_CORE_SEC_MEM_STATUS_L3SECRAM1_DESTROYED                                     (1U)
#define CTRL_CORE_SEC_MEM_STATUS_L3SECRAM1_DESTROYED_SAFE                                (0U)

#define CTRL_CORE_SEC_MEM_STATUS_FASTSECRAMBANK_DESTROYED_SHIFT                         (2U)
#define CTRL_CORE_SEC_MEM_STATUS_FASTSECRAMBANK_DESTROYED_MASK                          (0x00000004U)
#define CTRL_CORE_SEC_MEM_STATUS_FASTSECRAMBANK_DESTROYED                                (1U)
#define CTRL_CORE_SEC_MEM_STATUS_FASTSECRAMBANK_DESTROYED_SAFE                           (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_IPU1_RST_ACT_ST_SHIFT                         (21U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_IPU1_RST_ACT_ST_MASK                          (0x00200000U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_IPU1_RST_ACT_ST_UNMASKED                       (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_IPU1_RST_ACT_ST_MASKED                         (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_EVE1_RST_ACT_ST_SHIFT                         (17U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_EVE1_RST_ACT_ST_MASK                          (0x00020000U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_EVE1_RST_ACT_ST_UNMASKED                       (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_EVE1_RST_ACT_ST_MASKED                         (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSP2_RST_ACT_ST_SHIFT                         (16U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSP2_RST_ACT_ST_MASK                          (0x00010000U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSP2_RST_ACT_ST_UNMASKED                       (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSP2_RST_ACT_ST_MASKED                         (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_CPFROM_RST_ACT_ST_SHIFT                       (15U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_CPFROM_RST_ACT_ST_MASK                        (0x00008000U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_CPFROM_RST_ACT_ST_UNMASKED                     (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_CPFROM_RST_ACT_ST_MASKED                       (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_EMU_RST_ACT_ST_SHIFT                          (14U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_EMU_RST_ACT_ST_MASK                           (0x00004000U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_EMU_RST_ACT_ST_UNMASKED                        (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_EMU_RST_ACT_ST_MASKED                          (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_L4PER_RST_ACT_ST_SHIFT                        (13U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_L4PER_RST_ACT_ST_MASK                         (0x00002000U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_L4PER_RST_ACT_ST_UNMASKED                      (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_L4PER_RST_ACT_ST_MASKED                        (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_L3INIT_RST_ACT_ST_SHIFT                       (12U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_L3INIT_RST_ACT_ST_MASK                        (0x00001000U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_L3INIT_RST_ACT_ST_UNMASKED                     (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_L3INIT_RST_ACT_ST_MASKED                       (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_RST_ACT_ST_SHIFT                              (11U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_RST_ACT_ST_MASK                               (0x00000800U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_RST_ACT_ST_UNMASKED                            (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_RST_ACT_ST_MASKED                              (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSS_RST_ACT_ST_SHIFT                          (7U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSS_RST_ACT_ST_MASK                           (0x00000080U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSS_RST_ACT_ST_UNMASKED                        (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSS_RST_ACT_ST_MASKED                          (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSP1_RST_ACT_ST_SHIFT                         (6U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSP1_RST_ACT_ST_MASK                          (0x00000040U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSP1_RST_ACT_ST_UNMASKED                       (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DSP1_RST_ACT_ST_MASKED                         (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DEVICE_OFF_WKUP_SHIFT                         (4U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DEVICE_OFF_WKUP_MASK                          (0x00000010U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DEVICE_OFF_WKUP_UNMASKED                       (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_DEVICE_OFF_WKUP_MASKED                         (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_VIOL_RST_ACT_ST_SHIFT                         (3U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_VIOL_RST_ACT_ST_MASK                          (0x00000008U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_VIOL_RST_ACT_ST_UNMASKED                       (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_VIOL_RST_ACT_ST_MASKED                         (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_WD_RST_ACT_ST_SHIFT                           (2U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_WD_RST_ACT_ST_MASK                            (0x00000004U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_WD_RST_ACT_ST_UNMASKED                         (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_WD_RST_ACT_ST_MASKED                           (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_GLBL_WARM_RST_ACT_ST_SHIFT                    (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_GLBL_WARM_RST_ACT_ST_MASK                     (0x00000002U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_GLBL_WARM_RST_ACT_ST_UNMASKED                  (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_GLBL_WARM_RST_ACT_ST_MASKED                    (0U)

#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_POWERON_RST_ACT_ST_SHIFT                      (0U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_POWERON_RST_ACT_ST_MASK                       (0x00000001U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_POWERON_RST_ACT_ST_UNMASKED                    (1U)
#define CTRL_CORE_SEC_STATUS_MASK_DISABLE_POWERON_RST_ACT_ST_MASKED                      (0U)

#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_L3SECRAM1_NOT_ACCESSIBLE_SHIFT            (19U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_L3SECRAM1_NOT_ACCESSIBLE_MASK             (0x00080000U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_L3SECRAM1_NOT_ACCESSIBLE_UNMASKED          (1U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_L3SECRAM1_NOT_ACCESSIBLE_MASKED            (0U)

#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_FASTSECRAMBANK_NOT_ACCESSIBLE_SHIFT       (18U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_FASTSECRAMBANK_NOT_ACCESSIBLE_MASK        (0x00040000U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_FASTSECRAMBANK_NOT_ACCESSIBLE_UNMASKED     (1U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_FASTSECRAMBANK_NOT_ACCESSIBLE_MASKED       (0U)

#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_L3SECRAM1_DESTROYED_SHIFT                 (3U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_L3SECRAM1_DESTROYED_MASK                  (0x00000008U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_L3SECRAM1_DESTROYED_UNMASKED               (1U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_L3SECRAM1_DESTROYED_MASKED                 (0U)

#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_FASTSECRAMBANK_DESTROYED_SHIFT            (2U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_FASTSECRAMBANK_DESTROYED_MASK             (0x00000004U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_FASTSECRAMBANK_DESTROYED_UNMASKED          (1U)
#define CTRL_CORE_SEC_MEM_STATUS_MASK_DISABLE_FASTSECRAMBANK_DESTROYED_MASKED            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE1_FW_ERROR_SHIFT                             (28U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE1_FW_ERROR_MASK                              (0x10000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE1_FW_ERROR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE1_FW_ERROR_NO                                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_OCMC_ROM_FW_ERROR_SHIFT                         (27U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_OCMC_ROM_FW_ERROR_MASK                          (0x08000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_OCMC_ROM_FW_ERROR                                (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_OCMC_ROM_FW_ERROR_NO                             (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_CT_TRACE_BUFFER_ROUTER_FW_ERROR_SHIFT           (26U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_CT_TRACE_BUFFER_ROUTER_FW_ERROR_MASK            (0x04000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_CT_TRACE_BUFFER_ROUTER_FW_ERROR                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_CT_TRACE_BUFFER_ROUTER_FW_ERROR_NO               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_WAKEUP_FW_ERROR_SHIFT                        (22U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_WAKEUP_FW_ERROR_MASK                         (0x00400000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_WAKEUP_FW_ERROR_L4WKUP                        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_WAKEUP_FW_ERROR_NO_L4WKUP                     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DEBUGSS_FW_ERROR_SHIFT                          (18U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DEBUGSS_FW_ERROR_MASK                           (0x00040000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DEBUGSS_FW_ERROR                                 (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DEBUGSS_FW_ERROR_NO                              (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_SHIFT                        (17U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_MASK                         (0x00020000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_L4CONFIG                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_NO_L4CONFIG                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_PERIPH1_FW_ERROR_SHIFT                       (16U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_PERIPH1_FW_ERROR_MASK                        (0x00010000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_PERIPH1_FW_ERROR_L4PERIPH1                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_PERIPH1_FW_ERROR_NO_L4PERIPH1                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_ISS_FW_ERROR_SHIFT                              (15U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_ISS_FW_ERROR_MASK                               (0x00008000U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DSS_FW_ERROR_SHIFT                              (14U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DSS_FW_ERROR_MASK                               (0x00004000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DSS_FW_ERROR                                     (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DSS_FW_ERROR_NO                                  (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_SECMOD_FW_ERROR_SHIFT                           (11U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_SECMOD_FW_ERROR_MASK                            (0x00000800U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_SECMOD_FW_ERROR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_SECMOD_FW_ERROR_NO                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DISPDMA_ACC_ERROR_SHIFT                         (10U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DISPDMA_ACC_ERROR_MASK                          (0x00000400U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DISPDMA_ACC_ERROR_TARGET_FW                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DISPDMA_ACC_ERROR_NO_TARGET_FW                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IPU1_FW_ERROR_SHIFT                             (5U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IPU1_FW_ERROR_MASK                              (0x00000020U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IPU1_FW_ERROR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IPU1_FW_ERROR_NO                                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EMIF_FW_ERROR_SHIFT                             (3U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EMIF_FW_ERROR_MASK                              (0x00000008U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EMIF_FW_ERROR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EMIF_FW_ERROR_NO                                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPMC_FW_ERROR_SHIFT                             (2U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPMC_FW_ERROR_MASK                              (0x00000004U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPMC_FW_ERROR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPMC_FW_ERROR_NO                                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_SHIFT                           (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_MASK                            (0x00000002U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_NO                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_EVE1_FW_ERROR_SHIFT                (28U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_EVE1_FW_ERROR_MASK                 (0x10000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_EVE1_FW_ERROR_UNMASKED              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_EVE1_FW_ERROR_MASKED                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_OCMC_ROM_FW_ERROR_SHIFT            (27U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_OCMC_ROM_FW_ERROR_MASK             (0x08000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_OCMC_ROM_FW_ERROR_UNMASKED          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_OCMC_ROM_FW_ERROR_MASKED            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_CT_TRACE_BUFFER_ROUTER_FW_ERROR_SHIFT   (26U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_CT_TRACE_BUFFER_ROUTER_FW_ERROR_MASK   (0x04000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_CT_TRACE_BUFFER_ROUTER_FW_ERROR_UNMASKED   (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_CT_TRACE_BUFFER_ROUTER_FW_ERROR_MASKED   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_WAKEUP_FW_ERROR_SHIFT           (22U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_WAKEUP_FW_ERROR_MASK            (0x00400000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_WAKEUP_FW_ERROR_UNMASKED         (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_WAKEUP_FW_ERROR_MASKED           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DEBUGSS_FW_ERROR_SHIFT             (18U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DEBUGSS_FW_ERROR_MASK              (0x00040000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DEBUGSS_FW_ERROR_UNMASKED           (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DEBUGSS_FW_ERROR_MASKED             (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_CONFIG_FW_ERROR_SHIFT           (17U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_CONFIG_FW_ERROR_MASK            (0x00020000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_CONFIG_FW_ERROR_UNMASKED         (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_CONFIG_FW_ERROR_MASKED           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_PERIPH1_FW_ERROR_SHIFT          (16U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_PERIPH1_FW_ERROR_MASK           (0x00010000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_PERIPH1_FW_ERROR_UNMASKED        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L4_PERIPH1_FW_ERROR_MASKED          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_ISS_FW_ERROR_SHIFT                 (15U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_ISS_FW_ERROR_MASK                  (0x00008000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_ISS_FW_ERROR_UNMASKED               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_ISS_FW_ERROR_MASKED                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DSS_FW_ERROR_SHIFT                 (14U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DSS_FW_ERROR_MASK                  (0x00004000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DSS_FW_ERROR_UNMASKED               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DSS_FW_ERROR_MASKED                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_SECMOD_FW_ERROR_SHIFT              (11U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_SECMOD_FW_ERROR_MASK               (0x00000800U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_SECMOD_FW_ERROR_UNMASKED            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_SECMOD_FW_ERROR_MASKED              (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DISPDMA_ACC_ERROR_SHIFT            (10U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DISPDMA_ACC_ERROR_MASK             (0x00000400U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DISPDMA_ACC_ERROR_UNMASKED          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_DISPDMA_ACC_ERROR_MASKED            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_IPU1_FW_ERROR_SHIFT                (5U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_IPU1_FW_ERROR_MASK                 (0x00000020U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_IPU1_FW_ERROR_UNMASKED              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_IPU1_FW_ERROR_MASKED                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_EMIF_FW_ERROR_SHIFT                (3U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_EMIF_FW_ERROR_MASK                 (0x00000008U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_EMIF_FW_ERROR_UNMASKED              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_EMIF_FW_ERROR_MASKED                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_GPMC_FW_ERROR_SHIFT                (2U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_GPMC_FW_ERROR_MASK                 (0x00000004U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_GPMC_FW_ERROR_UNMASKED              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_GPMC_FW_ERROR_MASKED                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L3RAM1_FW_ERROR_SHIFT              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L3RAM1_FW_ERROR_MASK               (0x00000002U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L3RAM1_FW_ERROR_UNMASKED            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_1_L3RAM1_FW_ERROR_MASKED              (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE1_DBGFW_ERROR_SHIFT                         (28U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE1_DBGFW_ERROR_MASK                          (0x10000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE1_DBGFW_ERROR_FW                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE1_DBGFW_ERROR_NO_FW                          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_OCMC_ROM_DBGFW_ERROR_SHIFT                     (27U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_OCMC_ROM_DBGFW_ERROR_MASK                      (0x08000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_OCMC_ROM_DBGFW_ERROR_FW                         (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_OCMC_ROM_DBGFW_ERROR_NO_FW                      (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_CT_TRACE_BUFFER_ROUTER_DBGFW_ERROR_SHIFT       (26U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_CT_TRACE_BUFFER_ROUTER_DBGFW_ERROR_MASK        (0x04000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_CT_TRACE_BUFFER_ROUTER_DBGFW_ERROR_FW           (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_CT_TRACE_BUFFER_ROUTER_DBGFW_ERROR_NO_FW        (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_WAKEUP_DBGFW_ERROR_SHIFT                    (22U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_WAKEUP_DBGFW_ERROR_MASK                     (0x00400000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_WAKEUP_DBGFW_ERROR_L4WKUP_FW                 (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_WAKEUP_DBGFW_ERROR_NO_L4WKUP_FW              (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DEBUGSS_DBGFW_ERROR_SHIFT                      (18U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DEBUGSS_DBGFW_ERROR_MASK                       (0x00040000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DEBUGSS_DBGFW_ERROR_FW                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DEBUGSS_DBGFW_ERROR_NO_FW                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_CONFIG_DBGFW_ERROR_SHIFT                    (17U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_CONFIG_DBGFW_ERROR_MASK                     (0x00020000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_CONFIG_DBGFW_ERROR_L4CONFIG_FW               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_CONFIG_DBGFW_ERROR_NO_L4CONFIG_FW            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_PERIPH1_DBGFW_ERROR_SHIFT                   (16U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_PERIPH1_DBGFW_ERROR_MASK                    (0x00010000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_PERIPH1_DBGFW_ERROR_L4PERIPH1_FW             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_PERIPH1_DBGFW_ERROR_NO_L4PERIPH1_FW          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_ISS_DBGFW_ERROR_SHIFT                          (15U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_ISS_DBGFW_ERROR_MASK                           (0x00008000U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DSS_DBGFW_ERROR_SHIFT                          (14U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DSS_DBGFW_ERROR_MASK                           (0x00004000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DSS_DBGFW_ERROR_FW                              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DSS_DBGFW_ERROR_NO_FW                           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IPU1_DBGFW_ERROR_SHIFT                         (5U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IPU1_DBGFW_ERROR_MASK                          (0x00000020U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IPU1_DBGFW_ERROR_FW                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IPU1_DBGFW_ERROR_NO_FW                          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EMIF_DBGFW_ERROR_SHIFT                         (3U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EMIF_DBGFW_ERROR_MASK                          (0x00000008U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EMIF_DBGFW_ERROR_FW                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EMIF_DBGFW_ERROR_NO_FW                          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPMC_DBGFW_ERROR_SHIFT                         (2U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPMC_DBGFW_ERROR_MASK                          (0x00000004U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPMC_DBGFW_ERROR_FW                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPMC_DBGFW_ERROR_NO_FW                          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L3RAM1_DBGFW_ERROR_SHIFT                       (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L3RAM1_DBGFW_ERROR_MASK                        (0x00000002U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L3RAM1_DBGFW_ERROR_FW                           (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L3RAM1_DBGFW_ERROR_NO_FW                        (0U)

#define CTRL_CORE_HDCP_SEED0_SHIFT                                                      (0U)
#define CTRL_CORE_HDCP_SEED0_MASK                                                       (0xffffffffU)

#define CTRL_CORE_HDCP_SEED1_SHIFT                                                      (0U)
#define CTRL_CORE_HDCP_SEED1_MASK                                                       (0xffffffffU)

#define CTRL_CORE_KEK_SW_0_STD_FUSE_SHIFT                                               (0U)
#define CTRL_CORE_KEK_SW_0_STD_FUSE_MASK                                                (0xffffffffU)

#define CTRL_CORE_KEK_SW_1_STD_FUSE_SHIFT                                               (0U)
#define CTRL_CORE_KEK_SW_1_STD_FUSE_MASK                                                (0xffffffffU)

#define CTRL_CORE_KEK_SW_2_STD_FUSE_SHIFT                                               (0U)
#define CTRL_CORE_KEK_SW_2_STD_FUSE_MASK                                                (0xffffffffU)

#define CTRL_CORE_KEK_SW_3_STD_FUSE_SHIFT                                               (0U)
#define CTRL_CORE_KEK_SW_3_STD_FUSE_MASK                                                (0xffffffffU)

#define CTRL_CORE_KEK_SW_4_STD_FUSE_SHIFT                                               (0U)
#define CTRL_CORE_KEK_SW_4_STD_FUSE_MASK                                                (0xffffffffU)

#define CTRL_CORE_KEK_SW_5_STD_FUSE_SHIFT                                               (0U)
#define CTRL_CORE_KEK_SW_5_STD_FUSE_MASK                                                (0xffffffffU)

#define CTRL_CORE_KEK_SW_6_STD_FUSE_SHIFT                                               (0U)
#define CTRL_CORE_KEK_SW_6_STD_FUSE_MASK                                                (0xffffffffU)

#define CTRL_CORE_KEK_SW_7_STD_FUSE_SHIFT                                               (0U)
#define CTRL_CORE_KEK_SW_7_STD_FUSE_MASK                                                (0xffffffffU)

#define CTRL_CORE_CEK_0_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_CEK_0_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_CEK_1_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_CEK_1_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_CEK_2_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_CEK_2_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_CEK_3_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_CEK_3_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_MSV_CUST_FUSE_SHIFT                                                   (0U)
#define CTRL_CORE_MSV_CUST_FUSE_MASK                                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_0_SHIFT                                              (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_0_MASK                                               (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_1_SHIFT                                              (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_1_MASK                                               (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_2_SHIFT                                              (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_2_MASK                                               (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_3_SHIFT                                              (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_3_MASK                                               (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_4_SHIFT                                              (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_4_MASK                                               (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_BGAP_SHIFT                                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_MASK                                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_0_SHIFT                                                  (0U)
#define CTRL_CORE_STD_FUSE_MPK_0_MASK                                                   (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_1_SHIFT                                                  (0U)
#define CTRL_CORE_STD_FUSE_MPK_1_MASK                                                   (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_2_SHIFT                                                  (0U)
#define CTRL_CORE_STD_FUSE_MPK_2_MASK                                                   (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_3_SHIFT                                                  (0U)
#define CTRL_CORE_STD_FUSE_MPK_3_MASK                                                   (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_4_SHIFT                                                  (0U)
#define CTRL_CORE_STD_FUSE_MPK_4_MASK                                                   (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_5_SHIFT                                                  (0U)
#define CTRL_CORE_STD_FUSE_MPK_5_MASK                                                   (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_6_SHIFT                                                  (0U)
#define CTRL_CORE_STD_FUSE_MPK_6_MASK                                                   (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_7_SHIFT                                                  (0U)
#define CTRL_CORE_STD_FUSE_MPK_7_MASK                                                   (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_CEK_BCH_0_SHIFT                                             (0U)
#define CTRL_CORE_CUST_FUSE_CEK_BCH_0_MASK                                              (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_CEK_BCH_1_SHIFT                                             (0U)
#define CTRL_CORE_CUST_FUSE_CEK_BCH_1_MASK                                              (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_CEK_BCH_2_SHIFT                                             (0U)
#define CTRL_CORE_CUST_FUSE_CEK_BCH_2_MASK                                              (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_CEK_BCH_3_SHIFT                                             (0U)
#define CTRL_CORE_CUST_FUSE_CEK_BCH_3_MASK                                              (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_CEK_BCH_4_SHIFT                                             (0U)
#define CTRL_CORE_CUST_FUSE_CEK_BCH_4_MASK                                              (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_CEK2_BCH_0_SHIFT                                            (0U)
#define CTRL_CORE_CUST_FUSE_CEK2_BCH_0_MASK                                             (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_CEK2_BCH_1_SHIFT                                            (0U)
#define CTRL_CORE_CUST_FUSE_CEK2_BCH_1_MASK                                             (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_CEK2_BCH_2_SHIFT                                            (0U)
#define CTRL_CORE_CUST_FUSE_CEK2_BCH_2_MASK                                             (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_CEK2_BCH_3_SHIFT                                            (0U)
#define CTRL_CORE_CUST_FUSE_CEK2_BCH_3_MASK                                             (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_CEK2_BCH_4_SHIFT                                            (0U)
#define CTRL_CORE_CUST_FUSE_CEK2_BCH_4_MASK                                             (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_MSV_BCH_0_SHIFT                                             (0U)
#define CTRL_CORE_CUST_FUSE_MSV_BCH_0_MASK                                              (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_MSV_BCH_1_SHIFT                                             (0U)
#define CTRL_CORE_CUST_FUSE_MSV_BCH_1_MASK                                              (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_0_SHIFT                                                (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_0_MASK                                                 (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_1_SHIFT                                                (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_1_MASK                                                 (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_2_SHIFT                                                (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_2_MASK                                                 (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_3_SHIFT                                                (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_3_MASK                                                 (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_4_SHIFT                                                (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_4_MASK                                                 (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_5_SHIFT                                                (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_5_MASK                                                 (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_6_SHIFT                                                (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_6_MASK                                                 (0xffffffffU)

#define CTRL_CORE_BREG_SELECTION_SEL_DDR_SHIFT                                          (14U)
#define CTRL_CORE_BREG_SELECTION_SEL_DDR_MASK                                           (0x00004000U)
#define CTRL_CORE_BREG_SELECTION_SEL_DDR                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_DDR_NOSEL                                           (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_GMAC_SHIFT                                         (12U)
#define CTRL_CORE_BREG_SELECTION_SEL_GMAC_MASK                                          (0x00001000U)
#define CTRL_CORE_BREG_SELECTION_SEL_GMAC                                                (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_GMAC_NOSEL                                          (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_DSP_SHIFT                                          (11U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSP_MASK                                           (0x00000800U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSP                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSP_NOSEL                                           (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_PER_SHIFT                                          (5U)
#define CTRL_CORE_BREG_SELECTION_SEL_PER_MASK                                           (0x00000020U)
#define CTRL_CORE_BREG_SELECTION_SEL_PER                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_PER_NOSEL                                           (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_VIDEO1_SHIFT                                       (2U)
#define CTRL_CORE_BREG_SELECTION_SEL_VIDEO1_MASK                                        (0x00000004U)
#define CTRL_CORE_BREG_SELECTION_SEL_VIDEO1                                              (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_VIDEO1_NOSEL                                        (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_SHIFT                                              (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_MASK                                               (0x00000002U)
#define CTRL_CORE_BREG_SELECTION_SEL                                                     (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_NOSEL                                               (0U)

#define CTRL_CORE_DPLL_BCLK_BRW_SHIFT                                                   (1U)
#define CTRL_CORE_DPLL_BCLK_BRW_MASK                                                    (0x00000002U)
#define CTRL_CORE_DPLL_BCLK_BRW_SEL                                                      (1U)
#define CTRL_CORE_DPLL_BCLK_BRW_NOSEL                                                    (0U)

#define CTRL_CORE_DPLL_BCLK_SHIFT                                                       (0U)
#define CTRL_CORE_DPLL_BCLK_MASK                                                        (0x00000001U)
#define CTRL_CORE_DPLL_BCLK_SEL                                                          (1U)
#define CTRL_CORE_DPLL_BCLK_NOSEL                                                        (0U)

#define CTRL_CORE_DPLL_BADDR_BDATAW_SHIFT                                               (16U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_MASK                                                (0x000f0000U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_SEL                                                  (1U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_NOSEL                                                (0U)

/*PRASAD incompatible redefinition of macro "CTRL_CORE_DPLL_BADDR_BDATAW_SHIFT"
#define CTRL_CORE_DPLL_BADDR_BDATAW_SHIFT                                               (0U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_MASK                                                (0x0000ffffU)
#define CTRL_CORE_DPLL_BADDR_BDATAW_SEL                                                  (1U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_NOSEL                                                (0U) */

#define CTRL_CORE_DPLL_BDATAR_SHIFT                                                     (0U)
#define CTRL_CORE_DPLL_BDATAR_MASK                                                      (0x0000ffffU)
#define CTRL_CORE_DPLL_BDATAR_SEL                                                        (1U)
#define CTRL_CORE_DPLL_BDATAR_NOSEL                                                      (0U)

#define CTRL_CORE_TEMP_SENSOR_BGAP_TMPSOFF_SHIFT                                        (11U)
#define CTRL_CORE_TEMP_SENSOR_BGAP_TMPSOFF_MASK                                         (0x00000800U)

#define CTRL_CORE_TEMP_SENSOR_BGAP_EOCZ_SHIFT                                           (10U)
#define CTRL_CORE_TEMP_SENSOR_BGAP_EOCZ_MASK                                            (0x00000400U)

#define CTRL_CORE_TEMP_SENSOR_BGAP_DTEMP_SHIFT                                          (0U)
#define CTRL_CORE_TEMP_SENSOR_BGAP_DTEMP_MASK                                           (0x000003ffU)

#define CTRL_CORE_STD_FUSE_DFT_MEM_RW_SHIFT                                             (0U)
#define CTRL_CORE_STD_FUSE_DFT_MEM_RW_MASK                                              (0x0000ffffU)

#define CTRL_CORE_DUCATI_MMUADDRTRANSLTR_SHIFT                                          (0U)
#define CTRL_CORE_DUCATI_MMUADDRTRANSLTR_MASK                                           (0x000fffffU)

#define CTRL_CORE_DUCATI_MMUADDRLOGICTR_SHIFT                                           (0U)
#define CTRL_CORE_DUCATI_MMUADDRLOGICTR_MASK                                            (0x000fffffU)

#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_2_SHIFT                                      (14U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_2_MASK                                       (0x0007c000U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_2_DIV8                                        (8U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_2_DIV4                                        (4U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_2_NODIV                                       (1U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_2_DIV16                                       (16U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_2_DIV2                                        (2U)

#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_1_SHIFT                                      (9U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_1_MASK                                       (0x00003e00U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_1_DIV8                                        (8U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_1_DIV4                                        (4U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_1_NODIV                                       (1U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_1_DIV16                                       (16U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_1_DIV2                                        (2U)

#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_SHIFT                                        (3U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_MASK                                         (0x000000f8U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_DIV8                                          (8U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_DIV4                                          (4U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_NODIV                                         (1U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_DIV16                                         (16U)
#define CTRL_CORE_HWOBS_CONTROL_CLKDIV_SEL_DIV2                                          (2U)

#define CTRL_CORE_HWOBS_CONTROL_ALL_ZERO_MODE_SHIFT                                     (2U)
#define CTRL_CORE_HWOBS_CONTROL_ALL_ZERO_MODE_MASK                                      (0x00000004U)
#define CTRL_CORE_HWOBS_CONTROL_ALL_ZERO_MODE_ENABLED                                    (1U)
#define CTRL_CORE_HWOBS_CONTROL_ALL_ZERO_MODE_DISABLED                                   (0U)

#define CTRL_CORE_HWOBS_CONTROL_ALL_ONE_MODE_SHIFT                                      (1U)
#define CTRL_CORE_HWOBS_CONTROL_ALL_ONE_MODE_MASK                                       (0x00000002U)
#define CTRL_CORE_HWOBS_CONTROL_ALL_ONE_MODE_ENABLED                                     (1U)
#define CTRL_CORE_HWOBS_CONTROL_ALL_ONE_MODE_DISABLED                                    (0U)

#define CTRL_CORE_HWOBS_CONTROL_MACRO_ENABLE_SHIFT                                      (0U)
#define CTRL_CORE_HWOBS_CONTROL_MACRO_ENABLE_MASK                                       (0x00000001U)
#define CTRL_CORE_HWOBS_CONTROL_MACRO_ENABLE_ENABLED                                     (1U)
#define CTRL_CORE_HWOBS_CONTROL_MACRO_ENABLE_DISABLED                                    (0U)

#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_SHIFT                                        (30U)
#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_MASK                                         (0xc0000000U)
#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_FORCEIDLE                                     (1U)
#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_NOFUNC                                        (3U)
#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_NOIDLE                                        (0U)
#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_SMARTIDLE                                     (2U)

#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_SHIFT                                    (27U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_MASK                                     (0x38000000U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_250MS                                   (4U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_1MS                                     (1U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_100MS                                   (3U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_IMEDIAT                                 (0U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_10MS                                    (2U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_500MS                                   (5U)

#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_SHIFT                                           (23U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_MASK                                            (0x00800000U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE                                                  (1U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_NO_OP                                            (0U)

#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_SHIFT                                            (20U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_MASK                                             (0x00100000U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_RESET                                             (1U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_NO_OP                                             (0U)

#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_SHIFT                                      (17U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_MASK                                       (0x00020000U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_RESET                                       (1U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_NO_OP                                       (0U)

#define CTRL_CORE_BANDGAP_MASK_1_HOT_SHIFT                                              (5U)
#define CTRL_CORE_BANDGAP_MASK_1_HOT_MASK                                               (0x00000020U)
#define CTRL_CORE_BANDGAP_MASK_1_HOT_UNMASKED                                            (1U)
#define CTRL_CORE_BANDGAP_MASK_1_HOT_MASKED                                              (0U)

#define CTRL_CORE_BANDGAP_MASK_1_COLD_SHIFT                                             (4U)
#define CTRL_CORE_BANDGAP_MASK_1_COLD_MASK                                              (0x00000010U)
#define CTRL_CORE_BANDGAP_MASK_1_COLD_UNMASKED                                           (1U)
#define CTRL_CORE_BANDGAP_MASK_1_COLD_MASKED                                             (0U)

#define CTRL_CORE_BANDGAP_THRESHOLD_THOLD_HOT_SHIFT                                     (16U)
#define CTRL_CORE_BANDGAP_THRESHOLD_THOLD_HOT_MASK                                      (0x03ff0000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_THOLD_COLD_SHIFT                                    (0U)
#define CTRL_CORE_BANDGAP_THRESHOLD_THOLD_COLD_MASK                                     (0x000003ffU)

#define CTRL_CORE_BANDGAP_TSHUT_MUXCTRL_SHIFT                                           (31U)
#define CTRL_CORE_BANDGAP_TSHUT_MUXCTRL_MASK                                            (0x80000000U)
#define CTRL_CORE_BANDGAP_TSHUT_MUXCTRL_OCP                                              (1U)
#define CTRL_CORE_BANDGAP_TSHUT_MUXCTRL_EFUSE                                            (0U)

#define CTRL_CORE_BANDGAP_TSHUT_HOT_SHIFT                                               (16U)
#define CTRL_CORE_BANDGAP_TSHUT_HOT_MASK                                                (0x03ff0000U)

#define CTRL_CORE_BANDGAP_TSHUT_COLD_SHIFT                                              (0U)
#define CTRL_CORE_BANDGAP_TSHUT_COLD_MASK                                               (0x000003ffU)

#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_SHIFT                                             (0U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_MASK                                              (0xffffffffU)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_REPEAT                                             (1U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_SINGLE                                             (0U)

#define CTRL_CORE_BANDGAP_STATUS_1_ALERT_SHIFT                                          (31U)
#define CTRL_CORE_BANDGAP_STATUS_1_ALERT_MASK                                           (0x80000000U)

#define CTRL_CORE_BANDGAP_STATUS_1_HOT_SHIFT                                            (5U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_MASK                                             (0x00000020U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_EVENT                                             (1U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_NOEVENT                                           (0U)

#define CTRL_CORE_BANDGAP_STATUS_1_COLD_SHIFT                                           (4U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_MASK                                            (0x00000010U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_EVENT                                            (1U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_NOEVENT                                          (0U)

#define CTRL_CORE_CEK2_0_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_CEK2_0_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_CEK2_1_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_CEK2_1_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_CEK2_2_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_CEK2_2_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_CEK2_3_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_CEK2_3_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_DTEMP_0_TAG_SHIFT                                                     (10U)
#define CTRL_CORE_DTEMP_0_TAG_MASK                                                      (0xfffffc00U)

#define CTRL_CORE_DTEMP_0_TEMPERATURE_SHIFT                                             (0U)
#define CTRL_CORE_DTEMP_0_TEMPERATURE_MASK                                              (0x000003ffU)

#define CTRL_CORE_DTEMP_1_TAG_SHIFT                                                     (10U)
#define CTRL_CORE_DTEMP_1_TAG_MASK                                                      (0xfffffc00U)

#define CTRL_CORE_DTEMP_1_TEMPERATURE_SHIFT                                             (0U)
#define CTRL_CORE_DTEMP_1_TEMPERATURE_MASK                                              (0x000003ffU)

#define CTRL_CORE_DTEMP_2_TAG_SHIFT                                                     (10U)
#define CTRL_CORE_DTEMP_2_TAG_MASK                                                      (0xfffffc00U)

#define CTRL_CORE_DTEMP_2_TEMPERATURE_SHIFT                                             (0U)
#define CTRL_CORE_DTEMP_2_TEMPERATURE_MASK                                              (0x000003ffU)

#define CTRL_CORE_DTEMP_3_TAG_SHIFT                                                     (10U)
#define CTRL_CORE_DTEMP_3_TAG_MASK                                                      (0xfffffc00U)

#define CTRL_CORE_DTEMP_3_TEMPERATURE_SHIFT                                             (0U)
#define CTRL_CORE_DTEMP_3_TEMPERATURE_MASK                                              (0x000003ffU)

#define CTRL_CORE_DTEMP_4_TAG_SHIFT                                                     (10U)
#define CTRL_CORE_DTEMP_4_TAG_MASK                                                      (0xfffffc00U)

#define CTRL_CORE_DTEMP_4_TEMPERATURE_SHIFT                                             (0U)
#define CTRL_CORE_DTEMP_4_TEMPERATURE_MASK                                              (0x000003ffU)

#define CTRL_CORE_MREQDOMAIN_EXP4_LOCK_SHIFT                                            (31U)
#define CTRL_CORE_MREQDOMAIN_EXP4_LOCK_MASK                                             (0x80000000U)

#define CTRL_CORE_MREQDOMAIN_EXP4_DSP2_MDMA_SHIFT                                       (27U)
#define CTRL_CORE_MREQDOMAIN_EXP4_DSP2_MDMA_MASK                                        (0x38000000U)

#define CTRL_CORE_MREQDOMAIN_EXP4_DSP1_MDMA_SHIFT                                       (24U)
#define CTRL_CORE_MREQDOMAIN_EXP4_DSP1_MDMA_MASK                                        (0x07000000U)

#define CTRL_CORE_MREQDOMAIN_EXP4_GMACSW_SHIFT                                          (18U)
#define CTRL_CORE_MREQDOMAIN_EXP4_GMACSW_MASK                                           (0x001c0000U)

#define CTRL_CORE_MREQDOMAIN_EXP4_MMU1_SHIFT                                            (12U)
#define CTRL_CORE_MREQDOMAIN_EXP4_MMU1_MASK                                             (0x00007000U)

#define CTRL_CORE_MREQDOMAIN_EXP5_LOCK_SHIFT                                            (31U)
#define CTRL_CORE_MREQDOMAIN_EXP5_LOCK_MASK                                             (0x80000000U)

#define CTRL_CORE_MREQDOMAIN_EXP5_EVE1_TC1_SHIFT                                        (21U)
#define CTRL_CORE_MREQDOMAIN_EXP5_EVE1_TC1_MASK                                         (0x00e00000U)

#define CTRL_CORE_MREQDOMAIN_EXP5_VIP1_P2_SHIFT                                         (0U)
#define CTRL_CORE_MREQDOMAIN_EXP5_VIP1_P2_MASK                                          (0x00000007U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_CRC_SECDBG_EN_SHIFT               (19U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_CRC_SECDBG_EN_MASK                (0x00080000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_TESOC_SECDBG_EN_SHIFT             (17U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_TESOC_SECDBG_EN_MASK              (0x00020000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_MMU1_SECDBG_EN_SHIFT              (15U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_MMU1_SECDBG_EN_MASK               (0x00008000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_EMIF_LLI_SECDBG_EN_SHIFT          (14U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_EMIF_LLI_SECDBG_EN_MASK           (0x00004000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_TSC_ADC_SECDBG_EN_SHIFT           (11U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_TSC_ADC_SECDBG_EN_MASK            (0x00000800U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_EDMA_TPCC_SECDBG_EN_SHIFT         (10U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_EDMA_TPCC_SECDBG_EN_MASK          (0x00000400U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_EDMA_TC_SECDBG_EN_SHIFT           (9U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_EDMA_TC_SECDBG_EN_MASK            (0x00000200U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_QSPI_SECDBG_EN_SHIFT              (8U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_QSPI_SECDBG_EN_MASK               (0x00000100U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_DSP2_SECDBG_EN_SHIFT              (1U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_DSP2_SECDBG_EN_MASK               (0x00000002U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_DSP1_SECDBG_EN_SHIFT              (0U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_DBG_2_DSP1_SECDBG_EN_MASK               (0x00000001U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_CRC_SECLOCK_EN_SHIFT             (19U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_CRC_SECLOCK_EN_MASK              (0x00080000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_TESOC_SECLOCK_EN_SHIFT           (17U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_TESOC_SECLOCK_EN_MASK            (0x00020000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_MMU1_SECLOCK_EN_SHIFT            (15U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_MMU1_SECLOCK_EN_MASK             (0x00008000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_EMIF_LLI_SECLOCK_EN_SHIFT        (14U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_EMIF_LLI_SECLOCK_EN_MASK         (0x00004000U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_TSC_ADC_SECLOCK_EN_SHIFT         (11U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_TSC_ADC_SECLOCK_EN_MASK          (0x00000800U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_EDMA_TPCC_SECLOCK_EN_SHIFT       (10U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_EDMA_TPCC_SECLOCK_EN_MASK        (0x00000400U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_EDMA_TC_SECLOCK_EN_SHIFT         (9U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_EDMA_TC_SECLOCK_EN_MASK          (0x00000200U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_QSPI_SECLOCK_EN_SHIFT            (8U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_QSPI_SECLOCK_EN_MASK             (0x00000100U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_DSP2_SECLOCK_EN_SHIFT            (1U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_DSP2_SECLOCK_EN_MASK             (0x00000002U)

#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_DSP1_SECLOCK_EN_SHIFT            (0U)
#define CTRL_CORE_L3_HW_FW_EXPORTED_VALUES_CONF_LOCK_2_DSP1_SECLOCK_EN_MASK             (0x00000001U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TESOC_FW_ERROR_SHIFT                            (30U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TESOC_FW_ERROR_MASK                             (0x40000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TESOC_FW_ERROR_EDMA_TC1                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TESOC_FW_ERROR_NO_EDMA_TC1                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MMU1_FW_ERROR_SHIFT                             (28U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MMU1_FW_ERROR_MASK                              (0x10000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MMU1_FW_ERROR_EDMA_TC1                           (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MMU1_FW_ERROR_NO_EDMA_TC1                        (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_EMIF_LLI_FW_ERROR_SHIFT                         (27U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_EMIF_LLI_FW_ERROR_MASK                          (0x08000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_EMIF_LLI_FW_ERROR_EDMA_TC1                       (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_EMIF_LLI_FW_ERROR_NO_EDMA_TC1                    (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC1_EDMA_FW_ERROR_SHIFT                         (26U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC1_EDMA_FW_ERROR_MASK                          (0x04000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC1_EDMA_FW_ERROR                                (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC1_EDMA_FW_ERROR_NO                             (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TSC_ADC_FW_ERROR_SHIFT                          (23U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TSC_ADC_FW_ERROR_MASK                           (0x00800000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TSC_ADC_FW_ERROR_SPARE                           (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TSC_ADC_FW_ERROR_NO_SPARE                        (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_QSPI_FW_ERROR_SHIFT                             (22U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_QSPI_FW_ERROR_MASK                              (0x00400000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_QSPI_FW_ERROR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_QSPI_FW_ERROR_NO                                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TPCC_EDMA_FW_ERROR_SHIFT                        (17U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TPCC_EDMA_FW_ERROR_MASK                         (0x00020000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TPCC_EDMA_FW_ERROR                               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TPCC_EDMA_FW_ERROR_NO                            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC0_EDMA_FW_ERROR_SHIFT                         (16U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC0_EDMA_FW_ERROR_MASK                          (0x00010000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC0_EDMA_FW_ERROR                                (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC0_EDMA_FW_ERROR_NO                             (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP1_FW_ERROR_SHIFT                           (11U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP1_FW_ERROR_MASK                            (0x00000800U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP1_FW_ERROR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP1_FW_ERROR_NO                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_SHIFT                       (5U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_MASK                        (0x00000020U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_L4PERIPH3_INIT               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_NO_L4PERIPH3_INIT            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_SHIFT                       (4U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_MASK                        (0x00000010U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_L4PERIPH2_INIT               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_NO_L4PERIPH2_INIT            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP2_FW_ERROR_SHIFT                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP2_FW_ERROR_MASK                              (0x00000002U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP2_FW_ERROR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP2_FW_ERROR_NO                                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR_SHIFT                             (0U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR_MASK                              (0x00000001U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR_NO                                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TESOC_FW_ERROR_SHIFT               (30U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TESOC_FW_ERROR_MASK                (0x40000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TESOC_FW_ERROR_UNMASKED             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TESOC_FW_ERROR_MASKED               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_MMU1_FW_ERROR_SHIFT                (28U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_MMU1_FW_ERROR_MASK                 (0x10000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_MMU1_FW_ERROR_UNMASKED              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_MMU1_FW_ERROR_MASKED                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_EMIF_LLI_FW_ERROR_SHIFT            (27U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_EMIF_LLI_FW_ERROR_MASK             (0x08000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_EMIF_LLI_FW_ERROR_UNMASKED          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_EMIF_LLI_FW_ERROR_MASKED            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TC1_EDMA_FW_ERROR_SHIFT            (26U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TC1_EDMA_FW_ERROR_MASK             (0x04000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TC1_EDMA_FW_ERROR_UNMASKED          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TC1_EDMA_FW_ERROR_MASKED            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TSC_ADC_FW_ERROR_SHIFT             (23U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TSC_ADC_FW_ERROR_MASK              (0x00800000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TSC_ADC_FW_ERROR_UNMASKED           (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TSC_ADC_FW_ERROR_MASKED             (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_QSPI_FW_ERROR_SHIFT                (22U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_QSPI_FW_ERROR_MASK                 (0x00400000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_QSPI_FW_ERROR_UNMASKED              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_QSPI_FW_ERROR_MASKED                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TPCC_EDMA_FW_ERROR_SHIFT           (17U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TPCC_EDMA_FW_ERROR_MASK            (0x00020000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TPCC_EDMA_FW_ERROR_UNMASKED         (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TPCC_EDMA_FW_ERROR_MASKED           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TC0_EDMA_FW_ERROR_SHIFT            (16U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TC0_EDMA_FW_ERROR_MASK             (0x00010000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TC0_EDMA_FW_ERROR_UNMASKED          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_TC0_EDMA_FW_ERROR_MASKED            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_MCASP1_FW_ERROR_SHIFT              (11U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_MCASP1_FW_ERROR_MASK               (0x00000800U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_MCASP1_FW_ERROR_UNMASKED            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_MCASP1_FW_ERROR_MASKED              (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_L4_PERIPH3_FW_ERROR_SHIFT          (5U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_L4_PERIPH3_FW_ERROR_MASK           (0x00000020U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_L4_PERIPH3_FW_ERROR_UNMASKED        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_L4_PERIPH3_FW_ERROR_MASKED          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_L4_PERIPH2_FW_ERROR_SHIFT          (4U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_L4_PERIPH2_FW_ERROR_MASK           (0x00000010U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_L4_PERIPH2_FW_ERROR_UNMASKED        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_L4_PERIPH2_FW_ERROR_MASKED          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_DSP2_FW_ERROR_SHIFT                (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_DSP2_FW_ERROR_MASK                 (0x00000002U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_DSP2_FW_ERROR_UNMASKED              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_DSP2_FW_ERROR_MASKED                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_DSP1_FW_ERROR_SHIFT                (0U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_DSP1_FW_ERROR_MASK                 (0x00000001U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_DSP1_FW_ERROR_UNMASKED              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_2_DSP1_FW_ERROR_MASKED                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TESOC_DBGFW_ERROR_SHIFT                        (30U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TESOC_DBGFW_ERROR_MASK                         (0x40000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TESOC_DBGFW_ERROR_EDMA_TC1_FW                   (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TESOC_DBGFW_ERROR_NO_EDMA_TC1_FW                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MMU1_DBGFW_ERROR_SHIFT                         (28U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MMU1_DBGFW_ERROR_MASK                          (0x10000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MMU1_DBGFW_ERROR_EDMA_TC1_FW                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MMU1_DBGFW_ERROR_NO_EDMA_TC1_FW                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_EMIF_LLI_DBGFW_ERROR_SHIFT                     (27U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_EMIF_LLI_DBGFW_ERROR_MASK                      (0x08000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_EMIF_LLI_DBGFW_ERROR_EDMA_TC1_FW                (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_EMIF_LLI_DBGFW_ERROR_NO_EDMA_TC1_FW             (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC1_EDMA_DBGFW_ERROR_SHIFT                     (26U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC1_EDMA_DBGFW_ERROR_MASK                      (0x04000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC1_EDMA_DBGFW_ERROR_FW                         (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC1_EDMA_DBGFW_ERROR_NO_FW                      (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TSC_ADC_DBGFW_ERROR_SHIFT                      (23U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TSC_ADC_DBGFW_ERROR_MASK                       (0x00800000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TSC_ADC_DBGFW_ERROR_SPARE_FW                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TSC_ADC_DBGFW_ERROR_NO_SPARE_FW                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_QSPI_DBGFW_ERROR_SHIFT                         (22U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_QSPI_DBGFW_ERROR_MASK                          (0x00400000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_QSPI_DBGFW_ERROR_FW                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_QSPI_DBGFW_ERROR_NO_FW                          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TPCC_EDMA_DBGFW_ERROR_SHIFT                    (17U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TPCC_EDMA_DBGFW_ERROR_MASK                     (0x00020000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TPCC_EDMA_DBGFW_ERROR_FW                        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TPCC_EDMA_DBGFW_ERROR_NO_FW                     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC0_EDMA_DBGFW_ERROR_SHIFT                     (16U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC0_EDMA_DBGFW_ERROR_MASK                      (0x00010000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC0_EDMA_DBGFW_ERROR_FW                         (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC0_EDMA_DBGFW_ERROR_NO_FW                      (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP1_DBGFW_ERROR_SHIFT                       (11U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP1_DBGFW_ERROR_MASK                        (0x00000800U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP1_DBGFW_ERROR_FW                           (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP1_DBGFW_ERROR_NO_FW                        (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH3_DBGFW_ERROR_SHIFT                   (5U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH3_DBGFW_ERROR_MASK                    (0x00000020U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH3_DBGFW_ERROR_L4PERIPH3_INIT_FW        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH3_DBGFW_ERROR_NO_L4PERIPH3_INIT_FW     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH2_DBGFW_ERROR_SHIFT                   (4U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH2_DBGFW_ERROR_MASK                    (0x00000010U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH2_DBGFW_ERROR_L4PERIPH2_INIT_FW        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH2_DBGFW_ERROR_NO_L4PERIPH2_INIT_FW     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP2_DBGFW_ERROR_SHIFT                         (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP2_DBGFW_ERROR_MASK                          (0x00000002U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP2_DBGFW_ERROR_FW                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP2_DBGFW_ERROR_NO_FW                          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP1_DBGFW_ERROR_SHIFT                         (0U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP1_DBGFW_ERROR_MASK                          (0x00000001U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP1_DBGFW_ERROR_FW                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP1_DBGFW_ERROR_NO_FW                          (0U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_CS_DAP_SHIFT                                (24U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_CS_DAP_MASK                                 (0x07000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_CS_DAP_HIGHESTPRIORITY                       (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_CS_DAP_LOWESTPRIORITY                        (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_IEEE1500_2_OCP_SHIFT                        (20U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_IEEE1500_2_OCP_MASK                         (0x00700000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_IEEE1500_2_OCP_HIGHESTPRIORITY               (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_IEEE1500_2_OCP_LOWESTPRIORITY                (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_MDMA_SHIFT                             (16U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_MDMA_MASK                              (0x00070000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_MDMA_HIGHESTPRIORITY                    (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_MDMA_LOWESTPRIORITY                     (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_CFG_SHIFT                              (12U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_CFG_MASK                               (0x00007000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_CFG_HIGHESTPRIORITY                     (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_CFG_LOWESTPRIORITY                      (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_EDMA_SHIFT                             (8U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_EDMA_MASK                              (0x00000700U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_EDMA_HIGHESTPRIORITY                    (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_EDMA_LOWESTPRIORITY                     (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_EDMA_SHIFT                             (4U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_EDMA_MASK                              (0x00000070U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_EDMA_HIGHESTPRIORITY                    (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_EDMA_LOWESTPRIORITY                     (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_CFG_SHIFT                              (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_CFG_MASK                               (0x00000007U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_CFG_HIGHESTPRIORITY                     (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_CFG_LOWESTPRIORITY                      (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_DSP2_MDMA_SHIFT                             (28U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_DSP2_MDMA_MASK                              (0x70000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_DSP2_MDMA_HIGHESTPRIORITY                    (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_DSP2_MDMA_LOWESTPRIORITY                     (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE1_TC0_SHIFT                              (16U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE1_TC0_MASK                               (0x00070000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE1_TC0_HIGHESTPRIORITY                     (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE1_TC0_LOWESTPRIORITY                      (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU1_SHIFT                                  (16U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU1_MASK                                   (0x00070000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU1_HIGHESTPRIORITY                         (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU1_LOWESTPRIORITY                          (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_EDMA_TC0_SHIFT                              (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_EDMA_TC0_MASK                               (0x00000007U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_EDMA_TC0_HIGHESTPRIORITY                     (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_EDMA_TC0_LOWESTPRIORITY                      (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_EDMA_TC1_SHIFT                              (28U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_EDMA_TC1_MASK                               (0x70000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_EDMA_TC1_HIGHESTPRIORITY                     (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_EDMA_TC1_LOWESTPRIORITY                      (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_DSS_SHIFT                                   (24U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_DSS_MASK                                    (0x07000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_DSS_HIGHESTPRIORITY                          (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_DSS_LOWESTPRIORITY                           (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_MMU1_SHIFT                                  (20U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_MMU1_MASK                                   (0x00700000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_MMU1_HIGHESTPRIORITY                         (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_MMU1_LOWESTPRIORITY                          (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP1_P1_P2_SHIFT                            (8U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP1_P1_P2_MASK                             (0x00000700U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP1_P1_P2_HIGHESTPRIORITY                   (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP1_P1_P2_LOWESTPRIORITY                    (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_GMAC_SW_SHIFT                               (12U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_GMAC_SW_MASK                                (0x00007000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_GMAC_SW_HIGHESTPRIORITY                      (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_GMAC_SW_LOWESTPRIORITY                       (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE1_TC1_SHIFT                              (8U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE1_TC1_MASK                               (0x00000700U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE1_TC1_HIGHESTPRIORITY                     (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE1_TC1_LOWESTPRIORITY                      (7U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP1_CFG_SHIFT                                (17U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP1_CFG_MASK                                 (0x00060000U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP1_CFG_LOWEST                                (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP1_CFG_HIGHEST                               (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP2_CFG_SHIFT                                (9U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP2_CFG_MASK                                 (0x00000600U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP2_CFG_LOWEST                                (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP2_CFG_HIGHEST                               (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_CS_DAP_SHIFT                                  (3U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_CS_DAP_MASK                                   (0x00000018U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_CS_DAP_LOWEST                                  (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_CS_DAP_HIGHEST                                 (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_IEEE1500_2_OCP_SHIFT                          (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_IEEE1500_2_OCP_MASK                           (0x00000003U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_IEEE1500_2_OCP_LOWEST                          (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_IEEE1500_2_OCP_HIGHEST                         (3U)

#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_LDOVBBDSPEVE_FBB_MUX_SHIFT                      (10U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_LDOVBBDSPEVE_FBB_MUX_MASK                       (0x00000400U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_LDOVBBDSPEVE_FBB_MUX_OCP                         (1U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_LDOVBBDSPEVE_FBB_MUX_EFUSE                       (0U)

#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_LDOVBBDSPEVE_FBB_VSET_IN_SHIFT                  (5U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_LDOVBBDSPEVE_FBB_VSET_IN_MASK                   (0x000003e0U)

#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_LDOVBBDSPEVE_FBB_VSET_OUT_SHIFT                 (0U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_LDOVBBDSPEVE_FBB_VSET_OUT_MASK                  (0x0000001fU)

#define CTRL_CORE_CUST_FUSE_UID_0_SHIFT                                                 (0U)
#define CTRL_CORE_CUST_FUSE_UID_0_MASK                                                  (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_UID_1_SHIFT                                                 (0U)
#define CTRL_CORE_CUST_FUSE_UID_1_MASK                                                  (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_UID_2_SHIFT                                                 (0U)
#define CTRL_CORE_CUST_FUSE_UID_2_MASK                                                  (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_UID_3_SHIFT                                                 (0U)
#define CTRL_CORE_CUST_FUSE_UID_3_MASK                                                  (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_UID_4_SHIFT                                                 (0U)
#define CTRL_CORE_CUST_FUSE_UID_4_MASK                                                  (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_UID_5_SHIFT                                                 (0U)
#define CTRL_CORE_CUST_FUSE_UID_5_MASK                                                  (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_UID_6_SHIFT                                                 (0U)
#define CTRL_CORE_CUST_FUSE_UID_6_MASK                                                  (0xffffffffU)

#define CTRL_CORE_MAC_ID_SW_0_STD_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_MAC_ID_SW_0_STD_FUSE_MASK                                             (0x01ffffffU)

#define CTRL_CORE_MAC_ID_SW_1_STD_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_MAC_ID_SW_1_STD_FUSE_MASK                                             (0x01ffffffU)

#define CTRL_CORE_MAC_ID_SW_2_STD_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_MAC_ID_SW_2_STD_FUSE_MASK                                             (0x01ffffffU)

#define CTRL_CORE_MAC_ID_SW_3_STD_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_MAC_ID_SW_3_STD_FUSE_MASK                                             (0x01ffffffU)

#define CTRL_CORE_SW_ID_0_STD_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_SW_ID_0_STD_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SW_ID_1_STD_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_SW_ID_1_STD_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_EFUSE_DISABLE_SW_0_DSS_VIDEO_CLK_SHIFT                                (15U)
#define CTRL_CORE_EFUSE_DISABLE_SW_0_DSS_VIDEO_CLK_MASK                                 (0x00008000U)

#define CTRL_CORE_EFUSE_DISABLE_SW_0_OCMC_RAM1_SHIFT                                    (9U)
#define CTRL_CORE_EFUSE_DISABLE_SW_0_OCMC_RAM1_MASK                                     (0x00000200U)

#define CTRL_CORE_EFUSE_DISABLE_SW_0_IPU1_BOOT_ENABLE_SHIFT                             (8U)
#define CTRL_CORE_EFUSE_DISABLE_SW_0_IPU1_BOOT_ENABLE_MASK                              (0x00000100U)

#define CTRL_CORE_EFUSE_DISABLE_SW_0_EVE1_SHIFT                                         (2U)
#define CTRL_CORE_EFUSE_DISABLE_SW_0_EVE1_MASK                                          (0x00000004U)

#define CTRL_CORE_EFUSE_DISABLE_SW_0_DSP2_SHIFT                                         (1U)
#define CTRL_CORE_EFUSE_DISABLE_SW_0_DSP2_MASK                                          (0x00000002U)

#define CTRL_CORE_EFUSE_DISABLE_SW_0_DSP1_SHIFT                                         (0U)
#define CTRL_CORE_EFUSE_DISABLE_SW_0_DSP1_MASK                                          (0x00000001U)

#define CTRL_CORE_SLEW_SW_0_STD_FUSE_SHIFT                                              (0U)
#define CTRL_CORE_SLEW_SW_0_STD_FUSE_MASK                                               (0xffffffffU)

#define CTRL_CORE_SMA_SW_1_DSS_CH0_IPC_SHIFT                                            (22U)
#define CTRL_CORE_SMA_SW_1_DSS_CH0_IPC_MASK                                             (0x00400000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH0_ON_OFF_SHIFT                                         (19U)
#define CTRL_CORE_SMA_SW_1_DSS_CH0_ON_OFF_MASK                                          (0x00080000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH0_RF_SHIFT                                             (16U)
#define CTRL_CORE_SMA_SW_1_DSS_CH0_RF_MASK                                              (0x00010000U)

#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2B_SHIFT                                   (3U)
#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2B_MASK                                    (0x00000008U)

#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1B_SHIFT                                   (2U)
#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1B_MASK                                    (0x00000004U)

#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2A_SHIFT                                   (1U)
#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2A_MASK                                    (0x00000002U)

#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1A_SHIFT                                   (0U)
#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1A_MASK                                    (0x00000001U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_8_ISS_SHIFT                                   (8U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_8_ISS_MASK                                    (0x00000700U)

#define CTRL_CORE_MMR_LOCK_1_SHIFT                                                      (0U)
#define CTRL_CORE_MMR_LOCK_1_MASK                                                       (0xffffffffU)
#define CTRL_CORE_MMR_LOCK_1_TOLOCK                                                      (438075716U)
#define CTRL_CORE_MMR_LOCK_1_TOUNLOCK                                                    (804367403U)

#define CTRL_CORE_MMR_LOCK_2_SHIFT                                                      (0U)
#define CTRL_CORE_MMR_LOCK_2_MASK                                                       (0xffffffffU)
#define CTRL_CORE_MMR_LOCK_2_TOLOCK                                                      (4260648240U)
#define CTRL_CORE_MMR_LOCK_2_TOUNLOCK                                                    (4149738944U)

#define CTRL_CORE_MMR_LOCK_3_SHIFT                                                      (0U)
#define CTRL_CORE_MMR_LOCK_3_MASK                                                       (0xffffffffU)
#define CTRL_CORE_MMR_LOCK_3_TOLOCK                                                      (451339040U)
#define CTRL_CORE_MMR_LOCK_3_TOUNLOCK                                                    (3803986541U)

#define CTRL_CORE_MMR_LOCK_4_SHIFT                                                      (0U)
#define CTRL_CORE_MMR_LOCK_4_MASK                                                       (0xffffffffU)
#define CTRL_CORE_MMR_LOCK_4_TOUNLOCK                                                    (515838749U)
#define CTRL_CORE_MMR_LOCK_4_TOLOCK                                                      (804950652U)

#define CTRL_CORE_MMR_LOCK_5_SHIFT                                                      (0U)
#define CTRL_CORE_MMR_LOCK_5_MASK                                                       (0xffffffffU)
#define CTRL_CORE_MMR_LOCK_5_TOLOCK                                                      (339706668U)
#define CTRL_CORE_MMR_LOCK_5_TOUNLOCK                                                    (1865817605U)

#define CTRL_CORE_CONTROL_IO_1_MMU1_DISABLE_SHIFT                                       (16U)
#define CTRL_CORE_CONTROL_IO_1_MMU1_DISABLE_MASK                                        (0x00010000U)

#define CTRL_CORE_CONTROL_IO_1_TC1_DEFAULT_BURST_SIZE_SHIFT                             (12U)
#define CTRL_CORE_CONTROL_IO_1_TC1_DEFAULT_BURST_SIZE_MASK                              (0x00003000U)

#define CTRL_CORE_CONTROL_IO_1_TC0_DEFAULT_BURST_SIZE_SHIFT                             (8U)
#define CTRL_CORE_CONTROL_IO_1_TC0_DEFAULT_BURST_SIZE_MASK                              (0x00000300U)

#define CTRL_CORE_CONTROL_IO_1_GMII2_SEL_SHIFT                                          (4U)
#define CTRL_CORE_CONTROL_IO_1_GMII2_SEL_MASK                                           (0x00000030U)

#define CTRL_CORE_CONTROL_IO_1_GMII1_SEL_SHIFT                                          (0U)
#define CTRL_CORE_CONTROL_IO_1_GMII1_SEL_MASK                                           (0x00000003U)

#define CTRL_CORE_CONTROL_IO_2_RTI_RESET_SELECTION_TO_PRCM_SHIFT                        (24U)
#define CTRL_CORE_CONTROL_IO_2_RTI_RESET_SELECTION_TO_PRCM_MASK                         (0x07000000U)
#define CTRL_CORE_CONTROL_IO_2_RTI_RESET_SELECTION_TO_PRCM_RTI5                          (4U)
#define CTRL_CORE_CONTROL_IO_2_RTI_RESET_SELECTION_TO_PRCM_RTI2                          (1U)
#define CTRL_CORE_CONTROL_IO_2_RTI_RESET_SELECTION_TO_PRCM_RTI4                          (3U)
#define CTRL_CORE_CONTROL_IO_2_RTI_RESET_SELECTION_TO_PRCM_RT1                           (0U)
#define CTRL_CORE_CONTROL_IO_2_RTI_RESET_SELECTION_TO_PRCM_RTI3                          (2U)

#define CTRL_CORE_CONTROL_IO_2_GMAC_RESET_ISOLATION_ENABLE_SHIFT                        (23U)
#define CTRL_CORE_CONTROL_IO_2_GMAC_RESET_ISOLATION_ENABLE_MASK                         (0x00800000U)
#define CTRL_CORE_CONTROL_IO_2_GMAC_RESET_ISOLATION_ENABLE_RESETISOLATED                 (1U)
#define CTRL_CORE_CONTROL_IO_2_GMAC_RESET_ISOLATION_ENABLE_NOTRESETISOLATED              (0U)

#define CTRL_CORE_CONTROL_IO_2_PWMSS1_TBCLKEN_SHIFT                                     (20U)
#define CTRL_CORE_CONTROL_IO_2_PWMSS1_TBCLKEN_MASK                                      (0x00100000U)

#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN2_INPUT_SELECTION_SHIFT                          (15U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN2_INPUT_SELECTION_MASK                           (0x00008000U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN2_INPUT_SELECTION_FROMLVDSRXPORT2                 (1U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN2_INPUT_SELECTION_FROMPINS                        (0U)

#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN1_INPUT_SELECTION_SHIFT                          (14U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN1_INPUT_SELECTION_MASK                           (0x00004000U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN1_INPUT_SELECTION_FROMLVDSRXPORT1                 (1U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN1_INPUT_SELECTION_FROMPINS                        (0U)

#define CTRL_CORE_CONTROL_IO_2_QSPI_MEMMAPPED_CS_SHIFT                                  (8U)
#define CTRL_CORE_CONTROL_IO_2_QSPI_MEMMAPPED_CS_MASK                                   (0x00000700U)

#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SHIFT                                (5U)
#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_MASK                                 (0x00000020U)
#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_CAUSESTHEINITIALIZATIONPULSETOHAPPENANDNONEEDFORSWTOWRITE0   (1U)

#define CTRL_CORE_CONTROL_IO_2_DSS_DESHDCP_DISABLE_SHIFT                                (4U)
#define CTRL_CORE_CONTROL_IO_2_DSS_DESHDCP_DISABLE_MASK                                 (0x00000010U)

#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SHIFT                                (3U)
#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_MASK                                 (0x00000008U)
#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_CAUSESTHEINITIALIZATIONPULSETOHAPPENANDNONEEDFORSWTOWRITE0 (1U)

#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_SHIFT                                 (2U)
#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_MASK                                  (0x00000004U)

#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_SHIFT                                 (1U)
#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_MASK                                  (0x00000002U)

#define CTRL_CORE_CONTROL_IO_2_DSS_DESHDCP_CLKEN_SHIFT                                  (0U)
#define CTRL_CORE_CONTROL_IO_2_DSS_DESHDCP_CLKEN_MASK                                   (0x00000001U)

#define CTRL_CORE_CONTROL_DSP1_RST_VECT_NUM_MM_SHIFT                                    (24U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT_NUM_MM_MASK                                     (0x07000000U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT_NUM_MM_TWODSPS                                   (2U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT_NUM_MM_ONEDSP                                    (1U)

#define CTRL_CORE_CONTROL_DSP1_RST_VECT_SHIFT                                           (0U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT_MASK                                            (0x003fffffU)

#define CTRL_CORE_CONTROL_DSP2_RST_VECT_NUM_MM_SHIFT                                    (24U)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT_NUM_MM_MASK                                     (0x07000000U)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT_NUM_MM_TWODSPS                                   (2U)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT_NUM_MM_ONEDSP                                    (1U)

#define CTRL_CORE_CONTROL_DSP2_RST_VECT_SHIFT                                           (0U)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT_MASK                                            (0x003fffffU)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_RETMODE_MUX_SHIFT                (26U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_RETMODE_MUX_MASK                 (0x04000000U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_RETMODE_MUX_OCP                   (1U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_RETMODE_MUX_EFUSE                 (0U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_RETMODE_VSET_IN_SHIFT            (21U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_RETMODE_VSET_IN_MASK             (0x03e00000U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_RETMODE_VSET_OUT_SHIFT           (16U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_RETMODE_VSET_OUT_MASK            (0x001f0000U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_ACTMODE_MUX_SHIFT                (10U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_ACTMODE_MUX_MASK                 (0x00000400U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_ACTMODE_MUX_OCP                   (1U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_ACTMODE_MUX_EFUSE                 (0U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_ACTMODE_VSET_IN_SHIFT            (5U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_ACTMODE_VSET_IN_MASK             (0x000003e0U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_ACTMODE_VSET_OUT_SHIFT           (0U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_LDOSRAMDSPEVE_ACTMODE_VSET_OUT_MASK            (0x0000001fU)

#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_TMPSOFF_SHIFT                                 (11U)
#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_TMPSOFF_MASK                                  (0x00000800U)

#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_EOCZ_SHIFT                                    (10U)
#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_EOCZ_MASK                                     (0x00000400U)

#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_DTEMP_SHIFT                                   (0U)
#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_DTEMP_MASK                                    (0x000003ffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_0_SHIFT                                      (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_0_MASK                                       (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_1_SHIFT                                      (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_1_MASK                                       (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_2_SHIFT                                      (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_2_MASK                                       (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_3_SHIFT                                      (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_3_MASK                                       (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_4_SHIFT                                      (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_4_MASK                                       (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_0_SHIFT                                             (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_0_MASK                                              (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_1_SHIFT                                             (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_1_MASK                                              (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_2_SHIFT                                             (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_2_MASK                                              (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_3_SHIFT                                             (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_3_MASK                                              (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_4_SHIFT                                             (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_4_MASK                                              (0xffffffffU)

#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_RETMODE_MUX_SHIFT                       (26U)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_RETMODE_MUX_MASK                        (0x04000000U)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_RETMODE_MUX_OCP                          (1U)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_RETMODE_MUX_EFUSE                        (0U)

#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_RETMODE_VSET_IN_SHIFT                   (21U)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_RETMODE_VSET_IN_MASK                    (0x03e00000U)

#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_RETMODE_VSET_OUT_SHIFT                  (16U)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_RETMODE_VSET_OUT_MASK                   (0x001f0000U)

#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_ACTMODE_MUX_SHIFT                       (10U)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_ACTMODE_MUX_MASK                        (0x00000400U)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_ACTMODE_MUX_OCP                          (1U)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_ACTMODE_MUX_EFUSE                        (0U)

#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_ACTMODE_VSET_IN_SHIFT                   (5U)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_ACTMODE_VSET_IN_MASK                    (0x000003e0U)

#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_ACTMODE_VSET_OUT_SHIFT                  (0U)
#define CTRL_CORE_LDOSRAM_2_VOLTAGE_LDOSRAMCORE_ACTMODE_VSET_OUT_MASK                   (0x0000001fU)

#define CTRL_CORE_EFUSE_DISABLE_SW_1_STD_FUSE_SHIFT                                     (0U)
#define CTRL_CORE_EFUSE_DISABLE_SW_1_STD_FUSE_MASK                                      (0xffffffffU)

#define CTRL_CORE_NMI_DESTINATION_1_IPU1_C1_SHIFT                                       (0U)
#define CTRL_CORE_NMI_DESTINATION_1_IPU1_C1_MASK                                        (0x000000ffU)
#define CTRL_CORE_NMI_DESTINATION_1_IPU1_C1_ENABLE                                       (1U)
#define CTRL_CORE_NMI_DESTINATION_1_IPU1_C1_DISABLE                                      (0U)

#define CTRL_CORE_NMI_DESTINATION_2_IPU1_C0_SHIFT                                       (24U)
#define CTRL_CORE_NMI_DESTINATION_2_IPU1_C0_MASK                                        (0xff000000U)
#define CTRL_CORE_NMI_DESTINATION_2_IPU1_C0_ENABLE                                       (1U)
#define CTRL_CORE_NMI_DESTINATION_2_IPU1_C0_DISABLE                                      (0U)

#define CTRL_CORE_NMI_DESTINATION_2_DSP2_SHIFT                                          (16U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP2_MASK                                           (0x00ff0000U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP2_ENABLE                                          (1U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP2_DISABLE                                         (0U)

#define CTRL_CORE_NMI_DESTINATION_2_DSP1_SHIFT                                          (8U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP1_MASK                                           (0x0000ff00U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP1_ENABLE                                          (1U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP1_DISABLE                                         (0U)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_0_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_0_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_1_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_1_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_2_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_2_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_3_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_3_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_4_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_4_MASK                                        (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_7_SHIFT                                                (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_7_MASK                                                 (0xffffffffU)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_15_DSP_CLOCK_DIVIDER_SHIFT                          (15U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_15_DSP_CLOCK_DIVIDER_MASK                           (0x00008000U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_13_BOOTDEVICESIZE_SHIFT                             (13U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_13_BOOTDEVICESIZE_MASK                              (0x00002000U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_12_MUXCS0DEVICE_SHIFT                               (12U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_12_MUXCS0DEVICE_MASK                                (0x00001000U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_11_MUXCS0DEVICE_SHIFT                               (11U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_11_MUXCS0DEVICE_MASK                                (0x00000800U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_10_BOOTWAITEN_SHIFT                                 (10U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_10_BOOTWAITEN_MASK                                  (0x00000400U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_9_SYSCLK_SPEED_SELECT_SHIFT                         (9U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_9_SYSCLK_SPEED_SELECT_MASK                          (0x00000200U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_8_SYSCLK_SPEED_SELECT_SHIFT                         (8U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_8_SYSCLK_SPEED_SELECT_MASK                          (0x00000100U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_7_SHIFT                                             (7U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_7_MASK                                              (0x00000080U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_6_HWOBS_IO_SELECTION_SHIFT                          (6U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_6_HWOBS_IO_SELECTION_MASK                           (0x00000040U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_5_ADC_CLOCK_DIVIDER_SHIFT                           (5U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_5_ADC_CLOCK_DIVIDER_MASK                            (0x00000020U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_4_BOOTMODE_SHIFT                                    (4U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_4_BOOTMODE_MASK                                     (0x00000010U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_3_BOOTMODE_SHIFT                                    (3U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_3_BOOTMODE_MASK                                     (0x00000008U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_2_BOOTMODE_SHIFT                                    (2U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_2_BOOTMODE_MASK                                     (0x00000004U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_1_BOOTMODE_SHIFT                                    (1U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_1_BOOTMODE_MASK                                     (0x00000002U)

#define CTRL_CORE_BOOTSTRAP_SYSBOOT_0_BOOTMODE_SHIFT                                    (0U)
#define CTRL_CORE_BOOTSTRAP_SYSBOOT_0_BOOTMODE_MASK                                     (0x00000001U)

#define CTRL_CORE_MEK_BCH_0_CUST_FUSE_SHIFT                                             (0U)
#define CTRL_CORE_MEK_BCH_0_CUST_FUSE_MASK                                              (0xffffffffU)

#define CTRL_CORE_MEK_BCH_1_CUST_FUSE_SHIFT                                             (0U)
#define CTRL_CORE_MEK_BCH_1_CUST_FUSE_MASK                                              (0xffffffffU)

#define CTRL_CORE_MEK_BCH_2_CUST_FUSE_SHIFT                                             (0U)
#define CTRL_CORE_MEK_BCH_2_CUST_FUSE_MASK                                              (0xffffffffU)

#define CTRL_CORE_MEK_BCH_3_CUST_FUSE_SHIFT                                             (0U)
#define CTRL_CORE_MEK_BCH_3_CUST_FUSE_MASK                                              (0xffffffffU)

#define CTRL_CORE_MEK_BCH_4_CUST_FUSE_SHIFT                                             (0U)
#define CTRL_CORE_MEK_BCH_4_CUST_FUSE_MASK                                              (0xffffffffU)

#define CTRL_CORE_MEK_BCH_5_CUST_FUSE_SHIFT                                             (0U)
#define CTRL_CORE_MEK_BCH_5_CUST_FUSE_MASK                                              (0xffffffffU)

#define CTRL_CORE_MEK_BCH_6_CUST_FUSE_SHIFT                                             (0U)
#define CTRL_CORE_MEK_BCH_6_CUST_FUSE_MASK                                              (0xffffffffU)

#define CTRL_CORE_MEK_BCH_7_CUST_FUSE_SHIFT                                             (0U)
#define CTRL_CORE_MEK_BCH_7_CUST_FUSE_MASK                                              (0xffffffffU)

#define CTRL_CORE_MEK_BCH_8_CUST_FUSE_SHIFT                                             (0U)
#define CTRL_CORE_MEK_BCH_8_CUST_FUSE_MASK                                              (0xffffffffU)

#define CTRL_CORE_MEK_0_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_MEK_0_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_MEK_1_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_MEK_1_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_MEK_2_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_MEK_2_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_MEK_3_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_MEK_3_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_MEK_4_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_MEK_4_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_MEK_5_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_MEK_5_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_MEK_6_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_MEK_6_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_MEK_7_CUST_FUSE_SHIFT                                                 (0U)
#define CTRL_CORE_MEK_7_CUST_FUSE_MASK                                                  (0xffffffffU)

#define CTRL_CORE_SMPK_BCH_0_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SMPK_BCH_0_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_SMPK_BCH_1_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SMPK_BCH_1_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_SMPK_BCH_2_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SMPK_BCH_2_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_SMPK_BCH_3_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SMPK_BCH_3_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_SMPK_BCH_4_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SMPK_BCH_4_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_SMPK_BCH_5_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SMPK_BCH_5_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_SMPK_BCH_6_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SMPK_BCH_6_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_SMPK_BCH_7_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SMPK_BCH_7_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_SMPK_BCH_8_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SMPK_BCH_8_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_SMPK_0_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_SMPK_0_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SMPK_1_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_SMPK_1_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SMPK_2_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_SMPK_2_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SMPK_3_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_SMPK_3_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SMPK_4_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_SMPK_4_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SMPK_5_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_SMPK_5_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SMPK_6_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_SMPK_6_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SMPK_7_CUST_FUSE_SHIFT                                                (0U)
#define CTRL_CORE_SMPK_7_CUST_FUSE_MASK                                                 (0xffffffffU)

#define CTRL_CORE_SEC_SWRV_0_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SEC_SWRV_0_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_SEC_SWRV_1_CUST_FUSE_SHIFT                                            (0U)
#define CTRL_CORE_SEC_SWRV_1_CUST_FUSE_MASK                                             (0xffffffffU)

#define CTRL_CORE_MREQDOMAIN_EXP6_LOCK_SHIFT                                            (31U)
#define CTRL_CORE_MREQDOMAIN_EXP6_LOCK_MASK                                             (0x80000000U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_3_CRC_FW_ERROR_SHIFT                              (0U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_3_CRC_FW_ERROR_MASK                               (0x00000001U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_3_CRC_FW_ERROR_EDMA_TC1                            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_3_CRC_FW_ERROR_NO_EDMA_TC1                         (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_3_CRC_FW_ERROR_SHIFT                 (0U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_3_CRC_FW_ERROR_MASK                  (0x00000001U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_3_CRC_FW_ERROR_EDMA_TC1               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_MASK_DISABLE_3_CRC_FW_ERROR_NO_EDMA_TC1            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_3_CRC_DBGFW_ERROR_SHIFT                          (0U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_3_CRC_DBGFW_ERROR_MASK                           (0x00000001U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_3_CRC_DBGFW_ERROR_EDMA_TC1_FW                     (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_3_CRC_DBGFW_ERROR_NO_EDMA_TC1_FW                  (0U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CTRL_CORE_H_ */

