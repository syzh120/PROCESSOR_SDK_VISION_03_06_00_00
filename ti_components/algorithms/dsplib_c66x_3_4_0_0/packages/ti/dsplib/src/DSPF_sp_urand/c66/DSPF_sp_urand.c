/* ======================================================================= */
/* DSPF_sp_urand.c -- Optimized C Implementation                           */
/*                                                                         */
/* Rev 0.0.1                                                               */
/*                                                                         */
/* Copyright (c) 2011 Mutsuo Saito, Makoto Matsumoto, Hiroshima            */
/* University and The University of Tokyo. All rights reserved.            */
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

/*=========================================================================*/
/* Includes                                                                */
/*=========================================================================*/
#include "DSPF_sp_urand.h"

/*=========================================================================*/
/* User Functions                                                          */
/*=========================================================================*/

#pragma CODE_SECTION(DSPF_sp_urand,".text:optimized");
void DSPF_sp_urand(unsigned int size,     /*Size of the vector to be filled*/
                   float* vector,       /*Pointer to the destination vector*/
                   void* state)           /*State vector maintained by user*/
{
  _ti_uint32* v_state = (_ti_uint32*) state;

  /*local variables for state*/
  _ti_uint32 s0 = v_state[DSP_urand32_STATUS_0];
  _ti_uint32 s1 = v_state[DSP_urand32_STATUS_1];
  _ti_uint32 s2 = v_state[DSP_urand32_STATUS_2];
  _ti_uint32 s3 = v_state[DSP_urand32_STATUS_3];

  /*local variables for polynomial*/
  const _ti_uint32 mat1 = v_state[DSP_urand32_MAT_1];
  const _ti_uint32 mat2 = v_state[DSP_urand32_MAT_2];
  const _ti_uint32 tmat = v_state[DSP_urand32_TMAT];

  signed int i; /* Loop counter */
  for (i = 0; i < size; ++i)
  {
    vector[i] = DSP_urand32_generate_random_ti_uint32(&s0,&s1,&s2,&s3,mat1,mat2,tmat)
                 * DSPF_sp_urand_UINT_TO_FLOAT;
  }

  DSP_urand32_SAVE_STATE(s0, s1, s2, s3);
} /* DSPF_sp_urand */

/* ======================================================================== */
/*  End of file:  DSPF_sp_urand.c                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
