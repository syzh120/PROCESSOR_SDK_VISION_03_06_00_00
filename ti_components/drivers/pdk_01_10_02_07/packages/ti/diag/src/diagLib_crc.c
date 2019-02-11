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
 * \file     diagLib_crc.c
 * \brief    This file contains CRC software test APIs.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/cslr_crc.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_timer.h>
#include <ti/diag/diagLib_crc.h>
#include <diagLib_utils.h>
#include <ti/csl/cslr_synctimer.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* Maximum pattern count defined by CRC module */
#define DIAGLIB_MAX_PATTERN_CNT     (0xFFFFU)
/* Pattern size for 64bit data */
#define DIAGLIB_CRC_PATTERN_SIZE_64_BIT     (0x08U)
/* Pattern size for 32bit data */
#define DIAGLIB_CRC_PATTERN_SIZE_32_BIT     (0x04U)
/* Golden Array of Size 128 bytes */
#define DIAGLIB_CRC_GOLDEN_ARRAY_SIZE       (0x80)
/* Pre-determined CRC values for 64-bit data #DiagLib_CrcGoldenArray array */
#define DIAGLIB_CRC_64BIT_GOLDEN_REG_L            (0xA02B20BEU)
#define DIAGLIB_CRC_64BIT_GOLDEN_REG_H            (0x514AF471U)
/* Pre-determined CRC values for 32-bit data #DiagLib_CrcGoldenArray array */
#define DIAGLIB_CRC_32BIT_GOLDEN_REG_L            (0x8E09E086U)
#define DIAGLIB_CRC_32BIT_GOLDEN_REG_H            (0x52FE7B0BU)
/* ========================================================================== */
/*                         Global Variables Declarations                      */
/* ========================================================================== */
static const uint32_t DiagLib_CrcGoldenArray [DIAGLIB_CRC_GOLDEN_ARRAY_SIZE] =
{
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2A, 0x2B, 0x2C, 0x2D, 0x2E, 0x2F,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3A, 0x3B, 0x3C, 0x3D, 0x3E, 0x3F,
    0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
    0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F,
    0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
    0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E, 0x5F,
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E, 0x6F,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E, 0x7F
};

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
static int32_t DiagLib_crcChkParams(const DiagLib_CrcTestParams_t *testParams);
static uint64_t DiagLib_crcCmodel(uint64_t crc, uint64_t data);
static int32_t DiagLib_crcComputeSemiCPU(const DiagLib_CrcTestParams_t *testParams,
                DiagLib_CrcOutParams_t *outParams, DiagLib_CrcObj_t *crcObj);
static int32_t DiagLib_crcComputeFullCPU(const DiagLib_CrcTestParams_t *testParams,
                DiagLib_CrcOutParams_t *outParams, DiagLib_CrcObj_t *crcObj);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void DiagLibCrcTestParams_init(DiagLib_CrcTestParams_t *testParams)
{
    if (NULL != testParams)
    {
        testParams->baseAddr = SOC_CRC_BASE;
        testParams->mode = CRC_OPERATION_MODE_FULLCPU;
        testParams->chNumber = CRC_CHANNEL_1;
        testParams->dataSize = 0U;
        testParams->testData = NULL;
        testParams->testType = DIAGLIB_CRC_TEST_INBUILT;
        testParams->bitSize = DIAGLIB_CRC_BIT_32;
        testParams->crcCheckMode = DIAGLIB_CRC_POLLED_MODE;
        testParams->timeout      = DIAGLIB_UTILS_DEFAULT_TIMEOUT;
        testParams->crcEdmaChNum = 0U;
        testParams->crcEdmaEvtqNum = 0U;
        testParams->crcEdmaTccNum = 0U;
    }

}

