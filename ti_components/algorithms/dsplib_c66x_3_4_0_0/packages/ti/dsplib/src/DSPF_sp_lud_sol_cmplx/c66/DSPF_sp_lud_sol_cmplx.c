/* ======================================================================= */
/* DSPF_sp_lud_sol_cmplx.c - complex linear solver by LUD, single precision*/
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

#pragma CODE_SECTION(DSPF_sp_lud_solver_cmplx,".text:optimized");

#include "DSPF_sp_lud_sol_cmplx.h"

#define ENABLE_NR 1
#define ENABLE_MATHLIB 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2sp/c66/atan2sp.h>
#include <ti/mathlib/src/cossp/c66/cossp.h>
#include <ti/mathlib/src/sinsp/c66/sinsp.h>
#endif

static void complex_sp_inv(__float2_t cy,__float2_t *cz);

int DSPF_sp_lud_solver_cmplx(const int Nrows,unsigned short *restrict P,float *restrict L,float *restrict U,float *restrict b,float *restrict b_mod,float *restrict y,float *restrict x) {

  short row,col,Ncols;
  int addr;
  __float2_t *LL,*UU,*bb,*bb_mod,*yy,*xx;
  __float2_t sum,ctemp,cy,cz;

  _nassert(Nrows>0);
  _nassert((int)P % 2 == 0);
  _nassert((int)L % 8 == 0);
  _nassert((int)U % 8 == 0);
  _nassert((int)b % 8 == 0);
  _nassert((int)b_mod % 8 == 0);
  _nassert((int)y % 8 == 0);
  _nassert((int)x % 8 == 0);

  /* overlay __float2_t arrays with float arrays */
  addr=(int)(&L[0]);
  LL=(__float2_t *)(addr);
  addr=(int)(&U[0]);
  UU=(__float2_t *)(addr);
  addr=(int)(&b[0]);
  bb=(__float2_t *)(addr);
  addr=(int)(&b_mod[0]);
  bb_mod=(__float2_t *)(addr);
  addr=(int)(&y[0]);
  yy=(__float2_t *)(addr);
  addr=(int)(&x[0]);
  xx=(__float2_t *)(addr);


  /* modify b based on permutation matrix P */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
	sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Nrows;col++) {
	  ctemp=_ftof2(P[col+row*Nrows],P[col+row*Nrows]);
	  sum=_daddsp(sum,_dmpysp(ctemp,bb[col]));
	}
	bb_mod[row]=sum;
  }

  /* solve L*y=b for y using forward substitution */
  Ncols=Nrows;
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
	cy=LL[row+row*Ncols];
  	complex_sp_inv(cy,&cz);
    if (row==0) {
#ifndef _LITTLE_ENDIAN
      yy[row]=_complex_mpysp(bb_mod[row],cz);
#else
      ctemp=_complex_mpysp(bb_mod[row],cz);
      yy[row]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
	} else {
      sum=_ftof2(0,0);
	  for (col=0;col<=row-1;col++) {
#ifndef _LITTLE_ENDIAN
		sum=_daddsp(sum,_complex_mpysp(LL[col+row*Ncols],yy[col]));
#else
		ctemp=_complex_mpysp(LL[col+row*Ncols],yy[col]);
		sum=_daddsp(sum,_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
	  }
#ifndef _LITTLE_ENDIAN
	  yy[row]=_complex_mpysp(_dsubsp(bb_mod[row],sum),cz);
#else
	  ctemp=_complex_mpysp(_dsubsp(bb_mod[row],sum),cz);
	  yy[row]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
	}
  }

  /* solve U*x=y for x using backward substitution */
#pragma MUST_ITERATE(1,,)
  for (row=Nrows-1;row>=0;row--) {
	complex_sp_inv(UU[row+row*Ncols],&cz);
	if (row==Nrows-1) {
#ifndef _LITTLE_ENDIAN
	  xx[row]=_complex_mpysp(yy[row],cz);
#else
	  ctemp=_complex_mpysp(yy[row],cz);
	  xx[row]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
	} else {
      sum=_ftof2(0,0);
	  for (col=Nrows-1;col>=row+1;col--) {
#ifndef _LITTLE_ENDIAN
		sum=_daddsp(sum,_complex_mpysp(UU[col+row*Ncols],xx[col]));
#else
		ctemp=_complex_mpysp(UU[col+row*Ncols],xx[col]);
		sum=_daddsp(sum,_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
	  }
#ifndef _LITTLE_ENDIAN
	  xx[row]=_complex_mpysp(_dsubsp(yy[row],sum),cz);
#else
	  ctemp=_complex_mpysp(_dsubsp(yy[row],sum),cz);
	  xx[row]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
	}
  }

  return 0;
}

static void complex_sp_inv(__float2_t cy,__float2_t *cz) 
{
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
/*  End of file:  DSPF_sp_lud_sol_cmplx                                        */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
