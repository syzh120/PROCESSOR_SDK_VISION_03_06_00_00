/* ======================================================================= */
/* DSPF_dp_svd_cn.c -- singular value decomposition                        */
/*                 Natural C Implementation                                */
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
/*    Redistributions in binary form must reproduce the above copyright    */
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
/* ======================================================================= */\
#include <math.h>
#include <string.h>

#include "DSPF_dp_svd_cn.h"

static int DSPF_dp_convert_to_bidiag_cn(const int Nrows,const int Ncols,double *U,double *V,double *diag,double *superdiag);
static int DSPF_dp_bidiag_to_diag_cn(const int Nrows,const int Ncols,double *U,double *V,double *diag,double *superdiag);
static int DSPF_dp_sort_singular_values_cn(const int Nrows,const int Ncols,double *U,double *V,double *singular_values);


int DSPF_dp_svd_cn(const int Nrows,const int Ncols,double *A,double *U,double *V,double *U1,double *diag,double *superdiag)
{
  int status,row,col,Nrows1,Ncols1;

  /* ------------------------------------------------------------------- */
  /* copy A matrix to U                                                  */
  /* ------------------------------------------------------------------- */
  if (Nrows>=Ncols) {
	Nrows1=Nrows;
	Ncols1=Ncols;
    memcpy(U,A,sizeof(double)*Nrows*Ncols);
  } else {
	/* transpose matrix */
	for (row=0;row<Nrows;row++) {
      for (col=0;col<Ncols;col++) {
    	U[row+col*Nrows]=A[col+row*Ncols];
      }
	}
	Nrows1=Ncols;
	Ncols1=Nrows;
  }

  /* ------------------------------------------------------------------- */
  /* convert A to bidiagonal matrix using Householder reflections        */
  /* ------------------------------------------------------------------- */
  DSPF_dp_convert_to_bidiag_cn(Nrows1,Ncols1,U,V,diag,superdiag);

  /* ------------------------------------------------------------------- */
  /* convert bidiagonal to diagonal using Givens rotations               */
  /* ------------------------------------------------------------------- */
  status=DSPF_dp_bidiag_to_diag_cn(Nrows1,Ncols1,U,V,diag,superdiag);

  /* ------------------------------------------------------------------- */
  /* sort singular values in descending order                            */
  /* ------------------------------------------------------------------- */
  DSPF_dp_sort_singular_values_cn(Nrows1,Ncols1,U,V,diag);

  /* ------------------------------------------------------------------- */
  /* switch U and V                                                      */
  /* ------------------------------------------------------------------- */
  if (Ncols>Nrows) {
#ifndef ENABLE_REDUCED_FORM_CN
	memcpy(U1,V,sizeof(double)*Nrows*Nrows);
	memcpy(V,U,sizeof(double)*Ncols*Ncols);
	memcpy(U,U1,sizeof(double)*Nrows*Nrows);
#else
	memcpy(U1,V,sizeof(double)*Ncols*Ncols);
	memcpy(V,U,sizeof(double)*Nrows*Ncols);
	memcpy(U,U1,sizeof(double)*Nrows*Ncols);
#endif
  }

  return status;
}

