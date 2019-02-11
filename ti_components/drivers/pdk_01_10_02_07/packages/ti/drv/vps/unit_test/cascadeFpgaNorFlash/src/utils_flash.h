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
 *  \file utils_flash.h
 *
 *  \brief Cascade Radar flash utilities.
 */
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */

/*************** User Change Area *******************************************

   The purpose of this section is to show how the SW Drivers can be customized
   according to the requirements of the hardware and Flash memory configurations.
   It is possible to choose the Flash memory start address, the CPU Bit depth, the number of Flash
   chips, the hardware configuration and performance data (TimeOut Info).

   The options are listed and explained below:

   ********* Data Types *********
   The source code defines hardware independent datatypes assuming that the
   compiler implements the numerical types as

   unsigned char    8 bits (defined as uint8_t)
   char             8 bits (defined as int8_t)
   unsigned int     16 bits (defined as uint16_t)
   int              16 bits (defined as int16_t)
   unsigned long    32 bits (defined as uint32_t)
   long             32 bits (defined as int32_t)

   In case the compiler does not support the currently used numerical types,
   they can be easily changed just once here in the user area of the headerfile.
   The data types are consequently referenced in the source code as (u)int8_t,
   (u)int16_t and (u)int32_t. No other data types like 'CHAR','SHORT','INT','LONG'
   are directly used in the code.


   ********* Flash Type *********
   This driver supports the following Serial Flash memory Types:

    - N25Q 8M
    - N25Q 16M
    - N25Q 32M
    - N25Q 64M
    - N25Q 128M
    - N25Q 256M
    - N25Q 256M (N25Q256A8X)
    - N25Q 512M
    - N25Q 1G

   ********* Flash and Board Configuration *********
   The driver also supports different configurations of the Flash chips
   on the board. In each configuration a new data Type called
   'uCPUBusType' is defined to match the current CPU data bus width.
   This data type is then used for all accesses to the memory.

   Because SPI interface communications are controlled by the
   SPI master, which, in turn, is accessed by the CPU as an 8-bit data
   buffer, the configuration is fixed for all cases.

   ********* TimeOut *********
   There are timeouts implemented in the loops of the code, in order
   to enable a timeout detection for operations that would otherwise never terminate.
   There are two possibilities:

   1) The ANSI Library functions declared in 'time.h' exist

      If the current compiler supports 'time.h' the define statement
      TIME_H_EXISTS should be activated. This makes sure that
      the performance of the current evaluation HW does not change
      the timeout settings.

   2) or they are not available (COUNT_FOR_A_SECOND)

      If the current compiler does not support 'time.h', the define
      statement cannot be used. In this case the COUNT_FOR_A_SECOND
      value has to be defined so as to create a one-second delay.
      For example, if 100000 repetitions of a loop are
      needed to give a time delay of one second, then
      COUNT_FOR_A_SECOND should have the value 100000.

      Note: This delay is HW (Performance) dependent and therefore needs
      to be updated with every new HW.

      This driver has been tested with a certain configuration and other
      target platforms may have other performance data, therefore, the
      value may have to be changed.

      It is up to the user to implement this value to prevent the code
      from timing out too early and allow correct completion of the device
      operations.


   ********* Additional Routines *********
   The drivers also provide a subroutine which displays the full
   error message instead of just an error number.

   The define statement VERBOSE activates additional Routines.
   Currently it activates the FlashErrorStr() function

   No further changes should be necessary.

*****************************************************************************/


#ifndef __SERIAL__H__
#define __SERIAL__H__

#include <stdint.h>

#define DRIVER_VERSION_MAJOR 0
#define DRIVER_VERSION_MINOR 1

/* Enable device auto detect on init */
#define ADDR_MODE_AUTO_DETECT

/* This define enables N25QxxxA8xExxxxx devices                             */
/* (with this define, driver use the alternative command set)                */
//#define SUPPORT_N25Q_STEP_B

