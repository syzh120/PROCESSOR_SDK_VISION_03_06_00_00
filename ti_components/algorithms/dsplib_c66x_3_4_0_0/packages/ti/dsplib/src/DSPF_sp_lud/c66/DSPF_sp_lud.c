/* ======================================================================= */
/* DSPF_sp_lud.c -- lower/upper decomposition                              */
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

#pragma CODE_SECTION(DSPF_sp_lud, ".text:optimized");

#include "DSPF_sp_lud.h"

int DSPF_sp_lud(const int order, float *restrict A, float *restrict L,float *restrict U,unsigned short *restrict P)
{
  int row,col,delta;
  int min_row,max_row,k,temp;
  float min,max,tmp;
  float x,y;

  _nassert(order>0);
  _nassert((int)A % 8 == 0);
  _nassert((int)L % 8 == 0);
  _nassert((int)U % 8 == 0);
  _nassert((int)P % 2 == 0);

  /* ------------------------------------------------------------------- */
  /* generate identify matrix                                            */
  /* ------------------------------------------------------------------- */
  memset(P,0,sizeof(unsigned short)*order*order);
#pragma MUST_ITERATE(1,,)
  for (row=0;row<order;row++) {
	P[row+row*order]=1;
  }

  /* ------------------------------------------------------------------- */
  /* LU decomposition                                                    */
  /* ------------------------------------------------------------------- */
  memcpy(U,A, sizeof(float)*order*order);
#pragma MUST_ITERATE(1,,)
  for (k=0;k<order-1;k++) {

    /* find min and max entries in column */
    max=0.0;
    min=3.4e+38;
#pragma MUST_ITERATE(1,,)
    for (row=k;row<order;row++) {
   	  if (fabs(U[k+row*order])>max) {
    	max=fabs(U[k+row*order]);
    	max_row=row;
      }
      if (fabs(U[k+row*order])<min) {
        min=fabs(U[k+row*order]);
        min_row=row;
      }
    }

    /* swap rows if necessary */
    if (k!=max_row) {
#pragma MUST_ITERATE(1,,)
      for (col=0;col<order;col++) {
    	tmp=U[col+min_row*order];
    	U[col+min_row*order]=U[col+max_row*order];
    	U[col+max_row*order]=tmp;
    	temp=P[col+min_row*order];
    	P[col+min_row*order]=P[col+max_row*order];
    	P[col+max_row*order]=temp;
      }
    }

    /* generate U matrix */
    x=U[k+k*order];
	y=_rcpsp(x);
	y=y*(2.0-x*y);
	y=y*(2.0-x*y);
#pragma MUST_ITERATE(1,,)
   for (row=k+1;row<order;row++) {
	 U[k+row*order]*=y;
   }
#pragma MUST_ITERATE(1,,)
    for (row=k+1;row<order;row++) {
#pragma MUST_ITERATE(1,,)
      for (col=k+1;col<order;col+=2) {
        delta=1;
        if (col==(order-1)) delta=0;
    	tmp=U[col+row*order]-U[k+row*order]*U[col+k*order];
    	U[col+delta+row*order]-=U[k+row*order]*U[col+delta+k*order];
    	U[col+row*order]=tmp;
      }
    }
  }

    /* extract lower triangular entries from L into U and set L lower entries to zero */
#pragma MUST_ITERATE(1,,)
    for (row=0;row<order;row++) {
#pragma MUST_ITERATE(1,,)
      for (col=0;col<order;col++) {
        if (row<col) {
          L[col+row*order]=0;
        } else {
          if (row==col) {
        	L[col+row*order]=1;
          } else {
        	L[col+row*order]=U[col+row*order];
        	U[col+row*order]=0;
          }
        }
      }
    }

  return 0;
}

int DSPF_sp_lud_solver(const int order,unsigned short *restrict P,float *restrict L,float *restrict U,float *restrict b,float *restrict b_mod,float *restrict y,float *restrict x) {

  short row,col;
  float sum;
  float xx,yy;

  _nassert(order>0);
  _nassert((int)P % 2 == 0);
  _nassert((int)L % 8 == 0);
  _nassert((int)U % 8 == 0);
  _nassert((int)b % 8 == 0);
  _nassert((int)b_mod % 8 == 0);
  _nassert((int)y % 8 == 0);
  _nassert((int)x % 8 == 0);

  /* modify b based on permutation matrix P */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<order;row++) {
	sum=0;
#pragma MUST_ITERATE(1,,)
	for (col=0;col<order;col++) {
	  sum+=P[col+row*order]*b[col];
	}
	b_mod[row]=sum;
  }

  /* solve L*y=b for y using forward substitution */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<order;row++) {
	xx=L[row*order+row];
  	yy=_rcpsp(xx);
  	yy=yy*(2.0-xx*yy);
  	yy=yy*(2.0-xx*yy);
    if (row==0) {
      y[row]=b_mod[row]*yy;
	} else {
	  sum=0.0;
	  for (col=0;col<=row-1;col++) sum+=L[row*order+col]*y[col];
  	  y[row]=(b_mod[row]-sum)*yy;
	}
  }

  /* solve U*x=y for x using backward substitution */
#pragma MUST_ITERATE(1,,)
  for (row=order-1;row>=0;row--) {
    xx=U[row*order+row];
  	yy=_rcpsp(xx);
  	yy=yy*(2.0-xx*yy);
  	yy=yy*(2.0-xx*yy);
	if (row==order-1) {
      x[row]=y[row]*yy;
	} else {
	  sum=0.0;
	  for (col=order-1;col>=row+1;col--) sum+=U[row*order+col]*x[col];
  	  x[row]=(y[row]-sum)*yy;
	}
  }

  return 0;
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_lud.c                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
