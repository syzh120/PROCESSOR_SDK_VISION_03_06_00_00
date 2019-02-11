/*
 *  Copyright (c) Texas Instruments Incorporated 2017
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *  Redistributions of source code must retain the above copyright
 *  notice, this list of conditions and the following disclaimer.
 *
 *  Redistributions in binary form must reproduce the above copyright
 *  notice, this list of conditions and the following disclaimer in the
 *  documentation and/or other materials provided with the
 *  distribution.
 *
 *  Neither the name of Texas Instruments Incorporated nor the names of
 *  its contributors may be used to endorse or promote products derived
 *  from this software without specific prior written permission.
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
 */

/**
 *  \file CascadeFlashFpga_main.c
 *
 *  \brief Cascade Radar sample application.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

#include <CascadeFlashFpga_main.h>
#include "utils_flash.h"
#include "Serialize.h"

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */

#define APP_SIZE_MAX                (uint32_t) (2U * 1024U * 1024U)
#define APP_READ_BUF_SIZE_MAX       (uint32_t) (256)

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
#define READ_CHUNK      (16U * 1024U)

#define UTILS_FPGA_SELECT_EN_BASE         (SOC_GPIO6_BASE)
#define UTILS_FPGA_SELECT_EN_PIN          (29U)

#define UTILS_FPGA_SELECT_A_BASE         (SOC_GPIO5_BASE)
#define UTILS_FPGA_SELECT_A_PIN          (12U)

#define UTILS_FPGA_SELECT_B_BASE         (SOC_GPIO4_BASE)
#define UTILS_FPGA_SELECT_B_PIN          (17U)

#define UTILS_FPGA_SPI_INSTANCE1          (0U)
#define UTILS_FPGA_SPI_INSTANCE4          (3U)

#define UTILS_FPGA_SELECT_AWR_FPGA_BASE       (SOC_GPIO6_BASE)
#define UTILS_FPGA_SELECT_AWR_FPGA_PIN        (8U)

/* ========================================================================== */
/*                         Structure Declarations                             */
/* ========================================================================== */

/* None */

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */

static void CascadeFlashFpga_createTsk(void);
static void CascadeFlashFpga_tskMain(UArg arg0, UArg arg1);
EDMA3_DRV_Handle edma3init(UInt32 edma3Id, EDMA3_DRV_Result *);

/* ========================================================================== */
/*                            Global Variables                                */
/* ========================================================================== */

/* Align stack memory to integer boundary. */
/* Place the stack in stack section. */
#if defined(__GNUC__) && !defined(__ti__)
DATA_ALIGN(32) DATA_SECTION(".bss:taskStackSection")
#else
#pragma DATA_ALIGN(gCascadeFlashFpgaTskStackMain, 32)
#pragma DATA_SECTION(gCascadeFlashFpgaTskStackMain, ".bss:taskStackSection")
#endif
/* Test application stack */
static uint8_t             gCascadeFlashFpgaTskStackMain[CASCADE_APP_TSK_STACK_MAIN];

static volatile UInt32   gExitApp;

/* Handle to the EDMA driver instance                                         */
EDMA3_DRV_Handle gEdmaHandle;

void * mcspiHandle;

static uint32_t gAppReadBuff[(APP_SIZE_MAX / 4U)];
static uint32_t gAppVerifydBuff[(APP_READ_BUF_SIZE_MAX / 4U)];

/* ========================================================================== */
/*                          Function Definitions                              */
/* ========================================================================== */

/*
 * Application main
 */
int main(void)
{
    static Char stdin_buf[BUFSIZ];

    /* Provide buffer so that STDIO library will use this memory instead of
     * allocating from system heap, which might lead to false system leak
     * warning */
    setvbuf(stdin, stdin_buf, _IOLBF, BUFSIZ);

    /* Create test task */
    CascadeFlashFpga_createTsk();

    /* Start BIOS */
    BIOS_start();

    return (0);
}

/**
 * \brief      Function to initialize the edma driver and get the handle to the
 *             edma driver;
 *
 * \param      arg1  [IN]   unused
 * \param      arg2  [IN]   unused
 *
 * \return     None
 */
