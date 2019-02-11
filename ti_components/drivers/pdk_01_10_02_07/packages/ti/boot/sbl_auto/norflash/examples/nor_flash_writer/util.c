/*
 * TI Booting and Flashing Utilities
 *
 * Utility functions for flashing applications.
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

#include <stdint.h>
#include <stddef.h>
#include <ti/csl/tistdtypes.h>
#include <util.h>
#include <device.h>

/************************************************************
 * Explicit External Declarations                            *
 ************************************************************/

/************************************************************
 * Local Macro Declarations                                  *
 ************************************************************/

/************************************************************
 * Local Typedef Declarations                                *
 ************************************************************/

/************************************************************
 * Local Function Declarations                               *
 ************************************************************/
static inline void UTIL_noOperationASM(void);

/************************************************************
 * Local Variable Definitions                                *
 ************************************************************/

/************************************************************
 * Global Variable Definitions                               *
 ************************************************************/

/* Global memory allocation pointer */
static volatile UInt32 currMemPtr;

/************************************************************
 * Static Function Definitions                              *
 ************************************************************/

static inline void UTIL_noOperationASM(void)
{
    asm (" NOP");
}

/************************************************************
 * Global Function Definitions                               *
 ************************************************************/

/* DDR Memory allocation routines (for storing large data) */
void *UTIL_getCurrMemPtr(void)
{
    return ((void *) currMemPtr);
}

/* Setup for an adhoc heap */
void UTIL_setCurrMemPtr(const void *value)
{
    currMemPtr = (UInt32) value;
}

/* Allocate memory from the ad-hoc heap */
void *UTIL_allocMem(UInt32 size)
{
    void  *cPtr;
    UInt32 size_temp;
    UInt32 tmpMemPtr;

    /* Ensure word boundaries */
    size_temp = ((size + 4U) >> 2) << 2;

    if ((currMemPtr + size_temp) > (DEVICE_DDR2_RAM_END))
    {
        cPtr = NULL;
    }
    else
    {
        tmpMemPtr   = (DEVICE_DDR2_START_ADDR + currMemPtr);
        cPtr        = (void *) tmpMemPtr;
        currMemPtr += size_temp;
    }
    return cPtr;
}

/* Allocate memory from the ad-hoc heap */
void *UTIL_callocMem(UInt32 size)
{
    void  *ptr;
    UInt8 *cPtr;
    UInt32 i;

    /* Alloc the memory */
    ptr = UTIL_allocMem(size);
    if (ptr != NULL)
    {
        /* Clear the memory */
        cPtr = (UInt8 *) ptr;
        for (i = 0; i < size; i++)
        {
            cPtr[i] = 0x00;
        }
    }
    return ptr;
}

/* Simple wait loop - comes in handy. */
void UTIL_waitLoop(UInt32 loopcnt)
{
    UInt32 i;
    for (i = 0; i < loopcnt; i++)
    {
        UTIL_noOperationASM();
    }
}

/* Accurate n = ((t us * f MHz) - 5) / 1.65 */
void UTIL_waitLoopAccurate(UInt32 loopcnt)
{
#if defined (_TMS320C6X)
    asm ("      STW     B0, *+B15[2]    ");
    asm ("      SUB     A4, 24, A4      ");        /* Total cycles taken by this
                                                    * *function, with n = 0,
                                                    * *including clocks taken to
                                                    *jump to this function  */
    asm ("      CMPGT   A4, 0, B0       ");
    asm ("loop:                         ");
    asm (" [B0] B       loop            ");
    asm (" [B0] SUB     A4, 6, A4       ");        /* Cycles taken by loop */
    asm ("      CMPGT   A4, 0, B0       ");
    asm ("      NOP     3               ");
    asm ("      LDW     *+B15[2], B0    ");
#elif defined (_TMS320C5XX) || defined (__TMS320C55X__)
    UTIL_waitLoop(loopcnt);
#elif defined (_TMS320C28X)
    UTIL_waitLoop(loopcnt);
#elif (defined (__TMS470__) || defined (__GNUC__))
    UTIL_waitLoop(loopcnt);
#endif
}

/***********************************************************
 * End file                                                 *
 ***********************************************************/

/* --------------------------------------------------------------------------
 *  HISTORY
 *      v1.00  -  DJA  -  16-Aug-2007
 *         Initial release
 * -----------------------------------------------------------------------------
 * */

