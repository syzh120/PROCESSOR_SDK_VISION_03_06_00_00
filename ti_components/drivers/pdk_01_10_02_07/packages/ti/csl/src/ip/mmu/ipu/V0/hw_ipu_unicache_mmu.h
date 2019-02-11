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

#ifndef HW_IPU_UNICACHE_MMU_H_
#define HW_IPU_UNICACHE_MMU_H_

#ifdef __cplusplus
extern "C"
{
#endif

/****************************************************************************************************
* Register Definitions 
****************************************************************************************************/
#define IPU_LARGE_ADDR(n)                                                                                   ((uint32_t)0x0U + ((n) * (uint32_t)4U))
#define IPU_LARGE_XLTE(n)                                                                                   ((uint32_t)0x20U + ((n) * (uint32_t)4U))
#define IPU_LARGE_POLICY(n)                                                                                 ((uint32_t)0x40U + ((n) * (uint32_t)4U))
#define IPU_MED_ADDR(n)                                                                                     ((uint32_t)0x60U + ((n) * (uint32_t)4U))
#define IPU_MED_XLTE(n)                                                                                     ((uint32_t)0xa0U + ((n) * (uint32_t)4U))
#define IPU_MED_POLICY(n)                                                                                   ((uint32_t)0xe0U + ((n) * (uint32_t)4U))
#define IPU_SMALL_MAINT(n)                                                                                  ((uint32_t)0x2a0U + ((n) * (uint32_t)4U))
#define IPU_MAINT                                                                                           (0x4a8U)
#define IPU_MTSTART                                                                                         (0x4acU)
#define IPU_MTEND                                                                                           (0x4b0U)
#define IPU_MAINTST                                                                                         (0x4b4U)
#define IPU_MMUCONFIG                                                                                       (0x4b8U)
#define IPU_SMALL_ADDR(n)                                                                                   ((uint32_t)0x120U + ((n) * (uint32_t)4U))
#define IPU_SMALL_XLTE(n)                                                                                   ((uint32_t)0x1a0U + ((n) * (uint32_t)4U))
#define IPU_SMALL_POLICY(n)                                                                                 ((uint32_t)0x220U + ((n) * (uint32_t)4U))

/****************************************************************************************************
* Field Definition Macros 
****************************************************************************************************/

#define IPU_LARGE_ADDR_ADDRESS_SHIFT                                                                        (25U)
#define IPU_LARGE_ADDR_ADDRESS_MASK                                                                         (0xfe000000U)

#define IPU_LARGE_ADDR_RESERVED_SHIFT                                                                       (0U)
#define IPU_LARGE_ADDR_RESERVED_MASK                                                                        (0x00000001U)

#define IPU_LARGE_XLTE_ADDRESS_SHIFT                                                                        (25U)
#define IPU_LARGE_XLTE_ADDRESS_MASK                                                                         (0xfe000000U)

#define IPU_LARGE_XLTE_IGNORE_SHIFT                                                                         (0U)
#define IPU_LARGE_XLTE_IGNORE_MASK                                                                          (0x00000001U)

#define IPU_LARGE_XLTE_RESERVED_SHIFT                                                                       (1U)
#define IPU_LARGE_XLTE_RESERVED_MASK                                                                        (0x01fffffeU)

#define IPU_LARGE_POLICY_ENABLE_SHIFT                                                                       (0U)
#define IPU_LARGE_POLICY_ENABLE_MASK                                                                        (0x00000001U)
#define IPU_LARGE_POLICY_ENABLE_DISABLE                                                                      (0U)
#define IPU_LARGE_POLICY_ENABLE_ENABLE                                                                       (1U)

#define IPU_LARGE_POLICY_SIZE_SHIFT                                                                         (1U)
#define IPU_LARGE_POLICY_SIZE_MASK                                                                          (0x00000002U)
#define IPU_LARGE_POLICY_SIZE_32MB                                                                          (0U)
#define IPU_LARGE_POLICY_SIZE_512MB                                                                         (1U)

#define IPU_LARGE_POLICY_RESERVED_SHIFT                                                                     (2U)
#define IPU_LARGE_POLICY_RESERVED_MASK                                                                      (0x00000004U)
#define IPU_LARGE_POLICY_RESERVED_BIG_ENDIAN                                                                 (0U)
#define IPU_LARGE_POLICY_RESERVED_LITTLE_ENDIAN                                                              (1U)

#define IPU_LARGE_POLICY_VOLATILE_SHIFT                                                                     (3U)
#define IPU_LARGE_POLICY_VOLATILE_MASK                                                                      (0x00000008U)
#define IPU_LARGE_POLICY_VOLATILE_DISABLE                                                                    (0U)
#define IPU_LARGE_POLICY_VOLATILE_ENABLE                                                                     (1U)

#define IPU_LARGE_POLICY_EXECUTE_SHIFT                                                                      (4U)
#define IPU_LARGE_POLICY_EXECUTE_MASK                                                                       (0x00000010U)

#define IPU_LARGE_POLICY_READ_SHIFT                                                                         (5U)
#define IPU_LARGE_POLICY_READ_MASK                                                                          (0x00000020U)

#define IPU_LARGE_POLICY_PRELOAD_SHIFT                                                                      (6U)
#define IPU_LARGE_POLICY_PRELOAD_MASK                                                                       (0x00000040U)
#define IPU_LARGE_POLICY_PRELOAD_DISABLE                                                                     (0U)
#define IPU_LARGE_POLICY_PRELOAD_ENABLE                                                                      (1U)

#define IPU_LARGE_POLICY_EXCLUSION_SHIFT                                                                    (7U)
#define IPU_LARGE_POLICY_EXCLUSION_MASK                                                                     (0x00000080U)
#define IPU_LARGE_POLICY_EXCLUSION_DISABLE                                                                   (0U)
#define IPU_LARGE_POLICY_EXCLUSION_ENABLE                                                                    (1U)

#define IPU_LARGE_POLICY_L1_CACHEABLE_SHIFT                                                                 (16U)
#define IPU_LARGE_POLICY_L1_CACHEABLE_MASK                                                                  (0x00010000U)
#define IPU_LARGE_POLICY_L1_CACHEABLE_DISABLE                                                                (0U)
#define IPU_LARGE_POLICY_L1_CACHEABLE_ENABLE                                                                 (1U)

#define IPU_LARGE_POLICY_L1_POSTED_SHIFT                                                                    (17U)
#define IPU_LARGE_POLICY_L1_POSTED_MASK                                                                     (0x00020000U)
#define IPU_LARGE_POLICY_L1_POSTED_NON_POSTED                                                                (0U)
#define IPU_LARGE_POLICY_L1_POSTED_POSTED                                                                    (1U)

#define IPU_LARGE_POLICY_L1_WR_POLICY_SHIFT                                                                 (19U)
#define IPU_LARGE_POLICY_L1_WR_POLICY_MASK                                                                  (0x00080000U)
#define IPU_LARGE_POLICY_L1_WR_POLICY_WT                                                                     (0U)
#define IPU_LARGE_POLICY_L1_WR_POLICY_WB                                                                     (1U)

#define IPU_LARGE_POLICY_L2_CACHEABLE_SHIFT                                                                 (20U)
#define IPU_LARGE_POLICY_L2_CACHEABLE_MASK                                                                  (0x00100000U)
#define IPU_LARGE_POLICY_L2_CACHEABLE_NON_CACHEABLE                                                          (0U)
#define IPU_LARGE_POLICY_L2_CACHEABLE_CACHEABLE                                                              (1U)

#define IPU_LARGE_POLICY_L1_ALLOCATE_SHIFT                                                                  (18U)
#define IPU_LARGE_POLICY_L1_ALLOCATE_MASK                                                                   (0x00040000U)
#define IPU_LARGE_POLICY_L1_ALLOCATE_NON_ALLOCATE                                                            (0U)
#define IPU_LARGE_POLICY_L1_ALLOCATE_ALLOCATE                                                                (1U)

#define IPU_LARGE_POLICY_L2_ALLOCATE_SHIFT                                                                  (22U)
#define IPU_LARGE_POLICY_L2_ALLOCATE_MASK                                                                   (0x00400000U)
#define IPU_LARGE_POLICY_L2_ALLOCATE_NON_ALLOCATE                                                            (0U)
#define IPU_LARGE_POLICY_L2_ALLOCATE_ALLOCATE                                                                (1U)

#define IPU_LARGE_POLICY_L2_WR_POLICY_SHIFT                                                                 (23U)
#define IPU_LARGE_POLICY_L2_WR_POLICY_MASK                                                                  (0x00800000U)
#define IPU_LARGE_POLICY_L2_WR_POLICY_WT                                                                     (0U)
#define IPU_LARGE_POLICY_L2_WR_POLICY_WB                                                                     (1U)

#define IPU_LARGE_POLICY_L2_POSTED_SHIFT                                                                    (21U)
#define IPU_LARGE_POLICY_L2_POSTED_MASK                                                                     (0x00200000U)
#define IPU_LARGE_POLICY_L2_POSTED_NON_POSTED                                                                (0U)
#define IPU_LARGE_POLICY_L2_POSTED_POSTED                                                                    (1U)

#define IPU_LARGE_POLICY_RESERVED1_SHIFT                                                                    (8U)
#define IPU_LARGE_POLICY_RESERVED1_MASK                                                                     (0x0000ff00U)

#define IPU_LARGE_POLICY_RESERVED2_SHIFT                                                                    (24U)
#define IPU_LARGE_POLICY_RESERVED2_MASK                                                                     (0xff000000U)

#define IPU_MED_ADDR_ADDRESS_SHIFT                                                                          (17U)
#define IPU_MED_ADDR_ADDRESS_MASK                                                                           (0xfffe0000U)

#define IPU_MED_ADDR_RESERVED_SHIFT                                                                         (0U)
#define IPU_MED_ADDR_RESERVED_MASK                                                                          (0x0001ffffU)

#define IPU_MED_XLTE_IGNORE_SHIFT                                                                           (0U)
#define IPU_MED_XLTE_IGNORE_MASK                                                                            (0x00000001U)

#define IPU_MED_XLTE_ADDRESS_SHIFT                                                                          (17U)
#define IPU_MED_XLTE_ADDRESS_MASK                                                                           (0xfffe0000U)

#define IPU_MED_XLTE_RESERVED_SHIFT                                                                         (1U)
#define IPU_MED_XLTE_RESERVED_MASK                                                                          (0x0001fffeU)

#define IPU_MED_POLICY_ENABLE_SHIFT                                                                         (0U)
#define IPU_MED_POLICY_ENABLE_MASK                                                                          (0x00000001U)
#define IPU_MED_POLICY_ENABLE_DISABLE                                                                        (0U)
#define IPU_MED_POLICY_ENABLE_ENABLE                                                                         (1U)

#define IPU_MED_POLICY_SIZE_SHIFT                                                                           (1U)
#define IPU_MED_POLICY_SIZE_MASK                                                                            (0x00000002U)
#define IPU_MED_POLICY_SIZE_128KB                                                                           (0U)
#define IPU_MED_POLICY_SIZE_256KB                                                                           (1U)

#define IPU_MED_POLICY_RESERVED_SHIFT                                                                       (2U)
#define IPU_MED_POLICY_RESERVED_MASK                                                                        (0x00000004U)
#define IPU_MED_POLICY_RESERVED_BIG_ENDIAN                                                                   (0U)
#define IPU_MED_POLICY_RESERVED_LITTLE_ENDIAN                                                                (1U)

#define IPU_MED_POLICY_VOLATILE_SHIFT                                                                       (3U)
#define IPU_MED_POLICY_VOLATILE_MASK                                                                        (0x00000008U)
#define IPU_MED_POLICY_VOLATILE_DISABLE                                                                      (0U)
#define IPU_MED_POLICY_VOLATILE_ENABLE                                                                       (1U)

#define IPU_MED_POLICY_EXECUTE_SHIFT                                                                        (4U)
#define IPU_MED_POLICY_EXECUTE_MASK                                                                         (0x00000010U)

#define IPU_MED_POLICY_READ_SHIFT                                                                           (5U)
#define IPU_MED_POLICY_READ_MASK                                                                            (0x00000020U)

#define IPU_MED_POLICY_PRELOAD_SHIFT                                                                        (6U)
#define IPU_MED_POLICY_PRELOAD_MASK                                                                         (0x00000040U)
#define IPU_MED_POLICY_PRELOAD_DISABLE                                                                       (0U)
#define IPU_MED_POLICY_PRELOAD_ENABLE                                                                        (1U)

#define IPU_MED_POLICY_EXCLUSION_SHIFT                                                                      (7U)
#define IPU_MED_POLICY_EXCLUSION_MASK                                                                       (0x00000080U)
#define IPU_MED_POLICY_EXCLUSION_DISABLE                                                                     (0U)
#define IPU_MED_POLICY_EXCLUSION_ENABLE                                                                      (1U)

#define IPU_MED_POLICY_L1_CACHEABLE_SHIFT                                                                   (16U)
#define IPU_MED_POLICY_L1_CACHEABLE_MASK                                                                    (0x00010000U)
#define IPU_MED_POLICY_L1_CACHEABLE_DISABLE                                                                  (0U)
#define IPU_MED_POLICY_L1_CACHEABLE_ENABLE                                                                   (1U)

#define IPU_MED_POLICY_L1_POSTED_SHIFT                                                                      (17U)
#define IPU_MED_POLICY_L1_POSTED_MASK                                                                       (0x00020000U)
#define IPU_MED_POLICY_L1_POSTED_NON_POSTED                                                                  (0U)
#define IPU_MED_POLICY_L1_POSTED_POSTED                                                                      (1U)

#define IPU_MED_POLICY_L1_ALLOCATE_SHIFT                                                                    (18U)
#define IPU_MED_POLICY_L1_ALLOCATE_MASK                                                                     (0x00040000U)
#define IPU_MED_POLICY_L1_ALLOCATE_NON_ALLOCATE                                                              (0U)
#define IPU_MED_POLICY_L1_ALLOCATE_ALLOCATE                                                                  (1U)

#define IPU_MED_POLICY_L1_WR_POLICY_SHIFT                                                                   (19U)
#define IPU_MED_POLICY_L1_WR_POLICY_MASK                                                                    (0x00080000U)
#define IPU_MED_POLICY_L1_WR_POLICY_WT                                                                       (0U)
#define IPU_MED_POLICY_L1_WR_POLICY_WB                                                                       (1U)

#define IPU_MED_POLICY_L2_CACHEABLE_SHIFT                                                                   (20U)
#define IPU_MED_POLICY_L2_CACHEABLE_MASK                                                                    (0x00100000U)
#define IPU_MED_POLICY_L2_CACHEABLE_NON_CACHEABLE                                                            (0U)
#define IPU_MED_POLICY_L2_CACHEABLE_CACHEABLE                                                                (1U)

#define IPU_MED_POLICY_L2_POSTED_SHIFT                                                                      (21U)
#define IPU_MED_POLICY_L2_POSTED_MASK                                                                       (0x00200000U)
#define IPU_MED_POLICY_L2_POSTED_NON_POSTED                                                                  (0U)
#define IPU_MED_POLICY_L2_POSTED_POSTED                                                                      (1U)

#define IPU_MED_POLICY_L2_ALLOCATE_SHIFT                                                                    (22U)
#define IPU_MED_POLICY_L2_ALLOCATE_MASK                                                                     (0x00400000U)
#define IPU_MED_POLICY_L2_ALLOCATE_NON_ALLOCATE                                                              (0U)
#define IPU_MED_POLICY_L2_ALLOCATE_ALLOCATE                                                                  (1U)

#define IPU_MED_POLICY_L2_WR_POLICY_SHIFT                                                                   (23U)
#define IPU_MED_POLICY_L2_WR_POLICY_MASK                                                                    (0x00800000U)
#define IPU_MED_POLICY_L2_WR_POLICY_WT                                                                       (0U)
#define IPU_MED_POLICY_L2_WR_POLICY_WB                                                                       (1U)

#define IPU_MED_POLICY_RESERVED1_SHIFT                                                                      (8U)
#define IPU_MED_POLICY_RESERVED1_MASK                                                                       (0x0000ff00U)

#define IPU_MED_POLICY_RESERVED2_SHIFT                                                                      (24U)
#define IPU_MED_POLICY_RESERVED2_MASK                                                                       (0xff000000U)

#define IPU_SMALL_MAINT_PRELOAD_SHIFT                                                                       (0U)
#define IPU_SMALL_MAINT_PRELOAD_MASK                                                                        (0x00000001U)

#define IPU_SMALL_MAINT_LOCK_SHIFT                                                                          (1U)
#define IPU_SMALL_MAINT_LOCK_MASK                                                                           (0x00000002U)

#define IPU_SMALL_MAINT_CLEAN_SHIFT                                                                         (2U)
#define IPU_SMALL_MAINT_CLEAN_MASK                                                                          (0x00000004U)

#define IPU_SMALL_MAINT_INVALIDATE_SHIFT                                                                    (3U)
#define IPU_SMALL_MAINT_INVALIDATE_MASK                                                                     (0x00000008U)

#define IPU_SMALL_MAINT_INTERRUPT_SHIFT                                                                     (4U)
#define IPU_SMALL_MAINT_INTERRUPT_MASK                                                                      (0x00000010U)

#define IPU_SMALL_MAINT_RESERVED_SHIFT                                                                      (5U)
#define IPU_SMALL_MAINT_RESERVED_MASK                                                                       (0xffffffe0U)

#define IPU_MAINT_PRELOAD_SHIFT                                                                             (0U)
#define IPU_MAINT_PRELOAD_MASK                                                                              (0x00000001U)
#define IPU_MAINT_PRELOAD_DISABLE                                                                            (0U)
#define IPU_MAINT_PRELOAD_ENABLE                                                                             (1U)

#define IPU_MAINT_LOCK_SHIFT                                                                                (1U)
#define IPU_MAINT_LOCK_MASK                                                                                 (0x00000002U)
#define IPU_MAINT_LOCK_DISABLE                                                                               (0U)
#define IPU_MAINT_LOCK_ENABLE                                                                                (1U)

#define IPU_MAINT_UNLOCK_SHIFT                                                                              (2U)
#define IPU_MAINT_UNLOCK_MASK                                                                               (0x00000004U)
#define IPU_MAINT_UNLOCK_DISABLE                                                                             (0U)
#define IPU_MAINT_UNLOCK_ENABLE                                                                              (1U)

#define IPU_MAINT_CLEAN_SHIFT                                                                               (3U)
#define IPU_MAINT_CLEAN_MASK                                                                                (0x00000008U)
#define IPU_MAINT_CLEAN_DISABLE                                                                              (0U)
#define IPU_MAINT_CLEAN_ENABLE                                                                               (1U)

#define IPU_MAINT_INVALIDATE_SHIFT                                                                          (4U)
#define IPU_MAINT_INVALIDATE_MASK                                                                           (0x00000010U)
#define IPU_MAINT_INVALIDATE_DISABLE                                                                         (0U)
#define IPU_MAINT_INVALIDATE_ENABLE                                                                          (1U)

#define IPU_MAINT_HOST_INTERRUPT_SHIFT                                                                      (5U)
#define IPU_MAINT_HOST_INTERRUPT_MASK                                                                       (0x00000020U)
#define IPU_MAINT_HOST_INTERRUPT_NO_INT                                                                      (0U)
#define IPU_MAINT_HOST_INTERRUPT_GEN_INT                                                                     (1U)

#define IPU_MAINT_CPU_INTERRUPT_SHIFT                                                                       (6U)
#define IPU_MAINT_CPU_INTERRUPT_MASK                                                                        (0x00000040U)
#define IPU_MAINT_CPU_INTERRUPT_NO_INT                                                                       (0U)
#define IPU_MAINT_CPU_INTERRUPT_INT                                                                          (1U)

#define IPU_MAINT_L1_CACHE1_SHIFT                                                                           (7U)
#define IPU_MAINT_L1_CACHE1_MASK                                                                            (0x00000080U)
#define IPU_MAINT_L1_CACHE1_DISABLE                                                                          (0U)
#define IPU_MAINT_L1_CACHE1_PERFORM                                                                          (1U)

#define IPU_MAINT_L1_CACHE2_SHIFT                                                                           (8U)
#define IPU_MAINT_L1_CACHE2_MASK                                                                            (0x00000100U)
#define IPU_MAINT_L1_CACHE2_DISABLE                                                                          (0U)
#define IPU_MAINT_L1_CACHE2_PERFORM                                                                          (1U)

#define IPU_MAINT_L2_CACHE_SHIFT                                                                            (9U)
#define IPU_MAINT_L2_CACHE_MASK                                                                             (0x00000200U)
#define IPU_MAINT_L2_CACHE_DISABLE                                                                           (0U)
#define IPU_MAINT_L2_CACHE_PERFORM                                                                           (1U)

#define IPU_MAINT_G_FLUSH_SHIFT                                                                             (10U)
#define IPU_MAINT_G_FLUSH_MASK                                                                              (0x00000400U)
#define IPU_MAINT_G_FLUSH_DISABLE                                                                            (0U)
#define IPU_MAINT_G_FLUSH_PERFORM                                                                            (1U)

#define IPU_MAINT_RESERVED_SHIFT                                                                            (11U)
#define IPU_MAINT_RESERVED_MASK                                                                             (0xfffff800U)

#define IPU_MTSTART_BEGIN_ADDRESS_SHIFT                                                                     (0U)
#define IPU_MTSTART_BEGIN_ADDRESS_MASK                                                                      (0xffffffffU)

#define IPU_MTEND_END_ADDRESS_SHIFT                                                                         (0U)
#define IPU_MTEND_END_ADDRESS_MASK                                                                          (0xffffffffU)

#define IPU_MAINTST_STATUS_SHIFT                                                                            (0U)
#define IPU_MAINTST_STATUS_MASK                                                                             (0x00000001U)
#define IPU_MAINTST_STATUS_DONE                                                                              (0U)
#define IPU_MAINTST_STATUS_GOING                                                                             (1U)

#define IPU_MAINTST_RESERVED_SHIFT                                                                          (1U)
#define IPU_MAINTST_RESERVED_MASK                                                                           (0xfffffffeU)

#define IPU_MMUCONFIG_PRIVILEDGE_SHIFT                                                                      (1U)
#define IPU_MMUCONFIG_PRIVILEDGE_MASK                                                                       (0x00000002U)
#define IPU_MMUCONFIG_PRIVILEDGE_DISABLE                                                                     (0U)
#define IPU_MMUCONFIG_PRIVILEDGE_ENABLE                                                                      (1U)

#define IPU_MMUCONFIG_RESERVED_SHIFT                                                                        (2U)
#define IPU_MMUCONFIG_RESERVED_MASK                                                                         (0xfffffffcU)

#define IPU_MMUCONFIG_MMU_LOCK_SHIFT                                                                        (0U)
#define IPU_MMUCONFIG_MMU_LOCK_MASK                                                                         (0x00000001U)
#define IPU_MMUCONFIG_MMU_LOCK_DISABLE                                                                       (0U)
#define IPU_MMUCONFIG_MMU_LOCK_ENABLE                                                                        (1U)

#define IPU_SMALL_ADDR_ADDRESS_SHIFT                                                                        (12U)
#define IPU_SMALL_ADDR_ADDRESS_MASK                                                                         (0xfffff000U)

#define IPU_SMALL_ADDR_RESERVED_SHIFT                                                                       (0U)
#define IPU_SMALL_ADDR_RESERVED_MASK                                                                        (0x00000fffU)

#define IPU_SMALL_XLTE_RESERVED_SHIFT                                                                       (1U)
#define IPU_SMALL_XLTE_RESERVED_MASK                                                                        (0x00000ffeU)

#define IPU_SMALL_XLTE_IGNORE_SHIFT                                                                         (0U)
#define IPU_SMALL_XLTE_IGNORE_MASK                                                                          (0x00000001U)

#define IPU_SMALL_XLTE_ADDRESS_SHIFT                                                                        (12U)
#define IPU_SMALL_XLTE_ADDRESS_MASK                                                                         (0xfffff000U)

#define IPU_SMALL_POLICY_ENABLE_SHIFT                                                                       (0U)
#define IPU_SMALL_POLICY_ENABLE_MASK                                                                        (0x00000001U)
#define IPU_SMALL_POLICY_ENABLE_DISABLE                                                                      (0U)
#define IPU_SMALL_POLICY_ENABLE_ENABLE                                                                       (1U)

#define IPU_SMALL_POLICY_SIZE_SHIFT                                                                         (1U)
#define IPU_SMALL_POLICY_SIZE_MASK                                                                          (0x00000002U)
#define IPU_SMALL_POLICY_SIZE_4KB                                                                           (0U)
#define IPU_SMALL_POLICY_SIZE_16KB                                                                          (1U)

#define IPU_SMALL_POLICY_RESERVED_SHIFT                                                                     (2U)
#define IPU_SMALL_POLICY_RESERVED_MASK                                                                      (0x00000004U)
#define IPU_SMALL_POLICY_RESERVED_BIG_ENDIAN                                                                 (0U)
#define IPU_SMALL_POLICY_RESERVED_LITTLE_ENDIAN                                                              (1U)

#define IPU_SMALL_POLICY_VOLATILE_SHIFT                                                                     (3U)
#define IPU_SMALL_POLICY_VOLATILE_MASK                                                                      (0x00000008U)
#define IPU_SMALL_POLICY_VOLATILE_DISABLE                                                                    (0U)
#define IPU_SMALL_POLICY_VOLATILE_ENABLE                                                                     (1U)

#define IPU_SMALL_POLICY_EXECUTE_SHIFT                                                                      (4U)
#define IPU_SMALL_POLICY_EXECUTE_MASK                                                                       (0x00000010U)

#define IPU_SMALL_POLICY_READ_SHIFT                                                                         (5U)
#define IPU_SMALL_POLICY_READ_MASK                                                                          (0x00000020U)

#define IPU_SMALL_POLICY_PRELOAD_SHIFT                                                                      (6U)
#define IPU_SMALL_POLICY_PRELOAD_MASK                                                                       (0x00000040U)
#define IPU_SMALL_POLICY_PRELOAD_DISABLE                                                                     (0U)
#define IPU_SMALL_POLICY_PRELOAD_ENABLE                                                                      (1U)

#define IPU_SMALL_POLICY_EXCLUSION_SHIFT                                                                    (7U)
#define IPU_SMALL_POLICY_EXCLUSION_MASK                                                                     (0x00000080U)
#define IPU_SMALL_POLICY_EXCLUSION_DISABLE                                                                   (0U)
#define IPU_SMALL_POLICY_EXCLUSION_ENABLE                                                                    (1U)

#define IPU_SMALL_POLICY_L1_CACHEABLE_SHIFT                                                                 (16U)
#define IPU_SMALL_POLICY_L1_CACHEABLE_MASK                                                                  (0x00010000U)
#define IPU_SMALL_POLICY_L1_CACHEABLE_DISABLE                                                                (0U)
#define IPU_SMALL_POLICY_L1_CACHEABLE_ENABLE                                                                 (1U)

#define IPU_SMALL_POLICY_L1_POSTED_SHIFT                                                                    (17U)
#define IPU_SMALL_POLICY_L1_POSTED_MASK                                                                     (0x00020000U)
#define IPU_SMALL_POLICY_L1_POSTED_NON_POSTED                                                                (0U)
#define IPU_SMALL_POLICY_L1_POSTED_POSTED                                                                    (1U)

#define IPU_SMALL_POLICY_L1_ALLOCATE_SHIFT                                                                  (18U)
#define IPU_SMALL_POLICY_L1_ALLOCATE_MASK                                                                   (0x00040000U)
#define IPU_SMALL_POLICY_L1_ALLOCATE_NON_ALLOCATE                                                            (0U)
#define IPU_SMALL_POLICY_L1_ALLOCATE_ALLOCATE                                                                (1U)

#define IPU_SMALL_POLICY_L1_WR_POLICY_SHIFT                                                                 (19U)
#define IPU_SMALL_POLICY_L1_WR_POLICY_MASK                                                                  (0x00080000U)
#define IPU_SMALL_POLICY_L1_WR_POLICY_WT                                                                     (0U)
#define IPU_SMALL_POLICY_L1_WR_POLICY_WB                                                                     (1U)

#define IPU_SMALL_POLICY_L2_CACHEABLE_SHIFT                                                                 (20U)
#define IPU_SMALL_POLICY_L2_CACHEABLE_MASK                                                                  (0x00100000U)
#define IPU_SMALL_POLICY_L2_CACHEABLE_NON_CACHEABLE                                                          (0U)
#define IPU_SMALL_POLICY_L2_CACHEABLE_CACHEABLE                                                              (1U)

#define IPU_SMALL_POLICY_L2_POSTED_SHIFT                                                                    (21U)
#define IPU_SMALL_POLICY_L2_POSTED_MASK                                                                     (0x00200000U)
#define IPU_SMALL_POLICY_L2_POSTED_NON_POSTED                                                                (0U)
#define IPU_SMALL_POLICY_L2_POSTED_POSTED                                                                    (1U)

#define IPU_SMALL_POLICY_L2_ALLOCATE_SHIFT                                                                  (22U)
#define IPU_SMALL_POLICY_L2_ALLOCATE_MASK                                                                   (0x00400000U)
#define IPU_SMALL_POLICY_L2_ALLOCATE_NON_ALLOCATE                                                            (0U)
#define IPU_SMALL_POLICY_L2_ALLOCATE_ALLOCATE                                                                (1U)

#define IPU_SMALL_POLICY_L2_WR_POLICY_SHIFT                                                                 (23U)
#define IPU_SMALL_POLICY_L2_WR_POLICY_MASK                                                                  (0x00800000U)
#define IPU_SMALL_POLICY_L2_WR_POLICY_WT                                                                     (0U)
#define IPU_SMALL_POLICY_L2_WR_POLICY_WB                                                                     (1U)

#define IPU_SMALL_POLICY_RESERVED2_SHIFT                                                                    (24U)
#define IPU_SMALL_POLICY_RESERVED2_MASK                                                                     (0xff000000U)

#define IPU_SMALL_POLICY_RESERVED1_SHIFT                                                                    (9U)
#define IPU_SMALL_POLICY_RESERVED1_MASK                                                                     (0x0000fe00U)

#define IPU_SMALL_POLICY_COHERENCY_SHIFT                                                                    (8U)
#define IPU_SMALL_POLICY_COHERENCY_MASK                                                                     (0x00000100U)

#ifdef __cplusplus
}
#endif
#endif  /* _HW_IPU_UNICACHE_MMU_H_ */
