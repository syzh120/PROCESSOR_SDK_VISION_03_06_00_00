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

#ifndef HW_OCMC_RAM_H_
#define HW_OCMC_RAM_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions
****************************************************************************************************/
#define OCMC_RAM_OCMC_ECC_PID                                                                              (0x0U)
#define OCMC_RAM_OCMC_SYSCONFIG_PM                                                                         (0x4U)
#define OCMC_RAM_OCMC_SYSCONFIG_RST                                                                        (0x8U)
#define OCMC_RAM_OCMC_MEM_SIZE_READ                                                                        (0xcU)
#define OCMC_RAM_INTR0_STATUS_RAW_SET                                                                      (0x40U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR                                                                (0x44U)
#define OCMC_RAM_INTR0_ENABLE_SET                                                                          (0x48U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR                                                                        (0x4cU)
#define OCMC_RAM_INTR1_STATUS_RAW_SET                                                                      (0x60U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR                                                                (0x64U)
#define OCMC_RAM_INTR1_ENABLE_SET                                                                          (0x68U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR                                                                        (0x6cU)
#define OCMC_RAM_STATUS_ERROR_CNT                                                                          (0x90U)
#define OCMC_RAM_STATUS_SEC_ERROR_TRACE                                                                    (0x94U)
#define OCMC_RAM_STATUS_DED_ERROR_TRACE                                                                    (0x98U)
#define OCMC_RAM_STATUS_ADDR_TRANSLATION_ERROR_TRACE                                                       (0x9cU)
#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_0                                                                  (0xa0U)
#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_1                                                                  (0xa4U)
#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_2                                                                  (0xa8U)
#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_3                                                                  (0xacU)
#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_4                                                                  (0xb0U)
#define OCMC_RAM_CFG_OCMC_ECC                                                                              (0x80U)
#define OCMC_RAM_CFG_OCMC_ECC_MEM_BLK                                                                      (0x84U)
#define OCMC_RAM_CFG_OCMC_ECC_ERROR                                                                        (0x88U)
#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST                                                                   (0x8cU)
#define OCMC_RAM_CFG_OCMC_CBUF_EN                                                                          (0x200U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET                                                                       (0x204U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER                                                                 (0x208U)
#define OCMC_RAM_STATUS_CBUF_WR_OUT_OF_RANGE_ERR                                                           (0x20cU)
#define OCMC_RAM_STATUS_CBUF_WR_VBUF_START_ERR                                                             (0x210U)
#define OCMC_RAM_STATUS_CBUF_WR_ADDR_SEQ_ERROR                                                             (0x214U)
#define OCMC_RAM_STATUS_CBUF_RD_OUT_OF_RANGE_ERROR                                                         (0x218U)
#define OCMC_RAM_STATUS_CBUF_VBUF_RD_START_ERROR                                                           (0x21cU)
#define OCMC_RAM_STATUS_CBUF_RD_ADDR_SEQ_ERROR                                                             (0x220U)
#define OCMC_RAM_STATUS_CBUF_OVERFLOW_MID                                                                  (0x224U)
#define OCMC_RAM_STATUS_CBUF_OVERFLOW_WRAP                                                                 (0x228U)
#define OCMC_RAM_STATUS_CBUF_UNDERFLOW                                                                     (0x22cU)
#define OCMC_RAM_STATUS_CBUF_SHORT_FRAME_DETECT                                                            (0x230U)
#define OCMC_RAM_CBUF_VBUF_START_ADDR(n)                                                                   ((uint32_t)0x240U + ((n) * 16U))
#define OCMC_RAM_CBUF_VBUF_END_ADDR(n)                                                                     ((uint32_t)0x244U + ((n) * 16U))
#define OCMC_RAM_CBUF_OCMC_START_ADDR(n)                                                                   ((uint32_t)0x248U + ((n) * 16U))
#define OCMC_RAM_CBUF_OCMC_BUF_SIZE(n)                                                                     ((uint32_t)0x24cU + ((n) * 16U))
#define OCMC_RAM_CBUF_LAST_WR_ADDR(n)                                                                      ((uint32_t)0x300U + ((n) * 8U))
#define OCMC_RAM_CBUF_LAST_RD_ADDR(n)                                                                      ((uint32_t)0x304U + ((n) * 8U))
#define OCMC_RAM_LAST_ILLEGAL_OCMC_ADDR                                                                    (0x360U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define OCMC_RAM_OCMC_ECC_PID_MINOR_SHIFT                                                                 (0U)
#define OCMC_RAM_OCMC_ECC_PID_MINOR_MASK                                                                  (0x0000003fU)

#define OCMC_RAM_OCMC_ECC_PID_CUSTOM_SHIFT                                                                (6U)
#define OCMC_RAM_OCMC_ECC_PID_CUSTOM_MASK                                                                 (0x000000c0U)

#define OCMC_RAM_OCMC_ECC_PID_MAJOR_SHIFT                                                                 (8U)
#define OCMC_RAM_OCMC_ECC_PID_MAJOR_MASK                                                                  (0x00000700U)

#define OCMC_RAM_OCMC_ECC_PID_RTL_SHIFT                                                                   (11U)
#define OCMC_RAM_OCMC_ECC_PID_RTL_MASK                                                                    (0x0000f800U)

#define OCMC_RAM_OCMC_ECC_PID_FUNC_SHIFT                                                                  (16U)
#define OCMC_RAM_OCMC_ECC_PID_FUNC_MASK                                                                   (0x0fff0000U)

#define OCMC_RAM_OCMC_ECC_PID_RESERVED_SHIFT                                                              (28U)
#define OCMC_RAM_OCMC_ECC_PID_RESERVED_MASK                                                               (0x30000000U)

#define OCMC_RAM_OCMC_ECC_PID_SCHEME_SHIFT                                                                (30U)
#define OCMC_RAM_OCMC_ECC_PID_SCHEME_MASK                                                                 (0xc0000000U)

#define OCMC_RAM_OCMC_SYSCONFIG_PM_IDLEMODE_SHIFT                                                         (2U)
#define OCMC_RAM_OCMC_SYSCONFIG_PM_IDLEMODE_MASK                                                          (0x0000000cU)
#define OCMC_RAM_OCMC_SYSCONFIG_PM_IDLEMODE_FORCE_IDLE                                                    (0U)
#define OCMC_RAM_OCMC_SYSCONFIG_PM_IDLEMODE_NO_IDLE                                                       (1U)
#define OCMC_RAM_OCMC_SYSCONFIG_PM_IDLEMODE_SMART_IDLE                                                    (2U)
#define OCMC_RAM_OCMC_SYSCONFIG_PM_IDLEMODE_SMART_IDLE_WAKEUP_CAPABLE                                     (3U)

