/*
 *  Copyright (C) 2008-2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   hw_ctrl_core.h
 *
 *  \brief  register-level header file for CTRL_CORE
 *
**/

#ifndef HW_CTRL_CORE_H_
#define HW_CTRL_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define CTRL_CORE_STATUS                                                                                    (0x34U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1                                                                     (0x48U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1                                                                    (0x50U)
#define CTRL_CORE_MPU_FORCEWRNP                                                                             (0x5cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_0                                                                    (0x94U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_1                                                                    (0x98U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_2                                                                    (0x9cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_3                                                                    (0xa0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_4                                                                    (0xa4U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_5                                                                    (0xa8U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_0                                                                    (0xacU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_1                                                                    (0xb0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_2                                                                    (0xb4U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_3                                                                    (0xb8U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_4                                                                    (0xbcU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_5                                                                    (0xc0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_6                                                                    (0xc4U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_7                                                                    (0xc8U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_0                                                                   (0xccU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_1                                                                   (0xd0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_2                                                                   (0xd4U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_3                                                                   (0xd8U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_4                                                                   (0xdcU)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_GPU                                                                     (0xe0U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_MPU                                                                     (0xe4U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_CORE                                                                    (0xe8U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_MPU23                                                                   (0xecU)
#define CTRL_CORE_STD_FUSE_MPK_0                                                                            (0x120U)
#define CTRL_CORE_STD_FUSE_MPK_1                                                                            (0x124U)
#define CTRL_CORE_STD_FUSE_MPK_2                                                                            (0x128U)
#define CTRL_CORE_STD_FUSE_MPK_3                                                                            (0x12cU)
#define CTRL_CORE_STD_FUSE_MPK_4                                                                            (0x130U)
#define CTRL_CORE_STD_FUSE_MPK_5                                                                            (0x134U)
#define CTRL_CORE_STD_FUSE_MPK_6                                                                            (0x138U)
#define CTRL_CORE_STD_FUSE_MPK_7                                                                            (0x13cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_0                                                                (0x140U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_1                                                                (0x144U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_2                                                                (0x148U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_3                                                                (0x14cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_4                                                                (0x150U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_5                                                                (0x154U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_0                                                                (0x158U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_1                                                                (0x15cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_2                                                                (0x160U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_3                                                                (0x164U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_4                                                                (0x168U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_5                                                                (0x16cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_6                                                                (0x170U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_7                                                                (0x174U)
#define CTRL_CORE_CUST_FUSE_SWRV_0                                                                          (0x1bcU)
#define CTRL_CORE_CUST_FUSE_SWRV_1                                                                          (0x1c0U)
#define CTRL_CORE_CUST_FUSE_SWRV_2                                                                          (0x1c4U)
#define CTRL_CORE_CUST_FUSE_SWRV_3                                                                          (0x1c8U)
#define CTRL_CORE_CUST_FUSE_SWRV_4                                                                          (0x1ccU)
#define CTRL_CORE_CUST_FUSE_SWRV_5                                                                          (0x1d0U)
#define CTRL_CORE_CUST_FUSE_SWRV_6                                                                          (0x1d4U)
#define CTRL_CORE_BREG_SELECTION                                                                            (0x1e0U)
#define CTRL_CORE_DPLL_BCLK                                                                                 (0x1e4U)
#define CTRL_CORE_DPLL_BADDR_BDATAW                                                                         (0x1e8U)
#define CTRL_CORE_DPLL_BDATAR                                                                               (0x1ecU)
#define CTRL_CORE_DEV_CONF                                                                                  (0x200U)
#define CTRL_CORE_TEMP_SENSOR_MPU                                                                           (0x22cU)
#define CTRL_CORE_TEMP_SENSOR_GPU                                                                           (0x230U)
#define CTRL_CORE_TEMP_SENSOR_CORE                                                                          (0x234U)
#define CTRL_CORE_HWOBS_CONTROL                                                                             (0x260U)
#define CTRL_CORE_PCS1                                                                                      (0x264U)
#define CTRL_CORE_PCS2                                                                                      (0x268U)
#define CTRL_CORE_PCS_REVISION                                                                              (0x26cU)
#define CTRL_CORE_PHY_POWER_USB                                                                             (0x270U)
#define CTRL_CORE_PHY_POWER_SATA                                                                            (0x274U)
#define CTRL_CORE_BANDGAP_MASK_1                                                                            (0x280U)
#define CTRL_CORE_BANDGAP_THRESHOLD_MPU                                                                     (0x284U)
#define CTRL_CORE_BANDGAP_THRESHOLD_GPU                                                                     (0x288U)
#define CTRL_CORE_BANDGAP_THRESHOLD_CORE                                                                    (0x28cU)
#define CTRL_CORE_BANDGAP_TSHUT_MPU                                                                         (0x290U)
#define CTRL_CORE_BANDGAP_TSHUT_GPU                                                                         (0x294U)
#define CTRL_CORE_BANDGAP_TSHUT_CORE                                                                        (0x298U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_MPU                                                                   (0x29cU)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_GPU                                                                   (0x2a0U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_CORE                                                                  (0x2a4U)
#define CTRL_CORE_BANDGAP_STATUS_1                                                                          (0x2a8U)
#define CTRL_CORE_SATA_EXT_MODE                                                                             (0x2acU)
#define CTRL_CORE_DTEMP_MPU_0                                                                               (0x2c0U)
#define CTRL_CORE_DTEMP_MPU_1                                                                               (0x2c4U)
#define CTRL_CORE_DTEMP_MPU_2                                                                               (0x2c8U)
#define CTRL_CORE_DTEMP_MPU_3                                                                               (0x2ccU)
#define CTRL_CORE_DTEMP_MPU_4                                                                               (0x2d0U)
#define CTRL_CORE_DTEMP_GPU_0                                                                               (0x2d4U)
#define CTRL_CORE_DTEMP_GPU_1                                                                               (0x2d8U)
#define CTRL_CORE_DTEMP_GPU_2                                                                               (0x2dcU)
#define CTRL_CORE_DTEMP_GPU_3                                                                               (0x2e0U)
#define CTRL_CORE_DTEMP_GPU_4                                                                               (0x2e4U)
#define CTRL_CORE_DTEMP_CORE_0                                                                              (0x2e8U)
#define CTRL_CORE_DTEMP_CORE_1                                                                              (0x2ecU)
#define CTRL_CORE_DTEMP_CORE_2                                                                              (0x2f0U)
#define CTRL_CORE_DTEMP_CORE_3                                                                              (0x2f4U)
#define CTRL_CORE_DTEMP_CORE_4                                                                              (0x2f8U)
#define CTRL_CORE_SMA_SW_0                                                                                  (0x2fcU)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2                                                                     (0x314U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2                                                                    (0x31cU)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1                                                                 (0x320U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2                                                                 (0x324U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3                                                                 (0x328U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4                                                                 (0x32cU)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5                                                                 (0x330U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6                                                                 (0x334U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1                                                                   (0x33cU)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2                                                                   (0x340U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4                                                                   (0x348U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_5                                                                   (0x34cU)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6                                                                   (0x350U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_0                                                                    (0x358U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_1                                                                    (0x35cU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_2                                                                    (0x360U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_3                                                                    (0x364U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_4                                                                    (0x368U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL                                                                (0x36cU)
#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL                                                                   (0x370U)
#define CTRL_CORE_MAC_ID_SW_0                                                                               (0x414U)
#define CTRL_CORE_MAC_ID_SW_1                                                                               (0x418U)
#define CTRL_CORE_MAC_ID_SW_2                                                                               (0x41cU)
#define CTRL_CORE_MAC_ID_SW_3                                                                               (0x420U)
#define CTRL_CORE_SMA_SW_1                                                                                  (0x434U)
#define CTRL_CORE_DSS_PLL_CONTROL                                                                           (0x438U)
#define CTRL_CORE_MMR_LOCK_1                                                                                (0x440U)
#define CTRL_CORE_MMR_LOCK_2                                                                                (0x444U)
#define CTRL_CORE_MMR_LOCK_3                                                                                (0x448U)
#define CTRL_CORE_MMR_LOCK_4                                                                                (0x44cU)
#define CTRL_CORE_MMR_LOCK_5                                                                                (0x450U)
#define CTRL_CORE_CONTROL_IO_1                                                                              (0x454U)
#define CTRL_CORE_CONTROL_IO_2                                                                              (0x458U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT                                                                     (0x45cU)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT                                                                     (0x460U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_DSPEVE                                                                  (0x464U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_IVA                                                                     (0x468U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL                                                               (0x46cU)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL                                                                  (0x470U)
#define CTRL_CORE_TEMP_SENSOR_DSPEVE                                                                        (0x474U)
#define CTRL_CORE_TEMP_SENSOR_IVA                                                                           (0x478U)
#define CTRL_CORE_BANDGAP_MASK_2                                                                            (0x47cU)
#define CTRL_CORE_BANDGAP_THRESHOLD_DSPEVE                                                                  (0x480U)
#define CTRL_CORE_BANDGAP_THRESHOLD_IVA                                                                     (0x484U)
#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE                                                                      (0x488U)
#define CTRL_CORE_BANDGAP_TSHUT_IVA                                                                         (0x48cU)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_DSPEVE                                                                (0x490U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_IVA                                                                   (0x494U)
#define CTRL_CORE_BANDGAP_STATUS_2                                                                          (0x498U)
#define CTRL_CORE_DTEMP_DSPEVE_0                                                                            (0x49cU)
#define CTRL_CORE_DTEMP_DSPEVE_1                                                                            (0x4a0U)
#define CTRL_CORE_DTEMP_DSPEVE_2                                                                            (0x4a4U)
#define CTRL_CORE_DTEMP_DSPEVE_3                                                                            (0x4a8U)
#define CTRL_CORE_DTEMP_DSPEVE_4                                                                            (0x4acU)
#define CTRL_CORE_DTEMP_IVA_0                                                                               (0x4b0U)
#define CTRL_CORE_DTEMP_IVA_1                                                                               (0x4b4U)
#define CTRL_CORE_DTEMP_IVA_2                                                                               (0x4b8U)
#define CTRL_CORE_DTEMP_IVA_3                                                                               (0x4bcU)
#define CTRL_CORE_DTEMP_IVA_4                                                                               (0x4c0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_0                                                                   (0x4c4U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_1                                                                   (0x4c8U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_2                                                                   (0x4ccU)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_3                                                                   (0x4d0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_4                                                                   (0x4d4U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_5                                                                   (0x4c4U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_0                                                                (0x4d8U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_1                                                                (0x4dcU)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_2                                                                (0x4e0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_3                                                                (0x4e4U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_4                                                                (0x4e8U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_5                                                                (0x4d8U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_0                                                                  (0x4ecU)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_1                                                                  (0x4f0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_2                                                                  (0x4f4U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_3                                                                  (0x4f8U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_4                                                                  (0x4fcU)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL                                                               (0x580U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL                                                               (0x584U)
#define CTRL_CORE_NMI_DESTINATION_1                                                                         (0x58cU)
#define CTRL_CORE_NMI_DESTINATION_2                                                                         (0x590U)
#define CTRL_CORE_IP_PRESSURE                                                                               (0x598U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_0                                                                 (0x5a0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_1                                                                 (0x5a4U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_2                                                                 (0x5a8U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_3                                                                 (0x5acU)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_4                                                                 (0x5b0U)
#define CTRL_CORE_CUST_FUSE_SWRV_7                                                                          (0x5b4U)
#define CTRL_CORE_STD_FUSE_CALIBRATION_OVERRIDE_VALUE_0                                                     (0x5b8U)
#define CTRL_CORE_STD_FUSE_CALIBRATION_OVERRIDE_VALUE_1                                                     (0x5bcU)
#define CTRL_CORE_PCIE_POWER_STATE                                                                          (0x5c0U)
#define CTRL_CORE_BOOTSTRAP                                                                                 (0x5c4U)
#define CTRL_CORE_MLB_SIG_IO_CTRL                                                                           (0x5c8U)
#define CTRL_CORE_MLB_DAT_IO_CTRL                                                                           (0x5ccU)
#define CTRL_CORE_MLB_CLK_BG_CTRL                                                                           (0x5d0U)
#define CTRL_CORE_CORTEX_M4_MMUADDRTRANSLTR                                                                 (0x258U)
#define CTRL_CORE_CORTEX_M4_MMUADDRLOGICTR                                                                  (0x25cU)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CTRL_CORE_STATUS_DEVICE_TYPE_SHIFT                                                                  (6U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_MASK                                                                   (0x000001c0U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_B_2                                                                 (6U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_B_0                                                                 (4U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_E                                                                   (1U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_GP                                                                  (3U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_T                                                                   (0U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_B_3                                                                 (7U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_HS                                                                  (2U)
#define CTRL_CORE_STATUS_DEVICE_TYPE_DEV_B_1                                                                 (5U)

#define CTRL_CORE_STATUS_RESERVED_0_SHIFT                                                                   (9U)
#define CTRL_CORE_STATUS_RESERVED_0_MASK                                                                    (0xfffffe00U)

#define CTRL_CORE_STATUS_RESERVED_SHIFT                                                                     (0U)
#define CTRL_CORE_STATUS_RESERVED_MASK                                                                      (0x0000003fU)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE2_FW_ERROR_SHIFT                                                 (29U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE2_FW_ERROR_MASK                                                  (0x20000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE2_FW_ERROR_EVE2_FW_ERROR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE2_FW_ERROR_NO_EVE2_FW_ERROR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE1_FW_ERROR_SHIFT                                                 (28U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE1_FW_ERROR_MASK                                                  (0x10000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE1_FW_ERROR_EVE1_FW_ERROR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EVE1_FW_ERROR_NO_EVE1_FW_ERROR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_OCMC_ROM_FW_ERROR_SHIFT                                             (27U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_OCMC_ROM_FW_ERROR_MASK                                              (0x08000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_OCMC_ROM_FW_ERROR_OCMC_ROM_FW_ERROR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_OCMC_ROM_FW_ERROR_NO_OCMC_ROM_FW_ERROR                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_BB2D_FW_ERROR_SHIFT                                                 (23U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_BB2D_FW_ERROR_MASK                                                  (0x00800000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_BB2D_FW_ERROR_BB2D_FW_ERROR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_BB2D_FW_ERROR_NO_BB2D_FW_ERROR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_WAKEUP_FW_ERROR_SHIFT                                            (22U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_WAKEUP_FW_ERROR_MASK                                             (0x00400000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_WAKEUP_FW_ERROR_L4WKUP_FW_ERROR                                   (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_WAKEUP_FW_ERROR_NO_L4WKUP_FW_ERROR                                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DEBUGSS_FW_ERROR_SHIFT                                              (18U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DEBUGSS_FW_ERROR_MASK                                               (0x00040000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DEBUGSS_FW_ERROR_DEBUGSS_FW_ERR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DEBUGSS_FW_ERROR_NO_DEBUGSS_FW_ERR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_SHIFT                                            (17U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_MASK                                             (0x00020000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_L4CONFIG_FW_ERR                                   (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_CONFIG_FW_ERROR_NO_L4CONFIG_FW_ERR                                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_PERIPH1_FW_ERROR_SHIFT                                           (16U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_PERIPH1_FW_ERROR_MASK                                            (0x00010000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_PERIPH1_FW_ERROR_L4PERIPH1_FW_ERR                                 (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L4_PERIPH1_FW_ERROR_NO_L4PERIPH1_FW_ERR                              (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DSS_FW_ERROR_SHIFT                                                  (14U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DSS_FW_ERROR_MASK                                                   (0x00004000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DSS_FW_ERROR_DSS_FW_ERR                                              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_DSS_FW_ERROR_NO_DSS_FW_ERR                                           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPU_FW_ERROR_SHIFT                                                  (13U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPU_FW_ERROR_MASK                                                   (0x00002000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPU_FW_ERROR_GPU_FW_ERR                                              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPU_FW_ERROR_NO_GPU_FW_ERR                                           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IVAHD_SL2_FW_ERROR_SHIFT                                            (6U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IVAHD_SL2_FW_ERROR_MASK                                             (0x00000040U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IVAHD_SL2_FW_ERROR_IVAHD_SL2_FW_ERR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IVAHD_SL2_FW_ERROR_NO_IVAHD_SL2_FW_ERR                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IPU1_FW_ERROR_SHIFT                                                 (5U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IPU1_FW_ERROR_MASK                                                  (0x00000020U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IPU1_FW_ERROR_IPU1_FW_ERR                                            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IPU1_FW_ERROR_NO_IPU1_FW_ERR                                         (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IVAHD_FW_ERROR_SHIFT                                                (4U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IVAHD_FW_ERROR_MASK                                                 (0x00000010U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IVAHD_FW_ERROR_IVAHD_FW_ERR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_IVAHD_FW_ERROR_NO_IVAHD_FW_ERR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EMIF_FW_ERROR_SHIFT                                                 (3U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EMIF_FW_ERROR_MASK                                                  (0x00000008U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EMIF_FW_ERROR_EMIF_FW_ERR                                            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_EMIF_FW_ERROR_NO_EMIF_FW_ERR                                         (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPMC_FW_ERROR_SHIFT                                                 (2U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPMC_FW_ERROR_MASK                                                  (0x00000004U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPMC_FW_ERROR_GPMC_FW_ERR                                            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_GPMC_FW_ERROR_NO_GPMC_FW_ERR                                         (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_SHIFT                                               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_MASK                                                (0x00000002U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_L3RAM1_FW_ERR                                        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_L3RAM1_FW_ERROR_NO_L3RAM1_FW_ERR                                     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED1_SHIFT                                                     (0U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED1_MASK                                                      (0x00000001U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED2_SHIFT                                                     (15U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED2_MASK                                                      (0x00008000U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED3_SHIFT                                                     (19U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED3_MASK                                                      (0x00080000U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED4_SHIFT                                                     (20U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED4_MASK                                                      (0x00100000U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED5_SHIFT                                                     (21U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED5_MASK                                                      (0x00200000U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED6_SHIFT                                                     (26U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED6_MASK                                                      (0x04000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED6_CT_TRACE_BUFFER_ROUTER_FW_ERROR                            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED6_NO_CT_TRACE_BUFFER_ROUTER_FW_ERROR                         (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED7_SHIFT                                                     (24U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED7_MASK                                                      (0x01000000U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED8_SHIFT                                                     (25U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED8_MASK                                                      (0x02000000U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED10_SHIFT                                                    (30U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED10_MASK                                                     (0xc0000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED10_EVE3_FW_ERROR                                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED10_NO_EVE3_FW_ERROR                                          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED9_SHIFT                                                     (7U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_1_RESERVED9_MASK                                                      (0x00001f80U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE2_DBGFW_ERROR_SHIFT                                             (29U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE2_DBGFW_ERROR_MASK                                              (0x20000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE2_DBGFW_ERROR_EVE2_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE2_DBGFW_ERROR_NO_EVE2_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE1_DBGFW_ERROR_SHIFT                                             (28U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE1_DBGFW_ERROR_MASK                                              (0x10000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE1_DBGFW_ERROR_EVE1_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EVE1_DBGFW_ERROR_NO_EVE1_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_OCMC_ROM_DBGFW_ERROR_SHIFT                                         (27U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_OCMC_ROM_DBGFW_ERROR_MASK                                          (0x08000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_OCMC_ROM_DBGFW_ERROR_OCMC_ROM_FW_ERROR                              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_OCMC_ROM_DBGFW_ERROR_NO_OCMC_ROM_FW_ERROR                           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_BB2D_DBGFW_ERROR_SHIFT                                             (23U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_BB2D_DBGFW_ERROR_MASK                                              (0x00800000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_BB2D_DBGFW_ERROR_BB2D_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_BB2D_DBGFW_ERROR_NO_BB2D_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_WAKEUP_DBGFW_ERROR_SHIFT                                        (22U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_WAKEUP_DBGFW_ERROR_MASK                                         (0x00400000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_WAKEUP_DBGFW_ERROR_L4WKUP_FW_ERROR                               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_WAKEUP_DBGFW_ERROR_NO_L4WKUP_FW_ERROR                            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DEBUGSS_DBGFW_ERROR_SHIFT                                          (18U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DEBUGSS_DBGFW_ERROR_MASK                                           (0x00040000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DEBUGSS_DBGFW_ERROR_DEBUGSS_FW_ERR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DEBUGSS_DBGFW_ERROR_NO_DEBUGSS_FW_ERR                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_CONFIG_DBGFW_ERROR_SHIFT                                        (17U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_CONFIG_DBGFW_ERROR_MASK                                         (0x00020000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_CONFIG_DBGFW_ERROR_L4CONFIG_FW_ERR                               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_CONFIG_DBGFW_ERROR_NO_L4CONFIG_FW_ERR                            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_PERIPH1_DBGFW_ERROR_SHIFT                                       (16U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_PERIPH1_DBGFW_ERROR_MASK                                        (0x00010000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_PERIPH1_DBGFW_ERROR_L4PERIPH1_FW_ERR                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L4_PERIPH1_DBGFW_ERROR_NO_L4PERIPH1_FW_ERR                          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DSS_DBGFW_ERROR_SHIFT                                              (14U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DSS_DBGFW_ERROR_MASK                                               (0x00004000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DSS_DBGFW_ERROR_DSS_FW_ERR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_DSS_DBGFW_ERROR_NO_DSS_FW_ERR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPU_DBGFW_ERROR_SHIFT                                              (13U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPU_DBGFW_ERROR_MASK                                               (0x00002000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPU_DBGFW_ERROR_GPU_FW_ERR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPU_DBGFW_ERROR_NO_GPU_FW_ERR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IVAHD_SL2_DBGFW_ERROR_SHIFT                                        (6U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IVAHD_SL2_DBGFW_ERROR_MASK                                         (0x00000040U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IVAHD_SL2_DBGFW_ERROR_IVAHD_SL2_FW_ERR                              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IVAHD_SL2_DBGFW_ERROR_NO_IVAHD_SL2_FW_ERR                           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IPU1_DBGFW_ERROR_SHIFT                                             (5U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IPU1_DBGFW_ERROR_MASK                                              (0x00000020U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IPU1_DBGFW_ERROR_IPU1_FW_ERR                                        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IPU1_DBGFW_ERROR_NO_IPU1_FW_ERR                                     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IVAHD_DBGFW_ERROR_SHIFT                                            (4U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IVAHD_DBGFW_ERROR_MASK                                             (0x00000010U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IVAHD_DBGFW_ERROR_IVAHD_FW_ERR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_IVAHD_DBGFW_ERROR_NO_IVAHD_FW_ERR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EMIF_DBGFW_ERROR_SHIFT                                             (3U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EMIF_DBGFW_ERROR_MASK                                              (0x00000008U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EMIF_DBGFW_ERROR_EMIF_FW_ERR                                        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_EMIF_DBGFW_ERROR_NO_EMIF_FW_ERR                                     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPMC_DBGFW_ERROR_SHIFT                                             (2U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPMC_DBGFW_ERROR_MASK                                              (0x00000004U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPMC_DBGFW_ERROR_GPMC_FW_ERR                                        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_GPMC_DBGFW_ERROR_NO_GPMC_FW_ERR                                     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L3RAM1_DBGFW_ERROR_SHIFT                                           (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L3RAM1_DBGFW_ERROR_MASK                                            (0x00000002U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L3RAM1_DBGFW_ERROR_L3RAM1_FW_ERR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_L3RAM1_DBGFW_ERROR_NO_L3RAM1_FW_ERR                                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED0_SHIFT                                                    (7U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED0_MASK                                                     (0x00001f80U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED2_SHIFT                                                    (15U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED2_MASK                                                     (0x00008000U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED1_SHIFT                                                    (0U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED1_MASK                                                     (0x00000001U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED3_SHIFT                                                    (19U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED3_MASK                                                     (0x00380000U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED4_SHIFT                                                    (24U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED4_MASK                                                     (0x07000000U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED5_SHIFT                                                    (30U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED5_MASK                                                     (0xc0000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED5_EVE3_FW_ERROR                                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_1_RESERVED5_NO_EVE3_FW_ERROR                                          (0U)

