/* ======================================================================= */
/* DSPF_dp_cholesky_cmplx.c -- Cholesky decompostion and solver            */
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

#pragma CODE_SECTION(DSPF_dp_cholesky_cmplx, ".text:optimized");

#include "DSPF_dp_cholesky_cmplx.h"

#define ENABLE_MATHLIB 1
#define ENABLE_NR 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2dp/c66/atan2dp.h>
#include <ti/mathlib/src/cosdp/c66/cosdp.h>
#include <ti/mathlib/src/sindp/c66/sindp.h>
#endif

static void complex_dp_div(double x_real,double x_imag,double y_real,double y_imag,double *z_real,double *z_imag);
static void complex_dp_inv_sqrt(double x_real,double x_imag,double *z_real,double *z_imag);

int DSPF_dp_cholesky_cmplx(int enable_test, const int Nrows, double *restrict A, double *restrict L)
{
  short i,j,j2,k,Ncols;
  double sum_real,sum_imag,sum1_real,sum1_imag;
  double xreal,ximag,yreal,yimag,zreal,zimag;

  _nassert(Nrows>0);
  _nassert((int)A % 8 == 0);
  _nassert((int)L % 8 == 0);

  Ncols=2*Nrows;
  if (enable_test) {
    /* test A for positive definite matrix:    */
    /* z_transpose*A*z>0 where z=1,2,...Nrows  */
	sum1_real=0;
	sum1_imag=0;
#pragma MUST_ITERATE(1,,)
    for (i=0;i<Nrows;i++) {
	  sum_real=0;
	  sum_imag=0;
#pragma MUST_ITERATE(1,,)
	  for (j=0;j<Nrows;j++) {
		xreal=A[i*Ncols+2*j  ];
		ximag=A[i*Ncols+2*j+1];
		yreal=(double)(j+1);
		sum_real+=xreal*yreal;
		sum_imag+=ximag*yreal;
	  }
      sum1_real+=(double)(i+1)*sum_real;
      sum1_imag+=(double)(i+1)*sum_imag;
    }
    if (sum1_real<=0) {
	  return -1;
    }
  }


  /* generate lower diagonal matrix L */
#pragma MUST_ITERATE(1,,)
  for (j=0;j<Nrows;j++) {
	j2=2*j;
	/* diagonal entry */
	sum_real=0;
	sum_imag=0;
	for (k=0;k<=j2-1;k+=2) {
	  xreal=L[j*Ncols+k  ];
	  ximag=L[j*Ncols+k+1];
	  sum_real+=xreal*xreal+ximag*ximag;
	  sum_imag+=0;
	}
	xreal=A[j*Ncols+j2  ]-sum_real;
	ximag=A[j*Ncols+j2+1]-sum_imag;
	complex_dp_inv_sqrt(xreal,ximag,&zreal,&zimag);
	yreal=zreal;
	yimag=zimag;
	L[j*Ncols+j2  ]=xreal*yreal-ximag*yimag;
	L[j*Ncols+j2+1]=xreal*yimag+ximag*yreal;

	
    for (i=j+1;i<Nrows;i++) {
      /* lower triangular entries */
      sum_real=0;
      sum_imag=0;
      for (k=0;k<=j2-1;k+=2) {
    	xreal= L[i*Ncols+k  ];
    	ximag= L[i*Ncols+k+1];
    	yreal= L[j*Ncols+k  ];
    	yimag=-L[j*Ncols+k+1];
    	sum_real+=xreal*yreal-ximag*yimag;
    	sum_imag+=xreal*yimag+ximag*yreal;
      }
      xreal=A[i*Ncols+j2  ]-sum_real;
      ximag=A[i*Ncols+j2+1]-sum_imag;
      yreal=zreal;
      yimag=zimag;
      L[i*Ncols+j2  ]=xreal*yreal-ximag*yimag;
      L[i*Ncols+j2+1]=xreal*yimag+ximag*yreal;
	}
  }

  return 0;
}

int DSPF_dp_cholesky_in_place_cmplx(const int enable_test, const int Nrows, double *restrict A)
{
  short i,j,k,Ncols;
  double xreal,ximag,yreal,yimag,zreal,zimag;
  double sum_real,sum_imag,sum1_real,sum1_imag;

  _nassert(Nrows>0);
  _nassert((int)A % 8 == 0);

  Ncols=2*Nrows;
  if (enable_test) {
    /* test A for positive definite matrix:    */
    /* z_transpose*A*z>0 where z=1,2,...Nrows  */
	sum1_real=0;
	sum1_imag=0;
#pragma MUST_ITERATE(1,,)
    for (i=0;i<Nrows;i++) {
	  sum_real=0;
	  sum_imag=0;
#pragma MUST_ITERATE(1,,)
	  for (j=0;j<Nrows;j++) {
		xreal=A[i*Ncols+2*j  ];
		ximag=A[i*Ncols+2*j+1];
		yreal=(double)(j+1);
		sum_real+=xreal*yreal;
		sum_imag+=ximag*yreal;
	  }
      sum1_real+=(double)(i+1)*sum_real;
      sum1_imag+=(double)(i+1)*sum_imag;
    }
    if (sum1_real<=0) {
	  return -1;
    }
  }

  /* cholesky outer product version from p 145 Matrix Computations by Golub and Loan */
  /* use Newton Raphson iteration for y=1/sqrt(x) */
  /*   y[n+1]=y[n]*(3-x*y[n]*y[n])/2              */
  for (k=0;k<Nrows;k++) {
	  xreal=A[k*Ncols+2*k  ];
	  ximag=A[k*Ncols+2*k+1];
	  complex_dp_inv_sqrt(xreal,ximag,&zreal,&zimag);
	  A[k*Ncols+2*k  ]=xreal*zreal-ximag*zimag;
	  A[k*Ncols+2*k+1]=xreal*zimag+ximag*zreal;

	for (i=k+1;i<Nrows;i++) {
	  xreal=A[i*Ncols+2*k  ];
	  ximag=A[i*Ncols+2*k+1];
	  A[i*Ncols+2*k  ]=xreal*zreal-ximag*zimag;
	  A[i*Ncols+2*k+1]=xreal*zimag+ximag*zreal;
	}
	for (j=k+1;j<Nrows;j++) {
#pragma MUST_ITERATE(1,,)
      for (i=j;i<Nrows;i++) {
    	xreal= A[i*Ncols+2*k  ];
    	ximag= A[i*Ncols+2*k+1];
    	yreal= A[j*Ncols+2*k  ];
    	yimag=-A[j*Ncols+2*k+1];
    	A[i*Ncols+2*j  ]-=xreal*yreal-ximag*yimag;
    	A[i*Ncols+2*j+1]-=xreal*yimag+ximag*yreal;
      }
    }
  }

  return 0;
}

