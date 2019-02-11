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
 *  @file   qspi.c
 *
 *  @brief  This file contains the Flash driver using QSPI hal.
 *
 *  @path   $(ds)\test\hal\qspi_test\qspi.c
 *
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <stdlib.h>
#include <ti/csl/csl_types.h>
#include "qspi_flash.h"
#include <ti/csl/cslr_qspi.h>
#include <ti/csl/hw_types.h>
#include <ti/csl/soc.h>
#include "qspi_cmd_init.h"

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
#define QSPI_READ_DEVICEID_MAX_WORDS   (20U)
QSPI_FlashDevInfo_t gQspiFlashDevInfo;
uint32_t gQspiCmdInitDone = 0U;

#if (defined (SOC_AM574x) || defined (SOC_AM572x)) || (defined (SOC_AM571x))
#undef SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE
#define SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE CSL_MPU_CTRL_MODULE_CORE_CORE_REGISTERS_REGS
#undef SOC_L4PER_CM_CORE_BASE
#define SOC_L4PER_CM_CORE_BASE CSL_MPU_L4PER_CM_CORE_REGS
#undef SOC_QSPI_ADDRSP0_BASE
#define SOC_QSPI_ADDRSP0_BASE CSL_MPU_QSPI_ADDRSP0_REGS
#undef SOC_QSPI_ADDRSP1_BASE
#define SOC_QSPI_ADDRSP1_BASE CSL_MPU_QSPI_ADDRSP1_REGS
#endif

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
static uint32_t getNumAddrBytesFromBits(uint32_t numBits);
static uint32_t getNumDummyBytesFromBits(uint32_t numBits);
static uint32_t getMemSetupReadType(uint32_t cmdRegDataType);
static void mem1cpy(void *dstAddr, void *srcAddr, uint32_t length);

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */
void QSPIConfMAddrSpace(uint8_t MMPT_S,qspi_ChipSelect_e chipSelect)
{
    /* set MAddrSpace in control module for CS0*/
    HW_WR_FIELD32(
        (uint32_t) SOC_CTRL_MODULE_CORE_CORE_REGISTERS_BASE +
        CTRL_CORE_CONTROL_IO_2,
        CTRL_CORE_CONTROL_IO_2_QSPI_MEMMAPPED_CS,
        chipSelect);
}

void QSPISelClockFrequency(qspi_ClockFreq_e in_ClockSettings)
{
    /* select 128/192MHz from L4 QSPI CLK CTRL register */

    /* Set divider value in QSPI Clock Control */
    HW_WR_FIELD32(
        (uint32_t) SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL,
        CM_L4PER2_QSPI_CLKCTRL_CLKSEL_DIV,
        CM_L4PER2_QSPI_CLKCTRL_CLKSEL_DIV_DIV1);
    if (in_ClockSettings & QSPI_CLKSWITCH_MASK)  /* set QSPI clock source as
                                                  * PER_QSPI_CLK from DPLL_PER
                                                  */
    {
        HW_WR_FIELD32(
            (uint32_t) SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL,
            CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE,
            CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE_SEL_PER_QSPI_CLK);
    }
    else /* set QSPI clock source as 128MHz derived from DPLL_PER*/
    {
        HW_WR_FIELD32(
            (uint32_t) SOC_L4PER_CM_CORE_BASE + CM_L4PER2_QSPI_CLKCTRL,
            CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE,
            CM_L4PER2_QSPI_CLKCTRL_CLKSEL_SOURCE_SEL_FUNC_128M_CLK);
    }
}

