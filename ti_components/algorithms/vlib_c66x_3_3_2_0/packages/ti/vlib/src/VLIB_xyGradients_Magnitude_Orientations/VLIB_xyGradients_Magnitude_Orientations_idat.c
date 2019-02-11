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
#include "VLIB_xyGradients_Magnitude_Orientations_idat.h"

/* When SEQUENTIAL is selected as input type for the first vector, the test
 * framework produces the following input array, shown here for easy reference
 *
 * static uint8_t    staticRefInput[]=
 * {
 *     1,  2,  3,  4,  5,  6,  7, 8,
 *     9, 10, 11, 12, 13, 14, 15, 16,
 *    17, 18, 19, 20, 21, 22, 23, 24,
 *    25, 26, 27, 28, 29, 30, 31, 32
 * };
 */

/* The magnitude values returned are the sum of the absolute values of the
 * x and y difference gradients, for example:
 *   dx = 11-9 = 2
 *   dy = 18-2 = 16
 *   Mag = abs(2)+abs(16) = 18
 */
static uint32_t    staticRefOutMag[]=
{
    18, 18, 18, 18, 18, 18,
    18, 18, 18, 18, 18, 18
};

static uint32_t    staticRefOutOrien[]=
{
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4
};

static xyGradientsMagOrien_testParams_t    testParams[]=
{
    /********************************************
        {
           testPattern,
           *staticIn,
           *staticOutMag, *staticOutOrien,
           Width, Height, bins
        },
    *********************************************/
    {
        SEQUENTIAL,
        NULL,
        staticRefOutMag, staticRefOutOrien,
        8, 4, 9
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        10, 18, 9
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        16, 8, 9
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        32, 16, 9
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        64, 32 - 1, 9
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        128, 64, 12
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        320, 240, 9
    },
    {
        RANDOM,
        NULL,
        NULL, NULL,
        640, 480, 9
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void xyGradientsMagOrien_getTestParams(xyGradientsMagOrien_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(xyGradientsMagOrien_testParams_t);
}

/* ======================================================================== */
/*                       End of file                                        */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2014 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */

