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
 *  \file     rti_dwwd_reaction_change_in_open_window_main.c
 *
 *  \brief    This file contains RTI DWWD test code for changing reaction when
 *            DWWD is enabled.
 *
 *  \details  DWWD window size is set to 50%. DWWD is configured to generate
 *            reset. Reaction is changed during closed window to generate
 *            interrupt. DWWD will generate Interrupt to IPU after expiration.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_rti.h>
#include <ti/csl/tistdtypes.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/drv/stw_lld/platform/irq_xbar.h>
#include <ti/drv/stw_lld/uartconsole/uartStdio.h>
#include <ti/drv/stw_lld/examples/utility/stwutils_app.h>
#include <st_rti.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define CTRL_MODULE_CORE_CORE_REGISTERS_BASE_MMR_LOCK_2        (0x00000444U)
#define CTRL_MODULE_CORE_CORE_REGISTERS_BASE_MMR_LOCK_2_LOCK   (0xFDF45530U)
#define CTRL_MODULE_CORE_CORE_REGISTERS_BASE_MMR_LOCK_2_UNLOCK (0xF757FDC0U)
#define SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE_IPU_IRQ_43_44    (0x00000068U)
#define SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE_IPU_IRQ_44_MASK  (0x000001FFU)
#define SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE_IPU_IRQ_44_SHIFT (1U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static uint32_t   rtiWindow_size =
    RTI_DWWD_WINDOWSIZE_50_PERCENT;
static uint32_t   rtiPreload_value = 0x00EAU;
static uint32_t   rtiModule        = SOC_RTI4_BASE;
volatile uint32_t isrFlag          = 1U;
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   ISR for RTI 4.
 *
 * \param   none.
 *
 * \retval  none.
 */
void rtiisr(void *handle);

extern deviceLastResetStaus_t DeviceGetLastResetStatus(void);
extern void RTISetClockSource(uint32_t rtiModule, uint32_t rtiClockSource);
extern void RTISetSuspendLine(uint32_t             rtiModule,
                              rtiSuspendLineCore_t deviceCore);
extern void AMMU_config(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main()
{
    int32_t config_status, status;

    StwUtils_appWaitForSbl();

    PlatformUartConsoleSetPinMux();
    UARTStdioInit();

    RTISetClockSource(rtiModule, RTI_CLOCK_SOURCE_32KHZ);

    /*      Register RTI 4 interrupt for IPU        */
    if (irq_xbar_success ==
        IRQXBARConnect(SOC_IRQ_DMARQ_CROSSBAR_REGISTERS_BASE,
                       CPU_IPU1, XBAR_INST_IPU1_IRQ_44,
                       RTI4_IRQ_WWD))
    {
        /* Successfully configured CrossBar */
        status = STW_SOK;
    }
    else
    {
        UARTprintf("Error in configuring CrossBar.\n");
        status = STW_EFAIL;
    }
    if (STW_SOK == status)
    {
        /* Enable Error interrupt for DCC */
        Intc_IntEnable(44U);
        Intc_Init();
        /* Register ISR */
        Intc_IntRegister(44U,
                         (IntrFuncPtr) rtiisr, 0);
        Intc_IntPrioritySet(44U, 1, 0);
        Intc_SystemEnable(44U);
    }
    /*      Clear DWWD status     */
    RTIDwwdClearStatus(rtiModule, RTI_DWWD_STATUS_KEY_SEQ_VIOLATION |
                       RTI_DWWD_STATUS_TIME_WINDOW_VIOLATION |
                       RTI_DWWD_STATUS_ENDTIME_WINDOW_VIOLATION |
                       RTI_DWWD_STATUS_STARTTIME_WINDOW_VIOLATION |
                       RTI_DWWD_STATUS_LAST_RESET);
    /*      Configure DWWD      */
    config_status = RTIDwwdWindowConfig(rtiModule,
                                        RTI_DWWD_REACTION_GENERATE_RESET,
                                        rtiPreload_value,
                                        rtiWindow_size);
    if (config_status == STW_EFAIL)
    {
        UARTprintf(" Error during Window configuration.\n");
    }
    else
    {
        UARTprintf(
            "DWWD is configured to generate RESET after 60sec time-out.\n");
        /*      Enable DWWD     */
        RTIDwwdCounterEnable(rtiModule);
        /*      Change Reaction and Service DWWD in Open Window      */
        while (RTIDwwdIsClosedWindow(rtiModule)) {}
        RTIDwwdSetReaction(rtiModule, RTI_DWWD_REACTION_GENERATE_NMI);
        RTIDwwdService(rtiModule);
        UARTprintf("DWWD serviced.\n");
        /*      let DWWD expire here  */
        UARTprintf("Wait for Interrupt to be generated by DWWD.\n");
        while (1U == isrFlag)
        {}
        StwUtils_appLogTestResult(STWUTILS_APP_TST_STATUS_PASS);
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
void rtiisr(void *handle)
{
    UARTprintf("DWWD generated interrupt to IPU on expiration.\n");
    UARTprintf("Testcase (ID = STW_RTI_TC00013) PASSED.\n");
    isrFlag = 0U;
}