/*******************************************************************************
Flash address byte mode (see Datasheet)
*******************************************************************************/
typedef enum
{
    FLASH_3_BYTE_ADDR_MODE    = 0x03,            /* 3 byte address */
    FLASH_4_BYTE_ADDR_MODE    = 0x04            /* 4 byte address */

} AddressMode;

/*#define TIME_H_EXISTS*/  /* set this macro if C-library "time.h" is supported */
/* Possible Values: TIME_H_EXISTS
                    - no define - TIME_H_EXISTS */

#ifndef TIME_H_EXISTS
#define COUNT_FOR_A_SECOND 0xFFFFFF                   /* Timer Usage */
#endif

#define SE_TIMEOUT (3)    /* Timeout in seconds suggested for Sector Erase Operation*/
#define BE_TIMEOUT  (480) /* Timeout in seconds suggested for Bulk Erase Operation*/
#define DIE_TIMEOUT (480) /* Timeout in seconds suggested for Die Erase Operation*/
/* Activates additional Routines */
#define VERBOSE
#define DEBUG

/********************** End of User Change Area *****************************/

/*******************************************************************************
    Device Constants
*******************************************************************************/

/* manufacturer id + mem type + mem capacity  */
#define MEM_TYPE_N25Q8         0x9D4014    /* ID for N25Q   8M device */
#define MEM_TYPE_N25Q16        0x9D4015    /* ID for N25Q  16M device */
#define MEM_TYPE_N25Q32        0x9D4016    /* ID for N25Q  32M device */
#define MEM_TYPE_N25Q64        0x9D4017    /* ID for N25Q  64M device */
#define MEM_TYPE_N25Q128       0x9D4018    /* ID for N25Q 128M device */
#define MEM_TYPE_N25Q256       0x9D4019    /* ID for N25Q 256M device */
#define MEM_TYPE_N25Q512_V3    0x9D4020    /* ID for N25Q 512M device for operating voltage 3v  */
#define MEM_TYPE_N25Q512_V18   0x9D4020    /* ID for N25Q 512M device for operating voltage 1.8v */
#define MEM_TYPE_N25Q1G        0x9D4021    /* ID for N25Q   1G device */
#define MEM_TYPE_MICRON        0x9D4000    /* first ID byte */
#define MEM_TYPE_MASK          0x0000FF

#define DISCOVERY_TABLE1                0x0C
#define DTABLE1_SECTOR_DESCRIPTOR       0x1C
#define DTABLE1_FLASH_SIZE              0x04
/*******************************************************************************
    DERIVED DATATYPES
*******************************************************************************/
/******** InstructionsCode ********/
enum
{
    /* Command definitions (please see datasheet for more details) */

    /* RESET Operations */
    SPI_FLASH_INS_REN                 = 0x66, /* reset enable */
    SPI_FLASH_INS_RMEM                = 0x99, /* reset memory */

    /* IDENTIFICATION Operations */
    SPI_FLASH_INS_RDID                = 0x9F, /* read Identification */
    SPI_FLASH_INS_RDID_ALT            = 0x9E, /* read Identification */
    SPI_FLASH_INS_MULT_IO_RDID        = 0xAF, /* read multiple i/o read id */
    SPI_FLASH_INS_DISCOVER_PARAMETER  = 0x5A, /* read serial flash discovery parameter */

    /* READ operations */
    SPI_FLASH_INS_READ                = 0x03, /* read data bytes */
    SPI_FLASH_INS_FAST_READ           = 0x0B, /* read data bytes at higher speed */
    SPI_FLASH_INS_DOFR                = 0x3B, /* dual output Fast Read */
    SPI_FLASH_INS_DIOFR               = 0x0B, /* dual input output Fast Read */
    SPI_FLASH_INS_DIOFR_ALT1          = 0x3B, /* dual input output Fast Read */
    SPI_FLASH_INS_DIOFR_ALT2          = 0xBB, /* dual input output Fast Read */
    SPI_FLASH_INS_QOFR                = 0x6B, /* quad output Fast Read */
    SPI_FLASH_INS_QIOFR               = 0x0B, /* quad output Fast Read */
    SPI_FLASH_INS_QIOFR_ALT1          = 0x6B, /* quad input/output Fast Read */
    SPI_FLASH_INS_QIOFR_ALT2          = 0xEB, /* quad input output Fast Read */