#define OCMC_RAM_OCMC_SYSCONFIG_PM_RESERVED_SHIFT                                                         (0U)
#define OCMC_RAM_OCMC_SYSCONFIG_PM_RESERVED_MASK                                                          (0x00000003U)

#define OCMC_RAM_OCMC_SYSCONFIG_PM_RESERVED_2_SHIFT                                                       (4U)
#define OCMC_RAM_OCMC_SYSCONFIG_PM_RESERVED_2_MASK                                                        (0xfffffff0U)

#define OCMC_RAM_OCMC_SYSCONFIG_RST_SW_RST_SHIFT                                                          (0U)
#define OCMC_RAM_OCMC_SYSCONFIG_RST_SW_RST_MASK                                                           (0x00000001U)
#define OCMC_RAM_OCMC_SYSCONFIG_RST_SW_RST_NORMAL_OP                                                      (0U)
#define OCMC_RAM_OCMC_SYSCONFIG_RST_SW_RST_RESET                                                          (1U)

#define OCMC_RAM_OCMC_SYSCONFIG_RST_RESERVED_SHIFT                                                        (1U)
#define OCMC_RAM_OCMC_SYSCONFIG_RST_RESERVED_MASK                                                         (0xfffffffeU)

#define OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_SIZE_128K_CNT_SHIFT                                               (0U)
#define OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_SIZE_128K_CNT_MASK                                                (0x0000001fU)

#define OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_ECC_ENABLE_SHIFT                                                  (8U)
#define OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_ECC_ENABLE_MASK                                                   (0x00000100U)
#define OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_ECC_ENABLE_ECC_OFF                                                (0U)
#define OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_ECC_ENABLE_ECC_ON                                                 (1U)

#define OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_CBUF_ENABLE_SHIFT                                                 (9U)
#define OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_CBUF_ENABLE_MASK                                                  (0x00000200U)
#define OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_CBUF_ENABLE_CBUF_ECC_OFF                                          (0U)
#define OCMC_RAM_OCMC_MEM_SIZE_READ_MEM_CBUF_ENABLE_CBUF_ECC_ON                                           (1U)

#define OCMC_RAM_OCMC_MEM_SIZE_READ_RESERVED_SHIFT                                                        (5U)
#define OCMC_RAM_OCMC_MEM_SIZE_READ_RESERVED_MASK                                                         (0x000000e0U)

#define OCMC_RAM_OCMC_MEM_SIZE_READ_RESERVED_2_SHIFT                                                      (10U)
#define OCMC_RAM_OCMC_MEM_SIZE_READ_RESERVED_2_MASK                                                       (0xfffffc00U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_SEC_ERR_FOUND_SHIFT                                                 (0U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_SEC_ERR_FOUND_MASK                                                  (0x00000001U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_DED_ERR_FOUND_SHIFT                                                 (1U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_DED_ERR_FOUND_MASK                                                  (0x00000002U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_ADDR_ERR_FOUND_SHIFT                                                (2U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_ADDR_ERR_FOUND_MASK                                                 (0x00000004U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_OUT_OF_RANGE_ERR_FOUND_SHIFT                                        (3U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_OUT_OF_RANGE_ERR_FOUND_MASK                                         (0x00000008U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_VIRTUAL_ADDR_ERR_FOUND_SHIFT                                   (4U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_VIRTUAL_ADDR_ERR_FOUND_MASK                                    (0x00000010U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_OVERFLOW_MID_ERR_FOUND_SHIFT                                   (11U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_OVERFLOW_MID_ERR_FOUND_MASK                                    (0x00000800U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_UNDERFLOW_ERR_FOUND_SHIFT                                      (13U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_UNDERFLOW_ERR_FOUND_MASK                                       (0x00002000U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_SHORT_FRAME_DETECT_FOUND_SHIFT                                 (14U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_SHORT_FRAME_DETECT_FOUND_MASK                                  (0x00004000U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_SHIFT                                (5U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_MASK                                 (0x00000020U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_VBUF_WRITE_START_ERR_FOUND_SHIFT                               (6U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_VBUF_WRITE_START_ERR_FOUND_MASK                                (0x00000040U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_WRITE_SEQUENCE_ERR_FOUND_SHIFT                                 (7U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_WRITE_SEQUENCE_ERR_FOUND_MASK                                  (0x00000080U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_SHIFT                              (8U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_MASK                               (0x00000100U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_VBUF_READ_START_ERR_FOUND_SHIFT                                (9U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_VBUF_READ_START_ERR_FOUND_MASK                                 (0x00000200U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_READ_SEQUENCE_ERR_FOUND_SHIFT                                  (10U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_READ_SEQUENCE_ERR_FOUND_MASK                                   (0x00000400U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_OVERFLOW_WRAP_ERR_FOUND_SHIFT                                  (12U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_CBUF_OVERFLOW_WRAP_ERR_FOUND_MASK                                   (0x00001000U)

#define OCMC_RAM_INTR0_STATUS_RAW_SET_RESERVED_SHIFT                                                      (15U)
#define OCMC_RAM_INTR0_STATUS_RAW_SET_RESERVED_MASK                                                       (0xffff8000U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_SEC_ERR_FOUND_SHIFT                                           (0U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_SEC_ERR_FOUND_MASK                                            (0x00000001U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_DED_ERR_FOUND_SHIFT                                           (1U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_DED_ERR_FOUND_MASK                                            (0x00000002U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_ADDR_ERR_FOUND_SHIFT                                          (2U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_ADDR_ERR_FOUND_MASK                                           (0x00000004U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_OUT_OF_RANGE_ERR_FOUND_SHIFT                                  (3U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_OUT_OF_RANGE_ERR_FOUND_MASK                                   (0x00000008U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_VIRTUAL_ADDR_ERR_FOUND_SHIFT                             (4U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_VIRTUAL_ADDR_ERR_FOUND_MASK                              (0x00000010U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_OVERFLOW_MID_ERR_FOUND_SHIFT                             (11U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_OVERFLOW_MID_ERR_FOUND_MASK                              (0x00000800U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_UNDERFLOW_ERR_FOUND_SHIFT                                (13U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_UNDERFLOW_ERR_FOUND_MASK                                 (0x00002000U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_SHORT_FRAME_DETECT_FOUND_SHIFT                           (14U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_SHORT_FRAME_DETECT_FOUND_MASK                            (0x00004000U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_SHIFT                          (5U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_MASK                           (0x00000020U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_VBUF_WRITE_START_ERR_FOUND_SHIFT                         (6U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_VBUF_WRITE_START_ERR_FOUND_MASK                          (0x00000040U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_WRITE_SEQUENCE_ERR_FOUND_SHIFT                           (7U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_WRITE_SEQUENCE_ERR_FOUND_MASK                            (0x00000080U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_SHIFT                        (8U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_MASK                         (0x00000100U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_VBUF_READ_START_ERR_FOUND_SHIFT                          (9U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_VBUF_READ_START_ERR_FOUND_MASK                           (0x00000200U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_READ_SEQUENCE_ERR_FOUND_SHIFT                            (10U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_READ_SEQUENCE_ERR_FOUND_MASK                             (0x00000400U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_OVERFLOW_WRAP_ERR_FOUND_SHIFT                            (12U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_CBUF_OVERFLOW_WRAP_ERR_FOUND_MASK                             (0x00001000U)

