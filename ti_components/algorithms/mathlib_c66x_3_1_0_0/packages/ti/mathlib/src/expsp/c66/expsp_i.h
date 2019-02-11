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
/* expsp_i.h - Single precision floating point exp                         */
/*              optimized inlined C Implementation (w/ Intrinsics)         */
/* ======================================================================= */

#ifndef EXPSP_I_H_
#define EXPSP_I_H_ 1

#include <ti/mathlib/src/common/common.h>
#include <c6x.h>

#ifdef __cplusplus
#pragma CODE_SECTION(".text:optci")
#else
#pragma CODE_SECTION(expsp_i, ".text:optci");
#endif

/* ======================================================================= */
/* This function returns the exponential value of a real floating-point    */
/* argument. The return value is e^x.                                      */
/* ======================================================================= */

static inline float expsp_i (float x)
{
  const float log2_base_x16 =  23.083120654;  /*1.442695041 * 16*/
  const float half         =   0.5f;
  const float LnMin        =  -87.33654475f;
  const float LnMax        =   88.72283905f;
  const float Max          =   3.402823466E+38;
  const double p           =   0.0433216987816623;  /* 1/log2_base_x16 */

  /* coefficients to approximate the decimal part of the result */
  const float c0           =   0.166668549286041f;
  const float c1           =   0.500016170012920f;
  const float c2           =   0.999999998618401f;

  float pol, r, r2, r3,res;
  unsigned int Ttemp;
  int          J, K, N ;
  double       dT;

  /* Get N such that |N - x*16/ln(2)| is minimized */
  N = (int) (x * log2_base_x16 + half);
  if ((x * log2_base_x16) < - half) {
    N--;
  }

  /* Argument reduction, r, and polynomial approximation pol(r) */
  r  = (float) ((double)x - p * (double)N) ;
  r2 = r * r;
  r3 = r * r2;

  pol = (r * c2) + ((r3 * c0) + (r2 * c1));
  
  /* Get index for ktable and jtable */
  K  = _extu (N, 28, 30);
  J  = N & 0x3;
  dT = kTable[K] * jTable[J];

  /* Scale exponent to adjust for 2^M */
  Ttemp =  _hi(dT) + (unsigned int) ((N >> 4) << 20);
  dT    = _itod(Ttemp, _lo(dT));

  res = ((float)dT) * (1.0f + pol);

  /* < LnMin returns 0 */
  if (x < LnMin) {
    res = 0.0;
  }

  /* > LnMax returns MAX */
  if (x > LnMax) {
    res = Max;
  }

  return(res);
}

#endif /* EXPSP_I_H_ */

/* ======================================================================== */
/*  End of file: expsp_i.h                                                  */
/* ======================================================================== */

