/* ======================================================================= */
/* DSPF_sp_lud_inv_cmplx_cn.c - C source interface header file for complex */
/*                            matrix inversion by LUD, single precision    */
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

#include "DSPF_sp_lud_inv_cmplx_cn.h"

static void complex_sp_div_cn(float x_real,float x_imag,float y_real,
                              float y_imag,float *z_real,float *z_imag);

int DSPF_sp_lud_inverse_cmplx_cn(const int Nrows,unsigned short *P,float *L,
                                 float *U,float *inv_A) {

  int row,col,Ncols,k;
  float factor_real,factor_imag,sum_real,sum_imag;
  float xreal,ximag,yreal,yimag,zreal,zimag;
  float *inv_L,*inv_U,*inv_U_x_inv_L;

  /* set inv_A matrix to identity */
  inv_L=&inv_A[0];
  Ncols=2*Nrows;
  memset(inv_L,0.0,sizeof(float)*Nrows*Ncols);
  for (row=0;row<Nrows;row++) {
	inv_L[2*row  +row*Ncols]=1;
  }

  /* use Gauss Jordan algorithm to invert L whose result is in inv_L */
  for (col=0;col<Nrows-1;col++) {
    for (row=col+1;row<Nrows;row++) {
      xreal=L[2*col  +row*Ncols];
      ximag=L[2*col+1+row*Ncols];
      yreal=L[2*col  +col*Ncols];
      yimag=L[2*col+1+col*Ncols];
      complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
      factor_real=zreal;
      factor_imag=zimag;
  	  for (k=0;k<Nrows;k++) {
  		xreal=factor_real;
  		ximag=factor_imag;
  		yreal=inv_L[2*k  +col*Ncols];
  		yimag=inv_L[2*k+1+col*Ncols];
  		inv_L[2*k  +row*Ncols]-=xreal*yreal-ximag*yimag;
  		inv_L[2*k+1+row*Ncols]-=xreal*yimag+ximag*yreal;
  		xreal=factor_real;
  		ximag=factor_imag;
  		yreal=L[2*k  +col*Ncols];
  		yimag=L[2*k+1+col*Ncols];
  		L[2*k  +row*Ncols]-=xreal*yreal-ximag*yimag;
  		L[2*k+1+row*Ncols]-=xreal*yimag+ximag*yreal;
	  }
	}
  }

  /* set inv_U matrix to identity */
  inv_U=&L[0];
  memset(inv_U,0.0,sizeof(float)*Nrows*Ncols);
  for (row=0;row<Nrows;row++) {
	inv_U[2*row  +row*Ncols]=1;
  }

  /* use Gauss Jordan algorithm to invert U whose result is in L */
  for (col=Nrows-1;col>=1;col--) {
	for (row=col-1;row>=0;row--) {
	  xreal=U[2*col  +row*Ncols];
	  ximag=U[2*col+1+row*Ncols];
	  yreal=U[2*col  +col*Ncols];
	  yimag=U[2*col+1+col*Ncols];
	  complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  factor_real=zreal;
	  factor_imag=zimag;
	  for (k=0;k<Nrows;k++) {
		xreal=factor_real;
		ximag=factor_imag;
		yreal=inv_U[2*k  +col*Ncols];
		yimag=inv_U[2*k+1+col*Ncols];
		complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
		inv_U[2*k  +row*Ncols]-=xreal*yreal-ximag*yimag;
		inv_U[2*k+1+row*Ncols]-=xreal*yimag+ximag*yreal;
		xreal=factor_real;
		ximag=factor_imag;
		yreal=U[2*k  +col*Ncols];
		yimag=U[2*k+1+col*Ncols];
		U[2*k  +row*Ncols]-=xreal*yreal-ximag*yimag;
		U[2*k+1+row*Ncols]-=xreal*yimag+ximag*yreal;
	  }
	}
  }

  /* scale U & L to get identity matrix in U */
  for (row=Nrows-1;row>=0;row--) {
	factor_real=U[2*row  +row*Ncols];
	factor_imag=U[2*row+1+row*Ncols];
	for (col=0;col<Nrows;col++) {
	  xreal=L[2*col  +row*Ncols];
	  ximag=L[2*col+1+row*Ncols];
	  yreal=factor_real;
	  yimag=factor_imag;
	  complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  L[2*col  +row*Ncols]=zreal;
	  L[2*col+1+row*Ncols]=zimag;
	  xreal=U[2*col  +row*Nrows];
	  ximag=U[2*col+1+row*Nrows];
	  yreal=factor_real;
	  yimag=factor_imag;
	  complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  U[2*col  +row*Ncols]=zreal;
	  U[2*col+1+row*Ncols]=zimag;
	}
  }

  /* compute inv_U_x_inv_L=inv(U)*inv(L) */
  inv_U_x_inv_L=&L[0];
  for (row=0;row<Nrows;row++) {
    for (col=0;col<Nrows;col++) {
    sum_real=0;
    sum_imag=0;
  	for (k=0;k<Nrows;k++) {
   	  xreal=inv_U[2*k  +row*Ncols];
   	  ximag=inv_U[2*k+1+row*Ncols];
   	  yreal=inv_L[2*col  +k*Ncols];
   	  yimag=inv_L[2*col+1+k*Ncols];
   	  sum_real+=xreal*yreal-ximag*yimag;
   	  sum_imag+=xreal*yimag+ximag*yreal;
   	}
   	inv_U_x_inv_L[2*col  +row*Ncols]=sum_real;
   	inv_U_x_inv_L[2*col+1+row*Ncols]=sum_imag;
    }
  }
  /* compute inv_A=inv(U)*inv(L)*P */
  for (row=0;row<Nrows;row++) {
    for (col=0;col<Nrows;col++) {
      sum_real=0;
      sum_imag=0;
  	  for (k=0;k<Nrows;k++) {
   	    xreal=inv_U_x_inv_L[2*k  +row*Ncols];
   	    ximag=inv_U_x_inv_L[2*k+1+row*Ncols];
   	    yreal=P[col+k*Nrows];
   	    sum_real+=xreal*yreal;
   	    sum_imag+=ximag*yreal;
   	  }
      inv_A[2*col  +row*Ncols]=sum_real;
      inv_A[2*col+1+row*Ncols]=sum_imag;
    }
  }

  return 0;
}

void complex_sp_div_cn(float x_real,float x_imag,float y_real,float y_imag,
                       float *z_real,float *z_imag) {

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
/*  End of file:  DSPF_sp_lud_inv_cmplx_cn.c                               */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
