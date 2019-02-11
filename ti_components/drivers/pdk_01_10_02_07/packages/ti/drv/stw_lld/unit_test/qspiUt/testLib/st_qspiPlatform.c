/*
 *  Copyright (C) 2016 Texas Instruments Incorporated
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
 *  \file st_qspiPlatform.c
 *
 *  \brief Platform specific code.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <st_qspi.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static Int32 st_qspiEnableQspiModule();
static Int32 st_qspiEnableQspiPinMux();

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

Int32 st_qspiEnableQspiInstance()
{
    Int32 retVal = STW_SOK;

    retVal += st_qspiEnableQspiModule();
    retVal += st_qspiEnableQspiPinMux();

    return (retVal);
}


Int32 st_qspiDisableQspiInstance()
{
    Int32 retVal = STW_SOK;

    return (retVal);
}

static Int32 st_qspiEnableQspiModule()
{
    Int32 retVal = STW_SOK;

    /* Enable module */
    HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL,
                  CM_L4PER2_QSPI_CLKCTRL_MODULEMODE,
                  CM_L4PER2_QSPI_CLKCTRL_MODULEMODE_ENABLED);

    while ((HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL,
                          CM_L4PER2_QSPI_CLKCTRL_IDLEST)) ==
           CM_L4PER2_QSPI_CLKCTRL_IDLEST_DISABLE)
    {
        ;
    }

    IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                   XBAR_CPU, XBAR_INST,
                   XBAR_INTR_SOURCE);

    return (retVal);
}

static Int32 st_qspiEnableQspiPinMux()
{
    Int32 retVal = STW_SOK;

    PlatformQSPISetPinMux();

    return (retVal);
}

