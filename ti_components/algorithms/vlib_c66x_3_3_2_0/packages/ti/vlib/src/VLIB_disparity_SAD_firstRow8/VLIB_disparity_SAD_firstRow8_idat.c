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
#include "../common/VLIB_memory.h"
#include "VLIB_disparity_SAD_firstRow8_idat.h"

static uint8_t    inpL[] =
{
    0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15
};

static uint8_t    inpRPos[] =
{
    0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15,
    1, 2, 3, 4, 5, 6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16,
    2, 3, 4, 5, 6, 7,  8,  9, 10, 11, 12, 13, 14, 15, 16, 17,
    3, 4, 5, 6, 7, 8,  9, 10, 11, 12, 13, 14, 15, 16, 17, 18,
    4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19
};

static uint8_t    inpRNeg[] =
{
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    1, 0, 1, 2, 3, 4, 5, 6, 7, 8,  9, 10, 11, 12, 13, 14,
    2, 1, 0, 1, 2, 3, 4, 5, 6, 7,  8,  9, 10, 11, 12, 13,
    3, 2, 1, 0, 1, 2, 3, 4, 5, 6,  7,  8,  9, 10, 11, 12,
    4, 3, 2, 1, 0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11
};

static uint8_t    inpRBoth[] =
{
    2, 1, 0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13,
    1, 0, 1, 2, 3, 4, 5, 6,  7,  8,  9, 10, 11, 12, 13, 14,
    0, 1, 2, 3, 4, 5, 6, 7,  8,  9, 10, 11, 12, 13, 14, 15,
    1, 2, 3, 4, 5, 6, 7, 8,  9, 10, 11, 12, 13, 14, 15, 16,
    2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17,
};

static int8_t    staticOutPos[] =
{
    1, 1, 1, 1, 1, 1,
    2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 3
};

static int8_t    staticOutNeg[] =
{
    -1, -1, -1, -1, -1, -1,
    -2, -2, -2, -2, -2, -2,
    -3, -3, -3, -3, -3, -3
};

static int8_t    staticOutBoth[] =
{
    -1, -1, -1, -1, -1, -1,
    0,  0,  0,  0,  0,  0,
    1,  1,  1,  1,  1,  1
};

static uint8_t    inpLRand[] =
{
    103, 198, 105, 115,  81, 255,  74, 236,  41, 205, 186, 171, 242, 251, 227,  70,
    124, 194,  84, 248,  27, 232, 231, 141, 118,  90,  46,  99,  51, 159, 201, 154,
    102,  50,  13, 183,  49,  88, 163,  90,  37,  93,   5,  23,  88, 233,  94, 212,
    171, 178, 205, 198, 155, 180,  84,  17,  14, 130, 116,  65,  33,  61, 220, 135,
    112, 233,  62, 161,  65, 225, 252, 103,  62,   1, 126, 151, 234, 220, 107, 150
};

static uint8_t    inpRRand[] =
{
    143,  56,  92,  42, 236, 176,  59, 251,  50, 175,  60,  84, 236,  24, 219,  92,
    2,  26, 254,  67, 251, 250, 170,  58, 251,  41, 209, 230,   5,  60, 124, 148,
    117, 216, 190,  97, 137, 249,  92, 187, 168, 153,  15, 149, 177, 235, 241, 179,
    5, 239, 247,   0, 233, 161,  58, 229, 202,  11, 203, 208,  72,  71, 100, 189,
    31,   35,  30, 168,  28, 123, 100, 197,  20, 115,  90, 197,  94,  75, 121,  99,
};

static int8_t    staticOutRand[] =
{
    0, 0, 0, 8, 8, 0,
    2, 1, 0, 0, 3, 0,
    5, 5, 0, 1, 6, 4,
};

static disparity_SAD_firstRow8_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticInLeft, *staticInRight, *staticOut,
           width, height, minDisp, maxDisp, windowSize
        },
    *********************************************/

    {
        STATIC,
        inpL, inpRPos, staticOutPos,
        16, 5,  0, 8, 3
    },
    {
        STATIC,
        inpL, inpRNeg, staticOutNeg,
        16, 5, -8, 0, 3
    },
    {
        STATIC,
        inpL, inpRBoth, staticOutBoth,
        16, 5, -4, 4, 3
    },
    {
        STATIC,
        inpLRand, inpRRand, staticOutRand,
        16, 5,  0, 8, 3
    },
    {
        CONSTANT,
        NULL, NULL, NULL,
        64, 8, 0, 8, 5
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        64, 12, 0, 20, 5
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        120, 12, 0, 85, 5
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        120, 24, 0, 85, 9
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        320, 24, 0, 127, 11
    },
    {
        RANDOM,
        NULL, NULL, NULL,
        320, 24, -64, 127, 11
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void disparity_SAD_firstRow8_getTestParams(disparity_SAD_firstRow8_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(disparity_SAD_firstRow8_testParams_t);
}

