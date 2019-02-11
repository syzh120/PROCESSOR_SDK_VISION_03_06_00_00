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
*  File: lens_distortion_correction.h
*
=======================================================================*/

#ifndef LENS_DISTORTION_CORRECTION_INCLUDED
#define LENS_DISTORTION_CORRECTION_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#include "ldc_config.h"

/*================================================
Data Structure
================================================== */ 

/*data type*/
#if LDC_LIB_DATA_TYPE==2
typedef Int32 dtype;
#elif LDC_LIB_DATA_TYPE==1
typedef double dtype;
#elif LDC_LIB_DATA_TYPE==0
typedef float dtype;
#endif

/*status flag*/
typedef enum {
	LDC_STATUS_OK,
	LDC_STATUS_FAIL
} LDC_status;

/*main struct*/
typedef struct {
	dtype distCenterX; 
	dtype distCenterY; 
	dtype distFocalLength;
	dtype distFocalLengthInv;
	dtype *lut_d2u;
	Int32 lut_d2u_indMax;
	dtype lut_d2u_step;
	dtype lut_d2u_stepInv;
	dtype *lut_u2d;
	Int32 lut_u2d_indMax;
	dtype lut_u2d_step;
	dtype lut_u2d_stepInv;
} LensDistortionCorrection;

/*================================================
Function API
================================================== */
/* Initialize LensDistortionCorrection object*/
LDC_status LDC_Init(LensDistortionCorrection* ldc,
						   dtype distCenterX, dtype distCenterY, dtype distFocalLength,
						   dtype *lut_d2u, Int32 lut_d2u_length, dtype lut_d2u_step,
						   dtype *lut_u2d, Int32 lut_u2d_length, dtype lut_u2d_step);

/*
 * Convert distorted point coordinates to undistorted point coordinates.
 * In addition, output radius squared (rdSq_out) of distorted point.
 */
LDC_status LDC_DistToUndist(LensDistortionCorrection* ldc, dtype point_in[2], dtype point_out[2], dtype *rdSq_out);

/*
 * Convert undistorted point coordinates to distorted point coordinates.
 */
LDC_status LDC_UndistToDist(LensDistortionCorrection* ldc, dtype point_in[2], dtype point_out[2]);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif 




