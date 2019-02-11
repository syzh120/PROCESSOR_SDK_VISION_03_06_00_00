/*
*
* Copyright (c) 2009-2017 Texas Instruments Incorporated
*
* All rights reserved not granted herein.
*
* Limited License.
*
* Texas Instruments Incorporated grants a world-wide, royalty-free, non-exclusive
* license under copyrights and patents it now or hereafter owns or controls to make,
* have made, use, import, offer to sell and sell ("Utilize") this software subject to the
* terms herein.  With respect to the foregoing patent license, such license is granted
* solely to the extent that any such patent is necessary to Utilize the software alone.
* The patent license shall not apply to any combinations which include this software,
* other than combinations with devices manufactured by or for TI ("TI Devices").
* No hardware patent is licensed hereunder.
*
* Redistributions must preserve existing copyright notices and reproduce this license
* (including the above copyright notice and the disclaimer and (if applicable) source
* code license limitations below) in the documentation and/or other materials provided
* with the distribution
*
* Redistribution and use in binary form, without modification, are permitted provided
* that the following conditions are met:
*
* *       No reverse engineering, decompilation, or disassembly of this software is
* permitted with respect to any software provided in binary form.
*
* *       any redistribution and use are licensed by TI for use only with TI Devices.
*
* *       Nothing shall obligate TI to provide you with source code for the software
* licensed and provided to you in object code.
*
* If software source code is provided to you, modification and redistribution of the
* source code are permitted provided that the following conditions are met:
*
* *       any redistribution and use of the source code, including any resulting derivative
* works, are licensed by TI for use only with TI Devices.
*
* *       any redistribution and use of any object code compiled from the source code
* and any resulting derivative works, are licensed by TI for use only with TI Devices.
*
* Neither the name of Texas Instruments Incorporated nor the names of its suppliers
*
* may be used to endorse or promote products derived from this software without
* specific prior written permission.
*
* DISCLAIMER.
*
* THIS SOFTWARE IS PROVIDED BY TI AND TI'S LICENSORS "AS IS" AND ANY EXPRESS
* OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
* OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
* IN NO EVENT SHALL TI AND TI'S LICENSORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
* DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
* OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
* OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
* OF THE POSSIBILITY OF SUCH DAMAGE.
*
*/


/* ======================================================================== */
/*  TEXAS INSTRUMENTS, INC.                                                 */
/*                                                                          */
/*  NAME                                                                    */
/*      curve_fitting.c                                                     */
/*                                                                          */
/*  DESCRIPTION:                                                            */
/*  This file helps to calculate performance estimation formula for kernels */
/*                                                                          */
/*==========================================================================*/

/* Profiling includes */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "eve_profile.h"

/* Pointers for file-scoped static matrices and vectors */
static int     *AA[CF_PROFILE_MAX_TESTS];
static float   *xx;
static int     *bb;

/* Private file-scoped static variables for mode control */
static int      finalModeFlag;
static int      current_mode_order;

/* Profiling globals */
int         est_order; /* Order for the pseudo-inverse (2/3) */
int         est_count; /* Number of tests used in estimating formula */

extern volatile uint64_t test_module_cyles;

/****************************************************************************
*  Local Function: IMG_CHOLESKY_DECOMP
*
*  void img_cholesky_decomp
*  (
*      double **U,   - Pointer to upper triangular portion of symmetric
*                      positive definite matrix A'A
*      double **L,   - Pointer to lower triangular matrix L that satisfies
*                      A'A = LL'
*      short sz      - A'A and L matrix size (square)
*  )
*
*  Description:
*
****************************************************************************/
static void vlib_cholesky_decomp (double * *U, double * *L, short sz)
{
  double    sum;
  short     i, j, k;

  /* Solve for L using LL' = U */
  for( i=0; i < sz; i++ ) {
    for( j=i; j < sz; j++ ) {
      sum = U[i][j];

      for( k=i - 1; k >= 0; k-- ) {
        sum -= L[i][k] * L[j][k];
      }

      if( i == j ) {
        L[i][i] = sqrt(sum);
      } else {
        L[j][i] = sum / L[i][i];
      }
    }
  }
}

