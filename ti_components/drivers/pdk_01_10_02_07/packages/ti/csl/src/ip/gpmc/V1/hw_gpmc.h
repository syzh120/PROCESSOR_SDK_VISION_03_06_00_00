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
*
*  \file   hw_gpmc.h
*  \brief  register-level header file for GPMC
*
**/

#ifndef HW_GPMC_H_
#define HW_GPMC_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define GPMC_REVISION                                                                                       (0x0U)
#define GPMC_SYSCONFIG                                                                                      (0x10U)
#define GPMC_SYSSTATUS                                                                                      (0x14U)
#define GPMC_IRQSTATUS                                                                                      (0x18U)
#define GPMC_IRQENABLE                                                                                      (0x1cU)
#define GPMC_TIMEOUT_CONTROL                                                                                (0x40U)
#define GPMC_ERR_ADDRESS                                                                                    (0x44U)
#define GPMC_ERR_TYPE                                                                                       (0x48U)
#define GPMC_CONFIG                                                                                         (0x50U)
#define GPMC_STATUS                                                                                         (0x54U)
#define GPMC_PREFETCH_CONFIG1                                                                               (0x1e0U)
#define GPMC_PREFETCH_CONFIG2                                                                               (0x1e4U)
#define GPMC_PREFETCH_CONTROL                                                                               (0x1ecU)
#define GPMC_PREFETCH_STATUS                                                                                (0x1f0U)
#define GPMC_ECC_CONFIG                                                                                     (0x1f4U)
#define GPMC_ECC_CONTROL                                                                                    (0x1f8U)
#define GPMC_ECC_SIZE_CONFIG                                                                                (0x1fcU)
#define GPMC_ECCN_RESULT(n)                                                                                 ((uint32_t)0x200U + ((n) * 4U))
#define GPMC_BCH_RESULT_0(n)                                                                                ((uint32_t)0x240U + ((n) * 16U))
#define GPMC_BCH_RESULT_1(n)                                                                                ((uint32_t)0x244U + ((n) * 16U))
#define GPMC_BCH_RESULT_2(n)                                                                                ((uint32_t)0x248U + ((n) * 16U))
#define GPMC_BCH_RESULT_3(n)                                                                                ((uint32_t)0x24cU + ((n) * 16U))
#define GPMC_BCH_SWDATA                                                                                     (0x2d0U)
#define GPMC_BCH_RESULT_5(n)                                                                                ((uint32_t)0x304U + ((n) * 16U))
#define GPMC_BCH_RESULT_6(n)                                                                                ((uint32_t)0x308U + ((n) * 16U))
#define GPMC_BCH_RESULT_4(n)                                                                                ((uint32_t)0x300U + ((n) * 16U))
#define GPMC_CONFIG1_N(n)                                                                                   ((uint32_t)0x60U + ((n) * 48U))
#define GPMC_CONFIG2_N(n)                                                                                   ((uint32_t)0x64U + ((n) * 48U))
#define GPMC_CONFIG3_N(n)                                                                                   ((uint32_t)0x68U + ((n) * 48U))
#define GPMC_CONFIG4_N(n)                                                                                   ((uint32_t)0x6cU + ((n) * 48U))
#define GPMC_CONFIG5_N(n)                                                                                   ((uint32_t)0x70U + ((n) * 48U))
#define GPMC_CONFIG6_N(n)                                                                                   ((uint32_t)0x74U + ((n) * 48U))
#define GPMC_CONFIG7_N(n)                                                                                   ((uint32_t)0x78U + ((n) * 48U))
#define GPMC_NAND_COMMAND_N(n)                                                                              ((uint32_t)0x7cU + ((n) * 48U))
#define GPMC_NAND_ADDRESS_N(n)                                                                              ((uint32_t)0x80U + ((n) * 48U))
#define GPMC_NAND_DATA_N(n)                                                                                 ((uint32_t)0x84U + ((n) * 48U))

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define GPMC_REVISION_REVISION_SHIFT                                                                        (0U)
#define GPMC_REVISION_REVISION_MASK                                                                         (0xffffffffU)

#define GPMC_SYSCONFIG_RESERVED_233_SHIFT                                                                   (2U)
#define GPMC_SYSCONFIG_RESERVED_233_MASK                                                                    (0x00000004U)

#define GPMC_SYSCONFIG_SOFTRESET_SHIFT                                                                      (1U)
#define GPMC_SYSCONFIG_SOFTRESET_MASK                                                                       (0x00000002U)
#define GPMC_SYSCONFIG_SOFTRESET_NORMAL                                                                      (0U)
#define GPMC_SYSCONFIG_SOFTRESET_RESET                                                                       (1U)

#define GPMC_SYSCONFIG_RESERVED_234_SHIFT                                                                   (5U)
#define GPMC_SYSCONFIG_RESERVED_234_MASK                                                                    (0xffffffe0U)

#define GPMC_SYSCONFIG_IDLEMODE_SHIFT                                                                       (3U)
#define GPMC_SYSCONFIG_IDLEMODE_MASK                                                                        (0x00000018U)
#define GPMC_SYSCONFIG_IDLEMODE_FORCEIDLE                                                                    (0U)
#define GPMC_SYSCONFIG_IDLEMODE_NOIDLE                                                                       (1U)
#define GPMC_SYSCONFIG_IDLEMODE_SMARTIDLE                                                                    (2U)
#define GPMC_SYSCONFIG_IDLEMODE_RESERVED                                                                     (3U)

#define GPMC_SYSCONFIG_AUTOIDLE_SHIFT                                                                       (0U)
#define GPMC_SYSCONFIG_AUTOIDLE_MASK                                                                        (0x00000001U)
#define GPMC_SYSCONFIG_AUTOIDLE_FREERUN                                                                      (0U)
#define GPMC_SYSCONFIG_AUTOIDLE_AUTORUN                                                                      (1U)

#define GPMC_SYSSTATUS_RESETDONE_SHIFT                                                                      (0U)
#define GPMC_SYSSTATUS_RESETDONE_MASK                                                                       (0x00000001U)
#define GPMC_SYSSTATUS_RESETDONE_RSTONGOING                                                                  (0U)
#define GPMC_SYSSTATUS_RESETDONE_RSTDONE                                                                     (1U)

#define GPMC_SYSSTATUS_RESERVED_235_SHIFT                                                                   (8U)
#define GPMC_SYSSTATUS_RESERVED_235_MASK                                                                    (0xffffff00U)

#define GPMC_SYSSTATUS_RESERVED_SHIFT                                                                       (1U)
#define GPMC_SYSSTATUS_RESERVED_MASK                                                                        (0x000000feU)

#define GPMC_IRQSTATUS_RESERVED_218_SHIFT                                                                   (10U)
#define GPMC_IRQSTATUS_RESERVED_218_MASK                                                                    (0xfffffc00U)

#define GPMC_IRQSTATUS_RESERVED_219_SHIFT                                                                   (2U)
#define GPMC_IRQSTATUS_RESERVED_219_MASK                                                                    (0x000000fcU)

#define GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_SHIFT                                                            (1U)
#define GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_MASK                                                             (0x00000002U)
#define GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_TCSTAT0_R                                                         (0U)
#define GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_TCSTAT0_W                                                         (0U)
#define GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_TCSTAT1_R                                                         (1U)
#define GPMC_IRQSTATUS_TERMINALCOUNTSTATUS_TCSTAT1_W                                                         (1U)

#define GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_SHIFT                                                       (8U)
#define GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_MASK                                                        (0x00000100U)
#define GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_W0DET0_R                                                     (0U)
#define GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_W0DET0_W                                                     (0U)
#define GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_W0DET1_R                                                     (1U)
#define GPMC_IRQSTATUS_WAIT0EDGEDETECTIONSTATUS_W0DET1_W                                                     (1U)

#define GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_SHIFT                                                       (9U)
#define GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_MASK                                                        (0x00000200U)
#define GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_W1DET0_R                                                     (0U)
#define GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_W1DET0_W                                                     (0U)
#define GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_W1DET1_R                                                     (1U)
#define GPMC_IRQSTATUS_WAIT1EDGEDETECTIONSTATUS_W1DET1_W                                                     (1U)

