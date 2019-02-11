/* ======================================================================= */
/* DSPF_sp_lud_cmplx.c -- lower/upper complex matrix decomposition         */
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

#pragma CODE_SECTION(DSPF_sp_lud_cmplx,".text:optimized");

#include "DSPF_sp_lud_cmplx.h"

#define ENABLE_NR 1
#define ENABLE_MATHLIB 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2sp/c66/atan2sp.h>
#include <ti/mathlib/src/cossp/c66/cossp.h>
#include <ti/mathlib/src/sinsp/c66/sinsp.h>
#endif

static void complex_sp_inv(__float2_t cy,__float2_t *cz);

int DSPF_sp_lud_cmplx(const int Nrows, float *restrict A, float *restrict L,float *restrict U,unsigned short *restrict P)
{
  int row,col,Ncols;
  int min_row,max_row,k,temp;
  float mag,min,max;
  __float2_t ctemp,cy,cz;
  __float2_t *AA,*LL,*UU;
  int addr;

  _nassert(Nrows>0);
  _nassert((int)A % 8 == 0);
  _nassert((int)L % 8 == 0);
  _nassert((int)U % 8 == 0);
  _nassert((int)P % 2 == 0);

  /* initialize __float2_t arrays to overlay input float arrays */
  addr=(int)(&A[0]);
  AA=(__float2_t *)(addr);
  addr=(int)(&L[0]);
  LL=(__float2_t *)(addr);
  addr=(int)(&U[0]);
  UU=(__float2_t *)(addr);

  /* ------------------------------------------------------------------- */
  /* generate identify matrix                                            */
  /* ------------------------------------------------------------------- */
  memset(P,0,sizeof(unsigned short)*Nrows*Nrows);
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
	P[row+row*Nrows]=1;
  }

  /* ------------------------------------------------------------------- */
  /* LU decomposition                                                    */
  /* ------------------------------------------------------------------- */
  Ncols=Nrows;
  memcpy(UU,AA,sizeof(__float2_t)*Nrows*Ncols);
#pragma MUST_ITERATE(1,,)
  for (k=0;k<Nrows-1;k++) {

    /* find min and max entries in column */
    max=0.0;
    min=3.4e+38;
#pragma MUST_ITERATE(1,,)
    for (row=k;row<Nrows;row++) {
      ctemp= _dmpysp(UU[k+row*Ncols],UU[k+row*Ncols]);
      mag=sqrt(_hif2(ctemp)+_lof2(ctemp));


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
#pragma MUST_ITERATE(1,,)
      for (col=0;col<Nrows;col++) {
    	ctemp=UU[col+min_row*Ncols];
      	UU[col+min_row*Ncols]=UU[col+max_row*Ncols];
      	UU[col+max_row*Ncols]=ctemp;
       	temp=P[col+min_row*Nrows];
    	P[col+min_row*Nrows]=P[col+max_row*Nrows];
    	P[col+max_row*Nrows]=temp;
      }
    }

    /* generate U matrix */
    cy=UU[k+k*Ncols];
	complex_sp_inv(cy,&cz);

#pragma MUST_ITERATE(1,,)
    for (row=k+1;row<Nrows;row++) {
#ifndef _LITTLE_ENDIAN
      UU[k+row*Ncols]=_complex_mpysp(UU[k+row*Ncols],cz);
#else
      ctemp=_complex_mpysp(UU[k+row*Ncols],cz);
      UU[k+row*Ncols]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
    }
#pragma MUST_ITERATE(1,,)
    for (row=k+1;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
      for (col=k+1;col<Nrows;col++) {
#ifndef _LITTLE_ENDIAN
    	UU[col+row*Ncols]=_dsubsp(UU[col+row*Ncols],_complex_mpysp(UU[k+row*Ncols],UU[col+k*Ncols]));
#else
    	ctemp=_complex_mpysp(UU[k+row*Ncols],UU[col+k*Ncols]);
    	UU[col+row*Ncols]=_dsubsp(UU[col+row*Ncols],_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
      }
    }
  }

    /* extract lower triangular entries from L into U and set L lower entries to zero */
#pragma MUST_ITERATE(1,,)
    for (row=0;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
      for (col=0;col<Nrows;col++) {
        if (row<col) {
          LL[col+row*Ncols]=_ftof2(0,0);
        } else {
          if (row==col) {
#ifndef _LITTLE_ENDIAN
        	LL[col+row*Ncols]=_ftof2(1,0);
#else
        	LL[col+row*Ncols]=_ftof2(0,1);
#endif
          } else {
        	LL[col+row*Ncols]=UU[col+row*Ncols];
        	UU[col+row*Ncols]=_ftof2(0,0);
          }
        }
      }
    }

  return 0;
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
/*  End of file:  DSPF_sp_lud_cmplx                                        */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
