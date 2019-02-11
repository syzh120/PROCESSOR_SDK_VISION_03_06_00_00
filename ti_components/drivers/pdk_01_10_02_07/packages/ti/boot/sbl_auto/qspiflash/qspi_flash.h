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
 *  \defgroup QSPI_FLASH QSPI Flash Library
 *
 *  @{
 */
/**
 *  \file     qspi_flash.h
 *
 *  \brief    This file contains the interfaces present in the
 *            QSPI Flash Library.
 *            This also contains some related macros, structures and enums.
 */

#ifndef QSPI_FLASH_H_
#define QSPI_FLASH_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_qspi.h>

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  This typedef contains the prototype of QSPI lib init function.
 *
 */
typedef void (*QSPI_flashInitFunPtr)(qspi_DeviceType_e DeviceType);

/**
 * \brief  This macro defines the Boolean that is used for True.
 */
#define QSPI_FLASH_SUCCESS                             ((uint32_t) 1U)

/**
 * \brief  This macro defines the Boolean that is used for False.
 */
#define QSPI_FLASH_FAIL                                ((uint32_t) 0U)

/**
 * \name QSPI Config ID's
 *  @{
 */
/**
 * \brief  Clock speed configuration id
 */
#define QSPI_CONFIGID_CLOCKSPEED  (0)
/**
 * \brief  Read command configuration id
 */
#define QSPI_CONFIGID_READCMD     (1)
/** @} */

/**
 * \brief  Set this macro to 1 to reset the flash at initialization
 *         Required only if QSPI boot mode is selected and connected using
 *         CCS/debugger. Production code need not do the reset, so default
 *         value set to 0
 */
#define QSPI_FLASH_RESET_AT_INIT  (0)

/**
 * \brief  Block size of QSPI flash
 */
#define QSPIFLASH_BLOCKSIZE (64U * 1024U)
/**
 * \brief  Sector size of QSPI flash
 */
#define QSPIFLASH_SUBSECTORSIZE (4U * 1024U)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief Supported QSPI CR WLEN
 *        128 bits is not supported for tda3xx platform
 */
typedef enum {
    QSPI_CR_WLEN_1_BIT    = 0x0,
    /**< 1 bit */
    QSPI_CR_WLEN_8_BITS   = 0x7,
    /**< 8 bits */
    QSPI_CR_WLEN_16_BITS  = 0xF,
    /**< 16 bits */
    QSPI_CR_WLEN_24_BITS  = 0x17,
    /**< 24 bits */
    QSPI_CR_WLEN_32_BITS  = 0x1F,
    /**< 32 bits */
    QSPI_CR_WLEN_128_BITS = 0x7F
    /**< 128 bits */
} qspi_CR_WLEN_e;

/**
 * \brief Supported QSPI CR FLEN
 */
typedef enum {
    QSPI_CR_FLEN_1_WORD = 0x0,
    /**< 1 word */
    QSPI_CR_FLEN_2_WORDS,
    /**< 2 words */
    QSPI_CR_FLEN_3_WORDS,
    /**< 3 words */
    QSPI_CR_FLEN_4_WORDS,
    /**< 4 words */
    QSPI_CR_FLEN_5_WORDS,
    /**< 5 words */
    QSPI_CR_FLEN_6_WORDS,
    /**< 6 words */
    QSPI_CR_FLEN_7_WORDS,
    /**< 7 words */
    QSPI_CR_FLEN_8_WORDS
    /**< 8 words */
} qspi_CR_FLEN_e;

/**
 * \brief Struct to hold configuration descriptor type
 */
typedef struct
{
    uint32_t ConfigId;
    /**< Configuration ID */
    uint32_t Value;
    /**< Value */
} QSPI_ConfigDesc_t;

/**
 * \brief Struct to hold QSPI flash command parameters
 */
typedef struct
{
    uint32_t numCmdBits;
    /**< Number of flash command bits */
    uint32_t cmd;
    /**< Flash command */
    uint32_t numCmdDummyBits;
    /**< Number of flash command dummy bits */
    uint32_t numAddrBits;
    /**< Number of flash address bits */
    uint32_t addr;
    /**< Flash Address */
    uint32_t numAddrDummyBits;
    /**< Number of flash address dummy bits */
    uint32_t dataType;
    /**< Data type */
    uint32_t numPerDataWordbits;
    /**< Number of bits per data word */
    uint32_t numDataWords;
    /**< Number of data words */
} QSPI_FlashCmd_t;

/**
 * \brief Struct to hold QSPI flash device info
 */
typedef struct
{
    qspi_DeviceType_e    flashType;
    /**< Flash Type */
    uint32_t             numDatalines;
    /**< Number of data lines */
    uint32_t             qspiMode;
    /**< Supported QSPI mode */
    uint32_t             qspiCs;
    /**< QSPI CS */
    uint32_t             dataDelay;
    /**< Data Delay */
    qspi_ClockFreq_e     qspifrequency;
    /**< QSPI Clock Frequency */
    QSPI_FlashCmd_t      idCmd;
    /**< Command ID */
    QSPI_FlashCmd_t      readCmd;
    /**< Read command */
    QSPI_FlashCmd_t      writeCmd;
    /**< Write command */
    QSPI_FlashCmd_t      sectorEraseCmd;
    /**< Command to erase sector */
    QSPI_FlashCmd_t      subSectorEraseCmd;
    /**< Command to erase sub sector */
    QSPI_FlashCmd_t      fullEraseCmd;
    /**< Command to erase full flash */
    QSPI_FlashCmd_t      flashStatusCmd;
    /**< Command to get flash status */
    QSPI_FlashCmd_t      writeEnableCmd;
    /**< Command to enable write */
    QSPI_flashInitFunPtr qspiFlashInitFxn;
    /**< Function pointer to initialize flash */
} QSPI_FlashDevInfo_t;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   API to configure memory mapped address for different
 *          chip select in control module.
 *
 * \param   MMPT_S        Memory map switch value
 * \param   chipSelect    External Chip Select value from enum qspi_ChipSelect_e
 *
 * \return  none
 */
void QSPI_ConfMAddrSpace(uint8_t MMPT_S, qspi_ChipSelect_e chipSelect);

/**
 * \brief   API to configure the clock frequency
 *
 * \param   in_ClockSettings Clock frequency to be configured
 *
 * \return  none
 */
void QSPI_SelClockFrequency(qspi_ClockFreq_e in_ClockSettings);

/**
 * \brief   API to read or write data based on Word Length with data Buffer
 *          address incremented by 4 bytes only
 *
 * \param   flashCmd  Command
 * \param   data      Pointer to memory containing data
 *
 * \return  STW_SOK in case of success -ve otherwise
 */
int32_t QSPI_executeCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data);

