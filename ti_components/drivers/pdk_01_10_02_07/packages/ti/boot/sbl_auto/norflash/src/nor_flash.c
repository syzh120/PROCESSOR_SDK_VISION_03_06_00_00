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
#include <stddef.h>
#include <string.h>
#include <ti/boot/sbl_auto/norflash/nor_flash.h>
#include <ti/boot/sbl_auto/norflash/src/debug.h>
#include <ti/csl/csl_types.h>
#include <ti/csl/tistdtypes.h>

#define FLASH_WAIT_LOOP ((uint32_t) (500))

NOR_InfoObj    gNorInfoObj;
Nor_InitPrms_t gNor_InitPrms;

static void LOCAL_waitLoop(uint32_t loopcnt);

static volatile uint8_t *LOCAL_flashMakeAddr(NOR_InfoHandle hNorInfo,
                                             uint32_t       blkAddr,
                                             uint32_t       offset);
static void LOCAL_flashMakeCmd(NOR_InfoHandle hNorInfo, uint32_t cmd,
                               void *cmdbuf);
static void LOCAL_flashWriteCmd(NOR_InfoHandle hNorInfo, uint32_t blkAddr,
                                uint32_t offset,
                                uint32_t cmd);
static void LOCAL_flashWriteData(NOR_InfoHandle hNorInfo, uint32_t address,
                                 uint32_t data);
static uint32_t LOCAL_flashVerifyDataBuffer(NOR_InfoHandle hNorInfo,
                                            uint32_t       address,
                                            volatile void *data,
                                            uint32_t       numBytes);
uint32_t LOCAL_flashReadData(NOR_InfoHandle hNorInfo, uint32_t address,
                             uint32_t offset);
static Bool LOCAL_flashIsSetAll(NOR_InfoHandle hNorInfo, uint32_t blkAddr,
                                uint32_t offset,
                                uint32_t mask);
static Bool LOCAL_flashIsSetSome(NOR_InfoHandle hNorInfo, uint32_t blkAddr,
                                 uint32_t offset,
                                 uint32_t mask);
static NOR_Data LOCAL_flashReadCFIBytes(NOR_InfoHandle hNorInfo,
                                        uint32_t       offset,
                                        uint32_t       numBytes);
static Bool LOCAL_flashCFIIsEqual(NOR_InfoHandle hNorInfo, uint32_t offset,
                                  uint32_t val);

/* Flash Identification and discovery */
static uint32_t   LOCAL_flashQueryCFI(NOR_InfoHandle hNorInfo);

/* Generic commands that will point to either AMD or Intel command set*/
static uint32_t (*Flash_Write)(NOR_InfoHandle hNorInfo, uint32_t address,
                               volatile uint32_t length);
static uint32_t (*Flash_BufferWrite)(NOR_InfoHandle   hNorInfo,
                                     uint32_t         writeAddress,
                                     volatile uint8_t readAddress[],
                                     uint32_t         length);
static uint32_t (*Flash_Erase)(NOR_InfoHandle hNorInfo, uint32_t address);
static uint32_t (*Flash_ID)(NOR_InfoHandle hNorInfo);

/* Empty commands for when neither command set is used */
static uint32_t   Unsupported_Erase(NOR_InfoHandle hNorInfo, uint32_t address);
static uint32_t   Unsupported_Write(NOR_InfoHandle hNorInfo, uint32_t address,
                                    volatile uint32_t data);
static uint32_t   Unsupported_BufferWrite(NOR_InfoHandle   hNorInfo,
                                          uint32_t         address,
                                          volatile uint8_t data[],
                                          uint32_t         length);
static uint32_t   Unsupported_ID(NOR_InfoHandle hNorInfo);

/*Intel pointer-mapped commands */
static uint32_t   Intel_Erase(NOR_InfoHandle    hNorInfo,
                              volatile uint32_t blkAddr);
static uint32_t   Intel_Write(NOR_InfoHandle hNorInfo, uint32_t address,
                              volatile uint32_t data);
static uint32_t   Intel_BufferWrite(NOR_InfoHandle hNorInfo, uint32_t address,
                                    volatile uint8_t data[],
                                    uint32_t numBytes);
static uint32_t   Intel_ID(NOR_InfoHandle hNorInfo);
/* Misc. Intel commands */
static uint32_t   LOCAL_IntelClearLock(NOR_InfoHandle hNorInfo,
                                       uint32_t       blkAddr);
static uint32_t   LOCAL_IntelLockStatusCheck(NOR_InfoHandle hNorInfo);
static void     LOCAL_IntelSoftReset(NOR_InfoHandle hNorInfo);
static void     LOCAL_IntelClearStatus(NOR_InfoHandle hNorInfo);
static void     LOCAL_IntelWaitForStatusComplete(NOR_InfoHandle hNorInfo);

/*AMD pointer-mapped commands */
static uint32_t   AMD_Erase(NOR_InfoHandle hNorInfo, uint32_t blkAddr);
static uint32_t   AMD_Write(NOR_InfoHandle hNorInfo, uint32_t address,
                            volatile uint32_t data);
static uint32_t   AMD_BufferWrite(NOR_InfoHandle hNorInfo, uint32_t address,
                                  volatile uint8_t data[],
                                  uint32_t numBytes);
static uint32_t   AMD_ID(NOR_InfoHandle hNorInfo);
/* Misc. AMD commands */
static void     LOCAL_AMDSoftReset(NOR_InfoHandle hNorInfo);
static void     LOCAL_AMDPrefixCommands(NOR_InfoHandle hNorInfo);
static void     LOCAL_AMDWriteBufAbortReset(NOR_InfoHandle hNorInfo);

void NOR_InitParmsDefault(Nor_InitPrms_t *pNor_InitPrms)
{
    if (pNor_InitPrms != NULL)
    {
        pNor_InitPrms->norFlashInitPrintFxnPtr = NULL;
    }
}

void NOR_Init(const Nor_InitPrms_t *pNor_InitPrms)
{
    if (pNor_InitPrms->norFlashInitPrintFxnPtr != NULL)
    {
        gNor_InitPrms.norFlashInitPrintFxnPtr =
            pNor_InitPrms->norFlashInitPrintFxnPtr;
    }
}

