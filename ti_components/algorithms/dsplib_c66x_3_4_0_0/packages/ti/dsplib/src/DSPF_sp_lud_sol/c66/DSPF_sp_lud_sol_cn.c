/* ======================================================================= */
/* DSPF_sp_lud_sol_cn.c -- linear solver by LUD                            */
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
/* ======================================================================= */
#include <math.h>
#include <string.h>

#include "DSPF_sp_lud_sol_cn.h"


int DSPF_sp_lud_solver_cn(const int order,unsigned short *P,float *L,float *U,
                          float *b,float *b_mod,float *y,float *x) {

  short row,col;
  float sum;

  /* modify b based on permutation matrix P */
  for (row=0;row<order;row++) {
	sum=0;
	for (col=0;col<order;col++) {
	  sum+=P[col+row*order]*b[col];
	}
	b_mod[row]=sum;
  }

  /* solve L*y=b for y using forward substitution */
  for (row=0;row<order;row++) {
    if (row==0) {
	  y[row]=b_mod[row]/L[0];
	} else {
	  sum=0.0;
	  for (col=0;col<=row-1;col++) sum+=L[row*order+col]*y[col];
	  y[row]=(b_mod[row]-sum)/L[row*order+row];
	}
  }

  /* solve U*x=y for x using backward substitution */
  for (row=order-1;row>=0;row--) {
	if (row==order-1) {
	  x[row]=y[row]/U[row*order+row];
	} else {
	  sum=0.0;
	  for (col=order-1;col>=row+1;col--) sum+=U[row*order+col]*x[col];
	  x[row]=(y[row]-sum)/U[row*order+row];
	}
  }

  return 0;
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_lud_cn_sol.c                                     */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