#define CTRL_CORE_MPU_FORCEWRNP_MPU_FORCEWRNP_SHIFT                                                         (0U)
#define CTRL_CORE_MPU_FORCEWRNP_MPU_FORCEWRNP_MASK                                                          (0x00000001U)
#define CTRL_CORE_MPU_FORCEWRNP_MPU_FORCEWRNP_ENABLE                                                         (1U)
#define CTRL_CORE_MPU_FORCEWRNP_MPU_FORCEWRNP_DISABLE                                                        (0U)

#define CTRL_CORE_MPU_FORCEWRNP_RESERVED_0_SHIFT                                                            (1U)
#define CTRL_CORE_MPU_FORCEWRNP_RESERVED_0_MASK                                                             (0xfffffffeU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_0_STD_FUSE_OPP_VDD_GPU_0_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_0_STD_FUSE_OPP_VDD_GPU_0_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_1_STD_FUSE_OPP_VDD_GPU_1_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_1_STD_FUSE_OPP_VDD_GPU_1_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_2_STD_FUSE_OPP_VDD_GPU_2_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_2_STD_FUSE_OPP_VDD_GPU_2_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_3_STD_FUSE_OPP_VDD_GPU_3_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_3_STD_FUSE_OPP_VDD_GPU_3_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_4_STD_FUSE_OPP_VDD_GPU_4_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_4_STD_FUSE_OPP_VDD_GPU_4_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_5_STD_FUSE_OPP_VDD_GPU_5_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_5_STD_FUSE_OPP_VDD_GPU_5_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_0_STD_FUSE_OPP_VDD_MPU_0_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_0_STD_FUSE_OPP_VDD_MPU_0_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_1_STD_FUSE_OPP_VDD_MPU_1_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_1_STD_FUSE_OPP_VDD_MPU_1_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_2_STD_FUSE_OPP_VDD_MPU_2_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_2_STD_FUSE_OPP_VDD_MPU_2_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_3_STD_FUSE_OPP_VDD_MPU_3_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_3_STD_FUSE_OPP_VDD_MPU_3_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_4_STD_FUSE_OPP_VDD_MPU_4_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_4_STD_FUSE_OPP_VDD_MPU_4_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_5_STD_FUSE_OPP_VDD_MPU_5_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_5_STD_FUSE_OPP_VDD_MPU_5_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_6_STD_FUSE_OPP_VDD_MPU_6_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_6_STD_FUSE_OPP_VDD_MPU_6_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_7_STD_FUSE_OPP_VDD_MPU_7_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_7_STD_FUSE_OPP_VDD_MPU_7_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_0_STD_FUSE_OPP_VDD_CORE_0_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_0_STD_FUSE_OPP_VDD_CORE_0_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_1_STD_FUSE_OPP_VDD_CORE_1_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_1_STD_FUSE_OPP_VDD_CORE_1_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_2_STD_FUSE_OPP_VDD_CORE_2_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_2_STD_FUSE_OPP_VDD_CORE_2_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_3_STD_FUSE_OPP_VDD_CORE_3_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_3_STD_FUSE_OPP_VDD_CORE_3_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_4_STD_FUSE_OPP_VDD_CORE_4_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_CORE_4_STD_FUSE_OPP_VDD_CORE_4_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_BGAP_GPU_STD_FUSE_OPP_BGAP_GPU_SHIFT                                         (0U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_GPU_STD_FUSE_OPP_BGAP_GPU_MASK                                          (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_BGAP_MPU_STD_FUSE_OPP_BGAP_MPU_SHIFT                                         (0U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_MPU_STD_FUSE_OPP_BGAP_MPU_MASK                                          (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_BGAP_CORE_STD_FUSE_OPP_BGAP_CORE_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_CORE_STD_FUSE_OPP_BGAP_CORE_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_BGAP_MPU23_STD_FUSE_OPP_BGAP_MPU3_SHIFT                                      (16U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_MPU23_STD_FUSE_OPP_BGAP_MPU3_MASK                                       (0xffff0000U)

#define CTRL_CORE_STD_FUSE_OPP_BGAP_MPU23_STD_FUSE_OPP_BGAP_MPU2_SHIFT                                      (0U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_MPU23_STD_FUSE_OPP_BGAP_MPU2_MASK                                       (0x0000ffffU)

#define CTRL_CORE_STD_FUSE_MPK_0_STD_FUSE_MPK_0_SHIFT                                                       (0U)
#define CTRL_CORE_STD_FUSE_MPK_0_STD_FUSE_MPK_0_MASK                                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_1_STD_FUSE_MPK_1_SHIFT                                                       (0U)
#define CTRL_CORE_STD_FUSE_MPK_1_STD_FUSE_MPK_1_MASK                                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_2_STD_FUSE_MPK_2_SHIFT                                                       (0U)
#define CTRL_CORE_STD_FUSE_MPK_2_STD_FUSE_MPK_2_MASK                                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_3_STD_FUSE_MPK_3_SHIFT                                                       (0U)
#define CTRL_CORE_STD_FUSE_MPK_3_STD_FUSE_MPK_3_MASK                                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_4_STD_FUSE_MPK_4_SHIFT                                                       (0U)
#define CTRL_CORE_STD_FUSE_MPK_4_STD_FUSE_MPK_4_MASK                                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_5_STD_FUSE_MPK_5_SHIFT                                                       (0U)
#define CTRL_CORE_STD_FUSE_MPK_5_STD_FUSE_MPK_5_MASK                                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_6_STD_FUSE_MPK_6_SHIFT                                                       (0U)
#define CTRL_CORE_STD_FUSE_MPK_6_STD_FUSE_MPK_6_MASK                                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_MPK_7_STD_FUSE_MPK_7_SHIFT                                                       (0U)
#define CTRL_CORE_STD_FUSE_MPK_7_STD_FUSE_MPK_7_MASK                                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_0_STD_FUSE_OPP_VDD_GPU_LVT_0_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_0_STD_FUSE_OPP_VDD_GPU_LVT_0_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_1_STD_FUSE_OPP_VDD_GPU_LVT_1_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_1_STD_FUSE_OPP_VDD_GPU_LVT_1_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_2_STD_FUSE_OPP_VDD_GPU_LVT_2_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_2_STD_FUSE_OPP_VDD_GPU_LVT_2_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_3_STD_FUSE_OPP_VDD_GPU_LVT_3_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_3_STD_FUSE_OPP_VDD_GPU_LVT_3_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_4_STD_FUSE_OPP_VDD_GPU_LVT_4_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_4_STD_FUSE_OPP_VDD_GPU_LVT_4_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_5_STD_FUSE_OPP_VDD_GPU_LVT_5_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_GPU_LVT_5_STD_FUSE_OPP_VDD_GPU_LVT_5_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_0_STD_FUSE_OPP_VDD_MPU_LVT_0_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_0_STD_FUSE_OPP_VDD_MPU_LVT_0_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_1_STD_FUSE_OPP_VDD_MPU_LVT_1_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_1_STD_FUSE_OPP_VDD_MPU_LVT_1_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_2_STD_FUSE_OPP_VDD_MPU_LVT_2_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_2_STD_FUSE_OPP_VDD_MPU_LVT_2_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_3_STD_FUSE_OPP_VDD_MPU_LVT_3_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_3_STD_FUSE_OPP_VDD_MPU_LVT_3_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_4_STD_FUSE_OPP_VDD_MPU_LVT_4_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_4_STD_FUSE_OPP_VDD_MPU_LVT_4_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_5_STD_FUSE_OPP_VDD_MPU_LVT_5_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_5_STD_FUSE_OPP_VDD_MPU_LVT_5_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_6_STD_FUSE_OPP_VDD_MPU_LVT_6_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_6_STD_FUSE_OPP_VDD_MPU_LVT_6_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_7_STD_FUSE_OPP_VDD_MPU_LVT_7_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_MPU_LVT_7_STD_FUSE_OPP_VDD_MPU_LVT_7_MASK                                (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_0_CUST_FUSE_SWRV_0_SHIFT                                                   (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_0_CUST_FUSE_SWRV_0_MASK                                                    (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_1_CUST_FUSE_SWRV_1_SHIFT                                                   (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_1_CUST_FUSE_SWRV_1_MASK                                                    (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_2_CUST_FUSE_SWRV_2_SHIFT                                                   (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_2_CUST_FUSE_SWRV_2_MASK                                                    (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_3_CUST_FUSE_SWRV_3_SHIFT                                                   (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_3_CUST_FUSE_SWRV_3_MASK                                                    (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_4_CUST_FUSE_SWRV_4_SHIFT                                                   (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_4_CUST_FUSE_SWRV_4_MASK                                                    (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_5_CUST_FUSE_SWRV_5_SHIFT                                                   (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_5_CUST_FUSE_SWRV_5_MASK                                                    (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_6_CUST_FUSE_SWRV_6_SHIFT                                                   (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_6_CUST_FUSE_SWRV_6_MASK                                                    (0xffffffffU)

#define CTRL_CORE_BREG_SELECTION_SEL_DDR_SHIFT                                                              (14U)
#define CTRL_CORE_BREG_SELECTION_SEL_DDR_MASK                                                               (0x00004000U)
#define CTRL_CORE_BREG_SELECTION_SEL_DDR_SEL                                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_DDR_NOSEL                                                               (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_GPU_SHIFT                                                              (13U)
#define CTRL_CORE_BREG_SELECTION_SEL_GPU_MASK                                                               (0x00002000U)
#define CTRL_CORE_BREG_SELECTION_SEL_GPU_SEL                                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_GPU_NOSEL                                                               (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_GMAC_SHIFT                                                             (12U)
#define CTRL_CORE_BREG_SELECTION_SEL_GMAC_MASK                                                              (0x00001000U)
#define CTRL_CORE_BREG_SELECTION_SEL_GMAC_SEL                                                                (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_GMAC_NOSEL                                                              (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_DSP_SHIFT                                                              (11U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSP_MASK                                                               (0x00000800U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSP_SEL                                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSP_NOSEL                                                               (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_EVE_SHIFT                                                              (10U)
#define CTRL_CORE_BREG_SELECTION_SEL_EVE_MASK                                                               (0x00000400U)
#define CTRL_CORE_BREG_SELECTION_SEL_EVE_SEL                                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_EVE_NOSEL                                                               (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_USB_SHIFT                                                              (9U)
#define CTRL_CORE_BREG_SELECTION_SEL_USB_MASK                                                               (0x00000200U)
#define CTRL_CORE_BREG_SELECTION_SEL_USB_SEL                                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_USB_NOSEL                                                               (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_IVA_SHIFT                                                              (8U)
#define CTRL_CORE_BREG_SELECTION_SEL_IVA_MASK                                                               (0x00000100U)
#define CTRL_CORE_BREG_SELECTION_SEL_IVA_SEL                                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_IVA_NOSEL                                                               (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_PCIE_SHIFT                                                             (7U)
#define CTRL_CORE_BREG_SELECTION_SEL_PCIE_MASK                                                              (0x00000080U)
#define CTRL_CORE_BREG_SELECTION_SEL_PCIE_SEL                                                                (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_PCIE_NOSEL                                                              (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_SATA_SHIFT                                                             (6U)
#define CTRL_CORE_BREG_SELECTION_SEL_SATA_MASK                                                              (0x00000040U)
#define CTRL_CORE_BREG_SELECTION_SEL_SATA_SEL                                                                (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_SATA_NOSEL                                                              (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_PER_SHIFT                                                              (5U)
#define CTRL_CORE_BREG_SELECTION_SEL_PER_MASK                                                               (0x00000020U)
#define CTRL_CORE_BREG_SELECTION_SEL_PER_SEL                                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_PER_NOSEL                                                               (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_HDMI_SHIFT                                                             (4U)
#define CTRL_CORE_BREG_SELECTION_SEL_HDMI_MASK                                                              (0x00000010U)
#define CTRL_CORE_BREG_SELECTION_SEL_HDMI_SEL                                                                (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_HDMI_NOSEL                                                              (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_DSI1C_SHIFT                                                            (3U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSI1C_MASK                                                             (0x00000008U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSI1C_SEL                                                               (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSI1C_NOSEL                                                             (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_DSI1A_SHIFT                                                            (2U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSI1A_MASK                                                             (0x00000004U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSI1A_SEL                                                               (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_DSI1A_NOSEL                                                             (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_CORE_SHIFT                                                             (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_CORE_MASK                                                              (0x00000002U)
#define CTRL_CORE_BREG_SELECTION_SEL_CORE_SEL                                                                (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_CORE_NOSEL                                                              (0U)

#define CTRL_CORE_BREG_SELECTION_SEL_IPU_SHIFT                                                              (0U)
#define CTRL_CORE_BREG_SELECTION_SEL_IPU_MASK                                                               (0x00000001U)
#define CTRL_CORE_BREG_SELECTION_SEL_IPU_SEL                                                                 (1U)
#define CTRL_CORE_BREG_SELECTION_SEL_IPU_NOSEL                                                               (0U)

#define CTRL_CORE_BREG_SELECTION_RESERVED_0_SHIFT                                                           (15U)
#define CTRL_CORE_BREG_SELECTION_RESERVED_0_MASK                                                            (0xffff8000U)

#define CTRL_CORE_DPLL_BCLK_BRW_SHIFT                                                                       (1U)
#define CTRL_CORE_DPLL_BCLK_BRW_MASK                                                                        (0x00000002U)
#define CTRL_CORE_DPLL_BCLK_BRW_SEL                                                                          (1U)
#define CTRL_CORE_DPLL_BCLK_BRW_NOSEL                                                                        (0U)

#define CTRL_CORE_DPLL_BCLK_BCLK_SHIFT                                                                      (0U)
#define CTRL_CORE_DPLL_BCLK_BCLK_MASK                                                                       (0x00000001U)
#define CTRL_CORE_DPLL_BCLK_BCLK_SEL                                                                         (1U)
#define CTRL_CORE_DPLL_BCLK_BCLK_NOSEL                                                                       (0U)

#define CTRL_CORE_DPLL_BCLK_RESERVED_0_SHIFT                                                                (2U)
#define CTRL_CORE_DPLL_BCLK_RESERVED_0_MASK                                                                 (0xfffffffcU)

#define CTRL_CORE_DPLL_BADDR_BDATAW_BADDR_SHIFT                                                             (16U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_BADDR_MASK                                                              (0x000f0000U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_BADDR_SEL                                                                (1U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_BADDR_NOSEL                                                              (0U)

#define CTRL_CORE_DPLL_BADDR_BDATAW_BDATAW_SHIFT                                                            (0U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_BDATAW_MASK                                                             (0x0000ffffU)
#define CTRL_CORE_DPLL_BADDR_BDATAW_BDATAW_SEL                                                               (1U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_BDATAW_NOSEL                                                             (0U)

#define CTRL_CORE_DPLL_BADDR_BDATAW_RESERVED_0_SHIFT                                                        (20U)
#define CTRL_CORE_DPLL_BADDR_BDATAW_RESERVED_0_MASK                                                         (0xfff00000U)

#define CTRL_CORE_DPLL_BDATAR_BDATAR_SHIFT                                                                  (0U)
#define CTRL_CORE_DPLL_BDATAR_BDATAR_MASK                                                                   (0x0000ffffU)
#define CTRL_CORE_DPLL_BDATAR_BDATAR_SEL                                                                     (1U)
#define CTRL_CORE_DPLL_BDATAR_BDATAR_NOSEL                                                                   (0U)

#define CTRL_CORE_DPLL_BDATAR_RESERVED_0_SHIFT                                                              (16U)
#define CTRL_CORE_DPLL_BDATAR_RESERVED_0_MASK                                                               (0xffff0000U)

#define CTRL_CORE_DEV_CONF_RESERVED_0_SHIFT                                                                 (1U)
#define CTRL_CORE_DEV_CONF_RESERVED_0_MASK                                                                  (0xfffffffeU)

#define CTRL_CORE_DEV_CONF_USBPHY_PD_SHIFT                                                                  (0U)
#define CTRL_CORE_DEV_CONF_USBPHY_PD_MASK                                                                   (1U)

#define CTRL_CORE_TEMP_SENSOR_MPU_BGAP_TMPSOFF_MPU_SHIFT                                                    (11U)
#define CTRL_CORE_TEMP_SENSOR_MPU_BGAP_TMPSOFF_MPU_MASK                                                     (0x00000800U)

#define CTRL_CORE_TEMP_SENSOR_MPU_BGAP_EOCZ_MPU_SHIFT                                                       (10U)
#define CTRL_CORE_TEMP_SENSOR_MPU_BGAP_EOCZ_MPU_MASK                                                        (0x00000400U)

#define CTRL_CORE_TEMP_SENSOR_MPU_BGAP_DTEMP_MPU_SHIFT                                                      (0U)
#define CTRL_CORE_TEMP_SENSOR_MPU_BGAP_DTEMP_MPU_MASK                                                       (0x000003ffU)

#define CTRL_CORE_TEMP_SENSOR_MPU_RESERVED_0_SHIFT                                                          (12U)
#define CTRL_CORE_TEMP_SENSOR_MPU_RESERVED_0_MASK                                                           (0xfffff000U)

#define CTRL_CORE_TEMP_SENSOR_GPU_BGAP_TMPSOFF_GPU_SHIFT                                                    (11U)
#define CTRL_CORE_TEMP_SENSOR_GPU_BGAP_TMPSOFF_GPU_MASK                                                     (0x00000800U)

#define CTRL_CORE_TEMP_SENSOR_GPU_BGAP_EOCZ_GPU_SHIFT                                                       (10U)
#define CTRL_CORE_TEMP_SENSOR_GPU_BGAP_EOCZ_GPU_MASK                                                        (0x00000400U)

#define CTRL_CORE_TEMP_SENSOR_GPU_BGAP_DTEMP_GPU_SHIFT                                                      (0U)
#define CTRL_CORE_TEMP_SENSOR_GPU_BGAP_DTEMP_GPU_MASK                                                       (0x000003ffU)

#define CTRL_CORE_TEMP_SENSOR_GPU_RESERVED_0_SHIFT                                                          (12U)
#define CTRL_CORE_TEMP_SENSOR_GPU_RESERVED_0_MASK                                                           (0xfffff000U)

#define CTRL_CORE_TEMP_SENSOR_CORE_BGAP_TMPSOFF_CORE_SHIFT                                                  (11U)
#define CTRL_CORE_TEMP_SENSOR_CORE_BGAP_TMPSOFF_CORE_MASK                                                   (0x00000800U)

#define CTRL_CORE_TEMP_SENSOR_CORE_BGAP_EOCZ_CORE_SHIFT                                                     (10U)
#define CTRL_CORE_TEMP_SENSOR_CORE_BGAP_EOCZ_CORE_MASK                                                      (0x00000400U)

#define CTRL_CORE_TEMP_SENSOR_CORE_BGAP_DTEMP_CORE_SHIFT                                                    (0U)
#define CTRL_CORE_TEMP_SENSOR_CORE_BGAP_DTEMP_CORE_MASK                                                     (0x000003ffU)

#define CTRL_CORE_TEMP_SENSOR_CORE_RESERVED_0_SHIFT                                                         (12U)
#define CTRL_CORE_TEMP_SENSOR_CORE_RESERVED_0_MASK                                                          (0xfffff000U)

#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_2_SHIFT                                                    (14U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_2_MASK                                                     (0x0007c000U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_2_DIV8                                                      (8U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_2_DIV4                                                      (4U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_2_NODIV                                                     (1U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_2_DIV16                                                     (16U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_2_DIV2                                                      (2U)

#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_1_SHIFT                                                    (9U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_1_MASK                                                     (0x00003e00U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_1_DIV8                                                      (8U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_1_DIV4                                                      (4U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_1_NODIV                                                     (1U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_1_DIV16                                                     (16U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_1_DIV2                                                      (2U)