NOR_InfoHandle NOR_open(uint32_t baseCSAddr, uint8_t busWidth)
{
    /* Use the global Nor Handle */
    /* Only one handle supported */
    NOR_InfoHandle hNorInfo         = &gNorInfoObj;
    char           flashSizeStr[10] = {0};
    uint32_t       flashSize;

    memset(hNorInfo, 0, sizeof (NOR_InfoObj));

    /* Set NOR flash base address*/
    hNorInfo->flashBase = baseCSAddr;

    hNorInfo->CSOffset = 0;

    /* Set width to 8 or 16 */
    hNorInfo->busWidth = busWidth;

    if ((busWidth != (uint8_t) BUS_8BIT) && (busWidth != (uint8_t) BUS_16BIT))
    {
        DEBUG_printString("Bus Width Not supported .\r\n");
        hNorInfo = NULL;
    }
    else
    {
        /* Try both Intel and AMD resets ( we don't know yet which we need) */
        LOCAL_AMDSoftReset(hNorInfo);
        LOCAL_IntelSoftReset(hNorInfo);
        /* Perform CFI Query */
        DEBUG_printString("CFI Query...");
        if (LOCAL_flashQueryCFI(hNorInfo) != NOR_FLASH_SUCCESS)
        {
            DEBUG_printString("failed.\r\n");
            hNorInfo = NULL;
        }
        else
        {
            /* Setup function pointers */
            DEBUG_printString("passed.\r\nNOR Initialization:\r\n");

            DEBUG_printString("\tCommand Set: ");
            switch (hNorInfo->commandSet)
            {
                case AMD_BASIC_CMDSET:
                case AMD_EXT_CMDSET:
                    Flash_Erase       = &AMD_Erase;
                    Flash_BufferWrite = &AMD_BufferWrite;
                    Flash_Write       = &AMD_Write;
                    Flash_ID          = &AMD_ID;
                    DEBUG_printString("Spansion\r\n");
                    break;
                case INTEL_BASIC_CMDSET:
                case INTEL_EXT_CMDSET:
                    Flash_Erase       = &Intel_Erase;
                    Flash_BufferWrite = &Intel_BufferWrite;
                    Flash_Write       = &Intel_Write;
                    Flash_ID          = &Intel_ID;
                    DEBUG_printString("Intel\r\n");
                    break;
                default:
                    Flash_Write       = &Unsupported_Write;
                    Flash_BufferWrite = &Unsupported_BufferWrite;
                    Flash_Erase       = &Unsupported_Erase;
                    Flash_ID          = &Unsupported_ID;
                    DEBUG_printString("Unknown\r\n");
                    break;
            }

            if ((*Flash_ID)(hNorInfo) != NOR_FLASH_SUCCESS)
            {
                DEBUG_printString("NOR ID failed.\r\n");
                hNorInfo = NULL;
            }
            else
            {
                DEBUG_printString("\tManufacturer: ");
                switch (hNorInfo->manfID)
                {
                    case AMD:
                        DEBUG_printString("SPANSION");
                        break;
                    case FUJITSU:
                        DEBUG_printString("FUJITSU");
                        break;
                    case INTEL:
                        DEBUG_printString("INTEL");
                        break;
                    case MICRON:
                        DEBUG_printString("MICRON");
                        break;
                    case SAMSUNG:
                        DEBUG_printString("SAMSUNG");
                        break;
                    case SHARP:
                        DEBUG_printString("SHARP");
                        break;
                    default:
                        DEBUG_printString("Unknown");
                        break;
                }
                DEBUG_printString("\r\n");
                DEBUG_printString("\tSize: ");
                flashSize = hNorInfo->flashSize >> (uint32_t) 20;
                DEBUG_ConvertHexToString(flashSize, flashSizeStr, 10);
                DEBUG_printString(flashSizeStr);
                DEBUG_printString(" MB\r\n");
            }
        }
    }
    return hNorInfo;
}

/* Get info on block address and sizes */
uint32_t NOR_getBlockInfo(NOR_InfoHandle hNorInfo, uint32_t address,
                          uint32_t *blockSize,
                          uint32_t *blockAddr)
{
    int32_t  i;
    uint32_t currRegionAddr, nextRegionAddr;
    uint32_t retVal = NOR_FLASH_SUCCESS;

    currRegionAddr = (uint32_t) hNorInfo->flashBase;
    if ((address < currRegionAddr) ||
        (address >= (currRegionAddr + hNorInfo->flashSize)))
    {
        retVal = NOR_FLASH_FAIL;
    }
    else
    {
        for (i = 0; i < (hNorInfo->numberRegions); i++)
        {
            nextRegionAddr = currRegionAddr +
                             (hNorInfo->blockSize[i] *
                              hNorInfo->numberBlocks[i]);
            if ((currRegionAddr <= address) && (nextRegionAddr > address))
            {
                *blockSize = hNorInfo->blockSize[i];
                *blockAddr = address & (~((*blockSize) - 1U));
                break;
            }
            currRegionAddr = nextRegionAddr;
        }
    }
    return retVal;
}

/*Global Erase NOR Flash*/
uint32_t NOR_globalErase(NOR_InfoHandle hNorInfo)
{
    return NOR_erase(hNorInfo, hNorInfo->flashBase,
                     hNorInfo->flashSize);
}

