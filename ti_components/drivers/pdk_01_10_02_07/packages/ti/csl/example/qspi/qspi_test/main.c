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
/*
 * \file main.c
 * \brief This file demonstrates qspi dal API's to perform qspi quick
 *        flash test.
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <ti/csl/csl_qspi.h>
#include <ti/csl/example/utils/uart_console/inc/uartConfig.h>
#if defined (SOC_AM574x) || defined (SOC_AM572x) || defined (SOC_AM571x)
#include <ti/board/board.h>
#endif
#include "qspi_flash.h"
#include <ti/csl/csl_edma.h>
#include <ti/csl/soc.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
#define BOOT_FROM_FLASH 0
#define _READ_MM_MODE_ 0
#define _WRITE_MM_MODE_ 0

#define FLASH_BLOCK_SIZE (64 * 1024)
#define READ_LENGTH (16 * 1024)
#define FLASH_SIZE  (32 * 1024 * 1024)  /* 32MB */

#if !defined (__ARM_ARCH_7A__)
#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
uint8_t         _dstBuff1[FLASH_BLOCK_SIZE];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff2, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
uint8_t         _dstBuff2[256 * 1024];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */
uint8_t         _srcBuff1[FLASH_BLOCK_SIZE];

#else
uint8_t __attribute__((section(".my_sect_ddr"))) _dstBuff1[FLASH_BLOCK_SIZE];
uint8_t __attribute__((section(".my_sect_ddr"))) _dstBuff2[256 * 1024];
uint8_t __attribute__((section(".my_sect_ddr"))) _srcBuff1[FLASH_BLOCK_SIZE];
#endif

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/*To use UARTConfigPuts function for prints*/
#if (defined (SOC_AM574x) || defined (SOC_AM572x)) || (defined (SOC_AM571x))
uint32_t uartBaseAddr = CSL_MPU_UART3_REGS;
#undef SOC_QSPI_ADDRSP0_BASE
#define SOC_QSPI_ADDRSP0_BASE CSL_MPU_QSPI_ADDRSP0_REGS
#endif
#if defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_DRA75x)
uint32_t uartBaseAddr = SOC_UART1_BASE;
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
uint32_t uartBaseAddr = SOC_UART3_BASE;
#endif
uint32_t        edma_ch_num   = 1;
uint32_t        edma_tcc_num  = 1;
uint32_t        edma_evtq_num = 0;
uint32_t        entryPoint_modena;

uint32_t        flash_size;
uint32_t        buf_size;

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
    /*pad configurations for QSPI*/
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A18,0x70001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A13,0x70001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_CS2,0x70001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A17,0x70001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A16,0x70001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A15,0x70001);
    HW_WR_REG32(CSL_MPU_CORE_PAD_IO_REGISTERS_REGS+CSL_CONTROL_CORE_PAD_IO_PAD_GPMC_A14,0x70001);
#endif
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX) || defined (SOC_DRA72x) || defined (SOC_DRA75x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_RXD,0x00040000);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_UART1_TXD,0x00040000);
    /*pad configurations for QSPI*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A18,0x70001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A13,0x70001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_CS2,0x70001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A17,0x70001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A16,0x70001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A15,0x70001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_GPMC_A14,0x70001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
#endif
#if defined (SOC_TDA3XX) || defined (SOC_DRA78x)
    /*Pad configurations */
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_SCLK,0x00040001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_SPI1_CS0,0x00000001);
    /*pad configurations for QSPI*/
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_CS6,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_UART1_RTSN,0x70008);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_CS1,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_CS5,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_CS4,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_CS3,0x60001);
    HW_WR_REG32(SOC_CORE_PAD_IO_REGISTERS_BASE+CTRL_CORE_PAD_IO_GPMC_CS2,0x60001);
    /* Set the UART Parameters */
    UARTConfigInit(uartBaseAddr, BAUD_RATE_115200, UART_WORD_LENGTH_8, UART_STOP_BIT_1, UART_NO_PARITY,
                   UART_16x_MODE);
#endif
}

