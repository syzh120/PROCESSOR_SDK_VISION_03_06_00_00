/* ======================================================================= */
/* DSPF_sp_lud_inv_cmplx_d.c - complex matrix inversion by LUD single precision */
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
#include "DSPF_sp_lud_inv_cmplx_cn.h"
#include "DSPF_sp_lud_inv_cmplx.h"
#include "../DSPF_sp_lud_cmplx/DSPF_sp_lud_cmplx.h"

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

#define MAX_MATRIX_NROWS   64 /* 164 is max */
#define MAX_MATRIX_SIZE (2*MAX_MATRIX_NROWS*MAX_MATRIX_NROWS)

/* ======================================================================= */
/* formula arrays                                                          */
/* ======================================================================= */
#define CYCLE_FORMULA_ORDER_PT1  32
#define CYCLE_FORMULA_ORDER_PT2  64
#define FORMULA_SIZE  2
long long form_cycles[FORMULA_SIZE];

/* ======================================================================= */
/* float word alignment of arrays                                         */
/* ======================================================================= */
#pragma DATA_SECTION(A,".far:matrix")
#pragma DATA_ALIGN(A,8)
float A[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(L,".far:matrix")
#pragma DATA_ALIGN(L,8)
float L[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(U,".far:matrix")
#pragma DATA_ALIGN(U,8)
float U[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(P,".far:matrix")
#pragma DATA_ALIGN(P,1)
unsigned short P[MAX_MATRIX_NROWS*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(LU,".far:matrix")
#pragma DATA_ALIGN(LU,8)
float LU[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(inv_A,".far:matrix")
#pragma DATA_ALIGN(inv_A,8)
float inv_A[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(b,".far:matrix")
#pragma DATA_ALIGN(b,8)
float b[2*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(b_mod,".far:matrix")
#pragma DATA_ALIGN(b_mod,8)
float b_mod[2*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(x,".far:matrix")
#pragma DATA_ALIGN(x,8)
float x[2*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(y,".far:matrix")
#pragma DATA_ALIGN(y,8)
float y[2*MAX_MATRIX_NROWS];

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */
void main(void) {
	
  unsigned short test,Nrows,Ncols,pass;
  float xreal,ximag,yreal,yimag;
  float sum_real,sum_imag,error_real,error_imag;
  float max_LUD_error_cn,max_inverse_error_cn;
  float max_inverse_error;
  int row,col,k,status,invertible,num_rows, num_cols;
  long long t_overhead, t_start, t_stop;
  long long inverse_cn_t,inverse_t;
  float tolerance_invertible=0.0001;
  float tolerance=0.0001;

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
  invertible=0;
  for (test=1;test<=5;test++) {
	printf("DSPF_sp_lud_inv_cmplx\tIter#: %d\t", test);
	
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
		      for (row=0;row<Nrows;row++) {                // random matrix
		        for (col=0;col<Ncols;col++) {
		    	  A[row*Ncols+col]=(float)(rand())/((float)RAND_MAX);
		        }
	        	b[2*row  ]=(float)(rand())/((float)RAND_MAX);
	        	b[2*row+1]=(float)(rand())/((float)RAND_MAX);
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
	}
	num_rows = Nrows;
	num_cols = Ncols;

    /* ------------------------------------------------------------------- */
    /* decompose A into P, L, and U where A=transpose(P)*L*U               */
    /* ------------------------------------------------------------------- */
    status = DSPF_sp_lud_cmplx(Nrows,A,L,U,P);
    if (status==-1) {
      printf("LU decomposition failed!\n");
    }

    /* ------------------------------------------------------------------- */
    /* check decomposition: transpose(P)*L*U=A                             */
    /* ------------------------------------------------------------------- */
    max_LUD_error_cn=0;
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
      	if (error_real>max_LUD_error_cn) {
      	  max_LUD_error_cn=error_real;
      	}
      	error_imag=fabs(A[2*col+1+row*Ncols]-sum_imag);
    	if (error_imag>max_LUD_error_cn) {
    	  max_LUD_error_cn=error_imag;
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

    /* ------------------------------------------------------------------------------ */
    /* first check if A is invertible by looking for zeros on U diagonal              */
    /* ------------------------------------------------------------------------------ */
    invertible=1;
    for (row=0;row<Nrows;row++) {
      if ((fabs(U[2*row+row*Ncols])<tolerance_invertible)||(fabs(U[2*row+1+row*Ncols])<tolerance_invertible)) {
    	invertible=0;
      }
    }
	
    if (invertible) {
      /* ------------------------------------------------------------------- */
      /* inverse A = inv(U) * inv(L) * P                                     */
      /*   note that L and U matrices are modified during processing         */
      /* ------------------------------------------------------------------- */
      TSCL= 0,TSCH=0;
      t_start = _itoll(TSCH, TSCL);
      status = DSPF_sp_lud_inverse_cmplx_cn(Nrows,P,L,U,inv_A);
      t_stop = _itoll(TSCH, TSCL);
      inverse_cn_t = t_stop-t_start-t_overhead;

      /* ------------------------------------------------------------------- */
      /* check that inv(A)*A = identity matrix                               */
      /* ------------------------------------------------------------------- */
      max_inverse_error_cn=0;
      for (row=0;row<Nrows;row++) {
        for (col=0;col<Nrows;col++) {
          sum_real=0;
          sum_imag=0;
    	  for (k=0;k<Nrows;k++) {
      		xreal=inv_A[2*k  +row*Ncols];
      		ximag=inv_A[2*k+1+row*Ncols];
      		yreal=A[2*col  +k*Ncols];
      		yimag=A[2*col+1+k*Ncols];
      		sum_real+=xreal*yreal-ximag*yimag;
      		sum_imag+=xreal*yimag+ximag*yreal;
    	  }
    	  if (row==col) {
    		error_real=fabs(sum_real-1.0);
    		error_imag=fabs(sum_imag);
    	  } else {
    		error_real=fabs(sum_real);
    		error_imag=fabs(sum_imag);
    	  }
      	  if (error_real>max_inverse_error_cn) {
      	    max_inverse_error_cn=error_real;
      	  }
          if (error_imag>max_inverse_error_cn) {
      	    max_inverse_error_cn=error_imag;
      	  }
          if (error_real>tolerance) {
            pass=0;
            printf("nat C inverse error_real=%e\n",error_real);
            break;
          }
          if (error_imag>tolerance) {
            pass=0;
            printf("nat C inverse error_imag=%e\n",error_imag);
            break;
          }
        }
      }
    }

    /* ------------------------------------------------------------------- */
    /* decompose A into P, L, and U where A=transpose(P)*L*U               */
    /* ------------------------------------------------------------------- */
    status = DSPF_sp_lud_cmplx(Nrows,A,L,U,P);
    if (status==-1) {
      printf("LU decomposition failed!\n");
    }

    /* ------------------------------------------------------------------------------ */
    /* first check if A is invertible by looking for zeros on U diagonal              */
    /* ------------------------------------------------------------------------------ */
    invertible=1;
    for (row=0;row<Nrows;row++) {
      if ((fabs(U[2*row+row*Ncols])<tolerance_invertible)||(fabs(U[2*row+1+row*Ncols])<tolerance_invertible)) {
    	invertible=0;
      }
    }
	
    if (invertible) {
       /* ------------------------------------------------------------------- */
       /* inverse A = inv(U) * inv(L) * P                                     */
       /*   note that L and U matrices are modified during processing         */
       /* ------------------------------------------------------------------- */
       TSCL= 0,TSCH=0;
       t_start = _itoll(TSCH, TSCL);
       status = DSPF_sp_lud_inverse_cmplx(Nrows,P,L,U,inv_A);
       t_stop = _itoll(TSCH, TSCL);
       inverse_t=t_stop-t_start-t_overhead;

       /* ------------------------------------------------------------------- */
       /* check that inv(A)*A = identity matrix                               */
       /* ------------------------------------------------------------------- */
       max_inverse_error=0;
       for (row=0;row<Nrows;row++) {
         for (col=0;col<Nrows;col++) {
           sum_real=0;
           sum_imag=0;
     	  for (k=0;k<Nrows;k++) {
       		xreal=inv_A[2*k  +row*Ncols];
       		ximag=inv_A[2*k+1+row*Ncols];
       		yreal=A[2*col  +k*Ncols];
       		yimag=A[2*col+1+k*Ncols];
     		sum_real+=xreal*yreal-ximag*yimag;
     		sum_imag+=xreal*yimag+ximag*yreal;
     	  }
     	  if (row==col) {
     		error_real=fabs(sum_real-1.0);
     		error_imag=fabs(sum_imag);
     	  } else {
     		error_real=fabs(sum_real);
     		error_imag=fabs(sum_imag);
     	  }
       	  if (error_real>max_inverse_error) {
       	    max_inverse_error=error_real;
       	  }
           if (error_imag>max_inverse_error) {
       	    max_inverse_error=error_imag;
       	  }
          if (error_real>tolerance) {
             pass=0;
             printf("opt C inverse error_real=%e\n",error_real);
             break;
           }
           if (error_imag>tolerance) {
             pass=0;
             printf("opt C inverse error_imag=%e\n",error_imag);
             break;
           }
         }
       }
    }

    /* ------------------------------------------------------------------- */
    /* print results                                                       */
    /* ------------------------------------------------------------------- */
    if (pass) {
      printf("Result Successful");
      printf("\torder=%2dx%2d\tnatC: %lld\toptC: %lld\n", num_rows, num_cols, inverse_cn_t, inverse_t);
    } else {
      printf("Result Failure\torder=%2dx%2d\n", num_rows, num_cols);
    }
	
    if (num_rows==CYCLE_FORMULA_ORDER_PT1) {
      form_cycles[0] = inverse_t;
    } else if (num_rows==CYCLE_FORMULA_ORDER_PT2) {
      form_cycles[1] = inverse_t;
    }
	
  }

  /* ------------------------------------------------------------------- */
  /* provide memory and cycles information                               */
  /* ------------------------------------------------------------------- */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
  printf("Memory:  %d bytes\n", &kernel_size);
#endif

  printf("Cycles:  %lld (order=%d)  %lld (order=%d)\n",form_cycles[0],CYCLE_FORMULA_ORDER_PT1,form_cycles[1],CYCLE_FORMULA_ORDER_PT2);

}
/* ======================================================================= */
/*  End of file:  DSPF_sp_lud_inv_cmplx_d.c                                */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