#define GPMC_IRQSTATUS_FIFOEVENTSTATUS_SHIFT                                                                (0U)
#define GPMC_IRQSTATUS_FIFOEVENTSTATUS_MASK                                                                 (0x00000001U)
#define GPMC_IRQSTATUS_FIFOEVENTSTATUS_FIFOSTAT0_R                                                           (0U)
#define GPMC_IRQSTATUS_FIFOEVENTSTATUS_FIFOSTAT0_W                                                           (0U)
#define GPMC_IRQSTATUS_FIFOEVENTSTATUS_FIFOSTAT1_R                                                           (1U)
#define GPMC_IRQSTATUS_FIFOEVENTSTATUS_FIFOSTAT1_W                                                           (1U)

#define GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE_SHIFT                                                       (1U)
#define GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE_MASK                                                        (0x00000002U)
#define GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE_TCMASKED                                                     (0U)
#define GPMC_IRQENABLE_TERMINALCOUNTEVENTENABLE_TCENABLED                                                    (1U)

#define GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE_SHIFT                                                       (8U)
#define GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE_MASK                                                        (0x00000100U)
#define GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE_W0MASKED                                                     (0U)
#define GPMC_IRQENABLE_WAIT0EDGEDETECTIONENABLE_W0ENABLED                                                    (1U)

#define GPMC_IRQENABLE_FIFOEVENTENABLE_SHIFT                                                                (0U)
#define GPMC_IRQENABLE_FIFOEVENTENABLE_MASK                                                                 (0x00000001U)
#define GPMC_IRQENABLE_FIFOEVENTENABLE_FIFOMASKED                                                            (0U)
#define GPMC_IRQENABLE_FIFOEVENTENABLE_FIFOENABLED                                                           (1U)

#define GPMC_IRQENABLE_RESERVED_216_SHIFT                                                                   (10U)
#define GPMC_IRQENABLE_RESERVED_216_MASK                                                                    (0xfffffc00U)

#define GPMC_IRQENABLE_RESERVED_217_SHIFT                                                                   (2U)
#define GPMC_IRQENABLE_RESERVED_217_MASK                                                                    (0x000000fcU)

#define GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE_SHIFT                                                       (9U)
#define GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE_MASK                                                        (0x00000200U)
#define GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE_W1MASKED                                                     (0U)
#define GPMC_IRQENABLE_WAIT1EDGEDETECTIONENABLE_W1ENABLED                                                    (1U)

#define GPMC_TIMEOUT_CONTROL_RESERVED_237_SHIFT                                                             (13U)
#define GPMC_TIMEOUT_CONTROL_RESERVED_237_MASK                                                              (0xffffe000U)

#define GPMC_TIMEOUT_CONTROL_TIMEOUTSTARTVALUE_SHIFT                                                        (4U)
#define GPMC_TIMEOUT_CONTROL_TIMEOUTSTARTVALUE_MASK                                                         (0x00001ff0U)

#define GPMC_TIMEOUT_CONTROL_RESERVED_238_SHIFT                                                             (1U)
#define GPMC_TIMEOUT_CONTROL_RESERVED_238_MASK                                                              (0x0000000eU)

#define GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE_SHIFT                                                            (0U)
#define GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE_MASK                                                             (0x00000001U)
#define GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE_TODISABLED                                                        (0U)
#define GPMC_TIMEOUT_CONTROL_TIMEOUTENABLE_TOENABLED                                                         (1U)

#define GPMC_ERR_ADDRESS_RESERVED_212_SHIFT                                                                 (31U)
#define GPMC_ERR_ADDRESS_RESERVED_212_MASK                                                                  (0x80000000U)

#define GPMC_ERR_ADDRESS_ILLEGALADD_SHIFT                                                                   (0U)
#define GPMC_ERR_ADDRESS_ILLEGALADD_MASK                                                                    (0x7fffffffU)

#define GPMC_ERR_TYPE_ILLEGALMCMD_SHIFT                                                                     (8U)
#define GPMC_ERR_TYPE_ILLEGALMCMD_MASK                                                                      (0x00000700U)

#define GPMC_ERR_TYPE_RESERVED_213_SHIFT                                                                    (5U)
#define GPMC_ERR_TYPE_RESERVED_213_MASK                                                                     (0x000000e0U)

#define GPMC_ERR_TYPE_ERRORTIMEOUT_SHIFT                                                                    (2U)
#define GPMC_ERR_TYPE_ERRORTIMEOUT_MASK                                                                     (0x00000004U)
#define GPMC_ERR_TYPE_ERRORTIMEOUT_NOERR                                                                     (0U)
#define GPMC_ERR_TYPE_ERRORTIMEOUT_ERR                                                                       (1U)

#define GPMC_ERR_TYPE_ERRORNOTSUPPADD_SHIFT                                                                 (4U)
#define GPMC_ERR_TYPE_ERRORNOTSUPPADD_MASK                                                                  (0x00000010U)
#define GPMC_ERR_TYPE_ERRORNOTSUPPADD_NOERR                                                                  (0U)
#define GPMC_ERR_TYPE_ERRORNOTSUPPADD_ERR                                                                    (1U)

#define GPMC_ERR_TYPE_RESERVED_214_SHIFT                                                                    (1U)
#define GPMC_ERR_TYPE_RESERVED_214_MASK                                                                     (0x00000002U)

#define GPMC_ERR_TYPE_ERRORNOTSUPPMCMD_SHIFT                                                                (3U)
#define GPMC_ERR_TYPE_ERRORNOTSUPPMCMD_MASK                                                                 (0x00000008U)
#define GPMC_ERR_TYPE_ERRORNOTSUPPMCMD_NOERR                                                                 (0U)
#define GPMC_ERR_TYPE_ERRORNOTSUPPMCMD_ERR                                                                   (1U)

#define GPMC_ERR_TYPE_ERRORVALID_SHIFT                                                                      (0U)
#define GPMC_ERR_TYPE_ERRORVALID_MASK                                                                       (0x00000001U)
#define GPMC_ERR_TYPE_ERRORVALID_NOTVALID                                                                    (0U)
#define GPMC_ERR_TYPE_ERRORVALID_ERRDETECT                                                                   (1U)

#define GPMC_ERR_TYPE_RESERVED_215_SHIFT                                                                    (11U)
#define GPMC_ERR_TYPE_RESERVED_215_MASK                                                                     (0xfffff800U)

#define GPMC_CONFIG_RESERVED_0_SHIFT                                                                        (5U)
#define GPMC_CONFIG_RESERVED_0_MASK                                                                         (0x000000e0U)

#define GPMC_CONFIG_NANDFORCEPOSTEDWRITE_SHIFT                                                              (0U)
#define GPMC_CONFIG_NANDFORCEPOSTEDWRITE_MASK                                                               (0x00000001U)
#define GPMC_CONFIG_NANDFORCEPOSTEDWRITE_NOFORCEPWR                                                          (0U)
#define GPMC_CONFIG_NANDFORCEPOSTEDWRITE_FORCEPWR                                                            (1U)

#define GPMC_CONFIG_RESERVED_1_SHIFT                                                                        (10U)
#define GPMC_CONFIG_RESERVED_1_MASK                                                                         (0xfffffc00U)

#define GPMC_CONFIG_WAIT1PINPOLARITY_SHIFT                                                                  (9U)
#define GPMC_CONFIG_WAIT1PINPOLARITY_MASK                                                                   (0x00000200U)
#define GPMC_CONFIG_WAIT1PINPOLARITY_W1ACTIVEL                                                               (0U)
#define GPMC_CONFIG_WAIT1PINPOLARITY_W1ACTIVEH                                                               (1U)

#define GPMC_CONFIG_WAIT0PINPOLARITY_SHIFT                                                                  (8U)
#define GPMC_CONFIG_WAIT0PINPOLARITY_MASK                                                                   (0x00000100U)
#define GPMC_CONFIG_WAIT0PINPOLARITY_W0ACTIVEL                                                               (0U)
#define GPMC_CONFIG_WAIT0PINPOLARITY_W0ACTIVEH                                                               (1U)

#define GPMC_CONFIG_RESERVED_2_SHIFT                                                                        (1U)
#define GPMC_CONFIG_RESERVED_2_MASK                                                                         (0x0000001eU)

#define GPMC_STATUS_RESERVED_231_SHIFT                                                                      (10U)
#define GPMC_STATUS_RESERVED_231_MASK                                                                       (0xfffffc00U)

#define GPMC_STATUS_RESERVED_232_SHIFT                                                                      (1U)
#define GPMC_STATUS_RESERVED_232_MASK                                                                       (0x000000feU)

