/* ======================================================================== *
 *                                                                          *
 * Copyright (C) 2007 - 2017 Texas Instruments Incorporated                 *
 *                   http://www.ti.com/                                     *
 *                                                                          *
 *                                                                          *
 *  Redistribution and use in source and binary forms, with or without      *
 *  modification, are permitted provided that the following conditions      *
 *  are met:                                                                *
 *                                                                          *
 *    Redistributions of source code must retain the above copyright        *
 *    notice, this list of conditions and the following disclaimer.         *
 *                                                                          *
 *    Redistributions in binary form must reproduce the above copyright     *
 *    notice, this list of conditions and the following disclaimer in the   *
 *    documentation and/or other materials provided with the                *
 *    distribution.                                                         *
 *                                                                          *
 *    Neither the name of Texas Instruments Incorporated nor the names of   *
 *    its contributors may be used to endorse or promote products derived   *
 *    from this software without specific prior written permission.         *
 *                                                                          *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS     *
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT       *
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR   *
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT    *
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,   *
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT        *
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,   *
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY   *
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT     *
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE   *
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.    *
 * ======================================================================== */

/* Profiling includes */
#include "TI_profile.h"
#include "TI_memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static uint16_t    testId;

/* Handle COFF/ELF for linker cmd file symbols */
#if defined(__TI_EABI__)
#define _STACK_SIZE __TI_STACK_SIZE
#endif

/* Stack size global extern variables */
extern uint32_t    _STACK_SIZE;
extern uint32_t    _stack;

/* Stack size static variables */
static uint32_t    stackSize[TI_PROFILE_KERNEL_CNT]; /* Stack size for C-natural and optimized */
static uint32_t    maxStackSize[TI_PROFILE_KERNEL_CNT]; /* Max stack sizes for C-natural and optimized */
#if !defined(_HOST_BUILD) && !defined(DISABLE_STACK_PROFILING)
static uint32_t    oldSP, newSP;
static uint32_t   *topStack = &_stack;
#endif

/* Pointers for file-scoped static matrices and vectors */
static int     *AA[TI_PROFILE_MAX_TESTS];
static float   *xx;
static int     *bb;

/* Private file-scoped static variables for mode control */
static int     mode_num[TI_PROFILE_MAX_TESTS];
static int     modeFlag;
static int     finalModeFlag;
static int     current_mode_num;
static int     current_mode_order;
static char   *current_mode_desc;

/* Profiling globals */
int         est_order; /* Order for the pseudo-inverse (2/3) */
int         est_count; /* Number of tests used in estimating formula */
int         est_test= 0; /* Use current test in formula estimation */
uint64_t    beg_count; /* Begin cycle count for profiling */
uint64_t    end_count; /* End cycle count for profiling */
uint64_t    overhead;  /* Cycle profiling overhead */
uint64_t    cycles[TI_PROFILE_KERNEL_CNT]; /* Cycle counts for C-natural and optimized */


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
static void ti_cholesky_decomp (double * *U, double * *L, short sz)
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
                TI_test_assert(sum > 0, "Matrix A'A is not positive-definite\n");
                L[i][i] = sqrt(sum);
            } else {
                L[j][i] = sum / L[i][i];
            }
        }
    }
}

