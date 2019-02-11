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

#ifndef VLIB_CONVERTUYVYINT_TO_LABPL_CN_H_
#define VLIB_CONVERTUYVYINT_TO_LABPL_CN_H_ 1

int32_t    VLIB_convertUYVYint_to_LABpl_cn
(
    const uint8_t * yc,       /* Interleaved luma/chroma          */
    uint32_t width,           /* width (number of luma pixels)    */
    int32_t pitch,
    uint32_t height,
    const int16_t coeff[5],  /* YUV to sRGB Matrix coefficients  */
    VLIB_F32 whitePoint[3],   /* D65 = {0.950456, 1.0, 1.088754}; */
    VLIB_F32  * restrict L,    /* pointer to L plane   */
    VLIB_F32  * restrict a,    /* pointer to A plane   */
    VLIB_F32  * restrict b     /* pointer to B plane   */
);


#endif

/* ======================================================================== */
/*  End of file:  VLIB_convertUYVYint_to_LABpl_cn.h                         */
/* ======================================================================== */

