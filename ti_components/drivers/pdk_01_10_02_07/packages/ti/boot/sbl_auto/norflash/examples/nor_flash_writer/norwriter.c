/*
 * TI Booting and Flashing Utilities
 *
 * Main function for flashing the NOR device on the DM644x EVM.
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation version 2.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/tistdtypes.h>
#include <string.h>
#include <device.h>
#include <ti/csl/soc.h>
#include <ti/drv/stw_lld/platform/platform.h>
#include <norwriter.h>
#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
#include <ti/csl/csl_wd_timer.h>
#endif
#include <util.h>

/************************************************************
 * Explicit External Declarations                            *
 ************************************************************/

#define BUF_SIZE (32 * 1024)

/************************************************************
 * Local Macro Declarations                                  *
 ************************************************************/
/* NOR Base address */
#define NOR_BASE    ((UInt32) 0x08000000U)

#define READ_CHUNK      (16 * 1024)

#ifndef FILE_SEEK_SET
#define FILE_SEEK_SET    0   /* set file offset to offset */
#endif
#ifndef FILE_SEEK_CUR
#define FILE_SEEK_CUR    1   /* set file offset to current plus offset */
#endif
#ifndef FILE_SEEK_END
#define FILE_SEEK_END    2   /* set file offset to EOF plus offset */
#endif

/* GPMC CFG values for Spansion S29GL512P11TFI010 & S29GL512N11TFI010
 * This should work for most NOR, else we might have to move
 * these defines to evm.h
 * Values used here are for nominal speed, tweak it to improve performance
 */
#define SPNOR_GPMC_CONFIG1  0x00001010
#define SPNOR_GPMC_CONFIG2  0x00101080
#define SPNOR_GPMC_CONFIG3  0x00020201
#define SPNOR_GPMC_CONFIG4  0x0f031003
#define SPNOR_GPMC_CONFIG5  0x000f1111
#define SPNOR_GPMC_CONFIG6  0x0f030080
#define SPNOR_GPMC_CONFIG7  0x00000C00

#define GPMC_CS0 0

/************************************************************
 * Local Typedef Declarations                                *
 ************************************************************/

/************************************************************
 * Local Function Declarations                               *
 ************************************************************/

static UInt32 norwriter(void);
static int32_t local_DEBUGprintString(const char *s);

/************************************************************
 * Local Function Deefinitions                              *
 ************************************************************/
static int32_t local_DEBUGprintString(const char *s)
{
#if defined (__ARM_ARCH_7A__)
    UARTPuts(s, -1);
#else
    printf(s);
#endif
    return (int32_t) NOR_FLASH_SUCCESS;
}

/************************************************************
 * Local Variable Definitions                                *
 \***********************************************************/

UInt32        NORStartAddr = NOR_BASE;

/* Defines the ROM Code default parameters for NOR/superAND
 * Initializes as 16 bits multiplexed NOR interface without Wait monitoring
 * Timings are set to:
 *  TBD
 */
GPMC_Config_t GPMC_ConfigNorDefault = {
    /* SysConfig - ROM Code defaults */
    0x0,            /* 0x0008, */
    /* IRQEnable - ROM Code defaults */
    0x0000,
    /* TimeOutControl - ROM Code defaults */
    0xf01f0000U,
    /* Config - ROM Code defaults */
    0x000a0000,
    {
        0x41041010,
        0x001E1C01,
        0x00000000,
        0x0F071C03,
        0x041B1F1F,
        0x8F070000U,
        0x00000C08,
    },
    /* PrefetchConfig1 */
    0x0,
    /* PrefetchConfig2 */
    0x0,
    /* PrefetchConfig3 */
    0x0,
};

/************************************************************
 * Global Variable Definitions
 ************************************************************/

/************************************************************
 * Global Function Definitions                               *
 ************************************************************/