int32_t DiagLib_crcStartTest(const DiagLib_CrcTestParams_t *testParams,
            DiagLib_CrcOutParams_t *outParams,  DiagLib_CrcObj_t *crcObj)
{
    int32_t status = STW_SOK;

    status = DiagLib_crcChkParams(testParams);

    if(status == STW_SOK)
    {
        if (testParams->testType == DIAGLIB_CRC_TEST_INBUILT)
        {
            if(testParams->bitSize == DIAGLIB_CRC_BIT_64)
            {
                crcObj->crcSW_l = DIAGLIB_CRC_64BIT_GOLDEN_REG_L;
                crcObj->crcSW_h = DIAGLIB_CRC_64BIT_GOLDEN_REG_H;
            }
            else
            {
                crcObj->crcSW_l = DIAGLIB_CRC_32BIT_GOLDEN_REG_L;
                crcObj->crcSW_h = DIAGLIB_CRC_32BIT_GOLDEN_REG_H;
            }
        }
        else if (testParams->testType == DIAGLIB_CRC_TEST_USER)
        {
            status = DiagLib_crcCalculateSW(testParams, outParams, crcObj);
            if(status == STW_SOK)
            {
                crcObj->crcSW_l = outParams->crcData.regL;
                crcObj->crcSW_h = outParams->crcData.regH;

            }
        }
        else
        {
            status = STW_EINVALID_PARAMS;
        }
    }

    if(status == STW_SOK)
    {
        status = DiagLib_crcCalculateHW(testParams, outParams, crcObj);

        if((testParams->mode == CRC_OPERATION_MODE_FULLCPU) ||
            (testParams->crcCheckMode == DIAGLIB_CRC_POLLED_MODE))
        {
            if(status == STW_SOK)
            {
                if((outParams->crcData.regL == crcObj->crcSW_l) &&
                (outParams->crcData.regH == crcObj->crcSW_h))
                {
                    crcObj->testState = DIAGLIB_CRC_TEST_PASS;
                }
                else
                {
                    crcObj->testState = DIAGLIB_CRC_TEST_FAIL;
                }
                status = crcObj->testState;
            }
            else
            {
                status = DIAGLIB_CRC_TEST_FAIL;
            }
        }
        else
        {
            status = crcObj->testState;
        }
    }
    else
    {
        crcObj->testState = status;
    }

    return status;
}

int32_t DiagLib_crcCalculateSW(const DiagLib_CrcTestParams_t *testParams,
            DiagLib_CrcOutParams_t *outParams,  DiagLib_CrcObj_t *crcObj)
{
    int32_t status = STW_SOK;
    uint64_t crcV = 0U, data = 0U;
    uint32_t i;

    status = DiagLib_crcChkParams(testParams);

    outParams->crcData.regL = 0U;
    outParams->crcData.regH = 0U;

    if(status == STW_SOK)
    {
        if(testParams->bitSize == DIAGLIB_CRC_BIT_64)
        {
            for (i = 0U; i < (testParams->dataSize / 4U); i = i+2U)
            {
                data = (uint64_t)testParams->testData[i+1U];
                data = (data << 32U) | testParams->testData[i];
                crcV = DiagLib_crcCmodel(crcV, data);
            }
        }
        else
        {
            for (i = 0U; i < (testParams->dataSize / 4U); i++)
            {
                data = (uint64_t)testParams->testData[i];
                crcV = DiagLib_crcCmodel(crcV, data);
            }
        }

        outParams->crcData.regL = crcV &  0xFFFFFFFFU;
        outParams->crcData.regH = (crcV >> 32U) & 0xFFFFFFFFU;
    }

    return status;
}

int32_t DiagLib_crcCalculateHW(const DiagLib_CrcTestParams_t *testParams,
                DiagLib_CrcOutParams_t *outParams, DiagLib_CrcObj_t *crcObj)
{

    int32_t status = STW_SOK;

    status = DiagLib_crcChkParams(testParams);

    if(status == STW_SOK)
    {
        /* Initialize CRC signature value to zero */
        outParams->crcData.regL = 0U;
        outParams->crcData.regH = 0U;

        if (testParams->testType == DIAGLIB_CRC_TEST_INBUILT)
        {
            crcObj->remDataSize = DIAGLIB_CRC_GOLDEN_ARRAY_SIZE;
            crcObj->curSrcAddr = DiagLib_CrcGoldenArray;
        }
        else
        {
            /* Set the remaining data size as original data size */
            crcObj->remDataSize = testParams->dataSize;

            /* Set the current data address as original data address */
            crcObj->curSrcAddr = testParams->testData;
        }

        /* CRC channel RESET before initialization/configuration */
        CRCChannelReset(testParams->baseAddr, testParams->chNumber);

        if(testParams->mode == CRC_OPERATION_MODE_FULLCPU)
        {
            status = DiagLib_crcComputeFullCPU(testParams, outParams, crcObj);
        }
        else
        {
            /* Enable CRC interrupt for compression complete */
            if(testParams->crcCheckMode == DIAGLIB_CRC_INTERRUPT_MODE)
            {
                CRCEnableIntr(testParams->baseAddr, testParams->chNumber,
                                                CRC_INTS_CH1_CCITENS_MASK);
                status = DiagLib_crcComputeSemiCPU(testParams,
                                                    outParams, crcObj);
            }
            else
            {
                do
                {
                    status = DiagLib_crcComputeSemiCPU(testParams, outParams,
                                                                    crcObj);
                }
                while((crcObj->remDataSize != 0U) && (status != STW_ETIMEOUT));

            }
            status = crcObj->testState;
        }
    }

    return status;
}

