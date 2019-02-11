/* ======================================================================= */
/* DSPF_dp_cholesky_d.c -- Cholesky decomposition and solver driver code   */
/*                         using double precision                          */
/*   1. Generate symmetric A matrix using random numbers                   */
/*   2. Tests A for positive definiteness                                  */
/*   3. Decomposes A into lower triangular matrix L using basic and in     */
/*      place methods                                                      */
/*   4. Solver solves A*x=b for x using forward and backward substitution  */
/*      a. A*x = L*L_transpose*x = b                                       */
/*      b. y = inverse(L)*b - done using forward substitution              */
/*      c. x = inverse(L_transpose)*y - done using backward substitution   */
/*   5. Recomputes b_calc=A*x                                              */
/*   6. Computes average percent error = 100*sum(abs(b-b_calc)/b)/order    */
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
#include <math.h>
#include <time.h>
#include <c6x.h>

/* ======================================================================= */
/* Interface header files for the natural C and optimized C code           */
/* ======================================================================= */
#include "DSPF_dp_cholesky_cn.h"
#include "DSPF_dp_cholesky.h"

/* ======================================================================= */
/* define size constants                                                   */
/* ======================================================================= */
#if defined(__TI_EABI__)
#define kernel_size _kernel_size
#endif

/* ======================================================================= */
/* extern parameters                                                       */
/* ======================================================================= */
extern char kernel_size;

/* ======================================================================= */
/* define constants                                                        */
/* ======================================================================= */
#define FORMULA_SIZE                 2
#define CYCLE_FORMULA_ORDER_PT1     64
#define CYCLE_FORMULA_ORDER_PT2    128

#define MAX_MATRIX_ORDER   128
#define MAX_A_MATRIX_SIZE (MAX_MATRIX_ORDER*MAX_MATRIX_ORDER)

/* ======================================================================= */
/* formula arrays                                                          */
/* ======================================================================= */
int form_cycle_basic[FORMULA_SIZE];
int form_cycle_in_place[FORMULA_SIZE];
int form_cycle_solver[FORMULA_SIZE];

/* ======================================================================= */
/* double word alignment of arrays                                         */
/* ======================================================================= */
#pragma DATA_ALIGN(M,8);
double M[MAX_A_MATRIX_SIZE];

#pragma DATA_ALIGN(A,8);
double A[MAX_A_MATRIX_SIZE];

#pragma DATA_ALIGN(x_cn,8);
double x_cn[MAX_MATRIX_ORDER];
#pragma DATA_ALIGN(x_opt,8);
double x_opt[MAX_MATRIX_ORDER];

#pragma DATA_ALIGN(x_in_place_cn,8);
double x_in_place_cn[MAX_MATRIX_ORDER];
#pragma DATA_ALIGN(x_in_place_opt,8);
double x_in_place_opt[MAX_MATRIX_ORDER];

#pragma DATA_ALIGN(y,8);
double y[MAX_MATRIX_ORDER];