/* Erase Flash Block */
uint32_t NOR_erase(NOR_InfoHandle hNorInfo, volatile uint32_t start_address,
                   volatile uint32_t size)
{
    volatile uint32_t addr   = start_address;
    uint32_t          retVal = NOR_FLASH_SUCCESS;
    char rangeStr[10]        = {0};
    char blockAddrStr[10]    = {0};
    char addrStr[10]         = {0};

    volatile uint32_t range = start_address + size;
    uint32_t          blockSize, blockAddr;

    DEBUG_printString("\r\nErasing the NOR Flash upto range: ");
    DEBUG_ConvertHexToString(range, rangeStr, 10);
    DEBUG_printString(rangeStr);
    DEBUG_printString("\r\n");

    while (addr < range)
    {
        if (NOR_getBlockInfo(hNorInfo, addr, &blockSize,
                             &blockAddr) != NOR_FLASH_SUCCESS)
        {
            DEBUG_printString("Address out of range");
            retVal = NOR_FLASH_FAIL;
        }
        else
        {
            /*Increment to the next block */
            if ((*Flash_Erase)(hNorInfo, blockAddr) != NOR_FLASH_SUCCESS)
            {
                DEBUG_printString("Erase failure at block address ");
                DEBUG_ConvertHexToString(blockAddr, blockAddrStr, 10);
                DEBUG_printString(blockAddrStr);
                DEBUG_printString("\r\n");
                retVal = NOR_FLASH_FAIL;
            }
            else
            {
                addr = blockAddr + blockSize;

                /* Show status messages */
                DEBUG_printString("Erased through ");
                DEBUG_ConvertHexToString(addr, addrStr, 10);
                DEBUG_printString(addrStr);
                DEBUG_printString("\r\n");
            }
        }
        if (retVal == NOR_FLASH_FAIL)
        {
            break;
        }
    }
    if (retVal != NOR_FLASH_FAIL)
    {
        DEBUG_printString("Erase Completed\r\n");
    }

    return (retVal);
}

uint32_t NOR_writeBytes(NOR_InfoHandle hNorInfo, uint32_t writeAddress,
                        uint32_t numBytes,
                        uint32_t readAddress)
{
    uint32_t blockSize, blockAddr;
    uint32_t i;
    uint32_t retval              = NOR_FLASH_SUCCESS;
    char     numBytesStr[10]     = {0};
    char     writeAddressStr[10] = {0};

    DEBUG_printString("\r\nWriting ");
    DEBUG_ConvertHexToString(numBytes, numBytesStr, 10);
    DEBUG_printString(numBytesStr);
    DEBUG_printString("bytes to NOR...\r\n");

    /* Make numBytes even if needed */
    if (numBytes & 0x00000001U)
    {
        numBytes++;
    }

    if (NOR_getBlockInfo(hNorInfo, writeAddress, &blockSize,
                         &blockAddr) != NOR_FLASH_SUCCESS)
    {
        DEBUG_printString("Address out of range\r\n");
        retval = NOR_FLASH_FAIL;
    }
    else
    {
        while (numBytes > 0)
        {
            if ((hNorInfo->bufferSize == 1) ||
                (numBytes < hNorInfo->bufferSize) ||
                ((writeAddress & (hNorInfo->bufferSize - (uint32_t) 1)) != 0))
            {
                if ((*Flash_Write)(hNorInfo, writeAddress,
                                   LOCAL_flashReadData(hNorInfo, readAddress,
                                                       0)) != NOR_FLASH_SUCCESS)
                {
                    DEBUG_printString(
                        "\r\nNormal write failed.\r\n");
                    retval = NOR_FLASH_FAIL;
                }
                else
                {
                    numBytes     -= hNorInfo->busWidth;
                    writeAddress += hNorInfo->busWidth;
                    readAddress  += hNorInfo->busWidth;
                }
            }
            else
            {
                /* Try to use buffered writes */
                if ((*Flash_BufferWrite)(hNorInfo, writeAddress,
                                         (volatile uint8_t *) readAddress,
                                         hNorInfo->bufferSize) ==
                    NOR_FLASH_SUCCESS)
                {
                    numBytes     -= hNorInfo->bufferSize;
                    writeAddress += hNorInfo->bufferSize;
                    readAddress  += hNorInfo->bufferSize;
                }
                else
                {
                    DEBUG_printString(
                        "\r\nBuffered write failed @ address 0x%x\r\n");
                    DEBUG_printString("Trying normal write\r\n");
                    /* Try normal writes as a backup*/
                    for (i = 0U; i < (hNorInfo->bufferSize >> (uint32_t) 1);
                         i++)
                    {
                        if ((*Flash_Write)(hNorInfo, writeAddress,
                                           LOCAL_flashReadData(hNorInfo,
                                                               readAddress,
                                                               0)) !=
                            NOR_FLASH_SUCCESS)
                        {
                            DEBUG_printString(
                                "\r\nNormal write also failed\r\n");
                            retval = NOR_FLASH_FAIL;
                            break;
                        }
                        else
                        {
                            numBytes     -= hNorInfo->busWidth;
                            writeAddress += hNorInfo->busWidth;
                            readAddress  += hNorInfo->busWidth;
                        }
                    }
                }
            }

            /* Output status info on the write operation*/
            if (retval == NOR_FLASH_SUCCESS)
            {
                if (((writeAddress & (~((blockSize >> 2) - 1U))) ==
                     writeAddress) ||
                    (numBytes == 0))
                {
                    DEBUG_printString("NOR Write OK through ");
                    DEBUG_ConvertHexToString(writeAddress, writeAddressStr, 10);
                    DEBUG_printString(writeAddressStr);
                    DEBUG_printString(".\r\n");
                    if (numBytes != 0)
                    {
                        if (NOR_getBlockInfo(hNorInfo, writeAddress, &blockSize,
                                             &blockAddr) != NOR_FLASH_SUCCESS)
                        {
                            DEBUG_printString(
                                "Address out of range");
                            retval = NOR_FLASH_FAIL;
                        }
                    }
                }
            }
            else
            {
                DEBUG_printString("NOR Write Failed...Aborting!\r\n");
                retval = NOR_FLASH_FAIL;
            }

            if (retval != NOR_FLASH_SUCCESS)
            {
                break;
            }
        }
    }
    return retval;
}

static void LOCAL_waitLoop(uint32_t loopcnt)
{
    uint32_t i;
    for (i = 0; i < loopcnt; i++)
    {
        ;
    }
}

static volatile uint8_t *LOCAL_flashMakeAddr(NOR_InfoHandle hNorInfo,
                                             uint32_t       blkAddr,
                                             uint32_t       offset)
{
    uint32_t tempOffset  = offset * (uint32_t) hNorInfo->maxTotalWidth;
    uint32_t tempBlkAddr = blkAddr + tempOffset;
    return ((volatile uint8_t *) tempBlkAddr);
}

