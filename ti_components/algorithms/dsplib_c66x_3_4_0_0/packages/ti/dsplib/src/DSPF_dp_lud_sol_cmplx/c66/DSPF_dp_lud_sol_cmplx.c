/* ======================================================================= */
/* DSPF_dp_lud_sol_cmplx.c -- complex linear solver by LUD                 */
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

#pragma CODE_SECTION(DSPF_dp_lud_solver_cmplx,".text:optimized");
#include "DSPF_dp_lud_sol_cmplx.h"

#define ENABLE_NR 1
#define ENABLE_MATHLIB 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2dp/c66/atan2dp.h>
#include <ti/mathlib/src/cosdp/c66/cosdp.h>
#include <ti/mathlib/src/sindp/c66/sindp.h>
#endif

static void complex_dp_inv(double y_real,double y_imag,double *z_real,double *z_imag);

int DSPF_dp_lud_solver_cmplx(const int Nrows,unsigned short *restrict P,double *restrict L,double *restrict U,double *restrict b,double *restrict b_mod,double *restrict y,double *restrict x) {

  short row,col,Ncols;
  double sum_real,sum_imag;
  double xreal,ximag,yreal,yimag,zreal,zimag;

  _nassert(Nrows>0);
  _nassert((int)P % 2 == 0);
  _nassert((int)L % 8 == 0);
  _nassert((int)U % 8 == 0);
  _nassert((int)b % 8 == 0);
  _nassert((int)b_mod % 8 == 0);
  _nassert((int)y % 8 == 0);
  _nassert((int)x % 8 == 0);

  /* modify b based on permutation matrix P */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
	sum_real=0;
	sum_imag=0;
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Nrows;col++) {
	  sum_real+=P[col+row*Nrows]*b[2*col  ];
	  sum_imag+=P[col+row*Nrows]*b[2*col+1];
	}
	b_mod[2*row  ]=sum_real;
	b_mod[2*row+1]=sum_imag;
  }

  /* solve L*y=b for y using forward substitution */
  Ncols=2*Nrows;
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
  	yreal=L[2*row  +row*Ncols];
  	yimag=L[2*row+1+row*Ncols];
  	complex_dp_inv(yreal,yimag,&zreal,&zimag);
    if (row==0) {
      xreal=b_mod[2*row  ];
      ximag=b_mod[2*row+1];
      y[2*row  ]=xreal*zreal-ximag*zimag;
      y[2*row+1]=xreal*zimag+ximag*zreal;
	} else {
	  sum_real=0;
	  sum_imag=0;
	  for (col=0;col<=row-1;col++) {
		xreal=L[2*col  +row*Ncols];
		ximag=L[2*col+1+row*Ncols];
		yreal=y[2*col  ];
		yimag=y[2*col+1];
		sum_real+=xreal*yreal-ximag*yimag;
		sum_imag+=xreal*yimag+ximag*yreal;
	  }
	  xreal=b_mod[2*row  ]-sum_real;
	  ximag=b_mod[2*row+1]-sum_imag;
	  y[2*row  ]=xreal*zreal-ximag*zimag;
	  y[2*row+1]=xreal*zimag+ximag*zreal;
	}
  }

  /* solve U*x=y for x using backward substitution */
#pragma MUST_ITERATE(1,,)
  for (row=Nrows-1;row>=0;row--) {
	yreal=U[2*row  +row*Ncols];
	yimag=U[2*row+1+row*Ncols];
  	complex_dp_inv(yreal,yimag,&zreal,&zimag);
	if (row==Nrows-1) {
	  xreal=y[2*row  ];
	  ximag=y[2*row+1];
	  x[2*row  ]=xreal*zreal-ximag*zimag;
	  x[2*row+1]=xreal*zimag+ximag*zreal;
	} else {
	  sum_real=0;
	  sum_imag=0;
	  for (col=Nrows-1;col>=row+1;col--) {
		xreal=U[2*col  +row*Ncols];
		ximag=U[2*col+1+row*Ncols];
		yreal=x[2*col  ];
		yimag=x[2*col+1];
		sum_real+=xreal*yreal-ximag*yimag;
		sum_imag+=xreal*yimag+ximag*yreal;
	  }
	  xreal=y[2*row  ]-sum_real;
	  ximag=y[2*row+1]-sum_imag;
	  x[2*row  ]=xreal*zreal-ximag*zimag;
	  x[2*row+1]=xreal*zimag+ximag*zreal;
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
/*  End of file:  DSPF_dp_lud_sol_cmplx.c                                  */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