int32_t QSPI_executeCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data)
{
    int32_t  retVal          = TRUE;
    uint32_t frameLength = 0U, cmdInfo = 0U;
    uint32_t localData, i;

    if ((flashCmd.numDataWords != 0) && (NULL == data))
    {
        retVal = FALSE;
    }
    if (retVal == TRUE)
    {
        if (flashCmd.numAddrBits != 0)
        {
            frameLength++;
        }
        if (flashCmd.numAddrDummyBits != 0)
        {
            frameLength++;
        }
        if (flashCmd.numDataWords != 0)
        {
            frameLength = frameLength + flashCmd.numDataWords;
        }

        /* Write Command */
        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_FLEN, frameLength);
        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WIRQ,
                       QSPI_SPI_CMD_REG_WIRQ_WORD_COUNT_IRQ_DISABLE);
        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_FIRQ,
                       QSPI_SPI_CMD_REG_FIRQ_FRAME_COUNT_IRQ_DISABLE);
        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                       QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                       (flashCmd.numCmdBits - 1U));
        HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CSNUM,
                       QSPI_SPI_CMD_REG_CSNUM_CS_0);

        QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &flashCmd.cmd, (int32_t) 1);
        QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
        QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

        /* Write Address Bytes */
        if (flashCmd.numAddrBits != 0)
        {
            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &flashCmd.addr, (int32_t) 1);
            cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

            HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                           QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
            HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                           (flashCmd.numAddrBits - 1U));

            QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
            QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
        }

        /* Write dummy Bytes */
        if (flashCmd.numAddrDummyBits != 0)
        {
            localData = 0U;
            QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &localData, (int32_t) 1);
            cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

            HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                           QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
            HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                           (flashCmd.numAddrDummyBits - 1U));

            QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
            QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
        }
        /* Read or Write data */
        if (flashCmd.numDataWords != 0)
        {
            if (flashCmd.dataType == QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE)
            {
                for (i = 0; i < flashCmd.numDataWords; i++)
                {
                    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, data, (int32_t) 1);
                    cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

                    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                                   flashCmd.dataType);
                    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                                   (flashCmd.numPerDataWordbits - 1U));

                    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
                    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
                    data++;
                }
            }
            else
            {
                for (i = 0; i < flashCmd.numDataWords; i++)
                {
                    cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

                    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                                   flashCmd.dataType);
                    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                                   (flashCmd.numPerDataWordbits - 1U));

                    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
                    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
                    QSPIreadData(SOC_QSPI_ADDRSP0_BASE, data, (int32_t) 1);
                    data++;
                }
            }
        }
    }
    return retVal;
}

uint32_t QSPI_Initialize(qspi_DeviceType_e DeviceType)
{
    int32_t retVal;
    uint32_t memSetupInfo = 0U, devCtrlInfo = 0U;
    uint32_t numAddBytes, numDummyBytes, readType, numDummyBits;
    QSPI_FlashDevInfo_t localFlashDevInfo;

    if (gQspiCmdInitDone == 0U)
    {
        /* Default initialize for device type passed */
        retVal = QSPI_GetDefaultFlashDevInfo(DeviceType, &localFlashDevInfo);
        if (retVal == TRUE)
        {
            QSPI_SetDefaultFlashDevInfo(DeviceType, &localFlashDevInfo);
        }
    }

    /*
     * Set Device Control register - clock polarity, phase, CS polarity and data
     * delay depending on silicon Revision
     */
    devCtrlInfo = QSPIgetDeviceControl(SOC_QSPI_ADDRSP0_BASE);

    HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CSP0,
                   QSPI_SPI_DC_REG_CSP_ACTIVE_LOW);

    HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_DD0,
                   gQspiFlashDevInfo.qspiDataDelay);

    if (3U == gQspiFlashDevInfo.qspiMode)
    {
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CKP0,
                       QSPI_SPI_DC_REG_CKP_DATA_ACTIVE);
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CKPH0,
                       QSPI_SPI_DC_REG_CKPH_CKP_1_SHIFT_OUT_FALLING_EDGE);
    }
    else
    {
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CKP0,
                       QSPI_SPI_DC_REG_CKP_DATA_INACTIVE);
        HW_SET_FIELD32(devCtrlInfo, QSPI_SPI_DC_REG_CKPH0,
                       QSPI_SPI_DC_REG_CKPH_CKP_0_SHIFT_OUT_FALLING_EDGE);
    }
    QSPIsetDeviceControl(SOC_QSPI_ADDRSP0_BASE, devCtrlInfo);

    /* Set Clock Control register */
    QSPISelClockFrequency(gQspiFlashDevInfo.qspifrequency);
    QSPISetClockControl(SOC_QSPI_ADDRSP0_BASE, gQspiFlashDevInfo.qspifrequency);

    /* Set Memory Map Setup registers */
    numAddBytes = getNumAddrBytesFromBits(
        gQspiFlashDevInfo.readCmd.numAddrBits);

    numDummyBytes = getNumDummyBytesFromBits(
        gQspiFlashDevInfo.readCmd.numAddrDummyBits);

    readType = getMemSetupReadType(
        gQspiFlashDevInfo.readCmd.dataType);

    if (numDummyBytes != QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_NUM_D_BITS)
    {
        numDummyBits = 0;
    }
    else
    {
        numDummyBits = gQspiFlashDevInfo.readCmd.numAddrDummyBits;
    }

    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_RCMD,
                   gQspiFlashDevInfo.readCmd.cmd);
    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_NUM_A_BYTES, numAddBytes);
    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_NUM_D_BYTES,
                   numDummyBytes);
    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_READ_TYPE, readType);
    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_WCMD,
                   gQspiFlashDevInfo.writeCmd.cmd);
    HW_SET_FIELD32(memSetupInfo, QSPI_SPI_SETUP0_REG_NUM_D_BITS, numDummyBits);

    QSPISetMemoryMapSetup(SOC_QSPI_ADDRSP0_BASE, memSetupInfo,
                          gQspiFlashDevInfo.qspiCs);

    if (NULL != gQspiFlashDevInfo.qspiFlashInitFxn)
    {
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
        QSPIConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,
                            QSPI_MMR);
        gQspiFlashDevInfo.qspiFlashInitFxn(DeviceType);
    }

    return TRUE;
} /* QSPI_Initialize */