static void LOCAL_flashMakeCmd(NOR_InfoHandle hNorInfo, uint32_t cmd,
                               void *cmdbuf)
{
    uint32_t i;
    uint8_t *cp = (uint8_t *) cmdbuf;

    for (i = hNorInfo->busWidth; i > 0; i--)
    {
        *cp = (i & (hNorInfo->chipOperatingWidth - (uint32_t) 1)) ? 0x00 : cmd;
        cp++;
    }
}

static void LOCAL_flashWriteCmd(NOR_InfoHandle hNorInfo, uint32_t blkAddr,
                                uint32_t offset,
                                uint32_t cmd)
{
    volatile NOR_Ptr addr;
    NOR_Data         cmdword;

    addr.cp = LOCAL_flashMakeAddr(hNorInfo, blkAddr, offset);
    LOCAL_flashMakeCmd(hNorInfo, cmd, &cmdword);
    if (hNorInfo->busWidth == BUS_8BIT)
    {
        /* Bus width 8 bit */
        *addr.cp = cmdword.c;
    }
    else
    {
        /* Default Bus width 16 bit */
        *addr.wp = cmdword.w;
    }
}

static void LOCAL_flashWriteData(NOR_InfoHandle hNorInfo, uint32_t address,
                                 uint32_t data)
{
    volatile NOR_Ptr pAddr;
    NOR_Data         dataword;
    dataword.l = data;

    pAddr.cp = (volatile uint8_t *) address;

    if (hNorInfo->busWidth == BUS_8BIT)
    {
        /* Bus width 8 bit */
        *pAddr.cp = dataword.c;
    }
    else
    {
        /* Default Bus width 16 bit */
        *pAddr.wp = dataword.w;
    }
}

/* Used only once */
static uint32_t LOCAL_flashVerifyDataBuffer(NOR_InfoHandle hNorInfo,
                                            uint32_t       address,
                                            volatile void *data,
                                            uint32_t       numBytes)
{
    volatile NOR_Ptr  pAddr, pData;
    volatile uint8_t *endAddress;
    uint32_t          endAddressTmp;
    uint32_t          retVal = NOR_FLASH_SUCCESS;

    pData.cp      = (volatile uint8_t *) data;
    pAddr.cp      = (volatile uint8_t *) address;
    endAddressTmp = address + numBytes;
    endAddress    = (volatile uint8_t *) (endAddressTmp);
    while (pAddr.cp < endAddress)
    {
        if (hNorInfo->busWidth == BUS_8BIT)
        {
            /* Bus width 8 bit */
            if ((*pAddr.cp) != (*pData.cp))
            {
                retVal = NOR_FLASH_FAIL;
            }
            pAddr.cp++;
            pData.cp++;
        }
        else
        {
            /* Default Bus width 16 bit */
            if ((*pAddr.wp) != (*pData.wp))
            {
                retVal = NOR_FLASH_FAIL;
            }
            pAddr.wp++;
            pData.wp++;
        }

        if (retVal == NOR_FLASH_FAIL)
        {
            break;
        }
    }
    return retVal;
}

uint32_t LOCAL_flashReadData(NOR_InfoHandle hNorInfo, uint32_t address,
                             uint32_t offset)
{
    volatile NOR_Ptr pAddr;
    NOR_Data         dataword;
    dataword.l = 0x00000000;

    pAddr.cp = LOCAL_flashMakeAddr(hNorInfo, address, offset);

    if (hNorInfo->busWidth == BUS_8BIT)
    {
        /* Bus width 8 bit */
        dataword.c = *pAddr.cp;
    }
    else
    {
        /* Default Bus width 16 bit */
        dataword.w = *pAddr.wp;
    }
    return dataword.l;
}

static Bool LOCAL_flashIsSetAll(NOR_InfoHandle hNorInfo, uint32_t blkAddr,
                                uint32_t offset,
                                uint32_t mask)
{
    volatile NOR_Ptr addr;
    NOR_Data         maskword;
    Bool retval = TRUE;
    uint32_t         temp;

    maskword.l = 0x00000000;

    addr.cp = LOCAL_flashMakeAddr(hNorInfo, blkAddr, offset);
    temp    = *addr.wp;
    LOCAL_flashMakeCmd(hNorInfo, mask, &maskword);
    if (hNorInfo->busWidth == BUS_8BIT)
    {
        /* Bus width 8 bit */
        temp   = *addr.cp;
        retval = (Bool) ((maskword.c & temp) == maskword.c);
    }
    else
    {
        /* Default Bus width 16 bit */
        temp   = *addr.wp;
        retval = (Bool) ((maskword.w & temp) == maskword.w);
    }
    return retval;
}

static Bool LOCAL_flashIsSetSome(NOR_InfoHandle hNorInfo, uint32_t blkAddr,
                                 uint32_t offset,
                                 uint32_t mask)
{
    volatile NOR_Ptr addr;
    NOR_Data         maskword;

    Bool retval = TRUE;

    addr.cp = LOCAL_flashMakeAddr(hNorInfo, blkAddr, offset);
    LOCAL_flashMakeCmd(hNorInfo, mask, &maskword);
    if (hNorInfo->busWidth == BUS_8BIT)
    {
        /* Bus width 8 bit */
        retval = (Bool) ((uint32_t) maskword.c & *addr.cp);
    }
    else
    {
        /* Default Bus width 16 bit */
        retval = (Bool) (maskword.w & *addr.wp);
    }
    return retval;
}

static NOR_Data LOCAL_flashReadCFIBytes(NOR_InfoHandle hNorInfo,
                                        uint32_t       offset,
                                        uint32_t       numBytes)
{
    uint32_t i;
    NOR_Data readword;
    uint8_t *pReadword = &readword.c;

    for (i = 0; i < numBytes; i++)
    {
        *pReadword =
            *(LOCAL_flashMakeAddr(hNorInfo, hNorInfo->flashBase, offset + i));
        pReadword++;
    }

    return readword;
}

