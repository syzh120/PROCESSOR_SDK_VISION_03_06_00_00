/* ======================================================================= */
/* DSPF_dp_qrd_example.c -- example of using QR decomposition              */
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

#define MAX_MATRIX_NROWS   194 /* 194 is max */
#define MAX_MATRIX_NCOLS   194 /* 194 is max */
#define MAX_MATRIX_SIZE (MAX_MATRIX_NROWS*MAX_MATRIX_NCOLS)

/* ======================================================================= */
/* double word alignment of arrays                                         */
/* ======================================================================= */
#pragma DATA_SECTION(A,".matrix")
#pragma DATA_ALIGN(A,8)
double A[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(Q,".matrix")
#pragma DATA_ALIGN(Q,8)
double Q[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(R,".matrix")
#pragma DATA_ALIGN(R,8)
double R[MAX_MATRIX_SIZE];

#pragma DATA_SECTION(u,".matrix")
#pragma DATA_ALIGN(u,8)
double u[MAX_MATRIX_NROWS];

/* ======================================================================= */
/* profile arrays                                                          */
/* ======================================================================= */
unsigned short order[MAX_MATRIX_NROWS];
double QRD_cycles[MAX_MATRIX_NROWS];
double V[4*MAX_MATRIX_NROWS];
double z[MAX_MATRIX_NROWS];
double poly_coef_QRD[5];

/* ======================================================================= */
/* profile arrays                                                          */
/* ======================================================================= */
int gen_polynomial_coefficients(const unsigned short Nrows,const unsigned short Ncols,
     unsigned short *order,double *cycles,double *V,double *z,double *poly_coef);

/* ======================================================================= */
/* Main -- Top level driver for testing the algorithm                      */
/* ======================================================================= */

void main(void) {
	
  unsigned short pass,Nrows,Ncols;
  double sum,tolerance,error,y_QRD;
  int row,col,k,status;
  long long t_overhead, t_start, t_stop;
  long long QRD_t;
  unsigned short n;
  FILE *fid;
  unsigned short profile_idx,degree_QRD;

  profile_idx=0;
  fid=fopen("performance.dat","w");

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
  for (Nrows=3;Nrows<=194;Nrows++) {
    Ncols=Nrows;
    srand(1);
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
        A[row*Ncols+col]=(float)(rand())/((float)RAND_MAX);
      }
    }

    /* ------------------------------------------------------------------- */
    /* decompose A into Q and R where A=Q*R                                */
    /* ------------------------------------------------------------------- */
    TSCL= 0,TSCH=0;
    t_start = _itoll(TSCH, TSCL);
    status=DSPF_dp_qrd(Nrows,Ncols,A,Q,R,u);
    t_stop = _itoll(TSCH, TSCL);
    if (status==-1) {
      printf("QR decomposition failed!\n");
    }
    QRD_t=t_stop-t_start-t_overhead;

    /* ------------------------------------------------------------------- */
    /* check decomposition: Q*R=A                                          */
    /* ------------------------------------------------------------------- */
    tolerance=0.000001;
    for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
        sum=0;
    	for (k=0;k<Nrows;k++) {
          sum+=Q[k+row*Nrows]*R[col+k*Ncols];
    	}
    	error=fabs(A[col+row*Ncols]-sum);
        if (error>tolerance) {
          pass=0;
          break;
        }
      }
    }

    if (pass) {
      printf("test passes for %dx%d\n",Nrows,Ncols);
      order[profile_idx]             = Nrows;
      QRD_cycles[profile_idx]        = (double)QRD_t;
      profile_idx++;
      fprintf(fid,"%d %e\n",Nrows,(double)QRD_t);
    } else {
      printf("decomposition test failed for test %d for %dx%d\n",Nrows,Ncols);
      break;
    }
  } /* for (Nrows=3;Nrows<=194;Nrows++) */
  fclose(fid);

  if (pass) {
    /* generate approximating polynomial coefficients for QRD */
    degree_QRD=3;
    gen_polynomial_coefficients(profile_idx,degree_QRD+1,order,QRD_cycles,V,z,poly_coef_QRD);
    printf("\n");
    printf("QRD cycles        = ");
    for (n=0;n<=degree_QRD;n++) {
	  if (n==0)               printf("%7.1f*order^%d",poly_coef_QRD[n],degree_QRD-n);
	  else if (n==(degree_QRD-1)) printf("%+8.1f*order",poly_coef_QRD[n]);
	  else if (n==degree_QRD)     printf("%+8.1f",poly_coef_QRD[n]);
	  else                    printf("%+7.1f*order^%d",poly_coef_QRD[n],degree_QRD-n);
    }
    printf("\n");

    /* generate approximating polynomial outputs */
    fid=fopen("polyout.dat","w");
    for (Nrows=3;Nrows<=194;Nrows++) {

	  y_QRD=poly_coef_QRD[1]+poly_coef_QRD[0]*Nrows;
	  for (n=2;n<=degree_QRD;n++) y_QRD=poly_coef_QRD[n]+y_QRD*Nrows;

	  fprintf(fid,"%2d %e\n",Nrows,y_QRD);
    }
    fclose(fid);
  }
}

int gen_polynomial_coefficients(const unsigned short Nrows,const unsigned short Ncols,
           unsigned short *order,double *cycles,double *V,double *y,double *poly_coef) 
{

  int row,col;
  double x,prod;

  /* generate Vandermond matrix */
  for (row=0;row<Nrows;row++) {
	x=(double)order[row];
	prod=1.0;
	for (col=Ncols-1;col>=0;col--) {
	  V[col+row*Ncols]=prod;
	  prod*=x;
	}
  }

  /* QR decomposition */
  DSPF_dp_qrd(Nrows,Ncols,V,Q,R,u);

  /* calculate polynomial coefficients */
  DSPF_dp_qrd_solver(Nrows,Ncols,Q,R,cycles,y,poly_coef);

  return 0;
}
/* ======================================================================= */
/*  End of file:  DSPF_dp_qrd_example.c                                    */
/* ------------------------------------------------------------------------*/
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */

