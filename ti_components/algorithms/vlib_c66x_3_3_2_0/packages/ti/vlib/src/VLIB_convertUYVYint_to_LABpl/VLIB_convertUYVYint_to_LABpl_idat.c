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
 **|         Copyright (c) 2007-2013 Texas Instruments Incorporated           |**
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
#include "VLIB_convertUYVYint_to_LABpl_idat.h"

static uint8_t    staticRefIn[64] =
{
    151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6,
    31, 143, 178,   3, 135,  91,  54, 154, 193, 161,  20, 162, 137, 150, 128, 224,
    214, 113,   9,  28,  53, 211,  98, 217, 149, 233, 231, 127, 115, 203, 177,  42,
    62, 155,   3, 103, 127,  16, 135, 131, 211, 158,   9,   2, 106, 227, 249, 255
};

static VLIB_F32    staticRefOutL[32] =
{
    17.265034, 63.574043, 86.963959, 59.938698, 24.558899,
    31.405392, 4.765028, 4.765028, 58.058479, 7.330656, 45.775894, 68.106667,
    74.575233, 74.864967, 55.282509, 82.873566, 60.537140, 30.483486,
    87.028114, 89.085182, 73.892006, 55.931030, 74.744598, 17.155056,
    85.603165, 69.097565, 0.524044, 47.792004, 74.285027, 20.711773,
    70.190643, 76.634476
};

static VLIB_F32    staticRefOutA[32] =
{
    7.589161, 3.009796, -1.693904, 44.134914, -10.802895,
    -13.673991, 12.377151, 12.377151, 20.145357, 26.917166, -38.985950,
    -46.491325, -21.300167, -21.813095, 5.399912, 4.924804, 0.970393,
    21.399885, -52.812366, -52.864582, 59.851051, 82.322533, 36.903618,
    38.394405, -83.941193, -70.691193, 2.366193, 6.026894, -20.784527,
    25.984793, 50.326050, 39.896996
};

static VLIB_F32    staticRefOutB[32] =
{
    -26.081396, -22.099293, 84.643967, 68.164642, -15.977430,
    -16.349543, 7.369337, 7.369337, 64.340759, 11.588656, 12.075769,
    8.083177, -39.376877, -38.926254, -9.634387, -8.895719, -56.056023,
    -55.621086, 71.813759, 71.931549, -38.316608, -5.809820, 11.777973,
    25.310669, 79.130211, 68.226204, 0.833717, 0.334072, -39.828537,
    -52.491127, 0.810838, -5.225980
};

static int16_t     coeff[5] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 };
static VLIB_F32    whitePoint[3] = { 0.950456, 1.0, 1.088754 }; /* D65 */

static UYVYint_to_LABpl_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOutL, *staticOutA, *staticOutB, *coeff, *whitePoint
           width, pitch, height
        },
    *********************************************/
    {
        STATIC,
        staticRefIn, staticRefOutL, staticRefOutA, staticRefOutB, coeff, whitePoint,
        16, 16, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint,
        32, 32, 16
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint,
        64, 64, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint,
        128, 128, 55
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint,
        16, 20, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint,
        64, 84, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint,
        128, 136, 55
    },
#if defined (_TMS320C6600)
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint,
        320, 320, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint,
        320, 324, 240
    },
#if 0 // Removing due to large simulator test time
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint,
        640, 640, 480
    }
#endif
#endif
};

/*
 *  Sends the test parameter structure and number of tests
 */
void UYVYint_to_LABpl_getTestParams(UYVYint_to_LABpl_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(UYVYint_to_LABpl_testParams_t);
}

