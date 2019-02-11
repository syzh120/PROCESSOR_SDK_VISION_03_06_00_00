/* ======================================================================= */
/* DSPF_dp_qrd_d.c -- QR decomposition using double precision              */
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
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCQRDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCQRDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCQRDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
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
#include "DSPF_dp_qrd_cn.h"
#include "DSPF_dp_qrd.h"

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

#define MAX_MATRIX_NROWS   128 /* 194 is max for L2SRAM */
#define MAX_MATRIX_NCOLS   128 /* 194 is max for L2SRAM */
#define MAX_MATRIX_SIZE (MAX_MATRIX_NROWS*MAX_MATRIX_NCOLS)

/* ======================================================================= */
/* formula arrays                                                          */
/* ======================================================================= */
#define CYCLE_FORMULA_ORDER_PT1  64
#define CYCLE_FORMULA_ORDER_PT2  128
#define FORMULA_SIZE  2
long long form_cycles[FORMULA_SIZE];

/* ======================================================================= */
/* double word alignment of arrays                                         */
/* ======================================================================= */
#pragma DATA_SECTION(A,".far:matrix")
#pragma DATA_ALIGN(A,8)
double A[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(Q,".far:matrix")
#pragma DATA_ALIGN(Q,8)
double Q[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(R,".far:matrix")
#pragma DATA_ALIGN(R,8)
double R[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(u,".far:matrix")
#pragma DATA_ALIGN(u,8)
double u[MAX_MATRIX_NROWS];

#pragma DATA_SECTION(inv_A,".far:matrix")
#pragma DATA_ALIGN(inv_A,8)
double inv_A[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(b,".far:matrix")
#pragma DATA_ALIGN(b,8)
double b[MAX_MATRIX_NROWS];

#pragma DATA_SECTION(x,".far:matrix")
#pragma DATA_ALIGN(x,8)
double x[MAX_MATRIX_NROWS];

#pragma DATA_SECTION(y,".far:matrix")
#pragma DATA_ALIGN(y,8)
double y[MAX_MATRIX_NROWS];

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */

void main(void) {
	
  unsigned short test,pass,Nrows,Ncols;
  double sum,tolerance,error;
  int row,col,k,status,invertible;
  long long t_overhead, t_start, t_stop;
  long long QRD_t_cn,QRD_t;

  /* --------------------------------------------------------------------- */
  /* Compute the overhead of calling clock twice to get timing info        */
  /* --------------------------------------------------------------------- */
  TSCL=0,TSCH=0;
  t_start = _itoll(TSCH,TSCL);
  t_stop = _itoll(TSCH,TSCL);
  t_overhead = t_stop - t_start;

  /* --------------------------------------------------------------------- */
  /* process test cases                                                    */
  /* --------------------------------------------------------------------- */
  tolerance=0.000001;
  pass=1;
  for (test=1;test<=9;test++) {
	printf("DSPF_dp_qrd\tIter#: %d\t", test);
	
	switch(test) {
	case 1: { Nrows=4;Ncols=2; // 4x2
		      A[0]=1;A[1]=2;A[2]=3;A[3]=4;A[4]=5;A[5]=6;A[6]=7;A[7]=8;
		      b[0]=1;b[1]=2;b[2]=3;b[3]=4;
	          break;
	        }
	case 2: { Nrows=4;Ncols=3; // 4x3
		      A[0]=1;A[1]=5;A[2]=9;A[3]=2;A[4]=6;A[5]=10;A[6]=3;A[7]=7;A[8]=1;A[9]=4;A[10]=8;A[11]=2;
		      b[0]=1;b[1]=2;b[2]=3;b[3]=4;
	          break;
	        }
	case 3: { Nrows=3;Ncols=3; // 3x3
		      A[0]=12;A[1]=-51;A[2]=4;A[3]=6;A[4]=167;A[5]=-68;A[6]=-4;A[7]=24;A[8]=-41;
		      b[0]=1;b[1]=2;b[2]=3;
	          break;
	        }
	case 4: { Nrows=3;Ncols=3; // 3x3 singular non invertible
		      A[0]=1;A[1]=2;A[2]=3;A[3]=4;A[4]=5;A[5]=6;A[6]=7;A[7]=8;A[8]=9;
		      b[0]=1;b[1]=2;b[2]=3;
	          break;
	        }
	case 5: { Nrows=3;Ncols=4; // 3x4
		      A[0]=1;A[1]=2;A[2]=3;A[3]=4;A[4]=5;A[5]=6;A[6]=7;A[7]=8;A[8]=9;A[9]=10;A[10]=1;A[11]=2;
		      b[0]=1;b[1]=2;b[2]=3;
	          break;
	        }
	case 6: { Nrows=2;Ncols=4; // 2x4
		      A[0]=1;A[1]=2;A[2]=3;A[3]=4;A[4]=5;A[5]=6;A[6]=7;A[7]=8;
		      b[0]=1;b[1]=2;
	          break;
	        }
	case 7: {Nrows=3;Ncols=3; // 3x3
             A[0]=1;A[1]=0;A[2]=0;A[3]=0;A[4]=1;A[5]=0;A[6]=0;A[7]=0;A[8]=1;
             b[0]=1;b[1]=2;
             break;
            }
	case 8: {
	          Nrows=CYCLE_FORMULA_ORDER_PT1;
		      Ncols=Nrows;
		      srand(1);
		      for (row=0;row<Nrows;row++) {                    // random matrix
		        for (col=0;col<Ncols;col++) {
		    	  A[row*Ncols+col]=(double)(rand())/((double)RAND_MAX);
		        }
		        b[row]=(double)row+1.0;
		      }
	          break;
	        }
	case 9: {
	          Nrows=CYCLE_FORMULA_ORDER_PT2;
		      Ncols=Nrows;
		      srand(1);
		      for (row=0;row<Nrows;row++) {                    // random matrix
		        for (col=0;col<Ncols;col++) {
		    	  A[row*Ncols+col]=(double)(rand())/((double)RAND_MAX);
		        }
		        b[row]=(double)row+1.0;
		      }
	          break;
	        }
	}

    /* ------------------------------------------------------------------- */
    /* decompose A into Q and R where A=Q_cn*R_cn                          */
    /* ------------------------------------------------------------------- */
    TSCL= 0,TSCH=0;
	t_start = _itoll(TSCH, TSCL);
    status=DSPF_dp_qrd_cn(Nrows,Ncols,A,Q,R,u);
    t_stop = _itoll(TSCH, TSCL);
    QRD_t_cn=t_stop-t_start-t_overhead;
    if (status==-1) {
      printf("LU decomposition failed!\n");
    }

    /* ------------------------------------------------------------------- */
    /* check decomposition: Q*R=A                                          */
    /* ------------------------------------------------------------------- */
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
        sum=0;
    	for (k=0;k<Nrows;k++) {
          sum+=Q[k+row*Nrows]*R[col+k*Ncols];
    	}
    	error=fabs(A[col+row*Ncols]-sum);
        if (error>tolerance) {
          pass=0;
          printf("nat decomposition error=%e\n",error);
        }
      }
    }

    /* ------------------------------------------------------------------- */
    /* check transformation: Q*Q'=I                                        */
    /* ------------------------------------------------------------------- */
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
        sum=0;
   	    for (k=0;k<Nrows;k++) {
   		  sum+=Q[k+row*Nrows]*Q[k+col*Nrows];
   	    }
  	    if (row==col) {
  		  error=fabs(sum-1.0);
  	    } else {
  		  error=fabs(sum);
  	    }
  	    if (error>tolerance) {
  		  pass=0;
  	    }
      }
    }

    /* ------------------------------------------------------------------------------ */
    /* check if A is invertible by looking for zeros on R_cn diagonal                 */
    /* ------------------------------------------------------------------------------ */
    if (Nrows==Ncols) {
      invertible=1;
      for (row=0;row<Nrows;row++) {
        if (fabs(R[row+row*Ncols])<tolerance) {
    	  invertible=0;
        }
      }
    } else {
      invertible=0;
    }

    /* ------------------------------------------------------------------------------ */
    /* solve Ax=b                                                                     */
    /* ------------------------------------------------------------------------------ */
    if (invertible) {
      status = DSPF_dp_qrd_solver_cn(Nrows,Ncols,Q,R,b,y,x);
      if (status==-1) {
        printf("solver failed!\n");
      }

      /* ------------------------------------------------------------------- */
      /* verify A*x=b                                                        */
      /* ------------------------------------------------------------------- */
      for (row=0;row<Nrows;row++) {
        sum=0.0;
        for (col=0;col<Ncols;col++) {
    	  sum+=A[col+row*Ncols]*x[col];
        }
        error=fabs(b[row]-sum);
        if (error>tolerance) {
          pass=0;
        }
      }

      /* ------------------------------------------------------------------- */
      /* inverse A = inv(R) * Q'                                             */
      /*   note that R matrice is modified during processing                 */
      /* ------------------------------------------------------------------- */
      status = DSPF_dp_qrd_inverse_cn(Nrows,Ncols,Q,R,inv_A);

      /* ------------------------------------------------------------------- */
      /* check that inv(A)*A = identity matrix                               */
      /* ------------------------------------------------------------------- */
      for (row=0;row<Nrows;row++) {
        for (col=0;col<Ncols;col++) {
          sum=0;
    	  for (k=0;k<Ncols;k++) {
            sum+=inv_A[k+row*Ncols]*A[col+k*Ncols];
    	  }
    	  if (row==col) error=fabs(sum-1.0);
    	  else          error=fabs(sum);
          if (error>tolerance) {
            pass=0;
            printf("nat inverse error=%e\n",error);
          }
        }
      }
    } /* if (invertible) */

    /* ------------------------------------------------------------------- */
    /* decompose A into Q and R where A=Q*R                                */
    /* ------------------------------------------------------------------- */
    TSCL=0,TSCH=0;
    t_start = _itoll(TSCH,TSCL);
    status=DSPF_dp_qrd(Nrows,Ncols,A,Q,R,u);
    t_stop = _itoll(TSCH,TSCL);
    if (status==-1) {
      printf("QR decomposition failed!\n");
    }
    QRD_t=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* check decomposition: Q*R=A                                          */
    /* ------------------------------------------------------------------- */
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
        sum=0;
    	for (k=0;k<Nrows;k++) {
          sum+=Q[k+row*Nrows]*R[col+k*Ncols];
    	}
    	error=fabs(A[col+row*Ncols]-sum);
        if (error>tolerance) {
          pass=0;
          printf("opt decomposition error=%e\n",error);
        }
      }
    }

    /* ------------------------------------------------------------------- */
    /* check transformation: Q*Q'=I                                        */
    /* ------------------------------------------------------------------- */
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
        sum=0;
   	    for (k=0;k<Nrows;k++) {
   		  sum+=Q[k+row*Nrows]*Q[k+col*Nrows];
   	    }
  	    if (row==col) {
  		  error=fabs(sum-1.0);
  	    } else {
  		  error=fabs(sum);
  	    }
  	    if (error>tolerance) {
  		  pass=0;
  	    }
      }
    }

    /* ------------------------------------------------------------------------------ */
    /* check if A is invertible by looking for zeros on R diagonal                    */
    /* ------------------------------------------------------------------------------ */
    if (Nrows==Ncols) {
      invertible=1;
      for (row=0;row<Nrows;row++) {
        if (fabs(R[row+row*Ncols])<tolerance) {
    	  invertible=0;
        }
      }
    } else {
      invertible=0;
    }

    /* ------------------------------------------------------------------------------ */
    /* solve Ax=b                                                                     */
    /* ------------------------------------------------------------------------------ */
    if (invertible) {
      TSCL=0,TSCH=0;
      t_start = _itoll(TSCH,TSCL);
      status = DSPF_dp_qrd_solver(Nrows,Ncols,Q,R,b,y,x);
      t_stop = _itoll(TSCH,TSCL);
      if (status==-1) {
        printf("solver failed!\n");
      }

      /* ------------------------------------------------------------------- */
      /* verify A*x=b                                                        */
      /* ------------------------------------------------------------------- */
      for (row=0;row<Nrows;row++) {
        sum=0.0;
        for (col=0;col<Ncols;col++) {
    	  sum+=A[col+row*Ncols]*x[col];
        }
        error=fabs(b[row]-sum);
        if (error>tolerance) {
          pass=0;
          printf("opt solver error=%e\n",error);
        }
      }

      /* ------------------------------------------------------------------- */
      /* inverse A = inv(R) * Q'                                             */
      /*   note that R matrice is modified during processing                 */
      /* ------------------------------------------------------------------- */
      TSCL=0,TSCH=0;
      t_start = _itoll(TSCH,TSCL);
      status = DSPF_dp_qrd_inverse(Nrows,Ncols,Q,R,inv_A);
      t_stop = _itoll(TSCH,TSCL);

      /* ------------------------------------------------------------------- */
      /* check that inv(A)*A = identity matrix                            */
      /* ------------------------------------------------------------------- */
      for (row=0;row<Nrows;row++) {
        for (col=0;col<Ncols;col++) {
          sum=0;
    	  for (k=0;k<Ncols;k++) {
            sum+=inv_A[k+row*Ncols]*A[col+k*Ncols];
    	  }
    	  if (row==col) error=fabs(sum-1.0);
    	  else          error=fabs(sum);
          if (error>tolerance) {
            pass=0;
            printf("opt inverse error=%e",error);
          }
        }
      }
    } /* if (invertible) */

    if (pass) {
      printf("Result Successful");
      printf("\torder=%2dx%2d\tnatC: %lld\toptC: %lld\n", Nrows, Ncols, QRD_t_cn, QRD_t);
    } else {
      printf("Result Failure\torder=%2dx%2d\n", Nrows, Ncols);
    }

    if (Nrows==CYCLE_FORMULA_ORDER_PT1) {
      form_cycles[0] = QRD_t;
    } else if (Nrows==CYCLE_FORMULA_ORDER_PT2) {
      form_cycles[1] = QRD_t;
    }
  } /* for (test=1;test<=7;test++) */

  /* ------------------------------------------------------------------- */
  /* provide memory and cycles information                               */
  /* ------------------------------------------------------------------- */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
  printf("Memory:  %d bytes\n", &kernel_size);
#endif

  printf("Cycles:  %lld (order=%d)  %lld (order=%d)\n",form_cycles[0],CYCLE_FORMULA_ORDER_PT1,form_cycles[1],CYCLE_FORMULA_ORDER_PT2);

}

/* ======================================================================= */
/*  End of file:  DSPF_dp_qrd_d.c                                     */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

