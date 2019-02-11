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
 *  File: linAlg3DTypes.h
 *  
 =======================================================================*/

#ifndef _LINALG_3D_TYPES_INCLUDED_

#define _LINALG_3D_TYPES_INCLUDED_

#include "linAlgBasicTypes.h"

/******************************************
Vector/Point
******************************************/
typedef struct {
	Flouble x;
	Flouble y;
	Flouble z;
} Point3D_f;

/******************************************
Matrix
******************************************/
typedef struct {
	Flouble xx, xy, xz;
	Flouble yx, yy, yz;
	Flouble zx, zy, zz;
} Matrix3D_f;

/*****************************************
*Affine Transform:
* - matrix A
* - translation t
******************************************/
typedef struct {
	Matrix3D_f A;
	Point3D_f t;
} Affine3D_f;

/*****************************************
*Euclidean transform (Pose):
* - rotation matrix R (orthonormal)
* - translation t
******************************************/
typedef struct {
	Matrix3D_f R;
	Point3D_f t;
} Pose3D_f;

#endif