int main(void)
{
    UInt32         status;
    Nor_InitPrms_t Nor_InitPrms;
    uint32_t       local_DEBUGprintStringFuncAddr =
        (uint32_t) (&local_DEBUGprintString);

#if defined (SOC_TDA2XX) || defined (SOC_TDA2PX) || defined (SOC_TDA2EX)
    /*Disable the WDTIMER*/
    WDTIMERDisable(SOC_WD_TIMER2_BASE);
#endif

    GPMC_Init(&GPMC_ConfigNorDefault, GPMC_CS0);

    PlatformGPMCSetPinMux();

    /* Init memory alloc pointer to start of DDR heap */
    UTIL_setCurrMemPtr(0);

    memset(&Nor_InitPrms, 0, sizeof (Nor_InitPrms_t));

    /* Initialize function pointer Default */
    NOR_InitParmsDefault(&Nor_InitPrms);

    Nor_InitPrms.norFlashInitPrintFxnPtr =
        (NOR_FlashInitPrintFxnPtr) local_DEBUGprintStringFuncAddr;
    /* Initialize function pointer Default */
    NOR_Init(&Nor_InitPrms);

    /* Execute the NOR flashing */
    status = norwriter();

    if (status != NOR_FLASH_SUCCESS)
    {
        printf("\tNOR flashing failed!\r\n");
    }
    else
    {
        printf("\tNOR boot preparation was successful!\r\n");
    }

    return 0;
}

/************************************************************
 * Local Function Definitions                                *
 ************************************************************/

