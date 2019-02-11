/* ======================================================================= */
/* DSPF_dp_svd_cmplx.c -- singular value decomposition                     */
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

#pragma CODE_SECTION(DSPF_dp_svd_cmplx,".text:optimized");
#pragma CODE_SECTION(DSPF_dp_convert_to_bidiag_cmplx,".text:optimized");
#pragma CODE_SECTION(DSPF_dp_bidiag_to_diag_cmplx,".text:optimized");
#pragma CODE_SECTION(DSPF_dp_sort_singular_values_cmplx,".text:optimized");

#include "DSPF_dp_svd_cmplx.h"

#define ENABLE_NR   1
#define ENABLE_MATHLIB 1

#define MAX_ITERATION_COUNT 30
#define ZERO_TOLERANCE 1.0e-12
//#define ENABLE_REDUCED_FORM 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2dp/c66/atan2dp.h> 
#include <ti/mathlib/src/cosdp/c66/cosdp.h>
#include <ti/mathlib/src/sindp/c66/sindp.h>
#endif

static int DSPF_dp_convert_to_bidiag_cmplx(const int Nrows,const int Ncols,double *restrict U,double *restrict V,double *restrict diag,double *restrict superdiag);
static int DSPF_dp_bidiag_to_diag_cmplx(const int Nrows,const int Ncols,double *restrict U,double *restrict V,double *restrict diag,double *restrict superdiag);
static int DSPF_dp_sort_singular_values_cmplx(const int Nrows,const int Ncols,double *restrict U,double *restrict V,double *restrict singular_values);

static void complex_dp_sqrt(double x_real,double x_imag,double *z_real,double *z_imag);
static void complex_dp_inv(double y_real,double y_imag,double *z_real,double *z_imag);
static void complex_dp_div(double x_real,double x_imag,double y_real,double y_imag,double *z_real,double *z_imag);

int DSPF_dp_svd_cmplx(const int Nrows,const int Ncols,double *restrict A,double *restrict U,double *restrict V,double *restrict U1,double *restrict diag,double *restrict superdiag)
{
  int row,col,Nrows1,Ncols1,status;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)A % 8 == 0);
  _nassert((int)U % 8 == 0);
  _nassert((int)V % 8 == 0);
  _nassert((int)U1 % 8 == 0);
  _nassert((int)diag % 8 == 0);
  _nassert((int)superdiag % 8 == 0);

  /* ------------------------------------------------------------------- */
  /* copy A matrix to D                                                  */
  /* ------------------------------------------------------------------- */
  if (Nrows>=Ncols) {
	Nrows1=Nrows;
	Ncols1=Ncols;
    memcpy(U,A,sizeof(double)*Nrows*2*Ncols);
  } else {
	/* transpose matrix */
#pragma MUST_ITERATE(1,,)
	for (row=0;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
      for (col=0;col<Ncols;col++) {
      	U[2*row  +col*2*Nrows]= A[2*col  +row*2*Ncols];
      	U[2*row+1+col*2*Nrows]=-A[2*col+1+row*2*Ncols];
      }
	}
	Nrows1=Ncols;
	Ncols1=Nrows;
  }

  /* ------------------------------------------------------------------- */
  /* convert A to bidiagonal matrix using Householder reflections        */
  /* ------------------------------------------------------------------- */
  DSPF_dp_convert_to_bidiag_cmplx(Nrows1,Ncols1,U,V,diag,superdiag);

  /* ------------------------------------------------------------------- */
  /* convert bidiagonal to diagonal using Givens rotations               */
  /* ------------------------------------------------------------------- */
  status=DSPF_dp_bidiag_to_diag_cmplx(Nrows1,Ncols1,U,V,diag,superdiag);

  /* ------------------------------------------------------------------- */
  /* sort singular values in descending order                            */
  /* ------------------------------------------------------------------- */
  DSPF_dp_sort_singular_values_cmplx(Nrows1,Ncols1,U,V,diag);

  /* ------------------------------------------------------------------- */
  /* switch U and V                                                      */
  /* ------------------------------------------------------------------- */
  if (Ncols>Nrows) {
#ifndef ENABLE_REDUCED_FORM
	memcpy(U1,V,sizeof(double)*Nrows*2*Nrows);
	memcpy(V,U,sizeof(double)*Ncols*2*Ncols);
	memcpy(U,U1,sizeof(double)*Nrows*2*Nrows);
#else
	memcpy(U1,V,sizeof(double)*Ncols*2*Ncols);
	memcpy(V,U,sizeof(double)*Nrows*2*Ncols);
	memcpy(U,U1,sizeof(double)*Nrows*2*Ncols);
#endif
	/* get Hermitian of diagonal entries */
#pragma MUST_ITERATE(1,,)
	for (row=0;row<Nrows;row++) {
	  diag[2*row+1]=-diag[2*row+1];
	}
  }

  return status;
}

