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
 *  \file st_qspiCommon.c
 *
 *  \brief This file contains all common functions used by the QSPI UT
 *   applications
 *
 */

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <st_qspiCommon.h>
#include <ti/csl/cslr_synctimer.h>

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_dstBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */

/* 4 byte extra to check for corruption */
uint8_t         _dstBuff1[ST_QSPI_FLASH_BLOCK_SIZE + 4U];

#ifdef __cplusplus
#pragma DATA_SECTION(".my_sect_ddr");
#else
#pragma DATA_SECTION(_srcBuff1, ".my_sect_ddr");
#endif  /* #ifdef __cplusplus */

uint8_t         _srcBuff1[ST_QSPI_FLASH_BLOCK_SIZE];

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */
QSPI_FlashDevInfo_t gStQspiFlashDevInfo;
extern uint32_t gStQspiDataPtrCheck;
extern uint32_t gStQspiNumWCInt;
extern uint32_t gStQspiNumFCInt;

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */
/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/* None */
/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/* Read/ Write data for 120/32 bit data width*/
int32_t st_qspiTest_executeCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data)
{
    int32_t  retVal          = STW_SOK;
    uint32_t frameLength     = 0U, cmdInfo = 0U;
    uint32_t localData, i;

    if(gStQspiDataPtrCheck != 1)
    {
        if ((flashCmd.numDataWords != 0) && (NULL == data))
        {
            retVal = STW_EBADARGS;
        }
    }

    if (retVal == STW_SOK)
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
                if (flashCmd.dataType == QSPI_SPI_CMD_REG_CMD_THREE_PIN_WRITE_SINGLE)
                {
                    cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

                    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                                   flashCmd.dataType);

                    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
                    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
                }

                for (i = 0; i < flashCmd.numDataWords; i++)
                {
                    if(flashCmd.numPerDataWordbits == 120U)
                    {
                        QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, data, (int32_t) 4);

                        /*120 bit data width */
                        data = (uint32_t *)((uint8_t *)data + 15);
                    }
                    else
                    {
                        QSPIwriteData(SOC_QSPI_ADDRSP0_BASE, data, (int32_t) 1);

                        if(gStQspiDataPtrCheck == 1)
                        {
                            retVal = STW_EBADARGS;
                            break;
                        }
                        /*32 bit data width */
                        data++;
                    }
                    cmdInfo = QSPIgetCommandReg(SOC_QSPI_ADDRSP0_BASE);

                    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_CMD,
                                   flashCmd.dataType);
                    HW_SET_FIELD32(cmdInfo, QSPI_SPI_CMD_REG_WLEN,
                                  (flashCmd.numPerDataWordbits - 1U));

                    QSPIsetCommandReg(SOC_QSPI_ADDRSP0_BASE, cmdInfo);
                    QSPIWaitIdle(SOC_QSPI_ADDRSP0_BASE);
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

                    if(flashCmd.numPerDataWordbits == 120U)
                    {
                        QSPIreadData(SOC_QSPI_ADDRSP0_BASE, data, (int32_t) 4);
                         /*120 bit data width */
                        data = (uint32_t *)((uint8_t *)data + 15);

                    }
                    else
                    {
                        QSPIreadData(SOC_QSPI_ADDRSP0_BASE, data, (int32_t) 1);

                        if(gStQspiDataPtrCheck == 1)
                        {
                            retVal = STW_EBADARGS;
                            break;
                        }
                        /*32 bit data width */
                        data++;
                    }
                }
            }
        }
    }
    return retVal;
}


void st_qspiTest_readCfgMode(uint32_t dstAddr,
                             uint32_t srcOffsetAddr,
                             uint32_t length)
{
    gStQspiFlashDevInfo.readCmd.numDataWords = length;
    gStQspiFlashDevInfo.readCmd.addr         = srcOffsetAddr;
    st_qspiTest_executeCmd(gStQspiFlashDevInfo.readCmd, (uint32_t *) dstAddr);
    gStQspiFlashDevInfo.readCmd.numDataWords = 0;
    gStQspiFlashDevInfo.readCmd.addr         = 0;

    return;
}

