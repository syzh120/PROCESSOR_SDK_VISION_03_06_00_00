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
 *  \file     sbl_mbx_ipu1_cpu0.c
 *
 *  \brief    This file contains SBL multicore mailbox binary for IPU1 CPU0.
 *
 *  \details   IPU1 CPU0 sends message to IPU1 CPU1, DSP1, DSP2 and EVE1. Each
 *             core sends an acknowledgement after receiving message.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <stdio.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_mailbox.h>
#include <ti/csl/soc.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/csl/csl_emif.h>
#include <ti/drv/pm/include/prcm/pmhal_prcm.h>
#include <ti/drv/pm/include/prcm/pmhal_rm.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

#define IPU1_CPU0_MAILBOX_MSG                           ((uint32_t) 0xFF33BB00U)
#define IPU_ECC_EMIF_TEST_INTR_LINE_NUMBER              ((uint32_t) 35U)
#define ECC_EMIF_START_ADDRESS                          (0x80000000U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif
/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

static void EmifEccErrHandler(void);
static void EmifEccHFHandler(void);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void padConfig_prcmEnable()
{
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
}


int main()
{
    uint32_t         msg           = 0U;
    uint32_t         ipu1Cpu1Flag  = 0U;
    uint32_t         dsp1Flag      = 0U;
    uint32_t         dsp2Flag      = 0U;
    uint32_t         eve1Flag      = 0U;
    emifEccErrInfo_t eccDDRErrInfo = {0};
    uint32_t         index         = 0U;

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    UARTConfigPuts(uartBaseAddr,"\r\n Multi-core Mailbox Application: IPU1 Core0 Master core \r\n ",
             -1);

    /* Check if any one bit errors occurred previously */
    EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                               EMIF_ERR_ECC_ONEBIT,
                               &eccDDRErrInfo);

    for (index = 0U; index < eccDDRErrInfo.numValidErrAddr; index++)
    {
        UARTConfigPuts(uartBaseAddr,"\r\n 1 Bit ECC Error occurred before coming to application", -1);
        UARTConfigPuts(uartBaseAddr,"\r\n 1 Bit Error occurred at address: ", -1);
        UARTConfigPutHexNum(uartBaseAddr,eccDDRErrInfo.errAddr[index] + ECC_EMIF_START_ADDRESS);
    }

    if (0U < eccDDRErrInfo.numValidErrAddr)
    {
        UARTConfigPuts(uartBaseAddr,"\r\n 1 Bit Error mask value: ", -1);
        UARTConfigPutHexNum(uartBaseAddr,eccDDRErrInfo.errBitLoc);
        EMIFClearIntrStatus(
            SOC_EMIF1_CONF_REGS_BASE,
            EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ONEBIT_ECC_ERR_SYS_MASK);
    }

    /* Check if any two bit errors occurred previously */
    EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                               EMIF_ERR_ECC_TWOBIT,
                               &eccDDRErrInfo);

    if (0U != eccDDRErrInfo.errAddr[0U])
    {
        UARTConfigPuts(uartBaseAddr,"\r\n 2 Bit ECC Error occurred before coming to application", -1);
        UARTConfigPuts(uartBaseAddr,"\r\n 2 Bit Error occurred at address: ", -1);
        UARTConfigPutHexNum(uartBaseAddr,eccDDRErrInfo.errAddr[0U] + ECC_EMIF_START_ADDRESS);
    }

    /* Configure interrupts for ECC Errors */
    CSL_xbarIrqConfigure(CSL_XBAR_IRQ_CPU_ID_IPU1,XBAR_INST_IPU1_IRQ_35,
		                     CSL_XBAR_EMIF1_IRQ);

    Intc_Init();
    Intc_IntEnable(0);

    /* Enable The EMIF interrupt for 1Bit ECC Error */
    Intc_IntRegister(IPU_ECC_EMIF_TEST_INTR_LINE_NUMBER,
                     (IntrFuncPtr) EmifEccErrHandler,
                     NULL);
    Intc_IntPrioritySet(IPU_ECC_EMIF_TEST_INTR_LINE_NUMBER, 1, 0);
    Intc_SystemEnable(IPU_ECC_EMIF_TEST_INTR_LINE_NUMBER);

    /* Register Hard Fault Handler for 2Bit ECC Error */
    Intc_IntRegister(EXCEPTION_M4_HARD_FAULT_NUM_3,
                     (IntrFuncPtr) EmifEccHFHandler,
                     NULL);

    EMIFEnableIntr(SOC_EMIF1_CONF_REGS_BASE,
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK |
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK |
                   EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ONEBIT_ECC_ERR_SYS_MASK);

    /* Send message to IPU1 CPU1(MBX2_Q0) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_0,
                              IPU1_CPU0_MAILBOX_MSG)) ;

    /* Send message to DSP1(MBX2_Q1) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_1,
                              IPU1_CPU0_MAILBOX_MSG)) ;

    /* Send message to DSP2(MBX2_Q2) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_2,
                              IPU1_CPU0_MAILBOX_MSG)) ;

    /* Send message to EVE1(MBX2_Q3) */
    while (MESSAGE_INVALID ==
           MailboxSendMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_3,
                              IPU1_CPU0_MAILBOX_MSG)) ;

    while ((ipu1Cpu1Flag != 1U) ||
           (dsp1Flag != 1U) ||
           (dsp2Flag != 1U) ||
           (eve1Flag != 1U))
    {
        /* Read message from IPU1 CPU1 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_4, &msg))
        {
            UARTConfigPuts(uartBaseAddr," \r\n IPU1 CPU1 booted-up successfully \r\n", -1);
            ipu1Cpu1Flag = 1U;
        }

        /* Read message from DSP1 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_5, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n DSP1 booted-up successfully \r\n", -1);
            dsp1Flag = 1U;
        }

        /* Read message from DSP2 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_6, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n DSP2 booted-up successfully \r\n", -1);
            dsp2Flag = 1U;
        }
        /* Read message from EVE1 */
        if (MESSAGE_INVALID !=
            MailboxGetMessage(SOC_MAILBOX2_BASE, MAILBOX_QUEUE_7, &msg))
        {
            UARTConfigPuts(uartBaseAddr,"\r\n EVE1 booted-up successfully \r\n", -1);
            eve1Flag = 1U;
        }
    }
    return 0;
}

