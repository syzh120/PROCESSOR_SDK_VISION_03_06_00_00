/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2017 - 2018
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
#include <ti/csl/csl_emif.h>

#include "ecc_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define EMIF_ECC_NON_QUANTA_ALIGN_ADDR_ERR_TEST                          ('1')
#define EMIF_ECC_BYTECOUNT_WRITEACCESS_NOTMULTIPLE_ECCQUANTA_ERR_TEST    ('2')
#define EMIF_ECC_SEC_ERR_TEST                                            ('3')
#define EMIF_ECC_DED_ERR_TEST                                            ('4')

/** \brief EMIF instance used */
#define EMIF_APP_INST                     (SOC_EMIF1_CONF_REGS_BASE)
#define EMIF_START_ADDR                   (0x80000000)
#define EMIF_ECC_START_ADDR               (0x90000000)
#define EMIF_ECC_END_ADDR                 (0x9001FFFF)
/** \brief As Err address log FIFO size is 4 so EMIF_ECC_1B_ERR_THRSH_VAL is set
 *         as 2 to avoid missing of Err address log
 */
#define EMIF_ECC_1B_ERR_THRSH_VAL         (0x2)

#define EMIF_ECC_TEST_ADDR                (EMIF_ECC_START_ADDR + 0x100)
#define EMIF_ECC_TEST_ADDR_1              (EMIF_ECC_START_ADDR + 0x200)
#define EMIF_ECC_TEST_ADDR_2              (EMIF_ECC_START_ADDR + 0x3)

#if defined (__ARM_ARCH_7A__)
#define EMIF_ECC_ERR_INT                  (13U)
#define EMIF_ECC_ERR_INT_INDEX            (CSL_XBAR_INST_MPU_IRQ_13)
#elif defined (__TI_ARM_V7M4__)
#define EMIF_ECC_ERR_INT                  (35U)
#define EMIF_ECC_ERR_INT_INDEX            (CSL_XBAR_INST_IPU1_IRQ_35)
#elif defined (_TMS320C6X)
#define EMIF_ECC_ERR_INT                  (93U)
#define EMIF_ECC_ERR_INT_INDEX            (CSL_XBAR_INST_DSP1_IRQ_93)
#endif

void mainSubMenuEmifEccTest(char *option);
int32_t emifEccTest(void);

void isrEmifSecErr();
void isrEmifDedErr();
void isrEmifNonEccQuantaAlignAddrErr();
void isrEmifByteCntWRAccessNotMultEccQuantaErr();

#ifdef __cplusplus
}
#endif