#define GPMC_STATUS_WAIT1STATUS_SHIFT                                                                       (9U)
#define GPMC_STATUS_WAIT1STATUS_MASK                                                                        (0x00000200U)
#define GPMC_STATUS_WAIT1STATUS_W1ACTIVEL                                                                    (0U)
#define GPMC_STATUS_WAIT1STATUS_W1ACTIVEH                                                                    (1U)

#define GPMC_STATUS_EMPTYWRITEBUFFERSTATUS_SHIFT                                                            (0U)
#define GPMC_STATUS_EMPTYWRITEBUFFERSTATUS_MASK                                                             (0x00000001U)
#define GPMC_STATUS_EMPTYWRITEBUFFERSTATUS_B0                                                                (0U)
#define GPMC_STATUS_EMPTYWRITEBUFFERSTATUS_B1                                                                (1U)

#define GPMC_STATUS_WAIT0STATUS_SHIFT                                                                       (8U)
#define GPMC_STATUS_WAIT0STATUS_MASK                                                                        (0x00000100U)
#define GPMC_STATUS_WAIT0STATUS_W0ACTIVEL                                                                    (0U)
#define GPMC_STATUS_WAIT0STATUS_W0ACTIVEH                                                                    (1U)

#define GPMC_STATUS_WAIT2STATUS_SHIFT                                                                       (10U)
#define GPMC_STATUS_WAIT2STATUS_MASK                                                                        (0x00000400U)
#define GPMC_STATUS_WAIT2STATUS_W2ACTIVEL                                                                    (0U)
#define GPMC_STATUS_WAIT2STATUS_W2ACTIVEH                                                                    (1U)

#define GPMC_PREFETCH_CONFIG1_DMAMODE_SHIFT                                                                 (2U)
#define GPMC_PREFETCH_CONFIG1_DMAMODE_MASK                                                                  (0x00000004U)
#define GPMC_PREFETCH_CONFIG1_DMAMODE_INTERRUPTSYNC                                                          (0U)
#define GPMC_PREFETCH_CONFIG1_DMAMODE_DMAREQSYNC                                                             (1U)

#define GPMC_PREFETCH_CONFIG1_RESERVED_220_SHIFT                                                            (15U)
#define GPMC_PREFETCH_CONFIG1_RESERVED_220_MASK                                                             (0x00008000U)

#define GPMC_PREFETCH_CONFIG1_FIFOTHRESHOLD_SHIFT                                                           (8U)
#define GPMC_PREFETCH_CONFIG1_FIFOTHRESHOLD_MASK                                                            (0x00007f00U)

#define GPMC_PREFETCH_CONFIG1_RESERVED_221_SHIFT                                                            (31U)
#define GPMC_PREFETCH_CONFIG1_RESERVED_221_MASK                                                             (0x80000000U)

#define GPMC_PREFETCH_CONFIG1_ENABLEENGINE_SHIFT                                                            (7U)
#define GPMC_PREFETCH_CONFIG1_ENABLEENGINE_MASK                                                             (0x00000080U)
#define GPMC_PREFETCH_CONFIG1_ENABLEENGINE_PPDISABLED                                                        (0U)
#define GPMC_PREFETCH_CONFIG1_ENABLEENGINE_PPENABLED                                                         (1U)

#define GPMC_PREFETCH_CONFIG1_CYCLEOPTIMIZATION_SHIFT                                                       (28U)
#define GPMC_PREFETCH_CONFIG1_CYCLEOPTIMIZATION_MASK                                                        (0x70000000U)

#define GPMC_PREFETCH_CONFIG1_ENABLEOPTIMIZEDACCESS_SHIFT                                                   (27U)
#define GPMC_PREFETCH_CONFIG1_ENABLEOPTIMIZEDACCESS_MASK                                                    (0x08000000U)
#define GPMC_PREFETCH_CONFIG1_ENABLEOPTIMIZEDACCESS_OPTDISABLED                                              (0U)
#define GPMC_PREFETCH_CONFIG1_ENABLEOPTIMIZEDACCESS_OPTENABLED                                               (1U)

#define GPMC_PREFETCH_CONFIG1_RESERVED_222_SHIFT                                                            (1U)
#define GPMC_PREFETCH_CONFIG1_RESERVED_222_MASK                                                             (0x00000002U)

#define GPMC_PREFETCH_CONFIG1_SYNCHROMODE_SHIFT                                                             (3U)
#define GPMC_PREFETCH_CONFIG1_SYNCHROMODE_MASK                                                              (0x00000008U)
#define GPMC_PREFETCH_CONFIG1_SYNCHROMODE_ATSTART                                                            (0U)
#define GPMC_PREFETCH_CONFIG1_SYNCHROMODE_ATSTARTANDWAIT                                                     (1U)

#define GPMC_PREFETCH_CONFIG1_ACCESSMODE_SHIFT                                                              (0U)
#define GPMC_PREFETCH_CONFIG1_ACCESSMODE_MASK                                                               (0x00000001U)
#define GPMC_PREFETCH_CONFIG1_ACCESSMODE_PREFETCHREAD                                                        (0U)
#define GPMC_PREFETCH_CONFIG1_ACCESSMODE_WRITEPOSTING                                                        (1U)

#define GPMC_PREFETCH_CONFIG1_RESERVED_223_SHIFT                                                            (6U)
#define GPMC_PREFETCH_CONFIG1_RESERVED_223_MASK                                                             (0x00000040U)

#define GPMC_PREFETCH_CONFIG1_WAITPINSELECTOR_SHIFT                                                         (4U)
#define GPMC_PREFETCH_CONFIG1_WAITPINSELECTOR_MASK                                                          (0x00000030U)
#define GPMC_PREFETCH_CONFIG1_WAITPINSELECTOR_W3                                                             (3U)
#define GPMC_PREFETCH_CONFIG1_WAITPINSELECTOR_W0                                                             (0U)
#define GPMC_PREFETCH_CONFIG1_WAITPINSELECTOR_W1                                                             (1U)
#define GPMC_PREFETCH_CONFIG1_WAITPINSELECTOR_W2                                                             (2U)

#define GPMC_PREFETCH_CONFIG1_ENGINECSSELECTOR_SHIFT                                                        (24U)
#define GPMC_PREFETCH_CONFIG1_ENGINECSSELECTOR_MASK                                                         (0x07000000U)

#define GPMC_PREFETCH_CONFIG1_RESERVED_224_SHIFT                                                            (20U)
#define GPMC_PREFETCH_CONFIG1_RESERVED_224_MASK                                                             (0x00700000U)

#define GPMC_PREFETCH_CONFIG1_PFPWWEIGHTEDPRIO_SHIFT                                                        (16U)
#define GPMC_PREFETCH_CONFIG1_PFPWWEIGHTEDPRIO_MASK                                                         (0x000f0000U)

#define GPMC_PREFETCH_CONFIG1_PFPWENROUNDROBIN_SHIFT                                                        (23U)
#define GPMC_PREFETCH_CONFIG1_PFPWENROUNDROBIN_MASK                                                         (0x00800000U)
#define GPMC_PREFETCH_CONFIG1_PFPWENROUNDROBIN_RRENABLED                                                     (1U)
#define GPMC_PREFETCH_CONFIG1_PFPWENROUNDROBIN_RRDISABLED                                                    (0U)

#define GPMC_PREFETCH_CONFIG2_RESERVED_224_SHIFT                                                            (14U)
#define GPMC_PREFETCH_CONFIG2_RESERVED_224_MASK                                                             (0xffffc000U)

#define GPMC_PREFETCH_CONFIG2_TRANSFERCOUNT_SHIFT                                                           (0U)
#define GPMC_PREFETCH_CONFIG2_TRANSFERCOUNT_MASK                                                            (0x00003fffU)

#define GPMC_PREFETCH_CONTROL_RESERVED_225_SHIFT                                                            (1U)
#define GPMC_PREFETCH_CONTROL_RESERVED_225_MASK                                                             (0xfffffffeU)

#define GPMC_PREFETCH_CONTROL_STARTENGINE_SHIFT                                                             (0U)
#define GPMC_PREFETCH_CONTROL_STARTENGINE_MASK                                                              (0x00000001U)
#define GPMC_PREFETCH_CONTROL_STARTENGINE_STOP                                                               (0U)
#define GPMC_PREFETCH_CONTROL_STARTENGINE_START                                                              (1U)

