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
 *  \file   hw_core_prm.h
 *
 *  \brief  Register-level header file for PRCM
 *
**/

#ifndef HW_CORE_PRM_H_
#define HW_CORE_PRM_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define PM_CORE_PWRSTCTRL                                      (0x0U)
#define PM_CORE_PWRSTST                                        (0x4U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT                           (0x24U)
#define RM_L3MAIN1_GPMC_CONTEXT                                (0x2cU)
#define RM_L3MAIN1_MMU_EDMA_CONTEXT                            (0x34U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP                                  (0x50U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT                           (0x54U)
#define PM_L3MAIN1_TESOC_WKDEP                                      (0x58U)
#define RM_L3MAIN1_TESOC_CONTEXT                                    (0x5cU)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT                            (0x6cU)
#define PM_L3MAIN1_TPCC_WKDEP                                       (0x70U)
#define RM_L3MAIN1_TPCC_CONTEXT                                (0x74U)
#define PM_L3MAIN1_TPTC1_WKDEP                                      (0x78U)
#define RM_L3MAIN1_TPTC1_CONTEXT                               (0x7cU)
#define PM_L3MAIN1_TPTC2_WKDEP                                      (0x80U)
#define RM_L3MAIN1_TPTC2_CONTEXT                               (0x84U)
#define RM_L3MAIN1_SPARE_UNKNOWN6_CONTEXT                      (0xd4U)
#define RM_IPU2_IPU2_CONTEXT                                                                                (0x224U)
#define RM_DMA_DMA_SYSTEM_CONTEXT                                                                           (0x324U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT                                                                         (0x42cU)
#define RM_EMIF_EMIF1_CONTEXT                                  (0x434U)
#define RM_EMIF_EMIF_DLL_CONTEXT                                                                            (0x444U)
#define RM_ATL_ATL_CONTEXT                                                                                  (0x524U)
#define RM_L4CFG_L4_CFG_CONTEXT                                (0x624U)
#define RM_L4CFG_SPINLOCK_CONTEXT                              (0x62cU)
#define RM_L4CFG_MAILBOX1_CONTEXT                              (0x634U)
#define RM_L4CFG_MAILBOX2_CONTEXT                              (0x64cU)
#define RM_L4CFG_MAILBOX6_CONTEXT                              (0x66cU)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT                           (0x724U)
#define RM_L3INSTR_L3_INSTR_CONTEXT                            (0x72cU)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT                          (0x744U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_RETSTATE_SHIFT                                                    (8U)
#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_RETSTATE_MASK                                                     (0x00000100U)
#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_RETSTATE_MEM_RET                                                   (1U)

#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_ONSTATE_SHIFT                                                     (16U)
#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_ONSTATE_MASK                                                      (0x00030000U)
#define PM_CORE_PWRSTCTRL_CORE_OTHER_BANK_ONSTATE_MEM_ON                                                     (3U)

#define PM_CORE_PWRSTCTRL_LOGICRETSTATE_SHIFT                                      (2U)
#define PM_CORE_PWRSTCTRL_LOGICRETSTATE_MASK                                       (0x00000004U)
#define PM_CORE_PWRSTCTRL_LOGICRETSTATE_LOGIC_RET                                   (1U)
#define PM_CORE_PWRSTCTRL_LOGICRETSTATE_LOGIC_OFF                                   (0U)

#define PM_CORE_PWRSTCTRL_POWERSTATE_SHIFT                                         (0U)
#define PM_CORE_PWRSTCTRL_POWERSTATE_MASK                                          (0x00000003U)
#define PM_CORE_PWRSTCTRL_POWERSTATE_RESERVED                                       (0U)
#define PM_CORE_PWRSTCTRL_POWERSTATE_INACT                                          (2U)
#define PM_CORE_PWRSTCTRL_POWERSTATE_RET                                            (1U)
#define PM_CORE_PWRSTCTRL_POWERSTATE_ON                                             (3U)

#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_RETSTATE_SHIFT                                                        (9U)
#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_RETSTATE_MASK                                                         (0x00000200U)
#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_RETSTATE_MEM_RET                                                       (1U)

#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_ONSTATE_SHIFT                                                         (18U)
#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_ONSTATE_MASK                                                          (0x000c0000U)
#define PM_CORE_PWRSTCTRL_CORE_OCMRAM_ONSTATE_MEM_ON                                                         (3U)

