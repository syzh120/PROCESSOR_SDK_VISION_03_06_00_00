/* ======================================================================= */
/* DSPF_sp_cholesky.c -- Cholesky decompostion and sovler                  */
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

#pragma CODE_SECTION(DSPF_sp_cholesky, ".text:optimized");

#include "DSPF_sp_cholesky.h"

//#define ENABLE_ORIG_IN_PLACE 1 /* enables original in place algorithm */

int DSPF_sp_cholesky(int enable_test, const int order, float *restrict A, float *restrict L)
{
  short i,j,k,n;
  float sum,sum1,sum2;
  float x,y;
  short delta;
  float *A1,*A2;
  int orderdiv2;

  _nassert(order>0);
  _nassert((int)A % 4 == 0);
  _nassert((int)L % 4 == 0);

  if (enable_test) {
    /* test A for positive definite matrix:    */
    /* z_transpose*A*z>0 where z=1,2,...order  */
    orderdiv2=order>>1;
	sum=0;
    for (n=0,i=0;n<orderdiv2;n++,i+=2) {
	  sum1=0;
	  sum2=0;
	  A1=&A[i*order];
	  A2=&A[(i+1)*order];
#pragma MUST_ITERATE(1,,)
	  for (j=0;j<order;j++) {
  	    sum1+=A1[j]*(float)(j+1);
  	    sum2+=A2[j]*(float)(j+1);
	  }
	  sum+=(float)(i+1)*sum1+(float)(i+2)*sum2;
    }
    /* if order odd process last row */
    if (1&order) {
      sum1=0;
      for (j=0;j<order;j++) {
    	sum1+=A[(order-1)*order+j]*(float)(j+1);
      }
      sum+=(float)(order)*sum1;
    }
    if (sum<=0) {
	  return -1;
    }
  }

  /* generate lower diagonal matrix L */
#pragma MUST_ITERATE(1,,)
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
	L[j*order+j]=x*y;

	for (i=j+1;i<order;i+=2) {
	  sum=0.0;
	  sum1=0.0;
	  delta=1;
	  if (i==order) {
		delta=0;
	  }
	  for (k=0;k<=j-1;k++) {
	  	sum+=L[i*order+k]*L[j*order+k];
	  	sum1+=L[(i+delta)*order+k]*L[j*order+k];
	  }
	  L[i*order+j]=(A[i*order+j]-sum)*y;
	  L[(i+delta)*order+j]=(A[(i+delta)*order+j]-sum1)*y;
	}
  }

  return 0;
}

