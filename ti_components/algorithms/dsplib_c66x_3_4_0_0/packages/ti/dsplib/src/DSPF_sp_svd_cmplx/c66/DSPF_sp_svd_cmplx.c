/* ======================================================================= */
/* DSPF_sp_svd_cmplx.c -- singular value decomposition                     */
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
#include <c6x.h>

#pragma CODE_SECTION(DSPF_sp_svd_cmplx,".text:optimized");
#pragma CODE_SECTION(DSPF_sp_convert_to_bidiag_cmplx,".text:optimized");
#pragma CODE_SECTION(DSPF_sp_bidiag_to_diag_cmplx,".text:optimized");
#pragma CODE_SECTION(DSPF_sp_sort_singular_values_cmplx,".text:optimized");

#include "DSPF_sp_svd_cmplx.h"

#define ENABLE_NR   1
#define ENABLE_MATHLIB 1

#define MAX_ITERATION_COUNT 30
#define ZERO_TOLERANCE 1.0e-6
//#define ENABLE_REDUCED_FORM 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2sp/c66/atan2sp.h>
#include <ti/mathlib/src/cossp/c66/cossp.h>
#include <ti/mathlib/src/sinsp/c66/sinsp.h>
#endif

#define zero          _ftof2(0,0)

#ifndef _LITTLE_ENDIAN
#define cmpy(a,b)     _complex_mpysp(a,b)
#define ccmpy(a,b)    _complex_conjugate_mpysp(a,b)
#define real(a)       _hif2(a)
#define imag(a)       _lof2(a)
#define one           _ftof2(1,0)
#define real_to_f2(a) _ftof2(a,0)
#else
#define cmpy(a,b)     _ftof2(_lof2(_complex_mpysp(a,b)),-_hif2(_complex_mpysp(a,b)))
#define ccmpy(a,b)    _ftof2(-_lof2(_complex_conjugate_mpysp(a,b)),_hif2(_complex_conjugate_mpysp(a,b)))
#define real(a)       _lof2(a)
#define imag(a)       _hif2(a)
#define one           _ftof2(0,1)
#define real_to_f2(a) _ftof2(0,a)
#endif

static int DSPF_sp_convert_to_bidiag_cmplx(const int Nrows,const int Ncols,float *restrict U,float *restrict V,float *restrict diag,float *restrict superdiag);
static int DSPF_sp_bidiag_to_diag_cmplx(const int Nrows,const int Ncols,float *restrict U,float *restrict V,float *restrict diag,float *restrict superdiag);
static int DSPF_sp_sort_singular_values_cmplx(const int Nrows,const int Ncols,float *restrict U,float *restrict V,float *restrict singular_values);

static void complex_sp_sqrt(__float2_t cx,__float2_t *cz);
static void complex_sp_inv(__float2_t cx,__float2_t *cz);
static void complex_sp_div(__float2_t cx,__float2_t cy,__float2_t *cz);

int DSPF_sp_svd_cmplx(const int Nrows,const int Ncols,float *restrict A,float *restrict U,float *restrict V,float *restrict U1,float *restrict diag,float *restrict superdiag)
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
    memcpy(U,A,sizeof(float)*Nrows*2*Ncols);
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
  DSPF_sp_convert_to_bidiag_cmplx(Nrows1,Ncols1,U,V,diag,superdiag);

  /* ------------------------------------------------------------------- */
  /* convert bidiagonal to diagonal using Givens rotations               */
  /* ------------------------------------------------------------------- */
  status=DSPF_sp_bidiag_to_diag_cmplx(Nrows1,Ncols1,U,V,diag,superdiag);

  /* ------------------------------------------------------------------- */
  /* sort singular values in descending order                            */
  /* ------------------------------------------------------------------- */
  DSPF_sp_sort_singular_values_cmplx(Nrows1,Ncols1,U,V,diag);

  /* ------------------------------------------------------------------- */
  /* switch U and V                                                      */
  /* ------------------------------------------------------------------- */
  if (Ncols>Nrows) {
#ifndef ENABLE_REDUCED_FORM
	memcpy(U1,V,sizeof(float)*Nrows*2*Nrows);
	memcpy(V,U,sizeof(float)*Ncols*2*Ncols);
	memcpy(U,U1,sizeof(float)*Nrows*2*Nrows);
#else
	memcpy(U1,V,sizeof(float)*Ncols*2*Ncols);
	memcpy(V,U,sizeof(float)*Nrows*2*Ncols);
	memcpy(U,U1,sizeof(float)*Nrows*2*Ncols);
#endif
  }
  /* get Hermitian of diagonal entries */
  for (row=0;row<Nrows;row++) {
    diag[2*row+1]=-diag[2*row+1];
  }

  return status;
}

