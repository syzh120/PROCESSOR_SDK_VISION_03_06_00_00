/* ======================================================================= */
/* DSPF_dp_qrd_cmplx.c -- complex QR decomposition                         */
/*                 Optimized C Implementation                              */
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
#include <string.h>

#pragma CODE_SECTION(DSPF_dp_qrd_cmplx,".text:optimized");

#include "DSPF_dp_qrd_cmplx.h"

#define ENABLE_NR 1
#define ENABLE_MATHLIB 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2dp/c66/atan2dp.h>
#include <ti/mathlib/src/cosdp/c66/cosdp.h>
#include <ti/mathlib/src/sindp/c66/sindp.h>
#endif

static void complex_dp_inv(double y_real,double y_imag,double *z_real,double *z_imag);
static void complex_dp_div(double x_real,double x_imag,double y_real,double y_imag,double *z_real,double *z_imag);


int DSPF_dp_qrd_cmplx(const int Nrows,const int Ncols, double *restrict A, double *restrict Q,double *restrict R,double *restrict u)
{
  int row,col,i,k,loop_count,Nrows2,Ncols2;
  double xreal,ximag,yreal,yimag,zreal,zimag;
  double sum_real,sum_imag,scale_real,scale_imag;
  double sum,alpha;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)A % 8 == 0);
  _nassert((int)Q % 8 == 0);
  _nassert((int)R % 8 == 0);
  _nassert((int)u % 8 == 0);

  /* ------------------------------------------------------------------- */
   /* generate identify matrix and copy A to R                            */
   /* ------------------------------------------------------------------- */
   memcpy(R,A,sizeof(double)*Nrows*2*Ncols);
   memset(Q,0.0,sizeof(double)*Nrows*2*Nrows);
   for (row=0;row<Nrows;row++) {
 	 Q[2*row  +row*2*Nrows] = 1.0;
   }

  if (Nrows<=Ncols) {
	loop_count=Nrows-2;
  } else {
	loop_count=Ncols-1;
  }
  Ncols2=2*Ncols;
  Nrows2=2*Nrows;
  for (col=0;col<=loop_count;col++) {
    sum=0;
#pragma MUST_ITERATE(1,,)
    for (row=col;row<Nrows;row++) {
      xreal=R[2*col  +row*Ncols2];
      ximag=R[2*col+1+row*Ncols2];
      sum+=xreal*xreal+ximag*ximag;
    }
    if (sum!=0) {
      alpha=-sqrt(sum);
      if (R[2*col  +col*Ncols2]>=0){
    	alpha=-alpha;
      }
      u[2*col  ]=R[2*col  +col*Ncols2]+alpha;
      u[2*col+1]=R[2*col+1+col*Ncols2];
      R[2*col  +col*Ncols2]=-alpha;
      R[2*col+1+col*Ncols2]=0;
#pragma MUST_ITERATE(1,,)
      for (row=col+1;row<Nrows;row++) {
      	u[2*row  ]=R[2*col  +row*Ncols2];
      	u[2*row+1]=R[2*col+1+row*Ncols2];
      	R[2*col  +row*Ncols2]=0;
      	R[2*col+1+row*Ncols2]=0;
      	xreal=u[2*row  ];
      	ximag=u[2*row+1];
      }
      zreal=alpha*u[2*col  ];
      zimag=alpha*u[2*col+1];
      if ((zreal!=0)||(zimag!=0)) {
    	complex_dp_inv(zreal,zimag,&scale_real,&scale_imag);
    	/* R=Q1*R */
    	for (i=col+1;i<Ncols;i++) {
          sum_real=0;
          sum_imag=0;
#pragma MUST_ITERATE(1,,)
          for (k=col;k<Nrows;k++) {
          	xreal= u[2*k  ];
          	ximag=-u[2*k+1];
          	yreal=R[2*i  +k*Ncols2];
          	yimag=R[2*i+1+k*Ncols2];
          	sum_real+=xreal*yreal-ximag*yimag;
          	sum_imag+=xreal*yimag+ximag*yreal;
          }
          xreal=sum_real;
          ximag=sum_imag;
          yreal=scale_real;
          yimag=scale_imag;
          sum_real=xreal*yreal-ximag*yimag;
          sum_imag=xreal*yimag+ximag*yreal;
#pragma MUST_ITERATE(1,,)
          for (k=col;k<Nrows;k++) {
          	xreal=u[2*k  ];
          	ximag=u[2*k+1];
          	yreal=sum_real;
          	yimag=sum_imag;
          	R[2*i  +k*Ncols2]-=xreal*yreal-ximag*yimag;
          	R[2*i+1+k*Ncols2]-=xreal*yimag+ximag*yreal;
          }
    	}
    	/* Q=Q*Q1 */
    	for (i=0;i<Nrows;i++) {
      	  sum_real=0;
      	  sum_imag=0;
#pragma MUST_ITERATE(1,,)
    	  for (k=col;k<Nrows;k++) {
      		xreal= u[2*k  ];
      		ximag=-u[2*k+1];
      		yreal=Q[2*k  +i*Nrows2];
      		yimag=Q[2*k+1+i*Nrows2];
      		sum_real+=xreal*yreal-ximag*yimag;
      		sum_imag+=xreal*yimag+ximag*yreal;
    	  }
    	  xreal=sum_real;
    	  ximag=sum_imag;
    	  yreal=scale_real;
    	  yimag=scale_imag;
    	  sum_real=xreal*yreal-ximag*yimag;
    	  sum_imag=xreal*yimag+ximag*yreal;
#pragma MUST_ITERATE(1,,)
    	  for (k=col;k<Nrows;k++) {
      		xreal=u[2*k  ];
      		ximag=u[2*k+1];
      		yreal=sum_real;
      		yimag=sum_imag;
      		Q[2*k  +i*Nrows2]-=xreal*yreal-ximag*yimag;
      		Q[2*k+1+i*Nrows2]-=xreal*yimag+ximag*yreal;
    	  }
    	}
      } /* if (norm_sqr!=0) */
    } /* if (sum!=0) */
  } /* for (col=0;col<=loop_count;col++) */

  /* Q=conj(Q) */
  for (row=0;row<Nrows;row++) {
	for (col=0;col<Nrows;col++) {
	  Q[2*col+1+row*Nrows2]=-Q[2*col+1+row*Nrows2];
	}
  }

  return 0;
}