void st_qspiTest_writeCfgModeNonBlocking(uint32_t dstOffsetAddr,
                                         uint32_t srcAddr,
                                         uint32_t length)
{
    gStQspiFlashDevInfo.writeCmd.numDataWords = length;
    gStQspiFlashDevInfo.writeCmd.addr         = dstOffsetAddr;
    st_qspiTest_executeCmd(gStQspiFlashDevInfo.writeCmd, (uint32_t *) srcAddr);
    gStQspiFlashDevInfo.writeCmd.numDataWords = 0;
    gStQspiFlashDevInfo.writeCmd.addr         = 0;
}

void st_qspiTest_writeCfgMode(uint32_t dstOffsetAddr,
                              uint32_t srcAddr,
                              uint32_t length)
{
    uint32_t wordCount, testCnt;

    testCnt = QSPIgetStatusWordCount(DEF_QSPI_MODULE);

    st_qspiTest_writeCfgModeNonBlocking(dstOffsetAddr, srcAddr, length);

    wordCount = QSPIgetStatusWordCount(DEF_QSPI_MODULE);

    wordCount = wordCount - testCnt;

    while(wordCount != (length+1))
    {
        /* Do Nothing - Misra fix */
    }

    /* Wait while Flash is busy */
    while ((QSPI_FlashStatus() & 0x01U) != 0U)
    {
        /* Do Nothing - Misra fix */
    }
}

int32_t st_qspiTest_initFlash(st_QspiTestCfgPrms testCfg,
                              uint32_t          deviceType)
{
    uint32_t deviceId, flashType;
    int32_t  retVal = STW_SOK;

    st_qspiEnableQspiInstance();

    QSPIconfigIdleMode(DEF_QSPI_MODULE, DEF_IDLE_MODE);

    if(testCfg.flashType != DEVICE_TYPE_CUSTOM)
    {

        /*Intialize with default Info*/
        QSPI_Initialize((qspi_DeviceType_e) deviceType);

        /* Update the device type based on actual flash present on board */
        flashType = QSPI_getFlashType((qspi_DeviceType_e) deviceType);

        /* Default initialize for flash type passed */
        retVal = QSPI_GetDefaultFlashDevInfo((qspi_DeviceType_e) flashType,
                                             &gStQspiFlashDevInfo);

        if(retVal != STW_SOK)
        {
            printf("Get QSPI Default Flash Info fails \r\n");
        }
        else
        {
            st_qspiTest_setFlashDevInfo(testCfg, flashType);
        }
    }
    else
    {
        st_qspiTest_setCustomFlashDevInfo(testCfg);
    }

    if(retVal == STW_SOK)
    {
        /* Data read from the Flash in cfg port mode */
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);
        deviceId = QSPI_GetDeviceId();

        printf("MID - %x \r\n", (deviceId & 0xFF));
        printf("DID - %x \r\n", ((deviceId & 0xFF0000) >> 16));
    }

    return retVal;
}

int32_t st_qspiTest_setFlashDevInfo(st_QspiTestCfgPrms   testCfg,
                                    uint32_t              flashType)
{
    int32_t  retVal = STW_SOK;
    QSPI_FlashCmd_t  *testRdcmd;

    testRdcmd = &testCfg.rdCmdCfg.cmd;

    if(testCfg.dataWidth != DEF_DATA_WIDTH)
    {
        gStQspiFlashDevInfo.readCmd.numPerDataWordbits = testCfg.dataWidth;
        gStQspiFlashDevInfo.writeCmd.numPerDataWordbits = testCfg.dataWidth;
    }

    if(testCfg.clockFrequency != DEF_CLK_FREQUENCY)
    {
        gStQspiFlashDevInfo.qspifrequency =
                                    (qspi_ClockFreq_e)(testCfg.clockFrequency);
    }

    if(testCfg.clockMode != DEF_CLK_MODE)
    {
        gStQspiFlashDevInfo.qspiMode = testCfg.clockMode;
    }

    if((testRdcmd->cmd != QSPI_CMD_READ) &&
       (testRdcmd->cmd != QSPI_CMD_FAST_QREAD))
    {
        gStQspiFlashDevInfo.readCmd.cmd = testRdcmd->cmd;
        gStQspiFlashDevInfo.readCmd.numAddrBits = testRdcmd->numAddrBits;
        gStQspiFlashDevInfo.readCmd.numAddrDummyBits = testRdcmd->numAddrDummyBits;
        gStQspiFlashDevInfo.readCmd.dataType = testRdcmd->dataType;
    }

    QSPI_ConfigFlashDevInfo((qspi_DeviceType_e) flashType,
                            &gStQspiFlashDevInfo);

    return retVal;
}


