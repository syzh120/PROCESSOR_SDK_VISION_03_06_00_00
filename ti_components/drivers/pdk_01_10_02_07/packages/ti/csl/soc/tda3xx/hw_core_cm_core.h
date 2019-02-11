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
 *  \file   hw_core_cm_core.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_CORE_CM_CORE_H_
#define HW_CORE_CM_CORE_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define CM_L3MAIN1_CLKSTCTRL                                   (0x0U)
#define CM_L3MAIN1_DYNAMICDEP                                       (0x8U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL                           (0x20U)
#define CM_L3MAIN1_GPMC_CLKCTRL                                (0x28U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL                            (0x30U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL                           (0x50U)
#define CM_L3MAIN1_TESOC_CLKCTRL                                    (0x58U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL                            (0x68U)
#define CM_L3MAIN1_TPCC_CLKCTRL                                (0x70U)
#define CM_L3MAIN1_TPTC1_CLKCTRL                               (0x78U)
#define CM_L3MAIN1_TPTC2_CLKCTRL                               (0x80U)
#define CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL                      (0xd0U)
#define CM_IPU2_CLKCTRL                                             (0x220U)
#define CM_DMA_CLKSTCTRL                                       (0x300U)
#define CM_DMA_DYNAMICDEP                                      (0x308U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL                                                                           (0x320U)
#define CM_EMIF_CLKSTCTRL                                      (0x400U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL                                                                         (0x428U)
#define CM_EMIF_EMIF1_CLKCTRL                                  (0x430U)
#define CM_EMIF_EMIF_DLL_CLKCTRL                                                                            (0x440U)
#define CM_CRC_CRC_CLKCTRL                                                                                  (0x500U)
#define CM_CRC_CLKSTCTRL                                            (0x520U)
#define CM_L4CFG_CLKSTCTRL                                     (0x600U)
#define CM_L4CFG_DYNAMICDEP                                         (0x608U)
#define CM_L4CFG_L4_CFG_CLKCTRL                                (0x620U)
#define CM_L4CFG_SPINLOCK_CLKCTRL                              (0x628U)
#define CM_L4CFG_MAILBOX1_CLKCTRL                              (0x630U)
#define CM_L4CFG_MAILBOX2_CLKCTRL                              (0x648U)
#define CM_L4CFG_MAILBOX6_CLKCTRL                              (0x668U)
#define CM_L3INSTR_CLKSTCTRL                                   (0x700U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL                           (0x720U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL                            (0x728U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL                          (0x740U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL                           (0x748U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL                 (0x750U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_SHIFT                                       (0U)
#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_MASK                                        (0x00000003U)
#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                     (0U)
#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                   (1U)
#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_RESERVED_2                                   (2U)
#define CM_L3MAIN1_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                      (3U)

#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_SHIFT                                             (8U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_MASK                                              (0x00000100U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_INACT                                              (0U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L3_GICLK_ACT                                                (1U)

#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L4_GICLK_SHIFT                                             (9U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L4_GICLK_MASK                                              (0x00000200U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L4_GICLK_INACT                                              (0U)
#define CM_L3MAIN1_CLKSTCTRL_CLKACTIVITY_L3MAIN1_L4_GICLK_ACT                                                (1U)

#define CM_L3MAIN1_DYNAMICDEP_EMIF_DYNDEP_SHIFT                                         (4U)
#define CM_L3MAIN1_DYNAMICDEP_EMIF_DYNDEP_MASK                                          (0x00000010U)
#define CM_L3MAIN1_DYNAMICDEP_EMIF_DYNDEP_ENABLED                                        (1U)

#define CM_L3MAIN1_DYNAMICDEP_WINDOWSIZE_SHIFT                                          (24U)
#define CM_L3MAIN1_DYNAMICDEP_WINDOWSIZE_MASK                                           (0x0f000000U)

#define CM_L3MAIN1_DYNAMICDEP_L4CFG_DYNDEP_SHIFT                                        (12U)
#define CM_L3MAIN1_DYNAMICDEP_L4CFG_DYNDEP_MASK                                         (0x00001000U)
#define CM_L3MAIN1_DYNAMICDEP_L4CFG_DYNDEP_ENABLED                                       (1U)