    /* WRITE operations */
    SPI_FLASH_INS_WREN                = 0x06, /* write enable */
    SPI_FLASH_INS_WRDI                = 0x04, /* write disable */

    /* REGISTER operations */
    SPI_FLASH_INS_RDSR                = 0x05, /* read status register */
    SPI_FLASH_INS_WRSR                = 0x01, /* write status register */
    SPI_FLASH_INS_RDLR                = 0xE8, /* read lock register */
    SPI_FLASH_INS_CMD_WRLR            = 0xE5, /* write lock register */
    SPI_FLASH_INS_RFSR                = 0x70, /* read flag status register */
    SPI_FLASH_INS_CLFSR               = 0x50, /* clear flag status register */
    SPI_FLASH_INS_RDNVCR              = 0xB5, /* read non volatile configuration register */
    SPI_FLASH_INS_WRNVCR              = 0xB1, /* write non volatile configuration register */
    SPI_FLASH_INS_RDVCR               = 0x85, /* read volatile configuration register */
    SPI_FLASH_INS_WRVCR               = 0x81, /* write volatile configuration register */
    SPI_FLASH_INS_RDVECR              = 0x65, /* read volatile enhanced configuration register */
    SPI_FLASH_INS_WRVECR              = 0x61, /* write volatile enhanced configuration register */

    /* PROGRAM operations */
    SPI_FLASH_INS_PP                  = 0x02, /* PAGE PROGRAM */
#ifdef SUPPORT_N25Q_STEP_B
    SPI_FLASH_INS_PP4B                = 0x12, /* 4-BYTE PAGE PROGRAM (N25QxxxA8 only) */
#endif
    SPI_FLASH_INS_DIPP                = 0xA2, /* DUAL INPUT FAST PROGRAM */
    SPI_FLASH_INS_DIEPP               = 0x02, /* EXTENDED DUAL INPUT FAST PROGRAM */
    SPI_FLASH_INS_DIEPP_ALT1          = 0xA2, /* EXTENDED DUAL INPUT FAST PROGRAM (alt 1) */
    SPI_FLASH_INS_DIEPP_ALT2          = 0xD2, /* EXTENDED DUAL INPUT FAST PROGRAM (alt 2) */
    SPI_FLASH_INS_QIPP                = 0x32, /* QUAD INPUT FAST PROGRAM */
#ifdef SUPPORT_N25Q_STEP_B
    SPI_FLASH_INS_QIPP4B              = 0x34, /* 4-BYTE QUAD INPUT FAST PROGRAM (N25QxxxA8 only) */
#endif
    SPI_FLASH_INS_QIEPP               = 0x02, /* EXTENDED QUAD INPUT FAST PROGRAM */
    SPI_FLASH_INS_QIEPP_ALT1          = 0x32, /* EXTENDED QUAD INPUT FAST PROGRAM (alt 1) */
    SPI_FLASH_INS_QIEPP_ALT2          = 0x38, /* EXTENDED QUAD INPUT FAST PROGRAM */
#ifndef SUPPORT_N25Q_STEP_B
    SPI_FLASH_INS_QIEPP_ALT3          = 0x12, /* EXTENDED QUAD INPUT FAST PROGRAM (do not use in N25QxxxA8) */
#endif

    /* ERASE operations */
    SPI_FLASH_INS_SSE                 = 0x20, /* sub sector erase */
#ifdef SUPPORT_N25Q_STEP_B
    SPI_FLASH_INS_SSE4B               = 0x21, /* sub sector erase (N25QxxxA8 only) */
#endif
    SPI_FLASH_INS_SE                  = 0xD8, /* sector erase */
#ifdef SUPPORT_N25Q_STEP_B
    SPI_FLASH_INS_SE4B                = 0xDC, /* sector erase (N25QxxxA8 only) */
#endif
    SPI_FLASH_INS_DE                  = 0xC4, /* die erase */
#ifdef SUPPORT_N25Q_STEP_B
    SPI_FLASH_INS_BE                  = 0xC7, /* bulk erase (N25QxxxA8 only) */
#endif