static int DSPF_sp_convert_to_bidiag_cmplx(const int Nrows,const int Ncols,float *restrict U,float *restrict V,float *restrict diag,float *restrict superdiag)
{
  int i,j,k,addr;
  float scale;
  float x,y;
  float s,inv_s,s2;
  __float2_t *UU,*VV,*ddiag,*ssuperdiag;
  __float2_t s_f2,s2_f2,si,half_norm_squared,inv_half_norm_squared,inv_scale,inv_UU_x_s,temp;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)U % 8 == 0);
  _nassert((int)V % 8 == 0);
  _nassert((int)diag % 8 == 0);
  _nassert((int)superdiag % 8 == 0);


  /* initialize __float2_t arrays to overlay input float arrays */
  addr=(int)(&U[0]);
  UU=(__float2_t *)(addr);
  addr=(int)(&V[0]);
  VV=(__float2_t *)(addr);
  addr=(int)(&diag[0]);
  ddiag=(__float2_t *)(addr);
  addr=(int)(&superdiag[0]);
  ssuperdiag=(__float2_t *)(addr);

  /* Householder processing */
  s=0;
  scale=0;
  for (i=0;i<Ncols;i++) {
	/*superdiag[i]=scale*s; */
	ssuperdiag[i]=real_to_f2(scale*s);

	/* process columns */
	scale=0;
#pragma MUST_ITERATE(1,,)
	for (j=i;j<Nrows;j++) {
	  /* scale+=fabs(U[i+j*Ncols]; */
	  temp=_dmpysp(UU[i+j*Ncols],UU[i+j*Ncols]);
	  scale+=sqrt(_lof2(temp)+_hif2(temp));
	}
if (scale>0) {
	  s2_f2=0;
#pragma MUST_ITERATE(1,,)
	  for (j=i;j<Nrows;j++) {
		/* U[i+j*Ncols]=U[i+j*Ncols]/scale; */
#ifndef ENABLE_NR
		inv_scale=1/scale;
#else
	    x=scale;
        y=_rcpsp(x);
        y=y*(2.0-x*y);
        y=y*(2.0-x*y);
        y=y*(2.0-x*y);
        inv_scale=y*(2.0-x*y);
#endif
		UU[i+j*Ncols]=_dmpysp(UU[i+j*Ncols],_ftof2(inv_scale,inv_scale));
		/* s2+=U[i+j*Ncols]*conj(U[i+j*Ncols]); */
		s2_f2=_daddsp(s2_f2,ccmpy(UU[i+j*Ncols],UU[i+j*Ncols]));
	  }
	  s2=real(s2_f2)+imag(s2_f2);
	  if (real(UU[i+i*Ncols])<0) {
		s=sqrt(s2);
	  } else {
        s=-sqrt(s2);
	  }
	  /* half_norm_squared=U[i+i*Ncols]*s-s2; */
	  half_norm_squared=_dsubsp(_dmpysp(UU[i+i*Ncols],_ftof2(s,s)),real_to_f2(s2));

	  /* inv_half_norm_squared=1/half_norm_squared */
      complex_sp_inv(half_norm_squared,&inv_half_norm_squared);

      /* U[i+i*Ncols]-=s; */
	  UU[i+i*Ncols]=_dsubsp(UU[i+i*Ncols],real_to_f2(s));

	  for (j=i+1;j<Ncols;j++) {
		si=zero;
#pragma MUST_ITERATE(1,,)
		for (k=i;k<Nrows;k++) {
		  /* si+=conj(U[i+k*Ncols])*U[j+k*Ncols]; */
		  si=_daddsp(si,ccmpy(UU[i+k*Ncols],UU[j+k*Ncols]));
		}
        /* si=si/half_norm_squared; */
		si=cmpy(si,inv_half_norm_squared);
#pragma MUST_ITERATE(1,,)
		for (k=i;k<Nrows;k++) {
		  /* U[j+k*Ncols]+=si*U[i+k*Ncols]; */
		  UU[j+k*Ncols]=_daddsp(UU[j+k*Ncols],cmpy(si,UU[i+k*Ncols]));
		}
	  }
	} /* if (scale>0) */
#pragma MUST_ITERATE(1,,)
	for (j=i;j<Nrows;j++) {
	  /* U[i+j*Ncols]*=scale; */
	  UU[i+j*Ncols]=_dmpysp(UU[i+j*Ncols],_ftof2(scale,scale));
	}
	/* diag[i]=s*scale; */
	ddiag[i]=real_to_f2(s*scale);
	/* process rows */
    s=0;
    scale=0;
    if ((i<Nrows)&&(i!=Ncols-1)) {
      for (j=i+1;j<Ncols;j++) {
    	/* scale+=fabs(U[j+i*Ncols]); */
    	temp=_dmpysp(UU[j+i*Ncols],UU[j+i*Ncols]);
    	scale+=sqrt(_lof2(temp)+_hif2(temp));
      }
      if (scale>0) {
        s2_f2=zero;
#ifndef ENABLE_NR
        inv_scale=1/scale;
#else
        x=scale;
        y=_rcpsp(x);
        y=y*(2.0-x*y);
        y=y*(2.0-x*y);
        y=y*(2.0-x*y);
        inv_scale=y*(2.0-x*y);
#endif
        for (j=i+1;j<Ncols;j++) {
          /* U[j+i*Ncols]=U[j+i*Ncols]/scale; */
          UU[j+i*Ncols]=_dmpysp(UU[j+i*Ncols],_ftof2(inv_scale,inv_scale));
          /* s2+=U[j+i*Ncols]*conj(U[j+i*Ncols]); */
          s2_f2=_daddsp(s2_f2,ccmpy(UU[j+i*Ncols],UU[j+i*Ncols]));
        }
  	    s2=real(s2_f2)+imag(s2_f2);
        j--;
        if (real(UU[j+i*Ncols])<0) {
          s= sqrt(s2);
        } else {
          s=-sqrt(s2);
        }
        /* half_norm_squared=conj(U[i+1+i*Ncols])*s-s2; */
  	    half_norm_squared=_dsubsp(_dmpysp(UU[i+1+i*Ncols],_ftof2(s,s)),real_to_f2(s2));

  	    /* inv_half_norm_squared=1/half_norm_squared; */
        complex_sp_inv(half_norm_squared,&inv_half_norm_squared);

#pragma MUST_ITERATE(1,,)
        for (k=i+1;k<Ncols;k++) {
          /* U[k+i*Ncols]=conj([U[k+i*Ncols]) */
          U[2*k+1+i*2*Ncols]=-U[2*k+1+i*2*Ncols];

          if (k==i+1) {
        	UU[k+i*Ncols]=_dsubsp(UU[k+i*Ncols],real_to_f2(s));
          }

          /* superdiag[k]=conj(U[k+i*Ncols])/conj(half_norm_squared); */
          ssuperdiag[k]=ccmpy(UU[k+i*Ncols],inv_half_norm_squared);
        }
        if (i<Nrows-1) {
          for (j=i+1;j<Nrows;j++) {
        	si=zero;
#pragma MUST_ITERATE(1,,)
        	for (k=i+1;k<Ncols;k++) {
        	  /* si+=U[k+i*Ncols]*U[k+j*Ncols]; */
          	  si=_daddsp(si,cmpy(UU[k+i*Ncols],UU[k+j*Ncols]));
        	}
#pragma MUST_ITERATE(1,,)
        	for (k=i+1;k<Ncols;k++) {
        	  /* U[k+j*Ncols]+=si*superdiag[k]; */
          	  UU[k+j*Ncols]=_daddsp(UU[k+j*Ncols],cmpy(si,ssuperdiag[k]));
        	}
          }
        }
      }	/* if (scale>0) */
#pragma MUST_ITERATE(1,,)
      for (k=i+1;k<Ncols;k++) {
    	/* U[k+i*Ncols]*=scale; */
      	UU[k+i*Ncols]=_dmpysp(UU[k+i*Ncols],_ftof2(scale,scale));
      }
    } /* if ((i<Nrows)&&(i!=Ncols-1)) */
  } /* for (i=0;i<Ncols;i++) */

  /* update V */
  /* V[Ncols*Ncols-1]=1; */
  VV[Ncols*Ncols-1]=one;
  /* s=superdiag[Ncols-1]; */
  s_f2=ssuperdiag[Ncols-1];
  for (i=Ncols-2;i>=0;i--) {
	/* if (s!=0) { */
	  if(real(s_f2)!=0) {

	  /* inv=1/(conj(U[i+1+i*Ncols])*s); */
	  complex_sp_inv(ccmpy(UU[i+1+i*Ncols],s_f2),&temp);

#pragma MUST_ITERATE(1,,)
	  for (j=i+1;j<Ncols;j++) {
		/* V[i+j*Ncols]=U[j+i*Ncols]/(conj(U[i+1+i*Ncols])*s); */
		VV[i+j*Ncols]=cmpy(UU[j+i*Ncols],temp);
	  }
	  for (j=i+1;j<Ncols;j++) {
	    si=zero;
#pragma MUST_ITERATE(1,,)
	    for (k=i+1;k<Ncols;k++) {
	      /* si+=conj(U[k+i*Ncols])*V[j+k*Ncols]; */
		  si=_daddsp(si,ccmpy(UU[k+i*Ncols],VV[j+k*Ncols]));
	    }
#pragma MUST_ITERATE(1,,)
	    for (k=i+1;k<Ncols;k++) {
	      /* V[j+k*Ncols]+=si*V[i+k*Ncols]; */
		  VV[j+k*Ncols]=_daddsp(VV[j+k*Ncols],cmpy(si,VV[i+k*Ncols]));
	    }
	  }
	} /* if (s!=0) */
#pragma MUST_ITERATE(1,,)
	for (j=i+1;j<Ncols;j++) {
	  /* V[j+i*Ncols]=0; */
	  VV[j+i*Ncols]=zero;
	  /* V[i+j*Ncols]=0; */
	  VV[i+j*Ncols]=zero;
	}
	/* V[i+i*Ncols]=1; */
	VV[i+i*Ncols]=one;
	/* s=superdiag[i]; */
	s_f2=ssuperdiag[i];
  } /* for (i=Ncols-2;i>=0;i--) */