#define CM_L3MAIN1_DYNAMICDEP_WKUPAON_DYNDEP_SHIFT                                      (15U)
#define CM_L3MAIN1_DYNAMICDEP_WKUPAON_DYNDEP_MASK                                       (0x00008000U)
#define CM_L3MAIN1_DYNAMICDEP_WKUPAON_DYNDEP_ENABLED                                     (1U)

#define CM_L3MAIN1_DYNAMICDEP_DSP1_DYNDEP_SHIFT                                         (1U)
#define CM_L3MAIN1_DYNAMICDEP_DSP1_DYNDEP_MASK                                          (0x00000002U)
#define CM_L3MAIN1_DYNAMICDEP_DSP1_DYNDEP_ENABLED                                        (1U)

#define CM_L3MAIN1_DYNAMICDEP_DSP2_DYNDEP_SHIFT                                         (20U)
#define CM_L3MAIN1_DYNAMICDEP_DSP2_DYNDEP_MASK                                          (0x00100000U)
#define CM_L3MAIN1_DYNAMICDEP_DSP2_DYNDEP_ENABLED                                        (1U)

#define CM_L3MAIN1_DYNAMICDEP_DSS_DYNDEP_SHIFT                                          (8U)
#define CM_L3MAIN1_DYNAMICDEP_DSS_DYNDEP_MASK                                           (0x00000100U)
#define CM_L3MAIN1_DYNAMICDEP_DSS_DYNDEP_ENABLED                                         (1U)

#define CM_L3MAIN1_DYNAMICDEP_EVE1_DYNDEP_SHIFT                                         (28U)
#define CM_L3MAIN1_DYNAMICDEP_EVE1_DYNDEP_MASK                                          (0x10000000U)
#define CM_L3MAIN1_DYNAMICDEP_EVE1_DYNDEP_ENABLED                                        (1U)

#define CM_L3MAIN1_DYNAMICDEP_GPU_DYNDEP_SHIFT                                          (10U)
#define CM_L3MAIN1_DYNAMICDEP_GPU_DYNDEP_MASK                                           (0x00000400U)
#define CM_L3MAIN1_DYNAMICDEP_GPU_DYNDEP_ENABLED                                         (1U)

#define CM_L3MAIN1_DYNAMICDEP_IPU1_DYNDEP_SHIFT                                         (18U)
#define CM_L3MAIN1_DYNAMICDEP_IPU1_DYNDEP_MASK                                          (0x00040000U)
#define CM_L3MAIN1_DYNAMICDEP_IPU1_DYNDEP_ENABLED                                        (1U)

#define CM_L3MAIN1_DYNAMICDEP_IPU_DYNDEP_SHIFT                                          (3U)
#define CM_L3MAIN1_DYNAMICDEP_IPU_DYNDEP_MASK                                           (0x00000008U)
#define CM_L3MAIN1_DYNAMICDEP_IPU_DYNDEP_ENABLED                                         (1U)

#define CM_L3MAIN1_DYNAMICDEP_L4PER_DYNDEP_SHIFT                                        (13U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER_DYNDEP_MASK                                         (0x00002000U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER_DYNDEP_ENABLED                                       (1U)

#define CM_L3MAIN1_DYNAMICDEP_L4PER2_DYNDEP_SHIFT                                       (22U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER2_DYNDEP_MASK                                        (0x00400000U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER2_DYNDEP_ENABLED                                      (1U)

#define CM_L3MAIN1_DYNAMICDEP_L4PER3_DYNDEP_SHIFT                                       (23U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER3_DYNDEP_MASK                                        (0x00800000U)
#define CM_L3MAIN1_DYNAMICDEP_L4PER3_DYNDEP_ENABLED                                      (1U)

#define CM_L3MAIN1_DYNAMICDEP_L4SEC_DYNDEP_SHIFT                                        (14U)
#define CM_L3MAIN1_DYNAMICDEP_L4SEC_DYNDEP_MASK                                         (0x00004000U)
#define CM_L3MAIN1_DYNAMICDEP_L4SEC_DYNDEP_ENABLED                                       (1U)

#define CM_L3MAIN1_DYNAMICDEP_PCIE_DYNDEP_SHIFT                                         (21U)
#define CM_L3MAIN1_DYNAMICDEP_PCIE_DYNDEP_MASK                                          (0x00200000U)
#define CM_L3MAIN1_DYNAMICDEP_PCIE_DYNDEP_ENABLED                                        (1U)

