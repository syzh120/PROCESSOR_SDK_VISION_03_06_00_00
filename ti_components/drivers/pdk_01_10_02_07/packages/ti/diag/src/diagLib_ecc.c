/*
 *  Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file     diagLib_ecc.c
 * \brief    This file contains ECC software test APIs.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/diag/diagLib_ecc.h>
#include <diagLib_utils.h>

#include <diagLib_eccEmif.h>
#include <diagLib_eccOcmc.h>
#if defined (SOC_TDA3XX)
#include <diagLib_eccIpu.h>
#endif
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/* ========================================================================== */
static int32_t DiagLib_eccCheckParams(const DiagLib_EccTestParams_t *testParams);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void DiagLibEccTestParams_init(DiagLib_EccTestParams_t *initParams)
{
    int32_t status = STW_SOK;
    if (NULL == initParams)
    {
        status = STW_EINVALID_PARAMS;
    }

    if (STW_SOK == status)
    {
        initParams->eccErrCheckMode = DIAGLIB_ECC_INTERRUPT_MODE;
        initParams->timeout = DIAGLIB_UTILS_DEFAULT_TIMEOUT;
        initParams->ocmcPrm.eccOcmcMode = DIAGLIB_ECC_OCMC_MODE_RAM_FULL;
        initParams->ocmcPrm.eccOcmcEdmaChNum   = 1U;
        initParams->ocmcPrm.eccOcmcEdmaEvtqNum = 0U;
        initParams->ocmcPrm.eccOcmcEdmaTccNum  = 1U;
        initParams->ocmcPrm.eccOcmcRamErrAddr  = NULL;
        initParams->emifPrm.eccEmifErrAddr     = NULL;
        initParams->ipuPrm.eccIpuRamErrAddr    = NULL;
    }
}

int32_t DiagLib_eccStartTest(const DiagLib_EccTestParams_t *testParams,
                             DiagLib_EccObj_t *eccObj)
{

    int32_t status = STW_SOK;

    status = DiagLib_eccCheckParams(testParams);
    if (status == STW_SOK)
    {
        switch(testParams->testType)
        {
            case DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_ALIGN_ADDR:
            {
                emifEccConfig(testParams->testType, eccObj);
                emifNonEccQuantaAlignAddrTest(&(testParams->emifPrm), eccObj,
                            testParams->eccErrCheckMode, testParams->timeout);
                break;
            }
            case DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_MULTIPLE_BYTE:
            {
                emifEccConfig(testParams->testType, eccObj);
                emifByteCntWRAccessNotMultEccQuantaTest(&(testParams->emifPrm),
                        eccObj, testParams->eccErrCheckMode, testParams->timeout);
                break;
            }
        #if defined (SOC_TDA2PX)
            case DIAGLIB_ECC_TEST_EMIF_SUB_QUANTA_WRITE:
            {
                emifEccConfig(testParams->testType, eccObj);
                emifEccSubQuantaWriteTest(&(testParams->emifPrm),
                        eccObj, testParams->eccErrCheckMode, testParams->timeout);
                break;
            }
        #endif
            case DIAGLIB_ECC_TEST_EMIF_SEC:
            {
                emifEccConfig(testParams->testType, eccObj);
                emifSecErrTest(&(testParams->emifPrm), eccObj,
                                                testParams->eccErrCheckMode, testParams->timeout);
                break;
            }
            case DIAGLIB_ECC_TEST_EMIF_DED:
            {
                emifEccConfig(testParams->testType, eccObj);
                emifDedErrTest(&(testParams->emifPrm), eccObj,
                                                testParams->eccErrCheckMode);
                break;
            }
            case DIAGLIB_ECC_TEST_OCMC_SEC:
            {
                ocmcSecErrTest(&(testParams->ocmcPrm), eccObj,
                            testParams->eccErrCheckMode, testParams->timeout);
               break;
            }
            case DIAGLIB_ECC_TEST_OCMC_DED:
            {
                ocmcDedErrTest(&(testParams->ocmcPrm), eccObj,
                                                testParams->eccErrCheckMode);
                break;
            }
            case DIAGLIB_ECC_TEST_OCMC_ADDR:
            {
                ocmcAddrErrTest(&(testParams->ocmcPrm), eccObj,
                                                testParams->eccErrCheckMode);
                break;
            }
#if defined (SOC_TDA3XX)
            case DIAGLIB_ECC_TEST_IPU_L2RAM_SEC:
            {
                ipuL2RamErrTest(&(testParams->ipuPrm), eccObj,
                                testParams->eccErrCheckMode, DIAGLIB_IPU_ECC_ERR_SEC);
                break;
            }
            case DIAGLIB_ECC_TEST_IPU_L2RAM_DED:
            {
                ipuL2RamErrTest(&(testParams->ipuPrm), eccObj,
                                testParams->eccErrCheckMode, DIAGLIB_IPU_ECC_ERR_DED);
                break;
            }
            case DIAGLIB_ECC_TEST_IPU_L2RAM_CODE:
            {
                ipuL2RamErrTest(&(testParams->ipuPrm), eccObj,
                                testParams->eccErrCheckMode, DIAGLIB_IPU_ECC_ERR_CODE);
                break;
            }
            case DIAGLIB_ECC_TEST_IPU_L1DATA_SEC:
            {
                ipuL1DataErrTest(&(testParams->ipuPrm), eccObj,
                                testParams->eccErrCheckMode, DIAGLIB_IPU_ECC_ERR_SEC);
                break;
            }
            case DIAGLIB_ECC_TEST_IPU_L1DATA_DED:
            {
                ipuL1DataErrTest(&(testParams->ipuPrm), eccObj,
                                testParams->eccErrCheckMode, DIAGLIB_IPU_ECC_ERR_DED);
                break;
            }
            case DIAGLIB_ECC_TEST_IPU_L1DATA_CODE:
            {
                ipuL1DataErrTest(&(testParams->ipuPrm), eccObj,
                                testParams->eccErrCheckMode, DIAGLIB_IPU_ECC_ERR_CODE);
                break;
            }
            case DIAGLIB_ECC_TEST_IPU_L1TAG_SEC:
            {
                ipuL1TagErrTest(&(testParams->ipuPrm), eccObj,
                                testParams->eccErrCheckMode, DIAGLIB_IPU_ECC_ERR_SEC);
                break;
            }
            case DIAGLIB_ECC_TEST_IPU_L1TAG_DED:
            {
                ipuL1TagErrTest(&(testParams->ipuPrm), eccObj,
                                testParams->eccErrCheckMode, DIAGLIB_IPU_ECC_ERR_DED);
                break;
            }
            case DIAGLIB_ECC_TEST_IPU_L1TAG_CODE:
            {
                ipuL1TagErrTest(&(testParams->ipuPrm), eccObj,
                                testParams->eccErrCheckMode, DIAGLIB_IPU_ECC_ERR_CODE);
                break;
            }
#endif
            default:
            {
                eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
                break;
            }
        }
        status = eccObj->testState;
    }
    return status;
}