/**
 * \brief   API to read or write data based on Word Length with data Buffer
 *          address incremented by 1/2/4/8/16 bytes only
 *
 * \param   flashCmd  Command
 * \param   data      Pointer to memory containing data
 *
 * \return  STW_SOK in case of success -ve otherwise
 */
int32_t QSPI_executeRdWrDataCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data);

/**
 * \brief   API to initialize all QSPI Flash modes except custom Flash Mode.
 *
 *          API configures flash based on DeviceType but for custom Flash Mode
 *          (DEVICE_TYPE_CUSTOM), application will intialize the QSPI_FlashDevInfo_t
 *          structure with user defined flash configuration and then should call
 *          QSPI_ConfigFlashDevInfo() which configures flash with custom flash
 *          configuration For custom Flash Mode, Application has to call
 *          QSPI_ConfigFlashDevInfo() first with used defined flash configuration
 *          instead of QSPI_Initialize() before calling any other API's
 *
 * \param   DeviceType  Flash type qspi_DeviceType_e
 *
 * \return  QSPI_FLASH_SUCCESS if the QSPI initialized successfully
 *          QSPI_FLASH_FAIL otherwise
 */
uint32_t QSPI_Initialize(qspi_DeviceType_e DeviceType);

/**
 * \brief   API to configure the clock frequency
 *
 * \param   flashType    flash type qspi_DeviceType_e
 * \param   flashDevInfo Pointer to structure containing flash info QSPI_FlashDevInfo_t
 *
 * \return  none
 */
void QSPI_ConfigFlashDevInfo(qspi_DeviceType_e          flashType,
                             const QSPI_FlashDevInfo_t *flashDevInfo);

/**
 * \brief   Api to reads one or several sectors from the QSPI Memory described
 *          in the Device Descriptor.
 *
 * \param   dstAddr       Pointer to destination address
 * \param   srcOffsetAddr Source address
 * \param   length        Length of the data to be read
 *
 * \return  QSPI_FLASH_SUCCESS in case of success
 */