#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_RESERVED_SHIFT                                                (15U)
#define OCMC_RAM_INTR0_STATUS_ENABLED_CLEAR_RESERVED_MASK                                                 (0xffff8000U)

#define OCMC_RAM_INTR0_ENABLE_SET_SEC_ERR_FOUND_SHIFT                                                     (0U)
#define OCMC_RAM_INTR0_ENABLE_SET_SEC_ERR_FOUND_MASK                                                      (0x00000001U)

#define OCMC_RAM_INTR0_ENABLE_SET_DED_ERR_FOUND_SHIFT                                                     (1U)
#define OCMC_RAM_INTR0_ENABLE_SET_DED_ERR_FOUND_MASK                                                      (0x00000002U)

#define OCMC_RAM_INTR0_ENABLE_SET_ADDR_ERR_FOUND_SHIFT                                                    (2U)
#define OCMC_RAM_INTR0_ENABLE_SET_ADDR_ERR_FOUND_MASK                                                     (0x00000004U)

#define OCMC_RAM_INTR0_ENABLE_SET_OUT_OF_RANGE_ERR_FOUND_SHIFT                                            (3U)
#define OCMC_RAM_INTR0_ENABLE_SET_OUT_OF_RANGE_ERR_FOUND_MASK                                             (0x00000008U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_VIRTUAL_ADDR_ERR_FOUND_SHIFT                                       (4U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_VIRTUAL_ADDR_ERR_FOUND_MASK                                        (0x00000010U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_OVERFLOW_MID_ERR_FOUND_SHIFT                                       (11U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_OVERFLOW_MID_ERR_FOUND_MASK                                        (0x00000800U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_UNDERFLOW_ERR_FOUND_SHIFT                                          (13U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_UNDERFLOW_ERR_FOUND_MASK                                           (0x00002000U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_SHORT_FRAME_DETECT_FOUND_SHIFT                                     (14U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_SHORT_FRAME_DETECT_FOUND_MASK                                      (0x00004000U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_SHIFT                                    (5U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_MASK                                     (0x00000020U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_VBUF_WRITE_START_ERR_FOUND_SHIFT                                   (6U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_VBUF_WRITE_START_ERR_FOUND_MASK                                    (0x00000040U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_WRITE_SEQUENCE_ERR_FOUND_SHIFT                                     (7U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_WRITE_SEQUENCE_ERR_FOUND_MASK                                      (0x00000080U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_SHIFT                                  (8U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_MASK                                   (0x00000100U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_VBUF_READ_START_ERR_FOUND_SHIFT                                    (9U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_VBUF_READ_START_ERR_FOUND_MASK                                     (0x00000200U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_READ_SEQUENCE_ERR_FOUND_SHIFT                                      (10U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_READ_SEQUENCE_ERR_FOUND_MASK                                       (0x00000400U)

#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_OVERFLOW_WRAP_ERR_FOUND_SHIFT                                      (12U)
#define OCMC_RAM_INTR0_ENABLE_SET_CBUF_OVERFLOW_WRAP_ERR_FOUND_MASK                                       (0x00001000U)

#define OCMC_RAM_INTR0_ENABLE_SET_RESERVED_SHIFT                                                          (15U)
#define OCMC_RAM_INTR0_ENABLE_SET_RESERVED_MASK                                                           (0xffff8000U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_SEC_ERR_FOUND_SHIFT                                                   (0U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_SEC_ERR_FOUND_MASK                                                    (0x00000001U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_DED_ERR_FOUND_SHIFT                                                   (1U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_DED_ERR_FOUND_MASK                                                    (0x00000002U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_ADDR_ERR_FOUND_SHIFT                                                  (2U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_ADDR_ERR_FOUND_MASK                                                   (0x00000004U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_OUT_OF_RANGE_ERR_FOUND_SHIFT                                          (3U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_OUT_OF_RANGE_ERR_FOUND_MASK                                           (0x00000008U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_VIRTUAL_ADDR_ERR_FOUND_SHIFT                                     (4U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_VIRTUAL_ADDR_ERR_FOUND_MASK                                      (0x00000010U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_OVERFLOW_MID_ERR_FOUND_SHIFT                                     (11U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_OVERFLOW_MID_ERR_FOUND_MASK                                      (0x00000800U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_UNDERFLOW_ERR_FOUND_SHIFT                                        (13U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_UNDERFLOW_ERR_FOUND_MASK                                         (0x00002000U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_SHORT_FRAME_DETECT_FOUND_SHIFT                                   (14U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_SHORT_FRAME_DETECT_FOUND_MASK                                    (0x00004000U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_SHIFT                                  (5U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_MASK                                   (0x00000020U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_VBUF_WRITE_START_ERR_FOUND_SHIFT                                 (6U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_VBUF_WRITE_START_ERR_FOUND_MASK                                  (0x00000040U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_WRITE_SEQUENCE_ERR_FOUND_SHIFT                                   (7U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_WRITE_SEQUENCE_ERR_FOUND_MASK                                    (0x00000080U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_SHIFT                                (8U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_MASK                                 (0x00000100U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_VBUF_READ_START_ERR_FOUND_SHIFT                                  (9U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_VBUF_READ_START_ERR_FOUND_MASK                                   (0x00000200U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_READ_SEQUENCE_ERR_FOUND_SHIFT                                    (10U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_READ_SEQUENCE_ERR_FOUND_MASK                                     (0x00000400U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_OVERFLOW_WRAP_ERR_FOUND_SHIFT                                    (12U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_CBUF_OVERFLOW_WRAP_ERR_FOUND_MASK                                     (0x00001000U)

