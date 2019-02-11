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

#ifndef VLIB_CANNY_EDGE_DETECTION_CN_H_
#define VLIB_CANNY_EDGE_DETECTION_CN_H_ 1

#include "../common/VLIB_types.h"

void VLIB_conv_7x7_i8_c8s_cn(const uint8_t *restrict imgin_ptr,
                             uint8_t       *restrict imgout_ptr,
                             uint32_t width,
                             int16_t pitch,
                             const int8_t *restrict mask_ptr,
                             int16_t shift);

int32_t VLIB_doublethresholding_cn(int16_t *restrict pInMag,
                                   uint8_t *edgeMap,
                                   uint32_t *restrict strongEdgeListPtr,
                                   int32_t *numStrongEdges,
                                   uint16_t width,
                                   uint16_t pitch,
                                   uint16_t height,
                                   uint8_t loThresh,
                                   uint8_t hiThresh,
                                   uint32_t pos_frm);

int32_t VLIB_nonMaximumSuppressionCanny_cn(int16_t *restrict pInMag,
                                           int16_t *restrict pInGradX,
                                           int16_t *restrict pInGradY,
                                           uint8_t *restrict pOutBlk,
                                           uint16_t blkWidth,
                                           uint16_t pitch,
                                           uint16_t blkHeight);

int32_t VLIB_edgeRelaxation_cn(uint8_t *edgeMap,
                               uint32_t *restrict strongEdgeListPtr,
                               int32_t *numStrongEdges,
                               uint16_t width);

void VLIB_Canny_Edge_Detection_cn(uint8_t *pInput,
                                  int16_t *pBufGradX,
                                  int16_t *pBufGradY,
                                  int16_t *pBufMag,
                                  uint8_t *pBufOut,
                                  uint8_t *pScratch,
                                  int32_t *numItems,
                                  uint16_t width,
                                  uint16_t height);

#endif

/* ======================================================================== */
/*  End of file:  VLIB_Canny_Edge_Detection_cn.h                            */
/* ======================================================================== */