/* Profiling initialization routine */
void CF_profile_init (int order, char *kernel_name)
{
  short    i;


  /* Allocate A matrix */
  for( i=0; i < CF_PROFILE_MAX_TESTS; i++ ) {
    AA[i] = (int *) malloc(order * sizeof(int));
  }

  /* Initialize mode static variables */
  current_mode_order = order;
  finalModeFlag = 1;

  /* Allocate b/x vectors */
  bb = (int *)   malloc(CF_PROFILE_MAX_TESTS * sizeof(int));
  xx = (float *) malloc(order * sizeof(float));


  /* Clear cycle counts */
  test_module_cyles = (uint64_t) 0;

  /* Initialize profiling globals */
  est_order = order;
  est_count = 0;


  printf("\n");
  printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
  printf("\nTEST_REPORT_KERNEL_NAME : %s\n", kernel_name);
  printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
  printf("\n");
}

#define MAX_LINELEN  60
#define MAX_NUMLINES 3

/* Profiling add calculation */
void CF_formula_add_test (int Ax0, int Ax1, int Ax2, int Ax3, int errorFlag, char *desc, int mode)
{

  uint16_t    index, maxIndex;
  char       *descString;
  char       *curStr;
  char       *line[MAX_NUMLINES + 1];
  char       emptyString[20]="";

  index= 1;

  if( desc == NULL ) {
    descString= emptyString;
    line[0]= descString;
  } else {
    descString= desc;
    /* Code below is to break up a long description string into multiple lines
    * so everything fits nicely in the display.
    * The algorithm looks for last space before the line exceeeds
    * MAX_LINELEN characters to determine end of each line
    */
    curStr= descString;
    line[0]= descString;
    index= 1;

    while((strlen(curStr) > MAX_LINELEN) && (index < MAX_NUMLINES)) {
      curStr+= MAX_LINELEN;

      while( *curStr != ' ' && curStr != descString ) {
        curStr--;
      }

      if( curStr != descString ) {
        line[index++]= curStr;
      } else {
        line[index++]= descString + strlen(descString);
      }
      curStr++;
    }
  }

  maxIndex= index;
  line[index]= descString + strlen(descString);

  index= 0;

  *(line[index + 1])= 0; /* we set the end of line to '0' */

  if( index != maxIndex - 1 ) {
    *(line[index + 1])= ' '; /* we set back the end of line to ' ' if not last line */
  }
  index++;
  line[index]++; /* advance pointer line[index] by 1 to skip the 0 */

  while( index != maxIndex ) {
    *(line[index + 1])= 0;
    printf("|    |        |         |              |                 |        |                  | %s\n", line[index]);
    if( index != maxIndex - 1 ) {
      *(line[index + 1])= ' ';
    }
    index++;
    line[index]++; /* advance pointer line[index] by 1 to skip the 0 */
  }


  // Display order-2 parameters and measurements always
  printf("N: %5d,  ", Ax0);
  // Order-3 parameter
  if( est_order > 2 ) {
    printf("M: %5d,  ", Ax1);
  }
  // Order-4 parameter
  if( est_order > 3 ) {
    printf("L: %5d,  ", Ax2);
  }
  // Order-5 parameter
  if( est_order > 4 ) {
    printf("K: %5d,  ", Ax3);
  }

  // Display measurements always
  printf("CYC: %6lld\n\n", (long long)test_module_cyles);  



  /* Add test case to matrix and vectors for cycle formula estimation */


  /* Fill in all measurements (even if NULL) */
  AA[est_count][0] = Ax0;

  if( est_order > 2 ) 
  {
    AA[est_count][1] = Ax1;
    if( est_order > 3 ) 
    {
      AA[est_count][2] = Ax2;
      if( est_order > 4 ) 
      {
        AA[est_count][3] = Ax3;
      }
    }
  }

  /* Provide a 1 for the last one (constant overhead) */
  AA[est_count][est_order - 1] = 1;

  /* Add cycles to measurement vector */
  bb[est_count] = test_module_cyles;

  est_count += 1;

  /* Clear cycle counts for next test */
  test_module_cyles = (uint64_t) 0;
}


/****************************************************************************
*  Local Function: VLIB_CHOLESKY_BACKSUB
*
*  void img_cholesky_backsub
*  (
*      double **L,   - Pointer to lower triangular solution from
*                      img_cholesky_decomp().
*      double  *b,   - Pointer to vector from equation A'Ax = b
*      float   *x,   - Pointer to solution vector (output)
*      short   sz    - Lengths of b and x, square size of L
*  )
*
*  Description: Displays the estimated cycle formula
*
****************************************************************************/
static void vlib_cholesky_backsub (double * *L, double *b, float *x, short sz)
{
  double    z[CF_PROFILE_MAX_ORDER];
  double    sum;
  short     i, k;

  /* Back-sub:  Lz = y to solve for z  (where z = L'x) */
  for( i=0; i < sz; i++ ) {
    sum = b[i];

    for( k=i - 1; k >= 0; k-- ) {
      sum -= L[i][k] * (double) z[k];
    }

    z[i] = sum / L[i][i];
  }

  /* Back-sub:  L'x = z to solve for x  */
  for( i=sz - 1; i >= 0; i-- ) {
    sum = z[i];

    for( k=i + 1; k < sz; k++ ) {
      sum -= L[k][i] * x[k];
    }

    x[i] = (float) (sum / L[i][i]);
  }
}