int32_t DiagLib_crcISR(const DiagLib_CrcTestParams_t *testParams,
        DiagLib_CrcOutParams_t *outParams, DiagLib_CrcObj_t *crcObj)
{

    int32_t status = STW_SOK;
    crcSignature_t sectSignVal;
    sectSignVal.regL = 0U;
    sectSignVal.regH = 0U;
    uint32_t intrMask;

    intrMask = (uint32_t) 0x1U << (0x8U *  (testParams->chNumber - 0x1U));

    if ((CRCGetIntrStatus(testParams->baseAddr, testParams->chNumber) &
                                            intrMask) == (uint32_t)0x0U)
    {
         crcObj->testState = DIAGLIB_CRC_TEST_FAIL;
         status =  crcObj->testState;
    }

    if (STW_SOK == status)
    {
        /* Clear Interrupt Status */
        CRCClearIntr(testParams->baseAddr, testParams->chNumber,
                                CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);

        /* Fetch CRC signature value */
        CRCGetPSASectorSig(testParams->baseAddr, testParams->chNumber,
                                                            &sectSignVal);

        outParams->crcData.regL = sectSignVal.regL;
        outParams->crcData.regH = sectSignVal.regH;

        if (crcObj->remDataSize != 0U)
        {
            status = DiagLib_crcComputeSemiCPU(testParams, outParams, crcObj);
        }
        else
        {
            status = DIAGLIB_CRC_TEST_PASS;
        }
    }

    if(status == STW_SOK)
    {
        if ((testParams->testType == DIAGLIB_CRC_TEST_INBUILT) ||
                (testParams->testType == DIAGLIB_CRC_TEST_USER))
        {
            if((outParams->crcData.regL == crcObj->crcSW_l) &&
                (outParams->crcData.regH == crcObj->crcSW_h))
            {
                status = DIAGLIB_CRC_TEST_PASS;
            }
            else
            {
                status = DIAGLIB_CRC_TEST_FAIL;
            }
        }
    }

    crcObj->testState = status;
    return status;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static int32_t DiagLib_crcChkParams(const DiagLib_CrcTestParams_t *testParams)
{
    int32_t status = STW_SOK;

    if (testParams->testType != DIAGLIB_CRC_TEST_INBUILT)
    {
        if((testParams->testData == NULL) || (testParams->dataSize == 0U))
        {
            status = STW_EINVALID_PARAMS;
        }
    }

    if (testParams->bitSize == DIAGLIB_CRC_BIT_64)
    {
        if((testParams->dataSize % DIAGLIB_CRC_PATTERN_SIZE_64_BIT) != 0U)
        {
            status = STW_EINVALID_PARAMS;
        }
        if (testParams->mode == CRC_OPERATION_MODE_FULLCPU)
        {
            status = STW_EINVALID_PARAMS;
        }
    }
    if (testParams->bitSize == DIAGLIB_CRC_BIT_32)
    {
        if((testParams->dataSize % DIAGLIB_CRC_PATTERN_SIZE_32_BIT) != 0U)
        {
            status = STW_EINVALID_PARAMS;
        }
    }
    return status;
}

static uint64_t DiagLib_crcCmodel(uint64_t crc, uint64_t data)
{
    uint32_t  i, j;
    uint64_t nextCrc = 0;

    for (i = 63U; (int32_t)i >= 0; i--)
    {
        nextCrc =
            (nextCrc &
             (uint64_t) 0xfffffffffffffffeU) | ((crc >> 63) ^ (data >> i));

        for (j = 1U; j < 64U; j++)
        {
            if ((j == 1U) || (j == 3U) || (j == 4U))
            {
                nextCrc =
                    (nextCrc & ~((uint64_t) 1 << j)) |
                    ((((crc >> (j - 1U)) ^ (crc >> 63U) ^ (data >> i)) & 1U) << j);
            }
            else
            {
                nextCrc =
                    (nextCrc &
                     ~((uint64_t) 1U << j)) | (((crc >> (j - 1U)) & 1U) << j);
            }
        }
        crc = nextCrc;
    }

    return crc;
}

static int32_t DiagLib_crcComputeSemiCPU(const DiagLib_CrcTestParams_t *testParams,
                DiagLib_CrcOutParams_t *outParams, DiagLib_CrcObj_t *crcObj)
{
    int32_t status = STW_SOK;
    uint32_t patternSize, patternCnt, sectCnt;
    uint32_t edmaEvtqNumber, edmaTCCNumber, edmaChannelNumber;
    uint32_t srcAddr;
    uint32_t timeStart, elapsedTime = 0U;
    uint32_t loopCount;
    uint32_t intrMask;
    EDMA3CCPaRAMEntry edmaParam;
    crcSignatureRegAddr_t psaSignRegAddr;
    crcSignature_t sectSignVal;

    sectSignVal.regL = 0U;
    sectSignVal.regH = 0U;

    crcObj->testState = DIAGLIB_CRC_TEST_PENDING;

    /* Bit width to be written into CRC regsiter */
    if(testParams->bitSize == DIAGLIB_CRC_BIT_64)
    {
        patternSize = DIAGLIB_CRC_PATTERN_SIZE_64_BIT;
    }
    else
    {
        patternSize = DIAGLIB_CRC_PATTERN_SIZE_32_BIT;
    }
    /* Number of sectors is set to 1 */
    sectCnt = 1U;

    /* Total Number of arrays in a frame */
    patternCnt = crcObj->remDataSize / patternSize;

    srcAddr = (uint32_t)crcObj->curSrcAddr;

    if(testParams->bitSize == DIAGLIB_CRC_BIT_64)
    {
        if(patternCnt > DIAGLIB_MAX_PATTERN_CNT)
        {
            patternCnt = DIAGLIB_MAX_PATTERN_CNT;
            crcObj->remDataSize -=
                patternCnt * DIAGLIB_CRC_PATTERN_SIZE_64_BIT;
            crcObj->curSrcAddr += (patternCnt *
                (DIAGLIB_CRC_PATTERN_SIZE_64_BIT / sizeof(crcObj->curSrcAddr)));
        }
        else
        {
            crcObj->remDataSize = 0U;
        }
    }
    else
    {
        crcObj->remDataSize = 0U;
    }

    /* Get CRC PSA signature register address */
    CRCGetPSASigRegAddr(testParams->baseAddr,
                        testParams->chNumber,
                        &psaSignRegAddr);

    if(testParams->bitSize == DIAGLIB_CRC_BIT_64)
    {
        /* Configure EDMA parameters */
        edmaChannelNumber  = testParams->crcEdmaChNum;
        edmaEvtqNumber     = testParams->crcEdmaEvtqNum;
        edmaTCCNumber      = testParams->crcEdmaTccNum;
        edmaParam.opt      = 0U;
        edmaParam.srcAddr  = srcAddr;
        edmaParam.destAddr = psaSignRegAddr.regL;
        edmaParam.aCnt     = patternSize;
        edmaParam.bCnt     = patternCnt;
        edmaParam.cCnt     = 1U;
        edmaParam.srcBIdx  = patternSize;
        edmaParam.destBIdx = 0U;
        edmaParam.srcCIdx  = 0U;
        edmaParam.destCIdx = 0U;
        edmaParam.linkAddr = 0xFFFFU;
        edmaParam.opt     |=
            EDMA_TPCC_OPT_SYNCDIM_MASK |
            ((edmaTCCNumber << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK);

        /* Configure EDMA */
        EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                            EDMA3_CHANNEL_TYPE_DMA,
                            edmaChannelNumber,
                            edmaTCCNumber,
                            edmaEvtqNumber);
    }

    /* Set CRC signature Seed value to Zero */
    CRCSetPSASeedSig(testParams->baseAddr, testParams->chNumber, &outParams->crcData);

    /* Initialize CRC channel */
    CRCInitialize(testParams->baseAddr,
                  testParams->chNumber,
                  0x0U, 0x0U);


    /* Configure CRC channel */
    CRCConfigure(testParams->baseAddr, testParams->chNumber, patternCnt,
                                                sectCnt, testParams->mode);

    if(testParams->bitSize == DIAGLIB_CRC_BIT_64)
    {
        /* Set EDMA parameters and start transfer */
        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumber, &edmaParam);

        EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumber, EDMA3_TRIG_MODE_MANUAL);
    }
    else
    {
        for (loopCount = 0; loopCount < patternCnt; loopCount++)
        {
            HW_WR_REG32(psaSignRegAddr.regL, crcObj->curSrcAddr[loopCount]);
        }

    }

    if(testParams->crcCheckMode == DIAGLIB_CRC_POLLED_MODE)
    {
        timeStart = DiagLibUtils_getCurTimeInMsec();

        do
        {
            intrMask = (uint32_t) 0x1U << (0x8U *  (testParams->chNumber - 0x1U));

            if ((CRCGetIntrStatus(testParams->baseAddr, testParams->chNumber) &
                                                    intrMask) != (uint32_t)0x0U)
            {
                CRCClearIntr(testParams->baseAddr, testParams->chNumber,
                                    CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);
                /* Fetch CRC signature value */
                CRCGetPSASectorSig(testParams->baseAddr, testParams->chNumber,
                                                                &sectSignVal);

                outParams->crcData.regL = sectSignVal.regL;
                outParams->crcData.regH = sectSignVal.regH;
                break;
            }

            elapsedTime = DiagLibUtils_getElapsedTimeInMsec(timeStart);

        } while(elapsedTime <= testParams->timeout);

        if(elapsedTime > testParams->timeout)
        {
            crcObj->testState = DIAGLIB_CRC_TEST_TIMEOUT;
        }
        else
        {
            crcObj->testState = DIAGLIB_CRC_TEST_PASS;
        }
    }

    status = crcObj->testState;
    return status;
}