#ifndef ENABLE_REDUCED_FORM
  /* expand U to from Nrows x Ncols to */
  /*                  Nrows x Nrows    */
  if (Nrows>Ncols) {
	for (i=Nrows-1;i>=0;i--) {
	  for (j=Nrows-1;j>=0;j--) {
		if (j<=Ncols-1) {
		/* U[j+i*Nrows]=U[j+i*Ncols]; */
		  UU[j+i*Nrows]=UU[j+i*Ncols];
		} else {
		  /* U[j+i*Nrows]=0; */
		  UU[j+i*Nrows]=zero;
		}
	  }
	}
  }

  /* update U */
  for (i=Ncols-1;i>=0;i--) {

	/* s=diag[i]; */
	s=real(ddiag[i]);

#ifndef ENABLE_NR
    inv_s=1/s;
#else
    inv_s=_rcpsp(s);
    inv_s=inv_s*(2.0-s*inv_s);
    inv_s=inv_s*(2.0-s*inv_s);
    inv_s=inv_s*(2.0-s*inv_s);
#endif

    /* inv_UU=1/(conj(UU[i+i*Nrows])*s); */
    complex_sp_inv(_dmpysp(UU[i+i*Nrows],_ftof2(s,s)),&inv_UU_x_s);

#pragma MUST_ITERATE(1,,)
	for (j=i+1;j<Ncols;j++) {
	  /* U[j+i*Nrows]=0; */
	  UU[j+i*Nrows]=zero;
	}
    /* if (s!=0) { */
	if (fabs(s)>ZERO_TOLERANCE) {

      for (j=i+1;j<Nrows;j++) {
      	/* si=0; */
      	si=zero;
#pragma MUST_ITERATE(1,,)
    	for (k=i+1;k<Nrows;k++) {
      	  /* si+=conj(U[i+k*Nrows])*U[j+k*Nrows]; */
          si=_daddsp(si,ccmpy(UU[i+k*Nrows],UU[j+k*Nrows]));
    	}
    	/* si=si/(conj(U[i+i*Nrows])*s); */
    	si=ccmpy(inv_UU_x_s,si);

        #pragma MUST_ITERATE(1,,)
    	for (k=i;k<Nrows;k++) {
      	  /* U[j+k*Nrows]+=si*U[i+k*Nrows]; */
      	  UU[j+k*Nrows]=_daddsp(UU[j+k*Nrows],cmpy(si,UU[i+k*Nrows]));
    	}
      }
      /* initial U1 */
      if (i==Ncols-1) {
    	for (j=i;j<Nrows;j++) {
    	  for (k=Nrows-1;k>=i+1;k--) {
    	    /* U[k+j*Nrows]=U[i+j*Nrows]*conj(U[i+k*Nrows])/(conj(U[i+i*Nrows])*s); */
    		UU[k+j*Nrows]=ccmpy(inv_UU_x_s,ccmpy(UU[i+k*Nrows],UU[i+j*Nrows]));
    	    if (j==k) {
      	      /* U[k+j*Nrows]+=1; */
              UU[k+j*Nrows]=_daddsp(UU[k+j*Nrows],one);
    	    }
    	  }
    	}
      }
#pragma MUST_ITERATE(1,,)
      for (j=i;j<Nrows;j++) {
    	/* U[i+j*Nrows]=U[i+j*Nrows]/s; */
      	UU[i+j*Nrows]=_dmpysp(UU[i+j*Nrows],_ftof2(inv_s,inv_s));
      }
    } else { /* if (s!=0) */
      if (i==Ncols-1) {
#pragma MUST_ITERATE(1,,)
       	for (k=1;k<=Nrows-Ncols;k++) {
      	  /* U[i+k+(i+k)*Nrows]=1; */
       		UU[i+k+(i+k)*Nrows]=one;
       	}
      }
#pragma MUST_ITERATE(1,,)
      for (j=i;j<Nrows;j++) {
      	/* U[i+j*Nrows]=0; */
      	UU[i+j*Nrows]=zero;
      }
    } /* if (s!=0) */
    /* U[i+i*Nrows]+=1; */
	UU[i+i*Nrows]=_daddsp(UU[i+i*Nrows],one);
  } /* for (i=Ncols-1;i>=0;i--) */