#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_MODULEMODE_SHIFT                              (0U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_MODULEMODE_MASK                               (0x00000003U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_MODULEMODE_AUTO                                (1U)

#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_SHIFT                                  (16U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_MASK                                   (0x00030000U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_DISABLE                                 (3U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_IDLE                                    (2U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_FUNC                                    (0U)
#define CM_L3MAIN1_L3_MAIN_1_CLKCTRL_IDLEST_TRANS                                   (1U)

#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_SHIFT                                       (16U)
#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_MASK                                        (0x00030000U)
#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_DISABLE                                      (3U)
#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_IDLE                                         (2U)
#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_FUNC                                         (0U)
#define CM_L3MAIN1_GPMC_CLKCTRL_IDLEST_TRANS                                        (1U)

#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_SHIFT                                   (0U)
#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_MASK                                    (0x00000003U)
#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_DISABLED                                 (0U)
#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_AUTO                                     (1U)
#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_RESERVED_2                               (2U)
#define CM_L3MAIN1_GPMC_CLKCTRL_MODULEMODE_RESERVED                                 (3U)

#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_MODULEMODE_SHIFT                               (0U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_MODULEMODE_MASK                                (0x00000003U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_MODULEMODE_AUTO                                 (1U)

#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_SHIFT                                   (16U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_MASK                                    (0x00030000U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_DISABLE                                  (3U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_IDLE                                     (2U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_FUNC                                     (0U)
#define CM_L3MAIN1_MMU_EDMA_CLKCTRL_IDLEST_TRANS                                    (1U)

#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_MODULEMODE_SHIFT                              (0U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_MODULEMODE_MASK                               (0x00000003U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_MODULEMODE_AUTO                                (1U)

#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_SHIFT                                  (16U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_MASK                                   (0x00030000U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_DISABLE                                 (3U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_IDLE                                    (2U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_FUNC                                    (0U)
#define CM_L3MAIN1_OCMC_RAM1_CLKCTRL_IDLEST_TRANS                                   (1U)

#define CM_L3MAIN1_TESOC_CLKCTRL_MODULEMODE_SHIFT                                       (0U)
#define CM_L3MAIN1_TESOC_CLKCTRL_MODULEMODE_MASK                                        (0x00000003U)
#define CM_L3MAIN1_TESOC_CLKCTRL_MODULEMODE_AUTO                                         (1U)

#define CM_L3MAIN1_TESOC_CLKCTRL_IDLEST_SHIFT                                           (16U)
#define CM_L3MAIN1_TESOC_CLKCTRL_IDLEST_MASK                                            (0x00030000U)
#define CM_L3MAIN1_TESOC_CLKCTRL_IDLEST_DISABLE                                          (3U)
#define CM_L3MAIN1_TESOC_CLKCTRL_IDLEST_IDLE                                             (2U)
#define CM_L3MAIN1_TESOC_CLKCTRL_IDLEST_FUNC                                             (0U)
#define CM_L3MAIN1_TESOC_CLKCTRL_IDLEST_TRANS                                            (1U)

#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_MODULEMODE_SHIFT                               (0U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_MODULEMODE_MASK                                (0x00000003U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_MODULEMODE_AUTO                                 (1U)

#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_SHIFT                                   (16U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_MASK                                    (0x00030000U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_DISABLE                                  (3U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_IDLE                                     (2U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_FUNC                                     (0U)
#define CM_L3MAIN1_OCMC_ROM_CLKCTRL_IDLEST_TRANS                                    (1U)

#define CM_L3MAIN1_TPCC_CLKCTRL_MODULEMODE_SHIFT                                   (0U)
#define CM_L3MAIN1_TPCC_CLKCTRL_MODULEMODE_MASK                                    (0x00000003U)
#define CM_L3MAIN1_TPCC_CLKCTRL_MODULEMODE_AUTO                                     (1U)

#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_SHIFT                                       (16U)
#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_MASK                                        (0x00030000U)
#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_DISABLE                                      (3U)
#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_IDLE                                         (2U)
#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_FUNC                                         (0U)
#define CM_L3MAIN1_TPCC_CLKCTRL_IDLEST_TRANS                                        (1U)

#define CM_L3MAIN1_TPTC1_CLKCTRL_STBYST_SHIFT                                      (18U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_STBYST_MASK                                       (0x00040000U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_STBYST_FUNC                                        (0U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_STBYST_STANDBY                                     (1U)

