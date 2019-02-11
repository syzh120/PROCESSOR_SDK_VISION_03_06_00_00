/* ======================================================================= */
/* DSP_urand32_cn.c -- Natural C Implementation                            */
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
#include <stdlib.h>
#include "DSP_urand32_cn.h"

/*=========================================================================*/
/* State Array Positions                                                   */
/*=========================================================================*/
/*State*/
const int DSP_urand32_cn_STATUS_0 = (0);
const int DSP_urand32_cn_STATUS_1 = (1);
const int DSP_urand32_cn_STATUS_2 = (2);
const int DSP_urand32_cn_STATUS_3 = (3);

/*Polynomial*/
const int DSP_urand32_cn_MAT_1 = (4);
const int DSP_urand32_cn_MAT_2 = (5);
const int DSP_urand32_cn_TMAT  = (6);

/*=========================================================================*/
/* Tiny Mersenne Twister Constants                                         */
/*=========================================================================*/

/*Setup and Next State Constants*/
#define DSP_urand32_cn_PRE_LOOP       (8)
#define DSP_urand32_cn_MIN_LOOP       (8)
#define DSP_urand32_cn_TINYMT_MASK    (0x7ffffffful)

/*Default Polynomial Constants*/
#define DSP_urand32_cn_DEFAULT_MAT_1  (0xd02f1a11)
#define DSP_urand32_cn_DEFAULT_MAT_2  (0xfe80ffa)
#define DSP_urand32_cn_DEFAULT_TMAT   (0x695afbff)

/*=========================================================================*/
/* Internal Function Prototypes                                            */
/*=========================================================================*/
unsigned int generate_random_ti_uint32_cn(_ti_uint32 *state);
void  DSP_urand32_next_state_cn(_ti_uint32 *state);
static _ti_uint32 get__ti_uint32_cn(_ti_uint32 *state);
static void DSP_urand32_period_certification_cn(_ti_uint32 *state);

/*=========================================================================*/
/* Internal Functions                                                      */
/*=========================================================================*/

/*  Function Name: generate_random_ti_uint32_cn
 *
 *  @Purpose: This function is used internally to generate individual
 *  uniformly-distributed random @b _ti_uint32 values. It should not be
 *  called by the user.
 *
 *  @Precondition: The user has maintained the state array
 *
 *  @Postcondition: A uniformly-distributed random @b _ti_uint32 has been
 *  generated
 *
 *  @param state The array which was initialized with the "DSP_urand32_init"
 *  function and maintained (but NEVER modified) by the user between
 *  subsequent calls to the "DSP_urand32" function.
 *
 *  @returns A uniformly distributed random @b int
 *
 */
#pragma CODE_SECTION(generate_random_ti_uint32_cn,".text:ansi");
unsigned int generate_random_ti_uint32_cn(_ti_uint32 *state)
{
   DSP_urand32_next_state_cn(state);
   return get__ti_uint32_cn(state);
} /* generate_random_ti_uint32_cn */

/*  Function Name: period_certification_cn
 *
 *  Purpose: This function is used internally to ensure a period
 *  of 2^127-1. It should not be called by the user.
 *
 *  Precondition: The user has maintained the state array
 *
 *  Postcondition: The period length has been ensured and the state vector
 *  modified accordingly if certification test fails
 *
 *  @param state The array which was initialized with the "DSP_urand32_init"
 *  function and maintained (but NEVER modified) by the user between
 *  subsequent calls to the "DSP_urand32" function.
 *
 */
#pragma CODE_SECTION(DSP_urand32_period_certification_cn,".text:ansi");
static void DSP_urand32_period_certification_cn(_ti_uint32 *state)
{
    if ((state[DSP_urand32_cn_STATUS_0] & DSP_urand32_cn_TINYMT_MASK) == 0
           && state[DSP_urand32_cn_STATUS_1] == 0
           && state[DSP_urand32_cn_STATUS_2] == 0
           && state[DSP_urand32_cn_STATUS_3] == 0)
    {
        state[DSP_urand32_cn_STATUS_0] = 'T';
        state[DSP_urand32_cn_STATUS_1] = 'I';
        state[DSP_urand32_cn_STATUS_2] = 'N';
        state[DSP_urand32_cn_STATUS_3] = 'Y';
    }
} /* DSP_urand32_period_certification_cn */

/*  Function Name: DSP_urand32_next_state_cn
 *
 *  Purpose: This function is used internally to modify the state so that
 *  the next random number may be generated. It should not be called by the
 *  user.
 *
 *  Precondition: The user has maintained the state array
 *
 *  Postcondition: The "finite state machine" of the RNG has been modified
 *  so that the next random transition can occur.
 *
 *  @param state The array which was initialized with the "DSP_urand32_init"
 *  function and maintained (but NEVER modified) by the user between
 *  subsequent calls to the "DSP_urand32" function.
 *
 */
#pragma CODE_SECTION(DSP_urand32_next_state_cn,".text:ansi");
void DSP_urand32_next_state_cn (_ti_uint32* state)
{
  /* Temporary variables */
    _ti_uint32 j, k;

    k = state[DSP_urand32_cn_STATUS_3];
    j = (state[DSP_urand32_cn_STATUS_0] & DSP_urand32_cn_TINYMT_MASK) ^
    		state[DSP_urand32_cn_STATUS_1] ^ state[DSP_urand32_cn_STATUS_2];
    j ^= (j << 1);
    k ^= (k >> 1) ^ j;
    state[DSP_urand32_cn_STATUS_0] = state[DSP_urand32_cn_STATUS_1];
    state[DSP_urand32_cn_STATUS_1] = state[DSP_urand32_cn_STATUS_2];
    state[DSP_urand32_cn_STATUS_2] = j ^ (k << 10);
    state[DSP_urand32_cn_STATUS_3] = k;

    state[DSP_urand32_cn_STATUS_1] ^= -((_ti_int32) (k & 1)) &
    		state[DSP_urand32_cn_MAT_1];

    state[DSP_urand32_cn_STATUS_2] ^= -((_ti_int32) (k & 1)) &
    		state[DSP_urand32_cn_MAT_2];
} /* DSP_urand32_next_state_cn */


