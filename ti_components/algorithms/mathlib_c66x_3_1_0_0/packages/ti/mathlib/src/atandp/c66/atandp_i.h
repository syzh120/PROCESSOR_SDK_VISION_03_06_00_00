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
/* atandp_i.h - double precision floating point arctangent                 */
/*              optimized inlined C Implementation (w/ Intrinsics)         */
/* ======================================================================= */

#ifndef ATANDP_I_H_
#define ATANDP_I_H_ 1

#include <ti/mathlib/src/common/common.h>

#ifdef __cplusplus
#pragma CODE_SECTION(".text:optci")
#else
#pragma CODE_SECTION(divdpMod_atandpi, ".text:optci");
#endif

/* Pull in inline for divdp */
static inline double divdpMod_atandpi (double a, double b) {
  cmn_DIVDP (a,b);
}

#ifdef __cplusplus
#pragma CODE_SECTION(".text:optci")
#else
#pragma CODE_SECTION(sqrtdp_atandp_i, ".text:optci");
#endif
/* =========================================================================== */
/* The sqrtsp function returns the square root of a real floating-point value  */
/* =========================================================================== */

static inline double sqrtdp_atandp_i (double x)
{
  const double  half  =  0.5;
  const double  OneP5 =  1.5;
  double  y, y0, y1, y2, y3;

  y0 = _rsqrdp (x);                            /* y0 = 1/sqrt(x) */
  y1 = y0     * (OneP5 - (x*y0*y0*half));
  y2 = y1     * (OneP5 - (x*y1*y1*half));
  y3 = y2     * (OneP5 - (x*y2*y2*half));
  y = x * y3 * (OneP5 - (x*y3*y3*half));

  if (x <= 0.0) {
    y = 0.0;
  }

  return (y);
} /* sqrtdp_atandp_i */

#ifdef __cplusplus
#pragma CODE_SECTION(".text:optci")
#else
#pragma CODE_SECTION(pol_est_asindp_i, ".text:optci");
#endif

/* =========================================================================== */
/* Polynomial calculation to estimate the arc_sine funtion.                    */
/* The polynomial used is as follows:                                          */
/*   pol = x + c2 x^3 + c4 x^5 + c6 x^7 + c8 x^9 + c10 x^11 + c12 x^13 +       */
/*          c14 x^15 + c16 x^17,                                               */
/* where x is the input, c2 through c16 are the corresponding coefficients     */
/* to the polynomial, and pol is the result of the polynomial. This            */
/* polynomial only covers inputs in the range [0, 0.5].                        */
/* =========================================================================== */

//zz: pol_est_asindp_i has been defined in asindp_i.h
//    thus change the following function to be extern
extern double pol_est_asindp_i (double x);
/*
static inline double pol_est_asindp_i (double x)
{
  //Coefficients for the polynomial
  const double  c16 =  0.0128845102309331;
  const double  c14 =  0.0147126002168748;
  const double  c12 =  0.0176088429536748;
  const double  c10 =  0.0222431541581371;
  const double  c8  =  0.0304014411191328;
  const double  c6  =  0.0446390358862595;
  const double  c4  =  0.0750005487345893;
  const double  c2  =  0.166666642109919;
  double x2, x4, x6, x8, x10, x12;
  double pol, tmp1, tmp2;

  //calculate powers of x
  x2  = x*x;
  x4  = x2*x2;
  x6  = x2*x4;
  x8  = x4*x4;
  x10 = x6*x4;
  x12 = x8*x4;

  // =========================================================================
  // The polynomial calculation is done in two seperate parts.
  //   tmp1 =  c2 x^2 + c4 x^4 + c6 x^6 + c8 x^8
  //   tmp2 =  c10 x^10 + c12 x^12 + c14 x^14 + c16 x^16
  // In order to reduce the number of multiplications x is factored out of
  // the polynomial and multiplied by later.
  // =========================================================================

  tmp1 = ((c8 * x8) + (c6 * x6)) + ((c4 * x4) + (c2 * x2));
  tmp2 = (((c16 * x4 + c14 * x2) + c12) * x12) + (c10 * x10);


  pol = tmp1  + tmp2;
  pol = pol*x + x;

  return pol;
} // pol_est_asindp_i
*/


#ifdef __cplusplus
#pragma CODE_SECTION(".text:optci")
#else
#pragma CODE_SECTION(atandp_i, ".text:optci");
#endif

/* Pull in inline for atandp */
static inline double atandp_i (double a)
{
  double  MIN   =  1.490116119384e-8; 
  double  p0    = -1.3688768894191926929e+1; 
  double  p1    = -2.0505855195861651981e+1; 
  double  p2    = -8.4946240351320683534e+0; 
  double  p3    = -8.3758299368150059274e-1; 
  double  q0    =  4.1066306682575781263e+1; 
  double  q1    =  8.6157349597130242515e+1; 
  double  q2    =  5.9578436142597344465e+1; 
  double  q3    =  1.5024001160028576121e+1; 
  double  sqrt3 =  1.7320508075688772935e+0; 
  double  iims3 =  2.6794919243112270647e-1; 
  double  F, G, H, R, RN, RD;                 
  int     N, Sign;                            
                                              
  Sign = 0;                                   
  F    = a;                                   
  N    = 0;                                   
                                              
  if (F < 0.0) {                              
    F    = -F;                                
    Sign = 1;                                 
  }                                           
                                              
  if (F > 1.0) {                              
    F = divdpMod_atandpi (1,F);                           
    N = 2;                                    
  }                                           
                                              
  if (F > iims3) {                            
    N = N + 1;                                
    F = divdpMod_atandpi ((F * sqrt3 - 1.0),(F + sqrt3)); 
  }                                           
                                              
  H = F;                                      
                                              
  if (H < 0.0) {                              
    H = -H;                                   
  }                                           
                                              
  if (H > MIN) {                              
    G  = H * H;                               
    RN = (((p3*G + p2)*G + p1)*G + p0)*G;     
    RD = (((G + q3)*G + q2)*G + q1)*G + q0;   
    R  = divdpMod_atandpi (RN,RD);                        
    F  = (F + F*R);                           
  }                                           
                                              
  if (N > 1) {                                
    F = -F;                                   
  }                                           
                                              
  H = F + V[N];                               
                                              
  if (Sign == 1) {                            
    H = -H;                                   
  }                                           
                                              
  return (H);                                 
}

#endif /* ATANDP_I_H_ */

/* ======================================================================== */
/*  End of file: atandp_i.h                                                 */
/* ======================================================================== */
