/* ======================================================================= */
/* DSPF_dp_cholesky_cn.c -- Cholesky decomposition and solver              */
/*                 Natural C Implementation                                */
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
/* ======================================================================= */\
#include <math.h>

#include "DSPF_dp_cholesky_cn.h"

#define ENABLE_ORIG_IN_PLACE 1 /* enables original in place algorithm */

int DSPF_dp_cholesky_cn(int enable_test, const int order, double *A, double *L)
{
  short i,j,k;
  double sum,sum1;

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
	L[j*order+j]=(double)sqrt(A[j*order+j]-sum);

    /* lower triangular entries */
    for (i=j+1;i<order;i++) {
      sum=0.0;
      for (k=0;k<=j-1;k++) {
    	sum+=L[i*order+k]*L[j*order+k];
      }
      L[i*order+j]=(A[i*order+j]-sum)/L[j*order+j];
 	}
  }

  return 0;
}

int DSPF_dp_cholesky_in_place_cn(const int enable_test, const int order, double *A)
{
  short i,j,k;
  double sum,sum1;

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

#if ENABLE_ORIG_IN_PLACE
  /* cholesky outer product version from p 145 Matrix Computations by Golub and Loan */
  for (k=0;k<order;k++) {
	A[k*order+k]=(double)sqrt(A[k*order+k]);
	for (i=k+1;i<order;i++) {
      A[i*order+k]=A[i*order+k]/A[k*order+k];
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
	A[k*order+k]=(double)sqrt(A[k*order+k]);
	for (i=k+1;i<order;i++) {
      A[i*order+k]=A[i*order+k]/A[k*order+k];
      for (j=k+1;j<=i;j++) {
    	A[i*order+j]-=A[i*order+k]*A[j*order+k];
      }
    }
  }
#endif

  return 0;
}


int DSPF_dp_cholesky_solver_cn(const int order,double *L,double *y,double *b,double *x)
{
  short i,k;
  double sum;

  /* solve L*y=b for y using forward substitution */
  for (i=0;i<order;i++) {
    if (i==0) {
	  y[i]=b[i]/L[0];
	} else {
	  sum=0.0;
	  for (k=0;k<=i-1;k++) sum+=L[i*order+k]*y[k];
	  y[i]=(b[i]-sum)/L[i*order+i];
	}
  }

  /* solve U*x=y for x using backward substitution */
  for (i=order-1;i>=0;i--) {
	if (i==order-1) {
	  x[i]=y[i]/L[i*order+i];
	} else {
	  sum=0.0;
	  for (k=order-1;k>=i+1;k--) sum+=L[k*order+i]*x[k];
	  x[i]=(y[i]-sum)/L[i*order+i];
	}
  }

  return 0;
}
/* ======================================================================= */
/*  End of file:  DSPF_dp_cholesky_cn.c                                    */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
