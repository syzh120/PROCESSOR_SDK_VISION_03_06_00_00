/* ======================================================================= */
/* DSPF_sp_svd_cmplx_d.c -- Singular Value Decomposition                   */
/*                            using float precision                       */
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
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCSVDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCSVDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCSVDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
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
#include "DSPF_sp_svd_cmplx_cn.h"
#include "DSPF_sp_svd_cmplx.h"

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

#define MAX_NROWS   64 /* max is 168 for L2SRAM */
#define MAX_NCOLS   64 /* max is 168 for L2SRAM */
#define MAX_SIZE   (MAX_NROWS*2*MAX_NCOLS)
#define MAX_U_SIZE (MAX_NROWS*2*MAX_NROWS)
#define MAX_V_SIZE (MAX_NCOLS*2*MAX_NCOLS)
#define MAX_V_VECTOR_SIZE  2*MAX_NROWS

/* ======================================================================= */
/* formula arrays                                                          */
/* ======================================================================= */
#define CYCLE_FORMULA_ORDER_PT1  32
#define CYCLE_FORMULA_ORDER_PT2  64
#define FORMULA_SIZE  2
long long form_cycles[FORMULA_SIZE];

/* ======================================================================= */
/* float word alignment of arrays                                          */
/* ======================================================================= */
#pragma DATA_SECTION(A,".far:matrix")
#pragma DATA_ALIGN(A,8);
float A[MAX_SIZE];

#pragma DATA_SECTION(U,".far:matrix")
#pragma DATA_ALIGN(U,8);
float U[MAX_U_SIZE];

#pragma DATA_SECTION(V,".far:matrix")
#pragma DATA_ALIGN(V,8);
float V[MAX_V_SIZE];

#pragma DATA_SECTION(U1,".far:matrix")
#pragma DATA_ALIGN(U1,8);
float U1[MAX_U_SIZE];

#pragma DATA_SECTION(diag,".far:matrix")
#pragma DATA_ALIGN(diag,8);
float diag[2*MAX_NROWS];

#pragma DATA_SECTION(superdiag,".far:matrix")
#pragma DATA_ALIGN(superdiag,8);
float superdiag[2*MAX_NROWS];

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */

int check_decomposition(int Nrows,int Ncols,float *A,float *U,float *diag,float *V,float *U1,float *max_error,float *avg_error_SVD,char print_txt[16]);
int check_transformation(int Nrows,int Ncols,float *U,float *V,float *max_err);

void main(void) {
	
  int test,Nrows,Ncols;
  int pass,pass_cn,pass_opt;
  float max_error_cn,max_error,max_transform_error_cn,max_transform_error;
  float avg_error_SVD_cn,avg_error_SVD;
  int row,col,status;
  long long t_overhead, t_start, t_stop,SVD_t_cn,SVD_t;
  char print_txt[16];

  /* --------------------------------------------------------------------- */
  /* Compute the overhead of calling clock twice to get timing info        */
  /* --------------------------------------------------------------------- */
  TSCL= 0,TSCH=0;
  t_start = _itoll(TSCH, TSCL);
  t_stop = _itoll(TSCH, TSCL);
  t_overhead = t_stop - t_start;

  /* --------------------------------------------------------------------- */
  /* process test cases                                                    */
  /* --------------------------------------------------------------------- */
  for (test=0;test<=12;test++) {
	printf("DSPF_sp_svd_cmplx\tIter#: %d\t", test);
	
	switch(test) {
	case  0: { Nrows=3;Ncols=3; // 3x3
               A[ 0]= 1;A[ 1]= 2;A[ 2]= 3;A[ 3]= 4;A[ 4]= 5;A[ 5]= 6;
               A[ 6]= 7;A[ 7]= 8;A[ 8]= 9;A[ 9]=10;A[10]=11;A[11]=12;
               A[12]=13;A[13]=14;A[14]=15;A[15]=16;A[16]= 0;A[17]= 0;
               break;
             }
	case  1: { Nrows=4;Ncols=2; // 4x2
		       A[ 0]= 2;A[ 1]= 1;A[ 2]= 4;A[ 3]= 3;
		       A[ 4]= 6;A[ 5]= 5;A[ 6]= 8;A[ 7]= 7;
		       A[ 8]=10;A[ 9]= 9;A[10]=12;A[11]=11;
		       A[12]=14;A[13]=13;A[14]=16;A[15]=15;
	           break;
	         }
	case  2: { Nrows=3;Ncols=3; // 3x3
               A[ 0]=A[ 1]=1;A[ 2]=A[ 3]=1;A[ 4]=A[ 5]=1;
               A[ 6]=A[ 7]=1;A[ 8]=A[ 9]=2;A[10]=A[11]=3;
               A[12]=A[13]=1;A[14]=A[15]=3;A[16]=A[17]=6;
               break;
	         }
	case  3: { Nrows=3;Ncols=3; // 3x3
               A[ 0]=A[ 1]=1;A[ 2]=A[ 3]=2;A[ 4]=A[ 5]=3;
               A[ 6]=A[ 7]=4;A[ 8]=A[ 9]=5;A[10]=A[11]=6;
               A[12]=A[13]=7;A[14]=A[15]=8;A[16]=A[17]=0;
               break;
	         }
	case  4: { Nrows=3;Ncols=3; // 3x3 singular
               A[ 0]=A[ 1]=0;A[ 2]=A[ 3]=1;A[ 4]=A[ 5]=2;
               A[ 6]=A[ 7]=3;A[ 8]=A[ 9]=4;A[10]=A[11]=5;
               A[12]=A[13]=6;A[14]=A[15]=7;A[16]=A[17]=8;
               break;
	         }
	case  5: { Nrows=5;Ncols=4; // 5x4
               A[ 0]=A[ 1]=1;A[ 2]=A[ 3]=0;A[ 4]=A[ 5]=0;A[ 6]=A[ 7]=0;
               A[ 8]=A[ 9]=0;A[10]=A[11]=0;A[12]=A[13]=0;A[14]=A[15]=4;
               A[16]=A[17]=0;A[18]=A[19]=3;A[20]=A[21]=0;A[22]=A[23]=0;
               A[24]=A[25]=0;A[26]=A[27]=0;A[28]=A[29]=0;A[30]=A[31]=0;
               A[32]=A[33]=2;A[34]=A[35]=0;A[36]=A[37]=0;A[38]=A[39]=0;
               break;
	         }
	case  6: { Nrows=8;Ncols=5; // 8x5
               A[ 0]=A[ 1]=22;A[ 2]=A[ 3]=10;A[ 4]=A[ 5]= 2;A[ 6]=A[ 7]=  3;A[ 8]=A[ 9]= 7;
               A[10]=A[11]=14;A[12]=A[13]= 7;A[14]=A[15]=10;A[16]=A[17]=  0;A[18]=A[19]= 8;
               A[20]=A[21]=-1;A[22]=A[23]=13;A[24]=A[25]=-1;A[26]=A[27]=-11;A[28]=A[29]= 3;
               A[30]=A[31]=-3;A[32]=A[33]=-2;A[34]=A[35]=13;A[36]=A[37]= -2;A[38]=A[39]= 4;
               A[40]=A[41]= 9;A[42]=A[43]= 8;A[44]=A[45]= 1;A[46]=A[47]= -2;A[48]=A[49]= 4;
               A[50]=A[51]= 9;A[52]=A[53]= 1;A[54]=A[55]=-7;A[56]=A[57]=  5;A[58]=A[59]=-1;
               A[60]=A[61]= 2;A[62]=A[63]=-6;A[64]=A[65]= 6;A[66]=A[67]=  5;A[68]=A[69]= 1;
               A[70]=A[71]= 4;A[72]=A[73]= 5;A[74]=A[75]= 0;A[76]=A[77]= -2;A[78]=A[79]= 2;
	           break;
	         }
	case  7: { Nrows=5;Ncols=5; // 5x5
               A[ 0]=A[ 1]=1;A[ 2]=A[ 3]=0;A[ 4]=A[ 5]=0;A[ 6]=A[ 7]=0;A[ 8]=A[ 9]=0;
               A[10]=A[11]=0;A[12]=A[13]=1;A[14]=A[15]=0;A[16]=A[17]=0;A[18]=A[19]=0;
               A[20]=A[21]=0;A[22]=A[23]=0;A[24]=A[25]=1;A[26]=A[27]=0;A[28]=A[29]=0;
               A[30]=A[31]=0;A[32]=A[33]=0;A[34]=A[35]=0;A[36]=A[37]=1;A[38]=A[39]=0;
               A[40]=A[41]=0;A[42]=A[43]=0;A[44]=A[45]=0;A[46]=A[47]=0;A[48]=A[49]=1;
	           break;
	         }
	case  8: { Nrows=4;Ncols=5; // 4x5
               A[ 0]=A[ 1]=1;A[ 2]=A[ 3]=0;A[ 4]=A[ 5]=0;A[ 6]=A[ 7]=0;A[ 8]=A[ 9]=2;
               A[10]=A[11]=0;A[12]=A[13]=0;A[14]=A[15]=3;A[16]=A[17]=0;A[18]=A[19]=0;
               A[20]=A[21]=0;A[22]=A[23]=0;A[24]=A[25]=0;A[26]=A[27]=0;A[28]=A[29]=0;
               A[30]=A[31]=0;A[32]=A[33]=4;A[34]=A[35]=0;A[36]=A[37]=0;A[38]=A[39]=0;
	           break;
	         }
	case  9: { Nrows=2;Ncols=4; // 2x4
	           A[0]=A[1]=1;A[ 2]=A[ 3]=2;A[ 4]=A[ 5]=3;A[ 6]=A[ 7]=4;
	           A[8]=A[9]=5;A[10]=A[11]=6;A[12]=A[13]=7;A[14]=A[15]=8;
	           break;
	         }
	case 10: {
	          Nrows=16;
		      Ncols=Nrows;
		      srand(1);
		      for (row=0;row<Nrows;row++) {
		        for (col=0;col<2*Ncols;col++) {
		    	  A[row*2*Ncols+col]=(float)(rand())/((float)RAND_MAX);
		        }
		      }
	          break;
	        }
    case 11: { Nrows=CYCLE_FORMULA_ORDER_PT1;
	          Ncols=Nrows;
	          srand(1);
	          for (row=0;row<Nrows;row++) {
			    for (col=0;col<2*Ncols;col++) {
			      A[row*2*Ncols+col]=(double)(rand())/((double)RAND_MAX);
			    }
			  }
		      break;
	        }
    case 12: { Nrows=CYCLE_FORMULA_ORDER_PT2;
	           Ncols=Nrows;
	           srand(1);
	           for (row=0;row<Nrows;row++) {
			     for (col=0;col<2*Ncols;col++) {
			       A[row*2*Ncols+col]=(double)(rand())/((double)RAND_MAX);
			     }
			   }
		       break;
	         }
	}

    /* ------------------------------------------------------------------- */
    /* decompose A into Q and R where A=U*D*transpose(V) using natural C   */
    /* ------------------------------------------------------------------- */
    TSCL= 0,TSCH=0;
	t_start = _itoll(TSCH, TSCL);
    status=DSPF_sp_svd_cmplx_cn(Nrows,Ncols,A,U,V,U1,diag,superdiag);
    t_stop = _itoll(TSCH, TSCL);
    SVD_t_cn=t_stop-t_start-t_overhead;
    if (status==-1) {
      printf("natural C SV decomposition failed!\n");
    }

    /* ------------------------------------------------------------------- */
    /* check decomposition: U*D*transpose(V)=A                             */
    /* ------------------------------------------------------------------- */
    strcpy(print_txt,"nat decomp: ");
    pass_cn=check_decomposition(Nrows,Ncols,A,U,diag,V,U1,&max_error_cn,&avg_error_SVD_cn,print_txt);

    /* ------------------------------------------------------------------- */
    /* check transformation: U*U'=V*V'=I                                   */
    /* ------------------------------------------------------------------- */
    pass_cn=pass_cn && check_transformation(Nrows,Ncols,U,V,&max_transform_error_cn);

    /* ------------------------------------------------------------------- */
    /* decompose A into Q and R where A=U*D*transpose(V) using optimized C */
    /* ------------------------------------------------------------------- */
    TSCL= 0,TSCH=0;
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_sp_svd_cmplx(Nrows,Ncols,A,U,V,U1,diag,superdiag);
    t_stop = _itoll(TSCH, TSCL);
    if (status==-1) {
      printf("optimized C SV decomposition failed!\n");
    }
    SVD_t=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* check decomposition: U*D*transpose(V)=A                             */
    /* ------------------------------------------------------------------- */
    strcpy(print_txt,"opt decomp: ");
    pass_opt=check_decomposition(Nrows,Ncols,A,U,diag,V,U1,&max_error,&avg_error_SVD,print_txt);

    /* ------------------------------------------------------------------- */
    /* check transformation: U*U'=V*V'=I                                   */
    /* ------------------------------------------------------------------- */
    pass_opt=pass_opt && check_transformation(Nrows,Ncols,U,V,&max_transform_error);
    pass=(pass_cn)&&(pass_opt);

    /* ------------------------------------------------------------------- */
    /* print results                                                       */
    /* ------------------------------------------------------------------- */
    if (pass) {
      printf("Result Successful");
      printf("\torder=%2dx%2d\tnatC: %lld\toptC: %lld\n", Nrows, Ncols, SVD_t_cn, SVD_t);
    } else {
      printf("Result Failure\torder=%2d\n", Nrows);
    }
	
    if (Nrows==CYCLE_FORMULA_ORDER_PT1) {
      form_cycles[0] = SVD_t;
    } else if (Nrows==CYCLE_FORMULA_ORDER_PT2) {
      form_cycles[1] = SVD_t;
    }
  } /* for (test=1;test<=12;test++) */

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

int check_decomposition(int Nrows,int Ncols,float *A,float *U,float *diag,float *V,float *U1,float *max_error,float *avg_error_SVD,char print_txt[16]) {

  int pass,row,col,k;
  float tolerance,max_err;
  float xreal,ximag,yreal,yimag;
  float error_real,error_imag;
  float sum_real,sum_imag;
#ifdef ENABLE_PROFILE
  float total_error=0;
#endif

  pass=1;
  tolerance=0.0003;
  max_err=0;
#ifndef ENABLE_REDUCED_FORM
  for (row=0;row<Nrows;row++) {
    for (col=0;col<Ncols;col++) {
      if (col<Nrows) {
	    /* U1[col+row*Ncols]=U[col+row*Nrows]*diag[col]; */
       	xreal=U[2*col  +row*2*Nrows];
       	ximag=U[2*col+1+row*2*Nrows];
       	yreal=diag[2*col  ];
       	yimag=diag[2*col+1];
       	U1[2*col  +row*2*Ncols]=xreal*yreal-ximag*yimag;
       	U1[2*col+1+row*2*Ncols]=xreal*yimag+ximag*yreal;
      } else {
       	/* U1[col+row*Ncols]=0; */
       	U1[2*col  +row*2*Ncols]=0;
       	U1[2*col+1+row*2*Ncols]=0;
      }
    }
  }
  for (row=0;row<Nrows;row++) {
    for (col=0;col<Ncols;col++) {
      sum_real=0;
      sum_imag=0;
	  for (k=0;k<Ncols;k++) {
        /* sum+=U1[k+row*Ncols]*conj(V[k+col*Ncols]); */
		xreal= U1[2*k  +row*2*Ncols];
		ximag= U1[2*k+1+row*2*Ncols];
		yreal= V[2*k  +col*2*Ncols];
		yimag=-V[2*k+1+col*2*Ncols];
	    sum_real+=xreal*yreal-ximag*yimag;
	    sum_imag+=xreal*yimag+ximag*yreal;
	  }
	  error_real=fabs(A[2*col  +row*2*Ncols]-sum_real);
	  if (error_real>max_err) {
	    max_err=error_real;
	  }
	  error_imag=fabs(A[2*col+1+row*2*Ncols]-sum_imag);
	  if (error_imag>max_err) {
	    max_err=error_imag;
	  }
#ifndef ENABLE_PROFILE
      if ((error_real>tolerance)||(error_imag>tolerance)||(isnan(error_imag))) {
        pass=0;
        printf("%s orig=%e %e  calc=%e %e error=%e %e\n",print_txt,A[2*col+1+row*2*Ncols],A[2*col+row*2*Ncols],sum_real,sum_imag,error_real,error_imag);
      }
#else
      total_error+=error_real+error_imag;
#endif
    }
  }
#else
  if (Nrows>=Ncols) {
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
	    /* U1[col+row*Ncols]=U[col+row*Ncols]*diag[col]; */
       	xreal=U[2*col  +row*2*Ncols];
       	ximag=U[2*col+1+row*2*Ncols];
       	yreal=diag[2*col  ];
       	yimag=diag[2*col+1];
       	U1[2*col  +row*2*Ncols]=xreal*yreal-ximag*yimag;
       	U1[2*col+1+row*2*Ncols]=xreal*yimag+ximag*yreal;
      }
    }
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
        sum_real=0;
        sum_imag=0;
	    for (k=0;k<Ncols;k++) {
          /* sum+=U1[k+row*Ncols]*conj(V[k+col*Ncols]); */
		  xreal= U1[2*k  +row*2*Ncols];
		  ximag= U1[2*k+1+row*2*Ncols];
		  yreal= V[2*k  +col*2*Ncols];
		  yimag=-V[2*k+1+col*2*Ncols];
		  sum_real+=xreal*yreal-ximag*yimag;
		  sum_imag+=xreal*yimag+ximag*yreal;
		}
		error_real=fabs(A[2*col  +row*2*Ncols]-sum_real);
		if (error_real>max_err) {
		  max_err=error_real;
		}
		error_imag=fabs(A[2*col+1+row*2*Ncols]-sum_imag);
	    if (error_imag>max_err) {
	      max_err=error_imag;
	    }
#ifndef ENABLE_PROFILE
        if ((error_real>tolerance)||(error_imag>tolerance)||(isnan(error_real))||isnan(error_imag)) {
          pass=0;
          printf("%s orig=%e %e  calc=%e %e  error=%e %e\n",print_txt,A[2*col+1+row*2*Ncols],A[2*col+row*2*Ncols],sum_real,sum_imag,error_real,error_imag);
        }
#else
        total_error+=error_real+error_imag;
#endif
      }
    }
  } else { /* Nrows<Ncols */
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
  	    /* U1[col+row*Nrows]=U[col+row*Nrows]*diag[col]; */
      	xreal=U[2*col  +row*2*Nrows];
       	ximag=U[2*col+1+row*2*Nrows];
       	yreal=diag[2*col  ];
       	yimag=diag[2*col+1];
       	U1[2*col  +row*2*Nrows]=xreal*yreal-ximag*yimag;
       	U1[2*col+1+row*2*Nrows]=xreal*yimag+ximag*yreal;
      }
    }
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
        sum_real=0;
        sum_imag=0;
	    for (k=0;k<Nrows;k++) {
          /* sum+=U1[k+row*Nrows]*conj(V[k+col*Nrows]); */
		  xreal= U1[2*k  +row*2*Nrows];
		  ximag= U1[2*k+1+row*2*Nrows];
		  yreal= V[2*k  +col*2*Nrows];
		  yimag=-V[2*k+1+col*2*Nrows];
		  sum_real+=xreal*yreal-ximag*yimag;
		  sum_imag+=xreal*yimag+ximag*yreal;
		}
		error_real=fabs(A[2*col  +row*2*Ncols]-sum_real);
		if (error_real>max_err) {
		  max_err=error_real;
		}
		error_imag=fabs(A[2*col+1+row*2*Ncols]-sum_imag);
	    if (error_imag>max_err) {
	      max_err=error_imag;
	    }
