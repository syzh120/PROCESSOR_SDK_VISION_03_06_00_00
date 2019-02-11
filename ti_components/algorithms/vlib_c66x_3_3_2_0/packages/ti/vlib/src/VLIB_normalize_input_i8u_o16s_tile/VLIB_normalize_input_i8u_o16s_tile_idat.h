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
**|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
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

#ifndef VLIB_NORMALIZE_INPUT_I8U_O16S_TILE_IDAT_H
#define VLIB_NORMALIZE_INPUT_I8U_O16S_TILE_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t  testPattern; /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    int16_t *staticInChannel;
    int16_t  bias;
    int16_t *staticOutChannel;
    int16_t  numInChannels;
    int16_t  inCols;
    int16_t  inRows;
    int16_t  inPitch;
    int16_t  outCols;
    int16_t  outRows;
    int16_t  outPitch;
} VLIB_normalize_input_i8u_o16s_tile_testParams_t;

void VLIB_normalize_input_i8u_o16s_tile_getTestParams(VLIB_normalize_input_i8u_o16s_tile_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_NORMALIZE_INPUT_I8U_O16S_TILE_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_normalize_input_i8u_o16s_tile_idat.h                 */
/* ======================================================================== */