#define OCMC_RAM_INTR0_ENABLE_CLEAR_RESERVED_SHIFT                                                        (15U)
#define OCMC_RAM_INTR0_ENABLE_CLEAR_RESERVED_MASK                                                         (0xffff8000U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_SEC_ERR_FOUND_SHIFT                                                 (0U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_SEC_ERR_FOUND_MASK                                                  (0x00000001U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_DED_ERR_FOUND_SHIFT                                                 (1U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_DED_ERR_FOUND_MASK                                                  (0x00000002U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_ADDR_ERR_FOUND_SHIFT                                                (2U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_ADDR_ERR_FOUND_MASK                                                 (0x00000004U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_OUT_OF_RANGE_ERR_FOUND_SHIFT                                        (3U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_OUT_OF_RANGE_ERR_FOUND_MASK                                         (0x00000008U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_VIRTUAL_ADDR_ERR_FOUND_SHIFT                                   (4U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_VIRTUAL_ADDR_ERR_FOUND_MASK                                    (0x00000010U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_OVERFLOW_MID_ERR_FOUND_SHIFT                                   (11U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_OVERFLOW_MID_ERR_FOUND_MASK                                    (0x00000800U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_UNDERFLOW_ERR_FOUND_SHIFT                                      (13U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_UNDERFLOW_ERR_FOUND_MASK                                       (0x00002000U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_SHORT_FRAME_DETECT_FOUND_SHIFT                                 (14U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_SHORT_FRAME_DETECT_FOUND_MASK                                  (0x00004000U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_SHIFT                                (5U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_MASK                                 (0x00000020U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_VBUF_WRITE_START_ERR_FOUND_SHIFT                               (6U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_VBUF_WRITE_START_ERR_FOUND_MASK                                (0x00000040U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_WRITE_SEQUENCE_ERR_FOUND_SHIFT                                 (7U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_WRITE_SEQUENCE_ERR_FOUND_MASK                                  (0x00000080U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_SHIFT                              (8U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_MASK                               (0x00000100U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_VBUF_READ_START_ERR_FOUND_SHIFT                                (9U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_VBUF_READ_START_ERR_FOUND_MASK                                 (0x00000200U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_READ_SEQUENCE_ERR_FOUND_SHIFT                                  (10U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_READ_SEQUENCE_ERR_FOUND_MASK                                   (0x00000400U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_OVERFLOW_WRAP_ERR_FOUND_SHIFT                                  (12U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_CBUF_OVERFLOW_WRAP_ERR_FOUND_MASK                                   (0x00001000U)

#define OCMC_RAM_INTR1_STATUS_RAW_SET_RESERVED_SHIFT                                                      (15U)
#define OCMC_RAM_INTR1_STATUS_RAW_SET_RESERVED_MASK                                                       (0xffff8000U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_SEC_ERR_FOUND_SHIFT                                           (0U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_SEC_ERR_FOUND_MASK                                            (0x00000001U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_DED_ERR_FOUND_SHIFT                                           (1U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_DED_ERR_FOUND_MASK                                            (0x00000002U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_ADDR_ERR_FOUND_SHIFT                                          (2U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_ADDR_ERR_FOUND_MASK                                           (0x00000004U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_OUT_OF_RANGE_ERR_FOUND_SHIFT                                  (3U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_OUT_OF_RANGE_ERR_FOUND_MASK                                   (0x00000008U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_VIRTUAL_ADDR_ERR_FOUND_SHIFT                             (4U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_VIRTUAL_ADDR_ERR_FOUND_MASK                              (0x00000010U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_OVERFLOW_MID_ERR_FOUND_SHIFT                             (11U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_OVERFLOW_MID_ERR_FOUND_MASK                              (0x00000800U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_UNDERFLOW_ERR_FOUND_SHIFT                                (13U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_UNDERFLOW_ERR_FOUND_MASK                                 (0x00002000U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_SHORT_FRAME_DETECT_FOUND_SHIFT                           (14U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_SHORT_FRAME_DETECT_FOUND_MASK                            (0x00004000U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_SHIFT                          (5U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_MASK                           (0x00000020U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_VBUF_WRITE_START_ERR_FOUND_SHIFT                         (6U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_VBUF_WRITE_START_ERR_FOUND_MASK                          (0x00000040U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_WRITE_SEQUENCE_ERR_FOUND_SHIFT                           (7U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_WRITE_SEQUENCE_ERR_FOUND_MASK                            (0x00000080U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_SHIFT                        (8U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_MASK                         (0x00000100U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_VBUF_READ_START_ERR_FOUND_SHIFT                          (9U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_VBUF_READ_START_ERR_FOUND_MASK                           (0x00000200U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_READ_SEQUENCE_ERR_FOUND_SHIFT                            (10U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_READ_SEQUENCE_ERR_FOUND_MASK                             (0x00000400U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_OVERFLOW_WRAP_ERR_FOUND_SHIFT                            (12U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_CBUF_OVERFLOW_WRAP_ERR_FOUND_MASK                             (0x00001000U)

#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_RESERVED_SHIFT                                                (15U)
#define OCMC_RAM_INTR1_STATUS_ENABLED_CLEAR_RESERVED_MASK                                                 (0xffff8000U)

#define OCMC_RAM_INTR1_ENABLE_SET_SEC_ERR_FOUND_SHIFT                                                     (0U)
#define OCMC_RAM_INTR1_ENABLE_SET_SEC_ERR_FOUND_MASK                                                      (0x00000001U)

#define OCMC_RAM_INTR1_ENABLE_SET_DED_ERR_FOUND_SHIFT                                                     (1U)
#define OCMC_RAM_INTR1_ENABLE_SET_DED_ERR_FOUND_MASK                                                      (0x00000002U)

#define OCMC_RAM_INTR1_ENABLE_SET_ADDR_ERR_FOUND_SHIFT                                                    (2U)
#define OCMC_RAM_INTR1_ENABLE_SET_ADDR_ERR_FOUND_MASK                                                     (0x00000004U)

#define OCMC_RAM_INTR1_ENABLE_SET_OUT_OF_RANGE_ERR_FOUND_SHIFT                                            (3U)
#define OCMC_RAM_INTR1_ENABLE_SET_OUT_OF_RANGE_ERR_FOUND_MASK                                             (0x00000008U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_VIRTUAL_ADDR_ERR_FOUND_SHIFT                                       (4U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_VIRTUAL_ADDR_ERR_FOUND_MASK                                        (0x00000010U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_OVERFLOW_MID_ERR_FOUND_SHIFT                                       (11U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_OVERFLOW_MID_ERR_FOUND_MASK                                        (0x00000800U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_UNDERFLOW_ERR_FOUND_SHIFT                                          (13U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_UNDERFLOW_ERR_FOUND_MASK                                           (0x00002000U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_SHORT_FRAME_DETECT_FOUND_SHIFT                                     (14U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_SHORT_FRAME_DETECT_FOUND_MASK                                      (0x00004000U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_SHIFT                                    (5U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_MASK                                     (0x00000020U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_VBUF_WRITE_START_ERR_FOUND_SHIFT                                   (6U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_VBUF_WRITE_START_ERR_FOUND_MASK                                    (0x00000040U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_WRITE_SEQUENCE_ERR_FOUND_SHIFT                                     (7U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_WRITE_SEQUENCE_ERR_FOUND_MASK                                      (0x00000080U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_SHIFT                                  (8U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_MASK                                   (0x00000100U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_VBUF_READ_START_ERR_FOUND_SHIFT                                    (9U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_VBUF_READ_START_ERR_FOUND_MASK                                     (0x00000200U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_READ_SEQUENCE_ERR_FOUND_SHIFT                                      (10U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_READ_SEQUENCE_ERR_FOUND_MASK                                       (0x00000400U)

