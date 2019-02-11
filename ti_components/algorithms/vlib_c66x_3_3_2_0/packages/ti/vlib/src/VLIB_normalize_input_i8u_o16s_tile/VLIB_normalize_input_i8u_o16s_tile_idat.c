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
#include "VLIB_normalize_input_i8u_o16s_tile_idat.h"

#define NUM_IN_CH     (3)
#define BIAS_VALUE    (128)

static VLIB_normalize_input_i8u_o16s_tile_testParams_t    testParams[]=
{
    /***********************************
    testPattern,
    *staticInChannel,
    bias,
    *staticOutChannel,
    numInChannels,
    inCols, inRows, inPitch,
    outCols, outRows, outPitch
    ***********************************/
    {
        SEQUENTIAL,
        NULL,
        BIAS_VALUE,
        NULL,
        NUM_IN_CH,
        16, 16, 16,
        16, 16, 16
    },
    {
        SEQUENTIAL,
        NULL,
        BIAS_VALUE,
        NULL,
        NUM_IN_CH,
        32, 32, 32,
        32, 32, 32
    },
    {
        SEQUENTIAL,
        NULL,
        BIAS_VALUE,
        NULL,
        NUM_IN_CH,
        70, 70, 72,
        70, 70, 72
    },
    {
        SEQUENTIAL,
        NULL,
        BIAS_VALUE,
        NULL,
        NUM_IN_CH,
        16, 16, 32,
        16, 16, 24
    }
};

/*
*  Sends the test parameter structure and number of tests
*/
void VLIB_normalize_input_i8u_o16s_tile_getTestParams(VLIB_normalize_input_i8u_o16s_tile_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(VLIB_normalize_input_i8u_o16s_tile_testParams_t);
}

/* ======================================================================== */
/*  End of file:  VLIB_normalize_input_i8u_o16s_tile_idat.c                 */
/* ======================================================================== */