/* Profiling initialization routine */
void TI_profile_init (int order, char *kernel_name)
{
    short    i;

    PROFILE_INIT;

    /* Ensure the order is valid */
    TI_test_assert(order <= TI_PROFILE_MAX_ORDER, "Cycle formula estimation order too large");
    TI_test_assert(order > 1, "Cycle formula estimation order too small");

    /* Allocate A matrix */
    for( i=0; i < TI_PROFILE_MAX_TESTS; i++ ) {
        AA[i] = (int *) malloc(order * sizeof(int));
        mode_num[i] = 0;
    }

    /* Initialize mode static variables */
    modeFlag = 0;
    current_mode_num = 0;
    current_mode_order = order;
    finalModeFlag = 1;

    /* Allocate b/x vectors */
    bb = (int *)   malloc(TI_PROFILE_MAX_TESTS * sizeof(int));
    xx = (float *) malloc(order * sizeof(float));

    /* Compute the overhead of calling clock twice to get timing info. */
    beg_count = PROFILE_READ;
    end_count = PROFILE_READ;
    overhead  = end_count - beg_count;

    /* Clear cycle counts */
    cycles[TI_PROFILE_KERNEL_OPT] = (uint64_t) 0;
    cycles[TI_PROFILE_KERNEL_CN] = (uint64_t) 0;
    cycles[TI_PROFILE_KERNEL_INIT] = (uint64_t) 0;

    /* Clear stack sizes */
    stackSize[TI_PROFILE_KERNEL_OPT] = (uint32_t) 0;
    stackSize[TI_PROFILE_KERNEL_CN] = (uint32_t) 0;
    stackSize[TI_PROFILE_KERNEL_INIT] = (uint32_t) 0;
    maxStackSize[TI_PROFILE_KERNEL_OPT] = (uint32_t) 0;
    maxStackSize[TI_PROFILE_KERNEL_CN] = (uint32_t) 0;
    maxStackSize[TI_PROFILE_KERNEL_INIT] = (uint32_t) 0;

    /* Initialize profiling globals */
    est_order = order;
    est_count = 0;

    testId= 0;

    /* Informational message */
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("               %s testing starts.\n", kernel_name);
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| No | Status | Num pt  | Kernel Init     | Kernel Compute  | NatC Compute    | Description\n");
    printf("|    |        |         |  cyc            |  cyc/pt         |  cyc/pt         |            \n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");
}

#define MAX_LINELEN  60
#define MAX_NUMLINES 3

/* Profiling add calculation */
void TI_profile_formula_add_test (int Ax0, int Ax1, int Ax2, int errorFlag, char *desc, int mode)
{

    uint16_t    index, maxIndex;
    float       compute_cycles;
    char       *descString;
    char       *curStr;
    char       *line[MAX_NUMLINES + 1];
    char       *emptyString="";

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

    if( !errorFlag ) {
        printf("|%3d | PASS", testId++);
    } else {
        printf("|%3d | FAIL", testId++);
    }

    *(line[index + 1])= 0; /* we set the end of line to '0' */
    compute_cycles= (float)cycles[TI_PROFILE_KERNEL_OPT] / Ax0;
    /* For now io cycles is 0 */
    printf("   | %7d |    %12.2f |    %12.5f |    %12.2f |", Ax0, (float) cycles[TI_PROFILE_KERNEL_INIT], compute_cycles, (float)cycles[TI_PROFILE_KERNEL_CN] / Ax0);
    printf(" %s\n", line[0]);
    if( index != maxIndex - 1 ) {
        *(line[index + 1])= ' '; /* we set back the end of line to ' ' if not last line */
    }
    index++;
    line[index]++; /* advance pointer line[index] by 1 to skip the 0 */

    while( index != maxIndex ) {
        *(line[index + 1])= 0;
        printf("|    |        |         |                 |                 |                 | %s\n", line[index]);
        if( index != maxIndex - 1 ) {
            *(line[index + 1])= ' ';
        }
        index++;
        line[index]++; /* advance pointer line[index] by 1 to skip the 0 */
    }

#if 0
    /* Display order-2 parameters and measurements always */
    printf("Test %2d    N: %5d,  ", test_index, Ax0);
    /* Order-3 parameter */
    if( est_order > 2 ) {
        printf("M: %5d,  ", Ax1);
    }
    /* Order-4 parameter */
    if( est_order > 3 ) {
        printf("L: %5d,  ", Ax2);
    }
    /* Display measurements always */
    printf("OPT: %6d,  CN: %6d", cycles[TI_PROFILE_KERNEL_OPT], cycles[TI_PROFILE_KERNEL_CN]);
#endif


    /* Add test case to matrix and vectors for cycle formula estimation */
    if( est_test ) {
        mode_num[est_count] = mode - 1;

        /* Fill in all measurements (even if NULL) */
        AA[est_count][0] = Ax0;

        if( est_order > 2 ) {
            AA[est_count][1] = Ax1;
            if( est_order > 3 ) {
                AA[est_count][2] = Ax2;
            }
        }

        /* Provide a 1 for the last one (constant overhead) */
        AA[est_count][est_order - 1] = 1;

        /* Add cycles to measurement vector */
        bb[est_count] = cycles[TI_PROFILE_KERNEL_OPT];

        est_count += 1;
    }

    if( stackSize[TI_PROFILE_KERNEL_OPT] > maxStackSize[TI_PROFILE_KERNEL_OPT] ) {
        maxStackSize[TI_PROFILE_KERNEL_OPT] = stackSize[TI_PROFILE_KERNEL_OPT];
    }
    if( stackSize[TI_PROFILE_KERNEL_CN] > maxStackSize[TI_PROFILE_KERNEL_CN] ) {
        maxStackSize[TI_PROFILE_KERNEL_CN] = stackSize[TI_PROFILE_KERNEL_CN];
    }

    /* Clear cycle counts for next test */
    cycles[TI_PROFILE_KERNEL_OPT] = (uint64_t) 0;
    cycles[TI_PROFILE_KERNEL_CN] = (uint64_t) 0;
    cycles[TI_PROFILE_KERNEL_INIT] = (uint64_t) 0;

    /* Clear stack sizes */
    stackSize[TI_PROFILE_KERNEL_OPT] = (uint32_t) 0;
    stackSize[TI_PROFILE_KERNEL_CN] = (uint32_t) 0;
    stackSize[TI_PROFILE_KERNEL_INIT] = (uint32_t) 0;

    /*printf("\n");*/
}

