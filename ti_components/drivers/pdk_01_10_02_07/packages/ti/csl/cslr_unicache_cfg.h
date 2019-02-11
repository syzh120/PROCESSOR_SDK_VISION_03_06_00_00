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
#ifndef CSLR_UNICACHECFG_H
#define CSLR_UNICACHECFG_H

#ifdef __cplusplus
extern "C"
{
#endif
#include <ti/csl/cslr.h>
#include <ti/csl/tistdtypes.h>


/**************************************************************************
* Register Overlay Structure for __ALL__
**************************************************************************/
typedef struct {
    volatile Uint32 INFO;
    volatile Uint32 CONFIG;
    volatile Uint32 INT;
    volatile Uint32 OCP;
    volatile Uint32 MAINT;
    volatile Uint32 MTSTART;
    volatile Uint32 MTEND;
    volatile Uint32 CTADDR;
    volatile Uint32 CTDATA;
} CSL_UnicacheCfgRegs;


/**************************************************************************
* Register Macros
**************************************************************************/

/* Information Register */
#define CSL_UNICACHECFG_INFO                                    (0x0U)

/* Configuration Register */
#define CSL_UNICACHECFG_CONFIG                                  (0x4U)

/* Interrupt Register */
#define CSL_UNICACHECFG_INT                                     (0x8U)

/* Interface Configuration Register */
#define CSL_UNICACHECFG_OCP                                     (0xCU)

/* Maintenance Configuration Register */
#define CSL_UNICACHECFG_MAINT                                   (0x10U)

/* Maintenance Start Configuration Register */
#define CSL_UNICACHECFG_MTSTART                                 (0x14U)

/* Maintenance End Configuration Register */
#define CSL_UNICACHECFG_MTEND                                   (0x18U)

/* Cache Test Address Register */
#define CSL_UNICACHECFG_CTADDR                                  (0x1CU)

/* Cache Test Data Register */
#define CSL_UNICACHECFG_CTDATA                                  (0x20U)


/**************************************************************************
* Field Definition Macros
**************************************************************************/

/* INFO */

#define CSL_UNICACHECFG_INFO_VERSION_MASK                       (0x0000000FU)
#define CSL_UNICACHECFG_INFO_VERSION_SHIFT                      (0U)
#define CSL_UNICACHECFG_INFO_VERSION_RESETVAL                   (0x00000001U)
#define CSL_UNICACHECFG_INFO_VERSION_MAX                        (0x0000000fU)

#define CSL_UNICACHECFG_INFO_WAYS_MASK                          (0x00000030U)
#define CSL_UNICACHECFG_INFO_WAYS_SHIFT                         (4U)
#define CSL_UNICACHECFG_INFO_WAYS_RESETVAL                      (0x00000001U)
#define CSL_UNICACHECFG_INFO_WAYS__2WAY                         (0x00000000U)
#define CSL_UNICACHECFG_INFO_WAYS__4WAY                         (0x00000001U)
#define CSL_UNICACHECFG_INFO_WAYS__8WAY                         (0x00000002U)
#define CSL_UNICACHECFG_INFO_WAYS_RESERVED                      (0x00000003U)

#define CSL_UNICACHECFG_INFO_SIZE_MASK                          (0x0000FFC0U)
#define CSL_UNICACHECFG_INFO_SIZE_SHIFT                         (6U)
#define CSL_UNICACHECFG_INFO_SIZE_RESETVAL                      (0x00000020U)
#define CSL_UNICACHECFG_INFO_SIZE_MAX                           (0x000003ffU)

#define CSL_UNICACHECFG_INFO_SLAVES_MASK                        (0x00070000U)
#define CSL_UNICACHECFG_INFO_SLAVES_SHIFT                       (16U)
#define CSL_UNICACHECFG_INFO_SLAVES_RESETVAL                    (0x00000002U)
#define CSL_UNICACHECFG_INFO_SLAVES_MAX                         (0x00000007U)

#define CSL_UNICACHECFG_INFO_MASTERS_MASK                       (0x00180000U)
#define CSL_UNICACHECFG_INFO_MASTERS_SHIFT                      (19U)
#define CSL_UNICACHECFG_INFO_MASTERS_RESETVAL                   (0x00000001U)
#define CSL_UNICACHECFG_INFO_MASTERS_MAX                        (0x00000003U)

#define CSL_UNICACHECFG_INFO_RESETVAL                           (0x000a0811U)

/* CONFIG */

#define CSL_UNICACHECFG_CONFIG_SECURE_MASK                      (0x00000001U)
#define CSL_UNICACHECFG_CONFIG_SECURE_SHIFT                     (0U)
#define CSL_UNICACHECFG_CONFIG_SECURE_RESETVAL                  (0x00000000U)
#define CSL_UNICACHECFG_CONFIG_SECURE_NON_SECURE                (0x00000000U)
#define CSL_UNICACHECFG_CONFIG_SECURE_SECURE                    (0x00000001U)

#define CSL_UNICACHECFG_CONFIG_BYPASS_MASK                      (0x00000002U)
#define CSL_UNICACHECFG_CONFIG_BYPASS_SHIFT                     (1U)
#define CSL_UNICACHECFG_CONFIG_BYPASS_RESETVAL                  (0x00000000U)
#define CSL_UNICACHECFG_CONFIG_BYPASS_BYPASS                    (0x00000000U)
#define CSL_UNICACHECFG_CONFIG_BYPASS_NORMAL                    (0x00000001U)

#define CSL_UNICACHECFG_CONFIG_SECINT_MASK                      (0x00000004U)
#define CSL_UNICACHECFG_CONFIG_SECINT_SHIFT                     (2U)
#define CSL_UNICACHECFG_CONFIG_SECINT_RESETVAL                  (0x00000001U)
#define CSL_UNICACHECFG_CONFIG_SECINT_SECURE                    (0x00000000U)
#define CSL_UNICACHECFG_CONFIG_SECINT_NON_SECURE                (0x00000001U)

#define CSL_UNICACHECFG_CONFIG_SECPORT_MASK                     (0x00000008U)
#define CSL_UNICACHECFG_CONFIG_SECPORT_SHIFT                    (3U)
#define CSL_UNICACHECFG_CONFIG_SECPORT_RESETVAL                 (0x00000001U)
#define CSL_UNICACHECFG_CONFIG_SECPORT_SECURE                   (0x00000000U)
#define CSL_UNICACHECFG_CONFIG_SECPORT_NON_SECURE               (0x00000001U)

#define CSL_UNICACHECFG_CONFIG_SECMAIN_MASK                     (0x00000010U)
#define CSL_UNICACHECFG_CONFIG_SECMAIN_SHIFT                    (4U)
#define CSL_UNICACHECFG_CONFIG_SECMAIN_RESETVAL                 (0x00000001U)
#define CSL_UNICACHECFG_CONFIG_SECMAIN_SECURE                   (0x00000000U)
#define CSL_UNICACHECFG_CONFIG_SECMAIN_NON_SECURE               (0x00000001U)

#define CSL_UNICACHECFG_CONFIG_RESETVAL                         (0x0000001cU)

/* INT */

#define CSL_UNICACHECFG_INT_CONFIG_MASK                         (0x00000001U)
#define CSL_UNICACHECFG_INT_CONFIG_SHIFT                        (0U)
#define CSL_UNICACHECFG_INT_CONFIG_RESETVAL                     (0x00000000U)
#define CSL_UNICACHECFG_INT_CONFIG_MAX                          (0x00000001U)

#define CSL_UNICACHECFG_INT_PAGEFAULT_MASK                      (0x00000002U)
#define CSL_UNICACHECFG_INT_PAGEFAULT_SHIFT                     (1U)
#define CSL_UNICACHECFG_INT_PAGEFAULT_RESETVAL                  (0x00000000U)
#define CSL_UNICACHECFG_INT_PAGEFAULT_MAX                       (0x00000001U)

#define CSL_UNICACHECFG_INT_MAINT_MASK                          (0x00000004U)
#define CSL_UNICACHECFG_INT_MAINT_SHIFT                         (2U)
#define CSL_UNICACHECFG_INT_MAINT_RESETVAL                      (0x00000000U)
#define CSL_UNICACHECFG_INT_MAINT_MAX                           (0x00000001U)

#define CSL_UNICACHECFG_INT_WRITE_MASK                          (0x00000008U)
#define CSL_UNICACHECFG_INT_WRITE_SHIFT                         (3U)
#define CSL_UNICACHECFG_INT_WRITE_RESETVAL                      (0x00000000U)
#define CSL_UNICACHECFG_INT_WRITE_MAX                           (0x00000001U)

#define CSL_UNICACHECFG_INT_READ_MASK                           (0x00000010U)
#define CSL_UNICACHECFG_INT_READ_SHIFT                          (4U)
#define CSL_UNICACHECFG_INT_READ_RESETVAL                       (0x00000000U)
#define CSL_UNICACHECFG_INT_READ_MAX                            (0x00000001U)

#define CSL_UNICACHECFG_INT_PORT_MASK                           (0x000001E0U)
#define CSL_UNICACHECFG_INT_PORT_SHIFT                          (5U)
#define CSL_UNICACHECFG_INT_PORT_RESETVAL                       (0x00000000U)
#define CSL_UNICACHECFG_INT_PORT_MAX                            (0x0000000fU)

#define CSL_UNICACHECFG_INT_RESETVAL                            (0x00000000U)

/* OCP */

#define CSL_UNICACHECFG_OCP_WRAP_MASK                           (0x00000001U)
#define CSL_UNICACHECFG_OCP_WRAP_SHIFT                          (0U)
#define CSL_UNICACHECFG_OCP_WRAP_RESETVAL                       (0x00000000U)
#define CSL_UNICACHECFG_OCP_WRAP_NON_WRAP                       (0x00000000U)
#define CSL_UNICACHECFG_OCP_WRAP_WRAP                           (0x00000001U)

#define CSL_UNICACHECFG_OCP_WRBUFFER_MASK                       (0x00000002U)
#define CSL_UNICACHECFG_OCP_WRBUFFER_SHIFT                      (1U)
#define CSL_UNICACHECFG_OCP_WRBUFFER_RESETVAL                   (0x00000000U)
#define CSL_UNICACHECFG_OCP_WRBUFFER_NO_BUFFERED                (0x00000000U)
#define CSL_UNICACHECFG_OCP_WRBUFFER_BUFFERED                   (0x00000001U)

#define CSL_UNICACHECFG_OCP_WRALLOCATE_MASK                     (0x00000004U)
#define CSL_UNICACHECFG_OCP_WRALLOCATE_SHIFT                    (2U)
#define CSL_UNICACHECFG_OCP_WRALLOCATE_RESETVAL                 (0x00000000U)
#define CSL_UNICACHECFG_OCP_WRALLOCATE_NO_ALLOC                 (0x00000000U)
#define CSL_UNICACHECFG_OCP_WRALLOCATE_SIDEBAND                 (0x00000001U)

#define CSL_UNICACHECFG_OCP_CACHED_MASK                         (0x00000008U)
#define CSL_UNICACHECFG_OCP_CACHED_SHIFT                        (3U)
#define CSL_UNICACHECFG_OCP_CACHED_RESETVAL                     (0x00000001U)
#define CSL_UNICACHECFG_OCP_CACHED_NO_CACHE                     (0x00000000U)
#define CSL_UNICACHECFG_OCP_CACHED_CACHE                        (0x00000001U)

#define CSL_UNICACHECFG_OCP_PREFETCH_MASK                       (0x00000010U)
#define CSL_UNICACHECFG_OCP_PREFETCH_SHIFT                      (4U)
#define CSL_UNICACHECFG_OCP_PREFETCH_RESETVAL                   (0x00000000U)
#define CSL_UNICACHECFG_OCP_PREFETCH_MMU                        (0x00000000U)
#define CSL_UNICACHECFG_OCP_PREFETCH_PREFETCH                   (0x00000001U)

#define CSL_UNICACHECFG_OCP_CLEANBUF_MASK                       (0x00000020U)
#define CSL_UNICACHECFG_OCP_CLEANBUF_SHIFT                      (5U)
#define CSL_UNICACHECFG_OCP_CLEANBUF_RESETVAL                   (0x00000000U)
#define CSL_UNICACHECFG_OCP_CLEANBUF_NO_CLEAN                   (0x00000000U)
#define CSL_UNICACHECFG_OCP_CLEANBUF_CLEAN                      (0x00000001U)

#define CSL_UNICACHECFG_OCP_RESETVAL                            (0x00000008U)

/* MAINT */

#define CSL_UNICACHECFG_MAINT_PRELOAD_MASK                      (0x00000001U)
#define CSL_UNICACHECFG_MAINT_PRELOAD_SHIFT                     (0U)
#define CSL_UNICACHECFG_MAINT_PRELOAD_RESETVAL                  (0x00000000U)
#define CSL_UNICACHECFG_MAINT_PRELOAD_DISABLE                   (0x00000000U)
#define CSL_UNICACHECFG_MAINT_PRELOAD_ENABLE                    (0x00000001U)

#define CSL_UNICACHECFG_MAINT_LOCK_MASK                         (0x00000002U)
#define CSL_UNICACHECFG_MAINT_LOCK_SHIFT                        (1U)
#define CSL_UNICACHECFG_MAINT_LOCK_RESETVAL                     (0x00000000U)
#define CSL_UNICACHECFG_MAINT_LOCK_DISABLE                      (0x00000000U)
#define CSL_UNICACHECFG_MAINT_LOCK_ENABLE                       (0x00000001U)

#define CSL_UNICACHECFG_MAINT_UNLOCK_MASK                       (0x00000004U)
#define CSL_UNICACHECFG_MAINT_UNLOCK_SHIFT                      (2U)
#define CSL_UNICACHECFG_MAINT_UNLOCK_RESETVAL                   (0x00000000U)
#define CSL_UNICACHECFG_MAINT_UNLOCK_DISABLE                    (0x00000000U)
#define CSL_UNICACHECFG_MAINT_UNLOCK_ENABLE                     (0x00000001U)

#define CSL_UNICACHECFG_MAINT_CLEAN_MASK                        (0x00000008U)
#define CSL_UNICACHECFG_MAINT_CLEAN_SHIFT                       (3U)
#define CSL_UNICACHECFG_MAINT_CLEAN_RESETVAL                    (0x00000000U)
#define CSL_UNICACHECFG_MAINT_CLEAN_DISABLE                     (0x00000000U)
#define CSL_UNICACHECFG_MAINT_CLEAN_ENABLE                      (0x00000001U)

#define CSL_UNICACHECFG_MAINT_INVALIDATE_MASK                   (0x00000010U)
#define CSL_UNICACHECFG_MAINT_INVALIDATE_SHIFT                  (4U)
#define CSL_UNICACHECFG_MAINT_INVALIDATE_RESETVAL               (0x00000000U)
#define CSL_UNICACHECFG_MAINT_INVALIDATE_DISABLE                (0x00000000U)
#define CSL_UNICACHECFG_MAINT_INVALIDATE_ENABLE                 (0x00000001U)

#define CSL_UNICACHECFG_MAINT_INTERRUPT_MASK                    (0x00000020U)
#define CSL_UNICACHECFG_MAINT_INTERRUPT_SHIFT                   (5U)
#define CSL_UNICACHECFG_MAINT_INTERRUPT_RESETVAL                (0x00000000U)
#define CSL_UNICACHECFG_MAINT_INTERRUPT_NO_INT                  (0x00000000U)
#define CSL_UNICACHECFG_MAINT_INTERRUPT_GEN_INT                 (0x00000001U)

#define CSL_UNICACHECFG_MAINT_RESETVAL                          (0x00000000U)

/* MTSTART */

#define CSL_UNICACHECFG_MTSTART_START_ADDR_MASK                 (0xFFFFFFFFU)
#define CSL_UNICACHECFG_MTSTART_START_ADDR_SHIFT                (0U)
#define CSL_UNICACHECFG_MTSTART_START_ADDR_RESETVAL             (0x00000000U)
#define CSL_UNICACHECFG_MTSTART_START_ADDR_MAX                  (0xffffffffU)

#define CSL_UNICACHECFG_MTSTART_RESETVAL                        (0x00000000U)

/* MTEND */

#define CSL_UNICACHECFG_MTEND_END_ADDR_MASK                     (0xFFFFFFFFU)
#define CSL_UNICACHECFG_MTEND_END_ADDR_SHIFT                    (0U)
#define CSL_UNICACHECFG_MTEND_END_ADDR_RESETVAL                 (0x00000000U)
#define CSL_UNICACHECFG_MTEND_END_ADDR_MAX                      (0xffffffffU)

#define CSL_UNICACHECFG_MTEND_RESETVAL                          (0x00000000U)

/* CTADDR */

#define CSL_UNICACHECFG_CTADDR_ADDRESS_MASK                     (0xFFFFFFFFU)
#define CSL_UNICACHECFG_CTADDR_ADDRESS_SHIFT                    (0U)
#define CSL_UNICACHECFG_CTADDR_ADDRESS_RESETVAL                 (0x00000000U)
#define CSL_UNICACHECFG_CTADDR_ADDRESS_MAX                      (0xffffffffU)

#define CSL_UNICACHECFG_CTADDR_RESETVAL                         (0x00000000U)

/* CTDATA */

#define CSL_UNICACHECFG_CTDATA_DATA_MASK                        (0xFFFFFFFFU)
#define CSL_UNICACHECFG_CTDATA_DATA_SHIFT                       (0U)
#define CSL_UNICACHECFG_CTDATA_DATA_RESETVAL                    (0x00000000U)
#define CSL_UNICACHECFG_CTDATA_DATA_MAX                         (0xffffffffU)

#define CSL_UNICACHECFG_CTDATA_RESETVAL                         (0x00000000U)

#ifdef __cplusplus
}
#endif
#endif
