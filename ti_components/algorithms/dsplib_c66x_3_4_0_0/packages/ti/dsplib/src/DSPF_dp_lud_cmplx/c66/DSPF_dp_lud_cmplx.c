/* ======================================================================= */
/* DSPF_dp_lud_cmplx.c -- lower/upper complex matrix decomposition         */
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

#pragma CODE_SECTION(DSPF_dp_lud_cmplx,".text:optimized");

#include "DSPF_dp_lud_cmplx.h"

#define ENABLE_NR 1
#define ENABLE_MATHLIB 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2dp/c66/atan2dp.h>
#include <ti/mathlib/src/cosdp/c66/cosdp.h>
#include <ti/mathlib/src/sindp/c66/sindp.h>
#endif

static void complex_dp_inv(double y_real,double y_imag,double *z_real,double *z_imag);

int DSPF_dp_lud_cmplx(const int Nrows, double *restrict A, double *restrict L,
                      double *restrict U,unsigned short *restrict P)
{
  int row,col,col2,Ncols;
  int min_row,max_row,k,temp;
  double mag,min,max,tmp_real,tmp_imag;
  double xreal,ximag,yreal,yimag,zreal,zimag;

  _nassert(Nrows>0);
  _nassert((int)A % 8 == 0);
  _nassert((int)L % 8 == 0);
  _nassert((int)U % 8 == 0);
  _nassert((int)P % 2 == 0);

  /* ------------------------------------------------------------------- */
  /* generate identify matrix                                            */
  /* ------------------------------------------------------------------- */
  memset(P,0,sizeof(unsigned short)*Nrows*Nrows);
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
	P[row+row*Nrows]=1;
  }

  /* ------------------------------------------------------------------- */
  /* LU decomposition                                                    */
  /* ------------------------------------------------------------------- */
  Ncols=2*Nrows;
  memcpy(U,A, sizeof(double)*Nrows*Ncols);
#pragma MUST_ITERATE(1,,)
  for (k=0;k<Nrows-1;k++) {

    /* find min and max entries in column */
    max=0.0;
    min=3.4e+38;
#pragma MUST_ITERATE(1,,)
    for (row=k;row<Nrows;row++) {
      mag=sqrt(U[2*k  +row*Ncols]*U[2*k  +row*Ncols]+U[2*k+1+row*Ncols]*U[2*k+1+row*Ncols]);
   	  if (mag>max) {
    	max=mag;
    	max_row=row;
      }
      if (mag<min) {
        min=mag;
        min_row=row;
      }
    }

    /* swap rows if necessary */
    if (k!=max_row) {
#pragma MUST_ITERATE(1,,)
      for (col=0;col<Nrows;col++) {
      	tmp_real=U[2*col  +min_row*Ncols];
      	tmp_imag=U[2*col+1+min_row*Ncols];
      	U[2*col  +min_row*Ncols]=U[2*col  +max_row*Ncols];
      	U[2*col+1+min_row*Ncols]=U[2*col+1+max_row*Ncols];
      	U[2*col  +max_row*Ncols]=tmp_real;
      	U[2*col+1+max_row*Ncols]=tmp_imag;
       	temp=P[col+min_row*Nrows];
    	P[col+min_row*Nrows]=P[col+max_row*Nrows];
    	P[col+max_row*Nrows]=temp;
      }
    }

    /* generate U matrix */
	yreal=U[2*k  +k*Ncols];
	yimag=U[2*k+1+k*Ncols];
	complex_dp_inv(yreal,yimag,&zreal,&zimag);
#pragma MUST_ITERATE(1,,)
    for (row=k+1;row<Nrows;row++) {
      xreal=U[2*k  +row*Ncols];
      ximag=U[2*k+1+row*Ncols];
      U[2*k  +row*Ncols]=xreal*zreal-ximag*zimag;
      U[2*k+1+row*Ncols]=xreal*zimag+ximag*zreal;
    }
#pragma MUST_ITERATE(1,,)
    for (row=k+1;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
      for (col=k+1;col<Nrows;col++) {
    	xreal=U[2*k  +row*Ncols];
    	ximag=U[2*k+1+row*Ncols];
    	yreal=U[2*col  +k*Ncols];
    	yimag=U[2*col+1+k*Ncols];
    	U[2*col  +row*Ncols]-=xreal*yreal-ximag*yimag;
    	U[2*col+1+row*Ncols]-=xreal*yimag+ximag*yreal;
      }
    }
  }

    /* extract lower triangular entries from L into U and set L lower entries to zero */
#pragma MUST_ITERATE(1,,)
    for (row=0;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
      for (col=0;col<Nrows;col++) {
      	col2=2*col;
        if (row<col) {
          L[col2  +row*Ncols]=0;
          L[col2+1+row*Ncols]=0;
        } else {
          if (row==col) {
            L[col2  +row*Ncols]=1;
            L[col2+1+row*Ncols]=0;
          } else {
          L[col2  +row*Ncols]=U[col2  +row*Ncols];
          L[col2+1+row*Ncols]=U[col2+1+row*Ncols];
          U[col2  +row*Ncols]=0;
          U[col2+1+row*Ncols]=0;
          }
        }
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

/* ======================================================================= */
/*  End of file:  DSPF_dp_lud_cmplx                                        */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