#define GPMC_PREFETCH_STATUS_FIFOTHRESHOLDSTATUS_SHIFT                                                      (16U)
#define GPMC_PREFETCH_STATUS_FIFOTHRESHOLDSTATUS_MASK                                                       (0x00010000U)
#define GPMC_PREFETCH_STATUS_FIFOTHRESHOLDSTATUS_SMALLERTHANTHRES                                            (0U)
#define GPMC_PREFETCH_STATUS_FIFOTHRESHOLDSTATUS_GREATERTHANTHRES                                            (1U)

#define GPMC_PREFETCH_STATUS_RESERVED_226_SHIFT                                                             (14U)
#define GPMC_PREFETCH_STATUS_RESERVED_226_MASK                                                              (0x0000c000U)

#define GPMC_PREFETCH_STATUS_COUNTVALUE_SHIFT                                                               (0U)
#define GPMC_PREFETCH_STATUS_COUNTVALUE_MASK                                                                (0x00003fffU)

#define GPMC_PREFETCH_STATUS_RESERVED_227_SHIFT                                                             (31U)
#define GPMC_PREFETCH_STATUS_RESERVED_227_MASK                                                              (0x80000000U)

#define GPMC_PREFETCH_STATUS_FIFOPOINTER_SHIFT                                                              (24U)
#define GPMC_PREFETCH_STATUS_FIFOPOINTER_MASK                                                               (0x7f000000U)

#define GPMC_PREFETCH_STATUS_RESERVED_228_SHIFT                                                             (17U)
#define GPMC_PREFETCH_STATUS_RESERVED_228_MASK                                                              (0x00fe0000U)

#define GPMC_ECC_CONFIG_ECC16B_SHIFT                                                                        (7U)
#define GPMC_ECC_CONFIG_ECC16B_MASK                                                                         (0x00000080U)
#define GPMC_ECC_CONFIG_ECC16B_EIGHTCOL                                                                      (0U)
#define GPMC_ECC_CONFIG_ECC16B_SIXTEENCOL                                                                    (1U)

#define GPMC_ECC_CONFIG_ECCWRAPMODE_SHIFT                                                                   (8U)
#define GPMC_ECC_CONFIG_ECCWRAPMODE_MASK                                                                    (0x00000f00U)

#define GPMC_ECC_CONFIG_ECCCS_SHIFT                                                                         (1U)
#define GPMC_ECC_CONFIG_ECCCS_MASK                                                                          (0x0000000eU)
#define GPMC_ECC_CONFIG_ECCCS_CS0                                                                            (0U)
#define GPMC_ECC_CONFIG_ECCCS_CS1                                                                            (1U)
#define GPMC_ECC_CONFIG_ECCCS_CS2                                                                            (2U)
#define GPMC_ECC_CONFIG_ECCCS_CS3                                                                            (3U)
#define GPMC_ECC_CONFIG_ECCCS_CS4                                                                            (4U)
#define GPMC_ECC_CONFIG_ECCCS_CS5                                                                            (5U)
#define GPMC_ECC_CONFIG_ECCCS_CS6                                                                            (6U)
#define GPMC_ECC_CONFIG_ECCCS_CS7                                                                            (7U)

#define GPMC_ECC_CONFIG_ECCENABLE_SHIFT                                                                     (0U)
#define GPMC_ECC_CONFIG_ECCENABLE_MASK                                                                      (0x00000001U)
#define GPMC_ECC_CONFIG_ECCENABLE_ECCDISABLED                                                                (0U)
#define GPMC_ECC_CONFIG_ECCENABLE_ECCENABLED                                                                 (1U)

#define GPMC_ECC_CONFIG_RESERVED_206_SHIFT                                                                  (17U)
#define GPMC_ECC_CONFIG_RESERVED_206_MASK                                                                   (0xfffe0000U)

#define GPMC_ECC_CONFIG_ECCBCHTSEL_SHIFT                                                                    (12U)
#define GPMC_ECC_CONFIG_ECCBCHTSEL_MASK                                                                     (0x00003000U)

#define GPMC_ECC_CONFIG_ECCALGORITHM_SHIFT                                                                  (16U)
#define GPMC_ECC_CONFIG_ECCALGORITHM_MASK                                                                   (0x00010000U)

#define GPMC_ECC_CONFIG_RESERVED_205_SHIFT                                                                  (14U)
#define GPMC_ECC_CONFIG_RESERVED_205_MASK                                                                   (0x0000c000U)

#define GPMC_ECC_CONFIG_ECCTOPSECTOR_SHIFT                                                                  (4U)
#define GPMC_ECC_CONFIG_ECCTOPSECTOR_MASK                                                                   (0x00000070U)

#define GPMC_ECC_CONTROL_RESERVED_207_SHIFT                                                                 (9U)
#define GPMC_ECC_CONTROL_RESERVED_207_MASK                                                                  (0xfffffe00U)

#define GPMC_ECC_CONTROL_ECCCLEAR_SHIFT                                                                     (8U)
#define GPMC_ECC_CONTROL_ECCCLEAR_MASK                                                                      (0x00000100U)

#define GPMC_ECC_CONTROL_RESERVED_208_SHIFT                                                                 (4U)
#define GPMC_ECC_CONTROL_RESERVED_208_MASK                                                                  (0x000000f0U)

#define GPMC_ECC_CONTROL_ECCPOINTER_SHIFT                                                                   (0U)
#define GPMC_ECC_CONTROL_ECCPOINTER_MASK                                                                    (0x0000000fU)
#define GPMC_ECC_CONTROL_ECCPOINTER_NOEFFECT1                                                                (0U)
#define GPMC_ECC_CONTROL_ECCPOINTER_ECCRES1                                                                  (1U)
#define GPMC_ECC_CONTROL_ECCPOINTER_ECCRES2                                                                  (2U)
#define GPMC_ECC_CONTROL_ECCPOINTER_ECCRES3                                                                  (3U)
#define GPMC_ECC_CONTROL_ECCPOINTER_ECCRES4                                                                  (4U)
#define GPMC_ECC_CONTROL_ECCPOINTER_ECCRES5                                                                  (5U)
#define GPMC_ECC_CONTROL_ECCPOINTER_ECCRES6                                                                  (6U)
#define GPMC_ECC_CONTROL_ECCPOINTER_ECCRES7                                                                  (7U)
#define GPMC_ECC_CONTROL_ECCPOINTER_ECCRES8                                                                  (8U)
#define GPMC_ECC_CONTROL_ECCPOINTER_ECCRES9                                                                  (9U)

#define GPMC_ECC_SIZE_CONFIG_ECC3RESULTSIZE_SHIFT                                                           (2U)
#define GPMC_ECC_SIZE_CONFIG_ECC3RESULTSIZE_MASK                                                            (0x00000004U)
#define GPMC_ECC_SIZE_CONFIG_ECC3RESULTSIZE_SIZE0SEL                                                         (0U)
#define GPMC_ECC_SIZE_CONFIG_ECC3RESULTSIZE_SIZE1SEL                                                         (1U)

#define GPMC_ECC_SIZE_CONFIG_ECC5RESULTSIZE_SHIFT                                                           (4U)
#define GPMC_ECC_SIZE_CONFIG_ECC5RESULTSIZE_MASK                                                            (0x00000010U)
#define GPMC_ECC_SIZE_CONFIG_ECC5RESULTSIZE_SIZE0SEL                                                         (0U)
#define GPMC_ECC_SIZE_CONFIG_ECC5RESULTSIZE_SIZE1SEL                                                         (1U)

#define GPMC_ECC_SIZE_CONFIG_ECC2RESULTSIZE_SHIFT                                                           (1U)
#define GPMC_ECC_SIZE_CONFIG_ECC2RESULTSIZE_MASK                                                            (0x00000002U)
#define GPMC_ECC_SIZE_CONFIG_ECC2RESULTSIZE_SIZE0SEL                                                         (0U)
#define GPMC_ECC_SIZE_CONFIG_ECC2RESULTSIZE_SIZE1SEL                                                         (1U)

#define GPMC_ECC_SIZE_CONFIG_ECC1RESULTSIZE_SHIFT                                                           (0U)
#define GPMC_ECC_SIZE_CONFIG_ECC1RESULTSIZE_MASK                                                            (0x00000001U)
#define GPMC_ECC_SIZE_CONFIG_ECC1RESULTSIZE_SIZE0SEL                                                         (0U)
#define GPMC_ECC_SIZE_CONFIG_ECC1RESULTSIZE_SIZE1SEL                                                         (1U)

