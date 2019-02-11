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

#ifndef VLIB_INIT_UYVYINT_TO_LABPL_LUT_IDAT_H

#define VLIB_INIT_UYVYINT_TO_LABPL_LUT_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t   testPattern;  /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint16_t *staticOut;
    int16_t  *coeff;
    VLIB_F32 *whitePoint;
    int32_t   d;
} initUYVYint_to_LABpl_LUT_testParams_t;

void initUYVYint_to_LABpl_LUT_getTestParams(initUYVYint_to_LABpl_LUT_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_INIT_UYVYINT_TO_LABPL_LUT_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_initUYVYint_to_LABpl_LUT_idat.h                      */
/* ======================================================================== */

