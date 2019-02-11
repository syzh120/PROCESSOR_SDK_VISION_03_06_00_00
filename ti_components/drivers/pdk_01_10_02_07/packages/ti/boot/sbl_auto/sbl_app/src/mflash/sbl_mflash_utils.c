/*
 *  Copyright (C) 2016 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file     sbl_mflash_utils.c
 *
 *  \brief    This file contains the SBL mflash utility functions
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <stdint.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/csl_mmu.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib.h>
#include <ti/drv/pm/pmhal.h>
#include <stdlib.h>
#include <ti/csl/csl_qspi.h>
#include <ti/boot/sbl_auto/qspiflash/qspi_flash.h>
#include <ti/csl/csl_edma.h>
#include <sbl_mflash_utils.h>
#include <stdint.h>
#include <stdarg.h>
#include <ti/csl/csl_uart.h>
#include <ti/csl/arch/csl_arch.h>
#include <sbl_mflash_uart_console.h>
#include <ti/boot/sbl_auto/sbl_lib/sbl_lib_board.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/*
 * Number of word to be written to QSPI
 */
#define SBL_MFLASH_NUM_QSPI_WORDS           (64U)

/*
 * Temporary data buffer size for mflash
 */
#define SBL_MFLASH_BUFFER_SIZE              (64U * 1024U)

/*
*  Fifo trigger level
*/
#define SBL_MFLASH_UART_FIFO_TRIGGER         (16U)

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
/*
 * Temporary data buffer for mflash
 */
static uint8_t gDataBuffer[SBL_MFLASH_BUFFER_SIZE];

/* -------------------------------------------------------------------------- */
/*                 Flashing Function Definitions                              */
/* -------------------------------------------------------------------------- */
void SBLMFlashRun(void)
{
    int8_t startSignal;
    /* Two way handshake with the PC side mflash*/
    while(1)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, SBL_MFLASH_CMD_HNDSKE_STEP1);
        startSignal = SBLMFlashUARTConsoleGetcNonBlocking();
        if(startSignal == (int8_t)SBL_MFLASH_CMD_HNDSKE_STEP1_RESPONSE)
        {
            SBLLibPutc((uint32_t)SBLLIB_TRACE_LEVEL_INFO1, (uint8_t)SBL_MFLASH_CMD_HNDSKE_STEP2);
            break;
        }
    }

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n[TDAxx] Utility mflash will Execute now.");

    /* Initializes memory and prints device id */
    SBLMFlashMemoryInit();
    SBLMFlashPrintQSPIDeviceId();

    /* Enable cache */
#if defined (SOC_TDA3XX)
    UNICACHEEnable(SOC_IPU1_UNICACHE_MMU_CONF_REGS_BASE);
#endif
    /* Displays menu option to user */
    SBLMFlashMenu();
}

void SBLMFlashMenu(void)
{
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n[TDAxx] !!______TDAxx flashing utility______!!");
    uint32_t mainMenuOption;
    uint32_t stopByte = 1U;

    /* Takes inputs from user until utility exits */
    while (stopByte)
    {
        SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\v");
        mainMenuOption = SBLLibGetNum();

        switch (mainMenuOption)
        {
            case (1U):
                SBLMFlashMemoryErase();
                break;

            case (2U):
                SBLMFlashDownloadFile();
                break;

            case (3U):
                SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n[TDAxx] Exiting.");
                stopByte = 0U;
                break;

            default:
                break;
        }
    }
    /* Acks PC client about exit on the target */
    SBLLibPutc((uint32_t)SBLLIB_TRACE_LEVEL_INFO1, SBL_MFLASH_CMD_TRANSFER_COMPLETE);
}

void SBLMFlashMemoryInit(void)
{
    uint32_t edmaChNum   = 1U;
    uint32_t edmaTccNum  = 1U;
    uint32_t edmaEvtqNum = 0U;

    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n[TDAxx] Setting up QSPI");
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1,
                 "\n[TDAxx] QSPI Spansion 4 bit Device type");

    /* Configure PADs. */
    SBLLibQSPISetPinMux();

    /* Initialize the EDMA */
    EDMAsetRegion(0);
    EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);

    EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT,
                        EDMA3_CHANNEL_TYPE_DMA,
                        edmaChNum,
                        edmaTccNum,
                        edmaEvtqNum);

    /*QSPI Initialization*/
    QSPI_Initialize(DEVICE_TYPE_QSPI4);
}

void SBLMFlashPrintQSPIDeviceId(void)
{
    uint32_t deviceId;
    deviceId = QSPI_GetDeviceId();
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n[TDAxx] MID - ");
    SBLLibPrintHexNum(SBLLIB_TRACE_LEVEL_INFO1, deviceId & 0xFFU);
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n[TDAxx] DID - ");
    SBLLibPrintHexNum(SBLLIB_TRACE_LEVEL_INFO1, (deviceId & 0xFF0000U) >> 16U);
}