#define GPMC_ECC_SIZE_CONFIG_ECCSIZE0_SHIFT                                                                 (12U)
#define GPMC_ECC_SIZE_CONFIG_ECCSIZE0_MASK                                                                  (0x000ff000U)

#define GPMC_ECC_SIZE_CONFIG_RESERVED_209_SHIFT                                                             (9U)
#define GPMC_ECC_SIZE_CONFIG_RESERVED_209_MASK                                                              (0x00000e00U)

#define GPMC_ECC_SIZE_CONFIG_ECC7RESULTSIZE_SHIFT                                                           (6U)
#define GPMC_ECC_SIZE_CONFIG_ECC7RESULTSIZE_MASK                                                            (0x00000040U)
#define GPMC_ECC_SIZE_CONFIG_ECC7RESULTSIZE_SIZE0SEL                                                         (0U)
#define GPMC_ECC_SIZE_CONFIG_ECC7RESULTSIZE_SIZE1SEL                                                         (1U)

#define GPMC_ECC_SIZE_CONFIG_ECC9RESULTSIZE_SHIFT                                                           (8U)
#define GPMC_ECC_SIZE_CONFIG_ECC9RESULTSIZE_MASK                                                            (0x00000100U)
#define GPMC_ECC_SIZE_CONFIG_ECC9RESULTSIZE_SIZE0SEL                                                         (0U)
#define GPMC_ECC_SIZE_CONFIG_ECC9RESULTSIZE_SIZE1SEL                                                         (1U)

#define GPMC_ECC_SIZE_CONFIG_RESERVED_210_SHIFT                                                             (30U)
#define GPMC_ECC_SIZE_CONFIG_RESERVED_210_MASK                                                              (0xc0000000U)

#define GPMC_ECC_SIZE_CONFIG_ECC4RESULTSIZE_SHIFT                                                           (3U)
#define GPMC_ECC_SIZE_CONFIG_ECC4RESULTSIZE_MASK                                                            (0x00000008U)
#define GPMC_ECC_SIZE_CONFIG_ECC4RESULTSIZE_SIZE0SEL                                                         (0U)
#define GPMC_ECC_SIZE_CONFIG_ECC4RESULTSIZE_SIZE1SEL                                                         (1U)

#define GPMC_ECC_SIZE_CONFIG_ECC6RESULTSIZE_SHIFT                                                           (5U)
#define GPMC_ECC_SIZE_CONFIG_ECC6RESULTSIZE_MASK                                                            (0x00000020U)
#define GPMC_ECC_SIZE_CONFIG_ECC6RESULTSIZE_SIZE0SEL                                                         (0U)
#define GPMC_ECC_SIZE_CONFIG_ECC6RESULTSIZE_SIZE1SEL                                                         (1U)

#define GPMC_ECC_SIZE_CONFIG_ECC8RESULTSIZE_SHIFT                                                           (7U)
#define GPMC_ECC_SIZE_CONFIG_ECC8RESULTSIZE_MASK                                                            (0x00000080U)
#define GPMC_ECC_SIZE_CONFIG_ECC8RESULTSIZE_SIZE0SEL                                                         (0U)
#define GPMC_ECC_SIZE_CONFIG_ECC8RESULTSIZE_SIZE1SEL                                                         (1U)

#define GPMC_ECC_SIZE_CONFIG_ECCSIZE1_SHIFT                                                                 (22U)
#define GPMC_ECC_SIZE_CONFIG_ECCSIZE1_MASK                                                                  (0x3fc00000U)

#define GPMC_ECC_SIZE_CONFIG_RESERVED_211_SHIFT                                                             (20U)
#define GPMC_ECC_SIZE_CONFIG_RESERVED_211_MASK                                                              (0x00300000U)

#define GPMC_ECCN_RESULT_P512O_SHIFT                                                                        (25U)
#define GPMC_ECCN_RESULT_P512O_MASK                                                                         (0x02000000U)

#define GPMC_ECCN_RESULT_P256O_SHIFT                                                                        (24U)
#define GPMC_ECCN_RESULT_P256O_MASK                                                                         (0x01000000U)

#define GPMC_ECCN_RESULT_RESERVED_187_SHIFT                                                                 (12U)
#define GPMC_ECCN_RESULT_RESERVED_187_MASK                                                                  (0x0000f000U)

#define GPMC_ECCN_RESULT_P128O_SHIFT                                                                        (23U)
#define GPMC_ECCN_RESULT_P128O_MASK                                                                         (0x00800000U)

#define GPMC_ECCN_RESULT_P2048E_SHIFT                                                                       (11U)
#define GPMC_ECCN_RESULT_P2048E_MASK                                                                        (0x00000800U)

#define GPMC_ECCN_RESULT_P64O_SHIFT                                                                         (22U)
#define GPMC_ECCN_RESULT_P64O_MASK                                                                          (0x00400000U)

#define GPMC_ECCN_RESULT_P4E_SHIFT                                                                          (2U)
#define GPMC_ECCN_RESULT_P4E_MASK                                                                           (0x00000004U)

#define GPMC_ECCN_RESULT_P1024E_SHIFT                                                                       (10U)
#define GPMC_ECCN_RESULT_P1024E_MASK                                                                        (0x00000400U)

#define GPMC_ECCN_RESULT_P32O_SHIFT                                                                         (21U)
#define GPMC_ECCN_RESULT_P32O_MASK                                                                          (0x00200000U)

#define GPMC_ECCN_RESULT_P2E_SHIFT                                                                          (1U)
#define GPMC_ECCN_RESULT_P2E_MASK                                                                           (0x00000002U)

#define GPMC_ECCN_RESULT_P512E_SHIFT                                                                        (9U)
#define GPMC_ECCN_RESULT_P512E_MASK                                                                         (0x00000200U)

#define GPMC_ECCN_RESULT_P16O_SHIFT                                                                         (20U)
#define GPMC_ECCN_RESULT_P16O_MASK                                                                          (0x00100000U)

#define GPMC_ECCN_RESULT_RESERVED_188_SHIFT                                                                 (28U)
#define GPMC_ECCN_RESULT_RESERVED_188_MASK                                                                  (0xf0000000U)

#define GPMC_ECCN_RESULT_P1E_SHIFT                                                                          (0U)
#define GPMC_ECCN_RESULT_P1E_MASK                                                                           (0x00000001U)

#define GPMC_ECCN_RESULT_P256E_SHIFT                                                                        (8U)
#define GPMC_ECCN_RESULT_P256E_MASK                                                                         (0x00000100U)

#define GPMC_ECCN_RESULT_P8O_SHIFT                                                                          (19U)
#define GPMC_ECCN_RESULT_P8O_MASK                                                                           (0x00080000U)

#define GPMC_ECCN_RESULT_P2048O_SHIFT                                                                       (27U)
#define GPMC_ECCN_RESULT_P2048O_MASK                                                                        (0x08000000U)

#define GPMC_ECCN_RESULT_P128E_SHIFT                                                                        (7U)
#define GPMC_ECCN_RESULT_P128E_MASK                                                                         (0x00000080U)

#define GPMC_ECCN_RESULT_P4O_SHIFT                                                                          (18U)
#define GPMC_ECCN_RESULT_P4O_MASK                                                                           (0x00040000U)

#define GPMC_ECCN_RESULT_P1024O_SHIFT                                                                       (26U)
#define GPMC_ECCN_RESULT_P1024O_MASK                                                                        (0x04000000U)

#define GPMC_ECCN_RESULT_P64E_SHIFT                                                                         (6U)
#define GPMC_ECCN_RESULT_P64E_MASK                                                                          (0x00000040U)

#define GPMC_ECCN_RESULT_P2O_SHIFT                                                                          (17U)
#define GPMC_ECCN_RESULT_P2O_MASK                                                                           (0x00020000U)

#define GPMC_ECCN_RESULT_P32E_SHIFT                                                                         (5U)
#define GPMC_ECCN_RESULT_P32E_MASK                                                                          (0x00000020U)

#define GPMC_ECCN_RESULT_P1O_SHIFT                                                                          (16U)
#define GPMC_ECCN_RESULT_P1O_MASK                                                                           (0x00010000U)

