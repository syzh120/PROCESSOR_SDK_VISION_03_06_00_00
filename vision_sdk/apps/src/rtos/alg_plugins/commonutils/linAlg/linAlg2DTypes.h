/*=======================================================================
 *
 *            Texas Instruments Internal Reference Software
 *
 *                           EP Systems Lab
 *                     Embedded Signal Processing
 *                             Imaging R&D
 *         
 *         Copyright (c) 2014 Texas Instruments, Incorporated.
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
 *  File: linAlg2DTypes.h
 *  
 =======================================================================*/

#ifndef _LINALG_2D_TYPES_INCLUDED_

#define _LINALG_2D_TYPES_INCLUDED_

#include "linAlgBasicTypes.h"

/******************************************
Vector/Point
******************************************/
typedef struct {
	Flouble x;
	Flouble y;
} Point2D_f;

/******************************************
Matrix
******************************************/
typedef struct {
	Flouble xx, xy;
	Flouble yx, yy;
} Matrix2D_f;

/*****************************************
*Affine Transform:
* - matrix A
* - translation t
******************************************/
typedef struct {
	Matrix2D_f A;
	Point2D_f b;
} Affine2D_f;

/*****************************************
*Euclidean transform (Pose):
* - rotation matrix R (orthonormal)
* - translation t
******************************************/
typedef struct {
	Matrix2D_f R;
	Point2D_f t;
} Pose2D_f;

#endif

