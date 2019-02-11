/*
 *  Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/
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
 *  \file   qspi.h
 *
 *  \brief  This file contains the Flash driver using QSPI hal API's.
 *
 *
 */
#ifndef QSPI_FLASH_H_
#define QSPI_FLASH_H_

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C"
{
#endif
/* ========================================================================== */
/*                             Include Files                                  */
/* ========================================================================== */
#include "stdint.h"
#include <ti/csl/csl_edma.h>
#include <ti/csl/csl_qspi.h>

/* ========================================================================== */
/*                                 Macros                                     */
/* ========================================================================== */
/* ========================================================================== */
/*                         Structures                                         */
/* ========================================================================== */
typedef void (*QSPI_flashInitFunPtr)(qspi_DeviceType_e DeviceType);

/*____________________________ Exported Definitions __________________________*/
/* Defines for all possible configuration IDs. */
#define QSPI_CONFIGID_CLOCKSPEED  (0)
#define QSPI_CONFIGID_READCMD     (1)

/*______________________________ Exported Types ______________________________*/

/* QSPI CR WLEN : 128 bits is not supported for tda3xx platform*/
typedef enum {
    QSPI_CR_WLEN_1_BIT    = 0x0,  /* 1 bit   */
    QSPI_CR_WLEN_8_BITS   = 0x7,  /* 8 bits  */
    QSPI_CR_WLEN_16_BITS  = 0xF,  /* 16 bits */
    QSPI_CR_WLEN_24_BITS  = 0x17, /* 24 bits */
    QSPI_CR_WLEN_32_BITS  = 0x1F, /* 32 bits */
    QSPI_CR_WLEN_128_BITS = 0x7F  /* 128 bits*/
} qspi_CR_WLEN_e;

/* QSPI CR FLEN  */
typedef enum {
    QSPI_CR_FLEN_1_WORD = 0x0,  /* 1 word  */
    QSPI_CR_FLEN_2_WORDS,       /* 2 words */
    QSPI_CR_FLEN_3_WORDS,       /* 3 words */
    QSPI_CR_FLEN_4_WORDS,       /* 4 words */
    QSPI_CR_FLEN_5_WORDS,       /* 5 words */
    QSPI_CR_FLEN_6_WORDS,       /* 6 words */
    QSPI_CR_FLEN_7_WORDS,       /* 7 words */
    QSPI_CR_FLEN_8_WORDS        /* 8 words */
} qspi_CR_FLEN_e;

/* Configuration descriptor type. */
typedef struct
{
    uint32_t ConfigId;
    uint32_t Value;
} QSPI_ConfigDesc_t;

typedef struct
{
    uint32_t numCmdBits;
    uint32_t cmd;
    uint32_t numCmdDummyBits;
    uint32_t numAddrBits;
    uint32_t addr;
    uint32_t numAddrDummyBits;
    uint32_t dataType;
    uint32_t numPerDataWordbits;
    uint32_t numDataWords;
} QSPI_FlashCmd_t;

typedef struct
{
    qspi_DeviceType_e    flashType;
    uint32_t             numDatalines;
    uint32_t             qspiMode;
    uint32_t             qspiCs;
    uint32_t             qspiDataDelay;
    qspi_ClockFreq_e     qspifrequency;
    QSPI_FlashCmd_t      idCmd;
    QSPI_FlashCmd_t      readCmd;
    QSPI_FlashCmd_t      writeCmd;
    QSPI_FlashCmd_t      sectorEraseCmd;
    QSPI_FlashCmd_t      subSectorEraseCmd;
    QSPI_FlashCmd_t      fullEraseCmd;
    QSPI_FlashCmd_t      flashStatusCmd;
    QSPI_FlashCmd_t      writeEnableCmd;
    QSPI_flashInitFunPtr qspiFlashInitFxn;
} QSPI_FlashDevInfo_t;
#define QSPIFLASH_BLOCKSIZE (64U * 1024U)
#define QSPIFLASH_SUBSECTORSIZE (4U * 1024U)

/* ========================================================================== */
/*                          Function Declarations                             */
/* ========================================================================== */
/**
 * \brief This function configures memory mapped address for different
 *        chip select in control module.
 *
 * \param     MMPT_S    Memory map switch value
 * \param     chipSelect    External Chip Select value from enum
 *                          qspi_ChipSelect_e
 *
 * \return    None
 */
void QSPIConfMAddrSpace(uint8_t MMPT_S,qspi_ChipSelect_e chipSelect);

void QSPISelClockFrequency(qspi_ClockFreq_e in_ClockSettings);

int32_t QSPI_executeCmd(QSPI_FlashCmd_t flashCmd, uint32_t *data);

/**
 * \brief     Initializes the QSPI Device.
 *
 * \param     ipDeviceDesc IO Device Descriptor
 *
 * \return    TRUE if the QSPI initialized successfully
 *            Otherwise   FAIL
 *
**/
uint32_t QSPI_Initialize(qspi_DeviceType_e DeviceType);

/**
 * \brief        Reads one or several sectors from the QSPI Memory described
 *               in the Device Descriptor.
 *
 * \param       ipDeviceDesc Device Descriptor
 * \paran       ipReadDesc Indicate where from and how many sectors to read
 *
 * \return      TRUE if the QSPI Device Sector(s) could be read
 *
 **/
uint32_t QSPI_ReadSectors(void       *dstAddr,
                          const void *srcOffsetAddr,
                          uint32_t    length);

uint32_t QSPI_WriteSectors(uint32_t dstOffsetAddr, uint32_t srcAddr,
                           uint32_t length);

uint32_t QSPI_WriteSectorsNonBlocking(uint32_t dstOffsetAddr, uint32_t srcAddr,
                                      uint32_t length);

void QSPI_WriteCfgMode(uint32_t dstOffsetAddr, uint32_t srcAddr,
                       uint32_t length);

void QSPI_WriteCfgModeNonBlocking(uint32_t dstOffsetAddr, uint32_t srcAddr,
                                  uint32_t length);

uint32_t QSPI_FlashStatus(void);

void QSPI_WriteEnable(void);

void QSPI_QuadEnable(void);

void QSPI_QuadEnableNonBlocking(void);

void QSPI_FlashSubSectorErase(uint32_t offsetAddr);

void QSPI_FlashSubSectorEraseNonBlocking(uint32_t offsetAddr);

void QSPI_FlashBlockErase(uint32_t blkNo);

void QSPI_FlashBlockEraseNonBlocking(uint32_t blkNo);

#ifdef __cplusplus /* If this is a C++ compiler, end C linkage */
}
#endif

#endif /* QSPI_FLASH_H_ */
/********************************* End of file ******************************/

