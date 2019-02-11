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
 * \file  hw_pciectrl_rc_dbics2.h
 *
 * \brief Register-level header file for PCIECTRL_RC_DBICS2 [default]
 *
**/

#ifndef HW_PCIECTRL_RC_DBICS2_H_
#define HW_PCIECTRL_RC_DBICS2_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Component offset
****************************************************************************************************/
#define PCIECTRL_RC_DBICS2_OFFSET                                   (0x1000U)


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define PCIECTRL_RC_DBICS2_DEVICE_VENDORID                          (0x0U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER                  (0x4U)
#define PCIECTRL_RC_DBICS2_CLASSCODE_REVISIONID                     (0x8U)
#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH                       (0xcU)
#define PCIECTRL_RC_DBICS2_BAR0_MASK                                (0x10U)
#define PCIECTRL_RC_DBICS2_BAR1_MASK                                (0x14U)
#define PCIECTRL_RC_DBICS2_BUS_NUM_REG                              (0x18U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS                  (0x1cU)
#define PCIECTRL_RC_DBICS2_MEM_BASE_LIMIT                           (0x20U)
#define PCIECTRL_RC_DBICS2_PREF_MEM_BASE_LIMIT                      (0x24U)
#define PCIECTRL_RC_DBICS2_UPPER_32BIT_PREF_BASEADDR                (0x28U)
#define PCIECTRL_RC_DBICS2_UPPER_32BIT_PREF_LIMITADDR               (0x2cU)
#define PCIECTRL_RC_DBICS2_IO_BASE_LIMIT                            (0x30U)
#define PCIECTRL_RC_DBICS2_CAPPTR                                   (0x34U)
#define PCIECTRL_RC_DBICS2_EXPANSION_ROM_BAR                        (0x38U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT                               (0x3cU)
#define PCIECTRL_RC_DBICS2_PCIE_CAP                                 (0x70U)
#define PCIECTRL_RC_DBICS2_DEV_CAP                                  (0x74U)
#define PCIECTRL_RC_DBICS2_DEV_CAS                                  (0x78U)
#define PCIECTRL_RC_DBICS2_LNK_CAP                                  (0x7cU)
#define PCIECTRL_RC_DBICS2_LNK_CAS                                  (0x80U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP                                 (0x84U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS                                 (0x88U)
#define PCIECTRL_RC_DBICS2_ROOT_CAC                                 (0x8cU)
#define PCIECTRL_RC_DBICS2_ROOT_STS                                 (0x90U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_2                                (0x94U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_2                                (0x98U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_2                                (0x9cU)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2                                (0xA0U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define PCIECTRL_RC_DBICS2_DEVICE_VENDORID_SHIFT                                        (0U)
#define PCIECTRL_RC_DBICS2_DEVICE_VENDORID_MASK                                         (0x0000ffffU)

#define PCIECTRL_RC_DBICS2_DEVICE_VENDORID_DEVICEID_SHIFT                               (16U)
#define PCIECTRL_RC_DBICS2_DEVICE_VENDORID_DEVICEID_MASK                                (0xffff0000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_IO_SPACE_EN_SHIFT                    (0U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_IO_SPACE_EN_MASK                     (0x00000001U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_MEM_SPACE_EN_SHIFT                   (1U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_MEM_SPACE_EN_MASK                    (0x00000002U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_BUSMASTER_EN_SHIFT                   (2U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_BUSMASTER_EN_MASK                    (0x00000004U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_SPEC_CYCLE_EN_SHIFT                  (3U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_SPEC_CYCLE_EN_MASK                   (0x00000008U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_MEMWR_INVA_SHIFT                     (4U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_MEMWR_INVA_MASK                      (0x00000010U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_VGA_SNOOP_SHIFT                      (5U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_VGA_SNOOP_MASK                       (0x00000020U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_PARITYERRRESP_SHIFT                  (6U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_PARITYERRRESP_MASK                   (0x00000040U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_IDSEL_CTRL_SHIFT                     (7U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_IDSEL_CTRL_MASK                      (0x00000080U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_SERR_EN_SHIFT                        (8U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_SERR_EN_MASK                         (0x00000100U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_FAST_BBEN_SHIFT                      (9U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_FAST_BBEN_MASK                       (0x00000200U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_INTX_ASSER_DIS_SHIFT                 (10U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_INTX_ASSER_DIS_MASK                  (0x00000400U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_INTX_SHIFT                           (19U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_INTX_MASK                            (0x00080000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_CAP_LIST_SHIFT                       (20U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_CAP_LIST_MASK                        (0x00100000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_C66MHZ_CAP_SHIFT                     (21U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_C66MHZ_CAP_MASK                      (0x00200000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_RESERV3_SHIFT                        (22U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_RESERV3_MASK                         (0x00400000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_FAST_B2B_SHIFT                       (23U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_FAST_B2B_MASK                        (0x00800000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_MASTERDATA_PARERR_SHIFT              (24U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_MASTERDATA_PARERR_MASK               (0x01000000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_DEVSEL_TIME_SHIFT                    (25U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_DEVSEL_TIME_MASK                     (0x06000000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_SIGNAL_TRGTABORT_SHIFT               (27U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_SIGNAL_TRGTABORT_MASK                (0x08000000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_RCVD_TRGTABORT_SHIFT                 (28U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_RCVD_TRGTABORT_MASK                  (0x10000000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_RCVD_MASTERABORT_SHIFT               (29U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_RCVD_MASTERABORT_MASK                (0x20000000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_SIGNAL_SYSERR_SHIFT                  (30U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_SIGNAL_SYSERR_MASK                   (0x40000000U)

#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_DETECT_PARERR_SHIFT                  (31U)
#define PCIECTRL_RC_DBICS2_STATUS_COMMAND_REGISTER_DETECT_PARERR_MASK                   (0x80000000U)

#define PCIECTRL_RC_DBICS2_CLASSCODE_REVISIONID_REVID_SHIFT                             (0U)
#define PCIECTRL_RC_DBICS2_CLASSCODE_REVISIONID_REVID_MASK                              (0x000000ffU)

#define PCIECTRL_RC_DBICS2_CLASSCODE_REVISIONID_PROG_IF_CODE_SHIFT                      (8U)
#define PCIECTRL_RC_DBICS2_CLASSCODE_REVISIONID_PROG_IF_CODE_MASK                       (0x0000ff00U)

#define PCIECTRL_RC_DBICS2_CLASSCODE_REVISIONID_SUBCLS_CD_SHIFT                         (16U)
#define PCIECTRL_RC_DBICS2_CLASSCODE_REVISIONID_SUBCLS_CD_MASK                          (0x00ff0000U)

#define PCIECTRL_RC_DBICS2_CLASSCODE_REVISIONID_BASE_CLS_CD_SHIFT                       (24U)
#define PCIECTRL_RC_DBICS2_CLASSCODE_REVISIONID_BASE_CLS_CD_MASK                        (0xff000000U)

#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_LN_SZE_SHIFT                              (0U)
#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_LN_SZE_MASK                               (0x000000ffU)

#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_MSTR_TIM_SHIFT                            (8U)
#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_MSTR_TIM_MASK                             (0x0000ff00U)

#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_TYP_SHIFT                                 (16U)
#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_TYP_MASK                                  (0x007f0000U)
#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_TYP_TYPE0                                  (0U)
#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_TYP_TYPE1                                  (1U)

#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_MFD_SHIFT                                 (23U)
#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_MFD_MASK                                  (0x00800000U)

#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_SHIFT                                     (24U)
#define PCIECTRL_RC_DBICS2_BIST_HEAD_LAT_CACH_MASK                                      (0xff000000U)

#define PCIECTRL_RC_DBICS2_BAR0_MASK_BAR_MASK_SHIFT                                     (1U)
#define PCIECTRL_RC_DBICS2_BAR0_MASK_BAR_MASK_MASK                                      (0xFFFFFFFEU)

#define PCIECTRL_RC_DBICS2_BAR0_MASK_BAR_ENBALE_SHIFT                                   (0U)
#define PCIECTRL_RC_DBICS2_BAR0_MASK_BAR_ENBALE_MASK                                    (0x00000001U)

#define PCIECTRL_RC_DBICS2_BAR0_MASK_UPPER_BAR_MASK_SHIFT                               (0U)
#define PCIECTRL_RC_DBICS2_BAR0_MASK_UPPER_BAR_MASK_MASK                                (0xFFFFFFFFU)

#define PCIECTRL_RC_DBICS2_BAR1_MASK_BAR_MASK_SHIFT                                     (1U)
#define PCIECTRL_RC_DBICS2_BAR1_MASK_BAR_MASK_MASK                                      (0xFFFFFFFEU)

#define PCIECTRL_RC_DBICS2_BAR1_MASK_BAR_ENBALE_SHIFT                                   (0U)
#define PCIECTRL_RC_DBICS2_BAR1_MASK_BAR_ENBALE_MASK                                    (0x00000001U)

#define PCIECTRL_RC_DBICS2_BUS_NUM_REG_PRIM_SHIFT                                       (0U)
#define PCIECTRL_RC_DBICS2_BUS_NUM_REG_PRIM_MASK                                        (0x000000ffU)

#define PCIECTRL_RC_DBICS2_BUS_NUM_REG_SEC_SHIFT                                        (8U)
#define PCIECTRL_RC_DBICS2_BUS_NUM_REG_SEC_MASK                                         (0x0000ff00U)

#define PCIECTRL_RC_DBICS2_BUS_NUM_REG_SUBORD_SHIFT                                     (16U)
#define PCIECTRL_RC_DBICS2_BUS_NUM_REG_SUBORD_MASK                                      (0x00ff0000U)

#define PCIECTRL_RC_DBICS2_BUS_NUM_REG_SEC_LAT_TIMER_SHIFT                              (24U)
#define PCIECTRL_RC_DBICS2_BUS_NUM_REG_SEC_LAT_TIMER_MASK                               (0xff000000U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_IODECODE_32_0_SHIFT                  (0U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_IODECODE_32_0_MASK                   (0x00000001U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_IO_SPACE_BASE_SHIFT                  (4U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_IO_SPACE_BASE_MASK                   (0x000000f0U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_IODECODE_32_SHIFT                    (8U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_IODECODE_32_MASK                     (0x00000100U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_IO_SPACE_SHIFT                       (12U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_IO_SPACE_MASK                        (0x0000f000U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_C66MHZ_CAPA_SHIFT                    (21U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_C66MHZ_CAPA_MASK                     (0x00200000U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_FAST_B2B_CAP_SHIFT                   (23U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_FAST_B2B_CAP_MASK                    (0x00800000U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_MSTR_DATA_PRTY_ERR_SHIFT             (24U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_MSTR_DATA_PRTY_ERR_MASK              (0x01000000U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_DEVSEL_TIMING_SHIFT                  (25U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_DEVSEL_TIMING_MASK                   (0x06000000U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_SGNLD_TRGT_ABORT_SHIFT               (27U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_SGNLD_TRGT_ABORT_MASK                (0x08000000U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_RCVD_TRGT_ABORT_SHIFT                (28U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_RCVD_TRGT_ABORT_MASK                 (0x10000000U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_RCVD_MSTR_ABORT_SHIFT                (29U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_RCVD_MSTR_ABORT_MASK                 (0x20000000U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_RCVD_SYS_ERR_SHIFT                   (30U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_RCVD_SYS_ERR_MASK                    (0x40000000U)

#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_DET_PAR_ERR_SHIFT                    (31U)
#define PCIECTRL_RC_DBICS2_IOBASE_LIMIT_SEC_STATUS_DET_PAR_ERR_MASK                     (0x80000000U)

#define PCIECTRL_RC_DBICS2_MEM_BASE_LIMIT_BASE_ADDR_SHIFT                               (4U)
#define PCIECTRL_RC_DBICS2_MEM_BASE_LIMIT_BASE_ADDR_MASK                                (0x0000fff0U)

#define PCIECTRL_RC_DBICS2_MEM_BASE_LIMIT_LIMIT_ADDR_SHIFT                              (20U)
#define PCIECTRL_RC_DBICS2_MEM_BASE_LIMIT_LIMIT_ADDR_MASK                               (0xfff00000U)

#define PCIECTRL_RC_DBICS2_PREF_MEM_BASE_LIMIT_MEMDECODE_64_0_SHIFT                     (0U)
#define PCIECTRL_RC_DBICS2_PREF_MEM_BASE_LIMIT_MEMDECODE_64_0_MASK                      (0x00000001U)

#define PCIECTRL_RC_DBICS2_PREF_MEM_BASE_LIMIT_UPPPREF_ADDR_SHIFT                       (4U)
#define PCIECTRL_RC_DBICS2_PREF_MEM_BASE_LIMIT_UPPPREF_ADDR_MASK                        (0x0000fff0U)

#define PCIECTRL_RC_DBICS2_PREF_MEM_BASE_LIMIT_MEMDECODE_64_SHIFT                       (16U)
#define PCIECTRL_RC_DBICS2_PREF_MEM_BASE_LIMIT_MEMDECODE_64_MASK                        (0x00010000U)

#define PCIECTRL_RC_DBICS2_PREF_MEM_BASE_LIMIT_ADDR_SHIFT                               (20U)
#define PCIECTRL_RC_DBICS2_PREF_MEM_BASE_LIMIT_ADDR_MASK                                (0xfff00000U)

#define PCIECTRL_RC_DBICS2_UPPER_32BIT_PREF_BASEADDR_ADDRUPP_SHIFT                      (0U)
#define PCIECTRL_RC_DBICS2_UPPER_32BIT_PREF_BASEADDR_ADDRUPP_MASK                       (0xffffffffU)

#define PCIECTRL_RC_DBICS2_UPPER_32BIT_PREF_LIMITADDR_ADDRUPP_LIMIT_SHIFT               (0U)
#define PCIECTRL_RC_DBICS2_UPPER_32BIT_PREF_LIMITADDR_ADDRUPP_LIMIT_MASK                (0xffffffffU)

#define PCIECTRL_RC_DBICS2_IO_BASE_LIMIT_UPP16_IOBASE_SHIFT                             (0U)
#define PCIECTRL_RC_DBICS2_IO_BASE_LIMIT_UPP16_IOBASE_MASK                              (0x0000ffffU)

#define PCIECTRL_RC_DBICS2_IO_BASE_LIMIT_UPP16_IOLIMIT_SHIFT                            (16U)
#define PCIECTRL_RC_DBICS2_IO_BASE_LIMIT_UPP16_IOLIMIT_MASK                             (0xffff0000U)

#define PCIECTRL_RC_DBICS2_CAPPTR_CAPTR_SHIFT                                           (0U)
#define PCIECTRL_RC_DBICS2_CAPPTR_CAPTR_MASK                                            (0x000000ffU)

#define PCIECTRL_RC_DBICS2_EXPANSION_ROM_BAR_EXP_EN_SHIFT                               (0U)
#define PCIECTRL_RC_DBICS2_EXPANSION_ROM_BAR_EXP_EN_MASK                                (0x00000001U)

#define PCIECTRL_RC_DBICS2_EXPANSION_ROM_BAR_EXROM_ADDRESS_RO_SHIFT                     (11U)
#define PCIECTRL_RC_DBICS2_EXPANSION_ROM_BAR_EXROM_ADDRESS_RO_MASK                      (0x0000f800U)

#define PCIECTRL_RC_DBICS2_EXPANSION_ROM_BAR_EXROM_ADDRESS_SHIFT                        (16U)
#define PCIECTRL_RC_DBICS2_EXPANSION_ROM_BAR_EXROM_ADDRESS_MASK                         (0xffff0000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_LIN_SHIFT                                         (0U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_LIN_MASK                                          (0x000000ffU)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_PIN_SHIFT                                         (8U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_PIN_MASK                                          (0x0000ff00U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_PERR_RESP_EN_SHIFT                                (16U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_PERR_RESP_EN_MASK                                 (0x00010000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_SERR_EN_SHIFT                                     (17U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_SERR_EN_MASK                                      (0x00020000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_ISA_EN_SHIFT                                      (18U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_ISA_EN_MASK                                       (0x00040000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_VGA_EN_SHIFT                                      (19U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_VGA_EN_MASK                                       (0x00080000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_VGA_16B_DEC_SHIFT                                 (20U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_VGA_16B_DEC_MASK                                  (0x00100000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_MST_ABT_MOD_SHIFT                                 (21U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_MST_ABT_MOD_MASK                                  (0x00200000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_SEC_BUS_RST_SHIFT                                 (22U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_SEC_BUS_RST_MASK                                  (0x00400000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_FAST_B2B_EN_SHIFT                                 (23U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_FAST_B2B_EN_MASK                                  (0x00800000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_PRI_DT_SHIFT                                      (24U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_PRI_DT_MASK                                       (0x01000000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_SEC_DT_SHIFT                                      (25U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_SEC_DT_MASK                                       (0x02000000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_DT_STS_SHIFT                                      (26U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_DT_STS_MASK                                       (0x04000000U)

#define PCIECTRL_RC_DBICS2_BRIDGE_INT_DT_SERR_EN_SHIFT                                  (27U)
#define PCIECTRL_RC_DBICS2_BRIDGE_INT_DT_SERR_EN_MASK                                   (0x08000000U)

#define PCIECTRL_RC_DBICS2_PCIE_CAP_ID_SHIFT                                            (0U)
#define PCIECTRL_RC_DBICS2_PCIE_CAP_ID_MASK                                             (0x000000ffU)
#define PCIECTRL_RC_DBICS2_PCIE_CAP_ID                                                   (16U)

#define PCIECTRL_RC_DBICS2_PCIE_CAP_NX_PTR_SHIFT                                        (8U)
#define PCIECTRL_RC_DBICS2_PCIE_CAP_NX_PTR_MASK                                         (0x0000ff00U)

#define PCIECTRL_RC_DBICS2_PCIE_CAP_VER_SHIFT                                           (16U)
#define PCIECTRL_RC_DBICS2_PCIE_CAP_VER_MASK                                            (0x000f0000U)

#define PCIECTRL_RC_DBICS2_PCIE_CAP_DEV_TYPE_SHIFT                                      (20U)
#define PCIECTRL_RC_DBICS2_PCIE_CAP_DEV_TYPE_MASK                                       (0x00f00000U)
#define PCIECTRL_RC_DBICS2_PCIE_CAP_DEV_TYPE                                             (4U)

#define PCIECTRL_RC_DBICS2_PCIE_CAP_SLOT_SHIFT                                          (24U)
#define PCIECTRL_RC_DBICS2_PCIE_CAP_SLOT_MASK                                           (0x01000000U)

#define PCIECTRL_RC_DBICS2_PCIE_CAP_IM_NUM_SHIFT                                        (25U)
#define PCIECTRL_RC_DBICS2_PCIE_CAP_IM_NUM_MASK                                         (0x3e000000U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_MAX_PAYLOAD_SIZE_SHIFT                               (0U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_MAX_PAYLOAD_SIZE_MASK                                (0x00000007U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_MAX_PAYLOAD_SIZE_256_BYTE                             (1U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_PHANTOMFUNC_SHIFT                                    (3U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_PHANTOMFUNC_MASK                                     (0x00000018U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_EXTTAGFIELD_SUPPORT_SHIFT                            (5U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_EXTTAGFIELD_SUPPORT_MASK                             (0x00000020U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_DEFAULT_EP_L0S_ACCPT_LATENCY_SHIFT                   (6U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_DEFAULT_EP_L0S_ACCPT_LATENCY_MASK                    (0x000001c0U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_DEFAULT_EP_L1_ACCPT_LATENCY_SHIFT                    (9U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_DEFAULT_EP_L1_ACCPT_LATENCY_MASK                     (0x00000e00U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_UNDEFINED_SHIFT                                      (12U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_UNDEFINED_MASK                                       (0x00007000U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_ROLEBASED_ERRRPT_SHIFT                               (15U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_ROLEBASED_ERRRPT_MASK                                (0x00008000U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_CAPT_SLOW_PWRLIMIT_VALUE_SHIFT                       (18U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_CAPT_SLOW_PWRLIMIT_VALUE_MASK                        (0x03fc0000U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_CAPT_SLOW_PWRLIMIT_SCALE_SHIFT                       (26U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_CAPT_SLOW_PWRLIMIT_SCALE_MASK                        (0x0c000000U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_COR_RE_SHIFT                                         (0U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_COR_RE_MASK                                          (0x00000001U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_NFT_RE_SHIFT                                         (1U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_NFT_RE_MASK                                          (0x00000002U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_FT_RE_SHIFT                                          (2U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_FT_RE_MASK                                           (0x00000004U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_UR_RE_SHIFT                                          (3U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_UR_RE_MASK                                           (0x00000008U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_EN_RO_SHIFT                                          (4U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_EN_RO_MASK                                           (0x00000010U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_MPS_SHIFT                                            (5U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_MPS_MASK                                             (0x000000e0U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_EXTAG_EN_SHIFT                                       (8U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_EXTAG_EN_MASK                                        (0x00000100U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_PHFUN_EN_SHIFT                                       (9U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_PHFUN_EN_MASK                                        (0x00000200U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_AUXPM_EN_SHIFT                                       (10U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_AUXPM_EN_MASK                                        (0x00000400U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_AUXPM_EN_DIS                                          (0U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_AUXPM_EN                                              (1U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_NOSNP_EN_SHIFT                                       (11U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_NOSNP_EN_MASK                                        (0x00000800U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_MRRS_SHIFT                                           (12U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_MRRS_MASK                                            (0x00007000U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_INIT_FLR_SHIFT                                       (15U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_INIT_FLR_MASK                                        (0x00008000U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_COR_DET_SHIFT                                        (16U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_COR_DET_MASK                                         (0x00010000U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_NFT_DET_SHIFT                                        (17U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_NFT_DET_MASK                                         (0x00020000U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_FT_DET_SHIFT                                         (18U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_FT_DET_MASK                                          (0x00040000U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_UR_DET_SHIFT                                         (19U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_UR_DET_MASK                                          (0x00080000U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_AUXP_DET_SHIFT                                       (20U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_AUXP_DET_MASK                                        (0x00100000U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_TRANS_PEND_SHIFT                                     (21U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_TRANS_PEND_MASK                                      (0x00200000U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_MAX_LINK_SPEEDS_SHIFT                                (0U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_MAX_LINK_SPEEDS_MASK                                 (0x0000000fU)
#define PCIECTRL_RC_DBICS2_LNK_CAP_MAX_LINK_SPEEDS_GEN1                                  (1U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_MAX_LINK_SPEEDS_GEN2                                  (2U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_MAX_LINK_SPEEDS_GEN3                                  (3U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_MAX_LINK_WIDTH_SHIFT                                 (4U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_MAX_LINK_WIDTH_MASK                                  (0x000003f0U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_AS_LINK_PM_SUPPORT_SHIFT                             (10U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_AS_LINK_PM_SUPPORT_MASK                              (0x00000c00U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_COMM_L0S_EXIT_LAT_SHIFT                              (12U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_COMM_L0S_EXIT_LAT_MASK                               (0x00007000U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_COMM_L1_EXIT_LAT_SHIFT                               (15U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_COMM_L1_EXIT_LAT_MASK                                (0x00038000U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_CLK_PWR_MGMT_SHIFT                                   (18U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_CLK_PWR_MGMT_MASK                                    (0x00040000U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_UNSUP_SHIFT                                          (19U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_UNSUP_MASK                                           (0x00080000U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_DLL_ACTRPT_SHIFT                                     (20U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_DLL_ACTRPT_MASK                                      (0x00100000U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_BW_NOT_SHIFT                                         (21U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_BW_NOT_MASK                                          (0x00200000U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_ASPM_OPT_COMP_SHIFT                                  (22U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_ASPM_OPT_COMP_MASK                                   (0x00400000U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_PORT_NUM_SHIFT                                       (24U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_PORT_NUM_MASK                                        (0xff000000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_ASPM_CTRL_SHIFT                                      (0U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_ASPM_CTRL_MASK                                       (0x00000003U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_ASPM_CTRL_DISABLED                                    (0U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_ASPM_CTRL_L0S_ENABLED                                 (1U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_ASPM_CTRL_L1_ENABLED                                  (2U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_ASPM_CTRL_L0S_AND_L1_ENABLED                          (3U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_RCB_SHIFT                                            (3U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_RCB_MASK                                             (0x00000008U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_RCB_64_BYTE                                           (0U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_RCB_128_BYTE                                          (1U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_LINK_DIS_SHIFT                                       (4U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_LINK_DIS_MASK                                        (0x00000010U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_RETRAIN_LINK_SHIFT                                   (5U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_RETRAIN_LINK_MASK                                    (0x00000020U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_COM_CLK_CFG_SHIFT                                    (6U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_COM_CLK_CFG_MASK                                     (0x00000040U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_COM_CLK_CFG_ASYNC                                     (0U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_COM_CLK_CFG_COMMON                                    (1U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_EXT_SYN_SHIFT                                        (7U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_EXT_SYN_MASK                                         (0x00000080U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_EN_CPM_SHIFT                                         (8U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_EN_CPM_MASK                                          (0x00000100U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_HAWD_SHIFT                                           (9U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_HAWD_MASK                                            (0x00000200U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_LBMIE_SHIFT                                          (10U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_LBMIE_MASK                                           (0x00000400U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_LABIE_SHIFT                                          (11U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_LABIE_MASK                                           (0x00000800U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_LINK_SPEED_SHIFT                                     (16U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_LINK_SPEED_MASK                                      (0x000f0000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_NEG_LW_SHIFT                                         (20U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_NEG_LW_MASK                                          (0x03f00000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_UNDEF_SHIFT                                          (26U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_UNDEF_MASK                                           (0x04000000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_LINK_TRAIN_SHIFT                                     (27U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_LINK_TRAIN_MASK                                      (0x08000000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_SLOT_CLK_CONFIG_SHIFT                                (28U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_SLOT_CLK_CONFIG_MASK                                 (0x10000000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_DLL_ACT_SHIFT                                        (29U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_DLL_ACT_MASK                                         (0x20000000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_LBW_STATUS_SHIFT                                     (30U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_LBW_STATUS_MASK                                      (0x40000000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_LAB_STATUS_SHIFT                                     (31U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_LAB_STATUS_MASK                                      (0x80000000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_ABP_SHIFT                                           (0U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_ABP_MASK                                            (0x00000001U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_PCP_SHIFT                                           (1U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_PCP_MASK                                            (0x00000002U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_MRLSP_SHIFT                                         (2U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_MRLSP_MASK                                          (0x00000004U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_AIP_SHIFT                                           (3U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_AIP_MASK                                            (0x00000008U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_PIP_SHIFT                                           (4U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_PIP_MASK                                            (0x00000010U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_HPS_SHIFT                                           (5U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_HPS_MASK                                            (0x00000020U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_HPC_SHIFT                                           (6U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_HPC_MASK                                            (0x00000040U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_SPLV_SHIFT                                          (7U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_SPLV_MASK                                           (0x00007f80U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_SPLS_SHIFT                                          (15U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_SPLS_MASK                                           (0x00018000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_EIP_SHIFT                                           (17U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_EIP_MASK                                            (0x00020000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_NCCS_SHIFT                                          (18U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_NCCS_MASK                                           (0x00040000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAP_PSN_SHIFT                                           (19U)
#define PCIECTRL_RC_DBICS2_SLOT_CAP_PSN_MASK                                            (0xfff80000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_ABP_EN_SHIFT                                        (0U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_ABP_EN_MASK                                         (0x00000001U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_PFD_EN_SHIFT                                        (1U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_PFD_EN_MASK                                         (0x00000002U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_MRLSC_EN_SHIFT                                      (2U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_MRLSC_EN_MASK                                       (0x00000004U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_PDC_EN_SHIFT                                        (3U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_PDC_EN_MASK                                         (0x00000008U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_CCI_EN_SHIFT                                        (4U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_CCI_EN_MASK                                         (0x00000010U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_HPI_EN_SHIFT                                        (5U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_HPI_EN_MASK                                         (0x00000020U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_AIC_SHIFT                                           (6U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_AIC_MASK                                            (0x000000c0U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_PIC_SHIFT                                           (8U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_PIC_MASK                                            (0x00000300U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_PCC_SHIFT                                           (10U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_PCC_MASK                                            (0x00000400U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_EIC_SHIFT                                           (11U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_EIC_MASK                                            (0x00000800U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_DSC_EN_SHIFT                                        (12U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_DSC_EN_MASK                                         (0x00001000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_ABP_SHIFT                                           (16U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_ABP_MASK                                            (0x00010000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_PFD_SHIFT                                           (17U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_PFD_MASK                                            (0x00020000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_MRCSC_SHIFT                                         (18U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_MRCSC_MASK                                          (0x00040000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_PDC_SHIFT                                           (19U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_PDC_MASK                                            (0x00080000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_CC_SHIFT                                            (20U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_CC_MASK                                             (0x00100000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_MRLSS_SHIFT                                         (21U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_MRLSS_MASK                                          (0x00200000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_PDS_SHIFT                                           (22U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_PDS_MASK                                            (0x00400000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_EIS_SHIFT                                           (23U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_EIS_MASK                                            (0x00800000U)

#define PCIECTRL_RC_DBICS2_SLOT_CAS_DSC_SHIFT                                           (24U)
#define PCIECTRL_RC_DBICS2_SLOT_CAS_DSC_MASK                                            (0x01000000U)

#define PCIECTRL_RC_DBICS2_ROOT_CAC_SECE_EN_SHIFT                                       (0U)
#define PCIECTRL_RC_DBICS2_ROOT_CAC_SECE_EN_MASK                                        (0x00000001U)

#define PCIECTRL_RC_DBICS2_ROOT_CAC_SENE_EN_SHIFT                                       (1U)
#define PCIECTRL_RC_DBICS2_ROOT_CAC_SENE_EN_MASK                                        (0x00000002U)

#define PCIECTRL_RC_DBICS2_ROOT_CAC_SEFE_EN_SHIFT                                       (2U)
#define PCIECTRL_RC_DBICS2_ROOT_CAC_SEFE_EN_MASK                                        (0x00000004U)

#define PCIECTRL_RC_DBICS2_ROOT_CAC_PMEI_EN_SHIFT                                       (3U)
#define PCIECTRL_RC_DBICS2_ROOT_CAC_PMEI_EN_MASK                                        (0x00000008U)

#define PCIECTRL_RC_DBICS2_ROOT_CAC_CRSSV_EN_SHIFT                                      (4U)
#define PCIECTRL_RC_DBICS2_ROOT_CAC_CRSSV_EN_MASK                                       (0x00000010U)

#define PCIECTRL_RC_DBICS2_ROOT_CAC_CRSSV_SHIFT                                         (16U)
#define PCIECTRL_RC_DBICS2_ROOT_CAC_CRSSV_MASK                                          (0x00010000U)

#define PCIECTRL_RC_DBICS2_ROOT_STS_PME_RID_SHIFT                                       (0U)
#define PCIECTRL_RC_DBICS2_ROOT_STS_PME_RID_MASK                                        (0x0000ffffU)

#define PCIECTRL_RC_DBICS2_ROOT_STS_PME_SHIFT                                           (16U)
#define PCIECTRL_RC_DBICS2_ROOT_STS_PME_MASK                                            (0x00010000U)

#define PCIECTRL_RC_DBICS2_ROOT_STS_PME_PND_SHIFT                                       (17U)
#define PCIECTRL_RC_DBICS2_ROOT_STS_PME_PND_MASK                                        (0x00020000U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_2_CPL_TIMEOUT_RNG_SUPPORTED_SHIFT                    (0U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_2_CPL_TIMEOUT_RNG_SUPPORTED_MASK                     (0x0000000fU)

#define PCIECTRL_RC_DBICS2_DEV_CAP_2_CPL_TIMEOUT_DIS_SUPPORTED_SHIFT                    (4U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_2_CPL_TIMEOUT_DIS_SUPPORTED_MASK                     (0x00000010U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_2_ARI_FWD_SP_SHIFT                                   (5U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_2_ARI_FWD_SP_MASK                                    (0x00000020U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_2_AOR_SP_SHIFT                                       (6U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_2_AOR_SP_MASK                                        (0x00000040U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_2_AOC32_SP_SHIFT                                     (7U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_2_AOC32_SP_MASK                                      (0x00000080U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_2_AOC64_SP_SHIFT                                     (8U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_2_AOC64_SP_MASK                                      (0x00000100U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_2_CASC128_SP_SHIFT                                   (9U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_2_CASC128_SP_MASK                                    (0x00000200U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_2_NOROPR_SHIFT                                       (10U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_2_NOROPR_MASK                                        (0x00000400U)

#define PCIECTRL_RC_DBICS2_DEV_CAP_2_TPHC_SP_SHIFT                                      (12U)
#define PCIECTRL_RC_DBICS2_DEV_CAP_2_TPHC_SP_MASK                                       (0x00003000U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_2_CPL_TIMEOUT_VALUE_SHIFT                            (0U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_2_CPL_TIMEOUT_VALUE_MASK                             (0x0000000fU)

#define PCIECTRL_RC_DBICS2_DEV_CAS_2_CPL_TIMEOUT_DIS_SHIFT                              (4U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_2_CPL_TIMEOUT_DIS_MASK                               (0x00000010U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_2_ARI_FWD_SP_SHIFT                                   (5U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_2_ARI_FWD_SP_MASK                                    (0x00000020U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_2_AOP_REQ_EN_SHIFT                                   (6U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_2_AOP_REQ_EN_MASK                                    (0x00000040U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_2_AOP_EG_BLK_SHIFT                                   (7U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_2_AOP_EG_BLK_MASK                                    (0x00000080U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_2_IDO_REQ_EN_SHIFT                                   (8U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_2_IDO_REQ_EN_MASK                                    (0x00000100U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_2_IDO_CPL_EN_SHIFT                                   (9U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_2_IDO_CPL_EN_MASK                                    (0x00000200U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_2_LTR_EN_SHIFT                                       (10U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_2_LTR_EN_MASK                                        (0x00000400U)

#define PCIECTRL_RC_DBICS2_DEV_CAS_2_OBFF_EN_SHIFT                                      (13U)
#define PCIECTRL_RC_DBICS2_DEV_CAS_2_OBFF_EN_MASK                                       (0x00006000U)

#define PCIECTRL_RC_DBICS2_LNK_CAP_2_SP_LS_VEC_SHIFT                                    (1U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_2_SP_LS_VEC_MASK                                     (0x000000feU)

#define PCIECTRL_RC_DBICS2_LNK_CAP_2_CROSSLINK_SP_SHIFT                                 (8U)
#define PCIECTRL_RC_DBICS2_LNK_CAP_2_CROSSLINK_SP_MASK                                  (0x00000100U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_TRGT_LINK_SPEED_SHIFT                              (0U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_TRGT_LINK_SPEED_MASK                               (0x0000000fU)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_TRGT_LINK_SPEED_GEN1                                (1U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_TRGT_LINK_SPEED_GEN2                                (2U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_TRGT_LINK_SPEED_GEN3                                (3U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_ENTR_COMPL_SHIFT                                   (4U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_ENTR_COMPL_MASK                                    (0x00000010U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_HW_AUTO_SP_DIS_SHIFT                               (5U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_HW_AUTO_SP_DIS_MASK                                (0x00000020U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_SEL_DEEMP_SHIFT                                    (6U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_SEL_DEEMP_MASK                                     (0x00000040U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_TX_MARGIN_SHIFT                                    (7U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_TX_MARGIN_MASK                                     (0x00000380U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_ENT_MOD_COMPL_SHIFT                                (10U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_ENT_MOD_COMPL_MASK                                 (0x00000400U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_COMPL_SOS_SHIFT                                    (11U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_COMPL_SOS_MASK                                     (0x00000800U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_COMPL_PRST_DEEPH_SHIFT                             (12U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_COMPL_PRST_DEEPH_MASK                              (0x0000f000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_DEEMPH_LEVEL_SHIFT                                 (16U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_DEEMPH_LEVEL_MASK                                  (0x00010000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_EQ_COMPLETE_SHIFT                                  (17U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_EQ_COMPLETE_MASK                                   (0x00020000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_EQ_PH1_SHIFT                                       (18U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_EQ_PH1_MASK                                        (0x00040000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_EQ_PH2_SHIFT                                       (19U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_EQ_PH2_MASK                                        (0x00080000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_EQ_PH3_SHIFT                                       (20U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_EQ_PH3_MASK                                        (0x00100000U)

#define PCIECTRL_RC_DBICS2_LNK_CAS_2_LINK_EQ_REQ_SHIFT                                  (21U)
#define PCIECTRL_RC_DBICS2_LNK_CAS_2_LINK_EQ_REQ_MASK                                   (0x00200000U)

#ifdef __cplusplus
}
#endif
#endif  /* HW_PCIECTRL_RC_DBICS2_H_ */
