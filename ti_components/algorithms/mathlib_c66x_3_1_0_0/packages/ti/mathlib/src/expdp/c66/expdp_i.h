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
/* expdp_i.h - double precision floating point exp                         */
/*              optimized inlined C implementation (w/ intrinsics)         */
/* ======================================================================= */

#ifndef EXPDP_I_H_
#define EXPDP_I_H_ 1

#include <ti/mathlib/src/common/common.h>

#ifdef __cplusplus
#pragma CODE_SECTION(".text:optci")
#else
#pragma CODE_SECTION(divdpMod_expdp_i, ".text:optci");
#endif

/* ======================================================================= */
/* This function returns the division result of two real floating-point    */
/* values, a and b. The return value is a/b.                               */
/* ======================================================================= */

static inline double divdpMod_expdp_i (double a, double b) {
  cmn_DIVDP (a,b);
}

#ifdef __cplusplus
#pragma CODE_SECTION(".text:optci")
#else
#pragma CODE_SECTION(expdp_i, ".text:optci");
#endif

/* ======================================================================= */
/* This function returns the exponential value of a real floating-point    */
/* argument. The return value is e^x.                                      */
/* ======================================================================= */

static inline double expdp_i (double x)
{
  const double Half  =   0.5;
  const double Max   =   1.7976931348623157e+308;
  const double LnMax =   709.7827138470578;
  const double LnMin =   -708.3964185322641;
  const double a0    =   0.249999999999999993;
  const double a1    =   0.694360001511792852e-2;
  const double a2    =   0.165203300268279130e-4;
  const double b0    =   0.5;
  const double b1    =   0.555538666969001188e-1;
  const double b2    =   0.495862884905441294e-3;
  const double c1    =   0.693359375;                 /* 355/512 */
  const double c2    =  -2.1219444005469058277e-4;
  const double L2    =   1.4426950408889634074;       /* log (base 2) of e */
  double Y, Z, W, R, S, B, C, D;
  int    N, upper;

  Y = x;
  C = Y*L2;                                 /* base e --> base 2 argument */
  N = _dpint (C);                           /* get unbiased exponent as int */

  S = N;                                    /* double(int N) */
  Z = (Y - S*c1) - S*c2;                    /*  range reduction  */
  W = Z*Z;
  B = ( b2*W + b1)*W + b0;                  /* denominator  */
  D = ((a2*W + a1)*W + a0)*Z;               /* numerator */
  R = Half + divdpMod_expdp_i (D,(B - D));

  /* ======================================================================= */
  /* upper is used to calculate the exponent. 1024 produces overflow for     */
  /* large numbers, 1022 corrects overflow and it is adjusted by a factor    */
  /* of 4 later (2^2).                                                       */
  /* ======================================================================= */

  upper = 1022 + N;
  upper = _extu (upper,20,0); 
  S     = _itod (upper,0x00000000);
  C     = R*S*4;                            /* scale by power of 2 */

  /* > LnMax returns MAX  */
  if (x > LnMax) {
    C = (Max);
  }
  
  /* > LnMin returns 0 */
  if (x < LnMin) {
    C = 0.0;
  }
  
  return (C);
}

#endif /* EXPDP_I_H_ */

/* ======================================================================== */
/*  End of file: expdp_i.h                                                  */
/* ======================================================================== */