uint32_t QSPI_ReadSectors(void    *dstAddr,
                          uint32_t srcOffsetAddr,
                          uint32_t length);

/**
 * \brief   Api to reads one or several sectors from the QSPI Memory described
 *          in the Device Descriptor using EDMA
 *
 * \param   dstAddr       Pointer to destination address
 * \param   srcOffsetAddr Source address
 * \param   length        Length of the data to be read
 * \param   edma_ch_num   EDMA channel number
 *
 * \return  none
 */
void QSPI_ReadSectors_edma(void    *dstAddr,
                           uint32_t srcOffsetAddr,
                           uint32_t length,
                           uint32_t edma_ch_num);

/**
 * \brief   API to configure the QSPI Flash
 *
 * \param   ConfigId      Configure ID
 * \param   ConfigValue   Configure Value
 *
 * \return  QSPI_FLASH_SUCCESS in case of success, QSPI_FLASH_FAIL otherwise
 */
uint32_t QSPI_Configure(uint32_t ConfigId, uint32_t ConfigValue);

/**
 * \brief   API to Writes one or several sectors to the QSPI Memory blocking mode
 *
 * \param   dstOffsetAddr Address where data is to be written
 * \param   srcAddr       Source data address
 * \param   length        Length of data
 *
 * \return  QSPI_FLASH_SUCCESS in case of success, QSPI_FLASH_FAIL otherwise
 *
 * \note    Memory mapped mode for write is not supported
 *          Blocking mode currently is not supported
 */
uint32_t QSPI_WriteSectors(uint32_t dstOffsetAddr, uint32_t srcAddr,
                           uint32_t length);

/**
 * \brief   API to Writes one or several sectors to the QSPI Memory in non
 *          blocking mode
 *          flash status should be checked before sending next command
 *          Bit 0 of Flash status should be 0 indicating flash is not busy
 *          Ex: while ((QSPI_FlashStatus() & 0x01)) ;
 *          Note: write in memory map mode is not supported by driver. This is because
 *          Most of the flashes require write enable (WE) command to be sent before
 *          sending the write command. This puts a restriction on mem mapped write that
 *          after every word write, switch to cfg mode and send WE command.
 *          This is in effecient and also the IP was not designed for the mem mapped
 *          write operations.
 *
 * \param   dstOffsetAddr Address where data is to be written
 * \param   srcAddr       Source data address
 * \param   length        Length of data
 *
 * \return  QSPI_FLASH_SUCCESS in case of success, QSPI_FLASH_FAIL otherwise
 *
 * \note    Memory mapped mode for write is not supported
 */
uint32_t QSPI_WriteSectorsNonBlocking(uint32_t dstOffsetAddr, uint32_t srcAddr,
                                      uint32_t length);

/**
 * \brief   API to write data on flash moemory
 *
 * \param   dstOffsetAddr Address where data is to be written
 * \param   srcAddr       Source data address
 * \param   length        Length of data
 *
 * \return  QSPI_FLASH_SUCCESS in case of success, QSPI_FLASH_FAIL otherwise
 */
void QSPI_WriteCfgMode(uint32_t dstOffsetAddr, uint32_t srcAddr,
                       uint32_t length);

/**
 * \brief   API to write data on flash moemory
 *
 *          flash status should be checked before sending next command
 *          Bit 0 of Flash status should be 0 indicating flash is not busy
 *          Ex: while ((QSPI_FlashStatus() & 0x01)) ;
 *
 * \param   dstOffsetAddr Address where data is to be written
 * \param   srcAddr       Source data address
 * \param   length        Length of data
 *
 * \return  QSPI_FLASH_SUCCESS in case of success, QSPI_FLASH_FAIL otherwise
 */
void QSPI_WriteCfgModeNonBlocking(uint32_t dstOffsetAddr, uint32_t srcAddr,
                                  uint32_t length);

/**
 * \brief   API to get device ID
 *
 * \return  Device ID
 */
uint32_t QSPI_GetDeviceId(void);

/**
 *  \brief   QSPI Get Device Id
 *
 *  This function returns the device Id in the data pointer passed.
 *  each of the spi word is copied in the 32bit word pointed in the data ptr
 *  In each word first n bits equal to the spiWordLength will be valid.
 *
 *  \param  numSpiWords   Number of Spi Words in the Id Cmd to be read
 *  \param  data          Pointer to memory to store device ID
 *
 *  \return QSPI_FLASH_SUCCESS in case of success, QSPI_FLASH_FAIL otherwise
 *
 */
