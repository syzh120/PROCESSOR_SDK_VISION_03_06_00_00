/* ======================================================================= */
/* DSPF_sp_lud_inv_cmplx.c - complex matrix inversion by LUD single precision */
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

#pragma CODE_SECTION(DSPF_sp_lud_inverse_cmplx,".text:optimized");

#include "DSPF_sp_lud_inv_cmplx.h"

#define ENABLE_NR 1
#define ENABLE_MATHLIB 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2sp/c66/atan2sp.h>
#include <ti/mathlib/src/cossp/c66/cossp.h>
#include <ti/mathlib/src/sinsp/c66/sinsp.h>
#endif

static void complex_sp_inv(__float2_t cy,__float2_t *cz);
static void complex_sp_div(__float2_t cx,__float2_t cy,__float2_t *cz);

int DSPF_sp_lud_inverse_cmplx(const int Nrows,unsigned short *restrict P,
                    float *restrict L,float *restrict U,float *restrict inv_A) {

  int row,col,Ncols,k;
  int addr;
  __float2_t *LL,*UU,*inv_AA;
  __float2_t *inv_LL,*inv_UU,*inv_UU_x_inv_LL;
  __float2_t cz,factor,sum;
#ifdef _LITTLE_ENDIAN
  __float2_t ctemp;
#endif

  _nassert(Nrows>0);
  _nassert((int)P % 2 == 0);
  _nassert((int)L % 8 == 0);
  _nassert((int)U % 8 == 0);
  _nassert((int)inv_A % 8 == 0);

  /* overlay __float2_t arrays with float arrays */
  addr=(int)(&L[0]);
  LL=(__float2_t *)(addr);
  addr=(int)(&U[0]);
  UU=(__float2_t *)(addr);
  addr=(int)(&inv_A[0]);
  inv_AA=(__float2_t *)(addr);

  /* set inv_A matrix to identity */
  inv_LL=&inv_AA[0];
  Ncols=Nrows;
  memset(inv_LL,0.0,sizeof(__float2_t)*Nrows*Ncols);
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
#ifndef _LITTLE_ENDIAN
	inv_LL[row+row*Ncols]=_ftof2(1,0);
#else
	inv_LL[row+row*Ncols]=_ftof2(0,1);
#endif
  }

  /* use Gauss Jordan algorithm to invert L whose result is in inv_L */
#pragma MUST_ITERATE(1,,)
  for (col=0;col<Nrows-1;col++) {
	complex_sp_inv(LL[col+col*Ncols],&cz);

#pragma MUST_ITERATE(1,,)
    for (row=col+1;row<Nrows;row++) {

#ifndef _LITTLE_ENDIAN
     factor=_complex_mpysp(LL[col+row*Ncols],cz);
#else
     ctemp=_complex_mpysp(LL[col+row*Ncols],cz);
     factor=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif

#pragma MUST_ITERATE(1,,)
	  for (k=0;k<row;k++) {
#ifndef _LITTLE_ENDIAN
		inv_LL[k+row*Ncols]=_dsubsp(inv_LL[k+row*Ncols],_complex_mpysp(factor,inv_LL[k+col*Ncols]));
#else
		ctemp=_complex_mpysp(factor,inv_LL[k+col*Ncols]);
		inv_LL[k+row*Ncols]=_dsubsp(inv_LL[k+row*Ncols],_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
	  }
	}
  }

  /* set inv_U matrix to identity */
  inv_UU=&LL[0];
  memset(inv_UU,0.0,sizeof(__float2_t)*Nrows*Ncols);
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
#ifndef _LITTLE_ENDIAN
	inv_UU[row+row*Ncols]=_ftof2(1,0);
#else
	inv_UU[row+row*Ncols]=_ftof2(0,1);
#endif
  }

  /* use Gauss Jordan algorithm to invert U whose result is in L */