#else /* #ifndef ENABLE_REDUCED_FORM */
  /* update U */
  for (i=Ncols-1;i>=0;i--) {

	/* s=diag[i]; */
	s=real(ddiag[i]);
#ifndef ENABLE_NR
    inv_s=1/s;
#else
    inv_s=_rcpsp(s);
    inv_s=inv_s*(2.0-s*inv_s);
    inv_s=inv_s*(2.0-s*inv_s);
    inv_s=inv_s*(2.0-s*inv_s);
#endif

    /* inv_UU=1/(conj(UU[i+i*Ncols])*s); */
    complex_sp_inv(_dmpysp(UU[i+i*Ncols],_ftof2(s,s)),&inv_UU_x_s);

#pragma MUST_ITERATE(1,,)
	for (j=i+1;j<Ncols;j++) {
	  /* U[j+i*Nrows]=0; */
	  UU[j+i*Ncols]=zero;
	}
    /* if (s!=0) { */
	if (fabs(s)>ZERO_TOLERANCE) {

      for (j=i+1;j<Ncols;j++) {
      	/* si=0; */
      	si=zero;
#pragma MUST_ITERATE(1,,)
    	for (k=i+1;k<Nrows;k++) {
      	  /* si+=conj(U[i+k*Ncols])*U[j+k*Ncols]; */
          si=_daddsp(si,ccmpy(UU[i+k*Ncols],UU[j+k*Ncols]));
    	}
    	/* si=si/(conj(U[i+i*Ncols])*s); */
    	si=ccmpy(inv_UU_x_s,si);

        #pragma MUST_ITERATE(1,,)
    	for (k=i;k<Nrows;k++) {
      	  /* U[j+k*Ncols]+=si*U[i+k*Ncols]; */
      	  UU[j+k*Ncols]=_daddsp(UU[j+k*Ncols],cmpy(si,UU[i+k*Ncols]));
    	}
      }
#pragma MUST_ITERATE(1,,)
       for (j=i;j<Nrows;j++) {
    	/* U[i+j*Ncols]=U[i+j*Ncols]/s; */
    	UU[i+j*Ncols]=_dmpysp(UU[i+j*Ncols],_ftof2(inv_s,inv_s));
      }
    } else { /* if (s!=0) */
#pragma MUST_ITERATE(1,,)
      for (j=i;j<Nrows;j++) {
      	/* U[i+j*Ncols]=0; */
      	UU[i+j*Ncols]=zero;
      }
    } /* if (s!=0) */
    /* U[i+i*Ncols]+=1; */
	UU[i+i*Ncols]=_daddsp(UU[i+i*Ncols],one);
  } /* for (i=Ncols-1;i>=0;i--)
  */
