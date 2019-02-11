/* ======================================================================= */
/* DSPF_sp_lud_cmplx_cn.c -- lower/upper decomposition                     */
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
#include <string.h>

#include "DSPF_sp_lud_cmplx_cn.h"

static void complex_sp_div_cn(float x_real,float x_imag,float y_real,float y_imag,float *z_real,float *z_imag);

int DSPF_sp_lud_cmplx_cn(const int Nrows, float *A, float *L,float *U,unsigned short *P)
{
  int row,col,col2,Ncols;
  int min_row,max_row,k,temp;
  float mag,min,max,tmp_real,tmp_imag;
  float xreal,ximag,yreal,yimag,zreal,zimag;

  /* ------------------------------------------------------------------- */
  /* generate identify matrix                                            */
  /* ------------------------------------------------------------------- */
  for (row=0;row<Nrows;row++) {
	for (col=0;col<Nrows;col++) {
	  if (row==col) {
		P[col+row*Nrows] = 1;
	  } else {
		P[col+row*Nrows] = 0;
	  }
	}
  }

  /* ------------------------------------------------------------------- */
  /* LU decomposition                                                    */
  /* ------------------------------------------------------------------- */
  Ncols=2*Nrows;
  memcpy(U,A, sizeof(float)*Nrows*Ncols);
  for (k=0;k<Nrows-1;k++) {

    /* find min and max entries in column */
    max=0.0;
    min=3.4e+38;
    for (row=k;row<Nrows;row++) {
  	  mag=sqrt(U[2*k+row*Ncols]*U[2*k+row*Ncols]+U[2*k+1+row*Ncols]*U[2*k+1+row*Ncols]);
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
    for (row=k+1;row<Nrows;row++) {
  	  xreal=U[2*k  +row*Ncols];
  	  ximag=U[2*k+1+row*Ncols];
  	  yreal=U[2*k  +k*Ncols];
  	  yimag=U[2*k+1+k*Ncols];
  	  complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
  	  U[2*k  +row*Ncols]=zreal;
  	  U[2*k+1+row*Ncols]=zimag;
    }
    for (row=k+1;row<Nrows;row++) {
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
    for (row=0;row<Nrows;row++) {
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


void complex_sp_div_cn(float x_real,float x_imag,float y_real,float y_imag,float *z_real,float *z_imag) {

  float x_mag,y_mag,z_mag;
  float x_angle,y_angle,z_angle;

  /* magnitude */
  x_mag=sqrt(x_real*x_real+x_imag*x_imag);
  y_mag=sqrt(y_real*y_real+y_imag*y_imag);
  z_mag=x_mag/y_mag;

  /* angle */
  x_angle=atan2(x_imag,x_real);
  y_angle=atan2(y_imag,y_real);
  z_angle=x_angle-y_angle;

  /* results */
  *z_real=cos(z_angle)*z_mag;
  *z_imag=sin(z_angle)*z_mag;
}


/* ======================================================================= */
/*  End of file:  DSPF_sp_lud_cmplx_cn.c                                   */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