static void EmifEccErrHandler(void)
{
    uint32_t         eccDDRErrStatus;
    emifEccErrInfo_t eccDDRErrInfo = {0};
    uint32_t         index         = 0U;
    int32_t          retVal        = STW_SOK;
    EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                               EMIF_ERR_ECC_ONEBIT,
                               &eccDDRErrInfo);

    for (index = 0U; index < eccDDRErrInfo.numValidErrAddr; index++)
    {
        UARTConfigPuts(uartBaseAddr,"\r\n 1 Bit ECC Error is found!!", -1);
        UARTConfigPuts(uartBaseAddr,"\r\n 1 Bit Error occurred at address: ", -1);
        UARTConfigPutHexNum(uartBaseAddr,eccDDRErrInfo.errAddr[index] + ECC_EMIF_START_ADDRESS);
    }

    UARTConfigPuts(uartBaseAddr,"\r\n 1 Bit Error mask value: ", -1);
    UARTConfigPutHexNum(uartBaseAddr,eccDDRErrInfo.errBitLoc);

    EMIFClearIntrStatus(
        SOC_EMIF1_CONF_REGS_BASE,
        EMIF_SYSTEM_OCP_INTERRUPT_STATUS_ONEBIT_ECC_ERR_SYS_MASK);

    eccDDRErrStatus = EMIFGetIntrStatus(SOC_EMIF1_CONF_REGS_BASE);

    if (0x0U !=
        (eccDDRErrStatus &
         EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK))
    {
        EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                                   EMIF_ERR_ECC_TWOBIT,
                                   &eccDDRErrInfo);

        UARTConfigPuts(uartBaseAddr,"\r\n 2 Bit ECC Error is found!!", -1);
        UARTConfigPuts(uartBaseAddr,"\r\n 2 Bit Error occurred at address: ", -1);
        UARTConfigPutHexNum(uartBaseAddr,eccDDRErrInfo.errAddr[0] + ECC_EMIF_START_ADDRESS);
        UARTConfigPuts(uartBaseAddr,"\r\n Doing a cold reset due to 2 Bit Error Interrupt \r\n", -1);
        retVal = PMHALResetAssertGlobal(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
        if (STW_SOK != retVal)
        {
            UARTConfigPuts(uartBaseAddr,"\r\nFailed to do cold reset\r\n", -1);
            while (1) ;
        }
    }
    else if (0x0U !=
             (eccDDRErrStatus &
              EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK))
    {
        UARTConfigPuts(uartBaseAddr,"\r\n ECC Non-quanta Access Error is found!! \r\n", -1);
        UARTConfigPuts(uartBaseAddr,"\r\n Doing a cold reset due to 2 Bit Error Interrupt \r\n", -1);
        retVal = PMHALResetAssertGlobal(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
        if (STW_SOK != retVal)
        {
            UARTConfigPuts(uartBaseAddr,"\r\nFailed to do cold reset\r\n", -1);
            while (1) ;
        }
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"\r\n Unidentified interrupt found!! \r\n", -1);
        UARTConfigPuts(uartBaseAddr,"\r\n Doing a cold reset due to Unidentified Interrupt \r\n", -1);
        retVal = PMHALResetAssertGlobal(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
        if (STW_SOK != retVal)
        {
            UARTConfigPuts(uartBaseAddr,"\r\nFailed to do cold reset\r\n", -1);
            while (1) ;
        }
    }
}

