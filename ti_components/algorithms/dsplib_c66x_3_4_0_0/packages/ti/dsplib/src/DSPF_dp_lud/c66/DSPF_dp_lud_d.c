/* ======================================================================= */
/* DSPF_dp_lud_d.c -- lower upper decomposition using double precision     */
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
#include <c6x.h>

/* ======================================================================= */
/* Interface header files for the natural C and optimized C code           */
/* ======================================================================= */
#include "DSPF_dp_lud_cn.h"
#include "DSPF_dp_lud.h"

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
#define MAX_MATRIX_ORDER   128 /* 164 is max for L2SRAM */
#define MAX_MATRIX_SIZE (MAX_MATRIX_ORDER*MAX_MATRIX_ORDER)

/* ======================================================================= */
/* formula arrays                                                          */
/* ======================================================================= */
#define CYCLE_FORMULA_ORDER_PT1   64
#define CYCLE_FORMULA_ORDER_PT2  128
#define FORMULA_SIZE  2
long long form_cycle[FORMULA_SIZE];

/* ======================================================================= */
/* double word alignment of arrays                                         */
/* ======================================================================= */
#pragma DATA_SECTION(A,".far:matrix")
#pragma DATA_ALIGN(A,8)
double A[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(L,".far:matrix")
#pragma DATA_ALIGN(L,8)
double L[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(U,".far:matrix")
#pragma DATA_ALIGN(U,8)
double U[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(P,".far:matrix")
#pragma DATA_ALIGN(P,1)
unsigned short P[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(LU,".far:matrix")
#pragma DATA_ALIGN(LU,8)
double LU[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(inv_A,".far:matrix")
#pragma DATA_ALIGN(inv_A,8)
double inv_A[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(b,".far:matrix")
#pragma DATA_ALIGN(b,8)
double b[MAX_MATRIX_ORDER];

#pragma DATA_SECTION(b_mod,".far:matrix")
#pragma DATA_ALIGN(b_mod,8)
double b_mod[MAX_MATRIX_ORDER];

#pragma DATA_SECTION(x,".far:matrix")
#pragma DATA_ALIGN(x,8)
double x[MAX_MATRIX_ORDER];

#pragma DATA_SECTION(y,".far:matrix")
#pragma DATA_ALIGN(y,8)
double y[MAX_MATRIX_ORDER];

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */
void main(void) {
	
  unsigned short test,order,pass;
  double sum,error;
  int row,col,k,status;
  long long t_overhead, t_start, t_stop;
  long long lud_t_opt,lud_t_cn;
  double tolerance=0.000001;

  /* --------------------------------------------------------------------- */
  /* Compute the overhead of calling clock twice to get timing info        */
  /* --------------------------------------------------------------------- */
  TSCL=0, TSCH=0;
  t_start = _itoll(TSCH,TSCL);
  t_stop  = _itoll(TSCH,TSCL);
  t_overhead = t_stop - t_start;

  /* --------------------------------------------------------------------- */
  /* process test cases                                                    */
  /* --------------------------------------------------------------------- */
  pass=1;
  for (test=1;test<=4;test++) {

	printf("DSPF_dp_lud\tIter#: %d\t", test);
  
	switch(test) {
	case 1: { order=3;
		      A[0]=1;A[1]=2;A[2]=3;A[3]=4;A[4]=5;A[5]=6;A[6]=7;A[7]=8;A[8]=0; // non symmetric matrix
		      b[0]=1;b[1]=2;b[2]=3;
	          break;
	        }
	case 2: { order=3;
		      A[0]=0;A[1]=1;A[2]=2;A[3]=3;A[4]=4;A[5]=5;A[6]=6;A[7]=7;A[8]=8; // non symmetric singular matrix
	          break;
	        }
	case 3: { order=CYCLE_FORMULA_ORDER_PT1;
              srand(1);
	          for (row=0;row<order;row++) b[row]=(double)row+1.0;
		      for (row=0;row<order;row++) {                                   // random matrix
		        for (col=0;col<order;col++) {
		    	  A[row*order+col]=(double)(rand())/((double)RAND_MAX);
		        }
		      }
	          break;
	        }
	case 4: { order=CYCLE_FORMULA_ORDER_PT2;
              srand(1);
	          for (row=0;row<order;row++) b[row]=(double)row+1.0;
		      for (row=0;row<order;row++) {                                   // random matrix
		        for (col=0;col<order;col++) {
		    	  A[row*order+col]=(double)(rand())/((double)RAND_MAX);
		        }
		      }
	          break;
	        }
	}

    /* ------------------------------------------------------------------- */
    /* decompose A into P, L, and U where A=transpose(P)*L*U               */
    /* ------------------------------------------------------------------- */
    TSCL=0, TSCH=0;
    t_start  = _itoll(TSCH,TSCL);
    status   = DSPF_dp_lud_cn(order,A,L,U,P);
    t_stop   = _itoll(TSCH,TSCL);
    lud_t_cn = t_stop-t_start-t_overhead;
    if (status==-1) {
      printf("LU decomposition failed!\n");
    }
	
    /* ------------------------------------------------------------------- */
    /* check decomposition: transpose(P)*L*U=A                             */
    /* ------------------------------------------------------------------- */
    for (row=0;row<order;row++) {
      for (col=0;col<order;col++) {
        sum=0;
    	for (k=0;k<order;k++) {
          sum+=L[k+row*order]*U[col+k*order];
    	}
        LU[col+row*order]=sum;
      }
    }
    for (row=0;row<order;row++) {
      for (col=0;col<order;col++) {
        sum=0;
    	for (k=0;k<order;k++) {
          sum+=P[row+k*order]*LU[col+k*order];
    	}
    	error=fabs(A[col+row*order]-sum);
       if (error>tolerance) {
          pass=0;
          printf("error=%e\n",error);
        }
      }
    }

    /* ------------------------------------------------------------------- */
    /* decompose A and generate L and U using optimized C code             */
    /* ------------------------------------------------------------------- */
    TSCL=0, TSCH=0;
    t_start = _itoll(TSCH,TSCL);
    status=DSPF_dp_lud(order,A,L,U,P);
    t_stop = _itoll(TSCH,TSCL);
    if (status==-1) {
      printf("LU decomposition failed!\n");
    }
    lud_t_opt=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* check decomposition: transpose(P)*L*U=A                             */
    /* ------------------------------------------------------------------- */
    for (row=0;row<order;row++) {
      for (col=0;col<order;col++) {
        sum=0;
    	for (k=0;k<order;k++) {
          sum+=L[k+row*order]*U[col+k*order];
    	}
        LU[col+row*order]=sum;
      }
    }
    for (row=0;row<order;row++) {
      for (col=0;col<order;col++) {
        sum=0;
    	for (k=0;k<order;k++) {
          sum+=P[row+k*order]*LU[col+k*order];
    	}
    	error=fabs(A[col+row*order]-sum);
        if (error>tolerance) {
          pass=0;
          printf("error=%e\n",error);
        }
      }
    }

    if (pass) {
      printf("LUD Result Successful");
      printf("\torder=%3d\tnatC: %lld\toptC: %lld\n",order, lud_t_cn, lud_t_opt);
    } else {
      printf("Result Failure\torder=%3d\n",order);
    }
	
    if (order==CYCLE_FORMULA_ORDER_PT1) {
      form_cycle[0] = lud_t_opt;
    } else if (order==CYCLE_FORMULA_ORDER_PT2) {
      form_cycle[1] = lud_t_opt;
    }
	
  } /* for (test=1;test<=4;test++) */

  /* ------------------------------------------------------------------- */
  /* provide memory and cycles information                               */
  /* ------------------------------------------------------------------- */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
  printf("Memory:  %d bytes\n", &kernel_size);
#endif

  printf("Cycles:  %lld (order=%d)  %lld (order=%d)\n",form_cycle[0],CYCLE_FORMULA_ORDER_PT1,form_cycle[1],CYCLE_FORMULA_ORDER_PT2);

}
/* ======================================================================= */
/*  End of file:  DSPF_dp_lud_d.c                                     */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
