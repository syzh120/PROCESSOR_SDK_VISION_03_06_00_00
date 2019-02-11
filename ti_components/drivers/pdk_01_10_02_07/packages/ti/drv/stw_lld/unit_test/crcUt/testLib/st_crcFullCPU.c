/*
 *  Copyright (C) 2014 Texas Instruments Incorporated
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
 *  \file st_crcSemiCPU.c
 *
 *  \brief Common across test-cases using CRC Semi-CPU mode.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/cslr_crc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/csl/csl_crc.h>
#include <st_crc.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CRC_REFERNCE_SIGNATURE_VALUE_L      (0xEBEB19C1U)
#define CRC_REFERNCE_SIGNATURE_VALUE_H      (0xF2C2E9EEU)

#define TIMER_FREQUENCY                 (32000U)

#define ITERATIONCOUNT                  (20U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   Fetch testcase data and run the testcase.
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
void st_crcFullCPU_main(st_CRCTestcaseParams_t *testParams);

/**
 * \brief   This API to enable the clock for CRC module.
 *          Defined in st_crcCommon.c.
 *
 * \param   none.
 *
 * \retval  none.
 */
extern void CRCClockEnable(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void st_crcFullCPU_main(st_CRCTestcaseParams_t *testParams)
{
    /*      Declaration of variables      */
    uint32_t              forLoopCount, srcBuffer, crcErrorFlag;
    uint32_t              dataSize;
    uint32_t             *crcSourceMemory;
    uint32_t              timeStampBeforeDMAConfig,
                          timeStampAfterCompleteCompression;
    Float32               crcCompletionTime;
    uint32_t              crcPatterCount, crcSectorCount, crcModuleBaseAddress;
    uint32_t              crcWatchdogPreload, crcBlockPreload, crcPatternSize;
    uint32_t              crcChannelNumber;
    uint32_t              crcMode;
    crcSignature_t        crcSectorSignatureValue, refSignVal;
    crcSignatureRegAddr_t crcPSASignatureRegAddress;
    Float32               crcSemiCPUPerformance;

    /*      Initialization of variables     */
    crcErrorFlag    = 0U;
    crcSourceMemory = (uint32_t *) testParams->sourceMemory;
    srcBuffer       = testParams->sourceMemory;
    crcSectorSignatureValue.regL = 0U;
    crcSectorSignatureValue.regH = 0U;

    /*      Configure CRC parameters      */
    crcModuleBaseAddress = SOC_CRC_BASE;
    crcPatternSize       = testParams->crcConfigParams.crcPatternSize;
    crcPatterCount       = (testParams->dataSize) / crcPatternSize;
    crcSectorCount       = testParams->crcConfigParams.crcSectorCount;
    crcWatchdogPreload   = testParams->crcConfigParams.crcWatchdogPreload;
    crcBlockPreload      = testParams->crcConfigParams.crcBlockPreload;
    crcChannelNumber     = testParams->crcConfigParams.crcChannelNumber;
    crcMode = testParams->crcConfigParams.crcMode;
    /*      Enable CRC clock        */
    CRCClockEnable();
    /*      Get CRC PSA signature register address    */
    CRCGetPSASigRegAddr(crcModuleBaseAddress,
                        crcChannelNumber,
                        &crcPSASignatureRegAddress);

    dataSize = (testParams->dataSize);

    /*  Initialize source memory with reference data */
    PlatformUnlockMMR();
    if (0x4a002100U != testParams->sourceMemory)
    {
        for (forLoopCount = 0; forLoopCount < (dataSize / 4); forLoopCount++)
        {
            crcSourceMemory[forLoopCount] = forLoopCount;
        }
        UARTprintf("\nCopied reference data into memory @%x.", srcBuffer);
    }
    /*      Configure CRC channel       */
    CRCInitialize(crcModuleBaseAddress,
                  crcChannelNumber,
                  crcWatchdogPreload,
                  crcBlockPreload);

    if ((0U == testParams->crcConfigParams.crcSignHigh) &&
        (0U == testParams->crcConfigParams.crcSignLow))
    {
        UARTprintf("\nCalculating Reference CRC signature Value.");
        /* Get Reference CRC signature value first. */
        {
            /*      CRC channel RESET before initialization/configuration
             *      */
            CRCChannelReset(crcModuleBaseAddress, crcChannelNumber);
            /*      Initialize CRC channel      */
            CRCConfigure(crcModuleBaseAddress,
                         crcChannelNumber,
                         crcPatterCount,
                         crcSectorCount,
                         crcMode);

            for (forLoopCount = 0;
                 forLoopCount < (dataSize / crcPatternSize);
                 forLoopCount++)
            {
                HW_WR_REG32(crcPSASignatureRegAddress.regL,
                            crcSourceMemory[forLoopCount]);
            }
            /* Fetch CRC signature value       */
            CRCGetPSASectorSig(crcModuleBaseAddress,
                               crcChannelNumber,
                               &refSignVal);
            UARTprintf("\n CRC signature value : 0x%x%xU", refSignVal.regH,
                   refSignVal.regL);
        }
    }
    else
    {
        UARTprintf("\nUsing Pre-Defined Reference CRC signature Value.");
        refSignVal.regH = testParams->crcConfigParams.crcSignHigh;
        refSignVal.regL = testParams->crcConfigParams.crcSignLow;
    }
    /*      Get time-stamp     */
    timeStampBeforeDMAConfig = HW_RD_REG32(SOC_COUNTER_32K_BASE +
                                           COUNTER_32K_CR);
    for (forLoopCount = 0U; forLoopCount < ITERATIONCOUNT; forLoopCount++)
    {
        /*      CRC channel RESET before initialization/configuration       */
        CRCChannelReset(crcModuleBaseAddress, crcChannelNumber);
        /*      Initialize CRC channel      */
        CRCConfigure(crcModuleBaseAddress,
                     crcChannelNumber,
                     crcPatterCount,
                     crcSectorCount,
                     crcMode);

        for (forLoopCount = 0;
             forLoopCount < (dataSize / crcPatternSize);
             forLoopCount++)
        {
            HW_WR_REG32(crcPSASignatureRegAddress.regL,
                        crcSourceMemory[forLoopCount]);
        }

        /* Fetch CRC signature value       */
        CRCGetPSASectorSig(crcModuleBaseAddress,
                           crcChannelNumber,
                           &crcSectorSignatureValue);
        /* Compare CRC signature value against reference CRC signature*/
        if ((crcSectorSignatureValue.regH == refSignVal.regH)
            && (crcSectorSignatureValue.regL == refSignVal.regL))
        {
            /*       Sector signature matches        */
        }
        else
        {
            crcErrorFlag = 1U;
            UARTprintf("\nSector signature does not match.");
            UARTprintf("\nExpected CRC signature value : 0x%x%xU",
                   refSignVal.regH,
                   refSignVal.regL);
            UARTprintf("\nCalculated CRC signature value : 0x%08x%08xU",
                   crcSectorSignatureValue.regH,
                   crcSectorSignatureValue.regL);
            break;
        }
    }
    /*      get the time-stamp       */
    timeStampAfterCompleteCompression = HW_RD_REG32(
        SOC_COUNTER_32K_BASE + COUNTER_32K_CR);

    if (crcErrorFlag == 0U)
    {
        UARTprintf("\nCRC signature verification done successfully.");
        if (ST_TT_PERFORMANCE ==
            (testParams->testType & ST_TT_PERFORMANCE))
        {
            crcCompletionTime = ((Float32)
                                 (timeStampAfterCompleteCompression -
                                  timeStampBeforeDMAConfig))
                                / (Float32) TIMER_FREQUENCY;
            crcSemiCPUPerformance =
                (Float32) (((Float32) dataSize) / crcCompletionTime);
            crcSemiCPUPerformance = ((Float32) crcSemiCPUPerformance) *
                                    ((Float32) ITERATIONCOUNT);
            crcSemiCPUPerformance = (Float32) crcSemiCPUPerformance /
                                    (1024U * 1024U);
            UARTprintf("\nProcessed data of size %uBytes %d times in %f Seconds."
                   , testParams->dataSize, ITERATIONCOUNT,
                   crcCompletionTime);
            UARTprintf("\nCRC performance: %fMB/s", crcSemiCPUPerformance);
        }
        testParams->testResult = STW_SOK;
    }
    else
    {
        UARTprintf("\nCRC signature verification failed.");
        testParams->testResult = STW_EFAIL;
    }
//    return crcErrorFlag;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
/* None */
