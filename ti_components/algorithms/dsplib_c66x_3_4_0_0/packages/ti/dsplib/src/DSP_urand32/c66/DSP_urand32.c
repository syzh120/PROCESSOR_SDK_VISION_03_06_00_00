/* ======================================================================= */
/* DSP_urand32.c -- Optimized C Implementation                             */
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
#include <stddef.h>
#include "DSP_urand32.h"

/*=========================================================================*/
/* Internal Constants                                                      */
/*=========================================================================*/
/*Default Polynomial Constants*/
#define DSP_urand32_DEFAULT_MAT_1  (0xd02f1a11)
#define DSP_urand32_DEFAULT_MAT_2  (0xfe80ffa)
#define DSP_urand32_DEFAULT_TMAT   (0x695afbff)

#define DSP_urand32_PRE_LOOP       (8)

/*=========================================================================*/
/* Internal Functions                                                      */
/*=========================================================================*/

/*  Function Name : DSP_urand32_period_certification
 *
 *  @Purpose : This function is used internally to ensure a period
 *  of 2^127-1. It should not be called by the user.
 *
 *  @Precondition : The calling function has passed valid state variable
 *  pointers
 *
 *  @Postcondition : The period length has been ensured and the state vector
 *  modified accordingly if the certification test fails
 *
 *  @param s0 : Pointer to the STATUS_0 variable of type @b _ti_uint32
 *  @param s1 : Pointer to the STATUS_1 variable of type @b _ti_uint32
 *  @param s2 : Pointer to the STATUS_2 variable of type @b _ti_uint32
 *  @param s3 : Pointer to the STATUS_3 variable of type @b _ti_uint32
 *
 */
#pragma CODE_SECTION(DSP_urand32_period_certification,".text:optimized");
#pragma FUNC_ALWAYS_INLINE(DSP_urand32_period_certification);
static inline void DSP_urand32_period_certification(
    _ti_uint32 *s0,         /*Status_0*/
    _ti_uint32 *s1,         /*Status_1*/
    _ti_uint32 *s2,         /*Status_2*/
    _ti_uint32 *s3)         /*Status_3*/
{
  if (!((*s0 & DSP_urand32_TINYMT_MASK) | *s1 | *s2 | *s3))
  {
    *s0 = 'T';
    *s1 = 'I';
    *s2 = 'N';
    *s3 = 'Y';
  }
} /* DSP_urand32_period_certification */

/*=========================================================================*/
/* External Functions                                                      */
/*=========================================================================*/

#pragma CODE_SECTION(DSP_urand32_init,".text:optimized");
void DSP_urand32_init(
    unsigned int seed,        /*Arbitrary number used for initialization     */
    void *restrict polynomial,/*Array of length 3 containing polynomial data */
    void *restrict state)     /*Array of length 7 allocated and uninitialized*/

{
  register int i;

  /*New pointers to take care of void pointers*/
  _ti_uint32 *v_state = (_ti_uint32*) state;
  _ti_uint32 *v_polynomial;

  /*Local Variables for status and polynomials*/
  _ti_uint32 s0, s1, s2, s3, mat1, mat2, tmat;


  /*Check if user provided polynomial values. if not, use default values*/
  if (polynomial == NULL)
  {
    mat1 = (_ti_uint32) DSP_urand32_DEFAULT_MAT_1;
    mat2 = (_ti_uint32) DSP_urand32_DEFAULT_MAT_2;
    tmat = (_ti_uint32) DSP_urand32_DEFAULT_TMAT;
  }
  else
  {
    v_polynomial = (_ti_uint32*) polynomial;
    mat1 = (_ti_uint32) v_polynomial[0];
    mat2 = (_ti_uint32) v_polynomial[1];
    tmat = (_ti_uint32) v_polynomial[2];
  }

  /*Initialize the polynomial terms*/
  v_state[DSP_urand32_MAT_1] = mat1;
  v_state[DSP_urand32_MAT_2] = mat2;
  v_state[DSP_urand32_TMAT] = tmat;

  /*Save initial states to local variables for speed*/
  s0 = (_ti_uint32) seed & 0xFFFFFFFFu;
  s1 = mat1;
  s2 = mat2;
  s3 = tmat;

  /*Shuffle States (Loop manually unrolled)*/
  s1 ^= 1 + 1812433253ul * (s0 ^ (s0 >> 30));
  s2 ^= 2 + 1812433253ul * (s1 ^ (s1 >> 30));
  s3 ^= 3 + 1812433253ul * (s2 ^ (s2 >> 30));
  s0 ^= 4 + 1812433253ul * (s3 ^ (s3 >> 30));
  s1 ^= 5 + 1812433253ul * (s0 ^ (s0 >> 30));
  s2 ^= 6 + 1812433253ul * (s1 ^ (s1 >> 30));
  s3 ^= 7 + 1812433253ul * (s2 ^ (s2 >> 30));

  /*Ensure Proper Period length*/
  DSP_urand32_period_certification(&s0, &s1, &s2, &s3);

  /*Shuffle states*/
# pragma MUST_ITERATE(DSP_urand32_PRE_LOOP,DSP_urand32_PRE_LOOP)
  for (i = 0; i < DSP_urand32_PRE_LOOP; i++)
  {
    DSP_urand32_next_state(&s0, &s1, &s2, &s3, mat1, mat2);
  }

  /*Save initialized state for first use*/
  DSP_urand32_SAVE_STATE(s0, s1, s2, s3);
} /* DSP_urand32_init */

#pragma CODE_SECTION(DSP_urand32,".text:optimized");
void DSP_urand32(unsigned int size,     /*Size of the vector to be filled*/
                 void* vector,        /*Pointer to the destination vector*/
                 void* state)           /*State vector maintained by user*/
{

  int i; /* loop counter */
    
  /*New pointers to take care of void pointers*/
  _ti_uint32 *v_state = (_ti_uint32*) state;
  _ti_uint32 *array   = (_ti_uint32*) vector;

  /*local variables for state*/
  _ti_uint32 s0 = v_state[DSP_urand32_STATUS_0];
  _ti_uint32 s1 = v_state[DSP_urand32_STATUS_1];
  _ti_uint32 s2 = v_state[DSP_urand32_STATUS_2];
  _ti_uint32 s3 = v_state[DSP_urand32_STATUS_3];

  /*local variables for polynomial*/
  const _ti_uint32 mat1 = v_state[DSP_urand32_MAT_1];
  const _ti_uint32 mat2 = v_state[DSP_urand32_MAT_2];
  const _ti_uint32 tmat = v_state[DSP_urand32_TMAT];

  /*Obtain uniform random integers*/
  for (i = 0; i < size; ++i)
  {
    array[i] =
       DSP_urand32_generate_random_ti_uint32(&s0, &s1,&s2,&s3,mat1,mat2,tmat);
  }

  /*Save state for next time*/
  DSP_urand32_SAVE_STATE(s0, s1, s2, s3);

} /* DSP_urand32 */

/* ======================================================================== */
/*  End of file:  DSP_urand32.c                                             */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