static Bool LOCAL_flashCFIIsEqual(NOR_InfoHandle hNorInfo, uint32_t offset,
                                  uint32_t val)
{
    volatile NOR_Ptr addr;
    NOR_Data         testword;

    Bool retval = TRUE;

    addr.cp = LOCAL_flashMakeAddr(hNorInfo, hNorInfo->flashBase, offset);
    LOCAL_flashMakeCmd(hNorInfo, val, &testword);
    if (hNorInfo->busWidth == BUS_8BIT)
    {
        /* Bus width 8 bit */
        retval = (Bool) (testword.c == *addr.cp);
    }
    else
    {
        /* Default Bus width 16 bit */
        retval = (Bool) (testword.w == *addr.wp);
    }
    return retval;
}

/* Query the chip to check for CFI table and data*/
static uint32_t LOCAL_flashQueryCFI(NOR_InfoHandle hNorInfo)
{
    uint32_t i;
    uint32_t blkVal;
    uint32_t retVal = NOR_FLASH_FAIL;
    Bool     CFI_Qvalue, CFI_Rvalue, CFI_Yvalue;

    /*
     * Six possible NOR Flash Configurations
     * 1) Bus in x8 mode, x8 only device (chipOperatingWidth = 8-bit, busWidth =
     * 8-bit, maxTotalWidth = 8-bit)
     * 2) Bus in x8 mode, single x8/x16 flash operating in x8 mode
     * (chipOperatingWidth = 8-bit, busWidth = 8-bit, maxTotalWidth = 16-bit)
     * 3) Bus in x16 mode, single x8/x16 or x16-only flash operating in x16 mode
     * (chipOperatingWidth = 16-bit, busWidth = 16-bit, maxTotalWidth = 16-bit)
     * 4) Bus in x16 mode, two x8 flash operating in parallel.
     * (chipOperatingWidth = 8-bit, busWidth = 16-bit, maxTotalWidth = 16-bit)
     * 5) Bus in x16 mode, two x8/x16 flash, each in x8 mode, operating in
     * parallel  (chipOperatingWidth = 8-bit, busWidth = 16-bit, maxTotalWidth =
     * 32-bit)
     * 6) Bus in x16 mode, single x16/x32 flash operating in x16 mode
     * (chipOperatingWidth = 16-bit, busWidth = 16-bit, maxTotalWidth = 32-bit)
     * hNorInfo->chipOperatingWidth is the actual data bus width of the NOR
     * flash(es)
     * hNorInfo->busWidth is the operating width of the EMIF (8 or 16)
     * hNorInfo->maxTotalWidth is total possible data bus width that the NOR
     * flash supports (or flashes combined support)
     */
    for (hNorInfo->chipOperatingWidth = BUS_8BIT;
         hNorInfo->chipOperatingWidth <= hNorInfo->busWidth;
         hNorInfo->chipOperatingWidth <<= 1)
    {
        for (hNorInfo->maxTotalWidth = hNorInfo->busWidth;
             hNorInfo->maxTotalWidth <= (hNorInfo->busWidth * 2);
             hNorInfo->maxTotalWidth <<= 1)
        {
            /* Specify number of devices */
            hNorInfo->numberDevices = 0;
            while ((hNorInfo->numberDevices * hNorInfo->chipOperatingWidth) <
                   hNorInfo->busWidth)
            {
                hNorInfo->numberDevices++;
            }

            /* Enter the CFI Query mode */
            LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, 0, CFI_EXIT_CMD);
            LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, CFI_QRY_CMD_ADDR,
                                CFI_QRY_CMD);

            /* Check for Query QRY values */
            CFI_Qvalue = LOCAL_flashCFIIsEqual(hNorInfo, CFI_Q, (uint32_t) 'Q');
            CFI_Rvalue = LOCAL_flashCFIIsEqual(hNorInfo, CFI_R, (uint32_t) 'R');
            CFI_Yvalue = LOCAL_flashCFIIsEqual(hNorInfo, CFI_Y, (uint32_t) 'Y');

            if (CFI_Qvalue && CFI_Rvalue && CFI_Yvalue)
            {
                hNorInfo->commandSet =
                    (NOR_CmdSet) (LOCAL_flashReadCFIBytes(hNorInfo,
                                                          CFI_CMDSET,
                                                          (uint32_t) 2).w);
                hNorInfo->flashSize = (uint32_t) 0x1 <<
                                      (LOCAL_flashReadCFIBytes(
                                           hNorInfo,
                                           CFI_DEVICESIZE,
                                           (uint32_t) 1).c *
                                       hNorInfo->numberDevices);
                hNorInfo->numberRegions = LOCAL_flashReadCFIBytes(
                    hNorInfo, CFI_NUMBLKREGIONS, (uint32_t) 1).c;
                hNorInfo->bufferSize = (uint32_t) 0x1 <<
                                       (LOCAL_flashReadCFIBytes(
                                            hNorInfo,
                                            CFI_WRITESIZE,
                                            (uint32_t) 2).w *
                                        hNorInfo->numberDevices);

                /* Get info on sector sizes in each erase region of
                 *device */
                for (i = 0; i < hNorInfo->numberRegions; i++)
                {
                    blkVal =
                        LOCAL_flashReadCFIBytes(hNorInfo,
                                                (CFI_BLKREGIONS + (i *
                                                                   CFI_BLKREGIONSIZE)),
                                                (uint32_t) 4).l;
                    hNorInfo->numberBlocks[i] =
                        (blkVal & 0x0000FFFFU) + 1U;
                    hNorInfo->blockSize[i] =
                        ((blkVal &
                          0xFFFF0000U) ? (((blkVal >>
                                            16) &
                                           0xFFFFU) *
                                          256U) : 128U) *
                        hNorInfo->numberDevices;
                }
                retVal = NOR_FLASH_SUCCESS;
                break;
            }
        }
    }

    /* chipOperatingWidth should be <= busWidth */
    /* Dividing by 2 as it will be incremented in loop expression */
    hNorInfo->chipOperatingWidth >>= 1;

    /* Exit CFI mode */
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, 0, CFI_EXIT_CMD);
    return retVal;
}

/* ------------------------ Default empty commands ---------------------------
**/