int32_t QSPI_GetDeviceIdExtended(uint32_t numSpiWords, uint32_t *data);

/**
 * \brief   API to read data from flash moemory
 *
 * \param   dstAddr        Address where data is to be written
 * \param   srcOffsetAddr  Address on flash to read data
 * \param   length         Length of data
 *
 * \return  none
 */
void QSPI_ReadCfgMode(uint32_t dstAddr, uint32_t srcOffsetAddr,
                      uint32_t length);

/**
 * \brief   API to read MID
 *
 * \return  MID value
 */
uint32_t QSPIFlash_ReadMID(void);

/**
 * \brief   API to check flash status
 *
 * \return  Flash status
 */
uint32_t QSPI_FlashStatus(void);

/**
 * \brief   API to enable flash for writing data
 */
void QSPI_WriteEnable(void);

/**
 * \brief   API to Enable Quad
 */
void QSPI_QuadEnable(void);

/**
 * \brief   API to Enable Quad in non blocking mode
 *          flash status should be checked before sending next command
 *          Bit 0 of Flash status should be 0 indicating flash is not busy
 *          Ex: while ((QSPI_FlashStatus() & 0x01)) ;
 */
void QSPI_QuadEnableNonBlocking(void);

/**
 * \brief   API to erase sub sector in flash memory
 *
 * \param   offsetAddr  Offset addreess for erasing sector
 *
 * \return  none
 */
void QSPI_FlashSubSectorErase(uint32_t offsetAddr);

/**
 * \brief   API to erase sub sector in flash memory in non blocking mode
 *          flash status should be checked before sending next command
 *          Bit 0 of Flash status should be 0 indicating flash is not busy
 *          Ex: while ((QSPI_FlashStatus() & 0x01)) ;
 *          In some flashes (Ex: Spansion flashes used in TI EVMs) the sectors are
 *          organized as a hybrid combination of 4-kB and 64-kB sectors, and when the
 *          sub sector erase is executed on 64-kB sector the API returns with success
 *          without erasing. Since this is flash dpecific driver will not check for this.
 *          Application calling this API should make sure that this API is called only
 *          for the supported sectors.
 *
 * \param   offsetAddr  Offset addreess for erasing sector
 *
 * \return  none
 */
void QSPI_FlashSubSectorEraseNonBlocking(uint32_t offsetAddr);

/**
 * \brief   API to erase a block in flash memory
 *
 * \param   blkNo   Block number to be erased
 *
 * \return  none
 */
void QSPI_FlashBlockErase(uint32_t blkNo);

/**
 * \brief   API to erase a block in flash memory
 *          flash status should be checked before sending next command
 *          Bit 0 of Flash status should be 0 indicating flash is not busy
 *          Ex: while ((QSPI_FlashStatus() & 0x01)) ;
 *
 * \param   blkNo   Block number to be erased
 *
 * \return  none
 */
void QSPI_FlashBlockEraseNonBlocking(uint32_t blkNo);

/**
 * \brief   API Erase full flash
 */
void QSPI_FlashFullErase(void);

/**
 * \brief   API Erase full flash in non blocking mode
 *          flash status should be checked before sending next command
 *          Bit 0 of Flash status should be 0 indicating flash is not busy
 *          Ex: while ((QSPI_FlashStatus() & 0x01)) ;
 */
void QSPI_FlashFullEraseNonBlocking(void);

/**
 * \brief   API to seach for available input address
 *
 * \param   srcAddr   Pointer to store address
 * \param   location  Address to be searched
 *
 * \return  none
 */
void QSPI_seek(uint32_t *srcAddr, uint32_t location);

/**
 * \brief   API to get flash type
 *
 * \param   inDeviceType   Input device type qspi_DeviceType_e
 *
 * \return  Supported device type qspi_DeviceType_e
 */
qspi_DeviceType_e QSPI_getFlashType(qspi_DeviceType_e inDeviceType);

/**
 *  \brief   API to de inititalize the flash parameters
 *
 *  \return QSPI_FLASH_SUCCESS in case of success, QSPI_FLASH_FAIL otherwise
 */
uint32_t QSPI_DeInitialize(void);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* QSPI_FLASH_H_ */
/** @} */