#define GPMC_ECCN_RESULT_P16E_SHIFT                                                                         (4U)
#define GPMC_ECCN_RESULT_P16E_MASK                                                                          (0x00000010U)

#define GPMC_ECCN_RESULT_P8E_SHIFT                                                                          (3U)
#define GPMC_ECCN_RESULT_P8E_MASK                                                                           (0x00000008U)

#define GPMC_BCH_RESULT_0_BCH_RESULT_0_SHIFT                                                                (0U)
#define GPMC_BCH_RESULT_0_BCH_RESULT_0_MASK                                                                 (0xffffffffU)

#define GPMC_BCH_RESULT_1_BCH_RESULT_1_SHIFT                                                                (0U)
#define GPMC_BCH_RESULT_1_BCH_RESULT_1_MASK                                                                 (0xffffffffU)

#define GPMC_BCH_RESULT_2_BCH_RESULT_2_SHIFT                                                                (0U)
#define GPMC_BCH_RESULT_2_BCH_RESULT_2_MASK                                                                 (0xffffffffU)

#define GPMC_BCH_RESULT_3_BCH_RESULT_3_SHIFT                                                                (0U)
#define GPMC_BCH_RESULT_3_BCH_RESULT_3_MASK                                                                 (0xffffffffU)

#define GPMC_BCH_SWDATA_BCH_DATA_SHIFT                                                                      (0U)
#define GPMC_BCH_SWDATA_BCH_DATA_MASK                                                                       (0x0000ffffU)

#define GPMC_BCH_SWDATA_RESERVED_SHIFT                                                                      (16U)
#define GPMC_BCH_SWDATA_RESERVED_MASK                                                                       (0xffff0000U)

#define GPMC_BCH_RESULT_5_BCH_RESULT_5_SHIFT                                                                (0U)
#define GPMC_BCH_RESULT_5_BCH_RESULT_5_MASK                                                                 (0xffffffffU)

#define GPMC_BCH_RESULT_6_BCH_RESULT_6_SHIFT                                                                (0U)
#define GPMC_BCH_RESULT_6_BCH_RESULT_6_MASK                                                                 (0x0000ffffU)

#define GPMC_BCH_RESULT_6_RESERVED_SHIFT                                                                    (16U)
#define GPMC_BCH_RESULT_6_RESERVED_MASK                                                                     (0xffff0000U)

#define GPMC_BCH_RESULT_4_BCH_RESULT_4_SHIFT                                                                (0U)
#define GPMC_BCH_RESULT_4_BCH_RESULT_4_MASK                                                                 (0xffffffffU)

#define GPMC_CONFIG1_N_DEVICESIZE_SHIFT                                                                     (12U)
#define GPMC_CONFIG1_N_DEVICESIZE_MASK                                                                      (0x00003000U)
#define GPMC_CONFIG1_N_DEVICESIZE_SIXTEENBITS                                                                (1U)
#define GPMC_CONFIG1_N_DEVICESIZE_EIGHTBITS                                                                  (0U)
#define GPMC_CONFIG1_N_DEVICESIZE_THIRTYTWOBITS                                                              (2U)
#define GPMC_CONFIG1_N_DEVICESIZE_RES                                                                        (3U)

#define GPMC_CONFIG1_N_WRITEMULTIPLE_SHIFT                                                                  (28U)
#define GPMC_CONFIG1_N_WRITEMULTIPLE_MASK                                                                   (0x10000000U)
#define GPMC_CONFIG1_N_WRITEMULTIPLE_WRMULTIPLE                                                              (1U)
#define GPMC_CONFIG1_N_WRITEMULTIPLE_WRSINGLE                                                                (0U)

#define GPMC_CONFIG1_N_WRAPBURST_SHIFT                                                                      (31U)
#define GPMC_CONFIG1_N_WRAPBURST_MASK                                                                       (0x80000000U)
#define GPMC_CONFIG1_N_WRAPBURST_WRAPNOTSUPP                                                                 (0U)
#define GPMC_CONFIG1_N_WRAPBURST_WRAPSUPP                                                                    (1U)

#define GPMC_CONFIG1_N_READTYPE_SHIFT                                                                       (29U)
#define GPMC_CONFIG1_N_READTYPE_MASK                                                                        (0x20000000U)
#define GPMC_CONFIG1_N_READTYPE_RDASYNC                                                                      (0U)
#define GPMC_CONFIG1_N_READTYPE_RDSYNC                                                                       (1U)

#define GPMC_CONFIG1_N_READMULTIPLE_SHIFT                                                                   (30U)
#define GPMC_CONFIG1_N_READMULTIPLE_MASK                                                                    (0x40000000U)
#define GPMC_CONFIG1_N_READMULTIPLE_RDSINGLE                                                                 (0U)
#define GPMC_CONFIG1_N_READMULTIPLE_RDMULTIPLE                                                               (1U)

#define GPMC_CONFIG1_N_TIMEPARAGRANULARITY_SHIFT                                                            (4U)
#define GPMC_CONFIG1_N_TIMEPARAGRANULARITY_MASK                                                             (0x00000010U)
#define GPMC_CONFIG1_N_TIMEPARAGRANULARITY_X1                                                                (0U)
#define GPMC_CONFIG1_N_TIMEPARAGRANULARITY_X2                                                                (1U)

#define GPMC_CONFIG1_N_RESERVED_12_SHIFT                                                                    (5U)
#define GPMC_CONFIG1_N_RESERVED_12_MASK                                                                     (0x000000e0U)

#define GPMC_CONFIG1_N_RESERVED_11_SHIFT                                                                    (14U)
#define GPMC_CONFIG1_N_RESERVED_11_MASK                                                                     (0x0000c000U)

#define GPMC_CONFIG1_N_DEVICETYPE_SHIFT                                                                     (10U)
#define GPMC_CONFIG1_N_DEVICETYPE_MASK                                                                      (0x00000c00U)
#define GPMC_CONFIG1_N_DEVICETYPE_RES2                                                                       (3U)
#define GPMC_CONFIG1_N_DEVICETYPE_NORLIKE                                                                    (0U)
#define GPMC_CONFIG1_N_DEVICETYPE_NANDLIKE                                                                   (2U)
#define GPMC_CONFIG1_N_DEVICETYPE_RES1                                                                       (1U)

#define GPMC_CONFIG1_N_GPMCFCLKDIVIDER_SHIFT                                                                (0U)
#define GPMC_CONFIG1_N_GPMCFCLKDIVIDER_MASK                                                                 (0x00000003U)
#define GPMC_CONFIG1_N_GPMCFCLKDIVIDER_DIVBY4                                                                (3U)
#define GPMC_CONFIG1_N_GPMCFCLKDIVIDER_DIVBY2                                                                (1U)
#define GPMC_CONFIG1_N_GPMCFCLKDIVIDER_DIVBY1                                                                (0U)
#define GPMC_CONFIG1_N_GPMCFCLKDIVIDER_DIVBY3                                                                (2U)

#define GPMC_CONFIG1_N_RESERVED_10_SHIFT                                                                    (2U)
#define GPMC_CONFIG1_N_RESERVED_10_MASK                                                                     (0x0000000cU)

#define GPMC_CONFIG1_N_MUXADDDATA_SHIFT                                                                     (8U)
#define GPMC_CONFIG1_N_MUXADDDATA_MASK                                                                      (0x00000300U)
#define GPMC_CONFIG1_N_MUXADDDATA_MUX                                                                        (2U)
#define GPMC_CONFIG1_N_MUXADDDATA_NONMUX                                                                     (0U)
#define GPMC_CONFIG1_N_MUXADDDATA_AADMUX                                                                     (1U)
#define GPMC_CONFIG1_N_MUXADDDATA_RESERVED                                                                   (3U)

#define GPMC_CONFIG1_N_WAITMONITORINGTIME_SHIFT                                                             (18U)
#define GPMC_CONFIG1_N_WAITMONITORINGTIME_MASK                                                              (0x000c0000U)
#define GPMC_CONFIG1_N_WAITMONITORINGTIME_NOTDEFINED                                                         (3U)
#define GPMC_CONFIG1_N_WAITMONITORINGTIME_TWODEVICEB4                                                        (2U)
#define GPMC_CONFIG1_N_WAITMONITORINGTIME_ONEDEVICEB4                                                        (1U)
#define GPMC_CONFIG1_N_WAITMONITORINGTIME_ATVALID                                                            (0U)