#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_SHIFT                                      (16U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_MASK                                       (0x00030000U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_DISABLE                                     (3U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_IDLE                                        (2U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_FUNC                                        (0U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_IDLEST_TRANS                                       (1U)

#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_SHIFT                                  (0U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_MASK                                   (0x00000003U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_DISABLED                                (0U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_AUTO                                    (1U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_RESERVED_2                              (2U)
#define CM_L3MAIN1_TPTC1_CLKCTRL_MODULEMODE_RESERVED                                (3U)

#define CM_L3MAIN1_TPTC2_CLKCTRL_STBYST_SHIFT                                      (18U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_STBYST_MASK                                       (0x00040000U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_STBYST_FUNC                                        (0U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_STBYST_STANDBY                                     (1U)

#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_SHIFT                                      (16U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_MASK                                       (0x00030000U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_DISABLE                                     (3U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_IDLE                                        (2U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_FUNC                                        (0U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_IDLEST_TRANS                                       (1U)

#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_SHIFT                                  (0U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_MASK                                   (0x00000003U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_DISABLED                                (0U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_AUTO                                    (1U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_RESERVED_2                              (2U)
#define CM_L3MAIN1_TPTC2_CLKCTRL_MODULEMODE_RESERVED                                (3U)

#define CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL_IDLEST_SHIFT                             (16U)
#define CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL_IDLEST_MASK                              (0x00030000U)
#define CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL_IDLEST_DISABLE                            (3U)
#define CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL_IDLEST_IDLE                               (2U)
#define CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL_IDLEST_FUNC                               (0U)
#define CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL_IDLEST_TRANS                              (1U)

#define CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL_MODULEMODE_SHIFT                         (0U)
#define CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL_MODULEMODE_MASK                          (0x00000003U)
#define CM_L3MAIN1_SPARE_UNKNOWN6_CLKCTRL_MODULEMODE_AUTO                           (1U)

#define CM_IPU2_IPU2_CLKCTRL_STBYST_SHIFT                                                                   (18U)
#define CM_IPU2_IPU2_CLKCTRL_STBYST_MASK                                                                    (0x00040000U)
#define CM_IPU2_IPU2_CLKCTRL_STBYST_FUNC                                                                     (0U)
#define CM_IPU2_IPU2_CLKCTRL_STBYST_STANDBY                                                                  (1U)

#define CM_IPU2_IPU2_CLKCTRL_IDLEST_SHIFT                                                                   (16U)
#define CM_IPU2_IPU2_CLKCTRL_IDLEST_MASK                                                                    (0x00030000U)
#define CM_IPU2_IPU2_CLKCTRL_IDLEST_DISABLE                                                                  (3U)
#define CM_IPU2_IPU2_CLKCTRL_IDLEST_IDLE                                                                     (2U)
#define CM_IPU2_IPU2_CLKCTRL_IDLEST_FUNC                                                                     (0U)
#define CM_IPU2_IPU2_CLKCTRL_IDLEST_TRANS                                                                    (1U)

#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_SHIFT                                                               (0U)
#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_MASK                                                                (0x00000003U)
#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_DISABLED                                                             (0U)
#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_AUTO                                                                 (1U)
#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_RESERVED_2                                                           (2U)
#define CM_IPU2_IPU2_CLKCTRL_MODULEMODE_RESERVED                                                             (3U)

#define CM_DMA_CLKSTCTRL_CLKTRCTRL_SHIFT                                           (0U)
#define CM_DMA_CLKSTCTRL_CLKTRCTRL_MASK                                            (0x00000003U)
#define CM_DMA_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                         (0U)
#define CM_DMA_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                       (1U)
#define CM_DMA_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                          (2U)
#define CM_DMA_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                          (3U)

#define CM_DMA_CLKSTCTRL_CLKACTIVITY_DMA_L3_GICLK_SHIFT                                                     (8U)
#define CM_DMA_CLKSTCTRL_CLKACTIVITY_DMA_L3_GICLK_MASK                                                      (0x00000100U)
#define CM_DMA_CLKSTCTRL_CLKACTIVITY_DMA_L3_GICLK_INACT                                                      (0U)
#define CM_DMA_CLKSTCTRL_CLKACTIVITY_DMA_L3_GICLK_ACT                                                        (1U)

