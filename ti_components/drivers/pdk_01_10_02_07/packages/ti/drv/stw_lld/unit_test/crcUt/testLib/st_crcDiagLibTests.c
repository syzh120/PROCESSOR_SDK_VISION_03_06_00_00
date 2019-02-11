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
 *  \file st_crcDiagLibTests.c
 *
 *  \brief Common across test-cases with DiagLib.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdlib.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/cslr_crc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/csl/csl_crc.h>
#include <st_crc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#define EDMA3_CC_REGION                 (1U)

#define DIAGLIB_APP_CRC_INT             (34U)
#define XBAR_CPU                        (CPU_IPU1)
#define XBAR_INST                       (XBAR_INST_IPU1_IRQ_34)
#define XBAR_INTR_SOURCE                (CRC_IRQ_CH1_CPR_COMP)
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static DiagLib_CrcTestParams_t *gCrcTestParams;
static DiagLib_CrcOutParams_t   gCrcOutParams;
static DiagLib_CrcObj_t         gCrcObj;
static volatile int32_t         gTestStatus;

static uint32_t gCrcSrcMemory[8192U];
/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This API to enable the clock for CRC module.
 *          Defined in st_crcCommon.c.
 *
 * \param   none.
 *
 * \retval  none.
 */
extern void CRCClockEnable(void);

/**
 * \brief   This Interrupt Service Routine for EDMA completion interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void CrcCompletionISR(void *handle);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void DiagLibCrcTest_main(st_CRCTestcaseParams_t *testPrms)
{
    uint32_t edmaRegion, loopCnt;

    /*      Enable CRC clock        */
    CRCClockEnable();

    gCrcTestParams = &testPrms->diagLibTestParams;

    if ((gCrcTestParams->bitSize == DIAGLIB_CRC_BIT_64) &&
        (gCrcTestParams->mode == CRC_OPERATION_MODE_SEMICPU))
    {
        /* Do EDMA init Done once in the beginning */
        edmaRegion = EDMA3_CC_REGION;
        EDMAsetRegion(edmaRegion);
        EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);
    }

    if (gCrcTestParams->crcCheckMode == DIAGLIB_CRC_INTERRUPT_MODE)
    {
        if (irq_xbar_success ==
            IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                           XBAR_CPU, XBAR_INST, XBAR_INTR_SOURCE))
        {
            /* Successfully configured CrossBar */
        }
        else
        {
            UARTprintf("Error in configuring CrossBar.\n");
        }

        Intc_Init();
        Intc_IntEnable(0);
        Intc_IntRegister(DIAGLIB_APP_CRC_INT,
                         (IntrFuncPtr) CrcCompletionISR, NULL);
        Intc_IntPrioritySet(DIAGLIB_APP_CRC_INT, 1, 0);
        Intc_SystemEnable(DIAGLIB_APP_CRC_INT);
    }

    if ((gCrcTestParams->testType == DIAGLIB_CRC_TEST_GET_CRC) ||
        (gCrcTestParams->testType == DIAGLIB_CRC_TEST_USER))
    {
        for (loopCnt = 0; loopCnt < (gCrcTestParams->dataSize / 4U); loopCnt++)
        {
            gCrcSrcMemory[loopCnt] = loopCnt;
        }
        gCrcTestParams->testData = gCrcSrcMemory;
    }

    if (gCrcTestParams->testType == DIAGLIB_CRC_TEST_GET_CRC)
    {
        DiagLib_crcCalculateSW(gCrcTestParams, &gCrcOutParams, &gCrcObj);
        UARTprintf("CRC SW value for given data: regL: 0x%x regH: 0x%x\n",
                   gCrcOutParams.crcData.regL, gCrcOutParams.crcData.regH);

        DiagLib_crcCalculateHW(gCrcTestParams, &gCrcOutParams, &gCrcObj);
    }
    else
    {
        gTestStatus = DiagLib_crcStartTest(gCrcTestParams,
                                           &gCrcOutParams, &gCrcObj);
    }

    while (gTestStatus == 1)
    {}

    if (gCrcTestParams->testType == DIAGLIB_CRC_TEST_GET_CRC)
    {
        UARTprintf("CRC HW value for given data: regL: 0x%x regH: 0x%x\n",
                   gCrcOutParams.crcData.regL, gCrcOutParams.crcData.regH);
    }

    testPrms->testResult = gTestStatus;

    /* Disable the interrupt */
    Intc_SystemDisable(DIAGLIB_APP_CRC_INT);

    /* Unregister the interrupt */
    Intc_IntUnregister(DIAGLIB_APP_CRC_INT);

    Intc_IntDisable();
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void CrcCompletionISR(void *handle)
{
    gTestStatus = DiagLib_crcISR(gCrcTestParams, &gCrcOutParams, &gCrcObj);
}