/* Profiling skip message */
void TI_profile_skip_test (char *desc)
{
    uint16_t    index, maxIndex;
    char       *descString;
    char       *curStr;
    char       *line[MAX_NUMLINES + 1];
    char       *emptyString="";
    uint32_t    heapSize;

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
    heapSize = TI_get_heap_size();
    printf("|%3d | Test vector data buffers do not fit in L2RAM heap (%6d bytes) test skipped |", testId++, heapSize);
    printf(" %s\n", line[0]);
    if( index != maxIndex - 1 ) {
        *(line[index + 1])= ' '; /* we set back the end of line to ' ' if not last line */
    }
    index++;
    line[index]++; /* advance pointer line[index] by 1 to skip the 0 */

    while( index != maxIndex ) {
        *(line[index + 1])= 0;
        printf("|    |                                                                               | %s\n", line[index]);
        if( index != maxIndex - 1 ) {
            *(line[index + 1])= ' ';
        }
        index++;
        line[index]++; /* advance pointer line[index] by 1 to skip the 0 */
    }
}

/****************************************************************************
 *  Local Function: ti_CHOLESKY_BACKSUB
 *
 *  void ti_cholesky_backsub
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
static void ti_cholesky_backsub (double * *L, double *b, float *x, short sz)
{
    double    z[TI_PROFILE_MAX_ORDER];
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
 *  Function: TI_PROFILE_PRINT_FORMULA
 *
 *  void TI_profile_print_formula
 *  (
 *      float *x      - Solution to cycle formula
 *  )
 *
 *  Description: Displays the estimated cycle formula
 *
 ****************************************************************************/
