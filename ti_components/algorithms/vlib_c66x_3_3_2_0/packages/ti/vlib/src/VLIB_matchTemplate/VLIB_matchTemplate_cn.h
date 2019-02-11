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

#ifndef VLIB_MATCHTEMPLATE_CN_H_
#define VLIB_MATCHTEMPLATE_CN_H_ 1

#include "../common/VLIB_types.h"

int32_t    VLIB_matchTemplate_cn(uint8_t img[],           /* original image prepared outside this kernel*/
                                 int32_t imgWidth,        /* original image width  */
                                 int32_t imgHeight,       /* original image height */
                                 int32_t imgPitch,        /* original image pitch  */
                                 int16_t tempImg[],       /* template image prepared outside this kernel*/
                                 int32_t tempImgWidth,    /* template image width  */
                                 int32_t tempImgHeight,   /* template image height */
                                 int32_t tempImgPitch,    /* template image pitch  */
                                 VLIB_F32 scaledTempImgVar, /*template image variance*/
                                 uint8_t xDirJump,        /* x direction jump while search */
                                 uint8_t yDirJump,        /* y direction jump while search */
                                 int32_t method,          /* method used for template matching, currently only NCC is supported */
                                 int32_t outScorePitch,   /* output score pitch    */
                                 VLIB_F32  * outScore,    /* Output object list*/
                                 uint8_t   * scratch);

#endif
/* ======================================================================== */
/*  End of file:  VLIB_matchTemplate_cn.h                                   */
/* ======================================================================== */