int main(void) {
    qspi_DeviceType_e DeviceType;
    volatile uint32_t dstAddr, srcOffsetAddr;
    volatile uint32_t srcAddr, dstOffsetAddr;
    volatile uint32_t length;
    uint32_t          i;
    uint8_t          *patternOrg = (uint8_t *) (_srcBuff1);
    uint8_t          *patternAddr;
    uint8_t          *patternRead = (uint8_t *) (_dstBuff1);
    uint32_t         *srctest, *dsttest;
    uint32_t          offset_addr = 0x0;
    uint32_t          testCase;

    /*Pad configuration and PRCM enable*/
    padConfig_prcmEnable();

    while (1)
    {
        UARTConfigPuts(uartBaseAddr,
            "\nEnter Device type to use\
                \n1 - Spansion 1 bit \n2 - Spansion 4 bit\
                \n3 - Micron 1 bit   \n4 - Micron 4 bit\
                \n5 - Winbond 1 bit  \n6 - Winbond 4 bit\
                \n7 - ISSI 1 bit     \n8 - ISSI 4 bit\n$ > ",
            -1);
        testCase = UARTConfigGetNum(uartBaseAddr);
        if (testCase == 1)
        {
            DeviceType = DEVICE_TYPE_SPANSION_QSPI1;
            break;
        }
        else if (testCase == 2)
        {
            DeviceType = DEVICE_TYPE_SPANSION_QSPI4;
            break;
        }
        else if (testCase == 3)
        {
            DeviceType = DEVICE_TYPE_MICRON_QSPI1;
            break;
        }
        else if (testCase == 4)
        {
            DeviceType = DEVICE_TYPE_MICRON_QSPI4;
            break;
        }
        else if (testCase == 5)
        {
            DeviceType = DEVICE_TYPE_WINBOND_QSPI1;
            break;
        }
        else if (testCase == 6)
        {
            DeviceType = DEVICE_TYPE_WINBOND_QSPI4;
            break;
        }
        else if (testCase == 7)
        {
            DeviceType = DEVICE_TYPE_ISSI_QSPI1;
            break;
        }
        else if (testCase == 8)
        {
            DeviceType = DEVICE_TYPE_ISSI_QSPI4;
            break;
        }
        else
        {
            UARTConfigPuts(uartBaseAddr,"\nInvalid Input Please try again\n", -1);
        }
    }

    QSPI_Initialize(DeviceType);
    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
    QSPIConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);

        UARTConfigPuts(uartBaseAddr,"\nquick flash test",-1);

            /* Data read from the Flash in cfg port mode */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
            QSPIConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
            /* Erase the first block */
            QSPI_WriteEnable();
            UARTConfigPuts(uartBaseAddr,"\nErasing QSPI Flash Block", -1);
            QSPI_FlashBlockErase(0);

            UARTConfigPuts(uartBaseAddr,"\nErase Complete", -1);

            UARTConfigPuts(uartBaseAddr,"\nWriting test pattern to flash.. ", -1);
            length      = READ_LENGTH; /* in words */
            patternAddr = patternOrg;
            for (i = 0; i < (length * 4); i++)
            {
                *patternAddr++ = i + 8;
            }

            /* Write data from DDR location to flash at offset address  */
            srcAddr       = (uint32_t) patternOrg;
            dstOffsetAddr = offset_addr;
            while (length > 64) {
                /* Change to Memory mapped mode with given chip select */
                if (0)
                {
                    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
                    QSPIConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
                    QSPI_WriteEnable();
                    QSPI_WriteSectors(dstOffsetAddr, srcAddr, 64);
                }
                else
                {
                    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                    QSPIConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
                    QSPI_WriteEnable();
                    QSPI_WriteCfgMode(dstOffsetAddr, srcAddr, 64);
                    /* 64 words -- 64*4= 256 bytes */
                }
                length        -= 64;
                dstOffsetAddr += 256;
                srcAddr       += 256;
            }
            if (length > 0)
            {
                /* Change to Memory mapped mode with given chip select */
                if (0)
                {
                    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
                    QSPIConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
                    QSPI_WriteEnable();
                    QSPI_WriteSectors(dstOffsetAddr, srcAddr, length);
                }
                else
                {
                    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                    QSPIConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
                    QSPI_WriteEnable();
                    QSPI_WriteCfgMode(dstOffsetAddr, srcAddr, length);
                }
            }
            UARTConfigPuts(uartBaseAddr,"\nWrite flash Completed", -1);

            UARTConfigPuts(uartBaseAddr,"\nReading the flash data..\n", -1);

            /* Read From 0x10 words from offset address 0x100 Memory mapped
             *mode*/
            dstAddr       = (uint32_t) patternRead;
            srcOffsetAddr = offset_addr;
            length        = READ_LENGTH;

            /* Change to Memory mapped mode with given chip select */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
            QSPIConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
            QSPI_ReadSectors((void *) dstAddr, (void *) &srcOffsetAddr,
                            length * 4);

            srctest = (uint32_t *) (_srcBuff1);
            dsttest = (uint32_t *) (_dstBuff1);
            for (i = 0; i < (length); i++)
            {
                uint32_t dataval = *dsttest;
                if (*srctest !=
                    (((dataval & 0xFF) << 24) | ((dataval & 0xFF00) << 8) |
                    ((dataval &
                        0xFF0000) >> 8) | ((dataval & 0xFF000000) >> 24)))
                {
                    UARTConfigPuts(uartBaseAddr,"\n Data Read write error at flash location - ",
                            -1);
                    UARTConfigPutNum(uartBaseAddr,i);
                    break;
                }
                srctest++; dsttest++;
            }
            if (i == length)
            {
                UARTConfigPuts(uartBaseAddr,"\nData Read Write Test Passed.", -1);
            }
            /* switch to cfg port mode */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
            QSPIConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);
            /* Now erase first 4 KB sector using sub sector erase */
            QSPI_WriteEnable();
            QSPI_FlashSubSectorErase(0);
            /* Change to Memory mapped mode with given chip select */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                        QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
            QSPIConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,QSPI_CS0);
            dstAddr       = (uint32_t) patternRead;
            srcOffsetAddr = 0x0U;
            QSPI_ReadSectors((void *) dstAddr, (void *) &srcOffsetAddr,
                            QSPIFLASH_SUBSECTORSIZE);
            /* Check if all bits in first 4 KB is set to 0xFF */
            dsttest = (uint32_t *) (_dstBuff1);
            for (i = 0; i < (QSPIFLASH_SUBSECTORSIZE / 4); i++)
            {
                if (*dsttest != 0xFFFFFFFF)
                {
                    UARTConfigPuts(uartBaseAddr,"\nSub sector erase failed ", -1);
                    UARTConfigPutNum(uartBaseAddr,i);
                    break;
                }
                dsttest++;
            }
            if (i == (QSPIFLASH_SUBSECTORSIZE / 4))
            {
                UARTConfigPuts(uartBaseAddr,"\nSub sector erase on first 4 KB sector successful ",
                         -1);
            }

            UARTConfigPuts(uartBaseAddr,"\nQuick Flash Test Complete.\n", -1);
   /* end test case 1*/
   return 0;
}
/********************************* End of file ******************************/

