/*
 *  Copyright (C) 2013 - 2018 Texas Instruments Incorporated - http://www.ti.com/
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
 * \file  nor.c
 * \brief  API's to nor flash.
 */
 #ifndef NOR_H_
#define NOR_H_

/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/*
 * \brief  This typedef contains the prototype of Norflash lib print function.
 *
 */
typedef int32_t (*NOR_FlashInitPrintFxnPtr)(const char *format);

/* GENERIC BUS width defines */
#ifndef BUS_8BIT
  #define BUS_8BIT            (0x01)
#endif
#ifndef BUS_16BIT
  #define BUS_16BIT           (0x02)
#endif
#ifndef BUS_32BIT
  #define BUS_32BIT           (0x04)
#endif
#ifndef BUS_64BIT
  #define BUS_64BIT           (0x08)
#endif

/* Generic bit mask defines */
#ifndef BIT0
  #define BIT0    (uint32_t) (0x00000001)
  #define BIT1    (uint32_t) (0x00000002)
  #define BIT2    (uint32_t) (0x00000004)
  #define BIT3    (uint32_t) (0x00000008)
  #define BIT4    (uint32_t) (0x00000010)
  #define BIT5    (uint32_t) (0x00000020)
  #define BIT6    (uint32_t) (0x00000040)
  #define BIT7    (uint32_t) (0x00000080)
  #define BIT8    (uint32_t) (0x00000100)
  #define BIT9    (uint32_t) (0x00000200)
  #define BIT10   (uint32_t) (0x00000400)
  #define BIT11   (uint32_t) (0x00000800)
  #define BIT12   (uint32_t) (0x00001000)
  #define BIT13   (uint32_t) (0x00002000)
  #define BIT14   (uint32_t) (0x00004000)
  #define BIT15   (uint32_t) (0x00008000)
  #define BIT16   (uint32_t) (0x00010000)
  #define BIT17   (uint32_t) (0x00020000)
  #define BIT18   (uint32_t) (0x00040000)
  #define BIT19   (uint32_t) (0x00080000)
  #define BIT20   (uint32_t) (0x00100000)
  #define BIT21   (uint32_t) (0x00200000)
  #define BIT22   (uint32_t) (0x00400000)
  #define BIT23   (uint32_t) (0x00800000)
  #define BIT24   (uint32_t) (0x01000000)
  #define BIT25   (uint32_t) (0x02000000)
  #define BIT26   (uint32_t) (0x04000000)
  #define BIT27   (uint32_t) (0x08000000)
  #define BIT28   (uint32_t) (0x10000000)
  #define BIT29   (uint32_t) (0x20000000)
  #define BIT30   (uint32_t) (0x40000000)
  #define BIT31   (uint32_t) (0x80000000)
#endif

/**************** DEFINES for AMD Basic Command Set **************/
/* AMD CMD PREFIX 0 */
#define AMD_CMD0                    (uint32_t) (0xAA)
/* AMD CMD PREFIX 1 */
#define AMD_CMD1                    (uint32_t) (0x55)
/* AMD CMD0 Offset */
#define AMD_CMD0_ADDR               (uint32_t) (0x555)
/* AMD CMD1 Offset */
#define AMD_CMD1_ADDR               (uint32_t) (0x2AA)
/* AMD CMD2 Offset */
#define AMD_CMD2_ADDR               (uint32_t) (0x555)
/* AMD ID CMD */
#define AMD_ID_CMD                  (uint32_t) (0x90)
/* Manufacturer ID offset */
#define AMD_MANFID_ADDR             (uint32_t) (0x00)
/* First device ID offset */
#define AMD_DEVID_ADDR0             (uint32_t) (0x01)
/* Offset for 2nd byte of 3 byte ID */
#define AMD_DEVID_ADDR1             (uint32_t) (0x0E)
/* Offset for 3rd byte of 3 byte ID */
#define AMD_DEVID_ADDR2             (uint32_t) (0x0F)
/* First-byte ID value for 3-byte ID */
#define AMD_ID_MULTI                (uint32_t) (0x7E)
/* AMD Device Reset Command */
#define AMD_RESET                   (uint32_t) (0xF0)
/* Block erase setup */
#define AMD_BLK_ERASE_SETUP_CMD     (uint32_t) (0x80)
/* Block erase confirm */
#define AMD_BLK_ERASE_CMD           (uint32_t) (0x30)
/* Block erase check value */
#define AMD_BLK_ERASE_DONE          (uint32_t) (0xFF)
/* AMD simple Writecommand */
#define AMD_PROG_CMD                (uint32_t) (0xA0)
/* AMD write buffer load command */
#define AMD_WRT_BUF_LOAD_CMD        (uint32_t) (0x25)
/* AMD write buffer confirm command */
#define AMD_WRT_BUF_CONF_CMD        (uint32_t) (0x29)