    SPI_FLASH_INS_PER                 = 0x7A, /* program Erase Resume */
    SPI_FLASH_INS_PES                 = 0x75, /* program Erase Suspend */

    /* OTP operations */
    SPI_FLASH_INS_RDOTP               = 0x4B, /* read OTP array */
    SPI_FLASH_INS_PROTP               = 0x42, /* program OTP array */

    /* 4-BYTE ADDRESS operation  */
    SPI_FLASH_4B_MODE_ENTER           = 0xB7, /* enter 4-byte address mode */
    SPI_FLASH_4B_MODE_EXIT            = 0xE9, /* exit 4-byte address mode */

    /* DEEP POWER-DOWN operation */
    SPI_FLASH_INS_ENTERDPD            = 0xB9, /* enter deep power-down */
    SPI_FLASH_INS_RELEASEDPD          = 0xA8  /* release deep power-down */
};

/******** InstructionsType ********/
typedef enum
{
    InstructionWriteEnable,
    InstructionWriteDisable,

    ReadDeviceIdentification,
    ReadManufacturerIdentification,

    ReadStatusRegister,
    WriteStatusRegister,

    Read,
    FastRead,
    DualOutputFastRead,
    DualInputOutputFastRead,
    QuadOutputFastRead,
    QuadInputOutputFastRead,
    ReadFlashDiscovery,

    PageProgram,
    DualInputProgram,
    DualInputExtendedFastProgram,
    QuadInputProgram,
    QuadInputExtendedFastProgram,

    SubSectorErase,
    SectorErase,
    DieErase,
    BulkErase,
} InstructionType;

/******** ReturnType ********/
typedef enum
{
    Flash_Success,
    Flash_AddressInvalid,
    Flash_MemoryOverflow,
    Flash_PageEraseFailed,
    Flash_PageNrInvalid,
    Flash_SubSectorNrInvalid,
    Flash_SectorNrInvalid,
    Flash_FunctionNotSupported,
    Flash_NoInformationAvailable,
    Flash_OperationOngoing,
    Flash_OperationTimeOut,
    Flash_ProgramFailed,
    Flash_SectorProtected,
    Flash_SectorUnprotected,
    Flash_SectorProtectFailed,
    Flash_SectorUnprotectFailed,
    Flash_SectorLocked,
    Flash_SectorUnlocked,
    Flash_SectorLockDownFailed,
    Flash_WrongType
} ReturnType;

/******** SectorType ********/
typedef uint16_t uSectorType; // since N25Q256

/******** SubSectorType ********/
typedef uint16_t uSubSectorType;

/******** PageType ********/
typedef uint16_t uPageType;

/******** AddrType ********/
typedef uint32_t uAddrType;

/******** ParameterType ********/
typedef union
{
    /**** WriteEnable has no parameters ****/

    /**** WriteDisable has no parameters ****/

    /**** ReadDeviceIdentification Parameters ****/
    struct
    {
        uint32_t ucDeviceIdentification;
    } ReadDeviceIdentification;

    /**** ReadManufacturerIdentification Parameters ****/
    struct
    {
        uint8_t ucManufacturerIdentification;
    } ReadManufacturerIdentification;

    /**** ReadStatusRegister Parameters ****/
    struct
    {
        uint8_t ucStatusRegister;
    } ReadStatusRegister;

    /**** WriteStatusRegister Parameters ****/
    struct
    {
        uint8_t ucStatusRegister;
    } WriteStatusRegister;

    /**** Read Parameters ****/
    struct
    {
        uAddrType udAddr;
        uint32_t udNrOfElementsToRead;
        void *pArray;
    } Read;

    /**** PageProgram Parameters ****/
    struct
    {
        uAddrType udAddr;
        uint32_t udNrOfElementsInArray;
        void *pArray;
    } PageProgram;

    /**** SectorErase Parameters ****/
    struct
    {
        uSectorType ustSectorNr;
    } SectorErase;

    /***** BulkErase has no parameters ****/

    /**** Clear  has no parameters ****/

} ParameterType;