#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_SHIFT                                                      (3U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_MASK                                                       (0x000000f8U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_DIV8                                                        (8U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_DIV4                                                        (4U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_NODIV                                                       (1U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_DIV16                                                       (16U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_CLKDIV_SEL_DIV2                                                        (2U)

#define CTRL_CORE_HWOBS_CONTROL_HWOBS_ALL_ZERO_MODE_SHIFT                                                   (2U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_ALL_ZERO_MODE_MASK                                                    (0x00000004U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_ALL_ZERO_MODE_ENABLED                                                  (1U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_ALL_ZERO_MODE_DISABLED                                                 (0U)

#define CTRL_CORE_HWOBS_CONTROL_HWOBS_ALL_ONE_MODE_SHIFT                                                    (1U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_ALL_ONE_MODE_MASK                                                     (0x00000002U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_ALL_ONE_MODE_ENABLED                                                   (1U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_ALL_ONE_MODE_DISABLED                                                  (0U)

#define CTRL_CORE_HWOBS_CONTROL_HWOBS_MACRO_ENABLE_SHIFT                                                    (0U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_MACRO_ENABLE_MASK                                                     (0x00000001U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_MACRO_ENABLE_ENABLED                                                   (1U)
#define CTRL_CORE_HWOBS_CONTROL_HWOBS_MACRO_ENABLE_DISABLED                                                  (0U)

#define CTRL_CORE_HWOBS_CONTROL_RESERVED_0_SHIFT                                                            (19U)
#define CTRL_CORE_HWOBS_CONTROL_RESERVED_0_MASK                                                             (0xfff80000U)

#define CTRL_CORE_HWOBS_CONTROL_RESERVED_1_SHIFT                                                            (8U)
#define CTRL_CORE_HWOBS_CONTROL_RESERVED_1_MASK                                                             (0x00000100U)

#define CTRL_CORE_PCS1_USB_TEST_TXDATA_SHIFT                                                                (22U)
#define CTRL_CORE_PCS1_USB_TEST_TXDATA_MASK                                                                 (0xffc00000U)

#define CTRL_CORE_PCS1_USB_ERR_USB_BIT_EN_SHIFT                                                             (12U)
#define CTRL_CORE_PCS1_USB_ERR_USB_BIT_EN_MASK                                                              (0x003ff000U)

#define CTRL_CORE_PCS1_USB_CFG_HOLDOFF_SHIFT                                                                (4U)
#define CTRL_CORE_PCS1_USB_CFG_HOLDOFF_MASK                                                                 (0x00000ff0U)

#define CTRL_CORE_PCS1_USB_DET_DELAY_SHIFT                                                                  (0U)
#define CTRL_CORE_PCS1_USB_DET_DELAY_MASK                                                                   (0x0000000fU)

#define CTRL_CORE_PCS2_USB_CFG_SYNC_SHIFT                                                                   (27U)
#define CTRL_CORE_PCS2_USB_CFG_SYNC_MASK                                                                    (0xf8000000U)

#define CTRL_CORE_PCS2_USB_CFG_EQ_FUNC_SHIFT                                                                (23U)
#define CTRL_CORE_PCS2_USB_CFG_EQ_FUNC_MASK                                                                 (0x07800000U)

#define CTRL_CORE_PCS2_USB_CFG_EQ_HOLD_SHIFT                                                                (19U)
#define CTRL_CORE_PCS2_USB_CFG_EQ_HOLD_MASK                                                                 (0x00780000U)

#define CTRL_CORE_PCS2_USB_CFG_EQ_INIT_SHIFT                                                                (15U)
#define CTRL_CORE_PCS2_USB_CFG_EQ_INIT_MASK                                                                 (0x00078000U)

#define CTRL_CORE_PCS2_USB_TEST_OSEL_SHIFT                                                                  (12U)
#define CTRL_CORE_PCS2_USB_TEST_OSEL_MASK                                                                   (0x00007000U)

#define CTRL_CORE_PCS2_USB_RC_DELAY_SHIFT                                                                   (10U)
#define CTRL_CORE_PCS2_USB_RC_DELAY_MASK                                                                    (0x00000c00U)

#define CTRL_CORE_PCS2_USB_TEST_LSEL_SHIFT                                                                  (9U)
#define CTRL_CORE_PCS2_USB_TEST_LSEL_MASK                                                                   (0x00000200U)

#define CTRL_CORE_PCS2_USB_ERR_USB_MODE_SHIFT                                                               (6U)
#define CTRL_CORE_PCS2_USB_ERR_USB_MODE_MASK                                                                (0x000000c0U)

#define CTRL_CORE_PCS2_USB_L1_SLEEP_SHIFT                                                                   (5U)
#define CTRL_CORE_PCS2_USB_L1_SLEEP_MASK                                                                    (0x00000020U)

#define CTRL_CORE_PCS2_USB_TEST_MODE_SHIFT                                                                  (4U)
#define CTRL_CORE_PCS2_USB_TEST_MODE_MASK                                                                   (0x00000010U)

#define CTRL_CORE_PCS2_USB_ERR_USB_LN_EN_SHIFT                                                              (3U)
#define CTRL_CORE_PCS2_USB_ERR_USB_LN_EN_MASK                                                               (0x00000008U)

#define CTRL_CORE_PCS2_USB_SHORT_TIMES_SHIFT                                                                (0U)
#define CTRL_CORE_PCS2_USB_SHORT_TIMES_MASK                                                                 (0x00000001U)

#define CTRL_CORE_PCS2_RESERVED_0_SHIFT                                                                     (1U)
#define CTRL_CORE_PCS2_RESERVED_0_MASK                                                                      (0x00000006U)

#define CTRL_CORE_PCS2_RESERVED_1_SHIFT                                                                     (8U)
#define CTRL_CORE_PCS2_RESERVED_1_MASK                                                                      (0x00000100U)

#define CTRL_CORE_PCS_REVISION_USB_REVISION_SHIFT                                                           (29U)
#define CTRL_CORE_PCS_REVISION_USB_REVISION_MASK                                                            (0xe0000000U)

#define CTRL_CORE_PCS_REVISION_RESERVED_0_SHIFT                                                             (0U)
#define CTRL_CORE_PCS_REVISION_RESERVED_0_MASK                                                              (0x1fffffffU)

#define CTRL_CORE_PHY_POWER_USB_USB_PWRCTL_CLK_FREQ_SHIFT                                                   (22U)
#define CTRL_CORE_PHY_POWER_USB_USB_PWRCTL_CLK_FREQ_MASK                                                    (0xffc00000U)

#define CTRL_CORE_PHY_POWER_USB_USB_PWRCTL_CLK_CMD_SHIFT                                                    (14U)
#define CTRL_CORE_PHY_POWER_USB_USB_PWRCTL_CLK_CMD_MASK                                                     (0x003fc000U)

#define CTRL_CORE_PHY_POWER_USB_RESERVED_0_SHIFT                                                            (0U)
#define CTRL_CORE_PHY_POWER_USB_RESERVED_0_MASK                                                             (0x00003fffU)

#define CTRL_CORE_PHY_POWER_SATA_SATA_PWRCTL_CLK_FREQ_SHIFT                                                 (22U)
#define CTRL_CORE_PHY_POWER_SATA_SATA_PWRCTL_CLK_FREQ_MASK                                                  (0xffc00000U)

#define CTRL_CORE_PHY_POWER_SATA_SATA_PWRCTL_CLK_CMD_SHIFT                                                  (14U)
#define CTRL_CORE_PHY_POWER_SATA_SATA_PWRCTL_CLK_CMD_MASK                                                   (0x003fc000U)

#define CTRL_CORE_PHY_POWER_SATA_RESERVED_0_SHIFT                                                           (0U)
#define CTRL_CORE_PHY_POWER_SATA_RESERVED_0_MASK                                                            (0x00003fffU)

#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_SHIFT                                                            (30U)
#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_MASK                                                             (0xc0000000U)
#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_FORCEIDLE                                                         (1U)
#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_NOFUNC                                                            (3U)
#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_NOIDLE                                                            (0U)
#define CTRL_CORE_BANDGAP_MASK_1_SIDLEMODE_SMARTIDLE                                                         (2U)

#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_SHIFT                                                        (27U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_MASK                                                         (0x38000000U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_250MS                                                       (4U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_1MS                                                         (1U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_100MS                                                       (3U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_IMEDIAT                                                     (0U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_10MS                                                        (2U)
#define CTRL_CORE_BANDGAP_MASK_1_COUNTER_DELAY_C_500MS                                                       (5U)

#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_CORE_SHIFT                                                          (23U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_CORE_MASK                                                           (0x00800000U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_CORE_FREEZE                                                          (1U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_CORE_NO_OP                                                           (0U)

#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_GPU_SHIFT                                                           (22U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_GPU_MASK                                                            (0x00400000U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_GPU_FREEZE                                                           (1U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_GPU_NO_OP                                                            (0U)

#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_MPU_SHIFT                                                           (21U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_MPU_MASK                                                            (0x00200000U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_MPU_FREEZE                                                           (1U)
#define CTRL_CORE_BANDGAP_MASK_1_FREEZE_MPU_NO_OP                                                            (0U)

#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_CORE_SHIFT                                                           (20U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_CORE_MASK                                                            (0x00100000U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_CORE_RESET                                                            (1U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_CORE_NO_OP                                                            (0U)

#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_GPU_SHIFT                                                            (19U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_GPU_MASK                                                             (0x00080000U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_GPU_RESET                                                             (1U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_GPU_NO_OP                                                             (0U)

#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_MPU_SHIFT                                                            (18U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_MPU_MASK                                                             (0x00040000U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_MPU_RESET                                                             (1U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_MPU_NO_OP                                                             (0U)

#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_CORE_SHIFT                                                     (17U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_CORE_MASK                                                      (0x00020000U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_CORE_RESET                                                      (1U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_CORE_NO_OP                                                      (0U)

#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_GPU_SHIFT                                                      (16U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_GPU_MASK                                                       (0x00010000U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_GPU_RESET                                                       (1U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_GPU_NO_OP                                                       (0U)

#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_MPU_SHIFT                                                      (15U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_MPU_MASK                                                       (0x00008000U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_MPU_RESET                                                       (1U)
#define CTRL_CORE_BANDGAP_MASK_1_CLEAR_ACCUM_MPU_NO_OP                                                       (0U)

#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_CORE_SHIFT                                                        (5U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_CORE_MASK                                                         (0x00000020U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_CORE_UNMASKED                                                      (1U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_CORE_MASKED                                                        (0U)

#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_CORE_SHIFT                                                       (4U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_CORE_MASK                                                        (0x00000010U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_CORE_UNMASKED                                                     (1U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_CORE_MASKED                                                       (0U)

#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_GPU_SHIFT                                                         (3U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_GPU_MASK                                                          (0x00000008U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_GPU_UNMASKED                                                       (1U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_GPU_MASKED                                                         (0U)

#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_GPU_SHIFT                                                        (2U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_GPU_MASK                                                         (0x00000004U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_GPU_UNMASKED                                                      (1U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_GPU_MASKED                                                        (0U)

#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_MPU_SHIFT                                                         (1U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_MPU_MASK                                                          (0x00000002U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_MPU_UNMASKED                                                       (1U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_HOT_MPU_MASKED                                                         (0U)

#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_MPU_SHIFT                                                        (0U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_MPU_MASK                                                         (0x00000001U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_MPU_UNMASKED                                                      (1U)
#define CTRL_CORE_BANDGAP_MASK_1_MASK_COLD_MPU_MASKED                                                        (0U)

#define CTRL_CORE_BANDGAP_MASK_1_RESERVED_0_SHIFT                                                           (6U)
#define CTRL_CORE_BANDGAP_MASK_1_RESERVED_0_MASK                                                            (0x00007fc0U)

#define CTRL_CORE_BANDGAP_MASK_1_RESERVED_1_SHIFT                                                           (24U)
#define CTRL_CORE_BANDGAP_MASK_1_RESERVED_1_MASK                                                            (0x07000000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_MPU_THOLD_HOT_MPU_SHIFT                                                 (16U)
#define CTRL_CORE_BANDGAP_THRESHOLD_MPU_THOLD_HOT_MPU_MASK                                                  (0x03ff0000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_MPU_THOLD_COLD_MPU_SHIFT                                                (0U)
#define CTRL_CORE_BANDGAP_THRESHOLD_MPU_THOLD_COLD_MPU_MASK                                                 (0x000003ffU)

#define CTRL_CORE_BANDGAP_THRESHOLD_MPU_RESERVED_0_SHIFT                                                    (10U)
#define CTRL_CORE_BANDGAP_THRESHOLD_MPU_RESERVED_0_MASK                                                     (0x0000fc00U)

#define CTRL_CORE_BANDGAP_THRESHOLD_MPU_RESERVED_1_SHIFT                                                    (26U)
#define CTRL_CORE_BANDGAP_THRESHOLD_MPU_RESERVED_1_MASK                                                     (0xfc000000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_GPU_THOLD_HOT_GPU_SHIFT                                                 (16U)
#define CTRL_CORE_BANDGAP_THRESHOLD_GPU_THOLD_HOT_GPU_MASK                                                  (0x03ff0000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_GPU_THOLD_COLD_GPU_SHIFT                                                (0U)
#define CTRL_CORE_BANDGAP_THRESHOLD_GPU_THOLD_COLD_GPU_MASK                                                 (0x000003ffU)

#define CTRL_CORE_BANDGAP_THRESHOLD_GPU_RESERVED_0_SHIFT                                                    (10U)
#define CTRL_CORE_BANDGAP_THRESHOLD_GPU_RESERVED_0_MASK                                                     (0x0000fc00U)

#define CTRL_CORE_BANDGAP_THRESHOLD_GPU_RESERVED_1_SHIFT                                                    (26U)
#define CTRL_CORE_BANDGAP_THRESHOLD_GPU_RESERVED_1_MASK                                                     (0xfc000000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_CORE_THOLD_HOT_CORE_SHIFT                                               (16U)
#define CTRL_CORE_BANDGAP_THRESHOLD_CORE_THOLD_HOT_CORE_MASK                                                (0x03ff0000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_CORE_THOLD_COLD_CORE_SHIFT                                              (0U)
#define CTRL_CORE_BANDGAP_THRESHOLD_CORE_THOLD_COLD_CORE_MASK                                               (0x000003ffU)

#define CTRL_CORE_BANDGAP_THRESHOLD_CORE_RESERVED_0_SHIFT                                                   (10U)
#define CTRL_CORE_BANDGAP_THRESHOLD_CORE_RESERVED_0_MASK                                                    (0x0000fc00U)

#define CTRL_CORE_BANDGAP_THRESHOLD_CORE_RESERVED_1_SHIFT                                                   (26U)
#define CTRL_CORE_BANDGAP_THRESHOLD_CORE_RESERVED_1_MASK                                                    (0xfc000000U)

#define CTRL_CORE_BANDGAP_TSHUT_MPU_TSHUT_MUXCTRL_MPU_SHIFT                                                 (31U)
#define CTRL_CORE_BANDGAP_TSHUT_MPU_TSHUT_MUXCTRL_MPU_MASK                                                  (0x80000000U)
#define CTRL_CORE_BANDGAP_TSHUT_MPU_TSHUT_MUXCTRL_MPU_OCP                                                    (1U)
#define CTRL_CORE_BANDGAP_TSHUT_MPU_TSHUT_MUXCTRL_MPU_EFUSE                                                  (0U)

#define CTRL_CORE_BANDGAP_TSHUT_MPU_TSHUT_HOT_MPU_SHIFT                                                     (16U)
#define CTRL_CORE_BANDGAP_TSHUT_MPU_TSHUT_HOT_MPU_MASK                                                      (0x03ff0000U)

#define CTRL_CORE_BANDGAP_TSHUT_MPU_TSHUT_COLD_MPU_SHIFT                                                    (0U)
#define CTRL_CORE_BANDGAP_TSHUT_MPU_TSHUT_COLD_MPU_MASK                                                     (0x000003ffU)

#define CTRL_CORE_BANDGAP_TSHUT_MPU_RESERVED_0_SHIFT                                                        (10U)
#define CTRL_CORE_BANDGAP_TSHUT_MPU_RESERVED_0_MASK                                                         (0x0000fc00U)

#define CTRL_CORE_BANDGAP_TSHUT_MPU_RESERVED_1_SHIFT                                                        (26U)
#define CTRL_CORE_BANDGAP_TSHUT_MPU_RESERVED_1_MASK                                                         (0x7c000000U)

#define CTRL_CORE_BANDGAP_TSHUT_GPU_TSHUT_MUXCTRL_GPU_SHIFT                                                 (31U)
#define CTRL_CORE_BANDGAP_TSHUT_GPU_TSHUT_MUXCTRL_GPU_MASK                                                  (0x80000000U)
#define CTRL_CORE_BANDGAP_TSHUT_GPU_TSHUT_MUXCTRL_GPU_OCP                                                    (1U)
#define CTRL_CORE_BANDGAP_TSHUT_GPU_TSHUT_MUXCTRL_GPU_EFUSE                                                  (0U)

#define CTRL_CORE_BANDGAP_TSHUT_GPU_TSHUT_HOT_GPU_SHIFT                                                     (16U)
#define CTRL_CORE_BANDGAP_TSHUT_GPU_TSHUT_HOT_GPU_MASK                                                      (0x03ff0000U)

#define CTRL_CORE_BANDGAP_TSHUT_GPU_TSHUT_COLD_GPU_SHIFT                                                    (0U)
#define CTRL_CORE_BANDGAP_TSHUT_GPU_TSHUT_COLD_GPU_MASK                                                     (0x000003ffU)

#define CTRL_CORE_BANDGAP_TSHUT_GPU_RESERVED_0_SHIFT                                                        (10U)
#define CTRL_CORE_BANDGAP_TSHUT_GPU_RESERVED_0_MASK                                                         (0x0000fc00U)

#define CTRL_CORE_BANDGAP_TSHUT_GPU_RESERVED_1_SHIFT                                                        (26U)
#define CTRL_CORE_BANDGAP_TSHUT_GPU_RESERVED_1_MASK                                                         (0x7c000000U)

#define CTRL_CORE_BANDGAP_TSHUT_CORE_TSHUT_MUXCTRL_CORE_SHIFT                                               (31U)
#define CTRL_CORE_BANDGAP_TSHUT_CORE_TSHUT_MUXCTRL_CORE_MASK                                                (0x80000000U)
#define CTRL_CORE_BANDGAP_TSHUT_CORE_TSHUT_MUXCTRL_CORE_OCP                                                  (1U)
#define CTRL_CORE_BANDGAP_TSHUT_CORE_TSHUT_MUXCTRL_CORE_EFUSE                                                (0U)

#define CTRL_CORE_BANDGAP_TSHUT_CORE_TSHUT_HOT_CORE_SHIFT                                                   (16U)
#define CTRL_CORE_BANDGAP_TSHUT_CORE_TSHUT_HOT_CORE_MASK                                                    (0x03ff0000U)

#define CTRL_CORE_BANDGAP_TSHUT_CORE_TSHUT_COLD_CORE_SHIFT                                                  (0U)
#define CTRL_CORE_BANDGAP_TSHUT_CORE_TSHUT_COLD_CORE_MASK                                                   (0x000003ffU)

#define CTRL_CORE_BANDGAP_TSHUT_CORE_RESERVED_0_SHIFT                                                       (10U)
#define CTRL_CORE_BANDGAP_TSHUT_CORE_RESERVED_0_MASK                                                        (0x0000fc00U)

#define CTRL_CORE_BANDGAP_TSHUT_CORE_RESERVED_1_SHIFT                                                       (26U)
#define CTRL_CORE_BANDGAP_TSHUT_CORE_RESERVED_1_MASK                                                        (0x7c000000U)

#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_MPU_CUMUL_DTEMP_MPU_SHIFT                                             (0U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_MPU_CUMUL_DTEMP_MPU_MASK                                              (0xffffffffU)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_MPU_CUMUL_DTEMP_MPU_REPEAT                                             (1U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_MPU_CUMUL_DTEMP_MPU_SINGLE                                             (0U)

#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_GPU_CUMUL_DTEMP_GPU_SHIFT                                             (0U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_GPU_CUMUL_DTEMP_GPU_MASK                                              (0xffffffffU)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_GPU_CUMUL_DTEMP_GPU_REPEAT                                             (1U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_GPU_CUMUL_DTEMP_GPU_SINGLE                                             (0U)

#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_CORE_CUMUL_DTEMP_CORE_SHIFT                                           (0U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_CORE_CUMUL_DTEMP_CORE_MASK                                            (0xffffffffU)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_CORE_CUMUL_DTEMP_CORE_REPEAT                                           (1U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_CORE_CUMUL_DTEMP_CORE_SINGLE                                           (0U)

#define CTRL_CORE_BANDGAP_STATUS_1_ALERT_SHIFT                                                              (31U)
#define CTRL_CORE_BANDGAP_STATUS_1_ALERT_MASK                                                               (0x80000000U)

#define CTRL_CORE_BANDGAP_STATUS_1_HOT_CORE_SHIFT                                                           (5U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_CORE_MASK                                                            (0x00000020U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_CORE_EVENT                                                            (1U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_CORE_NOEVENT                                                          (0U)

#define CTRL_CORE_BANDGAP_STATUS_1_COLD_CORE_SHIFT                                                          (4U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_CORE_MASK                                                           (0x00000010U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_CORE_EVENT                                                           (1U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_CORE_NOEVENT                                                         (0U)

#define CTRL_CORE_BANDGAP_STATUS_1_HOT_GPU_SHIFT                                                            (3U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_GPU_MASK                                                             (0x00000008U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_GPU_EVENT                                                             (1U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_GPU_NOEVENT                                                           (0U)

#define CTRL_CORE_BANDGAP_STATUS_1_COLD_GPU_SHIFT                                                           (2U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_GPU_MASK                                                            (0x00000004U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_GPU_EVENT                                                            (1U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_GPU_NOEVENT                                                          (0U)

