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
#include <ti/csl/csl_ocmc_ecc.h>
#include <ti/csl/csl_edma.h>

#include "ecc_common.h"

#ifdef __cplusplus
extern "C" {
#endif

#define OCMC_RAM_ECC_SEC_TEST                    ('1')
#define OCMC_RAM_ECC_DED_TEST                    ('2')
#define OCMC_RAM_ECC_ADDR_ERR_TEST               ('3')

#define OCMC_RAM_FULL_ECC_MODE                   ('1')
#define OCMC_RAM_BLOCK_ECC_MODE                  ('2')

/** \brief OCMC instance used */
#define OCMC_RAM_APP_INST                 (SOC_OCMC_RAM1_CFG_BASE)
#define OCMC_RAM_START_ADDR               (0x40300000)
#define OCMC_RAM_ECC_START_ADDR           (0x40311100)
#define OCMC_RAM_ECC_END_ADDR             (0x403111FF)

#define OCMC_RAM_ECC_1B_ERR_THRSH_VAL     (0x1)
#define OCMC_RAM_ECC_2B_ERR_THRSH_VAL     (0x1)
#define OCMC_RAM_ECC_ADDR_ERR_THRSH_VAL   (0x1)

#define EDMA3_CC_REGION                  (1U)

#define BUFFER_SIZE                      (16)  /*aCnt*bCnt*cCnt */

#define EDMA_APP_INST                    (SOC_EDMA_TPCC_BASE_VIRT)

#if defined (__ARM_ARCH_7A__)
#define OCMC_RAM_ECC_ERR_INT              (24U)
#define OCMC_RAM_ECC_ERR_INT_INDEX        (CSL_XBAR_INST_MPU_IRQ_24)
#elif defined (__TI_ARM_V7M4__)
#define OCMC_RAM_ECC_ERR_INT              (25U)
#define OCMC_RAM_ECC_ERR_INT_INDEX        (CSL_XBAR_INST_IPU1_IRQ_25)
#elif defined (_TMS320C6X)
#define OCMC_RAM_ECC_ERR_INT              (94U)
#define OCMC_RAM_ECC_ERR_INT_INDEX        (CSL_XBAR_INST_DSP1_IRQ_94)
#endif

void mainSubMenuOcmcRamEccTest(char *option, char *mode);

int32_t ocmcRamEccTest(void);

void isrOcmcRamSecErr();
void isrOcmcRamDedErr();
void isrOcmcRamAddrErr();

#ifdef __cplusplus
}
#endif