#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_OVERFLOW_WRAP_ERR_FOUND_SHIFT                                      (12U)
#define OCMC_RAM_INTR1_ENABLE_SET_CBUF_OVERFLOW_WRAP_ERR_FOUND_MASK                                       (0x00001000U)

#define OCMC_RAM_INTR1_ENABLE_SET_RESERVED_SHIFT                                                          (15U)
#define OCMC_RAM_INTR1_ENABLE_SET_RESERVED_MASK                                                           (0xffff8000U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_SEC_ERR_FOUND_SHIFT                                                   (0U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_SEC_ERR_FOUND_MASK                                                    (0x00000001U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_DED_ERR_FOUND_SHIFT                                                   (1U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_DED_ERR_FOUND_MASK                                                    (0x00000002U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_ADDR_ERR_FOUND_SHIFT                                                  (2U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_ADDR_ERR_FOUND_MASK                                                   (0x00000004U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_OUT_OF_RANGE_ERR_FOUND_SHIFT                                          (3U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_OUT_OF_RANGE_ERR_FOUND_MASK                                           (0x00000008U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_VIRTUAL_ADDR_ERR_FOUND_SHIFT                                     (4U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_VIRTUAL_ADDR_ERR_FOUND_MASK                                      (0x00000010U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_OVERFLOW_MID_ERR_FOUND_SHIFT                                     (11U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_OVERFLOW_MID_ERR_FOUND_MASK                                      (0x00000800U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_UNDERFLOW_ERR_FOUND_SHIFT                                        (13U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_UNDERFLOW_ERR_FOUND_MASK                                         (0x00002000U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_SHORT_FRAME_DETECT_FOUND_SHIFT                                   (14U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_SHORT_FRAME_DETECT_FOUND_MASK                                    (0x00004000U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_SHIFT                                  (5U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_WR_OUT_OF_RANGE_ERR_FOUND_MASK                                   (0x00000020U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_VBUF_WRITE_START_ERR_FOUND_SHIFT                                 (6U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_VBUF_WRITE_START_ERR_FOUND_MASK                                  (0x00000040U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_WRITE_SEQUENCE_ERR_FOUND_SHIFT                                   (7U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_WRITE_SEQUENCE_ERR_FOUND_MASK                                    (0x00000080U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_SHIFT                                (8U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_READ_OUT_OF_RANGE_ERR_FOUND_MASK                                 (0x00000100U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_VBUF_READ_START_ERR_FOUND_SHIFT                                  (9U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_VBUF_READ_START_ERR_FOUND_MASK                                   (0x00000200U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_READ_SEQUENCE_ERR_FOUND_SHIFT                                    (10U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_READ_SEQUENCE_ERR_FOUND_MASK                                     (0x00000400U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_OVERFLOW_WRAP_ERR_FOUND_SHIFT                                    (12U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_CBUF_OVERFLOW_WRAP_ERR_FOUND_MASK                                     (0x00001000U)

#define OCMC_RAM_INTR1_ENABLE_CLEAR_RESERVED_SHIFT                                                        (15U)
#define OCMC_RAM_INTR1_ENABLE_CLEAR_RESERVED_MASK                                                         (0xffff8000U)

#define OCMC_RAM_STATUS_ERROR_CNT_SEC_ERROR_CNT_SHIFT                                                     (0U)
#define OCMC_RAM_STATUS_ERROR_CNT_SEC_ERROR_CNT_MASK                                                      (0x0000ffffU)

#define OCMC_RAM_STATUS_ERROR_CNT_DED_ERROR_CNT_SHIFT                                                     (16U)
#define OCMC_RAM_STATUS_ERROR_CNT_DED_ERROR_CNT_MASK                                                      (0x000f0000U)

#define OCMC_RAM_STATUS_ERROR_CNT_ADDR_ERROR_CNT_SHIFT                                                    (20U)
#define OCMC_RAM_STATUS_ERROR_CNT_ADDR_ERROR_CNT_MASK                                                     (0x00f00000U)

#define OCMC_RAM_STATUS_ERROR_CNT_RESERVED_SHIFT                                                          (24U)
#define OCMC_RAM_STATUS_ERROR_CNT_RESERVED_MASK                                                           (0xff000000U)

#define OCMC_RAM_STATUS_SEC_ERROR_TRACE_ADDRESS_128BIT_SHIFT                                              (0U)
#define OCMC_RAM_STATUS_SEC_ERROR_TRACE_ADDRESS_128BIT_MASK                                               (0x0003ffffU)

#define OCMC_RAM_STATUS_SEC_ERROR_TRACE_VALID_SHIFT                                                       (18U)
#define OCMC_RAM_STATUS_SEC_ERROR_TRACE_VALID_MASK                                                        (0x00040000U)
#define OCMC_RAM_STATUS_SEC_ERROR_TRACE_VALID_VALID_ADDRESS_READ                                          (1U)
#define OCMC_RAM_STATUS_SEC_ERROR_TRACE_VALID_ADDRESS_TRACE_FIFO_EMPTY                                    (0U)

#define OCMC_RAM_STATUS_SEC_ERROR_TRACE_RESERVED_SHIFT                                                    (19U)
#define OCMC_RAM_STATUS_SEC_ERROR_TRACE_RESERVED_MASK                                                     (0xfff80000U)

#define OCMC_RAM_STATUS_DED_ERROR_TRACE_ADDRESS_128BIT_SHIFT                                              (0U)
#define OCMC_RAM_STATUS_DED_ERROR_TRACE_ADDRESS_128BIT_MASK                                               (0x0003ffffU)

#define OCMC_RAM_STATUS_DED_ERROR_TRACE_VALID_SHIFT                                                       (18U)
#define OCMC_RAM_STATUS_DED_ERROR_TRACE_VALID_MASK                                                        (0x00040000U)

#define OCMC_RAM_STATUS_DED_ERROR_TRACE_RESERVED_SHIFT                                                    (19U)
#define OCMC_RAM_STATUS_DED_ERROR_TRACE_RESERVED_MASK                                                     (0xfff80000U)