static int DSPF_dp_convert_to_bidiag_cmplx(const int Nrows,const int Ncols,double *restrict U,double *restrict V,double *restrict diag,double *restrict superdiag)
{
  int i,j,k;
  double scale,s,s2;
  double s_real,s_imag,si_real,si_imag,half_norm_squared_real,half_norm_squared_imag;
  double inv_half_norm_squared_real,inv_half_norm_squared_imag;
  double inv_s;
  double xreal,ximag,yreal,yimag,zreal,zimag;
  double inv_U_x_s_real,inv_U_x_s_imag;
  double x,y;
#ifndef ENABLE_REDUCED_FORM
  double yreal1,yimag1;
#endif

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)U % 8 == 0);
  _nassert((int)V % 8 == 0);
  _nassert((int)diag % 8 == 0);
  _nassert((int)superdiag % 8 == 0);

  /* Householder processing */
  s=0;
  scale=0;
  for (i=0;i<Ncols;i++) {
	/* superdiag[i]=scale*s; */
	superdiag[2*i  ]=scale*s;
	superdiag[2*i+1]=0;

	/* process columns */
	scale=0;
#pragma MUST_ITERATE(1,,)
	for (j=i;j<Nrows;j++) {
	  /* scale+=fabs(U[i+j*Ncols]); */
	  scale+=sqrt(U[2*i+1+j*2*Ncols]*U[2*i+1+j*2*Ncols]+U[2*i+j*2*Ncols]*U[2*i+j*2*Ncols]);
	}
	if (scale>0) {
	  s2=0;
#ifndef ENABLE_NR
#pragma MUST_ITERATE(1,,)
	  for (j=i;j<Nrows;j++) {
		/* U[i+j*Ncols]=U[i+j*Ncols]/scale; */
		U[2*i  +j*2*Ncols]/=scale;
		U[2*i+1+j*2*Ncols]/=scale;
#else
	  x=scale;
      y=_rcpdp(x);
      y=y*(2.0-x*y);
      y=y*(2.0-x*y);
      y=y*(2.0-x*y);
#pragma MUST_ITERATE(1,,)
  	  for (j=i;j<Nrows;j++) {
  		/* U[i+j*Ncols]=U[i+j*Ncols]*y; */
  		U[2*i  +j*2*Ncols]*=y;
  		U[2*i+1+j*2*Ncols]*=y;
#endif
		/* s2+=U[i+j*Ncols]*conj(U[i+j*Ncols]); */
		xreal=U[2*i  +j*2*Ncols];
		ximag=U[2*i+1+j*2*Ncols];
		s2+=xreal*xreal+ximag*ximag;
	  }
	  /* if (U[i+i*Ncols]<0) { */
	  if (U[2*i  +i*2*Ncols]<0) {
		s=sqrt(s2);
	  } else {
		s=-sqrt(s2);
	  }
	  /* half_norm_squared=U[i+i*Ncols]*s-s2; */
	  half_norm_squared_real=U[2*i  +i*2*Ncols]*s-s2;
	  half_norm_squared_imag=U[2*i+1+i*2*Ncols]*s   ;
	  complex_dp_inv(half_norm_squared_real,half_norm_squared_imag,&inv_half_norm_squared_real,&inv_half_norm_squared_imag);
	  /* U[i+i*Ncols]-=s; */
	  U[2*i  +i*2*Ncols]-=s;
	  for (j=i+1;j<Ncols;j++) {
		si_real=0;
		si_imag=0;
#pragma MUST_ITERATE(1,,)
		for (k=i;k<Nrows;k++) {
		  /* si+=conj(U[i+k*Ncols])*U[j+k*Ncols]; */
		  xreal= U[2*i  +k*2*Ncols];
		  ximag=-U[2*i+1+k*2*Ncols];
		  yreal= U[2*j  +k*2*Ncols];
		  yimag= U[2*j+1+k*2*Ncols];
		  si_real+=xreal*yreal-ximag*yimag;
		  si_imag+=xreal*yimag+ximag*yreal;
		}
        /* si=si/half_norm_squared; */
        xreal=si_real;
        ximag=si_imag;
        yreal=inv_half_norm_squared_real;
        yimag=inv_half_norm_squared_imag;
        si_real=xreal*yreal-ximag*yimag;
        si_imag=xreal*yimag+ximag*yreal;
#pragma MUST_ITERATE(1,,)
		for (k=i;k<Nrows;k++) {
		  /* U[j+k*Ncols]+=si*U[i+k*Ncols]; */
		  xreal=si_real;
		  ximag=si_imag;
		  yreal=U[2*i  +k*2*Ncols];
		  yimag=U[2*i+1+k*2*Ncols];
		  U[2*j  +k*2*Ncols]+=xreal*yreal-ximag*yimag;
		  U[2*j+1+k*2*Ncols]+=xreal*yimag+ximag*yreal;
		}
	  }
	} /* if (scale>0) */
#pragma MUST_ITERATE(1,,)
	for (j=i;j<Nrows;j++) {
	  /* U[i+j*Ncols]*=scale; */
	  U[2*i  +j*2*Ncols]*=scale;
	  U[2*i+1+j*2*Ncols]*=scale;
	}
	/* diag[i]=s*scale; */
	diag[2*i  ]=s*scale;
	diag[2*i+1]=0;
	/* process rows */
    s=0;
    scale=0;
    if ((i<Nrows)&&(i!=Ncols-1)) {
      for (j=i+1;j<Ncols;j++) {
    	/* scale+=fabs(U[j+i*Ncols]); */
      	scale+=sqrt(U[2*j+1+i*2*Ncols]*U[2*j+1+i*2*Ncols]+U[2*j+i*2*Ncols]*U[2*j+i*2*Ncols]);
      }
      if (scale>0) {
        s2=0;
#ifdef ENABLE_NR
        x=scale;
        y=_rcpdp(x);
        y=y*(2.0-x*y);
        y=y*(2.0-x*y);
        y=y*(2.0-x*y);
#endif
        for (j=i+1;j<Ncols;j++) {
#ifndef ENABLE_NR
          /* U[j+i*Ncols]=U[j+i*Ncols]/scale; */
          U[2*j  +i*2*Ncols]/=scale;
          U[2*j+1+i*2*Ncols]/=scale;
#else
          /* U[j+i*Ncols]=U[j+i*Ncols]*y; */
          U[2*j  +i*2*Ncols]*=y;
          U[2*j+1+i*2*Ncols]*=y;
#endif
          /* s2+=U[j+i*Ncols]*conj(U[j+i*Ncols]); */
          xreal=U[2*j  +i*2*Ncols];
          ximag=U[2*j+1+i*2*Ncols];
          s2+=xreal*xreal+ximag*ximag;
        }
        j--;
        /* if (U[j+i*Ncols]<0) { */
        if (U[2*j  +i*2*Ncols]<0) {
          s=sqrt(s2);
        } else {
          s=-sqrt(s2);
        }
        /* half_norm_squared=conj(U[i+1+i*Ncols])*s-s2; */
        half_norm_squared_real= U[2*(i+1)  +i*2*Ncols]*s-s2;
        half_norm_squared_imag=-U[2*(i+1)+1+i*2*Ncols]*s;

        /* inv_half_norm_squared=1/half_norm_squared; */
        complex_dp_inv(half_norm_squared_real,half_norm_squared_imag,&inv_half_norm_squared_real,&inv_half_norm_squared_imag);

#pragma MUST_ITERATE(1,,)
        for (k=i+1;k<Ncols;k++) {
          /* U(i+1,k+1)=conj(U(i+1,k+1)); */
          U[2*k  +i*2*Ncols]= U[2*k  +i*2*Ncols];
          U[2*k+1+i*2*Ncols]=-U[2*k+1+i*2*Ncols];
          if (k==i+1) {
          	U[2*k  +i*2*Ncols]-=s;
          }
          /* superdiag[k]=conj(U[k+i*Ncols])/conj(half_norm_squared); */
          xreal= U[2*k  +i*2*Ncols];
          ximag=-U[2*k+1+i*2*Ncols];
          yreal= inv_half_norm_squared_real;
          yimag=-inv_half_norm_squared_imag;
          superdiag[2*k  ]=xreal*yreal-ximag*yimag;
          superdiag[2*k+1]=xreal*yimag+ximag*yreal;
        }
        if (i<Nrows-1) {
          for (j=i+1;j<Nrows;j++) {
        	si_real=0;
        	si_imag=0;
#pragma MUST_ITERATE(1,,)
        	for (k=i+1;k<Ncols;k++) {
        	  /* si+=U[k+i*Ncols]*U[k+j*Ncols]; */
          	  xreal=U[2*k  +i*2*Ncols];
          	  ximag=U[2*k+1+i*2*Ncols];
          	  yreal=U[2*k  +j*2*Ncols];
          	  yimag=U[2*k+1+j*2*Ncols];
          	  si_real+=xreal*yreal-ximag*yimag;
          	  si_imag+=xreal*yimag+ximag*yreal;
        	}
#pragma MUST_ITERATE(1,,)
        	for (k=i+1;k<Ncols;k++) {
        	  /* U[k+j*Ncols]+=si*superdiag[k]; */
          	  xreal=si_real;
          	  ximag=si_imag;
          	  yreal=superdiag[2*k  ];
          	  yimag=superdiag[2*k+1];
          	  U[2*k  +j*2*Ncols]+=xreal*yreal-ximag*yimag;
          	  U[2*k+1+j*2*Ncols]+=xreal*yimag+ximag*yreal;
        	}
          }
        }
      }	/* if (scale>0) */
#pragma MUST_ITERATE(1,,)
      for (k=i+1;k<Ncols;k++) {
    	/* U[k+i*Ncols]*=scale; */
      	U[2*k  +i*2*Ncols]*=scale;
      	U[2*k+1+i*2*Ncols]*=scale;
      }
    } /* if ((i<Nrows)&&(i!=Ncols-1)) */
  } /* for (i=0;i<Ncols;i++) */

  /* update V */
  /* V[Ncols*Ncols-1]=1; */
  V[2*(Ncols-1)  +(Ncols-1)*2*Ncols]=1;
  V[2*(Ncols-1)+1+(Ncols-1)*2*Ncols]=0;
  /* s=superdiag[Ncols-1]; */
  s_real=superdiag[2*(Ncols-1)  ];
  s_imag=superdiag[2*(Ncols-1)+1];

  for (i=Ncols-2;i>=0;i--) {
	/* if (s!=0) { */
	if (s_real!=0) {

	  /* inv=1/(conj(U[i+1+i*Ncols])*s); */
	  xreal= U[2*(i+1)  +i*2*Ncols];
	  ximag=-U[2*(i+1)+1+i*2*Ncols];
	  yreal=s_real;
	  yimag=s_imag;
	  zreal=xreal*yreal-ximag*yimag;
	  zimag=xreal*yimag+ximag*yreal;
	  complex_dp_inv(zreal,zimag,&yreal,&yimag);

#pragma MUST_ITERATE(1,,)
	  for (j=i+1;j<Ncols;j++) {
		/* V[i+j*Ncols]=U[j+i*Ncols]/(U[i+1+i*Ncols]*s); */
		xreal=U[2*j  +i*2*Ncols];
		ximag=U[2*j+1+i*2*Ncols];
		V[2*i  +j*2*Ncols]=xreal*yreal-ximag*yimag;
		V[2*i+1+j*2*Ncols]=xreal*yimag+ximag*yreal;
	  }
	  for (j=i+1;j<Ncols;j++) {
	    si_real=0;
	    si_imag=0;
#pragma MUST_ITERATE(1,,)
	    for (k=i+1;k<Ncols;k++) {
	      /* si+=conj(U[k+i*Ncols])*V[j+k*Ncols]; */
		  xreal= U[2*k  +i*2*Ncols];
		  ximag=-U[2*k+1+i*2*Ncols];
		  yreal= V[2*j  +k*2*Ncols];
		  yimag= V[2*j+1+k*2*Ncols];
		  si_real+=xreal*yreal-ximag*yimag;
		  si_imag+=xreal*yimag+ximag*yreal;
	    }
#pragma MUST_ITERATE(1,,)
	    for (k=i+1;k<Ncols;k++) {
	      /* V[j+k*Ncols]+=si*V[i+k*Ncols]; */
		  xreal=si_real;
		  ximag=si_imag;
		  yreal=V[2*i  +k*2*Ncols];
		  yimag=V[2*i+1+k*2*Ncols];
		  V[2*j  +k*2*Ncols]+=xreal*yreal-ximag*yimag;
		  V[2*j+1+k*2*Ncols]+=xreal*yimag+ximag*yreal;
	    }
	  }
	} /* if (s!=0) */
#pragma MUST_ITERATE(1,,)
	for (j=i+1;j<Ncols;j++) {
	  /* V[j+i*Ncols]=0; */
	  V[2*j  +i*2*Ncols]=0;
	  V[2*j+1+i*2*Ncols]=0;
	  /* V[i+j*Ncols]=0; */
	  V[2*i  +j*2*Ncols]=0;
	  V[2*i+1+j*2*Ncols]=0;
	}
	/* V[i+i*Ncols]=1; */
	V[2*i  +i*2*Ncols]=1;
	V[2*i+1+i*2*Ncols]=0;
	/* s=superdiag[i]; */
	s_real=superdiag[2*i  ];
	s_imag=superdiag[2*i+1];
  } /* for (i=Ncols-2;i>=0;i--) */

#ifndef ENABLE_REDUCED_FORM
  /* expand U to from Nrows x Ncols to */
  /*                  Nrows x Nrows    */
  if (Nrows>Ncols) {
	for (i=Nrows-1;i>=0;i--) {
	  for (j=Nrows-1;j>=0;j--) {
		if (j<=Ncols-1) {
		/* U[j+i*Nrows]=U[j+i*Ncols]; */
		  U[2*j  +i*2*Nrows]=U[2*j  +i*2*Ncols];
		  U[2*j+1+i*2*Nrows]=U[2*j+1+i*2*Ncols];
		} else {
		  /* U[j+i*Nrows]=0; */
		  U[2*j  +i*2*Nrows]=0;
		  U[2*j+1+i*2*Nrows]=0;
		}
	  }
	}
  }

  /* update U */
  for (i=Ncols-1;i>=0;i--) {
	/* s=diag[i]; */
	s=diag[2*i  ];

#ifndef ENABLE_NR
	inv_s=1/s;
#else
	inv_s=_rcpdp(s);
	inv_s=inv_s*(2.0-s*inv_s);
	inv_s=inv_s*(2.0-s*inv_s);
	inv_s=inv_s*(2.0-s*inv_s);
#endif

    /* inv_U_x_s=1/(conj(U[i+i*Nrows])*s); */
	xreal= U[2*i  +i*2*Nrows]*s;
	ximag=-U[2*i+1+i*2*Nrows]*s;
    complex_dp_inv(xreal,ximag,&inv_U_x_s_real,&inv_U_x_s_imag);

#pragma MUST_ITERATE(1,,)
	for (j=i+1;j<Ncols;j++) {
	  /* U[j+i*Nrows]=0; */
	  U[2*j  +i*2*Nrows]=0;
	  U[2*j+1+i*2*Nrows]=0;
	}
    /* if (s!=0) { */
	if (fabs(s)>ZERO_TOLERANCE) {

      for (j=i+1;j<Nrows;j++) {
      	/* si=0; */
      	si_real=0;
      	si_imag=0;
#pragma MUST_ITERATE(1,,)
    	for (k=i+1;k<Nrows;k++) {
      	  /* si+=conj(U[i+k*Nrows])*U[j+k*Nrows]; */
          xreal= U[2*i  +k*2*Nrows];
          ximag=-U[2*i+1+k*2*Nrows];
          yreal= U[2*j +k*2*Nrows];
          yimag= U[2*j+1+k*2*Nrows];
          si_real+=xreal*yreal-ximag*yimag;
          si_imag+=xreal*yimag+ximag*yreal;
    	}
    	/* si=si/(conj(U[i+i*Nrows])*s); */
        xreal=si_real;
        ximag=si_imag;
        yreal=inv_U_x_s_real;
        yimag=inv_U_x_s_imag;
        si_real=xreal*yreal-ximag*yimag;
        si_imag=xreal*yimag+ximag*yreal;

        #pragma MUST_ITERATE(1,,)
    	for (k=i;k<Nrows;k++) {
      	  /* U[j+k*Nrows]+=si*U[i+k*Nrows]; */
      	  xreal=si_real;
      	  ximag=si_imag;
      	  yreal=U[2*i  +k*2*Nrows];
      	  yimag=U[2*i+1+k*2*Nrows];
      	  U[2*j  +k*2*Nrows]+=xreal*yreal-ximag*yimag;
      	  U[2*j+1+k*2*Nrows]+=xreal*yimag+ximag*yreal;
    	}
      }
      /* initial U1 */
      if (i==Ncols-1) {
        /* inv=1/(conj(U[i+i*Nrows])*s); */
    	xreal= U[2*i  +i*2*Nrows]*s;
    	ximag=-U[2*i+1+i*2*Nrows]*s;
    	complex_dp_inv(xreal,ximag,&yreal1,&yimag1);

    	for (j=i;j<Nrows;j++) {
    	  for (k=Nrows-1;k>=i+1;k--) {
    	    /* U[k+j*Nrows]=U[i+j*Nrows]*conj(U[i+k*Nrows])/(conj(U[i+i*Nrows])*s); */
      		xreal= U[2*i  +j*2*Nrows];
      		ximag= U[2*i+1+j*2*Nrows];
      		yreal= U[2*i  +k*2*Nrows];
      		yimag=-U[2*i+1+k*2*Nrows];
      	    zreal=xreal*yreal-ximag*yimag;
      	    zimag=xreal*yimag+ximag*yreal;
      	    xreal=zreal;
      	    ximag=zimag;
       		U[2*k  +j*2*Nrows]=xreal*yreal1-ximag*yimag1;
       		U[2*k+1+j*2*Nrows]=xreal*yimag1+ximag*yreal1;
    	    if (j==k) {
      	      /* U[k+j*Nrows]+=1; */
      	      U[2*k  +j*2*Nrows]+=1;
    	    }
    	  }
    	}
      }
#pragma MUST_ITERATE(1,,)
      for (j=i;j<Nrows;j++) {
    	/* U[i+j*Nrows]=U[i+j*Nrows]/s; */
    	U[2*i  +j*2*Nrows]*=inv_s;
    	U[2*i+1+j*2*Nrows]*=inv_s;
      }
    } else { /* if (s!=0) */
      if (i==Ncols-1) {
#pragma MUST_ITERATE(1,,)
       	for (k=1;k<=Nrows-Ncols;k++) {
      	  /* U[i+k+(i+k)*Nrows]=1; */
      	  U[2*(i+k)  +(i+k)*2*Nrows]=1;
      	  U[2*(i+k)+1+(i+k)*2*Nrows]=0;
       	}
      }
#pragma MUST_ITERATE(1,,)
      for (j=i;j<Nrows;j++) {
      	/* U[i+j*Nrows]=0; */
      	U[2*i  +j*2*Nrows]=0;
      	U[2*i+1+j*2*Nrows]=0;
      }
    } /* if (s!=0) */
    /* U[i+i*Nrows]+=1; */
	U[2*i  +i*2*Nrows]+=1;
  } /* for (i=Ncols-1;i>=0;i--) */
#else /* #ifndef ENABLE_REDUCED_FORM */

  /* update U */
  for (i=Ncols-1;i>=0;i--) {
	/* s=diag[i]; */
	s=diag[2*i  ];

#ifndef ENABLE_NR
	inv_s=1/s;
#else
	inv_s=_rcpdp(s);
	inv_s=inv_s*(2.0-s*inv_s);
	inv_s=inv_s*(2.0-s*inv_s);
	inv_s=inv_s*(2.0-s*inv_s);
#endif

    /* inv_U_x_s=1/(conj(U[i+i*Ncols])*s); */
	xreal= U[2*i  +i*2*Ncols]*s;
	ximag=-U[2*i+1+i*2*Ncols]*s;
    complex_dp_inv(xreal,ximag,&inv_U_x_s_real,&inv_U_x_s_imag);

	#pragma MUST_ITERATE(1,,)
	for (j=i+1;j<Ncols;j++) {
	  /* U[j+i*Ncols]=0; */
	  U[2*j  +i*2*Ncols]=0;
	  U[2*j+1+i*2*Ncols]=0;
	}
    /* if (s!=0) { */
	if (fabs(s)>ZERO_TOLERANCE) {
      for (j=i+1;j<Ncols;j++) {
    	si_real=0;
    	si_imag=0;

#pragma MUST_ITERATE(1,,)
    	for (k=i+1;k<Nrows;k++) {
      	  /* si+=conj(U[i+k*Ncols])*U[j+k*Ncols]; */
      	  xreal= U[2*i  +k*2*Ncols];
      	  ximag=-U[2*i+1+k*2*Ncols];
      	  yreal= U[2*j  +k*2*Ncols];
      	  yimag= U[2*j+1+k*2*Ncols];
      	  si_real+=xreal*yreal-ximag*yimag;
      	  si_imag+=xreal*yimag+ximag*yreal;
    	}
    	/* si=si/(conj(U[i+i*Ncols])*s); */
        xreal=si_real;
        ximag=si_imag;
        yreal=inv_U_x_s_real;
        yimag=inv_U_x_s_imag;
        si_real=xreal*yreal-ximag*yimag;
        si_imag=xreal*yimag+ximag*yreal;

#pragma MUST_ITERATE(1,,)
    	for (k=i;k<Nrows;k++) {
      	  /* U[j+k*Ncols]+=si*U[i+k*Ncols]; */
      	  xreal=si_real;
      	  ximag=si_imag;
      	  yreal=U[2*i  +k*2*Ncols];
      	  yimag=U[2*i+1+k*2*Ncols];
      	  U[2*j  +k*2*Ncols]+=xreal*yreal-ximag*yimag;
      	  U[2*j+1+k*2*Ncols]+=xreal*yimag+ximag*yreal;
    	}
      }
#pragma MUST_ITERATE(1,,)
       for (j=i;j<Nrows;j++) {
    	/* U[i+j*Ncols]=U[i+j*Ncols]/s; */
    	U[2*i  +j*2*Ncols]*=inv_s;
    	U[2*i+1+j*2*Ncols]*=inv_s;
      }
    } else { /* if (s!=0) */
#pragma MUST_ITERATE(1,,)
      for (j=i;j<Nrows;j++) {
      	/* U[i+j*Ncols]=0; */
      	U[2*i  +j*2*Ncols]=0;
      	U[2*i+1+j*2*Ncols]=0;
      }
    } /* if (s!=0) */
    /* U[i+i*Ncols]+=1; */
	U[2*i  +i*2*Ncols]+=1;
  } /* for (i=Ncols-1;i>=0;i--) */
#endif

  return 0;
}