int DSPF_sp_cholesky_in_place(const int enable_test, const int order, float *restrict A)
{
  short i,j,k,n;
  float sum,sum1,sum2;
  float x,y;
  float tmp;
  short delta;
  int orderdiv2;
  float *A1,*A2;
#ifndef ENABLE_ORIG_IN_PLACE
  float tmp1;
#endif

  _nassert(order>0);
  _nassert((int)A % 4 == 0);

  if (enable_test) {

    /* test A for positive definite matrix:    */
    /* z_transpose*A*z>0 where z=1,2,...order  */
	orderdiv2=order>>1;
	sum=0;
    for (n=0,i=0;n<orderdiv2;n++,i+=2) {
	  sum1=0;
	  sum2=0;
	  A1=&A[i*order];
	  A2=&A[(i+1)*order];
#pragma MUST_ITERATE(1,,)
	  for (j=0;j<order;j++) {
  	    sum1+=A1[j]*(float)(j+1);
  	    sum2+=A2[j]*(float)(j+1);
	  }
	  sum+=(float)(i+1)*sum1+(float)(i+2)*sum2;
    }
    /* if order odd process last row */
    if (1&order) {
      sum1=0;
      for (j=0;j<order;j++) {
    	sum1+=A[(order-1)*order+j]*(float)(j+1);
      }
      sum+=(float)(order)*sum1;
    }
    if (sum<=0) {
	  return -1;
    }
  }

  /* cholesky outer product version from p 145 Matrix Computations by Golub and Loan */

#ifdef ENABLE_ORIG_IN_PLACE

#pragma MUST_ITERATE(1,,)
  for (k=0;k<order;k++) {
	x=A[k*(order+1)];
	y=_rsqrsp(x);
    y=0.5*y*(3.0-x*y*y);
    y=0.5*y*(3.0-x*y*y);
    A[k*(order+1)]*=y;
    for (i=k+1;i<order;i+=2) {
      delta=1;
      if (i==order) delta=0;
      tmp=A[i*order+k]*y;
      A[(i+delta)*order+k]*=y;
      A[i*order+k]=tmp;
	}
	for (j=k+1;j<order;j++) {
#pragma MUST_ITERATE(1,,)
      for (i=j;i<order;i+=2) {
    	delta=1;
    	if (i==order) delta=0;
    	tmp=A[i*order+j]-A[i*order+k]*A[j*order+k];
    	A[(i+delta)*order+j]-=A[(i+delta)*order+k]*A[j*order+k];
    	A[i*order+j]=tmp;
      }
    }
  }

#else

  /* slight mod from Ran Katzur */
#pragma MUST_ITERATE(1,,)
  for (k=0;k<order;k++) {
	  x=A[k*order+k];
	  y=_rsqrsp(x);
      y=0.5*y*(3.0-x*y*y);
      y=0.5*y*(3.0-x*y*y);
      A[k*order+k]*=y;
	  
      for (i=k+1;i<order;i+=2) {
      delta=1;
      if (i==order) delta=0;
      tmp=A[i*order+k]*y;
      A[(i+delta)*order+k]*=y;
      A[i*order+k]=tmp;
	  
	  for (j=k+1;j<=i;j++) {
		tmp=A[i*order+j]-A[i*order+k]*A[j*order+k];
		tmp1=A[(i+delta)*order+j+delta];
		A[(i+delta)*order+j]-=A[(i+delta)*order+k]*A[j*order+k];
		A[i*order+j]=tmp;
      }
	  A[(i+delta)*order+j-1+delta]=tmp1-A[(i+delta)*order+k]*A[(j-1+delta)*order+k];
    }
  }

#endif

  return 0;
}

int DSPF_sp_cholesky_solver(const int order,float *restrict L,float *restrict y,float *restrict b,float *restrict x)
{
  short i,k;
  float sum;
  float xx,yy;

  _nassert(order>0);
  _nassert((int)L % 4 == 0);
  _nassert((int)b % 4 == 0);
  _nassert((int)x % 4 == 0);

  /* solve L*y=b for y using forward substitution */
#pragma MUST_ITERATE(1,,)
  for (i=0;i<order;i++) {
    if (i==0) {
      xx=L[0];
      yy=_rcpsp(xx);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      y[i]=b[i]*yy;
	} else {
	  sum=0.0;
	  for (k=0;k<=i-1;k++) {
		sum+=L[i*order+k]*y[k];
	  }
	  xx=L[i*order+i];
	  yy=_rcpsp(xx);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
	  y[i]=(b[i]-sum)*yy;
	}
  }

  /* solve U*x=y for x using backward substitution */
  for (i=order-1;i>=0;i--) {
	if (i==order-1) {
	  xx=L[i*order+i];
	  yy=_rcpsp(xx);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      x[i]=y[i]*yy;
	} else {
	  sum=0.0;
	  for (k=order-1;k>=i+1;k--) {
		sum+=L[k*order+i]*x[k];
	  }
	  xx=L[i*order+i];
	  yy=_rcpsp(xx);
      yy=yy*(2.0-xx*yy);
      yy=yy*(2.0-xx*yy);
      x[i]=(y[i]-sum)*yy;
	}
  }

  return 0;
}
/* ======================================================================= */
/*  End of file:  DSPF_sp_cholesky.c                                       */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