#define OCMC_RAM_STATUS_ADDR_TRANSLATION_ERROR_TRACE_ADDRESS_128BIT_SHIFT                                 (0U)
#define OCMC_RAM_STATUS_ADDR_TRANSLATION_ERROR_TRACE_ADDRESS_128BIT_MASK                                  (0x0003ffffU)

#define OCMC_RAM_STATUS_ADDR_TRANSLATION_ERROR_TRACE_VALID_SHIFT                                          (18U)
#define OCMC_RAM_STATUS_ADDR_TRANSLATION_ERROR_TRACE_VALID_MASK                                           (0x00040000U)

#define OCMC_RAM_STATUS_ADDR_TRANSLATION_ERROR_TRACE_RESERVED_SHIFT                                       (19U)
#define OCMC_RAM_STATUS_ADDR_TRANSLATION_ERROR_TRACE_RESERVED_MASK                                        (0xfff80000U)

#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_0_SEC_BIT_ERROR_FOUND_SHIFT                                       (0U)
#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_0_SEC_BIT_ERROR_FOUND_MASK                                        (0xffffffffU)

#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_1_SEC_BIT_ERROR_FOUND_SHIFT                                       (0U)
#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_1_SEC_BIT_ERROR_FOUND_MASK                                        (0xffffffffU)

#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_2_SEC_BIT_ERROR_FOUND_SHIFT                                       (0U)
#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_2_SEC_BIT_ERROR_FOUND_MASK                                        (0xffffffffU)

#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_3_SEC_BIT_ERROR_FOUND_SHIFT                                       (0U)
#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_3_SEC_BIT_ERROR_FOUND_MASK                                        (0xffffffffU)

#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_4_SEC_ECC_CODE_ERROR_FOUND_SHIFT                                  (0U)
#define OCMC_RAM_STATUS_SEC_ERROR_DISTR_4_SEC_ECC_CODE_ERROR_FOUND_MASK                                   (0x000000ffU)

#define OCMC_RAM_CFG_OCMC_ECC_CFG_OCMC_MODE_SHIFT                                                         (0U)
#define OCMC_RAM_CFG_OCMC_ECC_CFG_OCMC_MODE_MASK                                                          (0x00000007U)
#define OCMC_RAM_CFG_OCMC_ECC_CFG_OCMC_MODE_NON_ECC_DATA                                                  (0U)
#define OCMC_RAM_CFG_OCMC_ECC_CFG_OCMC_MODE_NON_ECC_CODE                                                  (1U)
#define OCMC_RAM_CFG_OCMC_ECC_CFG_OCMC_MODE_FULL_ECC                                                      (2U)
#define OCMC_RAM_CFG_OCMC_ECC_CFG_OCMC_MODE_BLOCK_ECC                                                     (3U)

#define OCMC_RAM_CFG_OCMC_ECC_CFG_ECC_SEC_AUTO_CORRECT_SHIFT                                              (3U)
#define OCMC_RAM_CFG_OCMC_ECC_CFG_ECC_SEC_AUTO_CORRECT_MASK                                               (0x00000008U)

#define OCMC_RAM_CFG_OCMC_ECC_CFG_ECC_ERR_SRESP_EN_SHIFT                                                  (4U)
#define OCMC_RAM_CFG_OCMC_ECC_CFG_ECC_ERR_SRESP_EN_MASK                                                   (0x00000010U)

#define OCMC_RAM_CFG_OCMC_ECC_CFG_ECC_OPT_NON_ECC_READ_SHIFT                                              (5U)
#define OCMC_RAM_CFG_OCMC_ECC_CFG_ECC_OPT_NON_ECC_READ_MASK                                               (0x00000020U)

#define OCMC_RAM_CFG_OCMC_ECC_RESERVED_SHIFT                                                              (6U)
#define OCMC_RAM_CFG_OCMC_ECC_RESERVED_MASK                                                               (0xffffffc0U)

#define OCMC_RAM_CFG_OCMC_ECC_MEM_BLK_CFG_ECC_ENABLED_128K_BLK_SHIFT                                      (0U)
#define OCMC_RAM_CFG_OCMC_ECC_MEM_BLK_CFG_ECC_ENABLED_128K_BLK_MASK                                       (0x000fffffU)

#define OCMC_RAM_CFG_OCMC_ECC_MEM_BLK_RESERVED_SHIFT                                                      (20U)
#define OCMC_RAM_CFG_OCMC_ECC_MEM_BLK_RESERVED_MASK                                                       (0xfff00000U)

#define OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_SEC_CNT_MAX_SHIFT                                                 (0U)
#define OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_SEC_CNT_MAX_MASK                                                  (0x0000ffffU)

#define OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_DED_CNT_MAX_SHIFT                                                 (16U)
#define OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_DED_CNT_MAX_MASK                                                  (0x000f0000U)

#define OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_ADDR_ERR_CNT_MAX_SHIFT                                            (20U)
#define OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_ADDR_ERR_CNT_MAX_MASK                                             (0x00f00000U)

#define OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_DISCARD_DUP_ADDR_SHIFT                                            (24U)
#define OCMC_RAM_CFG_OCMC_ECC_ERROR_CFG_DISCARD_DUP_ADDR_MASK                                             (0x01000000U)

#define OCMC_RAM_CFG_OCMC_ECC_ERROR_RESERVED_SHIFT                                                        (25U)
#define OCMC_RAM_CFG_OCMC_ECC_ERROR_RESERVED_MASK                                                         (0xfe000000U)

#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_SEC_ERR_CNT_SHIFT                                          (0U)
#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_SEC_ERR_CNT_MASK                                           (0x00000001U)

#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_DED_ERR_CNT_SHIFT                                          (1U)
#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_DED_ERR_CNT_MASK                                           (0x00000002U)

#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_ADDR_ERR_CNT_SHIFT                                         (2U)
#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_ADDR_ERR_CNT_MASK                                          (0x00000004U)

#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_SEC_BIT_DISTR_SHIFT                                        (3U)
#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_CLEAR_SEC_BIT_DISTR_MASK                                         (0x00000008U)