int DSPF_dp_convert_to_bidiag_cn(const int Nrows,const int Ncols,double *U,double *V,double *diag,double *superdiag)
{
  int i,j,k;
  double s,s2,si,scale,half_norm_squared;

  /* Householder processing */
  s=0;
  scale=0;
  for (i=0;i<Ncols;i++) {
	superdiag[i]=scale*s;
	/* process columns */
	scale=0;
	for (j=i;j<Nrows;j++) {
	  scale+=fabs(U[i+j*Ncols]);
	}
	if (scale>0) {
	  s2=0;
	  for (j=i;j<Nrows;j++) {
		U[i+j*Ncols]=U[i+j*Ncols]/scale;
		s2+=U[i+j*Ncols]*U[i+j*Ncols];
	  }
	  if (U[i+i*Ncols]<0) {
		s=sqrt(s2);
	  } else {
		s=-sqrt(s2);
	  }
	  half_norm_squared=U[i+i*Ncols]*s-s2;
	  U[i+i*Ncols]-=s;
	  for (j=i+1;j<Ncols;j++) {
		si=0;
		for (k=i;k<Nrows;k++) {
		  si+=U[i+k*Ncols]*U[j+k*Ncols];
		}
		si=si/half_norm_squared;
		for (k=i;k<Nrows;k++) {
		  U[j+k*Ncols]+=si*U[i+k*Ncols];
		}
	  }
	} /* if (scale>0) */
	for (j=i;j<Nrows;j++) {
	  U[i+j*Ncols]*=scale;
	}
	diag[i]=s*scale;
	/* process rows */
    s=0;
    scale=0;
    if ((i<Nrows)&&(i!=Ncols-1)) {
      for (j=i+1;j<Ncols;j++) {
    	scale+=fabs(U[j+i*Ncols]);
      }
      if (scale>0) {
        s2=0;
        for (j=i+1;j<Ncols;j++) {
          U[j+i*Ncols]=U[j+i*Ncols]/scale;
          s2+=U[j+i*Ncols]*U[j+i*Ncols];
        }
        j--;
        if (U[j+i*Ncols]<0) {
          s=sqrt(s2);
        } else {
          s=-sqrt(s2);
        }
        half_norm_squared=U[i+1+i*Ncols]*s-s2;
        U[i+1+i*Ncols]-=s;
        for (k=i+1;k<Ncols;k++) {
          superdiag[k]=U[k+i*Ncols]/half_norm_squared;
        }
        if (i<Nrows-1) {
          for (j=i+1;j<Nrows;j++) {
        	si=0;
        	for (k=i+1;k<Ncols;k++) {
        	  si+=U[k+i*Ncols]*U[k+j*Ncols];
        	}
        	for (k=i+1;k<Ncols;k++) {
        	  U[k+j*Ncols]+=si*superdiag[k];
        	}
          }
        }
      }	/* if (scale>0) */
      for (k=i+1;k<Ncols;k++) {
    	U[k+i*Ncols]*=scale;
      }
    } /* if ((i<Nrows)&&(i!=Ncols-1)) */
  } /* for (i=0;i<Ncols;i++) */

  /* update V */
  V[Ncols*Ncols-1]=1;
  s=superdiag[Ncols-1];
  for (i=Ncols-2;i>=0;i--) {
	if (s!=0) {
	  for (j=i+1;j<Ncols;j++) {
		V[i+j*Ncols]=U[j+i*Ncols]/(U[i+1+i*Ncols]*s);
	  }
	  for (j=i+1;j<Ncols;j++) {
	    si=0;
	    for (k=i+1;k<Ncols;k++) {
	      si+=U[k+i*Ncols]*V[j+k*Ncols];
	    }
	    for (k=i+1;k<Ncols;k++) {
	      V[j+k*Ncols]+=si*V[i+k*Ncols];
	    }
	  }
	} /* if (s!=0) */
	for (j=i+1;j<Ncols;j++) {
	  V[j+i*Ncols]=0;
	  V[i+j*Ncols]=0;
	}
	V[i+i*Ncols]=1;
	s=superdiag[i];
  } /* for (i=Ncols-2;i>=0;i--) */

#ifndef ENABLE_REDUCED_FORM_CN
  /* expand U to from Nrows x Ncols to */
  /*                  Nrows x Nrows    */
  if (Nrows>Ncols) {
	for (i=Nrows-1;i>=0;i--) {
	  for (j=Nrows-1;j>=0;j--) {
		 if (j<=Ncols-1) {
		   U[j+i*Nrows]=U[j+i*Ncols];
		 } else {
			 U[j+i*Nrows]=0;
		 }
	  }
	}
  }

  /* update U */
  for (i=Ncols-1;i>=0;i--) {
	s=diag[i];
	for (j=i+1;j<Ncols;j++) {
	  U[j+i*Nrows]=0;
	}
    if (s!=0) {
      for (j=i+1;j<Nrows;j++) {
    	si=0;
    	for (k=i+1;k<Nrows;k++) {
    	  si+=U[i+k*Nrows]*U[j+k*Nrows];
    	}
    	si=si/(U[i+i*Nrows]*s);
    	for (k=i;k<Nrows;k++) {
    	  U[j+k*Nrows]+=si*U[i+k*Nrows];
    	}
      }
      /* initial U1 */
      if (i==Ncols-1) {
    	for (j=i;j<Nrows;j++) {
    	  for (k=Nrows-1;k>=i+1;k--) {
    	    U[k+j*Nrows]=U[i+j*Nrows]*U[i+k*Nrows]/(U[i+i*Nrows]*s);
    	    if (j==k) {
    	      U[k+j*Nrows]+=1;
    	    }
    	  }
    	}
      }
      for (j=i;j<Nrows;j++) {
    	U[i+j*Nrows]=U[i+j*Nrows]/s;
      }
    } else { /* if (s!=0) */
      if (i==Ncols-1) {
    	for (k=1;k<=Nrows-Ncols;k++) {
    	  U[i+k+(i+k)*Nrows]=1;
    	}
      }
      for (j=i;j<Nrows;j++) {
    	U[i+j*Nrows]=0;
      }
    } /* if (s!=0) */
    U[i+i*Nrows]+=1;
  } /* for (i=Ncols-1;i>=0;i--) */
#else
  /* update U */
  for (i=Ncols-1;i>=0;i--) {
	s=diag[i];
	for (j=i+1;j<Ncols;j++) {
	  U[j+i*Ncols]=0;
	}
    if (s!=0) {
      for (j=i+1;j<Ncols;j++) {
    	si=0;
    	for (k=i+1;k<Nrows;k++) {
    	  si+=U[i+k*Ncols]*U[j+k*Ncols];
    	}
    	si=si/(U[i+i*Ncols]*s);
    	for (k=i;k<Nrows;k++) {
    	  U[j+k*Ncols]+=si*U[i+k*Ncols];
    	}
      }
       for (j=i;j<Nrows;j++) {
    	U[i+j*Ncols]=U[i+j*Ncols]/s;
      }
    } else { /* if (s!=0) */
      for (j=i;j<Nrows;j++) {
    	U[i+j*Ncols]=0;
      }
    } /* if (s!=0) */
    U[i+i*Ncols]+=1;
  } /* for (i=Ncols-1;i>=0;i--) */
#endif

  return 0;
}