#endif

  return 0;
}

static int DSPF_sp_bidiag_to_diag_cmplx(const int Nrows,const int Ncols,float *restrict U,float *restrict V,float *restrict diag,float *restrict superdiag)
{

  int row,i,k,m,rotation_test,iter,total_iter,addr;
  float xx,yy,epsilon;
  __float2_t *UU,*VV,*ddiag,*ssuperdiag;
  __float2_t temp,c,s,f,g,h,x,y,z,num,den;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)U % 8 == 0);
  _nassert((int)V % 8 == 0);
  _nassert((int)diag % 8 == 0);
  _nassert((int)superdiag % 8 == 0);

  /* initialize __float2_t arrays to overlay input float arrays */
  addr=(int)(&U[0]);
  UU=(__float2_t *)(addr);
  addr=(int)(&V[0]);
  VV=(__float2_t *)(addr);
  addr=(int)(&diag[0]);
  ddiag=(__float2_t *)(addr);
  addr=(int)(&superdiag[0]);
  ssuperdiag=(__float2_t *)(addr);

  iter=0;
  total_iter=0;
  /* ------------------------------------------------------------------- */
  /* find max in col                                                     */
  /* ------------------------------------------------------------------- */
  xx=0;
#pragma MUST_ITERATE(1,,)
  for (i=0;i<Ncols;i++) {
	/* y=fabs(diag[i])+fabs(superdiag[i]); */
	temp=_dmpysp(ddiag[i],ddiag[i]);
	yy=sqrt(_lof2(temp)+_hif2(temp));
	temp=_dmpysp(ssuperdiag[i],ssuperdiag[i]);
	yy+=sqrt(_lof2(temp)+_hif2(temp));
	if (xx<yy) {
	  xx=yy;
	}
  }
  epsilon=FLT_EPSILON*xx;
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
      	temp=_dmpysp(ssuperdiag[m],ssuperdiag[m]);
      	if (sqrt(_lof2(temp)+_hif2(temp))<=epsilon) {
    	  rotation_test=0;
    	  break;
    	}
    	/* if (fabs(diag[m-1])<=epsilon) { */
    	temp=_dmpysp(ddiag[m-1],ddiag[m-1]);
    	if (sqrt(_lof2(temp)+_hif2(temp))<=epsilon) {
    	  break;
    	}
      } /* for (m=k;m>=0;m--) */
      if (rotation_test) {
      	/* c=0; */
      	/* s=1; */
      	c=zero;
      	s=one;
#pragma MUST_ITERATE(1,,)
    	for (i=m;i<=k;i++) {
      	  /* f=s*superdiag[i]; */
      	  f=cmpy(s,ssuperdiag[i]);
    	  /* superdiag[i]=c*superdiag[i]; */
    	  ssuperdiag[i]=cmpy(c,ssuperdiag[i]);

    	  /* if (fabs(f)<=epsilon) { */
    	  temp=_dmpysp(f,f);
    	  if (sqrt(_lof2(temp)+_hif2(temp))<=epsilon) {
    		break;
    	  }

    	  /* g=diag[i]; */
    	  g=ddiag[i];

    	  /* h=sqrt(f*f+g*g); */
          temp=_daddsp(cmpy(f,f),cmpy(g,g));
    	  complex_sp_sqrt(temp,&h);

    	  /* diag[i]=h; */
    	  ddiag[i]=h;

    	  /* c=g/h; */
    	  complex_sp_div(g,h,&c);
    	  /* s=-f/h; */
    	  complex_sp_div(f,h,&s);
    	  s=_dsubsp(zero,s);

#ifndef ENABLE_REDUCED_FORM
#pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Nrows;row++) {
      		/* y=U[m-1+row*Nrows]; */
      		y=UU[m-1+row*Nrows];
      		/* z=U[i+row*Nrows]; */
      		z=UU[i+row*Nrows];
      		/* U[m-1+row*Nrows]= y*c+z*s; */
      		UU[m-1+row*Nrows] = _daddsp(cmpy(y,c),cmpy(z,s));
      		/* U[i+row*Nrows]  =-y*s+z*c; */
      		UU[i+row*Nrows] =  _dsubsp(cmpy(z,c),cmpy(y,s));
    	  }
#else
#pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Nrows;row++) {
      		/* y=U[m-1+row*Ncols]; */
      		y=UU[m-1+row*Ncols];
      		/* z=U[i+row*Ncols]; */
      		z=UU[i+row*Ncols];
      		/* U[m-1+row*Ncols]= y*c+z*s; */
      		UU[m-1+row*Ncols]=_daddsp(cmpy(y,c),cmpy(z,s));
      		/* U[i+row*Ncols]  =-y*s+z*c; */
      		UU[i+row*Ncols]=_dsubsp(cmpy(z,c),cmpy(y,s));
    	  }
