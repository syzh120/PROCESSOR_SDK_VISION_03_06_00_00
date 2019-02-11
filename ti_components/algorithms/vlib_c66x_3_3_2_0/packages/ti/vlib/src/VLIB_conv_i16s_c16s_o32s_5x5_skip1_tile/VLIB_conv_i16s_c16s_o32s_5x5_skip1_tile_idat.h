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

#ifndef VLIB_CONV_I16S_C16S_O32S_5X5_SKIP1_TILE_IDAT_H
#define VLIB_CONV_I16S_C16S_O32S_5X5_SKIP1_TILE_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t  testPattern; /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    int16_t *staticInChannel;
    int16_t *staticWeights;
    int16_t *staticBias;
    int16_t *staticOutChannel;
    int16_t  numInChannels;
    int16_t  numOutChannels;
    int16_t  inCols;
    int16_t  inRows;
    int16_t  inPitch;
    int16_t  wgtCols;
    int16_t  wgtRows;
    int16_t  wgtPitch;
    int16_t  biasCols;
    int16_t  biasRows;
    int16_t  biasPitch;
    int16_t  outCols;
    int16_t  outRows;
    int16_t  outPitch;
} VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_testParams_t;

void VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_getTestParams(VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_CONV_I16S_C16S_O32S_5X5_SKIP1_TILE_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_idat.h            */
/* ======================================================================== */

