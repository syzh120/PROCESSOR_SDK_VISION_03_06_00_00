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

#ifndef  _VLIB_CCL_IDAT_H_

#define  _VLIB_CCL_IDAT_H_

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t  testPattern;     /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint8_t *staticIn;
    uint8_t *staticOut;        /* [out] expected reference map */
    VLIB_CC *staticOutStats;    /* [out] expected reference stats */
    int32_t  numCCs;           /* [out] expected number of CCs */
    uint16_t width;
    uint16_t height;
    int32_t  minBlobArea;
    int32_t  connected8Flag;
} ccl_testParams_t;

void ccl_getTestParams(ccl_testParams_t * *params, int32_t *numTests);

#endif /* define _VLIB_CCL_IDAT_H_ */

/* ======================================================================== */
/*  End of file:  VLIB_Connected_Components_Labeling_idat.h                 */
/* ======================================================================== */

