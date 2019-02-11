/*******************************************************************************
 **+--------------------------------------------------------------------------+**
 **|                            ****                                          |**
 **|                            ****                                          |**
 **|                            ******o***                                    |**
 **|                      ********_///_****                                   |**
 **|                      ***** /_//_/ ****                                   |**
 **|                       ** ** (__/ ****                                    |**
 **|                           *********                                      |**
 **|                            ****                                          |**
 **|                            ***                                           |**
 **|                                                                          |**
 **|         Copyright (c) 2007-2015 Texas Instruments Incorporated           |**
 **|                        ALL RIGHTS RESERVED                               |**
 **|                                                                          |**
 **| Permission to use, copy, modify, or distribute this software,            |**
 **| whether in part or in whole, for any purpose is forbidden without        |**
 **| a signed licensing agreement and NDA from Texas Instruments              |**
 **| Incorporated (TI).                                                       |**
 **|                                                                          |**
 **| TI makes no representation or warranties with respect to the             |**
 **| performance of this computer program, and specifically disclaims         |**
 **| any responsibility for any damages, special or consequential,            |**
 **| connected with the use of this program.                                  |**
 **|                                                                          |**
 **+--------------------------------------------------------------------------+**
 *******************************************************************************/
#include "../common/VLIB_memory.h"
#include "VLIB_simplex_3D_idat.h"

#define MAX_S32_S 2147483648
#define MAX_20p11 1048576
#define MAX_14p17 16384
#define MAX_4p27 16

/* Argument struct required for rosenbrock32 cost function */
typedef struct argsStruct {
    int32_t n;
    int32_t coeff;
} argsStruct;

/* Cost Function to minimize */
static int32_t rosenbrock32(int16_t *x, const void *k)
{
    int16_t       x2, temp;
    int32_t       temp2, temp3, temp4, mx, mx2, i;
    argsStruct   *K = (argsStruct *)k;

    temp4 = 0;

    for( i=0; i < K->n - 1; i++ ) {

        x2 = (int16_t)((x[i] * x[i]) >> 13);  /* S2.13 * S2.13 = SS4.26 >> 13 */
        temp = x[i + 1] - x2;

        temp2 = (temp * temp) << 1;     /* S2.13 * S2.13 = SS4.26 << 1 = S4.27 */
        temp3 = (int32_t)(K->coeff * temp2);
        mx = 8192 - x[i];
        mx2 = (int32_t)((mx * mx) << 1);

        temp4 += (temp3 + mx2);
    }

    return (temp4);
}

static int16_t       staticStart[]        =  { -10240, 10000, 10240 }; /* S2.13 */
static int16_t       staticStep[]         =  { 1024, 1024, 1024 };
static int16_t       staticrefMinPoint[]  =  { 8197, 8199, 8204 };
static argsStruct    rosenAddtlArgs[]  =  { 3, 10 };

static simplex_3D_testParams_t    testParams[]=
{
    /********************************************
        {
            (*func)(int16_t a[], const void *b),
            *start,
            *init_step,
             MaxIteration,
             EPSILON,
            *addtlArgs,
            *refMinPoint,
             refMinValue
        },
    *********************************************/
    {
        STATIC,
        rosenbrock32,
        staticStart,
        staticStep,
        200,
        0.00001 * MAX_S32_S / MAX_4p27,
        rosenAddtlArgs,
        staticrefMinPoint,
        408
    },
    {
        STATIC,
        rosenbrock32,
        staticStart,
        staticStep,
        200,
        0.001 * MAX_S32_S / MAX_4p27,
        rosenAddtlArgs,
        NULL,
        0
    },
    {
        STATIC,
        rosenbrock32,
        staticStart,
        staticStep,
        40,
        0.00001 * MAX_S32_S / MAX_4p27,
        rosenAddtlArgs,
        NULL,
        0
    },
};

/*
 *  Sends the test parameter structure and number of tests
 */
void simplex_3D_getTestParams(simplex_3D_testParams_t * *params, int32_t *numTests)
{
    *params = testParams;
    *numTests = sizeof(testParams) / sizeof(simplex_3D_testParams_t);
}

