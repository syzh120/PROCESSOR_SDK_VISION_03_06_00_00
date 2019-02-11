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

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <ti/csl/csl_qspi.h>
#include <ti/boot/sbl_auto/qspiflash/qspi_flash.h>
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#include <ti/csl/csl_wd_timer.h>
#endif
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <ti/csl/csl_types.h>


/* When 'USER_INPUT' is commented, user input is skipped and
 * values specified by USER_INPUT_xxx are used instead
 */
/* Uncomment below to take user input */
#define USER_INPUT

#define USER_INPUT_FLASH_TYPE     (2U)
#define USER_INPUT_FILE_NAME      "D:/ked/ADAS/code/vision_sdk/binaries/tda3xx_evm_bios_radar/vision_sdk/bin/tda3xx-evm/sbl_boot/AppImage_BE"
#define USER_INPUT_QSPI_OFFSET    (0x80000)
#define USER_INPUT_ERASE_TYPE     (0U)
#define USER_INPUT_FILE_READ_MODE (1U)


int32_t qspiwriter(void);
#define READ_CHUNK      (16U * 1024U)
#define QSPIFLASH_SIZE  (32U * 1024U * 1024U)
#define APP_SIZE_MAX                (uint32_t) (32U * 1024U * 1024U)
#define APP_READ_BUF_SIZE_MAX       (uint32_t) (0x1000000)

#ifndef FILE_SEEK_SET
#define FILE_SEEK_SET    0   /* set file offset to offset */
#endif
#ifndef FILE_SEEK_CUR
#define FILE_SEEK_CUR    1   /* set file offset to current plus offset */
#endif
#ifndef FILE_SEEK_END
#define FILE_SEEK_END    2   /* set file offset to EOF plus offset */
#endif
#define FNAME_SZ         (512U)

static uint32_t gAppReadBuff[(APP_SIZE_MAX / 4U)];
static uint32_t gAppVerifydBuff[(APP_READ_BUF_SIZE_MAX / 4U)];

int main(void) {
    qspi_DeviceType_e DeviceType = DEVICE_TYPE_CUSTOM;
    volatile uint32_t dstAddr, srcOffsetAddr;
    volatile uint32_t srcAddr, dstOffsetAddr;
    volatile uint32_t length = 10U;
    uint32_t          device_Id, usrInputFlashType;

    printf("\r\nQSPI Flash writer application");

    PlatformUnlockMMR();

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /*Disable the WDTIMER*/
    WDTIMERDisable(SOC_WD_TIMER2_BASE);
#endif
    while (1)
    {
        printf(
            "\r\nEnter Device type to use\
                \r\n1 - 1 bit read from flash\
                \r\n2 - 4 bit (Quad) read from flash\
                \r\n$ > ");

        #ifdef USER_INPUT
        scanf("%u", &usrInputFlashType);
        #else
        usrInputFlashType = USER_INPUT_FLASH_TYPE;
        #endif
        if (usrInputFlashType == 1U)
        {
            DeviceType = DEVICE_TYPE_QSPI1;
        }
        else if (usrInputFlashType == 2U)
        {
            DeviceType = DEVICE_TYPE_QSPI4;
        }
        else
        {
            printf("\r\nInvalid Input Please try again\r\n");
        }
        if (DeviceType != DEVICE_TYPE_CUSTOM)
        {
            break;
        }
    }

    /* Configure PADs. */
    PlatformQSPISetPinMux();

    QSPI_Initialize(DeviceType);

    device_Id = QSPI_GetDeviceId();

    printf("\r\nMID - ");
    printf("%x", (device_Id & 0xFFU));
    printf("\r\nDID - ");
    printf("%x", (device_Id & 0xFF0000U) >> 16);

    qspiwriter();
    return 0;
}

