/* ======================================================================= */
/* DSPF_dp_lud_sol_cmplx_cn.c -- complex linear solver by LUD              */
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

#include "DSPF_dp_lud_sol_cmplx_cn.h"

static void complex_dp_div_cn(double x_real,double x_imag,double y_real,
                              double y_imag,double *z_real,double *z_imag);

int DSPF_dp_lud_solver_cmplx_cn(const int Nrows,unsigned short *P,double *L,
                        double *U,double *b,double *b_mod,double *y,double *x) {

  short row,col,Ncols;
  double xreal,ximag,yreal,yimag,zreal,zimag;
  double sum_real,sum_imag;

  /* modify b based on permutation matrix P */
  Ncols=2*Nrows;
  for (row=0;row<Nrows;row++) {
	sum_real=0;
	sum_imag=0;
	for (col=0;col<Nrows;col++) {
	  sum_real+=P[col+row*Nrows]*b[2*col  ];
	  sum_imag+=P[col+row*Nrows]*b[2*col+1];
	}
	b_mod[2*row  ]=sum_real;
	b_mod[2*row+1]=sum_imag;
  }

  /* solve L*y=b for y using forward substitution */
  Ncols=2*Nrows;
  for (row=0;row<Nrows;row++) {
    if (row==0) {
      xreal=b_mod[2*row  ];
      ximag=b_mod[2*row+1];
      yreal=L[0];
      yimag=L[1];
      complex_dp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
      y[2*row  ]=zreal;
      y[2*row+1]=zimag;
	} else {
	  sum_real=0;
	  sum_imag=0;
	  for (col=0;col<=row-1;col++) {
		xreal=L[row*Ncols+2*col  ];
		ximag=L[row*Ncols+2*col+1];
		yreal=y[2*col  ];
		yimag=y[2*col+1];
	    sum_real+=xreal*yreal-ximag*yimag;
	    sum_imag+=xreal*yimag+ximag*yreal;
	  }
	  xreal=b_mod[2*row  ]-sum_real;
	  ximag=b_mod[2*row+1]-sum_imag;
	  yreal=L[row*Ncols+2*row  ];
	  yimag=L[row*Ncols+2*row+1];
	  complex_dp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  y[2*row  ]=zreal;
	  y[2*row+1]=zimag;
	}
  }

  /* solve U*x=y for x using backward substitution */
  for (row=Nrows-1;row>=0;row--) {
	if (row==Nrows-1) {
	  xreal=y[2*row  ];
	  ximag=y[2*row+1];
	  yreal=U[row*Ncols+2*row  ];
	  yimag=U[row*Ncols+2*row+1];
	  complex_dp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  x[2*row  ]=zreal;
	  x[2*row+1]=zimag;
	} else {
	  sum_real=0;
	  sum_imag=0;
	  for (col=Nrows-1;col>=row+1;col--) {
		xreal=U[row*Ncols+2*col  ];
		ximag=U[row*Ncols+2*col+1];
		yreal=x[2*col  ];
		yimag=x[2*col+1];
		sum_real+=xreal*yreal-ximag*yimag;
		sum_imag+=xreal*yimag+ximag*yreal;
	  }
	  xreal=y[2*row  ]-sum_real;
	  ximag=y[2*row+1]-sum_imag;
	  yreal=U[row*Ncols+2*row  ];
	  yimag=U[row*Ncols+2*row+1];
	  complex_dp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  x[2*row  ]=zreal;
	  x[2*row+1]=zimag;
	}
  }

  return 0;
}

static void complex_dp_div_cn(double x_real,double x_imag,double y_real,
                              double y_imag,double *z_real,double *z_imag) 
{
  double x_mag,y_mag,z_mag;
  double x_angle,y_angle,z_angle;

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
/*  End of file:  DSPF_dp_lud_sol_cmplx_cn.c                               */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
