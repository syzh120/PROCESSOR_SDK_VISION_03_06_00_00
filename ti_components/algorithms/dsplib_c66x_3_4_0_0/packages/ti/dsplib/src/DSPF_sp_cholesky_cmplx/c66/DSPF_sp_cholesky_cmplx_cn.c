/* ======================================================================= */
/* DSPF_sp_cholesky_cmplx_cn.c -- Cholesky decomposition and solver        */
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

#include "DSPF_sp_cholesky_cmplx_cn.h"

static void complex_sp_sqrt_cn(float x_real,float x_imag,float *z_real,float *z_imag);
static void complex_sp_div_cn(float x_real,float x_imag,float y_real,float y_imag,float *z_real,float *z_imag);

int DSPF_sp_cholesky_cmplx_cn(int enable_test, const int Nrows, float *A, float *L)
{
  short i,j,k,Ncols;
  float xreal,ximag,yreal,yimag,zreal,zimag;
  float sum_real,sum_imag,sum1_real,sum1_imag;

  if (enable_test) {
	Ncols=2*Nrows;
    /* test A for positive definite matrix:    */
    /* z_transpose*A*z>0 where z=1,2,...Nrows  */
	sum1_real=0;
	sum1_imag=0;
    for (i=0;i<Nrows;i++) {
	  sum_real=0;
	  sum_imag=0;
	  for (j=0;j<Nrows;j++) {
		xreal=A[i*Ncols+2*j  ];
		ximag=A[i*Ncols+2*j+1];
		yreal=(float)(j+1);
		sum_real+=xreal*yreal;
		sum_imag+=ximag*yreal;
	  }
      sum1_real+=(float)(i+1)*sum_real;
      sum1_imag+=(float)(i+1)*sum_imag;
    }
    if (sum1_real<=0) {
	  return -1;
    }
  }

  /* generate lower diagonal matrix L */
  Ncols=2*Nrows;
  for (j=0;j<Nrows;j++) {

	/* diagonal entry */
	sum_real=0.0;
	sum_imag=0.0;
	for (k=0;k<=2*j-1;k+=2) {
	  xreal=L[j*Ncols+k  ];
	  ximag=L[j*Ncols+k+1];
	  sum_real+=xreal*xreal+ximag*ximag;
	  sum_imag+=0;
	}
	xreal=A[j*Ncols+2*j  ]-sum_real;
	ximag=A[j*Ncols+2*j+1]-sum_imag;
	complex_sp_sqrt_cn(xreal,ximag,&zreal,&zimag);
	L[j*Ncols+2*j  ]=zreal;
	L[j*Ncols+2*j+1]=zimag;

    /* lower triangular entries */
    for (i=j+1;i<Nrows;i++) {
      sum_real=0.0;
      sum_imag=0.0;
      for (k=0;k<=2*j-1;k+=2) {
    	xreal= L[i*Ncols+k  ];
        ximag= L[i*Ncols+k+1];
        yreal= L[j*Ncols+k  ];
        yimag=-L[j*Ncols+k+1];
    	sum_real+=xreal*yreal-ximag*yimag;
    	sum_imag+=ximag*yreal+yimag*xreal;
      }
      xreal=A[i*Ncols+2*j  ]-sum_real;
      ximag=A[i*Ncols+2*j+1]-sum_imag;
      yreal=L[j*Ncols+2*j  ];
      yimag=L[j*Ncols+2*j+1];
      complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
      L[i*Ncols+2*j  ]=zreal;
      L[i*Ncols+2*j+1]=zimag;

 	}
  }

  return 0;
}

