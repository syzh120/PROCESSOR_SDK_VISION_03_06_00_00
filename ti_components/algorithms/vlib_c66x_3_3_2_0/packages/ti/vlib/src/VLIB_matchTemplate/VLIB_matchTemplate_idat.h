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
**|         Copyright (c) 2015 Texas Instruments Incorporated                |**
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

#ifndef VLIB_MATCH_TEMPLATE_IDAT_H

#define VLIB_MATCH_TEMPLATE_IDAT_H

#include "../common/VLIB_test.h"

typedef struct {
    uint8_t   testPattern;                          /* 0: constant, 1: sequential, 2: random, 3: static array, 4: file, etc */
    uint8_t  *orgImg;                               /* original image prepared outside this kernel*/
    int32_t   orgImgWidth;                          /* original image width  */
    int32_t   orgImgHeight;                         /* original image height */
    int32_t   orgImgPitch;                          /* original image pitch  */
    uint8_t  *tempImg;                              /* template image prepared outside this kernel*/
    int32_t   tempImgWidth;                         /* template image width  */
    int32_t   tempImgHeight;                        /* template image height */
    int32_t   tempImgPitch;                         /* template image pitch  */
    uint8_t   xDirJump;                             /* x-direction jump */
    uint8_t   yDirJump;                             /* y-direction jump */
    int32_t   outScorePitch;                        /* output score pitch    */
    int32_t   method;                               /* method used for finding template */
    VLIB_F32 *outScore;                             /* Output score buffer*/
    char     *desc;
} matchTemplate_testParams_t;

void matchTemplate_getTestParams(matchTemplate_testParams_t * *params, int32_t *numTests);

#endif /* define VLIB_MATCH_TEMPLATE_IDAT_H */

/* ======================================================================== */
/*  End of file:  VLIB_matchTemplate_idat.h                                 */
/* ======================================================================== */