#define CM_DMA_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT                                     (5U)
#define CM_DMA_DYNAMICDEP_L3MAIN1_DYNDEP_MASK                                      (0x00000020U)
#define CM_DMA_DYNAMICDEP_L3MAIN1_DYNDEP_DISABLED                                   (0U)

#define CM_DMA_DMA_SYSTEM_CLKCTRL_MODULEMODE_SHIFT                                                          (0U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_MODULEMODE_MASK                                                           (0x00000003U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_MODULEMODE_AUTO                                                            (1U)

#define CM_DMA_DMA_SYSTEM_CLKCTRL_STBYST_SHIFT                                                              (18U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_STBYST_MASK                                                               (0x00040000U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_STBYST_FUNC                                                                (0U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_STBYST_STANDBY                                                             (1U)

#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_SHIFT                                                              (16U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_MASK                                                               (0x00030000U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_DISABLE                                                             (3U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_IDLE                                                                (2U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_FUNC                                                                (0U)
#define CM_DMA_DMA_SYSTEM_CLKCTRL_IDLEST_TRANS                                                               (1U)

#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_SHIFT                                          (0U)
#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_MASK                                           (0x00000003U)
#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                        (0U)
#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                      (1U)
#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                         (3U)
#define CM_EMIF_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                         (2U)

#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_L3_GICLK_SHIFT                                                   (8U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_L3_GICLK_MASK                                                    (0x00000100U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_L3_GICLK_INACT                                                    (0U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_L3_GICLK_ACT                                                      (1U)

#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_DLL_GCLK_SHIFT                                                   (9U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_DLL_GCLK_MASK                                                    (0x00000200U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_DLL_GCLK_INACT                                                    (0U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_DLL_GCLK_ACT                                                      (1U)

#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_PHY_GCLK_SHIFT                                                   (10U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_PHY_GCLK_MASK                                                    (0x00000400U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_PHY_GCLK_INACT                                                    (0U)
#define CM_EMIF_CLKSTCTRL_CLKACTIVITY_EMIF_PHY_GCLK_ACT                                                      (1U)

#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_MODULEMODE_SHIFT                                                        (0U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_MODULEMODE_MASK                                                         (0x00000003U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_MODULEMODE_AUTO                                                          (1U)

#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_SHIFT                                                            (16U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_MASK                                                             (0x00030000U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_DISABLE                                                           (3U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_IDLE                                                              (2U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_FUNC                                                              (0U)
#define CM_EMIF_EMIF_OCP_FW_CLKCTRL_IDLEST_TRANS                                                             (1U)

#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_SHIFT                                         (16U)
#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_MASK                                          (0x00030000U)
#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_DISABLE                                        (3U)
#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_IDLE                                           (2U)
#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_FUNC                                           (0U)
#define CM_EMIF_EMIF1_CLKCTRL_IDLEST_TRANS                                          (1U)

#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_SHIFT                                     (0U)
#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_MASK                                      (0x00000003U)
#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_DISABLED                                   (0U)
#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_AUTO                                       (1U)
#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_RESERVED_2                                 (2U)
#define CM_EMIF_EMIF1_CLKCTRL_MODULEMODE_RESERVED                                   (3U)

#define CM_EMIF_EMIF1_CLKCTRL_CLKSEL_LL_SHIFT                                      (24U)
#define CM_EMIF_EMIF1_CLKCTRL_CLKSEL_LL_MASK                                       (0x01000000U)
#define CM_EMIF_EMIF1_CLKCTRL_CLKSEL_LL_SEL_C2C                                     (0U)
#define CM_EMIF_EMIF1_CLKCTRL_CLKSEL_LL_SEL_LLI                                     (1U)

#define CM_EMIF_EMIF_DLL_CLKCTRL_OPTFCLKEN_DLL_CLK_SHIFT                                                    (8U)
#define CM_EMIF_EMIF_DLL_CLKCTRL_OPTFCLKEN_DLL_CLK_MASK                                                     (0x00000100U)
#define CM_EMIF_EMIF_DLL_CLKCTRL_OPTFCLKEN_DLL_CLK_FCLK_EN                                                   (1U)
#define CM_EMIF_EMIF_DLL_CLKCTRL_OPTFCLKEN_DLL_CLK_FCLK_DIS                                                  (0U)