int DSPF_sp_cholesky_in_place_cmplx_cn(const int enable_test, const int Nrows, float *A)
{
  short i,j,k,Ncols;
  float xreal,ximag,yreal,yimag,zreal,zimag;
  float sum_real,sum_imag,sum1_real,sum1_imag;

  if (enable_test) {
	Ncols=2*Nrows;
    /* test A for positive definite matrix:    */
    /* z_transpose*A*z>0 where z=1,2,...Nrows  */
	sum1_real=0;
	sum1_imag=0;
    for (i=0;i<Nrows;i++) {
	  sum_real=0;
	  sum_imag=0;
	  for (j=0;j<Nrows;j++) {
		xreal=A[i*Ncols+2*j  ];
		ximag=A[i*Ncols+2*j+1];
		yreal=(float)(j+1);
		sum_real+=xreal*yreal;
		sum_imag+=ximag*yreal;
	  }
      sum1_real+=(float)(i+1)*sum_real;
      sum1_imag+=(float)(i+1)*sum_imag;
    }
    if (sum1_real<=0) {
	  return -1;
    }
  }

  /* cholesky outer product version from p 145 Matrix Computations by Golub and Loan */
  Ncols=2*Nrows;
  for (k=0;k<Nrows;k++) {
	xreal=A[k*Ncols+2*k  ];
	ximag=A[k*Ncols+2*k+1];
	complex_sp_sqrt_cn(xreal,ximag,&zreal,&zimag);
	A[k*Ncols+2*k  ]=zreal;
	A[k*Ncols+2*k+1]=zimag;

	for (i=k+1;i<Nrows;i++) {
	  xreal=A[i*Ncols+2*k  ];
	  ximag=A[i*Ncols+2*k+1];
	  yreal=A[k*Ncols+2*k  ];
	  yimag=A[k*Ncols+2*k+1];
	  complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  A[i*Ncols+2*k  ]=zreal;
	  A[i*Ncols+2*k+1]=zimag;
	}
	for (j=k+1;j<Nrows;j++) {
      for (i=j;i<Nrows;i++) {
    	xreal= A[i*Ncols+2*k  ];
    	ximag= A[i*Ncols+2*k+1];
    	yreal= A[j*Ncols+2*k  ];
    	yimag=-A[j*Ncols+2*k+1];
    	A[i*Ncols+2*j  ]-=xreal*yreal-ximag*yimag;
    	A[i*Ncols+2*j+1]-=xreal*yimag+ximag*yreal;
      }
    }
  }

  return 0;
}


int DSPF_sp_cholesky_solver_cmplx_cn(const int Nrows,float *L,float *y,float *b,float *x)
{
  short i,k,Ncols;
  float sum_real,sum_imag,xreal,ximag,yreal,yimag,zreal,zimag;

  /* solve L*y=b for y using forward substitution */
  Ncols=2*Nrows;
  for (i=0;i<Nrows;i++) {
    if (i==0) {
	  xreal=b[2*i  ];
	  ximag=b[2*i+1];
	  yreal=L[0];
      yimag=L[1];
      complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
      y[2*i  ]=zreal;
      y[2*i+1]=zimag;
	} else {
	  sum_real=0;
	  sum_imag=0;
	  for (k=0;k<=i-1;k++) {
		xreal=L[i*Ncols+2*k  ];
		ximag=L[i*Ncols+2*k+1];
		yreal=y[2*k  ];
		yimag=y[2*k+1];
		sum_real+=xreal*yreal-ximag*yimag;
		sum_imag+=xreal*yimag+ximag*yreal;
	  }
	  xreal=b[2*i  ]-sum_real;
	  ximag=b[2*i+1]-sum_imag;
	  yreal=L[i*Ncols+2*i  ];
	  yimag=L[i*Ncols+2*i+1];
	  complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  y[2*i  ]=zreal;
	  y[2*i+1]=zimag;
	}
  }

  /* solve U*x=y for x using backward substitution */
  for (i=Nrows-1;i>=0;i--) {
	if (i==Nrows-1) {
	  xreal=y[2*i  ];
	  ximag=y[2*i+1];
	  yreal= L[i*Ncols+2*i  ];
	  yimag=-L[i*Ncols+2*i+1];
	  complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  x[2*i  ]=zreal;
	  x[2*i+1]=zimag;
	} else {
	  sum_real=0;
	  sum_imag=0;
	  for (k=Nrows-1;k>=i+1;k--) {
		xreal= L[k*Ncols+2*i  ];
		ximag=-L[k*Ncols+2*i+1];
		yreal=x[2*k  ];
		yimag=x[2*k+1];
		sum_real+=xreal*yreal-ximag*yimag;
		sum_imag+=xreal*yimag+ximag*yreal;
	  }
	  xreal=y[2*i  ]-sum_real;
	  ximag=y[2*i+1]-sum_imag;
	  yreal= L[i*Ncols+2*i  ];
	  yimag=-L[i*Ncols+2*i+1];
	  complex_sp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
	  x[2*i  ]=zreal;
	  x[2*i+1]=zimag;
	}
  }

  return 0;
}

void complex_sp_sqrt_cn(float x_real,float x_imag,float *z_real,float *z_imag) {

  float x_mag,z_mag;
  float x_angle,z_angle;

  /* magnitude */
  x_mag=sqrt(x_real*x_real+x_imag*x_imag);
  z_mag=sqrt(x_mag);

  /* angle */
  x_angle=atan2(x_imag,x_real);
  z_angle=x_angle/2;

  /* results */
  *z_real=cos(z_angle)*z_mag;
  *z_imag=sin(z_angle)*z_mag;
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
/*  End of file:  DSPF_sp_cholesky_cmplx_cn.c                              */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