static int DSPF_dp_bidiag_to_diag_cmplx(const int Nrows,const int Ncols,double *restrict U,double *restrict V,double *restrict diag,double *restrict superdiag)
{

  int row,i,k,m,rotation_test,iter,total_iter;
  double x,y,epsilon;
  double xreal,ximag,yreal,yimag,zreal,zimag;
  double c_real,c_imag,s_real,s_imag,f_real,f_imag,g_real,g_imag,h_real,h_imag;
  double x_real,x_imag,y_real,y_imag,z_real,z_imag;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)U % 8 == 0);
  _nassert((int)V % 8 == 0);
  _nassert((int)diag % 8 == 0);
  _nassert((int)superdiag % 8 == 0);

  iter=0;
  total_iter=0;
  /* ------------------------------------------------------------------- */
  /* find max in col                                                     */
  /* ------------------------------------------------------------------- */
  x=0;
#pragma MUST_ITERATE(1,,)
  for (i=0;i<Ncols;i++) {
	/* y=fabs(diag[i])+fabs(superdiag[i]); */
	y=sqrt(diag[2*i+1]*diag[2*i+1]+diag[2*i]*diag[2*i])+sqrt(superdiag[2*i+1]*superdiag[2*i+1]+superdiag[2*i]*superdiag[2*i]);
	if (x<y) {
	  x=y;
	}
  }
  epsilon=DBL_EPSILON*x;
