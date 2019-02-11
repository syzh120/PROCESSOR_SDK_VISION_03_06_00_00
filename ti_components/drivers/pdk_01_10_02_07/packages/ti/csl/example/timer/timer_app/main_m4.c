/*
 *  Copyright (C) 2013-2017 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   main_m4.c
 *
 *  \brief This file demonstrates TIMER dal.
 *
**/

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include "stdint.h"
#include "stdio.h"
#include <ti/csl/soc.h>
#include <ti/csl/csl_timer.h>
#include "sample.h"
#include <ti/csl/csl_types.h>
#include <ti/csl/arch/csl_arch.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
uint32_t INP_CLK_FREQ           =        20000000U;
uint32_t TIMER_INITIAL_COUNT    =        0U;
uint32_t TIMER_RLD_COUNT        =        0U;
void Timer_val(uint32_t inp_clk, uint32_t delay, uint32_t prescl_val);
#else
#define TIMER_INITIAL_COUNT             (0xFFF00000U)
#define TIMER_RLD_COUNT                 (0xFFF00000U)
#endif

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
uint32_t irq_count = CSL_IPU_IRQ_XBAR_COUNT;
uint32_t uartBaseAddr = CSL_MPU_UART3_REGS;
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
uint32_t irq_count = CSL_IPU1_IRQ_XBAR_COUNT;
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t irq_count = CSL_IPU1_IRQ_XBAR_COUNT;
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

/* ========================================================================== */
/*                   Internal Varialbes Definitions                           */
/* ========================================================================== */
static volatile uint32_t gCntValue     = 10;
static volatile uint32_t gIsrSemaphore = 0;
static volatile uint32_t gXbarInst     = 1;
static volatile uint32_t gNumSuccess   = 0;

/* ========================================================================== */
/*                   Internal Function Declarations                           */
/* ========================================================================== */
static void TimerPRCMConfigure(void);
static void TimerIntcInit(void);
static void TimerIntcDeInit(void);
static void TimerSetUp(void);
static void TimerIsr(void *handle);
static void TimerRun(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /*Pad configurations */
    Board_initCfg boardCfg;
    boardCfg = BOARD_INIT_UNLOCK_MMR | BOARD_INIT_UART_STDIO | 
               BOARD_INIT_MODULE_CLOCK | BOARD_INIT_PINMUX_CONFIG;
    Board_init(boardCfg);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* Initialize the UART Instance */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* Initialize the UART Instance */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
}

int main(void)
{
    /* Do Pad Config for UART */
    padConfig_prcmEnable();

    /*Set PRCM for Timer4 */
    /*This is done in SBL, adding here to make the app standalone */
    TimerPRCMConfigure();

#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
    /*Set the timer reload count value */
    Timer_val(INP_CLK_FREQ, 50000U,1U);
#endif

    UARTConfigPuts(uartBaseAddr,"\nTimer Application Running", -1);

    /* Run the Timer irq_count times,
     * increment gXbarInst in each iteration */
    for (gXbarInst = 1; gXbarInst <= irq_count; gXbarInst++)
    {
        TimerRun();
    }

    if (gNumSuccess == irq_count)
    {
        UARTConfigPuts(uartBaseAddr,"\nAll Xbar instances for M4 are verified successfully", -1);
    }
    return 0;
}

static void TimerRun(void)
{
    /* Register Timer4 interrupts on to INTC */
    TimerIntcInit();

    /* Perform the necessary configurations for Timer4 */
    TimerSetUp();

    /* Enable the Timer4 interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);

    /* Start the Timer */
    TIMEREnable(SOC_TIMER4_BASE);

    UARTConfigPuts(uartBaseAddr,"\ncntValue:", -1);

    while (gCntValue)
    {
        if (gIsrSemaphore)
        {
            gIsrSemaphore--;
            UARTConfigPuts(uartBaseAddr," ", -1);
            UARTConfigPutNum(uartBaseAddr,(int32_t)gCntValue);
        }
    }

    /* Stop the Timer */
    TIMERDisable(SOC_TIMER4_BASE);

    if (gCntValue == 0)
    {
        UARTConfigPuts(uartBaseAddr,"\n|RESULT|SUCCESS|", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"\n|RESULT|FAIL|", -1);
    }

    /* Unregister Timer4 interrupts */
    TimerIntcDeInit();
}

