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
/* atandp_vec.c - double precision floating point cosine optimized         */
/*                inlined C implementation (w/ intrinsics) vector version  */
/* ======================================================================= */

#include "atandp.h"
#include "atandp_i.h"

#ifdef __cplusplus
#pragma DATA_SECTION(".text:optvec")
#else
#pragma CODE_SECTION(atandp_v, ".text:optvec");
#endif

void atandp_v (double * restrict a, double * restrict output, int size)
{
	int i;

const double rsqr2    =  7.071067811865475244008e-1;  /* 1/sqrt(2) */
const double sqr3div2 =  8.660254037844386467637e-1;  /* sqrt(3)/2 */
const double pi2      =  1.570796326794896619231e+0;   /* pi/2 */
const double pi4      =  7.853981633974483096157e-1;  /* pi/4 */
const double half     =  0.5;
const double max      =  6.0e+11;
double res, x, x_abs, x2, in, temp, temp1, temp2, temp3;
double sign, in1, in2, in3, in4, pol;
double res1, res2, res3, res4, res5;
double cond1, cond2, cond3, cond4;

/* Vector loop */
for (i = 0; i < size; i++) {
  x = a[i];

  temp = x*x;
  temp += 1.0;
  temp = sqrtdp_atandp_i(temp);
  x = divdpMod_atandpi (x,temp);
  sign = 1.0;
  x_abs = _fabs(x);

  if(x < 0){
    sign = -sign;                             /* sign var */
  }

   x2 = x*x;
  /* Conditions used to determine the range of the value x */
  cond1 = (x_abs > sqr3div2);
  cond2 = (x_abs < half);
  cond3 = (x_abs > rsqr2);
  cond4 = (x_abs > max);
  /* Calculate all possible values for the input of the polynomial */
  in1 = x_abs;
  in2 = 1 - 2 * x2;
  in3 = -in2;
  in4 = sqrtdp_atandp_i(1 - x2);

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
  res5 = 1.570796326794897;

  /* Set the result to the correct value */
  temp1 = (cond1) * res4 + (!cond1) * res3;
  temp2 = (cond2) * res1 + (!cond2) * res2;
  temp3 = (cond3) * temp1 + (!cond3) * temp2;
  res = (cond4) * res5 + (!cond4) * temp3;

  output[i] = res * sign;        /* restore sign for quadrant 3 & 4*/

}
}

/* ======================================================================== */
/*  End of file: atandp_vec.c                                                */
/* ======================================================================== */