void SBLMFlashDownloadFile(void)
{
    uint32_t bufferSize  = SBL_MFLASH_BUFFER_SIZE;
    uint32_t bytesToRead = SBL_MFLASH_BUFFER_SIZE;
    uint32_t destoffset;
    uint32_t current;
    uint32_t filesize;

    /* Sending "t" to client asking for file size request */
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\t");
    filesize = SBLLibGetNum();

    /* Sending "?" to client asking offset from beginning of qspi */
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\?");
    destoffset = SBLLibGetHexNum();
    current    = destoffset;

    /* Sending " ' " to client asking for file to be transferred */
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\'");

    /* Wait for the PC to send the START SEND signal*/
    SBLLibGetc();

    while (current < (destoffset + filesize))
    {
        /* Handles the case for last block if chunk size is less than
         * SBL_MFLASH_BUFFER_SIZE
         */
        if (((destoffset + filesize) - current) < SBL_MFLASH_BUFFER_SIZE)
        {
            bytesToRead = (destoffset + filesize) - current;
            bufferSize  = bytesToRead + 4U;

            if ((bufferSize % 4U) == 0U)
            {
                bufferSize = bufferSize - 4U;
            }
        }
        /* Asks for next patch of the file being downloaded */
        SBLLibPutc(SBLLIB_TRACE_LEVEL_INFO1, SBL_MFLASH_CMD_SEND_NEXT_PATCH);
        SBLMFlashUARTGetFile(gDataBuffer, bytesToRead);

        SBLMFlashWriteQSPI(gDataBuffer, bufferSize / 4U, current);

        current = current + bufferSize;
    }

    /* Notifies PC that file transfer is complete */
    SBLLibPutc(SBLLIB_TRACE_LEVEL_INFO1, SBL_MFLASH_CMD_TRANSFER_COMPLETE);
}

void SBLMFlashMemoryErase(void)
{
    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
    QSPI_ConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,
                        QSPI_MMR);

    QSPI_WriteEnable();
    SBLLibPrintf(
        SBLLIB_TRACE_LEVEL_INFO1,
        "\n[TDAxx] Erasing entire QSPI Flash..This takes 50-60 seconds.");

    /* Erases qspi memory */
    QSPI_FlashFullErase();
    SBLLibPrintf(SBLLIB_TRACE_LEVEL_INFO1, "\n!!![TDAxx] Erase Completed!!!");
}

void SBLMFlashWriteQSPI(const uint8_t *buff, uint32_t length,
                        uint32_t destination)
{
    /* Writes SBL_MFLASH_NUM_QSPI_WORDS to qspi  */
    while (length > (SBL_MFLASH_NUM_QSPI_WORDS))
    {
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
        QSPI_ConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,
                            QSPI_MMR);
        QSPI_WriteEnable();
        QSPI_WriteCfgMode(destination, (uint32_t) buff,
                          SBL_MFLASH_NUM_QSPI_WORDS);
        length      -= SBL_MFLASH_NUM_QSPI_WORDS;
        destination += (SBL_MFLASH_NUM_QSPI_WORDS * 4U);
        buff        += (SBL_MFLASH_NUM_QSPI_WORDS * 4U);
    }
    /* Writes remaining bytes to qspi  */
    if (length > 0)
    {
        QSPISetMAddrSpace(
            SOC_QSPI_ADDRSP0_BASE,
            (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
        QSPI_ConfMAddrSpace(
            (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);
        QSPI_WriteEnable();
        QSPI_WriteCfgMode(destination, (uint32_t) buff, length);
    }
}

void SBLMFlashUARTGetFile(uint8_t *pRxBuffer, uint32_t numBytesToRead)
{
    uint32_t count = 0U;
    uint32_t numBytesRead = 0U;

    do
    {
        /*Checking if the UART FIFO contains more than FIFO_SIZE characters*/
        if(SBLMFlashUARTRxFIFOLevelGet() >= SBL_MFLASH_UART_FIFO_TRIGGER)
        {
            numBytesRead = SBLMFlashUARTConsoleFIFOGets(pRxBuffer,
                                                        SBL_MFLASH_UART_FIFO_TRIGGER);
            pRxBuffer += numBytesRead;
            count += numBytesRead;
        }
    } while (count < numBytesToRead);
}

void SblPrintFunction(const char *message)
{
    SBLMFlashUARTPuts(message, -((int32_t) 1));
}

void SblPrintHexNumFunction(uint32_t tracelevel, uint32_t value)
{
    SBLMFlashUARTPutHexNum(value);
}

void SblPutcFunction(uint32_t tracelevel, uint8_t value)
{
    SBLMFlashUARTPutc(value);
}

char SblGetcFunction(void)
{
    return SBLMFlashUARTGetc();
}

uint32_t SblGetNumFunction(void)
{
    return ((uint32_t) SBLMFlashUARTGetNum());
}

uint32_t SblGetHexNumFunction(void)
{
    return SBLMFlashUARTGetHexNum();
}