static UInt32 norwriter(void)
{
    NOR_InfoHandle hNorInfo;
    FILE          *fPtr;
    UInt8         *tmp;
    Int32          fileSize = 0, input;
    char           fileName[512];
    UInt32         baseAddress = 0;
    UInt32         blockSize, blockAddr;
    UInt32         offset;
    Int32          eraseWhole = 0;
    UInt32         retVal     = NOR_FLASH_SUCCESS;
#ifdef USE_SRAM
    Int32          addr_offset = 0;
    Int32          writeSize   = 0;
#else
    UInt8         *filePtr;
    Int32          numBytesRead, totalBytesRead;
#endif

    DEBUG_printString("Starting NOR Flash Writer.\r\n");

    /* Initialize NOR Flash */
    hNorInfo = NOR_open(NORStartAddr, 2U /* 16 Bit */);
    if (hNorInfo == NULL)
    {
        DEBUG_printString("\tERROR: NOR Initialization failed.\r\n");
        retVal = NOR_FLASH_FAIL;
    }

    if (retVal == NOR_FLASH_SUCCESS)
    {
        /* Get NOR block size */
        NOR_getBlockInfo(hNorInfo, NORStartAddr, &blockSize, &blockAddr);

        /* let user enter the offset */
        offset = 0;

        /* Read the file from host */
        printf("\r\nEnter the file path to flash: ");
        scanf("%511s", fileName);

        /* Read the offset from user */
        printf("Enter the Offset in bytes (HEX): ");
        scanf("%x", &offset);

        printf("Erase Options:\r\n---------------\r\n");
        printf("          0 -> Erase Only Required Region\r\n");
        printf("          1 -> Erase Whole Flash\r\n");
        printf("          2 -> Skip Erase \r\n");
        printf("Enter Erase Option:\r\n");
        scanf("%d", &eraseWhole);

        /* Set base address to start putting data at */
        baseAddress = hNorInfo->flashBase + (UInt32) offset;

        /* Open a file from the PC */
        fPtr = fopen(fileName, "rb");
        if (fPtr == NULL)
        {
            DEBUG_printString("\tERROR: File ");
            DEBUG_printString(fileName);
            DEBUG_printString(" open failed.\r\n");
            retVal = NOR_FLASH_FAIL;
        }
    }
    if (retVal == NOR_FLASH_SUCCESS)
    {
        /* Read file size */
        fseek(fPtr, 0, FILE_SEEK_END);
        fileSize = ftell(fPtr);
        if (fileSize == 0)
        {
            DEBUG_printString(

                "\tERROR: File read failed.. Closing program.\r\n");
            fclose(fPtr);
            retVal = NOR_FLASH_FAIL;
        }
    }
    if (retVal == NOR_FLASH_SUCCESS)
    {
        fseek(fPtr, 0, FILE_SEEK_SET);

#ifdef USE_SRAM
        tmp = (UInt8 *) UTIL_allocMem(BUF_SIZE);
#else
        /* Setup pointer in RAM */
        tmp = filePtr = (UInt8 *) UTIL_allocMem((UInt32) fileSize);
#endif
        if (tmp != NULL)
        {
            switch (eraseWhole)
            {
                case 0: /* erase required region */
                    /* Erasing the Flash */
                    if (NOR_erase(hNorInfo, baseAddress,
                                  (UInt32) fileSize) != NOR_FLASH_SUCCESS)
                    {
                        DEBUG_printString(
                            "\tERROR: Erasing NOR failed.\r\n");
                        retVal = NOR_FLASH_FAIL;
                    }
                    break;
                case 1: /* erase whole FLASH */
                    /* Erasing the Flash */
                    if (NOR_erase(hNorInfo, baseAddress,
                                  hNorInfo->flashSize) != NOR_FLASH_SUCCESS)
                    {
                        DEBUG_printString(
                            "\tERROR: Erasing NOR failed.\r\n");
                        retVal = NOR_FLASH_FAIL;
                    }
                    break;
                default:
                    /* Skip erase */
                    DEBUG_printString("\tSkip Erase.\r\n");
                    break;
            }
            if (retVal == NOR_FLASH_SUCCESS)
            {
                printf("Load Options:\r\n-------------\r\n");
                printf("    0 -> fread using code (RTS Library)\r\n");
                printf("    1 -> load raw using CCS (Scripting console)\r\n");
                printf("Enter Load Option: \r\n");
                scanf("%d", &input);
#ifdef USE_SRAM
                addr_offset = 0;
                writeSize   = BUF_SIZE;
                DEBUG_printString("\tStarted Flashing....\r\n");
                while (!feof(fPtr))
                {
                    printf("Reading %d bytes from file...", BUF_SIZE);
                    fflush(stdout);
                    if (!feof(fPtr))
                    {
                        writeSize = (Int32) fread((void *) tmp, (size_t) 1,
                                                  (size_t) BUF_SIZE, fPtr);
                    }
                    printf("\r\n Flashing %d bytes...", BUF_SIZE);
                    /*Write the actual application to the flash*/
                    if (NOR_writeBytes(hNorInfo, (baseAddress + addr_offset),
                                       writeSize,
                                       (UInt32) tmp) != NOR_FLASH_SUCCESS)
                    {
                        DEBUG_printString(
                            "\tERROR: Writing NOR failed.\r\n");
                        retVal = NOR_FLASH_FAIL;
                        break;
                    }

                    addr_offset += writeSize;
                    fflush(stdout);
                }
                if (retVal == NOR_FLASH_SUCCESS)
                {
                    DEBUG_printString("\tCompleted\r\n");
                    DEBUG_printString(
                        "\t!!! Successfully Flashed !!!\r\n");
                    fclose(fPtr);
                }
#else
                if (0 == input)
                {
                    printf("Reading %u bytes from file...\r\n", fileSize);
                    totalBytesRead = 0;
                    while (1)
                    {
                        numBytesRead = (Int32) fread((void *) tmp,
                                                     (size_t) 1,
                                                     (size_t) READ_CHUNK,
                                                     fPtr);
                        tmp += numBytesRead;
                        totalBytesRead += numBytesRead;
                        if (numBytesRead < READ_CHUNK)
                        {
                            break;
                        }
                        printf("Read %d bytes [%d%%] from file...\r\n",
                               totalBytesRead,
                               ((totalBytesRead * 100) / fileSize));
                    }
                    if (fileSize != totalBytesRead)
                    {
                        printf("\tWARNING: File Size mismatch.\r\n");
                    }
                    printf("Read %d bytes [%d%%] from file. Done!!\r\n",
                           totalBytesRead, ((totalBytesRead * 100) / fileSize));
                }
                else
                {
                    printf("Use below command in CCS scripting console...\r\n");
                    printf("loadRaw(0x%.8x, 0, \"%s\", 32, false);\r\n",
                           tmp, fileName);
                    printf("Kindly use '/' (forward slash) in the file ");
                    printf("path\r\n");
                    printf("Enter any alpha-numeric key once ");
                    printf("loadraw is complete...\r\n");
                    scanf("%d", &input);
                }
                fclose(fPtr);

                /* Write the actual application to the flash */
                if (NOR_writeBytes(hNorInfo, baseAddress,
                                   (UInt32) fileSize,
                                   (UInt32) filePtr) != NOR_FLASH_SUCCESS)
                {
                    DEBUG_printString(
                        "\tERROR: Writing NOR failed.\r\n");
                    retVal = NOR_FLASH_FAIL;
                }
                else
                {
                    printf("Done.\r\n");
                    DEBUG_printString(
                        "\t!!! Successfully Flashed !!!\r\n");
                }
#endif
            }
        }
        else
        {
            retVal = NOR_FLASH_FAIL;
        }
        fclose(fPtr);
    }

    return retVal;
}

/***********************************************************
 * End file                                                 *
 ***********************************************************/

/* --------------------------------------------------------------------------
 *  HISTORY
 *      v1.00  -  DJA  -  06-Nov-2007
 *          Completion
 * -----------------------------------------------------------------------------
 * */

