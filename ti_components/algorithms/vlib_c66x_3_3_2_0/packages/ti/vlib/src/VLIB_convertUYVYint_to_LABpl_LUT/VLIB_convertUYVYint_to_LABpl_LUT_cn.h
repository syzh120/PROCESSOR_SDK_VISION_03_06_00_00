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

#ifndef VLIB_CONVERTUYVYINT_TO_LABPL_LUT_CN_H_
#define VLIB_CONVERTUYVYINT_TO_LABPL_LUT_CN_H_ 1

int32_t VLIB_convertUYVYint_to_LABpl_LUT_cn(const uint8_t *yc,         /* Interleaved luma/chroma          */
                                            uint32_t width, /* width (number of luma pixels)    */
                                            int32_t pitch,
                                            uint32_t height,
                                            int32_t d,
                                            uint16_t *LabExt, /* pointer to the Lab LUT  */
                                            uint16_t *L,
                                            uint16_t *a,
                                            uint16_t *b);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_convertUYVYint_to_LABpl_LUT_cn.h                     */
/* ======================================================================== */

