/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2015-2016
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
 *  \file     esm_app.c
 *
 *  \brief    This file contains ESM test code.
 *
 *  \details  ESM operational mode is set to normal mode for group 1.
 *            EVE reset interrupt is enabled from group 1 and
 *            it's priority is set as high level interrupt.
 **/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_timer.h>
#include <ti/csl/cslr_esm.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/csl_esm.h>
#include <ti/csl/cslr_synctimer.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#define APP_ESM_MODULE          (SOC_ESM_BASE)
#define APP_ESM_MODE            (ESM_OPERATION_MODE_NORMAL)
#define APP_ESM_INTR            (ESM_GROUP1_INTR_SRC_EVE_CPU_RST)

#define APP_ESM_INT_M4                                  (34U)
#define APP_ESM_INT_DSP                                 (32U)
#if defined (__TI_ARM_V7M4__)
    #define APP_ESM_INT                     (APP_ESM_INT_M4)
    #define XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_IPU1)
    #define XBAR_INST                       (CSL_XBAR_INST_IPU1_IRQ_34)
    #define XBAR_INTR_SOURCE                (CSL_XBAR_ESM_IRQ_HIGH)
#elif defined (_TMS320C6X)
    #define APP_ESM_INT                     (APP_ESM_INT_DSP)
    #define XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_DSP1)
    #define XBAR_INST                       (CSL_XBAR_INST_DSP1_IRQ_32)
    #define XBAR_INTR_SOURCE                (CSL_XBAR_ESM_IRQ_HIGH)
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
volatile uint32_t isrFlag = 1U;

#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This Interrupt Service Routine for ESM interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void AppESMIntrISR(void *handle);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
#endif
}

int main(void)
{
    /* Do Pad Config for UART */
    padConfig_prcmEnable();
    /* Initialize the UART Instance */
   /* Initialize the UART Instance */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
    UARTConfigPuts(uartBaseAddr,"\nStarting application...\n", -1);
    /* XBar configuration */
    CSL_xbarIrqConfigure(XBAR_CPU,XBAR_INST,XBAR_INTR_SOURCE);
    /* Enable Error interrupt for ESM */
    Intc_Init();
    Intc_IntEnable(APP_ESM_INT);

    /* Register ISR */
    Intc_IntRegister(APP_ESM_INT,
                     (IntrFuncPtr) AppESMIntrISR, 0);
    Intc_IntPrioritySet(APP_ESM_INT, 1, 0);
    Intc_SystemEnable(APP_ESM_INT);
    UARTConfigPuts(uartBaseAddr,"XBar configuration successfully done.\n", -1);

    /* Enable ESM module */
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    HW_WR_FIELD32(SOC_L4PER_CM_CORE_BASE+CM_L4PER_ESM_CLKCTRL,
                  CM_L4PER_ESM_CLKCTRL_MODULEMODE,
                  CM_L4PER_ESM_CLKCTRL_MODULEMODE_ENABLE);
    while (CM_L4PER_ESM_CLKCTRL_IDLEST_FUNC !=
           HW_RD_FIELD32(SOC_L4PER_CM_CORE_BASE+CM_L4PER_ESM_CLKCTRL,
                         CM_L4PER_ESM_CLKCTRL_IDLEST))
    {
        /* Wait till ESM module is enabled */
    }
#endif
    ESMSetMode(APP_ESM_MODULE, APP_ESM_MODE);
    ESMEnableIntr(APP_ESM_MODULE, APP_ESM_INTR);
    ESMSetIntrPriorityLvl(APP_ESM_MODULE, APP_ESM_INTR,
                          ESM_INTR_PRIORITY_LEVEL_HIGH);
    /* Generate/trigger error condition here */
    UARTConfigPuts(uartBaseAddr,"Do EVE CPU Reset.\nWait for interrupt till reset is given.\n",
             -1);
    while (1U == isrFlag)
    {
        /* Wait here till interrupt happens */
    }
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static void AppESMIntrISR(void *handle)
{
    uint32_t status;

    status = ESMGetIntrStatus(APP_ESM_MODULE,
                              APP_ESM_INTR);
    if (1U == status)
    {
        UARTConfigPuts(uartBaseAddr,"EVE reset interrupt occurred.\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"EVE reset did not interrupt occur.\n", -1);
    }
    status = ESMGetHighPriorityLvlIntrStatus(APP_ESM_MODULE);
    UARTConfigPuts(uartBaseAddr,"Highest level pending interrupt is",-1);
    UARTConfigPutNum(uartBaseAddr,(uint32_t)status);
    UARTConfigPuts(uartBaseAddr,"\n",-1);
    ESMClearIntrStatus(APP_ESM_MODULE, APP_ESM_INTR);
    ESMDisableIntr(APP_ESM_MODULE, APP_ESM_INTR);
    isrFlag = 0U;
    UARTConfigPuts(uartBaseAddr,"Application is completed.\n", status);
}
/********************************* End of file ******************************/
