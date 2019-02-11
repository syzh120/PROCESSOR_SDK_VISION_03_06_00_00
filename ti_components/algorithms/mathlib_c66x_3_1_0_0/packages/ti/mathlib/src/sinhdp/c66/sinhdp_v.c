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
/* sinhdp_v.c - double precision floating point hyperbolic sine            */
/*              optimized inlined C implementation (w/ intrinsics)         */
/*              vector version                                             */
/* ======================================================================= */

#include "sinhdp.h"
#include "sinhdp_i.h"


#ifdef __cplusplus
#pragma CODE_SECTION(".text:optvec")
#else
#pragma CODE_SECTION(sinhdp_v, ".text:optvec");
#endif

/* ====================================================================== */
/* The type of calculation for sinh(x) depends on the value of x:         */
/*                                                                        */
/* for x_abs <= 1,          res = pol_est_sinhdp_i (input x)              */
/* for x_abs > 25,          res = sign * expsp_sinhdp_i (input temp),     */
/*                               temp = x_abs - log_e(2)                  */
/* for 1 < x_abs <= 25,     res = (e^x - e^-x)/2,                         */
/*                                e^x = expsp_sinhsp_i (input x)          */
/* where x_abs is the absolute value of the input, sign has a value of 1  */
/* or -1 depending on the sign of the input, and res is the value         */
/* for sinh(x). This is repeated for every value in the array.            */
/* ====================================================================== */

void sinhdp_v (double * restrict a, double * restrict output, int size)
{
  const double half   =   0.5;
  const double bound  =   25.0;
  const double ln2    =   0.693147180559945;      /*  log_e(2) */
  const double Max    =   710.475860073944;
  const double pol_bound =   1;                   /* polynomial boundary */
  double res, x, x_abs, exp, exp_in, sign, div;
  double temp1, temp2;
  int i;

  /* Vector loop */
  for (i = 0; i < size; i++) {
    x = a[i];
    sign = 1.0;

    x_abs = _fabs(x);

    if(x < 0){
        sign = -sign;                           /* sign variable */
    }

    /* set input for the exponential function */
    exp_in = x_abs;

    /* estimate sinh for |x| <= 1 */
    temp1 = pol_est_sinhdp_i(x_abs) * 2;

    /* estimate cosh for |x| > 25, e^-|x| is negligible */
    if(x_abs > bound){
      /* set the value for exp input needed for this range */
      exp_in = x_abs-ln2;
    }
    exp = expdp_sinhdp_i(exp_in);                /* e^x */
    temp2 = exp * 2;

    /* assume sinh for 1 < |x| <= 25 */

    div = divdp_sinhdp_i(1, exp);               /* e^-x */
    res = exp - div;                            /* (e^x - e^-x)/2 */

    /* set the result to the right answer */
    if(x_abs <= pol_bound){                     /* |x| <= 1 */
      res = temp1;
    }
    if(x_abs > bound){                          /* |x| > 25 */
      res= temp2;
    }

    res = res * half;

    if (x_abs > Max) {                          /* reached max */
      res =  _lltod(0x7FF0000000000000);
    }

    output[i] = res * sign;
  }
}

/* ======================================================================== */
/*  End of file: sinhdp_v.c                                                 */
/* ======================================================================== */