/****************************************************************************
*  Function: VLIB_PRINT_FORMULA
*
*  void VLIB_print_formula
*  (
*      float *x      - Solution to cycle formula
*  )
*
*  Description: Displays the estimated cycle formula
*
****************************************************************************/
static void VLIB_print_formula (float *x, int order)
{
  float    C = x[1];

  /* Print start of cycle formula string */
  printf("  Cycles:  ");

  /* Provide profiling information for x[0] and multiplier (N) */
  printf("%f", x[0]);
  printf("*N ");

  /* If third/fourth order, provide 2nd variable output */
  if( order > 2 ) {
    /* Provide profiling information for x[1] and multiplier (M) */
    if(x[1] >= 0)
    {
      printf("+ %f", x[1]);
    }
    else
    {
      x[1] = -x[1];
      printf("- %f", x[1]);  
    }
    printf("*M ");
    /* Change the constant (overhead) cycles */
    C = x[2];
  }

  /* If fourth order, provide 3rd variable output */
  if( order > 3 ) {
    /* Provide profiling information for x[2] and multiplier (L) */
    if(x[2] >= 0)
    {
      printf("+ %f", x[2]);
    }
    else
    {
      x[2] = -x[2];
      printf("- %f", x[2]);  
    }
    printf("*L ");
    /* Change the constant (overhead) cycles */
    C = x[3];
  }

  if( order > 4 ) {
    /* Provide profiling information for x[2] and multiplier (L) */
    if(x[3] >= 0)
    {
      printf("+ %f", x[3]);
    }
    else
    {
      x[3] = -x[3];
      printf("- %f", x[3]);  
    }
    printf("*K ");
    /* Change the constant (overhead) cycles */
    C = x[4];
  }

  /* Provide remainder of formula */
  if( C < 0 ) {
    C = -C;
    printf("- ");
  } else {
    printf("+ ");
  }
  printf("%d\n", (int) C);
}

/****************************************************************************
*  Function: VLIB_PSEUDO_INVERSE
*
*  void VLIB_pseudo_inverse
*  (
*      int   **A,  - Matrix of parameters for each test performed.  Each
*                    row of the matrix holds all parameters for a single test.
*                    This includes a 1 for cycle overhead.
*      int   *b,   - Vector of cycle counts for each test case.  Holds one
*                    value per test applied towards formula estimation.
*      float *x,   - Returned (linear) equation values.  There will as many
*                    values as the order of the estimation.
*      short  m,   - Number of test cases (length of b, columns in A)
*      short  n,   - Order of inverse (rows in A')
*  )
*
*  Description: Finds the solution to an overdetermined set of linear
*               equations with N unknowns (currently maximum of 4). It is assumed
*               that the equations are of the form:
*
*                  b[i] = a[i][0]*x[0] + a[i][1]*x[1] + ... + x[N-1]
*
*               The best fit may be found using the Moore-Penrose pseudo-inverse.
*               Since A'A is positive-definite, we employ Cholesky decomposition
*               and back substitution for the matrix inverse.
*
*               The approach follows:
*
*                       Ax   = b       (where A is MxN with M>=N over-determined)
*
*                       A'Ax = A'b
*
*                       Mx   = y       (where M = A'A and y = A'b)
*
*                       LL'x = y       (Cholesky for LL' decomposition)
*
*                       Lz   = y       (where z = L'x)
*
*                    Solve for "z" using back substitution
*
*                       L'x  = z
*
*                    Solve for "x" using back substitution (again)
*
****************************************************************************/
static void VLIB_pseudo_inverse (int * *A, int *b, float *x, short m, short n)
{
  double   *U [CF_PROFILE_MAX_ORDER];
  double   *L [CF_PROFILE_MAX_ORDER];
  double    y [CF_PROFILE_MAX_ORDER];
  double    sum;
  short     i, j, k;


  /* Allocate U & L matrices */
  for( i=0; i < n; i++ ) {
    U[i] = (double *) malloc(n * sizeof(double));
    L[i] = (double *) malloc(n * sizeof(double));
  }


  /* Create A'A = U (symmetric, upper-triangular only) */
  for( i=0; i < n; i++ ) {
    for( j=i; j < n; j++ ) {
      //sum = (VLIB_D64) 0.0;
      sum = 0.0;

      for( k=0; k < m; k++ ) {
        sum += (double) A[k][i] * (double) A[k][j];
      }

      U[i][j] = sum;
    }
  }



  /* Use Cholesky decomposition to get L */
  vlib_cholesky_decomp(U, L, n);

  /* Create A'b = y for Cholesky solution */
  for( i=0; i < n; i++ ) {
    sum = (double) 0;

    for( j=0; j < m; j++ ) {
      sum += (double) A[j][i] * b[j];
    }

    y[i] = sum;
  }


  /* Use L,L' to solve for x */
  vlib_cholesky_backsub(L, y, x, n);

  /* Free U & L matrices */
  for( i=0; i < n; i++ ) {
    free(U[i]);
    free(L[i]);
  }

  /* Round overhead to integer */
  x[n - 1] = (float) ((int) (x[n - 1] + 0.5));
}

