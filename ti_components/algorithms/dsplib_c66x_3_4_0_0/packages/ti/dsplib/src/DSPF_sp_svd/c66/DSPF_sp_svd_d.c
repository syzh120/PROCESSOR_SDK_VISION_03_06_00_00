/* ======================================================================= */
/* DSPF_sp_svd_d.c -- Singular Value Decomposition using float precision  */
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
#include "DSPF_sp_svd_cn.h"
#include "DSPF_sp_svd.h"

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

#define MAX_NROWS   128 /* max is 239 for L2SRAM */
#define MAX_NCOLS   128 /* max is 239 for L2SRAM */
#define MAX_SIZE   (MAX_NROWS*MAX_NCOLS)
#define MAX_U_SIZE (MAX_NROWS*MAX_NCOLS)
#define MAX_V_SIZE (MAX_NROWS*MAX_NCOLS)
#define MAX_V_VECTOR_SIZE  MAX_NROWS

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
float A[MAX_SIZE];

#pragma DATA_SECTION(U,".far:matrix")
#pragma DATA_ALIGN(U,8)
float U[MAX_U_SIZE];

#pragma DATA_SECTION(V,".far:matrix")
#pragma DATA_ALIGN(V,8)
float V[MAX_V_SIZE];

#pragma DATA_SECTION(U1,".far:matrix")
#pragma DATA_ALIGN(U1,8)
float U1[MAX_U_SIZE];

#pragma DATA_SECTION(diag,".far:matrix")
#pragma DATA_ALIGN(diag,8)
float diag[MAX_NROWS];

#pragma DATA_SECTION(superdiag,".far:matrix")
#pragma DATA_ALIGN(superdiag,8)
float superdiag[MAX_NROWS];

int check_decomposition(int Nrows,int Ncols,float *A,float *U,float *diag,float *V,float *U1,float *max_error,float *avg_error_SVD,char print_txt[16]);
int check_transformation(int Nrows,int Ncols,float *U,float *V);

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */

void main(void) {
	
  int test,Nrows,Ncols;
  int pass,pass_cn,pass_opt;
  int row,col,status;
  float max_error_cn,max_error,avg_error_SVD_cn,avg_error_SVD;
  long long t_overhead, t_start, t_stop, SVD_t, SVD_cn_t;
  char print_txt[16];
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
  for (test=1;test<=11;test++) {
	printf("DSPF_sp_svd\tIter#: %d\t", test);
	
	switch(test) {
	case  1: { Nrows=4;Ncols=2; // 4x2
		       A[0]=1;A[1]=2;A[2]=3;A[3]=4;A[4]=5;A[5]=6;A[6]=7;A[7]=8;
	           break;
	         }
	case  2: { Nrows=3;Ncols=3; // 3x3
               A[0]=1;A[1]=1;A[2]=1;
               A[3]=1;A[4]=2;A[5]=3;
               A[6]=1;A[7]=3;A[8]=6;
               break;
	         }
	case  3: { Nrows=3;Ncols=3; // 3x3
               A[0]=1;A[1]=2;A[2]=3;
               A[3]=4;A[4]=5;A[5]=6;
               A[6]=7;A[7]=8;A[8]=0;
               break;
	         }
	case  4: { Nrows=3;Ncols=3; // 3x3 singular
               A[0]=0;A[1]=1;A[2]=2;
               A[3]=3;A[4]=4;A[5]=5;
               A[6]=6;A[7]=7;A[8]=8;
               break;
	         }
	case  5: { Nrows=5;Ncols=4; // 5x4
               A[ 0]=1;A[ 1]=0;A[ 2]=0;A[ 3]=0;
               A[ 4]=0;A[ 5]=0;A[ 6]=0;A[ 7]=4;
               A[ 8]=0;A[ 9]=3;A[10]=0;A[11]=0;
               A[12]=0;A[13]=0;A[14]=0;A[15]=0;
               A[16]=2;A[17]=0;A[18]=0;A[19]=0;
               break;
	         }
	case  6: { Nrows=8;Ncols=5; // 8x5
               A[ 0]=22;A[ 1]=10;A[ 2]= 2;A[ 3]=  3;A[ 4]= 7;
               A[ 5]=14;A[ 6]= 7;A[ 7]=10;A[ 8]=  0;A[ 9]= 8;
               A[10]=-1;A[11]=13;A[12]=-1;A[13]=-11;A[14]= 3;
               A[15]=-3;A[16]=-2;A[17]=13;A[18]= -2;A[19]= 4;
               A[20]= 9;A[21]= 8;A[22]= 1;A[23]= -2;A[24]= 4;
               A[25]= 9;A[26]= 1;A[27]=-7;A[28]=  5;A[29]=-1;
               A[30]= 2;A[31]=-6;A[32]= 6;A[33]=  5;A[34]= 1;
               A[35]= 4;A[36]= 5;A[37]= 0;A[38]= -2;A[39]= 2;
	           break;
	         }
	case  7: { Nrows=5;Ncols=5; // 5x5
               A[ 0]=1;A[ 1]=0;A[ 2]=0;A[ 3]=0;A[ 4]=0;
               A[ 5]=0;A[ 6]=1;A[ 7]=0;A[ 8]=0;A[ 9]=0;
               A[10]=0;A[11]=0;A[12]=1;A[13]=0;A[14]=0;
               A[15]=0;A[16]=0;A[17]=0;A[18]=1;A[19]=0;
               A[20]=0;A[21]=0;A[22]=0;A[23]=0;A[24]=1;
	           break;
	         }
	case  8: { Nrows=4;Ncols=5; // 4x5
               A[ 0]=1;A[ 1]=0;A[ 2]=0;A[ 3]=0;A[ 4]=2;
               A[ 5]=0;A[ 6]=0;A[ 7]=3;A[ 8]=0;A[ 9]=0;
               A[10]=0;A[11]=0;A[12]=0;A[13]=0;A[14]=0;
               A[15]=0;A[16]=4;A[17]=0;A[18]=0;A[19]=0;
	           break;
	         }
	case  9: { Nrows=2;Ncols=4; // 2x4
	           A[0]=1;A[1]=2;A[2]=3;A[3]=4;
	           A[4]=5;A[5]=6;A[6]=7;A[7]=8;
	           break;
	         }
	case 10: {Nrows=CYCLE_FORMULA_ORDER_PT1;
		      Ncols=Nrows;
		      srand(1);
		      for (row=0;row<Nrows;row++) {
		        for (col=0;col<Ncols;col++) {
		    	  A[row*Ncols+col]=(float)(rand())/((float)RAND_MAX);
		        }
		      }
	          break;
	        }
	case 11: {Nrows=CYCLE_FORMULA_ORDER_PT2;
		      Ncols=Nrows;
		      srand(1);
		      for (row=0;row<Nrows;row++) {
		        for (col=0;col<Ncols;col++) {
		    	  A[row*Ncols+col]=(float)(rand())/((float)RAND_MAX);
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
    status = DSPF_sp_svd_cn(Nrows,Ncols,A,U,V,U1,diag,superdiag);
    t_stop = _itoll(TSCH, TSCL);
    SVD_cn_t = t_stop-t_start-t_overhead;
    if (status==-1) {
      printf("natual C:  SV decomposition failed!\n");
    }

    /* ------------------------------------------------------------------- */
    /* check decomposition: U*D*transpose(V)=A                             */
    /* ------------------------------------------------------------------- */
    strcpy(print_txt,"natural: ");
    pass_cn=check_decomposition(Nrows,Ncols,A,U,diag,V,U1,&max_error_cn,&avg_error_SVD_cn,print_txt);

    /* ------------------------------------------------------------------- */
    /* check transformation: U*U'=V*V'=I                                   */
    /* ------------------------------------------------------------------- */
    pass_cn=pass_cn && check_transformation(Nrows,Ncols,U,V);

    /* ------------------------------------------------------------------- */
    /* decompose A into Q and R where A=U*D*transpose(V) using optimized C */
    /* ------------------------------------------------------------------- */
    TSCL= 0,TSCH=0;
    t_start = _itoll(TSCH, TSCL);
    status = DSPF_sp_svd(Nrows,Ncols,A,U,V,U1,diag,superdiag);
    t_stop = _itoll(TSCH, TSCL);
    if (status==-1) {
      printf("optimized C:  SV decomposition failed!\n");
    }
    SVD_t=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* check decomposition: U*D*transpose(V)=A                             */
    /* ------------------------------------------------------------------- */
    strcpy(print_txt,"optimized: ");
    pass_opt=check_decomposition(Nrows,Ncols,A,U,diag,V,U1,&max_error,&avg_error_SVD,print_txt);

    /* ------------------------------------------------------------------- */
    /* check transformation: U*U'=V*V'=I                                   */
    /* ------------------------------------------------------------------- */
    pass_opt=pass_opt && check_transformation(Nrows,Ncols,U,V);

    pass=(pass_cn)&&(pass_opt);
	
    if (pass) {
      printf("Result Successful");
      printf("\torder=%2dx%2d\tnatC: %lld\toptC: %lld\n", Nrows, Ncols, SVD_cn_t, SVD_t);
    } else {
      printf("Result Failure\torder=%2dx%2d\n", Nrows, Ncols);
    }

    if (Nrows==CYCLE_FORMULA_ORDER_PT1) {
      form_cycles[0] = SVD_t;
    } else if (Nrows==CYCLE_FORMULA_ORDER_PT2) {
      form_cycles[1] = SVD_t;
    }
  } /* for (test=1;test<=11;test++) */

  /* ------------------------------------------------------------------- */
  /* provide memory and cycles information                               */
  /* ------------------------------------------------------------------- */
#ifdef __TI_COMPILER_VERSION__            // for TI compiler only
  printf("Memory:  %d bytes\n", &kernel_size);
#endif

  printf("Cycles:  %lld (order=%d)  %lld (order=%d)\n",form_cycles[0],CYCLE_FORMULA_ORDER_PT1,form_cycles[1],CYCLE_FORMULA_ORDER_PT2);

}

int check_decomposition(int Nrows,int Ncols,float *A,float *U,float *D,float *V,float *U1,float *max_error,float *avg_error_SVD,char print_txt[16]) {

  int pass,row,col,k;
  float total_error,sum,error,max_err;
#ifndef ENABLE_PROFILE
  float tolerance=0.001;
#endif

  pass=1;
  total_error=0;
  max_err=0;
#ifndef ENABLE_REDUCED_FORM
  for (row=0;row<Nrows;row++) {
    for (col=0;col<Ncols;col++) {
      if (col<Nrows) {
  	    U1[col+row*Ncols]=U[col+row*Nrows]*diag[col];
      } else {
    	  U1[col+row*Ncols]=0;
      }
    }
  }
  for (row=0;row<Nrows;row++) {
    for (col=0;col<Ncols;col++) {
      sum=0;
	  for (k=0;k<Ncols;k++) {
        sum+=U1[k+row*Ncols]*V[k+col*Ncols];
  	  }
  	  error=fabs(A[col+row*Ncols]-sum);
  	  if (error>max_err) {
  	    max_err=error;
  	  }
#ifndef ENABLE_PROFILE
      if ((error>tolerance)||(isnan(error))) {
        pass=0;
        printf("%s orig=%e  calc=%e  error=%e\n",print_txt,A[col+row*Ncols],sum,error);
        break;
      } else {
 	    total_error+=error;
      }
#else
      total_error+=error;
#endif
    }
    if (pass==0) {
  	  break;
    }
  }
#else
  if (Nrows>=Ncols) {
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
  	    U1[col+row*Ncols]=U[col+row*Ncols]*diag[col];
      }
    }
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
        sum=0;
	    for (k=0;k<Ncols;k++) {
          sum+=U1[k+row*Ncols]*V[k+col*Ncols];
  	    }
  	    error=fabs(A[col+row*Ncols]-sum);
  	    if (error>max_err) {
  	      max_err=error;
  	    }
#ifndef ENABLE_PROFILE
        if ((error>tolerance)||(isnan(error))) {
          pass=0;
          printf("%s orig=%e  calc=%e  error=%e\n",print_txt,A[col+row*Ncols],sum,error);
          break;
        } else {
 	      total_error+=error;
        }
#else
        total_error+=error;
#endif
      }
      if (pass==0) {
  	    break;
      }
    }
  } else { /* Nrows<Ncols */
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Nrows;col++) {
    	U1[col+row*Nrows]=U[col+row*Nrows]*diag[col];
      }
    }
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
        sum=0;
 	    for (k=0;k<Nrows;k++) {
          sum+=U1[k+row*Nrows]*V[k+col*Nrows];
  	    }
  	    error=fabs(A[col+row*Ncols]-sum);
  	    if (error>max_err) {
  	      max_err=error;
  	    }