#define PM_CORE_PWRSTCTRL_IPU_L2RAM_RETSTATE_SHIFT                                 (10U)
#define PM_CORE_PWRSTCTRL_IPU_L2RAM_RETSTATE_MASK                                  (0x00000400U)
#define PM_CORE_PWRSTCTRL_IPU_L2RAM_RETSTATE_MEM_RET                                (1U)
#define PM_CORE_PWRSTCTRL_IPU_L2RAM_RETSTATE_MEM_OFF                                (0U)

#define PM_CORE_PWRSTCTRL_IPU_L2RAM_ONSTATE_SHIFT                                  (20U)
#define PM_CORE_PWRSTCTRL_IPU_L2RAM_ONSTATE_MASK                                   (0x00300000U)
#define PM_CORE_PWRSTCTRL_IPU_L2RAM_ONSTATE_MEM_ON                                  (3U)

#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_RETSTATE_SHIFT                              (11U)
#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_RETSTATE_MASK                               (0x00000800U)
#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_RETSTATE_MEM_OFF                             (0U)
#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_RETSTATE_MEM_RET                             (1U)

#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_ONSTATE_SHIFT                               (22U)
#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_ONSTATE_MASK                                (0x00c00000U)
#define PM_CORE_PWRSTCTRL_IPU_UNICACHE_ONSTATE_MEM_ON                               (3U)

#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_RETSTATE_SHIFT                             (12U)
#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_RETSTATE_MASK                              (0x00001000U)
#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_RETSTATE_MEM_OFF                            (0U)

#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_ONSTATE_SHIFT                              (24U)
#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_ONSTATE_MASK                               (0x03000000U)
#define PM_CORE_PWRSTCTRL_OCP_NRET_BANK_ONSTATE_MEM_ON                              (3U)

#define PM_CORE_PWRSTCTRL_LOWPOWERSTATECHANGE_SHIFT                                (4U)
#define PM_CORE_PWRSTCTRL_LOWPOWERSTATECHANGE_MASK                                 (0x00000010U)
#define PM_CORE_PWRSTCTRL_LOWPOWERSTATECHANGE_EN                                    (1U)
#define PM_CORE_PWRSTCTRL_LOWPOWERSTATECHANGE_DIS                                   (0U)

#define PM_CORE_PWRSTST_POWERSTATEST_SHIFT                                         (0U)
#define PM_CORE_PWRSTST_POWERSTATEST_MASK                                          (0x00000003U)
#define PM_CORE_PWRSTST_POWERSTATEST_ON                                             (3U)
#define PM_CORE_PWRSTST_POWERSTATEST_RESERVED                                       (0U)
#define PM_CORE_PWRSTST_POWERSTATEST_RET                                            (1U)
#define PM_CORE_PWRSTST_POWERSTATEST_INACTIVE                                       (2U)

#define PM_CORE_PWRSTST_INTRANSITION_SHIFT                                         (20U)
#define PM_CORE_PWRSTST_INTRANSITION_MASK                                          (0x00100000U)
#define PM_CORE_PWRSTST_INTRANSITION_NO                                             (0U)
#define PM_CORE_PWRSTST_INTRANSITION_ONGOING                                        (1U)

#define PM_CORE_PWRSTST_LOGICSTATEST_SHIFT                                         (2U)
#define PM_CORE_PWRSTST_LOGICSTATEST_MASK                                          (0x00000004U)
#define PM_CORE_PWRSTST_LOGICSTATEST_ON                                             (1U)
#define PM_CORE_PWRSTST_LOGICSTATEST_OFF                                            (0U)

#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_SHIFT                                                       (4U)
#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_MASK                                                        (0x00000030U)
#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_MEM_ON                                                       (3U)
#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_MEM_RET                                                      (1U)
#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_MEM_OFF                                                      (0U)
#define PM_CORE_PWRSTST_CORE_OTHER_BANK_STATEST_RESERVED                                                     (2U)

#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_SHIFT                                                           (6U)
#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_MASK                                                            (0x000000c0U)
#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_MEM_ON                                                           (3U)
#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_MEM_RET                                                          (1U)
#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_MEM_OFF                                                          (0U)
#define PM_CORE_PWRSTST_CORE_OCMRAM_STATEST_RESERVED                                                         (2U)

