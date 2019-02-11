/* ======================================================================= */
/* DSPF_sp_qrd.c -- QR decomposition single precision                      */
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
/* ======================================================================= */\
#include <math.h>
#include <string.h>

#pragma CODE_SECTION(DSPF_sp_qrd, ".text:optimized");

#include "DSPF_sp_qrd.h"

#define ENABLE_NR 1

int DSPF_sp_qrd(const int Nrows,const int Ncols, float *restrict A, float *restrict Q,float *restrict R,float *restrict u)
{
  int row,col,i,k,loop_count;
  float alpha,scale,sum,norm_sqr;
  float x,y;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)A % 8 == 0);
  _nassert((int)Q % 8 == 0);
  _nassert((int)R % 8 == 0);
  _nassert((int)u % 8 == 0);

  /* ------------------------------------------------------------------- */
   /* generate identify matrix and copy A to R                            */
   /* ------------------------------------------------------------------- */
   memcpy(R,A,sizeof(float)*Nrows*Ncols);
   memset(Q,0.0,sizeof(float)*Nrows*Nrows);
   for (row=0;row<Nrows;row++) {
 	 Q[row+row*Nrows] = 1.0;
   }

  if (Nrows<=Ncols) {
	loop_count=Nrows-2;
  } else {
	loop_count=Ncols-1;
  }
  for (col=0;col<=loop_count;col++) {
    sum=0;
#pragma MUST_ITERATE(1,,)
    for (row=col;row<Nrows;row++) {
      sum+=R[col+row*Ncols]*R[col+row*Ncols];
    }
    if (sum!=0) {
      alpha=sqrt(sum);
      if (R[col+col*Ncols]>=0) {
    	alpha=-alpha;
      }
      u[col]=R[col+col*Ncols]+alpha;
      R[col+col*Ncols]=-alpha;
      norm_sqr=u[col]*u[col];
#pragma MUST_ITERATE(1,,)
      for (row=col+1;row<Nrows;row++) {
    	u[row]=R[col+row*Ncols];
    	R[col+row*Ncols]=0;
    	norm_sqr+=u[row]*u[row];
      }
    //if (norm_sqr!=0) {
      if (alpha*u[col]!=0) {
#ifndef ENABLE_NR
    	scale=1/(alpha*u[col]);
#else
    	x=alpha*u[col];
    	y=_rcpsp(x);
    	y=y*(2.0-x*y);
    	y=y*(2.0-x*y);
    	scale=y;
#endif
    	/* R=Q1*R */
    	for (i=col+1;i<Ncols;i++) {
          sum=0;
#pragma MUST_ITERATE(1,,)
          for (k=col;k<Nrows;k++) {
        	sum+=u[k]*R[i+k*Ncols];
          }
         sum*=scale;
#pragma MUST_ITERATE(1,,)
          for (k=col;k<Nrows;k++) {
        	R[i+k*Ncols]-=u[k]*sum;
          }
    	}
      	/* Q=A*Q1 */
    	for (i=0;i<Nrows;i++) {
    	  sum=0;
#pragma MUST_ITERATE(1,,)
    	  for (k=col;k<Nrows;k++) {
    		sum+=u[k]*Q[k+i*Nrows];
    	  }
    	  sum*=scale;
#pragma MUST_ITERATE(1,,)
    	  for (k=col;k<Nrows;k++) {
    		Q[k+i*Nrows]-=u[k]*sum;
    	  }
    	}
      } /* if (norm_sqr!=0) */
    } /* if (sum!=0) */
  } /* for (col=0;col<=loop_count;col++) */

  return 0;
}

int DSPF_sp_qrd_solver(const int Nrows,const int Ncols,float *restrict Q,float *restrict R,float *restrict b,float *restrict y,float *restrict x) {

  short row,col,loop_cnt,delta;
  float sum,sum1;
  float xx,yy;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)Q % 8 == 0);
  _nassert((int)R % 8 == 0);
  _nassert((int)b % 8 == 0);
  _nassert((int)y % 8 == 0);
  _nassert((int)x % 8 == 0);

  /* generate y=Q'*b */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row+=2) {
	sum=0.0;
	sum1=0.0;
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Nrows;col++) {
	  sum +=Q[row+col*Nrows]*b[col];
	  sum1+=Q[row+delta+col*Nrows]*b[col];
	}
	y[row]=sum;
	y[row+delta]=sum1;
  }

  /* use backward substitution to solve x=inv(R)*y */
  if (Nrows>=Ncols) loop_cnt=Ncols;
  else              loop_cnt=Nrows;
  memset(x,0,sizeof(float)*Ncols);
#pragma MUST_ITERATE(1,,)
  for (row=loop_cnt-1;row>=0;row--) {
	sum=0.0;
#pragma MUST_ITERATE(1,,)
	for (col=row+1;col<loop_cnt;col++) {
	  sum+=R[col+row*Ncols]*x[col];
	}
	xx=R[row+row*Ncols];
	yy=_rcpsp(xx);
	yy=yy*(2.0-xx*yy);
	yy=yy*(2.0-xx*yy);
	x[row]=(y[row]-sum)*yy;
  }

  return 0;
}

int DSPF_sp_qrd_inverse(const int Nrows,const int Ncols,float *restrict Q,float *restrict R,float *restrict inv_A) {

  int row,col,k;
  float factor,sum;
  float x,y;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)Q % 8 == 0);
  _nassert((int)R % 8 == 0);
  _nassert((int)inv_A % 8 == 0);

  /* set inv_A matrix to identity */
  memset(inv_A,0.0,sizeof(float)*Nrows*Ncols);
  for (row=0;row<Nrows;row++) {
	inv_A[row+row*Ncols]=1.0;
  }

  /* use Gauss Jordan algorithm to invert R whose result will be in inv_A */
#pragma MUST_ITERATE(1,,)
  for (col=Ncols-1;col>=1;col--) {
	x=R[col+col*Ncols];
	y=_rcpsp(x);
	y=y*(2.0-x*y);
	y=y*(2.0-x*y);
#pragma MUST_ITERATE(1,,)
	for (row=col-1;row>=0;row--) {
      factor=R[col+row*Ncols]*y;
#pragma MUST_ITERATE(1,,)
	  for (k=0;k<Ncols;k++) {
		inv_A[k+row*Ncols] -= factor*inv_A[k+col*Ncols];
		R[k+row*Ncols]     -= factor*R[k+col*Ncols];
	  }
	}
  }

  /* scale R and inv_A to get identity matrix in R */
#pragma MUST_ITERATE(1,,)
  for (row=Nrows-1;row>=0;row--) {
	x=R[row+row*Ncols];
	y=_rcpsp(x);
	y=y*(2.0-x*y);
	y=y*(2.0-x*y);
	factor=y;
#pragma MUST_ITERATE(1,,)
	for (col=row;col<Ncols;col++) {
	  inv_A[col+row*Ncols] *= factor;
	}
  }

  /* inv_A = inv_R * Q' */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Ncols;col++) {
      sum=0.0;
#pragma MUST_ITERATE(1,,)
      for (k=0;k<Ncols;k++) {
    	sum+=inv_A[k+row*Ncols]*Q[k+col*Ncols];
      }
      R[col]=sum;
	}
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Ncols;col++) {
	  inv_A[col+row*Ncols]=R[col];
	}
  }

  return 0;
}



/* ======================================================================= */
/*  End of file:  DSPF_sp_qrd.c                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