/*  Function Name: get__ti_uint32_cn
 *
 *  @Purpose: This function is used internally to generate a random number
 *  based on the current state It should not be called by the user. It
 *  basically concatenates the 4 status variables into one @b _ti_uint32.
 *  It should not be called by the user.
 *
 *  @Precondition: The u *  @Precondition: The user has maintained the state array and
 *  "DSP_urand32_next_state_cn" was previously called
 *
 *  @Postcondition  A random number based on the current state of the RNG has
 *  been returned
 *
 *  @param state The array which was initialized with tFhe "DSP_urand32_init"
 *  function and maintained (but NEVER modified) by the user between subsequent
 *  calls to the "DSP_urand32" function.
 *
 *  @returns A uniformly distributed random @b _ti_uint32.
 *
 */
#pragma CODE_SECTION(get__ti_uint32_cn,".text:ansi");
_ti_uint32 get__ti_uint32_cn(_ti_uint32* state)
{
  /* Temporary variables */
    _ti_uint32 j, k;

    j = state[DSP_urand32_cn_STATUS_3];
    k = state[DSP_urand32_cn_STATUS_0] + (state[DSP_urand32_cn_STATUS_2] >> 8);
    j ^= k;
    j ^= -((_ti_int32) (k & 1)) & state[DSP_urand32_cn_TMAT];
    return j;
} /* get__ti_uint32_cn */

/*=========================================================================*/
/* User Functions                                                          */
/*=========================================================================*/
#pragma CODE_SECTION(DSP_urand32_init_cn,".text:ansi");
void DSP_urand32_init_cn(
    unsigned int seed,        /*Arbitrary number used for initialization     */
    void* restrict polynomial,/*Array of length 3 containing polynomial data */
    void* restrict state)     /*Array of length 7 allocated and uninitialized*/

{
    _ti_uint32* v_state = (_ti_uint32*) state; /* Non-void pointer to state */
    _ti_uint32* v_polynomial;             /* Non-void pointer to polynomial */
    int i;                                /* Loop counter */

    /* Check if user provided polynomial values. if not, use default values */
    if (polynomial == NULL)
    {
        v_polynomial =    malloc(3 * sizeof(_ti_uint32));
        v_polynomial[0] = (_ti_uint32) DSP_urand32_cn_DEFAULT_MAT_1;
        v_polynomial[1] = (_ti_uint32) DSP_urand32_cn_DEFAULT_MAT_2;
        v_polynomial[2] = (_ti_uint32) DSP_urand32_cn_DEFAULT_TMAT;
    }
    else
    {
        v_polynomial = polynomial;
    }

    /* Initialize the state array */
    v_state[DSP_urand32_cn_MAT_1] = v_polynomial[0];
    v_state[DSP_urand32_cn_MAT_2] = v_polynomial[1];
    v_state[DSP_urand32_cn_TMAT] = v_polynomial[2];
    v_state[DSP_urand32_cn_STATUS_0] = (_ti_uint32) seed & 0xFFFFFFFFu;
    v_state[DSP_urand32_cn_STATUS_1] = v_state[DSP_urand32_cn_MAT_1];
    v_state[DSP_urand32_cn_STATUS_2] = v_state[DSP_urand32_cn_MAT_2];
    v_state[DSP_urand32_cn_STATUS_3] = v_state[DSP_urand32_cn_TMAT];

    for (i = 1; i < DSP_urand32_cn_MIN_LOOP; i++)
  {
    v_state[i & 3] ^= i + 1812433253ul * (v_state[(i - 1) & 3] ^
                      (v_state[(i - 1) & 3] >> 30));
  }

    /* Ensure Period of (2^127)-1 */
    DSP_urand32_period_certification_cn(v_state);

    /*Iterate through first 8 states */
    for (i = 0; i < DSP_urand32_cn_PRE_LOOP; i++)
    {
        DSP_urand32_next_state_cn(v_state);
    }
} /* DSP_urand32_init_cn */

#pragma CODE_SECTION(DSP_urand32_cn,".text:ansi");
void DSP_urand32_cn(unsigned int size,     /*Size of the vector to be filled*/
                    void* vector,        /*Pointer to the destination vector*/
                    void* state)           /*State vector maintained by user*/
{
    _ti_uint32* v_state = (_ti_uint32*) state;  /* Non-void pointer to state */
    _ti_uint32* array = (_ti_uint32*) vector;  /* Non-void pointer to vector */

    int i = 0; /* Loop counter */

    while (i < size)
    {
        array[i++] = generate_random_ti_uint32_cn((_ti_uint32*) v_state);
    }
} /* DSP_urand32_cn */

/* ======================================================================== */
/*  End of file:  DSP_rand32_cn.c                                           */
/* ------------------------------------------------------------------------ */
/*            Copyright (c) 2013 Texas Instruments, Incorporated.           */
/*                           All Rights Reserved.                           */
/* ======================================================================== */