static void spiEdmaInit(void)
{
    EDMA3_DRV_Result edmaResult = 0;

    gEdmaHandle = edma3init(0, &edmaResult);

    if (edmaResult != EDMA3_DRV_SOK)
    {
        /* Report EDMA Error */
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME " EDMA driver initialization FAIL\r\n");
    }
    else
    {
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME " EDMA driver initialization PASS.\r\n");
    }
}
/*
 * Create test task
 */
static void CascadeFlashFpga_createTsk(void)
{
    Task_Params tskPrms;

    /* Create test task */
    Task_Params_init(&tskPrms);
    tskPrms.priority      = RADAR_APP_TSK_PRI_MAIN;
    tskPrms.stack         = gCascadeFlashFpgaTskStackMain;
    tskPrms.stackSize     = sizeof (gCascadeFlashFpgaTskStackMain);
    tskPrms.arg0          = (UArg) NULL;
    Task_create(CascadeFlashFpga_tskMain, &tskPrms, NULL);
    return;
}

/*******************************************************************************
Function:     Serialize(const CharStream* char_stream_send,
                    CharStream* char_stream_recv,
                    SpiMasterConfigOptions optBefore,
                    SpiMasterConfigOptions optAfter
                )
Arguments:    char_stream_send, the char stream to be sent from the SPI master to
              the Flash memory, usually contains instruction, address, and data to be
              programmed.
              char_stream_recv, the char stream to be received from the Flash memory
              to the SPI master, usually contains data to be read from the memory.
              optBefore, configurations of the SPI master before any transfer/receive
              optAfter, configurations of the SPI after any transfer/receive
Return Values:TRUE
Description:  This function can be used to encapsulate a complete transfer/receive
              operation
Pseudo Code:
   Step 1  : perform pre-transfer configuration
   Step 2  : perform transfer/ receive
   Step 3  : perform post-transfer configuration
*******************************************************************************/
SPI_STATUS Serialize_SPI(const CharStream* char_stream_send,
                         CharStream* char_stream_recv,
                         SpiConfigOptions optBefore,
                         SpiConfigOptions optAfter
                        )
{

    uint8_t char_send[1024] = {0};
    uint16_t rx_len = 0, tx_len = 0;

#ifdef ENABLE_PRINT_DEBUG
    int i;
    printf("\nSEND: ");
    for(i=0; i<char_stream_send->length; i++)
        printf(" 0x%x ", char_stream_send->pChar[i]);
    printf("\n");
#endif

    tx_len = char_stream_send->length;
    memcpy(char_send, char_stream_send->pChar, tx_len);
    if (NULL_PTR != char_stream_recv)
    {
        rx_len = char_stream_recv->length;
    }
    Bsp_FPGASpiWriteCb(mcspiHandle, char_send, tx_len + rx_len);
    if (NULL_PTR != char_stream_recv)
    {
        memcpy(char_stream_recv->pChar, &char_send[tx_len], rx_len);
    }
#ifdef ENABLE_PRINT_DEBUG
    printf("\nRECV: ");
    for(i=0; i<char_stream_recv->length; i++)
        printf(" 0x%x ", char_stream_recv->pChar[i]);
    printf("\n");
#endif

    return RetSpiSuccess;
}

/*
 * Test task main
 */
