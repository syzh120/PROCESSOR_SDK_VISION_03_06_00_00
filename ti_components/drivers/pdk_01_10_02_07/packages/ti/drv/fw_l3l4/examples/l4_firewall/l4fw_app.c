/* =============================================================================
 *   Copyright (c) Texas Instruments Incorporated 2016
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
 *  \file     l4fw_app.c
 *
 *  \brief    This file contains L4FW lib.
 *
 *  \details  The application will configure the L4Per1 firewall all the regions
 *            to block and try to access the base address of region.
 *            This will cause the ISR where errors are cleared.
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/arch/csl_arch.h>
#include <ti/drv/fw_l3l4/fwlibl4.h>
#include <ti/csl/csl_l4fw.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */
#if defined (__TI_ARM_V7M4__)
    #define APP_L4FW_ERROR_INT                  (44U)
    #define APP_XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_IPU1)
    #define APP_XBAR_INST_ERROR                 (CSL_XBAR_INST_IPU1_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CSL_XBAR_CTRL_MODULE_CORE_IRQ_SEC_EVTS)
#else
    #define APP_L4FW_ERROR_INT                  (44U)
    #define APP_XBAR_CPU                        (CSL_XBAR_IRQ_CPU_ID_MPU)
    #define APP_XBAR_INST_ERROR                 (CSL_XBAR_INST_MPU_IRQ_44)
    #define APP_XBAR_INTR_SOURCE_ERROR          (CSL_XBAR_CTRL_MODULE_CORE_IRQ_SEC_EVTS)
#endif
/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
static volatile uint32_t gIsrWait;
static l4fwAllApErrors_t gL4fwAllErr;
/* Skip AP region and Initiator Port regions */
static uint32_t          gSkipRegions[4] = {0, 1, 77, 78};
static uint32_t          gErrorIsrCount = 0;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA75X)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78X)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   This function is used to configure and enable CPU interrupt.
 *
 * \param   None.
 *
 * \retval  status          Configuration status.
 */
static uint32_t L4FWAppInterruptConfig(void);

/**
 * \brief   This Interrupt Service Routine for L3FW error interrupt.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void L4FWAppErrorIntrISR(void *handle);

/**
 * \brief   This Clears all existing interrupts in Control module sec err and
 *          L4FW IA errors.
 *
 * \param   none.
 *
 * \retval  none.
 */
static void L4FWAppClearExistingInterrupts(void);
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
int main(void)
{
    L4FWRegionSizeParams_t regionSizeParam;
    uint32_t regionNum, groupNum, baseAddr;
    volatile uint32_t      done = 1;
    l4fwInstSummary_t      instSum;
    uint32_t loopCnt, portCnt, i, skipRegion;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA75X)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00000000);
    /* set the uart parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78X)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /* set the uart parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                    UART_16x_MODE);
#endif

    UARTConfigPuts(uartBaseAddr, "\r\nStarting application...\r\n", -1);
    L4FWAppClearExistingInterrupts();

    L4FWAppInterruptConfig();

    /* Access some address in one region before and after blocking in L4FW */
    groupNum = 2;
    baseAddr = SOC_L4_PER_AP_BASE;

    FWLIBL4GetInstSummary(baseAddr, &instSum);
    /* Access the register in the region */
    FWLIBL4SetProtGroupMembers(baseAddr, groupNum, 0);
    FWLIBL4SetProtGroupMembers(baseAddr, groupNum + 1, 0xFFFF);
    for (regionNum = 0; regionNum < instSum.fwNumRegions; regionNum++)
    {
        skipRegion = 0;
        for (i = 0; i < 4; i++)
        {
            if (regionNum == gSkipRegions[i])
            {
                skipRegion = 1;
            }
        }
        if (skipRegion == 1)
        {
            continue;
        }
        gIsrWait = 1;
        L4FWGetRegionSizeParams(baseAddr, regionNum, &regionSizeParam);
        HW_RD_REG32(baseAddr + regionSizeParam.regionBaseAddr);

        /* Block access to all masters in group, and assign this group to the
         *region */
        FWLIBL4SetRegionProtGroupId(baseAddr, regionNum, groupNum);

#if defined (__TI_ARM_V7M4__)
        UARTConfigPuts(uartBaseAddr, "Now we are accesssing an Address from M4 core which is "
            "blocked in L4FW, This will result in Hard fault\r\n", -1);
#endif
        /* Access the register in the region after blocking in L4 firewall */
        HW_RD_REG32(baseAddr + regionSizeParam.regionBaseAddr);

        /* Wait till L4 address protection error isr */
        while (gIsrWait == 1) ;
        FWLIBL4SetRegionProtGroupId(baseAddr, regionNum, groupNum + 1);
        for (loopCnt = 0U; loopCnt < L4FW_NUM_INST; loopCnt++)
        {
            for (portCnt = 0U; portCnt < L4FW_MAX_PORTS; portCnt++)
            {
                if (gL4fwAllErr.l4Err[loopCnt][portCnt].fwErrorCode !=
                    L4_IA_AGENT_ERROR_LOG_L_CODE_NO_ERROR)
                {
                    if (baseAddr + regionSizeParam.regionBaseAddr !=
                        (gL4fwAllErr.l4Err[loopCnt][portCnt].fwErrorBaseAddr
                         +
                         gL4fwAllErr.l4Err[loopCnt][portCnt].fwBaseAddr))
                    {
                        UARTConfigPuts(uartBaseAddr, "App Error.\r\n", -1);
                        while (1) ;
                    }
                }
            }
        }
    }
    UARTConfigPuts(uartBaseAddr, "\r\nL4 Error interrupt called ", -1);
    UARTConfigPutNum(uartBaseAddr, gErrorIsrCount);
    UARTConfigPuts(uartBaseAddr, " times.\r\n", -1);
    UARTConfigPuts(uartBaseAddr, "End of application...\r\n", -1);

    /* Restore the group access parameters */
    L4FWSetProtGroupMembers(baseAddr, groupNum, 0xFFFF);
    while (done) ;
    return 0;
}

/* ========================================================================== */
/*                 Internal Function Definitions                              */
/* ========================================================================== */
static uint32_t L4FWAppInterruptConfig(void)
{
    /* Configure Cross bar instance and interrupt */
    CSL_xbarIrqConfigure(APP_XBAR_CPU, APP_XBAR_INST_ERROR, APP_XBAR_INTR_SOURCE_ERROR);

    /* Enable Error interrupt for L3FW */
    Intc_Init();
    Intc_IntEnable(APP_L4FW_ERROR_INT);

    /* Register ISR */
    Intc_IntRegister(APP_L4FW_ERROR_INT,
                     (IntrFuncPtr) L4FWAppErrorIntrISR, 0);
    Intc_IntPrioritySet(APP_L4FW_ERROR_INT, 1, 0);
    Intc_SystemEnable(APP_L4FW_ERROR_INT);

    return STW_SOK;
}

static void L4FWAppErrorIntrISR(void *handle)
{
    uint32_t loopCnt, portCnt;

    memset(&gL4fwAllErr, 0, sizeof (gL4fwAllErr));
    FWLIBL4ClearAndGetAllError(&gL4fwAllErr);

    for (loopCnt = 0U; loopCnt < L4FW_NUM_INST; loopCnt++)
    {
        for (portCnt = 0U; portCnt < L4FW_MAX_PORTS; portCnt++)
        {
            if (gL4fwAllErr.l4Err[loopCnt][portCnt].fwErrorCode !=
                L4_IA_AGENT_ERROR_LOG_L_CODE_NO_ERROR)
            {
                gIsrWait = 0;
                gErrorIsrCount++;
            }
        }
    }
}

static void L4FWAppClearExistingInterrupts(void)
{
    memset(&gL4fwAllErr, 0, sizeof (gL4fwAllErr));
    FWLIBL4ClearAndGetAllError(&gL4fwAllErr);

    /* Clear all remaining errors in control module sec err register */
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_SEC_ERR_STATUS_FUNC_1, 0xFFFFFFFFU);
    HW_WR_REG32(SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
                CTRL_CORE_SEC_ERR_STATUS_FUNC_2, 0xFFFFFFFFU);
}

