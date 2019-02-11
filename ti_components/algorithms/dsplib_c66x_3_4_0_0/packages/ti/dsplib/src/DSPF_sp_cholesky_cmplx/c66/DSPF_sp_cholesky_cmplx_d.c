/* ======================================================================= */
/* DSPF_sp_cholesky_cmplx_d.c -- Cholesky decomposition and solver driver  */
/*                               code using single precision               */
/*   1. Generate symmetric A matrix using random numbers                   */
/*   2. Tests A for positive definiteness                                  */
/*   3. Decomposes A into lower triangular matrix L using basic and in     */
/*      place methods                                                      */
/*   4. Solver solves A*x=b for x using forward and backward substitution  */
/*      a. A*x = L*L_transpose*x = b                                       */
/*      b. y = inverse(L)*b - done using forward substitution              */
/*      c. x = inverse(L_transpose)*y - done using backward substitution   */
/*   5. Recomputes b_calc=A*x                                              */
/*   6. Computes average percent error = 100*sum(abs(b-b_calc)/b)/Nrows    */
/*   7. Measures number of CPU cycles for decomposition and solver         */
/*                                                                         */
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
/*    Redistributions in binary form must rep roduce the above copyright   */
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
/* ======================================================================= */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <c6x.h>

/* ======================================================================= */
/* Interface header files for the natural C and optimized C code           */
/* ======================================================================= */
#include "DSPF_sp_cholesky_cmplx_cn.h"
#include "DSPF_sp_cholesky_cmplx.h"

/* ======================================================================= */
/* define kernel size constant                                             */
/* ======================================================================= */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#endif

/* ======================================================================= */
/* extern parameters                                                       */
/* ======================================================================= */
extern char kernel_size;

/* ======================================================================= */
/* define size constants                                                   */
/* ======================================================================= */

#define MAX_MATRIX_NROWS   64 /* max is 240 */
#define MAX_A_MATRIX_SIZE (2*MAX_MATRIX_NROWS*MAX_MATRIX_NROWS)

/* ======================================================================= */
/* formula arrays                                                          */
/* ======================================================================= */
#define CYCLE_FORMULA_ORDER_PT1  32
#define CYCLE_FORMULA_ORDER_PT2  64
#define FORMULA_SIZE  2
long long form_cholesky_cycles[FORMULA_SIZE];

/* ======================================================================= */
/* float word alignment of arrays                                         */
/* ======================================================================= */
#pragma DATA_SECTION(M,".far:matrix")
#pragma DATA_ALIGN(M,8);
float M[MAX_A_MATRIX_SIZE];

#pragma DATA_SECTION(A,".far:matrix")
#pragma DATA_ALIGN(A,8);
float A[MAX_A_MATRIX_SIZE];