#pragma DATA_ALIGN(b,8);
double b[MAX_MATRIX_ORDER];

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */
void main() {
	
  unsigned short order,pass;
  double sum;
  double b_calc,error,tolerance,percent_error;
  int i,j,k,status,enable_test;
  clock_t t_overhead, t_start, t_stop;
  clock_t cholesky_t_cn;
  //clock_t cholesky_in_place_t_cn, solver_t_cn;
  clock_t cholesky_t_opt;
  clock_t cholesky_in_place_t_opt, solver_t_opt;
  double *L_cn,*L_opt,*A_in_place_cn,*A_in_place_opt;
  int iter;

  /* --------------------------------------------------------------------- */
  /* Compute the overhead of calling clock twice to get timing info        */
  /* --------------------------------------------------------------------- */
  /* Initialize timer for clock */
  TSCL= 0,TSCH=0;
  t_start = _itoll(TSCH, TSCL);
  t_stop = _itoll(TSCH, TSCL);
  t_overhead = t_stop - t_start;

  /* --------------------------------------------------------------------- */
  /* process matrix order loop                                             */
  /* --------------------------------------------------------------------- */
  for (iter=1, order=4;order<=128;order*=2, iter++) {

    /* ------------------------------------------------------------------- */
	/* Print timing results                                                */
	/* ------------------------------------------------------------------- */
	printf("DSPF_dp_cholesky\tIter#: %d\t", iter);

    /* ------------------------------------------------------------------- */
	/* generate M matrix of random numbers in the interval [0,1]           */
	/* ------------------------------------------------------------------- */
	for (i=0;i<order;i++) {
	  for (j=0;j<order;j++) {
		M[i*order+j]=(double)(rand())/((double)RAND_MAX);
	  }
	}

    /* ------------------------------------------------------------------- */
	/* generate symmetric A matrix: A=M*M_transpose                        */
    /* ------------------------------------------------------------------- */
	for (i=0;i<order;i++) {
	  for (j=0;j<order;j++) {
		sum=0.0;
		for (k=0;k<order;k++) {
		  sum+=M[i*order+k]*M[j*order+k];
	    }
	    A[i*order+j]=sum;
	  }
	}

    /* ------------------------------------------------------------------- */
	/* generate b vector                                                   */
    /* ------------------------------------------------------------------- */
	for (i=0;i<order;i++) {
	  b[i]=(double)order;
	}

    /* ------------------------------------------------------------------- */
    /* decompose A and generate L_cn using natural C code                  */
    /* ------------------------------------------------------------------- */
	enable_test=1;
	L_cn=&M[0];
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_dp_cholesky_cn(enable_test,order,A,L_cn);
    t_stop = _itoll(TSCH, TSCL);
    if (status==-1) {
      printf("cholesky decomposition matrix A is not positive definite!\n");
    }
    cholesky_t_cn=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* solve for x using natural C code                                    */
    /* ------------------------------------------------------------------- */
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_dp_cholesky_solver_cn(order,L_cn,y,b,x_cn);
    t_stop = _itoll(TSCH, TSCL);
    //solver_t_cn=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* decompose A and generate L_opt using optimized C code               */
    /* ------------------------------------------------------------------- */
	enable_test=1;
    L_opt=&M[0];
	t_start = _itoll(TSCH, TSCL);
    status=DSPF_dp_cholesky(enable_test,order,A,L_opt);
    t_stop = _itoll(TSCH, TSCL);
    if (status==-1) {
      printf("cholesky decomposition matrix A is not positive definite!\n");
    }
    cholesky_t_opt=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* solve for x using optimized C code                                  */
    /* ------------------------------------------------------------------- */
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_dp_cholesky_solver(order,L_opt,y,b,x_opt);
    t_stop = _itoll(TSCH, TSCL);
    solver_t_opt=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* decompose A_in_place_cn in place using natural C code               */
    /* ------------------------------------------------------------------- */
	A_in_place_cn=&M[0];
	for (i=0;i<order;i++) {
	  for (j=0;j<order;j++) {
	    A_in_place_cn[i*order+j]=A[i*order+j];
	  }
	}
    enable_test=1;
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_dp_cholesky_in_place_cn(enable_test,order,A_in_place_cn);
    t_stop = _itoll(TSCH, TSCL);
    if (status==-1) {
      printf("cholesky decomposition matrix A is not positive definite!\n");
    }
    //cholesky_in_place_t_cn=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* solve for x using A_in_place using natural C code                   */
    /* ------------------------------------------------------------------- */
    status=DSPF_dp_cholesky_solver_cn(order,A_in_place_cn,y,b,x_in_place_cn);
    if (status==-1) {
      printf("solver fails!\n");
    }

    /* ------------------------------------------------------------------- */
    /* decompose A_in_place_opt in place using optimized C code            */
    /* ------------------------------------------------------------------- */
	A_in_place_opt=&M[0];
	for (i=0;i<order;i++) {
	  for (j=0;j<order;j++) {
	    A_in_place_opt[i*order+j]=A[i*order+j];
	  }
	}
    enable_test=1;
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_dp_cholesky_in_place(enable_test,order,A_in_place_opt);
    t_stop = _itoll(TSCH, TSCL);
    if (status==-1) {
      printf("cholesky decomposition matrix A is not positive definite!\n");
    }
    cholesky_in_place_t_opt=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* solve for x using A_in_place using optimized C code                 */
    /* ------------------------------------------------------------------- */
    status=DSPF_dp_cholesky_solver(order,A_in_place_opt,y,b,x_in_place_opt);
    if (status==-1) {
      printf("solver fails!\n");
    }

    /* ------------------------------------------------------------------- */
    /* check A*x_cn=b                                                      */
    /* ------------------------------------------------------------------- */
    pass=1;
    tolerance=1.0e-6;
    for (i=0;i<order;i++) {
      b_calc=0.0;
      for (j=0;j<order;j++) {
    	b_calc+=A[i*order+j]*x_cn[j];
      }
      error=fabs(b_calc-b[i]);
      percent_error=100.0*error/b[i];
      if (percent_error>=tolerance) {
    	printf("A*x_cn=b test failure at i=%d b_calc=%e b[%d]=%e  percent_error=%e\n",i,b_calc,i,b[i],percent_error);
    	pass=0;
    	break;
      }
    }

    /* ------------------------------------------------------------------- */
    /* check A*x_opt=b                                                     */
    /* ------------------------------------------------------------------- */
    for (i=0;i<order;i++) {
      b_calc=0.0;
      for (j=0;j<order;j++) {
    	b_calc+=A[i*order+j]*x_opt[j];
      }
      error=fabs(b_calc-b[i]);
      percent_error=100.0*error/b[i];
      if (percent_error>=tolerance) {
    	printf("A*x_opt=b test failure at i=%d b_calc=%e b[%d]=%e  percent_error=%e\n",i,b_calc,i,b[i],percent_error);
    	pass=0;
    	break;
      }
    }

    /* ------------------------------------------------------------------- */
    /* check A*x_in_place_cn=b                                             */
    /* ------------------------------------------------------------------- */
    for (i=0;i<order;i++) {
      b_calc=0.0;
      for (j=0;j<order;j++) {
    	b_calc+=A[i*order+j]*x_in_place_cn[j];
      }
      error=fabs(b_calc-b[i]);
      percent_error=100.0*error/b[i];
      if (percent_error>=tolerance) {
    	printf("A*x_in_place_cn=b test failure at i=%d b_calc=%e b[%d]=%e  percent_error=%e\n",i,b_calc,i,b[i],percent_error);
    	pass=0;
    	break;
      }
    }

    /* ------------------------------------------------------------------- */
    /* check A*x_in_place_opt=b                                            */
    /* ------------------------------------------------------------------- */
    for (i=0;i<order;i++) {
      b_calc=0.0;
      for (j=0;j<order;j++) {
    	b_calc+=A[i*order+j]*x_in_place_opt[j];
      }
      error=fabs(b_calc-b[i]);
      percent_error=100.0*error/b[i];
      if (percent_error>=tolerance) {
    	printf("A*x_in_place_opt=b test failure at i=%d b_calc=%e b[%d]=%e  percent_error=%e\n",i,b_calc,i,b[i],percent_error);
    	pass=0;
    	break;
      }
    }

    /* ------------------------------------------------------------------- */
    /* print timing results                                                */
    /* ------------------------------------------------------------------- */
    if (pass) {
      printf("Result Successful");
      printf("\torder=%2d\tnatC: %u\toptC: %u\n", order, cholesky_t_cn, cholesky_t_opt);

      /* save optimized timing results                                     */

      if (order==CYCLE_FORMULA_ORDER_PT1) {
        form_cycle_basic[0]   =cholesky_t_opt;
        form_cycle_in_place[0]=cholesky_in_place_t_opt;
        form_cycle_solver[0]  =solver_t_opt;
      } else {
        if (order==CYCLE_FORMULA_ORDER_PT2) {
          form_cycle_basic[1]   =cholesky_t_opt;
          form_cycle_in_place[1]=cholesky_in_place_t_opt;
          form_cycle_solver[1]  =solver_t_opt;
        }
      }
    }
    else {
      printf("Result Failure");
      printf("\torder=%d\n",order);
    }
  }

  /* ------------------------------------------------------------------- */
  /* provide memory information                                          */
  /* ------------------------------------------------------------------- */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
  printf("Memory:  %d bytes\n", &kernel_size);
#endif

  /* ------------------------------------------------------------------- */
  /* provide profiling information                                       */
  /* ------------------------------------------------------------------- */

  printf("Cycles:  %7d (order=%3d)  %7d (order=%3d)\n",form_cycle_basic[0],CYCLE_FORMULA_ORDER_PT1,form_cycle_basic[1],CYCLE_FORMULA_ORDER_PT2);
  //printf("Cycles (basic)    :  %7d (order=%3d)  %7d (order=%3d)\n",form_cycle_basic[0],CYCLE_FORMULA_ORDER_PT1,form_cycle_basic[1],CYCLE_FORMULA_ORDER_PT2);
  //printf("Cycles (in place) :  %7d (order=%3d)  %7d (order=%3d)\n",form_cycle_in_place[0],CYCLE_FORMULA_ORDER_PT1,form_cycle_in_place[1],CYCLE_FORMULA_ORDER_PT2);
  //printf("Cycles (solver)   :  %7d (order=%3d)  %7d (order=%3d)\n",form_cycle_solver[0],CYCLE_FORMULA_ORDER_PT1,form_cycle_solver[1],CYCLE_FORMULA_ORDER_PT2);

}
/* ======================================================================= */
/*  End of file:  DSPF_dp_cholesky_d.c                                     */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

