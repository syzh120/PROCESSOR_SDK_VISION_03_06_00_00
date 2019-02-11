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
#include "VLIB_convertUYVYint_to_RGBpl_idat.h"

static uint8_t    staticRefIn[64] =
{
    151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6,
    31, 143, 178,   3, 135,  91,  54, 154, 193, 161,  20, 162, 137, 150, 128, 224,
    214, 113,   9,  28,  53, 211,  98, 217, 149, 233, 231, 127, 115, 203, 177,  42,
    62, 155,   3, 103, 127,  16, 135, 131, 211, 158,   9,   2, 106, 227, 249, 255
};

static uint8_t    staticRefOutR[32] =
{
    24, 137, 255, 233, 0, 6, 36, 36, 195, 55, 0, 36, 0, 0, 134, 208,
    0, 0, 153, 159, 255, 252, 254, 93, 0, 0, 9, 124, 0, 0, 255, 255
};

static uint8_t    staticRefOutG[32] =
{
    41, 154, 215, 108, 64, 81, 7, 7, 124, 0, 124, 187, 198, 199, 130, 204,
    151, 66, 241, 247, 138, 32, 157, 0, 248, 196, 0, 110, 197, 41, 133, 161
};

static uint8_t    staticRefOutB[32] =
{
    80, 193, 24, 0, 82, 99, 0, 0, 0, 0, 87, 150, 255, 255, 149, 223, 245,
    160, 65, 71, 253, 147, 164, 3, 24, 0, 0, 113, 255, 129, 172, 200
};

static int16_t    coeff[5] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 };


static UYVYint_to_RGBpl_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOutR, *staticOutG, *staticOutB, *coeff,
           width, pitch, height
        },
    *********************************************/
    {
        STATIC,
        staticRefIn, staticRefOutR, staticRefOutG, staticRefOutB, coeff,
        16, 16, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        32, 32, 16
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        64, 64, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        128, 128, 55
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        320, 320, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        640, 640, 480
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        16, 20, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        64, 84, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        128, 136, 55
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        320, 324, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        640, 644, 480
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void UYVYint_to_RGBpl_getTestParams(UYVYint_to_RGBpl_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(UYVYint_to_RGBpl_testParams_t);
}

