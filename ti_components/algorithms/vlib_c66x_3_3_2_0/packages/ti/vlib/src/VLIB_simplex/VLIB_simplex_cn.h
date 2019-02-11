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

#ifndef VLIB_SIMPLEX_CN_H_
#define VLIB_SIMPLEX_CN_H_ 1

void    VLIB_simplex_cn
(
    int32_t (*func)(int16_t[], const void *), /* function handle */
    int16_t * restrict start,        /* start point */
    int16_t * restrict init_step,    /* step size for initial simplex */
    int32_t N,                     /* number of dimensions */
    int16_t N_INV,                   /* 1/N */
    int32_t MaxIteration,
    int32_t EPSILON,                   /* convergence threshold */
    int16_t * restrict v,            /* pointer to buffer */
    int32_t * restrict f,          /* pointer to buffer */
    int16_t * restrict vr,           /* pointer to buffer */
    int16_t * restrict ve,           /* pointer to buffer */
    int16_t * restrict vc,           /* pointer to buffer */
    int16_t * restrict vm,           /* pointer to buffer */
    void *addtlArgs,               /* arguments to func */
    int16_t * restrict minPoint,     /* stop point */
    int32_t * restrict minValue        /* minimum value */
);


#endif

/* ======================================================================== */
/*  End of file:  VLIB_simplex_cn.h                                         */
/* ======================================================================== */