/* Profiling mode initialization routine */
void CF_profile_setMode(int mode_order, int finalMode)
{
  current_mode_order = mode_order;
  finalModeFlag = finalMode;
}

/* Estimate cycle formula using Moore-Penrose pseudo-inverse */
void CF_profile_cycle_report (int reportType, char *formulaInfo)
{
  short    i;
  int      count = est_count;
  int     *AAmode[CF_PROFILE_MAX_TESTS];
  int     *bbmode;
  char    *spacer = (char *)"";

  printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");

  for( i=0; i < CF_PROFILE_MAX_TESTS; i++ ) {
    AAmode[i] = AA[i];
  }
  bbmode = bb;

  printf("%sTest vectors run: %d\n", spacer, count);
  printf("\nTEST_REPORT_PERF_FORMULA : \n");

  if((reportType == CF_PROFILE_FORMULA) || (reportType == CF_PROFILE_FORMULA_RANGE)) {
    printf("%sFormula:\n%s", spacer, spacer);
    if( count >= current_mode_order ) {
      /* Solve overdetermined set of equations for x */
      VLIB_pseudo_inverse(AAmode, bbmode, xx, count, current_mode_order);


      /* Provide cycle formula */
      VLIB_print_formula(xx, current_mode_order);
      if( formulaInfo ) {
        printf("%s  Where:   %s\n", spacer, formulaInfo);
      }
    } else {
      printf("%s  Equation could not be determined.\n", spacer);
    }
  }

  if((reportType == CF_PROFILE_RANGE) || (reportType == CF_PROFILE_FORMULA_RANGE)) {
    float   *compute_cycles = (float   *)malloc(CF_PROFILE_MAX_TESTS * sizeof(float));
    float    minRange = 9000000000;
    float    maxRange = 0;
    float    avgRange, medRange;
    float    sum = 0;

    for( i=0; i < count; i++ ) {
      compute_cycles[i] = (float) bbmode[i];
      minRange = (compute_cycles[i] < minRange) ? compute_cycles[i] : minRange;
      maxRange = (compute_cycles[i] > maxRange) ? compute_cycles[i] : maxRange;
      sum += compute_cycles[i];
    }

    avgRange = sum / (float)i;

    if( count > 1 ) {
      int    flag;

      do {
        flag = 0;

        for( i=1; i < count; i++ ) {
          if( compute_cycles[i - 1] > compute_cycles[i] ) {
            float    temp = compute_cycles[i];
            compute_cycles[i] = compute_cycles[i - 1];
            compute_cycles[i - 1] = temp;
            flag = 1;
          }
        }
      } while( flag == 1 );

      medRange = compute_cycles[count / 2 - 1];
    } else {
      medRange = compute_cycles[0];
    }

    free(compute_cycles);

    printf("%sRange:\n", spacer);
    printf("%s  Min: %12.2f cycles            Avg: %12.2f cycles\n", spacer, minRange, avgRange);
    printf("%s  Max: %12.2f cycles            Med: %12.2f cycles\n", spacer, maxRange, medRange);


  }

  if (finalModeFlag) {
    /* Free memory allocated in VLIB_profile_init(),
    * this can not be freed until all the modes have been printed */
    for( i=0; i < CF_PROFILE_MAX_TESTS; i++ ) {
      free(AA[i]);
    }
    free(bb);
    free(xx);
  }
}



/* =========================================================================*/
/*  End of file:  VLIB_profile.c                                             */
/* =========================================================================*/

