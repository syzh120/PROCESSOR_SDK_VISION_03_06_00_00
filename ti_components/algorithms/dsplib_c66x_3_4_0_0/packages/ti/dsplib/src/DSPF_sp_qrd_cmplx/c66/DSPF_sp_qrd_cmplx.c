/* ======================================================================= */
/* DSPF_sp_qrd_cmplx.c -- lower/upper decomposition                        */
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
#include <c6x.h>

#pragma CODE_SECTION(DSPF_sp_qrd_cmplx,".text:optimized");

#include "DSPF_sp_qrd_cmplx.h"

#define ENABLE_NR      1
#define ENABLE_MATHLIB 1

#ifdef ENABLE_MATHLIB
#include <ti/mathlib/src/atan2sp/c66/atan2sp.h>
#include <ti/mathlib/src/cossp/c66/cossp.h>
#include <ti/mathlib/src/sinsp/c66/sinsp.h>
#endif

static void complex_sp_inv(__float2_t cx,__float2_t *cz);
static void complex_sp_div(__float2_t cx,__float2_t cy,__float2_t *cz);

int DSPF_sp_qrd_cmplx(const int Nrows,const int Ncols, float *restrict A, float *restrict Q,float *restrict R,float *restrict u)
{
  int row,col,i,k,loop_count;
  int addr;
  float summ,alpha;
  __float2_t *QQ,*RR,*uu;
  __float2_t sum,cz,scale;
#ifdef _LITTLE_ENDIAN
  __float2_t ctemp;
#endif

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)A % 8 == 0);
  _nassert((int)Q % 8 == 0);
  _nassert((int)R % 8 == 0);
  _nassert((int)u % 8 == 0);

  /* initialize __float2_t arrays to overlay input float arrays */
  addr=(int)(&Q[0]);
  QQ=(__float2_t *)(addr);
  addr=(int)(&R[0]);
  RR=(__float2_t *)(addr);
  addr=(int)(&u[0]);
  uu=(__float2_t *)(addr);

  /* ------------------------------------------------------------------- */
   /* generate identify matrix and copy A to R                            */
   /* ------------------------------------------------------------------- */
   memcpy(R,A,sizeof(float)*Nrows*2*Ncols);
   memset(Q,0.0,sizeof(float)*Nrows*2*Nrows);
   for (row=0;row<Nrows;row++) {
 	 Q[2*row  +row*2*Nrows] = 1.0;
   }

  if (Nrows<=Ncols) {
	loop_count=Nrows-2;
  } else {
	loop_count=Ncols-1;
  }
  for (col=0;col<=loop_count;col++) {
    sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
    for (row=col;row<Nrows;row++) {
#ifndef _LITTLE_ENDIAN
      sum=_daddsp(sum,_complex_conjugate_mpysp(RR[col+row*Ncols],RR[col+row*Ncols]));
#else
      ctemp=_complex_conjugate_mpysp(RR[col+row*Ncols],RR[col+row*Ncols]);
      sum=_daddsp(sum,_ftof2(-_lof2(ctemp),_hif2(ctemp)));
#endif
    }
#ifndef _LITTLE_ENDIAN
    summ=_hif2(sum);
#else
    summ=_lof2(sum);
#endif
    if (summ!=0) {
      alpha=-sqrt(summ);
      if (R[2*col  +col*2*Ncols]>=0) {
    	alpha=-alpha;
      }
      u[2*col  ]=R[2*col  +col*2*Ncols]+alpha;
      u[2*col+1]=R[2*col+1+col*2*Ncols];
      R[2*col  +col*2*Ncols]=-alpha;
      R[2*col+1+col*2*Ncols]=0;
#pragma MUST_ITERATE(1,,)
      for (row=col+1;row<Nrows;row++) {
    	uu[row]=RR[col+row*Ncols];
    	RR[col+row*Ncols]=_ftof2(0,0);
      }
      cz=_dmpysp(_ftof2(alpha,alpha),uu[col]);
      if ((_hif2(cz)!=0)||(_lof2(cz)!=0)) {
    	complex_sp_inv(cz,&scale);
    	/* R=Q1*R */
    	for (i=col+1;i<Ncols;i++) {
          sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
          for (k=col;k<Nrows;k++) {
#ifndef _LITTLE_ENDIAN
        	sum=_daddsp(sum,_complex_conjugate_mpysp(uu[k],RR[i+k*Ncols]));
#else
        	ctemp=_complex_conjugate_mpysp(uu[k],RR[i+k*Ncols]);
        	sum=_daddsp(sum,_ftof2(-_lof2(ctemp),_hif2(ctemp)));
#endif
          }
#ifndef _LITTLE_ENDIAN
          sum=_complex_mpysp(sum,scale);
#else
          ctemp=_complex_mpysp(sum,scale);
          sum=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
#pragma MUST_ITERATE(1,,)
          for (k=col;k<Nrows;k++) {
#ifndef _LITTLE_ENDIAN
        	RR[i+k*Ncols]=_dsubsp(RR[i+k*Ncols],_complex_mpysp(uu[k],sum));
#else
        	ctemp=_complex_mpysp(uu[k],sum);
        	RR[i+k*Ncols]=_dsubsp(RR[i+k*Ncols],_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
          }
    	}
    	/* Q=A*Q1 */
    	for (i=0;i<Nrows;i++) {
      	  sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
    	  for (k=col;k<Nrows;k++) {
#ifndef _LITTLE_ENDIAN
      		sum=_daddsp(sum,_complex_conjugate_mpysp(uu[k],QQ[k+i*Nrows]));
#else
      		ctemp=_complex_conjugate_mpysp(uu[k],QQ[k+i*Nrows]);
      		sum=_daddsp(sum,_ftof2(-_lof2(ctemp),_hif2(ctemp)));
#endif
    	  }
#ifndef _LITTLE_ENDIAN
    	  sum=_complex_mpysp(sum,scale);
#else
    	  ctemp=_complex_mpysp(sum,scale);
    	  sum=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
#pragma MUST_ITERATE(1,,)
    	  for (k=col;k<Nrows;k++) {
#ifndef _LITTLE_ENDIAN
      		QQ[k+i*Nrows]=_dsubsp(QQ[k+i*Nrows],_complex_mpysp(uu[k],sum));
#else
      		ctemp=_complex_mpysp(uu[k],sum);
      		QQ[k+i*Nrows]=_dsubsp(QQ[k+i*Nrows],_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
    	  }
    	}
      } /* if (norm_sqr!=0) */
    } /* if (sum!=0) */
  } /* for (col=0;col<=loop_count;col++) */

  /* Q=conj(Q) */
  for (row=0;row<Nrows;row++) {
	for (col=0;col<Nrows;col++) {
	  Q[2*col+1+row*2*Nrows]=-Q[2*col+1+row*2*Nrows];
	}
  }

  return 0;
}

int DSPF_sp_qrd_solver_cmplx(const int Nrows,const int Ncols,float *restrict Q,float *restrict R,float *restrict b,float *restrict y,float *restrict x) {

  short row,col,loop_cnt;
  int addr;
  __float2_t *QQ,*RR,*bb,*yy,*xx;
  __float2_t sum,cx,cy,cz;
#ifdef _LITTLE_ENDIAN
  __float2_t ctemp;
#endif

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)Q % 8 == 0);
  _nassert((int)R % 8 == 0);
  _nassert((int)b % 8 == 0);
  _nassert((int)y % 8 == 0);
  _nassert((int)x % 8 == 0);

  /* initialize __float2_t arrays to overlay input float arrays */
  addr=(int)(&Q[0]);
  QQ=(__float2_t *)(addr);
  addr=(int)(&R[0]);
  RR=(__float2_t *)(addr);
  addr=(int)(&b[0]);
  bb=(__float2_t *)(addr);
  addr=(int)(&y[0]);
  yy=(__float2_t *)(addr);
  addr=(int)(&x[0]);
  xx=(__float2_t *)(addr);

  /* generate y=Q'*b */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
	sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Nrows;col++) {
#ifndef _LITTLE_ENDIAN
	  sum=_daddsp(sum,_complex_conjugate_mpysp(QQ[row+col*Nrows],bb[col]));
#else
	  ctemp=_complex_conjugate_mpysp(QQ[row+col*Nrows],bb[col]);
	  sum=_daddsp(sum,_ftof2(-_lof2(ctemp),_hif2(ctemp)));
#endif
	}
	yy[row]=sum;
  }

  /* use backward substitution to solve x=inv(R)*y */
  if (Nrows>=Ncols) loop_cnt=Ncols;
  else              loop_cnt=Nrows;
  memset(x,0,sizeof(float)*2*Ncols);