#pragma MUST_ITERATE(1,,)
  for (k=Ncols-1;k>=0;k--) {
	total_iter+=iter;
	iter=0;
#pragma MUST_ITERATE(1,,)
    while (1==1) {
      rotation_test=1;
#pragma MUST_ITERATE(1,,)
      for (m=k;m>=0;m--) {
      	/* if (fabs(superdiag[m])<=epsilon) { */
      	if (sqrt(superdiag[2*m+1]*superdiag[2*m+1]+superdiag[2*m]*superdiag[2*m])<=epsilon) {
    	  rotation_test=0;
    	  break;
    	}
    	/* if (fabs(diag[m-1])<=epsilon) { */
    	if (sqrt(diag[2*(m-1)+1]*diag[2*(m-1)+1]+diag[2*(m-1)]*diag[2*(m-1)])<=epsilon) {
    	  break;
    	}
      } /* for (m=k;m>=0;m--) */
      if (rotation_test) {
      	/* c=0; */
      	/* s=1; */
      	c_real=0;
      	c_imag=0;
      	s_real=1;
      	s_imag=0;
#pragma MUST_ITERATE(1,,)
    	for (i=m;i<=k;i++) {
      	  /* f=s*superdiag[i]; */
      	  xreal=s_real;
      	  ximag=s_imag;
      	  yreal=superdiag[2*i  ];
      	  yimag=superdiag[2*i+1];
      	  f_real=xreal*yreal-ximag*yimag;
      	  f_imag=xreal*yimag+ximag*yreal;

    	  /* superdiag[i]=c*superdiag[i]; */
    	  xreal=c_real;
    	  ximag=c_imag;
    	  yreal=superdiag[2*i  ];
    	  yimag=superdiag[2*i+1];
    	  superdiag[2*i  ]=xreal*yreal-ximag*yimag;
    	  superdiag[2*i+1]=xreal*yimag+ximag*yreal;

    	  /* if (fabs(f)<=epsilon) { */
    	  if (sqrt(f_real*f_real+f_imag*f_imag)<=epsilon) {
    		break;
    	  }

    	  /* g=diag[i]; */
    	  g_real=diag[2*i  ];
    	  g_imag=diag[2*i+1];

    	  /* h=sqrt(f*f+g*g); */
          xreal=f_real*f_real-f_imag*f_imag+g_real*g_real-g_imag*g_imag;
          ximag=2*(f_real*f_imag+g_real*g_imag);
    	  complex_dp_sqrt(xreal,ximag,&h_real,&h_imag);

    	  /* diag[i]=h; */
    	  diag[2*i  ]=h_real;
    	  diag[2*i+1]=h_imag;

    	  /* c=g/h; */
    	  complex_dp_div(g_real,g_imag,h_real,h_imag,&c_real,&c_imag);
    	  /* s=-f/h; */
    	  complex_dp_div(f_real,f_imag,h_real,h_imag,&s_real,&s_imag);
    	  s_real=-s_real;
    	  s_imag=-s_imag;

#ifndef ENABLE_REDUCED_FORM
#pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Nrows;row++) {
      		/* y=U[m-1+row*Nrows]; */
      		y_real=U[2*(m-1)  +row*2*Nrows];
      		y_imag=U[2*(m-1)+1+row*2*Nrows];
      		/* z=U[i+row*Nrows]; */
      		z_real=U[2*i  +row*2*Nrows];
      		z_imag=U[2*i+1+row*2*Nrows];
      		/* U[m-1+row*Nrows]= y*c+z*s; */
      		U[2*(m-1)  +row*2*Nrows]=y_real*c_real-y_imag*c_imag+z_real*s_real-z_imag*s_imag;
      		U[2*(m-1)+1+row*2*Nrows]=y_real*c_imag+y_imag*c_real+z_real*s_imag+z_imag*s_real;
      		/* U[i+row*Nrows]  =-y*s+z*c; */
      		U[2*i  +row*2*Nrows]=-y_real*s_real+y_imag*s_imag+z_real*c_real-z_imag*c_imag;
      		U[2*i+1+row*2*Nrows]=-y_real*s_imag-y_imag*s_real+z_real*c_imag+z_imag*c_real;
    	  }
#else
#pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Nrows;row++) {
      		/* y=U[m-1+row*Ncols]; */
      		y_real=U[2*(m-1)  +row*2*Ncols];
      		y_imag=U[2*(m-1)+1+row*2*Ncols];
      		/* z=U[i+row*Ncols]; */
      		z_real=U[2*i  +row*2*Ncols];
      		z_imag=U[2*i+1+row*2*Ncols];
      		/* U[m-1+row*Ncols]= y*c+z*s; */
      		U[2*(m-1)  +row*2*Ncols]=y_real*c_real-y_imag*c_imag+z_real*s_real-z_imag*s_imag;
      		U[2*(m-1)+1+row*2*Ncols]=y_real*c_imag+y_imag*c_real+z_real*s_imag+z_imag*s_real;
      		/* U[i+row*Ncols]  =-y*s+z*c; */
      		U[2*i  +row*2*Ncols]=-y_real*s_real+y_imag*s_imag+z_real*c_real-z_imag*c_imag;
      		U[2*i+1+row*2*Ncols]=-y_real*s_imag-y_imag*s_real+z_real*c_imag+z_imag*c_real;
    	  }
#endif
     	} /* for (i=m;i<=k;i++) */
      } /* if (rotation_test) */
      /* z=diag[k]; */
      z_real=diag[2*k  ];
      z_imag=diag[2*k+1];

      if (m==k) {
      	/* if (z<0) { */
      	if (z_real<0) {
      	  /* diag[k]=-z; */
      	  diag[2*k  ]=-z_real;
      	  diag[2*k+1]=-z_imag;
#pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Ncols;row++) {
      		/* V[k+row*Ncols]=-V[k+row*Ncols]; */
      		V[2*k  +row*2*Ncols]=-V[2*k  +row*2*Ncols];
      		V[2*k+1+row*2*Ncols]=-V[2*k+1+row*2*Ncols];
    	  }
    	} /* if (z>0) */
    	break;
      } else { /* if (m==k) */
        if (iter>=MAX_ITERATION_COUNT) {
          return -1;
        }
        iter++;
    	/* x=diag[m]; */
        x_real=diag[2*m  ];
        x_imag=diag[2*m+1];
    	/* y=diag[k-1]; */
        y_real=diag[2*(k-1)  ];
        y_imag=diag[2*(k-1)+1];
    	/* g=superdiag[k-1]; */
        g_real=superdiag[2*(k-1)  ];
        g_imag=superdiag[2*(k-1)+1];
    	/* h=superdiag[k]; */
        h_real=superdiag[2*k  ];
        h_imag=superdiag[2*k+1];
    	/* f=((y-z)*(y+z)+(g-h)*(g+h))/(2*h*y); */
        xreal=y_real*y_real-y_imag*y_imag-(z_real*z_real-z_imag*z_imag)+g_real*g_real-g_imag*g_imag-(h_real*h_real-h_imag*h_imag);
        ximag=2*(y_real*y_imag-z_real*z_imag+g_real*g_imag-h_real*h_imag);
        yreal=2*(h_real*y_real-h_imag*y_imag);
        yimag=2*(h_real*y_imag+h_imag*y_real);
        complex_dp_div(xreal,ximag,yreal,yimag,&f_real,&f_imag);

    	/* g=sqrt(f*f+1); */
        xreal=f_real*f_real-f_imag*f_imag+1;
        ximag=2*f_real*f_imag;
        complex_dp_sqrt(xreal,ximag,&g_real,&g_imag);

    	/* if (f<0) { */
        if (f_real<0) {
    	  /* g=-g; */
          g_real=-g_real;
          g_imag=-g_imag;
    	}

    	/* f=((x-z)*(x+z)+h*(y/(f+g)-h))/x; */
        xreal=y_real;
        ximag=y_imag;
        yreal=f_real+g_real;
        yimag=f_imag+g_imag;
        complex_dp_div(xreal,ximag,yreal,yimag,&zreal,&zimag);
        xreal=h_real;
        ximag=h_imag;
        yreal=(zreal-h_real);
        yimag=(zimag-h_imag);
        zreal=xreal*yreal-ximag*yimag;
        zimag=xreal*yimag+ximag*yreal;
        xreal=x_real*x_real-x_imag*x_imag-(z_real*z_real-z_imag*z_imag)+zreal;
        ximag=2*(x_real*x_imag-z_real*z_imag)+zimag;
        yreal=x_real;
        yimag=x_imag;
        complex_dp_div(xreal,ximag,yreal,yimag,&f_real,&f_imag);

    	/* next QR transformation */
    	/* c=1; */
    	/* s=1; */
        c_real=1;
        c_imag=0;
        s_real=1;
        s_imag=0;
#pragma MUST_ITERATE(1,,)
    	for (i=m+1;i<=k;i++) {
    	  /* g=superdiag[i]; */
    	  g_real=superdiag[2*i  ];
    	  g_imag=superdiag[2*i+1];

    	  /* y=diag[i]; */
    	  y_real=diag[2*i  ];
    	  y_imag=diag[2*i+1];

    	  /* h=s*g; */
    	  h_real=s_real*g_real-s_imag*g_imag;
    	  h_imag=s_real*g_imag+s_imag*g_real;

    	  /* g=g*c; */
    	  xreal=g_real;
    	  ximag=g_imag;
    	  g_real=xreal*c_real-ximag*c_imag;
    	  g_imag=xreal*c_imag+ximag*c_real;

    	  /* z=sqrt(f*f+h*h); */
    	  xreal=f_real*f_real-f_imag*f_imag+h_real*h_real-h_imag*h_imag;
    	  ximag=2*(f_real*f_imag+h_real*h_imag);
    	  complex_dp_sqrt(xreal,ximag,&z_real,&z_imag);

    	  /* superdiag[i-1]=z; */
    	  superdiag[2*(i-1)  ]=z_real;
    	  superdiag[2*(i-1)+1]=z_imag;

    	  /* c=f/z; */
    	  complex_dp_div(f_real,f_imag,z_real,z_imag,&c_real,&c_imag);

    	  /* s=h/z; */
    	  complex_dp_div(h_real,h_imag,z_real,z_imag,&s_real,&s_imag);

    	  /* f= x*c+g*s; */
    	  f_real=x_real*c_real-x_imag*c_imag+g_real*s_real-g_imag*s_imag;
    	  f_imag=x_real*c_imag+x_imag*c_real+g_real*s_imag+g_imag*s_real;

    	  /* g=-x*s+g*c; */
    	  zreal=-x_real*s_real+x_imag*s_imag+g_real*c_real-g_imag*c_imag;
    	  g_imag=-x_real*s_imag-x_imag*s_real+g_real*c_imag+g_imag*c_real;
    	  g_real=zreal;

    	  /* h=y*s; */
    	  h_real=y_real*s_real-y_imag*s_imag;
    	  h_imag=y_real*s_imag+y_imag*s_real;

    	  /* y=c*y; */
    	  zreal=c_real*y_real-c_imag*y_imag;
    	  y_imag=c_real*y_imag+c_imag*y_real;
    	  y_real=zreal;

    	  #pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Ncols;row++) {
      		/* x=V[i-1+row*Ncols]; */
      		x_real=V[2*(i-1)  +row*2*Ncols];
      		x_imag=V[2*(i-1)+1+row*2*Ncols];

      		/* z=V[i+row*Ncols]; */
      		z_real=V[2*i  +row*2*Ncols];
      		z_imag=V[2*i+1+row*2*Ncols];

      		/* V[i-1+row*Ncols]= x*c+z*s; */
      		V[2*(i-1)  +row*2*Ncols]=x_real*c_real-x_imag*c_imag+z_real*s_real-z_imag*s_imag;
      		V[2*(i-1)+1+row*2*Ncols]=x_real*c_imag+x_imag*c_real+z_real*s_imag+z_imag*s_real;

      		/* V[i+row*Ncols]  =-x*s+z*c; */
      		V[2*i  +row*2*Ncols]= -x_real*s_real+x_imag*s_imag+z_real*c_real-z_imag*c_imag;
      		V[2*i+1+row*2*Ncols]= -x_real*s_imag-x_imag*s_real+z_real*c_imag+z_imag*c_real;
    	  }

    	  /* z=sqrt(f*f+h*h); */
    	  xreal=f_real*f_real-f_imag*f_imag+h_real*h_real-h_imag*h_imag;
    	  ximag=2*(f_real*f_imag+h_real*h_imag);
    	  complex_dp_sqrt(xreal,ximag,&z_real,&z_imag);

    	  /* diag[i-1]=z; */
    	  diag[2*(i-1)  ]=z_real;
    	  diag[2*(i-1)+1]=z_imag;

    	  /* if (z!=0) { */
    	  if (sqrt(z_real*z_real+z_imag*z_imag)>ZERO_TOLERANCE) {

    		/* c=f/z; */
    		complex_dp_div(f_real,f_imag,z_real,z_imag,&c_real,&c_imag);

    		/* s=h/z; */
    		complex_dp_div(h_real,h_imag,z_real,z_imag,&s_real,&s_imag);
    	  }

    	  /* f= c*g+s*y; */
    	  f_real=c_real*g_real-c_imag*g_imag+s_real*y_real-s_imag*y_imag;
    	  f_imag=c_real*g_imag+c_imag*g_real+s_real*y_imag+s_imag*y_real;

    	  /* x=-s*g+c*y; */
    	  x_real=-s_real*g_real+s_imag*g_imag+c_real*y_real-c_imag*y_imag;
    	  x_imag=-s_real*g_imag-s_imag*g_real+c_real*y_imag+c_imag*y_real;

#ifndef ENABLE_REDUCED_FORM
#pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Nrows;row++) {
    	   	/* y=U[i-1+row*Nrows]; */
    	    y_real=U[2*(i-1)  +row*2*Nrows];
    	    y_imag=U[2*(i-1)+1+row*2*Nrows];

    	    /* z=U[i+row*Nrows]; */
    	    z_real=U[2*i  +row*2*Nrows];
    	    z_imag=U[2*i+1+row*2*Nrows];

    	    /* U[i-1+row*Nrows]= c*y+s*z; */
    	    U[2*(i-1)  +row*2*Nrows]=c_real*y_real-c_imag*y_imag+s_real*z_real-s_imag*z_imag;
    	    U[2*(i-1)+1+row*2*Nrows]=c_real*y_imag+c_imag*y_real+s_real*z_imag+s_imag*z_real;

    	    /* U[i+row*Nrows]  =-s*y+c*z; */
    	    U[2*i  +row*2*Nrows]=-s_real*y_real+s_imag*y_imag+c_real*z_real-c_imag*z_imag;
    	    U[2*i+1+row*2*Nrows]=-s_real*y_imag-s_imag*y_real+c_real*z_imag+c_imag*z_real;
    	  }