int32_t st_qspiTest_eraseFlash(uint32_t eraseType,
                               uint32_t blockNo,
                               uint32_t sectorNo)
{
    int32_t  retVal = STW_SOK;

    /* Data read from the Flash in cfg port mode */
    QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                      QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
    QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,
                        QSPI_MMR);
    QSPI_WriteEnable();

    printf("Erasing QSPI Flash\r\n");

    if(eraseType == ST_QSPI_BLOCK_ERASE)
    {
        /* Erase the QSPI Flash */
        QSPI_FlashBlockErase(blockNo);
    }
    else if(eraseType == ST_QSPI_FULL_ERASE)
    {
        /* Erase the QSPI Flash */
        QSPI_FlashFullErase();
    }
    else if(eraseType == ST_QSPI_SECTOR_ERASE)
    {
        /* Erase the QSPI Flash */
        QSPI_FlashSubSectorErase(sectorNo);
    }
    else
    {
        /*Do Nothing*/
    }

    printf("Erase Flash Complete\r\n");

    return retVal;
}

int32_t st_qspiTest_verifyFlashData(uint32_t length,
                                    uint32_t enableReadMemMapMode)
{
    int32_t   retVal    = STW_SOK;
    uint32_t  *srctest, *dsttest;
    uint32_t  dataval, i, dataSize;

    dataSize = length%4;

    srctest = (uint32_t *) (_srcBuff1);
    dsttest = (uint32_t *) (_dstBuff1);

    for (i = 0; i < length/4; i++)
    {
        dataval = *dsttest;

        /* For Memory mapped read mode : value will be in Big Endian Mode
         * So Convert to Little Endian Mode */
        if(enableReadMemMapMode == TRUE)
        {
            dataval = (((dataval & 0xFF) << 24) |
                      ((dataval & 0xFF00) << 8) |
                      ((dataval & 0xFF0000) >> 8) |
                      ((dataval & 0xFF000000) >> 24));
        }

        if (*srctest != dataval)
        {
            printf(" Data Read write error at flash location - %x\r\n", (i * 4));
            retVal = STW_EFAIL;
            break;
        }
        srctest++; dsttest++;
    }

    i = i * 4;

    if(dataSize > 0)
    {
        dataval = *dsttest;

        /* For Memory mapped read mode : value will be in Big Endian Mode
         * So Convert to Little Endian Mode */
        if(enableReadMemMapMode == TRUE)
        {
            dataval = (((dataval & 0xFF) << 24) |
                      ((dataval & 0xFF00) << 8) |
                      ((dataval & 0xFF0000) >> 8) |
                      ((dataval & 0xFF000000) >> 24));
        }

        if(dataSize == 1)
        {
            *srctest  = *srctest & 0xFF;
            dataval = dataval & 0xFF;
            i = i + dataSize;
        }
        else if(dataSize == 2)
        {
            *srctest  = *srctest & 0xFFFF;
            dataval = dataval & 0xFFFF;
            i = i + dataSize;
        }
        else
        {
            *srctest  = *srctest & 0xFFFFFF;
            dataval = dataval & 0xFFFFFF;
            i = i + dataSize;
        }

        if (*srctest != dataval)
        {
            printf(" Data Read write error at flash location - %x\r\n", (i * 4));
            retVal = STW_EFAIL;
        }
        srctest++; dsttest++;

    }

    if (i != length)
    {
        retVal = STW_EFAIL;
    }

    return retVal;
}