int DSPF_dp_qrd_solver_cmplx(const int Nrows,const int Ncols,double *restrict Q,double *restrict R,double *restrict b,double *restrict y,double *restrict x) {

  short row,col,loop_cnt,Nrows2,Ncols2;
  double xreal,ximag,yreal,yimag,zreal,zimag,sum_real,sum_imag;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)Q % 8 == 0);
  _nassert((int)R % 8 == 0);
  _nassert((int)b % 8 == 0);
  _nassert((int)y % 8 == 0);
  _nassert((int)x % 8 == 0);

  /* generate y=Q'*b */
  Nrows2=2*Nrows;
  Ncols2=2*Ncols;
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
	sum_real=0;
	sum_imag=0;
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Nrows;col++) {
	  xreal= Q[2*row  +col*Nrows2];
	  ximag=-Q[2*row+1+col*Nrows2];
	  yreal=b[2*col  ];
	  yimag=b[2*col+1];
	  sum_real+=xreal*yreal-ximag*yimag;
	  sum_imag+=xreal*yimag+ximag*yreal;
	}
	y[2*row  ]=sum_real;
	y[2*row+1]=sum_imag;
  }

  /* use backward substitution to solve x=inv(R)*y */
  if (Nrows>=Ncols) loop_cnt=Ncols;
  else              loop_cnt=Nrows;
  memset(x,0,sizeof(double)*Ncols2);
#pragma MUST_ITERATE(1,,)
  for (row=loop_cnt-1;row>=0;row--) {
	sum_real=0;
	sum_imag=0;
#pragma MUST_ITERATE(1,,)
	for (col=row+1;col<loop_cnt;col++) {
	  xreal=R[2*col  +row*Ncols2];
	  ximag=R[2*col+1+row*Ncols2];
	  yreal=x[2*col  ];
	  yimag=x[2*col+1];
	  sum_real+=xreal*yreal-ximag*yimag;
	  sum_imag+=xreal*yimag+ximag*yreal;
	}
	xreal=y[2*row  ]-sum_real;
	ximag=y[2*row+1]-sum_imag;
	yreal=R[2*row  +row*2*Ncols];
	yimag=R[2*row+1+row*2*Ncols];
	complex_dp_div(xreal,ximag,yreal,yimag,&zreal,&zimag);
	x[2*row  ]=zreal;
	x[2*row+1]=zimag;
  }

  return 0;
}

int DSPF_dp_qrd_inverse_cmplx(const int Nrows,const int Ncols,double *restrict Q,double *restrict R,double *restrict inv_A) {

  int row,col,k,Ncols2;
  double xreal,ximag,yreal,yimag,zreal,zimag;
  double factor_real,factor_imag,sum_real,sum_imag;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)Q % 8 == 0);
  _nassert((int)R % 8 == 0);
  _nassert((int)inv_A % 8 == 0);


  /* set inv_A matrix to identity */
  Ncols2=2*Ncols;
  memset(inv_A,0.0,sizeof(double)*Nrows*Ncols2);
  for (row=0;row<Nrows;row++) {
	inv_A[2*row  +row*Ncols2]=1.0;
  }

  /* use Gauss Jordan algorithm to invert R whose result will be in inv_A */
