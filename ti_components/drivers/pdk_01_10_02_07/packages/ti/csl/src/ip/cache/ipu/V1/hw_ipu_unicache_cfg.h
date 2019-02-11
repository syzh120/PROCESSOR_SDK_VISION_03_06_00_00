/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2008-2016
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

#ifndef HW_IPU_UNICACHE_CFG_H_
#define HW_IPU_UNICACHE_CFG_H_

#ifdef __cplusplus
extern "C"
{
#endif


/****************************************************************************************************
* Register Definitions
****************************************************************************************************/

#define IPU_UNICACHE_INFO                                       (0x0U)
#define IPU_UNICACHE_CONFIG                                     (0x4U)
#define IPU_UNICACHE_INT                                        (0x8U)
#define IPU_UNICACHE_OCP                                        (0xcU)
#define IPU_UNICACHE_MAINT                                      (0x10U)
#define IPU_UNICACHE_MTSTART                                    (0x14U)
#define IPU_UNICACHE_MTEND                                      (0x18U)
#define IPU_UNICACHE_CTADDR                                     (0x1cU)
#define IPU_UNICACHE_CTDATA                                     (0x20U)
#define IPU_UNICACHE_ECC                                        (0x24U)
#define IPU_UNICACHE_L1DATA_ERR_INFO                            (0x28U)
#define IPU_UNICACHE_L1DATA_ERR_DATA_LOC                        (0x2cU)
#define IPU_UNICACHE_L1DATA_ERR_ADDR_LOC                        (0x30U)
#define IPU_UNICACHE_L1TAG_ERR_INFO                             (0x34U)
#define IPU_UNICACHE_L1TAG_ERR_DATA_LOC                         (0x38U)
#define IPU_UNICACHE_L1TAG_ERR_ADDR_LOC                         (0x3cU)
#define IPU_UNICACHE_L2RAM_ERR_INFO                             (0x40U)
#define IPU_UNICACHE_L2RAM_ERR_DATA_LOC                         (0x44U)
#define IPU_UNICACHE_L2RAM_ERR_ADDR_LOC                         (0x48U)

/****************************************************************************************************
* Field Definition Macros
****************************************************************************************************/

#define IPU_UNICACHE_INFO_VERSION_SHIFT                                             (0U)
#define IPU_UNICACHE_INFO_VERSION_MASK                                              (0x0000000fU)

#define IPU_UNICACHE_INFO_WAYS_SHIFT                                                (4U)
#define IPU_UNICACHE_INFO_WAYS_MASK                                                 (0x00000030U)
#define IPU_UNICACHE_INFO_WAYS_2WAY                                                  (0U)
#define IPU_UNICACHE_INFO_WAYS_4WAY                                                  (1U)
#define IPU_UNICACHE_INFO_WAYS_8WAY                                                  (2U)
#define IPU_UNICACHE_INFO_WAYS_RESERVED                                              (3U)

#define IPU_UNICACHE_INFO_SIZE_SHIFT                                                (6U)
#define IPU_UNICACHE_INFO_SIZE_MASK                                                 (0x0000ffc0U)

#define IPU_UNICACHE_INFO_SLAVES_SHIFT                                              (16U)
#define IPU_UNICACHE_INFO_SLAVES_MASK                                               (0x00070000U)

#define IPU_UNICACHE_INFO_MASTERS_SHIFT                                             (19U)
#define IPU_UNICACHE_INFO_MASTERS_MASK                                              (0x00180000U)

#define IPU_UNICACHE_INFO_RESERVED_SHIFT                                            (21U)
#define IPU_UNICACHE_INFO_RESERVED_MASK                                             (0xffe00000U)

#define IPU_UNICACHE_CONFIG_RESERVED_SHIFT                                          (5U)
#define IPU_UNICACHE_CONFIG_RESERVED_MASK                                           (0xffffffe0U)

#define IPU_UNICACHE_CONFIG_SCACHE_LOCK_SHIFT                                       (0U)
#define IPU_UNICACHE_CONFIG_SCACHE_LOCK_MASK                                        (0x00000001U)
#define IPU_UNICACHE_CONFIG_SCACHE_LOCK_NON_SECURE                                  (0U)
#define IPU_UNICACHE_CONFIG_SCACHE_LOCK_SECURE                                      (1U)

#define IPU_UNICACHE_CONFIG_BYPASS_SHIFT                                            (1U)
#define IPU_UNICACHE_CONFIG_BYPASS_MASK                                             (0x00000002U)
#define IPU_UNICACHE_CONFIG_BYPASS_BYPASS                                           (0U)
#define IPU_UNICACHE_CONFIG_BYPASS_NORMAL                                           (1U)

#define IPU_UNICACHE_CONFIG_LOCK_INT_SHIFT                                          (2U)
#define IPU_UNICACHE_CONFIG_LOCK_INT_MASK                                           (0x00000004U)
#define IPU_UNICACHE_CONFIG_LOCK_INT_SECURE                                         (0U)
#define IPU_UNICACHE_CONFIG_LOCK_INT_NON_SECURE                                     (1U)

#define IPU_UNICACHE_CONFIG_LOCK_PORT_SHIFT                                         (3U)
#define IPU_UNICACHE_CONFIG_LOCK_PORT_MASK                                          (0x00000008U)
#define IPU_UNICACHE_CONFIG_LOCK_PORT_SECURE                                        (0U)
#define IPU_UNICACHE_CONFIG_LOCK_PORT_NON_SECURE                                    (1U)

#define IPU_UNICACHE_CONFIG_LOCK_MAIN_SHIFT                                         (4U)
#define IPU_UNICACHE_CONFIG_LOCK_MAIN_MASK                                          (0x00000010U)
#define IPU_UNICACHE_CONFIG_LOCK_MAIN_SECURE                                        (0U)
#define IPU_UNICACHE_CONFIG_LOCK_MAIN_NON_SECURE                                    (1U)

#define IPU_UNICACHE_INT_RESERVED_SHIFT                                             (9U)
#define IPU_UNICACHE_INT_RESERVED_MASK                                              (0xfffffe00U)

#define IPU_UNICACHE_INT_CONFIG_SHIFT                                               (0U)
#define IPU_UNICACHE_INT_CONFIG_MASK                                                (0x00000001U)

#define IPU_UNICACHE_INT_PAGEFAULT_SHIFT                                            (1U)
#define IPU_UNICACHE_INT_PAGEFAULT_MASK                                             (0x00000002U)

#define IPU_UNICACHE_INT_MAINT_SHIFT                                                (2U)
#define IPU_UNICACHE_INT_MAINT_MASK                                                 (0x00000004U)

#define IPU_UNICACHE_INT_WRITE_SHIFT                                                (3U)
#define IPU_UNICACHE_INT_WRITE_MASK                                                 (0x00000008U)

#define IPU_UNICACHE_INT_READ_SHIFT                                                 (4U)
#define IPU_UNICACHE_INT_READ_MASK                                                  (0x00000010U)

#define IPU_UNICACHE_INT_PORT_SHIFT                                                 (5U)
#define IPU_UNICACHE_INT_PORT_MASK                                                  (0x000001e0U)

#define IPU_UNICACHE_OCP_RESERVED_SHIFT                                             (6U)
#define IPU_UNICACHE_OCP_RESERVED_MASK                                              (0xffffffc0U)
#define IPU_UNICACHE_OCP_WRAP_SHIFT                                                 (0U)
#define IPU_UNICACHE_OCP_WRAP_MASK                                                  (0x00000001U)
#define IPU_UNICACHE_OCP_WRAP_NON_WRAP                                              (0U)
#define IPU_UNICACHE_OCP_WRAP_WRAP                                                  (1U)

#define IPU_UNICACHE_OCP_WRBUFFER_SHIFT                                             (1U)
#define IPU_UNICACHE_OCP_WRBUFFER_MASK                                              (0x00000002U)
#define IPU_UNICACHE_OCP_WRBUFFER_NO_BUFFERED                                       (0U)
#define IPU_UNICACHE_OCP_WRBUFFER_BUFFERED                                          (1U)

#define IPU_UNICACHE_OCP_WRALLOCATE_SHIFT                                           (2U)
#define IPU_UNICACHE_OCP_WRALLOCATE_MASK                                            (0x00000004U)
#define IPU_UNICACHE_OCP_WRALLOCATE_NO_ALLOC                                        (0U)
#define IPU_UNICACHE_OCP_WRALLOCATE_SIDEBAND                                        (1U)

#define IPU_UNICACHE_OCP_CACHED_SHIFT                                               (3U)
#define IPU_UNICACHE_OCP_CACHED_MASK                                                (0x00000008U)
#define IPU_UNICACHE_OCP_CACHED_NO_CACHE                                            (0U)
#define IPU_UNICACHE_OCP_CACHED_CACHE                                               (1U)

#define IPU_UNICACHE_OCP_PREFETCH_SHIFT                                             (4U)
#define IPU_UNICACHE_OCP_PREFETCH_MASK                                              (0x00000010U)
#define IPU_UNICACHE_OCP_PREFETCH_MMU                                               (0U)
#define IPU_UNICACHE_OCP_PREFETCH_PREFETCH                                          (1U)

#define IPU_UNICACHE_OCP_CLEANBUF_SHIFT                                             (5U)
#define IPU_UNICACHE_OCP_CLEANBUF_MASK                                              (0x00000020U)
#define IPU_UNICACHE_OCP_CLEANBUF_NO_CLEAN                                          (0U)
#define IPU_UNICACHE_OCP_CLEANBUF_CLEAN                                             (1U)
#define IPU_UNICACHE_MAINT_RESERVED_SHIFT                                           (6U)
#define IPU_UNICACHE_MAINT_RESERVED_MASK                                            (0xffffffc0U)

#define IPU_UNICACHE_MAINT_PRELOAD_SHIFT                                            (0U)
#define IPU_UNICACHE_MAINT_PRELOAD_MASK                                             (0x00000001U)
#define IPU_UNICACHE_MAINT_PRELOAD_DISABLE                                          (0U)
#define IPU_UNICACHE_MAINT_PRELOAD_ENABLE                                           (1U)

#define IPU_UNICACHE_MAINT_LOCK_SHIFT                                               (1U)
#define IPU_UNICACHE_MAINT_LOCK_MASK                                                (0x00000002U)
#define IPU_UNICACHE_MAINT_LOCK_DISABLE                                             (0U)
#define IPU_UNICACHE_MAINT_LOCK_ENABLE                                              (1U)

#define IPU_UNICACHE_MAINT_UNLOCK_SHIFT                                             (2U)
#define IPU_UNICACHE_MAINT_UNLOCK_MASK                                              (0x00000004U)
#define IPU_UNICACHE_MAINT_UNLOCK_DISABLE                                           (0U)
#define IPU_UNICACHE_MAINT_UNLOCK_ENABLE                                            (1U)

#define IPU_UNICACHE_MAINT_CLEAN_SHIFT                                              (3U)
#define IPU_UNICACHE_MAINT_CLEAN_MASK                                               (0x00000008U)
#define IPU_UNICACHE_MAINT_CLEAN_DISABLE                                            (0U)
#define IPU_UNICACHE_MAINT_CLEAN_ENABLE                                             (1U)

#define IPU_UNICACHE_MAINT_INVALIDATE_SHIFT                                         (4U)
#define IPU_UNICACHE_MAINT_INVALIDATE_MASK                                          (0x00000010U)
#define IPU_UNICACHE_MAINT_INVALIDATE_DISABLE                                       (0U)
#define IPU_UNICACHE_MAINT_INVALIDATE_ENABLE                                        (1U)

#define IPU_UNICACHE_MAINT_INTERRUPT_SHIFT                                          (5U)
#define IPU_UNICACHE_MAINT_INTERRUPT_MASK                                           (0x00000020U)
#define IPU_UNICACHE_MAINT_INTERRUPT_NO_INT                                         (0U)
#define IPU_UNICACHE_MAINT_INTERRUPT_GEN_INT                                        (1U)

#define IPU_UNICACHE_MTSTART_START_ADDR_SHIFT                                       (0U)
#define IPU_UNICACHE_MTSTART_START_ADDR_MASK                                        (0xffffffffU)

#define IPU_UNICACHE_MTEND_END_ADDR_SHIFT                                           (0U)
#define IPU_UNICACHE_MTEND_END_ADDR_MASK                                            (0xffffffffU)

#define IPU_UNICACHE_CTADDR_ADDRESS_SHIFT                                           (0U)
#define IPU_UNICACHE_CTADDR_ADDRESS_MASK                                            (0xffffffffU)

#define IPU_UNICACHE_CTDATA_DATA_SHIFT                                              (0U)
#define IPU_UNICACHE_CTDATA_DATA_MASK                                               (0xffffffffU)

#define IPU_UNICACHE_ECC_L1DATA_EN_SHIFT                                            (0U)
#define IPU_UNICACHE_ECC_L1DATA_EN_MASK                                             (0x00000001U)

#define IPU_UNICACHE_ECC_L1DATA_CODE_MASK_SHIFT                                     (1U)
#define IPU_UNICACHE_ECC_L1DATA_CODE_MASK_MASK                                      (0x00000002U)

#define IPU_UNICACHE_ECC_L1DATA_DATA_MASK_SHIFT                                     (2U)
#define IPU_UNICACHE_ECC_L1DATA_DATA_MASK_MASK                                      (0x00000004U)

#define IPU_UNICACHE_ECC_L1TAG_EN_SHIFT                                             (5U)
#define IPU_UNICACHE_ECC_L1TAG_EN_MASK                                              (0x00000020U)

#define IPU_UNICACHE_ECC_L1TAG_CODE_MASK_SHIFT                                      (6U)
#define IPU_UNICACHE_ECC_L1TAG_CODE_MASK_MASK                                       (0x00000040U)

#define IPU_UNICACHE_ECC_L1TAG_DATA_MASK_SHIFT                                      (7U)
#define IPU_UNICACHE_ECC_L1TAG_DATA_MASK_MASK                                       (0x00000080U)

#define IPU_UNICACHE_ECC_L2RAM_EN_SHIFT                                             (10U)
#define IPU_UNICACHE_ECC_L2RAM_EN_MASK                                              (0x00000400U)

#define IPU_UNICACHE_ECC_L2RAM_CODE_MASK_SHIFT                                      (11U)
#define IPU_UNICACHE_ECC_L2RAM_CODE_MASK_MASK                                       (0x00000800U)

#define IPU_UNICACHE_ECC_L2RAM_DATA_MASK_SHIFT                                      (12U)
#define IPU_UNICACHE_ECC_L2RAM_DATA_MASK_MASK                                       (0x00001000U)

#define IPU_UNICACHE_ECC_L1DATA_SRESP_EN_SHIFT                                      (3U)
#define IPU_UNICACHE_ECC_L1DATA_SRESP_EN_MASK                                       (0x00000008U)

#define IPU_UNICACHE_ECC_L1DATA_SEC_AUTO_EN_SHIFT                                   (4U)
#define IPU_UNICACHE_ECC_L1DATA_SEC_AUTO_EN_MASK                                    (0x00000010U)

#define IPU_UNICACHE_ECC_L1TAG_SRESP_EN_SHIFT                                       (8U)
#define IPU_UNICACHE_ECC_L1TAG_SRESP_EN_MASK                                        (0x00000100U)

#define IPU_UNICACHE_ECC_L1TAG_SEC_AUTO_EN_SHIFT                                    (9U)
#define IPU_UNICACHE_ECC_L1TAG_SEC_AUTO_EN_MASK                                     (0x00000200U)

#define IPU_UNICACHE_ECC_L2RAM_SRESP_EN_SHIFT                                       (13U)
#define IPU_UNICACHE_ECC_L2RAM_SRESP_EN_MASK                                        (0x00002000U)

#define IPU_UNICACHE_ECC_L2RAM_SEC_AUTO_EN_SHIFT                                    (14U)
#define IPU_UNICACHE_ECC_L2RAM_SEC_AUTO_EN_MASK                                     (0x00004000U)

#define IPU_UNICACHE_L1DATA_ERR_INFO_SEC_SHIFT                                      (0U)
#define IPU_UNICACHE_L1DATA_ERR_INFO_SEC_MASK                                       (0x00000001U)

#define IPU_UNICACHE_L1DATA_ERR_INFO_CODEERR_SHIFT                                  (1U)
#define IPU_UNICACHE_L1DATA_ERR_INFO_CODEERR_MASK                                   (0x00000002U)

#define IPU_UNICACHE_L1DATA_ERR_INFO_DED_SHIFT                                      (2U)
#define IPU_UNICACHE_L1DATA_ERR_INFO_DED_MASK                                       (0x00000004U)

#define IPU_UNICACHE_L1DATA_ERR_INFO_ACCESSTYPE_SHIFT                               (3U)
#define IPU_UNICACHE_L1DATA_ERR_INFO_ACCESSTYPE_MASK                                (0x00000008U)

#define IPU_UNICACHE_L1DATA_ERR_DATA_LOC_DATALOC_SHIFT                              (0U)
#define IPU_UNICACHE_L1DATA_ERR_DATA_LOC_DATALOC_MASK                               (0x0000003fU)

#define IPU_UNICACHE_L1DATA_ERR_ADDR_LOC_LOCATION_SHIFT                             (0U)
#define IPU_UNICACHE_L1DATA_ERR_ADDR_LOC_LOCATION_MASK                              (0x000001ffU)

#define IPU_UNICACHE_L1TAG_ERR_INFO_SEC_SHIFT                                       (0U)
#define IPU_UNICACHE_L1TAG_ERR_INFO_SEC_MASK                                        (0x00000001U)

#define IPU_UNICACHE_L1TAG_ERR_INFO_CODEERR_SHIFT                                   (1U)
#define IPU_UNICACHE_L1TAG_ERR_INFO_CODEERR_MASK                                    (0x00000002U)

#define IPU_UNICACHE_L1TAG_ERR_INFO_DED_SHIFT                                       (2U)
#define IPU_UNICACHE_L1TAG_ERR_INFO_DED_MASK                                        (0x00000004U)

#define IPU_UNICACHE_L1TAG_ERR_INFO_ACCESSTYPE_SHIFT                                (3U)
#define IPU_UNICACHE_L1TAG_ERR_INFO_ACCESSTYPE_MASK                                 (0x00000008U)

#define IPU_UNICACHE_L1TAG_ERR_DATA_LOC_DATALOC_SHIFT                               (0U)
#define IPU_UNICACHE_L1TAG_ERR_DATA_LOC_DATALOC_MASK                                (0x0000003fU)

#define IPU_UNICACHE_L1TAG_ERR_ADDR_LOC_LOCATION_SHIFT                              (0U)
#define IPU_UNICACHE_L1TAG_ERR_ADDR_LOC_LOCATION_MASK                               (0x000001ffU)

#define IPU_UNICACHE_L2RAM_ERR_INFO_SEC_SHIFT                                       (0U)
#define IPU_UNICACHE_L2RAM_ERR_INFO_SEC_MASK                                        (0x00000001U)

#define IPU_UNICACHE_L2RAM_ERR_INFO_CODEERR_SHIFT                                   (1U)
#define IPU_UNICACHE_L2RAM_ERR_INFO_CODEERR_MASK                                    (0x00000002U)

#define IPU_UNICACHE_L2RAM_ERR_INFO_DED_SHIFT                                       (2U)
#define IPU_UNICACHE_L2RAM_ERR_INFO_DED_MASK                                        (0x00000004U)

#define IPU_UNICACHE_L2RAM_ERR_INFO_ACCESS_TYPE_CACHE2_SHIFT                        (3U)
#define IPU_UNICACHE_L2RAM_ERR_INFO_ACCESS_TYPE_CACHE2_MASK                         (0x00000008U)

#define IPU_UNICACHE_L2RAM_ERR_INFO_ACCESS_TYPE_CACHE1_SHIFT                        (4U)
#define IPU_UNICACHE_L2RAM_ERR_INFO_ACCESS_TYPE_CACHE1_MASK                         (0x00000010U)

#define IPU_UNICACHE_L2RAM_ERR_INFO_ACCESS_TYPE_MPORT_SHIFT                         (5U)
#define IPU_UNICACHE_L2RAM_ERR_INFO_ACCESS_TYPE_MPORT_MASK                          (0x00000020U)

#define IPU_UNICACHE_L2RAM_ERR_DATA_LOC_DATALOC_SHIFT                               (0U)
#define IPU_UNICACHE_L2RAM_ERR_DATA_LOC_DATALOC_MASK                                (0x0000003fU)

#define IPU_UNICACHE_L2RAM_ERR_ADDR_LOC_LOCATION_SHIFT                              (0U)
#define IPU_UNICACHE_L2RAM_ERR_ADDR_LOC_LOCATION_MASK                               (0x000001ffU)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_IPU_UNICACHE_CFG_H_ */