static void EmifEccHFHandler(void)
{
    uint32_t         eccDDRErrStatus;
    emifEccErrInfo_t eccDDRErrInfo = {0};
    int32_t          retVal        = STW_SOK;

    eccDDRErrStatus = EMIFGetIntrStatus(SOC_EMIF1_CONF_REGS_BASE);

    if (0x0U !=
        (eccDDRErrStatus &
         EMIF_SYSTEM_OCP_INTERRUPT_STATUS_TWOBIT_ECC_ERR_SYS_MASK))
    {
        EMIFConfigECCGetEccErrInfo(SOC_EMIF1_CONF_REGS_BASE,
                                   EMIF_ERR_ECC_TWOBIT,
                                   &eccDDRErrInfo);

        UARTConfigPuts(uartBaseAddr,"\r\n 2 Bit ECC Error is found!!", -1);
        UARTConfigPuts(uartBaseAddr,"\r\n 2 Bit Error occurred at address: ", -1);
        UARTConfigPutHexNum(uartBaseAddr,eccDDRErrInfo.errAddr[0] + ECC_EMIF_START_ADDRESS);
    }
    else if (0x0U !=
             (eccDDRErrStatus &
              EMIF_SYSTEM_OCP_INTERRUPT_STATUS_WR_ECC_ERR_SYS_MASK))
    {
        UARTConfigPuts(uartBaseAddr,"\r\n ECC Non-quanta Access Error is found!! \r\n", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"\r\n Hard Fault Interrupt occurred!! \r\n", -1);
    }

    UARTConfigPuts(uartBaseAddr,"\r\n Doing a cold reset due to HF Error \r\n", -1);
    retVal = PMHALResetAssertGlobal(PMHAL_PRCM_GLB_RG_GLOBAL_COLD_RST);
    if (STW_SOK != retVal)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nFailed to do cold reset\r\n", -1);
        while (1) ;
    }
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */
