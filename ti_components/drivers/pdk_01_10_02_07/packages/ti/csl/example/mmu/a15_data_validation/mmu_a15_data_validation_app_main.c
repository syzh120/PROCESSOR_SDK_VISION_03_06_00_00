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
 *  \file     mmu_a15_data_validation_app_main.c
 *
 *  \brief    Source file containing the example application code for A15 MMU
 *            App. First MMU is enabled and data is written using virtual
 *            address. Afterwards MMU is disabled and data is read from physical
 *            address and data integrity is verified.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/csl_mmu.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#include <ti/csl/arch/a15/mmu_a15.h>
#include <ti/csl/arch/a15/cache_a15.h>

/* ========================================================================== */
/*                                Macros                                      */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                 Internal Function Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

__attribute__((aligned(16384)))
mmuA15ModuleTable_t gMmuTable;

mmuA15DescriptorAttrs_t gAttrs;
int32_t gTestStatus = STW_SOK;

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif

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
    uint32_t cacheEnabled = 0;
    uint32_t virtualAddr, tempVirtualAddr;
    uint32_t phyAddr, tempPhyAddr;
    uint32_t regVal = 0, err = 0;

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    UARTConfigPuts(uartBaseAddr,"\r\nA15 MMU Data Validation Test Application", -1);

    /* Check if cache is already enabled */
    cacheEnabled = CACHEA15GetEnabled();

    /* In case cache is disabled, invalidate and enable it */
    if (CACHE_A15_TYPE_ALL != cacheEnabled)
    {
        CACHEA15InvalidateL1DAll();

        CACHEA15InvalidateL1IAll();

        CACHEA15Enable(CACHE_A15_TYPE_ALL);
    }

    /* Initialize MMU module */
    MMUA15Init();

    /* Set MAIR to inner and outer cacheable */
    MMUA15SetMAIR(&gMmuTable, MMU_A15_ATTR_INDEX_2, 0xFF);

    /* Initialize descriptor attributes */
    MMUA15InitDescAttrs(&gAttrs);

    /* Set level one descriptor attributes */
    gAttrs.descriptorType = MMU_A15_DESCRIPTOR_TYPE_BLOCK;
    gAttrs.attrIndx       = MMU_A15_ATTR_INDEX_2;
    gAttrs.nonSecure      = MMU_A15_NON_SECURE_ENABLE;
    gAttrs.accPerm        = MMU_A15_ACC_PERM_RW_ANY_PL; /*Read Write at any PL*/

    /* Set level one descriptor */
    virtualAddr = 0x0, phyAddr = 0x0;
    MMUA15SetFirstLevelDesc(&gMmuTable, virtualAddr, phyAddr, &gAttrs);
    virtualAddr = 0x40000000, phyAddr = 0x40000000;
    MMUA15SetFirstLevelDesc(&gMmuTable, virtualAddr, phyAddr, &gAttrs);
    virtualAddr = 0x80000000, phyAddr = 0x80000000;
    MMUA15SetFirstLevelDesc(&gMmuTable, virtualAddr, phyAddr, &gAttrs);
    virtualAddr = 0xc0000000, phyAddr = 0x80000000;
    MMUA15SetFirstLevelDesc(&gMmuTable, virtualAddr, phyAddr, &gAttrs);

    /* Enable MMU */
    MMUA15Enable(&gMmuTable);

    virtualAddr = 0xd0000000;

    for (tempVirtualAddr = virtualAddr;
         tempVirtualAddr < virtualAddr + 0x00200000;
         tempVirtualAddr = tempVirtualAddr + 4)
    {
        HW_WR_REG32(tempVirtualAddr, 0x12345678U);
    }

    /* Disable MMU */
    MMUA15Disable();

    phyAddr = 0x90000000;

    /* Check if data is written correctly at physical address */
    for (tempPhyAddr = phyAddr;
         tempPhyAddr < phyAddr + 0x00200000;
         tempPhyAddr = tempPhyAddr + 4)
    {
        regVal = HW_RD_REG32(tempPhyAddr);
        if (0x12345678 != regVal)
        {
            UARTConfigPuts(uartBaseAddr,"\r\nData read error at address:", -1);
            UARTConfigPutHexNum(uartBaseAddr,tempPhyAddr);
            err         = 1;
            gTestStatus = STW_EFAIL;
            break;
        }
    }

    if ((0U == err) && (tempPhyAddr == (phyAddr + 0x00200000)))
    {
        UARTConfigPuts(uartBaseAddr,"\r\nData integrity verified", -1);
        UARTConfigPuts(uartBaseAddr,"\r\nA15 MMU App Passed", -1);
    }

    /* Disable cache */
    CACHEA15Disable(CACHE_A15_TYPE_ALL);

    if (gTestStatus == STW_SOK)
    {
        UARTConfigPuts(uartBaseAddr,"\r\nA15 MMU Data Validation Test Pass", -1);
    }
    else
    {
        UARTConfigPuts(uartBaseAddr,"\r\nA15 MMU Data Validation Test Fail", -1);
    }

    return 0;
}

/* -------------------------------------------------------------------------- */
/*                 Internal Function Definitions                              */
/* -------------------------------------------------------------------------- */

/* None */