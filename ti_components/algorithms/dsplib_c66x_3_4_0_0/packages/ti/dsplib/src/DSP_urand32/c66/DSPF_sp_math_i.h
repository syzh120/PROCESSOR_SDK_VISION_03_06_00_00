/* ======================================================================= */
/* DSPF_sp_math_i.h -- Optimized C Implementation                            */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (C) 2013 Texas Instruments Incorporated - http://www.ti.com/  */
/*                                                                         */
/*                                                                         */
/*  Redistribution and use in source and binary forms, with or without     */
/*  modification, are permitted provided that the following conditions     */
/*  are met:                                                               */
/*                                                                         */
/*    Redistributions of source code must retain the above copyright       */
/*    notice, this list of conditions and the following disclaimer.        */
/*                                                                         */
/*    Redistributions in binary form must reproduce the above copyright    */
/*    notice, this list of conditions and the following disclaimer in the  */
/*    documentation and/or other materials provided with the               */
/*    distribution.                                                        */
/*                                                                         */
/*    Neither the name of Texas Instruments Incorporated nor the names of  */
/*    its contributors may be used to endorse or promote products derived  */
/*    from this software without specific prior written permission.        */
/*                                                                         */
/*  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS    */
/*  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT      */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR  */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT   */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,  */
/*  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT       */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,  */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY  */
/*  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE  */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.   */
/*                                                                         */
/* ======================================================================= */

#ifndef DSP_SP_MATH_I_
#define DSP_SP_MATH_I_

/*=========================================================================*/
/* Macros                                                                  */
/*=========================================================================*/

#define GENERATE_RANDOM_FLOAT(s0,s1,s2,s3,mat1,mat2,tmat)                    \
  (float)(DSP_urand32_generate_random_ti_uint32(s0,s1,s2,s3,mat1,mat2,tmat)* \
          DSPF_sp_urand_UINT_TO_FLOAT + FLT_MIN)

/*=========================================================================*/
/* Functions                                                               */
/*=========================================================================*/

/* Log table */
#pragma DATA_SECTION(logtable,".data:logTable");
double logtable[8] = {
   0.0000000000,            // 
  -0.1177830356,            // 
  -0.2231435513,            // 
  -0.3184537311,            // 
  -0.4054651081,            // 
  -0.4855078157,            // 
  -0.5596157879,            // 
  -0.6286086594             // 
};

/* kTable */
#pragma DATA_SECTION(kTable,".data:y_kTable");
double kTable[4] = {
  1.000000000,              // 2^(0/4)
  1.189207115,              // 2^(1/4)
  1.414213562,              // 2^(2/4)
  1.681792831               // 2^(3/4) 
};                          
                            
/* jTable */
#pragma DATA_SECTION(jTable,".data:jTable");
double jTable[4] = {        
  1.000000000,              // 2^(0/16) 
  1.044273782,              // 2^(1/16) 
  1.090507733,              // 2^(2/16) 
  1.138788635               // 2^(3/16)
}; 

#pragma FUNC_ALWAYS_INLINE (DSP_logsp_i);
static inline float DSP_logsp_i (float a)
{
  double  ln2  =  0.693147180559945;
  float   c1   = -0.2302894f;
  float   c2   =  0.1908169f;
  float   c3   = -0.2505905f;
  float   c4   =  0.3333164f;
  float   c5   = -0.5000002f;
  float   MAXe =  3.402823466E+38;
  float   pol, r1, r2, r3, r4, res;
  double  dr, frcpax, rcp, T;
  int     N, T_index;

  /* r = x * frcpa(x) -1 */
  rcp = _rcpdp((double) a);
  frcpax = _itod(_clr(_hi(rcp),0,16), 0);
  dr = frcpax * (double) a  - 1.0; 

  /* Polynomial p(r) that approximates ln(1+r) - r */
  r1 = (float) dr;
  r2 = r1*r1;
  r3 = r1*r2;
  r4 = r2*r2; 

  pol = c5*r2 + ((c4*r3) + ((c2*r1 + c3) + c1*r2)*r4);

  /* Reconstruction: result = T + r + p(r) */
  N       = _extu(_hi(frcpax),  1, 21) - 1023;
  T_index = _extu(_hi(frcpax), 12, 29);
  T       = logtable[T_index] - ln2 * (double) N;
  res     = (dr + T) + (pol);

  if (a <= 0) {
    res = _itof(0xFF800000);
  }
  if (a > MAXe) {
    res = 709.7827;
  }

  return (res);
} /* DSP_logsp_i */


#pragma FUNC_ALWAYS_INLINE (DSP_expsp_i);
static inline float DSP_expsp_i (float a)
{
  float log2_base_x16 =   1.442695041 * 16.0;
  float Halfe         =   0.5f;
  float LnMine        = -87.33654475;
  float LnMaxe        =  88.72283905;
  float Maxe          =   3.402823466E+38;
  float c0            =   0.1667361910f;
  float c1            =   0.4999999651f;
  float c2            =   0.9999998881f;
  float P1            =   0.04331970214844;
  float P2            =   1.99663646e-6;
  float pol, r, r2, r3, res;
  unsigned int Ttemp;
  int          J, K, N;
  double       dT;

  /* Get N such that |N - x*16/ln(2)| is minimized */
  N = (int) (a * log2_base_x16 + Halfe);
  if ((a * log2_base_x16) < -Halfe) {
    N--;
  }

  /* Argument reduction, r, and polynomial approximation pol(r) */
  r  = (a - P1 * (float) N) - P2 * (float) N;
  r2 = r * r;
  r3 = r * r2;
  
  pol = (r * c2) + ((r3 * c0) + (r2 * c1));
 
  /* Get index for ktable and jtable */
  K  = _extu (N, 28, 30);
  J  = N & 0x3;
  dT = kTable[K] * jTable[J];

  /* Scale exponent to adjust for 2^M */
  Ttemp = _hi(dT) + (unsigned int) ((N >> 4) << 20);
  dT    = _itod(Ttemp, _lo(dT));

  res = (float) (dT * (1.0f + pol));
  
  /* Early exit for small a */
  if (_extu(_ftoi(a), 1, 24) < 114) {
    res = (1.0f + a);               
  }

  /* < LnMin returns 0 */
  if (a < LnMine) {
    res = 0.0; 
  }

  /* > LnMax returns MAX */   
  if (a > LnMaxe) {
    res = Maxe;
  } 

  return(res);
} /* DSP_logsp_i */
#endif /* DSP_SP_MATH_I_ */

/* ======================================================================== */
/*  End of file:  DSPF_sp_math.h                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
