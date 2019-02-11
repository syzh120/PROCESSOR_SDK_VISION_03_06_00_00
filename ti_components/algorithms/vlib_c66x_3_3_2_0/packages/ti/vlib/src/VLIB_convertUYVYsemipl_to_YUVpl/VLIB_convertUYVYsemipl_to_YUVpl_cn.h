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

#ifndef VLIB_CONVERTUYVYSEMIPL_TO_YUVPL_CN_H_
#define VLIB_CONVERTUYVYSEMIPL_TO_YUVPL_CN_H_ 1

int32_t VLIB_convertUYVYsemipl_to_YUVpl_cn(const uint8_t *crcb,      /* Interleaved chroma  */
                                           uint32_t width, /* width (number of luma pixels)    */
                                           int32_t pitch, /* pitch (number of luma pixels)    */
                                           uint32_t height, /* height (number of luma pixels)   */
                                           uint8_t *restrict cr, /* Cr chroma plane (8-bit) */
                                           uint8_t *restrict cb /* Cb chroma plane (8-bit) */
                                           );

#endif

/* ======================================================================== */
/*  End of file: VLIB_convertUYVYsemipl_to_YUVpl_cn.h                       */
/* ======================================================================== */