#else
#pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Nrows;row++) {
      		/* y=U[i-1+row*Ncols]; */
      		y_real=U[2*(i-1)  +row*2*Ncols];
      		y_imag=U[2*(i-1)+1+row*2*Ncols];
      		/* z=U[i+row*Ncols]; */
      		z_real=U[2*i  +row*2*Ncols];
      		z_imag=U[2*i+1+row*2*Ncols];
      		/* U[i-1+row*Ncols]= c*y+s*z; */
      		U[2*(i-1)  +row*2*Ncols]=c_real*y_real-c_imag*y_imag+s_real*z_real-s_imag*z_imag;
      		U[2*(i-1)+1+row*2*Ncols]=c_real*y_imag+c_imag*y_real+s_real*z_imag+s_imag*z_real;
      		/* U[i+row*Ncols]  =-s*y+c*z; */
      		U[2*i  +row*2*Ncols]=-s_real*y_real+s_imag*y_imag+c_real*z_real-c_imag*z_imag;
      		U[2*i+1+row*2*Ncols]=-s_real*y_imag-s_imag*y_real+c_real*z_imag+c_imag*z_real;
       	  }
#endif
    	} /* for (i=m+1;i<=k;i++) */

    	/* superdiag[m]=0; */
    	superdiag[2*m  ]=0;
    	superdiag[2*m+1]=0;

    	/* superdiag[k]=f; */
    	superdiag[2*k  ]=f_real;
    	superdiag[2*k+1]=f_imag;

    	/* diag[k]=x; */
    	diag[2*k  ]=x_real;
    	diag[2*k+1]=x_imag;

      } /* if (m==k) */
    } /* while (1==1) */
  } /* for (k=Ncols-1:k>=0;k--) */

  return total_iter;
}