/*
** Do the necessary Timer configurations on to INTC.
*/
static void TimerIntcInit(void)
{
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,gXbarInst,CSL_XBAR_TIMER4_IRQ);

    UARTConfigPuts(uartBaseAddr,"\nXBar is sucessfully connected to inst:", -1);
    UARTConfigPutNum(uartBaseAddr,(int32_t)gXbarInst);

    /* Initialize the interrupt control */
    Intc_Init();

    /* Enable the interrupt */
    Intc_IntEnable(0);

    /* Registering TimerIsr */
    Intc_IntRegister(intrM4[gXbarInst - 1], (IntrFuncPtr) TimerIsr, NULL);

    /* Set the priority */
    Intc_IntPrioritySet(intrM4[gXbarInst - 1], 1, 0);

    /* Enable the system interrupt */
    Intc_SystemEnable(intrM4[gXbarInst - 1]);
}

/*
** Disable the interrupt configurations on INTC.
*/
static void TimerIntcDeInit(void)
{
    /* Restore the initial state of gCntValue */
    gCntValue = 10;

    /* Disconnect the XBar */
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,gXbarInst,CSL_XBAR_IRQ_MIN);

    /* Disable the timer interrupt */
    Intc_SystemDisable(intrM4[gXbarInst - 1]);

    /* Unregister the interrupt */
    Intc_IntUnregister(intrM4[gXbarInst - 1]);
}

/*
** Setup the timer for one-shot and compare mode.
*/
static void TimerSetUp(void)
{
    /*Reset the timer module */
    TIMERReset(SOC_TIMER4_BASE);

    /* Enable free run in emulation mode */
    TIMEREmuModeConfigure(SOC_TIMER4_BASE, TIMER_FREE);

    /* Load the counter with the initial count value */
    TIMERCounterSet(SOC_TIMER4_BASE, TIMER_INITIAL_COUNT);

    /* Load the load register with the reload count value */
    TIMERReloadSet(SOC_TIMER4_BASE, TIMER_RLD_COUNT);

    /* Configure the Timer for Auto-reload and compare mode */
    TIMERModeConfigure(SOC_TIMER4_BASE, TIMER_AUTORLD_NOCMP_ENABLE);

    /* Configure the posted mode of TIMER */
    TIMERPostedModeConfig(SOC_TIMER4_BASE, TIMER_NONPOSTED);

    /* Configure the read mode of TIMER */
    TIMERReadModeConfig(SOC_TIMER4_BASE, TIMER_READ_MODE_NONPOSTED);
}

/*
** Timer interrupt service routine. This will send a character to serial
** console.
*/
static void TimerIsr(void *handle)
{
    /* Disable the Timer interrupts */
    TIMERIntDisable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);

    /* Clear the status of the interrupt flags */
    TIMERIntStatusClear(SOC_TIMER4_BASE, TIMER_INT_OVF_IT_FLAG);

    gIsrSemaphore++;
    gCntValue--;

    if (gCntValue == 0)
    {
        UARTConfigPuts(uartBaseAddr," ", -1);
        UARTConfigPutNum(uartBaseAddr,(int32_t) (gCntValue));
        gIsrSemaphore = 0;
        gNumSuccess++;
    }

    /* Enable the Timer interrupts */
    TIMERIntEnable(SOC_TIMER4_BASE, TIMER_INT_OVF_EN_FLAG);
}

/*
** Timer4 PRCM configuration. This will explicitly enable the Timer4 module.
*/
static void TimerPRCMConfigure(void)
{
    HW_WR_REG32(SOC_L4PER_CM_CORE_BASE + CM_L4PER_TIMER4_CLKCTRL, 0x2);

    while ((HW_RD_REG32(SOC_L4PER_CM_CORE_BASE +
                        CM_L4PER_TIMER4_CLKCTRL) & (0x00030000)) != 0x0) ;
}

/*
** This function is used to find the timer count value 
** required for the provided delay
** inp_clk is the input clock source of the timer.
** time unit is always micro seconds.
** prescl_val defines the timer prescale value.
*/
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
void Timer_val(uint32_t inp_clk, uint32_t delay, uint32_t prescl_val)
{
   uint32_t divisor = 1000000U, count = 0U;
   
   divisor = divisor * prescl_val;
   count = (inp_clk / divisor) * delay;
   if(count <= 0xffffffffU)
   {
        TIMER_INITIAL_COUNT = 0xffffffff - count;
        TIMER_RLD_COUNT = 0xffffffff - count;
   }
   else
   {
        TIMER_INITIAL_COUNT = 0U;
        TIMER_RLD_COUNT = 0U;
   }
}
#endif

/********************************* End of file ******************************/
