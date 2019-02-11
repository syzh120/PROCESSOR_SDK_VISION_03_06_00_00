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
#include "VLIB_nonMaxSuppress_U16_idat.h"

/* Test Vector */
static uint16_t    IMAGE[16 * 16]={ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                    1, 9, 9, 8, 7, 5, 5, 1, 1, 9, 9, 8, 7, 5, 5, 1,
                                    2, 8, 7, 9, 4, 8, 3, 1, 2, 8, 7, 9, 4, 8, 3, 1,
                                    1, 9, 5, 9, 2, 1, 7, 1, 1, 9, 5, 9, 2, 1, 7, 1,
                                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                    1, 9, 9, 8, 7, 5, 5, 1, 1, 9, 9, 8, 7, 5, 5, 1,
                                    2, 8, 7, 9, 4, 8, 3, 1, 2, 8, 7, 9, 4, 8, 3, 1,
                                    1, 9, 5, 9, 2, 1, 7, 1, 1, 9, 5, 9, 2, 1, 7, 1,
                                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                    1, 9, 9, 8, 7, 5, 5, 1, 1, 9, 9, 8, 7, 5, 5, 1,
                                    2, 8, 7, 9, 4, 8, 3, 1, 2, 8, 7, 9, 4, 8, 3, 1,
                                    1, 9, 5, 9, 2, 1, 7, 1, 1, 9, 5, 9, 2, 1, 7, 1,
                                    1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
                                    1, 9, 9, 8, 7, 5, 5, 1, 1, 9, 9, 8, 7, 5, 5, 1,
                                    2, 8, 7, 9, 4, 8, 3, 1, 2, 8, 7, 9, 4, 8, 3, 1,
                                    1, 9, 5, 9, 2, 1, 7, 1, 1, 9, 5, 9, 2, 1, 7, 1 };

/* Output buffer */
static int16_t    Pixindex7x7[] = { 17, 0, 7, 3, 6, 3, 3, 3, 11, 3, 10, 3, 9, 9, 7, 9,
                                    5, 9, 3, 9, 11, 9, 9, 10, 5, 10, 7, 11, 6, 11,
                                    3, 11, 11, 11, 10, 11 };

static int16_t    Pixindex5x5[] = { 24, 0, 5, 2, 9, 2, 13, 2, 6, 3, 3, 3, 2, 3, 11, 3, 10, 3,
                                    7, 3, 5, 9, 3, 9, 11, 9, 9, 9, 7, 9, 13, 9, 5, 10, 9, 10,
                                    13, 10, 6, 11, 3, 11, 2, 11, 11, 11, 10, 11,
                                    7, 11 };

static int16_t    Pixindex3x3[] = { 36, 0, 3, 1, 1, 1, 5, 1, 9, 1, 7, 1, 11, 1, 13, 1, 1, 2, 5, 2,
                                    9, 2, 13, 2, 3, 3, 2, 3, 6, 3, 7, 3, 11, 3, 10, 3, 14, 3, 3, 9,
                                    1, 9, 5, 9, 9, 9, 7, 9, 11, 9, 13, 9, 1, 10, 5, 10, 9, 10, 13, 10,
                                    3, 11, 2, 11, 6, 11, 7, 11, 11, 11, 10, 11, 14, 11 };

static uint16_t    IMAGE_1[16 * 16]={ 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8,
                                      8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7,
                                      7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6,
                                      6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5,
                                      5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4,
                                      4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2, 3,
                                      3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 2,
                                      2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1,
                                      1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2,
                                      2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3,
                                      3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4,
                                      4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5,
                                      5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6,
                                      6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7,
                                      7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8,
                                      8, 7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

/* Output buffer */
static int16_t    Pixindex7x7_1[] = { 10, 0, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,
                                      10, 10, 11, 11, 12, 12 };

static int16_t    Pixindex5x5_1[] = { 12, 0, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,
                                      10, 10, 11, 11, 12, 12, 13, 13 };

static int16_t    Pixindex3x3_1[] = { 14, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9,
                                      10, 10, 11, 11, 12, 12, 13, 13, 14, 14 };

static nonMaxSuppressU16_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn, staticOut,
           w, h,
           filterWidth, threshold
        },
    *********************************************/
    /* 7x7 */
    {
        STATIC,
        IMAGE, Pixindex7x7,
        16, 16,
        7, 8
    },
    {
        STATIC,
        IMAGE_1, Pixindex7x7_1,
        16, 16,
        7, 8
    },
    {
        RANDOM,
        NULL, NULL,
        20, 18,
        7, 80
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48,
        7, 80
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48,
        7, 12000
    },
    {
        RANDOM,
        NULL, NULL,
        160, 120,
        7, 80
    },
    {
        RANDOM,
        NULL, NULL,
        320, 240,
        7, 80
    },

    /* 5x5 */
    {
        STATIC,
        IMAGE, Pixindex5x5,
        16, 16,
        5, 8
    },
    {
        STATIC,
        IMAGE_1, Pixindex5x5_1,
        16, 16,
        5, 8
    },
    {
        RANDOM,
        NULL, NULL,
        20, 18,
        5, 80
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48,
        5, 80
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48,
        5, 12000
    },
    {
        RANDOM,
        NULL, NULL,
        160, 120,
        5, 80
    },
    {
        RANDOM,
        NULL, NULL,
        320, 240,
        5, 80
    },

    /* 3x3 */
    {
        STATIC,
        IMAGE, Pixindex3x3,
        16, 16,
        3, 8
    },
    {
        STATIC,
        IMAGE_1, Pixindex3x3_1,
        16, 16,
        3, 8
    },
    {
        RANDOM,
        NULL, NULL,
        20, 18,
        3, 80
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48,
        3, 80
    },
    {
        RANDOM,
        NULL, NULL,
        64, 48,
        3, 12000
    },
    {
        RANDOM,
        NULL, NULL,
        160, 120,
        3, 80
    },
    {
        RANDOM,
        NULL, NULL,
        320, 240,
        3, 80
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void nonMaxSuppressU16_getTestParams(nonMaxSuppressU16_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(nonMaxSuppressU16_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

