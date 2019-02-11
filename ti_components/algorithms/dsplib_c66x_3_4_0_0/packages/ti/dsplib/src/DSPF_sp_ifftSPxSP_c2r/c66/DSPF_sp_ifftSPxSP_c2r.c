/* ======================================================================= */
/* DSPF_sp_ifftSPxSP_c2r.c -- Inverse FFT with Mixed Radix                 */
/*                 Intrinsic C Implementation                              */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (C) 2011 Texas Instruments Incorporated - http://www.ti.com/  */ 
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

#pragma CODE_SECTION(DSPF_sp_ifftSPxSP_c2r, ".text:Intrinsic");

#include "DSPF_sp_ifftSPxSP_c2r.h"
#ifdef __TI_COMPILER_VERSION__
#include "c6x.h"
#endif

#ifdef _LITTLE_ENDIAN
void DSPF_sp_ifftSPxSP_c2r (int N, float *ptr_x, float *ptr_w, float *ptr_y,
                        unsigned char *brev, int n_min, int offset, int n_max)
{
  int   i,k;
  float *restrict tw2 = ptr_w;
  float *restrict y0, *restrict y1, t0, t1;
  __float2_t y0_i_r, y1_i_r, co_si, twid, hf_hf, mh_hf, mo_o;
  __float2_t temp1, temp2, temp3, temp4, temp5, temp6, temp7;

  hf_hf = _ftof2( 0.5, 0.5);
  mh_hf = _ftof2(-0.5, 0.5);
  mo_o  = _ftof2(-1.0, 1.0);
 
  /* split factors */
  t0 = ptr_x[0];
  t1 = ptr_x[N];
  _amem8_f2(&ptr_x[0]) = _dmpysp(_ftof2(t0-t1, t0+t1), hf_hf);
  ptr_x[N/2+1] = -ptr_x[N/2+1];

  co_si = _amem8_f2(&tw2[0]);

  y0 = ptr_x;
  y1 = ptr_x + N;

  y0_i_r = _amem8_f2(&y0[2]);
  y1_i_r = _amem8_f2(&y1[-2]);

  temp1 = _dmpysp(_daddsp(y1_i_r, y0_i_r), hf_hf);
  temp2 = _dmpysp(_dsubsp(y1_i_r, y0_i_r), mh_hf);
  temp3 = _ftof2(_hif2(temp2), _lof2(temp1));
  temp4 = _ftof2(_lof2(temp2), _hif2(temp1));
  temp5 = _complex_mpysp(temp4, co_si);
  temp6 = _daddsp(temp3, temp5);
  temp7 = _dsubsp(temp3, temp5);

  _amem8_f2(&y0[2])  = temp6;
  _amem8_f2(&y1[-2]) = _dmpysp(temp7, mo_o);

  #pragma UNROLL(2)
  for (i = 4; i < N/2; i += 2) {
      twid   = _amem8_f2(&tw2[i-2]);

      k      = -i;
      y0_i_r = _amem8_f2(&y0[i]);
      y1_i_r = _amem8_f2(&y1[k]);

      temp1  = _dmpysp(_daddsp(y1_i_r, y0_i_r), hf_hf);
      temp2  = _dmpysp(_dsubsp(y1_i_r, y0_i_r), mh_hf);
      temp3  = _ftof2(_hif2(temp2), _lof2(temp1));
      temp4  = _ftof2(_lof2(temp2), _hif2(temp1));
      temp5  = _complex_mpysp(temp4, twid);
      temp6  = _daddsp(temp3, temp5);
      temp7  = _dsubsp(temp3, temp5);

      _amem8_f2(&y0[i]) = temp6;
      _amem8_f2(&y1[k]) = _dmpysp(temp7, mo_o);
  }

  /* complex to complex IFFT */
  DSPF_sp_ifftSPxSP (N/2, ptr_x, ptr_w + N/2 - 2, ptr_y, brev, n_min, offset, N/2);
}
#else
void DSPF_sp_ifftSPxSP_c2r (int N, float *ptr_x, float *ptr_w, float *ptr_y,
                        unsigned char *brev, int n_min, int offset, int n_max)
{
  int   i,k;
  float *restrict tw2 = ptr_w;
  float *restrict y0, *restrict y1, t0, t1;
  __float2_t y0_i_r, y1_i_r, co_si, twid, hf_hf, hf_mh, o_mo;
  __float2_t temp1, temp2, temp3, temp4, temp5, temp6, temp7;

  hf_hf = _ftof2(0.5,  0.5);
  hf_mh = _ftof2(0.5, -0.5);
  o_mo  = _ftof2(1.0, -1.0);
 
  /* split factors */
  t0 = ptr_x[0];
  t1 = ptr_x[N];
  _amem8_f2(&ptr_x[0]) = _dmpysp(_ftof2(t0+t1, t0-t1), hf_hf);
  ptr_x[N/2+1] = -ptr_x[N/2+1];

  hf_hf = _ftof2(0.5,  0.5);

  co_si = _amem8_f2(&tw2[0]);

  y0 = ptr_x;
  y1 = ptr_x + N;

  y0_i_r = _amem8_f2(&y0[2]);
  y1_i_r = _amem8_f2(&y1[-2]);

  temp1 = _dmpysp(_daddsp(y1_i_r, y0_i_r), hf_hf);
  temp2 = _dmpysp(_dsubsp(y1_i_r, y0_i_r), hf_mh);
  temp3 = _ftof2(_hif2(temp1), _lof2(temp2));
  temp4 = _ftof2(_lof2(temp1), _hif2(temp2));
  temp5 = _complex_mpysp(temp4, co_si);
  temp6 = _daddsp(temp3, temp5);
  temp7 = _dsubsp(temp3, temp5);

  _amem8_f2(&y0[2])  = temp6;
  _amem8_f2(&y1[-2]) = _dmpysp(temp7, o_mo);

  #pragma UNROLL(2)
  for (i = 4; i < N/2; i += 2) {
      twid   = _amem8_f2(&tw2[i-2]);

      k      = -i;
      y0_i_r = _amem8_f2(&y0[i]);
      y1_i_r = _amem8_f2(&y1[k]);

      temp1 = _dmpysp(_daddsp(y1_i_r, y0_i_r), hf_hf);
      temp2 = _dmpysp(_dsubsp(y1_i_r, y0_i_r), hf_mh);
      temp3 = _ftof2(_hif2(temp1), _lof2(temp2));
      temp4 = _ftof2(_lof2(temp1), _hif2(temp2));
      temp5 = _complex_mpysp(temp4, twid);
      temp6 = _daddsp(temp3, temp5);
      temp7 = _dsubsp(temp3, temp5);

      _amem8_f2(&y0[i]) = temp6;
      _amem8_f2(&y1[k]) = _dmpysp(temp7, o_mo);
  }

  /* complex to complex IFFT */
  DSPF_sp_ifftSPxSP (N/2, ptr_x, ptr_w + N/2 - 2, ptr_y, brev, n_min, offset, N/2);
}
#endif
/* ======================================================================= */
/*  End of file:  DSPF_sp_ifftSPxSP_c2r.c                                  */
/* ----------------------------------------------------------------------- */
/*            Copyright (c) 2011 Texas Instruments, Incorporated.          */
/*                           All Rights Reserved.                          */
/* ======================================================================= */