#define GPMC_CONFIG1_N_WAITREADMONITORING_SHIFT                                                             (22U)
#define GPMC_CONFIG1_N_WAITREADMONITORING_MASK                                                              (0x00400000U)
#define GPMC_CONFIG1_N_WAITREADMONITORING_WMONIT                                                             (1U)
#define GPMC_CONFIG1_N_WAITREADMONITORING_WNOTMONIT                                                          (0U)

#define GPMC_CONFIG1_N_RESERVED_9_SHIFT                                                                     (20U)
#define GPMC_CONFIG1_N_RESERVED_9_MASK                                                                      (0x00100000U)

#define GPMC_CONFIG1_N_WAITPINSELECT_SHIFT                                                                  (16U)
#define GPMC_CONFIG1_N_WAITPINSELECT_MASK                                                                   (0x00030000U)
#define GPMC_CONFIG1_N_WAITPINSELECT_W2                                                                      (2U)
#define GPMC_CONFIG1_N_WAITPINSELECT_W1                                                                      (1U)
#define GPMC_CONFIG1_N_WAITPINSELECT_W3                                                                      (3U)
#define GPMC_CONFIG1_N_WAITPINSELECT_W0                                                                      (0U)

#define GPMC_CONFIG1_N_CLKACTIVATIONTIME_SHIFT                                                              (25U)
#define GPMC_CONFIG1_N_CLKACTIVATIONTIME_MASK                                                               (0x06000000U)
#define GPMC_CONFIG1_N_CLKACTIVATIONTIME_ATSTART                                                             (0U)
#define GPMC_CONFIG1_N_CLKACTIVATIONTIME_TWOCLKB4                                                            (2U)
#define GPMC_CONFIG1_N_CLKACTIVATIONTIME_ONECLKB4                                                            (1U)
#define GPMC_CONFIG1_N_CLKACTIVATIONTIME_NOTDEFINED                                                          (3U)

#define GPMC_CONFIG1_N_WAITWRITEMONITORING_SHIFT                                                            (21U)
#define GPMC_CONFIG1_N_WAITWRITEMONITORING_MASK                                                             (0x00200000U)
#define GPMC_CONFIG1_N_WAITWRITEMONITORING_WNOTMONIT                                                         (0U)
#define GPMC_CONFIG1_N_WAITWRITEMONITORING_WMONIT                                                            (1U)

#define GPMC_CONFIG1_N_ATTACHEDDEVICEPAGELENGTH_SHIFT                                                       (23U)
#define GPMC_CONFIG1_N_ATTACHEDDEVICEPAGELENGTH_MASK                                                        (0x01800000U)
#define GPMC_CONFIG1_N_ATTACHEDDEVICEPAGELENGTH_EIGHT                                                        (1U)
#define GPMC_CONFIG1_N_ATTACHEDDEVICEPAGELENGTH_SIXTEEN                                                      (2U)
#define GPMC_CONFIG1_N_ATTACHEDDEVICEPAGELENGTH_THIRTYTWO                                                    (3U)
#define GPMC_CONFIG1_N_ATTACHEDDEVICEPAGELENGTH_FOUR                                                         (0U)

#define GPMC_CONFIG1_N_WRITETYPE_SHIFT                                                                      (27U)
#define GPMC_CONFIG1_N_WRITETYPE_MASK                                                                       (0x08000000U)
#define GPMC_CONFIG1_N_WRITETYPE_WRASYNC                                                                     (0U)
#define GPMC_CONFIG1_N_WRITETYPE_WRSYNC                                                                      (1U)

#define GPMC_CONFIG2_N_RESERVED_43_SHIFT                                                                    (21U)
#define GPMC_CONFIG2_N_RESERVED_43_MASK                                                                     (0xffe00000U)

#define GPMC_CONFIG2_N_RESERVED_44_SHIFT                                                                    (4U)
#define GPMC_CONFIG2_N_RESERVED_44_MASK                                                                     (0x00000070U)

#define GPMC_CONFIG2_N_CSONTIME_SHIFT                                                                       (0U)
#define GPMC_CONFIG2_N_CSONTIME_MASK                                                                        (0x0000000fU)

#define GPMC_CONFIG2_N_CSWROFFTIME_SHIFT                                                                    (16U)
#define GPMC_CONFIG2_N_CSWROFFTIME_MASK                                                                     (0x001f0000U)

#define GPMC_CONFIG2_N_RESERVED_45_SHIFT                                                                    (13U)
#define GPMC_CONFIG2_N_RESERVED_45_MASK                                                                     (0x0000e000U)

#define GPMC_CONFIG2_N_CSRDOFFTIME_SHIFT                                                                    (8U)
#define GPMC_CONFIG2_N_CSRDOFFTIME_MASK                                                                     (0x00001f00U)

#define GPMC_CONFIG2_N_CSEXTRADELAY_SHIFT                                                                   (7U)
#define GPMC_CONFIG2_N_CSEXTRADELAY_MASK                                                                    (0x00000080U)
#define GPMC_CONFIG2_N_CSEXTRADELAY_NOTDELAYED                                                               (0U)
#define GPMC_CONFIG2_N_CSEXTRADELAY_DELAYED                                                                  (1U)

#define GPMC_CONFIG3_N_ADVEXTRADELAY_SHIFT                                                                  (7U)
#define GPMC_CONFIG3_N_ADVEXTRADELAY_MASK                                                                   (0x00000080U)
#define GPMC_CONFIG3_N_ADVEXTRADELAY_NOTDELAYED                                                              (0U)
#define GPMC_CONFIG3_N_ADVEXTRADELAY_DELAYED                                                                 (1U)

#define GPMC_CONFIG3_N_ADVAADMUXONTIME_SHIFT                                                                (4U)
#define GPMC_CONFIG3_N_ADVAADMUXONTIME_MASK                                                                 (0x00000070U)

#define GPMC_CONFIG3_N_RESERVED_68_SHIFT                                                                    (21U)
#define GPMC_CONFIG3_N_RESERVED_68_MASK                                                                     (0x00e00000U)

#define GPMC_CONFIG3_N_ADVONTIME_SHIFT                                                                      (0U)
#define GPMC_CONFIG3_N_ADVONTIME_MASK                                                                       (0x0000000fU)

#define GPMC_CONFIG3_N_ADVWROFFTIME_SHIFT                                                                   (16U)
#define GPMC_CONFIG3_N_ADVWROFFTIME_MASK                                                                    (0x001f0000U)

#define GPMC_CONFIG3_N_RESERVED_69_SHIFT                                                                    (13U)
#define GPMC_CONFIG3_N_RESERVED_69_MASK                                                                     (0x0000e000U)

#define GPMC_CONFIG3_N_ADVRDOFFTIME_SHIFT                                                                   (8U)
#define GPMC_CONFIG3_N_ADVRDOFFTIME_MASK                                                                    (0x00001f00U)

#define GPMC_CONFIG3_N_ADVAADMUXRDOFFTIME_SHIFT                                                             (24U)
#define GPMC_CONFIG3_N_ADVAADMUXRDOFFTIME_MASK                                                              (0x07000000U)

#define GPMC_CONFIG3_N_ADVAADMUXWROFFTIME_SHIFT                                                             (28U)
#define GPMC_CONFIG3_N_ADVAADMUXWROFFTIME_MASK                                                              (0x70000000U)

#define GPMC_CONFIG3_N_RESERVED_0_SHIFT                                                                     (27U)
#define GPMC_CONFIG3_N_RESERVED_0_MASK                                                                      (0x08000000U)

#define GPMC_CONFIG3_N_RESERVED_1_SHIFT                                                                     (31U)
#define GPMC_CONFIG3_N_RESERVED_1_MASK                                                                      (0x80000000U)

#define GPMC_CONFIG4_N_OEONTIME_SHIFT                                                                       (0U)
#define GPMC_CONFIG4_N_OEONTIME_MASK                                                                        (0x0000000fU)

#define GPMC_CONFIG4_N_RESERVED_92_SHIFT                                                                    (20U)
#define GPMC_CONFIG4_N_RESERVED_92_MASK                                                                     (0x00700000U)

#define GPMC_CONFIG4_N_WEONTIME_SHIFT                                                                       (16U)
#define GPMC_CONFIG4_N_WEONTIME_MASK                                                                        (0x000f0000U)