#pragma MUST_ITERATE(1,,)
  for (col=Nrows-1;col>=1;col--) {
#pragma MUST_ITERATE(1,,)
	for (row=col-1;row>=0;row--) {
      complex_sp_div(UU[col+row*Ncols],UU[col+col*Ncols],&cz);
      factor=cz;

#pragma MUST_ITERATE(1,,)
	  for (k=col;k<Nrows;k++) {
#ifndef _LITTLE_ENDIAN
		inv_UU[k+row*Ncols]=_dsubsp(inv_UU[k+row*Ncols],_complex_mpysp(factor,inv_UU[k+col*Ncols]));
		UU[k+row*Ncols]=_dsubsp(UU[k+row*Ncols],_complex_mpysp(factor,UU[k+col*Ncols]));
#else
		ctemp=_complex_mpysp(factor,inv_UU[k+col*Ncols]);
		inv_UU[k+row*Ncols]=_dsubsp(inv_UU[k+row*Ncols],_ftof2(_lof2(ctemp),-_hif2(ctemp)));
		ctemp=_complex_mpysp(factor,UU[k+col*Ncols]);
		UU[k+row*Ncols]=_dsubsp(UU[k+row*Ncols],_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
	  }
	}
  }

  /* scale U & L to get identity matrix in U */
#pragma MUST_ITERATE(1,,)
  for (row=Nrows-1;row>=0;row--) {
	  complex_sp_inv(UU[row+row*Ncols],&cz);
	  factor=cz;

#pragma MUST_ITERATE(1,,)
	for (col=0;col<Nrows;col++) {
#ifndef _LITTLE_ENDIAN
	  LL[col+row*Ncols]=_complex_mpysp(LL[col+row*Ncols],cz);
#else
	  ctemp=_complex_mpysp(LL[col+row*Ncols],cz);
	  LL[col+row*Ncols]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
	}
  }

  /* compute inv_U_x_inv_L=inv(U)*inv(L) */
  inv_UU_x_inv_LL=&LL[0];
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
    for (col=0;col<Nrows;col++) {
      sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
  	  for (k=0;k<Nrows;k++) {
#ifndef _LITTLE_ENDIAN
  		sum=_daddsp(sum,_complex_mpysp(inv_UU[k+row*Ncols],inv_LL[col+k*Ncols]));
#else
  		ctemp=_complex_mpysp(inv_UU[k+row*Ncols],inv_LL[col+k*Ncols]);
  		sum=_daddsp(sum,_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
  	  }
  	  inv_UU_x_inv_LL[col+row*Ncols]=sum;
    }
  }

  /* compute inv_A=inv(U)*inv(L)*P */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
    for (col=0;col<Nrows;col++) {
      sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
  	  for (k=0;k<Nrows;k++) {
  	    sum=_daddsp(sum,_dmpysp(inv_UU_x_inv_LL[k+row*Ncols],_ftof2(P[col+k*Nrows],P[col+k*Nrows])));
  	  }
  	  inv_AA[col+row*Ncols]=sum;
    }
  }

  return 0;
}


static void complex_sp_div(__float2_t cx,__float2_t cy,__float2_t *cz) {

  float x_real,x_imag,y_real,y_imag,z_real,z_imag;
  float inv_mag_sq;
#ifdef ENABLE_NR
  float x,y;
#endif

#ifndef _LITTLE_ENDIAN
  x_real=_hif2(cx);
  x_imag=_lof2(cx);
  y_real=_hif2(cy);
  y_imag=_lof2(cy);
#else
  x_real=_lof2(cx);
  x_imag=_hif2(cx);
  y_real=_lof2(cy);
  y_imag=_hif2(cy);
#endif
#ifndef ENABLE_NR
  inv_mag_sq=1/(y_real*y_real+y_imag*y_imag);
#else
  x=y_real*y_real+y_imag*y_imag;
  y=_rcpsp(x);
  y=y*(2.0-x*y);
  y=y*(2.0-x*y);
  inv_mag_sq=y;
#endif

  /* results */
  z_real=(x_real*y_real+x_imag*y_imag)*inv_mag_sq;
  z_imag=(x_imag*y_real-x_real*y_imag)*inv_mag_sq;
#ifndef _LITTLE_ENDIAN
  *cz=_ftof2(z_real,z_imag);
#else
  *cz=_ftof2(z_imag,z_real);
#endif

}

static void complex_sp_inv(__float2_t cy,__float2_t *cz) {

  float y_real,y_imag,z_real,z_imag;
  float inv_mag_sq;
#ifdef ENABLE_NR
  float x,y;
#endif

#ifndef _LITTLE_ENDIAN
  y_real=_hif2(cy);
  y_imag=_lof2(cy);
#else
  y_real=_lof2(cy);
  y_imag=_hif2(cy);
#endif
#ifndef ENABLE_NR
  inv_mag_sq=1/(y_real*y_real+y_imag*y_imag);
#else
  x=y_real*y_real+y_imag*y_imag;
  y=_rcpsp(x);
  y=y*(2.0-x*y);
  y=y*(2.0-x*y);
  inv_mag_sq=y;
#endif

  /* results */
  z_real= y_real*inv_mag_sq;
  z_imag=-y_imag*inv_mag_sq;
#ifndef _LITTLE_ENDIAN
  *cz=_ftof2(z_real,z_imag);
#else
  *cz=_ftof2(z_imag,z_real);
#endif

}
/* ======================================================================= */
/*  End of file:  DSPF_sp_lud_inv_cmplx                                    */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