typedef struct _FLASH_DESCRIPTION
{
    uint32_t        FlashId;
    uint8_t        FlashType;
    uint32_t         StartingAddress;    /* Start Address of the Flash Device */
    uint32_t         FlashAddressMask;
    uint32_t         FlashSectorCount;
    uint32_t         FlashSubSectorCount;
    uint32_t        FlashSubSectorSize_bit;
    uint32_t         FlashPageSize;
    uint32_t        FlashPageCount;
    uint32_t        FlashSectorSize;
    uint32_t        FlashSectorSize_bit;
    uint32_t        FlashSubSectorSize;
    uint32_t         FlashSize;
    uint32_t        FlashOTPSize;
    uint8_t        FlashDieCount;
    uint32_t        FlashDieSize;
    uint32_t        FlashDieSize_bit;
    uint32_t        Size;                /* The density of flash device in bytes */
    uint32_t        BufferSize;            /* In bytes */
    uint8_t        DataWidth;            /* In bytes */
    AddressMode        NumAddrByte;        /* Num of bytes used to address memory */

}  FLASH_DESCRIPTION, *PFLASH_DESCRIPTION;

/* FLASH_OPERATION
 *
 * This object set low-level flash device operations
 */

typedef struct _FLASH_OPERATION
{
    uAddrType  (*BlockOffset)(uSectorType);
    ReturnType (*DeviceId)(uint32_t * );
    ReturnType (*ReadStatusRegister)(uint8_t *);
    ReturnType (*DataProgram)(InstructionType, ParameterType *);
    ReturnType (*DataRead)(InstructionType, ParameterType *);
    ReturnType (*SectorErase)(uSectorType);
    ReturnType (*SubSectorErase)(uSectorType);
    ReturnType (*DieErase)(uSectorType);
    ReturnType (*BulkErase)(uSectorType);
    ReturnType (*WriteEnable)(void);
    ReturnType (*WriteDisable)(void);
    ReturnType (*ProgramEraseSuspend)(void);
    ReturnType (*ProgramEraseResume)(void);
    ReturnType (*ClearFlagStatusRegister)(void);
    ReturnType (*ReadNVConfigurationRegister)(uint16_t *);
    ReturnType (*ReadVolatileConfigurationRegister)(uint8_t *);
    ReturnType (*ReadVolatileEnhancedConfigurationRegister)(uint8_t *);
    ReturnType (*ReadFlagStatusRegister)(uint8_t *);
    ReturnType (*WriteNVConfigurationRegister)(uint16_t);
    ReturnType (*WriteVolatileConfigurationRegister)(uint8_t);
    ReturnType (*WriteVolatileEnhancedConfigurationRegister)(uint8_t);
    ReturnType (*Enter4ByteAddressMode) (void);
    ReturnType (*Exit4ByteAddressMode) (void);
    ReturnType (*LockSector)(uAddrType, uint32_t);
    ReturnType (*UnlockAllSector)(void);
    ReturnType (*OTPProgram)(uint8_t *, uint32_t);
    ReturnType (*OTPRead)(uint8_t *, uint32_t);

} FLASH_OPERATION;

typedef struct
{
    FLASH_DESCRIPTION     Desc;
    FLASH_OPERATION       GenOp;

} FLASH_DEVICE_OBJECT;

/******************************************************************************
    Standard functions
*******************************************************************************/