#define CTRL_CORE_BANDGAP_STATUS_1_HOT_MPU_SHIFT                                                            (1U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_MPU_MASK                                                             (0x00000002U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_MPU_EVENT                                                             (1U)
#define CTRL_CORE_BANDGAP_STATUS_1_HOT_MPU_NOEVENT                                                           (0U)

#define CTRL_CORE_BANDGAP_STATUS_1_COLD_MPU_SHIFT                                                           (0U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_MPU_MASK                                                            (0x00000001U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_MPU_EVENT                                                            (1U)
#define CTRL_CORE_BANDGAP_STATUS_1_COLD_MPU_NOEVENT                                                          (0U)

#define CTRL_CORE_BANDGAP_STATUS_1_RESERVED_0_SHIFT                                                         (6U)
#define CTRL_CORE_BANDGAP_STATUS_1_RESERVED_0_MASK                                                          (0x7fffffc0U)

#define CTRL_CORE_SATA_EXT_MODE_SATA_EXTENDED_MODE_SHIFT                                                    (0U)
#define CTRL_CORE_SATA_EXT_MODE_SATA_EXTENDED_MODE_MASK                                                     (0x00000001U)
#define CTRL_CORE_SATA_EXT_MODE_SATA_EXTENDED_MODE_EXTENDED                                                  (1U)
#define CTRL_CORE_SATA_EXT_MODE_SATA_EXTENDED_MODE_NO_EX                                                     (0U)

#define CTRL_CORE_SATA_EXT_MODE_RESERVED_0_SHIFT                                                            (1U)
#define CTRL_CORE_SATA_EXT_MODE_RESERVED_0_MASK                                                             (0xfffffffeU)

#define CTRL_CORE_DTEMP_MPU_0_DTEMP_TAG_MPU_0_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_MPU_0_DTEMP_TAG_MPU_0_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_MPU_0_DTEMP_TEMPERATURE_MPU_0_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_MPU_0_DTEMP_TEMPERATURE_MPU_0_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_MPU_1_DTEMP_TAG_MPU_1_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_MPU_1_DTEMP_TAG_MPU_1_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_MPU_1_DTEMP_TEMPERATURE_MPU_1_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_MPU_1_DTEMP_TEMPERATURE_MPU_1_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_MPU_2_DTEMP_TAG_MPU_2_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_MPU_2_DTEMP_TAG_MPU_2_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_MPU_2_DTEMP_TEMPERATURE_MPU_2_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_MPU_2_DTEMP_TEMPERATURE_MPU_2_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_MPU_3_DTEMP_TAG_MPU_3_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_MPU_3_DTEMP_TAG_MPU_3_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_MPU_3_DTEMP_TEMPERATURE_MPU_3_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_MPU_3_DTEMP_TEMPERATURE_MPU_3_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_MPU_4_DTEMP_TAG_MPU_4_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_MPU_4_DTEMP_TAG_MPU_4_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_MPU_4_DTEMP_TEMPERATURE_MPU_4_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_MPU_4_DTEMP_TEMPERATURE_MPU_4_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_GPU_0_DTEMP_TAG_GPU_0_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_GPU_0_DTEMP_TAG_GPU_0_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_GPU_0_DTEMP_TEMPERATURE_GPU_0_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_GPU_0_DTEMP_TEMPERATURE_GPU_0_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_GPU_1_DTEMP_TAG_GPU_1_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_GPU_1_DTEMP_TAG_GPU_1_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_GPU_1_DTEMP_TEMPERATURE_GPU_1_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_GPU_1_DTEMP_TEMPERATURE_GPU_1_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_GPU_2_DTEMP_TAG_GPU_2_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_GPU_2_DTEMP_TAG_GPU_2_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_GPU_2_DTEMP_TEMPERATURE_GPU_2_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_GPU_2_DTEMP_TEMPERATURE_GPU_2_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_GPU_3_DTEMP_TAG_GPU_3_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_GPU_3_DTEMP_TAG_GPU_3_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_GPU_3_DTEMP_TEMPERATURE_GPU_3_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_GPU_3_DTEMP_TEMPERATURE_GPU_3_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_GPU_4_DTEMP_TAG_GPU_4_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_GPU_4_DTEMP_TAG_GPU_4_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_GPU_4_DTEMP_TEMPERATURE_GPU_4_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_GPU_4_DTEMP_TEMPERATURE_GPU_4_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_CORE_0_DTEMP_TAG_CORE_0_SHIFT                                                       (10U)
#define CTRL_CORE_DTEMP_CORE_0_DTEMP_TAG_CORE_0_MASK                                                        (0xfffffc00U)

#define CTRL_CORE_DTEMP_CORE_0_DTEMP_TEMPERATURE_CORE_0_SHIFT                                               (0U)
#define CTRL_CORE_DTEMP_CORE_0_DTEMP_TEMPERATURE_CORE_0_MASK                                                (0x000003ffU)

#define CTRL_CORE_DTEMP_CORE_1_DTEMP_TAG_CORE_1_SHIFT                                                       (10U)
#define CTRL_CORE_DTEMP_CORE_1_DTEMP_TAG_CORE_1_MASK                                                        (0xfffffc00U)

#define CTRL_CORE_DTEMP_CORE_1_DTEMP_TEMPERATURE_CORE_1_SHIFT                                               (0U)
#define CTRL_CORE_DTEMP_CORE_1_DTEMP_TEMPERATURE_CORE_1_MASK                                                (0x000003ffU)

#define CTRL_CORE_DTEMP_CORE_2_DTEMP_TAG_CORE_2_SHIFT                                                       (10U)
#define CTRL_CORE_DTEMP_CORE_2_DTEMP_TAG_CORE_2_MASK                                                        (0xfffffc00U)

#define CTRL_CORE_DTEMP_CORE_2_DTEMP_TEMPERATURE_CORE_2_SHIFT                                               (0U)
#define CTRL_CORE_DTEMP_CORE_2_DTEMP_TEMPERATURE_CORE_2_MASK                                                (0x000003ffU)

#define CTRL_CORE_DTEMP_CORE_3_DTEMP_TAG_CORE_3_SHIFT                                                       (10U)
#define CTRL_CORE_DTEMP_CORE_3_DTEMP_TAG_CORE_3_MASK                                                        (0xfffffc00U)

#define CTRL_CORE_DTEMP_CORE_3_DTEMP_TEMPERATURE_CORE_3_SHIFT                                               (0U)
#define CTRL_CORE_DTEMP_CORE_3_DTEMP_TEMPERATURE_CORE_3_MASK                                                (0x000003ffU)

#define CTRL_CORE_DTEMP_CORE_4_DTEMP_TAG_CORE_4_SHIFT                                                       (10U)
#define CTRL_CORE_DTEMP_CORE_4_DTEMP_TAG_CORE_4_MASK                                                        (0xfffffc00U)

#define CTRL_CORE_DTEMP_CORE_4_DTEMP_TEMPERATURE_CORE_4_SHIFT                                               (0U)
#define CTRL_CORE_DTEMP_CORE_4_DTEMP_TEMPERATURE_CORE_4_MASK                                                (0x000003ffU)

#define CTRL_CORE_SMA_SW_0_SATA_PLL_SOFT_RESET_SHIFT                                                        (18U)
#define CTRL_CORE_SMA_SW_0_SATA_PLL_SOFT_RESET_MASK                                                         (0x00040000U)

#define CTRL_CORE_SMA_SW_0_RESERVED0_SHIFT                                                                  (0U)
#define CTRL_CORE_SMA_SW_0_RESERVED0_MASK                                                                   (0x0003ffffU)

#define CTRL_CORE_SMA_SW_0_RESERVED1_SHIFT                                                                  (19U)
#define CTRL_CORE_SMA_SW_0_RESERVED1_MASK                                                                   (0xfff80000U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC1_EDMA_FW_ERROR_SHIFT                                             (26U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC1_EDMA_FW_ERROR_MASK                                              (0x04000000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC1_EDMA_FW_ERROR_EDMA_TC1_FW_ERROR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC1_EDMA_FW_ERROR_NO_EDMA_TC1_FW_ERROR                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_QSPI_FW_ERROR_SHIFT                                                 (22U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_QSPI_FW_ERROR_MASK                                                  (0x00400000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_QSPI_FW_ERROR_QSPI_FW_ERROR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_QSPI_FW_ERROR_NO_QSPI_FW_ERROR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TPCC_EDMA_FW_ERROR_SHIFT                                            (17U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TPCC_EDMA_FW_ERROR_MASK                                             (0x00020000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TPCC_EDMA_FW_ERROR_EDMA_TPCC_FW_ERROR                                (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TPCC_EDMA_FW_ERROR_NO_EDMA_TPCC_FW_ERROR                             (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC0_EDMA_FW_ERROR_SHIFT                                             (16U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC0_EDMA_FW_ERROR_MASK                                              (0x00010000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC0_EDMA_FW_ERROR_EDMA_TC0_FW_ERROR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_TC0_EDMA_FW_ERROR_NO_EDMA_TC0_FW_ERROR                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP3_FW_ERROR_SHIFT                                               (13U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP3_FW_ERROR_MASK                                                (0x00002000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP3_FW_ERROR_MCASP3_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP3_FW_ERROR_NO_MCASP3_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP2_FW_ERROR_SHIFT                                               (12U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP2_FW_ERROR_MASK                                                (0x00001000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP2_FW_ERROR_MCASP2_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP2_FW_ERROR_NO_MCASP2_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP1_FW_ERROR_SHIFT                                               (11U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP1_FW_ERROR_MASK                                                (0x00000800U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP1_FW_ERROR_MCASP1_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_MCASP1_FW_ERROR_NO_MCASP1_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_VCP2_FW_ERROR_SHIFT                                                 (10U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_VCP2_FW_ERROR_MASK                                                  (0x00000400U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_VCP2_FW_ERROR_VCP2_FW_ERROR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_VCP2_FW_ERROR_NO_VCP2_FW_ERROR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_VCP1_FW_ERROR_SHIFT                                                 (9U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_VCP1_FW_ERROR_MASK                                                  (0x00000200U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_VCP1_FW_ERROR_VCP1_FW_ERROR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_VCP1_FW_ERROR_NO_VCP1_FW_ERROR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS2_FW_ERROR_SHIFT                                              (8U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS2_FW_ERROR_MASK                                               (0x00000100U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS2_FW_ERROR_PCIESS2_FW_ERROR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS2_FW_ERROR_NO_PCIESS2_FW_ERROR                                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS1_FW_ERROR_SHIFT                                              (7U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS1_FW_ERROR_MASK                                               (0x00000080U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS1_FW_ERROR_PCIESS1_FW_ERROR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_PCIESS1_FW_ERROR_NO_PCIESS1_FW_ERROR                                 (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_IPU2_FW_ERROR_SHIFT                                                 (6U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_IPU2_FW_ERROR_MASK                                                  (0x00000040U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_IPU2_FW_ERROR_IPU2_TARGET_FW_ERR                                     (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_IPU2_FW_ERROR_NO_IPU2_TARGET_FW_ERR                                  (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_SHIFT                                           (5U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_MASK                                            (0x00000020U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_L4PERIPH3_INIT_FW_ERR                            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH3_FW_ERROR_NO_L4PERIPH3_INIT_FW_ERR                         (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_SHIFT                                           (4U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_MASK                                            (0x00000010U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_L4PERIPH2_INIT_FW_ERR                            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L4_PERIPH2_FW_ERROR_NO_L4PERIPH2_INIT_FW_ERR                         (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L3RAM3_FW_ERROR_SHIFT                                               (3U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L3RAM3_FW_ERROR_MASK                                                (0x00000008U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L3RAM3_FW_ERROR_L3RAM3_INIT_FW_ERR                                   (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L3RAM3_FW_ERROR_NO_L3RAM3_INIT_FW_ERR                                (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L3RAM2_FW_ERROR_SHIFT                                               (2U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L3RAM2_FW_ERROR_MASK                                                (0x00000004U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L3RAM2_FW_ERROR_L3RAM2_TARGET_FW_ERR                                 (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_L3RAM2_FW_ERROR_NO_L3RAM2_TARGET_FW_ERR                              (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP2_FW_ERROR_SHIFT                                                 (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP2_FW_ERROR_MASK                                                  (0x00000002U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP2_FW_ERROR_DSP2_FW_ERROR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP2_FW_ERROR_NO_DSP2_FW_ERROR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR_SHIFT                                                 (0U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR_MASK                                                  (0x00000001U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR_DSP1_FW_ERROR                                          (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_DSP1_FW_ERROR_NO_DSP1_FW_ERROR                                       (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED_0_SHIFT                                                    (27U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED_0_MASK                                                     (0xf8000000U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED1_SHIFT                                                     (14U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED1_MASK                                                      (0x0000c000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED1_AES1_FW_ERROR                                              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED1_NO_AES1_FW_ERROR                                           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED2_SHIFT                                                     (18U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED2_MASK                                                      (0x003c0000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED2_SHA2MD5_1_FW_ERROR                                         (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED2_NO_SHA2MD5_1_FW_ERROR                                      (0U)

#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED3_SHIFT                                                     (23U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED3_MASK                                                      (0x03800000U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED3_SPARE_TSC_ADC_FW_ERROR                                     (1U)
#define CTRL_CORE_SEC_ERR_STATUS_FUNC_2_RESERVED3_NO_SPARE_TSC_ADC_FW_ERROR                                  (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC1_EDMA_DBGFW_ERROR_SHIFT                                         (26U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC1_EDMA_DBGFW_ERROR_MASK                                          (0x04000000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC1_EDMA_DBGFW_ERROR_EDMA_TC1_FW_ERROR                              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC1_EDMA_DBGFW_ERROR_NO_EDMA_TC1_FW_ERROR                           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_QSPI_DBGFW_ERROR_SHIFT                                             (22U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_QSPI_DBGFW_ERROR_MASK                                              (0x00400000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_QSPI_DBGFW_ERROR_QSPI_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_QSPI_DBGFW_ERROR_NO_QSPI_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TPCC_EDMA_DBGFW_ERROR_SHIFT                                        (17U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TPCC_EDMA_DBGFW_ERROR_MASK                                         (0x00020000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TPCC_EDMA_DBGFW_ERROR_EDMA_TPCC_FW_ERROR                            (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TPCC_EDMA_DBGFW_ERROR_NO_EDMA_TPCC_FW_ERROR                         (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC0_EDMA_DBGFW_ERROR_SHIFT                                         (16U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC0_EDMA_DBGFW_ERROR_MASK                                          (0x00010000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC0_EDMA_DBGFW_ERROR_EDMA_TC0_FW_ERROR                              (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_TC0_EDMA_DBGFW_ERROR_NO_EDMA_TC0_FW_ERROR                           (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP3_DBGFW_ERROR_SHIFT                                           (13U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP3_DBGFW_ERROR_MASK                                            (0x00002000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP3_DBGFW_ERROR_MCASP3_FW_ERROR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP3_DBGFW_ERROR_NO_MCASP3_FW_ERROR                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP2_DBGFW_ERROR_SHIFT                                           (12U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP2_DBGFW_ERROR_MASK                                            (0x00001000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP2_DBGFW_ERROR_MCASP2_FW_ERROR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP2_DBGFW_ERROR_NO_MCASP2_FW_ERROR                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP1_DBGFW_ERROR_SHIFT                                           (11U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP1_DBGFW_ERROR_MASK                                            (0x00000800U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP1_DBGFW_ERROR_MCASP1_FW_ERROR                                  (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_MCASP1_DBGFW_ERROR_NO_MCASP1_FW_ERROR                               (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_VCP2_DBGFW_ERROR_SHIFT                                             (10U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_VCP2_DBGFW_ERROR_MASK                                              (0x00000400U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_VCP2_DBGFW_ERROR_VCP2_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_VCP2_DBGFW_ERROR_NO_VCP2_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_VCP1_DBGFW_ERROR_SHIFT                                             (9U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_VCP1_DBGFW_ERROR_MASK                                              (0x00000200U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_VCP1_DBGFW_ERROR_VCP1_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_VCP1_DBGFW_ERROR_NO_VCP1_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_PCIESS2_DBGFW_ERROR_SHIFT                                          (8U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_PCIESS2_DBGFW_ERROR_MASK                                           (0x00000100U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_PCIESS2_DBGFW_ERROR_PCIESS2_FW_ERROR                                (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_PCIESS2_DBGFW_ERROR_NO_PCIESS2_FW_ERROR                             (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_PCIESS1_DBGFW_ERROR_SHIFT                                          (7U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_PCIESS1_DBGFW_ERROR_MASK                                           (0x00000080U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_PCIESS1_DBGFW_ERROR_PCIESS1_FW_ERROR                                (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_PCIESS1_DBGFW_ERROR_NO_PCIESS1_FW_ERROR                             (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_IPU2_DBGFW_ERROR_SHIFT                                             (6U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_IPU2_DBGFW_ERROR_MASK                                              (0x00000040U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_IPU2_DBGFW_ERROR_IPU2_FW_ERR                                        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_IPU2_DBGFW_ERROR_NO_IPU2_FW_ERR                                     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH3_DBGFW_ERROR_SHIFT                                       (5U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH3_DBGFW_ERROR_MASK                                        (0x00000020U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH3_DBGFW_ERROR_L4PERIPH3_INIT_FW_ERR                        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH3_DBGFW_ERROR_NO_L4PERIPH3_INIT_FW_ERR                     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH2_DBGFW_ERROR_SHIFT                                       (4U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH2_DBGFW_ERROR_MASK                                        (0x00000010U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH2_DBGFW_ERROR_L4PERIPH2_INIT_FW_ERR                        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L4_PERIPH2_DBGFW_ERROR_NO_L4PERIPH2_INIT_FW_ERR                     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L3RAM3_DBGFW_ERROR_SHIFT                                           (3U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L3RAM3_DBGFW_ERROR_MASK                                            (0x00000008U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L3RAM3_DBGFW_ERROR_L3RAM3_INIT_FW_ERR                               (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L3RAM3_DBGFW_ERROR_NO_L3RAM3_INIT_FW_ERR                            (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L3RAM2_DBGFW_ERROR_SHIFT                                           (2U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L3RAM2_DBGFW_ERROR_MASK                                            (0x00000004U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L3RAM2_DBGFW_ERROR_L3RAM2_TARGET_FW_ERR                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_L3RAM2_DBGFW_ERROR_NO_L3RAM2_TARGET_FW_ERR                          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP2_DBGFW_ERROR_SHIFT                                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP2_DBGFW_ERROR_MASK                                              (0x00000002U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP2_DBGFW_ERROR_DSP2_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP2_DBGFW_ERROR_NO_DSP2_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP1_DBGFW_ERROR_SHIFT                                             (0U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP1_DBGFW_ERROR_MASK                                              (0x00000001U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP1_DBGFW_ERROR_DSP1_FW_ERROR                                      (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_DSP1_DBGFW_ERROR_NO_DSP1_FW_ERROR                                   (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED_0_SHIFT                                                   (27U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED_0_MASK                                                    (0xf8000000U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED1_SHIFT                                                    (14U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED1_MASK                                                     (0x0000c000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED1_AES1_FW_ERROR                                             (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED1_NO_AES1_FW_ERROR                                          (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED2_SHIFT                                                    (18U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED2_MASK                                                     (0x003c0000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED2_SHA2MD5_1_FW_ERROR                                        (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED2_NO_SHA2MD5_1_FW_ERROR                                     (0U)

