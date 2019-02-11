/*
 *******************************************************************************
 *
 * Copyright (C) 2015 Texas Instruments Incorporated - http://www.ti.com/
 * ALL RIGHTS RESERVED
 *
 *******************************************************************************
 *
 *  File: sgxRender3Dutils.h
 *
 *  Custom utilities for sgxRender3D links
 *  
 ******************************************************************************/

#ifndef _SGX_RENDER_3D_UTILS_INCLUDED_

#define _SGX_RENDER_3D_UTILS_INCLUDED_

#include <include/alglink_api/algorithmLink_sfmMap.h>
#include <float.h>
#include <math.h>

/****************************************************
*Constants
****************************************************/
#if LIN_ALG_FLOUBLE_TYPE == 0
	#define FLOUBLE_MAX FLT_MAX
	#define FLOUBLE_EPSILON FLT_EPSILON
#elif LIN_ALG_FLOUBLE_TYPE == 1
	#define FLOUBLE_MAX DBL_MAX
	#define FLOUBLE_EPSILON DBL_EPSILON
#endif

/****************************************************
*Basic Functions
****************************************************/
#if LIN_ALG_FLOUBLE_TYPE == 0
	#define SQRT(x)  sqrtf((x))
	#define ATAN(x)  atanf((x))
#elif LIN_ALG_FLOUBLE_TYPE == 1
	#define SQRT(x)  sqrt((x))
	#define ATAN(x)  atan((x))
#endif

/****************************************************
*Functions in 3D
****************************************************/
/*p_out = -p;*/
static inline void point3Dnegate(Point3D_f *p){
	p->x = -p->x;
	p->y = -p->y;
	p->z = -p->z;
}

/* Euclidean distance between two 3D points*/
static inline Flouble dist3D(Point3D_f *v1, Point3D_f *v2){
	Flouble dx = v1->x - v2->x;
	Flouble dy = v1->y - v2->y;
	Flouble dz = v1->z - v2->z;

	return SQRT(dx *dx + dy * dy + dz * dz);
}

/* initialize matrix with value val*/
static inline void matrix3Dinit(Matrix3D_f *M, Flouble val){
	M->xx = val; M->xy = val; M->xz = val;
	M->yx = val; M->yy = val; M->yz = val;
	M->zx = val; M->zy = val; M->zz = val;
}

/*matrix multiplication m_out = m1 * m2;*/
static inline void matrix3Dcat(Matrix3D_f *m1, Matrix3D_f *m2, Matrix3D_f *mout){
	mout->xx = m1->xx * m2->xx + m1->xy * m2->yx + m1->xz * m2->zx;
	mout->xy = m1->xx * m2->xy + m1->xy * m2->yy + m1->xz * m2->zy;
	mout->xz = m1->xx * m2->xz + m1->xy * m2->yz + m1->xz * m2->zz;

	mout->yx = m1->yx * m2->xx + m1->yy * m2->yx + m1->yz * m2->zx;
	mout->yy = m1->yx * m2->xy + m1->yy * m2->yy + m1->yz * m2->zy;
	mout->yz = m1->yx * m2->xz + m1->yy * m2->yz + m1->yz * m2->zz;

	mout->zx = m1->zx * m2->xx + m1->zy * m2->yx + m1->zz * m2->zx;
	mout->zy = m1->zx * m2->xy + m1->zy * m2->yy + m1->zz * m2->zy;
	mout->zz = m1->zx * m2->xz + m1->zy * m2->yz + m1->zz * m2->zz;
}

/* xyz_out = M*xyz_int*/
static inline void matrix3Dtransform(Matrix3D_f *m, Point3D_f *vin, Point3D_f *vout){
	vout->x = m->xx*vin->x + m->xy*vin->y + m->xz*vin->z;
	vout->y = m->yx*vin->x + m->yy*vin->y + m->yz*vin->z;
	vout->z = m->zx*vin->x + m->zy*vin->y + m->zz*vin->z;
}

/* inverse of 3D pose*/
static inline void pose3Dinv(Pose3D_f *p, Pose3D_f *pinv){
	pinv->R.xx = p->R.xx; pinv->R.xy = p->R.yx; pinv->R.xz = p->R.zx;
	pinv->R.yx = p->R.xy; pinv->R.yy = p->R.yy; pinv->R.yz = p->R.zy;
	pinv->R.zx = p->R.xz; pinv->R.zy = p->R.yz; pinv->R.zz = p->R.zz;

	pinv->t.x = -(pinv->R.xx*p->t.x + pinv->R.xy*p->t.y + pinv->R.xz*p->t.z);
	pinv->t.y = -(pinv->R.yx*p->t.x + pinv->R.yy*p->t.y + pinv->R.yz*p->t.z);
	pinv->t.z = -(pinv->R.zx*p->t.x + pinv->R.zy*p->t.y + pinv->R.zz*p->t.z);
}

/*pose concatenation, pcat = p2 * p1*/
static inline void pose3Dcat(Pose3D_f *pcat, Pose3D_f *p2, Pose3D_f *p1){
	pcat->R.xx = p2->R.xx * p1->R.xx + p2->R.xy * p1->R.yx + p2->R.xz * p1->R.zx;
	pcat->R.xy = p2->R.xx * p1->R.xy + p2->R.xy * p1->R.yy + p2->R.xz * p1->R.zy;
	pcat->R.xz = p2->R.xx * p1->R.xz + p2->R.xy * p1->R.yz + p2->R.xz * p1->R.zz;
	pcat->R.yx = p2->R.yx * p1->R.xx + p2->R.yy * p1->R.yx + p2->R.yz * p1->R.zx;
	pcat->R.yy = p2->R.yx * p1->R.xy + p2->R.yy * p1->R.yy + p2->R.yz * p1->R.zy;
	pcat->R.yz = p2->R.yx * p1->R.xz + p2->R.yy * p1->R.yz + p2->R.yz * p1->R.zz;
	pcat->R.zx = p2->R.zx * p1->R.xx + p2->R.zy * p1->R.yx + p2->R.zz * p1->R.zx;
	pcat->R.zy = p2->R.zx * p1->R.xy + p2->R.zy * p1->R.yy + p2->R.zz * p1->R.zy;
	pcat->R.zz = p2->R.zx * p1->R.xz + p2->R.zy * p1->R.yz + p2->R.zz * p1->R.zz;

	pcat->t.x = (p2->R.xx*p1->t.x + p2->R.xy*p1->t.y + p2->R.xz*p1->t.z) + p2->t.x;
	pcat->t.y = (p2->R.yx*p1->t.x + p2->R.yy*p1->t.y + p2->R.yz*p1->t.z) + p2->t.y;
	pcat->t.z = (p2->R.zx*p1->t.x + p2->R.zy*p1->t.y + p2->R.zz*p1->t.z) + p2->t.z;
}

/* xyz_out = R*xyz_in + t*/
static inline void pose3Dtransform(Pose3D_f *A, Point3D_f *xyz_in, Point3D_f *xyz_out){
	xyz_out->x = A->R.xx * xyz_in->x + A->R.xy * xyz_in->y + A->R.xz * xyz_in->z + A->t.x;
	xyz_out->y = A->R.yx * xyz_in->x + A->R.yy * xyz_in->y + A->R.yz * xyz_in->z + A->t.y;
	xyz_out->z = A->R.zx * xyz_in->x + A->R.zy * xyz_in->y + A->R.zz * xyz_in->z + A->t.z;
}

/****************************************************
* Camera/Lens-specific Operations
****************************************************/
UInt32 project3DPointToImage(Point3D_f *xyzc, Point3D_f *xyd);


#endif

