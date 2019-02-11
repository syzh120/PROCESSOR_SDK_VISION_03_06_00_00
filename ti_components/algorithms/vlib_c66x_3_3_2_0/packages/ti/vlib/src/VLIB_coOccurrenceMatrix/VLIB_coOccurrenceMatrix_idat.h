/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 2007-2014 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission to use, copy, modify, or distribute this software,            |**
**| whether in part or in whole, for any purpose is forbidden without        |**
**| a signed licensing agreement and NDA from Texas Instruments              |**
**| Incorporated (TI).                                                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/

#ifndef VLIB_CO_OCCURRENCEMATRIX_IDAT_H

#define VLIB_CO_OCCURRENCEMATRIX_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t   testPattern;
    uint8_t  *staticIn;
    uint16_t *staticOut;
    uint16_t  imageWidth;
    uint16_t  imageHeight;
    uint16_t  imagePitch;
    uint8_t   loPixelVal;
    uint8_t   hiPixelVal;
    uint16_t  numLevels;
    uint8_t   numOffsets;
    int8_t    rowOffsets[4];
    int8_t    colOffsets[4];
    uint8_t   scratchFlow;
} coOccurrence_testParams_t;

void coOccurrence_getTestParams(coOccurrence_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_CO_OCCURRENCEMATRIX_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_coOccurrenceMatrix_idat.h                            */
/* ======================================================================== */