int DSPF_dp_bidiag_to_diag_cn(const int Nrows,const int Ncols,double *U,double *V,double *diag,double *superdiag)
{

  int row,i,k,m,rotation_test,iter,total_iter;
  double x,y,z,epsilon;
  double c,s,f,g,h;

  iter=0;
  total_iter=0;
  /* ------------------------------------------------------------------- */
  /* find max in col                                                     */
  /* ------------------------------------------------------------------- */
  x=0;
  for (i=0;i<Ncols;i++) {
	y=fabs(diag[i])+fabs(superdiag[i]);
	if (x<y) {
	  x=y;
	}
  }
  epsilon=DBL_EPSILON*x;
  for (k=Ncols-1;k>=0;k--) {
	  total_iter+=iter;
      iter=0;
	  while (1==1) {
      rotation_test=1;
      for (m=k;m>=0;m--) {
    	if (fabs(superdiag[m])<=epsilon) {
    	  rotation_test=0;
    	  break;
    	}
    	if (fabs(diag[m-1])<=epsilon) {
    	  break;
    	}
      } /* for (m=k;m>=0;m--) */
      if (rotation_test) {
    	c=0;
    	s=1;
    	for (i=m;i<=k;i++) {
    	  f=s*superdiag[i];
    	  superdiag[i]=c*superdiag[i];
    	  if (fabs(f)<=epsilon) {
    		break;
    	  }
    	  g=diag[i];
    	  h=sqrt(f*f+g*g);
    	  diag[i]=h;
    	  c=g/h;
    	  s=-f/h;
#ifndef ENABLE_REDUCED_FORM_CN
    	  for (row=0;row<Nrows;row++) {
    		y=U[m-1+row*Nrows];
    		z=U[i+row*Nrows];
    		U[m-1+row*Nrows]= y*c+z*s;
    		U[i+row*Nrows]  =-y*s+z*c;
    	  }
#else
    	  for (row=0;row<Nrows;row++) {
    		y=U[m-1+row*Ncols];
    		z=U[i+row*Ncols];
    		U[m-1+row*Ncols]= y*c+z*s;
    		U[i+row*Ncols]  =-y*s+z*c;
    	  }
#endif
     	} /* for (i=m;i<=k;i++) */
      } /* if (rotation_test) */
      z=diag[k];
      if (m==k) {
    	if (z<0) {
    	  diag[k]=-z;
    	  for (row=0;row<Ncols;row++) {
    		V[k+row*Ncols]=-V[k+row*Ncols];
    	  }
    	} /* if (z>0) */
    	break;
      } else { /* if (m==k) */
        if (iter>=MAX_ITERATION_COUNT) {
          return -1;
        }
        iter++;
    	x=diag[m];
    	y=diag[k-1];
    	g=superdiag[k-1];
    	h=superdiag[k];
    	f=((y-z)*(y+z)+(g-h)*(g+h))/(2*h*y);
    	g=sqrt(f*f+1);
    	if (f<0) {
    	  g=-g;
    	}
    	f=((x-z)*(x+z)+h*(y/(f+g)-h))/x;
    	/* next QR transformation */
    	c=1;
    	s=1;
    	for (i=m+1;i<=k;i++) {
    	  g=superdiag[i];
    	  y=diag[i];
    	  h=s*g;
    	  g=g*c;
    	  z=sqrt(f*f+h*h);
    	  superdiag[i-1]=z;
    	  c=f/z;
    	  s=h/z;
    	  f= x*c+g*s;
    	  g=-x*s+g*c;
    	  h=y*s;
    	  y=c*y;
    	  for (row=0;row<Ncols;row++) {
    		x=V[i-1+row*Ncols];
    		z=V[i+row*Ncols];
    		V[i-1+row*Ncols]= x*c+z*s;
    		V[i+row*Ncols]  =-x*s+z*c;
    	  }
    	  z=sqrt(f*f+h*h);
    	  diag[i-1]=z;
    	  if (z!=0) {
    		c=f/z;
    		s=h/z;
    	  }
    	  f= c*g+s*y;
    	  x=-s*g+c*y;
#ifndef ENABLE_REDUCED_FORM_CN
    	  for (row=0;row<Nrows;row++) {
    		y=U[i-1+row*Nrows];
    		z=U[i+row*Nrows];
    		U[i-1+row*Nrows]= c*y+s*z;
    		U[i+row*Nrows]  =-s*y+c*z;
    	  }
#else
    	  for (row=0;row<Nrows;row++) {
    		y=U[i-1+row*Ncols];
    		z=U[i+row*Ncols];
    		U[i-1+row*Ncols]= c*y+s*z;
    		U[i+row*Ncols]  =-s*y+c*z;
    	  }
#endif
    	} /* for (i=m+1;i<=k;i++) */
    	superdiag[m]=0;
    	superdiag[k]=f;
    	diag[k]=x;
      } /* if (m==k) */
    } /* while (1==1) */
  } /* for (k=Ncols-1:k>=0;k--) */

  return total_iter;
}

