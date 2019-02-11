/* ======================================================================= */
/* DSPF_dp_lud_sol_cmplx_d.c -- complex linear solver by LUD double precision */
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
#include "DSPF_dp_lud_sol_cmplx_cn.h"
#include "DSPF_dp_lud_sol_cmplx.h"
#include "../DSPF_dp_lud_cmplx/DSPF_dp_lud_cmplx.h"

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
/* define size constants                                                   */
/* ======================================================================= */

#define MAX_MATRIX_NROWS   64 /* 117 is max size */
#define MAX_MATRIX_SIZE (2*MAX_MATRIX_NROWS*MAX_MATRIX_NROWS)

/* ======================================================================= */
/* formula arrays                                                          */
/* ======================================================================= */
#define CYCLE_FORMULA_ORDER_PT1  32
#define CYCLE_FORMULA_ORDER_PT2  64
#define FORMULA_SIZE  2
long long form_cycles[FORMULA_SIZE];

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
unsigned short P[MAX_MATRIX_NROWS*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(LU,".far:matrix")
#pragma DATA_ALIGN(LU,8)
double LU[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(inv_A,".far:matrix")
#pragma DATA_ALIGN(inv_A,8)
double inv_A[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(b,".far:matrix")
#pragma DATA_ALIGN(b,8)
double b[2*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(b_mod,".far:matrix")
#pragma DATA_ALIGN(b_mod,8)
double b_mod[2*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(x,".far:matrix")
#pragma DATA_ALIGN(x,8)
double x[2*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(y,".far:matrix")
#pragma DATA_ALIGN(y,8)
double y[2*MAX_MATRIX_NROWS];

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */
void main(void) {
	
  unsigned short test,Nrows,Ncols,pass;
  double xreal,ximag,yreal,yimag;
  double sum_real,sum_imag,error_real,error_imag;
  double max_LUD_error,max_solver_error_cn,max_solver_error;
  int row,col,k,status,invertible,num_rows,num_cols;
  long long t_overhead, t_start, t_stop;
  long long solver_cn_t;
  long long solver_t;
  double tolerance_invertible=0.000001;
  double tolerance=0.000001;

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
  /* process test cases                                                    */
  /* --------------------------------------------------------------------- */
  pass=1;
  for (test=1;test<=5;test++) {
	printf("DSPF_dp_lud_sol_cmplx\tIter#: %d\t", test);
	
	switch(test) {
	case 1: { Nrows=3;
              Ncols=2*Nrows;
              A[ 0]= 1;A[ 1]= 2;A[ 2]= 3;A[ 3]= 4;A[ 4]= 5;A[ 5]= 6;
              A[ 6]= 7;A[ 7]= 8;A[ 8]= 9;A[ 9]=10;A[10]=11;A[11]=12;
              A[12]=13;A[13]=14;A[14]=15;A[15]=16;A[16]= 0;A[17]= 0;
		      b[0]=1;b[1]=2;b[2]=3;b[3]=4;b[4]=5;b[5]=6;
	          break;
	        }
	case 2: { Nrows=3;
              Ncols=2*Nrows;
		      A[ 0]=A[ 1]=0; A[ 2]=A[ 3]=1; A[ 4]=A[ 5]=2;  // non symmetric singular and invertible matrix
		      A[ 6]=A[ 7]=3; A[ 8]=A[ 9]=4; A[10]=A[11]=5;
		      A[12]=A[13]=6; A[14]=A[15]=7; A[16]=A[17]=8;
	          break;
	        }
	case 3: { Nrows=16;
              Ncols=2*Nrows;
              srand(1);
		      for (row=0;row<Nrows;row++) {                                   // random matrix
		        for (col=0;col<Ncols;col++) {
		    	  A[row*Ncols+col]=(double)(rand())/((double)RAND_MAX);
		        }
		        b[2*row  ]=(double)(rand())/((double)RAND_MAX);
		        b[2*row+1]=(double)(rand())/((double)RAND_MAX);
		      }
	          break;
	        }
    case 4: { Nrows=CYCLE_FORMULA_ORDER_PT1;
	          Ncols=Nrows;
	          srand(1);
	          for (row=0;row<Nrows;row++) {
			    for (col=0;col<2*Ncols;col++) {
			      A[row*2*Ncols+col]=(double)(rand())/((double)RAND_MAX);
			    }
			    b[2*row  ]=(double)(rand())/((double)RAND_MAX);
			    b[2*row+1]=(double)(rand())/((double)RAND_MAX);
			  }
		      break;
	        }
    case 5: { Nrows=CYCLE_FORMULA_ORDER_PT2;
	          Ncols=Nrows;
	          srand(1);
	          for (row=0;row<Nrows;row++) {
			    for (col=0;col<2*Ncols;col++) {
			      A[row*2*Ncols+col]=(double)(rand())/((double)RAND_MAX);
			    }
			    b[2*row  ]=(double)(rand())/((double)RAND_MAX);
			    b[2*row+1]=(double)(rand())/((double)RAND_MAX);
			  }
		      break;
	        }
	} /* switch(test) */

	num_rows = Nrows;
	num_cols = Ncols;
	
    /* ------------------------------------------------------------------- */
    /* decompose A into P, L, and U where A=transpose(P)*L*U               */
    /* ------------------------------------------------------------------- */
    status = DSPF_dp_lud_cmplx(Nrows,A,L,U,P);
    if (status==-1) {
      printf("LU decomposition failed!\n");
    }

    /* ------------------------------------------------------------------- */
    /* check decomposition: transpose(P)*L*U=A                             */
    /* ------------------------------------------------------------------- */
    max_LUD_error=0;
    Ncols=2*Nrows;
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
        sum_real=0;
        sum_imag=0;
    	for (k=0;k<Nrows;k++) {
      	  xreal=L[2*k  +row*Ncols];
      	  ximag=L[2*k+1+row*Ncols];
      	  yreal=U[2*col  +k*Ncols];
      	  yimag=U[2*col+1+k*Ncols];
            sum_real+=xreal*yreal-ximag*yimag;
            sum_imag+=xreal*yimag+ximag*yreal;
      	}
        LU[2*col  +row*Ncols]=sum_real;
        LU[2*col+1+row*Ncols]=sum_imag;
      }
    }
	
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
        sum_real=0;
        sum_imag=0;
      	for (k=0;k<Nrows;k++) {
            sum_real+=P[row+k*Nrows]*LU[2*col  +k*Ncols];
            sum_imag+=P[row+k*Nrows]*LU[2*col+1+k*Ncols];
      	}
      	error_real=fabs(A[2*col  +row*Ncols]-sum_real);
      	if (error_real>max_LUD_error) {
      	  max_LUD_error=error_real;
      	}
      	error_imag=fabs(A[2*col+1+row*Ncols]-sum_imag);
    	if (error_imag>max_LUD_error) {
    	  max_LUD_error=error_imag;
    	}
        if (error_real>tolerance) {
          pass=0;
          printf("nat C decomposition error_real=%e\n",error_real);
          break;
        }
        if (error_imag>tolerance) {
          pass=0;
          printf("nat C decomposition error_imag=%e\n",error_imag);
          break;
        }
      }
    }

    /* --------------------------------------------------------------------- */
    /* first check if A is invertible by looking for zeros on U diagonal     */
    /* --------------------------------------------------------------------- */
    invertible=1;
    for (row=0;row<Nrows;row++) {
      if ((fabs(U[2*row+row*Ncols])<tolerance_invertible)||(fabs(U[2*row+1+row*Ncols])<tolerance_invertible)) {
    	invertible=0;
      }
    }
	
    /* --------------------------------------------------------------------- */
    /* then solve linear equation A*x = b if A is invertible                 */
    /* --------------------------------------------------------------------- */
    if (invertible) {
      TSCL= 0,TSCH=0;
  	  t_start = _itoll(TSCH, TSCL);
      status = DSPF_dp_lud_solver_cmplx_cn(Nrows,P,L,U,b,b_mod,y,x);
      t_stop = _itoll(TSCH, TSCL);
      solver_cn_t=t_stop-t_start-t_overhead;
      if (status==-1) {
        printf("solver failed!\n");
      }

      /* ------------------------------------------------------------------- */
      /* verify A*x=b                                                        */
      /* ------------------------------------------------------------------- */
      max_solver_error_cn=0;
      for (row=0;row<Nrows;row++) {
        sum_real=0;
        sum_imag=0;
        for (col=0;col<Nrows;col++) {
          xreal=A[2*col  +row*Ncols];
          ximag=A[2*col+1+row*Ncols];
          yreal=x[2*col  ];
          yimag=x[2*col+1];
          sum_real+=xreal*yreal-ximag*yimag;
          sum_imag+=xreal*yimag+ximag*yreal;
        }
        error_real=fabs(b[2*row  ]-sum_real);
        if (error_real>max_solver_error_cn) max_solver_error_cn=error_real;
        error_imag=fabs(b[2*row+1]-sum_imag);
        if (error_imag>max_solver_error_cn) max_solver_error_cn=error_imag;
        if (error_real>tolerance) {
          pass=0;
          printf("nat C solver error_real=%e\n",error_real);
          break;
        }
        if (error_imag>tolerance) {
          pass=0;
          printf("nat C solver error_imag=%e\n",error_imag);
          break;
        }
      }
    } /* if (invertible) */

    /* ------------------------------------------------------------------- */
    /* decompose A into P, L, and U where A=transpose(P)*L*U               */
    /* ------------------------------------------------------------------- */
    status = DSPF_dp_lud_cmplx(Nrows,A,L,U,P);
    if (status==-1) {
      printf("LU decomposition failed!\n");
    }

    /* -------------------------------------------------------------------- */
    /* first check if A is invertible by looking for zeros on U diagonal    */
    /* -------------------------------------------------------------------- */
    invertible=1;
    for (row=0;row<Nrows;row++) {
      if ((fabs(U[2*row+row*Ncols])<tolerance_invertible)||(fabs(U[2*row+1+row*Ncols])<tolerance_invertible)) {
    	invertible=0;
      }
    }

    /* --------------------------------------------------------------------- */
    /* then solve linear equation A*x = b if A is invertible                 */
    /* --------------------------------------------------------------------- */
    if (invertible) {
      TSCL= 0,TSCH=0;
      t_start = _itoll(TSCH, TSCL);
      status = DSPF_dp_lud_solver_cmplx(Nrows,P,L,U,b,b_mod,y,x);
      t_stop = _itoll(TSCH, TSCL);
      if (status==-1) {
        printf("solver failed!\n");
      }
      solver_t = t_stop-t_start-t_overhead;

      /* ------------------------------------------------------------------- */
      /* verify A*x=b                                                        */
      /* ------------------------------------------------------------------- */
      max_solver_error=0;
      for (row=0;row<Nrows;row++) {
        sum_real=0;
        sum_imag=0;
        for (col=0;col<Nrows;col++) {
            xreal=A[2*col  +row*Ncols];
            ximag=A[2*col+1+row*Ncols];
            yreal=x[2*col  ];
            yimag=x[2*col+1];
            sum_real+=xreal*yreal-ximag*yimag;
            sum_imag+=xreal*yimag+ximag*yreal;
        }
        error_real=fabs(b[2*row  ]-sum_real);
        if (error_real>max_solver_error) max_solver_error=error_real;
        error_imag=fabs(b[2*row+1]-sum_imag);
        if (error_imag>max_solver_error) max_solver_error=error_imag;
        if (error_real>tolerance) {
          pass=0;
          printf("opt C solver error_real=%e\n",error_real);
          break;
        }
        if (error_imag>tolerance) {
          pass=0;
          printf("opt C solver error_imag=%e\n",error_imag);
          break;
        }
      }
    } /* if (invertible ) */

   /* ------------------------------------------------------------------- */
   /* print results                                                       */
   /* ------------------------------------------------------------------- */
    if (pass) {
      printf("Result Successful");
      printf("\torder=%2dx%2d\tnatC: %lld\toptC: %lld\n", num_rows, num_cols, solver_cn_t, solver_t);
    } else {
      printf("Result Failure\torder=%2dx%2d\n", num_rows, num_cols);
    }
	
    if (num_rows==CYCLE_FORMULA_ORDER_PT1) {
      form_cycles[0] = solver_t;
    } else if (num_rows==CYCLE_FORMULA_ORDER_PT2) {
      form_cycles[1] = solver_t;
    }
	
  } /* for (test=1;test<=5;test++) */

#ifdef ENABLE_PROFILE
  fclose(fid);
#endif

  /* ------------------------------------------------------------------- */
  /* provide memory and cycles information                               */
  /* ------------------------------------------------------------------- */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
  printf("Memory:  %d bytes\n", &kernel_size);
#endif

  printf("Cycles:  %lld (order=%d)  %lld (order=%d)\n",form_cycles[0],CYCLE_FORMULA_ORDER_PT1,form_cycles[1],CYCLE_FORMULA_ORDER_PT2);

} /* main */

/* ======================================================================= */
/*  End of file:  DSPF_dp_lud_sol_cmplx_d.c                                */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