static void CascadeFlashFpga_tskMain(UArg arg0, UArg arg1)
{
    FLASH_DEVICE_OBJECT flash_device_object;
    ParameterType para; /* parameters used for all operation */
    char      fileName[FNAME_SZ];
    FILE     *fPtr;
    int32_t   status = BSP_SOK;
    uint32_t i= 0U;
    uint32_t  offset, original_offset, original_fileSize;
    uint32_t  fileSize, numBytesRead, totalBytesRead, input;
    uint32_t  eraseWhole;
    int32_t   option = 1;
    uint8_t  *tmp, *srcAddr;
    uint32_t  blkno;
    uint32_t  eraseSize;
    int32_t  readBlkOffset, readBlkSize, numBlks, lastBlkSize = 0U;
    uint32_t  blkCnt, currentBlkSize, loopBreakFlag = 1U;
    uint32_t *dstAddr;
    uint32_t *srctest, *dsttest;
    uint32_t fpgaNum;

    GT_0trace(BspAppTrace, GT_INFO, APP_NAME "\r\nFPGA SPI Flash writer application\r\n");
    spiEdmaInit();

    status = BspUtils_appDefaultInit(TRUE);
    GT_assert(BspAppTrace, (BSP_SOK == status));

    /* SPI 4 is used for communication with Flash */
    CascadeFlashFpga_InitPadMuxSPIFlash();

    GPIOModuleEnable(UTILS_FPGA_SELECT_EN_BASE);
    GPIODirModeSet(
                UTILS_FPGA_SELECT_EN_BASE,
                UTILS_FPGA_SELECT_EN_PIN,
                GPIO_DIR_OUTPUT);

    GPIOPinWrite(UTILS_FPGA_SELECT_EN_BASE,
                 UTILS_FPGA_SELECT_EN_PIN, 0);
    printf("Enter the FPGA SPI number to flash (0-3) : ");
    scanf("%u", &fpgaNum);
    /* Currently reading from only one flash */
    GPIOModuleEnable(UTILS_FPGA_SELECT_A_BASE);
    GPIOModuleEnable(UTILS_FPGA_SELECT_B_BASE);
    GPIODirModeSet(
                UTILS_FPGA_SELECT_A_BASE,
                UTILS_FPGA_SELECT_A_PIN,
                GPIO_DIR_OUTPUT);
    GPIODirModeSet(
                UTILS_FPGA_SELECT_B_BASE,
                UTILS_FPGA_SELECT_B_PIN,
                GPIO_DIR_OUTPUT);
    switch (fpgaNum)
    {
        case 0:
            GPIOPinWrite(UTILS_FPGA_SELECT_A_BASE,
                         UTILS_FPGA_SELECT_A_PIN, 0);

            GPIOPinWrite(UTILS_FPGA_SELECT_B_BASE,
                         UTILS_FPGA_SELECT_B_PIN, 0);
            GT_0trace(BspAppTrace, GT_INFO, APP_NAME "!!! Ensure J2 on the Cascade board is shorted!!! \n\r");
            break;
        case 1:
            GPIOPinWrite(UTILS_FPGA_SELECT_A_BASE,
                         UTILS_FPGA_SELECT_A_PIN, 1);

            GPIOPinWrite(UTILS_FPGA_SELECT_B_BASE,
                         UTILS_FPGA_SELECT_B_PIN, 0);
            GT_0trace(BspAppTrace, GT_INFO, APP_NAME "!!! Ensure J4 on the Cascade board is shorted!!! \n\r");
            break;
        case 2:
            GPIOPinWrite(UTILS_FPGA_SELECT_A_BASE,
                         UTILS_FPGA_SELECT_A_PIN, 0);

            GPIOPinWrite(UTILS_FPGA_SELECT_B_BASE,
                         UTILS_FPGA_SELECT_B_PIN, 1);
            GT_0trace(BspAppTrace, GT_INFO, APP_NAME "!!! Ensure J6 on the Cascade board is shorted!!! \n\r");
            break;
        case 3:
            GPIOPinWrite(UTILS_FPGA_SELECT_A_BASE,
                         UTILS_FPGA_SELECT_A_PIN, 1);

            GPIOPinWrite(UTILS_FPGA_SELECT_B_BASE,
                         UTILS_FPGA_SELECT_B_PIN, 1);
            GT_0trace(BspAppTrace, GT_INFO, APP_NAME "!!! Ensure J8 on the Cascade board is shorted!!! \n\r");
            break;
        default:
            printf("Incorrect FPGA number !!\n\r");
            status = BSP_EFAIL;
    }
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Init SPI Interface ... \n\r");
    if (status == BSP_SOK)
    {
        if (Bsp_boardGetBaseBoardRev() < BSP_BOARD_REV_E)
        {
            Utils_mcspiInit(UTILS_FPGA_SPI_INSTANCE4);
            mcspiHandle = Bsp_FPGASpiOpenCb(UTILS_FPGA_SPI_INSTANCE4);
        }
        else
        {
            GPIOModuleEnable(UTILS_FPGA_SELECT_AWR_FPGA_BASE);
            GPIODirModeSet(
                        UTILS_FPGA_SELECT_AWR_FPGA_BASE,
                        UTILS_FPGA_SELECT_AWR_FPGA_PIN,
                        GPIO_DIR_OUTPUT);

            GPIOPinWrite(UTILS_FPGA_SELECT_AWR_FPGA_BASE,
                         UTILS_FPGA_SELECT_AWR_FPGA_PIN, 1);

            Utils_mcspiInit(UTILS_FPGA_SPI_INSTANCE1);
            mcspiHandle = Bsp_FPGASpiOpenCb(UTILS_FPGA_SPI_INSTANCE1);
        }
        GT_0trace(BspAppTrace, GT_INFO, APP_NAME " Init SPI Interface done ... \n\r");
        status = (int32_t) Driver_Init(&flash_device_object);
    }
    if (status == BSP_SOK)
    {
        GT_1trace(BspAppTrace, GT_INFO, APP_NAME "\r\nEnter 0 for Erase-Only (without flashing any image)"
               "\r\nNote : File size should be less than %d Bytes."
               "\r\nEnter the file path to flash: ", APP_SIZE_MAX);
        scanf("%511s", fileName);
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
        scanf("%x", &offset);
        printf("Erase Options:\r\n---------------\r\n");
        printf("    0 -> Erase Only Required Region\r\n");
        printf("    1 -> Erase Whole Flash\r\n");
        printf("    2 -> Skip Erase \r\n");
        printf("Enter Erase Option: \r\n");
        scanf("%u", &eraseWhole);

        if (option != 0)
        {
            fPtr = fopen(fileName, "rb");
            if (fPtr == NULL)
            {
                printf("\tERROR: File ");
                printf("%s", fileName);
                printf(" open failed.\r\n");
                status = BSP_EFAIL;
            }

            if (status == BSP_SOK)
            {
                /* Read file size */
                fseek(fPtr, 0, FILE_SEEK_END);
                fileSize = (uint32_t) ftell(fPtr);
                if (fileSize == 0U)
                {
                    printf("\tERROR: File read failed.. Closing program.\r\n");
                    fclose(fPtr);
                    status = BSP_EFAIL;
                }
                /* store filesize for re-use later in verification */
                original_fileSize = fileSize;
            }

            if (status == BSP_SOK)
            {
                fseek(fPtr, 0, FILE_SEEK_SET);

                printf("Load Options:\r\n-------------\r\n");
                printf("    0 -> fread using code (RTS Library)\r\n");
                printf("    1 -> load raw using CCS (Scripting console)\r\n");
                printf("Enter Load Option: \r\n");
                scanf("%u", &input);
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
                    status = BSP_EFAIL;
                }
                fclose(fPtr);
            }
        }
        if (status == BSP_SOK)
        {
            /* Erase the flash as required */
            if (eraseWhole == 1U)
            {
                printf("\r\n SPI Flash whole chip erase in progress\r\n");
                for (i = 0U ; i < flash_device_object.Desc.FlashSectorCount; i++)
                {
                    status = (int32_t)flash_device_object.GenOp.SectorErase(i);
                    if (status != BSP_SOK)
                    {
                        printf("\r\n SPI Sector %d Erase Failed\r\n", i);
                        break;
                    }
                    else
                    {
                        if (i % 64 == 0)
                        {
                            printf("\r\n .");
                        }
                    }
                }
                if (status == BSP_SOK)
                {
                    printf("\r\n SPI Flash Erase completed\r\n");
                }
            }
            else if (eraseWhole == 0U)
            {
                if (option == 0)
                {
                    printf("\r\nEnter number of bytes to erase (HEX): ");
                    scanf("%x", &fileSize);
                }

                if ((fileSize > 0) &&
                    (fileSize < flash_device_object.Desc.FlashSize))
                {
                    printf("\r\n SPI Flash Erase started\r\n");
                    blkno     = offset /
                                flash_device_object.Desc.FlashSubSectorSize;
                    eraseSize = fileSize;
                    while (eraseSize > 0U)
                    {
                        status = (int32_t)
                            flash_device_object.GenOp.SubSectorErase(blkno);
                        blkno++;
                        if (status != BSP_SOK)
                        {
                            printf("\r\n SPI Sub Sector %d Erase Failed\r\n", blkno);
                            break;
                        }
                        else
                        {
                            if (blkno % 64 == 0)
                            {
                                printf("\r\n .");
                            }
                        }
                        if (eraseSize >
                            flash_device_object.Desc.FlashSubSectorSize)
                        {
                            eraseSize -=
                                flash_device_object.Desc.FlashSubSectorSize;
                        }
                        else
                        {
                            break;
                        }
                    }
                    printf("\r\n SPI Flash Erase completed\r\n");
                }
                else
                {
                    printf(
                        "\r\n Number of bytes entered is invalid or greater than SPIFLASH_SIZE (%d) \r\n", flash_device_object.Desc.FlashSize);
                    status = BSP_EFAIL;
                }
            }
            else
            {
                /* Nothing to be done here */
            }
        }
        if ((status == BSP_SOK) && (option != 0))
        {
            uint32_t orgFileSize = fileSize;
            uint32_t count       = 4001U;
            /* Used later for validation */
            srctest = (uint32_t *) srcAddr;
            original_offset = offset;
            printf("\r\n SPI Flash file write started \r\n");
            printf("file size to write: %d Bytes \r\n", fileSize);
            while (fileSize >= 256U)
            {
                /* Write 256 bytes at offset */
                para.PageProgram.udAddr = offset;
                para.PageProgram.pArray = (uint8_t *)srcAddr;
                para.PageProgram.udNrOfElementsInArray = 256;
                flash_device_object.GenOp.DataProgram(PageProgram, &para);
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
                /* Write fileSize bytes at offset */
                para.PageProgram.udAddr = offset;
                para.PageProgram.pArray = (uint8_t *)srcAddr;
                para.PageProgram.udNrOfElementsInArray = fileSize;
                flash_device_object.GenOp.DataProgram(PageProgram, &para);
            }
            printf("\r\n SPI Flash file write completed. Verifying \r\n");

            /* Code to do read-back & verify */
            dstAddr = (uint32_t *) (gAppVerifydBuff);

            /* Read block size for data verification */
            readBlkSize   = APP_READ_BUF_SIZE_MAX;
            readBlkOffset = original_offset;
            numBlks       = original_fileSize / readBlkSize;
            if (original_fileSize > (numBlks * readBlkSize))
            {
                lastBlkSize = original_fileSize - (numBlks * readBlkSize);
                numBlks++;
            }
            loopBreakFlag = 1U;
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
                para.Read.udAddr = readBlkOffset;
                para.Read.pArray = (uint8_t *)dstAddr;
                para.Read.udNrOfElementsToRead = currentBlkSize;
                flash_device_object.GenOp.DataRead(Read, &para);
                readBlkOffset += currentBlkSize;
                for (i = 0; i < (currentBlkSize / 4U); i++)
                {
                    uint32_t dataval = *dsttest;
                    if (*srctest != dataval)
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

        if (status == BSP_SOK)
        {
            printf(
                "\r\n ************SPI Flash flash completed sucessfully************** \r\n");
        }
        else
        {
            printf(
                "\r\n ************SPI Flash flash Failed************** \r\n");
        }

    }
    /* Make the FPGA SPI flash access from TDA OEN high to tristate the output
     * of the mux.
     */
    GPIOPinWrite(UTILS_FPGA_SELECT_EN_BASE,
                 UTILS_FPGA_SELECT_EN_PIN, 1);
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " De-Init SPI Interface ... \n\r");
    Utils_mcspiDeinit(3);
    GT_0trace(BspAppTrace, GT_INFO, APP_NAME " De-Init SPI Interface Done... \n\r");

    BspOsal_sleep(500);
    return;
}