int DSPF_dp_sort_singular_values_cn(const int Nrows,const int Ncols,double *U,double *V,double *singular_values)
{
  int i,j,row,max_index;
  double temp;

  for (i=0;i<Ncols-1;i++) {
	max_index=i;
	for (j=i+1;j<Ncols;j++) {
	  if (singular_values[j]>singular_values[max_index]) {
		max_index=j;
	  }
	}
	if (max_index!=i) {
      temp=singular_values[i];
      singular_values[i]=singular_values[max_index];
      singular_values[max_index]=temp;
#ifndef ENABLE_REDUCED_FORM_CN
	  for (row=0;row<Nrows;row++) {
		temp=U[max_index+row*Nrows];
		U[max_index+row*Nrows]=U[i+row*Nrows];
		U[i+row*Nrows]=temp;
	  }
#else
	  for (row=0;row<Nrows;row++) {
		temp=U[max_index+row*Ncols];
		U[max_index+row*Ncols]=U[i+row*Ncols];
		U[i+row*Ncols]=temp;
	  }
#endif
	  for (row=0;row<Ncols;row++) {
		temp=V[max_index+row*Ncols];
		V[max_index+row*Ncols]=V[i+row*Ncols];
		V[i+row*Ncols]=temp;
	  }
	}
  }

  return 0;
}


/* ======================================================================= */
/*  End of file:  DSPF_dp_svd_cn.c                                         */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
