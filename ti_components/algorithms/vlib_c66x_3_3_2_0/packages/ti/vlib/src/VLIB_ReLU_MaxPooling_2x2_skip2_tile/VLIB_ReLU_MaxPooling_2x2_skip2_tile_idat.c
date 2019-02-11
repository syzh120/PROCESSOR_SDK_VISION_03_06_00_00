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
#include "VLIB_ReLU_MaxPooling_2x2_skip2_tile_idat.h"

#define NUM_OUT_CH    (16)

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

static VLIB_ReLU_MaxPooling_2x2_skip2_tile_testParams_t    testParams[]=
{
    /***********************************
    testPattern,
    *staticInChannel,
    staticRefWeights,
    *staticOutChannel,
    numOutChannels,
    inCols, inRows, inPitch,
    outCols, outRows, outPitch
    ***********************************/
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NUM_OUT_CH,
        16, 16, 16,
        8, 8, 8
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NUM_OUT_CH,
        32, 32, 32,
        16, 16, 16
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NUM_OUT_CH,
        64, 64, 64,
        32, 32, 32
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NUM_OUT_CH,
        12, 12, 16,
        6, 6, 8
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NUM_OUT_CH,
        32, 32, 40,
        16, 16, 32
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights, NULL,
        NUM_OUT_CH,
        64, 64, 72,
        32, 32, 40
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void VLIB_ReLU_MaxPooling_2x2_skip2_tile_getTestParams(VLIB_ReLU_MaxPooling_2x2_skip2_tile_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(VLIB_ReLU_MaxPooling_2x2_skip2_tile_testParams_t);
}

/* ======================================================================== */
/*  End of file:  VLIB_ReLU_MaxPooling_2x2_skip2_tile_idat.c                                  */
/* ======================================================================== */