int32_t qspiwriter(void)
{
    char      fileName[FNAME_SZ];
    FILE     *fPtr;
    uint32_t  original_offset, original_fileSize;
    uint32_t  offset, fileSize, numBytesRead, totalBytesRead, input;
    uint32_t  eraseWhole;
    uint8_t  *tmp, *srcAddr;
    uint32_t *dstAddr;
    uint32_t *srctest, *dsttest;
    uint32_t  blkno;
    uint32_t  eraseSize;
    int32_t   option = 1;
    int32_t   retVal = STW_SOK;
    uint32_t  i;
    uint32_t  readBlkOffset, readBlkSize, numBlks, lastBlkSize = 0U;
    uint32_t  blkCnt, currentBlkSize, loopBreakFlag = 1U;

    memset((void *) fileName, (int32_t) 0U, sizeof (fileName));
    printf("\r\nEnter 0 for Erase-Only (without flashing any image)"
           "\r\nNote : File size should be less than %d Bytes."
           "\r\nEnter the file path to flash: ", APP_SIZE_MAX);
    #ifdef USER_INPUT
    scanf("%511s", fileName);
    #else
    strcpy(fileName, USER_INPUT_FILE_NAME);
    #endif

    if ((fileName[0] == (char) '0') && (((uint32_t)fileName[1]) == 0x0))
    {
        /* Set option variable to '0' to erase without flashing */
        option = 0;
    }
    for (i = 0; i < (sizeof (fileName) - 1U); i++)
    {
        if (fileName[i] == (char) '\\')
        {
            if (i != sizeof (fileName))
            {
                if (fileName[i + 1U] != (char) '\\')
                {
                    fileName[i] = (char) '/';
                }
            }
        }
    }

    /* Read the offset from user */
    printf("Enter the Offset in bytes (HEX): ");
    #ifdef USER_INPUT
    scanf("%x", &offset);
    #else
    offset = USER_INPUT_QSPI_OFFSET;
    #endif
    /* store offset for re-use later in verification */
    original_offset = offset;

    printf("Erase Options:\r\n---------------\r\n");
    printf("    0 -> Erase Only Required Region\r\n");
    printf("    1 -> Erase Whole Flash\r\n");
    printf("    2 -> Skip Erase \r\n");
    printf("Enter Erase Option: \r\n");
    #ifdef USER_INPUT
    scanf("%u", &eraseWhole);
    #else
    eraseWhole = USER_INPUT_ERASE_TYPE;
    #endif

    if (option != 0)
    {
        fPtr = fopen(fileName, "rb");
        if (fPtr == NULL)
        {
            printf("\tERROR: File ");
            printf("%s", fileName);
            printf(" open failed.\r\n");
            retVal = STW_EFAIL;
        }

        if (retVal == STW_SOK)
        {
            /* Read file size */
            fseek(fPtr, 0, FILE_SEEK_END);
            fileSize = (uint32_t) ftell(fPtr);
            if (fileSize == 0U)
            {
                printf("\tERROR: File read failed.. Closing program.\r\n");
                fclose(fPtr);
                retVal = STW_EFAIL;
            }
            /* store filesize for re-use later in verification */
            original_fileSize = fileSize;
        }

        if (retVal == STW_SOK)
        {
            fseek(fPtr, 0, FILE_SEEK_SET);

            printf("Load Options:\r\n-------------\r\n");
            printf("    0 -> fread using code (RTS Library)\r\n");
            printf("    1 -> load raw using CCS (Scripting console)\r\n");
            printf("Enter Load Option: \r\n");
            #ifdef USER_INPUT
            scanf("%u", &input);
            #else
            input = USER_INPUT_FILE_READ_MODE;
            #endif
            srcAddr = tmp = (uint8_t *) (gAppReadBuff);

            if (APP_SIZE_MAX >= fileSize)
            {
                if (0U == input)
                {
                    printf("Reading %u bytes from file...\r\n", fileSize);
                    totalBytesRead = 0U;
                    while (1)
                    {
                        numBytesRead =
                            fread((void *) tmp, (size_t) 1, READ_CHUNK,
                                  fPtr);
                        tmp += numBytesRead;
                        totalBytesRead += numBytesRead;
                        if (numBytesRead < READ_CHUNK)
                        {
                            break;
                        }
                        printf("Read %d bytes [%d%%] from file...\r\n",
                               totalBytesRead,
                               ((totalBytesRead * 100U) / fileSize));
                    }
                    if (fileSize != totalBytesRead)
                    {
                        printf("\tWARNING: File Size mismatch.\r\n");
                    }
                    printf("Read %d bytes [%d%%] from file. Done!!\r\n",
                           totalBytesRead, ((totalBytesRead * 100U) / fileSize));
                }
                else
                {
                    printf("Use below command in CCS scripting console...\r\n");
                    printf("loadRaw(0x%.8x, 0, \"%s\", 32, false);\r\n",
                           srcAddr,
                           fileName);
                    printf(
                        "Kindly use '/' (forward slash) in the file path\r\n");
                    printf(
                        "Enter any alpha-numeric key once loadraw is complete...\r\n");
                    scanf("%u", &input);
                }
            }
            else
            {
                printf(
                    "Given file can not be read into memory since it's size exceeds the allowed memory limit...\r\n");
                retVal = STW_EFAIL;
            }
            fclose(fPtr);

            blkno = offset / QSPIFLASH_BLOCKSIZE;
        }
    }

    if (retVal == STW_SOK)
    {
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

        QSPI_ConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,
                            QSPI_MMR);

        /* Erase the flash as required */
        if (eraseWhole == 1U)
        {
            printf("\r\n QSPI whole chip erase in progress\r\n");
            QSPI_WriteEnable();
            QSPI_FlashFullErase();
            printf("\r\n QSPI Erase completed\r\n");
        }
        else if (eraseWhole == 0U)
        {
            if (option == 0)
            {
                printf("\r\nEnter number of bytes to erase (HEX): ");
                scanf("%x", &fileSize);
            }

            if ((fileSize > 0) && (fileSize < QSPIFLASH_SIZE))
            {
                printf("\r\n QSPI Erase started\r\n");
                blkno     = offset / QSPIFLASH_BLOCKSIZE;
                eraseSize = fileSize;
                while (eraseSize > 0U)
                {
                    QSPI_WriteEnable();
                    QSPI_FlashBlockErase(blkno);
                    blkno++;

                    if (eraseSize > QSPIFLASH_BLOCKSIZE)
                    {
                        eraseSize -= QSPIFLASH_BLOCKSIZE;
                    }
                    else
                    {
                        break;
                    }
                }
                printf("\r\n QSPI Erase completed\r\n");
            }
            else
            {
                printf(
                    "\r\n Number of bytes entered is invalid or greater than QSPIFLASH_SIZE(32MB) \r\n");
                retVal = STW_EFAIL;
            }
        }
        else
        {
            /* Nothing to be done here */
        }
    }

    if ((retVal == STW_SOK) && (option != 0))
    {
        uint32_t orgFileSize = fileSize;
        uint32_t count       = 4001U;
        printf("\r\n QSPI file write started \r\n");
        printf("file size to write: %d Bytes \r\n", fileSize);
        while (fileSize >= 256U)
        {
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                              (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
            QSPI_ConfMAddrSpace(
                (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);
            QSPI_WriteEnable();
            QSPI_WriteCfgMode(offset, (uint32_t) srcAddr, 64U);
            fileSize -= 256U;
            offset   += 256U;
            srcAddr  += 256U;
            if ((count % 4000U) == 0U)
            {
                /* Update write status after 1MB write */
                printf("written %d Bytes: [%d%%] \r\n", (orgFileSize - fileSize),
                       (((orgFileSize - fileSize) * 100U) / orgFileSize));
            }
            count++;
        }
        if (fileSize > 0U)
        {
            QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                              (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);
            QSPI_ConfMAddrSpace(
                (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT, QSPI_MMR);
            QSPI_WriteEnable();
            QSPI_WriteCfgMode(offset, (uint32_t) srcAddr,
                              (fileSize / 4U) + 1U);
        }
        printf("\r\n QSPI file write completed. Verifying \r\n");

        /* Change to Memory mapped mode with given chip select */
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT);

        QSPI_ConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_CFG_PORT,
                            QSPI_MMR);

        /* Code to do read-back & verify */
        dstAddr = (uint32_t *) (gAppVerifydBuff);

        /* Read block size for data verification- this is due to
         * limited memory on tda3xx 12X12 package */
        readBlkSize   = APP_READ_BUF_SIZE_MAX;
        readBlkOffset = original_offset;
        numBlks       = original_fileSize / readBlkSize;
        if (original_fileSize > (numBlks * readBlkSize))
        {
            lastBlkSize = original_fileSize - (numBlks * readBlkSize);
            numBlks++;
        }

        /* Change to Memory mapped mode with given chip select */
        QSPISetMAddrSpace(SOC_QSPI_ADDRSP0_BASE,
                          (uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT);

        QSPI_ConfMAddrSpace((uint8_t) QSPI_SPI_SWITCH_REG_MMPT_S_SEL_MM_PORT,
                            QSPI_CS0);

        srctest = (uint32_t *) (gAppReadBuff);     /* same as hardcoded source
                                                    * address
                                                    *above */
        for (blkCnt = 0; blkCnt < numBlks; blkCnt++)
        {
            if (1U != loopBreakFlag)
            {
                break;
            }
            dsttest = dstAddr;
            if (blkCnt < (numBlks - 1U))
            {
                currentBlkSize = readBlkSize;
            }
            else
            {
                currentBlkSize = lastBlkSize;
            }
            QSPI_ReadSectors((void *) dstAddr, readBlkOffset, currentBlkSize);
            readBlkOffset += currentBlkSize;
            for (i = 0; i < (currentBlkSize / 4U); i++)
            {
                uint32_t dataval = *dsttest;
                if (*srctest !=
                    (((dataval & 0xFFU) << 24) | ((dataval & 0xFF00U) << 8) |
                     ((dataval &
                       0xFF0000U) >> 8) | ((dataval & 0xFF000000U) >> 24)))
                {
                    printf(
                        "\r\n Data Read write error at flash location - 0x%x\r\n",
                        (((readBlkOffset - currentBlkSize) + (i * 4U))
                         - original_offset));
                    loopBreakFlag = 0U;
                    break;
                }
                srctest++; dsttest++;
            }
        }
    }

    if (retVal == STW_SOK)
    {
        printf(
            "\r\n ************QSPI flash completed sucessfully************** \r\n");
    }
    else
    {
        printf(
            "\r\n ************QSPI flash Failed************** \r\n");
    }

    {
        volatile uint8_t spin = 1U;
        while (spin)
        {
            /* Busy Loop*/
        }
    }

    return retVal;
}