#pragma MUST_ITERATE(1,,)
  for (row=loop_cnt-1;row>=0;row--) {
	sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
	for (col=row+1;col<loop_cnt;col++) {
#ifndef _LITTLE_ENDIAN
	  sum=_daddsp(sum,_complex_mpysp(RR[col+row*Ncols],xx[col]));
#else
	  ctemp=_complex_mpysp(RR[col+row*Ncols],xx[col]);
	  sum=_daddsp(sum,_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
	}
	cx=_dsubsp(yy[row],sum);
	cy=RR[row+row*Ncols];
	complex_sp_div(cx,cy,&cz);
	xx[row]=cz;
  }

  return 0;
}

int DSPF_sp_qrd_inverse_cmplx(const int Nrows,const int Ncols,float *restrict Q,float *restrict R,float *restrict inv_A) {

  int row,col,k;
  int addr;
  __float2_t *QQ,*RR,*inv_AA;
  __float2_t sum,factor,cx,cz;
#ifdef _LITTLE_ENDIAN
  __float2_t ctemp;
#endif

  _nassert(Nrows>0);
  _nassert(Ncols>0);
  _nassert((int)Q % 8 == 0);
  _nassert((int)R % 8 == 0);
  _nassert((int)inv_A % 8 == 0);

  /* initialize __float2_t arrays to overlay input float arrays */
  addr=(int)(&Q[0]);
  QQ=(__float2_t *)(addr);
  addr=(int)(&R[0]);
  RR=(__float2_t *)(addr);
  addr=(int)(&inv_A[0]);
  inv_AA=(__float2_t *)(addr);

  /* set inv_A matrix to identity */
  memset(inv_A,0.0,sizeof(float)*Nrows*2*Ncols);
  for (row=0;row<Nrows;row++) {
	inv_A[2*row  +row*2*Ncols]=1.0;
  }

  /* use Gauss Jordan algorithm to invert R whose result will be in inv_A */
#pragma MUST_ITERATE(1,,)
  for (col=Ncols-1;col>=1;col--) {
	cx=RR[col+col*Ncols];
	complex_sp_inv(cx,&cz);

#pragma MUST_ITERATE(1,,)
	for (row=col-1;row>=0;row--) {
#ifndef _LITTLE_ENDIAN
	  factor=_complex_mpysp(RR[col+row*Ncols],cz);
#else
	  ctemp=_complex_mpysp(RR[col+row*Ncols],cz);
	  factor=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
#pragma MUST_ITERATE(1,,)
	  for (k=0;k<Ncols;k++) {
#ifndef _LITTLE_ENDIAN
		inv_AA[k+row*Ncols]=_dsubsp(inv_AA[k+row*Ncols],_complex_mpysp(factor,inv_AA[k+col*Ncols]));
		RR[k+row*Ncols]=_dsubsp(RR[k+row*Ncols],_complex_mpysp(factor,RR[k+col*Ncols]));
#else
		ctemp=_complex_mpysp(factor,inv_AA[k+col*Ncols]);
		inv_AA[k+row*Ncols]=_dsubsp(inv_AA[k+row*Ncols],_ftof2(_lof2(ctemp),-_hif2(ctemp)));
		ctemp=_complex_mpysp(factor,RR[k+col*Ncols]);
		RR[k+row*Ncols]=_dsubsp(RR[k+row*Ncols],_ftof2(_lof2(ctemp),-_hif2(ctemp)));
#endif
	  }
	}
  }

  /* scale R and inv_A to get identity matrix in R */
#pragma MUST_ITERATE(1,,)
  for (row=Nrows-1;row>=0;row--) {
	cx=RR[row+row*Ncols];
	complex_sp_inv(cx,&factor);

#pragma MUST_ITERATE(1,,)
	for (col=0;col<Ncols;col++) {
#ifndef _LITTLE_ENDIAN
	  inv_AA[col+row*Ncols]=_complex_mpysp(factor,inv_AA[col+row*Ncols]);
#else
	  ctemp=_complex_mpysp(factor,inv_AA[col+row*Ncols]);
	  inv_AA[col+row*Ncols]=_ftof2(_lof2(ctemp),-_hif2(ctemp));
#endif
	}
  }

  /* inv_A = inv_R * Q' */
#pragma MUST_ITERATE(1,,)
  for (row=0;row<Nrows;row++) {
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Ncols;col++) {
	  sum=_ftof2(0,0);
#pragma MUST_ITERATE(1,,)
      for (k=0;k<Ncols;k++) {
#ifndef _LITTLE_ENDIAN
        sum=_daddsp(sum,_complex_conjugate_mpysp(QQ[k+col*Ncols],inv_AA[k+row*Ncols]));
#else
    	ctemp=_complex_conjugate_mpysp(QQ[k+col*Ncols],inv_AA[k+row*Ncols]);
    	sum=_daddsp(sum,_ftof2(-_lof2(ctemp),_hif2(ctemp)));
#endif
      }
      RR[col]=sum;
	}
#pragma MUST_ITERATE(1,,)
	for (col=0;col<Ncols;col++) {
	  inv_AA[col+row*Ncols]=RR[col];
	}
  }

  return 0;
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
/*  End of file:  DSPF_sp_qrd_cmplx.c                                      */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
