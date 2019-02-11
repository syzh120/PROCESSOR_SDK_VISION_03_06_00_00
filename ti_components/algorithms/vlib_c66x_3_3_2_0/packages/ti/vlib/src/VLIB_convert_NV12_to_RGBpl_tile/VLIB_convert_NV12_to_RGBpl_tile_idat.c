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
#include "VLIB_convert_NV12_to_RGBpl_tile_idat.h"

static int16_t    coeff[5] = { 0x2000, 0x2BDD, -0x0AC5, -0x1658, 0x3770 };

static VLIB_convert_NV12_to_RGBpl_tile_testParams_t    testParams[]=
{
    /********************************************
    {
      testPattern,
      *staticIn, *staticOutR, *staticOutG, *staticOutB, *coeff,
      width, pitch, height
    },
    *********************************************/
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
        128, 128, 56
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        68, 72, 68
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        640, 640, 480
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        16, 24, 2
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        64, 88, 42
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        128, 136, 56
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        320, 328, 240
    },
    {
        RANDOM,
        NULL, NULL, NULL, NULL, coeff,
        640, 648, 480
    }
};

/*
 *  Sends the test parameter structure and number of tests
 */
void VLIB_convert_NV12_to_RGBpl_tile_getTestParams(VLIB_convert_NV12_to_RGBpl_tile_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(VLIB_convert_NV12_to_RGBpl_tile_testParams_t);
}

/* ======================================================================== */
/*  End of file:  VLIB_convert_NV12_to_RGBpl_tile_idat.c                    */
/* ======================================================================== */

