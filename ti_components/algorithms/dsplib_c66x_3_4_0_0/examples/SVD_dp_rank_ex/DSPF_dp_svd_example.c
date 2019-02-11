/* ======================================================================= */
/* DSPF_dp_svd_example.c -- Singular Value Decomposition example           */
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

/* ======================================================================= */
/* Interface header files                                                  */
/* ======================================================================= */
#include <ti/dsplib/dsplib.h>

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

#define MAX_NROWS   150 /* max is 150 */
#define MAX_NCOLS   150 /* max is 150 */
#define MAX_SIZE   (MAX_NROWS*MAX_NCOLS)
#define MAX_U_SIZE (MAX_NROWS*MAX_NROWS)
#define MAX_V_SIZE (MAX_NCOLS*MAX_NCOLS)
#define MAX_V_VECTOR_SIZE  MAX_NROWS

/* ======================================================================= */
/* double word alignment of arrays                                         */
/* ======================================================================= */
#pragma DATA_SECTION(A,".matrix")
#pragma DATA_ALIGN(A,8);
double A[MAX_SIZE];

#pragma DATA_SECTION(U,".matrix")
#pragma DATA_ALIGN(U,8);
double U[MAX_U_SIZE];

#pragma DATA_SECTION(V,".matrix")
#pragma DATA_ALIGN(V,8);
double V[MAX_V_SIZE];

#pragma DATA_SECTION(U1,".matrix")
#pragma DATA_ALIGN(U1,8);
double U1[MAX_U_SIZE];

#pragma DATA_SECTION(diag,".matrix")
#pragma DATA_ALIGN(diag,8);
double diag[MAX_NROWS];

#pragma DATA_SECTION(superdiag,".matrix")
#pragma DATA_ALIGN(superdiag,8);
double superdiag[MAX_NROWS];

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */
void main(void) {
	
  int test,Nrows,Ncols;
  int row,col,status;
  int rank,loop_limit;
  double tolerance=0.000001;

  /* --------------------------------------------------------------------- */
  /* process test cases                                                    */
  /* --------------------------------------------------------------------- */
  for (test=1;test<=10;test++) {
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
	case 10: {
	          Nrows=16;
		      Ncols=Nrows;
		      srand(1);
		      for (row=0;row<Nrows;row++) {
		        for (col=0;col<Ncols;col++) {
		    	  A[row*Ncols+col]=(double)(rand())/((double)RAND_MAX);
		        }
		      }
	          break;
	        }
	}

    /* ------------------------------------------------------------------- */
    /* decompose A into Q and R where A=U*D*transpose(V) using optimized C */
    /* ------------------------------------------------------------------- */
    status=DSPF_dp_svd(Nrows,Ncols,A,U,V,U1,diag,superdiag);
    if (status==-1) {
      printf("optimized C SV decomposition failed!\n");
    }


    /* ------------------------------------------------------------------- */
    /* determine matrix rank by counting non singular values               */
    /* ------------------------------------------------------------------- */
    if (Nrows>=Ncols) {
      loop_limit=Ncols;
    } else {
      loop_limit=Nrows;
    }
    rank=0;
    for (row=0;row<loop_limit;row++) {
       if (fabs(diag[row])>tolerance) {
    	 rank++;
       }
    }

    printf("test=%d:  %dx%d matrix has rank=%d\n",test,Nrows,Ncols,rank);

  } /* for (test=1;test<=10;test++) */

}

/* ======================================================================= */
/*  End of file:  DSPF_dp_svd_example.c                                    */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

