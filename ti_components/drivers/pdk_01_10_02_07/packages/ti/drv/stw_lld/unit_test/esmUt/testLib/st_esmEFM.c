/*
 *  Copyright (C) 2015 Texas Instruments Incorporated
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
 *  \file     st_esmNormalMode.c
 *
 *  \brief    This file contains ESM test code.
 *
 *  \details  ESM operational mode is set to normal mode for group 1.
 *            EVE reset interrupt is enabled from group 1 and
 *            it's priority is set as high level interrupt.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/cslr_esm.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/csl/soc.h>
#include <ti/csl/cslr_synctimer.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/drv/pm/pmhal.h>
#include <ti/csl/csl_esm.h>
#include <st_esm.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
extern void ESMPlatformUARTInit(void);

extern int32_t ESMClockEnable(void);

extern void ESMTestFunc(uint32_t testId);

extern void cntrl_core_pad_configuration1(uint32_t            baseAdd,
                                          const pad_config_t *pad_config);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int32_t st_esmefm_main(st_ESMTestcaseParams_t *testParams)
{
    /* Testcase params */
    uint32_t     esmBaseAddr, esmMode;
    int32_t      configStatus, result = STW_EFAIL;
    uint32_t     loopCnt/*, numOfIntr*/;
    pad_config_t esm_pad_config = {CTRL_CORE_PAD_IO_MDIO_D,
                                   CTRL_CORE_PAD_IO_MDIO_D_MUXMODE_ESM_ERROR_5,
                                   CTRL_CORE_PAD_IO_MDIO_D_PULLUDENABLE_ENABLE,
                                   CTRL_CORE_PAD_IO_MDIO_D_PULLTYPESELECT_PULL_UP,
                                   CTRL_CORE_PAD_IO_MDIO_D_INPUTENABLE_ENABLE,
                                   CTRL_CORE_PAD_IO_MDIO_D_SLEWCONTROL_FAST,
                                   0xff};

    /* Configure testcase params */
    esmBaseAddr = testParams->esmConfigParams.esmModule;
    esmMode     = testParams->esmConfigParams.esmMode;

    /*numOfIntr = testParams->esmConfigParams.numOfIntr;*/

    /* Set result to fail */
    testParams->testResult = STW_EFAIL;

    /* Configure UARTStdioInit */
    ESMPlatformUARTInit();

    /* PAD config */
    cntrl_core_pad_configuration1(SOC_CORE_PAD_IO_REGISTERS_BASE,
                                  &esm_pad_config);

    /* Enable ESM module */
    configStatus = ESMClockEnable();
    if (STW_SOK != configStatus)
    {
        UARTprintf("Error in ESM module enable.\n");
    }
    else
    {
        if (1U != ESMGetErrPinStatus(esmBaseAddr))
        {
            ESMResetErrPin(esmBaseAddr);
        }
        UARTprintf("Probe and Check esm_error pin on oscilloscope.\n");
        UARTprintf("Configuring ESM in Error Force Mode.\n");
        ESMSetMode(esmBaseAddr, esmMode);
        /* Enable and configure all the test-case interrupts */
        if (0U == ESMGetErrPinStatus(esmBaseAddr))
        {
            result = STW_SOK;
            UARTprintf("esm_error pin is LOW.\n");
        }
        /* some delay */
        for (loopCnt = 0; loopCnt < 0xFFFFFU; loopCnt++)
        {}
        if (0U == ESMGetErrPinStatus(esmBaseAddr))
        {
            UARTprintf("esm_error reset requested.\n");
            ESMResetErrPin(esmBaseAddr);
            if (1U == ESMGetErrPinStatus(esmBaseAddr))
            {
                UARTprintf("esm_error pin is HIGH.\n");
                result = STW_SOK;
            }
        }
        else
        {
            result = STW_EFAIL;
        }
        /* Set result to pass */
        testParams->testResult = result;
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
/* None */