#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_SHIFT                                    (8U)
#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_MASK                                     (0x00000300U)
#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_MEM_ON                                    (3U)
#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_MEM_RET                                   (1U)
#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_MEM_OFF                                   (0U)
#define PM_CORE_PWRSTST_IPU_L2RAM_STATEST_RESERVED                                  (2U)

#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_SHIFT                                 (10U)
#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_MASK                                  (0x00000c00U)
#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_MEM_ON                                 (3U)
#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_MEM_RET                                (1U)
#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_MEM_OFF                                (0U)
#define PM_CORE_PWRSTST_IPU_UNICACHE_STATEST_RESERVED                               (2U)

#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_SHIFT                                (12U)
#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_MASK                                 (0x00003000U)
#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_MEM_ON                                (3U)
#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_RESERVED1                             (1U)
#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_MEM_OFF                               (0U)
#define PM_CORE_PWRSTST_OCP_NRET_BANK_STATEST_RESERVED                              (2U)

#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_SHIFT                                (24U)
#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_MASK                                 (0x03000000U)
#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_ON                                    (3U)
#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_OFF                                   (0U)
#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_RET                                   (1U)
#define PM_CORE_PWRSTST_LASTPOWERSTATEENTERED_INACTIVE                              (2U)

#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                         (0U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_DFF_MASK                          (0x00000001U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_DFF_LOST                           (1U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                     (0U)

#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                         (1U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_RFF_MASK                          (0x00000002U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_RFF_LOST                           (1U)
#define RM_L3MAIN1_L3_MAIN_1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                     (0U)

#define RM_L3MAIN1_GPMC_CONTEXT_LOSTCONTEXT_RFF_SHIFT                              (1U)
#define RM_L3MAIN1_GPMC_CONTEXT_LOSTCONTEXT_RFF_MASK                               (0x00000002U)
#define RM_L3MAIN1_GPMC_CONTEXT_LOSTCONTEXT_RFF_LOST                                (1U)
#define RM_L3MAIN1_GPMC_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                          (0U)

#define RM_L3MAIN1_MMU_EDMA_CONTEXT_LOSTCONTEXT_RFF_SHIFT                          (1U)
#define RM_L3MAIN1_MMU_EDMA_CONTEXT_LOSTCONTEXT_RFF_MASK                           (0x00000002U)
#define RM_L3MAIN1_MMU_EDMA_CONTEXT_LOSTCONTEXT_RFF_LOST                            (1U)
#define RM_L3MAIN1_MMU_EDMA_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                      (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP1_SHIFT                                             (2U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP1_MASK                                              (0x00000004U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU1_SHIFT                                             (4U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU1_MASK                                              (0x00000010U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_IPU1_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP2_SHIFT                                             (5U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP2_MASK                                              (0x00000020U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP2_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_DSP2_DISABLED                                           (0U)

#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE1_SHIFT                                             (6U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE1_MASK                                              (0x00000040U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE1_ENABLED                                            (1U)
#define PM_L3MAIN1_OCMC_RAM1_WKDEP_WKUPDEP_OCMC_RAM1_EVE1_DISABLED                                           (0U)

#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                         (0U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTCONTEXT_DFF_MASK                          (0x00000001U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTCONTEXT_DFF_LOST                           (1U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                     (0U)

#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTMEM_CORE_OCMRAM_SHIFT                     (8U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTMEM_CORE_OCMRAM_MASK                      (0x00000100U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTMEM_CORE_OCMRAM_LOST                       (1U)
#define RM_L3MAIN1_OCMC_RAM1_CONTEXT_LOSTMEM_CORE_OCMRAM_MAINTAINED                 (0U)

#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_DSP1_SHIFT                                       (2U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_DSP1_MASK                                        (0x00000004U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_DSP1_ENABLED                                      (1U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_DSP1_DISABLED                                     (0U)

#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_IPU1_SHIFT                                       (4U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_IPU1_MASK                                        (0x00000010U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_IPU1_ENABLED                                      (1U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_IPU1_DISABLED                                     (0U)

#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_DSP2_SHIFT                                       (5U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_DSP2_MASK                                        (0x00000020U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_DSP2_ENABLED                                      (1U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_DSP2_DISABLED                                     (0U)

