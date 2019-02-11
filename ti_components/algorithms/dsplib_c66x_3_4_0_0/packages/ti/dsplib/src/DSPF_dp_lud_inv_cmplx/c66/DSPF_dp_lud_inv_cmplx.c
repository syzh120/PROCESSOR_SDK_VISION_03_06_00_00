/* ======================================================================= */
/* DSPF_dp_lud_inv_cmplx.c - complex matrix inversion by LUD double precision*/
/*                        optimized C Implementation                       */
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

#pragma CODE_SECTION(DSPF_dp_lud_inverse_cmplx,".text:optimized");

#include "DSPF_dp_lud_inv_cmplx.h"

#define ENABLE_NR 1
#define ENABLE_MATHLIB 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2dp/c66/atan2dp.h>
#include <ti/mathlib/src/cosdp/c66/cosdp.h>
#include <ti/mathlib/src/sindp/c66/sindp.h>
#endif

static void complex_dp_div(double x_real,double x_imag,double y_real,double y_imag,
                           double *z_real,double *z_imag);
static void complex_dp_inv(double y_real,double y_imag,double *z_real,double *z_imag);


int DSPF_dp_lud_inverse_cmplx(const int Nrows,unsigned short *restrict P,double *restrict L,
                              double *restrict U,double *restrict inv_A) {

  int row,col,Ncols,k;
  double xreal,ximag,yreal,yimag,zreal,zimag;
  double factor_real,factor_imag,sum_real,sum_imag;
  double *inv_L,*inv_U,*inv_U_x_inv_L;

  _nassert(Nrows>0);
  _nassert((int)P % 2 == 0);
  _nassert((int)L % 8 == 0);
  _nassert((int)U % 8 == 0);
  _nassert((int)inv_A % 8 == 0);

  /* set inv_A matrix to identity */
  inv_L=&inv_A[0];
  Ncols=2*Nrows;
  memset(inv_L,0.0,sizeof(double)*Nrows*Ncols);
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
	inv_L[2*row  +row*Ncols]=1;
  }

  /* use Gauss Jordan algorithm to invert L whose result is in inv_L */
#pragma MUST_ITERATE(1,,)
  for (col=0;col<Nrows-1;col++) {
	yreal=L[2*col  +col*Ncols];
	yimag=L[2*col+1+col*Ncols];
	complex_dp_inv(yreal,yimag,&zreal,&zimag);

#pragma MUST_ITERATE(1,,)
    for (row=col+1;row<Nrows;row++) {
      xreal=L[2*col  +row*Ncols];
      ximag=L[2*col+1+row*Ncols];
	  factor_real=xreal*zreal-ximag*zimag;
	  factor_imag=xreal*zimag+ximag*zreal;

#pragma MUST_ITERATE(1,,)
	  for (k=0;k<row;k++) {
		xreal=factor_real;
		ximag=factor_imag;
		yreal=inv_L[2*k  +col*Ncols];
		yimag=inv_L[2*k+1+col*Ncols];
		inv_L[2*k  +row*Ncols]-=xreal*yreal-ximag*yimag;
		inv_L[2*k+1+row*Ncols]-=xreal*yimag+ximag*yreal;
	  }
	}
  }

  /* set inv_U matrix to identity */
  inv_U=&L[0];
  memset(inv_U,0.0,sizeof(double)*Nrows*Ncols);
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
	inv_U[2*row  +row*Ncols]=1;
  }

  /* use Gauss Jordan algorithm to invert U whose result is in L */
#pragma MUST_ITERATE(1,,)
  for (col=Nrows-1;col>=1;col--) {
#pragma MUST_ITERATE(1,,)
	for (row=col-1;row>=0;row--) {
	  xreal=U[2*col  +row*Ncols];
	  ximag=U[2*col+1+row*Ncols];
	  yreal=U[2*col  +col*Ncols];
	  yimag=U[2*col+1+col*Ncols];
	  complex_dp_div(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  factor_real=zreal;
	  factor_imag=zimag;

#pragma MUST_ITERATE(1,,)
	  for (k=col;k<Nrows;k++) {
		xreal=factor_real;
		ximag=factor_imag;
		yreal=inv_U[2*k  +col*Ncols];
		yimag=inv_U[2*k+1+col*Ncols];
		complex_dp_div(xreal,ximag,yreal,yimag,&zreal,&zimag);
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
#pragma MUST_ITERATE(1,,)
  for (row=Nrows-1;row>=0;row--) {
	yreal=U[2*row  +row*Ncols];
	yimag=U[2*row+1+row*Ncols];
	complex_dp_inv(yreal,yimag,&zreal,&zimag);
	factor_real=zreal;
	factor_imag=zimag;

#pragma MUST_ITERATE(1,,)
	for (col=0;col<Nrows;col++) {
	  xreal=L[2*col  +row*Ncols];
	  ximag=L[2*col+1+row*Ncols];
	  L[2*col  +row*Ncols]=xreal*zreal-ximag*zimag;
	  L[2*col+1+row*Ncols]=xreal*zimag+ximag*zreal;
	}
  }

  /* compute inv_U_x_inv_L=inv(U)*inv(L) */
  inv_U_x_inv_L=&L[0];
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
    for (col=0;col<Nrows;col++) {
      sum_real=0;
      sum_imag=0;
#pragma MUST_ITERATE(1,,)
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
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
    for (col=0;col<Nrows;col++) {
      sum_real=0;
      sum_imag=0;
#pragma MUST_ITERATE(1,,)
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

static void complex_dp_div(double x_real,double x_imag,double y_real,double y_imag,double *z_real,double *z_imag) {

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
  *z_real=(x_real*y_real+x_imag*y_imag)*inv_mag_sq;
  *z_imag=(x_imag*y_real-x_real*y_imag)*inv_mag_sq;

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
/*  End of file:  DSPF_dp_lud_inv_cmplx.c                                  */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
