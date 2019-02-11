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
 *  \defgroup NOR_FLASH NOR Flash Library
 *
 *  @{
 */
/**
 *  \file     nor_flash.h
 *
 *  \brief    This file contains the interfaces present in the
 *            Nor Flash Library.
 *            This also contains some related macros, structures and enums.
 */

#ifndef NOR_H_
#define NOR_H_

#ifdef __cplusplus
extern  "C" {
#endif

/* ========================================================================== */
/*                           Macros & Typedefs                                */
/* ========================================================================== */
/**
 * \brief  This typedef contains the prototype of Norflash lib print function.
 *
 */
typedef int32_t (*NOR_FlashInitPrintFxnPtr)(const char *format);

/**
 * \brief  This macro defines the Boolean that is used for True.
 */
#define NOR_FLASH_SUCCESS                              ((uint32_t) 1U)

/**
 * \brief  This macro defines the Boolean that is used for False.
 */
#define NOR_FLASH_FAIL                                 ((uint32_t) 0U)

/* GENERIC BUS width defines */
#ifndef BUS_8BIT
  #define BUS_8BIT            (0x01) /**< Bus width is 8 bit */
#endif
#ifndef BUS_16BIT
  #define BUS_16BIT           (0x02) /**< Bus width is 16 bit */
#endif
#ifndef BUS_32BIT
  #define BUS_32BIT           (0x04) /**< Bus width is 32 bit */
#endif
#ifndef BUS_64BIT
  #define BUS_64BIT           (0x08) /**< Bus width is 64 bit */
#endif

/* Generic bit mask defines */
#ifndef BIT0
  #define BIT0    (uint32_t) (0x00000001) /**< Bit width is 0 */
  #define BIT1    (uint32_t) (0x00000002) /**< Bit width is 1 */
  #define BIT2    (uint32_t) (0x00000004) /**< Bit width is 2 */
  #define BIT3    (uint32_t) (0x00000008) /**< Bit width is 3 */
  #define BIT4    (uint32_t) (0x00000010) /**< Bit width is 4 */
  #define BIT5    (uint32_t) (0x00000020) /**< Bit width is 5 */
  #define BIT6    (uint32_t) (0x00000040) /**< Bit width is 6 */
  #define BIT7    (uint32_t) (0x00000080) /**< Bit width is 7 */
  #define BIT8    (uint32_t) (0x00000100) /**< Bit width is 8 */
  #define BIT9    (uint32_t) (0x00000200) /**< Bit width is 9 */
  #define BIT10   (uint32_t) (0x00000400) /**< Bit width is 10 */
  #define BIT11   (uint32_t) (0x00000800) /**< Bit width is 11 */
  #define BIT12   (uint32_t) (0x00001000) /**< Bit width is 12 */
  #define BIT13   (uint32_t) (0x00002000) /**< Bit width is 13 */
  #define BIT14   (uint32_t) (0x00004000) /**< Bit width is 14 */
  #define BIT15   (uint32_t) (0x00008000) /**< Bit width is 15 */
  #define BIT16   (uint32_t) (0x00010000) /**< Bit width is 16 */
  #define BIT17   (uint32_t) (0x00020000) /**< Bit width is 17 */
  #define BIT18   (uint32_t) (0x00040000) /**< Bit width is 18 */
  #define BIT19   (uint32_t) (0x00080000) /**< Bit width is 19 */
  #define BIT20   (uint32_t) (0x00100000) /**< Bit width is 20 */
  #define BIT21   (uint32_t) (0x00200000) /**< Bit width is 21 */
  #define BIT22   (uint32_t) (0x00400000) /**< Bit width is 22 */
  #define BIT23   (uint32_t) (0x00800000) /**< Bit width is 23 */
  #define BIT24   (uint32_t) (0x01000000) /**< Bit width is 24 */
  #define BIT25   (uint32_t) (0x02000000) /**< Bit width is 25 */
  #define BIT26   (uint32_t) (0x04000000) /**< Bit width is 26 */
  #define BIT27   (uint32_t) (0x08000000) /**< Bit width is 27 */
  #define BIT28   (uint32_t) (0x10000000) /**< Bit width is 28 */
  #define BIT29   (uint32_t) (0x20000000) /**< Bit width is 29 */
  #define BIT30   (uint32_t) (0x40000000) /**< Bit width is 30 */
  #define BIT31   (uint32_t) (0x80000000) /**< Bit width is 31 */
#endif

/**
 * \name DEFINES for AMD Basic Command Set
 *  @{
 */
/**
 * \brief  AMD CMD PREFIX 0
 */
#define AMD_CMD0                    (uint32_t) (0xAA)
/**
 * \brief  AMD CMD PREFIX 1
 */
#define AMD_CMD1                    (uint32_t) (0x55)
/**
 * \brief  AMD CMD0 Offset
 */
#define AMD_CMD0_ADDR               (uint32_t) (0x555)
/**
 * \brief  AMD CMD1 Offset
 */
#define AMD_CMD1_ADDR               (uint32_t) (0x2AA)
/**
 * \brief  AMD CMD2 Offset
 */
#define AMD_CMD2_ADDR               (uint32_t) (0x555)
/**
 * \brief  AMD ID CMD
 */
#define AMD_ID_CMD                  (uint32_t) (0x90)
/**
 * \brief  Manufacturer ID offset
 */
#define AMD_MANFID_ADDR             (uint32_t) (0x00)
/**
 * \brief  First device ID
 */
#define AMD_DEVID_ADDR0             (uint32_t) (0x01)
/**
 * \brief  Offset for 2nd
 */
#define AMD_DEVID_ADDR1             (uint32_t) (0x0E)
/**
 * \brief  Offset for 3rd byte of 3 byte ID
 */
#define AMD_DEVID_ADDR2             (uint32_t) (0x0F)
/**
 * \brief  First-byte ID value for 3-byte ID
 */
#define AMD_ID_MULTI                (uint32_t) (0x7E)
/**
 * \brief  AMD Device Reset Command
 */
#define AMD_RESET                   (uint32_t) (0xF0)
/**
 * \brief  Block erase setup
 */
#define AMD_BLK_ERASE_SETUP_CMD     (uint32_t) (0x80)
/**
 * \brief  Block erase confirm
 */
#define AMD_BLK_ERASE_CMD           (uint32_t) (0x30)
/**
 * \brief  Block erase check value
 */
#define AMD_BLK_ERASE_DONE          (uint32_t) (0xFF)
/**
 * \brief  AMD simple Writecommand
 */
#define AMD_PROG_CMD                (uint32_t) (0xA0)
/**
 * \brief  AMD write buffer load command
 */
#define AMD_WRT_BUF_LOAD_CMD        (uint32_t) (0x25)
/**
 * \brief  AMD write buffer confirm command
 */
#define AMD_WRT_BUF_CONF_CMD        (uint32_t) (0x29)
/** @} */

/**
 * \name DEFINES for Intel Basic Command Set
 *  @{
 */
/**
 * \brief Intel ID CMD
 */
#define INTEL_ID_CMD                (uint32_t) (0x90)
/**
 * \brief Manufacturer ID offset
 */
#define INTEL_MANFID_ADDR           (uint32_t) (0x00)
/**
 * \brief Device ID offset
 */
#define INTEL_DEVID_ADDR            (uint32_t) (0x01)
/**
 * \brief Intel Device Reset Command
 */
#define INTEL_RESET                 (uint32_t) (0xFF)
/**
 * \brief Intel Erase command
 */
#define INTEL_ERASE_CMD0            (uint32_t) (0x20)
/**
 * \brief Intel Erase command
 */
#define INTEL_ERASE_CMD1            (uint32_t) (0xD0)
/**
 * \brief Intel simple write command
 */
#define INTEL_WRITE_CMD             (uint32_t) (0x40)
/**
 * \brief Intel write buffer load command
 */
#define INTEL_WRT_BUF_LOAD_CMD      (uint32_t) (0xE8)
/**
 * \brief Intel write buffer confirm command
 */
#define INTEL_WRT_BUF_CONF_CMD      (uint32_t) (0xD0)
/**
 * \brief Intel lock mode command
 */
#define INTEL_LOCK_CMD0             (uint32_t) (0x60)
/**
 * \brief Intel lock command
 */
#define INTEL_LOCK_BLOCK_CMD        (uint32_t) (0x01)
/**
 * \brief Intel unlock command
 */
#define INTEL_UNLOCK_BLOCK_CMD      (uint32_t) (0xD0)
/**
 * \brief Intel clear status command
 */
#define INTEL_CLEARSTATUS_CMD       (uint32_t) (0x50)
/** @} */

/**
 * \name DEFINES for CFI Commands and Table
 *  @{
 */
/**
 * \brief CFI Entry command
 */
#define CFI_QRY_CMD             (uint32_t) (0x98U)
/**
 * \brief CFI Exit command
 */
#define CFI_EXIT_CMD            (uint32_t) (0xF0U)
/** @} */

/**
 * \brief CFI address locations
 */
#define CFI_QRY_CMD_ADDR        (uint32_t) (0x55U)

/* CFI Table Offsets in Bytes */
#define CFI_Q                   (uint32_t) (0x10) /**< Table offset for Q */
#define CFI_R                   (uint32_t) (0x11) /**< Table offset for R */
#define CFI_Y                   (uint32_t) (0x12) /**< Table offset for Y */
#define CFI_CMDSET              (uint32_t) (0x13) /**< Table offset for CMDSET */
#define CFI_CMDSETADDR          (uint32_t) (0x15) /**< Table offset for CMDSETADDR */
#define CFI_ALTCMDSET           (uint32_t) (0x17) /**< Table offset for ALTCMDSET */
#define CFI_ALTCMDSETADDR       (uint32_t) (0x19) /**< Table offset for ALTCMDSETADDR */
#define CFI_MINVCC              (uint32_t) (0x1B) /**< Table offset for MINVCC */
#define CFI_MAXVCC              (uint32_t) (0x1C) /**< Table offset for MAXVCC */
#define CFI_MINVPP              (uint32_t) (0x1D) /**< Table offset for MINVPP */
#define CFI_MAXVPP              (uint32_t) (0x1E) /**< Table offset for MAXVPP */
#define CFI_TYPBYTEPGMTIME      (uint32_t) (0x1F) /**< Table offset for TYPBYTEPGMTIME */
#define CFI_TYPBUFFERPGMTIME    (uint32_t) (0x20) /**< Table offset for TYPBUFFERPGMTIME */
#define CFI_TYPBLOCKERASETIME   (uint32_t) (0x21) /**< Table offset for TYPBLOCKERASETIME */
#define CFI_TYPCHIPERASETIME    (uint32_t) (0x22) /**< Table offset for TYPCHIPERASETIME */
#define CFI_MAXBYTEPGMTIME      (uint32_t) (0x23) /**< Table offset for MAXBYTEPGMTIME */
#define CFI_MAXBUFFERPGMTIME    (uint32_t) (0x24) /**< Table offset for MAXBUFFERPGMTIME */
#define CFI_MAXBLOCKERASETIME   (uint32_t) (0x25) /**< Table offset for MAXBLOCKERASETIME */
#define CFI_MAXCHIPERASETIME    (uint32_t) (0x26) /**< Table offset for MAXCHIPERASETIME */
#define CFI_DEVICESIZE          (uint32_t) (0x27) /**< Table offset for DEVICESIZE */
#define CFI_INTERFACE           (uint32_t) (0x28) /**< Table offset for INTERFACE */
#define CFI_WRITESIZE           (uint32_t) (0x2A) /**< Table offset for WRITESIZE */
#define CFI_NUMBLKREGIONS       (uint32_t) (0x2C) /**< Table offset for NUMBLKREGIONS */
#define CFI_BLKREGIONS          (uint32_t) (0x2D) /**< Table offset for BLKREGIONS */
#define CFI_BLKREGIONSIZE       (uint32_t) (0x04) /**< Table offset for BLKREGIONSIZE */

/**
 * \brief Maximum number of block regions supported
 */
#define CFI_MAXREGIONS          (0x06)

/* ========================================================================== */
/*                         Structures and Enums                               */
/* ========================================================================== */
/**
 * \brief Supported Flash Manufacturers
 */
typedef enum NOR_MANF_ID_
{
    UNKNOWN_ID = 0x00,
    AMD        = 0x01,
    FUJITSU    = 0x04,
    INTEL      = 0x89,
    MICRON     = 0x2C,
    SAMSUNG    = 0xEC,
    SHARP      = 0xB0
}
NOR_ManfID;

/**
 * \brief Supported CFI command sets
 */
typedef enum NOR_CMD_SET_
{
    UNKNOWN_CMDSET     = 0x0000,
    INTEL_EXT_CMDSET   = 0x0001,
    AMD_BASIC_CMDSET   = 0x0002,
    INTEL_BASIC_CMDSET = 0x0003,
    AMD_EXT_CMDSET     = 0x0004,
    MITSU_BASIC_CMDSET = 0x0100,
    MITSU_EXT_CMDSET   = 0x0101
}
NOR_CmdSet;

/**
 * \brief Struct to hold Init parametrs for Nor flash
 */
typedef struct
{
    NOR_FlashInitPrintFxnPtr norFlashInitPrintFxnPtr;
    /**< Print function
     */
}
Nor_InitPrms_t;

/**
 * \brief Struct to hold discovered flash parameters
 */
typedef struct NOR_INFO_
{
    uint32_t   flashBase;
    /**< 32-bit address of flash start
     */
    uint8_t    CSOffset;
    /**< index of what CS region are we in
     */
    uint8_t    busWidth;
    /**< 8-bit or 16-bit bus width
     */
    uint8_t    chipOperatingWidth;
    /**< The operating width of each chip
     */
    uint8_t    maxTotalWidth;
    /**< Maximum extent of width of all chips combined - determines
         offset shifts
     */
    uint32_t   flashSize;
    /**< Size of NOR flash regions in bytes (numberDevices * size of
         one device)
     */
    uint32_t   bufferSize;
    /**< Size of write buffer
     */
    NOR_CmdSet commandSet;
    /**< command set id (see CFI documentation)
     */
    uint8_t    numberDevices;
    /**< Number of deives used in parallel
     */
    uint8_t    numberRegions;
    /**< Number of regions of contiguous regions of same block size
     */
    uint32_t   numberBlocks[CFI_MAXREGIONS];
    /**< Number of blocks in a region
     */
    uint32_t   blockSize[CFI_MAXREGIONS];
    /**< Size of the blocks in a region
      */
    NOR_ManfID manfID;
    /**< Manufacturer's ID
     */
    uint16_t   devID1;
    /**< Device ID
     */
    uint16_t   devID2;
    /**< Used for AMD 3-byte ID devices
     */
}
NOR_InfoObj, *NOR_InfoHandle; /**< NOR Info Handle */

/**
 * \brief Union for Nor data
 */
typedef union
{
    uint8_t  c;
    /**< Varibale to store 8 bit data
     */
    uint16_t w;
    /**< Varibale to store 16 bit data
     */
    uint32_t l;
    /**< Varibale to store 32 bit data
     */
}
NOR_Data;

/**
 * \brief Union for Nor data pointer
 */
typedef union
{
    volatile uint8_t  *cp;
    /**< Pointer to 8 bit data
     */
    volatile uint16_t *wp;
    /**< Pointer to 16 bit data
     */
    volatile uint32_t *lp;
    /**< Pointer to 32 bit data
     */
}
NOR_Ptr;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief   API to open access interface with NOr flash
 *
 * \param   baseCSAddr    Nor Flash base address
 * \param   busWidth      Data bus width
 *
 * \return  Struct holding discovered flash parameters
 */
extern NOR_InfoHandle NOR_open(uint32_t baseCSAddr, uint8_t busWidth);

/**
 * \brief   API to write data on NOR flash
 *
 * \param   hNorInfo      Struct holding discovered flash parameters
 * \param   writeAddress  Data write address
 * \param   numBytes      Number of bytes to be written
 * \param   readAddress   Data read address
 *
 * \return  NOR_FLASH_SUCCESS in case of success -ve number otherwise
 */
extern uint32_t NOR_writeBytes(NOR_InfoHandle hNorInfo, uint32_t writeAddress,
                               uint32_t numBytes,
                               uint32_t readAddress);

/**
 * \brief   API to erase complete NOr flash
 *
 * \param   hNorInfo      Struct holding discovered flash parameters
 *
 * \return  NOR_FLASH_SUCCESS in case of success -ve number otherwise
 */
extern uint32_t NOR_globalErase(NOR_InfoHandle hNorInfo);

/**
 * \brief   API to erase the section of NOR flash
 *
 * \param   hNorInfo      Struct holding discovered flash parameters
 * \param   start_address Start address for erasing Nor flash
 * \param   size          Size of flas to be erased
 *
 * \return  NOR_FLASH_SUCCESS in case of success -ve number otherwise
 */
extern uint32_t NOR_erase(NOR_InfoHandle    hNorInfo,
                          volatile uint32_t start_address,
                          volatile uint32_t size);

/**
 * \brief   Api to get the block address and size info
 *
 * \param   hNorInfo      Struct holding discovered flash parameters
 * \param   address       Memory address
 * \param   blockSize     Pointer to get size of the block
 * \param   blockAddr     Pointer to get address of the block
 *
 * \return  NOR_FLASH_SUCCESS in case of success -ve number otherwise
 */
extern uint32_t NOR_getBlockInfo(NOR_InfoHandle hNorInfo, uint32_t address,
                                 uint32_t *blockSize,
                                 uint32_t *blockAddr);

/**
 * \brief   This API initializes the default parameters for Nor Flash Lib.
 *
 * \param   pNor_InitPrms Nor Flash Lib Initialization parameters.
 *
 * \return  None.
 */
void NOR_InitParmsDefault(Nor_InitPrms_t *pNor_InitPrms);

/**
 * \brief   This API initializes the actual init parameters for Nor Flash Lib.
 *
 * \param   pNor_InitPrms Nor Flash Lib Initialization parameters.
 *
 * \return  None.
 */
void NOR_Init(const Nor_InitPrms_t *pNor_InitPrms);

#ifdef __cplusplus
}
#endif

#endif
/** @} */
