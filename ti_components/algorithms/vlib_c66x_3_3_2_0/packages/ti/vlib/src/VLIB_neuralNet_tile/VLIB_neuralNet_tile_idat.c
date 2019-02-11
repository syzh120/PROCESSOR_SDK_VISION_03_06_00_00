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
#include "../common/VLIB_memory.h"
#include "VLIB_neuralNet_tile_idat.h"

static int16_t    staticRefWeights[7 * 8]=
{
    1,    1,   1,   1,   1,   1,   1,   0,
    2,   -1,  -1,  -1,  -1,  -1,   2,   0,
    2,   -1,   2,   2,   2,  -1,   2,   0,
    2,   -1,   2,   8,   2,  -1,   2,   0,
    2,   -1,   2,   2,   2,  -1,   2,   0,
    2,   -1,  -1,  -1,  -1,  -1,   2,   0,
    1,    1,   1,   1,   1,   1,   1,   0
};

static VLIB_neuralNet_tile_testParams_t    testParams[]=
{
    /***********************************
      testPattern,
      *staticIn,
      staticWeights,
      *staticBias,
      *staticOut,
      inCols, inRows, inPitch, numCh
      wgtCols, wgtRows, wgtPitch, numCh
      biasCols, biasRows, biasPitch, numCh
      outCols, outRows, outPitch, numCh
    ***********************************/
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NULL,
        32, 1, 32, 32,
        32, 16, 32, 1,
        16, 1, 16, 1,
        16, 1, 16, 32
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NULL,
        64, 1, 64, 64,
        64, 16, 64, 1,
        16, 1, 16, 1,
        16, 1, 16, 64
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NULL,
        32, 1, 40, 32,
        32, 16, 72, 1,
        16, 1, 32, 1,
        16, 1, 16, 32
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NULL,
        64, 1, 72, 64,
        64, 32, 80, 1,
        32, 1, 32, 1,
        32, 1, 40, 64
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NULL,
        1152, 1, 1160, 1,
        1152, 92, 1168, 1,
        92, 1, 104, 1,
        92, 1, 112, 1
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void VLIB_neuralNet_tile_getTestParams(VLIB_neuralNet_tile_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(VLIB_neuralNet_tile_testParams_t);
}

/* ======================================================================== */
/*  End of file:  VLIB_neuralNet_tile_idat.c                                */
/* ======================================================================== */

