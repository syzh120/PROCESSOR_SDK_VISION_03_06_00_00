/*
 * TI Booting and Flashing Utilities
 *
 * Header for UTIL module.
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

#ifndef UTIL_H_
#define UTIL_H_

#include <ti/boot/sbl_auto/norflash/nor_flash.h>
#include <ti/boot/sbl_auto/norflash/src/debug.h>

/* Prevent C++ name mangling */
#ifdef __cplusplus
extern "C" {
#endif

/***********************************************************
 * Global Macro Declarations                                *
 ***********************************************************/

#define ENDIAN_SWAP(a) ((((a) & 0xFFU) << 24) |    \
                        (((a) & 0xFF0000U) >> 8) | \
                        (((a) & 0xFF00U) << 8) |   \
                        (((a) & 0xFF000000U) >> 24))

/***********************************************************
 * Global Typedef declarations                              *
 ***********************************************************/

/***********************************************************
 * Global Function Declarations                             *
 ***********************************************************/

void *UTIL_allocMem(UInt32 size);
void *UTIL_callocMem(UInt32 size);
void *UTIL_getCurrMemPtr(void);
void UTIL_setCurrMemPtr(const void *value);
void UTIL_waitLoop(UInt32 loopcnt);
void UTIL_waitLoopAccurate(UInt32 loopcnt);
UInt32 UTIL_calcCRC32(UInt32 *lutCRC, UInt8 *data, UInt32 size, UInt32 currCRC);
void UTIL_buildCRC32Table(UInt32 *lutCRC, UInt32 poly);
UInt16 UTIL_calcCRC16(UInt16 *lutCRC, UInt8 *data, UInt32 size, UInt16 currCRC);
void UTIL_buildCRC16Table(UInt16 *lutCRC, UInt16 poly);

/***********************************************************
 * End file                                                 *
 ***********************************************************/

#ifdef __cplusplus
}
#endif

#endif /* UTIL_H_ */

/* --------------------------------------------------------------------------
 * HISTORY
 *    v1.00  -  DJA  -  07-Nov-2007
 *    Initial release
 * -----------------------------------------------------------------------------
 * */

