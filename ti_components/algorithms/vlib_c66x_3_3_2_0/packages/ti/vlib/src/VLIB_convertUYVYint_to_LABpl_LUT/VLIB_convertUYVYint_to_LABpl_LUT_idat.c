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
#include "VLIB_convertUYVYint_to_LABpl_LUT_idat.h"

static uint8_t    staticRefIn[64] =
{
    151,  57, 116, 170,   9, 247, 208, 140, 150,  60,  88,  77,   4,   6, 162,   6,
    31, 143, 178,   3, 135,  91,  54, 154, 193, 161,  20, 162, 137, 150, 128, 224,
    214, 113,   9,  28,  53, 211,  98, 217, 149, 233, 231, 127, 115, 203, 177,  42,
    62, 155,   3, 103, 127,  16, 135, 131, 211, 158,   9,   2, 106, 227, 249, 255
};

static int16_t     coeff[5] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 };
static VLIB_F32    whitePoint[3] = { 0.950456, 1.0, 1.088754 }; /* D65 */

static UYVYint_to_LABpl_LUT_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, *staticOutL, *staticOutA, *staticOutB, *coeff, *whitePoint, d,
           width, pitch, height
        },
    *********************************************/
    /* NOTE: d values < 3 take too long to setup on simulator for regression testing,
     * which is why they have been removed from here */
    {
        STATIC,
        staticRefIn, NULL, NULL, NULL, coeff, whitePoint, 4,
        16, 16, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint, 3,
        32, 32, 16
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint, 4,
        64, 64, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint, 4,
        128, 128, 55
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint, 4,
        320, 320, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint, 4,
        640, 640, 480
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint, 4,
        16, 22, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint, 4,
        62, 82, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint, 4,
        128, 136, 55
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint, 4,
        320, 324, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff, whitePoint, 4,
        640, 644, 480
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void UYVYint_to_LABpl_LUT_getTestParams(UYVYint_to_LABpl_LUT_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(UYVYint_to_LABpl_LUT_testParams_t);
}