/**************** DEFINES for Intel Basic Command Set **************/
/* Intel ID CMD */
#define INTEL_ID_CMD                (uint32_t) (0x90)
/* Manufacturer ID offset */
#define INTEL_MANFID_ADDR           (uint32_t) (0x00)
/* Device ID offset */
#define INTEL_DEVID_ADDR            (uint32_t) (0x01)
/* Intel Device Reset Command */
#define INTEL_RESET                 (uint32_t) (0xFF)
/* Intel Erase command */
#define INTEL_ERASE_CMD0            (uint32_t) (0x20)
/* Intel Erase command */
#define INTEL_ERASE_CMD1            (uint32_t) (0xD0)
/* Intel simple write command */
#define INTEL_WRITE_CMD             (uint32_t) (0x40)
/* Intel write buffer load command */
#define INTEL_WRT_BUF_LOAD_CMD      (uint32_t) (0xE8)
/* Intel write buffer confirm command */
#define INTEL_WRT_BUF_CONF_CMD      (uint32_t) (0xD0)
/* Intel lock mode command */
#define INTEL_LOCK_CMD0             (uint32_t) (0x60)
/* Intel lock command */
#define INTEL_LOCK_BLOCK_CMD        (uint32_t) (0x01)
/* Intel unlock command */
#define INTEL_UNLOCK_BLOCK_CMD      (uint32_t) (0xD0)
/* Intel clear status command */
#define INTEL_CLEARSTATUS_CMD       (uint32_t) (0x50)

/**************** DEFINES for CFI Commands and Table **************/

/* CFI Entry and Exit commands */
#define CFI_QRY_CMD             (uint32_t) (0x98U)
#define CFI_EXIT_CMD            (uint32_t) (0xF0U)

/* CFI address locations */
#define CFI_QRY_CMD_ADDR        (uint32_t) (0x55U)

/* CFI Table Offsets in Bytes */
#define CFI_Q                   (uint32_t) (0x10)
#define CFI_R                   (uint32_t) (0x11)
#define CFI_Y                   (uint32_t) (0x12)
#define CFI_CMDSET              (uint32_t) (0x13)
#define CFI_CMDSETADDR          (uint32_t) (0x15)
#define CFI_ALTCMDSET           (uint32_t) (0x17)
#define CFI_ALTCMDSETADDR       (uint32_t) (0x19)
#define CFI_MINVCC              (uint32_t) (0x1B)
#define CFI_MAXVCC              (uint32_t) (0x1C)
#define CFI_MINVPP              (uint32_t) (0x1D)
#define CFI_MAXVPP              (uint32_t) (0x1E)
#define CFI_TYPBYTEPGMTIME      (uint32_t) (0x1F)
#define CFI_TYPBUFFERPGMTIME    (uint32_t) (0x20)
#define CFI_TYPBLOCKERASETIME   (uint32_t) (0x21)
#define CFI_TYPCHIPERASETIME    (uint32_t) (0x22)
#define CFI_MAXBYTEPGMTIME      (uint32_t) (0x23)
#define CFI_MAXBUFFERPGMTIME    (uint32_t) (0x24)
#define CFI_MAXBLOCKERASETIME   (uint32_t) (0x25)
#define CFI_MAXCHIPERASETIME    (uint32_t) (0x26)
#define CFI_DEVICESIZE          (uint32_t) (0x27)
#define CFI_INTERFACE           (uint32_t) (0x28)
#define CFI_WRITESIZE           (uint32_t) (0x2A)
#define CFI_NUMBLKREGIONS       (uint32_t) (0x2C)
#define CFI_BLKREGIONS          (uint32_t) (0x2D)
#define CFI_BLKREGIONSIZE       (uint32_t) (0x04)