int32_t st_qspiTest_readFlash(uint32_t length,
                              uint32_t dataWidth,
                              uint32_t enableReadMemMapMode,
                              uint32_t offsetAddr,
                              uint32_t dataTransferMode)
{
    int32_t  retVal = STW_SOK;
    volatile uint32_t dstAddr, srcOffsetAddr;
    uint8_t  *patternRead = (uint8_t *) (_dstBuff1);
    uint32_t numWords, numBytes, numBits;
    uint32_t edmaChNum = 1, edmaTccNum = 1, edmaEventQNum = 0;

    dstAddr       = (uint32_t) patternRead;
    srcOffsetAddr = offsetAddr;

    if((dataTransferMode == ST_QSPI_DMA_MODE) &&
        (enableReadMemMapMode == TRUE))
    {
        /* Change to Memory mapped mode with given chip select */
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,
                            QSPI_CS0);

        EDMAsetRegion(1);
        EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);
        EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHANNEL_TYPE_DMA,
                            edmaChNum,
                            edmaTccNum,
                            edmaEventQNum);

        QSPI_ReadSectors_edma((void *) dstAddr,
                              srcOffsetAddr,
                              length,
                              edmaChNum);
    }

    else if(dataTransferMode == ST_QSPI_POLLED_MODE)
    {
        if (enableReadMemMapMode == TRUE)
        {
            /* Change to Memory mapped mode with given chip select */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                              QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,
                                QSPI_CS0);
            QSPI_ReadSectors((void *) dstAddr,
                             srcOffsetAddr,
                             length);
        }
        else
        {
            if(dataWidth == 8)
            {
                numWords = 256;
            }
            else if(dataWidth == 16)
            {
                numWords = 128;
            }
            else if(dataWidth == 32)
            {
                numWords = 64;
            }
            else if(dataWidth == 64)
            {
                numWords = 32;
            }
            else if(dataWidth == 120)
            {
                numWords = 17;
            }
            else
            {
                numWords = 16;
            }

            while (length >= 256) {

                QSPISetMAddrSpace(
                    SOC_QSPI_ADDRSP0_BASE,
                    QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                QSPI_ConfMAddrSpace(
                    QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);

                if((dataWidth == 120)|| (dataWidth == 32))
                {
                    st_qspiTest_readCfgMode(dstAddr, srcOffsetAddr, numWords);
                }
                else
                {
                    QSPI_ReadCfgMode(dstAddr, srcOffsetAddr, numWords);
                }

                if(ST_QSPI_FLASH_PAGE_SIZE % numWords != 0)
                {
                /* As dataWidth(120) is not multiple of page size. So will write
                   data till multiple of page size( only 255 bytes is read from flash
                   and last byte of flash is ignored for read) and then the remaining
                   bytes will read from next page
                */
                    numBytes = (numWords * dataWidth) / 8;

                    length        -= numBytes;
                    srcOffsetAddr += 256; /* Point to next page*/
                    dstAddr       += numBytes;
                }
                else
                {
                    length        -= 256;
                    srcOffsetAddr += 256;
                    dstAddr       += 256;
                }
            }
            if (length > 0)
            {
                numBits = length * 8;

                QSPISetMAddrSpace(
                    SOC_QSPI_ADDRSP0_BASE,
                    QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                QSPI_ConfMAddrSpace(
                    QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);

                if(numBits < dataWidth)
                {
                    if((dataWidth == 120) || (dataWidth == 32))
                    {
                        st_qspiTest_readCfgMode(dstAddr, srcOffsetAddr, 1U);
                    }
                    else
                    {
                        QSPI_ReadCfgMode(dstAddr, srcOffsetAddr, 1U);
                    }
                }
                else
                {
                    numWords = numBits / dataWidth;

                    if((numBits % dataWidth) != 0)
                    {
                        numWords = numWords + 1;
                    }

                    if(dataWidth == 120)
                    {
                        st_qspiTest_readCfgMode(dstAddr, srcOffsetAddr, numWords);
                    }
                    else
                    {
                        QSPI_ReadCfgMode(dstAddr, srcOffsetAddr, numWords);
                    }

                }

            }
        }
    }
    else
    {
        printf("Invalid Transfer/ Memory Map Mode\r\n");
        retVal = STW_EFAIL;
    }

    return retVal;
}