#define GPMC_CONFIG4_N_OEOFFTIME_SHIFT                                                                      (8U)
#define GPMC_CONFIG4_N_OEOFFTIME_MASK                                                                       (0x00001f00U)

#define GPMC_CONFIG4_N_WEOFFTIME_SHIFT                                                                      (24U)
#define GPMC_CONFIG4_N_WEOFFTIME_MASK                                                                       (0x1f000000U)

#define GPMC_CONFIG4_N_OEEXTRADELAY_SHIFT                                                                   (7U)
#define GPMC_CONFIG4_N_OEEXTRADELAY_MASK                                                                    (0x00000080U)
#define GPMC_CONFIG4_N_OEEXTRADELAY_NOTDELAYED                                                               (0U)
#define GPMC_CONFIG4_N_OEEXTRADELAY_DELAYED                                                                  (1U)

#define GPMC_CONFIG4_N_WEEXTRADELAY_SHIFT                                                                   (23U)
#define GPMC_CONFIG4_N_WEEXTRADELAY_MASK                                                                    (0x00800000U)
#define GPMC_CONFIG4_N_WEEXTRADELAY_NOTDELAYED                                                               (0U)
#define GPMC_CONFIG4_N_WEEXTRADELAY_DELAYED                                                                  (1U)

#define GPMC_CONFIG4_N_OEAADMUXOFFTIME_SHIFT                                                                (13U)
#define GPMC_CONFIG4_N_OEAADMUXOFFTIME_MASK                                                                 (0x0000e000U)

#define GPMC_CONFIG4_N_OEAADMUXONTIME_SHIFT                                                                 (4U)
#define GPMC_CONFIG4_N_OEAADMUXONTIME_MASK                                                                  (0x00000070U)

#define GPMC_CONFIG4_N_RESERVED_SHIFT                                                                       (29U)
#define GPMC_CONFIG4_N_RESERVED_MASK                                                                        (0xe0000000U)

#define GPMC_CONFIG5_N_WRCYCLETIME_SHIFT                                                                    (8U)
#define GPMC_CONFIG5_N_WRCYCLETIME_MASK                                                                     (0x00001f00U)

#define GPMC_CONFIG5_N_RESERVED_123_SHIFT                                                                   (5U)
#define GPMC_CONFIG5_N_RESERVED_123_MASK                                                                    (0x000000e0U)

#define GPMC_CONFIG5_N_RDCYCLETIME_SHIFT                                                                    (0U)
#define GPMC_CONFIG5_N_RDCYCLETIME_MASK                                                                     (0x0000001fU)

#define GPMC_CONFIG5_N_RESERVED_124_SHIFT                                                                   (28U)
#define GPMC_CONFIG5_N_RESERVED_124_MASK                                                                    (0xf0000000U)

#define GPMC_CONFIG5_N_PAGEBURSTACCESSTIME_SHIFT                                                            (24U)
#define GPMC_CONFIG5_N_PAGEBURSTACCESSTIME_MASK                                                             (0x0f000000U)

#define GPMC_CONFIG5_N_RESERVED_125_SHIFT                                                                   (21U)
#define GPMC_CONFIG5_N_RESERVED_125_MASK                                                                    (0x00e00000U)

#define GPMC_CONFIG5_N_RDACCESSTIME_SHIFT                                                                   (16U)
#define GPMC_CONFIG5_N_RDACCESSTIME_MASK                                                                    (0x001f0000U)

#define GPMC_CONFIG5_N_RESERVED_126_SHIFT                                                                   (13U)
#define GPMC_CONFIG5_N_RESERVED_126_MASK                                                                    (0x0000e000U)

#define GPMC_CONFIG6_N_CYCLE2CYCLEDIFFCSEN_SHIFT                                                            (6U)
#define GPMC_CONFIG6_N_CYCLE2CYCLEDIFFCSEN_MASK                                                             (0x00000040U)
#define GPMC_CONFIG6_N_CYCLE2CYCLEDIFFCSEN_NOC2CDELAY                                                        (0U)
#define GPMC_CONFIG6_N_CYCLE2CYCLEDIFFCSEN_C2CDELAY                                                          (1U)

#define GPMC_CONFIG6_N_RESERVED_155_SHIFT                                                                   (20U)
#define GPMC_CONFIG6_N_RESERVED_155_MASK                                                                    (0x00f00000U)

#define GPMC_CONFIG6_N_CYCLE2CYCLEDELAY_SHIFT                                                               (8U)
#define GPMC_CONFIG6_N_CYCLE2CYCLEDELAY_MASK                                                                (0x00000f00U)

#define GPMC_CONFIG6_N_RESERVED_156_SHIFT                                                                   (4U)
#define GPMC_CONFIG6_N_RESERVED_156_MASK                                                                    (0x00000030U)

#define GPMC_CONFIG6_N_CYCLE2CYCLESAMECSEN_SHIFT                                                            (7U)
#define GPMC_CONFIG6_N_CYCLE2CYCLESAMECSEN_MASK                                                             (0x00000080U)
#define GPMC_CONFIG6_N_CYCLE2CYCLESAMECSEN_NOC2CDELAY                                                        (0U)
#define GPMC_CONFIG6_N_CYCLE2CYCLESAMECSEN_C2CDELAY                                                          (1U)

#define GPMC_CONFIG6_N_BUSTURNAROUND_SHIFT                                                                  (0U)
#define GPMC_CONFIG6_N_BUSTURNAROUND_MASK                                                                   (0x0000000fU)

#define GPMC_CONFIG6_N_WRDATAONADMUXBUS_SHIFT                                                               (16U)
#define GPMC_CONFIG6_N_WRDATAONADMUXBUS_MASK                                                                (0x000f0000U)

#define GPMC_CONFIG6_N_RESERVED_1_SHIFT                                                                     (12U)
#define GPMC_CONFIG6_N_RESERVED_1_MASK                                                                      (0x0000f000U)

#define GPMC_CONFIG6_N_RESERVED_0_SHIFT                                                                     (29U)
#define GPMC_CONFIG6_N_RESERVED_0_MASK                                                                      (0x60000000U)

#define GPMC_CONFIG6_N_WRACCESSTIME_SHIFT                                                                   (24U)
#define GPMC_CONFIG6_N_WRACCESSTIME_MASK                                                                    (0x1f000000U)

#define GPMC_CONFIG6_N_RESERVED_SHIFT                                                                       (31U)
#define GPMC_CONFIG6_N_RESERVED_MASK                                                                        (0x80000000U)

#define GPMC_CONFIG7_N_BASEADDRESS_SHIFT                                                                    (0U)
#define GPMC_CONFIG7_N_BASEADDRESS_MASK                                                                     (0x0000003fU)

#define GPMC_CONFIG7_N_RESERVED_171_SHIFT                                                                   (12U)
#define GPMC_CONFIG7_N_RESERVED_171_MASK                                                                    (0xfffff000U)

#define GPMC_CONFIG7_N_MASKADDRESS_SHIFT                                                                    (8U)
#define GPMC_CONFIG7_N_MASKADDRESS_MASK                                                                     (0x00000f00U)

#define GPMC_CONFIG7_N_RESERVED_172_SHIFT                                                                   (7U)
#define GPMC_CONFIG7_N_RESERVED_172_MASK                                                                    (0x00000080U)

#define GPMC_CONFIG7_N_CSVALID_SHIFT                                                                        (6U)
#define GPMC_CONFIG7_N_CSVALID_MASK                                                                         (0x00000040U)
#define GPMC_CONFIG7_N_CSVALID_CSDISABLED                                                                    (0U)
#define GPMC_CONFIG7_N_CSVALID_CSENABLED                                                                     (1U)

#define GPMC_NAND_COMMAND_N_GPMC_NAND_COMMAND_N_SHIFT                                                       (0U)
#define GPMC_NAND_COMMAND_N_GPMC_NAND_COMMAND_N_MASK                                                        (0xffffffffU)

#define GPMC_NAND_ADDRESS_N_GPMC_NAND_ADDRESS_N_SHIFT                                                       (0U)
#define GPMC_NAND_ADDRESS_N_GPMC_NAND_ADDRESS_N_MASK                                                        (0xffffffffU)

#define GPMC_NAND_DATA_N_GPMC_NAND_DATA_N_SHIFT                                                             (0U)
#define GPMC_NAND_DATA_N_GPMC_NAND_DATA_N_MASK                                                              (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_GPMC_H_ */