#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_EVE1_SHIFT                                       (6U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_EVE1_MASK                                        (0x00000040U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_EVE1_ENABLED                                      (1U)
#define PM_L3MAIN1_TESOC_WKDEP_WKUPDEP_TESOC_EVE1_DISABLED                                     (0U)

#define RM_L3MAIN1_TESOC_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                  (0U)
#define RM_L3MAIN1_TESOC_CONTEXT_LOSTCONTEXT_DFF_MASK                                   (0x00000001U)
#define RM_L3MAIN1_TESOC_CONTEXT_LOSTCONTEXT_DFF_LOST                                    (1U)
#define RM_L3MAIN1_TESOC_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                              (0U)

#define RM_L3MAIN1_TESOC_CONTEXT_LOSTMEM_CORE_OCMRAM_SHIFT                              (8U)
#define RM_L3MAIN1_TESOC_CONTEXT_LOSTMEM_CORE_OCMRAM_MASK                               (0x00000100U)
#define RM_L3MAIN1_TESOC_CONTEXT_LOSTMEM_CORE_OCMRAM_LOST                                (1U)
#define RM_L3MAIN1_TESOC_CONTEXT_LOSTMEM_CORE_OCMRAM_MAINTAINED                          (0U)

#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTCONTEXT_DFF_SHIFT                          (0U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTCONTEXT_DFF_MASK                           (0x00000001U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTCONTEXT_DFF_LOST                            (1U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                      (0U)

#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTMEM_CORE_OCMROM_SHIFT                      (8U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTMEM_CORE_OCMROM_MASK                       (0x00000100U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTMEM_CORE_OCMROM_LOST                        (1U)
#define RM_L3MAIN1_OCMC_ROM_CONTEXT_LOSTMEM_CORE_OCMROM_MAINTAINED                  (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP1_SHIFT                                                       (2U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP1_MASK                                                        (0x00000004U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP1_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP1_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU1_SHIFT                                                       (4U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU1_MASK                                                        (0x00000010U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU1_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_IPU1_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP2_SHIFT                                                       (5U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP2_MASK                                                        (0x00000020U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP2_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_DSP2_DISABLED                                                     (0U)

#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE1_SHIFT                                                       (6U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE1_MASK                                                        (0x00000040U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE1_ENABLED                                                      (1U)
#define PM_L3MAIN1_TPCC_WKDEP_WKUPDEP_TPCC_EVE1_DISABLED                                                     (0U)

#define RM_L3MAIN1_TPCC_CONTEXT_LOSTCONTEXT_RFF_SHIFT                              (1U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTCONTEXT_RFF_MASK                               (0x00000002U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTCONTEXT_RFF_LOST                                (1U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                          (0U)

#define RM_L3MAIN1_TPCC_CONTEXT_LOSTMEM_TPCC_BANK_SHIFT                                                     (8U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTMEM_TPCC_BANK_MASK                                                      (0x00000100U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTMEM_TPCC_BANK_LOST                                                       (1U)
#define RM_L3MAIN1_TPCC_CONTEXT_LOSTMEM_TPCC_BANK_MAINTAINED                                                 (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP1_SHIFT                                                     (2U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP1_MASK                                                      (0x00000004U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP1_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU1_SHIFT                                                     (4U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU1_MASK                                                      (0x00000010U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_IPU1_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP2_SHIFT                                                     (5U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP2_MASK                                                      (0x00000020U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP2_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_DSP2_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE1_SHIFT                                                     (6U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE1_MASK                                                      (0x00000040U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC1_WKDEP_WKUPDEP_TPTC1_EVE1_DISABLED                                                   (0U)

#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                             (1U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTCONTEXT_RFF_MASK                              (0x00000002U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTCONTEXT_RFF_LOST                               (1U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                         (0U)

#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTMEM_TPTC_BANK_SHIFT                           (8U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTMEM_TPTC_BANK_MASK                            (0x00000100U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTMEM_TPTC_BANK_LOST                             (1U)
#define RM_L3MAIN1_TPTC1_CONTEXT_LOSTMEM_TPTC_BANK_MAINTAINED                       (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP1_SHIFT                                                     (2U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP1_MASK                                                      (0x00000004U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP1_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU1_SHIFT                                                     (4U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU1_MASK                                                      (0x00000010U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_IPU1_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP2_SHIFT                                                     (5U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP2_MASK                                                      (0x00000020U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP2_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_DSP2_DISABLED                                                   (0U)

