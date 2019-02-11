/*=======================================================================
*
*            Texas Instruments Internal Reference Software
*
*                           EP Systems Lab
*                    Perception & Analytics Lab R&D
*
*         Copyright (c) 2015 Texas Instruments, Incorporated.
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
*  File: lens_distortion_correction.c
*
=======================================================================*/

#include "lens_distortion_correction.h"
#include <math.h>

/*----------------------------------------------------------------------------------
Internal Function Declarations
-----------------------------------------------------------------------------------*/
#if LDC_LIB_DATA_TYPE<2 
dtype lut_lookup_floating(dtype *lut, dtype inval, Int32 indMax, dtype stepInv, LDC_status *status);
#endif

/*----------------------------------------------------------------------------------
API Function Implementation
-----------------------------------------------------------------------------------*/
/***********************************************************************************
*
************************************************************************************/
LDC_status LDC_Init(LensDistortionCorrection* ldc,
						   dtype distCenterX, dtype distCenterY, dtype distFocalLength,
						   dtype *lut_d2u, Int32 lut_d2u_length, dtype lut_d2u_step,
						   dtype *lut_u2d, Int32 lut_u2d_length, dtype lut_u2d_step)
{
#if LDC_LIB_DATA_TYPE!=0 && LDC_LIB_DATA_TYPE!=1
	"LDC_LIB_DATA_TYPE must be 0 (float) or 1 (double) in lens_distortion_correction.h"
#endif
	/*FLOATING TYPE*/
	/*distortion center*/
	ldc->distCenterX = distCenterX;
	ldc->distCenterY = distCenterY;
	ldc->distFocalLength = distFocalLength;
	ldc->distFocalLengthInv = 1/ldc->distFocalLength;
	/*ldc look-up table parameters*/
	ldc->lut_d2u_indMax = lut_d2u_length-1;
	ldc->lut_d2u_step = lut_d2u_step;
	ldc->lut_u2d_indMax = lut_u2d_length - 1;
	ldc->lut_u2d_step = lut_u2d_step;

	ldc->lut_d2u_stepInv = 1/ldc->lut_d2u_step;
	ldc->lut_u2d_stepInv = 1/ldc->lut_u2d_step;


	/*ldc look-up table pointers*/
	ldc->lut_d2u = lut_d2u;
	ldc->lut_u2d = lut_u2d;

	return LDC_STATUS_OK;
}

/***********************************************************************************
*
************************************************************************************/
LDC_status LDC_DistToUndist(LensDistortionCorrection* ldc, dtype point_in[2], dtype point_out[2], dtype *lut_in_val)
{
#if LDC_LIB_DATA_TYPE!=0 && LDC_LIB_DATA_TYPE!=1
	"LDC_LIB_DATA_TYPE must be 0 (float) or 1 (double)"
#endif
#if LDC_LIB_D2U_LUT_TYPE!=0 
	"LDC_LIB_D2U_LUT_TYPE must be 0 "
#endif

	LDC_status status;
	dtype diffX, diffY;
	dtype ruDivRd;

#if LDC_LIB_D2U_LUT_TYPE == 0
	diffX = point_in[0] - ldc->distCenterX;
	diffY = point_in[1] - ldc->distCenterY;
	*lut_in_val = diffX*diffX + diffY*diffY;
	ruDivRd = lut_lookup_floating(ldc->lut_d2u, *lut_in_val, ldc->lut_d2u_indMax, ldc->lut_d2u_stepInv, &status);
	point_out[0] = diffX * ruDivRd + ldc->distCenterX;
	point_out[1] = diffY * ruDivRd + ldc->distCenterY;
#endif

	return status;
}

/***********************************************************************************
*
************************************************************************************/
LDC_status LDC_UndistToDist(LensDistortionCorrection* ldc, dtype point_in[2], dtype point_out[2])
{
#if LDC_LIB_DATA_TYPE!=0 && LDC_LIB_DATA_TYPE!=1
	"LDC_LIB_DATA_TYPE must be 0 (float) or 1 (double) in lens_distortion_correction.h"
#endif
#if LDC_LIB_U2D_LUT_TYPE!=0 && LDC_LIB_U2D_LUT_TYPE!=1 && LDC_LIB_U2D_LUT_TYPE!=2
	"LDC_LIB_U2D_LUT_TYPE must be 0, 1 or 2"
#endif

	LDC_status status;
	dtype diffX, diffY;
	dtype lut_in_val;
	dtype lut_out_val;

	diffX = point_in[0] - ldc->distCenterX;
	diffY = point_in[1] - ldc->distCenterY;

#if LDC_LIB_U2D_LUT_TYPE == 0 || LDC_LIB_U2D_LUT_TYPE == 2
	dtype ru;
	#if LDC_LIB_DATA_TYPE==0 
		ru = sqrtf(diffX*diffX + diffY*diffY);
		lut_in_val = atanf(ru*ldc->distFocalLengthInv);
	#elif LDC_LIB_DATA_TYPE==1
		ru = sqrt(diffX*diffX + diffY*diffY);
		lut_in_val = atan(ru*ldc->distFocalLengthInv);
	#endif
#elif LDC_LIB_U2D_LUT_TYPE == 1
	#if LDC_LIB_DATA_TYPE==0 
		lut_in_val = sqrtf(diffX*diffX + diffY*diffY);
	#elif LDC_LIB_DATA_TYPE==1
		lut_in_val = sqrt(diffX*diffX + diffY*diffY);
	#endif
#endif

	lut_out_val = lut_lookup_floating(ldc->lut_u2d, lut_in_val, ldc->lut_u2d_indMax, ldc->lut_u2d_stepInv, &status);

#if LDC_LIB_U2D_LUT_TYPE == 0 || LDC_LIB_U2D_LUT_TYPE == 1
	point_out[0] = diffX * lut_out_val + ldc->distCenterX;
	point_out[1] = diffY * lut_out_val + ldc->distCenterY;
#elif LDC_LIB_U2D_LUT_TYPE == 2
	if (ru==0)
	{
		point_out[0] = ldc->distCenterX;
		point_out[1] = ldc->distCenterY;
	}
	else
	{
		point_out[0] = lut_out_val * diffX / ru + ldc->distCenterX;
		point_out[1] = lut_out_val * diffY / ru + ldc->distCenterY;
	}
#endif

	return status;
}


/*----------------------------------------------------------------------------------
Internal Function Implementation
-----------------------------------------------------------------------------------*/
/***********************************************************************************
*
************************************************************************************/
#if LDC_LIB_DATA_TYPE<2 
dtype lut_lookup_floating(dtype *lut, dtype inval, Int32 indMax, dtype stepInv, LDC_status *status)
{
	*status = LDC_STATUS_OK;
	dtype ind = inval * stepInv;
	if (ind >= (dtype)indMax)
	{
		*status = LDC_STATUS_FAIL;
		return lut[indMax];
	}


#if LDC_LIB_INTERPOLATION_METHOD==0
	return lut[(Int32)ind];
#elif LDC_LIB_INTERPOLATION_METHOD==1
	return lut[(Int32)(ind + 0.5)];
#elif LDC_LIB_INTERPOLATION_METHOD==2
	Int32 N = (Int32)ind;
	dtype indMinN = ind - (dtype)N;
	return (1.0f - indMinN)*lut[N] + indMinN * lut[N + 1];
#endif
}
#endif