#ifndef ENABLE_PROFILE
        if ((error>tolerance)||(isnan(error))) {
          pass=0;
          printf("%s orig=%e  calc=%e  error=%e\n",print_txt,A[col+row*Ncols],sum,error);
          break;
        } else {
  	      total_error+=error;
        }
#else
        total_error+=error;
#endif
      }
      if (pass==0) {
  	    break;
      }
    }
  } /* if (Nrows>=Ncols) */
#endif
  *avg_error_SVD=total_error/((float)Nrows*(float)Ncols);
  *max_error=max_err;

   return pass;
}

int check_transformation(int Nrows,int Ncols,float *U,float *V) {

  int row,col,k,width,pass;
  float sum,error,tolerance;

  pass=1;
  tolerance=0.001;
  /* check U*U'=I */
#ifndef ENABLE_REDUCED_FORM
  width=Nrows;
  for (row=0;row<Nrows;row++) {
    for (col=0;col<width;col++) {
      sum=0;
 	  for (k=0;k<width;k++) {
 		sum+=U[k+row*width]*U[k+col*width];
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

  /* check V*V'=I */
  for (row=0;row<Ncols;row++) {
    for (col=0;col<Ncols;col++) {
      sum=0;
 	  for (k=0;k<Ncols;k++) {
 		sum+=V[k+row*Ncols]*V[k+col*Ncols];
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
#else
  if (Nrows>=Ncols) { /* check V only */
	/* check V*V'=I */
	for (row=0;row<Ncols;row++) {
	  for (col=0;col<Ncols;col++) {
	    sum=0;
	    for (k=0;k<Ncols;k++) {
	      sum+=V[k+row*Ncols]*V[k+col*Ncols];
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
  } else {            /* check U only */
    /* check U*U'=I */
	width=Nrows;
	for (row=0;row<Nrows;row++) {
	  for (col=0;col<width;col++) {
	    sum=0;
	    for (k=0;k<width;k++) {
	 	  sum+=U[k+row*width]*U[k+col*width];
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
  }
#endif

  return pass;
}

/* ======================================================================= */
/*  End of file:  DSPF_sp_svd_d.c                                     */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

