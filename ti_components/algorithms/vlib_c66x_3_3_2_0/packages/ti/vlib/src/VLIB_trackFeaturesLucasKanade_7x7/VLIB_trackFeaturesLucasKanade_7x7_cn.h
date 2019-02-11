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

#ifndef VLIB_TRACKFEATURESLUCASKANADE_CN_H_
#define VLIB_TRACKFEATURESLUCASKANADE_CN_H_ 1

int32_t VLIB_trackFeaturesLucasKanade_7x7_cn(const uint8_t *im1,
                                             const uint8_t *im2,
                                             const int16_t *gradX,
                                             const int16_t *gradY,
                                             uint16_t width,
                                             uint16_t height,
                                             uint32_t nfeatures,
                                             const uint16_t *x,
                                             const uint16_t *y,
                                             uint16_t *outx,
                                             uint16_t *outy,
                                             uint16_t *error,
                                             uint32_t max_iters,
                                             uint32_t earlyExitTh,
                                             const uint8_t *scratch);

#endif
/* ======================================================================== */
/*  End of file:  VLIB_trackFeaturesLucasKanade_7x7_cn.h                    */
/* ======================================================================== */

