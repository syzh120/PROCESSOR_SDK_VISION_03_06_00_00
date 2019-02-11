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
*  File: svGenerate_3D_LDCLUT.h
*
=======================================================================*/
#ifndef _SV_GENERATE_3D_LDCLUT_H_
#define _SV_GENERATE_3D_LDCLUT_H_

#include "../include/svGAlignStruct.h"

#ifdef PC_VERSION
void read3dmesh(svGAlignStruct *sv, uWord32 viewid);
#endif
void svSetFrameCenters_3D(svGAlignStruct* sv);
void svGenerate_3D_LDCLUT(svGAlignStruct* sv, Word32* calmatin3d);

#endif