#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED3_SHIFT                                                    (23U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED3_MASK                                                     (0x03800000U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED3_SPARE_TSC_ADC_FW_ERROR                                    (1U)
#define CTRL_CORE_SEC_ERR_STATUS_DEBUG_2_RESERVED3_NO_SPARE_TSC_ADC_FW_ERROR                                 (0U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_MPU_EMIF_PRIORITY_SHIFT                                         (28U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_MPU_EMIF_PRIORITY_MASK                                          (0x70000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_MPU_EMIF_PRIORITY_HIGHESTPRIORITY                                (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_MPU_EMIF_PRIORITY_LOWESTPRIORITY                                 (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_MDMA_EMIF_PRIORITY_SHIFT                                   (16U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_MDMA_EMIF_PRIORITY_MASK                                    (0x00070000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_MDMA_EMIF_PRIORITY_HIGHESTPRIORITY                          (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_MDMA_EMIF_PRIORITY_LOWESTPRIORITY                           (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_CFG_EMIF_PRIORITY_SHIFT                                    (12U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_CFG_EMIF_PRIORITY_MASK                                     (0x00007000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_CFG_EMIF_PRIORITY_HIGHESTPRIORITY                           (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_CFG_EMIF_PRIORITY_LOWESTPRIORITY                            (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_EDMA_EMIF_PRIORITY_SHIFT                                   (8U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_EDMA_EMIF_PRIORITY_MASK                                    (0x00000700U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_EDMA_EMIF_PRIORITY_HIGHESTPRIORITY                          (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP1_EDMA_EMIF_PRIORITY_LOWESTPRIORITY                           (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_EDMA_EMIF_PRIORITY_SHIFT                                   (4U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_EDMA_EMIF_PRIORITY_MASK                                    (0x00000070U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_EDMA_EMIF_PRIORITY_HIGHESTPRIORITY                          (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_EDMA_EMIF_PRIORITY_LOWESTPRIORITY                           (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_CFG_EMIF_PRIORITY_SHIFT                                    (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_CFG_EMIF_PRIORITY_MASK                                     (0x00000007U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_CFG_EMIF_PRIORITY_HIGHESTPRIORITY                           (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_DSP2_CFG_EMIF_PRIORITY_LOWESTPRIORITY                            (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED0_SHIFT                                                 (31U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED0_MASK                                                  (0x80000000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED2_SHIFT                                                 (15U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED2_MASK                                                  (0x00008000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED3_SHIFT                                                 (11U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED3_MASK                                                  (0x00000800U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED_SHIFT                                                  (19U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED_MASK                                                   (0x0ff80000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED_HIGHESTPRIORITY                                         (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED_LOWESTPRIORITY                                          (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED4_SHIFT                                                 (7U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED4_MASK                                                  (0x00000080U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED5_SHIFT                                                 (3U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_1_RESERVED5_MASK                                                  (0x00000008U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_DSP2_MDMA_EMIF_PRIORITY_SHIFT                                   (28U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_DSP2_MDMA_EMIF_PRIORITY_MASK                                    (0x70000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_DSP2_MDMA_EMIF_PRIORITY_HIGHESTPRIORITY                          (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_DSP2_MDMA_EMIF_PRIORITY_LOWESTPRIORITY                           (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_IVA_ICONT1_EMIF_PRIORITY_SHIFT                                  (24U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_IVA_ICONT1_EMIF_PRIORITY_MASK                                   (0x07000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_IVA_ICONT1_EMIF_PRIORITY_HIGHESTPRIORITY                         (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_IVA_ICONT1_EMIF_PRIORITY_LOWESTPRIORITY                          (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE1_TC0_EMIF_PRIORITY_SHIFT                                    (16U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE1_TC0_EMIF_PRIORITY_MASK                                     (0x00070000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE1_TC0_EMIF_PRIORITY_HIGHESTPRIORITY                           (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE1_TC0_EMIF_PRIORITY_LOWESTPRIORITY                            (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE2_TC0_EMIF_PRIORITY_SHIFT                                    (12U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE2_TC0_EMIF_PRIORITY_MASK                                     (0x00007000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE2_TC0_EMIF_PRIORITY_HIGHESTPRIORITY                           (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_EVE2_TC0_EMIF_PRIORITY_LOWESTPRIORITY                            (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_RESERVED0_SHIFT                                                 (31U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_RESERVED0_MASK                                                  (0x80000000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_RESERVED1_SHIFT                                                 (27U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_RESERVED1_MASK                                                  (0x08000000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_RESERVED2_SHIFT                                                 (19U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_RESERVED2_MASK                                                  (0x00f80000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_RESERVED3_SHIFT                                                 (15U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_RESERVED3_MASK                                                  (0x00008000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_RESERVED4_SHIFT                                                 (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_2_RESERVED4_MASK                                                  (0x00000fffU)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU1_EMIF_PRIORITY_SHIFT                                        (16U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU1_EMIF_PRIORITY_MASK                                         (0x00070000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU1_EMIF_PRIORITY_HIGHESTPRIORITY                               (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU1_EMIF_PRIORITY_LOWESTPRIORITY                                (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU2_EMIF_PRIORITY_SHIFT                                        (12U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU2_EMIF_PRIORITY_MASK                                         (0x00007000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU2_EMIF_PRIORITY_HIGHESTPRIORITY                               (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_IPU2_EMIF_PRIORITY_LOWESTPRIORITY                                (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_DMA_SYSTEM_EMIF_PRIORITY_SHIFT                                  (8U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_DMA_SYSTEM_EMIF_PRIORITY_MASK                                   (0x00000700U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_DMA_SYSTEM_EMIF_PRIORITY_HIGHESTPRIORITY                         (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_DMA_SYSTEM_EMIF_PRIORITY_LOWESTPRIORITY                          (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_EDMA_TC0_EMIF_PRIORITY_SHIFT                                    (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_EDMA_TC0_EMIF_PRIORITY_MASK                                     (0x00000007U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_EDMA_TC0_EMIF_PRIORITY_HIGHESTPRIORITY                           (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_EDMA_TC0_EMIF_PRIORITY_LOWESTPRIORITY                            (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_RESERVED0_SHIFT                                                 (3U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_RESERVED0_MASK                                                  (0x000000f8U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_RESERVED1_SHIFT                                                 (11U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_RESERVED1_MASK                                                  (0x00000800U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_RESERVED2_SHIFT                                                 (15U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_RESERVED2_MASK                                                  (0x00008000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_RESERVED3_SHIFT                                                 (19U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_3_RESERVED3_MASK                                                  (0xfff80000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_EDMA_TC1_EMIF_PRIORITY_SHIFT                                    (28U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_EDMA_TC1_EMIF_PRIORITY_MASK                                     (0x70000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_EDMA_TC1_EMIF_PRIORITY_HIGHESTPRIORITY                           (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_EDMA_TC1_EMIF_PRIORITY_LOWESTPRIORITY                            (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_DSS_EMIF_PRIORITY_SHIFT                                         (24U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_DSS_EMIF_PRIORITY_MASK                                          (0x07000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_DSS_EMIF_PRIORITY_HIGHESTPRIORITY                                (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_DSS_EMIF_PRIORITY_LOWESTPRIORITY                                 (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_MLB_MMU1_EMIF_PRIORITY_SHIFT                                    (20U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_MLB_MMU1_EMIF_PRIORITY_MASK                                     (0x00700000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_MLB_MMU1_EMIF_PRIORITY_HIGHESTPRIORITY                           (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_MLB_MMU1_EMIF_PRIORITY_LOWESTPRIORITY                            (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_PCIESS1_EMIF_PRIORITY_SHIFT                                     (16U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_PCIESS1_EMIF_PRIORITY_MASK                                      (0x00070000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_PCIESS1_EMIF_PRIORITY_HIGHESTPRIORITY                            (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_PCIESS1_EMIF_PRIORITY_LOWESTPRIORITY                             (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_PCIESS2_EMIF_PRIORITY_SHIFT                                     (12U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_PCIESS2_EMIF_PRIORITY_MASK                                      (0x00007000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_PCIESS2_EMIF_PRIORITY_HIGHESTPRIORITY                            (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_PCIESS2_EMIF_PRIORITY_LOWESTPRIORITY                             (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP1_P1_P2_EMIF_PRIORITY_SHIFT                                  (8U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP1_P1_P2_EMIF_PRIORITY_MASK                                   (0x00000700U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP1_P1_P2_EMIF_PRIORITY_HIGHESTPRIORITY                         (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP1_P1_P2_EMIF_PRIORITY_LOWESTPRIORITY                          (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP2_P1_P2_EMIF_PRIORITY_SHIFT                                  (4U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP2_P1_P2_EMIF_PRIORITY_MASK                                   (0x00000070U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP2_P1_P2_EMIF_PRIORITY_HIGHESTPRIORITY                         (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP2_P1_P2_EMIF_PRIORITY_LOWESTPRIORITY                          (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP3_P1_P2_EMIF_PRIORITY_SHIFT                                  (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP3_P1_P2_EMIF_PRIORITY_MASK                                   (0x00000007U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP3_P1_P2_EMIF_PRIORITY_HIGHESTPRIORITY                         (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_VIP3_P1_P2_EMIF_PRIORITY_LOWESTPRIORITY                          (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED0_SHIFT                                                 (3U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED0_MASK                                                  (0x00000008U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED1_SHIFT                                                 (7U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED1_MASK                                                  (0x00000080U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED2_SHIFT                                                 (11U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED2_MASK                                                  (0x00000800U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED3_SHIFT                                                 (15U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED3_MASK                                                  (0x00008000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED4_SHIFT                                                 (19U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED4_MASK                                                  (0x00080000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED5_SHIFT                                                 (23U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED5_MASK                                                  (0x00800000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED6_SHIFT                                                 (27U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED6_MASK                                                  (0x08000000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED7_SHIFT                                                 (31U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_4_RESERVED7_MASK                                                  (0x80000000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_VPE_P1_P2_EMIF_PRIORITY_SHIFT                                   (28U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_VPE_P1_P2_EMIF_PRIORITY_MASK                                    (0x70000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_VPE_P1_P2_EMIF_PRIORITY_HIGHESTPRIORITY                          (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_VPE_P1_P2_EMIF_PRIORITY_LOWESTPRIORITY                           (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_MMC1_GPU_P1_EMIF_PRIORITY_SHIFT                                 (24U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_MMC1_GPU_P1_EMIF_PRIORITY_MASK                                  (0x07000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_MMC1_GPU_P1_EMIF_PRIORITY_HIGHESTPRIORITY                        (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_MMC1_GPU_P1_EMIF_PRIORITY_LOWESTPRIORITY                         (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_MMC2_GPU_P2_EMIF_PRIORITY_SHIFT                                 (20U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_MMC2_GPU_P2_EMIF_PRIORITY_MASK                                  (0x00700000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_MMC2_GPU_P2_EMIF_PRIORITY_HIGHESTPRIORITY                        (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_MMC2_GPU_P2_EMIF_PRIORITY_LOWESTPRIORITY                         (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_BB2D_P1_P2_EMIF_PRIORITY_SHIFT                                  (16U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_BB2D_P1_P2_EMIF_PRIORITY_MASK                                   (0x00070000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_BB2D_P1_P2_EMIF_PRIORITY_HIGHESTPRIORITY                         (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_BB2D_P1_P2_EMIF_PRIORITY_LOWESTPRIORITY                          (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_GMAC_SW_EMIF_PRIORITY_SHIFT                                     (12U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_GMAC_SW_EMIF_PRIORITY_MASK                                      (0x00007000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_GMAC_SW_EMIF_PRIORITY_HIGHESTPRIORITY                            (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_GMAC_SW_EMIF_PRIORITY_LOWESTPRIORITY                             (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB1_EMIF_PRIORITY_SHIFT                                        (8U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB1_EMIF_PRIORITY_MASK                                         (0x00000700U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB1_EMIF_PRIORITY_HIGHESTPRIORITY                               (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB1_EMIF_PRIORITY_LOWESTPRIORITY                                (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB2_EMIF_PRIORITY_SHIFT                                        (4U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB2_EMIF_PRIORITY_MASK                                         (0x00000070U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB2_EMIF_PRIORITY_HIGHESTPRIORITY                               (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB2_EMIF_PRIORITY_LOWESTPRIORITY                                (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB3_EMIF_PRIORITY_SHIFT                                        (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB3_EMIF_PRIORITY_MASK                                         (0x00000007U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB3_EMIF_PRIORITY_HIGHESTPRIORITY                               (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_USB3_EMIF_PRIORITY_LOWESTPRIORITY                                (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_0_SHIFT                                                (3U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_0_MASK                                                 (0x00000008U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_1_SHIFT                                                (7U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_1_MASK                                                 (0x00000080U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_2_SHIFT                                                (11U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_2_MASK                                                 (0x00000800U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_3_SHIFT                                                (15U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_3_MASK                                                 (0x00008000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_4_SHIFT                                                (19U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_4_MASK                                                 (0x00080000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_5_SHIFT                                                (23U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_5_MASK                                                 (0x00800000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_6_SHIFT                                                (27U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_6_MASK                                                 (0x08000000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_7_SHIFT                                                (31U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_5_RESERVED_7_MASK                                                 (0x80000000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_USB4_EMIF_PRIORITY_SHIFT                                        (28U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_USB4_EMIF_PRIORITY_MASK                                         (0x70000000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_USB4_EMIF_PRIORITY_HIGHESTPRIORITY                               (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_USB4_EMIF_PRIORITY_LOWESTPRIORITY                                (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_SATA_EMIF_PRIORITY_SHIFT                                        (12U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_SATA_EMIF_PRIORITY_MASK                                         (0x00007000U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_SATA_EMIF_PRIORITY_HIGHESTPRIORITY                               (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_SATA_EMIF_PRIORITY_LOWESTPRIORITY                                (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE1_TC1_EMIF_PRIORITY_SHIFT                                    (8U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE1_TC1_EMIF_PRIORITY_MASK                                     (0x00000700U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE1_TC1_EMIF_PRIORITY_HIGHESTPRIORITY                           (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE1_TC1_EMIF_PRIORITY_LOWESTPRIORITY                            (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE2_TC1_EMIF_PRIORITY_SHIFT                                    (4U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE2_TC1_EMIF_PRIORITY_MASK                                     (0x00000070U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE2_TC1_EMIF_PRIORITY_HIGHESTPRIORITY                           (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_EVE2_TC1_EMIF_PRIORITY_LOWESTPRIORITY                            (7U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_RESERVED0_SHIFT                                                 (0U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_RESERVED0_MASK                                                  (0x00000007U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_RESERVED1_SHIFT                                                 (7U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_RESERVED1_MASK                                                  (0x00000080U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_RESERVED2_SHIFT                                                 (11U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_RESERVED2_MASK                                                  (0x00000800U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_RESERVED3_SHIFT                                                 (15U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_RESERVED3_MASK                                                  (0x0fff8000U)

#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_RESERVED4_SHIFT                                                 (31U)
#define CTRL_CORE_EMIF_INITIATOR_PRIORITY_6_RESERVED4_MASK                                                  (0x80000000U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_MPU_L3_PRESSURE_SHIFT                                             (26U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_MPU_L3_PRESSURE_MASK                                              (0x0c000000U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_MPU_L3_PRESSURE_LOWEST                                             (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_MPU_L3_PRESSURE_HIGHEST                                            (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP1_CFG_L3_PRESSURE_SHIFT                                        (17U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP1_CFG_L3_PRESSURE_MASK                                         (0x00060000U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP1_CFG_L3_PRESSURE_LOWEST                                        (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP1_CFG_L3_PRESSURE_HIGHEST                                       (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP2_CFG_L3_PRESSURE_SHIFT                                        (9U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP2_CFG_L3_PRESSURE_MASK                                         (0x00000600U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP2_CFG_L3_PRESSURE_LOWEST                                        (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_DSP2_CFG_L3_PRESSURE_HIGHEST                                       (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_RESERVED0_SHIFT                                                   (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_RESERVED0_MASK                                                    (0x000001ffU)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_RESERVED1_SHIFT                                                   (11U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_RESERVED1_MASK                                                    (0x0001f800U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_RESERVED2_SHIFT                                                   (19U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_RESERVED2_MASK                                                    (0x03f80000U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_RESERVED3_SHIFT                                                   (28U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_1_RESERVED3_MASK                                                    (0xf0000000U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_IPU1_L3_PRESSURE_SHIFT                                            (12U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_IPU1_L3_PRESSURE_MASK                                             (0x00003000U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_IPU1_L3_PRESSURE_LOWEST                                            (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_IPU1_L3_PRESSURE_HIGHEST                                           (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_IPU2_L3_PRESSURE_SHIFT                                            (9U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_IPU2_L3_PRESSURE_MASK                                             (0x00000600U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_IPU2_L3_PRESSURE_LOWEST                                            (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_IPU2_L3_PRESSURE_HIGHEST                                           (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_RESERVED0_SHIFT                                                   (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_RESERVED0_MASK                                                    (0x000001ffU)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_RESERVED1_SHIFT                                                   (11U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_RESERVED1_MASK                                                    (0x00000800U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_RESERVED2_SHIFT                                                   (14U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_2_RESERVED2_MASK                                                    (0xffffc000U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_GPU_P1_L3_PRESSURE_SHIFT                                          (23U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_GPU_P1_L3_PRESSURE_MASK                                           (0x01800000U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_GPU_P1_L3_PRESSURE_LOWEST                                          (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_GPU_P1_L3_PRESSURE_HIGHEST                                         (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_GPU_P2_L3_PRESSURE_SHIFT                                          (20U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_GPU_P2_L3_PRESSURE_MASK                                           (0x00300000U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_GPU_P2_L3_PRESSURE_LOWEST                                          (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_GPU_P2_L3_PRESSURE_HIGHEST                                         (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_RESERVED0_SHIFT                                                   (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_RESERVED0_MASK                                                    (0x000fffffU)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_RESERVED1_SHIFT                                                   (22U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_RESERVED1_MASK                                                    (0x00400000U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_RESERVED2_SHIFT                                                   (25U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_4_RESERVED2_MASK                                                    (0xfe000000U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_SATA_L3_PRESSURE_SHIFT                                            (3U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_SATA_L3_PRESSURE_MASK                                             (0x00000018U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_SATA_L3_PRESSURE_LOWEST                                            (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_SATA_L3_PRESSURE_HIGHEST                                           (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_MMC1_L3_PRESSURE_SHIFT                                            (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_MMC1_L3_PRESSURE_MASK                                             (0x00000003U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_MMC1_L3_PRESSURE_LOWEST                                            (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_MMC1_L3_PRESSURE_HIGHEST                                           (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_RESERVED0_SHIFT                                                   (2U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_RESERVED0_MASK                                                    (0x00000004U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_RESERVED1_SHIFT                                                   (5U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_5_RESERVED1_MASK                                                    (0xffffffe0U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_MMC2_L3_PRESSURE_SHIFT                                            (17U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_MMC2_L3_PRESSURE_MASK                                             (0x00060000U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_MMC2_L3_PRESSURE_LOWEST                                            (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_MMC2_L3_PRESSURE_HIGHEST                                           (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB1_L3_PRESSURE_SHIFT                                            (15U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB1_L3_PRESSURE_MASK                                             (0x00018000U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB1_L3_PRESSURE_LOWEST                                            (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB1_L3_PRESSURE_HIGHEST                                           (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB2_L3_PRESSURE_SHIFT                                            (12U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB2_L3_PRESSURE_MASK                                             (0x00003000U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB2_L3_PRESSURE_LOWEST                                            (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB2_L3_PRESSURE_HIGHEST                                           (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB3_L3_PRESSURE_SHIFT                                            (9U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB3_L3_PRESSURE_MASK                                             (0x00000600U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB3_L3_PRESSURE_LOWEST                                            (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB3_L3_PRESSURE_HIGHEST                                           (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB4_L3_PRESSURE_SHIFT                                            (6U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB4_L3_PRESSURE_MASK                                             (0x000000c0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB4_L3_PRESSURE_LOWEST                                            (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_USB4_L3_PRESSURE_HIGHEST                                           (3U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_RESERVED0_SHIFT                                                   (0U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_RESERVED0_MASK                                                    (0x0000001fU)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_RESERVED1_SHIFT                                                   (8U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_RESERVED1_MASK                                                    (0x00000100U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_RESERVED2_SHIFT                                                   (11U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_RESERVED2_MASK                                                    (0x00000800U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_RESERVED3_SHIFT                                                   (14U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_RESERVED3_MASK                                                    (0x00004000U)

#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_RESERVED4_SHIFT                                                   (19U)
#define CTRL_CORE_L3_INITIATOR_PRESSURE_6_RESERVED4_MASK                                                    (0xfff80000U)

#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_0_STD_FUSE_OPP_VDD_IVA_0_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_0_STD_FUSE_OPP_VDD_IVA_0_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_1_STD_FUSE_OPP_VDD_IVA_1_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_1_STD_FUSE_OPP_VDD_IVA_1_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_2_STD_FUSE_OPP_VDD_IVA_2_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_2_STD_FUSE_OPP_VDD_IVA_2_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_3_STD_FUSE_OPP_VDD_IVA_3_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_3_STD_FUSE_OPP_VDD_IVA_3_MASK                                        (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_4_STD_FUSE_OPP_VDD_IVA_4_SHIFT                                       (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_IVA_4_STD_FUSE_OPP_VDD_IVA_4_MASK                                        (0xffffffffU)

#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_MUX_CTRL_SHIFT                                (10U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_MUX_CTRL_MASK                                 (0x00000400U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_MUX_CTRL_OCP                                   (1U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_MUX_CTRL_EFUSE                                 (0U)

#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_VSET_IN_SHIFT                                 (5U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_VSET_IN_MASK                                  (0x000003e0U)

#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_VSET_OUT_SHIFT                                (0U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_LDOVBBDSPEVE_FBB_VSET_OUT_MASK                                 (0x0000001fU)

#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_RESERVED_0_SHIFT                                               (11U)
#define CTRL_CORE_LDOVBB_DSPEVE_VOLTAGE_CTRL_RESERVED_0_MASK                                                (0xfffff800U)

#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL_LDOVBBIVA_FBB_MUX_CTRL_SHIFT                                      (10U)
#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL_LDOVBBIVA_FBB_MUX_CTRL_MASK                                       (0x00000400U)
#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL_LDOVBBIVA_FBB_MUX_CTRL_OCP                                         (1U)
#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL_LDOVBBIVA_FBB_MUX_CTRL_EFUSE                                       (0U)

#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL_LDOVBBIVA_FBB_VSET_IN_SHIFT                                       (5U)
#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL_LDOVBBIVA_FBB_VSET_IN_MASK                                        (0x000003e0U)

#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL_LDOVBBIVA_FBB_VSET_OUT_SHIFT                                      (0U)
#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL_LDOVBBIVA_FBB_VSET_OUT_MASK                                       (0x0000001fU)

#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL_RESERVED_0_SHIFT                                                  (11U)
#define CTRL_CORE_LDOVBB_IVA_VOLTAGE_CTRL_RESERVED_0_MASK                                                   (0xfffff800U)

#define CTRL_CORE_SMA_SW_1_RGMII2_ID_MODE_N_SHIFT                                                           (26U)
#define CTRL_CORE_SMA_SW_1_RGMII2_ID_MODE_N_MASK                                                            (0x04000000U)

#define CTRL_CORE_SMA_SW_1_RGMII1_ID_MODE_N_SHIFT                                                           (25U)
#define CTRL_CORE_SMA_SW_1_RGMII1_ID_MODE_N_MASK                                                            (0x02000000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH2_ON_OFF_SHIFT                                                             (24U)
#define CTRL_CORE_SMA_SW_1_DSS_CH2_ON_OFF_MASK                                                              (0x01000000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH1_ON_OFF_SHIFT                                                             (23U)
#define CTRL_CORE_SMA_SW_1_DSS_CH1_ON_OFF_MASK                                                              (0x00800000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH0_ON_OFF_SHIFT                                                             (22U)
#define CTRL_CORE_SMA_SW_1_DSS_CH0_ON_OFF_MASK                                                              (0x00400000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH2_IPC_SHIFT                                                                (21U)
#define CTRL_CORE_SMA_SW_1_DSS_CH2_IPC_MASK                                                                 (0x00200000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH1_IPC_SHIFT                                                                (20U)
#define CTRL_CORE_SMA_SW_1_DSS_CH1_IPC_MASK                                                                 (0x00100000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH0_IPC_SHIFT                                                                (19U)
#define CTRL_CORE_SMA_SW_1_DSS_CH0_IPC_MASK                                                                 (0x00080000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH2_RF_SHIFT                                                                 (18U)
#define CTRL_CORE_SMA_SW_1_DSS_CH2_RF_MASK                                                                  (0x00040000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH1_RF_SHIFT                                                                 (17U)
#define CTRL_CORE_SMA_SW_1_DSS_CH1_RF_MASK                                                                  (0x00020000U)