#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE1_SHIFT                                                     (6U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE1_MASK                                                      (0x00000040U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE1_ENABLED                                                    (1U)
#define PM_L3MAIN1_TPTC2_WKDEP_WKUPDEP_TPTC2_EVE1_DISABLED                                                   (0U)

#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                             (1U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTCONTEXT_RFF_MASK                              (0x00000002U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTCONTEXT_RFF_LOST                               (1U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                         (0U)

#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTMEM_TPTC_BANK_SHIFT                           (8U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTMEM_TPTC_BANK_MASK                            (0x00000100U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTMEM_TPTC_BANK_LOST                             (1U)
#define RM_L3MAIN1_TPTC2_CONTEXT_LOSTMEM_TPTC_BANK_MAINTAINED                       (0U)

#define RM_L3MAIN1_SPARE_UNKNOWN6_CONTEXT_LOSTCONTEXT_DFF_SHIFT                    (0U)
#define RM_L3MAIN1_SPARE_UNKNOWN6_CONTEXT_LOSTCONTEXT_DFF_MASK                     (0x00000001U)
#define RM_L3MAIN1_SPARE_UNKNOWN6_CONTEXT_LOSTCONTEXT_DFF_LOST                      (1U)
#define RM_L3MAIN1_SPARE_UNKNOWN6_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                (0U)

#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                          (0U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_DFF_MASK                                                           (0x00000001U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_DFF_LOST                                                            (1U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                      (0U)

#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                          (1U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_RFF_MASK                                                           (0x00000002U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_RFF_LOST                                                            (1U)
#define RM_IPU2_IPU2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                      (0U)

#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_UNICACHE_SHIFT                                                     (8U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_UNICACHE_MASK                                                      (0x00000100U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_UNICACHE_LOST                                                       (1U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_UNICACHE_MAINTAINED                                                 (0U)

#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_L2RAM_SHIFT                                                        (9U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_L2RAM_MASK                                                         (0x00000200U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_L2RAM_LOST                                                          (1U)
#define RM_IPU2_IPU2_CONTEXT_LOSTMEM_IPU_L2RAM_MAINTAINED                                                    (0U)

#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                     (1U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTCONTEXT_RFF_MASK                                                      (0x00000002U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTCONTEXT_RFF_LOST                                                       (1U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                                 (0U)

#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTMEM_CORE_OTHER_BANK_SHIFT                                             (8U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTMEM_CORE_OTHER_BANK_MASK                                              (0x00000100U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTMEM_CORE_OTHER_BANK_LOST                                               (1U)
#define RM_DMA_DMA_SYSTEM_CONTEXT_LOSTMEM_CORE_OTHER_BANK_MAINTAINED                                         (0U)

#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                   (0U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_DFF_MASK                                                    (0x00000001U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_DFF_LOST                                                     (1U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                               (0U)

#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                                   (1U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_RFF_MASK                                                    (0x00000002U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_RFF_LOST                                                     (1U)
#define RM_EMIF_EMIF_OCP_FW_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                                               (0U)

#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                                (1U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_RFF_MASK                                 (0x00000002U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_RFF_LOST                                  (1U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                            (0U)

#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                (0U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_DFF_MASK                                 (0x00000001U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_DFF_LOST                                  (1U)
#define RM_EMIF_EMIF1_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                            (0U)

#define RM_EMIF_EMIF_DLL_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                      (0U)
#define RM_EMIF_EMIF_DLL_CONTEXT_LOSTCONTEXT_DFF_MASK                                                       (0x00000001U)
#define RM_EMIF_EMIF_DLL_CONTEXT_LOSTCONTEXT_DFF_LOST                                                        (1U)
#define RM_EMIF_EMIF_DLL_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                  (0U)

#define RM_ATL_ATL_CONTEXT_LOSTCONTEXT_DFF_SHIFT                                                            (0U)
#define RM_ATL_ATL_CONTEXT_LOSTCONTEXT_DFF_MASK                                                             (0x00000001U)
#define RM_ATL_ATL_CONTEXT_LOSTCONTEXT_DFF_LOST                                                              (1U)
#define RM_ATL_ATL_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                                                        (0U)