int32_t DiagLib_eccISR(const DiagLib_EccTestParams_t *testParams,
                            DiagLib_EccObj_t *eccObj)
{
    switch(testParams->testType)
    {
        case DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_ALIGN_ADDR:
        case DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_MULTIPLE_BYTE:
        case DIAGLIB_ECC_TEST_EMIF_SUB_QUANTA_WRITE:
        {
            emifNonEccQuantaAddrISR(&(testParams->emifPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_EMIF_SEC:
        {
            emifSecISR(&(testParams->emifPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_EMIF_DED:
        {
            emifDedISR(&(testParams->emifPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_OCMC_SEC:
        {
            ocmcSecISR(&(testParams->ocmcPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_OCMC_DED:
        {
            ocmcDedISR(&(testParams->ocmcPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_OCMC_ADDR:
        {
            ocmcAddrISR(&(testParams->ocmcPrm), eccObj);
            break;
        }
#if defined (SOC_TDA3XX)
        case DIAGLIB_ECC_TEST_IPU_L2RAM_SEC:
        {
            ipuL2RamSecErrISR(&(testParams->ipuPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_IPU_L2RAM_DED:
        {
            ipuL2RamDedErrISR(&(testParams->ipuPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_IPU_L2RAM_CODE:
        {
            ipuL2RamCodeErrISR(&(testParams->ipuPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_IPU_L1DATA_SEC:
        case DIAGLIB_ECC_TEST_IPU_L1DATA_CODE:
        {
            ipuL1DataSecOrCodeErrISR(&(testParams->ipuPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_IPU_L1DATA_DED:
        {
            ipuL1DataDedErrISR(&(testParams->ipuPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_IPU_L1TAG_SEC:
        case DIAGLIB_ECC_TEST_IPU_L1TAG_CODE:
        {
            ipuL1TagSecOrCodeErrISR(&(testParams->ipuPrm), eccObj);
            break;
        }
        case DIAGLIB_ECC_TEST_IPU_L1TAG_DED:
        {
            ipuL1TagDedErrISR(&(testParams->ipuPrm), eccObj);
            break;
        }
#endif
        default:
        {
            eccObj->testState = DIAGLIB_ECC_TEST_FAIL;
            break;
        }
    }
    return eccObj->testState;

}
/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static int32_t DiagLib_eccCheckParams(const DiagLib_EccTestParams_t *testParams)
{
    int32_t status = STW_SOK;

    if ((testParams->testType == 0U) || (testParams->testType >= DIAGLIB_ECC_TEST_MAX))
    {
        status = STW_EINVALID_PARAMS;
    }
    if ((testParams->eccErrCheckMode != DIAGLIB_ECC_POLLED_MODE)
            && (testParams->eccErrCheckMode != DIAGLIB_ECC_INTERRUPT_MODE))
    {
        status = STW_EINVALID_PARAMS;
    }

    /* EMIF DED Error, OCMC DED, ADDR errors and IPU ECC errors result in
     * hard fault.
     * Therefore they cannot be tested in polled mode.
     */
    if (testParams->eccErrCheckMode == DIAGLIB_ECC_POLLED_MODE)
    {
        if ((testParams->testType == DIAGLIB_ECC_TEST_EMIF_DED) ||
                (testParams->testType == DIAGLIB_ECC_TEST_OCMC_DED) ||
                (testParams->testType == DIAGLIB_ECC_TEST_OCMC_ADDR) ||
                (testParams->testType == DIAGLIB_ECC_TEST_IPU_L2RAM_SEC) ||
                (testParams->testType == DIAGLIB_ECC_TEST_IPU_L2RAM_DED) ||
                (testParams->testType == DIAGLIB_ECC_TEST_IPU_L2RAM_CODE) ||
                (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1DATA_SEC) ||
                (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1DATA_DED) ||
                (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1DATA_CODE) ||
                (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1TAG_SEC) ||
                (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1TAG_DED) ||
                (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1TAG_CODE))
        {
            status = STW_EINVALID_PARAMS;
        }
    }

    /* Check for error addresses being set for respective module tests */
    if ((testParams->testType == DIAGLIB_ECC_TEST_EMIF_DED) ||
            (testParams->testType == DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_ALIGN_ADDR) ||
            (testParams->testType == DIAGLIB_ECC_TEST_EMIF_NON_QUANTA_MULTIPLE_BYTE) ||
            (testParams->testType == DIAGLIB_ECC_TEST_EMIF_SUB_QUANTA_WRITE) ||
            (testParams->testType == DIAGLIB_ECC_TEST_EMIF_SEC))
    {
        if (testParams->emifPrm.eccEmifErrAddr == NULL)
        {
            status = STW_EINVALID_PARAMS;
        }
    }

    if ((testParams->testType == DIAGLIB_ECC_TEST_OCMC_SEC) ||
            (testParams->testType == DIAGLIB_ECC_TEST_OCMC_DED) ||
            (testParams->testType == DIAGLIB_ECC_TEST_OCMC_ADDR))
    {
        if (testParams->ocmcPrm.eccOcmcRamErrAddr == NULL)
        {
            status = STW_EINVALID_PARAMS;
        }
        if((testParams->ocmcPrm.eccOcmcMode != DIAGLIB_ECC_OCMC_MODE_RAM_FULL)
            && (testParams->ocmcPrm.eccOcmcMode
                    != DIAGLIB_ECC_OCMC_MODE_RAM_BLOCK))
        {
            status = STW_EINVALID_PARAMS;
        }
    }

    if ((testParams->testType == DIAGLIB_ECC_TEST_IPU_L2RAM_SEC) ||
            (testParams->testType == DIAGLIB_ECC_TEST_IPU_L2RAM_DED) ||
            (testParams->testType == DIAGLIB_ECC_TEST_IPU_L2RAM_CODE) ||
            (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1DATA_SEC) ||
            (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1DATA_DED) ||
            (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1DATA_CODE) ||
            (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1TAG_SEC) ||
            (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1TAG_DED) ||
            (testParams->testType == DIAGLIB_ECC_TEST_IPU_L1TAG_CODE))
    {
        if (testParams->ipuPrm.eccIpuRamErrAddr == NULL)
        {
            status = STW_EINVALID_PARAMS;
        }
    }
    return status;
}