#define CTRL_CORE_SMA_SW_1_DSS_CH0_RF_SHIFT                                                                 (16U)
#define CTRL_CORE_SMA_SW_1_DSS_CH0_RF_MASK                                                                  (0x00010000U)

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)

#define CTRL_CORE_SMA_SW_1_VIP3_CLK_INV_PORT_1A_SHIFT                                                       (10U)
#define CTRL_CORE_SMA_SW_1_VIP3_CLK_INV_PORT_1A_MASK                                                        (0x00000400U)

#define CTRL_CORE_SMA_SW_1_VIP3_CLK_INV_PORT_2A_SHIFT                                                       (9U)
#define CTRL_CORE_SMA_SW_1_VIP3_CLK_INV_PORT_2A_MASK                                                        (0x00000200U)

#endif  /* #if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) */

#define CTRL_CORE_SMA_SW_1_VPE_CLK_DIV_BY_2_EN_SHIFT                                                        (8U)
#define CTRL_CORE_SMA_SW_1_VPE_CLK_DIV_BY_2_EN_MASK                                                         (0x000000100U)
#define CTRL_CORE_SMA_SW_1_VPE_CLK_DIV_BY_2_EN_SEL_DPLL_CORE                                                (0U)
#define CTRL_CORE_SMA_SW_1_VPE_CLK_DIV_BY_2_EN_SEL_DPLL_VIDEO1                                              (1U)

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
#define CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_2B_SHIFT                                                       (7U)
#define CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_2B_MASK                                                        (0x00000080U)

#define CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_1B_SHIFT                                                       (6U)
#define CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_1B_MASK                                                        (0x00000040U)

#define CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_2A_SHIFT                                                       (5U)
#define CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_2A_MASK                                                        (0x00000020U)

#define CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_1A_SHIFT                                                       (4U)
#define CTRL_CORE_SMA_SW_1_VIP2_CLK_INV_PORT_1A_MASK                                                        (0x00000010U)

#endif  /* #if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x) */

#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2B_SHIFT                                                       (3U)
#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2B_MASK                                                        (0x00000008U)

#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1B_SHIFT                                                       (2U)
#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1B_MASK                                                        (0x00000004U)

#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2A_SHIFT                                                       (1U)
#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_2A_MASK                                                        (0x00000002U)

#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1A_SHIFT                                                       (0U)
#define CTRL_CORE_SMA_SW_1_VIP1_CLK_INV_PORT_1A_MASK                                                        (0x00000001U)

#define CTRL_CORE_SMA_SW_1_RESERVED_0_SHIFT                                                                 (6U)
#define CTRL_CORE_SMA_SW_1_RESERVED_0_MASK                                                                  (0x0000ffc0U)

#define CTRL_CORE_SMA_SW_1_RESERVED1_SHIFT                                                                  (25U)
#define CTRL_CORE_SMA_SW_1_RESERVED1_MASK                                                                   (0xfe000000U)

#define CTRL_CORE_DSS_PLL_CONTROL_RESERVED_SHIFT                                                            (11U)
#define CTRL_CORE_DSS_PLL_CONTROL_RESERVED_MASK                                                             (0xfffff800U)

#define CTRL_CORE_DSS_PLL_CONTROL_SDVENC_CLK_SELECTION_SHIFT                                                (9U)
#define CTRL_CORE_DSS_PLL_CONTROL_SDVENC_CLK_SELECTION_MASK                                                 (0x00000600U)
#define CTRL_CORE_DSS_PLL_CONTROL_SDVENC_CLK_SELECTION_DPLL_VIDEO1_HSDIVIDER_CLKOUT3                         (1U)
#define CTRL_CORE_DSS_PLL_CONTROL_SDVENC_CLK_SELECTION_HDMI_CLK                                              (0U)

#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_SELECTION_SHIFT                                               (7U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_SELECTION_MASK                                                (0x00000180U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_SELECTION_DPLL_VIDEO1                                          (1U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_SELECTION_DPLL_VIDEO2                                          (0U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_C_CLK1_SELECTION_DPLL_HDMI                                            (2U)

#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_SHIFT                                               (5U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_MASK                                                (0x00000060U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_DPLL_VIDEO2                                          (1U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_DPLL_ABE                                             (3U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_DPLL_VIDEO1                                          (0U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_B_CLK1_SELECTION_DPLL_HDMI                                            (2U)

#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_SELECTION_SHIFT                                               (3U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_SELECTION_MASK                                                (0x00000018U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_SELECTION_DPLL_HDMI                                            (1U)
#define CTRL_CORE_DSS_PLL_CONTROL_DSI1_A_CLK1_SELECTION_DPLL_VIDEO1                                          (0U)

#define CTRL_CORE_DSS_PLL_CONTROL_PLL_HDMI_DSS_CONTROL_DISABLE_SHIFT                                        (2U)
#define CTRL_CORE_DSS_PLL_CONTROL_PLL_HDMI_DSS_CONTROL_DISABLE_MASK                                         (0x00000004U)
#define CTRL_CORE_DSS_PLL_CONTROL_PLL_HDMI_DSS_CONTROL_DISABLE_PLLDISABLED                                   (1U)
#define CTRL_CORE_DSS_PLL_CONTROL_PLL_HDMI_DSS_CONTROL_DISABLE_PLLENABLED                                    (0U)

#define CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO2_DSS_CONTROL_DISABLE_SHIFT                                      (1U)
#define CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO2_DSS_CONTROL_DISABLE_MASK                                       (0x00000002U)
#define CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO2_DSS_CONTROL_DISABLE_PLLDISABLED                                 (1U)
#define CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO2_DSS_CONTROL_DISABLE_PLLENABLED                                  (0U)

#define CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO1_DSS_CONTROL_DISABLE_SHIFT                                      (0U)
#define CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO1_DSS_CONTROL_DISABLE_MASK                                       (0x00000001U)
#define CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO1_DSS_CONTROL_DISABLE_PLLDISABLED                                 (1U)
#define CTRL_CORE_DSS_PLL_CONTROL_PLL_VIDEO1_DSS_CONTROL_DISABLE_PLLENABLED                                  (0U)

#define CTRL_CORE_MMR_LOCK_1_MMR_LOCK_1_SHIFT                                                               (0U)
#define CTRL_CORE_MMR_LOCK_1_MMR_LOCK_1_MASK                                                                (0xffffffffU)
#define CTRL_CORE_MMR_LOCK_1_MMR_LOCK_1_TOLOCK                                                               (438075716U)
#define CTRL_CORE_MMR_LOCK_1_MMR_LOCK_1_TOUNLOCK                                                             (804367403U)

#define CTRL_CORE_MMR_LOCK_2_MMR_LOCK_2_SHIFT                                                               (0U)
#define CTRL_CORE_MMR_LOCK_2_MMR_LOCK_2_MASK                                                                (0xffffffffU)
#define CTRL_CORE_MMR_LOCK_2_MMR_LOCK_2_TOLOCK                                                               (4260648240U)
#define CTRL_CORE_MMR_LOCK_2_MMR_LOCK_2_TOUNLOCK                                                             (4149738944U)

#define CTRL_CORE_MMR_LOCK_3_MMR_LOCK_3_SHIFT                                                               (0U)
#define CTRL_CORE_MMR_LOCK_3_MMR_LOCK_3_MASK                                                                (0xffffffffU)
#define CTRL_CORE_MMR_LOCK_3_MMR_LOCK_3_TOLOCK                                                               (451339040U)
#define CTRL_CORE_MMR_LOCK_3_MMR_LOCK_3_TOUNLOCK                                                             (3803986541U)

#define CTRL_CORE_MMR_LOCK_4_MMR_LOCK_4_SHIFT                                                               (0U)
#define CTRL_CORE_MMR_LOCK_4_MMR_LOCK_4_MASK                                                                (0xffffffffU)
#define CTRL_CORE_MMR_LOCK_4_MMR_LOCK_4_TOUNLOCK                                                             (515838749U)
#define CTRL_CORE_MMR_LOCK_4_MMR_LOCK_4_TOLOCK                                                               (804950652U)

#define CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_SHIFT                                                               (0U)
#define CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_MASK                                                                (0xffffffffU)
#define CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOLOCK                                                               (339706668U)
#define CTRL_CORE_MMR_LOCK_5_MMR_LOCK_5_TOUNLOCK                                                             (1865817605U)

#define CTRL_CORE_CONTROL_IO_1_MMU2_DISABLE_SHIFT                                                           (20U)
#define CTRL_CORE_CONTROL_IO_1_MMU2_DISABLE_MASK                                                            (0x00100000U)

#define CTRL_CORE_CONTROL_IO_1_MMU1_DISABLE_SHIFT                                                           (16U)
#define CTRL_CORE_CONTROL_IO_1_MMU1_DISABLE_MASK                                                            (0x00010000U)

#define CTRL_CORE_CONTROL_IO_1_TC1_DEFAULT_BURST_SIZE_SHIFT                                                 (12U)
#define CTRL_CORE_CONTROL_IO_1_TC1_DEFAULT_BURST_SIZE_MASK                                                  (0x00003000U)

#define CTRL_CORE_CONTROL_IO_1_TC0_DEFAULT_BURST_SIZE_SHIFT                                                 (8U)
#define CTRL_CORE_CONTROL_IO_1_TC0_DEFAULT_BURST_SIZE_MASK                                                  (0x00000300U)

#define CTRL_CORE_CONTROL_IO_1_GMII2_SEL_SHIFT                                                              (4U)
#define CTRL_CORE_CONTROL_IO_1_GMII2_SEL_MASK                                                               (0x00000030U)

#define CTRL_CORE_CONTROL_IO_1_GMII1_SEL_SHIFT                                                              (0U)
#define CTRL_CORE_CONTROL_IO_1_GMII1_SEL_MASK                                                               (0x00000003U)

#define CTRL_CORE_CONTROL_IO_1_RESERVED0_SHIFT                                                              (2U)
#define CTRL_CORE_CONTROL_IO_1_RESERVED0_MASK                                                               (0x0000000cU)

#define CTRL_CORE_CONTROL_IO_1_RESERVED1_SHIFT                                                              (6U)
#define CTRL_CORE_CONTROL_IO_1_RESERVED1_MASK                                                               (0x000000c0U)

#define CTRL_CORE_CONTROL_IO_1_RESERVED2_SHIFT                                                              (10U)
#define CTRL_CORE_CONTROL_IO_1_RESERVED2_MASK                                                               (0x00000c00U)

#define CTRL_CORE_CONTROL_IO_1_RESERVED_SHIFT                                                               (14U)
#define CTRL_CORE_CONTROL_IO_1_RESERVED_MASK                                                                (0x0000c000U)

#define CTRL_CORE_CONTROL_IO_1_RESERVED_2_SHIFT                                                             (17U)
#define CTRL_CORE_CONTROL_IO_1_RESERVED_2_MASK                                                              (0x000e0000U)

#define CTRL_CORE_CONTROL_IO_1_RESERVED_3_SHIFT                                                             (21U)
#define CTRL_CORE_CONTROL_IO_1_RESERVED_3_MASK                                                              (0xffe00000U)

#define CTRL_CORE_CONTROL_IO_2_GMAC_RESET_ISOLATION_ENABLE_SHIFT                                            (23U)
#define CTRL_CORE_CONTROL_IO_2_GMAC_RESET_ISOLATION_ENABLE_MASK                                             (0x00800000U)
#define CTRL_CORE_CONTROL_IO_2_GMAC_RESET_ISOLATION_ENABLE_RESETISOLATED                                     (1U)
#define CTRL_CORE_CONTROL_IO_2_GMAC_RESET_ISOLATION_ENABLE_NOTRESETISOLATED                                  (0U)

#define CTRL_CORE_CONTROL_IO_2_PWMSS3_TBCLKEN_SHIFT                                                         (22U)
#define CTRL_CORE_CONTROL_IO_2_PWMSS3_TBCLKEN_MASK                                                          (0x00400000U)

#define CTRL_CORE_CONTROL_IO_2_PWMSS2_TBCLKEN_SHIFT                                                         (21U)
#define CTRL_CORE_CONTROL_IO_2_PWMSS2_TBCLKEN_MASK                                                          (0x00200000U)

#define CTRL_CORE_CONTROL_IO_2_PWMSS1_TBCLKEN_SHIFT                                                         (20U)
#define CTRL_CORE_CONTROL_IO_2_PWMSS1_TBCLKEN_MASK                                                          (0x00100000U)

#define CTRL_CORE_CONTROL_IO_2_MLB_CLOCK_DOUBLER_ENABLE_SHIFT                                               (18U)
#define CTRL_CORE_CONTROL_IO_2_MLB_CLOCK_DOUBLER_ENABLE_MASK                                                (0x00040000U)
#define CTRL_CORE_CONTROL_IO_2_MLB_CLOCK_DOUBLER_ENABLE_MLB6PINCLOCKDOUBLERISENABLED                         (1U)
#define CTRL_CORE_CONTROL_IO_2_MLB_CLOCK_DOUBLER_ENABLE_MLB6PINCLOCKISENABLED                                (0U)

#define CTRL_CORE_CONTROL_IO_2_VIP2_VIN2_INPUT_SELECTION_SHIFT                                              (17U)
#define CTRL_CORE_CONTROL_IO_2_VIP2_VIN2_INPUT_SELECTION_MASK                                               (0x00020000U)
#define CTRL_CORE_CONTROL_IO_2_VIP2_VIN2_INPUT_SELECTION_FROMLVDSRXPORT2                                     (1U)
#define CTRL_CORE_CONTROL_IO_2_VIP2_VIN2_INPUT_SELECTION_FROMPINS                                            (0U)

#define CTRL_CORE_CONTROL_IO_2_VIP2_VIN1_INPUT_SELECTION_SHIFT                                              (16U)
#define CTRL_CORE_CONTROL_IO_2_VIP2_VIN1_INPUT_SELECTION_MASK                                               (0x00010000U)
#define CTRL_CORE_CONTROL_IO_2_VIP2_VIN1_INPUT_SELECTION_FROMLVDSRXPORT1                                     (1U)
#define CTRL_CORE_CONTROL_IO_2_VIP2_VIN1_INPUT_SELECTION_FROMPINS                                            (0U)

#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN2_INPUT_SELECTION_SHIFT                                              (15U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN2_INPUT_SELECTION_MASK                                               (0x00008000U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN2_INPUT_SELECTION_FROMLVDSRXPORT2                                     (1U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN2_INPUT_SELECTION_FROMPINS                                            (0U)

#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN1_INPUT_SELECTION_SHIFT                                              (14U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN1_INPUT_SELECTION_MASK                                               (0x00004000U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN1_INPUT_SELECTION_FROMLVDSRXPORT1                                     (1U)
#define CTRL_CORE_CONTROL_IO_2_VIP1_VIN1_INPUT_SELECTION_FROMPINS                                            (0U)

#define CTRL_CORE_CONTROL_IO_2_PCIE_1LANE_2LANE_SELECTION_SHIFT                                             (13U)
#define CTRL_CORE_CONTROL_IO_2_PCIE_1LANE_2LANE_SELECTION_MASK                                              (0x00002000U)
#define CTRL_CORE_CONTROL_IO_2_PCIE_1LANE_2LANE_SELECTION_2_LANE                                             (1U)
#define CTRL_CORE_CONTROL_IO_2_PCIE_1LANE_2LANE_SELECTION_1_LANE                                             (0U)

#define CTRL_CORE_CONTROL_IO_2_QSPI_MEMMAPPED_CS_SHIFT                                                      (8U)
#define CTRL_CORE_CONTROL_IO_2_QSPI_MEMMAPPED_CS_MASK                                                       (0x00000700U)

#define CTRL_CORE_CONTROL_IO_2_DSP2_SECURE_EN_RESERVED_SHIFT                                                (7U)
#define CTRL_CORE_CONTROL_IO_2_DSP2_SECURE_EN_RESERVED_MASK                                                 (0x00000080U)

#define CTRL_CORE_CONTROL_IO_2_DSP1_SECURE_EN_RESERVED_SHIFT                                                (6U)
#define CTRL_CORE_CONTROL_IO_2_DSP1_SECURE_EN_RESERVED_MASK                                                 (0x00000040U)

#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SHIFT                                                    (5U)
#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_MASK                                                     (0x00000020U)
#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET                                                      (1U)
#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_CLEAR                                                    (0U)
#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_CAUSESTHEINITIALIZATIONPULSETOHAPPEN_NONEEDFORSWTOWRITE0  (CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_START_SET)

#define CTRL_CORE_CONTROL_IO_2_DSS_DESHDCP_DISABLE_SHIFT                                                    (4U)
#define CTRL_CORE_CONTROL_IO_2_DSS_DESHDCP_DISABLE_MASK                                                     (0x00000010U)

#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SHIFT                                                    (3U)
#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_MASK                                                     (0x00000008U)
#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET                                                      (1U)
#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_CLEAR                                                    (0U)
#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_CAUSESTHEINITIALIZATIONPULSETOHAPPEN_NONEEDFORSWTOWRITE0  (CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_START_SET)

#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_SHIFT                                                     (2U)
#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_MASK                                                      (0x00000004U)
#define CTRL_CORE_CONTROL_IO_2_DCAN2_RAMINIT_DONE_CLEAR                                                     (1U)

#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_SHIFT                                                     (1U)
#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_MASK                                                      (0x00000002U)
#define CTRL_CORE_CONTROL_IO_2_DCAN1_RAMINIT_DONE_CLEAR                                                     (1U)

#define CTRL_CORE_CONTROL_IO_2_DSS_DESHDCP_CLKEN_SHIFT                                                      (0U)
#define CTRL_CORE_CONTROL_IO_2_DSS_DESHDCP_CLKEN_MASK                                                       (0x00000001U)

#define CTRL_CORE_CONTROL_IO_2_RESERVED3_SHIFT                                                              (24U)
#define CTRL_CORE_CONTROL_IO_2_RESERVED3_MASK                                                               (0xff000000U)

#define CTRL_CORE_CONTROL_IO_2_RESERVED2_SHIFT                                                              (14U)
#define CTRL_CORE_CONTROL_IO_2_RESERVED2_MASK                                                               (0x000fc000U)

#define CTRL_CORE_CONTROL_IO_2_RESERVED1_SHIFT                                                              (11U)
#define CTRL_CORE_CONTROL_IO_2_RESERVED1_MASK                                                               (0x00001800U)

#define CTRL_CORE_CONTROL_IO_2_RESERVED0_SHIFT                                                              (6U)
#define CTRL_CORE_CONTROL_IO_2_RESERVED0_MASK                                                               (0x000000c0U)

#define CTRL_CORE_CONTROL_DSP1_RST_VECT_DSP1_NUM_MM_SHIFT                                                   (24U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT_DSP1_NUM_MM_MASK                                                    (0x07000000U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT_DSP1_NUM_MM_TWODSPS                                                  (2U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT_DSP1_NUM_MM_ONEDSP                                                   (1U)

#define CTRL_CORE_CONTROL_DSP1_RST_VECT_DSP1_RST_VECT_SHIFT                                                 (0U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT_DSP1_RST_VECT_MASK                                                  (0x003fffffU)

#define CTRL_CORE_CONTROL_DSP1_RST_VECT_RESERVED_0_SHIFT                                                    (22U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT_RESERVED_0_MASK                                                     (0x00c00000U)

#define CTRL_CORE_CONTROL_DSP1_RST_VECT_RESERVED_1_SHIFT                                                    (27U)
#define CTRL_CORE_CONTROL_DSP1_RST_VECT_RESERVED_1_MASK                                                     (0xf8000000U)

#define CTRL_CORE_CONTROL_DSP2_RST_VECT_DSP2_NUM_MM_SHIFT                                                   (24U)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT_DSP2_NUM_MM_MASK                                                    (0x07000000U)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT_DSP2_NUM_MM_TWODSPS                                                  (2U)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT_DSP2_NUM_MM_ONEDSP                                                   (1U)

#define CTRL_CORE_CONTROL_DSP2_RST_VECT_DSP2_RST_VECT_SHIFT                                                 (0U)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT_DSP2_RST_VECT_MASK                                                  (0x003fffffU)

#define CTRL_CORE_CONTROL_DSP2_RST_VECT_RESERVED_0_SHIFT                                                    (22U)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT_RESERVED_0_MASK                                                     (0x00c00000U)

#define CTRL_CORE_CONTROL_DSP2_RST_VECT_RESERVED_1_SHIFT                                                    (27U)
#define CTRL_CORE_CONTROL_DSP2_RST_VECT_RESERVED_1_MASK                                                     (0xf8000000U)

#define CTRL_CORE_STD_FUSE_OPP_BGAP_DSPEVE_STD_FUSE_OPP_BGAP_DSPEVE_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_DSPEVE_STD_FUSE_OPP_BGAP_DSPEVE_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_BGAP_IVA_STD_FUSE_OPP_BGAP_IVA_SHIFT                                         (0U)
#define CTRL_CORE_STD_FUSE_OPP_BGAP_IVA_STD_FUSE_OPP_BGAP_IVA_MASK                                          (0xffffffffU)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_RETMODE_MUX_CTRL_SHIFT                          (26U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_RETMODE_MUX_CTRL_MASK                           (0x04000000U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_RETMODE_MUX_CTRL_OCP                             (1U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_RETMODE_MUX_CTRL_EFUSE                           (0U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_RETMODE_VSET_IN_SHIFT                           (21U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_RETMODE_VSET_IN_MASK                            (0x03e00000U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_RETMODE_VSET_OUT_SHIFT                          (16U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_RETMODE_VSET_OUT_MASK                           (0x001f0000U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_ACTMODE_MUX_CTRL_SHIFT                          (10U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_ACTMODE_MUX_CTRL_MASK                           (0x00000400U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_ACTMODE_MUX_CTRL_OCP                             (1U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_ACTMODE_MUX_CTRL_EFUSE                           (0U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_ACTMODE_VSET_IN_SHIFT                           (5U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_ACTMODE_VSET_IN_MASK                            (0x000003e0U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_ACTMODE_VSET_OUT_SHIFT                          (0U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_LDOSRAMDSPEVE_ACTMODE_VSET_OUT_MASK                           (0x0000001fU)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_RESERVED_0_SHIFT                                              (11U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_RESERVED_0_MASK                                               (0x0000f800U)