/******************************************************************************
    Standard functions
*******************************************************************************/
uAddrType BlockOffset(uSectorType uscSectorNr);
ReturnType FlashReadDeviceIdentification(uint32_t *uwpDeviceIdentification);
ReturnType Driver_Init(FLASH_DEVICE_OBJECT *flash_device_object);
ReturnType FlashWriteEnable(void);
ReturnType FlashWriteDisable(void);
ReturnType FlashReadStatusRegister(uint8_t *ucpStatusRegister);
ReturnType FlashWriteStatusRegister(uint8_t ucStatusRegister);
ReturnType FlashGenProgram(uAddrType udAddr, uint8_t *pArray , uint32_t udNrOfElementsInArray, uint8_t ubSpiInstruction);
ReturnType DataProgram(InstructionType insInstruction, ParameterType *fp);
ReturnType DataRead(InstructionType insInstruction, ParameterType *fp);
ReturnType FlashDataProgram(uAddrType udAddr, uint8_t *pArray , uint16_t udNrOfElementsInArray, uint8_t ubSpiInstruction);
ReturnType FlashDataRead( uAddrType udAddr, uint8_t *ucpElements, uint32_t udNrOfElementsToRead, uint8_t insInstruction);
ReturnType FlashSectorErase(uSectorType uscSectorNr);
ReturnType FlashSubSectorErase(uSectorType uscSectorNr);
ReturnType FlashDieErase(uSectorType uscDieNr);
ReturnType FlashBulkErase(void);
ReturnType FlashProgramEraseResume(void);
ReturnType FlashProgramEraseSuspend(void);
ReturnType FlashClearFlagStatusRegister(void);
ReturnType FlashReadNVConfigurationRegister(uint16_t *ucpNVConfigurationRegister);
ReturnType FlashReadVolatileConfigurationRegister(uint8_t *ucpVolatileConfigurationRegister);
ReturnType FlashReadVolatileEnhancedConfigurationRegister(uint8_t *ucpVolatileEnhancedConfigurationRegister);
ReturnType FlashReadFlagStatusRegister(uint8_t *ucpFlagStatusRegister);
ReturnType FlashWriteNVConfigurationRegister(uint16_t ucpNVConfigurationRegister);
ReturnType FlashWriteVolatileConfigurationRegister(uint8_t ucpVolatileConfigurationRegister);
ReturnType FlashWriteVolatileEnhancedConfigurationRegister(uint8_t ucVolatileEnhancedConfigurationRegister);
ReturnType FlashEnter4ByteAddressMode(void);
ReturnType FlashExit4ByteAddressMode(void);
ReturnType FlashLockSector(uAddrType address, uint32_t len);
ReturnType FlashUnlockAllSector(void);
ReturnType FlashOTPProgram(uint8_t *pArray , uint32_t udNrOfElementsInArray);
ReturnType FlashOTPRead(uint8_t *ucpElements, uint32_t udNrOfElementsToRead);
ReturnType FlashReadLockRegister(uAddrType address,  uint8_t * val);
ReturnType FlashWriteLockRegister(uAddrType address,  uint8_t * val);
ReturnType FlashLockOneSector(uAddrType address);
ReturnType FlashUnlockOneSector(uAddrType address);

/******************************************************************************
    Utility functions
*******************************************************************************/
#ifdef VERBOSE
int8_t *FlashErrorStr( ReturnType rErrNum );
#endif

ReturnType FlashTimeOut( uint32_t udSeconds );