static uint32_t Unsupported_Write(NOR_InfoHandle hNorInfo, uint32_t address,
                                  volatile uint32_t data)
{
    return NOR_FLASH_FAIL;
}

static uint32_t Unsupported_BufferWrite(NOR_InfoHandle   hNorInfo,
                                        uint32_t         address,
                                        volatile uint8_t data[],
                                        uint32_t         length)
{
    return NOR_FLASH_FAIL;
}

static uint32_t Unsupported_Erase(NOR_InfoHandle hNorInfo, uint32_t address)
{
    return NOR_FLASH_FAIL;
}

static uint32_t Unsupported_ID(NOR_InfoHandle hNorInfo)
{
    return NOR_FLASH_FAIL;
}

/* ------------------- Begin of Intel specific commands ----------------------
 * ID flash
 */
static uint32_t Intel_ID(NOR_InfoHandle hNorInfo)
{
    /* Intel Exit back to read array mode*/
    LOCAL_IntelSoftReset(hNorInfo);

    /* Write ID command*/
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, 0, INTEL_ID_CMD);

    /*Read Manufacturer's ID*/
    hNorInfo->manfID =
        (NOR_ManfID) LOCAL_flashReadData(hNorInfo, hNorInfo->flashBase,
                                         INTEL_MANFID_ADDR);

    /* Read Device ID*/
    hNorInfo->devID1 = (uint16_t) LOCAL_flashReadData(
        hNorInfo, hNorInfo->flashBase, INTEL_DEVID_ADDR);
    hNorInfo->devID2 = 0x0000;

    /* Intel Exit back to read array mode*/
    LOCAL_IntelSoftReset(hNorInfo);

    return NOR_FLASH_SUCCESS;
}

/* Reset back to Read array mode */
static void LOCAL_IntelSoftReset(NOR_InfoHandle hNorInfo)
{
    /* Intel Exit back to read array mode*/
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, 0, INTEL_RESET);
}

/* Clear status register*/
static void LOCAL_IntelClearStatus(NOR_InfoHandle hNorInfo)
{
    /* Intel clear status*/
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, 0, INTEL_CLEARSTATUS_CMD);
}

/* Remove block write protection*/
static uint32_t LOCAL_IntelClearLock(NOR_InfoHandle hNorInfo, uint32_t blkAddr)
{
    /* Write the Clear Lock Command*/
    LOCAL_flashWriteCmd(hNorInfo, blkAddr, 0, INTEL_LOCK_CMD0);

    LOCAL_flashWriteCmd(hNorInfo, blkAddr, 0, INTEL_UNLOCK_BLOCK_CMD);

    /* Check Status*/
    return LOCAL_IntelLockStatusCheck(hNorInfo);
}

static void LOCAL_IntelWaitForStatusComplete(NOR_InfoHandle hNorInfo)
{
    while (!LOCAL_flashIsSetAll(hNorInfo, hNorInfo->flashBase, 0,
                                BIT7))
    {
        /* Busy Loop */
    }
}

static uint32_t LOCAL_IntelLockStatusCheck(NOR_InfoHandle hNorInfo)
{
    uint32_t retval = NOR_FLASH_SUCCESS;

    LOCAL_IntelWaitForStatusComplete(hNorInfo);

    if (LOCAL_flashIsSetSome(hNorInfo, hNorInfo->flashBase, 0,
                             (BIT5 | BIT3)))
    {
        retval = NOR_FLASH_FAIL;
    }
    /* Clear status*/
    LOCAL_IntelClearStatus(hNorInfo);

    /* Put chip back into read array mode.*/
    LOCAL_IntelSoftReset(hNorInfo);

    /* Set Timings back to Optimum for Read*/
    return retval;
}

/* Erase Block*/
static uint32_t Intel_Erase(NOR_InfoHandle hNorInfo, volatile uint32_t blkAddr)
{
    uint32_t retval = NOR_FLASH_SUCCESS;

    /* Clear Lock Bits*/
    retval |= LOCAL_IntelClearLock(hNorInfo, blkAddr);

    /* Send Erase commands*/
    LOCAL_flashWriteCmd(hNorInfo, blkAddr, 0, INTEL_ERASE_CMD0);
    LOCAL_flashWriteCmd(hNorInfo, blkAddr, 0, INTEL_ERASE_CMD1);

    /* Wait until Erase operation complete*/
    LOCAL_IntelWaitForStatusComplete(hNorInfo);

    /* Verify successful erase*/
    if (LOCAL_flashIsSetSome(hNorInfo, hNorInfo->flashBase, 0, BIT5))
    {
        retval = NOR_FLASH_FAIL;
    }

    /* Put back into Read Array mode.*/
    LOCAL_IntelSoftReset(hNorInfo);

    return retval;
}

/* Write data*/
static uint32_t Intel_Write(NOR_InfoHandle hNorInfo, uint32_t address,
                            volatile uint32_t data)
{
    uint32_t retval = NOR_FLASH_SUCCESS;

    /* Send Write command*/
    LOCAL_flashWriteCmd(hNorInfo, address, 0, INTEL_WRITE_CMD);
    LOCAL_flashWriteData(hNorInfo, address, data);

    /* Wait until Write operation complete*/
    LOCAL_IntelWaitForStatusComplete(hNorInfo);

    /* Verify successful program*/
    if (LOCAL_flashIsSetSome(hNorInfo, hNorInfo->flashBase, 0,
                             (BIT4 | BIT3)))
    {
        retval = NOR_FLASH_FAIL;
    }

    /* Put back into Read Array mode.*/
    LOCAL_IntelSoftReset(hNorInfo);

    return retval;
}

