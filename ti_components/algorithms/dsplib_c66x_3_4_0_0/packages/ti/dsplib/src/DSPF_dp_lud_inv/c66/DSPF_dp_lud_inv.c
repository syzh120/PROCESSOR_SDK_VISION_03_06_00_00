/* ======================================================================= */
/* DSPF_dp_lud_inv.c -- matrix inversion by LUD                            */
/*                 optimized C Implementation                              */
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

#pragma CODE_SECTION(DSPF_dp_lud_inverse, ".text:optimized");

#include "DSPF_dp_lud_inv.h"

int DSPF_dp_lud_inverse(const int order,unsigned short *restrict P,
                   double *restrict L,double *restrict U,double *restrict inv_A) 
{
  int row,col,k;
  double factor,sum;
  double *inv_L,*inv_U,*inv_U_x_inv_L;
  double x,y;

  _nassert(order>0);
  _nassert((int)P % 2 == 0);
  _nassert((int)L % 8 == 0);
  _nassert((int)U % 8 == 0);
  _nassert((int)inv_A % 8 == 0);

  /* set inv_A matrix to identity */
  inv_L=&inv_A[0];
  memset(inv_L,0.0,sizeof(double)*order*order);
#pragma MUST_ITERATE(1,,)
  for (row=0;row<order;row++) {
	inv_L[row+row*order]=1.0;
  }

  /* use Gauss Jordan algorithm to invert L whose result is in inv_L */
#pragma MUST_ITERATE(1,,)
  for (col=0;col<order-1;col++) {
	x=L[col+col*order];
	y=_rcpdp(x);
	y=y*(2.0-x*y);
	y=y*(2.0-x*y);
	y=y*(2.0-x*y);
#pragma MUST_ITERATE(1,,)
    for (row=col+1;row<order;row++) {
	  factor=L[col+row*order]*y;
#pragma MUST_ITERATE(1,,)
	  for (k=0;k<row;k++) {
		inv_L[k+row*order]-= factor*inv_L[k+col*order];
	  }
	}
  }

  /* set inv_U matrix to identity */
  inv_U=&L[0];
  memset(inv_U,0.0,sizeof(double)*order*order);
#pragma MUST_ITERATE(1,,)
  for (row=0;row<order;row++) {
	inv_U[row+row*order]=1.0;
  }

  /* use Gauss Jordan algorithm to invert U whose result is in L */
#pragma MUST_ITERATE(1,,)
  for (col=order-1;col>=1;col--) {
#pragma MUST_ITERATE(1,,)
	for (row=col-1;row>=0;row--) {
	  x=U[col+col*order];
	  y=_rcpdp(x);
	  y=y*(2.0-x*y);
	  y=y*(2.0-x*y);
	  y=y*(2.0-x*y);
	  factor=U[col+row*order]*y;
#pragma MUST_ITERATE(1,,)
	  for (k=col;k<order;k++) {
		inv_U[k+row*order] -= factor*inv_U[k+col*order];
		U[k+row*order]     -= factor*U[k+col*order];
	  }
	}
  }

  /* scale U & L to get identity matrix in U */
#pragma MUST_ITERATE(1,,)
  for (row=order-1;row>=0;row--) {
	//factor=U[row+row*order];
	x=U[row+row*order];
	y=_rcpdp(x);
	y=y*(2.0-x*y);
	y=y*(2.0-x*y);
	y=y*(2.0-x*y);
	factor=y;
#pragma MUST_ITERATE(1,,)
	for (col=0;col<order;col++) {
	  //L[col+row*order] /= factor;
		L[col+row*order] *= factor;
	}
  }

  /* compute inv_U_x_inv_L=inv(U)*inv(L) */
  inv_U_x_inv_L=&L[0];
#pragma MUST_ITERATE(1,,)
  for (row=0;row<order;row++) {
#pragma MUST_ITERATE(1,,)
    for (col=0;col<order;col++) {
    sum=0;
#pragma MUST_ITERATE(1,,)
  	  for (k=0;k<order;k++) {
        sum+=inv_U[k+row*order]*inv_L[col+k*order];
  	  }
      inv_U_x_inv_L[col+row*order]=sum;
    }
  }
  /* compute inv_A=inv(U)*inv(L)*P */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<order;row++) {
#pragma MUST_ITERATE(1,,)
    for (col=0;col<order;col++) {
    sum=0;
#pragma MUST_ITERATE(1,,)
  	for (k=0;k<order;k++) {
        sum+=inv_U_x_inv_L[k+row*order]*P[col+k*order];
  	}
    inv_A[col+row*order]=sum;
    }
  }

  return 0;
}



/* ======================================================================= */
/*  End of file:  DSPF_dp_lud_inv.c                                            */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