static void TI_profile_print_formula (float *x, int order)
{
    float    C = x[1];

    /* Print start of cycle formula string */
    printf("  Cycles:  ");

    /* Provide profiling information for x[0] and multiplier (N) */
    TI_test_print_float(x[0], 0);
    printf("*N ");

    /* If third/fourth order, provide 2nd variable output */
    if( order > 2 ) {
        /* Provide profiling information for x[1] and multiplier (M) */
        TI_test_print_float(x[1], 1);
        printf("*M ");
        /* Change the constant (overhead) cycles */
        C = x[2];
    }

    /* If fourth order, provide 3rd variable output */
    if( order > 3 ) {
        /* Provide profiling information for x[2] and multiplier (L) */
        TI_test_print_float(x[2], 1);
        printf("*L ");
        /* Change the constant (overhead) cycles */
        C = x[3];
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
 *  Function: ti_PSEUDO_INVERSE
 *
 *  void ti_pseudo_inverse
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
static void ti_pseudo_inverse (int * *A, int *b, float *x, short m, short n)
{
    double   *U [TI_PROFILE_MAX_ORDER];
    double   *L [TI_PROFILE_MAX_ORDER];
    double    y [TI_PROFILE_MAX_ORDER];
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
            sum = (double) 0.0;

            for( k=0; k < m; k++ ) {
                sum += (double) A[k][i] * (double) A[k][j];
            }

            U[i][j] = sum;
        }
    }

    /* Use Cholesky decomposition to get L */
    ti_cholesky_decomp(U, L, n);

    /* Create A'b = y for Cholesky solution */
    for( i=0; i < n; i++ ) {
        sum = (double) 0;

        for( j=0; j < m; j++ ) {
            sum += (double) A[j][i] * b[j];
        }

        y[i] = sum;
    }

    /* Use L,L' to solve for x */
    ti_cholesky_backsub(L, y, x, n);

    /* Free U & L matrices */
    for( i=0; i < n; i++ ) {
        free(U[i]);
        free(L[i]);
    }

    /* Round overhead to integer */
    x[n - 1] = (float) ((int) (x[n - 1] + 0.5));
}

/* Profiling mode initialization routine */
void TI_profile_setMode(int mode, int mode_order, char *mode_desc, int finalMode)
{
    current_mode_num = mode - 1;
    current_mode_order = mode_order;
    current_mode_desc = mode_desc;
    finalModeFlag = finalMode;
    modeFlag = 1;
}