#endif
     	} /* for (i=m;i<=k;i++) */
      } /* if (rotation_test) */
      /* z=diag[k]; */
      z=ddiag[k];

      if (m==k) {
      	/* if (z<0) { */
      	if (real(z)<0) {
      	  /* diag[k]=-z; */
      	  ddiag[k]=_dsubsp(zero,z);
#pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Ncols;row++) {
      		/* V[k+row*Ncols]=-V[k+row*Ncols]; */
      		VV[k+row*Ncols]=_dsubsp(zero,VV[k+row*Ncols]);
    	  }
    	} /* if (z>0) */
    	break;
      } else { /* if (m==k) */
        if (iter>=MAX_ITERATION_COUNT) {
          return -1;
        }
        iter++;
    	/* x=diag[m]; */
        x=ddiag[m];
    	/* y=diag[k-1]; */
        y=ddiag[k-1];
    	/* g=superdiag[k-1]; */
        g=ssuperdiag[k-1];
    	/* h=superdiag[k]; */
        h=ssuperdiag[k];
    	/* f=((y-z)*(y+z)+(g-h)*(g+h))/(2*h*y); */
        num=_daddsp(cmpy(_dsubsp(y,z),_daddsp(y,z)),cmpy(_dsubsp(g,h),_daddsp(g,h)));
        den=_dmpysp(_ftof2(2,2),cmpy(h,y));
        complex_sp_div(num,den,&f);

    	/* g=sqrt(f*f+1); */
        temp=_daddsp(cmpy(f,f),_ftof2(1,0));
        complex_sp_sqrt(temp,&g);

    	/* if (f<0) { */
        if (real(f)<0) {
    	  /* g=-g; */
          g=_dsubsp(zero,g);
    	}

    	/* f=((x-z)*(x+z)+h*(y/(f+g)-h))/x; */
        num=y;
        den=_daddsp(f,g);
        complex_sp_div(num,den,&temp);
        temp=_dsubsp(temp,h);
        temp=cmpy(h,temp);
        num=_daddsp(cmpy(_dsubsp(x,z),_daddsp(x,z)),temp);
        complex_sp_div(num,x,&f);

    	/* next QR transformation */
    	/* c=1; */
    	/* s=1; */
        c=one;
        s=one;
#pragma MUST_ITERATE(1,,)
    	for (i=m+1;i<=k;i++) {
    	  /* g=superdiag[i]; */
    	  g=ssuperdiag[i];

    	  /* y=diag[i]; */
    	  y=ddiag[i];

    	  /* h=s*g; */
    	  h=cmpy(s,g);

    	  /* g=g*c; */
    	  g=cmpy(g,c);

    	  /* z=sqrt(f*f+h*h); */
    	  temp=_daddsp(cmpy(f,f),cmpy(h,h));
          complex_sp_sqrt(temp,&z);

    	  /* superdiag[i-1]=z; */
    	  ssuperdiag[i-1]=z;

    	  /* c=f/z; */
    	  complex_sp_div(f,z,&c);

    	  /* s=h/z; */
    	  complex_sp_div(h,z,&s);

    	  /* f= x*c+g*s; */
    	  f=_daddsp(cmpy(x,c),cmpy(g,s));

    	  /* g=-x*s+g*c; */
    	  g=_dsubsp(cmpy(g,c),cmpy(x,s));

    	  /* h=y*s; */
    	  h=cmpy(y,s);

    	  /* y=c*y; */
    	  y=cmpy(c,y);

    	  #pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Ncols;row++) {
      		/* x=V[i-1+row*Ncols]; */
      		x=VV[i-1+row*Ncols];

      		/* z=V[i+row*Ncols]; */
      		z=VV[i+row*Ncols];

      		/* V[i-1+row*Ncols]= x*c+z*s; */
      		VV[i-1+row*Ncols]=_daddsp(cmpy(x,c),cmpy(z,s));

      		/* V[i+row*Ncols]  =-x*s+z*c; */
      		VV[i+row*Ncols]=_dsubsp(cmpy(z,c),cmpy(x,s));
    	  }

    	  /* z=sqrt(f*f+h*h); */
    	  temp=_daddsp(cmpy(f,f),cmpy(h,h));
    	  complex_sp_sqrt(temp,&z);

    	  /* diag[i-1]=z; */
    	  ddiag[i-1]=z;

    	  /* if (z!=0) { */
    	  temp=_dmpysp(z,z);
    	  if (sqrt(_lof2(temp)+_hif2(temp))>ZERO_TOLERANCE) {

    		/* c=f/z; */
    		complex_sp_div(f,z,&c);

    		/* s=h/z; */
    		complex_sp_div(h,z,&s);
    	  }

    	  /* f= c*g+s*y; */
    	  f=_daddsp(cmpy(c,g),cmpy(s,y));

    	  /* x=-s*g+c*y; */
    	  x=_dsubsp(cmpy(c,y),cmpy(s,g));
#ifndef ENABLE_REDUCED_FORM
#pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Nrows;row++) {
    	   	/* y=U[i-1+row*Nrows]; */
    	    y=UU[i-1+row*Nrows];

    	    /* z=U[i+row*Nrows]; */
    	    z=UU[i+row*Nrows];

    	    /* U[i-1+row*Nrows]= c*y+s*z; */
    	    UU[i-1+row*Nrows]=_daddsp(cmpy(c,y),cmpy(s,z));

    	    /* U[i+row*Nrows]  =-s*y+c*z; */
    	    UU[i+row*Nrows]=_dsubsp(cmpy(c,z),cmpy(s,y));
    	  }