int32_t st_qspiTest_readFlashWithCheck(uint32_t length,
                                       uint32_t dataWidth,
                                       uint32_t enableReadMemMapMode,
                                       uint32_t offsetAddr,
                                       uint32_t dataTransferMode)
{
    int32_t  retVal = STW_SOK;
    volatile uint32_t dstAddr, srcOffsetAddr;
    uint8_t  *patternRead = (uint8_t *) (_dstBuff1);
    uint32_t *checkPtr;
    uint32_t numWords, numBytes, numBits;
    uint32_t edmaChNum = 1, edmaTccNum = 1, edmaEventQNum = 0;

    memset(patternRead, 0xABU, sizeof(_dstBuff1));
    dstAddr       = (uint32_t) patternRead;
    srcOffsetAddr = offsetAddr;

    if((dataTransferMode == ST_QSPI_DMA_MODE) &&
        (enableReadMemMapMode == TRUE))
    {
        /* Change to Memory mapped mode with given chip select */
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
        QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,
                            QSPI_CS0);

        EDMAsetRegion(1);
        EDMA3Init(SOC_EDMA_TPCC_BASE_VIRT, 0);
        EDMA3RequestChannel(SOC_EDMA_TPCC_BASE_VIRT, EDMA3_CHANNEL_TYPE_DMA,
                            edmaChNum,
                            edmaTccNum,
                            edmaEventQNum);

        QSPI_ReadSectors_edma((void *) dstAddr,
                              srcOffsetAddr,
                              length,
                              edmaChNum);
        checkPtr = (uint32_t *) (dstAddr + length);
        if(*checkPtr != 0xABABABABU)
        {
            printf("Buffer overflow/corruption!!\r\n");
            retVal = STW_EFAIL;
        }
    }
    else if(dataTransferMode == ST_QSPI_POLLED_MODE)
    {
        if (enableReadMemMapMode == TRUE)
        {
            /* Change to Memory mapped mode with given chip select */
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                              QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);
            QSPI_ConfMAddrSpace(QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,
                                QSPI_CS0);
            QSPI_ReadSectors((void *) dstAddr,
                             srcOffsetAddr,
                             length);
            checkPtr = (uint32_t *) (dstAddr + length);
            if(*checkPtr != 0xABABABABU)
            {
                printf("Buffer overflow/corruption!!\r\n");
                retVal = STW_EFAIL;
            }
        }
        else
        {
            if(dataWidth == 8)
            {
                numWords = 256;
            }
            else if(dataWidth == 16)
            {
                numWords = 128;
            }
            else if(dataWidth == 32)
            {
                numWords = 64;
            }
            else if(dataWidth == 64)
            {
                numWords = 32;
            }
            else if(dataWidth == 120)
            {
                numWords = 17;
            }
            else
            {
                numWords = 16;
            }

            while (length >= 256) {
                /* As dataWidth(120) is not multiple of page size. So will write
                   data till multiple of page size( only 255 bytes is read from flash
                   and last byte of flash is ignored for read) and then the remaining
                   bytes will read from next page
                */
                numBytes = (numWords * dataWidth) / 8;

                QSPISetMAddrSpace(
                    SOC_QSPI_ADDRSP0_BASE,
                    QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                QSPI_ConfMAddrSpace(
                    QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);

                if((dataWidth == 120)|| (dataWidth == 32))
                {
                    st_qspiTest_readCfgMode(dstAddr, srcOffsetAddr, numWords);
                }
                else
                {
                    QSPI_ReadCfgMode(dstAddr, srcOffsetAddr, numWords);
                }
                checkPtr = (uint32_t *) (dstAddr + numBytes);
                if(*checkPtr != 0xABABABABU)
                {
                    printf("Buffer overflow/corruption!!\r\n");
                    retVal = STW_EFAIL;
                    break;
                }

                if(ST_QSPI_FLASH_PAGE_SIZE % numWords != 0)
                {
                    length        -= numBytes;
                    srcOffsetAddr += 256; /* Point to next page*/
                    dstAddr       += numBytes;
                }
                else
                {
                    length        -= 256;
                    srcOffsetAddr += 256;
                    dstAddr       += 256;
                }
            }
            if (length > 0)
            {
                numBits = length * 8;

                QSPISetMAddrSpace(
                    SOC_QSPI_ADDRSP0_BASE,
                    QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
                QSPI_ConfMAddrSpace(
                    QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);

                if(numBits < dataWidth)
                {
                    if((dataWidth == 120) || (dataWidth == 32))
                    {
                        st_qspiTest_readCfgMode(dstAddr, srcOffsetAddr, 1U);
                    }
                    else
                    {
                        QSPI_ReadCfgMode(dstAddr, srcOffsetAddr, 1U);
                    }
                    checkPtr = (uint32_t *) (dstAddr + 1U);
                    if(*checkPtr != 0xABABABABU)
                    {
                        printf("Buffer overflow/corruption!!\r\n");
                        retVal = STW_EFAIL;
                    }
                }
                else
                {
                    numWords = numBits / dataWidth;

                    if((numBits % dataWidth) != 0)
                    {
                        numWords = numWords + 1;
                    }

                    if(dataWidth == 120)
                    {
                        st_qspiTest_readCfgMode(dstAddr, srcOffsetAddr, numWords);
                    }
                    else
                    {
                        QSPI_ReadCfgMode(dstAddr, srcOffsetAddr, numWords);
                    }
                    checkPtr = (uint32_t *) (dstAddr + length);
                    if(*checkPtr != 0xABABABABU)
                    {
                        printf("Buffer overflow/corruption!!\r\n");
                        retVal = STW_EFAIL;
                    }
                }
            }
        }
    }
    else
    {
        printf("Invalid Transfer/ Memory Map Mode\r\n");
        retVal = STW_EFAIL;
    }

    return retVal;
}

