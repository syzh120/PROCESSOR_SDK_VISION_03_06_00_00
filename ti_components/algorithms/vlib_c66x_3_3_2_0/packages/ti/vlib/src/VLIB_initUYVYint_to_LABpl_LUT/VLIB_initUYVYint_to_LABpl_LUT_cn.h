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

#ifndef VLIB_INITUYVYINT_TO_LABPL_LUT_CN_H_
#define VLIB_INITUYVYINT_TO_LABPL_LUT_CN_H_ 1

int32_t VLIB_initUYVYint_to_LABpl_LUT_cn(const int32_t d,              /* Decimation factor (0 = none, 1/2/3 = by 2/4/8) */
                                         const int16_t coeff[5], /* YUV to sRGB Matrix coefficients  */
                                         const VLIB_F32 whitePoint[3], /* D65 = {0.950456, 1.0, 1.088754}; */
                                         uint16_t *Lab /* Interleaved Lab values
                                points to enough memory to hold
                                3 x 2 x (256/d + 1)^3 bytes
                                d      memory size [bytes]
                                0        101847558
                                1         12880134
                                2          1647750
                                3           215622               */
                                         );


#endif

/* ======================================================================== */
/*  End of file:  VLIB_initUYVYint_to_LABpl_LUT_cn.h                        */
/* ======================================================================== */