/* Buffer write data*/
static uint32_t Intel_BufferWrite(NOR_InfoHandle hNorInfo, uint32_t address,
                                  volatile uint8_t data[],
                                  uint32_t numBytes)
{
    uint32_t retval     = NOR_FLASH_SUCCESS;
    uint32_t timeoutCnt = 0, shift;

    /* Send Write_Buff_Load command*/
    do {
        LOCAL_flashWriteCmd(hNorInfo, address, 0, INTEL_WRT_BUF_LOAD_CMD);
        timeoutCnt++;
    } while ((!LOCAL_flashIsSetAll(hNorInfo, hNorInfo->flashBase, 0,
                                   BIT7)) &&
             (timeoutCnt < 0x00010000U));

    if (timeoutCnt >= 0x10000U)
    {
        retval = NOR_FLASH_FAIL;
    }
    else
    {
        volatile NOR_Ptr  pAddr, pData;
        volatile uint8_t *endAddress;

        /*Establish correct shift value*/
        shift = 0;
        while (((uint32_t) hNorInfo->busWidth >> shift) > 1U)
        {
            shift++;
        }

        /* Write Length (either numBytes or numBytes/2)*/
        LOCAL_flashWriteCmd(hNorInfo, address, 0,
                            ((numBytes >> shift) - 1U));

        /* Write buffer data*/
        pData.cp   = (volatile uint8_t *) data;
        pAddr.cp   = (volatile uint8_t *) address;
        endAddress = (volatile uint8_t *) (pAddr.cp + numBytes);
        while (pAddr.cp < endAddress)
        {
            if (hNorInfo->busWidth == BUS_8BIT)
            {
                *pAddr.cp = *pData.cp;
                pAddr.cp++;
                pData.cp++;
            }
            else
            {
                *pAddr.wp = *pData.wp;
                pAddr.wp++;
                pData.wp++;
            }
        }
        /* Send write buffer confirm command*/
        LOCAL_flashWriteCmd(hNorInfo, address, 0, INTEL_WRT_BUF_CONF_CMD);

        /* Check status*/
        LOCAL_IntelWaitForStatusComplete(hNorInfo);

        /* Verify program was successful*/
        if (LOCAL_flashIsSetSome(hNorInfo, hNorInfo->flashBase, 0,
                                 BIT4))
        {
            retval = NOR_FLASH_FAIL;
        }

        /* Put back into Read Array mode.*/
        LOCAL_IntelSoftReset(hNorInfo);
        if (retval == NOR_FLASH_SUCCESS)
        {
            retval =
                LOCAL_flashVerifyDataBuffer(hNorInfo, address,
                                            (volatile void *) data,
                                            numBytes);
            if (retval != NOR_FLASH_SUCCESS)
            {
                DEBUG_printString("Data verify failed.\r\n");
            }
        }
    }

    return retval;
}

/* -------------------- End of Intel specific commands -----------------------*/

/*-------------------- Begin of AMD specific commands -----------------------*/

/* Identify the Manufacturer and Device ID*/
static uint32_t AMD_ID(NOR_InfoHandle hNorInfo)
{
    /* Exit back to read array mode*/
    LOCAL_AMDSoftReset(hNorInfo);

    /* Write ID commands*/
    LOCAL_AMDPrefixCommands(hNorInfo);
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, AMD_CMD2_ADDR,
                        AMD_ID_CMD);

    /* Read manufacturer's ID*/
    hNorInfo->manfID =
        (NOR_ManfID) LOCAL_flashReadData(hNorInfo, hNorInfo->flashBase,
                                         AMD_MANFID_ADDR);

    /* Read device ID*/
    hNorInfo->devID1 =
        (uint16_t) LOCAL_flashReadData(hNorInfo, hNorInfo->flashBase,
                                       AMD_DEVID_ADDR0);

    /* Read additional ID bytes if needed*/
    if ((hNorInfo->devID1 & (uint16_t) 0xFF) == (uint16_t) AMD_ID_MULTI)
    {
        hNorInfo->devID2 =
            LOCAL_flashReadCFIBytes(hNorInfo, AMD_DEVID_ADDR1, (uint32_t) 2).w;
    }
    else
    {
        hNorInfo->devID2 = 0x0000;
    }

    /* Exit back to read array mode*/
    LOCAL_AMDSoftReset(hNorInfo);

    return NOR_FLASH_SUCCESS;
}

static void LOCAL_AMDSoftReset(NOR_InfoHandle hNorInfo)
{
    /* Reset Flash to be in Read Array Mode*/
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, AMD_CMD2_ADDR, AMD_RESET);
    LOCAL_waitLoop((uint32_t) 5000);
}

/* AMD Prefix Commands*/
static void LOCAL_AMDPrefixCommands(NOR_InfoHandle hNorInfo)
{
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, AMD_CMD0_ADDR, AMD_CMD0);
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, AMD_CMD1_ADDR, AMD_CMD1);
}

/* Erase Block*/
static uint32_t AMD_Erase(NOR_InfoHandle hNorInfo, uint32_t blkAddr)
{
    uint32_t retval = NOR_FLASH_SUCCESS;
    uint32_t cnt    = 0;

    /* Send commands*/
    LOCAL_AMDPrefixCommands(hNorInfo);
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, AMD_CMD2_ADDR,
                        AMD_BLK_ERASE_SETUP_CMD);
    LOCAL_AMDPrefixCommands(hNorInfo);
    LOCAL_flashWriteCmd(hNorInfo, blkAddr, 0x0, AMD_BLK_ERASE_CMD);

    /* Poll DQ7 and DQ15 for status*/
    while (!LOCAL_flashIsSetAll(hNorInfo, blkAddr, 0, BIT7))
    {
        cnt++;
    }

    LOCAL_waitLoop((uint32_t) 1000);

    /* Check data*/
    if (!LOCAL_flashIsSetAll(hNorInfo, blkAddr, 0, AMD_BLK_ERASE_DONE))
    {
        retval = NOR_FLASH_FAIL;
    }

    /* Flash Mode: Read Array*/
    LOCAL_AMDSoftReset(hNorInfo);

    return retval;
}