#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_RESERVED_1_SHIFT                                              (27U)
#define CTRL_CORE_LDOSRAM_DSPEVE_VOLTAGE_CTRL_RESERVED_1_MASK                                               (0xf8000000U)

#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_RETMODE_MUX_CTRL_SHIFT                                (26U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_RETMODE_MUX_CTRL_MASK                                 (0x04000000U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_RETMODE_MUX_CTRL_OCP                                   (1U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_RETMODE_MUX_CTRL_EFUSE                                 (0U)

#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_RETMODE_VSET_IN_SHIFT                                 (21U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_RETMODE_VSET_IN_MASK                                  (0x03e00000U)

#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_RETMODE_VSET_OUT_SHIFT                                (16U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_RETMODE_VSET_OUT_MASK                                 (0x001f0000U)

#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_ACTMODE_MUX_CTRL_SHIFT                                (10U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_ACTMODE_MUX_CTRL_MASK                                 (0x00000400U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_ACTMODE_MUX_CTRL_OCP                                   (1U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_ACTMODE_MUX_CTRL_EFUSE                                 (0U)

#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_ACTMODE_VSET_IN_SHIFT                                 (5U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_ACTMODE_VSET_IN_MASK                                  (0x000003e0U)

#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_ACTMODE_VSET_OUT_SHIFT                                (0U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_LDOSRAMIVA_ACTMODE_VSET_OUT_MASK                                 (0x0000001fU)

#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_RESERVED_0_SHIFT                                                 (11U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_RESERVED_0_MASK                                                  (0x0000f800U)

#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_RESERVED_1_SHIFT                                                 (27U)
#define CTRL_CORE_LDOSRAM_IVA_VOLTAGE_CTRL_RESERVED_1_MASK                                                  (0xf8000000U)

#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_TMPSOFF_DSPEVE_SHIFT                                              (11U)
#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_TMPSOFF_DSPEVE_MASK                                               (0x00000800U)

#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_EOCZ_DSPEVE_SHIFT                                                 (10U)
#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_EOCZ_DSPEVE_MASK                                                  (0x00000400U)

#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_DTEMP_DSPEVE_SHIFT                                                (0U)
#define CTRL_CORE_TEMP_SENSOR_DSPEVE_BGAP_DTEMP_DSPEVE_MASK                                                 (0x000003ffU)

#define CTRL_CORE_TEMP_SENSOR_DSPEVE_RESERVED_0_SHIFT                                                       (12U)
#define CTRL_CORE_TEMP_SENSOR_DSPEVE_RESERVED_0_MASK                                                        (0xfffff000U)

#define CTRL_CORE_TEMP_SENSOR_IVA_BGAP_TMPSOFF_IVA_SHIFT                                                    (11U)
#define CTRL_CORE_TEMP_SENSOR_IVA_BGAP_TMPSOFF_IVA_MASK                                                     (0x00000800U)

#define CTRL_CORE_TEMP_SENSOR_IVA_BGAP_EOCZ_IVA_SHIFT                                                       (10U)
#define CTRL_CORE_TEMP_SENSOR_IVA_BGAP_EOCZ_IVA_MASK                                                        (0x00000400U)

#define CTRL_CORE_TEMP_SENSOR_IVA_BGAP_DTEMP_IVA_SHIFT                                                      (0U)
#define CTRL_CORE_TEMP_SENSOR_IVA_BGAP_DTEMP_IVA_MASK                                                       (0x000003ffU)

#define CTRL_CORE_TEMP_SENSOR_IVA_RESERVED_0_SHIFT                                                          (12U)
#define CTRL_CORE_TEMP_SENSOR_IVA_RESERVED_0_MASK                                                           (0xfffff000U)

#define CTRL_CORE_BANDGAP_MASK_2_FREEZE_IVA_SHIFT                                                           (22U)
#define CTRL_CORE_BANDGAP_MASK_2_FREEZE_IVA_MASK                                                            (0x00400000U)
#define CTRL_CORE_BANDGAP_MASK_2_FREEZE_IVA_UNMASKED                                                         (1U)
#define CTRL_CORE_BANDGAP_MASK_2_FREEZE_IVA_MASKED                                                           (0U)

#define CTRL_CORE_BANDGAP_MASK_2_FREEZE_DSPEVE_SHIFT                                                        (21U)
#define CTRL_CORE_BANDGAP_MASK_2_FREEZE_DSPEVE_MASK                                                         (0x00200000U)
#define CTRL_CORE_BANDGAP_MASK_2_FREEZE_DSPEVE_UNMASKED                                                      (1U)
#define CTRL_CORE_BANDGAP_MASK_2_FREEZE_DSPEVE_MASKED                                                        (0U)

#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_IVA_SHIFT                                                            (19U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_IVA_MASK                                                             (0x00080000U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_IVA_UNMASKED                                                          (1U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_IVA_MASKED                                                            (0U)

#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_DSPEVE_SHIFT                                                         (18U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_DSPEVE_MASK                                                          (0x00040000U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_DSPEVE_UNMASKED                                                       (1U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_DSPEVE_MASKED                                                         (0U)

#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_ACCUM_IVA_SHIFT                                                      (16U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_ACCUM_IVA_MASK                                                       (0x00010000U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_ACCUM_IVA_UNMASKED                                                    (1U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_ACCUM_IVA_MASKED                                                      (0U)

#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_ACCUM_DSPEVE_SHIFT                                                   (15U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_ACCUM_DSPEVE_MASK                                                    (0x00008000U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_ACCUM_DSPEVE_UNMASKED                                                 (1U)
#define CTRL_CORE_BANDGAP_MASK_2_CLEAR_ACCUM_DSPEVE_MASKED                                                   (0U)

#define CTRL_CORE_BANDGAP_MASK_2_MASK_HOT_IVA_SHIFT                                                         (3U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_HOT_IVA_MASK                                                          (0x00000008U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_HOT_IVA_UNMASKED                                                       (1U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_HOT_IVA_MASKED                                                         (0U)

#define CTRL_CORE_BANDGAP_MASK_2_MASK_COLD_IVA_SHIFT                                                        (2U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_COLD_IVA_MASK                                                         (0x00000004U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_COLD_IVA_UNMASKED                                                      (1U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_COLD_IVA_MASKED                                                        (0U)

#define CTRL_CORE_BANDGAP_MASK_2_MASK_HOT_DSPEVE_SHIFT                                                      (1U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_HOT_DSPEVE_MASK                                                       (0x00000002U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_HOT_DSPEVE_UNMASKED                                                    (1U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_HOT_DSPEVE_MASKED                                                      (0U)

#define CTRL_CORE_BANDGAP_MASK_2_MASK_COLD_DSPEVE_SHIFT                                                     (0U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_COLD_DSPEVE_MASK                                                      (0x00000001U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_COLD_DSPEVE_UNMASKED                                                   (1U)
#define CTRL_CORE_BANDGAP_MASK_2_MASK_COLD_DSPEVE_MASKED                                                     (0U)

#define CTRL_CORE_BANDGAP_MASK_2_RESERVED_0_SHIFT                                                           (4U)
#define CTRL_CORE_BANDGAP_MASK_2_RESERVED_0_MASK                                                            (0x00007ff0U)

#define CTRL_CORE_BANDGAP_MASK_2_RESERVED_1_SHIFT                                                           (17U)
#define CTRL_CORE_BANDGAP_MASK_2_RESERVED_1_MASK                                                            (0x00020000U)

#define CTRL_CORE_BANDGAP_MASK_2_RESERVED_2_SHIFT                                                           (20U)
#define CTRL_CORE_BANDGAP_MASK_2_RESERVED_2_MASK                                                            (0x00100000U)

#define CTRL_CORE_BANDGAP_MASK_2_RESERVED_3_SHIFT                                                           (23U)
#define CTRL_CORE_BANDGAP_MASK_2_RESERVED_3_MASK                                                            (0x7f800000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_DSPEVE_THOLD_HOT_DSPEVE_SHIFT                                           (16U)
#define CTRL_CORE_BANDGAP_THRESHOLD_DSPEVE_THOLD_HOT_DSPEVE_MASK                                            (0x03ff0000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_DSPEVE_THOLD_COLD_DSPEVE_SHIFT                                          (0U)
#define CTRL_CORE_BANDGAP_THRESHOLD_DSPEVE_THOLD_COLD_DSPEVE_MASK                                           (0x000003ffU)

#define CTRL_CORE_BANDGAP_THRESHOLD_DSPEVE_RESERVED_0_SHIFT                                                 (10U)
#define CTRL_CORE_BANDGAP_THRESHOLD_DSPEVE_RESERVED_0_MASK                                                  (0x0000fc00U)

#define CTRL_CORE_BANDGAP_THRESHOLD_DSPEVE_RESERVED_1_SHIFT                                                 (26U)
#define CTRL_CORE_BANDGAP_THRESHOLD_DSPEVE_RESERVED_1_MASK                                                  (0xfc000000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_IVA_THOLD_HOT_IVA_SHIFT                                                 (16U)
#define CTRL_CORE_BANDGAP_THRESHOLD_IVA_THOLD_HOT_IVA_MASK                                                  (0x03ff0000U)

#define CTRL_CORE_BANDGAP_THRESHOLD_IVA_THOLD_COLD_IVA_SHIFT                                                (0U)
#define CTRL_CORE_BANDGAP_THRESHOLD_IVA_THOLD_COLD_IVA_MASK                                                 (0x000003ffU)

#define CTRL_CORE_BANDGAP_THRESHOLD_IVA_RESERVED_0_SHIFT                                                    (10U)
#define CTRL_CORE_BANDGAP_THRESHOLD_IVA_RESERVED_0_MASK                                                     (0x0000fc00U)

#define CTRL_CORE_BANDGAP_THRESHOLD_IVA_RESERVED_1_SHIFT                                                    (26U)
#define CTRL_CORE_BANDGAP_THRESHOLD_IVA_RESERVED_1_MASK                                                     (0xfc000000U)

#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_TSHUT_MUXCTRL_DSPEVE_SHIFT                                           (31U)
#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_TSHUT_MUXCTRL_DSPEVE_MASK                                            (0x80000000U)
#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_TSHUT_MUXCTRL_DSPEVE_OCP                                              (1U)
#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_TSHUT_MUXCTRL_DSPEVE_EFUSE                                            (0U)

#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_TSHUT_HOT_DSPEVE_SHIFT                                               (16U)
#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_TSHUT_HOT_DSPEVE_MASK                                                (0x03ff0000U)

#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_TSHUT_COLD_DSPEVE_SHIFT                                              (0U)
#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_TSHUT_COLD_DSPEVE_MASK                                               (0x000003ffU)

#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_RESERVED_0_SHIFT                                                     (10U)
#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_RESERVED_0_MASK                                                      (0x0000fc00U)

#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_RESERVED_1_SHIFT                                                     (26U)
#define CTRL_CORE_BANDGAP_TSHUT_DSPEVE_RESERVED_1_MASK                                                      (0x7c000000U)

#define CTRL_CORE_BANDGAP_TSHUT_IVA_TSHUT_MUXCTRL_IVA_SHIFT                                                 (31U)
#define CTRL_CORE_BANDGAP_TSHUT_IVA_TSHUT_MUXCTRL_IVA_MASK                                                  (0x80000000U)
#define CTRL_CORE_BANDGAP_TSHUT_IVA_TSHUT_MUXCTRL_IVA_OCP                                                    (1U)
#define CTRL_CORE_BANDGAP_TSHUT_IVA_TSHUT_MUXCTRL_IVA_EFUSE                                                  (0U)

#define CTRL_CORE_BANDGAP_TSHUT_IVA_TSHUT_HOT_IVA_SHIFT                                                     (16U)
#define CTRL_CORE_BANDGAP_TSHUT_IVA_TSHUT_HOT_IVA_MASK                                                      (0x03ff0000U)

#define CTRL_CORE_BANDGAP_TSHUT_IVA_TSHUT_COLD_IVA_SHIFT                                                    (0U)
#define CTRL_CORE_BANDGAP_TSHUT_IVA_TSHUT_COLD_IVA_MASK                                                     (0x000003ffU)

#define CTRL_CORE_BANDGAP_TSHUT_IVA_RESERVED_0_SHIFT                                                        (10U)
#define CTRL_CORE_BANDGAP_TSHUT_IVA_RESERVED_0_MASK                                                         (0x0000fc00U)

#define CTRL_CORE_BANDGAP_TSHUT_IVA_RESERVED_1_SHIFT                                                        (26U)
#define CTRL_CORE_BANDGAP_TSHUT_IVA_RESERVED_1_MASK                                                         (0x7c000000U)

#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_DSPEVE_CUMUL_DTEMP_DSPEVE_SHIFT                                       (0U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_DSPEVE_CUMUL_DTEMP_DSPEVE_MASK                                        (0xffffffffU)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_DSPEVE_CUMUL_DTEMP_DSPEVE_REPEAT                                       (1U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_DSPEVE_CUMUL_DTEMP_DSPEVE_SINGLE                                       (0U)

#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_IVA_CUMUL_DTEMP_IVA_SHIFT                                             (0U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_IVA_CUMUL_DTEMP_IVA_MASK                                              (0xffffffffU)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_IVA_CUMUL_DTEMP_IVA_REPEAT                                             (1U)
#define CTRL_CORE_BANDGAP_CUMUL_DTEMP_IVA_CUMUL_DTEMP_IVA_SINGLE                                             (0U)

#define CTRL_CORE_BANDGAP_STATUS_2_HOT_IVA_SHIFT                                                            (3U)
#define CTRL_CORE_BANDGAP_STATUS_2_HOT_IVA_MASK                                                             (0x00000008U)
#define CTRL_CORE_BANDGAP_STATUS_2_HOT_IVA_EVENT                                                             (1U)
#define CTRL_CORE_BANDGAP_STATUS_2_HOT_IVA_NOEVENT                                                           (0U)

#define CTRL_CORE_BANDGAP_STATUS_2_COLD_IVA_SHIFT                                                           (2U)
#define CTRL_CORE_BANDGAP_STATUS_2_COLD_IVA_MASK                                                            (0x00000004U)
#define CTRL_CORE_BANDGAP_STATUS_2_COLD_IVA_EVENT                                                            (1U)
#define CTRL_CORE_BANDGAP_STATUS_2_COLD_IVA_NOEVENT                                                          (0U)

#define CTRL_CORE_BANDGAP_STATUS_2_HOT_DSPEVE_SHIFT                                                         (1U)
#define CTRL_CORE_BANDGAP_STATUS_2_HOT_DSPEVE_MASK                                                          (0x00000002U)
#define CTRL_CORE_BANDGAP_STATUS_2_HOT_DSPEVE_EVENT                                                          (1U)
#define CTRL_CORE_BANDGAP_STATUS_2_HOT_DSPEVE_NOEVENT                                                        (0U)

#define CTRL_CORE_BANDGAP_STATUS_2_COLD_DSPEVE_SHIFT                                                        (0U)
#define CTRL_CORE_BANDGAP_STATUS_2_COLD_DSPEVE_MASK                                                         (0x00000001U)
#define CTRL_CORE_BANDGAP_STATUS_2_COLD_DSPEVE_EVENT                                                         (1U)
#define CTRL_CORE_BANDGAP_STATUS_2_COLD_DSPEVE_NOEVENT                                                       (0U)

#define CTRL_CORE_BANDGAP_STATUS_2_RESERVED_0_SHIFT                                                         (4U)
#define CTRL_CORE_BANDGAP_STATUS_2_RESERVED_0_MASK                                                          (0xfffffff0U)

#define CTRL_CORE_DTEMP_DSPEVE_0_DTEMP_TAG_DSPEVE_0_SHIFT                                                   (10U)
#define CTRL_CORE_DTEMP_DSPEVE_0_DTEMP_TAG_DSPEVE_0_MASK                                                    (0xfffffc00U)

#define CTRL_CORE_DTEMP_DSPEVE_0_DTEMP_TEMPERATURE_DSPEVE_0_SHIFT                                           (0U)
#define CTRL_CORE_DTEMP_DSPEVE_0_DTEMP_TEMPERATURE_DSPEVE_0_MASK                                            (0x000003ffU)

#define CTRL_CORE_DTEMP_DSPEVE_1_DTEMP_TAG_DSPEVE_1_SHIFT                                                   (10U)
#define CTRL_CORE_DTEMP_DSPEVE_1_DTEMP_TAG_DSPEVE_1_MASK                                                    (0xfffffc00U)

#define CTRL_CORE_DTEMP_DSPEVE_1_DTEMP_TEMPERATURE_DSPEVE_1_SHIFT                                           (0U)
#define CTRL_CORE_DTEMP_DSPEVE_1_DTEMP_TEMPERATURE_DSPEVE_1_MASK                                            (0x000003ffU)

#define CTRL_CORE_DTEMP_DSPEVE_2_DTEMP_TAG_DSPEVE_2_SHIFT                                                   (10U)
#define CTRL_CORE_DTEMP_DSPEVE_2_DTEMP_TAG_DSPEVE_2_MASK                                                    (0xfffffc00U)

#define CTRL_CORE_DTEMP_DSPEVE_2_DTEMP_TEMPERATURE_DSPEVE_2_SHIFT                                           (0U)
#define CTRL_CORE_DTEMP_DSPEVE_2_DTEMP_TEMPERATURE_DSPEVE_2_MASK                                            (0x000003ffU)

#define CTRL_CORE_DTEMP_DSPEVE_3_DTEMP_TAG_DSPEVE_3_SHIFT                                                   (10U)
#define CTRL_CORE_DTEMP_DSPEVE_3_DTEMP_TAG_DSPEVE_3_MASK                                                    (0xfffffc00U)

#define CTRL_CORE_DTEMP_DSPEVE_3_DTEMP_TEMPERATURE_DSPEVE_3_SHIFT                                           (0U)
#define CTRL_CORE_DTEMP_DSPEVE_3_DTEMP_TEMPERATURE_DSPEVE_3_MASK                                            (0x000003ffU)

#define CTRL_CORE_DTEMP_DSPEVE_4_DTEMP_TAG_DSPEVE_4_SHIFT                                                   (10U)
#define CTRL_CORE_DTEMP_DSPEVE_4_DTEMP_TAG_DSPEVE_4_MASK                                                    (0xfffffc00U)

#define CTRL_CORE_DTEMP_DSPEVE_4_DTEMP_TEMPERATURE_DSPEVE_4_SHIFT                                           (0U)
#define CTRL_CORE_DTEMP_DSPEVE_4_DTEMP_TEMPERATURE_DSPEVE_4_MASK                                            (0x000003ffU)

#define CTRL_CORE_DTEMP_IVA_0_DTEMP_TAG_IVA_0_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_IVA_0_DTEMP_TAG_IVA_0_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_IVA_0_DTEMP_TEMPERATURE_IVA_0_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_IVA_0_DTEMP_TEMPERATURE_IVA_0_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_IVA_1_DTEMP_TAG_IVA_1_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_IVA_1_DTEMP_TAG_IVA_1_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_IVA_1_DTEMP_TEMPERATURE_IVA_1_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_IVA_1_DTEMP_TEMPERATURE_IVA_1_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_IVA_2_DTEMP_TAG_IVA_2_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_IVA_2_DTEMP_TAG_IVA_2_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_IVA_2_DTEMP_TEMPERATURE_IVA_2_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_IVA_2_DTEMP_TEMPERATURE_IVA_2_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_IVA_3_DTEMP_TAG_IVA_3_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_IVA_3_DTEMP_TAG_IVA_3_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_IVA_3_DTEMP_TEMPERATURE_IVA_3_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_IVA_3_DTEMP_TEMPERATURE_IVA_3_MASK                                                  (0x000003ffU)

#define CTRL_CORE_DTEMP_IVA_4_DTEMP_TAG_IVA_4_SHIFT                                                         (10U)
#define CTRL_CORE_DTEMP_IVA_4_DTEMP_TAG_IVA_4_MASK                                                          (0xfffffc00U)

#define CTRL_CORE_DTEMP_IVA_4_DTEMP_TEMPERATURE_IVA_4_SHIFT                                                 (0U)
#define CTRL_CORE_DTEMP_IVA_4_DTEMP_TEMPERATURE_IVA_4_MASK                                                  (0x000003ffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_0_STD_FUSE_OPP_VMIN_IVA_0_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_0_STD_FUSE_OPP_VMIN_IVA_0_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_1_STD_FUSE_OPP_VMIN_IVA_1_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_1_STD_FUSE_OPP_VMIN_IVA_1_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_2_STD_FUSE_OPP_VMIN_IVA_2_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_2_STD_FUSE_OPP_VMIN_IVA_2_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_3_STD_FUSE_OPP_VMIN_IVA_3_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_3_STD_FUSE_OPP_VMIN_IVA_3_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_4_STD_FUSE_OPP_VMIN_IVA_4_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_4_STD_FUSE_OPP_VMIN_IVA_4_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_5_STD_FUSE_OPP_VMIN_IVA_5_SHIFT                                     (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_IVA_5_STD_FUSE_OPP_VMIN_IVA_5_MASK                                      (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_0_STD_FUSE_OPP_VMIN_DSPEVE_0_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_0_STD_FUSE_OPP_VMIN_DSPEVE_0_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_1_STD_FUSE_OPP_VMIN_DSPEVE_1_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_1_STD_FUSE_OPP_VMIN_DSPEVE_1_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_2_STD_FUSE_OPP_VMIN_DSPEVE_2_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_2_STD_FUSE_OPP_VMIN_DSPEVE_2_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_3_STD_FUSE_OPP_VMIN_DSPEVE_3_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_3_STD_FUSE_OPP_VMIN_DSPEVE_3_MASK                                (0xffffffffU)