/*******************************************************************************
List of Errors and Return values, Explanations and Help.
********************************************************************************

Error Name:   Flash_AddressInvalid
Description:  The address given is out of the range of the Flash device.
Solution:     Check whether the address is in the valid range of the
              Flash device.
********************************************************************************

Error Name:   Flash_PageEraseFailed
Description:  The Page erase Instruction did not complete successfully.
Solution:     Try to erase the Page again. If this fails once more, the device
              may be faulty and need to be replaced.
********************************************************************************

Error Name:   Flash_PageNrInvalid
Note:         The Flash memory is not at fault.
Description:  A Page has been selected (Parameter), which is not
              within the valid range. Valid Page numbers are from 0 to
              FLASH_PAGE_COUNT - 1.
Solution:     Check that the Page number given is in the valid range.
********************************************************************************

Error Name:   Flash_SectorNrInvalid
Note:         The Flash memory is not at fault.
Description:  A Sector has been selected (Parameter), which is not
              within the valid range. Valid Page numbers are from 0 to
              FLASH_SECTOR_COUNT - 1.
Solution:     Check that the Sector number given is in the valid range.
********************************************************************************

Return Name:  Flash_FunctionNotSupported
Description:  The user has attempted to make use of a functionality not
              available on this Fash device (and thus not provided by the
              software drivers).
Solution:     This may happen after changing Flash SW Drivers in existing
              environments. For example an application tries to use a
              functionality which is no longer provided with the new device.
********************************************************************************

Return Name:  Flash_NoInformationAvailable
Description:  The system cannot give any additional information about the error.
Solution:     None
********************************************************************************

Error Name:   Flash_OperationOngoing
Description:  This message is one of two messages that are given by the TimeOut
              subroutine. It means that the ongoing Flash operation is still within
              the defined time frame.
********************************************************************************

Error Name:   Flash_OperationTimeOut
Description:  The Program/Erase Controller algorithm could not finish an
              operation successfully. It should have set bit 7 of the Status
              Register from 0 to 1, but that did not happen within a predetermined
              time. The program execution was therefore cancelled by a
              timeout. This may be because the device is damaged.
Solution:     Try the previous Instruction again. If it fails a second time then it
              is likely that the device will need to be replaced.
********************************************************************************

Error Name:   Flash_ProgramFailed
Description:  The value that should be programmed has not been written correctly
              to the Flash memory.
Solutions:    Make sure that the Page which is supposed to receive the value
              was erased successfully before programming. Try to erase the Page and
              to program the value again. If it fails again then the device may
              be faulty.
********************************************************************************

Error Name:   Flash_WrongType
Description:  This message appears if the Manufacture and Device Identifications read from
              the current Flash device do not match the expected identifier
              codes. This means that the source code is not explicitely written for
              the currently used Flash chip. It may work, but the operation cannot be
              guaranteed.
Solutions:    Use a different Flash chip with the target hardware or contact
              STMicroelectronics for a different source code library.
********************************************************************************

Return Name:  Flash_Success
Description:  This value indicates that the Flash memory Instruction was executed
              correctly.
********************************************************************************/

/******************************************************************************
    External variable declaration
*******************************************************************************/

/* none in this version of the release */

/*******************************************************************************
Status Register Definitions (see Datasheet)
*******************************************************************************/
enum
{
    SPI_FLASH_SRWD        = 0x80,                /* status Register Write Protect */
    SPI_FLASH_BP3        = 0x40,                /* block Protect Bit3 */
    SPI_FLASH_TB        = 0x20,                /* top/Bottom bit */
    SPI_FLASH_BP2        = 0x10,                /* block Protect Bit2 */
    SPI_FLASH_BP1        = 0x08,                /* block Protect Bit1 */
    SPI_FLASH_BP0        = 0x04,                /* block Protect Bit0 */
    SPI_FLASH_WEL        = 0x02,                /* write Enable Latch */
    SPI_FLASH_WIP        = 0x01                /* write/Program/Erase in progress bit */
};

/*******************************************************************************
flag Status Register Definitions (see Datasheet)
*******************************************************************************/
enum
{
    SPI_FSR_PROG_ERASE_CTL        = 0x80,
    SPI_FSR_ERASE_SUSP            = 0x40,
    SPI_FSR_ERASE                = 0x20,
    SPI_FSR_PROGRAM                = 0x10,
    SPI_FSR_VPP                    = 0x08,
    SPI_FSR_PROG_SUSP            = 0x04,
    SPI_FSR_PROT                = 0x02,
    SPI_FSR_ADDR_MODE            = 0x01
};


/*******************************************************************************
Specific Function Prototypes
*******************************************************************************/
typedef unsigned char BOOL;

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#ifndef NULL_PTR
#define NULL_PTR 0x0
#endif

BOOL IsFlashBusy(void);
BOOL IsFlashWELBusy(void);


/*******************************************************************************
List of Specific Errors and Return values, Explanations and Help.
*******************************************************************************

// none in this version of the release
********************************************************************************/

#endif /* __N25Q__H__  */
/* In order to avoid a repeated usage of the header file */

/*******************************************************************************
     End of file
********************************************************************************/