/* AMD Flash Write*/
static uint32_t AMD_Write(NOR_InfoHandle hNorInfo, uint32_t address,
                          volatile uint32_t data)
{
    uint32_t retval = NOR_FLASH_SUCCESS;
    uint32_t flag   = 0;

    /* Send Commands*/
    LOCAL_AMDPrefixCommands(hNorInfo);
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, AMD_CMD2_ADDR,
                        AMD_PROG_CMD);
    LOCAL_flashWriteData(hNorInfo, address, data);

    /* Wait for ready.*/
    while (TRUE)
    {
        if ((LOCAL_flashReadData(hNorInfo, address,
                                 0) & (BIT7 | BIT15)) == (data & (BIT7 | BIT15)))
        {
            flag = 1U;
        }
        else
        {
            if (LOCAL_flashIsSetAll(hNorInfo, address, 0, BIT5))
            {
                if ((LOCAL_flashReadData(hNorInfo, address,
                                         0) & (BIT7 | BIT15)) !=
                    (data & (BIT7 | BIT15)))
                {
                    DEBUG_printString("Timeout ocurred.\r\n");
                    retval = NOR_FLASH_FAIL;
                }
                flag = 1U;
            }
        }

        if (flag == 1U)
        {
            break;
        }
    }

    /* Return Read Mode*/
    LOCAL_AMDSoftReset(hNorInfo);

    /* Verify the data.*/
    if (retval == NOR_FLASH_SUCCESS)
    {
        if ((LOCAL_flashReadData(hNorInfo, address, 0) != data))
        {
            DEBUG_printString("Failed flashing @ 0x%x\r\n");
            retval = NOR_FLASH_FAIL;
        }
    }

    return retval;
}

/* AMD flash buffered write*/
static uint32_t AMD_BufferWrite(NOR_InfoHandle hNorInfo, uint32_t address,
                                volatile uint8_t data[],
                                uint32_t numBytes)
{
    uint32_t          startAddress = address;
    uint32_t          blkAddress, blkSize;
    uint32_t          data_temp;
    uint32_t          retval = NOR_FLASH_SUCCESS;
    uint32_t          shift;
    volatile NOR_Ptr  pAddr, pData;
    volatile uint8_t *endAddress;
    uint32_t          flag = 0;

    /* Get block base address and size */
    NOR_getBlockInfo(hNorInfo, address, &blkSize, &blkAddress);

    /* Write the Write Buffer Load command*/
    LOCAL_AMDPrefixCommands(hNorInfo);
    LOCAL_flashWriteCmd(hNorInfo, blkAddress, 0, AMD_WRT_BUF_LOAD_CMD);

    /*Establish correct shift value*/
    shift = 0;
    while (((uint32_t) hNorInfo->busWidth >> shift) > 1U)
    {
        shift++;
    }

    /* Write Length (either numBytes or numBytes/2)*/
    LOCAL_flashWriteCmd(hNorInfo, blkAddress, 0, (numBytes >> shift) - 1U);

    /* Write Data*/
    pData.cp   = (volatile uint8_t *) data;
    pAddr.cp   = (volatile uint8_t *) address;
    endAddress = (volatile uint8_t *) (pAddr.cp + numBytes);
    while (pAddr.cp < endAddress)
    {
        if (hNorInfo->busWidth == BUS_8BIT)
        {
            /* Bus width 8 bit */
            *pAddr.cp = *pData.cp;
            pAddr.cp++;
            pData.cp++;
        }
        else
        {
            /* Default Bus width 16 bit */
            *pAddr.wp = *pData.wp;
            pAddr.wp++;
            pData.wp++;
        }
    }

    /* Put last data written at start of data buffer - For AMD
     *verification*/
    if (hNorInfo->busWidth == BUS_8BIT)
    {
        /* Bus width 8 bit */
        address = (uint32_t) (endAddress - 1);
    }
    else
    {
        /* Default Bus width 16 bit */
        address = (uint32_t) (endAddress - 2);
    }

    /* Program Buffer to Flash Confirm Write*/
    LOCAL_flashWriteCmd(hNorInfo, blkAddress, 0, AMD_WRT_BUF_CONF_CMD);

    LOCAL_waitLoop(FLASH_WAIT_LOOP);

    /* Read last data item*/
    data_temp =
        LOCAL_flashReadData(hNorInfo,
                            (uint32_t) (data + (address - startAddress)),
                            0);

    while (TRUE)
    {
        if ((LOCAL_flashReadData(hNorInfo, address,
                                 0) & (BIT7 | BIT15)) ==
            (data_temp & (BIT7 | BIT15)))
        {
            flag = 1U;
        }
        else
        {
            /* Timeout has occurred*/
            if (LOCAL_flashIsSetAll(hNorInfo, address, 0, BIT5))
            {
                if ((LOCAL_flashReadData(hNorInfo, address,
                                         0) & (BIT7 | BIT15)) !=
                    (data_temp & (BIT7 | BIT15)))
                {
                    DEBUG_printString(
                        "Timeout ocurred \r\n");
                    retval = NOR_FLASH_FAIL;
                }
                flag = 1U;
            }
            /* Abort has occurred*/
            if (flag != 1U)
            {
                if (LOCAL_flashIsSetAll(hNorInfo, address, 0, BIT1))
                {
                    if ((LOCAL_flashReadData(hNorInfo, address,
                                             0) & (BIT7 | BIT15)) !=
                        (data_temp & (BIT7 | BIT15)))
                    {
                        DEBUG_printString(
                            "Abort ocurred.\r\n");
                        retval = NOR_FLASH_FAIL;
                        LOCAL_AMDWriteBufAbortReset(hNorInfo);
                    }
                    flag = 1U;
                }
            }
        }

        if (flag == 1U)
        {
            break;
        }
    }

    /* Put chip back into read array mode.*/
    LOCAL_AMDSoftReset(hNorInfo);
    if (retval == NOR_FLASH_SUCCESS)
    {
        retval =
            LOCAL_flashVerifyDataBuffer(hNorInfo, startAddress,
                                        (volatile void *) data,
                                        numBytes);
        if (retval != NOR_FLASH_SUCCESS)
        {
            DEBUG_printString("Data verify failed.\r\n");
        }
    }
    return retval;
}

/* AMD Write Buf Abort Reset Flash*/
static void LOCAL_AMDWriteBufAbortReset(NOR_InfoHandle hNorInfo)
{
    /* Reset Flash to be in Read Array Mode*/
    LOCAL_AMDPrefixCommands(hNorInfo);
    LOCAL_AMDSoftReset(hNorInfo);
}

/* --------------------- End of AMD specific commands ------------------------*/