int DSPF_dp_cholesky_solver_cmplx(const int Nrows,double *restrict L,double *restrict y,double *restrict b,double *restrict x)
{
  short i,k,Ncols;
  double sum_real,sum_imag,xreal,ximag,yreal,yimag,zreal,zimag;

  _nassert(Nrows>0);
  _nassert((int)L % 8 == 0);
  _nassert((int)b % 8 == 0);
  _nassert((int)x % 8 == 0);

  /* solve L*y=b for y using forward substitution */
  Ncols=2*Nrows;
  for (i=0;i<Nrows;i++) {
    if (i==0) {
	  xreal=b[2*i  ];
	  ximag=b[2*i+1];
	  yreal=L[0];
      yimag=L[1];
      complex_dp_div(xreal,ximag,yreal,yimag,&zreal,&zimag);
      y[2*i  ]=zreal;
      y[2*i+1]=zimag;
	} else {
	  sum_real=0;
	  sum_imag=0;
	  for (k=0;k<=i-1;k++) {
		xreal=L[i*Ncols+2*k  ];
		ximag=L[i*Ncols+2*k+1];
		yreal=y[2*k  ];
		yimag=y[2*k+1];
		sum_real+=xreal*yreal-ximag*yimag;
		sum_imag+=xreal*yimag+ximag*yreal;
	  }
	  xreal=b[2*i  ]-sum_real;
	  ximag=b[2*i+1]-sum_imag;
	  yreal=L[i*Ncols+2*i  ];
	  yimag=L[i*Ncols+2*i+1];
	  complex_dp_div(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  y[2*i  ]=zreal;
	  y[2*i+1]=zimag;
	}
  }

  /* solve U*x=y for x using backward substitution */
  for (i=Nrows-1;i>=0;i--) {
	if (i==Nrows-1) {
	  xreal=y[2*i  ];
	  ximag=y[2*i+1];
	  yreal=L[i*Ncols+2*i  ];
	  yimag=-L[i*Ncols+2*i+1];
	  complex_dp_div(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  x[2*i  ]=zreal;
	  x[2*i+1]=zimag;
	} else {
	  sum_real=0;
	  sum_imag=0;
	  for (k=Nrows-1;k>=i+1;k--) {
		xreal=L[k*Ncols+2*i  ];
		ximag=-L[k*Ncols+2*i+1];
		yreal=x[2*k  ];
		yimag=x[2*k+1];
		sum_real+=xreal*yreal-ximag*yimag;
		sum_imag+=xreal*yimag+ximag*yreal;
	  }
	  xreal=y[2*i  ]-sum_real;
	  ximag=y[2*i+1]-sum_imag;
	  yreal=L[i*Ncols+2*i  ];
	  yimag=-L[i*Ncols+2*i+1];
	  complex_dp_div(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  x[2*i  ]=zreal;
	  x[2*i+1]=zimag;
	}
  }

  return 0;
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

static void complex_dp_inv_sqrt(double x_real,double x_imag,double *z_real,double *z_imag) {

  double x_mag,z_mag;
  double x_angle,z_angle;
#ifdef ENABLE_NR
  double x,y;
#endif

  /* magnitude */
  x_mag=sqrt(x_real*x_real+x_imag*x_imag);
#ifndef ENABLE_NR
  z_mag=1/sqrt(x_mag);
#else
  x=x_mag;
  y=_rsqrdp(x);

  y=0.5*y*(3.0-x*y*y);
  y=0.5*y*(3.0-x*y*y);
  y=0.5*y*(3.0-x*y*y);
  z_mag=y;
#endif

  /* angle */
#ifndef ENABLE_MATHLIB
  x_angle=atan2(x_imag,x_real);
#else
  x_angle=atan2dp(x_imag,x_real);
#endif
  z_angle=-x_angle*0.5;

  /* results */
#ifndef ENABLE_MATHLIB
  *z_real=cos(z_angle)*z_mag;
  *z_imag=sin(z_angle)*z_mag;
#else
  *z_real=cosdp(z_angle)*z_mag;
  *z_imag=sindp(z_angle)*z_mag;
#endif

}

/* ======================================================================= */
/*  End of file:  DSPF_dp_cholesky_cmplx.c                                 */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
