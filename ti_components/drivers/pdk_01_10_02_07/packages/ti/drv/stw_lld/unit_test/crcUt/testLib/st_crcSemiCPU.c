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
#include <ti/csl/cslr_crc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/csl/csl_crc.h>
#include <st_crc.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define CRC_REFERNCE_SIGNATURE_VALUE_L      (0xD5D7103DU)
#define CRC_REFERNCE_SIGNATURE_VALUE_H      (0x6370D34EU)

#define TIMER_FREQUENCY                 (32000U)

#define ITERATIONCOUNT                  (20U)

/* Parameters for registering EDMA interrupt */
#define EDMA3_CC_XFER_COMPLETION_INT_M4                 (34U)
#define EDMA3_CC_XFER_COMPLETION_INT_DSP                (32U)
#define EDMA3_CC_REGION_M4                              (1U)
#define EDMA3_CC_REGION_DSP                             (1U)
#ifdef __TI_ARM_V7M4__
    #define EDMA3_CC_XFER_COMPLETION_INT    (EDMA3_CC_XFER_COMPLETION_INT_M4)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_M4)
    #define XBAR_CPU                        (CPU_IPU1)
    #define XBAR_INST                       (XBAR_INST_IPU1_IRQ_34)
    #define XBAR_INTR_SOURCE                (EDMA_TPCC_IRQ_REGION1)
#elif defined (_TMS320C6X)
    #define EDMA3_CC_XFER_COMPLETION_INT    (EDMA3_CC_XFER_COMPLETION_INT_DSP)
    #define EDMA3_CC_REGION                 (EDMA3_CC_REGION_DSP)
    #define SOC_EMIF1_BASE                  (0x80000000U)
    #define XBAR_CPU                        (CPU_DSP1)
    #define XBAR_INST                       (XBAR_INST_DSP1_IRQ_32)
    #define XBAR_INTR_SOURCE                (EDMA_TPCC_IRQ_REGION1)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t edmaTransferComplete;
uint32_t          edmaEvtqNumber, edmaTCCNumber, edmaChannelNumber,
                  edmaInterruptNumber;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This Interrupt Service Routine for EDMA completion interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
void isrEdmaCompletion(void *handle);

/**
 * \brief   Fetch testcase data and run the testcase.
 *
 * \param   testParams        structure to details of testcase to run.
 *
 * \return  None
 */