int32_t st_qspiTest_writeRandomTestPattern()
{
    int32_t  retVal = STW_SOK;
    uint8_t    *patternAddr = (uint8_t *) (_srcBuff1);
    uint32_t   seedVal, i;

    seedVal = HW_RD_REG32(SOC_COUNTER_32K_BASE + COUNTER_32K_CR);
    seedVal = seedVal & 0xFF;

    for (i = 0; i < ST_QSPI_FLASH_BLOCK_SIZE; i++)
    {
        *patternAddr++ = i + 8 + seedVal;
    }

    printf("Writing test pattern to flash Complete....\r\n");
  return retVal;
}

int32_t st_qspiTest_writeFlash(uint32_t length,
                               uint32_t dataWidth,
                               uint32_t offsetAddr)
{
    int32_t  retVal = STW_SOK;
    uint8_t    *patternOrg = (uint8_t *) (_srcBuff1);
    volatile uint32_t   srcAddr, dstOffsetAddr;
    uint32_t numWords, numBytes, numBits;

    if(dataWidth == 8)
    {
        numWords = 256;
    }
    else if(dataWidth == 16)
    {
        numWords = 128;
    }
    else if(dataWidth == 32)
    {
        numWords = 64;
    }
    else if(dataWidth == 64)
    {
        numWords = 32;
    }
    else if(dataWidth == 120)
    {
        numWords = 17;
    }
    else
    {
        numWords = 16;
    }

    /* Write data from DDR location to flash at offset address  */
    srcAddr       = (uint32_t) patternOrg;
    dstOffsetAddr = offsetAddr;

    while (length >= 256)
    {
        QSPISetMAddrSpace(
            SOC_QSPI_ADDRSP0_BASE,
            QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
        QSPI_ConfMAddrSpace(
            QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);

        QSPI_WriteEnable();

        if(dataWidth == 120)
        {
            st_qspiTest_writeCfgMode(dstOffsetAddr, srcAddr, numWords);
        }
        else
        {
            QSPI_WriteCfgMode(dstOffsetAddr, srcAddr, numWords);
        }

        if(ST_QSPI_FLASH_PAGE_SIZE % numWords != 0)
        {
        /* As dataWidth(120) is not multiple of page size. So will write
           data till multiple of page size( only 255 bytes is transferred and
           last byte is ignored for write) and then the remaining bytes will
           transfer from next page
        */
            numBytes = (numWords * dataWidth) / 8;

            length        -= numBytes;
            dstOffsetAddr += 256;  /* Point to next page*/
            srcAddr       += numBytes;
        }
        else
        {
            length        -= 256;
            dstOffsetAddr += 256;
            srcAddr       += 256;
        }
    }
    if (length > 0)
    {
        numBits = length * 8;

        QSPISetMAddrSpace(
            SOC_QSPI_ADDRSP0_BASE,
            QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
        QSPI_ConfMAddrSpace(
            QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);

        QSPI_WriteEnable();

        if(numBits < dataWidth)
        {
            if(dataWidth == 120)
            {
                st_qspiTest_writeCfgMode(dstOffsetAddr, srcAddr, 1U);
            }
            else
            {
                QSPI_WriteCfgMode(dstOffsetAddr, srcAddr, 1U);
            }
        }
        else
        {
            numWords = numBits / dataWidth;

            if((numBits % dataWidth) != 0)
            {
                numWords = numWords + 1;
            }

            if(dataWidth == 120)
            {
                st_qspiTest_writeCfgMode(dstOffsetAddr, srcAddr, numWords);
            }
            else
            {
                QSPI_WriteCfgMode(dstOffsetAddr, srcAddr, numWords);
            }
        }
    }

    return retVal;
}

int32_t st_qspiTest_deInitFlash()
{
    int32_t  retVal = STW_SOK;

    QSPI_DeInitialize();

    return retVal;
}

int32_t st_qspiTest_setCustomFlashDevInfo(st_QspiTestCfgPrms   testCfg)
{
    int32_t  retVal = STW_SOK;

    gStQspiFlashDevInfo.flashType = (qspi_DeviceType_e) testCfg.flashType;
    gStQspiFlashDevInfo.numDatalines = testCfg.numDataLines;
    gStQspiFlashDevInfo.qspiMode = testCfg.clockMode;
    gStQspiFlashDevInfo.qspiCs = 0U;
    gStQspiFlashDevInfo.dataDelay = QSPI_SPI_DC_REG_DD_CS_TO_DATA_DELAY_0;
    gStQspiFlashDevInfo.qspifrequency = (qspi_ClockFreq_e)testCfg.clockFrequency;

    memcpy(&gStQspiFlashDevInfo.idCmd,
           &testCfg.idCmdCfg.cmd,
           sizeof (QSPI_FlashCmd_t));

    memcpy(&gStQspiFlashDevInfo.readCmd,
           &testCfg.rdCmdCfg.cmd,
           sizeof (QSPI_FlashCmd_t));

    memcpy(&gStQspiFlashDevInfo.writeCmd,
           &testCfg.wrCmdCfg.cmd,
           sizeof (QSPI_FlashCmd_t));

    memcpy(&gStQspiFlashDevInfo.sectorEraseCmd,
           &testCfg.sectEraseCmdCfg.cmd,
           sizeof (QSPI_FlashCmd_t));

    memcpy(&gStQspiFlashDevInfo.subSectorEraseCmd,
           &testCfg.subSectEraseCmdCfg.cmd,
           sizeof (QSPI_FlashCmd_t));

    memcpy(&gStQspiFlashDevInfo.fullEraseCmd,
           &testCfg.fullEraseCmdCfg.cmd,
           sizeof (QSPI_FlashCmd_t));

    memcpy(&gStQspiFlashDevInfo.flashStatusCmd,
           &testCfg.statCmdCfg.cmd,
           sizeof (QSPI_FlashCmd_t));

    memcpy(&gStQspiFlashDevInfo.writeEnableCmd,
           &testCfg.wrEnCmdCfg.cmd,
           sizeof (QSPI_FlashCmd_t));

    gStQspiFlashDevInfo.qspiFlashInitFxn = &QSPI_SpansionFlashInit;

    QSPI_ConfigFlashDevInfo((qspi_DeviceType_e) gStQspiFlashDevInfo.flashType,
                            &gStQspiFlashDevInfo);

    if(testCfg.numDataLines == 4U)
    {
        QSPI_QuadEnable();
    }

    return retVal;
}

void st_qspiTest_isr_wc_fc()
{
    uint32_t intStatus;

    intStatus = QSPIintStatus(SOC_QSPI_ADDRSP0_BASE);

    if((intStatus & QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK) ==
        QSPI_INTR_ENABLE_SET_REG_WIRQ_ENA_SET_MASK)
    {
        gStQspiNumWCInt++;
    }

    if((intStatus & QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK) ==
        QSPI_INTR_ENABLE_SET_REG_FIRQ_ENA_SET_MASK)
    {
        gStQspiNumFCInt++;
    }

    QSPIintClear(SOC_QSPI_ADDRSP0_BASE, intStatus);
}
