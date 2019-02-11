/* ======================================================================= */
/* DSPF_sp_qrd_cmplx_d.c                                                   */
/* -- lower upper decomposition using float precision                     */
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
#include "DSPF_sp_qrd_cmplx_cn.h"
#include "DSPF_sp_qrd_cmplx.h"

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

#define MAX_MATRIX_NROWS  64 /* 195 is max for L2SRAM */
#define MAX_MATRIX_NCOLS  64 /* 195 is max for L2SRAM */
#define MAX_MATRIX_SIZE (MAX_MATRIX_NROWS*2*MAX_MATRIX_NCOLS)

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

#pragma DATA_SECTION(Q,".far:matrix")
#pragma DATA_ALIGN(Q,8)
float Q[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(R,".far:matrix")
#pragma DATA_ALIGN(R,8)
float R[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(u,".far:matrix")
#pragma DATA_ALIGN(u,8)
float u[2*MAX_MATRIX_NROWS];

#pragma DATA_SECTION(inv_A,".far:matrix")
#pragma DATA_ALIGN(inv_A,8)
float inv_A[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(b,".far:matrix")
#pragma DATA_ALIGN(b,8)
float b[2*MAX_MATRIX_NROWS];

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
	
  unsigned short test,pass,Nrows,Ncols;
  float tolerance;
  float xreal,ximag,yreal,yimag;
  float sum_real,sum_imag,error_real,error_imag;
  float max_error_cn,max_error,max_solver_error_cn,max_solver_error,max_inverse_error_cn,max_inverse_error;
  float max_transform_error_cn,max_transform_error;
  int row,col,k,status,invertible;
  long long t_overhead, t_start, t_stop;
  long long QRD_t_cn, QRD_t;

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
  tolerance=0.001;
  pass=1;

  for (test=1;test<=10;test++) {
	printf("DSPF_sp_qrd_cmplx\tIter#: %d\t", test);
	
	switch(test) {
	case 1: { Nrows=4;Ncols=2; // 4x2
              A[0]= 1;A[1]= 2;A[ 2]= 3;A[ 3]= 4;A[ 4]= 5;A[ 5]= 6;A[ 6]= 7;A[ 7]= 8;
              A[8]= 9;A[9]=10;A[10]=11;A[11]=12;A[12]=13;A[13]=14;A[14]=15;A[15]=16;
		      b[0]=2;b[1]=1;b[2]=4;b[3]=3;b[4]=6;b[5]=5;b[6]=8;b[7]=7;
		      break;
	        }
	case 2: { Nrows=4;Ncols=3; // 4x3
		      A[ 0]=A[ 1]=1;A[ 2]=A[ 3]=5;A[ 4]=A[ 5]=9;
		      A[ 6]=A[ 7]=2;A[ 8]=A[ 9]=6;A[10]=A[11]=10;
		      A[12]=A[13]=3;A[14]=A[15]=7;A[16]=A[17]=1;
		      A[18]=A[19]=4;A[20]=A[21]=8;A[22]=A[23]=2;
		      b[0]=b[1]=1;b[2]=b[3]=2;b[4]=b[5]=3;b[6]=b[7]=4;
	          break;
	        }
	case 3: { Nrows=3;Ncols=3; // 3x3
		      A[ 0]=A[ 1]=12;A[ 2]=A[ 3]=-51;A[ 4]=A[ 5]=  4;
		      A[ 6]=A[ 7]= 6;A[ 8]=A[ 9]=167;A[10]=A[11]=-68;
		      A[12]=A[13]=-4;A[14]=A[15]= 24;A[16]=A[17]=-41;
		      b[0]=b[1]=1;b[2]=b[3]=2;b[4]=b[5]=3;
	          break;
	        }
	case 4: { Nrows=3;Ncols=3; // 3x3 singular non invertible
		      A[ 0]=A[ 1]=1;A[ 2]=A[ 3]=2;A[ 4]=A[ 5]=3;
		      A[ 6]=A[ 7]=4;A[ 8]=A[ 9]=5;A[10]=A[11]=6;
		      A[12]=A[13]=7;A[14]=A[15]=8;A[16]=A[17]=9;
		      b[0]=b[1]=1;b[2]=b[3]=2;b[4]=b[5]=3;
	          break;
	        }
	case 5: { Nrows=3;Ncols=4; // 3x4
		      A[ 0]=A[ 1]=1;A[ 2]=A[ 3]= 2;A[ 4]=A[ 5]=3;A[ 6]=A[ 7]=4;
		      A[ 8]=A[ 9]=5;A[10]=A[11]= 6;A[12]=A[13]=7;A[14]=A[15]=8;
		      A[16]=A[17]=9;A[18]=A[19]=10;A[20]=A[21]=1;A[22]=A[23]=2;
		      b[0]=b[1]=1;b[2]=b[3]=2;b[4]=b[5]=3;
	          break;
	        }
	case 6: { Nrows=2;Ncols=4; // 2x4
		      A[0]=A[1]=1;A[ 2]=A[ 3]=2;A[ 4]=A[ 5]=3;A[ 6]=A[ 7]=4;
		      A[8]=A[9]=5;A[10]=A[11]=6;A[12]=A[13]=7;A[14]=A[15]=8;
		      b[0]=b[1]=1;b[2]=b[3]=2;
	          break;
	        }
	case 7: {Nrows=3;Ncols=3; // 3x3
             A[0]=0;A[1]=1;A[2]=A[3]=A[4]=A[5]=0;
             A[6]=A[7]=0;A[8]=0;A[9]=1;A[10]=A[11]=0;
             A[12]=A[13]=A[14]=A[15]=0;A[16]=0;A[17]=1;
             b[0]=b[1]=1;b[2]=b[3]=2;
             break;
            }
	case 8: {
	          Nrows=16;
		      Ncols=Nrows;
		      srand(1);
		      for (row=0;row<Nrows;row++) {                    // random matrix
		        for (col=0;col<2*Ncols;col++) {
		    	  A[row*2*Ncols+col]=(float)(rand())/((float)RAND_MAX);
		        }
		        b[2*row  ]=(float)(rand())/((float)RAND_MAX);
		        b[2*row+1]=(float)(rand())/((float)RAND_MAX);
		      }
	          break;
	        }
    case 9: { Nrows=CYCLE_FORMULA_ORDER_PT1;
	          Ncols=Nrows;
	          srand(1);
	          for (row=0;row<Nrows;row++) {
			    for (col=0;col<2*Ncols;col++) {
			      A[row*2*Ncols+col]=(float)(rand())/((float)RAND_MAX);
			    }
			    b[2*row  ]=(float)(rand())/((float)RAND_MAX);
			    b[2*row+1]=(float)(rand())/((float)RAND_MAX);
			  }
		      break;
	        }
    case 10: { Nrows=CYCLE_FORMULA_ORDER_PT2;
	           Ncols=Nrows;
	           srand(1);
	           for (row=0;row<Nrows;row++) {
			     for (col=0;col<2*Ncols;col++) {
			       A[row*2*Ncols+col]=(float)(rand())/((float)RAND_MAX);
			     }
			     b[2*row  ]=(float)(rand())/((float)RAND_MAX);
			     b[2*row+1]=(float)(rand())/((float)RAND_MAX);
			   }
		       break;
	         }
	}

    /* ------------------------------------------------------------------- */
    /* decompose A into Q and R where A=Q_cn*R_cn                          */
    /* ------------------------------------------------------------------- */
    TSCL= 0,TSCH=0;
	t_start = _itoll(TSCH, TSCL);
    status=DSPF_sp_qrd_cmplx_cn(Nrows,Ncols,A,Q,R,u);
    t_stop = _itoll(TSCH, TSCL);
    QRD_t_cn=t_stop-t_start-t_overhead;
    if (status==-1) {
      printf("QRD decomposition failed!\n");
    }

    /* ------------------------------------------------------------------- */
    /* check decomposition: Q*R=A                                          */
    /* ------------------------------------------------------------------- */
    max_error_cn=0;
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
        sum_real=0;
        sum_imag=0;
    	for (k=0;k<Nrows;k++) {
          xreal=Q[2*k  +row*2*Nrows];
          ximag=Q[2*k+1  +row*2*Nrows];
          yreal=R[2*col  +k*2*Ncols];
          yimag=R[2*col+1+k*2*Ncols];
          sum_real+=xreal*yreal-ximag*yimag;
          sum_imag+=xreal*yimag+ximag*yreal;
    	}
    	error_imag=fabs(A[2*col+1+row*2*Ncols]-sum_imag);
    	if (error_imag>max_error_cn) {
    	  max_error_cn=error_imag;
    	}
    	error_real=fabs(A[2*col  +row*2*Ncols]-sum_real);
    	if (error_real>max_error_cn) {
    	  max_error_cn=error_real;
    	}
        if (error_real>tolerance) {
          pass=0;
          printf("nat C decomp error real=%e\n",error_real);
          break;
        }
        if (error_imag>tolerance) {
          pass=0;
          printf("nat C decomp error imag=%e\n",error_imag);
          break;
        }
      }
    }

    /* ------------------------------------------------------------------- */
    /* check transformation: Q*Q'=I                                        */
    /* ------------------------------------------------------------------- */
    max_transform_error_cn=0;
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
        sum_imag=0;
        sum_real=0;
   	    for (k=0;k<Nrows;k++) {
       	  xreal= Q[2*k  +row*2*Nrows];
       	  ximag= Q[2*k+1+row*2*Nrows];
       	  yreal= Q[2*k  +col*2*Nrows];
       	  yimag=-Q[2*k+1+col*2*Nrows];
   		  sum_real+=xreal*yreal-ximag*yimag;
   		  sum_imag+=xreal*yimag+ximag*yreal;
   	    }
  	    if (row==col) {
  		  error_real=fabs(sum_real-1.0);
  	    } else {
  		  error_real=fabs(sum_real);
  	    }
  	    error_imag=fabs(sum_imag);
  	    if (error_real>max_transform_error_cn) max_transform_error_cn=error_real;
  	    if (error_imag>max_transform_error_cn) max_transform_error_cn=error_imag;
  	    if ((error_real>tolerance)||(error_imag>tolerance)) {
  		  pass=0;
  		  printf("nat C transformation error = %e %e\n",error_real,error_imag);
  	    }
      }
    }

    /* ------------------------------------------------------------------------------ */
    /* check if A is invertible by looking for zeros on R_cn diagonal                 */
    /* ------------------------------------------------------------------------------ */
    invertible=1;
     if (Nrows==Ncols) {
       for (row=0;row<Nrows;row++) {
         if ((fabs(R[2*row+row*2*Ncols])<tolerance)&&(fabs(R[2*row+1+row*2*Ncols])<tolerance)) {
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
      status = DSPF_sp_qrd_solver_cmplx_cn(Nrows,Ncols,Q,R,b,y,x);
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
        for (col=0;col<Ncols;col++) {
          xreal=A[2*col  +row*2*Ncols];
          ximag=A[2*col+1+row*2*Ncols];
          yreal=x[2*col  ];
          yimag=x[2*col+1];
          sum_real+=xreal*yreal-ximag*yimag;
          sum_imag+=xreal*yimag+ximag*yreal;
        }
        error_real=fabs(b[2*row  ]-sum_real);
        if (error_real>max_solver_error_cn) {
          max_solver_error_cn=error_real;
        }
        error_imag=fabs(b[2*row+1]-sum_imag);
        if (error_imag>max_solver_error_cn) {
          max_solver_error_cn=error_imag;
        }
        if (error_real>tolerance) {
          pass=0;
          printf("nat C solver error real=%e at row,col = %d %d\n",error_real,row,col);
          break;
        }
        if (error_imag>tolerance) {
          pass=0;
          printf("nat C solver error imag=%e at row,col = %d %d\n",error_imag,row,col);
          break;
        }
      }

      /* ------------------------------------------------------------------- */
      /* inverse A = inv(R) * Q'                                             */
      /*   note that R matrice is modified during processing                 */
      /* ------------------------------------------------------------------- */
      status = DSPF_sp_qrd_inverse_cmplx_cn(Nrows,Ncols,Q,R,inv_A);

      /* ------------------------------------------------------------------- */
      /* check that inv(A)*A = identity matrix                               */
      /* ------------------------------------------------------------------- */
      max_inverse_error_cn=0;
      for (row=0;row<Nrows;row++) {
        for (col=0;col<Ncols;col++) {
          sum_real=0;
          sum_imag=0;
    	  for (k=0;k<Ncols;k++) {
            xreal=inv_A[2*k  +row*2*Ncols];
        	ximag=inv_A[2*k+1+row*2*Ncols];
        	yreal=A[2*col  +k*2*Ncols];
        	yimag=A[2*col+1+k*2*Ncols];
    		sum_real+=xreal*yreal-ximag*yimag;
    		sum_imag+=xreal*yimag+ximag*yreal;
    	  }
    	  if (row==col) {
    		error_real=fabs(sum_real-1.0);
    	  } else {
    		error_real=fabs(sum_real);
    	  }
    	  if (error_real>max_inverse_error_cn) {
    		max_inverse_error_cn=error_real;
    	  }
    	  error_imag=fabs(sum_imag);
    	  if (error_imag>max_inverse_error_cn) {
    		max_inverse_error_cn=error_imag;
    	  }
          if (error_real>tolerance) {
            pass=0;
            printf("nat C inverse error real=%e\n",error_real);
            break;
          }
          if (error_imag>tolerance) {
            pass=0;
            printf("nat C inverse error imag=%e\n",error_imag);
            break;
          }
        }
      }
    } /* if (invertible) */

    /* ------------------------------------------------------------------- */
    /* decompose A into Q and R where A=Q*R                                */
    /* ------------------------------------------------------------------- */
    TSCL= 0,TSCH=0;
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_sp_qrd_cmplx(Nrows,Ncols,A,Q,R,u);
    t_stop = _itoll(TSCH, TSCL);
    if (status==-1) {
      printf("QR decomposition failed!\n");
    }
    QRD_t=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* check decomposition: Q*R=A                                          */
    /* ------------------------------------------------------------------- */
    max_error=0;
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
        sum_real=0;
        sum_imag=0;
    	for (k=0;k<Nrows;k++) {
          xreal=Q[2*k  +row*2*Nrows];
          ximag=Q[2*k+1+row*2*Nrows];
          yreal=R[2*col  +k*2*Ncols];
          yimag=R[2*col+1+k*2*Ncols];
          sum_real+=xreal*yreal-ximag*yimag;
          sum_imag+=xreal*yimag+ximag*yreal;
    	}
    	error_imag=fabs(A[2*col+1+row*2*Ncols]-sum_imag);
    	if (error_imag>max_error) {
    	  max_error=error_imag;
    	}
    	error_real=fabs(A[2*col  +row*2*Ncols]-sum_real);
    	if (error_real>max_error) {
    	  max_error=error_real;
    	}
        if (error_real>tolerance) {
          pass=0;
          printf("opt C decomp error real=%e\n",error_real);
          break;
        }
        if (error_imag>tolerance) {
          pass=0;
          printf("opt C decomp error imag=%e\n",error_imag);
          break;
        }
      }
    }

    /* ------------------------------------------------------------------- */
    /* check transformation: Q*Q'=I                                        */
    /* ------------------------------------------------------------------- */
    max_transform_error=0;
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
        sum_imag=0;
        sum_real=0;
   	    for (k=0;k<Nrows;k++) {
          xreal= Q[2*k  +row*2*Nrows];
          ximag= Q[2*k+1+row*2*Nrows];
       	  yreal= Q[2*k  +col*2*Nrows];
       	  yimag=-Q[2*k+1+col*2*Nrows];
   		  sum_real+=xreal*yreal-ximag*yimag;
   		  sum_imag+=xreal*yimag+ximag*yreal;
   	    }
  	    if (row==col) {
  		  error_real=fabs(sum_real-1.0);
  	    } else {
  		  error_real=fabs(sum_real);
  	    }
  	    error_imag=fabs(sum_imag);
  	    if (error_real>max_transform_error) max_transform_error=error_real;
  	    if (error_imag>max_transform_error) max_transform_error=error_imag;
  	    if ((error_real>tolerance)||(error_imag>tolerance)) {
  		  pass=0;
  		  printf("opt C transformation error = %e %e\n",error_real,error_imag);
  	    }
      }
    }

    /* ------------------------------------------------------------------------------ */
    /* check if A is invertible by looking for zeros on R diagonal                    */
    /* ------------------------------------------------------------------------------ */
    invertible=1;
    if (Nrows==Ncols) {
      for (row=0;row<Nrows;row++) {
        if ((fabs(R[2*row+row*2*Ncols])<tolerance)&&(fabs(R[2*row+1+row*2*Ncols])<tolerance)) {
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
      TSCL= 0,TSCH=0;
      t_start = _itoll(TSCH, TSCL);
      status = DSPF_sp_qrd_solver_cmplx(Nrows,Ncols,Q,R,b,y,x);
      t_stop = _itoll(TSCH, TSCL);
      if (status==-1) {
        printf("solver failed!\n");
      }
      //solver_t=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* verify A*x=b                                                        */
    /* ------------------------------------------------------------------- */
      max_solver_error=0;
      for (row=0;row<Nrows;row++) {
        sum_real=0;
        sum_imag=0;
        for (col=0;col<Ncols;col++) {
          xreal=A[2*col  +row*2*Ncols];
          ximag=A[2*col+1+row*2*Ncols];
          yreal=x[2*col  ];
          yimag=x[2*col+1];
          sum_real+=xreal*yreal-ximag*yimag;
          sum_imag+=xreal*yimag+ximag*yreal;
        }
        error_real=fabs(b[2*row  ]-sum_real);
        if (error_real>max_solver_error) {
          max_solver_error=error_real;
        }
        error_imag=fabs(b[2*row+1]-sum_imag);
        if (error_imag>max_solver_error) {
          max_solver_error=error_imag;
        }
        if (error_real>tolerance) {
          pass=0;
          printf("opt C solver error real=%e\n",error_real);
          break;
        }
        if (error_imag>tolerance) {
          pass=0;
          printf("opt C solver error imag=%e\n",error_imag);
          break;
        }
      }

      /* ------------------------------------------------------------------- */
      /* inverse A = inv(R) * Q'                                             */
      /*   note that R matrice is modified during processing                 */
      /* ------------------------------------------------------------------- */
      TSCL= 0,TSCH=0;
      t_start = _itoll(TSCH, TSCL);
      status = DSPF_sp_qrd_inverse_cmplx(Nrows,Ncols,Q,R,inv_A);
      t_stop = _itoll(TSCH, TSCL);
      //inverse_t=t_stop-t_start-t_overhead;

      /* ------------------------------------------------------------------- */
      /* check that inv(A)*A = identity matrix                            */
      /* ------------------------------------------------------------------- */
      max_inverse_error=0;
      for (row=0;row<Nrows;row++) {
        for (col=0;col<Ncols;col++) {
          sum_real=0;
          sum_imag=0;
    	  for (k=0;k<Ncols;k++) {
        	xreal=inv_A[2*k  +row*2*Ncols];
        	ximag=inv_A[2*k+1+row*2*Ncols];
        	yreal=A[2*col  +k*2*Ncols];
        	yimag=A[2*col+1+k*2*Ncols];
    		sum_real+=xreal*yreal-ximag*yimag;
    		sum_imag+=xreal*yimag+ximag*yreal;
    	  }
    	  if (row==col) {
    		error_real=fabs(sum_real-1.0);
    	  } else {
    		error_real=fabs(sum_real);
    	  }
    	  if (error_real>max_inverse_error) {
    		max_inverse_error=error_real;
    	  }
    	  error_imag=fabs(sum_imag);
    	  if (error_imag>max_inverse_error) {
    		max_inverse_error=error_imag;
    	  }
          if (error_real>tolerance) {
            pass=0;
            printf("opt C inverse error real=%e\n",error_real);
            break;
          }
          if (error_imag>tolerance) {
            pass=0;
            printf("opt C inverse error imag=%e\n",error_imag);
            break;
          }
        }
      }
    } /* if (invertible) */

    /* ------------------------------------------------------------------- */
    /* print results                                                       */
    /* ------------------------------------------------------------------- */
    if (pass) {
      printf("Result Successful");
      printf("\torder=%2dx%2d\tnatC: %lld\toptC: %lld\n", Nrows, Ncols, QRD_t_cn, QRD_t);
    } else {
      printf("Result Failure\torder=%2d\n", Nrows);
    }
	
    if (Nrows==CYCLE_FORMULA_ORDER_PT1) {
      form_cycles[0] = QRD_t;
    } else if (Nrows==CYCLE_FORMULA_ORDER_PT2) {
      form_cycles[1] = QRD_t;
    }
  } /* for (test=1;test<=10;test++) */

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
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_qrd_cmplx_d.c                                    */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