#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_RESERVED_SHIFT                                                   (4U)
#define OCMC_RAM_CFG_OCMC_ECC_CLEAR_HIST_RESERVED_MASK                                                    (0xfffffff0U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_MODE_EN_SHIFT                                                      (0U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_MODE_EN_MASK                                                       (0x00000001U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_DEBUG_EN_SHIFT                                                     (1U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_DEBUG_EN_MASK                                                      (0x00000002U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_0_SHIFT                                                         (16U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_0_MASK                                                          (0x00010000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_1_SHIFT                                                         (17U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_1_MASK                                                          (0x00020000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_2_SHIFT                                                         (18U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_2_MASK                                                          (0x00040000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_3_SHIFT                                                         (19U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_3_MASK                                                          (0x00080000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_4_SHIFT                                                         (20U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_4_MASK                                                          (0x00100000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_5_SHIFT                                                         (21U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_5_MASK                                                          (0x00200000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_6_SHIFT                                                         (22U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_6_MASK                                                          (0x00400000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_7_SHIFT                                                         (23U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_7_MASK                                                          (0x00800000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_8_SHIFT                                                         (24U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_8_MASK                                                          (0x01000000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_9_SHIFT                                                         (25U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_9_MASK                                                          (0x02000000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_10_SHIFT                                                        (26U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_10_MASK                                                         (0x04000000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_11_SHIFT                                                        (27U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_CBUF_EN_11_MASK                                                         (0x08000000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_RSVD_SHIFT                                                              (28U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_RSVD_MASK                                                               (0xf0000000U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_NEW_FRAME_SEL_SHIFT                                                     (2U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_NEW_FRAME_SEL_MASK                                                      (0x00000004U)

#define OCMC_RAM_CFG_OCMC_CBUF_EN_RESERVED_SHIFT                                                          (3U)
#define OCMC_RAM_CFG_OCMC_CBUF_EN_RESERVED_MASK                                                           (0x0000fff8U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_0_SHIFT                                                   (0U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_0_MASK                                                    (0x00000001U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_1_SHIFT                                                   (1U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_1_MASK                                                    (0x00000002U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_2_SHIFT                                                   (2U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_2_MASK                                                    (0x00000004U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_3_SHIFT                                                   (3U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_3_MASK                                                    (0x00000008U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_4_SHIFT                                                   (4U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_4_MASK                                                    (0x00000010U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_5_SHIFT                                                   (5U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_5_MASK                                                    (0x00000020U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_6_SHIFT                                                   (6U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_6_MASK                                                    (0x00000040U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_7_SHIFT                                                   (7U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_7_MASK                                                    (0x00000080U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_8_SHIFT                                                   (8U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_8_MASK                                                    (0x00000100U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_9_SHIFT                                                   (9U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_9_MASK                                                    (0x00000200U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_10_SHIFT                                                  (10U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_10_MASK                                                   (0x00000400U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_11_SHIFT                                                  (11U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_CBUF_RESET_11_MASK                                                   (0x00000800U)

#define OCMC_RAM_CFG_OCMC_CBUF_RESET_RSVD_SHIFT                                                           (12U)
#define OCMC_RAM_CFG_OCMC_CBUF_RESET_RSVD_MASK                                                            (0xfffff000U)

#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_ERR_CHECK_EN_SHIFT                                    (2U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_ERR_CHECK_EN_MASK                                     (0x00000004U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_ERR_CHECK_EN_OVERFLOW_CHECK_ENABLE                    (0U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_ERR_CHECK_EN_OVERFLOW_CHECK_DISABLE                   (1U)

#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_UNDERFLOW_ERR_CHECK_EN_SHIFT                                   (3U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_UNDERFLOW_ERR_CHECK_EN_MASK                                    (0x00000008U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_UNDERFLOW_ERR_CHECK_EN_UNDERFLOW_CHECK_ENABLE                  (0U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_UNDERFLOW_ERR_CHECK_EN_UNDERFLOW_CHECK_DISABLE                 (1U)

#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_SHORT_FRAME_DETECT_CHECK_EN_SHIFT                              (0U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_SHORT_FRAME_DETECT_CHECK_EN_MASK                               (0x00000001U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_SHORT_FRAME_DETECT_CHECK_EN_SHORT_FRAME_DETECT_ENABLE          (0U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_SHORT_FRAME_DETECT_CHECK_EN_SHORT_FRAME_DETECT_DISABLE         (1U)

#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_WRITE_HANDLER_SEL_SHIFT                               (4U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_WRITE_HANDLER_SEL_MASK                                (0x00000030U)

#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_CHECK_REENABLE_SEL_SHIFT                              (6U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_OVERFLOW_CHECK_REENABLE_SEL_MASK                               (0x000000c0U)

#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_UNDERFLOW_LAST_CBUF_SLICE_DISABLE_SHIFT                        (8U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_UNDERFLOW_LAST_CBUF_SLICE_DISABLE_MASK                         (0x00000100U)

#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_SHORT_FRAME_PREV_EOF_SEL_SHIFT                                 (1U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_SHORT_FRAME_PREV_EOF_SEL_MASK                                  (0x00000002U)

#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_RESERVED_SHIFT                                                 (9U)
#define OCMC_RAM_CFG_OCMC_CBUF_ERR_HANDLER_RESERVED_MASK                                                  (0xfffffe00U)

#define OCMC_RAM_STATUS_CBUF_WR_OUT_OF_RANGE_ERR_CBUF_ERR_SHIFT                                           (0U)
#define OCMC_RAM_STATUS_CBUF_WR_OUT_OF_RANGE_ERR_CBUF_ERR_MASK                                            (0x00000fffU)

#define OCMC_RAM_STATUS_CBUF_WR_OUT_OF_RANGE_ERR_RESERVED_SHIFT                                           (12U)
#define OCMC_RAM_STATUS_CBUF_WR_OUT_OF_RANGE_ERR_RESERVED_MASK                                            (0xfffff000U)

#define OCMC_RAM_STATUS_CBUF_WR_VBUF_START_ERR_CBUF_ERR_SHIFT                                             (0U)
#define OCMC_RAM_STATUS_CBUF_WR_VBUF_START_ERR_CBUF_ERR_MASK                                              (0x00000fffU)

#define OCMC_RAM_STATUS_CBUF_WR_VBUF_START_ERR_RESERVED_SHIFT                                             (12U)
#define OCMC_RAM_STATUS_CBUF_WR_VBUF_START_ERR_RESERVED_MASK                                              (0xfffff000U)

#define OCMC_RAM_STATUS_CBUF_WR_ADDR_SEQ_ERROR_CBUF_ERR_SHIFT                                             (0U)
#define OCMC_RAM_STATUS_CBUF_WR_ADDR_SEQ_ERROR_CBUF_ERR_MASK                                              (0x00000fffU)

#define OCMC_RAM_STATUS_CBUF_WR_ADDR_SEQ_ERROR_RESERVED_SHIFT                                             (12U)
#define OCMC_RAM_STATUS_CBUF_WR_ADDR_SEQ_ERROR_RESERVED_MASK                                              (0xfffff000U)

#define OCMC_RAM_STATUS_CBUF_RD_OUT_OF_RANGE_ERROR_CBUF_ERR_SHIFT                                         (0U)
#define OCMC_RAM_STATUS_CBUF_RD_OUT_OF_RANGE_ERROR_CBUF_ERR_MASK                                          (0x00000fffU)