#define CM_CRC_CRC_CLKCTRL_IDLEST_SHIFT                                                     (16U)
#define CM_CRC_CRC_CLKCTRL_IDLEST_MASK                                                      (0x00030000U)
#define CM_CRC_CRC_CLKCTRL_IDLEST_DISABLE                                                    (3U)
#define CM_CRC_CRC_CLKCTRL_IDLEST_IDLE                                                       (2U)
#define CM_CRC_CRC_CLKCTRL_IDLEST_FUNC                                                       (0U)
#define CM_CRC_CRC_CLKCTRL_IDLEST_TRANS                                                      (1U)

#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE1_SHIFT                                             (24U)
#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE1_MASK                                              (0x03000000U)
#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE1_SEL_VIDEO1_CLK                                     (1U)
#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE1_SEL_VIDEO2_CLK                                     (2U)
#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE1_SEL_HDMI_CLK                                       (3U)
#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE1_SEL_FUNC_32K_CLK                                   (0U)

#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE2_SHIFT                                             (26U)
#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE2_MASK                                              (0x0c000000U)
#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE2_SEL_L3_ICLK                                        (0U)
#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE2_SEL_PER_ABE_X1_CLK                                 (1U)
#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE2_SEL_DPLL_CLK                                       (2U)
#define CM_CRC_CRC_CLKCTRL_CLKSEL_SOURCE2_RESERVED                                           (3U)

#define CM_CRC_CRC_CLKCTRL_MODULEMODE_SHIFT                                                                 (0U)
#define CM_CRC_CRC_CLKCTRL_MODULEMODE_MASK                                                                  (0x00000003U)
#define CM_CRC_CRC_CLKCTRL_MODULEMODE_DISABLED                                                               (0U)
#define CM_CRC_CRC_CLKCTRL_MODULEMODE_RESERVED_1                                                             (1U)
#define CM_CRC_CRC_CLKCTRL_MODULEMODE_ENABLE                                                                 (2U)
#define CM_CRC_CRC_CLKCTRL_MODULEMODE_RESERVED                                                               (3U)

#define CM_CRC_CLKSTCTRL_CLKTRCTRL_SHIFT                                                (0U)
#define CM_CRC_CLKSTCTRL_CLKTRCTRL_MASK                                                 (0x00000003U)
#define CM_CRC_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                              (0U)
#define CM_CRC_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                            (1U)
#define CM_CRC_CLKSTCTRL_CLKTRCTRL_SW_WKUP                                               (2U)
#define CM_CRC_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                               (3U)

#define CM_CRC_CLKSTCTRL_CLKACTIVITY_CRC_L3_GICLK_SHIFT                                 (8U)
#define CM_CRC_CLKSTCTRL_CLKACTIVITY_CRC_L3_GICLK_MASK                                  (0x00000100U)
#define CM_CRC_CLKSTCTRL_CLKACTIVITY_CRC_L3_GICLK_INACT                                  (0U)
#define CM_CRC_CLKSTCTRL_CLKACTIVITY_CRC_L3_GICLK_ACT                                    (1U)

#define CM_CRC_CLKSTCTRL_CLKACTIVITY_CRC_GFCLK_SHIFT                                    (9U)
#define CM_CRC_CLKSTCTRL_CLKACTIVITY_CRC_GFCLK_MASK                                     (0x00000200U)
#define CM_CRC_CLKSTCTRL_CLKACTIVITY_CRC_GFCLK_INACT                                     (0U)
#define CM_CRC_CLKSTCTRL_CLKACTIVITY_CRC_GFCLK_ACT                                       (1U)

#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_SHIFT                                         (0U)
#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_MASK                                          (0x00000003U)
#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_NO_SLEEP                                       (0U)
#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_RESERVED_1                                     (1U)
#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_RESERVED_2                                     (2U)
#define CM_L4CFG_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                        (3U)

#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_SHIFT                                                 (8U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_MASK                                                  (0x00000100U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_INACT                                                  (0U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L4_GICLK_ACT                                                    (1U)

#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_SHIFT                                                 (9U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_MASK                                                  (0x00000200U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_INACT                                                  (0U)
#define CM_L4CFG_CLKSTCTRL_CLKACTIVITY_L4CFG_L3_GICLK_ACT                                                    (1U)

#define CM_L4CFG_DYNAMICDEP_EMIF_DYNDEP_SHIFT                                           (4U)
#define CM_L4CFG_DYNAMICDEP_EMIF_DYNDEP_MASK                                            (0x00000010U)
#define CM_L4CFG_DYNAMICDEP_EMIF_DYNDEP_ENABLED                                          (1U)

