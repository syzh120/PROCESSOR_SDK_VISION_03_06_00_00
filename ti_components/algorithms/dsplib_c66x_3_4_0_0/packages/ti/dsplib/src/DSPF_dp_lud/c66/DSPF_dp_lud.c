/* ======================================================================= */
/* DSPF_dp_lud.c -- lower/upper decomposition                              */
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

#pragma CODE_SECTION(DSPF_dp_lud, ".text:optimized");

#include "DSPF_dp_lud.h"

int DSPF_dp_lud(const int order, double *restrict A, double *restrict L,double *restrict U,unsigned short *restrict P)
{
  int row,col;
  int min_row,max_row,k,temp;
  double min,max,tmp;
  double x,y;

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
  memcpy(U,A, sizeof(double)*order*order);
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
	y=_rcpdp(x);
	y=y*(2.0-x*y);
	y=y*(2.0-x*y);
	y=y*(2.0-x*y);
#pragma MUST_ITERATE(1,,)
    for (row=k+1;row<order;row++) {
	  U[k+row*order]*=y;
    }
#pragma MUST_ITERATE(1,,)
    for (row=k+1;row<order;row++) {
#pragma MUST_ITERATE(1,,)
      for (col=k+1;col<order;col++) {
     	U[col+row*order]-=U[k+row*order]*U[col+k*order];
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

/* ======================================================================= */
/*  End of file:  DSPF_dp_lud.c                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
