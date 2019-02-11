/* ======================================================================= */
/* DSPF_sp_cholesky_cmplx.c -- Cholesky decompostion and solver            */
/*              Optimized C Implementation (w/ Intrinsics)                 */
/*                                                                         */
/* Rev 1.0.0                                                               */
/*                                                                         */
/* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/  */
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */
#include <math.h>
#include <c6x.h>

#pragma CODE_SECTION(DSPF_sp_cholesky_cmplx, ".text:optimized");

#include "DSPF_sp_cholesky_cmplx.h"

#define ENABLE_NR 1
#define ENABLE_MATHLIB 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2sp/c66/atan2sp.h>
#include <ti/mathlib/src/cossp/c66/cossp.h>
#include <ti/mathlib/src/sinsp/c66/sinsp.h>
#endif

static void complex_sp_div(__float2_t cx,__float2_t cy,__float2_t *cz);
static void complex_sp_inv_sqrt(__float2_t x,__float2_t *z);

int DSPF_sp_cholesky_cmplx(int enable_test, const int Nrows, float *restrict A, float *restrict L)
{
  short i,j,k,Ncols;
  int addr;
  float yreal;
  __float2_t *AA,*LL;
  __float2_t sum,sum1,cx,cz;
#ifdef _LITTLE_ENDIAN
  __float2_t ctemp;
#endif

  _nassert(Nrows>0);
  _nassert((int)A % 8 == 0);
  _nassert((int)L % 8 == 0);

  /* initialize __float2_t arrays with input float arrays */
  addr=(int)(&A[0]);
  AA=(__float2_t *)(addr);
  addr=(int)(&L[0]);
  LL=(__float2_t *)(addr);

  Ncols=Nrows;
  if (enable_test) {
    /* test A for positive definite matrix:    */
    /* z_transpose*A*z>0 where z=1,2,...Nrows  */
	  sum1=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
    for (i=0;i<Nrows;i++) {
      sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
	  for (j=0;j<Nrows;j++) {
		yreal=(float)(j+1);
#ifndef _LITTLE_ENDIAN
		sum=_daddsp(sum,_complex_mpysp(AA[i*Ncols+j],_ftof2(yreal,0)));
#else
		ctemp=_complex_mpysp(AA[i*Ncols+j],_ftof2(0,yreal));
		sum=_daddsp(sum,_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
	  }
	  sum1=_daddsp(sum1,_dmpysp(_ftof2((float)(i+1),(float)(i+1)),sum));
    }
#ifndef _LITTLE_ENDIAN
    if (_hif2(sum1)<=0) {
#else
    if (_lof2(sum1)<=0) {
#endif
	  return -1;
    }
  }

  /* generate lower diagonal matrix L */
#pragma MUST_ITERATE(1,,)
  for (j=0;j<Nrows;j++) {
	/* diagonal entry */
	sum=_ftof2(0,0);
	for (k=0;k<=j-1;k++) {
#ifndef _LITTLE_ENDIAN
	  sum=_daddsp(sum,_complex_conjugate_mpysp(LL[j*Ncols+k],LL[j*Ncols+k]));
#else
	  ctemp=_complex_conjugate_mpysp(LL[j*Ncols+k],LL[j*Ncols+k]);
	  sum=_daddsp(sum,_ftof2(-_lof2(ctemp),_hif2(ctemp)));
#endif
	}
	cx=_dsubsp(AA[j*Ncols+j],sum);
	complex_sp_inv_sqrt(cx,&cz);
#ifndef _LITTLE_ENDIAN
	LL[j*Ncols+j]=_complex_mpysp(cx,cz);
#else
	ctemp=_complex_mpysp(cx,cz);
	LL[j*Ncols+j]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
    for (i=j+1;i<Nrows;i++) {

       if ((i==1)&&(j==1)) {
    	 k=0;
       }


      /* lower triangular entries */
      sum=_ftof2(0,0);
      for (k=0;k<=j-1;k++) {
#ifndef _LITTLE_ENDIAN
        sum=_daddsp(sum,_complex_conjugate_mpysp(LL[j*Ncols+k],LL[i*Ncols+k]));
#else
    	ctemp=_complex_conjugate_mpysp(LL[j*Ncols+k],LL[i*Ncols+k]);
    	sum=_daddsp(sum,_ftof2(-_lof2(ctemp),_hif2(ctemp)));
#endif
      }
      cx=_dsubsp(AA[i*Ncols+j],sum);
#ifndef _LITTLE_ENDIAN
      LL[i*Ncols+j]=_complex_mpysp(cx,cz);
#else
      ctemp=_complex_mpysp(cx,cz);
      LL[i*Ncols+j]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
	}
  }

  return 0;
}

int DSPF_sp_cholesky_in_place_cmplx(const int enable_test, const int Nrows, float *restrict A)
{
  short i,j,k,Ncols;
  int addr;
  float yreal;
  __float2_t *AA;
  __float2_t sum,sum1,cx,cz;
#ifdef _LITTLE_ENDIAN
  __float2_t ctemp;
#endif

  _nassert(Nrows>0);
  _nassert((int)A % 8 == 0);

  /* initialize __float2_t arrays with input float arrays */
  addr=(int)(&A[0]);
  AA=(__float2_t *)(addr);

  Ncols=Nrows;
  if (enable_test) {
    /* test A for positive definite matrix:    */
    /* z_transpose*A*z>0 where z=1,2,...Nrows  */
	  sum1=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
    for (i=0;i<Nrows;i++) {
      sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
	  for (j=0;j<Nrows;j++) {
		yreal=(float)(j+1);
#ifndef _LITTLE_ENDIAN
		sum=_daddsp(sum,_complex_mpysp(AA[i*Ncols+j],_ftof2(yreal,0)));
#else
		ctemp=_complex_mpysp(AA[i*Ncols+j],_ftof2(0,yreal));
		sum=_daddsp(sum,_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
	  }
	  sum1=_daddsp(sum1,_dmpysp(_ftof2((float)(i+1),(float)(i+1)),sum));
    }
#ifndef _LITTLE_ENDIAN
    if (_hif2(sum1)<=0) {
#else
    if (_lof2(sum1)<=0) {
#endif
  	  return -1;
    }
  }

  /* cholesky outer product version from p 145 Matrix Computations by Golub and Loan */
  /* use Newton Raphson iteration for y=1/sqrt(x) */
  /*   y[n+1]=y[n]*(3-x*y[n]*y[n])/2              */
  for (k=0;k<Nrows;k++) {
	  cx=AA[k*Ncols+k];
	  complex_sp_inv_sqrt(cx,&cz);
#ifndef _LITTLE_ENDIAN
	  AA[k*Ncols+k]=_complex_mpysp(cx,cz);
#else
	  ctemp=_complex_mpysp(cx,cz);
	  AA[k*Ncols+k]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif

	for (i=k+1;i<Nrows;i++) {
#ifndef _LITTLE_ENDIAN
	  AA[i*Ncols+k]=_complex_mpysp(AA[i*Ncols+k],cz);
#else
	  ctemp=_complex_mpysp(AA[i*Ncols+k],cz);
	  AA[i*Ncols+k]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
	}
	for (j=k+1;j<Nrows;j++) {
#pragma MUST_ITERATE(1,,)
      for (i=j;i<Nrows;i++) {
#ifndef _LITTLE_ENDIAN
    	AA[i*Ncols+j]=_dsubsp(AA[i*Ncols+j],_complex_conjugate_mpysp(AA[j*Ncols+k],AA[i*Ncols+k]));
#else
    	ctemp=_complex_conjugate_mpysp(AA[j*Ncols+k],AA[i*Ncols+k]);
    	AA[i*Ncols+j]=_dsubsp(AA[i*Ncols+j],_ftof2(-_lof2(ctemp),_hif2(ctemp)));
#endif
      }
    }
  }

  return 0;
}

int DSPF_sp_cholesky_solver_cmplx(const int Nrows,float *restrict L,float *restrict y,float *restrict b,float *restrict x)
{
  short i,k,Ncols;
  int addr;
  __float2_t *LL,*yy,*bb,*xx;
  __float2_t cx,cy,cz,sum;
#ifdef _LITTLE_ENDIAN
  __float2_t ctemp;
#endif

  _nassert(Nrows>0);
  _nassert((int)L % 8 == 0);
  _nassert((int)b % 8 == 0);
  _nassert((int)x % 8 == 0);

  addr=(int)(&L[0]);
  LL=(__float2_t *)(addr);
  addr=(int)(&y[0]);
  yy=(__float2_t *)(addr);
  addr=(int)(&b[0]);
  bb=(__float2_t *)(addr);
  addr=(int)(&x[0]);
  xx=(__float2_t *)(addr);

  /* solve L*y=b for y using forward substitution */
  Ncols=Nrows;
  for (i=0;i<Nrows;i++) {
    if (i==0) {
      cx=bb[i];
      cy=LL[0];
      complex_sp_div(cx,cy,&cz);
      yy[i]=cz;
	} else {
	  sum=_ftof2(0,0);
	  for (k=0;k<=i-1;k++) {
		cx=LL[i*Ncols+k];
		cy=yy[k];
#ifndef _LITTLE_ENDIAN
		sum=_daddsp(sum,_complex_mpysp(cx,cy));
#else
		ctemp=_complex_mpysp(cx,cy);
	    sum=_daddsp(sum,_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
	  }
	  cx=_dsubsp(bb[i],sum);
	  cy=LL[i*Ncols+i];
	  complex_sp_div(cx,cy,&cz);
	  yy[i]=cz;
	}
  }

  /* solve U*x=y for x using backward substitution */
  for (i=Nrows-1;i>=0;i--) {
	if (i==Nrows-1) {
	  cx=yy[i];
	  cy=LL[i*Ncols+i];
#ifndef _LITTLE_ENDIAN
	  cy=_ftof2(_hif2(cy),-_lof2(cy));
#else
	  cy=_ftof2(-_hif2(cy),_lof2(cy));
#endif
	  complex_sp_div(cx,cy,&cz);
	  xx[i]=cz;
	} else {
	  sum=_ftof2(0,0);
	  for (k=Nrows-1;k>=i+1;k--) {
		cx=LL[k*Ncols+i];
		cy=xx[k];
#ifndef _LITTLE_ENDIAN
		sum=_daddsp(sum,_complex_conjugate_mpysp(cx,cy));
#else
		ctemp=_complex_conjugate_mpysp(cx,cy);
		sum=_daddsp(sum,_ftof2(-_lof2(ctemp),_hif2(ctemp)));
#endif
	  }
	  cx=_dsubsp(yy[i],sum);
	  cy=LL[i*Ncols+i];
#ifndef _LITTLE_ENDIAN
	  cy=_ftof2(_hif2(cy),-_lof2(cy));
#else
	  cy=_ftof2(-_hif2(cy),_lof2(cy));
#endif
	  complex_sp_div(cx,cy,&cz);
	  xx[i]=cz;
	}
  }

  return 0;
}

static void complex_sp_div(__float2_t cx,__float2_t cy,__float2_t *cz) {

  float x_real,x_imag,y_real,y_imag,z_real,z_imag;
  float inv_mag_sq;
#ifdef ENABLE_NR
  float x,y;
#endif

#ifndef _LITTLE_ENDIAN
  x_real=_hif2(cx);
  x_imag=_lof2(cx);
  y_real=_hif2(cy);
  y_imag=_lof2(cy);
#else
  x_real=_lof2(cx);
  x_imag=_hif2(cx);
  y_real=_lof2(cy);
  y_imag=_hif2(cy);
#endif
#ifndef ENABLE_NR
  inv_mag_sq=1/(y_real*y_real+y_imag*y_imag);
#else
  x=y_real*y_real+y_imag*y_imag;
  y=_rcpsp(x);
  y=y*(2.0-x*y);
  y=y*(2.0-x*y);
  inv_mag_sq=y;
#endif

  /* results */
  z_real=(x_real*y_real+x_imag*y_imag)*inv_mag_sq;
  z_imag=(x_imag*y_real-x_real*y_imag)*inv_mag_sq;
#ifndef _LITTLE_ENDIAN
  *cz=_ftof2(z_real,z_imag);
#else
  *cz=_ftof2(z_imag,z_real);
#endif

}

static void complex_sp_inv_sqrt(__float2_t cx,__float2_t *cz) {

  float x_mag,z_mag,z_real,z_imag;
  float x_angle,z_angle;
  __float2_t ctemp;
#ifdef ENABLE_NR
  float x,y;
#endif

  /* magnitude */
  ctemp=_dmpysp(cx,cx);
  x_mag=sqrt(_hif2(ctemp)+_lof2(ctemp));
#ifndef ENABLE_NR
  z_mag=1/sqrt(x_mag);
#else
  x=x_mag;
  y=_rsqrsp(x);
  y=0.5*y*(3.0-x*y*y);
  y=0.5*y*(3.0-x*y*y);
  z_mag=y;
#endif

  /* angle */
#ifndef _LITTLE_ENDIAN

#ifndef ENABLE_MATHLIB
  x_angle=atan2(_lof2(cx),_hif2(cx));
#else
  x_angle=atan2sp(_lof2(cx),_hif2(cx));
#endif

#else

#ifndef ENABLE_MATHLIB
  x_angle=atan2(_hif2(cx),_lof2(cx));
#else
  x_angle=atan2sp(_hif2(cx),_lof2(cx));
#endif

#endif
  z_angle=-x_angle*0.5;

  /* results */
#ifndef ENABLE_MATHLIB
  z_real=cos(z_angle)*z_mag;
  z_imag=sin(z_angle)*z_mag;
#else
  z_real=cossp(z_angle)*z_mag;
  z_imag=sinsp(z_angle)*z_mag;
#endif

#ifndef _LITTLE_ENDIAN
  *cz=_ftof2(z_real,z_imag);
#else
  *cz=_ftof2(z_imag,z_real);
#endif

}

/* ======================================================================= */
/*  End of file:  DSPF_sp_cholesky_cmplx.c                                 */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