#define CM_L4CFG_DYNAMICDEP_L3INIT_DYNDEP_SHIFT                                         (7U)
#define CM_L4CFG_DYNAMICDEP_L3INIT_DYNDEP_MASK                                          (0x00000080U)
#define CM_L4CFG_DYNAMICDEP_L3INIT_DYNDEP_ENABLED                                        (1U)

#define CM_L4CFG_DYNAMICDEP_COREAON_DYNDEP_SHIFT                                        (16U)
#define CM_L4CFG_DYNAMICDEP_COREAON_DYNDEP_MASK                                         (0x00010000U)
#define CM_L4CFG_DYNAMICDEP_COREAON_DYNDEP_ENABLED                                       (1U)

#define CM_L4CFG_DYNAMICDEP_CUSTEFUSE_DYNDEP_SHIFT                                      (17U)
#define CM_L4CFG_DYNAMICDEP_CUSTEFUSE_DYNDEP_MASK                                       (0x00020000U)
#define CM_L4CFG_DYNAMICDEP_CUSTEFUSE_DYNDEP_ENABLED                                     (1U)

#define CM_L4CFG_DYNAMICDEP_SDMA_DYNDEP_SHIFT                                           (11U)
#define CM_L4CFG_DYNAMICDEP_SDMA_DYNDEP_MASK                                            (0x00000800U)
#define CM_L4CFG_DYNAMICDEP_SDMA_DYNDEP_ENABLED                                          (1U)

#define CM_L4CFG_DYNAMICDEP_L3MAIN1_DYNDEP_SHIFT                                        (5U)
#define CM_L4CFG_DYNAMICDEP_L3MAIN1_DYNDEP_MASK                                         (0x00000020U)
#define CM_L4CFG_DYNAMICDEP_L3MAIN1_DYNDEP_ENABLED                                       (1U)

#define CM_L4CFG_DYNAMICDEP_WINDOWSIZE_SHIFT                                            (24U)
#define CM_L4CFG_DYNAMICDEP_WINDOWSIZE_MASK                                             (0x0f000000U)

#define CM_L4CFG_L4_CFG_CLKCTRL_MODULEMODE_SHIFT                                   (0U)
#define CM_L4CFG_L4_CFG_CLKCTRL_MODULEMODE_MASK                                    (0x00000003U)
#define CM_L4CFG_L4_CFG_CLKCTRL_MODULEMODE_AUTO                                     (1U)

#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_SHIFT                                       (16U)
#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_MASK                                        (0x00030000U)
#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_DISABLE                                      (3U)
#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_IDLE                                         (2U)
#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_FUNC                                         (0U)
#define CM_L4CFG_L4_CFG_CLKCTRL_IDLEST_TRANS                                        (1U)

#define CM_L4CFG_SPINLOCK_CLKCTRL_MODULEMODE_SHIFT                                 (0U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_MODULEMODE_MASK                                  (0x00000003U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_MODULEMODE_AUTO                                   (1U)

#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_SHIFT                                     (16U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_MASK                                      (0x00030000U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_DISABLE                                    (3U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_IDLE                                       (2U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_FUNC                                       (0U)
#define CM_L4CFG_SPINLOCK_CLKCTRL_IDLEST_TRANS                                      (1U)

#define CM_L4CFG_MAILBOX1_CLKCTRL_MODULEMODE_SHIFT                                 (0U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_MODULEMODE_MASK                                  (0x00000003U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_MODULEMODE_AUTO                                   (1U)

#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_SHIFT                                     (16U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_MASK                                      (0x00030000U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_DISABLE                                    (3U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_IDLE                                       (2U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_FUNC                                       (0U)
#define CM_L4CFG_MAILBOX1_CLKCTRL_IDLEST_TRANS                                      (1U)

#define CM_L4CFG_MAILBOX2_CLKCTRL_MODULEMODE_SHIFT                                 (0U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_MODULEMODE_MASK                                  (0x00000003U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_MODULEMODE_AUTO                                   (1U)

#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_SHIFT                                     (16U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_MASK                                      (0x00030000U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_DISABLE                                    (3U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_IDLE                                       (2U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_FUNC                                       (0U)
#define CM_L4CFG_MAILBOX2_CLKCTRL_IDLEST_TRANS                                      (1U)