#else
#pragma MUST_ITERATE(1,,)
    	  for (row=0;row<Nrows;row++) {
      		/* y=U[i-1+row*Ncols]; */
      		y=UU[i-1+row*Ncols];
      		/* z=U[i+row*Ncols]; */
      		z=UU[i+row*Ncols];
      		/* U[i-1+row*Ncols]= c*y+s*z; */
      		UU[i-1+row*Ncols]=_daddsp(cmpy(c,y),cmpy(s,z));
      		/* U[i+row*Ncols]  =-s*y+c*z; */
      		UU[i+row*Ncols]=_dsubsp(cmpy(c,z),cmpy(s,y));
       	  }
#endif
    	} /* for (i=m+1;i<=k;i++) */

    	/* superdiag[m]=0; */
    	ssuperdiag[m]=zero;

    	/* superdiag[k]=f; */
    	ssuperdiag[k]=f;

    	/* diag[k]=x; */
    	ddiag[k]=x;

      } /* if (m==k) */
    } /* while (1==1) */
  } /* for (k=Ncols-1:k>=0;k--) */

  return total_iter;
}

static int DSPF_sp_sort_singular_values_cmplx(const int Nrows,const int Ncols,float *restrict U,float *restrict V,float *restrict singular_values)
{
  int i,j,row,max_index,addr;
  float temp1,temp2;
  __float2_t *UU,*VV,*ssingular_values;
  __float2_t temp;

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)U % 8 == 0);
  _nassert((int)V % 8 == 0);
  _nassert((int)singular_values % 8 == 0);

  /* initialize __float2_t arrays to overlay input float arrays */
  addr=(int)(&U[0]);
  UU=(__float2_t *)(addr);
  addr=(int)(&V[0]);
  VV=(__float2_t *)(addr);
  addr=(int)(&singular_values[0]);
  ssingular_values=(__float2_t *)(addr);

  #pragma MUST_ITERATE(1,,)
  for (i=0;i<Ncols-1;i++) {
	max_index=i;
#pragma MUST_ITERATE(1,,)
	for (j=i+1;j<Ncols;j++) {
	  /* (if (singular_values[j]>singular_values[max_index]) { */
	  temp=_dmpysp(ssingular_values[j],ssingular_values[j]);
	  temp1=sqrt(_lof2(temp)+_hif2(temp));
	  temp=_dmpysp(ssingular_values[max_index],ssingular_values[max_index]);
	  temp2=sqrt(_lof2(temp)+_hif2(temp));
	  if (temp1>temp2) {
		max_index=j;
	  }
	}
	if (max_index!=i) {
	  temp=ssingular_values[i];
	  ssingular_values[i]=ssingular_values[max_index];
	  ssingular_values[max_index]=temp;
#ifndef ENABLE_REDUCED_FORM
#pragma MUST_ITERATE(1,,)
	  for (row=0;row<Nrows;row++) {
		temp=UU[max_index+row*Nrows];
		UU[max_index+row*Nrows]=UU[i+row*Nrows];
		UU[i+row*Nrows]=temp;
	  }
#else
#pragma MUST_ITERATE(1,,)
	  for (row=0;row<Nrows;row++) {
		temp=UU[max_index+row*Ncols];
		UU[max_index+row*Ncols]=UU[i+row*Ncols];
		UU[i+row*Ncols]=temp;
	  }
#endif
#pragma MUST_ITERATE(1,,)
	  for (row=0;row<Ncols;row++) {
		temp=VV[max_index+row*Ncols];
		VV[max_index+row*Ncols]=VV[i+row*Ncols];
		VV[i+row*Ncols]=temp;
	  }
	}
  }

  return 0;
}

