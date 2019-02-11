/* ======================================================================== *
 * MATHLIB -- TI Floating-Point Math Function Library                       *
 *                                                                          *
 *                                                                          *
 * Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/   *
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

/* ======================================================================= */
/* asindp_v.c - Double precision floating point arc_sine                   */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* ======================================================================= */

#include "asindp.h"
#include "asindp_i.h"


#ifdef __cplusplus
#pragma CODE_SECTION(".text:optvec")
#else
#pragma CODE_SECTION(asindp_v, ".text:optvec");
#endif

/* =========================================================================== */
/* The type of calculation for asin(x) depends on the value of x:              */
/*   x_abs <= 0.5,               res = pol_est_asindp_i (input x)              */
/*                                                                             */
/*   1 > x_abs > sqrt(3)/2,      res = pi/2 - pol_est_asindp_i (input a)       */
/*                                 a = sqrt(1 - x^2)                           */
/*                                                                             */
/*   sqrt(3)/2 =>x_abs> 1/sqrt(2), res = pi/4 +(1/2)*pol_est_asindp_i (input a)*/
/*                                   a = 2x^2 - 1                              */
/*                                                                             */
/*   1/sqrt(2) => x_abs > 0.5,   res = 1/2 (pi/2 - pol_est_asindp_i (input a)  */
/*                                 a = 1 - 2x^2                                */
/* where x_abs is the absolute value of the input, a is defined for each       */
/* interval as shown above and it's used as an input for the polynomial, and   */
/* res is the value for asin(x). This is repeated for every value in the array.*/
/* =========================================================================== */

void asindp_v (double* restrict a, double* restrict output, int size)
{
  const double rsqr2    =  0.70710678118654752440;  /* 1/sqrt(2) */
  const double sqr3div2 =  0.86602540378443864876;  /* sqrt(3)/2 */
  const double pi2      =  1.5707963267948966192;   /* pi/2 */
  const double pi4      =  0.78539816339744830962;  /* pi/4 */
  const double half     =  0.5;
  double res, x, x_abs, x2, in, temp1, temp2;
  double sign, in1, in2, in3, in4, pol;
  double res1, res2, res3, res4;
  int i, cond1, cond2, cond3;

  /* Vector loop */
  for (i = 0; i < size; i++) {
    x = a[i];
    sign = 1.0;
    x_abs = _fabs(x);

    if(x < 0){
      sign = -sign;                             /* sign var */
    }

    /* Conditions used to determine the range of the value x */
    cond1 = (x_abs > sqr3div2);
    cond2 = (x_abs < half);
    cond3 = (x_abs > rsqr2);

    x2 = x * x;

    /* Calculate all possible values for the input of the polynomial */
    in1 = x_abs;
    in2 = 1 - 2 * x2;
    in3 = 2 * x2 - 1;
    in4 = sqrtdp_asindp_i(1 - x2);

    temp1 = (cond1) * in4 + (!cond1) * in3;
    temp2 = (cond2) * in1 + (!cond2) * in2;
    /* Select final result for the input of the polynomial */
    in = (cond3) * temp1 + (!cond3) * temp2;

    pol = pol_est_asindp_i(in);

    /* Calculate all possible values for the result */
    res1 = pol;
    res2 = half * (pi2 - pol);;
    res3 = pi4 + half * pol;
    res4 = pi2 - pol;

    /* Set the result to the correct value */
    temp1 = (cond1) * res4 + (!cond1) * res3;
    temp2 = (cond2) * res1 + (!cond2) * res2;
    res = (cond3) * temp1 + (!cond3) * temp2;

    output[i] = res * sign;        /* restore sign for quadrant 3 & 4*/
    }
}

/* ======================================================================== */
/*  End of file: asindp_v.c                                                 */
/* ======================================================================== */