static uint32_t getMemSetupReadType(uint32_t cmdRegDataType)
{
    uint32_t localReadType;
    if (cmdRegDataType == QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE)
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ;
    }
    else if (cmdRegDataType == QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_DUAL)
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_DUAL_READ;
    }
    else if (cmdRegDataType == QSPI_SPI_CMD_REG_CMD_SIX_PIN_READ_QUAD)
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_QUAD_READ;
    }
    else
    {
        localReadType = QSPI_SPI_SETUP0_REG_READ_TYPE_NORMAL_READ;
    }
    return localReadType;
}

static uint32_t getNumAddrBytesFromBits(uint32_t numBits)
{
    uint32_t numBytes;
    if (numBits <= 8U)
    {
        numBytes = (uint32_t) 0U;
    }
    else if (numBits <= 16U)
    {
        numBytes = 1U;
    }
    else if (numBits <= 24U)
    {
        numBytes = 2U;
    }
    else if (numBits <= 32U)
    {
        numBytes = 3U;
    }
    else
    {
        numBytes = (uint32_t) 0U;
    }
    return numBytes;
}

static uint32_t getNumDummyBytesFromBits(uint32_t numBits)
{
    uint32_t numBytes;
    if (numBits == 8U)
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_8_BITS;
    }
    else if (numBits == 16U)
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_16_BITS;
    }
    else if (numBits == 24U)
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_24_BITS;
    }
    else
    {
        numBytes = QSPI_SPI_SETUP0_REG_NUM_D_BYTES_USE_NUM_D_BITS;
    }
    return numBytes;
}

static void mem1cpy(void *dstAddr, void *srcAddr, uint32_t length)
{
    uint32_t  i;
    uint32_t *DAddr = (uint32_t *) (dstAddr);
    uint32_t *SAddr = (uint32_t *) (srcAddr);
    uint8_t  *DAddr_byte, *SAddr_byte;
    void     *DAddr_byteTmp, *SAddr_byteTmp;

    /*Do a word read*/
    for (i = 0U; i < (length / 4U); i++)
    {
        *DAddr = *SAddr;
        DAddr++;
        SAddr++;
    }

    /*Do a byte write*/
    if ((length % 4U) != 0U)
    {
        DAddr_byteTmp = (void *) DAddr;
        SAddr_byteTmp = (void *) SAddr;
        DAddr_byte    = (uint8_t *) DAddr_byteTmp;
        SAddr_byte    = (uint8_t *) SAddr_byteTmp;
        for (i = 0U; i < (length % 4U); ++i)
        {
            *DAddr_byte = *SAddr_byte;
            DAddr_byte++;
            SAddr_byte++;
        }
    }
}

uint32_t QSPI_ReadSectors(void    *dstAddr,
                          const void *srcOffsetAddr,
                          uint32_t length)
{
    uint32_t Address;
    uint32_t offset = *((const uint32_t *) srcOffsetAddr);
    /* Compute QSPI address and size */
    Address = SOC_QSPI_ADDRSP1_BASE + offset;

    /* Read from QSPI */
    mem1cpy(dstAddr, (void *) Address, length);
    *((uint32_t *) srcOffsetAddr) += (length);

    return TRUE;
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
uint32_t QSPI_WriteSectorsNonBlocking(uint32_t dstOffsetAddr, uint32_t srcAddr,
                                      uint32_t length)
{
    uint32_t Address;
    /* Compute QSPI address and size */
    Address = SOC_QSPI_ADDRSP1_BASE + dstOffsetAddr;
    /* Read from QSPI */
    mem1cpy((void *) Address, (void *) srcAddr, length);

    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

    QSPIConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,QSPI_MMR);

    return TRUE;
}