/* Estimate cycle formula using Moore-Penrose pseudo-inverse */
void TI_profile_cycle_report (int reportType, char *formulaInfo, char *rangeInfo)
{
    short    i, k;
    int      count = est_count;
    int     *AAmode[TI_PROFILE_MAX_TESTS];
    int     *bbmode;
    char    *spacer = "";

    printf("---------------------------------------------------------------------------------------------------------------------------------------------\n");

    if( modeFlag ) {
        printf("Mode %d: %s\n", current_mode_num + 1, current_mode_desc);
        spacer = "  ";

        /* Allocate AAmode matrix */
        for( i=0; i < TI_PROFILE_MAX_TESTS; i++ ) {
            AAmode[i] = (int *) malloc(current_mode_order * sizeof(int));
        }

        /* Allocate bbmode vectors */
        bbmode = (int *)   malloc(TI_PROFILE_MAX_TESTS * sizeof(int));

        count = 0;

        for( i=0; i < est_count; i++ ) {
            if( mode_num[i] == current_mode_num ) {
                for( k=0; k < current_mode_order - 1; k++ ) {
                    AAmode[count][k] = AA[i][k];
                }

                AAmode[count][k] = 1;
                bbmode[count] = bb[i];
                count++;
            }
        }
    } else {
        for( i=0; i < TI_PROFILE_MAX_TESTS; i++ ) {
            AAmode[i] = AA[i];
        }

        bbmode = bb;
    }

    printf("%sTest vectors run: %d\n", spacer, count);

    if((reportType == TI_PROFILE_FORMULA) || (reportType == TI_PROFILE_FORMULA_RANGE)) {
        printf("%sFormula:\n%s", spacer, spacer);
        if( count >= current_mode_order ) {
            /* Solve overdetermined set of equations for x */
            ti_pseudo_inverse(AAmode, bbmode, xx, count, current_mode_order);

            /* Provide cycle formula */
            TI_profile_print_formula(xx, current_mode_order);
            if( formulaInfo ) {
                printf("%s  Where:   %s\n", spacer, formulaInfo);
            }
        } else {
            printf("%s  Equation could not be determined.\n", spacer);
        }
    }
    if((reportType == TI_PROFILE_RANGE) || (reportType == TI_PROFILE_FORMULA_RANGE)) {
        float   *compute_cycles = (float *)malloc(TI_PROFILE_MAX_TESTS * sizeof(float));
        float    minRange = 9000000000;
        float    maxRange = 0;
        float    avgRange, medRange;
        float    sum = 0;

        for( i=0; i < count; i++ ) {
            compute_cycles[i] = (float)bbmode[i] / (float)AAmode[i][0];
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
        printf("%s  Min: %12.2f cycles/pt            Avg: %12.2f cycles/pt\n", spacer, minRange, avgRange);
        printf("%s  Max: %12.2f cycles/pt            Med: %12.2f cycles/pt\n", spacer, maxRange, medRange);

        if( rangeInfo ) {
            printf("%s  Num pt = %s\n", spacer, rangeInfo);
        }
    }

    if( modeFlag ) {
        /* Free memory allocated for mode-based calculations */
        for( i=0; i < TI_PROFILE_MAX_TESTS; i++ ) {
            free(AAmode[i]);
        }

        free(bbmode);
    }

    if( finalModeFlag ) {
        /* Free memory allocated in TI_profile_init(),
         * this can not be freed until all the modes have been printed */
        for( i=0; i < TI_PROFILE_MAX_TESTS; i++ ) {
            free(AA[i]);
        }

        free(bb);
        free(xx);
    }
}

uint32_t TI_profile_getSP(void)
{
#if !defined(_HOST_BUILD) && !defined(DISABLE_STACK_PROFILING)
    /* Must use static variable since I can't return pointer to local variable */
    static uint32_t   *pTemp = 0;

    uint32_t    iTemp; /* Local variable on stack, within 8 bytes of calling function */

    pTemp = &iTemp; /* Assign address of local variable to static location in fardata section */

    return ((uint64_t)pTemp); /* Return address of variable near top of stack */
#else
    return (0);
#endif
}

void TI_profile_initStack(uint32_t SP)
{
#if !defined(_HOST_BUILD) && !defined(DISABLE_STACK_PROFILING)
    int32_t     i;
    uint32_t    stsize;

#if defined (_TMS320C6600)
#define SP_SKIP 16
#else
#define SP_SKIP 8
#endif

    oldSP = SP;
    stsize = oldSP - (uint64_t)topStack - SP_SKIP;

    for( i=0; i < stsize / 4; i++ ) {
        topStack[i] = 0xDEADBEEF;
    }

#endif
}

void TI_profile_setStackDepth(void)
{
#if !defined(_HOST_BUILD) && !defined(DISABLE_STACK_PROFILING)
    int32_t    i;

    for( i=0; i < ((uint64_t)&_STACK_SIZE / 4); i++ ) {
        if( topStack[i] != 0xDEADBEEF ) {
            break;
        }
    }

    newSP = (i * 4) + (uint64_t)topStack;

    stackSize[act_kernel] = (oldSP - newSP);
#endif
}

/* Display stack memory reqirements */
void TI_profile_stack_memory (void)
{
#if !defined(_HOST_BUILD) && !defined(DISABLE_STACK_PROFILING)
    /* Provide memory information */
    printf("  Stack usage:  %7d bytes\n", maxStackSize[TI_PROFILE_KERNEL_OPT]);
#endif
}

/* =========================================================================*/
/*  End of file:  TI_profile.c                                             */
/* =========================================================================*/