void st_crcSemiCPU_main(st_CRCTestcaseParams_t *testParams);

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
void st_crcSemiCPU_main(st_CRCTestcaseParams_t *testParams)
{
    /*      Declaration of variables      */
    uint32_t              forLoopCount, loopBreakFlag, srcBuffer, edmaRegion,
                          crcErrorFlag;
    cpu_id_t              xbarCPU;
    uint32_t              transferLoopCount, dataSize, edmaCCnt;
    uint32_t             *crcSourceMemory;
    uint32_t              timeStampBeforeDMAConfig,
                          timeStampAfterCompleteCompression;
    Float32               crcCompletionTime;
    EDMA3CCPaRAMEntry     edmaParam;
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

    if (DSP1 == testParams->cpuID)
    {
        xbarCPU = CPU_DSP1;
    }
    else if (DSP2 == testParams->cpuID)
    {
        xbarCPU = CPU_DSP2;
    }
    else
    {
        xbarCPU = CPU_IPU1;
    }
    /*      Configure CRC parameters      */
    crcModuleBaseAddress = SOC_CRC_BASE;
    crcPatternSize       = testParams->crcConfigParams.crcPatternSize;
    crcPatterCount       = (testParams->dataSize) /
                           (testParams->crcConfigParams.crcPatternSize);
    crcSectorCount     = testParams->crcConfigParams.crcSectorCount;
    crcWatchdogPreload = testParams->crcConfigParams.crcWatchdogPreload;
    crcBlockPreload    = testParams->crcConfigParams.crcBlockPreload;
    crcChannelNumber   = testParams->crcConfigParams.crcChannelNumber;
    crcMode = testParams->crcConfigParams.crcMode;
    /*      Enable CRC clock        */
    CRCClockEnable();
    /*      Get CRC PSA signature register address    */
    CRCGetPSASigRegAddr(crcModuleBaseAddress,
                        crcChannelNumber,
                        &crcPSASignatureRegAddress);

    dataSize = (testParams->dataSize);

    edmaRegion = EDMA3_CC_REGION;
    EDMAsetRegion(edmaRegion);
    /*      Do EDMA init Done once in the beginning of application      */
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);
    /*      Enable EDAM completion interrupt     */
    edmaInterruptNumber = EDMA3_CC_XFER_COMPLETION_INT;

    /* Unlock the Crossbar register */
    PlatformUnlockMMR();
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       xbarCPU, XBAR_INST,
                       XBAR_INTR_SOURCE))
    {
        /* Successfully configured CrossBar */
    }
    else
    {
        UARTprintf("Error in configuring CrossBar.\n");
    }

    Intc_IntEnable(edmaInterruptNumber);
    Intc_Init();
    Intc_IntRegister(edmaInterruptNumber, (IntrFuncPtr) isrEdmaCompletion, NULL);
    Intc_IntPrioritySet(edmaInterruptNumber, 1, 0);
    Intc_SystemEnable(edmaInterruptNumber);

    /*      Calculate EDMA cCnt  */
    edmaCCnt = 1;
    while (((dataSize) / edmaCCnt) > 0x7FFF)
    {
        edmaCCnt = edmaCCnt * 2;
    }
    /*      Configure EDMA parameters       */
    edmaChannelNumber  = 0x1U;
    edmaEvtqNumber     = 0x0U;
    edmaTCCNumber      = 0x1U;
    edmaParam.opt      = 0U;
    edmaParam.srcAddr  = (uint32_t) srcBuffer;
    edmaParam.destAddr = crcPSASignatureRegAddress.regL;
    edmaParam.aCnt     = crcPatternSize;
    edmaParam.bCnt     = crcPatterCount / edmaCCnt;
    edmaParam.cCnt     = edmaCCnt;
    edmaParam.srcBIdx  = crcPatternSize;
    edmaParam.destBIdx = 0U;
    edmaParam.srcCIdx  = (crcPatternSize / edmaCCnt);
    edmaParam.destCIdx = 0U;
    edmaParam.linkAddr = 0xFFFFU;
    edmaParam.opt     |=
        (EDMA_TPCC_OPT_SYNCDIM_MASK | EDMA3_OPT_TCINTEN_MASK |
         EDMA3_OPT_ITCINTEN_MASK |
         ((edmaTCCNumber << EDMA3_OPT_TCC_SHIFT) & EDMA3_OPT_TCC_MASK));
    PlatformUnlockMMR();
    /*  Initialize source memory with reference data */
    if (0x4a002100U != testParams->sourceMemory)
    {
        for (forLoopCount = 0;
             forLoopCount < (dataSize / 4);
             forLoopCount++)
        {
            crcSourceMemory[forLoopCount] = forLoopCount;
        }
        UARTprintf("\nCopied reference data into memory @%x.", srcBuffer);
    }
    UARTprintf("\nConfiguring EDMA and CRC for transfer.");
    /*      Configure CRC channel       */
    CRCInitialize(crcModuleBaseAddress,
                  crcChannelNumber,
                  crcWatchdogPreload,
                  crcBlockPreload);
    /*      Configure EDMA      */
    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChannelNumber,
                        edmaTCCNumber,
                        edmaEvtqNumber);

    if ((0U == testParams->crcConfigParams.crcSignHigh) &&
        (0U == testParams->crcConfigParams.crcSignLow))
    {
        /* Get Reference CRC signature value first. */
        UARTprintf("\nCalculating Reference CRC signature Value.");
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
            EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumber, &edmaParam);
            for (transferLoopCount = 0;
                 transferLoopCount < edmaParam.cCnt;
                 transferLoopCount++)
            {
                edmaTransferComplete = 0;
                EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT,
                                    edmaChannelNumber,
                                    EDMA3_TRIG_MODE_MANUAL);
                /*      wait for transfer to complete       */
                while (edmaTransferComplete != 1)
                {}
                /*      Check interrupt status at channel level   */
            }
            loopBreakFlag = 1U;
            while (loopBreakFlag)
            {
                if (CRCGetIntrStatus(crcModuleBaseAddress,
                                     crcChannelNumber) != 0x0U)
                {
                    /* Fetch CRC signature value       */
                    CRCGetPSASectorSig(crcModuleBaseAddress,
                                       crcChannelNumber,
                                       &refSignVal);
                    UARTprintf("\n CRC signature value : 0x%x%xU", refSignVal.regH,
                           refSignVal.regL);
                    loopBreakFlag = 0U;
                    CRCClearIntr(crcModuleBaseAddress,
                                 crcChannelNumber,
                                 CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);
                }
            }
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
        EDMA3SetPaRAM(SOC_EDMA_TPCC_BASE_VIRT, edmaChannelNumber, &edmaParam);
        for (transferLoopCount = 0;
             transferLoopCount < edmaParam.cCnt;
             transferLoopCount++)
        {
            edmaTransferComplete = 0;
            EDMA3EnableTransfer(SOC_EDMA_TPCC_BASE_VIRT,
                                edmaChannelNumber,
                                EDMA3_TRIG_MODE_MANUAL);
            /*      wait for transfer to complete       */
            while (edmaTransferComplete != 1)
            {}
            /*      Check interrupt status at channel level   */
        }
        loopBreakFlag = 1U;
        while (loopBreakFlag)
        {
            if (CRCGetIntrStatus(crcModuleBaseAddress,
                                 crcChannelNumber) != 0x0U)
            {
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
                loopBreakFlag = 0U;
                CRCClearIntr(crcModuleBaseAddress,
                             crcChannelNumber,
                             CRC_CHANNEL_IRQSTATUS_RAW_MAIN_ALL);
            }
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
    /* Disable the EDMA interrupt */
    Intc_SystemDisable(edmaInterruptNumber);
    Intc_IntUnregister(edmaInterruptNumber);

//    return crcErrorFlag;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
void isrEdmaCompletion(void *handle)
{
    edmaTransferComplete = 1;
    EDMA3ClrIntr(SOC_EDMA_TPCC_BASE_VIRT, edmaTCCNumber);
}