#define CM_L4CFG_MAILBOX6_CLKCTRL_MODULEMODE_SHIFT                                 (0U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_MODULEMODE_MASK                                  (0x00000003U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_MODULEMODE_AUTO                                   (1U)

#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_SHIFT                                     (16U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_MASK                                      (0x00030000U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_DISABLE                                    (3U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_IDLE                                       (2U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_FUNC                                       (0U)
#define CM_L4CFG_MAILBOX6_CLKCTRL_IDLEST_TRANS                                      (1U)

#define CM_L3INSTR_CLKSTCTRL_CLKTRCTRL_SHIFT                                       (0U)
#define CM_L3INSTR_CLKSTCTRL_CLKTRCTRL_MASK                                        (0x00000003U)
#define CM_L3INSTR_CLKSTCTRL_CLKTRCTRL_HW_AUTO                                      (3U)

#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_SHIFT                                             (8U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_MASK                                              (0x00000100U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_INACT                                              (0U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_L3_GICLK_ACT                                                (1U)

#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_DLL_AGING_GCLK_SHIFT                                       (9U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_DLL_AGING_GCLK_MASK                                        (0x00000200U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_DLL_AGING_GCLK_INACT                                        (0U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_DLL_AGING_GCLK_ACT                                          (1U)

#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_TS_GCLK_SHIFT                                              (10U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_TS_GCLK_MASK                                               (0x00000400U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_TS_GCLK_INACT                                               (0U)
#define CM_L3INSTR_CLKSTCTRL_CLKACTIVITY_L3INSTR_TS_GCLK_ACT                                                 (1U)

#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_SHIFT                                  (16U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_MASK                                   (0x00030000U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_DISABLE                                 (3U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_IDLE                                    (2U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_FUNC                                    (0U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_IDLEST_TRANS                                   (1U)

#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_SHIFT                              (0U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_MASK                               (0x00000003U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_DISABLED                            (0U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_AUTO                                (1U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_RESERVED_2                                                   (2U)
#define CM_L3INSTR_L3_MAIN_2_CLKCTRL_MODULEMODE_RESERVED                            (3U)

#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_SHIFT                                   (16U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_MASK                                    (0x00030000U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_DISABLE                                  (3U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_IDLE                                     (2U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_FUNC                                     (0U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_IDLEST_TRANS                                    (1U)

#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_SHIFT                               (0U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_MASK                                (0x00000003U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_DISABLED                             (0U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_AUTO                                 (1U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_RESERVED_2                           (2U)
#define CM_L3INSTR_L3_INSTR_CLKCTRL_MODULEMODE_RESERVED                             (3U)

#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_SHIFT                                 (16U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_MASK                                  (0x00030000U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_DISABLE                                (3U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_IDLE                                   (2U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_FUNC                                   (0U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_IDLEST_TRANS                                  (1U)

#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_SHIFT                             (0U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_MASK                              (0x00000003U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_DISABLED                           (0U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_AUTO                               (1U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_RESERVED_2                         (2U)
#define CM_L3INSTR_OCP_WP_NOC_CLKCTRL_MODULEMODE_RESERVED                           (3U)

#define CM_L3INSTR_DLL_AGING_CLKCTRL_MODULEMODE_SHIFT                              (0U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_MODULEMODE_MASK                               (0x00000003U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_MODULEMODE_AUTO                                (1U)

#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_SHIFT                                  (16U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_MASK                                   (0x00030000U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_DISABLE                                 (3U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_IDLE                                    (2U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_FUNC                                    (0U)
#define CM_L3INSTR_DLL_AGING_CLKCTRL_IDLEST_TRANS                                   (1U)

#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_MODULEMODE_SHIFT                    (0U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_MODULEMODE_MASK                     (0x00000003U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_MODULEMODE_AUTO                      (1U)

#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_SHIFT                        (16U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_MASK                         (0x00030000U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_DISABLE                       (3U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_IDLE                          (2U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_FUNC                          (0U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_IDLEST_TRANS                         (1U)

#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_SHIFT                        (24U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_MASK                         (0x03000000U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_DIV8                          (0U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_DIV16                         (1U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_DIV32                         (2U)
#define CM_L3INSTR_CTRL_MODULE_BANDGAP_CLKCTRL_CLKSEL_RESERVED                      (3U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CORE_CM_CORE_H_ */

