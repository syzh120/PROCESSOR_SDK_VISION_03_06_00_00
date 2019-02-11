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
#include "VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_idat.h"

#define KERNEL_WIDTH  (5)
#define KERNEL_HEIGHT (5)
#define KERNEL_PITCH  (8)
#define NUM_IN_CH     (3)
#define NUM_OUT_CH    (2)

static int16_t    staticRefWeights[KERNEL_PITCH * KERNEL_HEIGHT * NUM_IN_CH * NUM_OUT_CH] =
{
    -1, -1, -1, -1, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1,  2,  8,  2, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1, -1, -1, -1, -1, 0, 0, 0,

    -1, -1, -1, -1, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1,  2,  8,  2, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1, -1, -1, -1, -1, 0, 0, 0,

    -1, -1, -1, -1, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1,  2,  8,  2, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1, -1, -1, -1, -1, 0, 0, 0,

    -1, -1, -1, -1, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1,  2,  8,  2, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1, -1, -1, -1, -1, 0, 0, 0,

    -1, -1, -1, -1, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1,  2,  8,  2, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1, -1, -1, -1, -1, 0, 0, 0,

    -1, -1, -1, -1, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1,  2,  8,  2, -1, 0, 0, 0,
    -1,  2,  2,  2, -1, 0, 0, 0,
    -1, -1, -1, -1, -1, 0, 0, 0,
};

static int16_t    staticRefBias[NUM_OUT_CH] =
{
    10, 20
};

static VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_testParams_t    testParams[]=
{
    /***********************************
    testPattern,
    *staticInChannel,
    staticRefWeights,
    *staticBias,
    *staticOutChannel,
    numInChannels,
    numOutChannels,
    inCols, inRows, inPitch,
    wgtCols, wgtRows, wgtPitch,
    biasCols, biasRows, biasPitch,
    outCols, outRows, outPitch
    ***********************************/
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights,
        staticRefBias,
        NULL,
        NUM_IN_CH,
        NUM_OUT_CH,
        16, 16, 16,
        KERNEL_WIDTH, KERNEL_HEIGHT, KERNEL_PITCH,
        NUM_OUT_CH, 1,  NUM_OUT_CH,
        12, 12, 16
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights,
        staticRefBias,
        NULL,
        NUM_IN_CH,
        NUM_OUT_CH,
        20, 20, 24,
        KERNEL_WIDTH, KERNEL_HEIGHT, KERNEL_PITCH,
        NUM_OUT_CH, 1,  NUM_OUT_CH,
        16, 16, 16
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights,
        staticRefBias,
        NULL,
        NUM_IN_CH,
        NUM_OUT_CH,
        36, 36, 40,
        KERNEL_WIDTH, KERNEL_HEIGHT, KERNEL_PITCH,
        NUM_OUT_CH, 1,  NUM_OUT_CH,
        32, 32, 32
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights,
        staticRefBias,
        NULL,
        NUM_IN_CH,
        NUM_OUT_CH,
        68, 68, 72,
        KERNEL_WIDTH, KERNEL_HEIGHT, KERNEL_PITCH,
        NUM_OUT_CH, 1,  NUM_OUT_CH,
        64, 64, 64
    },
    {
        SEQUENTIAL,
        NULL,
        staticRefWeights,
        staticRefBias,
        NULL,
        NUM_IN_CH,
        NUM_OUT_CH,
        132, 132, 136,
        KERNEL_WIDTH, KERNEL_HEIGHT, KERNEL_PITCH,
        NUM_OUT_CH, 1,  NUM_OUT_CH,
        128, 128, 128
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_getTestParams(VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_testParams_t);
}

/* ======================================================================== */
/*  End of file:  VLIB_conv_i16s_c16s_o32s_5x5_skip1_tile_idat.c                                  */
/* ======================================================================== */

