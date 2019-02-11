/* ======================================================================= */
/* DSPF_dp_lud_cn.c -- lower/upper decomposition                           */
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

#include "DSPF_dp_lud_cmplx_cn.h"

static void complex_dp_div_cn(double x_real,double x_imag,double y_real,
                              double y_imag,double *z_real,double *z_imag);

int DSPF_dp_lud_cmplx_cn(const int Nrows, double *A, double *L,double *U,unsigned short *P)
{
  int row,col,col2,Ncols;
  int min_row,max_row,k,temp;
  double mag,min,max,tmp_real,tmp_imag;
  double xreal,ximag,yreal,yimag,zreal,zimag;

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
  memcpy(U,A, sizeof(double)*Nrows*Ncols);
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
	  complex_dp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
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

int DSPF_dp_lud_solver_cmplx_cn(const int Nrows,unsigned short *P,double *L,double *U,double *b,double *b_mod,double *y,double *x) {

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

int DSPF_dp_lud_inverse_cmplx_cn(const int Nrows,unsigned short *P,double *L,double *U,double *inv_A) {

  int row,col,Ncols,k;
  double factor_real,factor_imag,sum_real,sum_imag;
  double xreal,ximag,yreal,yimag,zreal,zimag;
  double *inv_L,*inv_U,*inv_U_x_inv_L;

  /* set inv_A matrix to identity */
  inv_L=&inv_A[0];
  Ncols=2*Nrows;
  memset(inv_L,0.0,sizeof(double)*Nrows*Ncols);
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
      complex_dp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
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
  memset(inv_U,0.0,sizeof(double)*Nrows*Ncols);
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
      complex_dp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
      factor_real=zreal;
      factor_imag=zimag;
	  for (k=0;k<Nrows;k++) {
		xreal=factor_real;
		ximag=factor_imag;
		yreal=inv_U[2*k  +col*Ncols];
		yimag=inv_U[2*k+1+col*Ncols];
		complex_dp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
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
      complex_dp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
      L[2*col  +row*Ncols]=zreal;
      L[2*col+1+row*Ncols]=zimag;
      xreal=U[2*col  +row*Nrows];
      ximag=U[2*col+1+row*Nrows];
      yreal=factor_real;
      yimag=factor_imag;
      complex_dp_div_cn(xreal,ximag,yreal,yimag,&zreal,&zimag);
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

static void complex_dp_div_cn(double x_real,double x_imag,double y_real,double y_imag,double *z_real,double *z_imag) {

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
/*  End of file:  DSPF_dp_lud_cn.c                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
