/* ======================================================================= */
/* DSPF_dp_cholesky.c -- Cholesky decompostion and sovler                  */
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

#pragma CODE_SECTION(DSPF_dp_cholesky, ".text:optimized");

#include "DSPF_dp_cholesky.h"

#define ENABLE_ORIG_IN_PLACE 1 // enables original in place algorithm

int DSPF_dp_cholesky(int enable_test, const int order, double *restrict A, double *restrict L)
{
  short i,j,k;
  double sum,sum1;
  double x,y;

  _nassert(order>0);
  _nassert((int)A % 8 == 0);
  _nassert((int)L % 8 == 0);

  if (enable_test) {
    /* test A for positive definite matrix:    */
    /* z_transpose*A*z>0 where z=1,2,...order  */
	sum1=0;
    for (i=0;i<order;i++) {
	  sum=0;
	  for (j=0;j<order;j++) {
  	    sum+=A[i*order+j]*(double)(j+1);
	  }
      sum1+=(double)(i+1)*sum;
    }
    if (sum1<=0) {
	  return -1;
    }
  }

  /* generate lower diagonal matrix L */
  for (j=0;j<order;j++) {
	/* diagonal entry */
	sum=0.0;
	for (k=0;k<=j-1;k++) {
	  sum+=L[j*order+k]*L[j*order+k];
	}
 	x=A[j*order+j]-sum;
    y=_rsqrdp(x);
    y=0.5*y*(3.0-x*y*y);
    y=0.5*y*(3.0-x*y*y);
    y=0.5*y*(3.0-x*y*y);
	L[j*order+j]=x*y;

    for (i=j+1;i<order;i++) {
      /* lower triangular entries */
      sum=0.0;
      for (k=0;k<=j-1;k++) {
    	sum+=L[i*order+k]*L[j*order+k];
      }
      L[i*order+j]=(A[i*order+j]-sum)*y;
	}
  }

  return 0;
}

int DSPF_dp_cholesky_in_place(const int enable_test, const int order, double *restrict A)
{
  short i,j,k;
  double sum,sum1;
  double x,y;

  _nassert(order>0);
  _nassert((int)A % 8 == 0);

  if (enable_test) {
    /* test A for positive definite matrix:    */
    /* z_transpose*A*z>0 where z=1,2,...order  */
	sum1=0;
    for (i=0;i<order;i++) {
	  sum=0;
	  for (j=0;j<order;j++) {
  	    sum+=A[i*order+j]*(double)(j+1);
	  }
	  sum1+=(double)(i+1)*sum;
    }
    if (sum1<=0) {
	  return -1;
    }
  }

  /* cholesky outer product version from p 145 Matrix Computations by Golub and Loan */
  /* use Newton Raphson iteration for y=1/sqrt(x) */
  /*   y[n+1]=y[n]*(3-x*y[n]*y[n])/2              */

#if ENABLE_ORIG_IN_PLACE
  for (k=0;k<order;k++) {
	  x=A[k*(order+1)];
	  y=_rsqrdp(x);
      y=0.5*y*(3.0-x*y*y);
      y=0.5*y*(3.0-x*y*y);
      y=0.5*y*(3.0-x*y*y);
      A[k*(order+1)]*=y;
	for (i=k+1;i<order;i++) {
	  A[i*order+k]*=y;
	}
	for (j=k+1;j<order;j++) {
      for (i=j;i<order;i++) {
    	A[i*order+j]-=A[i*order+k]*A[j*order+k];
      }
    }
  }
#else

  /* slight mod from Ran Katzur */
  for (k=0;k<order;k++) {
	  x=A[k*(order+1)];
	  y=_rsqrdp(x);
      y=0.5*y*(3.0-x*y*y);
      y=0.5*y*(3.0-x*y*y);
      y=0.5*y*(3.0-x*y*y);
      A[k*(order+1)]*=y;
	for (i=k+1;i<order;i++) {
	  A[i*order+k]*=y;
	  for (j=k+1;j<=i;j++) {
    	A[i*order+j]-=A[i*order+k]*A[j*order+k];
      }
    }
  }
#endif

  return 0;
}

int DSPF_dp_cholesky_solver(const int order,double *restrict L,double *restrict y,double *restrict b,double *restrict x)
{
  short i,k;
  double sum;
  double xx,yy;

  _nassert(order>0);
  _nassert((int)L % 8 == 0);
  _nassert((int)b % 8 == 0);
  _nassert((int)x % 8 == 0);

  /* solve L*y=b for y using forward substitution */
  for (i=0;i<order;i++) {
    if (i==0) {
      xx=L[0];
      yy=_rcpdp(xx);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      y[i]=b[i]*yy;
	} else {
	  sum=0.0;
	  for (k=0;k<=i-1;k++) {
		sum+=L[i*order+k]*y[k];
	  }
	  xx=L[i*order+i];
      yy=_rcpdp(xx);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      y[i]=(b[i]-sum)*yy;
	}
  }

  /* solve U*x=y for x using backward substitution */
  for (i=order-1;i>=0;i--) {
	if (i==order-1) {
	//x[i]=y[i]/L[i*order+i];
	  xx=L[i*order+i];
      yy=_rcpdp(xx);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      x[i]=y[i]*yy;
	} else {
	  sum=0.0;
	  for (k=order-1;k>=i+1;k--) {
		sum+=L[k*order+i]*x[k];
	  }
	//x[i]=(y[i]-sum)/L[i*order+i];
	  xx=L[i*order+i];
      yy=_rcpdp(xx);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      x[i]=(y[i]-sum)*yy;
	}
  }

  return 0;
}
/* ======================================================================= */
/*  End of file:  DSPF_dp_cholesky.c                                       */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