#define OCMC_RAM_STATUS_CBUF_RD_OUT_OF_RANGE_ERROR_RESERVED_SHIFT                                         (12U)
#define OCMC_RAM_STATUS_CBUF_RD_OUT_OF_RANGE_ERROR_RESERVED_MASK                                          (0xfffff000U)

#define OCMC_RAM_STATUS_CBUF_VBUF_RD_START_ERROR_CBUF_ERR_SHIFT                                           (0U)
#define OCMC_RAM_STATUS_CBUF_VBUF_RD_START_ERROR_CBUF_ERR_MASK                                            (0x00000fffU)

#define OCMC_RAM_STATUS_CBUF_VBUF_RD_START_ERROR_RESERVED_SHIFT                                           (12U)
#define OCMC_RAM_STATUS_CBUF_VBUF_RD_START_ERROR_RESERVED_MASK                                            (0xfffff000U)

#define OCMC_RAM_STATUS_CBUF_RD_ADDR_SEQ_ERROR_CBUF_ERR_SHIFT                                             (0U)
#define OCMC_RAM_STATUS_CBUF_RD_ADDR_SEQ_ERROR_CBUF_ERR_MASK                                              (0x00000fffU)

#define OCMC_RAM_STATUS_CBUF_RD_ADDR_SEQ_ERROR_RESERVED_SHIFT                                             (12U)
#define OCMC_RAM_STATUS_CBUF_RD_ADDR_SEQ_ERROR_RESERVED_MASK                                              (0xfffff000U)

#define OCMC_RAM_STATUS_CBUF_OVERFLOW_MID_CBUF_ERR_SHIFT                                                  (0U)
#define OCMC_RAM_STATUS_CBUF_OVERFLOW_MID_CBUF_ERR_MASK                                                   (0x00000fffU)

#define OCMC_RAM_STATUS_CBUF_OVERFLOW_MID_RESERVED_SHIFT                                                  (12U)
#define OCMC_RAM_STATUS_CBUF_OVERFLOW_MID_RESERVED_MASK                                                   (0xfffff000U)

#define OCMC_RAM_STATUS_CBUF_OVERFLOW_WRAP_CBUF_ERR_SHIFT                                                 (0U)
#define OCMC_RAM_STATUS_CBUF_OVERFLOW_WRAP_CBUF_ERR_MASK                                                  (0x00000fffU)

#define OCMC_RAM_STATUS_CBUF_OVERFLOW_WRAP_RESERVED_SHIFT                                                 (12U)
#define OCMC_RAM_STATUS_CBUF_OVERFLOW_WRAP_RESERVED_MASK                                                  (0xfffff000U)

#define OCMC_RAM_STATUS_CBUF_UNDERFLOW_CBUF_ERR_SHIFT                                                     (0U)
#define OCMC_RAM_STATUS_CBUF_UNDERFLOW_CBUF_ERR_MASK                                                      (0x00000fffU)

#define OCMC_RAM_STATUS_CBUF_UNDERFLOW_RESERVED_SHIFT                                                     (12U)
#define OCMC_RAM_STATUS_CBUF_UNDERFLOW_RESERVED_MASK                                                      (0xfffff000U)

#define OCMC_RAM_STATUS_CBUF_SHORT_FRAME_DETECT_CBUF_ERR_SHIFT                                            (0U)
#define OCMC_RAM_STATUS_CBUF_SHORT_FRAME_DETECT_CBUF_ERR_MASK                                             (0x00000fffU)

#define OCMC_RAM_STATUS_CBUF_SHORT_FRAME_DETECT_RESERVED_SHIFT                                            (12U)
#define OCMC_RAM_STATUS_CBUF_SHORT_FRAME_DETECT_RESERVED_MASK                                             (0xfffff000U)

#define OCMC_RAM_CBUF_VBUF_START_ADDR_ADDR_SHIFT                                                          (4U)
#define OCMC_RAM_CBUF_VBUF_START_ADDR_ADDR_MASK                                                           (0xfffffff0U)

#define OCMC_RAM_CBUF_VBUF_START_ADDR_RESERVED_SHIFT                                                      (0U)
#define OCMC_RAM_CBUF_VBUF_START_ADDR_RESERVED_MASK                                                       (0x0000000fU)

#define OCMC_RAM_CBUF_VBUF_END_ADDR_ADDR_SHIFT                                                            (4U)
#define OCMC_RAM_CBUF_VBUF_END_ADDR_ADDR_MASK                                                             (0xfffffff0U)

#define OCMC_RAM_CBUF_VBUF_END_ADDR_RESERVED_SHIFT                                                        (0U)
#define OCMC_RAM_CBUF_VBUF_END_ADDR_RESERVED_MASK                                                         (0x0000000fU)

#define OCMC_RAM_CBUF_OCMC_START_ADDR_ADDR_SHIFT                                                          (4U)
#define OCMC_RAM_CBUF_OCMC_START_ADDR_ADDR_MASK                                                           (0xfffffff0U)

#define OCMC_RAM_CBUF_OCMC_START_ADDR_RESERVED_SHIFT                                                      (0U)
#define OCMC_RAM_CBUF_OCMC_START_ADDR_RESERVED_MASK                                                       (0x0000000fU)

#define OCMC_RAM_CBUF_OCMC_BUF_SIZE_BUF_SIZE_SHIFT                                                        (4U)
#define OCMC_RAM_CBUF_OCMC_BUF_SIZE_BUF_SIZE_MASK                                                         (0x000ffff0U)

#define OCMC_RAM_CBUF_OCMC_BUF_SIZE_RESERVED_SHIFT                                                        (0U)
#define OCMC_RAM_CBUF_OCMC_BUF_SIZE_RESERVED_MASK                                                         (0x0000000fU)

#define OCMC_RAM_CBUF_OCMC_BUF_SIZE_RESERVED1_SHIFT                                                       (20U)
#define OCMC_RAM_CBUF_OCMC_BUF_SIZE_RESERVED1_MASK                                                        (0xfff00000U)

#define OCMC_RAM_CBUF_LAST_WR_ADDR_ADDR_SHIFT                                                             (0U)
#define OCMC_RAM_CBUF_LAST_WR_ADDR_ADDR_MASK                                                              (0xffffffffU)

#define OCMC_RAM_CBUF_LAST_RD_ADDR_ADDR_SHIFT                                                             (0U)
#define OCMC_RAM_CBUF_LAST_RD_ADDR_ADDR_MASK                                                              (0xffffffffU)

#define OCMC_RAM_LAST_ILLEGAL_OCMC_ADDR_ADDR_SHIFT                                                        (0U)
#define OCMC_RAM_LAST_ILLEGAL_OCMC_ADDR_ADDR_MASK                                                         (0xffffffffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_OCMC_RAM_H_ */