uint32_t QSPI_WriteSectors(uint32_t dstOffsetAddr, uint32_t srcAddr,
                           uint32_t length)
{
    uint32_t retVal;
    retVal = QSPI_WriteSectorsNonBlocking(dstOffsetAddr, srcAddr, length);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
    return retVal;
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_WriteCfgModeNonBlocking(uint32_t dstOffsetAddr, uint32_t srcAddr,
                                  uint32_t length)
{
    gQspiFlashDevInfo.writeCmd.numDataWords = length;
    gQspiFlashDevInfo.writeCmd.addr         = dstOffsetAddr;
    QSPI_executeCmd(gQspiFlashDevInfo.writeCmd, (uint32_t *) srcAddr);
    gQspiFlashDevInfo.writeCmd.numDataWords = 0;
    gQspiFlashDevInfo.writeCmd.addr         = 0;
}

void QSPI_WriteCfgMode(uint32_t dstOffsetAddr, uint32_t srcAddr,
                       uint32_t length)
{
    QSPI_WriteCfgModeNonBlocking(dstOffsetAddr, srcAddr, length);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

uint32_t QSPI_FlashStatus(void)
{
    uint32_t data;
    QSPI_executeCmd(gQspiFlashDevInfo.flashStatusCmd, &data);
    return (data & 0xFFU);
}

void QSPI_WriteEnable(void)
{
    QSPI_executeCmd(gQspiFlashDevInfo.writeEnableCmd, NULL);
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_QuadEnableNonBlocking(void)
{
    uint32_t data, cmdInfo = 0U;
    uint32_t sr1, cr;
    QSPI_WriteEnable();
    /* Read Ststus register 1 */
    data = QSPI_CMD_RDSR;
    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_FLEN, QSPI_CR_FLEN_2_WORDS);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN, QSPI_CR_WLEN_8_BITS);

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN, QSPI_CR_WLEN_8_BITS);

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
    QSPIreadData(SOC_QSPI_ADDRSP0_BASE, &sr1, (int32_t) 1);
    /* Read Command Register */
    data = QSPI_CMD_RDCR;
    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_FLEN, QSPI_CR_FLEN_2_WORDS);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN, QSPI_CR_WLEN_8_BITS);

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_READ_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN, QSPI_CR_WLEN_8_BITS);

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
    QSPIreadData(SOC_QSPI_ADDRSP0_BASE, &cr, (int32_t) 1);

    /* Set Configuration register 2nd bit to 1 for Quad enable */
    cr |= 0x2U;
    /* write CR register */
    data = ((uint32_t) QSPI_CMD_WRREG << 16U) | (sr1 << 8U) | cr;
    QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, &data, (int32_t) 1);

    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_FLEN, QSPI_CR_FLEN_1_WORD);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                   QSPI_SPI_CMD_REG_CMD_FOUR_PIN_WRITE_SINGLE);
    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN, QSPI_CR_WLEN_24_BITS);

    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);

    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
}

void QSPI_QuadEnable(void)
{
    QSPI_QuadEnableNonBlocking();
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_FlashSubSectorEraseNonBlocking(uint32_t offsetAddr)
{
    gQspiFlashDevInfo.subSectorEraseCmd.numDataWords = 0;
    gQspiFlashDevInfo.subSectorEraseCmd.addr         = offsetAddr;
    QSPI_executeCmd(gQspiFlashDevInfo.subSectorEraseCmd, NULL);
    gQspiFlashDevInfo.subSectorEraseCmd.addr = 0;
}

void QSPI_FlashSubSectorErase(uint32_t offsetAddr)
{
    QSPI_FlashSubSectorEraseNonBlocking(offsetAddr);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

/* flash status should be checked before sending next command
 * Bit 0 of Flash status should be 0 indicating flash is not busy
 * Ex: while ((QSPI_FlashStatus() & 0x01)) ; */
void QSPI_FlashBlockEraseNonBlocking(uint32_t blkNo)
{
    gQspiFlashDevInfo.sectorEraseCmd.numDataWords = 0;
    gQspiFlashDevInfo.sectorEraseCmd.addr         = blkNo * QSPIFLASH_BLOCKSIZE;
    QSPI_executeCmd(gQspiFlashDevInfo.sectorEraseCmd, NULL);
    gQspiFlashDevInfo.sectorEraseCmd.addr = 0;
}

void QSPI_FlashBlockErase(uint32_t blkNo)
{
    QSPI_FlashBlockEraseNonBlocking(blkNo);
    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}
/********************************* End of file ******************************/
