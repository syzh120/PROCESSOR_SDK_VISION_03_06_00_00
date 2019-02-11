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
**|         Copyright (c) 2007-2012 Texas Instruments Incorporated           |**
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

#ifndef VLIB_NONMAXSUPRESS_U32_CN_H_
#define VLIB_NONMAXSUPRESS_U32_CN_H_ 1

int VLIB_nonMaxSuppress_U32_cn(const unsigned int *restrict im,  /* input image */
                               int w, /* image width */
                               int h, /* image height */
                               int p, /* filter width */
                               unsigned int threshold, /* threshold for the maxima */
                               unsigned int *restrict buffer, /* buffer for internal use */
                               short *restrict pixIndex
                               /* output: list of coordinates of non-maxima locations, \
                                   [numPoints, 0, r1 c1 r2 c2 r3 c3 ... ] */
                               );


#endif

/* ======================================================================== */
/*  End of file:  VLIB_nonMaxSuppress_U32_cn.h                              */
/* ======================================================================== */