#ifndef ENABLE_PROFILE
        if ((error_real>tolerance)||(error_imag>tolerance)||(isnan(error_real))||(isnan(error_imag))) {
          pass=0;
          printf("%s orig=%e %e  calc=%e %e  error=%e %e\n",print_txt,A[2*col+1+row*2*Ncols],A[2*col+row*2*Ncols],sum_real,sum_imag,error_real,error_imag);
        }
#else
        total_error+=error;
#endif
      }
    }
  } /* if (Nrows>=Ncols) */
#endif

#ifdef ENABLE_PROFILE
  *avg_error_SVD=total_error/(2.0*(float)Nrows*(float)Ncols);
#endif

  *max_error=max_err;

  return pass;
}

int check_transformation(int Nrows,int Ncols,float *U,float *V,float *max_err) {

  int row,col,k,width,pass;
  float tolerance;
  float xreal,ximag,yreal,yimag;
  float sum_real,sum_imag,error_real,error_imag;
  float max_error=0;

  pass=1;
  tolerance=0.001;
  /* check U*U'=I */
#ifndef ENABLE_REDUCED_FORM
  width=Nrows;
  for (row=0;row<Nrows;row++) {
    for (col=0;col<width;col++) {
      sum_real=0;
      sum_imag=0;
 	  for (k=0;k<width;k++) {
 		/* sum+=U[k+row*width]*conj(U[k+col*width]); */
 	  	xreal= U[2*k  +row*2*width];
 	 	ximag= U[2*k+1+row*2*width];
 	 	yreal= U[2*k  +col*2*width];
 	 	yimag=-U[2*k+1+col*2*width];
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
	  if (error_real>max_error) max_error=error_real;
	  if (error_imag>max_error) max_error=error_imag;
#ifndef ENABLE_PROFILE
	  if ((error_real>tolerance)||(error_imag>tolerance)) {
		pass=0;
		printf("U tranform error=%e %e\n",error_real,error_imag);
	  }
#endif
    }
  }

  /* check V*V'=I */
  for (row=0;row<Ncols;row++) {
    for (col=0;col<Ncols;col++) {
      sum_real=0;
      sum_imag=0;
 	  for (k=0;k<Ncols;k++) {
 		/* sum+=V[k+row*Ncols]*conj(V[k+col*Ncols]); */
 	 	xreal= V[2*k  +row*2*Ncols];
 	 	ximag= V[2*k+1+row*2*Ncols];
 	 	yreal= V[2*k  +col*2*Ncols];
 	 	yimag=-V[2*k+1+col*2*Ncols];
 		sum_real+=xreal*yreal-ximag*yimag;
 		sum_imag+=xreal*yimag+ximag*yreal;
 	  }
	  if (row==col) {
		error_real=fabs(sum_real-1.0);
	  } else {
		error_real=fabs(sum_real);
	  }
	  error_imag=fabs(sum_imag);
	  if (error_real>max_error) max_error=error_real;
	  if (error_imag>max_error) max_error=error_imag;
#ifndef ENABLE_PROFILE
	  if ((error_real>tolerance)||(error_imag>tolerance)) {
		pass=0;
		printf("V tranform error=%e %e\n",error_real,error_imag);
	  }
#endif
    }
  }
#else
  if (Nrows>=Ncols) { /* check V only */
	/* check V*V'=I */
	for (row=0;row<Ncols;row++) {
	  for (col=0;col<Ncols;col++) {
	    sum_real=0;
	    sum_imag=0;
	    for (k=0;k<Ncols;k++) {
	      /* sum+=V[k+row*Ncols]*conj(V[k+col*Ncols]); */
		  xreal= V[2*k  +row*2*Ncols];
		  ximag= V[2*k+1+row*2*Ncols];
		  yreal= V[2*k  +col*2*Ncols];
		  yimag=-V[2*k+1+col*2*Ncols];
	      sum_real+=xreal*yreal-ximag*yimag;
	      sum_imag+=xreal*yimag+ximag*yreal;
	 	}
		if (row==col) {
		  error_real=fabs(sum_real-1.0);
		} else {
		  error_real=fabs(sum_real);
		}
		error_imag=fabs(sum_imag);
		if (error_real>max_error) max_error=error_real;
		if (error_imag>max_error) max_error=error_imag;
		if ((error_real>tolerance)||(error_imag>tolerance)) {
		  pass=0;
		  printf("nat C transform fails\n");
		}
	  }
	}
  } else {            /* check U only */
    /* check U*U'=I */
	width=Nrows;
	for (row=0;row<Nrows;row++) {
	  for (col=0;col<width;col++) {
	    sum_real=0;
	    sum_imag=0;
	    for (k=0;k<width;k++) {
	 	  /* sum+=U[k+row*width]*conj(U[k+col*width]); */
		  xreal= U[2*k  +row*2*width];
		  ximag= U[2*k+1+row*2*width];
		  yreal= U[2*k  +col*2*width];
		  yimag=-U[2*k+1+col*2*width];
	      sum_real+=xreal*yreal-ximag*yimag;
	      sum_imag+=xreal*yimag+ximag*yreal;
	 	}
		if (row==col) {
		  error_real=fabs(sum_real-1.0);
		} else {
		  error_real=fabs(sum_real);
		}
		error_imag=fabs(sum_imag);
		if (error_real>max_error) max_error=error_real;
		if (error_imag>max_error) max_error=error_imag;
		if ((error_real>tolerance)||(error_imag>tolerance)) {
		  pass=0;
		  printf("nat c transform fails\n");
		}
	  }
	}
  }
#endif

  *max_err=max_error;

  return pass;
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_svd_cmplx_d.c                                    */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