static void complex_sp_sqrt(__float2_t cx,__float2_t *cz) {

  float xmag,zmag,xreal,ximag,zreal,zimag;
  float x_angle,z_angle;
  __float2_t ctemp;

  /* magnitude */
  ctemp=_dmpysp(cx,cx);
  xmag=sqrt(_lof2(ctemp)+_hif2(ctemp));
  zmag=sqrt(xmag);

  /* angle */
#ifndef _LITTLE_ENDIAN
  xreal=_hif2(cx);
  ximag=_lof2(cx);
#else
  xreal=_lof2(cx);
  ximag=_hif2(cx);
#endif
#ifndef ENABLE_MATHLIB
  x_angle=atan2(ximag,xreal);
#else
  x_angle=atan2sp_c(ximag,xreal);
#endif
  z_angle=x_angle/2;

  /* results */
#ifndef ENABLE_MATHLIB
  zreal=cos(z_angle)*zmag;
  zimag=sin(z_angle)*zmag;
#else
  zreal=cossp(z_angle)*zmag;
  zimag=sinsp(z_angle)*zmag;
#endif
#ifndef _LITTLE_ENDIAN
  *cz=_ftof2(zreal,zimag);
#else
  *cz=_ftof2(zimag,zreal);
#endif
}

static void complex_sp_inv(__float2_t cy,__float2_t *cz) {

  float inv_mag_sq,yreal,yimag,zreal,zimag;
#ifdef ENABLE_NR
  float x,y;
#endif

#ifndef _LITTLE_ENDIAN
  yreal=_hif2(cy);
  yimag=_lof2(cy);
#else
  yreal=_lof2(cy);
  yimag=_hif2(cy);
#endif

#ifndef ENABLE_NR
  inv_mag_sq=1/(yreal*yreal+yimag*yimag);
#else
  x=yreal*yreal+yimag*yimag;
  y=_rcpsp(x);
  y=y*(2.0-x*y);
  y=y*(2.0-x*y);
  inv_mag_sq=y;
#endif

  /* results */
  zreal= yreal*inv_mag_sq;
  zimag=-yimag*inv_mag_sq;
#ifndef _LITTLE_ENDIAN
  *cz=_ftof2(zreal,zimag);
#else
  *cz=_ftof2(zimag,zreal);
#endif

}

static void complex_sp_div(__float2_t cx,__float2_t cy,__float2_t *cz) {

  float xreal,ximag,yreal,yimag,zreal,zimag;
  float inv_mag_sq;
#ifdef ENABLE_NR
  float x,y;
#endif

#ifndef _LITTLE_ENDIAN
  xreal=_hif2(cx);
  ximag=_lof2(cx);
  yreal=_hif2(cy);
  yimag=_lof2(cy);
#else
  xreal=_lof2(cx);
  ximag=_hif2(cx);
  yreal=_lof2(cy);
  yimag=_hif2(cy);
#endif
#ifndef ENABLE_NR
  inv_mag_sq=1/(yreal*yreal+yimag*yimag);
#else
  x=yreal*yreal+yimag*yimag;
  y=_rcpsp(x);
  y=y*(2.0-x*y);
  y=y*(2.0-x*y);
  inv_mag_sq=y;
#endif

  /* results */
  zreal=(xreal*yreal+ximag*yimag)*inv_mag_sq;
  zimag=(ximag*yreal-xreal*yimag)*inv_mag_sq;
#ifndef _LITTLE_ENDIAN
  *cz=_ftof2(zreal,zimag);
#else
  *cz=_ftof2(zimag,zreal);
#endif

}
/* ======================================================================= */
/*  End of file:  DSPF_sp_svd_cmplx.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