#ifndef ENABLE_DECOMP_ONLY
#pragma DATA_SECTION(x,".far:matrix")
#pragma DATA_ALIGN(x,8);
float x[2*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(x_in_place,".far:matrix")
#pragma DATA_ALIGN(x_in_place,8);
float x_in_place[2*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(y,".far:matrix")
#pragma DATA_ALIGN(y,8);
float y[2*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(b,".far:matrix")
#pragma DATA_ALIGN(b,8);
float b[2*MAX_MATRIX_NROWS];
#endif

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */
void main() {
	
  unsigned short Nrows,pass;
  float xreal,ximag,yreal,yimag,zreal,zimag;
  float sum_real,sum_imag;
  float error_real,error_imag;
  float b_calc_real,b_calc_imag;
  float max_cholesky_error_cn,max_solver_error_cn,max_cholesky_in_place_error_cn,max_solver_in_place_error_cn;
  float max_cholesky_error,max_solver_error,max_cholesky_in_place_error,max_solver_in_place_error;
  int i,j,k,status,enable_test,Ncols;
  int row,col,loop_limit;
  long long t_overhead, t_start, t_stop;
  long long cholesky_t_cn;
  long long cholesky_t, cholesky_in_place_t, solver_t;
  float *L,*A_in_place;
  int test;
  float tolerance=0.00004;
  float tolerance_solver=0.003;

  /* --------------------------------------------------------------------- */
  /* intialize hardware timers                                             */
  /* --------------------------------------------------------------------- */
  TSCL= 0,TSCH=0;

  /* --------------------------------------------------------------------- */
  /* Compute the overhead of calling clock twice to get timing info        */
  /* --------------------------------------------------------------------- */
  t_start = _itoll(TSCH, TSCL);
  t_stop = _itoll(TSCH, TSCL);
  t_overhead = t_stop - t_start;

  /* --------------------------------------------------------------------- */
  /* process matrix Nrows loop                                             */
  /* --------------------------------------------------------------------- */
  pass=1;
  for (test=1;test<=3;test++) {

	printf("DSPF_sp_cholesky_cmplx\tIter#: %d\t", test);
  
	switch(test) {
	  case 1: { Nrows=3;
                M[ 0]= 2;M[ 1]= 0;M[ 2]= 2;M[ 3]= 1;M[ 4]= 4;M[ 5]= 0;
                M[ 6]= 2;M[ 7]=-1;M[ 8]= 3;M[ 9]= 0;M[10]= 0;M[11]= 1;
                M[12]= 4;M[13]= 0;M[14]= 0;M[15]=-1;M[16]= 1;M[17]= 0;
               break;
	          }
	  case 2: { Nrows=CYCLE_FORMULA_ORDER_PT1;
	            Ncols=Nrows;
	            srand(1);
			    for (row=0;row<Nrows;row++) {
			      for (col=0;col<2*Ncols;col++) {
			        M[row*2*Ncols+col]=(float)(rand())/((float)RAND_MAX);
			      }
			    }
		        break;
	          }
	  case 3: { Nrows=CYCLE_FORMULA_ORDER_PT2;
	            Ncols=Nrows;
	            srand(1);
			    for (row=0;row<Nrows;row++) {
			      for (col=0;col<2*Ncols;col++) {
			        M[row*2*Ncols+col]=(float)(rand())/((float)RAND_MAX);
			      }
			    }
		        break;
	          }
	}

	/* ------------------------------------------------------------------- */
	/* generate symmetric A matrix: A=M*M_transpose                        */
	/* ------------------------------------------------------------------- */
    Ncols=2*Nrows;
	for (i=0;i<Nrows;i++) {
	  for (j=0;j<Nrows;j++) {
		sum_real=0;
		sum_imag=0;
		for (k=0;k<Nrows;k++) {
			  xreal= M[i*Ncols+2*k  ];
			  ximag= M[i*Ncols+2*k+1];
			  yreal= M[j*Ncols+2*k  ];
			  yimag=-M[j*Ncols+2*k+1];
		  sum_real+=xreal*yreal-ximag*yimag;
		  sum_imag+=xreal*yimag+ximag*yreal;
	    }
	    A[i*Ncols+2*j  ]=sum_real;
	    A[i*Ncols+2*j+1]=sum_imag;
	  }
	}
	memset(M,0.0,sizeof(float)*2*Nrows*Nrows);

    /* ------------------------------------------------------------------- */
	/* generate b vector                                                   */
    /* ------------------------------------------------------------------- */
	for (i=0;i<2*Nrows;i++) {
	  b[i]=(float)(rand())/((float)RAND_MAX);
	}

    /* ------------------------------------------------------------------- */
    /* decompose A and generate L using natural C code                     */
    /* ------------------------------------------------------------------- */
	enable_test=1;
	L=&M[0];
    TSCL= 0,TSCH=0;
	t_start = _itoll(TSCH, TSCL);
    status=DSPF_sp_cholesky_cmplx_cn(enable_test,Nrows,A,L);
    t_stop = _itoll(TSCH, TSCL);
    cholesky_t_cn=t_stop-t_start-t_overhead;
    if (status==-1) {
      printf("cholesky decomposition matrix A is not positive definite!\n");
    }

    /* ------------------------------------------------------------------- */
    /* check decomposition results                                         */
    /* ------------------------------------------------------------------- */
    max_cholesky_error_cn=0;
    Ncols=2*Nrows;
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
    	sum_real=0;
    	sum_imag=0;
    	for (k=0;k<Nrows;k++) {
          xreal= L[2*k  +row*Ncols];
          ximag= L[2*k+1+row*Ncols];
          yreal= L[2*k  +col*Ncols];
          yimag=-L[2*k+1+col*Ncols];
      	  zreal=xreal*yreal-ximag*yimag;
      	  zimag=ximag*yreal+xreal*yimag;
      	  sum_real+=zreal;
      	  sum_imag+=zimag;
    	}
    	error_real=fabs(sum_real-A[2*col  +row*Ncols]);
    	if (error_real>max_cholesky_error_cn) max_cholesky_error_cn=error_real;
    	error_imag=fabs(sum_imag-A[2*col+1+row*Ncols]);
    	if (error_imag>max_cholesky_error_cn) max_cholesky_error_cn=error_imag;
    	if (error_real>tolerance) {
      	  printf("nat C: row=%d col=%d A=%e sum=%e error=%e\n",row,col,A[2*col  +row*Ncols],sum_real,error_real);
    	  pass=0;
    	}
    	if (error_imag>tolerance) {
      	  printf("nat C: row=%d col=%d A=%e sum=%e error=%e\n",row,col,A[2*col+1+row*Ncols],sum_imag,error_imag);
    	  pass=0;
    	}
      }
    }

    /* ------------------------------------------------------------------- */
    /* solve for x using natural C code                                    */
    /* ------------------------------------------------------------------- */
    status=DSPF_sp_cholesky_solver_cmplx_cn(Nrows,L,y,b,x);

    /* ------------------------------------------------------------------- */
    /* check A*x=b                                                         */
    /* ------------------------------------------------------------------- */
    max_solver_error_cn=0;
    Ncols=2*Nrows;
    for (i=0;i<Nrows;i++) {
      b_calc_real=0;
      b_calc_imag=0;
      for (j=0;j<Nrows;j++) {
      	xreal=A[i*Ncols+2*j  ];
      	ximag=A[i*Ncols+2*j+1];
      	yreal=x[2*j  ];
      	yimag=x[2*j+1];
       	b_calc_real+=xreal*yreal-ximag*yimag;
    	b_calc_imag+=xreal*yimag+ximag*yreal;
      }
      error_real=fabs(b_calc_real-b[2*i  ]);
      if (error_real>max_solver_error_cn) max_solver_error_cn=error_real;
      error_imag=fabs(b_calc_imag-b[2*i+1]);
      if (error_imag>max_solver_error_cn) max_solver_error_cn=error_imag;
      if (error_real>=tolerance_solver) {
      	printf("nat C:  A*x_cn=b test failure at i=%d b_calc_real=%e b[2*%d  ]=%e  error_real=%e\n",i,b_calc_real,i,b[2*i],error_real);
      	pass=0;
      }
      if (error_imag>=tolerance_solver) {
      	printf("nat C:  A*x_cn=b test failure at i=%d b_calc_imag=%e b[2*%d+1]=%e  error_imag=%e\n",i,b_calc_imag,i,b[2*i+1],error_imag);
    	pass=0;
      }
    }

    /* ------------------------------------------------------------------- */
    /* decompose A and generate L using optimized C code                   */
    /* ------------------------------------------------------------------- */
	enable_test=1;
	memset(M,0.0,sizeof(float)*2*Nrows*Nrows);
    L=&M[0];
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_sp_cholesky_cmplx(enable_test,Nrows,A,L);
    t_stop = _itoll(TSCH, TSCL);
    if (status==-1) {
      printf("cholesky decomposition matrix A is not positive definite!\n");
    }
    cholesky_t=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* check decomposition results                                         */
    /* ------------------------------------------------------------------- */
    max_cholesky_error=0;
    Ncols=2*Nrows;
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
    	sum_real=0;
    	sum_imag=0;
    	for (k=0;k<Nrows;k++) {
      	  xreal= L[2*k  +row*Ncols];
      	  ximag= L[2*k+1+row*Ncols];
      	  yreal= L[2*k  +col*Ncols];
      	  yimag=-L[2*k+1+col*Ncols];
      	  zreal=xreal*yreal-ximag*yimag;
      	  zimag=ximag*yreal+xreal*yimag;
      	  sum_real+=zreal;
      	  sum_imag+=zimag;
    	}
    	error_real=fabs(sum_real-A[2*col  +row*Ncols]);
    	if (error_real>max_cholesky_error) max_cholesky_error=error_real;
    	error_imag=fabs(sum_imag-A[2*col+1+row*Ncols]);
    	if (error_imag>max_cholesky_error) max_cholesky_error=error_imag;
    	if (error_real>tolerance) {
      	  printf("opt C: row=%d col=%d A=%e sum=%e error=%e\n",row,col,A[2*col  +row*Ncols],sum_real,error_real);
      	  pass=0;
      	}
      	if (error_imag>tolerance) {
      	  printf("opt C: row=%d col=%d A=%e sum=%e error=%e\n",row,col,A[2*col+1+row*Ncols],sum_imag,error_imag);
    	  pass=0;
    	}
      }
    }

    /* ------------------------------------------------------------------- */
    /* solve for x using optimized C code                                  */
    /* ------------------------------------------------------------------- */
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_sp_cholesky_solver_cmplx(Nrows,L,y,b,x);
    t_stop = _itoll(TSCH, TSCL);
    solver_t=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* check A*x=b                                                         */
    /* ------------------------------------------------------------------- */
    max_solver_error=0;
    Ncols=2*Nrows;
    for (i=0;i<Nrows;i++) {
      b_calc_real=0;
      b_calc_imag=0;
      for (j=0;j<Nrows;j++) {
      	xreal=A[i*Ncols+2*j  ];
      	ximag=A[i*Ncols+2*j+1];
      	yreal=x[2*j  ];
      	yimag=x[2*j+1];
    	b_calc_real+=xreal*yreal-ximag*yimag;
    	b_calc_imag+=xreal*yimag+ximag*yreal;
      }
      error_real=fabs(b_calc_real-b[2*i  ]);
      if (error_real>max_solver_error) max_solver_error=error_real;
      error_imag=fabs(b_calc_imag-b[2*i+1]);
      if (error_imag>max_solver_error) max_solver_error=error_imag;
      if (error_real>=tolerance_solver) {
      	printf("nat C:  A*x_cn=b test failure at i=%d b_calc_real=%e b[2*%d]=%e  error_real=%e\n",i,b_calc_real,i,b[2*i  ],error_real);
      	pass=0;
      }
      if (error_imag>=tolerance_solver) {
      	printf("nat C:  A*x_cn=b test failure at i=%d b_calc_imag=%e b[2*%d+1]=%e  error_imag=%e\n",i,b_calc_imag,i,b[2*i+1],error_imag);
    	pass=0;
      }
    }

    /* ------------------------------------------------------------------- */
    /* decompose A_in_place_cn in place using natural C code               */
    /* ------------------------------------------------------------------- */
    A_in_place=&M[0];
    Ncols=2*Nrows;
	for (i=0;i<Nrows;i++) {
	  for (j=0;j<Nrows;j++) {
	    A_in_place[i*Ncols+2*j]=A[i*Ncols+2*j];
	    A_in_place[i*Ncols+2*j+1]=A[i*Ncols+2*j+1];
	  }
	}
    enable_test=1;
    status=DSPF_sp_cholesky_in_place_cmplx_cn(enable_test,Nrows,A_in_place);
    if (status==-1) {
      printf("cholesky decomposition matrix A is not positive definite!\n");
     }

    /* ------------------------------------------------------------------- */
    /* check decomposition results                                         */
    /* ------------------------------------------------------------------- */
    L=&A_in_place[0];
    max_cholesky_in_place_error_cn=0;
    Ncols=2*Nrows;
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
    	sum_real=0;
    	sum_imag=0;
    	if (row<col) loop_limit=row;
        else         loop_limit=col;
    	for (k=0;k<=loop_limit;k++) {
      	  xreal= L[2*k  +row*Ncols];
      	  ximag= L[2*k+1+row*Ncols];
      	  yreal= L[2*k  +col*Ncols];
      	  yimag=-L[2*k+1+col*Ncols];
      	  zreal=xreal*yreal-ximag*yimag;
      	  zimag=ximag*yreal+xreal*yimag;
      	  sum_real+=zreal;
      	  sum_imag+=zimag;
    	}
    	error_real=fabs(sum_real-A[2*col  +row*Ncols]);
    	if (error_real>max_cholesky_in_place_error_cn) max_cholesky_in_place_error_cn=error_real;
    	error_imag=fabs(sum_imag-A[2*col+1+row*Ncols]);
    	if (error_imag>max_cholesky_in_place_error_cn) max_cholesky_in_place_error_cn=error_imag;
    	if (error_real>tolerance) {
      	  printf("opt C: row=%d col=%d A=%e sum=%e error=%e\n",row,col,A[2*col  +row*Ncols],sum_real,error_real);
      	  pass=0;
      	}
      	if (error_imag>tolerance) {
          printf("opt C: row=%d col=%d A=%e sum=%e error=%e\n",row,col,A[2*col+1+row*Ncols],sum_imag,error_imag);
       	  pass=0;
    	}
      }
    }

    /* ------------------------------------------------------------------- */
    /* solve for x using A_in_place using natural C code                   */
    /* ------------------------------------------------------------------- */
    status=DSPF_sp_cholesky_solver_cmplx_cn(Nrows,A_in_place,y,b,x);
    if (status==-1) {
      printf("solver fails!\n");
    }

    /* ------------------------------------------------------------------- */
    /* check A*x=b and compute max error                                   */
    /* ------------------------------------------------------------------- */
    max_solver_in_place_error_cn=0;
    Ncols=2*Nrows;
    for (i=0;i<Nrows;i++) {
      b_calc_real=0;
      b_calc_imag=0;
      for (j=0;j<Nrows;j++) {
      	xreal=A[i*Ncols+2*j  ];
      	ximag=A[i*Ncols+2*j+1];
      	yreal=x[2*j  ];
      	yimag=x[2*j+1];
    	b_calc_real+=xreal*yreal-ximag*yimag;
    	b_calc_imag+=xreal*yimag+ximag*yreal;
      }
      error_real=fabs(b_calc_real-b[2*i  ]);
      if (error_real>max_solver_in_place_error_cn) max_solver_in_place_error_cn=error_real;
      error_imag=fabs(b_calc_imag-b[2*i+1]);
      if (error_imag>max_solver_in_place_error_cn) max_solver_in_place_error_cn=error_imag;
      if (error_real>=tolerance_solver) {
      	printf("nat C:  A*x_cn=b test failure at i=%d b_calc_real=%e b[2*%d]=%e  error_real=%e\n",i,b_calc_real,i,b[2*i  ],error_real);
      	pass=0;
      }
      if (error_imag>=tolerance_solver) {
      	printf("nat C:  A*x_cn=b test failure at i=%d b_calc_imag=%e b[2*%d+1]=%e  error_imag=%e\n",i,b_calc_imag,i,b[2*i+1],error_imag);
    	pass=0;
      }
    }

    /* ------------------------------------------------------------------- */
    /* decompose A_in_place_opt in place using optimized C code            */
    /* ------------------------------------------------------------------- */
    A_in_place=&M[0];
    Ncols=2*Nrows;
	for (i=0;i<Nrows;i++) {
	  for (j=0;j<Nrows;j++) {
	    A_in_place[i*Ncols+2*j]=A[i*Ncols+2*j];
	    A_in_place[i*Ncols+2*j+1]=A[i*Ncols+2*j+1];
	  }
	}
    enable_test=1;
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_sp_cholesky_in_place_cmplx(enable_test,Nrows,A_in_place);
    t_stop = _itoll(TSCH, TSCL);
    if (status==-1) {
      printf("cholesky decomposition matrix A is not positive definite!\n");
    }
    cholesky_in_place_t=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* check decomposition results                                         */
    /* ------------------------------------------------------------------- */
    L=&A_in_place[0];
    max_cholesky_in_place_error=0;
    Ncols=2*Nrows;
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
    	sum_real=0;
    	sum_imag=0;
    	if (row<col) loop_limit=row;
        else         loop_limit=col;
    	for (k=0;k<=loop_limit;k++) {
      	  xreal= L[2*k  +row*Ncols];
      	  ximag= L[2*k+1+row*Ncols];
      	  yreal= L[2*k  +col*Ncols];
      	  yimag=-L[2*k+1+col*Ncols];
      	  zreal=xreal*yreal-ximag*yimag;
      	  zimag=ximag*yreal+xreal*yimag;
      	  sum_real+=zreal;
      	  sum_imag+=zimag;
    	}
    	error_real=fabs(sum_real-A[2*col  +row*Ncols]);
    	if (error_real>max_cholesky_in_place_error) max_cholesky_in_place_error=error_real;
    	error_imag=fabs(sum_imag-A[2*col+1+row*Ncols]);
    	if (error_imag>max_cholesky_in_place_error) max_cholesky_in_place_error=error_imag;
    	if (error_real>tolerance) {
      	  printf("opt C: row=%d col=%d A=%e sum=%e error=%e\n",row,col,A[2*col  +row*Ncols],sum_real,error_real);
      	  pass=0;
      	}
      	if (error_imag>tolerance) {
      	  printf("opt C: row=%d col=%d A=%e sum=%e error=%e\n",row,col,A[2*col+1+row*Ncols],sum_imag,error_imag);
    	  pass=0;
    	}
      }
    }

    /* ------------------------------------------------------------------- */
    /* solve for x using A_in_place using optimized C code                 */
    /* ------------------------------------------------------------------- */
    status=DSPF_sp_cholesky_solver_cmplx(Nrows,A_in_place,y,b,x);
    if (status==-1) {
      printf("solver fails!\n");
     }

    /* ------------------------------------------------------------------- */
    /* check A*x=b and compute max error                                   */
    /* ------------------------------------------------------------------- */
    max_solver_in_place_error=0;
    Ncols=2*Nrows;
    for (i=0;i<Nrows;i++) {
      b_calc_real=0;
      b_calc_imag=0;
      for (j=0;j<Nrows;j++) {
      	xreal=A[i*Ncols+2*j  ];
      	ximag=A[i*Ncols+2*j+1];
      	yreal=x[2*j  ];
      	yimag=x[2*j+1];
    	b_calc_real+=xreal*yreal-ximag*yimag;
    	b_calc_imag+=xreal*yimag+ximag*yreal;
      }
      error_real=fabs(b_calc_real-b[2*i  ]);
      if (error_real>max_solver_in_place_error) max_solver_in_place_error=error_real;
      error_imag=fabs(b_calc_imag-b[2*i+1]);
      if (error_imag>max_solver_in_place_error) max_solver_in_place_error=error_imag;
      if (error_real>=tolerance_solver) {
      	printf("opt C:  A*x_cn=b test failure at i=%d b_calc_real=%e b[2*%d]=%e  error_real=%e\n",i,b_calc_real,i,b[2*i  ],error_real);
      	pass=0;
      }
      if (error_imag>=tolerance_solver) {
      	printf("opt C:  A*x_cn=b test failure at i=%d b_calc_imag=%e b[2*%d+1]=%e  error_imag=%e\n",i,b_calc_imag,i,b[2*i+1],error_imag);
    	pass=0;
      }
    }

    /* ------------------------------------------------------------------- */
    /* print error and timing results                                      */
    /* ------------------------------------------------------------------- */
    if (pass) {
      printf("Result Successful");
      printf("\torder=%2d\tnatC: %lld\toptC: %lld\n", Nrows, cholesky_t_cn, cholesky_t);

      if (test==2) {
        form_cholesky_cycles[0]=cholesky_t;
      }
      if (test==3) {
        form_cholesky_cycles[1]=cholesky_t;
      } 
    } else {
      printf("Result Failure\torder=%2d\n", Nrows);
    }
  }

#ifdef ENABLE_PROFILE
  fclose(fid);
#endif

  /* ------------------------------------------------------------------- */
  /* provide memory and cycles information                               */
  /* ------------------------------------------------------------------- */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
  printf("Memory:  %d bytes\n", &kernel_size);
#endif

  /* ------------------------------------------------------------------- */
  /* provide profiling information                                       */
  /* ------------------------------------------------------------------- */
  printf("Cycles:  %7d (order=%3d)  %7d (order=%3d)\n",(int)form_cholesky_cycles[0],CYCLE_FORMULA_ORDER_PT1,(int)form_cholesky_cycles[1],CYCLE_FORMULA_ORDER_PT2);
}
/* ======================================================================= */
/*  End of file:  DSPF_sp_cholesky_cmplx_d.c                               */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