#pragma MUST_ITERATE(1,,)
  for (col=Ncols-1;col>=1;col--) {
	xreal=R[2*col  +col*Ncols2];
	ximag=R[2*col+1+col*Ncols2];
	complex_dp_inv(xreal,ximag,&zreal,&zimag);

#pragma MUST_ITERATE(1,,)
	for (row=col-1;row>=0;row--) {
	  xreal=R[2*col  +row*Ncols2];
	  ximag=R[2*col+1+row*Ncols2];
	  factor_real=xreal*zreal-ximag*zimag;
	  factor_imag=xreal*zimag+ximag*zreal;

#pragma MUST_ITERATE(1,,)
	  for (k=0;k<Ncols;k++) {
		xreal=factor_real;
		ximag=factor_imag;
		yreal=inv_A[2*k  +col*Ncols2];
		yimag=inv_A[2*k+1+col*Ncols2];
		inv_A[2*k  +row*Ncols2]-=xreal*yreal-ximag*yimag;
		inv_A[2*k+1+row*Ncols2]-=xreal*yimag+ximag*yreal;
		yreal=R[2*k  +col*Ncols2];
		yimag=R[2*k+1+col*Ncols2];
		R[2*k  +row*Ncols2]-=xreal*yreal-ximag*yimag;
		R[2*k+1+row*Ncols2]-=xreal*yimag+ximag*yreal;
	  }
	}
  }

  /* scale R and inv_A to get identity matrix in R */
#pragma MUST_ITERATE(1,,)
  for (row=Nrows-1;row>=0;row--) {
	xreal=R[2*row  +row*Ncols2];
	ximag=R[2*row+1+row*Ncols2];
	complex_dp_inv(xreal,ximag,&factor_real,&factor_imag);
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Ncols;col++) {
	  yreal=inv_A[2*col  +row*Ncols2];
	  yimag=inv_A[2*col+1+row*Ncols2];
	  inv_A[2*col  +row*Ncols2]=factor_real*yreal-factor_imag*yimag;
	  inv_A[2*col+1+row*Ncols2]=factor_real*yimag+factor_imag*yreal;
	}
  }

  /* inv_A = inv_R * Q' */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Ncols;col++) {
	  sum_real=0;
	  sum_imag=0;
#pragma MUST_ITERATE(1,,)
      for (k=0;k<Ncols;k++) {
      	xreal=inv_A[2*k  +row*2*Ncols];
      	ximag=inv_A[2*k+1+row*2*Ncols];
      	yreal= Q[2*k  +col*2*Ncols];
      	yimag=-Q[2*k+1+col*2*Ncols];
      	sum_real+=xreal*yreal-ximag*yimag;
      	sum_imag+=xreal*yimag+ximag*yreal;
      }
      R[2*col  ]=sum_real;
      R[2*col+1]=sum_imag;
	}
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Ncols;col++) {
	  inv_A[2*col  +row*2*Ncols]=R[2*col  ];
	  inv_A[2*col+1+row*2*Ncols]=R[2*col+1];
	}
  }

  return 0;
}

static void complex_dp_inv(double y_real,double y_imag,double *z_real,double *z_imag) {

  double inv_mag_sq;
#ifdef ENABLE_NR
  double x,y;
#endif

#ifndef ENABLE_NR
  inv_mag_sq=1/(y_real*y_real+y_imag*y_imag);
#else
  x=y_real*y_real+y_imag*y_imag;
  y=_rcpdp(x);
  y=y*(2.0-x*y);
  y=y*(2.0-x*y);
  y=y*(2.0-x*y);
  inv_mag_sq=y;
#endif
  *z_real= y_real*inv_mag_sq;
  *z_imag=-y_imag*inv_mag_sq;

}

static void complex_dp_div(double x_real,double x_imag,double y_real,double y_imag,double *z_real,double *z_imag) {

  double inv_mag_sq;
#ifdef ENABLE_NR
  double x,y;
#endif

#ifndef ENABLE_NR
  inv_mag_sq=1/(y_real*y_real+y_imag*y_imag);
#else
  x=y_real*y_real+y_imag*y_imag;
  y=_rcpdp(x);
  y=y*(2.0-x*y);
  y=y*(2.0-x*y);
  y=y*(2.0-x*y);
  inv_mag_sq=y;
#endif
  *z_real=(x_real*y_real+x_imag*y_imag)*inv_mag_sq;
  *z_imag=(x_imag*y_real-x_real*y_imag)*inv_mag_sq;

}

/* ======================================================================= */
/*  End of file:  DSPF_dp_qrd_cn.c                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