/* Maximum number of block regions supported */
#define CFI_MAXREGIONS          (0x06)

/* Supported Flash Manufacturers */
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

/* Supported CFI command sets */
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

/* ========================================================================== */
/*                         Structures                                         */
/* ========================================================================== */
typedef struct
{
    NOR_FlashInitPrintFxnPtr norFlashInitPrintFxnPtr;
}
Nor_InitPrms_t;

/* Struct to hold discovered flash parameters */
typedef struct NOR_INFO_
{
    uint32_t   flashBase;                     /* 32-bit address of flash start
                                              **/
    uint8_t    CSOffset;                      /* index of what CS region are we
                                               *in  */
    uint8_t    busWidth;                      /* 8-bit or 16-bit bus width */
    uint8_t    chipOperatingWidth;            /* The operating width of each
                                               *chip */
    uint8_t    maxTotalWidth;                 /* Maximum extent of width of all
                                               * *chips combined - determines
                                               *offset shifts */
    uint32_t   flashSize;                     /* Size of NOR flash regions in
                                               * *bytes (numberDevices * size of
                                               *one device) */
    uint32_t   bufferSize;                    /* Size of write buffer */
    NOR_CmdSet commandSet;                    /* command set id (see CFI
                                               *documentation) */
    uint8_t    numberDevices;                 /* Number of deives used in
                                               *parallel */
    uint8_t    numberRegions;                 /* Number of regions of contiguous
                                               *regions of same block size */
    uint32_t   numberBlocks[CFI_MAXREGIONS];  /* Number of blocks in a region */
    uint32_t   blockSize[CFI_MAXREGIONS];     /* Size of the blocks in a region
                                              **/
    NOR_ManfID manfID;                        /* Manufacturer's ID */
    uint16_t   devID1;                        /* Device ID */
    uint16_t   devID2;                        /* Used for AMD 3-byte ID devices
                                              **/
}
NOR_InfoObj, *NOR_InfoHandle;

typedef union
{
    uint8_t  c;
    uint16_t w;
    uint32_t l;
}
NOR_Data;

typedef union
{
    volatile uint8_t  *cp;
    volatile uint16_t *wp;
    volatile uint32_t *lp;
}
NOR_Ptr;

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
extern NOR_InfoHandle NOR_open(uint32_t baseCSAddr, uint8_t busWidth);
extern uint32_t NOR_writeBytes(NOR_InfoHandle hNorInfo, uint32_t writeAddress,
                               uint32_t numBytes,
                               uint32_t readAddress);
extern uint32_t NOR_globalErase(NOR_InfoHandle hNorInfo);
extern uint32_t NOR_erase(NOR_InfoHandle    hNorInfo,
                          volatile uint32_t start_address,
                          volatile uint32_t size);
extern uint32_t NOR_getBlockInfo(NOR_InfoHandle hNorInfo, uint32_t address,
                                 uint32_t *blockSize,
                                 uint32_t *blockAddr);

/* \brief   This API initializes the default parameters for Nor Flash Lib.
 *
 * \param   Nor_InitPrms_t         Nor Flash Lib Initialization parameters.
 *
 * \return  None.
 */
void NOR_InitParmsDefault(Nor_InitPrms_t *pNor_InitPrms);

/* \brief   This API initializes the actual init parameters for Nor Flash Lib.
 *
 * \param   Nor_InitPrms_t         Nor Flash Lib Initialization parameters.
 *
 * \return  None.
 */
void NOR_Init(const Nor_InitPrms_t *pNor_InitPrms);

#ifdef __cplusplus
}
#endif

#endif
/********************************* End of file ******************************/

