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
/* atanhdp_v.c - Double precision floating point inverse hyperbolic tangent*/
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* ======================================================================= */

#include "atanhdp.h"
#include "atanhdp_i.h"

#ifdef __cplusplus
#pragma CODE_SECTION(".text:optvec")
#else
#pragma CODE_SECTION(atanhdp_v, ".text:optvec");
#endif

/* ======================================================================== */
/* The type of calculation for atanh(x) depends on the value of x:          */
/*   x_abs > 0.1, res =  0.5 * ln((1 + x)/(1 - x))                          */
/*                                                                          */
/*   x_abs <= 0.1, res = polynomial estimation (input x)                    */
/* where x_abs is the absolute value of the input and res is the calculated */
/* value for atanh(x)                                                       */
/*                                                                          */
/* The polynomial used is as follows:                                       */
/*   pol = x + c2 x^3 + c4 x^5 + c6 x^7                                     */
/* where x is the input, c2 through c6 are the corresponding coefficients   */
/* for the polynomial, and pol is the result of the polynomial. This is     */
/* repeated for every value in the array.                                   */
/* ======================================================================== */

void atanhdp_v (double * restrict a, double * restrict output, int size)
{
  const double pol_bound   =  0.1;
  const double half        =  0.5;
  const double limit       =  1.0;

  /* Coefficients for the polynomial */
  const double c2          =  0.333333357308678;
  const double c4          =  0.199986699941523;
  const double c6          =  0.145059552096944;

  double res, pol, temp1, temp2, div;
  double x2, x4, x6, x, x_abs, sign;
  int i, cond;

  /* Vector loop */
  for (i = 0; i < size; i++) {
    x = a[i];
    sign = 1.0;
    x_abs = _fabs(x);
    cond = (x_abs <= pol_bound);              /* |x| <= 0.1 */

    if(x < 0){
      sign = -sign;
    }

    /* powers of x */
    x2 = x * x;
    x4 = x2 * x2;
    x6 = x4 * x2;

    temp1 = 1 + x_abs;
    temp2 = 1 - x_abs;


    /* use polynomial estimation for |x| <= 0.1 */
    /* polynomial to estimate atanh(x) for small inputs */
    pol = ((x2 * c2) + (x4 * c4)) + (x6 * c6) ;
    pol = pol * x_abs + x_abs;

    /* assume |x| > 0.1 calculate atanh(x) based on 0.5*ln((1+ x) / (1- x)) */

    div = divdp_atanhdp_i(temp1,temp2);
    res = logdp_atanhdp_i(div);               /*  ln((1 + x)/(1 - x)) */
    res = res * half;                         /* divide by 2*/

    /* set the value of the result depending on the input value */
    res = (cond) * pol + (!cond) * res;

    if(x_abs > limit){
      res = _lltod(0x7FFFFFFFFFFFFFFF);         /* NaN */
    }

    if(x_abs == limit){
      res = _lltod(0x7FF0000000000000);        /* INF */
    }

    output[i] = res * sign;
  }
}

/* ======================================================================== */
/*  End of file: atanhdp_v.c                                                */
/* ======================================================================== */