static int DSPF_dp_sort_singular_values_cmplx(const int Nrows,const int Ncols,double *restrict U,double *restrict V,double *restrict singular_values)
{
  int i,j,row,max_index;
  double tempr,tempi;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)U % 8 == 0);
  _nassert((int)V % 8 == 0);
  _nassert((int)singular_values % 8 == 0);

#pragma MUST_ITERATE(1,,)
  for (i=0;i<Ncols-1;i++) {
	max_index=i;
#pragma MUST_ITERATE(1,,)
	for (j=i+1;j<Ncols;j++) {
	  /* (if (singular_values[j]>singular_values[max_index]) { */
 	  if (sqrt(singular_values[2*j+1]*singular_values[2*j+1]+singular_values[2*j]*singular_values[2*j])>sqrt(singular_values[2*max_index+1]*singular_values[2*max_index+1]+singular_values[2*max_index]*singular_values[2*max_index])) {
		max_index=j;
	  }
	}
	if (max_index!=i) {
	  tempr=singular_values[2*i  ];
	  tempi=singular_values[2*i+1];
	  singular_values[2*i  ]=singular_values[2*max_index  ];
	  singular_values[2*i+1]=singular_values[2*max_index+1];
	  singular_values[2*max_index  ]=tempr;
	  singular_values[2*max_index+1]=tempi;
#ifndef ENABLE_REDUCED_FORM
#pragma MUST_ITERATE(1,,)
	  for (row=0;row<Nrows;row++) {
		tempr=U[2*max_index  +row*2*Nrows];
		tempi=U[2*max_index+1+row*2*Nrows];
		U[2*max_index  +row*2*Nrows]=U[2*i  +row*2*Nrows];
		U[2*max_index+1+row*2*Nrows]=U[2*i+1+row*2*Nrows];
		U[2*i  +row*2*Nrows]=tempr;
		U[2*i+1+row*2*Nrows]=tempi;
	  }
#else
#pragma MUST_ITERATE(1,,)
	  for (row=0;row<Nrows;row++) {
		/* temp=U[max_index+row*Ncols]; */
		tempr=U[2*max_index  +row*2*Ncols];
		tempi=U[2*max_index+1+row*2*Ncols];
		/* U[max_index+row*Ncols]=U[i+row*Ncols]; */
		U[2*max_index  +row*2*Ncols]=U[2*i  +row*2*Ncols];
		U[2*max_index+1+row*2*Ncols]=U[2*i+1+row*2*Ncols];
		/* U[i+row*Ncols]=temp; */
		U[2*i  +row*2*Ncols]=tempr;
		U[2*i+1+row*2*Ncols]=tempi;
	  }
#endif
#pragma MUST_ITERATE(1,,)
	  for (row=0;row<Ncols;row++) {
		tempr=V[2*max_index  +row*2*Ncols];
		tempi=V[2*max_index+1+row*2*Ncols];
		V[2*max_index  +row*2*Ncols]=V[2*i  +row*2*Ncols];
		V[2*max_index+1+row*2*Ncols]=V[2*i+1+row*2*Ncols];
		V[2*i  +row*2*Ncols]=tempr;
		V[2*i+1+row*2*Ncols]=tempi;
	  }
	}
  }

  return 0;
}

static void complex_dp_sqrt(double x_real,double x_imag,double *z_real,double *z_imag) {

  double x_mag,z_mag;
  double x_angle,z_angle;

  /* magnitude */
  x_mag=sqrt(x_real*x_real+x_imag*x_imag);
  z_mag=sqrt(x_mag);

  /* angle */
#ifndef ENABLE_MATHLIB
  x_angle=atan2(x_imag,x_real);
#else
  x_angle=atan2dp(x_imag,x_real);
#endif
  z_angle=x_angle/2;

  /* results */
#ifndef ENABLE_MATHLIB
  *z_real=cos(z_angle)*z_mag;
  *z_imag=sin(z_angle)*z_mag;
#else
  *z_real=cosdp(z_angle)*z_mag;
  *z_imag=sindp(z_angle)*z_mag;
#endif
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

/* ======================================================================= */
/*  End of file:  DSPF_dp_svd_cmplx.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