#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_4_STD_FUSE_OPP_VMIN_DSPEVE_4_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_4_STD_FUSE_OPP_VMIN_DSPEVE_4_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_5_STD_FUSE_OPP_VMIN_DSPEVE_5_SHIFT                               (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_DSPEVE_5_STD_FUSE_OPP_VMIN_DSPEVE_5_MASK                                (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_0_STD_FUSE_OPP_VMIN_CORE_0_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_0_STD_FUSE_OPP_VMIN_CORE_0_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_1_STD_FUSE_OPP_VMIN_CORE_1_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_1_STD_FUSE_OPP_VMIN_CORE_1_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_2_STD_FUSE_OPP_VMIN_CORE_2_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_2_STD_FUSE_OPP_VMIN_CORE_2_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_3_STD_FUSE_OPP_VMIN_CORE_3_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_3_STD_FUSE_OPP_VMIN_CORE_3_MASK                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_4_STD_FUSE_OPP_VMIN_CORE_4_SHIFT                                   (0U)
#define CTRL_CORE_STD_FUSE_OPP_VMIN_CORE_4_STD_FUSE_OPP_VMIN_CORE_4_MASK                                    (0xffffffffU)

#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_RETMODE_MUX_CTRL_SHIFT                          (26U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_RETMODE_MUX_CTRL_MASK                           (0x04000000U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_RETMODE_MUX_CTRL_OCP                             (1U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_RETMODE_MUX_CTRL_EFUSE                           (0U)

#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_RETMODE_VSET_IN_SHIFT                           (21U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_RETMODE_VSET_IN_MASK                            (0x03e00000U)

#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_RETMODE_VSET_OUT_SHIFT                          (16U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_RETMODE_VSET_OUT_MASK                           (0x001f0000U)

#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_ACTMODE_MUX_CTRL_SHIFT                          (10U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_ACTMODE_MUX_CTRL_MASK                           (0x00000400U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_ACTMODE_MUX_CTRL_OCP                             (1U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_ACTMODE_MUX_CTRL_EFUSE                           (0U)

#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_ACTMODE_VSET_IN_SHIFT                           (5U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_ACTMODE_VSET_IN_MASK                            (0x000003e0U)

#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_ACTMODE_VSET_OUT_SHIFT                          (0U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_LDOSRAMCORE_2_ACTMODE_VSET_OUT_MASK                           (0x0000001fU)

#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_RESERVED_0_SHIFT                                              (11U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_RESERVED_0_MASK                                               (0x0000f800U)

#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_RESERVED_1_SHIFT                                              (27U)
#define CTRL_CORE_LDOSRAM_CORE_2_VOLTAGE_CTRL_RESERVED_1_MASK                                               (0xf8000000U)

#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_RETMODE_MUX_CTRL_SHIFT                          (26U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_RETMODE_MUX_CTRL_MASK                           (0x04000000U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_RETMODE_MUX_CTRL_OCP                             (1U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_RETMODE_MUX_CTRL_EFUSE                           (0U)

#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_RETMODE_VSET_IN_SHIFT                           (21U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_RETMODE_VSET_IN_MASK                            (0x03e00000U)

#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_RETMODE_VSET_OUT_SHIFT                          (16U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_RETMODE_VSET_OUT_MASK                           (0x001f0000U)

#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_ACTMODE_MUX_CTRL_SHIFT                          (10U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_ACTMODE_MUX_CTRL_MASK                           (0x00000400U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_ACTMODE_MUX_CTRL_OCP                             (1U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_ACTMODE_MUX_CTRL_EFUSE                           (0U)

#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_ACTMODE_VSET_IN_SHIFT                           (5U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_ACTMODE_VSET_IN_MASK                            (0x000003e0U)

#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_ACTMODE_VSET_OUT_SHIFT                          (0U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_LDOSRAMCORE_3_ACTMODE_VSET_OUT_MASK                           (0x0000001fU)

#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_RESERVED_0_SHIFT                                              (11U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_RESERVED_0_MASK                                               (0x0000f800U)

#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_RESERVED_1_SHIFT                                              (27U)
#define CTRL_CORE_LDOSRAM_CORE_3_VOLTAGE_CTRL_RESERVED_1_MASK                                               (0xf8000000U)

#define CTRL_CORE_NMI_DESTINATION_1_IPU2_C1_SHIFT                                                           (16U)
#define CTRL_CORE_NMI_DESTINATION_1_IPU2_C1_MASK                                                            (0x00ff0000U)
#define CTRL_CORE_NMI_DESTINATION_1_IPU2_C1_ENABLE                                                           (1U)
#define CTRL_CORE_NMI_DESTINATION_1_IPU2_C1_DISABLE                                                          (0U)

#define CTRL_CORE_NMI_DESTINATION_1_IPU2_C0_SHIFT                                                           (8U)
#define CTRL_CORE_NMI_DESTINATION_1_IPU2_C0_MASK                                                            (0x0000ff00U)
#define CTRL_CORE_NMI_DESTINATION_1_IPU2_C0_ENABLE                                                           (1U)
#define CTRL_CORE_NMI_DESTINATION_1_IPU2_C0_DISABLE                                                          (0U)

#define CTRL_CORE_NMI_DESTINATION_1_IPU1_C1_SHIFT                                                           (0U)
#define CTRL_CORE_NMI_DESTINATION_1_IPU1_C1_MASK                                                            (0x000000ffU)
#define CTRL_CORE_NMI_DESTINATION_1_IPU1_C1_ENABLE                                                           (1U)
#define CTRL_CORE_NMI_DESTINATION_1_IPU1_C1_DISABLE                                                          (0U)

#define CTRL_CORE_NMI_DESTINATION_1_RESERVED0_SHIFT                                                         (24U)
#define CTRL_CORE_NMI_DESTINATION_1_RESERVED0_MASK                                                          (0xff000000U)

#define CTRL_CORE_NMI_DESTINATION_2_IPU1_C0_SHIFT                                                           (24U)
#define CTRL_CORE_NMI_DESTINATION_2_IPU1_C0_MASK                                                            (0xff000000U)
#define CTRL_CORE_NMI_DESTINATION_2_IPU1_C0_ENABLE                                                           (1U)
#define CTRL_CORE_NMI_DESTINATION_2_IPU1_C0_DISABLE                                                          (0U)

#define CTRL_CORE_NMI_DESTINATION_2_DSP2_SHIFT                                                              (16U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP2_MASK                                                               (0x00ff0000U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP2_ENABLE                                                              (1U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP2_DISABLE                                                             (0U)

#define CTRL_CORE_NMI_DESTINATION_2_DSP1_SHIFT                                                              (8U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP1_MASK                                                               (0x0000ff00U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP1_ENABLE                                                              (1U)
#define CTRL_CORE_NMI_DESTINATION_2_DSP1_DISABLE                                                             (0U)

#define CTRL_CORE_NMI_DESTINATION_2_MPU_SHIFT                                                               (0U)
#define CTRL_CORE_NMI_DESTINATION_2_MPU_MASK                                                                (0x000000ffU)
#define CTRL_CORE_NMI_DESTINATION_2_MPU_ENABLE                                                               (1U)
#define CTRL_CORE_NMI_DESTINATION_2_MPU_DISABLE                                                              (0U)

#define CTRL_CORE_IP_PRESSURE_MLB_L3_PRESSURE_ENABLE_SHIFT                                                  (2U)
#define CTRL_CORE_IP_PRESSURE_MLB_L3_PRESSURE_ENABLE_MASK                                                   (0x00000004U)
#define CTRL_CORE_IP_PRESSURE_MLB_L3_PRESSURE_ENABLE_ENABLE                                                  (1U)
#define CTRL_CORE_IP_PRESSURE_MLB_L3_PRESSURE_ENABLE_DISABLE                                                 (0U)

#define CTRL_CORE_IP_PRESSURE_MLB_L3_PRESSURE_SHIFT                                                         (0U)
#define CTRL_CORE_IP_PRESSURE_MLB_L3_PRESSURE_MASK                                                          (0x00000003U)
#define CTRL_CORE_IP_PRESSURE_MLB_L3_PRESSURE_LOWEST                                                         (0U)
#define CTRL_CORE_IP_PRESSURE_MLB_L3_PRESSURE_HIGHEST                                                        (3U)

#define CTRL_CORE_IP_PRESSURE_RESERVED0_SHIFT                                                               (3U)
#define CTRL_CORE_IP_PRESSURE_RESERVED0_MASK                                                                (0xfffffff8U)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_0_STD_FUSE_OPP_VDD_DSPEVE_0_SHIFT                                 (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_0_STD_FUSE_OPP_VDD_DSPEVE_0_MASK                                  (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_1_STD_FUSE_OPP_VDD_DSPEVE_1_SHIFT                                 (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_1_STD_FUSE_OPP_VDD_DSPEVE_1_MASK                                  (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_2_STD_FUSE_OPP_VDD_DSPEVE_2_SHIFT                                 (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_2_STD_FUSE_OPP_VDD_DSPEVE_2_MASK                                  (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_3_STD_FUSE_OPP_VDD_DSPEVE_3_SHIFT                                 (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_3_STD_FUSE_OPP_VDD_DSPEVE_3_MASK                                  (0xffffffffU)

#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_4_STD_FUSE_OPP_VDD_DSPEVE_4_SHIFT                                 (0U)
#define CTRL_CORE_STD_FUSE_OPP_VDD_DSPEVE_4_STD_FUSE_OPP_VDD_DSPEVE_4_MASK                                  (0xffffffffU)

#define CTRL_CORE_CUST_FUSE_SWRV_7_CUST_FUSE_SWRV_7_SHIFT                                                   (0U)
#define CTRL_CORE_CUST_FUSE_SWRV_7_CUST_FUSE_SWRV_7_MASK                                                    (0xffffffffU)

#define CTRL_CORE_STD_FUSE_CALIBRATION_OVERRIDE_VALUE_0_STD_FUSE_CALIBRATION_OVERRIDE_VALUE_0_SHIFT         (0U)
#define CTRL_CORE_STD_FUSE_CALIBRATION_OVERRIDE_VALUE_0_STD_FUSE_CALIBRATION_OVERRIDE_VALUE_0_MASK          (0xffffffffU)

#define CTRL_CORE_STD_FUSE_CALIBRATION_OVERRIDE_VALUE_1_STD_FUSE_CALIBRATION_OVERRIDE_VALUE_1_SHIFT         (0U)
#define CTRL_CORE_STD_FUSE_CALIBRATION_OVERRIDE_VALUE_1_STD_FUSE_CALIBRATION_OVERRIDE_VALUE_1_MASK          (0xffffffffU)

#define CTRL_CORE_PCIE_POWER_STATE_BYPASS_EN_APLL_PCIE_SHIFT                                                (31U)
#define CTRL_CORE_PCIE_POWER_STATE_BYPASS_EN_APLL_PCIE_MASK                                                 (0x80000000U)

#define CTRL_CORE_PCIE_POWER_STATE_CLKOOUTEN_APLL_PCIE_SHIFT                                                (30U)
#define CTRL_CORE_PCIE_POWER_STATE_CLKOOUTEN_APLL_PCIE_MASK                                                 (0x40000000U)

#define CTRL_CORE_PCIE_POWER_STATE_EFUSE_TRIM_ACS_PCIE_SHIFT                                                (16U)
#define CTRL_CORE_PCIE_POWER_STATE_EFUSE_TRIM_ACS_PCIE_MASK                                                 (0x03ff0000U)

#define CTRL_CORE_PCIE_POWER_STATE_EFUSE_TRIM_PCIE_PLL_SHIFT                                                (0U)
#define CTRL_CORE_PCIE_POWER_STATE_EFUSE_TRIM_PCIE_PLL_MASK                                                 (0x0000ffffU)

#define CTRL_CORE_PCIE_POWER_STATE_RESERVED_0_SHIFT                                                         (26U)
#define CTRL_CORE_PCIE_POWER_STATE_RESERVED_0_MASK                                                          (0x3c000000U)

#define CTRL_CORE_BOOTSTRAP_RESERVED_0_SHIFT                                                                (16U)
#define CTRL_CORE_BOOTSTRAP_RESERVED_0_MASK                                                                 (0xffff0000U)

#define CTRL_CORE_BOOTSTRAP_BOOTMODE_SHIFT                                                                  (0U)
#define CTRL_CORE_BOOTSTRAP_BOOTMODE_MASK                                                                   (0x0000003fU)

#define CTRL_CORE_BOOTSTRAP_RESERVED_SHIFT                                                                  (6U)
#define CTRL_CORE_BOOTSTRAP_RESERVED_MASK                                                                   (0x000000c0U)

#define CTRL_CORE_BOOTSTRAP_SPEEDSELECT_SHIFT                                                               (8U)
#define CTRL_CORE_BOOTSTRAP_SPEEDSELECT_MASK                                                                (0x00000300U)
#define CTRL_CORE_BOOTSTRAP_SPEEDSELECT_SEL_SYS_32K                                                         (0U)
#define CTRL_CORE_BOOTSTRAP_SPEEDSELECT_SEL_FUNC_32K_1                                                      (1U)
#define CTRL_CORE_BOOTSTRAP_SPEEDSELECT_SEL_FUNC_32K_2                                                      (2U)
#define CTRL_CORE_BOOTSTRAP_SPEEDSELECT_SEL_FUNC_32K_3                                                      (3U)

#define CTRL_CORE_BOOTSTRAP_BOOTWAITEN_SHIFT                                                                (10U)
#define CTRL_CORE_BOOTSTRAP_BOOTWAITEN_MASK                                                                 (0x00000400U)

#define CTRL_CORE_BOOTSTRAP_MUXCS0DEVICE_SHIFT                                                              (11U)
#define CTRL_CORE_BOOTSTRAP_MUXCS0DEVICE_MASK                                                               (0x00001800U)

#define CTRL_CORE_BOOTSTRAP_BOOTDEVICESIZE_SHIFT                                                            (13U)
#define CTRL_CORE_BOOTSTRAP_BOOTDEVICESIZE_MASK                                                             (0x00002000U)

#define CTRL_CORE_BOOTSTRAP_RESERVED1_SHIFT                                                                 (14U)
#define CTRL_CORE_BOOTSTRAP_RESERVED1_MASK                                                                  (0x00004000U)

#define CTRL_CORE_BOOTSTRAP_DSP_CLOCK_DIVIDER_SHIFT                                                         (15U)
#define CTRL_CORE_BOOTSTRAP_DSP_CLOCK_DIVIDER_MASK                                                          (0x00008000U)

#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_NC_IN_SHIFT                                                           (16U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_NC_IN_MASK                                                            (0x003f0000U)

#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_PC_IN_SHIFT                                                           (8U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_PC_IN_MASK                                                            (0x00003f00U)

#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_REMOVE_SKEW_SHIFT                                                     (6U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_REMOVE_SKEW_MASK                                                      (0x00000040U)

#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_PWRDNRX_SHIFT                                                         (5U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_PWRDNRX_MASK                                                          (0x00000020U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_PWRDNRX_POWEREDOFF                                                     (1U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_PWRDNRX_POWEREDON                                                      (0U)

#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_PWRDNTX_SHIFT                                                         (4U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_PWRDNTX_MASK                                                          (0x00000010U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_PWRDNTX_POWEREDOFF                                                     (1U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_PWRDNTX_POWEREDON                                                      (0U)

#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_EN_EXT_RES_SHIFT                                                      (3U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_EN_EXT_RES_MASK                                                       (0x00000008U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_EN_EXT_RES_ENABLEEXTERNALRESISTORS                                     (1U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_SIG_EN_EXT_RES_DISABLEEXTERNALRESISTORS                                    (0U)

#define CTRL_CORE_MLB_SIG_IO_CTRL_RESERVED0_SHIFT                                                           (2U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_RESERVED0_MASK                                                            (0x0000001cU)
#define CTRL_CORE_MLB_SIG_IO_CTRL_RESERVED0_ENABLE                                                           (1U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_RESERVED0_DISABLE                                                          (0U)

#define CTRL_CORE_MLB_SIG_IO_CTRL_RESERVED1_SHIFT                                                           (7U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_RESERVED1_MASK                                                            (0x00000080U)

#define CTRL_CORE_MLB_SIG_IO_CTRL_RESERVED2_SHIFT                                                           (14U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_RESERVED2_MASK                                                            (0x0000c000U)

#define CTRL_CORE_MLB_SIG_IO_CTRL_RESERVED3_SHIFT                                                           (22U)
#define CTRL_CORE_MLB_SIG_IO_CTRL_RESERVED3_MASK                                                            (0xffc00000U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_NC_IN_SHIFT                                                           (16U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_NC_IN_MASK                                                            (0x003f0000U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_PC_IN_SHIFT                                                           (8U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_PC_IN_MASK                                                            (0x00003f00U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_REMOVE_SKEW_SHIFT                                                     (6U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_REMOVE_SKEW_MASK                                                      (0x00000040U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_PWRDNRX_SHIFT                                                         (5U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_PWRDNRX_MASK                                                          (0x00000020U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_PWRDNRX_POWEREDOFF                                                     (1U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_PWRDNRX_POWEREDON                                                      (0U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_PWRDNTX_SHIFT                                                         (4U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_PWRDNTX_MASK                                                          (0x00000010U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_PWRDNTX_POWEREDOFF                                                     (1U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_PWRDNTX_POWEREDON                                                      (0U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_EN_EXT_RES_SHIFT                                                      (3U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_EN_EXT_RES_MASK                                                       (0x00000008U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_EN_EXT_RES_ENABLEEXTERNALRESISTORS                                     (1U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_EN_EXT_RES_DISABLEEXTERNALRESISTORS                                    (0U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_ENN_SHIFT                                                             (1U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_ENN_MASK                                                              (0x00000002U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_ENN_ENABLE                                                             (1U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_ENN_DISABLE                                                            (0U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_ENP_SHIFT                                                             (0U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_ENP_MASK                                                              (0x00000001U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_ENP_ENABLE                                                             (1U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_DAT_ENP_DISABLE                                                            (0U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_RESERVED_0_SHIFT                                                          (7U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_RESERVED_0_MASK                                                           (0x00000080U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_RESERVED_1_SHIFT                                                          (14U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_RESERVED_1_MASK                                                           (0x0000c000U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_RESERVED_2_SHIFT                                                          (22U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_RESERVED_2_MASK                                                           (0xffc00000U)

#define CTRL_CORE_MLB_DAT_IO_CTRL_RESERVED_3_SHIFT                                                          (0U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_RESERVED_3_MASK                                                           (0x00000007U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_RESERVED_3_ENABLE                                                          (1U)
#define CTRL_CORE_MLB_DAT_IO_CTRL_RESERVED_3_DISABLE                                                         (0U)

#define CTRL_CORE_MLB_CLK_BG_CTRL_RESERVED_SHIFT                                                            (17U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_RESERVED_MASK                                                             (0x003e0000U)

#define CTRL_CORE_MLB_CLK_BG_CTRL_T_HYSTERISIS_EN_SHIFT                                                     (16U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_T_HYSTERISIS_EN_MASK                                                      (0x00010000U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_T_HYSTERISIS_EN_ENABLE                                                     (1U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_T_HYSTERISIS_EN_DISABLE                                                    (0U)

#define CTRL_CORE_MLB_CLK_BG_CTRL_BG_TRIM_SHIFT                                                             (2U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_BG_TRIM_MASK                                                              (0x000000fcU)

#define CTRL_CORE_MLB_CLK_BG_CTRL_BG_PWRDN_SHIFT                                                            (1U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_BG_PWRDN_MASK                                                             (0x00000002U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_BG_PWRDN_ENABLE                                                            (1U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_BG_PWRDN_DISABLE                                                           (0U)

#define CTRL_CORE_MLB_CLK_BG_CTRL_CLK_PWRDN_SHIFT                                                           (0U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_CLK_PWRDN_MASK                                                            (0x00000001U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_CLK_PWRDN_ENABLE                                                           (1U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_CLK_PWRDN_DISABLE                                                          (0U)

#define CTRL_CORE_MLB_CLK_BG_CTRL_RESERVED_0_SHIFT                                                          (8U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_RESERVED_0_MASK                                                           (0x0000ff00U)

#define CTRL_CORE_MLB_CLK_BG_CTRL_RESERVED_1_SHIFT                                                          (22U)
#define CTRL_CORE_MLB_CLK_BG_CTRL_RESERVED_1_MASK                                                           (0xffc00000U)

#define CTRL_CORE_CORTEX_M4_MMUADDRTRANSLTR_RESERVED_0_SHIFT                                                (20U)
#define CTRL_CORE_CORTEX_M4_MMUADDRTRANSLTR_RESERVED_0_MASK                                                 (0xfff00000U)

#define CTRL_CORE_CORTEX_M4_MMUADDRTRANSLTR_CORTEX_M4_MMUADDRTRANSLTR_SHIFT                                 (0U)
#define CTRL_CORE_CORTEX_M4_MMUADDRTRANSLTR_CORTEX_M4_MMUADDRTRANSLTR_MASK                                  (0x000fffffU)

#define CTRL_CORE_CORTEX_M4_MMUADDRLOGICTR_RESERVED_0_SHIFT                                                 (20U)
#define CTRL_CORE_CORTEX_M4_MMUADDRLOGICTR_RESERVED_0_MASK                                                  (0xfff00000U)

#define CTRL_CORE_CORTEX_M4_MMUADDRLOGICTR_CORTEX_M4_MMUADDRLOGICTR_SHIFT                                   (0U)
#define CTRL_CORE_CORTEX_M4_MMUADDRLOGICTR_CORTEX_M4_MMUADDRLOGICTR_MASK                                    (0x000fffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_CTRL_CORE_H_ */