static int32_t DiagLib_crcComputeFullCPU
                        (const DiagLib_CrcTestParams_t *testParams,
                        DiagLib_CrcOutParams_t *outParams, DiagLib_CrcObj_t *crcObj)
{
    int32_t status = STW_SOK;
    uint32_t patternCnt, sectCnt, loopCount;
    crcSignatureRegAddr_t psaSignRegAddr;
    crcSignature_t crcSignVal;
    crcSignVal.regL = 0U;
    crcSignVal.regH = 0U;

    patternCnt = crcObj->remDataSize / DIAGLIB_CRC_PATTERN_SIZE_32_BIT;

    /* Number of sectors is set to 1 */
    sectCnt = 1U;

    /* Get CRC PSA signature register address */
    CRCGetPSASigRegAddr(testParams->baseAddr,
                        testParams->chNumber,
                        &psaSignRegAddr);

    /* Initialize CRC channel */
    CRCInitialize(testParams->baseAddr,
                  testParams->chNumber,
                  0x0U, 0x0U);
    /* Configure CRC channel */
    CRCConfigure(testParams->baseAddr, testParams->chNumber, patternCnt,
                                                sectCnt, testParams->mode);

    for (loopCount = 0; loopCount < patternCnt; loopCount++)
    {
        HW_WR_REG32(psaSignRegAddr.regL,  crcObj->curSrcAddr[loopCount]);
    }

    /* Fetch CRC signature value */
    CRCGetPSASectorSig(testParams->baseAddr, testParams->chNumber, &crcSignVal);

    outParams->crcData.regL = crcSignVal.regL;
    outParams->crcData.regH = crcSignVal.regH;

    crcObj->testState = DIAGLIB_CRC_TEST_PASS;
    status = crcObj->testState;
    return status;
}