#define RM_ATL_ATL_CONTEXT_LOSTMEM_ATL_BANK_SHIFT                                                           (8U)
#define RM_ATL_ATL_CONTEXT_LOSTMEM_ATL_BANK_MASK                                                            (0x00000100U)
#define RM_ATL_ATL_CONTEXT_LOSTMEM_ATL_BANK_LOST                                                             (1U)
#define RM_ATL_ATL_CONTEXT_LOSTMEM_ATL_BANK_MAINTAINED                                                       (0U)

#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_DFF_SHIFT                              (0U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_DFF_MASK                               (0x00000001U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_DFF_LOST                                (1U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                          (0U)

#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_RFF_SHIFT                              (1U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_RFF_MASK                               (0x00000002U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_RFF_LOST                                (1U)
#define RM_L4CFG_L4_CFG_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                          (0U)

#define RM_L4CFG_SPINLOCK_CONTEXT_LOSTCONTEXT_RFF_SHIFT                            (1U)
#define RM_L4CFG_SPINLOCK_CONTEXT_LOSTCONTEXT_RFF_MASK                             (0x00000002U)
#define RM_L4CFG_SPINLOCK_CONTEXT_LOSTCONTEXT_RFF_LOST                              (1U)
#define RM_L4CFG_SPINLOCK_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                        (0U)

#define RM_L4CFG_MAILBOX1_CONTEXT_LOSTCONTEXT_RFF_SHIFT                            (1U)
#define RM_L4CFG_MAILBOX1_CONTEXT_LOSTCONTEXT_RFF_MASK                             (0x00000002U)
#define RM_L4CFG_MAILBOX1_CONTEXT_LOSTCONTEXT_RFF_LOST                              (1U)
#define RM_L4CFG_MAILBOX1_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                        (0U)

#define RM_L4CFG_MAILBOX2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                            (1U)
#define RM_L4CFG_MAILBOX2_CONTEXT_LOSTCONTEXT_RFF_MASK                             (0x00000002U)
#define RM_L4CFG_MAILBOX2_CONTEXT_LOSTCONTEXT_RFF_LOST                              (1U)
#define RM_L4CFG_MAILBOX2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                        (0U)

#define RM_L4CFG_MAILBOX6_CONTEXT_LOSTCONTEXT_RFF_SHIFT                            (1U)
#define RM_L4CFG_MAILBOX6_CONTEXT_LOSTCONTEXT_RFF_MASK                             (0x00000002U)
#define RM_L4CFG_MAILBOX6_CONTEXT_LOSTCONTEXT_RFF_LOST                              (1U)
#define RM_L4CFG_MAILBOX6_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                        (0U)

#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_DFF_SHIFT                         (0U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_DFF_MASK                          (0x00000001U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_DFF_LOST                           (1U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                     (0U)

#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_RFF_SHIFT                         (1U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_RFF_MASK                          (0x00000002U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_RFF_LOST                           (1U)
#define RM_L3INSTR_L3_MAIN_2_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                     (0U)

#define RM_L3INSTR_L3_INSTR_CONTEXT_LOSTCONTEXT_DFF_SHIFT                          (0U)
#define RM_L3INSTR_L3_INSTR_CONTEXT_LOSTCONTEXT_DFF_MASK                           (0x00000001U)
#define RM_L3INSTR_L3_INSTR_CONTEXT_LOSTCONTEXT_DFF_LOST                            (1U)
#define RM_L3INSTR_L3_INSTR_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                      (0U)

#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_RFF_SHIFT                        (1U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_RFF_MASK                         (0x00000002U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_RFF_LOST                          (1U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_RFF_MAINTAINED                    (0U)

#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_DFF_SHIFT                        (0U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_DFF_MASK                         (0x00000001U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_DFF_LOST                          (1U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTCONTEXT_DFF_MAINTAINED                    (0U)

#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTMEM_CORE_NRET_BANK_SHIFT                 (8U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTMEM_CORE_NRET_BANK_MASK                  (0x00000100U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTMEM_CORE_NRET_BANK_LOST                   (1U)
#define RM_L3INSTR_OCP_WP_NOC_CONTEXT_LOSTMEM_CORE_NRET_BANK_MAINTAINED             (0U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_CORE_PRM_H_ */

