/*=======================================================================
*
*            Texas Instruments Internal Reference Software
*
*                           EP Systems Lab
*                     Embedded Signal Processing
*                             Imaging R&D
*
*         Copyright (c) 2016 Texas Instruments, Incorporated.
*                        All Rights Reserved.
*
*
*          FOR TI INTERNAL USE ONLY. NOT TO BE REDISTRIBUTED.
*
*                 TI Confidential - Maximum Restrictions
*
*
*
*=======================================================================
*
*  File: svTransform.h
*
=======================================================================*/
#ifndef _SV_TRANSFORM_H_
#define _SV_TRANSFORM_H_

#include "../include/svGAlignStruct.h"

void svProjectiveTransform_float(svGAlignStruct* sv, Word32 regmark,
                            float *SV_origin, float X, float Y, float Z);
void svFisheyeTransform_distort_LDC(svGAlignStruct* sv, Word32 regmark);

#endif
